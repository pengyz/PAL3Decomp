# UITitle_JDHY / Note_Item 双布局判别性证据（只读取证）

- 卡：tsk_01M8C9B3E8ZEPN20YSX515（#22，R6①）
- 范围：只读取证；只新增本文件，未改注解/代码/数据/基线，未跑 apply/export/codegen/probe/loop。
- 证据源：`original/PAL3.exe`（经 `data/status/_disasm_cache.txt` 反汇编缓存）、`asm/pal3/ida_structs.json`（IDB 导出）、`data/annotations/structs/*.json`、`data/pdb/pdb_export.json`（PAL3A PDB）、`data/status/probe_heap_alloc_census_20261126.json`、`data/status/struct_holes_20261125.json`。

## 0. 结论摘要

1. **本 exe 的 `sizeof(UITitle_JDHY) = 290,488 = 0x46EB8`（A 级）。** 判别性证据是 `operator new` 立即数：`0x4A46B5 push 0x46EB8` → `0x4A46C4 call 0x55353B`（operator new）→ `0x4A46DE call 0x4B01D0`（真 ctor）→ `0x4A46F2 mov [esi+0x2AFD0],eax`（存入 RoleStatePanel 第 7 槽）。
2. **`sizeof(Note_Item) = 3,560 = 0xDE8`（A 级）**，且 UITitle 里是 **`Note_Item[36] @0x262C8`**，不是 `[99] @0x634`：ctor 两处 vector-ctor-iterator 都是 `(ptr=esi+0x262C8, size=0xDE8, count=0x24=36, ctor=0x454AA0)`；`m_isItemShow` 用 `mov ecx,9; rep stos dword` = **36 字节**。
3. **旧注解 377,700 无构造证据**：全库没有 `push 0x5C364`（377,700）或 `push 0x5C404`（377,860）的分配；`data/status/ctor_layout_decode.json` 对该类记录 `"status": "no-func"`，即它从未匹配到 ctor。
4. **3,728 不是独立测量值**，而是旧布局的派生量：`(0x5A7E4 - 0x634) / 99 = 3,728.0`。99×3,728 = 369,072 恰好把 `[99]@0x634` 排到旧注解的下一员 `m_Title_JDHY@0x5A7E4`；换 99×3,560 = 352,440 则落到 `0x566EC`，越过真尺寸 63,540B。
5. **PDB 的 377,860 / 3,728 属 PAL3A 构建**，不是本 exe 布局：PDB `UIStatic=160` 而本 exe IDB `UIStatic=152`；`Note_Item` 的 3,728−3,560 = **168 = 21×8**，21 正是该类里的 UIStatic 实例数（1+1+5+5+1+1+5+1+1）。
6. 结论：**支持 290,488 + Note_Item 3,560 + `[36]` 一套**（两类独立证据——分配立即数/ctor 写界 与 数组 ctor 参数/自身 ctor 写界——闭合）；377,700、99×3,560、3,728 三条线均无本 exe 证据，属旧注解、旧注解派生、PAL3A PDB 产物。

## 1. 问题与各数字的来源

### 1.1 四个/五个数字并存

| 数字 | 出处 | 性质 |
|---|---|---|
| **377,700** | `data/annotations/structs/UITitle_JDHY.json` 的 HEAD 版（`git show HEAD:`），28 员全 `unverified` | 旧注解，无 ctor/分配支撑；`ctor_layout_decode.json` 记 `status=no-func` |
| **377,860** | `data/pdb/pdb_export.json` → `UITitle_JDHY` union | PAL3A PDB 布局（见 §2.7） |
| **290,488** | ① `_disasm_cache.txt:207302 push 0x46EB8` + `:207305` operator new；② IDB `UITitle_JDHY.size`；③ 工作树注解 `binary_size`（mtime 23:50:11，他人并发改动） | 本 exe 真尺寸（A） |
| **3,560** | `Note_Item` 注解/IDB `binary_size`；Note_Item ctor 写界；UITitle ctor 数组 ctor 的 size 参数 | 本 exe 真尺寸（A） |
| **3,728** | `(0x5A7E4−0x634)/99`（由旧注解成员位置反推）；PDB `Note_Item` struct 亦为 3,728 | 派生量 + PAL3A PDB |
| 99×3,560 = **352,440** | 旧布局 `[99]` × 注解尺寸 | 两者混算的产物 |
| 99 | 旧注解 `m_isItemShow unsigned char[99]` / `m_NoteItem Note_Item[99]` | 无二进制出处（§2.3 表明是 36） |

