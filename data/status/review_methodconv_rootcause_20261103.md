# 独立对抗性复核：methodConversions 重写误击根因分析（2026-11-03）

复核对象：「methodConversions 重写误击根因链」（现象→契约→证据→根因假设）。
复核方式：只读取证 + 复算 + 编译日志逐形归因。铁律执行：**不准确=不判定**；所有引证带 `文件路径:行号`。
代码引用以 `pal3-redivivus/thirdparty/ghidra-reconstruct/`（下称 *engine*）为准；与顶层 `thirdparty/ghidra-reconstruct/` 逐字节相同（`diff` exit=0，两副本无分叉）。

---

## 1. 总裁

**部分成立。**

| 链条环节 | 裁定 |
|---|---|
| §2 契约读取（MethodCallMapping 四元组 / config 三元组 / 解析期） | **成立**（3 处行号边界有 1 行级微差，见 §2.1） |
| §3 证据计数（3957 条 / 272 重名键 / 801 损失 / top-8 重名） | **算术成立、落点错误**：数字逐一复算全中；但「byFunctionName 一键一值 ⇒ 801 失映射」的落点是**死索引**（生产面零消费），且 801 未过生成器按址去重与抽取层实际键空间（实际 416/146 键） |
| §4 根因「Record<name> 键空间冲突 ⇒ 误映射 ⇒ 重写误击」 | **部分成立**：调用侧名单值 Record + 无类型/元数消歧 ✓ 真实存在；但分析**漏了两套既有消歧机制**（byAddress 按址解析 + codegen 限定键/共名删除），且误击只是 void* 形的**少数派机理**——主机制是「正确目标 + 接收者类型缺（void\*），插件不上转型」 |
| 形① `expected '{' before '.'` ×1377 挂在本链 | **归因错误**：实为 globals.h 点号模块名当 C++ 命名空间标识符的**静态病**（6 物理行 × 227 TU = 1362），与重写零机制关联 |
| 形② `void* 非对象指针` ×5083 挂在本链 | **成立（重写诱发 ✓）**，但根因拆解需修正：类型缺为主、错实例误击为辅 |
| 形③ `local_4._0_1_` ×1359 挂在本链 | **并行病，非同链**：栈变量联合视图未在声明处具象化；重写插件在机制上不可能产出 `._0_1_` 后缀 |

一句话：**「重写误击」机制真实且确有其形，但三形不是一个根因链——一形误挂、一形并行、一形成立而机理归属需从「重名覆盖」修正为「接收者类型缺为主 + 键空间名单值为辅」。**

---

## 2. 证据核对表（逐处行号）

### 2.1 契约读取核对

| 待核主张 | 裁定 | 实测 |
|---|---|---|
| MethodCallMapping = `{className, methodName, thisParam, originalName}` 四元组 @ method-call-rewrite.ts:49-58 | ✅ 成立 | 接口体在 `method-call-rewrite.ts:49-54`；56-58 是 MethodCallRewriteOptions 开头（`methodMappings?: Record<string, MethodCallMapping>` 在 :57-58）。引用区间 49-58 覆盖两者，无误 |
| config 面 `MethodConversionEntry{address, className, methodName?, thisParam?}` @ schema.ts:133-141 | ✅ 成立 | `schema.ts:133-142`（字段 :134-141，:142 闭括号）。注意其**键是 address 不是 name**——config 本身可按址表达任意重名群 |
| 解析在 methods/index.ts；`byAddress + byFunctionName` 双索引；`indexByName` 在 applyMethodConversions 期填充 | ✅ 成立 | `methods/index.ts:40-41`（两 Map）；构造器占位 `:46-56`；`indexByName` `:75-85`（`byFunctionName.set` 在 :84）；applyMethodConversions 内调用 `:251-256`（「Index BEFORE renaming」注释 :255） |
| MethodCallMapping 在 methods/index.ts 亦有副本 | ➕ 补充 | `methods/index.ts:28-33` 同名接口（形状一致）；`impl.ts:537` 消费 `Record<string, MethodCallMapping>` |

