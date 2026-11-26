# m_unk_ 批次决策包：可复现清册 + 分批建议（只读）

- 任务：#12（tsk_01M8C13EC6M1CAF4WS7VSD），owner 观澜
- 写作时点：2026-11-26 21:40（扫描时点 21:39，见 §1 产物哈希）
- 性质：**只读决策包**。不执行任何改名、不动 annotation / 基线 / 生成树、不跑管线。
- 配套产物：`docs/audit/munk_census_20261126.py`（普查脚本）、`docs/audit/munk_census_20261126.json`（逐条快照 + 每文件 sha256）

---

## 0. 一分钟结论

1. **「全库 538 员 m_unk_」不可复现，本包不沿用这个数字。** 当前工作树实测 `m_unk_<offset>` 形态成员 = **91 条 / 3 类**（RoleStatePanel 40 + EquipUI 2 + SaleUI 49）；其中**已提交进 git 的只有 42 条 / 2 类**（HEAD），SaleUI 的 49 条是 #9 正在进行中的未提交重建产物（工作树 diff 371/358，mtime 21:29:00）。
2. 538 这个数只出现在交接文档自身（`docs/handoff/2026-11-26-struct-hole-campaign-handoff.md:18` 与 `:77`）；`git log -S"538 员存量" --all` 显示它由该文档的提交 `e4378a1c4` **引入**，此前仓库内无任何产物或提交含这个口径。同句的「余 891 类」反而可复现（= 含至少一个 unverified/无 evidence_level 成员的类数，891/927，§3.4）。
3. 91 条的真实构成（形态见 §2）：**51 条大数组（81,956B）+ 27 条区块（5,564B）+ 13 条标量（41B）**。大数组几乎全是 `unsigned char[N]` 或「相邻构造点空隙」（`rep stosd` 清零），按命名铁律只能留白；真正具备正名起点的只有 **13 条标量 + 部分带类型/消费面线索的区块**（RoleStatePanel 的 source 里带 ctor/disp 指令直证）。所以本批的正确形态不是机械改名，而是**分三批、只对有证据的成员开正名卡**。
4. 切分建议（详见 §4）：**批 A**＝RoleStatePanel 40 条（已提交，38 条 verified，但依赖 #8 验收与 C2440 cast 修复先落地）；**批 B**＝SaleUI 49 条（依赖 #9 验收，且 37 条为大数组，仅少量可正名）；**批 C**＝EquipUI 2 条（两段无证据大数组，建议暂缓、仅登记不复名）。台账那 61 类 323 员是**另一条战线**（字母/序号后缀形），不要并进本批。
5. 三项待批的互相关系与建议拍板顺序见 §5：**先拍 C2440「赋值行 cast」方案（替代已证不可行的 L-VAR）→ #8 验收 → 批 A → #9 验收 → 批 B**；`cls_43dfc0` 建档与本批无文件重叠，单独排期，不与批 A 同窗口跑 loop。

### 需拍板项（口径打架，请先裁这三条）

| # | 问题 | 可选项 | 本包立场 | 影响 |
|---|---|---|---|---|
| P1 | 「538 员」是否继续作为批准量的依据 | (a) 作废，改用实测 91/42；(b) 另立口径说明 538 的算法 | **(a)** —— 538 无命令可复现，按它批准会给出错误规模 | Human 已悬置的该项批准，规模依据要换 |
| P2 | 本批的目标定义 | (a) 对已有证据的 m_unk_ 成员**正名**；(b) 把其他占位形（todo/数字后缀/台账）**迁移成** m_unk_ 形 | **(a)** 本批只处理 m_unk_ 形态；(b) 属另一战役（涉及 332+102 条，判据不同） | 决定批 A/B 是「改名」还是「改名＋迁移」，工作量差数倍 |
| P3 | EquipUI 的两段无证据大数组（24,460B + 2,064B） | (a) 保持 `m_unk_` 留白；(b) 强行起名 | **(a)** —— R2 只证了「它们是 ctor 内联清零的数组」，没有语义证据；起名即违反命名铁律 | 若选 (b)，需要在命名战役里先补消费面证据 |

---

## 1. 可复现真值（命令 + 原样输出）

### 1.1 命令

```bash
python3 docs/audit/munk_census_20261126.py --json docs/audit/munk_census_20261126.json
```

