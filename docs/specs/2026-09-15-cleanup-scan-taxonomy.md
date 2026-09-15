# 清理扫描分类学、证据门槛与验收口径（2026-09-15）

本文件是 cleanup-arch-scan 轮次的**共同依据**：三份扫描清单（t2/t3/t4）、triage 裁决（t5）、
修复（t6/t7/t8）、验证（t9）与落地（t12）必须使用本文件的分类、字段与门槛。
本文件只定义规则，不裁决具体条目（条目裁决在 t5）。

- 上游约束来源：`CLAUDE.md`（项目强约束）、`.claude/skills/pal3-pipeline/SKILL.md:79-84`（证据等级）
- 基线锚点（本轮实测，2026-09-15，见第 4 节取证命令）

---

## 1. 四类分类学（互斥且可判定）

任一清单条目**必须**且只能归入下列四类之一。判定按**闸门顺序**进行，先命中先归类，禁止"多标签"。

### 判定闸门（按顺序，命中即停）

| 顺序 | 闸门问题 | 命中 → 类别 |
|------|----------|-------------|
| G1 | 该条目是否为"无活引用 / 已被取代 / 本不该入库"的**资产本身**（文件、脚本、symlink 条目、分支、stash）？ | **C4 僵尸资产** |
| G2 | 该条目是否是**信息流越界 / 层职责错位**（读错了上游层、在该层打补丁替代上游修复、后处理编造信息）？ | **C1 架构违规** |
| G3 | 该条目是否为**代码生成器显式植入的信号**，且其产生位置在注释/提交/文档中写明了保留理由？ | **C2 有意保留的信号** |
| G4 | 以上均否，且存在**未修根的待清理痕迹**（未修根的 misattribution、tracked 生成物/过期引用、死代码路径、已放弃的一次性方案）？ | **C3 历史残留** |
| — | 以上均否 | 属**缺口**：写明缺什么证据、如何取证；不得留 "unknown/待定"（见第 5 节 `evidence_grade=E`） |

> G3 的"显式植入"必须可举证：产生位置 = 代码正则/模板字面量所在 `文件:行号`；保留理由 = 注释原文或提交信息。
> 只有"标记存在"而无保留理由的，落入 C3。

### C1 架构违规（arch_violation）

**定义**：违反 `CLAUDE.md` "项目强约束" 的信息流约束或分层职责的**当前活跃**代码路径。

判定子类（任一命中即 C1）：

1. **红线：codegen 读 annotation** —— `pipeline/gen/**` 直接打开 `data/annotations/` 下的文件做决策。
   声明例外：`pipeline/gen/data.py` 的 vtable slot 解析（原件注释称其为唯一例外）。
   **注意**：该注释的"唯一"性本身是可证伪的，若实测存在其他读取点，那些读取点是 C1，**且该注释失实也应记为 C1**（见 3.1 锚点）。
2. **红线：export 读 annotation** —— `pipeline/ida/export_full.py`（或 export 阶段任何代码）读 `data/annotations/`。
3. **后处理编造信息** —— stage 变换引入上游数据中不存在的类型/名称/偏移（非等价变换）。
4. **IDA 层能解决的问题在 codegen 打补丁** —— 结构体布局/成员类型/函数签名类问题通过 codegen 侧特殊分支或替换表绕开，而非修 annotation 或 IDA 导入器。
5. **门禁被弱化** —— 以 skip/吞异常/放宽阈值使强制检查点"通过"。

**不属 C1**（必须判为 C2 或 C3）：
- 已在 `docs/knowledge/` 记录、且**仍然成立**的既定取舍 → C2。
- 只在死代码路径上违规、活路径不受影响 → C3（并在缺口说明中提示"复活风险"）。

### C2 有意保留的信号（intentional_signal）

**定义**：由 codegen 显式植入、产生位置可定位、且保留理由被写明的标记。它**本身不是缺陷**：
它是把不可静默修复的歧义保留成编译期可见信号的设计。

判定必须同时满足三条：
1. 产生位置可举证（`文件:行号`）；
2. 保留理由在代码注释 / 提交信息 / `docs/knowledge` 中有原文；
3. 该信号**当前仍然有效**（未被上游修复使其成为过期信息）。

第 3 条不成立时（例如根因已修但标记仍在、或标记描述与实况矛盾）→ 降为 **C3**。

