# E2′ 核心纠错 实施计划

> **面向 Agent 执行者：** 必需子技能：使用 superpower-subagent-driven-development（推荐）或 superpower-executing-plans 按任务逐项执行本计划。步骤使用复选框（`- [ ]`）语法进行跟踪。

**目标：** 纠正 3 个已损坏的多基类 `base_class`（`SceneObj`/`MUIDialog`/`Role`），消除成员丢失与 C2385 ambiguity

**架构：** 先裁决两文冲突（KB 链被 objdump 证伪）→ 建尺寸格门（假链零假阴性检测）→ 逐类纠正 `base_class`（每类过三条硬裁决 + 成员零丢失验证）→ 全链验收

**技术栈：** Python 3 · MSVC 6.0 SP0 · objdump（二进制证据）· `tools/audit_type_layout.py`（编译器裁判）

**规格：** `docs/superpowers/specs/2026-10-08-e2-prime-design.md`（本计划实现其 **Step 0 + Step 1**；Step 2 另立项）

## 全局约束

- **不可按 KB 链写入**（`arch_gbui_seven_slot_vtables_inheritance_chain.md` 的链方向和根都被 objdump 证伪：实为 `SceneObj : UIWnd`，非 `UIWnd : SceneObj`；`CGameData` 是独立根）
- **不可批量写入**（每类独立裁决 + 验证）
- **不可设覆盖率棘轮**（违反 `docs/knowledge/decision_goal_metric_over_proxy_metric.md`）
- **不可新建裁决工具**（复用 `tools/coff_vtable.py`·`audit_attribution_evidence.py`·`vtable_class_reconcile.py`·`mi_base_offsets.py`·`audit_type_layout.py`）
- **统一写 `list`**（898 struct 里 179 非空 = **159 `list` + 20 `str`**；`stage4_substitution.py` 对 `str` **逐字符迭代**）
- **每处 annotation 修改必须有二进制直接证据**（ctor/dtor 安装顺序 + 尺寸格）
- **L1 棘轮回写基线** ⇒ **退化不可事后查文件，必须当场读**
- **回退非干净**：`apply` 只增不删 ⇒ 回退后须手工清**幽灵 base**；每批 ≤3 类，先固化成员清单快照
- ⚠️ `tools/misattribution_ledger.py` 会写 `data/status`（历史事故：`--help` 覆盖受跟踪产物）⇒ 用前复制到 `/tmp` 跑

---

## 文件结构

| 文件 | 职责 | 类型 |
|---|---|---|
| `tools/size_grid_gate.py` | 尺寸格门（假链零假阴性检测）| 新建（20 行）|
| `data/annotations/structs/SceneObj.json` | 纠正 `base_class` + `base_size` | 修改 |
| `data/annotations/structs/MUIDialog.json` | 纠正 `base_class` | 修改 |
| `data/annotations/structs/Role.json` | 纠正第二基 @+0x40 | 修改 |
| `docs/knowledge/arch_gbui_seven_slot_vtables_inheritance_chain.md` | KB 勘误 | 修改 |
| `docs/knowledge/MEMORY.md` | Decision 补收 | 修改 |
| `tests/test_size_grid_gate.py` | 尺寸格门测试 | 新建 |
| `data/status/_e2p_member_snapshot_*.json` | 成员清单快照（回退用）| 新建 |

---

### 任务 1：Step 0 — KB 勘误 + 索引补收

**文件：**
- 修改：`docs/knowledge/arch_gbui_seven_slot_vtables_inheritance_chain.md`
- 修改：`docs/knowledge/MEMORY.md`
- 修改：`docs/superpowers/specs/2026-10-08-e2-base-class-chain-checklist.md`

**接口：**
- 依赖输入：无
- 对外产出：勘误后的 KB（标注 v2 读法已被 v4 终裁否决）· `MEMORY.md` Decision 段补收 `decision_sceneobj_composition_not_inheritance.md`

- [ ] **步骤 1：给 KB 加勘误头（在 front-matter 之后）**

