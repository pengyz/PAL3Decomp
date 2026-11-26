# R1 实施计划：CCBCamControl 整表重建 + SkillUI 退赔重挂

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** R1 轮——CCBCamControl 洞（348KB）按孪生定谳整表重建（池/句柄表落位+17 员冲突面退役），副线 SkillUI 53 退赔重挂；每步后强制子 agent 对抗复核。

**Architecture:** 注解考古四段式（探针取证→注解落位→对抗复核→管线验证），所有证据走 idalib 探针产物落档；本计划只覆盖 spec R1，R2-R6 各自另立计划。

**Tech Stack:** idalib（/home/peng/ida-pro-9.1/idalib/python，DB=original/PAL3.exe.i64）、python3、pipeline/cli.py（check/loop）、tools/census_struct_holes.py

**Spec:** docs/specs/2026-11-26-struct-hole-filling-campaign-design.md（§2 R1、§3 流程、§4 红线随本计划生效）

## Global Constraints

- N12 无证据不名：禁 slot_N/sub_/unk_ 占位语义名；无证据区不填充
- 六证择二：ctor 写序/disp 聚类/工厂解码/调用点 ecx 回溯/PDB mangle/金表字面量
- **PDB 单证不定谳**（本族构建漂移实锤），须与二进制证据组合
- 池计数无字面量（push 0x7D0/最大句柄上界）→ 不上 `tagCCT[2000]`，走推迟分支（轮预期 −22KB）
- 每个落位成员 `evidence_level + source` 齐备；ctor 三件套=类名+`flags:["ctor"]`+sig 返 this/void
- 每完成一步（Task 内所有动作步后）必须派子 agent 对抗复核门，真 bug 当步修复不带病前进
- annotation 改动必须过 `python3 pipeline/cli.py check`；轮门=`cli.py loop` 全链绿（恒红 codegen 容错）
- codegen 失败→先独立 `python3 pipeline/cli.py codegen all` 完成头树再生再 loop（头树部分再生陷阱）
- 回归门基线刷新必须带归因；±10% 验收基准=预期中值

**关键既证事实（执行者无需重推，直接引用）：**
- 句柄表锚 = **0x64190**（idx=T+50L+102500，4×102500=410000=0x64190；+20000=0x68FB0=430000 精确闭合；行步距 200B=50 项/行）
- 池条目寻址 = `this + 204×handle`（shl4→×17→×3→×4 乘法链）；tagCCT.json binary_size=204 已闭合
- 池计数 2000 **无代码字面量证据**（push 0x7D0 全库零命中）；m_bPoolInUse 独立数组模型已证伪（状态字节在条目内 +0x59/5A/5B）
- CCBCamControl ctor = 0x5052e0（已 verified，flags=["ctor"]）
- 冲突面 17 员名单（复核 C8）：12 unverified（m_pvecCenter@0x8/m_nTodo_00C@0xc/m_nTodo_010@0x10/m_fCamBlendA@0x34/m_fCamBlendB@0x38/m_CamCtrlData@0x3c/m_nTodo_EC@0xec/m_PanelSlots@0x260/m_nList@0x984/m_nPointerUnderMouse@0x988/m_CamEntries@0x98c/m_nCurCamIdx@0x2594）+ m_nCurPageTab@0x5558 + 4 A级已证伪填充物（m_RenderQueue UIParticle[98]@0x3cfb8/m_SelectRect int[4]@0x4af48/m_SlotButtons UIButton[5]@0x5d9ec/m_TabLists _BYTE[6040]@0x5f360）
- 尾域 42 员（0x68FB0..0x690AE）已 verified 不动（含 m_nCurList@0x68FD0/m_nCurTask@0x68FD4）
- SkillUI 退赔台账 = data/annotations/archive/ccbui_identity_adjudication_20261121.json，**53 条 retired_members**（0x94~0x4b8+0xa30，均 unverified）+4 kept

---

### Task 1: 池计数取证探针