**解除条件**：C2 条目必须写明"何种上游修复完成后该标记可撤销"，否则视为未完成分类。

### C3 历史残留（historical_residue）

**定义**：曾经生效、现在已被取代或应当清理，但仍在仓库/产物中留痕的对象。四个可操作子类：

| 子类 | 判定特征 | 典型锚点 |
|------|----------|----------|
| C3a 已打标记但未修根的 misattribution | 站点存在且证据未达门槛；分桶为需考古 | `data/status/misattribution_ledger.json`（bucket `C`） |
| C3b 已被取代的旧代码路径 | 定义了但无活引用、或被新实现取代 | `pipeline/gen/stages/**` 内的失效分支 |
| C3c tracked 生成物 / 过期引用 | 生成物被版本控制；文档/代码引用已不存在的文件 | `data/status/baselines/latest.json`；指向 `_misattrib_evidence` 的失效知识页引用 |
| C3d 一次性/作废脚本、stash/备份分支 | 单次任务完成后的脚本、长期堆积的 stash、备份分支 | 见 3.3 锚点 |

**已放弃的一次性方案**（代码存在但路线已废弃）也归 C3b；判定需给出"被谁取代"的举证。

### C4 僵尸资产（zombie_asset）

**定义**：**资产本身**不该存在或已损坏，与它是否被引用无关。

判定子类：
1. **入库形态损坏的条目** —— git 条目类型/内容不匹配（如 mode `120000` 但 blob 是 462KB JSON）。
2. **本地堆积** —— `git stash list` 中的历史 stash、备份分支。
3. **未被跟踪且无产者的临时物** —— 仓库根/构建目录下的一次性 `.obj`、日志、临时测试残留。
4. **一次性脚本** —— 完成单次数据搬运后仍留在仓库的工具脚本（参考处理原则：提交 `9cb436305 chore: remove one-shot MCP extraction script`）。

**与 C3c 的分界**：条目是"**内容过期的生成物**"（路径合法、可被重新生成、只是内容旧）→ C3c；
条目是"**入库形态已经坏了 / 本就不该被跟踪**"（如 symlink 条目、临时 `*.obj`）→ C4。

---

## 2. 证据分级门槛

等级沿用 `.claude/skills/pal3-pipeline/SKILL.md:79-84` 的 A–D，并新增 E 级（无证据）以消除"未判定"态。

| 等级 | 定义 | 可用于 | 禁止用于 |
|------|------|--------|----------|
| **A** | 指令级 `reg+disp32`、绝对地址（`mov eax,[esi+0x1C]` 形态） | **偏移修改的最低门槛**；成员类型、归属修正的证据基础 | — |
| **B** | ≥3 条独立 A 级交叉确认；或 `ret-N`、mangled 名（`?Name@Class@@`）、decomp member access evidence | 归属修正、签名修正 | 单独用于偏移修改 |
| **C** | Hex-Rays 反编译文本推断 | 命名参考、方向提示 | **禁止**单独用于偏移修改（`CLAUDE.md` 明令） |
| **D** | 语义推断（命名合理性、调用模式直觉） | 仅供记录 | 任何偏移/类型/归属修改 |
| **E** | 无证据（含"声称有证据但证据本身不可信"） | 无——必须判 **需补证** | 任何修改 |

**硬门槛**：

- 偏移修改：**必须 A 级**（`CLAUDE.md`：A 级证据是偏移修改的最低门槛）。
- 归属（misattribution）修正：**必须 decomp member access evidence**，即函数内 `this->member`
  引用的成员**在目标类存在、且不在原类存在**。**仅凭 signature `this` 类型禁止作为唯一证据**。
- 类型/尺寸修改：A 级或 B 级，且须过 `python3 tools/audit_layout.py`。
- 删除（C4/C3c）：不要求二进制证据，但要求"无活引用/坏形态"的**命令级**举证。
- **禁止**：批量未验证修改、猜测性修改、伪语义命名（`m_nState_4968` 式地址后缀 ≠ 语义，
  等同 `_todo_`；不确定含义保留 `_todo_`）、破坏性 workaround（用 `void*`/`int`/`char[]` 掩盖真实类型）。

### 2.1 "历史证据"的可信度规则（`_misattrib_evidence`）

结构体注解 `methods[<addr>]._misattrib_evidence` 是**历史记录**，不是证据。规则：

