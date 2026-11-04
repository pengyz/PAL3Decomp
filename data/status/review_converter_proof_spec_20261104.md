#《转换器完备性与正确性证明》设计 spec 独立对抗性复核（2026-11-04）

- 复核对象：`docs/specs/2026-11-04-converter-proof-design.md`（91 行，状态：待对抗复核）。
- 铁律执行：**不准确=不判定**；凡裁定必带 `文件路径:行号`。测量性数字注明口径。本复核只写本文件。
- 实测口径：全量扫描 `data/annotations/`（`structs/*.json` 942 件 · `functions.json` 438 条 · `globals.json` 1381 条）的字段键分布；`ghidra_track/` 转换链逐行；`thirdparty/ghidra-mcp` 源码注册面（**未起活体 daemon**，见 §5-2）。
- 攻击面：任务书六必攻（证明模型有效性 / daemon 回读面可行性 / 矩阵枚举源 / 实施序与环境成本 / 边界与遗漏 / 替代方案与证明器自证）。

## 1. 总裁：**部分可行——三柱骨架成立；须补「期望投影独立性」与「证明器自证」两个缺件、按 §4 修订后方可实施**

| 层 | 裁定 |
|---|---|
| 证明对象边界（忠实搬运 annotation 语义、不含二进制真值） | **成立**（spec:9-11 与用户裁定一致；A/B 真值轴切分正确，§2.6） |
| 三柱证明模型（矩阵 + 回读 diff + fixture）架构 | **成立**——方向正确、fail-loud 化（spec:27）合理 |
| 「回读 diff=∅」的证明力 | **部分成立**：能证「投影面内传递保真」；**不能单独证完备**（域外静默丢对 diff 不可见）也**不能证合并/投影语义正确**（期望侧若复用转换器解析=循环论证，§3.1） |
| fixture 的证明力 | **部分成立**：布局维有独立 oracle（机测 layout，`ghidra_track/fixture/cases/case-01-struct-union-overload/expected/layout.json:5`）；名/签/union 变体维若期望由 annotation 派生则循环（§3.2）；且 case-01 实况不含 spec:40 声称的「union 嵌套/占位名形」（§2.4） |
| daemon 回读面可行性 | **基本成立**：结构字段名/偏移/型可回读（§2.2）；但 `indirect:<效果验法>` 对 adjudication 可操作、对 evidence/name_source 是空话（§2.3）；「B 侧无存储」是转换器现状而非工具面上限（set_comment 可用） |
| 矩阵枚举源 | **需修订**：仓内无正式 annotation schema 文件，「annotation schema 字段枚举」（spec:20,46）无出处；实测字段面 45+14+33+17+15 种键，须改成「语料机械枚举 + 人工分类账」（§2.5、§4-R5） |
| 实施序 | **基本成立**，1 处错位（RED 挂错构件）、门禁触发面漏 1 文件（§2.5）；已知缺口清单漏 4 项实测缺口（§2.6） |
| 门禁接线与测试环境成本 | **未证可行**：净室 Ghidra 项目 + daemon 互斥持库 + 固定端口（`ghidra_track/README.md:53-55`、`ghidra_track/import_via_daemon.py:9`）；CI 须自备 Ghidra 12.1.2（`ghidra_track/README.md:37`）；仓内零时间测量（§5-4） |
| 证明器自身有效性 | **缺件**：spec 全文无「注入已知错误必须被抓」的 mutation 校验（§3.6）——verify 器自身有 bug 时 PROVEN=假绿，无任何防护 |

**总裁一句话**：三柱模型不用推倒，但现状的「回读 diff=∅」若照 spec 实施，最大风险是**假绿**（期望投影与转换器共享同一套解析/合并语义 ⇒ 共享 bug 双侧一致 ⇒ diff=∅）。必须先钉「期望投影独立实现 + 合并语义入契约 + mutation 自证」，再谈 PROVEN。

## 2. 逐条证据核对

### 2.1 spec 文本主张 vs 实况

