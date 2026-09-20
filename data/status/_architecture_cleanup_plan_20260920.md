# 架构清理与修复 · 实施计划（2026-09-20）

依据：`data/status/_audit_repair_plan_20260920.md`（Kiro 独立复核版）。
目标（本会话长期目标 `goal-312d2835`）：**完整实施 P0→P1→P2**，每项带验证证据，每步提交推送。

## 硬约束（全程）
不重写 5 阶段 codegen 管线；不做未经用户同意的 git 历史重写；
每项改动后必须验证 + 提交推送；**L1 多重集不得回退（基线 34）、总错误不得增加（基线 2151）**、
`pipeline/cli.py check` PASS；结束时工作区 clean。

## P0 止血（先做，成本小）
| # | 动作 | 验证 |
|---|---|---|
| P0-1 | `tests/e2e/test_smoke.py`：`return True/False` ⇒ `assert`；`MIN_S2` 改真实值 + 注明需手动核对 | 故意把 MIN_S2 设 9999 必须 FAIL |
| P0-2 | `pipeline/cli.py` `cmd_compile` 末尾传播 ninja 退出码 | 注入语法错误后 `echo $?` 非 0 |
| P0-3 | `hooks.json` / `gate_commit.sh` / `gate_annotations.sh` / `aide.toml`：死路径 `pipeline/data/annotations/` ⇒ `data/annotations/`；`chmod +x` 两个 .sh | `touch`+`git add` 后跑 gate 能触发 `check` |
| P0-4 | 同上（aide.toml 同款死路径一并修） | `grep -rn "pipeline/data/annotations" .` 归零 |
| P0-5 | `tools/_land_sizes.py` 的 `git checkout --` ⇒ **仅报告 + 非零退出** | 构造未提交修改，确认文件未被自动改动 |

## P1 进度

### P1-5 第九批（第 18 轮，**收尾**）：`emit_headers.py` 最后 3 处 ⇒ **P1-5 完成**
- `sdk_types.json`(:157)：只把**路径**收敛到 `_annview.annotation_json_path('sdk_types.json')`，
  **精确 try 保持原样**（`except (OSError, json.JSONDecodeError, TypeError)`）。
  为什么不换成 `load_annotation_json`：后者是**宽捕获 + 返回 None**，会改变语义 ✗
  ⇒ 为此**新增路径原语** `annotation_json_path()`，让"需要自己保留精确容错"的调用点也能收敛路径 ✓
- `structs/*.json` 全量 glob(:726)：`_ann_dir.glob("*.json")` + per-file `try/except: continue`
  ⇒ `_annview.iter_structs(directory=...)`（**同样排序 + 同样静默跳过**）✓（循环体只用 `_ad`，`_jf` 未使用 ⇒ 类型变化无影响 ✓）
- `globals.json`(:2911)：路径收敛到 `annotation_json_path('globals.json')`，**保留"此处无 try ⇒ 出错即抛"的原语义** ✓
  并顺手清掉原先的局部别名 `import json as _ann_json` ✗

**验证**：`codegen headers`（739 个 .h 重生成）⇒ **0 条 OVERLAY-DIAG**、EXIT=0 ✓
⇒ `diff -rq` 与快照 **非 globals 差异 = 0** ✓ ⇒ **字节中性** ✓

## 🏁 P1-5 完成（本轮里程碑）
**18 处已迁移**：`stage4_substitution` 1 · `collect` 1 · **`data.py` 5（全部）** · `ast_transform` 1 ·
**`emit_headers.py` 10（全部）**；另有 **1 处**（`_sig_evidence_pack.json`）经**边界裁定排除**
（`data/status/` 状态产物、非注解）✓
**⇒ 所有 codegen 侧的注解直读都已收敛到 `pipeline/gen/annotation_view.py`**，
且**每一处都过了"逻辑/路径等价 + 产物字节 diff"两道验证** ✓
**副产物**：定位并修复了一个**静默吞掉 635 个类"覆盖整体失效"的 `except: pass`**（改为出声）✓
**⇒ P1 全部完成**（P1-1/2/3/4/5/6）；目标剩余只有 **P2-1 的传递死链裁决**。


### P1-5 第八批（第 17 轮）：`emit_headers.py` 的 4 处 per-class 读取 + **一个真实潜伏缺陷的定位与修复**
**迁移**：`:975 known_members overlay` / `:1375 base_class` / `:1616 known_methods` / `:2234 operators`
四处原先各自 `PROJECT_ROOT/"data"/"annotations"/"structs"/("<cls>.json")` + `.exists()` +
`read_text(utf-8)` + `json.loads` ⇒ 统一到 `_annview.struct_by_class(cls)`（exists 由原语内部处理，
**保留各处自己的 try 容错**）。同批把第七批遗留的 **3 处函数内 `import annotation_view as _av`
去掉**（改用模块级别名）✓

**⚠️ 过程中撞上一个真实潜伏缺陷（已定位 + 已修）**：
- 现象：迁移后 **195 个非 globals 头文件产物变化**（`char X[29028]` ⇒ `_BYTE X[18740]` + `m_nTodo_*` + `_gap_*`）
  ⇒ **注解的 `known_members` 覆盖整体失效** ✗