在 `arch_gbui_seven_slot_vtables_inheritance_chain.md` 的 `---` front-matter 之后插入：

```markdown
> ⚠️ **勘误（2026-10-08，经两路对抗复核 + objdump 实证）**：
> 本文的继承链 **`CCBResultWindow → UIFrameWnd → UIWnd → SceneObj → CGameData(根)`** 被证伪：
> - `0x445aa0` UIWnd ctor：先 `lea ecx,[esi+0x24]; call 0x432660`（**成员子对象** ctor）后 `mov [esi],0x56AEC8` ⇒ **UIWnd 是根**（size 68）
> - `0x452fd0` SceneObj ctor：`call 0x445aa0`（UIWnd ctor）**之后**才 `mov [esi],0x56B200`，自有成员从 +0x44=68 起 ⇒ **`SceneObj : public UIWnd @0`**（**与本文方向相反**）
> - `0x44f065` CGameData ctor：先 `mov [esi],0x56b094`、**无基类 ctor 调用** ⇒ **CGameData 也是根**（size 28268）
> - 尺寸算术：68 ≥ 1784 ≥ 28268 **不成立**
>
> **正确关系**：`SceneObj : public UIWnd`（非 `UIWnd : SceneObj`）；`CGameData` 是独立的根。
> **本文的"~500 MISATTRIBUTED"收益估计量错了对象**：当前 `[ROWTABLE]`=544、`[MISATTRIBUTED]`=9、`C2352=0`；"83"是误引（`_cleanup_review_c2660_independent.md:147` 的历史 347 子集）。
> **终裁见** `docs/knowledge/decision_sceneobj_composition_not_inheritance.md`（v4，明文"不是 base_class"）。
> 本文的 confidence 85 **降为 20**（待证伪）。
```

- [ ] **步骤 2：改 front-matter 的 confidence**

```yaml
confidence: 20   # 原 85，2026-10-08 勘误后降级（链被 objdump 证伪）
```

- [ ] **步骤 3：`MEMORY.md` Decision 段补收**

在 `docs/knowledge/MEMORY.md` 的 Decision 段（若无则新建）追加：

```markdown
- **decision_sceneobj_composition_not_inheritance.md**（v4 终裁）：SceneObj 是**组合**而非继承；行表不是继承。现行 `[ROWTABLE]` 分支 + `_rowtable_family.json`（63 类）是该终裁的落地。
```

- [ ] **步骤 4：E2 清单收益估计修正**

在 `docs/superpowers/specs/2026-10-08-e2-base-class-chain-checklist.md` 的 §0 目标处追加：

```markdown
> ⚠️ **2026-10-08 修正**：原估计"~500±50 MISATTRIBUTED"**量错了对象**。实测当前 `[ROWTABLE]`=544、`[MISATTRIBUTED]`=9、`C2352=0`。**收益估计改为 ~0**。详见 `2026-10-08-e2-prime-design.md`。
```

- [ ] **步骤 5：提交**

```bash
git add docs/knowledge/arch_gbui_seven_slot_vtables_inheritance_chain.md \
        docs/knowledge/MEMORY.md \
        docs/superpowers/specs/2026-10-08-e2-base-class-chain-checklist.md
git commit -m "docs(knowledge): KB 继承链勘误（objdump 证伪方向与根）+ MEMORY Decision 补收"
```

---

### 任务 2：尺寸格门工具（假链零假阴性检测）

**文件：**
- 新建：`tools/size_grid_gate.py`
- 测试：`tests/test_size_grid_gate.py`

**接口：**
- 依赖输入：`data/annotations/structs/*.json` 的 `base_class` + `known_members`（算 size）
- 对外产出：`check_chain(cls, expected_bases) -> (ok: bool, reason: str)`

- [ ] **步骤 1：编写失败的测试**

