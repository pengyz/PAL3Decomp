# C 批执行方案（容器缺口填充 + 布局前置修复）——2026-09-27 草案 v1，待对抗复核

目标（goal 口径）：CEffMgr + SceneMgr 的 known_members 覆盖缺口填充（原方案 263/165），
SceneMgr 布局修复为强制前置。全程 annotation 证据规则 + 四道门 + 逐步对抗复核。

## 0. 现状实测（2026-09-27 12:5x，globals_census.json 现读）
- B2 行共 437（census 总 2035）：g_EffMgr **263**（方案数字未变）、g_SceneMgr **129**
  （方案 165 已随 sub_4B43E0 归属修复 + CGameData+1 漂移，**以现测为准并报告差异**）、
  g_CPKPackFiles 18、g_ScriptSystemData 26、g_ScriptCounters 1。
- CEffMgr 263 分布：**138 个落在 m_sz5D8C3C char[29028] @+0x37B8 跨度 [0x37B8,0xA91C) 内**
  （blob 是未探索区占位，尺寸恰好闭合 0xA930=binary_size），125 个散在既有成员之间
  （+0x8..+0xA8E8，含 0xB64 等已知成员的间隙）。
- extern 自带语义名样例：aBink/aShock/aMeteor/aExplosive/aGrid（+0x8..+0x34，间距 8-12B，
  像名称串表）；IDA type 字段（RenderTarget2/CEffMgr/CEffectSystem）是垃圾猜测，不可用。
- 布局现状（audit_type_layout 编译器裁判，2026-09-27 新读数）：SceneMgr 1/167 冲突
  （仅 _gap_C812 实际 0xC810，−2）、CEffMgr 7/48（幽灵成员 +10288 级联）、
  ScriptSystemData/CGameData/RoleSystem/CPK 0 冲突。

## 1. 病灶层检查（CLAUDE.md 红线，动任何跨层代码前的三问）
1. **病灶在哪一层**：
   - CEffMgr 7 处布局冲突 ⇒ annotation 层（m_nTodo_80EC/_gap_80F0 幽灵成员，源注仅
     ida_gap_1refs 弱启发）；
   - SceneMgr _gap_C812 −2 ⇒ **codegen 发射层**（emit_headers.py:2073 pack(1) union 台账
     用自然对齐尺寸 404，编译实际打包尺寸 402）；
   - 容器缺口 ⇒ annotation 层（known_members 覆盖 7%）。
2. **消费者实际读哪个文件**：生成头权威源 = `asm/pal3/ida_structs.json`（apply→export 回灌，
   emit_headers.py:1932-1965）；stage4 解析读 struct_instances（globals type + IDB UDT size）+
   known_members（stage4_substitution.py:207-271）；globals 级 binary_size 无消费者（勿写）。
3. **报错还缺什么**：263+129 各偏移的三形态访问证据（绝对地址 G+off / 符号名渲染 / memcpy 区间）；
   新成员语义命名证据（K 类字符串仅 C 级，只命名不证位移）。

## 2. C0 布局前置修复（顺序强制：先于一切成员化）
### C0a CEffMgr 幽灵成员删除（annotation 层）
- 删 `m_nTodo_80EC`@0x80EC + `_gap_80F0`@0x80F0。四证（_b_batch_premeasure.md §CEffMgr 终裁）：
  (a) 与 char[29028] 跨度物理重叠（注解内部矛盾）；(b) 28 个 CEffMgr 方法 census 零访问；
  (c) 源注仅 ida_gap_1refs 弱启发且伪语义名；(d) 删除后 7 处冲突全归零可当场编译器裁判复核。
- 落地：守卫新增 **delete_member** kind（evidence 硬约束 + 防陈旧：key 存在且 name 匹配）
  → 逐条批次 → annotation_diff → **apply→export** → `audit_type_layout --only CEffMgr`
  （期望 7/48 → 0/46）→ verify_fix --class CEffMgr → 四道门。
### C0b SceneMgr 发射层根修（codegen 层，跨层 ⇒ 严格走病灶层检查写入 commit）
- 修 emit_headers.py:2073：pack(1) union 的台账 `member_size` 改用**打包尺寸**——
  递归求 variant 打包 extent（struct=成员打包尺寸求和不补对齐、数组=打包元素×计数、
  union=各 variant 打包尺寸取 max、指针/标量=自然大小），与 pack(1) 发射的真实编译尺寸一致。
  ⇒ SceneMgr gap 自动变 `_gap_C810[56]`，冲突归零。