- 隔离：回退 4 处 ⇒ 产物**恢复逐字节一致**（证确定性）；只应用 `:975` ⇒ 195 个差异复现 ⇒ **罪魁锁定** ✓
- **定位手段**：把 `:975` 处外层的 `except Exception: pass` 临时改成**出声** ⇒ 一次跑出 **635 条**
  `UnboundLocalError: local variable '_av' referenced before assignment` ✓✓
- **根因**：**第七批**在 `generate_header` **函数体内**插入了 `import annotation_view as _av`
  ⇒ `_av` 因此成为**该函数的局部名** ⇒ **第八批**的模块级别名 `_av` 被遮蔽，而 `:975` 位于那些
  局部 import **之前** ⇒ 引用即 `UnboundLocalError` ⇒ 被 `except Exception: pass` **静默吞掉** ✓
  **教训：① 别名 `_av` 太短、与函数内 import 冲突（我的错）；② `except: pass` 把整体失效藏了 635 个类。**
- **修复**：别名改为 **`_annview`**；去掉 3 处函数内 import；**并把该 `except` 永久改为出声**
  （这是**独立于本次迁移的健壮性改进**：今后任何该类异常都会显式报出，不再静默降级）✓
**验证**：`codegen headers`（全部 739 个头重新生成）⇒ 诊断输出 **0 条 OVERLAY-DIAG**（不再抛错）✓
⇒ `diff -rq` 与快照 **非 globals 差异 = 0** ✓、`codegen headers` EXIT=0 ✓ ⇒ **迁移字节中性** ✓
**P1-5 累计 15 处**（stage4 1 · collect 1 · data.py 5 · ast_transform 1 · emit_headers **7**）。
**`emit_headers.py` 剩余 3 处**：`sdk_types.json`(:157)、`structs/*.json` 全量 glob(:726)、`globals.json`(:2911)。


### P1-5 第七批（第 16 轮）：`emit_headers.py` 的 **3 处 `template_bases.json` 归并**
`emit_headers.py` 的 10 处直读中，**:1098 / :1311 / :2427 读的是同一个 `template_bases.json`**
（两处结构逐字相同，第三处仅缩进不同）⇒ 本次归并为一个**带缓存**的读点。
- `annotation_view` 新增 `template_bases()` / `template_bases_path()`；**语义严格保持**：
  同样先 `exists` 守卫、**同样不捕获异常**（文件缺失/损坏时**抛出**，与原 `if exists: open/json.load`
  一致 —— 原代码没有 try 包裹）；且与原代码一致**不指定 encoding**（逐字行为）。
- 三处各自的**转换逻辑原样保留**（`_template_map` / `template_map` / `_template_concrete` 各取所需）。
**验证**：快照 945 ⇒ `codegen all --skip-probe`（**EXIT=0**）⇒ `diff -rq` 差异仅
`globals.cpp`/`globals.h`（已知非确定、排序多重集相同）⇒ **非 globals 差异 = 0**、945=945 ⇒ **字节中性** ✓
**P1-5 累计 11 处**（stage4 1 · collect 1 · data.py 5 · ast_transform 1 · emit_headers 3）。
**`emit_headers.py` 剩余 7 处**：`sdk_types.json`(:157)、`structs/*.json` 全量 glob(:726)、
**4 处 `structs/<cls>.json`**(:975/:1375/:1616/:2234)、`globals.json`(:2911)。


### P1-5 第六批（第 15 轮）：`ast_transform.py` —— 1 处迁移 + **1 处边界裁定排除**
- **迁移**：`_load_ret_slots()` 的**路径枚举** `sorted(os.listdir(_structs_dir))` + `endswith('.json')`
  ⇒ `annotation_view.iter_struct_files(_structs_dir)` ✓（等价）；**保留本处的容错策略**
  （坏文件打印 **WARN** 再 continue —— 不是静默跳过），符合 annotation_view
  "细粒度原语 + 调用方保留容错"的设计原则 ✓
- **排除（边界裁定）**：同文件的 `_sig_evidence_pack.json`（`data/status/` 的**状态产物**，
  **不是注解**）**不纳入 P1-5 的"注解直读收敛"范围**（annotation_view 只管 `data/annotations/**`）；
  且其 typed except 已被前人记为**有意保留**（C3b：冗余但非缺陷，实测 335/335 键已在 byte-scan
  表中、0 处冲突 ⇒ 损坏 pack 不改变判定）。**已就地写注释，避免后人重复讨论。**
**验证**：快照 945 ⇒ `codegen all --skip-probe`（**EXIT=0**）⇒ `diff -rq` 差异仅
`globals.cpp`/`globals.h`（已知非确定、排序多重集相同）⇒ **非 globals 差异 = 0**、945=945 ⇒ **字节中性** ✓
**P1-5 累计 8/19**（口径：19 处 = 原审计点名的直读点；`_sig_evidence_pack` 一处经裁定不计入 ⇒ 实际待迁 11 处）。
剩余：**`emit_headers.py` 10 处**（最重）+ `data.py`? no（已全收敛）。


### P1-5 第五批（第 14 轮）：`data.py` 的 vtables + `functions.json`（两处一起）→ **data.py 全部收敛**
- `_load_vtables()`：`.exists()` 守卫 + `sorted(glob)` + 逐文件 `json.load`（坏文件 continue）
  ⇒ 改调 **`annotation_view.iter_structs(directory=...)`**（缺失目录返回空、同样排序与跳过）✓
