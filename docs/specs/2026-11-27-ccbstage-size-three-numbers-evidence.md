# CCBStage 三尺寸取证（R6 ③：673,988 / 672,040 / 673,968）

> 只读取证。本文件是 `tsk_01M8CBACFXV6YG2FJT9SX4` 的唯一交付件；未改 `data/annotations`、`pal3/src`、`pipeline`、`tests`、基线，未跑 `apply/export/codegen/probe/loop`。
> 证据源：`original/PAL3.exe`、`data/status/_disasm_cache.txt`、`asm/pal3/ida_structs.json`、`data/annotations/structs/CCBStage.json`、`data/status/struct_holes_20261125.json`、`data/pdb/pdb_export.json`、`docs/audit/2026-11-26-r6-decision-brief.md`。

## 0. 结论

| 数字 | 性质 | 等级 |
|---|---|---|
| **672,040 (0xA4128)** | **本 exe 的 CCBStage 真尺寸**：唯一 ctor 分配点 + ctor 末端写界闭合 + vptr 0x5705D0 类身份 | **A** |
| 673,968 (0xA48B0) | **另一个对象的尺寸**：独立分配点 + 256 槽循环写界（末槽终点 `0xA48A4`，余 12B）+ 全对象清零常量；其 offset 0 被写入描述符指针而非 vptr，IDB 把它的初始化器误挂在 CCBStage 名下 | A（该对象）/ B（归属） |
| 673,988 (0xA48C4) | **注解派生值，无二进制支撑**：= 673,968 + 20B 幻影尾员；IDB/census 只是继承注解 | B |

一句话：**注解把两个对象拼成了一个类**——vtable/bases 与 ctor 属于 672,040 那个类，20 个成员与 673,968 那个对象吻合，末端再加 20B 得到 673,988。

## 1. 三数出处

| 数字 | 来源文件/字段 | 具体值 | 等级 |
|---|---|---|---|
| 673,988 | `data/annotations/structs/CCBStage.json` `binary_size`；`asm/pal3/ida_structs.json` `CCBStage.size`（导出照抄） | 末员 `m_dwAniFlagOver@0xA48C0`(uint) 末端 `0xA48C4` | B（注解）；IDB 非独立 |
| 672,040 | `probe_heap_alloc_census` 行 `??0CCBStage`，site `0x5233CD`，caller `InitGameSystems@CUtil`；`docs/audit/2026-11-26-r6-decision-brief.md:88-94`（census 该行把 store 记作 `esi+0x6C8`，与反汇编的 `[esi+0x6CC]` 不符，以反汇编为准） | `0x5233BE push 0xa4128` → `0x5233F9 mov [esi+0x6CC],eax` | A |
| 673,968 | 同表，`InitFromDescriptor@CCBStage`，site `0x512856`，store `esi+0x14`，caller `ProcNormalAttack@CCBSystem` | `0x512851 push 0xa48b0` | A（分配）/ B（被 new 的类） |
| 673,992 | `data/pdb/pdb_export.json` `CCBStage.size`（union） | PAL3A 的类表；与本 exe 差 4B，参考级 | C |

**同源派生关系**：673,988 与 IDB 的 673,988 是同一事实（IDB 由注解导出）；672,040 与 673,968 是两个真实分配，互斥——不可能同时是同一个类的 sizeof。

派生算术：673,968 − 673,988 = −20；672,040 − 673,988 = −1,948；673,988 − 672,040 = 1,948。

## 2. 判别性证据

### 2.1 分配 A（A 级）：672,040 只出现一次

```
5233be: 68 28 41 0a 00        push   0xa4128           ; 672,040
5233cd: e8 69 01 03 00        call   0x55353b          ; operator new
5233e5: 8b c8                 mov    ecx,eax
5233e7: e8 24 a3 ff ff        call   0x51d710          ; ??0CCBStage（IDB: flags=ctor）
5233f9: 89 86 c8 06 00 00     mov    DWORD PTR [esi+0x6c8],eax
```

