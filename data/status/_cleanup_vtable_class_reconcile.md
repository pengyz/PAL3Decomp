# vtable ↔ 类 全局对账（只读取证）— 2026-09-17

> ## ⛔ 状态：§8 的落地已于 2026-09-18 **回退**（独立复核 `e1140ba4` 判定 blocker）
>
> **回退原因**（复核结论，我已复现确认）：
> 1. `tools/compile_regression.py` 明确报 `- pal3/src/Misc/UI3DCtrl.cpp`（21 errors）——
>    那 20 个错误只是从 `UIProgressBar.cpp` **搬**过来，但 `s4` 里 **11 条 UI3DCtrl 符号（含 1 条 L1）随之消失**，
>    其中 **7 个方法本就属于 UI3DCtrl**。总 `L1 17→17` 是**成分替换**造成的假平稳
>    （0x43F950 / 0x43D860 两个函数仍在 L1，只是改名换 TU）。
> 2. 清空 `UIButton.json` 使 UIButton 失去 `__vftable` ⇒ **`pal3/src/Misc/UIButton.cpp` 不再生成**，
>    并让 `CCBControlWindow.cpp` 等报 `'__vftable' : is not a member of 'UIButton'`。
> 3. 「UIButton(344) 真表未找到」**是错的**：复核找到 ctor **`0x43A770`**（`call 0x445aa0` 直系 UIWnd 派生 →
>    `movl $0x56ac70,(%esi)`）+ `push $0x158; call 0x55353b` ×2 ⇒ **size 344**，stride 0x158 有 **106 对**；
>    而 `0x56AC70` 现被 **`UICaption`(binary_size=96)** 声明 ⇒ **第 4 处同类错配**。清空只是把"错挂"变成"空"。
>
> 按 CLAUDE.md「发现退化立即报警，不提交」，5 个 JSON 已回退到 pre-state
> （快照 `data/status/archive/20260918_1423_vtable_reconcile/`，回退方法见其 README）。
> **§2 的归属结论（哪张表属于哪个类）经复核全部成立**（见 §1 表），不成立的是"可以这样落地"。
> 下文 §2.1/§2.2/§2.4/§3/§4/§6.3 中若干措辞已被复核证伪，**逐条见 §11 勘误**；引用时以 §11 为准。


> **本文件只记录取证结论，不含任何 annotation 改动。** 落地清单见 §6，需单独审议。

## 1. 结论摘要

| vtable | 现挂在哪 | 真实归属 | 证据强度 |
|--------|----------|----------|----------|
| `0x56AC20` | `UIProgressBar.json` | **UI3DCtrl** | **A（三链互证）** |
| `0x56AD64` | `UIButton.json` | **UIProgressBar** | **A（三链互证）** |
| `0x56ACFC` | `UI3DCtrl.json` | **UIFlexBar**（84 字节）| **A（ctor 写入成员集逐一吻合 + 尺寸吻合）** |

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
| `0x56ACFC` | `0x43d83a`（真 ctor `0x43D830`）, `0x43d880`（**不是 ctor**，见 §2.4）| — |

### 2.4 `0x56ACFC` = UIFlexBar（84 字节）

**先修正一处自己的错误**：`0x43D880` **不是 ctor**。它是
```
43d880: movl $0x56acfc,(%ecx)
43d886: jmp  0x445b40
```
而 `0x445b40`（`UIWnd::UIWnd`）在 `0x445b5d` 立刻写 `movl $0x56aec8,(%esi)` —— **把它覆盖掉**。
所以它只是"装 vptr 然后尾调基类 ctor"的 stub（`??_E` 一类），**不能**用来推断类尺寸
（这正是 `--stride 0x43d880` 测不出小 stride 的原因）。

真 ctor 是含 `0x43D83A` 的 **`0x43D830`**（37 字节，`int *__thiscall`，返回 `this`）：

```
43d833: call   0x445aa0           ; 基类 ctor
43d83a: movl   $0x56acfc,(%esi)   ; 装本类 vptr
43d840: mov    %eax,0x50(%esi)    ; 偏移 80 = 0
43d843: mov    %eax,0x4c(%esi)    ; 偏移 76 = 0
43d846: mov    $0x20,%eax
43d84b: mov    %eax,0x44(%esi)    ; 偏移 68 = 0x20 = 32
43d84e: mov    %eax,0x48(%esi)    ; 偏移 72 = 32
```

它初始化的偏移**恰好是 `{68,72,76,80}`**，`req = 84`。

而 `UIFlexBar`（`UIFlexBar.json`，`base=UIWnd`）：
- `binary_size = 84` ✅ 与 `req` 完全相等
- `known_members` own = `{0, 68, 72, 76, 80}` ✅ 与被初始化的偏移**逐一相同**
- 当前 `vtables: []`、`methods: {}` —— **空记录**（正是 `vtable_scanner.py` 记录的"57 个类没有虚表记录"之一）

三个竞争候选里，`CCBParabolaWindow`/`CCBSkillWindow` 同为 84 但其 `0x57058C`/`0x570570`
已由 `0x51c23c`/`0x51bbbc` 真实安装（表被占用）⇒ **UIFlexBar 是唯一未被占用且成员集完全吻合的 84 字节类**。

> 这条同时解释了 `UI3DCtrl.json` 的 `0x43D830` 方法为何**名字**叫 `"UI3DCtrl"`：
> 那是"把所在文件的类名当 ctor 名"的**循环命名**，无独立证据权重（见
> `gotcha_pdb_identity_drift_vtable_arbitration.md`：名字都是"谁说的"，不是二进制说的）。

## 3. 工具

`tools/vtable_class_reconcile.py`（新增，只读）
- `--self-test`：**12/12 通过**，把上面手工核验过的锚点钉成回归用例（stride / `new` 尺寸 /
  安装点归属 / 冲突判决 / cluster B 的 `this` 写入集 / `0x43D880` 是 stub）。
- `--stride <ctor>`：报 heap 尺寸 + 内嵌 stride（含对数）。
- `--writes <ctor>`：列出该 ctor 的 `this` 写入偏移，并**反查** `binary_size == req` 且
  成员集覆盖的注解类（cluster B 用它一次列出 `CCBParabolaWindow/CCBSkillWindow/UIFlexBar`，
  再用"表是否已被占用"排除前两个）。
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

1. ~~`0x56ACFC` 属于谁~~ —— **已定谳：UIFlexBar**（§2.4）。
2. **UIButton(344) 的表在哪**：三簇都不是 344。需要按 `--stride`/`new(0x158)` 全量搜 344 的 ctor。
   **在找到之前 `UIButton.json` 的 `binary_size=344` 与 `known_members` 都缺独立证据**
   （`0x43F7F0` 实测 244 已证其 `ctor_17` 归属为假）。
