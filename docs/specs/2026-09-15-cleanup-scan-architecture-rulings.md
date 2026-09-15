# t4 架构级裁决书（2026-09-15）

本文件是 `data/status/_cleanup_scan_architecture.json`（t4 扫描产物）的**裁决附件**。
两项裁决由 captain 在 t4 期间直接指定必须给出结论、不得留作缺口。分类学与证据门槛见
`docs/specs/2026-09-15-cleanup-scan-taxonomy.md`。

---

## 裁决 (a)：codegen 读 `data/annotations` 属 C1 架构违规

### 裁决结论

**判定为 C1 架构违规。** 违规包含两个独立构成要件，任一成立即违规，此处两者皆成立：

1. **实际读取越出声明例外**（违反 CLAUDE.md「codegen 只读 export 产物、不直接访问 data/annotations」）。
2. **`pipeline/gen/data.py:226` 的"唯一位置"断言失实**——按 captain 要求，该失实注释**本身也作为违规证据**计入。

不采纳"属已声明的例外范围的延伸"这一辩护，理由见下文「为何不是合法延伸」。

### 证据（文件:行号）

**要件 1 —— 实际读取点清单（`data/annotations/` 下的直接文件读取）**

| 模块 | 位置 | 读取对象 | 是否声明例外 |
|------|------|----------|--------------|
| `pipeline/gen/data.py` | `:229` | `structs/`（vtable slot→方法名映射） | ✅ **唯一被声明的例外**（`:224-227` 注释） |
| `pipeline/gen/data.py` | `:191` | `skip_functions.json`（thunk 替换） | ❌ 未声明 |
| `pipeline/gen/data.py` | `:262` | `globals.json`（extern 生成） | ❌ 未声明 |
| `pipeline/gen/data.py` | `:374` | `functions.json`（补自由函数签名） | ❌ 未声明 |
| `pipeline/gen/ast_transform.py` | `:52`、`:148` | `structs/`（**两处独立读取**） | ❌ 未声明（该模块注释中无任何例外申明） |
| `pipeline/gen/stages/emit_headers.py` | `:106`、`:646`、`:869`、`:993`、`:1206`、`:1270`、`:1511`、`:2080`、`:2232`、`:2710`、`:3043` | `structs/`、`globals.json`、`template_bases.json` | ️ **模块 docstring 自声明**（`:1-12` 把 `data/annotations/` 列为 "field name overrides and template mappings"）——自声明但**与红线冲突** |
| `pipeline/gen/stages/collect.py` | `:97` | `skip_functions.json` | ❌ 未声明 |
| `pipeline/gen/stages/stage3_cleanup.py` | `:96` | `structs/<class>.json` | ❌ 未声明 |
| `pipeline/gen/stages/stage4_substitution.py` | `:334` | `store.annotations_dir/structs` |  未声明 |

**要件 2 —— 失实注释原文**
`pipeline/gen/data.py:226`：`This is the ONLY place codegen reads from annotations (architectural exception).`
同文件 `:191`/`:262`/`:374` 三处读取与该断言直接矛盾——**"ONLY" 为假**。
（取证：`grep -n 'annotations' pipeline/gen/data.py`）

### 判定依据

- **CLAUDE.md 红线原文**：「codegen 不读 annotation：codegen 只读 export 产物，不直接访问 `data/annotations/`」。
  `pipeline/gen/**` 是 codegen 层的代码实体，其直接 `open()` `data/annotations/` 下文件即命中红线。
- **例外只有一条**：`data.py:224-229` 的 vtable slot 解析。其余 12 处（含 `ast_transform.py` 两处、
  `emit_headers.py` 十一处等）均在例外范围之外。

### 为何不是「合法延伸」（关键论证）

尝试过辩护路径：export 阶段已经把 annotation 写进 IDB，因此 codegen 读 annotation 只是"读同一份数据的第二个入口"，不构成新的信息泄漏。**该辩护不成立**，因为 codegen 读 annotation 与 export 读 annotation 的后果不同：

- export 读 annotation 是**把 annotation 落进 IDB**（`export_full.py:148` 自称 "authoritative source for signatures"），此时 annotation 是"输入源"。
- codegen 读 annotation 是在**已有一条合法信息通道（export 产物）之外另开一条旁路**。旁路的危险在于：
  **它绕过了 export 层的过滤/映射契约**，使 `type: skip`、类型映射、可见性过滤等 export 层规则可被 codegen 自己再解释一遍（SKILL.md:130-132 明确禁止 codegen 绕过 annotation 状态做决策）。
- `ast_transform.py` 的两处读取尤其严重：该模块的职责是 **AST 语义变换**（stage2），却在
  **未声明**的情况下读 `structs/` 来判定跨类调用的合法性（`_rowtable_family()`）。这正是
  「在 codegen 层自行解释 annotation」的形态，而非"等价变换"。

因此判定：**例外之外的读取是 C1 违规，不是合法延伸。**

### 与 `emit_headers.py` 的区分（供 t5 分级，不改变违规判定）

