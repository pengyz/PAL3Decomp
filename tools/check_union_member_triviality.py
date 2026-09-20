#!/usr/bin/env python3
"""union 按值成员的"平凡性"门禁（2026-09-20 B34 事故后新增）。

# 拦的是什么

**B34 事故**（真实发生）：给 `tagRoleSlot` 加了一个方法并把名字写成**类名本身**（⇒ codegen 发成
**构造函数声明** `tagRoleSlot();`）⇒ `tagRoleSlot` 从 **trivial** 变成 **non-trivial**；
而它是 `PalScript` 里一个 `union { tagRoleSlot slot; ... }` 的**按值成员** ⇒
`C2620 union '__unnamed' : member 'slot' has user-defined constructor or non-trivial default constructor`
**在每一个包含 globals.h 的 TU 里各报一次**（208 个单元 ⇒ S2 ok 76→0）。dtor 单独存在则报 **C2623**。

**独立复核的隔离编译实验（仓内 MSVC6 SP0）**结论：
* 平凡成员 → 通过
* 只加 **ctor**（名字 = 类名）→ **C2620**（消息逐字一致）
* 只加 **dtor**（`~类名`）→ **C2623**
* ctor + dtor → 只报 C2620（C2623 被抑制）
* 只加**普通成员函数**（名字 ≠ 类名）→ 通过
⇒ 充分触发条件是"**类有 ctor/dtor**"，而与"方法属于哪个类"无关。

# 判据

对每个注解结构体：若它被**按值**用作某个 `union` 的成员类型（含 inline union 语法
`"type": {"union": [ {"type": "T", ...}, ... ]}`），则 **T 不得有 ctor/dtor 形态的方法**：
* 方法名 == `T`（构造函数）
* 方法名 == `~T`（析构函数）

# 用法

    python3 tools/check_union_member_triviality.py          # 报告 + 退出码
    python3 tools/check_union_member_triviality.py --self-test   # 注入式自检（证明它能失败）
退出码：0 = 无 landmine；1 = 检出 landmine；2 = 前置缺失。
"""
import argparse
import glob
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations', 'structs')


def _load_all():
    out = {}
    for f in glob.glob(os.path.join(ANN, '*.json')):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        nm = d.get('name') or os.path.basename(f)[:-5]
        out[nm] = d
    return out


def _union_variant_types(structs):
    """收集"被按值用作 union 成员"的类型名 → [(union 所属类, 成员名/偏移, 字段名)]"""
    used = {}
    for cls, d in structs.items():
        for off, m in (d.get('known_members') or {}).items():
            if not isinstance(m, dict):
                continue
            t = m.get('type')
            variants = []
            if isinstance(t, dict) and isinstance(t.get('union'), list):
                variants = t['union']
            elif isinstance(t, str) and t in structs and isinstance(
                    (structs[t].get('type') or None), dict):
                u = structs[t].get('type') or {}
                if isinstance(u.get('union'), list):
                    variants = u['union']
            for v in variants:
                if not isinstance(v, dict):
                    continue
                vt = v.get('type')
                # 只取**按值**的类类型：排除指针/基础类型/内联 struct
                if isinstance(vt, str) and vt in structs and not vt.endswith('*'):
                    used.setdefault(vt, []).append((cls, off, m.get('name')))
    return used


def _ctor_dtor_names(cls, d):
    hits = []
    for a, v in (d.get('methods') or {}).items():
        nm = (v or {}).get('name') or ''
        if nm == cls or nm == ('~' + cls):
            hits.append((a, nm, (v or {}).get('signature')))
    return hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--self-test', action='store_true',
                    help='注入一个 B34 式 landmine 到内存副本，验证本检查能报错')
    args = ap.parse_args()

    if not os.path.isdir(ANN):
        print('[ERROR] 缺注解目录: %s' % ANN, file=sys.stderr)
        return 2
    structs = _load_all()
    used = _union_variant_types(structs)

    if args.self_test:
        # 注入：给第一个 union 按值成员类加一个"名字 = 类名"的方法（只在内存里）
        if not used:
            print('[self-test] 当前语料里找不到 union 按值成员类 ⇒ 无法注入', file=sys.stderr)
            return 2
        victim = sorted(used)[0]
        structs[victim].setdefault('methods', {})['0xDEADBEEF'] = {
            'name': victim, 'signature': 'void __thiscall %s::%s()' % (victim, victim)}
        print('[self-test] 已给 %s 注入方法 %s()（模拟 B34 的 ctor 命名）' % (victim, victim))

    landmines = []
    for cls in sorted(used):
        d = structs.get(cls)
        if not d:
            continue
        for a, nm, sig in _ctor_dtor_names(cls, d):
            landmines.append((cls, a, nm, sig, used[cls][:2]))

    print('union 按值成员类型共 %d 个：%s' % (len(used), ', '.join(sorted(used)) or '(无)'))
    print('检查：这些类不得有 ctor/dtor 形态的方法（方法名 == 类名 或 ~类名）')
    if not landmines:
        print('\n✅ 无 landmine：没有 union 按值成员类带 ctor/dtor')
        return 0
    print('\n❌ 检出 landmine %d 处：' % len(landmines))
    for cls, a, nm, sig, spots in landmines:
        print('   %s 的方法 %s = %r  (signature=%s)' % (cls, a, nm, sig))
        print('      该类型被按值用作 union 成员：%s' % (spots,))
        print('      ⇒ 会触发 C2620（ctor）/ C2623（dtor），并在**每个包含它的 TU** 里各报一次')
    print('\n处置：给该类型改名（不得用类名/析构名），或把 union 里的该视图降级为扁平视图。')
    return 1


if __name__ == '__main__':
    sys.exit(main())