3. **26 条 `IMPOSSIBLE`**：逐条用 §2 方法复核（含 `UIFrameWnd req=172>72`、`UIMap req=352>152` 等
   更像漂移假阳性）。

## 6. 落地清单（待审议，附 ROI）

**可立即落地（全部 A 级，4 文件）**
1. `UI3DCtrl.json`：`vtables` 改为 `0x56AC20` + 其槽位表；从 `UIProgressBar.json` 迁入
   `0x439030(ctor)`, `0x439410(Render,ord1)`, `0x439810(Destroy,ord3)`, `0x439A20(CheckRayHitRole,ord2)`；
   **移出** `0x43D830(ctor)/0x43D880/0x43D860/0x43D890/0x43D920/0x43D940`（→ UIFlexBar）；
   保留 `0x52AF20/0x52B050/0x52E8C0/0x52E940/0x52E9C0/0x52EA40/0x52EAC0`（本就属于它）。
2. `UIProgressBar.json`：`vtables` 改为 `0x56AD64` + 其槽位表；从 `UIButton.json` 迁入
   `0x43F7F0(ctor)`, `0x43F970(dtor)`, `0x43F950`, `0x43F9C0(Destroy,ord3)`,
   `0x43FF00(Create,ord4)`, `0x43FF70(Render,ord1)`, `0x440560(Update,ord2)`；
   **移出** `0x439030/0x439410/0x439810/0x439A20`（→ UI3DCtrl）；保留 `0x43FDC0/D0/E0/FDF0`；
   并删掉三条 `GetWidth/GetHeight/GetPosition` 里**已证伪的 `sizeof(UIProgressBar)=308` 论据**
   （它们本身仍属 UIProgressBar：访问 `140/144/148 < 244`）。
3. `UIFlexBar.json`：补 `vtables` = `0x56ACFC` + 槽位表；从 `UI3DCtrl.json` 迁入
   `0x43D830(ctor)`, `0x43D860(ord5)`, `0x43D890(ord7)`, `0x43D920`, `0x43D940(ord1)`。
4. `UIButton.json`：清空被证伪的 `methods`/`vtables`（其真表未找到）；`binary_size=344` 标注为待取证。

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
---

# 8. 落地结果（2026-09-18）—— A-B-A 实测

落地内容：4 文件 `methods`+`vtables` 整块迁移（§6 清单），**并追加** 2 个同簇方法
（`0x43D920 Destroy(ord3)`、`0x43DAB0 RenderQuadSlice`，原挂 `UIStatic.json` —— 见 §9）。

管线段：`check`(PASS 0 errors) → `audit_layout`(PASSED) → `apply` → `annotation_diff`(变更集=意图) →
`export`(3599 decomp 刷新) → `codegen all` → `compile` → `probe all` → `match`。

## 8.1 指标（pre = `data/status/archive/20260918_1423_vtable_reconcile/` + 基线 `20260917_201614`）

| 指标 | pre | post | Δ |
|------|-----|------|---|
| probe **s1** ok | 731/751 | 731/751 | 0 |
| probe **s2** ok | 61/202 | **62/202** | **+1** |
| s2 fail_own | 141 | 140 | −1 |
| **s4 `match_L1`（硬线）** | **17** | **17** | **0** ✅ `[L1 ratchet] previous 17 -> current 17` |
| s4 matched | 191/218 | 194/228 | +3 |
| s4 partial | 149 | 150 | +1 |
| s4 unmatched | 27 | 34 | +7（UIFlexBar 新符号名不在预期表） |
| unresolved_synth | 25 | 27 | +2 |
| error_classifier 失败文件 | — | 140（annotation_fix 63 / codegen_fix 29 / hexrays_limit 41 / manual_idb 1 / unknown 6） | — |

## 8.2 生成头文件的效果（落地目的达成）

| 头文件 | pre | post |
|--------|-----|------|
| `UIProgressBar.h` | `Render@0x00439410 / CheckRayHitRole@0x00439A20 / Destroy@0x00439810`（**UI3DCtrl 的函数**）| `Render@0x0043FF70 / Update@0x00440560 / Destroy@0x0043F9C0 / Create@0x0043FF00` ✅ |
| `UI3DCtrl.h` | `Render@0x0043D940 / CreateWithTexture@0x0043D890`（**UIFlexBar 的函数**）| `Render@0x00439410 / CheckRayHitRole@0x00439A20 / Destroy@0x00439810` ✅ |
| `UIButton.h` | 4 个 `virtual`（**其真表未找到**）| 0 个 `virtual` ✅（诚实化）|
| `UIFlexBar.h` | **零个 virtual**（但其有虚表 ⇒ 必然字节不匹配）| `~UIFlexBar / Render@0x0043D940 / CreateWithTexture@0x0043D890` ✅ |

## 8.3 错误账：**同一多重集搬移 +2**

`UIProgressBar.cpp` 基线 **fail, 20 errors** → 现在 **ok, 0**；`UI3DCtrl.cpp` 0 → **21**。
按 `(code,msg)` **忽略行号**比对：两者**相同 20 条**，`UI3DCtrl.cpp` 多 1 条
`C2660 'QueryState' : function does not take 1 parameters`。

`RoleAtt.cpp` 22 → 23：按 `(code,msg)` 比对，**真实新增仅 1 条**
`C2059 syntax error : ')'`（`RoleAtt.cpp:123`）；其余差异是
(i) **行号漂移**（同一条 C2664 由 668→667，`(code,line)` 比较把它算成"删+增"）、
(ii) 我的重命名使反编译文本里的 `->UIButton` 变成 `->UIProgressBar`（C2653/C2227 各 1 条，数量不变）。

⇒ **净增量 = 2 条**，且两条都在**本就失败**的单元里，分属两个**已归档的 codegen 缺口族**：
- `C2059`：`...->UIProgressBar::FindChildByName(` —— **单段限定名**调用点。
  `pipeline/gen/ast_transform.py` 的安全网 `_QUAL2` 要求 `(?:Ident::){2,}`，**单段不触发**（既有 C5(a) 的延伸）。
- `C2660 QueryState`：已知 C2660 **原型约定**族（annotation 参数数 vs `ret N` vs 调用点实参数）。

按 CLAUDE.md「**编译错误不是 annotation 回退理由**」，且 `L1` 硬线与 s2 ok 都未退化，**保留落地**；
上述 2 条作为独立后续项（不属本次归属修复范围）。

## 8.4 本次实测暴露的**门禁盲区**（第二个实证）

`tools/regression_detector.py` 同时踩两坑：
1. **按 `(code,line)` 比较** ⇒ 生成文件行号漂移会把同一条错误报成"新错误 + 已消失"。
   实证：`RoleAtt.cpp` 的 C2664 由 668→667，被判为新增。