`emit_headers.py` 的读取在模块 docstring 中被明确列为输入源，属**自声明**读取。它仍然是红线违规
（红线不因自声明而失效），但**与 `ast_transform.py` 的未声明读取应分为两个严重度**：
前者是"红线与实现长期脱节的存量"，后者是"未声明旁路"。t5 分级时建议分别处理。

### 建议动作（不自行扩范围）

- **不得**以"改注释把 SHOULD 说成 OK"的方式收口。两条合法收口路径：
  (i) 若团队确认需要 codegen 读 annotation，则**修改 CLAUDE.md 红线并记录决策**（当前 `docs/knowledge`
      的 Decisions 段为空，无任何记载）；
  (ii) 若红线维持，则把 `ast_transform.py`/`collect.py`/`stage3_cleanup.py`/`stage4_substitution.py`
      的读取改为消费 export 产物，`data.py` 的另外三处读取一并归并。
- 该收口涉及 codegen 层重构，**超出本轮 DAG**（t6 的 inScope 是 `data/annotations/`，t7 是
  `pipeline/ida/apply_annotations.py`，t8 是基建与 `pipeline/gen/codegen.py`）。故**不改**，
  仅作为裁决记录 + t5 分级输入。→ 已在 JSON 中以 `AR-001`/`AR-002` 记录。

---

## 裁决 (b)：声明式 `binary_size` 无真实尺寸来源 → S2 级证据不能成立

### 裁决结论

1. **撑大的 `binary_size` 确为缺陷，且其发源证据是「缩减式尺寸落地」脚本，而非任何真实尺寸来源。**
2. **`max_offset`（指令级成员访问上界）是唯一 A 级证据，但只是尺寸的「下界」。**
3. **结论：当前声明式 `binary_size` 不能满足 S2 级证据门槛**——凡以它为基础的尺寸一致性判定
   （`audit_layout.py`、`check_annotations.py`、`decomp_quality.py`）**均不能作为尺寸正确性的证据**。

### 证据

**(b-1) 统计独立复算（与 captain 数字一致）**
821 个「同时有 binary_size 与 known_members」的结构中：
- `binary_size > 3 × max_member_offset`：**53 个**
- `binary_size > 50 × max_member_offset`：**10 个**
- 极端值：`gbVFileSystem` 917972 / 24（38248×）、`SoundMgr` 918796 / 848（1083×）、
  `MXTransport` 363968 / 1108（328×）、`st_Manager` 244 / 1、`tagGroup` 516 / 4、`CSEHException` 264 / 4

**(b-2) 发源证据（captain 引用已核实）**
`tools/ida/archive/pal3_fix_oversized_structs.py:18` 注释：
`safe_size = max_offset * 2 (conservative, covers unobserved members)`
`:31` 实际写入形式为 `struct %s { char _data[%d]; }`，即**用纯填充字节占位替换真实定义**。
`:19-28` 的 FIXES 表仅 7 条（CEffect/CCBSystem/CEffMgr/PropUI/CEffMeteor/CEffCylinder/CEffExplosive），
**不能解释 53 个撑大项的全量**。

**(b-3) 更大宗的发源：缩减式尺寸落地脚本（本轮新发现）**
`tools/_land_sizes.py:1-9` docstring：
> `One-at-a-time size-update landing with probe verification.`
> `For each (class, size): edit structs JSON -> codegen headers -> probe S1+S2.`
> `Keep if S1 >= baseline and S2 >= baseline; else revert`

`:8-11` 的 `UPDATES` 表为**硬编码尺寸猜测**（UIStatic 248、CCBUIPanel 22112、UISceneFrm 3288、
UITitle_ArcSave 4004、JusticeBookUI 56192、UIRoleSelectDialog 2204、CScreenMode 5496、UIListBox 1760），
`:49` 直接 `d['binary_size'] = size` 写回注解。
**保留条件仅为「S1 与 S2 不低于基线」（`BASE_S1 731/751`、`BASE_S2 49/197`）**——
这是一个**极弱的通过条件**（基线 S2=49，低于当前 53），因此**几乎任何尺寸猜测都会留在树里**。

这解释了 53 个撑大项的形态：它们是**未经验证的尺寸猜测**被弱门禁放行的产物，
不是从 IDA 导出、PDB 或指令级证据推导出的尺寸。

**(b-4) 无任何尺寸来源记录**
53 个撑大项（含 `gbVFileSystem`/`SoundMgr`/`MXTransport`/`UIStatic`/`CCBUIPanel`/`UIListBox`/
`JusticeBookUI`/`UISceneFrm`/`CScreenMode`/`UITitle_ArcSave`/`UIRoleSelectDialog`）的
`size_evidence` **全部为 `null`**，`base_size`/`base_class` 亦无尺寸论证。
对比：`SceneObj.json` 至少记录 `base_size`。

**(b-5) 两个佐证尺寸无来源的「同一类在不同阶段有不同尺寸」事实**
- `UIListBox`：`_land_sizes.py:15` 目标 1760，当前注解与 IDB 均为 **1208**。
- `UIStatic`：`_land_sizes.py:12` 目标 248，当前注解与 IDB 均为 **152**。
两例说明这些尺寸是**反复试凑后的残值**；只要试凑通过弱门禁就被固化，无外部真值可对照。

