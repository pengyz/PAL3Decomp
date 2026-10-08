# D 批三方基线对账（2026-09-27 预工版，goal 第三交付物素材）

## 1. 三方读数与时间线（"矛盾"实为时序陈旧，非真冲突）
| 基线 | 读数 | 时点 | 消费者 |
|---|---|---|---|
| data/status/compile_baseline.json | S2 **79/204** | 09-24 16:59 | tools/compile_regression.py（codegen all 内部）|
| data/status/baselines/latest.json | S2 **89/208** | 09-27 03:40 | tools/regression_detector.py（probe 内部）|
| data/status/probe_census.json（现普查） | S2 **92/208** | 09-27 12:51 | status/一切现况判断 |
| data/status/s4_baseline.json | L1 棘轮=63 | — | pipeline/compare_pal3.py（match）；实况待 loop |

## 2. 增益/回退归因（compile_baseline → 现普查，逐单元）
- ok 79 → 92；文件集 204 → 208。
- **新绿 15**：CCBAttackSequen · CCBMagicWindow · Combat · InputSystem · CCBFiveNimbusWindow ·
  CEffAudio · CEffCustomShape · Object · ParabolaCalculator · SoundMgr · UICaption · UIMap ·
  ScriptObj · UIDialog · UIWnd。
- **回退 2**：MatrixStack.cpp · UIProgressBar.cpp（见 §3，非 B/C 批所致）。
- 文件集 +5（CEffAudio/CEffCustomShape/Object/ParabolaCalculator/ScriptObj 首次进入编译面）/
  −1（CG_Entry.cpp 离开）。⇒ 79−2+15=92 ✓ 204+5−1=208 ✓ 逐数闭合。
- 结论：compile_baseline.json **3 天陈旧**；"两份基线矛盾" = 陈旧分母把新增单元计成回归
  （status 输出自认"文件集变化被当成回归"）。处置：B/C 批落地后跑
  `tools/compile_regression.py --update-baseline`（棘轮决策，需用户确认）。

## 3. 2 个回退单元的法证（零回归主张的必须账目）
现象：MatrixStack.cpp 2× C2660 `'SetAsCurrent' : function does not take 2 parameters`（:29/:100）；
UIProgressBar.cpp C2660 SetAsCurrent(:102) + C2660 `'GetOBBox' : function does not take 2 parameters`(:505)。
- **时间窗**：09-24 16:59（ok）→ 09-27 03:40（同错已红）⇒ 断裂在 09-24 夜至 09-26 晚的生成侧窗口。
- **排除头文件层**：`include/gbengine/gbCamera.h:138 void SetAsCurrent(int mode)`（1 参）与
  `gbGeomNode.h:84 gbOBBox* GetOBBox(gbOBBox* box)`（1 参）自 **09-20 后未改动**（git log）。
- **病灶层定责**：生成侧调用形态是 `gbCamera::SetAsCurrent(cam, 3)`（显式 this + 参数的
  限定全调用形态），与手写 SDK 头的成员声明（1 参）契约不符。嫌疑提交窗口 09-26：
  478151285（stage5 双修）/ eb7ddad56 / 3d10adcc2（SDK 虚构清理，"删虚构 2 参重载"纪律
  正当，但暴露了调用形态契约缺口）。
- **修复方向（不在虚构重载回头路上）**：(a) 注解 methods 表登记 gbCamera::SetAsCurrent /
  gbGeomNode::GetOBBox 的正确签名，使 codegen 走成员调用形态 `cam->SetAsCurrent(3)`；
  (b) 或修 codegen 的限定全调用 fallback 形态。二选一先过病灶层检查 + 对抗复核。
- **对零回归的口径**：该 2 单元红于 B/C 批开工前（03:40 已红），**不计 B/C 批回归**；
  但 D 批"收官验证"必须在台账里显式承接（修复或带理由转交）。

### 3.1 二进制法证补全（2026-09-27，capstone 直读 PAL3.exe）
- `CameraCtrl::SetAsCurrent` @0x0041C630：`mov esi,ecx` + 尾 `ret 4`（callee-pop 1 栈参）
  ⇒ **__thiscall + 1 显式 int 参**，与 `include/gbengine/gbCamera.h` 的成员声明**吻合**。
- 其转调 `push ebx; lea ecx,[esi+4]; call dword ptr [0x56a2dc]`（gbengine 导入槽）：
  **ECX = this+4（gbCamera 子对象）+ 1 栈参** ⇒ `gbCamera::SetAsCurrent` 真实约定是
  **thiscall 成员、1 显式参**。
- ⇒ **手写 SDK 头声明是正确的，生成调用形态是病灶**：Hex-Rays 对导入型函数给出
  `gbCamera::SetAsCurrent(cam, 3)`（显式 this 自由形态），codegen 对**已登记方法**
  会变换为成员形态（同文件 `gbMatrixStack::Push(v3)` → `((gbMatrixStack*)v3)->Push()` ✓），
  但对**未登记的导入型 thiscall** 保留自由形态 ⇒ 与成员声明 arity 不符（C2660）。
- **修复方案（定案待复核）**：把 `gbCamera::SetAsCurrent` / `gbGeomNode::GetOBBox` 以
  `__thiscall` 签名登记进 codegen 调用变换所依据的签名表（functions/imports 表），
  触发既有成员形态变换。**禁止**在 include/gbengine 加 (gbCamera*,int) 静态/自由形态
  （静态调用 ABI 是 push this，与真实 mov ecx,this 字节不符——假修复）。
  落地走病灶层检查三问入 commit + 四道门 + 对抗复核。

## 4. D 批验证序列（B/C 落地后执行）
1. `python pipeline/cli.py loop --expect-s2 <新读数> --expect-errors <新读数> --expect-l1 <新读数>`
   （恒红门禁 codegen all→compile_regression / match L1 会被显式标 TOLERATED）。
2. C1003 截断单元按"列表内最大行号"判（现基线：CCBStage.cpp 3824 / free_functions.cpp 2874）。
3. 三基线刷新决策：compile_baseline --update-baseline（用户确认）；baselines/latest 随 probe；
   s4 L1 棘轮只升不降。
4. 知识回写：gotcha_emitted_layout_drifts_from_annotated_offsets 的 101/169 量化更正
   （现 1/167）；本对账方法（时序陈旧≠矛盾、逐单元增退闭合）入库。
5. §3 的 2 单元：修复（推荐 (a)）或显式 deferred 记录 + 理由。

## 5. 当前普查快照（2026-09-27 12:51）
S2 92/208 · 总错误 1796 · C1003 截断 2 单元（CCBStage.cpp max 3824 / free_functions.cpp max 2874）。
