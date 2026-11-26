# UITitle_JDHY 落位验收 oracle（独立于实现方）

- 卡：#25 `tsk_01M8C7XSRZMJP27AQN8JG8`（观澜，只读）
- 生成时间：2026-11-26 23:4x（Asia/Shanghai）
- 用途：#23（玄策，UITitle_JDHY 洞区落位）的验收对照基准——本卡在实现方产物之外独立算出「应该是多少」，供白砚在验收时逐项比对。

## 0 独立于实现方声明

- 本卡开工前未读 #23 的任何文档、提交或中间产物；全文不引用其数字。
- 依据只有四类：`original/PAL3.exe.asm`（IDA 文本清单，22.8MB）、`asm/pal3/decomp/UITitle_JDHY_*.json`、`data/annotations/structs/*.json`（现版，HEAD 状态）、`data/status/` 已提交产物（census）。
- `docs/ui-inventory/2026-11-26-r6-ui-evidence.md`（#17，已验收）只作为「待验命题」来源（Note_Item[36]@0x262C8），其结论在本文由 asm 独立重算，不直接采信。
- 未改任何 annotation / 生成树 / 基线；未跑管线（只 grep/sed/python 只读）。

## 1 复现命令与原样输出

```bash
# 1) 工厂站点：唯一的 0x46EB8 分配，紧跟 ctor 0x4B01D0
sed -n '240584,240600p' original/PAL3.exe.asm
```

```
                push    46EB8h          ; Size   ; ← asm:240584
                mov     [esp+68h+var_4], edi
                mov     [esi+2AFCCh], eax
                call    ??2@YAPAXI@Z    ; operator new(uint)
                add     esp, 4
                mov     [esp+64h+var_54], eax
                cmp     eax, ebx
                mov     [esp+64h+var_4], 6
                jz      short loc_4A46E5
                mov     ecx, eax
                call    sub_4B01D0
```

```bash
# 2) 全 asm 里 377,700(0x5C364) 与 290,488(0x46EB8) 的字面量出现次数
grep -c "5C364h" original/PAL3.exe.asm    # -> 0
grep -c "46EB8h" original/PAL3.exe.asm    # -> 1
```

```bash
# 3) ctor 0x4B01D0 的结构（成员对象逐个 lea ecx）
awk 'NR>=257244 && NR<=257424 {printf "%d\t%s\n", NR, $0}' original/PAL3.exe.asm \
  | grep -E 'lea +(ecx|eax|edx), \[esi\+|push +(0DE8h|24h|80h|248h)'
```

关键行原样：

```
257266  lea ecx, [esi+170h]
257273  lea ecx, [esi+208h]
257276  lea ecx, [esi+2A0h]
257279  lea ecx, [esi+338h]
257282  lea ecx, [esi+3D0h]
257285  lea ecx, [esi+468h]
257288  lea ecx, [esi+500h]      … 共 9 个，步长 0x158，到 0xFC0
257315  lea ecx, [esi+1118h]
257318  lea ecx, [esi+11C0h]
257322  lea ecx, [esi+1258h]
257326  push 80h                 ; 数组1 count=128
257327  lea eax, [esi+12F0h]
257328  push 248h                ; 元素 0x248
257363  push 24h                 ; 数组3 count=36
257364  lea edx, [esi+262C8h]
257365  push 0DE8h               ; 元素 3560
257369  lea ecx, [esi+45768h]
257372  lea ecx, [esi+458C0h]
257390  lea ecx, [esi+45EB0h]
257399  lea ecx, [esi+46408h]
257402  lea ecx, [esi+46960h]
```

```bash
# 4) dtor 0x4B0540 里同一批成员的析构（含数组3的 ??_M）
awk 'NR>=257424 && NR<=257690 {printf "%d\t%s\n", NR, $0}' original/PAL3.exe.asm \
  | grep -E 'lea +(ecx|eax|edx), \[esi\+|push +(0DE8h|24h)|call +\?\?_M'
```

关键行原样：

```
257509  push 24h                 ; count=36
257510  lea eax, [esi+262C8h]
257511  push 0DE8h               ; 元素 3560
257514  call ??_M@YGXPAXIHP6EX0@Z@Z ; eh vector destructor iterator
257478  lea ecx, [esi+46960h]    ; 最后一个成员对象
257481  lea ecx, [esi+46408h]
257484  lea ecx, [esi+45EB0h]
…
257586  lea ecx, [esi+468h]      ; 与 ctor 的 6 个 0x98 对象一一对应
257601  lea ecx, [esi+170h]
```