- 任何引用 `_misattrib_evidence` 的条目，必须**先**把它与当前实况核对：证据串中的 `class_size`
  是否等于该结构体当前 `binary_size`。
- 本轮实测：222 处 `_misattrib_evidence` method 条目中 182 处可解析出 `class_size`，其中
  **141 处 `class_size != binary_size`（77.5%）**（取证命令见 4.4）。
- **`class_size` 的语义已在本轮确认为"分歧态"**：它既可能是旧注解尺寸、也可能是该方法的
  oracle/PDB 类尺寸，存在与 `binary_size` 相同的情形（如 `CUtil` 一处 48 vs 1772）。
  因此**不能**仅凭"数值不等"判定证据失效。
- 判定要求：`class_size != binary_size` 的条目**一律降级重取证**（需 live TIL/IDB 复核），
  不得沿用历史串作为修改依据；数值相等的条目可作**方向性**参考，仍需 A/B 级复核方可动偏移。
- **缺口**：团队简报引用的知识页 `docs/knowledge/pattern_misattrib_evidence_unreliable.md`
  **在仓库中不存在**（取证见 4.5）。该页是"此证据不可整体信任"结论的引用来源，
  但不构成可复核依据——本节的量化结论（77.5%）应作为替代锚点，并在 t12 沉淀为知识页。

---

## 3. 每类的本仓真实锚点

以下锚点均已实测，可直接引用；数值为 2026-09-15 本轮实测。

### 3.1 C1 架构违规 —— 锚点

信号标记与产生位置（全仓实测，见 4.1）：

| 标记 | 产生位置 | 语义 | 触发条件 | 实测规模 |
|------|----------|------|----------|----------|
| `[MISATTRIBUTED]` | `pipeline/gen/ast_transform.py:353`、`:436` | 跨类调用落在本类 `this` 上：保留**静态调用形式**并打标，令 MSVC6 报 C2352 作为"去修 callee 的 IDB 名"的诚实信号；**禁止**洗成合法语法 | 被调类 ≠ 当前类 | 344 站点 / 74 文件 |
| `[ROWTABLE]` | `pipeline/gen/ast_transform.py:421` | 家族窗口类经**调用者自己的 ROWTABLE** 分发：转成 `((X*)this)->X::M(...)` | 被调类 ∈ `_rowtable_family()` | 576 站点 / 88 文件 |
| `[VFTABLE]` | `pipeline/gen/stages/stage3_cleanup.py`（`__vftable` 引用行注释化，含行续接处理） | IDA 产物中不可编译的 `__vftable` 引用被注释掉 | 行内含 `__vftable` | 1643 站点 / 82 文件 |
| `[IDA_MISID]` | `pipeline/gen/stages/stage3_cleanup.py:752-759` | 命中 FLIRT/TIL 误识别模式串的行被注释：`Concurrency`、`details::VirtualProcessor`、`NtTib`、`ExceptionList`、`std::_Xlen`、`std::_Xran` | 行内含上述任一模式 | 84 站点 / 29 文件 |
| `[IDA_VTABLE]` | `pipeline/gen/stages/stage3_cleanup.py:290`（`action == 'comment_vft'` 分支） | 待 t2 确认（与 `[VFTABLE]` 的区别在 `comment_vft` 触发条件上） | 待确认 | **仅头文件 1 处、`.cpp` 0 处**（captain 裁定，2026-09-15）：`pal3/src/Render/RenderTarget3.h:31` 注释 `// [IDA_VTABLE] _nearby_4b6ca0; // 0x004B6CA0`；`grep -ro "IDA_VTABLE" pal3/src --include=*.cpp` 无命中。口径差异源于 grep 是否含 `--include=*.h`，**不再当分歧** |
| `[VFTABLE-STUB]` | `pipeline/gen/stages/stage3_cleanup.py:350-352` | vtable 存根的**代换**标记（与 `[VFTABLE]` 的"注释化"不同类） | 外层表达式需可编译 | 612 站点 / 51 文件 |

**C1 候选锚点（需 t4 复核后定级）**：`pipeline/gen/data.py:44` 的注释断言
"vtable slot 解析是 codegen 读 annotations 的**唯一**位置"（`data.py:226`），
但同文件另有 `:191 skip_functions.json`、`:262 globals.json`、`:374 functions.json`
三处读取，另有 `pipeline/gen/ast_transform.py:52`、`:148` 直接读 `data/annotations/structs`。
断言与实况矛盾，且 `ast_transform.py` 的读取点是否落在声明例外内需 t4 定性。

