#!/usr/bin/env python3
"""端到端裁判（Task 4 R=1，C-3）：真实**生效断言** × 真实**发射头** ⇒ 真机 MSVC6 编译。

## 为什么必须有它（R=0 的教训）

生成器自己的单测只能证明"生成器的规则与我的模型一致"，**不能**证明"规则与 MSVC6
在真实声明上的行为一致"。R=0 的实测反例：

```
RoleCameraCtrl : public PalScriptWaitObj        （pal3/src/Misc/RoleCameraCtrl.h）
  PalScriptWaitObj 发射头 0 个 virtual（注解只有 methods）
  ⇒ MSVC6 把 vfptr 排在**非多态基类子对象之后** ⇒ sizeof(void (RoleCameraCtrl::*)()) = 8
  而 R=0 的"只看继承形状"规则给 4，且标 active/trusted ⇒ 真实头编译 **C2118**（假杀）
```

⇒ 唯一能抓到假杀的手段：把生成头里的**生效**断言逐条放进真实发射头的 TU 里交给编译器。

## 分类（每条生效断言一个编译单元；按**行号**区分"断言行"与"头文件自身"）

| 类别 | 判据 | 含义 |
|---|---|---|
| `pass` | 0 错误 | 断言与真实声明的常量一致 |
| `false_kill` | **断言行** C2118 | 生成器预测值 ≠ 真实声明 ⇒ 假杀（本裁判要消灭的对象） |
| `assert_error` | 断言行其它错误（C2065/C2027…） | 类没被声明/类型不全 ⇒ 头文件侧问题 |
| `header_error` | 只有头文件行报错 | 发射头自身编不过 ⇒ "骑在有错头上"，不判生成器 |
| `no_header` | 找不到声明该类的头 | 生成器侧应已降级（外部类/无发射头） |

## 用法

```sh
cd /home/peng/workspace/PAL3Decomp
P=data/status/_layout_assert_probe_20260925
python3 $P/verify_emitted_asserts.py                       # 全量（≈150 次 MSVC6 编译）
python3 $P/verify_emitted_asserts.py --only RoleCameraCtrl  # 单类追查
python3 $P/verify_emitted_asserts.py --self-test            # 负相自检（故意写错 ⇒ 必须被抓）
python3 $P/verify_emitted_asserts.py --json $P/_emitted_asserts_judge.json
```

退出码：发现 `false_kill` ⇒ 1（可作门禁）。
"""
from __future__ import annotations

import argparse
import concurrent.futures
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple

PROBE_DIR = Path(__file__).resolve().parent
ROOT = PROBE_DIR.parents[2]
sys.path.insert(0, str(ROOT / 'tools'))

from layout_assert_gen import (  # noqa: E402
    GenOptions, STATUS_ACTIVE, generate, load_struct_layouts,
)

WINE_CL = ROOT / 'tools' / 'wine_cl.sh'
VC6_INC = ROOT / 'tools' / 'compilers' / 'msvc6.0' / 'Include'
DX_INC = ROOT / 'tools' / 'vc6' / 'Include'

#: 头文件搜索顺序：**发射头**优先（声明由注解发射 ⇒ 与注解可比）→ spec 头（可能自行补虚函数）
HEADER_ROOTS = ('pal3/src', 'include', 'gbengine/src')
EMITTED_ROOT = 'pal3/src'

DEFAULT_STRUCTS = ROOT / 'data' / 'annotations' / 'structs'
DEFAULT_TREE = ROOT / 'data' / 'status' / '_inheritance_tree.json'

#: 类/结构体**定义**（`class GBAPI X {` / `struct X : public Y {`）；前向声明（`;`）不匹配
_DECL_RE = re.compile(r'^[ \t]*(?:class|struct)\s+([^;{}\n]*?)\s*(?::[^;{\n]*)?\{', re.M)
#: MSVC 错误行：`Z:\tmp\t.cpp(3) : error C2118: ...` / `fatal error C1083: ...`
_ERROR_RE = re.compile(r'\((\d+)\)\s*:\s*(?:fatal\s+)?error\s+(C\d+)')

#: 断言恒在第 3 行（stddef → 头文件 → 断言）
ASSERT_LINE = 3


def wine_cl_available() -> bool:
    return WINE_CL.exists() and (ROOT / 'tools' / 'compilers' / 'msvc6.0' / 'Bin' / 'CL.EXE').exists()


def class_name_of(prelude: str) -> Optional[str]:
    """`class GBAPI gbRefObject` ⇒ `gbRefObject`（导出宏在类名之前，取最后一个标识符）。"""
    toks = re.findall(r'[A-Za-z_]\w*', prelude or '')
    return toks[-1] if toks else None


