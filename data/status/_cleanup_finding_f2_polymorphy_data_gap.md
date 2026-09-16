# F2 机制调研：多态性判定的数据缺口

> **性质**：机制性调研（**不是修复**）。产出是"为什么字节匹配当前不可能"的机理与规模。
> **日期**：2026-09-15 · **仓库**：`/home/peng/workspace/PAL3Decomp` · **HEAD**：`17b1af7e2`
> **来源**：独立复核 `data/status/_cleanup_review_cv_design.json`（子 agent `761ba967`）的 **F2**
> **主结论**：**F2 不是"某些类漏了 vtable"，而是"多态性判定所需的数据在 57/118 个类上根本不存在"。**

---

## 1. F2 是什么

C-V 设计（`docs/specs/2026-09-15-cv-layout-design.md`）主张：把 vptr 的认领者从"显式 gap/`__vftable` 成员"
改为"**编译器插入的 vptr**"（由 `virtual` 触发），理由是原源码写的就是 `virtual`。

**F2 指出这条路对一批类走不通**：这些类**永远不会发射任何 `virtual`**，
于是删掉 `__vftable`/gap 后，**vptr 无人提供** ⇒ 对象布局比二进制**少 4 字节**，
且 vtable 符号无法生成。**P1（`sizeof` 一致）通过 ≠ 字节匹配可行。**

---

## 2. 机制（三环，每环实测）

### 环 1：`vtables` 是**注解的透传**，不是导出时推导的

```
pipeline/ida/export_full.py:678   'vtables': _ann_structs.get(type_name, {}).get('vtables', []),
pipeline/ida/export_full.py:527   # Load annotation struct data for vtables/methods pass-through
pipeline/ida/export_full.py:529   # vtables/methods/_variants 透传（实测 761/761 struct 与注解逐字段等值）
```

⇒ `ida_structs[cls]['vtables'] == []` **不是因为导出丢了**，而是**注解里本来就没有**。

### 环 2：`class_vtable_slots()` 只读当前类，**不跨继承链**

```
pipeline/gen/stages/emit_headers.py:231  def class_vtable_slots(cls_name, with_addr=False, vtables=None, methods=None):
pipeline/gen/stages/emit_headers.py:241      _is = _get_ida_structs().get(cls_name)
pipeline/gen/stages/emit_headers.py:242      if not _is or not _is.get('vtables'):
pipeline/gen/stages/emit_headers.py:243          return [] if not with_addr else []
```

⇒ 类的 `vtables` 为空 ⇒ 守卫 `emit_headers.py:1787` 的 `class_vtable_slots(cls_name)` 为假
⇒ **一个 `virtual` 都不发射**（`emit_headers.py:1547/1579/1915` 同样取空）。
且**不向上查基类**：即使基类有 vtable，子类也看不到。

### 环 3：`vtables` 只在**有人手工发现并记录**过 vtable 地址与 slots 时才存在

对比（同一继承体系）：

| 类 | `methods` 数 | `vtables` | `+0` 成员 |
|---|---|---|---|
| `CEffCylinder` | 17 | **非空**（`addr 0x0056F7C8` + slots） | `__vftable` |
| `CEffBase` | **0** | `null` | `__vftable` |
| `CEffExplosive` | 4 | `null` | `__vftable` |
| `PalScriptWaitObj` | 1（`ReleaseObject`，**非 virtual**） | `null` | `__vftable` |

覆盖度：**有 `methods` 的 struct 218 个，其中有 `vtables` 的仅 79 个（36%）**。

---

## 3. 规模（实测，比复核者所述更细）

**118 个注解里有 `__vftable` 成员的类**，按"能否判定虚函数"分类：

| 分类 | 数量 | 后果 |
|---|---|---|
| **`methods` 为空** | **50** | **连"哪些是虚函数"都不知道** ⇒ 无法发射任何 `virtual` ⇒ 去掉 `__vftable` 后 vptr 无人提供 |
| `methods>0` 但 `vtables=[]` | **7** | 有方法、无 vtable 记录 ⇒ 同样不发射 `virtual` |
| `vtables` 非空 | **61** | 可发射 `virtual` |

`methods=0` 的样例：`gbMeshData`、`CEffBase`、`MvcController`、
`CTaskTpl_tagEffTaskParam_CEff{Quad,Explosive,Cylinder}`、
`elelife_emitter_graph`、`direction_emitter_graph` …

