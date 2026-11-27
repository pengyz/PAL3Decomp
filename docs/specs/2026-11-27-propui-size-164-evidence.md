# R6④ PropUI 尺寸差 164 判别性证据（只读）

- 任务：`tsk_01M8CCQRW2XZG5BFGYBX4B`（#31），只读取证，不建卡、不改数据。
- 证据源：`original/PAL3.exe`、`data/status/_disasm_cache.txt`、`asm/pal3/ida_structs.json`、
  `data/annotations/structs/PropUI.json`、`data/status/struct_holes_20261125.json`、
  `data/pdb/pdb_export.json`、`data/audit/2026-11-26-r6-decision-brief.md`。
- 口径：偏移/尺寸均为**本 exe**（PAL3.exe）实测；PDB 为 PAL3A，仅作参考级（C）。

## §0 结论

1. **PropUI 本 exe 的真实 `sizeof` = 28,892 = `0x70DC`**（A 级，两条独立证据闭合：
   两处 `push 0x70DC` → `operator new` → 同一 ctor `0x46D140`；ctor 最大写偏移 `0x70D8`，
   终点 `0x70D9`，按 4 对齐 = `0x70DC`）。
2. **164 = `0x7180 − 0x70DC` 不是对齐填充、不是另一个对象混入，而是注解尾部模型多算**：
   `52B`（`0x70DC..0x7110`，落在注解假设的 `mb_OK UIButton` 内）+ `16B`（`mb_OKRc tagRECT@0x7110`）
   + `96B`（`0x7120..0x7180` 尾洞）。
3. `mb_OKRc@0x7110` 是**越界幻影成员**（`0x7110 ≥ 0x70DC`，且全库对 `0x70DC` 以上**零单基址访问**，
   A 级否证），应从 `known_members` 删除。
4. 注解 `binary_size=29,056` 与 PDB `29,384`（PAL3A）**均无本 exe 分配支撑**；29,056 的构成是
   「成员末端 `0x7120` + 96B 无成员尾垫」，属注解层派生物，不是二进制尺寸。
5. 影响面：`binary_size` 真值 29,056→28,892（−164），但**不能单独落地**——`mb_OK@0x6FB8`
   （UIButton 344B，末 0x7110）仍越界 52B，尺寸须与尾部成员重排成对改（§3.2/§4）；
   `known_members` 95→94 只是计数变化，单独执行不构成合法布局；
   census 洞预期 18,652B/45 段 → 18,540B/44 段（**须重跑 census 为准**）；
   无内嵌/数组依赖（两处分配都是指针成员 `[esi+0xCC0]` / `[esi+0x6D4]`）。

## §1 命题与出处

### 1.1 #17 ④ 原文

`docs/audit/2026-11-26-r6-decision-brief.md:114`：

> **决策问题**：`PropUI` 的真实 sizeof 是金表 28,892 还是注解 29,056；两处 `InitUI@PropUI` new 的是否同一类；
> 注解末端 28,960 超金表 68B 是尾部多算还是金表对象是派生/子对象。

同文 `:120-121` 给出两个操作数：注解 `binary_size=29,056`；金表 `28,892=0x70DC` ×2、
`?InitUI@PropUI`、site `0x45975e`/`0x523431`。

### 1.2 五个数字与出处

| 数字 | 含义 | 出处 | 等级 |
|---|---|---|---|
| 29,056 = `0x7180` | 注解 `binary_size`（IDB 照抄） | `data/annotations/structs/PropUI.json`（mtime 11-24 21:20）、`asm/pal3/ida_structs.json` | B（注解） |
| 28,960 = `0x7120` | 注解成员末端（`mb_OKRc@0x7110` + 16B） | 同上 | B（注解派生） |
| 28,892 = `0x70DC` | 两处 `operator new` 立即数 | `_disasm_cache.txt:119071`、`:377289` | **A** |
| 28,892 = `0x70DC` | ctor `0x46D140` 写界终点（`0x70D8`+1 对齐） | `_disasm_cache.txt` ctor 区段 | **A** |
| 29,384 = `0x72C8` | PDB（PAL3A）`PropUI` union 尺寸 | `data/pdb/pdb_export.json` | C（参考） |

### 1.3 164 的算式

```
164 = 29,056 − 28,892 = 0x7180 − 0x70DC
    = 52 (0x70DC..0x7110) + 16 (mb_OKRc) + 96 (0x7120..0x7180)
68  = 28,960 − 28,892 = 0x7120 − 0x70DC   （简报所说「超金表 68B」= 52 + 16）
```

