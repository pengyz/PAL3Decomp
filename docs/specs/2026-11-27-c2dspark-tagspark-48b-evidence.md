# R6② 取证：C2DSpark / C2DSpark_tagSpark 的实体归属与 48B 命题闭合

> 卡：`tsk_01M8CC2V7F3HG3CEFS3VSV`（只读取证）。本文只依据 `original/PAL3.exe` 的反汇编缓存、`asm/pal3/decomp`/`ida_structs.json`、`data/annotations/`、`data/status/struct_holes_20261125.json`、`data/pdb/pdb_export.json`。
> **未运行** apply / export / codegen / probe / loop；**未修改**任何注解、源码、管线、基线。

## §0 结论

1. **`sizeof(C2DSpark) = 0x5870 = 22,640`**（A 级）。三链独立一致：唯一分配点立即数 `push 0x5870`（`0x512AE1`）→ ctor 整对象清零常量 `mov ecx,0x161C; rep stos`（`0x161C×4 = 22,640`）→ ctor 最大写偏移 `[esi+0x586C]`（+4 = `0x5870`）。
2. **`sizeof(C2DSpark_tagSpark) = 0x2C = 44`**（A 级）。三处独立步长均为 `0x2C`、元素数均为 `0x200=512`；`CreateSingle` 以 `mov ecx,0xb; rep movs` 整元素拷贝 11 dword = 44B；`512×44 = 22,528 = 0x5800`，与尾部成员起点逐字节对齐。
3. **`m_Spark` = `C2DSpark_tagSpark[512] @0x0`，占 22,528B**，不是 24,576B；尾部 19 个成员从 `0x5800` 起，`m_Quad@0x5848 + 0x28 = 0x5870` 精确闭合。
4. 注解的 **24,688 / 48 是派生量**：`48 = 24,576/512`，而 `24,576` 来自注解自己的尾部起点 `0x6000`（比实测多 `0x800 = 512×4`）——**循环自洽、与二进制不符**。PDB（PAL3A）同为 24,688/48，属另一构建参考值（CLAUDE.md：PDB 只能作参考、不能单独作证据），不能压过本 exe 的三条 A 级链。
5. 元素真实字段用法（Render/CreateSingle 共同证明）：`+0x00`/`+0x04` 为 float 位置、`+0x18` 为 float 颜色/亮度源、`+0x20` 为 float 尺寸、`+0x28` 为 BYTE 类型（0..3，四路跳表）、`+0x29` 为 BYTE 可见位（0/1），`+0x2A..+0x2B` 对齐填充。现存 12 员（5 组 texture/wrap + nRenderEffect + pRenderEffect）与实际使用**不符**，属元素语义层的独立缺陷（§4.3 D-1），本卡不改、不臆造新名。
6. 顺带发现方法名错位：`0x4D61C0`（现名 `DestroyAll`）函数体内是完整的绘制循环，`0x4D6380`（现名 `Render`）函数体是鼠标轨迹更新（读 `[esi+0x5818]` 后调 `0x4022E0`）。属注解层命名缺陷（§4.3 D-2），本卡只记录不改。

## §1 命题与出处

### 1.1 简报原文（#17 §2）

> C2DSpark 真实 sizeof 是金表 22,640 还是注解 24,688；`m_Spark` 是 512×48B(24,576) 还是元素数/元素尺寸另有其值。

### 1.2 数字表（照抄简报，标注实测/推断）

| 数字 | 出处 | 简报定级 | 本文复核 |
|---|---|---|---|
| `C2DSpark binary_size = 24,688` | `data/annotations/structs/C2DSpark.json` | B | 反推值：`22,640 + 512×4`，见 §3.6 |
| `m_Spark@0x0 = C2DSpark_tagSpark[512]`，数组末端 24,576 | 同上 | B | 元素数 512 正确；元素尺寸 48 错，应为 44 |
| 尾员 112B（`0x6000..0x6070`） | 同上 | B | 112B 正确；起点应为 `0x5800` |
| `C2DSpark_tagSpark binary_size = 48` | `C2DSpark_tagSpark.json` note：「Size=48 from array stride (24576/512)」 | B（反推） | 错，应为 44；48 由错误数组长度反推 |
| 金表 `22,640 = 0x5870`、`??0C2DSpark`、site `0x512AF0` | `data/status/probe_heap_alloc_census_20261126.json` | A | 成立，分配点 `0x512AE1`、new 调用 `0x512AF0` |