**(b-6) 受影响门禁与其循环性**
| 门禁 | 位置 | 用法 | 循环性判定 |
|------|------|------|-----------|
| `tools/audit_layout.py` | `:200-205` | `binary_size != ida_size` → ERROR | **循环**：IDB 类型由 annotation 经 apply 写入，两者同源必相等 |
| `pipeline/check_annotations.py` | `:583-587` | `max_extent > binary_sz` → error | **不完整**：只能发现"撑破"，无法发现"撑大"（`binary_size` 越大越"通过"） |
| `pipeline/decomp_quality.py` | `:110-112` | `max(this+N) > cls_size * 2` → misattrib | **被稀释**：`cls_size` 撑大 N 倍，阈值放大 N 倍，误归属检出率随之下降 |

**循环性的直接实证（TIL 查询，IDB 副本，退出码 0）**：

```
gbVFileSystem    til_size=917972    udt_ok=True  nmembers=7   max_member_end=917972
SoundMgr         til_size=918796    udt_ok=True  nmembers=13  max_member_end=918796
MXTransport      til_size=363968    udt_ok=True  nmembers=12  max_member_end=363968
UIStatic         til_size=152       udt_ok=True  nmembers=19  max_member_end=152
CCBUIPanel       til_size=22112     udt_ok=True  nmembers=59  max_member_end=22068
UIListBox        til_size=1208      udt_ok=True  nmembers=25  max_member_end=1208
```

`gbVFileSystem` 的 TIL 尺寸与注解**逐位相同**（917972），且 `max_member_end` 也被拉到 917972 ——
说明 IDB 忠实反映了注解，而注解值与真实二进制（成员最大访问 +24）相差 38248 倍。
**`audit_layout.py:200` 的 mismatch 检查因此永远通过**，它对这 53 个结构零覆盖。
（与 `AR-005` 的"缺 ida_structs 时静默跳过"叠加：该检查在实际使用中双重失效。）

### 真实尺寸来源裁决

| 候选来源 | 可否作为 `binary_size` 的证据 | 理由 |
|----------|------------------------------|------|
| **IDA 导出结构**（`asm/pal3/ida_structs.json`） | ❌ **不可** | 该导出本身由 annotation 经 apply 写入 IDB 后产出，**与注解同源**（`audit_layout.py:200` 恒等已证）。用它做交叉验证是**循环论证** |
| **PDB（PAL3/PAL3A）** | ⚠️ **仅可作参考** | CLAUDE.md 明令「PDB 数据只能作参考（来自 PAL3A，偏移可能与 PAL3 不同），不能单独作为证据」；且本轮事实本身即由 PAL3A PDB 尺寸过大引发（`pal3_fix_oversized_structs.py:1-11` 记载 Scene 1094164、CEffect 245800、CCBSystem 90840、CEffMgr 43312 均属 PAL3A 的**错误尺寸**） |
| **指令级 `max_offset`**（A 级：`reg+disp32`） | ✅ **唯一 A 级证据，但只是下界** | 它能证明「至少用到这么多」，**不能证明类到此为止**；`_misattrib_evidence` 串中的 `max_offset=` 即此类（例：`max_offset=383296>class_size=111488`） |
| 分配点证据（`new T` / `operator new` 常量尺寸） | ✅ 可达 A/B 级 | 本轮未系统采集，属可补证路径 |

**因此**：`binary_size` 的当前值**没有一项真实尺寸来源**。而 `max_offset` 只给出下界，
故**不能**把 `binary_size` 直接降到 `max_offset`（那是"用下界冒充精确值"，同样违反
CLAUDE.md「每一处 annotation 修改必须有二进制直接证据」）。这正是 captain 要求裁决的核心：
**S2 级证据在尺寸问题上当前不成立。**

### 对本轮验收口径的影响（需 t5/t12 吸收）

1. **不得**把 53 个撑大项按 `max_offset` 批量改小（违反「禁止批量未验证修改」）。
2. `audit_layout.py` / `check_annotations.py` / `decomp_quality.py` 的"通过"**不能**作为
   `binary_size` 正确性的验收依据；涉及尺寸的修复条目，验收必须改用**独立于注解**的证据
   （指令级访问上界 + 分配点尺寸）。
3. 建议新增一个**能发现"撑大"的独立门禁**：以指令级 `max_offset` 为下界，
   标记 `binary_size > 3 × max_offset` 的条目（即本轮的 53 个）为待复核。
   该门禁的输入 `max_offset` 已存在于 `_misattrib_evidence` 串与 IDA 查询中，
   **但需要一个消费方**（见下）。

### 需 captain 决策：超出本轮 DAG（不自行扩范围）

以下动作**超出本轮 DAG 的任务范围**，我不执行，回报 captain：
1. **53 个撑大项的逐条尺寸重建**：需对每个 struct 采集分配点/指令级上界并逐条改注解
   （t6 inScope 是 `data/annotations/`，但 t6 的契约是按 triage 的 A/B 级证据批次修复；
   若 triage 判为"需补证据"，则本条应新建任务或明确排除）。
2. **新增"撑大检测"门禁**：属 `tools/`（t8 inScope 含部分 tools，但未含新门禁开发）。
3. **`audit_layout.py` 循环性修复**：其 IDA 侧输入与注解同源，需改为消费**独立**来源
   （raw IDB / 分配点证据），属工具改造。