| # | spec 主张 | 裁定 | 证据 |
|---|---|---|---|
| 1 | 「完备性域=annotation 全语义域——含 known_members/methods/vtables/bases/inline-union dict 形/adjudication/owner/evidence/name_source/global/type 字段族」（spec:11） | **成立**（范围裁定引述准确；覆盖面账见 §2.5 实测字段面） | 用户裁定（任务书背景）；字段面实测见 §2.5 |
| 2 | 「plan IR 9941 op」（背景口径） | **成立** | 实测 `ghidra_track/out/pal3_full_plan.json` = 9941 ops（set_name 3830 / set_func_sig 3817 / define_global 1356 / define_struct 925 / define_union 12 / _meta 1） |
| 3 | 「adjudication 不消费（败者条目进 plan）」（spec:82） | **成立（机制）** | `ghidra_track/gen_plan.py:23-25`（methods 合并只取 name/signature/class，无 adjudication 过滤）；对照 A 侧已修：`pipeline/ida/apply_annotations.py:1382-1385`（rejected 禁消费 + owner 加权）、`pipeline/ida/export_full.py:369-370`（同型）——**B 侧缺的正是 A 侧 2026-11-03 已补的过滤** |
| 4 | 「inline-union dict 形被降级 byte（import_standard coerce 实证）」（spec:83） | **部分成立（形名不确）** | 机制真实：`ghidra_track/import_standard.py:28`（union 字段）与 `:33`（struct 字段）`type` 非 str 强制 `byte`。但**顶层 union dict 并不降 byte**——`ghidra_track/import_annotation.py:63-69` 已把 `{"union":[...]}` 转成 `define_union` op（且有单测 `ghidra_track/tests/test_annotation_import.py` `test_union_dict_maps_to_define_union`）。实测真正降 byte 的是：①inline-struct dict（`type={"struct":[...]}` 非 union 键，语料 4 件，如 `data/annotations/structs/RoleAttRemarkSkills.json` 的 `skillCount`）②union 成员内嵌 dict 型（语料 9+ 件，如 `data/annotations/structs/CCBTaskSlot.json` `_ovl_20`/`_ovl_28`）——它们经 `import_annotation.py:71-72`/`:66` 以 dict 形流到 import_standard 被降 byte |
| 5 | 「owner 字段不转」（spec:84） | **成立** | `ghidra_track/gen_plan.py:25`（`funcs[addr] = {'name','signature','class'}`）丢 owner；全 `ghidra_track/*.py` grep `owner` 仅命中 `gen_type_ownership.py:2` 无关文档串 |
| 6 | 「vtables 预期 dropped+理由（Ghidra 重算）」（spec:85） | **处置合法、理由不准确** | 甲案允许「dropped+理由」；但「Ghidra 重算」≠ annotation vtables 语义：实测 `data/annotations/structs/UIWnd.json` `vtables[0].slots[]` 带 `from` 归属字段（如 `"from": "UIFrameWnd"`）与 gap_fill 条目，Ghidra 自动分析无从复现；且 changeset 词表无 vtable 项（`thirdparty/ghidra-mcp/ghidra-worker/src/main/java/com/ghidramcp/Changeset.java:201-202`）。准确理由应是「B 面工具面无 annotation vtables 载体」 |
| 7 | 回读工具面 `list_functions`/`get_function_info`/`list_data_types`/`get_data_type`（spec:44） | **成立** | `thirdparty/ghidra-mcp/packages/mcp/src/tools/index.ts:672,690,2293,2311`；worker 分发 `.../CommandHandler.java:75-80,151`。**结构字段可回读**：`get_data_type` 描述明言返回 "structure fields and enum values"（`tools/index.ts:2311-2320`），字段形=name/dataType/offset/size/comment（`.../GhidraEngine.java:960-965` FieldDetail）⇒ **攻 2「get_data_type 能拿到字段名/偏移/型吗」答案：能** |
| 8 | 全局回读（题面列 `get_global_value`） | **题面工具名与实况不符（不判 spec 错，spec:44 未点名）** | 全仓 grep `get_global_value` **0 命中**；实际工具名 `get_global_variables`（`CommandHandler.java:208`，`GhidraEngine.java:456-457`） |
| 9 | 「回读 `diff=∅` ≙ 完备性实证 + 传递正确性」（spec:22-23） | **不成立（作为等价式）** | 证明力分解见 §3.1：diff=∅ 只在投影面内成立；完备性须矩阵兜底（spec 自己也写了矩阵互补，但把 diff 行直接标「完备性实证」过强） |
| 10 | 「fixture case-01 …（含 union 嵌套/thiscall/占位名形）」（spec:40） | **与 case-01 实况不符** | thiscall ✓（`ghidra_track/fixture/cases/case-01-struct-union-overload/annotations/structs/Derived.json` methods 4 条均 `__thiscall`）；**union 嵌套 ✗**（`Complex.json:4` union 为平 float/int 两变体，无 struct-in-union 嵌套）；**占位名 ✗**（fixture annotations grep `_todo_/_gap_/_unk_` 全 0 命中）；case.json features 列表（`case.json:2`）也无此二项 |
| 11 | 「不转字段须显式 dropped+理由，禁域外静默丢」（spec:11,27） | **规则成立，但转换链现状大面积静默丢**（预期红项不足，见 §2.6） | 见 §2.6 四项补充缺口 |
| 12 | 完成判据「真实 session proof=PROVEN（或 BROKEN 面全部显式入矩阵）」（spec:76） | **成立但有语义滑移风险** | 按 spec:11 的完备定义（每字段有显式归属）此式自洽；但「BROKEN 面全部显式入矩阵」与「PROVEN」并列作为完成条件，会把「已知不转+理由」与「已证传递」混在一个绿灯里——判据文本应改为二态报告（PROVEN 面 / DROPPED 面分账），见 §4-R10 |

