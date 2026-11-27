# PropUI 落位预期基准（R7 首类 oracle）：尺寸三方对账 + ctor 建链 + 164B 差独立复算

- 任务：`#36` tsk_01M8CEFPKNH8DJ7HCKRHA4（只读；writeScope 仅 `docs/audit/`）
- 日期：2026-11-27
- 输入：`data/annotations/structs/PropUI.json`、`original/PAL3.exe.asm`、`data/status/struct_holes_20261125.json`、`data/status/probe_heap_alloc_census_20261126.json`
- 独立声明：本报告不复用 #17 的任何中间产物；#17 的「68+96」只当待证命题，下文的分解由本次独立复算得到。未读 #31/#32 的在途产物，未运行任何 `pipeline/cli.py` 子命令。

## §0 结论摘要

1. **真 `sizeof(PropUI)` = 28,892（0x70DC）**。三方对账：分配立即数 `push 70DCh` 两处一致；ctor `sub_46D140` 最高写 `[esi+70D8h]`（byte）⇒ 写界 0x70D9；注解 29,056（0x7180）虚高 164B。
2. **164 = 68 + 96，两笔性质不同**：68 = 注解最后两员越过真实对象末尾（`mb_OK@0x6FB8` 的 344B span 越界 52B + `mb_OKRc@0x7110` 整块 16B 在对象外）；96 = `binary_size` 比「最后成员末端 0x7120」又高出的一截尾填。两笔都是注解层形状错误，不是「某成员尺寸差一个数量级」。
3. **ctor 建链可逐段闭合到 0x70DC**：28 个构造点合计 10,408B + 对象间对齐间隙 308B（13 段）+ `st_Manager` 零填块 17,504B + 头 88B + 字段区 552B + 尾标量/标志 32B = 28,892B（逐笔见 §4）。
4. **两个实例点都是真持有者，不是「同尺寸别的对象」**：`UISceneFrm::InitGameUI` 存 `+0xCC0`、`CUtil::InitGameSystems` 存 `+0x6D4`，两处都走同一个 ctor `sub_46D140`。`+0x6D4` 的撞车反例是 `PAL3::HandleDeviceLost` 在该偏移写 float，说明「偏移」不能证明类型、ctor 身份才行。
5. **洞 18,652B 的主体不是 45 段碎片，而是一个建模口径问题**：其中 16,968B/21 段落在 `0x58–0x44B8`，根因是注解 `st_Manager` 只有 274B（0xF4），而 ctor 用 `rep stosd 0x4460` 把 `0x58–0x44B8` 整块零填。正确修法是「扩容 st_Manager 或改为内联 union」，不是逐段补洞。
6. **一个会影响落位的卡外发现**：ctor 首调 `sub_43DCD0`，该 ctor 写 `off_56AD20`（UIListBox 表）⇒ 二进制上 PropUI 的基类是 UIListBox；注解 `bases=[UIFrameWnd@0]` 缺证据（两者同为 72B，尺寸不炸但类型链错）。本报告只登记，不建议 R7 顺手改。

## §1 只读与口径声明

- 本卡只读：未改 `data/annotations/`、`data/status/`、`pal3/src/`；写面仅 `docs/audit/2026-11-27-propui-expectation-baseline.md`。
- 未运行 `python pipeline/cli.py` 的任何子命令（status/check/loop/probe/match 全未跑），引用的是 2026-11-26 已落盘产物（census mtime 22:12:22；alloc census 提交态）。
- 地址一律用 `original/PAL3.exe.asm` 的行号定位；函数号即 IDA 命名（`sub_XXXXXX`），类名按注解/函数名表引用并标注确定度。

## §2 复现命令与关键输出

```bash
# 1) 两处分配立即数 + 紧随其后的 ctor 调用
grep -n "push    70DCh" original/PAL3.exe.asm
grep -n "call    sub_46D140" original/PAL3.exe.asm
```
```
139327:                push    70DCh           ; Size
438693:                push    70DCh           ; Size
139338:                call    sub_46D140
438703:                call    sub_46D140
```

