# Spike 报告：`??_L/??_M` 元素尺寸证据源（交付 1 · 任务 5）

日期：2026-09-20 ｜ 计划：`docs/specs/2026-09-20-evidence-layer-spike-plan.md`（交付 1）
规格：`docs/specs/2026-09-20-evidence-layer-design.md`（含三路复核附录）

## 0. 成功判据（三条，全部达成 ✓）

| 判据 | 结果 |
|---|---|
| ① `??_L` **133/133 参数完整** | **达成** ✓：`ehl=133`、`ehm=333`、**不完整=0**（与 `grep -c "call.*??_L@"` = 133 三处交叉一致 ✓；站点行集合与 call 行集合**完全相等** ✓）|
| ② **`Role` 可由独立证据解析、`BINK` 错锚判非 verified** | **达成** ✓（见 §2；**全仓 `verified_class` 非空行数 = 0** ⇒ 无任何类被误判为"已验证" ✓）|
| ③ **不改注解 / 不改生成物 / 不接硬门禁** | **达成** ✓：`git status --porcelain -- data/annotations pal3/src` **为空** ✓；本交付**未新增任何 exit≠0 的门** ✓ |

## 1. 站点规模与证据性质（**已知漏采必须显式记录** ✓）

- 站点 **466** = `ehl` **133** + `ehm` **333**；不完整 **0** ✓
- **`??_L` 是五元组** `(ptr, size, count, ctor, dtor)`；**`??_M` 是四元组** `(ptr, size, count, dtor)`，**无 ctor** ✓
  —— 两者**不共用**五元组描述 ✓（若共用会凭空给 `??_M` 造一个 ctor ✗）
- 证据等级：**`size`/`count` 来自指令字面量** ⇒ 对"元素尺寸"是 **A 级** ✓；
  但**归属只到"候选"级**（`evidence=annotation(lowered)`）✓，**永不直接产生 class 级 A 证据** ✓（三路复核的强制要求 ✓）
- **已知漏采（显式）**：
  1. **`ptr` 仅 4/466 是绝对地址** ✓（其余是 `ecx`/`eax` 等寄存器或内存操作数 ✗）⇒ `ptr` **不可用于归属** ✓；
  2. **`dtor` 433/466 是地址** ✓，其余 33 条是改编符号（如 `??1stdiobuf@@UAE@XZ_2`）或 `nullsub_1` ✓ ⇒ 记入 `unresolved_operands` ✓；
  3. 归属判定**只用 size + ctor/dtor** ✓（不假设 `ptr` 可用 ✓）
- **尺寸唯一性不可依赖** ✗：`8704` 同时匹配 `Role` 与 `ScriptSystem` ✓；`896` 唯一匹配 `tagRoleSlot` ✓
  ⇒ 因此产出**候选集合**而非单一答案 ✓（这正是三路复核对 `??_L` "弱判据"的警告 ✓）

## 2. 三个 fixture 的实际裁定（**本交付的核心证据** ✓）

| fixture | 裁定 | 备注 |
|---|---|---|
| `sub_408740`，`size=8704`(0x2200)，ctor `0x411900`，dtor `0x411CA0` | `size_state=**evidenced**` ✓；候选含 **`Role`** ✓；`state=**ambiguous**` ✓ | 尺寸类 = `['Role','ScriptSystem']` ⇒ **不唯一** ⇒ 不硬判 ✓（`RoleSystem` 是错的 ✗：其 `binary_size=4868` ✓）|
| `sub_41F6F0`，`size=896`，ctor `0x4236D0`（注解为 **`BINK::Reset`** ✗），dtor `0x423880` | `size_state=**evidenced**` ✓；候选含 **`tagRoleSlot`** ✓；`state=**conflict**` ✓；**`verified_class=None`** ✓ | **`BINK` 的 `binary_size=932 ≠ 896`** ✓ ⇒ 错锚被**必判定为冲突**而非 verified ✓✓（**全仓 `verified_class=='BINK'` 行数 = 0** ✓）|
| `ctor/dtor = 0x411CA0` 的双重归属 | **暴露** ✓：`active=[PalScript ~PalScript]`（来自 `methods`）/ `retracted=[ScriptObj]`（来自 `functions.json` `type=skip` ✓）；引用该地址的 6 行候选均 ≥2（其中 4 行 `conflict` ✓）| **并单列 `prose_mentions{structured:false}`** ✓：`Scene.json` 的 source 散文提到该地址，但 `Role.json` 的 methods **没有**它 ⇒ **拒绝把散文读成结构化主张** ✓（"那会编造" ✓）|

**裁定总览**：`rows=466`、`evidenced=466`、`state: conflict=375 / ambiguous=70 / candidate=21`、`address_conflicts=104`、
**`verified_class` 非空 = 0** ✓。
⇒ **重要发现（供交付 2/3）**：**没有任何一个类达到 `verified`** ✓ —— 真实注解与指令字面量尺寸**普遍矛盾**，
而 `verified` 分支目前只被合成测试覆盖 ✓ ⇒ 这说明"独立尺寸证据"的价值正在于**暴露普遍矛盾**（而非确认现状）✓。

