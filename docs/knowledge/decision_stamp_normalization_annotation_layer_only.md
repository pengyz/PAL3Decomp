---
name: stamp-normalization-annotation-layer-only
description: 戳归一（__ovl_/地址尾消歧戳）只发生在 annotation 层——发射/收集/调用形一律原样透传；让隐性撞名变真撞名，语义正名走证据裁决
type: decision
created: 2026-11-04
sources: [session-2026-11-04 ovl 迁移（用户裁定）]
---

戳名（`__ovl_XXX`/`_ovl`）归一只在 annotation 层做（2026-11-04 全量剥除 17 处 + 纠偏 6 处）；管线任何层不再剥戳（collect/emit/ast_transform 三处已退役，防回流锁 tests/test_ovl_migration_lock.py）。

**为什么：** 发射层剥戳是"隐性撞名"制造机（定义侧无条件剥 vs 声明侧撞则不剥的判据不对称 ⇒ 同 TU 双定义 C2084 静默生成）；annotation=真值源原则要求归一化在数据层完成，管线只消费。**让隐性撞名变真撞名**（用户铁律）：剥戳后同名同签双址必须当场显形（cxx_gate 硬红 + C2084），不保留戳名消歧掩盖——显形后按 data/status/name_adjudication_queue.md 逐对二进制取证正名。

**何时使用：** 新增名字消歧需求时（禁止再引入 `__ovl_`/地址尾戳）；遇到 `Name_XXXX` 尾名先查 data/status/tail_name_census_20261104.md（真撞 26/重载 19/单例 8）再动；合成物族（crt_sub/_sdtor/SingletonThunk）地址尾=身份，不剥（D7 教训：误剥产生假碰撞）。
