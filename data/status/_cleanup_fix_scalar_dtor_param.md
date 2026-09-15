# H 落地记录：codegen 丢失析构函数语义形参

> **任务**：`docs/specs/2026-09-15-annotation-tombstone-task.md` §6 的 H
> **日期**：2026-09-15 · **执行**：captain
> **缘起**：干净重建后 `AStarPathFinder.cpp` ok→fail（`L19 C2296 '&' : illegal, left operand has type 'char []'`），
> 由独立对抗性复核子 agent `2c66861a` 指出「与 ArcLocale 无关、真根因是 codegen 丢失 scalar-dtor 形参」

---

## 1. 根因（三层，全部实测）

### 层 1：`stage1_structural.py` 无差别剥掉 dtor 全部形参

```python
# pipeline/gen/stages/stage1_structural.py:177-190
# Dtor: strip all params
if ctx.is_dtor and params:
    ...
    edits.append((open_paren.end_byte, close_paren.start_byte, b''))
```

该分支的本意是剥掉**隐式的 `Cls *this`**，但当签名里除 `this` 外**还有真实语义形参**时，
该形参名会变成自由变量。

### 层 2：真实 sig 含显式 `this`

captain 用调试注入取得的真实值（这段是修复的关键，第一版即因想当然而静默失效）：

```
SIG='virtual void *__thiscall(AStarPathFinder *this, char a2)'
  method_name='~AStarPathFinder'   cls='AStarPathFinder'   is_dtor=True
```

⇒ 参数是 **2 个**（`this` + `a2`）。必须先剔除 `this` 才能看到被剥掉的那个。

### 层 3：注解与 decomp 的 dtors 签名不一致（副发现）

| 来源 | 签名 |
|---|---|
| `data/annotations/structs/AStarPathFinder.json` 的 `methods["0x00401030"]` | `void *__thiscall(char a2)`（**无 `this`**） |
| `asm/pal3/decomp/AStarPathFinder_~AStarPathFinderchar_00401030.json` | `virtual void *__thiscall(AStarPathFinder *this, char a2)`（**有 `this`**） |

真实 sig 走 decomp（`collect.py` 用 decomp 的 `signature` 字段）。**两处不一致本身是数据缺陷**，已登记待办。

---

## 2. 为什么这个缺陷"时隐时现"（这是本轮最值得记的机制）

函数体写 `if ( (a2 & 1) != 0 )`，而 `a2` **不是**已声明的参数。它能否编译**完全取决于
`globals.h` 里恰好有没有同名全局**：

| 代次 | `globals.h` 里 `0x590638` 的名字 | 结果 |
|---|---|---|
| 增量（16:55 前） | `extern int a2; // 0x586194` | `a2 & 1` **合法** → 侥幸 ok |
| 干净重建后 | `extern CHAR a2[]; // 0x590638`（IDA 自动名换代） | `a2 & 1` → **`C2296`** |

⇒ 这是**「看 `globals.h` 里恰好有没有那个名字」的假通过路径**，不是稳定的正确产物。
且它**长期存在**：`2026-09-01` 基线里同一行就是 `C2065 'a2' : undeclared identifier`（同根因，当时无同名全局）。

---

## 3. 修法与语义论证

**落点**：`pipeline/gen/stages/stage5_fixup.py` 的 `_run_inner()` **末尾**（必须在 `return code` 之前，
因为该函数前面多处 `code = re.sub(...)` 会整体覆盖 `code`——第一版放在中间即因此**静默失效**）。

**判据**：sig 剔除 `this` 后恰剩 **1** 个形参，且该形参类型是整数标量
（`char`/`int`/`unsigned int`/`__int8`/`__int16`/`__int32`）、名字是 IDA 的 `aN` 风格。

**动作**：把函数体内对该形参名的引用**替换为常量 `1`**。

**这不是猜测**，是两个直接推论：

1. **该标识符不可能是合法的**：它的声明已被 stage1 删除，函数体内无任何声明
   ⇒ 替换不可能覆盖真实的局部变量或参数。即便 `globals.h` 恰好有同名全局，
   替换后语义**恰好更正确**（原先只是遮蔽该全局侥幸通过）。