- `functions.json` 补录：`project_root/"data"/"annotations"/"functions.json"` ⇒ 改调
  **`annotation_view.load_annotation_json('functions.json', store=self)`**（读不出 None ⇒ falsy，
  与 `except: {}` 同效）✓
**验证**：快照 945 ⇒ `codegen all --skip-probe`（**EXIT=0**）⇒ `diff -rq` 差异仅
`globals.cpp`/`globals.h`（已知非确定、排序多重集相同）⇒ **非 globals 差异 = 0**、945=945 ⇒ **字节中性** ✓

**里程碑**：`data.py` 原先直读 5 处（skip_functions / structs / globals / vtables / functions）
**已全部经 `annotation_view`** —— 它自述的"the ONLY place codegen reads from annotations"
现在**名实相符**（`pipeline/gen/annotation_view.py`）✓
**P1-5 累计 7/19**。剩余：`ast_transform.py`(2) + `emit_headers.py`(10) = **12 处**。


### P1-5 第四批（第 13 轮）：`data.py` 的 structs 遍历 + `globals.json`（两处一起）
- `_load_struct_bases()`：`sorted(annotations_dir/"structs".glob("*.json"))` + 逐文件 `json.load`
  （坏文件静默 continue）+ 名字回退 `_f.stem` ⇒ 改调 **`annotation_view.iter_structs(directory=...,)`**
  （同样"排序 + 坏文件跳过"，路径 basename 去 `.json` 得同 stem）✓
- `_load_annotated_globals()`：`project_root/"data"/"annotations"/"globals.json"` ⇒ 改调
  **`annotation_view.load_annotation_json('globals.json', store=self)`**（读不出返回 None，
  与原 `except: return` 同效）✓
**验证**：快照 945 文件 ⇒ `codegen all --skip-probe`（**EXIT=0**，含 lint/compile_regression 通过）
⇒ `diff -rq` 差异**仅 globals.cpp + globals.h**（已知非确定、排序行多重集相同）⇒
**非 globals 差异 = 0**、文件数 945=945 ⇒ **字节中性** ✓
**P1-5 累计 5/19**（stage4 成员名 · collect skip · data.py thunks · data.py structs · data.py globals）。
剩余：`data.py` 的 vtables(`:240`)/functions(`:433`)、`ast_transform.py`(2)、`emit_headers.py`(10)。

- [x] **P1-1** 两条硬线注入式负例测试 ✓✓ **两条都真跑并验证通过**
      · `tests/e2e/test_probe_baseline_injection.py`：注入 ok→fail ⇒
        `regression_detector --check` **退出码非 0** ✓ 且 `baselines/latest.json`
        **逐字节未变** ✓（"不得刷新基线"成立）。设计适配：`probe all` 会**重生成** census，
        故注入打在 census 文件上、直接测 `cmd_probe` 判定所用的那一步（已注明）。
      · `tests/e2e/test_l1_ratchet_injection.py`：注入 `s4_baseline.match_L1=35` ⇒
        真跑 `pipeline/cli.py match` ⇒ **退出码非 0**（棘轮报警）✓ 且基线被**写回注入值**
        （证明"退化时写回旧基线"，棘轮不会失忆）✓；`finally` 还原后实测 `match_L1=34` ✓。
        耗时约 5 分钟（e2e 固有成本），用 `PAL3_E2E_INJECTION=1` 开启以免拖慢日常套件。
- [x] **P1-6** 两个回归门禁职责分工写入 `compile_regression.py` / `regression_detector.py`
      docstring + `CLAUDE.md`（含"检查点表缺 `probe` 一步"的明示）✓
- [x] **P1-3** `audit_layout` 的 `1b declared-size geometry` 从"仅打印"提升为**影响退出码** ✓
      加 `--strict-geometry`（**默认关**）+ 阈值可环境覆盖（`PAL3_GEOMETRY_WARN_RATIO` /
      `PAL3_GEOMETRY_HIGH_RATIO`，后者是**为了能被注入式验证**）。
      验证：A 默认 ⇒ exit 0（行为不变，38 warnings）；B 注入 `HIGH=1.0`+strict ⇒ **exit 1** ✓
      （门禁可被触发）；C strict+默认阈值 ⇒ **exit 1**（**14 个结构体 >50x**，这是真实发现）。
      **新落地清单**：`data/status/_geometry_strict_report.json`（HIGH 14 个 / warn 38 个），
      例：`CCBProtectWindow`(size 与成员几何严重不符)、`CEffQuake`、`CONTEXT`、
      `CTaskTpl_tagEffTaskParam_CEff*` —— 与审计 §4 的"尺寸判据"发现互相印证
      （我此前的 `_structural_contradictions` 也记过 `CCBProtectWindow 176→2632`）。
      这批需**按二进制证据**修正尺寸或成员，属**独立 backlog**（不在本目标的 P0/P1 范围内）。
