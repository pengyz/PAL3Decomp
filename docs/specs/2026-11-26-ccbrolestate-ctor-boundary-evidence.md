# CCBRoleState ctor 写界取证（R6 ⑤，P0）

> 只读取证。本文件是 `tsk_01M8CADS47F7XPAYVYGK37` 的唯一交付件；未改 `data/annotations`、`pal3/src`、`pipeline`、`tests`、任何基线，未跑 `apply/export/codegen/probe/loop`。
> 证据源：`original/PAL3.exe`、`data/status/_disasm_cache.txt`、`asm/pal3/ida_structs.json`、`data/annotations/structs/CCBRoleState.json`、`data/status/probe_heap_alloc_census_20261126.json`、`docs/audit/2026-11-26-r6-decision-brief.md`。

## 0. 结论

1. **ctor 不越界。** `0x44c5f3` 的 `push 0x5058`（20,568）→ `operator new` → `0x44c60e call 0x456ab0`，该 ctor 的最远写入是 `0x456b2a mov DWORD PTR [esi+0x5054],edi`，写入终点 `0x5054+4=0x5058`，与分配尺寸**逐字节相等**。
2. **`binary_size=22,224` 没有二进制支撑。** 全库无 `push 0x56d0`（22,224）分配；22,224 是注解 89 员末端的算术值，IDB 的 size 只是照抄注解。
3. **尾部 23 个成员跨类混装**（这是「越界」假象的真正来源）：`0x5060..0x50A0` 属另一个 20,644B 类的对象；`0x55C8..0x55D0` 全库零访问；`0x5654..0x565C` 属 `CCBUIPanel`（22,112B）；`0x56CC` 属 `PropUI`（29,056B）。
4. **定谳：伪命题（B 级）**——不是 ctor 写错、也不是 CCBRoleState 尺寸偏小，而是注解成员表把三个别的类拼进了 CCBRoleState。第一遍 loop 把 20,568「回退成 22,224」是注解自洽性拦截，不是二进制要求。
5. **影响**：`binary_size` 应为 **20,568 (0x5058)**；删/移 23 个尾部成员后，census 洞至少减少 **1,568B**（`0x5058` 之后的全部洞）。

## 1. 原始命题（#17 决策简报原文）

`docs/audit/2026-11-26-r6-decision-brief.md:139`：

> `??0CCBRoleState` 的分配 20,568 与注解成员写至 0x56cc（末端 22,224）互斥——是 ctor 名义误挂到另一个类，还是 0x55c8..0x56cc 段成员越界；`ClearAndSetGP` 的 20,644 是 self-new 还是工厂。

同文 `:145-149` 的数字与等级：

| 数字 | 出处 | 等级（简报自评） |
|---|---|---|
| `binary_size=22,224`；89 员；`bases=[UIListBox@0]`；`m_BattleFlags@0x56cc` 末端 `0x56d0=22,224` | `CCBRoleState.json`（mtime 11-26 01:00） | 注解，B |
| ctor 20,568=0x5058，site `0x44c5f8`，caller `CreateSettingsUI@UIScenePanel` | `probe_heap_alloc_census`；`_gold:15` | A（分配行） |
| `ClearAndSetGP` 20,644=0x50A4，site `0x512730`，store `esi+0x10`，caller `ProcNormalAttack@CCBSystem` | 同上 | A（分配行，self/工厂未辨） |
| 22,224−20,568=1,656；22,224−20,644=1,580 | 简报算术 | A（算术） |
| 第一遍 loop 已把 20,568 回退为 22,224（成员末端越界触发拦截） | `_gold:44-47` | 现场记录，A（已发生） |
| 洞 6,483B/27 | `struct_holes` | 普查，B |

**哪些是实测**：两条分配行、两个 site、算术、回退事件。
**哪些是推断**：「ctor 越界」与「成员越界」是二选一的假设，简报未做 ctor 体内逐笔写入核对——这正是本卡补的部分。

