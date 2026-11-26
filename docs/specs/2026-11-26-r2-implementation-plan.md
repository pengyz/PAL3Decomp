# R2 实施计划：EquipUI 尾区九数组落位 + RoleStatePanel 七模块指针

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** R2 轮——EquipUI 尾区 9 笔 ??_L 数组落位（~229KB 洞主体）+ RoleStatePanel 七模块指针落位（侦查修正：宿主非 EquipUI）；每步后强制子 agent 对抗复核门。

**Architecture:** 同 R1 四段式（探针→落位→对抗复核→管线），证据=??_L 字面量三元组（type,count,size,ctor,dtor）+ 金表 + 消费面。

**Tech Stack:** 同 R1（idalib/pipeline/cli.py/census_struct_holes.py）

**Spec:** docs/specs/2026-11-26-struct-hole-filling-campaign-design.md §2 R2/R3（侦查修正：七指针宿主=RoleStatePanel，归入本计划 T3；spec 轮次总量不变）

## Global Constraints

- 同 R1 全部红线（N12/六证择二/PDB 单证不定谳/每步对抗复核门/ctor 三件套/check 门禁/头树陷阱/基线归因刷新）
- 函数命名遵循 C++ 重载规则（禁数字后缀）；数据成员真语义名，无证据不注
- 元素类命名：??_L ctor 回调函数名=元素类名钥匙（SceneBuf 先例：??_L(g_SceneBuf,3,0x78664,ctor=?Reset@SystemUI@@…)）；ctor 名与注解类名对齐才可落类型，对不齐→元素类型留 byte 序列+note（禁发明名）
- `binary_size_contested` 式冲突注记为合法中间态；void* 透明指针为合法未名类指针形（gbSingleton 先例）

**关键既证事实（侦查探针 data/status/probe_equipui_tail_20261126.json）：**
1. **七指针宿主=RoleStatePanel**（0x2B080=176256 金表闭合）：Init@0x4A4220（mangle ?Init@EquipUI 名义性错挂）真接收者=UIGameFrm+0x6E14 缓存的 RoleStatePanel 实例（new 0x2B080+InitUI@RoleStatePanel 构造）；七槽 [esi+0x2AFB8..0x2AFD0] 全走该实例；消费面 27/26/26/26/15/14/9 读点全活
2. **EquipUI 尾区 9 笔 ??_L 数组**（ctor 内联原位构造，无 memset）：
   | 基址 | 元素数 | 步距 | 末端 |
   |---|---|---|---|
   | 0x1414 | 128 | 584 | 0x13814 |
   | 0x13814 | 128 | 584 | 0x25C14 |
   | 0x261F8 | 5 | 0x131C(4860) | 0x2C184 |
   | 0x2C48C | 6 | 0x158 | ~0x2CDB4* |
   | 0x2CC9C | 6 | 0xF8 | ~0x2D3C4* |
   | 0x2D3F0 | 152 | 0xC | 0x2E0A0* |
   | 0x2F760 | 5 | 52 | 0x2F7C4* |
   | 0x2FE04 | 60 | 584 | 0x386E4 |
   | 0x386E4 | 60 | 584 | 0x40FC4 |
   （*号=探针初值，Task 1 精确化；584=UIParticle 尺寸嫌疑（CCBCamControl 填充物同期同值）——Task 1 验证）
3. EquipUI 现 90 员，尾区内已 57 员（最大末端 0x1D470）——落位前须核对新数组与既有 57 员的几何关系（重叠=既有员证伪退役，遵循 R1 整表重建纪律）
4. SkillUI 重挂修正数字：实消 2440B（m_Task tagUITask[19]=1368B 数组跨度）

---

### Task 1: 九数组元素类鉴定探针

**Files:**
- Create: `tools/probe_equipui_arrays_20261126.py`
- Create: `data/status/probe_equipui_arrays_20261126.json`

**Interfaces:**
- Produces: 九笔 ??_L 的 {offset,count,stride,ctor_fn,dtor_fn,element_class_candidate}——Task 2 落位类型钥匙

