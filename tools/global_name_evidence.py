"""G8 命名清扫·角色证据谱（真·可变 214 自动名 → 逐条 xref 角色证据）。
只读分析：python tools/global_name_evidence.py
输出：可命名候选（角色清晰）/ 留 _todo_（无据）——禁伪语义命名（无据不名）。
"""
import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    from tools.member_existence_gate import build_xref_index
    from tools.type_evidence import exe_text_image
    xref = build_xref_index()
    data, va2off, sections = exe_text_image()
    rep = json.load(open(os.path.join(ROOT, 'data', 'status', 'global_reality_report.json'),
                         encoding='utf-8'))
    g = json.load(open(os.path.join(ROOT, 'data', 'annotations', 'globals.json'), encoding='utf-8'))
    items = g.get('globals') or g
    rows = [r for r in rep['rows'] if r['cls'] == '真·可变全局（游戏状态）']
    auto = [r for r in rows if not (r['name'] or '').startswith('g_')]
    print('真·可变 %d · 其中自动名 %d（命名清扫面）' % (len(rows), len(auto)))
    sigs = collections.Counter()
    named_candidates = []
    for r in auto:
        va = int(r['va'], 16)
        sites = xref.get(va, [])
        shapes = collections.Counter(s for _, _, s in sites)
        # 角色谱系：写读比 + 形态组合
        w = shapes.get('mov_store', 0) + shapes.get('mov_imm', 0) + shapes.get('fpu', 0)
        rd = shapes.get('mov_load', 0) + shapes.get('cmp', 0) + shapes.get('push_arg', 0)
        role = ('计数/累加' if shapes.get('mov_imm') and w > rd else
                '浮点状态' if shapes.get('fpu') else
                '标志/开关' if shapes.get('cmp') and not shapes.get('fpu') else
                '句柄/指针' if shapes.get('mov_store') and shapes.get('mov_load') and not shapes.get('fpu') else
                '数据面')
        sigs[role] += 1
        named_candidates.append((r['va'], r['name'], r['type'], role, len(sites), dict(shapes)))
    print('\n角色谱系:')
    for k, v in sigs.most_common():
        print('   %-10s %d' % (k, v))
    print('\n样例（每角色 3）:')
    seen = collections.Counter()
    for va, nm, ty, role, ns, sh in named_candidates:
        if seen[role] < 3:
            print('   %s %-22s %-12s %-8s sites=%d %s' % (va, nm or '(无名)', str(ty)[:12], role, ns, sh))
            seen[role] += 1
    out = os.path.join(ROOT, 'data', 'status', 'global_name_evidence.json')
    json.dump({'rows': [{'va': v, 'name': n, 'type': t, 'role': r, 'sites': s, 'shapes': sh}
                        for v, n, t, r, s, sh in named_candidates]},
              open(out, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('\n报告 -> %s' % out)
    return 0


if __name__ == '__main__':
    sys.exit(main())
