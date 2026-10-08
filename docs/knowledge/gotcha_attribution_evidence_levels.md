# gotcha：函数归属（free / static / 实例成员）的判别证据等级

**日期**：2026-09-29（PassCmdViaThread 归属翻转错误的终裁教训）
**症状**：把 `CCBSystem::PassCmdViaThread` 从类成员翻转为自由函数（证据="渲染 this-> 计数 0"+调用侧 cdecl fn-ptr 铸形）——终裁发现二进制序言 `mov edi, ecx` + `[edi+0x90]` 等成员访问密集 ⇒ 实为 **`__thiscall` 实例成员**。翻转撤销。

## 三种形态的判别表

| 形态 | 调用代码生成 | 二进制可判？ | 判别证据 |
|---|---|---|---|
| **free 函数** `bool F(int,int)` | `push`×2 + `call` | — | 名字形（裸名/`?F@@YAHHH@Z`）+ PDB |
| **static 成员** `bool C::F(int,int)` | `push`×2 + `call`（**与 free 完全相同**）| ✗ 不可判 | **符号修饰形**（`?F@C@@YAHHH@Z` 含 `@C@@`）+ PDB |
| **实例成员** `bool C::F(int,int)` thiscall | `mov reg,ecx` + `push`×2 + `call` | **✓ 可判** | **序言触 ECX**（`mov edi,ecx` 等）+ 成员访问（this+offset）|

## 证据等级（从强到弱）

1. **二进制序言/指令**（A 级）：`mov r32, ecx` 存 this + `this+off` 成员访问 ⇒ 实例成员铁证；
   无 ECX 触碰 ⇒ 非实例成员（free 或 static——**再分需符号形**）。
2. **符号修饰形**（A 级）：mangled name 的 `@C@@` 段=类归属；`AAE`/`ABE`=private/public thiscall
   实例形，`CA`/`CG`=static/cdecl 形。PDB 符号（PAL3A）可作参考（非单独证据，但名字形问题
   上是最强参考）。
3. **渲染文本**（C 级⚠️）：`this->` 计数**不可靠**——渲染的接收者名可能是 `v1`/`a1`/别的变量名
   （本次翻转错误的直接原因：文本计数 0 但二进制成员访问密集）；调用侧 fn-ptr 铸形是
   Hex-Rays 的类型猜测，亦非铁证。

## 可检查规则

- 归属翻转（成员↔free/static）**必须有二进制级证据**：ECX 序言判别（实例成员与否）+
  符号形（free vs static）；渲染文本只可作线索不可作证据。
- "零 this-> 用法"作为**否定**证据不成立——先查渲染的接收者名形态，再查二进制 ECX。
- static 与 free 的二进制代码生成完全相同——**只有符号形能分**；若符号不可得，保留
  语义上最可能的形并注记未定。

## 关联
- `debug_two_layer_localization.md`（同宗：验证层）
- CLAUDE.md "禁止仅凭 signature this 修正函数归属"——本条把"member access evidence"
  明确为**二进制级**（ECX 序言），补其证据等级缺位。