### 1.3 现状快照

- 注解 `C2DSpark.json`：`binary_size 24688`、无 `bases`/`base_size`、20 员、9 methods（ctor `0x4D5AB0`、`~C2DSpark 0x4D5DC0`、CreateSingle/CreateTrack/SetEnableMouseTrack/CreateMore/CreateStars/DestroyAll/Render）、mtime `2026-11-18 18:41:21`（本轮未改）。
- 注解 `C2DSpark_tagSpark.json`：`binary_size 48`、12 员、mtime `2026-11-16 21:22:26`。
- `asm/pal3/ida_structs.json`：C2DSpark 24688（照抄注解）、C2DSpark_tagSpark 48；依赖类型 `gbUIQuad=40`、`gbTextureArray=68`、`gbRenderEffect=68`。
- `data/annotations/functions.json`：243 条扁平 dict，对本文涉及的 9 个地址均无条目（类方法只存在于 `structs/*.json`）。
- `struct_holes_20261125.json`：**C2DSpark / C2DSpark_tagSpark 都不在 200 类列表内**（无 census 洞条目）。

## §2 实体判别

### 2.1 唯一分配点与调用者

`data/status/_disasm_cache.txt`（C2）：

```
512ae1: 68 70 58 00 00        push   0x5870
512af0: e8 46 0a 04 00        call   0x55353b          ; operator new
512b19: 8b c8                 mov    ecx,eax
512b1b: e8 90 2f fc ff        call   0x4d5ab0          ; ??0C2DSpark
512b30: 89 46 34              mov    DWORD PTR [esi+0x34],eax
```

- `push 0x5870` 全库唯一；紧随其后 `push 0x3e30`（15,920）分配相邻对象并存入 `[esi+0x38]`——这是同一初始化序列里的连续成员分配。
- ctor 唯一调用点 `0x512B1B`；dtor `0x4D5DC0` 唯一调用点 `0x512D09`（同一调用者，见 C9）。⇒ 该 22,640B 对象就是注解里的 C2DSpark 实例，不是"另一类被误挂"。

### 2.2 ctor 写界（C3）

```
4d5ac4: b9 1c 16 00 00        mov    ecx,0x161c        ; 0x161C dword = 22,640B
4d5acb: c7 86 6c 58 00 00 ff  mov    DWORD PTR [esi+0x586c],0xffffffff
4d5ad5: 89 9e 68 58 00 00     mov    DWORD PTR [esi+0x5868],ebx
4d5adb: f3 ab                 rep stos DWORD PTR es:[edi],eax
4d5d77: c7 86 6c 58 00 00 ff  mov    DWORD PTR [esi+0x586c],0xffffffff
4d5d81: 89 86 64 58 00 00     mov    DWORD PTR [esi+0x5864],eax
4d5d87: 89 86 60 58 00 00     mov    DWORD PTR [esi+0x5860],eax
4d5d99: c7 86 68 58 00 00 00  mov    DWORD PTR [esi+0x5868],0x3f000000
4d5daf: c2 08 00              ret    0x8
```

- 最大写偏移是 `[esi+0x586C]`（4B）⇒ 末字节 `0x586F`，终点 `0x5870`。
- 清零常量 `0x161C×4 = 22,640` 与分配立即数、最大写终点**三者逐字节相等**。
- ctor 还以 `operator new(0x44)` 建 6 个 68B 子对象（`gbTextureArray`/`gbRenderEffect` 均为 68），分别存 `0x581C/0x5820/0x5824/0x5828/0x5830/0x5838…0x5844`——与 §3.4 的尾员映射一致。

### 2.3 类身份与 vtable

C2DSpark 无 vtable（注解 `vtables` 为空、`ida_structs` 无 vtable 段、ctor 无 vptr 写），因此不能靠 vtable 判身份；身份由「唯一分配点 + ctor 唯一调用 + dtor 唯一调用 + 成员使用面」共同确定。IDB 把这 9 个方法都挂在 C2DSpark 名下，与调用点分布一致。

