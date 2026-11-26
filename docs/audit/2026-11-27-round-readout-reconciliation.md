# 轮次读数对账：census 快照差异归因 + L1 22:20 异常读数定性

- 卡号：#33 `tsk_01M8CCC0AYGPCD2Y60A89Y`
- 作者：观澜（业务）；性质：只读对账，不重跑管线、不改 annotation/基线/生成树
- 数据时点：2026-11-27 01:0x（工作树有并发卡在写，见 §6-4）
- 结论口径：本文所有数字都带「文件 + sha256 前 16 位 + 时点」；无法归因的进 §6 未决

---

## §0 五分钟结论

1. **洞面三份快照的差异可以逐笔归因**，没有一笔是「普查器自己漂了」：
   - 19:14 提交态 201 类 / 1,142 洞 / **1,275,908B（1,246.0KB）**
   - 22:13 归档 201 类 / 1,123 洞 / **875,232B（854.7KB）**，Δ−400,676B = ScreenEffectMgr −363,800（#13/#15）+ SaleUI −36,876（提交 `7f9d6a636`）
   - 23:36 中间态 200 类 / 1,120 洞 / **867,548B（847.2KB）**，Δ−7,684B = SaleUI 归零（#22 复核补 3 员 / 提交 `9f4436c2b`）
   - 00:40 工作树 200 类 / 1,105 洞 / **848,196B（828.3KB）**，Δ−19,352B = UITitle_JDHY −19,388（#23）+ ScreenEffect 族 6 类净 +36（#15 收尾，新增 ScreenEffectRingNode）
2. **L1 22:20 的 38 是「可比域塌缩」，不是退化**：该次 run 只把 47 个单元纳入 partial 明细（正常 148 个）、符号总体 1,259→661、matched 1,152→219；155 个「LOST 函数」在 22:45 的干净 match（L1=189，无丢失）里全部回来，其间没有改动这些函数的提交。**但它也不能当「无退化」的证明**——它只比较了很小的子集。
3. 三条引用纪律（详见 §5）：洞面数字要带「快照 sha + 是否 HEAD 提交态」；L1 数字要带「棘轮值 / 同域实跑值 / 可比域大小」；S2 与 check 各自带 `probe_census.generated_at` 与 warning 族口径。

---

## §1 复现命令与产物清单

```bash
# 四份 census 快照的总数与 sha
python3 - <<'PY'
import hashlib, json, subprocess
snaps = [('19:14 HEAD', 'git:HEAD:data/status/struct_holes_20261125.json'),
         ('22:13 archive', 'data/status/archive/struct_holes_after_sefmgr_20261126.json'),
         ('23:36 r5', 'docs/handoff/r5-20261126/struct_holes_r5_20261126.json'),
         ('00:40 worktree', 'data/status/struct_holes_20261125.json')]
for name, p in snaps:
    if p.startswith('git:'):
        b = subprocess.run(['git','show',p[4:]], capture_output=True).stdout
    else:
        b = open(p,'rb').read()
    m = json.loads(b)['_meta']
    print(name, hashlib.sha256(b).hexdigest()[:16],
          m['classes_with_holes'], m['total_holes'], m['total_hole_bytes'])
PY

# 逐类差分（对上一步的四个 JSON 两两比较 hole_bytes）
# 见 §2.2；差异类只有 2 + 1 + 6 个

# L1：现有产物（不重跑）
ls -l data/status/archive/s4_diff_detail_regressed_20261126T*.json
python3 - <<'PY'
import json, glob, os
for p in sorted(glob.glob('data/status/archive/s4_diff_detail_regressed_20261126T*.json')):
    d = json.load(open(p))
    print(os.path.basename(p), os.path.getsize(p), 'l1=', d['l1'],
          'partial=', d['partial'], 'units=', len(d['units']))
PY

# 干净 run 的对照（归档日志）
grep -E "^matched|carrier inventory|decomp entries" data/status/archive/r4_sefmgr_match_20261126.log
grep -E "^matched|carrier inventory|decomp entries" data/status/archive/r6_t1_titlejhdy_match_20261127.log
```

产物清单（时点 / 大小 / sha 前 16 位）：

