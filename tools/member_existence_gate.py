"""成员存在性/容器真实性裁定门（W1 v2）——系统性排查修复方案 v2 §4 的判据实现。

v2 重写（复核 5eb371d4 四硬伤返工 + fbe198d4 六条件收口）：
- **单遍 xref 形态索引**：全函数体一遍扫描，按形态分类（push_arg/mov_load/mov_store/
  mov_imm/fpu/cmp/lea/other）——"该地址被引用"≠"是本容器成员"，形态才分语义；
- **结构性负证优先**：容器级幻影传播 → static 块侵入 → A 级锚仲裁（>区间包含）→
  串对象形态（仅 push 实参 + 非文本型 + NUL 终止串）⇒ phantom；数据访问形态 ≥2 ⇒ exists，
  **=1 ⇒ exists（弱正证，单点真成员场景实证存在——C 契约锁）**；其余 pending；
- **判据②③⑤⑥落地**：②ctor thunk 对（`B9 imm32 E9 rel32` 字节级全 .text）为 A 级锚；
  ③static guard 块直扫（atexit 邻域写簇 + **guard-test 三元组要求**——收窄复核 fbe198d4
  R2 误伤）；⑤串指纹三条件（GBK 感知 + 严格 NUL + push 实参形态）；⑥同址冲突 A 级仲裁。
- **判据①this 物化锚、④尺寸锚、区间覆盖仲裁：未实现**（_meta.caveats 如实标注，不虚标）。

口径（P1-e）：_meta 记录探针/输入 md5 + 参数 + 时间戳；行内证据带 insn VA + 形态。
⚠️ 覆盖扩展（2026-10-16，R11 契约守恒）：MEG_EXTEND_XREF=1 开启语料外（gap）域补扫
（classify_gap_regions + scan_shape_index 纯函数，tests/test_xref_coverage.py 6/6）；
默认关。stash 判别实证（2026-10-17）：HEAD 版 self-test=13/37 FAIL（既有契约债，非本扩展引入）；
开/关旗标败数同 13/37 ⇒ gap 合流契约中性；13 败项疑黄金案读活注解数据随他线在途漂移，待独立核查。
用法（只读）：
    python tools/member_existence_gate.py                # 全库裁定报告
    python tools/member_existence_gate.py --class PAL3
    python tools/member_existence_gate.py --self-test    # 黄金用例 + 判定契约
"""
import argparse
import collections
import hashlib
import json
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools.type_evidence import exe_text_image, load_func_ranges, parse_member_key  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PAL3_EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
IDA_STRUCTS = os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json')
ANN_STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')
ANN_GLOBALS = os.path.join(ROOT, 'data', 'annotations', 'globals.json')
ONEXIT_WRAP = 0x553041

TEXTUAL_TYPES = ('char', 'byte', 'wchar')   # 仅**数组**形态算文本存储（指针不算，见下）
DATA_SHAPES = ('mov_load', 'mov_store', 'mov_imm', 'fpu', 'cmp', 'lea')


# ---------------------------------------------------------------- 纯函数（R15）

def type_is_textual(declared):
    """文本存储判别（v2 修正：dict 安全 + **只认数组**）。
    char*/BYTE* 指针型的槽里存的是指针，槽内出现串字节=矛盾（负证素材）⇒ 不算文本；
    dict 形态（inline union/struct，CLAUDE.md 允许）不是文本且**不得崩**。"""
    if isinstance(declared, dict):
        return False
    t = (declared or '').lower()
    return any(k in t for k in TEXTUAL_TYPES) and '[' in t


def string_fingerprint(buf, min_run=4):
    """串指纹条件 A+B：≥min_run 连续文本字节 + **严格 NUL 收尾**。
    v2：文本字节含 GBK 高位（0x80-0xFF）——'(%s)' 型 GBK 格式串此前漏检。
    复核 fbe198d4 P2⑧/E6：24B 全文本无 NUL 不得判串（FOURCC "RIFF"+后随数据是真成员）。"""
    s = 0
    while s < len(buf) and buf[s] == 0:
        s += 1
    e = s

    def _txt(b):
        return 32 <= b < 127 or b >= 0x80
    while e < len(buf) and _txt(buf[e]):
        e += 1
    if e - s >= min_run and e < len(buf) and buf[e] == 0:      # 严格要求 NUL 终止
        return buf[s:e].decode('latin-1')
    return None


