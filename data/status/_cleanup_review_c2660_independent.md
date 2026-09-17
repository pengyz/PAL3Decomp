# 独立复核：C2660 根因结论（`_cleanup_finding_c2660_root_cause.md`）

> 复核者立场：**证伪优先**。凡引用必自测（跑 wine CL、objdump、读 IDB export 产物、重跑管线）。
> 复核对象：`data/status/_cleanup_finding_c2660_root_cause.md`（下称"该文"）及其证据链
> `_cleanup_finding_too_many_args_scale.md` / `_cleanup_patch_oop_normalize_attempt.py` /
> `_cleanup_a2_vtable_dispatch_feasibility.md` / `_cleanup_baseline_20260915_FINAL.md`。
> 复核时间：2026-09-17。工作目录 `/home/peng/workspace/PAL3Decomp`。

## 0. 结论速览（verdict）

| 主张 | verdict | 一句话 |
|---|---|---|
| **A 规模** | **partial** | `632` 条 ✓；`101 个文件` ✗（当次 census 是 **104**）；**"全部是过多" ✗**（至少 **108 条是"过少"**，另 209 条无法归属） |
| **B 根因唯一一点 = ast_transform.py:587-693** | **refuted** | 632 条里**只有 264 条（41.8%）**带 `[MISATTRIBUTED]` 标记；同一文件里**还有 8 处分支**会保留静态调用形式；另有 **214 条**是"已经是合法成员调用、纯粹实参个数不符" |
| **C "对象确实是调用者 this" + 归属不可信** | **partial** | 调用点地址**引错了**（4db667/4db672 属于 `GetCmdSlot`，不是生成该行的 `CalcTurnOrder`）；但**结论方向正确**，且该文认为"不足以判定"的**归属问题可以判定**：`CalcSpeed` 真实归属是 **CCBAttackSequen**（A 级布局证据） |
| **D 归一化测量 + 回退** | **confirmed** | 完整管线独立复现：`ok 56→56 · C2660 632→417 · C2039 1075→1469 · matched 170→170 · L1 16→16`，**五个数字全中**；补丁的唯一功能 diff 就是那一处；已回退 |
| **E "C2660 不是 codegen 能修的"** | **refuted** | 反例实测：保留 cast、保留 IDB 归属的合法形态（`((Cls*)this)->Cls::M(rest)`，即**既有 Track-1/ROWTABLE 出口的同一个形状**）⇒ `ok 56→59（+3）· C2660 632→383（−249）· C2039 1075→1107（+32）· matched 170→177（+7）· L1 16→16（不回退）` |

**同一个 C2660 里至少有 6 类互不相同的成因**（见 §2 表格）。该文把 632 条统一收敛到"一个门禁分支"，是**过度收敛**。

---

## 1. 复核 A：规模与"全部是过多"

### 1.1 命令与输出（**当次**读数一律取 `data/status/probe_census.json`；`baselines/latest.json` 仅作为**带时间戳的历史快照**引用）

```console
$ python3 - <<'EOF'
import json,collections
d=json.load(open('data/status/probe_census.json'))
print(d['generated_at'], d['s2']['total'], d['s2']['ok'], d['s2']['fail_own'])
c=collections.Counter(); files=collections.Counter()
for r in d['s2']['results']:
    for e in r['errors']:
        c[e['code']]+=1
        if e['code']=='C2660': files[r['unit']]+=1
print(c.most_common(6)); print('C2660',c['C2660'],'files',len(files))
EOF
2026-09-17T15:49:23 202 56 146
[('C2039', 1075), ('C2660', 632), ('C2664', 311), ('C2440', 287), ('C2227', 223), ('C2059', 171)]
C2660 632 files 104
```

- **条数 632 ✓**（与该文一致）。
- **文件数 104 ✗**（该文写 101）。**已定位 101 的出处**（回归对账快照 `data/status/baselines/latest.json`，`timestamp 2026-09-15T23:23:06`）：
  ```console
  $ python3 -c "...data/status/baselines/latest.json: 统计含 C2660 的文件与出现次数..."
  snapshot files containing C2660: 101 ~sites 634
  ```
  ⇒ **`634 条 / 101 文件` 是 9-15 那次快照的真实读数；`632 条 / 104 文件` 是本次 census 的真实读数。该文把两者的"条数用新的、文件数用旧的"拼在了一起。**
  104/146 = **71.2%**、101/142 = **71.1%**——**"71% 的失败文件"这个比例成立**，但"632 条 / 101 文件"这个组合**在任何一次运行里都不存在**。
- 更刺眼的是该文 §1 贴的 N 分布 `0:93·1:183·2:193·3:114·4:20·5:12·6:7·7:1·9:10·10:1` **合计 634**，与它自己标题的 632 不是同一次运行。**该文自身内部不同源**。
  当前 census 的真实分布是：`0:93 · 1:181 · 2:195 · 3:112 · 4:20 · 5:12 · 6:7 · 7:1 · 9:10 · 10:1`（合计 632）。

### 1.2 "全部是「过多」参数" —— 用编译器实测证伪

