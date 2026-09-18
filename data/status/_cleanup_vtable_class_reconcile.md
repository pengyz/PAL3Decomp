# vtable ↔ 类 全局对账（只读取证）— 2026-09-17

> **本文件只记录取证结论，不含任何 annotation 改动。** 落地清单见 §6，需单独审议。

## 1. 结论摘要

| vtable | 现挂在哪 | 真实归属 | 证据强度 |
|--------|----------|----------|----------|
| `0x56AC20` | `UIProgressBar.json` | **UI3DCtrl** | **A（三链互证）** |
| `0x56AD64` | `UIButton.json` | **UIProgressBar** | **A（三链互证）** |
| `0x56ACFC` | `UI3DCtrl.json` | 某个 **84 字节 UIWnd 派生类**（最佳候选 `UIFlexBar`）| **B（仅下界 + 成员集吻合）** |

并且：**这不是"三个 `vtables` 字段写错地址"，而是 `methods`+`vtables` 整块与 `known_members`+`binary_size` 错配**
（见 §4）——所以修法比"改一个地址"重。

## 2. 三链 A 级证据

### 2.1 `0x56AC20` = UI3DCtrl（尺寸 308）

链 1 — **内嵌成员 stride**（同一函数内连续构造的两个成员，偏移差 = 类尺寸）：

```
SaleUI::InitUI  0x5251f8 lea 0xfa4(%esi),%ecx   0x525203 call 0x439030
                0x525208 lea 0x10d8(%esi),%ecx  0x525213 call 0x439030
                0x525218 lea 0x120c(%esi),%ecx  0x525223 call 0x439030
       0x10d8-0xfa4 = 0x134 = 308 ；0x120c-0x10d8 = 0x134 = 308
```
`python3 tools/vtable_class_reconcile.py --stride 0x439030` → **stride 0x134，4 对**
（`0x47e769`、`0x4a71a5`、`0x525203`、`CCCTData`）。全注解集里 **只有 UI3DCtrl 的 `binary_size` 是 308**。

链 2 — **ctor 的 `this` 写入覆盖整个成员块**：
`0x439030` 写入偏移 `236,240,244,248,252,256,260,264,268,272,276,280,284,288,292,296,300,304`，
`req = 308`。这些偏移**逐一命中 UI3DCtrl 的 `known_members`**（`232,236,240,244,248…296`）。

链 3 — **该类自己命名的非虚方法访问同一块**：
`UI3DCtrl.json` 的 `LoadModel(0x52AF20)` / `UpdateRotation(0x52E8C0)` / `UpdateTransform(0x52EAC0)`
访问 `228,232,236,240,244,248,260,264,268,272,276,284,288…294`——与链 2 同一区块。

> 注：`0x439030` 的 `--stride` 还给出 `0x170=368` 一对（JusticeBookUI `1912→2280`）。
> 这是"两次构造之间夹了别的成员"，所以**取最小 stride**、并报对数——单对不足为凭。

### 2.2 `0x56AD64` = UIProgressBar（尺寸 244）

链 1 — **堆分配实参 = sizeof（独立于 annotation）**：
```
44f8fd push $0x14c ; 44f902 call 0x55353b(operator new) ; 44f91c call 0x450710  ⇒ sizeof(UILoadingFrm)=332
```
`--stride 0x43f7f0` → `heap sizes: {'0xf4': 2}` ⇒ **两处 `new(0xF4=244)` 后调用 `0x43F7F0`**。

链 2 — **stride**：`UITitle_BBTY` `0x451ced` `off 0x44` → `0x451cfd` `off 0x138`，差 `0xF4 = 244`。

链 3 — **调用点语义 + 上界排除**：`UILoadingFrm.m_LoadProgress`（偏移 `0x48`=72，声明类型 `UIProgressBar`）
由 `0x45073d call 0x43F7F0` 构造 ⇒ `0x43F7F0` 是 UIProgressBar 的 ctor ⇒ 它安装的 vptr 是
`0x56AD64`。若该类是 `UIButton`(344)，则 `72 + 344 = 416 > 332 = sizeof(UILoadingFrm)` —— **溢出，不可能**；
`72 + 244 = 316 ≤ 332` ✅。

