# gotcha: 落后 checkout + init --force 重生成 = 全线崩塌（0/213），且增量判定全程绿灯

**日期**：2026-10-23 崩塌 / 2026-10-24 定谳（对抗复核完整链见 data/status/_init_force_20261024.log 时代与会话记录）

## 现象

`cli.py init --force` 强制重建 IDB 后全链重跑，probe 读数 **S2 0/213 · fail_own=0 ·
fail_imported_only=213**——全部单元死在**公共头**上（census `root_blame`：
`pal3/src/Misc/RoleAttRemarkSkills.h` + `include/pal3/gen/_ns_udts.h`）。
崩塌前最后一次健康读数是 S2 123/214（同日晚 20:21，55617884e）。

直接错误链：`_ns_udts.h` 第 5 行 byval-include `RoleAttRemarkSkills.h`，而后者按值使用
`_inline_RoleAttRemarkSkills_skillCount`，该类型定义在 `_ns_udts.h` 第 201 行——
**include 先于定义的循环序** ⇒ C2079 × 全 TU。此顺序缺陷的修复
（`_block_byval_deps` 分层发射）已在 **2183b71bd（2026-10-23 15:30）** 落库，
但其注释里记录的失败签名与本次崩塌逐字相同——**修复已存在，只是崩塌机器上没有**。

## 为什么（三层合谋）

1. **双机谱系分叉**：origin/master 在 Linux 侧推进到 319dd77e5（含 dae624431 双写点合并、
   2183b71bd 分层发射）；Windows 侧本地 master 停在 **ddb29a290（10-20 23:32，落后 3 天）**
   且此后未再 pull。init --force 跑在**无修复代码**上。
2. **init --force 是唯一的全量重生成触发器**：日常 codegen 是"只加不减"的增量形态
   （scoped 模式跳过头文件重生成、`include/pal3/gen` 不被清理也不被校验），
   陈旧/侥幸能编的树可以存活数天；init --force 把整棵输出树从 fresh IDB 一次性重算，
   潜伏的发射缺陷**当场全量引爆**。
3. **增量判定对头文件树全盲**（本崩塌的掩盖机制，已修）：`tools/check_incremental.py`
   的 12 项输入 hash 不含 `include/pal3/gen` ⇒ 头文件被删/空壳/陈旧时
   codegen/probe 照常跳过 ⇒ 崩塌不可见，直到有人跑全量 probe。

另两件同晚连环事故（同一考古会话）：
- **sparse-checkout 误操作**：`!.wine-t2` 单条 pattern 在非 cone 模式 = 排除全部
  （6034 文件 skip-worktree 剥空工作树）。本意只是排除 wine prefix（其 `dosdevices/c:`
  符号链接在 Windows 无法落盘）。正确写法：`/*` + `!/.wine-t2`（非 cone）。
- **free_functions.h "空壳版"**：pre-dae624431 代码的预生成写点只出声明零前向声明
  （单独 include ⇒ 102 error 至 C1003 截断）；它不是本次崩塌的直接死因
  （当晚全量写点因 free_functions.cpp 在 census 单元表里可证已执行），
  但属于同根因（旧代码 + fresh 数据）的另一表现。

## 后续实证（2026-10-24 恢复会话）：free_functions.h 的"不可见"还有第二层

修复代码 + init --force 重建后首验：C2079 循环消除 ✓，但 **C1083 ×152**
`Cannot open include file: 'free_functions.h'` —— 文件已生成（全量版），
但落在 `include/pal3/gen/`，而：

- emit 发射的是**裸名** `#include "free_functions.h"`（5d96faefb 2026-06-14 起）；
- probe `/I` 只有 `include`、`pal3/src`、编译器 Include——**没有 include/pal3/gen**；
- `stage5_fixup._load_free_func_names()` **硬编码读 `pal3/src/free_functions.h`**；
- free_functions.h 是**唯一**跟随 `cfg.output_headers`（机器本地、gitignored 的
  pipeline.toml）漂移的产物；类头恒在 pal3/src、_ns_udts.h 双址写。
- 健康机器（Linux）靠 toml/config 默认 `output_headers="pal3/src"` 成立；
  本机 toml 写了 `include/pal3/gen` ⇒ 头文件写入无人引用的地址 ⇒ 编译器不可见。

⇒ **"文件没创建"与"创建了但编译器看不见"在该位置上是同一表象**；且这类
机器本地配置漂移在双机场景下不可见（toml 不进 git）。根治方向（代码层，
需单独 TDD）：include 形态改路径形 `pal3/gen/free_functions.h` 或发射侧
双址写，并把 stage5 硬编码路径与之对齐；短期修复 = 本机 toml 对齐健康配置。

## 何时使用

- **任何机器跑重管线（init/export/codegen/probe）前**：先 `git fetch` + 确认
  `HEAD == origin/master`；落后 checkout 上的管线读数不可信，也不许当作修复验证。
- **init --force 后**：必须跟一次**全量** codegen + probe 当场读数（陈旧产物全被
  重算，任何潜伏发射缺陷会在这一轮集中暴露——这是特性不是故障，正好照妖镜）。
- **S2 全绿单元 = 0 / fail_imported_only = N_total 形态**：先读 census `root_blame`
  定位公共头，别逐 cpp 修——那是共享头层面的单点故障。
- **见 `!.xxx` 单条 sparse pattern**：非 cone 模式下这是"全排除"，必配 `/*` 包含条目。
- 排查此类"读数断崖"时，`__pycache__/*.pyc` 头部 16 字节（source mtime+size）+
  `git reflog --date=iso` 可精确重构"当时跑的是哪版代码、谁动过工作树"。
