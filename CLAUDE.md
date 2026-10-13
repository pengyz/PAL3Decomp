# PAL3 Decompilation Project

**匹配反编译**：目标为 MSVC 6.0 SP0 编译的 PAL3.exe 生成字节匹配的 C/C++ 源码。

## Pipeline Philosophy

### 编译是不可逆的，我们做的是"再创作"

C++ 编译成二进制是一个**不可逆的信息丢失过程**。类型信息、类层次、继承关系、模板实例化——全部坍缩为指令和数据。我们不是在"恢复"源码，而是在**再创作**一个能输出完全相同二进制的 C++ 程序。

这个认知决定了所有设计决策的优先级：**字节匹配 > 代码优雅 > 工具链便利 > 个人偏好**。

### 两阶段管线

```
annotations → apply → IDB → Hex-Rays → decomp JSON → codegen → C++  →  Phase2: 手工fix
↑________________________ Phase 1 ________________________↑    ↕ 字节比对
```

**Phase 1 — 自动化管线**：annotation 为 IDA 提供类型信息，激发 Hex-Rays 输出最好的伪代码。codegen 将 Hex-Rays 的输出转换为可编译的 C++（修补 Hex-Rays 不支持的语法如引用、模板）。目标是在零人工干预下生成质量尽可能高的源码。

**Phase 2 — 手工修正**：当逼近 Hex-Rays 能力上限后，通过字节比对工具定位不匹配处，手工修改源码做字节级别的 fix。

### Phase 1 各层职责

| 层 | 职责 | 红线 |
|----|------|------|
| **annotation** | 为 IDA 提供类型信息（结构体、函数签名、全局变量），让 Hex-Rays 输出尽可能高质量的伪代码 | 不能直接修改 codegen 产物 |
| **apply_annotations** | 将 annotation 写入 IDB，不改变语义 | 不能编造信息 |
| **Hex-Rays** | 基于 IDB 类型信息生成伪代码 | 能力有限（不支持引用、模板） |
| **codegen** | 将 Hex-Rays 输出转换为可编译 C++，修补 Hex-Rays 的语法缺口 | 只能做等价变换，不能编造信息 |
| **check_annotations** | 验证 annotation 内部一致性，防止矛盾信息写入 IDB | 不检查 codegen 产物风格 |

### annotation 质量的投入产出

充分标注函数归属（struct methods）和全局变量能使 Hex-Rays 输出 **`this->member` / `g_GlobalName.field`** 而非 **`*(type*)(this+offset)` / `*(DWORD*)0xADDR`**。Phase 2 的人工编辑量与此直接相关——标注质量越高，Phase 2 工作量越小。投入产出的最优策略是：**在 Phase 1 做所有能做的标注，即使某些信息在 Phase 1 不会立即产生收益**。

### 影响字节匹配的核心困难

1. **CRT 边界**：哪些函数是 CRT 的（编译器链接而来）、哪些是游戏自带的？区分错误导致重复定义或遗漏。
2. **vtable 布局**：虚函数声明顺序、COMDAT 折叠、调整 thunk 必须精确匹配 MSVC 生成规则。
3. **模板特化**：Hex-Rays 不支持模板，`template_bases.json` 做桥接映射。
4. **优化反编译产物**：Hex-Rays 对优化后代码的反编译可能"看起来对但字节不对"。
5. **（2026-09-20 更正：本条已过时，已删除该主张）** 曾经的状态是"无实时字节验证"；
   现在**已有自动对比机制**：`pipeline/cli.py match`（`cmd_match`）+ `pipeline/compare_pal3.py`
   + `data/status/s4_baseline.json`，且 `match` 是**强制检查点**（见下方检查点表）。
   ⚠️ 但需注意：`match EXIT=1` 可能是**编译崩塌的下游现象**（S2 绿单元=0 时无可比对对象），
   且 L1 棘轮会**回写基线**（`pipeline/cli.py` 的 ratchet 分支）⇒ **不能事后查基线文件判断退化**，
   必须在同一管线运行中当场读输出 ✓。

### 设计原则

