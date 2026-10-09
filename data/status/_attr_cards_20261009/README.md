# 归因卡 · 族 A/B/C + MISATTRIBUTED（只读归因，未动任何 annotation/生成态/管线）

**日期**：2026-10-09 · **基线**：`probe_census.json` S2 100/210 · 总错误 1735（2026-10-08T21:52:01）
**规格**：8 节归因卡（经协作方确认）· **本轮只读**，所有修法均为"最小修法建议"，未执行
**复核**：待子 agent 对抗复核（复核点 R-a..R-d 见各卡 ⑧）

---

## 全局结论（先看这张）

| # | 根因 | 病灶层 | 命中单元 | ⑥ E2 引入 vs 解封 |
|---|---|---|---|---|
| **N1** | `UIPushButton::FormatText/LoadTexture` 签名错（类型+arity 双错）| **annotation** | 1（+2 待立案）| 解封/显形 |
| **N2** | `E.T` 直读（T=类名）触发 MSVC6 函数式铸形 | **codegen**（`stage4_substitution.py:484` 覆盖不全）| 3 | 解封/显形 |
| **N3** | `enum` 形参 + `int` 字面量，缺 enum cast | **codegen** | 1 | 解封/显形 |
| **N4** | `SetAxisAngle` 重载集不完整（include 链同名声明不一致）| **头声明层** | 1 | 解封/显形 |
| **N5** | 指针→整型赋值补 cast 漏形态 | **codegen**（`stage4_substitution.py:768`）| 3 | 解封/显形 |
| **N6** | callee 命名错位 / 伪语义命名 | **annotation·命名层** | 2 站点 | 解封/显形 |

**共同机理（N2/N3/N5/N6）**：Hex-Rays 的固有形态缺陷 + IDB 类型缺口，被 codegen 解形后**显形**为编译错误。
**⇒ 全部 9 个新失败 + 9 处 MISATTRIBUTED 均非 E2 引入**（详见各卡 ⑥；A-B-A 待补跑收口）。

---

# N1 · `NewTexture` C2664（族 C）

## ① 根因标识
`C2664 'NewTexture' : cannot convert parameter 1 from 'int' to 'const …'` · 族 C · 命中 **1 确证 + 2 待立案** 单元

## ② 病灶层三问
| 问 | 答 |
|---|---|
| **哪一层** | **annotation**（主因）：`data/annotations/structs/UIPushButton.json` 的 `0x00440960 FormatText` / `0x00440AE0 LoadTexture` 形参类型与 arity 双错。**codegen 无病**（只是解开 Hex-Rays 的函数指针 cast 形）。**Hex-Rays 无病**（虚调用发 cast 形是固有形态）。 |
| **消费者读哪个声明** | `NewTexture` = `gbGfxManager.json:142` `gbTexture *__thiscall(const char *name)`；同函数另两个 callee 声明 `LPCSTR`（`_Texture_Info.h:26` / `TextureLibDataBase.h:23`）。 |
| **报错还缺什么** | C2664 截断不给全形参类型、不能推重载 ⇒ 已用二进制补齐。 |

## ③ 二进制证据链（A 级）
| # | 证据 | 结论 |
|---|---|---|
| E1 | `0x440a18: c2 08 00` (`ret 0x8`) | **2 个栈参数**，注解说 1 个 ⇒ **arity 错** |
| E2 | `0x4409a6: mov edi,[esp+0x20]` → 三处 `push edi` / `push eax` 喂 `0x53fcf0` / `0x53fdd0` / `call [edx+0x8]` | 同一 arg1 喂三个 callee |
| E3 | `0x440997: mov al,BYTE PTR [esp+0x1c]` | arg2 按 BYTE 读 ⇒ bool/char |
| E4 | `_CalculateUV`：`push ebp; call [0x56a028]`→`jle`；`push eax;push ebp; call 0x55ef90` | arg1 喂 strlen/strcmp 形 |
| **E5** | `0x53fd5f: push ebp; push 0x608cbc`，`0x608cbc = "Not Found %s In UI_o…"` | **arg1 作 `sprintf("%s",…)` 的 `%s` ⇒ 字符串指针，破环成立** |
| E6 | IF 分支传 `_CalculateUV` 返回的 `CHAR*`、ELSE 传 arg1，均入虚槽 2 | **`NewTexture(const char*)` 声明正确** |
| E7 | 同文件 `UIPushButton::CreateWithTextures(…, const char *pszName, …)` 里 `sprintf(Buffer,"%s%d.tga",pszName,v7)` → `NewTexture(Buffer)`，`Buffer` 是真 `char Buffer[260]` | **独立佐证 E6** |

