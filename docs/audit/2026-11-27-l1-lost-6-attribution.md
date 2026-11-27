# 12:08 丢失的 6 个 L1 函数逐条归因（#60，只读）

数据来源：`data/status/archive/r7_t6_skillui_match_final_20261127.log:195-205` 记 `[L1 ratchet] previous 198 -> current 192`、
LOST 6 条、新增 L1 0 条、population `matched=1194/1309 -> 1140/1253`。
本文只回答「这 6 个 VA 为什么不再进 L1」，不改任何注解/代码/基线，不跑管线。

## 一、逐条结论表

命令与输出都取自工作树现况（census `generated_at=2026-11-27T18:38:36`；baseline 工作树与 HEAD 两版）。

| # | VA | 名字（原函数） | size | 我们的树发射符号？ | 进比对了？ | 裁决 | 依据（可复跑） |
|---|----|---------------|------|------------------|-----------|------|----------------|
| 1 | `0x004431b0` | CCBPanelSlot::\`scalar deleting destructor'(uint) | 30 | **否**（连完整析构体都没发射） | 否 | **真退化（可修）**，修在**注解层 methods** | `grep -rn 'CCBPanelSlot::~' pal3/src` = **0 行**；`CCBPanelSlot.h:41` 只有 `virtual ~CCBPanelSlot();` 声明；`data/annotations/structs/CCBPanelSlot.json` 的 methods 只有 `0x00443200 Render / 0x00442ff0 Update_2ff0 / 0x00442420 HideAll / 0x004431b0 ~CCBPanelSlot[dtor,deleting]`，**缺完整析构 `0x004431d0`**。反汇编证明它存在：`data/status/_disasm_cache.txt` `4431b0: push esi / mov esi,ecx / call 0x4431d0 / test BYTE PTR [esp+0x8],0x1 / je / push esi / call 0x541d10 / ret 4`（??_G 调完整析构 + operator delete）；`4431d0: mov DWORD PTR [ecx],0x56ae2c / jmp 0x442e80`（写本类 vptr 后跳基类析构）。没有完整析构体，MSVC 不会生成 ??_G ⇒ 该符号在我们产物中不存在 |
| 2 | `0x00449b90` | CCBUIPanel::FocusCurrentRole(void) | 66 | 是（`pal3/src/Misc/CCBUIPanel.cpp:2019` `char CCBUIPanel::FocusCurrentRole()`） | 否——单元**编译失败** | **真退化（可修）**，修在**注解/编译错误层** | census（18:38:36）`pal3/src/Misc/CCBUIPanel.cpp` = `fail`，4 条错误：`C2440 L2434 '=' cannot convert from 'const int' to 'int *'`、`C2065 L2450 'off_56B22C' undeclared identifier`、`C2440 L2477`、`C2440 L2522`。单元失败 ⇒ 不产出 obj ⇒ 我方无该符号可对 |
| 3 | `0x00449980` | CCBUIPanel::SetUserData(int) | 13 | 是（`CCBUIPanel.cpp:1964` `void CCBUIPanel::SetUserData(int nVal1)`） | 同上（单元 fail） | **真退化（可修）**，同上 | 见附录 A3（定义行 grep + census 该单元 4 条错误原文） |
| 4 | `0x004461d0` | CCBUIPanel::\`scalar deleting destructor'(uint) | 30 | 是（完整析构 `CCBUIPanel.cpp:56` `CCBUIPanel::~CCBUIPanel()`，删除式伴生随之生成） | 同上（单元 fail） | **真退化（可修）**，同上 | 见附录 A4（完整析构定义行 + census 原文） |
| 5 | `0x004538d0` | UIPushButton::IsHidden(void) | 11 | 是（`pal3/src/Misc/UIPushButton.cpp:739` `BOOL UIPushButton::IsHidden()`） | 否——单元**编译失败** | **真退化（可修）**，修在**签名注解层** | census：`pal3/src/Misc/UIPushButton.cpp` = `fail`，4 条 `C2660 L656/664/677/685 'UIInitSystem' : function does not take 5 parameters` ⇒ 单元失败、无 obj |
| 6 | `0x004407a0` | UIPushButton::\`scalar deleting destructor'(uint) | 30 | 是（完整析构 `UIPushButton.cpp:126` `UIPushButton::~UIPushButton()`） | 同上（单元 fail） | **真退化（可修）**，同上 | 见附录 A6（完整析构定义行 + census 原文） |

### 为什么「没进比对」不是「名字不匹配」

`match` 的 unmatched 是「原件有、我方无该符号」这一桶：第 1 条是我们**根本没发射**；第 2–6 条是所在单元**编译失败不产出 obj**，
整个单元的所有符号都不参与比对（不是逐符号名字/大小不符）。可用 `data/status/s4_diff_detail.json` 交叉验证：
`CCBPanelSlot.cpp` 只有 2 条 partial 记录（`Update_2ff0@0x00442ff0`、另一条），不含 `0x004431b0`；
`CCBUIPanel.cpp`/`UIPushButton.cpp` 整个不在 `units` 字典里（只有 150 个单元有比对记录）。

### baseline rows 口径核对（QA 第 3 条）

```
$ python3 -c "...rows_vas = {r['va'] for r in json.load(s4_baseline)['rows']}..."
工作树 present in rows: []
HEAD     present in rows: []
工作树 stats（同一次读取，mtime 2026-11-27 18:43:08）: symbols 1282 / matched 1161 / match_L1 196 / partial 827 / rows 1023
HEAD   stats: symbols 1259 / matched 1152 / match_L1 189 / partial 827 / rows 1016
```
两条口径说明：
- 两版 rows（工作树 1023 条、HEAD 1016 条）都不含这 6 个 VA——rows 只收录 partial 与 L1，符号缺席与本文结论一致。
- 「symbols 1253 / matched 1140 / match_L1 192 / partial 812」是 #63 落地前（18:12:32 那轮 census + 12:20 那轮 match）的快照，
  18:43:08 该文件已被后续 match 重写为 196/1161/1282/827（仍无 rebaseline 键）。本文只陈述「缺这 6 个 VA」这一不随快照变化的结论。

## 二、机制：为什么这 6 个会同时丢（≤20 行）

1. 两类原因，互不相干：
   - **注解漏一条完整析构**（第 1 条）：`CCBPanelSlot.json` 只标注了删除式析构 `0x004431b0`，没标注完整析构 `0x004431d0`。
     codegen 据此只发射 `virtual ~CCBPanelSlot();` 声明、不发射函数体 ⇒ MSVC 不生成 ??_G ⇒ 符号从未存在。
     这一类是**长期缺口**，不是 12:08 才有。
   - **两个单元编译失败**（第 2–6 条）：`CCBUIPanel.cpp`（C2440×3 + C2065 `off_56B22C`）与 `UIPushButton.cpp`
     （C2660 `UIInitSystem` 5 参 ×4）在归档 census（2026-11-26 起多份 `data/status/archive/probe_census_after_*.json`）里已是 fail。
     单元 fail ⇒ 无 obj ⇒ 该单元全部符号退出比对。
2. 12:08 的 `198→192` 之所以把这 6 条记为「LOST」，是因为**上一版 baseline 的 L1 集合**（人口 1194/1309）里它们还在，
   而本轮人口是 1140/1253（12:08 当轮口径，非当前值）——棘轮日志自己打印了「可比总体已变化」。也就是说 −6 里真正新发生的是
   「两个单元已经坏掉、符号退出比对」这件事被本轮棘轮显影，而不是本轮改动打坏了这 6 个函数。
3. 结论口径：6 条都是**可修的真退化**（注解层/签名层），没有一条属于「预期变更（设计决策让它消失）」。

## 三、推荐的修复卡范围（建议，不落地）

1. **注解补完整析构（1 条，A 级证据已备）**：`data/annotations/structs/CCBPanelSlot.json` methods 增加
   `0x004431d0`：`name=~CCBPanelSlot`、`flags=["dtor"]`、`sig_model={return:void, cc:thiscall, params:[], varargs:false}`；
   依据：`4431d0: mov DWORD PTR [ecx],0x56ae2c / jmp 0x442e80` + `4431b0` 调它 + vtable `0x56ae2c` slot5=0x004431b0。
   预期效果：`??1CCBPanelSlot`/`??_GCCBPanelSlot` 成对出现（`s4_baseline.json` 的 `stats.carrier.unpaired_syms` 里 `??1CCBPanelSlot@@UAE@XZ` 与 `??_GCCBPanelSlot@@UAEPAXI@Z` 都在未配对名单，已是现状）。
2. **修 CCBUIPanel.cpp 的 4 条编译错误**（另卡，属注解/签名层）：
   - `C2440 L2434/2477/2522 '=' cannot convert from 'const int' to 'int *'`：同一族，先看是不是某个成员被标成 `int *` 而原值是常量；
   - `C2065 L2450 'off_56B22C'`：全局/偏移未声明（全局注解或 codegen extern 缺口）。
3. **修 UIPushButton.cpp 的 C2660**（另卡，属签名层）：`UIInitSystem` 调用点传 5 参、但声明形只收更少参数，
   需按调用点实参 + 函数体重定 sig_model（不是加 varargs 糊过去）。
4. 顺序建议：先 1（最小、A 级、只动一条 methods）→ 跑一次 match 看 `0x004431b0` 是否回到 L1；
   再 2/3（各自动对应单元）→ 每修好一个单元，其符号整体回到比对，L1 的增量应按单元粒度记账。
5. 不建议把这条 6 个 VA 的恢复塞进任何单点热修：2–6 条的根因是两个单元各自的注解错误，混在一起会让「修好了没有」不可判。

## 附：本文用到的命令（全部只读，可复跑）

```bash
grep -rn --include=*.cpp --include=*.h 'CCBPanelSlot::~' pal3/src | wc -l          # 0
grep -n '~CCBPanelSlot' pal3/src/Misc/CCBPanelSlot.h                              # :41 只有声明
grep -n '^char CCBUIPanel::FocusCurrentRole\|^void CCBUIPanel::SetUserData\|^CCBUIPanel::~' pal3/src/Misc/CCBUIPanel.cpp
grep -n '^BOOL UIPushButton::IsHidden\|^UIPushButton::~' pal3/src/Misc/UIPushButton.cpp
python3 - <<'EOF'   # 单元状态与错误（读 data/status/probe_census.json 的 s2.results）
...
EOF
python3 - <<'EOF'   # baseline rows 缺 6 VA（工作树 + HEAD 两版）
...
EOF
sed -n '89690,89755p' data/status/_disasm_cache.txt                                # 0x443190..0x4431db
```

## 附录：逐行命令与原始输出（QA 第 1 条「每项带命令与输出」）

单元状态统一取 `data/status/probe_census.json`（`generated_at=2026-11-27T18:38:36`），读法：

```bash
python3 - <<'PY'
import json
s2=json.load(open('data/status/probe_census.json'))['s2']
for r in s2['results']:
    if r['unit'] in ('pal3/src/Misc/CCBUIPanel.cpp','pal3/src/Misc/UIPushButton.cpp','pal3/src/Misc/CCBPanelSlot.cpp'):
        print(r['unit'], r['status'], len(r['errors']))
        for e in r['errors']: print('   ', e['line'], e['code'], e['msg'])
