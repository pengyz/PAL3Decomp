# 勘误：对抗性复核（内部子 agent `bc0a67e9`）抓出我 2 条核心主张被证伪

**日期**：2026-09-17 · 复核者：内部 dsh 子 agent `bc0a67e9-b412-4c91-980f-a6a9bac1030b`
全文：`/tmp/independent_review_C1_C6.md` · **本文件只做撤回与更正，不辩解**

---

## 0. 一句话结论

**`sizeof(UIProgressBar)=308` 是错的（真值 244）**，我据此写的"27 个 overlap 是注解错、
244 是同源传播错误值"整段**撤回**；**"刷新基线后门禁通过"是恒真式，撤回**。
C3（Δ=0）降级为**无法判定**；C4 结论成立但机制与修法写错；C2 结论保留、论证重写。

## 1. ❌ 撤回：`sizeof(UIProgressBar)=308`（C1 证伪）

**我错在哪**：我用 `UIProgressBar.json` **自己的** `vtables` 字段（声明 `0x0056AC20` 属于
UIProgressBar）去锚定 `0x439030` 是该类的 ctor —— **用注解验证注解，循环论证**。

**复核者证据 + 我的独立复核**（都已亲自跑过）：

| 检查 | 结果 |
|---|---|
| `pal3/src/Misc/UI3DCtrl.h:37` | **`// total size: 0x134 (308)`** |
| vtable `0x56ac20` 的 slot1 = `0x439410` 体内访问的 `%esi` 偏移 | `0x124` `0x58` `0xe8` `0xf8` `0x100` `0x104` `0x108` `0x10c` `0x110` `0x114` `0x118` `0x11c` `0x44` |
| `UI3DCtrl.h:35` | `gbCamera * m_camera; // +0x124` ⇒ **这些偏移全是 UI3DCtrl 的成员** |
| `UILoadingFrm::InitFullScreen` 里 `m_LoadProgress` 的真实构造 | `450732 lea 0x48(%esi),%ecx` → **`45073d call 0x43f7f0`**（**不是** `0x439030`）|
| PDB（复核者引）| `UIProgressBar length=0xf4`(244)、`UI3DCtrl length=0x134`(308) |

⇒ `0x439030` 是 **`UI3DCtrl::ctor`**，308 是 **UI3DCtrl** 的尺寸。
**`UIProgressBar` = 244**，与注解、与 `UILoadingFrm.m_LoadProgress(+72)` 的下一成员
`m_anitime(+316)` 的槽位算术一致。

**连带的两个更正**：
1. 我测到的"5 处连续 ctor 位移 308"全部是 **UI3DCtrl** 对象 ⇒ 与 UIProgressBar 无关。
2. **"改 308 会级联 27 个 overlap"那个信号是^^^^对的** —— 它正是在告诉我 308 错了；
   我却把它解释成"那批注解错"。**这是口径切换**（复核者点名）。
3. `JusticeBookUI` 的 368 我写成"两成员间可有空隙"（最弱解释）——实际是
   `0x778` + **308**(=UI3DCtrl) 后紧跟一个 **5×12=60B** 成员到 `0x8e8` ⇒ 368 **不是尺寸**，
   但 **308 是精确上界**。我的解释方式错，结论方向偶然对。

**要改的文件**：
- `_cleanup_correction_misattribution_scan_v2.md` §10（308 与 27-overlap 的豁免）→ 已加撤回横幅
- `_cleanup_landing_uiwnd_3methods.md` §4（308）→ 已加撤回横幅

## 2. ❌ 撤回："门禁恢复绿色"（C6 证伪，且这条最该先测）

复核者读码 + **注入实验**证明：

- `tools/regression_detector.py --check` **只读 census + baseline，不编译**；
- 刷新基线后 `latest.json` 的内容 == `extract_results(probe_census.json)`
  ⇒ `0/0/0` 是**恒真式**，不构成任何验证；
- **同轮 A-B-A 注入**：向当时 ok 的 `pal3/src/UI/UINote.cpp` 注入
  `void _c6_injected(void){int x=0;x="not_an_int";}` → `probe_compile` 报 `L65 C2440`，
  而**带着这个错误**跑 `--check` 仍报 `新失败0/新错误0/未检测到回归/exit 0`。
  （已还原，sha256 一致。）

**两处盲区**（读码 + 内存模拟）：
1. 只存在于一侧的单元被 `continue` 跳过（`regression_detector.py:188`）
   ⇒ 基线外的**新失败单元永不报**。数据上真实发生：4 个 `AStarPathFinder__*` 单元
   全 fail、共 **50 错**被静默忽略。