## ④ 精确机理
> IDB 把 `FormatText`/`LoadTexture` 的 arg1 标成 `int` ⇒ Hex-Rays 对**非虚** callee 自补 `(LPCSTR)`（decomp L18/L20），对**虚** callee 发函数指针 cast 形 `(*(fn)(T*, **int**))(mgr, nVal1)`（decomp L24-26，**实参类型被写成 `int` 塞进 cast，永不报缺转换**）⇒ codegen 解形（`stage4_substitution.py:653`）⇒ 错配**显形为 C2664**。

## ⑤ 最小修法（未执行）
`UIPushButton.json` 两个方法签名改为 **2 参、arg1=`LPCSTR`**。**不改 codegen**。验收：`check_annotations.py` + `audit_type_layout.py --only UIPushButton`。

## ⑥ E2 引入 vs 解封 → **解封/显形**
1. 三单元不在 E2 改的 4 个类内；2. 机理链无一环经过 `base_class`/`base_size`/vptr；3. 成因是形态差恒定存在。
⚠️ **置信度 高但非决定性** —— A-B-A 未跑（见 ⑧ R-d）。

## ⑦ 爆炸半径 / 风险
| 单元 | arity | arg 去向 | 独立破环 | 判定 |
|---|---|---|---|---|
| `UIPushButton::FormatText/LoadTexture` | ❌ 1 vs `ret 8` | 三 callee 交叉 | ✅ E5 | **N1 主因** |
| `UI3DCtrl::CreateWithTexture` | ✅ `ret 0x14`=5 参 | arg3→`NewTexture` | ⚠️ 仅旁证（函数名 + 与 `CreateWithTextures(…,const char* pszName,…)` 同族）| 同形，**修复前须补锤** |
| `CEffQuad::ToNextFrame` | ✅ `ret 0x4`=1 参 | arg1→`NewTexture` | ❌ **反例**：调用方 `add edi,0x28` 步长数组元素地址、且 `edi` 被读 `+0xd0` 字段 | 🔴 **分歧，单独立案，不得随 N1 批量改** |

## ⑧ 复核点
- **R-a** `ret 0x8` 是否可能来自别的原因（`__declspec(dllexport)` / 异常清理）？
- **R-b** `0x608cbc` 的 `push ebp` 是否确在 `%s` 位而非 `%d` 位？
- **R-c** `NewTexture` 是否有 `const char*`/`int` **两个重载**而注解只记一个？
- **R-d** ⑥ 的判定是否被 A-B-A 推翻？

---

# N2 · 函数式铸形 C2273/C2274（族 A）

## ① 根因标识
`C2273/C2274 'function-style cast' : illegal as right side of '->'/'.' operator` · 族 A · 命中 **3** 新失败单元（CCBResultWindow / UIMap / UICaption）

## ② 病灶层三问
| 问 | 答 |
|---|---|
| **哪一层** | **codegen**：`pipeline/gen/stages/stage4_substitution.py:484-493` 的 `&E->T`/`&E.T` 改写**只覆盖取地址形，漏了 `E.T` 直读形**。**Hex-Rays 无病**（`.UIWnd` 是其基类子对象渲染的固有形态，decomp L28 原样）。 |
| **消费者读哪个声明** | `UIWnd` 既是**类名**又在表达式里作**子对象标识符** ⇒ MSVC6 解析器把 `X.UIWnd` 当函数式铸形。 |
| **报错还缺什么** | C2274 只说"非法"，不说哪个 token 触发 ⇒ 用最小复现锁定。 |

## ③ 证据链（A 级 · 最小复现 1:1 复刻报错码）
```
struct UIWnd { virtual void Render() {} void Foo(); };
struct S : UIWnd { int UIWnd; int x; };
void g(S *this_) { int v = this_[2].UIWnd; }

→ t3.cpp(2) : error C2086: 'UIWnd' : redefinition
→ t3.cpp(4) : error C2274: 'function-style cast' : illegal as right side of '.' operator   ← 与 UIMap 逐字同码
```
对照实验（**证伪我的第一假设**）：`(((Der *)this))->Der::Render()`（ROWTABLE 形）**编译通过** ⇒ **不是 ROWTABLE 的问题**，早前判断需修正。

## ④ 精确机理
> Hex-Rays 把基类子对象渲染为 `E.T`（T = 类名）。codegen 现有改写只认 `&E.T`（`stage4_substitution.py:484` 的 `pointer_expression` + `&` 分支）。直读形 `this[2].UIWnd` 原样落到生成码 ⇒ MSVC6 解析器把 `UIWnd(...)` 当函数式铸形 ⇒ C2273/C2274（+ 同族 C2086 redefinition）。