---

## 附：本裁决新增/修正的 JSON 条目

| id | 变更 |
|----|------|
| `AR-001` | 裁决完成：**C1**（要件 2：失实注释）。`root_cause_fixed=false`，`recommended_action=FIX_PIPELINE` |
| `AR-002` | 裁决完成：**C1**（要件 1：例外外读取 12 处）。补充 `emit_headers.py` 自声明 vs `ast_transform.py` 未声明的严重度区分 |
| `AR-009`（新） | **C1**：`binary_size` 无真实尺寸来源；受损门禁 `audit_layout.py:200`（循环）/`check_annotations.py:583`（不完整）/`decomp_quality.py:110`（被稀释）；53 撑大项 / 10 超 50× |
| `AR-010`（新） | **C3c**：缩减式尺寸落地脚本 `tools/_land_sizes.py`（`Keep if S1>=baseline and S2>=baseline` 弱通过条件 + 硬编码尺寸猜测） |
| `AR-011`（新） | **C3c**：`tools/ida/archive/pal3_fix_oversized_structs.py` 以 `char _data[N]` 占位替换真实结构定义（丢弃类型信息的破坏性 workaround 残留） |
| `AR-102` | 修正：`[IDA_VTABLE]` 口径澄清（见下） |

## 附：`[IDA_VTABLE]` 口径澄清（captain 已裁定）

**仅头文件 1 处、`.cpp` 0 处**——两边都对，口径不同：
- `pal3/src/Render/RenderTarget3.h:31` 注释 `// [IDA_VTABLE] _nearby_4b6ca0; // 0x004B6CA0`（**1 处，头文件**）
- `.cpp` 实测 **0 处**（`grep -ro "IDA_VTABLE" pal3/src --include=*.cpp` 无命中）

**后续一律按此口径记录，不得再当分歧。** 原 `AR-101`/`t2` 相关表述以本条为准。

---

## 裁决 (c)：1266 条符号链接 = 刻意设计的工程结构（C2），但底层机制确为脆弱耦合

captain 追加线索（verifier 实测 `find . -type l` 共 1266 条，全部可解析）要求裁决：
这是**刻意设计的工程结构**还是**与 `core.symlinks` 强耦合的脆弱依赖**。

### 裁决结论

**必须分开裁决两件事——它们的答案相反：**

| 对象 | 裁决 |
|------|------|
| **1258 条 `tools/vc6/**` 小写 shim + 7 条 `.opencode/node_modules`** | **C2 有意保留**（刻意设计，需补一条存在性门禁） |
| **1 条 tracked 符号链接 `data/status/baselines/latest.json`** | **C4 僵尸资产**（唯一真正与 `core.symlinks` 强耦合且会静默错读的条目，已记为 `AR-205`） |
| 「与 `core.symlinks` 强耦合」这一**性质** | **成立，但耦合面只有 1 条链接，不是 1266 条** |

### 决定性拆分（tracked vs untracked 决定一切）

```
本仓库符号链接总数（排除 .git）：1266
├── tracked（mode 120000）：1     ← data/status/baselines/latest.json
│      └── 其 blob = 462044 字节 JSON（非路径串）→ 唯一坏条目
└── untracked：1265               ← 全部可解析，且全部是生成物
       ├── tools/vc6/ 小写 shim：1258
       ├── .opencode/node_modules：7（npm 安装副产物，非本仓库设计）
       └── （data/status/baselines/latest.json 除外）
```

取证：
```bash
git ls-files -s | awk '$1=="120000"{print $4}'          # → 仅 1 条
find . -type l -not -path "./.git/*" | wc -l            # → 1266
find . -type l -not -path "./.git/*" ! -exec test -e {} \; -print | wc -l   # → 0（无断链）
```

**关键点：`core.symlinks` 只影响 git 检出的 `tracked` 符号链接。**
`core.symlinks=false` 时 git 把 tracked symlink 物化成「内容为路径串的文本文件」；
而**untracked 的 1265 条 shim 完全不受该配置影响**（它们由本地脚本创建，git 从不管理它们）。
因此「1266 条与 `core.symlinks` 强耦合」这一说法**不成立**——耦合面实际只有 1 条。

### ① 链接目标是否都在仓库内且 tracked？——**是**

- `tools/vc6/**` 的 1258 条 shim 全部为**同目录相对链接**，目标是大写真实文件。
  实测：`tools/vc6/Lib/msvcrt.lib -> MSVCRT.LIB`，而 `MSVCRT.LIB` **tracked**（`git ls-files --error-unmatch` 成功），
  shim 自身 **untracked**。
- `tools/vc6/` 下 tracked 文件 1579 个，tracked symlink **0** 个 → shim **刻意不入库**。
- `.gitignore:87-88` 明确排除它们：
  `tools/vc6/Include/[a-z_]*`、`tools/vc6/Lib/[a-z_]*`
  → **shim 是"故意不跟踪的派生品"**，与 `!tools/vc6/**`（:81）的白名单配合，说明该 ignore 是刻意设计而非遗漏。
- 断链 0 条 → ① 通过。