| 用途 | 文件 | 时点 | 大小 | sha256 |
|---|---|---|---|---|
| census 19:14 提交态 | `git show HEAD:data/status/struct_holes_20261125.json` | HEAD `9f4436c2b` 内容 | 88,412B | `8aa80d4df68d34db` |
| census 22:13 | `data/status/archive/struct_holes_after_sefmgr_20261126.json` | 22:13 | 87,388B | `0574dc75b8b41085` |
| census 23:36 | `docs/handoff/r5-20261126/struct_holes_r5_20261126.json` | 23:36 | 87,055B | `4da7a2be8321e976` |
| census 00:40 工作树 | `data/status/struct_holes_20261125.json` | 00:40 | 86,297B | `802b3d824e88222e` |
| L1 22:20 明细 | `data/status/archive/s4_diff_detail_regressed_20261126T222052.json` | 22:20 | 96,718B | — |
| L1 22:12 明细 | `...T221209.json` | 22:12 | 62,819B | — |
| L1 23:07 明细 | `...T230704.json` | 23:07 | 101,979B | — |
| 正常 L1 明细（对照） | `...T214644.json` | 21:46 | 657,328B | — |
| 22:45 干净 match | `data/status/archive/r4_sefmgr_match_20261126.log` | 22:45 | 17,904B | — |
| 00:38 干净 match | `data/status/archive/r6_t1_titlejhdy_match_20261127.log` | 00:38 | 17,740B | — |

---

## §2 三份（实为四份）census 快照逐类对比

### 2.1 总量表

| 快照 | 类数 | 洞数 | 洞字节 | KB（÷1024） | 说明 |
|---|---|---|---|---|---|
| 19:14 提交态（HEAD 内容） | 201 | 1,142 | 1,275,908 | 1,246.0 | #4 对账时的读数；`8aa80d4d…` 与 #2 报告里 20:39 重跑产物 byte-identical |
| 22:13 归档 | 201 | 1,123 | 875,232 | 854.7 | R4 落位 + SaleUI 首版之后 |
| 23:36 中间态 | 200 | 1,120 | 867,548 | 847.2 | SaleUI 归零、节点类尚未改完 |
| 00:40 工作树 | 200 | 1,105 | 848,196 | 828.3 | **并发卡在写，仅供定位，不作定谳** |

### 2.2 逐类差分（只有这些类变过）

| 区间 | Δ字节 | 类 | 前 → 后（洞字节 / 洞数） | 归因 |
|---|---|---|---|---|
| 19:14 → 22:13 | **−400,676** | ScreenEffectMgr | 363,820 → 20（2→3 洞） | #13/#15 R4 实施 A：363,816B 大锚落位（`ScreenEffectMgr.json` 工作树改动，22:12–22:13；**未提交**） |
|  |  | SaleUI | 44,560 → 7,684（23→3 洞） | 提交 `7f9d6a636`（21:49:11「池证据落位」） |
| 22:13 → 23:36 | **−7,684** | SaleUI | 7,684 → 0（3→0 洞） | #22 独立复核「4B@0x10564 是字段」+ 补 3 员；提交 `9f4436c2b`（23:37:55，快照在其前 1 分钟取，读的是同一工作树内容） |
| 23:36 → 00:40 | **−19,388** | UITitle_JDHY | 19,396 → 8（14→1 洞；size 377,700 → 290,488） | #23 R6-T1 落位（`UITitle_JDHY.json` mtime 00:21，未提交） |
|  | −16 | ScreenEffectMgr | 20 → 4（3→1；size 363,968 → 152） | #15 收尾（mtime 23:40:32，未提交） |
|  | −4 | CEffGroupNode | 4 → 0 | #15 节点类修订（mtime 23:36:29，未提交） |
|  | −4 | ScreenEffectNode | 124 → 120 | 同上 |
|  | −4 | UI3DModelNode | 68 → 64 | 同上 |
|  | **+64** | ScreenEffectRingNode | 新增类 0 → 64（size 363,968） | 同上（新文件 mtime 23:40，未提交） |
|  |  | 合计 | −19,388−16−4−4−4+64 = **−19,352** | 与总量 −19,352 闭合 |

差分脚本验证：三个区间分别只有 2 / 1 / 6 个类发生变化，Δ 求和与总量差完全一致（`-400676`、`-7684`、`-19352`）。