### 3.2 C2 有意保留的信号 —— 锚点

**锚点（`[MISATTRIBUTED]` / `[ROWTABLE]`）**：保留理由以注释原文写在产生位置
（`ast_transform.py:345-352`、`:427-435`：*"Do NOT launder it into legal syntax — keep the static
call form and mark it; MSVC6 reports C2352, which is the honest 'fix the IDB attribution' signal
(C2039 would mislead people into adding declarations)."*）。
故**标记本身**是 C2；只有当其描述的根因已修复而标记仍残留、或标记与实况矛盾时，该站点降为 C3。

**解除条件**：当 `data/status/misattribution_ledger.json` 对应条目从 bucket `C` 转为已确认的
`rename_to` 目标并落地后，该站点的 `[MISATTRIBUTED]` 可撤销。

**已知的风险信号**：本轮实测 ledger 197 条**全部**为 bucket `C`（需考古），`rename_to` 全为 `null`
（见 4.2）——即当前没有任何一条达到"可直接改名"的 A/B 分桶，这决定了 t3/t5 的"可立即修"批次
必须完全依赖**新取证**，不能从 ledger 直接取用。

### 3.3 C3 历史残留 —— 锚点

- **C3c 锚点（tracked 生成物）**：`data/status/baselines/latest.json` 被版本控制（多个基线快照
  共 ~20 个 JSON 文件在 `data/status/baselines/` 下入库），且其 git 条目形态损坏（同时属 C4，见 3.4）。
- **C3c 锚点（过期引用）**：`docs/knowledge/pattern_misattrib_evidence_unreliable.md` 被本轮
  团队简报当作既有结论引用，但文件不存在（见 4.5）。
- **C3a 锚点**：`data/status/misattribution_ledger.json` 中 197 条 bucket `C` 记录。
- **C3d 锚点**：`git stash list` 10 条、备份分支 `backup/local-line-20260904`。

### 3.4 C4 僵尸资产 —— 锚点

- **入库形态损坏**：`data/status/baselines/latest.json` —— `git ls-files -s` 显示 mode `120000`
  （symlink），其 blob `1b3b4705` 大小 **462044 字节**且内容是 JSON（非路径串）。
  产生路径：`tools/regression_detector.py` 的 Windows 回退分支（`symlink_to` 失败后 `copyfile`）。
  → 任何 Linux 检出触发 `ENAMETOOLONG`。（完整取证见 4.3）
- **仓库根僵尸资产（已定性）**：
  - `__vftable` —— **tracked** 且 0 字节，仓库根下的空文件，无任何引用价值 → C4_3/C4_4（入库残留）。
    取证：`git ls-files --error-unmatch __vftable`（成功）与 `ls -la __vftable`（size 0）。
  - `build_output.txt`（919690 B）与 `test.obj`/`mi_test.obj`/`mi_direct_test.obj`/
    `base_slot_derived_call.obj`/`deep_chain_test.obj`/`polybase_test.obj`/`si_base_slot_test.obj`
    —— **untracked 的本地残留**（`.gitignore:144 build_output.txt`、`.gitignore:3 *.obj` 已忽略）。
    取证：`git ls-files --error-unmatch test.obj`（失败）+ `git check-ignore -v test.obj`。
    → 属**本地堆积**：清理动作是删除工作区文件，**不产生 git 改动**（因此不算"修复"，t5 应归入
    C4 但 `recommended_action=DELETE` 且注明"不影响版本控制内容"）。

---

## 4. 基线锚点与取证命令

### 4.1 标记规模

```bash
for m in "VFTABLE-STUB" "\[VFTABLE\]" "\[ROWTABLE\]" "MISATTRIBUTED" "IDA_MISID" "IDA_VTABLE"; do
  echo "$m sites=$(grep -ro "$m" pal3/src --include=*.cpp | wc -l) files=$(grep -rl "$m" pal3/src --include=*.cpp | wc -l)"
done; find pal3/src -name '*.cpp' | wc -l   # → 198
```