## §2 尺寸闭合

### 2.1 分配点（两处，同一尺寸同一 ctor，A 级）

```
45974f: 68 dc 70 00 00        push   0x70dc
45975e: e8 d8 9d 0f 00        call   0x55353b          ; operator new(28,892)
459763: 83 c4 04              add    esp,0x4
459777: 8b c8                 mov    ecx,eax
459779: e8 c2 39 01 00        call   0x46d140          ; PropUI ctor
45978b: 89 86 c0 0c 00 00     mov    [esi+0xcc0],eax

523422: 68 dc 70 00 00        push   0x70dc
523431: e8 05 01 03 00        call   0x55353b
523449: 8b c8                 mov    ecx,eax
52344b: e8 f0 9c f4 ff        call   0x46d140          ; 同一个 ctor
52345f: 89 86 d4 06 00 00     mov    [esi+0x6d4],eax
```

`push 0x70dc` 全库仅此 2 命中（`grep -nE "push\s+0x70dc"` = 2）；两处 new 后跟**同一个 ctor `0x46D140`**
⇒ 「两处 `InitUI@PropUI` 是否同类」的答案是**是**，且尺寸即时数 `0x70DC`。

### 2.2 ctor 写界（A 级）

ctor 区段 `0x46D140..0x46D4B6`（196 条），对象写入最大位移：

```
46d410: 89 9e b4 70 00 00   mov [esi+0x70b4],ebx
46d416: 89 9e b8 70 00 00   mov [esi+0x70b8],ebx
46d41c: 89 9e bc 70 00 00   mov [esi+0x70bc],ebx
46d422: 88 9e c0 70 00 00   mov BYTE PTR [esi+0x70c0],bl
46d428: 88 9e c1 70 00 00   mov BYTE PTR [esi+0x70c1],bl
46d42e: 89 9e c4 70 00 00   mov [esi+0x70c4],ebx
46d434: c7 86 c8 70 00 00 00 80 3f  mov DWORD PTR [esi+0x70c8],0x3f800000
46d43e: 89 9e cc 70 00 00   mov [esi+0x70cc],ebx
46d49f: c6 86 d8 70 00 00 01  mov BYTE PTR [esi+0x70d8],0x1     ; 最大写
46d4b6: c3                 ret
```

最大写 `0x70D8`（1B）⇒ 终点 `0x70D9`，按 4 对齐 `0x70DC` = 28,892，与分配立即数**逐字节相等**。

### 2.3 类身份（vptr，A 级）

```
46d444: c7 06 88 b6 56 00   mov DWORD PTR [esi],0x56b688
```

`0x56B688` 正是注解 `PropUI.vtables[0].addr`（7 槽：`0x445E70` / Render `0x43DDF0` /
Update `0x46F620` / HideAll `0x43DE40` / `0x445B90` / dtor `0x46D4C0` / OnMessage `0x46F650`）
⇒ ctor `0x46D140` 构造的确实是 PropUI（当前 IDB 把它命名为 `InitUI` 是错的，见 §4）。

### 2.4 否证：`0x70DC` 以上零访问 + 尾部真实布局（A 级）

对 `data/status/_disasm_cache.txt`（1.27M 行）做**单基址**引用扫描 `[<reg>+disp]`（排除 `[reg+reg*n+disp]` 数组形）：

```
单基址引用落在 0x70D0..0x7180 的共 30 条，位移只有三种：0x70D0 / 0x70D4 / 0x70D8
  - 写：0x46D49F [esi+0x70d8]=1（ctor）、0x46EC08 [esi+0x70d0]=edx、0x46EBEE [esi+0x70d4]=ecx
  - 读：0x46DFD5 / 0x46E081 / 0x46E0D1 / 0x46E1CF / 0x46E32F / 0x46E3C2 / 0x46E503 / 0x46E5E5 /
        0x46E753 / 0x46E7E2 / 0x46E820 / 0x46E85F / 0x46E937 / 0x46E9C1 / 0x46E9EB / 0x46EA2D /
        0x46EA8A / 0x46F2D6 / 0x46F2E5 / 0x46F756 / 0x470365 / 0x470374 / 0x470384 / 0x470393 /
        0x4703A2 / 0x4703B2 / 0x470911（均为 0x70D0 / 0x70D4 / 0x70D8）
  ⇒ 0x70DC..0x7180 区间：0 条访问
```

带缩放索引的 `[edx+esi*1+0x710c]` 共 13 处（`0x45CE3C`/`0x45F199`/`0x466894`/`0x467539` 等），
base 是另一对象的数组指针 + 运行期索引，**不是 PropUI 本体**，不能当作 `PropUI+0x710C` 的证据。

