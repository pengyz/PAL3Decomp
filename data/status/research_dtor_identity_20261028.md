# dtor 身份确认与定位 · 只读取证调研（2026-10-28）

> **性质**：只读取证调研，未改动任何产品/标注/管线文件。仅产出本报告。
> **工具**：IDA PRO MCP（session `278944bc`，`original/PAL3.exe.i64`）为主，objdump/decomp 语料/标注面交叉复核。
> **证据纪律**：每结论带地址/指令字节/xref/伪码摘录；推测显式标「推测」。矛盾如实记录。

---

## 0. 一句话定调

这批「未定义 dtor 形符号」**不是一个家族**，而是**五个异质群体**被 overlay 一锅端注释掉。真正的问题不是"缺 dtor 定义"，而是：

1. **命名不可信**：`_scalar_dtor_*` / `_nearby_*` / `*_deleting_view` 全是**地址后缀占位名**（管线按入口地址造的名字），与"是否 scalar deleting dtor"**无必然关系**（实测 `_scalar_dtor_BE80` 其实是纯析构，真 deleting dtor 叫 `sub_44BE40`）。**判据必须回到字节形，不能看名字。**
2. **归属错置**：共享虚方法 `Destroy__ovl_03` 被当成某单类成员（CCBRoleState）→ 其它类看不见 → C2065「无定义/声明」。它其实是**多 UI 类共享的基类虚方法**。
3. **合成物该由 MSVC6 重生成，不该手写**：真 scalar deleting dtor（`??_G`）/ adjustor thunk / 纯析构 thunk 都是编译器按需 COMDAT 合成，源码只写 `~X()` + `delete`，编译器自动产出；字节匹配靠 match/L1 验证合成物一致。
4. **crt_runtime 是筐**：`_nearby_452570` 这类其实已能用**正确 reason**（`compiler_global_init_stub`/`compiler_scalar_dtor`/`compiler_generated`）分类，不该混进 `crt_runtime`（923 条）。

---

## 1. 结论摘要（每个符号一行）

| # | 符号（管线名） | 地址 | 真实身份 | 证据强度 |
|---|---|---|---|---|
| 1 | `Destroy__ovl_03` | `0x43DE40` | **真实游戏共享虚方法 `Destroy()`/cleanup**（非合成、非 dtor）；`__ovl_03`=命名碰撞消歧后缀 | **强**（objdump `e8` call + 18 code xref + 22 vtable 槽 + 无 vptr/base 的清理体） |
| 2 | `_sdtor_15` | `0x450370` | **scalar deleting dtor**（编译器合成）；经 `UICaption::_UICaption_adjthunk`(0x4506C0) 调 | **强**（`test flags,1 / operator delete / return this`） |
| 3 | `UIFrameWnd__deleting_view` | `0x43D880` | **纯析构 `~UIFrameWnd` thunk**（`mov [ecx],stru_56ACFC; jmp UIWnd::~UIWnd`）；名字 "deleting" **误导**（无 delete） | **强**（disasm 2 指令无 delete + 被 UI3DCtrl deleting-dtor 作析构步 + SystemUI×4 成员析构直调） |
| 4 | `_scalar_dtor_1BD0` (ScriptObj) | `0x411BD0` | **scalar deleting dtor**（`~ScriptObj` + `if flags&1 delete`）；真名应为 `??_GScriptObj@@UAEPAXI@Z` | **强**（decomp: `ScriptObj__ScriptObj; if(nVal1&1) delete`） |
| 5 | `_scalar_dtor_20B0` (EffObjectPool) | `0x4C20B0` | **scalar deleting dtor**（`~EffObjectPool` + `if flags&1 delete`） | **强**（decomp: `DestroyEffBink; if(v2&1) delete`） |
| 6 | `_scalar_dtor_BE80` (UIScenePanel) | `0x44BE80` | **纯析构 `~UIScenePanel`**（667B，析成员 + 尾调 `~UIListBox`，**无 delete**）—— 名 `_scalar_dtor` **倒置误标** | **强**（decomp 尾部无 delete + 单参签名） |
| 7 | `_nearby_452570` (UITitle_BBTY) | `0x452570` | **非 dtor** = 编译器**全局初始化存根**（`flt_DC25B8 = dword_56B1B8*2`）；skip reason=`compiler_global_init_stub` | **强**（disasm `fld/fadd/fstp` + skip_functions reason） |
| 8 | `Role::`scalar deleting destructor'` | `0x41BE30` `??_GRole@@UAEPAXI@Z` | **scalar deleting dtor（MI this-adjust thunk）** → 调 `ScriptObj::_scalar_dtor_1BD0` | **强**（真 MSVC 名 `??_G` + 8B thunk） |
| 9 | `Object_adjthunk_1be20` | `0x41BE20` | **adjustor thunk**（二次 vtable 的 deleting-dtor this-调整跳板）→ `ScriptObj::_scalar_dtor_1BD0` | **强**（8B + 仅 vtable 引用 `0x56a9b0`） |
| 10 | `UI3DCtrl::_scalar_dtor_D860` | `0x43D860` | **scalar deleting dtor**（`UIFrameWnd__deleting_view(this); if flags&1 delete`） | **强**（decomp） |
| 11 | `UICaption::_UICaption_adjthunk` | `0x4506C0` | **adjustor thunk** → `_sdtor_15` | **强**（xref） |
| 12 | `UIScene::sub_44BE40` | `0x44BE40` | **真 scalar deleting dtor**（`_scalar_dtor_BE80(this); if flags&1 delete`）= UIScenePanel deleting dtor | **强**（decomp） |
| 13 | `AStarPathFinder::`scalar deleting destructor'` | `0x401040` `??_GAStarPathFinder@@UAEPAXI@Z` | **scalar deleting dtor** | **强**（真 MSVC 名 `??_G`） |
| 14 | `_scalar_dtor_83B0` (Actor) | `0x4083B0` | **scalar deleting dtor**；skip reason=`compiler_scalar_dtor` | **强**（skip_functions 实证） |
| 15 | `_scalar_dtor_2BD0` (GRPinput) | `0x402BE0` | **scalar deleting dtor** | 中（decomp 名 + adj 形，未全 disasm） |
| 16 | `_scalar_dtor_full/light/rain/weather` (WeatherEffectNode) | `0x404D40/5310/5560/5580` | **scalar deleting dtor 族**（4 个 delete 形） | 中（xref `0x541d10`=operator delete 实证其 delete 行为） |
| 17 | `ScriptObj::scalar_deleting_dtor/_0` | `0x411B80/0x411BB0` | **scalar deleting dtor**；skip reason=`compiler_generated` | 中（skip_functions 实证，未单独 disasm） |

