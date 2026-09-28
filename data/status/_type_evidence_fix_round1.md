# type_evidence 修复轮 1 记录（2026-09-27，Step 1/4）

两轮独立对抗复核（方法论 A：D1–D12 / 代码 B：F1–F15）后的合并修复。
冲突裁决：**浮点证据优先**（B 的"float+int⇒C"误杀 3 个已确证 float——A 实测；
按触碰类 mov/movzx/setcc/push/cmp/test 与整型运算类 fild/fi*/算术拆分处理）。

## 改动面（3 文件）
1. `tools/type_evidence.py` 重写（v2）
2. `tools/test_type_evidence.py` 重写（35 契约测试，含集成缝）
3. `tools/apply_annotation_batch.py`（type_change kind + F8 风格保持 + 2 个顺手修出的潜伏 bug）

## 修复对照（复核编号 → 实现）
- F1/D1（P0，偏移基错位）：decode_refs_at 全部走 blob 同源基；单缓冲 fixture 曾 100% 掩盖 ✗
- F2/D7（P0，hex 键崩溃）：parse_member_key 十六/十进制 + dup 显式报告
- F3+D4（裁决）：int 触碰/运算拆分、float-double 混用⇒C、多宽度⇒C、unknown 混入⇒C、
  double 提案只报（**v1 禁填**，emit_batch+守卫双拦）
- F4/D2：[reg+disp] 拒绝；指令边界表（decomp 函数区间线性反汇编 342,417 条）过滤错位解码；
  无边界时歧义不作证据
- F5：同一指令 mem 命中优先于巧合 imm（宽度证据不被 addr 覆盖）
- F6：lea ⇒ addr；F7：fi* ⇒ int；F10：set* 不证符号、cvtt*⇒浮点、cvtsi2*⇒int；
  F15：op_size=0 ⇒ unknown、argparse、evidence_refs isinstance
- F9/D9：多实例全 VA 取证（vas 列表；RoleSystem×5/PAL3×2/Array×4…116 成员受影响）
- F11：unknown 站点混入 ⇒ C；F12：8/16B 宽度如实报不填
- F13/D6：落盘走守卫新 kind `type_change`（evidence 硬约束/防陈旧批次/防覆盖已验证类型/
  double 禁填），emit_batch 只产批次不直接写注解
- F8：守卫 save_ann/flush 按**原字节风格**回写（CRLF/LF、indent 2/1、尾换行；仓内混杂
  实测 CRLF 886/LF 12、indent2 833/indent1 49、尾换行 122/776）
- F14/D11：T2 词边界匹配；T2 只佐证不投票
- D5：报告/输出的生效链含 **apply_annotations → export_full**（不回灌 IDB 不进生成头）
- D8：工作集 W 口径写死（容器类 known_members 占位成员；B2 行仅旁证）
- D10：INT-MATCHED 更名 **WIDTH-4-MATCHED**（int/float/指针 不可分）

## 顺手修出的 2 个潜伏 bug（守卫）
- dispatch 双链 `else` 会把 rename/reattribute/add_method 误判"未知 kind"⇒整批中止（合并为
  单条 elif 链）
- load_ann 文本模式通用换行吃掉 CRLF ⇒ 风格探测失效（newline='' 修复）

## 测试：35/35 绿（含真实 PE 集成缝：tagEffMgrData 解码率下界、load_candidates 多实例）

## 验收比对（复核 A 的 10 样本表 → 6 个 W 内样本全数命中）
| 样本 | 预期 | 实测 |
|---|---|---|
| SceneMgr.m_nTodo_142C（fimul） | 不得 float | WIDTH-4-MATCHED（int 4B 1 站点）✓ |
| tagEffSParticleSys.m_nSpawn2Color | float | float B（fstp + imm 位型 0xc2480000=-50.0f 旁证）✓ |
| tagCombatTaskData.m_nEffParam14 | float | **已早是 float**（cluster 定型）⇒ 不在 W 正确 ✓ |
| CEffMgr.m_nTargetSlot（21 站点） | WIDTH-4-MATCHED | ✓（标签不再过强） |
| SSD.m_pCurrentBlock | 不得 int 过度声明 | WIDTH-4-MATCHED（char* 假设只进观察）✓ |
| PAL3.m_nRT2Buf* / m_nEffObjCount（D9 误判 21 条） | 多实例 VA 修复 | vas 双实例 ✓；7 条 A 级 float 提案（**待复核独立验证**）|

## 全量 dry-run 读数（data/status/type_evidence_report.json）
W = 715 / 26 类（与复核 A 裁定精确一致）；A=203 B=298 C=3 0=211；
WIDTH-4-MATCHED=196；填充提案 11 float（A 级 7，全 PAL3 多实例区）；double 0（禁填生效）。
真冲突 3 条全部是整型多宽度混用（m_nCurrentRoleSlot 55×4B+1×1B 等），报告制 ✓。

## 未决/已知
- tagEffSParticleSys 2 条 float 单站点 B 级（imm 位型旁证强但保守不填）——进 B 批人工裁定池
- PAL3 7 条 A 级 float 提案语义可疑点（m_nEffObjCount 名字像计数却有 fadd/fstp）——
  正是对抗复核 1 号核对对象
- Step 2 产出物：dry-run 报告 + W=715 钉死 + 与"211"口径差异说明