```bash
# 5) 尺寸算术（可复算）
python3 - <<'PY'
alloc=0x46EB8; ann=377700
print(alloc, ann, ann-alloc, hex(ann-alloc))
print('6 控制', [hex(0x170+i*0x98) for i in range(6)])
print('9 按钮', [hex(0x500+i*0x158) for i in range(9)])
print('数组3 end', hex(0x262C8+36*0xDE8))
print('最后对象 end', hex(0x46960+0x558))
print('旧布局 99 元 end', hex(0x634+99*0xDE8))
PY
```

输出：

```
290488 377700 87212 0x154ac
6 控制 ['0x170','0x208','0x2a0','0x338','0x3d0','0x468']
9 按钮 ['0x500','0x658','0x7b0','0x908','0xa60','0xbb8','0xd10','0xe68','0xfc0']
数组3 end 0x45768
最后对象 end 0x46eb8
旧布局 99 元 end 0x566ec
```

## 2 尺寸裁决：290,488 是真值，377,700 是注解虚高

三条独立证据（互相闭合）：

### 2.1 工厂 / operator new 站点（A 级）
`push 46EB8h`（asm:240584）→ `operator new` → `mov ecx,eax; call sub_4B01D0`（asm:240594）→ 结果存 `[esi+2AFD0h]`；census 同一行：

```json
{"size":290488,"ctor":"?DestroyPages@UITitle_JDHY@@QAEHXZ","store":"esi+0x2AFD0","caller":"?Init@EquipUI@@QAEXXZ","site":"0x4a46c4"}
```

`sub_4B01D0` 在函数尾写 `mov dword ptr [esi], offset off_56F33C`（asm:257407；dtor 同址写 257477），`0x0056F33C` 正是 `UITitle_JDHY.json` 的 vtable 地址 ⇒ 被 new 出来的对象就是 UITitle_JDHY，分配尺寸 290,488。

### 2.2 类内数组的 `??_M` 压栈尺寸（A 级）
dtor 对 Note_Item 数组压 `0DE8h`/`24h`/基址 `0x262C8h`（asm:257509–257514），ctor 对同一数组压同样的三元组（asm:257363–257368）。该数组止于 `0x262C8+36*0xDE8=0x45768`，其后仍是本类成员（asm:257369 起继续构造）⇒ 类至少延伸到 `0x46EB8`，与 377,700 不相容。

### 2.3 新对象 span（A 级）
ctor 最后三个对象在 `0x45EB0`/`0x46408`/`0x46960`（asm:257390/257399/257402），每个 0x558（1368B，步长即证据）；最后一个对象尾部正好 `0x46960+0x558=0x46EB8` = 分配尺寸，且 ctor 在 `0x46EB8` 之后无任何写点（最后的写是 `[esi+45EA8h]=0`，asm:257413）。dtor 同样从 `0x46960` 开始析构（asm:257478），之后不再有成员。

### 2.4 反证
全 asm 搜 `5C364h`（377,700）**0 命中**；`probe_heap_alloc_census_20261126.json` 亦无 377,700 行。377,700 在二进制中没有对应分配，来源未决（疑旧版布局/他类尺寸被套用）。

**裁决：`binary_size=290,488`（0x46EB8）；现注解 377,700 应收缩 87,212B（0x154AC）。**

## 3 Note_Item[36]@0x262C8 独立复核

- 起点：asm:257364 `lea edx,[esi+262C8h]`（ctor）；asm:257510 同址（dtor）。
- 元素：`push 0DE8h`=3,560（asm:257365/257511），与 `data/annotations/structs/Note_Item.json` 的 `binary_size=3560` 一致。
- 数量：`push 24h`=36（asm:257363/257509）。
- 预期 span：`36×0xDE8=0x1F4A0=128,160`，`0x262C8+0x1F4A0=0x45768`；而 `0x45768` 处紧接着构造下一个成员对象（asm:257369 `lea ecx,[esi+45768h]`）⇒ 数组末端与下一成员起点**逐字节闭合**，无洞。
- 与现注解对照：现注解 `m_NoteItem` @0x634、`Note_Item[99]`，`99×0xDE8` 从 0x634 起止于 `0x566EC` —— 这正好是 census 里 16,632B 洞的起点（见 §4 第6段）。**99 与 0x634 均无 asm 支持**。