2. **只比计数** ⇒ **错误在文件间整体搬移**（方法体迁移）看起来像回归。
   实证：`UIProgressBar.cpp` −20 / `UI3DCtrl.cpp` +20 被报成"新失败"。

⇒ 修法（与既有待办一致）：改成比 **`(code,msg)` 多重集**（忽略行号），并对"搬移"做
跨文件多重集抵消后再判回归。已记入 `docs/knowledge/gotcha_measurement_bench_replicating_subject_logic.md` 附四。

## 9. 追加：`0x43D920` / `0x43DAB0` 同属 cluster B

两者原挂 `UIStatic.json`，而 `UIStatic` 自身 18 个方法的地址**全在 `0x440740..0x44BExx`** ⇒ 它们是离群项。

| 函数 | 长度 | `this` 访问 | 判定 |
|------|------|-------------|------|
| `0x43D920` | 25 B | 只 `76` | cluster B 的 `Destroy`（`mov 0x4c(%esi),%ecx; test; je; call *0x56a58c; movl $0x0,0x4c(%esi)` = 释放 `m_tex: gbTexture*@76`）；且它是 `0x56ACFC` 的 **slot3**，**不是** `UIStatic` 两张表（`0x56AD88` slot3=`0x440BA0` OnMessage / `0x56AE48` slot3=`0x442420`）的任何槽位 |
| `0x43DAB0` | 400 B | 恰 `{68,72,76,80}`，req=84 | cluster B 的非虚方法 `RenderQuadSlice` |

迁移后 `UIFlexBar` 的 ordinal 为 **1/3/5/7**，恰好落在 8 槽表的 4 个重写位上
（`0x56ACFC` = UIWnd 的 7 槽 + 本类新增虚函数 `CreateWithTexture`@slot7）—— 强内部一致性。
另把 `0x56ACFC` slot3 的 `from` 由 `"CCBProtectWindow"` 改为 `null`（本类重写）。

**cluster B 归属的第 4 条独立证据**：`0x445aa0` 装 `0x56aec8`(=UIWnd 的表) ⇒
`0x43D830` 是"先调 `UIWnd::UIWnd`(0x445aa0) 再覆盖 vptr"的**直系 UIWnd 派生**标准形态，
与 `UIFlexBar.json`(`base_class:[UIWnd]`, `base_size:68`, `binary_size:84`) 吻合。
**第 5 条**：ctor 写 `m_tilewidth=0x20, m_tileheight=0x20, m_tex=0, m_style=0` —— 与
"flex/tile bar"(tile 32px) 语义吻合。

---

# 10. 方法论推广到全部 178 张已安装表（2026-09-18）

## 10.1 能不能推广：**能**，且 1.2 秒跑完

`tools/vtable_class_reconcile.py --audit` 把 §2 的三种取证手段自动套到**每一张**由 ctor/dtor 安装的表上：

| 手段 | 实现的函数 | 覆盖 |
|------|-----------|------|
| vptr 安装点 → (表, ctor, dtor) | `site_index()` / `vptr_installs()` | **178 张表** |
| 内嵌成员 stride → 类尺寸 | `measured_size()`（**要求同基址寄存器**） | 9 张 |
| `new` 实参 → 类尺寸 | 同上（`last_new`） | 1 张额外 |

一次遍历全 `.text` 预计算（`site_index()` 缓存），避免 178× 重复反汇编 —— 全量 **1.2 s**。
输出 `data/status/_vtable_audit_global.json`。

## 10.2 全局结果（证据已分级）

```
NO_MEASUREMENT   80     # 无内嵌/new 证据（单例、静态、其他构造路径）
UNASSIGNED       89     # ctor 安装了表，但没有任何注解类声明它  <<< 最大机会
SIZE_CONFLICT     5
SIZE_OK           4
total           178
by tier (仅 SIZE_*): A=5  B=4
```

**分级规则**（`tier`）：`A(new)` = 有 `new` 实参（独立于 stride）；`A(stride xN)` = N≥3；
`B(stride xN)` = N≤2。理由是实测：`0x43bce0` 给出**互不一致**的 272(×1)/280(×1) ⇒ 1~2 对的 stride
可能是"同函数里两个宿主对象 / 嵌套对象"的巧合，**必须先手验**。

### SIZE_OK（4，含本次落地的 3 张 + 1 张新独立确认）

| 表 | ctor | 实测 | 声明 | 级别 |
|---|---|---|---|---|
| `0x56AC20` | `0x439030` | 308 | UI3DCtrl 308 ✅ | A(stride x4) |
| `0x56ACFC` | `0x43D830` | 84 | UIFlexBar 84 ✅ | B(stride x1) |
| `0x56AD64` | `0x43F7F0` | 244 | UIProgressBar 244 ✅ | B(stride x1) + `new(0xF4)×2` |
| `0x56AD40` | `0x43DFC0` | 1208 | **UIListBox 1208** ✅ | A(stride x17) |

⇒ `UIListBox` 是**本次方法独立确认**的又一例（未做任何手工工作）。

### SIZE_CONFLICT（5，A/B 级候选工作清单）

| 表 | ctor | 实测 | 现声明 | 声明尺寸 | 级别 | 备注 |
|---|---|---|---|---|---|---|
| `0x56AC70` | `0x43A770` | **344** | UICaption | 96 | **A(stride x106)** | 106 对压倒性；344 恰为 `UIButton` 的声明尺寸 ⇒ **可能是 UIButton 的真表**（§5.2 未决项） |
| `0x56AD88` | `0x440740` | **248** | UIStatic | 152 | **A(stride x19)** + `new(0xF8)×3` | `new` 实参是独立第二链 |
| `0x56E190` | `0x4A12F0` | **1368** | UIRoleDialog | 720 | **A(stride x9)** | |
| `0x56ACD8` | `0x43BCE0` | 272 | UIScene | 344 | B(stride x1) | stride 出现互不一致的 272/280 ⇒ **可能假** |
| `0x56AE2C` | `0x443190` | 192 | CCBPanelSlot, UIWnd | 476 / 68 | B(stride x1) | "UIWnd 拥有第二张表"本身可疑 |

## 10.3 纪律：这些是**候选**，不是结论

本次落地的 3 张表各有 **3 条互相独立的链条**（安装点归属 + stride + `new`/调用点语义 + 成员集覆盖）。
`--audit` 的 `measured` 只是其中**一条**（stride 或 new）。因此：

- **A 级冲突**（`0x56AC70`/`0x56AD88`/`0x56E190`）值得排进落地槽位，但**仍需**补齐第二、三条链
  （成员集覆盖、调用点语义、表槽位与 ordinal 自洽性），并跑完整管线 + A-B-A。
