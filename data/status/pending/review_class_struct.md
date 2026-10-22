# class/struct mismatch 复核

## 根因验证

**C4099 属实，C2653 归因 REJECT。** class/struct 键不一致**只产生 warning，不产生 error**。

自建 TU（重建 pre-fix 头 43 条 `struct X;` + `Combat/CCBStage.h` 同 TU，即 lead 声称的危害面）实测：
`C4099=50 / C2653=0 / error=0`，obj 正常产出。含 `'CCBStage' : type name first seen using 'struct' now seen using 'class'`（old_free_functions.h:56）。

全仓唯一 `C2653 'CCBStage'` 在 `CCBSystem.cpp:1513`，同文件:行的**伴随错误**是
`C2440 cannot convert from 'float' to 'class CCBStage *'` + `C2227 left of '->CCBStage'`。原句为 codegen 产物
`(((CCBStage *)v3))->CCBStage::EditorUpdate();`（`v3` 为 Hex-Rays 垃圾 float 局部量）。我用同形 case 精确复刻三元组 ⇒
**C2653 是 float→指针转型失败的级联，与 class/struct 键无关**。

## 修复方案评估（A/B/C）

| 方案 | 裁决 | 依据 |
|---|---|---|
| A 改 free_functions.h | ✗ | 治标且不可留存：该头 auto-generated + untracked（三重灭失），codegen 覆盖；`phase2_retain.py` 禁直改 `pal3/src` |
| B 改 emit 逻辑 | ✓ 但只清 warning | 键确实在此决定（正确定层）。已落 `emit_cpp.py:848`（未提交）。实测同 TU **C4099 50→5 / error 0 / C2653 0**。⚠️ 收益 = 0 error；且"全 class"非一致解，残留 5 条**反向** C4099：gbengine 真 struct 型 `gbVec3D/gbColorQuad/gbTextureArray/gbVFile/gbGfxManager` 被 emit 成 class |
| C 改 CCBStage.h | ✗ | 反向制造新分叉（定义侧 776 头恒 `class`，`emit_headers.py:2143-2155` 硬编码），且只救 35 个名字中的 1 个 |

## 全仓扫描结果

- **fwd-vs-def 键不一致 19 名**：CCBSystem、CatchableType、GRPinput、ObjectCamera、PtrArray、UIWnd、tagCmdData、gbGfxDriverInfo、gbGfxManager_D3D、gbImage2D、gbTextureArray 等。
- **同名 class+struct 双定义 26 名**：`gbengine_api.h`（多为 class）vs `pal3_structs.h` / `gbengine/*.h`（多为 struct）——平铺 dump 分叉，比 free_functions.h 单点更值得修。
- **58 条 C2653 全部归因与 class/struct 键无关**：C2039 成员缺失级联 23 / C2227 系 17 / C2440 转型级联 9 / C2027 不完整型 4 / C2059 解析 1 / C2065 1。
- **发射点实为 11 处**（lead 说 9）：顶层 `class %s;` ×8（含已修的 848）+ 嵌套 `struct %s;` ×2（`emit_headers.py:2160/2227`）+ 嵌套定义 `struct %s {`（1313）。**嵌套侧恒 struct、顶层恒 class 是两个自洽约定**，非笔误级单点分叉。

## 自构造 case

| case | 形态 | 结果 |
|---|---|---|
| T1 | `struct X;` + `class X{}` 正常使用 | 仅 C4099，obj 出 |
| T3 | `(((X*)v3))->X::f()`，v3=float | **C2440+C2227+C2653** 精确复刻 CCBSystem.cpp:1513 |
| T4 | 仅 fwd 声明 + `X::f()` | C2027+C2227+C2653（另一真根因族） |
| T5/T8 | mismatch + float cast / + static、sizeof | 仅叠加 C4099，无新 error |
| T9/T10 | 全局 fwd vs 嵌套定义 | **无 C2143** ⇒ lead 引的 `emit_headers.py:1807` 先例不可复现为最小 case |
| T-pre | 重建 pre-fix 头 + CCBStage.h | C4099×50 / C2653×0 / error×0 |

## verdict

**根因定性 REJECT**：C2653 不由 class/struct 键引起；A/B/C 三案**都修不掉任何 C2653**。B 可保留为 1 行 warning 清理（零风险），但**不得宣称修复 C2653**；真 C2653 需按族修（F1 转型级联 9 条 = codegen 浮点垃圾局部量；F2 不完整型 4 条 = 缺 include/前向声明）。

⚠️ **并案实证（emit 双写点漏洞，live 抓获）**：`free_functions.h` 有两写点，17:19:56 快照为"预生成"**零前向声明**版（单独 include ⇒ 102 error 至 C1003 截断），17:27:07 全量重写后归 0。`emit_cpp.py:825-855` 全量写在 `if free_funcs and not filter_classes` 内，`filter_classes` 跑即留编译破坏态 ⇒ lead 结构修②（合并双写点）**必须做**，否则本次 1 行修随时被污染。
