#!/usr/bin/env python3
"""审计注解里 offset0 声明的 `__vftable`：**它到底是不是 vfptr**。

# 为什么需要

`pipeline/ida/apply_annotations.py:431` 对 `offset == 0 and name in ("__vftable","vfptr")`
有特判：把它建成"带类型的 vtable 指针"，其结果**不进 `data_members`**（只在 `_variants`），
于是头生成器（只读 `data_members`）**从不发射该成员** ⇒ 所有 `X.__vftable` / `X::__vftable`
访问都报"不是成员"。实测这一族占 C2039 的绝大多数。

**改名成别的名字 ⇒ 就是普通成员 ⇒ 被发射**（试点：SceneObj 链 4 个碎片，总错误 −216、L1 +1）。

**但不能一刀切**：全库 118 个这样的声明里，只有一部分 offset0 真的是 vfptr。
对有 vtable 的类，那条特判是**正确**的，改了反而破坏。

# 判据（只用独立于"注解怎么命名"的证据）

| 信号 | 含义 |
|---|---|
| `ctor_disp0` | 该类**注解 ctor**（或安装其主表的函数）里是否有 **位移 0** 的 vtable 安装 ⇒ 有则 offset0 真是 vfptr |
| `polymorphic` | 该类是否有 `vtables` 注解 / 有被注解的方法 / 在 `struct_vtables` 里有槽表 |
| `objptr_casts` | decomp 里 `(X *)C::__vftable` 形态的次数 ⇒ 被当**对象指针**用 ⇒ 是数据 |
| `member_through` | `C::__vftable->M` 次数 ⇒ 经它取成员（两者皆可能） |
| `stores` | `C::__vftable = …` 的次数；若 RHS 是 vtable 符号 ⇒ vfptr，否则数据 |
| `src` | 注解里的 `source` 字段（**最后参考**，见知识库条目） |

结论：**VFPTR**（有安装点 / 多态且无对象指针用法）｜**DATA_PTR**（有对象指针用法且无安装点）｜
**UNKNOWN**（证据不足，需人工 IDB 分析）。

用法：
    python3 tools/audit_vftable_offset0.py                 # 报告
    python3 tools/audit_vftable_offset0.py --json out.json # 导出
"""
import argparse
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations', 'structs')
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
ASM = os.path.join(ROOT, 'original', 'PAL3.exe.asm')

sys.path.insert(0, os.path.join(ROOT, 'tools'))
import importlib.util
_spec = importlib.util.spec_from_file_location('mi', os.path.join(ROOT, 'tools', 'mi_base_offsets.py'))
_mi = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_mi)


def load_decomp_texts():
    """{文件名: 反编译文本}，只读一次。"""
    out = {}
    for f in sorted(glob.glob(os.path.join(DECOMP, '*.json'))):
        try:
            out[f] = json.load(open(f, encoding='utf-8')).get('decompiled_c') or ''
        except Exception:
            continue
    return out


