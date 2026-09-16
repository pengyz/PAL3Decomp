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
---

# R13 C-V 前提的**决定性实测**：**判定 FAIL**（captain，2026-09-15）

> **这是方案 4 的 P3 判据的第一次真正执行。** 结论推翻复核者 `ad32c455` 的"结构同构 ⇒ 可行"乐观预期。

## 实验设置（两侧分离，避免 P3 的恒真陷阱）

| 侧 | 工具 | 取什么 |
|---|---|---|
| **编译产物侧** | **新增 `tools/coff_vtable.py`** | 遍历 COFF 符号表找 `??_7<Cls>@@6B@`（vftable 符号），读其 section 的 DWORD 序列，按 **DIR32 重定位**解出**槽位函数符号名** |
| **二进制侧** | `tools/vtable_scanner.py` | 从 ctor 实际写入的 vptr 地址读槽位 |

**`coff_vtable.py` 自检 PASS**（`--selfcheck`）：固定源码编出 `??_7B@@6B@` / `??_7D@@6B@`，
槽序 `[0]=??_E<Cls>`（虚 dtor 占槽 0）、override 原位替换、未替换槽指基类 —— 全部正确。
**保留了复核者点名的坑**：reloc 的符号索引必须按**原始 COFF 索引**建映射（aux 占位会错位）。

## 结果一：CEffCylinder（F2 缺口类）**根本不产出 vtable**

```
编译含 CEffCylinder.h 的 TU（3 种：仅 include / 定义虚函数 / 全局实例化）：
  vtable 符号: **0**          ← 三次都为 0
  .bss 大小 = **4344**（二进制 4292，差 +52，与复核者实测吻合）
  产出符号只有 ??0CEffCylinder@@QAE@XZ / ??1CEffCylinder@@QAE@XZ（**QAE=非虚**）
```

原因：其多态基类 **`CEffObj` 的生成头里只有一个 `char _gap_000[4]`、零 `virtual`**
（`CEffObj` 注解 `binary_size=12`、`+0=__vftable`、`methods=[]` —— **正是 F2 的数据缺口**）。
⇒ **编译器无处生成 vptr；`virtual` 只能声明新槽，不能凭空造出 vptr。**

**把 `~CEffCylinder` 改成 `virtual`（产生 `??1CEffCylinder@@UAE@XZ`）后仍为 0** ⇒ 不是虚析构的问题。

## 结果二：CEffAction（**能**产出表）——但**逐槽顺序与二进制不同**

对照组 `CEffAction.h`（同样继承 `CEffObj` + `CTaskTpl_...`）**产出 vtable** ✓（7 槽），
说明**不是编译器能力问题**，是供给/建模问题。

| 槽 | 二进制 @`0x56F5E4` | 编译器合成 |
|---|---|---|
| 0 | `0x4C0540` ExecutePasses | `ExecutePasses` |
| 1 | `0x4C0650` ? | `ResetState` |
| 2 | `0x4C0640` ResetState | `UpdateFrame` |
| 3 | `0x408BD0` NullCallback | `AllocRenderTarget` |
| 5 | `0x4C0740` UpdateFrame | `RenderScene` |
| 7 | `0x4C0520` AllocRenderTarget | — |
| 9 | `0x4C0920` PrepareEffect | — |

- **集合相同** ✓（两者都含那 7 个函数）
- **逐槽顺序不同** ✗：合成表 **紧凑、严格按声明顺序**；
  二进制是 `[0][2][5][7][9]…`（**步长 2–3，非紧凑**）
- 二进制基址 `0x56F5E4` **已确证**（ctor `0x4C04EC` / `0x4C056B` 两处实写该地址）

⇒ **复核者的"槽序=声明序"结论被证伪**：二进制槽序不跟随生成头的声明序。

## 判定：**FAIL**

C-V 的核心前提（"编译器合成的 vtable 能与二进制逐字节一致"）**不成立**，两条独立理由：

1. **F2 缺口类根本不产出 vtable**（`CEffObj` 等多态基类无 `virtual` 供给）⇒ 无表可谈；
2. **能产出的类，其槽序与二进制不同**（合成 = 紧凑声明序；二进制 = 非紧凑）

