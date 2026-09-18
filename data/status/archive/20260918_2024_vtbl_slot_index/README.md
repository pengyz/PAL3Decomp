# 2026-09-18 vtable 槽位 //4 —— **调查结论，未落地任何代码改动**

## 档案
- `probe_census.pre.json` / `l1_pre.json` / `gen_cpp_list.pre.txt` —— 改动前基线（S2 67/202，L1=17）
- `error_delta.json` —— 两次尝试（`N` 与"窄修法"）的**可信对账**结果

## 结论：**已回退**，pipeline 无残留改动
先**证明**了 `//4` 语义错（A 级：`sub_4C52C0` 的 `__vftable + 2` ⇔ `call dword ptr [edx+8]`，
即 N = 位移/4），但改成 `N` 后实测 **2 个 ok→fail**（UI3DCtrl、UIStatic）、S2 净 −1。
**根因不在那行算术**，而是 **DLL 类 vtable 注解不完整**（gbTexture 只标 0–3 而引用到 5；
gbGfxManager 只标 0–6 而引用到 28），`//4` 把未标注的高槽折叠进低区间、侥幸产出能过类型检查的名字。

详见 `data/status/_cleanup_vtable_class_reconcile.md` §22 与
`docs/knowledge/gotcha_wrong_arithmetic_can_be_accidentally_load_bearing.md`。