- **B 级冲突**必须先手验 stride 是否真（把 `--stride <ctor>` 的对数与偏移逐个看，确认同基址寄存器、
  且两次构造确为**相邻成员**）。
- **89 张 UNASSIGNED** 是比"补 5 个错挂"大得多的机会：它们是"ctor 真的安装了表，但注解里没有类认领"，
  对应 `docs/knowledge/gotcha_vtables_not_derivable_from_bytes.md` 里"57 个类没有虚表记录"的问题
  —— 现在有了**带安装点证据**的 89 张表清单，补录不再是猜。

## 10.4 已知残余弱点（不许当结论用）

1. `site_index()` 不跟踪寄存器被改写/重载 ⇒ 同一函数里 `%esi` 换成另一个宿主对象时仍会被当成"同基址"。
   `--audit` 的 B 级分级就是这个弱点的缓冲；**A 级（`new` 实参）不受影响**。
2. `stride` 只在"同一 ctor 被连续调用 ≥2 次"时才有值 ⇒ 覆盖率天然低（9/178）。这是**方法上限**，不是缺陷。
3. `UNASSIGNED` 判据是"注解里没有 `vtables[].addr` 等于该表"。多继承子表、`??_E` 之类 stub 安装的表
   会落进来（本次 `0x43D880` 即一例）⇒ 需要按安装点函数是否为真 ctor 再筛一遍。

---

# 11. 勘误（独立复核 `e1140ba4`，2026-09-18）—— 逐条

复核独立自写 PE/dword 分析器（未复用我的工具），只读。**§2 的三处归属结论全部成立**，
被证伪的是我的**论证措辞**、**工具断言**与**落地处置**。逐条：

| 位置 | 我原来写的 | 复核结论 | 更正 |
|------|-----------|---------|------|
| §2.1 链 2 | ctor 写偏移"**逐一命中** UI3DCtrl 的 `known_members`" | **假**：写入含 **+300/+304**，而 known_members 只到 **+296**（且 +232 是成员却未被写）。工具因 `set(w) <= own` 失败而**打不出任何匹配候选** ⇒ 这条"吻合"从未被机器验证 | 改为「覆盖 16/18，尾部 +300/+304 未注解；+232 未写」。**归属结论不受影响**：靠 `req=308` + stride 0x134 + 表只此一张 |
| §2.2 链 4 | 写偏移"**逐一落在** UIProgressBar 已标注成员上" | **假**：ctor 写到 **+240**，known_members 只到 **+220**（+224/228/232/236-238/240、+219 无注解） | 改为「前段吻合、尾部 7 个偏移未注解」 |
| §2.4 | `0x445b40` = `UIWnd::UIWnd`；`0x43D880` 是"尾调基类 **ctor** 的 stub（`??_E`）" | **种类搞错**：`0x445aa0` 才是 UIWnd ctor（装 0x56aec8 + 构造 +0x24 成员）；`0x445b40` 装 0x56aec8 后调 `0x445c10`、**析构 +0x24 成员** ⇒ 是 **`~UIWnd`**；故 `0x43D880` 是 **84 类的析构 `??1`**（`0x43D860`=`??_G` 调它） | 措辞更正；"不能用于推尺寸"的结论仍对 |
| §2.4 | "三个竞争候选里 CCBParabolaWindow/CCBSkillWindow 同为 84" | 不实：`binary_size==84` 有 **7 个**类 | 改为：`{68,72,76,80}⊆own` 的类有 40+，`bs==84 ∧ 直系 UIWnd 派生` 才收敛到 UIFlexBar；CCB* 用**层次**排除（其 ctor `0x51c210`/`0x51bb90` 先 `call 0x43dcd0` = UIFrameWnd 层） |
| §2.4 / §10 | cluster B 的 A 级"三链"含"成员集吻合" | **不能区分 UIStatic**（`base=[UIWnd]`，成员 `0,68,72,76,80,84…148` 偏移集相同，同为直系派生） | 真正独立的只有三条：「ctor 写入集 + req=84」「**stride 0x54=84**（复核独立发现：`0x4a7359 lea 0x5d944` / `0x4a7369 lea 0x5d998`，差 0x54，全 .text 唯一）」「直系 UIWnd 派生（调 0x445aa0）」。UIStatic 靠"两张表已被 `0x440740`/`0x443388` 占用"排除（**依赖注解里 UIStatic 表归属正确**） |
| §9 | `0x43D920` 是"cluster B 的 slot3"（隐含唯一） | **部分**：它**同时**是 `0x56AFB0`（**UIWnd.json 自己声明**的表，由多继承类 ctor `0x44A790` 安装）的 slot3；`cmake/MSVCSettings.cmake:141` 是 **`/OPT:ICF`** ⇒ 地址共享是**合并产物** | 保留归属结论（`0x56ACFC` slot3 是直接事实），但必须写明「**ICF 双表共享**」；"只碰偏移 76"**不是**判据（复核：`0x43DAB0` 那类函数也只在 68..80）。反证其**非 UIStatic**：UIStatic ctor `0x440779 movl $0x1,0x4c(%esi)` 把 +76 写成**整数 1**，而 `0x43D920` 把 +76 当**指针**解引用 |
| §9 | `0x43DAB0` = cluster B（理由：this 访问恰为 {68,72,76,80}） | **结论成立，理由错**：UIStatic 同样是这四个偏移，`req=84` 只证明跨度 ≥84 | 换成两条硬证据：① 被 cluster B 的 `Render 0x43D940` 以 `mov %esi,%ecx` **调用 5 次**（`43d992/43d9c1/43da31/43da59/43da99`），全 .text 无绝对引用、不在任何槽位 ⇒ 非虚成员；② `[this+76]` 被**当指针**解引用（`43dade mov 0x4c(%edi),%ecx; 43dae7 fildl 0x1c(%ecx)`），UIStatic 的 +76 是整数 1；③ 按 +80 做 0/1 switch（`43dacb`）与 `m_style`(int) 吻合、与 UIStatic 的 `m_ratioh`(float) 不吻合 |
| §3 | `--self-test` **12/12 通过** | 落地后**必然**变 11/12：该断言是"注解状态快照"，不是二进制回归用例 | 已改：改为断言**不可变二进制事实** + 落地后地面真值（现 18/18）。**教训**：回归用例不许编码注解状态 |
| §4 表 | UI3DCtrl 的 methods 簇含 **`0x43D920`** | **假**：归档只有 `0x43D880/0x43D830/0x43D860/0x43D890/0x43D940`（5 个） | 更正；`0x43D920` 是本轮之后从 UIStatic 迁入的，不在原簇 |
| §6.3 | 「从 UI3DCtrl 迁入 …0x43D920」「未列 0x43D880」 | 与落地不符：实际迁入含 `0x43D880`、**无** `0x43D920` | 更正清单 |
| §5.2 / §6.4 / §8 | 「UIButton(344) 的真表未找到」⇒ 清空其 methods/vtables | **证伪**：ctor `0x43A770` + 表 `0x56AC70` + `new(0x158)`×2 + stride 0x158×106（复核已验证）。清空造成 `UIButton.cpp` 消失与 2 条 L1 标签丢失 | 撤销"清空"；先定谳 `0x56AC70`/`0x56AC90` 属 `UICaption`(96) 还是 `UIButton`(344)（注：`0x43A770` 在注解里被挂成 `NameSys::GetSys`，**又一个自由函数同名**，不可用作名字证据）|
| §10.4(3) | 「UNASSIGNED 含多继承子表与 `??_E` stub」 | 补充：`0x43D880` 实为 **`??1` 析构**（非 `??_E`）；`owning_func()` 会把安装点误归（`0x51c23c` → `CCBMagicWindow::GetActivePage`）⇒ "某表属某类"的**类名来自注解**，不是工具输出 | 工具输出不得作为类名归属的证据 |
| §10.2 | UIStatic 相关推论依赖其 `binary_size=152` | 复核：`0x440740` 的 `rep stos` 写到 `0xf4` ⇒ 真实 ≥248（与 UIStatic 自身 `size_note` 一致） | 标注为预存问题；`0x56AD88` 的 `SIZE_CONFLICT(248 vs 152)` 正是它的表现 |

