# Task 7 报告：虚调用转换（三形态识别）

- **状态**：DONE_WITH_CONCERNS
- **提交**：`7ee6041fb`（2 files, +1101/−53：`stage3_cleanup.py` 620 行变更 + 新测试 534 行）
- **一行测试摘要**：新增 `tests/test_vtable_call_transform.py` **27 passed / 0 failed**；前序 35（slot_order）/38（slot_classifier）/68（sig_infer）/46（layout_assert）/4（stub_dedup）/5（slot_index）/4（owner_self_drop）/1+4skip（deref_preserved）全无回退；`test_qualified_vftable_tristate` 的 1 项失败经**旧实现逐字节比对**证明是既有失败（非本任务引入）。

交付文件（只这两个，`git add` 也只加这两个）：

- `pipeline/gen/stages/stage3_cleanup.py`（+563 / −53，删除行全部是 legacy 分支的重缩进，无语义删除）
- `tests/test_vtable_call_transform.py`（新增）

---

## 1. 交付内容

### 1.1 三形态识别（都在 `_resolve_vftable_calls_ast` 的解码分支内）

新增解码器 `_decode_vptr_dispatch(call_node, vptr_locals)`，与既有 `_decode_vtbl_call`（`__vftable` 锚定）**并列**而非替换：

| 形态 | 输入（stage3 解码时的文本） | 输出 |
|---|---|---|
| 1 inline | `(*(R (__thiscall **)(Cls *, ...))(*(_DWORD *)OBJ + N))(OBJ, args)` | `OBJ->Method(args)` |
| 2 局部 vftable 变量 | `v5 = *(T *)OBJ;` … `(*(R …)(v5 + N))(OBJ, args)` | `OBJ->Method(args)` |
| 3 裸 vptr 读（偏移 0） | `(*(R …)(*(void **)(OBJ)))(OBJ)` / `*(T *)OBJ->_tail_000` | `OBJ->Method(args)` |

支撑件：

- `_fn_cast_of()`：取「函数指针 cast」的 `(cast_node, value_node, 解引用层数)`，要求 `stars ≥ 1` 且 cast 类型是**成员函数指针的指针**（`**`）——这是"这是虚派发而不是普通函数指针调用"的最低门槛。
- `_vptr_read_of()`：把 slot base 译成 `(对象, 字节偏移, 形态)`。**只接受有显式 vptr 读的形态**；裸标识符/成员链一律返回 `None`（见 §5 假阳性防护）。
- `_collect_vptr_locals()`：形态 2 的窗口——扫本函数（`run()` 一次调用 = 一个函数）的 `V = <vptr 读>` 赋值，建立 `V → 对象` 表。源形态含 `*(T *)OBJ`、`*(T *)OBJ->_tail_000`、`OBJ->__vftable`。
- `_strip_outer_parens()` / `_split_expr_offset()`：tree-sitter 的 slot base 常是 `parenthesized_expression`（`(*(_DWORD *)this + 4)`），**必须**先剥完整外层括号再解析末尾 `+ N`（首版漏掉此步 ⇒ 15 条测试红；这是 TDD 抓到的第一个真 bug）。
- `_same_self_arg()`：首个实参必须**就是** vptr 的持有者（`this` 一致），否则记 `self_arg_mismatch` 并保留原文。

### 1.2 名称解析链（不用 mangling）

`_load_vtbl_index()` 懒加载（`_VTBL_INDEX`，测试可注入）：

```
类名(cast 首参) → 注解 vtables[0].addr → IDB vtbl_<ADDR>.data_members
                → 注解 methods[槽地址].name（缺省回落 IDB data_members[i].name）
```

数据源只读：`data/annotations/structs/*.json`（`vtables[0].addr` / `slots[i].addr` / `methods` / `known_methods`）+ `asm/pal3/ida_structs.json`（`vtbl_<ADDR>` 与类结构 `methods`）。**不使用 mangling**。实测规模：80 个声明了 `vtables[]` 的类，其中 79 个能在 IDB 找到 `vtbl_<ADDR>` 结构（92 个 `vtbl_*` 结构）。

解析结果（实测全语料，`_resolve_vtbl_name_chain` 被调用 907 次，其中 113 次给出名字）。

`::` 限定一律剥掉（`_vtbl_method_name`）⇒ **绝不发射 `obj->Base::Method()`**（限定调用抑制虚派发）；同时拒绝 `_tail_000` / `sub_XXXX` / `unknown*` 等 IDB 占位名。