实测（`.cpp` 口径）：`VFTABLE-STUB` 612/51、`[VFTABLE]` 1643/82、`[ROWTABLE]` 576/88、
`MISATTRIBUTED` 344/74、`IDA_MISID` 84/29、`IDA_VTABLE` **0/0**；`.cpp` 总数 **198**。
**附加口径（captain 裁定）**：`IDA_VTABLE` 若含头文件则 **1 处**（`pal3/src/Render/RenderTarget3.h:31`），
故汇总时须声明是否含 `*.h`。`[IDA_MISID]` 84 处由 `stage3_cleanup.py:752-759` 整体注释掉，
其"事实正确但丢语义 vs 应重命名保留"的二分见 `docs/specs/2026-09-15-attribution-artifact-inventory.md` §3.5。

### 4.2 misattribution ledger

```bash
python3 -c "
import json,collections
d=json.load(open('data/status/misattribution_ledger.json'))['ledger']
print(len(d), collections.Counter(e['bucket'] for e in d),
      'rename_to=', sum(1 for e in d if e.get('rename_to')))"
```

实测：`197 {'C': 197} rename_to= 0`。分桶语义见 `tools/misattribution_ledger.py:115-126`
（`B` = 单一 vtable owner 且 ≠ callee；`A` = 单一 caller 且无 vtable/struct owner 冲突；其余 `C`）。

### 4.3 坏符号链接

```bash
git ls-files -s data/status/baselines/latest.json      # → 120000 ... 0	data/status/baselines/latest.json
git cat-file -s 1b3b47053090cce9cd5cca74e2d3a398da5a1fe2   # → 462044
git cat-file -p 1b3b47053090cce9cd5cca74e2d3a398da5a1fe2 | head -c 40  # → { "name": "20260915_075701", ...
```

### 4.4 `_misattrib_evidence` 陈旧比例

见第 2.1 节；取证脚本统计 `data/annotations/structs/*.json` 中
`methods[addr]._misattrib_evidence`（222 条，可解析 `class_size` 182 条，不等 141 条）。

### 4.5 缺失引用

```bash
find . -iname '*misattrib*' -not -path './.git/*'
# → 仅 data/status/misattribution_ledger.json 与 tools/misattribution_ledger.py
grep -rn "misattrib_evidence_unreliable" --include=*.py --include=*.md --include=*.json . | grep -v '^./.git'
# → 无输出
```

### 4.6 不得回退门禁项与本轮基线

| 门禁项 | 基线值（2026-09-15 实测） | 取证 |
|--------|---------------------------|------|
| **L1 字节全同函数数** | **5** | `data/status/s4_baseline.json` → `stats.match_L1 = 5` |
| **S2 ok 文件数** | **53 / 198** | `data/status/baselines/latest.json` → `results` 中 `status=="ok"` 计数 53、总数 198 |
| S2 错误总数 | 3090 | 同上 `error_count` 求和 |
| S4 matched | 123 / 175 | `data/status/s4_baseline.json` → `stats.matched = 123`、`symbols = 175` |
| apply struct 导入 | 879 / 881 | apply 日志（t9 独立复测） |

**判定规则（回退 = 立即失败，不得进入下一阶段）**：

1. `L1 < 5` → 判**回退**。
2. `S2 ok < 53`（分母必须仍为 198）→ 判**回退**。
3. 分母 `198` 变化（新增/删除 `.cpp`）→ 必须显式声明并给出理由，否则判**不可比**。
4. `L1 > 5` 或 `ok > 53` → 视为改进；t12 才更新基线，且必须跑
   `python3 tools/compile_regression.py` 确认无退化后才 `--update-baseline`。
5. 任一修复若使上述两项回退，**该条修复判失败**（不允许"整体净收益"式辩解）。

---

## 5. 清单字段级约定（t2/t3/t4 → t5 的消费契约）

三份清单**必须**是 JSON，顶层为对象，含 `taxonomy_version`、`baseline`、`items`、`gaps`
四个键。每个 `items[]` 条目字段如下（缺字段的条目视为不合格，t5 必须退回）：