### ② 是否有关键构建/读取路径依赖它们？——**是，且是构建必需**

- **生成者（tracked）**：`tools/setup_wine_vc6.sh:6` 自述
  「Creates lowercase symlinks in vc6/Lib/ and vc6/Include/ (**Linux case-sensitivity fix**)」，
  `:34-41` 对 `*.LIB *.OBJ *.PDB` 逐个 `ln -sf`，`:48-55` 对 Include 全目录做同样处理。
- **文档化（tracked）**：`docs/linux_build.md:50`（快速开始第 1 步）、`:62-66`、`:158`
  「解决方案：`setup_wine_vc6.sh` 自动创建小写符号链接」。
- **构建路径依赖**：
  - `cmake/toolchain-vc6.cmake:21` → `VC6_LIB_DIR = .../tools/vc6/Lib`
  - `cmake/toolchain-vc6.cmake:119` → `DXSDK_INCLUDE = .../tools/vc6/Include`
  - `tools/wine_vc6.sh:24` → `VC6_LIB="$PROJECT_ROOT/tools/vc6/Lib"`，`:36` 传为 `WIN_VC6_LIB`
- **为什么必需**：VC6 的 `cl.exe`/`link.exe` 在 **Windows 大小写不敏感**假设下查找
  `windows.h`/`msvcrt.lib`，而 `tools/vc6/Include` 里实际是大写 `WINDOWS.H`。
  Linux 的大小写敏感文件系统上，**没有 shim 就会 "cannot open include file"**。
  → shim 是**跨平台构建的必要适配层**，不是冗余。
- → ② 通过（属"刻意设计"）。

### ③ 在 `core.symlinks=false` 下是否会静默错读？——**shim 不会；但那 1 条 tracked 链接会**

- **本机实测 `git config --get core.symlinks` → `false`**（已设，Linux 默认应为 true）。
  这是团队为绕过 `latest.json` 检出失败而设的**本地 workaround**。
- **对 1258 条 shim：无影响**。它们 untracked，git 不参与其物化；由 `setup_wine_vc6.sh` 用 `ln -s` 创建。
  且即使 shim 缺失，失败形态是**编译器硬报错**（"cannot open include file"），**不是静默错读**。
- **对 `data/status/baselines/latest.json`：正是静默错读**。
  它是 tracked 120000，blob 是 462044 字节 JSON。两种检出模式都坏，但坏法不同：
  | 检出模式 | 结果 | 后果 |
  |----------|------|------|
  | `core.symlinks=true`（Linux 默认） | 用 462KB 串作链接目标 → 挂载创建 | **`ENAMETOOLONG`，`git reset --hard` 失败**（团队已知） |
  | `core.symlinks=false`（当前本机设置） | 物化为「内容为 JSON 的普通文件」 | **检出"成功"**，但该路径语义上应是链接 → 任何按「链接→时间戳文件」假设的读取会**静默读到过期 JSON** |
- → ③ 对 shim **不通过风险**；对 `latest.json` **成立**，且已记为 `AR-205`/`AR-303`。

### 定性

- **`tools/vc6` 的 1258 条 shim → `C2_intentional_signal`**：
  判定三条件齐备（产生位置可举证 = `setup_wine_vc6.sh:34-55`；保留理由有原文 = `:6` 与 `docs/linux_build.md:158`；当前仍有效）。
  **保留条件（必须写明）**：
  1. `tools/vc6/` 下继续以**大写**文件名跟踪真实产物（`!tools/vc6/**` 白名单维持）；
  2. `.gitignore:87-88` 的 `[a-z_]*` 排除规则维持——若被移除，1258 条 shim 会被误提交；
  3. `docs/linux_build.md` 的"第 1 步 `bash tools/setup_wine_vc6.sh`"不被删除；
  4. **解锁条件**：若将来改为在构建前对 include/lib 做大小写不敏感查找层（或改用已归一化文件名的 VC6 分发），
     则 shim 可整体撤销。
- **`data/status/baselines/latest.json` → 维持 `C4`**（见 `AR-205`），t8 修 100644 时须一并解决其 dangling 目标
  （它指向的 `20260915_100946.json` 未入库）。

### 派生缺陷：shim 的存在性无门禁（新条目 `AR-013`）

**实测无任何门禁校验 shim 是否存在**：
```bash
grep -rn "setup_wine_vc6\|msvcrt.lib\|lowercase" pipeline/*.py tools/*.py   # → 无命中
grep -n "symlink\|lowercase" tools/wine_vc6.sh                              # → 无命中
```
即：`wine_vc6.sh`（构建入口）与全部 probe/compile 门禁**都不检查 shim**。
后果：新机器/新检出若跳过 `setup_wine_vc6.sh`，**编译会以晦涩的
"cannot open include file" 失败**，而门禁不会指出"你漏跑了 setup"。
严重度：中（失败是**响亮的**，不是静默错读；但排障成本高、且会被误判为源码问题）。

**建议动作**（`FIX_INFRA`，但 `tools/wine_vc6.sh` 不在任何任务 inScope 内，故只作裁决记录）：
在 `tools/wine_vc6.sh` 加载时对 `tools/vc6/Include` 抽样 1-2 个已知小写名（如 `windows.h`）做 `test -e`，
缺失则**明确提示** `bash tools/setup_wine_vc6.sh` 并以非零退出。