def audit_one(cls, ann, asm, texts, cache):
    """返回该类的证据字典与结论。"""
    ev = {'class': cls}
    e0 = (ann.get('known_members') or {}).get('0') or {}
    ev['src'] = e0.get('source')
    ev['type'] = e0.get('type')

    # --- 多态性 ---
    ev['n_methods'] = len(ann.get('methods') or {})
    ev['n_vtables'] = len([v for v in (ann.get('vtables') or []) if v.get('addr')])
    ev['polymorphic'] = bool(ev['n_vtables'] or ev['n_methods'])

    # --- 安装点：注解 ctor，或安装"主表"的那个函数 ---
    disp0 = False
    ctor = next((int(a, 16) for a, v in (ann.get('methods') or {}).items()
                 if v.get('name') == cls), None)
    cands = []
    if ctor is not None:
        cands.append('sub_%X' % ctor)
    vts = [int(v['addr'], 16) for v in (ann.get('vtables') or []) if v.get('addr')]
    for vt in vts[:1]:
        key = 'off_%X' % vt
        for lab in asm.spans:
            if key in asm.seg(lab):
                cands.append(lab)
                break
    for lab in cands:
        s = asm.installs(lab) or []
        if 0 in s:
            disp0 = True
            break
    ev['ctor_disp0'] = disp0
    ev['install_funcs'] = cands[:2]

    # --- 用法统计（decomp） ---
    cast_pat = re.compile(r'\(\s*([A-Za-z_]\w*)\s*\*\s*\)\s*[\w\.\->:]*\b%s::__vftable\b' % re.escape(cls))
    through_pat = re.compile(r'\b%s::__vftable\s*->\s*\w+' % re.escape(cls))
    store_pat = re.compile(r'\b%s::__vftable\s*=\s*([^;]{0,60})' % re.escape(cls))
    arith_pat = re.compile(r'[&*]?\s*\b%s::__vftable\b\s*[+\-]' % re.escape(cls))
    casts = {}
    n_through = n_store = n_arith = 0
    store_rhs = []
    total = 0
    for txt in texts.values():
        if cls not in txt:
            continue
        total += txt.count('%s::__vftable' % cls)
        for m in cast_pat.finditer(txt):
            casts[m.group(1)] = casts.get(m.group(1), 0) + 1
        n_through += len(through_pat.findall(txt))
        for m in store_pat.finditer(txt):
            n_store += 1
            if len(store_rhs) < 4:
                store_rhs.append(m.group(1).strip()[:40])
        n_arith += len(arith_pat.findall(txt))
    ev.update({'refs': total, 'objptr_casts': casts, 'n_through': n_through,
               'n_store': n_store, 'store_rhs': store_rhs, 'n_arith': n_arith})

    # --- 结论（**只有拿到位移 0 的安装点才算 VFPTR**；"多态"不作为充分条件） ---
    n_objcast = sum(casts.values())
    if disp0:
        verdict = 'VFPTR'
    elif n_objcast > 0 or n_arith > 0 or (total > 0 and n_through == 0 and n_store == 0):
        verdict = 'DATA_PTR'
    else:
        verdict = 'UNKNOWN'
    ev['verdict'] = verdict
    return ev


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--json', help='导出到该路径')
    args = ap.parse_args()

    asm = _mi.Asm()
    texts = load_decomp_texts()
    rows = []
    for f in sorted(glob.glob(os.path.join(ANN, '*.json'))):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        cls = d.get('name') or os.path.basename(f)[:-5]
        e0 = (d.get('known_members') or {}).get('0') or {}
        if e0.get('name') != '__vftable':
            continue
        rows.append(audit_one(cls, d, asm, texts, {}))

    by = {}
    for r in rows:
        by.setdefault(r['verdict'], []).append(r)

    print('=' * 96)
    print('注解 offset0 `__vftable` 审计（独立证据；注解的 source 只作最后参考）')
    print('=' * 96)
    print('共 %d 个类：VFPTR(=保持) %d ｜ DATA_PTR(建议改名) %d ｜ UNKNOWN(需人工) %d'
          % (len(rows), len(by.get('VFPTR', [])), len(by.get('DATA_PTR', [])),
             len(by.get('UNKNOWN', []))))
    print()
    for v in ('DATA_PTR', 'UNKNOWN', 'VFPTR'):
        rs = by.get(v) or []
        if not rs:
            continue
        print('【%s】%d 个类' % (v, len(rs)))
        print('   %-34s %-8s %-5s %-6s %-6s %-6s %s' % ('类', 'src', '多态', '引用', '对象指针强转', '安装0', '例子'))
        for r in sorted(rs, key=lambda x: -sum(x['objptr_casts'].values())):
            ex = ', '.join('%s*%d' % (k, n) for k, n in
                           sorted(r['objptr_casts'].items(), key=lambda kv: -kv[1])[:2])
            print('   %-34s %-8s %-5s %-6d %-6d %-6s %s' % (
                r['class'][:34], str(r['src'])[:8], 'Y' if r['polymorphic'] else 'n',
                r['refs'], sum(r['objptr_casts'].values()),
                'Y' if r['ctor_disp0'] else 'n', ex))
        print()

    if args.json:
        json.dump(rows, open(args.json, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        print('结果 -> %s' % args.json)


if __name__ == '__main__':
    main()