### 2.2 攻 2：daemon 回读面够吗（逐工具裁定）

| 事实面 | 回读工具 | 裁定 |
|---|---|---|
| 函数名/签名 | `list_functions`（`tools/index.ts:672`）+ `get_function_info`（`:690`） | ✅ 可回读 |
| 结构字段名/偏移/型/尺寸 | `list_data_types`（`:2293`）+ `get_data_type`（`:2311`；`GhidraEngine.java:960-965`） | ✅ 可回读（含 bitfield 位偏移 `GhidraEngine.java:967-972`） |
| 全局名/型 | `get_global_variables`（`CommandHandler.java:208`） | ✅ 可回读 |
| adjudication / owner / evidence / name_source | **无 B 侧字段存储**（changeset 词表仅 rename_function/rename_global/rename_local/retype_local/set_prototype/set_global_type/struct_field，`Changeset.java:201-202,277-278`） | ⚠️ 字段级不可回读，但**「效果验法」分层裁定**：①adjudication 效果=胜者名/签落于地址 ⇒ **可操作**（get_function_info 对账）；②owner 效果=this 型/类归属 ⇒ **部分可操作**（签名 this 型可读；命名空间归属未转则不可验）；③evidence/name_source ⇒ **零效果**——spec:51 的 `indirect:<效果验法>` 对它们是空话。正解二选一：dropped+理由，或写入 comment 载体（`set_comment` 实存，`CommandHandler.java:117`，`list_comments` 可回读）——spec 未做这个分层 |

附加可行性事实：现导入链写入可靠性不足——实测 `ghidra_track/out/import_standard_fails.jsonl` 24 条 `"No transaction is open"` 写失败，而 `ghidra_track/import_standard.py:66-68` 只打计数不 fail-loud ⇒ 证明链必须先断言「导入成功」前提（§4-R10），否则「缺字段」与「写失败」混账。

### 2.3 攻 3：矩阵枚举源从哪来

- **无正式 schema 文件**：`data/annotations/` 无 schema 定义；校验逻辑散在 `tools/check_annotation_*.py` 家族。
- **实测字段面**（全语料键扫描，本次复核）：
  - struct 顶层 **45 种**键（`name/binary_size/known_members/methods/vtables(132 件)/bases(181 件)/base_size(177 件)/nested_types/_verdicts/pack/...`）
  - 成员 **14 种**（`name/type/source/evidence_level/offset/note/comment/union(5 件)/size/...`）
  - methods **33 种**（`adjudication 231（实测值域恰 3 值：shared_impl 97/rejected 76/confirmed 58）/owner 8/evidence 41/name_source 249/pending_adjudication 106/alt_name 105/ordinal 316/declaration_only 287/static 99/local_vars 8/...`，全库 3956 条）
  - `functions.json` **17 种**（`type:"skip" 199 · reason 198 · declaration_only 23 · face3_rule 6 · ...`）
  - `globals.json` **15 种**（`type:"skip" 203 · deleted 13（墓碑）· category 1330 · orig_type 20 · ...`）