```bash
# 2) ctor 最高写点（写界）+ 写表
sed -n '163351,163363p;163376,163380p' original/PAL3.exe.asm
```
```
163362:                 mov     dword ptr [esi], offset off_56B688
163379:                 mov     byte ptr [esi+70D8h], 1
```
（`0x70D8+1 = 0x70D9` 是写界；到分配尺寸 0x70DC 还余 3B，是 4 字节对齐尾。）

```bash
# 3) 三方数字与 164 分解
python3 -c "print(hex(29056),hex(28892),hex(0x7110-0x70DC),hex(0x7120-0x70DC),hex(0x7180-0x7120),29056-28892)"
```
```
0x7180 0x70dc 0x34 0x44 0x60 164
```
（`0x34=52` 是 mb_OK 越界、`0x44=68 = 52+16`、`0x60=96` 是尾填、合计 164。）

```bash
# 4) 洞清单口径
python3 - <<'PY'
import json
d=json.load(open('data/status/struct_holes_20261125.json'))
c=[x for x in d['classes'] if x['cls']=='PropUI'][0]
print(c['size'],c['hole_bytes'],len(c['holes']))
PY
```
```
29056 18652 45
```

```bash
# 5) alloc census 两行（caller/store 口径）
python3 - <<'PY'
import json
d=json.load(open('data/status/probe_heap_alloc_census_20261126.json'))
for r in d['allocs']:
    if r['size']==28892: print(r)
PY
```
```
{'size': 28892, 'ctor': '?InitUI@PropUI@@QAEHXZ', 'store': 'esi+0x0CC0', 'caller': '?InitGameUI@UISceneFrm@@QAEXXZ', 'site': '0x45975e'}
{'size': 28892, 'ctor': '?InitUI@PropUI@@QAEHXZ', 'store': 'esi+0x6D4', 'caller': '?InitGameSystems@CUtil@@QAEHXZ', 'site': '0x523431'}
```

## §3 尺寸三方对账（①）

| 来源 | 值 | 证据 |
|---|---|---|
| 注解 `binary_size` | **29,056 = 0x7180** | `data/annotations/structs/PropUI.json`（95 员，全 `unverified`，`bases=[UIFrameWnd@0]`） |
| 分配立即数 | **28,892 = 0x70DC** | `asm:139327`、`asm:438693` 两处 `push 70DCh ; Size`，各接 `call ??2@YAPAXI@Z` |
| ctor 写界 | **0x70D9**（最高写 `[esi+70D8h]` 1B） | `sub_46D140`，`asm:163379` |
| 构造链闭合 | **0x70DC**（逐段求和，§4） | ctor/dtor 逐对象 span |
| **真值** | **28,892** | 三证一致：分配=写界上界=构造链闭合 |

**164B 的自己复算（不是照抄 #17）**

- 注解最后两员：`mb_OK`（`UIButton`，type 尺寸 344）@`0x6FB8` ⇒ 末端 `0x7110`；`mb_OKRc`（`tagRECT`，16）@`0x7110` ⇒ 末端 `0x7120`。
- `0x7120 − 0x70DC = 0x44 = 68`：这 68B 是「声明内容越过真实末尾」，可再拆为 `mb_OK` 越界 `0x7110−0x70DC=52` + `mb_OKRc` 整块 16。
- `0x7180 − 0x7120 = 0x60 = 96`：`binary_size` 比最后成员末端又高出 96B，注解里没有任何成员占它（洞清单最后一段 `0x7120–0x7180` 96B 即此）。
- `68 + 96 = 164 = 29,056 − 28,892` ✓。
- 交叉验证：洞清单里 `0x7120–0x7180` 是 96B 独立一段，正对应第二笔；第一笔 68B 不与洞重叠（洞只统计到 members 之间的空隙，越界成员本身不算洞）。

