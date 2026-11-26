# UIGameFrm 落位预期基准（#8 裁决后的验收 oracle）

- 卡号：#26 `tsk_01M8C91W7E2V36HF2FY7SG`
- 日期：2026-11-26
- 角色：验收 oracle（**独立于实现方**）。本文只给「预期」，不判断实现是否已达成。
- 只读：未改 annotation / 生成树 / 基线，未运行任何 `pipeline/cli.py` 命令。

## 0. 独立声明

- 数据来源仅四类：`original/PAL3.exe.asm`（IDA 反汇编文本）、`asm/pal3/decomp/`、`data/annotations/structs/*.json`、`data/status/struct_holes_20261125.json` 与 `data/status/probe_heap_alloc_census_20261126.json`。
- **未读取** #23 在途产物；#8 的裁决卷宗只当「待验命题骨架」使用（§2.2 子对象表逐条独立复算，不是照抄）。
- 未读取 #9 SaleUI 的任何文件。
- 本文与实现方无共同作者；结论可被实现方反证推翻，反证请直接指出 §4 的行号。

## 1. 复现命令与原样输出

```bash
$ python3 - <<'PY'
import json
d=json.load(open('data/annotations/structs/UIGameFrm.json'))
km=d['known_members']
print('size',d['binary_size'],hex(d['binary_size']))
print('members',len(km),'max',hex(max(int(k,16) for k in km)))
print('vtable',d['vtables'][0]['addr'])
PY
size 28268 0x6e6c
members 63 max 0x6e18
vtable 0x0056b094

$ python3 - <<'PY'
import json
h=json.load(open('data/status/struct_holes_20261125.json'))
print({k:h['_meta'][k] for k in ('classes_with_holes','total_hole_bytes','total_holes','unresolved_type_members','vptr_exempt_classes')})
c=[x for x in h['classes'] if x['cls']=='UIGameFrm'][0]
print(c['size'],c['hole_bytes'],c['total_holes'],len(c['holes']))
PY
{'classes_with_holes': 200, 'total_hole_bytes': 867548, 'total_holes': 1120, 'unresolved_type_members': 6, 'vptr_exempt_classes': 58}
28268 27916 37 37

$ grep -c "push    6E6Ch" original/PAL3.exe.asm
0
$ grep -ci "6E6Ch" original/PAL3.exe.asm
16
$ grep -n "sub_44F050      proc" original/PAL3.exe.asm
122290:sub_44F050      proc near
$ grep -n "sub_44F130      proc" original/PAL3.exe.asm
122358:sub_44F130      proc near
```

`6E6Ch` 的 16 处命中全部是**其它类**的 `[+0x26E6C]` 偏移访问（不是 28268 字面量），见 §3。

## 2. 独立复算的子对象骨架（本报告的骨架）

按 asm 逐条读出的构造/析构链。**表内 span 用尺寸累加闭合，不靠注解**。

