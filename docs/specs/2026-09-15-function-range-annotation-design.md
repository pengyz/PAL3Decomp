# 函数范围标注（function-range annotation）设计

> **状态**：**待用户复核**。本文档只是设计，**未实施**。
> **日期**：2026-09-15 · **仓库**：`/home/peng/workspace/PAL3Decomp` · **HEAD**：`b091b2f52`
> **分类**：**architectural** —— 给 annotation 接口新增一类语义（函数**范围**），
> 改变 `apply` 的阶段契约，并触发全量重反编译。
> **来源**：用户提出「IDA 的函数切分错误需要新机制——允许手动切分函数，
> 函数标注可标注起始和结束偏移；先把可行方案调研清楚，写测试用例确保机制有效，
> 然后落地 annotation 中的函数范围标注功能，然后进行重标注」
> **已确认决策**：问题1 = **甲**（`functions.json` 加可选 `"end"`）；问题2 = **乙**（允许新建 + 修正，带强校验）
> **Hindsight**：本会话 `hindsight_*` 全部 401（`API key required`）⇒ 知识落 `docs/knowledge/`

---

## 1. 问题（实测规模）

`C2039 "'__vftable' : is not a member"` 族（**718 条 / 38 文件**）与"函数归属不确定"的**共同根因**之一，
是 **IDA 的函数边界不可靠**：

| 证据 | 实测 |
|---|---|
| **边界错位**（抽样 60 个随机函数）| **18 个（30%）** 的结束地址处**不是** `ret`/`int3`/填充 |
| 样例 | `?AttachToRole@CameraCtrl@@QAEXH@Z` 结束于 `0x41E7CB` → 反汇编为 **指令中间**（`les (%ebx,%eax,8),%ecx`）；`?CastAttackMagic@CCBAI@@QAE_NHH@Z`、`?GetRenderFlag@CCBSystem@@QAEHXZ` 同类 |
| **"经典吞并式合并"** | **无证据**：用 3618 个已知函数起始扫描 5554 个函数，"体内含其他已知起始" = **0 个** |
| **函数过大的误判我已排除** | 31KB 的 `?CreatePanelElements@SaleUI@@QAEHPAUCCBUIPanel@@@Z` **只有 1 个函数序言**（对照组单一函数也是 1），尾部 `jl` 是**循环回边** ⇒ **真正的单个大函数** |
| **另一个真问题（非边界）** | `0x4D3280` 被名为 `?GetEditorTaskDescription@CEffShock@@QAEPBDH@Z`，实际是**构造函数**（写 3 个 vptr + 初始化 + `ret`）⇒ **错的是"名字"**，`functions.json` 可修 |

**⇒ 需要的能力**：annotation 能表达"**这个函数的范围是 [start, end)**"，`apply` 据此**修正 IDB 的函数边界**。

---

## 2. 现有机制与本设计的差距

### 2.1 `apply` 已经会 `add_func`，但**无法指定 `end`**

`pipeline/ida/apply_annotations.py:1704-1718`：
```python
if not _ida_funcs.get_func(addr):
    if _ida_funcs.add_func(addr):              # 无 end ⇒ 用 IDA 自己的推断
        created += 1
    else:
        _next_func = _ida_funcs.get_next_func(addr)
        if _next_func:
            _ida_funcs.add_func(addr, _next_func.start_ea)   # end = 下一个函数起点
```

⇒ **只做启发式**；annotation 层**没有 `end` 的表达能力** ⇒ 错位无法修。

### 2.2 项目已有同型操作的**先例**（可直接复用其顺序）

`docs/superpowers/plans/2026-05-06-pal3a-ida-quality-fix.md:640-675`
（PAL3A 的 BOUNDARY_OVERLAP 修复 `split_overlapping_functions`）：
```python
old_end = func.end_ea
if not ida_funcs.set_func_end(addr, split_addr): continue
if not ida_funcs.add_func(split_addr):
    ida_funcs.set_func_end(addr, old_end)      # 回滚
    continue
ida_name.set_name(split_addr, safe_name, SN_NOWARN | SN_NOCHECK)
```
**已含 dry-run（默认）/ `--execute` / 回滚 / 逐条日志。**

