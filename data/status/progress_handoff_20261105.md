# 接续声明（2026-11-05）——B 导入改名落地战役·中场

## 已完成（全带证据·门禁五弹护航）
1. **证明链 T1-T10 全完**（spec 2026-11-04-converter-proof-design.md v2）：
   mutation 6/6 硬闸 · case-01/02 手写 oracle 零差 · 135 键矩阵 · 活体 proof
   · gate.sh+pre-commit 触发面（实路径 .git/hooks/pre-commit=符号链接→pipeline/hooks/）
2. **改名落地四轮**（标准通路逐根因族打通）：
   changeset ok **0→702→242→3165**；非 ident 名活验落地（0x401000=~AStarPathFinder）
   根因族账：expect 乐观锁 · C 标识符拒 dtor/mangled → create_label 面 ·
   set_prototype 三字段（signature 含名+cc __x+expect 双键）· 16/8-hex 键 int 归一 ·
   原子批单点拒（占位预滤+dryRun 剔重试环 parse_fail_indexes/partition_batch）·
   globals→label 面（无数据定义 1356 拒）· 签名 :: 限定名双位剥离（name 末段+ret 内剥名）

## 进行中（昨日中断点）
**ret 残名族诊断**：15 失败型分两类——
- ret 残名族（`virtual int GRPinput::InitKeyMappings`/`char * SetRoleLevelAndRefresh`/
  `BOOL PointInRect`/`int WinMain`/`void InitScriptEventArray`）=注解签名形
  `ret qualifiedName cc(params)` 中名字未从 ret 剥离（修：plan_to_changeset/ret 剥名
  通用规则——含 '::' 或尾 token 形如标识符且非类型词）
