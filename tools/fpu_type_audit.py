#!/usr/bin/env python3
"""FPU 伪变量类型恢复：x87 操作数尺寸 census → 批量产 lvars.json 条目。

原理（2026-09-26 FPU 批次，Render2/探针校准）:
  Hex-Rays 把 x87 中间值默认定型 double，而原始的 float/double 信息编码在
  x87 指令的内存操作数尺寸里（fild/fld/fadd/fsub/fmul/fdiv(r)/fst(p) 的
  dword = float、qword/tbyte = double）。对某函数：全部 x87 内存操作均为
  dword ⇒ 该函数的 double 伪变量真类型是 float ⇒ 产出 `{'reg': '<reg1>',
  'type': 'float'}` 注解（lvars.json schema v2，export 钩子应用后 VC6 重新
  发出 float 编码、`and esp,-8` 消失、帧尺寸归位）。

保守边界（宁可漏，不可错）:
  - 函数内出现任何 qword/tbyte x87 内存操作 ⇒ 整函数跳过（真 double 混合，
    per-var 归属需要微码级证据，v1 不做）。
  - 无任何 x87 内存操作（纯寄存器算术）⇒ 无证据，跳过。
  - 已有手写条目的函数键不覆盖。

用法:
  python tools/fpu_type_audit.py            # 产出报告（dry-run）
  python tools/fpu_type_audit.py --write    # 写入 data/annotations/lvars.json
"""
import json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
LVARS = os.path.join(ROOT, 'data', 'annotations', 'lvars.json')

sys.path.insert(0, os.path.join(ROOT, 'tools'))
X87_MEM = re.compile(r'\b(fld|fst|fstp|fild|fist|fistp|fadd|faddp|fiadd|fsub|fsubp|'
                     r'fisub|fsubr|fsubrp|fisubr|fmul|fmulp|fimul|fdiv|fdivp|fidiv|'
                     r'fdivr|fdivrp|fidivr|fcom|fcomp|ficom|fcomp|ftst|fchs|fild)\b')


def exe_text_image():
    """原始 exe 的 .text 切片（VA→文件偏移），与 compare_pal3 同语义。"""
    import struct
    data = open(EXE, 'rb').read()
    e_lfanew = struct.unpack_from('<I', data, 0x3c)[0]
    nsec = struct.unpack_from('<H', data, e_lfanew + 6)[0]
    optsz = struct.unpack_from('<H', data, e_lfanew + 20)[0]
    sect = e_lfanew + 24 + optsz
    imagebase = struct.unpack_from('<I', data, e_lfanew + 24 + 28)[0]

    def va2off(va):
        rva = va - imagebase
        for s in range(nsec):
            h = sect + s * 40
            vsz, vaddr, rsz, roff = struct.unpack_from('<IIII', data, h + 8)
            if vaddr <= rva < vaddr + max(vsz, rsz):
                return roff + (rva - vaddr)
        return None
    return data, va2off


def x87_census(data, va2off, va, size):
    """函数内 x87 内存操作数尺寸 census → dict(dword=n, qword=n, tbyte=n)。"""
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    off = va2off(va)
    if off is None:
        return None
    census = {'dword': 0, 'qword': 0, 'tbyte': 0}
    for ins in md.disasm(data[off:off + size], va):
        if not ins.mnemonic.startswith('f'):
            continue
        if not X87_MEM.match(ins.mnemonic):
            continue
        if 'dword ptr' in ins.op_str:
            census['dword'] += 1
        elif 'qword ptr' in ins.op_str:
            census['qword'] += 1
        elif 'tbyte ptr' in ins.op_str:
            census['tbyte'] += 1
    return census


# 经验排除清单：批量注解实测 nd 恶化的函数（形状主导型对注解敏感——
# 2026-09-26 实测 CEffQuad 双函数 no-annotation 903/945 vs annotated 918/955）。
# 逐函数否决是批量启发式的合法组成；加入前必须有 before/after 测量。
EXCLUDE_FUNCS = {
    '0x004D1300',  # CEffQuad::sub_4D1300
    '0x004D17D0',  # CEffQuad::sub_4D17D0
}


