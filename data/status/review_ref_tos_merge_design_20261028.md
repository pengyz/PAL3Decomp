# 对抗式设计复核：ref_params TOS 合并方案（2026-10-28）

复核对象：`_fix_ref_params` 家族单一 TOS 合并方案（7 点，人类原则已认可「stage 间零互引、单一 TOS」）。
复核方法：全部结论经源码实读 + AST 外依扫描 + 既有测试实跑 + `cli.py status` 实测复验；证据锚点（文件:行号）随结论走。

---

## 1. 总结

**ACCEPT-WITH-FIXES** —— 方案方向正确（单一 TOS、零 stage↔stage 边、表单源 [R99]），但**两条实证性缺陷必须先修**：
① 「stage3 版=仅 Case1 剥&」的双实现 diff **不完整**——stage3 版尾部还有 `_tail_000` 折叠（stage3_cleanup.py:2248-2249），
被既有测试 `tests/test_vtable_call_transform.py::test_form3_existing_tail_000_fold_is_preserved` 逐字锁死，直接下沉会让该测试红；
② 「删本地实现、双双向下导入」若照字面执行且 stage3 调用点不改（stage3_cleanup.py:2061 现为 `_fix_ref_params(code)` 无 ctx），
超集的 **Case 3 无证据门**会在 stage3 打开「裸标识符补 `*`」的 C2100 复燃面（F1a 门的 docstring 自证此 bug 类）。
修法（均在第 3 节定稿中落实）：折叠 `_tail_000` 尾步**留在共享 `_fix_ref_params` 内**（对 stage5 幂等无害，见攻击点 1）；
stage3 调用点**必须传 ctx**（`TransformContext.sig` 两 stage 同型，实证见攻击点 2）；其余为工程性修正。

---

## 2. 逐攻击点 verdict + 修法

### 攻击点 1 —— 合并方向风险：stage5 超集套到 stage3 是否改变 stage3 产物？

**VERDICT：会改变，且比方案自评的差集更大。方案的双实现 diff 漏了一条反向差异（`_tail_000` 尾步）。**

实测双实现真差集（AST 逐函数比对 + 逐行实读，非目测）：

| 维度 | stage3 `_fix_ref_params`（2166-2250） | stage5 `_fix_ref_params`（631-709） |
|---|---|---|
| Case 1（`&` 剥除） | ✓ | ✓ |
| Case 2（cast-ptr 前插 `*`） | ✗ | ✓（`_fix_single_ref_arg` L738-741） |
| Case 2b（`*stru_XX` → `*(T*)&stru`，`_GB_REF_PARAM_TYPES` 承重） | ✗ | ✓（L744-749） |
| Case 3（裸标识符补 `*`，F1a 证据门） | ✗ | ✓（L751-790，ctx 缺失时**退化为无门**） |
| `_tail_000` 折叠（`X->_tail_000` → `*(void**)(X)`） | **✓（L2248-2249 尾步）** | **✗** |
| ctx / `_build_var_types` 证据 | ✗（签名 `(code)`） | ✓（签名 `(code, ctx=None)`） |

即真正的漂移是**双向**的：stage3 缺 Case2/2b/3（方案已知），但 stage5 缺 `_tail_000` 折叠（方案未知）。
「stage3 版=仅 Case1」的表述因此**不成立**，定稿必须按「互有增减」处理。

**修法（行为差集分析 + 验证法）：**

1. **`_tail_000` 尾步留在共享 `_fix_ref_params` 内部、位于实参循环之后**（与 stage3 现执行位序逐字一致）。
   幂等性证明（stage5 侧无害）：折叠正则 `(\w+)->_tail_000\b(?!\[)`（stage3:2249）的输出 `*(void**)(X)` 不含
   `->_tail_000` 可匹配形；被 `(?!\[)` 故意跳过的 `X->_tail_000[N]` 形再次命中时同样跳过；`(\w+)` 不匹配的残形
   （如 `(obj)->_tail_000`）两次都不匹配 ⇒ stage5 侧逐字幂等。**带单测锁死**（测试清单 T5）。
   备选（TOS 纯度优先）：抽成 stage3 局部 `_fold_vptr_tail_000` 尾步 + 调用点显式串联——但需改
   `test_form3_existing_tail_000_fold_is_preserved`（tests/test_vtable_call_transform.py:289-291 现直调
   `s3._fix_ref_params`）且给实现者留「忘加尾步」的静默破坏面。**裁定取前者**（零测试搅动、零调用点搅动、
   同正则幂等可证）；共享函数 docstring 显式写明尾步归属与幂等依据。
2. **stage3 调用点必传 ctx**：`stage3_cleanup.py:2061` `code = _fix_ref_params(code)` →
   `code = _fix_ref_params(code, ctx)`。依据：stage3 的 `run(code, ctx)`（1795）与 stage5 同收
   `TransformContext`（transform.py:17-32，含 `sig` 字段）⇒ F1a 证据门在 stage3 可用。
   **不传 ctx 的后果**：`_fix_single_ref_arg` Case 3 在 vt={} 时走「unknown → 补 `*`」分支（L788-790），
   即 docstring 自证的 `Rotate(v10, *v15)` C2100 bug 类在 stage3 全量打开。