`push 0xa4128` 全库仅此一处（C1）。store 槽是 `[esi+0x6CC]`（`0x5233F9 mov [esi+0x6CC],eax`），不是 `+0x6C8`。`0x5233C7 mov [esi+0x6C8],eax` 发生在 new **之前**，存的是上一个对象 `gbBinkVideo`（`0x5233B5 call 0x523F30`）的结果。`probe_heap_alloc_census` 的该行把 store 记作 `esi+0x6C8`，与反汇编不符，以反汇编为准。

### 2.2 ctor 写界 A（A 级）：终点 = 0xA4128

`0x51D710` 体（`0x51D710..0x51DD7F`，389 条）最大位移出现在尾部：

```
51dd2e: e8 bd 35 f8 ff        call   0x4a12f0          ; UIRoleDialog ctor（size 1368=0x558）
51dd33: 8d 8e d0 3b 0a 00     lea    ecx,[esi+0xa3bd0] ; 最后一个子对象
51dd3e: e8 ad 35 f8 ff        call   0x4a12f0          ; UIRoleDialog ctor
51dd43: c7 06 d0 05 57 00     mov    DWORD PTR [esi],0x5705d0   ; CCBStage vtable
```

`0xA3BD0 + 0x558 = 0xA4128 = 672,040`，与分配立即数逐字节相等。

第二个 ctor 变体 `0x51DDA0`（1273 条）同样以 `lea ecx,[esi+0xa3bd0]`（`0x51DDC3`）+ `call 0x4a12f0` + 写同一 vptr（`0x51DDBD`）收尾，最大位移同为 `0xA3BD0` ⇒ 两个入口的写界都是 `0xA4128`。

### 2.3 vptr 类身份（A 级）

`0x5705D0` 在 `ida_structs.json` 中只属于 `CCBStage`（7 槽：Render 0x524970 / Update 0x51F0A0 / HideAll 0x43DE40 / ~CCBStage 0x51DD80 / OnMessage 0x51F1B0）；ctor 在 `0x51DD43` 写它，`0x51DDBD` 复写。⇒ 分配到 `0x51D710` 的对象就是 CCBStage。

### 2.4 分配 B（A 级）：673,968 是另一个对象

```
512851: 68 b0 48 0a 00        push   0xa48b0           ; 673,968
512856: e8 e0 0c 04 00        call   0x55353b          ; operator new
512871: 56                    push   esi               ; 描述符参数
512872: 8b c8                 mov    ecx,eax
512874: e8 27 91 fe ff        call   0x4fb9a0          ; IDB 名 InitFromDescriptor@CCBStage
512886: 89 46 14              mov    DWORD PTR [esi+0x14],eax
```

`0x4FB9A0` 体（`0x4FB9A0..0x4FB9DE`）：

```
4fb9a5: 8d 93 c0 0a 00 00     lea    edx,[ebx+0xac0]    ; 256 个槽，步长 0xA48
4fb9ab: be 00 01 00 00        mov    esi,0x100
4fb9b2: b9 0b 00 00 00        mov    ecx,0xb            ; 每次 11 dword = 44B
4fb9b9: 81 c2 48 0a 00 00     add    edx,0xa48
4fb9c0: f3 ab                 rep stos DWORD PTR es:[edi],eax
4fb9c4: b9 2c 92 02 00        mov    ecx,0x2922c        ; 168,492 dword
4fb9c9: 8b fb                 mov    edi,ebx
4fb9cb: f3 ab                 rep stos DWORD PTR es:[edi],eax   ; 0x2922C*4 = 673,968B 全清零
4fb9d2: 89 03                 mov    DWORD PTR [ebx],eax ; offset 0 ← 描述符指针（不是 vptr）
4fb9d8: 89 43 04              mov    DWORD PTR [ebx+0x4],eax
```

三条相互独立的闭合：
1. **分配立即数**：`push 0xa48b0 = 673,968`（C1 全库唯一）；
2. **构造写界**：256 槽循环最后一槽从 `0xAC0 + 255×0xA48 = 0xA4878` 起写 44B，终点 `0xA48A4`，距 `0xA48B0` 余 **12B**（4B 对齐余量），没有越界；
3. **全对象清零常量**：`mov ecx,0x2922C` × 4 = **673,968**，与分配立即数一致。

> 注：`0x4FBA5A mov [esi+0xA48A8],eax` 位于 `0x4FB9DE ret 4` **之后**，属于下一个函数 `0x4FB9F0`（IDB 名 `SetData`），**不能**当作 `0x4FB9A0` 的末员写入证据；本报告不使用它。