链 4（补充）— **ctor 写入偏移逐一落在 UIProgressBar 已标注成员上**（`68,72,108,112,116,124,132,136,140…208`，
其中 `88/92/96/100` 等带 `A:PAL3patch_verified(running_code)` 证据）。`req=244` 与 `binary_size` 完全相等。

### 2.3 vptr 安装点（与 annotation 无关的第三方证据）

`tools/vtable_class_reconcile.py --installs` / `vptr_installs()`：扫描全 `.text` 的
`movl $0x5xxxxx,(%reg)`，覆盖 **189 张表**。ctor 与 dtor 都写自己的 vptr，因此成对出现在**相邻函数**：

| vtable | 安装点 | 所属函数 |
|--------|--------|----------|
| `0x56AC20` | `0x43909d`, `0x43914d` | ctor `0x439030` / dtor `0x439130` |
| `0x56AD64` | `0x43f871`, `0x43f98d` | ctor `0x43F7F0` / dtor `0x43F970` |
| `0x56ACFC` | `0x43d83a`, `0x43d880` | `0x43D7F0`? / `0x43D880`（`movl $vptr,(%ecx); jmp 0x445b40`，叶 ctor） |

## 3. 工具

`tools/vtable_class_reconcile.py`（新增，只读）
- `--self-test`：**9/9 通过**，把上面手工核验过的锚点钉成回归用例（stride / `new` 尺寸 / 安装点归属 / 冲突判决）。
- `--stride <ctor>`：报 heap 尺寸 + 内嵌 stride（含对数）。
- `--installs`：vptr 安装点覆盖统计。
- `--all --out ...`：全量对账，输出 `data/status/_vtable_reconcile_20260917.json`。

### 3.1 诚实边界（重要）

**它是候选生成器，不是判决器。** 全量输出里 26 条 `IMPOSSIBLE (req > binary_size)` 是**候选**：
`this` 寄存器跟踪在大型优化函数里会漂移（`%ebp` 被复用为**另一个对象**的指针，例如
`MainEquipUI` 里 `mov 0x3305c(%ebp),%ebx` 与 `mov 0x2a774(%ebp),%al` 混用），
于是 `req` 会算出 `205776` 这类荒谬值。**每条 `IMPOSSIBLE` 都必须再用 §2 的 stride / `new` / 安装点链条复核**，
做法已产品化（`--stride <ctor>`）。

候选打分（`candidates`）尤其不可信：低偏移人人命中，实测 `_D3DCAPS9` / `ASISTAGE` 会靠 ratio 挤到榜首。
`--self-test` 因此**只断言可证明项**，不断言 `candidates[0]`。

## 4. 真正的病：`methods`+`vtables` 与 `known_members`+`binary_size` 错配

三份 JSON **各自内部**（`methods` ↔ `vtables`）是自洽的：

| 文件 | `methods` 簇 | 其 `vtables` 的槽位 | `known_members`/`binary_size` 实际属于 |
|------|--------------|---------------------|----------------------------------------|
| `UIProgressBar.json` | `0x439030,0x439410,0x439810,0x439A20`(+`0x43FDC0/D0/E0/FDF0`) | `0x56AC20` = `0x439410/0x439810/0x439A20/0x439110` ✅ | **UIProgressBar**（244，与 `0x43F7F0` 的写入偏移吻合）|
| `UI3DCtrl.json` | `0x43D830/0x43D860/0x43D880/0x43D890/0x43D920/0x43D940` **+** `0x52AF20/0x52B050/0x52E8C0…` | `0x56ACFC` = `0x43D860/0x43D890/0x43D920/0x43D940` ✅ | **UI3DCtrl**（308，链 2/3 吻合）|
| `UIButton.json` | `0x43F7F0/0x43F950/0x43F970/0x43F9C0/0x43FF00/0x43FF70/0x440560` | `0x56AD64` = 同簇 ✅ | **UIButton?**（344，但 ctor 实测 244）|

⇒ 即 **`methods`+`vtables` 这一整块被挂到了错误的类上**，而 `known_members`+`binary_size` 大体是对的。
改写 `vtables.addr` 一个字段**不足以**修复：`methods` 仍留在错误的类里。

