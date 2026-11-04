---
name: hidden-collision-strip-machinery-divergence
description: 隐性撞名三联病灶——collect 无条件剥戳(定义侧)/emit_headers 撞则不剥(声明侧)判据不对称 + cxx_sig_key 末参名泄漏 + 棘轮 grandfather 冻结先于门禁存在的撞名；戳归一必须单点在 annotation 层
type: gotcha
created: 2026-11-04
sources: [out/_adversarial_review_verdict.md, session-2026-11-04 ovl 迁移]
---

`__ovl_` 消歧戳让"同类同名同签双址"撞名在数据层隐形，剥戳后在生成代码里物质化为 C2084——三道防线各失一处，全放行。

**为什么：** ①剥戳实现曾有 **3 个语义不一致副本**（collect strip_ovl 只认 hex 尾无条件剥+正文重写=定义名剥落真路径；emit_headers strip_stamp 撞则不剥；emit_cpp 正则只清调用形）——声明侧防撞/定义侧盲剥的不对称直接制造双定义（对抗复核定谳 out/_adversarial_review_verdict.md #1，emit_cpp 正则对定义实为 no-op）；②专职撞名闸 cxx_gate 的 `cxx_sig_key` 参名剥离正则不吃行尾 ⇒ **末参名泄进键**（`int,int,intnVal3` vs `int,int,inta4`）⇒ 真撞名被判"合法重载"，4 条 Destroy 被抓恰因零参无名可漏；③棘轮 grandfather 把先于门禁 bootstrap 存在的撞名冻结成存量（UIScene 一条还是注解认领粒度假阳性：门禁判据与 codegen 路由粒度分叉）。

**何时使用：** 任何"多副本归一化"（剥戳/键形/判据）必须单点化并跑防回流锁（tests/test_ovl_migration_lock.py）；改名批须做**改名前后撞名对账**（census：data/status/tail_name_census_20261104.md）；棘轮 bootstrap 前先分账"破坏性存量"（同名同签双正文=必然 C2084，不得 grandfather）与良性存量；门禁正则改键形须重跑其单测 + 重冻基线。
