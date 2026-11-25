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
