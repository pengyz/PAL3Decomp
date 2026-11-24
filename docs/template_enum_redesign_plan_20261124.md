# PAL3 反编译语料类型系统 · 端到端完备重设计方案

日期: 2026-11-24 · 性质: 推翻式重设计（非补丁） · 前置: 上一轮多轮补丁方案被否决

---

## 0. 设计公理（第一性原理，全案由此推导）

1. **真相唯一**: 每个类型名恰好有**一个**权威声明通道（enum 头 / 类内嵌套 / 注解别名表 / gbengine 外部头 / SDK），由注解层显式登记，管线其余层只消费不裁决。
2. **注解层 = 唯一真相**: codegen 的枚举值、枚举形式（平铺/嵌套）、别名表全部读注解 json。IDB（apply 产物）只为 hexrays 服务；IDB 与注解分歧 = 管线 bug，必须显式记录而不是静默取一边。
3. **MSVC6 合法性是硬约束**: 枚举**永不前向声明**（VC6 无 enum fwd）；枚举尺寸恒 4B（int）；同名 class fwd + enum def 同作用域非法。
4. **暴露原则**: 每个名字要么按真值渲染，要么显式进入裁决队列（记录+人工定谳），**不允许静默降级**（伪类 `_tail_000[4]`、POD typedef、残缺 stub 都是静默降级，废除）。
5. **输出集先知**: 一次 codegen 运行的全部产物文件集合在写第一个文件前就确定（产物清单由注册表推导）→ include 解析不探测文件系统、清理不用启发式、运行间无顺序依赖。

---

## 1. 当前态诊断（逐层，全部读码验证）

### 1.1 事实总表（探针 census + 代码实证）

| 项 | 现状 | 证据 |
|---|---|---|
| S2 | 112/230（C2664×277, C2440×202, C2109×71, C2011×61, C2079×61, C2061×46…） | data/status/probe_census.json（与今日口径一致） |
| 三源枚举分歧 | enums.json=69（59平+10嵌套）/ IDB `_enums`=85（75平+10嵌套）/ PDB=351 | 读 json 实测 |
| 注解有而 IDB 无（apply 未落地 5 个） | NameSys_NAMEFLAG, ParabolaCalculator_PRBL_STATE, UIButton_UIBUTTON_STATE, UIScrollBar_SB_AREA, UIStaticFlex_State | 集合差实测 |
| IDB 有而注解无（无主 21 个） | D3D*×14, gb*×5, GBPARAMHANDLE, LGT_TYPE, LIGHT_TYPE | 集合差实测 |
| 值失真 | JB_NULL/DLG_MSG_NONE/_invalid = 18446744073709551615（IDA edm_t.value u64 存储，-1 伪影）；PDB 真值="-1" | export_full.py:1067 直接写 em.value |
| 值丢失 | IDB UIPushButton::UIPUSHBUTTON_STATE 只有 PUSH_UP/PUSH_DOWN；注解与 PDB 有 NUMSTATE=2 | apply 3b merge 未补齐 |
| 语料 body 枚举用法 | 全部为 `(EnumName)裸值` 强转；**零处枚举成员名**（NOTE_SAVE/FS_FENGDU/ACT_STAND 全语料 0 命中） | grep 实测 |

### 1.2 emit_headers.py（pipeline/gen/stages/emit_headers.py）

