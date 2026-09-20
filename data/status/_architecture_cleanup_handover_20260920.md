# 架构清理与修复 · 交接文档（2026-09-20）

**目标**：`goal-312d2835`（按 `_audit_repair_plan_20260920.md` 实施 P0→P1→P2，每项带验证）。
**结论：目标未完成，保持 active。** 14 项中 **12 项已交付并验证**（含 1 项部分），
剩余为**机械但量大**的工作，方法已固化。

**累计交付**：15 个提交（`8d6db0048..7e2601b78`），全部只改门禁/工具/文档/读取方式，
**未碰任何注解数据**；指标始终 **S2 75/206 ｜ 总错误 2151 ｜ L1 34**（未回退）。

---

## 一、已完成（每项都有注入式/哈希式/字节式验证）

### P0 止血（5/5）
| # | 内容 | 关键验证 |
|---|---|---|
| P0-1 | `tests/e2e/test_smoke.py`：`return` ⇒ **`assert`**；`MIN_S2` 改读**编译基线**（棘轮） | 注入 `PAL3_MIN_S2=9999` ⇒ **probe_compile 失败** ✓ |
| P0-2 | `cmd_compile` 末尾传播 ninja 退出码（原**恒 0**） | AST 确认末语句为 `sys.exit(0 if rc==0 else 1)` |
| P0-3/4 | 死路径 `pipeline/data/annotations/` ⇒ `data/annotations/` **8 处**；7 个 `.sh` **chmod +x** | 全仓 grep 归零 ✓ |
| P0-5 | `_land_sizes.py` 不再自动 `git checkout --`（改为仅报告） | grep 已无该命令 ✓ |

### P1 结构（6/6 有进展；P1-5 部分）
| # | 内容 | 关键验证 |
|---|---|---|
| P1-1 | **两条硬线的注入式负例**：L1 棘轮 / probe 不得刷新基线 | 真跑 `match`：注入 `match_L1=35` ⇒ **非零退出且基线被写回** ✓；census 注入 ok→fail ⇒ `regression_detector --check` **非零**且 `latest.json` **逐字节未变** ✓ |
| P1-2 | `codegen all` 钩子**先跑 `probe s2`**（默认开，`--skip-probe` 逃生；成本 21s） | 实跑出现 `[Probe]` 并在检出回归时 **exit 1** ✓ |
| P1-3 | `audit_layout` 的 IDB 无关几何判据升为**可影响退出码**（`--strict-geometry` 默认关，阈值可环境覆盖） | 注入 `HIGH=1.0`+strict ⇒ **exit 1** ✓；默认 ⇒ exit 0 ✓ |
| P1-4 | 复核 `export_full.py` 的 8 处 `[t4-DECLARED-EXCEPTION]`（**判定=合理，不删**）+ 新工具 `check_export_annotation_consistency.py` 接入 `export` 尾部 | 现状 exit 0（vtables/methods **0 不一致**，独立印证其自述 761/761）；**注入**一处 methods 名 ⇒ exit 1 ✓ |
| P1-6 | 两个回归门禁职责分工写入两个 docstring + `CLAUDE.md` | 并明示"检查点表缺 `probe` 一步" |
| **P1-5** | **直读收敛（部分：2/19 处）** | 见下 |

### P1-5 部分完成（2/19 处，方法已固化）
新建 `pipeline/gen/annotation_view.py`（注解的**单一读取视图**；细粒度原语，**保留各调用方容错语义**）。
已迁：`stage4_substitution._load_member_names()`、`collect._get_skip_classes()`。
**验证方法（每处都必须过两道）**：
1. **逻辑等价**（集合 md5 / 逐元素比较）；
2. **产物字节**：`cp -r pal3/src /tmp/before` ⇒ `codegen all --skip-probe` ⇒
   `diff -rq` 差异**必须恰为 `globals.cpp`+`globals.h`**（已知非确定，排序行多重集相同）
   且**文件数 945=945**；否则**回退该处**。
> ⚠️ **坑**：`diff` 前必须确认 codegen **已结束**（看日志有 `EXIT=`），否则半成品目录会给出
> 假差异（我第一轮就被骗过，84 处"假缺失"）。

### P2 清理（4/4 有进展）
| # | 内容 | 关键验证 |
|---|---|---|
| P2-1 | 归档第一批 **9 个**确认失效脚本（三重判据：引用不存在的 `asm/pal3a`/作者机路径 + 零文档引用 + 零 import）用 **`git mv` 不删** | 归档后无残留 import；`check` PASS；`tool --list` 中计数 0 ✓ |
| P2-2 | `requirements.txt` 补 `capstone`（**先复现** `ModuleNotFoundError`） | 复现输出 + 文件已含该依赖 |
| P2-3 | **确认无需历史重写**（406M zip 与 643M 目录**从未被跟踪**）；收窄 `.gitignore` 消除"被跟踪文件落在被忽略路径" | `check-ignore` vendor 目录/zip ✓、`load_pdb.py` 未被忽略 ✓、`git ls-files tools/ghidra` 仍 7 ✓ |
| P2-4 | 16 个"会写盘且无参数解析"工具 + 4 个"忽略未知开关"工具（含审计两起事故的工具）加**统一护栏** | `--help` 前后**产物哈希不变** ✓（逐个实测）|