⇒ **"vtable 表示收口到 C++ `virtual`"这条路线在原理上不足以复现二进制 vtables。**
方案 3（布局炸弹）若以"改用 `virtual`"为前提，**必须先重新设计**。

## ️ 副产物：`vtable_scanner` 的**边界吞并**缺陷已量化

```
CEffAction 表 0x56F5E4：读出 **96 槽**（注解记录 15 槽）⇒ 吞并了相邻多张表
CEffAction 注解记录的槽位内容也**混入了别的类**（[1] = CEffQuake::AllocSegments）
⇒ 注解记录的 vtables **可能同样来自串读**，不可作为 P3 的 ground truth 直接用
```

⇒ **P3 的正确 ground truth 需要"按 ctor 实写的基址 + 表结束判据"重新界定**，不能用注解记录。
（`vtable_scanner` 的 `read_rdata_dwords` 以"非 `.text` 指针"为终止 ⇒ 对本例失效。）

## 结论与建议

| 项 | 判定 |
|---|---|
| C-V 前提（合成表 == 二进制表） | **FAIL** |
| 方案 4（vtable 表示收口到 `virtual`） | **应放弃或重新设计** |
| 方案 3（布局炸弹） | **其"改用 virtual"前提不成立** ⇒ 必须先解决 **F2 供给**（否则无表）**且**解释二进制槽序的非紧凑性 |
| `coff_vtable.py` | **保留**（它是本判定的唯一手段，且自检严格）|
| 省下的成本 | 原计划 3–5 天（方案 3）**不应按原设计投入** |

**诚实标注**：
1. 只测了 **2 个类**（`CEffCylinder` 失败、`CEffAction` 顺序不符）——**样本小**，
   但两条理由都是**结构性**的（不产出 / 顺序不符），不是个例噪声。
2. `CEffAction` 二进制槽序的**成因未查明**（为何非紧凑？可能是多继承布局或 IDA 类型系统伪影）
   —— **这本身是新问题，需独立调研**。
3. `coff_vtable.py` 未在**全量 56 个单元**上跑（只测了 3 个 TU + 自检）。

---

# R15 【重要】R13 判定**理由被推翻**，但FAIL 结论**仍然成立**（captain，2026-09-15）

> **这是一次自我纠正。** R13 的"逐槽顺序不同"结论**是我用错对象造成的假象**。
> 换用受控最小件与正确边界后，理由完全改变，但 FAIL 判定**依然成立**（新理由）。

## 错误一：`vtable_scanner` 的**边界吞并**污染了 R13 的比对

```
CEffAction 表 @0x56F5E4：vtable_scanner 读出 **96 槽**（注解记录 15 槽）
真因（实测）：0x56F5E4 之后的**所有 DWORD 都落在 .text**
  ⇒ 该工具的终止判据「遇到非 .text 指针即停」**永不触发**
  ⇒ 它实际把 0x56F5E4 之后的多张相邻表全读成了一张表
```
**R13 因此把"多张表"当成"一张表有 96 槽"**，比对自然全错。

**修正**：新增 `tools/vtable_compare.py`，用**ctor 实写的 vptr 地址**界定边界。
实测 `original/PAL3.exe` 里有 **467 个** `movl $0x5xxxxx,(%reg)` 形式的 vptr 存储，
其目标即各表的**起始地址**；相邻起始地址之差 = 前一张表长度（**精确，不靠启发式**）。

## 错误二：受控最小件证明「槽序 = 源码声明序」

用与 `CEffCylinder` 形态一致的最小类（1 个多态基类 + 11 个自身虚方法）编译：

```
??_7C@@6B@   [0] ?b1@B1@@UAEXXZ          ← 基类槽
             [1] ??_EC@@UAEPAXI@Z         ← 虚析构占槽
             [2] Create  [3] Init  [4] CreateTask  [5] Destroy
             [6] AllocEffect  [7] Update …   ← **严格按源码声明序**
```