## 3. `binary_size` 污染口径的解释（91 vs 38）（规格 §0 的落实 ✓）

- **唯一权威算法**：`tools/audit_layout.py::declared_size_geometry`（只读 ✓）
- **锁定基线（881 structs）**：`ratio>3.0` = **38** ✓、`>50.0` = **14** ✓、`ratio==2.0`（四舍五入）= **4** ✓、整数精确 `==2×` = **3** ✓
- **"91" 的来源**：规格初稿引用了**未经复算的一句断言** ✗；其溯源链（spec:8 ← diagnosis:102 ← :104 ← :140）**全是复制、无一处命令输出** ✗
  ⇒ 独立复核指出后由编排者**亲自复算证伪** ✓，并裁定"**今后引用数字必须附可复跑的复算命令**" ✓
- 5 天前的 A 级纪要 AT-200 记 **52** ⇒ 真实计数**随时间下降** ✓
⇒ 本 Spike **不改变**该口径 ✓，只是把它连同"复算命令"一起钉死 ✓（§0 ✓）

## 4. 本交付最有价值的产出：**它把我计划里的 6 个 bug 逼了出来** ✗（其中 2 个致命）

| # | 计划代码的 bug | 若未修的后果 |
|---|---|---|
| 1 | **元组取反** ✗：把**源码 push 顺序**当实参序（x86 cdecl **右→左**，最后 push 才是 `ptr`）| `size` 会取成 **ctor 地址** ✗✗ ⇒ **全库尺寸证据全错** |
| 2 | **`_PUSH` 的 `\s*$` 锚点在真实 asm 全失配** ✗✗（**16601 行** push 带 `; comment`）| 站点大面积 incomplete + **43 条"完整但值全错"** ✗ |
| 3 | `_val` 对 `push offset aWidth` 直接 **`ValueError` 崩溃** ✗（真实 asm 行 8679 ✓）| 工具**跑不起来** |
| 4 | hex 字面量返回**字符串** ✗（与 `size:int` 接口/下游比较不相容）| T4 类型比较恒 False |
| 5 | `\w+` 丢改编符号 ✗（`??1stdiobuf@@UAE@XZ_2`）| 6 个假 incomplete |
| 6 | **SEH funclet 归属** ✗✗：`; START OF FUNCTION CHUNK FOR X` 里的站点**无自身 `proc near`** ⇒ 被挂到**最后一个 proc 名** `sub_55D67E` ✗ | **213/466（45.7%）归属错** ✗，且**已被 T3 固化** ✗ |

**根因（两条，均为"元错误"✗）**：
- **fixture 不具代表性** ✗：我的正则对着**自造的、无注释的 fixture** 调 ⇒ 真实 asm 的 `; comment`、改编符号、funclet 全没覆盖 ✓
- **处方锚点错误** ✗：修复处方里的 `_CHUNK.match(line)` **不可能生效** ✗（`line` 已剥尾注，而 **chunk 头本身就是注释行** ⇒ 剥后为空 ✗）⇒ 必须用 `raw_line` ✓；
  同样的错误**编排者也犯过一次**（植入脚本打印"已植入"却没真正插入 ✗）⇒ **是我自己写的测试把它抓出来的** ✓

## 5. 结论与建议

**结论：Spike 成功 ✓** —— "独立于注解的尺寸/归属证据源"**可行** ✓，且**已经证明它能发现真实矛盾** ✓：
`BINK` 错锚被必判冲突 ✓、`0x411CA0` 双源矛盾被暴露 ✓、**401 条尺寸不自洽痕迹覆盖 375 行** ✓、**`verified` 全仓为 0** ✓。

**建议（交交付 2/3 决定）**：
1. **不宜把本层的"候选"直接当结论** ✗ —— 尺寸不唯一（8704 ↔ `Role`/`ScriptSystem`）+ ctor 归属本身可能错（`sub_411CA0` 被注成 `~PalScript` ✓）
   ⇒ 必须配**第二判据**（vtable 写表签名 / ctor 的 vfptr 安装次序 / `operator new(N)`）✓（与三路复核一致 ✓）
2. **`site` 归属的教训应进通用规则** ✓：**asm 里"没有自己 `proc near`"的 funclet 也要归属宿主** ✓；
   且**失效安全优于猜** ✓（END 之后宿主未知 ⇒ `site=None`，宁可缺失也不误挂 ✓——已实现并测试 ✓）
3. **本交付未接任何硬门禁** ✓ —— 若要接，须先按规格 §5.5 补"注入式负例作为必跑命令 + 恒假检测 + 单一责任人" ✓
4. **建议先做"第二判据"再清存量** ✗（规格 §2.5 的 ROI 前置：本层受益面是 **O(10–38)** 个类，而射程外占当前错误 **≥59%** ✓）