| 偏移 | span | 类/身份 | 证据 | 等级 |
|---|---|---|---|---|
| 0x000 | 0x104 | UIGameFrm 自身（UIWnd 基 + 0x44..0x102 区） | vtable 0x56B094 7 槽；decomp memset 0x44..0x6A 与 0xDC..0x102 | A |
| 0x104 | 96 | UICaption | dtor 0x44A7F0 写 0x56AFB0、+0x44→0x56AFA4、adjustor 0x56A9C0；注解 size 96 | A |
| 0x164 | 76 | RoleCameraCtrl | dtor 0x450AD0 写 0x56B120；注解 size 76 | A |
| 0x1B0 | 224 | **未知** | 0x1B0–0x290 无 ctor/dtor/写点；decomp 只在 0x44..0x102 与 0xDC..0x102 清零 | 无 |
| 0x290 | **1488 (0x5D0)** | **UIListBoxDialog 复合体**（暂用 g_UIListBoxDlg 全局名） | dtor 0x451900：`[esi]=0x56B178`、`[esi+48h]=0x56B16C`、`lea ecx,[esi+510h]→0x445010`、`lea ecx,[esi+58h]→0x43E120`、`0x43BBB0`(UIFrameWnd dtor)；见 §2.1 | A（span 闭合） |
| 0x860 | 0x6E0（5×352） | **5 元素数组，元素 352B** | dtor `??_M(0x860,0x160,5,0x450390)`；ctor `??_M(0x860,0x160,5,0x450390)`；逐元素 0x4503D0(Create)/0x450550(Show) | A（大小）/ B（类名） |
| 0xF40 | 1108 (0x454) | UISceneMap（globals）／dtor 名 RoleAtt | dtor 0x450EB0 写 0x56B14C + 0x56B140@+0x48；真表 0x56B140 3 槽，writer `UISceneMap::Init`；globals 切片 g_UISceneMapDlg 声明 UISceneMap 1012 | B（**1012 与 1108 二义**） |
| 0x1394 | 9520 | UITitle | dtor 0x44ACE0 写 0x56AFD4；ctor/InitRoles 0x44ADE0；注解 size 9520 | A |
| 0x38C4 | 12 | 对齐填充 | UITitle 止 0x38C4，下一数组止点 0x38D0 | B |
| 0x38D0 | 13632（6×2272） | UIEmote[6] | dtor `??_M(0x38D0,0x8E0,6,0x44E5E0)`；InitItems 0x44E660 ×6；vtable 0x56B044；注解 UIEmote size 2272 | A |
| 0x6E10 | 4 | `m_pGameObj`：指向 2864B 对象（表 0x56B1BC） | Init `new(0xB30)`→ctor 0x452580→store [esi+6E10] | A（大小）/ 类名待定 |
| 0x6E14 | 4 | `m_pRoleStatePanel`：RoleStatePanel*（176256） | census `176256 ?InitUI@RoleStatePanel@@QAEHXZ store=esi+0x6E14 site=0x44f1da` | A |
| 0x6E18 | 4 | `m_pTitleYXXX`：UITitle_YXXX*（3832） | Init `new(0xEF8)`→ctor 0x47DCA0→store [esi+6E18] | A |
| 0x6E1C | — | 类尾（注解按 0x6E6C） | 无任何访问点；下界=0x6E1C | **无证据（80B 估算）** |

### 2.1 0x290 复合体的 span 闭合（本报告最关键的新发现）

`sub_451900`（asm:126527；由 UIGameFrm dtor 在 asm:122290 起的 `lea ecx,[esi+290h]` 处调用）按逆序析构三个部分：

```
lea edi,[esi+48h]  ; 第二子对象 vptr 位
mov [esi],0x56B178
mov [edi],0x56B16C
lea ecx,[esi+510h] ; → 0x445010 = UITextArea 析构（写 vtable 0x56AEA4，size 192）
lea ecx,[esi+58h]  ; → 0x43E120 = 1208B 类（cls_43dfc0）完整 dtor
call 0x43BBB0      ; → UIFrameWnd::~UIFrameWnd（size 72）
```

`sub_451980`（CreateDialog）与之一致：`lea ebx,[esi+510h]` 调 `0x4450A0`（note 文本创建）/`0x445FA0`；`lea edi,[esi+58h]` 调 `0x43E560`(SetColumnHead)/`0x43F690`(SetItemData)；首调 `0x445B90`(UIWnd::Create)。

尺寸累加：`0x48(UIWnd 基) + 0x10(第二 vptr 区 0x48–0x58，其中 0x4C–0x58 的 12B 内容未定) + 0x4B8(1208B UIListBox) + 0xC0(UITextArea 192) = 0x5D0`。

注：0x4C–0x58 这 12B 未定内容不影响洞计量——它在复合体成员内部，属「双视图」，不是 UIGameFrm 的缺员。

**闭合验证**：`0x290 + 0x5D0 = 0x860`，恰为 0x860 数组起点（`??_M(0x860,0x160,5)`），两者不重叠、无间隙。

⇒ **0x290 不是 72B 的 UIListBox，而是 1488B 的复合对话框**。这是 #8 §2.2 表里唯一需要修正的子项（#8 写「0x290–0x2d8 | 72 | UIListBox」）。