- 真缺型族（`__int64`/`const char *`/`const void *`/`void * `scalar deleting`）
  = 别名表（__int64→longlong 等）+ ret 形清洗（'virtual'/'scalar deleting' 前缀误入）

## 未完成（序）
1. ret 残名族修 + 真缺型别名 → 型解析族清（23 批→0）
2. ident 改名全量落地验证（0x401030 FUN_ 残面）
3. **② B 重跑**（净室导入→proof→generate→整编=真修后读数——欠两轮的兑现点）
4. 函数 bad 154 分类

## 新目标（2026-11-05 立项·oot 借鉴）
zeldaret/oot 分析结论：同编译器+声明式单源+逐函数匹配三支柱与我们同构（路线硬背书）；
值得借=诊断/进度工具层：①first_diff 首差定位 ②progress per-unit 仪表
③asm-differ 式函数级 asm 并排 diff（x86 支持度待验）+permuter 思想移植 Phase2。
序：2→3→1（first_diff 零成本即用）。

## 环境注记
- daemon 端口 8432（死则重启：GHIDRA_HOME=... node packages/cli/dist/bin.js &
  于 thirdparty/ghidra-mcp）；会话=PAL3_P.gpr（bf3837cd）
- 预存 7 测试失败（A 轨债·名单在 .superpowers/sdd/.../t*-suite.log）
- lstrip('0x') 陷阱禁用（切片 [2:]）——已三次犯

## 追加（2026-11-05 13:16 · s4 源修诊断中）

**s4 双文件异源病灶定谳+修**（commit a5eb05770）：cli.py 棘轮真退步分支只回写旧
baseline、detail 已被本轮 compare 覆写 ⇒ 双文件异源（实证 baseline 161/924-1188
vs detail 110）。修：`pipeline/s4_pair.restore_pair` 成对回滚+regressed detail
存档 `data/status/archive/`（诊断不丢）+prev detail 缺则移除 cur（宁缺勿伪同源）。
**盘上旧伤仍存**（恢复只保旧对不愈旧伤）——愈合须全链重跑+按需 --rebaseline。

**L1 161→94 读数定性（衰退纪律·先分析后动）**：主因=**总体收缩 1188→957**，
非可直接比 L1。指认 9 失 2 得（10-30 ok=135 → 11-03 ok=128·净 −7·
**窗口 10-30→11-03 的 annotation/gen 批所致·非本会话**·src 最新 11-03 20:18）：
- **C2084 重复体族 ×4**：CCBProtectWindow::Destroy / CCBFiveNimbusWindow::Destroy /
  UILoadingFrm::OnMessage / UIListBox::Destroy（already has a body——疑 codegen
  双发射单根因）
- **C2100 悬垂解引用族 ×3**：Effect/CEffGrid·CEffect·CEffgbParticle（illegal indirection
  ——疑 Effect 族单根因）
- JusticeBookUI（UIParticle 型可见性 C2227/C2653）· CameraCtrl（float*→float C2109/C2106）
- GAINED ×2：ARC_PlayerAtt.cpp·UICamera.cpp
⇒ **A 轨债移交项**：C2084 与 C2100 各疑单根因（2 修≈7 单元回）——修好即总体回升、
L1 可与 161 直接比、免 rebaseline。在 handoff 登记，不混本车道。

## 追加（2026-11-05 14:45 · B 面型解析族=四层病灶定谳）

**damage**：plan define_struct 929 → 程序在场 **77** · 缺 **852**（list_data_types
全量∩plan 清点）。函数名/改名面正常（~AStarPathFinder 持久）⇒ 仅 struct 阶段塌。

**四层病灶（全码证）**：
1. **假成功计数**（与 changeset ok 同族）：import 时 worker 病态（其后 daemon 死=
   同源）返回 JSON-RPC error 对象/空文本 → `t.startswith('Error')` 不中 → 计 ok。
   修：create_* 阶段 bad 判定必须认 `success: true` 文本（resp_ok 纯函数·TDD）。
2. **create_structure 无 size 参数**（inputSchema 证·128 工具无 resize/pad）：
   UIWnd `success:true 但 size=65≠68`——Ghidra 按 fields 和算，**尾部填充字节丢**。
   修=Java 侧 honor size（补 padding）或 fields 补 gap 成员。
3. **resolver 三缺形**（GhidraContext.resolveDataType:470 读码证实无 const 段）：
   dryRun 干探四例：`gbRay *`占位**可解 ok**（历史失败=当时型未生成）·
   `const char *` ❌ · `AStarPathFinder::NODE *` ❌（`::` 无映射且程序 0 条）·
   `struct gbVFileSystem *` ❌（前缀未剥）。
4. **nested_types 不消费**：AStarPathFinder.json nested_types.NODE 全声明
   （size64+f/h/g/x 成员）未建 → `AStarPathFinder::NODE *` 无解。
   + demangler 占位（/Demangler size1·gbRay/gbVec3D/gbVFileSystem/gbSound2DNode）
   可解但**布局是占位 1 字节**——语义使用前须以 annotation 真型覆盖。

**探针污染自首**（须清）：直调 create_structure 建出 root 副本——
`AStarPathFinder`(size1 空)·`gbVec3D`(root size1·与 /Demangler 占位并存)·
`UIWnd`(size65=按 fields 算·尾 3 字节缺) → 修后统一 delete_data_type+重建。

**修复序**：P0 resp_ok 假成功修（TDD）→ P1 Java 补丁（const/struct/class 剥离+
`::` 精确名优先+size honor）→ `npm run install:worker` 重编+daemon 重启 →
P2 929 重灌（存在性去重）→ P3 nested_types 入 build_import_plan →
P4 污染清 → P5 终验（get_data_type size 对齐+set_prototype 全探 ok+活体 proof）

## 追加（2026-11-05 15:50 · 三方件质疑定案+四探终局）

**用户质疑→取证定案**（三方改动三项全保留）：D2 证据=issues.md §4（D2 实战同款
错误类·上游修法=worker 预归一 extractCallingConvention 先例）+test/e2e 可执行契约
（纯 C 签名·从不传 size）+redivivus 无独立客户端（测试即契约）。
三方仓 commit `485639b`（7 文件·additive·D2 零行为变化）。

**四探终局（活体·全绿）**：
- `const char *` 返回 → **ok=True**（setPrototype 剥离生效）
- `struct gbVFileSystem *` → **ok=True**（同剥离）
- `AStarPathFinder::NODE` 指参+返回 → **双 ok=True**——**第 2 条定谳：根因=
  nested_types 未建型（型缺失），parser 不拒 ::**；建型（字面 :: 名·size64
  honor）即通。converter 侧 P3=nested_types 消费仍要做（批量建型）
- UIWnd size **65→68 honor** ✅ · NODE size **64** ✅（size 链三层+TS 转发全通）

**运维教训（新坑·记）**：**daemon 复用孤儿 java worker**——15:01 旧 JVM（载
15:00 jar）被新 daemon 接管，15:13 setPrototype 补丁假失效（探针全败假象）。
规矩：**重建 worker jar 后必须杀光 java 进程再验**（`ps java` 代际对表 jar mtime）。

**污染账（P4 待清）**：`gbVec3D` root size1 副本（/Demangler 占位仍在）·
`AStarPathFinder` root size1 空壳（P2 重建真型时 REPLACE）· ProbeNoColon 已删 ✓
· ProbeB/E/C/F dryRun 已回滚无痕 ✓

**P 链进度**：P0 resp_ok 假成功修 ✅（5/5）· P1 Java+TS 补丁 ✅（485639b·四探验）
· **P2 929 重灌（852 回填·存在性去重）=下一步** · P3 nested_types 入
build_import_plan · P4 污染清 · P5 终验（size 对齐+全探+活体 proof）

## 追加（2026-11-05 17:11 · A 案收口：P2 达成+B 面阶段性封账）

**用户裁定 A**：让 P2 跑完→跑一次 proof→**B 面阶段性收口**；P3-P5 降级按需；
B 面转低频交叉验证（只在 A 面新 annotation 批次时跑）；不再追求 B 面自身完美。
成本背景：B 面运维 debug ≈1.5-2 天（daemon 死×3/僵尸锁/孤儿 JVM/双会话互抢/
假成功/D2 契约考证）vs 验证收益（改名未落/852 型/1869 findings）——运维成本已超
验证收益，故止损收口。

**P2 终读**：structs **929 ok/0 bad·在场 929 缺 0**（852 全回填）·unions 12/0·
functions 5269/28·changeset 4800 ok/3571 bad（boundary-gap+interior 剔账族）·
占位预滤 11·label 1473·fail-loud 按设计响（rc=1·stat 分账缺口 509=剔环计数
结构差·已知不阻）·size 抽验 UIWnd=68/CCBAI=3664 ✓。
耗时 ~30min（串行 RPC 架构性成本：929 型+3800 函数+42 批×2.3s+剔环重试）。

**proof 终读（data/status/b_import_proof_20261105.json）**：
- match **11→924**（structs/成员面回填直接兑现）·structs exp925/**act1349**
- missing 2935→**453**·changed 11062→**6363**·extra 424·unverifiable 7570·
  coverage_extra 6227·verdict 仍 **BROKEN**（设计=缺口显形）
- 余量归因（=下轮两件）：①改名 changeset 3571 bad 剔账族（boundary-gap/
  interior/expect 残留）②nested_types（`AStarPathFinder::NODE` 未建·P3·
  手动建的随会话 churn 丢）

**下轮序（低频触发）**：A 面主线回（9 单元 S2 退化三族修复=c508a6c24 移交项·
L1 94 爬坡）→按需时 B 轮：P3 nested_types 入 build_import_plan + 改名 3571 bad
分类 + P5 终验。环境手册=本 handoff 三节（锁/会话/JVM 三清+孤儿教训）。