- **字节匹配是第一优先级**：一切决策以此为准。
- **全局变量不依赖 export _globals**：二进制中存在的全局就应该可标注，不取决于 IDA 是否将其列为 `_globals`。codegen 的就地 extern 机制是合理的 fallback。
- **check_annotations 不强制执行风格规范**：它的角色是发现标注矛盾，不是强制执行组织规范（如"全局必须在 globals.h 中"）。
- **codegen 的注解读取必须经单一读点**：`pipeline/gen/annotation_view.py`。
  历史上这条写作"codegen 不读 annotation（绝对禁止）"，但实测 codegen 侧有 10+ 处注解直读
  （`emit_headers.py` / `ast_transform.py` / `data.py` / `collect.py` / `stage4_substitution.py`），
  属**已声明的例外**（取舍见 `pipeline/ida/export_full.py` 头部 `[t4-DECLARED-EXCEPTION]`）。
  2026-09-20 已把**其中大部分**收敛到该单一读点，并逐处验证产物字节不变。
  **【2026-09-20 更正（经独立复核证伪原措辞）】并非"全部收敛"** ✗ —— 实测**仍有 3 处直读**：
  `pipeline/gen/stages/emit_headers.py:3259-3260`（`data/annotations/globals.json`）·
  `pipeline/gen/ast_transform.py:336-342`（`structs/*.json`）·
  `pipeline/gen/stages/stage3_cleanup.py:107-110`（`structs/<Cls>.json`，**此前不在任何违规清单里**）。
  ⇒ **当前措辞应为"尚有 3 处"**；修完这 3 处后才可改回"全部收敛" ✓。
  规则本身不变且**可检查**：新增注解直读必须走 `annotation_view`。
- **编译错误不是问题本身**：C2440/C2664 等是标注错误的**表象**。盯着错误码修是治标不治本。真正的任务是理解原始代码的意图——内存布局、复用模式、生命周期——然后让 annotation 正确表达它。错误自然消失。
- **禁止"试错式修改"**：不理解内存布局之前，不修改 annotation。先用 IDA 查全所有访问点，画出完整的使用图景，确认场景和约束，再动 annotation。

## Project Overview

- **Compiler**: MSVC 6.0 SP0 (`tools/compilers/msvc6.0/`), `/O2 /Ob2 /Oi /Ot /Oy`
- **Toolchain**: `cmake/toolchain-vc6.cmake` — Ninja + wine_cl.sh
- **Graphics**: DirectX 9, D3DX Summer 2003
- **Audio**: Miles Sound System, **Video**: Bink
- **Script**: SCE bytecode VM (~140 opcodes)

## 项目强约束

以下规则**必须严格遵守**，任何违反都将导致代码质量下降或字节不匹配：

### 管线规则
- **编译错误不是 annotation 回退理由**：更精确的类型标注可能暴露 codegen 适配问题，导致更多编译错误——这是正常的，不构成回退标注的理由。
- **export 不读 annotation**：`export_full.py` 只能从 IDB 读取数据，不能直接读 `data/annotations/` JSON 文件。

### annotation 规则
- **每一处 annotation 修改必须有二进制直接证据**。证据等级见 pal3-pipeline skill 的置信度规则表。A 级证据（指令中的 reg+disp32、绝对地址）是偏移修改的最低门槛。
- **禁止猜测性修改**。没有二进制证据不能修改偏移、类型、函数签名。PDB 数据只能作参考（来自 PAL3A，偏移可能与 PAL3 不同），不能单独作为证据。
- **禁止批量修改未验证字段**。每个偏移/类型变更必须逐一验证，不能批量推断。
- **禁止伪语义命名**：`m_nState_4968`、`m_fParam_0A0` 这类用地址后缀伪装的名字没有语义价值，和 `_todo_` 没有区别。不确定含义时保留 `_todo_`。
- **禁止仅凭 Hex-Rays 反编译文本推断偏移**——除非 IDB 已 apply_annotations 且结构体正确。
- **禁止仅凭 signature this 修正函数归属**——必须有 decomp member access evidence（函数内 this->member 引用的成员在目标类中存在且不在原类中存在）。

### inline union/struct 语法（2026-06-20 新增）

对于内存复用/重叠的字段，annotation JSON 的 `type` 字段可使用 dict 形式定义 inline union/struct：

```json
// 内联 union — 同一偏移的多视图
"offset": {
  "name": "field_name",
  "type": {
    "union": [
      { "type": "BaseType",      "name": "variant1" },
      { "type": { "struct": [    // 嵌套内联 struct
        { "offset": 0, "name": "member1", "type": "int" },
        { "offset": 4, "name": "member2", "type": "float" }
      ]}, "name": "variant2" }
    ]
  },
  "source": "overlay:..."
}
```

生成效果：
```cpp
union { // +0xN
    BaseType variant1;
    struct { int member1; float member2; } variant2;
} field_name;
```

