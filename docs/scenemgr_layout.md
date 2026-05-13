# SceneMgr 内存布局 (PAL3.exe, 非 PAL3A)

## 概要

`g_SceneMgr` @ `0x00C04390`, size = 54116 bytes (0xD364)

SceneMgr 本质上是 CEffMgr 的超集。其中间区域 (+0x00~+0xA940) 同时被特效系统
和角色系统以不同 stride 访问——这是通过 inline accessor + reinterpret_cast 实现的。

## 真实 C++ 布局 (编译器视角)

```cpp
class SceneMgr {
    // === CEffMgr 部分 ===
    tagEffClass m_EffClass[32];       // +0x0000, 32*72=2304
    char _pad_900[44];                // +0x0900
    tagEffObj m_EffTable[2048];       // +0x092C, 2048*20=40960
    int m_nEff;                       // +0xA92C
    float m_fCurTime;                 // +0xA930
    float m_fDeltaTime;              // +0xA934
    float m_fTimer;                   // +0xA938
    float m_fTimeScale;              // +0xA93C (init 1.0f)
    // === CEffMgr 结束 (+0xA940) ===

    // === SceneMgr 自有数据 ===
    char _gap_A940[0xC5D0-0xA940];   // +0xA940, 7312 bytes TODO
    CGameData *m_pGameData;           // +0xC5D0
    int _unkC5D4;                     // +0xC5D4
    CameraCtrl *m_pCameraCtrl;        // +0xC5D8
    PalScriptMgr *m_pScriptCtrl;      // +0xC5DC
    SceneMgrCamBlock m_camBlock;      // +0xC5E0, 856 bytes
    int m_nCurrentScriptSlot;         // +0xC938
    char _gap_C93C[0xCD0C-0xC93C];   // +0xC93C, 976 bytes TODO
    float m_fMoveParam;              // +0xCD0C
    char _gap_CD10[0xD35C-0xCD10];   // +0xCD10, 1612 bytes TODO
    gbGeomNode *m_pCollisionNode;     // +0xD35C
    char _tail[4];                    // +0xD360
};
```

## 多视图访问模式

### 视图 A: 特效系统 (真实内存布局)
- `m_EffClass[32]`: base=+0x00, stride=72, count=32
- `m_EffTable[2048]`: base=+0x92C, stride=20, count=2048
- 用于: RenderAll, RenderUpdate, CreateEffect 等

### 视图 B: 角色/脚本系统 (reinterpret_cast 访问)
- `ARC_PlayerAtt[5]`: base=+0x50, stride=1408, count=5
- `RoleSystem[5]`: base=+0x1BD0, stride=8704, count=5
- 用于: RunEvent, RunScript, Render, UpdateTimers 等

### 原始代码实现方式

```cpp
// SceneMgr.h 中的 inline accessor
inline ARC_PlayerAtt* SceneMgr::GetPlayerSlot(int i) {
    return (ARC_PlayerAtt*)((char*)this + 0x50 + i * sizeof(ARC_PlayerAtt));
}
inline RoleSystem* SceneMgr::GetRoleSystem(int i) {
    return (RoleSystem*)((char*)this + 0x1BD0 + i * sizeof(RoleSystem));
}
```

## 需要视图转换的函数

以下函数以**视图 B (角色系统)** 访问数据，在编译阶段需要转换为 cast 表达式:

| 地址 | 函数名 | 访问方式 | 转换目标 |
|------|--------|----------|----------|
| 0x410470 | ScriptSystem::RunEvent | PlayerSlots[slot].byEventFlags | GetPlayerSlot(slot)->byEventFlags |
| 0x4100A0 | ScriptSystem::RunScript | PlayerSlots[slot].nScriptCounter | GetPlayerSlot(slot)->nScriptCounter |
| 0x4101F0 | ScriptSystem::RunWithDelay | PlayerSlots[slot].nScriptSpeed/Counter | GetPlayerSlot(slot)->... |
| 0x40C630 | ScriptSystem::Render | RoleSystems[slot].m_fTargetX | GetRoleSystem(slot)->... |
| 0x40C630 | ScriptSystem::Render | RoleSystems[slot] (RenderRole call) | GetRoleSystem(slot)->RenderRole(...) |
| 0x40C790 | ScriptSystem::Cleanup | iterate RoleSystems | GetRoleSystem(i)->... |
| 0x40C960 | ScriptSystem::Destroy | iterate RoleSystems | GetRoleSystem(i)->... |
| 0x411F60 | ScriptSystem::UpdateTimers | RoleSystem fields | GetRoleSystem(slot)->... |
| 0x4194C0 | ScriptSystem::UpdateObjects | RoleSystem fields | GetRoleSystem(slot)->... |

以下函数以**视图 A (特效系统)** 直接访问 m_EffTable，无需转换:

| 地址 | 函数名 | 访问方式 |
|------|--------|----------|
| 0x4CDBF0 | SceneMgr::RenderAll | m_EffTable[i] 遍历 |
| 0x4CDC20 | SceneMgr::RenderUpdate | m_EffTable[i] 遍历 |
| 0x4CDCA0 | CEffMgr::CreateEffect | m_EffTable[i] 查找/分配 |
| 0x4CDED0 | CEffMgr::InitEffClass | m_EffClass[i] 注册 |
| 0x4CE100 | CEffMgr::LoadEffData | 加载 effect 配置文件 |

## 完整受影响函数列表（自动扫描 2026-05-13）

188 个函数包含视图 B 错乱访问（`PlayerAtts[4/5].byMagicLevel[...]` 或 `m_camBlock._field_`），
共 839 处引用。**这些函数需要在编译阶段手动修复视图转换。**

Top 20（按引用数）：

| 地址 | 函数名 | 引用数 |
|------|--------|--------|
| 0x0041D9A0 | CameraUpdate_Internal | 60 |
| 0x00408FD0 | PAL3::FullInit | 51 |
| 0x0049B2E0 | UIListBox::_init_49b2e0 | 39 |
| 0x004A9870 | UIListBox::Method_9870 | 25 |
| 0x00474C80 | UIListBox::_init_474c80 | 24 |
| 0x00473B50 | UIListBox::_init_473b50 | 24 |
| 0x00472AA0 | UIListBox::_init_472aa0 | 23 |
| 0x00460A90 | PAL_GDB::Method_0a90 | 16 |
| 0x00424C20 | PalScriptMgr::ExecuteBlock | 16 |
| 0x00435830 | PalScript::_nearby_435830 | 14 |
| 0x0040E5F0 | ScriptSystem::Execute | 14 |
| 0x0041A450 | RoleSystem::_nearby_41a450 | 14 |
| 0x00435BF0 | PalScript::_nearby_435bf0 | 14 |
| 0x004E5800 | PAL_GDB::_auto_4e5800 | 13 |
| 0x00494D70 | EquipUI::HandleInput | 12 |
| 0x0042F460 | PalScriptMgr::_nearby_42f460 | 12 |
| 0x0042EBE0 | PalScriptMgr::ExecuteOpcode | 12 |
| 0x00417420 | RoleSystem::_nearby_417420 | 11 |
| 0x0048D040 | CameraCtrl::UpdateBlendWeight | 11 |
| 0x00407320 | PAL3::StartCombat | 11 |

状态：**跳过自动修复，标记为手动修复阶段处理。**

## 偏移对齐验证

```
PlayerAtts:  +0x50 + 5*1408 = +0x50 + 0x1B80 = +0x1BD0 (= RoleSystems base, 完美对齐)
RoleSystems: +0x1BD0 + 5*8704 = +0x1BD0 + 0xAA00 = +0xC5D0 (= m_pGameData, 完美对齐)
EffTable:    +0x92C + 2048*20 = +0x92C + 0xA000 = +0xA92C (= m_nEff)
EffClass:    +0x00 + 32*72 = +0x900 (= _pad before EffTable)
```

## 二进制证据

- stride 1408: `add esi, 580h` at RunWithDelay+0x86
- stride 8704: Render loop `v3 += 2176` DWORDs
- stride 20: RenderAll `v1 += 5` DWORDs, `mov edi, 800h` (2048)
- stride 72: sub_4CDCA0 `this + 18*classIdx` (18 DWORDs = 72 bytes)
- tagEffClass size=72: PAL3A PDB confirmed
- tagEffObj size=20: PAL3A PDB confirmed, fields: {CRC, CRC, RunGroupID, bValid, bIdle, ...}
- ARC_PlayerAtt size=1408: PAL3A PDB confirmed, stride from binary confirmed
- RoleSystem size=8704: gen_size from annotations, stride from binary confirmed
- CEffMgr size=43312 (PAL3A): 28(header) + 2304(EffClass) + 44(pad) + 40960(EffTable) + 16(tail) ≈ 43352... 需要细化

## IDA 标注策略 (当前阶段)

选择**视图 B** (PlayerAtts[5] + RoleSystems[5]) 作为 SceneMgr struct 的主表示,
因为 90%+ 的函数从此视角访问. RenderAll 等少数特效函数显示为 raw 偏移.

## 编译阶段处理方案

1. SceneMgr.h: 用真实布局 (CEffMgr 视图) 定义 struct
2. SceneMgr.h: 添加 inline GetPlayerSlot/GetRoleSystem accessor
3. gen_cpp 后处理: 识别 `m_PlayerSlots[N].field` / `m_RoleSystems[N].field` 模式
   转换为 `GetPlayerSlot(N)->field` / `GetRoleSystem(N)->field`
4. 手动验证所有视图转换函数的字节匹配