2. `new_errors` 只比错误**数量**（按后缀切片）⇒ 同数不同码不可见
   （模拟 `UIDialog` 1×C2059 → 1×C9999 ⇒ 报 0）。

**对照组**（说明门禁并非完全无用）：向基线内**已存在**的 ok 单元注入新失败 ⇒
`new_failures=1` ✓。

⇒ `_cleanup_fix_globals_const.md` §4 的"刷新后 `--check` 为 新失败0/新错误0"**不能作为
"门禁通过"**，只说明"我没在它眼皮底下改 census"。**已加撤回横幅。**

## 3. ⚠️ 降级：`Δok/L1=0`（C3 无法判定）

复核者证明：`data/status/probe_census.json` **未被 git 跟踪**（`.gitignore`），
现在只剩一份 `generated_at 2026-09-17T20:10:43`；`s4_baseline.json` **没被这三个 commit
更新过**（我引用的 `L1 17` 是**继承值**，不是本次测量）。

**能支持的只有"窗口总 Δ"**：唯一一份已提交、带时间戳的独立运行记录
（`bdecb45b9` 17:14 的 kiro 复核）记 `s2.ok=61/202、matched=191/218、L1 17`，
而三次改动提交于 19:08/20:06/20:16 ⇒ 与"窗口内总 Δ=0"相容；
**"每条各自 Δ0"不可判定**（同窗口、无单次前后测量，且生成树未归档）。

另：**S2 单元集合不恒定** —— `git show 00293e8e1^:data/status/baselines/latest.json`
= **198** units（142 fail/56 ok），现 **202**。我写的"都是 202"只在本次窗口成立。
⇒ 以后所有 Δ 声明必须写成 **"窗口总 Δ"** 并附两次 `generated_at` 与单元集合 diff。

## 4. ⚠️ 更正：C4 的机制句与候选修法 B 都错

复核者合成 TU 逐级比**错误码**（在 `/tmp`，未写 `pal3/src`）：
- V1（8 个 include，去 `free_functions.h`）⇒ **ok**
- V2（9 个）⇒ 唯一 `C2059 syntax error ')'` ✓（= 我文件里的码）
- V3（`free_functions.h` 放最前）⇒ `C2373 'RoleCameraCtrl' : redefinition` + C2146 + C1004 ⇒ **同源成立**
- **V4（去掉限定符 `((RoleCameraCtrl*)&this[1])->SetTargetDistance(2)`）⇒ 仍然 C2059**
- **V5/V6（`((class RoleCameraCtrl*)…)`）⇒ ok**

⇒ **真正被误解析的是 cast 里的类型名**（`(RoleCameraCtrl *)` 中的 `RoleCameraCtrl`
被当成函数），**不是"函数::成员"**。我文档 §4 的**候选 B（省略限定符）实测无效**，
应改为 **候选 B′：把 cast 写成 elaborated type specifier `(class RoleCameraCtrl *)`**。
候选 A（改名）仍可行，但"是否在 `symbols=218`"**不能从 `s4_baseline` 判定**（该产物无名单），
须查 `pipeline/compare_pal3.py`。

另：我写的"881 个类名"**复核者复算不出**（`pal3/src`=742、加 `include/`=871）——口径未披露。

## 5. ⚠️ 补口径：C5(a) 的"75→0"偏窄

复核者自写正则确认 `->(Ident::){2,}Ident(` = **0** ✓，但发现**同源残形**且确实报错：
`pal3/src/Misc/UISceneMap.cpp:153  (((string *)p_bottom))->string::_init_4530c0(arg0);`
（**单段限定 + cast 退化**，该单元 4 错含 2×C2039）。
⇒ 我的 75→0 只覆盖"≥2 段限定"，**单段限定在 cast 退化时同样非法**，待扩口径。
C5(b)（`const` 一致性 45→0、反向 0）**证实**。

## 6. C2：结论保留，论证必须重写

- ✅ `sizeof(UIWnd)=68` 可信 ⇒ 三者写 +140/144/148 **不可能属 UIWnd**；
- ✅ 59 个调用点（19 组）**全部**是同一对象调同一族 setter，**无反例**；
- ⚠️ **但**：我引用的 `UILoadingFrm+0x48` 是 `0x43F7F0` 构造的，而
  `UIButton.json` 又声称 `0x43F7F0` 是它的 ctor —— **与 `UIProgressBar.json` 自己的
  ctor 归属直接冲突**，我**未披露**；
