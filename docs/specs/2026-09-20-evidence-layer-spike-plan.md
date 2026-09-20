# 注解证据层 · 交付 1（advisory 写盘接线 + Spike）实施计划

> **面向 Agent 执行者：** 必需子技能：使用 superpower-subagent-driven-development（推荐）或 superpower-executing-plans 按任务逐项执行本计划。步骤使用复选框（`- [ ]`）语法进行跟踪。

**目标：** 让 `codegen_invariants` 的 advisory 报告真正挂在**写盘路径**上（不再是空门），并用一个**只读 Spike** 验证"独立于注解的尺寸/归属证据源"可行（133 个 `??_L` 站点 → 元素尺寸证据），**不改注解、不改生成物、不接硬门禁**。

**架构：** 两个互不阻塞的部分。(A) 把 `--advisory` 调用点从 `cmd_check` 扩展到 `cmd_apply`/`cmd_export`，只打印不改变退出码 ✓。(B) Spike 新增**只读**工具 `tools/audit_element_sizes.py`：从 `original/PAL3.exe.asm` 按函数边界抽 `??_L` 五元组（`ptr,size,count,ctor,dtor`）与 `??_M` 四元组（`ptr,size,count,dtor`），产出**两层**报告：`raw_site`（纯地址/字节/字面量 ✓）与 `ownership_candidate`（ctor 地址 → 注解归属**仅作候选** ✓），并对三个 fixture 输出判定。

**技术栈：** Python 3（标准库 `re`/`json`/`argparse`）、仓库自带 MSVC6（**本计划不使用**）、`original/PAL3.exe.asm`（**gitignored**，缺失时工具必须 exit 2 而非静默 ✓）。

**规格：** `docs/specs/2026-09-20-evidence-layer-design.md`（含"三路对抗复核结论与修订要求"附录）——**执行者需同时阅读规格与该附录**。

## 全局约束
- **本计划不改任何 annotation**（`data/annotations/**` 零改动）✓；不改生成物（`pal3/src/**`）✓；**不接硬门禁**（不加任何 exit≠0 的门）✓。
- 判据（若误触管线时）：`new_failures=0`、`L1 == 34` 不回退、`s2 ok ≥76`、`pipeline/cli.py check` PASS；**总错误数不作判据**（同状态可差 ±18）。
- 新增写盘能力的脚本必须套用 `tools/_land_sizes.py` 的护栏模式：**任何以 `-` 开头的参数不是已知开关即拒绝执行并退出**（防重演已发生 2 起的 `--help` 覆盖产物事故）。
- 禁止 `git checkout/restore/stash/clean -fd`；回退用 `git show HEAD:<path> > <path>`。
- 产物必须记录**输入参数与来源**（算法版本、输入文件路径、生成时刻）——反例：`_geometry_strict_report.json` 的 `warn_count: 6` 因未记录 `PAL3_GEOMETRY_WARN_RATIO` 而不可复现 ✗。
- `??_L` 五元组顺序（已由两路独立读 asm 确认）：`push dtor; push ctor; push count; push size; push ptr; call ??_L` ⇒ 实参语义为 `(ptr, size, count, ctor, dtor)`。
- `??_M` 是**四元组** `(ptr, size, count, dtor)`，**无 ctor** ⇒ 不得与 `??_L` 共用五元组描述。

---

### 任务 1：把 advisory 报告挂到写盘路径（apply / export）

**文件：**
- 修改：`pipeline/cli.py`（`cmd_apply` 尾部、`cmd_export` 尾部；`cmd_check` 已接好，勿动）
- 测试：`tests/test_advisory_wired_into_write_path.py`（新建）

**接口：**
- 依赖输入：`tools/codegen_invariants.py --advisory`（已存在；恒 exit 0）
- 对外产出：`pipeline.cli._run_invariants_advisory()` → `int`（返回子进程退出码，**调用方不得据此改变自身退出码**）

- [ ] **步骤 1：编写失败的测试**