### 2.3 模式可安全扩展

`check_annotations.py:138-195` 对 `functions.json` 只校验
`address` 格式、`name`、`signature`（重复 / `virtual` / `__thiscall` 归属）
⇒ **新增 `end` 字段不会被拒**；新校验挂在 `check()`（`:117`）的同一循环里。

---

## 3. 行为测试：三个未知项**已确定**（`pipeline/ida/_test_func_range.py`）

> 用户要求"写测试用例确保机制有效"。测试台**只在 `/tmp` 的 IDB 副本上跑**，
> 内置安全闸（路径含生产 IDB 且不在 `/tmp` 下则 `qexit(2)` 拒绝），每个实验后复原。

| 测试 | 目标（31KB 函数 `0x4623A0-0x469CEC`，下一函数 `0x469D00`）| 实测 | 结论 |
|---|---|---|---|
| **T1** | `set_func_end(start, 0x46603F)` | **`ok=True`**，end `0x469CEC → 0x46603F` | 截断**可行** |
| **T1_restore** | 复原到 `0x469CEC` | **`ok=True`** | **可回滚** |
| **T2** | `set_func_end(start, 0x469D20)`（**越过**下一函数起点）| **`ok=False`**，end 不变 | **重叠被拒** |
| **T3a** | 不截断，直接在体内 `add_func(0x464C07, +0x40)` | **`ok=False`** | **不能越级新建** |
| **T3b** | **先** `set_func_end(start, 0x464C07)`，**再** `add_func` | **`ok=True`** | **正确顺序** |
| **final_restore** | | end 复原 `0x469CEC` | **测试无副作用** |

**⇒ 三条确定结论（直接决定实现）**：
1. `set_func_end` 截断**可行且可复原**（回滚有保障）；
2. **延长越过下一函数起点会被拒**（重叠约束）⇒ 拆分**必须"先截断后新建"**；
3. 在**已有函数覆盖**的地址上 `add_func` 会**失败** ⇒ **必须先 `set_func_end`**（或 `del_func`）。

**这与 §2.2 的先例顺序一致** ⇒ 先例是对的，**采用它**。

---

## 4. 设计

### 4.1 annotation 模式（问题1 = **甲**）

`data/annotations/functions.json` 每条**可选**新增 `"end"`：
```json
"0x004623A0": {
  "name": "?CreatePanelElements@SaleUI@@QAEHPAUCCBUIPanel@@@Z",
  "signature": "...",
  "end": "0x00469CEC"          // ← 新增，可选；省略则行为与现在相同（完全向后兼容）
}
```

**字段语义**（必须无歧义）：

| 属性 | 语义 |
|---|---|
| `end` | 函数范围的**排他上界**（`[start, end)`），与 IDA 的 `end_ea` 同义 |
| 缺省 | 不修正边界（行为与当前完全一致）|
| 与 `name` 关系 | **`end` 只改边界，不改名字**；`name` 仍由现有逻辑 `set_name` |
| 与 `skip_functions.json` 关系 | 该文件的条目**也**可带 `end`（它是"只命名不分析"的清单）|

### 4.2 `apply` 的处理（问题2 = **乙**：允许新建 + 修正）

新增一个**阶段**（在现有 "1. functions — set_name + SetType" **之前**，
因为边界必须在类型/名字之前确定；`set_name` 幂等，顺序无碍，但先定边界更稳）。

```
phase 0b: function ranges   —— 对带 "end" 的条目，修正 IDB 的函数范围
```

单条处理逻辑（据 §3 实测的**正确顺序**）：

```python
def apply_range(addr, end, name):
    cur = ida_funcs.get_func(addr)
    if cur is None:
        # 该地址没有函数 ⇒ 直接建（实测 T3b 表明"先截断"是父函数存在时的前提）
        prev = ida_funcs.get_prev_func(addr)      # 可能的"父"函数（吞并了本函数）
        if prev is not None and prev.end_ea > addr:
            saved = prev.end_ea
            if not ida_funcs.set_func_end(prev.start_ea, addr):
                return FAIL, "set_func_end(prev) failed"
            if not ida_funcs.add_func(addr, end):
                ida_funcs.set_func_end(prev.start_ea, saved)   # 回滚
                return FAIL, "add_func failed"
        else:
            if not ida_funcs.add_func(addr, end):
                return FAIL, "add_func failed"
        return OK_CREATED
    # 已存在函数 ⇒ 只修正 end
    saved = cur.end_ea
    if cur.end_ea == end:
        return OK_NOCHANGE                      # 幂等
    if not ida_funcs.set_func_end(addr, end):
        return FAIL, "set_func_end failed"
    return OK_FIXED
```

