# t7 — 破坏性注释与硬编码模式表（`stage3_cleanup.py`）修复报告

> 执行单元：t7 · 日期：2026-09-15 · 仓库 `/home/peng/workspace/PAL3Decomp`（HEAD `9cb436305`，未提交）
> 主证据法（按硬纪律 §5）：**不写 `pal3/src`**。所有"改前/改后"都在**同源 harness** 内比较：
> `PYTHONHASHSEED=0 python3 /tmp/t7/gen.py {orig|new} /tmp/t7/{base,new}`，
> 两者**唯一差异是 `pipeline/gen/stages/stage3_cleanup.py`**（orig = `/tmp/t7/stage3_cleanup.ORIG.py`，
> sha256 `190516a45d1168445994a688ada137e64570c47f3c05940dd35501d85b611ea4`）。
> 另用**单 TU VC6 编译**（`tools/wine_cl.sh`，与 `build/build.ninja` 同 flag 集）对 54 个变化文件做 base↔new 编译对照。
> 未运行 `apply`/`export`/`codegen`/`probe`/`match`，未触碰 IDB。

---

## 0. 结论摘要（TL;DR）

| 项 | 结果 |
|---|---|
| `[VFTABLE]` 注释行（127 个"当前管线会重生成"的文件内） | **596 → 0**（−100%） |
| 其中**真 vptr 存根**（正证据判据命中数） | **0**（pass 层 1511 函数实测；语料层 108 条 `__vftable =` 逐条枚举） |
| 恢复为 offset-0 等价访问 | 422 处折叠（377 行），`(*(void **)(X))` / `((void **)(X))` |
| 保留原样（不可安全折叠） | 116 限定基类 + 31 链式 + 8 下标 = 155 行（GAP-1/2） |
| `[AUTO-COMMENTED]` | **172 → 89**；**83 条"被丢弃的被使用赋值"全部恢复**（§4 逐条） |
| `[IDA_MISID]` | **35 → 0**（6 个硬编码模式表删除）；悬垂引用实测 2 处 → 0 |
| `[MISATTRIBUTED]` / `[ROWTABLE]` / `[VFTABLE-STUB]` | **不变**（153/153、373/373、186/186）→ 未越界改 t6 的成果 |
| 逐字节影响范围 | **54 个文件**（53 `.cpp` + `free_functions.cpp`），**无 `.h` 变化** |
| 单 TU 编译对照（54 文件） | base ok **7** → new ok **7**；**回归 1**（`Misc/ChoseCompose.cpp`）、**改善 1**（`Misc/ArcLocaleRole.cpp`） |
| `L1` | **预期保持 5**（5 个 L1 符号所在文件：4 个字节未变；`ObjectCamera.cpp` 只改了**另一个函数**且仍编译通过）→ **最终读数待 t9 窗口** |
| `ok`（S2） | 基准 53/198。按单 TU 实测外推：`ChoseCompose.cpp` ok→fail（−1）、`UIStatic.cpp` 新增 2 条 C2440（很可能 −1）、`ArcLocaleRole.cpp` fail→ok（+1）→ **预计 52/198，待窗口确认** |
| 测试 | `python3 -m unittest test_pipeline`：**44 tests / 42 pass**；2 个失败是 **t6 未提交的 `ast_transform.py` 造成的既有失败**（`TestOopTransform::test_identifier_as_first_arg`、`test_complex_expr_as_first_arg`，与我无关） |

---

## 1. 判据：只允许真 vptr 存根走注释路径

### 1.1 判据（实现于 `_vptr_store_kind()`）

一条语句进入**注释路径**必须**同时**满足：

1. **赋值目标是 vptr 设计ator**：`<obj>[Base::]__vftable = <rhs>;`，且设计ator 前一个非空字符是
   `>` / `.` / `:`（排除 `&x->__vftable = …`、`*(float *)&x.__vftable = …` 这类"目标是字段地址的派生量"）；
