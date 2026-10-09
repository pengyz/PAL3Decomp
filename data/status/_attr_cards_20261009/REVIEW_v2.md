# 归因卡 v2 · 经 kiro + codex 交叉对抗复核修订

**日期**：2026-10-09 · **v1 被交叉证伪 3 处、部分证伪 3 处**，本文取代 `README.md` 的结论
**复核模式**：kiro（代码级分支+安全性）× codex（证据链+政策+回归风险）**交叉一致**，可信度最高

---

## 0. 两位复核者的**交集结论**（交叉确认）

| # | 结论 | kiro | codex |
|---|---|---|---|
| 1 | **N4 完全证伪**（我把两个类的同名方法搞混）| ✅ | ✅ |
| 2 | **N5 修法违反政策**（会洗白真实注解/布局错误）| ✅ | ✅ |
| 3 | **N2 须拆两张子卡**（两种不同机理被我混为一谈）| ✅ | ✅ |
| 4 | **N6 范围远超"2 处命名"**（整函数级归因污染）| ✅ | ✅ |
| 5 | **全局"9 个新失败"过度**（实为 **7** 个 ok→fail）| — | ✅ |
| 6 | **C1003 度量盲区完全缺失**（违反 CLAUDE.md「评估改动前必看」）| — | ✅ |

---

## 1. v1 被证伪/需修正的主张（诚实记录）

| 卡 | v1 主张 | 判决 | 反证 |
|---|---|---|---|
| **N4** | 「`pal3_structs.h:180` 只有 1 个重载 ⇒ include 链不完整」| ❌ **完全证伪** | `:180` 是 **`gbQuaternion::SetAxisAngle`**（本来就只有 1 个重载，不是缺失）；`gbMatrix4::SetAxisAngle` 在 `:272-274` **3 个重载全**。且 `pal3_structs.h` **根本不在 `Object3D.cpp` 的 include 链上**（真实链：`Object3D.cpp:1` → `include/pal3/ida_defs.h:13` → `include/gbengine/gbengine_types.h:140-142`，3 重载全）|
| **N5** | 「codegen 补 cast 漏形态 ⇒ 扩 `stage4_substitution.py:768`」| ❌ **证伪 + 违反政策** | `UIPushButton.json:35-39` 注解 `+0x54/+0x58` 是 **`gbTexture*[2]`**；二进制 `0x4408bd: mov [esi],eax` / `0x4408ce: mov [esi+0x8],eax` / `0x4408f4: add esi,0x4` 证明**就是两个指针槽**。`UICaption.json:20-23` 标 `m_curline` 为 `int`，但 `0x43a8ff: mov [edi],eax` 存返回指针、`0x43a935: add edi,0x4` 走 3 槽 ⇒ **类型/布局/归属至少一层错**。补 cast = **破坏性 workaround**（CLAUDE.md:132-134）|
| **N2** | 「最小复现 1:1 复刻 ⇒ 成员名与类名同名」| ⚠️ **部分证伪** | 真实 TU **没有**字面成员名 `UIWnd`；且真实触发分裂为**两种机理**：`this[N].UIWnd` 直读（UIMap/UICaption）vs `ptr->UIWnd` **vfptr 读取**（CCBResultWindow **94 处**，占压倒多数）。且 **C2086 根本不在真实错误集**（只在我的复现里）|
| **N1** | E5「直接 `sprintf("%s", arg1)`」| ⚠️ **描述失真** | 真实链是**二级嵌套**：`sub_440960` → `sub_53FCF0` → `sub_53CF30`（内部 `__snprintf("%s(%d):%s,%s", …)`）。`0x608cbc = "Not Found %s In UI_opt.tli"` 是 helper 的**消息模板**，`ebp` 是**第二参数**间接进 `%s`。**核心结论（arity=2、arg1=LPCSTR）保留** |
| **N1** | arg2 = `bool`/`char` | ⚠️ **不得定名** | 二进制只证明 **1 字节宽 + 按真假分支**；`bool`/`char`/单字节枚举/调用方约定**无法区分** ⇒ 必须标「未定」（CLAUDE.md:87-89 禁猜测签名）|
| **N6** | 「AStar 7 处证据已足」| ❌ **无证据断言** | 文件名畸形**只能证明提取层有问题**，不能证明 7 个 callee 归属 ⇒ 须独立取证 |
| **全局** | 「9 个新失败」| ⚠️ **过度** | 权威基线 `baselines/latest.json` vs 当前 census 的 **ok→fail 只有 7 个**：CCBResultWindow / Combat / SoundMgr / UICaption / UIMap / UIPushButton / Object3D。`Actor` 是 fail 86→91、`PalScript` 是 fail 77→72（**计数变化，不是新失败**）|

---

## 2. 修订后的根因表（取代 v1 的全局结论）