MSVC6 的 C2660 **对"过多"和"过少"都报**，且消息里的 **N = 实际传入的参数个数**（不是声明数）：

```console
$ cat /tmp/c2660probe/t.cpp        # nfree(int,int) / A::m(int,int)
int nfree(int a, int b) { return a + b; }
int too_many(void) { return nfree(1, 2, 3); }
int too_few(void) { return nfree(1); }
int none_few(void) { return nfree(); }
struct A { int m(int, int); };
int mem_many(A* p) { return A::m(p, 1, 2, 3); }
int mem_few(A* p) { return A::m(p); }

$ bash tools/wine_cl.sh /TP /c /W3 /Fo/tmp/c2660probe/t.obj /tmp/c2660probe/t.cpp
t.cpp(2) : error C2660: 'nfree' : function does not take 3 parameters      ← 过多，N=传入 3
t.cpp(3) : error C2660: 'nfree' : function does not take 1 parameters      ← 过少，N=传入 1
t.cpp(4) : error C2660: 'nfree' : function does not take 0 parameters      ← 过少，N=传入 0
t.cpp(6) : error C2660: 'm' : function does not take 4 parameters          ← 过多
t.cpp(7) : error C2660: 'm' : function does not take 1 parameters          ← 过少
```
（`t2.cpp` 追加验证：`p->m()` 声明 2 参 ⇒ `C2660 ... does not take 0 parameters`；`A::z()` 声明 0 参 ⇒ **C2352**。故"0 参数报 C2660"必然是**过少**。）

**推论（硬）**：任何 `N=0` 的 C2660 站点 **必然是"过少"**。当前 census 里 `N=0` 共 **93 条**。

### 1.3 逐站点按"声明参数数 vs 传入参数数"分类（自己解析生成头声明）

```console
$ # 从 pal3/src/**/*.h 建 类→方法→参数个数 索引，再对每个 C2660 站点解析调用点实参数
classification: {'too_many': 314, 'decl-unknown': 209, 'too_few': 108, 'no-call': 1}
resolved: 422 | too_many: 314 | too_few: 108
== too_few 样例
   ('CCBStage.cpp', 215, 'Array', 'Copy', supplied=0, decl=[1])       # (((Array*)j))->Array::Copy();
   ('CCBStage.cpp', 519, 'PtrArray', 'CompareValues', supplied=1, decl=[2])
   ('CCBStage.cpp', 1947, 'C3DSpark', 'Render', supplied=0, decl=[1])
   ('CCBGame 等，共 108 条')
```
（"arity_ok_but_error"与"between_overloads"均为 0 ⇒ 解析器自洽，没有"实参个数本来就对却报错"的伪分类。）

- **可归属的 422 条中：过多 314 条（74.4%）· 过少 108 条（25.6%）。**
- 209 条 `decl-unknown` 主要是：`operator=` 家族（`=`/`+=`，生成器不写类名前缀）、非限定名（`ShowWindow(hDlg,4)`）、首参为解引用/取址的静态形态（类名前缀在更外层转义里）。
  **这 209 条同样不能算"已证明是过多"。**
- ⇒ **"全部是「过多」参数"= refuted。** 该文此句无任何实测支撑（它只数了错误消息里的 N，而 N 恰是**传入数**，无法区分方向）。

### 1.4 A 的最终裁定

- `632` 条：**confirmed**
- `101 文件`：**refuted**（当次 104；104/146 与 101/142 都是 ~71%）
- `全部是过多`：**refuted**（≥108 条是过少，其中 93 条 N=0 可纯由消息+编译器语义判定）
- 结论：**A = partial**

---

## 2. 复核 B：`ast_transform.py:587-693` 是否**唯一**出路

### 2.1 方法

1. 通读 `pipeline/gen/ast_transform.py` 的 `transform_oop_calls`（现文件 897 行），**逐条列出所有"不改写 / 保留静态形态"的出口**；
2. 从 census 的 632 条 C2660 里，按"错误行→定位该行发出的调用表达式"（用方法名 `name(` 在 ±10 行窗口内配对括号扫描，**解析出的实参数与消息里的 N 逐条一致，0 处不符**）复原**产物里真实存在的形态**，再按形态归类到分支。

### 2.2 穷举：`transform_oop_calls` 里**会保留 `Cls::M(...)` 静态形态**的出口（共 9 处，不止 587-693）

| # | 行 | 出口 | 后果 |
|---|---|---|---|
| 1 | L419-420 | `qualified in static_methods` | 原样返回 |
| 2 | L423-424 | `class_name=='operator' or method_name=='operator'` | 原样返回 |
| 3 | L449-461 | 零实参 & 类不相关 ⇒ `return`（不编辑） | `Cls::M()` 原样 |
| 4 | L576-586 | 首参是数字/字符串/字符字面量 ⇒ `return` | 原样 |
| 5 | L585-586 | 首参是 `call_expression` ⇒ `return` | 原样 |
| 6 | L592-593 | `cast` 分支内的 `static_methods` 命中 ⇒ `return` | 原样 |
| 7 | **L533-554** | 首参 **裸 `this`**、类不相关 ⇒ **`[MISATTRIBUTED]` + 静态形态** | 不合法 |
| 8 | **L682-687** | 首参 `(T*)this`、类不相关、Track-1 门禁不成立 ⇒ **`[MISATTRIBUTED]` + 静态形态**（该文唯一承认的一支） | 不合法 |
| 9 | L716-760 | 首参 `*expr` / `&expr` 且 `_this_consistent` 不成立 ⇒ `return`（注释明写"保持静态形式让 MSVC6 诚实报错"） | 原样 |