## ⑤ 最小修法（未执行）
扩 `stage4_substitution.py:484` 同一判据（`fname in store.game_classes` + `fname not in _load_member_names()`）覆盖**无 `&` 的直读形**。

## ⑥ E2 引入 vs 解封 → **解封/显形**（同全局结论）

## ⑦ 爆炸半径 / 风险
🔴 **`E.T` 直读作 rvalue 时的等价改写语义未定**：是「基类子对象整体」还是「首 DWORD 读取」？两种改写字节不同。**不得盲改**，须先定语义（见 ⑧ R-b）。
另：`CCBResultWindow.cpp:820` 的 `((void(*)(UIStatic**, _DWORD))this[20].m_pFace[5]->UIWnd)(…)` 是**函数指针调用**形，与 UIMap 的直读**不同形**，须分开处理。

## ⑧ 复核点
- **R-a** 最小复现是否 1:1 对应真实 TU（真实 TU 里 `UIWnd` 的可见性/继承关系不同）？
- **R-b** `E.T` 直读的**正确等价形**是什么（子对象拷贝 vs 首 DWORD 读取）？必须从二进制（mov 宽度）裁决。
- **R-c** 同族 C2086 是否也在本轮错误集里（若是，同一修复可一并消）？

---

# N3 · `CPK::SetOpenMode` C2664（族 C）

## ① 根因标识
`'SetOpenMode' : cannot convert parameter 1 from 'const int' to 'enum ECPKMode'` · 族 C · 命中 **1** 新失败单元（SoundMgr，2 站点）

## ② 病灶层三问
| 问 | 答 |
|---|---|
| **哪一层** | **codegen**：Hex-Rays 不知道枚举常量名，发 `1`；codegen 未补 `(enum)` cast。 |
| **消费者读哪个声明** | `include/gbengine/gbVFileSystem.h:154` `void SetOpenMode(ECPKMode mode)`；`enum ECPKMode { CPKM_Null=0, CPKM_Normal=1, … }`（同文件 :30）。实现 `gbengine/src/gbVFileSystem.cpp:259`。 |
| **报错还缺什么** | 报错**完整**（`from 'const int' to 'enum ECPKMode'`）⇒ 无需补测。 |

## ③ 证据链
- 真源 `gbVFileSystem.cpp:259` `void CPK::SetOpenMode(ECPKMode mode) { if (!m_bLoaded) m_eMode = mode; }` —— **形参确为 enum**
- 调用点 decomp L14/L16 `CPK::SetOpenMode(&this->m_szScriptMusic[8], 1);` —— **实参是 int 字面量 `1`**
- MSVC6/C++：`int`→`enum` **不隐转** ⇒ 必然 C2664

## ④ 精确机理
> Hex-Rays 丢枚举常量名 → 发 `1` → codegen 未补 `(ECPKMode)` → C2664。

## ⑤ 最小修法（未执行）
**codegen 层**：在 enum 形参的实参处补 `(EnumType)` cast（等价变换，符合 codegen「修补 Hex-Rays 语法缺口」职责）。
⚠️ **不做**：把形参改成 `int`（破坏性 workaround，丢类型信息，违反 CLAUDE.md）。

## ⑥ E2 引入 vs 解封 → **解封/显形**

## ⑦ 爆炸半径 / 风险
同机制可能遍布全仓（**族 C 共 252 错 / 52 单元**）⇒ 修法应做成**通用规则**而非单点补丁，但**必须先枚举全部 enum 形参站点**（禁止批量推断）。

## ⑧ 复核点
- **R-a** 是否有别处已用 `(ECPKMode)` cast（若有，说明规则已有、只是没覆盖这里）？
- **R-b** 通用规则的判据应是什么（IDB enum 类型 vs 头里的 enum）？

---

# N4 · `gbMatrix4::SetAxisAngle` C2664（族 C）

## ① 根因标识
`'void __thiscall gbMatrix4::SetAxisAngle(**struct gbVec3D *,float**)' : cannot convert parameter 1 from 'const int' to 'struct gbVec3D *'` · 族 C · 命中 **1** 新失败单元（Object3D，3 站点）