**裁决：数组=36 元素、起点 0x262C8、stride 3,560、末端 0x45768。现注解的 0x634/99 应整体替换。**

## 4 14 段洞逐段预期

现 census（`data/status/struct_holes_20261125.json`，mtime 22:12:22）记 14 段/19,396B。逐段如下（「预期」指按真布局修正后该段应是什么）：

| # | 段（起–止） | 账面 | 预期 | 依据 |
|---|---|---|---|---|
| 1 | 0x1f0–0x1f8 | 8B | **0B**：属 UIFrameContainer@0x170 的尾部字段（0x170+0x98=0x208） | ctor 257266 / dtor 257601；UIFrameContainer size=152 |
| 2 | 0x290–0x298 | 8B | **0B**：属 @0x208 尾部（+0x98=0x2A0） | ctor 257273 / dtor 257598 |
| 3 | 0x330–0x338 | 8B | **0B**：属 @0x2A0 尾部（+0x98=0x338） | ctor 257276 / dtor 257595 |
| 4 | 0x3d0–0x3d8 | 8B | **0B**：属 @0x3D0 头部（该对象 0x3D0–0x468） | ctor 257282 / dtor 257589 |
| 5 | 0x470–0x478 | 8B | **0B**：属 @0x468（0x468–0x500） | ctor 257285 / dtor 257586 |
| 6 | 0x566ec–0x5a7e4 | 16,632B | **0B / 类外**：这是「0x634+99×0xDE8」的假末端；真相是数组在 0x262C8 只有 36 个元素、止于 0x45768，0x566EC 已超出真类末 0x46EB8 | 240584 vs 257363–257365 |
| 7 | 0x5a87c–0x5a884 | 8B | **0B / 类外**：随 99 元布局推出的假成员（0x5a7e4 起 0xA0 步进） | 同上 |
| 8 | 0x5a91c–0x5a924 | 8B | **0B / 类外** | 同上 |
| 9 | 0x5a9bc–0x5a9c4 | 8B | **0B / 类外** | 同上 |
| 10 | 0x5aa5c–0x5aa64 | 8B | **0B / 类外** | 同上 |
| 11 | 0x5aafc–0x5ab04 | 8B | **0B / 类外**：`m_pbPage UIPushButton[10]`（10×248=0x9B0）的假末端 | 同上 |
| 12 | 0x5b4b4–0x5b4dc | 40B | **0B / 类外**：假 UIPushButton 数组后的假 pad | 同上 |
| 13 | 0x5b63c–0x5b64c | 16B | **0B / 类外**：假 int 组（m_CurScrollPos..）前的假对齐 | 同上 |
| 14 | 0x5b920–0x5c364 | 2,628B | **0B / 类外**：size 虚高 87,212B 的尾部余量 | 同上 |

- 第 1–5 段全部是 **0xA0 步进 vs 真 0x98 步进** 的产物：注解把 6 个 152B 容器按 160B 排布，每段错出 8B；真偏移是 0x170/0x208/0x2A0/0x338/0x3D0/0x468（第 3 个恰好在 0x338 重合，所以第 3 段仍落在真对象边界上）。
- 第 6–14 段全部落在真类末 0x46EB8 之外，**不是「缺证据的洞」，而是尺寸错误的账面残影**。正确处置是收缩 size + 删除相应成员，不是补成员/补类型。

### 4.1 修正后仍会存在的未知块（oracle 预警，勿当实现缺陷）
- `0x158–0x170`（24B）：ctor 只写 `0x168`(byte 0) 与 `0x16C`(dword 0)，`0x158–0x168` 16B 无写点；而第一个 152B 容器从 0x170 开始。修正偏移后此处会成为新洞（或需要一个新的 ≤24B 小结构）。
- `0x25AF0–0x25B7C`（140B）：数组2（0x136F0，128×0x248）止于 0x25AF0，下一成员 0x25B7C 才开始，中间 140B 无对象构造。
- 预期修正后洞面 ≈ **164B（2 段）** 是「诚实残留」，不是 0；若 #23 报出更小的洞面但没解释这两处，需追问它们是哪来的结构。

## 5 预期 vs 实现可对照表

字段含义：offset/长度/类型倾向/命名形/证据等级（A=asm 直接可证，B=尺寸+构造闭合，C=现注解沿用未复核）。