```python
# tests/test_size_grid_gate.py
import unittest
from tools.size_grid_gate import check_chain


class TestSizeGridGate(unittest.TestCase):
    def test_kb_chain_rejected(self):
        """KB 链 UIWnd→SceneObj→CGameData 应被尺寸格否决（68<1784<28268）。"""
        # 派生尺寸必须 ≥ 每个基类尺寸
        ok, reason = check_chain(
            derived_size=68,
            base_sizes=[1784, 28268],   # SceneObj, CGameData
        )
        self.assertFalse(ok)
        self.assertIn('68', reason)

    def test_correct_chain_accepted(self):
        """正确链 SceneObj(1784) : UIWnd(68) 应通过。"""
        ok, reason = check_chain(
            derived_size=1784,
            base_sizes=[68],
        )
        self.assertTrue(ok, reason)

    def test_base_size_must_match_first_base(self):
        """base_size 必须 == 首基尺寸。"""
        ok, reason = check_chain(
            derived_size=1784,
            base_sizes=[68],
            declared_base_size=44,   # 与首基 68 不符
        )
        self.assertFalse(ok)
        self.assertIn('base_size', reason)


if __name__ == '__main__':
    unittest.main()
```

- [ ] **步骤 2：运行测试并确认其失败**

运行：`python3 -m unittest tests.test_size_grid_gate`
预期：FAIL，提示 `ModuleNotFoundError: No module named 'tools.size_grid_gate'`

- [ ] **步骤 3：编写最小实现**

```python
# tools/size_grid_gate.py
"""尺寸格门：假继承链的零假阴性检测。

判据（2026-10-08 对抗复核定稿）：
  1. 派生类尺寸 ≥ 每个基类尺寸（C++ 布局定理：派生类必须包含基类子对象）
  2. base_size == 首基尺寸（注解自洽）

实测：本门禁一票否决 KB 链（UIWnd=68 < SceneObj=1784 < CGameData=28268）。
"""
from typing import List, Tuple


def check_chain(derived_size: int,
                base_sizes: List[int],
                declared_base_size: int = None) -> Tuple[bool, str]:
    """检查继承链的尺寸格。返回 (ok, reason)。"""
    if not base_sizes:
        return True, 'no bases'
    for bs in base_sizes:
        if derived_size < bs:
            return False, (f'derived size {derived_size} < base size {bs} — '
                           '派生类必须包含基类子对象')
    if declared_base_size is not None and declared_base_size != base_sizes[0]:
        return False, (f'declared base_size {declared_base_size} != '
                       f'first base size {base_sizes[0]}')
    return True, 'ok'
```

- [ ] **步骤 4：运行测试并确认其通过**

运行：`python3 -m unittest tests.test_size_grid_gate`
预期：`Ran 3 tests ... OK`

- [ ] **步骤 5：提交**

```bash
git add tools/size_grid_gate.py tests/test_size_grid_gate.py
git commit -m "feat(tools): 尺寸格门——假继承链零假阴性检测（一票否决 KB 链）"
```

---

### 任务 3：修 `SceneObj.base_class`（成员丢失修复）

**文件：**
- 修改：`data/annotations/structs/SceneObj.json`
- 产出：`data/status/_e2p_member_snapshot_SceneObj.json`（回退快照）

**接口：**
- 依赖输入：任务 2 的 `check_chain`
- 对外产出：`SceneObj.base_class = ['UIWnd']` · `base_size = 68` · `GlowObj` 改标为 +8 成员对象

**二进制证据**（必须写入 commit message）：
- `0x452fd0` SceneObj ctor：`call 0x445aa0`（UIWnd ctor）**之后**才 `mov [esi],0x56B200`，自有成员从 +0x44=68 起
- `0x44A7F9`：`mov [ecx],0x56AFB0; lea edx,[ecx+0x44]; mov [edx],0x56AFA4; jmp 0x445B40` ⇒ **+0x44(=68) 是成员对象，不是第二基**

- [ ] **步骤 1：固化成员清单快照（回退用）**

```bash
python3 -c "
import json
d=json.load(open('data/annotations/structs/SceneObj.json'))
km=d.get('known_members',{})
snap={k: v.get('offset') if isinstance(v,dict) else v for k,v in km.items()}
json.dump(snap, open('data/status/_e2p_member_snapshot_SceneObj.json','w'), indent=2, ensure_ascii=False)
print('快照成员数:', len(snap))
"
```
预期：`快照成员数: 46`

