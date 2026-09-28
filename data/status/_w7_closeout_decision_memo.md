# W7 基线收官决策备忘（2026-09-28，供用户确认项 + 自动执行面）

## 〇、权威现状（`cli.py status` 实测 2026-09-28T02:47）
- **当前普查：S2 95/208 · 总错误 1657**；
- **两份 S2 基线互相矛盾**：compile_baseline.json **79/204**（9-24）vs baselines/latest.json
  **89/208**（9-27 03:40）——均陈旧于现况 95/208；
- C1003 截断单元 2 个（CCBStage 102 错/最大行 3843；free_functions 102 错/最大行 2874）
  ——**进展看最大行号**不看总数；
- L1 棘轮已回写至 68（s4_baseline），下次 match 读数待测。

## 一、需用户确认的棘轮决策（纪律：--update-baseline/--rebaseline/--save-baseline 均为显式动作）
| 决策点 | 现状 | 建议 |
|---|---|---|
| ① `compile_baseline.json`（S2 棘轮） | 03:40 陈旧（79/204），现 **95/208**（含 6 转绿+文件集变化）| 刷新为当前读数——3 天陈旧已造成多轮"假回归"归因成本 |
| ② `baselines/latest.json`（regression_detector） | 03:40 陈旧 | 同步刷新（与 ①同批决策）|
| ③ `s4_baseline.json` L1 棘轮 | 63→**68**（可比总体 367/438→396/469 已变）| `match --rebaseline "<理由>"` 显式对齐——语料增长型变化，非字节回退 |
| ④ 全局退役方案的 merge-ratchet（extern 2034/2299） | 未设 | 无需动作（非门禁）|

## 二、自动执行面（无需确认）
1. `pipeline/cli.py loop --expect-s2 95/208 --expect-errors <现读数> --expect-l1 68`（恒红门禁显式 TOLERATED）；
2. 知识回写收尾：emitted_layout_drifts gotcha 数字更正（101/169 → 当前）+ 双层定位案例补充；
3. 台账归档：本会话 30+ status 文档索引。

## 三、尾账清单（挂 W7 后续，不阻塞收官）
- C2372 off_5AC098（W3 尾：标量/数组双启发不一致，W5 类型审计）；
- CreateEff W6 参数回收缺口（695bcbb4 记账）；
- bDestRole/gbVec3D* 两条新形态（b6ed6ed5 Q2 在裁）；
- C2664 CreateObj 族（CCBSystem 签名错配，独立工项）；
- 6 个 ast_transform 存量测试失败（W6 已裁归该域）；
- 4 文件风格归一化（Logger/tagCam/tagCmdData/tagRoleTask，P1-3 封杀面）；
- m_nUnk61D8 键错位（先 normalize_key 11104→7752 再重裁）；
- nState/pTextureWrap4 双有证争端（+0x1C）；
- W1 判据④尺寸锚未实现（_meta.caveats 如实标注）。