def scan_declared_classes(root: Path) -> Dict[str, List[str]]:
    """扫描一个目录下的 `*.h` ⇒ `{类名: [头文件相对路径, ...]}`（只收**定义**）。"""
    out: Dict[str, List[str]] = {}
    root = Path(root)
    for path in sorted(root.rglob('*.h')):
        try:
            text = path.read_text(encoding='utf-8', errors='ignore')
        except OSError:
            continue
        for m in _DECL_RE.finditer(text):
            name = class_name_of(m.group(1))
            if not name:
                continue
            out.setdefault(name, []).append(str(path.relative_to(root)))
    return out


def build_header_index(roots: Sequence[str] = HEADER_ROOTS) -> Dict[str, Tuple[str, str]]:
    """`{类名: (根, 头文件相对该根的路径)}`；先到先得（`pal3/src` 发射头优先）。

    一个类算"有发射声明"的条件（两条任一）：
      1. 该头文件里有 `class/struct X { ... }` 的**定义**；
      2. 该根下有**同名头文件** `X.h`（codegen 对模板具体化会发射
         `<X>.h` shim：`typedef CTaskTpl<...> X;` + include 具体化头 —— 实测
         `pal3/src/Misc/CTaskTpl_tagEffTaskParam_CEffAction.h`，其具体化头里的类体
         同样由注解发射 ⇒ 与注解可比）。
    同一根内有多个候选时，优先与类同名的 `X.h`，再按路径长度/字典序（确定性）。
    """
    per_root: Dict[str, Dict[str, List[str]]] = {}
    for rel in roots:
        d = ROOT / rel
        if d.is_dir():
            per_root[rel] = scan_declared_classes(d)
    index: Dict[str, Tuple[str, str]] = {}
    for rel in roots:
        root_dir = ROOT / rel
        decls = per_root.get(rel) or {}
        for cls, paths in decls.items():
            if cls in index:
                continue
            best = sorted(paths, key=lambda p: (Path(p).stem != cls, len(p), p))[0]
            index[cls] = (rel, best)
        # 同名头文件（模板 shim / 只有 typedef 的发射头）也算发射声明
        if root_dir.is_dir():
            for path in sorted(root_dir.rglob('*.h')):
                stem = path.stem
                if stem and stem not in index:
                    index[stem] = (rel, str(path.relative_to(root_dir)))
    return index


def parse_errors(stdout: str) -> List[Tuple[int, str]]:
    return [(int(line), code) for line, code in _ERROR_RE.findall(stdout or '')]


def classify_result(stdout: str, assert_line: int = ASSERT_LINE) -> str:
    """编译器输出 ⇒ `pass` / `false_kill` / `unreliable` / `assert_error` / `header_error`。

    ★ 只有在 **TU 自身编得过**（除断言行外无错误）时，断言行的 C2118 才算**假杀**；
    否则算 `unreliable`（例如 `CEffTrack*` 的 C2584 重复间接基、`PlayerAtt` 的 C2061 —
    头本身编不过时，断言行的失败可能是连锁噪声，不能据此判生成器）。
    """
    errs = parse_errors(stdout)
    if not errs:
        return 'pass'
    at_line = [c for line, c in errs if line == assert_line]
    other = [1 for line, _ in errs if line != assert_line]
    if at_line and 'C2118' in at_line:
        return 'false_kill' if not other else 'unreliable'
    if at_line:
        return 'assert_error' if not other else 'header_error'
    return 'header_error'


def build_tu(header_rel: str, condition: str, name: str) -> str:
    return ('#include <stddef.h>\n'
            '#include "%s"\n'
            'typedef char %s[(%s) ? 1 : -1];\n' % (header_rel, name, condition))


def compile_tu(text: str, workdir: Path, tag: str, timeout: int = 300) -> str:
    src = workdir / ('%s.cpp' % tag)
    obj = workdir / ('%s.obj' % tag)
    src.write_text(text, encoding='utf-8')
    cmd = [str(WINE_CL), '/c', '/nologo', '/O2', '/GR',
           '/I%s' % (ROOT / 'include'), '/I%s' % (ROOT / 'pal3' / 'src'),
           '/I%s' % (ROOT / 'gbengine' / 'src'), '/I%s' % DX_INC, '/I%s' % VC6_INC,
           '/Fo%s' % obj, str(src)]
    try:
        proc = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return 'TIMEOUT'
    return (proc.stdout or '') + (proc.stderr or '')