### 我新发现并修复的缺陷（不在原审计里）
1. `tools/misattribution_ledger.py` **忽略未知开关** ⇒ `--help` 覆盖受跟踪产物（实测 197→3）⇒ **已修**；
2. **`tools/sig_evidence.py` 默认运行把 `_sig_evidence_pack.json` 从 6931 行砍到 1648 行**
   （graded **456→144，丢 68%**）⇒ 加**棘轮护栏**：新条目 < 旧 ×0.9 即拒绝覆盖，需 `--force-overwrite`；
3. `globals.h` 头部注释仍写**陈旧路径** `pipeline/data/annotations/globals.json`（triage:5766 已记）。

---

## 二、未完成（保持 active 的原因）

### ① P1-5 剩余 **17 处**直读（机械，方法已固化）
| 文件 | 处数 | 备注 |
|---|---|---|
| `pipeline/gen/stages/emit_headers.py` | **10** | sdk_types / known_methods / known_members overlay / template_bases×3 / base_class / operators / globals.json skip+name；**最重** |
| `pipeline/gen/data.py` | 5 | skip_functions / vtables / bases / globals.json / functions.json（**它自称"唯一读点"已不成立**）|
| `pipeline/gen/ast_transform.py` | 2 | `structs/*.json` 的 methods 表 + `_sig_evidence_pack.json` |

**注意事项**：`ast_transform.py` 里读的是 **`data/status/_sig_evidence_pack.json`（不是注解）**，
按 P1-5 的边界它属"status 产物"而非 annotation ⇒ 迁移前需先判定归属。
`emit_headers.py` 的 **10 处容错语义各不相同**，必须逐处保留（**不要**做统一容错合并）。

### ② P2-1 传递死链（需整链裁决，不能单点移动）
7 个脚本因被 `tools/ida/ida_master_pipeline.py` import 而暂缓；而该父件**自身只被一个
Windows `.bat` 引用**。⇒ 需要一次性裁决 `ida_master_pipeline.py` → 子件 → `.bat`/文档 整条链。
清单：`ghidra/export_functions.py`、`ida/ida_export_globals.py`、`ida/ida_fix_boundaries.py`、
`ida/ida_import_pdb_types.py`、`ida/ida_verify_and_export.py`、`ida/pal3_import_structs.py`、
`ida/pal3a_dump_func_bytes.py`。
> 审计估的"约 137 个应删/归档"**多数属此类传递死链**，是逐链裁决工作，不是简单删除。

### ③ 已知未修的实质缺陷（与本目标正交，但会影响门禁颜色）
| 项 | 说明 |
|---|---|
| **`sub_421870`（`UISystem.cpp`）** | 唯一未修回归，**使 P0-1 的 `test_smoke` 与 `codegen all` 正常路径保持红色**（P1-2 的直接后果=门禁如实变红）。根因在**调用点两处可疑注解**（`0xc21fe8` 被注成 `PalScriptMgr`(9512B)/`SceneMgr*`(58692B)，都与步长 `493156` 冲突）⇒ 需先定性那个 493156B 的对象 |
| `//4` 槽位假设 | 已证错但**仍在承重**（`stage3_cleanup.py:522`），仅在 `tests/test_vtbl_slot_index.py` 用 SKIP 固化 |
| **318 个成员以 PDB 为唯一 source** | 违反 `CLAUDE.md:73` 与 `_pdb_nonauthority_notice.json` |
| **14 个几何超标结构体** | `data/status/_geometry_strict_report.json`（HIGH>50x：10 个 `*_graph` 各 1325x、`CEffQuake`、`tagRoleSlot`、`st_Manager`、`ConfigFile`）—— 其中 10 个 `*_graph` 正是 PDB-sole-source 成员 |
| 审计的"D 组"问题 | 等级词汇 6 套不映射、A 级门槛无执行者（`apply_annotations.py` 中 `grade` 0 命中）、33 处 `A:decomp_*` 自标 A、268 条 triage 等级不可审计、44/78 个 status JSON 无元数据 |

---

## 三、下次继续的最短路径

```bash
# 1. 确认状态（应 clean、指标 75/2151/34）
git pull && python3 pipeline/cli.py check && git status --porcelain

# 2. 迁移下一处（示例：collect 已完成，接着做 ast_transform 或 data.py 的一处）
#    —— 改完只做两件事：
cp -r pal3/src /tmp/before_p15c
python3 pipeline/cli.py codegen all --skip-probe     # 必须等到日志出现 EXIT=
python3 - <<'PY'
import subprocess,os
r=subprocess.run(['diff','-rq','/tmp/before_p15c','pal3/src'],capture_output=True,text=True)
real=[l for l in r.stdout.split('\n') if l and 'globals.cpp' not in l and 'globals.h' not in l]
print('非 globals 差异:', len(real), real[:5])       # 必须为 0，否则回退本处
PY

# 3. 通过后提交推送；每批一处或两处
```

**回退纪律**：一律用 `git show HEAD:<path> > <path>`，**禁止** `git checkout --`/`restore`/`stash`/`clean -fd`。
**门禁颜色**：`test_smoke` 的 `compile_regression` 项与 `codegen all` 正常路径
**在 `sub_421870` 修好前会保持红色**，这是如实反映，不是故障；只跑 codegen 时用 `--skip-probe`。