**Files:**
- Create: `tools/probe_ccbcamcontrol_poolcount_20261126.py`
- Create: `data/status/probe_ccbcamcontrol_poolcount_20261126.json`

**Interfaces:**
- Consumes: 池寻址事实（this+204×handle）、池方法地址（InsertTaskToList 0x5075e0/SwapTask 0x507b20/ClearList 0x508190/Init@0x5061a0/InitEntries 0x44d780/CCCTData_6F10 0x4a6f10）
- Produces: `pool_count_evidence` 字段 ∈ {literal:"0x7D0", bound:N} 或 {unresolved:true}——Task 3 据此走落位或推迟分支

- [ ] **Step 1.1: 写探针脚本**

```python
#!/usr/bin/env python3
"""probe_ccbcamcontrol_poolcount_20261126.py — 池计数取证。
三查: ①池初始化函数族的 0x7D0/2000 字面量(push/cmp/mov imm)
②句柄表区 [0x64190,0x68FB0) 的 -1 哨兵与上界 cmp 常量
③m_nCurList/m_nCurTask@0x68FD0/D4 写入点的常量上界"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64', run_auto_analysis=False)
import idc, ida_funcs, idautils
OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_ccbcamcontrol_poolcount_20261126.json'
TARGETS = {0x5075e0:'InsertTaskToList', 0x507b20:'SwapTask', 0x508190:'ClearList',
           0x5061a0:'Init', 0x506020:'Create', 0x44d780:'InitEntries',
           0x4a6f10:'CCCTData_6F10', 0x4a8770:'Create_8770', 0x5058f0:'copyctor_58f0'}
report = {'literal_hits': [], 'bound_hits': [], 'table_sentinel': []}
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    if not f: continue
    cn = idc.get_func_name(f.start_ea)
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 5000:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        if re.search(r'\b(push|cmp|mov)\b.*\b(7D0h|2000)\b', t):
            report['literal_hits'].append({'func': cn, 'site': hex(cur), 'line': t})
        cur = idc.next_head(cur, f.end_ea)
        n += 1
# 句柄表写入点: [reg+64190h..68FB0h] 区间的 cmp 上界
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    if not f: continue
    cn = idc.get_func_name(f.start_ea)
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 5000:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        if re.search(r'cmp\s+e?[a-z]{2},\s*[0-9A-Fa-f]{1,4}h', t):
            m = re.search(r'cmp\s+e?[a-z]{2},\s*([0-9A-Fa-f]{1,4})h', t)
            v = int(m.group(1), 16)
            if 32 <= v <= 4096:
                report['bound_hits'].append({'func': cn, 'site': hex(cur), 'val': v, 'line': t})
        cur = idc.next_head(cur, f.end_ea)
        n += 1
json.dump(report, open(OUT, 'w'), indent=1)
print('literal_hits:', len(report['literal_hits']), 'bound_hits:', len(report['bound_hits']))
idapro.close_database(False)
```

- [ ] **Step 1.2: 跑探针**

Run: `timeout 550 python3 tools/probe_ccbcamcontrol_poolcount_20261126.py`
Expected: 输出 literal_hits/bound_hits 计数并落 JSON

- [ ] **Step 1.3: 解读产出（落位或推迟判定）**

判定规则：literal_hits 中存在池方法族（TARGETS 内）或其调用者的 `0x7D0` 写/比较 → count=2000 有证；bound_hits 中存在句柄表访问上下文的稳定上界（如 cmp eax,0x7D0）→ 同上。否则 unresolved=true。

- [ ] **Step 1.4: 对抗复核门①（子 agent）**

派 general-purpose 子 agent，prompt 要旨：「独立复核 /tmp 外的 data/status/probe_ccbcamcontrol_poolcount_20261126.json：①重写独立探针（不 import 原脚本）复扫 0x7D0/2000 字面量与句柄表 cmp 上界，比对命中集 ②复核 Step 1.3 判定逻辑是否把无关函数的 2000 常量误归池 ③裁决表：真 bug 须修/近似/口径题」。复核通过才进 Task 2；发现真 bug 修探针重跑。