- ⚠️ `gbColorQuad.binary_size = 4` ⇒ 4B float 写到 +144/+148 **尺寸相容**
  （只有 +140 的 `BYTE` 会溢出到 padding）⇒ 我"归属与成员类型至少一个错"在**布局层面不成立**；
- ⇒ 迁移**目标**正确（PDB：+0x8c/0x90/0x94 = `m_rradius/m_tradius/m_bradius`，
  且有 `SetRRadius/SetTRadius/SetBRadius`），但那个 commit 把**属 vtable-0x56ad64 类**的方法
  写进了 `UIProgressBar.json` —— 而该文件的 `vtables/ctor/Render/CheckRayHitRole/Destroy`
  全是 **UI3DCtrl** 的 `0x56ac20` ⇒ **该文件混了两个类**。

## 7. 复核确认可用的部分（保留）
- `tools/annotation_diff.py` 的 `methods` 修复**可用**（复核者内存构造验证：methods 增/删/改 +
  `base_class` + 未知新字段全检出；12 个官方用例全过）；
- C4 的**结论**（同名冲突、正好 2 个、影响 3 文件/错误数）**可用**，机制与修法按 §4 更正；
- C5(b) 可用；C5(a) 可用但口径要扩；
- 我主动披露的 5 条弱点里 **1/2/5 成立**（跨运行拼接、程序序假设、基线掩盖）；
  第 4 条（`_inline_` 10 个错误）复核者复算**准确**。

## 8. 下一步（复核者建议 + 我的排序）
1. **vtable ↔ 类 全局对账（只读）**：对每个 vtable slot 的函数体做
   `objdump -d … | grep -oE '0x[0-9a-f]+\(%esi\)' | sort | uniq -c`，与所属注解类的成员偏移求交。
   **已知 3 处错映射**：`0x56ac20 → UI3DCtrl`（现挂 `UIProgressBar.json`）、
   `0x56ad64 → UIProgressBar`（现挂 `UIButton.json`）、`0x56acfc → ?`（现挂 `UI3DCtrl.json`）。
2. 按 A 级证据修这 3 份注解的 `vtables`/`methods`，再 `check` + `audit_layout`；
   之后才谈 UIWnd 三方法的迁移与尺寸。
3. **门禁三修**：单侧单元不跳过、比 `(code,line)` 多重集、`--check` 断言
   `latest != extract(census)`；回归用例：注入 `UINote.cpp` 一行 → `probe s2` → `--check` 必须 exit 1。
4. C3 改成"窗口总 Δ"口径，并把 `probe_census.json` 随 commit 归档（或纳入 git）。
5. C4 落地前查 `pipeline/compare_pal3.py` 的 218 symbols 是否含 `?RoleCameraCtrl@@YAXXZ`；
   优先采用 `(class RoleCameraCtrl *)`。
---

# 第二轮追加（复核者 `bc0a67e9` 追加复核，2026-09-17）

## 9. ✅ 已执行：pre-state 产物入仓
复核者穷尽搜索发现**唯一**的改前产物集在 `/tmp/c2660bak/`（易失），已归档：
`data/status/archive/20260917_1549/`（生成树 tar.gz + 15:49 census + 15:52/17:22 两份 s4 +
`latest.json` + registry，含 README）。**以后每条主张都能做真正的 A-B-A。**

## 10. C3 从"无法判定"上调为"高度证实（残留一处文档依赖）"
- **L1 分量：产物级证实 ΔL1=0。** 改前侧 = `76349df80`(16:50) 提交的 `s4_baseline.json`
  （`L1 17 · matched 191/218 · symbols 218`，17:22 有同内容产物）；改后侧
  `data/status/s4_baseline.json`（mtime 20:14:17）**是一次真跑** —— 同一次跑重写的
  `pal3_registry.jsonl` 从 133 行→166 行，且内部自洽（`17+149+25=191 matched`）。
- **ok 分量：窗口级 + 受影响单元级证实。** 15:49 与 20:10 两份 census 的
  **S2 单元集合完全相同（202/202）**、S1 亦相同（751/751）⇒ 跨运行口径成立：
  `ok 56→61`，`fail→ok` 5 个、**`ok→fail` 0 个**，总错误 3817→3572；5 个 flip 全落在
  16:30/16:50 两个已记录 commit 上。