口径：扫描 `data/annotations/structs/*.json` 全部 927 个文件；`known_members` 顶层 + `type={struct|union}` 内联成员；`exact` 正则 `^m_unk_(0x)?[0-9A-Fa-f]+$`；跨度 = 下一个顶层成员偏移差，末员用 `binary_size` 收尾。

### 1.2 原样输出（2026-11-26 21:39）

```
扫描文件: 927 个 (data/annotations/structs/*.json)

[exact] m_unk_<offset> 成员: 91 条 / 3 类
  EquipUI                2 条  跨度合计  27300 B  ev={'verified': 2}
  RoleStatePanel        40 条  跨度合计   7525 B  ev={'verified': 38, 'unverified': 2}
  SaleUI                49 条  跨度合计  52736 B  ev={'A': 49}
  跨度合计: 87561 B（无跨度 0 条）

[口径变体] todo=102  ledger=270  num=332  unk=91  any=94
  五种口径并集(按 类+偏移+名 去重): 797 条 / 92 类
  仅 unk: 91
  仅 any: 94
  仅 todo: 102
  仅 num: 332
  仅 ledger: 270
```

### 1.3 已提交态（HEAD）对照

```bash
$ git grep -h -o '"name": "m_unk_[^"]*"' HEAD -- data/annotations/structs | wc -l
42
$ for c in SaleUI RoleStatePanel EquipUI; do printf "%-16s " $c; \
    git show HEAD:data/annotations/structs/$c.json | grep -o '"name": "m_unk_[^"]*"' | wc -l; done
SaleUI           0
RoleStatePanel   40
EquipUI          2
```

⇒ **42 条已提交，49 条只存在于工作树**（SaleUI，见 §1.4）。引用「全库 m_unk_ 存量」时必须二选一说明口径，否则数字会随 #9 的提交/回退在 42↔91 之间跳。

### 1.4 并发事实（为什么 91 会漂）

| 文件 | 工作树 mtime | 工作树 sha256（前 16） | git diff | 归属卡 |
|---|---|---|---|---|
| `data/annotations/structs/RoleStatePanel.json` | 2026-11-26 20:52:54 | `932c4564329b65a4` | +1/−0（`base_size: 72`） | #8 布局修复（pending_acceptance） |
| `data/annotations/structs/SaleUI.json` | 2026-11-26 21:29:00 | `1e7fbaf856d6d433` | +371/−358 | #9 SaleUI 首版（in_progress） |
| `data/annotations/structs/EquipUI.json` | 2026-11-26 18:57:51 | `5a1f2ee07a578f72` | 无 | R2 已提交 |

- 扫描时点另有一轮 `probe all` 在跑（`ps` 见 §7），由别的卡启动；本包只读 struct JSON，不依赖 census/probe 产物，故不受其刷新影响。
- **SaleUI 49 条是 #9 重建时按留白形新落的成员**，不是历史存量；#9 若调整/回退，该部分需重新扫描（脚本重跑即可，10 秒内）。

---

## 2. 按类分布（规模 / 证据 / 形态）

| 类 | 条数 | 跨度合计 | evidence 分布 | 可命名性（形态） | git 状态 |
|---|---|---|---|---|---|
| RoleStatePanel | 40 | 7,525 B | verified 38 · unverified 2 | 标量 12（37B）· 区块 16（2,584B）· 大数组 12（4,904B） | **已提交** |
| EquipUI | 2 | 27,300 B | verified 2 | 大数组 2（24,460B + 2,064B），**无语义** | **已提交** |
| SaleUI | 49 | 52,736 B | A 49 | 标量 1（4B）· 区块 11（2,980B）· 大数组 37（49,752B） | **未提交（#9）** |
| **合计** | **91** | **87,561 B** | verified 40 · A 49 · unverified 2 | 标量 13 · 区块 27 · 大数组 51 | 42 已提交 |

形态判定规则（脚本内可复算）：类型含 `[N]` 且 N≥16 或跨度≥64B ⇒ 大数组；含 `[N]` 且 N<16 ⇒ 小数组；跨度≤8B 且非数组 ⇒ 标量；其余 ⇒ 区块。

证据强度观察：

