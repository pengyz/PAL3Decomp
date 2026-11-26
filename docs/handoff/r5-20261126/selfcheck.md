# R5-SaleUI（#9）提交前自检表

数据源：`data/annotations/structs/SaleUI.json`（commit 7f9d6a636，55 成员 / binary_size 105912）。

## 一、QA checklist 逐条对照

| # | checklist | 结论 | 证据 |
|---|---|---|---|
| 1 | census v3 重跑：SaleUI 洞 44,560B→≤7,684B，命令与输出可复现 | ✅ | `python3 tools/census_struct_holes.py` → SaleUI `3 洞 / 7,684B`；全库 `1,239,032B / 1,122 洞 / 201 类`；副本 `struct_holes_r5_20261126.json` |
| 2 | census 产物落 `docs/handoff/r5-20261126/`（不写 data/status/） | ✅ | 本目录 `struct_holes_r5_20261126.json`（87KB）。注意：census 脚本无 `--out`，运行时顺带重写 `data/status/struct_holes_20261125.json`，我**未提交**该文件 |
| 3 | 三类合计下降 ≥36,000B，差额逐段归因有指针 | ✅ | 三类 117,128B→80,252B，净降 **36,876B**；差额来源 = MagicUI 44,652B（`r5_magicui_dossier.md`：无 ctor/无分配点/无表项，四槽真主人 MainPropUI/EquipUI）+ UIGameFrm 27,916B（README §4：2026-11-24 已裁定为 g_gamefrm 第二视图） |
| 4 | check PASS 且 0 new | ✅ | `python3 pipeline/cli.py check` → `0 new errors + 37 frozen(advisory), 109 warnings — PASS`（EXIT=0） |
| 5 | loop 全链 apply/export/probe/match rc=0（codegen 恒红容错），loop 前 ps 确认无并发 | ⚠️ 部分 | apply 21:30 rc=0 / export rc=0 / codegen rc=1（已知恒红）/ probe rc=1、match rc=1 —— 后两者为**既存红**（probe 基线陈旧记 S2 900/995；match 唯一 LOST=RoleStatePanel `?_G @0x4A2150`，R4 已归因 ev_0003/ev_0004）。22:00 起 loop 的 apply 段 rc=1 是**共享管线 bug**：`pipeline/ida/apply_annotations.py:2025` 引用未定义的 `gb_sig_ok/gb_sig_try/gb_sig_skip`（同函数 2194 行才初始化）⇒ NameError；非本卡引入（同注解 21:30 直接 apply 成功；21:04 他人 run 日志同报错） |
| 6 | 新落成员 evidence_level+source 齐备，命名 `m_unk_<offset>` 无数字后缀/伪语义 | ✅ | 55 成员：`evidence_level` 缺失 0、`source` 缺失 0；分布 A=54 / unverified=1（`buf`，既有成员，source 注明「本轮未取得二进制证据」）；命名扫描无数字后缀形 |
| 7 | 独立子 agent 对抗复核已完成 | ⛔ 待安排 | 我 delegation depth=0 无法自派，已请 lead 指派；材料=`README.md`+`SaleUI.final.json`+`saleui_ctor_dtor_map.json` |
| 8 | 独立提交含 Evidence 格式与 census 落档 | ✅ | commit 7f9d6a636（commit message 带 `[Evidence]`/`[Verify]`/`[Scope]`） |

## 二、覆盖与残留（脚本从最终 JSON 复算）

- 成员声明 span 合计 **98,156B**；布局覆盖 `0x48`→`0x19DB8`（105,912B，含基类 UIListBox 0..0x48 的 72B）
- 残留洞 3 段合计 **7,684B**：

| 段 | 字节 | 归因 |
|---|---|---|
| 0xF574–0x10474 | 3,840 | ctor/dtor 均无构造调用、无清零跨度；探针在 0x7000–0x10FFF 页零 disp 访问 |
| 0x10658–0x11558 | 3,840 | 同上 |
| 0x10564–0x10568 | 4 | 两个 240B `rep stosd` 清零块（0x10474 / 0x10568）之间的对齐空隙 |

## 三、证据形态分布（source 前缀）

| 形态 | 条数 |
|---|---|
| ctor 写序 / `??_L` 池三元组 | 40 |
| dtor 拆除点（含 `??_M`） | 10 |
| 相邻构造点空隙（下界闭合） | 3 |
| 相邻池空隙 | 1 |
| 既有成员未取到二进制证据（buf） | 1 |

## 四、复跑命令

```bash
python3 pipeline/cli.py check                 # 期望 0 new PASS
python3 tools/census_struct_holes.py          # 期望 SaleUI 3 洞/7,684B；全库 1,239,032/1,122
python3 pipeline/cli.py loop                  # 期望 apply/export rc=0；probe/match 附既存归因
```

## 五、反例留档

`SaleUI.union.json`：union 双视图版，check PASS 但 VC6 `C2621`（`UIFrameContainer[240]` 非 POD 不能进 union）导致 S1/S2 崩塌（0/229），**不可用**。