def classify_member(shapes, str_run, declared_type, in_static_block,
                    foreign_a_anchor, container_phantom):
    """成员级判定 v2（结构性负证优先）→ (verdict, notes)。
    规则序（复核 5eb371d4 硬伤 3 语义修正）：
      1 容器级幻影 ⇒ phantom（成员不存在于该容器——m_sz5D8C3C 案）；
      2 static 块侵入 ⇒ phantom（PAL3 statics 案）；
      3 A 级锚仲裁：他对象 A 级锚 > 区间包含 ⇒ phantom（g_palScript vs m_pCameraCtrl 案）；
      4 串对象形态：非文本型 + 仅 push_arg 引用 + 串指纹 ⇒ phantom（m_pDisplay 案）；
      5 数据访问形态 ≥2 ⇒ exists（FOURCC/真成员落串区案）；
      6 其余 ⇒ pending（无证据 ≠ 不存在）。
    反例契约（--self-test 锁）：FOURCC int 槽"RIFF"+数据访问 ⇒ 不得 phantom；
    char* 槽压串字节+仅 push ⇒ phantom；char[216] 落串区+push ⇒ 不得 phantom。"""
    notes = []
    if container_phantom:
        notes.append('容器级幻影传播')
        return 'phantom', notes
    if in_static_block:
        notes.append('函数内 static 块侵入（guard+atexit 三元组区）')
        return 'phantom', notes
    if foreign_a_anchor:
        notes.append('A 级锚仲裁：%s > 区间包含' % foreign_a_anchor)
        return 'phantom', notes
    n_push = shapes.get('push_arg', 0)
    n_data = sum(shapes.get(s, 0) for s in DATA_SHAPES)
    textual = type_is_textual(declared_type)
    if str_run is not None and not textual and n_data == 0 and n_push >= 1:
        notes.append('串对象形态：非文本型槽压串字节且唯一引用=指针实参（条件 C）')
        return 'phantom', notes
    if textual and str_run is not None:
        notes.append('文本/字节数组落串区=常态（不作负证）')
    # 规则序（N2 补记）：5) 数据访问 ≥2 ⇒ exists；**=1 ⇒ exists（弱正证，单点真成员
    # 场景实证存在，C12 锁）**；6) 其余 pending。
    if n_data >= 2:
        notes.append('数据访问形态 %d 站点' % n_data)
        return 'exists', notes
    if n_data == 1:
        notes.append('数据访问单点（真成员可只被一处用 ⇒ 弱正证）')
        return 'exists', notes
    notes.append('无成员访问形态证据（push=%d）' % n_push)
    return 'pending', notes


def verdict_of(pos, neg):
    if pos and neg:
        return 'disputed'
    return 'exists' if pos else ('phantom' if neg else 'pending')


# ---------------------------------------------------------------- 二进制索引（单遍）

_CACHED = {}


def _load():
    if 'core' not in _CACHED:
        data, va2off, sections = exe_text_image()
        funcs = load_func_ranges()
        _CACHED['core'] = (data, va2off, sections, funcs)
    return _CACHED['core']


def build_xref_index():
    """单遍全函数体扫描：{abs_va: [(insn_va, mnemonic, shape)]}。
    形态（复核 Q3 口径）：push_arg=指针实参；mov_load/mov_store/mov_imm=数据访问；
    fpu=浮点读写；cmp/test=比较；lea=地址物化；other。"""
    if 'xref' in _CACHED:
        return _CACHED['xref']
    import capstone
    from capstone import x86 as cs_x86
    data, va2off, sections, funcs = _load()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    idx = collections.defaultdict(list)
    for fva, sz in funcs:
        off = va2off(fva)
        if off is None or sz > 0x30000:
            continue
        for ins in md.disasm(data[off:off + sz], fva):
            mn = ins.mnemonic
            for op in ins.operands:
                target, shape = None, 'other'
                if op.type == cs_x86.X86_OP_IMM:
                    target = op.imm & 0xFFFFFFFF
                    # 复核 84fd2ef7 Q5 缺陷修：`mov reg,imm`=**地址物化**（不作数据访问证据
                    # ——曾把 m_vCamLookAt/m_CamMatrix/m_fTileSize 误升 exists 漏选）；
                    # 仅 `mov [mem],imm` 的 imm 才是数据初始化（mov_imm）。
                    if mn == 'push':
                        shape = 'push_arg'
                    elif mn == 'lea':
                        shape = 'lea'
                    elif mn.startswith('mov'):
                        shape = 'mov_imm' if (ins.operands and
                                              ins.operands[0].type == cs_x86.X86_OP_MEM) else 'addr'
                    else:
                        shape = 'other'
                elif op.type == cs_x86.X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0:
                    target = op.mem.disp & 0xFFFFFFFF
                    if mn.startswith('f') and mn not in ('fs',):
                        shape = 'fpu'
                    elif mn in ('cmp', 'test'):
                        shape = 'cmp'
                    elif mn == 'lea':
                        shape = 'lea'
                    elif mn.startswith('mov'):
                        shape = 'mov_store' if ins.operands[0] is op else 'mov_load'
                        if mn == 'mov' and ins.operands[0] is op and \
                                ins.operands[1].type == cs_x86.X86_OP_IMM:
                            shape = 'mov_imm'
                    else:
                        shape = 'other'
                if target is not None and 0x400000 <= target < 0x2000000:
                    idx[target].append((ins.address, mn, shape))
    if not os.environ.get('MEG_EXTEND_XREF'):
        _CACHED['xref'] = idx
        return idx
    # 语料外（gap）域补扫（2026-10-16 覆盖扩展：xref 此前仅扫 decomp 语料函数域 ⇒
    # 语料外成员无从判证 = pending 2751 的 73.6% 盲区；gap 证据与语料内同强度（指令级 A 级））
    _, _, sections, _ = _load()
    text = next((x for x in sections if x[0] in ('.text', 'TEXT')), None)
    if text:
        t0, t1 = text[1], text[1] + text[2]
        gaps = classify_gap_regions((t0, t1), funcs)
        gap_idx = scan_shape_index(data, t0, va2off, gaps)
        for k, v in gap_idx.items():
            idx[k].extend(v)
    _CACHED['xref'] = idx
    return idx


# ---------------------------------------------------------------- 覆盖扩展（R15 纯函数，tests/test_xref_coverage.py）

def classify_gap_regions(text_span, func_ranges):
    """语料函数域对 .text 的补集 = 语料外（gap）域（纯函数）。
    text_span=(start,end) 端不含；func_ranges=[(fva,size)]；重叠域先并、越界裁剪。
    返回 [(start,size),...] 升序不相交。"""
    t0, t1 = text_span
    clipped = []
    for fva, sz in func_ranges:
        a, b = max(fva, t0), min(fva + sz, t1)
        if b > a:
            clipped.append((a, b))
    clipped.sort()
    merged = []
    for a, b in clipped:
        if merged and a <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(merged[-1][1], b))
        else:
            merged.append((a, b))
    gaps, cur = [], t0
    for a, b in merged:
        if a > cur:
            gaps.append((cur, a - cur))
        cur = max(cur, b)
    if t1 > cur:
        gaps.append((cur, t1 - cur))
    return gaps