| # | 根因（修订）| 病灶层 | 命中 | 判决 |
|---|---|---|---|---|
| **N1** | `UIPushButton::FormatText/LoadTexture` 签名错（arity 2 vs 1、arg1=`LPCSTR`）| **annotation** | 1 确证 + 2 待立案 | ✅ 核心成立（E5 措辞改写）|
| **N2a** | `this[N].UIWnd` 直读（基类子对象/vfptr 渲染）| **codegen**（`stage4_substitution.py:484` 只覆盖 `&E.T`）| UIMap / UICaption 3 站点 | ⚠️ **须补逐站点 `mov` 宽度 A 级证据**才能改 |
| **N2b** | `ptr->UIWnd` **vfptr 读取**被渲染成函数指针 cast | **codegen / IDB 类型** | **CCBResultWindow 94 站点** | ⚠️ **独立子卡，与 N2a 不同机理** |
| **N3** | `enum` 形参 + `int` 字面量，缺 enum cast | **codegen**（**从未实现** enum cast 规则，非"覆盖不全"）| SoundMgr 2 站点 | ✅ 通过（仅措辞）|
| **N4** | ❌ ~~重载集不完整~~ → **`int → gbAxis` 需显式 cast（与 N3 同机理）** + **`LODWORD(float)` 位保持问题** | **codegen** + **annotation** | Object3D 3 站点 | 🔴 **v1 撤销，重新归因** |
| **N5** | ❌ ~~codegen 漏 cast~~ → **annotation 成员类型/布局错**（`UIPushButton +0x54/+0x58` 应为 `gbTexture*[2]`；`UICaption +0x58 m_curline` 应为指针）| **annotation** | UIPushButton / UICaption | 🔴 **v1 撤销；修 cast 会洗白真实错误** |
| **N5b** | `Combat.cpp:17` `(int)this[1]` | 待定 | 1 | 立案（须先核 `sizeof(Combat)` 布局）|
| **N6a** | `UIListBox::_nearby_532a30` 伪语义命名 | **命名层** | 1 站点 | ✅ **已闭环**：`skip_functions.json:4569-4571` 自己标 `reason: compiler_global_init_stub`，**与它挂的名字自相矛盾**；`0x532a30` 是全局构造 stub（不读 `ecx`），`UIListBox` 真实方法在 `0x43xxxx`（差近 1MB）。**改回 `_todo_00532A30`** |
| **N6b** | `std::string::max_size` 被强塞 `this` | **codegen 调用形态** + **整函数级归因污染** | `PalScript::InitScriptObj` 全函数 | 🔴 **升级范围**：`0x407d40: mov eax,0xfffffffd; ret`（**零参、不读 `ecx`**），codegen 把无 this 的库函数渲染成 `PalScript::this` 成员调用。同函数 L614 `_Grow` 3参不符、L1037 `_Eos` 0参不符，`this` 被 reinterpret 成 4 种类型 ⇒ **疑似整个 STL `basic_string` 实现被误并入 PalScript.cpp**，不是命名层小问题 |
| **N6c** | `AStarPathFinder` 7 处函数名裸括号伪影 | 提取层/命名层 | 7 站点 | ⚠️ **须独立取证**（v1 的"证据已足"是无证据断言）|

---

## 3. 🔴 v1 漏掉的高危项（codex 发现）

### 3.1 `LODWORD(float)` 位保持陷阱（N4/N3 共同）
`include/pal3/ida_defs.h:54` —— `LODWORD(x)` 是**位保持的 DWORD lvalue**。把它传给 `float` 形参会触发**整数→浮点数值转换**，不是保持原始 float 位。
⇒ **即使补 `(gbAxis)2` 让它编译通过，也可能生成错误字节**（编译过 ≠ 字节对）。
**修法必须同时给出位保持的 float 实参，或修正成员类型** —— 二者取一，且须二进制裁决。

### 3.2 C1003 截断单元盲区（v1 全表缺失，违反 CLAUDE.md）
| 单元 | 当前错误数 | 风险 |
|---|---|---|
| `CCBStage.cpp` | 101 | **近阈值**；历史带 C1003；含 `SetVariant` int→enum、`SetAxisAngle` 同形错误（L7073/7078/7280）|
| `free_functions.cpp` | 101 | **近阈值**；含大量 C2440 |

⇒ **N3/N4 的通用 enum cast 规则会触及这两个单元** ⇒ 修掉早期错误会露出隐藏错误，**总错误可能不降**。
⇒ 收益判据必须改为：C1003 出现/消失 + **截断列表内最大错误行号是否后移** + `(code,msg)` 多重集 + **codegen 产物 diff**，而不是总错误数。

### 3.3 全局「非 E2 引入」的审计范围不完整
v1 的排除法只查了「命中单元是否在 E2 改的 4 个类内」，**没查间接继承耦合**：
`class Role : public Object, public PalScriptWaitObj, **public GlowObj**` —— `GlowObj` **正是 E2 改动的类之一**；`RoleSystem` 又继承 `UIWnd`（N2 核心类）。
⇒ 本次复核**未发现**任何 N 项机理链真正经过 `base_class`/`base_size`/vptr，但 v1 的排除法**证据强度被包装成"确定性结论"，实为"直接命中查过、间接传播未查"** ⇒ **降级为假设**，待 A-B-A 收口。