⇒ **门禁不是"唯一一点"，而是"两支 + 另外 7 处静默保留"**。且第 7 支（裸 `this`）与该文唯一承认的第 8 支是**同一个设计意图的重复实现**。

### 2.3 632 条的实际成因分解（实测）

```console
TOTAL 632
B1_gate_cast_this(marker, L682-687)                 253
B2_gate_bare_this(marker, L533-554)                  10
B3_gate_marker_other(形态 *this)                      1
M_member_call_arity(已是合法成员调用，仅实参数不符)   214
S2_static_deref_first(L758 静默保留)                 63
S3_static_addr_first(L758/L736 静默保留，含 operator=) 74
S7_static_other(Win32 API 被成员名遮蔽等)             14
S1_static_zero_arg(L449 静默保留 / 非限定名)           2
UNLOCATED                                              1
```

- **门禁族（带 `[MISATTRIBUTED]` 标记）= 253+10+1 = 264 条 = 41.8%**，**不是全部**。
- 从"错误行同一行的调用前缀"精确判定：**632 条里只有 264 条的调用表达式带 `[MISATTRIBUTED]` 标记**；全树 `[MISATTRIBUTED]` 标记共 **347** 个 ⇒ **83 个标记站点根本不产生 C2660**（产生 C2352 或能编译）。"632 条 = 632 处疑似归属错误"**双重不成立**。
- **214 条**（33.9%）是**已经完全合法的成员调用形态**（如 `(((gbVFileSystem*)g_pVFileSys))->gbVFileSystem::Read();`、`(((Array*)j))->Array::Copy();`），报 C2660 的原因是**声明实参数与 decomp 实参数不符**（其中一大类是 N=0 的"过少"），与"静态调用形式"毫无关系。
- 该文 §6-3 说"首参分支共 4 条出路……只有 MISATTRIBUTED 那条产出不合法代码"：该描述**只对 `cast_expression + inner=='this'` 这一个子分支成立**；整个 `transform_oop_calls` 的首参分支远多于 4 条，且**产出非法形态的子分支有 2 条**（L533/L682）。

### 2.4 B 的最终裁定：**refuted**

---

## 3. 复核 C：`0x004DB640` 的证据链与**归属判定**

### 3.1 该文引用的两个地址本身正确，但**挂错了函数**

```console
$ objdump -d --start-address=0x4db640 --stop-address=0x4db658 -M intel original/PAL3.exe
  4db640: 8b 44 24 04   mov  eax,DWORD PTR [esp+0x4]
  4db644: 8b 49 08      mov  ecx,DWORD PTR [ecx+0x8]      ← 读 this+8，不是"读 this"
  4db647: 50            push eax
  4db648: e8 d3 82 01 00 call 0x4f3920
  4db64d: 83 c0 04      add  eax,0x4
  4db650: 8d 04 80      lea  eax,[eax+eax*4]              ← 5*(x+4)
  4db653: c2 08 00      ret  0x8                          ← 2 个栈参数 ✓
```
该文引用的"调用点 4db667/4db672"**属于 `0x4DB660`（IDB: `CCBSystem::GetCmdSlot`）**，而它用来配对的行 `CCBAttackSequen.cpp:172` 由 **`0x4DBB80`（`CCBAttackSequen::CalcTurnOrder`）** 生成：

```console
$ objdump -d --start-address=0x4dbb80 --stop-address=0x4dbbb8 -M intel original/PAL3.exe
  4dbb85: 8b f9        mov   edi,ecx          ← edi = CalcTurnOrder 的 this
  4dbba3: 8b cf        mov   ecx,edi          ← 真正的调用点①：ecx = 调用者 this
  4dbba8: e8 93 fa ff ff call  0x4db640
  4dbbb0: 8b cf        mov   ecx,edi          ← 真正的调用点②
  4dbbb5: e8 86 fa ff ff call  0x4db640
```
⇒ **该文把"另一个函数内部的调用点"当成了本行的证据**（对象与证据不同源）。结论方向（对象=调用者 this）**在正确地址上依然成立**，但该文的证据链**不可采信**。

### 3.2 该文说"尚无该函数读写的成员属于 CCBAttackSequen 的直接证据" —— **该判断过保守，归属可以判定**

**证据 1（成员访问类型）：`this+8` 被当作 `CCBRoleState*` 使用**

