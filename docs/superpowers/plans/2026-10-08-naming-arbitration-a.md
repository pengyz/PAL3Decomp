# 命名仲裁·交付物 A 实施计划

> **面向 Agent 执行者：** 必需子技能：使用 superpower-subagent-driven-development（推荐）或 superpower-executing-plans 按任务逐项执行本计划。步骤使用复选框（`- [ ]`）语法进行跟踪。

**目标：** 修 120 个同址多 `methods` 声明中**可机械消解的 24 个**，并落地确定性修复 + 冲突检测器

**架构：** 先只读审计定位可解项 → 按 vtable `from:None` 根表槽判属主 → 删除 `vtable_gap_fill_v1` 污染注入的重复条目 → 修 `audit_attribution_evidence.py` 的自比对漏洞 → 5 个站点统一改走 `annotation_view.iter_structs`（已 sorted）→ 确定性测试兜底

**技术栈：** Python 3 · MSVC 6.0 SP0（`tools/compilers/msvc6.0/`）· wine_cl.sh · Ninja

**规格：** `docs/superpowers/specs/2026-10-08-naming-arbitration-design.md`（本计划实现其**交付物 A**；交付物 B 另立项）

## 全局约束

- **L1 字节安全**：`this->UIWnd::OnMessage()` 直调（可内联）vs `this->OnMessage()` 虚分派（`FF 10`），字节不同 ⇒ 改发射形态须逐点字节证据（`ast_transform.py:1448-1451`）
- **多类声明合法**：`CGameData.h:208` 与 `UIWnd.h:45` 并存 `// 0x00445D10` 是合法虚覆写，**不得去重**（`emit_headers.py:938-940`）
- **禁止双真相源**：不新建第 8/9 个归属工具；扩展 `audit_attribution_evidence.py`
- **禁止批量未验证改动**：每个偏移/类型变更必须逐一验证（`vtable_gap_fill_v1` 是 120 冲突根源）
- **禁止仅凭 signature this 修归属**：必须有 decomp member access evidence
- **export 不读 annotation**：`export_full.py` 只能从 IDB 读
- **codegen 注解读取经单一读点**：`pipeline/gen/annotation_view.py`
- **每处 annotation 修改必须有二进制直接证据**（A 级：指令中的 reg+disp32、绝对地址）
- **回退**：注解 924 文件 git 跟踪可回退；IDB 命名是**派生状态**（`apply` 幂等、注解驱动，`apply_annotations.py:1952` "Un-name stale functions"）⇒ 重新 `apply` 即可

---

## 文件结构

| 文件 | 职责 | 类型 |
|---|---|---|
| `tools/audit_attribution_evidence.py` | 归属证据审计（修自比对漏洞 + 加三元组输出） | 修改 |
| `pipeline/ida/apply_annotations.py` | IDB 命名（走单一读点） | 修改 |
| `pipeline/ida/export_full.py` | decomp 导出（走单一读点） | 修改 |
| `pipeline/check_annotations.py` | 注解一致性闸（走单一读点） | 修改 |
| `tools/verify_fix.py` | 证物报告（走单一读点） | 修改 |
| `tools/audit_retn_param_count.py` | ret-N 参数计数（走单一读点） | 修改 |
| `pipeline/gen/annotation_view.py` | **单一读点**（已 sorted，复用不改） | 只读 |
| `tests/test_annotation_determinism.py` | 确定性测试 | 新建 |
| `data/annotations/structs/*.json` | 注解（删污染条目） | 修改 |

---

### 任务 1：只读审计 — 枚举 120 冲突 + 机械消解 24 个

**文件：**
- 新建：无（只读脚本，输出落 `data/status/_naming_audit_A1.json`）
- 只读：`data/annotations/structs/*.json`

**接口：**
- 依赖输入：无
- 对外产出：`data/status/_naming_audit_A1.json`，结构：
  ```json
  {
    "multi_decl_addrs": ["0x...", ...],           // 120 个同址多声明地址
    "resolvable": [{"addr": "0x...", "owner": "Cls", "evidence": "vtable_from_null_unique"}],  // 24 个
    "unresolved": [{"addr": "0x...", "claimants": ["A","B"], "reason": "multiple_from_null"}]   // 96 个
  }
  ```

- [ ] **步骤 1：编写只读审计脚本**