2. **RHS 有 vtable 符号的正证据**：`&<symbol>` 或含 MSVC 的 `` `vftable' `` 符号；
3. **RHS 不命中数据形态黑名单**：`(T *)<数字字面量>`、`LODWORD(`/`HIDWORD(`、`*(float *)`。

**关键取舍（有实测反例支撑）**：`(vtbl_XXXX *)<expr>` **不是**证据 —— 它是字段在 IDB 里的**声明类型**，
Hex-Rays 对数据写入同样会加；`= 0`、`= <局部变量>` 同样不是证据（见 §1.3 反例）。因此判据故意收得很窄。

### 1.2 实测命中数 = **0**

| 层面 | 口径 | 命中 |
|---|---|---|
| pass 层 | `_comment_vptr_stores()` 在 stage1→3 之后被调用 **1511** 次（= 1511 个函数），逐行跑 `_vptr_store_kind()` | **0** |
| 语料层 | 3594 个 decomp JSON 中 **108 条** `__vftable =` 赋值语句，逐条判 RHS | **0** |

命令（可复核）：

```bash
PYTHONHASHSEED=0 python3 /tmp/t7/count_hits.py      # pass_calls=1511 / 真 vptr 存根注释命中=0 / fold 334+88
#   语料层：python3 - <<'PY' … 见 /tmp/t7/corpus_rhs.txt
```

语料层 108 条 `__vftable =` 的 RHS 形态**全枚举**：

| RHS 形态 | 条数 | 例 |
|---|---|---|
| cast(数字字面量) → 数据值 | **49** | `this[2].__vftable = (vtbl_0056AE2C *)1117782016;`（= 80.0f）、`… = (vtbl_0056AC08 *)1082130432;`（= 4.0f）、`… = (vtbl_0056AE2C *)38;` |
| 裸标识符 | 23 | `this->m_btnPar2[11][5]._element.__vftable = left;`、`this->m_OutFrameT.__vftable = Color;` |
| 字面 `0` | 17 | `this->GlowObj::__vftable = 0;`、`this->me_Role[2].m_RoleAttCng[2].__vftable = 0;` |
| 其它 cast 表达式 | 15 | `… = (vtbl_0056AE2C *)((char *)m_disablepic + v44);`、`… = (vtbl_0056AE2C *)(this->stp_Effect.m_bfocus + 5);` |
| 其它（float 运算 / 字段互拷） | 3 | `*(float *)&this[1].__vftable = 360.0 - (v4 - v5) + v4;`、`pSceneObj->GlowObj::__vftable = this->GlowObj::__vftable;` |
| **vtable 符号证据（`&` / `` `vftable' ``）** | **0** | — |

### 1.3 「`(vtbl_*)`/`= 0`/字段拷贝」为什么不是 vptr 存根（A 级上下文反例）

1. **`Scene/SceneObj.cpp`（真实树）:526 / :974** —— `pSceneObj->GlowObj::__vftable = v5;`
   `v5` 在同一函数里被当**长度**与**下标**用：`qmemcpy(pSceneObj->m_needscriptdel, &v16[dwVal], (unsigned int)v5);`
   之后 `v5[(_DWORD)v17] = 0;`；:974 的 `vftable` 同样是 `qmemcpy(…, (unsigned int)vftable)` 的长度、
   `*((_BYTE *)vftable + (_DWORD)v11) = 0;` 的下标。→ 该字段是**数据**（注意：`SceneObj` 的
   `GlowObj` 基类在 **+8**、`TaskMgr_SceneObjParam_SceneObj` 在 **+40**，见 `asm/pal3/ida_structs.json`）。
2. **`Misc/UISceneFrm.cpp:326`（同模式重复 10 处）** —— `v5->__vftable = *(vtbl_0056AE2C **)v6;`
   而 `v6` 在同段被当 float 数组用（`v6[1]`、`*(v6-3)`、`*(v6-2)`、`v6 += 60`）→ `(vtbl_… **)` 是
   Hex-Rays 为匹配字段类型的**强制转换**，不是来源证据。
3. **铁证锚点 `Combat/CCBCamControl.cpp:972-975` vs `:983-986`** —— 未注释的
   `*v3 = -1098907648; v3[1] = -1098907648; … v3[3] = 1065353216;`（`0xBE800000`、`0x3F800000`）
   与**被注释**的 `v4->__vftable = (void *)-1098907648; … v4[3].__vftable = (void *)1065353216;`
   是同一件事：**offset-0 的 float 写入**。
4. **`Render/CScreenMode.cpp:1649-1676`** —— `v30[i].__vftable = (void *)1;` /
   `v31[j].__vftable = (void *)1036831949;`（0.1f）/ `1065353216`（1.0f）→ 数据。

### 1.4 补充发现：旧 pass 连**已经合成好的桩调用行**也一起注释掉

旧 blanket commenter 的判据是"行内含 `__vftable` 且不含 `//`"，而 `[VFTABLE-STUB]` 的**调用点**形如
`pal3_vtbl_unk_0(args) /* [VFTABLE-STUB] */`（块注释，**不含** `//`）→ 命中判据被整行注释，
**把 `_resolve_vftable_calls_ast()` 刚刚用来保全表达式的桩又抹掉了**（第二道正则的 `(?!/[/*])` 只看行首，救不回来）。

| 口径 | 被注释掉的桩调用行 |
|---|---|
| 真实树（当前 `pal3/src`） | **12 行 / 6 文件** |
| 同源 base（127 重生成文件内） | **7 行** |
| 改后（new） | **0 行**（余 4 行在孤儿文件 `CCBSkillWindow.cpp`/`CCBAttackSequen.cpp` 里，我的改动不可达） |

实例（真实树 `pal3/src/free_functions.cpp:10913`）：

```c
// [VFTABLE] pal3_vtbl_unk_0(v55, (char *)&((CCBFiveNimbusWindow *)&stru_A00601)->__vftable + 1, &v76, v2) /* [VFTABLE-STUB] */;
```

复核命令：`grep -rc '// \[VFTABLE\].*VFTABLE-STUB' {pal3/src,/tmp/t7/base/pal3/src,/tmp/t7/new/pal3/src}`

> 因此 **交接文档 §4 t7 的「仅约 2.5% 是真 vptr 存根」不可复现**：以正证据计上限是 **0/596（0%）**。
> 这**不等于**"语料里没有 vptr 存根"——MSVC 生成的 `this->__vftable = &Cls::`` `vftable' ``;` 在管线里
> 由 `_remove_backtick_calls()`（`run()` 末尾）整行删除，且我的注释 pass 仍覆盖它们（判据的
> `&<symbol>` / `` `vftable' `` 分支，单测 `test_vftable_assign_backtick_symbol_commented` 已固定该行为）。
> 二者叠加：**真存根既不会留在源码里，也不会被误注释**。

---

## 2. 标记形态分类计数（改前 / 改后）

### 2.1 三个口径必须先说清（这决定了数字怎么读）

1. **当前管线只重生成 127 个 `.cpp`**，而 `pal3/src` 里有 **198 个 `.cpp`** →
   **71 个是"孤儿文件"**（其类名已不在当前 `asm/pal3/decomp` 语料中，例如 `RenderTarget2.cpp`、
   `CEffgbParticle.cpp`、`UICursor.cpp`），当前管线**永远不会重写**它们。
   复核：`python3 /tmp/t7/gen.py new …` 打印 `Generated 127 .cpp files (1511 functions)`（= `/tmp/t7/regen_files.txt` 127 行）。
2. 当前 `pal3/src`（15:10 生成）**与当前 decomp 语料（15:44 重建）不同源** → 全量重生成会额外产生与 t7 无关的差异
   （实测：harness base 与 `pal3/src` 有 138 个文件不同）。**所以改前/改后只能在 harness 内比。**
3. 因此下表给三个数：`真实树`（当前 `pal3/src`，供对照）·`base`（同源 harness 改前）·`new`（改后）。

### 2.2 计数表

**A. 127 个"会重生成"的文件**

| 标记 | 真实树（当前） | base（改前·同源） | new（改后） | Δ |
|---|---|---|---|---|
| `[VFTABLE]` | 1250 | **596** | **0** | −596（−100%） |
| `[VFTABLE-STUB]` | 568 | 186 | 186 | 0 ✅ |
| `[AUTO-COMMENTED]` | 219 | 172 | **89** | −83 |
| `[IDA_MISID]` | 78 | 35 | **0** | −35 |
| `[MISATTRIBUTED]` | 306 | 153 | 153 | 0 ✅（t6 领域未动） |
| `[ROWTABLE]` | 533 | 373 | 373 | 0 ✅ |
| `[IDA_VFTABLE]` | 0 | 0 | 0 | 0（死发射分支已删） |

**B. 全树（含 71 个孤儿文件）**

| 标记 | 真实树 | base | new | 说明 |
|---|---|---|---|---|
| `[VFTABLE]` | **1935**（与 §2.3 一致 ✅） | 1281 | **685** | 余下 685 行**全部在孤儿文件里**，我的改动对其零影响 |
| `[AUTO-COMMENTED]` | **233**（一致 ✅） | 186 | 103 | 余下 103 = 孤儿 14 + standalone 89 |
| `[IDA_MISID]` | **84**（一致 ✅） | 41 | **6** | 余下 6 行全在孤儿文件（`CEffGrid.cpp` 3、`RoleStatePanel.cpp` 2、`ExternalStatistics.cpp` 1） |
| `[MISATTRIBUTED]` | **341** | 153 | 153 | 交接文档记 344 → 实测 341（t6 的 −3 已落地，**不是我的改动**） |
| `[ROWTABLE]` | **576**（一致 ✅） | — | — | 未动 |
| `[IDA_VTABLE]` | **1**（.h，一致 ✅） | — | — | 属 t8 |

### 2.3 `[VFTABLE]` 改前形态分类（base，596 行 = 500 head + 96 续行）

| 编码 | 形态 | 行数 | 占比 | 例 |
|---|---|---|---|---|
| **A** | **真 vptr 存根（vtable 符号证据）** | **0** | **0%** | — |
| B | vptr 槽写入：其它 RHS | 58 | 11.6% | `v5->__vftable = (vtbl_0056AE2C *)gfxMgr->~gbGfxManager(Buffer);` |
| C | vptr 槽写入：数据值（float/int 位型） | 48 | 9.6% | `this->m_scrollbar.UIListBox::__vftable = (vtbl_0056AE2C *)800;` |
| D | 取地址 `&X->__vftable`（= 对象首字节地址） | 90 | 18.0% | `*((_DWORD *)&this->SceneObj::TaskMgr_…::__vftable + 9) = 0;` |
| E | 控制流头（if/while） | 26 | 5.2% | `if ( v5->__vftable )` |
| F | 读入变量 / 参与运算 | 129 | 25.8% | `vftable = (int ( **)(gbGfxManager *, CHAR *))gfxMgr->__vftable;` |
| G | 通过 vptr 的调用/分派 | 21 | 4.2% | `(char *)&((CCBFiveNimbusWindow *)&stru_A00601)->__vftable + 3,` |
| H | 限定基类 `__vftable`（偏移不可知） | 64 | 12.8% | `(*((void ( **)(SceneObj *, int))m_pSceneObjRef->PalScriptWaitObj::__vftable + 5))(…)` |
| I | 其它 | 64 | 12.8% | `(((gbRefObject *)v5->__vftable))->gbRefObject::Release();` |

> 分类器的类别是启发式（`/tmp/t7/shape2.txt` 有每类样本），但 **A=0 是判定式的**（由 §1.1 判据直接给出）。

**改后**：A/B/C/D/E/F/G/I 全部**不再被注释**；其中可安全折叠的变成 offset-0 等价访问（422 处），
H（116 行）、`X->__vftable->M`（31）、`X.__vftable[i]`（8）**保留原样**（见 §7 GAP-1/2）。

---

## 3. 逐字节影响范围（base ↔ new）

```
diff -rq /tmp/t7/base/pal3/src /tmp/t7/new/pal3/src
→ 54 个文件不同：53 个 .cpp + free_functions.cpp；**0 个 .h**
合计：删除 [VFTABLE] 行 596 · 新增折叠行 377（422 处折叠）· 恢复 [AUTO-COMMENTED] 83 · 恢复 [IDA_MISID] 35
```

逐文件（完整表 `/tmp/t7/perfile.txt`）摘要 —— 每个变化都属于下列三类之一：

| 变化类型 | 为何是「恢复真实语义」 | 例 |
|---|---|---|
| ① `// [VFTABLE] <行>` → 折叠后的真实语句 | 该行是**真实机器码的可见形式**（数据写入/读取/分派/控制流）被整段丢弃；折叠后字节等价（vfptr 变体在**自身对象的 offset 0**） | `Misc/UIStatic.cpp:179` `vftable = (int ( **)(gbGfxManager *, CHAR *))gfxMgr->__vftable;` → `… (*(void **)(gfxMgr));` |
| ② `// [AUTO-COMMENTED] LHS = …Cls(args)…` → `LHS = ((Cls *)obj)…` | Hex-Rays 把显式 ctor 调用建模成"返回对象指针"的调用；**被赋的值后续被使用**（如 `v4` → `this->m_pCamera`、`Color` → `v7->curColor.Color`），丢弃即丢真实语义 | `Role/ObjectCamera.cpp:90` `v4 = v3->gbCamera(position);` → `v4 = ((gbCamera *)v3);` |
| ③ `// [IDA_MISID] <行>` → 原行 | 6 个硬编码模式表按**名字子串**注释，抽到的是真实代码（SEH 初始化、FLIRT 误命中名下的真实调用/变量） | `GameBase/PAL3.cpp:1056` `ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;` |

变化最大的文件：
`Misc/CCBUIPanel.cpp`（−133 VFT / +122 折叠 / +38 AUTO-COMMENTED）·
`Scene/SceneObj.cpp`（−44 / +1）· `Misc/UITitle_JDHY.cpp`（−37 / +37）·
`UI/PropUI.cpp`（−37 / +12）· `Script/PalScript.cpp`（−11 VFT / −5 MIS）·
`Render/RenderTarget.cpp`（仅 −5 MIS）· `GameBase/PAL3.cpp`（−11 VFT / −5 MIS / −2 AC）。

---

## 4. `[AUTO-COMMENTED]`：被丢弃的「被使用赋值」是否已恢复

**改前**（同源 base，127 文件）：172 行 = `standalone` 89 + `assign` **83**。
**改后**：89（`standalone` 全保留旧行为）；**83 条 `assign` 全部恢复**，逐条如下
（完整机读表 `/tmp/t7/ac_pairs.txt`）：

| # | 文件 | 恢复前（被注释） | 恢复后 |
|---|---|---|---|
| 1 | Combat/CCBRoleState.cpp | `v9 = v13.gbColorQuad(0x3Du, 0x5Au, 0x85u, 0xFFu);` | `v9 = ((gbColorQuad *)&v13);` |
| 2 | Combat/CCCTData.cpp | `Color = v45.gbColorQuad(v6, v41, v42, v44)->Color;` | `Color = ((gbColorQuad *)&v45)->Color;` |
| 3 | Data/CGameData.cpp | `v10 = v32->CCBUIPanel();` | `v10 = ((CCBUIPanel *)v32);` |
| 4 | GameBase/GRPinput.cpp | `v4->curColor = (gbColorQuad)v20->gbColorQuad(0xFFu,…)->Color;` | 同型折叠 |
| … | （共 83 条，见 `/tmp/t7/ac_pairs.txt` 全表） | | |

**口径差异（以实测为准）**：交接文档 §4 t7 说"`[AUTO-COMMENTED]`（233）中 **89 处**丢弃被使用的赋值"。
实测：全树 233 = `standalone` 138 + `assign` **95**；同源 harness 的 127 文件范围内 `assign` **83**（全部已恢复）。
差异来源有三：孤儿文件（14 行，我的改动不可达）、decomp 语料换代、以及 t6 漂移。

**恢复后仍可能报错（已归因，见 §6）**：折叠把 ctor 调用的"返回值"还原成对象指针，
若 Hex-Rays 认为的类型与**注解里成员的真实类型**不一致，就会暴露 C2440 —— 这正是
CLAUDE.md「编译错误是标注错误的表象」的情形。实例：`Misc/UIStatic.cpp:262/297`
`this->m_textx = ((gbGfxManager *)gfxMgr);` → `C2440: cannot convert from 'class gbGfxManager *' to 'int'`，
而同函数 `:264` 就是 `v7 = (gbTexture *)this->m_textx;` → **`m_textx` 被注解成 `int` 是错的**（应是指针）。

---

## 5. `[IDA_MISID]`：子类 (i) 悬垂引用 / 子类 (ii) 处置

**改前**（同源 base，127 文件）：35 行 = **子类 (i) NtTib/ExceptionList 3** + **子类 (ii) `_Xlen`/`_Xran`/Concurrency 32**。
（全树：84 = 交接文档数字一致 ✅）

**处置：整表删除**（`run()` 中 6 模式正则表移除，替换为说明注释）。理由：该表按**名字子串**整行注释，
(a) 抽到的是真实代码；(b) 与"由名字决定的声明/使用"配对无关 → 会产生**悬垂引用**；
(c) 根因（FLIRT/TIL 误命中）**属于 IDA 层**，按 CLAUDE.md「IDA 层能解决的问题在 IDA 层解决」不应在 codegen 打补丁。

**悬垂引用实测（真实树）**：

| 文件 | 标识符 | 被注释的引入行 | 仍在引用的未注释行 | 归属 |
|---|---|---|---|---|
| `Combat/CCBCamControl.cpp` | `index` | `192: // [IDA_MISID] Concurrency::IThreadProxy *index;` | `245: if ( (int)index > 0 )`、`266: while ( v6 < (int)index );` | **子类 (ii)** |
| `Combat/CCBRoleState.cpp` | `Proxy` | `4635: // [IDA_MISID] Concurrency::IThreadProxy *Proxy;` | `4643: if ( (int)Proxy <= 0 )`、`4762: while ( v5 < (int)Proxy );` | **子类 (ii)** |

> **与交接文档不符**：§4 t7 说"子类 (i) 15 处（NtTib/ExceptionList，注释后留**悬垂引用**）"。
> 实测**子类 (i) 悬垂 0 处**：`PAL3.cpp:1047/1066/1068` 这类 decl/赋值/使用**三行都含模式串**，
> 被整体注释 → 是"**整段丢代码**"而不是悬垂；真正的悬垂 2 处反而在**子类 (ii)**。
> **改后**：两处悬垂随声明行恢复而消除（`grep -c '\[IDA_MISID\]' /tmp/t7/new/... = 0`）。

**子类 (ii) 残余风险（诚实标注）**：恢复后源码里保留了 IDA 误命中的名字
（`Concurrency::IThreadProxy`、`std::_Xlen()`、`…::details::VirtualProcessor::IsThrottled()`），
会产生 C2039/C2653/C2065 → **需要 IDA/注解层修掉 FLIRT 误命中或补类型**（本轮不在 inScope，记 GAP-4）。

---

## 6. 判据：`L1` 与 `ok`

### 6.1 `L1 ≥ 5`（硬线）——**预期保持 5；最终读数待 t9 窗口**

5 个 `match_L1`（`data/status/s4_baseline.json`）与我的变化文件集求交：

| L1 符号 | 文件 | 是否在 54 变化文件内 | 结论 |
|---|---|---|---|
| `CCBControl::GetControl` 0x004DC5B0 | `Combat/CCBControl.cpp` | ❌ 未变 | 字节不变 |
| `AStarPathFinder::IsInBounds` 0x004014E0 | `Misc/AStarPathFinder.cpp` | ❌ 未变 | 字节不变 |
| `TxtFile::TxtFile` 0x00431870 | `Misc/TxtFile.cpp` | ❌ 未变 | 字节不变 |
| `CameraSystem::BindToRoleSlot` 0x0041D980 | `Scene/CameraSystem.cpp` | ❌ 未变 | 字节不变 |
| **`ObjectCamera::Destroy` 0x0047C810（26B, 100%）** | `Role/ObjectCamera.cpp` | ✅ 在集合内 | **`Destroy` 文本逐字节未变**；唯一改动在**另一个函数** `SetCameraEyePosition`（0x0047C640）；且该文件单 TU 编译 **exit=0** |

`ObjectCamera.cpp` 的完整 diff（唯一 hunk）：

```diff
   v3 = (gbCamera *)operator new(0x178u);
   if ( v3 )
-  {
-    // [AUTO-COMMENTED] v4 = v3->gbCamera(position);
-  }
+    v4 = ((gbCamera *)v3);
   else
     v4 = 0;
   this->m_pCamera = v4;
```

（`{ }` 的消失不是我的改动：pre-stage3 文本本来就没有花括号；旧行为把唯一语句注释掉后，
后续阶段不得不补一对花括号——**那对花括号本身就是破坏性注释的副产物**。）

### 6.2 `ok`（S2）——单 TU 编译实测 + 逐条归因

方法：`tools/wine_cl.sh` + `build/build.ninja` 同 flag 集（`/O2 /Ob2 /Oi /Ot /Oy /GF /Gy /MT /Zp4 /W0`，
`-I<pal3/src> -I<include> -I<msvc6 Include> -I<vc6 Include>`），对 **54 个变化文件**在 base/new 各编译一次：

| | base | new |
|---|---|---|
| ok | **7** | **7** |
| fail | 47 | 47 |

**回归（base ok → new fail）1 个**：

| 文件 | 真实基线 | base | new | 错误码 | 归因 |
|---|---|---|---|---|---|
| `Misc/ChoseCompose.cpp` | **ok** | ok（0 错） | **fail（17 错：C2039 + C2227）** | C2039 `'__vftable' : is not a member`、C2227 `left of '->OnMessage' must point to class/struct` | **恢复的真实代码**：`ChoseCompose.cpp:35` 等处 `((void ( *)(ChoseCompose *, int, int, _DWORD))this->UIFrameWnd::UIWnd::__vftable->OnMessage)(this, 1000, 1, 0);` —— 这是**真的虚调用**（通过 `UIFrameWnd::UIWnd` 基子对象的分派表），但该基子对象在 `ChoseCompose` 里的**偏移文本里没有**（`store` 无 bases 表）→ 按 GAP-1 保留原样 → 无法编译。**不是新注释掉的语义，而是恢复语义的可见代价** |

**改善（base fail → new ok）1 个**：`Misc/ArcLocaleRole.cpp`（1 错 → 0 错）——
折叠后原先的非法 `__vftable` 访问变成合法的 `(*(void **)(…))`。

**真实基线为 ok 的 5 个文件细目**：

| 文件 | 真实 | base | new | 说明 |
|---|---|---|---|---|
| `Misc/ChoseCompose.cpp` | ok | ok | **fail** | 见上，**预计真实树 −1** |
| `Misc/UIStatic.cpp` | ok | fail(16) | fail(18) | 新增 2 条 `C2440`（`:262`/`:297`，`gbGfxManager *` → `int`），落在**恢复的赋值行**上；根因是 `m_textx`/`m_texty` 被注解成 `int`（同函数 `:264` 把它当 `gbTexture *` 用）→ **预计真实树 −1**，且这是**标注缺陷被暴露**（应在注解层修） |
| `Misc/UIPushButton.cpp` | ok | ok | ok | 2 行折叠（`*(float *)((void **)&(this[1])) = …`），无新错误 |
| `Misc/UITitle_BBTY.cpp` | ok | ok | ok | 1 行折叠（`vftable = (void ( **)(NPC *, int))(*(void **)(v9));`） |
| `Role/ObjectCamera.cpp` | ok | ok | ok | L1 保护，见 §6.1 |

**`ok` 外推（标注为「待窗口确认」）**：`53 − 2 + 1 = 52/198`。
**分母不变（198）** → 与基线可比。

### 6.3 新错误归因（13 个抽样文件，358 条新错误）

| 文件 | 新增错误 | 错误码 |
|---|---|---|
| `Script/PalScript.cpp` | 76 | C2039 C2059 C2065 C2102 C2143 C2146 C2227 C2228 C2230 C2440 C2446 C2653 C2660 C2664 C2676 C2882 |
| `Scene/SceneObj.cpp` | 64 | C2039 C2059 C2113 C2227 C2653 C2660 C2679 C2882 |
| `Misc/CCBUIPanel.cpp` | 50 | C2039 C2653 |
| `UI/StateUI.cpp` | 44 | … |
| `Misc/UIBigMap.cpp` | 38 | … |
| `Render/CScreenMode.cpp` | 28 | … |
| `Misc/UICaption.cpp` | 18 | C2039（18 行**全部**是限定基类 `this[1].UIWnd::__vftable`，属 GAP-1） |
| `Misc/LineupUI.cpp` | 15 | … |
| `Combat/CCBRoleState.cpp` | 4 | C2039 |
| `UI/PropUI.cpp` / `UI/UIScene.cpp` / `Role/RoleSystem.cpp` / `Misc/ChoseCompose.cpp` | 4/4/2/11 | … |

**归因方法（可复核，`/tmp/t7/attrib.py` → `/tmp/t7/attrib.txt`）**：把 new 独有错误的行号取出来，
对照 new 树该行文本，判它是否落在"折叠行（含 `void **`）"或"保留的 `__vftable` 行"：
**358 条中 151 条直接命中这两类**，其余 207 条是**级联**（同一 TU 内后续报错、以及
`pal3_vtbl_unk_*` 合成桩声明在解析失步下的连带报错）——例：`Render/CScreenMode.cpp:696`
`(((UICursor *)v18))->UICursor::IRender();` 本身两棵树都一样，只是前面恢复的限定 `__vftable`
行把解析器带偏后开始报错。**没有一条新错误来自"新被注释的语义"**（改后 `[VFTABLE]`=0、`[IDA_MISID]`=0，
`[AUTO-COMMENTED]` 只剩 standalone 形态）。

### 6.4 判据豁免合规性（captain 特别裁决）与 ROWTABLE 边界确认

| 裁决 | 合规性 |
|---|---|
| ① `L1 ≥ 5` 不回退 | ✅ 见 §6.1：5 个 L1 符号所在文件里 4 个字节未变；`ObjectCamera.cpp` 的 L1 符号 `Destroy` 逐字节未变且文件编译通过（最终 `match` 读数待窗口） |
| ② 不得再有真实语义被注释 | ✅ 改后 `[VFTABLE]=0`、`[IDA_MISID]=0`、`[AUTO-COMMENTED]` 只剩 `standalone`（无赋值 → 无被消费的值）：**没有任何带值的真实语义仍处于注释状态**（全树残留的 685/6/103 行全在孤儿文件，管线不可达） |
| ③ ok 若下降须逐条归因 | ✅ 见 §6.2/§6.3：回归仅 1 个文件（`Misc/ChoseCompose.cpp`，C2039+C2227，根因 = GAP-1 限定基类偏移不可知）；新增错误 358 条中 151 条直接落在恢复/折叠行，其余为级联；**无一条来自"新注释掉的语义"** |
| **ROW TABLE 判定顺序翻转**（t6 的 W-03） | ✅ **未越界**：`grep -n "ROWTABLE\|rowtable" pipeline/gen/stages/stage3_cleanup.py` → **0 命中**（该逻辑只在 `ast_transform.py`，属 t6 inScope）。我文件内**不存在** ROWTABLE 相关逻辑，故无需回报冲突。改后 `[ROWTABLE]` 计数 373→373、`[MISATTRIBUTED]` 153→153 均不变，可作为"未触碰 t6 领域"的实测证据 |

---

## 7. 代码改动逐处说明（`pipeline/gen/stages/stage3_cleanup.py`）

| # | 位置（改后行号） | 改动 | 说明 |
|---|---|---|---|
| 1 | 新增 `_VPTR_STORE_RE`（:638）/ `_VPTR_RHS_EVIDENCE`（:646）/ `_VPTR_RHS_DATA` / `_vptr_store_kind()`（:654）/ `_comment_vptr_stores()`（:677） | 用**判据**替换两处 blanket commenter | 原 `:722-743`（括号深度整段注释）+ `:745-749`（`^...__vftable[^;]*;.*$` 正则）删除；新 pass 同时修掉了旧实现的两个漏洞：(a) 不区分**块注释**里的 `__vftable`（旧实现把 `pal3_vtbl_unk_*() /* [VFTABLE-STUB] */` 这类**已合成桩的调用行整行注释掉**：真实树 12 行/6 文件，见 §1.4），(b) 带尾随 `//` 的行要走第二个正则 |
| 2 | 新增 `_needs_ptr_wrap()`（:717）/ `_fold_vftable_mask()`（:727-803），`run()` 内调用两 pass（:1017-1018） | 把 `__vftable` 访问折叠成 **offset-0 等价形式**，AST（tree-sitter）级、字节区间精确 | `X->__vftable → (*(void **)(X))`、`X.__vftable → (*(void **)&(X))`、`&X->__vftable → ((void **)(X))`、`&X.__vftable → ((void **)&(X))`；赋值目标是 vptr 时把 RHS 包成 `(void *)(…)`（字段声明类型是 `void *`）；**类型完全一致**（原本 `__vftable` 的类型就是 `void *`） |
| 3 | `_IDA_MISID_PATTERNS` 表 + 正则（原 `:751-759`） | **删除**，替换为说明注释 | 理由见 §5 |
| 4 | `_ast_cleanup()` 的 `insert` / `comment_vft` 两个 action（原 `:287-290`） | **删除 + 写入原意标注** | 全仓 grep 证明**无产生者**（只有消费者）：`'comment_vft'`/`'insert'` 不出现在任何 stage；`[IDA_VFTABLE]` 实测 0 处。原意（已记入注释）：为 IDA 层发射的 vftable 注释准备的 `[IDA_VFTABLE]` 标记（与 codegen 侧 `// [VFTABLE]` 不同拼写），IDA 层从未产生 → 不可达；其拼写是 handoff §2.3 点名的四种不可合并拼写之一 |
| 5 | `_is_vftable_assignment()`（原 `:49-55`） | **保留 + 标注为"被抢占的死路径"** | 该分支（`_ast_cleanup` 的 `'delete'`）改前被 blanket commenter 抢占；改后所有未限定的 `__vftable =` 目标都被折叠掉（实测 new 树**未限定赋值残留 0**），因此仍是死路径；保留是因为它是该模式的正确 AST 描述，一旦上游 pass 收窄即可恢复可达 |
| 6 | `_ast_cleanup()` 赋值分支（:298-321）+ 新 `_fold_ctor_call_value()`（:215-247） | 新增 `assign_ctor` action：`LHS = …Cls(args)…` → `LHS = …((Cls *)&obj)…` | 见 §4；`standalone`（无赋值）保持旧 `comment_ctor` 行为；`return` 分支不变 |
| 7 | 裸 except 逐处处置 | 见 §7.1 | — |

### 7.1 裸 except 逐处处置表

| 改前行 | 代码 | 风险 | 处置 |
|---|---|---|---|
| `:111` | `except Exception: return None`（`_try_resolve_vftable` 读注解 JSON） | 吞掉一切：JSON 结构/字典形状被改坏时，**所有** vtable 调用静默退化成桩 | 收窄为 `except (OSError, ValueError, KeyError, IndexError, TypeError) as _e` + **stderr 告警含类名与异常**（不再是静默） |
| `:628` | `except: pass`（legacy resolver#1 `_try_resolve_vtable`） | 裸 except，同上 | 收窄为 `(AttributeError, KeyError, TypeError, IndexError, ValueError)` + stderr 告警 |
| `:653` | `except: pass`（resolver#2 `_try_resolve_vtable3`） | 同上 | 同上 |
| `:678` | `except: pass`（resolver#3 `_try_resolve_vtable2`） | 同上 | 同上 |
| `:578` | `except (ValueError, OverflowError)`（`COERCE_FLOAT` 数值解析） | 已收窄，语义正确 | **保留不动**（并说明：只包住 `int()`/`struct.unpack` 的数值转换） |

行为兼容性：这三处 `try` 体只读 `store.struct_vtables`（一个 `dict[str, dict[int, str]]`），
上述异常类型覆盖了"缺 key / 形状不对 / 类型不对"的全部预期失败；**预期路径返回值与改前完全一致**，
差异仅在"意外异常不再被吞"。

---

## 8. 交付物与改动文件

| 类别 | 路径 | sha256 |
|---|---|---|
| 主实现 | `pipeline/gen/stages/stage3_cleanup.py`（954 → 1213 行） | `4ce4889520c72f9052d9dd85a69ecbb7fdfe7ec89144298d8f9e80c655dd2dc7` |
| 测试 | `pipeline/gen/test_pipeline.py`（33 → 44 个用例；新增/改写 14 个 stage3 断言） | `90a985a783aa6bc167c2b5c059f06e6126d134d3748f6183c7498aaf3f51fc6f` |
| 本报告 | `data/status/_cleanup_fix_vftable_comment.md` | — |

**测试命令与结果**：

```bash
cd pipeline/gen && python3 -m unittest test_pipeline
# Ran 44 tests … FAILED (failures=2)
#   失败 1: TestOopTransform::test_identifier_as_first_arg        ← t6 未提交的 ast_transform.py 多出一层括号，**与 t7 无关**
#   失败 2: TestOopTransform::test_complex_expr_as_first_arg      ← 同上
#   改前同口径基线：Ran 33 tests / failures=2（同样这两个）
```

新增/改写的关键断言：`test_vftable_assign_commented`（`&off_123456` 仍走注释）、
`test_vftable_assign_backtick_symbol_commented`（`` &Cls::`vftable' `` 走注释）、
`test_vftable_value_read_folded`、`test_vftable_address_keeps_pointer_type`（保 `void **` 类型，指针算术不变）、
`test_qualified_vftable_left_alone`（SceneObj `GlowObj` +8 的反例）、`test_vftable_chained_access_left_alone`、
`test_slot0_vftable_call_folded`、`test_mixed_normal_and_vftable`（`= 0` 不再被注释）、
`test_auto_commented_assignment_value_restored` / `_arrow_` / `_dtor_` / `_standalone_call_still_commented`、
`test_ida_misid_table_removed`、`test_ida_vftable_dead_branch_removed`。

---

## 9. 残留 GAP（未做 / 需别人做）

| ID | 内容 | 实测规模 | 建议归属 |
|---|---|---|---|
| **GAP-1** | **限定基类 `X->Base::__vftable`**：基子对象偏移在 decomp 文本里没有（`SceneObj`: `GlowObj` **+8**、`TaskMgr_SceneObjParam_SceneObj` **+40**，见 `asm/pal3/ida_structs.json.bases[].offset`），而 codegen 的 `store` **没有 bases 表** → 不能安全折叠 → 保留原样 → 新编译错误（`ChoseCompose` 回归的根因） | new 树 127 文件内 **116 行**（`Scene/SceneObj.cpp` 44、`Misc/UICaption.cpp` 18、`Data/CGameData.cpp` 8…） | 需在 `data.py`（t8 inScope）加 `struct_bases`，或在 export 层把 bases 一并给出；**不建议**在 stage3 直接读 JSON |
| **GAP-2** | `X->__vftable->M`（vptr 值被当对象用，`void *` 不可解引用）与 `X.__vftable[i]` | **31 + 8 行** | 需要 vtable **结构体类型**（`vtbl_XXXX`）在头文件里声明；属 emit_headers（t8） |
| **GAP-3** | **71 个孤儿 `.cpp`**：类名已不在当前 decomp 语料，当前管线永不重写；其中 `[VFTABLE]` **685** 行、`[AUTO-COMMENTED]` 14、`[IDA_MISID]` 6 → 我的改动**零影响**。同时意味着 `pal3/src` 有 71/198 个文件"编译但不可再生成" | 71 文件 | 需要 t9/t12/用户决策：重生成（改名映射）· 删除 · 或显式登记为手工维护 |
| **GAP-4** | 子类 (ii) 恢复后的 IDA 误命中名（`Concurrency::IThreadProxy`、`std::_Xlen()`、`…VirtualProcessor::IsThrottled()`）需要 **IDA/注解层**修 FLIRT 误命中或补类型 | 32 行（127 文件内）/ 全树 ~69 | annotation/IDA 层 |
| **GAP-5** | `Misc/UIStatic.cpp` 的 `m_textx`/`m_texty` 被注解成 `int`（同函数当 `gbTexture *` 用）→ 折叠后暴露 C2440 | 2 处 | annotation 层（正确的修法）；短期也可在 stage5（t8）把已有的 `_DWORD*` 指针→整型强制扩展到手写标量成员赋值 |
| **GAP-6** | 当前 `pal3/src` 与 decomp 语料**不同源**（decomp 15:44 重建后未重生成 src）→ 全树计数不能直接当"改后"读数 | 138 文件差异 | t9 窗口重生成一次即消解 |

---

## 10. 与交接文档数字不一致的清单（以实测为准）

| # | 交接文档 §4 t7 / §2.3 的说法 | 实测 | 依据 |
|---|---|---|---|
| 1 | 「仅约 **2.5%** 是真 vptr 存根」 | **0%（0/596 行；pass 层 1511 函数命中 0；语料层 108 条逐条枚举 0）** | §1.2/§1.3 |
| 2 | 「控制流头约 168、真实数据访问约 546、`__vftable` 当数据值 163、cast 44」 | 同源 base：E 控制流头 **26**、D 取地址 **90**、F 读入变量 **129**、B/C vptr 槽写入 **106**、G 分派 **21**、H 限定 **64**、I 其它 **64**（500 head + 96 续行 = 596） | §2.3 |
| 3 | 「`[IDA_MISID]` 子类 (i) **15 处**（NtTib/ExceptionList，注释后留**悬垂引用**）」 | 子类 (i) 为 **3 行**（127 文件内）/全树口径亦远小于 15；**悬垂引用 0 处**；真正的悬垂 **2 处属子类 (ii)** | §5 |
| 4 | 「`[AUTO-COMMENTED]`（233）中 **89 处**丢弃被使用赋值」 | 全树 233 = standalone 138 + assign **95**；同源 harness 127 文件内 assign **83**（全部恢复） | §4 |
| 5 | §2.3 `[MISATTRIBUTED]` **344** | 实测 **341**（t6 的 −3 已落地） | §2.2 |
| 6 | §2.3 `[VFTABLE]` **1935**（"当前树"） | 实测 **1935 一致 ✅**，但其中 **685 行（35.4%）在 71 个孤儿文件里**（交接文档未记录该事实）；**当前管线会重生成的 127 文件里只有 1250 行** | §2.2 |
| 7 | §4 t7「死分支 `:287-290` 无产生者」 | **确认**（全仓 grep：`'comment_vft'`/`'insert'` 无产生者；`[IDA_VFTABLE]` 实测 0） | §7 #4 |
| 8 | §4 t7「铁证锚点 `CCBCamControl.cpp:972-975` 未注释 vs `:983-986` 被注释」 | **确认**，并据此把 `(void *)<数字>` 归为**数据**证据 | §1.3 |

---

## 11. `files_changed` / `pending_window`

```json
{
  "task": "t7",
  "files_changed": [
    "pipeline/gen/stages/stage3_cleanup.py",
    "pipeline/gen/test_pipeline.py",
    "data/status/_cleanup_fix_vftable_comment.md"
  ],
  "evidence_artifacts_tmp_only": [
    "/tmp/t7/stage3_cleanup.ORIG.py", "/tmp/t7/gen.py", "/tmp/t7/count_hits.py",
    "/tmp/t7/base/pal3/src", "/tmp/t7/new/pal3/src", "/tmp/t7/base_vs_new.txt",
    "/tmp/t7/perfile.txt", "/tmp/t7/ac_pairs.txt", "/tmp/t7/shape2.txt",
    "/tmp/t7/corpus_rhs.txt", "/tmp/t7/compile_matrix.tsv",
    "/tmp/t7/compile_summary2.txt", "/tmp/t7/attrib.txt"
  ],
  "l1": {"measured": false, "expected": 5, "reason": "ObjectCamera::Destroy 文本未变且该文件单 TU 编译通过；其余 4 个 L1 文件不在变化集内"},
  "ok": {"measured_files": 54, "base_ok": 7, "new_ok": 7,
         "predicted_global": "52/198（53 −2 +1）", "measured_global": false},
  "pending_window": [
    "t9 窗口内重生成 pal3/src + probe S2 + match，取得权威 L1 / ok 读数（分母须仍为 198）",
    "重生成同时会消解 GAP-6（src 与 decomp 不同源）并给出孤儿文件（GAP-3）的处置依据",
    "GAP-1（限定基类偏移）需 data.py/export 提供 bases 表后才可折叠",
    "GAP-5（m_textx/m_texty 注解类型）需注解层修正"
  ],
  "not_done": [
    "未运行 apply/export/codegen/probe/match，未触碰 IDB（遵守窗口纪律）",
    "未折叠限定基类/链式/下标访问（GAP-1/2），未在 stage3 里新增读 JSON 的旁路依赖",
    "未修 t6 遗留的 2 个 TestOopTransform 失败（ast_transform.py 属 t6 inScope）"
  ]
}
```