**关键点**：
- **先 `set_func_end(父, addr)` 再 `add_func(addr, end)`**——据 T2/T3a/T3b 实测，这是**唯一可行**的顺序；
- **每条记录 `saved` 用于回滚**；
- **幂等**：`cur.end_ea == end` 时不动；
- 只改**带 `end`** 的条目 ⇒ **未标注的函数零影响**。

### 4.3 `check_annotations` 的新校验（强校验，问题2 的"乙"要求）

挂在 `check()`（`:117`）的 functions 循环里：

| 校验 | 规则 | 失败等级 |
|---|---|---|
| 格式 | `end` 匹配 `^0x[0-9A-Fa-f]{8}$` | error |
| 顺序 | `end > start` | error |
| 范围 | `end` 落在 `.text` 内（`0x00401000 ≤ end ≤ 0x0056A000`）| error |
| **重叠** | `[start, end)` **不得**与同文件内其它条目的 `[start', end')` 重叠 | error |
| 相邻完备性 | 若 `end` 与下一个带 `end` 的条目的 `start'` **不衔接**，报 **warning**（提示中间有未覆盖的函数）| warning |

**为什么重叠校验必须有**：T2 实测"越过下一函数起点会被拒" ⇒ 若 annotation 不校验，
`apply` 会在运行时失败 ⇒ **把可静态发现的问题推迟到运行时**（本会话已 6 次遇到这类门禁问题）。

### 4.4 dry-run 与执行模式

沿用 §2.2 先例：
- `apply` 默认**执行**（它是管线的一步，必须幂等且可靠）；
- 新增独立命令 `python3 pipeline/cli.py ranges --dry-run` 用于**预览**：
  输出"将截断 X / 将新建 Y / 将跳过 Z（已一致）"，**不修改 IDB**；
- `--execute` 才真改（默认 `--dry-run`，防止误操作）。

### 4.5 连锁影响（必须写进文档并接受）

| # | 影响 | 说明 |
|---|---|---|
| **1** | **改边界 ⇒ 必须重跑 `export`** | `export_full.py:388` 用 `ida_hexrays.decompile(ea)`，**按函数边界**输出 ⇒ 边界变则 `decomp` 必须重建（**全量 3598 个 JSON**），时间成本可观 |
| **2** | `decomp.address` 语义变化 | 成为"修正后的函数起始"；下游 `match`/`mangler_bench` 的 `symbols`/`unmatched` **分母会变** ⇒ **不可跨轮比较**（本会话已有"分母变即不可比"的教训）|
| **3** | `Hex-Rays` 缓存过期 | 边界变更后需 `dirty mark`（`export_full.py:382` 已有该机制）|
| **4** | **不得与 `apply` 的其它阶段顺序冲突** | 新阶段放在 functions 之前（见 §4.2）|

### 4.6 重标注（用户要求的最后一步）

本设计**只提供机制**。真正的"重标注"是**逐类取证**的工作，依赖前面已沉淀的方法：
`docs/knowledge/pattern_recover_polymorphic_base_virtual_methods.md`
（含"如何判定函数归属"与三个工具）。
**⚠️ 但 §5 里的"归属证据"问题仍未解决**——见下。

---

## 5. ⚠️ 本设计**不解决**的事（诚实边界）

**"某个函数属于哪个类"的证据问题依然存在**，而这正是 F2 供给的核心：

| 我尝试过的归属口径 | 结果 |
|---|---|
| `decomp`/`annotations` 的函数边界 | ❌ 不可靠（§1 实测 30% 错位）|
| IDA 的函数容器 | ❌ 有合并（但**已排除**两个我误判的案例）|
| **"计分法"**（表的最多槽位归属类）| ✅ 对已知类**正确**，但**只能覆盖 20/467 张表** |
| IDA `vptr_sites` 归属 | ✅ **170/467**，但 **F2 缺口类只 3/57**——因**这些类在 IDB 里没有归属给它们的函数** |