### 2.3 归因证据

- `git show -s --format='%h %ci %s' 7f9d6a636 9f4436c2b` → `7f9d6a636 2026-11-26 21:49:11 annotations(SaleUI): 池证据落位…洞 44,560B→7,684B`；`9f4436c2b 2026-11-26 23:37:55 annotations(SaleUI): 按 #22 独立复核补 3 员，洞 44,560B→0B（58 成员）`。
- ScreenEffect 族与 UITitle_JDHY 均**未提交**：`git status --short data/annotations/structs/` 显示 `M ScreenEffectMgr/Node/RingNode/UI3DModelNode/CEffGroupNode/UITitle_JDHY`；mtime 依次 23:36:29 / 23:40:32 / 00:21。
- 交叉印证：`docs/specs/2026-11-26-ccctdata-recast-plan.md:362` 记录同一批并发写（`CEffGroupNode/PAL3VisNode/RenderTarget/ScreenEffect/ScreenEffectNode/UI3DModelNode/UIRoleDialog` 均 23:36:29、`ScreenEffectMgr` 23:40:32、`UITitle_JDHY` 23:50:11，基线四件 23:36:20）。
- `UIGameFrm` 在本轮四份快照中**完全没变**（28,268 / 27,916 / 37 洞 / 63 员，注解 mtime 11-24 21:20）——#31 尚未落盘，当前读数不能算它的战果。

---

## §3 L1 22:20 读数 38 的定性

### 3.1 读数链（22:20:52）

```
[L1 ratchet] previous 189 -> current 38
[L1 ratchet] semantic: previous 12 -> current 4 (L1+sem: 201 -> 42)
[L1 ratchet] population: previous matched=1152/1259 -> current matched=219/661
[L1 ratchet] coverage: previous carrier.paired=93 -> current 36
⚠️ 可比总体已变化 ⇒ 两次 L1 不可直接比较
🚨 拒绝自动对齐, 须显式 --rebaseline 并逐条归因
丢失函数 155 个（样本：C2DSpark::~C2DSpark @5070272 size=250、C2DSpark::CreateStars @5071264、ArcSceneObject::InitFromConfig @5395648、CCBControl::GetControl @5096880 …）
新增 L1 4 个
baseline+detail pair restored to previous run
REGRESSION: byte-perfect functions lost — investigate before committing
```

同一日志还打印了 `matched 219/661 symbols | L1 38 | partial 121 | … | compile-skip 88` 与 `121 partial rows in 47 units`。

> 该 `pipeline/_logs/loop_match.log` 的 22:20 版本已在 **00:53 被后续 match 覆盖**（现文件为 00:38 那次正常 run）。上面这段与 `decomp entries: 1358 / mangled methods: 3883`（正常 run 为 3,586 / 10,016）是本人在 00:5x 前读取时的原样记录；§3.2 的全部数字另有**落盘产物**可复现。

### 3.2 落盘产物交叉核对（可独立复跑）

| 产物 | L1 | partial 行 | 有 partial 的单元数 | 文件大小 |
|---|---|---|---|---|
| 21:46 正常 run `...T214644.json` | 188 | 810 | 148 | 657,328B |
| 22:12 `...T221209.json` | 31 | 78 | 39 | 62,819B |
| 22:20 `...T222052.json` | 38 | 121 | 47 | 96,718B |
| 23:07 `...T230704.json` | 34 | 128 | 18 | 101,979B |
| 22:45 干净 run（日志） | 189 | 827 | — | — |
| 00:38 干净 run（日志） | 189 | 816 | — | — |

正常 run 的 partial 明细覆盖 148 个单元；22:20 只覆盖 47 个 —— **约 2/3 的单元根本没进入对拍**。这与「155 个函数同时退化」不是一回事。

### 3.3 机制（两条，均由现有代码 + 产物支撑）

