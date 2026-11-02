# 对抗性复核：Ghidra 双轨验证轨·持久化架构两案决策（2026-11-02）

> 复核人：独立对抗性复核（subagent）· 被复核物：systematic-debugging Phase 1-3 证据链 + 两案（A 单会话 / B 续攻持久化）
> 铁律：不准确=不判定 · 只做等价变换不编造 · 字节匹配第一 · VERIFICATION-ONLY（验证轨可弃件）
> 本复核动作范围：只写本文件；全部实验跑在 `/tmp/persist_probe/`（ghidra_proj 副本），仓库派生物未改动。
> 复核方法：字节码取证（javap/zipfile 直读 Ghidra jar）+ API 契约取证（type stubs 原文）+ 三通道活体实验
> （读回探针 ×3 种 openProgram/保存组合 + 新鲜会话读回 + 现行代码实跑）+ 时间线考古（git log/diff/产物 mtime）。

---

## 1. 总裁

**裁 C —— 根因修案（B 的一击验已完成 ⇒ 立即三处小修 + 全链重跑收 M1 判据），否决 A，废止 B 的假设清单形态。**

一句话根据：**「持久化死」不是架构事实，是一个布尔参数 + 一个 NameError。**
`GhidraProject.openProgram(folderPath, programName, readOnly)` 第三参是 **readOnly**；
现代码传 `True` ⇒ 拿到「与原域文件脱钩的只读临时副本」（DomainFileProxy），
一切写入天然蒸发；传 `False` ⇒ 拿到真绑定（GhidraFile），`proj.save(prog)` 成功、
**新鲜会话读回实测通过**（`/annotations/PROBE_rw` + `PROBE_LABEL_rw` 均在，见 §3.1 实验 E3/E4）。

| 案 | 裁定 | 理由（证据） |
|---|---|---|
| A 单会话架构 | **否决** | ①根因修成本实测≈3 处小修（§5 T0），低于 A 案引入的结构性欠债；②A 案下 ghidra-mcp/daemon/M2 永远读不到 apply 结果 ⇒ D4 对拍（G1 核心产出）被永久锁死，欠债不是渐进是**结构性**（§3.2）；③D3 单会话判据缺 fresh-session 复验，A 案把缺口固化进架构（§3.2） |
| B 续攻持久化（假设清单逐个试） | **废止形态** | 「域文件写权 / openProgram 第三参语义 / importFile 自建档 / DomainFile 绑定丢失机理」四假设中，**第二条就是全部答案**（且方向与假设相反：False=绑定、True=脱钩）；此前 4 连败（varargs→ArrayList、proj.save→prog.save、setThis、deleteAll）全是真 bug 但均非根因——在错假设空间试错。目标保留，方法废止 |
| C 根因修案（新） | **采纳** | 一击验已中：`prog.getDomainFile()` 类读回 + API 契约 + 三通道保存实验互证（§3.1）；修复后持久化回归断言可进 CI，M2 前置条件同时满足 |

**必攻 1 的正面回答**：假设「pyghidra 会话的程序对象根本没绑定 domain file」——**证实**（E1 实测
`getDomainFile()` = `ghidra.framework.data.DomainFileProxy`，`exists()=False/canSave()=False`）。
但假设措辞「openProgram 第三参=False 语义=未绑定副本」**方向反了**：第三参名就是 `readOnly`
（type stub 实证），`True`=未绑定副本（getReadOnlyDomainObject，API 文档原文
"a new domain object that is **disassociated** from its original domain file" +
"a **temporary** domain file that will not allow a save"），`False`=正常绑定。
现代码传的正是 `True`。**真根因 = 参数语义误解**，一击验 `getDomainFile()` 读回即可定案（本复核已完成）。

---

## 2. 证据链漏洞表

