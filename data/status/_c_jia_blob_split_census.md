# C(甲) SceneMgr 拆 blob 填充——gap 普查与裁决（2026-09-28 round 46/47，只读普查）

## ⚠️ 裁决（round 47 渲染语义复核后**改写**）：无干净字段候选——(甲) 转向 span 审计
+0x3A0 强候选经 4 函数 decomp 渲染复核 = **g_RoleSlotBuf 对象内部**（`g_RoleSlotBuf.m_partyActor.m_obbox`），
非 SceneMgr 字段！证据：`memset(&g_RoleSlotBuf, 0, 0x1B80u)`（=7040B=**1408B×5 槽**）+
`RoleSystem::RecalcAggregatedStats((RoleSystem*)&g_RoleSlotBuf, 1)` ×5 次分段 + `352*nVal` int 簇
⇒ g_RoleSlotBuf=真实 RoleSystem 槽簇对象（独立全局，自有成员面建模）。
叠加 84fd2ef7 已证：0xC04390（SceneMgr 声称基址）**无 ctor 锚、20 个 this 物化全是 Array::Insert/Erase/Size**。

⇒ **SceneMgr 58692B 声称 span 疑似 PAL3 同款幻影容器**（吞噬 g_RoleSlotBuf/g_palScript 锚区等真对象）。
(甲)"拆 blob 填充"不成立——38 gap 行 = 纯填充 + 真对象嵌入区（各有其结构面）+ 锚区；
正确后续 = **SceneMgr span 审计**（PAL3 W2-① 同法：正向锚定 sizeof、区间还给真对象），
归 C 轨道 W2-SceneMgr-② 工项，与 m_pAddEffect↔g_RoleSlotBuf 槽建模争端（84fd2ef7 Q5#4）同账。

## 普查数据（保留，供 span 审计用）
- SceneMgr.h gap/tail **38 行 / 52,702B**（W2 删 22 成员后余量）；
- 有数据访问区 6 个：+0x3A0（11 站点=g_RoleSlotBuf.m_partyActor.m_obbox）· +0xC5D8（addr9=g_palScript 锚址）
  · +0xC67E（匿名 union 内部）· +0xC810/+0x590/+0xC84C（单站点弱）；其余 32 区/≈48KB 零访问。

## 对照 goal C
(甲) 已裁决为**伪命题**（gap 非未标注字段）；替代工项=SceneMgr span 审计（C-②）。
CEffMgr 0x1895580 重定基（C-③）不变。

## 附：span 审计核证（round 48，T1b this+disp 谱）
SceneMgr 15 方法（10 播种）→ **37 this+disp 偏移/76 站点**，稀疏簇分布：
- 真字段簇：**0x0-0x20**（头部 25 站点）· 0x34 · 0x110-0x126 · **0x91C-0x92C**(8) · 0x372C/0x3794 ·
  0x894C · **0xA91C-0xA92C**(6) · **0xDB6C-0xDB78**(8) · **0xE0E0-0xE191**(11)；
- **离群 2 偏移 0x31FB8/0x32050（≈205KB）超 claimed 58692** ⇒ 疑方法误归属污染（1239c52d R4），
  span 审计第一步=这两条的方法归属复核；
- **结论形**：58692 的**外延近真**（末簇 0xE191<0xE544），但**成分是合成声明**——
  gap 大段（0x130-0x91C、0x92C-0x372C…）=嵌入真对象（g_RoleSlotBuf@+0x3A0、g_palScript@+0xC5D8
  =0xC10968 锚区、UIManager@+0xD3C8）+ 纯填充。⇒ C-② 的正确形态=**成分拆分**（成员簇保留、
  嵌入对象还给各自结构面、gap 诚实）而非尺寸收缩（与 PAL3 的 18 倍虚高不同型）。