### 1.3 ★ 头文件一致性护栏（本任务实测发现的**真缺陷**，已修）

仅"链能给出名字"还不够：头文件只为**该类声明过的方法名**发 `virtual`，缺失槽发占位名 `slot_<i>`（`emit_headers.py:2309-2327`）。实测反例：

- `UIWnd` 槽 3（0x00442420）在 IDB `vtbl_0056AE2C.data_members[3]` 里叫 `Destroy`；
- 但该类的 `Destroy` 声明在 **0x0043BBB0 且非 virtual**（`pal3/src/UI/UIWnd.h:45: void Destroy();`），
  `UIWnd.json` 的 `methods` 也只把 0x0043BBB0 记为 `Destroy`；
- 头文件里槽 3 是 `virtual void slot_3();`（`pal3/src/UI/UIWnd.h:41`）。

⇒ 若直接发射 `p->Destroy(...)`，会绑定到**同名的另一个非虚函数**（直接调用 ⇒ 字节必不匹配，且实参个数也可能不符）。故护栏为：

```
名字必须在本类有声明；若有声明，其声明地址必须包含本槽地址
  → 否则 name_declared_at_other_address
名字在本类完全没有声明（且槽地址可得）
  → 否则 name_not_declared_for_class
```

护栏的依据表 `class_decl{类: {名字: {声明地址}}}` 与头文件的名字来源对齐：注解 `methods`、注解 `known_methods`（人工策展，如 `UIWnd.known_methods["6"] = OnMessage@0x00445D10`）、IDB 类结构 `methods`。**已知保守处（诚实披露）**：头文件的头号名字来源是 decomp JSON 的 `Cls::Method`（`emit_headers.collect_methods` 主源），本索引**不扫 3598 个 decomp 文件**，所以"仅由 decomp 声明"的名字会被记进台账而不是转换——宁可少转不可错转；代价可量化（当前 113 个转换的名字全部命中廉价三源，见 §4）。

## 2. 字节偏移语义（二进制实证）

`*(_DWORD *)X + 8` 里的 **8 是字节偏移**，槽下标 = 8/4 = 2（**不是** `+8` 即槽 8，也不是 `+8` 再乘 4）。证据：

