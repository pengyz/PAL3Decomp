#!/usr/bin/env python3
"""ROI-1（2026-09-19）：把 `data/status/s4_diff_detail.json` 里的字节差异**解释成人能读的原因**。

背景：`pipeline/compare_pal3.py` 过去把 `compare_bytes()` 算出的差异偏移全部丢掉，只留
`match_pct` ⇒ 173 个 partial 没有任何可排序的"为什么不是 L1"。本工具读取新产出的
`s4_diff_detail.json`（含每个 partial 的 `diffs`/`obj`/`va`/`size`），用 capstone 双侧反汇编、
按指令对齐后给出**首个分歧点**与原因分类，汇总成 `data/status/s4_diff_explain.json`。

只读输入，只写一个新文件；不改 ratchet 产物。
"""
import json
import os
import re
import struct
import sys
import collections
import difflib
from pathlib import Path


# ---- 2026-09-20 审计 P2-4：无参数解析工具的统一护栏 ----------------------------
# 本工具**会写盘**且**没有任何 argparse/sys.argv 处理** ⇒ 传任何 `-` 开头的参数
# （最典型的是 `--help`）此前会被当作普通输入，**执行全流程并覆盖产物**。
# 本次审计期间已因此发生 **2 起事故**（`sig_evidence.py` 删掉 6020 行、
# `misattribution_ledger.py` 把 197 cluster 改写成 3）。
# 统一护栏：见到任何以 `-` 开头的参数即打印用法并**退出，不执行任何工作**。
import sys as _sys_guard
if any(_a.startswith('-') for _a in _sys_guard.argv[1:]):
    print('[%s] 本工具不接受命令行开关；收到 %r ⇒ 不执行任何操作。'
          % (__file__.rsplit('/', 1)[-1], _sys_guard.argv[1:]))
    print('用法: python3 %s    # 无参数，直接运行' % __file__)
    _sys_guard.exit(0)
# ---------------------------------------------------------------------------

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / 'pipeline'))
sys.path.insert(0, str(REPO / 'tools'))
import capstone  # noqa: E402
import gbengine_compare as gc  # noqa: E402

DETAIL = REPO / 'data' / 'status' / 's4_diff_detail.json'
OUT = REPO / 'data' / 'status' / 's4_diff_explain.json'
EXE = REPO / 'original' / 'PAL3.exe'


def load_text():
    """(image_base, text_rva, text_raw, text_raw_size) —— 最小 PE 解析。"""
    data = EXE.read_bytes()
    pe = struct.unpack_from('<I', data, 0x3C)[0]
    nsec = struct.unpack_from('<H', data, pe + 6)[0]
    opt = pe + 24
    image_base = struct.unpack_from('<I', data, opt + 28)[0]
    sec = opt + struct.unpack_from('<H', data, pe + 20)[0]
    for i in range(nsec):
        o = sec + i * 40
        name = data[o:o + 8].rstrip(b'\0')
        va = struct.unpack_from('<I', data, o + 12)[0]
        raw_size = struct.unpack_from('<I', data, o + 16)[0]
        raw = struct.unpack_from('<I', data, o + 20)[0]
        if name == b'.text':
            return image_base, va, data[raw:raw + raw_size], raw_size
    raise SystemExit('no .text')


def disasm(code, base, relocs=()):
    """反汇编成 [(addr, mnemonic, op_str, size)]；重定位字节所在指令的操作数归一为 {R}。"""
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = False
    out = []
    for ins in md.disasm(code, base):
        op = ins.op_str
        if relocs and any(ins.address <= r < ins.address + ins.size for r in relocs):
            op = '{R}'
        out.append((ins.address, ins.mnemonic, op, ins.size))
    return out


def key(i):
    return (i[1] + ' {T}') if (i[1] in ('call', 'jmp') and '[' not in i[2]) else ('%s %s' % (i[1], i[2]))


def classify(a, b):
    """a/b 为同位置的指令元组（可能 None=缺失）。"""
    if a is None:
        return 'extra-instr (我们有，原函数没有)'
    if b is None:
        return 'missing-instr (原函数有，我们缺)'
    ma, mb = a[1], b[1]
    oa, ob = a[2], b[2]
    if ma != mb:
        return ('cond-jump signedness differs (annotation type)' if (ma in ('jl','jle','jg','jge','jb','jbe','ja','jae') and mb in ('jl','jle','jg','jge','jb','jbe','ja','jae')) else 'opcode/flow differs')
    if oa == ob:
        return 'same-text (仅字节级差异/编码不同)'
    # 同助记符：看操作数差异类型
    da = re.findall(r'0x[0-9a-fA-F]+|[-+]?\d+', oa)
    db = re.findall(r'0x[0-9a-fA-F]+|[-+]?\d+', ob)
    ra = re.findall(r'\b(?:e?[abcd]x|e?[sd]i|e?[sb]p|eip|st\d?|xmm\d)\b', oa)
    rb = re.findall(r'\b(?:e?[abcd]x|e?[sd]i|e?[sb]p|eip|st\d?|xmm\d)\b', ob)
    if len(da) == len(db) and any('[' in s for s in (oa, ob)):
        # F46：内存操作数里"基址寄存器不同"是一类独立缺陷（this 落在别的寄存器，
        # 例如原函数 `[ecx+0x3c]` vs 我们 `[eax+0x3c]`）—— 与"位移值不同"不是一回事，
        # 分开计数才能量出各自的爆炸半径。
        _ba = re.findall(r'\[(e?[abcd]x|e?[sd]i|e?[sb]p)', oa)
        _bb = re.findall(r'\[(e?[abcd]x|e?[sd]i|e?[sb]p)', ob)
        if _ba and _bb and _ba[0] != _bb[0]:
            return 'this-register differs (this in a different reg)'
        return 'this/member disp differs'
    if da and db and da != db:
        return 'immediate/const differs'
    if ra != rb:
        return 'register choice differs'
    return 'operand shape differs'


