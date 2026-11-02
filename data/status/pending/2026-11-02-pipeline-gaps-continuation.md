# 管线缺口续账（2026-11-02 变向收口）

> 变向：主线转「ghidra 双轨验证」（见 docs/specs/2026-11-02-ghidra-dual-track-spec.md）。
> 本文件=既有轨（IDA/Hex-Rays 字节轨）在途缺口全量，双轨告一段落后回来继续。

## A. 修复域在途（复核/审计已定性待做）

1. **Fix2 `*stru_` 类型取证**：`*stru_17A7BB0` C2100 簇（~25 错）——g_17A7B 六视图 buffer
   应为数组型（`*stru_=元素访问`），按 spec 层 3 修**类型**非修渲染
2. **Fix3 C2084 thunk 对三件**：UIListBox/CCBProtectWindow/CCBFiveNimbusWindow `Destroy`
   thunk→体双注册 → 合成物机制接管（需逐对字节证：0x43DE90 thunk/0x43E520 体已证）
3. **层③ 重复注册 2 组**：`sub_4C0510_0510`×2（CEffSParticle）· `nullsub_75_override_0610`×2
   （RenderTarget2）——同名同签双址，需裁（合并/正名）
4. **spec 层 3/4 逐条**：C2440 类型标注（CCBPanelSlot 等 27 条）· C2039/C2227/C2653 归属
   （RoleAtt→SaleUI_SortData 等 18+ 条）——见 data/status/s2_regression_fix_spec.md

## B. 裁决队列（不准确=不判定，证据包待产）

5. **Q1×20 this 噪声疑似重复**（含 Destroy 全局 3 方：stdiobuf*this=误归属实锤例）
6. **Q2×24 伪重载/全同**（CCBStageRole_DispatchUpdate×3 同签三方等）
7. 9/14 vs 远端基线余量（合流中期态）

## C. 结构债（复核 D 系列记账）

8. **TOS D3 双副本 10 面**：apply 局部 `_mangle_vc6` vs vc6_mangler——委派=绷带；
   收编须**逐面归并禁整体替换**（局部副本锚定形在嵌套返回型上是对的）
9. D5 preflight mangled 键缺 cv（const 重载假冲突潜伏）· D8 `--bootstrap` 无理由参数
   （洗白面）· D9 PtrVec_InsertN 对「参型实异」=猜测封印（观测挂账）
10. 重载换轨余量：`__ovl_` 残余退役=Q 裁决完成后收尾（G1/G2 已清 147 件）

## D. 已规划未开工（双轨收官后续排序）

11. **变换必要性审计**（开关矩阵+probe 裁判：A/B/C 分级，`__ovl_`=C 类已砍样例）
12. **边界登记册**（hexrays_limit 15 文件过三路：转注解/转手写/真硬接受）
13. **2a 结构借壳**（现有 Python 变换插件化+tiering+开关——零 L1 风险重构）
14. **增量基建**（loop 20min→2-3min：export 类型摘要失效/codegen hash 跳过/
    probe 单元级增量/match 并行）
15. (ii) 真型取证重注册（char[N] 猜测已撤回，0xD8C2E8/0xD8C2C8/0xDE8B40 pending）

## E. 运维注意

- **idalib worker 与管线 idat 互斥**（gotcha 已记）：跑管线前 `kill idalib_server` 进程
- commit message 须带 Evidence/Confidence 段（纪律钩）
- annotation 变更=完整管线验证；L1 引用须带三限定
