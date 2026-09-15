# C-V 设计书：vtable 与基类布局的单一认领

> **状态**：**待独立复核**（不实施）。本文档只是设计，不含代码改动。
> **日期**：2026-09-15 · **仓库**：`/home/peng/workspace/PAL3Decomp` · **HEAD**：`e1064ee93`
> **量级**：`__vftable` 族 **718 条错误 / 43 类**；生成源码 **611 处** `Class::__vftable`；
> 布局漂移 **59 个多态头 + 145 个多继承头**
> **来源**：独立复核 `data/status/_cleanup_review_abc_plan.json`（子 agent `415003de`）提出方向，
> 本文档补全根因定位与判据。**captain 此前的两次成因臆造（「union 变体展开」）已引以为戒。**

---

## 1. 目标

让生成的头文件在 **VC6 下的 `sizeof` 与二进制尺寸一致**，并让 `__vftable` 引用可编译。

**这是字节匹配的前提**：当前即使 718 条名字错误全部修好，59/145 个类的对象布局仍与二进制不符，
`.h` 里成员的 `+0xNN` 注释与实际偏移**不一致**，字节匹配在原理上不可能。

**明确的非目标**：本设计不追求提升 `ok`/`L1` 数字。修好布局后，此前**靠错位"侥幸编译通过"**
的代码会暴露新错误，**数字可能先变差**——这与 M1 修复时「错误总数 +293 变难看」是同一模式。

---

## 2. 根因（两条，均非推测；每条给出实证）

### 根因 A：vtable 指针被两种表示同时认领

**证据链（每一环可复核）**：

1. 注解层统一把 vfptr 改名为 `__vftable`：
   `data/annotations/structs/gbMeshData.json:8` 与 `CTaskTpl_*.json:8` 均载
   `"note": "renamed vfptr -> __vftable (unified with IDA convention)"`
2. IDB 的 UDT 成员名因此是 `__vftable`（不是 `vfptr`）
3. 但 `pipeline/gen/stages/emit_headers.py:1727-1731` 的跳过判据只认旧名：
   ```python
   # Skip vfptr at +0 for classes with vtables (compiler-generated)
   if mname == 'vfptr' and off == 0 and class_vtable_slots(cls_name):
       start_off = off + 4
       continue
   ```
   ⇒ **该跳过永不触发**（`mname` 已是 `__vftable`）
4. ⇒ `+0` 落到 gap 生成（`:1735`）→ `.h` 里出现 `char _gap_000[4]; // +0x0`
5. 同时 `emit_headers.py:1836-1842` 对含 `_scalar_dtor` 的类自动发射
   `lines.append("    virtual ~%s() {}" % cls_name)`
   ⇒ **同一对象里 vptr 被算两次**（显式 gap 占 4 字节 + 编译器为 `virtual` 再插 4 字节）

**实证**：

```
pal3/src/UI/UIWnd.h:
  12:  char _gap_000[4]; // +0x0
  27:  virtual ~UIWnd() {}
  25:  // total size: 0x44 (68)          ← 二进制真值
注解 UIStatic… 同族：UIWnd binary_size=68

captain 的 VC6 实测（/tmp 最小复现）：
  template<int N> class Show;
  Show<sizeof(Plain{char[4];int;int})>            → Show<12>
  Show<sizeof(V1  {同上 + virtual ~V1()})>        → Show<16>   ← vptr 在 _gap_000 之外**又多 4 字节**
```

⇒ **多态类对象比二进制大 4 字节，且每个成员偏移都漂移**。受影响 **59 个头**（同时含
`_gap_000` 与 `virtual`）。

### 根因 B：基类区域被两种表示同时认领

**证据链**：

1. 注解用**两种**表示记同一段内存：
   - `base_class: ['PalScriptWaitObj','GlowObj','TaskMgr_SceneObjParam_SceneObj']` + `base_size: 44`
   - 且 `known_members['0'] = __vftable`、`known_members['0x44'] = m_fTimerLimit …`
     （即成员偏移从基类区域之后继续编号）
2. `emit_headers.py:978/1214/1262` 用注解 `base_class` 发射
   `class SceneObj : public PalScriptWaitObj, public GlowObj, public TaskMgr_SceneObjParam_SceneObj {`
3. 同时 gap 生成（`:1735`）按注解偏移补洞 ⇒ 发射 `char _gap_000[88]; // +0x0`
4. ⇒ **基类区域被 `public Base` 与 `_gap_000[88]` 双重认领**

**实证**：

```
pal3/src/Scene/SceneObj.h:14-16
class SceneObj : public PalScriptWaitObj, public GlowObj, public TaskMgr_SceneObjParam_SceneObj {
public:
    char _gap_000[88]; // +0x0
    float m_fTime;     // +0x58        ← 0x58 = 88 ✓ 与 gap 自洽
    // total size: 0x6F8 (1784)        ← 二进制真值
注解 SceneObj: base_size=44, binary_size=1784

复核者 VC6 实测：sizeof(SceneObj.h)=3196 vs 二进制 1784
```

