# F2 可执行供给清单：57 个"有 `__vftable` 但无 vtable 记录"的类

> **日期**：2026-09-15 · **仓库**：`/home/peng/workspace/PAL3Decomp` · **HEAD**：`c54830570`
> **性质**：**清单 + 取证规程**（非修复）。它是方案 3 的**前置任务定义**。
> **关联**：`docs/knowledge/pattern_recover_polymorphic_base_virtual_methods.md`（方法链）、
> `docs/specs/2026-09-15-cv-layout-design.md` R13–R18（C-V 判定演进）

---

## 1. 为什么需要这份清单

C-V（vtable 表示收口到 C++ `virtual`）经 R18 判定**机制可行**，唯一障碍是 **F2 数据供给**：

> **多态基类的虚方法未标注** ⇒ codegen 编不出 `virtual` ⇒ 编译器**不发射 vtable**
> ⇒ 生成头只有 `char _gap_000[4]` 占位 ⇒ `C2039 "'__vftable' : is not a member"`（**718 条 / 38 文件**）。

**⇒ 修 `C2039` 的本质是"补多态基类的虚方法集合"，不是改名字。**

---

## 2. 规模（实测，`asm/pal3/ida_structs.json` + `data/annotations/structs/`）

| 分类 | 数量 | 说明 |
|---|---|---|
| **OK**（`vtables` 非空）| **61** | 数据已有，可直接用于 codegen |
| **A. 缺表**：`vtables` 空、`methods` 非空 | **7** | 有函数可查，**最容易** |
| **B. 全缺**：`vtables` 空、`methods` 空 | **50** | 需从二进制取证 |
| **缺口合计** | **57** | = 7 + 50 |

**按形态分组（57 个缺口类）**：

| 组 | 数量 | 含义 |
|---|---|---|
| **A. 无基类** | **47** | **它们本身就是基类**（`CEffObj`/`gbRefObject`/`NPC`/`ScriptVM` 等）⇒ 取证目标就是它们自己 |
| B. 有基类但基类不多态 | 8 | 自身声明虚方法即可 |
| C. 有多态基类 | 2 | 供给应从基类继承 |

**⇒ 重中之重：那 47 个"无基类的基类"是一切的根**——
`CEffObj` 是 `CEffAction`/`CEffCylinder`/`CEffBase`/`CEffQuad`/`CEffShock`/`CEffExplosive` 的共同基类；
`gbRefObject` 是 gbengine 侧的根。**先补它们，下游类才能排出槽位。**

---

## 3. 取证规程（本会话已验证走通，可直接复用）

见 `docs/knowledge/pattern_recover_polymorphic_base_virtual_methods.md`，摘要：

| 步 | 动作 | 工具 |
|---|---|---|
| **1** | **界定表边界**：用 **ctor 实写的 vptr 地址**（`PAL3.exe` 里有 **467 个** `movl $0x5xxxxx,(%reg)`），相邻起始之差 = 表长 | `tools/vtable_compare.py --list-bin` |
| **2** | **识别槽位函数**：VA 反查 `decomp`/`annotations`；无名槽用反汇编特征识别（见 §4） | `--bin-base 0xXXXX` |
| **3** | **最小件验证合成**：构造同形最小类，确认"槽序 = 源码声明序" | `tools/coff_vtable.py --obj` |
| **4** | **补注解→逐槽比对** | `coff_vtable.py` + `vtable_compare.py` |
| ⚠️ | **查虚析构是否被定义**：MSVC6 只在"定义了本类虚函数"时才发射 vtable（**R18 实测**）；生成头里 `~Cls();` 是非虚声明且 `.cpp` 编译失败 ⇒ **表永远不发射** | — |

---

## 4. 槽位函数的反汇编特征（用于识别无名槽）

| 形态 | 字节特征 | 语义 |
|---|---|---|
| **deleting destructor** | `test $0x1,%al`（或 `testb $0x1,0x8(%esp)`）+ **恢复 vptr** `movl $0x<表地址>,(%reg)` + 条件 `call <operator delete>` | 虚析构的 vtable 入口 |
| **返回 0 的桩** | `xor %al,%al; ret $0x4` | `int Stub(...) { return 0; }` |
| **空槽桩** | `ret $0x10`（4 个 DWORD 参数）/ `ret`（无参） | `void nullsub(...)` |
| **this 调整 thunk** | `83 e9 08`（`sub $0x8,%ecx`）+ `e9 rel32`（`jmp`）| 多继承的 adjustor thunk |

**实测样本**（`CEffObj`）：
```
0x4C0620  无名 → deleting destructor（`test $0x1,%al` + `movl $0x56f62c,(%esi)` + 条件释放）
0x4C0600  → `xor %al,%al; ret 4`     = 返回 0 的桩
0x4C0610  → `ret 0x10`               = 空桩
```

---

## 5. 缺口清单（57 个类）

完整表格见 `/tmp/f2_gap.txt`（本会话生成；**含每个类的 `methods` 数与基类**）。
**按优先级**：

### P0 — 根基类（先做，收益最大）