```python
# tests/test_advisory_wired_into_write_path.py
import re, pathlib
SRC = pathlib.Path(__file__).resolve().parent.parent / 'pipeline' / 'cli.py'

def test_apply_and_export_call_invariants_advisory():
    src = SRC.read_text(encoding='utf-8')
    for fn in ('def cmd_apply(', 'def cmd_export('):
        i = src.index(fn)
        j = src.index('\ndef ', i + 1)
        body = src[i:j]
        assert '_run_invariants_advisory' in body, '%s 未接 advisory 门' % fn

def test_advisory_result_does_not_change_exit_code():
    src = SRC.read_text(encoding='utf-8')
    i = src.index('def _run_invariants_advisory(')
    j = src.index('\ndef ', i + 1)
    body = src[i:j]
    assert 'sys.exit' not in body, 'helper 不得自行退出'
```

- [ ] **步骤 2：运行测试并确认其失败**

运行：`python3 tests/test_advisory_wired_into_write_path.py -v`（若该文件用 `main()` 风格则 `python3 tests/test_advisory_wired_into_write_path.py`）
预期：FAIL，`AssertionError: def cmd_apply( 未接 advisory 门`

- [ ] **步骤 3：编写最小实现**

```python
# pipeline/cli.py —— 放在 cmd_check 之前
def _run_invariants_advisory():
    """advisory 地跑 codegen_invariants：只报告计数，**不影响调用方的退出码**。"""
    inv = os.path.join(_PROJECT_DIR, 'tools', 'codegen_invariants.py')
    if not os.path.exists(inv):
        return 0
    print()
    print("[Invariants] advisory 模式（只报告，不影响退出码）...")
    r = subprocess.run([sys.executable, inv, '--advisory'])
    if r.returncode != 0:
        print("[WARN] codegen_invariants 在 advisory 模式下仍非零退出（%d）—— 不影响本次结果，"
              "但说明工具行为与预期不符 ✓" % r.returncode)
    return r.returncode
```

在 `cmd_apply` 与 `cmd_export` 的**成功路径末尾**（即最后一行 `print("Next: ...")` 之前）各插入：

```python
    _run_invariants_advisory()
```

- [ ] **步骤 4：运行测试并确认其通过**

运行：`python3 tests/test_advisory_wired_into_write_path.py`
预期：PASS（无输出即通过；若有 `main()` 汇总则显示 `Results: 2 passed`）

- [ ] **步骤 5：提交**

```bash
git add pipeline/cli.py tests/test_advisory_wired_into_write_path.py
git commit -m "exec(D1): 把 codegen_invariants advisory 挂到写盘路径（apply/export），消除'只改 cmd_check 就是空门'"
```

---

### 任务 2：`??_L/??_M` 站点抽取器（只读，先写测试）

**文件：**
- 新建：`tools/audit_element_sizes.py`
- 测试：`tests/test_audit_element_sizes.py`

**接口：**
- 依赖输入：`original/PAL3.exe.asm`（gitignored ⇒ 缺失时 `return 2`）
- 对外产出：`parse_sites(asm_text: str) -> list[dict]`，每条 `{"site":"0x…","kind":"ehl|ehm","ptr":"0x…","size":int,"count":int,"ctor":"0x…"|None,"dtor":"0x…"|None,"line":int}`

- [ ] **步骤 1：编写失败的测试**（含 **fixture 断言**：`size` 必须来自字面量 `push`）

```python
# tests/test_audit_element_sizes.py
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'tools'))
import audit_element_sizes as a

ASM = """
sub_408740      proc near
                push    offset sub_411CA0
                push    offset sub_411900
                push    5
                push    2200h
                push    offset unk_C05F60
                call    ??_L@YGXPAXIHP6EX0@Z1@Z
sub_408740      endp
"""

def test_parse_l_pushes_tuple():
    sites = a.parse_sites(ASM)
    assert len(sites) == 1
    s = sites[0]
    assert s['kind'] == 'ehl'
    assert s['size'] == 0x2200          # 来自 push 2200h 字面量
    assert s['count'] == 5
    assert s['ctor'] == '0x411900'
    assert s['dtor'] == '0x411CA0'

def test_missing_asm_returns_2(tmp_path, monkeypatch):
    monkeypatch.setattr(a, 'ASM_PATH', str(tmp_path / 'nope.asm'))
    assert a.main([]) == 2

def test_unknown_flag_is_rejected(monkeypatch):
    monkeypatch.setattr(sys, 'argv', ['audit_element_sizes.py', '--help'])
    assert a.main(['--help']) == 0   # 护栏：拒绝执行而非跑全流程
```

