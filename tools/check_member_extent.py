#!/usr/bin/env python3
"""E6 小闸：注解级不变量「**成员末端 < binary_size**」（只读）。

缘起（方向复核 e0ea83d9 的 E6 建议 ✓）：这条不变量**正是 apply 拒绝的前置** ✓ ——
`apply_annotations.py` 会按基类尺寸 push 基类子对象，再由 `_layout_end_of_members(..., binary_size)`
判越界 ⇒ 一旦"成员末端 ≥ binary_size"，apply 就会拒绝该 UDT ⇒ **生成头消失** ✓
（UIStatic 152→248 那次 76 单元 C2079 的直接成因 ✓）。
复核者实测：**用正确的 offset 归一后存量为 0** ✓ ⇒ 按"逐闸毕业生效"可**硬接** ✓。

⚠️ offset 键混用（十进制 9792 / `0x…` 51 / `NNN_N` 后缀 4）⇒ **必须归一** ✗，**禁用 `int(k,0)`**
（它会把 `'50814_0'` 当 508140 ✗）。

用法：
    python3 tools/check_member_extent.py            # 检查（越界 ⇒ exit 1）
    python3 tools/check_member_extent.py --self-test # 注入式自检（证明它能失败 ✓）
"""
import argparse, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')
_DIM = re.compile(r'\[(\d+)\]')


def norm_offset(k):
    """offset 键归一：十进制 / 0x… / `NNN_N` 后缀 ⇒ int 或 None（不猜 ✗）。"""
    ks = str(k)
    if ks.startswith('0x') or ks.startswith('0X'):
        try:
            return int(ks, 16)
        except ValueError:
            return None
    if '_' in ks:
        head = ks.split('_')[0]
        return int(head, 10) if re.fullmatch(r'\d+', head) else None
    return int(ks, 10) if re.fullmatch(r'\d+', ks) else None


def _dims(t):
    n = 1
    for d in _DIM.findall(t or ''):
        n *= int(d)
    return n


# 2026-09-21（复核 7f6a52cd 查出本闸**判别力=0** ✗）：原先成员尺寸 = 维度连乘 × **1 字节/元素** ✗
# ⇒ `Note_Item[99]` 只算 99B ✗ ⇒ 实测 Baseline / 含 5 处真实超界的计划 **全部 0 越界** ✗。
# 现改为**真实类型尺寸**：标量查常用表 ✓、类查 `binary_size` ✓、数组再乘维度 ✓。
_SCALAR = {'char': 1, 'unsigned char': 1, '_BYTE': 1, 'BYTE': 1, 'bool': 1, 'short': 2,
           'unsigned short': 2, '_WORD': 2, 'WORD': 2, 'wchar_t': 2, 'int': 4, 'unsigned int': 4,
           'long': 4, 'unsigned long': 4, '_DWORD': 4, 'DWORD': 4, 'float': 4, 'unsigned __int64': 8,
           '__int64': 8, 'double': 8, 'int64': 8}


def _base_and_dims(t):
    """拆出"基础类型 + 维度乘积"（`UIStatic[8][6][5]` ⇒ ('UIStatic', 240) ✓）。"""
    if not isinstance(t, str):
        return None, 1
    m = __import__('re').match(r'^([A-Za-z_]\w*)', t.strip())
    base = m.group(1) if m else None
    return base, _dims(t)


def _size_of(t, sizes):
    """真实尺寸：类 ⇒ binary_size ✓；标量 ⇒ 表 ✓；数组 ⇒ × 维度 ✓；未知 ⇒ None（不猜 ✗）。

    **指针/引用 ⇒ 4/跳过** ✓ —— 若不显式判，`CCBSystem *m_pCBSystem` 会被当成
    `sizeof(CCBSystem)` ⇒ 假报超界（实测 CCBAI 假报 90852 ✗）。这是复核者 7f6a52cd
    明确警告过的"须显式判 `*`/`&`" ✓。
    """
    if not isinstance(t, str):      # 内联 struct/union（type 是 dict）⇒ 跳过（不猜 ✗）
        return None
    tt = t.strip()
    tt = __import__('re').sub(r'^(struct|class|union|enum)\s+', '', tt)   # 剥 `struct ` 前缀 ✓
    if '&' in tt:
        return None                      # 引用成员：不是内嵌对象 ✓ 跳过
    if '*' in tt:
        return 4                         # 指针：4 字节 ✓（32 位目标）
    base, dims = _base_and_dims(tt)
    if base is None:
        return None
    if base in sizes:
        return sizes[base] * dims
    if base in _SCALAR:
        return _SCALAR[base] * dims
    return None