### 审计第一步完成（round 49）：2 离群偏移定因=方法误归属实锤
0x493E40 `FormatStatusCaption`（SceneMgr methods 表内）——decomp 签名实为
**`int __cdecl SceneMgr_FormatStatusCaption(int nVal)`**（自由函数，`SceneMgr_` 前缀被收集期误收进类；
无 this）⇒ 注解 thiscall 播种 × cdecl 真形 ⇒ ECX 跟踪垃圾造出 0x31FB8/0x32050 假偏移（1239c52d R4 实证）。
**处置**：SceneMgr methods 删该条（守卫需补 `delete_method` kind——与 C-② 批同轮加）；
删后 T1b 谱收敛至 35 偏移/74 站点、全落 claimed 58692 内 ⇒ "外延近真"结论强化。

### 成员-区带映射（round 53，C-② 拆分输入第二层）
96 成员按实证区带定位：**真簇 10 / 嵌入区 59 / 其他 27**：
1. **RoleSlot 簇嵌入区（51 条，+0x28C..+0x4D8）**：m_aEquipGDB_*/m_aStatMaxVal_*/m_aNPC* 族——
   与 g_RoleSlotBuf 渲染面（m_partyActor.m_obbox 族）**同址双建模** = 84fd2ef7 Q5#4 留裁的
   "RoleSystem 槽建模争端"**放大版**。拆分前须裁决哪套建模是真面（decomp 渲染=g_RoleSlotBuf 面活跃）；
2. **g_palScript 锚区（8 条，+0xC5DC..+0xCCEC）**：m_pScriptCtrl（Q5#6 互指留裁）+ m_nTodo_C660/
   C848/m_fMoveParam 等——区间覆盖仲裁可删（同组C 5 条先例），处置=PalScript 建模批；
3. **其他 27 条**：含相机块（m_fCamFOV/m_vCameraTarget/m_vCameraPos/m_bCameraActive/m_nCameraFlags
   @+0xCF70..+0xD300，落 g_palScript 尾与 UIManager 头之间）——疑独立相机状态块或 CameraCtrl
   嵌入，**无锚证据待核**；+0x50 m_PlayerAtts/+0x560 m_RenderBuffer/+0x1610 stru_C059A0 等散件。

⇒ C-② 批次序：①delete_method 误归属（已备）→ ②g_palScript 区 8 条删（组C 同法）→
③RoleSlot 51 条争端裁决（需 84fd2ef7 级复核）→ ④相机块 27 条核证。

### C-② 批 v1 落地验证（round 60，出链实测）
8 条（7 删 g_palScript 区成员+1 删误归属方法）落地 → 全链 apply→export→codegen：
**S2 95/208 持平 · 新失败 0 · 6 转绿保持 · 真新增 10 全为已归因形态转世族（零条来自本批）** ✓
注解层：known_members 96→89、methods 15→14 ✓ 逐条核销。
守卫防陈旧兜住 3 处手算十进制错（整批拒→hex 直算重建）——dry-run 不查键存在性、写入期才查。

#### 第④步核证（round 54）：相机块=历史证据源与现址错位 + 现行零访问
17 条相机块成员（m_fCamFOV/m_vCameraTarget/m_bCameraActive 族）：
- **现行证据为零**：xref 绝对访问 0 站点、decomp 渲染 0 可见（名字与地址皆不现）；
- **历史 source 疑错位**：`binary:5refs_+0xCFD0`（成员在 +0xCF70）、`A:ida_stru_C11430_Camera_field`
  （Camera 对象在 +0xD0A0 而成员按 +0xCFxx 放置）——**键/源错位族**（m_nUnk61D8 同款）；
- 另3条 `decomp_context` 源（m_bPathEnabled/m_pRoleSystem/m_nCameraFlags）无独立证据。
⇒ 处置=逐行重裁（很可能整体错位 0x60 或该块属 Camera 对象建模被误挂 SceneMgr）——C-② 第④步，
  与 RoleSlot 51 条同需 84fd2ef7 级复核裁定。