- **RoleStatePanel 的 38 条 verified 是有真证据的**：source 里带 ctor/disp 的指令偏移与访问形态（如 `0x58/0x5c` 注记「疑窗口宽高，LineupUI bkWndX/Y 孪生同址同值在册」；`0x2afc8/0x2afd0` 是七模块指针槽，pointee 分别 402,824B / 290,488B）。这 2 条 unverified（`0x2afd8`、`0x2afd9`）只有 normalize_key 线索，不能正名。
- **SaleUI 的 49 条 A 级证明的是「这块内存存在且被 ctor 写过」，不是「它是什么」**：4 条 source 直接写「相邻构造点空隙」，3 条 `rep stosd` 整段清零，37 条是 `unsigned char[N]` 大块。按命名铁律这类只能留白。
- **EquipUI 的 2 条**是 R2 九数组落位 gate① 的产物，证据只到「ctor 内联 `??_L@YGXPAXII` 清零一段 24,460B / 2,064B」，没有消费面语义。

---

## 3. 口径对照：538 从哪来、和 296/323 差在哪

### 3.1 六个可复现口径（同一工作树、同一时点）

| 口径 | 值 | 命令/来源 | 说明 |
|---|---|---|---|
| A. `m_unk_<offset>` 精确形（本卡口径） | **91 条 / 3 类** | `docs/audit/munk_census_20261126.py` | 含未提交 SaleUI；HEAD 为 42/2 类 |
| B. 名字含 `m_unk_`（宽口径） | 94 条 | 脚本 `any` | 多出 3 条 SaleUI 的 `m_unk_0x150_view` 等派生名 |
| C. 名字含 `_todo_`（struct 内） | 102 条 | 脚本 `todo` | 若按大小写不敏感含 `m_nTodo_*` 则 343 条（与交接文档「todo 343」吻合，见 §3.3） |
| D. 数字后缀伪语义形 `^m_[A-Za-z]+_[0-9A-Fa-f]{2,}$` | 332 条 | 脚本 `num` | 形如 `m_nArrData_2C`、`m_nTodo_8D8`，属台账同族形态 |
| E. 伪语义台账在档形状（按 类+名 命中） | 270 条 | 脚本 `ledger` | 台账共 61 类 323 员，其中 270 员仍以原名在树 |
| F. 五口径并集（去重） | 797 条 / 92 类 | 脚本 `union` | 任何「全库非语义名」都会落到这个量级 |

**没有一种口径等于 538。**538 也不等于它们的任何简单组合（A+C=193、A+E=361、C+D=434、A+C+E=463、A+C+D=521、C+E=372……）。

### 3.2 538 的出处

- 全库仅两处出现：`docs/handoff/2026-11-26-struct-hole-campaign-handoff.md:18`（§1 状态表）与 `:77`（§5 待批清单）。
- `git log -S"538 员存量" --all --oneline` → **只有 `e4378a1c4`**（即写入交接文档的那次提交）。仓库内任何 data/status 产物、任何更早提交都没有这个数。
- 结论：538 是**文档写作时的估算/笔误**，不是某次扫描的输出。它不能作为批准量的依据（见 §0 P1）。

### 3.3 「58 类 296 员」与「61 类 323 员」的差异（可归因）

`data/annotations/archive/pseudo_semantic_names_20261118.json` 的版本史（`git log --follow` 实测）：

| 提交 | 类数 | 条目数 | 说明 |
|---|---|---|---|
| `308763f84`（初始落档） | 58 | **296** | 交接文档 §2 的「58 类 296 员」就是这个初始值 |
| `c1c61fdca` | 58 | 303 | R1 语义收敛补录 |
| `93c4f02bd` / `d0b8d775b` | 58 | 301 | R2 调整 |
| `788ade5ed`（R6 台账豁免） | **61** | **323** | 「22+1 漏登补齐」（commit message 原话） |

⇒ 296→323 是台账自身在两个月的补齐，不是扫描口径变化；引用时写「61 类 323 员（2026-11-26 在档）」即可。

### 3.4 「余 891 类」可复现，538 不可

现工作树 927 个 struct 文件中，**含至少一个 `unverified` / 无 `evidence_level` 成员的类 = 891 个**（共 8,833 个成员）。这与交接文档同句的「余 891 类」精确吻合，说明作者当时确有类维度的扫描；但成员维度的 538 没有任何对应输出。**同句一半可复现、一半不可复现**，这正是它不能直接拿来批准的原因。

---

## 4. 分批建议（三批 + 一条旁线）

设计原则：按「是否已提交 / 证据强度 / 是否被在跑卡占用」切，不按字母序切；每批都必须能独立开卡、独立过门禁。

### 批 A：RoleStatePanel 40 条（已提交，推荐先做）

