# 「尺寸可疑 9 条」的分配点取证（2026-09-19，§49.4 第 (1) 项）

> 目标：为 `data/status/_structural_contradictions.json` 里 `verdict=size_suspect` 的 9 条
> 取**真实尺寸**的二进制证据。本文只记证据与结论，**不含任何 annotation 改动**。

## 1. 方法与工具

新增 `tools/alloc_point_size.py`（分配点分析）。判据是 MSVC 6 的构造函数惯用法，逐条可在
`original/PAL3.exe.asm` 里核对：

```
push    <N>              ; Size
call    ??2@YAPAXI@Z     ; operator new(uint)
...
mov     ecx, eax         ; this = 刚分配的对象
call    <ctor>           ; ⇒ sizeof(ctor 所属类) == N
```

全量扫描结果：**304 个分配点，其中 141 个能挂到 ctor**（`--scan`）。
命令：`python tools/alloc_point_size.py --scan --json out.json`、
`--ctor 0xADDR`、`--class Name`、`--callers 0xADDR`。

**为什么不能只扫 `operator new` 的实参**：实参是"被分配对象"的尺寸，不是"调用者所属类"的尺寸 ——
§49.1 的失败尝试正是栽在这里。唯一可靠的挂钩是**紧随其后的 ctor 调用**，而 ctor 必须先是**真的** ctor。

## 2. 已定案（A 级证据）

### 2.1 `CCBProtectWindow` 真实尺寸 = **0x0A48 = 2632**（注解写 176，差 15 倍）

分配点 `sub_5125E0 + 0x9F`（asm 行 413240–413249）：

```
413240|                 push    0A48h           ; Size
413241|                 call    ??2@YAPAXI@Z    ; operator new(uint)
413243|                 mov     [esp+1018h+var_1010], eax
413244|                 test    eax, eax
413247|                 push    esi
413248|                 mov     ecx, eax        ; this = 新对象
413249|                 call    sub_5160A0      ; CCBProtectWindow ctor
```

**为什么 `sub_5160A0` 就是它的 ctor（不是"看起来像"）**：

1. `sub_5160A0`（asm 行 419268）本体写 vtable：`mov dword ptr [esi], offset off_5704A8`（行 419290）；
2. `off_5704A8` 的数据区（行 539364）的唯一代码 XREF 是 **`sub_5160A0+2C`** ⇒ 只有它安装这张表；
3. vtable `0x005704A8` 在**全部注解里只有 `CCBProtectWindow` 声明**（7 槽）；
4. 槽位与注解方法表吻合：槽 2 = `sub_518E30`、槽 3 = `sub_5164D0`，注解里确有 `0x00518E30` / `0x005164D0`。

> 注意这条同时说明：**注解现在的 `binary_size: 176` 是错的**，而且
> `_structural_contradictions.json` 里 `0x0051F0A0` 访问 `this+2883` **仍然 > 2632** ——
> 那条矛盾**不会**因为改尺寸而闭合，仍需按"归属"追（与 §48 的划分相反，它是归属问题）。

### 2.2 附带发现：3 个"方法"是编译器生成的静态初始化 thunk

`CCBProtectWindow.json` 把这三个地址当方法（其中一个还当 **ctor**、一个当 **dtor**）：

| 地址 | 注解名字 | asm 实况（行号） |
|---|---|---|
| `0x0051D6D0` | （未注解） | `jmp sub_51D6E0`（行 431120，`.data:00580844` 的 XREF） |
| `0x0051D6E0` | `CCBProtectWindow`（ctor） | `mov eax, ds:dword_5705B0; mov dword_17AD59C, eax; retn`（行 431130–431133） |
| `0x0051D6F0` | `~CCBProtectWindow`（dtor） | `jmp sub_51D700`（行 431143） |
| `0x0051D700` | `Reset` | `fld ds:dword_5705B0; fadd st, st; fstp flt_17AD598; retn`（行 431153–431157） |

