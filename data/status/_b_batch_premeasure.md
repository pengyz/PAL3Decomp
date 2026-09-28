# B/C 批前置测量（2026-09-27，改动前基线）

依据：gotcha_measure_state_before_not_after_change —— 先测后改。
工具：tools/audit_type_layout.py（编译器裁判，offsetof 对账）。

## 布局一致性（C 批前置；也是 B 批类型填充的布局门基线）

| 类 | 成员数 | 冲突 | 明细 |
|---|---|---|---|
| SceneMgr | 167 | **1** | `_gap_C812` 声明 +0xC812 但实际不是 |
| CEffMgr | 48 | **7** | m_nTodo_80EC@0x80EC · _gap_80F0@0x80F0 · m_nEff@0xA91C · m_fCurTime@0xA920 ·（工具只打印前 4 条，余 3 条待 --json 取全） |
| ScriptSystemData | 331 | 0 | ✓ 一致 |
| CGameData | 179 | 0 | ✓ 一致 |
| RoleSystem | 181 | 0 | ✓ 一致 |
| CPK | — | 0 | ✓（无冲突输出） |

⚠️ 更正知识库陈旧读数：gotcha_emitted_layout_drifts_from_annotated_offsets 记
"SceneMgr 101/169 不匹配"——实测已收敛至 1/167（该 gotcha 的成因分析仍有效，量化已过时）。
⇒ C 批前置（"SceneMgr 布局修复"）的真实工作量 = 修 1 处 + CEffMgr 7 处，不是百级。

## B 批门禁基线快照
- probe_census 快照 → %TEMP%\probe_census_beforeB.json（S2 92/208 · 总错误 1796 @ 2026-09-27T12:51:27）
- s4_baseline.json L1=63（棘轮）

## 工具缺陷（待修，勿忘）
- tools/audit_type_layout.py 硬编码 `/tmp/` 路径（line ~207 `open(src,...)`）—— Windows 上
  FileNotFoundError；本机用 `D:\tmp` 目录垫片绕行。应改 tempfile.mkdtemp()。

## CEffMgr 7 处布局冲突的病灶层取证（2026-09-27，只读）
- 冲突分两簇：{m_nTodo_80EC@0x80EC, _gap_80F0@0x80F0} 与 {m_nEff@0xA91C, m_fCurTime@0xA920,
  m_fDeltaTime@0xA924, m_fTimer@0xA928, m_fTimeScale@0xA92C}。
- **注解内部矛盾显形**：m_sz5D8C3C `char[29028]`@0x37B8 跨度 [0x37B8, 0xA91C) **包含** 0x80EC/0x80F0
  两个成员；且 0x37B8+29028=0xA91C + 尾块 20B = 0xA930 = binary_size(43312) 精确闭合 ⇒
  0x80EC/0x80F0 疑幽灵成员（源注 'ida_gap_1refs' 弱证据）。发射层按序排 ⇒ 编译 offsetof 全体位移。
- **T1 盲区定量（对 B 批方案是决定性输入）**：g_EffMgr 基址 0x5D5484 的成员绝对地址
  全镜像扫描（含 .rdata/.data）：m_pDisplay+0 命中 1（地址物化）；m_EffTable+0x91C（已知真实成员）
  **命中 0**；m_nTodo_80EC/m_nEff/m_fCurTime 均 0 ⇒ **CEffMgr 成员访问全部是 [reg+disp32]
  this-relative 形态，绝对地址扫描对容器成员近乎零收益**。
  ⇒ type-evidence 工具必须补 **T1b：this-relative disp32 访问 census**（按 pattern 文档的
  承载指令确认 + access_map.py 的 ECX provenance 追踪），否则 B 批产不出证据。
- **T1b 可行性实测（探针 %TEMP%\t1b_probe.py，capstone + ECX provenance）**：
  28 个 CEffMgr 函数 ⇒ 46 个偏移有 this+disp 访问证据；浮点运算族在 0x68–0x94 区段清晰
  （fadd/fmul/fstp/fild）、0x929 有 byte 级访问（宽度 1）⇒ **宽度+int/float 证据确实可取**。
  备注两个改造注意点：① 数组元素内部偏移也会入 census（0x20-0x64 ⊂ m_EffClass[32]、
  0x928-0x92C ⊂ m_EffTable）⇒ 聚合须按成员分段归属；② 声明但无访问 18 个成员
  （含 m_sz5D8C3C char[29028] 与 m_nTodo_80EC）⇒ 与"幽灵成员"假说一致。