- [ ] **步骤 2：运行测试并确认其失败**

运行：`python3 tests/test_audit_element_sizes.py`
预期：FAIL，`ModuleNotFoundError: No module named 'audit_element_sizes'`

- [ ] **步骤 3：编写最小实现**

```python
#!/usr/bin/env python3
"""只读：从 original/PAL3.exe.asm 抽 ??_L/??_M 的元素尺寸证据（Spike 用）。"""
import argparse, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM_PATH = os.path.join(ROOT, 'original', 'PAL3.exe.asm')
_PUSH = re.compile(r'^\s*push\s+(?:offset\s+)?([0-9A-Fa-f]+h|offset\s+\w+|\w+)\s*$')
_CALL_L = re.compile(r'^\s*call\s+(\?\?_L@\S+)')
_CALL_M = re.compile(r'^\s*call\s+(\?\?_M@\S+)')
_PROC = re.compile(r'^([A-Za-z_]\w*)\s+proc near')

def _val(tok):
    tok = tok.strip()
    if tok.endswith('h'):
        return '0x%X' % int(tok[:-1], 16)
    if re.fullmatch(r'\d+', tok):
        return int(tok)
    return tok  # 符号名（sub_/unk_/offset …）

def parse_sites(asm_text):
    sites, cur, buf, ln = [], None, [], 0
    for i, line in enumerate(asm_text.split('\n'), 1):
        m = _PROC.match(line)
        if m:
            cur, buf = m.group(1), []
            continue
        if _CALL_L.match(line) or _CALL_M.match(line):
            kind = 'ehl' if _CALL_L.match(line) else 'ehm'
            vals = [v for v in buf[-5:]]           # 最近 5 个 push
            need = 5 if kind == 'ehl' else 4
            if len(vals) < need:
                sites.append({'site': cur, 'kind': kind, 'incomplete': True, 'line': i}); buf = []; continue
            ptr, size, count, a4, a5 = vals[-5:] if kind == 'ehl' else (vals[-4:] + [None])
            sites.append({'site': cur, 'kind': kind, 'ptr': ptr, 'size': size,
                          'count': count,
                          'ctor': a4 if kind == 'ehl' else None,
                          'dtor': a5 if kind == 'ehl' else a4, 'line': i})
            buf = []
            continue
        p = _PUSH.match(line)
        if p:
            buf.append(_val(p.group(1)))
    return sites

def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    known = {'--asm', '--json'}
    unknown = [a for a in argv if a.startswith('-') and a.split('=')[0] not in known]
    if unknown:
        print('[audit_element_sizes] 未知开关 %r ⇒ 不执行任何操作' % unknown); return 0
    ap = argparse.ArgumentParser(); ap.add_argument('--asm', default=ASM_PATH)
    ap.add_argument('--json', default=None)
    args = ap.parse_args(argv)
    if not os.path.exists(args.asm):
        print('[ERROR] 缺 asm: %s（gitignored，需本机存在）' % args.asm, file=sys.stderr); return 2
    sites = parse_sites(open(args.asm, encoding='utf-8', errors='replace').read())
    inc = [s for s in sites if s.get('incomplete')]
    print('站点 %d（完整 %d / 不完整 %d）' % (len(sites), len(sites) - len(inc), len(inc)))
    if args.json:
        json.dump({'asm': args.asm, 'sites': sites}, open(args.json, 'w'), indent=1)
        print('-> %s' % args.json)
    return 0

if __name__ == '__main__':
    sys.exit(main())
```

- [ ] **步骤 4：运行测试并确认其通过**

运行：`python3 tests/test_audit_element_sizes.py`
预期：PASS（3 例全过）

- [ ] **步骤 5：提交**