| 项 | 内容 |
|---|---|
| 规模 | 40 条 / 7,525B；可命名候选 = 12 标量 + 16 区块（37B + 2,584B），12 条大数组（4,904B）沿用留白 |
| 证据 | verified 38（ctor/disp 指令直证 + source 记访问形态）；unverified 2（`0x2afd8/0x2afd9`，只有 normalize_key 线索，本批不动） |
| 风险 | 中低。① 同文件正被 #8 占用（`base_size: 72` 未提交）⇒ 必须等 #8 验收落地；② 该类的 C2440@777 未修，单元 fail 会让 loop 的 S2/L1 读数失真 ⇒ 必须等 cast 方案落地再看门禁；③ 12 条大数组若强行起名会违反命名铁律 |
| 门禁 | `check`（0 new）→ `loop` 全链（apply/export/codegen/probe/match，约 20–25 分钟）→ `verify_fix --class RoleStatePanel`（offsetof/sizeof 证物） |
| 依赖顺序 | #8 验收 → cast 修复（#6） → 批 A 开卡 |
| 可直接开卡的形态 | 「RoleStatePanel 标量/区块成员正名（≤28 条，逐条带 source 证据；数组与 2 条 unverified 保持留白）」 |

### 批 B：SaleUI 49 条（依赖 #9，且大部分不可正名）

| 项 | 内容 |
|---|---|
| 规模 | 49 条 / 52,736B；形态：大数组 37（49,752B，多为 `unsigned char[N]` 与「相邻构造点空隙」）、区块 11（2,980B）、标量 1（4B） |
| 证据 | A 级 49，但证明的是「ctor 写过这块内存」，不是语义；source 里 4 条明写「空隙」、3 条 `rep stosd` 清零 |
| 风险 | 高。① `SaleUI.json` 正被 #9 改（+371/−358，未提交），此刻动它必冲突；② 37 条大数组若起名=编造语义；③ #9 的验收本身要求「命名 m_unk_ 留白形」，本批若在 #9 未验收时介入会互相打脸 |
| 门禁 | 先等 #9 accepted 并 commit → 重跑本包脚本确认条数 → `check` → `loop` → `verify_fix --class SaleUI` |
| 依赖顺序 | #9 验收 → 重扫 → 批 B 开卡（只做「有类型/有消费面」的少数成员，例如 `UIRoleDialog`/`CCBResultWindow` 型窗口对象，其余留白） |
| 可直接开卡的形态 | 「SaleUI 有类型线索的窗口对象成员正名（预计 ≤5 条）+ 其余 44 条留白并登记原因」 |

### 批 C：EquipUI 2 条（建议暂缓，仅登记）

| 项 | 内容 |
|---|---|
| 规模 | 2 条 / 27,300B（24,460B + 2,064B 两段 `unsigned char` 数组） |
| 证据 | verified 仅到「ctor 内联清零」，无消费面、无类型线索 |
| 风险 | 起名即编造；收益为零（这两段本来就该留白） |
| 门禁 | 不需要（不改名）；若要合并进批 A 的 loop 一起验，顺带即可 |
| 依赖顺序 | 无；等 R6/命名战役有消费面证据后再议 |
| 建议 | **暂缓**，在本包登记为「无证据、维持留白」，不作为实施卡 |

### 旁线（不进本批）：台账 61 类 323 员正名战役

- 这是**字母/序号后缀装饰名**（`CachedA/B`、`RoleParam0-3`、`UIFlagA/B`…）的战役，判据是「消费/写值证据实锤」，与 m_unk_ 留白形的正名同法但对象不同。
- 在档 323 员、当前仍以原名在树 270 员；若并入本批，规模会从 91 直接膨胀到 361+，且两类形态的门禁预期不同（台账成员多已 verified/unverified 混杂，正名会连带改类型）。
- 建议：作为独立卡「台账伪语义名正名（按类分片，每片 ≤50 员）」，不进本批的批准范围。

### 门禁成本对照（供排期）

| 门禁 | 单次成本 | 必须过的场景 |
|---|---|---|
| `python3 pipeline/cli.py check` | 秒级 | 任何 annotation 改动后 |
| `python3 pipeline/cli.py loop` | 20–25 分钟（全链 apply→export→codegen→probe→match） | 任何会影响生成头/源或布局的改动；改完必须同一轮读 S2/L1，**不能事后查基线**（棘轮会回写） |
| `python3 tools/verify_fix.py --class <Cls>` | 分钟级/类 | 成员偏移、sizeof、传递依赖、端到端基线 |
| `python3 tools/audit_type_layout.py --only <Cls>` | 秒级 | 改 struct 布局后 |