同一 ctor 还给出尾部真实构造（与注解模型冲突）：

```
46d3f7: 8d 8e 1c 70 00 00   lea ecx,[esi+0x701c]
46d402: e8 d9 4e fd ff      call 0x4422e0        ; UIFrameContainer(152B) 构造/复位 → 止于 0x70B4
46d410..46d43e              11 个标量写 0x70B4/0x70B8/0x70BC/0x70C0/0x70C1/0x70C4/0x70C8/0x70CC
46d49f: [esi+0x70d8]=1
```

⇒ 注解假设的 `mb_OK UIButton@0x6FB8`（本 exe UIButton=344B，止于 `0x7110`）在 `0x701C` 处
会覆盖一个 UIFrameContainer、在 `0x70B4..0x70D8` 会覆盖 11 个标量 —— **该成员模型与 ctor 写点冲突**，
这是「尾 68B」与「164」的结构性来源（详见 §3.2）。

## §3 164 的性质

| # | 假设 | 判据 | 结论 |
|---|---|---|---|
| A | 类尾对齐填充 | `0x70DC` 已是 4 对齐；`0x7180 − 0x70DC = 0xA4` 不是任何 2 的幂对齐产物；且 `0x70DC..0x7180` 无成员无访问 | **否** |
| B | 成员表多算 | `mb_OKRc tagRECT@0x7110` 越界 68B（`0x7110 ≥ 0x70DC`）且零访问；`mb_OK@0x6FB8` 344B 模型与 ctor 写点冲突 | **是**（52+16=68B） |
| C | 另一个对象的尺寸混入 | 两处分配都是 `0x70DC` + 同一 ctor `0x46D140`；`0x710C` 的数组访问属另一对象（缩放索引基址不同）；PDB 29,384/注解 29,056 无本 exe 分配 | **否** |
| D | 注解末端算术（尾垫） | 注解 `binary_size` 恰为成员末端 `0x7120` + 96B（`0x7120..0x7180` 无成员、无访问） | **是**（96B） |

### 3.1 分段表

| 区间 | 长度 | 注解模型 | 二进制实况 |
|---|---|---|---|
| `0x70DC..0x7110` | 52B | `mb_OK UIButton` 的尾部 | 无成员、零访问（越界） |
| `0x7110..0x7120` | 16B | `mb_OKRc tagRECT` | 无成员、零访问（越界） |
| `0x7120..0x7180` | 96B | 尾洞（census 已记） | 无成员、零访问（尾垫） |

合计 52+16+96 = **164**。

### 3.2 尾部真实结构（供下一张卡重排用）

按 ctor 写点，`0x701C` 起是：UIFrameContainer（`0x98`，止 `0x70B4`）→ 标量
`0x70B4`(4)、`0x70B8`(4)、`0x70BC`(4)、`0x70C0`(1)、`0x70C1`(1)、`0x70C4`(4)、
`0x70C8`(float 1.0)、`0x70CC`(4)、`0x70D0`(4)、`0x70D4`(4)、`0x70D8`(1) → 对象止 `0x70DC`。
注解在这些偏移上没有成员（被 `mb_OK@0x6FB8` 344B 与 `mb_OKRc@0x7110` 覆盖），
所以「删 164B」不能单独执行；尺寸修正必须与尾部重排成对（本卡不改名、不编名）。

**可执行性约束（本节与 §4 一致）**：`mb_OK@0x6FB8` 在本 exe 是 `UIButton`（344B），
末端 `0x6FB8+0x158=0x7110`；若只把 `binary_size` 改成 `0x70DC` 并删 `mb_OKRc`，
`mb_OK` 仍越过新尺寸 **52B**（`0x70DC..0x7110`），`audit_type_layout` / `check` 会报成员越界。
因此**尺寸修正与尾部成员重排必须成对执行**，单改尺寸不是合法布局。

## §4 结论与影响面

- `binary_size` 真值：29,056 → **28,892**（−164，A 级）。但**不可单独落地**：现有末员
  `mb_OK UIButton@0x6FB8`（本 exe UIButton=344B）末端 `0x7110 > 0x70DC`，若只改 `binary_size`
  并删 `mb_OKRc`，`mb_OK` 仍越界 **52B**，`audit_type_layout` / `check` 必然报成员越界
  （§3.2「可执行性约束」）。
- `known_members` 95 → **94**：这只是计数随删除 `mb_OKRc tagRECT@0x7110` 的变化，
  **单独执行不构成合法布局**，不能据此拆卡。