**另一观察（不单独定性）**：`tools/wine_vc6.sh:21` 用 `tools/compilers/msvc6.0` 作 `VC6_ROOT`（Bin/Include），
而 `setup_wine_vc6.sh`、`cmake/toolchain-vc6.cmake` 用 `tools/vc6`。两者**同时存在**（`tools/compilers/msvc6.0` 有 4 项，
`tools/vc6` 有 66 项）。这不构成本裁决的缺陷（shim 只为 `tools/vc6` 生成，而两处 `VC6_LIB` 都指向 `tools/vc6/Lib`，是自洽的），
但存在**双份 VC6 安装**的维护歧义，建议 t5 记为低优先级 `DOCUMENT`。

---

## 裁决 (d)：M1/M4 区分用 `subclass` 承载，但需一个字段级修正（不新增词汇、不改已完成 spec）

captain 已裁定：**不引入 S1/S2/S3 词汇**（沿用 `evidence_grade` + `proof_needed`），
M1/M4 的区分用**已有的 `subclass` 字段**承载，并在 t5 批次里强制分列。

### 先确认纠错成立

```
grep -c: M4=0  M1=0  S1=0  S3=0  "调用方"=0  "this 类型"=0   （docs/specs/2026-09-15-cleanup-scan-taxonomy.md）
S2 的 4 次命中全部是编译阶段名（行 251/252/259/341，S2 probe / S2 ok 文件数）
```
→ 该 spec 中**确无** M1/M4/S1/S3 章节，"已落地 t1 spec"的说法不成立。纠错成立，
后续不得再引用该不存在的章节。

### 裁决结论：`subclass` 需拆分，且必须写进 t5 产物

**问题**：captain 要求 M1/M4 用 `subclass` 承载。但 spec 第 5 节已把 `subclass` 的取值约束为
**C3 域**（`C3a`/`C3b`/`C3c`/`C3d`）与 **C4 域**（`C4_1`..`C4_4`）。
两个域是**不同维度**：

| 维度 | 取值 | 含义 |
|------|------|------|
| 处置域（`class`/`subclass`） | C1 / C2 / C3a..d / C4_1..4 | 该条目的**性质与处置** |
| 根因域（缺陷类型） | M1_callee_name / M4_caller_this_type | 归属问题的**根因类别** |

**同一个 M4 条目可能落在任何处置域**——因此把它塞进 `subclass` 会造成**域混叠**。

**对 t3 实际产物的复核（已实测，纠正我最初的假设）**：t3 交付的
`data/status/_cleanup_scan_attribution.json`（212 条）已用**复合字符串**承载两个域：
```
subclass 取值分布： "C3a/M1_callee_name" 87   "C3a/M4_caller_this_type" 108
                    "M4_caller_this_type" 1   "C3c/M1_callee_name" 7
                    "C3b/M1_callee_name" 1    null 1    "M_UNDETERMINED" 7
```
M1/M4 **已经分列**（87 vs 108，动作也不同）。t3 在这一点上做对了，captain 要求 1（强制分列）
在**内容**上已满足。以下修正只针对**字段编码**，不针对分类实质。

**实测的好消息（不必返工的 3 项）**：
- 全部 109 条 M4 的 `recommended_action` 均为 `NEED_EVIDENCE`（唯一例外 1 条为 `KEEP_AS_SIGNAL`，见下）
  → **M4 已不在任何"改名"批次**，captain 要求 2 的风险**当前不存在**。
- `M_UNDETERMINED` 7 条全部为 `evidence_grade=E` + `recommended_action=NEED_EVIDENCE` + `proof_needed` 非空
  → **未违反** spec §6.2"待定不是合法终态"（该禁令约束 `evidence_grade`，不约束 `subclass`）；
  它只是用了非 spec 词汇做字段值，属**用词不精确**而非终态违规。
- spec §5.1 的 grade/action 合法性**零违规**（0 条 `C/D/E` 携带 `FIX_ATTRIBUTION`/`FIX_ANNOTATION`）。

**真正需要修正的只有一项（字段编码）**：`subclass` 的复合取值
（`"C3a/M1_callee_name"`、`"C3a/M4_caller_this_type"` 等）**不符合 spec §5 的字段契约**——
spec 规定 `subclass` 为单一取值（C3a..d / C4_1..4）或 `null`，复合值使
**"C3a 有多少条"不可直接计数**，spec §5 要求的自洽校验会失败。

**对 t3 产物的一致性快照实测**（`data/status/_cleanup_scan_attribution.json`，212 条，
快照时间 2026-09-15 10:31:03；**注意该文件当时正被并发更新，下列数字以该时间点为准**）：

