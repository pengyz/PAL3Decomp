# R3 实施计划：RoleStatePanel 152KB 布局重建（CEffMgr 模式）

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** R3 轮——RoleStatePanel 洞（156433B，主体 153852B）按 ctor 全解码落位（侦查：99.63% 已映射，残余仅 574B）；前置解 UIListBox 基类尺寸矛盾与 C11 bases 裁决。

**Architecture:** 同 R1/R2 四段式；本轮特色=基类链裁决先行（ctor 首调 UIListBox-named@this+0，其真身 1208B 与注解 72B 矛盾卡住 [0x44,0x4B8) 段归属）。

**Tech Stack:** 同 R1/R2

**Spec:** docs/specs/2026-11-26-struct-hole-filling-campaign-design.md §2 R3

## Global Constraints

- 同 R1/R2 全部红线；??_L 元素类钥匙失效时走三角定位（stride+足迹+PDB/census 交叉，UIParticle 先例）
- C11 bases 变更必须落 data/status/bases_adjudications.json（ctor_evidence=基构造直调地址链）
- annotation_schema/N16 对新字段先跑 check 验证再批量

**关键既证事实（侦查探针 data/status/probe_rolestatepanel_layout_20261126.json）：**
1. 真 ctor=InitUI@0x4a1e40（162 指令）：首调 ??0UIListBox-named(0x43dcd0)@this+0、vtable 0x56F040、23 this 写、零 memset
2. 五笔 ??_L：0x12f8/0x136f8 各 128×584（回调=EquipUI 同款误名对→UIParticle 嫌疑，三角定位待做）；0x25e04 5×3788=s_RoleState[5] 直证；0x2a800 4×152+0x2ab08 5×152 UIFrameContainer verdict=both
3. disp 普查：344-stride ×9（0x508..0xfc8）、152B 群、23 子对象构造对（152B×11+344B×10）
4. 六洞全部有证据；ctor 覆盖后残余 574B（[0x68,0x168)256B+16B 缝×5+[0x25af8,0x25b78)128B）
5. **阻塞项**：UIListBox.json binary_size=72 vs 其 size_evidence"1208 确认"自相矛盾；0x43dcd0 真身构造 1208B 对象（UIWnd 三重指纹）→[0x44,0x4B8) 段归属待裁
6. UIWnd=68=0x44；基区 [0,0x44) 全覆盖（PtrArray=16 填 0x24..0x34）；RoleStatePanel 方法直用基区 disp 4 处

---

### Task 1: 基类链裁决（阻塞项先行）

**Files:**
- Modify: `data/annotations/structs/UIListBox.json`（按裁决结果）
- Create: `data/status/uilistbox_chain_adjudication_20261126.json`
- Modify: `data/status/bases_adjudications.json`（C11）

**Interfaces:**
- Produces: UIListBox 真身尺寸（72 或 1208 或双类拆分）+ RoleStatePanel bases 裁决——Task 2 落位的 [0x44,0x4B8) 归属前提

- [ ] **Step 1.1: 裁决探针**——0x43dcd0 ctor 真身尺寸（new/??_L/足迹三路）、UIListBox.json size_evidence 1208 出处复核、g_UIListBoxDlg（72B 全局）与 1208B 类的实例关系（双类并存 or 注解错）、UIWnd vtable 三重指纹复核
- [ ] **Step 1.2: 裁决落档**——三态择一：A=UIListBox 实为 1208B（72 系误记，改注解+g_UIListBoxDlg 连带）；B=双类（72B UIListBox + 1208B 未名派生类，0x43dcd0 归后者，需新类名——禁发明，走中性名或消费语义名报批）；C=证据不足挂账。RoleStatePanel bases 按 A/B 落 bases_adjudications（ctor_evidence=首调 0x43dcd0@this+0 链）
- [ ] **Step 1.3: 对抗复核门①**——独立复核裁决链与 bases_adjudications 完整性

### Task 2: ctor 解码成员落位

**Files:**
- Modify: `data/annotations/structs/RoleStatePanel.json`
- Modify: `data/status/rolestatepanel_r3_adjustments_20261126.json`（新建）

**Interfaces:**
- Consumes: Task 1 基类尺寸（定 [0x44,0x4B8) 归属）
- Produces: RoleStatePanel 大幅扩员

- [ ] **Step 2.1: 五笔 ??_L 落位**——0x12f8/0x136f8（元素三角定位：584 stride+足迹+误名回调同款→UIParticle 嫌疑，按证据强度落名或 byte 形）；0x25e04 s_RoleState[5]（直证）；0x2a800 UIFrameContainer[4]/0x2ab08 UIFrameContainer[5]
- [ ] **Step 2.2: 344/152 子对象群落位**——344-stride ×9（0x508..0xfc8）+152B×11+344B×10 构造对（探针 ctor_layout_map 段表逐对落，元素/子对象类按回调或 census 定；未名者 byte 形+note）
- [ ] **Step 2.3: [0x44,0x4B8) 段落位**——按 Task 1 裁决归属（基类子对象 or 本类成员）
- [ ] **Step 2.4: check+census**——新 N13a 冻结走过渡协议；census 记录
- [ ] **Step 2.5: 对抗复核门②**——独立复算全部新区间几何+对账+类型

### Task 3: 残洞收口与诚实留洞

- [ ] **Step 3.1: 574B 残区处置**——[0x68,0x168)256B（disp 活证据区，按直方图落位或留）+16B 缝×5+[0x25af8,0x25b78)128B（byte 串 disp 活）
- [ ] **Step 3.2: census 终读数**——RoleStatePanel 预期洞 →~1KB 级或全闭
- [ ] **Step 3.3: 对抗复核门③**——残区处置合规性（无伪语义名/无证据区留洞）

### Task 4: 管线段

- [ ] **Step 4.1: loop 全链**（R1/R2 预案同）
- [ ] **Step 4.2: N13a 解冻验证 + S2/L1 记录 + churn 归因**
- [ ] **Step 4.3: 对抗复核门④**

### Task 5: 落账段

- [ ] **Step 5.1: 提交+push**（Evidence 格式）
- [ ] **Step 5.2: census 重跑+记忆更新+ledger 终记**