- 下一张落地卡（草案，重排优先，尺寸与成员成对改）：writeScopes=
  `data/annotations/structs/PropUI.json`、`tests/`；必做三件事成对落地——
  ① 按 §3.2 重排 `0x6FB8..0x70DC` 区间：`mb_OK` 重定位/缩短或删除（依据 `0x701C` UIFrameContainer
  与 `0x70B4..0x70D8` 11 个标量），`mb_OKRc@0x7110` 删除；
  ② 同一次提交把 `binary_size` 改为 `28892`；③ 新增回归测试断言
  `max(member_end) <= binary_size` 且 `sizeof(PropUI)==28892`。
  验收：`python tools/audit_type_layout.py --only PropUI`、`python pipeline/cli.py check`、
  `python tools/census_struct_holes.py`（洞 ≤18,540B/44）、独占窗口 `python pipeline/cli.py loop`
  （S2 不低于当前基线、无新增错误）；不重锚四份基线。
  停止条件：若 `mb_OK` 无法在有证据下重定位，则**只提交区间重排取证结论、保持 `binary_size` 不变**，
  不得先改尺寸再补成员。
- census：现 `{"size":29056,"members":95,"hole_bytes":18652,"total_holes":45}`，末洞 `["0x7120","0x7180",96]`；
  成对改动后预期 `hole_bytes≈18,540`、`total_holes≈44`（**派生值，须以重跑 census 为准**）。
- 下游：两个分配点都是指针成员（`[esi+0xCC0]`、`[esi+0x6D4]`），无内嵌/数组依赖；
  `data/annotations/structs/*.json` 中无以 `PropUI` 为成员类型的类（grep `"PropUI"` 除自身 0 命中）。
- 方法命名：`0x46D140` 现名 `InitUI` 实为 ctor（两处 new 后直调 + 写 vptr）；`0x46D4C0/0x46D4E0`
  为 deleting/complete dtor —— 改名属注解层，另卡处理。

## §5 复现命令与关键输出

C1 两处分配点：

```bash
grep -nE "push\s+0x70dc" data/status/_disasm_cache.txt
```
```
119071:  45974f:	68 dc 70 00 00       	push   0x70dc
377289:  523422:	68 dc 70 00 00       	push   0x70dc
```

C2 ctor 写界与 vptr：

```bash
python3 - <<'PY'
import re
rows=[(int(m.group(1),16),l) for l in open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace')
      for m in [re.match(r'^\s*([0-9a-f]{6,8}):',l)] if m]
seg=[(a,l) for a,l in rows if 0x46d140<=a<0x46d4c0]
offs=[int(m.group(2),16) for a,l in seg for m in re.finditer(r'\[(esi|edi|ebx)\+0x([0-9a-f]+)\]',l)]
print('rows',len(seg),'max [reg+disp]',hex(max(offs)))
print([l.split('\t')[-1].strip() for a,l in seg if '[esi],0x56b688' in l or '0x70d8],0x1' in l])
PY
```
```
rows 196 max [reg+disp] 0x70d8
['mov    DWORD PTR [esi],0x56b688', 'mov    BYTE PTR [esi+0x70d8],0x1']
```

C3 单基址引用只到 0x70D8：

```bash
python3 - <<'PY'
import re
rx=re.compile(r'\[(e[a-z]{2})(\+0x([0-9a-f]+))\]')
offs=set()
for l in open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace'):
    for m in rx.finditer(l):
        o=int(m.group(3),16)
        if 0x70d0<=o<=0x7180: offs.add(o)
print(sorted(hex(o) for o in offs))
PY
```
```
['0x70d0', '0x70d4', '0x70d8']
```

C4 五数对照：

```bash
python3 - <<'PY'
import json
a=json.load(open('data/annotations/structs/PropUI.json'))
s=json.load(open('asm/pal3/ida_structs.json'))['PropUI']
c=[x for x in json.load(open('data/status/struct_holes_20261125.json'))['classes'] if x['cls']=='PropUI'][0]
p=[x for x in json.load(open('data/pdb/pdb_export.json'))['classes'] if x['name']=='PropUI'][0]
km={int(k,16):v for k,v in a['known_members'].items()}
print('annot',a['binary_size'],'members',len(km),'last',hex(max(km)))
print('idb',s['size'],'census',c['size'],c['members'],c['hole_bytes'],c['total_holes'],c['holes'][-1])
print('pdb',p['kind'],p['size'])
print('164',hex(0x7180-0x70dc),0x7180-0x70dc,'68',hex(0x7120-0x70dc),0x7120-0x70dc)
PY
```
```
annot 29056 members 95 last 0x7110
idb 29056 census 29056 95 18652 45 ['0x7120', '0x7180', 96]
pdb union 29384
164 0xa4 164 68 0x44 68
```