def _cases(assertions: Iterable, index: Dict[str, Tuple[str, str]],
           negative_controls: Sequence[Tuple[str, str]] = ()) -> List[dict]:
    cases = []
    for a in assertions:
        ent = index.get(a.cls)
        cases.append({'cls': a.cls, 'name': a.name, 'condition': a.condition,
                      'kind': a.kind, 'root': ent[0] if ent else None,
                      'header': ent[1] if ent else None, 'control': False})
    for cls, condition in negative_controls:
        ent = index.get(cls)
        cases.append({'cls': cls, 'name': '_negctl_%s' % cls, 'condition': condition,
                      'kind': 'negative-control', 'root': ent[0] if ent else None,
                      'header': ent[1] if ent else None, 'control': True})
    return cases


def judge_emitted(layouts=None, options: Optional[GenOptions] = None,
                  only: Optional[frozenset] = None, jobs: int = 4,
                  timeout: int = 300,
                  negative_controls: Sequence[Tuple[str, str]] = (),
                  header_index: Optional[Dict[str, Tuple[str, str]]] = None,
                  restrict_emitted: bool = True, verbose: bool = True) -> dict:
    """把生成头的**生效**断言逐条拿去真机编译 ⇒ 台账 dict。

    `restrict_emitted=True`（默认）只编译**发射头**（`pal3/src`）里的类：
    只有那里的声明才是由注解发射的，断言才可比；spec 头（`gb*`）单列 `spec_header`。
    """
    index = header_index if header_index is not None else build_header_index()
    if layouts is None:
        layouts = load_struct_layouts(DEFAULT_STRUCTS, tree_path=DEFAULT_TREE)
    if options is None:
        emitted = frozenset(c for c, (r, _) in index.items() if r == EMITTED_ROOT)
        options = GenOptions(declared_classes=emitted)
    res = generate(layouts, options)
    actives = [a for a in res.assertions if a.status == STATUS_ACTIVE]
    if only is not None:
        actives = [a for a in actives if a.cls in only]
    cases = _cases(actives, index, negative_controls)

    report = {'total': 0, 'pass': 0, 'false_kill': [], 'unreliable': [],
              'assert_error': [], 'header_error': [], 'no_header': [], 'spec_header': [],
              'by_root': {}, 'gate': {'active': len(actives)}}

    todo = []
    for c in cases:
        if c['header'] is None:
            report['no_header'].append({'cls': c['cls'], 'condition': c['condition']})
            continue
        if restrict_emitted and c['root'] != EMITTED_ROOT:
            report['spec_header'].append({'cls': c['cls'], 'root': c['root'],
                                          'condition': c['condition']})
            continue
        todo.append(c)
    report['total'] = len(todo)

    if todo and not wine_cl_available():
        raise RuntimeError('MSVC6/wine 不可用：%s' % WINE_CL)

    def _run(item):
        c, workdir = item
        out = compile_tu(build_tu(c['header'], c['condition'], c['name']),
                         workdir, c['name'][:60] or 'a')
        c['kind_result'] = classify_result(out)
        c['errors'] = ['C%s@%d' % (code[1:], line) for line, code in parse_errors(out)]
        first = [l for l in (out or '').splitlines() if 'error' in l][:3]
        c['output'] = '\n'.join(first)
        return c

    with tempfile.TemporaryDirectory(prefix='lap_judge_') as tmp:
        workdir = Path(tmp)
        items = [(c, workdir) for c in todo]
        if jobs <= 1:
            done = [_run(it) for it in items]
        else:
            with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as pool:
                done = list(pool.map(_run, items))

    for c in done:
        kind = c['kind_result']
        bucket = {'cls': c['cls'], 'condition': c['condition'], 'root': c['root'],
                  'header': c['header'], 'errors': c['errors'], 'output': c['output'],
                  'control': c['control']}
        if kind == 'pass':
            report['pass'] += 1
        elif kind == 'false_kill':
            report['false_kill'].append(bucket)
        elif kind == 'unreliable':
            report['unreliable'].append(bucket)
        elif kind == 'assert_error':
            report['assert_error'].append(bucket)
        else:
            report['header_error'].append(bucket)
        report['by_root'][c['root']] = report['by_root'].get(c['root'], 0) + 1

    if verbose:
        print_report(report, res.census)
    return report