```bash
git add tools/audit_element_sizes.py tests/test_audit_element_sizes.py
git commit -m "spike(D1): 只读 ??_L/??_M 元素尺寸站点抽取器（含 -开头参数护栏与 asm 缺失 exit 2）"
```

---

### 任务 3：全量抽取 + **133 站点**核对（Spike 成功判据 ①）

**文件：**
- 修改：无（只跑工具）
- 产物：`data/status/element_size_sites.json`（新，tracked；含输入路径与生成时刻）

**接口：**
- 依赖输入：任务 2 的 `tools/audit_element_sizes.py`
- 对外产出：`data/status/element_size_sites.json`，顶层 `{"asm":…,"generated_at":…,"sites":[…]}`

- [ ] **步骤 1：运行抽取**

```bash
python3 tools/audit_element_sizes.py --json data/status/element_size_sites.json
```

- [ ] **步骤 2：核对计数（成功判据 ①：`??_L` 必须 133 且无"不完整"）**

```bash
python3 - <<'PY'
import json, collections
d = json.load(open('data/status/element_size_sites.json'))
c = collections.Counter(s['kind'] for s in d['sites'])
inc = [s for s in d['sites'] if s.get('incomplete')]
print('ehl=%d ehm=%d 不完整=%d' % (c['ehl'], c['ehm'], len(inc)))
assert c['ehl'] == 133, 'ehl 站点应为 133，实得 %d' % c['ehl']
assert not inc, '存在抽取不完整的站点：%s' % inc[:3]
print('OK')
PY
```
预期：`ehl=133 ehm=… 不完整=0` 且 `OK`。**若 ehl ≠ 133 ⇒ 停止并记录**（不得修改断言迁就结果 ✗）。

- [ ] **步骤 3：提交**

```bash
git add data/status/element_size_sites.json
git commit -m "spike(D1): 全量抽取 element-size 站点（ehl=133, 不完整=0）"
```

---

### 任务 4：三个 fixture 裁定（Spike 成功判据 ②，**本交付的核心**）

**文件：**
- 新建：`tools/element_size_adjudicate.py`
- 测试：`tests/test_element_size_adjudicate.py`
- 产物：`data/status/element_size_adjudication.json`（tracked）

**接口：**
- 依赖输入：任务 3 的站点 JSON；`data/annotations/structs/*.json`（**只读**）
- 对外产出：`adjudicate(sites, structs) -> list[dict]`，每条含 `raw_site`（**不含注解信息** ✓）与 `ownership_candidate`（**仅候选，含 lowered evidence 标注** ✓）

**fixture 期望（成功判据 ②）**：
| fixture | 期望裁定 | 理由 |
|---|---|---|
| `Role`（size `0x2200`）| `evidenced`（size 与 `Role.binary_size==8704` 一致 ✓）| 元素尺寸来自**指令字面量** ✓ |
| `sub_4236D0`（被注成 `BINK::Reset`）| `ownership=conflict`（**不是** `BINK` 的 verified ✗）| `BINK.binary_size=932 ≠ 896` ✓ |
| `sub_411CA0`（`PalScript::~PalScript` vs `Role` 数组 dtor）| `ownership=conflict`（**双源矛盾**）| 同一地址被两处主张 ✓ |

- [ ] **步骤 1：编写失败的测试**

```python
# tests/test_element_size_adjudicate.py
import sys, os, json, pathlib
ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'tools'))
import element_size_adjudicate as a

def test_role_is_evidenced_from_literal():
    sites = [{'site':'sub_408740','kind':'ehl','ptr':'0x0','size':0x2200,'count':5,
              'ctor':'0x411900','dtor':'0x411CA0','line':1}]
    structs = {'Role': {'binary_size': 8704}, 'RoleSystem': {'binary_size': 8704}}
    out = a.adjudicate(sites, structs)
    role = [x for x in out if x['size'] == 0x2200][0]
    assert role['raw_site']['size'] == 0x2200          # raw 层不掺注解
    assert role['size_state'] == 'evidenced'
    assert set(role['ownership_candidate']['candidates']) == {'Role', 'RoleSystem'}  # 不唯一 ⇒ 仅候选
    assert role['ownership_candidate']['state'] == 'ambiguous'

def test_bink_wrong_anchor_is_conflict_not_verified():
    sites = [{'site':'sub_41F6F0','kind':'ehl','ptr':'0x0','size':896,'count':64,
              'ctor':'0x4236D0','dtor':'0x423880','line':1}]
    structs = {'BINK': {'binary_size': 932}, 'tagRoleSlot': {'binary_size': 896}}
    out = a.adjudicate(sites, structs)
    assert out[0]['size_state'] == 'evidenced'
    assert out[0]['ownership_candidate']['state'] in ('ambiguous','conflict')
    assert out[0]['ownership_candidate'].get('verified_class') != 'BINK'   # 不得把 896 挂到 BINK
```