### 2.4 方法名错位（只记录）

- `0x4D6380`（IDB 名 `Render`）开头：`cmp BYTE PTR [esi+0x5818],bl`（`m_bMouseTrack`）→ `call 0x4022E0`（取输入/光标）→ 与 `ds:0x17A8438/0x17A843C` 比较 ⇒ 是**鼠标轨迹更新**，不是绘制。
- `0x4D61C0`（IDB 名 `DestroyAll`）函数体内含完整绘制循环（§3.3）：取设备 `ds:0xBFDA60`、建 `m_Quad`、选纹理数组、`call ds:0x56A36C` 提交 512 个元素 ⇒ 是真正的 **Render**。
- 结论：两处名字需要另卡正名（D-2），本卡不动注解。

## §3 48B 命题的闭合检验

### 3.1 三处独立步长（C4/C5）

| 位置 | 指令 | 含义 |
|---|---|---|
| `CreateSingle 0x4D5EC5/0x4D5ECE` | `lea ecx,[ebx+0x29]` / `add ecx,0x2c` | 从元素+0x29 起扫，步长 0x2C |
| `CreateStars 0x4D61A0/0x4D61AB` | `lea eax,[ecx+0x29]` / `add eax,0x2c` | 清 512 个元素的可见位，步长 0x2C |
| `Render 0x4D62B3/0x4D6350` | `lea edi,[esi+0x20]` / `add edi,0x2c` | 绘制循环，步长 0x2C |

元素数：`CreateSingle 0x4D5ED1 cmp eax,0x200`、`CreateStars 0x4D61A3 mov edx,0x200` ⇒ **512**。三处步长/计数互相独立，不可能同时被"48"满足（48≠0x2C）。

### 3.2 整元素拷贝是 11 dword

`CreateSingle` 命中空槽后：

```
4d5ede: 8d 0c 80              lea    ecx,[eax+eax*4]        ; 5i
4d5ee7: 8d 14 48              lea    edx,[eax+ecx*2]        ; 11i
4d5eea: b9 0b 00 00 00        mov    ecx,0xb                ; 11 dword = 44B
4d5eef: 8d 14 93              lea    edx,[ebx+edx*4]        ; 44i
4d5ef4: f3 a5                 rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
4d5ef6: c6 42 29 01           mov    BYTE PTR [edx+0x29],0x1
```

索引乘法链 `i + 10i = 11i`、`×4 = 44i` 与 `rep movs` 的 11 dword 一致 ⇒ 元素 **44B**。

### 3.3 元素字段的真实用法（绘制循环）

```
4d62b3: 8d 7e 20              lea    edi,[esi+0x20]         ; edi = 元素+0x20
4d62b6: 8a 47 09              mov    al,BYTE PTR [edi+0x9]  ; 元素+0x29 可见位
4d62c3: 8a 47 08              mov    al,BYTE PTR [edi+0x8]  ; 元素+0x28 类型 0..3
4d62cf: ff 24 85 68 63 4d 00  jmp    DWORD PTR [eax*4+0x4d6368]
4d62f4: 8b 57 e0              mov    edx,DWORD PTR [edi-0x20] ; 元素+0x00
4d6308: d9 07                 fld    DWORD PTR [edi]          ; 元素+0x20 尺寸
4d630a: d8 47 e0              fadd   DWORD PTR [edi-0x20]
4d630d: d9 9e 50 58 00 00     fstp   DWORD PTR [esi+0x5850]  ; m_Quad.ex
4d631e: 8b 57 f8              mov    edx,DWORD PTR [edi-0x8] ; 元素+0x18 颜色
4d6334: 88 96 6f 58 00 00     mov    BYTE PTR [esi+0x586f],dl
```

- 元素 `+0x00/+0x04` 是 float 坐标（写进 `m_Quad.sx/sy`），`+0x18` 是 float 颜色源（转换成字节写 `m_Quad.color` 位），`+0x20` 是 float 尺寸，`+0x28` 是类型字节（四路跳表选纹理数组），`+0x29` 是可见位。
- 因此现存 12 员的「5 组 texture/wrap + nRenderEffect + pRenderEffect」与实际访问不符；`pRenderEffect@0x2C` 实际落在下一个元素 `+0x00`，是「假设 stride=48」造出的伪成员（D-1）。