## ② 病灶层三问
| 问 | 答 |
|---|---|
| **哪一层** | **头声明层**（include 链 / 同名声明不一致）：编译器**只看到 1 个重载** `(gbVec3D*, float)`，而真源有 **3 个**。 |
| **消费者读哪个声明** | 🔴 **关键**：`include/pal3_structs.h:180` 只有 `SetAxisAngle(gbVec3D*, float)`；`:272` 有 `SetAxisAngle(gbAxis, float, float)`；而 `include/gbengine/gbengine_types.h:140-142` 与 `include/topo_api.h:41-43` **三个重载全**。**谁先被 `#include` 到，决定编译结果** ⇒ 必须查 `Object3D.cpp` 的 include 链与 `/I` 顺序。 |
| **报错还缺什么** | 报错给出了**被选中的那个重载**（`gbVec3D*,float`）⇒ 已足以定位"重载集不完整"。 |

## ③ 证据链
- 真源 `topo/src/gbMatrix4.cpp:357/394/408`：**3 个重载**，`SetAxisAngle(gbAxis axis, float angle)` 的 `angle` **确为 float**（`angle * 0.017453292f`）
- 调用点 decomp L7/L9 `gbMatrix4::SetAxisAngle(&v4, 0, LODWORD(this->m_fPosBZ));` / `(&v4, 1, this->m_nSavedDataB)` —— 显式实参 2 个（`&v4` 是 this）⇒ 对应 `(gbAxis, float)` 重载
- **调用点无法区分 float/int**（x86 压栈 4 字节同形）⇒ 已用真源裁决，**不据调用点猜**

## ④ 精确机理
> 生成码调 `SetAxisAngle(2, LODWORD(x))`，而 TU 里可见的重载只有 `(gbVec3D*, float)` ⇒ `2` 无法转 `gbVec3D*` ⇒ C2664。**根因是重载集缺失，不是 cast 缺失**（若 `(gbAxis,float)` 在场，仍需 `(gbAxis)2` cast，那是 N3 同族问题）。

## ⑤ 最小修法（未执行）
**头声明层**：让实际被 include 的头声明**全部 3 个重载**（对齐 `gbengine_types.h:140-142`），或修 include 链指向完整头。再叠 N3 的 enum cast 规则。
⚠️ **不做**：删掉 `(gbVec3D*,float)` 重载来"让它匹配"（丢类型信息）。

## ⑥ E2 引入 vs 解封 → **解封/显形**

## ⑦ 爆炸半径 / 风险
`LODWORD(this->m_fPosBZ)` 暗示 `PalScriptMgr` 的 `+0x230`/`+0xE0` 成员类型也可能标错（**N4-b**），但**调用点字节无法裁决 float/int** ⇒ 需读成员被使用处的 `fld`/`fstp`。**单独立案，不得随 N4-a 改**。

## ⑧ 复核点
- **R-a** `Object3D.cpp` 实际 include 到的是哪个头？（`/I` 顺序 + `#include` 链实测，不得推断）
- **R-b** 三个重载的真实语义/地址是否与 `topo_api.h:41-43` 标注的 `0x1A60/0x1A30/0x1910` 一致？
- **R-c** N4-b（成员类型）是否真是 float？

---

# N5 · C2440 指针→整型赋值（族 B）

## ① 根因标识
`C2440 '=' : cannot convert from 'class gbTexture *' to 'long'` 等 · 族 B · 命中 **3** 新失败单元（UIPushButton / Combat / UICaption）

## ② 病灶层三问
| 问 | 答 |
|---|---|
| **哪一层** | **codegen**：`pipeline/gen/stages/stage4_substitution.py:768`「Pointer/integral assignment cast insertion (VC6 C2440)」**已存在但漏了这些形态**。 |
| **消费者读哪个声明** | `p_m_rect->left` 是 `LONG`（`tagRECT`）；`*p_m_curline` 是整型成员；`NewTexture`/`CreateParentData` 返回指针。 |
| **报错还缺什么** | `Combat.cpp:17` 的 `result = (int)this[1];` 是**另一形态**（结构体→int），须分开。 |

## ③ 证据链
- `UIPushButton.cpp:173/180` `p_m_rect->left = gfxMgr->NewTexture(...)` —— 指针→`LONG`
- `UICaption.cpp:59` `*p_m_curline = CreateParentData(Buffer)` —— 指针→整型成员
- `stage4_substitution.py:777-778` 自述："All insertions are byte-equivalent … **Cross-class pointer mismatches are NOT cast — they signal annotation** [errors]" ⇒ **该规则的设计就排除了某些形态**，需核是否误排
- `Combat.cpp:17` `result = (int)this[1];` —— decomp 原文即 `(int)this[1]`，是**结构体整体转 int**（原源码应是读某成员）

