# 系统性问题全面排查：分析·定性·修复方案 v2（2026-09-27，已并入复核 acfd56b8 全部修订）

> v1→v2 变更：4 硬条件落地（P0-a ida_structs 活体层 / P0-b Array 反例撤回 / 顺序重排 /
> W2 字节面门）+ 数字口径闭合 + 多实例/形态差异/黄金集等 P1-P2 修订。
> 复核判定【有条件可执行】；v1 的 S3 头号 288、S4 45/26、S1"26 落串"、"18 条"标注为
> **不可复算口径**，按本文 §1 勘误表替代。

## 0. 排查范围与方法
六轴探测器 + 三份对抗复核合流（ff86c62f/c34f38aa/0cc3dbf0）+ 方案复核（acfd56b8，
pefile+capstone 直读 + 真实解析器复放）。
**统计数字硬规（P1-e）**：本文及后续台账引用的每个统计数字必须附探针脚本路径 + 输入文件
md5 + 口径定义；缺任一不得进验收门与 docs/knowledge 回写。

## 1. 数字勘误表（v1 → 复核复算）
| 项 | v1 | 复核复算/口径 | 处置 |
|---|---|---|---|
| S3 头号 | 288/21 容器 | 明细和 298、独立复算 **300/20**（漏 g_CPKPackFiles **19**）| 用 300/20 口径（globals.json × top_levels 区间），CPK 19 单列 |
| S4 | 45 真/26 other | 机制同形态复放：可解析 **130**（dword_ 形态）/17（真名形态）；落幻影 **34**（严格 auto:overlap/global_analysis 子集=29）；非幻影 96 | 用复放值；45/26 弃用 |
| S1-2 | 26/38 落串字节 | **31/38**（≥4 可打印 run 口径）；⚠️ 真成员也落串区（m_EffTable[584]/m_szEffectPath/m_szLogPath）| 串字节**不得单独**作幻影判据，用 §3 判据⑤三条件合一 |
| key↔source | 18 条 | 43 条（干净 10）；且 SceneMgr 四条同 **−0x60**、一条 −0x260、GeomNode −8 = **整体漂移族** | 先按 Δ 分组裁整族（疑成员插删），再裁个案 |
| auto:overlap | 37 | 37 ✓ 但漏 4 条 `auto:extern_overlap_*`（CEffMgr+0x37B8/CGameData+0x1BA0/SSD+0x8A8/SSD+0xBD8）| 清单 37+4 |
| global_analysis | 8 | 8(PAL3) ✓ + SceneMgr 2（g_CCBStageRoleFind/g_bRoleSlotValid）| 清单 8+2 |
| 低证据面 | 63% | **≥64.8%**（+173 修正）；另有未分级 1633 条（cluster:*378/gen_headers_9.2 586/binary 580/PDB_batch_import 59/transfer_from_*30） | 表述改"≥64.8% + 1633 条未分级" |
| PAL3 收缩界 | ≤0x1358 | **≤0x1348**（guard-bit-8 块写 0xDE8DE8..0xDE8DF0）| 用 0x1348 |
| 精确复算 ✓ | — | auto:overlap 37 · 键谱系 9745/51/4 · _gap_ 1673 · S3 明细七项 · 幻影方向 29 · census md5 | 保留 |

## 2. 问题分类定性（v2 修正版）
### S1【P0】幻影容器
- g_EffMgr(43312)：**整体幻影**（.data=VC6 池化串表 732 段可打印 run；.text 恰 1 处
  `push 0x5D5484` 串实参；m_sz5D8C3C=格式串；尾块=rollBar/scrollbar）✓ 铁证；
- g_PAL3(91024)：**范围膨胀**（census size_bytes=None 零锚；statics 块**自 +0x1348 起**
  （guard 位 1/2/4/8 + atexit 空 thunk 四连）；末真实成员 0xF9C）⇒ 收缩目标 ≤0x1348；
- 4× Array 件：**v1"吞邻"撤回**（复核反例成立）——`Array::Size/Free/InsertAt` 的 this
  物化（`mov ecx,0xC04350; call 0x4111C0`）+ 12B stride ⇒ +4/+8/+0xC 是 Array 字段；
  12 个"邻接全局"是**字段被误登记为独立全局**（弱源 `CRT init`）⇒ 处置=字段正名，不收缩。