### 1.2 两套假设

- **假设 L（290,488 布局）**：`Note_Item[36]@0x262C8`，尾部 0x45EB0/0x46408/0x46960 三个 `UIRoleDialog`，末员 0x46960+0x558=0x46EB8 精确闭合。
- **假设 H（377,700 布局）**：`Note_Item[99]@0x634`（每元素 3,728 才能排到 0x5A7E4），其后 `m_Title_JDHY/m_TopBar/.../m_noteState@0x5B91C`，0x5B920..0x5C364（2,628B）无成员解释。

## 2. 逐项取证

### 2.1 operator new 立即数（判别性，A 级）

`data/status/_disasm_cache.txt`：

```
207302:  4a46b5: 68 b8 6e 04 00        push   0x46eb8          ; 290,488
207305:  4a46c4: e8 72 ee 0a 00        call   0x55353b         ; operator new
207313:  4a46de: e8 ed ba 00 00        call   0x4b01d0         ; UITitle ctor（IDB 误名 DestroyPages）
207319:  4a46f2: 89 86 d0 af 02 00     mov    [esi+0x2afd0],eax ; RoleStatePanel 第 7 槽
```

同段 `0x4A4692` 起是上一槽（`[esi+0x2AFCC]`，`call 0x47E5C0`）的分配，说明这是 `RoleStatePanel::Init` 的七模块分配序列（与 #18 的七槽结论一致）。

反证式检验：全库 `grep -E 'push +0x(5c364|5c404)\b'` **零命中**——本 exe 从未按 377,700 或 377,860 分配过该对象。

### 2.2 ctor 写界（判别性，A 级）

真 ctor `0x4B01D0`（`_disasm_cache.txt:221964` 起）：

- `0x4B01EF call 0x43DCD0`：基类 ctor（IDB 把 0x43DCD0 命名为 `UIListBox`，与 `bases=[UIFrameWnd@0]` 不符，属命名缺口，不影响尺寸）。
- `0x4B04DF mov [esi],0x56F33C`：写自有 vptr（`_disasm_cache.txt:222120`）。
- `0x4B04E5 lea edi,[esi+0x262A4]` + `0x4B04F0 mov ecx,9` + `0x4B0501 rep stos dword`（`:222121`/`:222127`）：清 36 字节。
- 最高标量写：`[esi+0x45EA8]=0`（`0x4B04FB`）、`[esi+0x45E90]=0x5C`、`[esi+0x45E94]=0x262`（`0x4B0486`/`0x4B0490`）。
- 最后子对象：`0x4B04D2` 调 `0x4A12F0` 构造 `UIRoleDialog@0x46960`；`UIRoleDialog` 尺寸 1,368=0x558 ⇒ **0x46960+0x558 = 0x46EB8 = 分配尺寸，精确闭合**。
- ctor 结束于 `0x4B0516 ret`（`_disasm_cache.txt:222135`），之后 `0x4B0520/0x4B0540` 是删除式/complete dtor。

### 2.3 数组 stride 与元素数（判别性，A 级）

`m_NoteItem` 在 ctor 里被 **vector-ctor-iterator** 初始化两次，参数一致（`_disasm_cache.txt`）：