```python
# tools/audit_naming_conflicts.py  （临时脚本，A1 用完即可弃）
import json, os, collections

STRUCTS_DIR = 'data/annotations/structs'

def load():
    addr_to_classes = collections.defaultdict(set)
    class_vtable_from = {}   # (cls, addr) -> from
    for fn in sorted(os.listdir(STRUCTS_DIR)):
        if not fn.endswith('.json'):
            continue
        cls = fn[:-5]
        d = json.load(open(os.path.join(STRUCTS_DIR, fn), encoding='utf-8'))
        for addr in (d.get('methods') or {}).keys():
            addr_to_classes[addr].add(cls)
        for vt in d.get('vtables') or []:
            for slot in vt.get('slots') or []:
                a = slot.get('addr')
                if a:
                    class_vtable_from[(cls, a)] = slot.get('from')
    return addr_to_classes, class_vtable_from

def audit():
    addr_to_classes, class_vtable_from = load()
    multi = {a: c for a, c in addr_to_classes.items() if len(c) > 1}
    resolvable, unresolved = [], []
    for addr, classes in sorted(multi.items()):
        # vtable 槽 from=None 的类 = 自认原创（根）
        roots = [c for c in classes
                 if class_vtable_from.get((c, addr), '_') is None]
        if len(roots) == 1:
            resolvable.append({
                'addr': addr, 'owner': roots[0],
                'evidence': 'vtable_from_null_unique',
                'claimants': sorted(classes)})
        else:
            unresolved.append({
                'addr': addr, 'claimants': sorted(classes),
                'reason': 'multiple_from_null' if roots else 'no_from_null',
                'roots': sorted(roots)})
    return {'multi_decl_addrs': sorted(multi.keys()),
            'resolvable': resolvable, 'unresolved': unresolved}

if __name__ == '__main__':
    out = audit()
    json.dump(out, open('data/status/_naming_audit_A1.json', 'w'),
              indent=2, ensure_ascii=False)
    print('multi=%d resolvable=%d unresolved=%d'
          % (len(out['multi_decl_addrs']), len(out['resolvable']),
             len(out['unresolved'])))
```

- [ ] **步骤 2：运行审计脚本**

运行：`python3 tools/audit_naming_conflicts.py`
预期输出：`multi=120 resolvable=24 unresolved=96`
（若数字不同，**停下记录实际值并报告**，不要硬凑）

- [ ] **步骤 3：人工核对 3 个抽样（二进制证据）**

对 `resolvable` 的前 3 项，用 objdump 核对属主：

```bash
for A in 0x00445D10 0x00445B90 0x00445E70; do
  echo "=== $A ==="
  python3 -c "
import struct
d=open('original/PAL3.exe','rb').read()
pe=struct.unpack_from('<I',d,0x3c)[0]
nsec=struct.unpack_from('<H',d,pe+6)[0]
opt=pe+24
base=struct.unpack_from('<I',d,opt+28)[0]
va=int('$A',16)
for i in range(nsec):
    o=opt+struct.unpack_from('<H',d,pe+20)[0]+i*40
    name=d[o:o+8].rstrip(b'\x00').decode('latin1')
    sva=struct.unpack_from('<I',d,o+12)[0]
    vs=struct.unpack_from('<I',d,o+8)[0]
    if base+sva <= va < base+sva+vs:
        raw=struct.unpack_from('<I',d,o+20)[0]
        fo=raw+(va-(base+sva))
        print(name, hex(va), d[fo:fo+12].hex())
"
done
```

预期：每址的字节与 `resolvable[i].evidence` 的归属判断一致
（如 `0x00445D10` = `33c0c20c00` = `xor eax,eax; ret 0xC` ⇒ 三参 `__thiscall` 空实现 ⇒ 基类默认方法）

- [ ] **步骤 4：提交审计产物**

```bash
git add -f data/status/_naming_audit_A1.json
git commit -m "audit(naming): A1 枚举 120 冲突 + 机械消解 24 个（vtable from=None 唯一根）"
```

---

### 任务 2：修 `audit_attribution_evidence.py` 的自比对漏洞

**文件：**
- 修改：`tools/audit_attribution_evidence.py`（`reconcile()` 与 `vtable_evidence()`）
- 测试：`tests/test_audit_attribution_evidence.py`

**接口：**
- 依赖输入：任务 1 的 `_naming_audit_A1.json`（仅作对照，不直接读）
- 对外产出：`audit_attribution_evidence.py` 的 `reconcile()` 不再对"owner 恒等于 current_cls"的情况判 `consistent`