结论：**注解应改 `binary_size=28892` 并重建尾段；`mb_OK@0x6FB8` 与 `mb_OKRc@0x7110` 两个名字不能平移到新布局里**（`0x6FB8` 在真实对象中落在 `0x6EA4` 那个 344B 对象体内，见 §4）。

## §4 ctor 建链逐段 span 与闭合（②）

`sub_46D140`（注解函数名表记 `?InitUI@PropUI`，**该名不是 ctor 名**；体首 `call sub_43DCD0` 调基类 ctor、体尾写 `off_56B688`，是构造器）建链如下（偏移均为相对对象基址）：

| 区间 | 字节 | 内容 | 证据 |
|---|---:|---|---|
| 0x000–0x048 | 72 | 基类（`sub_43DCD0`，写 `off_56AD20`） | asm:163219 |
| 0x048–0x058 | 16 | 4 个 int：`0x48=0x320`、`0x4C=0x258`、`0x50=0x12C`、`0x54=0x190` | asm:163222–163226 |
| 0x058–0x44B8 | 17,504 | `st_Manager` 块（ctor `rep stosd 0x1118` = 0x4460 全零） | asm:163351–163363 |
| 0x44B8–0x46E0 | 552 | 指针/缓冲/标量区（`p_DealData`、`buf[256]`、`remarkbuf[256]`、各 int） | 注解成员 + dtor 释放 `[0x46C0]/[0x46C4]`（asm:163446–163463） |
| 0x46E0–0x4778 | 152 | `sub_4422E0` 容器 | asm:163250 |
| 0x4778–0x47CC | 84 | `sub_43D830`（写 `off_56ACFC`） | asm:163253、96060 附近 |
| 0x47CC–0x4864 | 152 | `sub_4422E0` 容器 | asm:163256 |
| 0x4864–0x4874 | 16 | 对齐间隙 | — |
| 0x4874–0x49CC | 344 | `sub_43A770` 344B 控件 | asm:163259 |
| 0x49CC–0x4A70 | 164 | `sub_43A160` 164B 控件 | asm:163262 |
| 0x4A70–0x4D68 | 760 | `??_L(0x98,5)` = 5×152 容器 | asm:163263–163270 |
| 0x4D68–0x4DD0 | 104 | 对齐间隙 | — |
| 0x4DD0–0x5328 | 1,368 | `sub_4A12F0`（UIRoleDialog 尺寸吻合） | asm:163271–163273 |
| 0x5328–0x545C | 308 | `sub_439030`（308B 控件） | asm:163274–163276 |
| 0x545C–0x54F4 | 152 | `sub_4422E0` | asm:163277–163279 |
| 0x54F4–0x5504 | 16 | 对齐间隙 | — |
| 0x5504–0x559C | 152 | `sub_4422E0` | asm:163280–163282 |
| 0x559C–0x5634 | 152 | `sub_4422E0` | asm:163283–163285 |
| 0x5634–0x56CC | 152 | `sub_4422E0` | asm:163286–163288 |
| 0x56CC–0x5764 | 152 | `sub_4422E0` | asm:163289–163291 |
| 0x5764–0x5774 | 16 | 对齐间隙 | — |
| 0x5774–0x580C | 152 | `sub_4422E0` | asm:163292–163294 |
| 0x580C–0x5FC4 | 1,976 | `??_L(0x98,13)` = 13×152 容器 | asm:163295–163302 |
| 0x5FC4–0x605C | 152 | `sub_4422E0` | asm:163303–163305 |
| 0x605C–0x60F4 | 152 | `sub_4422E0` | asm:163306–163308 |
| 0x60F4–0x6104 | 16 | 对齐间隙 | — |
| 0x6104–0x65BC | 1,208 | `sub_43DFC0`（= 1208B 类 `cls_43dfc0`） | asm:163309–163311 |
| 0x65BC–0x65CC | 16 | 对齐间隙 | — |
| 0x65CC–0x68A8 | 732 | 复合体：头 32 + `[+0x20]` 344B + `[+0x178]` 344B + 12B 标量（`0x2D0=0x20`、`0x2D4=0x10`、`0x2D8/0x2DC=0`） | asm:163312–163323；dtor asm:163497 起 |
| 0x68A8–0x68B8 | 16 | 对齐间隙 | — |
| 0x68B8–0x6950 | 152 | `sub_4422E0` | asm:163324–163326 |
| 0x6950–0x69E8 | 152 | `sub_4422E0` | asm:163327–163329 |
| 0x69E8–0x6A80 | 152 | `sub_4422E0` | asm:163330–163332 |
| 0x6A80–0x6B18 | 152 | `sub_4422E0` | asm:163333–163335 |
| 0x6B18–0x6B28 | 16 | 对齐间隙 | — |
| 0x6B28–0x6BC0 | 152 | `sub_4422E0` | asm:163336–163338 |
| 0x6BC0–0x6BD0 | 16 | 对齐间隙 | — |
| 0x6BD0–0x6D28 | 344 | `sub_43A770` 344B 控件 | asm:163339–163341 |
| 0x6D28–0x6D3C | 20 | 对齐间隙 | — |
| 0x6D3C–0x6E94 | 344 | `sub_43A770` 344B 控件 | asm:163342–163344 |
| 0x6E94–0x6EA4 | 16 | 对齐间隙 | — |
| 0x6EA4–0x6FFC | 344 | `sub_43A770` 344B 控件 | asm:163345–163347 |
| 0x6FFC–0x701C | 32 | 对齐间隙 | — |
| 0x701C–0x70B4 | 152 | `sub_4422E0` | asm:163348–163350 |
| 0x70B4–0x70D0 | 28 | 尾标量：`0x70B4/0x70B8/0x70BC=0`、`0x70C0/0x70C1=0`、`0x70C4=0`、`0x70C8=1.0f`、`0x70CC=0` | asm:163354–163361 |
| 0x70D0–0x70D8 | 8 | 未写（无构造、无字段） | — |
| 0x70D8–0x70D9 | 1 | `[0x70D8]=1`（ctor 最后一条写） | asm:163379 |
| 0x70D9–0x70DC | 3 | 4 字节对齐尾 | — |

