# 同一逻辑表双副本并存会静默分叉（表修一漏一）

**type**: gotcha
**created**: 2026-10-16（reviewer 复核实证归档）
**实证案**: `_GB_REF_PARAM_FUNCS` / `_fix_ref_params` 在 `pipeline/gen/stages/stage3_cleanup.py:2222/2256` 与 `pipeline/gen/stages/stage5_fixup.py:564/664` **双副本并存**；2026-10-14「B 修补条」在 stage5 侧把 `GetAABBox` 裸键拆成限定键 `gbOBBox::GetAABBox`，**stage3 副本未同步** ⇒ 两表键级分叉至今（当场实测：stage3 键 30 / stage5 键 34 / 交集 29；仅 stage3 有 `GetAABBox`，仅 stage5 有 `GetBlend`/`SetBlend`/`RightMultiply`/`PointWorldToScr`/`gbOBBox::GetAABBox`，**分叉键合计 6**）。R15 测试 `pipeline/gen/test_ref_param_table_b.py` 只 `from stage5_fixup import _GB_REF_PARAM_FUNCS`——**单侧防护**，stage3 副本漂移零覆盖。

**为什么：** 逻辑表/映射在两个 stage 各存一份时，修表动作天然是「点状」的——修者看着眼前的副本改，另一份没有红线提醒、没有测试盯着，分叉后两侧渲染行为静默不一致（同一调用形在 stage3 路径和 stage5 路径得到不同改写），且**编译/字节指标都不会报警**（两份各自"自洽"）。本仓已有同型教训：codegen 注解直读多点散落（CLAUDE.md「单一读点」条款，现存 3 处直读未清），以及 test 影子副本突变杀 0 实证（`test_struct_value_cast_fix.py` 头注：「import 生产函数——影子副本教训：本地副本突变杀 0/5」）。修一漏一是**结构性**风险，不是粗心问题。

**何时使用：** ① 任何「同一张表/同一段改写逻辑出现在 ≥2 个模块」的场景（grep `= {` 同名常量、同名 `_fix_*` 函数）——要么收敛到单一读点/单一实现（export_full 头部 `[t4-DECLARED-EXCEPTION]` 的处置先例），要么建**双侧一致性测试**（断言两份键集相等）；② 修表/改映射类补丁落地前，必须 `grep -rn "<表名>" pipeline/` 找全副本并同改（R13 变体：补丁落地 grep 核实应含**副本数核对**）；③ R15 写测试时 import **生产函数**（禁影子副本），且若生产物有双副本，测试必须双侧各断言一份。

**诊断命令（复算本文数字）：**
```bash
python3 -c "
import re
def keys(f):
    b=re.search(r'_GB_REF_PARAM_FUNCS\s*=\s*\{(.*?)\n\}', open(f).read(), re.S).group(1)
    return set(re.findall(r\"'([\w:]+)'\s*:\s*\{\", b))
k3=keys('pipeline/gen/stages/stage3_cleanup.py'); k5=keys('pipeline/gen/stages/stage5_fixup.py')
print(len(k3), len(k5), len(k3&k5), sorted(k3-k5), sorted(k5-k3))"
```

---

## 实例二（2026-10-20）：annotation `methods` vs `known_methods` —— 语义相近、命名相近的双注册表

**实证案**：`data/annotations/structs/*.json` 里方法信息存于**两个**表：

| 字段 | 来源 | 形 | 覆盖 | 用途 |
|---|---|---|---|---|
| **`methods`** | IDB 导出 | `{地址: {name, signature, source}}` | CCBStage **231 条**（含 MoveToAbsolute）| **主表**（codegen 经 ida_structs 生成头）|
| **`known_methods`** | **手工补录** | `{slot: {name}}` | 全仓仅 **6 个**注解文件有 | vtable 程序名补充 |

`pipeline/gen/stages/emit_headers.py:1120` 注释自证："annotation known_methods are **manually** [added]"。