def scan_shape_index(code, base_va, va2off, ranges):
    """对任意域做单遍形态索引（纯函数逻辑；不改全局缓存）。
    形态口径与 build_xref_index 同源：push_arg/lea/addr/mov_imm/mov_load/mov_store/fpu/cmp/other。
    不可解码字节单遍前进不崩（R15 契约：确定性、零 IO 副作用）。"""
    import capstone
    from capstone import x86 as cs_x86
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    idx = collections.defaultdict(list)
    for rva, rsz in ranges:
        off = va2off(rva)
        if off is None or rsz <= 0 or rsz > 0x30000:
            continue
        blob = code[off:off + rsz]
        pos = 0
        while pos < len(blob):
            ins_list = list(md.disasm(blob[pos:pos + 15], rva + pos, count=1))
            if not ins_list:
                pos += 1
                continue
            ins = ins_list[0]
            mn = ins.mnemonic
            for op in ins.operands:
                target, shape = None, 'other'
                if op.type == cs_x86.X86_OP_IMM:
                    target = op.imm & 0xFFFFFFFF
                    if mn == 'push':
                        shape = 'push_arg'
                    elif mn == 'lea':
                        shape = 'lea'
                    elif mn.startswith('mov'):
                        shape = 'mov_imm' if (ins.operands and
                                              ins.operands[0].type == cs_x86.X86_OP_MEM) else 'addr'
                elif op.type == cs_x86.X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0:
                    target = op.mem.disp & 0xFFFFFFFF
                    if mn.startswith('f') and mn not in ('fs',):
                        shape = 'fpu'
                    elif mn in ('cmp', 'test'):
                        shape = 'cmp'
                    elif mn == 'lea':
                        shape = 'lea'
                    elif mn.startswith('mov'):
                        shape = 'mov_store' if ins.operands[0] is op else 'mov_load'
                        if mn == 'mov' and ins.operands[0] is op and \
                                ins.operands[1].type == cs_x86.X86_OP_IMM:
                            shape = 'mov_imm'
                if target is not None and 0x400000 <= target < 0x2000000:
                    idx[target].append((ins.address, mn, shape))
            pos += ins.size
    return dict(idx)


def _find_guard_jump(win):
    """保护体起点判定（纯函数，N1 补咬合）：win=[(addr, mnemonic, is_test_imm8, is_cond_jump)]；
    返回 guard 条件跳地址（写点须 > 该址才算保护体内）或 None。
    归因勘误（复核 63ce3392 N1）：vRotate 案靠**同块豁免**解救、tag17A7BData 案靠
    **guard 三元组要求**解救——保护体内过滤是第三道防线（此为其专属锁）。"""
    for qi, (addr, mn, is_test, _cj) in enumerate(win):
        if is_test:
            for (a2, mn2, _t2, cj2) in win[qi + 1:]:
                if cj2:
                    return a2               # 保护体 = 条件跳之后
    return None


def _resolve_this_def(win):
    """call 前窗口内 ECX 物化的**最近定义优先**解析（纯函数；复核 5eb371d4 Q4 语义修复）。
    win = [(mnemonic, op_str)] **自 call 逆序**（近→远）。返回 (imm|None, note)。
    - `mov ecx,imm32` / `lea ecx,[imm32]` ⇒ 物化（T3 修复：取最近而非最旧定义）；
    - `mov ecx,reg` ⇒ 窗口内 reg 的最近 imm 装载做**一层复制传播**（T4）；
    - 其他 ecx 写点（mov ecx,[mem] / add ecx / pop ecx …）⇒ **失效保守放弃**（T2）；
    - `lea ecx,[reg+N]` 基址不可考 ⇒ 放弃不猜（T5）。"""
    reg_imm = {}
    want = None            # 进入"追踪 reg 定义"态（mov ecx,reg 的复制传播，T4）
    for mn, ops in win:
        o = ops.replace(' ', '')
        if want is not None:
            if mn == 'mov' and o.startswith(want + ','):
                rest = o[len(want) + 1:]
                if rest.startswith('0x'):
                    return int(rest, 16), 'mov-copy(%s)' % want
            if o.split(',')[0] == want or (mn in ('pop', 'xchg') and want in o):
                return None, 'src-clobber(%s)' % want            # 追踪源被写 ⇒ 放弃
            continue
        if mn == 'mov' and o.startswith('ecx,'):
            rest = o[4:]
            if rest.startswith('0x'):
                return int(rest, 16), 'mov-imm'
            want = rest                                          # T4：转追踪源寄存器
            continue
        if mn == 'lea' and o.startswith('ecx,'):
            if o.startswith('ecx,[0x'):
                return int(o.split('[0x')[1].rstrip(']'), 16), 'lea-abs'
            return None, 'lea-relative'                          # T5 保守放弃
        if o.split(',')[0] in ('ecx',) or (mn in ('pop', 'xchg') and 'ecx' in o):
            return None, 'ecx-clobber(%s)' % mn                  # T2 写点失效
    return None, 'no-def'