**⇒ F2 的精确规模：57 个类（50+7）无法通过 `virtual` 获得 vptr。**

---

## 4. 交叉证据：同一个 144 类错误在 2026-05-19 就被掩盖过一次

`data/annotations/CHANGE_LOG.md:181-188`：

> `### [2026-05-19] stage3 __vftable 完整注释 + FLIRT srand 修正`
> `- 问题: Hex-Rays 直接引用 this->__vftable (编译器内部实现, 不应出现在源码中)`
> `- 旧行为: 只注释含 __vftable 的单行, 多行函数调用参数残留`
> `- 效果: 消除 144 个 C2039 "__vftable is not a member" errors`

⇒ **今天看到的 718 条 `__vftable` 族错误，其主体在 2026-05-19 就被"注释掉"掩盖过一次。**
本会话的 t7 删除了该掩盖机制（`_IDA_MISID_PATTERNS` 与 blanket commenter），**把它放了回来**。
**这不是 t7 新引入的缺陷，而是"掩盖 vs 暴露"的取舍被翻转**——
且当时那条记录**没有说明真正的修法**（只记了掩盖手段），所以问题被搁置了 4 个月。

**另一条溯源**：`git log -S '"__vftable"' -- data/annotations/structs/` 命中
`58224d54a unify: vfptr -> __vftable in all annotations`
—— 证实了 C-V 设计书根因 A 里引用的"注解层统一改名"，也**解释了为什么
`emit_headers.py:1787` 只认 `vfptr` 的判据会失效**（改名后该判据失去对象）。

---

## 5. 对 C-V 设计的影响（设计必须吸收）

1. **根因 A 的修法（改判据拼写）已被复核证伪为"死代码"**（vptr 成员经 `apply_annotations.py:940`
   与 `udt_classify` 过滤，根本不进成员列表）。**F2 进一步说明：即便改对判据，
   对 57 个类也无 `virtual` 可发射。**
2. **多态性判定需要一个不依赖 `vtables` 的独立信号。** 候选：
   - `__vftable` 成员的存在（118 个类有）——**这是注解明确声明的"本类有 vptr"**，
     与 `vtables`（"我们知道虚表的**内容**"）是**两个不同的问题**。
   - 二进制侧：`Class_ctor` 是否写 `[this+0]`（`mov dword [ecx], offset vtbl_XXX`）
     —— 可用 `tools/pe_probe.py`（**不占 IDB 窗口**）批量取证。
3. **vtable 符号的生成**：61 个有 `vtables` 的类有 `addr`，可发射 `vtbl_XXXX` 符号；
   其余 57 个**没有地址** ⇒ 即便知道"有 vptr"，也**说不出它指向哪张表** ⇒
   `virtual` 由编译器合成的 vtable 与二进制表**不可能是同一张**。
   **⇒ 这 57 个类在原理上无法用"编译器插入 vptr"的方案表达。**

---

## 6. 结论：F2 是字节匹配的**独立硬前提**

| 问题 | 数据是否具备 |
|---|---|
| 某类**是否有 vptr** | 有：118 个类有 `__vftable` 成员（注解声明） |
| 某类**的哪些方法是虚函数** | **不足**：50 个类 `methods=0` |
| 某类**的虚表地址与槽位内容** | **不足**：仅 61/118 有 `vtables`（含 `addr`） |
| 全仓**有 methods 的类**中知道虚表的比例 | **79/218 = 36%** |

⇒ **C-V 只能覆盖 `vtables` 非空的 61 个类。** 其余 57 个类的 vptr/vtable 表达
**需要先补数据**（二进制取证：ctor 写 `[this+0]` + 虚表在 `.rdata` 的地址与槽位），
**这是设计之外的一项独立工程**。

---

## 7. 建议的下一步（待裁定）

| 选项 | 内容 | 代价 |
|---|---|---|
| **I1** | 用 `tools/pe_probe.py` 批量取证：对 118 个类找其 ctor 写 `[ecx+0]` 的指令，读出 vtable 地址 ⇒ 补齐"有 vptr + 表地址"两项 | 中；**不占 IDB 窗口** |
| **I2** | 再从 `.rdata` 的 vtable 读出槽位地址 ⇒ 与 `methods` 表对照，判定虚性并补 `vtables` → `slots` | 中大 |
| **I3** | C-V 先只做 61 个有数据的类，其余 57 个**暂保留 `__vftable`**（承认两种表示并存，但**按类明确**而非全局混乱） | 小；但不彻底 |
| **I4** | 把"多态性判定"做成独立门禁：`__vftable` 存在但 `vtables` 空 ⇒ 报待补清单 | 小 |