**家族归属**：
- **A 组 · 真实游戏方法（源码必须写出）**：#1 `Destroy__ovl_03`
- **B 组 · 编译器合成 scalar deleting dtor（`??_G`/`_scalar_dtor_*`/`sdtor_*`，源码不写）**：#2 #4 #5 #8 #10 #12 #13 #14 #15 #16 #17
- **C 组 · 编译器合成纯析构 thunk（`??1`/`_deleting_view`，源码写 `~X()`）**：#3 #6
- **D 组 · adjustor thunk（MI this-调整跳板，源码不写）**：#9 #11
- **E 组 · 非 dtor（误入清单）**：#7 `_nearby_452570`

---

## 2. 逐符号取证（证据原文摘录）

### 2.1 `Destroy__ovl_03` @ `0x43DE40` —— 真实共享虚方法，非 dtor

**定义体伪码**（`asm/pal3/decomp/CCBRoleState_Destroy_ovl_03_0043de40.json`）：
```c
int __thiscall Destroy__ovl_03(int nMode)   // __thiscall, nMode = this（单参，无 flags）
{
  gbRefObject *v2 = *(gbRefObject **)(nMode + 68);   // this+0x44 = gbRefObject*
  if ( v2 ) { gbRefObject::Release(v2); *(_DWORD *)(nMode + 68) = 0; }
  SceneObj::HideAll((SceneObj *)nMode);
  return result;
}
```
**关键判据**：体内**不设 vptr、不调基类析构、无 `if flags&1 delete`** ⇒ **不是析构，是 cleanup 虚方法**。`0x20`（32B）。

**调用点字节**（objdump，UIListBox dtor `0x43DD10`）：
```
43dd27: 8b f1                 mov  %ecx,%esi
43dd2d: c7 06 20 ad 56 00     movl $0x56ad20,(%esi)   ; 设 UIListBox vptr
43dd3b: e8 00 01 00 00        call 0x43de40            ; ← Destroy__ovl_03
43dd4a: e8 f1 7d 00 00        call 0x445b40            ; ← UIWnd::~UIWnd（基析构）
```
⇒ UIListBox dtor = `Destroy__ovl_03(this); UIWnd::~UIWnd(this);`。**这是"析构前先 cleanup"的典型**，`Destroy__ovl_03` 在基析构之前跑。