- [x] **P1-2** `codegen all` 钩子**先跑 `probe s2`**（默认开）+ `--skip-probe` 逃生 ✓
      插入位置（代码行号确认）：**PROBE(L428) → SNAPSHOT(L455) → LINT(L474) → REGRESSION(L484)**
      —— 让 `snapshot` 与 `compile_regression` 看**本次** codegen 的 census（此前它们看的是
      "上一次不知何时跑的 probe 快照"）。
      成本实测：`probe s2` **21 秒**（206 单元）⇒ 可接受，故默认开启。
      验证：真跑 `codegen all` ⇒ 日志出现 `[Probe] Running probe s2 …`，并因**检出已知回归**
      （`UISystem.cpp`/`sub_421870`）而**中断 exit 1** ✓（退出码已传播 ⇒ `&&` 链断开）。
      注：日志里 snapshot 的输出**早于** probe 是父子进程 stdout **缓冲交错**的假象，
      以**代码顺序**为准（已用 AST/行号核对）。
      顺手修了自己引入的 `%d` 未插值 bug。
- [ ]
      **P1-4** 复核 `export_full.py` 的 8 处 `[t4-DECLARED-EXCEPTION]` + 一致性校验 ✓
      复核结论：这 8 处是"高质量的已声明例外"，**不该删到合规**（头部声明块给出：IDB 无等价
      可查询形式 / 承重且量化：1955 skip 地址与 3594 导出交集=0、475 virtual→442 签名前缀、
      3276 mangled 名、686 struct 的 8979 条 _variants、1816 _skip_function_names / 
      vtables+methods 与注解逐字段等值）。
      新工具 `tools/check_export_annotation_consistency.py` 补上缺失的告警，判据只用
      `vtables`+`methods`；`_variants` **仅提示**（两侧表示不同，比键会产出 742 个假阳性 ——
      我第一版之错，已降级）。已**接入 `cmd_export` 尾部**（只读、无需 IDA、报警不阻断）。
      验证：A 现状 exit 0（0 不一致 ⇒ 独立印证 export_full 自述的 761/761）；B 注入一处
      methods 名 ⇒ exit 1 + ❌ ✓；C 还原后 exit 0 ✓。
· **P1-5**（直读收敛）

## P1 结构（P0 后）
P1-1 两条硬线注入式负例测试（L1 棘轮 / probe 不得刷新基线，均 `finally` 还原）
P1-2 `cmd_codegen` 钩子插入 `probe_compile`（+`--skip-probe`）
P1-3 `audit_layout` 的 `1b` 几何判据提升为影响退出码（+`--strict-geometry` 默认关）
P1-4 复核 `export_full.py` 8 处 `[t4-DECLARED-EXCEPTION]` + 加"注解 vs IDB"一致性校验
P1-5 直读收敛到 `pipeline/gen/annotation_view.py`（验证：`codegen all` 产物 `diff -r` 字节相同）
P1-6 两个回归门禁职责分工写入 docstring + CLAUDE.md

## P2 清理（滚动）

### P2-1 整链归档（第 19 轮）+ 死哨兵清理 ⇒ **目标全部项完成**
**① P2-1 传递死链裁决（整链一次动）**：先画引用链 ⇒ 父件 `ida_master_pipeline.py` 与
`run_pipeline.bat`、以及 7 个子件的引用者**只有** `docs/superpowers/2026-05-0*`（**历史规划文档**，
描述早已被取代的 PAL3A/IDA 阶段）+ 本审计自己的 status 文档（作为候选提及）+ 链内互引
（`pal3_strict_match.py` → `pal3a_dump_func_bytes`）。
⇒ 判定**整链已死**，用 `git mv` 归档 **9 个文件**（父件 + `.bat` + 7 子件，其中含
`pal3_strict_match.py`）：`ida_master_pipeline.py` / `run_pipeline.bat` / `ida_export_globals.py` /
`ida_fix_boundaries.py` / `ida_import_pdb_types.py` / `ida_verify_and_export.py` /
`pal3_import_structs.py` / `pal3a_dump_func_bytes.py` / `pal3_strict_match.py`（**不删**，历史保留 ✓）。
验证：活跃代码（`tools/*.py` + `pipeline/**`）对这些文件**零引用**（`apply_annotation_batch.py` 的
`args.run_pipeline` 是它**自己的开关**，已核对同名子串 ✓）；`check` PASS；`tool --list` 正常；
`.bat` 零活跃引用 ✓。

**② 死哨兵清理（`emit_headers.py` 原 `load_annotations_data()`）**：全仓 grep 证明它**从未被调用**
⇒ 一道**永远不会触发的假防护**，且其宣称的"codegen 绝对禁止读 annotation"**与事实相反**（10 处已声明例外）。
⇒ 换为**可检查的诚实规则**：codegen 侧读注解**必须经单一读点 `pipeline/gen/annotation_view.py`**
（10 处已全部收敛并逐处验证字节不变）✓ 并**同步 `CLAUDE.md`** 的设计原则措辞（"绝对禁止" ⇒
"必须经单一读点"，并写明已声明例外的出处）✓
验证：`check` PASS、`codegen headers` EXIT=0、**0 条 OVERLAY-DIAG** ✓

P2-1 归档失效脚本（先 `grep -rln` 确认零文档引用，移 `tools/archive/`）
P2-2 `requirements.txt` 补 `capstone`（先复现 ImportError）
P2-3 424MB Ghidra zip（**需用户明确同意**，不自行重写历史）
P2-4 给 4 个"无 argparse 且写盘"的审计工具补 argparse

