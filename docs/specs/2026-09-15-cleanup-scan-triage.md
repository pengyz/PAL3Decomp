# 清理扫描汇总裁决（t5）

生成：captain 接管 t5 · 2026-09-15T13:21:36

## 批次计数

- **B3_need_evidence** = 200  （需补证（逐条单独取证，禁止批量修改））
- **B5_intentional_keep** = 27  （有意保留（信号/刻意的设计/冻结证据/文档化））
- **B2_fix_pipeline_codegen** = 23  （可立即修（管线/基建/codegen 类）→ t7/t8/t13/t14/t15/t16）
- **B4_delete** = 14  （应删除（僵尸资产/死路径/坏形态入库））
- **B1_fix_annotation** = 4  （可立即修（注解/布局类，有 A/B 级证据）→ t6）

## 每批责任任务

- t8: 12 条
- t15: 6 条
- t6: 4 条
- t13: 2 条
- t16: 2 条
- t14: 1 条

## B1 可立即修（注解/布局，t6）

- T6-01 [A] SceneObj 删除越界成员 18804/18808（m_nSpringTargetX/Y）——实属 CCBRoleState
- T6-02 [A] UICursor binary_size 32→64（A 级：UICursor::Update 中 esi=this 访问到 +0x3E）
- T6-03 [B] SaleUI 33 项逐条裁定（32 项位移在整份 asm 出现 0 次 + 第 33 项 ml_SmeltList 位移属 124268 字节类）——禁止整批删除，须逐条证据 + 显式回应"binary_size 偏小"竞争假设
- T6-04 [B] SaleUI 两条 member overlap（m_ani@88320 ends88484 > pNGHVarianceParticle@88408；m_Role@88484 ends89244 > m_nDataPoolBase@88540）+ globals 重叠 g_RoleSlotBuf ⊂ g_SceneMgr 需 overlaps_with

## B2 可立即修（管线/codegen）

