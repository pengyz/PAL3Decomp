# 注解接口层（Annotation Interface）— 架构任务书

> **状态**：**已立档，未启动**。本任务**不属于** 2026-09-15 清理工作的 t3–t12 DAG（那批是存量缺陷修复）。
> **立档时间**：2026-09-15 · **仓库**：`/home/peng/workspace/PAL3Decomp` · **HEAD**：`aacdf69c5`
> **缘起**：清理工作 t4（export 红线）判「有意取舍」后，captain 做第一性对抗性复查，得出**边界划错**的结论。见 `docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md` 裁决 (a) 与 `data/status/_cleanup_fix_export_redline_decision_page.md`。
> **启动条件**：用户显式决定投入。**不要在清理工作轮次内顺手启动**——历史上「顺手扩展桥模式」正是本债务的成因（`38f811d0f`/`ad527e5c2` 在红线写下之后继续扩展）。

---

## 1. 核心结论（一句话）

**边界划错了地方**：真正的不变量不是「哪个阶段可以读注解」，而是「**注解 → codegen 语义的翻译必须恰好发生在一个地方**」。

修正后的红线措辞应为：

> **只有 export 读 annotation；codegen 不读 annotation。**

原文（`CLAUDE.md:69`）「export 不读 annotation：`export_full.py` 只能从 IDB 读取数据」**不可满足**——它要求一个阶段从 IDB 取数，而该数据在 IDB 里**根本不存在**（见 §2）。

---

## 2. 为什么原文不可满足（全部实测，出处见 t4 交付物）

| 读点 | 读什么 | IDB 里有没有 | 实测证据 |
|---|---|---|---|
| `export_full.py:238` | `skip_functions.json` → 1955 个 skip 地址 | **没有** | `apply_annotations.py:1682-1689` 对这些地址只做 `add_func` + `set_name`，**不留任何 skip 标记**；且**故意把它们造成函数**（`if not _ida_funcs.get_func(addr): _ida_funcs.add_func(addr)`），所以 `idautils.Functions()` 必然列出它们 |
| `:738` | `globals.json` 的 `type=="skip"`（196 条） | **没有** | `apply_annotations.py:1710` 显式把 `gtype=="skip"` 排除在 `SetType` 之外 |
| `:325` | `functions.json` 全地址表 | **没有** | 该表用途正是「IDB 里还没有的函数地址」——IDB 无法自证不存在的函数 |
| `:770` | 非 thunk skip 名单（1816 个） | 部分 | 名字被写入 IDB，但「哪些地址属于刻意 skip 且非 thunk」这一**集合语义**只在注解里 |
| `:532` | `structs/*.json` 的 `vtables`/`methods` | 部分 | 导出的这三个字段与注解**逐字段等值（761/761，0 不一致）** ⇒ 纯复制，非 IDB 读出量；`vtables[].slots[].from`（继承来源）在 IDB 无持久化形态 |
| `:194`/`:254`/`:257` | 虚性/类归属/mangled 名 | 部分 | 可从 IDB 推，但**等价性未验证**（t6 实测换源漂移 219/3524） |

**关键事实**：`apply_annotations.py` **不产出任何可供 export 消费的元数据文件**（磁盘写入只有 `_logs/*.txt`、`gbengine_flat_ida.h`、sig-fail log）。所以「让 export 读 apply 产物」这条路**当前不存在**，需要新建——这正是本任务的主体工作。

**历史事实**：`docs/knowledge/MEMORY.md` 的 `## Decisions` 段**实测为空** → 这个架构取舍从未被正式批准过。

---

## 3. 为什么这符合第一性原理（复利来源）

各层的**持久性**根本不同：

| 层 | 性质 | 可再生性 |
|---|---|---|
| A 级证据（指令级 `reg+disp32`、绝对地址） | **不可再生的智力资产** | 重做数百小时 |
| `data/annotations/`（881 struct / 1306 global / 3673 func） | **唯一持久的真相载体** | 已投入 |
| IDB（86MB） | 可重建缓存，**未入版本控制** | 重建贵 |
| `decomp/`、`pal3/src`、`baselines/` | **派生品**（`.gitignore`） | 随时重算 |

⇒ **真相源可以被读；但它的语义只能被解读一次。**