### S2【P0】幻影成员：auto:overlap 37+4、global_analysis 8+2（§1 勘误）、PDB 搬运族
（PDB_batch_import(size_match) 59 + transfer_from_* 30 + PDB+PAL3_offset_adjusted 20 =
"按 size 匹配搬运"，与 blob 自我闭合同源）。
### S3【P0】分区争端：300 个独立全局落入 20 个容器声称区间（含 CPK 19）；同址冲突
g_palScript（ctor thunk + atexit + 12 xrefs ✓ A 级）vs m_pCameraCtrl（docs: 源）；
**同址冲突仲裁规则：A 级锚 > 区间包含**（Array 件与 g_palScript 案都由这条裁）。
### S4【P1】退役机制输入盲区 + **形态差异（Q6-1 关键纠正）**：
`_try_struct_member_resolution` 按 `int(name.split('_',1)[1],16)` 解析 ⇒ **真名恒返回
None**（实测真名形态仅 17 命中、dword_ 形态 130 命中）⇒ 命名全局**不被 extern 退役路径
处理**。v1"29 条错误方向退役"**改述**：29 条是"区间+键"口径下的**渲染层成员路径改写风险**
（stage4 将其使用点改写为幻影成员路径，如 g_EffMgr.m_nTargetSlot），extern 面损失仅发生在
dword_ 形态。W3 必须**与机制同形态复放**。
### S5【P1】发射层账目：emit_headers.py:2174/2162 inline 打包尺寸（具名类型须查表，
tagTeamSlotsBOverlay 607≠800 实证）；`_gap_` 造生 1673；key↔source 整体漂移族（§1）。
### S6【P1】键/解析纪律：dec 9745/hex 51/N_N 4；apply_annotations.py:447 已修（守卫返工批）；
data.py:151 变体键、51 条 hex 键归一仍待 W5。
### S7【P2】度量自证环：census md5 stale、compile_baseline 陈旧、**L1 棘轮回写（事后不可查）**、
C1003 截断计数不敏感。
### S8【P1】显式 this 调用：0cc3dbf0 两前提证伪 ⇒ W6 走 ast_transform.py:870 最小修复。

## 3. 根因（v2：三层 + 四补）
主干：①地址区间⇒成员存在的推理跳跃 ②机制修复未验输入 ③下游确定性传播。
**补充**：④**导出回路自证**（注解→apply→IDB→export→ida_structs.json→codegen store 读的是
自己写出去的导出物——与废弃 audit_layout.py 同源病发生在成员存在性上）⑤名字/类型搬运
（PDB size-match 族）⑥多实例同型聚合（RoleSystem×6/PAL3×2/CPK×2，类级证据当实例级用）
⑦度量自证环（S7）。

## 4. W1 裁定门规格（v2 升级）
判据优先序（Q4）：**①this 物化锚**（`mov ecx,imm32; call 成员`，含 vtable slot 反解）——
对象性最直接证据，列第一 ②ctor/dtor thunk 对（`mov ecx,imm; jmp ctor` + `push dtor;
call 0x553041`）③static-init guard 三元组 ④**尺寸锚**（`operator new(N)`/push N 立即数/
memset/rep stos 范围/数组 stride）——收缩"缩到多少"的正向证据 ⑤串字面量指纹
（**三条件合一**：连续 ≥N 可打印 + NUL 填充 + 仅被当指针实参引用；落串字节不得单独定罪）
⑥同址冲突仲裁：A 级锚 > 区间包含。
- 输出按 **(类, 实例基址) 双键**（P1-c：RoleSystem×6/PAL3×2/CPK×2 禁止类级套实例）；
- **黄金用例 ≥13**：3 定案组 + Array 4 件 + 8 个字符串容器 + g_palScript；
- 输入面 = data/annotations/structs|globals.json **∪ asm/pal3/ida_structs.json**
  （`_globals` name/type + struct size + data_members）（P0-a）；
- 误判面警戒：假阳最坏=真 char[]/float 表被判幻影（m_EffTable[584] 等）；假阴最坏=
  PalScript[N] stride 数组区、单函数引用的真成员（m_nTodo_2E4 族）。