**但它不是 CCBStage**：offset 0 被写成描述符指针而非 `0x5705D0`；函数无 ctor flag；store 槽是 `CCBSystem+0x14`（另一个宿主）。IDB 把它挂到 `CCBStage` 名下属 owner 误归。

### 2.5 注解 673,988 = 673,968 + 20

`grep -nE "push\s+0xa48c4\b"` 全库 0 命中；`0xA48C4` 无任何分配。注解的 20 个成员全部落在 `0x58..0xA48A8`，其中 `m_TaskGroups` 为 `CCBTaskGroup[256]@0xA8`，`0xA8 + 256×0xA48 = 0xA48A8`，正好是 673,968 那个对象里 `m_nTodo_A48A8` 的起始偏移（`int` 占 4B → `0xA48AC`，4B 对齐到 `0xA48B0`，与分配相等）。再往上加 `m_dwAniFlagOver@0xA48C0`（4B）和 20B 空洞，才得到 673,988。

## 3. 归属判别

| 对象 | 尺寸 | 构造/初始化 | 身份证据 | 成员证据 |
|---|---|---|---|---|
| A：CCBStage | **672,040** | `0x51D710` / `0x51DDA0`（ctor），写 vptr `0x5705D0` | vtable 槽位与方法表一致；分配点唯一 | ctor 写入的偏移：`0x58=0x80`、`0x5c=0x200`、`0x168/0x200/0x298/0x330`、`0x6D0..0x1E50` 一串子对象、`0x50154`/`0x7BE1C`/`0xA3664` 三块重复结构，末块子对象 `0xA3BD0` |
| B：未名对象 | **673,968** | `0x4FB9A0`（初始化器，非 ctor），`[this]=描述符`、`[this+4]=描述符->0x10` | offset 0 非 vptr；无 vtable 记录 | `0xAC0` 起 256 槽（步长 0xA48）清零，末槽终点 `0xA48A4`；`m_nTodo_A48A8` 位于 `0xA48A8`（不在 `0x4FB9A0` 的写界内，属类布局的末员） |
| 注解 673,988 | — | 无 | 借 A 的 vtable/bases | 借 B 的 20 员 + 20B 幻影尾员 |

**直接否证「673,988 是真实尺寸」**：它既无分配点，又同时容纳 A 的 ctor 终点（672,040）与 B 的成员末端（673,968），两个对象不可能同址。

## 4. 结论与影响面

### 4.1 结论

- **本 exe 的 CCBStage `binary_size` 应为 672,040 (0xA4128)**，证据等级 A（分配 + ctor 终点 + vptr 三链闭合）。
- **673,968 是另一个对象的真实尺寸**（A 级），其类名、vtable 归属未定；本卡不替它命名。
- **673,988 是注解派生值**：A 的类身份 + B 的成员表 + 20B 幻影尾员的 chimera，应废弃。
- PDB 的 673,992（PAL3A）与本 exe 差 4B，且 PDB 的类表在这几处与实机不一致（此前 #15/#22 已记录同型偏差），只能作参考，不能当选型依据。

### 4.2 缺口（不凑结论）

- ~~G1~~ **已闭合（原报告此条为算术错，已撤销）**：循环 `0x4FB9B0 mov edi,edx` / `0x4FB9B9 add edx,0xA48` / `0x4FB9C0 rep stos` 的最后一槽起点是 `0xAC0 + 255×0xA48 = 0xA4878`，写 44B 到 `0xA48A4`，距分配 `0xA48B0` **余 12B**，不越界。原稿把 `add edx` 之后的值（`0xA52C0`）当成最后一槽起点，误判 2,484B 越界——该错误不再保留。
- **G2**：B 的类名与 vtable 归属未定（无 `mov [this],offset` 记录，可能非多态结构）。
- **G3**：注解 20 员中 `m_pShadow/m_pEffect` 的类型与 A 的 ctor 写值（`0x58=0x80`、`0x5c=0x200`，即 128/512）矛盾，成员迁给 B 时需逐员重取证。

### 4.3 影响面（若按 672,040 重铸）

