# 对抗性复核（机制方）：M2-M4 覆盖率爬坡方案 v1

> 2026-10-31 · 评审人：对抗子代理 5219bfbb（机制/设计攻击）· 立场：不信任方案，只信机制推演。
> 对象：docs/specs/2026-10-31-m2m4-coverage-ramp-plan.md v1 · 判定：**REJECT**（修订后可复审）
> 15 条发现：3 BLOCKER / 4 HIGH / 5 MEDIUM / 3 LOW。全部实测核实。
> 修复落点见方案 v2 §8 销账表。

## F1 [BLOCKER] _real/ 不在 mock_link 编译面
mock_link.py:68-74 extras 只编 _eh_metadata_stub.cpp + _slots/ + _supply/ + 计划单元；
`_real/WinMain_real.cpp` 无 glob ⇒ 退役 _WinMain@16 合成体后 WinMain 无定义破闭合；
不退役则合成体冒充真身假回填。且与母设计 §6 M2「stub TU 内该函数」矛盾未声明。
修法：extras 加 glob('_real/') 列入 D5 前置；声明与母设计偏离。

## F2 [BLOCKER] demand_ledger 只增 + _supply 整目录重生成 ⇒ 退役/手修必震荡
ledger 写入=旧∪新从不删；stub_gen --supply-log 每次 unlink 整目录再全量渲染；
KNOWN_CFUNC_FORMS 为 _WinMain@16 备好合成形 ⇒ 退役条目连体复活（demand_ledger.txt:5 实证在账）。
T1 同撞：ArraySort 既是 PRUNED 债又是 _supply 合成定义——手修放回 stub 即 LNK2005。
修法：ledger 状态行/持久 exclude；生成前已定义面普查（复用 haystack）；退役=剪账+重生成原子步。

## F3 [BLOCKER] D5 对拍不作用于被验证物
manual_l1_match.py:40-49 编译面=已冻结 manual/ 构建，WINDOW=0x100+similarity 非三限定；
对拍读数可恒定而 D5 照常绿——母设计否定 manual/ 时的 P1「验证空气」重演。
修法：对拍以 mock_link 产物为编译面，复用 compare_pal3/gbengine_compare 三限定；D5 验收补字节来源。

## F4 [HIGH] 状态锚点自相矛盾 + census 无新鲜度门
124/213（10-26 census）与 135/214（10-30 基线）两个快照并列；仓库另有 209 分母；
census 刷新 ⇒ 覆盖率零功跳。修法：逐读数标源+新鲜度校验+归因枚举扩 census_refresh。

## F5 [HIGH] 「只升/只降」被自家对策证伪
R3 允许带归因增长、RK2 允许回补 stub ⇒ 字面验收必败。修法：改「非增+一切变动归因落账」。

## F6 [HIGH] stub 存量=单元数可掏空稀释
_supply/_slots 不计单元、PRUNED 掏空仍算 1 单元。修法：双口径（单元数+全 stub 面符号总数）。

## F7 [HIGH] 手修/真函数嵌入无免再生成保护区；PRUNED 债账随退役蒸发
render_stub「DO NOT hand-edit」+整文件覆盖 ⇒ T1 手修与真函数嵌入被静默灭失；
债账注记写在将删文件里=欠债注销非清偿。修法：债账迁 data/status/pruned_debt.json；
手修走修提取器/侧车补丁；补纯函数单测。

## F8 [MEDIUM] 循环⑤前置不在每轮验证链
删 stub 只能凭陈旧 census。修法：⑤前置写死「同轮 probe 当场读 ok」或挪批级。

## F9 [MEDIUM] 「每轮强制缺一不落账」自表证伪
L1 只在批级；回退粒度未定义。修法：轮级轻量 L1 抽查；commit 粒度；D6 改「结构对上+偏差归因」。

## F10 [MEDIUM] 停滞判据与靶源错位
T1/T4 天然不动 S2 数；刷 trivial 可重置计数器；「pending 扩员」是缓兵。
修法：多指标停滞；升级改限期裁决；T4 配额。

## F11 [MEDIUM] 禁注水红线不可证伪+归因零约束
修法：机械判据（分子只认 census ok；函数级宣称带对拍读数）；归因 JSON schema；append-only。

## F12 [MEDIUM] stub_retire 盘点口径未定义
五类面并存+.obj 产物。修法：路径模式→类别→读数归属规则表；.obj 移出。

## F13 [LOW] S1 仅 WARN 但验收「check 绿」
修法：strict/阈值；「覆盖率失真」措辞修正（动的是存量不是覆盖率）。

## F14 [LOW] R1-R4/R1-R5 双义、裸引用
修法：S1-S4 前缀；引用带路径；定优先序。

## F15 [LOW] D1-D3 依赖倒置
修法：顺序调整；点名台账写者/执行者。

## 总判定
REJECT。三 BLOCKER 集中在首批要动的 M2/D5 与 T1 快胜批上——照原文执行必然验收撞墙或被迫造假。
可救：M3 骨架、数据源单一、stub 不进 S2 红线、盲区声明、D6 分账加和（7078 ✓）。
