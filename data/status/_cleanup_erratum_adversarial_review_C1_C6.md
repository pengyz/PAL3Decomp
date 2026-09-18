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