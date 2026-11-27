# 交接文档：字节空洞填充战役（R1-R3.5）+ 结构重建

日期: 2026-11-26
分支: master（最新 commit 见 git log；本文档提交时点的一切状态以文内"验证命令"可复现为准）
前置阅读: docs/specs/2026-11-26-struct-hole-filling-campaign-design.md（战役 spec）

---

## 1. 一页状态

| 项 | 战役前 | 现在 | 变化 |
|---|---|---|---|
| 空洞目标面 | 201 类/1168 洞/1478KB | **201 类/1142 洞/1246KB** | 三大锚收口+CCCTData 中间态显形 |
| CCBCamControl | 348KB 洞 | **12B** | 池区四段闭合（R1） |
| EquipUI | 164KB 洞 | **15.6KB** | 尾区九数组落位（R2） |
| RoleStatePanel | 156KB 洞 | **556B** | 40 员落位+基类链裁决（R3） |
| 编译读数 | S2 157/229 · L1 188 | S2 **158**/229 · L1 **189**（重锚） | 但见 §5 match 棘轮红（R4 首查） |
| 语义清理 | 触达 7 类 38+ 非语义名 | **42 员迁移 m_unk_<offset> 统一形** | 全库 538 员存量待批次（R3.6+） |

> **修正注（2026-11-26 实测，依据 [交接对账报告](../audit/2026-11-26-handoff-reconciliation.md)）**：上表原值保留不改（只加注、不改史），仅就五处与实测不符或不可复现之处加注。
>
> 1. 〔§1「编译读数」行〕「现在 S2 **158**/229 · L1 **189**」是 **R2 终点**（commit `cf70c0b48`）的读数；2026-11-26 实测为 **S2 157/229（总错误 633）· L1 188**。证据：`data/status/probe_census.json` `generated_at=2026-11-26T19:14:46`（`s2.ok=157/229`，`total_errors=633`）；`pipeline/_logs/loop_match.log` 19:29:02（`L1 rate 188/998`，`[L1 ratchet] previous 189 -> current 188`，`LOST RoleStatePanel 的 scalar deleting destructor'(uint) @0x4A2150 size=30`）。差异归因 R3 提交 `ac9c67673`（`RoleStatePanel.cpp` L777 C2440 使该单元转 fail，同轮 ??_G 退出可比域），即 §5 的 R4 首查项；**棘轮未重锚**，见对账报告 §3-A。
> 2. 〔§1「RoleStatePanel」行〕「156KB 洞」单位错：实为 **152.8KB（156,453 B）**（R2 后 156,433 B）。终点 556B 实测无误，见对账报告 §3-B。
> 3. 〔§1「语义清理」行「7 类 38+」〕`38+` 无产物来源（疑写作前预估稿）；可复现值为 **42 员**（`data/status/r35_semantic_cleanup_20261126.json` tally=42；`git show 22417d35d` 中 `"name": "m_unk_` 命中 42 条），且实际迁移仅 **2 类**（RoleStatePanel 40 + EquipUI 2），见对账报告 §3-C。
> 4. 〔§1「语义清理」行及 §5「待办与入口点」批次项「全库 538 员」〕无命令/产物可复现，**列未决**；在档可复现量：伪语义名台账 61 类 323 员、注解 todo 词 149。另 §2 的「伪语义名台账 58 类 296 员」与现文件 61 类 323 员不一致，同列未决（对账报告 §6-1/§6-4）。
> 5. 〔README 读数〕本文件未载 README 读数；对账结论：README「当前读数（2026-11-23）」的 S2 160/233 · L1 181 · check 13 警告三项全陈旧，已由对账卡刷新为 2026-11-26 实测值；**233→229 的四个 S2 单元去向无记录，列未决**（对账报告 §3-E/§6-2）。


## 2. 本段工作明细（按提交序，均可 git show 验证）