⇒ **编译器的槽序 = 源码声明序**（紧凑、无空隙）。我此前"声明序 ⇒ 应与二进制一一对应"的
**预期本身就用错了对象**（拿"我按地址排序的序"去比，当然不符）。

## 用正确边界重读二进制 `CEffCylinder` 表 @`0x56F7C8`

```
[ 0] 0x4C3DB0  ← **scalar deleting destructor**（实测：testb $0x1,0x8(%esp) + 条件 call 0x541d10=operator delete）
[ 1] 0x4C4060  CEffCylinder::Create        [ 2] 0x4C3EC0  CEffCylinder::Init
[ 3] 0x408BD0  NullCallback                [ 4] 0x408BD0  NullCallback
[ 5] 0x4C45A0  CEffCylinder::CreateTask    [ 6] 0x4C4370  CEffCylinder::Destroy
[ 7] 0x4C3D90  CEffCylinder::AllocEffect
```
⇒ **二进制前 7 槽的形式与"基类槽 + 虚析构槽 + 声明序的自身虚方法"一致**
（与受控最小件的结构同构）—— **R13 的"顺序不符"不成立。**

## ⚠️ 但 FAIL 仍成立，理由改为两条**新**的

### 理由 A（不变，且是根本）：F2 缺口类**根本不产出 vtable**

`CEffCylinder` 编译产出 **0 个 vtable 符号**（3 种 TU 均如此），
因为多态基类 `CEffObj` 的生成头里只有 `char _gap_000[4]`、**零 `virtual`**
（其注解 `+0=__vftable`、`methods=[]` ⇒ **F2 数据缺口**）。
**⇒ 无表可谈，P3 判据无从执行。**

### 理由 B（新，且可能是**不可修复**的）：**删除析构函数的变体不匹配**

```
编译器合成（受控最小件，虚析构）: 槽 1 = ??_E<Cls>@@UAEPAXI@Z   ← **vector** deleting dtor
二进制 CEffCylinder:              槽 0 = 0x4C3DB0              ← **scalar** deleting dtor
                                          （testb $0x1,0x8(%esp) + operator delete）
```
MSVC 对虚析构在 vtable 里放 `??_E`（vector）还是 `??_G`（scalar）由**编译器决定**，
**源码层面无法指定**。实测本项目 `.obj` 侧只见到 `??_G`（15 个），**未见 `??_E`**。
⇒ 若二进制确用 `??_G` 而编译器恒发 `??_E`，则**槽 0 内容在原理上不可复现**。

**⚠️ 理由 B 未完全证实**（需确认二进制槽 0 的 `0x4C3DB0` 是否就是 `??_G` 的地址，
以及编译器是否在某些条件下发 `??_G`）—— 列为**待验证**，但它是比"顺序"更硬的候选障碍。

## 修正后的判定表

| 项 | R13 原判 | **修正后** |
|---|---|---|
| "逐槽顺序不符" | 判 FAIL 的理由之一 | **推翻**（是我用错对象 + 工具边界吞并）|
| "F2 类不产出 vtable" | 理由之一 | **成立**（不变）|
| 删除析构变体 `??_E` vs `??_G` | 未提 | **新增理由**，可能不可修复，**待验证** |
| **FAIL 结论** | FAIL | **仍 FAIL**（理由改为 A + B）|
| 编译器槽序 = 源码声明序 | 我误以为"应按地址序" | **确认 = 声明序** |

## 诚实标注

1. **R13 的"顺序"理由是错的，我在同一份文档里自我纠正**（本会话第 N 次被实测推翻自己的归因）。
2. 理由 B **待验证**：需确认 `0x4C3DB0` 的 mangled 名与编译器在何条件下发 `??_G`。
3. 仍未在**全量 56 单元**上跑 `vtable_compare.py`。
4. `vtable_compare.py` 的边界法仍不完美：`0x56F7C8` 读到 **65 槽**（到 `0x56F8CC` 才有下一起写地址），
   而真实表在 `0x56F804` 后接的是**别的类**（`RenderTarget2::*`）⇒ **多继承的连续子表使"相邻起写地址"也不可靠**。

---