## T1/T1b 信号地图 + 冻结工具 P0 缺陷（2026-09-27 探针 2/3/4 定谳）
- **按类分信号**（占位成员有证据的比例）：
  | 类 | 方法函数 | T1b 精确偏移证据 | T1 绝对命中 | 主信号 |
  |---|---|---|---|---|
  | tagEffMgrData | 0 | 0/93 | **93/93** | T1 绝对 |
  | tagCombatTaskData | 0 | 0/48 | **48/48** | T1 绝对 |
  | ScriptSystemData | 0 | 0/119 | 28/119 | T1 绝对 |
  | CEffMgr | 28 | 5/11 | 2/11 | T1b |
  | RoleSystem | 150 | 41/64 | 1/64 | T1b |
  | CGameData | 12 | 13/65 | 16/65 | 混合 |
  | CScreenMode | 65 | 18/42 | 0/42 | T1b |
  | PAL3 | 42 | 8/49 | 0/49 | T1b |
  | SceneMgr | 10 | 1/20 | 8/20 | 混合 |
  ⇒ **最终工具必须 T1（数据类）+ T1b（方法类）双信号合并**。
- **冻结工具 tools/type_evidence.py 的 P0 缺陷（探针 3/4 定谳，待复核确认后修）**：
  1. `scan_t1` 把 blob 相对命中偏移 h 直接当文件偏移传 `decode_refs_at`（`data[start:start+15]`
     用了错误起点；.text roff≠0）⇒ 真实数据上 429/431 "T1-empty" 全是假阴性；
     单测只测 `decode_refs_at` 本体、未测 scan_t1 端到端 ⇒ 测试网漏了这一层。
  2. `known_members` 键混用十进制与 '0x4C' 十六进制（CGameData 实证）⇒
     `load_candidates` 的 `int(str(key).split('_')[0])` 直接 ValueError。
  3. 缺 T1b（this-relative disp32 census）——上述信号地图的主信号之一。

## CEffMgr 布局冲突终裁（探针 5：位编码 C2118 取精确 offsetof）
实测（发射头 Effect/CEffMgr.h，编译器裁判）：
| 成员 | 声明 | 实际 | 位移 |
|---|---|---|---|
| m_sz5D8C3C | 0x37B8 | 0x37B8 ✓ | 0 |
| m_nTodo_80EC | 0x80EC | 0xA91C | +10288 |
| _gap_80F0 | 0x80F0 | 0xA920 | +10288 |
| m_nEff..m_fTimeScale（5 个） | 0xA91C..0xA92C | 0xD14C..0xD15C | +10288 |

**机制链**（全部对上）：① 数组 char[29028] 正确发射 [0x37B8, 0xA91C)（0x37B8+0x7164=0xA91C，
尾 20B 后 = 0xA930 = binary_size 精确闭合）；② m_nTodo_80EC(0x80EC) 落在数组跨度**内部**被顺排到
数组尾 0xA91C；③ _gap_80F0 按"下一成员 m_nEff@0xA91C − 0x80F0 = 0x2A2C"铺 gap ⇒ 尾块整体 +10288。

**修复方向（证据齐备，待 B 批后落地）**：删 m_nTodo_80EC + _gap_80F0 两个幽灵成员——
四证：(a) 与数组跨度物理重叠（注解内部矛盾）；(b) 28 个 CEffMgr 方法 census 零访问；
(c) 源注仅 `ida_gap_1refs` 弱启发（且名字是伪语义地址后缀名，仓规本就不许）；
(d) 删除后 7 处冲突全数归零可由编译器裁判当场复核。数组与尾块保持不动（有 T1b 访问证据 + 尺寸闭合）。

## SceneMgr 唯一布局冲突终裁（探针 6：位编码 C2118 + 发射层定责）
- 实测：`_gap_C812` 实际 **0xC810**（−2）；`m_nTodo_C848` 实际 0xC848 ✓；
  `m_partyInitData` 0xC680 ✓、`m_pRoleSystemArrayEnd` 0xC67E ✓（union 两视图均在声明位）。
- **机制**：inline union 发射时包 `#pragma pack(push,1)`（emit_headers.py:2064）⇒ 编译尺寸
  402B（max(4, 2+400)）@0xC67E → 尾端 **0xC810**；但 gap 台账 `member_size = max(union_sizes)`
  （emit_headers.py:2073）取的是**自然对齐尺寸 404** ⇒ start_off=0xC812 ⇒ `_gap_C812[54]` 虚报
  2 字节。其后 `int m_nTodo_C848` 由编译器自然对齐自愈回 0xC848（emit_headers.py:2063 注释
  "外层中央补白会吸收余量"说的就是这个）⇒ **全类语义成员零位移，纯 gap 标签错**。
- **修复方向（C 批落地，二选一，倾向 a）**：
  (a) 发射层根修：pack(1) union 的 member_size 改用**打包尺寸**（variant 打包尺寸求最大，
      不带内部对齐补白）⇒ gap 自动变 `_gap_C810[56]`，冲突归零。须防波及：inline union 共
      10 处（FightItem/MUIDialog/PalScript×2/RoleAtt/RoleSystem×2/SceneMgr/tagCam/
      tagCmdData/tagRoleTask），现仅 SceneMgr 显性受损，改后全类跑 audit_type_layout 复核。
  (b) 注解层补 `char _unkC810[2]` 占位（未知字节二分）——不动管线但拆分任意。
- ⚠️ 本改动属 codegen 层（跨层），落地时按 CLAUDE.md 病灶层检查 + 四道门 + 对抗复核走。