### 3.4 尾区 112B 与 m_Quad 闭合（C6）

- `512 × 44 = 22,528 = 0x5800`；尾部 19 个成员从 `0x5800` 开始：
  `0x5800 m_fDisplayWidth`、`0x5804 m_fDisplayHeight`、`0x5808 m_nCurrentSpark`、`0x580C m_fBigLum`、`0x5810/0x5814 m_nBigLumX/Y`、`0x5818 m_bMouseTrack`（+3B 对齐）、`0x581C m_pAdditiveBlend`、`0x5820..0x5844` 五对纹理/数组指针、`0x5848 m_Quad`。
- `0x5848 + 40 = 0x5870`，与 §2.2 的 ctor 终点、§2.1 的分配立即数完全一致；`0x5800 + 112 = 0x5870` 亦一致。
- 注解尾部同样是 112B（`0x6000..0x6070`），但整体比实测高 `0x800 = 512×4`——正好等于"元素 48 而非 44"乘 512。

### 3.5 PDB 的 24,688/48 为什么不能作准

`data/pdb/pdb_export.json` 记 `C2DSpark::tagSpark struct 48`、`C2DSpark union 24688`（C1）。该 PDB 来自 PAL3A（CLAUDE.md 明示：PDB 只能作参考，偏移可能与 PAL3 不同）。本 exe 的三条 A 级链（分配立即数、清零常量、最大写终点）都指向 22,640/44，且 `push 0x6070`、`push 0x6000` 在反汇编缓存中**零命中**（C7）——本 exe 没有 24,688B 的分配。

### 3.6 48 的循环性

`C2DSpark_tagSpark.json` 的 note 自述「Size=48 from array stride (24576/512)」；而 24,576 恰是注解自己把尾部起点写成 `0x6000` 得到的数组长度（`0x6000 − 0x0`）。即：尾部起点 → 数组长度 → 元素尺寸 → 尾部起点，闭环自洽但无独立证据。实测方向相反：元素尺寸 44 → 数组 22,528 → 尾部起点 0x5800 → 总尺寸 22,640。

## §4 结论与影响面

### 4.1 分级

| 结论 | 等级 | 依据 |
|---|---|---|
| `sizeof(C2DSpark)=22,640` | A | 分配立即数 + 清零常量 + 最大写终点三链一致（§2.1/§2.2） |
| `sizeof(tagSpark)=44`、元素数 512 | A | 三处独立步长 + 整元素 11 dword 拷贝 + 512×44 落点（§3.1/§3.2/§3.4） |
| 注解 24,688/48 为派生量 | A | note 自述 + 差值 `2,048 = 512×4`（§3.5/§3.6） |
| 元素字段语义（x/y/颜色/尺寸/类型/可见） | B | 绘制循环与 CreateSingle 写点（§3.3），字段名待另卡取证 |
| PDB 与本体差异原因 | C | 只能判定"PAL3A ≠ 本 exe"，具体字段差异需 PAL3A 侧取证 |

### 4.2 影响面

- 注解：`C2DSpark.binary_size 24,688 → 22,640`；`m_Spark` 元素类型 `C2DSpark_tagSpark[512]` 保持，元素尺寸 `48 → 44`；19 个尾员偏移整体 `−0x800`（`0x6000..0x6048 → 0x5800..0x5848`）。
- `ida_structs.json`：随 apply/export 更新（本卡未跑管线）。
- census：当前无 C2DSpark 条目；重铸后应新增一条 0 洞记录（`0x48..0x58` 那类空隙在本类不存在）。
- 下游：`m_Spark` 的数组步进由 48 改 44 后，任何按 48 计算的索引都会错位——落地卡必须先改元素类型、再改尾员偏移，顺序不可颠倒。

### 4.3 缺口与另卡