**机制 A：对拍开始时 decomp 语料被并发 export 清空/重写。**
- `pipeline/compare_pal3.py:105-119` `load_decomp_index()` 在 run 开始时 `glob` 整个 `asm/pal3/decomp/*.json` 一次成索引；索引缺失的类不进入 `mangled_map`，其函数也就无法参与比对。
- `pipeline/ida/export_full.py:265-270` 全量 export 在写之前会**清空主 decomp 目录**（`for f in glob(... '*.json'): os.remove(f)`），随后逐个重写（脚本自注：「过滤在 targets.sort() 之后 ⇒ 射程 export 会清空主 decomp 目录（实测 3649 → 1 个文件）」）。
- 22:20 run 读取到 `decomp entries: 1358`（正常 3,586），符号总体因此从 1,259 降到 661 —— 与「读到半份语料」完全一致。

**机制 B：本工具每单元自行编译，编译失败即整单元跳过。**
- `pipeline/compare_pal3.py:557-566`：每个 S2-green 单元都重新 `pc.run_cl(['/Fo'+obj, src] + flags)`，失败则 `COMPILE-SKIP` 并 `continue`（**不是**读 probe 遗留的 obj）。
- 22:20 的 `compile-skip 88`（正常 run 为 0）说明 88 个单元在当次编译硬失败；同时有并发管线占满 wine/CPU 时，这属于资源竞争表现，不改变任何函数的字节。
- 因此 `matched 219` = 能编译并匹配到符号的单元集合缩小，不是「字节变坏」。

> 22:12（39 单元）与 23:07（18 单元）两次同族异常，产物形态与 22:20 相同（明细文件 62–102KB、单元数远小于 148）；三次都落在并发管线活动窗口内（同一时段有 apply/export/probe 在跑，见 `data/status/archive/r4_sefmgr_loop_20261126.log` 22:04 的 loop、以及 23:14 的 `loop_after16` 归档）。

### 3.4 为什么「不是退化」

1. **身份集合可复原**：22:20 报的 155 个 LOST（如 `C2DSpark::~C2DSpark @5070272`、`C2DSpark::CreateStars @5071264`）在 22:45 的匹配里重新计入且 L1=189（`r4_sefmgr_match_20261126.log`：「无丢失函数、无新增 L1、无 REGRESSION」）。
2. **其间没有触碰这些函数的提交**：22:20→22:45 只有 docs 提交（`5b15fc482` 22:37 文档）；`pal3/src` 无内容变更（#5 报告已记 21:0x–21:5x 的 mtime 变化来自并发 loop、内容无 diff）。
3. **棘轮本身拒绝把它当退化**：判据是「L1 下降 + coverage 同降 + population 变化」⇒ 输出「可比总体已变化、拒绝自动对齐」，并把 baseline/detail 恢复为上一轮；`s4_baseline.json` 的 `rebaseline` 记录仍停在 R2 的 14:17:46（未被这次读数推进）。
4. **明细规模同步缩水**：判 L1 的分子掉了 151，但 partial 行也从 827 掉到 121——若真是 155 个函数字节变坏，partial 行应大幅**增加**而不是减少。

### 3.5 为什么「不能当无退化的证明」

- 该 run 只覆盖 47/148 个有 partial 的单元、219 个符号（正常 1,152）。**没进对拍的单元里有没有真退化，这次读数无法回答**。
- 判 L1 的可比域（`matched/symbols`）本身随注解变化而漂（本轮 1,259→1,248 就来自 #7 MagicUI 删类与 R6 落位），只有「同一可比域内」的 L1 变化才可解释为函数级进退。
- 结论口径：38 既不能写「退化 151 个」，也不能写「无退化」；正确写法是「该次 run 可比域塌缩，作废，需同域复测」。

---

## §4 「读数漂移」与「真实退化」判据

| 观察 | 判为读数漂移（并发/基线刷新） | 判为真实退化 |
|---|---|---|
| 可比域 | `matched/symbols`、`partial units`、`carrier.paired` 任一显著变化 | 三者基本不变 |
| L1 与 partial | L1 下降**且** partial 行数下降/明细文件变小 | L1 下降**且** partial 行数上升，LOST 行能对上具体字节差异 |
| 身份 | LOST 函数在随后同域 run 中原样回来 | LOST 在多次干净 run 中持续缺席 |
| 提交面 | 期间无触碰该函数的提交；`pal3/src` 无 diff | 有对应注解/代码提交 |
| 棘轮/基线 | `rebaseline` 记录未变、baseline pair 被恢复 | 需显式 `--rebaseline` 且有逐条归因 |
| 进程 | 同窗口有 apply/export/codegen/probe 在跑（`ps` 可证） | 独占窗口复跑仍复现 |