- [ ] **Step 1.1: 写探针**——扫 EquipUI ctor(0x498820) 及其内联构造区的 9 笔 ??_L 调用，解三元组 (push type / push count / push size / ctor 回调地址 / dtor 回调地址)，回调地址反 mangle 得元素类名（如 ?Reset@SystemUI@@→SystemUI；??0X@@→X）
- [ ] **Step 1.2: 跑探针+元素类对账**——element_class_candidate 与 data/annotations/structs/ 现有类名对齐（存在且 binary_size==stride → 类型可用；不存在或尺寸不合 → candidate=unknown）
- [ ] **Step 1.3: 对抗复核门①**——子 agent 独立反汇编 9 笔 ??_L 现场复算三元组+回调名，裁决 element_class_candidate 对齐逻辑；真 bug 修复重跑

### Task 2: EquipUI 九数组落位

**Files:**
- Modify: `data/annotations/structs/EquipUI.json`
- Modify: `data/status/equipui_r2_adjustments_20261126.json`（新建：与既有 57 尾区员的几何对账）

**Interfaces:**
- Consumes: Task 1 element_class_candidate
- Produces: EquipUI known_members 增 ≤9 数组员（type=ElemClass[N] 或 unsigned char[N×stride]（元素 unknown 时的诚实字节序列形+note））

- [ ] **Step 2.1: 几何对账**——9 数组区间 vs 既有 57 尾区员逐一比对：重叠员=证伪退役（R1 纪律，进 adjustments 台账）；相邻员保持
- [ ] **Step 2.2: 落位**——9 员按 Task 1 类型落位（evidence_level=verified，source=??_L 三元组+offset+stride+回调名）；元素 unknown 者落 `unsigned char[整体跨度]`+note"元素 584B stride，类名待鉴定"（诚实字节形，禁发明名）
- [ ] **Step 2.3: check+census**——check PASS（新 N13a 冻结走过渡协议）；census 记录 EquipUI 洞变化（预期 164KB→数十 KB 级）
- [ ] **Step 2.4: 对抗复核门②**——独立复算 9 区间几何+对账+落位类型+check/census；真 bug 修复

### Task 3: RoleStatePanel 七模块指针落位

**Files:**
- Modify: `data/annotations/structs/RoleStatePanel.json`
- Modify: `data/status/equipui_r2_adjustments_20261126.json`（追加）

**Interfaces:**
- Consumes: 侦查七槽证据（消费面 27/26/26/26/15/14/9 读点）
- Produces: RoleStatePanel known_members 增 7 指针员（+0x2AFB8..0x2AFD0）

- [ ] **Step 3.1: 类型定谳**——七槽 pointee：+0x2AFC0=MainPropUI*(219984)/+0x2AFC4=EquipUI*(266260)/+0x2AFCC=LineupUI*(162772) 三命名类直落；+0x2AFB8(171244 类)/+0x2AFBC(353840 类)/+0x2AFC8(402824 类Y)/+0x2AFD0(UITitle_JDHY 290488 vs 注解 377700 争议)——未名/争议类落 `void *`+note（透明指针先例；类型名等类身份定谳，禁发明）
- [ ] **Step 3.2: 落位+check+census**——7 员 verified（source=分配+存储+消费面三证）；check PASS；census 记录 RoleStatePanel 变化（152KB 洞中 [0x2AFB8,0x2AFD0] 28B 落位+尾区语义锚定，大头留给 R3 disp 普查）
- [ ] **Step 3.3: 对抗复核门③**——独立验证七槽消费面+类型定谳三命名/四透明；RoleStatePanel bases 变更无（不动 bases）；裁决表

### Task 4: 管线段（loop 全链）

- [ ] **Step 4.1: loop**——同 R1 T7 预案（codegen 夭折→独立 codegen all；probe 回归→归因带回；S2/L1 记录）
- [ ] **Step 4.2: N13a 过渡**——新 N13a 冻结（退役员语料引用），loop 重渲后解冻验证
- [ ] **Step 4.3: 对抗复核门④**——loop 读数+S2/L1+churn 归因复核

### Task 5: 落账段

- [ ] **Step 5.1: 提交+push**（commit-msg Evidence 格式；清单=EquipUI/RoleStatePanel.json+adjustments 台账+探针+status 族）
- [ ] **Step 5.2: census 重跑+记忆更新+ledger 终记**

## 明确不做（R2 范围外）

- 171244/353840/402824 三未名类的类名定谳（R6/命名战役）
- UITitle_JDHY 尺寸仲裁（Note_Item 双布局，挂账批）
- EquipUI 尾区 57 既有员中非重叠者的逐员重取证（后续轮）
- RoleStatePanel 尾区 disp 普查主体（R3 主攻）