## 进度
- [x] **P0-1** `test_smoke.py` 改 assert ✓（`MIN_S2` 改读**编译基线**=68，棘轮语义）
      验证：`python3 tests/e2e/test_smoke.py` → 3 passed / **1 failed**；
      注入 `PAL3_MIN_S2=9999` → `❌ probe_compile: S2 75/206 < 下限 9999` ✓ **门禁已复活**。
      ⚠️ **那 1 failed 是真实回归、不是测试 bug**：`compile_regression` 退出码非 0，
      对应既存未修回归 `UISystem.cpp`/`sub_421870`（根因=调用点两处可疑注解，§50.4 已诊断）。
      **本用例保持红色**——它现在如实反映一个已诊断未修的问题，属"门禁复活"的证据。
- [x] **P0-2** `cmd_compile` 末尾传播 ninja 退出码 ✓
      验证：AST 检查 `cmd_compile` 最后一条语句 = `sys.exit(0 if result.returncode == 0 else 1)`。
      （未做全量 ninja 真跑验证：耗时长，留待需要时补）
- [x] **P0-3/4** 死路径 `pipeline/data/annotations/` ⇒ `data/annotations/` ✓
      共 8 处：`hooks.json`(2) + `aide.toml`(4) + `scripts/gate_commit.sh`(1) + `scripts/gate_readonly.sh`(1)；
      并把 7 个 `scripts/*.sh` 全部 `chmod +x`（原先 3 个是 664 不可执行）。
      验证：`grep -rn "pipeline/data/annotations" --include=*.json --include=*.toml --include=*.sh` 仅剩
      `data/status/*.json`（审计记录本身）⇒ **无活门禁路径**。
      **附带发现**：`data/status/_cleanup_scan_triage.json:5766` 记录 `globals.h` 头部注释也写着
      过期的 `pipeline/data/annotations/globals.json` ⇒ 生成物里的路径字面量陈旧，归入 P1/P2。
- [x] **P0-5** `tools/_land_sizes.py` 不再自动 `git checkout --` ✓（改为打印 `[REVERT-NEEDED]` + 收集清单）
      验证：`grep -n "git', 'checkout'" tools/_land_sizes.py` → 已移除 ✓
- [ ] P1-1 … P1-6
- [ ] P2-1 … P2-4

## P2-4 执行记录（2026-09-20，第 5 轮）
**问题**：本仓多个**会写盘**的工具**没有参数解析**（或只识别个别开关、**对未知开关一律忽略**）⇒
`--help` 会被当作普通输入并**执行全流程、覆盖产物**。本次审计期间已因此发生 **2 起事故**。

**做法**：给 **16 个**"会写盘且完全无 argv 处理"的工具统一插入护栏：
见到任何 `-` 开头的参数即打印用法并 **exit 0，不执行任何工作**。
文件清单见 commit；护栏文本统一带 `_sys_guard` 标记（可 grep 复查）。

**验证（产物哈希，`--help` 前后必须不变）**：
| 工具 | exit | 产物变化 |
|---|---|---|
| `alloc_sizeof.py` | 0 | **无** ✓ |
| `audit_signature_consistency.py` | 0 | **无** ✓ |
| `byte_diff_explain.py` | 0 | **无** ✓ |
| `misattribution_ledger.py`（**审计事故工具**）| 0 | **无** ✓（修复后）|
| `audit_retn_param_count.py` | 1 | 无（它 `import idc`，IDA 外本就跑不了 ⇒ 非回归）|

**额外发现并修复**：`tools/misattribution_ledger.py` **不在**上述 16 个里 —— 它有**部分**
`sys.argv` 处理（`:37` 的 `--min-sites`）却**忽略未知开关**，于是 `--help` 仍会执行并覆盖
受跟踪的 `data/status/misattribution_ledger.json`（本轮实测哈希 `e90498be→4a1412d2`）。
⇒ 已给它加**严格拒绝未知开关**的护栏，并用**合规方式**（`git show HEAD:<path> > <path>`，
**非** `git checkout`）还原文件（还原后 md5 = HEAD ✓）。
**教训：判据"完全无 argv"太窄；真正的危险类是"无严格开关校验"。**

**残留清单**（已存档 `data/status/_tools_argparse_hazard.json`）：仍有若干工具满足
"会写盘 且 无 argparse 且 无严格护栏"，其中 `uses_argv=True` 的那些与 `misattribution_ledger.py`
同型（会忽略未知开关），应在后续轮次按同一护栏修掉。

## P2-4 残留（第 6 轮，已完成）
给 4 个"会写盘但**忽略未知开关**"的同型工具加**严格拒绝未知开关**护栏：
`sig_evidence.py`（**审计事故工具**）、`apply_vtable_fix.py`、`fix_all_vtables.py`、`fix_vtable_splits.py`。
验证（`--help` 前后产物哈希）：三者 exit0 且**产物无变化** ✓；`sig_evidence.py`
`--help` ⇒ exit0 + 产物不变 ✓，且**无参调用仍正常**（exit0，会按设计重写 pack）✓。

**过程中我犯的错（记录）**：第一版补丁按 4 空格缩进插入，但 `sig_evidence.py` 的锚点是
**模块级 `if __name__ == '__main__':` 内的 4 空格 `if`** —— 插入后 `IndentationError:351`
把文件**改坏**。已 `git show HEAD:` 还原后，**按锚点实际缩进重插**并验证语法+行为 ✓。
**教训：给已有文件插代码必须指定与锚点一致的缩进，且插入后必须跑 `py_compile`。**