**闭合算式**：28 个构造对象 10,408B + 对齐间隙 308B（13 段）+ `st_Manager` 17,504B + 头 88B（0x48+16）+ 字段区 552B + 尾标量/标志 32B（28+1+3）= **28,892B = 0x70DC** ✓。

**注解尾段的问题（与 span 冲突的具体位置）**：`0x6BD0` 起 ctor 是 `344 + 344 + 344 + 152 + 标量`，注解却是 6 个 `UIStatic`(152)+1 个 `UIButton`(344)+rect，且最后一个 `UIButton@0x6FB8` 落在真对象 `0x6EA4–0x6FFC` 的体内（`0x6FB8−0x6EA4=0x114`）。⇒ 尾段必须按对象簇重建，不能按名字平移。

## §5 两个实例点与真持有者（③）

| 实例点 | 持有者类 | 槽位 | 现场证据 |
|---|---|---|---|
| `sub_4593C0`（= `UISceneFrm::InitGameUI`） | **UISceneFrm**（3,288B = 0xCD8） | `+0x0CC0` | `asm:139348 mov [esi+0CC0h], eax`；同函数 `+0xCBC` 存 SaleUI（0x19DB8）、`+0xCC4` 存 124,268B 类；`sub_44F8D0` case2 先 `new(0xCD8)`+`sub_4590D0`（UISceneFrm ctor）再 `call sub_4593C0`（asm:123270–123289） |
| `sub_5232B0`（= `CUtil::InitGameSystems`） | **CUtil**（1,772B） | `+0x6D4` | `asm:438714 mov [esi+6D4h], eax`；同函数 `+0x6C8` 存 CScreenMode（0x1578=5,496）、`+0x6CC` 存 672,040B 类、`+0x6D0` 存 124,268B 类；census 行 `caller=?InitGameSystems@CUtil` |