### 2.2 「Record<name> 无法表达重载群」推断核对（必攻 2）

**裁定：对调用侧成立；「无消歧机制」不成立——存在两套被分析遗漏的机制，且定义侧本就按址消歧。**

| 机制 | 位置 | 行为 |
|---|---|---|
| 定义侧按址消歧（已有） | `methods/index.ts:40,49-55`（byAddress）、`:63-65`（get by addr）、`:239-256`（applyMethodConversions 用 `funcByAddr` 按址匹配、逐址 rename） | 改名/入类**逐址正确**，52 个同名 `Update` 的定义侧互不踩踏 |
| 撞名覆盖（真凶） | `methods/index.ts:90-102`：`buildPluginMappings` 以 `entry.originalName` 为键写 Record（:94），后写胜 | 同名多类 ⇒ 只剩一条映射（**误映射**而非单纯失映射） |
| 调用侧名单值查找 | `method-call-rewrite.ts:209-211`：`mappings[qualified] ?? mappings[unqualified]`，只按调用点文本名 | 无类/元数/签名消歧；唯一护栏是 `:216`（`args.length <= thisParam` 则跳过）与 `:230`（null-like 接收者跳过） |
| codegen 消歧（已有，被漏） | `codegen/index.ts:1024-1060`：`namespace::originalName` 限定键（:1052-1056）+ **与自由函数共名的裸名整体删除**（:1044-1052，含 console 报告） | 自由函数共名场景已被压制（「失映射」的真正通道）；**但 method-vs-method 跨类同名不在其判定内**（两方都有 parentClass，`ambiguousNames` 不收） |
| currentFunction 绑定（已有） | `impl.ts:2467` 逐函数传 `currentFunction`；`method-call-rewrite.ts:222`（Rule 3 同类判定 `mapping.className === currentFn.className`） | 绑定存在；但 className 撞名时 Rule 3 会把**别类调用**改写成 `this->M()`——误击放大器 |

⇒ **生成器缺的那一环不是 methodName/thisParam 显式化**（methodName 缺省取 func.name、thisParam 缺省 0 对 __thiscall 正确，均逐址派生，`methods/index.ts:265,52`）。缺的是：
1. **调用点→callee 地址绑定**（extractor 知道每个 CallExpr 的目标地址，插件却在文本名键空间上事后查找）——结构性缺口；
2. 接收者类型/转型（插件用裸 thisArg 建 MemberExpr，`method-call-rewrite.ts:257-265`，**从不 cast 到 mapping.className**）；
3. 生成器侧 guard：双指针接收者排除与 quest-state 排除**只存在于被禁用的 tag 路径**（`methods/index.ts:193-209`），config 路径（`gen_method_conversions.py:12-15`）裸奔。

### 2.3 801 计数核对（必攻 3）

**裁定：注解空间算术逐位复现；「（byFunctionName 一键一值）」落点错误、口径高估。**

复算（`data/annotations/structs/*.json` 的 `methods` dict 全量，2026-11-03 读数）：

| 口径 | 总数 | 重名键 | 损失（Σ(v−1)） | top 重名 |
|---|---|---|---|---|
| 注解原始（全部 methods 条目） | **3957** | **272** | **801** | Update×52 · Render×50 · Destroy×50 · Create×41 · OnMessage×37 · Reset×34 · Init×32 · `_scalar_dtor`×23（✅ 与被审分析逐字一致） |
| 生成器按址去重后（`gen_method_conversions.py:13-14` 的 `seen` 集，同址多注解 317 条先丢） | 3640 | 197 | 598 | Render×47 · Destroy×47 · Create×39 · Update×37 … |
| 抽取层 func.name 实际键空间（`functions.ndjson` 5946 函数） | 5946 | 150 | 419 | Destroy×31 · Update×27 · Render×27 … |
| 3640 转换条目在快照中命中者（832 条地址无对应函数） | 2808 | **146** | **416** | 同上 |