它们没有 `this`、只碰全局，是**静态初始化簇**（`.data` 里被初始化表引用）。
⇒ 真正该做的是把 `0x0051D6E0/0x0051D6F0/0x0051D700` 标成 `skip`（理由：编译器生成的静态初始化 thunk），
并**补上真正的 ctor `0x005160A0`**（它现在**不在**注解方法表里）。

### 2.3 `UIRenderObj`：对象是**函数内静态**，不是堆分配（尺寸注解 4 明确错）

- 构造点（asm 行 8474–8476，在 `sub_405C00` 里）：
  `call sub_5415F0` → `mov ecx, eax` → `call sub_541640`；
- `sub_5415F0`（asm 行 485493）是**静态局部变量的守卫**：首次调用时
  `mov ecx, offset dword_1894D90` → `call sub_541470` → `push offset unknown_libname_237; call _atexit`，
  然后 `mov eax, offset dword_1894D90; retn` —— 返回的是**静态对象地址 `0x1894D90`**，不是 `operator new` 的结果。
- 真 ctor `sub_541640`（注解里已正确标为该类 ctor）写 `[esi+0Ch]`、`[esi+1Ch]`、`[esi+1Dh]`、`[esi+ecx*4+10h]`
  ⇒ **尺寸 ≥ 0x1E**，而注解写 4。**下界，非精确值**。

## 3. 方法论修正（对 §49.4 的交接）

§49.4 写的"做**分配点分析**（`operator new` 实参 / `new X` 调用的紧随 ctor）"**只对堆分配的对象成立**。
本批 9 条的实测分布是三类，取证路线各不相同：

1. **堆分配**（本例 `CCBProtectWindow`）⇒ 分配点分析，`push N` 即精确尺寸；
2. **函数内静态 / 全局实例**（本例 `UIRenderObj`；`0x1894D90`）⇒ 没有分配点。取证改为
   真 ctor 的**写入脚印**（最大 `[this+off]` + 写宽度）或 `memset(this,0,N)` 的 N；
3. **注解的 ctor 是 thunk**（本例 `CCBProtectWindow`）⇒ 必须先用 **vtable 写入点**
   （`mov [ecx], offset <vtbl>` + 该 vtbl 的数据 XREF）把**真 ctor** 找出来，否则一切挂钩都是错的。
   查 vtable 归属的现成办法：在 `data/annotations/structs/*.json` 里搜 `vtables[].addr`（本例只有 CCBProtectWindow 声明）。

## 4. 未解（下一轮）

| 类 | 现状 | 下一步 |
|---|---|---|
| `Combat`（size 4，0 成员） | 注解方法 `LogMessage`/`GetSlotCount`/`HandleControlCmd` 等彼此不像同类 | 找真 ctor 或先质疑归属 |
| `MatrixStack`（size 4，0 成员） | `BeginSceneWithRotation` 已带 `_misattrib_evidence: max_offset=784>4` | 同上；先看 `0x0052FC60` 调用点上 `ecx` 的来源 |
| `MiniGame2Scene`（size 4，0 成员） | `UpdateMiniGame2` 带 `_misattrib_evidence: max_offset=3628>4` | 同上 |
| `MiniGame3`（size 4，0 成员） | 有 5 个 thiscall 方法 | 同上 |
| `UIManager`（size 4，0 成员） | 仅 `Render`/`LoadShadowTexture` | 同上 |
| `UIRenderObj`（size 4） | 2.3 已给下界 ≥0x1E | 取精确尺寸：静态对象 `0x1894D90` 的**相邻静态对象间距**或 ctor 完整脚印 |
| `CCBProtectWindow`（size 176） | 2.1 已给精确 2632；`0x51F0A0` 矛盾未闭合 | 尺寸改动入批；`0x51F0A0` 转归属线 |

**落盘纪律**：证据齐了用 `tools/apply_annotation_batch.py --run-pipeline` 一次落地，
并验证 `new_failures` 为 0、L1 不回退。