---

## 4. 修订后的最小修法（全部未执行）

| # | 修法（修订）| 前置条件（缺一不可）|
|---|---|---|
| N1 | `UIPushButton.json` 两方法签名改 **2 参、arg1=`LPCSTR`**；**arg2 类型标「未定」不写 `char`/`bool`** | `check_annotations.py` + `audit_type_layout.py --only UIPushButton` |
| N2a | 先补**逐站点 `mov` 宽度** A 级证据，再定等价改写形 | 每站点 objdump 读取宽度 |
| N2b | **独立子卡**（vfptr 调用形），与 N2a 分开验证 | 同上 |
| N3 | **站点级**补 `(ECPKMode)1`（值 1 = `CPKM_Normal`，合法枚举常量，同宽 4 字节压栈 ⇒ 等价）| 确认导入表装饰名 `?SetOpenMode@CPK@@QAEXW4ECPKMode@@@Z` + 调用指令 `0x53c38f: push 0x1` |
| N3 通用 | **新写**规则（不是扩分支）：被调形参是 `enum_specifier` 且实参是 integral 字面量 → 插 `(EnumName)` | **逐站**验目标签名 + 枚举值合法 + 同宽传参 |
| **N4** | 🔴 **撤销 v1**。真实修法 = **N3 同机理的 enum cast** + **`LODWORD(float)` 位保持方案**（二者取一，二进制裁决）| 先定 `m_fPosBZ`/`m_nSavedDataB` 成员真实类型（读使用点 `fld`/`fstp`）|
| **N5** | 🔴 **撤销 v1 修法**。改走 **annotation 层**：`UIPushButton +0x54/+0x58` 应为 `gbTexture*[2]`（二进制 `0x4408bd/0x4408ce/0x4408f4` 实证）；`UICaption +0x58 m_curline` 应为指针（`0x43a8ff: mov [edi],eax` 实证），且 `binary_size=96` 与写点 `+0xb8` **不符** ⇒ 布局层也要查 | `audit_type_layout.py` + `verify_fix.py --class <Cls>` |
| N6a | `UIListBox::_nearby_532a30` → **`_todo_00532A30`** | ✅ 证据已齐，可闭环 |
| N6b | **升级为「函数级归因边界复核」**：`audit_attribution_evidence.py` 核 `PalScript::InitScriptObj` 真实边界 | 不得只做命名层补丁 |
| N6c | AStar 7 处**独立取证** | 不得沿用 v1 的"证据已足" |

---

## 5. 全局判决

| 项 | v1 | **v2** |
|---|---|---|
| ok→fail 单元数 | "9 个新失败" | **7 个**（Actor/PalScript 是计数变化）|
| 「非 E2 引入」 | 确定性结论 | **假设**（直接命中已查、间接传播未查、A-B-A 未跑）|
| 可直接落地的修法 | 6 张卡 | **仅 N1（arg1/arity）+ N3 站点 + N6a** 三项证据齐备 |
| 须返工 | — | **N4 全卡重写 · N5 转 annotation 层 · N2 拆卡补证据 · N6b 升级范围** |
| C1003 盲区 | 无 | **已补**（CCBStage/free_functions 各 101 条，近阈值）|

### 与另一位复核者最该对齐的 3 个分歧点（codex 明确给）
1. **`LODWORD(float)` 传 `float` 形参时 codegen 应采哪种位保持输出**，及这是 N3/N4 共同规则还是单独规则
2. **`E.T` 直读在每类站点分别代表**「首 DWORD / 基类子对象地址 / 函数指针槽」—— **不能只按 token 相同合并**
3. **UIPushButton/UICaption 的 C2440 应修 annotation 成员类型、函数归属还是布局尺寸** —— 二进制写点与消费者声明必须逐层闭环

---

## 6. 本轮可信/不可信清单（给下一轮）

**✅ 证据齐备、可落地**：
- N1 的 arity=2 + arg1=`LPCSTR`（`ret 0x8` + `0x608cbc` 的 `%s` 位）
- N3 站点 `SetOpenMode(1)` → `(ECPKMode)1`（导入表装饰名 + `push 0x1`）
- N6a `_nearby_532a30` → `_todo_00532A30`（`skip_functions.json` 自相矛盾 + 不读 `ecx`）

**⚠️ 方向可信、证据不足**：N2a/N2b（须逐站点 `mov` 宽度）· N6c（须独立取证）

**🔴 必须返工**：N4（全卡重写）· N5（转 annotation 层）· N6b（升级范围）

**📌 全局**：A-B-A 未跑 · C1003 盲区已补表 · 「非 E2 引入」降级为假设