- `CCBStage.json`：`binary_size` 673,988 → **672,040**；20 个成员全部迁往 B 的正名卡（本卡不迁），`m_dwAniFlagOver@0xA48C0` 作废（落在两个对象之外）。
- census：`CCBStage` 当前 `hole_bytes=36`（`[0x48,0x58)=16`、`[0xA48AC,0xA48C0)=20`）。按真值重铸后，`[0xA48AC,0xA48B0)` 是 B 的尾对齐、`[0xA48B0,0xA48C0)` 落在 B 之外，两者都不再属于 CCBStage；CCBStage 只剩 `[0x48,0x58)` 的 16B。
- 下游：`CCBStageScene 1012`、`CCBStageRole 6848`、`CCBStageCam 6272`、`CCBStageEffect 25488`、`CCBStageShadow 1556` 是独立类，不受影响；`0x4FC7xx` 一带按 `+0xA48` 步进的方法跟随 B 走，需与 B 的卡一起迁移。
- IDB：`CCBStage.size` 会经 apply→export 跟随注解更新，不手改。

## 5. 下一张落地卡（草案，不建卡）

- 卡名建议：`CCBStage 尺寸重铸 + 20 员迁出（含 B 类正名）`。
- writeScopes：`data/annotations/structs/CCBStage.json`、`data/annotations/structs/<B>.json`（新建）、`data/annotations/functions.json`（`0x4FB9A0` 改挂）、`tests/`。
- 动作：①`CCBStage.binary_size=672040`，删 20 员与 `m_dwAniFlagOver`；②新建 B（`binary_size=673968`，成员=现 20 员，逐员重取证），把 `0x4FB9A0` 从 CCBStage.methods 移到 B；③`0x51D710/0x51DDA0` 保持 CCBStage ctor。
- 验收：`python tools/audit_type_layout.py --only CCBStage`；`python tools/check_annotations.py`；`python tools/census_struct_holes.py`（CCBStage 洞 ≤16B）；独占窗口 `pipeline/cli.py loop`（S2 ≥158/229、L1 ≥189、总错误 ≤630，不重锚）。
- 前置：B 的槽布局已由「分配立即数 + 末槽终点 `0xA48A4`（余 12B）」双向闭合，可按 `0xAC0/0xA48/256` 直接落卡；`0x4FBA5A`（`0x4FB9F0` 内）的 `[this+0xA48A8]` 写入需在卡里单独确认 `0x4FB9F0` 的 this 类型，不作为 B 的尺寸证据。

## 6. 复现命令与输出

### C1 三个数字的分配点计数

```bash
for s in 0xa4128 0xa48b0 0xa48c4; do
  echo "-- $s"; grep -cE "push\s+$s\b" data/status/_disasm_cache.txt
done
```

```
-- 0xa4128
1
-- 0xa48b0
1
-- 0xa48c4
0
```

### C2 分配 A 上下文

```bash
grep -nE "^\s*5233(be|c7|cd|e5|e7|f9):" data/status/_disasm_cache.txt
```

```
377261:  5233be:	68 28 41 0a 00       	push   0xa4128
377263:  5233c7:	89 86 c8 06 00 00    	mov    DWORD PTR [esi+0x6c8],eax
377264:  5233cd:	e8 69 01 03 00       	call   0x55353b
377271:  5233e5:	8b c8                	mov    ecx,eax
377272:  5233e7:	e8 24 a3 ff ff       	call   0x51d710
377277:  5233f9:	89 86 cc 06 00 00    	mov    DWORD PTR [esi+0x6cc],eax
```

### C3 ctor 终点与 vptr

```bash
grep -nE "^\s*51dd(2e|33|3e|43|bd|c3):" data/status/_disasm_cache.txt
```

```
371104:  51dd2e:	e8 bd 35 f8 ff       	call   0x4a12f0
371105:  51dd33:	8d 8e d0 3b 0a 00    	lea    ecx,[esi+0xa3bd0]
371107:  51dd3e:	e8 ad 35 f8 ff       	call   0x4a12f0
371108:  51dd43:	c7 06 d0 05 57 00    	mov    DWORD PTR [esi],0x5705d0
371156:  51ddbd:	c7 06 d0 05 57 00    	mov    DWORD PTR [esi],0x5705d0
371157:  51ddc3:	8d 8e d0 3b 0a 00    	lea    ecx,[esi+0xa3bd0]
```