**事故**：2026-10-20 实现 `qualify_shadowed_free_calls` 时读 `known_methods` ⇒
CCBStage 恒为空集 ⇒ 变换**从不命中但不报错** ⇒ I3 门禁计数不变才暴露。
后续一版改从**生成头解析**成员名（能用），但属 codegen 读自己产物的**循环依赖**，
最终改读 `annotation_view.struct_by_class(cls).get('methods')`（单一读点）。

**与实例一同构**：两表**语义相近、命名相近、一个稀疏一个完整** ⇒ 修者自然去读名字更"对"
的那个，而它恰好是稀疏的。`methods`/`known_methods` 与 `_GB_REF_PARAM_FUNCS` 双副本
一样：**编译指标不报警，只有"业务量计数"（I3=19 不动）才暴露**。

**防复发约定**（本仓通用）：
1. 注解方法信息的**唯一权威源是 `methods`**；`known_methods` 仅作 vtable 名字补充，
   **不得**用它判「某类是否有某方法」。
2. 任何「按类查方法名/成员名」的代码，一律走 `annotation_view` 单一读点取 `methods`。
3. 读到**空集**时不得静默继续 —— 必须与 ida_structs 的 `methods` 数量对照；
   两侧都为空才接受（否则是读错表）。
4. 引入 `except Exception: … = set()` 吞异常时，须在旁边写**门禁校验点**
   （本次靠 `codegen_invariant_lint.py` 的 I3 计数不变才暴露 NameError 被吞）。

**核对命令**：
```bash
python3 -c "
import json
for f in ('CCBStage',):
    a=json.load(open('data/annotations/structs/%s.json'%f))
    i=json.load(open('asm/pal3/ida_structs.json'))[f]
    print('annotation.methods  =', len(a.get('methods') or {}))
    print('annotation.known_methods =', len(a.get('known_methods') or {}))
    print('ida_structs.methods =', len(i.get('methods') or []))"
```

---

## 实例三（2026-10-20）：annotation `base_class` vs `bases` —— 演进未统一的双字段

**实证案**：`data/annotations/structs/*.json` 里继承信息存于**两个**字段：

| 字段 | 引入 | 目的 | 值形态 | 覆盖 |
|---|---|---|---|---|
| **`base_class`** | 早期 | **单继承**（ctor 证据判定）| 纯名字：list 160 + **str 20** | 180 类 |
| **`bases`** | 后期（MI 专项）| **多继承**（`tools(mi)` 基类偏移纯二进制推导）| `{name, offset}` | 15 类 |

关键提交：`774f77206`（UIScene base_class=UIWnd）· `fbde8f52e`（MI 基类偏移工具 + 反证）·
`34f7f435f`（Role 多继承核实 + 尺寸格门 MI 约定）· `17d1bc0cf`（收窄 CEff 族 bases 偏移）。

**判定：是重复，且 `bases` 是超集**
- 15/15 重叠案例名字**完全一致**（0 矛盾）；`bases` 额外带 MI 偏移
- 只有 `bases` 的 = **0** 个（`bases` 从不单独存在）
- codegen **双源都读**：`stage2_semantic` / `stage4_substitution` / `emit_headers` /
  `data.py` / `ast_transform` / `apply_annotations` 全有 `base_class` 读点 ⇒ 修一漏一

**处置（2026-10-20 真相源迁移）**：
- 180 类 `base_class` → `bases`（MI 偏移取 ida_structs.bases）
- 名字等价核验：180 类 · 0 丢失 · 0 变化
- `base_class` 字段 annotation 层**彻底清零**；消费面收敛到单一读点
  `annotation_view.base_names()/base_entries()`

**与前两实例同构**：语义相近、命名相近、一个早期一个后期 ⇒ 修者自然读"名字更对"
的那个。差别在于：前两例是**数据表**双副本，本例是**数据字段**双副本，
且代码侧有 ~30 个读点。

**防复发**（前三例通用）：任何「同义字段」并存时，**必须在引入第二字段的那一刻
废弃第一个**，或建立单一读点 + 契约锁。
