# A2 进度（26 个 ≤2 错文件逐个修复）

> 用户指示：「我接受逐个 IDA 查询的消耗，本来反编译就有这个成本，逃不开的」
> ⇒ 逐个诊断+修复，每个取其 L1/L2 二进制证据。

基线：`ok=55/202` · `L1=14` · `matched=156`（`_cleanup_baseline_20260915_FINAL.md`）

## 已诊断（含根因）

| # | 文件 | 错误 | 根因（已取证） | 状态 |
|---|---|---|---|---|
| 1 | `UIGameOver.cpp` | `C2227 vftable->Create` | **`void* vftable` + `->` 访问**（20 个文件同源，**批量机会**）| 待修（需二进制验证等价变换）|
| 2 | `UILoadingFrm.cpp` | 同上 | 同上 | 待修 |
| 3 | `UIWnd.cpp` | `C2065 UIInitSystem` + `C2227 vftable->OnMessage` | 同上 + 一个未声明的全局 | 待修 |
| 4 | `SoundMgr.cpp` | `C2660 SetOpenMode` ×1 + `C2664` ×1 | 成员 `m_szScriptMusic` 声明为 `std::basic_string`(8B)，但**该地址内存复用**为 `CPK`（917948B）⇒ 需 **inline union** | 待修（需确认 union 偏移）|
| 5 | `C3DSpark.cpp` | `C2660 RenderGeomQuad` | 库声明（`include/gbengine/gbMesh.h:423`）**4 参**，decomp 调用给 **3 参**（缺 `gbGeomQuad*`）| 待修（需找实参来源）|
| 6 | `UI3DCtrl.cpp` | `C2102 '&' requires l-value` ×2 |  `COERCE_FLOAT(GetTickCount())` = `*(float*)&(rvalue)` ⇒ 对 rvalue 取地址 | 待修 |

## ★ 批量根因：`void* vftable`（20 个文件全部编译失败）

```cpp
// UIGameOver.cpp:80,91,96（UILoadingFrm.cpp:53,57,62 同形）
  void *vftable;
  vftable = (*(void **)&(this->m_Blood));
  ((void ( *)(UIStatic *, _DWORD, int *, UIGameOver *))vftable->Create)(...);   // C2227
```
**对照能编译的形态**（`UIStatic.cpp:177,179`）：`vftable` 已类型化 + `vftable[2](...)` 下标调用。

**⚠️ 修复前必须确认**：`vftable->Create` 的语义是"**调 vtable 里的 `Create` 槽**"还是
"`Create` 是结构成员"。这决定生成 `vftable[slot](...)` 还是 `((T*)vftable)->Create(...)`。
**⇒ 需取该调用点的反汇编证据**（CLAUDE.md：禁止未验证修改）。

## 尚未诊断的 20 个

`CCBAI` · `CCBLineupWindow` · `BINK` · `Comp_DonateUI` · `DealData` · `SwordUI` · `UIButton` ·
`TextureLib` · `SceneMgr` · `UIDialog` · `CCBStageEffect` · `Combat` · `InputSystem` ·
`ArcPastScene` · `CG_Entry` · `ScriptPoolPage` · `UIMap` · `UIRoleSelectDialog` · `Role` · `UICamera`