## 5. 落盘实测（A-B-A 控制实验）—— **该批回退，不落盘**

把 4 条（`CCBProtectWindow` 尺寸 176→2632 + 3 个 thunk 标 `skip`）经
`tools/apply_annotation_batch.py`（新扩展 `set_size` / `skip_method` 两种 kind）落盘并跑完整管线。
`check` 通过（0 errors / 13 warnings），但**未过验证清单**：

| 腿 | 注解 | IDB 构建 | 额外 apply | globals.h / cpp | 总错误 | matched | **L1** | unresolved-synth |
|---|---|---|---|---|---|---|---|---|
| 1（基准） | 回退 | `init --force` | 否 | 2743 / 2686 | 2456 | 222/256 | **21** | 28 |
| 2（控制） | 回退 | `init --force` | **是** | **2746 / 2689** | **2484** | 222/256 | **21** | 28 |
| 3（改动） | 落盘 4 条 | `init --force` | **是** | **2746 / 2689** | **2484** | 219/253 | **20** | 26 |

**读法（两两对比，各只差一个变量）**：

* **腿 2 vs 腿 1**：只多跑了一次 `apply`（`--run-pipeline` 自带的那一步），globals 就变了 +3、
  总错误 +28 ⇒ 这两项**与注解改动无关**，是"多跑一趟 apply"的状态漂移。
  **教训：验证清单的 A/B 必须让两条腿的 `apply` 次数一致**，否则会把状态漂移算到改动头上。
* **腿 3 vs 腿 2**：globals 与总错误**逐项相同**，**只有 match 不同**
  （matched 222→219、L1 21→20、unresolved-synth 28→26）⇒ **L1 的损失确实由这批注解改动引起**。

**判定**：验证清单第 2 项（L1 不得回退）不满足 ⇒ **本批不落盘**。
`data/annotations/structs/CCBProtectWindow.json` 已回退（176 + 原名），共享棘轮保持发布值（L1 18）；
`data/status/annotation_fix_batch.json` 保留这 4 条为**待落盘**（证据不变，但需先拆开定位代价来源）。

**这与 `gotcha_wrong_arithmetic_can_be_accidentally_load_bearing` 同型**：
"证明了它是错的" ≠ "证明了改成对的是安全的"。尺寸 176 确实与二进制不符，
但改成真值 2632 会改动 `CCBProtectWindow.h/.cpp` 的生成形态，连带丢掉 1 个字节全同函数、3 个可匹配符号。

**下一步（拆分定位）**：

1. 只落 `set_size`（不带 skip）→ 量 L1；
2. 只落 3 条 `skip_method`（不带 set_size）→ 量 L1；
3. 找出腿 3 丢掉的那个 L1 是哪个函数（需在两次 match 里保留 `pal3_registry.jsonl` 的逐符号结果做 diff）；
   若是 `CCBProtectWindow` 自己的方法，则按 CLAUDE.md「字节匹配 > 代码优雅」
   **优先保字节匹配**：回退尺寸，只落能保住 L1 的那部分。

## 6. 拆分定位（同日续做）与最终处置

把 4 条拆成"**只落 `set_size`**"重测（IDB 构建路径与 `apply` 次数三条腿全部对齐 = `init --force` 2 趟 + 1 趟 `apply`）：

| 腿 | 落盘内容 | globals.h/cpp | S2 ok/total | matched | **L1** | partial | synth |
|---|---|---|---|---|---|---|---|
| 控制 | 无（HEAD） | 2746/2689 | 70/201 | 222/256 | **21** | 173 | 28 |
| 只落尺寸 | `set_size` | 2746/2689 | 70/201 | 222/256 | **21** | 173 | 28 |
| 落 4 条 | `set_size` + 3×`skip_method` | 2746/2689 | **71/201** | 222/256 | **20** | 176 | 26 |

⇒ **S2 的 +1 与 L1 的 −1 都来自那 3 条 thunk 修正**；`set_size` 对全部稳定指标**中性**。

