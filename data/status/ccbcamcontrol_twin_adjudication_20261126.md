# CCBCamControl/CCCTData 双注解孪生案定谳（W2 P0 首战，2026-11-26）

## 裁决

**g_CCBCamControlData@0x17AAF64 = 编辑器相机路径模块单例**（INI 装载，
节名 "EditorCamD*"，CIniFile::LoadStructuredConfig@0x504130）。
现役两注解（CCBCamControl 42 员 / CCCTData 3 员，binary_size 同 430256=0x690B0）
**双双身份破损**，其成员模型大部分为区间填充物或错挂。空洞普查的 348KB"洞"
不是字段缺口，而是**真子结构未被解码**（任务池/关键帧表/对话框域）。

## 五面证据链（探针 tools/probe_ccbcamcontrol_*.py ×4）

### 1. 身份钥匙：INI 装载器（A 级）
- `sprintf(name, "EditorCamD*")` → `ReadSection` → 64 次循环 ×0x18 步距
  ReadLine{key@5DB9B8→+0, key@5DB9B4→+4, key@5DB9B0→+8, "Pitch"→+0xC, "Roll"→+0x10}
  = **64 相机关键帧 @+0x11EC，五字段 {f,f,f,Pitch,Roll}**，区 [0x11EC,0x17EC)

### 2. 任务池 stride=204 铁证（A 级，InsertTaskToList@0x5075e0/SwapTask@0x507b20）
- `mov eax,[ecx+68FD0](m_nCurList); mov edx,[ecx+68FD4](m_nCurTask)`
- `shl eax,4→add eax,edx→lea [eax+eax*2]→lea [ecx+eax*4]` = **句柄×204B**
  = `this + 204×task_id` 池访问；状态字节在条目内 +0x59/+0x5A/+0x5B
  （m_bPoolInUse[2000]@0x639C0 独立数组模型**证伪**）
- 列表句柄表：`lea eax,[eax+eax*4+280Ah]; lea eax,[eax+eax*4]; lea edx,[edx+eax*2]`
  = idx = T + 50L + 102500 → **int[50][50] @0x64080**（现注解 int[50][100]@0x64190
  偏移与维度双错）；-1=空，否则池句柄

### 3. 头域 = UIListBox 派生对话框（A 级，CCCTData_6F10@0x4a6f10）
- 首指令 `call ??0UIListBox@@QAE@XZ`（基类 ctor）→ [esi+0x58]=0x320/[esi+0x5C]=0x258
  （800/600 尺寸）→ ResetContainerState@+0x16C → lstrcpy 循环@+0x224

### 4. UI 部件域（A 级，Create_8770@0x4a8770）
- `lea edi,[esi+5E3F0]` → vtable call + `CreateFromTemplate@UIPushButton`
  = **内嵌 UI 部件 @+0x5E3F0**（m_SlotButtons UIButton[5] 填充物证伪——
  0x5d9ec..0x5f360 跨度 6516/5 非整数）

### 5. FLIRT/ICF 撞名实锤（codecvt 案同族）
- "IsTaskValid"@0x5081a0 = `mov eax,ds:dword_56FD88; mov g_CCBCamControlData+5B8h,eax; retn`
- "GetFreeSpaceInPool"@0x5081c0 = `fld ds:dword_56FD88; fadd st,st; fstp +5B4h`（浮点加倍器）
- "GetTaskNumInList"/"ClearList" = 5B jmp thunk 互跳
  → **这四个"CCCTData 方法"名字全假**；CCCTData "ctor"@0x5058f0 写
  [0x69094..0x690A8] = **恰是 CCBCamControl 的 m_vecCircleCenter/m_vecCircleEnd**
  （写序逐字节吻合注解）——CCCTData 的 ctor 证据实为相机域函数

## 区间填充物证伪清单（现注解 → 真结构）

| 现注解 | 证据 | 真结构 |
|---|---|---|
| m_CamEntries int[1794]@0x98c | InitEntries@0x44d780 lea esi,[ecx+2188h] + FOV 数学 + SetRect@UIWnd | 0x2188 起相机条目结构（150×? 待解码） |
| m_bPoolInUse uchar[2000]@0x639c0 | 状态字节在池条目内 +0x59..0x5B | 证伪（区间填充物） |
| m_nCCTIndex int[50][100]@0x64190 | idx 公式闭合 @0x64080 | int[50][50]@0x64080（-1=空句柄） |
| m_SlotButtons UIButton[5]@0x5d9ec | 6516/5 非整数 | 内嵌 UI 部件 @0x5E3F0 |
| m_TabLists _BYTE[6040]@0x5f360 | ShowAllSlots 32 站访问（0x60640） | 真 UI 列表域（待解码） |
| 4 大洞 [0x2598,0x5558)[0x555c,0x3cfb8)[0x4af58,0x5d9ec)[0x60af8,0x68fb0) | 方法 this-form 全二进制零访问 | 任务池散布区+未知域（经 204×idx 间接访问故 disp 不现形） |