- ⇒ spec:46「遍历 annotation schema 字段」**没有枚举源**；若由人手维护清单必腐（用户担忧成立）。可行形只有一种：**枚举源=语料机械键扫描（机器触发），分类账=人写 disposition（每键 transfer|dropped+理由|not-semantic）**——新键出现即红，补的是分类不是清单。spec 未写此形。

### 2.4 攻 4：实施序与环境成本

- 依赖顺序（spec:57-63）总体无倒置：RED → diff 引擎 → CLI 首证 → 矩阵 → 修缺口 → fixture → 重灌。三处问题：
  1. **RED 挂错构件**：spec:57 把「adjudication 漏转」用例放进 `test_verify_roundtrip`，但 §2.1 定义它是「投影/diff 纯函数测试」（spec:39）；病灶在 `gen_plan.load`（`gen_plan.py:23-25`）。RED 应拆两处：diff 侧「expected=裁决后语义 vs actual=现状 ⇒ 非空」+ 转换侧「build_import_plan 输出含 rejected 条目」——否则只测裁判不测转换器，gen_plan 回归无守护。
  2. **门禁触发面漏文件**：spec:47「转换器三文件 gen_plan.py/plan_to_changeset.py/import_standard.py 改动时必跑」——但字段取舍真身在 `ghidra_track/import_annotation.py:38-81`（`build_import_plan`），改它不触发门禁。
  3. **环境准备无落点**：Ghidra 12.1.2 一次性前置（`ghidra_track/README.md:36-44`：解压 + submodule pnpm build + pyghidra）与净室项目重建（`README.md:49-51`「清 .gpr+.rep 整目录再导」）在 spec 步骤表里没有位置。
- **环境成本/门禁现实性**：daemon 与 headless 互斥持库、跑前清会话锁（`ghidra_track/README.md:53-55`）；daemon 端口写死 8432（`ghidra_track/import_via_daemon.py:9`）⇒ pre-commit 并发/已有会话场景会撞；仓内无 `.pre-commit-config.yaml`（全仓 0 命中）；`pipeline/cli.py:1018` 的 loop 是 IDA 轨（apply→export→codegen→probe→match），把 Ghidra-daemon fixture_proof 挂进 loop 会把两轨环境耦合。**结论：接线须走独立 ghidra_track 门禁 + 环境 preflight，「进 pre-commit/loop 检查点」按现状不成立**。时间成本（「20 分钟级？」）仓内无任何测量记录 ⇒ 不判定（§5-4）。

### 2.5 攻 5：边界与遗漏

1. **「去重保后」的「后」=偶然性，且在证明域内**：`plan_to_changeset.py:9-28` `seen[key]=` 覆盖=内容保后、`order` 保首位；而同址唯一性上游由 `gen_plan.py:23-25`（`funcs[addr]=` dict 覆盖）决定，其遍历序=`glob.glob` **未排序**（`gen_plan.py:17`）=文件系统序=偶然性。A 侧刻意排序防漂移（`pipeline/gen/annotation_view.py:51-54`「排序与历史实现一致，避免产物顺序漂移」）；B 侧未排序 ⇒ 多注地址（实测 232 组，`data/status/review_multiclaim_audit_20261103.md` §3）的胜者可随机器漂移 ⇒ `gen_plan.py:1` 自述「G8 可重放」不成立。此点必须入证明域（否则 expected/actual 双侧各按一次偶然序归并，diff 无意义）。
2. **更细的 key 空间错位**：`plan_to_changeset.py:15,23` 把 set_name 与 define_global 归同一 key `'name:'+addr`，而 changeset 真实 targetKey 空间分立（fn-name/fn-proto/global-name/global-type，`Changeset.java:313-322`）且同目标重复是**报错拒收**（`Changeset.java:113-122`「changes the same thing as ops[N]」）不是去重——转换器 key 空间比 schema 粗，同址函数+全局时会互吃一个语义。
3. **多注合并序（first-wins）是被证对象的一部分，不是上游**：「忠实搬运 annotation 语义」在多注地址上**没有定义**，除非 spec 把归并规则写进契约。spec:61「跳 rejected/prefer confirmed+owner」是唯一线索，但未定义 tie-break（同 confirmed、无 owner、shared_impl 时谁胜）与序。A 侧规则现成可对齐：first-wins+owner 加权（`pipeline/ida/apply_annotations.py:1382-1385`）+ 文件序 sorted（`annotation_view.py:51-54`）。
4. **vtables**：dropped+理由合法，理由措辞须改（§2.1-#6）；另注意 `bases`(181)/`base_size`(177) 也在 spec:11 的域内但 §6 缺口清单未列。
5. **与 A 面真值轴的边界切对了**：spec:9「转换器只对忠实搬运负责；对二进制为真是 A 面的事」与用户裁定一致；fixture 的 `expected/layout.json` 是编译器机测（`expected/layout.json:5`「机测 layout_dump」）=对 fixture 自源码的独立真值锚，用作布局维 oracle 不越界。