### 2.2 类型名的两处不确定

- 0x6E10 指向的 2864B 对象：ctor 0x452580 写表 0x56B1BC，内部 `UIListBox@0`(0x43DCD0)、`+0x48`(0x452790)、`+0x43C`(0x451CC0)；函数名沿用 `NavFaceLayer`，但 `NavFaceLayer.json` 只有 16B 且无表 ⇒ 名称是**待定名**，大小 2864 才是 A 级。
- 0xF40 对象：dtor 名 `RoleAtt::~RoleAtt`、globals 切片名 `UISceneMap`、表 0x56B140 的 writer 是 `UISceneMap::Init`。`1012`(globals 类型尺寸) 与 `1108`(下一子对象 0x1394 减 0xF40) 差 96B，未定。

## 3. 尺寸三方对账与真值裁决

| 来源 | 值 | 性质 |
|---|---|---|
| 注解 binary_size | 28268 (0x6E6C) | 来自 IDA UDT；而 IDA UDT 又由注解回写 ⇒ **循环引用，不是独立证据** |
| g_gamefrm 全局条目 | 仅 `type=UIGameFrm`，无 size 字段 | 不构成尺寸证据 |
| 分配立即数 | `push 6E6Ch` 命中 **0**；全文 `6E6Ch` 16 处全是 `[+26E6Ch]` 他类偏移；无 28268 字面量 | **不存在该尺寸的分配点**（内嵌对象只有末三个指针成员是 new） |

可证下界：最后被访问的字段是 `+0x6E18`（`+0x6E10` 8 处、`+0x6E14` 20 处、`+0x6E18` 3 处）；`+0x6E94..+0x6EAC` 的访问属其它类（sub_45B990 / sub_46D140 / sub_46DF40 / sub_46F650）。下一独立全局 `0xDC10FC` = `g_gamefrm+0x712C`，与 0x6E6C 之间留 0x2C0 空隙。

**裁决**：28268 **不能声称已被验证**；可证 `size ≥ 0x6E1C (28188)`，`0x6E1C–0x6E6C` 这 80B 是估算/对齐余量。实现卡保留 28268 可以，但注解必须注明「尾部 80B 无证据」，且**不得**据此宣称「尺寸已定谳」。

## 4. 37 段逐段预期

规则：某段若落在上表某个子对象的 span 内，则它**不是 UIGameFrm 的缺员**，而是该子对象内部/双视图（预期 0B，由子对象类型覆盖）。「无法闭合」只给真正没有归属的段。

