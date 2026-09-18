# 2026-09-18 static_methods 守卫恒为假

## 归档
- `probe_census.pre.json` —— 落地前普查（S2 66/202）
- `l1_pre.json` —— 落地前 L1 多重集（count 17）
- `gen_cpp_list.pre.txt` —— 落地前 .cpp 清单（存在性 diff）
- `error_delta.json` —— `tools/regression_detector.py --before` 的可信对账

## 归因结论（必须一起看）
对账报 `CCBStage.cpp` 真新增 5 条 C2440。**已查清是错误恢复位移**：
该文件只有 6 行变化（227/487/490/494/531/12618），而这 5 条错误所在行
（3540/3543/3560/3569）**均不在变化区间内**（逐行脚本核对），且同缺陷的
3512/3524 改前已报出。`compile_regression.py` 与 S2 ok 集合**均无回归**，
`L1` 多重集**恒等**。

## 未归档（有意）
落地前 `pal3/src` 的完整内容（12MB）只用于本地 A-B-A 内容 diff，不入库
（`pal3/src` 本身 gitignored）。见 §20.4 的说明。
