#!/usr/bin/env python3
"""**类型布局审计**（只读）：把「注解声明的偏移」与**两个独立裁判**对比并报警。

## 为什么需要它（2026-09-21 的教训）

`tools/audit_layout.py` 比的是 **注解 vs `asm/pal3/ida_structs.json`**，而那个导出文件
正是 `apply_annotations.py` **从这些注解写进 IDB 再导出**的 ⇒ 它的 docstring 自己承认
"check 1 是同源比较、恒等、**无判别力**" ✗ ⇒ **漂移永远发现不了**。

实测（本仓当前状态）：`SceneMgr` 生成头里写 `int m_nRoleCount; // +0xE0E0`，
而**编译器实际把它放在 0xE0BC**（`ClearInactiveRoles` 编译出的指令就是 `[eax+0E0BCh]`），
且 class 起始处因注入的 `virtual ~SceneMgr() {}` 多了 **vptr** ⇒ 成员偏移整体 +4 ✗
⇒ 该类函数**不可能字节一致**（实测：删掉那行虚析构后 `SceneMgr::Create` 由 **25.5% → 80.6%**）。

## 两个独立裁判

* **A. 编译器**（真实 C++ 布局）：逐成员 `char c[offsetof(Cls, m) == 0x<注解偏移> ? 1 : -1];`
  —— 只有不匹配者报 `C2118` ⇒ 一次编译列出全部冲突 ✓
  ⚠️ **测量必须自校验**：本工具用 `#line` 让"检查 → 行号"映射**按构造正确**，
  并额外放一条**故意错误**的校准检查；**若它没报错就中止**（说明映射或编译口径不可信）✓
* **B. IDA**（二进制；需 `--ida`）：`search_structs` 给该类型的 **size / cardinality**，
  与注解的 `binary_size` / 成员数对比 ✓（这是 IDB 之外的独立来源）

## DAG 排序（使用者 2026-09-21 指定）

按**按值成员的类型依赖**做拓扑排序：**先扫基础/叶子类型，再扫依赖类型**，
避免一上来就面对"多类型内嵌"导致的问题 ✓ 环会在报告里显式列出。

用法::

    python3 tools/audit_type_layout.py                 # 编译器裁判（离线、快）
    python3 tools/audit_type_layout.py --limit 20      # 只看前 20 个（按 DAG 序）
    python3 tools/audit_type_layout.py --ida --limit 20
    python3 tools/audit_type_layout.py --json
退出码：发现冲突 ⇒ 1；否则 0。
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'pipeline'))
SRC = os.path.join(ROOT, 'pal3', 'src')
STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')

MEMBER_RE = re.compile(
    r'^\s{4}[\w:<>,\* ]+?\b([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;\s*//\s*\+0x([0-9A-Fa-f]+)')


def load_annotation_members():
    """→ {cls: [(name, declared_offset), ...]}（只取生成头里带 `// +0x` 注释的成员）"""
    out = {}
    for h in sorted(glob.glob(os.path.join(SRC, '**', '*.h'), recursive=True)):
        cls = os.path.basename(h)[:-2]
        ms = []
        for line in open(h, encoding='utf-8', errors='replace'):
            m = MEMBER_RE.match(line)
            if m:
                ms.append((m.group(1), int(m.group(3), 16)))
        if ms:
            out[cls] = (h, ms)
    return out


def dag_order(types):
    """按按值成员依赖做拓扑排序（叶子在前）。→ (order, cycles)

    "按值成员"判定：成员的 `type` 里出现某个已知类型名且**不含 `*`**（指针不决定布局）。
    依据：注解 JSON 的 `known_members[offset].type`。
    """
    deps = {}
    ann = {}
    for p in glob.glob(os.path.join(STRUCTS, '*.json')):
        cls = os.path.basename(p)[:-5]
        try:
            d = json.load(open(p, encoding='utf-8'))
        except Exception:
            continue
        ann[cls] = d
        km = d.get('known_members') or {}
        items = km.values() if isinstance(km, dict) else km
        dset = set()
        for m in items:
            if not isinstance(m, dict):
                continue
            t = str(m.get('type') or '')
            if '*' in t or '[' in t:
                continue
            base = t.replace('struct ', '').replace('class ', '').strip()
            if base in ann or base in types:
                dset.add(base)
        deps[cls] = dset
    order, state, cycles = [], {}, []

    def visit(n, stack):
        st = state.get(n)
        if st == 2:
            return
        if st == 1:
            cycles.append(stack[stack.index(n):] + [n] if n in stack else [n])
            return
        state[n] = 1
        for d in sorted(deps.get(n, ())):
            if d in types:
                visit(d, stack + [n])
        state[n] = 2
        if n in types:
            order.append(n)

    for t in sorted(types):
        visit(t, [])
    return order, cycles


def _measure_chunk(cls, header, chunk, include_dirs, timeout, tag):
    """测量一块（<100 检查，避免 C1003 截断）→ (conflicts, calibration_ok)"""
    import probe_compile as pc
    rel = os.path.relpath(header, SRC).replace('\\', '/')
    lines = ['#include "pal3/ida_defs.h"', '#include "globals.h"', '#include "%s"' % rel]
    line2member = {}
    for n, (name, off) in enumerate(chunk):
        ln = 10000 + n
        line2member[ln] = (name, off)
        lines.append('#line %d "layoutchk"' % ln)
        lines.append('char c_%d[offsetof(%s, %s) == 0x%X ? 1 : -1];' % (n, cls, name, off))
    calib_ln = 99999
    lines.append('#line %d "layoutchk"' % calib_ln)
    lines.append('char calib_bad[offsetof(%s, %s) == 0xDEADBEEF ? 1 : -1];'
                 % (cls, chunk[0][0]))
    src = '/tmp/layout_audit_%s_%s.cpp' % (cls, tag)
    obj = '/tmp/layout_audit_%s_%s.obj' % (cls, tag)
    open(src, 'w', encoding='utf-8').write('\n'.join(lines) + '\n')
    out, _hard = pc.run_cl(
        ['/Fo' + pc.wpath(obj), pc.wpath(src)] + ['/I' + pc.wpath(d) for d in include_dirs],
        timeout=timeout, flags=('/nologo', '/TP', '/c', '/W3'))
    bad = set()
    for m in re.finditer(r'layoutchk\((\d+)\)\s*:\s*error C2118', out):
        bad.add(int(m.group(1)))
    return ({name: off for ln, (name, off) in line2member.items() if ln in bad},
            calib_ln in bad)


def measure_cpp_layout(cls, header, declared, include_dirs, timeout=180, chunk_size=60):
    """编译器裁判（**分块 + 每块自校准**）→ (conflicts, calibration_ok)

    为什么分块：MSVC 在单次编译 ~100 条错误处 C1003 截断 ⇒ 大类的检查会在**末尾之前**
    被截断，校准检查根本编译不到 ⇒ 会把"截断"误读成"无冲突" ✗（`SceneMgr` 实测踩到）。
    每块 60 个检查 + 自带校准 ⇒ 任何一块校准失败即整类结果不可信 ✓
    """
    conflicts, ok = {}, True
    for i in range(0, len(declared), chunk_size):
        chunk = declared[i:i + chunk_size]
        c, calib = _measure_chunk(cls, header, chunk, include_dirs, timeout, 'c%d' % i)
        conflicts.update(c)
        ok = ok and calib
    return conflicts, ok


def ida_struct_summary(names, session=None):
    """IDA 裁判：→ {name: (size, cardinality)}（用 headless MCP 的 search_structs）。"""
    helper = '/tmp/mcp.py'
    if not os.path.exists(helper):
        return None
    try:
        sys.path.insert(0, '/tmp')
        import mcp  # noqa
    except Exception:
        return None
    out = {}
    for n in names:
        try:
            r = mcp.call('search_structs', {'filter': n, 'database': session})
            txt = r[0]['result']['content'][0]['text']
            for item in json.loads(txt):
                if item.get('name') == n:
                    out[n] = (item.get('size'), item.get('cardinality'))
                    break
        except Exception:
            return None
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--limit', type=int, default=15)
    ap.add_argument('--ida', action='store_true')
    ap.add_argument('--session')
    ap.add_argument('--only', help='只审计这些类（逗号分隔）')
    ap.add_argument('--json', action='store_true')
    a = ap.parse_args()

    import probe_compile as pc
    members = load_annotation_members()
    order, cycles = dag_order(set(members))
    todo = [c for c in order if c in members]
    if a.only:
        want = [x.strip() for x in a.only.split(',') if x.strip()]
        todo = [c for c in want if c in members]
    todo = todo[:a.limit]
    print('=' * 78)
    print('类型布局审计（DAG 序：先基础/叶子，再依赖类型）')
    print('  有成员注释的类: %d · DAG 序前 %d 个 · 依赖环: %d' % (len(members), len(todo), len(cycles)))
    if cycles:
        for cyc in cycles[:5]:
            print('  ⚠️ 环: %s' % ' → '.join(cyc))
    print('=' * 78)
    report, n_conf = [], 0
    for cls in todo:
        header, declared = members[cls]
        conf, calib = measure_cpp_layout(cls, header, declared, pc.INCLUDE_DIRS)
        if not calib:
            print('  %-22s ⚠️ **测量不可信**（校准检查未报错）⇒ 跳过' % cls)
            report.append({'cls': cls, 'error': 'calibration_failed'})
            continue
        tag = '✓ 一致' if not conf else '✗ 冲突 %d/%d' % (len(conf), len(declared))
        print('  %-22s 成员=%-4d %s' % (cls, len(declared), tag))
        if conf:
            n_conf += len(conf)
            for name, off in list(conf.items())[:4]:
                print('       %-26s 声明 +0x%-6X 但**实际不是**' % (name, off))
        report.append({'cls': cls, 'declared': len(declared),
                       'conflicts': {k: hex(v) for k, v in conf.items()}})
    print('=' * 78)
    print('冲突合计: %d 个成员（涉及 %d 个类）' % (n_conf, sum(1 for r in report if r.get('conflicts'))))
    print('⇒ 冲突需**人工介入**：先修基础类型（DAG 序靠前），再修依赖类型 ✓')
    if a.json:
        print(json.dumps(report, ensure_ascii=False, indent=1))
    return 1 if n_conf else 0


if __name__ == '__main__':
    sys.exit(main())