```console
$ cat asm/pal3/decomp/CCBSystem_CalcSpeedint_int_004db640.json
"decompiled_c": "int __thiscall CCBSystem::CalcSpeed(CCBSystem *this, int roleIdx, int nVal)
{ return 5 * (CCBRoleState::GetSpeedBonus((CCBRoleState *)this->m_pControl, roleIdx) + 4); }"

$ cat asm/pal3/decomp/CCBRoleState_GetSpeedBonusint_004f3920.json
"name": "CCBRoleState::GetSpeedBonus(int)"
  v2 = (char *)this + 892 * roleIdx;
  if ( v2[1153] ) { v3 = *((_DWORD *)v2 + 155); ... }        ← 至少要访问 this+1153
```
类布局（生成头，均有偏移标注）：
```
CCBAttackSequen.h:  CCBSystem *m_pCBSystem; // +0x0   CCBUI *m_pUI; // +0x4   CCBRoleState *m_pRole; // +0x8
CCBSystem.h:        CCBSystem *m_pUtil; // +0x0   CCBUI *m_pUI; // +0x4   CCBControl *m_pControl; // +0x8
CCBControl.h:       // total size: 0x170 (368)
CCBRoleState.h:     // total size: 0x56D0 (22224)
```
⇒ `GetSpeedBonus` 最少要读 `+1153` 字节；**`CCBControl` 只有 368 字节**，把 `CCBSystem::m_pControl`（`CCBControl*`）当 `CCBRoleState` 用**物理上不可能**；
   而 `CCBAttackSequen::m_pRole`（**`CCBRoleState*`**）与之**类型精确吻合，且无需任何 cast**（decomp 里那个 `(CCBRoleState *)` cast 本身就是不一致的气味）。

**证据 2（调用者布局）：`0x4DBB80` 只能落在 CCBAttackSequen 上**

```
4dbb8b: lea esi,[edi+0x2e]      ← &this->m_Sequen[0].bSlot2Running（m_Sequen 基址 +0xC ⇒ 元素内偏移 0x22）
4dbb9c/9e/a2/a5: 写 [esi+2]=1 / [esi]=0 / [esi-2] / [esi-1]
4dbbcc: add esi,0x28            ← 步长 40（tagAttackSequen 大小）
4dbbe6: lea ecx,[edi+0x20] ; 循环 add ecx,0x28 ; 写 [ecx]=0x2cec 或 0
```
- 换成 `CCBSystem` 布局：`this+0x2C`＝`m_pEffMgr`、`+0x30`＝`m_pATSEffMgr`、`+0x28`＝`m_pConfig`、`+0x40`＝`m_DeltaTime`……
  以 40 步长写 `0x28..0x1B8` 会**成片破坏 CCBSystem 的指针/`double` 成员**（游戏不可能还能跑）。
- 换成 `CCBAttackSequen`：`m_Sequen[11]` 基址 `+0xC`、步长 40 ⇒ 上述偏移全部落在数组内，**严丝合缝**。

**证据 3（唯一"真正属于 CCBSystem"的调用点，也把对象标成了 CCBAttackSequen）**

`CCBSystem::GetSameThreadNum`（0x514870，布局可自证是 CCBSystem：`m_nThread@+0x90`、`m_Thread[1024]@+0x98`）：
```asm
  514870: push ecx/ebx/esi ; mov esi,ecx          ← esi = this (CCBSystem*)
  514957: mov ecx,[edi+0x30] ; push 1 ; push ecx
          mov ecx,[esi+0xC]                        ← ecx = this->m_pAttackSequen (CCBAttackSequen*)
          call sub_4DB640                          ← CalcSpeed 的 this = 一个 CCBAttackSequen
```
生成源码里同一处（注释形态）：
```
pal3/src/Combat/CCBSystem.cpp:2434
    v9 = 2 * v8 * (((CCBSystem *)this->m_pAttackSequen))->CCBSystem::CalcSpeed(v4->cmd.nSrcRole, 1);
```
`CCBSystem::GetSameThreadNum` 的 decomp 另一处同样：
```
    CCBSystem::GetCmdPtr((CCBSystem *)this->m_pAttackSequen, nSrcRole);
```
⇒ 连"真正的 CCBSystem 方法"在调用这一族函数时，**都是把 `m_pAttackSequen`（`CCBAttackSequen*`）强转成 `CCBSystem*`** —— cast 只是为迁就错误注解而存在。

**证据 4（其余调用者）**：`0x4DB640` 的全部调用者 = `0x4DB660 / 0x4DBB80 / 0x4DBE60 / 0x514870`。
`0x4F8BB0`（`CCBRoleState::InitSlot`）对同一对象 `[[CCBRoleState+0x208]+0xC]` 连调 `0x4DBE60/0x4DB750/0x4DB660/0x4DB920`；
这些函数只访问 `[ecx+eax*8+0x20/0x24/0x2d/0x2e/0x2f/0x30]`（即 `this+40*idx+32..48`）——**又是 m_Sequen 元素内偏移**，对 CCBSystem 而言同样落在指针成员上。

### 3.3 第 3 问的归属判定（明确回答）