## 11.1 复核**未能推翻**的部分（我的结论因此更硬）

- **`0x56AC20 = UI3DCtrl`**：复核加了三条我没写的证据 ——
  ① `.rdata` 绝对引用反查：`0x439410→0x56ac24`、`0x439A20→0x56ac28`、`0x439810→0x56ac2c`、`0x439110→0x56ac34`
  **只出现在 `0x56AC20` 一张表** ⇒ 不存在第二张 308 表/多继承；
  ② **第二条独立 308 stride**：`0x4ac421 lea 0x2b7bc(%ebp)` / `0x4ac4a8 lea 0x2b8f0(%ebp)` 两处 `call 0x439230`，
  差 `0x134`；而 `0x439230` 是**同类方法**（`new(0x118)` 后装 `0x56a66c`，非 ctor）；
  ③ 上界排除与注解无关：`0x439444 mov 0x124(%esi),%ecx` ⇒ 292+4=296 > 244。
  另：UI3DCtrl 保留的 7 个非虚方法逐条量 `req = 260/280/292/293/294/295/296`，**全 >244** ⇒ 保留正确。
- **`0x56AD64 = UIProgressBar`**：`new(0xF4)`×2（第三处 `push $0xf4` 后接 `call *0x56a4cc`，属另一类 ⇒ 工具未混入）、
  stride 0xF4 **全 .text 唯一**、`sizeof(UILoadingFrm)=332`。
- **槽位表长度污染**：这 3 张表后紧跟浮点常量（`0x43B38000`/`0x41400000`/`0x3EAAAAAB`），
  原始 dword 数 = **7/8/7** 与注解逐一相同，`ordinal == slot index` 三表自洽 ⇒ **把 8 槽表搬到 UIFlexBar 没引入新错误**；
  `docs/knowledge/gotcha_vtables_not_derivable_from_bytes.md` 的"不可导出"在这 3 张表上不适用。
- `0x4C6831` / `0x52B050` 未被误移（`git diff` 确认）。

## 11.2 复核未证实但仍待办（不可当结论）

- **`0x56AC70` 属 `UICaption` 还是 `UIButton`**：复核能证明"存在 344 字节、装 `0x56AC70` 的 ctor `0x43A770`"，
  但**不能**只凭二进制定其名字（两者 known_members 都只部分吻合）。需额外取证：
  `0x56AC90`（派生表）的安装者是否 `call 0x43A770`；两组槽位函数的 this 跨度。
- **UIStatic 的离群方法不止 2 个**：复核逐条量完后另有 2 个**不可判**项 ——
  `0x44BE60 DestroyChainToBase`（12B，不访问任何 this 偏移）、`0x4538D0 IsHidden`（11B，只读 76，
  且 **0x4538D0 远在 0x44BE60 之外** ⇒ 我在 §9 写的"UIStatic 方法全在 `0x440740..0x44BExx`"**不成立**）。
- **UI3DCtrl 缺 3 个注解**：dtor `0x439130`、`??_G 0x439110`（⇒ 表 slot5 无名）、同类第二 308 交点 `0x439230`。
- **`0x56AC20` slot5=`0x439110` 的 `from` 仍写 `"UIWnd"`**，而 UIWnd 表 slot5=`0x445B20` ⇒ 应为 `null`。
- 复核指出工具 3 个实现缺陷：`--writes` 候选过滤用 `binary_size == req`（**藏掉更大的类**，如 UIStatic 被 `0x43dab0` 隐藏）
  ⇒ 应改 `>= req` 并标注"下界判据"；`is_thiscall()` 走 decomp（注解经 IDB 的产物）⇒ 对被测注解是**循环论证**
  （且 decomp 有错名：`0x439130` 是 308 类 dtor 却签名 `PalScript *this`/名 `PalScript::Reset`）；
  `owning_func()` 误归属。**`--writes` 已改为 `>= req`（见工具 v 后续提交）。**

## 11.3 结论

- **§2 / §9 / §10 的归属判断：成立**（复核逐条攻击均失败，且新证据更强）。
- **§8 的落地：不成立**，已回退。正确顺序是：
  ① 修 `UI3DCtrl.cpp` 的 18 个 `codegen_fix`（`C2664 SetAxisAngle`/`C2100 illegal indirection` 等，
  是**既存**缺口，只是换了个文件暴露）**或**先接受 `UIProgressBar.cpp` 继续失败；
  ② 定谳 `0x43A770 + 0x56AC70/0x56AC90` 的归属，让 `UIButton` 有真内容（不再"清空"）；
  ③ 把 `0x439130/0x439110/0x439230` 与 slot5 的 `from` 一并补正；
  ④ 作为**一个完整变更集**重新落地，跑 `check`+`audit_layout`+`apply`+`diff`+`export`+`codegen all`+
  `compile`+`compile_regression`+`probe all`+`error_classifier`+`match`，并做 A-B-A 与
  **L1 的 (VA) 集合**比对（不只看条数）。

---

# 12. 下一步（2026-09-18 定案）—— 为什么先修 20 个错误