def main():
    write = '--write' in sys.argv
    data, va2off = exe_text_image()
    lv = json.load(open(LVARS, encoding='utf-8'))
    # 自动条目索引：本工具产出的键可安全重生成（删除后重发）；手写键永不覆盖
    all_keys = {k for k in lv if not k.startswith('_')}
    if '_auto_keys' in lv:
        auto_keys = set(lv.get('_auto_keys', []))
    else:
        # 一次性迁移：索引字段建立前本工具已产出 326 键（2026-09-26 首轮批量），
        # 除手写键外全部视为自动条目移交索引管理
        auto_keys = all_keys - {'0x0040C7D0'}
    auto_keys -= EXCLUDE_FUNCS
    existing = all_keys - auto_keys
    # 先摘除旧自动条目（本轮可能产出更多变量，如 long double 扩展）——
    # 摘除前必须留档：stored 记忆要从旧条目读名字（读 lv.get(key) 会拿空集
    # ⇒ 清空全部自动条目的事故）
    auto_entries = {k: lv.get(k, []) for k in auto_keys}
    for k in auto_keys:
        lv.pop(k, None)
    # 排除清单函数：连旧条目一起删除（注解实测负收益）
    for k in EXCLUDE_FUNCS:
        lv.pop(k, None)

    emit, skip_mixed, skip_noev, skip_existing = [], [], [], 0
    tot_dbl_vars = 0
    for f in sorted(os.listdir(DECOMP)):
        if not f.endswith('.json'):
            continue
        d = json.load(open(os.path.join(DECOMP, f), encoding='utf-8'))
        va_s = d.get('address') or ''
        if not va_s:
            continue
        key = '0x%08X' % int(va_s, 16)
        if key in existing:
            skip_existing += 1
            continue
        # 候选来源（2026-09-26 v3）：
        # ① 纯净类型 = 当前 decomp 中 double 的寄存器变量
        #   （float 是注解的效果而非候选——错注的 float 会自证循环，
        #   SceneProp CalculateWorldPos 事故：eax 指针变量被错注 float）；
        #   【long double 不纳入】（2026-09-26 CEffQuad 实验）：long double
        #   变量可能是纯寄存器存留的 80 位值——无内存编码可反驳，all-dword
        #   census 不构成 float 证据；强行 float 化实测 nd 反升（sub_4D1300
        #   903→918、sub_4D17D0 945→955）；
        # ② 记忆类型 = 本工具此前注解过的函数，沿用存储的名字
        #   （注解后 decomp 显示 float，重跑时靠 _auto_keys 记忆保持幂等）。
        stored = {x.get('name') for x in auto_entries.get(key, []) if x.get('name')} \
            if key in auto_entries else set()
        cands = []
        seen = set()
        for x in d.get('local_vars', []):
            nm, reg = x.get('name'), x.get('register')
            if not nm or reg is None or nm in seen:
                continue
            if x.get('type') == 'double' or nm in stored:
                cands.append((nm, reg))
                seen.add(nm)
        if not cands:
            continue
        tot_dbl_vars += len(cands)
        size = int(d.get('size_bytes') or 0)
        if size <= 0:
            continue
        c = x87_census(data, va2off, int(va_s, 16), size)
        if c is None:
            continue
        if c['dword'] == 0 and (c['qword'] or c['tbyte']):
            skip_noev.append((f, c))
            continue
        if c['qword'] or c['tbyte']:
            skip_mixed.append((f, c))
            continue
        if c['dword'] == 0:
            skip_noev.append((f, c))
            continue
        emit.append((key, f, c, cands))

    print('=== FPU 类型恢复 census ===')
    print('候选 double 伪变量: %d 个' % tot_dbl_vars)
    print('全 dword（产出 float 注解）: %d 函数 / %d 变量' % (
        len(emit), sum(len(c) for _, _, _, c in emit)))
    print('混合 qword/tbyte（跳过）: %d' % len(skip_mixed))
    print('无 x87 内存证据（跳过）: %d' % len(skip_noev))
    print('已有条目跳过: %d' % skip_existing)
    for key, f, c, cands in emit[:12]:
        print('  [emit] %s %s  x87=%s  vars=%s' % (key, f[:44], c, [n for n, _ in cands]))
    if not write:
        print('\n(dry-run — 加 --write 落盘 lvars.json)')
        return
    for key, f, c, cands in emit:
        # 寄存器变量按【名】匹配（函数内唯一）：同一 reg1 被 Hex-Rays 顺序复用
        # （st7 上多个变量），reg 键会注错对象（SceneProp C2440 事故）
        lv[key] = [{'name': name, 'type': 'float'} for name, _ in cands]
    lv['_auto_keys'] = sorted(e[0] for e in emit)
    open(LVARS, 'w', encoding='utf-8', newline='').write(
        json.dumps(lv, ensure_ascii=False, indent=1))
    print('\n写入 %s：%d 个自动函数键（手写键保留；总数 %d）' % (
        os.path.relpath(LVARS, ROOT), len(emit), len([k for k in lv if not k.startswith('_')])))


if __name__ == '__main__':
    main()