> **可以判定，不必"不足以判定"**：`0x004DB640 CalcSpeed` 的真实归属是 **`CCBAttackSequen`**（连同 0x4DB5C0–0x4DBE60 这一段被标成 `CCBSystem::GetCmd*/InitCombatSlot/...` 的函数，都是同一族的 CCBAttackSequen 方法）。
> 依据：(a) `this+8` 被当 `CCBRoleState*` 用，与 `CCBAttackSequen::m_pRole`（`CCBRoleState*`）类型精确吻合、与 `CCBSystem::m_pControl`（`CCBControl*`，368B < 最小访问 1153B）**不可能共存**；
> (b) 调用者/被调者共同使用 `m_Sequen`（基址 +0xC、步长 40、元素偏移 32..48）的布局，只有 CCBAttackSequen 能同时解释；
> (c) `CCBSystem` 自己的方法在调用它们时**必须写 `(CCBSystem *)this->m_pAttackSequen` 这种 cast**，说明对象的真实类型是 CCBAttackSequen。
>
> **同时**：该文 C 段引用的 `4db667/4db672` 是 `GetCmdSlot` 内部调用点，**与它引用的源码行不同源**，应改为 `4dbba3/4dbba8`（与 `4dbbb0/4dbbb5`）。
> 另外该文把 `4db644: mov 0x8(%ecx),%ecx` 描述为"读 %ecx = this"也不准确：它是**读 `this+8` 到 ecx**（这正是判定的关键指令）。

⇒ **C = partial**（结论方向对、且可进一步判定到具体类；但证据链引错地址，§5 的"证据不足"结论偏保守）。

---

## 4. 复核 D：归一化尝试的测量（**完整管线独立复现**）

### 4.1 方法（成对：改了就跑，跑完就回退）

```console
$ md5sum pipeline/gen/ast_transform.py
0c9817ae9de6712eb5743e475fe82b02                       # 基线
$ cp -a pal3/src /tmp/c2660bak/pal3_src                  # 备份（pal3/src 被 .gitignore，git checkout 不能还原）
$ cp -a data/status/{probe_census.json,s4_baseline.json,baselines/latest.json,pal3_registry.jsonl} /tmp/c2660bak/
$ cp data/status/_cleanup_patch_oop_normalize_attempt.py pipeline/gen/ast_transform.py
$ python3 pipeline/cli.py codegen all     # codegen_exit=1（compile_regression 报了预期中的退化，见下）
$ python3 pipeline/cli.py probe all
$ python3 pipeline/cli.py match
```
补丁内容核对：`diff pipeline/gen/ast_transform.py _cleanup_patch_oop_normalize_attempt.py` 只有 **1 个 hunk / 38 行**，
唯一功能改动就是在 Track-1 门禁的 `else` 里加 `if _t1_retn and cls_name: new_text='((cls_name *)this)->cls_name::M(rest)'`。**"可原样复用"属实 ✓**

### 4.2 实测数字（与该文 D 表逐格对照）

| 指标 | 改前（我读的当次 census / s4） | 该文"改后" | **我实测改后** | 一致 |
|---|---|---|---|---|
| census `ok` | 56/202 | 56/202 | **56/202** | ✓ |
| C2660 | 632 | 417 | **417（−215）** | ✓ |
| C2039 | 1075 | 1469 | **1469（+394）** | ✓ |
| `matched` | 170/196 | 170 | **170/196** | ✓ |
| `L1` | 16 | 16 | **16（ratchet: previous 16 -> current 16）** | ✓ |

补充实测：
- 补丁产物的 C2039 **机制**也复现了（最小样例）：
  ```console
  $ bash tools/wine_cl.sh /TP /c /W3 /Fo/tmp/c2660probe/t3.obj /tmp/c2660probe/t3.cpp
  t3.cpp(4) : error C2039: 'CalcSpeed' : is not a member of 'CCBAttackSequen'
  ```
  （因为补丁把调用**改写成"调用者自己的类"的成员** `((CCBAttackSequen*)this)->CCBAttackSequen::CalcSpeed(...)`，而生成头里没有这个成员 ⇒ +394 C2039。）
- 该文把 `matched 170 / L1 16` 当作"改前"，与 `_cleanup_baseline_20260915_FINAL.md` 的 `matched 156 / L1 14 / ok 55` **不是同一次运行**——两份证据文件**互相矛盾**（也解释了 §1 的 632/634 与 101/104 混乱）。

### 4.3 回退（逐条）

```console
$ git checkout -- pipeline/gen/ast_transform.py ; echo $?
0
$ md5sum pipeline/gen/ast_transform.py
0c9817ae9de6712eb5743e475fe82b02                        # == 改前 ✓
$ rm -rf pal3/src && cp -a /tmp/c2660bak/pal3_src pal3/src
$ cp -a /tmp/c2660bak/{probe_census.json→data/status/,s4_baseline.json→data/status/,latest.json→data/status/baselines/,pal3_registry.jsonl→data/status/}
$ find pal3/src -name '*.cpp' -o -name '*.h' | sort | xargs md5sum | md5sum
8788e8ab76bc07b596a8c2c2d50398b1                        # == 改前 ✓
$ python3 -c "...probe_census.json..."
census restored: 2026-09-17T15:49:23 ok 56 C2660 632 C2039 1075   # == 改前 ✓
$ git status --porcelain
 M data/status/pal3_registry.jsonl                       # 会话开始前就已是 M（非本次引入）
```