关键约束：
- `struct` 内成员的 `offset` 是**相对于外层 struct 起始**的偏移
- type 可嵌套：`union` 成员可包含 `struct`，`struct` 成员可包含 `union`
- 同一 struct JSON 内允许多个不同偏移的 inline union/struct
- 此语法**只适用于本类 `known_members` 范围内的偏移**（不能跨越继承边界在基类区域内插入成员）
- 跨继承边界的内存复用应在定义该偏移的基类中标注 union
- **`union` 本身即为 overlap 声明**：`check_annotations` 遇到 `type={"union":[...]}` 时会自动跳过该成员与后续成员的 overlap 检测，无需额外在 `source` 中写 `overlap`

### workaround 规则
- **禁止破坏性 workaround**：不为了编译通过而丢失类型信息或结构体定义。`void*`、`int`、`char[]` 等泛化类型只在确实不知道真实类型时使用。
- **后处理只做等价变换**：codegen pipeline 只做不改变语义的代码转换，不编造信息。
- **IDA 层能解决的问题在 IDA 层解决**：类型标注、结构体导入、函数签名等应该在 IDA 中通过 annotation 完成，不在 codegen 层打补丁。

## AI 工作流纪律

以下工具必须在指定节点自动运行，不可跳过：

### 强制检查点

**先跑一次状态预检**（秒级、只读，不刷新任何基线）：`python pipeline/cli.py status`
—— 它打印一次迭代的**唯一权威顺序**、三份基线的对照、以及**已知恒红门禁**。
⚠️ 在干净 HEAD 上 `codegen all` 与 `match` 目前**恒 exit 1**（陈旧棘轮造成的假失败，见 status 输出）；
不知道这一点就会把假失败当退化，或把真退化当噪声。

| 时机 | 工具 | 命令 | 失败处理 |
|------|------|------|----------|
| **动手改任何东西之前** | **病灶层检查（必做）** | 见下节 | 答不出"病灶在哪一层 / 消费者实际读哪个文件·哪份声明"就**不许动手** |
| **一轮完整迭代** | 一键循环 + 基线断言 | `python pipeline/cli.py loop --expect-s2 127/209 --expect-errors 1337 --expect-l1 132` | 断言不满足 ⇒ exit 1；恒红门禁被**显式标 TOLERATED**，不静默吞掉。⚠️ **基线数字须随实况刷新**（2026-10-10 对抗复核实证：原 `76/205 · 2140 · 38` 已陈旧 3 周、恒红 ⇒ 门禁失去判别力；2026-10-12 T6 `101/209 · 1720 · 86`；2026-10-13 T16 `112/209 · 1434 · 104`；2026-10-13 T25 `118/209 · 1383 · 115`；2026-10-13 T29 `121/209 · 1372 · 120`；2026-10-13 T33 `125/209 · 1361 · 129`；2026-10-13 T36 `125/209 · 1353 · 129`；2026-10-13 T39 `127/209 · 1339 · 132`；2026-10-13 T42 `127/209 · 1337 · 132`（迭代 8 收口态，T40-T41 两任务）） |
| **codegen all 后** | 编译回归检测 | `python tools/compile_regression.py` | 发现退化立即报警，不提交 |
| **apply 后** | annotation diff | `python tools/annotation_diff.py` | 显示变更摘要，确认无意外修改 |
| **probe_compile 后** | 错误分类 | `python tools/error_classifier.py --summary` | 输出根因分布，指导下一步修复方向 |
| **probe_compile 后** | 字节匹配裁判 | `python pipeline/cli.py match` | L1（字节全同函数数）不得回退；partial 的字节 diff 是注解布局/归属错误的直接证据 |
| **修改 struct annotation 后** | 布局验证（**编译器裁判**）| `python tools/audit_type_layout.py --only <Cls>` | 发现布局问题立即修复 |
| **任何"无证据/无冲突"结论** | 语义/类型证据（**三形态**）| `python tools/audit_member_semantics.py --class <Cls>` | 否定结论必须来自**权威批量原始扫描** ✓ |
| **函数归属改动** | 归属证据（**可证**）| `python tools/audit_attribution_evidence.py` | 只看 contradiction 告警，人工裁定 |
| **任何修复提交前** | **证物报告** | `python tools/verify_fix.py --class <Cls>` | 成员偏移+**sizeof**+传递依赖+端到端+基线；有问题 ⇒ 不提交 |
| **annotation 批量改动** | **四道门** | ①布局等价 ②`loop --expect-errors`不增 ③`l1`不降 ④证据自校验 | 缺一不可 ⇒ 见 `annotation-audit` skill |