def build_this_anchor_index():
    """判据① 对象级：call <方法入口> 前 ECX 物化聚类（最近定义优先语义）。
    返回 {obj_imm: (count, notes)}——W1 正面证据（对象性最直接）。
    方法入口集 = 注解 methods 全体（跨类聚类后按实例区间归属）。"""
    if 'this_anchor' in _CACHED:
        return _CACHED['this_anchor']
    import capstone
    from capstone import x86 as cs_x86
    data, va2off, sections, funcs = _load()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    import os as _os
    import json as _json
    mvas = set()
    sdir = _os.path.join(ROOT, 'data', 'annotations', 'structs')
    for f in _os.listdir(sdir):
        if not f.endswith('.json'):
            continue
        try:
            dd = _json.load(open(_os.path.join(sdir, f), encoding='utf-8'))
        except Exception:
            continue
        for k in (dd.get('methods') or {}):
            try:
                mvas.add(int(str(k), 16) if str(k).startswith('0x') else int(str(k)))
            except Exception:
                pass
    hits = collections.defaultdict(lambda: [0, collections.Counter()])
    for fva, sz in funcs:
        off = va2off(fva)
        if off is None or sz > 0x20000:
            continue
        insns = list(md.disasm(data[off:off + sz], fva))
        for i, ins in enumerate(insns):
            if ins.mnemonic == 'call' and ins.operands and \
                    ins.operands[0].type == cs_x86.X86_OP_IMM:
                tgt = ins.operands[0].imm & 0xFFFFFFFF
                if tgt not in mvas:
                    continue
                win = [(p.mnemonic, p.op_str)
                       for p in reversed(insns[max(0, i - 24):i])]   # T7 窗口 24
                imm, note = _resolve_this_def(win)
                if imm is not None and 0x400000 <= imm < 0x2000000:
                    hits[imm][0] += 1
                    hits[imm][1][note] += 1
    out = {imm: (n, dict(notes)) for imm, (n, notes) in hits.items()}
    _CACHED['this_anchor'] = out
    return out


def build_static_blocks():
    """判据③直扫：atexit 注册（call 0x553041）邻域写簇，且**必须含 guard-test 三元组**
    （`test <r8>,<imm8>` + 条件跳——复核 fbe198d4 R2 收窄：纯成员初始化写不构成 static 块，
    g_vRotateAxis/tag17A7BData 误伤案）+ guard 字节写 ⇒ 函数内 static 存储块 [lo,hi)。
    返回 (blocks, detail)。"""
    if 'statics' in _CACHED:
        return _CACHED['statics']
    import capstone
    from capstone import x86 as cs_x86
    data, va2off, sections, funcs = _load()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    writes = []          # (insn_va, abs, imm)
    for fva, sz in funcs:
        off = va2off(fva)
        if off is None or sz > 0x30000:
            continue
        insns = list(md.disasm(data[off:off + sz], fva))
        for i, ins in enumerate(insns):
            if ins.mnemonic == 'call' and ins.operands and \
                    ins.operands[0].type == cs_x86.X86_OP_IMM and \
                    (ins.operands[0].imm & 0xFFFFFFFF) == ONEXIT_WRAP:
                win = insns[max(0, i - 40):i]
                guard_jump = _find_guard_jump([
                    (p.address, p.mnemonic,
                     p.mnemonic == 'test' and p.operands and
                     p.operands[1].type == cs_x86.X86_OP_IMM and p.operands[1].imm < 0x100,
                     p.mnemonic.startswith('j') and p.mnemonic != 'jmp')
                    for p in win])
                if guard_jump is None:
                    continue
                for p in win:
                    if p.address <= guard_jump:
                        continue                   # 只收保护体内的写
                    if p.mnemonic == 'mov' and p.operands and \
                            p.operands[0].type == cs_x86.X86_OP_MEM and \
                            p.operands[0].mem.base == 0 and p.operands[0].mem.index == 0:
                        writes.append((p.address, p.operands[0].mem.disp & 0xFFFFFFFF,
                                       p.operands[1].imm & 0xFFFFFFFF
                                       if p.operands[1].type == cs_x86.X86_OP_IMM else -1))
    addrs = sorted({a for _, a, _ in writes})
    blocks = []
    for a in addrs:
        if blocks and a - blocks[-1][1] <= 16:
            blocks[-1][1] = a + 4
        else:
            blocks.append([a, a + 4])
    _CACHED['statics'] = ([(lo, hi) for lo, hi in blocks], writes)
    return _CACHED['statics']


def build_ctor_anchors():
    """判据② A 级锚：`mov ecx,imm32; jmp rel32` ctor thunk（g_palScript@0x4086C0 形态）。
    **字节级全 .text 扫**（thunk 常不在 decomp 函数语料内——G3 实测教训）。
    返回 {obj_va: (thunk_va, ctor_va)}。"""
    if 'ctor' in _CACHED:
        return _CACHED['ctor']
    import struct as _st
    data, va2off, sections, funcs = _load()
    out = {}
    for name, sva, ssz, _rel in sections:
        if name not in ('.text', '.code'):
            continue
        off = va2off(sva)
        blob = data[off:off + ssz]
        i = 0
        while True:
            i = blob.find(b'\xB9', i)
            if i < 0 or i + 10 > len(blob):
                break
            if blob[i + 5] == 0xE9:                     # B9 imm32 E9 rel32
                obj = _st.unpack('<I', blob[i + 1:i + 5])[0]
                rel = _st.unpack('<i', blob[i + 6:i + 10])[0]
                thunk_va = sva + i
                ctor_va = (thunk_va + 10 + rel) & 0xFFFFFFFF
                if 0x400000 <= obj < 0x2000000 and 0x400000 <= ctor_va < 0x600000:
                    out[obj] = (thunk_va, ctor_va)
            i += 1
    _CACHED['ctor'] = out
    return out