- **D-1（元素语义）**：12 员中仅 6 个偏移有使用证据（+0x00/+0x04/+0x18/+0x20/+0x28/+0x29），其余 5 个 dword（+0x08/+0x0C/+0x10/+0x14/+0x1C）与两个尾字节语义未定；`pRenderEffect@0x2C` 是伪成员。需新卡对 `CreateMore` 的源结构（`ds:0x17A8150` 起 44B 写入）逐字段取证后正名。
- **D-2（方法名）**：`0x4D61C0`/`0x4D6380` 名字错位（§2.4），需另卡正名并核对 `DestroyAll` 的真身。
- **G-1**：本卡只覆盖 C2DSpark 自身；其 6 个 68B 子对象（gbTextureArray/gbRenderEffect）的成员语义不在本卡范围。

## §5 复现命令与输出（原样）

### C1 三处记录尺寸

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import json
d=json.load(open('data/annotations/structs/C2DSpark.json')); km=d['known_members']
print('C1 annotation C2DSpark', d['binary_size'], 'bases', d.get('bases'), 'members', len(km))
for k in list(km)[:3]: print('   ', k, km[k]['name'], km[k]['type'])
t=json.load(open('data/annotations/structs/C2DSpark_tagSpark.json')); kt=t['known_members']
print('C1 annotation tagSpark', t['binary_size'], 'members', len(kt), 'note:', t.get('note'))
for k in list(kt)[-2:]: print('   ', k, kt[k]['name'], kt[k]['type'])
s=json.load(open('asm/pal3/ida_structs.json'))
print('C1 idb C2DSpark', s['C2DSpark']['size'], 'tagSpark', s['C2DSpark_tagSpark']['size'], 'gbUIQuad', s['gbUIQuad']['size'], 'gbTextureArray', s['gbTextureArray']['size'])
p=json.load(open('data/pdb/pdb_export.json'))
for c in p['classes']:
    if c.get('name') in ('C2DSpark','C2DSpark::tagSpark'): print('C1 PDB', c['name'], c.get('kind'), c['size'])
PY
```

```
C1 annotation C2DSpark 24688 bases None members 20
    0x0 m_Spark C2DSpark_tagSpark[512]
    0x6000 m_fDisplayWidth float
    0x6004 m_fDisplayHeight float
C1 annotation tagSpark 48 members 12 note: C2DSpark nested struct, originally C2DSpark::tagSpark. Size=48 from array stride (24576/512).
    0x28 nRenderEffect int
    0x2c pRenderEffect int
C1 idb C2DSpark 24688 tagSpark 48 gbUIQuad 40 gbTextureArray 68
C1 PDB C2DSpark::tagSpark struct 48
C1 PDB C2DSpark union 24688
```

### C2 分配点

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import re
txt=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().split('\n')
pat=re.compile(r'^\s*([0-9a-f]{6,8}):')
rows=[(int(m.group(1),16),ln.strip()) for ln in txt for m in [pat.match(ln)] if m]
import re
for a,ln in rows:
    if 0x512ae1<=a<0x512b35 and re.search(r'push\s+0x5870|call\s+0x55353b|mov\s+ecx,eax|call\s+0x4d5ab0|\[esi\+0x34\]',ln): print(ln)
PY
```

```
512ae1:	68 70 58 00 00       	push   0x5870
512af0:	e8 46 0a 04 00       	call   0x55353b
512b19:	8b c8                	mov    ecx,eax
512b1b:	e8 90 2f fc ff       	call   0x4d5ab0
512b30:	89 46 34             	mov    DWORD PTR [esi+0x34],eax
512b33:	e8 03 0a 04 00       	call   0x55353b
```

### C3 ctor 清零常量与最大写

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import re
txt=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().split('\n')
pat=re.compile(r'^\s*([0-9a-f]{6,8}):')
rows=[(int(m.group(1),16),ln.strip()) for ln in txt for m in [pat.match(ln)] if m]
for a,ln in rows:
    if 0x4d5ab0<=a<0x4d5dc0 and re.search(r'rep stos|0x161c|0x586c|0x5868|0x5860|0x5864|ret',ln): print(ln)