**[D1] 五个渲染通道互不感知，UIPUSHBUTTON_STATE 同时走了四个**（C2011×61 + C2079×61 根因）:
- 通道① POD 早退（:1980-1985）: 平铺伪影 struct `UIPUSHBUTTON_STATE`(size1) 无注解 json → `_pod_scalar_names()` 收录 → 写 stub 头 `Misc/UIPUSHBUTTON_STATE.h` + `_POD_TYPEDEFS.append('typedef unsigned char UIPUSHBUTTON_STATE;')`。
- 通道② scalar_typedefs 写出（:5846-5889）: "枚举让位"过滤（:5867）查 `_enums` **键**，但 IDB 键是嵌套形 `UIPushButton::UIPUSHBUTTON_STATE`，平铺名不在其中 → typedef 落盘。**实盘证实**: `pal3/src/scalar_typedefs.h` 第 6 行 `typedef unsigned char UIPUSHBUTTON_STATE;`。①+②叠加 = 文件作用域 typedef(1B) 与类作用域 enum(4B) 双重冲突，且 typedef 形会**破坏布局**（m_state @0x50 stride 4）。
- 通道③ 类内嵌套前向 A 路（:2709-2712）: `nested_types` 参数=scope_tree children（嵌套枚举节点在内），kind 只查注解 json `_nested_kind`（:1133-1148）→ UIPushButton.json **无 nested_types 键**（实测）→ 默认 'struct' → 发射 `struct UIPUSHBUTTON_STATE;`（UIPushButton.h:21）。定义紧随其后（通道⑤）→ 同类作用域 struct fwd + enum def = **C2011**（MSVC6 硬非法）。
- 通道④ 类内嵌套前向 B 路（:2770-2780）: 枚举感知（查 `_enums` 有 values 则 skip）——**与 A 路判据不同源**，B 正确跳过、A 没跳过，双路冗余且分叉。
- 通道⑤ 嵌套定义渲染（:2784-2787 → `_emit_nested_struct` :1741-1830）: 查 `_enums` 命中 → 发射真 enum def（UIPushButton.h:26-29）。
- 附生 bug: include 接线（m_state 值员 → include_types → :2285-2288 **文件系统探测**）命中**上一轮运行的 stale stub** → UIPushButton.h:11 `#include "Misc/UIPUSHBUTTON_STATE.h"` → TU 同时见 typedef + 双形式。**运行间状态依赖**。

**[D2] 5b 补丁无效的精确根因**: scope_tree.py:128-139（5b）把平铺伪影节点标 `is_skipped`，但 **`scope_tree.roots` 在 emit_headers 中零消费**（grep 全文件：只调 `build/find/children`）。main() 的类循环用 `all_classes`（:4290 由 ida_data 直接重建）+ `classes_with_headers`（:4351-4379 同样直读 ida_data）→ 5b 标记对头生成路径**零影响**。POD stub + typedef 照发，S2 恒 112。**层间接缝断裂，非消解逻辑 bug。**

**[D3] POD 机制烂尾三证**:
- `_pod_scalar_names()`（:445-469）判据 = size∈{1,2,4,8} − 系统 − 注解 json，**不看成员**：`_s_CatchableTypeArray`(2 成员)、`TypeDescriptor`(3 成员) 被标量化 → stub 头 + `typedef DWORD/_int64`（scalar_typedefs.h 实盘 4 条 typedef 中 2 条是**有真成员的 RTTI 结构**）。
- :472-492 死代码（双重 return 后的 template_bases 成员指针第三证据源永不执行）——该源只做 discard，死掉使 POD 集**偏大**。
- `_RAW_SLOT_RE`（:443）定义后**全文件零使用**——raw-slot-only 改造没落进函数体。
- generate_header 内联再判（:1980 `and not methods`）与预扫描判据不同源（C 阶段事故已证明这类双判据必然分叉）。

**[D4] 平铺注解枚举被渲染成伪类（暴露违背实例）**: 注解枚举 `UIButton_UIBUTTON_STATE`（enums.json 有全值表）apply 未落地 → IDB 只有 size4 空 struct 伪影 → 类循环渲染 `class UIButton_UIBUTTON_STATE { char _tail_000[4]; }`（Misc/UIButton_UIBUTTON_STATE.h 实盘）。ParabolaCalculator_PRBL_STATE.h / UIStaticFlex_State.h 同族。编译能过（4B 布局侥幸对齐）但**真值被静默隐藏**——正是"错误该暴露暴露"要消灭的形态。

**[D5] `enum CDState;` 前向声明发射（VC6 非法）**: R76 修（:2706-2712 注释自述"enum kind 发 enum %s;"）在注解 nested_types.kind=enum 时发射 `enum CDState;`——Comp_DonateUI.h:15 实盘。**VC6 不支持枚举前向声明**，且定义就在 20 行。R76 把 C2011 换成了另一个 VC6 非法形。

**[D6] include 接线三缺陷**:
- 方法签名扫描正则只匹配 `Type *`（指针，:2250），**按值参数类型不入 include/fwd 面** → `char GetTaskState_cc50(int, ECBStageTaskState)`（CCBStage.h:115）无接线 → C2061×46 族（census 样本逐字命中 'ECBStageTaskState'）。
- 枚举 fwd→include 提升（:2315-2327）依赖 `enum_names` = IDB 平铺枚举（:4370-4379），注解独有 5 枚举与嵌套形均不在册 → 按值枚举参数命中不了提升。
- 解析靠 `(OUTPUT_DIR/'X.h').exists()`（:2285-2288）探测**上一轮**的产物 → 顺序依赖 + stale 判真。