- **对 `2b94ce769` 的受影响 8 单元逐个比对：状态全不变**
  （`CJ_FindFile ok(0)→ok(0)`、`UILoadingFrm fail(1)→fail(1)`、`UIProgressBar fail(20)→20`、
  `StateUI 52→37`、`CCBMagicWindow 32→32`、`UITitle_XJTM 20→19`、`UIBigMap 53→44`、
  `free_functions 101→102`），并用**快照树独立重编译**了唯一 ok 的那个（两侧 0 错）。
- 残留：**"每条 commit 各自的 Δok"仍无逐次测量**（kiro 17:14 的 61 只是文档、非产物）。
⇒ 我的写法应固定为 **"窗口总 Δ=0（L1 产物级、ok 窗口级+受影响单元级）"**。

## 11. C2 的**落地**已有产物级验证（错的只是论证）
`diff` 15:49 快照 vs 当前：`UI/UIWnd.h` **只删了 3 行**、`Misc/UIProgressBar.h` **只加了 3 行**；
调用点 cast 随方法所属类改写（`->UIWnd::GetHeight(9)` → `->UIProgressBar::GetHeight(9)`），
并删了一行 `#include "UI/UIWnd.h"`。**改动面与文档描述一致、受影响单元状态不变**
⇒ "迁出 UIWnd + 目标类 UIProgressBar + Δ0" 在**落地层面成立**；错的仅是 justify 用的 308。

## 12. C5 的"改前"侧现在有产物数字
- (a) 15:49 快照 `->(Ident::){2,}Ident(` = **68**（`_Tidy 36 / _Eos 11 / do_always_noconv 11 /
  _Split 6 / _Freeze 3 / _Grow 1`；`~string` = 0），与 commit 自报 75 的**5/6 分项完全一致**
  （`_Split` 6 vs 10；`~string` 0 vs 3 属 15:49→20:06 漂移）；当前 = **0** ✓
  ⇒ 方向与量级证实，**精确 75 不可复算**（我原文已如实标注）。
- (b) 15:49 快照 const 不一致 = **46**（483 对可比），**全部是"声明 const/定义非 const"、反向 0**；
  当前 = **0**（512 对）⇒ "45→0" 证实到 **±1**、方向完全一致。

## 13. C4 最后一个风险关闭 + **我的一处口径澄清 + 复核者一处路径错误**
- ✅ **符号风险不存在**：`symbols=218` 来自"对每个 S2-passing 的 .cpp 编译并读 COFF 符号表"，
  而 `void RoleCameraCtrl()` 只在 `pal3/src/free_functions.cpp`（**fail, 102 错**）里
  ⇒ **不可能在 218 里**；全树仅**定义 1 处、调用点 0 处**。**改名可安全进行。**
- ⚠️ **复核者 §4 有一处路径错误，我不接受该指控**：它称
  "`pal3/src/Script/ScriptVM.cpp` 在树里不存在 ⇒ 文档里 `FightInfo` 的 4 个调用点说法是错的"。
  实测：`pal3/src/Script/ScriptVM.cpp` 确实不存在，但**我文档引用的是
  `pal3/src/Misc/ScriptVM.cpp`（该文件存在）**，其 `443/963/1318/1494` **确为 `FightInfo();` 调用点**
  （且第 10 行 `#include "Misc/FightInfo.h"`）。复核者另说的"CCBSystem/CCBRoleState/CCBStage/
  CCBStageScene 里约 10 处**类型用法**"**也对**——两者并存（调用点 + 类型用法）。
  ⇒ 正确表述：**改名需同时处理 `Misc/ScriptVM.cpp` 的 4 个调用点**（复核者漏了它们）。

## 14. C6 的精确措辞（避免夸大）
15:49→20:10 窗口内错误计数**非单调**：`PAL_GDB 33→52`、`SoundSystem 1→7`、
`CEffMgr 10→14`、`GeomNode 2→3`。其中**只有 `PAL_GDB` 相对 Sep-15 基线是新增**；
另三个是相对**中间态**上升 ⇒ **不能**说成"相对刷新基线未披露的回归"。
准确版本：**刷新所吸收的"现状"本身包含若干错误增长，其来源落在 13 个 commit 的窗口内、
无法归因到单条 commit；而门禁对它们一律无感（刷新后即成为基线）。**

## 15. 建议动作（第二轮）
1. ✅ **已完成**：`/tmp/c2660bak/` 入仓 `data/status/archive/20260917_1549/`。
2. **`probe_census.json` 随 commit 归档**（`probe_census_<rev>.json`），否则"Δok"永远靠文档。
3. 其余同第一轮：vtable↔类对账（3 处已知错映射）· 门禁三修 · 撤回 308（已做）·
   C4 落地用 `(class RoleCameraCtrl *)`。
