"""asm_diff — 单函数三态指令对齐视图（spec v2 §1.3·oot asm-differ 借鉴·自建 PE 版）。

定位：fdiff.py=并排 hex+disasm；byte_diff_explain.py=批量首分歧根因直方图——
本件补中间层：**单函数全序列三态对齐**（= 相等 / < 原独有 / > 我方独有）+
首分歧高亮。复用纪律（TOS 单源·禁复制）：disasm/key/classify 全部
import 自 byte_diff_explain——align 只是编排其 SequenceMatcher 逻辑。
对齐语义与 byte_diff_explain 同（base=0 双侧反汇编防分支目标假阳性）。
"""
import difflib
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))  # 包内平导（同 ghidra_track 惯例）
from byte_diff_explain import classify, disasm, key  # noqa: E402,F401 （复用断言钉）


def align_disasm(A, B):
    """指令元组列 A(原)/B(我方) → 三态对齐列 [{tag, orig, ours, cls}]。"""
    sm = difflib.SequenceMatcher(a=[key(x) for x in A], b=[key(x) for x in B],
                                 autojunk=False)
    pairs = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            for k in range(i2 - i1):
                pairs.append({'tag': '=', 'orig': A[i1 + k], 'ours': B[j1 + k],
                              'cls': None})
        else:
            n = max(i2 - i1, j2 - j1)
            for k in range(n):
                a = A[i1 + k] if i1 + k < i2 else None
                b = B[j1 + k] if j1 + k < j2 else None
                st = '=' if (a and b and key(a) == key(b)) else ('<' if b is None else ('>' if a is None else '~'))
                pairs.append({'tag': st, 'orig': a, 'ours': b,
                              'cls': (classify(b, a) if a and b and st == '~' else None)})
    return pairs


def first_divergence(pairs):
    """首个非 '=' 对 → {idx, cls, orig, ours}（无→None）。"""
    for i, p in enumerate(pairs):
        if p['tag'] != '=':
            return {'idx': i, 'cls': p['cls'], 'orig': p['orig'], 'ours': p['ours']}
    return None


def render(pairs, va=''):
    """三态列渲染（首分歧 '>>>' 高亮·'=' 行可省略显示但保留计数）。"""
    fd = first_divergence(pairs)
    lines = []
    n_eq = sum(1 for p in pairs if p['tag'] == '=')
    lines.append('== asm_diff %s | instrs: orig=%d ours=%d equal=%d ==' % (
        va, sum(1 for p in pairs if p['orig']), sum(1 for p in pairs if p['ours']), n_eq))
    for i, p in enumerate(pairs):
        mark = '>>>' if (fd and fd['idx'] == i) else '   '
        a = '%s %s' % (p['orig'][1], p['orig'][2]) if p['orig'] else '-'
        b = '%s %s' % (p['ours'][1], p['ours'][2]) if p['ours'] else '-'
        if p['tag'] == '=' and not (fd and fd['idx'] == i):
            lines.append('%s %-44s | %s' % (mark, a, b))
        else:
            cls = ('  [%s]' % p['cls']) if p.get('cls') else ''
            lines.append('%s %s %-44s | %s%s' % (mark, p['tag'], a, b, cls))
    return '\n'.join(lines)


def main(argv):
    import argparse
    import json
    import os
    from first_diff import find_row, norm_va
    ap = argparse.ArgumentParser(description='单函数三态指令对齐（复用 fdiff/byte_diff_explain 数据链）')
    ap.add_argument('va')
    ap.add_argument('--detail', default='data/status/s4_diff_detail.json')
    a = ap.parse_args(argv)
    detail = json.load(open(a.detail))
    row = find_row(detail, a.va)
    if row is None:
        print('MISS: %s 不在 detail（L1/未比对行无此面）' % a.va)
        return 1
    obj = row.get('obj')
    if not obj or not os.path.exists(obj):
        print('obj 已清（probe rmtree）→ 重算须重跑 probe（match hypothesis flags·'
              '禁缺省 PROBE_FLAGS）；存储账见 first_diff.py %s' % a.va)
        return 2
    # 数据链复用 byte_diff_explain 同源（load_text + parse_coff_obj）
    import gbengine_compare as gc
    from byte_diff_explain import load_text
    image_base, text_rva, text, _ = load_text()
    funcs = gc.parse_coff_obj(obj)
    info = funcs.get(row['symbol'])
    if info is None:
        print('symbol %s 不在 obj %s' % (row['symbol'], obj))
        return 1
    size = row['size']
    va = norm_va(row['va'])
    idx0 = va - image_base - text_rva
    orig = text[idx0:idx0 + size]
    comp = info['bytes']
    relocs = set(info.get('relocs') or ())
    A = disasm(orig, 0)
    B = disasm(comp, 0, relocs)
    print(render(align_disasm(A, B), va=row['va']))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