## 5. 未决问题（不落地）

1. **`0x56ACFC` 属于谁**：只有下界（`req=84`）+ 成员集吻合（访问到的派生区偏移恰为 `{68,72,76,80}`）。
   `UIFlexBar`（`binary_size=84`，`base=UIWnd`，own `{68,72,76,80}`，且**当前 `vtables:[]`、`methods:{}`**）
   是最佳候选，但 `--stride 0x43d880` **测不出小 stride**（只有跨函数假值）⇒ **不到 A 级**。
   `CCBParabolaWindow`/`CCBSkillWindow` 也是 84 且成员吻合，但它们的 `0x57058C`/`0x570570`
   已由 `0x51c23c`/`0x51bbbc` 真实安装（**表被占用**）。
2. **UIButton(344) 的表在哪**：三簇都不是 344。需要按 `--stride`/`new(0x158)` 全量搜 344 的 ctor。
3. **26 条 `IMPOSSIBLE`**：逐条用 §2 方法复核（含 `UIFrameWnd req=172>72`、`UIMap req=352>152` 等
   更像漂移假阳性）。

## 6. 落地清单（待审议，附 ROI）

**可立即落地（A 级）**
1. `UI3DCtrl.json`：`vtables` 改为 `0x56AC20` + 槽位表；从 `UIProgressBar.json` 迁入
   `0x439030(ctor)`, `0x439410(Render,ord1)`, `0x439810(Destroy,ord3)`, `0x439A20(CheckRayHitRole,ord2)`。
2. `UIProgressBar.json`：`vtables` 改为 `0x56AD64` + 槽位表；从 `UIButton.json` 迁入
   `0x43F7F0(ctor)`, `0x43F970(dtor)`, `0x43F950`, `0x43F9C0(Destroy,ord3)`,
   `0x43FF00(Create,ord4)`, `0x43FF70(Render,ord1)`, `0x440560(Update,ord2)`；
   并删掉三条 `GetWidth/GetHeight/GetPosition` 里**已证伪的 `sizeof(UIProgressBar)=308` 论据**
   （它们本身仍属 UIProgressBar：访问 `140/144/148 < 244`）。
3. `UIButton.json`：清空被证伪的 `methods`/`vtables`，`binary_size` 待重新取证（344 是否有独立证据？）。

**ROI 估计**
- 收益：`emit_headers.class_vtable_slots()` 按 `vtables` 给类发 `virtual` ⇒ 修对之后
  **UI3DCtrl / UIProgressBar / UIButton 三类的虚函数声明回到正确的类**，直接影响生成头文件与字节匹配；
  同时解锁 §5.1/§5.2 的补录（`UIFlexBar` 空记录、`UIButton` 缺表）。
- 成本：3 个 JSON 的手工迁移 + `check` + `audit_layout` + `audit_log` + `apply/export/codegen all`
  + `probe s2` + `match`（`L1` 不得回退）+ `compile_regression.py`。估计 **1 个落地槽位**。
- 风险：**中**。迁 `methods` 会改变头文件里的虚性判定 ⇒ `probe` 的 ok/L1 可能双向变动；
  必须先归档 `probe_census.json` 再做 A-B-A（本会话已把 pre-state 归档到
  `data/status/archive/20260917_1549/`）。

**不建议**：在本轮一并处理 §5.1/§5.2（证据不到级），以及那 26 条漂移候选。

## 7. 与本会话既有勘误的关系

- 本结论**替换**了此前 `UIProgressBar.json` 里 `_evidence` 字段中的 `sizeof(UIProgressBar)=308` 论证
  （该论证已在 `_cleanup_landing_uiwnd_3methods.md` §4 撤回）。**新论证更强**：
  `140/144/148 < 244`，且 244 现有三条独立证据（§2.2）。
- UIWnd 三方法（`GetWidth/GetHeight/GetPosition`）**迁移本身是对的**，只是当初的理由（308）是错的。
- 与 `docs/knowledge/gotcha_pdb_identity_drift_vtable_arbitration.md` 一致：
  "ctor 安装的 vtable 值 = 类的身份证"。本次新增**定量**手段（stride / `new` 实参）。