---

### Task 2: 句柄表落位 @0x64190

**Files:**
- Modify: `data/annotations/structs/CCBCamControl.json`（known_members 增员）
- Modify: `data/annotations/structs/CCCTData.json`（同步删 m_nCCTIndex——防 chimera，复核 C8）

**Interfaces:**
- Consumes: 0x64190 锚（4×102500 闭合）、Task 1 的 L 上界（如有）
- Produces: CCBCamControl.json 新成员键 `"0x64190"`；后续 census 重跑时该 20000B 区计覆盖

- [ ] **Step 2.1: 注解编辑（python 直改）**

```python
import json
p = 'data/annotations/structs/CCBCamControl.json'
d = json.load(open(p, encoding='utf-8'))
km = d['known_members']
km['0x64190'] = {
    'name': 'm_TaskListIndex',
    'type': 'int[100][50]',   # 行步距200B=50项/行(公式 entry(L,T)=0x64190+200L+4T); L行数上界100=闭合0x68FB0, 待Task1上界佐证, 如Task1给出更小上界则改
    'evidence_level': 'verified',
    'source': '2026-11-26 R1: idx公式T+50L+102500 -> 基址4x102500=0x64190(410000), +20000=0x68FB0=430000精确闭合(=binary_size尾域起点); 访问形 lea eax,[eax+eax*4+280Ah]/lea eax,[eax+eax*4]/lea edx,[edx+eax*2]/mov edx,[ecx+edx*4] (InsertTaskToList 0x5075e0/SwapTask 0x507b20 双方法同式); 行步距200B=50项/行; 探针 data/status/probe_ccbcamcontrol_pooldecode_20261126.json',
}
json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
# 同步删 CCCTData.json 的 m_nCCTIndex(错挂域)
p2 = 'data/annotations/structs/CCCTData.json'
d2 = json.load(open(p2, encoding='utf-8'))
removed = d2['known_members'].pop('0x64190', None)
json.dump(d2, open(p2, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('CCBCamControl +m_TaskListIndex; CCCTData -m_nCCTIndex:', removed is not None)
```

- [ ] **Step 2.2: check 门禁（含闭合预验算）**

预验算（计划自审修正稿）：0x64190 + 20000B(int[100][50]) = **430000 = 0x68FB0** = 尾域起点（m_pStage 偏移），< binary_size 0x690B0(430256)——**精确闭合无越界**，与尾域 42 员零重叠，与 0x64190 之前最近成员 m_TabLists@0x5f360(末端 0x60AF8)无重叠。MemberExtent 应放行。

Run: `python3 pipeline/cli.py check 2>&1 | grep -E "new errors|PASS|FAIL"`
Expected: PASS（若被拦，按拦截名单回查本预验算遗漏，不得擅自砍 dims——砍行数须复核门②裁决）

- [ ] **Step 2.4: 对抗复核门②（子 agent）**

派子 agent：「独立复算 0x64190 锚与 int[100][50] 闭合算术（从 probe_pooldecode JSON 的 idx 公式原始反汇编行起，不用本计划数字：基址=4×102500？末端=0x68FB0？是否<binary_size 0x690B0？是否恰为尾域起点？）；核对 CCBCamControl.json 新成员 source 证据链与 CCCTData.json 删除对称性；行数 100 是布局闭合推导而非计数字面量——裁决是否违反'计数无证不上注解'红线（行数=几何闭合 vs 池计数=运行时数量，两律适用面不同）；裁决表」。

**计划自审更正记录**：初稿 Step 2.2/2.3 曾误算 0x64190+20000=0x69190（幻影越界）——正确值 430000=0x68FB0，恰闭合于尾域起点。该错误由本计划自审环节抓出并删除整段幻影回退逻辑（Step 2.3 撤销）。

