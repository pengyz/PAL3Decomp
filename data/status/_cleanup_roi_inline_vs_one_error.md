# ROI 测量：`_inline_*` 类型发射 vs 1 错文件（本轮未改代码，有意）

**日期**：2026-09-17 · 前置：`_cleanup_fix_globals_const.md`（门禁已刷新为绿）

---

## 1. 结论：被批准的 `_inline_*` 任务 **Δok = 0**

先测量再实现（避免把一次落地机会花在 Δ0 上）：

| 项 | 实测 |
|---|---|
| 被引用的 `_inline_*` 类型 | **5 个**（`_inline_tagCam_yaw`、`_inline_MUIDialog_m_btRc`、`_inline_PalScript_m_RoleSlotArray`、`_inline_RoleAtt_Remark`、`_inline_RoleAtt_Remark::$101B5358F90B67F92EE483560EB2675D`）|
| 总引用 | **25 处 / 7 个文件** |
| 用法形态 | 24 处**仅指针**（前向声明即可）；**2 处 by-value**（`_inline_tagCam_yaw v45;`）**且有成员访问**（`v45.p->m_EffClass[0]`）⇒ 需**完整定义** |
| 全语料 `_inline_` 相关错误 | **10 个** |
| 分布 | `PAL_GDB.cpp` 7、`CCCTData.cpp` 1、`LineupUI.cpp` 1、`PalScript.cpp` 1 |
| 这 4 个文件的错误总数 | **52 / 48 / 53 / 102** |
| ⇒ `ok` 影响 | **0**（没有一个接近 pass）|

**它的真实价值**是消除一个**已文档化的高严重度家族**（`_cleanup_finding_dangling_nested_type.md`：
`_inline_*` 类型存在于 `ida_structs.json` 但无任何生成头文件声明它），不是 `ok` 增量。
**建议**：等它与其他修复凑成一批文件时再做（或作为 codegen 结构性补全单独排期）。

`_inline_*` 的结构（供实现时用）：**内联 union**（成员同在偏移 0），
如 `_inline_tagCam_yaw{ float f@0; CEffMgr *p@0 }` size=4、
`_inline_MUIDialog_m_btRc{ tagRECT rc@0; void *pCallback@0 }` size=16。

## 2. 真正的 `ok` 机会：**16 个文件只有 1 个错误**

```
CCBAI.cpp          C2440  bool(__cdecl*)(int,int) -> int(__thiscall CCBSystem::*)
CCBLineupWindow.cpp C2440 '=' : CCBItemWindow * -> char
Combat.cpp         C2440  type cast: Combat -> int
UIMap.cpp          C2440 '=' : void * -> unsigned long          ← 见 §3.1
CCBProtectWindow.cpp C2664 gbTexture::UpdateTexture(gbImage2D*) 参数不符
BINK.cpp           C2664 void(unsigned long,int) 参数1不符
DealData.cpp       C2664 lstrcpyA: unsigned char * -> char *
UIButton.cpp       C2664 SetLibFolder: unsigned char * -> char *   ← 与上一行同形
C3DSpark.cpp       C2660 RenderGeomQuad 不接受 3 个参数
Comp_DonateUI.cpp  C2660 UpdateAnim 不接受 1 个参数
SwordUI.cpp        C2660 RecalcAggregatedStats 不接受 2 个参数
TextureLib.cpp     C2660 InsertBlocks 不接受 4 个参数
Scene.cpp          C2660 Copy 不接受 0 个参数
UIGameOver.cpp     C2227 left of '->Create' must point to class/struct/union
UILoadingFrm.cpp   C2227 left of '->Create' must point to class/struct/union
UIDialog.cpp       C2059 syntax error : ')'                     ← 见 §3.2
```
按错误码：C2660×5、C2440×4、C2664×4、C2227×2、C2059×1。
**上限 +16 ok**，但**不是同质族**，每个都要各自取证。

## 3. 已取到的具体证据（下一轮直接可用）

### 3.1 `UIMap.cpp:119`（C2440 void* → unsigned long）
```cpp
*(_DWORD *)pszFolder = (*(void **)&(this[2]));   // RHS 是 void*，赋给 DWORD 左值
```
MSVC6 严格：`void*` → `unsigned long` 不允许隐式转换。**codegen 层**问题
（AST 层可按左值类型插入显式转换），但需评估插入转换的全局影响面。

### 3.2 `UIDialog.cpp:57`（C2059 syntax error : ')'）
```cpp
54|  (((CCBItemWindow *)this))->CCBItemWindow::Create(0, &pRect, parent) /* [ROWTABLE] */;
57|  (((RoleCameraCtrl *)&this[1]))->RoleCameraCtrl::SetTargetDistance(2);
```
形态本身合法 ⇒ 需 `cl /E` 或最小复现定位真正报错点（可能是 `RoleCameraCtrl` 未声明
或 `SetTargetDistance` 声明异常）。

