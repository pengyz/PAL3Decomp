# reference · P0/P1/P2/长期 四线前置分析（captain 备料）

**type**: reference
**created**: 2026-10-10（Goal Round 5-8 期间，等 T1 诊断时完成）
**status**: 备料完成，P0 收敛后可直接执行
**related**: `decision_byte_match_is_goal_judges_may_improve.md`

## P1 字节裁决（⚠️ 不能简单扩展）

`_completeness_convergence_ledger.md:33-35` 实锤：
> **N-F3 存量毒**：`&E.T`→`((T*)&E)` 对**非零偏移基类**折偏移——
> 例 `((MUIDialogMgr*)&this->m_DlgEx)`（`UIDialog@0`+`MUIDialogMgr@72`）——须 match 裁决/规则层修

**裁决**：❌ 不能把 `stage4_substitution.py:483-493` 简单扩展到 `E.T` 直读形（现有 `&E.T` 改写**已有丢偏移 bug**，扩展会传给 162 站点）。
**✅ 正确顺序**：① 先修 N-F3（`&E.T` 补 `+off` 或保留原形）→ ② 再扩展 `E.T` 直读（复用同一含偏移改写）→ ③ `CCBResultWindow:820` 的 **vfptr 形单独处理**（归因卡 ⑦）。
**⚠️ 撤销**「一补丁翻 7 绿」（无出处，kiro 终审已点名）。

## P2 类型坍缩（147 条 → 3 类分界）

**`X* → 标量` 赋值 72 条**（top 4 单元）：
| 单元 | 条数 |
|---|---|
| `pal3/src/Misc/ScriptVM.cpp` | 14 |
| `pal3/src/UI/UIScene.cpp` | 11 |
| `pal3/src/Role/RoleSystem.cpp` | 10 |
| `pal3/src/GameBase/PAL3.cpp` | 7 |

**🔑 关键分界（lvalue 分类）**：
| 形态 | 样例 | 处理 |
|---|---|---|
| **`reg_*` 寄存器临时变量** | `ScriptVM.cpp:347` `reg_EDI = (_DWORD *)RolePtr;` | ❌ **不改注解**（codegen 寄存器建模，非注解坍缩）—— 误改会引新 bug |
| **真成员类型坍缩** | `UIScene.cpp:907` `*(_DWORD *)&this->m_bCursorLeft = gfxMgr->NewTexture(v3);` | ✅ 查 `structs/*.json` 的 `type`，A 级取证后改回指针 |
| **伪语义名 + 类型错** | `PAL3.cpp:1259` `m_nRetryCount = (PAL3 *)(&dword_1000000 + 257);` | 🔴 **双重问题** —— 类型改回指针 **+ 改名**（存指针却叫 retry count，违反禁伪语义命名）|

**⇒ 若把 147 条当一类批量改，会误伤 `reg_*` 临时变量。**

## 长期：运行时 trace 裁判边界（**修正 C 路说法**）

PAL3.exe 导入 **7 个 DLL**（`objdump -p` 实测）：
| DLL | 钩子点 |
|---|---|
| `KERNEL32` | `QueryPerformanceCounter`/`GetTickCount`/`GetLocalTime`/`Sleep`/文件 API |
| `WINMM` | `timeGetTime` |
| `DINPUT8` | `DirectInput8Create` + 设备读 |
| `USER32` | `MsgProc` / 消息泵 |
| `ADVAPI32` | 注册表 |
| `BINKW32` | 播放时序 |
| `GBENGINE.DLL` | **249 个按名导入**（含 `gbCreateGraphManager`）|

⚠️ **修正**：C 路说「边界 = 249 导入 + **d3d9 层**」—— **导入表无 `d3d9.dll`**（kiro 终审也点过）。
⇒ **正确边界 = 249 个按名导入 + 7 个系统 DLL 的确定性钩子**；渲染全在 `GBENGINE.DLL` 内部
⇒ 这进一步印证 kiro 对「录制型 gbGfxManager」的否决（`DrawIndexedPrimitive` 在 gbengine 内部、不经 PAL3 的 vptr）。