## P2-2（第 6 轮，已完成）
`capstone` 未安装已在 `byte_diff_explain.py:38` / `check_member_offsets.py:30` 复现
`ModuleNotFoundError` ⇒ 已补入 `requirements.txt`（`capstone>=5.0.0` + 理由注释）。
**安装仍需操作者执行 `pip install -r requirements.txt`**（本环境未联网安装）。

## 🆕 新发现（第 6 轮，登记为 **P2-5**，未修）
**`tools/sig_evidence.py` 的默认（无参）运行会把受跟踪产物 `data/status/_sig_evidence_pack.json`
从 6931 行砍到 1648 行（丢 76%）** —— 实测（本轮验证时无意触发，已 `git show` 还原，md5==HEAD）。
这与审计观察到的"该 pack 被重写成 363→30 含 slots"一致，也印证工具自述的
"**54 条 A-V2 是现行评分函数产不出的更高等级（别的版本写入）**"⇒ **当前工具无法忠实重建该产物**。
**已修（P2-5，第 7 轮）**：加**棘轮护栏** —— 新 pack 的 `graded` 条目 < 现有 × 0.9 时
**拒绝覆盖并 exit 1**；确要覆盖须显式 `--force-overwrite`（同时加入已知开关白名单）。
**量化**：默认运行只产出 **144 条** graded，而现有 **456 条** ⇒ 原本会**丢 312 条（68%）**。
验证：A 默认运行 ⇒ **exit 1** + `[RATCHET] 拒绝覆盖 …144 明显少于 456` 且 **pack 未变**（md5 比对）✓；
B `--force-overwrite` ⇒ exit 0、允许覆盖（graded=144）✓；随后 `git show HEAD:` 还原，md5==HEAD ✓。

## P2-1 归档（第 8 轮，第一批 9 个）
**判据（严格三重）**：① 引用已不存在的 `asm/pal3a/` 或硬编码作者机 `D:\workspace`；
② **零文档/知识库/status/CLAUDE.md 引用**（`grep -rl <basename>`）；③ **不被任何其它 .py import**。
只有三条全过才移动，且用 `git mv`（**不删**）。

**已归档 9 个 → `tools/archive/`**：
`dia_export_bases.py`、`dia_export_structs.py`、`ghidra/export_known_functions.py`、
`ida/manual_decompile.py`、`ida/pal3_apply_globals.py`、`ida/pal3_import_types.py`、
`ida_class_cluster_match.py`、`ida_enhanced_order_match.py`、`pal3_strict_match_local.py`。

**验证**：① 归档后**无任何 .py 再 import 这些模块**（逐个 grep，无输出=✓）；
② `pipeline/cli.py check` PASS；③ `tool --list` 正常且被归档脚本**不再出现在清单**（grep 计数 0）；
④ 活跃工具 `check_export_annotation_consistency.py` 仍 exit 0 ✓。

**暂不动 7 个**（被 `tools/ida/ida_master_pipeline.py` import，或文档引用）：
`ghidra/export_functions.py`、`ida/ida_export_globals.py`、`ida/ida_fix_boundaries.py`、
`ida/ida_import_pdb_types.py`、`ida/ida_verify_and_export.py`、`ida/pal3_import_structs.py`、
`ida/pal3a_dump_func_bytes.py`。
⇒ 这 7 个属**传递死链**（`ida_master_pipeline.py` 自身仅被一个 Windows `.bat` 引用），
需要一整条链的决策 + 文档更新，**留待后续轮次**（不做单点移动，避免"搬了子件、父件成孤儿"）。
**审计估的"约 137 个"中，多数属此类传递死链，需逐链裁决，不是简单删除。**

## P2-3（第 9 轮，只读分析 + 一处卫生修正）
**结论：不需要任何 git 历史重写。** 事实：`tools/ghidra/ghidra_11.2.1_PUBLIC_20241105.zip`（**406M**）
与解压目录 `ghidra_11.2.1_PUBLIC/`（**643M**）**都不被 git 跟踪**（`git ls-files` 均为 0），
且 `.gitignore` 早有 `tools/ghidra/` 规则（在它们加入**之前**就存在）。⇒ 它们从未进历史。

**唯一的不一致（已修）**：原规则忽略**整个** `tools/ghidra/`，但该目录下有 **7 个项目脚本
已被跟踪**（`load_pdb.py`/`export_*.py`/`run_headless_export.bat`/`README.md` 等，规则加入前就跟踪了）
⇒ 形成"被跟踪文件落在被忽略路径"。已把规则收窄为 `tools/ghidra/ghidra_11.2.1_PUBLIC*`
（**不带尾斜杠**，同时匹配 zip 与解压目录 —— 第一版带 `*/` 只匹配目录、漏了 zip，已修正）。
验证：vendor 目录与 zip 均被忽略 ✓；`load_pdb.py` **未被忽略** ✓；`git ls-files tools/ghidra` 仍为 **7** ✓。

**本地磁盘**：这两个载荷合计约 **1.05GB**；因未跟踪，**删除它们对 git 无任何影响**
（仅影响本机是否保留 Ghidra 路线）。是否删除由操作者按需决定。