**xref（IDA，18 个 code + 22 个 vtable data 槽）**——**多 UI 类共享**的铁证：
- code：`??1UIListBox`、`?Destroy@CCBUIPanel`、`?Destroy_C910@UIScene`、`?Destroy@UISceneFrm`、`??1SaleUI`、`??1PropUI`、`LineupUI`、`?Destroy@UITitle_ArcSave`、`UIGameFrm_Destroy`、`?Destroy@CCBProtectWindow/CCBResultWindow/CCBFiveNimbusWindow/CCBItemWindow/CCBMagicWindow`、`??1CCBParabolaWindow`、`?Update@CCBControlWindow`……
- data（**vtable 槽**）：`0x56ad20`(UIListBox vtable)、`0x56b100/0x56b1bc/0x56b22c/0x56b274/0x56b364/0x56b5cc/0x56b688/0x56b794/0x56b820/0x56b898/0x56b90c/0x56ba30/0x56c590/0x56d618/0x56e170/0x56f29c/0x56f33c/0x5705d0/0x5705f4/0x570630/0x5706cc`……

**vtable 槽位**（`get_bytes 0x56ad20`，UIListBox vtable）：偏移 `0x0c`（槽 3）= `40 de 43 00` = `0x43DE40` ⇒ **确系虚方法**。

**名字来由**（`data/annotations/functions.json`）：
```json
"0x0043DE40": {"name":"Destroy__ovl_03","signature":"int __thiscall Destroy(int nMode)",
  "source":" | [R93 修 2026-10-23·8 errors] 命名碰撞 => __ovl_03"}
```
⇒ `__ovl_03` 是**命名碰撞消歧后缀**（存在多个 `Destroy`，此为第 03 号实例），**不是 IDA overlay 合成**。

> **【矛盾记录】** overlay 现注释（`phase2/overlay/UI/UIListBox.cpp:82`）称「`Destroy__ovl_03` 无定义/声明（IDA overlay 合成名）」——**与二进制矛盾**：它在 `0x43DE40` 有定义、`functions.json` 有声明、22 个 vtable 在册。C2065 的真实根因是**归属错置**（被当成 `CCBRoleState` 单类成员 → 其它 .cpp 看不见），不是符号不存在。详见 §3。

### 2.2 `_sdtor_15` @ `0x450370` —— scalar deleting dtor（铁证）

**disasm**（IDA）：
```
450370: push esi
450371: mov  esi, ecx                         ; esi = this
450373: call ?DelegateRender@UIWnd@@QAEXXZ    ; ← 析构步（实为 ~UIWnd，名错位，见下）
450378: test [esp+4+a2], 1                    ; test flags & 1
45037d: jz   short loc_450388
45037f: push esi                              ; Block
450380: call ??3@YAXPAX@Z                     ; operator delete(void*)
450385: add  esp, 4
450388: mov  eax, esi                         ; return this
45038a: pop  esi
45038b: retn 4                                ; __thiscall：this=ecx，栈 1 参=flags
```
**判据**：`test flags,1 → operator delete(this) → return this` = **教科书 scalar deleting dtor** `X::`scalar deleting destructor'(unsigned int)`。签名 `void* __thiscall(void* Block, char a2)`，`retn 4` 清 flags。`0x1e`(30B)。

**调用点**（xref）：`?_UICaption_adjthunk@UICaption@@QAEXXZ`(0x4506C0, 8B) + vtable `0x56b0d4`。
⇒ 即用户所指 `UICaption::_UICaption_adjthunk` 内 `sdtor_15(&this[-1].m_linetime + 45, v1)`——**adjustor thunk 调整 this 后调 deleting dtor**。

**附带发现**：`UIWnd::DelegateRender`(0x450390) **名错位**，实为**多 vptr 重置析构**：
```
450392: lea  edx,[ecx+48h]
450399: mov  [ecx],offset stru_56B0D4.ShowClipped
4503a1: mov  [edx],offset stru_56B0D4
4503a7: mov  [eax],offset stru_56A9BC._scalar_dtor_1bb0
4503ad: jmp  _UIFrameWnd        ; 尾调基析构
```
⇒ `_sdtor_15` = **UIWnd 子对象的 scalar deleting dtor**（经 UICaption MI adjthunk 到达）。具体类归属（UIWnd vs UICaption）标**推测**（adjthunk 语境 + vtable `0x56b0d4`）。