- 既有实现复用：global_region_audit.py E/D/atexit/partition + alloc_sizeof ctor-anchored。

## 5. 修复方案（v2 顺序铁律 + 验收）
**顺序：W1 → W4-C0b（尺寸 oracle）→ W2 → W3（W2 批内即刻重放、同批挂账）→ W5（W2 批量
改名前完成）→ W6 → W7**（撤回"W2/W3 并行、W4/W5/W6 独立线"——W3 复放结论依赖 W2 状态，
W4-C0b 不前置会把账目错位先固化成新 _gap_/伪成员）。
| # | 工项 | v2 关键修订 | 验收 |
|---|---|---|---|
| W1 | 裁定门 | §4 规格；黄金 13 例 | 全部判对 + 全库可复算（脚本+md5+口径入档）|
| W4-C0b | 尺寸 oracle | emit_headers 2174/2162 具名类型查表 + 与守卫共用 | 45 测试绿（tools/test_type_evidence.py）+ SceneMgr 1/167→0 + 12 类不降（audit_type_layout --only）|
| W2 | 幻影清理批 | ①收缩**仅 PAL3**（≤0x1348）②**Array 件不收缩**，12 名字段正名 ③删 auto:overlap 37+4 + global_analysis 8+2 ④独立全局正名入 globals.json ⑤**实例类型纠正**：a*/asc_* 串名 `_globals` 类型→char[]、删伪 struct_instance | **字节面门（条件4）**：(a) 受影响 TU 逐函数 match diff=0（同运行读，禁聚合 L1）(b) 生成物 diff 白名单（globals.cpp/h/生成头逐符号登记）(c) 符号尺寸表比对（含 sizeof 收缩；PAL3 用行数↓红度不升口径——audit 现 87/87 系统性偏移基错位无绝对判别力，beb91db4 P1-c）(d) **删除可追溯（复核 beb91db4 Q1 精确化条文）**：每条被删成员须给出①归属级否定证据（static 块锚/池化串锚/同址既有独立全局视图/多函数非 this 访问+独立符号语义，四选一）+②地址处置闭合（随 static 块消失／由 globals.json 新旧条目承接／函数 static 正名）；**W1 的 exists 只证地址活性，既不单独构成删除理由也不构成保留理由**；落地核对=渲染不断链+新 C2065=0+键可追溯 (e) 全链重生成后 ida_structs.json 与注解同步核对 |
| W3 | 退役审计 | **与机制同形态复放**（真名 vs dword_ 形态差异先写成结论）；按**容器实例**裁（一址多视图）；数组吞址后落到别的幻影路径也算未恢复；分母统一（extern 2034 / globals 1306）| extern 变化有账 + 逐条理由字段 + 26/34 条机械清单 |
| W5 | 键纪律 | apply_annotations:447 已修；data.py:151 + 51 hex 归一 | int('50814_0') 用例 + 51 键断言 |
| W6 | AST 最小修复 | ast_transform.py:870 放宽复杂 *expr/**expr + 词法安全 | 2984 定义头零变化 + 串/注释零污染 + C2660 153→≤110 **且 C1003 截断单元最大行号前进**（同运行读）|
| W7 | 基线收官 | census 重跑、compile_baseline 棘轮（用户确认）、**TOLERATED 逐条白名单 + --expect-* 三值随批更新**（撤"全绿即过"）| loop 断言 + 同址冲突反向清点 + ida_structs 同步核对 + 知识回写（含 §1 勘误表）|

附加时点规（P1-d）：B 批 W=715 重编目与 T1b 量化表（_b_t1b_unlock_premeasure §2/§3）**W2 落地
后重跑**，旧表标 superseded，禁引旧数字做期望管理。
每批落地前重生成下一批（防 type_change 陈旧）；改名级下游按 R7 重跑；L1/错误数**同运行读**。

## 6. 与既有工作的关系
- 全局退役方案（cc7f9665a）机制保留；W3 补输入审计 + 形态差异结论；
- C 批重定标（_bc_rescope）并入 W2/W4；B 批重编目排 W2 后；D 批收官排 W7；
- 守卫返工（_guard_rework_round1）已毕（45/45），W2/W3 的批次全部走该守卫。