### 结构重建三部曲
1. **孪生案定谳 v1-v4**（417d3a34a/b93e53921/1a52354e2/4bcc8fbae）：g_CCBCamControlData BSS"全局"=静态变量块证伪（零装载形判据）；双堆类终局（类 X=CCBCamControl 0x690B0/类 Y=0x62588）；PDB 交叉（CCCTData 15API 真名族/tagCCT=204 闭合）；FLIRT 假名第四形态（4 微型函数名全假=地址错挂）
2. **编译器 sizeof 金表**（probe_heap_alloc_census_20261126.json，33 笔 ≥0x4000）：binary_size 修正 4 类（EquipUI +146144/MainPropUI −27992/LineupUI −8472/ScreenEffectMgr +363816）；**ctor 三件套定谳**（0x5052e0=CCBCamControl ctor，emit_headers fail-loud 拦截实录）
3. **R1**（ed73fd85e）：CCBCamControl 池区四段闭合——m_Pool tagCCT[2000]@0x0（计数 0x7D0 五址+ResetAllData 三派生+乘法链）+ m_bPoolInUse@0x639c0（flexcam.dat 布局+活性消费者 0x5052c0 空闲槽分配器）+ m_TaskListIndex@0x64190（idx 公式 4×102500 闭合 0x68FB0）+ 尾域 25 员；17 员冲突面退役；SkillUI 53 退赔重挂
4. **R2**（cf70c0b48）：EquipUI 尾区九数组落位（UIParticle[128]×2/UIPushButton[6]/UIFrameContainer[12]/tagPlayerSet[5]/UIParticle[60]×2 + 2 未名 byte 形）+ 76 员退役（PDB 独立佐证旧注解系 PAL3A 布局导入）；RoleStatePanel 七模块指针（侦查修正：宿主非 EquipUI）
5. **R3**（ac9c67673）：RoleStatePanel 40 员落位 + **基类链双类裁决**（0x43DCD0=72B UIListBox 类 ctor vs 0x43DFC0=1208B 另类真 ctor，MI 双表+push0x4B8=new 双证伪）+ bases=[UIListBox@0]+vtables 同步；9 残洞零证据诚实留
6. **R3.5 语义清理**（22417d35d）：触达 7 类 42 员非语义字段迁移 **m_unk_<offset> 统一形**（用户裁定留白形）；正名 0=判据诚实产出

### 语义名三档（用户问询后审计口径）
- PDB/语料证据名 62（m_Pool/m_bPoolInUse 语义行为证明：空闲槽分配器 0x5052c0 等）
- 推断语义名 6（m_TaskListIndex/m_pTabPanel/m_pSubTabPanel/m_par 族——证据支撑的推断，非原文恢复）
- 留白 42（m_unk_ 形）+ 正名 0（判据从紧）

### 语义名正名工作流（未竟）
- 伪语义名台账 58 类 296 员（20261118 在档）+ 全库 todo 343/field 29——正名判据=消费/写值证据实锤（R3.5 判据从紧先例：800/600 对零读站不硬凑）

## 3. 本段新定律（全库适用）

1. **对齐 pad 默认不计**、无名字豁免不存在（空洞普查 v2 用户裁定）
2. **类型分类禁前缀猜**——enums.json 数据驱动（v3 自伤案：'tag' 前缀入枚举正则→CPK 768KB 伪洞）
3. **binary_size 修正必须过 loop 门禁**——离线 extent 检查不完备（CCBRoleState 回退案）
4. **ctor 注解三件套**=类名+flags:["ctor"]+sig 返 this/void（emit_headers fail-loud 强制）
5. **codegen 头树部分再生陷阱**——夭折后先独立 `codegen all` 再 loop
6. **大洞+零访问≠无主空间**——先查间接寻址（pool[idx]×stride）再判无主
7. **区间填充物甄别**——跨度非整数闭合或 stride 乘法链显形即填充物
8. **FLIRT 假名第四形态**——5-15B 微函数挂语义名（体长+体语义失配判据）
9. **BSS 名被当对象锚的识别**——引用点形态普查：零装载形+散乱微函数绝对写=静态变量块非对象
10. **operator new 尺寸字面量=类真尺寸终极证**
11. **PDB 参考非权威**——构建漂移实证（DoTask/AddTask 不在 PDB 表）；单 PDB 证不定谳
12. **函数名禁数字后缀**→C++ 重载规则（用户裁定，撤销 HideAll_3DE40 先例）
13. **Todo 词=占位不可再建名**；数据成员留白统一形=**m_unk_<offset>**（用户裁定）
14. **解冻按精确条件清单，不 blanket**（_tail_000 误放案）
15. **移动 tracked 文件用 git mv**（docs/superpowers 42 文档误删案）

## 4. 工具与产物索引