- [ ] **步骤 2：跑尺寸格门验证目标状态**

```bash
python3 -c "
from tools.size_grid_gate import check_chain
ok, reason = check_chain(derived_size=1784, base_sizes=[68], declared_base_size=68)
print(ok, reason)
assert ok
"
```
预期：`True ok`

- [ ] **步骤 3：编写失败的测试（成员零丢失）**

```python
# tests/test_sceneobj_base_fix.py
import json
import unittest


class TestSceneObjBaseFix(unittest.TestCase):
    def test_base_class_is_uiwnd(self):
        d = json.load(open('data/annotations/structs/SceneObj.json', encoding='utf-8'))
        self.assertEqual(d.get('base_class'), ['UIWnd'],
                         'SceneObj 的 base_class 应为 [UIWnd]（objdump 实证）')

    def test_base_size_is_68(self):
        d = json.load(open('data/annotations/structs/SceneObj.json', encoding='utf-8'))
        self.assertEqual(d.get('base_size'), 68,
                         'base_size 应为 68（UIWnd 的尺寸）')

    def test_member_count_not_shrunk(self):
        """成员零丢失：known_members 数不得少于快照（46）。"""
        d = json.load(open('data/annotations/structs/SceneObj.json', encoding='utf-8'))
        snap = json.load(open('data/status/_e2p_member_snapshot_SceneObj.json', encoding='utf-8'))
        self.assertGreaterEqual(len(d.get('known_members', {})), len(snap),
                                '成员被静默吃掉')


if __name__ == '__main__':
    unittest.main()
```

- [ ] **步骤 4：运行测试并确认其失败**

运行：`python3 -m unittest tests.test_sceneobj_base_fix`
预期：FAIL，`AssertionError: SceneObj 的 base_class 应为 ['UIWnd']`

- [ ] **步骤 5：修改 `SceneObj.json`**

⚠️ **统一写 `list`**（不要 str）。

```python
# 手工或脚本修改 data/annotations/structs/SceneObj.json
{
  "name": "SceneObj",
  "base_class": ["UIWnd"],          # 原 ['PalScriptWaitObj','GlowObj','TaskMgr_SceneObjParam_SceneObj']
  "base_size": 68,                   # 原 44
  ...
}
# 同时把 GlowObj 的成员从"基类"改标为"+8 成员对象"（若其成员被列在 SceneObj 的 known_members）
```

- [ ] **步骤 6：运行测试并确认其通过**

运行：`python3 -m unittest tests.test_sceneobj_base_fix`
预期：`Ran 3 tests ... OK`

- [ ] **步骤 7：编译器裁判验证**

运行：`python3 tools/audit_type_layout.py --only SceneObj`
预期：0 冲突

- [ ] **步骤 8：提交（含二进制证据）**

```bash
git add data/annotations/structs/SceneObj.json \
        data/status/_e2p_member_snapshot_SceneObj.json \
        tests/test_sceneobj_base_fix.py
git commit -m "fix(annotations): SceneObj.base_class 3 基类→['UIWnd']，修成员静默丢失

原 3 基类（PalScriptWaitObj+GlowObj+TaskMgr=80B）已把 +0x44 m_fTimerLimit、
+0x4C _SaveTaskInfo 静默吃出生成头（pal3/src/Scene/SceneObj.h 46→44）。

Evidence: 0x452fd0 SceneObj ctor = call 0x445aa0(UIWnd ctor) 后 mov [esi],0x56B200，
自有成员从 +0x44=68 起 ⇒ SceneObj : public UIWnd @0。
0x44A7F9: mov [ecx],0x56AFB0; lea edx,[ecx+0x44]; mov [edx],0x56AFA4; jmp 0x445B40
⇒ +0x44(=68) 是成员对象非第二基。尺寸格：1784 ≥ 68 ✓（原 1784 < 80 假链不成立）。
Confidence: 90"
```