## 2. ctor 写界（逐笔）

### 2.1 入口清单

| 入口 | VA | 说明 | 写界 |
|---|---|---|---|
| `??0CCBRoleState` | `0x456ab0` | 唯一调用点 `0x44c60e`（见 §2.2）；函数体 `0x456ab0..0x456b58` | **最大 `0x5054`（+4B = `0x5058`）** |
| 构造后初始化 | `0x456c20` | ctor 返回后由 `0x44c627` 立即调用（`mov ecx,eax`，同一对象） | 最大 `0x5054`（`0x456c65`），同样止于 `0x5058` |
| 析构 | `0x456b60`（deleting）/`0x456b80`（complete） | 只写 vptr/栈槽，无对象尾写 | ≤`0x20` |
| `ClearAndSetGP` | `0x4ec680` | **不是本类 ctor**：它先把 `ecx` 当 `this`，`rep stos` 清零 **0x1429 dword = 0x50A4 = 20,644B**，不写 vptr | `0x210`（+2 个字段） |
| 派生类 ctor | 无 | `ida_structs.json` 中 `bases` 含 `CCBRoleState` 的类为 0（只有 9 处 `CCBRoleState *` 指针成员） | — |

### 2.2 分配链（A 级）

`data/status/_disasm_cache.txt:101376-101384`：

```
44c5f3: 68 58 50 00 00        push   0x5058
44c5f8: e8 3e 6f 10 00        call   0x55353b          ; operator new
44c60c: 8b c8                 mov    ecx,eax
44c60e: e8 9d a4 00 00        call   0x456ab0          ; ??0CCBRoleState
44c621: 89 86 20 36 00 00     mov    DWORD PTR [esi+0x3620],eax   ; 存 UIScenePanel+0x3620
```

`push 0x5058` 全库仅此一处（`grep -nE "push\s+0x5058\b"` 命中 1 行）。

### 2.3 ctor 体内全部对象写入（`0x456ab0..0x456b58`）

| VA | 指令原文 | 目标（相对 this） | 宽度 | 归属 |
|---|---|---|---|---|
| `0x456ace` | `call 0x43dcd0` | 基类 `UIListBox` ctor（`this+0`） | — | 基类区（0..0x48） |
| `0x456adf` | `call 0x4422e0`（`ecx=[esi+0x168]`） | `0x168` | 152B 子对象 | 内嵌 `UIFrameContainer` |
| `0x456ae4`/`0x456ae9`/`0x456aee`/`0x456af6`/`0x456afb` | `push 0x43b4d0; push 0x43b3e0; push 0x34; push 0x178; push eax(=esi+0x200)` | `0x200` 起 | `0x178 × 0x34 = 0x4C60` | 内嵌数组，止于 `0x4E60` |
| `0x456b01` | `call 0x553627` | 数组构造器 | — | 同上 |
| `0x456b11` | `call 0x43a770`（`ecx=[esi+0x4e60]`） | `0x4E60` | 0x158 子对象（到 `0x4FB8`） | 内嵌对象 |
| `0x456b21` | `call 0x4422e0`（`ecx=[esi+0x4fb8]`） | `0x4FB8` | 152B 子对象（到 `0x5050`） | 内嵌 `UIFrameContainer` |
| `0x456b2a` | `89 be 54 50 00 00  mov DWORD PTR [esi+0x5054],edi` | `0x5054` | 4B | **最远写入** |
| `0x456b30` | `89 7e 4c  mov DWORD PTR [esi+0x4c],edi` | `0x4C` | 4B | 自有成员 |
| `0x456b33` | `89 7e 48  mov DWORD PTR [esi+0x48],edi` | `0x48` | 4B | 自有成员 |
| `0x456b36` | `c7 06 64 b3 56 00  mov DWORD PTR [esi],0x56b364` | `0x0` | 4B | vptr（CCBRoleState 表） |
| `0x456b3c` | `c7 46 50 20 03 00 00  mov DWORD PTR [esi+0x50],0x320` | `0x50` | 4B | 自有成员（800） |
| `0x456b43` | `c7 46 54 58 02 00 00  mov DWORD PTR [esi+0x54],0x258` | `0x54` | 4B | 自有成员（600） |
| `0x456b58` | `ret` | — | — | — |