| 偏移 | 长度 | 类型倾向 | 命名形（建议） | 等级 | 依据 |
|---|---|---|---|---|---|
| 0x0 | 0x48 | 基类 UIListBox(72B)（现注解写 UIFrameWnd，二者同布局） | — | A | ctor 首调 sub_43DCD0（asm:257264） |
| 0x48 | 0x10 | tagRECT | 语义名（rc） | C | 现注解，无 asm 写点 |
| 0x58 | 0x100 | 缓冲区；首 8B 被写成 800/600 | 语义名 | A(首8B)/C(余) | ctor `[58]=320h, [5C]=258h` |
| 0x158 | 0x18 | 未知小结构（0x168 byte=0、0x16C dword=0） | 待定名 | B/C | ctor 写点 |
| 0x170 | 0x98 | UIFrameContainer（vtable 0x56ADD0，size152） | 语义名 | A | ctor 257266 / dtor 257601 |
| 0x208 | 0x98 | 同上 | 语义名 | A | 257273 / 257598 |
| 0x2A0 | 0x98 | 同上 | 语义名 | A | 257276 / 257595 |
| 0x338 | 0x98 | 同上 | 语义名 | A | 257279 / 257592 |
| 0x3D0 | 0x98 | 同上 | 语义名 | A | 257282 / 257589 |
| 0x468 | 0x98 | 同上 | 语义名 | A | 257285 / 257586 |
| 0x500…0xFC0 | 9×0x158 | 344B 尺寸族（与 UIButton 同尺寸；ctor sub_43A770 写 vtable 0x56AC70，该 vtable 在注解里**无类登记**） | 语义名 | A | ctor 257288–257312 / dtor 257559–257583 |
| 0x1118 | 0xA8 | 未定（UIFrameContainer/UIButton 之间尺寸） | 语义名 | B | 257315 / 257556，下一对象 0x11C0 |
| 0x11C0 | 0x98 | UIFrameContainer 尺寸 | 语义名 | B | 257318 |
| 0x1258 | 0x98 | 同上 | 语义名 | B | 257322 |
| 0x12F0 | 128×0x248 | 数组（元素 584B） | 语义名 | A | ctor 257326–257331 |
| 0x136F0 | 128×0x248 | 数组（元素 584B，止 0x25AF0） | 语义名 | A | ctor 257334–257339 |
| 0x25B7C | 0x98 | UIFrameContainer 尺寸 | 语义名 | B | 257340 |
| 0x25C14 | 0x98 | 同上 | 语义名 | B | 257343 |
| 0x25CAC | 0xF8 | UIPushButton 尺寸（248B） | 语义名 | B | 257346 |
| 0x25DA4 | 0xF8 | 同上 | 语义名 | B | 257349 |
| 0x25E9C/0x25FF4/0x2614C | 3×0x158 | 344B 尺寸族（同上 vtable 0x56AC70） | 语义名 | B | 257352–257358 |
| 0x262A4 | 0x24 | 零填充（`rep stosd` 9 dword） | 无成员建议 | A | 257405–257414 |
| 0x262C8 | 36×0xDE8 | Note_Item（3560B） | m_NoteItem | A | 257363–257368 / 257509–257514 |
| 0x45768 | 0x158 | 344B 尺寸族（同上 vtable 0x56AC70） | 语义名 | B | 257369 |
| 0x458C0 | 0x158 | 同上（344B/0x56AC70） | 语义名 | B | 257372 |
| 0x45A28/0x45B40/0x45C50 | ≈0x110–0x118 | 未定小对象 | 语义名 | B | 257375–257381 |
| 0x45D60/0x45DF8 | 2×0x98 | UIFrameContainer 尺寸 | 语义名 | B | 257384/257387 |
| 0x45EB0/0x46408/0x46960 | 3×0x558 | 1368B 对象（ctor sub_4A12F0） | 语义名 | A | 257390/257399/257402；末端=0x46EB8 |
| 0x46EB8 | — | **类末** | — | A | 分配尺寸 + 最后对象末端 |

## 6 「若实现给出 X 而本卡预期 Y，则实现可疑」判据（5 条）