## 开放案（下轮裁决）

1. **接收者归属**：InsertTaskToList/SwapTask 的 this 是否 = g_CCBCamControlData？
   （需调用点 ecx 回溯——若池方法接收者是独立对象，430KB 单体模型破裂，
   改两对象模型：对话框+池。pool 方法访问 [this+0x68FD0] 与相机域成员同域，
   单体模型当前占优但未闭环）
2. **31 独立名重叠仲裁**：+0x624..+0x9284 区 g_nCBFormation1/g_InputState/
   g_CScreenMode 等 own-name 引用 40-149 次、零 +disp 成员形——独立对象
   （锚区过称）还是成员双重注解？W1 查一同法逐名裁决
3. **池条目 204B 结构**：+0x59/+0x5A/+0x5B 状态字节 + SwapTask 内 [ebx+0x15]/
   [ebx+0x58]/[ebx+0x20] 等字段全解码
4. **类名定谳**：INI 节名全文（aEditorcamD 完整串）+ PDB 交叉 →
   EditorCamDlg / CCBCamControl / CCCTData 三名归一
5. **头域对话框布局**：UIListBox 基类域 + 0x58/0x5C/0x16C/0x224 域解码

## 对空洞普查的口径修正

CCBCamControl 348KB"洞" = 真子结构未解码（池 204×idx 间接访问不产生
常数 disp）——**大洞+零访问 ≠ 无主空间，可能是经计算寻址的池/表**。
普查器已诚实报告（洞区列表+零访问面），解读需配 disp 普查+间接寻址检查。

—— 探针产物: data/status/probe_ccbcamcontrol_{census,global_census,twin,
pooldecode,dynamicinit}_20261126.json

---

# 定谳 v2（同日续战：接收者回溯 6 探针后反转）

## 终局裁决：BSS"全局"不是对象，真实例在堆上

### 1. g_CCBCamControlData@0x17AAF64 = 静态变量块（对象身份证伪，A 级）
54 个引用点全分类（probe_dynamicinit）：**50 绝对写 + 2 ABS_RW + 2 CIniFile push，
零 `mov reg,offset` 装载形**——该地址从未作为对象指针传递。绝对写 disp 全景：
- `+0x0`：sprintf 缓冲（`sprintf(buf,&g_CCBCamControlData,"EditorCamD%d",idx)`）
- `+0x2C4..+0x32C`：独立静态变量（compiler_init_00503DD0/E20/EC0/F10/F60、
  ui_width_init_00503E70 等微函数各写 4-16B）
- `+0x5B4..+0x61C`：七个方法各自的状态导出槽（GetFreeSpace-folded +5B4/
  IsTaskValid-folded +5B8/~CCBCamControl +5C0/Create +5D0/CCBCamControl_Init
  +5E0/StartList +5F0/StopList +600/UpdateCircleSet +610，各 16B=4 dword）
- **binary_size 0x690B0 锚声明全错**：吞了 ~30 独立全局（g_nCBFormation 等）+
  静态变量块；CCBCamControl.json 的现注解不可修复，需退役重建

### 2. 真实例 = 堆对象，多载体（probe_receiver 调用点 ecx 全回溯）
| 载体 | 接收的方法 | 证据 |
|---|---|---|
| [CCBStage+0x10] | Init/DoTask/ProcCamMove/AddTask/ClearFinishedTask/CCCTData-copy-ctor | Create_be50 创建+delete；disp 至 0x690AE |
| [CCBStage+0x4C] | DoList/ProcessCamMove/KeepCurCam/DoLineMove | Create_be50: call DoList 后 delete |
| [CCBRoleState/CCBSystem/RenderTarget2/CCBStageCam+0x10] | 同 [CCBStage+0x10] 方法族 | 四类共用指针成员 |
| .data 指针表 dword_56FD88..56FDA8 | Create/StartList/StopList/UpdateCircleSet/Create | `mov ecx, ds:dword_56FD90` 直装 |
| DlgProc esi | Show/ShowCameraDialog/ReadCameraDialog/GetData_B8D0 | 对话框过程携带 |

### 3. CCCTData 身份完全溶解
- 4 个"池方法"=FLIRT/ICF 假名（v1 已证）
- "ctor"=错挂（写序=相机域 vec，v1 已证）
- m_Pool tagCCT[2000] 模型半真半假：stride 204/idx 乘法链是**真池**但属于
  **堆类**（InsertTaskToList 接收者=[X+0x10] 堆对象），不属于 BSS 全局