**判定：两处都是真持有者（同一类的两个实例），不是「另一个是同尺寸别的对象」**。依据是 ctor 身份而不是尺寸：两处都 `push 70DCh → call ??2 → call sub_46D140`，ctor 地址相同。

**#34 说的 [0x6D4] 撞车反例已定位**：`sub_527C30`（注解 `PAL3::HandleDeviceLost`）在 `asm:445150–445160` 一带写 `[esi+6D8h]=3F400000h/3F800000h`、`[esi+6D4h]=eax`（float）。⇒ 同一偏移在别的类里是 float 字段，证明「偏移撞车」不能反证类型，但也不能正证；正证只能用 ctor/写表。

## §6 写表 off_56B688 核对（④）

- ctor `asm:163362`、dtor 实现 `sub_46D4E0` `asm:163445` 各写一次 `mov dword ptr [esi], offset off_56B688`。
- `.rdata` `asm:536446` 起 7 槽（`asm:536446–536453`）：

| slot | 地址 | 注解名 |
|---|---|---|
| 0 | 0x445E70 | （ShowClipped 族） |
| 1 | 0x43DDF0 | Render |
| 2 | 0x46F620 | Update |
| 3 | 0x43DE40 | HideAll |
| 4 | 0x445B90 | Create |
| 5 | 0x46D4C0 | `_scalar_dtor_D4C0`（deleting dtor；`sub_46D4C0` 体 `call sub_46D4E0` + 条件 `operator delete`） |
| 6 | 0x46F650 | OnMessage |

- XREF 核对：`off_56B688` 的 DATA XREF 记 `sub_46D140+304`（即 asm:163362 处），与 ctor 写点一致；`0x56B69C`（slot5）XREF `sub_46D4C0`，与 deleting dtor 一致。
- 与 `PropUI.json` 的 `vtables[0].addr=0x0056b688` 完全对上（槽数 7、地址逐一相同）。

## §7 洞 18,652B 分解（⑤）

### 7.1 分类汇总（census 原样 45 段，求和 18,652B）

| 类别 | 字节 | 段数 | 性质 |
|---|---:|---:|---|
| `st_Manager` 块内（0x58–0x44B8） | **16,968** | 21 | 建模口径问题：注解 `st_Manager` 仅 274B，ctor 零填 0x4460 |
| 构造对象内部 / 跨对象段（注解未建模） | **1,588** | 23 | 对象 span 是 A 级（ctor 构造），成员级无证据；其中 0x64BC–0x6950 一段 1,172B 跨 0x6104 对象尾、0x68A8 对齐间隙与 0x68B8 容器 |
| 越出真实对象（0x7120–0x7180） | 96 | 1 | 注解 `binary_size` 尾填，改尺寸后消失 |
| **合计** | **18,652** | 45 | = census `hole_bytes` |

### 7.2 逐段（census 原样 23 段 + 两组汇总行）