**[D7] 执行序 bug + 硬编码残留**（用户问题 7 清单）:
- should_skip_class（:1196-1231）: SKIP_CLASSES(:1209)/SDK_PLATFORM_TYPES(:1211)/SKIP_PREFIXES(:1216) 三个旧硬编码集**仍在数据驱动检查(:1223-1230)之前**——执行序 bug，迁移未收口。
- domain_exclude.json types.system_prefixes 含 **'gb'** 与垃圾条目 **'not a member'**；'gb' 与 collect/export 的显式 classes 清单（94 个 gb*）双轨冗余，且与 emit_headers :1112-1115 注释（2026-08-31 刻意移除 'gb'，理由：gb* 无外部头时必须本地生成防 C2039）**直接冲突**——同一裁决在两处相反。
- GAME_ENUMS_UNDERSCORE（:4517 {'_BGM','_FLIP','_BIGMAP_ELEMENT','_MU_R_STATE'}）硬编码白名单；_UNDERSCORE_TYPES（:4268）同类。
- main() :4257-4279 自建过滤链与 scope_tree 判据重复（第二套 skip 逻辑）。
- "枚举让位"(:5867)、colliding_enums/embedded_enums/enum_by_lower 大小写碰撞机（:4299-4311,:4381-4384,:4465-4478,:4537-4539）= 通道间临时粘合剂，注册表化后全废。

### 1.3 scope_tree.py

build（:63-142）本身结构良好；问题全在**消费侧**（见 D2）。5b 的方向正确（平铺伪影裁决），但 (a) 放错了层（scope_tree 无渲染权），(b) 判据不全（只比嵌套枚举 short 名，不比平铺枚举名/注解枚举名——`UIButton_UIBUTTON_STATE` 伪类漏不掉）。设计上 scope_tree 应升格为**唯一 gating + 唯一父子结构源**。

### 1.4 apply（pipeline/ida/apply_annotations.py 3b :2695-2782）

BADADDR 修复 + til 占位升级路径正确。两缺口:
- 占位升级/merge 后**无对账**: IDB 枚举成员集 vs enums.json 值集不比对（NUMSTATE 静默缺失）。
- 注解独有 5 枚举落地失败原因未显式呈报（`enum_notes` 截断 40 条 :2781）。

### 1.5 export（pipeline/ida/export_full.py :1049-1070）

枚举值原样写 u64（D-值失真）；无"平铺伪影被枚举遮蔽"的显式记录（codegen 只能猜）；'gb' 前缀跳过（:1017-1018 经 domain_exclude）与 emit 侧同病。

### 1.6 stage5_fixup.py

_fix_singleton_byvalue_decls（:1230-1246）: gbSingleton 族按值 decl → 指针。**语料中 gbSingleton 按值/强转已零命中**（grep 实测）——该规则已消化完毕。C2440×202/C2664×277/C2109×71 是**另外三个族**（见 §2.7），与枚举波正交。

### 1.7 生成头现状清单（钉死证据）

- `pal3/src/scalar_typedefs.h`: 4 typedef（_s_CatchableTypeArray, TypeDescriptor, UIPUSHBUTTON_STATE, unchar）——3 条违规 1 条合法。
- `Misc/UIPUSHBUTTON_STATE.h`: POD stub（含 `#include "scalar_typedefs.h"`）。
- `Misc/UIPushButton.h`: :21 struct fwd + :26 enum def（C2011 现场）+ :11 stale stub include。
- `Misc/Comp_DonateUI.h`: :15 `enum CDState;`（VC6 非法）+ :20 enum def。
- `Misc/UIButton_UIBUTTON_STATE.h` / `ParabolaCalculator_PRBL_STATE.h` / `UIStaticFlex_State.h`: 伪类 `_tail_000[4]`。
- `Misc/gbSingleton_gbGfxManager.h`: include 垫片指向**不存在的** `gbSingleton_gbGfxManager_.h`（孤儿文件，stale 清理盲区）。
- `Misc/PlayerMgr.h`: 标量包装形（`_tail_000[4]` + int-cast ctor）——PDB 证据 union(size1,35 members)，独立裁决线（§5 推迟）。