**最小写入偏移** = `0x0`（vptr）；**最大写入偏移** = `0x5054`，**写入终点** = `0x5058`；**总跨度** = 20,568B，与分配立即数完全一致。

## 3. 类尺寸（两类以上独立证据）

### 3.1 证据 A：operator new 立即数 + ctor 终点

- 分配 `0x5058`（§2.2，A 级）。
- ctor 最远写 `0x5054`+4（§2.3，A 级）。
- 两者相等，且 ctor 尾部 `0x4FB8 + 0x98 = 0x5050`（`UIFrameContainer` 152B）→ `0x5050 uchar` → `0x5054 int` → `0x5058`，**末端逐段顶格无余量**（B 级，依赖 `UIFrameContainer=152` 的注解/IDB 值）。

### 3.2 证据 B：vptr 归属（排除「ctor 是另一个类」）

ctor 在 `0x456b36` 写入 `0x56b364`。`ida_structs.json` 中该 vtable 只属于 `CCBRoleState`（7 槽），槽内 `Render 0x524970 / Update 0x457020 / ~CCBRoleState 0x456b60 / OnMessage 0x457070` 与方法表一致；相邻 vtable 是 `UISceneFrm 0x56b394`，无别名。

### 3.3 证据 C：22,224 无分配支撑

`grep -nE "push\s+0x56d0\b"` 全库 **0 命中**；`0x56d0` 也不作为栈帧 `sub esp` 立即数出现。22,224 只出现在注解与 IDB（IDB 由注解导出，不独立）。

### 3.4 口径与排除项

- 位移扫描口径：`_disasm_cache.txt` 中 `[reg+0xNN]` 形式，限制在函数体地址区间内；排除 `ds:`/`fs:` 绝对寻址与 `[esp+..]` 栈槽。
- `operator new` 只统计 `push imm32; call 0x55353b` 形态；`new[]`（`0x553627`）与 `operator new(size_t,int)` 不计入类分配。
- 未把 IDB `size` 当独立证据（它由注解成员表投影而来）。

## 4. 判别：四种情形逐一排除

| 情形 | 判据 | 结论 |
|---|---|---|
| ① 真越界 | ctor 写入终点 `0x5058` vs 分配 `0x5058` | **排除**（相等） |
| ② 类尺寸偏小 | 22,224 无任何分配；20,568 有唯一分配且 ctor 顶格 | **排除**（是注解偏大） |
| ③ 写入落基类/内嵌对象 | ctor 的 `0x168/0x200..0x4E60/0x4E60/0x4FB8` 都是子对象构造，全部 <`0x5058` | **成立但无害** |
| ④ ctor 实为另一个类 | vptr `0x56b364` = CCBRoleState 表；`Render/Update/OnMessage` 槽一致 | **排除** |

### 4.1 尾部 23 个成员的归属（这是「越界」假象的成因）