| # | 原证据链声称 | 复核发现 | 等级 | 严重度 |
|---|---|---|---|---|
| L1 | 「持久化死」是待攻的架构级事实 | 根因=openProgram 第三参 readOnly=True 的脱绑只读副本；一行修复即通（E3/E4 实测 PROBE 落盘+新鲜会话读回） | 实测 | **高·定性反转** |
| L2 | 「同库不同写法命运不同」——demangler 写入神秘持久、apply 蒸发 | 归因错误。真差异是**写入通道**：demangler=导入期（analyzeHeadless 绑定通道）、早期 apply=postScript 形（同为绑定通道）；后期 apply=pyghidra `main()` runner（`openProgram(…,True)` 脱绑副本）。残留的 plan 派生 `update` 标签（ELF symtab 无裸 `update` 符号，`nm` 实证）证明**曾有 apply 写入持久过**——即 15:36 初版 postScript 形（git 12e1eeebc 实证初版无 `main()`、`currentProgram` 驱动）。「蒸发」是 runner 通道引入后才出现的 | 实测+git 考古 | **高·归因错误** |
| L3 | 对照组：`/Demangler/*` 桩持久 ✓ | **不可复验**：PAL3_FX/fixture 与 PAL3/PAL3.exe 两个程序的新鲜会话读回 `/Demangler` 均 = None。对照组证据失效（可能只见于瞬态会话、或被重导入抹掉、或本来就没有）。删掉此对照不影响 L2 新归因 | 实测 | 中 |
| L4 | `prog.save(None, CM)` 回退已接未验 | **已验=双死**：rw 绑定上抛 `IOException: Unable to lock due to active transaction`（GhidraProject.openProgram 自持外层事务——javap 实证其 save() 先 endTransaction 再存再 startTransaction）；ro 副本上抛 `ReadOnlyException: File is read-only`。回退通道应删除，不是修 | 实测 | 中 |
| L5 | apply 内事务 `startTransaction/endTransaction(_,True)` 正确 | 事务对本身正确；但**漏一层**：GhidraProject.openProgram 给每个程序开了常驻外层事务（javap 实证 openPrograms 表存 txn id）——这正是 L4 锁死的机理；事务模型认知缺一环 | 字节码 | 中 |
| L6 | 本面已 4+ 修 ⇒ Phase 4.5 交裁；「M1 的 D2/D3 判据即刻可收」 | **不成立**：当前 worktree `apply_plan.py:150` `return _mismatch` 是 **NameError 活虫**（`_mismatch` 从未定义，实跑 exit=1，崩在 apply 完成后、decompile/save 之前）；case-01 report.json（16:50）产自旧代码，早于 17:29 修复集。现场 D2=**FAIL**（transform-broken 1>0）、D3 member-access=**false**、union-view=**false**（report.json 实证）。「即刻可收」须先过 T0-T2 | 实测 | **高** |
| L7 | ArrayList 修复已证（绑 /annotations/SS ✓ 渲染 `->aa` ✓ 同会话 R2） | 微实验层可信（与 verify-comps 同型证据互证）；但**全链 case-01 产物是旧 `setArguments` 错绑代码所产**（slice 里 `*(int *)(this + 0x38)` 裸偏移、无 `this->m_flags`），修复后全链重跑从未发生。且微实验只证「同会话渲染」，fresh-session 渲染复验缺位 | 实测+时间线 | 中 |
| L8 | sizeof 对账=导入即校验 | 判据盲：report 里 `sizeof_mismatch: null`（无数据）被 run_e2e.py 判 PASS（`not a.get('sizeof_mismatch')` 把「无数据」当「无失配」）；旧 apply_plan 无 return 值，null=空转。真实信号在新 verify-comps（本复核实跑：Base.m_baseVal@8、Derived.m_flags@56、Complex fval@16、Vec3.x/y/z 全对） | 实测 | 中 |
| L9 | setThis 修复 | `f.setThis` 被裸 `except: pass` 吞错——与 varargs 静默错绑**同型风险面**仍在；失败无记账 | 读码 | 中 |
| L10 | 「新鲜会话读回一切变更蒸发」 | 大体成立但不精确：pyghidra runner 通道写入全蒸发 ✓；但 plan 派生 `update` 标签残留（postScript 时代写入）。「一切」应改为「runner 通道」 | 实测 | 低 |

---

## 3. 逐案攻防

### 3.1 一击验实验记录（全在 /tmp 副本，可复现）

