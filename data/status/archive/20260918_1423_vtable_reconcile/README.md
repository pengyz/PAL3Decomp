# pre-state @ 20260918_1423 —— vtable↔类迁移（0x56AC20/0x56AD64/0x56ACFC）

落地前快照。A-B-A 用。

- probe_census.json (generated_at 2026-09-17T20:10:43) —— probe s1/s2 逐单元
- s4_baseline.json —— symbols 218 / matched 191 / match_L1 17 / partial 149
- UI3DCtrl.json / UIProgressBar.json / UIButton.json / UIFlexBar.json —— 迁移前原文

变更依据：data/status/_cleanup_vtable_class_reconcile.md §2（A 级三链证据）

## 回退方法

```bash
# 4 个文件：直接用本目录快照覆盖
cp data/status/archive/20260918_1423_vtable_reconcile/{UI3DCtrl,UIProgressBar,UIButton,UIFlexBar}.json \
   data/annotations/structs/

# UIStatic.json 未在快照里（落地后期才追加修改），用 git：
git show 66367eab6^:data/annotations/structs/UIStatic.json > data/annotations/structs/UIStatic.json

# 回退后必须重跑：check → apply → export → codegen all → compile → probe all → match
```