3. **A/B 行为差集验证法**（三步，写进定稿验证序列）：
   - **C1 态激活面普查**（改 stage3 之前，两实现并存时）：临时脚本对 decomp 语料**逐函数体**同时跑
     旧 stage3 实现与新共享实现（都活着，不需第三份拷贝），输出 (文件, case-kind, 旧文本, 新文本) 多重集。
     case-kind 直方图（case1/case2/case2b/case3-value/case3-ptr/case3-array/case3-global/none）即**行为差集全集**。
   - **生成物 A/B**：C2（stage5 重接线）后跑 `loop` 得读数 R2；C3（stage3 重接线）后得 R3；
     对 `pal3/src` 做逐文件哈希 diff，变化单元按普查的 case-kind 归因。
   - **等价/改良判读**：`*stru→*(T*)&stru`（Case2b）=C2100 修复向；`x→*x`（Case3-unknown）=风险向；
     `x→x[0]`（Case3-array）=C2664 修复向。R3 的 S2/错误族须与差集逐条对得上；对不上即盲区，回退 C3。
4. 差集若含 Case3-unknown 风险向，回退预案见第 3 节（ctx kill-switch 兜底）。

### 攻击点 2 —— 依赖闭合完备性

**VERDICT：闭合干净、无环；方案证据里的 `t?` 是 AST 扫描假阳性（实证销案）。**

1. **`t` 依赖 = 假阳性**。`_fix_single_ref_arg` 内 `_norm = lambda t: re.sub(...)`（stage5:783 附近）——
   `t` 是 **lambda 形参**，非外依。我用 ast 逐 Name 节点 + 归集赋值/形参/for 目标重扫：
   `_fix_single_ref_arg` 外依 = `{_NON_POINTER_LOCAL_KINDS, re, store}`（仅此三）。
   同类假阳性亦见于 `_resolve_offset`（`any(t in mt for t in …)` 推导式变量 t）——
   **归集器必须含 lambda 形参 + comprehension 目标**，守卫脚本按此写（见攻击点 4）。
2. **`store` 反向依赖不成环**：`ref_params → data(store) → annotation_view`，实测
   `pipeline/gen/annotation_view.py` 顶层只 `import json, os`（annotation_view.py:23-24），
   `data.py` 顶层 `from annotation_view import …`（data.py:3）+ 标准库；`pipeline.config` 仅
   `DataStore.__init__` 内运行时取（data.py:52）。**无 `data → stages/ref_params` 边 ⇒ 无环**。
   守卫（T7）断言 `data.py`/`annotation_view.py`/`tables.py` 不 import 任何 `pipeline.gen.stages`/`ref_params`。
3. **`store` 是懒加载单例**：`store.global_types` 在未 `load()` 时为 `{}`（data.py:63），
   `_fix_single_ref_arg` F81b 分支自然退化 ⇒ 纯单测零基建可用（既有 test_ref_param_table_b.py 已如此跑通）。
4. **`_split_top_commas` / `_DECL_KEYWORDS` / `_NON_POINTER_LOCAL_KINDS` 归属与共用面**：
   - `_split_top_commas`（stage5:836-850）：**全仓唯一调用点 = `_build_var_types` L885** ⇒ 随 `_build_var_types` 下沉，无扩面。
   - `_DECL_KEYWORDS`（stage5:833）：唯一消费者 = `_build_var_types` L866/874/879 ⇒ 同上。
   - `_NON_POINTER_LOCAL_KINDS`（stage5:628）：唯一消费者 = `_fix_single_ref_arg` L767 ⇒ 随 `_fix_single_ref_arg` 下沉。
   - ⚠️ **但 `_build_var_types` 的消费面比「ref 参数」大**：stage5:1375、1431、163 三处
     （C2440 修复器族 / `_fix_line_plain_var_assign`）也在用。⇒ 下沉后 stage5 仍须 `from pipeline.gen.ref_params
     import _build_var_types`（stage→shared，合法），且**模块 charter 要写清**：ref_params.py =
     「引用参适配机制 + 其声明证据机器（`_build_var_types` 族，C2440 修复器共用）」，
     否则后人见「C2440 修复器 import ref_params」会误判跨界。命名不变（已获原则认可），docstring 补一句即可。
5. `pipeline/gen/tables.py` 保持零 import 纯数据（现无任何 import，42 行）⇒ 不给它加机制依赖（见攻击点 3）。

### 攻击点 3 —— 模块选址：ref_params.py vs 并入 tables.py

**VERDICT：独立 `pipeline/gen/ref_params.py`（不并入 tables.py）。数据/逻辑分离胜出；
`_GB_REF_PARAM_TYPES` 按方案留 ref_params.py，tables.py 头部加姊妹表交叉引用。imports 用绝对形
`from pipeline.gen.ref_params import …`（与 [R99] tables 先例一致）；包初始化零风险（两个 `__init__.py`
均为空注释，实测）。**

裁定理由：

1. **tables.py 的零依赖纯度是承重的，不是审美**。scoped_targets.py 的存在即实证（该文件头部注释，
   2026-10-10 实测）：IDA 环境 `from data import store` **解析失败**（sys.path 无 pipeline/gen）
   ⇒ 才被迫造了无依赖副本。机制若并入 tables.py，tables.py 就带上 `re`/`store` 依赖，
   失去「任意 sys.path 语境可 import」的性质，把 scoped_targets 教训反向引进表层。