---

## 2. 端到端完备方案

### 2.0 总架构：一条类型注册表（TypeRegistry），四个消费面

```
data/annotations/enums.json ─┐
data/annotations/type_aliases.json (新) ─┼→ TypeRegistry（codegen 内单一构建，main() 开头）
data/annotations/domain_exclude.json ─┤      │
include/gbengine/*.h（外部域，只扫描不生成）┘      │
                                                  ├→ 面1 头生成（standalone enum 头 / 类头 / 别名）
asm/pal3/ida_structs.json（= apply 后的镜像）──────┤→ 面2 对账（registry vs _enums 分歧清单，只报不改真相）
                                                  ├→ 面3 include 接线（TYPE_HEADER_MAP，纯内存）
                                                  └→ 面4 清理（本次产物全集之差 = 删除清单）
```

registry 条目: `{name(注解键原样), values(注解字符串值, 保号), form: flat|nested, owner_cls?, source: annotation|gbengine, header_path}`。

### 2.1 注解层（真相声明，唯一需要人工维护的地方）

**E-1 枚举**: enums.json 为枚举唯一真相。键名原样即语料可见名——平铺键（UIButton_UIBUTTON_STATE）= 全局 enum；嵌套键（UIPushButton::UIPUSHBUTTON_STATE）= 类内嵌套 enum。**不做名字合成、不做键形转换**。
- 21 个 IDB 有而注解无的枚举逐条定谳进 enums.json 或 domain_exclude（D3D*→前缀已盖；gb*5 个→gbengine 域；GBPARAMHANDLE/LGT_TYPE/LIGHT_TYPE→人工补注解）。定谳前 codegen 遇到即报 `adjudication-required`，不渲染。

**E-2 别名表（新文件 data/annotations/type_aliases.json）**: 取代 POD 扫描。
```json
{ "_doc": "显式标量别名（原码 typedef 证据），唯一允许进 scalar_typedefs.h 的通道",
  "aliases": { "unchar": { "base": "unsigned char", "evidence": "IDA til 名 unchar size1；原码 gbengine 族字节别名" } } }
```
初始仅 `unchar`。`_s_CatchableTypeArray`/`TypeDescriptor` **不进别名表**（有真成员=真结构，按结构渲染，暴露真值）。

**E-3 域排除收敛**: domain_exclude.json（收集/导出/发射三面共读）:
- types.system_prefixes: 删 'gb'（域归属由 classes 段 94 个 gb* 显式条目承载；新增未列名 gb* 在 export 侧发 warning 进裁决队列）、删 'not a member'（导入垃圾）。
- emit_headers 的 SKIP_CLASSES/SKIP_PREFIXES/SDK_PLATFORM_TYPES 内容并入 classes/types 段后删除硬编码。
- GAME_ENUMS_UNDERSCORE/_UNDERSCORE_TYPES 白名单废除：registry 命中即发射，不按首字符猜。

### 2.2 apply 层（IDB 物化，只为 hexrays）

- 3b 占位升级路径保留；新增**对账后置**: 升级/merge 完成后逐枚举比对 IDB 成员值集 vs enums.json（注解值保号解析，'-1'→-1），缺失成员补 add（NUMSTATE→补入），值冲突只记录不改。输出 `data/status/enum_reconcile.json`（69 条逐名状态: landed/merged/value-diff/failed）。
- 注解独有 5 枚举用既有升级路径落地（BADADDR 修复已通，预期 69/69）。
- 验收: enum_reconcile.json failed=0 且 value-diff=0。

### 2.3 export 层（IDB → ida_structs.json 镜像）

- 枚举值**保号规范化**: `v = em.value; if v >= 2**63: v -= 2**64; elif v >= 2**31: v -= 2**32`（PDB/注解 type=int）→ JB_NULL 导出为 -1。
- 新增 `_shadowed`: 平铺 struct 伪影（til 占位 ordinal762 类）若与 registry 任一枚举名（平铺名/嵌套 short 名/无前缀大小写折叠名）同名 → 不导出为 struct，写入 `_shadowed` 列表（显式留痕，codegen 可证明性跳过）。
- 与注解枚举键差集写 `_enum_divergence`（对账的第二视角）。

### 2.4 codegen/emit_headers（核心改造）