- CG-001 → t15 [B] [VFTABLE] 1643 站点是对真实语句的注释化（非等价变换）：仅 41 处(2.5%)是编译器自管的 vptr 存根，其余为真实数据访问/控制流头被丢弃
- CG-007 → t15 [B] [IDA_MISID] 84 站点以硬编码模式表在 codegen 层注释掉 IDA FLIRT/TIL 误识别行——非等价变换 + 应在 IDA 层解决
- CG-008 → t15 [B] [AUTO-COMMENTED] 229 站点中的 89 处是丢弃被使用赋值的 ctor 注释化（非等价变换），且该标记不在五类清单内
- CG-019 → t15 [B] pipeline/gen 共 29 处裸 except: 与 4 处 except Exception: pass，其中 data.py:218 会静默丢弃 thunk 映射
- CG-020 → t8 [B] cli.py 的 codegen all 后置 snapshot/regression 钩子不检查 returncode：门禁失败被吞、命令仍以 0 退出
- CG-021 → t8 [A] pipeline/compare_pal3.py 未守卫 census 读取：缺 probe_census.json 时 cli.py match 以裸 FileNotFoundError 崩栈（非可操作提示）
- CG-022 → t8 [A] tools/annotation_diff.py 无法区分'无变更'与'读不到 git'：git 不可用时把 898 个结构体全报为新增并以 exit 0 结束
- CG-023 → t13 [B] [ROWTABLE] 语义依赖静默失败的 status 文件：_rowtable_family() 读不到 data/status/_rowtable_family.json 时返回空集，576 个站点会整体降级为 [M
- AT-199 → t15 [B] [IDA_MISID] 84 处仍留在生成产物中：命中即整行注释，真实语义一并被抹掉
- AT-200 → t8 [A] binary_size 已被"撑大/占位"值污染，使 attribution/misattribution 门禁全部失效：52 个 struct 的 binary_size > 3x 最大声明成员偏移
- AT-212 → t15 [B] [IDA_MISID] 子类 (ii) 应重命名保留：std::_Xlen/_Xran/Concurrency 共 69 处，对应真实代码而非库调用
- AR-001 → t16 [B] 裁决(a)-要件2：data.py:226 '唯一位置' 断言失实——本身作为 C1 违规证据
- AR-002 → t13 [B] 裁决(a)-要件1：codegen 12 处读取 data/annotations 落在声明例外之外
- AR-003 → t14 [A] export 层读 data/annotations（红线：export 不读 annotation）——export_full.py 共 10 处直接读取
- AR-004 → t8 [B] cmd_apply 失败时以退出码 0 结束，破坏 `apply && export && ...` 门禁链
- AR-005 → t8 [B] tools/audit_layout.py 在缺 asm/pal3/ida_structs.json 时仅告警并以空 dict 继续，跨 IDA 的布局校验被静默跳过，形成'零问题'假通过
- AR-006 → t8 [A] compile_regression.py 的棘轮基线 data/status/compile_baseline.json 自 2026-09-01 冻结（58/204），与当前 53/198 长期失配，门禁每次恒定报警
- AR-007 → t8 [A] codegen all 的后置 snapshot 钩子在缺 probe_census.json 时以未捕获异常终止（FileNotFoundError 堆栈），而非可操作提示
- AR-008 → t8 [B] work IDB 为单写者共享文件且无锁探测：团队并发 agent 会竞争同一 original/PAL3.exe.i64（按脚本直接 `idat -A -Sscript <idb>`，无锁检查）
- AR-013 → t8 [A] VC6 小写 shim 的存在性无任何门禁校验：跳过 setup 会以晦涩的 "cannot open include file" 失败
- AR-202 → t8 [A] data/status/baselines/latest.json 是 dangling symlink：唯一 tracked 的符号链接指向未入库的时间戳文件
- AR-203 → t8 [A] compile_regression 门禁与 probe 快照使用两套互不相通的基线（compile_baseline.json vs baselines/latest.json）
- AR-204 → t16 [A] 生成物中的注解路径字面量过期：globals.h 头部注释指向不存在的 pipeline/data/annotations/globals.json

## B4 应删除

- CG-009 stage3_cleanup 的 action 分派含两个永不产生的分支：'comment_vft'（发射 [IDA_VFTABLE]）与 'insert'
- CG-010 stage3_cleanup._node_contains_text 无任何引用
- CG-011 stage3_cleanup._is_vftable_call 无任何引用
- CG-012 stage3_cleanup._try_resolve_vftable 无任何引用，已被 _resolve_vftable_calls_ast 取代
- CG-013 stage5_fixup 的数组 stride 索引三件套从未接线（dead-on-arrival）
- CG-014 emit_headers 的 [IDA_USERPURGE] 分支不可达：sig 中的 __userpurge/__usercall 在检查前已被剥离
- CG-015 emit_headers 的 [IDA_REGPARAM] 分支不可达：@<reg> 在检查前已被剥离（且被剥离两次）
- CG-016 emit_headers.OVERRIDES_DIR 指向不存在的 include/pal3/overrides，且该常量无任何引用（override 机制已被 template_bases.json 取代）
- CG-017 pipeline/gen 中 4 个模块存在无引用 import（data.py 的 os/Path、stage4/stage5 的 struct、emit_headers 的 sys）
- CG-018 pipeline/cli.py 的 iterate 命令指向不存在的模块 pipeline/iterate.py（调用即 ModuleNotFoundError）
- AT-201 // [MISATTRIB] attribution unconfirmed 这条 codegen 路径是死路径（生成产物 0 处）
- AR-301 仓库根空文件 __vftable（0 字节）被版本控制跟踪
- AR-302 original/PAL3.exe.i64.polluted.bak（85MB）不被 .gitignore 覆盖，存在误提交风险
- AR-303 工作区本地残留：build_output.txt(919690B)、8 个一次性 .obj、/tmp 之外的临时 .obj 全是未跟踪且已被忽略

## B5 有意保留

- CG-002 [VFTABLE] 中 41 处真正的 vptr 存根（this->__vftable = &vtbl）是合法的等价变换信号，应保留
- CG-003 [VFTABLE-STUB] 612 站点是 substitute 型信号（非破坏性存根），有代码注释与提交双重保留理由
- CG-004 [ROWTABLE] 576 站点是 gbUI 7 槽消息处理器家族的表分发保真形式，保留理由经 4 轮对抗性复核后写入代码与知识页
- CG-005 [MISATTRIBUTED] 344 站点是证据门槛下的诚实信号（保留静态调用形式令 MSVC6 报 C2352），非缺陷
- CG-006 [IDA_VTABLE] 生成物仅 1 处（在 .h 中而非 .cpp）：emit_headers 跳过不可拼写的 vtbl_ 参数类型声明，是有意的保守跳过
- AT-022 [MISATTRIBUTED] AStarPathFinder::GetHeuristicIdx x3 — callee attribution is BINARY-CONFIRMED correct; root cause is the 
- AT-197 _misattrib_evidence 历史串 222 条挂在 structs/*.json 上，无任何活代码消费；141/182 可解析条目的 class_size 与当前 binary_size 不等
- AT-198 misattribution_ledger.json 197 cluster 全部 bucket=C / rename_to=null，bucket A/B 的判据在本仓数据下不可计算
- AT-202 [IDA_VTABLE] 唯一 1 处在头文件注解（pal3/src/Render/RenderTarget3.h:31），与生成器实际标记名 [IDA_VFTABLE] 拼写不一致
- AT-203 AStarPathFinder::GetHeuristicIdx x3 — 桩体候选（decomp 平凡 5 字节）：桩体检测在此地址无判别力
- AT-204 LineupComp::DispatchSlotMethod x7 — 桩体候选（decomp 平凡 18 字节）：桩体检测在此地址无判别力
- AT-205 CCBRoleState::CalcComboDirect x1 — 桩体候选（decomp 平凡 18 字节）：桩体检测在此地址无判别力
- AT-206 CCBSystem::CalcSpeed x2 — 桩体候选（decomp 平凡 22 字节）：桩体检测在此地址无判别力
- AT-207 ScriptVM::IsRunning x1 — 桩体候选（decomp 平凡 26 字节）：桩体检测在此地址无判别力
- AT-208 PAL_GDB::IsRoleAlive x1 — 桩体候选（decomp 平凡 29 字节）：桩体检测在此地址无判别力
- AT-209 PAL_GDB::IsRoleDead x1 — 桩体候选（decomp 平凡 29 字节）：桩体检测在此地址无判别力
- AT-211 [IDA_MISID] 子类 (i) 事实正确但丢语义：NtTib/ExceptionList 共 15 处（SEH 探针样板），注释后留下悬垂引用
- AR-010 缩减式尺寸落地脚本 tools/_land_sizes.py：以硬编码尺寸猜测 + 弱通过条件(Keep if S1>=baseline and S2>=baseline)写回 binary_size
- AR-011 tools/ida/archive/pal3_fix_oversized_structs.py 以 char _data[N] 占位替换真实结构定义（破坏性 workaround 残留）
- AR-012 tools/vc6 的 1258 条小写符号链接是刻意的跨平台构建适配层（Linux 大小写敏感 fix），非脆弱耦合
- AR-015 N1_STUB_CALL_NO_FIX：CCBAI 三处 [MISATTRIBUTED] 站点(callee 0x004014F0 为 3 字节桩)已定案 NO_FIX，记录以防再被当待修 misattribution 重扫
- AR-016 [MISATTRIBUTED] 标记把'合法直呼(callee 为桩)'与'真归属错误'报成同一动作：建议文本已被证伪、判据本身未被证伪，须用户裁决后才可改 policy
- AR-101 五类 codegen 信号标记本身是有意保留的设计信号（产生位置均带保留理由注释），非缺陷
- AR-102 IDA 数据库多份历史备份（.bak/.91/.92/.polluted.bak）是单写者 IDB 语义下的灾难恢复副本，属有意保留
- AR-201 pal3/src/ 全部 198 个 .cpp 与 include/pal3/gen/ 被 .gitignore 排除，验收判据（S2 ok、L1）所依赖的产物在干净检出中不存在
- AR-205 脚本内硬编码的过期路径引用（引用文件/工具均已不存在）
- AR-304 本地堆积的 10 条 stash 与备份分支 backup/local-line-20260904

## 自洽校验
```
{
 "C3_class_count": 226,
 "C3_subclass_sum": 226,
 "C3_ok": true,
 "C4_class_count": 4,
 "C4_subclass_sum": 4,
 "C4_ok": true,
 "FIX_on_CDE": 0,
 "NEED_EVIDENCE_without_proof": 0
}
```

## 全局 caveat（读数前必读）

- ⚠️ 计数基于 10:39 之前生成的 pal3/src；该树已于 10:39 被一次未授权链（apply→export→codegen all）重新生成，当前树标记数不同（[VFTABLE] 1643→1935、[AUTO-COMMENTED] 229→233）。权威计数须在权威窗口后重取。
- 当前环境三层不一致：工作区注解=未修复态 / IDB=修复态 / pal3/src+asm/pal3/decomp=由修复态 IDB 生成。所有读数在权威窗口（t6 apply→export→codegen）之前不可比。
- IDB 曾于 10:34:43（apply）与 10:37:38（export 收尾）被写；t9 必须在净态自行重跑 apply 取数。
- 权威口径更正：export_full.py 直读 annotations = 9 处（非 10）；AUTO-COMMENTED = 233（非 229）；[VFTABLE] 当前树 = 1935（原 1643 属旧树）。
- B6 类结论的独立复核只覆盖 callee 侧；"caller 传错 this 类型"另有扫描工具自报，需独立取证。
- audit_layout 假通过是条件性缺陷（需 ida_structs.json 缺失才触发，该文件当前存在）。
- "10:34:43=apply" 为 mtime 聚簇推断，非直接日志证据。
- 退出码取值一律用 PIPESTATUS[0]（cmd | tail 会让 $? 变成 tail 的退出码，已致两次误判）。

## 需补证批次（B3）
共 200 条 + 31 个缺口；逐条单独取证、**禁止批量修改**；其中 200 条带 proof_needed。