2. **「表+机制同族共居」vs「数据/逻辑分离」**：本案机制（regex 扫描 + 证据门）与表（dict 字面量）
   生命周期不同——表按登记纪律改（误登代价>漏登代价，F1b/F3 删键史为证），机制按行为改（每次要 A/B）。
   分离后表改动天然零行为 diff（dict 级），机制改动走行为闸，**两条变更轴不互相污染归因**。
   同族共居唯一好处（改格式串顺手改表）在本案不成立：`*(%s *)&%s` 的 `%s` 只吃类型名字符串，无格式耦合。
3. `_GB_REF_PARAM_TYPES` 与 `_GB_REF_PARAM_FUNCS` 分居两文件是小瑕疵，用两行注释互指即可
   （tables.py 头注释加「姊妹表 `_GB_REF_PARAM_TYPES` 在 ref_params.py——登记纪律同本文档」；
   ref_params.py 表块引用 [R99]）。**F1b/SetAxisAngle、F3/SetBlend 删键史注释块必须随表迁移**
   （stage5:599-625 → ref_params.py 表块紧后），这是「误登代价>漏登代价」的登记证据，不能丢。
4. **imports 形**：绝对形 `from pipeline.gen.tables import _GB_REF_PARAM_FUNCS`（既有，stage3:2163 / stage5:564 同款）
   + `from data import store`（与 stage5:22 同款）。**禁止相对形**（`.ref_params`）：既有代码全用平铺/绝对混形
   （test 侧 `sys.path.insert(0, _GEN)` 平铺导入），相对形会在测试平铺导入语境下炸。
   **⚠️ 双注册陷阱（身份断言的隐雷）**：`pipeline/gen/ref_params.py` 被 `pipeline.gen.ref_params`（stage 侧）
   与 `ref_params`（测试平铺侧）两种名字 import 时 Python 会**执行两遍**生成两个函数对象 ⇒ `is` 断言假红。
   守卫测试只准用 `pipeline.gen.ref_params` 形取源模块（与 stage 内 import 形一致），断言只在
   「两个消费方绑定」与「消费方 ↔ pipeline.gen.ref_params 绑定」之间做（实测验证法见 T1）。
5. **包初始化顺序**：`pipeline/__init__.py` 不存在（namespace package），`pipeline/gen/__init__.py` 与
   `stages/__init__.py` 均为单行注释（实测）⇒ 无 import 副作用、无初始化顺序风险。
   data.py 的 `from annotation_view import …` 要求 `pipeline/gen/` 在 sys.path——生产（codegen 启动）与
   测试（test 文件头部 insert）两侧现均已如此 ⇒ ref_params 同形 import 不新增要求。

### 攻击点 4 —— 守卫测试设计

**VERDICT：AST 扫描（非 grep）+ 「精确允许边集合」表述；transform.py 豁免用显式 allowlist 字典表达并带注释。
另补一条方案没写的「全景同名双定义」守卫——它把第 7 点的遗漏检查变成自维护的可执行项。**

1. **AST vs grep**：grep 会漏函数内 import（本案 2 处违例恰在函数内：emit_headers:2893/3750），
   且会被注释/字符串误伤（stage3:1813 注释里就有 `rewrite_thiscall_fnptr_param` 字样）。
   ⇒ 用 `ast.parse` + `ast.walk` 全树收集 `ast.Import`/`ast.ImportFrom`（含嵌套），
   归一化三种拼写（`pipeline.gen.stages.X` / `stages.X` / 裸 `X`）+ 相对导入（`level>0` 按包解析）到模块基名。
   **归集器补 lambda 形参与 comprehension 目标**（攻击点 2 的 `t` 假阳性教训）。
2. **「零 stage→stage import」的精确表述**（两规则，现状全绿可落地）：
   - **R-A（横向）**：`stage{1..5}_*.py` 对 `stages/` 任何模块的 import 数 **= 0**（现状 0，实测）。
   - **R-B（反向）**：除 `transform.py`（编排器）外，任何模块不得 import `stage{1..5}_*.py`。
     现状违例恰 2 处（emit_headers:2893/3750 → stage4_substitution），**进 allowlist 并注释「待第 5 点清扫」**；
     清扫落地时从 allowlist 删除 ⇒ 空表即「零违例」棘轮。
   - **允许边冻结集**（R-B 的完整豁免面，超出即红）：`emit_cpp→{transform, collect, emit_headers}`、
     `emit_headers→{scope_tree, collect}`（实测现存 7 条跨模块边里 5 条属此类，是既定分层——
     emit 层→编排/收集/工具层向下依赖，合法；全部冻结进 allowlist，**新增任何跨模块边必须显式登记**）。
     这样误报面 = 零（每条现存边都点名豁免），漏报面 = 零（新边默认红）。
3. **transform.py 豁免表达**：`ALLOWED = {('emit_cpp.py','transform.py'), …, ('transform.py','stage1_structural.py'), …}`——
   transform 对 5 个 stage 的 import 逐条登记（5 条）而非「文件级白名单」，防止后人往 transform 里塞
   非编排依赖时被文件级豁免掩盖。