### 3.3 C2660 族：**证据齐但不一致，构成取证障碍**
| 文件 | 调用点 | callee 注解 | 二进制 `ret N` | decomp 签名 |
|---|---|---|---|---|
| `Comp_DonateUI.cpp:42` | `(((NPC *)a1))->UpdateAnim(v4);` | `void __thiscall(NPC *this)`（**0 参**）| `ret 4` ⇒ **1 栈参** | `void __thiscall(NPC *this)`（也 0 参，**IDA 本身错**）|
| `SwordUI.cpp:218` | `RoleSystem::RecalcAggregatedStats(&g_RoleSlotBuf, 0);` | 无 signature | `ret 4` ⇒ 1 | `int __thiscall(RoleSystem *this, char pData)` ✓ |
| `TextureLib.cpp:173` | `Array::InsertBlocks(&v41, v41.m_pData, 1u, &p_DWORD);` | 无 signature | `ret 0xC` ⇒ 3 | `char *__thiscall(Array *this, char *pszBuf, unsigned int dwVal, int *p_DWORD)` ✓ |
| `Scene.cpp:143` | `(((Array *)i))->Array::Copy();` | 无 signature | `ret`（无 imm）| `void *__cdecl(void *dst)` |
| `C3DSpark.cpp:380` | `...->gbDynVertBuf::RenderGeomQuad(a,b,c)` | **注解中查无此方法** | — | — |

**为什么我停在这里（不猜）**：
- `NPC::UpdateAnim`：注解 0 参、二进制 `ret 4`（1 参）、而**全部 15 个调用点都只传一个
  `(NPC *)` 实参**（`NPC::UpdateAnim((NPC *)(v3 + 156304));` 这种静态形式）。
  三者不能同时成立 ⇒ 要么注解的 `__thiscall` 约定错（实际可能是 `__cdecl(1)`），
  要么调用点的静态形式少了一个实参。**这需要先定原型约定，不能猜**
  （CLAUDE.md：禁止猜测性修改 / 禁止试错式修改）。
- `SwordUI.cpp` / `TextureLib.cpp` 两个是**静态形式 `X::Y(obj, args)` 未被改写**，
  而改写门禁要求 `_ret_param_slots`（读注解 signature）**且** `_occupies_vtable_slot`。
  它们的注解缺 signature ⇒ 门禁拿不到参数数。**可行的机制修复**：
  `_ret_param_slots` 在注解缺 signature 时**回落到 decomp 导出的签名**
  （实测这 2 个的 decomp 签名与二进制 `ret N` 一致）。全语料缺 signature 的方法仅
  **19 个（1%）**，其中 **13 个**在 decomp 里有签名 ⇒ 影响面小、可控。
  ⚠️ 但 `NPC::UpdateAnim` 的 decomp 签名是**错的**（0 参），所以回落只能当"额外线索"，
  最终仍要与 `ret N` 交叉验证。
- `C3DSpark.cpp`：`gbDynVertBuf::RenderGeomQuad` **不在任何类的注解里** ⇒ 是
  **lib 头文件的声明与调用点不符**，属另一条线。

## 4. 下一轮建议（按 ROI）
1. **`UIDialog.cpp` C2059** —— 先做最小复现定位（可能一处修复就 +1 ok，且风险最低）。
2. **`UIMap.cpp` C2440** 与 **`DealData/UIButton` 的 `unsigned char*→char*`** ——
   三处同属"赋值/传参的指针类型不匹配"，评估一个 AST 层"按目标类型插入显式转换"
   的统一修法（一次可能 +3 ok，但**必须先评估影响面**）。
3. **静态形式改写的 signature 回落**（§3.3）—— 机制级，可 +2 ok，且顺带修
   `ret N` 信息缺失。
4. `C3DSpark` / `CCBProtectWindow` / `BINK` / `CCBAI` / `Combat` / `CCBLineupWindow` ——
   逐个取证。
5. `_inline_*` 类型发射（§1）—— Δok=0，按结构性补全排期。

## 5. 复现
```bash
python3 - <<'EOF'   # 1 错文件清单
import json;pc=json.load(open('data/status/probe_census.json',encoding='utf-8'))
r=(pc['s2']['results']);it=r.items() if isinstance(r,dict) else [(x['unit'],x) for x in r]
for k,v in sorted(it):
    if len(v.get('errors') or [])==1: print(k, v['errors'][0]['code'], v['errors'][0]['msg'][:70])
EOF
grep -rn "_inline_" pal3/src --include=*.cpp --include=*.h | wc -l   # 25
```