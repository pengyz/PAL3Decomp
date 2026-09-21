---
name: gotcha-thiscall-free-function-is-a-model-error-and-invisible-to-error-metric
description: 自由函数不可能有 this —— decomp 里 77 条"无 :: 却 __thiscall"是归属错(28 纯重复发射/42 归属缺口)或签名错(7 类型丢失)；codegen 把它们发成 __cdecl 自由函数 ⇒ ABI 错 ⇒ 字节永不匹配，而**编译错误指标完全看不见**（合法代码）
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：`__thiscall` 的自由函数 = 模型错误；而它对本项目的错误指标**不可见**

## 现象

decomp 语料里有 **77 条 `__thiscall` 却名字无 `::`** 的条目（例 `void __thiscall(RoleSystem *this)` / `int __thiscall(int this, char *a2)`）。
codegen 把它们**发射成自由函数**，并保留显式 this 形参：

```c
// free_functions.h
void ResetPathState(RoleSystem *_this);      // ① 无调用约定 ⇒ 默认 __cdecl
int  GDB_GetItemNum(PAL_GDB *_this);         // ② 同上
void sub_5306A0(int _this, char *a2);        // ⑦ 把 this 改名 _this
// 调用侧
ResetPathState((RoleSystem *)this);          // 2 个栈参 ⇒ ABI ≠ 原 __thiscall(ECX)
```

**为什么这是错的**（不是"能编译就行"）：
* 原函数是 `__thiscall`（`this` 走 **ECX** + 剩余栈参）；发射成 `__cdecl` 自由函数 ⇒ **调用约定不同 ⇒ 字节必然不同** ✗
  ⇒ 该项目**第一契约是字节匹配** ⇒ 这类函数及其调用点**永远到不了 L1/partial** ✗；
* 且**至少 28 条是同一地址的重复发射**（下详）—— 同一函数在两个名字空间下各发一份。

## 分类（2026-09-21 实测，77 条全部可枚举）

| 类 | 条数 | 判据 | 修法 |
|---|---|---|---|
| **① 地址已被归属 ⇒ 纯重复发射** | **28** | 该地址已在 `structs/*.json` 的 `methods` 里 | **codegen 抑制自由发射 + 调用改成员形态**（**零注解工作**）|
| ② 未归属，但首参类型给出了类名 | 42 | 如 `UIScenePanel *Block`、`RenderTarget *this` | 归属恢复（**A 级证据**：类型本身）|
| ③ 未归属且类型丢失 | 7 | `int this`、`_DWORD *this`、`_BYTE *this` | 需 IDA 取证（或确认实为 static）|

①的真实样本（**同一地址、两份发射**，编译器不报错）：

| 地址 | 已归属的成员 | 又被发成自由函数 |
|---|---|---|
| `0x00532E10` | `RoleSystem::ResetPathState()` | `void ResetPathState(RoleSystem *_this);` |
| `0x004517A0` | `BINK::SetVideoRect` | `void SetVideoRect(BINK *_this);` |
| `0x00533DB0` | `RoleAtt::ResetNameField` | `void ResetNameField(RoleAtt *_this);` |
| `0x004A8770` | `CCCTData::CreateUI` | `Create__ovl_1_0(...)` |
| `0x004D6D30` | `C3DSpark::Update` | `void Update(C3DSpark *_this);` |

## **为什么**这个缺陷长期不可见（**第二个指标盲区**）

1. **编译错误指标看不见**：自由函数与成员同名但**不同名字空间** ⇒ 声明/定义/调用三者自洽 ⇒ **0 编译错误** ✗
   （与 `gotcha_c1003_truncation_blinds_metric` 同类：判据用了代理量，而非契约量"字节匹配"）。
2. **`check_annotations` 其实已经报 WARN** ✓：
   `functions[0x004B4830]: '__thiscall' without '::' in 'IsVisible' … likely member function, needs IDA investigation`
   ⇒ 但 WARN 不是工作项、无清单、无门禁 ⇒ **从未被处理** ✗。
   （本会话开头 `check` 输出里就有 13 条此类 WARN，我当时未追。）

## **何时使用**

* 看到 `C4234 '__thiscall' keyword reserved for future use`、或 `free_functions.h` 里出现带 `_this`/`*this` 形参的声明：
  **这不是"忠实的显式 this 表示"，而是归属/签名错误被固化成了 ABI 错误** ✗（我本轮就曾据此错误论证"它是忠实的"）。
* 评估任何改动时：**"编译错误不增加"不足以证明正确** —— 本项目还有两个不可见的轴：
  **ABI/调用约定** 与 **同地址重复发射**。判据要加上「调用约定是否与 decomp 一致」+「同一地址是否只发射一次」。
* 处理 ① 那 28 条时：**不要**只删掉自由函数声明 —— 其调用点会立刻 C2065；
  正确做法是**同时**把调用改写为成员形态 `((Cls *)this_expr)->M(rest)`，
  其中**类**来自证据（已归属的成员）、**形参数**来自该成员**注解里那份已归一化的声明** ⇒
  **不需要 `method_sigs`、不需要新建表** ✓（这也解开了 F3b 的阻塞）。

## ⚠️ IDA Pro MCP 二进制校验（2026-09-21，**使用者明确要求：这类结论必须走 MCP**）