### 4.4 D 的裁定：**confirmed**（数字可复现、回退干净）
但 **D 的推论不能外推到 E**：该补丁是"把被调者搬到调用者类里"（断言了一个**新的**归属，才换来 +394 C2039），
**它并没有测试"保留 cast + 保留原归属"这一形态**（§5 实测）。

---

## 5. 复核 E：反例清单（"C2660 不是 codegen 能修的"）

### 5.1 候选清单与"是否引入未取证断言"的判断

| 候选 | 产物形态 | 是否合法 | 字节忠实 | 是否引入未取证断言 | 判定 |
|---|---|---|---|---|---|
| **① 保留 cast + 保留 IDB 归属**：`((Cls*)this)->Cls::M(rest)`（**＝既有 Track-1 / ROWTABLE 出口的同一形状**） | 合法（只要 `Cls::M` 在生成头里声明） | 直接 `E8` 调用 + `ecx=this`，与二进制同构 | **是**：断言"this 是 `Cls*`"（含 cast）。但**这正是 annotation 已经断言的归属**，且**项目现状里已遍地如此**（见 `CCBSystem.cpp:2434` 的 `((CCBSystem *)this->m_pAttackSequen)->CCBSystem::CalcSpeed(...)`，连门禁都没有） | **反例成立** |
| ② 该文 D 实做的 `((cls_name*)this)->cls_name::M(rest)`（**调用者**的类） | 仅当调用者类声明了 M 才合法 | 同构 | **是**：断言"**被调者属于调用者类**"——一个与 IDB 相反、且生成头不支持的**新**归属 | 不可采（实测 +394 C2039 / ok 无改善）→ 这才是该文真正测到的东西 |
| ③ `this->Cls::M(rest)` | 仅当 `cls_name` 继承 `Cls` 才合法（本例 CCBAttackSequen 与 CCBSystem 是组合不是继承 ⇒ 不合法） | — | **是**：断言了不存在的继承关系 | 不可采 |
| ④ `this->M(rest)`（去限定） | 合法 | **有风险**：`M` 若为虚函数 ⇒ `this->M()` 编译成 **vtable 分发**，与原二进制的直接 `E8` 调用**字节不同**（代码注释 L523-527 已明写此坑） | **是**：断言 `M ∈ 调用者类` | 不可采 |
| ⑤ 放宽 Track-1（只留 `_t1_retn`） | 等价于候选① | 同构 | 同① | 结论同①；但"I-1 例外"名字本身就暗示这是**门禁既有的合法出口** |

### 5.2 候选①的实测量（这才是对 E 的判决性反例）

```console
$ # 只对 L682-687 的 else 分支做一处替换（保留 cast，改用 IDB 归属的类 + 限定调用）
$ python3 - <<'EOF'  # 断言只替换 1 处
old: "else: new_text = ('/* [MISATTRIBUTED] %s on %s::this ... % (class_name, cls_name, ...)"
new: "else: new_text = ('((%s))->%s::%s(%s) ...' % (first_arg_text, class_name, method_name, rest_str))"
EOF
E-candidate written, changed 1 site
$ python3 pipeline/cli.py codegen all ; python3 pipeline/cli.py probe all ; python3 pipeline/cli.py match
```

精确的一处改动（可直接复现；`first_arg_text` 就是 `(CCBSystem *)this`，`class_name`＝被调者类，`rest_str`＝去掉首参后的实参）：

```diff
--- a/pipeline/gen/ast_transform.py
+++ b/pipeline/gen/ast_transform.py
@@ -682,7 +682,8 @@
                                             else:
                                                 new_text = (
-                                                    '/* [MISATTRIBUTED] %s on %s::this '
-                                                    '-> fix IDB name of callee */ %s::%s(%s)'
-                                                    % (class_name, cls_name, class_name,
-                                                       method_name, _margs))
+                                                    '((%s))->%s::%s(%s)  /* [E-CANDIDATE: cast + '
+                                                    'IDB-attributed qualified call] */'
+                                                    % (first_arg_text, class_name,
+                                                       method_name, rest_str))
```
（脚本与日志留存于 `/tmp/ast_transform_E.py`、`/tmp/e_codegen.log`、`/tmp/e_probe.log`、`/tmp/e_match.log`；`/tmp` 易失，故此处内联 diff。）
| 指标 | 基线 | **候选①实做** | 变化 |
|---|---|---|---|
| census `ok` | **56/202** | **59/202** | **+3** |
| **C2660** | 632 | **383** | **−249** |
| **C2039** | 1075 | **1107** | +32 |
| 总错误 | 3817 | **3667** | **−150** |
| `matched` | 170/196 | **177/203** | **+7** |
| **`L1`** | **16** | **16** | **不回退**（`[L1 ratchet] previous 16 -> current 16`） |

（诚实边界：`L1` 不回退只能证明"没有打破任何字节全同函数"。被改写站点的**父函数**多为 partial，因此"这些调用点逐字节全同"未被本测量直接证明；但其形态是直接调用 + `ecx=this`，与 `4dbba8/4dbbb5` 的 `mov ecx,edi; call` 同构。）

