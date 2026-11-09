# 方向定谳：A 面回归主攻，B 面冻结为研究线（2026-11-09）

## 决策

**A 面（IDA/Hex-Rays 主产物线）回归主攻方向；B 面（Ghidra/reconstruct + VC6）冻结为研究线。**

原设想"B 面快速收敛→收益回馈 A 面"——收益已兑现并沉淀，继续投入边际收益递减，正式转线。

## 数据依据（2026-11-09 决策时点）

| | A 面 | B 面 |
|---|---|---|
| 水位 | 131/215 probe ok（61%）| 截断 ~3654 / 24.3 万行（1.5%）|
| 剩余 | 1096 错 / 84 独立 TU（均值 13，56 个 ≤10 错）| C1003 封顶 + 98% 区域未编译 |
| 瓶颈 | 无结构性阻塞 | 渲染器 P1（TS 根治）未做 + nsfix 机制脆弱 |
| 确定性 | TU 独立编译，进度可数 | 链非确定性（P0 停损 8c0cb17 已止血但机制未根治）|

## B 面已兑现资产（回馈 A 面，实测）

1. **净减 26 组错误码**（C2440 −251 / C2664 −175 / C2039 −77 / C2227 −52）
2. **gbengine.def 签名库 + nsfix siglib**（1019 导出已解析）——dll 签名权威
3. **C2084 真双注消歧 ×4**（vtable 结构证据裁决，落 annotation 层）
4. **DBCS 注释吞行检查器**（tools/fix_vc6_dbcs_comment_splice.py，0/215 根因治理）
5. **编译器-as-oracle 战术** + 分层归责原则定谳

## B 面冻结状态

- 老树（pal3-redivivus/reconstruct-out）**冻结为工作基线：只 build，不再跑 adapt 链**
- P0 停损已落（nsfix rebuild 边界守恒 + 孤儿迁移 + P0.2 定义守恒断言，8c0cb17）——下次真 regen 时生效
- 渲染器根治（P1：dll 签名库集成 / ctor 上游化 / 表达式层）挂长线专项，作为独立验证线的重启点
- 已知冻结态读数：102 错 @ 3654（子头文件族 gbParticleEffect.h 等）

## A 面首战清单

1. **9 个新失败**（已归因）：thunk 渲染 ×1（UIListBox）/ C2100 ref-param ×3（CEffect/CEffGrid/CEffgbParticle）/ 声明闭合 ×2（JusticeBookUI UIParticle / SystemUI dword_56F22C）/ pszRoleDir undeclared ×2 / free_functions mangled 泄漏
2. **78 持续失败单元**逐批歼灭（批大小 15-20 单元，按错误族聚类）
3. 215/215 后 → wine_link 链接 → byte-match 主线