**背景**（kiro 发现的缺陷）：
`vtable_evidence()` 里 `src = s.get('from') or cls` 会把当前类自己也算成一个 owner 候选；
`reconcile()` 判断 `current_cls in ancestors(owner)` 时，`current==owner` 恒真 ⇒ 自比对漏洞
⇒ 对 `0x00445D10` 这类案例**完全失明**（实测报 `consistent` 而非 `contradiction`）。

- [ ] **步骤 1：编写失败的测试**

```python
# tests/test_audit_attribution_evidence.py 追加
def test_reconcile_detects_self_comparison_vulnerability():
    """owner 恒等于 current_cls 时不应判 consistent（自比对漏洞）。

    场景：CGameData 的 methods 声明 0x00445D10，但 CGameData 自己的 vtable 槽
    标 from='UIWnd'（即 CGameData 自认继承自 UIWnd）。
    正确判定应为 contradiction，而非 consistent。
    """
    from tools.audit_attribution_evidence import reconcile, vtable_evidence
    # 构造最小输入：1 条 methods 声明 + 1 条 vtable 槽证据
    cls = 'CGameData'
    addr = '0x00445D10'
    claims = [(cls, addr)]                       # methods: CGameData 声明
    vtables = [{'addr': addr, 'from': 'UIWnd'}]  # vtable: 自认继承自 UIWnd
    verdict, detail = reconcile(cls=cls, addr=addr,
                                claims=claims, vtables=vtables,
                                ancestors=lambda c: {c})
    assert verdict == 'contradiction', \
        'owner==current_cls 不应恒真；应依据 vtable from 判定'
```

- [ ] **步骤 2：运行测试并确认其失败**

运行：`python3 tests/test_audit_attribution_evidence.py`
预期：FAIL，提示 `AssertionError: owner==current_cls 不应恒真`
（若 `reconcile` 签名与上述不一致，**先读实际签名再改测试**，不要改实现迁就测试）

- [ ] **步骤 3：编写最小实现（修自比对漏洞）**

```python
# tools/audit_attribution_evidence.py — reconcile() 内
# 旧：src = s.get('from') or cls
# 新：from 为空时**不**把 cls 自己当 owner 候选（那正是漏洞）
def vtable_evidence(slots, cls):
    out = []
    for s in slots or []:
        src = s.get('from')
        if src:
            out.append((cls, s.get('addr'), src))
        # from 为空 ⇒ 该槽由 cls 自己原创 ⇒ 属主=cls，但**不**进 owner 候选池
        # （reconcile 的判断依据是 vtable 的 from，不是 methods 的声明方）
    return out
```

并在 `reconcile()` 里把判断改为：
```python
# 旧：verdict = 'consistent' if current_cls in ancestors(owner) else 'contradiction'
# 新：owner 来自 vtable 的 from（非 cls 自己）时，才作属主判断
if owner and owner != current_cls:
    verdict = 'consistent' if current_cls in ancestors(owner) else 'contradiction'
elif owner == current_cls:
    # 自比对 ⇒ 不下结论，交由 from 证据判定
    verdict = 'contradiction' if vtable_says_other else 'unchecked'
```

- [ ] **步骤 4：运行测试并确认其通过**

运行：`python3 tests/test_audit_attribution_evidence.py`
预期：PASS；且全量 `python3 tests/test_audit_attribution_evidence.py` 不破坏既有用例

- [ ] **步骤 5：提交**

```bash
git add tools/audit_attribution_evidence.py tests/test_audit_attribution_evidence.py
git commit -m "fix(attribution): 修 reconcile() 自比对漏洞（owner 恒等于 current_cls 时不再判 consistent）"
```

---

### 任务 3：C1 扩面 — 5 个站点统一改走 `annotation_view.iter_structs`

**文件：**
- 修改：`pipeline/ida/apply_annotations.py:1331`
- 修改：`pipeline/ida/export_full.py:197,218`
- 修改：`pipeline/check_annotations.py:38`
- 修改：`tools/verify_fix.py:388`
- 修改：`tools/audit_retn_param_count.py:137`
- 只读：`pipeline/gen/annotation_view.py:41`（`iter_structs` 已 `sorted(glob.glob(...))`）

**接口：**
- 依赖输入：`annotation_view.iter_structs()`（已存在，签名不变）
- 对外产出：5 个站点的注解遍历顺序**确定性**（产物 byte-equal）