---

## 5. 与三项待批的关系（L-VAR 引脚 / cls_43dfc0 建档 / 本批）

### 5.1 L-VAR 引脚提案

- 现状：可行性试验已完成（#2，对影验收），结论 **「只改局部声明行」不可行**——`unsigned long*`/`unsigned char*` 仍 C2440，`char*` 会退化成 1+1 字节写，`void*` 无法解引用。最小可用替代是**赋值行 cast**（`m_bRtVisible = (unsigned long *)this->m_bRtVisible;`，字节中性）。
- 与本批的关系：**不共享写入文件**（L-VAR/cast 改的是 codegen 规则与生成源，本批改的是 struct 成员名），但**同属 RoleStatePanel 单元**，且 cast 不落地时该单元 fail，批 A 的 loop 读数不可信。
- 建议：把待批项从「L-VAR 引脚」更新为「**赋值行 cast 方案**」，并**排在批 A 之前**拍。理由：它是 S2 红（157/229）的直接修复路径，也是批 A 门禁的前置。

### 5.2 cls_43dfc0 建档（基类链债务 #2）

- 现状：`0x43DFC0` 是 1208B 的真类 ctor（写表 `0x56AD40`，`push 0x4B8 → operator new` ×3）；`UIListBox` 名义仍绑 72B 类（下游 SkillUI/StateUI/CCBUICtrl 的 bases 锚定它）。建档 = 新建 struct JSON + 迁 ~34 方法 + `UIListBox` 名义重锚。
- 与本批的关系：**无文件重叠**（新文件 + UIListBox/methods vs 三个类的 known_members），但会动 bases 晶格，check C10 布局冲突风险约 280 项（knowledge 文档原话），**不能与批 A 在同一 loop 窗口做**（读数会混在一起，无法归因）。
- 建议：独立 P1，排在批 A 之后或与批 B 错峰；不需要 Human 额外批准本批的口径。

### 5.3 本批（m_unk_ 批次）

- 只读决策包，批准后按 §4 开实施卡；不预设批准、不执行改名。

### 5.4 建议拍板顺序

```
① C2440 赋值行 cast（原 L-VAR 提案的替代）  ← 解 S2 红，批 A 的前置
② #8 布局修复验收（base_size:72 落地 commit）
③ 批 A：RoleStatePanel 40 条（≤28 条正名，数组/2 条 unverified 留白）
④ #9 SaleUI 验收 → 重扫 → 批 B：SaleUI 少数有类型成员
⑤ cls_43dfc0 建档（独立排期，不与 ③ 同窗口）
  批 C（EquipUI 2 条）暂缓，仅登记
```

---

## 6. 附录：逐条清单（91 条，与 §1 输出闭合）

字段：偏移 / 现名 / 类型 / 跨度 B / evidence / source 摘要。完整原文（含 file 路径与每文件 sha256）在 `docs/audit/munk_census_20261126.json`。

#### RoleStatePanel（40 条，跨度 7525 B）