### 2.3 `UIFrameWnd__deleting_view` @ `0x43D880` —— 纯析构 thunk，名字 "deleting" 误导

**disasm**（IDA，2 指令）：
```
43d880: mov dword ptr [ecx],offset stru_56ACFC   ; 设 vptr
43d886: jmp ?_UIWnd@UIWnd@@QAEXXZ                ; 尾调 UIWnd::~UIWnd(0x445b40)
```
**判据**：设 vptr + 尾调基析构，**无 `operator delete`、无 flags 参**（签名 `void __thiscall(this)`）⇒ **纯析构 `~UIFrameWnd`**（thunk 形），**不是 deleting dtor**。`0xb`(11B)。

**谁在用**（xref 15，截选）：
- `UI3DCtrl::_scalar_dtor_D860`(0x43d860)——**作 deleting dtor 的析构步**（见 2.10）
- **`??1SystemUI`×4**（0x4a7768/78a2/78ef/78ff）——即用户所指「SystemUI ×4 处 `UIFrameWnd__deleting_view((UIFrameWnd*)&...)`」，**成员子对象析构直调**
- `??1SaleUI`、`??1PropUI`、`LineupUI`×2、`??1MainEquipUI`、`??1EquipUI`、`RenderTarget_InitNPCPanel`、`UIMap::UIMap`

⇒ 语义 = 对 UIFrameWnd 成员/子对象调 `~UIFrameWnd`。名字里的 "deleting" 是**管线误标**（它同时被 deleting dtor 引用过，命名被污染）。

### 2.4 `_scalar_dtor_1BD0` (ScriptObj) @ `0x411BD0` —— scalar deleting dtor

**伪码**：
```c
void __thiscall ScriptObj::_scalar_dtor_1BD0(ScriptObj *this, int nVal1)
{
  ScriptObj__ScriptObj(v3);          // = ~ScriptObj（名被 Hex-Rays 折成构造形）
  if ( (nVal1 & 1) != 0 ) operator delete(this);
}
```
**判据**：`~X + if flags&1 delete` = scalar deleting dtor。`0x1e`(30B)。真名应为 `??_GScriptObj@@UAEPAXI@Z`；现名 `?_scalar_dtor_1BD0@ScriptObj@@QAEXH@Z` 是**管线地址后缀占位**。

**xref**：`Object_adjthunk_1be20`(0x41be23) + `??_GRole@@UAEPAXI@Z`(0x41be33) + vtable `0x56a9bc`。
⇒ 被 **Role 的 deleting dtor（`??_GRole`）经 MI this-调整 thunk** 调用。

### 2.5 `_scalar_dtor_20B0` (EffObjectPool) @ `0x4C20B0` —— scalar deleting dtor

**伪码**：
```c
void __thiscall EffObjectPool::_scalar_dtor_20B0(EffObjectPool *this)
{
  RenderTarget2::DestroyEffBink((RenderTarget2 *)this);   // = ~EffObjectPool 析构步（名错位）
  if ( (v2 & 1) != 0 ) operator delete(this);
}
```
**判据**：`析构步 + if flags&1 delete`。`0x1e`(30B)。xref：`RenderTarget2::DestroyEffWithBink`(0x4c27c0, 8B thunk) + vtable `0x56f5d8`。

### 2.6 `_scalar_dtor_BE80` (UIScenePanel) @ `0x44BE80` —— 纯析构（名 `_scalar_dtor` 倒置误标）

**伪码尾部**（全文 1366 字符，667B）：
```c
void __thiscall UIScenePanel::_scalar_dtor_BE80(UIScenePanel *this)   // 单参，无 flags
{
  UIScene::Destroy_C910(this);
  UIFrameContainer::~UIFrameContainer(...);   // × 多个成员
  UICaption::Destroy2((UICaption *)&this->m_SceneF); ... m_SceneA;
  UIFrameWnd::DestroyCallingCtor(...); ...
  UIListBox::~UIListBox((UIListBox *)this);   // ← 尾调基析构
}
```
**判据**：尾部**无 `if flags&1 delete`**、**签名单参无 flags**、析一串成员 + 尾调基析构 `~UIListBox` ⇒ **纯析构 `~UIScenePanel`**，**不是 scalar deleting dtor**。名字 `_scalar_dtor_BE80` **倒置误标**。