⇒ 受影响 **145 个多继承头**（多基类 + `_gap_000` 并存）。

### 两条根因的共同形状

**同一段内存被两种表示同时认领。** A 是 vptr（gap vs `virtual`），B 是基类区（gap vs `public Base`）。
这解释了为什么"单独补一行 `void *__vftable;`"（复核者称 D3）**有害**：
它不删除已有的 `virtual`，反而**制造第三种认领**。

### 根因 C（captain 在设计过程中新发现，**可能推翻 B 的修法**）：`base_size` 的语义不一致

B 的修法依赖"`[0, base_size)` 就是基类区"。但实测**这个前提不普遍成立**：

| 类 | 基类尺寸之和（各基类注解 `binary_size`） | 注解 `base_size` | 自洽？ |
|---|---|---|---|
| `SceneObj` | `PalScriptWaitObj 8` + `GlowObj 32` + `TaskMgr_SceneObjParam_SceneObj 40` = **80** | **44** |  首个自成员在 `+68 (0x44)`，但基类实际占 `[0,80)` |
| `UIStatic` | `UIWnd 68` | **68** | ✅ |
| `ChoseCompose` | `UIFrameWnd` + `PalScriptWaitObj` | **80** | 待核 |

全仓统计（176 个带 `base_class` 且 `base_size>0` 的 struct）：
`base_size == binary_size` **6** 个 · `base_size < binary_size` **170** 个 · `>` **0** 个。

⇒ **`base_size` 的含义在类之间不一致**（"基类区宽度"还是"某基类的整体尺寸"）。
而 `apply_annotations.py:929-932` 与 `emit_headers.py` 的 gap 生成**都用它作 `[0, base_size)` 的界**。
**若直接用注解 `base_size` 计算布局，`SceneObj` 会得到 44 而非 80 的基类区宽度。**

**这条必须在 S1 一并实测**：正确口径应是 **`sum(sizeof(base) for base in base_class)`**（而非注解 `base_size`）。
captain 的 VC6 最小复现已证 **VC6 多基类顺序紧排、`sizeof` 之和 = 基类区**：

```
sizeof(B1)=8  sizeof(B2)=4  sizeof(B3)=12
sizeof(D : public B1, public B2, public B3 { int g; }) = 28 = 8+4+12+4   ← 无填充、无 vptr
sizeof(V1 {virtual ~V1(){}; int a;})      = 8    ← vptr(4) + int(4)
sizeof(DV : public V1, public V2 { int c; }) = 16 = 8+4+4                 ← 仍紧排
```

⇒ 3.3 的二分**有答案**：认领者可选 ①`public Base`，**但基类区宽度必须由 `sum(sizeof(base))` 计算，
不能用注解 `base_size`**。

### 这解释了 96 字节漂移的规模远超 4 字节

复核者报 `SceneObj` 的 `m_fTime` 落在 `+184` 而注解为 `+88`，差 **96 字节**——
单个 vptr（4 字节）解释不了。**根因 C 给出了候选解释**：基类区宽度被算错
（或 `public Base` 与 gap 叠加后产生更大的错位）。**此为假设，S1 必须实测确认。**

---

## 3. 设计：单一认领（single-claim）

### 3.1 不变式（本设计的核心，可机械检查）

> **对任意类 C，C 的每个字节区间 `[0, sizeof(C))` 有且只有一个构造认领。**
> 认领者只有三类：**① `public Base` 子对象**、**② 编译器插入的 vptr**（由 `virtual` 触发）、
> **③ 显式成员**（含 gap）。
> 且 **VC6 下 `sizeof(C)` 必须等于注解的 `binary_size`**。

### 3.2 根因 A 的修法

**认领者选 ②（编译器 vptr）**，理由：**原源码本无 `__vftable` 成员**——
`virtual` 才是忠实的再创作（`__vftable` 是 IDA 的类型系统 artifact）。

1. 把 `emit_headers.py:1728` 的跳过判据与注解**实际使用的名字对齐**
   ——改为与 `vfptr` **或** `__vftable` 任一匹配（**不硬编码单一拼写**，两者并存期都能工作）。
2. 跳过时**推进 `start_off` 越过 vptr 的 4 字节**（现有逻辑已如此），使后续成员偏移正确。
3. **不再为该区间发射 `_gap_000`**（这是第 1 步的直接后果）。
4. `virtual` 发射保持现状。⇒ vptr 由编译器插入，偏移 4，与二进制一致。