- [ ] **步骤 2：运行测试并确认其失败**

运行：`python3 tests/test_element_size_adjudicate.py`
预期：FAIL，`ModuleNotFoundError: No module named 'element_size_adjudicate'`

- [ ] **步骤 3：编写最小实现**

```python
#!/usr/bin/env python3
"""只读：把 element-size 站点裁成 raw_site + ownership_candidate 两层（Spike）。

**分层纪律（三路复核要求）**：raw_site 只含地址/字节/字面量 ✓；
annotation-derived 的 ctor 归属**只能进 ownership_candidate 且标记为 lowered evidence** ✓，
**永不直接产生 class 级 A 证据** ✓。
"""
import argparse, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations', 'structs')

def _load_structs():
    out = {}
    for f in sorted(os.listdir(ANN)) if os.path.isdir(ANN) else []:
        if f.endswith('.json'):
            try: d = json.load(open(os.path.join(ANN, f), encoding='utf-8'))
            except Exception: continue
            out[d.get('name') or f[:-5]] = d
    return out

def _ctor_to_class(structs):
    m = {}
    for name, d in structs.items():
        for addr, v in (d.get('methods') or {}).items():
            m.setdefault(addr.lower(), []).append((name, (v or {}).get('name')))
    return m

def adjudicate(sites, structs):
    idx = _ctor_to_class(structs)
    out = []
    for s in sites:
        raw = {'site': s.get('site'), 'line': s.get('line'), 'kind': s.get('kind'),
               'ptr': s.get('ptr'), 'size': s.get('size'), 'count': s.get('count'),
               'ctor': s.get('ctor'), 'dtor': s.get('dtor')}
        same = [n for n, d in structs.items() if d.get('binary_size') == s.get('size')]
        cands = []
        for key in ('ctor', 'dtor'):
            a0 = s.get(key)
            if a0 and a0.lower() in idx:
                for cls, nm in idx[a0.lower()]:
                    cands.append({'addr': a0, 'class': cls, 'name': nm, 'evidence': 'annotation(lowered)'})
        verified = None
        if len(cands) == 1 and len(same) == 1 and cands[0]['class'] == same[0]:
            verified = same[0]
        state = 'conflict' if len(cands) > 1 else ('ambiguous' if len(same) > 1 else 'candidate')
        out.append({'raw_site': raw,
                    'size_state': 'evidenced' if s.get('size') is not None else 'unestablished',
                    'size_matches_classes': same,
                    'ownership_candidate': {'candidates': cands, 'state': state,
                                            'verified_class': verified}})
    return out

def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    known = {'--sites', '--json'}
    unk = [a for a in argv if a.startswith('-') and a.split('=')[0] not in known]
    if unk:
        print('[element_size_adjudicate] 未知开关 %r ⇒ 不执行' % unk); return 0
    ap = argparse.ArgumentParser()
    ap.add_argument('--sites', default=os.path.join(ROOT, 'data', 'status', 'element_size_sites.json'))
    ap.add_argument('--json', default=None)
    a = ap.parse_args(argv)
    if not os.path.exists(a.sites):
        print('[ERROR] 缺站点文件: %s（先跑 audit_element_sizes.py）' % a.sites, file=sys.stderr); return 2
    sites = json.load(open(a.sites, encoding='utf-8')).get('sites', [])
    res = adjudicate(sites, _load_structs())
    ev = sum(1 for r in res if r['size_state'] == 'evidenced')
    print('裁定 %d 条：evidenced=%d' % (len(res), ev))
    if a.json:
        json.dump({'sites': a.sites, 'rows': res}, open(a.json, 'w'), indent=1)
        print('-> %s' % a.json)
    return 0

if __name__ == '__main__':
    sys.exit(main())
```

