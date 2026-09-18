# 2026-09-18 retn 证据门改用指令级 asm 源 + 修 stage5 上下文无关替换

## 归档内容
- `probe_census.pre.json` —— 落地前的 S1/S2 普查（S2 65/202）
- `s4_baseline.pre.json` / `l1_pre.json` —— 落地前的 L1（count 17 / distinct VA 13）多重集
- `gen_cpp_list.pre.txt` —— 落地前 pal3/src 的 .cpp 清单（存在性 diff 用）
- `error_delta.json` —— 用 tools/regression_detector.py --before 生成的可信对账

## 未归档（有意）
落地前 `pal3/src` 的**完整内容**（12MB 生成源码）只用于本地 A-B-A 内容 diff，
**不入库**（`pal3/src` 本身是 gitignored；把生成物塞进 git 会造成仓库膨胀）。
它当时的副本在本地 `/tmp/gate_src_pre`（易失）。需要重做内容 diff 时，
应改为导出到 `/tmp` 并用 `git status` 之外的 md5/清单对账。

## 本次改动与其影响
见 `data/status/_cleanup_vtable_class_reconcile.md` §20。
