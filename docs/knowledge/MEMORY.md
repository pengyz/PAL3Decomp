# 项目共享知识库索引

规则见 [README.md](README.md)。每次写入新条目后在对应 type 段追加一行。

## Architecture

- [gbui 七槽 vtable 继承链](arch_gbui_seven_slot_vtables_inheritance_chain.md) — gbui 家族 vtable 的槽位与继承链关系

## Gotchas

- [多重继承匿名成员渲染 bug](gotcha_codegen_multi_inheritance_anon_member.md) — 根因是 apply/export 两层自造限制（IDA 原生支持多基类），已修复并有单测+IDB 回归守卫；待重跑 codegen+compile 收口
- [annotation hook 从未生效](gotcha_annotation_hook_never_wired.md) — validate-annotations.py 路径过期 + 未接入 settings.json，双重失效
- [apply 静默失败（IDB 锁）](gotcha_apply_silent_fail_idb_lock.md) — 别的会话持有 IDB 锁时 cli.py apply 静默失败，cmd_apply 不以非零退出终止 && 链
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
- [**裸字节扫描不能当证据源**](gotcha_bare_byte_scan_as_evidence_source.md) — 在字节里搜 `0xC2/0xC3` 找函数尾会把**指令操作数**当函数尾；与指令级真值**分歧 367/3178（11.6%）**，幅度可达 105 个假 slots（`LoadActorModel` 真 1）；改用 `PAL3.exe.asm` 指令级为主源、裸扫描降为回退并上报
- [**globals.cpp 行序不确定**](gotcha_globals_cpp_nondeterministic_order.md) — 同输入两次生成，2703 行多重集完全相同、顺序不同 ⇒ 它的 md5 永远在变，不能当 A-B-A 字节锚点，也不能用 md5 判「该文件是否被改动」
- [**codegen 输出路径未锚定 PROJECT_ROOT**](gotcha_codegen_output_path_not_anchored_to_project_root.md) — `emit_cpp` 用 `store.project_root`、`emit_headers` 用 `PIPELINE_ROOT.parent`，而 `pipeline.toml` 的输入路径是绝对的 ⇒ 在 `git worktree` 里跑 codegen 会**先 rmtree 再重建主仓库的 pal3/src**；不要用 worktree 做 A-B-A

## Patterns

- [无证据批量重命名](pattern_annotation_batch_rename_no_evidence.md) — A:cascade_sync 标记的伪语义重命名事故，check_annotations 通过 ≠ 标注质量真实提升
- [**恢复多态基类的虚方法集合**](pattern_recover_polymorphic_base_virtual_methods.md) — 从二进制取证虚方法的完整方法链 + MSVC6 vtable 发射条件（定义本类虚函数才发射）+ ??_E/??_G 是同一函数

## Debugging

## Decisions

## References

- [IDA MCP 本机搭建](reference_ida_mcp_setup.md) — headless ida-pro-mcp 独立 venv，启动/打开 IDB 命令
- [SceneObj/UI 家族跨类调用是组合不是继承](decision_sceneobj_composition_not_inheritance.md) — base_size 钉死终裁；修复方向=transform 识别成员持有的跨类调用
