# case-01 facts_oracle 来源注（手写·R8 独立性）

**禁从 annotation 脚本派生**——本文件人工按 annotation 语义+converter 契约直译写定。
每区来源：
- `functions.*.name/signature` ← annotations/functions.json 三键（0x401356/380/390）
  与 structs/{Base,Derived}.json methods（update×2 同名异址=合法重载；calc 双型）；
  signature=reconstruction 形（ret+conv+params 直拼，T3 证明链契约）。
- `class` ← methods 所在 struct 名（Base.update→Base / Derived.*→Derived）。
- `structs.*.size` ← size 键原值；`members` ← known_members 十进制键原值。
- `Complex.members[16].type=UNION_Complex_16` ← inline-union 转换产物
  （import_annotation define_union 命名式 UNION_<cls>_<off>）。
- `bases`（Derived→Base）**不在 oracle**：converter 契约=不转（矩阵 dropped·spec §4）。
- `globals.*` ← globals.json 三键（type 原样）。
- 地址：annotation 16 位 hex → oracle 8 位短写（norm_addr 同 int，diff 归一）。

- `UNION_Complex_16` ← inline-union 转换产物（变体键=声明序：fval/ival 源序）。