**逐文件定位（L1 丢在哪）**：`pal3/src/Combat/CCBProtectWindow.cpp`
从 `funcs=10 matched=9 L1=1 partial=6` 变成 `funcs=7 matched=6 L1=0 partial=6`；
控制态该文件名下有一个 `match_L1 100%` 的符号 `UIWnd::`scalar deleting destructor'(uint)` @ `0x004518E0`
（即"为这个类发射的析构/scalar-deleting-dtor 桩"），改动态它不再挂在该文件下。
这与"把注解里的 `~CCBProtectWindow`（实为 `0x0051D6F0` 静态初始化 thunk）标 skip/改名"直接相关
—— 又一次「错的标注在意外顶住字节匹配」。

**最终处置**：

* **落盘**：`set_size`（176 → 2632）。证据见 `data/annotations/CHANGE_LOG.md` 2026-09-19 条目；
  验证 = `new_failures 0` + L1 21→21。
* **不落盘**：3 条 thunk 的 `skip`/改名 —— 被 L1 硬线挡下（+1 S2 换 −1 L1，按项目优先级不接受）。
  证据保留在本文 §2.2，供将来找到"既修 thunk 又不丢那个桩"的办法后再落。

**顺带修正的度量结论**（已并入 `docs/knowledge/gotcha_error_census_not_a_pure_function_of_the_tree.md`）：
总错误数**连同一状态重跑都不稳定**（控制腿两次分别 2484 / 2466）。因此 A/B 只允许建立在
**文件级 pass→fail 翻转 + L1** 上；本轮这两项在所有腿里都可复现。

## 7. 续做：`UIRenderObj` 取到精确尺寸；`UIManager` 取到下界

### 7.1 `UIRenderObj` 真实尺寸 = **0x20 = 32**（注解写 4）——两侧夹逼

| 方向 | 证据 |
|---|---|
| **对象首址** | `sub_5415F0`（函数内静态的守卫）返回 `mov eax, offset dword_1894D90`，并在首调用时 `mov ecx, offset dword_1894D90; call sub_541470; push offset …; call _atexit`（asm 行 485493-485510）⇒ 对象就是全局 `0x1894D90`。 |
| **下界 ≥ 0x1E** | 真 ctor `sub_541640` 写 `[esi+0Ch]`、`[esi+1Ch]`、`[esi+1Dh]`、`[esi+ecx*4+10h]`（最大 0x1D）。 |
| **上界 ≤ 0x20** | `0x1894D90 + 0x20 = 0x1894DB0` 是**该静态变量自己的 MSVC 守卫字节**（`sub_5415F0` 里 `mov cl, byte_1894DB0` / `mov byte_1894DB0, dl` 读写它，行 485495/485502）——它是**独立符号**，不属于对象 ⇒ 对象不可能越过它。 |

两侧合起来 ⇒ **size = 0x20 = 32**（0x1E ≤ size ≤ 0x20 且需 4 字节对齐）。
数据区也与之一致：`dword_1894D90 dd 8 dup(?)`（8×4=0x20）紧接 `byte_1894DB0`（asm 行 578978-578980）。
**已入批**（`data/status/annotation_fix_batch.json`，待下一次攒批落盘）。

### 7.2 `UIManager` 只拿到**下界 ≥ 0x44**（注解写 4）

* 实例是**全局**：4 处调用点都是 `mov ecx, offset dword_C11758`（asm 行 6319/8243/46644/46659），
  其中行 8243 后的 `call sub_41F370` 就是注解里的 `UIManager::Render`。
* **注解的 `LoadShadowTexture`（`sub_41F5E0`）其实是这个全局实例的就地初始化函数**：
  行 6319-6320 `mov ecx, offset dword_C11758 ; call sub_41F5E0` 发生在静态初始化序列里；
  它 `mov esi, ecx` 后只做三件事：取 `shadow.tga` 纹理写 `[esi+4]`、
  `NewRenderEffect("gfxscript\\shadow.gbf")` 写 `[esi+8]`、
  `NewRenderEffect("gfxscript\\shadow_F2.gbf")` 写 `[esi+0Ch]`（asm 行 46957-46991）。