1. **尺寸**：若 `binary_size` 不是 290,488，或类末不是 0x46EB8（例如仍接近 377,700），可疑。可复核：`grep -c 46EB8h` 为 1、`grep -c 5C364h` 为 0。
2. **数组起点/数量/stride**：若 `m_NoteItem` 起点不是 0x262C8、数量不是 36、stride 不是 0xDE8（或末端不是 0x45768），可疑。三者同时出现在 ctor 的 `??_L`(257363–257368) 与 dtor 的 `??_M`(257509–257514)。
3. **6 个容器偏移**：若仍保留 0x158/0x1F8/0x298/0x3D8/0x478 的 0xA0 步进（或任何 8B 缝保留在 0x1f0/0x290/0x330/0x3d0/0x470），可疑；真起点 0x170/0x208/0x2A0/0x338/0x3D0/0x468，步长 0x98。
4. **类外成员**：若任何成员偏移 ≥0x46EB8（尤其现注解的 m_Title_JDHY@0x5a7e4、m_Scroll@0x5b4dc、m_noteState@0x5b91c 这一串），可疑——它们落在分配之外，不能作为本类成员保留；若要保留这些语义，必须重新给出类内真实偏移（本卡暂未找到，见 §7）。
5. **零填充**：若在 0x262A4–0x262C8（36B）内声明了有写证据的成员，可疑——该区间被 `rep stosd` 9 dword 清零（asm:257405–257414），无其它写点；反之，若实现把数组起点挪到 0x262A4 之前并侵占了这段零区，也与 ctor 不符。

## 7 未决 / 风险（不阻塞验收，但实现方与验收方都该知道）

1. **0x158–0x170（24B）无定名**：只有 0x168/0x16C 两个零写点；16B 完全无写。需 IDA UDT/调用点证据才能定名，本卡只断言「它不是第 1 个 152B 容器的头部」。
2. **0x25AF0–0x25B7C（140B）部分无构造**：数组2 末端到下一个成员之间，ctor 只写 `[esi+25B70h]=0`、`[esi+25B78h]=0`（asm:257405–257406、257411），其余无写点、dtor 也不析构；可能是数组元素数不是 128（但 `push 80h` 明确是 128），也可能是对齐/未登记对象。
3. **类外那串成员的真实归属未查**：m_Title_JDHY/m_TopBar/m_Scroll/… 这一串（0x5a7e4 起）在 290,488B 类里没有位置。它们可能是另一个类（或旧版布局）的成员，本卡未做跨类追查；#23 若只是删掉它们，需在提交里写明删除理由与它们的去向。
4. **0x45A28/0x45B40/0x45C50 三个小对象类型未定**：步长 0x118/0x110，不匹配已知 152/248/344 三种尺寸，暂记 B 级。
5. **`?DestroyPages@UITitle_JDHY` 是 0x4B01D0 的误名**：它就是 ctor（写 vtable 0x56F33C）；注解 methods 里的 `_misattrib_evidence: max_offset=289120>class_size=1208` 用的 1208 是 UIListBox 链的旧 class_size，与本文尺寸裁决无关，但会在实现完后继续误导读者。
6. **基类名疑错**：现注解 `bases=[UIFrameWnd@0]`，但 ctor 首调 `sub_43DCD0`（asm:257264），该函数写 vtable `0x56AD20` = **UIListBox**（72B）。两者同为 72B、不影响本文尺寸与偏移，但影响继承链与槽位归属，实现时若改 bases 需另附证据。
7. **decomp JSON 不可作偏移证据**：`UITitle_JDHY_DestroyPagesvoid_004b01d0.json` 的 `this->` 成员名与现注解偏移已错位（把 ctor 写成 ResetContainerState、把数组写成 m_NoteItem[42]/[43]），本卡未使用其偏移，只作旁证。

## 8 只读自证

```
git status --short   # 本卡仅新增 docs/audit/2026-11-26-uititle-jdhy-expectation-baseline.md
```

- 未改 `data/annotations/**`、未改 `pal3/src/**`、未动 `data/status/**` 基线。
- 未运行 `pipeline/cli.py` 任何子命令；全部命令为 grep/sed/awk/python 只读。
- 工作树里其它 `M`（RoleStatePanel/SaleUI/ScreenEffectMgr/UIFrameContainer.json、stage5_fixup.py、README、data/status/*）均非本卡改动。

---

**一句话给验收方**：真值是 **290,488B / 数组 36×0xDE8@0x262C8 / 6 个 152B 容器@0x170 步长0x98 / 3 个 0x558 对象收尾于 0x46EB8**；现注解的 377,700 与「m_NoteItem@0x634 [99]」以及 0x5a7e4 之后的一串成员，都是同一条错误链的产物。
