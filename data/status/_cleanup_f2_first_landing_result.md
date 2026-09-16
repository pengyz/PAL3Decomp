# F2 首次落地：**技术成功、但触发真实退化**（captain，2026-09-15）

> 这是本会话**第一次**让 F2 注解真正影响到生成产物。结论：**机制通了，但产生了 `L1` 退化**
> ⇒ 按项目纪律（`L1` 回退 ⇒ 该步判失败）**已回退**。本文档记录全部证据与归因。

## 1. 做到了什么（技术路径完整走通）

```
① 从二进制取证 CEffShock 的表：0x56FADC（15 槽）
   证据（A 级）：ctor 0x4D3280 实写该表；槽 7 = ??0CEffShock(0x4D3910)；
   同族参照 CEffSParticle 的 0x56FB34 亦 15 槽、槽 7 = 本类 ctor（结构完全对应）
② 写注解：structs/CEffShock.json 加 vtables[0] = {addr:0x56FADC, base:'CEffect', slots:[15]}
③ 发现 codegen 的**真实条件**（emit_headers.py:1913）：
   只有「**地址出现在表的槽地址里**」的 methods 才会被判为虚拟方法、按 slot 序发射
   ⇒ 必须把**表的 15 个槽函数写进 methods**
④ 补 12 条 methods（槽 0/1/2/3/5/6/8/9/10/12/13/14）
⑤ 重跑 export（**必须**：codegen 读导出的 ida_structs.json，注解直改不生效）
   ⇒ methods 18 条、vtables 1 条、class_vtable_slots 返回 **15 个**（含 NullCallback×2、Update×3）
⑥ codegen ⇒ **CEffShock.h 的 virtual 计数 0 → 7** ✅
```

**⇒ 首次证明：补 `vtables` + `methods` ⇒ codegen 真的会发 `virtual`。**

## 2. ⚠️ 但触发了真实退化（棘轮正确抓住）

| 指标 | 改前 | 改后 | Δ |
|---|---|---|---|
| `ok` | 56 | 56 | 0 |
| `err` | 3703 | 3703 | 0 |
| `C2039` | 1068 | 1068 | **0** ← 目标指标**没动** |
| `__vftable` 族 | 718 | 718 | 0 |
| `symbols` | 189 | **133** | **−56** |
| `matched` | 150 | 118 | −32 |
| **`L1`** | **14** | **6** | **−8** |

```
[L1 ratchet] previous 14 -> current 6
[L1 ratchet] REGRESSION: byte-perfect functions lost — investigate before committing
```
**⇒ 棘轮按设计工作**：`s4_baseline.json` 已被正确还原（现为 `L1=14 matched=164 symbols=189`）。

## 3. 退化精确定位：**三个文件跌出比对池**

```
改前 L1=14 的分布: JusticeBookUI 3 · UITitle_BBTY 3 · UIStatic 2 · CCBControl 1 ·
                  AStarPathFinder 1 · TxtFile 1 · UISceneFace 1 · ObjectCamera 1 · CameraSystem 1
改后: **JusticeBookUI / UIStatic / UITitle_BBTY 从 match 日志中完全消失**
⇒ 丢失 3+3+2 = **8 个 L1**（正好 14→6），其 symbols 也一并消失（189→133）
```
**这三个文件的 8 个 L1 函数全部是 `??_G`/`_sdtor` 类**：
```
UIWnd::_sdtor_14(void*,char) · JusticeBookUI::_scalar_dtor · UIButton::_scalar_dtor
UISceneFace::ResetAllSlots / ObjectCamera::Destroy 等仍在
```

## 4. 归因假设（**未验证**，但指向精确）

**假设**：`build_mangled_map` 的 `_load_dtor_candidates()` 会**为任何有 ctor / `_scalar_dtor` 的类
推导出 `??1<Cls>@@{Q,U}AE@XZ` 键**。我给 `CEffShock` 加了 12 条 methods（其中 `CEffShock` 是 ctor 名）
⇒ **`CEffShock` 成为新的 dtor 候选** ⇒ 生成了新的 `??1CEffShock@@...` 键。
而 `??_G`/`_sdtor` 那些 L1 函数的匹配**依赖 `mangled_map` 的键格局**；
新键若与既有键**同名冲突**，`setdefault` 的先到先得会**改变条目绑定** ⇒ 那些函数不再被匹配。

**支持证据**：`mangled_map` 键数 **9700**（改前基线记录为 9591）⇒ **键确实增加了 109 个**。
**反面证据（需排除）**：`ok`/`err`/`C2039` 全未变 ⇒ 不是"编译退化"，而是**匹配层变化**；
`decomp` 计数 **3598 未变** ⇒ 不是语料变化。

⇒ **结论：退化发生在 `mangled_map` 层（匹配），不是因为生成头变差。**
**⇒ 这本身就是一条重要知识**：`mangled_map` 的键格局是**全局共享**的，
**给一个类加 methods 会影响其他类的 `??_G` 匹配** —— 这是**非局部耦合**。

## 5. 已执行的动作（按纪律）

1. **回退注解**：`data/annotations/structs/CEffShock.json` 已恢复为 git 干净版（`vtables=None`、`methods=6`）；
   带改动的版本保全在 `data/status/_cleanup_f2_ceffshock_attempt.json`（供后续复用）。
2. **基线未被污染**：棘轮已还原 `s4_baseline.json`。
3. `probe` 的 census 未刷新（`probe_exit=1`，退化检测生效）⇒ `match` 用的是**旧 census 的 56 个 passing**
   ⇒ 这也解释了为什么日志里仍列出那些已 fail 的文件。

## 6. ⇒ 下一步（据本轮证据）

**先修"非局部耦合"，再重做 F2 落地**。具体：

| 序 | 动作 | 依据 |
|---|---|---|
| **1** | **查清 `mangled_map` 的键冲突**：为什么给 `CEffShock` 加 methods 会让 `UIWnd::_sdtor_14` 等**不再被匹配** | §4 的 109 个新键 |
| **2** | 修 `build_mangled_map` 的**冲突处理**（现在用 `setdefault` 先到先得；应改为**按类族优先**或**检测冲突并告警**）| 同上 |
| **3** | 修好后**重做**本次落地（注解已保全，可直接复用）| §5.1 |
| **4** | 若冲突无法避免 ⇒ 研究"**按类分批补 methods**"的顺序（先补不冲突的）| — |

**⇒ 本轮最大价值**：**发现了 `mangled_map` 的非局部耦合**——这是此前 40+ 轮都没暴露的，
而**只有真正落地才会暴露**（印证了"必须落地"的判断）。