### 2.6 攻 5 续：缺口清单漏项（全部本次实测，spec:78-85 应补）

| 漏项 | 实测 | 证据 |
|---|---|---|
| ① 变体键 int() 错位（发明偏移=比丢更糟） | `known_members` 变体键 `0_1`/`144_1`/`144_2`/`50814_0`（`data/annotations/structs/scVARIANT_data.json:13`、`PalScript.json:659,666`、`SceneMgr.json:138`；「off[_variant]+union:true」惯例）被 `import_annotation.py:59` `int(k)` **静默强转**：`int("144_1")==1441`、`int("50814_0")==508140`（Python 下划线数字分隔符陷阱）⇒ 成员落错偏移=**编造事实** |
| ② define_global 的 type 不转 | `import_annotation.py:76-80` 出 `type`，`plan_to_changeset.py:22-24` 只出 `rename_global`——**注释 `plan_to_changeset.py:8` 声称「rename_global+set_global_type」但代码没有**；schema 词表本支持 `set_global_type`（`Changeset.java:252`） |
| ③ skip/墓碑语义不消费 | `functions.json` `type:"skip"` 199 条、`globals.json` `type:"skip"` 203 条 + `deleted` 13 条（墓碑）+ `skip_functions.json` 整文件——`gen_plan.load`/`build_import_plan` 全不看；A 侧有 skip 语义（`pipeline/ida/apply_annotations.py:2422-2423`「skip "skip" and empty」、`:3067`）⇒ B 侧会把「不该进」的条目照灌 |
| ④ spec:83 形名更正 | 见 §2.1-#4：降 byte 的是 inline-struct dict（4 件）+ union 内嵌 dict 型（9+ 件），不是顶层 union dict |

## 3. 盲区与循环论证检验（攻 1 / 攻 6）

### 3.1 「回读 diff=∅」的核心盲区：期望侧循环论证（假绿）

`diff(project_b_facts(session), project_ann_facts(annotation))=∅`（spec:22）的期望侧 `project_ann_facts` 必须做三件事：①多注归并 ②变体键/inline 形解析 ③类型别名归一。**如果其实现复用转换器代码（`gen_plan.load`/`build_import_plan`）或复用其规则但同 bug**，则：
- 变体键 `int("144_1")==1441` 双侧同错 ⇒ diff=∅ ⇒ **发明偏移被证「正确」**；
- 归并序双侧同取偶然序 ⇒ diff=∅ ⇒ 多注语义漂移不可见；
- adjudication 过滤若双侧同漏 ⇒ 败者胜出被证「正确」。

⇒ **回读 diff 只能证明「搬运没走样」，不能证明「搬运规则对」**；后者的正确性只能来自（a）spec 钉死归并/投影语义（独立实现+禁 import 转换器模块）、（b）mutation 自证（§3.6）、（c）独立 oracle（fixture 机测/手写期望）。spec 三者都没写 ⇒ 这是本设计的最大缺口。

### 3.2 fixture 的证明力与循环面

