# W2-PAL3 落地字节面门核对清单（2026-09-28，随 pwsh-25 全链出链即跑）

## 预期生成物 diff 白名单（门 b）——逐符号登记，超白名单即红
| 产物 | 预期变化 |
|---|---|
| `data/annotations/structs/PAL3.json` | −20 成员（已落 ✓ git diff −100 行）|
| `data/annotations/globals.json` | +7 条目（已落 ✓ +35 行，含 g_nSoundTargetSeq 等纠真名）|
| `pal3/src/GameBase/PAL3.h` | −20 成员行 + `_gap_` 合并（0x1358..0x1384 区段并入邻近 gap）|
| `pal3/src/globals.h` | +7 extern（g_nSoundTargetSeq/g_nVideoTargetSeq/g_nEffectTargetSeq/g_nRenderTarget2Count/g_nCEffExplosiveCount/g_nCEffCylinderCount/g_nMeteorChainCount）|
| `pal3/src/globals.cpp` | +7 定义 |
| 其余 pal3/src/** | **零变化**（渲染只影响 PAL3 成员路径与上述全局名；若出现其他文件 diff ⇒ 逐条归因）|

## 门 (a) 受影响 TU 逐函数字节 diff=0
- 受影响 TU：引用 g_PAL3.<被删成员> 渲染的单元（PAL3 成员渲染面）+ 引用 7 个改名全局的单元；
- `pipeline/cli.py match` 同运行读 L1：**只看受影响 TU 的逐函数 diff**（聚合 L1 禁用——棘轮回写）；
- 已知例外论证（若出现）：渲染形态 `g_PAL3.m_x` → 裸 `*(T*)addr`/static——同一绝对存储，
  预期指令不变；**不得先验断言**（beb91db4 Q2），逐函数当场证。

## 门 (c) 符号尺寸表
- ⚠️ **勘误（2026-09-28，落地事实推翻原措辞）**：W2-① 收缩批**已改** binary_size
  91024→4936（`w2_batch_pal3_shrink.json` set_size 实测落地）——原"binary_size 不动"
  仅适用于纯删除批；收缩批的尺寸变化是**设计目的**（释放区间内被吞全局）。
- `audit_type_layout --only PAL3` 用**行数↓红度不升**口径（现 87/87 系统性偏移基错位全红，
  beb91db4 P1-c）：删后预期 ≈57 行同构红 ⇒ 判据=行数↓ 且红行数不增。

## 门 (d) 删除可追溯（方案 v2 精确化条文）
- 20 条各带归属级否定证据（static 块锚 / 同址既有全局视图 / 多函数访问+独立角色）✓ 批次 evidence 已按 C1 重写；
- 地址处置闭合：9 statics 随块归函数 static（正名属后续）· 3 条由既有全局条目承接 · 7 条由 global_add 新条目承接 · 4972 随块；
- 落地核对=渲染不断链 + 新 C2065=0 + 键可追溯。

## 门 (e) 全链重生成后 ida_structs.json 与注解同步
- export 后 `_globals` 应含 7 个新全局（g_nSoundTargetSeq 等）；
- PAL3 的 data_members 应少 20 行；
- 幻影两族（auto:overlap 37+4 / global_analysis 8+2）本批只清 PAL3 20 条——其余类留后续批。

## 出链后命令序列（同运行读数）
1. `python tools/error_classifier.py --summary`（新 C2065=0）；
2. `python pipeline/cli.py match`（门 a，L1 当场读）；
3. `python tools/audit_type_layout.py --only PAL3`（门 c 行数口径）；
4. ida_structs 同步核对（门 e）；
5. W 重编目 715→697 + T1b 量化表标 superseded。