PY
```

原始输出：

```
pal3/src/Misc/CCBPanelSlot.cpp ok 0
pal3/src/Misc/CCBUIPanel.cpp fail 4
    2434 C2440 '=' : cannot convert from 'const int' to 'int *'
    2450 C2065 'off_56B22C' : undeclared identifier
    2477 C2440 '=' : cannot convert from 'const int' to 'int *'
    2522 C2440 '=' : cannot convert from 'const int' to 'int *'
pal3/src/Misc/UIPushButton.cpp fail 4
    656 C2660 'UIInitSystem' : function does not take 5 parameters
    664 C2660 'UIInitSystem' : function does not take 5 parameters
    677 C2660 'UIInitSystem' : function does not take 5 parameters
    685 C2660 'UIInitSystem' : function does not take 5 parameters
```

### A2 `0x00449b90` FocusCurrentRole（66B）

```bash
$ grep -n '^char CCBUIPanel::FocusCurrentRole' pal3/src/Misc/CCBUIPanel.cpp
2019:char CCBUIPanel::FocusCurrentRole()
```
→ 符号已发射；所在单元 `pal3/src/Misc/CCBUIPanel.cpp` = fail（上面 4 条错误）⇒ 无 obj、不进比对。

### A3 `0x00449980` SetUserData（13B）

```bash
$ grep -n '^void CCBUIPanel::SetUserData' pal3/src/Misc/CCBUIPanel.cpp
1964:void CCBUIPanel::SetUserData(int nVal1)
```
→ 已发射；同一单元 fail（同上 4 条）⇒ 不进比对。

### A4 `0x004461d0` CCBUIPanel::??_G（30B，删除式 dl）

```bash
$ grep -n '^CCBUIPanel::~' pal3/src/Misc/CCBUIPanel.cpp
56:CCBUIPanel::~CCBUIPanel()
```
→ 完整析构已发射（??_G 由它派生）；但单元 fail ⇒ 两者都不进比对。

### A5 `0x004538d0` IsHidden（11B）

```bash
$ grep -n '^BOOL UIPushButton::IsHidden' pal3/src/Misc/UIPushButton.cpp
739:BOOL UIPushButton::IsHidden()
```
→ 已发射；单元 `pal3/src/Misc/UIPushButton.cpp` = fail（上面 4 条 C2660）⇒ 不进比对。

### A6 `0x004407a0` UIPushButton::??_G（30B，删除式 dl）

```bash
$ grep -n '^UIPushButton::~' pal3/src/Misc/UIPushButton.cpp
126:UIPushButton::~UIPushButton()
```
→ 完整析构已发射（??_G 由它派生）；单元 fail ⇒ 不进比对。