**captain 倾向 I1**：它用**已建成的、不占窗口的工具**，把"最缺的那一环"（表地址）
从二进制直接读出来，且能同时服务 118 个类；而 I3 只是缓解。

---

## 8. 未验证 / 诚实清单

1. 上述 50 个 `methods=0` 的类，**是否真的在二进制里多态**——**未逐类验证**。
   若其中一部分其实没有 vptr（`__vftable` 注解是错的），F2 的规模会缩小。
   **这是 I1 要顺手回答的**。
2. `ctor 写 [ecx+0]` 这一取证路径**未验证可行**（本会话用 `pe_probe` 只做过 getter 与小函数）。
3. `vtables` 的 61 个类，其 `slots` 是否**完整覆盖**真实虚表——未验证。
4. 复核者另报 `PalScriptWaitObj` 的 `vtables=[]` 但二进制多态；本文档确认它在注解里
   `methods` 只有 1 个且**非 virtual** ⇒ 它**是否真多态**同样属未验证项 1。
---

## 9. I1 取证路径的可行性实测（captain 补充，2026-09-15）

**已验证可行的部分**：

| 项 | 实测 |
|---|---|
| decomp 里的自名 ctor 文件（`<Cls>_<Cls>void_ADDR.json`） | 覆盖 **69 个类** |
| `CEffCylinder` 的 ctor 是否被收录为 method | **是**（`0x004c3dd0`，`methods` 17 条） |
| 其 `vtables` 数据 | 完整（`addr=0x0056F7C8`、`base=CEffAction`、**15 slots**） |
| ctor 正文里是否出现 `__vftable` | **是**（多类命中） |

**已验证**不可行的部分（**I1 的原设想需修正**）：

captain 原设想"从 ctor 的 `mov [ecx+0], offset vtbl` 读出 vtable 地址"。实测
**decomp 层的 ctor 正文里拿不到 vptr 安装指令**，出现的是**经 vptr 写字段**：

```
CCBItemWindow ctor : LOBYTE(this->__vftable) = 0;
SceneObj ctor      : *((_DWORD *)&this->TaskMgr_SceneObjParam_SceneObj::__vftable + 8) = 0;
CScreenMode ctor   : v2->UIDialog::UIWnd::__vftable = 0;
```

原因是 **vptr 安装在基类 ctor 里**（子类 ctor 只调用基类 ctor），
且 `udt_classify` 已把 `__vftable` 从 `data_members` **过滤掉**（实测 `UIWnd`/`SceneObj` 的
`data_members` 均无 `__vftable`）⇒ 该字段既不在导出数据里，也不在 ctor 正文里。

⇒ **I1 需改为 PE 层取证**：在子类 ctor 的指令流里找写 `[reg+0]` 且 RHS 是 `.rdata` 地址的形态。
**卡点**：`tools/pe_probe.py` 的极简反汇编器**不认识 SEH 序言**
（`6A FF 68 <imm32> 64 A1 00 00 00 00` = `push -1; push imm32; mov eax, fs:0`），
实测在 `CEffCylinder` 的 ctor 上产出垃圾（把 `push imm32` 的立即数第 4 字节当成 `push esi`）。
**⇒ 需先增强 pe_probe 的字节解码（或改用 capstone/pyelftools 之类的成熟解码器）。**

**附带确认（服务 F3）**：`SceneObj`/`CScreenMode` 的 ctor 里就有**限定基类形式**
`Base::__vftable`（`TaskMgr_SceneObjParam_SceneObj::__vftable`、`UIDialog::UIWnd::__vftable`）
⇒ 证实 606 处限定引用**不是孤例**，而是普遍形态。

---

## 10. ⚠️ 勘误：§9 的"拿不到 vptr 安装指令"是**工具造成的假象**（captain 立即纠正）

§9 的结论「decomp 层拿不到 vptr 安装指令 ⇒ I1 需改为 PE 层取证」**部分错误**，
而其"不可行"的**唯一证据来自 `tools/pe_probe.py` 的错误输出**。正确工具立刻证伪：