4. **T6 全景同名双定义守卫**（方案第 7 点的可执行化）：AST 收集 `pipeline/gen/**` 全部**顶层** def 名，
   同名 >1 即红，allowlist 现为 `{run（5 stage 入口契约）, main（codegen.py:149 / emit_headers.py:3198 两个入口）}`。
   合并后 `_fix_ref_params`/`_strip_outer_parens` 自动出表（单源）；`_call_return_type` 改名后自动出表；
   `resolve_targets`/`scoped_decomp_dir`（collect↔scoped_targets 双副本）与 `_resolve_ordinal_type`（emit_headers 自影）
   **在本批前/后各自进 allowlist 并挂各自任务号**（见缺陷清单 D3/D4）——每清一个删一行 allowlist。
   这就是 gotcha_dual_copy_table_divergence 那类「修一漏一」的机器闸。

### 攻击点 5 —— 第 4/5 点处置顺序

**VERDICT：第 4 点（rename）并入本批（纯更名、零行为）；第 5 点（emit_headers 下沉）确按「独立小任务」押后。
两函数外依实测闭合干净，无新纠缠。**

1. **`_call_return_type` 同名异义实锤（禁盲合正确，merge 不可行，rename 唯一解）**：
   | | stage4:1853 | stage5:921 |
   |---|---|---|
   | 入参 | tree-sitter **node** | **名字字符串** |
   | 取名 | `child_by_field_name('function')` → field/identifier | 直接用 |
   | 查源 | `_method_return_index()`（annotation_view 侧、短名→返回型、**多声明不一致不收录**，1819-1844） | `store.method_sigs`/`free_func_sigs`（**decomp 侧签名**）regex 抠返回型 |
   | 未命中 | `''` | `None` |
   两个查源**故意不同源**（注解侧 vs decomp 侧；stage5:1590 注释明言两者会不一致）。
   ⇒ 修法：stage4 `_call_return_type` → `_node_call_return_type`（调用点 :1941 同步），
   stage5 → `_sig_call_return_type`（调用点 :1034、:1042 同步）。**不 merge、不统一返回 sentinel**。
   T6 守卫自动盯复发。
2. **emit_headers→stage4 下沉依赖面（实测 AST 闭包）**：
   - `rewrite_thiscall_fnptr_param`（1299-1310）→ `rewrite_thiscall_fnptr_param_ex`（1313-1340）→
     `_FPTR_PARAM_RE`（1287-1288）/`_THIS_NAME_RE`（1290）/`_ANON_PTR_ARG_RE`（1296）。外依 = **仅 `re`**。
   - `_try_struct_member_resolution`（222-247）→ `_resolve_offset`（149-219）→
     `_anon_aggregate`（142-146）+ `_ELEM_SIZES`（137-139，纯 dict）+ `store`。外依 = **`re` + `store`**。
   - 两单元全闭包 = `{re, store, 其自身}`，**零 stage 内部符号** ⇒ 无新纠缠。
   - 反向消费面：stage4 内部调用 `_resolve_offset`×5（203/216/244/267/285）、`_try_struct_member_resolution`（1141）、
     `rewrite_thiscall_fnptr_param_ex`（1400）⇒ 下沉后 stage4 反向 import 共享层（合法），**不产生共享→stage 边**。
   - 落点：新建 `pipeline/gen/sig_resolve.py`（与 ref_params 同层；charter「emit/stage 共享的签名文本/成员解析机制」）。
     下沉单元 = 上列 8 个符号；`_try_struct_member_resolution` 随迁改公有名 `try_struct_member_resolution`
     （跨模块私有名是坑），3 个调用点同步。
   - **为什么押后**：单元虽干净，但动 emit_headers（4511 行）+ stage4 双侧，与 ref-param 机制零耦合——
     混批会让 C3 的行为差集归因变脏。顺序：本批（ref_params）→ rename 批内顺手 → sig_resolve 独立批 → 自影微批。

### 攻击点 6 —— 回退预案（合并后 S2/L1 回退的二分定位）

**VERDICT：按「每个提交单变量」切分，天然支持 `git bisect` + 读数二分；stage3 影响面与 stage5 影响面物理隔离在 C2/C3 两个提交。**

1. 提交切分（详见定稿）：**C1 纯新增**（ref_params.py + tables.py 表 + 单测，零消费方改动 ⇒ loop 读数必与基线逐字同）→
   **C2 stage5 重接线**（删本地实现、import 共享；超集=stage5 现行为+幂等折叠 ⇒ loop 读数**必逐字同**；不同=stage5 面 bug，
   在 C2 内修/回退，不进 C3）→ **C3 stage3 重接线**（唯一行为变更提交）→ **C4 `_strip_outer_parens` 下沉**（行为中性）→
   **C5 rename×2**（行为中性）。
2. **二分法**：loop 读数在 C2 变 ⇒ stage5 面（查共享 vs 旧 stage5 的 case 级单测差 + 折叠幂等断言）；
   在 C3 变 ⇒ stage3 激活面（用 C1 态普查的 (file, case-kind) 多重集逐条对账 `pal3/src` diff；对不上的 hunk = 盲区）。
   C4/C5 变 ⇒ 实现抄写错（本应零 diff，直接 `git diff` 定位）。
3. **回退动作**：`git revert` 单个提交即可（C3 可独立回退而保留 C1/C2 的单源收益）；
   若 C3 退化且「先修后回」判定为修复成本高，C3 内的兜底 = 共享函数加 `case3=False` 关键字形 kill-switch、
   stage3 调用点显式关（Case2/2b 保留——它们是 C2100 修复向）；全批回退 = revert C1..C5 逆序。
