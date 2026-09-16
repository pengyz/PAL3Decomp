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
---

## 8. 【修正 §6.1 的结论】IDA 分析**能**解决归属——但受 F2 缺口本身限制（captain，2026-09-15）

> **用户指出：「为什么不走 IDA 分析确定 ctor 归属？」——这是对的。**
> 我把 IDA 列为"需窗口的选项 A"并让位给离线方案，**判断有误**：
> **函数边界本就是 IDA auto-analysis 的职责**，用 `objdump` + Python 重建是舍近求远。

### 已实施：`pipeline/ida/export_func_bounds.py`（**只读**）

```
idat -A -S"pipeline/ida/export_func_bounds.py" original/PAL3.exe.i64
⇒ pipeline/ida/_logs/func_bounds.json
   counts: {funcs: 5554, vptr_sites: 476}
```

- **5554 个函数边界**（`start`/`end`/`name`/`flags`），名字含 **mangled 3261 个**（如 `??0AStarPathFinder@@QAE@XZ`）
- **476 个 vptr 写站点**，每条都带 **`func_start` + `func_name`**（IDA 归属）
- **只读**：脚本不调用 `save_database`；**IDB 文件大小不变**（85,659,881）。
  ⚠️ **mtime 被更新**（18:07），需在下次窗口操作时留意；内容未变（无 `save_database`）。

**首版脚本的操作数判据错误**，只抓到 **80/476** 条（把内存操作数只判为 `o_displ`）；
改为接受 `o_mem`/`o_displ`/`o_phrase` 后正确（476）。**如实留痕。**

### 归属效果：**170/467 张表**有了类归属（离线 6 种口径的最好结果是 20/467）

且立刻暴露两处**标注错误**：
```
0x4C0629 → IDA: RenderTarget2::scalar_deleting_dtor    （注解说 nullsub_75_override，错）
0x4C04EC → IDA: ?ClearTarget@RenderTarget2@@QAEPAPAUCEffBase@@XZ （注解说 CEffAction，待核）
0x4C3DF3 → ??0CEffCylinder@@QAE@XZ                     ✓
0x446175 → ??0CCBUIPanel@@QAE@XZ                       ✓（证实是 CCBUIPanel 的 ctor）
```

### 但 F2 缺口类只命中 **3/57**（`CEffShock` / `ScriptVM` / `filebuf`）

**真因（实测）**：**剩余 54 个类本身没有 IDA 函数归属**——
`IDA 函数名里含该类名的: 13 / 57`。这与 F2 缺口的定义**自洽**：
`methods=0` ⇔ **IDA 侧也没有归属给该类的函数**。

⇒ **不是归属方法的问题，是这些类在 IDB 里"没有名字"**。
⇒ 要补它们，需要**先给 IDA 里的那些函数命名/归属**（即 annotation 的 `methods` 侧），
那是**另一个工作方向**（不是"从二进制反推虚方法"，而是"先把 IDB 里的函数归属做对"）。

### 修正后的路径建议

| 序 | 动作 | 说明 |
|---|---|---|
| **1** | 用 `func_bounds.json` 的 **`vptr_sites` + IDA 归属**重跑全量"表→类"映射（170/467 已可做）| **纯离线**，立即可做 |
| **2** | 对那 54 个"IDA 无名"的类：**先在 IDB 里找到它们的 ctor 并命名**（annotation 工作）| 需窗口；这是 F2 的真正前置 |
| **3** | `CEffShock` / `ScriptVM` / `filebuf` 这 3 个**已可取证**的，先做闭环验证 | 验证方法链 |

---

## 9. 【更正 R18/§8 的错误方向】IDB 是**生成物**，修法只能在 annotation 层（captain 记）

> **用户纠正**：「你飘了，IDB 是生成物，不能写，正确的路径是走 annotation apply export codegen 完整管线」

**这个纠正是对的**，我在此前的 R18/§8 里把「在 IDB 里创建/重命名函数」当成了候选路径——**方向错误**。

### 事实（已核实 `pipeline/cli.py:cmd_init`）

```
[1/4] Raw IDB: EXISTS (original/PAL3.exe.raw.i64)
[2/4] Work IDB: EXISTS, **overwriting with fresh raw copy**   ← 每次 init 都从 raw 覆盖
      → 再 apply annotations（第 3 步）→ export（第 4 步）
```