| 校验项 | 结果 |
|--------|------|
| spec §5.1 grade/action（`C/D/E` + `FIX_ATTRIBUTION`/`FIX_ANNOTATION`） | **0 违规** |
| spec §5.1 class→action 合法性表 | **0 越界** |
| M1 / M4 分列 | M1=95、M4=109 → **内容上已分列** |
| M4 进入改名批次 | **0 条**（108 × `NEED_EVIDENCE` + 1 × `KEEP_AS_SIGNAL`） |
| `evidence.kind` 多样性 | 5 类（`decomp_member_access` 116 / `comment` 79 / `measured_count` 15 / `abs_addr` 1 / `file_absence` 1）→ **达标** |
| §5 计数自洽 | **不通过**：`class==C3` 210 条，但其中 **7 条** subclass 为 `"M_UNDETERMINED"`、不含任何 `C3x` 码 → 按 `class` 计数与按 `subclass` 计数不一致 |

`action` 全分布：`NEED_EVIDENCE` 196、`DOCUMENT` 11、`FIX_PIPELINE` 3、`DELETE` 1、`KEEP_AS_SIGNAL` 1；
`grade` 全分布：`B` 117、`C` 74、`E` 20、`A` 1。

**修正方案（不新增词汇、不改已完成 spec，只加字段）**——把两个域拆到两个字段：
```
"subclass": "C3a" | "C3b" | "C3c" | "C3d" | null,   ← 单一取值，维持 spec §5 约束
"m_code":   "M1_callee_name" | "M4_caller_this_type" | null,   ← 新增，承载根因域
"m_undetermined": true | false,             ← 可选：替代 "M_UNDETERMINED" 字段值
```
- 落地方式二选一（成本都低）：
  (a) **t5 在消费时归一化**（按 `/` 拆分并映射到 `subclass` + `m_code`），**不改 t3 产物——推荐，零返工**；
  (b) 请 t3 做一次字段重排（不改任何分类结论，仅改编码）。
- t5 归一化后**必须重跑一次 §5 自洽校验**（`class` 计数 == `subclass` 计数之和）并把结果写进产物。

**我不再主张的两点（已实测推翻，避免 captain 据错信息返工）**：
1. ~~"M4 + C3a 自相矛盾，必须返工"~~ —— 实测那 108 条的真实状态是"已打标记但**证据未足**"
   （grade B + `NEED_EVIDENCE`），"C3a = 已打标记但未修根"在**证据维度**上并不矛盾；
   矛盾只存在于"把 M4 读成需要改名"的**动作推断**上，而 t3 的动作字段已是 `NEED_EVIDENCE`，风险已被 t3 自行规避。
2. ~~"t3 违反 spec §6.2 的"待定不是合法终态"~~ —— 该禁令约束 `evidence_grade`，
   而那 7 条 `M_UNDETERMINED` 全部是 `grade=E` + `action=NEED_EVIDENCE` + `proof_needed` 非空，
   **合规**；问题仅是用了非 spec 词汇做**字段值**（用词不精确），非终态违规。

### t5 必须显式写明的 4 条（写入 t5 产物，不改 spec）

1. **M1 与 M4 强制分列**，各自独立计数与独立批次：
   - `M1_callee_name` = callee 归属/名字错误 → 动作是**改归属/改名**；
   - `M4_caller_this_type` = callee 归属正确、错在**调用方 `this` 类型**（`AStarFinder::GetHeuristicIdx` 型）
     → 动作**不是改名**。
   理由（captain 原文）：两类修复动作不同，混做会诱发**批量无证据改名**，
   正踩 `docs/knowledge/pattern_annotation_batch_rename_no_evidence.md`。
   实测计数（t3 产物）：M1=95 条（87 个 C3a + 7 个 C3c + 1 个 C3b），M4=109 条。
2. **M4 类不进入任何"改名"批次**（硬约束）。M4 的合法动作集合：
   `FIX_ANNOTATION`（改调用方 `this` 类型标注）/ `DOCUMENT` / `NEED_EVIDENCE`；
   **禁止** `FIX_ATTRIBUTION`。
   **实测现状**：109 条 M4 全部已是 `NEED_EVIDENCE`（1 条例外为 `KEEP_AS_SIGNAL`），
   故**当前无违规**；t5 须把该约束**显式写下**以固化，并保证归一化后仍成立。
   **推论（t5 应据此界定 M4 批次范围）**：M4 的 109 条**主体是"需补证据"批次**（108 条），
   而**不是**"可立即修"批次——因为 M4 要动的是**调用方 `this` 类型**，其门槛在 spec §2：
   归属/类型修正需 A 级（`reg+disp32`/绝对地址）或 decomp member access evidence。
   故 t5 不得把 M4 塞进"可立即修"，除非逐条达到该门槛。
3. **`evidence_grade ∈ {C,D,E}` 的条目禁止填 `FIX_ATTRIBUTION`/`FIX_ANNOTATION`**（沿用 spec §5.1）。
   实测 t3 产物此项 **0 违规**。
4. **`evidence.kind` 保留取证路径的多样性粒度**（captain 要求 3）：不得把不同来源压成单一取值。
   实测 t3 产物已保留 5 类：`decomp_member_access` 116、`comment` 79、`measured_count` 15、
   `abs_addr` 1、`file_absence` 1 → **达标**，t5/t6 归一化时**不得**把它们压平。
   t5 应至少能区分以下可复核取值（自由文本，但须可辨认）：
   - vtable 槽确认 callee 归属（`vtable_slot_confirm`）
   - struct 度规 `max_offset` vs 真实尺寸（`struct_metric_max_offset`）
   - 唯一 caller 类且无相反证据（`unique_caller_no_counter_evidence`）
   - 指令级 `reg+disp32` / 绝对地址（`instr_disp32` / `abs_addr`）
   - decomp member access（`decomp_member_access`）
   - ret-N（`ret_n`）、mangled 名（`mangled`）
   - 文件缺失/无消费方（`file_absence`）、注释/提交（`comment`/`commit`）、计数实测（`measured_count`）

