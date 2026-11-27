---
name: pattern-chimera-class-split-by-object-identity
description: 一个注解类装着多个二进制对象时，用 vptr 存表、ctor 基类调用、分配/写界三锚拆成独立类，不按成员偏移猜。
type: pattern
created: 2026-11-27
sources:
  - tsk_01M8CCP13GVWNJTCQAXXMF (#19 R4 落地)
  - tsk_01M8BVF4T62R0V707HJ7BY (#16 R4 施工图)
  - docs/specs/2026-11-26-r4-fill-change-plan.md
  - docs/specs/2026-11-26-screeneffect-prefix-evidence.md
---

一个 struct JSON 的 `binary_size` 可能只是“最大那个对象”的尺寸；同一份成员表里混着多个各自分配、各自写 vptr 的对象。拆类时先判对象身份，再判成员归属，最后才改尺寸和成员表。

## 现象

R4 的 `ScreenEffectMgr.json` 拆前是 **363,968B / 16 员**，实际装着三个对象：

| 对象 | 尺寸 | 身份锚 | 拆后 |
|---|---:|---|---|
| `ScreenEffectRingNode` | 363,968 | ctor `0x4BEE60`；`0x4BEF01 mov [edi],0x56F580`；基类调用 `0x4BEE7F call 0x4B6F70`（PAL3VisNode ctor）；工厂 `0x4B7121 push 0x58DC0` | 363,968B / 13 员，base `PAL3VisNode`，vtable `0x56F580` |
| `ScreenEffectMgr` | 152 | 单例实例 `0xDE7DF8`；ctor `0x4BDFB0`；尾写 `0x4BE03E mov [esi],0x56F508`；dtor `0x4BE060`→`0x4BE080` | 152B / 16 员，vtable `0x56F508` |
| `ScreenEffect` | 24 | ctor `0x4BDF10`；写 vptr `0x56F4F0`；`[8]=1`，`[4]/[0xC]/[0x10]/[0x14]=0` | 24B，vtable `0x56F4F0` |

拆前 `0x56F508` 被记在 `ScreenEffect` 名下，`0x56F580` 被记在 `ScreenEffectMgr` 名下；`0x4BDF10` 还挂在 `RenderTarget.methods`，`0x4BEF50` 挂在 `UIRoleDialog.methods`。这些都是“同地址多 owner”的残留。

另一个同时暴露的尺寸矛盾：`PAL3VisNode` 注解 `binary_size=88`，但 ctor `0x4B6F70` 写 `[esi+0x58]`；实际是 **92B / 1 员 `m_nState@0x58`**，`base_size` 仍 88（直接基类 `gbVisNode` 的尺寸），派生首员从 `0x5C` 起。三个派生 `CEffGroupNode`（116）/`UI3DModelNode`（248）/`ScreenEffectNode`（220）的 `base_size` 跟着改成 92，`sizeof` 不变。

拆后洞要分两套口径：census 口径 B1 76B→B2 **64B**（`[0x68,0xA4)=60` + `[0xAC,0xB0)=4`）；严格布局洞 B1 96B→B2 **84B**（再加 `[0x410,0x424)=20` 有访问但未命名）。把“96→64”写成一条会把两套口径混在一起；`ScreenEffectMgr` 只剩 `[0x90,0x94)=4B`。洞没有清零并不等于拆错，剩余洞要按成员证据单独处理。

## 为什么

注解是围绕“成员偏移 + 空洞填充”长出来的：只要一个 ctor 写到更远的偏移，JSON 就会把 `binary_size` 撑到那里，后面的对象也被并进同一张表。二进制里却是三次独立构造、三个 vptr、三套方法；`ScreenEffectMgr` 只是其中最小的单例。

`ida_structs.json`、census 和 codegen 都继承注解的结果，所以它们会一致地“证明”这个错误尺寸；loop 的注解自洽检查也发现不了混装。唯一能拆开的是二进制里的对象身份锚。

owner 门还会放大这个问题：同一 VA 若仍留在旧类的 `methods`/`vtables` 里，新类的迁移可能被静默丢弃，或者旧类继续占着名字。拆类必须同时删旧 owner，不能只新建 JSON。

## 怎么判

### 锚 1：vptr 存表

在 ctor 尾部找 `mov [this], offset vtable`。R4 三处：

- `0x4BEF01 mov [edi],0x56F580` → RingNode；
- `0x4BE03E mov [esi],0x56F508` → Mgr；
- `0x4BDF10` ctor 写 `0x56F4F0` → ScreenEffect。

vtable 地址是对象身份的第一手证据；不要用类名、成员名或“谁看起来更像”反推。

### 锚 2：ctor 基类调用链

RingNode ctor `0x4BEE60` 在 `0x4BEE7F call 0x4B6F70` 调 PAL3VisNode ctor；后者写自己的 vptr `0x56F37C` 并写 `[esi+0x58]=0`。这条链同时给出：

- 基类是谁：`PAL3VisNode`；
- 基类尺寸：92（不是 88）；
- `m_nState@0x58` 的归属：基类成员，不是 RingNode 自有成员。

### 锚 3：分配立即数 + ctor 写界

对每个堆对象找 `push <size>` → `operator new`（`0x55353B`）→ ctor：

- RingNode：`0x4B7121 push 0x58DC0`（363,968）→ `0x4BEE60`；
- 分配立即数、ctor 最大写偏移 + 宽度、类尺寸三者应闭合。

单例或短生命周期子对象没有 `operator new` 时，不强行凑第三锚；vptr + ctor 基类链已足够判身份，尺寸再用 ctor 写界或成员终点核对。`ScreenEffect` 的 24B 就属于这种短对象，不要为它伪造一个 `push 0x18`。

### 判完后怎么落

1. 先列“对象 → 尺寸 → 三个锚”的表；至少两锚一致才拆。
2. 新建独立 JSON：`bases`/`base_size`/`binary_size`/vtable 按锚填写；名字没有语义证据就留 `m_unk_<offset>`，不要造名。
3. 成员按“谁写入/谁读取 + 目标对象尺寸”归位；拿不准的成员留洞，不按相邻偏移硬塞。
4. 方法/槽按 vtable 家族迁移；同 VA 旧条目从原 owner 删除（R4：`RenderTarget` 的 `0x4BDF10`、`UIRoleDialog` 的 `0x4BEF50`），`functions.json` 的 `0x4BE5D0` 从 `InitScreenEffectSingleton` 改名 `DestroyScreenEffectSingleton`。
5. 拆完跑回归：R4 新增 `tests/test_r4_screeneffect_split.py`，7 条判据（尺寸/base_size/成员名/禁 `m_unk_`/旧 owner 删除/改名）改前 7 failed、改后 7 passed；再跑 check、apply→export、census，确认洞落到预期值。

## 证据索引

- 拆类、ctor/vtable 对照：#16 `docs/specs/2026-11-26-r4-fill-change-plan.md` §1.1/§1.2/§2.2/§4（`0x4BEE60`/`0x4BEE7F`/`0x4BDFB0`/`0x4BDF10`/`0x4BEF01`/`0x4BE03E`）。
- 拆后实体：#19 落地的 `data/annotations/structs/ScreenEffectRingNode.json`、`ScreenEffectMgr.json`、`ScreenEffect.json`、`PAL3VisNode.json`，以及 `tests/test_r4_screeneffect_split.py`（7 条判据，改前 7 failed、改后 7 passed）。
- 洞：`data/status/struct_holes_20261125.json`（`ScreenEffectRingNode` 64B/2 洞、`ScreenEffectMgr` 4B/1 洞；2026-11-27 01:05 读）。
- 旧 owner 清理：`RenderTarget.json` 已无 `0x4BDF10`，`UIRoleDialog.json` 已无 `0x4BEF50`，`functions.json` 的 `0x4BE5D0` 已改名 `DestroyScreenEffectSingleton`。

## 何时使用

- 一个类的 `binary_size` 异常大（几百 KB），洞集中在类尾；
- `binary_size` 与 ctor 的 `operator new` 立即数对不上，或 ctor 写界只到中间；
- `methods`/`vtables` 来自多个家族，或 vtable 槽指向别家的表；
- `bases` 为空但槽位、基类 ctor 调用都指向某个基类；
- census 里一个类占了全库洞的很大比例；
- 同一个 VA 在多个类的 `methods`/`vtables` 里出现（owner 残留）；
- 准备重铸 `binary_size` 前，先把“一个类还是多个对象”判清。

R6 的 `CCBStage`、`CCBRoleState`、`C2DSpark` 也出现“注解尺寸与对象身份不符”的同类形态；套用本判据时仍以各自的对象锚为准，不能拿本篇的 R4 尺寸当别的类的证据。
