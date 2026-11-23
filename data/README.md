# data/ — 数据层

## annotations/（标注真值层，git tracked）
- `structs/*.json` — 类注解（known_members 布局 + methods 条目 + vtables 槽）
- 顶层：functions.json（IDB 命名通道，仅自由函数）/ globals.json / skip_functions.json / enums.json / sdk_types.json / annotation_schema.json（N16 门格式宪法）/ allowlist 族 / thunk_registry / system_lib_statics / sce_opcodes（SC 引擎参考）
- 详见 `manifest.json`（文件注册表）与 `CHANGE_LOG.md`（置信度计算规则方法论）
- 门禁：`python3 pipeline/check_annotations.py`（N16-N24+KEYCASE+REF 等硬门）

## status/（运行状态对账层，git tracked(latest)）
- **棘轮基线**：s4_baseline(L1 棘轮)/compile_baseline(编译回归门)/check_baseline_errors(存量冻结)/canonical_contract/claim_gate/quality 等
- **裁决台账**：bases_adjudications/n22_pair_closure/true_vtable_map 等
- `pending/` 活裁决队列 · `archive/` 归档 · `baselines/` 只跟踪 latest.json（时间戳快照 20261123 起不入库+自动 prune 保 5）
- 生命周期：运行输出→pipeline/_logs/；一次性调查→archive/；顶层散放禁止