- [ ] **步骤 1：核实 `annotation_view.iter_structs` 签名**

```bash
sed -n '35,55p' pipeline/gen/annotation_view.py
```
预期：看到 `def iter_structs(...)` 或 `def iter_struct_files(...)`，内部用 `sorted(glob.glob(...))`
**若不是 sorted，停下报告**（说明规格前提有误）

- [ ] **步骤 2：编写失败的测试（顺序确定性）**

```python
# tests/test_annotation_determinism.py 追加
import os, sys, json, random, importlib

def test_five_sites_use_single_sorted_read_point(monkeypatch):
    """5 个站点不得再用 os.listdir/glob.glob 裸遍历。"""
    sites = [
        ('pipeline/ida/apply_annotations.py', 'os.listdir'),
        ('pipeline/ida/export_full.py', 'glob.glob'),
        ('pipeline/check_annotations.py', 'os.listdir'),
        ('tools/verify_fix.py', 'os.listdir'),
        ('tools/audit_retn_param_count.py', 'os.listdir'),
    ]
    for path, bad_call in sites:
        src = open(path, encoding='utf-8').read()
        # 该文件内不应再有裸的 os.listdir( 或 glob.glob( 调用注解目录
        assert bad_call + '(' not in src or 'annotation_view' in src, \
            f'{path} 仍用 {bad_call}，未改走 annotation_view'
```

- [ ] **步骤 3：运行测试并确认其失败**

运行：`python3 tests/test_annotation_determinism.py`
预期：FAIL（5 个站点仍用 `os.listdir`/`glob.glob`）

- [ ] **步骤 4：逐站点改走单一读点**

以 `apply_annotations.py:1331` 为例（其余 4 处同理）：

```python
# pipeline/ida/apply_annotations.py
# 旧：
# for fname in os.listdir(structs_dir):
#     if not fname.endswith(".json"): continue
#     ...
# 新：
from pipeline.gen.annotation_view import iter_structs
for fname, sdata in iter_structs():
    # sdata 已是解析后的 dict（含 name/methods/vtables）
    sname = sdata.get('name') or fname.replace('.json', '')
    structs[sname] = sdata
    ...
```

⚠️ **注意**：`iter_structs` 返回的可能是 `(fname, data)` 元组或单值 —— **先读实际签名再改**；
改完后 5 处产物必须 **byte-equal**（用 `git diff` 确认无意外改动）。

- [ ] **步骤 5：运行测试并确认其通过**

运行：`python3 tests/test_annotation_determinism.py`
预期：PASS

- [ ] **步骤 6：提交**

```bash
git add pipeline/ida/apply_annotations.py pipeline/ida/export_full.py \
        pipeline/check_annotations.py tools/verify_fix.py \
        tools/audit_retn_param_count.py tests/test_annotation_determinism.py
git commit -m "fix(determinism): 5 个注解遍历站点统一走 annotation_view.iter_structs（已 sorted）"
```

---

### 任务 4：删除 24 个可解项的污染条目

**文件：**
- 修改：`data/annotations/structs/*.json`（24 个地址的 `methods` 重复条目）
- 只读：`data/status/_naming_audit_A1.json`（任务 1 产出）

**接口：**
- 依赖输入：任务 1 的 `resolvable` 列表（24 个 `addr` + `owner`）
- 对外产出：24 个地址的 `methods` 只保留 `owner` 类的声明

⚠️ **红线**：每处改动必须有二进制直接证据。任务 1 步骤 3 已抽样核对 3 个；
**本任务须对剩余 21 个逐一核对**（用同一 objdump 脚本），核对记录写入 commit message。

⚠️ **不得动 vtable 继承记录**（`vtables[].slots[].from` 保留）。
⚠️ **不得动合法多类声明**（`emit_headers.py:938-940` 的豁免）。

- [ ] **步骤 1：生成删除清单（只读）**

```python
# tools/gen_purge_list.py（临时脚本）
import json
audit = json.load(open('data/status/_naming_audit_A1.json'))
for r in audit['resolvable']:
    addr, owner = r['addr'], r['owner']
    for cls in r['claimants']:
        if cls != owner:
            print(f'{cls}.json  移除 methods[{addr}]  （属主={owner}）')
```

- [ ] **步骤 2：逐条核对二进制证据**