---

### Task 3: 池落位或推迟分支

**Files:**
- Modify: `data/annotations/structs/CCBCamControl.json`（池有证时增 m_Pool）或仅落档推迟注记
- Modify: `data/annotations/structs/CCCTData.json`（同步删 m_Pool/m_bPoolInUse 两员——复核 C8 防 chimera；其内容已被证伪/错挂）

**Interfaces:**
- Consumes: Task 1 的 `pool_count_evidence`
- Produces: 池落位 → 洞收 −335KB 级；推迟 → −22KB 分支（轮预期重排）

- [ ] **Step 3.1: 分支执行**

若 Task 1 判定 count 有证（值=N）：
```python
import json
p = 'data/annotations/structs/CCBCamControl.json'
d = json.load(open(p, encoding='utf-8'))
d['known_members']['0x0'] = {
    'name': 'm_Pool',
    'type': 'tagCCT[%d]' % N,
    'evidence_level': 'verified',
    'source': '2026-11-26 R1: 寻址 this+204*handle(shl4->x17->x3->x4 乘法链, InsertTaskToList 0x5075e0); tagCCT=204 已闭合; 计数字面量 %s (探针 probe_ccbcamcontrol_poolcount)' % 证据位置,
}
json.dump(d, open(p, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
```
若 unresolved：在 CCBCamControl.json 类级加 `"pool_count_deferred": "2026-11-26 R1 推迟: 计数字面量未获(探针poolcount), 池区[0,?x204)留洞诚实呈现"`（若该字段被 N16 schema 拒——先跑 check 验证，被拒则改放 source 注记到 m_nCurList 成员）。

同步删除 CCCTData.json 的 `m_Pool`/`m_bPoolInUse` 两员（chimera 防复刻；退役理由写入删除时留档的 adjudication 记录文件 data/status/ccbcamcontrol_r1_retirement_20261126.json——含每员 name/offset/退役理由/原证据引用）。

- [ ] **Step 3.2: check 门禁**

Run: `python3 pipeline/cli.py check 2>&1 | grep -E "new errors|PASS|FAIL"`
Expected: PASS（池落位时注意 [0x0,0x63xxx) 与现有头域成员的 MemberExtent——由 Task 4 统一处理冲突面，此处若被拦属预期，记录拦截名单供 Task 4）

- [ ] **Step 3.3: 对抗复核门③（子 agent）**

派子 agent：「复核分支判定是否符合 Task1 证据（有无字面量误读）；池落位时 N 的算术闭合（204×N ≤ 0x639C0 且边界自洽）；CCCTData 删除对称性与退役台账完整性（三员全删、理由充分）；推迟分支时注记落位是否合规（N12）；裁决表」。

---

### Task 4: 冲突面 17 员整表重建

**Files:**
- Modify: `data/annotations/structs/CCBCamControl.json`（退役/重取证 17 员）
- Create: `data/status/ccbcamcontrol_r1_retirement_20261126.json`（退役台账）

**Interfaces:**
- Consumes: 复核 C8 名单、孪生定谳 v1 证伪记录（4 填充物）、Task 2/3 落位结果
- Produces: CCBCamControl.json 头域净表（仅保留有证据成员）；退役台账（每员 name/offset/退役理由/原证据引用）

- [ ] **Step 4.1: 4 个 A 级证伪填充物退役**

m_RenderQueue UIParticle[98]@0x3cfb8 / m_SelectRect int[4]@0x4af48 / m_SlotButtons UIButton[5]@0x5d9ec / m_TabLists _BYTE[6040]@0x5f360——从 known_members 删除，退役理由=孪生定谳 v1 证伪（跨度非整数闭合 6516/5 等）+复核 C8。写入退役台账。注意：这些区落回洞后，corpus（CCBCamControl.cpp）对这些成员的引用将渲染为裸偏移——编译可行，错误数 churn 归 Task 7 归因。

- [ ] **Step 4.2: 13 员逐个重取证裁决**