| 字段 | 类型 | 必填 | 约定 |
|------|------|------|------|
| `id` | string | 是 | 稳定且全局唯一，格式 `<清单前缀>-<NNN>`（`CG-` / `AT-` / `AR-`），跨迭代不复用 |
| `class` | enum | 是 | `C1_arch_violation` / `C2_intentional_signal` / `C3_historical_residue` / `C4_zombie_asset`，**恰好一个** |
| `subclass` | string\|null | 是 | C3 必填 `C3a`/`C3b`/`C3c`/`C3d`；C4 必填 `C4_1`..`C4_4`；C1/C2 填 `null` |
| `title` | string | 是 | 一句话可判定的描述 |
| `evidence_grade` | enum | 是 | `A` / `B` / `C` / `D` / `E`；不可留空 |
| `evidence` | object | 是 | `{kind, location, detail, command}`。`kind ∈ {instr_disp32, abs_addr, ret_n, mangled, decomp_member_access, comment, commit, file_absence, measured_count, til_query}`；`location` 用 `文件:行号` 或 `注解路径`；`command` 为可复现命令（删除/形态类必填） |
| `location` | string | 是 | 主锚点 `文件:行号` 或资产路径 |
| `sites` | int | 是 | 站点数（无站点概念填 `1`） |
| `files` | string[] | 是 | 涉及文件列表 |
| `root_cause_fixed` | bool | 是 | 根因是否已修（C2 判定关键） |
| `recommended_action` | enum | 是 | `FIX_ATTRIBUTION` / `FIX_ANNOTATION` / `FIX_PIPELINE` / `FIX_INFRA` / `DELETE` / `DOCUMENT` / `KEEP_AS_SIGNAL` / `NEED_EVIDENCE` |
| `proof_needed` | string\|null | 是 | `evidence_grade=E` 或 `NEED_EVIDENCE` 时必填：缺什么证据、如何取证 |
| `consistency` | object | 是 | `{bucket_ref, agrees, discrepancy}`：与 `misattribution_ledger.json` bucket / `_c2660_join.json` / `_c2660_adjudication_worklist.json` / `_ret_n_census.json` 的核对结果；`agrees=false` 必须写 `discrepancy` |
| `notes` | string | 否 | 补充；禁止用未验证推断填充 |

顶层 `gaps[]` 每条：`{id, what, why_unresolved, how_to_resolve}`。
顶层 `baseline`：至少含 `{l1, s2_ok, s2_total, s4_matched, captured_at}`。

**自洽要求**：`items` 长度 = 各类别计数之和；摘要与 JSON 计数必须一致（t5 复核点）。

### 5.1 类别与动作的合法性

| class | 允许的 `recommended_action` |
|-------|------------------------------|
| C1 | `FIX_ANNOTATION` / `FIX_PIPELINE` / `FIX_INFRA` |
| C2 | `KEEP_AS_SIGNAL`（附解除条件） |
| C3 | `FIX_*` / `DELETE` / `DOCUMENT` / `NEED_EVIDENCE` |
| C4 | `DELETE`（`DELETE` 不要求二进制证据，但要求命令级举证） |

`evidence_grade` 与 `recommended_action` 的门槛一致性：
`FIX_ATTRIBUTION` / `FIX_ANNOTATION`（涉及偏移/类型/归属）**不允许** `evidence_grade ∈ {C, D, E}`；
此类条目必须改为 `NEED_EVIDENCE` + `proof_needed`。

---

## 6. "已明确 / 已修复"的验收口径

### 6.1 条目级：判定"已修复"

一条 C1/C3 条目同时满足下列 5 条才算**已修复**；缺任一条只能标"部分完成"并保留在总账：

1. **证据**：修改点与 A 级（偏移类）或 B 级（归属/签名类）证据一一对应，且证据来源可复现。
2. **根因**：修改针对根因，不是绕过——不得以删除/弱化信号标记、加 codegen 特例、
   跳过门禁、吞异常的方式使其"消失"。
3. **层次**：修复落在正确层（`CLAUDE.md`：IDA 层能解决的问题在 IDA 层解决）。
4. **门禁**：跑完所属任务的 `verify` 全链，且第 4.6 节两条不回退门禁项均不回退。
5. **留痕**：`data/annotations/CHANGE_LOG.md`（注解类）或任务产出 JSON（管线/基建类）
   具备"证据 + 改动 + 验证"三要素，且验证含实际命令与输出。

### 6.2 条目级：判定"已明确"

`class` + `evidence_grade` 有确定取值、且 `evidence.command` 可复现即可判**已明确**，
**不要求**已修复。证据不足者必须是 `E` + `NEED_EVIDENCE` + `proof_needed`——
"已明确为需补证"是合法终态；**"待定/unknown"不是合法终态**。

### 6.3 批次级：判定"本轮清理完成"