| 实验 | 操作 | 结果 | 判定 |
|---|---|---|---|
| E1 绑定探针（ro，现代码语义） | `openProgram('/','fixture',True)` | `getDomainFile()`=**DomainFileProxy**；`df.canSave=False, df.exists=False, df.isReadOnly=True` | 假设证实 |
| E2 同会话写入（ro） | 事务内 addDataType(/annotations/PROBE_ro)+createLabel | 同会话全生效（PROBE_ro 可读回） | 与原证据链一致 |
| E3 保存通道（ro） | `proj.save(prog)` | 抛 `ReadOnlyException: Location does not exist for a save operation!`（与现场逐字一致；javap 证此消息=DomainFileProxy.save 硬编码抛出） | 原证据复现 ✓ |
| E4 保存通道（fallback） | ro 上 `prog.save(None,CM)` / rw 上同 | ro→`ReadOnlyException: File is read-only`；rw→`IOException: Unable to lock due to active transaction` | L4 回退双死 ✓ |
| E5 绑定探针（rw，修复向） | `openProgram('/','fixture',False)` | `getDomainFile()`=**GhidraFile**；`df.canSave=True, df.exists=True`；`proj.save(prog)` **成功**，`isChanged` 归 False | 修复通道打通 |
| E6 新鲜会话读回（决定性） | 新进程只读开库查 PROBE | **`/annotations/PROBE_rw` 存在、`PROBE_LABEL_rw` 存在**；PROBE_ro/PROBE_fallback=None | **持久化在一行修复后完全打通** |
| E7 现行代码实跑 | `python3.10 apply_plan.py …`（proj2 副本） | apply 工作全做完（names=11 sigs=8 structs=4 union=True、verify-comps 全对）后 **`NameError: name '_mismatch' is not defined`，exit=1** | L6 活虫实锤 |
| E8 对照组复验 | 两程序新鲜会话查 /Demangler | 均 None | L3 对照失效 |
| E9 纯逻辑回归 | `pytest ghidra_track/tests/` | 8 passed | 转换层纯函数无恙 |

关键字节码/契约证据（复验路径）：
- `ghidra/base/project/GhidraProject.class`（`tools/ghidra/ghidra_12.1.2_PUBLIC/Ghidra/Features/Base/lib/Base.jar`）
  `openProgram(String,String,boolean)` 分支：`iload_3; ifeq → getDomainObject(…,true,…)`（False=写开），
  落穿 → `getReadOnlyDomainObject(…)`（True=只读脱钩）；参数名 `readOnly`（同目录 `docs/ghidra_stubs/.../base/project/__init__.pyi:327`）。
- `ghidra/framework/data/DomainFileProxy.class`（`…/Framework/Project/lib/Project.jar`）：
  构造器注册 `TransientDataManager.addTransient`；`exists()=false`、`canSave()=false`、
  `save(TaskMonitor)` 无条件 `new ReadOnlyException("Location does not exist for a save operation!")`。
- `DomainFile.getReadOnlyDomainObject` 文档原文（type stubs）："…**disassociated from its original domain file**…"
  "…assigned a **temporary domain file** that will not allow a save…"
- 一致性：11.2.1 与 12.1.2 两侧 Project.jar 均含该消息（zip 扫描）；实验跑在 12.1.2（run_e2e 实际所用版本）。

### 3.2 A 案（单会话架构）攻防

**攻（风险实锤）**：
1. **欠债是结构性的**：M2 的消费端（ghidra-mcp/daemon/差分器）跨进程读库。单会话绕过意味着
   apply 结果永远活在进程内 ⇒ D4 对拍（spec G1 核心产出：C₁/C₂ 错误集差分）**永远拍不到 apply 效果**，
   拍到的是「未 apply 的 Ghidra 库」对「已 apply 的 IDB」——差分信号被系统性污染，G1/G2 全部失真。
   「M2 前欠债越滚越大」的答案：不是量的问题，是 A 案在 M2 边界**必然二次手术**。
2. **D3 判据的两半**（必攻 2 正面回答）：(a) 渲染本身是真实能力——decompiler 读活 DTM，
   微实验 `->aa` 与 verify-comps（成员落位全对）互证，非缓存假象；(b) 但「同会话绿」不覆盖
   「落盘→fresh session→再渲染」，若持久化后 DTM 重载有差异（category 解析/类型归并），D3 会翻车。
   ⇒ 现 D3 判据**欠一条 fresh-session 渲染复验**（无论选 A 选 C 都该补；选 C 顺手补）。
3. 验证轨铁律「失败即弃」（spec §5）已内置降级出口——A 案是把降级出口当主干走。

