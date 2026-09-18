# 2026-09-18 `~` 护栏 —— **实测未能落地**（已回退）

按对抗性复核 §25.8 的建议实现：`_resolve_vtbl_method` 的 offset 分支命中析构名即返回 None。

## 结果：预期效果达成，但 S2 净退化
- 达成：codegen 后 20 文件变化 / 124 hunk，被误删语句恢复为 `[VFTABLE-STUB]` 调用
- **S2 67 → 66（−1）**；ok→fail 1（`Misc/UIStatic.cpp`）
- 新增 `C2084`×4 / `C2556`×2 / `C2371`×1 / `C2264`×7

## 根因
stub 命名是**每文件序号计数器**（`pal3_vtbl_unk_N`），恢复出的新 stub 与文件中已存在的 stub
**撞名/撞签名** ⇒ 重复定义与声明冲突。"把删除改成 stub"不是止血，只是把伤害换了位置。

## 档案
- `probe_census.pre.json` / `l1_pre.json` / `gen_cpp_list.pre.txt` —— 改动前基线（S2 67，L1=17）
- `error_delta.json` —— `regression_detector --before` 的可信对账（即上表的来源）

详见状态文档 §26。**pipeline/ 与 data/annotations/ 已回退为零改动。**