- **不循环的维度**：布局（sizeof/offsetof）——`expected/layout.json:5` 是 `g++ layout_dump` 机测产物，独立于 annotation（e2e 规则亦明言「机测产物，禁手算」，`docs/specs/2026-11-02-e2e-fixture-rules.md:14`）。
- **循环的维度**：名/签/union 变体/占位名形的「期望」若由 `project_ann_facts` 从 fixture annotation 洛生 ⇒ annotation=输入=期望 ⇒ 零差只证「形变不失真」（spec:24 的措辞其实已承认），**不证「形对」**。且 case-01 实况根本不含 union 嵌套/占位名形（§2.1-#10）。
- e2e 规则「期望即真值」（`docs/specs/2026-11-02-e2e-fixture-rules.md:58`）与「禁改 fixture 迁就」（spec:71）方向正确——但那是防「迁就实现」，不是防「期望派生循环」。

### 3.3 假红盲区（同语义多形，diff 判据该归一到哪层）

- 签名形：annotation `"int __thiscall(int)"`（`Derived.json` methods）vs Ghidra 回读形（隐藏 this、类型别名 `uint`/`unsigned int`、`char[16]` vs `char *`、参数名剥除 `import_annotation.py:34`）；
- 名字形：mangled 直通 `?fixture_get@@YAHXZ`（`case-01 .../annotations/functions.json`）vs Ghidra 规范化形；
- union 形：plan 层 `UNION_<Cls>_<off>` 生成名（`import_annotation.py:65`）vs annotation dict 形 vs Ghidra create_union 实际名。
- ⇒ 判据必须归一到**语义事实层**（函数={名,调用约定,返回型,参数型列}；结构={尺寸,(偏移,名,型)集}；union=变体集），spec:45 五类 diff 未定义归一化层=假红假绿双险。另须定义 **extra 侧域过滤**：B 程序自带自动分析产物（数千符号/类型），不按 annotation 地址域+类型名域裁剪则 `extra` 恒红。

### 3.4 unverifiable 的语义滑移

spec:51 把「回读工具缺口」统一打成 `unverifiable+理由`。但实况分两类：**有载体可验的间接效果**（adjudication→胜者名签；owner→this 型）与**零载体**（evidence/name_source——纯溯源元数据，B 侧无效果也无存储）。前者用 indirect 免验=放弃了一条本可走的验证路；后者用 indirect=<效果验法> 写出来必是空话。两者的正名不同：前者=「effect:via <通道>」，后者=「dropped+理由 或 comment 载体」（set_comment 实存，`CommandHandler.java:117`）。

### 3.5 完备性证明的互补性边界（矩阵的自报属性）

矩阵（spec:20-21）是转换器作者的「自报家门」：字段枚举对了、每行 disposition 齐了，只证明**账面完备**，不证明转换器真按矩阵行事——这正是回读 diff 的职责。反之 diff 不管账外。两柱互补成立，但**任何一柱单独都不够**，而 fixture 只锚已覆盖形。三柱+mutation 才闭环。

### 3.6 攻 6：证明器自身有效性（mutation 测试）——spec 完全缺失

verify 器 bug ⇒ PROVEN=假绿。必须补「注入已知错误必须被抓」套件：导入后（或对投影输出）逐类注入：①改名 ②移偏移 ③换型 ④删字段 ⑤加多余字段 ⑥调换多注胜者 ⇒ diff 必须逐类转红。这是对**证明器**的证明，成本低（纯函数+合成事实即可起步），缺它则整条证明链的置信度无锚。spec:72「证明件变更=全链重证」只防漂移，不防验证器本身错。

## 4. 修订建议（可操作，按优先级）