```
222072:  4b03e9: 68 a0 4a 45 00   push 0x454aa0     ; Note_Item ctor
222074:  4b03f3: 6a 24            push 0x24         ; count = 36
222076:  4b03fb: 68 e8 0d 00 00   push 0xde8        ; size = 3,560
222077:  4b0400: 52               push edx          ; ptr = esi+0x262c8
222079:  4b0406: e8 ...           call 0x553627     ; 5 参变体
...
222199:  4b0606: 68 a0 4a 45 00   push 0x454aa0
222202:  4b0613: 68 e8 0d 00 00   push 0xde8
222204:  4b0619: 50               push eax          ; ptr = esi+0x262c8
222206:  4b061e: e8 ...           call 0x553549     ; 4 参 vector ctor iterator
```

⇒ 元素 3,560、元素数 **36**、基址 0x262C8。`0x262C8 + 36×3,560 = 0x45768`，正好是下一员 `m_unk_0x45768` 的偏移（成员链无缝隙）。

同一 ctor 的 `m_isItemShow` 也用 36：`0x4B04E5 lea edi,[esi+0x262A4]; mov ecx,9; rep stos dword` = 36 字节，与 `unsigned char[36]` 一致。

### 2.4 Note_Item 自身 ctor 写界（判别性，A 级）

`Note_Item` ctor `0x454AA0`（`_disasm_cache.txt:112953`）：

- `0x454ABD lea ecx,[esi+0xD50]` → `call 0x442390`（UIStatic ctor，`:112962`）——这是最高成员。
- `0x454AE7 lea eax,[esi+0x9C0]; push 0x98(152); push 5; call 0x553549`——`UIStatic[5]` 数组。
- **0xD50 + 0x98 = 0xDE8 = 3,560**，与注解/IDB `binary_size` 一致；该 ctor 没有任何 ≥0xDE8 的成员写。

### 2.5 内嵌与 vtable 边界

- `UITitle_JDHY` vtable `0x56F33C`，7 槽（Render 0x4B2C70 / Update 0x4B3100 / HideAll 0x43DE40 / `scalar deleting dtor` 0x4B0520 / OnMessage 0x4B3470 等），与 290,488 布局的方法集一致；邻近 vtable（0x56F37C 等）无重叠。
- 基类 `UIFrameWnd` = 72 = 0x48，与首员 `rc@0x48` 吻合。
- 假设 H 的 `0x5A7E4..0x5B91C` 成员（`m_Title_JDHY/m_TopBar/m_BottomBar/m_BackBar/m_BackBar2/m_pbPage/m_Scroll/m_*`）在本 exe 的 UITitle 方法域里**没有任何访问点**（见 §2.6），也没有对应构造调用。

### 2.6 成员访问位移直方图（判别性，B 级）

口径：只统计 `UITitle_JDHY` 方法域 `0x4B01D0..0x4B4600`（ctor/dtor/Render/Update/OnMessage/HandleInput/SaveData/LoadData/InitPageState 等 23 个方法地址都落在此区间），指令必须形如 `[reg+0xNNNN]`，且位移 <0x100000（排除把立即数地址误读成位移的行）。

实测（`C6`）：

- 带位移的指令 **1,359 条**（缓存 md5 `28cacbf44d172880f07255c91b3aba52`，mtime 16:02:24）；最大合理位移 **0x46E9D**（位于最后一个 UIRoleDialog 内）。
- 位移 **≥0x46EB8 的 0 条**；落在 **0x46EB8..0x5C364 区间 0 条**。

⇒ 没有任何方法把该对象当作 >290,488 使用；假设 H 的 0x46EB8 以上成员全部无消费点。

### 2.7 PDB 的 377,860 / 3,728 为什么不同（B 级，机制已定）

`data/pdb/pdb_export.json` 与 IDB 的 UI 基类尺寸不同：