def build_push_index():
    """xref 语料外补充：全 .text 字节级 `push imm32`（68 xx xx xx xx）→ {va: [push sites]}。
    （m_sz5D8C3C/g_EffMgr 串实参的 push 站点有在 decomp 语料外的——G4 实测教训。"""
    if 'push' in _CACHED:
        return _CACHED['push']
    import struct as _st
    data, va2off, sections, funcs = _load()
    out = collections.defaultdict(list)
    for name, sva, ssz, _rel in sections:
        if name not in ('.text', '.code'):
            continue
        off = va2off(sva)
        blob = data[off:off + ssz]
        i = 0
        while True:
            i = blob.find(b'\x68', i)
            if i < 0 or i + 5 > len(blob):
                break
            v = _st.unpack('<I', blob[i + 1:i + 5])[0]
            if 0x400000 <= v < 0x2000000:
                out[v].append(sva + i)
            i += 1
    _CACHED['push'] = out
    return out


def object_level_phantom(base, span, data, va2off):
    """容器级幻影：声称区间内文本 run 密度（g_EffMgr 43312B/732 run 实证口径）。"""
    off = va2off(base)
    if off is None or not span:
        return False, 0
    blob = data[off:off + min(span, 0x20000)]
    runs, i = 0, 0
    while i < len(blob):
        b = blob[i]
        if 32 <= b < 127 or b >= 0x80:
            j = i
            while j < len(blob) and (32 <= blob[j] < 127 or blob[j] >= 0x80):
                j += 1
            if j - i >= 4:
                runs += 1
            i = j
        else:
            i += 1
    return runs >= 100, runs


# ---------------------------------------------------------------- 主流程

_NON_CONTAINER = ('skip', 'unknown', 'int', 'float', 'unsigned int', 'char', 'short',
                  'double', 'bool', 'long')       # 双源同过滤（复核 fbe198d4 次要⑦）


def load_instances():
    """实例清单（P0-a 输入面）：**双源合并** —— ida_structs._globals ∪ annotations/globals.json
    （复核 Q7：此前 globals.json 载入未用；Array 件等实例只在注解侧有）。"""
    ida = json.load(open(IDA_STRUCTS, encoding='utf-8'))
    gl = ida.get('_globals') or {}
    insts = {}
    for k, v in gl.items():
        if not isinstance(v, dict):
            continue
        ty, nm = v.get('type') or '', v.get('name') or ''
        if not ty or ty in _NON_CONTAINER:
            continue
        try:
            addr = int(str(k), 16)
        except Exception:
            continue
        insts[(nm, addr, ty)] = 'ida_structs'
    gj = json.load(open(ANN_GLOBALS, encoding='utf-8'))
    items = gj.get('globals') or gj
    for k, v in items.items():
        if not isinstance(v, dict):
            continue
        ty, nm = v.get('type') or '', v.get('name') or k
        if not ty or ty in _NON_CONTAINER:
            continue
        try:
            addr = int(str(k), 16)
        except Exception:
            continue
        if (nm, addr, ty) not in insts:
            insts[(nm, addr, ty)] = 'annotations'
    return [(nm, addr, ty) for (nm, addr, ty) in sorted(insts, key=lambda x: (x[2], x[1]))]