对 12 unverified + m_nCurPageTab@0x5558 逐员查证：语料渲染证据（asm/pal3/decomp/ 中 grep 该名）+ disp 访问证据（probe_ccbcamcontrol_census JSON）。三态：**留**（有具体访问证据且不与池/表区间冲突——头域 [0x40,0xec) 有 31 站访问、[0x14,0x34) 37 站、[0x1c8,0x260) 5 站，这些区间成员有访问支撑可留但 offset 需在池外才留）/**改**（offset 正确但 type/名错）/**退役**（无访问证据或与池/表区间重叠）。与池/表落位区间 [0x0,0x64190) 重叠的成员一律退役（台账记录）。m_pvecCenter@0x8/m_nTodo_00C@0xc/m_nTodo_010@0x10/fCamBlendA@0x34/fCamBlendB@0x38/CamCtrlData@0x3c/nTodo_EC@0xec/PanelSlots@0x260/nList@0x984/nPointerUnderMouse@0x988/CamEntries@0x98c/nCurCamIdx@0x2594/nCurPageTab@0x5558 全部落池区内——除有强访问证据者改判外默认退役（台账留证据链）。

- [ ] **Step 4.3: check 门禁 + census 重跑**

Run: `python3 pipeline/cli.py check 2>&1 | tail -3 && python3 tools/census_struct_holes.py 2>&1 | head -8`
Expected: PASS + CCBCamControl 洞字节记录（对照预期）

- [ ] **Step 4.4: 对抗复核门④（子 agent）**

派子 agent：「复核 17 员裁决逐条：退役台账 vs CCBCamControl.json 现状对账（17 员无一遗漏）；'留'判成员的证据是否真独立于池模型；4 填充物退役理由引用是否准确；census 重跑读数 vs Task3 分支预期差 >10% 归因；裁决表」。

---

### Task 5: SkillUI 53 退赔重挂（副线）

**Files:**
- Modify: `data/annotations/structs/SkillUI.json`（known_members 增 53 员）
- Create: `data/status/skillui_rehang_20261126.json`（重挂台账）

**Interfaces:**
- Consumes: data/annotations/archive/ccbui_identity_adjudication_20261121.json retired_members 53 条（name/type/offset 均在档，evidence_level 均 unverified）
- Produces: SkillUI known_members 53 员；census 口径消 ~240B（账务修复）

- [ ] **Step 5.1: 台账读取+批量重挂脚本**

```python
import json
arch = json.load(open('data/annotations/archive/ccbui_identity_adjudication_20261121.json'))
retired = arch['retired_members']   # 53 条; 每条含 name/type(/offset 或键载)
d = json.load(open('data/annotations/structs/SkillUI.json', encoding='utf-8'))
km = d.setdefault('known_members', {})
ledger = []
for i, r in enumerate(retired):
    off = r.get('offset')
    if off is None:
        off = r.get('key')          # 0xa30 fp 条目 offset 键载
    key = '0x%x' % int(str(off), 16)
    km[key] = {
        'name': r['name'], 'type': r['type'],
        'evidence_level': 'unverified',
        'source': '2026-11-26 R1 退赔重挂: ccbui_identity_adjudication_20261121 retired_members[%d], 原退役理由=%s; 重挂=CCBUI身份案定谳后归属回归' % (i, str(r.get('reason', r.get('op', '')))[:80]),
    }
    ledger.append({'key': key, 'name': r['name']})
json.dump(d, open('data/annotations/structs/SkillUI.json', 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
json.dump({'rehung': ledger, 'n': len(ledger)}, open('data/status/skillui_rehang_20261126.json', 'w'), indent=1)
print('重挂', len(ledger), '员')
```
注意：offset 全部 < 0x639C0 池区？否——SkillUI 独立类（size 101940），无池冲突。执行时若 offset 键已存在（与 kept 4 员碰撞）——台账核查过无碰撞（0x94~0x4b8/0xa30 vs kept 0x48/0x4c/0x50/0x68）。

- [ ] **Step 5.2: check 门禁**

Run: `python3 pipeline/cli.py check 2>&1 | grep -E "new errors|PASS|FAIL"`
Expected: PASS

- [ ] **Step 5.3: 对抗复核门⑤（子 agent）**

派子 agent：「独立读 archive 台账清点 retired_members 条数与字段；对账 SkillUI.json 53 员逐一（key/name/type/与 kept 无碰撞）；抽查 5 员的 ops 理由引用是否忠实；MemberExtent/REF 门禁产物复核；裁决表」。

---

### Task 6: 轮级对抗复核（全轮独立复核）

**Files:**
- Create: `data/status/r1_adversarial_review_20261126.json`（裁决表落档）

- [ ] **Step 6.1: 派全轮复核子 agent**

prompt 要旨：「全轮独立复核（只读+分析）：①Task2/3/4/5 全部注解改动 diff 复验（git diff HEAD~N）②census 重跑读数 vs spec R1 预期（池有证 −337~348.7KB / 推迟 −22KB+SkillUI 0.24KB）±10% 中值基准③六证择二合规抽查（每落位成员证据是否≥2证、PDB 是否单证定谳）④N12/占位名红线全扫 ⑤裁决表落 data/status/r1_adversarial_review_20261126.json（真bug须修/近似/口径题呈用户）」。真 bug → 修复后重跑本步。

---

### Task 7: 管线段（loop 全链）

- [ ] **Step 7.1: 跑 loop**

Run: `python3 pipeline/cli.py loop > /tmp/loop_r1_20261126.log 2>&1; echo EXIT=$?; tail -20 /tmp/loop_r1_20261126.log`
Expected: apply/export/probe/match rc=0（codegen 恒红容错）；S2/L1 读数记录

- [ ] **Step 7.2: 失败处理预案**

- codegen 中途夭折 → `python3 pipeline/cli.py codegen all` 独立完成头树再生 → 重跑 loop
- probe 回归 → 逐案例归因（渲染 churn vs 真退化）；基线刷新带归因（`tools/regression_detector.py --save-baseline`）
- apply check 拦截 → 回 Task 4/5 修数据

- [ ] **Step 7.3: 读数归因记录**

预期（池有证分支）：CCBCamControl 洞 −337~348.7KB；全局面 1478KB→~1130KB；SkillUI −0.24KB。渲染 churn 单元（CCBCamControl.cpp 裸偏移化/SkillUI.cpp 53 员新名）错误数波动按归因记录，不盲 rebaseline。

---

### Task 8: 落账段

- [ ] **Step 8.1: 独立提交**

```bash
git add data/annotations/structs/CCBCamControl.json data/annotations/structs/CCCTData.json \
  data/annotations/structs/SkillUI.json data/status/ccbcamcontrol_r1_retirement_20261126.json \
  data/status/skillui_rehang_20261126.json data/status/r1_adversarial_review_20261126.json \
  data/status/struct_holes_20261125.json tools/probe_ccbcamcontrol_poolcount_20261126.py \
  data/status/probe_ccbcamcontrol_poolcount_20261126.json
git commit -m "feat(R1 整表重建): CCBCamControl 池/句柄表落位+17员冲突面退役+SkillUI53退赔重装——洞<实际KB>"
git push
```
（commit-msg 按实际读数填 Evidence 格式）

- [ ] **Step 8.2: 记忆更新**

memory/ccbcamcontrol-twin-adjudication-20261126.md 追加 R1 落账节（池判定结果/落位成员/退役台账/读数变化/复核裁决引用）。

- [ ] **Step 8.3: 洞清单刷新确认**

Run: `python3 tools/census_struct_holes.py 2>&1 | head -6`
Expected: 总 KB 与 Task 7 归因一致；CCBCamControl 退出 top3（池有证分支）或降至 ~326KB（推迟分支）。