⇒ **`original/PAL3.exe.i64` 完全由 `PAL3.exe` + PDB + `data/annotations/` 重建**。
**对它的任何写入都会被下次 `init` 覆盖 = 无意义的动作。**

**我犯的具体错误**：
1. 在 §8 把"写 IDB（创建/重命名函数）"列为**候选路径 B**；
2. 更早我还用 `idat -A -S"<只读脚本>"` 跑了一次——**即使脚本不 `save_database`，
   `idat` 仍更新了 IDB 的 mtime**（大小未变）。**那也是"向生成物写入"的动作，不该做。**
   （正确做法：如果只是要读信息，应明确知道 IDB 会被 `init` 重建，
   所以"读到的东西"必须来自 `apply/export` 的**产物**，而不是"改 IDB 让产物变好"。）

### 正确的修法位置

| 目标 | 正确位置 | 机制 |
|---|---|---|
| 给函数命名/改归属 | `data/annotations/functions.json` | `apply_annotations.py:11` → `set_name` + `SetType`（幂等）|
| **给类补方法归属（F2 缺口）** | **`data/annotations/structs/<Cls>.json` 的 `methods` 字段** | apply 时写入 IDB 的 struct methods ⇒ **codegen 才能据此发 `virtual`** |
| 给类补 vtable 记录 | `structs/<Cls>.json` 的 `vtables` 字段 | 同上 |

**⇒ 所以 F2 的修法是**：往 `structs/*.json` 的 `methods`/`vtables` 加条目（**带二进制证据**），
然后跑完整管线 `apply → export → codegen`，让 IDB 与 `ida_structs.json` 自然带上这些信息。

**并须遵守项目规则**：`CLAUDE.md` 「每一处 annotation 修改必须有二进制直接证据」
（A 级 = 指令中的 reg+disp32 / 绝对地址；禁止猜测性修改、禁止批量未验证修改）。

### ️ 但"归属"本身的证据仍不足（这是真实的技术障碍，不是方向问题）

即使方向对了，**"某个函数属于哪个类"的证据仍难取**。本轮实测的两条反例：

```
CEffShock:  ?GetEditorTaskDescription@CEffShock@@QAEPBDH@Z（const char*(int) 的 getter）
            写了 3 张表 0x56FA7C/0x56FA88/0x56FAC4
            ⇒ **一个 getter 不可能是 ctor** ⇒ IDA 的函数边界把 ctor 合并进了它
```
```
IDA 函数大小：中位数 73 B，均值 246 B，**最大 31052 B**；>4KB 的 24 个（0.4%）
 例：?CreatePanelElements@SaleUI@@QAEHPAUCCBUIPanel@@@Z = 31,052 B
⇒ **IDA 的"函数容器"也有合并** ⇒ 不能用它做归属
```

**⇒ 结论**：方向已明确（annotation 层 + 完整管线），
但**"给 F2 的 57 个类补方法归属"缺少可靠的归属证据**——
`decomp`、`annotations`、**IDB 的函数边界**三者都不足以单独支撑归属。

**⇒ 需要的方法**：用**调用链**取证（ctor 的调用者是谁、`new Cls` 的调用点在哪），
而不是依赖"函数容器"。

---

# 附：函数范围标注机制的可行性调研（captain，2026-09-15）

> **用户的观察与要求**：IDA 的函数切分错误需要新机制——
> 「允许手动切分函数，函数标注可标注**起始和结束偏移**；IDA 有能力自定义函数与修改函数范围；
> 发现错误合并就自己标注修正。**先把可行方案调研清楚，写测试用例确保机制有效，
> 然后落地 annotation 中的函数范围标注功能，然后进行重标注**」

## 1. 可行性：**成立**，且项目已有先例

### 1.1 IDA 具备所需 API

| API | 作用 |
|---|---|
| `ida_funcs.set_func_end(ea, new_end)` | 截断/延长函数范围 |
| `ida_funcs.add_func(start, end)` | 在指定范围创建函数 |
| `ida_funcs.del_func(ea)` | 删除函数 |
| `ida_name.set_name(ea, name, flags)` | 命名 |

### 1.2 项目已实现过同型操作（**可直接复用**）

`docs/superpowers/plans/2026-05-06-pal3a-ida-quality-fix.md:640-675` 的
`split_overlapping_functions`（PAL3A 的 BOUNDARY_OVERLAP 修复）：