1. 三份清单所有条目均有唯一 `class` 与确定 `evidence_grade`，无空值。
2. t5 四批次（可立即修 / 需补证据 / 应删除 / 有意保留）划分完成，计数自洽。
3. 可立即修批次：全部条目要么完成修复并附证据，要么给出"不可修"的证据说明。
4. 应删除批次：已删除并记录，或逐条写明未执行理由。
5. 第 4.6 节两条不回退门禁项**均不回退**（L1 ≥ 5、ok ≥ 53/198）。
6. `git status` 中无声明外改动；出现即点名。

### 6.3.1 冻结证据与"声明范围"必须分开列示（captain 要求，t5/t12 强制）

**冻结证据**：`data/status/baselines/verifier_prefix_s2.json`
（verifier 于 2026-09-15 10:09 冻结的**修复前** S2 快照；实测 `units=198 / ok=53 / errors=3090`，
`generated_at=2026-09-15T10:09:20`，与第 4.6 节基线锚点一致）。

纪律（违反即返工）：

- **不得删除**。它当前 **untracked 且未被 .gitignore 忽略**（`git status` 显示为 `??`），
  因此会被 `git reset --hard` / `git clean -fd` 清除 → t12 必须**显式加入版本控制**，
  并在 triage 的"应删除"批次中列为**保护条目**（`recommended_action` 不得为 `DELETE`）。
- **计数与对账必须分开列示**：在 t5 的批次计数与 t12 的清理总账中，
  「修复前冻结证据」与「t6/t7/t8 声明范围内的改动」**不得合并为一行/一个数字**。
  总账至少要有两个独立区段：
  1. **冻结/基线类**（verifier_prefix_s2.json、`*_baseline.json`、t6/t7/t8 产出的证据 JSON）；
  2. **修复类**（t6/t7/t8 在声明 inScope 内改动的文件）。
- 同类应保护项（皆 untracked、皆不可再生）：`data/status/baselines/20260915_{095407,100814,100946}.json`、
  `data/status/_cleanup_scan_{codegen,attribution,architecture}.json`、
  `data/status/_cleanup_verify_scan_claims.json`、`data/status/_cleanup_evidence_stub_call_4014F0.json`。

取证：
```bash
git status --short                                   # verifier_prefix_s2.json 应为 ??（未跟踪）
python3 -c "import json;d=json.load(open('data/status/baselines/verifier_prefix_s2.json'));\
s=d['s2'];print(d['generated_at'], s['ok'],'/',s['total'])"
```

### 6.4 明确禁止（本轮，违反即返工）

- 弱化门禁（删除校验、放宽阈值、try/except 吞错）以取得"通过"。
- 删除信号标记而未修根因（静默抹掉信号）。
- 用批量未验证修改或猜测性修改凑数。
- 用破坏性 workaround（`void*`/`int`/`char[]` 掩盖真实类型）换取编译通过。
- 用 codegen 特例替代 IDA 层修复。
- 把未验证的历史串（`_misattrib_evidence`、旧基线数字）当作证据提交。

---

## 7. 本轮已知缺口（需 t2/t4 复核，勿当结论使用）

| 缺口 | 现状 | 取证 |
|------|------|------|
| ~~`[IDA_VTABLE]` 规模不一致~~ **已澄清（captain 裁定 2026-09-15）** | 口径差异而非分歧：**仅头文件 1 处**（`pal3/src/Render/RenderTarget3.h:31`）、**`.cpp` 0 处**。差异源于 grep 是否含 `--include=*.h` | 第 3.1 节；`grep -rn "IDA_VTABLE" pal3/src --include=*.h --include=*.cpp` |
| `pattern_misattrib_evidence_unreliable.md` 不存在 | 简报引用的既有结论页缺失，结论无锚可依 | 第 4.5 节 |
| `data.py:226` "唯一例外"断言失实 | 同文件另有 3 处 annotation 读取（`:191`/`:262`/`:374`），`ast_transform.py:52`/`:148` 亦有 | 3.1 节 |
| `class_size` 语义未定 | 与 `binary_size` 不等时无法判定是"旧注解尺寸"还是"oracle 尺寸"；本轮仅量化分歧率（77.5%） | 第 2.1 节 |
| `[MISATTRIBUTED]` 标记的根因修复率未知 | 344 站点分别对应的根因是否已修，需 t3 逐条取证 | — |