## P1-5 第一批（第 10 轮）：直读收敛的**单一读点** + 一处迁移（字节验证通过）
**做法**：新建 `pipeline/gen/annotation_view.py` 作为注解的**单一读取视图**
（`structs_dir` / `iter_struct_files` / `load_struct` / `iter_structs` / `member_names`）。
**设计原则**：不改"读不读"这个既成事实，只把散落直读**收敛到一个读点**；
提供**细粒度原语**、由调用方保留自己的容错语义（**不做会改行为的"统一容错"合并**）。

**第一处迁移**：`pipeline/gen/stages/stage4_substitution.py` 的 `_load_member_names()`
（原先自己 glob `store.annotations_dir/structs/*.json`）⇒ 改调 `annotation_view.member_names(store=store)`。

**验证（两层）**：
1. **逻辑等价**：旧逻辑集合 **7001** 个成员名 == 新逻辑 **7001** 个，差集为空 ✓
2. **产物字节**（权威）：先 `cp -r pal3/src /tmp/src_before_p15` 快照 945 个文件 ⇒
   迁移后 `codegen all --skip-probe` ⇒ `diff -rq`：**差异恰为 2 条 = `globals.cpp` + `globals.h`**
   （**已知非确定**的那对，其**排序行多重集相同**）⇒ **非 globals 差异 = 0**，文件数 945=945 ✓
   ⇒ **本次迁移字节中性**。

**过程中的自我纠错**：第一次做 `diff` 时看到 84 处"快照有、新产物没有"，差点误判为回退 ——
查日志发现 **codegen 当时仍在写盘**（无 `EXIT=`、无钩子行），是**半成品目录**造成的假象。
**教训：验证必须确认被验对象已完成，否则 diff 结论无效。** 等其完成后重测即通过。

**后续（P1-5 剩余）**：`emit_headers.py`（10 处）、`ast_transform.py`、`collect.py`、`data.py`
的其余直读点，按**同样流程逐处迁移**（每处都过"逻辑等价 + `diff -r` 字节"两道验证）。