对 21 个未抽样项，用任务 1 步骤 3 的 objdump 脚本核对；
**核对结果写入 `data/status/_naming_audit_A1.json` 的 `evidence_checked` 字段**。

- [ ] **步骤 3：执行删除（逐条，不批量）**

⚠️ **禁止批量**：每改一个文件，跑一次 `python3 tools/audit_attribution_evidence.py` 确认无新增 contradiction。

```python
# 伪代码（实际执行须逐文件手工改或逐文件跑脚本）
import json, os
for cls, addr in purge_list:
    p = f'data/annotations/structs/{cls}.json'
    d = json.load(open(p, encoding='utf-8'))
    d['methods'].pop(addr, None)
    json.dump(d, open(p, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
```

- [ ] **步骤 4：验证无新增 contradiction**

运行：`python3 tools/audit_attribution_evidence.py`
预期：contradiction 数 **不增**（基线 80，见 kiro 复核）

- [ ] **步骤 5：提交**

```bash
git add data/annotations/structs/*.json data/status/_naming_audit_A1.json
git commit -m "fix(naming): 删除 24 个可解项的 vtable_gap_fill_v1 污染条目（逐条二进制核对）"
```

---

### 任务 5：确定性测试兜底

**文件：**
- 修改：`tests/test_annotation_determinism.py`（任务 3 已建）

**接口：**
- 依赖输入：任务 2-4 的改动
- 对外产出：`tests/test_annotation_determinism.py` 可独立运行，验证确定性

- [ ] **步骤 1：补充 shuffle 确定性测试**

```python
# tests/test_annotation_determinism.py 追加
def test_load_annotations_deterministic_under_shuffle(monkeypatch):
    """shuffle os.listdir 30 次，winner 变动应为 0。"""
    import importlib, random
    import pipeline.ida.apply_annotations as aa
    importlib.reload(aa)
    real_listdir = os.listdir

    def shuffled(path):
        out = real_listdir(path)
        random.shuffle(out)
        return out

    winners = set()
    for seed in range(30):
        random.seed(seed)
        monkeypatch.setattr(os, 'listdir', shuffled)
        fns = aa.load_annotations()['functions']
        winners.add(frozenset((a, v.get('class'), v.get('name'))
                              for a, v in fns.items()))
        monkeypatch.undo()
    assert len(winners) == 1, f'winner 随机：{len(winners)} 种不同结果'
```

- [ ] **步骤 2：运行测试并确认其通过**

运行：`python3 tests/test_annotation_determinism.py`
预期：PASS
**若 FAIL**（winner 仍有变动）⇒ 说明任务 2-4 未完全修复 ⇒ 停下报告

- [ ] **步骤 3：提交**

```bash
git add tests/test_annotation_determinism.py
git commit -m "test(determinism): shuffle 30 次断言 winner 变动==0（含 17 对同名 struct 覆盖）"
```

---

## 自检（规格覆盖度）

| 规格要求 | 对应任务 | 状态 |
|---|---|---|
| A1 只读审计 120 冲突 | 任务 1 | ✅ |
| A2 处理 24 个可解项 | 任务 4 | ✅ |
| A3 修 `audit_attribution_evidence.py` 自比对漏洞 | 任务 2 | ✅ |
| A4 C1 扩面 5 站点 | 任务 3 | ✅ |
| A5 确定性测试 | 任务 3 + 5 | ✅ |
| 二进制证据（红线）| 任务 1 步骤 3 + 任务 4 步骤 2 | ✅ |
| 不动合法多类声明 | 任务 4 ⚠️ 注 | ✅ |
| 不新建归属工具 | 任务 2（扩展） | ✅ |

**占位符扫描**：无 TBD/TODO/「与任务 N 类似」
**类型一致性**：`reconcile()`/`vtable_evidence()` 签名在任务 2 定义、任务 4 引用一致

---

## 执行交接

**计划已完成并保存至 `docs/superpowers/plans/2026-10-08-naming-arbitration-a.md`。两种执行方式：**

**1. 子代理驱动（推荐）**——每个任务分发全新子代理，任务间进行评审，迭代更快

**2. 内联执行**——在当前会话中使用 executing-plans 批量执行，设置检查点

**请选择哪种方式？**

⚠️ **交付物 B**（owner schema + 二进制裁判 + 棘轮治理）**单独立项**，其计划见 `2026-10-08-naming-arbitration-b.md`（待写）。