三处落点纠错：
1. **byFunctionName 是死索引**：生产面唯一消费是测试（`__tests__/method-conversions.test.ts:94`）；全仓（含 pal3-redivivus 非 thirdparty 面）无第二消费者。它的覆盖损失不产生任何实效。
2. **实效落点是 `buildPluginMappings` 的 Record**（`methods/index.ts:94`）与 `mergedMappings`（`codegen/index.ts:1019,1052-1056`）；操作面重名损失 416/146 键（当前快照口径），非 801。
3. **「失映射」用词不当**：Map/Record 覆盖保一条 ⇒ 主要是**误映射**（错类存活）；真失映射通道是 `codegen/index.ts:1044-1052` 删裸名（与自由函数共名者），有独立计数 log。
4. 另发现 config 静默撞址：`project/project.json` methodConversions **3640 条 / 3632 唯一地址（8 对重复）**，构造器 `byAddress.set` 后写胜（`methods/index.ts:49-55`，无告警）。

### 2.4 现象数字核对（编译日志逐形计数）

日志来源：`/tmp/conv_errors.txt`（注入后整编，32516 行）· `/tmp/full_errors.txt`、`/tmp/full2_errors.txt`（quick 基线，各 12578 行，复现一致）。

| 形 | 声称 | 实测（conv） | 基线（full） | 裁定 |
|---|---|---|---|---|
| 总错 | 32516 / 12578 | 32516 行 ✓ / 12578 行 ✓ | — | ✅ |
| `expected '{' before '.'` | ×1377 新增 | **1377** ✓（globals.h 1362 + KERNEL32.DLL.cpp 7 + globals.cpp 6 + KERNEL32.DLL.h 2） | **51**（globals.h 36 + 后三者 **7/6/2 逐一同数**） | 计数 ✅；「新增」措辞与归因 ✗（见 §3-H1） |
| `void* 非对象指针` | ×5083 新增 | **5083** ✓，全部为 `‘void*’ is not a pointer-to-object type` | **33**（全在 _unnamespaced.cpp） | ✅ 重写诱发成立 |
| `local_4._0_1_` | ×1359 新增 | `._0_1_` 族共 **1395**，其中 `local_4` 精确 **1359** ✓（其余 36 为 local_14/g_nActor/pvStack_c 等） | **0** | 计数 ✅；归因 ✗（见 §3-H2） |

---

## 3. 替代假说检验（必攻 4）

### H1（替代·已证）：形①= 点号模块名命名空间病，非重写链

- 1377 例中 **1362 聚在 globals.h 的 6 个物理行**（3482/3488/3494/3500/3506/3514），逐 TU 重复报出。
- `globals.h:3482` 原文 = `namespace DINPUT8.DLL {`；错误列 18 恰为 `.`。`namespace GBENGINE.DLL::gbRefObject {` 等 5 行同病（`globals.h:3488,3494,3500,3506,3514`）。**DLL 模块名带点被当 C++ 命名空间标识符** ⇒ GCC `expected ‘{’ before ‘.’ token` + 配对 `expected unqualified-id before ‘.’ token`（各 1377）。
- 数字闭合：6 行 × **227 个 TU**（conv 日志恰含 227 个错误文件）= **1362**，+15（KERNEL32.DLL.cpp 7 + globals.cpp 6 + KERNEL32.DLL.h 2，与基线逐一同数）= **1377** ✓ 精确闭合。
- 基线同形 51 = 同样 6 行 × 约 6 个 TU + 15。⇒ **计数差 = TU 覆盖差（quick 增量 vs 整编），不是病势增长**。
- 机制上与 method-call-rewrite 零交集（该插件只动 CallExpr/MemberExpr/Identifier，`method-call-rewrite.ts:170-272`；globals.h 是 extern 声明头，无调用点）。

**裁定：形①挂链错误，属独立病灶（namespace 发射把模块名 `X.Y` 直写为命名空间名）。**

### H2（替代·已证）：形③= 栈变量联合视图未具象化，与注入并行