```
# 起服务（~/.local/ida-mcp-venv, IDADIR=/home/peng/ida-pro-9.1）
python -m ida_pro_mcp.idalib_supervisor --host 127.0.0.1 --port 13337 --unsafe
# 打开工作 IDB → session_id，之后每次调用都要带 database=<session_id>
idb_open {input_path: original/PAL3.exe.i64, idle_ttl_sec: 7200}
```

实测（`session_id=f703cd44`）：

| 查询 | 结果 | 结论 |
|---|---|---|
| `export_funcs prototypes` | `0x00532E10 → void __thiscall(RoleSystem *this)`；`0x004517A0 → void __thiscall(BINK *this)`；`0x00479250 → int __thiscall(PAL_GDB *this)`；`0x005306A0 → void __thiscall(int this, char *)` | **IDB 里就是 `__thiscall`** ⇒ 发射成 `__cdecl` 自由函数是 **ABI 错** ✓ |
| `lookup_funcs 0x00532E10` | 名字 = **`ResetPathState`（自由名，无 `::`）** | ⇒ "重复发射"是**活的**，**不是陈旧 decomp JSON** ✓ |
| `xrefs_to 0x00532E10` | 仅 **1** 个 xref：`0x5331b2`（`?CalculateWorldPos@SceneProp@@QAEDM@Z`）| 爆炸半径小 ✓ |
| `disasm 0x005331a0` | `5331ad: mov ecx, ebx ; this` → `5331b2: call ResetPathState` | **ECX = 调用方自己的 `this`** ⇒ 调用点确实按 thiscall 传参 ✓ |
| 成员归属（注解检索）| `m_nPathState` ∈ RoleSystem · `m_fontcolor/m_wndcolor` ∈ UIWnd · `vecFling/parabola/pGeom` ∈ SceneProp | 被调函数访问 RoleSystem 成员 ⇒ **注解归属 RoleSystem 对** ✓，而调用方是 SceneProp 方法 ⇒ 两侧类不同，是**归属/签名的深层不一致**，需继续按偏移裁 |

⇒ **MCP 把三个命题都验成了二进制事实**；且证明了"离线推断只能算假设"——其中"是否是陈旧 JSON"这一支，
只有活 IDB 能证伪/证实。

## 审核工具（2026-09-21）

`python3 tools/audit_this_in_free_functions.py`（只读，`[A]` 非空 ⇒ exit 1）：
* **[A] 非法**：文件作用域函数形参名 == `this` ⇒ **34 处**（全在 `free_functions.cpp`）
  —— C++ 里 `this` 是关键字 ⇒ 语法错；**普查里只见 3 处，其余 31 处被 C1003 截断挡住** ✗
* **[B] 可疑**：显式 `_this`/`*this` 形参 ⇒ 55 处
* **[C] decomp**：无 `::` 却带 this 槽 ⇒ 77 条（①已归属=纯重复发射 28 · ②类型=已知类 11 · ③类型丢失 38）
* **[D]** 与 `this` 相关的现有语法错 ⇒ 9 条

**规则（使用者定，2026-09-21）**：**自由函数的形参名不允许用 `this`，要改**。
现状不对称：`emit_headers:2128` 只在**声明侧**把 `this`→`_this`，**函数体侧没改** ⇒ 34 处定义非法。

## 处置与实测结果（2026-09-21，已落地）

**规则**：自由函数的形参名不允许用 `this` ⇒ 改名 `_this`（合法标识符）。

**落点与不对称根因**：`stage4_substitution:597` **早已**对体里的 `this` **表达式节点**改名
（`node.type == 'this' and ctx.is_free_function`），但**没改形参名** ⇒ 实测出现"体里用 `_this`、
形参却叫 `this`" ⇒ 既非法（`C2143`）又级联"未声明标识符" ✗。
补在 `stage1_structural.run()` 的公共前导（两路径都继承）：`ctx.is_free_function` 且头部含
`this` 标识符 ⇒ 用**跳过字符串/字符/注释**的纯函数 `rename_this_identifier()` 整体改名。

| 指标 | before | after |
|---|---|---|
| `[A]` 非法（`tools/audit_this_in_free_functions.py`）| **34** | **0** ✓ |
| `C2143 syntax error : missing ')' before 'this'` 族 | **9** | **0** ✓ |
| free_functions.cpp 里与 this 相关的错 | 9 | 2（只剩另一族 `C2440` 成员函数指针）|
| S2 / L1 / 总错误 | 75/205 · 35 · 2150 | **不变**（被 C1003 吸收）|

⚠️ **修正我自己的一个指标**：`gotcha_c1003_truncation_blinds_metric` 里提的"列表内最大行号"**非单调**
—— 本次它从 2879 **下降**到 2848：错误变稀后，第 102 条错误出现在**更早**的行 ✗。
⇒ 该指标只在"错误密度不变、只往前推进"时可靠；**判据应以「目标族是否清零 + 有无同族新错」为主** ✓。

⚠️ **R14 补充**：IDA Pro MCP 的 idalib 会话**自己也持有 IDB**（`idb_open` 后）
⇒ 开着 MCP 时**不能跑 `apply`/`export`**（与"管线持有 IDB 期间不得并发 idat"同源）。
只跑 `codegen/probe/match` 是安全的（它们不读 IDB）✓。
