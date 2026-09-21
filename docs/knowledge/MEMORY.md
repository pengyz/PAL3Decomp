# 项目共享知识库索引

规则见 [README.md](README.md)。每次写入新条目后在对应 type 段追加一行。

## Architecture

- [gbui 七槽 vtable 继承链](arch_gbui_seven_slot_vtables_inheritance_chain.md) — gbui 家族 vtable 的槽位与继承链关系

## Gotchas
- [vtable 派发改写丢解引用](gotcha_vftable_rewrite_drops_deref.md) — `(*ptr)->__vftable->M(*ptr,…)` 被改成 `ptr->M(…)` 丢掉 `*`（76 站点/29 文件）；**只修这一行必被门禁拦下**：实测 C2227 −41 但 C2039 +22、S2 ok 75→74、L1 35→34，因为"接收者类型对"≠"方法确是该类成员"；完整批次与自门控验收测试见文
- [ida_defs.h 寄存器伪变量是字面量 0](gotcha_ida_defs_register_macros_are_zero.md) — `#define _EAX/_ESI/_ET1 0` 一个 hack = **167 条错误（7.8%）**，集中在 2 个单元共 150 条；且**无单一全局类型可修**（`void*` 会把 C2106 换成 C2036），根治在 IDB 签名/寄存器建模
- [中文注释行末 GBK 次字节为 0x5C 会吞掉下一行](gotcha_gbk_comment_trailing_backslash_eats_next_line.md) — MSVC6 按 GBK 读 UTF-8 中文注释 ⇒ 行拼接吞掉下一行（本次吞掉一个 __forceinline 定义）；四条死路与决定性验证手法见文

- [多重继承匿名成员渲染 bug](gotcha_codegen_multi_inheritance_anon_member.md) — 根因是 apply/export 两层自造限制（IDA 原生支持多基类），已修复并有单测+IDB 回归守卫；待重跑 codegen+compile 收口
- [annotation hook 从未生效](gotcha_annotation_hook_never_wired.md) — validate-annotations.py 路径过期 + 未接入 settings.json，双重失效
- [apply 静默失败（IDB 锁）](gotcha_apply_silent_fail_idb_lock.md) — 别的会话持有 IDB 锁时 cli.py apply 静默失败，cmd_apply 不以非零退出终止 && 链
- [计划代码片段必须在真实输入上验证](gotcha_plan_code_snippets_must_be_validated_on_real_input.md) — 只对着自造 fixture 写代码 ⇒ 真实 asm 上暴露 6 个 bug（2 致命：元组取反、16601 行尾注致锚点全失配）
- [测试必须断言契约而非现状](gotcha_tests_must_assert_contract_not_status_quo.md) — 断言『真实产物应含字符串 count』把缺陷固化成隐性规格 ⇒ 上游修好后测试反而失败；附翻转清单与变异自检法
- [asm funclet 需按 chunk 头归属宿主](gotcha_asm_funclets_without_proc_need_host_attribution.md) — SEH unwind funclet 无自身 `proc near` ⇒ 213/466 站点误挂最后一个 proc；且须在剥注释**之前**匹配、END 后失效安全
- [本机 pytest 崩，用自带 runner](gotcha_local_pytest_collect_crashes_use_self_runner.md) — collect 阶段 TypeError（sys.path 混入 aide 的 pytest dev 构建）⇒ 仓内测试一律自带 `__main__` runner，不依赖 pytest fixture
- [审计结论必须蒸馏进 knowledge](gotcha_audit_findings_must_be_distilled_into_knowledge.md) — 病灶不是"没落盘"而是"落错面"：`data/status/` 373 文件/293 tracked，而知识库只把它当"基线输入路径" ⇒ "审计 → status → 消失"；附 3 条可检查要求（落盘面/写入触发器/MEMORY 入链）
- [审查动作会写坏工作区](gotcha_review_actions_can_clobber_the_workspace.md) — 两起 `--help` 探测无 argparse 工具覆盖受跟踪产物（sig_evidence −6020 行 / ledger 197→3）；另一起 `ln -s` + 重定向**写穿符号链接**静默覆盖工作区文件；附护栏范式与"真实复制到 /tmp"规范
- [**init --force 后只跑一趟 apply 不够**](gotcha_apply_single_pass_leaves_globals_untyped.md) — 全局变量名字/类型不落地（`0xC10968` = `unk_C10968` size **1** 而非 `g_palScript` size 2176）⇒ S2 67/201 · L1 20 而非 70/201 · L1 21；**必须再 apply 一次**才算初始化完成
- [字节匹配判据被 mangler 单点把关](gotcha_byte_match_metric_is_mangler_gated.md) — matched/L1/partial 全经 mangled_map；base_idx 回退只对非 '?' 符号生效；**名字命中 ≠ 参与比对**
- [测量台复刻被测逻辑 + 比例须逐样本核验](gotcha_measurement_bench_replicating_subject_logic.md) — 复刻被测逻辑=测量另一个程序；"30% 边界错位"是我的 objdump 末行假象，实测 60/60 正常
  · 附二：**"改后读数"必须核验文件 mtime**（probe 遇退化拒绝刷新基线 ⇒ 读到的是改前值）
  · 附三：**基线不可复现时先 `init --force` 干净重建**再谈测量；`probe_census.json` 不被跟踪 ⇒ 须自行归档