```python
old_end = func.end_ea
if not ida_funcs.set_func_end(addr, split_addr):     # 截断父函数
    log("[FAIL]"); continue
if not ida_funcs.add_func(split_addr):               # 在切点建新函数
    ida_funcs.set_func_end(addr, old_end)            # **回滚**
    continue
ida_name.set_name(split_addr, safe_name, SN_NOWARN | SN_NOCHECK)
```
**已含 dry-run（默认）/ `--execute` / 回滚 / 逐条日志** —— 正是所需的机制骨架。

### 1.3 为什么现有 `apply` 修不了

`pipeline/ida/apply_annotations.py:1704-1718`：
```python
if not _ida_funcs.get_func(addr):
    if _ida_funcs.add_func(addr):          # 无 end 参数 ⇒ 用 IDA 自己的推断
        created += 1
    else:
        _next_func = _ida_funcs.get_next_func(addr)
        if _next_func:
            _ida_funcs.add_func(addr, _next_func.start_ea)   # end = **下一个函数起点**
```
⇒ **只做启发式，annotations 无法指定 `end`** ⇒ **合并/错位无法修**。

### 1.4 annotation 模式可以安全扩展

`pipeline/check_annotations.py:138-195` 对 `functions.json` 只校验
`address` 格式、`name`、`signature`（及重复/`virtual`/`__thiscall` 归属）——
**新增 `end`（或 `range`）字段不会被拒**。

## 2. 问题的真实规模（实测，**修正我先前的错误推断**）

### 2.1 ️ 我说过的"两个合并案例"**都不成立**

| 我此前的说法 | 实测真相 |
|---|---|
| `?CreatePanelElements@SaleUI@@QAEHPAUCCBUIPanel@@@Z` = 31,052 B **是合并** | **不是**：该范围只有 **1 个函数序言**（对照组单一函数也是 1）；尾部 `jl 0x4623f9` 是**循环回边**，是**真正的单个大函数** |
| `?GetEditorTaskDescription@CEffShock@@QAEPBDH@Z` 写 3 张表 ⇒ **边界合并** | **不是**：反汇编显示它是**构造函数**（`mov %ecx,%eax` + 初始化成员 + 3 个 vptr 写 + `ret`），**自包含在 58 字节内、未合并**。**错的是"名字"**，不是边界 |

### 2.2 但边界**确实**有系统性问题（抽样确证）

对 **60 个随机函数**检查"结束地址处是否为 `ret`/`int3`/填充"：
**18 个（30%）不是**。样例：
```
?AttachToRole@CameraCtrl@@QAEXH@Z   结束于 0x41E7CB → 反汇编为 `les (%ebx,%eax,8),%ecx`（**指令中间**）
?CastAttackMagic@CCBAI@@QAE_NHH@Z   结束处 `or %al,(%eax)`（指令中间）
?GetRenderFlag@CCBSystem@@QAEHXZ    结束处 `add %bl,-0x3e(%esi)`（指令中间）
thunk_00503D80                      结束于 `jmp`（thunk，**正常**）
SingletonThunk_00408B40             结束处非 ret（**正常**）
```
⇒ **约 30% 的边界有问题**（其中部分是 thunk/正常形态，部分是**真错位**）。

**另一个独立信号："函数体内含其他已知函数起始" = 0 个**（用 3618 个已知起始扫描 5554 个函数）
⇒ **"经典吞并式合并"没有证据**；问题是**边界错位**（end 落在指令中间、或 start 不是真入口）。

## 3. 修完边界后的连锁影响（必须设计进去）

1. **必须重反编译**：Hex-Rays 按**函数边界**输出（`export_full.py:388` `ida_hexrays.decompile(ea)`）
   ⇒ 改边界后**受影响的函数必须重跑 `export`**，而 `export` 是**全量**的（3598 个 JSON）⇒
   **改边界 = 一次全量 export**（时间成本可观）。
2. **`decomp` 的 `address` 语义会变**：它将成为"修正后的函数起始"
   ⇒ 下游 `match`/`mangler_bench` 的 `symbols` 与 `unmatched` **可能变化**（分母变 ⇒ 不可跨轮比较）。
3. **`functions.json` 的 `name` 与 `end` 必须一致**：若 `name` 指向的地址不是函数起始，
   现有 `add_func` 会创建**新函数**（可能吞掉后续代码）⇒ 新增 `end` 应当**强制**
   （即：有 `end` 时用 `add_func(start, end)`，并在必要时 `set_func_end` 先截断）。