| 偏移 | 现名 | 类型 | 跨度 B | evidence | source 摘要 |
|---|---|---|---|---|---|
| 0x58 | m_unk_0x58 | int | 4 | verified | [R3 ctor 解码落位 2026-11-26 verified] ctor 写 [esi+58h]… |
| 0x5c | m_unk_0x5c | int | 4 | verified | [R3 ctor 解码落位 2026-11-26 verified] ctor 写 [esi+5Ch]… |
| 0x64 | m_unk_0x64 | int | 4 | verified | [R3 ctor 解码落位 2026-11-26 verified] ctor 清零 [esi+64h… |
| 0x68 | m_unk_0x68 | int | 256 | verified | [R3 disp 直证落位 2026-11-26 verified] disp 0x68 (Updat… |
| 0x168 | m_unk_0x168 | unsigned char | 1 | verified | [R3 ctor 解码落位 2026-11-26 verified] ctor 清零 [esi+168… |
| 0x170 | m_unk_0x170 | int | 4 | verified | [R3 ctor 解码落位 2026-11-26 verified] ctor 清零 dword [e… |
| 0x174 | m_unk_0x174 | unsigned char | 1 | verified | [R3 ctor 解码落位 2026-11-26 verified] ctor 清零 [esi+174… |
| 0x175 | m_unk_0x175 | unsigned char | 3 | verified | [R3 ctor 解码落位 2026-11-26 verified] ctor 清零 [esi+175… |
| 0x178 | m_unk_0x178 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x210 | m_unk_0x210 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x2a8 | m_unk_0x2a8 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x340 | m_unk_0x340 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x3d8 | m_unk_0x3d8 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x470 | m_unk_0x470 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x508 | m_unk_0x508 | unsigned char[344] | 344 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x660 | m_unk_0x660 | unsigned char[344] | 344 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x7b8 | m_unk_0x7b8 | unsigned char[344] | 344 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x910 | m_unk_0x910 | unsigned char[344] | 344 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0xa68 | m_unk_0xa68 | unsigned char[344] | 344 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0xbc0 | m_unk_0xbc0 | unsigned char[344] | 344 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0xd18 | m_unk_0xd18 | unsigned char[344] | 344 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0xe70 | m_unk_0xe70 | unsigned char[344] | 344 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0xfc8 | m_unk_0xfc8 | unsigned char[344] | 344 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x1120 | m_unk_0x1120 | UIFrameContainer | 168 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x11c8 | m_unk_0x11c8 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x1260 | m_unk_0x1260 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x25b94 | m_unk_0x25b94 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x25c2c | m_unk_0x25c2c | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x25cc4 | m_unk_0x25cc4 | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x25d5c | m_unk_0x25d5c | UIFrameContainer | 168 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x2a800 | m_unk_0x2a800 | UIFrameContainer[4] | 608 | verified | [R3 ??_L 三元组落位 2026-11-26 verified] ctor 内 ??_L@YGX… |
| 0x2aa60 | m_unk_0x2aa60 | UIFrameContainer | 168 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x2ab08 | m_unk_0x2ab08 | UIFrameContainer[5] | 840 | verified | [R3 ??_L 三元组落位 2026-11-26 verified] ctor 内 ??_L@YGX… |
| 0x2ae50 | m_unk_0x2ae50 | unsigned char[344] | 360 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x2afc8 | m_unk_0x2afc8 | void * | 4 | verified | [R2 七模块指针落位 2026-11-26 verified] 三证：①分配=金表闭合容器七模块槽 … |
| 0x2afd0 | m_unk_0x2afd0 | void * | 4 | verified | [R2 七模块指针落位 2026-11-26 verified] 三证：①分配=金表闭合容器七模块槽 … |
| 0x2afd8 | m_unk_0x2afd8 | unsigned char | 1 | unverified | SetEquipSlotData / normalize_key: 0x2afd8 -> 176088… |
| 0x2afd9 | m_unk_0x2afd9 | unsigned char | 3 | unverified | SetEquipSlotData / normalize_key: 0x2afd9 -> 176089… |
| 0x2afdc | m_unk_0x2afdc | UIFrameContainer | 152 | verified | [R3 ctor 解码落位 2026-11-26 verified] InitUI@0x4a1e40 … |
| 0x2b074 | m_unk_0x2b074 | int | 4 | verified | [R3 ctor 解码落位 2026-11-26 verified] ctor 清零 dword @0… |

#### EquipUI（2 条，跨度 27300 B）

| 偏移 | 现名 | 类型 | 跨度 B | evidence | source 摘要 |
|---|---|---|---|---|---|
| 0x261f8 | m_unk_0x261f8 | unsigned char[24460] | 25236 | verified | [EquipUI 九数组落位 gate① 2026-11-26 verified] ctor ??0E… |
| 0x2c48c | m_unk_0x2c48c | unsigned char[2064] | 2064 | verified | [EquipUI 九数组落位 gate① 2026-11-26 verified] ctor ??0E… |

#### SaleUI（49 条，跨度 52736 B）

| 偏移 | 现名 | 类型 | 跨度 B | evidence | source 摘要 |
|---|---|---|---|---|---|
| 0x178 | m_unk_0x178 | unsigned char[17504] | 17504 | A | ctor ??0SaleUI(0x45A7B0) site 0x45ACFB rep stosd 0x… |
| 0x45d8 | m_unk_0x45d8 | int | 4 | A | ctor ??0SaleUI(0x45A7B0) site 0x45A8A8 写 0 |
| 0x45dc | m_unk_0x45dc | unsigned char[7040] | 7040 | A | ctor ??0SaleUI(0x45A7B0) 循环 0x45A878–0x45A940，5×0x5… |
| 0x615c | m_unk_0x615c | unsigned char[16] | 16 | A | 相邻构造点空隙 |
| 0x616c | m_unk_0x616c | UIFrameContainer | 152 | A | ctor ??0SaleUI(0x45A7B0) site 0x45A977 ResetContain… |
| 0x6204 | m_unk_0x6204 | unsigned char[84] | 84 | A | ctor ??0SaleUI(0x45A7B0) site 0x45A984 ??0UI3DCtrl；… |
| 0x6258 | m_unk_0x6258 | UIFrameContainer | 152 | A | ctor ??0SaleUI(0x45A7B0) site 0x45A993；dtor ??1Sale… |
| 0x62f0 | m_unk_0x62f0 | unsigned char[164] | 164 | A | ctor ??0SaleUI(0x45A7B0) site 0x45A9A2；dtor ??1Sale… |
| 0x6394 | m_unk_0x6394 | UIFrameContainer[5] | 760 | A | ctor ??0SaleUI(0x45A7B0) site 0x45A98D ??_L(0x98,5)… |
| 0x668c | m_unk_0x668c | unsigned char[104] | 104 | A | 相邻池空隙 |
| 0x10474 | m_unk_0x10474 | unsigned char[240] | 244 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AD54 rep stosd 0x… |
| 0x10568 | m_unk_0x10568 | unsigned char[240] | 4080 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AD61 rep stosd 0x… |
| 0x14618 | m_unk_0x14618 | CCBResultWindow[30] | 5400 | A | ctor ??0SaleUI(0x45A7B0) site 0x45A9FC ??_L(0xB4,30… |
| 0x15b30 | m_unk_0x15b30 | UIFrameContainer[30] | 4560 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AA1E ??_L(0x98,30… |
| 0x16d00 | m_unk_0x16d00 | unsigned char[176] | 176 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AA3C–0x45AA5E 写 0… |
| 0x16db0 | m_unk_0x16db0 | UIProgressBar | 244 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AA6B ?ctor@UIProg… |
| 0x16ea4 | m_unk_0x16ea4 | unsigned char[64] | 64 | A | 相邻构造点空隙 |
| 0x16ee4 | m_unk_0x16ee4 | UIRoleDialog | 1368 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AA8B ??0UIRoleDia… |
| 0x1743c | m_unk_0x1743c | UIFrameContainer | 152 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AA9A；dtor ??1Sale… |
| 0x174d4 | m_unk_0x174d4 | UIFrameContainer | 152 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AAA9；dtor ??1Sale… |
| 0x1756c | m_unk_0x1756c | UIFrameContainer | 152 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AAB8；dtor ??1Sale… |
| 0x17604 | m_unk_0x17604 | unsigned char[168] | 168 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AAC7；dtor ??1Sale… |
| 0x176ac | m_unk_0x176ac | unsigned char[344] | 344 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AAD6 GetSys(注解名)；… |
| 0x17804 | m_unk_0x17804 | unsigned char[344] | 344 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AAE5；dtor ??1Sale… |
| 0x1795c | m_unk_0x1795c | unsigned char[168] | 168 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AAF4；dtor ??1Sale… |
| 0x17a04 | m_unk_0x17a04 | UIFrameContainer | 152 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AB03；dtor ??1Sale… |
| 0x17a9c | m_unk_0x17a9c | UIFrameContainer[13] | 1976 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AAFE ??_L(0x98,13… |
| 0x18254 | m_unk_0x18254 | UIFrameContainer | 152 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AB21；dtor ??1Sale… |
| 0x182ec | m_unk_0x182ec | UIFrameContainer | 152 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AB30；dtor ??1Sale… |
| 0x18384 | m_unk_0x18384 | unsigned char[1224] | 1224 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AB3F sub_43DFC0；d… |
| 0x1884c | m_unk_0x1884c | unsigned char[344] | 344 | A | dtor ??1SaleUI(0x45AE60) 0x45AFF8 ?Destroy2@UICapti… |
| 0x189a4 | m_unk_0x189a4 | unsigned char[404] | 404 | A | 相邻构造点空隙 |
| 0x18b38 | m_unk_0x18b38 | UIFrameContainer | 152 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AB7A；dtor ??1Sale… |
| 0x18bd0 | m_unk_0x18bd0 | unsigned char[168] | 168 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AB89；dtor ??1Sale… |
| 0x18c78 | m_unk_0x18c78 | unsigned char[168] | 168 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AB98；dtor ??1Sale… |
| 0x18d20 | m_unk_0x18d20 | unsigned char[168] | 168 | A | ctor ??0SaleUI(0x45A7B0) site 0x45ABA7；dtor ??1Sale… |
| 0x18dc8 | m_unk_0x18dc8 | unsigned char[168] | 168 | A | ctor ??0SaleUI(0x45A7B0) site 0x45ABB6；dtor ??1Sale… |
| 0x18e70 | m_unk_0x18e70 | unsigned char[364] | 364 | A | dtor ??1SaleUI(0x45AE60) 0x45AF98 ?Destroy2@UICapti… |
| 0x18fdc | m_unk_0x18fdc | unsigned char[360] | 360 | A | dtor ??1SaleUI(0x45AE60) 0x45AF88；邻接 360 |
| 0x19144 | m_unk_0x19144 | unsigned char[360] | 360 | A | dtor ??1SaleUI(0x45AE60) 0x45AF78；邻接 360 |
| 0x192ac | m_unk_0x192ac | unsigned char[360] | 360 | A | dtor ??1SaleUI(0x45AE60) 0x45AF68；邻接 360 |
| 0x19414 | m_unk_0x19414 | unsigned char[344] | 344 | A | dtor ??1SaleUI(0x45AE60) 0x45AF58；344B；段长 344 与 IDB… |
| 0x1956c | m_unk_0x1956c | unsigned char[344] | 344 | A | dtor ??1SaleUI(0x45AE60) 0x45AF48；344B；段长 344 与 IDB… |
| 0x196c4 | m_unk_0x196c4 | unsigned char[344] | 344 | A | dtor ??1SaleUI(0x45AE60) 0x45AF38；344B；段长 344 与 IDB… |
| 0x1981c | m_unk_0x1981c | unsigned char[344] | 344 | A | dtor ??1SaleUI(0x45AE60) 0x45AF28；344B；段长 344 与 IDB… |
| 0x19974 | m_unk_0x19974 | unsigned char[376] | 376 | A | dtor ??1SaleUI(0x45AE60) 0x45AF18；邻接 376 |
| 0x19aec | m_unk_0x19aec | unsigned char[154] | 154 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AC63；dtor ??1Sale… |
| 0x19b86 | m_unk_0x19b86 | unsigned char[256] | 256 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AC81 lstrcpyA 目标；… |
| 0x19c86 | m_unk_0x19c86 | unsigned char[306] | 306 | A | ctor ??0SaleUI(0x45A7B0) site 0x45AC86 lstrcpyA 目标；… |

---

## 7. 约束自证（只读）

- **未改 annotation / 基线 / 生成树**：本卡写面仅 `docs/audit/`（见下 git status）。`data/annotations/structs/` 的 `M` 项均为并发卡：`RoleStatePanel.json`（#8，+1 `base_size`）、`SaleUI.json`（#9，+371/−358）、`UIFrameContainer.json`（#8，+1），本卡未写入。
- **未跑管线**：扫描期间 `ps` 可见另一卡启动的 `probe all`（`timeout 1200 python3 pipeline/cli.py probe all`，PID 4114225/4114226，21:39 启动），本卡未启动任何 `pipeline/cli.py`、未跑 loop/apply/export/codegen。
- **未执行改名**：91 条全部原样保留；本包只统计。
- **产物可重跑**：`python3 docs/audit/munk_census_20261126.py --json /tmp/x.json` 在 10 秒内复现 §1 输出；若 SaleUI 已被 #9 提交/回退，`exact` 条数应在 42–91 之间变化，脚本会如实报出。

```bash
$ git status --short docs/audit data/annotations/structs
?? docs/audit/
 M data/annotations/structs/RoleStatePanel.json
 M data/annotations/structs/SaleUI.json
 M data/annotations/structs/UIFrameContainer.json
```

## 8. 未决事项

1. **538 的来源**：已确认只在交接文档、由 `e4378a1c4` 引入；是否为某次未落档的临时扫描值，无法从仓库证据判定 → 不再追，按 P1 作废处理。
2. **SaleUI 49 条的最终形态**：取决于 #9 验收结果（可能被调整/回退），本包的 49 需在 #9 落地后重扫确认。
3. **批 A 的正名清单**：本包只给出「≤28 条可命名」的边界，具体每个成员叫什么必须由实施卡逐条取证（source 里的 ctor/disp 线索 + 消费面），本包不代拟名字。