### 5.3 E 的裁定：**refuted（作为普适结论）**

- "C2660 **不是** codegen 能修的" **不成立**：一处 codegen 改动即可 **−249 条 C2660、`ok` +3、`matched` +7、`L1` 不回退**。
- 该文的回退依据（`−215 C2660 / +394 C2039 / ok 无改善`）**只对它自己那个"把被调者搬到调用者类"的错误写法成立**，不构成对候选①的反驳。
- **但**：候选①在**诚实性**上确实有代价——它把"对象是 `Cls*`"这个断言**写实**了；对 §3 已判定归属的 `CalcSpeed` 而言，该断言与二进制事实**相反**。
  所以正确的下一步不是"放宽门禁"，而是 **annotation 层把这一族函数从 `CCBSystem` 迁到 `CCBAttackSequen`**（§3 已给出 A 级证据）；
  同时可以**立刻拿到 +3 ok / −249 C2660 / +7 matched 的收益**（若纪律允许"先合法化、后纠正归属"两阶段推进）。
- ⇒ **E = refuted**；其背后真正的瓶颈（归属注解）判断是对的，但"codegen 修不了"的边界被自己的错误实现假象放大了。

---

## 6. 该文漏了什么（第 6 问）

### 6.1 两个既有 unittest 失败：**先前就存在 ✓（该文说法正确）**——用 `git show`（无 stash）核实

```console
$ git log --oneline -1 9cb436305 ; git cat-file -t 9cb436305
9cb436305 ...（会话起点提交）
commit
$ git show 9cb436305:pipeline/gen/ast_transform.py > /tmp/oldgen/ast_transform.py
$ cd /tmp/oldgen && python3 -c "...transform_oop_calls..."
OLD(9cb436305) id: 'int test() { (((Foo *)ptr))->Foo::DoSomething(1, 2); return 0; }'
OLD(9cb436305) cx: 'int test() { (((Foo *)obj->field))->Foo::DoSomething(1); return 0; }'

$ cd pipeline/gen && python3 -m unittest test_pipeline 2>&1 | tail -4
FAIL: test_complex_expr_as_first_arg ... not found in '... (((Foo *)obj->field))->Foo::DoSomething(1) ...'
FAIL: test_identifier_as_first_arg  ... not found in '... (((Foo *)ptr))->Foo::DoSomething(1, 2) ...'
Ran 44 tests ... FAILED (failures=2)
```
⇒ 多点一层括号（`(((Foo*)x))` vs 期望 `((Foo*)x)`）**在会话起点提交上就已存在**，且**纯括号冗余、不影响编译**。
（附带：`python3 -m pytest` 在本环境因外部 pytest 插件路径崩掉，我改用 `python3 -m unittest`。）

### 6.2 `pal3_vtbl_unk_N` 签名损坏：**是独立缺陷，规模被夸大 60 倍**

```console
pal3_vtbl_unk_* 相关错误: {'C2664': 8, 'C2371': 3, 'C2264': 4} 合计 15 条 / 8 个文件 / 4 个不同符号
pal3/src 里 pal3_vtbl_unk_ 的出现次数: 927 ；**不同 stub 符号数: 38**
```
⇒ 该文"927 个 stub 可能普遍如此"把**出现次数**当成了**stub 个数**；真实错误面是 **15 条 / 4 个符号**，与 C2660 完全独立（不同错误码）。

### 6.3 632 条里"退化形态（非方法名）"：**37 条（5.9%），该文当成同一根因不妥当**

```console
非标识符名字: 37  ['=' 27, '+=' 8, '-' 1, '*=' 1]     （全部 N≥1）
```
这些是 `gbVec3D::operator=(&v21.Direction, ViewTarget)` 一类：走的是 **L716-760 `pointer_expression` 分支的静默保留**（`&` 首参 + `_this_consistent` 不成立），
**与 L682-687 的门禁无关**（该文 §2 说"C2660 全部出自这一支"对它们直接不成立）。

### 6.4 该文没有指出的另外两类独立成因

- **成员名遮蔽 Win32 API**（15 条）：生成头里有 `void CCBStage::ShowWindow(); // 0x0051DDA0`，
  于是类内 `ShowWindow(hDlg, 4)` 解析到**成员**（0 参数）⇒ `C2660 'ShowWindow' : function does not take 2 parameters`。**与归属门禁无关**。
- **"过少"族**（108 条，其中 93 条 N=0）：如 `(((gbVFileSystem*)g_pVFileSys))->gbVFileSystem::Read();`（`Read` 声明有参）、
  `(((Array*)j))->Array::Copy();`（`Copy` 声明 1 参）——**这是"调用点实参数 < 声明参数数"的注解/反编译缺口**，方向与"多传参"相反。

### 6.5 其它遗漏/不一致