- [PDB 身份漂移与 vtable 仲裁](gotcha_pdb_identity_drift_vtable_arbitration.md) — PDB 来自 PAL3A，偏移可能与 PAL3 不同，不能单独作证据（**2026-09-17 补充：定量裁决** —— 内嵌成员 stride + `new` 实参两条 A 级手段，把"哪张表属于哪个类"升级为可证明；工具 `tools/vtable_class_reconcile.py --stride`）
- [**vtables 无法从二进制导出**](gotcha_vtables_not_derivable_from_bytes.md) — 表在 .rdata 连续排布且内容全是 .text 指针，字节层无"表结束"信号；IDA 也只给 8 张建符号且无 UDT；6 个判据已穷尽
- [**归属信号的真实覆盖**](gotcha_attribution_signal_limits.md) — mangled 名可靠但 F2 缺口只命中 3/57；**IDA/注解的函数名本身不可信**；operator new=0x55353b 但 size 不唯一；F2 缺口分 A/C/D 三组
- [**PE 节范围须用 max(VirtualSize,SizeOfRawData)**](gotcha_pe_section_extent_max_vsz_rsz.md) — 按 VirtualSize 读 `.rdata` 会截掉尾部，把 `0x5704A8` 等**真实存在的 vtable** 误判为"未映射"，产出"18 个注解 vtable 是伪造的"**假发现**
- [**/OPT:ICF 使函数地址共享**](gotcha_icf_function_address_sharing.md) — 相同的函数被折叠到一个地址 ⇒「同一函数出现在两张不相关的 vtable」**不是**矛盾，不能当归属证据；要用 `[this+off]` 的语义/数据流判定
- [**compile_regression 读的是缓存 census**](gotcha_compile_regression_reads_cached_census.md) — 它从不重新编译，只读 `data/status/probe_census.json` ⇒ `codegen all` 后直接跑它会用**上一轮**数据报「✅ No regressions」；正确顺序是 codegen → **probe all** → compile_regression → error_classifier → match
- [**错误 census 不是源码的纯函数**](gotcha_error_census_not_a_pure_function_of_the_tree.md) — C1003 截断 15 个文件（恰 102 条，逐码增减不可测）+ 修掉早期错误会让后期错误"浮现"（CCBStage C2440 5→7 但 L3536/3540 源码逐字未变）⇒ "总错误数/逐码增减"是带噪声的指示器，可信量是 ok 文件数与 L1 多重集；工具 `tools/regression_detector.py` 已剔除截断单元
- [**可选后缀写在捕获组外 ⇒ 解析分支成死代码**](gotcha_optional_group_suffix_kills_parse_branch.md) — `RET_RE` 的 `h?` 吃掉 h，所有 `retn` 多位立即数按十进制解析，静默污染"显式 this 证据门"的二进制真值（`B-ODDRET` 不发 slots ⇒ 门永久阻塞；`20h`→错 slots；`0Ch`→ValueError 被吞）；pack 的 `err` 字段一直记着现场却无人消费。修法须收窄到"可被证明错"的 29 条，"顺手重评整张 pack"会误伤 54 条 `A-V2`
- [**上下文无关的替换会破坏已被改写的调用**](gotcha_context_blind_text_substitution_corrupts_rewritten_calls.md) — `Name((int)this)` → `this->Name()` 命中 `obj->Cls::Name((int)this)` 的尾部，拼出`obj->Cls::this->Name()` 畸形代码；**既有 15 处**被 C1003 截断掩盖，只有内容 diff 能发现；修后错误 3497→3305，截断文件 15→11
- [**集合键的形态必须与消费方一致**](gotcha_set_key_shape_must_match_consumers.md) — 同一循环里 `method_sigs` split 了、`static_methods` 没 split，而消费方都用裸名 ⇒守卫**恒为假**（104 条里 96 条形态不符）；后果是静态成员首参被当 `this` 吞掉，**仍能编译**（静默语义错误）。找法：同一段代码里相邻两行归一化不一致
- [**错的算术可能在意外顶住**](gotcha_wrong_arithmetic_can_be_accidentally_load_bearing.md) — 证明了 `//4` 错（A 级：`__vftable + 2` ⇔ `call [edx+8]`）就改它，结果 2 个 ok 文件转 fail、S2 净 −1；根因是 **DLL 类 vtable 注解不完整**（gbTexture 只标 0–3 而引用到 5；gbGfxManager 只标 0–6 而引用到 28），`//4` 把未标注的高槽折叠进低区间、侥幸产出能过类型检查的名字。教训：**"证明了它是错的"≠"证明了改成对的是安全的"**
- [**裸字节扫描不能当证据源**](gotcha_bare_byte_scan_as_evidence_source.md) — 在字节里搜 `0xC2/0xC3` 找函数尾会把**指令操作数**当函数尾；与指令级真值**分歧 367/3178（11.6%）**，幅度可达 105 个假 slots（`LoadActorModel` 真 1）；改用 `PAL3.exe.asm` 指令级为主源、裸扫描降为回退并上报
- [**globals.cpp 行序不确定**](gotcha_globals_cpp_nondeterministic_order.md) — 同输入两次生成，2703 行多重集完全相同、顺序不同 ⇒ 它的 md5 永远在变，不能当 A-B-A 字节锚点，也不能用 md5 判「该文件是否被改动」
- [**codegen 输出路径未锚定 PROJECT_ROOT**](gotcha_codegen_output_path_not_anchored_to_project_root.md) — `emit_cpp` 用 `store.project_root`、`emit_headers` 用 `PIPELINE_ROOT.parent`，而 `pipeline.toml` 的输入路径是绝对的 ⇒ 在 `git worktree` 里跑 codegen 会**先 rmtree 再重建主仓库的 pal3/src**；不要用 worktree 做 A-B-A