**真 scalar deleting dtor 是 `UIScene::sub_44BE40`**（见 2.12）。

### 2.7 `_nearby_452570` (UITitle_BBTY) @ `0x452570` —— 非 dtor，全局初始化存根

**disasm**（IDA，4 指令）：
```
452570: fld  ds:dword_56B1B8      ; 载全局 float
452576: fadd st, st               ; ×2
452578: fstp flt_DC25B8           ; 存回全局 float
45257e: retn
```
**判据**：浮点运算 + 全局存写，**与析构无关**。skip_functions 条目：
```json
"0x00452570": {"name":"UITitle_BBTY::_nearby_452570","reason":"compiler_global_init_stub"}
```
⇒ **编译器全局初始化存根**（static-init 里 `flt_DC25B8 = dword_56B1B8*2`），**非 dtor**。用户将其列入 dtor 族系**误归**。

**调用点**：`?GetVertexBuf@NavFaceLayer@@QAEPAVgbVec3D@@XZ`(0x452560) = **5B `jmp _nearby_452570` thunk**。
> **【矛盾记录】** `GetVertexBuf` 声明返回 `gbVec3D*`，却尾跳到一个"存全局 float、返回 void"的 init 存根——**语义不一致**。推测 COMDAT/同码折叠或 GetVertexBuf 本身是被折叠的桩。列入 §5 遗留未知。

### 2.8 `Role::`scalar deleting destructor'` @ `0x41BE30` —— 真 MSVC 名 + MI thunk

- 真名 `??_GRole@@UAEPAXI@Z`（`??_G` = **scalar deleting dtor** 的 MSVC 修饰）。
- `0x8`(8B) thunk：`ScriptObj::_scalar_dtor_1BD0((ScriptObj*)&this[-1].m_path_region[7024], a2); return;`
- ⇒ Role 的 deleting dtor（ScriptObj 二次 vtable 视图）= **this-调整跳板 → ScriptObj deleting dtor**（Role 不加自有析构工作）。

### 2.9 `Object_adjthunk_1be20` @ `0x41BE20` —— adjustor thunk

- `0x8`(8B)：`ScriptObj::_scalar_dtor_1BD0((ScriptObj*)&this[-1], v1);`
- xref **仅 vtable `0x56a9b0`**（无 code 直调）⇒ 纯 vtable 内 adjustor thunk，MI deleting-dtor 的 this-调整跳板。

### 2.10 `UI3DCtrl::_scalar_dtor_D860` @ `0x43D860` —— scalar deleting dtor

**伪码**：
```c
void *__thiscall UI3DCtrl::_scalar_dtor_D860(UI3DCtrl *this, UIWnd *Block, char pData)
{
  UIFrameWnd__deleting_view((UIFrameWnd *)this);   // ← 析构步 = ~UIFrameWnd（2.3）
  if ( ((unsigned __int8)Block & 1) != 0 ) operator delete(this);
  return this;
}
```
**判据**：`析构步(UIFrameWnd__deleting_view) + if flags&1 delete` = scalar deleting dtor。`0x1e`(30B)。xref **仅 vtable `0x56acfc`**。
⇒ **2.3 的 `UIFrameWnd__deleting_view` 被此 deleting dtor 作析构步调用**——进一步坐实它 = 纯析构 thunk。

### 2.11 `UICaption::_UICaption_adjthunk` @ `0x4506C0` —— adjustor thunk

- xref 调 `_sdtor_15`(0x450370)。MI this-调整后调 deleting dtor，即用户 `sdtor_15(&this[-1].m_linetime+45, v1)` 场景。

### 2.12 `UIScene::sub_44BE40` @ `0x44BE40` —— 真 scalar deleting dtor（UIScenePanel）

**伪码**：
```c
void __thiscall UIScene::sub_44BE40(UIScene *this, int a2)
{
  UIScenePanel::_scalar_dtor_BE80((UIScenePanel *)this);   // ← 纯析构步（2.6）
  if ( (a2 & 1) != 0 ) operator delete(this);
}
```
**判据**：`~UIScenePanel + if flags&1 delete` = **真 scalar deleting dtor**。`0x1e`(30B)。
⇒ 与 2.6 **命名倒置**：真 deleting dtor 叫 `sub_44BE40`（通用名），纯析构却叫 `_scalar_dtor_BE80`。**证伪"看名字判 dtor 类型"**。

