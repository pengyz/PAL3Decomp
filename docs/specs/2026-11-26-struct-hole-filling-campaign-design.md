# 字节空洞填充战役设计（Struct Hole Filling Campaign）

日期: 2026-11-26
状态: 已获用户批准的设计（终态口径+轮次排序两问已裁决）
前置: 洞普查 v3 可信基线（tools/census_struct_holes.py，201 类/1168 洞/1478KB）

## 1. 目标与终态

- **终态口径（用户裁决）**：证据背书填充，残洞诚实留——每个落位成员必须
  `evidence_level + source` 齐备；无证据区不做占位填充，洞清单即债务清单。
  符合 N12 无证据不名律、语义退化禁令，与现有门禁体系自洽。
- **轮验收三件**：
  1. check 门禁 PASS（新增违规阻断制）
  2. `cli.py loop` 全链绿（恒红 codegen 容错；apply/export/probe/match rc=0）
  3. 洞字节下降达标（当轮预期值 ±10% 内，超出须归因）
- L1/S2 渲染 churn 按既有棘轮律处理；回归门基线按归因知情刷新
  （CScreenMode 单元退役先例）。
- **预计终态（复核 B4 修正）**：目标面 1478KB → **~400-450KB 残洞**。
  算术：点名大锚最大可收 ≈1075KB → floor = 1513.6−1075 ≈ 439KB；189 个
  非点名类长尾 ~443KB 无轮次承接，留后续战役。
- ±10% 验收基准 = 预期**中值**（区间预期取 (上+下)/2）；R4/R6 定性轮
  （验收=诊断完成/裁决完成，不设数字阈值）。
- **R1 推迟分支重排规则（复核 B5）**：池计数探针失败（无 push 0x7D0 字面量
  且最大句柄上界不可得）→ 池落位推迟，R1 预期重排为 **−22KB**（句柄表
  20000B+杂项），验收按重排值执行，不视为轮失败。

## 2. 轮次规划（R1-R6）

| 轮 | 主攻（主洞） | 副线 | 预期洞收缩 |
|---|---|---|---|
| R1 | CCBCamControl 348KB **整表重建**（孪生定谳 v2 裁决"现注解不可修复"）：①池计数探针（push 0x7D0/最大句柄上界）→`m_Pool tagCCT[N]@0x0` 落位（N 有证才落）②句柄表落位 `@0x64190`（**复核 A2c 修正锚**：公式 4×102500=410000=0x64190，闭合 0x68FB0=430000 精确；行步距 200B=50 项/行，L 行数上界取证）③冲突面 17 员整表重建（复核 C8 名单：12 unverified + m_nCurPageTab + **4 A 级已证伪填充物** m_RenderQueue/m_SelectRect/m_SlotButtons/m_TabLists 优先退役）④CCCTData.json 三员（m_Pool/m_bPoolInUse/m_nCCTIndex）同步处置防 chimera 复刻 | SkillUI **53 条**退赔重挂（复核 A2a 修正：台账 53 retired+4 kept；census 口径仅消 240B——账务修复非消洞） | 池有证：−337~348.7KB（复核 A3 复算式）；池推迟：**−22KB**（§1 重排规则） |
| R2 | EquipUI 164KB：尾区七模块指针落位（A级证据在档：EquipUI::Init 分配+存储+金表尺寸）+ 尾区 disp 普查（成员末端仅 36KB，~229KB 内区待查） | — | −100KB 级 |
| R3 | RoleStatePanel 152KB：ctor 写序解码 + disp 普查 + 字段验证（CEffMgr 模式） | — | −100KB 级 |
| R4 | ScreenEffectMgr 355KB：从零诊断（新立案；ctor+普查） | — | 定性轮（诊断完成即验收，数字下轮报） |
| R5 | MagicUI 43KB + SaleUI 43KB 批量小锚 | UIGameFrm 27KB | −80KB 级 |
| R6 | 挂账批：金表第二批（UITitle_JDHY Note_Item 双布局仲裁/C2DSpark tagSpark 重验/CCBStage 三数字两态/PropUI 差164/CCBRoleState ctor 写界取证）+ **堆类身份定谳**（复核 C10 改写：430256=X 已裁[金表 site 0x4fbc2e+ctor 链]；402824=类Y[site 0x4a4660]待名；425136 候选**除名**——换算错，0x68FB0=430000≠425136；继承边界候选=430000，须 CCBCamControl ctor 基类构造直调证据，0x5052e0 已解码无显式基类调用[内联可能]，弱证据待另证） | — | 定性轮（裁决完成即验收） |

轮次间可按对抗复核结果重排（真 bug 多的锚优先返工）。

## 3. 每轮标准流程（三段式 + 落账）