```
$ objdump -d --start-address=0x4C3DD0 --stop-address=0x4C3E20 original/PAL3.exe
  4c3df3:  c7 45 00 c8 f7 56 00   movl   $0x56f7c8,0x0(%ebp)     ← **vptr 安装**
  4c3dfa:  c7 07 bc f7 56 00      movl   $0x56f7bc,(%edi)        ← 第二张表（基类子对象）
```

- `0x56f7c8` **正是** `CEffCylinder` 注解里记录的 `vtables[0].addr`（§3 的对照表）
  ⇒ **I1 的原始设想（从 ctor 读 vtable 地址）成立。**
- `pe_probe` 在 `0x4C3DD0` 上把 `c7 45 00` 解成 `db 0x00 0x00 0x00` 等垃圾
  —— 它的极简解码器不认识 `c7 45 00`（`mov r/m32, imm32`，modrm=0x45 即 `[ebp+disp8]`）。

**⇒ 教训（与本会话其它错误同型）：我把"工具读不出来"当成了"事实不存在"。**
这与我把 `matched 123→101` 当退化读（分母不同）、把"不在 functions.json"当 CRT 证据（缺席论证）
是**同一类错误**：**用缺席/异常读数反推事实。**

**系统里已有成熟反汇编器，无需自造**：

```
objdump  (GNU binutils 2.38)  → 直接解 PE：`文件格式 pei-i386`，`objdump -d` 可用
ndisasm / gdb 亦在
capstone / pefile 未安装（python）
```

⇒ **pe_probe 的正确演进不是"自己补解码表"，而是复用 `objdump`**（或装 capstone）。
captain 倾向：`pe_probe` 保留"VA→字节"的映射职责（那部分已自检通过），
**反汇编交 `objdump`**，避免自造解码器带来的假象风险。

---

## 11. 独立复核（`511b4e4f`）的裁定与本文件的第二次勘误

复核交付：`data/status/_cleanup_review_f2_next.json`。**它纠正了本文档 5 处，其中 2 处是
§10 自我批评过的"以缺席/异常读数反推事实"同型残留。**

| 本文件主张 | 复核裁定 | 要点 |
|---|---|---|
| §3 规模 118/50/7/61 | **partial** | 118/7/61 精确；"50"实为 48 空导出 + 2 未导出；"218"含 3 个 `_` 内部键（实为 215）|
| §2 机制三环 | **partial** | 环①③属实；**环②结论性表述错误** |
| §4 "144 与 718 同批" | **refuted** | 形态不同批 |
| §9/§10 pe_probe 描述 | **confirmed + 反勘误** | 我的"它解不出 `c7 45 00`"**不复现** |
| §5/§6 "57 类原理上不可能" | **refuted（最重）** | 见下 |

### 勘误 1：§5"57 类说不出指向哪张表 ⇒ 原理上不可能"**错误**

复核用 `objdump -d` 全量反汇编（0.26s / 47 万行）+ 扫描 `mov [reg(+0)], imm32 ∈ .rdata`
+ 槽位内容校验 ⇒ **186 个 vptr 存储目标**、**92 张已记录表有 89 张被直接命中**、
**86 张注解未记录但通过校验的实表**。

**captain 独立验证了核心反例**：

```
注解 CEffCylinder:  vtables = [0x0056F7C8]（只记了一张）
ctor 实际存储:      4c3df3  movl $0x56f7c8,0x0(%ebp)    ← 已记录
                    4c3dfa  movl $0x56f7bc,(%edi)       ← **未记录的第二张表**
0x56f7bc 处确有表:   00584c00 50284c00 10584c00 b03d4c00 ...
```

⇒ **"注解没有地址" ≠ "地址不可获得"。** 这正是我在 §10 批评过的同型错误
（**用缺席反推事实**），却又在 §5 犯了一次。

### 勘误 2：§2 环②"子类看不到基类 vtable"**结论性表述错误**

```
emit_headers.py:231-243  class_vtable_slots 本体**确实**只读当前类（该部分成立）
emit_headers.py:1542-1567 _collect_base_vtable_names() **沿 bases 递归聚合基类槽名** ← 我漏了
emit_headers.py:2040/2045/2052  virtual 关键字**真实来源是 decomp 签名自带**（442 文件），
                                emit_headers 只做透传/剥离 ← 不是从 vtables 推导
```