def run_report(only_cls=None):
    data, va2off, sections, funcs = _load()
    xref = build_xref_index()
    sblocks, swrites = build_static_blocks()
    ctor_anchors = build_ctor_anchors()
    this_index = build_this_anchor_index()      # W1 判据①（5eb371d4 Q4 语义）
    insts = load_instances()
    rep = {'_meta': {
        'probe': 'tools/member_existence_gate.py', 'ts': time.strftime('%Y-%m-%dT%H:%M:%S'),
        'probe_md5': hashlib.md5(open(__file__, 'rb').read()).hexdigest(),
        'exe_md5': hashlib.md5(open(PAL3_EXE, 'rb').read()).hexdigest(),
        'ida_structs_md5': hashlib.md5(open(IDA_STRUCTS, 'rb').read()).hexdigest(),
        'params': {'xref_shape_classes': list(DATA_SHAPES) + ['push_arg', 'other'],
                   'static_block_gap': 16, 'phantom_run_threshold': 100},
        'caveats': 'xref 仅覆盖 decomp 函数体语料（3608 函数）+ 语料外 push 字节级补充；'
                   '判据①this 物化锚、④尺寸锚（new/push N/memset/stride）**未实现**；'
                   'A 级锚仲裁仅限**同址冲突**，区间覆盖仲裁未实现（锚落他容器 span 内的'
                   '16 处盲区实测存在）；对象级正证现仅判据②ctor thunk。'
                   '报告数字出档须带本口径（P1-e）',
    }, 'rows': [], 'containers': []}
    # 实例级
    by_type = {}
    for nm, addr, ty in insts:
        by_type.setdefault(ty, []).append((nm, addr))
    for ty, lst in sorted(by_type.items()):
        if only_cls and ty != only_cls:
            continue
        p = os.path.join(ANN_STRUCTS, '%s.json' % ty)
        if not os.path.exists(p):
            continue
        d = json.load(open(p, encoding='utf-8'))
        km = d.get('known_members') or {}
        span = d.get('binary_size') or 0
        for nm, base in lst:
            phantom, runs = object_level_phantom(base, span, data, va2off)
            is_string_name = nm.startswith(('a', 'p')) and ty in (
                'CEffMgr', 'RenderTarget2', 'CEffectSystem', 'CEffModel', 'CCBStage')
            rep['containers'].append({'cls': ty, 'instance': nm, 'base': base, 'span': span,
                                      'text_runs': runs, 'object_phantom': phantom,
                                      'string_named_instance': is_string_name,
                                      'ctor_anchor': ctor_anchors.get(base),
                                      'this_anchor': this_index.get(base, (0, {}))[0]})
            for key, meta in km.items():
                try:
                    off = parse_member_key(key)
                except Exception:
                    continue
                va = base + off
                shapes = collections.Counter(sh for _, _, sh in xref.get(va, []))
                # 语料外 push 补充（G4 教训）：push_arg 形态并入
                extra_push = len(build_push_index().get(va, []))
                if extra_push:
                    shapes['push_arg'] = shapes.get('push_arg', 0) + extra_push
                str_run = string_fingerprint(_read(va, 24))
                _blk = next(('%X-%X' % (lo, hi) for lo, hi in sblocks if lo <= va < hi), None)
                # R2 豁免（fbe198d4 假阳假阳①②定因）：实例基址**同块** ⇒ 该块就是实例自身
                # 存储（static 对象本体注册为实例时，其字段是它自己的成员）⇒ 不定罪。
                # PAL3 案不豁免：base=0xDE7AA0 ∉ static 块 ⇒ statics 槽位确非其成员 ✓。
                _blk_lo, _blk_hi = (int(x, 16) for x in _blk.split('-')) if _blk else (0, 0)
                _self_block = bool(_blk) and _blk_lo <= base < _blk_hi
                in_block = _blk is not None and not _self_block
                foreign_a = None
                for obj, (tv, cv) in ctor_anchors.items():
                    # A 级锚仲裁限定**同址冲突**（obj==va 精确命中，g_palScript 案形态）；
                    # 区间覆盖（obj<va<obj+span）需对象 span 数据——未实现，不虚标。
                    if obj == va and obj != base:
                        foreign_a = 'ctor-anchor:0x%X' % obj
                        break
                verdict, notes = classify_member(dict(shapes), str_run,
                                                 (meta or {}).get('type'),
                                                 in_block, foreign_a, phantom)
                rep['rows'].append({
                    'cls': ty, 'instance': nm, 'base': base, 'key': key, 'offset': off,
                    'name': (meta or {}).get('name'), 'type': (meta or {}).get('type'),
                    'source': (meta or {}).get('source') or '',
                    'shapes': dict(shapes), 'str_run': str_run,
                    'in_static_block': in_block, 'static_block': _blk,
                    'foreign_a_anchor': foreign_a,
                    'container_phantom': phantom,
                    'verdict': verdict, 'notes': notes,
                    'evidence': ['0x%08X %s %s' % (iv, mn, sh) for iv, mn, sh in
                                 (xref.get(va) or [])[:4]],
                })
    # 跨实例 (cls,key) 聚合（复核 63ce3392 7b 裁决：工具显式输出，不推给 W2 去重）。
    # 语义：任一实例 exists ⇒ exists（正证优先）；全 phantom 且机制为类级（容器传播/
    # 块侵入）⇒ phantom；全 pending ⇒ pending；其余 ⇒ disputed + contradiction 标记。
    by_ck = collections.defaultdict(list)
    for r in rep['rows']:
        by_ck[(r['cls'], r['key'])].append(r)
    aggs = []
    for (cls, key), rs in sorted(by_ck.items()):
        vs = {r['instance']: r['verdict'] for r in rs}
        vals = list(vs.values())
        class_mech = any(('容器级幻影' in n) or ('static' in n) or ('A 级锚' in n)
                         for r in rs for n in r['notes'])
        if 'exists' in vals:
            agg = 'exists'
        elif vals and all(v == 'phantom' for v in vals):
            agg = 'phantom' if class_mech else 'disputed'
        elif all(v == 'pending' for v in vals):
            agg = 'pending'
        else:
            agg = 'disputed'
        aggs.append({'cls': cls, 'key': key, 'name': rs[0].get('name'),
                     'aggregate': agg, 'per_instance': vs,
                     'contradiction': len(set(vals)) > 1})
    rep['aggregates'] = aggs
    return rep


def _read(va, n):
    data, va2off, sections, funcs = _load()
    off = va2off(va)
    return b'' if off is None else data[off:off + n]


# ---------------------------------------------------------------- 黄金用例 + 判定契约