- m_bPoolInUse/m_nCCTIndex 偏移维度双错（v1 已证）

## 重建战役立案（下轮主攻）
1. **创建点定尺寸**：找 [CCBStage+0x10] 的 operator new 字面量 → 编译器
   sizeof A 级（堆类真尺寸）
2. **编译单元聚类归属**：33+22 方法按地址域聚类（0x505-0x508 交织=同一
   .cpp；CalcDist@0x41c900/ProcessTask@0x4533f0 远散=疑错挂）逐方法
   接收者定主
3. **实例拓扑**：[CCBStage+0x10] vs [CCBStage+0x4C] 同类两实例 or 两类？
   .data 指针表 9 槽各指什么？
4. **BSS 块分解**：g_CCBCamControlData 退役 → 逐变量 globals 条目
   （+0x2C4..0x32C 静态变量族 + +0x5B4..0x61C 状态导出槽族）
5. **池条目 204B 结构**（v1 开放案③不变，归属改堆类）
6. **类名定谳**（v1 开放案④：INI 节名全文+PDB 交叉）

## 对既有机制的连带
- 空洞普查：CCBCamControl 348KB"洞"将在重建后消解（二注解全退役，
  BSS 块分解后洞归零或重归真结构）
- W1 锚审计：PLACEMENT-CONFLICT 病新例（静态变量块被当对象锚）
- globals.json：g_CCBCamControlData type=unsigned char const_data 反而
  接近真相（scratch 块），但 category 注记需按分解结果重写

---

# 定谳 v3（重建战役①收官）：编译器 sizeof 金表 + 双堆类终局

## 决定性证据：`push 0x690B0; call ??2@YAPAXI@Z`（全二进制唯一）
0x690B0=430256 的堆分配**真实存在**（new 后调用链通向 SetCamPos 方法族=
far-tail 大类）——**CCBCamControl 注解 binary_size 精确命中**，但锚错位：
真身是堆类 X（实例=[CCBStage+0x10] 等），不是 BSS 静态变量块。

## 终局结构：两类并存（方法集交织=同编译单元家族）
| | 类 X（far-tail 相机模块） | 类 Y（编辑器对话框） |
|---|---|---|
| sizeof（A 级） | **0x690B0=430256** | **0x62588=402824** |
| ctor | new 后 SetCamPos 族链（地址被误名，真 ctor 待正名） | **CCCTData_6F10@0x4a6f10** |
| 特征 | tail 相机状态 0x68FB0..0x690AE / m_nCurList@0x68FD0 / 任务池 | UIListBox 派生头域 0x58/0x5C/0x16C/0x224 |
| 实例载体 | [CCBStage+0x10]/[CCBRoleState+0x10]/.data 表 | EquipUI+0x2AFC8 |
| 方法归属 | SetCamPos/DoTask/ProcCamMove/SwapTask/InsertTaskToList（disp 至 0x690AE 自洽：430256-0x690AE=2） | 头域对话框方法 |
两类方法在 0x505xxx-0x508xxx 地址段交织 = **同一 .cpp 编译单元**（VC6 聚合律）——
逐方法归属需编译单元聚类+接收者载体双向证据。

## 全项目大分配金表（probe_heap_alloc_census，33 笔 ≥0x4000）
**精确命中 9 类**：ParticleEffect 362860 / MainEquipUI 209008 / RoleStatePanel
176256 / LineupUI 171244 / SaleUI 105912 / SkillUI 101940 / CCBSystem 90840 /
**CCBCamControl 430256** / CEffect 245800（=InitVertexBuffer@CEffectSystem）
**虚胖待修 2 类**：MainPropUI 247976→**219984**（-27992）/ UITitle_JDHY
377700→**290488**（-87212）
**反向低估 1 类**：EquipUI 120116→**266260**（+146144，EquipUI=266KB 大容器，
尾部 +0x2AFB8..0x2AFD0 持七模块指针表）
**待名新类**：0x56630=353840 / 0x27BD4=162772（??0LineupUI mangle 惯性疑）
**关联链**：CCBStage 0xA4128=672040(ctor)+0xA48B0=673968(InitFromDescriptor)
——注解 673792 居中（真值待两态分辨）；CEffMgr 0xA930 ×3（池模式复分配）

## 下轮（重建②-⑥）
1. binary_size 金表修正（MainPropUI/UITitle_JDHY/EquipUI + CCBStage 两态分辨）
   ——注意涟漪：空洞普查/语料重导随动