| 注解成员区间 | 数量 | 二进制归属 | 证据 |
|---|---|---|---|
| `0x5060..0x50A0` | 15 | **另一个 20,644B 类**（无 vptr，`0x4ec680` 清零恰好 `0x50A4`） | `0x51272b push 0x50a4` → `0x51274e call 0x4ec680`；`0x4ec680` 体 `mov ecx,0x1429; rep stos` = 0x50A4；该类方法 `0x4ec830` 写 `[esi+0x5060]`/`[esi+0x50a0]`、`0x4f7910` 写 `[esi+0x5060]`，最大 0x50A4 |
| `0x55C8/0x55C9/0x55CC/0x55D0` | 4 | **全库零访问**（幻影成员；偏移与 `CG_UI` 的 `m_nNoteMoney/m_pBuyUI` 重合） | `grep -nE "\+0x55(c8|cc|d0)\]"` = 0 命中 |
| `0x5654/0x5658/0x565C` | 3 | **`CCBUIPanel`（22,112 = 0x5660）** | 访问者 `0x44a2e0` 由 `CCBUIPanel::Update 0x44a1b0` 在 `0x44a214` 以同 this 调用；其最大位移 `0x565c`+4 = `0x5660` 与 CCBUIPanel 尺寸相等 |
| `0x56CC` | 1 | **`PropUI`（29,056 = 0x7180）** | 访问者 `0x46d2be lea ecx,[esi+0x56cc]` 位于 `PropUI::InitUI 0x46d140`；该函数最大位移 `0x70d8` < `0x7180` |

四组合计 **15 + 4 + 3 + 1 = 23**，与 §0 第 3 条、§2.1「尾部 23 个成员」一致（`known_members` 共 89 员，偏移 ≥0x5058 者 23 员，按 offset 排序逐个数出）。

## 5. 定谳、影响与下一张卡

### 5.1 定谳

- **A/B/C**：B（伪命题）。证据强度：ctor/分配/写界为 **A**（指令原文 + 唯一分配）；尾部跨类归属为 **B**（每族一个访问点 + 目标类尺寸吻合）；缺口见下。
- **置信度**：对「ctor 不越界」≈ 高（两条独立 A 级闭合）；对「22,224 是混装产物」≈ 高（三类各有独立访问证据）。

### 5.2 缺口

1. 20,644B 类的真名未定（无 vtable、无注解；`ClearAndSetGP` 是 IDB 给它的错名之一）。
2. `0x4e60` 成员注解为 `UIScene *`（4B），但 ctor 以 `call 0x43a770` 构造 0x158B 子对象——类型疑为内嵌对象而非指针（属另一张卡，不影响本结论）。
3. `0x55C8..0x55D0` 四员的来源未追（可能由早期语料抄入 `CG_UI` 的同偏移字段）。

### 5.3 影响面

- `data/annotations/structs/CCBRoleState.json`：`binary_size` 22,224 → **20,568**；删/移 §4.1 的 23 员；`bases/base_size` 不变（`UIListBox@0`，72）。
- census：当前 `6,483B/27` 洞中，`0x5058` 之后的部分（`[0x5058,0x5060)`、`[0x50a4,0x55c8)`、`[0x55d4,0x5654)`、`[0x5660,0x56cc)` 等）合计 **1,568B** 属类外空间，修正后应消失。
- `asm/pal3/ida_structs.json` 的 size 会经 apply→export 跟随注解更新；不得手改。
- 相邻布局：`CCBAI/CCBControl/CCBEditor/CCBStageRole/CCBSystem/CCBAttackSequen` 都只存 `CCBRoleState *`，不受尺寸变化影响。

### 5.4 下一张落地卡输入

- writeScopes：`data/annotations/structs/CCBRoleState.json`、`tests/`。
- 动作：改 `binary_size=20568`；把 §4.1 的 23 员从 `known_members` 移除（15 员迁往 20,644B 类需先命名，另卡；4 员幻影删除；3 员迁 CCBUIPanel、1 员迁 PropUI 先记 TODO 不静默丢）。
- 验收命令：`python tools/audit_type_layout.py --only CCBRoleState`、`python tools/check_annotations.py`、`python tools/census_struct_holes.py`（期望洞从 6,483B 降到 ≤4,915B）、独占窗口 `pipeline/cli.py loop`（S2 ≥158/229、L1 ≥189、总错误 ≤630），不得重锚 `s4_baseline.json`。

## 6. 复现命令与实测输出

