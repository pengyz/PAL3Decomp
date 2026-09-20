# 批次记录：`UIStatic 152 → 248` —— **判据破线，已回退**（2026-09-20）

## 事实
- **注解改动**（已回退 ✓）：`data/annotations/structs/UIStatic.json` 的 `binary_size` **152 → 248**。
  证据为 A 级三重（`??_L` size=248 且 ctor=`0x440740` ×3 ✓；`operator new(248)`+`call 0x440740` ✓；
  ctor 写的 `0x56AD88` 正是本类自己声明的 vtable ✓；成员位移上界 ≥200 ✓）——
  **证据本身没问题** ✓（并查出 `f87db02f0` 曾正确落地 248、被 `1c2234d06` 改回 ⇒ 一次回退 ✗）。

## 破线结果（一批一管线，实测）
| 判据 | 结果 |
|---|---|
| `probe all` | **EXIT=1** ✗ |
| `match` | **EXIT=1** ✗（`[L1 ratchet] REGRESSION: byte-perfect functions lost` ✗）|
| S2 | **新失败 76** ✗（持续失败 130 ✓ 不变）|
| 直接错误 | **`C2079: 'm_face' uses undefined class 'UIStaticFlip'`** ✗（同样出现在 `UIStaticRM` ✗）|

## 根因（**与 B34 同族：级联** ✗）
`UIStaticFlip` / `UIStaticRM` **派生自 `UIStatic`** ⇒ 基类 `binary_size` 152→248 **级联改变所有子类的布局** ✗
（子类尺寸 +96 ✓）⇒ 生成的头里那些**按值成员的类型**变成**不完整类型** ✗ ⇒ 76 个单元编译失败 ✗。
**这不是"证据错"，而是"改动的爆炸半径没被评估"** ✗ —— 与 B34 的按值成员/union 平凡性是**同一类失败模式**：
**注解层的改动会通过 C++ 语义（继承/按值成员/union）在生成层放大** ✗。

## 处置（已执行）
1. 注解**立即回退** ✓（`git show HEAD:... > ...` ✓，禁止破坏性 git ✓）；
2. **补跑下游链** ✓（`apply → export → codegen → probe → match`）—— **只回退注解不够** ✗（B34 教训 ✓，
   因为 IDB 与 `asm/pal3/ida_structs.json` 都已被前一次 `apply/export` 污染 ✓）；
3. 本批**未提交** ✓（改动只在工作区，回退后即干净 ✓）。

## ⇒ 新增纪律（R10）
**改动"被继承的基类的 `binary_size`"前，必须先评估级联** ✗：
1. 先查**有哪些类派生自它**（`base_class` 反查 ✓）；
2. 若子类被**按值**用作其它类的成员（含在 header 里 ✗）⇒ 该改动会命中 **include 图 + 布局** 两侧 ✗
   ⇒ 必须与"补 include/完整类型"**同批**处理 ✓，否则必然出现 `C2079 uses undefined class` ✗；
3. 该类改动应**单独成批**（爆炸半径大 ✗），且**优先在子类数量少时**做 ✓。
**⇒ 后续被裁决的尺寸修正（`Camera 12956→544` 等）必须先按此评估** ✓ ——
`Camera` 若无子类/无按值引用则可直接做 ✓；若否则先做 include 侧 ✓。