### 3.1 填充段
1. idalib 探针（tools/probe_*.py 惯例，产物落 data/status/probe_*.json）
2. 证据链：**六证择二**——ctor 写序 / disp 聚类 / 工厂解码 /
   调用点 ecx 回溯 / PDB mangle / 金表字面量
3. 注解落位（evidence_level + source 齐备）→ `cli.py check`

### 3.2 对抗复核段
- 子 agent 独立复核（general-purpose，只读+跑分析，不改文件）：
  - 本轮新落成员逐条证据链重验（独立重实现探针逻辑，不 import 原探针）
  - 读数归因：洞减少量 vs 预期差 >10% 须给出解释
  - 裁决表：真 bug（须修）/ 可接受近似（记录口径）/ 口径解释题（呈用户）
- 发现真 bug → 当轮修复并重跑管线，**不带病进下一轮**。

### 3.3 管线段
- `cli.py loop` 全链（apply→export→codegen→probe→match）
- 已知陷阱（本会话实录）：codegen 中途夭折会留下部分再生头树 → REF 假性
  新失败 + [D] 失配放大——**codegen 失败先独立跑 `codegen all` 完成头树
  再生，再进 loop**。
- 回归门基线刷新必须带归因（每案例逐条说明来源）。

### 3.4 落账段
- 独立提交（commit-msg Evidence 格式：证据链+置信度）
- 记忆更新（memory/ 既有文件追加或新文件）
- `python3 tools/census_struct_holes.py` 重跑刷新洞清单
- 对抗复核裁决表落 data/status/（*_adjudication_*.json 或 md）

## 4. 证据红线（复用既有法律，全轮适用）

- 池/数组落位：**stride 乘法链 + 计数闭合**（tagCCT=204=0xCC 先例）；
  计数无代码字面量（如 push 0x7D0 / 最大句柄上界）时不上注解、推迟并挂探针案
- **PDB 证边界（复核 C9）**：单一 PDB mangle 不定谳，须与二进制证据组合；
  本族 PDB 名仅作线索（DoTask/AddTask 不在 PDB CCBCamControl 表=构建漂移
  实锤；4 个"CCCTData 方法"FLIRT/ICF 假名实证）
- 禁 slot_N / sub_ / unk_ 占位语义名（N12/语义退化禁令）
- 禁魔法关键词豁免、禁无证据 gap 填充（对齐 pad 由普查器自动扣除，不手填）
- 成员名用真语义名或地址消歧形（HideAll_3DE40 先例）；置信度留档
- ctor 注解三件套：类名 + `flags:["ctor"]` + sig 返 this/void
  （emit_headers fail-loud 门禁强制，SceneMapPlayer/CCBCamControl 先例）
- bases 变更必须落 data/status/bases_adjudications.json（C11 门禁）
- 禁止未经用户同意的管线新机制；既有机制组合不在此限

## 5. 每轮已知风险与防护

| 风险 | 防护 |
|---|---|
| 池计数无字面量 | 不猜（不上 2000），落 _residual 注记或推迟（R1 池计数探针首查） |
| 语料渲染 churn（新成员名进渲染） | L1 棘轮既有律；单元错误波动按归因处理，不盲 rebaseline |
| codegen 头树部分再生 | 失败后独立 `codegen all` 完成再生（3.3 陷阱条） |
| 门禁拦截（MemberExtent/REF/emit_headers） | 拦截=设计生效，按提示修数据不带病闯 |
| 双注解 chimera（CCCTData 案） | 三候选注记在档，R6 裁决前不动尺寸 |
| IDA 名与注解名漂移（name_drift 警告族） | 改名链随轮清理，非本轮范围不追 |

## 6. 明确不做（本战役范围外）

- CCBCamControl/CCCTData 的类重命名涟漪（PDB 交叉已完成，重命名待 R6 后统一）
- BSS 块分解（g_CCBCamControlData → 逐变量 globals）——W3 范畴
- gold table 待名新类（0x56630/0x27BD4/0x207F0/0x1E56C）建档——挂账不清洞
- W3 检查器查 pool（70 误报）/ reg-var cast 规则（待批管线项）

## 7. 基线数据（战役起点，2026-11-26）

- 洞普查：201 类 / 1168 洞 / 1478KB（data/status/struct_holes_20261125.json）
- top 洞：ScreenEffectMgr 355KB（新显形）/ CCBCamControl 348KB（诊断完成）/
  EquipUI 164KB / RoleStatePanel 152KB / SkillUI 99KB / MagicUI 43KB /
  SaleUI 43KB / UIGameFrm 27KB
- 编译读数：S2 157/229 · L1 188（matched 1146/1254）
- overlay 孪生单列 897KB（union 变体类，不在目标面）
- 金表：data/status/probe_heap_alloc_census_20261126.json（33 笔 ≥0x4000）
- PDB 族谱：data/status/pdb_camera_family_20261126.json
