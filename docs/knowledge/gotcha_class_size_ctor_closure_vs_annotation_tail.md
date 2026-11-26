---
name: gotcha-class-size-ctor-closure-vs-annotation-tail
description: 类尺寸别用注解成员末端减起始；用 operator new 立即数 + ctor 最远写界闭合，尾部成员可能是别的类混装（CCBRoleState 22,224 vs 20,568 实证）
type: gotcha
created: 2026-11-27
sources: [tsk_01M8CADS47F7XPAYVYGK37, docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md]
---

> 本条目只固化 #24 报告（`docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md`，白砚验收）§0/§2.2/§2.3/§4.1/§5.1 的结论；指令原文见其 §6 C1–C6。未新增未取证推断。

`CCBRoleState` 的注解写 `binary_size=22,224`、89 员，但二进制里 `operator new` 只分配 `0x5058`（20,568），ctor 最远写入也正好止于 `0x5058`。差额 1,656B 不是 ctor 越界，而是 23 个别的类的成员被拼进了注解表。

## 现象

- `data/annotations/structs/CCBRoleState.json` 写 `binary_size=22,224`、89 员；末员 `m_BattleFlags@0x56CC` 末端 `0x56D0=22,224`。
- 分配链：`0x44C5F3 push 0x5058` → `0x44C5F8 call 0x55353B`（`operator new`）→ `0x44C60E call 0x456AB0`（`??0CCBRoleState`）。
- ctor 最远写：`0x456B2A mov DWORD PTR [esi+0x5054],edi`，写入终点 `0x5054+4=0x5058`，与分配**逐字节相等**。
- 全库 `push 0x56D0`（22,224）为 **0 命中**。
- 第一遍 loop 把 `20,568` 回退成 `22,224`；这是注解自洽性拦截，不是二进制要求。

证据等级（#24 §0/§5.1）：分配行、ctor 写界是 **A**（指令原文 + 唯一分配）；尾部 23 员的跨类归属是 **B**（每族一个访问点 + 目标类尺寸吻合）；总体定谳 **B**（伪命题）。

## 为什么

22,224 是注解 89 员末端的算术值，不是任何分配尺寸。把 89 员的末端当成类尺寸，就会把下面这些外类成员算进来（归属逐条见 #24 §4.1）：

| 注解区间 | 员数 | 二进制归属 | 关键证据 |
|---|---:|---|---|
| `0x5060..0x50A0` | 15 | 另一个 20,644B 类 | `0x51272B push 0x50A4` → `0x51274E call 0x4EC680`；该函数 `mov ecx,0x1429; rep stos` = `0x1429×4=0x50A4` |
| `0x55C8..0x55D0` | 4 | 全库零访问（幻影成员） | `+0x55C8/+0x55CC/+0x55D0` 命中 0 |
| `0x5654..0x565C` | 3 | `CCBUIPanel`（22,112=`0x5660`） | 访问者 `0x44A2E0` 由 `CCBUIPanel::Update 0x44A1B0` 以同 this 调用；最大位移 `0x565C+4=0x5660` |
| `0x56CC` | 1 | `PropUI`（29,056=`0x7180`） | `0x46D2BE lea ecx,[esi+0x56CC]` 位于 `PropUI::InitUI 0x46D140`；该函数最大位移 `0x70D8<0x7180` |

合计 `15+4+3+1=23`，正好是 89 员里偏移 `≥0x5058` 的全部成员。

另外两条容易误用的“证据”：

- **IDB 的 size 不是独立证据**。`asm/pal3/ida_structs.json` 的尺寸由注解导出，注解写 22,224 它就读回 22,224；用它反证注解等于循环论证。
- **census 的尺寸也不是独立证据**。census 按注解的 `binary_size` 扫洞，注解偏大时它只会把外类区间记成“洞”。

## 怎么判

按顺序做，至少拿到两条独立闭合再改 `binary_size`：

1. **找分配点**：在 `_disasm_cache.txt` 找 `push imm32; call 0x55353B`（`operator new`），确认该立即数唯一；`new[]`（`0x553627`）和 `operator new(size_t,int)` 不计入类分配。CCBRoleState 的 `push 0x5058` 全库只有 1 处。
2. **找 ctor 写界**：在 ctor 函数体地址区间内扫 `[reg+disp]` 写入，取最大 `disp+宽度`；它应与分配立即数相等。CCBRoleState 是 `0x5054+4=0x5058`。注意排除 `[esp+..]` 栈槽和 `ds:`/`fs:` 绝对寻址。
3. **确认类身份**：ctor 必须写自己的 vptr，例如 `0x456B36 mov DWORD PTR [esi],0x56B364`；再核对该 vtable 的槽（`Render/Update/~CCBRoleState/OnMessage`）与方法表一致。不要只凭函数名或注解名认类。
4. **交叉第三源**：若该类被派生类内嵌或作为数组元素，用内嵌偏移/数组 stride 再闭合一次；若是栈/全局对象，用栈帧 `sub esp,imm` 或全局尺寸代替 `operator new`。
5. **先判尾员归属，再谈尺寸**：对每个 `≥分配尺寸` 的成员，查访问点落在哪个函数、那个函数的 `this` 属于哪个类、目标类尺寸是否与最大位移吻合。零访问的先当幻影，不要直接算进本类。
6. **最后改注解**：`binary_size` 改成闭合值；尾员按归属删除/迁移，未命名目标类先挂账，不能静默丢。改完跑 `audit_type_layout`、`check_annotations`、`census_struct_holes`，再在独占窗口跑完整 loop。

禁止把这些当尺寸证据：

- 「成员末端 − 类起始」的算术值；
- census/IDB 里与注解同源的尺寸；
- 「这个数看起来更像」或 PDB 的参考值；
- ctor 里出现过的最大偏移，但未确认它写的是本类对象（可能是内嵌子对象或另一个 this）。

最小复核命令（CCBRoleState 例）：

```bash
grep -nE 'push\s+0x5058\b' data/status/_disasm_cache.txt
grep -cE 'push\s+0x56d0\b' data/status/_disasm_cache.txt
grep -nE '^\s*456(ab|b[0-5])[0-9a-f]:' data/status/_disasm_cache.txt | grep -E '\+0x50[0-9a-f]{2}\]'
```

期望：第一条只有 `101376:44c5f3` 一处；第二条输出 `0`；第三条命中 `115561:456b2a ... [esi+0x5054]`。

## 何时用

- 任何 `binary_size`/`sizeof` 争议，尤其是注解值明显大于 `operator new` 分配值时。
- 洞集中在类尾，且尾员访问点稀少或落在别的函数域时。
- ctor 分配尺寸与注解末端不相等，或第一遍 loop 把新尺寸“回退”时。
- IDB 的 size 与注解完全一致、但找不到对应分配点时（先怀疑两者同源，不要当双证）。
- R6 这类按类重铸/拍板前，需要先确认“真尺寸”而不是继续在越界伪命题上做决定。

不适用：没有 `operator new` 且没有栈帧/内嵌/数组 stride 可闭合的类；这类只能标“证据不足 + 缺口”，不要用注解末端算术凑一个尺寸。