### 与本裁决相关的一条既有条目

`GAP-AR-02`（344 个 `[MISATTRIBUTED]` 站点根因修复率未测）与 M1/M4 分列**直接相关**：
只有把 344 站点先分成 M1/M4，才能判定哪些站点根因已修（→ C2）、哪些未修根（→ C3a）。
故 t5 应把 M1/M4 分列作为 `GAP-AR-02` 的补证前提，而不是并列的两件事。

---

## 裁决 (e)：`M_UNDETERMINED` 类成立，且真实缺陷体落在**无任务覆盖**的 `pal3/src/`

captain 新增类别 `M_UNDETERMINED`（callee 的 decomp 是桩 `return 0;`、真实实现另有地址）。
规则已固化进 `docs/specs/2026-09-15-cleanup-scan-t5-rules.md` §1/§5。本节只记**我的独立复核结果**，
因为它比原报告更精确、并改变了一处定性。

### 字节级实证（PE 直读，非 Hex-Rays 文本推断）

```
0x004014F0  .text  32 C0 C2 08 00   →  xor al,al ; ret 8     (return 0，thiscall 2 参，5 字节)
0x004014E0  .text  33 C0 C2 08 00   →  xor eax,eax ; ret 8   (return 0)
0x00401500  .text  8b 49 04 8b 41 3c 85 c0 ...              (FindInOpen，真实实现)
vtable 0x0056A600 三槽 = 0x00401030 / 0x004014E0 / 0x004014F0
```
- `0x004014F0` **确为该类虚表 slot 2**，**槽位归属正确**。
- 该类 14 个被标注方法中**只有这 2 个是桩**（正是两个虚槽）；其余 12 个都有真实实现。
- caller（`pal3/src/Combat/CCBAI.cpp:246/444/646`）：
  `AStarPathFinder::GetHeuristicIdx((AStarPathFinder *)this, nRoleIndex, (int)&this->m_nHandleEnemyWell)`，
  `this` 是 **CCBAI**，返回值当 **bool** 用 —— captain 所述与实测一致。

### 对原报告的两处修正

1. **"真实实现另有地址"在该地址上不成立**：`pal3/src/Misc/AStarPathFinder.cpp` 对应体**同为 `return 0;`**，
   与 decomp 记录（`size_bytes=5`、`decompiled_c` 仅 `return 0;`）一致。
   故剩余待证的不是"另一处同名实现"，而是 **"该 5 字节桩是否为原二进制的真实体，
   抑或 decomp/IDB 未解析出函数体"** —— 这正确认了该案例属于 `M_UNDETERMINED` 而非 M1/M4。
2. **归因已由 vtable 确认正确** → 本类**不得**填 `FIX_ATTRIBUTION`；`[MISATTRIBUTED]` 注释里
   `-> fix IDB name of callee` 对本案是**误导性指引**（名字是对的），已在发给 engineer-codegen 的消息中提请区分文案。

### 对 t13 双轨策略的影响（已同步 engineer-codegen）

t13 的两分法（**合法直呼** vs **归属错误**）**覆盖不了这一类**：本站点 `this` 确是 CCBAI（不是合法直呼），
而 callee 归属又经 vtable 确认正确（不是归属错误）。
若按"被调方是虚方法 → 合法直呼 → 改成成员直调形态"处理，会把"调用方 `this` 类型错误"**静默藏起来**。
**建议增第三档**：`callee 经 vtable 确认正确，但 caller this 不符`（= M4 型）→
保持静态形态 + 标记，**改名不得作为动作**（与 captain 的"M4 不进任何改名批次"一致）。

### 缺口（已登记 `GAP-AR-09`）

真实缺陷体位于 `pal3/src/`，而 **`pal3/src/` 不在任何任务 inScope 内**（实测各任务 inScope：
t6 `data/annotations/`、t7 `pipeline/ida/apply_annotations.py`、t8 基建、t12 `data/status/`、
t13 `pipeline/gen/ast_transform.py`、t14 `pipeline/ida/export_full.py`、
t15 `pipeline/gen/stages/stage3_cleanup.py`、t16 `emit_headers.py`+`data.py`）。
它是 **codegen 生成物**（`.gitignore:125` 实测确认），手改属 Phase 2 且会被下次 codegen 覆盖。

**勘误（我自己写错并更正）**：我起初把理由写成"t6 的 outOfScope 已含 codegen 产物"——
实测 t6 `outOfScope = ['pipeline/gen/', 'pipeline/ida/apply_annotations.py', 'tools/']`，**并不含 `pal3/src/`**。
正确理由是**性质与生命周期**不同（t6 修归属/注解；`pal3/src` 是生成物），已更正。