⇒ "空 `vtables` ⇒ 一个 virtual 都不发射"**不成立**。captain 独立验证 `442` 一致。

### 勘误 3：§4 "144 与 718 是同一批、曾被掩盖"**refuted**

- `stage3` 旧 regex（`git show 31a155585^` 实读 `:79`）只匹配 `->__vftable`，**不支持 `::`**
  ⇒ 限定形态（占 718 的主体）**从未被掩盖**，05-19 与今天都在报错
- 被掩盖的是**无修饰形态**（至今仍折叠 422 处），与 718 主体**不同批**
- captain 独立核对：718 条中"错误消息含 `::`" 243 条、不含 475 条（与复核者的
  AST 形态分类 650/38/15/7 **不是同一度量**，但总数 718 一致；captain **未能独立复现
  650 这个分类数**，如实标注）

### 勘误 4：§9/§10 对 `pe_probe` 的描述（反勘误）

复核称当前 `pe_probe` 对 `0x4C3DD0` **重同步后能正确解出两条 vptr 存储**
（`mov dword [+0x0], 0x56F7C8` / `mov dword [], 0x56F7BC`）。captain 此前只看了前 16 字节
（序言错位区）就断言"产出垃圾"。**⇒ 我的"工具坏了"结论下得过早**（仍是"以异常读数反推"）。

### 重大收益：第 4 问的 VC6 实测**推翻了我"必须补数据"的前提**

复核用 `tools/wine_cl.sh` 实测：

| 组合 | `sizeof` | 成员偏移 | 判定 |
|---|---|---|---|
| `A{void*__vftable; int a; int b;}`（**无 virtual**） | **12** | `__vftable@0` | ✅ 与多态布局同构 |
| `B : A {int c;}` | 16 | `c@+0xC` | ✅ 无第二指针 |
| `Both{virtual ~; void*__vftable; int z;}` | 12 | 成员**全 +4** | **偏移炸弹**（尺寸未必变，故更难发现）|

`A::A` 生成 `mov eax,ecx; mov DWORD PTR [eax],OFFSET fake_tbl` —— 与二进制 `c7 45 00 imm32` 同族；
const 表落 `CONST(.rdata)`；`__vftable` 成员名零警告。

⇒ **「删 `virtual` + 保留显式 `__vftable` 成员 + ctor 显式赋表 + const 表发射」可同时覆盖
61 个与 57 个类。** 先前复核者把 D3 判为"有害"，其前提是**`virtual` 未删**——
在"同时删 virtual"的前提下 D3 **是可行的**。

**⇒ 我最初问的 "A（先补数据）vs B（先做布局）" 是伪对立**：A 的取证产出是**任何路线的共同前提**。

### 另一处反例提醒（复核者给，captain 采纳）

`SceneObj` 的 ctor（`0x453036`）里，基类 `PalScriptWaitObj` 的 vptr 存储
**被 MSVC 死存储消除（DSE）** ⇒ **"找不到存储指令"不能当"不多态"的证据**——
这是同一类缺席论证陷阱的又一个实例。

### 修正后的结论

1. **§5/§6 的"字节匹配当前不可能"应限定为**：*在"只用编译器合成 vtable"（C-V 原设想）的前提下*
   不可能；**不代表没有可行路线**。
2. **C-V 原设想有一个至今完全未验证的前提**：**编译器合成的 vtable 能否与二进制逐字节一致**。
   复核明确指出这一点"至今完全未验证"。
3. **推荐路线改为**（复核建议，captain 认同）：
   - **S-a**：把 `/tmp` 的 objdump 扫描器**产品化**（objdump + 槽位内容校验 + 槽位→methods 归属），
     产出 **118 类取证表**，一次性关闭 §8.1"逐类多态性"未验证项
   - **S-b**：在「删 `virtual` + 显式 `__vftable` + 手工表发射」（已实测）与 C-V 之间做**小范围 A/B** 定案
   - **S-c**：`B`（gap 起点决策表）**单独不可行**——它只解布局，不产 vtable 符号与 ctor 存储指令；
     且当前 `PalScriptWaitObj.h` 已用 `_gap_000[4]` 占位，**布局本来就没少 4 字节**
     （§1 那句只在 C-V 删 gap 的场景下成立）