**R-1 TypeRegistry 构建**（main() 开头，写任何文件之前）:
1. 注解枚举: enums.json 全键 → values 解析（int(v,0)，保号）。
2. gbengine 枚举: 扫 include/gbengine/*.h（现 :993 逻辑收编）→ source=gbengine，header=gbengine 映射。
3. 对 IDB `_enums` 做差集 → 注解缺的名进 `adjudication_required`（渲染时硬报错）。
4. 类型→头映射 TYPE_HEADER_MAP: 枚举名→`<get_class_dir(name)>/<name>.h`（嵌套枚举不进此表，随容器头）；类根（=scope_tree.roots）→同式；gbengine→外部映射。**纯内存，无文件系统探测。**

**R-2 唯一 gating**（消灭 all_classes 双轨）:
- 类循环遍历 `scope_tree.roots`（scope_tree.build 接收 registry 完成三裁决: 系统跳过、枚举遮蔽[平铺伪影同名→跳过并记 `_shadowed`]、伪影过滤）。5b 逻辑收编进 build，判据扩为 registry 全名集。
- `classes_with_headers`/`ida_classes` 自建链（:4257-4279,:4350-4379）删除。
- "枚举包装类跳过"（:4460-4463）删除——registry 命中名在进类循环前已被遮蔽。

**R-3 POD 通道关闭**:
- 删 `_pod_scalar_names()`（连死代码）、`_pod_scalar_names_cache -= methods_by_class`（:4242-4243）、generate_header POD 早退（:1980-1985）、`_POD_TYPEDEFS`（:1910）。
- scalar_typedefs.h 只写 type_aliases.json 的显式别名 + ida_defs.h 基座。产出恒定 1 条（unchar），回归可断言。
- 后果: `CatchableType`/`_s_CatchableTypeArray`/`TypeDescriptor` 转真结构头（成员齐，可编译，RTTI 铸形继续可用）——暴露 ✓。

**R-4 类体渲染规则（MSVC6 合法性矩阵）**:
| 嵌套类型 | 前向声明 | 定义 | 位置 |
|---|---|---|---|
| 嵌套 enum | **永不**（VC6 无 enum fwd；R76 的 `enum X;` 形废除） | registry 值渲染 | 类体顶部 public: 起始处，先于任何引用成员 |
| 嵌套 struct/union | **永不**（定义同类体内，fwd 冗余且是 C2011 风险源） | `_emit_nested_struct` | 同上 |
| 平铺枚举（registry flat） | 永不 | standalone 头 | `enum NAME { signed 值表 };`，按值排序，值字符串保号直写 |
| 平铺伪影被遮蔽名 | — | 无（进 `_shadowed`） | — |
- 删 A 路（:2709-2714）与 B 路（:2769-2781）两段嵌套 fwd 发射（合并为空——定义恒在类内）。
- `_emit_nested_struct` 数据源从 `_enums` 切到 registry（NUMSTATE/保号值即刻生效）。
- 嵌套枚举成员引用写短名（m_state；类内可见 ✓）；平铺枚举成员引用写全名（UIButton_UIBUTTON_STATE m_state；全局可见 ✓）。**同名遮蔽不可能发生**（注册表保证: 嵌套枚举 short 名不另发平铺头，平铺枚举名不作嵌套渲染）。

**R-5 include 接线（纯内存三步）**:
1. **扫描面补全**: 方法签名参数表逐参数 token 化（复用 split_params），按值参数类型入 include/fwd 面（修复 C2061×46 根因）；值成员/基类扫描保持。
2. **分类规则**: 类型 ∈ registry(gbengine) → include 外部头；∈ registry(枚举, flat) → **恒 include**（枚举不可 fwd）；∈ registry(嵌套枚举) → include 容器类头；类名 → 值用/指针用按现规则（include/fwd），但**解析查 TYPE_HEADER_MAP，不探测文件系统**。
3. 发射序: enum 头 include 段先于类头（确定性排序）。
- TU(.cpp) 侧: 现有机制（var 类型→include）同样切 TYPE_HEADER_MAP；body 中 `(EnumName)` 铸形名已由 var/cast 类型扫描覆盖（UISceneFrm.cpp 实证在接线）。

**R-6 产物集先知 + 清理**:
- main() 先算 `expected_outputs`（registry + scope_tree.roots + 模板映射路径推导的每个 .h），跑完写 `manifest`。
- 清理 = OUTPUT_DIR 现存 .h − expected − 手写基建名单（free_functions.h 等，入 domain_exclude 或 manifest 白名单）→ 删除并逐条日志。孤儿 `gbSingleton_gbGfxManager.h`、stale stub 由本步统一消灭。2026-10-20 的保守回退不再需要（模板实例化头在 expected 内）。

**R-7 大小写 FS 碰撞（UIEMOTE/UIEmote 类）**: registry 构建时按 casefold 检测，同盘名碰撞在**注册表构建期**一次裁决（嵌套消歧/头名加后缀并回写注解），generation 期不再有 colliding_enums/embedded_enums 机件。

### 2.5 模板映射路径（gbSingleton）

templates.json 单实例映射（decl_lines: `template <class T> class gbSingleton { public: static T *pSingleton; };`）**保持现状**——已数据驱动、VC6 合法（static 成员无引用则无需定义点）、与 PDB 真值一致。唯一动作: 孤儿垫片头由 R-6 清理。零新增投资。

### 2.6 枚举真值链终态（对照用户问题 4/5）

```
PDB(351, 保号值) → enums.json(人工定谳集, 唯一真相)
  → apply: til 物化 + 对账(enum_reconcile.json)          [IDB 只为 hexrays 成员名/类型]
  → export: 保号值 + _shadowed + _enum_divergence        [镜像留痕]
  → codegen: registry → 平铺 enum 头 / 类内嵌套 enum      [值=注解, 形=注解键形]
  → include: TYPE_HEADER_MAP 纯内存接线                  [枚举恒 include, 按值参数入扫描]
  → 语料: 成员名不用（现状零使用），铸形/声明全走 enum 名   [MSVC6 合法]
```
无注解结构 json 的枚举（ECBShowItemKind 类）**天然自洽**: 枚举头发射只依赖 enums.json，与 structs/*.json 解耦（R-1 之 1）；结构 json 若引用枚举名，经 registry 命中即可。

### 2.7 C2440×202 / C2664×277 / C2109×71 波（独立工作流，本方案只定界）

- **透明包装族**（C2440 'class tagEffSPSlot'→'char'/char*、C2664 同型、SaleUI_SortData）: hexrays 把小类局部按透明槽声明，语料却decl成类值。修法=**声明重定锻**（var 改铸宽度真类型），不是插 cast（cast 会掩盖归属错误）。泛化 _fix_singleton_byvalue_decls 为注解驱动 `transparent_wrappers` 清单，逐族证据落地。
- **C2109 `0x3[v]` 常量索引形**（CCBStage.cpp:7463 等实测）: v 被声明为标量而原码为数组/指针 → var 重定锻为数组/指针（decomp 证据），或索引形改写。stage4/5 家族规则。
- **C2664 其余**: 按被调方聚合，签名错在注解层修（mangling 证据），调用点错在 stage5 arg-cast。全部**排在类型系统落地之后**（本方案消波后其暴露面更纯）。

---

## 3. 实施序列（每步独立可验证；回退点 = git tag + probe census diff）

| # | 步骤 | 内容 | 验收标准 | 回退 |
|---|---|---|---|---|
| P0 | 基线冻结 | git tag `redesign-baseline`；跑 s1+s2 存 census | census 与 §1.1 一致 | — |
| P1a | 别名表 | 建 type_aliases.json（unchar） | schema 校验过；仅 1 条 | 删文件 |
| P1b | 域排除收敛 | domain_exclude 删 'gb'/'not a member'；三硬编码集内容并入 | **等价性测试**: 新旧 should_skip_class 对 1031 导出名+85 枚举全量 diff=空（'gb' 例外: classes 段显式名单为准，diff 仅允许新增未列名 gb* 的 warning 清单） | git revert |
| P2a | export 规范化 | 值保号 + _shadowed + _enum_divergence | JB_NULL/DLG_MSG_NONE/_invalid=-1；_shadowed 含 UIPUSHBUTTON_STATE 等 | revert |
| P2b | apply 对账 | 3b 后置对账 + 5 枚举落地 | enum_reconcile.json: 69/69，failed=0，value-diff=0（NUMSTATE 在 IDB） | revert（3b 原路径仍可跑） |
| P3a | registry + gating | R-1/R-2（scope_tree.roots 收编 5b） | 单测: 平铺伪影零类头；roots=期望集 | tag `pre-registry` |
| P3b | POD 关闭 | R-3 | scalar_typedefs.h 恒 1 条；stub 头清单=∅；CatchableType 族真结构头可编译（s1 单元实测） | 同上 |
| P3c | 嵌套渲染 | R-4（删双 fwd 路；registry 供值） | lint: 生成头中 `enum \w+;`=0、`struct E;`+`enum E{` 同文件=0；UIPushButton.h 无 fwd；Comp_DonateUI.h 无 `enum CDState;`；嵌套枚举值=注解（NUMSTATE 在场） | tag `pre-render` |
| P3d | include 接线 | R-5 | CCBStage.h 含 ECBStageTaskState.h include；TYPE_HEADER_MAP 单测全命中；文件系统探测代码=0 | 同上 |
| P3e | 清理先知化 | R-6 | 孤儿/stale 清单=0；产物集=manifest | tag `pre-clean` |
| P4 | 普查对账 | s1: C2011/C2079/C2061/C1083 → 0；s2: C2011×61/C2079×61/C2061×46 → 0 | S2 预期 112→**127~135**（C2011/C2079 单元≈18 个 + C2061 单元部分恢复；其余单元残错不变属 §2.7）；C2440/C2664/C2109 计数**不得恶化**（回归门） | tag `pre-probe`，regression_detector 对照 |
| P5 | （独立流）透明包装/C2109/C2664 族 | §2.7 | 逐族 census 减记，S2 逐波上行 | 逐 tag |

P3a–P3e 为一个原子 PR 序列（同一 commit 链），P1/P2 可先行独立合入（P2 完成前 P3 对账面降级为 warning）。

---

## 4. 明确不做什么（推迟项与理由）

1. **不恢复任何 POD 扫描判据**（含 size/无成员/成员指针三证据源混合式）——扫描=启发式=静默降级温床；别名唯一合法通道=显式注解表。
2. **不做枚举前向声明的任何形式**（含类内 `enum X;`）——VC6 无此能力，R76 形态废除。
3. **不把嵌套枚举强改平铺（或反向）来迁就语料**——键形=注解真相；个别键形与语料用法冲突时作为数据定谳（改 enums.json 键+留痕），不在管线里合成名字。
4. **不用 cast 注入消 C2440/C2664 透明包装波**——声明重定锻才是暴露原则的正解（§2.7 独立流）。
5. **gbSingleton 模板不加新机制**——映射路径已自洽，仅清理孤儿垫片。
6. **PlayerMgr 标量包装形、union(35 members) 真值还原、_tail 布局重划**——独立裁决线（涉 PDB union 语义与 882-struct 收缩），不与枚举波混车。
7. **不在本轮重导 decomp 换取 body 枚举成员名**——现语料全为铸形用法（零成员名依赖），重导收益为零风险为正（大面积 cast 变动）。
8. **不动 D3D*/Windows SDK 枚举发射**——前缀域排除已覆盖，registry 仅保留 adjudication-required 报警通道。
9. **不做 include 顺序的全局优化**——只保证枚举先于类的确定性序；其余按字母序，不做依赖图重排（收益低、回归面大）。

---

## 5. 自洽性核对表（方案内部冲突自查）

- 枚举头通道唯一: 平铺→standalone（R-4）；嵌套→类内（R-4）；遮蔽名→无产物（R-2）——scalar_typedefs 不再承载枚举名（R-3 别名表由人工维护且 E-1 规定枚举名禁入别名表）→ 无双形式可能。
- 嵌套成员类型名解析: 类内=短名（嵌套枚举可见域）；类外=全名（平铺枚举全局）——注册表保证两形不同名共存时各归各头。
- 暴露原则逐点: 伪类 _tail 渲染废除（D4 族→真 enum 头）；POD typedef 废除；adjudication-required 硬报警；_shadowed/_enum_divergence/enum_reconcile 三份留痕。
- MSVC6 合法性逐点: 无 enum fwd；无名双形式；enum=4B（既有 :1703/:2843/:3937 尺寸判据与 registry 对齐，size1 伪影修正逻辑保留）；别名表别名宽度不参与布局（unchar 仅铸形/声明用）。
- 层间无裁决重复: skip 裁决只在 domain_exclude（三面共读）；枚举/类裁决只在 registry；父子结构只在 scope_tree；文件清理只在 manifest 差集。