```
C2DSpark::C2DSpark @0x4D5AB0（original/PAL3.exe.asm）
    mov  ecx, dword_BFDA60
    mov  edx, [ecx]
    call dword ptr [edx+8]
⇔ decomp `(*(int (__thiscall **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr->_tail_000 + 8))(gfxMgr, aTga)`
⇒ 槽2 = gbGfxManager::NewTexture(char const *)（实参 aTga 与声明相符）
```

对照：`AStarPathFinder::TryExpand @0x4012A0` 的 `call dword ptr [eax+4]` ⇔ `*(_DWORD *)this + 4`
（槽1 = `IsInBounds`，实参 `(this, nTileX, nTileY)` 相符）。

另一族 `obj->__vftable + N` 里的 N 是**槽下标**（vtable 结构体指针运算），仍由既有 `_decode_vtbl_call` / `_resolve_vtbl_method` 处理，**本任务不改其语义**（该族在当前 decomp 语料里 **0 命中**：全文 `__vftable` 出现次数 = 0，故 legacy 分支实际未触发 —— 这也解释了为什么 `_tail_000`/`*(_DWORD *)` 家族全部落空）。

## 3. 失败输出契约

识别为虚调用却无法转换时：

1. **原文本逐字保留**（除 `run()` 开头统一剔除的 `__thiscall ` 外零改动）；绝不伪造 `_tail_00N`、伪成员名之类"裸偏移"形态；
2. **记账**到 `data/status/vtable_transform_failures.md`（追加 + **幂等**：每行一个
   `(位置, 形态, cls_hint, 字节偏移, 原因)` 唯一站点；跨进程靠回读既有行去重）；
3. 既有 `__vftable` 路径的 stub 语义（`pal3_vtbl_unk_*` + `[VFTABLE-STUB]`）**逐字不变** ——
   有回归测试 `test_existing_vftable_stub_semantics_preserved` 固定它。

**契约读法（明示，供复核裁定）**：本仓的 stub 机制是为"`__vftable` 成员在生成头里不存在 ⇒ C2039"而设的**可编译性**兜底；形态 1/2/3 的间接调用文本**本身可编译**，故把它们改成 stub 只会**引入新字节差异**且无 compilability 收益。因此"保留既有 stub 语义"实现为：**legacy stub 路径保持不变**（回归测试证明）＋ 新形态失败时原文保留。若复核认为契约应要求"新形态失败也合成 stub"，改动点是一处分支（`_record_vtable_failure` 之前调用既有 `_vtbl_stub_names` 即可），但需要一次完整 pipeline 运行来评估字节影响——本任务受并发约束不能跑（见 §7）。

台账原因取值与全语料计数（3598 个 decomp 函数、按函数去重后 **464** 行）：

| 原因 | 含义 | 实测行数 |
|---|---|---|
| `non_class_hint` | cast 首参是标量/typedef（`int`/`char`/`_DWORD`/`LONG`/`float`…），不是类 | 240 |
| `self_arg_mismatch` | vptr 持有者 ≠ 首个实参（子对象/偏移视图，`this` 不同） | 185 |
| `slot_out_of_range` | 槽下标超出 IDB `vtbl_<ADDR>.data_members` 长度 | 21 |
| `no_vtables_declaration` | 该类注解无 `vtables[]`（未声明为多态）——见设计约束 2 | 17 |
| `name_declared_at_other_address` | §1.3 的真实反例（UIWnd 槽3 `Destroy`） | 1 |
| `no_idb_vtbl_struct` / `no_method_name` / `no_class_hint` / `name_not_declared_for_class` | 本语料 0 命中（测试覆盖） | 0 |

台账样例行（`/tmp` 试跑产物，**未入库**）：

```
| `Actor::DispatchAction` | inline | `gbActor` | 16 | self_arg_mismatch | `(*(int (__thiscall **)(gbActor *, int))(*(_DWORD *)&this->m_pact->gbChain1DNode + 16))(this->m_pact, actionId)` |
| `CEffAction::UpdateFrame` | inline | `CTaskTpl_tagEffTaskParam_CEffAction` | 4 | no_vtables_declaration | `(*(void (__thiscall **)(CTaskTpl_… *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v2->_tail_000 + 4))( v2, …)` |
```

首行是"该补 `gbActor` 的 vtable 注解"的直接工单；第二行是"该类未声明多态"。

## 4. 验证证据

### 4.1 TDD 红 → 绿

- 红相（实现前，仅测试文件）：`Results: 1 passed, 20 failed`（唯一通过的 1 条是**既有行为**的保留断言 `_fix_ref_params` 的 `_tail_000 → *(void**)(X)`）。
- 绿相：`Results: 27 passed, 0 failed`。

### 4.2 全语料**逐字节差分**（最强无回退证据）

以 `git show HEAD:…/stage3_cleanup.py` 为旧实现（`/tmp` 副本），对 **3598 个 decomp 函数**逐一比对 `stage3_cleanup.run()` 的**完整输出**：

```
files 3598 · identical 3540 · changed 58 · converted_lines 113 · ADDED 行 0 · 异常 0
```

即：**除 113 处新转换外，输出逐字节不变**（58 个文件的所有差异都落在 `->Method(` 直接虚调用上；`REMOVED` 行全是多行调用的续行碎片）。`_resolve_vftable_calls_ast` 单函数差分同样为 3539 identical / 59 changed / 0 unexpected。

### 4.3 槽名与生成头文件对表（5 个唯一名字，全部命中）

| 转换 | 槽 | 声明点（生成头文件） |
|---|---|---|
| `gbGfxManager::NewTexture` ×66 | byte8 → slot2 | `include/gbengine/gbGfxManager.h:146 virtual gbTexture* NewTexture(const char* name); // slot 2` |
| `UIWnd::OnMessage` ×40 | byte24 → slot6 | `pal3/src/UI/UIWnd.h:43 virtual int OnMessage(int,int,int); // 0x00445D10` |
| `AStarPathFinder::GetHeuristicIdx` ×5 | byte8 → slot2 | `pal3/src/Misc/AStarPathFinder.h:40 virtual unsigned __int8 GetHeuristicIdx(int,int); // 0x004014F0` |
| `AStarPathFinder::IsInBounds` ×1 | byte4 → slot1 | `pal3/src/Misc/AStarPathFinder.h:39 virtual int IsInBounds(int,int); // 0x004014E0` |
| `CCBPanelSlot::Render` ×1 | byte4 → slot1 | `pal3/src/Misc/CCBPanelSlot.h:32 virtual void Render(); // 0x00443200` |

被护栏挡下的 1 处正是 `UIWnd` 槽3（`Destroy` vs 非虚 `Destroy@0x0043BBB0`）。三个真实样本的槽位还与二进制 asm 交叉核对过（`[edx+8]`/`[eax+4]`/`[eax+4]`，见 §2 与 §4.4）。

### 4.4 形态 2 的真实产出（任务简报称"更大的头"）

实测形态 2 在生产语料里长这样（`UIPushButton::CreateFromTemplate` 等 14 个函数）：

```
v7 = *(_DWORD *)gfxMgr->_tail_000;            ← 局部 vftable 变量（既有两条解码路径全部落空）
…
this->m_pDownpic = (gbTexture *)gfxMgr->NewTexture(v8);
```

即 66 个 `NewTexture` 转换中绝大多数来自形态 2 —— 与简报的判断一致。

### 4.5 台账幂等（跨进程）

同一条路径连续 3 个**独立进程**各跑一遍全语料：文件大小 `0 → 94190 → 94190 → 94190`；
同进程内两轮亦为 `464 行 / 94190 字节` 不变。

### 4.6 假阳性防护（实测语料）

不进入三形态的间接调用**零改动、零记账**（有测试）：

- `(*(void (__stdcall **)(_DWORD))m_pData)(0, v29);`（COM 接口表，`__stdcall` + 裸成员）
- `(*(void (__thiscall **)(int *, _DWORD))this->m_NewItem[7].fnHP)(&this->m_NewItem[7], 0);`（函数指针成员）
- `(**(void (__thiscall ***)(char *, _DWORD))this->m_Slots[17].m_Widget)(this->m_Slots[17].m_Widget, 0);`（双解引用 + 裸成员链，**刻意划出范围**：该形态 cast 首参通常是 `char *`/`_DWORD` 而非类，语料里多为函数指针数组/成员）

## 5. 顾虑（复核重点）

1. **契约读法差异（需裁定）**：见 §3 末尾。我把"保留既有 stub 语义"实现为"legacy stub 路径不变 + 新形态失败原文保留"，理由是 stub 是为**可编译性**而非"更忠实的字节"而存在；另一种读法（新形态失败也合成 stub）会带来 **≈460 处**新 stub 调用而无法在本任务的并发约束下量测字节影响。若复核要求后者，请一并授权一次完整 pipeline 运行（`loop --expect-*`）以评估，否则不应盲改。
2. **护栏的保守性**：`name_not_declared_for_class` / `name_declared_at_other_address` 会挡住"头文件其实会发（因为 decomp 声明了）"的名字。代价目前为 0（113 个转换的名字全部命中注解 methods / known_methods / IDB 类 methods 三源），但若后续注解补全后出现误挡，台账会直接显示，且修法是给索引加 decomp 名字源（一次 3598 文件扫描，约 1-2 秒，一次性懒加载）。
3. **未做端到端字节验证**：并发约束禁止 `pipeline/cli.py loop/apply/export/codegen`（IDB 争用 + 会干扰 Task 3/6 并重生成 `pal3/src`）。因此"113 处转换是否真的改善 L1/S2"**没有实测**，只有：全语料差分（无副作用）＋ 槽位对表（名字与槽位正确）＋ 生成头文件对表（每个名字都是该槽的 virtual 声明）。真正的字节裁决归 Task 8（L1 + .rdata 双裁判）。
4. **`test_qualified_vftable_tristate` 的 1 项失败是既有的**：`test_strip_state_not_a_base`（`CCBUIPanel` 的 `this->m_scrollbar.UIListBox::__vftable` 未按 `strip` 态改写）。已用**旧实现**跑该文件全部 7 个用例的输入，输出**逐字节相同**（`OLD==NEW: True` ×7），且新旧都保留 `__vftable` ⇒ 与本任务无关。建议开独立工单（疑与 `store.struct_bases`/`base_class` 数据状态有关）。
5. **`pytest` 在本机不可用**（collect 阶段 `TypeError: required field "lineno" missing from alias`，来自一个 `pytest-dev__pytest-7432` 基准 worktree 的旧 pytest + Python 3.10）。故所有验证走自带 runner（`python3 tests/test_vtable_call_transform.py`），与 Task 1/2/3/4 报告的口径一致。
6. **台账文件未入库**：我的 `git add` 范围被限定为两个文件，故 `data/status/vtable_transform_failures.md` **不在本提交里**（首次失败时自动创建/追加，含表头）。若希望基线台账入库，请另行授权。
7. **形态边界（已披露）**：`(**(fn***)MEMBER)` 双解引用家族（实测 54-58 站点）与 `*((_DWORD *)v8 + 39846) + 16` 这类嵌套 cast 家族**刻意不处理**（前者 cast 首参常非类，后者对象与 vptr 持有者关系复杂）；它们保持原文并**不记账**（因为未被识别为虚调用，避免把 COM/函数指针成员误记）。若 Task 8 发现其中含真实虚调用，应扩范围而不是放宽假阳性门槛。

## 6. 并发约束合规

- 只改了 `pipeline/gen/stages/stage3_cleanup.py`，只新建 `tests/test_vtable_call_transform.py`；**未触碰** `tools/vtable_sig_infer.py` / `tools/vtable_slot_classifier.py` / `tools/vtable_verify.py`（后两者的新文件由 Task 5/6 创建，`git status` 里可见，我未 add）。
- **未运行** `pipeline/cli.py loop|apply|export|codegen`；全部验证都是**只读**读 `asm/pal3/decomp`、`data/annotations`、`asm/pal3/ida_structs.json`、`original/PAL3.exe.asm`。
- 中间产物（旧实现副本、差分脚本、试跑台账）全部在 `/tmp`，未入库。
- 提交（`git add` 仅两文件）：`7ee6041fb`
  ```bash
  git add pipeline/gen/stages/stage3_cleanup.py tests/test_vtable_call_transform.py
  git commit  # 7ee6041fb feat(stage3): Task7 虚调用转换（三形态识别）——直接虚调用 + 失败台账
  ```
  `git show --stat 7ee6041fb` 只含这 2 个文件。本报告位于 `.superpowers/sdd/**`（该目录
  `.gitignore` 为 `*`）⇒ 报告不入库，属工作产物。
---

# 修复轮 R=1（评审 I-1 / I-2 必修 + M1 / M7）

- **状态**：DONE
- **覆盖文件**：`pipeline/gen/stages/stage3_cleanup.py`（+43/−13）、
  `tests/test_vtable_call_transform.py`（+132，27 → **35** 条测试）
- **一行测试摘要**：`test_vtable_call_transform` **35 passed / 0 failed**（新增 8 条：
  I-1×3 + I-2×1 + M1×2 + M7×2）；前序 9 个测试文件计数与 R=0 报告**逐项一致**
  （35 / 38 / 68 / 73 / 4 / 5 / 4 / 1+4skip / 6 passed+1 既有失败）。

## R=1-1（I-1，必修）：`slot_addr` 缺失 ⇒ 护栏两条判据双双旁路

**病灶层**：stage3 解码后的**名称解析链**（`_resolve_vtbl_name_chain` 的最后一段护栏），
不是 Hex-Rays 原始输出、也不是 pattern 识别层。

**根因**：`slot_addr` 被当成内层判定的**前置条件**：

```python
if decl_addrs:
    if slot_addr and slot_addr not in decl_addrs:   # ← slot_addr='' ⇒ 整个内层检查跳过
        return None, 'name_declared_at_other_address'
elif slot_addr:                                     # ← slot_addr='' ⇒ 同样跳过
    return None, 'name_not_declared_for_class'
return name, None                                   # ← 于是直接放行
```

**最小修法（fail-closed）**：判据不完整即拒绝。

```python
slot_addr = (idx.get('class_slot_addrs', {}).get(cls_hint) or {}).get(slot, '')
if not slot_addr:
    return None, 'no_slot_addr'
decl = idx.get('class_decl', {}).get(cls_hint) or {}
decl_addrs = decl.get(name)
if decl_addrs:
    if slot_addr not in decl_addrs:
        return None, 'name_declared_at_other_address'
else:
    return None, 'name_not_declared_for_class'
return name, None
```

**红 → 绿（原文）**

红相（仅加测试，未改实现）：

```
  FAIL test_name_chain_rejects_missing_slot_addr_when_name_is_declared: AssertionError: ('GetHeuristicIdx', None)
  FAIL test_name_chain_rejects_missing_slot_addr_when_name_is_undeclared: AssertionError: ('GetHeuristicIdx', None)
  FAIL test_missing_slot_addr_call_fails_closed_with_ledger: AssertionError: int CCBSkillWindow::Create(int rc, int nVal)
Results: 29 passed, 4 failed, 0 skipped
```

第 3 条的红相输出直接给出了 Critical 证据 —— 端到端跑出 `  this->Destroy(1);`
（`PalScriptMgr` 形状：有 `vtables[]` 但 `slots[i]` 缺 `addr` ⇒ 旧实现**发射了凭空名**）。

绿相：

```
Results: 35 passed, 0 failed, 0 skipped
```

**触发数实测（只读全语料，3598 个 decomp 函数）**：`bypass_i1=0`
（同一次计量同时复现 R=0 报告的 `_resolve_vtbl_name_chain` 调用数 **907**、给出名字 **113**
⇒ 计量口径与 R=0 一致，故"当前 0 触发"这个判断可复现）。该缺陷因此是**潜伏**的：
触发即 Critical，现在已被 fail-closed 封住。

## R=1-2（I-2，必修）：`_load_vtbl_index` 直读注解 ⇒ 收敛到单一读点

**病灶层**：注解**读取路径**（不是注解内容、不是 IDB）。

**修法**：`os.listdir + json.load(.../structs/*.json)` → `annotation_view.structs_dir()` +
`annotation_view.iter_structs()`（懒 import，模式与 `pipeline/gen/data.py:198-201` 一致）。

**语义等价性（全量实测，不是断言）**：替换前后各建一次索引并规范化 dump 比对：

```
=== index equivalence (before vs after I-2) ===
identical: True
```

（`class_addr` / `by_addr` / `idb_members` / `class_slot_addrs` / `class_decl` 五张表
逐字段相同；规模 `classes=80 idb_vtbls=92 slot_addrs=80`，与 R=0 报告一致。）

**结构护栏测试**（新）：`test_load_vtbl_index_reads_structs_through_annotation_view`
把 `annotation_view.iter_structs` 换成探针，断言 ①探针**被调用** ②索引内容**只**来自探针
（真实语料一个类都不得混入）⇒ 今后任何人把直读改回来都会立刻红。

红相：`FAIL test_load_vtbl_index_reads_structs_through_annotation_view: AssertionError: annotation_view.iter_structs 未被调用 ⇒ 仍在直读注解文件` ✓

## R=1-3（M1，Minor）：`_VTBL_VPTR_READ` 前缀收紧为单 `*`

`^\*+` → `^\*`。原写法把 `**(int **)this`（`this`→vptr→slot0 指针，**两次 load**）
误读成"一次 vptr 读"⇒ 发射 `this->M()` 会丢掉一次 load。

**影响面实测（只读）**：

- 该形态在当前语料有 **30** 个文本命中（`_vptr_read_of` 返回非 None 且 head 以 `**` 开头）；
- 收紧后文本命中 **30 → 0**；
- **全语料 `_resolve_vftable_calls_ast` 输出 0 字节变化**：
  `files=3598 changed=0 added=0 removed=0`（把 regex 收紧版与原件在同进程内各跑一遍逐文件比对）；
- 台账（`vtable_transform_failures.md` 形状）：`rows old=197 new=187`，
  `only_old=12`（全是 `**(...)` 的 `self_arg_mismatch` **误报**，如
  `(**(_DWORD **)this + 16)`）、`only_new=2`（原本被幂等键压掉的**真**行，
  如 `(*(_DWORD *)LODWORD(x) + 16)`）。

⇒ 零输出风险 + 假阳性收口。

## R=1-4（M7，Minor）：补 no_class_hint / non_class_hint 单测

`test_name_chain_reports_no_class_hint`（`''`/`None`）+
`test_name_chain_reports_non_class_hint`（`int`/`char`/`_DWORD`/`void`/`unsigned int`/`BOOL`
必须在查索引**之前**归因，否则会被误报成 `no_vtables_declaration`，把注解工单指错方向）。

## R=1 验证证据（全部只读；未跑 `pipeline/cli.py loop|apply|export|codegen`）

### ① A/B 全语料逐字节差分（HEAD 实现 vs 工作区实现）

方法：`git show HEAD:pipeline/gen/stages/stage3_cleanup.py` → `/tmp`，与工作区模块在同一进程内
对 **3598** 个 decomp 函数各跑一遍 `_resolve_vftable_calls_ast`，**两边注入同一份索引**
（该索引已由 ①' 单独证明与替换前逐字段相同）⇒ 差分只反映 I-1 护栏 + M1 regex 的行为变化。

```
index: classes=80 idb_vtbls=92 slot_addrs=80
files=3598 identical=3598 changed=0 added=0 removed=0 errors_old=0 errors_new=0
arrow-lines old=43421 new=43421
```

⇒ **输出逐字节相同**（113 处转换全部保留，0 新增/0 丢失）。

### ② 前序 9 个测试文件（自带 runner，原文摘要）

| 测试文件 | 结果 | R=0 报告 |
|---|---|---|
| `test_vtable_slot_order.py` | `Results: 35 passed, 0 failed, 0 skipped` | 35 ✓ |
| `test_vtable_slot_classifier.py` | `Results: 38 passed, 0 failed, 0 skipped` | 38 ✓ |
| `test_vtable_sig_infer.py` | `Results: 68 passed, 0 failed, 0 skipped` | 68 ✓ |
| `test_layout_assert_gen.py` | `Results: 73 passed, 0 failed, 0 skipped` | 46 → 73（该文件正被**并行实现者**修改，`git status` 显示 `M`；非本次改动） |
| `test_vtbl_stub_dedup.py` | `Results: 4 passed, 0 failed` | 4 ✓ |
| `test_vtbl_slot_index.py` | `Results: 5 passed, 0 failed` | 5 ✓ |
| `test_owner_self_drop.py` | `Results: 4 passed, 0 failed` | 4 ✓ |
| `test_vftable_deref_preserved.py` | `Results: 1 passed, 0 failed, 4 skipped` | 1+4skip ✓ |
| `test_qualified_vftable_tristate.py` | `Results: 6 passed, 1 failed` | 6+1 既有失败 ✓ |
| `test_vtable_call_transform.py` | `Results: 35 passed, 0 failed, 0 skipped` | 27 → 35（本任务） |

既有失败**逐字仍是同一条**，并用 HEAD 实现隔离复跑证明与本轮改动无关：

```
NEW: 1/7 failed → ['test_strip_state_not_a_base: AssertionError: void CCBUIPanel::F() … __vftable = (void *)80…']
OLD: 1/7 failed → ['test_strip_state_not_a_base: AssertionError: void CCBUIPanel::F() … __vftable = (void *)80…']
```

### ③ 索引等价 dump（I-2）

```
=== index equivalence (before vs after I-2) ===
identical: True
```

### ④ I-1 触发计量 & M1 命中计量（同一只读脚本，两遍）

| 计量 | before（HEAD 逻辑） | after（本轮） |
|---|---|---|
| `_resolve_vtbl_name_chain` 调用数 | 907 | 907 |
| 给出名字数 | 113 | 113 |
| I-1 旁路触发数（缺 `slot_addr` 却放行） | **0**（潜伏） | 0（已 fail-closed） |
| M1 `**` 误读命中数 | **30** | **0** |

## R=1 顾虑

1. **两处直读仍在（未在本轮范围）**：`stage3_cleanup.py:173-191`
   （`_resolve_vtbl_method` 的 legacy 兜底，`data/annotations/structs/<Cls>.json` 直读 +
   `except (OSError, ValueError, KeyError, IndexError, TypeError)` 精确容错）。
   它就是 CLAUDE.md「尚有 3 处直读」清单里 stage3 那处（行号已漂移，原文写 `107-110`）。
   本轮 I-2 只按评审范围修 `_load_vtbl_index`；该处若要收敛，需要用
   `annotation_view.struct_path`/`struct_by_class` 并保留精确容错语义，属独立工单。
2. **`no_slot_addr` 的新失败面**：注解 `vtables[0].slots[i]` 缺 `addr` 的 10 个 (类,槽)
   （`CCBPanelSlot` 槽3-6、`PalScriptMgr` 槽0-5）从"能解析出名字"变为"记账 `no_slot_addr`"。
   当前语料 0 调用点 ⇒ 输出无变化；但**注解补全的工单方向变了**：这 10 个槽现在是
   "补 `slots[i].addr`"而不是"补方法名"，补完即可恢复转换。
3. **未做端到端字节验证**（与 R=0 同因）：并发约束禁止 `loop/apply/export/codegen`，
   故 L1/S2 门禁仍未实测；本轮证据链止于"全语料输出逐字节不变 + 35 条契约测试"。
   字节裁决仍归 Task 8。