def main():
    d = json.load(open(DETAIL, encoding='utf-8'))
    image_base, text_rva, text, _ = load_text()
    hist = collections.Counter()
    fps = []
    cache = {}
    for unit, rows in d['units'].items():
        for r in rows:
            obj = r.get('obj')
            if not obj or not os.path.exists(obj):
                hist['(obj missing)'] += 1
                continue
            if obj not in cache:
                try:
                    cache[obj] = gc.parse_coff_obj(obj)
                except Exception:
                    cache[obj] = {}
            funcs = cache[obj]
            info = funcs.get(r['symbol'])
            if info is None:
                hist['(symbol missing in obj)'] += 1
                continue
            size = r['size']
            va = int(r['va'], 16)
            idx0 = va - image_base - text_rva
            orig = text[idx0:idx0 + size]
            comp = info['bytes']
            relocs = {x for x in info.get('relocs', [])}
            # 两侧都用 **base=0** 反汇编：否则分支/调用目标会渲染成不同基址下的绝对值，
            # 指令文本永远不相等 ⇒ 首批"分歧点"里会混进大量假阳性（实测 FindInOpen 就是）。
            # 显示地址时再加回 va（只影响展示，不影响比较）。
            A = disasm(orig, 0)
            B = disasm(comp, 0, relocs)
            sm = difflib.SequenceMatcher(a=[key(x) for x in A], b=[key(x) for x in B], autojunk=False)
            op = sm.get_opcodes()
            cause = None
            site = None
            for tag, i1, i2, j1, j2 in op:
                if tag == 'equal':
                    continue
                a = A[i1] if i1 < len(A) else None
                b = B[j1] if j1 < len(B) else None
                cause = classify(b, a)          # a=原函数, b=我们
                site = {'orig_addr': hex(a[0] + va) if a else None,
                        'orig': ('%s %s' % (a[1], a[2])).strip() if a else None,
                        'ours_addr': hex(b[0]) if b else None,
                        'ours': ('%s %s' % (b[1], b[2])).strip() if b else None,
                        'tag': tag}
                break
            if cause is None:
                cause = '(instruction-aligned, only encoding differs)'
            # F21（2026-09-19）：调整器 thunk —— 原函数形态是 `add ecx, <imm>` 紧跟 `jmp/call`
            # （C++ 多继承/子对象调整的编译器产物）。我们当前不发这条 `add ecx,N`，
            # 所以这类函数永远不可能 L1。单列一类以便量爆炸半径。
            if len(A) >= 2 and A[0][1] == 'add' and 'ecx' in A[0][2] \
                    and A[1][1] in ('jmp', 'call'):
                cause = 'adjustor-thunk (add ecx,%s before tail jump)' % \
                        A[0][2].split(',')[-1].strip()
                _adj = True
            else:
                _adj = False
            hist[cause] += 1
            fps.append({'file': unit, 'name': r['name'], 'va': r['va'], 'size': size,
                        'n_diff': r['n_diff'], 'first_diff': r['first_diff'],
                        'compiled_len': r['compiled_len'], 'cause': cause,
                        'adjustor_thunk': _adj, 'site': site})
    fps.sort(key=lambda x: (x['n_diff'], x['name']))
    OUT.write_text(json.dumps(
        {'generated_by': 'tools/byte_diff_explain.py', 'partials': len(fps),
         'cause_histogram': dict(hist.most_common()), 'functions': fps},
        indent=1, ensure_ascii=False))
    print('partials explained: %d' % len(fps))
    print('%-42s %s' % ('cause', 'count'))
    for k, v in hist.most_common():
        print('%-42s %d' % (k, v))
    print()
    print('lowest-residual partials (n_diff asc):')
    for x in fps[:15]:
        s = x['site'] or {}
        print('  %-38s n_diff=%-4s (%s/%s B) %-30s | orig: %-26s ours: %s'
              % (x['name'][:38], x['n_diff'], x['compiled_len'], x['size'],
                 x['cause'][:30], (s.get('orig') or '-')[:26], (s.get('ours') or '-')[:26]))
    print('\n-> %s' % OUT)


if __name__ == '__main__':
    main()