### C4 分配 B 与全清零常量

```bash
grep -nE "^\s*5128(51|56|74|86):|^\s*4fb9(c4|cb|d2|d8):" data/status/_disasm_cache.txt
```

```
325856:  4fb9c4:	b9 2c 92 02 00       	mov    ecx,0x2922c
325858:  4fb9cb:	f3 ab                	rep stos DWORD PTR es:[edi],eax
325861:  4fb9d2:	89 03                	mov    DWORD PTR [ebx],eax
325864:  4fb9d8:	89 43 04             	mov    DWORD PTR [ebx+0x4],eax
355269:  512851:	68 b0 48 0a 00       	push   0xa48b0
355270:  512856:	e8 e0 0c 04 00       	call   0x55353b
355279:  512874:	e8 27 91 fe ff       	call   0x4fb9a0
355284:  512886:	89 46 14             	mov    DWORD PTR [esi+0x14],eax
```

`0x2922C × 4 = 673,968`。

### C5 B 的 256 槽循环（写界）

```bash
grep -nE "^\s*4fb9(ab|b0|b2|b9|bf|c0|c2):" data/status/_disasm_cache.txt
```

```
325848:  4fb9ab:	be 00 01 00 00       	mov    esi,0x100
325849:  4fb9b0:	8b fa                	mov    edi,edx
325850:  4fb9b2:	b9 0b 00 00 00       	mov    ecx,0xb
325852:  4fb9b9:	81 c2 48 0a 00 00    	add    edx,0xa48
325853:  4fb9bf:	4e                   	dec    esi
325854:  4fb9c0:	f3 ab                	rep stos DWORD PTR es:[edi],eax
325855:  4fb9c2:	75 ec                	jne    0x4fb9b0
```

`mov edi,edx` 在 `add edx,0xa48` **之前**，所以最后一槽（第 256 次）的起点是 `edx` 的**上一个值** `0xAC0 + 255×0xA48 = 0xA4878`，不是 `0xA52C0`。

### C6 写界与数组的算术闭合

```bash
python3 - <<'PY'
base, stride, n = 0xAC0, 0xA48, 256
last = base + (n-1)*stride
print(hex(last), last, hex(last+44), last+44)
print(hex(0xA48B0), 0xA48B0, 'headroom', 0xA48B0-(last+44))
print(hex(0xA8 + stride*n), 0xA8 + stride*n)
print(hex(0xA3BD0 + 0x558), 0xA3BD0 + 0x558)
PY
```

```
0xa4878 673912 0xa48a4 673956
0xa48b0 673968 headroom 12
0xa48a8 673960
0xa4128 672040
```

`0xA48A4` 距 `0xA48B0` 余 12B（4B 对齐），**不越界**；`0xA8 + 256×0xA48 = 0xA48A8` 是 `m_nTodo_A48A8` 的起始偏移（+4 对齐到 `0xA48B0`）。

### C7 PDB 参考值

```bash
python3 - <<'PY'
import json
d=json.load(open('data/pdb/pdb_export.json'))
cl=d['classes']
it=cl.items() if isinstance(cl,dict) else [(c.get('name'),c) for c in cl]
for n,c in it:
    if n=='CCBStage': print(n, c.get('size'), c.get('kind'))
PY
```

```
CCBStage 673992 union
```

### C8 census 现状

```bash
python3 - <<'PY'
import json
d=json.load(open('data/status/struct_holes_20261125.json'))
for c in d.get('classes') or []:
    if c.get('cls')=='CCBStage':
        print(c['size'], c['members'], c['hole_bytes'], c['holes'])
PY
```

```
673988 20 36 [['0x48', '0x58', 16], ['0xa48ac', '0xa48c0', 20]]
```

## 7. 边界

- 只新增本文件；`data/annotations/structs/CCBStage.json`、`asm/pal3/ida_structs.json`、基线均未改（`git status` 中若见 `M data/status/s4_baseline.json`，属并发管线的改动，非本卡）。
- 未跑任何管线阶段；未用 `pal3/src` 生成物当证据。