| # | 段 | 字节 | 预期 | 依据 |
|---|---|---|---|---|
| 1 | 0x4c–0xdc | 144 | 未闭合：UIGameFrm 自身头区，ctor 只清 0x44..0x6A 与 0xDC..0x102 | decomp memset 两段 |
| 2 | 0xe0–0xf4 | 20 | 未闭合（同上，0xDC..0x102 清零区内的无字段部分） | 同上 |
| 3 | 0xf8–0x100 | 8 | 未闭合 | 同上 |
| 4 | 0x108–0x148 | 64 | 0B：UICaption(96) 内部 | dtor 0x44A7F0 |
| 5 | 0x14c–0x164 | 24 | 0B：UICaption 内部（至 0x164） | 同上 |
| 6 | 0x168–0x198 | 48 | 0B：RoleCameraCtrl(76) 内部 | dtor 0x450AD0 |
| 7 | 0x19c–0x270 | 212 | 20B 属 RoleCameraCtrl 内部；192B（0x1B0–0x270）**未闭合** | 0x1B0–0x290 无写点 |
| 8 | 0x290–0x2d8 | 72 | 0B：复合体 X 头部（UIWnd 基 0x48 + 第二子对象头 0x10） | §2.1 |
| 9 | 0x2dc–0x2e0 | 4 | 0B：X 内部 | §2.1 |
| 10 | 0x2e4–0x300 | 28 | 0B：X 内部（跨 1208B UIListBox 起点 0x2E8） | §2.1 |
| 11 | 0x304–0x400 | 252 | 0B：X 内部（1208B UIListBox 体内） | §2.1 |
| 12 | 0x404–0x500 | 252 | 0B：同上 | §2.1 |
| 13 | 0x504–0x600 | 252 | 0B：同上 | §2.1 |
| 14 | 0x604–0x6d0 | 204 | 0B：同上 | §2.1 |
| 15 | 0x6d8–0x6fc | 36 | 0B：同上 | §2.1 |
| 16 | 0x6fd–0x730 | 51 | 0B：同上 | §2.1 |
| 17 | 0x734–0x8ac | 376 | 0B：0x734–0x7A0 UIListBox 尾；0x7A0–0x860 UITextArea(192) 内部；0x860–0x8AC 数组元素 1 内部 | §2.1 + ??_M |
| 18 | 0x8e0–0x900 | 32 | 0B：数组元素 1 内部（元素 0 从 0x860 起，352B 止 0x9C0） | ??_M(0x160×5) |
| 19 | 0x904–0x9b0 | 172 | 0B：数组元素 1 内部 | 同上 |
| 20 | 0x9b8–0xed4 | 1308 | 0B：跨元素 1 尾 / 元素 2–4 内部 | 同上 |
| 21 | 0xed8–0xef5 | 29 | 0B：元素 5 内部 | 同上 |
| 22 | 0xef8–0xf88 | 144 | 0B：0xEF8–0xF40 元素 5 内部；0xF40–0xF88 UISceneMap 内部 | 同上 + 0x450EB0 |
| 23 | 0xf8c–0x1160 | 468 | 0B：UISceneMap 内部 | dtor 0x450EB0 |
| 24 | 0x1168–0x13f0 | 648 | 0B：UISceneMap 内部（至 0x1394） | 同上 |
| 25 | 0x13f4–0x1680 | 652 | 0B：UITitle(9520, 0x1394–0x38C4) 内部 | dtor 0x44ACE0 |
| 26 | 0x1688–0x1910 | 648 | 0B：UITitle 内部 | 同上 |
| 27 | 0x1918–0x1ba0 | 648 | 0B：UITitle 内部 | 同上 |
| 28 | 0x1ba4–0x1e30 | 652 | 0B：UITitle 内部 | 同上 |
| 29 | 0x1e38–0x2870 | 2616 | 0B：UITitle 内部 | 同上 |
| 30 | 0x2874–0x287c | 8 | 0B：UITitle 内部 | 同上 |
| 31 | 0x2880–0x2b00 | 640 | 0B：UITitle 内部 | 同上 |
| 32 | 0x2b08–0x32c0 | 1976 | 0B：UITitle 内部 | 同上 |
| 33 | 0x32c4–0x38bc | 1528 | 0B：UITitle 内部 | 同上 |
| 34 | 0x38d4–0x4028 | 1876 | 0B：UIEmote[6] 内部（0x38D0–0x6E10） | ??_M(0x8E0×6) |
| 35 | 0x402c–0x42d0 | 676 | 0B：UIEmote[6] 内部 | 同上 |
| 36 | 0x42d4–0x6e10 | 11068 | 0B：UIEmote[6] 内部 | 同上 |
| 37 | 0x6e1c–0x6e6c | 80 | **未闭合**：类尾 80B，无任何访问点（§3） | 访问点普查 |

**预期残留总量（实现方应达到的量级）**：未闭合段 = #1(144) + #2(20) + #3(8) + #7 的 192 + #37(80) = **444B**；其余 27,472B 应被「七个子对象成员」覆盖（UICaption96 / RoleCameraCtrl76 / X1488 / 352B 数组 1760 / UISceneMap 1108 / UITitle 9520 / UIEmote[6] 13632）。

注：这不是要求实现方把这 27,472B 全部填成标量成员——**正相反**，正确形态是引入上表 7 个 typed 成员（其中 X 与 352B 数组需要新类），并把现有落在这些 span 内的标量成员**降级为 dual-view 注记或删除**（#8 的「保留视图」只对成员可见性成立，对洞计量应按 typed 子对象算 0B）。