- 错误形 = `request for member ‘_0_1_’ in ‘local_4’, which is of non-class type ‘uint32_t’`。
- 同函数内声明与用法对照（`BINK.cpp`，转换体）：声明 `uint32_t local_4;`（:22）vs 用法 `local_4._0_1_ = 1;`（:38）、`local_4 = CONCAT31(local_4._1_3_, 2);`（:47）——Ghidra 反编译器的**匿名 union 成员后缀**（offset_size 命名）出现在正文，而抽取层变量类型是 `undefined4`（`functions.ndjson` @004236d0：`{"name":"local_4","dataType":"undefined4","size":4,…}`）⇒ 声明被发射成标量。表面形（union 成员后缀）与被审分析的 union 假设一致；**深层根 = 反编译正文的联合视图 vs 发射声明不具象化**（emit/类型双缺）。
- 机制排除：method-call-rewrite 的三个 visitor（`method-call-rewrite.ts:170-272`）不触碰变量声明、不生成 `._0_1_` 标识符。
- **转换无关的硬证**：1395 例中 **23 例落在 `_unnamespaced.cpp`**（未转换函数的集合区）；若属重写链，不应在插件不改写的文本形态上出现。
- 基线 0 例 ⇒ 增量来自 14:01 的抽取快照刷新（见 §5-2），时间同现而非注入因果。

**裁定：形③与 methodConversions 根因是并行病（同 regen 异病灶），不应挂在误击链上修。**

### H3（替代·部分成立）：void* 形的主机制 = 接收者类型缺（typeOwnership/成员类型），误击只是少数派

5083 例逐例解析接收者表达式（读报错行源文）：

| 接收者形态 | 例数 | 占比 | 例句（文件:行） | 机理 |
|---|---|---|---|---|
| 字段槽 cast-deref（`(*(void**)((int)this+off))->M()`） | 3976 | 78% | `ArcLocaleRole.cpp:404` `(*(void**)((int)this + 0x14))->InitActorComponents();` | 目标多半正确，**类成员槽被发射为 void\*\*** ⇒ 解引用即 void* ⇒ 成员调用不可编 |
| 局部/寄存器副本（`in_ECX`/`pvVar*`） | 748 | 15% | `ARC_PlayerAtt.cpp:31` `in_ECX->_todo_445B90();`（`void* in_ECX;` :21） | this 参数/ECX 副本类型为 void* |
| this 族参数（`this_00`） | 100 | 2% | `CCBItemWindow.cpp:224` `this_00->Destroy();` | 形参未带类类型 |
| **真·错实例/自由函数误击** | 约 80-120 | 2-3% | `CCBEditor.cpp:12` `lpString2->SetDialogTemplate();`（lpString2 是 `char*` 形参 :10）· `Actor.cpp:1539-1540` `PTR_s_…_tga_…->GetChildCount(…)`（数据指针当实例）· `_unnamespaced.cpp:15695-15700` `off_5F50B4->SetMaterialName(0);` 等 4 例 · `ScriptVM.cpp:431` `in_stack_00000004->UpdateTransform_2710();` | 名键映射命中了本不该重写的调用（参数当实例/数据符号当实例） |
| 语法坏形（真·重写破坏） | 2 | — | `_unnamespaced.cpp:15127` `~in_ECX->CCBUI();`、`:9459` `~in_ECX->UIListBox();` | 析构调用 `~CCBUI(x)` 被解析为 `~(CCBUI(x))`，call 重写后 `~` 挂在接收者前 |

关键推理：**插件不给接收者上转型**（`method-call-rewrite.ts:257-265` 直接以裸 thisArg 建 MemberExpr），因此即使映射 100% 正确，`(*(void**)(this+0x14))->M()` 一类照样报 void*——**类型缺机理对形②具有充分性**；而 801 重名撞名导致的是「错类映射」，其典型形应为「错类成员不存在/误绑」，不是「数据指针当实例」。真误击例（lpString2/PTR_s_/off_ 等）的成因是**名单值查找命中非方法调用**（键空间粒度问题），与 801 覆盖损失同源但不同一计数。

**裁定：形②= 重写诱发 ✓（基线 33→5083，全部 void*）；但根因应修正为「接收者类型缺（主）+ 名单值误击（辅）」。被审分析把 void* 形整体归于「错误实例被当方法重写 ⇒ 801 失映射」——主机制归属**不准确**。误击/类型缺的精确占比需逐呼叫点 target 取证，本报告**不判定**（§5-4）。**

