# case-02 facts_oracle 来源注（手写·R8 独立性）

**禁从 annotation 脚本派生**——人工按缺形语义+converter 契约直译。每行来源：
- `0x402000 winner_m/class=PairB` ← PairB.json confirmed 认领；**PairA rejected 败者禁出**
  （T7①——oracle 无 loser_m=负锚）。
- `0x402100 nested_do owner=Nested` ← Nested.methods owner 维（T7⑤ owner 入 plan）。
- `0x403000 _todo_00403000` ← functions.json 占位名**原样过**（铁律：占位名不清洗）。
- `0x403100 own_fn owner=Nested` ← functions.json owner 维（T7⑤）。
- `UNION_Nested_4` ← 嵌套 union 转换产物（import_annotation UNION_<cls>_<off>；
  **变体键=声明序非偏移**——union 变体无偏移语义，投影键=枚举序）。
- `INLINE_Nested_8` ← inline-struct dict 显式化（T7④ INLINE_<cls>_<off>；禁静默降 byte）。
- `Nested.members` 三键 ← 十进制键 0/4/8；**`12_1` 变体键视图不在 oracle**
  （T1 裁定：变体视图域外，回补待 union 折叠——converter 契约=不转）。
- `PairA/PairB size=4` ← binary_size 键（空成员 struct 仍 define_struct）。
- `g_case2` ← globals.json（type 原样 int）。