| 类 | `methods` | 下游影响 |
|---|---|---|
| **`CEffObj`** | **0** | `CEffAction` / `CEffCylinder` / `CEffBase` / `CEffQuad` / `CEffShock` / `CEffExplosive` 的共同基类 |
| **`gbRefObject`** | 1 | gbengine 侧引用计数根（`UIStatic.m_textx` 的类型）|
| `GlowObj` | 0 | `SceneObj` 的基类之一（R13 的 96 字节漂移来源之一）|
| `TaskMgr_SceneObjParam_SceneObj` | 0 | `SceneObj` 的基类之一 |
| `PalScriptWaitObj` | 1 | `SceneObj` 的主基类 |
| `gbVisNode` / `gbResour` 系 | 0 | `gbActor` / `gbGeomNode` / `gbRenderEffect` / `gbTexture_D3D` 的基类 |

### P1 — 有 `methods` 的（7 个，最容易）

`CEffExplosive`(4) · `CEffQuad`(5) · `CEffShock`(6) · `NPC`(20) · `ScriptVM`(11) ·
`PalScriptWaitObj`(1) · `gbRefObject`(1)

### P2 — 模板实例（`CTaskTpl_*`，约 22 个，`methods=0`）

大多是**数据载体**（`tagEffTaskParam` 系列），**多数可能本就没有自己的 vtable**
（其 `__vftable` 注解或指基类表）⇒ **需逐个确认"是否真需要 vptr"**，
不要一律补。

### P3 — 其它（`*_graph` / `*_particle_graph` 等，约 11 个）

`elelife_emitter_graph` / `direction_emitter_graph` / `rgbcolor_particle_graph` …
（多为粒子系统的参数图，`methods=0`）

---

## 6. ⚠️ 本清单的**未完成部分**（诚实标注）

### 6.1 【已穷尽】"表 → 类"映射：**用现有数据源无法解决**

要把 467 张表映射到类，本会话尝试了 **6 种口径，全部失败**：

| # | 口径 | 结果 | 失败原因（实测） |
|---|---|---|---|
| 1 | 按函数名前缀 `Cls::` 匹配 store 所属函数 | 0/57 | decomp 的 ctor 名是 **`Cls(void)`** 而非 `Cls::Cls` |
| 2 | 按"类的已知函数 VA ∩ 表前 8 槽" | 0/57 | 缺口类**没有已知函数 VA**（`methods=0`）|
| 3 | 按"store 指令所属函数"（decomp 地址）| 0/57 | 同 #1 |
| 4 | 按 decomp 的 `(address, size_bytes)` **区间**归属 | 0/57 | **decomp 函数边界不可靠**：`CCBItemWindow` 的 `decomp.address=0x4461B0` **高于**其 vptr 存储 `0x446175`；且 `0x4C04EC` 落在被标为 `RenderTarget2::ClearTarget` 的范围内（实际是别的函数）|
| 5 | 按 `functions.json` 精确起始（534 个）| 0/57 | **该区域根本没被标注**：`0x4C0000-0x4C0800` 只有 **2 个**条目（`0x4C0510`、`0x4C0610`）|
| 6 | **计分法**：表的最多槽位归属类（**对已知类有效！**）| 0/57 | **循环依赖**：计分需要"该类的已知函数 VA"，而缺口类**恰恰是 `methods=0` 的那批** |

**口径 6 对已知类是正确的**（实测：表 `0x56F5E4` → `CEffAction` 9 分；
表 `0x56F7C8` → `CEffCylinder` 10 分，**均正确**），但**只能归属 20/467 张表**
（高置信 ≥5 分仅 **11** 张）——因为多数表所属的类同样 `methods=0`。

**⇒ 结论：`decomp` 与 `annotations` 都缺少"可靠函数边界"，无法支撑"表→类"映射。**

**正确路径**（需 IDA 窗口）：
- 用 **IDA 的函数边界**（`funcs.json` / IDA 导出的函数起止）替代 `decomp.address`，
  再重跑口径 3/4；
- 或先对目标类逐个用 **`ctor` 的调用点链**反推归属
  （ctor 里 `movl $表,0(%ecx)`，而 `%ecx` 来自 `new Cls`/`this` 的调用者）。

### 6.2 其它未完成项

1. **57 个类里有多少"真需要 vptr"未验证**。P2（`CTaskTpl_*` 模板实例）与 P3（`*_graph`）
   **很可能不需要**——它们的 `__vftable` 注解或指基类表。**不要一律补。**
2. **`CEffCylinder` 的声明序缺陷**（`Init` 与 `CreateTask` 之间 2 个 `NullCallback` 空槽）
   只在 1 个类上定位到（R18），**未推广**。
3. **未做**"补全 `CEffObj` 真实虚方法集合后两表逐槽一致"的闭环验证。

---

## 7. 建议的执行顺序

| 序 | 动作 | 依据 |
|---|---|---|
| **1** | **解决"ctor 归属"** ⇒ 把 467 张表映射到类 | §6.1 的三个口径都失败，需新方法 |
| **2** | 只对 **P0（根基类）** 做完整取证 + 补注解 | 下游类依赖它们 |
| **3** | 用 `CEffCylinder` 做**闭环验证**（R18 已定位 2 个缺陷，补齐后逐槽应一致）| 验证方法链有效 |
| **4** | P1（7 个，最容易）→ 再评估 P2/P3 是否真需要 | 边际收益判断 |