> ⚠️ **不要再用 `tools/audit_layout.py` 作布局判据**：它比的是「注解 vs `asm/pal3/ida_structs.json`」，
> 而后者是 `apply_annotations.py` **从这些注解写进 IDB 再导出**的 ⇒ **同源比较、恒等、无判别力** ✗
> （该脚本 docstring 自认 "check 1 是同源比较、恒等、无判别力"）。现代替品：`tools/audit_type_layout.py` ✓

### 病灶层检查（动手前的第一件事）

**规则**：在修改任何"跨层"代码（annotation / apply / export / codegen / stage1–5 / 宏头）之前，
必须先**只读地**回答三个问题，并把答案写进 commit message：

1. **病灶在哪一层？**（例：是 Hex-Rays 的原始输出就错，还是 codegen 某 stage 改坏的？）
2. **消费者实际读的是哪个文件/哪份声明？**（`#include` 链、`/I` 顺序、同名声明谁先被找到）
3. **报错还缺什么信息？**（例：`does not take N parameters` 只给个数、**不给类型** ⇒ 不能据此推断重载）

**为什么必须**：本仓实测——**11 次**在没有这个验证时直接动手，**全部零效果或净回归** ✗；
而每次只读验证（`grep` 声明 / 临时 `#error` 探 `#include` 链 / `sys.settrace` 行级追踪 +
代理该模块的 `re`）都能**一步定位** ✓。详见
`docs/knowledge/gotcha_verify_the_layer_before_patching.md` 与 `docs/knowledge/debug_two_layer_localization.md`。

**配套**：定位完成后把**实测数字**写进被改代码旁的注释（例：`stage3_cleanup.py` 那个 `re.sub` 上方
记录了 `C2227 −41 / C2039 +22 / S2 ok 75→74 / L1 35→34`），下一个会话不必重新测量。

### ⚠️ 度量盲区：C1003 截断单元（评估改动前必看）

MSVC 在单个编译单元错误数超过 ~100 时以 **C1003** 停住（**2026-09-28 复核更新：现 2 个**
`Combat/CCBStage.cpp` · `free_functions.cpp`，各 102 条；`Combat/CCBUI.cpp` 已退出截断
——原文"实测 3 个"过时，33c45090 复核实证）。
后果：**在这些单元里修掉早期错误，列表会立刻被原本隐藏的后续错误填满** ⇒
`总错误` 与 `(code,msg)` 多重集**都可能完全不变** ✗。

> 实测（2026-09-21，`::ShowWindow` 补限定）：消失 **9** 条 `C2660 'ShowWindow' : does not take 2 parameters`，
> 同时露出 **9** 条**无关族**错误（成员函数指针 `C2296`/`C2440`、`__vftable` `C2039`）⇒ 总数 2150→2150。
> 那 9 条"新增"可**证明**是旧隐藏错误（改动只 touching `ShowWindow(`，不可能产生成员函数指针错误 ✓）。

⇒ 评估任何改动时，除 `总错误`/逐码净增减外，**必须同时看**：

* `python pipeline/cli.py status` 打印的 **C1003 截断单元表**（含"列表内最大行号"）；
* **最大行号变大 = 有真实进展**（上例 `CCBUI.cpp` 3389 → **3787**、`CCBStage.cpp` 3823 → **3855**）✓。

⇒ 发布门禁"改善 ≥ 新增"在**截断单元**上会**误判为中性**；此时以"新增错误是否与改动**同族**"+
"截断进度是否前进"作为判据，并在 commit message 里写明理由。

### 纪律编号现状（⚠️ 阅读前必看）

本仓历史文档里的 **`R1`–`R16` 不是一套统一编号**，同一个标签**至少有两种含义**：

| 标签 | 含义 A | 含义 B（同仓另一处） |
|---|---|---|
| `R1` | 编排者不得在子代理 running 期间编辑同一文件（`_d1_ledger.md:12`）| 规格评审意见编号（`_d1_ledger.md:1103`）|
| `R3`/`R4`/`R5` | 并行推进 / 预检前置 / parity corpus | 同上：规格评审意见编号（`1089`/`1105`/`1108`）|
| `R10` | 台账里是**问题标签** `Q3 R10`（`:261`）| 纪律定义在**另一个文件** `data/status/_batch_uistatic_reverted_20260920.md:29`；另在 `docs/specs/2026-09-15-plan-1to5-landing-design.md:555` 又是步骤号 |
| `R16` | 病灶层检查（`_d1_ledger.md:1343`）| `docs/specs/2026-09-15-cv-layout-design.md` 的**理由编号** R13/R15/R16 |
| `R9` | **不存在**（全台账 0 命中）| — |