| 区间 | 字节 | 预期 / 真未闭合理由 |
|---|---:|---|
| 0x014c–0x44b8 内 21 段（详见 §7.3 合计数） | 16,968 | `st_Manager` 内部：ctor 已整块零填，无逐段成员证据；应扩容/内联，不补洞 |
| 0x477c–0x4780 | 4 | `sub_43D830` 对象内部（84B span A 级），成员无证据 |
| 0x490c–0x4914 | 8 | 344B 控件内部（span A 级） |
| 0x49ac–0x49b4 | 8 | 344B 控件内部 |
| 0x4a4c–0x4a54 | 8 | 164B 控件内部 |
| 0x4aec–0x4af4 | 8 | 5×152 容器内部 |
| 0x4ff8–0x5020 | 40 | 1,368B 对象内部 |
| 0x5590–0x559c | 12 | 152 容器内部 |
| 0x55a0–0x55f0 | 80 | 152 容器内部 |
| 0x57bc–0x57c4 | 8 | 152 容器内部 |
| 0x586c–0x5874 | 8 | 13×152 容器内部 |
| 0x590c–0x5914 | 8 | 13×152 容器内部 |
| 0x59bc–0x59c4 | 8 | 13×152 容器内部 |
| 0x6214–0x6284 | 112 | 1,208B 对象内部 |
| 0x631c–0x6324 | 8 | 1,208B 对象内部 |
| 0x63bc–0x63c4 | 8 | 1,208B 对象内部 |
| 0x645c–0x6464 | 8 | 1,208B 对象内部 |
| 0x64bc–0x6950 | 1,172 | 跨三段：0x6104 对象尾段 + 0x68A8 对齐间隙 + 0x68B8 容器头；census 按注解成员间空隙合并成一段，成员级无证据 |
| 0x6954–0x697c | 40 | 152 容器内部 |
| 0x6d10–0x6d18 | 8 | 344B 控件内部 |
| 0x6db0–0x6db8 | 8 | 344B 控件内部 |
| 0x6e50–0x6e58 | 8 | 344B 控件内部 |
| 0x6ef0–0x6ef8 | 8 | 344B 控件内部 |
| 0x6fa0–0x6fa8 | 8 | 344B 控件内部 |
| 0x7120–0x7180 | 96 | 越界：注解虚高，改 `binary_size=28892` 后消失 |

### 7.3 `st_Manager` 内 21 段明细（合计 16,968B）

0x14c(24)、0x16c(12)、0x17c(20)、0x194(96)、0x1fc(48)、0x230(40)、0x25c(4)、0x2a4(44)、0x2e4(60)、0x324(280)、0x440(76)、0x494(208)、0x5a4(704)、0x8a4(2,164)、0x111c(9,516)、0x364c(4)、0x3654(80)、0x36a8(1,512)、0x3c94(884)、0x400c(708)、0x42d4(484)。

**根因**：注解 `st_Manager` 的 `binary_size=244`（0xF4），2 个成员（`m_Type`/`m_Dicker` 各 1B）；`0x58+0xF4=0x14C`，正是第一个洞的起点。ctor `rep stosd 0x1118`（`asm:163351–163363`，0x1118×4=0x4460）把 `0x58–0x44B8` 整块零填，与 `p_DealData@0x44B8` 严丝合缝。⇒ 这两万个字节不是 21 个独立洞，而是**一个 0x4460 的块没有建模**。

**修法二选一（建议 a，交评审定）**：
- (a) 把 `0x58` 改为内联 union：`union { st_Manager m_PropData; struct { ...现 21 个 ida_gap 成员... } }`，块尺寸写 0x4460 —— 成员名保留、洞归零，符合项目 inline union 语法与 overlap 规则；
- (b) `st_Manager.binary_size` 直接改 0x4460，同时把 21 个成员迁进 `st_Manager.json` —— 跨文件改动更大，且这些成员目前只被 PropUI 代码按 `this+off` 访问。

## §8 验收检查点（实现交上来时逐条对）