## 5. 「预期 vs 实现」对照表（验收时逐行打勾）

| # | 检查点 | 预期 | 来源 |
|---|---|---|---|
| P1 | 0x290 成员类型 | 复合体 X，size **1488**，**不是** 72B UIListBox | §2.1 |
| P2 | 0x860 成员类型 | 352B 元素 ×5 的数组（stride 0x160），不是 5 个独立成员 | ??_M |
| P3 | 0x38D0 成员类型 | UIEmote[6]（2272×6=13632），不是 spread 标量 | ??_M |
| P4 | 0xF40 成员尺寸 | 1012 或 1108 之一，且注解写明二义与证据 | §2.2 |
| P5 | 0x104 / 0x164 / 0x1394 | 96 / 76 / 9520 typed 成员 | dtors |
| P6 | 0x6E14 / 0x6E18 | RoleStatePanel* / UITitle_YXXX* 指针（不是 int/char*） | Init new |
| P7 | 0x6E1C–0x6E6C | 若保留 28268，注解须注「尾部 80B 无证据」 | §3 |
| P8 | 洞计量 | 目标 ≤ ~444B（未闭合五段），且不把 X/数组/UITitle 内部算成洞 | §4 |

## 6. 实现可疑判据（3–5 条，命中即须回退或补证）

1. **0x290 仍按 72B 建模**（成员尺寸 72、或洞表里 0x290–0x2D8 仍计 72B）⇒ 与 §2.1 的 span 闭合矛盾。
2. **0x860 元素声明为 72B**（或 5 个成员总 stride ≠ 0x160）⇒ sizeof 与 `??_M(0x160,5)` 矛盾。
3. **0x38D0 仍是单个 `int m_aItemData`** 且 0x38D0–0x6E10 仍报洞 ⇒ 与 `??_M(0x8E0,6)` 矛盾（该区应被 UIEmote[6] 覆盖）。
4. **0x6E14 声明为 int/`m_nMode`** ⇒ 与 census `store=esi+0x6E14, size=176256, ctor=?InitUI@RoleStatePanel` 矛盾（4 字节装不下 176KB 对象，且 Init 明确 `new(0x2B080)` 后存该槽）。
5. **宣称「28268 已定谳」** ⇒ 无分配立即数、UDT 循环引用（§3），属未证断言。

## 7. 未决（实现方可反证，但不得静默忽略）

1. 0x1B0–0x290 的 224B：无 ctor/dtor/写点；候选是 UIGameFrm 自身成员（注解 0x19c–0x270 段已报洞），也可能是 0x290 复合体的前置填充——需 ctor 0x44F130 的完整写点普查。
2. 复合体 X 的**类名**：0x56B178 表归属未在注解登记；g_UIListBoxDlg 全局类型（UIListBox 72B）与 1488B 实测不符。
3. 0xF40：1012 vs 1108，96B 差是 pad 还是尾部成员，需该对象 ctor 的写点。
4. 352B 数组元素类：UIHeadDialog(352) 无 vtable/方法，UIDialog(72) 尺寸不符；类名无证据。
5. 0x6E10 指向对象（2864B）的类名：NavFaceLayer.json 16B 且无表，名称只是函数名沿用。
6. 尾部 80B（0x6E1C–0x6E6C）：无访问点，28268 属估算。

## 8. 只读自证

```
$ git status --short
?? docs/audit/2026-11-26-uigamefrm-expectation-baseline.md
（其余 M 项均非本卡：structs/{RoleStatePanel,ScreenEffectMgr,UIFrameContainer}.json、pipeline/gen/stages/stage5_fixup.py、README.md、data/status/* —— 属 #8/#9/#15 等在跑卡）

$ git diff --stat data/annotations/structs/UIGameFrm.json
（空）

$ ls docs/audit/ | grep uigamefrm
2026-11-26-uigamefrm-expectation-baseline.md
```

未运行 `python pipeline/cli.py *` 任何子命令；未写 `data/status/`、`asm/`、`pal3/src/`。
