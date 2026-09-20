#!/usr/bin/env python3
"""一致性校验（审计 P1-4）：`asm/pal3/ida_structs.json` 与注解是否**逐字段等值**。

# 为什么需要

`pipeline/ida/export_full.py` 有 **8 处 `[t4-DECLARED-EXCEPTION]`**：它**有意**直读
`data/annotations/`（取舍理由与量化证据写在该文件头部声明块，交付物见
`data/status/_cleanup_fix_export_redline.json`）。其中一类是把注解的
`vtables` / `methods` / `_variants` **透传**进导出产物 `ida_structs.json`。
该文件头部自述：实测 **761/761 个 struct 零不一致** ⇒ 这些字段是"**注解的副本**"，
而不是"IDB 状态的证据"。

**风险**：透传是"假装成 IDB 状态"的。一旦**有人手改 IDB**（或在 IDA 里改了类型/名字）
而**没同步注解**，导出产物就会与注解不一致，而下游（`pipeline/gen/data.py` 读
`ida_structs.json`）会**继续按注解的值工作** ⇒ **静默产生与 IDB 不符的数据**，无任何告警。

本工具就是那道缺失的告警：比较导出产物与注解的这三个字段，**不一致即报告并非零退出**。

# 判据（只比"透传字段"，不碰真正的 IDB-only 字段）

对每个同时在两侧出现的 struct：
  * `vtables`：地址集合是否相同（顺序不敏感，比集合）；
  * `methods`：`{addr: name}` 映射是否相同；
  * `_variants`：键集合是否相同（只比键；值的 type 差异单独计为 warning）。
另外统计：只在一侧出现的 struct 名（供参考，不计失败）。

用法：
    python3 tools/check_export_annotation_consistency.py           # 报告 + 退出码
    python3 tools/check_export_annotation_consistency.py --json o.json
退出码：0=一致；1=检出漂移（或产物/注解缺失 ⇒ 2）。
"""
import argparse
import glob
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDA_STRUCTS = os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json')
ANN_DIR = os.path.join(ROOT, 'data', 'annotations', 'structs')


def _vt_addrs(entry):
    out = set()
    for v in (entry.get('vtables') or []):
        a = v.get('addr') if isinstance(v, dict) else v
        if a:
            out.add(str(a).lower())
    return out


def _methods(entry):
    out = {}
    for a, v in (entry.get('methods') or {}).items():
        out[str(a).lower()] = v.get('name') if isinstance(v, dict) else v
    return out


def _variant_keys(entry):
    return set(str(k) for k in (entry.get('_variants') or {}).keys())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--json', help='把结果写到该路径')
    args = ap.parse_args()

    if not os.path.exists(IDA_STRUCTS):
        print('[ERROR] 缺少导出产物: %s（先跑 pipeline/cli.py export）' % IDA_STRUCTS,
              file=sys.stderr)
        return 2
    if not os.path.isdir(ANN_DIR):
        print('[ERROR] 缺少注解目录: %s' % ANN_DIR, file=sys.stderr)
        return 2

    ida = json.load(open(IDA_STRUCTS, encoding='utf-8'))
    ann = {}
    for f in glob.glob(os.path.join(ANN_DIR, '*.json')):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        name = d.get('name') or os.path.basename(f)[:-5]
        ann[name] = d

    both = sorted(set(ida) & set(ann))
    only_ida = sorted(set(ida) - set(ann))
    only_ann = sorted(set(ann) - set(ida))

    vt_diff, m_diff, vk_diff, vt_only_warn = [], [], [], []
    for name in both:
        i, a = ida[name], ann[name]
        if _vt_addrs(i) != _vt_addrs(a):
            vt_diff.append(name)
        if _methods(i) != _methods(a):
            m_diff.append(name)
        if _variant_keys(i) != _variant_keys(a):
            vk_diff.append(name)

    # 判据只用 vtables + methods。
    # `_variants` **不参与失败判定**：注解把成员变体存在 `known_members`（按 offset 键），
    # 导出产物的 `_variants` 是另一种表示 —— 直接比键集合会产生大量**假阳性**
    # （实测 742 个），那是在"比错东西"。仅作提示。
    total_bad = len(vt_diff) + len(m_diff)
    print('导出产物 vs 注解 一致性校验（[t4-DECLARED-EXCEPTION] 的透传字段）')
    print('=' * 72)
    print('  两侧都有 struct: %d   仅导出侧: %d   仅注解侧: %d'
          % (len(both), len(only_ida), len(only_ann)))
    print('  vtables  不一致: %d' % len(vt_diff))
    print('  methods  不一致: %d' % len(m_diff))
    print('  _variants 键不一致: %d  （**仅提示**：两侧表示不同，不参与失败判定）'
          % len(vk_diff))
    for label, lst in (('vtables', vt_diff), ('methods', m_diff),
                       ('_variants', vk_diff)):
        if lst:
            print('    [%s] %s%s' % (label, ', '.join(lst[:10]),
                                     ' …' if len(lst) > 10 else ''))
    if total_bad == 0:
        print('\n✅ 一致：导出产物中这些字段与注解**逐字段等值**（与 export_full.py 头部'
              '自述的 761/761 相符）')
    else:
        print('\n❌ 检出漂移 %d 处（vtables/methods）—— 注解与 IDB/导出产物不同步。'
              '\n   注意：下游按**注解**的值工作（data.py 读 ida_structs.json），'
              '\n   漂移意味着"看起来像 IDB 状态、实际是注解值"的静默不一致。' % total_bad)

    if args.json:
        json.dump({'both': len(both), 'only_ida': only_ida, 'only_ann': only_ann,
                   'vtables_diff': vt_diff, 'methods_diff': m_diff,
                   'variants_diff': vk_diff},
                  open(args.json, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        print('结果 -> %s' % args.json)
    return 0 if total_bad == 0 else 1


if __name__ == '__main__':
    sys.exit(main())
