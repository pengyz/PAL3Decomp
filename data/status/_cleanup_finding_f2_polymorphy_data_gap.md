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