| 类 | PDB（PAL3A） | 本 exe IDB | 差 |
|---|---|---|---|
| `UIStatic` | 160 | 152 | +8 |
| `UIPushButton` | 252 | 248 | +4 |
| `UIScrollBar` | 368 | 352 | +16 |

`Note_Item` 含 **21 个 UIStatic 实例**（m_NoteID 1 + m_NoteState 1 + m_HeadShot_NO_SEL[5] 5 + m_HeadShot[5] 5 + m_NoteTime 1 + m_NoteMoney 1 + m_NoteLv[5] 5 + m_NotePic 1 + m_NotePicName 1）：**21×8 = 168 = 3,728−3,560**，差额被完整解释。故 PDB 的 3,728 是 PAL3A 头文件/布局的产物，不能作为本 exe 目标值；同理 PDB 的 377,860 与旧注解 377,700 相差 160，也不是本 exe 的分配尺寸。

## 3. 对账：两套假设各能解释什么

| 现象 | 假设 L（290,488/[36]/3,560） | 假设 H（377,700/[99]/3,728） |
|---|---|---|
| `push 0x46EB8` + new + ctor + store 0x2AFD0 | ✅ 直接就是该尺寸 | ❌ 无法解释为何只分配 290,488 |
| ctor 尾 0x46960+0x558=0x46EB8 | ✅ 精确闭合 | ❌ 0x46EB8 处被截断，剩余 87,212B 无构造 |
| 数组 ctor `size=0xDE8,count=0x24` | ✅ 3,560×36 | ❌ 参数应为 0xE90/0x63，实际不是 |
| `m_isItemShow` rep stos 9 dword=36B | ✅ | ❌ 应为 99B（需 25 dword） |
| Note_Item 自身 ctor 0xD50+0x98 | ✅ 3,560 | ❌ 3,728 多出 168B 无写点 |
| 访问位移 ≤0x46E9D | ✅ | ❌ 0x46EB8 以上零访问 |
| 旧注解 `[99]` 排到 0x5A7E4 | ❌ 该成员在 290,488 内不存在 | ✅ 但这是它自己的假设所造 |
| PDB 377,860/3,728 | ❌ | ✅ 但属 PAL3A 构建（§2.7） |
| 无 `push 0x5C364/0x5C404` | ✅ | ❌ 从未按该尺寸分配 |

判别性证据排序（均由本 exe 直接读出）：
1. `0x4A46B5 push 0x46EB8` + `0x4A46C4 new` + `0x4A46DE ctor` + `0x4A46F2 store`；
2. `0x4B03FB/0x4B0613 push 0xDE8` + `push 0x24`（元素尺寸/个数）；
3. `0x4B0501 rep stos`（36B）与 `0x4B04D2` 的末子对象闭合。

## 4. 结论（A/B/C 分级）

- **A 级（结论）**：本 exe `sizeof(UITitle_JDHY)=290,488`、`sizeof(Note_Item)=3,560`、`m_NoteItem[36]@0x262C8`、`m_isItemShow[36]@0x262A4`。置信度高：分配链、ctor 写界、数组 ctor 参数、Note_Item 自身 ctor 四路互相闭合。
- **B 级（否定）**：377,700、99×3,560=352,440、3,728 三条线均无本 exe 证据；前两者是旧注解与旧注解派生量，3,728 亦见于 PAL3A PDB 但机制已解释（21×8）。
- **C 级（未决缺口，不影响上述定谳）**：
  1. 290,488 布局内部的成员语义空隙（0x160..0x168 等）未逐段定名；现行 census 尚未按 290,488 布局重算（见 §5.6），因此「洞账」一栏以重跑后的 census 为准；
  3. `0x43DCD0` 的基类 ctor 命名（IDB 名 UIListBox vs bases UIFrameWnd），需另案正名，不影响尺寸；
  4. 「是否另有一套 `Role[50]` 布局」不在本卡，未取证。

> 定论依据全部是「本 exe 的指令/分配/构造」，没有用任何总数配平或 PDB 单源推断。