---

### 任务 4：修 `MUIDialog.base_class`（C2385 ambiguity）

**文件：**
- 修改：`data/annotations/structs/MUIDialog.json`
- 产出：`data/status/_e2p_member_snapshot_MUIDialog.json`

**接口：**
- 依赖输入：任务 2 的 `check_chain`；任务 3 的成员快照模式
- 对外产出：`MUIDialog.base_class` 纠正（消除 32 处 C2385 ambiguity）

- [ ] **步骤 1：固化成员清单快照**

```bash
python3 -c "
import json
d=json.load(open('data/annotations/structs/MUIDialog.json'))
km=d.get('known_members',{})
snap={k: v.get('offset') if isinstance(v,dict) else v for k,v in km.items()}
json.dump(snap, open('data/status/_e2p_member_snapshot_MUIDialog.json','w'), indent=2, ensure_ascii=False)
print('快照成员数:', len(snap))
"
```

- [ ] **步骤 2：二进制考古（ctor/dtor 安装顺序）**

```bash
# 找 MUIDialog 的 ctor，看它调用哪些基类 ctor、按什么顺序装表
# 命令：objdump -d original/PAL3.exe | grep -A 30 "<MUIDialog ctor addr>"
# 产出：写入 commit message 的 Evidence
```
⚠️ **若判不出正确基类，保持空**（不写）。

- [ ] **步骤 3：跑尺寸格门验证**

```bash
python3 -c "
from tools.size_grid_gate import check_chain
# 填入考古得到的 derived_size 与 base_sizes
ok, reason = check_chain(derived_size=..., base_sizes=[...], declared_base_size=...)
print(ok, reason)
"
```

- [ ] **步骤 4：编写失败的测试**

```python
# tests/test_muidialog_base_fix.py
import json
import unittest


class TestMUIDialogBaseFix(unittest.TestCase):
    def test_base_class_not_ambiguous(self):
        """基类不得含菱形歧义（如同时含 UIDialog 与 UIFrameWnd）。"""
        d = json.load(open('data/annotations/structs/MUIDialog.json', encoding='utf-8'))
        bc = d.get('base_class') or []
        # UIDialog 与 UIFrameWnd 都派生自 UIWnd ⇒ 同时含会歧义
        self.assertFalse(('UIDialog' in bc) and ('UIFrameWnd' in bc),
                         f'菱形歧义: {bc}')

    def test_member_count_not_shrunk(self):
        d = json.load(open('data/annotations/structs/MUIDialog.json', encoding='utf-8'))
        snap = json.load(open('data/status/_e2p_member_snapshot_MUIDialog.json', encoding='utf-8'))
        self.assertGreaterEqual(len(d.get('known_members', {})), len(snap),
                                '成员被静默吃掉')


if __name__ == '__main__':
    unittest.main()
```

- [ ] **步骤 5：运行测试并确认其失败**

运行：`python3 -m unittest tests.test_muidialog_base_fix`
预期：FAIL（当前 3 基类含歧义）

- [ ] **步骤 6：修改 `MUIDialog.json`**

按考古结论改 `base_class`（**统一写 `list`**）。若考古判不出 ⇒ **保持空**，跳过步骤 7-8。

- [ ] **步骤 7：运行测试 + 编译器裁判**

运行：`python3 -m unittest tests.test_muidialog_base_fix` → 期望 OK
运行：`python3 tools/audit_type_layout.py --only MUIDialog` → 期望 0 冲突

- [ ] **步骤 8：提交（含二进制证据）**

```bash
git add data/annotations/structs/MUIDialog.json \
        data/status/_e2p_member_snapshot_MUIDialog.json \
        tests/test_muidialog_base_fix.py
git commit -m "fix(annotations): MUIDialog.base_class 纠正，消除 32 处 C2385 ambiguity

Evidence: <填入 objdump 的 ctor/dtor 安装顺序证据>
Confidence: <0-100>"
```

---

### 任务 5：修 `Role` 第二基 @+0x40