4. ⚠️ 读数纪律（CLAUDED 强制）：验证前必须 `apply→export`（防 2026-10-19 陈旧验证教训）；
   `compile_baseline.json` 现 124/214 与实况 133/214 矛盾（status 预检实测 2026-10-28）⇒
   `codegen all` 内置 compile_regression **恒红是既存噪声**，判读以 `loop --expect-*` 当场读数为准，不以该文件判退化。

### 攻击点 7 —— 遗漏检查

**VERDICT：`__init__`/`_repl`/`_sub` 良性判定**确认**；`_resolve_ordinal_type` 自影不并入本批（独立微批）；
另发现 2 项方案未列的存量问题（1 项活红测试 + 1 组双副本）入缺陷清单。**

1. **`__init__`×3（data.py:47 / scope_tree.py:59 / stage3_cleanup.py:94）** = 三个不同类的构造器，类作用域隔离 ⇒ **良性确认**。
   **`_repl`×2（emit_cpp.py:64/566）与 `_sub`×3（ast_transform.py:1034/1309/1476）** = 全部 `col_offset=4` 嵌套函数（AST 实测），
   各自闭包作用域 ⇒ **良性确认**。与 T6 守卫口径一致（只扫顶层 def，嵌套/方法不计）。
2. **`_resolve_ordinal_type` 自影（emit_headers:375-379 / 389-392）**：两函数体**逐字同**（仅 docstring 有无之差），
   后定义遮蔽前定义 ⇒ 前者死代码。**顺手修=删 :375-379，行为零 diff**。
   但**不并入本批**：本批 C3 是唯一行为变更提交，混入任何「看起来零 diff」的改动都会污染 A/B 归因。
   定为独立微批（C7），自带一次 loop 零 diff 验证，T6 allowlist 同步删行。
3. **全景同名双定义清单复核**（T6 守卫的初始 allowlist 依据）：`run`×5 = stage 入口契约（良性，冻结登记）；
   `main`×2 = 两个可执行入口（良性）；`resolve_targets`/`scoped_decomp_dir`（collect.py:332/357 vs
   scoped_targets.py:13/36）= **非良性双副本**（文档化但可漂移）→ D3；`_call_return_type`/`_fix_ref_params`/
   `_strip_outer_parens` = 本批清。
4. **方案未列的新发现**：
   - **D1 活红测试**：`test_ref_param_table_b.py::test_getaabox_cross_class_form_split` **现测现红**
     （2026-10-28 实跑：19 passed / 1 failed）——测试（B 修补条 2026-10-14）要求 `GetAABBox` 裸键出表 +
     `gbOBBox::GetAABBox` 限定键入表，tables.py **未改**（仍有 `GetAABBox': {0}`）。
     这是表纪律的活信号（测试先行、表未落）。**合并批严禁顺手改表**（改表=行为变更，污染 C2「读数必同」断言）；
     单列表纪律任务（C8）走自己的 A/B。合并批的测试基线记「19 passed / 1 failed（存量红）」。
   - **D2 `fix_ref_arg_calls`（ast_transform.py:1355）**：实参位 `&` 补全机制（指针参补 `&`、引用参不动），
     已单源、已 13 项单测（test_fix_ref_arg_calls.py）、**无生产调用方**（全仓 grep 仅测试引用）。
     与 `_fix_ref_params`（引用参剥 `&`）方向相反、同域（实参形适配）⇒ 今日无 TOS 违例，但**接线时**须与
     ref_params 的 case 语义做一次协调（挂账，不并入本批）。
5. **`_ref_positions` 死闭包**（stage5:653-656，def 后全仓零调用）：下沉时**直接丢弃**（行为零 diff），不带进共享模块。

---

## 3. 实施就绪定稿

### 3.1 文件级操作清单（每提交单变量；锚点为当前 HEAD 实测行号）

**C1 —— 纯新增（零消费方改动；loop 读数必须与基线逐字相同）**
- **新建 `pipeline/gen/ref_params.py`**，charter docstring 写明：
  「引用参适配机制单一 TOS + 声明证据机器（`_build_var_types` 族，stage5 C2440 修复器共用）。
  尾部 `_tail_000` 折叠为 stage3 vtable 形态 3 输入侧的历史尾步，对 stage5 幂等（正则 `(\w+)->_tail_000\b(?!\[)`，
  输出不含可再匹配形；`(?!\[)` 跳过形二次同样跳过）——保留在此以免调用点漏加。」
  迁入（**源 = stage5 超集版逐字 + stage3 尾步**）：
  | 符号 | 源锚点 | 迁入处理 |
  |---|---|---|
  | `_GB_REF_PARAM_FUNCS` | tables.py:12（[R99] 单源） | **不迁**，ref_params 里 `from pipeline.gen.tables import _GB_REF_PARAM_FUNCS` |
  | `_GB_REF_PARAM_TYPES` | stage5:571-594 | 迁 dict + **F1b(599-610)/F3(612-625) 删键史注释块随迁** |
  | `_NON_POINTER_LOCAL_KINDS` | stage5:628 | 原样迁 |
  | `_fix_ref_params(code, ctx=None)` | stage5:631-709 | 以 stage5 版为基；**丢 `_ref_positions` 死闭包（653-656）**；尾部追加 stage3 尾步（stage3:2248-2249 逐字，含 `# _tail_000 兼容转换` 注释） |
  | `_fix_single_ref_arg(arg, vt=None, ref_type=None)` | stage5:712-791 | 原样迁 |
  | `_DECL_KEYWORDS` | stage5:833 | 原样迁 |
  | `_split_top_commas` | stage5:836-850 | 原样迁 |
  | `_build_var_types(code, ctx)` | stage5:853-903 | 原样迁 |
  顶部 imports：`import re` + `from data import store` + `from pipeline.gen.tables import _GB_REF_PARAM_FUNCS`（绝对形，禁相对形）。