### H4（替代·成立）：覆盖差混杂

quick 基线与整编非同覆盖 A/B（`pal3-redivivus/pipeline.py:13` 「quick = build+audit **增量环**」）。globals.h 形 6×227 精确闭合证明两日志的 TU 覆盖差一个量级。⇒ 「32516−12578 = 注入损伤」的整体差值**不可直接归因**；有效归因必须落在逐形逐文件机理上（§2.4/§3）。

### H5（并存事实）：抽取刷新混杂

时间线（文件系统读数）：full_errors 13:45 → full2 13:57（=12578 复现）→ project.json 被改 13:59 → **codegen-snapshot 重写 14:01:26**（manifest `writtenAt 2026-11-03T06:01:26Z`）→ output 重生成 14:04 → conv_errors 14:05。注入与一次抽取快照刷新同窗发生；形③（0→1395）与形①（globals.h 36→1362）的增量均可用刷新/覆盖解释，无法在两份日志内分离。

---

## 4. 修复案评审（必攻 5，约束：数据不变、机制修）

| 案 | 可行性 | 风险 | 裁定 |
|---|---|---|---|
| **A. 生成器消歧**（每名唯一键 + thisParam 显式） | **不可行（作为主修）**：键空间在 `buildPluginMappings`（`methods/index.ts:94`，以 originalName=func.name 为键）——生成器（`gen_method_conversions.py:15` 只发 address+className）**无法改变该键**；methodName 唯一化会改发射成员名（语义变更，违「数据不变」）。thisParam 显式收益趋零（缺省 0 对 __thiscall 正确，`methods/index.ts:52`） | 强行做会把矛盾转移到类声明/调用名不一致 | ✗ 不推荐主修；**可做 guard 补强**：生成器补双指针接收者/quest-state 排除（现仅 tag 路径有，`methods/index.ts:193-209`）+ 撤 8 对重复地址（§2.3-4） |
| **B. 修解析（按址消歧优先）** | **可行，推荐方向**。分层：<br>B1 `buildPluginMappings` 撞名 fail-loud（弃键+报告；把 `codegen/index.ts:1044-1052` 的共名删除扩展到 method-vs-method）<br>B2 插件侧：非对象指针形接收者（数据符号/字符串参/整型/槽 void**）与析构形（UnaryExpr `~` 包裹）不重写（扩 `isNullLike` 族，`method-call-rewrite.ts:100-114`）<br>B3 结构修：发射期按 callee **地址**重写（extractor 有目标地址），彻底脱离名字键空间 | B1 静默丢转换 vs 现状误转换——fail-loud 更安全；B2 漏判会残留少量误击；B3 触 emitter 面大、需回归。若给接收者补 cast（`((Cls*)recv)->M()`）虽能压 void* 形，但会把错类误击从**编译期响亮**压成**运行期静默**——对字节匹配管线是劣化，**不推荐** | ✓ 推荐 B1+B2 先行，B3 排期 |
| **C. 关 plugin 只留签名导入** | **可行（作为止血/归因隔离阀）**：插件本就 `defaultEnabled:false`（`method-call-rewrite.ts:290`），停发 methodMappings 即静默。⚠️ 但 `applyMethodConversions` 的改名/入类（`methods/index.ts:262,302`）仍跑 ⇒ 调用点裸调用会缺声明；要干净对照须整条 methodConversions 置空（生成器输出为空），回到引擎设计默认「自由函数 + 显式 this 参数」姿态（`codegen/index.ts:1006-1012` 注释明示） | 作终态则放弃 this->member 读性收益 | ✓ 作为**第一步对照 build**（一次即可验证形②去留并隔离 H4/H5 混杂） |

**明确推荐路径**：`C（一次对照 build，隔离归因）→ B1+B2（机制修，数据不变）→ B3（按址重写，结构性根治）；A 仅做 guard 补强`。
形①（namespace 点号）与形③（联合视图声明化）**分灶修**：前者改命名空间发射（模块名 `X.Y` → 合法标识符），后者给 `undefined4` 栈变量具象化联合视图声明——两者都不挂 methodConversions 链，避免错修。