- `export` = **唯一的注解读取者 / 语义物化层**
- `codegen` = **只消费物化产物**（**这条红线是对的，必须保留**）
- `apply` = 把注解物化进 IDB；**能落的语义都要落，不许丢**

**代码病灶不在「谁读」，而在「多点各自解释」**：裁决 (a) 对 `ast_transform.py` 的判定是对的——它在模块内部**未经声明地**读 `structs/` 来判定跨类调用合法性。活证据是 `CG-023`：`_rowtable_family()` 读不到 `data/status/_rowtable_family.json` 时**静默返回空集 → 586 个站点 / 326 个文件被改判**（t6 实测数）。

---

## 4. 复利收益

1. **漂移检测变免费**。2026-09-15 发现「IDB 新 / decomp 新 / `pal3/src` 旧 / 基线旧」是靠**手工查 mtime 取证**（t4 子 agent 发现）。若产物携带来源（注解 git rev + sha + IDB rev），三层分叉**第一次就能自动报错**。
2. **「export 到底依赖注解的什么」变得可回答**。现在依赖散在 8 处 + 13 处消费者。单消费者之后，这个清单**可枚举、可测试**——也是迁移的**前提**。
3. **IDB 被移出关键路径**。若 export 可仅由 `binary + annotations` 复现，就能绕开 86MB 未版本化 blob，并**消除 IDB 单写者造成的窗口串行**（清理工作全程被迫串行，正因 IDB 是单写者）。
4. **消灭一类 bug，而不是一个个修**。同一根因（隐式、多点、静默的注解/元数据消费）导致的已知缺陷：`CG-023`、恒假门禁、`data.py:218` 丢 139 条 thunk 映射。显式接口让这类缺陷**无法悄悄成立**。

---

## 5. 实施步骤

| 步 | 内容 | 验收 |
|---|---|---|
| 1 | 新建 `pipeline/annotations_interface.py`：**唯一**读注解的模块，归一化 + 校验 + 输出**溯源**（注解 git rev / sha / 消费清单） | 单测覆盖每个字段族；对缺失/畸形注解显式失败 |
| 2 | `export_full.py` 改经该接口读（8 处 → 接口调用） | **行为等价性证明**：`export_full.py` 输出与改动前**逐字节 diff**（用 `/tmp` 输出目录，不写共享产物） |
| 3 | `apply` 补落 skip/variant 语义（现在故意丢）**或**显式声明「这是管线策略、注定不在 IDB」 | 逐条确认哪些语义真能落库；**不能承诺全部可落**（见 §6） |
| 4 | 红线改措辞（`CLAUDE.md:69`）：export 可读、codegen 不可读；决策页落盘 `docs/knowledge/` | 用户批准 |
| 5 | 漂移门禁：产物带来源 rev，不一致即失败 | 故意造一次分叉，门禁必须报错 |

---

## 6. 成本与不确定性（不粉饰）

- **步骤 1–2 是 1–2 天量级的重构，有回归风险**。清理工作 t3–t12 的 DAG 装不下，**故本任务单独立档**。
- **「IDB 装不下」里确实有一部分是真的**：`vtables[].slots[].from`（继承来源）与 `_variants` 未必有 IDB 表示形态。所以接口层**不能消除全部注解读取**，只能让依赖**显式、单一、可审计**——**这才是它的收益所在**，不要承诺超出此范围的效果。
- **步骤 3 需要逐条确认哪些语义真能落库**，尚未验证；不能承诺。
- 迁移**必然改变** export 的部分行为（t6 实测换 export 源 → 219/3524 文件漂移，含「静默放行」危险方向）⇒ 步骤 2 的等价性证明是**强制门禁**，不是可选项。

---

## 7. 与清理工作 t3–t12 的关系

- 清理工作**不阻塞**在本任务上：t4 已按「有意取舍」登记为**有待撤回条件的已知例外**（8 处带 `[t4-DECLARED-EXCEPTION]` 可 grep 标记）。
- 本任务的决策页草稿已由 t4 产出：`data/status/_cleanup_fix_export_redline_decision_page.md`，由清理工作的 t12 落盘到 `docs/knowledge/` 并登记到 `MEMORY.md` 的 `## Decisions` 段。
- **不建议**在清理工作中顺手做本任务——那正是本债务的成因模式。