## ④ 精确机理
> 指针值存入整型成员/局部，MSVC6 要求显式转换；codegen 的补 cast 规则覆盖面不足。

## ⑤ 最小修法（未执行）
扩 `stage4_substitution.py:768` 的判据覆盖遗漏形态（指针→`LONG`/`unsigned`/整型成员）。
`Combat.cpp:17` 的 `(int)this[1]` **单独立案**（需先定 `this[1]` 的真实语义）。

## ⑥ E2 引入 vs 解封 → **解封/显形**

## ⑦ 爆炸半径 / 风险
族 B 共 `C2440 +69` 净增 ⇒ 规则改动**波及面大**，须逐形态枚举、逐个验证字节不变。

## ⑧ 复核点
- **R-a** `stage4_substitution.py:778` 的"NOT cast"排除项是否正是漏网原因？
- **R-b** 补 cast 是否真**字节等价**（`mov` 宽度不变）？必须 diff 反汇编验证。
- **R-c** `(int)this[1]` 的真实语义？

---

# N6 · MISATTRIBUTED 2 处 callee 命名（③ 面）

## ① 根因标识
9 处 MISATTRIBUTED 中的 **2 处**（另 7 处是 `AStarPathFinder` 函数名裸括号伪影，另案）

## ② 病灶层三问
| 问 | 答 |
|---|---|
| **哪一层** | **annotation·命名层**（IDB 名污染）。 |
| **消费者读哪个声明** | `PalScript.cpp:524` `std::string::max_size on PalScript::this` —— callee 名是 `std::string::max_size` 但对象是 `PalScript`；`Actor.cpp:2733` `UIListBox::_nearby_532a30 on Actor::this` —— callee 名 `_nearby_532a30` 是**地址后缀伪语义名**（CLAUDE.md 明令禁止的形态）。 |
| **报错还缺什么** | 需查这两个地址的**真实归属**（`audit_attribution_evidence.py` + objdump）。 |

## ③ 证据链（⚠️ **本轮未取二进制证据**）
- 生成码原文：
  - `PalScript.cpp:524` `if ( /* [MISATTRIBUTED] std::string::max_size on PalScript::this -> fix IDB name of callee */ std::string::max_size(this) < (unsigned int)v6 )`
  - `Actor.cpp:2733` `/* [MISATTRIBUTED] UIListBox::_nearby_532a30 on Actor::this */ UIListBox::_nearby_532a30(this);`
- 🔴 **缺**：两地址的 objdump 归属裁决 —— **下一轮必补**

## ④ 精确机理
> IDB 名字被 `vtable_gap_fill_v1` 批量复制污染（历史实测 185/305 copies）⇒ 同址多声明 ⇒ 归属错位 ⇒ `_is_derived_from()` 失配 ⇒ MISATTRIBUTED。

## ⑤ 最小修法（未执行）
按 `misattribution_ledger` bucket + `audit_attribution_evidence.py` 裁决，**修命名不改 `[MISATTRIBUTED]` 出口**（与 N1 同原则）。
`_nearby_532a30` 这类伪语义名**必须改回 `_todo_`**（CLAUDE.md 硬约束）。

## ⑥ E2 引入 vs 解封 → **解封/显形**

## ⑦ 爆炸半径 / 风险
另 7 处 `AStarPathFinder` 是**函数名裸括号伪影**（文件名 `AStarPathFinder__TryExpand(AStarPathFinder.cpp` 自证），修 2 个函数名即可，**证据已足**，与本卡 2 处**不同因，分开处理**。

## ⑧ 复核点
- **R-a** 两个地址的 objdump 归属（必补）
- **R-b** `std::string::max_size` 是否真是 `PalScript` 的方法（还是 std::string 成员对象被误当 this）
- **R-c** `_nearby_532a30` 的真实语义

---

## 遗留（诚实标注）

| # | 项 | 状态 |
|---|---|---|
| 1 | **A-B-A 未跑**（`regression_detector --before <旧census> --after`）| ⑥ 的"解封而非引入"判定置信度**高但非决定性**，须补跑收口 |
| 2 | N6 的 objdump 归属证据 | 未取 |
| 3 | N2 的 `E.T` 直读等价形语义 | 未定 |
| 4 | N4-b 成员类型 float/int | 未裁 |
| 5 | CEffQuad / UI3DCtrl 是否随 N1 | **已判：不得随**，须各自补锤 |
| 6 | 最小复现 `/tmp/n2probe/*` | **一次性/可丢弃**，未入仓 |