**未决（需复核者判定）**：`__vftable` 引用（611 处 `Class::__vftable`）在删除该成员后如何编译？
两个候选：(a) codegen 把 `X->__vftable` 改写为 `*(void **)X`（等价、可编译）；
(b) 由 `virtual` 隐式提供 vptr——C++ **不需要**也不允许显式访问它。
**captain 倾向 (a)**（显式、可机械验证），但这是需要裁定的点。

### 3.3 根因 B 的修法

**认领者选 ①（`public Base`）**，理由：与 A 同理——原源码写的就是继承。

1. 对**有 `base_class` 的类**：跳过所有落在 `[0, base_size)` 内的成员（**不发射 gap**），
   让 C++ 继承决定布局。
2. **未决（需复核者判定）**：VC6 的多重继承布局是否**恰好**把基类按 `base_class` 顺序
   依次放置、且各基类 `sizeof` 之和 == `base_size`？**我未验证**。若不成立，则须改为
   认领者 ③（保留 gap、不发射 `public Base`）——那会牺牲 C++ 继承的表达但保证布局。
   **这个二分必须先实测，再定方案。**

### 3.4 判据（新增硬门禁）

| 判据 | 内容 | 现状 |
|---|---|---|
| **P1** | **`sizeof` 一致**：对受影响类，VC6 编译 `.h` 取 `sizeof` == 注解 `binary_size` | **59/145 类不满足** |
| **P2** | **偏移一致**：`.h` 里每个成员的 `// +0xNN` 注释 == 注解偏移 | 待测 |
| **P3** | **单一认领**：`.h` 中不存在「同一区间被 gap 与 `virtual`/`public Base` 同时认领」 | 待测 |
| **P4** | 既有硬线不回退：`L1 ≥ 5`、`ok ≥ 53/198`、`oob == 0`、struct import 881/881 | 当前 6 / 56 / 0 / ✓ |

**P1/P2/P3 应实现为可复跑的门禁**（P1 需 VC6 编译，成本较高；P2/P3 可静态检查）。

### 3.5 实施顺序

| 步 | 内容 | 风险 |
|---|---|---|
| **S1** | **先实测 3.3 的二分**（VC6 下多基类布局是否等于注解 `base_size`）——这决定 B 的修法 | 低（/tmp 最小复现） |
| **S2** | 修根因 A（`vfptr|__vftable` 对齐 + 推进偏移），**单类验证 `sizeof` 与偏移** | 中 |
| **S3** | 按 S1 结论修根因 B | 中 |
| **S4** | `__vftable` 引用的 codegen 改写（3.2 未决项按复核结论） | 中 |
| **S5** | 加 P1/P2/P3 门禁；跑全链取权威 `ok`/`L1` | — |

---

## 4. 诚实清单：本文档未验证的部分

1. **根因 C 与 96 字节漂移的因果**——`base_size` 语义不一致已**实测确认**（上表），
   但它是否就是 `m_fTime` 漂到 `+184` 的**成因**，**未验证**，S1 必须先做。
2. **`__vftable` 引用的正确改写形式**（3.2 未决）——未验证。
3. **59/145 这两个数字的来源**是复核者的 VC6 编译统计，captain **只独立验证了 2 个类**
   （`UIWnd` 的机制、`SceneObj` 的 gap/偏移自洽），**未复跑全部 59/145**。
4. **P1 门禁的可行性**：需要为每个类单独编译取 `sizeof`，成本未估。
5. **本设计不保证提升 `ok`/`L1`**；也可能因暴露此前被错位掩盖的错误而**短期变差**。
6. **已实测的**（供复核者引用，不必重做）：VC6 多基类顺序紧排（`sizeof(D)=28=8+4+12+4`）；
   `virtual` 使 `sizeof` 增 4（`Show<12>` / `Show<16>`）；`vfptr` 跳过判据只认旧名；
   `base_size` 语义不一致（176 个样本：6 个 `==binary_size`、170 个 `<`）。

---

## 5. 请复核者重点判定的问题

1. **根因 A/B 的定位是否成立**？（尤其：A 的"跳过判据只认 `vfptr`"是否真的是 vptr 双计的唯一成因？
   有没有其它路径也发射 `_gap_000`？）
2. **3.2 的未决项**：`__vftable` 引用应选 (a) 改写为 `*(void **)X`，还是 (b) 别的？
3. **3.3 的二分**：认领者选 `public Base` 还是 gap？请给出 VC6 布局的实测（这是设计的关键前提）。
4. **是否漏了第三种双重认领**？（captain 已两次臆造成因，请特别检查有没有 B 之外的路径。）
5. **P1/P2/P3 判据是否可机械实现**，还是某个在原理上做不到？
6. **S1–S5 的顺序是否合理**？有没有更该先做的一步？
7. **本设计是否会破坏既有硬线**（`L1`/`ok`/`oob`/struct import）？