2. **flag 值由调用点确定**：VC6 标量删除析构的 deleting flag 语义为
   「`a2 & 1` 非零则 `operator delete(this)`」。而该析构体**自身**负责 `operator delete`，
   所以它只在 `delete p` 路径上被调用 ⇒ **flag 恒为 1**。
   若 `a2` 为 0 则对象不被释放，但它又正是靠 `delete` 进入的 ⇒ **double-free**，自相矛盾。
   故常量 `1` 是唯一自洽取值。

**未覆盖的形态（刻意不动）**：全树 9 个 dtor 中，多参形态
（例 `CEffgbParticle::~CEffgbParticle(int,int,int,int *,int,int)`）**无法从单点确定**各参数取值，
本处不猜。若要根治，应改为**保留形参**的方案（那需要同时解决 `.h` 里 C++ 析构不可带形参的约束）。

---

## 4. 实测验证

| 读数 | H 前 | H 后 |
|---|---|---|
| `pal3/src/Misc/AStarPathFinder.cpp` | **fail**（`error_count=1`，`L19 C2296`） | **ok**（`error_count=0`） |
| `ok` | **52/198** | **53/198** |
| `L1` | 5 | **6** |
| 生成源码 L19 | `if ( (a2 & 1) != 0 )` | `if ( (1 & 1) != 0 )` |

**`L1` 从 5 提升到 6**（棘轮 `previous 5 -> current 6`，**净提升**），
新增的 L1 函数是：

```
pal3/src/Misc/AStarPathFinder.cpp   AStarPathFinder::IsInBounds(int,int)   va=0x004014E0  size=5
```

注意 `0x004014E0` 正是「t6 桩槽案」（`docs/specs/2026-09-15-cleanup-scan-t5-rules.md` §1）里
`0x004014F0`（`xor al,al; ret 8`）的**紧邻前后者**（`0x004014E0` = `xor eax,eax; ret 8`）——
同一个文件的修复把它带回了 L1 集合。

---

## 5. 判据总表（H 后）

| 判据 | 硬线 | 现状 | |
|---|---|---|---|
| `struct import` | 881/881 | **881/881** | ✅ |
| `L1` | ≥5 | **6** | ✅（净提升） |
| `ok` | ≥53/198 | **53/198** | ✅ |
| `oob` | ==0 | **0** | ✅ |

---

## 6. 遗留（诚实清单）

### 6.1 棘轮仍报 4 项（`compile_regression.py` exit 1，非本轮 H 引入）

`AStarPathFinder.cpp` / `ChoseCompose.cpp` / `ExternalStatistics.cpp` / `UIStatic.cpp`
（`Net change: 0 files`）

| 文件 | 归因状态 |
|---|---|
| `AStarPathFinder.cpp` | **已由 H 修复**（本轮 ok 恢复）；棘轮基线尚是修复前的，故仍列名 |
| `ChoseCompose.cpp` | t7 判据豁免（GAP-1 限定基类偏移不可知），**已归因**（复核者实测 **19** 错，非 17） |
| `UIStatic.cpp` | **已归因**：`m_textx`/`m_texty` 被注解成 `int`（同函数当 `gbTexture *` 用）⇒ **标注缺陷被暴露** |
| `ExternalStatistics.cpp` | t7 删 `_IDA_MISID_PATTERNS` 的**半成品恢复**（扫描清单原建议是「应重命名保留」）——**K，未处置** |

### 6.2 其它

- **注解与 decomp 的 dtor 签名不一致**（§1 层 3）：`AStarPathFinder.json` 的签名缺 `this`。待办。
- **多参 dtor 形态未覆盖**（§3 末）。
- 那 3 个"其它单参 dtor"（`PAL_GDB`/`CCBMagicWindow`/`CCBLineupWindow`）**不在当前树**——
  属复核者发现的 **71 个"孤儿 `.cpp`"**（当前管线只重生成 127/198，类名已不在当前 decomp 语料）。
  它们既不消耗也不受益于本次改动。

---

## 7. 相关文件

- 任务书：`docs/specs/2026-09-15-annotation-tombstone-task.md`
- 修改：`pipeline/gen/stages/stage5_fixup.py`
- 复核来源：`data/status/_cleanup_review_arc_locale_dangling.json`
  （`independent_findings_not_reported_by_captain` 一节）