# 编译器 sizeof 金表对账落地（2026-11-26，重建战役②·第一批）

## 数据源
- 金表: data/status/probe_heap_alloc_census_20261126.json（33 笔 ≥0x4000）
- 判据: `push SIZE; call ??2@YAPAXI@Z; mov ecx,eax; call ??0ClassName@@`
  —— 构造 mangle + 尺寸字面量 = 编译器 sizeof A 级

## 已落地修正（5 类，成员末端 0 越界验证后）
| 类 | 旧 → 新 | Δ | 证据 |
|---|---|---|---|
| EquipUI | 120116 → **266260** | +146144 | ??0EquipUI + push 0x41014；266KB 大容器尾部 +0x2AFB8..0x2AFD0 七模块指针表 |
| MainPropUI | 247976 → **219984** | −27992 | ??0MainPropUI + push 0x35B50 |
| LineupUI | 171244 → **162772** | −8472 | ??0LineupUI + push 0x27BD4；旧值 171244=邻类（0x29CEC 分配首 call Save@LineupUI 误名） |
| ScreenEffectMgr | 152 → **363968** | +363816 | ??0ScreenEffectMgr + push 0x58DC0；旧值严重低估（355KB 真欠账曾全遮蔽） |
| CCBRoleState | 22224 → **20568** | −1656 | ??0CCBRoleState + push 0x5058；另 ClearAndSetGP 分配 0x50A4=20644 待辨 |

## 挂账（越界/多数字，缓修）
1. **UITitle_JDHY** 377700→290488（push 0x46EB8）：成员 m_NoteItem@0x634
   （Note_Item[99]）末端 352440 > 290488 越界 —— 与挂账案「Role[50] vs
   Note_Item[99] 双布局仲裁」纠缠，随该案一并修
2. **C2DSpark** 24688→22640（??0C2DSpark + push 0x5870）：成员 m_Spark@0x0
   末端 24576 > 22640 —— tagSpark 型尺寸或元素数须重验
3. **CCBStage** 三数字：ctor ??0CCBStage new 0xA4128=672040 / InitFromDescriptor
   new 0xA48B0=673968 / 注解 673988 —— 两分配两态分辨（池?派生?）独立成役

## 精确命中表（零改动，binary_size 自证精确）
ParticleEffect 362860 / MainEquipUI 209008 / SaleUI 105912 / SkillUI 101940 /
CCBSystem 90840 / JusticeBookUI 56192 / CCBUIPanel 22112 / CEffect 245800 /
RoleStatePanel 176256 / CEffMgr 43312×3 / CCBCamControl 430256（锚错位案 v3）

## 待名新类（金表产物，分配有尺寸无注解）
- 0x56630=353840（首 call InitChildPanels@RenderTarget——Render 系邻类）
- 0x29CEC=171244（首 call Save@LineupUI——ctor 地址误名案）
- 0x207F0=133104（sub_454830）
- 0x1E56C=124268 ×2（InitWithPalScript@UIListBox——UIListBox 派生族）
- 0x70DC=28892 ×2（InitUI@PropUI——PropUI 注解 29056 差 164 待核）
- 0x6390=25488（SetCircle 链）、0x4618=17944（InitStage 链=CCBDisplayChain?）

## 洞普查新读数（v3+金表修正）
201 类 / 1168 洞 / **1478KB**（+463KB=ScreenEffectMgr 355KB + EquipUI 164KB
真欠账显形；MainPropUI 幻影区 −27KB 消除）——普查目标面更诚实。

## 落地验证（loop 全链）
- 第一遍 loop 拦截: CCBRoleState 成员 m_BattleFlags@0x56CC 末端 22224 越界
  （离线检查漏读，门禁抓到）→ **回退 20568→22224（成员背书保守胜出）**，
  挂构造字面量冲突案（??0CCBRoleState new 0x5058 vs 成员证据，待 ctor
  写界取证裁定是 ctor 误名还是成员越界）
- 第二遍 loop: apply/export/probe/match 全 rc=0（codegen 恒红容错）
- **读数: S2 157/229 · L1 188（+3 副增益）· matched 1146/1254**
- 改进面归因: SaleUI 37↓35 / Actor 3↓1 / globals 10↓2 —— EquipUI+146KB/
  ScreenEffectMgr+363KB 尺寸修正直接修好 8 处渲染错误
- 回归门基线知情刷新（baselines/20261126_010832, 995 文件 95 失败）:
  归因=CScreenMode.cpp 单元随退役战役停止发射（fresh init 229 单元已无它，
  非本次引入）+ 三单元错误下降=本次正收益
- 终态修正 4 类: EquipUI 266260 / MainPropUI 219984 / LineupUI 162772 /
  ScreenEffectMgr 363968