# R16 理由 B 被证伪 ⇒ **C-V 只剩一个障碍（F2 供给）**（captain，2026-09-15）

## 动机

R15 提出理由 B：「编译器发 `??_E`（vector deleting dtor）而二进制用 `??_G`（scalar）⇒
槽 0 内容原理上不可复现」。若成立，**整条 `virtual` 路线死亡**。故必须验证。

## 验证一：`??_E` 与 `??_G` **不是两个函数，是同一个**

`.obj` 符号表实读（受控变体 `v1.cpp`：单继承 + 虚析构 + 一个虚方法）：

```
??_GC@@UAEPAXI@Z  idx=19  sec=0   storage=2    ← 定义（在 COMDAT section）
??_EC@@UAEPAXI@Z  idx=20  sec=0   storage=105  ← **IMAGE_SYM_CLASS_WEAK_EXTERNAL（别名）**
                  aux[0]: TagIndex=2
??_GC@@UAEPAXI@Z  idx=29  sec=9   storage=2    ← **同一个定义**（section 9）
??_7C@@6B@        sec=7（.rdata）  ← vtable 引用 ??_E
```

⇒ **`??_E` 是弱外部别名，解析到 `??_G` 的定义**（COFF 的 COMDAT 别名机制）。
**⇒ 两者最终是同地址，vtable 槽 0 的内容不会因此不同。理由 B 不成立。**

## 验证二：链接后的最终 `.exe` 里 vtable 结构正确

链接一个最小 exe（`wine_link.sh` + `tools/vc6/Lib/LIBCMT.LIB`，此前因缺 `LIBPATH` 失败）：

```
最终 m.exe 的 vtable 候选（.rdata 里连续 .text 指针段）:
  0x4060D0  **5 槽**: 0x401060, 0x401010, 0x401060, 0x401040, 0x401060
```
⇒ 槽数 5（= 1 基类槽 + 1 虚析构 + 1 自身虚方法 + 链接器补充）、
且构造函数自写 vptr（`401080: movl $0x4060d8,0x409a38` 指向该表）⇒ **合成表在链接后结构正确**。

## 修正后的结论：C-V 的障碍**只剩一个**

| 理由 | R13 | R15 | **R16（最终）** |
|---|---|---|---|
| ①「逐槽顺序不符」 | FAIL 理由 | 已推翻（我用错对象 + 工具边界吞并）| 不成立 |
| ②「`??_E` vs `??_G` 不可复现」 | — | 新增理由，待验证 | **证伪**（同一函数，别名） |
| ③「**F2 缺口类不产出 vtable**」| FAIL 理由 | 成立 | **成立 ⇒ 唯一障碍** |

⇒ **C-V 判定从"FAIL，两条理由"收敛为"只差 **F2 数据供给**"。**

**这是**重要转折**：F2 供给是**可做的工程**（注解层有 70 个 `~Cls`；`CEffObj` 这类多态基类
需要补它的虚方法声明，那正是 F2 调研量化过的 57 类缺口），
**不是"原理上不可复现"**。

## 但仍**不能在今天判定 C-V 可行**——剩余未知

1. **未做"补好 F2 供给后"的端到端验证**：即给 `CEffObj` 补上虚方法声明后，
   `CEffCylinder` 是否能产出与二进制**逐槽一致**的表。**这是决定性的下一步**。
2. `vtable_compare.py` 的边界法仍不完美（多继承连续子表 ⇒ 相邻起写地址不可靠）。
3. 只测了 1 个最小件 + 2 个真实类，**未在全量 56 单元**上验证。

## 诚实标注

- R13 → R15 → R16 是**同一问题连续三次自我纠正**：先错判理由、再误提新理由、现证伪新理由。
  **每次都是实测推翻我的推断**（本会话第 N 次）。累计外部复核者 6 任，**我的归因被推翻多于被确认**。
- 理由 B 的证伪依据是**符号表的 storage class 语义**（`WEAK_EXTERNAL` = 别名），
  不是"我没看到 `??_E` 所以它不存在"——后者是"以缺席反推"（我犯过多次），**这次避开了**。
