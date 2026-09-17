# ROI 分析：下一步该投哪里（2026-09-15，基线 `ok=55/202 · L1=14`）

## 1. 基线（见 `_cleanup_baseline_20260915_FINAL.md`）

```
census ok=**55/202** · match matched **156/180** · **L1 14** · err 3703 · C2039 1068
失败文件 142 个；错误数分布：1错13 · 2错13 · 3错10 · 4错3 · 5错9 · … · ≥11错 **79**
```

## 2. A2（26 个 ≤2 错文件）的**真实可修性**（逐个诊断后修正了预估）

| 组 | 数量 | 真实成本 |
|---|---|---|
| **C2660 调用参数数不符** | **13** | ⚠️ **每例需语义调查**。实测样例 `C3DSpark:380` 的 `RenderGeomQuad`：库声明 `include/gbengine/gbMesh.h:423` 是 **4 参**，而 decomp 调用只给 **3 参**（缺 `gbGeomQuad*`）⇒ 需**补调用点**（Phase2 编辑）或找该实参来源 |
| C2664 参数类型不符 | 4 | 中（如 `SoundMgr:21` 的 `SetOpenMode(&this->m_szScriptMusic[8], 1)`：库要 `ECPKMode` 1 参 ⇒ **成员类型 + 调用点**双改）|
| C2440 类型转换 | 4 | 中（成员/局部类型）|
| C2227/C2065 成员/基类 | 3 | **低**（见 §3，有统一根因）|
| C2059/C2102/C2100 语法 | 2 | 低-中（`UI3DCtrl` 的 `COERCE_FLOAT(GetTickCount())` 对 rvalue 取地址）|

**⇒ 关键事实：C2660 的 23 个符号【完全不重复】** ⇒ **无共同机械根因，无法批量**。
**⇒ 我先前"每例 15 分钟、2 小时 +13 ok"的估计是偏乐观的**；实际以 C2660 为主体的 A2
更接近"每例 30–60 分钟"，26 个约 **13–26 小时**。

## 3. ★ 真正的批量机会：**`void* vftable` + `vftable->Create`**（20 个文件）

### 3.1 现象与根因（实测）

```cpp
// pal3/src/Misc/UIGameOver.cpp:80,91,96
  void *vftable;                                  // ← 声明为 void*
  vftable = (*(void **)&(this->m_Blood));
  ((void ( *)(UIStatic *, _DWORD, int *, UIGameOver *))vftable->Create)(   // ← 对 void* 用 ->Create
     &this->m_Blood, 0, &v3, this);
```
`pal3/src/Misc/UILoadingFrm.cpp:53,57,62` 同形。

**根因**：`vftable` 被声明/赋值为 `void *`，而 `void *` **没有成员** ⇒
`vftable->Create` 报 **C2227**（"left of '->Create' must point to class/struct/union"）。

**对照能编译的形态**（`pal3/src/Misc/UIStatic.cpp:177,179`）：
```cpp
  int ( **vftable)(gbGfxManager *, CHAR *);                       // ← 已类型化
  vftable = (int ( **)(gbGfxManager *, CHAR *))(*(void **)(gfxMgr));
  *v9 = (UIListBox *)vftable[2](gfxMgr, v11);                     // ← 用下标，不是 ->
```
⇒ **codegen 在"`vftable` 从 `void*` 赋值"时保留了 `void*`，之后又用 `->` 访问** ——
这是**codegen 的等价变换缺失**（CLAUDE.md：codegen 只做等价变换；此处应生成 `((T*)vftable)->Create(...)`，
即**把 `void*` 还原为 `T*`**）。

### 3.2 规模（量化）

```
全库含【`void *vftable` 声明 + `vftable->X` 使用】的文件: **20 个**
⇒ **这 20 个全部编译失败**（无一例外）
其中落在"≤2 错"集合: **3 个**（UIGameOver · UILoadingFrm · UIWnd）
```
**⇒ 修好这一个 codegen 根因 ⇒ `ok` 至少 +3，且可能连带改善其余 17 个文件**（它们错误更多，
但同一根因）。

### 3.3 修复方案（codegen 层，等价变换）

在 codegen 的变换阶段（`pipeline/gen/stages/`）加入规则：

> 当 `vftable`（或其它同样从 `*(void**)` 派生的局部）声明为 `void *`，
> 且其后面出现 `vftable->Member(...)` 形态时，改写成
> `((<Member 的声明类型> *)vftable)->Member(...)` —— 或更简单：
> 把 `void *vftable;` 的声明提升为可调用类型，使 `->` 合法。

**⚠️ 需先确认**：`vftable->Create` 的语义（它调用的是 vtable 里的 `Create` 槽）——
应生成 `vftable[<slot>](...)` 还是 `((T*)vftable)->Create(...)`。**这决定改动是否等价。**
**⇒ 修复前必须取该调用点的二进制证据**（CLAUDE.md：禁止未验证修改）。

### 3.4 ⚠️ 但注意：这不属于"annotation_fix"，而是 `codegen_fix`
`error_classifier` 现在把 `codegen_fix` 记 21 个（旧 33）。
**若本根因修复成功 ⇒ `codegen_fix` 显著下降、`ok` 上升** ⇒ 是**最高确定性**的方向。

## 4. 结论：ROI 排序（据实测修正）

| 序 | 方向 | 潜在 `ok` | 成本 | 确定性 | 判定 |
|---|---|---|---|---|---|
| **1** | **`void* vftable` codegen 根因**（§3）| **+3 起**（20 文件全受影响，可能更多）| **小**（一处等价变换 + 二进制验证）| **高** | ⭐⭐ **首选** |
| 2 | A2 里的**非 C2660** 子集（C2440/C2664/C2227，8 个）| +8 | 中（每个需成员类型诊断）| 中 | 次选 |
| 3 | A2 里的 **C2660**（13 个）| +13 | **高**（每例 30–60 分钟，含 Phase2 编辑）| 中 | 分批推进 |
| 4 | **F2**（补 `CEffShock` 注解）| ❌ **实测 `C2039` 未动**（近失池 **0 个** `__vftable` 文件）| 中 | 低 | **不推荐** |
| 5 | `UICamera.cpp`（7 错）| +1 | 小-中 | 中 | 可并入 2 |

**⇒ 首选 §3**：它是**唯一"单点根因、多文件收益、可先取二进制证据再改"**的方向。
