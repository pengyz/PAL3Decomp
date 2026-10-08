# 守卫/工具加固返工记录（2026-09-27，复核 5560c6c5【须返工】→ 返工实施 → 复核 75f6709b 验证中）

## 返工项（复核判定 → 修复 → 测试锁）
| 复核判定 | 修复 | 测试锁 |
|---|---|---|
| **P0 同文件多条目互踩**（_BUFFER 按 path 键控 + load_ann 重读原盘 ⇒ 第 2 条覆盖第 1 条、rc=0；B 批 25/26 类多候选必踩） | load_ann 先查 _BUFFER 命中返回缓冲版（链式施加，kind 无关）| test_guard_same_file_multi_entry_chained |
| **P1 key 规则方向反转**（旧"放 N_N 拒 hex"恰好放危险拒安全；51 真实 hex 键（B 集 14 个）被误拒） | regex `(0x[0-9a-fA-F]+\|\d+)(_\d+)*`；apply_annotations.py:447 两处 `int(str(off).split('_')[0],0)`（堵 int('50814_0',0)=508140）| test_guard_type_change_key_format（hex 正/负面均用真实键 '0x10'；非法 '16 20' 校验期拒）|
| **P1 测试掩盖 2 条**（P1-2 被 P1-3 探测兜底、hex 负面被"无成员键"兜底）+ 缺口2 零覆盖 | fixture 全部 CRLF+indent2 可 round-trip；补 name/new_name 契约 | test_guard_write_phase_skip_rejects_whole_batch（重写）/ test_guard_rename_requires_nonempty_new_name |
| P2 幂等重跑破坏 | add_method 内容一致 ⇒ no-op 成功；不一致 ⇒ 拒 | test_guard_add_method_idempotent_noop + existing_rejects |
| P2 _float_bits 99.2% 误报（push 地址也"像 float"） | exp∈[0x20,0xEF] + 排除 imm==target + 承载纠真标签 | test_decode_imm_float_bits_corroboration（正反面）|
| P2 shift_offset 空转报成功 | from 不命中任何键 ⇒ _write_rejected 整批拒 | 待 75f6709b 验证（探针级）|
| P2 flush 无原子替换 | _dump_like 临时文件 + os.replace | 间接（风格测试全过）|

结果：`python tools/test_type_evidence.py` **45/45 绿**（42→45：+3 新契约，2 条掩盖修复后仍绿=真契约）。

## 遗留（已登记未修，防误称）
- check 闸（pipeline check）在 flush 后失败无回滚（P2，违反全或无叙事）——随 W4 落；
- Logger/tagCam/tagCmdData/tagRoleTask 4 文件被 P1-3 探测封杀——专门归一化提交（W4）；
- 存量 test_guard_rejects_nonplaceholder_and_double 的"非占位"契约被同测试 double 验证掩盖（存量问题）；
- 复核 5560c6c5 未验证项：UIStatic 1507 历史批次落盘完整性抽查（挂 W3 台账）。

## 验证复核 75f6709b【有条件返工合格】→ 三条件当轮清账
- **C1** ✓：shift_offset 空转拒绝 + _float_bits 收紧/imm==target 排除各补契约测试
  （test_guard_shift_offset_miss_rejects / test_float_bits_tightened_and_target_excluded）；
  add_member name 约束**文档登记**（现行 kind 无 `name` 回退路径可测，防未来 kind 用）；
- **C2** ✓：test_guard_add_method_idempotent_noop 增 `[no-op]` 输出断言（判别 HEAD 静默跳过）；
- **C3** ✓：apply_annotations.py:629（hex 键 ValueError）/:1013（N_N 键 int(o,0) 坑）同批修复
  （`int(str(k).split('_')[0],0)` 规范形态）。
结果：`python tools/test_type_evidence.py` **47/47**；复核实测附注：B 集 hex 键分布
CGameData×**8**（非 7，口径笔误已正）；随机 _float_bits 通过率 99.24%→81.27%（收紧后）。

## 台账链接
- 修复依据：5560c6c5 全文（%TEMP%\pal3_probe\ 探针 6 组）；验证复核：75f6709b（在跑）。
- 前一轮修复记录：data/status/_type_evidence_fix_round1.md（F1-F15/D1-D12）。