2. 类 X/Y 方法编译单元聚类归属（CCBCamControl.json→类 X 真身重建；
   CCCTData.json 退役；类 Y 新建）
3. BSS 块分解（g_CCBCamControlData→逐变量 globals）
4. 类名定谳（INI 节名全文+PDB 交叉）
5. 池条目 204B 结构（归属类 X）

---

# 定谳 v4（重建③·PDB 交叉）：双真类架构 + tagCCT 闭合

## PDB 金矿（data/pdb/pdb_export.json，PAL3A 符号族 242 命中）
- `??0CCBCamControl@@QAE@PAVCCBStage@@PAVCCBStageCam@@@Z` — 构造签名
  (CCBStage*, CCBStageCam*) **恰对齐尾成员 m_pStage@0x68FB0/m_pCam@0x68FB4**
- `?DestroyObj@CCBStage@@AAE_NPAPAVCCBCamControl@@@Z` — CCBStage 指针成员
  类型 = **CCBCamControl\***（[CCBStage+0x10]/+0x4C 载体定谳）
- **CCCTData 15 方法全真**：InsertTaskToList/SwapTask/GetFreeSpaceInPool/
  IsTaskValid/ClearList/GetTaskNumInList/AddTaskToList/DelTaskInList/GetCCT/
  Create/Destroy/Init/Load/Save/Reset——二进制 4 微型函数=注解错挂地址
  （名字不假，地址错；真体在别处待重挂）
- **CCBCamControl 40 方法**：平行任务 API + DoCircleMove(+SpeedUnknow/
  TargetUnknow/TimeUnknow 变体，PDB 源码拼写彩蛋)/DoLineMove(+3)/
  DoMechanicsMove/GetCCT/GetCircleCenter/GetCircleEnd/GetCurList/GetCurTask/
  HandleInput/DoList——语料 GetData/GetData_B720/GetData_B8D0=GetCCT 误名
- `??0tagCCT@@QAE@XZ` — **tagCCT 真名实锤**

## tagCCT 尺寸闭合（池模型定谳）
tagCCT.json binary_size = **204 = 0xCC** 与池乘法链 `shl4→×17→×3→×4` 精确
一致；字段地图完整（fp[4]@0x0/dwID@0x10/bValid..bSplice@0x14-17/fStartTime/
fExpectTime/StartPos tagCam@0x20/EndPos@0x38/nStartCam/nEndCam@0x50-54/...
fCircleEndZ/fSwing 族/fStartFOV/fEndFOV/dwReserved@0xC4——0x58-0x5B 域=
二进制状态字节 bValid 族邻域待核）。池 = `this + 204×handle`，句柄表
int[50][50]@0x64080（T+50L+102500 闭合）。

## 架构模型（v4）
- **类 X = CCBCamControl**（0x690B0=430256 A 级 ✓）：池+句柄表+m_nCurList/
  m_nCurTask@0x68FD0/4+相机尾域 0x68FB0..0x690AE+任务 API——实例 =
  [CCBStage+0x10]（CCBCamControl\* PDB 型证）
- **类 Y = CCCTData**（0x62588=402824）：ctor=??0CCCTData（PAL3
  0x4a6f10，UIListBox 派生——任务编辑对话框数据类），实例=EquipUI+0x2AFC8
- **判别证据**：池方法 disp 0x68FD0=425424 > 402824 ⇒ 池方法属类 X 非 Y；
  CCBCamControl 的平行任务 API = 转发或自有实现（逐方法定谳挂下轮）
- **现注解 chimera 实锤**：CCCTData.json binary_size=430256(=X 的尺寸!)+
  成员池模型(=X 的域)——两类内容被混装；CCBCamControl.json 头域成员
  （m_pvecCenter@0x8 等）与池[0] 域冲突（tagCCT[0].fp[2]@0x8）——头域成员
  证据链疑错挂（source 引 CCBRoleState::ProcessActions 混乱链）

## 下轮手术清单（重建④）
1. CCCTData.json 重铸：binary_size 0x62588=402824、方法表=15 PDB API、
   池/表成员重验（类 Y 自有池尺寸？）
2. CCBCamControl.json 重铸：确认=类 X；头域成员逐个重取证（与 tagCCT[0]
   冲突面）；池成员 m_Pool tagCCT[2000]@0x0 落位（2000=0x63A80/204 闭合）
3. 方法重命名红利：GetData 族→GetCCT（PDB 对齐，语料渲染随动）
4. 4 微型函数错挂重挂（IsTaskValid/GetFreeSpaceInPool 真体搜索）
5. 类名定谳收官：类 Y 在 EquipUI+0x2AFC8 的完整证据链落 globals