PY
```

```
4d5ac4:	b9 1c 16 00 00       	mov    ecx,0x161c
4d5acb:	c7 86 6c 58 00 00 ff 	mov    DWORD PTR [esi+0x586c],0xffffffff
4d5ad5:	89 9e 68 58 00 00    	mov    DWORD PTR [esi+0x5868],ebx
4d5adb:	f3 ab                	rep stos DWORD PTR es:[edi],eax
4d5d77:	c7 86 6c 58 00 00 ff 	mov    DWORD PTR [esi+0x586c],0xffffffff
4d5d81:	89 86 64 58 00 00    	mov    DWORD PTR [esi+0x5864],eax
4d5d87:	89 86 60 58 00 00    	mov    DWORD PTR [esi+0x5860],eax
4d5d99:	c7 86 68 58 00 00 00 	mov    DWORD PTR [esi+0x5868],0x3f000000
4d5daf:	c2 08 00             	ret    0x8
```

### C4 三处步长

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import re
txt=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().split('\n')
pat=re.compile(r'^\s*([0-9a-f]{6,8}):')
rows=[(int(m.group(1),16),ln.strip()) for ln in txt for m in [pat.match(ln)] if m]
for a,ln in rows:
    if a in (0x4d5ec5,0x4d5ed1,0x4d5ece,0x4d5ef6,0x4d61a0,0x4d61a3,0x4d61ab,0x4d62b3,0x4d6350,0x4d65e2): print(ln)
PY
```

```
4d5ec5:	8d 4b 29             	lea    ecx,[ebx+0x29]
4d5ece:	83 c1 2c             	add    ecx,0x2c
4d5ed1:	3d 00 02 00 00       	cmp    eax,0x200
4d5ef6:	c6 42 29 01          	mov    BYTE PTR [edx+0x29],0x1
4d61a0:	8d 41 29             	lea    eax,[ecx+0x29]
4d61a3:	ba 00 02 00 00       	mov    edx,0x200
4d61ab:	83 c0 2c             	add    eax,0x2c
4d62b3:	8d 7e 20             	lea    edi,[esi+0x20]
4d6350:	83 c7 2c             	add    edi,0x2c
4d65e2:	83 c1 2c             	add    ecx,0x2c
```

### C5 整元素拷贝 / 建星循环

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import re
txt=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().split('\n')
pat=re.compile(r'^\s*([0-9a-f]{6,8}):')
rows=[(int(m.group(1),16),ln.strip()) for ln in txt for m in [pat.match(ln)] if m]
for a,ln in rows:
    if 0x4d5ede<=a<0x4d5f11: print(ln)
PY
```

```
4d5ede:	8d 0c 80             	lea    ecx,[eax+eax*4]
4d5ee1:	56                   	push   esi
4d5ee2:	8b 74 24 0c          	mov    esi,DWORD PTR [esp+0xc]
4d5ee6:	57                   	push   edi
4d5ee7:	8d 14 48             	lea    edx,[eax+ecx*2]
4d5eea:	b9 0b 00 00 00       	mov    ecx,0xb
4d5eef:	8d 14 93             	lea    edx,[ebx+edx*4]
4d5ef2:	8b fa                	mov    edi,edx
4d5ef4:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
4d5ef6:	c6 42 29 01          	mov    BYTE PTR [edx+0x29],0x1
4d5efa:	8b 8b 08 58 00 00    	mov    ecx,DWORD PTR [ebx+0x5808]
4d5f00:	5f                   	pop    edi
4d5f01:	3b c1                	cmp    eax,ecx
4d5f03:	5e                   	pop    esi
4d5f04:	7c 07                	jl     0x4d5f0d
4d5f06:	40                   	inc    eax
4d5f07:	89 83 08 58 00 00    	mov    DWORD PTR [ebx+0x5808],eax
4d5f0d:	b0 01                	mov    al,0x1
4d5f0f:	5b                   	pop    ebx
4d5f10:	c2 04 00             	ret    0x4
```

### C6 闭合算术

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
print('512*44 =', 512*44, hex(512*44))
print('0x5800+112 =', hex(0x5800+112), 0x5800+112)
print('0x5848+40 =', hex(0x5848+40))
print('0x6000+112 =', hex(0x6000+112), 0x6000+112)
print('24688-22640 =', 24688-22640, '=', 512*4)
print('0x161C*4 =', 0x161C*4, hex(0x161C*4))
PY
```

```
512*44 = 22528 0x5800
0x5800+112 = 0x5870 22640
0x5848+40 = 0x5870
0x6000+112 = 0x6070 24688
24688-22640 = 2048 = 2048
0x161C*4 = 22640 0x5870
```