## P1-5 第二批（第 11 轮）：`collect.py` 的 `skip_functions.json` 读取收敛
**新增原语**：`annotation_view.load_annotation_json(name, store)` 与 `annotation_view.skip_functions(store)`
（"顶层注解 JSON"的单一读点；structs/*.json 走已有的 `iter_structs`）。
**迁移**：`pipeline/gen/stages/collect.py::_get_skip_classes()` 原先自读
`store.annotations_dir/"skip_functions.json"` ⇒ 改调 `annotation_view.skip_functions(store=store)`。

**验证（两层）**：
1. **逻辑等价**：skip 集合 **124** 个、md5 `d77ffcf353` ⇒ 迁移前后**逐元素相同** ✓
2. **产物字节**（权威）：快照 945 文件 ⇒ `codegen all --skip-probe` ⇒ `diff -rq` 差异
   **恰为 2 条 = globals.cpp + globals.h**（已知非确定、排序多重集相同）⇒ **非 globals 差异 = 0**、
   文件数 945=945 ✓

**累计**：P1-5 已迁 2 处（`stage4._load_member_names`、`collect._get_skip_classes`），
两处都过"逻辑等价 + 字节 diff"两道验证。**剩余**：`data.py`（5 处）、`ast_transform.py`（2 处）、
`emit_headers.py`（10 处）—— 按同一流程逐处迁移。


## 目标外续作（用户指派）：`Scene` / `Role` 布局修正（**一批一管线**）
**通胀链的根**：`Role.binary_size` 虚高（8928）⇒ `Scene.m_npc: Role[72]` 末端虚高到 1,099,748
⇒ `Scene.binary_size` 被抬到 1100000 ✗。而构造函数证明的真实布局自洽于 **0x78664 = 493156**。
**本批（一次 apply→export→codegen→probe→match）**：
1. **`Role`: 8928 → 8704**（A 级：ctor `??_L(esi+0E0E4h, 0x2200, 0x32, sub_411900=Role, …)`
   的**元素尺寸字面量 0x2200**；旁证：`Role` 末成员 0x21f4=8692 与 8704 相容、与 8928 不相容）
2. **`Scene`: 1100000 → 493156**（三重 A 级：ctor 的三个字面量 `push 3/00078664h/00C21FE8h`；
   BSS 跨度 493156×3 整除；getter 移位链算术）
3. **移除 3 个无据/冲突成员**：`+0xE0 m_obj: SceneObj[256]`（与 ctor 的 **64×896** 冲突 ✗）、
   `+0x6f8e0 m_numnpc`、`+0x6f8e4 m_npc: Role[72]`（二者**落在** ctor 的 `Role[50]` 区间
   `[0xE0E4,0x784E4)` **之内** ✗）
4. **新增 8 个指令级证据成员**：`+0xE0 m_roleSlots: tagRoleSlot[64]`（896 字节唯一匹配）、
   `+0xE0E0`、`+0xE0E4 m_roles: Role[50]`、`+0x78650/54/58`、`+0x7865C(BYTE)`、`+0x78660`
**自检**：成员末端 = **493156**，与 `binary_size` **恰好相等** ✓（布局完全自洽）
**判据（注解修正用"无退化"而非"字节不变"）**：`probe all` **EXIT=0**、**新失败 0**、
**总错误 2150 未增**、**L1 34→34 未回退**、`match` EXIT=0、partial **198→200** ✓
**我自己的失误（已修）**：新增成员时**手算 hex→decimal 算错**（`0xE0E4` 写成 923876 ✗）
⇒ 末端冲到 1,359,078 被 `check` 抓住 ⇒ 改为**用代码换算**（从此不再手算）✓
**遗留（未做）**：offset0 `_vftable`（挡住 getter 用 `Scene*` 正确类型；且 ctor 不装 vptr ⇒ 该成员**很可能无据**）；
`Role` 的 ctor/dtor 对里 `sub_411CA0` 被注成 `~PalScript` ✗、`+0xE0` 元素的 ctor `sub_4236D0` 被注成
`BINK::Reset` ✗（归属存疑）；`+0x784E4` 子对象类型未知 ⇒ 未注解。


## 目标外续作 2：修复 **include 依赖分析缺口**（用户选 A）
**背景**：上一批把 getter 返回类型改成正确的 `Scene*` 后，`UIAnimateCtrlEX.cpp` 多出 2 个错误
（`C2027 use of undefined type 'Scene'` + `C2227 left of '->m_roles' ...`）。归因显示：该 .cpp 的
include 列表**没有 `Scene.h`** ⇒ 返回类型是 `Scene*` 时，`->m_roles` 需要**完整定义** ✗。
**根因**：`pipeline/gen/stages/emit_cpp.py::_detect_needed_includes()` 原有 **4 条**启发式
（`X::` 静态调用 / `(X *)` 转换 / **类名字面量** / `globals.h` 前向声明解析）**都漏掉**
"**函数调用结果被解引用**"这一形态 —— 而 `Scene` 在该代码里**不出现字面量**（只出现
`UISceneUpdate()->m_roles`）✗
**修复（新增第 5 条启发式）**：对出现在本单元的**函数名**，若其形态是"调用后立即 `->`/`.`/`[`"，
则从 `store.free_func_sigs`/`method_sigs` 的**签名**解析返回类型，是已知类即 include 其头 ✓
（性能：先用**子串**预筛函数名，再做正则 ⇒ 每单元只跑几条 ✓）
**验证（同批一次管线 codegen→probe→match）**：
`UIAnimateCtrlEX.cpp:10` 出现 **`#include "Scene/Scene.h"`** ✓；**总错误 2152 → 2150** ✓
（那 2 个 C2027/C2227 消失，该单元 7→5 errors）；`probe all` **EXIT=0**；`新失败 0`；
**L1 previous 34 -> current 34** ✓；`match` EXIT=0 ✓
**⇒ 两全**：上一批的**正确注解**（`Scene*` + 移除幻影 `_vftable`）保留，且**总错误不再增加** ✓
**副产物**：这个缺口是**通用**的 —— 任何"`f()->member`"形态的单元此前都会漏 include ✓


## 目标外续作 3（第 20 轮）：**"类型不是类"家族（~500 条）的成因量化**（侦察，未改代码）
**动机**：include 缺口修好后，想找下一个"单点高收益"。`census` 里 `C2227`=226（47 单元）、
`C2027`=5 ⇒ 先在 `C2227/C2027/C2228/C2039` 上做构成分析（按出错行的 `->` 左侧标识符分类）。
**量化结果（总计 ~500 条）**：
| 成因族 | 条数 | 单元 | 性质 |
|---|---|---|---|
| `this->…`（本类成员类型为原始/未知）| **181** | 32 | **注解长尾** |
| 非 `->` 形态（如 `NtCurrentTeb()->NtTib.ExceptionList`）| **156** | 31 | **CRT/SDK 类型缺失** |
| 成员类型为原始/未知（`p_m_pButtonAI->ShowWindow`）| **48** | 12 | **注解**（CCB 窗口类成员，**有共性**）|
| `vftable->` 存根 | **32** | 17 | **深水区**（审计已知 `[VFTABLE-STUB]`=475）|
| 各种局部变量（`v9`/`i`/`v5`/`pNode`…）| ~90 | — | 多派生自存根调用点 |
**结论：该家族没有"单点快修"** ✗ —— 主体是注解长尾 + SDK 类型 + vtable 深水区。
**同时否掉了另一条候选**：`--strict-geometry` 的 14 个"几何超标"经查是**成员严重缺失**（10 个
`*_graph` 与 `CEffQuake`/`ConfigFile`/`tagRoleSlot` 都只有 **1 个成员在 +0**，尺寸本身可能是对的）
⇒ 属**长期注解工作**，不是同型快修 ✗
**⇒ 供选择的下一步（按 ROI）**：
1. **CCB 窗口类的 `p_m_p*` 成员（48 条 / 12 单元）**：形态高度重复（`p_m_pButtonAI`/`p_m_pBack`/
   `p_m_wndcolor` …），若能用**指令级访问证据**证明它们同属少数几个类（`UIStatic*`/`Caption*`…），
   可批量收敛 —— **需逐成员取证**，但**共性最强** ✓
2. **SDK/CRT 类型（156 条）**：`NtCurrentTeb()->NtTib.ExceptionList` 这类，若能在
   `sdk_types.json`/头里**一次性声明**，可一次消掉一片 ✓（需确认它们是否属"hexlimits 不修"范畴 ✗）
3. **`this->` 长尾（181 条）**：逐成员补类型，纯长尾 ✗
4. **vftable 深水区**：审计已定性为"不可从字节推导"，需 `vtable_class_reconcile` 路线 ✗