## 5. 影响（只写，不改）

1. `data/annotations/structs/UITitle_JDHY.json`：`binary_size` 应为 **290,488**（工作树已是该值，mtime 23:50:11，属并发改动；HEAD 的 377,700 不应恢复）。
2. `m_NoteItem` 的元素数应为 **36**、元素类型 `Note_Item`（3,560），基址 0x262C8；`m_isItemShow` 应为 `unsigned char[36]`。
3. 旧布局 0x5A7E4..0x5B91C 的成员（`m_Title_JDHY/m_TopBar/m_BottomBar/m_BackBar/m_BackBar2/m_pbPage/m_Scroll/m_CurScrollPos/m_ItemH/m_ItemW/m_firstItem/m_selItem/m_getNote/m_loading/m_passtime/m_LoadBtn/m_DeleteBtn/m_noteState`）**没有证据支持**，应从注解移除而不是搬家（本卡不改）。
4. `RoleStatePanel+0x2AFD0` 槽（#18 七模块第 7 槽）可在本结论后类型化为 `UITitle_JDHY*`（此前因尺寸不合暂记 `void*`）；`+0x2AFB8..+0x2AFCC` 其余六槽不受影响。
5. sizeof 断言可用：`sizeof(UITitle_JDHY)==290488`、`sizeof(Note_Item)==3560`；`m_NoteItem` 数组尾部 = 0x45768。
6. 洞账：**当前** `data/status/struct_holes_20261125.json`（mtime 11-27 00:10:25）仍按**旧注解**计——`UITitle_JDHY size=377700 / members=28 / hole_bytes=19,396 / 14 段`，其中 `0x566EC..0x5A7E4`（16,632B）与 `0x5B920..0x5C364`（2,628B）两段正是 377,700 假设的产物（99×3,560 越界区与其后的无访问尾部）。该 census 未随工作树 290,488 注解与 IDB 同步更新，**落地后必须重跑 census** 才能得到新洞账；本报告不以旧 census 作为尺寸证据。`Note_Item` 不在该 census 的 201 类列表中（原文误写为「3,560」），其尺寸结论不依赖 census。

## 6. 复现命令与实测输出

以下命令在仓库根执行，均只读。C1–C7 原样执行 `EXIT_ALL=0`。

### C1 五方尺寸对账

```bash
python3 - <<'PY'
import json
a=json.load(open('data/annotations/structs/UITitle_JDHY.json'))
n=json.load(open('data/annotations/structs/Note_Item.json'))
idb=json.load(open('asm/pal3/ida_structs.json'))
pdb=json.load(open('data/pdb/pdb_export.json'))
print('注解 UITitle', a['binary_size'], '员', len(a['known_members']), 'base', a.get('base_size'), a.get('bases'))
print('注解 Note_Item', n['binary_size'], '员', len(n['known_members']))
print('IDB UITitle', idb['UITitle_JDHY']['size'], 'Note_Item', idb['Note_Item']['size'])
print('IDB UIStatic', idb['UIStatic']['size'], 'UIPushButton', idb['UIPushButton']['size'], 'UIScrollBar', idb['UIScrollBar']['size'])
for c in pdb['classes']:
    if c['name'] in ('UITitle_JDHY','Note_Item','UIStatic','UIPushButton','UIScrollBar'):
        print('PDB', c['name'], c['kind'], c['size'])
PY
```

实测输出：

```
注解 UITitle 290488 员 39 base 72 [{'name': 'UIFrameWnd', 'offset': 0}]
注解 Note_Item 3560 员 12
IDB UITitle 290488 Note_Item 3560
IDB UIStatic 152 UIPushButton 248 UIScrollBar 352
PDB UIScrollBar union 368
PDB UIStatic union 160
PDB UIPushButton union 252
PDB UITitle_JDHY union 377860
PDB Note_Item struct 3728
```

### C2 分配链