def self_test():
    fails = 0
    total = 0

    def check(name, cond, detail=''):
        nonlocal fails, total
        total += 1
        if cond:
            print('PASS %s' % name)
        else:
            fails += 1
            print('FAIL %s %s' % (name, detail))

    # —— 判定契约（复核 5eb371d4：黄金必须打判定核心）——
    v, _ = classify_member({'mov_load': 2, 'mov_imm': 1}, 'RIFF', 'int', False, None, False)
    check('C1 FOURCC int 槽落"串"+数据访问 ⇒ 不得 phantom（假阳反例）', v == 'exists', v)
    v, _ = classify_member({'push_arg': 1}, 'quake', 'char *', False, None, False)
    check('C2 char* 槽压串字节+仅 push ⇒ phantom（假阴反例）', v == 'phantom', v)
    v, _ = classify_member({'push_arg': 3}, 'logpath', 'char [216]', False, None, False)
    check('C3 char[] 文本型落串区+push ⇒ 不得 phantom', v == 'pending', v)
    v, _ = classify_member({}, None, 'int', True, None, False)
    check('C4 static 块侵入 ⇒ phantom', v == 'phantom', v)
    v, _ = classify_member({'mov_load': 5}, None, 'int', False, 'ctor-anchor:0xC10968', False)
    check('C5 A 级锚仲裁 ⇒ phantom', v == 'phantom', v)
    v, _ = classify_member({'mov_load': 5}, None, 'int', False, None, True)
    check('C6 容器幻影传播 ⇒ phantom', v == 'phantom', v)
    v, _ = classify_member({}, None, 'int', False, None, False)
    check('C7 无证据 ⇒ pending（无证据≠不存在）', v == 'pending', v)
    check('C8 dict 型 type 不崩且非文本', type_is_textual({'union': []}) is False)
    check('C9 指针型非文本/数组型文本',
          not type_is_textual('char *') and type_is_textual('char [48]'))
    check('C10 GBK 格式串指纹', string_fingerprint(b'(\xb5\xd0)%s\x00') is not None)
    v, _ = classify_member({'push_arg': 2}, None, 'int', False, None, False)
    check('C11 FOURCC int 槽（RIFF+后随数据⇒无 NUL）仅 push ⇒ 不得 phantom',
          v == 'pending', v)
    v, _ = classify_member({'mov_load': 1}, None, 'int', False, None, False)
    check('C12 数据访问单点=弱正证 ⇒ exists（文档化规则，复核 fbe198d4 条件 3）',
          v == 'exists', v)
    check('C13 无 NUL 文本串不判串（24B 全文本假阳，P2⑧）',
          string_fingerprint(b'RIFF' + bytes([1, 2, 3])) is None
          and string_fingerprint(b'abcd\x00') == 'abcd')
    check('C14 保护体起点判定（N1 专属锁）',
          _find_guard_jump([(0x10, 'test', True, False), (0x12, 'jne', False, True),
                            (0x20, 'mov', False, False)]) == 0x12
          and _find_guard_jump([(0x10, 'mov', False, False)]) is None
          and _find_guard_jump([(0x10, 'test', True, False), (0x12, 'mov', False, False)]) is None)
    # W1 判据① 契约（复核 5eb371d4 Q4：T2 失效/T3 最近定义/T4 复制传播/T5 保守放弃）
    check('C15 this 解析=最近定义优先（T3）',
          _resolve_this_def([('mov', 'ecx, 0x22222222'), ('mov', 'ecx, 0x11111111')])[0] == 0x22222222)
    check('C16 this 追踪源被写/未知 ⇒ 保守放弃（T2）',
          _resolve_this_def([('mov', 'ecx, eax'), ('mov', 'eax, edx')])[0] is None
          and _resolve_this_def([('mov', 'ecx, eax'), ('add', 'eax, 4'),
                                 ('mov', 'eax, 0x1000')])[0] is None)
    check('C17 复制传播一层（T4）',
          _resolve_this_def([('mov', 'ecx, esi'), ('mov', 'esi, 0x33333333')])[0] == 0x33333333)
    check('C18 lea 相对形态保守放弃（T5）/lea 绝对物化',
          _resolve_this_def([('lea', 'ecx, [esi + 8]')])[0] is None
          and _resolve_this_def([('lea', 'ecx, [0x44444444]')])[0] == 0x44444444)

    # —— 二进制黄金（检测器 + 端到端判定）——
    sblocks, swrites = build_static_blocks()
    check('G1 static 块直扫可检出 PAL3 statics 区', any(lo <= 0xDE8DF8 < hi for lo, hi in sblocks),
          str(sblocks[:6]))
    check('G2 atexit 邻域 mov [abs],imm 写簇可数', len(swrites) >= 8, str(len(swrites)))
    ctor = build_ctor_anchors()
    check('G3 g_palScript ctor thunk 锚（A 级）可检出', 0xC10968 in ctor, str(list(ctor)[:8]))
    xref = build_xref_index()
    check('G4 xref 形态索引含 push_arg（含语料外补充）/mov 形态',
          (any(sh == 'push_arg' for _, _, sh in xref.get(0x5D5484, []))
           or len(build_push_index().get(0x5D5484, [])) >= 1)
          and any(sh.startswith('mov') for _, _, sh in xref.get(0xDE8DF8, [])))
    check('G5 m_sz5D8C3C 唯一引用=push 串实参', all(sh == 'push_arg' for _, _, sh in
          (xref.get(0x5D8C3C) or [])[:2]) and len(xref.get(0x5D8C3C) or []) >= 1)
    # 端到端：跑报告子集断言关键 verdict
    rep = run_report(only_cls='PAL3')
    rows = {(r['base'], r['offset']): r for r in rep['rows']}
    # G6：W2 落地后语义（2026-09-28）——幻影行已清除=正确终态，断言其**不存在**+static 块仍在
    r = rows.get((0xDE7AA0, 0x1358))
    check('G6 PAL3+0x1358 幻影行已清除（W2 终态）且 static 块覆盖该区',
          r is None and any(lo <= 0xDE8DF8 < hi for lo, hi in sblocks),
          str(r and r['verdict']))
    check('G7 static 块覆盖起点 0xDE8DE8（+0x1348 区）',
          any(lo <= 0xDE8DE8 < hi for lo, hi in sblocks), str(sblocks[:6]))
    rep2 = run_report(only_cls='CEffMgr')
    rows2 = {(r['base'], r['offset']): r for r in rep2['rows']}
    any_ce = [r for r in rep2['rows'] if r['offset'] == 0xB64]
    check('G8 m_nTargetSlot(auto:overlap 于幻影容器) ⇒ phantom',
          any_ce and all(r['verdict'] == 'phantom' for r in any_ce),
          str([(r['verdict'], r['container_phantom']) for r in any_ce[:3]]))
    any_sz = [r for r in rep2['rows'] if r['offset'] == 0x37B8]
    check('G9 m_sz5D8C3C ⇒ phantom（真实机制=R1 容器传播，非条件 C）',
          any_sz and all(r['verdict'] == 'phantom' and
                         any('容器级幻影' in n for n in r['notes']) for r in any_sz),
          str([(r['verdict'], r['notes']) for r in any_sz[:2]]))
    # G15：条件 C（串对象形态）端到端——aExplosive+0xC 'grid' 串 + 仅 push 实参
    # （N5：目标行在**串名伪实例** aExplosive 上，string_named_instance=True）
    rep_ce = run_report(only_cls='CEffectSystem')
    cc = [r for r in rep_ce['rows'] if r['offset'] == 0xC and r['instance'] == 'aExplosive']
    check('G15 条件 C 端到端（伪实例 aExplosive+0xC 串对象形态 ⇒ phantom）',
          cc and all(r['verdict'] == 'phantom' and any('串对象' in n for n in r['notes'])
                     for r in cc),
          str([(r['verdict'], r['notes'], r['str_run']) for r in cc[:2]]))
    # G16/G17：R2 收窄 + 自身存储豁免回归锁（复核 fbe198d4 假阳①②）
    rep_bc = run_report(only_cls='gbVec3D')
    vr = [r for r in rep_bc['rows'] if r['instance'] == 'g_vRotateAxis' and r['offset'] in (0, 4, 8)]
    check('G16 gbVec3D/g_vRotateAxis x/y/z（static 对象自身字段）不得被 R2 定罪',
          len(vr) == 3 and all(r['verdict'] != 'phantom' for r in vr),
          str([(r['offset'], r['verdict'], r['in_static_block']) for r in vr]))
    rep_17 = run_report(only_cls='tag17A7BData')
    blk17 = [r for r in rep_17['rows'] if r['in_static_block']]
    check('G17 tag17A7BData 字段族（10 行，N4 勘误）不得被 R2 定罪',
          not blk17 and len(rep_17['rows']) >= 10,
          str([(r['name'], r['static_block']) for r in blk17[:4]]))
    # G18：跨实例聚合（63ce3392 7b 裁决语义）——RoleSystem key=1408 组：
    # 84fd2ef7 分类修正（mov reg,imm=地址物化非数据访问）后 g_RoleSlotBuf exists→pending，
    # 组内无正证 ⇒ disputed + contradiction 标记必须亮（冲突不许静默吞）。
    rep_rs = run_report(only_cls='RoleSystem')
    ag = [a for a in rep_rs['aggregates'] if a['key'] == '1408']
    check('G18 跨实例聚合：key=1408 ⇒ disputed + contradiction 标记（分类修正后）',
          ag and ag[0]['aggregate'] == 'disputed' and ag[0]['contradiction'],
          str(ag and ag[0]))
    tbl = [r for r in rep2['rows'] if r['offset'] == 0x91C]
    check('G10 m_EffTable _BYTE[584]：容器传播判 phantom 且**非串字节定罪**',
          tbl and all(r['verdict'] == 'phantom' and any('容器级幻影' in n for n in r['notes'])
                      and not any('串对象' in n for n in r['notes']) for r in tbl),
          str([(r['verdict'], r['notes']) for r in tbl[:2]]))
    # 串名伪实例标记
    check('G11 串名伪实例带 string_named_instance 标记',
          any(c['string_named_instance'] for c in rep2['containers']))
    # G15：判据① 真身聚类锚（Round16 this 物化实证 0x1895580×146/208）
    ti = build_this_anchor_index()
    n189, notes189 = ti.get(0x1895580, (0, {}))
    check('G15 CEffMgr 真身 0x1895580 this 物化聚类 ≥100（判据①）',
          n189 >= 100, 'got %d %s' % (n189, notes189))
    rep3 = run_report(only_cls='SceneMgr')
    cam = [r for r in rep3['rows'] if r['offset'] == 0xC5D8]
    check('G14 SceneMgr+0xC5D8 同址 g_palScript ⇒ A 级锚仲裁 phantom（Q5 案）',
          cam and all(r['verdict'] == 'phantom' and any('A 级锚仲裁' in n for n in r['notes'])
                      for r in cam),
          str([(r['verdict'], r['notes']) for r in cam[:2]]))
    # Array 件（正证：不得收缩）
    arr = [c for c in run_report(only_cls='Array')['containers']]
    check('G12 Array 件实例可产出（非幻影）', bool(arr) and not any(
        c['object_phantom'] for c in arr), str([(c['instance'], c['object_phantom']) for c in arr[:4]]))
    # meta 口径（P1-e）
    check('G13 _meta 含 md5×3 + 参数 + 时间戳', all(
        k in rep['_meta'] for k in ('probe_md5', 'exe_md5', 'ida_structs_md5', 'params', 'ts')))

    print('%s' % ('ALL %d passed' % total if not fails else '%d/%d FAIL' % (fails, total)))
    return 1 if fails else 0


def main(argv=None):
    ap = argparse.ArgumentParser(description='成员存在性/容器真实性裁定门（W1 v2）')
    ap.add_argument('--class', dest='cls')
    ap.add_argument('--report', default=os.path.join('data', 'status', 'member_existence_report.json'))
    ap.add_argument('--self-test', action='store_true')
    args = ap.parse_args(argv)
    if args.self_test:
        return self_test()
    rep = run_report(only_cls=args.cls)
    import collections as _c
    dist = _c.Counter(r['verdict'] for r in rep['rows'])
    print('实例 %d / 成员行 %d / verdict 分布 %s' % (
        len(rep['containers']), len(rep['rows']), dict(dist)))
    out = args.report if os.path.isabs(args.report) else os.path.join(ROOT, args.report)
    json.dump(rep, open(out, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('报告 -> %s' % out)
    return 0


if __name__ == '__main__':
    sys.exit(main())