- **改 `pipeline/gen/tables.py`**：头部注释加一行「姊妹表 `_GB_REF_PARAM_TYPES` 在 pipeline/gen/ref_params.py——登记纪律同本文档（误登代价>漏登代价）」。dict 本身不动。
- **新建测试**：`pipeline/gen/test_ref_params_tos.py`（T1-T4，见 3.2）+ `tests/test_tos_stage_isolation.py`（T6-T8）。
- 此提交**不改 stage3/stage5 任何行** ⇒ 生效读数不变是硬断言。

**C2 —— stage5 重接线（行为必逐字同；读数与 C1 同）**
- **删 stage5_fixup.py 本地实现**：`_GB_REF_PARAM_TYPES`（571-594）、F1b/F3 注释块（566-625 内随表走）、
  `_NON_POINTER_LOCAL_KINDS`（627-628）、`_fix_ref_params`（631-709）、`_fix_single_ref_arg`（712-791）、
  `_DECL_KEYWORDS`（833）、`_split_top_commas`（836-850）、`_build_var_types`（853-903）。
  **改 stage5_fixup.py 模块级 import**（原 :564 `from pipeline.gen.tables import _GB_REF_PARAM_FUNCS` 行处扩）：
  ```python
  from pipeline.gen.ref_params import (          # [TOS ref 2026-10-28] 机制单源
      _fix_ref_params, _fix_single_ref_arg, _build_var_types,
      _GB_REF_PARAM_TYPES,                       # 测试兼容再导出（test_ref_param_table_b:30）
  )
  ```
  （`_GB_REF_PARAM_FUNCS` 保留原 tables import 或一并从 ref_params 再导出——二选一，注明即可；
  `_split_top_commas`/`_DECL_KEYWORDS`/`_NON_POINTER_LOCAL_KINDS` 无外部消费者，不需再导出。）
- 调用点 :1605 `code = _fix_ref_params(code, ctx)` **不动**（签名兼容）。
- **不改 `_strip_outer_parens`（934-951）/`_call_return_type`（921-931）**（C4/C5 处理）。
- 既有测试 `test_ref_param_table_b.py`（`from stage5_fixup import …`）**零改动全绿**（除 D1 存量红）。

**C3 —— stage3 重接线（本批唯一行为变更提交）**
- **删 stage3_cleanup.py 本地实现**：注释块+import（2157-2164，含 :2163 tables import）+ `_fix_ref_params`（2166-2250）。
- **改 stage3_cleanup.py**：模块级加 `from pipeline.gen.ref_params import _fix_ref_params`。
- **改调用点 :2061**：`code = _fix_ref_params(code)` → `code = _fix_ref_params(code, ctx)`（ctx=TransformContext，.sig 可用）。
- 既有 `tests/test_vtable_call_transform.py::test_form3_existing_tail_000_fold_is_preserved`（:289-291 直调
  `s3._fix_ref_params`）**零改动保持绿**（折叠在共享函数内）。

**C4 —— `_strip_outer_parens` 下沉（行为中性）**
- 语义裁定：两版**字符串域逐字等价**（全括号形穷举核对：`((a)+(b))`/`()`/`(`/`)`/`(a)(b)`/`((a)`/`(a)))` 等全同）；
  **仅 None/假值域不同**（stage3:873 用 `str(text or '')` 容忍 None；stage5:934 `e.strip()` 直接炸）。
  **采 stage3 容忍版**（更安全；两版调用点实测都只传字符串，故零行为 diff）。
- 删 stage3:873-889 与 stage5:934-951，迁入 ref_params.py；两 stage `from pipeline.gen.ref_params import _strip_outer_parens`。
- 调用点不动（stage3:916/923/926/933/999/1012、stage5:1009）。

**C5 —— `_call_return_type` 双改名（行为中性）**
- stage4_substitution.py:1853 `_call_return_type` → `_node_call_return_type`（调用点 :1941）。
- stage5_fixup.py:921 `_call_return_type` → `_sig_call_return_type`（调用点 :1034、:1042）。
- T6 守卫的同名 allowlist 无此项（改名后自动出表）。

**C6 ——（独立任务，非本批）emit_headers→stage4 下沉**
- 新建 `pipeline/gen/sig_resolve.py`：迁 `rewrite_thiscall_fnptr_param`（stage4:1299-1310）、
  `rewrite_thiscall_fnptr_param_ex`（1313-1340）、`_FPTR_PARAM_RE`（1287-1288）、`_THIS_NAME_RE`（1290）、
  `_ANON_PTR_ARG_RE`（1296）、`_resolve_offset`（149-219）、`_anon_aggregate`（142-146）、`_ELEM_SIZES`（137-139）、
  `try_struct_member_resolution`（原 `_try_struct_member_resolution` 222-247，随迁改公有名）。
- stage4 反向 import 自用符号（203/216/244/267/285/1141/1400 调用点不动或改一次名）；
  emit_headers:2893/3750 的两处函数内 `from stages.stage4_substitution import …` 删除，改模块级
  `from pipeline.gen.sig_resolve import …`。