**结论：下一步不是继续改归属，而是修掉 `pal3/src/Misc/UIProgressBar.cpp` 的 20 个编译错误。**
理由：这些错误**在基线就存在**（`UIProgressBar.cpp` 一直 fail），修它独立于 vtable 之争就有收益（救回一个 s2 单元）；
同时它是**整套 vtable 落地的 gate** —— 一经迁移，这 20 个错误会**原样搬到** `UI3DCtrl.cpp`
（`(code,msg)` 多重集已实测相同，仅多 1 条 `C2660 QueryState`），把 `UI3DCtrl.cpp` 从 ok 打成 fail、
丢掉它 11 条 s4 符号 —— 这正是上一轮被独立复核判 blocker 的机制。

## 12.1 错误分解（实测，20 = 11 + 7 + 2）

| 族 | 数量 | 形态（当前源码行） | 层次 |
|---|----|-------------------|------|
| `C2100 illegal indirection` | **11** | `:239 void *v20; // esi` → `:132 Rotate(v12, *v20)`（局部被推成 `void *` 后解引用/传值） | annotation 成员类型 → 传染局部 |
| `C2664` | **7** | ① `:94 SetAxisAngle(v20, 45.0)` 传**值**、声明是 `gbVec3D*`（2）② `:337 GetRayToScreen(pRay, &Point.x)`：`POINT.x` 是 **`LONG`**，MSVC6 里 `long*` ≠ `int*`（5） | ①调用点实参退化 ②参数类型注解 |
| `C2660` | **2** | `:358 GetOBBox(&actionId)` 传 1 参而声明 "does not take 2" ⇒ 参数数 vs `ret N` | annotation 签名 |

## 12.2 两条可直接开工的线索

1. **`void *` 局部从哪来**：`UIProgressBar.json` 的 `known_members["88"]`(`m_progress`) 的 source 串是
   `"A:PAL3patch_verified(running_code); type_fix:m_p*_int_to_void*"`（但 `type` 现值是 `int`）。
   **全库共 10 处这种批量 `type_fix:m_p*_int_to_void*`**，其中 **6 处现值就是 `void *`**：
   `Actor+496 m_pSelfAtt`、`NPC+60 m_pConditionB`、`PalScript+144/+148 m_pCurrentTask/m_pTaskPtr`、
   **`RoleCameraCtrl+8 m_pVtable`**、**`ScreenEffectMgr+0 m_pVtable`**。
   ⚠️ 后两个把**偏移 0 的 vftable** 标成名为 `m_pVtable` 的 `void*` 成员 —— 与 `__vftable` 约定冲突，须单独核。
   这类批量 type_fix 正是 CLAUDE.md 禁的"批量修改未验证字段"，值得作为**独立审计项**。
2. **`0x56AC70` 属 `UICaption`(96) 还是 `UIButton`(344)**：ctor `0x43A770`（`new(0x158)`×2、stride 0x158×106、
   直调 `0x445aa0`=UIWnd ctor ⇒ 直系派生）。关键判据 = **`0x56AC90`（派生表）的安装者是否 `call 0x43A770`**
   + `0x43A770` 的写入偏移集（尤其 `rep stos` 覆盖 212..340）与两候选的 `known_members` 对照。
   这条不解，`UIButton` 只能空着，会重演 `UIButton.cpp` 消失。

## 12.3 在飞任务（本次会话）

- 内部子 agent `d62338e9`：**N1** —— 三族错误的根因 + 最小修复方案（只读，不改文件）。
- 内部子 agent `d4acdb30`：**N2** —— `0x56AC70`/`0x56AC90` 归属定谳（只读）。

回来后由 captain 合并成**一个完整变更集**再落地。**不许**拆分落地（这正是上一轮的教训）。

## 12.4 重新落地的验收清单（补上上一轮漏掉的两项）

```
① L1 按 (VA) 集合比对 —— 不只看条数        ← 上一轮只比条数，漏掉"成分替换"
② 生成文件存在性 diff（ls pal3/src/**/*.cpp vs 上一版）  ← 上一轮漏掉"UIButton.cpp 消失"
③ compile_regression.py 单独跑（不信 codegen 内置那次：
   回退后它报过幻影回归 15:01:25 指纹 62/202，而 15:01:37 独立 probe 才给出正确的 61）
④ s4 逐行符号 diff（查"静默消失"的符号）
⑤ probe all + error_classifier + audit_layout + check + annotation_diff
⑥ A-B-A：先归档 probe_census.json + s4_baseline.json
```

## 12.5 当前安全状态

工作区干净；`3aff03cf2` 已提交。回退后指标逐项回到 pre-state：
`UIButton.cpp` 已恢复生成、`matched 191/218 | L1 17`、`probe s2 ok=61`、
`compile_regression.py → ✅ No regressions detected (Current S2: 61/202)`、
`--self-test 17/17`、单测 54 OK。

---

# 13. N2 定谳（子 agent `d4acdb30`，只读）：`0x56AC70`/`0x56AC90` 与 UICaption

## 13.1 判定

| 表 | 归属 | sizeof | 置信度 |
|---|------|--------|--------|
| **`0x56AC70`** | **`UIButton`**（基类 `UIWnd`，单继承） | **344** | **A** |
| **`0x56AC90`** | **`UIButtonEXA`**（基类 `UIButton`） | **376** | 结构 **A** / 名字 B+ |
| **`0x56AFB0`** | **`UICaption`** 主表（+ 第二基类表 `0x56AFA4` @+0x44） | 132(PDB) / 二进制下界 96 | **A** |
| `0x56ACD8` | 疑 **`UIDragBar`(272)**，非注解的 `UIScene`(344) | 272 | 未闭合，另开单 |

工具独立判据：`--vtable 0x56AC70` → `slots=8 req=344 声明=UICaption  <<< MISMATCH` + `!! UICaption: IMPOSSIBLE (req 344 > binary_size 96)`。

## 13.2 **根因**：两张表被并成一张 17 槽表

`data/annotations/vtable_ownership_evidence.json` 对 `0x56AC70` 记录的正是
**`slot_count: 17, orig_class: "UIScene"`** —— 它把 `0x56AC70`(8 槽) 与 `0x56AC90`(9 槽)
跨边界并成一张 17 槽表，并挂给 `UIScene`，后又被 `UICaption` 继承了这个地址。
**这就是 §2/§10 反复出现的"表长不可从字节导出"陷阱的实例化**（`gotcha_vtables_not_derivable_from_bytes.md`）。

独立于工具的边界论据：**两张表各含恰好一个 scalar deleting destructor**（`0x43A7F0` / `0x43B4B0`），
MSVC 单继承 vtable 不可能有两个；`0x56AC90` 前一张表 `0x56AC4C` 在两枚 float 常量后于
`0x56AC68/0x56AC6C` 收尾，`0x56AC90` 后 `0x56ACB4 = 0x41400000`(=12.0f，非 `.text` 指针) 收尾。