---

## 5. 未复验（明确保留，不判定）

1. **32516 vs 12578 非同覆盖 A/B**：quick=增量环（`pipeline.py:13`）；总差值含 TU 覆盖成分，未做同覆盖重测。
2. **14:01 抽取快照刷新的混杂**：形③ 0→1395、形① globals.h 36→1362 的增量与该刷新无法在现有两份日志内分离（需基线态旧快照或「同快照±注入」对照 run）。
3. **416/146 键为子集口径**：3640 转换条目中 832 条地址在当前 `functions.ndjson` 无对应函数（地址漂移或抽取覆盖缺）——全量口径的重名损失未复验。
4. **误击 vs 类型缺的精确占比**：需逐呼叫点 call-target provenance（调用点实际目标地址 vs 映射类）；本报告只证「类型缺机制充分」+「误击实例存在」，占比**不判定**。
5. **`is not a member of / has no member named` 2206 例族未全量裁定**：抽样见 Rule-3 疑形（`CCBEditor.cpp:17` `this->vmethod_6(…)`——类声明缺成员/错类混杂）、限定名指非常静态成员族（`BINK.cpp:155` `gbSound3DNode::~gbSound3DNode(this);` 等 872 例）、槽位 Release 形（`C3DSpark.cpp:23` 等 307 例）——疑三病灶混流。
6. **8 对重复地址的静默覆盖**（`project/project.json` 3640/3632，`methods/index.ts:49-55` 后写胜）影响面未查。
7. **重名统计口径随注解流变**：3957/272/801 为 2026-11-03 当时 `data/annotations/structs/*.json` 读数，后续注解变更即漂移。
8. **`thisParam:-1`（静态方法）无 config 通路**：`loader.ts:160-162` 校验 thisParam 非负，tag 路径（`methods/index.ts:215` 产 -1）已禁用（`codegen/index.ts:1011`）——当前面无静态方法误击暴露，未实测插件对 thisParam=-1 的行为（`method-call-rewrite.ts:216` 对 -1 不拦截，存在 `args[-1]` 悬空路径）。

---

## 附：本报告全部一手证据指针

- 契约：`pal3-redivivus/thirdparty/ghidra-reconstruct/packages/cpp-parser/src/transform/plugins/builtins/method-call-rewrite.ts:49-54,56-68,100-114,120-132,170-272,209-211,216,222,230,257-265,290`；`packages/reconstruct/src/config/schema.ts:20-22,133-142`；`packages/reconstruct/src/methods/index.ts:18-33,39-57,63-85,90-102,108-120,179-222,234-303`；`packages/reconstruct/src/codegen/index.ts:1003-1070`；`packages/reconstruct/src/codegen/impl.ts:2446,2467`；`packages/reconstruct/src/config/loader.ts:152-162`
- 生成器：`ghidra_track/gen_method_conversions.py:9-17`（seen 按址去重 :13-14，只发 `{address, className}` :15）
- 数据：`data/annotations/structs/*.json`（3957/272/801 复算）· `pal3-redivivus/project/project.json`（3640/3632）· `pal3-redivivus/project/.ghidra-mcp/codegen-snapshot/functions.ndjson`（5946 函数；004236d0=`Reset`，local_4=`undefined4`）· `…/manifest.json`（writtenAt 2026-11-03T06:01:26Z）
- 编译日志：`/tmp/conv_errors.txt`（32516）· `/tmp/full_errors.txt`、`/tmp/full2_errors.txt`（各 12578）· 逐形归因样本：`globals/globals.h:3482,3488,3494,3500,3506,3514` · `BINK.cpp:22,38,47` · `ARC_PlayerAtt.cpp:21,31` · `ArcLocaleRole.cpp:404,408` · `CCBEditor.cpp:10,12,17` · `Actor.cpp:1539-1540` · `_unnamespaced.cpp:15127,9459,15695-15700`
