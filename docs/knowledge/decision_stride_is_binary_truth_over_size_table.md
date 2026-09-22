---
name: decision-stride-is-binary-truth-over-size-table
description: 成员尺寸的**真相是"注解步长"**（=二进制派生），而尺寸表/类型估计只是对仓库 shim 的测量——两者冲突时以步长为准；"实际类型尺寸 > 步长"无法用补白修正，必须改类型本身（shim/枚举尺寸与二进制一致）；编译器审计是唯一裁判
type: decision
created: 2026-09-22
updated: 2026-09-22
status: active
sources: [session-2026-09-21]
---

# decision：**步长是二进制真相**，尺寸表只是兜底

## 实测链（2026-09-22，三级 DAG，全部用编译器裁判量化）

```
Comp_DonateUI  sizeof=46204 vs 注解 46192  (+12)
  ← UIRoleDialog   sizeof=728  vs 注解 720   (+8)
      ← UIStaticFlex  sizeof=196 vs 注解 192  (+4)   ← 发射器多发 `_gap_0A1[3]`（以为 gbFontType=1 ✗）
      ← UITextArea    sizeof=108 vs 注解 104  (+4)   ← 仓库 shim 的 `string`=16，而二进制步长=12 ✗
```

* `UIStaticFlex` 的**成员类型尺寸全部正确**（`gbFontType`=4 ✓ `UITextureArray`=68 ✓ `UIStaticFlex_State`=4 ✓）
  ⇒ 漂移**只**来自发射器**多发的 3 字节 gap**（`_gap_0A1` 声明 0xA1、实际 0xA4 ⇒ +3），
  其后 `m_tilesize` 被 4 对齐推到 0xA8 ⇒ **+4** ✓ 算术自洽 ✓
* `UITextArea`：注解 `m_buf@0x44`、下一成员 `m_bInvalidate@0x50` ⇒ **步长 12** ✓（=二进制）
  而仓库 `pal3_stl.h` 的 `string` 实测 **16** ✗ ⇒ **+4**

## 规则（**步长优先**）

1. **记账以"注解步长"为准**（步长 = 二进制派生的事实 ✓）
2. 类型尺寸估计只作**下限检查**：
   * 估计 ≤ 步长 ⇒ 用补白补齐 ✓（无害）
   * 估计 > 步长 ⇒ **无法补白**（不能负 padding ✗）⇒ **必须改类型本身**（shim/枚举/typedef 尺寸要与二进制一致 ✓）
3. **唯一裁判是编译器审计**（`offsetof` 全等 + `sizeof == binary_size` ✓）——
   任何"尺寸表"（STL 表/`sdk_types`/`ida_structs['size']`）都可能与二进制不一致 ✗
4. 因此：**"我实测了一个尺寸" ≠ "二进制就是这个尺寸"** —— 前者是我方 shim 的事实，后者才是目标 ✓

## 教训（我自己的错误，值得记住）
* 我加的 **STL 全局尺寸表**（`vector/string=16` 等）**修复了 `UIListBox` 的 −12** ✓，
  但同一张表对 `UITextArea` 的 `string` 又是**错的**（二进制要 12 ✗）⇒
  ⇒ **尺寸表不能作为"真相"**，只能作为"当我们无法从步长推断时的最佳猜测" ✓
* 判据顺序必须是：**① 注解步长（二进制）→ ② 编译器实测（我方类型）→ ③ 兜底常数** ✓

## **何时使用**
* 发现"某类 `sizeof` ≠ `binary_size`"时：**先算步长**，再判断是"少补白"还是"类型过大" ✓
* 想加/改任何尺寸表时：先问"这张表与二进制步长冲突过吗？" ✓（本会话已有一次 ✗）
* 报"布局已修好"之前：**必须**跑 `offsetof` 全等 **且** `sizeof == binary_size` ✓

## 追加·更正（同一会话，**第二次自我纠正**，并由独立子 agent 复核确认）

⚠️ 上一版此处我写"二进制 `string` = 12 字节"**是错的** ✗ —— 必须撤回 ✓

**错误怎么来的**：我在 `UITextArea::InitAfterClear` 里看到 `mov [esi+50h],edi` / `mov [esi+54h],edi`，
据"若字符串 16 字节则在 0x50 写会写进字符串内部"推出 string=12 ✗。
**独立复核（我自跑 O2 + 子 agent 各自验证）推翻**：

```
444F79  mov    %ecx,%esi                 ; esi = this ✓
444F8F  mov    %al,0x48(%esi)            ; +0x48 BYTE（注解缺失）
444F92  mov    %edi,0x4c(%esi)           ; xor edi,edi ⇒ **int 归零**
444F95  mov    %edi,0x50(%esi)
444F98  mov    %edi,0x54(%esi)
444F9B  lea    0x68(%esi),%ecx ; call 0x445ea0
444FD4  movl   $0x3f000000,0x44(%esi)    ; ★ +0x44 是 **float 0.5** ✗（注解说是 string ✗）
444FAE  mov    %edi,0xb0(%esi)           ; 对象 ≥0xB0/0xBC ✗（注解 binary_size=104 ✗）
```

⇒ 真相：**`UITextArea` 的注解是错的** ✗（`m_buf` 不在 0x44、类远大于 104、缺 +0x48 等字段），
而 **`string` 就是工具链 `std::string` ⇒ 16 字节** ✓（`pal3_stl.h` 仅 `#include <string>` + `using namespace std` ✓；
5 个类的步长也都是 16 ✓）

## 教训（比结论更重要）
1. **孤立的指令片段会误导** ✗ —— 我把一处 int 归零读成"12 字节字符串之后的字段"，
 原因是**没有读整条函数里的完整字段图** ✓ ⇒ **裁定字段布局必须看函数内全部访问** ✓
2. **"步长多数派"不是证据** ✓（本会话已证），**"单条指令的推理"也不是证据** ✗
3. **注解的 `source` 是 `pdb_merge`/`gen_headers` 时 ⇒ 无二进制证据** ✗ ⇒ 不能当基准 ✓
4. **`verify_fix` 只证明"发射 == 注解"，不证明"注解 == 二进制"** ✗✗
 ⇒ 当注解本身错时它会把错误**认证为通过** ✗ ⇒ **必须补一道"注解 vs 二进制"的门** ✓（见下）

## 补门要求（子 agent 复核建议，已采纳）
在 `verify_fix` 增加**注解 vs 二进制**检查：对改动类的每个成员，
用 `tools/bin_oracle.py` 找 **`[reg+off]` 访问**并核对其**宽度/种类**与注解**是否矛盾** ✓；
对 shim/类型表类改动，另跑**全量布局审计**对比冲突类数 ✓