操作要求：引用 L1 前先 `ps aux | grep pipeline/cli.py`；有并发时**不要**跑 match 或只标注不可比。`match` 是编译+对拍的单进程动作，必须独占。

---

## §5 「引用洞面 / L1 数字必须带的口径」清单

**洞面（census）**
1. 文件路径 + **sha256 前 16 位**（或注明 `git show <sha>:…`）；仅写「最新」无效。
2. 三数一起引：`classes_with_holes / total_holes / total_hole_bytes`，并给 KB 换算（÷1024，声明口径）。历史事故：把 156,453B 当「156KB」。
3. 声明是**提交态**还是**工作树**：工作树可能被并发卡写到一半（本轮 00:40 的 ScreenEffectMgr=152B、RingNode=363,968 就是 #15 在途态）。
4. 声明 census 规则版本（现为 `_meta.rule` = v3 对齐感知+四修）。

**L1（match）**
5. 引用 **棘轮值（s4_baseline.stats.match_L1）** 与 **同域实跑值** 两个数，并注明最近一次可比的时点。
6. 必带可比域：`matched/symbols`、`partial`、`carrier.paired`（取自同一 run 的 s4_baseline/日志）。
7. 声明是否 `--rebaseline`、是否同域（域变了就写「不可比」）。
8. 区分数字类型：**census 洞面**（注解布局）≠ **match 读数**（字节匹配）≠ **S2 编译读数**（单元 ok/fail）。

**S2 / check**
9. S2 带 `probe_census.json` 的 `generated_at` + `ok/total` + `fail_own` + 总错误数。
10. check 带 `0 new + N frozen + M warnings` 三元组，并声明 warning 族口径（汇总行与逐族计数本轮未闭合，见 #19 报告 §1.2）。

---

## §6 未决（附下一步证据）

1. **22:20 那次 overlap 的具体进程无法钉死**：22:20 版 `loop_match.log` 已被 00:53 的 run 覆盖，没有 stdout 归档；只能从 `decomp entries:1358` / `compile-skip 88` 与代码路径推断。下一步：开一张**独占窗口**的干净 `loop`（或 `probe,match`）复测，若 L1 回 189 即可把 22:20 正式作废。
2. **机制 A/B 各占多少无法量化**：现有产物只能证明「单元数减少 + 语料变少」，无法拆出 155 LOST 里多少来自 decomp 截断、多少来自编译失败。下一步：在同一窗口人工制造一次「半份 decomp + 全量 obj」的对照（只读实验，不写产物）。
3. **22:12 与 23:07 两次同族异常未单独归因**：只有明细产物（31/78/39、34/128/18），没有当时的 stdout。下一步同上，用独占复跑替代。
4. **00:40 工作树快照是不稳定态**：ScreenEffect 族正被 #15 收尾（`ScreenEffectMgr` 152B、`ScreenEffectRingNode` 363,968B 新增），#31 UIGameFrm 尚未落盘。下一步：等 #15/#31 提交后重新 pin sha 再引用。
5. **s4_baseline 的 matched/symbols 已从 1,152/1,262 漂到 1,139/1,248**（00:37 run），L1 分母随注解变化属预期漂移，但目前没有「哪张卡贡献了哪几个符号」的账。下一步：按卡列函数级增删清单（可作为后续小卡）。
6. **`_loop_last.json` 与各阶段日志只保留最后一轮**：本轮三次异常之所以只能靠 `s4_diff_detail_regressed_*` 反推，是因为 `pipeline/_logs/loop_*.log` 每轮覆盖。下一步建议 loop 落盘带时间戳的轮次日志（属工具改进，需另开卡）。

---

## §7 只读自证

- 本卡写面只有 `docs/audit/`（本报告）；未运行任何 `pipeline/cli.py` 子命令（含 status/check/loop/match/probe）、未跑 `tools/census_struct_holes.py`、未改 `data/status/`、未改 annotation/生成树。
- 所用数据全部为 `git show` / `cat` / `python3` 只读解析现有产物。
- `git status --short` 中其他 `M/??` 均为并发卡产物（本报告新增仅 `?? docs/audit/`）。