**守（A 案仅存的合理面）**：若 B' 修复经 T0-T2 验证后 fresh-session 渲染仍系统性不一致，
A 案降级用法（「Ghidra 单函数对偶旁证」）就是止损形态——但它只配当**降级**，不配当架构。

### 3.3 B 案（续攻持久化）攻防

**攻**：四假设清单里三条是伪问题（域文件写权：`GhidraFile.canSave=True` 实测否；
importFile 自建档：不解决 openProgram 语义，纯绕行；DomainFile 绑定丢失机理：机理=getReadOnlyDomainObject
文档明示的脱钩语义，不需要再攻）。唯一真假设（openProgram 第三参语义）一击验即中。
**「4 连败」的教训不是持久化不可攻，而是从未做 E1/E3 型最小判定实验就开始打补丁**——
四个修（ArrayList/setThis/deleteAll/save 回调换位）全在错误层。

**守**：B 的**目标**（跨进程持久化，M2 消费必需）完全正确——只是方法该换成根因修（=C）。

---

## 4. 第三案评估（必攻 4）

| 案 | 内容 | 评估 |
|---|---|---|
| C1 pyghidra 建档自导入（不经 analyzeHeadless） | GhidraProject.importFile/createProgram 自建库 | **可行但不必要**：绑定问题不在「谁建档」而在 openProgram 第三参；importFile 返回的程序天然绑定，但后续 openProgram 仍要传对 readOnly。价值=卸 analyzeHeadless 依赖（长期），非本瓶颈 |
| C2 import 型 API 工具化（ghidra-mcp 内置导入） | 把导入+apply 收进 MCP 工具链 | 同 C1：消费通道问题，不是持久化根因；M2 阶段再议 |
| **C3 根因修（裁中）** | 三处小修+全链重跑+回归断言 | **最优**：成本 0.5-3h、M2 前置条件一并满足、VERIFICATION-ONLY 下风险≈0 |
| C4 saveAs/saveAsPackedFile 副本落地 | 对脱绑副本 save-as 新文件 | 语义=另起库文件，等同弃原库重建，劣于 C3；仅当 C3 失败的兜底（比 A 干净） |

---

## 5. 执行序 + 止损判据

| 步 | 动作 | 验收判据 | 时间盒 |
|---|---|---|---|
| **T0 三处修** | ①`apply_plan.py:161` `openProgram(_folder,_name,**False**)` ②`:150` `return _mismatch` → `return diffs`（同步 `:164`）③`:199-203` 删 `prog.save(None,CM)` 回退（单通道 `proj.save(prog)`，异常响亮上抛）；顺手 `:118` `f.setThis` 的 `except: pass` 改记账打印（L9 同型风险面） | `pytest ghidra_track/tests/` 8 passed；E7 重跑 exit=0 | ≤0.5h |
| **T1 持久化回归断言** | 复用本次 E5/E6 探针为脚本：apply 一枚 PROBE 类型+标签 → `proj.save` → **新进程读回** | PROBE 类型+标签双命中（断言非 null 不算数，必须正存在）；建议进 run_e2e 链尾防 openProgram 语义回退 | ≤1h |
| **T2 case-01 全链重跑** | `run_e2e.py case-01-struct-union-overload`（apply→出码→D1-D4 首读数） | D3 member-access/union-view 预期转绿（ArrayList+setThis 全链生效）；D2 transform-broken 1 条展开归因（现只记数不记文）；D1c 判据修 null=PASS 盲点（L8） | ≤1.5h |
| **T3 D3 补钉** | fresh-session 渲染复验：持久化后重开库 decompile 同函数，渲染结果与同会话比对 | 逐条一致才收 D3（堵「缓存假象」缺口，必攻 2 的另一半） | ≤1h |
| **T4 收 M1** | D2/D3 判据正式落档 `dual_track_m1_diff.json`（spec §8） | 四钉读数齐；D4 挂 IDA 轨占位 | ≤1h |