C5 尾部真实构造（UIFrameContainer@0x701C + 标量）：

```bash
python3 - <<'PY'
import re
rows=[(int(m.group(1),16),l.split('\t')[-1].strip()) for l in open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace')
      for m in [re.match(r'^\s*([0-9a-f]{6,8}):',l)] if m]
for a,l in rows:
    if 0x46d3f7<=a<0x46d4c0 and ('[esi+0x701c]' in l or 'call   0x4422e0' in l or re.search(r'\[esi\+0x70[bcd][0-9a-f]\]',l)):
        print(hex(a),l)
PY
```
```
0x46d3f7 lea    ecx,[esi+0x701c]
0x46d402 call   0x4422e0
0x46d410 mov    DWORD PTR [esi+0x70b4],ebx
0x46d416 mov    DWORD PTR [esi+0x70b8],ebx
0x46d41c mov    DWORD PTR [esi+0x70bc],ebx
0x46d422 mov    BYTE PTR [esi+0x70c0],bl
0x46d428 mov    BYTE PTR [esi+0x70c1],bl
0x46d42e mov    DWORD PTR [esi+0x70c4],ebx
0x46d434 mov    DWORD PTR [esi+0x70c8],0x3f800000
0x46d43e mov    DWORD PTR [esi+0x70cc],ebx
0x46d49f mov    BYTE PTR [esi+0x70d8],0x1
```

C6 无内嵌依赖：

```bash
grep -rn '"PropUI"' data/annotations/structs/ | grep -v '/PropUI.json:' | wc -l
```
```
0
```

C7 方法表与 vtable：

```bash
python3 - <<'PY'
import json
s=json.load(open('asm/pal3/ida_structs.json'))['PropUI']
print([ (k,v.get('name')) for k,v in sorted(s['methods'].items()) if 0x46d000<=int(k,16)<0x470000 ])
print([ (v['addr'],v.get('base')) for v in s['vtables']])
PY
```
```
[('0x0046d140', 'InitUI'), ('0x0046d4c0', '~PropUI'), ('0x0046d4e0', '~PropUI'), ('0x0046dd10', 'UpdateItemList'), ('0x0046df40', 'InitPlayerList'), ('0x0046ec30', 'SetSlotLock'), ('0x0046ec50', 'CheckMode'), ('0x0046ec70', 'SetSceneStates'), ('0x0046ecc0', 'DisplayItemInfo'), ('0x0046f160', 'UpdateCaptions'), ('0x0046f300', 'UpdateItemDetail'), ('0x0046f3d0', 'GetInputFlag'), ('0x0046f620', 'Update'), ('0x0046f650', 'OnMessage')]
[('0x0056b688', 'UIWnd')]
```

## §6 只读边界

- 只跑 `grep`/`python3` 读 `_disasm_cache.txt`、注解 JSON、`ida_structs.json`、census、PDB；
  **未跑** apply/export/codegen/probe/loop，未改任何 `data/annotations`、`pal3/src`、`pipeline`、基线。
- 本卡唯一新增文件即本文档；`data/status/s4_baseline.json`（mtime 00:53:08 的 `M`）与
  `data/status/struct_holes_20261125.json`（mtime 00:53:22 的 `M`）均为并发管线所写，非本卡改动；
  `data/annotations/structs/PropUI.json` mtime 仍为 11-24 21:20、`asm/pal3/ida_structs.json` 无改动。

## §7 QA 自检

| # | 要求 | 落点 |
|---|---|---|
| 1 | 164 及候选尺寸逐个给出处 | §1.2 表（A/B/C 分级）、C4 |
| 2 | ≥2 条独立闭合 | §2.1 分配立即数、§2.2 ctor 写界、§2.3 vptr、§2.4 零访问否证 |
| 3 | 归属双向吻合 | §2.3 vptr 0x56B688 ↔ 注解 vtable；两处分配 → 同一 ctor；C6 无内嵌 |
| 4 | 只新增本文档、不改数据/基线、不跑管线 | §6 |
| 5 | 下一卡输入可执行（不给出必然失败的最小改动） | §3.2「可执行性约束」+ §4：尺寸与尾部重排成对改，单改尺寸被 `mb_OK` 52B 越界阻断 |