def check(structs, inject=()):
    """返回越界清单；`inject` 为 (类名, offset, 尺寸) 三元组，用于注入式自检 ✓。"""
    # 先建立"类名 ⇒ binary_size"表（真实尺寸解析所需 ✓）
    sizes = {}
    for f in sorted(os.listdir(STRUCTS)) if os.path.isdir(STRUCTS) else []:
        if f.endswith('.json'):
            try:
                d2 = json.load(open(os.path.join(STRUCTS, f), encoding='utf-8'))
                if isinstance(d2.get('binary_size'), int):
                    sizes[d2.get('name') or f[:-5]] = d2['binary_size']
            except Exception:
                pass
    inj = {}
    for cls, off, sz in inject:
        inj.setdefault(cls, []).append((off, sz))
    bad = []
    for f in sorted(os.listdir(STRUCTS)) if os.path.isdir(STRUCTS) else []:
        if not f.endswith('.json'):
            continue
        try:
            d = json.load(open(os.path.join(STRUCTS, f), encoding='utf-8'))
        except Exception:
            continue
        bs = d.get('binary_size')
        if not isinstance(bs, int) or bs <= 0:
            continue
        worst = None
        for k, m in (d.get('known_members') or {}).items():
            off = norm_offset(k)
            if off is None:
                continue
            ty = (m or {}).get('type') if isinstance(m, dict) else None
            sz = _size_of(ty, sizes)
            if sz is None:
                continue          # 未知类型：不猜 ✗（宁可漏报也不假报 ✓）
            end = off + max(sz, 1)
            if worst is None or end > worst[1]:
                worst = (off, end, (m or {}).get('name') if isinstance(m, dict) else None)
        for off, sz in inj.get(d.get('name'), []):
            end = off + sz
            if worst is None or end > worst[1]:
                worst = (off, end, '<injected>')
        if worst and worst[1] > bs:
            bad.append({'class': d.get('name'), 'binary_size': bs,
                        'member_end': worst[1], 'offset': worst[0], 'member': worst[2]})
    return bad


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    known = {'--self-test', '--json'}
    unk = [a for a in argv if a.startswith('-') and a.split('=')[0] not in known]
    if unk:
        print('[check_member_extent] 未知开关 %r ⇒ 不执行任何操作' % unk)
        return 0
    ap = argparse.ArgumentParser()
    ap.add_argument('--self-test', action='store_true', help='注入一个越界成员，验证本闸能失败')
    ap.add_argument('--json', action='store_true')
    a = ap.parse_args(argv)
    if not os.path.isdir(STRUCTS):
        print('[ERROR] 缺注解目录: %s' % STRUCTS, file=sys.stderr)
        return 2
    inject = ()
    if a.self_test:
        # 注入：给第一个有 binary_size 的类塞一个远超前界的成员（只在内存里 ✓）
        for f in sorted(os.listdir(STRUCTS)):
            if f.endswith('.json'):
                d = json.load(open(os.path.join(STRUCTS, f), encoding='utf-8'))
                if isinstance(d.get('binary_size'), int) and d['binary_size'] > 0:
                    inject = ((d.get('name'), d['binary_size'] + 64, 4),)
                    print('[self-test] 已对 %s 注入一个越界成员（+%d）' % (d.get('name'), d['binary_size'] + 64))
                    break
    bad = check(None, inject)
    if a.json:
        print(json.dumps(bad, ensure_ascii=False, indent=1))
    else:
        print('成员末端 < binary_size 的检查：越界 %d 个' % len(bad))
        for b in bad[:8]:
            print('   ✗ %s: binary_size=%d 但成员末端=%d（%s@%s）'
                  % (b['class'], b['binary_size'], b['member_end'], b['member'], b['offset']))
        if not bad:
            print('   ✅ 无不变量破坏')
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