def print_report(report: dict, census: Optional[dict] = None) -> None:
    print('=== 端到端裁判（真实生效断言 × 真实发射头，MSVC6）===')
    if census:
        print('生成口径: total=%s active=%s commented=%s consistency-only=%s'
              % (census.get('total'), census.get('active'), census.get('commented'),
                 census.get('consistency-only', 0)))
    print('编译: total=%d pass=%d false_kill=%d unreliable=%d assert_error=%d header_error=%d'
          % (report['total'], report['pass'], len(report['false_kill']),
             len(report['unreliable']), len(report['assert_error']),
             len(report['header_error'])))
    print('未编译: no_header=%d spec_header=%d by_root=%s'
          % (len(report['no_header']), len(report['spec_header']), report['by_root']))
    for b in report['false_kill']:
        print('  FALSE-KILL %s: %s\n    %s' % (b['cls'], b['condition'], b['output']))
    for b in report['unreliable']:
        print('  UNRELIABLE %s (%s): 头未编过 + 断言行 C2118：%s'
              % (b['cls'], b['header'], b['errors'][:3]))
    for b in report['header_error']:
        print('  HEADER-ERROR %s (%s): %s' % (b['cls'], b['header'], b['errors'][:3]))
    print('=== %s ===' % ('ALL CHECKS PASSED' if not report['false_kill'] else 'FALSE KILLS FOUND'))


def self_test(jobs: int = 2, verbose: bool = True) -> int:
    """负相自检：故意写错一条断言 ⇒ 裁判**必须**报 false_kill（证明裁判看得见 C2118）。"""
    if not wine_cl_available():
        print('SKIP self-test: MSVC6/wine 不可用', file=sys.stderr)
        return 0
    index = build_header_index()
    if 'RoleCameraCtrl' not in index:
        print('SKIP self-test: 找不到 RoleCameraCtrl 的发射头', file=sys.stderr)
        return 0
    report = judge_emitted(only=frozenset({'RoleCameraCtrl'}), jobs=jobs, verbose=False,
                           negative_controls=[('RoleCameraCtrl',
                                               'sizeof(void (RoleCameraCtrl::*)()) == 4096')])
    ok = len(report['false_kill']) == 1 and report['pass'] >= 1
    print('SELF-TEST %s: pass=%d false_kill=%d'
          % ('OK' if ok else 'FAILED', report['pass'], len(report['false_kill'])))
    if verbose and not ok:
        print_report(report)
    return 0 if ok else 1


def main(argv=None) -> int:
    p = argparse.ArgumentParser(description='布局断言端到端裁判（真实发射头 × 真实生效断言）')
    p.add_argument('--only', default=None, help='逗号分隔类名（只裁这类）')
    p.add_argument('--jobs', type=int, default=4)
    p.add_argument('--timeout', type=int, default=300)
    p.add_argument('--json', default=None, help='把台账写到该路径')
    p.add_argument('--self-test', action='store_true', help='负相自检（故意写错一条）')
    p.add_argument('--all-headers', action='store_true',
                   help='连 spec 头（gb*）一起编译（默认只编译发射头 pal3/src）')
    p.add_argument('--no-declared-gate', action='store_true',
                   help='不给生成器 --declared-classes（度量"没有名单时会漏多少"）')
    p.add_argument('--quiet', action='store_true')
    args = p.parse_args(argv)

    if args.self_test:
        return self_test(jobs=min(args.jobs, 2), verbose=not args.quiet)

    index = build_header_index()
    emitted = frozenset(c for c, (r, _) in index.items() if r == EMITTED_ROOT)
    options = GenOptions() if args.no_declared_gate else GenOptions(declared_classes=emitted)
    only = frozenset(s.strip() for s in args.only.split(',') if s.strip()) if args.only else None
    layouts = load_struct_layouts(DEFAULT_STRUCTS, tree_path=DEFAULT_TREE)

    # 承重度量：不给名单时有多少生效断言落在"没有发射头"的类上（说明名单是必需的）
    if not args.no_declared_gate:
        plain = generate(layouts, GenOptions())
        plain_active = [a for a in plain.assertions if a.status == STATUS_ACTIVE]
        leaked = sorted({a.cls for a in plain_active
                         if index.get(a.cls, (None,))[0] != EMITTED_ROOT})
        if leaked and not args.quiet:
            print('名单承重: 不给 --declared-classes 时有 %d 个类的生效断言没有发射头: %s'
                  % (len(leaked), ', '.join(leaked[:12])))

    report = judge_emitted(layouts, options=options, only=only, jobs=args.jobs,
                           timeout=args.timeout, header_index=index,
                           restrict_emitted=not args.all_headers, verbose=not args.quiet)
    if args.json:
        Path(args.json).write_text(json.dumps(report, ensure_ascii=False, indent=1),
                                  encoding='utf-8')
    return 1 if report['false_kill'] else 0


if __name__ == '__main__':
    sys.exit(main())