- 门禁行为被 **unit test 钉住**（`pipeline/gen/test_pipeline.py: TestTrack1EvidenceGate` 等，注释里还写着"ret-N alone rewrites 298 sites / 189 files"）。**改门禁必须同步改测试**——该文完全未提这个依赖。
- 该文 **§1 与 §2 的因果不一致**：§2 说"两条件不都成立 ⇒ 静态形态"，而实测有 **264 条带标记**、另有 **347 个标记里 83 个不产生 C2660**；"632 = 632 处疑似归属错误"没有任何一条命令能复现。
- 该文 §4 的"改前"列（`ok 56 / matched 170 / L1 16`）与其证据文件 `_cleanup_baseline_20260915_FINAL.md`（`ok 55 / matched 156 / L1 14 / C2660 634`）**互相矛盾**；读者无法判断到底哪个是基线。

---

## 7. `changed_paths_and_reverted`（我改过/动过的每一样东西）

| 路径 | 动作 | 是否已还原 | 证据 |
|---|---|---|---|
| `pipeline/gen/ast_transform.py` | ① 覆盖为 `_cleanup_patch_oop_normalize_attempt.py`（复现 D）② 覆盖为 `/tmp/ast_transform_E.py`（复现 E 反例） | **已还原** | 两次 `git checkout --`；md5 均回到 `0c9817ae9de6712eb5743e475fe82b02` |
| `pal3/src/**`（gitignored，codegen 产物） | 被上述两次 `codegen all` 重写 | **已还原** | 整树 md5 回到 `8788e8ab76bc07b596a8c2c2d50398b1`（与实验前一致） |
| `data/status/probe_census.json` | 被两次 `probe all` 重写 | **已还原** | 回到 `generated_at 2026-09-17T15:49:23 / ok 56 / C2660 632 / C2039 1075` |
| `data/status/s4_baseline.json` | 被两次 `match` 重写 | **已还原** | 从 `/tmp/c2660bak` 回拷 |
| `data/status/baselines/latest.json` | 可能被 probe 对账触碰 | **已还原** | 从 `/tmp/c2660bak` 回拷 |
| `data/status/pal3_registry.jsonl` | 被两次 `match` 重写 | **已还原** | 从 `/tmp/c2660bak` 回拷；`git status` 仍显示 ` M`（**会话开始前即为 M**，非本次引入） |
| `data/status/_cleanup_review_c2660_independent.md` | **新建**（本报告） | —— | 交付物 |
| `/tmp/c2660probe/*`、`/tmp/oldgen/*`、`/tmp/ast_transform_E.py`、`/tmp/c2660bak/*`、`/tmp/{d,e}_*.log` | `/tmp` 实验副本与日志 | 保留在 `/tmp`（仓库外） | —— |
| 未触碰 | `data/annotations/**`、`include/**`、`original/PAL3.exe.i64`（未跑 idat） | — | — |

**验证过 git status（结束时）**：只有会话开始前就存在的 ` M data/status/pal3_registry.jsonl` 与既有 `.agent-teams/*` 未跟踪目录。

---

## 8. 给 captain 的净结论

1. **A 部分错**：632 条对、101 文件错（104）、"全部是过多"错（≥108 条是过少，93 条由 N=0 可直接判定）。
2. **B 部分错**：`[MISATTRIBUTED]` 门禁只解释 **264/632（41.8%）**；另有 214 条是"合法成员调用 + 实参数不符"、137 条是其它静默保留出口、15 条是 Win32 API 被成员名遮蔽。**"唯一一点"不成立**，且门禁本身有 **两支**（L533 裸 `this` 与 L682 `(T*)this`）。
3. **C 结论方向对、证据引用错**：应引用 `4dbba3/4dbba8`（`CalcTurnOrder` 内），而非 `4db667-4db672`（`GetCmdSlot` 内）；且**归属可以判定为 `CCBAttackSequen`**（A 级布局证据），不该停在"不足以判定"。
4. **D 可复现、回退干净**：五个数字全中，补丁确为单 hunk。
5. **E 被实测反例推翻**：保留 cast + 保留 IDB 归属的既有合法形态，一处 codegen 改动即 **ok 56→59、C2660 −249、matched +7、L1 不回退**。该文的"codegen 修不了"是**由它自己那个错误实现（把被调者搬到调用者类）造成的假象**。
6. **建议的下一步（按证据强度排序）**：
   - **annotation 层**：把 `CalcSpeed` / `GetCmdSlot` / `InitCombatSlot` / `GetCmd*` 一族从 `CCBSystem` 迁到 `CCBAttackSequen`（§3 三条 A 级证据；可先迁 0x4DB640/0x4DB660/0x4DBE60 三个点验证）。
   - **codegen 层（可选、可立即收益）**：若纪律允许"先合法化、后纠正归属"，把 L682-687 门禁的 else 改为 `((Cls*)this)->Cls::M(rest)`（候选①），实测 **+3 ok / −249 C2660 / +7 matched / L1 不回退**；但必须同时在报告里标注"该 cast 断言对已判定站点与二进制的真实类型相反"。
   - **顺带**：`pal3_vtbl_unk_N`（15 条 / 4 符号）与 `ShowWindow` 成员遮蔽（15 条）是两个独立的小缺陷，值得单独立项，不要与 C2660 混为一谈。