### 2.13–2.17 其余 `??_G`/`_scalar_dtor_*` 族

- `AStarPathFinder::`scalar deleting destructor'`(0x401040, `??_GAStarPathFinder@@UAEPAXI@Z`) —— 真 MSVC 名，scalar deleting dtor。
- `_scalar_dtor_83B0`(Actor, 0x4083B0) —— skip reason=`compiler_scalar_dtor`，源注「同址已注册 Actor.~Actor ⇒ 声明收编形标 declaration_only」。
- `_scalar_dtor_2BD0`(GRPinput, 0x402BE0) —— xref 显示被 `??1GRPinput` 等调，delete 形。
- `_scalar_dtor_full/light/rain/weather`(WeatherEffectNode, 0x404D40/5310/5560/5580) —— xref `0x541d10`(`operator delete`) 证实 delete 行为 ⇒ deleting dtor 族。
- `ScriptObj::scalar_deleting_dtor/_0`(0x411B80/0x411BB0) —— skip reason=`compiler_generated`。

---

## 3. 机制判断（当前管线处置是否合理、缺口在哪）

### 3.1 现状处置（overlay 层）
`phase2/overlay/UI/UIListBox.cpp:80-84`：
```cpp
UIListBox::~UIListBox()
{
  // [overlay-fix 2026-10-27] C2065: Destroy__ovl_03 无定义/声明（IDA overlay 合成名）——待归属定谳
  // Destroy__ovl_03((int)this);
  this->UIWnd::~UIWnd();
}
```
**评估**：
- ✅ **注释掉避免编译崩塌**是务实的（C2065 挡不住就 C2556/2373 双定义爆炸，批0 教训在案）。
- ❌ **归因错误**：注释说「IDA overlay 合成名 / 无定义声明」——**与二进制矛盾**（0x43DE40 有定义、functions.json 有声明、22 vtable 在册）。真实根因是**归属错置**：`Destroy__ovl_03` 被当成 `CCBRoleState` 单类成员（decomp 文件名 `CCBRoleState_Destroy_ovl_03`），其它 .cpp 头文件看不见 ⇒ C2065。它是**多 UI 类共享的基类虚方法**，应归到公共基类（UIWnd/SceneObj 系）。

### 3.2 缺口清单

| 缺口 | 表现 | 根因 | 修法方向 |
|---|---|---|---|
| **归属错置** | `Destroy__ovl_03` C2065 无定义/声明 | 共享虚方法被标成单类成员 | 按 vtable xref 定归属公共基类，声明进基类 methods.json + 基类头可被各 .cpp include |
| **命名不可信** | `_scalar_dtor_BE80` 其实纯析构、`_deleting_view` 其实纯析构、`_nearby` 其实 init stub | 管线按入口地址造占位名，未按字节形判类 | 建立**字节形判据**（见 §4）取代看名字 |
| **合成物被当手写** | `_scalar_dtor_*` 被声明成类成员 → C2039「is not a member of X」 | 把编译器合成 COMDAT 当源码可写方法 | B/D 组不手写：源写 `~X()`+`delete`，MSVC6 自动合成；match/L1 验字节 |
| **crt_runtime 是筐** | `_nearby` 等混进 crt_runtime（923 条） | 历史按"CRT 长相"粗分 | 改用精确 reason：`compiler_scalar_dtor`/`compiler_generated`/`compiler_global_init_stub`（**已存在但未普及**） |
| **skip reason 双注** | 同址既有 skip 条目又有 methods 声明 | skip=体排除 与 声明收编 不同源 | 风险闸：unskip 前查 functions.json/methods 同址（批0 教训） |

### 3.3 与 MSVC6 语义的契合点（处置根本依据）