**止损判据（具体）**：
1. T0-T2 累计 >1 天仍未产出 D2/D3 有效读数 ⇒ 冻结，降级「Ghidra 单函数对偶旁证」（spec §5 条款），M2 按欠债立案并显式记「D4 对拍不可用」。
2. T3 若 fresh-session 渲染与同会话渲染**系统性**不一致（>1 个函数级差异且同型）⇒ 停止扩面，回到 M1 用法，持久化仅保「MCP 可读库」用途，渲染判据只认 fresh-session 侧。
3. T2 若 member-access 仍红 ⇒ 查 `setThis` 吞错（L9）与 this 形参绑定；同型修 2 次仍红 ⇒ 记 hexlimits 观测挂账，不恋战。
4. 任何阶段发现要动字节轨（annotation/pal3/src）才能推进 ⇒ 立即停（spec 铁律 3），回 master 走完整管线纪律。

---

## 6. 未复验（本复核未覆盖/未重跑项）

| # | 项 | 状态 | 建议 |
|---|---|---|---|
| U1 | Q3/Q4/Q6 微实验（同会话 getDataType/allStructures 立即命中） | 未重跑（与 verify-comps 同型证据互证，可信） | 随 T2 覆盖 |
| U2 | SS 绑定微实验（渲染 `->aa`）原始记录 | 会话内实验、盘上无产物（out/ 各 plan 无 SS），仅凭提交描述 | T2 全链重跑等效覆盖 |
| U3 | analyzeHeadless -postScript 通道持久性 | 未现场重跑；「postScript=绑定通道⇒持久」由 `update` 标签残留反推（ELF 无裸 `update` 符号） | 低优先；机制已由 E3-E6 侧证 |
| U4 | PAL3_FX.rep 17:31 idata/user/versioned 触碰来源 | 未复盘（疑似 run_e2e 重导入；若重导入会抹写入，U3 的标签解释需一次日志回放） | 低优先 |
| U5 | D2「transform-broken 1 条」的具体错误文本 | run_e2e 只计数不记条文 | T2 顺手收 |
| U6 | Ghidra 11.2.1（spec 所写）vs 12.1.2（run_e2e 实用）双版本 | 机制两侧同类（jar 双侧扫描含同一消息）；实验在 12.1.2 | 钉死单一版本入 spec |
| U7 | ghidra-mcp/daemon 端消费读库（M2 域） | 未验——依赖 T1 通了才可测 | M2 首项 |
| U8 | plan_m1_slice.json（真实 PAL3 切片 160 名/159 签/3 结构/200 全局）的 apply 效果 | out/slice 里 ArraySort.c 显示旧 `setSignature` 通道签名未生效（"parameter storage is locked"）——postScript 时代名称持久但签名没绑上 | T2 后用真实切片重跑一轮（M1 本体） |

---

## 附：证据快照（自包含，防 /tmp 清场）

```
E1  ro:  getDomainFile=DomainFileProxy canSave=False exists=False isReadOnly=True
E3  ro:  proj.save(prog) -> ReadOnlyException: Location does not exist for a save operation!
E4  fb:  prog.save(None,CM) -> rw: IOException: Unable to lock due to active transaction
                              ro: ReadOnlyException: File is read-only
E5  rw:  getDomainFile=GhidraFile canSave=True exists=True; proj.save OK; isChanged=False
E6  RB:  /annotations/PROBE_rw = /annotations/PROBE_rw   (存在)
         PROBE_LABEL_rw @0x4011fe = True ['update','_ZN4Base6updateEi','PROBE_LABEL_rw']
         /annotations/PROBE_ro|fallback = None ; /Demangler = None (两程序皆然)
E7  apply_plan.py 实跑: [apply_plan] done: names=11 sigs=8 structs=4 union=True nofunc=None
         verify-comps: Base.m_baseVal@8 Derived.m_complex@12,m_pNext@48,m_flags@56
                       Complex.id@0,pos@4,fval@16,name@20 Vec3.x@0,y@4,z@8
         -> NameError: name '_mismatch' is not defined   (exit=1)
E9  pytest ghidra_track/tests/ -> 8 passed
现场  case-01 report.json: D2=FAIL(transform-broken 1>0) D3 member-access=false union-view=false
      slice/Derived.update: return iVar1 + *(int *)(this + 0x38);   (无 this->m_flags)
```

复现命令骨架：`cp -r ghidra_track/ghidra_proj /tmp/persist_probe/proj` →
`GHIDRA_INSTALL_DIR=…/ghidra_12.1.2_PUBLIC python3.10 probe_persist.py <proj> {ro|rw|fallback}` →
`python3.10 readback.py <proj>`（探针全文随本复核会话，逻辑等同 §3.1 表）。