- T6/T7 allowlist 同步清空对应行。独立 A/B（loop 零 diff 期望）。

**C7 ——（独立微批）emit_headers `_resolve_ordinal_type` 自影**
- 删 emit_headers.py:375-379（前定义死代码；389-392 保留）。调用点 :1665 不动。T6 allowlist 删行。

**C8 ——（独立表纪律任务）GetAABBox 表修正（D1）**
- tables.py：删 `'GetAABBox': {0}`、加 `'gbOBBox::GetAABBox': {0}`（按 test_ref_param_table_b:40-55 的 B 修补条语义）。
- 自带 A/B（行为变更：裸 `GetAABBox` 调用形不再剥 `&`）+ `test_getaabox_cross_class_form_split` 转绿。

### 3.2 测试清单（名字 + 断言形）

`pipeline/gen/test_ref_params_tos.py`（平铺导入消费者、绝对形导入源模块——防双注册假红）：
- **T1 `test_ref_mechanism_single_tos_identity`**：
  `from pipeline.gen.ref_params import _fix_ref_params as S`；`import stage3_cleanup as s3, stage5_fixup as s5`；
  断言 `s3._fix_ref_params is s5._fix_ref_params is S`；同形断言 `_fix_single_ref_arg`、`_build_var_types`、
  `_strip_outer_parens`（C4 后）、`_GB_REF_PARAM_TYPES`（`s5._GB_REF_PARAM_TYPES is pipeline.gen.ref_params._GB_REF_PARAM_TYPES`）。
- **T2 `test_fix_single_ref_arg_cases`**：直接单测共享函数 5 分支——
  `'&v'→'v'`（Case1）；`'(T*)x'→'*(T*)x'`（Case2）；`'*stru_12AB'`+ref_type→`'*(struct gbVec3D *)&stru_12AB'`（Case2b）；
  裸 `'v15'` + vt{value}→原样、vt{array}→`'v15[0]'`、vt{ptr}→`'*v15'`、vt{}（无 ctx）→`'*v15'`（**锁定无门退化行为**，防静默改判）。
- **T3 `test_build_var_types_kinds`**：fnptr/ptr/value(含初始化形)/array/参数(sig 形含 `this` 跳过)/同名多 kind→ambiguous 保守各一断言。
- **T4 `test_fix_ref_params_arity_and_qualified_keys`**：`gbMatrixStack::Rotate` 双载（2 元 ref@1 / 1 元 ref@0）选位、
  限定键命中/裸键出表不动（吸收现 test_ref_param_table_b 的有效面亦可）。
- **T5 `test_tail000_fold_preserved_and_idempotent`**：`'x = obj->_tail_000;'→'x = *(void**)(obj);'`；
  幂等 `f(f(s)) == f(s)`；`'obj->_tail_000[3]'` 原样（`(?!\[)` 守护）。

`tests/test_tos_stage_isolation.py`（AST 守卫，归集器含 lambda 形参/comprehension 目标）：
- **T6 `test_no_duplicate_top_level_defs`**：`pipeline/gen/**` 顶层同名 def >1 即红；
  ALLOWED 初始 = `{run, main}` + `(collect.py|scoped_targets.py, resolve_targets|scoped_decomp_dir)`（挂 D3）+
  `(emit_headers.py, _resolve_ordinal_type)`（挂 C7 前）；每行注释任务号。
- **T7 `test_zero_stage_to_stage_imports`**：R-A（stage1-5 对 stages/ import 数=0）+ R-B（除 transform.py 外无人 import stage1-5；
  现违例 2 处进 ALLOWED 注「待 C6」）+ 允许边冻结集 5 条（emit_cpp→transform/collect/emit_headers、emit_headers→scope_tree/collect）；
  新边默认红。
- **T8 `test_shared_layer_no_upward_imports`**：`data.py`/`tables.py`/`annotation_view.py`/`ref_params.py` 不得 import
  `pipeline.gen.stages` 任何模块（环守卫，封死攻击点 2 的环回归面）。

`pipeline/gen/test_ref_params_ab_corpus.py`（`@pytest.mark.slow`，默认排除）：C1↔C3 间跑行为差集普查（攻击点 1 修法第 3 步）。

### 3.3 验证命令序列（每提交重复 1-6；标 ✱ 的是硬断言）

```bash
python3 pipeline/cli.py status                    # 0) 预检（秒级只读）：刷新基线数字与恒红门禁清单
                                                  #    2026-10-28 实测：S2 133/214 · 错误 1137 · L1 147
                                                  #    ⚠️ compile_baseline 124/214 陈旧恒红=既存噪声，不作判据
python3 -m pytest pipeline/gen/test_ref_param_table_b.py \
        pipeline/gen/test_cast_reg_assignments.py \
        pipeline/gen/test_ref_params_tos.py \
        tests/test_tos_stage_isolation.py \
        tests/test_vtable_call_transform.py -q   # 1) 单测面（基线 19+1 存量红见 D1；新测试全绿）
python3 pipeline/cli.py loop --expect-s2 133/214 --expect-errors 1137 --expect-l1 147   # 2)✱ 全链（含 apply→export→codegen→probe→match）
python3 tools/compile_regression.py               # 3) 即时快照闸（已知恒红=陈旧基线噪声，人工判读）
python3 tools/error_classifier.py --summary       # 4) 错误族分布（C3 后逐族对账 case-kind 差集）
python3 pipeline/cli.py match                     # 5) L1 当场读 [metric] 三限定账（L1 不回退✱）
python3 tools/annotation_diff.py                  # 6) 无 annotation 变更时应为空（本批不动 annotation）
```
硬断言逐提交：C1/C2/C4/C5 = 读数与前一提交**逐字同**（133/214 · 1137 · 147）；
C3 = 读数变化须逐条落在 C1 态普查的 case-kind 差集内（对不上 ⇒ 盲区 ⇒ 走回退预案）。
**引用 L1 数字带三限定**（截断/等长/重定位 4B don't-care，gotcha_l1_reloc_dontcare_three_qualifications.md）。