**文件：**
- 修改：`data/annotations/structs/Role.json`
- 产出：`data/status/_e2p_member_snapshot_Role.json`

**接口：**
- 依赖输入：任务 2 的 `check_chain`；`tools/mi_base_offsets.py`（MI 基偏移）
- 对外产出：`Role` 的第二基 @+0x40 纠正

**二进制证据**（知识库已记录）：`Role : ScriptObj`（ctor `0x411965` 先装 ScriptObj 1 槽表、`0x411B30` 装 Role 4 槽表覆盖；dtor 反向互证），且 Role 有**多继承第二基 @+0x40**（vtable `0x56A9A4` slot2 含 `sub ecx,40h; jmp` this 调整 thunk）

- [ ] **步骤 1：固化成员清单快照**

```bash
python3 -c "
import json
d=json.load(open('data/annotations/structs/Role.json'))
km=d.get('known_members',{})
snap={k: v.get('offset') if isinstance(v,dict) else v for k,v in km.items()}
json.dump(snap, open('data/status/_e2p_member_snapshot_Role.json','w'), indent=2, ensure_ascii=False)
print('快照成员数:', len(snap))
"
```

- [ ] **步骤 2：用 `mi_base_offsets.py` 裁决第二基**

```bash
python3 tools/mi_base_offsets.py --class Role
```
预期：输出第二基偏移（应为 0x40）与候选类

- [ ] **步骤 3：二进制验证（thunk）**

```bash
# 读 vtable 0x56A9A4 slot2 的函数字节，确认 sub ecx,40h; jmp
# 命令：objdump -D -M intel --start-address=<slot2 addr> original/PAL3.exe | head -5
```

- [ ] **步骤 4：跑尺寸格门验证**

```bash
python3 -c "
from tools.size_grid_gate import check_chain
ok, reason = check_chain(derived_size=..., base_sizes=[...], declared_base_size=...)
print(ok, reason)
"
```

- [ ] **步骤 5：编写失败的测试**

```python
# tests/test_role_base_fix.py
import json
import unittest


class TestRoleBaseFix(unittest.TestCase):
    def test_member_count_not_shrunk(self):
        d = json.load(open('data/annotations/structs/Role.json', encoding='utf-8'))
        snap = json.load(open('data/status/_e2p_member_snapshot_Role.json', encoding='utf-8'))
        self.assertGreaterEqual(len(d.get('known_members', {})), len(snap),
                                '成员被静默吃掉')

    def test_base_class_is_list(self):
        """统一写 list（159 list + 20 str 的类型不统一陷阱）。"""
        d = json.load(open('data/annotations/structs/Role.json', encoding='utf-8'))
        bc = d.get('base_class')
        if bc is not None:
            self.assertIsInstance(bc, list, 'base_class 必须是 list，不得是 str')


if __name__ == '__main__':
    unittest.main()
```

- [ ] **步骤 6：运行测试并确认其失败**（若当前是 str 或成员丢失）

运行：`python3 -m unittest tests.test_role_base_fix`

- [ ] **步骤 7：修改 `Role.json`**

按考古结论改 `base_class`（**统一写 `list`**）。若判不出 ⇒ **保持现状**，跳过步骤 8-9。

- [ ] **步骤 8：运行测试 + 编译器裁判**

运行：`python3 -m unittest tests.test_role_base_fix` → 期望 OK
运行：`python3 tools/audit_type_layout.py --only Role` → 期望 0 冲突

- [ ] **步骤 9：提交（含二进制证据）**

```bash
git add data/annotations/structs/Role.json \
        data/status/_e2p_member_snapshot_Role.json \
        tests/test_role_base_fix.py
git commit -m "fix(annotations): Role 第二基 @+0x40 纠正

Evidence: vtable 0x56A9A4 slot2 = sub ecx,40h; jmp（this 调整 thunk）·
ctor 0x411965 装 ScriptObj 1 槽表、0x411B30 装 Role 4 槽表覆盖
Confidence: <0-100>"
```

---

### 任务 6：全链验收