- 波及面：inline union 10 处（FightItem/MUIDialog/PalScript×2/RoleAtt/RoleSystem×2/
  SceneMgr/tagCam/tagCmdData/tagRoleTask）。全 10 类跑 audit_type_layout 复核；
  **等价性门 = 全部类布局读数不降**（当前全绿类不得出新冲突）。
- 备选 (b)（若 (a) 波及失控）：注解层补 `char _unkC810[2]`——不动管线但拆分任意，仅作回退。
- 发射层新增打包尺寸函数必须配纯函数单测（R15）。
- **本步独立对抗复核通过后才可进 C1**。

## 3. C1 成员化（CEffMgr 263 / SceneMgr 129，按容器分批）
### 证据纪律（每成员）
- 三形态访问证据（归属复核 §3.4）：绝对地址 G+off 命中 / 符号名渲染点 / memcpy 区间；
  0 命中 ⇒ 降 B8/padding，**不给类型不给名**（诚实缺口）。
- 位移/宽度证据复用 B 批 type_evidence（T1 绝对地址形态对数据对象是主信号：
  tagEffMgrData 93/93 实测）；方法内 [reg+disp32] 形态经 T1b（access_map ECX provenance）
  ——CEffMgr 28 方法 46 偏移有 this+disp 证据，是 in-blob 成员的主证据源。
### 命名纪律（CLAUDE.md 红线）
- 禁伪语义（m_nTodo_80EC 这类地址后缀名本就违禁）；语义可证（K 类字符串渲染）给语义名
  + name_evidence；否则 `_todo_` 风格诚实名 + "含义未定"。
- extern 现名（aShock/aMeteor…）按 IDA 惯例是串表名：仅作 C 级语义线索，名字落盘须过
  守卫 name_evidence。
### in-blob 138 个（CEffMgr 特有设计点，须复核裁定）
- m_sz5D8C3C char[29028] 是未探索区占位。两种切法：
  (甲) **拆 blob**：按证据偏移切出成员 + `char _pad_XXXX[n]` 间隙段，删 m_sz5D8C3C。
      风险：任何 decomp 对 m_sz5D8C3C 的现有渲染引用随重 decomp 全量更名（走全链自洽）。
  (乙) **union 视图**：+0x37B8 改 `{"union":[char[29028], {struct:[证据成员+相对偏移]}]}`。
      风险：known_members 键仍是 0x37B8 单键，**stage4 的 known_member 回退能否解析内层
      偏移未验**——若不能，成员化零收益。
  ⇒ **倾向 (甲)**：stage4 按精确偏移查 known_members，拆 blob 才让 138 个偏移可解析；
     但须先实测 m_sz5D8C3C 在 decomp/生成头的现存引用数（0 则 (甲) 无痛）。
### 落地链（每类一批，顺序 CEffMgr 先、SceneMgr 最后）
守卫新增 **add_member** kind（class/key/offset/name/type/evidence/name_evidence；
防重叠：新偏移不得落进既有成员跨度，union 除外）→ 逐类批次 → annotation_diff →
**apply→export** → codegen → `audit_type_layout --only <Cls>`（0 新冲突）→
`verify_fix --class <Cls>` → 四道门（布局等价 / loop --expect-errors 不增 / L1 不降 /
证据自校验）→ 逐步对抗复核。

## 4. 门禁与度量
- 每批四道门全过 + verify_fix；错误多重集不增（C1003 截断单元按"列表内最大行号"判）。
- 全批后：census 直方图 B2 缺口只降不升；loop --expect-* 对账；知识回写
  （gotcha_emitted_layout_drifts_from_annotated_offsets 的 101/169 陈旧量化一并更正）。
- 棘轮：`data/status/_c_batch_ledger.md` 记每批 (成员数/证据形态分布/门禁读数)。

## 5. 已知风险清单（交对抗复核重点攻击）
R1 (甲)/(乙) 切法的 stage4 解析实测未做——最大设计不确定性。
R2 263/129 中可能有 extern 是**独立对象误落容器 extent**（分区规则 §3.3：inner 有独立生命
   证据 ⇒ outer extent 收缩，不是成员化）——成员化前须过三形态 + 独立 ctor/atexit 无锚检查。
R3 aShock 类名的语义推断可能翻车（串表 vs 成员名）；命名宁缺勿滥。
R4 emit_headers 打包尺寸函数对嵌套 inline struct/union 的递归正确性（必须纯函数单测）。
R5 SceneMgr 129 与方案 165 的差异须在产物里解释（漂移来源：sub_4B43E0 归属修复吃掉部分）。
R6 T1b（this+disp）信号接入 type_evidence v2 仍未实现——in-blob 成员的宽度/类型证据
   将依赖 T1b，需在 C1 前补（或用 audit_member_semantics.py 三形态工具兜底）。