* 下界来自 `sub_41F370`：读/写 `this+0x04 / +0x08 / +0x0C`，并 `lea esi, [ebx+40h]`（+0x40 处有数组）
  ⇒ **size ≥ 0x44**。
* **上界未取到**：数据区里 `dword_C11758 dd 2 dup(?)` 之后是 `dword_C11760`（自身被 `sub_4B6E20` 等按绝对地址访问，
  很可能就是本对象的 `+8` 成员），再往后是 `dd 449h dup(?)` 的无类型区，直到 `flt_C12888` —— 没有紧邻的独立符号可当边界。
  ⇒ 下一轮的取法：找该类的 **vtable 写入点**（`mov [reg], offset <vtbl>`）或 `memset(&dword_C11758,0,N)`。

## 8. 第 12 轮：`tagEffClass` 的尺寸拿到**两侧证明**，并牵出 `CEffMgr` 20 个成员与二进制矛盾

### 8.1 `sizeof(tagEffClass) = 72`（两侧夹逼，与 `UIRenderObj` 同型）

| 方向 | 证据 |
|---|---|
| **下界 ≥ 0x48 = 72** | `sub_4CDAE0` 的循环把每条记录的第 3 个字段当**指针**用（`mov ecx,[esi] ; mov eax,[ecx] ; call [eax+0Ch]`），该字段位于记录内 **+0x44** ⇒ 记录尺寸 ≥ 0x48。 |
| **上界 ≤ 72** | `CEffMgr` 的 `m_EffClass tagEffClass[32]` 起始于 **+0x1C**，而下一个成员 `m_EffTable` 起始于 **+0x91C**（asm 独立读到）⇒ 每条记录 ≤ (0x91C−0x1C)/32 = **0x900/32 = 72**。 |
| **算术吻合** | `0x1C + 32×72 = 0x91C` —— **正好**落在 `m_EffTable` 的起始处（实测输出：`32*72 = 0x900 ; 基址+该值 = 0x91C ⇒ 吻合!`）。 |

⇒ **`tagEffClass.json` 的 `binary_size = 4` 是错的，应为 72。**

### 8.2 但**不能单独落盘**：数组跨度内压着 20 个与二进制矛盾的 CEffMgr 成员

修正后 `tagEffClass[32]` 的跨度是 `0x1C..0x91C`，而 `CEffMgr` 现注解了 **20 个成员落在该区间内**
（`m_fEffParam`@0x9C、`m_fPosX`@0xA0 … `m_pEffectArray`@0x800）。逐条对照 asm 后**类型直接冲突**：

| 偏移 | 注解 | asm 实测（同一 72 字节记录的对应位置） |
|---|---|---|
| `0xA0` | `m_fPosX` **float** | 循环第 1 次迭代把 `0xA0` 当**字节**读（`mov al,[esi-8]`） |
| `0xA8` | `m_fPosZ` **float** | 循环把 `0xA8` 当**指针**用（`mov ecx,[esi] ; call [eax+0Ch]`） |

⇒ 这 20 个成员**不是**那 20 条记录里的字段；它们对同一批字节给出了与指令不符的类型。

**处置（本轮不动手）**：尺寸证明成立，但它与这 20 个成员**互斥** —— 只改尺寸会让数组跨度压住这些成员（overlap），
只删成员又会丢失待查信息。正确做法是一次**协同改**：
1. 落 `tagEffClass.binary_size = 72`；
2. 把跨度内那 20 个成员按 asm 重新判定（改成记录内字段并搬进 `tagEffClass`，或按"与指令不符"删除）；
3. 跑完整管线 + 验证清单（`new_failures 0`、L1 不回退）。

在此之前 `sub_4CDAE0` 的归属（疑似 `CEffMgr`）一并挂起 —— 见 `_attribution_evidence_20260919.md` §10。