### 3.4 回退预案

见攻击点 6：提交切分 C1..C5 单变量 ⇒ `git bisect` + loop 读数二分；
C2 变 ⇒ stage5 面查共享实现与旧 stage5 的 case 级差（T2/T5 先行兜底）；
C3 变 ⇒ stage3 激活面按普查多集对账，修复成本高则 C3 内 `case3=False` kill-switch（Case2/2b 保留）或 revert C3（保留 C1/C2 单源收益）；
C4/C5 变 ⇒ 抄写错，`git diff` 直查。验证纪律：任何实效读数前先 `apply→export`；读数当场读，不以陈旧基线文件判退化。

---

## 4. 缺陷/遗漏清单

| # | 级别 | 内容 | 处置 |
|---|---|---|---|
| D0 | **BLOCKER** | 双实现 diff 漏 `_tail_000` 反向差异（stage3:2248-2249 有、stage5 无）；既有测试 tests/test_vtable_call_transform.py:289-291 锁死 | 定稿 C1 已处置（尾步留共享函数内 + T5 幂等锁） |
| D0' | **BLOCKER** | 「删实现+导入」照字面执行且 stage3 调用点（:2061）不传 ctx ⇒ Case3 无门打开 C2100 复燃面 | 定稿 C3 已处置（必传 ctx + T2 锁无门退化行为 + kill-switch 回退） |
| D1 | 高 | **活红测试**：test_ref_param_table_b::test_getaabox_cross_class_form_split 现测现红（GetAABBox 表未按 2026-10-14 B 修补条落表）——表纪律活信号 | C8 独立任务；合并批严禁顺手改表；测试基线记「19+1 存量红」 |
| D2 | 中 | `fix_ref_arg_calls`（ast_transform.py:1355）同域反向机制（补 `&`），已单源+13 测、**无生产调用方** | 挂账：接线时与 ref_params case 语义协调；不并入本批 |
| D3 | 中 | `resolve_targets`/`scoped_decomp_dir` collect↔scoped_targets 双副本（docstring 微异、import 风格异；scoped_targets 为 IDA 环境依赖隔离的**文档化**副本）——同 gotcha_dual_copy 类漂移面 | T6 allowlist 登记（挂任务号）；后续批抽零依赖共享核让两侧再导出 |
| D4 | 低 | emit_headers:375/389 `_resolve_ordinal_type` 文件内自影（前定义死代码，两体逐字同） | C7 独立微批删 :375-379；不混入本批 A/B |
| D5 | 低 | stage5:653 `_ref_positions` 死闭包（def 后零调用） | C1 下沉时丢弃（零行为 diff） |
| D6 | 低 | `_build_var_types` 消费面超出 ref 参数域（stage5:163/1375/1431 C2440 修复器共用）⇒ ref_params.py charter 需写明，防「C2440 修复器 import ref_params」被误判跨界 | C1 docstring 已列 |
| D7 | 信息 | 双注册陷阱：源模块被平铺名+包名双 import 会执行两遍致 `is` 断言假红 | T1 已按「源只准 pipeline.gen.ref_params 形」设计 |

## 5. 未复验清单（结论按现状采信，实施前应复验）

1. **git 史锚点**：6801d614e（删 `_GB_REF_PARAM_FUNCS['SetBlend']`）提交号未开库核对（stage5:612-625 F3 注释块已实证其事，提交号待核）。
2. **C1 态行为差集普查的量**（Case2/2b/3 在 stage3 语料上的实际触发条数）——需按攻击点 1 修法第 3 步实跑一次普查才有数；本报告只给方法与判读规则。
3. **`_tail_000` 折叠对 stage5 幂等**——已按正则语义论证（输出无可再匹配形、`(?!\[)` 双侧一致），但「stage5 输入零 `->_tail_000` 残形」是推论非实测；T5 幂等单测 + C2 零 diff 读数双兜底。
4. **loop 基线数字 133/214 · 1137 · 147**：取自 2026-10-28 `cli.py status` 实测；实施日须重读刷新（仓库纪律「基线数字须随实况刷新」）。
5. **`_strip_outer_parens` 字符串域等价**：穷举核对了典型括号形，未做全空间穷举；T2 附属性测试（随机括号串双函数对拍）可补。
6. **`test_ref_param_table_b` 19 passed/1 failed** 为 2026-10-28 单次实跑读数；D1 存量红的形成时点未考古（git blame 未查）。
7. **`from data import store` 在生产入口的 sys.path 保障**：实测测试侧已保障（test 头 insert）、codegen 生产侧未逐步跟踪（既有 stage 皆同形 import，风险=0 新增，但未单证）。
