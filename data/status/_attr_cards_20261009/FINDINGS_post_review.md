# 立案 · 真字节回归（独立复核发现，非本轮引入）

**日期**：2026-10-09 · **来源**：独立复核 0d54e301 的 L1 逐行对账
**发生窗**：2026-10-07 01:16 → 2026-10-08 21:52（**E2 窗口**，早于本轮）

## R1 · `CCBStageEffect::PreLoadEffGroup` @0x00509090 — L1 → partial

| 项 | 内容 |
|---|---|
| **症状** | 原 `E9 0B 00 00 00`（5B 尾跳 + NOP）→ 现 `51 E8 .. 59 C3`（push ecx / call / pop ecx / ret，8B） |
| **根因形态** | thunk 体被渲成 **cdecl 自由函数调用** `compiler_init_005090A0(this)`（声明在 `pal3/src/free_functions.h:352` `void compiler_init_005090A0(...);`）而非**尾跳** |
| **关联纪律** | `_d1_ledger.md`：「thunk 契约 = `jmp->retn`（0 栈参）」——本例正是该契约被破坏 |
| **修法方向** | ① thunk 尾跳渲染（`jmp` 形，非 `call`）② 或给 `compiler_init_005090A0` 桩 `__thiscall` 形签名 |
| **优先级** | **HIGH**（真字节回归，会烤进 L1 基线；`--rebaseline` 前必须先修）|

## R2 · L1 总体塌陷（10 单元丢绿）—— L1 总体债

`S2 108/209 → 100/210`，ok→fail **10** 个（复核修正：此前我说"8 个"是错的）：
`CCBResultWindow` · `Combat` · `CEffQuad` · **`Math`（单元整个消失）** · `SoundMgr` · `UI3DCtrl` · `UICaption` · `UIMap` · `UIPushButton` · `Object3D`
fail→ok 2 个：`CCBStageRole`（新文件）· `UITitle_ArcSave`
单元宇宙 209→210（−Math.cpp、+CCBStageRole.cpp、+CG_Entry.cpp）

## R3 · L1 精确对账（复核逐行核算，可查）

```
85 = 94 − 12（总体退出）− 1（真回归 R1）+ 4（增益）
13 行丢失 = 12 行总体退出 + 1 行 R1
  12 行退出：UICaption::Destroy · UI3DCtrl/UIPushButton/CCBResultWindow 的
            UIWnd::scalar deleting destructor COMDAT ×3 · UIMap::Destroy/OnMessage ·
            CCBResultWindow::SetDirty · UICaption::DestroyPanel ·
            Object3D::CheckMouseLPressed · Combat::ReleaseCompletedEffects
4 行新增 = PalScriptWaitObj::ReleaseObject @0x4A68D0（partial→L1）
         + UIWnd::OnMessage @0x445D10（新入总体；正是 c6692adac owner 加权修的地址）
         + UITitle_ArcSave dtor @0x47BD00 + UIWnd dtor @0x44E5C0
partial 闭合：359 = 348 + 1 + 10
```

**⇒ 结构性排除本轮**：`UIPushButton`/`Actor` 的调用点所在单元**都是红单元、不在 L1 总体里** ⇒ 本轮 2 处改动**结构上不可能**影响任何 L1 计量单元。

---

# 记档坑（LOW，但下次会踩）

## G1 · decomp 渲染**吃掉前导下划线**
IDB 名 `_todo_00532A30` → 伪代码渲染成 `todo_00532A30`（无下划线）。
而 `Actor::_todo_00532A20` 因走 mangled-demangle 路径**保留**下划线。
⇒ 两种形都命中 `emit_cpp.py:21` 的 `_todo_[0-9A-Fa-f]+|todo_[0-9A-Fa-f]+` 正则 ⇒ 修复有效，但**理由与设想不同**。
⇒ 下次给 skip_functions 命名时，**两种形都要能被 `collect_sub_refs` 认出**。

## G2 · `int f(...);` 在 C++ 下合法（MSVC6 实测）
「`(...)` 需至少一个具名参数」**只对 C 成立，对 C++ 不成立**。
项目自带 cl 12.00.8168 四组最小用例全部 CLEAN；现有 **8 个绿单元**已含 `int f(...);`
（Scene/TextureLib/UICamera/UISystem/UIQuadManager/CEffShock/CCBItemWindow/CCBProtectWindow）。

## G3 · `char`/`bool`/`unsigned char`/`signed char` 字节等价（受控实证）
项目同款 flags `/O2 /Ob2 /Oi /Ot /Oy /Gd` + 项目 VC6：四者编译 `if(a)` 字节**全同**
`8A 44 24 04 84 C0 74 05`；`int` 为 `8B 44 24 04 85 C0`（**不同**）。
⇒ **宽度才是字节约束，1 字节类型名不是**。禁猜测条款管的是"知识主张"，不管"表示选择"。
⚠️ 约束：若该参数被外传给其他函数，movsx/movzx 会使类型名字节相关 ⇒ 须重新取证。
更严格的替代：`_BYTE`（IDA 式宽度占位，本仓已用于成员，如 `CEffMgr.m_EffTable` `_BYTE[584]`）。