1. **`binary_size` 必须是 28,892（0x70DC）**，不能是 29,056；若生成树里仍是 `0x7180`，直接判未落位。
2. **vtable 必须恰为 0x56B688 的 7 槽**，逐槽等于 §6 表；slot5 必须是 `sub_46D4C0`（deleting dtor），slot1/2/6 分别是 `0x43DDF0/0x46F620/0x46F650`。
3. **ctor 写界不得越过 0x70D8**：实现里若出现对 `+0x70DC` 及以上的字段写，说明尺寸或成员偏移错。
4. **建链锚点必须全中**：`0x4DD0`、`0x5328`、`0x545C`、`0x6104`、`0x65CC(+0x20/+0x178)`、`0x68B8`、`0x6BD0`、`0x6D3C`、`0x6EA4`、`0x701C` 这十组对象起点，以及 `0x58` 的 0x4460 块；缺一个就是段表没落地。
5. **尾段不得平移到 `mb_OK@0x6FB8`**：该偏移在真实对象里落在 344B 控件体内；`mb_OK` 若保留名字，必须落到 `0x6EA4` 那组控件或其内部（需要成员级证据才能定名，否则按「344B 控件」留白）。
6. **两个实例点都要有 owner 注解**：`UISceneFrm+0xCC0`、`CUtil+0x6D4` 均应标成 `PropUI*`；只标一个说明实例面没做完。
7. **`st_Manager` 洞的处理方式要对**：若实现用「逐段补 byte 数」把 18,652B 消掉、而 `st_Manager` 仍是 244B，判为假闭合——正确形态是 union/内联或 st_Manager 扩容 + 成员归位。

## §9 未决（不影响本卡结论，但影响实施细节）

1. **基类链**：二进制 ctor 调 `sub_43DCD0`（写 UIListBox 表 `0x56AD20`）⇒ 基类应为 UIListBox；注解 `bases=[UIFrameWnd@0]` 与 `vtables[0].base=UIWnd` 三处口径不一。改 bases 需另一轮证据（vtable 槽继承比对），本轮只登记。
2. **子对象类名**：`sub_43A770` 的 span 344 与注解 `NameSys`(280) 不符；`sub_43A160` span 164 与 `PalScript`(2,176) 不符（尺寸恰等于 `UIAnimateCtrl`164）；`sub_439030` span 308 与 `UIProgressBar`(244) 不符（尺寸恰等于 `UI3DCtrl`308）；`sub_43D830` span 84 与 `UI3DCtrl`(308) 不符（恰等于 `UIFlexBar`84）。span 是 A 级，类名需 IDA UDT/ctor 名另证。
3. **尾标量语义**：`0x70B4/0x70B8/0x70BC/0x70C0/0x70C1/0x70C4/0x70C8(=1.0f)/0x70CC` 的字段名无证据（注解把它们归到 `m_ctrlTime`/`m_bCanUpdate1/2` 一带，但偏移对不上）。
4. **`0x70D0–0x70D8` 8B 与 `0x70D9–0x70DC` 3B**：无写点、无成员，判为对齐尾；若实施卡给出成员名，需要额外证据。
5. **`0x44B8–0x46E0` 字段区**：`buf[256]/remarkbuf[256]` 的尺寸来自 decomp `lstrlenA` 语义，属 B 级；`m_SelNum/m_ListSelNum/m_MaxNum` 指针真正指向的数组长度未核。
6. **两处实例的生命周期**：UISceneFrm 与 CUtil 各持一个 PropUI，谁先析构、是否重复创建（ShowCategory 切换时是否复用）未追；本卡只证「两个实例、同一 ctor」。

## §10 只读自证

- `git status --short` 本卡只新增 `?? docs/audit/`（报告文件）；未改 `data/annotations/structs/PropUI.json`（`git diff` 空）、未改 `data/status/`、未改 `pal3/src/`。
- 本卡未执行任何 `pipeline/cli.py` 子命令；未触碰 IDB/IDB 锁；`original/PAL3.exe.asm` 仅只读打开。
- `git status --short docs/audit` 下两个 `M` 不是本卡改动：`2026-11-27-round-readout-reconciliation.md` 是 #33 验收后按白砚注记改的两处措辞（mtime 01:05:50，3/3 行）；`2026-11-26-r6-decision-brief.md` 非本卡所写（mtime 01:39:40，164/1 行，属他人）。本卡只新增 `?? docs/audit/2026-11-27-propui-expectation-baseline.md`。
- 所有数字均来自本报告的 §2 命令或 §4 的 span 表；`18,652 = 16,968+1,588+96`、`28,892 = 10,408+308+17,504+88+552+32` 两式可在报告内逐项相加复核。
