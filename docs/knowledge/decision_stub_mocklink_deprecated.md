# decision: stubs/mock_link 机制废弃（2026-11-02）

## 裁定
用户裁定废弃 stub 生成与 mocklink 装配机制。理由：思路与核心原则相悖——
stub=编造信息（违反「后处理只做等价变换，不编造信息」）；mocklink 471040B
中 42% 假件不是目标工件；「链接闭合」非目标（字节匹配的可运行重建才是）；
平行宇宙吸血（stubs 子项目吃掉标注/管线产能——「能力未释放」的对价）。

## 退役四步（已执行）
1. 冻结生成：stub_gen/mock_link 打 DEPRECATED banner，禁新 stub/新装配
2. 台账翻转：stub 台账语义=「真身需求单」（每条 stub = 待真身 TODO）
3. 度量收编：链接层度量归 link_probe；stub_retire 保留存量/退役对账（cli.py 状态显示保留）
4. 产能归还：标注质量→Hex-Rays 质量→真身覆盖率（投入产出曲线）为主战场

## 保留遗产
thunk_scan/seh_variants（真实取证）· stub_retire 哈希链记账形 ·
unresolved 180 清单（与 B 战役归属对账交叉）· cli stub↔S2 三读数（纯计量）