⇒ **引用 `Rn` 时必须带文件路径**；`R1–R16` 这个说法是**事后聚合的异质标签**，不是 16 条可检查的规则 ✗。
可逐字验证的**通用纪律**只有：`R7`（确定性下游工具必须重跑）、`R11`（改工具必须跑其测试）、
`R12`（中止必须杀整条进程链并复核 census/baseline）、`R13`（补丁落地必须 grep 核实）、
`R14`（管线持有 IDB 期间不得并发 `idat`）、`R15`（新渲染/字符串逻辑先写纯函数单测）、
**病灶层检查**（`R16`）——原文见 `data/status/_d1_ledger.md`。

### Rn 统一引用格式（2026-10-07 文档债修）
引用 Rn 时必须带文件路径（例：R7（data/status/_d1_ledger.md））——异质标签不可裸引。

### 工具使用规范

1. **编译回归检测**（`compile_regression.py`）：
   - 每次 `codegen all` 后必须运行
   - 发现退化时：立即 `git diff` 检查变更，回退有问题的修改
   - 基线更新：只有确认无退化后才运行 `--update-baseline`

2. **错误分类**（`error_classifier.py`）：
   - 每次 `probe_compile` 后运行
   - 根据分类结果优先修复 `annotation_fix` 类（投入产出比最高）
   - `hexlimits` 类不修，`manual_idb` 类记录待办

3. **布局验证**（`audit_type_layout.py`，**编译器裁判**；`audit_layout.py` 已废弃 ✗ —— 同源比较无判别力）：
   - 修改 struct annotation 后必须运行
   - 检测到类型大小不匹配时：对比 IDA 导出，修正 annotation 类型
   - 典型案例：`CEffMgr.m_EffTable` 从 `tagEffObj[2048]` 改回 `_BYTE[584]`

4b. **两个回归门禁的分工（勿混用/勿误删）**：
   - `tools/compile_regression.py` = **`codegen all` 之后的即时快照闸**（基线
     `data/status/compile_baseline.json`，只比 ok/fail）。它读**缓存** `probe_census.json`，
     故**未跑 `probe` 时其结论无意义**。
   - `tools/regression_detector.py` = **`probe` 之后的正式对账闸**（基线
     `data/status/baselines/latest.json`，`(code,msg)` 多重集 + 剔除 C1003 + churn 识别 +
     `--before/--after`/`--self-test`）。
   - **检查点表缺了一步**：`codegen all` 与 `compile_regression` 之间**必须先跑 `probe`**，
     否则门禁验的是陈旧快照（见 `docs/knowledge/gotcha_compile_regression_reads_cached_census.md`）。
4. **annotation diff**（`annotation_diff.py`）：
   - `apply` 后运行，显示本次变更摘要
   - 确认无意外修改（如指针级别变化、类型大小变化）

### 修复优先级

基于错误分类结果（146 个失败文件）：
1. **annotation_fix**（49 文件，33.6%）— 最高优先级，投入产出比最高
2. **codegen_fix**（33 文件，22.6%）— 次优先级，需要 codegen 层修改
3. **manual_idb**（2 文件，1.4%）— 需要手动 IDB 调查
4. **hexrays_limit**（62 文件，42.5%）— 不修，记录为已知限制

## 项目共享记忆

[`docs/knowledge/`](docs/knowledge/)：跨会话的项目级共享知识（6 类 type：architecture/gotcha/pattern/debug/decision/reference）。引用前必须验证文件/字段仍存在（见该目录 README 的"引用前验证"）。单字段证据仍归 `data/annotations/CHANGE_LOG.md`，不进这里——这里只记通用规律和管线级坑。

会话中遇到平台坑、门禁失效、被纠正的方法、确认有效的取舍时，按 `docs/knowledge/README.md` 判断是否写入。

## Skill Routing

管线、annotation、IDA 查询、编译错误分析 → 加载 `pal3-pipeline` skill
annotation 的**布局/类型/名字/归属审计**（DAG 序、三形态证据、四道基线门、盲区与反模式）→ 加载 `annotation-audit` skill