## 13.3 表长/槽位（字节界定）

```
0x56AC70 (8 槽, 0x56AC70–0x56AC8F)
  +00 0x00445E70(UIWnd s0)  +04 0x0043AD40  +08 0x0043AB20  +0C 0x0043AB00
  +10 0x00445B90(UIWnd s4)  +14 0x0043A7F0(scalar dtor→0x43A810)
  +18 0x00445D10(UIWnd s6)  +1C 0x0043A870(新增虚函数, ret $0x18 = 6 参数)
0x56AC90 (9 槽, 0x56AC90–0x56ACB3)
  +00 0x00445E70  +04 0x0043B660  +08 0x0043B900  +0C 0x0043AB00
  +10 0x00445B90  +14 0x0043B4B0(scalar dtor→0x43B4D0)  +18 0x00445D10
  +1C 0x0043A870  +20 0x0043B570
```

`0x56AC90` **不是** `0x56AC70` 的第二 vptr，而是**派生类**的表：安装点 `0x43B497`(ctor `0x43B3E0` 内)、
`0x43B4D3`(dtor `0x43B4D0` 内)；ctor `0x43B3E0` **确实 `call 0x43A770`**（`43b3e4`，同 this），
dtor 末尾 `call 0x43A810`(UIButton 的 dtor) ⇒ `UIButtonEXA : UIButton`。
多继承的第二 vptr 写在**非零偏移**（如 UICaption 的 `movl $0x56afa4,0x44(%esi)`）。

## 13.4 sizeof 的 A 级证据（`operator new` / `__ehvec_ctor` 元素尺寸）

- `push $0x158; call 0x55353b; …; call 0x43A770` @ **`0x519a50`**、**`0x51d42d`** ⇒ 344。
- `__ehvec_ctor`(0x553627) 元素 `$0x158,$n,ctor 0x43a770,dtor 0x43a810` @ 11 处 ⇒ 344。
- `$0x178,$0x3, ctor 0x43b3e0,dtor 0x43b4d0` @`0x453d71`、`$0x178,$0x34` @`0x456b01` ⇒ 376。
- **独立第三方约束**：`CCBItemWindow` ctor `0x446105` 建 0x26 个 **0x1dc=476** 字节元素，
  元素 ctor `0x4461B0` 在 **+0x60** 构造 class_B、随后写 **+0x1d8** ⇒ `0x60+0x178=0x1d8`
  ⇒ class_B **恰好 376**（`UIScenePanel` 声明 14232，**不可能是它**）。

## 13.5 `0x43A770` 写入 vs 候选（19/19 命中 PDB）

- ctor 实写：`0x48=1.0f, 0x4c=1.0f, 0x60=0`；`lea 0x74; call 0x445ea0`(UITextureArray ctor)；
  `0xc4=0, 0xcc=1(B), 0xd0=1`；`lea 0xd4; mov $0x20,%ecx; rep stos` ⇒ **212..339 = `m_caption[128]`**；
  虚函数 `0x43A870` 另写 `0x44(B),0x64(B),0x68,0x6c,0x70(B),0xc8,0x154(B)` + `lea 0xb8`(3 指针 0xb8/0xbc/0xc0)。
- **vs `UICaption.json`(成员 0/76/80/84/88/92, bs96)**：命中仅 `0/76`（且 `76` 语义冲突：UICaption 是 `m_tex` 指针，
  UIButton 是 `m_ratioh`=1.0f）；`rep stos 212..339` 与 96 上限**直接冲突**（req=344）。
- **vs `UIButton.json`**：**该文件的 offsets 本身是错的** —— = PDB UIButton 布局**删掉 `m_ratioh`(76,4B)
  与 `m_drawrc`(80, tagRECT 16B) 后整体前移 20**（96→76、116→96、212→192、340→320 处处差 20）。
  改用其真正来源 `data/pdb/pdb_export.json` 的 `UIButton`(344)：**19/19 命中** ——
  `68 m_hasDBclk / 72 m_ratiow / 76 m_ratioh / 96 m_state / 100 m_canctrl / 104 m_offsetx / 108 m_offsety /
  112 m_bBigFont / **116 m_texarray**(=lea 0x74) / **184 m_texarrayInfo**(=0xb8/bc/c0) / 196 m_disablepic /
  200 m_disablepicInfo / 204 m_mouseoff / 205 m_mouseon / 208 m_alignmode / **212 m_caption[128]** /
  **340 m_benable_snd**(=0x154) / size 344`。
- 两条独立**语义**旁证：**`0x43AFA0` = `UIButton::SetCaption(char const*)`**（arg==NULL → `rep stos 0x20 dwords @0xd4`；
  否则 `strncpy(this+0xd4, arg, 0x7f)`，call `0x5540f0`）；`0x43AA00` 只碰 `0xc4/0xc8` 且用 `"%s%d.tga"`(0x5967b0) 建纹理。
- class_B 5/5 命中 PDB `UIButtonEXA`(376, base UIButton)：`0x158`(dtor free)=`m_optData`、`0x168=1`=`m_EnableMode`、
  `0x16c/0x170/0x174`(打包色值 0x44/0x80/0xff/0x0a)=`m_color`/`m_enablecolor`/`m_surecolor`。
- **344 的三个"ctor 候选"全部不是 ctor**：`0x43AA00`=UIButton 方法（只碰 +0xc4/+0xc8）、
  `0x43AFA0`=`SetCaption`、`0x445E50`=**UIWnd 方法**。

## 13.6 UICaption 的真表（反向排除，已找到）

- **ctor `0x44A790`**：`call 0x445aa0`(UIWnd) → `movl $0x56a9c0,0x44(%esi)`(PalScriptWaitObj 子对象 vptr)
  → `0x48=0` → **`0x4c=0`(`m_tex`)** → **`0x50=0`(`m_numline`)** → `movl $0x56afb0,(%esi)`
  → **`movl $0x56afa4,0x44(%esi)`** → **`0x54=1`(`m_lineheight`)**；dtor **`0x44A7F0`** 还原两处 vptr 后 `jmp 0x445b40`(`~UIWnd`)。
- 主表 `0x56AFB0` = `[0x445E70, 0x44A870, 0x44A820, 0x43D920, 0x445B90, 0x44A7D0, 0x445D10]`（7 槽）；
  第二基类表 `0x56AFA4` = `[0x44AB40, 0x44AB00, 0x4AF760]`（3 槽）@+0x44 —— **铁证**：
  `0x44AB40` = 调整 thunk **`sub $0x44,%ecx; jmp 0x44a7d0`**。