```bash
grep -nE '4a46b5:|4a46c4:|4a46de:|4a46f2:' data/status/_disasm_cache.txt
```

实测输出：

```
207302:  4a46b5:	68 b8 6e 04 00       	push   0x46eb8
207305:  4a46c4:	e8 72 ee 0a 00       	call   0x55353b
207313:  4a46de:	e8 ed ba 00 00       	call   0x4b01d0
207319:  4a46f2:	89 86 d0 af 02 00    	mov    DWORD PTR [esi+0x2afd0],eax
```

### C3 ctor 写界与 vptr

```bash
grep -nE '4b04df:|4b04e5:|4b0501:|4b04d2:|4b04fb:' data/status/_disasm_cache.txt
```

实测输出：

```
222117:  4b04d2:	e8 19 0e ff ff       	call   0x4a12f0            ; UIRoleDialog@0x46960 ctor
222120:  4b04df:	c7 06 3c f3 56 00    	mov    DWORD PTR [esi],0x56f33c
222121:  4b04e5:	8d be a4 62 02 00    	lea    edi,[esi+0x262a4]
222126:  4b04fb:	89 9e a8 5e 04 00    	mov    DWORD PTR [esi+0x45ea8],ebx
222127:  4b0501:	f3 ab                	rep stos DWORD PTR es:[edi],eax
```

### C4 数组 ctor 参数（元素尺寸/个数）

```bash
sed -n '222072,222080p;222199,222206p' data/status/_disasm_cache.txt | sed 's/^ *//'
```

实测输出：

```
4b03e9:	68 a0 4a 45 00       	push   0x454aa0
4b03ee:	68 a0 49 45 00       	push   0x4549a0
4b03f3:	6a 24                	push   0x24
4b03f5:	8d 96 c8 62 02 00    	lea    edx,[esi+0x262c8]
4b03fb:	68 e8 0d 00 00       	push   0xde8
4b0400:	52                   	push   edx
4b0401:	c6 44 24 2c 1b       	mov    BYTE PTR [esp+0x2c],0x1b
4b0406:	e8 1c 32 0a 00       	call   0x553627
4b040b:	8d 8e 68 57 04 00    	lea    ecx,[esi+0x45768]
4b0606:	68 a0 4a 45 00       	push   0x454aa0
4b060b:	6a 24                	push   0x24
4b060d:	8d 86 c8 62 02 00    	lea    eax,[esi+0x262c8]
4b0613:	68 e8 0d 00 00       	push   0xde8
4b0618:	50                   	push   eax
4b0619:	c6 44 24 20 1b       	mov    BYTE PTR [esp+0x20],0x1b
4b061e:	e8 26 2f 0a 00       	call   0x553549
4b0623:	c6 44 24 10 1a       	mov    BYTE PTR [esp+0x10],0x1a
```

### C5 Note_Item 自身 ctor 写界

```bash
sed -n '112953,112975p' data/status/_disasm_cache.txt | sed 's/^ *//' | grep -E 'lea|push|call'
```

实测输出（节选）：

```
454abd:	8d 8e 50 0d 00 00    	lea    ecx,[esi+0xd50]
454acb:	e8 c0 d8 fe ff       	call   0x442390
454ae7:	8d 86 c0 09 00 00    	lea    eax,[esi+0x9c0]
454aed:	68 98 00 00 00       	push   0x98
454af2:	50                   	push   eax
454af8:	e8 4c ea 0f 00       	call   0x553549
```

### C6 访问位移直方图（方法域 0x4B01D0..0x4B4600）

