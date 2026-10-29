# TOS 批归因闭合 + 叙事勘误（2776d174 复核交付物）

## C3 行为差集归因（E3 闭合）
三态 worktree 全量再生成 A/B（C3 态输出与记录哈希 013ab196 逐字命中）：
差集 = **8 文件 14 行纯空白等价形**（whitespace-normalized 全等）——
CCBStage / CEffModel / GRPinput / RoleCamera / UIAnimateCtrlEX / Object3D /
RoleSystem / Camera。编译不可见 ⇒ 错误多重集 214 单元全等 + L1 147 不动是必然。

## 叙事勘误（两处）
1. C3 commit message 称「Case2/3（ctx 门）激活」**错**——实为 **arg 前导空白保留 vs
   旧 lstrip**；ctx 门语料零 token 级激活（stage5 下游同修复吸收）。
2. C8 commit message「19+1 断言全过」**失实**——实为 test_ref_param_table_b 过而
   test_ref_params_tos 3 红（GetAABBox 旧契约被 B 修补条合法废止），F1 修复后方 10/10。
   同族：C3 测试计数「10/10」实为 pytest 收 9（双定义遮蔽 1 测）——已随 F2 双定义切除修复。

## 读数台账（5 快照对账，复核实测）
C3/C4/C5 错误多重集全等（1137）· 末步 1136（−1 = C8 预期修复 ScreenEffectMgr C2664）
· L1 147 / 880-1141 全程不动。

## 状态
归因 ✅ 闭合 · 勘误 ✅ 本档 · F1/F2 ✅ 修复（13/13 测）· F4-F10 低危挂账（见复核报告）

## 终审勘误补（f78e97a9，2026-10-29）
- I-4：T2 commit f7b4faa「测试 6/6 绿」失实——实测 3 支（test_crt_sub_unskip 3）；同族第 2 例（前例 T6 D7「6/6」实 3）
- M-1：T8 commit「文件清 18」实为 10 文件变更（9 overlay + 1 base 存在，其余 base 路径不存在）
- I-1 附注：52 条 crt_sub_* 因 `_sub_` 截胡误桶 lib_relink_ok ⇒ 已重分 awaiting_signature（G 冤户候选禁猜测）

## 终审勘误补 2（复核 8c777315，2026-10-29）
- 失实第 5 例：a50e2415c「目标件入卡 ✓」为假（两版队列均缺席，信号源错位+正则漏参数形）——本条更正
- B2a「P:misowned 3」为假判定（absence-based，违反不准确=不判定）——已改正向反证契约（4 参 located_classes）
- B2b「双源合并」为假合并（known_members dict 形 0/9597 收录）+ 无继承闭包（RED 80% 假阳）——已修

## 勘误 3（复核 5216c3fb，2026-10-29）
- 考古断言撤回：「gap_fill 216=多认领 216 同族」不成立——条目级/地址级数字巧合
  （gap 216 条目=155 址 vs multi 216 址，交集 132；84 多认领址无 gap 标记、致因未考）
  「176 移植」口径不可复现（实测 166 from 形+50 IDB 形=216）——记质疑
- R7 note 失实修正：holder 166/216、slot 136/216（非「全在」）