- **scalar deleting dtor（`??_G`）**：MSVC6 **按需合成 COMDAT**，源码**不应手写**。源码写 `~X()` + `delete p`/虚析构，编译器自动产出 `??_G`。字节匹配时**必须验证合成物与原 exe 一致**（match/L1）。
- **adjustor thunk**：MI/虚继承的 vtable this-调整跳板，**源码不写**，由**正确的类层次声明**（基类顺序/虚函数布局）触发编译器产出。
- **纯析构 thunk**（`~X` = vptr 重置 + 尾调基析构）：源码写 `~X()`，MSVC6 产出。`_empty_dtor_retirement.json` 已定谳「MSVC6 对多态类 ctor/dtor 自动生成 vtable 存储，源码不可见也无法手写，重编译形态取决于类上下文（基类/虚函数声明）正确性 ⇒ 析构字节残差走『类上下文正确性』路线，不设专项 codegen 修复」——**与本调研结论一致**。
- **真游戏方法**（`Destroy__ovl_03`）：**必须源码写出**（声明 + 体），编译器不会合成。

---

## 4. 完备性 spec（判定流程 + 处置矩阵）

### 4.1 判定流程：输入未定义 dtor 形符号 S → 输出身份 + 处置

```
输入：符号 S（带入口地址 A）
  │
  ├─ STEP 1  disasm S 体（IDA 优先，objdump 兜底）
  │    │
  │    ├─ 体含 `test flags,1 → operator delete(this) → return this`
  │    │     ⇒ 【B 组】scalar deleting dtor（??_G）
  │    ├─ 体含 `mov [ecx],vtable; [jmp|call] base_dtor`（vptr 重置+基析构，无 delete）
  │    │     ⇒ 【C 组】纯析构 thunk（??1）
  │    ├─ 体含 `sub this,N; jmp|call target_dtor`（this-调整+转发）
  │    │     ⇒ 【D 组】adjustor thunk
  │    ├─ 体含游戏逻辑（成员访问/API 调用，无 vptr 重置、无 delete）
  │    │     ⇒ 【A 组】真实游戏方法（Destroy/cleanup 等）
  │    └─ 体是浮点/全局存写/字符串等非析构
  │          ⇒ 【E 组】非 dtor（reclassify：compiler_global_init_stub / 游戏 util）
  │
  ├─ STEP 2  xref 交叉（code 调用者 + vtable data 槽）
  │    ├─ 多类 code 调用 + 多 vtable 槽 ⇒ 共享基类虚方法（A）或共享析构（C）
  │    ├─ 仅 vtable 槽 + adjthunk 调用 ⇒ B/D（合成物）
  │    └─ 单 code 调用 + 单 vtable 槽 ⇒ 视体定 A/B/C
  │
  ├─ STEP 3  vtable 槽定位（get_bytes vtable，找 A 的槽号）⇒ 辅助定归属类
  │
  ├─ STEP 4  gbengine.def 核查：若导出 ⇒ gbengine 导入（链接期供给）；
  │          （本批 12+ 全非导出 ⇒ 游戏本体代码；仅 Destroy__ovl_03 调的
  │           gbRefObject::Release 是 gbengine 导入，但 dtor 本身是游戏代码）
  │
  ├─ STEP 5  skip_functions.json reason 核查：
  │    ├─ compiler_scalar_dtor / compiler_generated / compiler_global_init_stub ⇒ 精确（可用）
  │    └─ crt_runtime ⇒ 可疑筐，需重审（923 条，参考 crt_skip_census_20261028.md）
  │
  └─ STEP 6  名字校验：??_G/??_E 前缀=真 MSVC 删除析构；
             _<语义>_<ADDR>=管线占位名（不可信，回 STEP 1 按字节判）
```

### 4.2 处置矩阵

| 组 | 身份 | 判据（字节形） | 源码处置 | 标注面 | skip_functions reason | 验证 |
|---|---|---|---|---|---|---|
| **A** | 真实游戏方法（Destroy/cleanup 虚方法） | 游戏逻辑体，无 vptr 重置/无 delete | **必须写**：声明 + 体 | 归属**公共基类** methods.json（按 vtable xref 定） | 不 skip | 编译 + match/L1 |
| **B** | scalar deleting dtor（`??_G`） | `if flags&1 delete` | **不写**：源写 `~X()`+`delete`，MSVC6 COMDAT 合成 | **不声明为成员**（防 C2039） | `compiler_scalar_dtor` | match/L1 验合成物字节 |
| **C** | 纯析构 thunk（`??1`） | `mov [ecx],vtable; jmp/call base_dtor` | **写 `~X()`**，编译器产出 thunk | 类声明 + 虚函数布局正确 | 需要体时不 skip | match/L1 |
| **D** | adjustor thunk | `sub this,N; jmp/call target` | **不写**：正确 MI 声明触发 | 基类顺序/虚布局正确 | `compiler_generated` | match/L1 |
| **E** | 非 dtor（init stub/util） | 浮点/全局存写等 | 不写（链接/CRT 供给）或游戏 util 归位 | — | `compiler_global_init_stub` / 摘 crt_runtime 伪装 | — |