**⇒ 本机制解决的是"边界能不能改"（能，已实测）；没解决"该改成什么"。**
后者需要**调用链取证**（`new Cls` 的调用点、ctor 的调用者），是**独立的下一个任务**。

---

## 6. 测试策略（TDD；用户要求"写测试用例确保机制有效"）

### 6.1 单元/行为测试（扩展 `pipeline/ida/_test_func_range.py`）

| # | 用例 | 期望 |
|---|---|---|
| 1 | **截断**：对一个已知大函数设 `end` 到中点 | `ok`，`get_func().end_ea == want` |
| 2 | **新建**：对一个"被吞并"的地址设 `start+end` | `ok`，父函数被截断、新函数存在 |
| 3 | **重叠拒绝**：`end` 越过下一函数起点 | `ok=False` 且 IDB **未变**（回滚生效）|
| 4 | **回滚**：注入一个必然失败的 `add_func`，验证父函数 end 被复原 | 复原成立 |
| 5 | **幂等**：连续两次 apply 同一条目 | 第二次 `OK_NOCHANGE`，IDB 无差异 |
| 6 | **未标注零影响**：不带 `end` 的条目 | IDB 与现状逐字节一致 |

**测试必须在 `/tmp` 的 IDB 副本上跑**（安全闸已实现）。

### 6.2 静态校验测试

| # | 用例 | 期望 |
|---|---|---|
| 7 | `end < start` / 格式错 / 越界 | `check_annotations` 报 **error** |
| 8 | 两条范围重叠 | 报 **error** |
| 9 | 范围不衔接 | 报 **warning** |

### 6.3 端到端（**窗口 + 全量**）

| # | 步骤 | 判据 |
|---|---|---|
| 10 | 对**1 个**已知错位函数加 `end` → `apply` → `export` | 该函数的 `decomp` 重新生成、边界正确 |
| 11 | 跑 `check → apply → export → codegen all → probe all → match` | `L1` **不回退**（≥14）；`ok` 不回退（≥56）；**同时记录 `symbols` 分母** |
| 12 | 重标注后 `C2039` 族计数 | 应下降（这是本机制的目标）|

---

## 7. 规格自检

1. **占位符扫描**：无 `TBD`/`TODO`；§4 各节均有明确规则与失败处置。
2. **内部一致性**：§4.2 的操作顺序与 §3 实测结论一致；§4.3 的重叠校验对应 §3 的 T2 约束。
3. **范围检查**：本文档覆盖 **1 个字段 + 1 个 apply 阶段 + 1 组校验 + 1 个 dry-run 命令 + 测试**，
   **超单一实现计划容量** ⇒ 需在 writing-plans 阶段拆为
   ①`check_annotations` 校验 ②`apply` 阶段 ③`ranges --dry-run` 命令 ④测试扩展 ⑤端到端验证。
4. **歧义检查（已消歧）**：
   - "`end`"——明确为**排他上界** `[start, end)`，与 IDA `end_ea` 同义；
   - "重叠"——明确为**同文件内条目之间**；跨文件（`functions.json` vs `structs/*.json` 的 `methods`）
     **本设计不校验**（列为 future work）；
   - "回滚"——明确为 `set_func_end(父, saved)` + `del_func(新建)`；
   - "dry-run 默认/执行"——明确：`apply` 是管线一步（**执行**）；
     独立命令 `ranges` **默认 dry-run**，`--execute` 才改。
5. **诚实标注**：§5 明确本设计**不解决归属证据**问题。

---

## 8. 请求复核

本文档为**设计**，未实施任何改动。**请复核**：
- §4.1 的字段形态与 §4.2 的操作顺序；
- §4.3 的校验规则（尤其**重叠=error / 不衔接=warning** 的分级）；
- §4.5 的连锁影响（**改边界=全量 export** 是否可接受）；
- §5 的诚实边界（本机制**不解决归属证据**）。

如无异议，我按技能进入 `superpower-writing-plans` 拆出 5 个子计划并实现。