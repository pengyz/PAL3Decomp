# 落地记录：`UIWnd::GetWidth/GetHeight/GetPosition` → `UIProgressBar`

**日期**：2026-09-17 · 前置：`_cleanup_correction_misattribution_scan_v2.md`（§10 消歧、§11 证据基础）

---

## 1. 改了什么

| 文件 | 改动 |
|---|---|
| `data/annotations/structs/UIWnd.json` | 移除 `0x0043FDC0/D0/E0` 三个方法条目（12 行）|
| `data/annotations/structs/UIProgressBar.json` | 加入这三个方法，带 `_migrated_from` / `_evidence`（18 行）|

**没有改**：任何成员偏移、任何成员类型、`binary_size`。名称保留原名
（`GetWidth`/`GetHeight`/`GetPosition` 与"void、一个 int 参数"的 setter 语义不符，
但改名需要新证据，不在本次范围）。

## 2. 证据（A 级）

1. 三者函数体是 `fildl 0x4(%esp); fstps 0x8c/0x90/0x94(%ecx); ret $0x4`
   —— 向 **+140/+144/+148 写 4 字节 float**，而 `sizeof(UIWnd) = 68`
   ⇒ **写在自身对象之外 72 字节，`UIWnd` 归属必然有误**。
2. 调用点传的是 `UIProgressBar`：
   - `UILoadingFrm::InitFullScreen`（`0x4507F0`）：`4507f6 mov %ecx,%edi`、
     `450825 lea 0x48(%edi),%esi` ⇒ 对象 = `this+72` =
     `UILoadingFrm.m_LoadProgress : UIProgressBar`；
   - `CCBUI_SetupAIWindow`（`0x516A30`）：`0x516c93 mov 0x42c(%esi),%ecx`，
     `CCBUI+1064 = m_pRoleStateGP : UIProgressBar *[4]` ⇒ `+1068=[1]`。
3. 三个函数不属任何 vtable（全二进制无 `0x43FDC0/D0/E0` 的 vtable 项）。

## 3. 验证（同轮 before/after，全部实测）

| 检查点 | 结果 |
|---|---|
| `python3 pipeline/cli.py check` | **0 errors, PASS**（13 个既有警告）|
| `python3 tools/audit_layout.py` | PASSED（37 警告）|
| `apply` → `export` | OK；**改动已传导** |
| `codegen all` | 953 个生成文件重写（`pal3/src/` 是 gitignored，需靠 mtime 判断）|
| `probe` s2 | **61/202 → 61/202（Δ0）** |
| `probe` s1 | 731/751 → 731/751（Δ0） |
| `match` | **L1 17 → 17；matched 191/218 → 191/218；partial 149（Δ0）** |
| 扫描器交叉验证 | `UIWnd::GetWidth/GetHeight/GetPosition` 的 `self_overflow` 行**恰好消失**（11→8 组合，无新增）|

### 3.1 传导后的实际收益（质量，不是计数）
调用点从"原始偏移 cast"变为**按成员名**：

```cpp
// 之前（`this` 被当成 UIWnd）
// 之后：
UIProgressBar::GetHeight(&this->m_LoadProgress, 10);
UIProgressBar::GetPosition(&this->m_LoadProgress, 6);
UIProgressBar::GetWidth(&this->m_LoadProgress, 6);
```
函数体内 Hex-Rays 仍写 `*(float *)&this->m_IsGetit = (float)nWidth;`
（成员声明是 BYTE，故保留 float 指针转换）—— 能编译，不引入新错误。

**诚实结论：本次落地 `ok`/`L1` 均无变化（Δ0）。** 收益是注解正确性与反编译产物可读性
（CLAUDE.md 所述"annotation 质量 → Phase 2 工作量"杠杆），不是本轮的字节收益。

## 4. 顺带证实的重大事实：`sizeof(UIProgressBar) = 308`（不是 244）

**下界**：`UIProgressBar::ctor`（`0x439030`，vtable 锚点 `0x56AC20` 唯一安装处之一）
初始化成员到 **+0x130(304)**，最后一次是 dword ⇒ **≥308**。

**上界**：5 个互不相关函数里连续两次构造 UIProgressBar 的 `lea` 位移
（`_ecx_sources` 数据流，非注解推导）：
```
SaleUI::InitUI      0xfa4 → 0x10d8 → 0x120c     位移 308, 308
LineupUI::LineupUI  0x25ae4 → 0x25c18           位移 308
CCCTData::CCCTData  0x2b774 → 0x2b8a8           位移 308
```
（`JusticeBookUI` 的 368 是**上界不是尺寸** —— 两成员之间可有空隙。）

**上界 = 下界 ⇒ 308 精确成立。**

### 4.1 但它会级联出 27 个重叠 —— 所以本次**未**改 `binary_size`
把 `binary_size` 改成 308 后 `check` 立即报 **27 个 member overlap**：一批类把
UIProgressBar 的下一成员放在 +244（`CG_UI` 8748→8992、`s_RoleState` 608→852、
`UISceneFace` 68→312、`m_RoleState`/`p_RoleState`/`CCBRoleStatePanel*` …）。

⇒ 那批注解是错的（244 是同源传播的错误值，可能来自 PAL3A 的 PDB），
修它要**重导 ~10 个类的后续成员偏移**，每个都需独立证据。
按 CLAUDE.md「禁止批量修改未验证字段」，**本轮不做**，已还原 `binary_size=244`。
这是一个边界清晰、可独立执行的任务。

## 5. 本轮发现的三个门禁缺陷（都影响可信度，建议单独修）

1. **`tools/annotation_diff.py` 假阴性**：我改了 2 个 struct 文件后它仍报
   "变更结构体数量: 0 / 898 个 struct 文件与 HEAD 一致 / verdict: clean"
   —— 而 `git status` 明确显示两个文件 ` M`。该检查点目前**无法发现未提交的注解改动**。
2. **`compile_regression.py` / `probe` 的"回归对账"基线陈旧**：
   基线是 **2026-09-15T16:13**（53/204），当前 61/202，于是把**跨 2 天的既有改善**
   当成本次 diff 报出来（"+8 files / 9 improvements / 1 regression"），
   **无法用于衡量一次具体改动**。本记录因此改用同轮 `probe_census.json` +
   `match` 输出对照。
3. ~~**`probe` 的"回归"提示语义反了**：它列出的条目是 `EquipUI.cpp: 31 ↓ 17`
   这类**错误数下降**，却打出"🚨 检测到回归"并拒绝刷新基线。~~
   **❌ 勘误（2026-09-17 晚）：这条不成立。** 读码确认判定是
   `has_regression = new_failures > 0 or new_errors > 0`，即**由（陈旧的）基线驱动**；
   `📈 错误数量变化` 里的 `↓` 只是附带信息，不是判据。真实缺陷只有一个：
   **基线陈旧**（即上面第 2 条）。详见
   `_cleanup_fix_qualified_name_call.md` §7。

## 6. 复现

```bash
python3 pipeline/cli.py check && python3 tools/audit_layout.py
python3 pipeline/cli.py apply && python3 pipeline/cli.py export
python3 pipeline/cli.py codegen all && python3 pipeline/cli.py probe
python3 pipeline/cli.py match
python3 tools/scan_misattribution.py --limit 0 --out _scan_misattribution_v4.json
```