- 成员级：`0x44A870` 读 `0x4c/0x50/0x58`；`0x44A820` `fadds 0x5c(%ecx)` + `fcomps 0x56afa0`(=2.0f) 累加并换行
  ⇒ 字幕换行计时。与 PDB `UICaption`(132；UIWnd@0 + PalScriptWaitObj@68, m_tex@76…) 一致。
- **根因线索（与 §13.2 同源）**：注解里 UICaption 的 `Destroy 0x0043AB00` / `_sdtor 0x0043A7F0` /
  `CreateChildWidget 0x0043A870` **全是 0x43xxxx（UIButton 系）**，而 UICaption 真的是
  **`0x44AB00 / 0x44A7F0 / 0x44A7D0`** ⇒ 典型的 **`43xxxx ↔ 44xxxx` 混淆**（同一类被写错一位十六进制前缀）。
- `0x00450320` 经 `$0x160,$0x5,ctor 0x450320` 元素尺寸证据属 **`UIHeadDialog`(352)**，不是 UICaption。

## 13.7 名字证据的边界（严格区分）

- 二进制**无游戏类 RTTI**：全库 `.?AV` 仅 6 条（CRT 的 `_Exception/exception/logic_error/length_error/out_of_range/type_info`）。
  无 `UIButton/UICaption/UIScene` 字符串。
- 唯一 UI 源文件串是 `D:\Project\PAL3\UI\UIListBox.cpp`@0x5971b8；344B 的 new 站点 assert 是通用
  `C++ new failed` + `Combat\CBUI.cpp`。
- ⇒ **唯一独立名字源是 `data/pdb/pdb_export.json`（PAL3A PDB）**；`UIScene`/`UIScenePanel` 在 PDB 里**不存在**
  （这两个名字**没有外部来源**）。`asm/pal3/decomp/*.json` 的文件名（`NameSys_GetSys_0043a770` 等）全是注解派生，**不可作证据**。

## 13.8 最小变更方案（未执行）+ 下游风险

1. `UIButton.json`：`vtables[0].addr` `0x0056AD64`→**`0x0056AC70`**（8 槽）；`known_members` 按 §13.5 的 19 项重建
   （关键差别：**不是**现在的 `…/96/164/176/180/184/185/188/192/320`，而是 `…/96/100/101/104/108/112/**116**/
   **184**/196/200/204/205/208/**212(char[128])**/**340**`）；`methods` 把 7 个 244B 类的方法迁给 UIProgressBar，
   补 `0x43A770/0x43A810/0x43A7F0/0x43A870/0x43AB00/0x43AB20/0x43AD40/0x43AA00/0x43AFA0/0x43AFE0`。
2. `UICaption.json`：`vtables` 两条（`0x56AFB0` 7 槽 + `0x56AFA4` base `PalScriptWaitObj` 3 槽）；
   `binary_size` 96→**132**（PDB；二进制硬下界 96）；`known_members` 补 `96/100/104/108/112(tagRECT)/128/129`；
   `methods` 删 7 个 `0x43xxxx`、补 `0x44A790/0x44A7F0/0x44A870/0x44A820/0x44A7D0/0x44AB00/0x44AB40/0x4AF760`。
3. `UIButtonEXA.json`：增 `vtables` = `{0x0056AC90, base: UIButton, 9 槽}`。
4. `UIScenePanel.json`：删 `vtables[0]`（`0x0056AC90`；376B ≠ 14232B，只是 476B 槽结构体的子对象）。
5. 另开单：`0x56ACD8`（实测 272，疑 PDB `UIDragBar`；`UIScene/UIScenePanel` 两名在 PDB 无据）。

**风险**：
- `emit_headers.py:243 class_vtable_slots()` 按 slot 地址取短名决定虚性 ⇒ `UIButton.h` 的 virtual 将由
  `0x43AD40/0x43AB20/0x43AB00/0x43A870` 决定（现状写的是 `0x0043FF70/0x00440560` 等 244B 类的方法）。
- `UIButton.h` 布局：现为 `m_texarray+0x60 / m_caption+0xC0 / m_benable_snd+0x140`，**从 `m_state` 起全部错 20 字节**；
  改后 `+0x74 / +0xD4 / +0x154`（**总 size 仍 344**，只改字段语义）。
- **s4**：现有 2 条 L1 `UIButton::??_G @0x0043F950`（JusticeBookUI.cpp / UITitle_BBTY.cpp）修好后
  会**改名换 TU**（UIButton 的 scalar dtor 变 `0x43A7F0`、`0x43F950` 归 UIProgressBar）⇒ 必须重跑 `match`
  并重设基线，**不能只看 L1 总数（17→17 是假平稳）**。

## 13.9 N2 未能推翻/未闭合

1. 「`0x56AC70 = UIScene(344)`」：仅凭二进制**无法绝对排除**（UIScene 不在 PDB），但它需同时解释
   class_A 的 **19/19** 命中 PDB UIButton **且**其派生类 376B 的 **5/5** 命中 UIButtonEXA ⇒ 判为不可维持。
2. class_B 的**名字**只能到 B+（无 RTTI、无字符串）。
3. `0x56ACD8`/ctor `0x43BCE0` 实测 272（`0x10c+4=0x110`），更像 PDB `UIDragBar` ⇒ 另开单。

## 13.10 工具缺陷（N2 发现，已修）

`--writes <ctor>` 在 `req=None`（非 thiscall 或无 this 访问）时崩溃
`TypeError: '>=' not supported between 'int' and 'NoneType'`（我上一轮把 `==req` 改成 `>=req` 引入）。
**已修**（`req is None` 直接跳过）。

同时暴露一条更本质的问题：`is_thiscall()` 只看 decomp 签名 ⇒ 对**正在被争议的注解**是循环论证，
`0x43A770` 因被错挂成 `NameSys *__cdecl()` 而**静默返回空**，N2 不得不手工 objdump。
**已补纯二进制判据 `thiscall_binary()`**（序言里 `mov %ecx,%reg` 或读 `(%ecx)`，且发生在第一次 `call` 之前、
`%ecx` 未被写过），二者取或。修后 `--writes 0x43a770` 给出 `req=216` 与偏移 `[0,72,76,96,116,196,204,208,212]`
（与 N2 手工抽取一致）。

⚠️ **该修改的副作用需注意**：`--audit` 的汇总从 `SIZE_OK 4 / SIZE_CONFLICT 5` 变为 `SIZE_OK 1 / SIZE_CONFLICT 8`
—— 因为更多 ctor 现在"可测"，`measured_size` 的 `best` 选主（同一张表的多个 ctor 中挑一个）可能挑错。
**结论：`--audit` 的 `SIZE_*` 汇总暂不可用，`--stride/--writes --vtable` 单点模式可用**；
下一步需给 `measured_size` 的 ctor 选择加判据（优先"有 `new` 实参"或"配对 dtor 在相邻函数"的那个）。
