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
5. **无实时字节验证**：缺少自动对比机制，无法及时感知偏差。

### 设计原则

- **字节匹配是第一优先级**：一切决策以此为准。
- **全局变量不依赖 export _globals**：二进制中存在的全局就应该可标注，不取决于 IDA 是否将其列为 `_globals`。codegen 的就地 extern 机制是合理的 fallback。
- **check_annotations 不强制执行风格规范**：它的角色是发现标注矛盾，不是强制执行组织规范（如"全局必须在 globals.h 中"）。
- **codegen 的注解读取必须经单一读点**：`pipeline/gen/annotation_view.py`。
  历史上这条写作"codegen 不读 annotation（绝对禁止）"，但实测 codegen 侧有 10+ 处注解直读
  （`emit_headers.py` / `ast_transform.py` / `data.py` / `collect.py` / `stage4_substitution.py`），
  属**已声明的例外**（取舍见 `pipeline/ida/export_full.py` 头部 `[t4-DECLARED-EXCEPTION]`）。
  2026-09-20 已把它们**全部收敛到该单一读点**，并逐处验证产物字节不变 ⇒
  现在的规则是**可检查的**：新增注解直读必须走 `annotation_view`。
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

| 时机 | 工具 | 命令 | 失败处理 |
|------|------|------|----------|
| **codegen all 后** | 编译回归检测 | `python3 tools/compile_regression.py` | 发现退化立即报警，不提交 |
| **apply 后** | annotation diff | `python3 tools/annotation_diff.py` | 显示变更摘要，确认无意外修改 |
| **probe_compile 后** | 错误分类 | `python3 tools/error_classifier.py --summary` | 输出根因分布，指导下一步修复方向 |
| **probe_compile 后** | 字节匹配裁判 | `python3 pipeline/cli.py match` | L1（字节全同函数数）不得回退；partial 的字节 diff 是注解布局/归属错误的直接证据 |
| **修改 struct annotation 后** | 布局验证 | `python3 tools/audit_layout.py` | 发现布局问题立即修复 |

### 工具使用规范

1. **编译回归检测**（`compile_regression.py`）：
   - 每次 `codegen all` 后必须运行
   - 发现退化时：立即 `git diff` 检查变更，回退有问题的修改
   - 基线更新：只有确认无退化后才运行 `--update-baseline`

2. **错误分类**（`error_classifier.py`）：
   - 每次 `probe_compile` 后运行
   - 根据分类结果优先修复 `annotation_fix` 类（投入产出比最高）
   - `hexlimits` 类不修，`manual_idb` 类记录待办

3. **布局验证**（`audit_layout.py`）：
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