## Patterns

- [无证据批量重命名](pattern_annotation_batch_rename_no_evidence.md) — A:cascade_sync 标记的伪语义重命名事故，check_annotations 通过 ≠ 标注质量真实提升
- [**恢复多态基类的虚方法集合**](pattern_recover_polymorphic_base_virtual_methods.md) — 从二进制取证虚方法的完整方法链 + MSVC6 vtable 发射条件（定义本类虚函数才发射）+ ??_E/??_G 是同一函数
- [**用 ctor 做二进制挂钩前先验本体**](pattern_verify_ctor_body_before_binary_hooks.md) — 注解里的"ctor"可能是静态初始化 thunk（实测 `0x51D6E0`）；真 ctor 的判据是 `mov [this], offset <自己的vtable>`；配方=vtable 归属 → 表的 DATA XREF → 写表者

## Debugging

- [两层定位"是谁改写了我这行文本"](debug_two_layer_localization.md) — `sys.settrace` 行级追踪（钉死源码行）+ 代理该模块命名空间里的 `re`（打印真正生效的 pattern/repl/before/after）；配合"先禁用可疑解析器做二分"；本会话用它把上一轮的 12 次猜测换成 1 次定位

## Decisions

## References

- [IDA MCP 本机搭建](reference_ida_mcp_setup.md) — headless ida-pro-mcp 独立 venv，启动/打开 IDB 命令
- [SceneObj/UI 家族跨类调用是组合不是继承](decision_sceneobj_composition_not_inheritance.md) — base_size 钉死终裁；修复方向=transform 识别成员持有的跨类调用
- [IDA 立即数是十六进制字面量](gotcha_ida_disasm_immediates_are_hex.md) — `push 424h` 被 `%s` 原样打印成 424 ⇒ 我据此"推翻"了正确的 1060 并写进台账；规则：一律 `int(x,16)` 且同时打印两形态，结论前回 asm 核对
- [漏一个 global ⇒ "两阶段全或无"不存在](gotcha_missing_global_silently_disables_buffering.md) — `_BUFFER` 没写 `global` ⇒ 只建局部名 ⇒ 逐条直写；而"成对测试"因拒绝发生在校验阶段而变绿；规则：安全守卫必须落在唯一出口，测试必须让拒绝发生在被保护的那段
- [先确认你量的是哪个状态](gotcha_measure_state_before_not_after_change.md) — 用"求变更"的工具诊断"变更前后"，在已应用状态下必得 Δ=0 ⇒ 本会话三次错误结论；规则：写结论前先声明数据是哪一刻的
- [互锁不变式让局部修复净亏](gotcha_interlocking_invariants_block_local_fixes.md) — vtable 解析里 owner 文本同时是 `_drop_self_arg` 的输入、又与 stub 签名约定耦合 ⇒ 只修"owner 前缀截断"两轮各净增 17 条 C2660（两层各测一次）；规则：改被别处当输入的字符串前先找全部消费者；局部净亏 ⇒ 回退并立为独立项目
- [动手前先验证'病灶在哪一层'](gotcha_verify_the_layer_before_patching.md) — 跨层缺陷的病灶常在消费者侧；本会话 12 次假设驱动修补全部零效果，而每次只读验证（#include 链 + -I 顺序 + 临时 #error）都能一步定位；规则：先答'哪一层/消费者实际读哪个文件/报错还缺什么信息'再动手
- [`does not take N parameters` 不含类型信息](gotcha_does_not_take_n_says_nothing_about_types.md) — 该报错只说实参数目 ⇒ 据此推断重载必然失败（本会话两次）；必须 grep 出调用点所在函数的签名取真实类型；多站点类型不一致 ⇒ 属发射侧统一