### C1 分配行唯一性

```bash
grep -nE "push\s+0x5058\b" data/status/_disasm_cache.txt
```

```
101376:  44c5f3:	68 58 50 00 00       	push   0x5058
```

### C2 22,224 无分配

```bash
grep -cE "push\s+0x56d0\b" data/status/_disasm_cache.txt
```

```
0
```

### C3 ctor 最远写入

```bash
grep -nE "^\s*456(ab|b[0-5])[0-9a-f]:" data/status/_disasm_cache.txt | grep -E "\+0x50[0-9a-f]{2}\]"
```

```
115561:  456b2a:	89 be 54 50 00 00    	mov    DWORD PTR [esi+0x5054],edi
```

### C4 20,644 类的清零宽度

```bash
grep -nE "^\s*4ec68[0-9a-f]:" data/status/_disasm_cache.txt | grep -E "mov\s+ecx,0x1429|rep stos"
```

```
304525:  4ec683:	b9 29 14 00 00       	mov    ecx,0x1429
304528:  4ec68c:	f3 ab                	rep stos DWORD PTR es:[edi],eax
```

`0x1429 × 4 = 0x50A4 = 20,644`。

### C5 尾部四族访问点（按偏移计数）

```bash
python3 - <<'PY'
import re, collections
lines = open('data/status/_disasm_cache.txt', encoding='utf-8', errors='ignore').read().splitlines()
pat = re.compile(r'\[[a-z0-9]+\+0x(5060|50a0|55c8|55cc|55d0|5654|565c|56cc)\]')
cnt = collections.Counter(); sample = {}
for ln in lines:
    m = pat.search(ln)
    if m:
        k = m.group(1); cnt[k] += 1; sample.setdefault(k, ln.strip())
for o in ('5060','50a0','55c8','55cc','55d0','5654','565c','56cc'):
    print(f'0x{o}: {cnt[o]:4d}  first: {sample.get(o, "-")}')
PY
```

```
0x5060:    3  first: 4ec8ea:	c7 86 60 50 00 00 00 	mov    DWORD PTR [esi+0x5060],0x0
0x50a0:    3  first: 4ec8f9:	d9 9e a0 50 00 00    	fstp   DWORD PTR [esi+0x50a0]
0x55c8:    0  first: -
0x55cc:    0  first: -
0x55d0:    0  first: -
0x5654:    4  first: 44a2e9:	38 9e 54 56 00 00    	cmp    BYTE PTR [esi+0x5654],bl
0x565c:    4  first: 44a2f5:	8b 86 5c 56 00 00    	mov    eax,DWORD PTR [esi+0x565c]
0x56cc:   17  first: 46d2be:	8d 8e cc 56 00 00    	lea    ecx,[esi+0x56cc]

```

`0x55c8/0x55cc/0x55d0` 全库零命中；`0x5060/0x50a0` 只出现在 20,644B 类的方法里；`0x5654/0x565c` 只在 `0x44a2e0`（CCBUIPanel::Update 调用）；`0x56cc` 的 17 处全在 `0x46xxxx`（PropUI 方法域）。

### C6 尾部归属类的尺寸

```bash
python3 - <<'PY'
import json
d=json.load(open('asm/pal3/ida_structs.json'))
for k in ('CCBRoleState','CCBUIPanel','PropUI','CG_UI'):
    print(k, d[k]['size'])
PY
```

```
CCBRoleState 22224
CCBUIPanel 22112
PropUI 29056
CG_UI 39240
```

## 7. 边界

- 只新增本文件；`data/annotations/structs/CCBRoleState.json` 未改（`git status` 该路径为空）。
- `data/status/s4_baseline.json` 在取证期间显示 `M`（并发管线写入，mtime 晚于本卡开始），**非本卡改动**；本卡未跑管线、未重锚。
- 未使用 `pal3/src` 生成物作为证据；未引用不存在的文件。
