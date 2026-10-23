# Step 0 风险复核

## 风险评估

「风险 0」**不成立**。①②接近零风险；③**根本不是只读**——它改写 3 份基线数字。本仓铁律：L1 棘轮会回写基线、`compile_regression` 读**缓存** `probe_census.json`（`gotcha_compile_regression_reads_cached_census.md`）⇒ 不先 probe 就对齐 = 用陈旧读数写裁判（2026-10-19 陈旧验证致 S2 0/214 误判为改善）。更根本：3 份基线**量纲不同**——`compile_baseline`=ok/fail 快照（214 分母，10-22）· `baselines/latest.json`=(code,msg) 多重集（205 分母，10-16）· `s4_baseline`=L1 计量（194）——它们是**不同工具的不同账**，不是同一量的三份副本。"统一数字到 3 份基线"是范畴错误，写进去只会破坏各自记账。且「对齐」可能**洗白真退化**（2026-10-10 陈旧基线致门禁失去判别力）。

## 副作用

1. **① 报表误导下游**：`ida_structs.json` 是 export 产物，不先 `apply→export` 则报表量化的是陈旧数据（2026-10-19 强制规则）；且 `known_members` 的 inline union/overlap 语义是**位面复用 ≠ 偏移冲突**（2026-10-16 定谳），type 可为 dict 形态 ⇒ 朴素偏移 diff 必产假阳性「标注面过大」，误导阶段 1 清理方向。
2. **② 行号白名单脆断**：无关编辑移行即误 FAIL；若匹配放宽松，旧行号又能**掩护新增直读**。
3. **③ 裁判污染**：改基线数字=改裁判读数，P1-5 同树 A/B 若以「对齐后」数字划界，回归可被记作中性。

## 失败模式

1. **lint 扫错目录（已实测）**：规格写「扫描 `pipeline/gen/*.py`」，但白名单文件全在 `pipeline/gen/stages/`（`emit_headers.py`/`stage4_substitution.py`/`stage3_cleanup.py`）⇒ glob 漏掉全部违规文件，测试恒 PASS、防回潮失效。
2. **白名单三重脱节**：规格称「8 处」却列 11 行（4+4+1+1+1）；CLAUDE.md 称「尚有 3 处」；实测 `ast_transform.py:337` 与 `stage3_cleanup.py:671` **已收敛到 `annotation_view`**（代码注释自证）却仍挂在待清清单；而 `stage4_substitution.py:2447/2456/2467/2477` 等直读**未列入**。三数字互斥 ⇒ 闸基线不可信，FAIL 无法裁决。
3. **③ 单向写入无快照**：`align_baselines.py` 无 before/after 留证 ⇒ 事后无法证明「只归一、未洗白」。
4. **引用违规**：`s4_baseline` L1=194 与 T146 实测 L1=184 不符；且 L1 带三限定（截断/长度/重定位 4 字节 don't-care），当「唯一裁判」外推即违反三限定规则。

## 缓解措施

- **③ 降级为只读对账报告**：只输出 3 份基线的差异清单与量纲说明，**不写入**；归一动作挪到阶段 4，届时必须现场 probe 读数 + before/after 快照。
- **② 白名单锚「文件+内容模式」禁行号**；扫描范围改 `pipeline/gen/**/*.py`；白名单条目失配即 FAIL（陈旧条目不得掩护）；先以实测定清单，废弃 8/11/3 三个旧数字。
- **① 报表头部记录 `ida_structs.json` mtime 与最近 export 时间**，陈旧则拒绝出报告；diff 须识别 inline union dict 形态与位面复用语义。
- 引用 L1/S2 数字一律带三限定 + 当场读数，不引基线文件。

## verdict

**非零风险**。①② 可做（按上条改锚点/扫目录后）；③ 「改 3 份基线数字」**不应留在 Step 0**——量纲不同 + 缓存陈旧 + 洗白风险，改为只读对账报告，归一挪至阶段 4。Step 0 改称「近零风险（③ 降级后）」方可放行。