### 4.3 可扩展性（unknown_libname / 嵌套类）

- **unknown_libname_***：同走 STEP 1（字节形）判 A–E，不因名废义；crt_skip_census 已列「unknown_libname_（另行审计）」。
- **嵌套类/匿名 union dtor**：STEP 2 vtable 槽 + STEP 3 槽定位定归属；嵌套类合成 dtor 归 B/C（编译器合成），不手写。
- **COMDAT 折叠**：同码函数（如 `GetVertexBuf`↔`_nearby`）可能折叠到同址——STEP 1 若见语义不一致，标折叠嫌疑，回退 objdump 全量核对（见 §5）。

---

## 5. 遗留未知（显式列出）

1. **`Destroy__ovl_03` 的确切归属类**：已证是多 UI 类共享虚方法（22 vtable 槽），但**具体是 UIWnd::Destroy 还是 SceneObj::Destroy 未逐槽定谳**。需遍历 `0x56ad20` 等 vtable 的槽号语义（哪个槽=Destroy）+ 基类链注解。**（推测：UIWnd/SceneObj 系公共基类的 Destroy 虚方法）**
2. **`_sdtor_15` 的精确类归属**（UIWnd vs UICaption）：经 UICaption adjthunk 到达、调 `~UIWnd`（`DelegateRender`），但 vtable `0x56b0d4` 归属未逐槽核。**（推测：UIWnd 子对象 deleting dtor）**
3. **`GetVertexBuf`(0x452560) ↔ `_nearby_452570` 语义矛盾**：`GetVertexBuf` 返回 `gbVec3D*` 却 5B 尾跳到"存全局 float、返回 void"的 init 存根。疑似 COMDAT/同码折叠或 GetVertexBuf 本身是被折叠桩。**未定谳**。
4. **vtable 槽语义表**：0x56ad20 等 vtable 里 `0x41400000`（=12.0f 位型）等非函数值、槽 0-2 的确切含义（是否 scalar/vector deleting dtor、offset-to-top）**未逐槽解析**——影响 A/C 组的"是否 dtor 槽"精确认定。
5. **`_scalar_dtor_full/light/rain/weather`、`_scalar_dtor_2BD0`、`ScriptObj::scalar_deleting_dtor/_0`**：仅凭 skip reason + delete-xref 判 B 组，**未逐个 disasm 确认 delete 形**（标"中"证据强度）。
6. **gbengine 导入边界**：`Destroy__ovl_03` 调的 `gbRefObject::Release` 是 gbengine 导入；**其虚表/生命周期是否跨 DLL 边界**（gbengine 侧基类）未深挖。
7. **命名碰撞全貌**：`Destroy__ovl_03` 的 `__ovl_03` 暗示存在 `__ovl_00/01/02/04...`（多个 Destroy）；**这批兄弟符号的地址/身份未清点**，完备性 spec 的 STEP 2 需覆盖。
8. **字节匹配验证**：本调研为只读取证，**未跑 match/L1** 验证"源码写 `~X()`+`delete` → MSVC6 合成物与原 exe 一致"——这是处置矩阵 B/C/D 组落地前的**必验前置**（三限定见 CLAUDE.md「字节全同≠全字节相同」）。

---

## 附：证据工具与可复现性

- **IDA MCP**：session `278944bc`（`original/PAL3.exe.i64`），用 `xrefs_to`/`disasm`/`get_bytes`/`lookup_funcs`。
- **objdump**：`original/PAL3.exe`，`objdump -d --start-address=... ` 核 call 目标。
- **decomp 语料**：`asm/pal3/decomp/*.json`（3695），按符号名 grep 定位调用点。
- **标注面**：`data/annotations/{functions,skip_functions}.json`。
- **overlay 现状**：`phase2/overlay/UI/UIListBox.cpp` 等。
- **既有裁决**：`data/status/crt_skip_census_20261028.md`（crt_runtime 是筐）、`_empty_dtor_retirement.json`（析构字节残差走类上下文正确性路线）、`_cleanup_correction_scalar_dtor_orphan.md`（_scalar_dtor 孤立体 codegen 缺陷）。