| # | 修订 | 落点 |
|---|---|---|
| R1 | **期望投影独立化+语义钉死**：`project_ann_facts` 独立实现，合并语义写入 spec 契约——skip `adjudication=="rejected"`（对齐 `pipeline/ida/apply_annotations.py:1382`）、owner 加权（`:1383-1385`）、文件序 sorted（对齐 `pipeline/gen/annotation_view.py:51-54`）、tie-break 明文；verify 代码禁 import `gen_plan`/`import_annotation`（CI grep 守护） | spec §2.2 + 新测试 |
| R2 | **证明器自证（mutation 套件）**：§3.6 六类注入逐类必须红；纯函数半档（合成事实对）先行（R15），真实回读半档挂 fixture_proof | `tests/test_verify_roundtrip.py` + `test_fixture_proof.py` |
| R3 | **归一化层+域过滤钉死**：定义 canonical fact 形与类型别名表（可引 `ghidra_track/import_via_daemon.py:58-73` aliases 先例）；diff 保留双侧原形；`project_b_facts` 按 annotation 地址域+类型名域裁剪，extra 侧定义白名单形 | spec §2.2-2 |
| R4 | **unverifiable 拆两类**：`effect:via get_function_info/get_global_variables`（adjudication/owner）与 `dropped+理由`（evidence/name_source）或 comment 载体（`CommandHandler.java:117`）；禁对有载体字段用 indirect 免验 | spec §2.3 |
| R5 | **矩阵枚举源机械化**：守护测试的枚举源=语料机械键扫描（本次复核脚本形）；`proof_matrix.json`=每键 disposition 分类账；断言「语料键集 ⊆ 矩阵键集」，新键即红 | `tests/test_proof_matrix.py` |
| R6 | **缺口清单补 4 项**（§2.6：变体键 int() 错位 / define_global type 不转 / skip·墓碑不消费 / spec:83 形名更正）；变体键修复建议键形解析显式化（`off[_variant]` → (off, variant)），禁 `int()` 直吞 | spec §6 + `import_annotation.py:59` |
| R7 | **合并序钉死**：`gen_plan.py:17` glob 加 sorted（与 `annotation_view.py:54` 同式）；「保后」定义=sorted 文件序后者；`plan_to_changeset` key 空间对齐 `Changeset.java:313-322` 的 targetKey 分立 | `gen_plan.py` / `plan_to_changeset.py` |
| R8 | **fixture 形补缺**：union 嵌套/占位名/变体键/多注/adjudication 形按 e2e 规则**新立 case**（`docs/specs/2026-11-02-e2e-fixture-rules.md:58`「每加一层特性=新 case 目录」）；名/签期望**手写独立 oracle**，禁由 `project_ann_facts` 生成 | `ghidra_track/fixture/cases/` |
| R9 | **门禁触发面+接线现实化**：触发清单补 `import_annotation.py`；走独立 ghidra_track 门禁（preflight：GHIDRA_HOME/端口 8432/库锁，`README.md:53-55`），勿挂 IDA 轨 loop（`pipeline/cli.py:1018`）；CI 文档化 Ghidra 12.1.2 自备（`README.md:37`） | spec §2.2-4 |
| R10 | **导入成功前提 + 判据二态化**：verify_b_import 先断言 import_standard 失败计数=0（现状 `import_standard.py:66-68` 只打印）否则 verdict=IMPORT-BROKEN 与转换缺口分账；完成判据拆 PROVEN 面 / DROPPED 面两本账，禁合一个绿灯 | spec §5 + `verify_b_import.py` |

## 5. 未复验（不判定项）

1. **「25367 整编三连不变」**：全仓 grep 仅命中 spec:82 自引与无关 `data/status/_disasm_cache.txt:48812`，无原始记录 ⇒ 机制可证（§2.1-#3）、数字与「三连」不判定。
2. **活体 daemon tools/list**：本次以 `thirdparty/ghidra-mcp` HEAD 源码注册面为据；运行实例可能带未入库补丁，`get_global_value` 若存在于活体清单则 §2.1-#8 的「题面名不符」需翻案（仓内源码 0 命中不等于活体 0 命中）。
3. **get_data_type 回读形实测**：依 `GhidraEngine.java:960-965` 声明判定「可回读」，未跑活体样例核对序列化形（偏移串形/型串形与 annotation 型串的实差）。
4. **时间成本**：「本地 20 分钟级？」——仓内零测量（`report.json` 无耗时字段），不判定；结构性成本（daemon 互斥/项目重建/端口写死）已列 §2.4。
5. **dryRun/expect 乐观锁行为**（`plan_to_changeset.py:2`、`import_standard.py:56-62`）未复跑。
6. **adjudication tie-break**：值域实测 3 值（shared_impl 97/rejected 76/confirmed 58，231 条全扫），spec:61「prefer confirmed+owner」对 shared_impl/双 confirmed/无 owner 情形未定义 ⇒ 无法核对其正确性（已列入 R1）。
7. **case-01 链现状**：`ghidra_track/fixture/cases/case-01-struct-union-overload/report.json` 现存 D1 读数 `act:null` 全空（上次运行未产出布局测量）——fixture 链当前是否绿未复跑。