| 工具/产物 | 用途 |
|---|---|
| tools/census_struct_holes.py | 空洞普查常备审计器（v3 对齐感知）→ data/status/struct_holes_20261125.json |
| tools/probe_heap_alloc_census_20261126.py | 编译器 sizeof 金表（33 笔 ≥0x4000） |
| tools/probe_ccbcamcontrol_*.py（6 支） | 孪生案全证据链（census/pooldecode/dynamicinit/twin/global_census/receiver） |
| tools/probe_equipui_{tail,arrays}_20261126.py | R2 侦查+元素鉴定 |
| tools/probe_rolestatepanel_{layout,holes}_20261126.py | R3 侦查+残洞验证 |
| data/status/probe_pdb_camera_family_20261126.json | PDB 方法族谱（CCBCamControl 40/CCCTData 15/tagCCT/CCBEditor 101） |
| docs/specs/2026-11-26-{campaign,r1,r2,r3}*.md | 战役 spec+三轮实施计划 |
| .superpowers/sdd/*/progress.md | 三轮 SDD ledger（任务级裁定全记录） |

## 5. 待办与入口点（按优先级）

### R4 首查（阻塞级）
- **match 棘轮红归因**：RoleStatePanel::`scalar deleting destructor'(uint) @0x4A2150 30B LOST——s_RoleState.cpp 单元重渲组内联决策变化（regressed detail 已存档 data/status/archive/s4_diff_detail_regressed_20261126T192902.json）。**拒绝重锚是正确状态**，归因后才可 rebaseline。

### 待用户批准（呈报中）
- **L-VAR 引脚提案**：RoleStatePanel.cpp C2440@777（hexrays 局部类型化伪影，ASM 全字节粒度实证）——三选一：L-VAR 引脚（推荐，先例 BuildCollisionMesh pVal:_WORD）/stage5 cast 规则/成员拆 8 byte 员
- **cls_43dfc0 建档+迁 ~34 方法**（基类链债务 #2：1208B 类才配叫 UIListBox 的名义重锚）
- **全库 538 员 m_unk_ 迁移批次**（触达 7 类已清，余 891 类）

### R4-R6 轮次（spec §2）
- R4: ScreenEffectMgr 355KB 从零诊断（新立案；注意 census 语义：ScreenEffectMgr binary_size 363968 金表修正后首轮普查）
- R5: MagicUI 43KB+SaleUI 43KB 批量小锚（+UIGameFrm 27KB）
- R6: 挂账批——UITitle_JDHY Note_Item 双布局仲裁/C2DSpark tagSpark 重验/CCBStage 三数字/PropUI 差 164/CCBRoleState ctor 写界/**堆类身份定谳**（430256=X 已裁；402824=类 Y 待名）

### 语义名主战役（跨轮）
- 全库 todo 伪语义 343+field 29：正名判据=消费/写值证据实锤，留白终点=m_unk_<offset>（统一形已裁）
- RoleStatePanel 升级候选：0x58/0x5c 疑窗口宽高（LineupUI bkWndX/Y 孪生同址同值在册）；m_nScanIndex@0x60 ctor 写直证升 verified

### 其它挂账（详录 .superpowers/sdd/*/progress.md 与各轮报告）
- CCBUI↔SkillUI 0x94~0x4b8 双声张裁定；HideAll_3DE40 重载正名；placeholder_in_str_pos +2 R6 回收；CCCTData 类 Y 重铸（现全洞 420KB 中间态）；UIStatic-UIFrameContainer 尺寸孪生调和；UITitle_JDHY 377700 vs 金表 290488（Note_Item 双布局纠缠）

## 6. 验证命令（交接即验）

```bash
python3 tools/census_struct_holes.py            # 空洞普查：预期 201 类/1142 洞/1246KB
python3 pipeline/cli.py check                    # 门禁：预期 0 new + 37 frozen PASS
python3 pipeline/cli.py status                   # 管线读数：S2/L1
python3 pipeline/cli.py loop                     # 全链（约 20 分钟；codegen rc=1 恒红容错；
                                                 #  ⚠ match 棘轮红=R4 首查项，勿重锚）
```

## 7. 交接红线（新会话勿犯）

- 解冻冻结条目按精确条件清单，**不 blanket**（_tail_000 两次误放案）
- gate 结论禁止 pre-judge（评审者独立裁决）
- lvar 标注需用户报审（既定律）；管线新机制需用户批准
- annotation 改动必跑 check+loop；binary_size 修正必过 loop 门禁（CCBRoleState 回退案）
- 池/数组落位必须 stride 乘法链+计数闭合；计数无字面量不猜