### C7 全库无 24,688 分配

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import re
txt=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().split('\n')
for pat in ('0x6070','0x6000'):
    hits=[ln for ln in txt if re.search(r'push\s+'+pat+r'\b',ln)]
    print(pat, len(hits))
PY
```

```
0x6070 0
0x6000 0
```

### C8 census 归属

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import json
d=json.load(open('data/status/struct_holes_20261125.json'))
classes=d['classes']; names={c.get('cls') for c in classes}
print('classes', len(classes), 'C2DSpark' in names, 'C2DSpark_tagSpark' in names)
print('meta', {k:v for k,v in d.get('_meta',{}).items() if k in ('total_hole_bytes','total_holes','classes_with_holes')})
PY
```

```
classes 200 False False
meta {'classes_with_holes': 200, 'total_hole_bytes': 848196, 'total_holes': 1105}
```

### C9 调用点与方法边界

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import re
txt=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().split('\n')
pat=re.compile(r'^\s*([0-9a-f]{6,8}):')
rows=[(int(m.group(1),16),ln.strip()) for ln in txt for m in [pat.match(ln)] if m]
for tgt in ('0x4d5ab0','0x4d5dc0'):
    hits=[ln for a,ln in rows if re.search(r'call\s+'+tgt+r'\b',ln)]
    print(tgt, len(hits), hits)
for a,ln in rows:
    if 0x4d6380<=a<0x4d63a5: print(ln)
PY
```

```
0x4d5ab0 1 ['512b1b:\te8 90 2f fc ff       \tcall   0x4d5ab0']
0x4d5dc0 1 ['512d09:\te8 b2 30 fc ff       \tcall   0x4d5dc0']
4d6380:	83 ec 0c             	sub    esp,0xc
4d6383:	53                   	push   ebx
4d6384:	56                   	push   esi
4d6385:	8b f1                	mov    esi,ecx
4d6387:	33 db                	xor    ebx,ebx
4d6389:	38 9e 18 58 00 00    	cmp    BYTE PTR [esi+0x5818],bl
4d638f:	0f 84 27 01 00 00    	je     0x4d64bc
4d6395:	8d 44 24 08          	lea    eax,[esp+0x8]
4d6399:	b9 70 ad bf 00       	mov    ecx,0xbfad70
4d639e:	50                   	push   eax
4d639f:	e8 3c bf f2 ff       	call   0x4022e0
4d63a4:	8b 4c 24 08          	mov    ecx,DWORD PTR [esp+0x8]
```

## §6 下一张落地卡草案（不改数据，只给输入）

**目标**：把 `C2DSpark` 从 24,688 重铸为 22,640，元素从 48 改 44，尾员整体 −0x800。

**writeScopes**：`data/annotations/structs/C2DSpark.json`、`data/annotations/structs/C2DSpark_tagSpark.json`、`tests/`、`data/status/`（落证物与读数）。

**逐文件改动**：
1. `C2DSpark_tagSpark.json`：`binary_size 48 → 44`；删除 `0x2c pRenderEffect`（伪成员，实际是下一元素 +0x00）；`0x28 nRenderEffect` 待 D-1 取证后再定名/定宽，暂保留并标 unverified。
2. `C2DSpark.json`：`binary_size 24688 → 22640`；`m_Spark` 类型保持 `C2DSpark_tagSpark[512]`；19 个尾员偏移 `−0x800`（`0x6000→0x5800` … `0x6048→0x5848`），成员名与类型不动。
3. 校验：`python tools/audit_type_layout.py --only C2DSpark`、`python pipeline/cli.py check`、`python tools/census_struct_holes.py`（洞账应从"无该类"变为 0 洞）。

**验收读数**（独占窗口）：apply→export→codegen→probe→match 一轮；S2 ≥ 158/229、总错误 ≤ 630、L1 ≥ 189；不重锚四份基线；`git status` 只允许出现上述两个注解文件与 tests/读数文件。

**blockedBy**：`#6`（管线单通道，避免与并发 codegen 抢 IDB）。

**风险**：`m_Spark` 步长变化会同时影响所有按 48 索引的旧代码生成结果——必须先落元素类型再落尾员偏移，顺序颠倒会出现半新半旧布局。