- [ ] **步骤 4：运行测试并确认其通过**

运行：`python3 tests/test_element_size_adjudicate.py`
预期：PASS（2 例）

- [ ] **步骤 5：全量裁定并**手工核对三个 fixture**（成功判据 ②）**

```bash
python3 tools/element_size_adjudicate.py --json data/status/element_size_adjudication.json
python3 - <<'PY'
import json
d = json.load(open('data/status/element_size_adjudication.json'))
rows = d['rows']
role = [r for r in rows if r['raw_site']['size'] == 0x2200]
print('0x2200 站点数:', len(role))
for r in role[:3]:
    print('  ctor候选:', r['ownership_candidate']['candidates'],
          '| verified:', r['ownership_candidate']['verified_class'],
          '| state:', r['ownership_candidate']['state'])
# 成功判据 ②：Role 一致；BINK 错锚不得被判 verified
bink = [c for r in rows for c in r['ownership_candidate']['candidates'] if c['class'] == 'BINK']
print('BINK 作为归属候选出现次数:', len(bink), '（其 verified_class 必须为 None）')
assert not [r for r in rows if r['ownership_candidate']['verified_class'] == 'BINK']
print('OK')
PY
```
预期：打印 `0x2200` 站点与候选；**无任何 BINK 被 `verified_class`** ⇒ `OK`。

- [ ] **步骤 6：提交**

```bash
git add tools/element_size_adjudicate.py tests/test_element_size_adjudicate.py data/status/element_size_adjudication.json
git commit -m "spike(D1): 两层裁定器（raw_site / ownership_candidate）—— Role evidenced、BINK 错锚判非 verified"
```

---

### 任务 5：Spike 报告（成功判据 ③：**不改注解/不改生成物/不接硬门禁**）

**文件：**
- 新建：`data/status/_spike_element_sizes_20260920.md`

**接口：**
- 依赖输入：任务 3/4 的产物 JSON
- 对外产出：一份含"结论 + 复算命令 + 未决项"的报告（供决定是否推进交付 2/3）

- [ ] **步骤 1：写报告**（必须包含：站点计数与不完整数；三个 fixture 的裁定；`??_M` 与 `??_L` 的参数差异；**已知漏采**：indexed addressing / this 重载 / 中间指针 ⇒ 只能作 candidate/signal ✓；与 91-vs-38 口径的解释）

- [ ] **步骤 2：核对"未改任何注解与生成物"（成功判据 ③）**

```bash
git status --porcelain -- data/annotations pal3/src | head
```
预期：**无输出**（本交付不得改动这两处）✓

- [ ] **步骤 3：提交**

```bash
git add data/status/_spike_element_sizes_20260920.md
git commit -m "spike(D1): 报告与未决项（未改注解/未改生成物/未接硬门禁）"
```

---

## 自检（已由计划作者执行）
1. **规格覆盖度**：本计划只覆盖规格附录 §D 的"先做一小步 #1（C advisory 接线）"与"#4（Spike）"✓；**交付 2（消费点 INCONCLUSIVE 与报告通道）与交付 3（`--scan` + 逐闸毕业生效）另立计划** ✓；规格 §0/§2.5/§3.5/§4.5/§5.5/§7.5 的其余要求**不在本计划**（已在规格中标注归属）✓。
2. **占位符扫描**：无 TBD/TODO；每个代码步骤都含可运行代码块 ✓；每步都有确切命令与预期 ✓。
3. **类型一致性**：`parse_sites()` 的字段名（`kind/ptr/size/count/ctor/dtor/line/site`）在任务 3/4 中一致 ✓；`adjudicate()` 返回值字段（`raw_site/size_state/ownership_candidate`）在任务 4 测试与步骤 5 中一致 ✓；`_run_invariants_advisory()` 在任务 1 中唯一命名 ✓。