```bash
python3 - <<'PY'
import re
raw=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().split('\n')
pat=re.compile(r'^\s*([0-9a-f]{6,8}):\t([0-9a-f ]+)\t(.*)$')
disp=[]
for ln in raw:
    m=pat.match(ln)
    if not m: continue
    if not (0x4b01d0 <= int(m.group(1),16) <= 0x4b4600): continue
    for d in re.findall(r'\[e[a-z]{2}\+0x([0-9a-f]+)\]', m.group(3)):
        v=int(d,16)
        if v < 0x100000: disp.append(v)
print('带位移指令', len(disp), '最大', hex(max(disp)))
print('>=0x46eb8', sum(1 for v in disp if v>=0x46eb8), '0x46eb8..0x5c364', sum(1 for v in disp if 0x46eb8<=v<=0x5c364))
PY
```

实测输出：

```
带位移指令 1359 最大 0x46e9d
>=0x46eb8 0 0x46eb8..0x5c364 0
```

### C7 PDB 差异机制与派生量

```bash
python3 - <<'PY'
print('3,728-3,560 =', 3728-3560, '= 21*8 ->', 21*8)
print('(0x5a7e4-0x634)/99 =', (0x5a7e4-0x634)/99)
print('99*3560 end =', hex(0x634+99*3560), 'overflow vs 290488 =', 0x634+99*3560-290488)
print('36*3560 end =', hex(0x262c8+36*3560))
print('0x46960+0x558 =', hex(0x46960+0x558), '== 0x46eb8', 0x46960+0x558==0x46eb8)
PY
```

实测输出：

```
3,728-3,560 = 168 = 21*8 -> 168
(0x5a7e4-0x634)/99 = 3728.0
99*3560 end = 0x566ec overflow vs 290488 = 63540
36*3560 end = 0x45768
0x46960+0x558 = 0x46eb8 == 0x46eb8 True
```

### C8 现行 census 实况（用于核对 §5.6）

```bash
python3 - <<'PYC'
import json
d=json.load(open('data/status/struct_holes_20261125.json'))
cls=d.get('classes') or []
names=[c.get('cls') for c in cls]
print('classes', len(names), 'UITitle_JDHY' in names, 'Note_Item' in names)
for c in cls:
    if c.get('cls')=='UITitle_JDHY':
        print(c['cls'], 'size', c.get('size'), 'members', c.get('members'), 'hole_bytes', c.get('hole_bytes'), 'holes_n', len(c.get('holes') or []))
        print('  holes', c.get('holes'))
PYC
```

实测输出（11-27 00:10:25 版文件）：

```
classes 201 True False
UITitle_JDHY size 377700 members 28 hole_bytes 19396 holes_n 14
  holes [['0x1f0', '0x1f8', 8], ['0x290', '0x298', 8], ['0x330', '0x338', 8], ['0x3d0', '0x3d8', 8], ['0x470', '0x478', 8], ['0x566ec', '0x5a7e4', 16632], ['0x5a87c', '0x5a884', 8], ['0x5a91c', '0x5a924', 8], ['0x5a9bc', '0x5a9c4', 8], ['0x5aa5c', '0x5aa64', 8], ['0x5aafc', '0x5ab04', 8], ['0x5b4b4', '0x5b4dc', 40], ['0x5b63c', '0x5b64c', 16], ['0x5b920', '0x5c364', 2628]]
```

**注意**：`Note_Item` **不在**该 census 的 201 个类里（`'Note_Item' in names` 为 `False`），所以不能从该文件取它的洞账；它的 3,560 结论来自注解/IDB 与自身 ctor 写界（§2.4），不依赖 census。

## 7. 只读边界与工作区归属

- 本卡只新增本文件；`data/annotations`、`pal3/src`、`pipeline`、`tests`、基线均未由我改动。
- 工作区 `data/annotations/structs/UITitle_JDHY.json` 处于 `M`（mtime 23:50:11，diff +212/−146），是并发任务对 290,488 布局的重铸；本报告独立复算与之一致，但**不是我的改动**，也未据此改任何文件。
- `data/status/s4_baseline.json` 等基线在并发管线中可能为 `M`；本卡未读写基线，未重锚。
- 与 #17 决策简报不重复全文：本文件只补二进制证据与判别链。