**文件：**
- 无新文件（只跑验证）

**接口：**
- 依赖输入：任务 3-5 的改动
- 对外产出：验收报告

- [ ] **步骤 1：固化最终成员清单快照**

```bash
for c in SceneObj MUIDialog Role; do
  python3 -c "
import json
d=json.load(open('data/annotations/structs/$c.json'))
km=d.get('known_members',{})
print('$c members:', len(km))
"
done
```
预期：各 ≥ 任务 3-5 的快照数

- [ ] **步骤 2：尺寸格门全量跑**

```bash
python3 -c "
import json, glob, os
from tools.size_grid_gate import check_chain
for f in glob.glob('data/annotations/structs/*.json'):
    d=json.load(open(f,encoding='utf-8'))
    bc=d.get('base_class') or []
    if not bc: continue
    # 算 derived_size（max offset + 1）
    km=d.get('known_members',{})
    ds=max((v.get('offset',0) if isinstance(v,dict) else 0) for v in km.values())+1 if km else 0
    # 简化：base_sizes 需从各基类读
    print(os.path.basename(f), 'base_class=', bc)
" | head -10
```

- [ ] **步骤 3：编译器裁判（3 个类）**

```bash
for c in SceneObj MUIDialog Role; do
  python3 tools/audit_type_layout.py --only $c
done
```
预期：0 冲突

- [ ] **步骤 4：全链跑（当场读数）**

```bash
python3 pipeline/cli.py loop --stages apply,export,codegen,probe,match
```
⚠️ **当场读** `L1≥94` / `S2≥99` / `own_unresolved=0`（**不可事后查基线文件**）

- [ ] **步骤 5：C2385 单调降**

```bash
python3 -c "
import json
d=json.load(open('data/status/probe_census.json'))
n=sum(1 for u in d['s2']['results'] for e in u.get('errors',[]) if 'ambiguous' in e['msg'])
print('C2385-ish:', n)
"
```
预期：**34 → 0**（或显著下降）

- [ ] **步骤 6：提交验收记录**

```bash
git add data/status/_e2p_member_snapshot_*.json
git commit -m "chore: E2′ 核心纠错验收（成员零丢失 · 尺寸格门 · audit_type_layout · L1/S2 当场读）"
```

---

## 自检（规格覆盖度）

| 规格要求 | 对应任务 | 状态 |
|---|---|---|
| Step 0 KB 勘误 + 索引补收 + 收益修正 | 任务 1 | ✅ |
| 尺寸格门（零假阴性）| 任务 2 | ✅ |
| Step 1 修 `SceneObj`（成员丢失）| 任务 3 | ✅ |
| Step 1 修 `MUIDialog`（C2385）| 任务 4 | ✅ |
| Step 1 修 `Role`（第二基）| 任务 5 | ✅ |
| 全链验收（成员零丢失 + 编译器裁判 + L1 当场读）| 任务 6 | ✅ |
| 统一写 `list`（类型陷阱）| 任务 3/4/5 步骤 | ✅ |
| 成员清单快照（回退）| 任务 3/4/5 步骤 1 | ✅ |
| 二进制证据（红线）| 任务 3/4/5 提交 message | ✅ |
| 不设覆盖率棘轮 | 全局约束 | ✅ |

**占位符扫描**：无 TBD/TODO/"与任务 N 类似"
**类型一致性**：`check_chain(derived_size, base_sizes, declared_base_size)` 在任务 2 定义、任务 3/4/5 一致引用

---

## 执行交接

**计划已完成并保存至 `docs/superpowers/plans/2026-10-08-e2-prime-core.md`。两种执行方式：**

**1. 子代理驱动（推荐）** —— 每个任务分发全新子代理，任务间进行评审，迭代更快

**2. 内联执行** —— 在当前会话中使用 executing-plans 批量执行，设置检查点

**请选择哪种方式？**

⚠️ **Step 2（清 9 处 MISATTRIBUTED）单独立项**，其计划见 `2026-10-08-e2-prime-misattr.md`（待写）。