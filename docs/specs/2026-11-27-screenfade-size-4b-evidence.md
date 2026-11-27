# R4 边界二取证：四个 fade 类各多 4B 的来源与 ScreenEffectMgr 168→152 差

> 任务：#34（tsk_01M8CE6MTRN89Z9VWCCERJ），只读取证。
> 证据口径：注解 = `data/annotations/structs/*.json`（当前工作树）；生成 = 用本仓生成头 `pal3/src/**/*.h` 经 MSVC 6.0（`tools/compilers/msvc6.0`）实测 sizeof/offsetof；二进制 = `original/PAL3.exe` 反汇编（`data/status/_disasm_cache.txt`）。
> 本文件只新增，未改 data/annotations、pal3/src、pipeline、tests、基线，未跑 apply/export/codegen/probe/loop/match。

## 0. 结论

1. **二进制真值与注解一致**：`ScreenFadeIn=28 (0x1C)`、`ScreenFadeOut=24 (0x18)`、`ScreenFadeWhite=24`、`ScreenFadeWhite2=24`；`ScreenEffect=24 (0x18)`（A 级，§2）。
2. **生成头多出的 4B 不是注解写错**：生成 `sizeof = 28/32/28/28/28`（ScreenEffect + 四类），`ScreenEffectMgr = 168`；注解与二进制都是 `24/28/24/24/24`、`152`。
3. **共同机理（四类同因，一次）**：`PalScriptWaitObj` 在注解里是**非多态类**，其 0x0 被记成数据成员 `void* m_nTodo_000`；但二进制里 0x0 是 **vptr**（该类有 3 槽基表 `0x0056AFA4`，见 §3.4）。生成头因此给基类 0 个虚函数槽，而 `ScreenEffect` 又声明了 `virtual ~ScreenEffect()` ⇒ MSVC6 把派生 vfptr 插在 8B 基类**之后**（偏移 8），`ScreenEffect` 全体成员 +4、类 +4；四个派生类各继承这份 +4 ⇒ 生成 32/28/28/28；`ScreenEffectMgr` 内嵌四个子对象 ⇒ 累加 +16 ⇒ 168。
4. **机理已用独立探针复现**（不依赖本仓头文件，§3.2）：占位式 28/12、派生 32/28；把基类改成真多态后 24/8、派生 28/24 —— 与本仓实测逐值吻合。
5. `ScreenEffectMgr = 152` 有第二条独立证据：静态实例 `0xDE7DF8` 与其 guard `0xDE7E90` 间距恰 `0x98 = 152`（§2.3）。
6. **修复落点**：annotation 层把 `PalScriptWaitObj` 建模为多态类（0x0 是 vptr、不再作为数据成员；binary_size 仍 8），并让 `ScreenEffect` 不再另插 vfptr。影响面=以 PSWO 为**主基类**且自带虚函数的类，本仓现役只有 `ScreenEffect` 一族（`Role`/`UICaption` 的主基类分别是 96B/76B 的别类，实测 `sizeof(UICaption)=96` 与注解一致）。该改法**不在本卡落地**，见 §4.5。

## 1. 四类现状表（三列对照）

| 类 | 注解 binary_size | 注解成员（末端） | bases / base_size | vtable | 生成 sizeof（实测） | 二进制真值 | 等级 |
|---|---|---|---|---|---|---|---|
| `ScreenEffect` | 24 (0x18) | 4 员：m_nType@0x8 / m_life@0xC / m_age@0x10 / m_hold@0x14(BYTE) → 0x15 | `PalScriptWaitObj@0` / 8 | 0x0056F4F0（1 槽） | **28** | **24** | A |
| `ScreenFadeIn` | 28 (0x1C) | 1 员：m_first@0x18(int) → 0x1C | `ScreenEffect@0` / 24 | 0x0056F510 | **32** | **28** | A |
| `ScreenFadeOut` | 24 (0x18) | 0 员 | `ScreenEffect@0` / 24 | 0x0056F52C | **28** | **24** | A |
| `ScreenFadeWhite` | 24 (0x18) | 0 员 | `ScreenEffect@0` / 24 | 0x0056F548 | **28** | **24** | A |
| `ScreenFadeWhite2` | 24 (0x18) | 0 员 | `ScreenEffect@0` / 24 | 0x0056F564 | **28** | **24** | A |
| `ScreenEffectMgr` | 152 (0x98) | 16 员，末员 m_nEffectCount@0x94 → 0x98 | 无 bases | 0x0056F508（15 槽） | **168** | **152** | A |

口径说明：
- 「二进制真值」由 ctor 写界 + 内嵌间距 + 实例/guard 间距三条独立闭合给出（§2），不是从注解反推。
- 「生成 sizeof」= 用 `pal3/src/Effect/ScreenEffect.h`、`pal3/src/Misc/ScreenFade*.h`、`pal3/src/Misc/PalScriptWaitObj.h`（后者由 ScreenEffect.h 间接包含）按 MSVC6 `/TP /c /W3 /GX` 编译，靠 `sizeof(X)==N ? 1 : -1` 的 C2118 负下标判定（§5 C2）。
- `ScreenEffect`/四个 fade 都不在 `struct_holes_20261125.json` 的 200 类列表里（无洞条目）；`ScreenEffectMgr` 在，`size=152 / members=16 / holes=[["0x90","0x94",4]] / hole_bytes=4`。

## 2. 尺寸闭合（每类 ≥2 条独立证据）

口径补充（QA 可能问「为什么没有 operator new 立即数」）：
- 四个 fade **没有独立分配点**——它们是 `ScreenEffectMgr` 的内嵌成员，分配只有 Mgr 一处；Mgr 本身也不是 `operator new` 出来的，而是 `0x4BE590 GetInstance` 在静态区 `0xDE7DF8` 上就地构造（`0x4BE59E mov ecx,0xde7df8` → ctor），因此用「实例/guard 间距 0x98」作为等价独立证据（§2.3）。
- 四个 fade 的独立证据是「自身 ctor 写界」+「Mgr 内嵌起点间距」两条，互不依赖。

### 2.1 二进制 ctor 写界（A 级）

| 函数（IDB 名） | 关键指令 | 最大写偏移 | 终点 | 对应 sizeof |
|---|---|---|---|---|
| `ScreenEffect` ctor `0x4BDF10` | `4bdf17 mov [eax],0x56f4f0`；`4bdf1d mov [eax+0x8],1`；`4bdf2a mov BYTE [eax+0x14],cl` | 0x14（BYTE） | 0x15 → 4 对齐 **0x18** | 24 |
| `ScreenFadeIn` ctor `0x4BE8D0` | `4be8d3 call 0x4bdf10`；`4be8d8 mov [esi],0x56f510`；`4be8de mov [esi+0xc],0x40200000`；`4be8e5 mov [esi+0x18],1` | 0x18（DWORD） | **0x1C** | 28 |
| `ScreenFadeOut` ctor `0x4BEA60` | `call 0x4bdf10`；`mov [esi],0x56f52c`；写点最大 `[esi+0x14]` | 0x14 | 0x18（基类 24 定底） | 24 |
| `ScreenFadeWhite` ctor `0x4BEBB0` | `call 0x4bdf10`；`mov [esi],0x56f548`；最大 `[esi+0x14]` | 0x14 | 0x18 | 24 |
| `ScreenFadeWhite2` ctor `0x4BED00` | `call 0x4bdf10`；`mov [esi],0x56f564`；最大 `[esi+0xc]` | 0x0C | 0x18（基类 24 定底） | 24 |
| `ScreenEffectMgr` ctor `0x4BDFB0` | `4be032 mov [esi+0x90],edi`；`4be038 mov [esi+0x94],edi`；`4be03e mov [esi],0x56f508` | 0x94 | **0x98** | 152 |

注：`0x4BE8D0/0x4BEA60/0x4BEBB0/0x4BED00` 都是先 `call 0x4BDF10`（ScreenEffect 基类 ctor，写 0x0..0x14），再写自己的 vptr 与字段 —— 这说明四个 fade 的**基类子对象在 0..0x17**，与 `ScreenEffect=24` 一致。

### 2.2 内嵌间距（Mgr ctor 的四个 `lea ecx,[esi+X]`）

`0x4BDFB0` 体内顺序（逐条已读）：

```
4bdfd0 lea ecx,[esi+0x04] ; 4bdfd3 call 0x4be8d0   ← ScreenFadeIn
4bdfda lea ecx,[esi+0x20] ; 4bdfe1 call 0x4bea60   ← ScreenFadeOut
4bdfe6 lea ecx,[esi+0x38] ; 4bdfee call 0x4bebb0   ← ScreenFadeWhite
4bdff3 lea ecx,[esi+0x50] ; 4bdffb call 0x4bed00   ← ScreenFadeWhite2
```

子对象起点差：`0x20−0x04=0x1C=28`（FadeIn）、`0x38−0x20=0x18=24`、`0x50−0x38=0x18=24`、`0x68−0x50=0x18=24`（FadeWhite2 之后紧接 `m_activeQueue@0x68`）。四个跨度与 §2.1 的 ctor 写界**各自相等**。

### 2.3 静态实例与 guard（Mgr 152 的第二条证据）

`0x4BE590 GetInstance`：`4be590 mov cl,BYTE ds:0xde7e90`；`4be59e mov ecx,0xde7df8`；`4be5a5 mov BYTE ds:0xde7e90,dl`；`4be5bd mov eax,0xde7df8`；`4be5d0 mov ecx,0xde7df8`（`jmp 0x4be080`，atexit）。实例 `0xDE7DF8`、guard `0xDE7E90`，间距 `0xDE7E90−0xDE7DF8 = 0x98 = 152` —— 对象按 152B 排列，后面紧跟 guard。

## 3. 共同机理

### 3.1 观察

- `ScreenEffect` 生成 `sizeof=28`、`offsetof(m_nType)=12`、`offsetof(m_hold)=24`；注解/二进制是 `24 / 8 / 0x14(20)`。即**成员整体 +4**，且多出的 4B 落在基类之后、首成员之前。
- 四个 fade 各自 +4（`ScreenFadeIn` 的 `m_first` 生成在 28，注解/二进制是 0x18=24）。
- `ScreenEffectMgr` 自身成员无额外 +4（`m_fadeIn` 生成 4 = 注解 4），它的 +16 全部来自四个子对象各 +4 的累加。

### 3.2 独立探针（不复用本仓头文件，A 级）

两类形状用同一编译器实测（§5 C7 原样可跑）：

| 形状 | 定义 | sizeof | 首成员偏移 | 派生+int 的 sizeof/偏移 |
|---|---|---|---|---|
| 占位式（复现 bug） | `struct Base{void*p;void*q;}; struct Eff:Base{int a;int b;float c;uchar d; virtual ~Eff(){}};` | **28** | **12** | 32 / 28 |
| 真多态式 | `struct Base{virtual ~Base(){} void*q;}; struct Eff:Base{...}` | **24** | **8** | 28 / 24 |

占位式与本仓生成值逐值相同（28/12、32/28），真多态式与二进制值逐值相同（24/8、28/24）⇒ 「+4」的唯一变量就是**基类有没有 vptr**。

### 3.3 归因（为什么本仓命中占位式）

`PalScriptWaitObj` 注解：`binary_size=8`、`known_members = {0x0: m_nTodo_000(void*), 0x4: m_needscriptdel(gbImage2D*)}`、**没有任何虚函数**（methods 只有 `0x4A68D0 ReleaseObject`，且其自身 `_adjudicated_tables` 注明 `0x0056AFA4` 是「PSWO 型 3 槽第二基表」）。
二进制里 `0x0056AFA4` 被写进对象：`0x44A7B0 mov [esi+0x44],0x56afa4`、`0x44A801 mov [edx],0x56afa4` —— 这类「把 3 槽表写进某个基类子对象首 dword」的形态说明 **PSWO 在二进制里是多态基类，0x0 就是它的 vfptr**；注解把它记成了普通数据成员 `m_nTodo_000`。

于是生成头里 `PalScriptWaitObj` 编译为「无 vptr 的 8B 结构」，而 `ScreenEffect` 声明了 `virtual ~ScreenEffect()` ⇒ 编译器在**基类之后**（偏移 8）插 vfptr，`m_nType` 从 8 变 12，`sizeof` 24→28；四个 fade 继承 `ScreenEffect` 再各带 4B；`ScreenEffectMgr` 四个子对象累加 16。

### 3.4 四假设逐项检验

| 假设 | 判据 | 结论 |
|---|---|---|
| ① 某个 fade 「多了一个 4B 成员」 | 四类注解成员数：FadeIn 1、其余 0；二进制 ctor 写点与注解一致（§2.1）；生成的 32/28/28/28 与「多成员」无关（`m_first` 只是 4B，且它在 FadeIn 内） | **不成立** |
| ② 基类 base_size 多 4 | `ScreenEffect` 注解 base_size=8（PSWO 真值 8，实测 `sizeof(PalScriptWaitObj)=8`）；生成侧 ScreenEffect 是 28 而不是 24，差在 vptr 插入位置 | **成立（本因）**：不是 base_size 数值错，而是基类**非多态**导致派生 vfptr 另占 4B |
| ③ vtable 槽数/对齐 | 对齐为 4（类内最大成员 4B），`0x15→0x18` 已含对齐；若只是对齐不会把 `m_nType` 从 8 推到 12 | **不成立** |
| ④ 注解幻影尾员 | 四类末员分别为 `m_hold@0x14`、`m_first@0x18`、无、无；与 ctor 写界一致 | **不成立** |

四类**同因**：都经由 `ScreenEffect` 继承同一份 +4，没有逐类差异。

## 4. 影响面

### 4.1 ScreenEffectMgr 成员偏移逐项差（编译器实测，decl → 实际，Δ）

| 成员 | 注解 | 生成（实测） | Δ |
|---|---|---|---|
| m_fadeIn | 0x04 | 0x04 | 0 |
| m_fadeOut | 0x20 (32) | 0x24 (36) | +4 |
| m_fadeWhite | 0x38 (56) | 0x40 (64) | +8 |
| m_fadeWhite2 | 0x50 (80) | 0x5C (92) | +12 |
| m_activeQueue | 0x68 (104) | 0x78 (120) | +16 |
| m_pAllocBlock | 0x6C (108) | 0x7C (124) | +16 |
| m_pAllocBlockEnd | 0x70 (112) | 0x80 (128) | +16 |
| m_pAllocPos | 0x74 (116) | 0x84 (132) | +16 |
| m_pAllocSlot | 0x78 (120) | 0x88 (136) | +16 |
| m_pAllocRest | 0x7C (124) | 0x8C (140) | +16 |
| m_nAllocFlag1 | 0x80 (128) | 0x90 (144) | +16 |
| m_nAllocFlag2 | 0x84 (132) | 0x94 (148) | +16 |
| m_fAllocFactor | 0x88 (136) | 0x98 (152) | +16 |
| m_pEffect | 0x8C (140) | 0x9C (156) | +16 |
| `_gap_090` | 0x90 (144) | 0xA0 (160) | +16 |
| m_nEffectCount | 0x94 (148) | 0xA4 (164) | +16 |
| **sizeof** | **152** | **168** | **+16** |

规律：前 4 个成员的 Δ 是「前面已积累的子对象增量」（0/4/8/12），从 `m_activeQueue` 起固定 +16。

### 4.2 对 ctor/dtor 的影响

- 生成态下 `ScreenEffectMgr` ctor 的成员写点全部相对 this 偏移，偏移由编译器按布局算，不读注解常量 ⇒ 生成代码**语义仍正确**（写的是「第 5 个成员」而非「+0x68」），只是 `sizeof` 断言/布局审计失败。
- 但凡是**跨单元按注解偏移硬编码**的代码（如 `_ns_udts.h` 的 `offsetof` 断言、`audit_type_layout` 的门禁）会把 16 个成员全部判为冲突（本卡实测 `audit_type_layout --only ScreenEffectMgr` = 16/16 冲突）。
- `ScreenEffect`/四个 fade 的 dtor 不写界外成员，不受影响。

### 4.3 census 影响

`ScreenEffectMgr` 现 `size=152 / holes=[["0x90","0x94",4]] / hole_bytes=4`；修好后 size 仍是 152（注解本来就对），census 不变。四个 fade 与 `ScreenEffect` 不在 census 200 类中，无洞变化。

### 4.4 下游 RingNode / ScreenEffect

`ScreenEffectRingNode`（#19 落地，363,968B）不含 fade 子对象，不受影响；`ScreenEffect` 自身（24B）在改 PSWO 多态后仍是 24（vptr 移回 0），其成员偏移从 12/16/20/24 回到 8/12/16/20 —— 这正是二进制值。

### 4.5 修复落点（只写方案，不落地）

- **方案 A（推荐，annotation 层）**：把 `PalScriptWaitObj` 建模为多态类——`vtables` 挂 `0x0056AFA4`（3 槽），`known_members` 删去 `0x0 m_nTodo_000`（0x0 是 vptr），`binary_size` 保持 8；`ScreenEffect` 的虚函数自然复用基类 vfptr 槽 0，`sizeof` 回到 24，四个 fade 与 Mgr 全部回到 28/24/24/24/152。
  - 风险：PSWO 有 11 个派生类，需逐一确认「主基类=PSWO 且自带虚函数」的类（现役只有 `ScreenEffect` 族；`Role` base_size=96、`UICaption` base_size=76，实测 `sizeof(UICaption)=96` 与注解一致，不受影响）。改后必须跑 `audit_type_layout --only` 这 6 个类 + `check_annotations` + 洞普查。
  - 前置缺口 **G1**：`0x0056AFA4` 的 3 个槽分别是什么虚函数（签名/语义）尚未取证；本卡只证明「PSWO 有多态表」，没有给槽名。若强行只加 `virtual ~PalScriptWaitObj()` 而不对齐 3 槽，vtable 内容会与二进制不符（但 sizeof 已可修正）；建议下一卡先取证 3 槽再落地。
- **方案 B（不推荐，codegen 层）**：在 `ScreenEffect` 里显式加 `void* __vptr` 并去掉 `virtual` 声明。会破坏虚调用分发，且与「IDB 层能解决的不在 codegen 打补丁」的红线冲突。
- **方案 C（临时）**：只改 `ScreenEffect` 的 `binary_size` 为 24 并强行压成员偏移，会让编译期布局与注解再次分叉，不可取。

## 5. 复现命令与关键输出

> 全部命令在仓库根执行。C2/C6/C7 走 MSVC6 + wine（`pipeline/probe_compile.py` 的 `run_cl`），单条 1–3 分钟；C1/C3/C4/C5 是纯文本解析。

### C0 从本文附录还原探测器

```bash
awk '/^## 附录/{f=1;next} f&&/^```python/{g=1;next} g&&/^```$/{exit} g' \
  docs/specs/2026-11-27-screenfade-size-4b-evidence.md > /tmp/szprobe.py
wc -l /tmp/szprobe.py
```

实测输出：

```
71 /tmp/szprobe.py
```

### C1 注解 / IDB / census 三处数值

```bash
python3 - <<'PY'
import json
for c in ['ScreenEffect','ScreenFadeIn','ScreenFadeOut','ScreenFadeWhite','ScreenFadeWhite2','ScreenEffectMgr']:
    d=json.load(open('data/annotations/structs/%s.json'%c))
    km=d['known_members']; last=max(km, key=lambda k:int(k,16)) if km else None
    print('%-18s ann=%s base_size=%s bases=%s members=%d last=%s %s' % (
        c, d.get('binary_size'), d.get('base_size'),
        [b.get('name') for b in (d.get('bases') or [])], len(km),
        last, km[last]['name'] if last else '-'))
h=json.load(open('data/status/struct_holes_20261125.json'))
for x in h['classes']:
    if x.get('cls','').startswith('Screen') or x.get('cls','').startswith('PalScriptWait'):
        print(x)
PY
```

实测输出（节选）：

```
ScreenEffect       ann=24 base_size=8 bases=['PalScriptWaitObj'] members=4 last=0x14 m_hold
ScreenFadeIn       ann=28 base_size=24 bases=['ScreenEffect'] members=1 last=0x18 m_first
ScreenFadeOut      ann=24 base_size=24 bases=['ScreenEffect'] members=0 last=None -
ScreenFadeWhite    ann=24 base_size=24 bases=['ScreenEffect'] members=0 last=None -
ScreenFadeWhite2   ann=24 base_size=24 bases=['ScreenEffect'] members=0 last=None -
ScreenEffectMgr    ann=152 base_size=None bases=[] members=16 last=0x94 m_nEffectCount
{'cls': 'ScreenEffectNode', 'size': 220, 'members': 2, 'bases': 1, 'holes': [['0x5c', '0xa4', 72], ['0xac', '0xdc', 48]], 'hole_bytes': 120, 'total_holes': 2, 'vptr_slot_exempt': True}
{'cls': 'ScreenEffectRingNode', 'size': 363968, 'members': 13, 'bases': 1, 'holes': [['0x68', '0xa4', 60], ['0xac', '0xb0', 4]], 'hole_bytes': 64, 'total_holes': 2, 'vptr_slot_exempt': True}
{'cls': 'PalScriptWaitTimer', 'size': 16, 'members': 2, 'bases': 0, 'holes': [['0x0', '0x8', 8]], 'hole_bytes': 8, 'total_holes': 1, 'vptr_slot_exempt': True}
{'cls': 'ScreenEffectMgr', 'size': 152, 'members': 16, 'bases': 0, 'holes': [['0x90', '0x94', 4]], 'hole_bytes': 4, 'total_holes': 1, 'vptr_slot_exempt': True}
```

> 说明：`ScreenEffect`/四个 fade 都不在 census 列表里（故无 `ScreenEffect*` 之外的行）；`ScreenEffectNode` 是另一个类（220B，屏效节点），与本卡的 fade 不是同一实体，列出只为说明 census 里 `Screen*` 的取数范围。

### C2 生成头 sizeof（MSVC6 实测）

```bash
python3 /tmp/szprobe.py sizeof      # 探测器源码见 §5 末尾附录
```

实测输出：

```
sizeof(ScreenEffect) = [28]
sizeof(ScreenFadeIn) = [32]
sizeof(ScreenFadeOut) = [28]
sizeof(ScreenFadeWhite) = [28]
sizeof(ScreenFadeWhite2) = [28]
sizeof(ScreenEffectMgr) = [168]
```

### C3 二进制 ctor 写界（从反汇编缓存解析）

```bash
python3 - <<'PY'
import re
lines=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().split('\n')
start={}
for i,l in enumerate(lines):
    m=re.match(r'^\s*([0-9a-f]{6,8}):\t',l)
    if m: start[int(m.group(1),16)]=i
def block(a):
    i=start[a]; out=[]
    for l in lines[i:i+500]:
        out.append(l)
        if re.search(r'\tret\b',l): break
    return out
for a,name in [(0x4bdf10,'ScreenEffect ctor'),(0x4be8d0,'ScreenFadeIn ctor'),(0x4bea60,'ScreenFadeOut ctor'),
               (0x4bebb0,'ScreenFadeWhite ctor'),(0x4bed00,'ScreenFadeWhite2 ctor'),(0x4bdfb0,'ScreenEffectMgr ctor')]:
    b=block(a); best=(-1,'')
    for l in b:
        for m in re.finditer(r'(?:mov|or|and|add)\s+(?:BYTE|WORD|DWORD)?\s*PTR \[(e[a-z]{2})(?:\+(0x[0-9a-f]+))?\]',l):
            d=int(m.group(2),16) if m.group(2) else 0
            if m.group(1) in ('esi','edi','eax','ecx','edx') and d>best[0]: best=(d,l.strip()[:80])
    print('0x%x %-22s lines=%d maxdisp=0x%x  %s' % (a,name,len(b),best[0],best[1]))
PY
```

实测输出：

```
0x4bdf10 ScreenEffect ctor      lines=9 maxdisp=0x14  4bdf2a:	88 48 14             	mov    BYTE PTR [eax+0x14],cl
0x4be8d0 ScreenFadeIn ctor      lines=9 maxdisp=0x18  4be8e5:	c7 46 18 01 00 00 00 	mov    DWORD PTR [esi+0x18],0x1
0x4bea60 ScreenFadeOut ctor     lines=9 maxdisp=0x14  4bea75:	c6 46 14 01          	mov    BYTE PTR [esi+0x14],0x1
0x4bebb0 ScreenFadeWhite ctor   lines=9 maxdisp=0x14  4bebc5:	c6 46 14 01          	mov    BYTE PTR [esi+0x14],0x1
0x4bed00 ScreenFadeWhite2 ctor  lines=8 maxdisp=0xc  4bed0e:	c7 46 0c 00 00 20 40 	mov    DWORD PTR [esi+0xc],0x40200000
0x4bdfb0 ScreenEffectMgr ctor   lines=43 maxdisp=0x94  4be038:	89 be 94 00 00 00    	mov    DWORD PTR [esi+0x94],edi
```

（FadeOut/White 的 `[esi+0x14]` 是 BYTE 写、终点 0x15，但它们的基类 `ScreenEffect` 已占 0..0x17，故类尺寸由基类 24B 定底；White2 的 maxdisp 0x0C 更小，同理。）

### C4 Mgr ctor 的四个子对象入口

```bash
sed -n '/4bdfd0:/,/4bdffb:/p' data/status/_disasm_cache.txt | head -20
```

实测输出：

```
  4bdfd0:	8d 4e 04             	lea    ecx,[esi+0x4]
  4bdfd3:	e8 f8 08 00 00       	call   0x4be8d0
  4bdfd8:	33 ff                	xor    edi,edi
  4bdfda:	8d 4e 20             	lea    ecx,[esi+0x20]
  4bdfdd:	89 7c 24 18          	mov    DWORD PTR [esp+0x18],edi
  4bdfe1:	e8 7a 0a 00 00       	call   0x4bea60
  4bdfe6:	8d 4e 38             	lea    ecx,[esi+0x38]
  4bdfe9:	c6 44 24 18 01       	mov    BYTE PTR [esp+0x18],0x1
  4bdfee:	e8 bd 0b 00 00       	call   0x4bebb0
  4bdff3:	8d 4e 50             	lea    ecx,[esi+0x50]
  4bdff6:	c6 44 24 18 02       	mov    BYTE PTR [esp+0x18],0x2
  4bdffb:	e8 00 0d 00 00       	call   0x4bed00
```

### C5 实例与 guard 间距

```bash
grep -nE "0xde7df8|0xde7e90" data/status/_disasm_cache.txt | head
python3 -c "print(hex(0xde7e90-0xde7df8), 0xde7e90-0xde7df8)"
```

实测输出：

```
240543:  4be590:	8a 0d 90 7e de 00    	mov    cl,BYTE PTR ds:0xde7e90
240548:  4be59e:	b9 f8 7d de 00       	mov    ecx,0xde7df8
240550:  4be5a5:	88 15 90 7e de 00    	mov    BYTE PTR ds:0xde7e90,dl
240555:  4be5bd:	b8 f8 7d de 00       	mov    eax,0xde7df8
240570:  4be5d0:	b9 f8 7d de 00       	mov    ecx,0xde7df8
0x98 152
```

### C6 Mgr 16 员编译期偏移（Δ 表）

```bash
python3 /tmp/szprobe.py mgr
```

实测输出（16 员逐条，实测值见 §4.1 表）：

```
offsetof(ScreenEffectMgr,m_fadeIn) = [4]
offsetof(ScreenEffectMgr,m_fadeOut) = [36]
offsetof(ScreenEffectMgr,m_fadeWhite) = [64]
offsetof(ScreenEffectMgr,m_fadeWhite2) = [92]
offsetof(ScreenEffectMgr,m_activeQueue) = [120]
offsetof(ScreenEffectMgr,m_pAllocBlock) = [124]
offsetof(ScreenEffectMgr,m_pAllocBlockEnd) = [128]
offsetof(ScreenEffectMgr,m_pAllocPos) = [132]
offsetof(ScreenEffectMgr,m_pAllocSlot) = [136]
offsetof(ScreenEffectMgr,m_pAllocRest) = [140]
offsetof(ScreenEffectMgr,m_nAllocFlag1) = [144]
offsetof(ScreenEffectMgr,m_nAllocFlag2) = [148]
offsetof(ScreenEffectMgr,m_fAllocFactor) = [152]
offsetof(ScreenEffectMgr,m_pEffect) = [156]
offsetof(ScreenEffectMgr,m_nEffectCount) = [164]
```

### C7 机理探针（独立于本仓头文件）

```bash
python3 /tmp/szprobe.py mech
```

实测输出：

```
sizeof(EffA) = [28]
offsetof(EffA,m_nType) = [12]
sizeof(FadeA1) = [32]
offsetof(FadeA1,m_first) = [28]
sizeof(EffB) = [24]
offsetof(EffB,m_nType) = [8]
sizeof(FadeB1) = [28]
offsetof(FadeB1,m_first) = [24]
```

对照：EffA 组 = 本仓生成值（28/12、32/28）；EffB 组 = 二进制值（24/8、28/24）。

### C8 PSWO 多态表证据

```bash
grep -nE "0x56afa4" data/status/_disasm_cache.txt
```

实测输出：

```
99002:  44a7b0:	c7 46 44 a4 af 56 00 	mov    DWORD PTR [esi+0x44],0x56afa4
99040:  44a801:	c7 02 a4 af 56 00    	mov    DWORD PTR [edx],0x56afa4
```

## 6. 边界与未覆盖

- 本卡只做只读取证，未改任何注解/代码/基线。取证时点（2026-11-27 01:50）实测：`git status --porcelain` 全仓 73 条 = 48 `??` + 25 `M`，其中 25 条 `M` 全部是并发管线/他人的产物；与本卡直接相关的 5 个证据文件里只有 `data/status/struct_holes_20261125.json` 是 `M`（01:44:37 被并发重写，非本卡改动），`data/annotations/structs/ScreenEffect.json`（mtime 23:36:29）、`ScreenFadeIn.json`（21:22:27）、`PalScriptWaitObj.json`（17:31:21）、`asm/pal3/ida_structs.json`（01:26:59）**均无变更**；本文件自身为 `??`。
- 引用的是 01:26:59 时点的 `ida_structs.json` 与 01:44:37 时点的 census；后续并发刷新可能改变 census 数值，执行修复卡前须当场重取。
- 未取证：`0x0056AFA4` 三个槽的虚函数签名（G1）；PSWO 其余 10 个派生类的生成 sizeof 是否也偏移（只验了 `UICaption=96`，与注解一致；`Role` 未验）。
- 未验证修复后的端到端读数（本卡不跑管线）；§4.5 的验收命令是给下一张卡的输入。

## 7. QA 自检

- [x] 四个 fade 类逐个给真实 sizeof，且每类 ≥2 条独立证据（ctor 写界 + Mgr 内嵌间距 + vtable 归属）。
- [x] 「各多 4B」共同机理明确：基类非多态导致派生 vfptr 另占 4B，四类同因；四假设逐项检验（§3.4）。
- [x] 给出 Mgr 16 员逐项差表（0/+4/+8/+12/+16）与修复落点（annotation 层，方案 A）及风险（G1、11 派生类）。
- [x] 只新增 `docs/specs/2026-11-27-screenfade-size-4b-evidence.md`；未改代码/注解/数据/基线；未跑 apply/export/codegen/probe/loop/match。

## 附录：`/tmp/szprobe.py` 全文（C0 从这里还原）

```python
"""C-profile sizeof/offsetof 探测器：用 C2118（负下标）判定候选值。
用法: python3 /tmp/szprobe.py {sizeof|mgr|mech}"""
import sys, re
sys.path.insert(0, 'pipeline')
import probe_compile as pc

HDR = ['#include "pal3/ida_defs.h"', '#include "globals.h"',
       '#include "Effect/ScreenEffect.h"', '#include "Misc/ScreenFadeIn.h"',
       '#include "Misc/ScreenFadeOut.h"', '#include "Misc/ScreenFadeWhite.h"',
       '#include "Misc/ScreenFadeWhite2.h"', '#include "Effect/ScreenEffectMgr.h"']

def _run(pre, expr, lo, hi, chunk=18):
    found = []
    for i in range(lo, hi, chunk):
        lines = list(pre); line2 = {}; ln = 9000
        for n in range(i, min(i + chunk, hi)):
            ln += 1; line2[ln] = n
            lines.append('#line %d "szprobe"' % ln)
            lines.append('char c_%d[%s==%d?1:-1];' % (n, expr, n))
        open('/tmp/szprobe_tu.cpp', 'w').write('\n'.join(lines) + '\n')
        args = ['/Fo' + pc.wpath('/tmp/szprobe.obj'), pc.wpath('/tmp/szprobe_tu.cpp')] + \
               ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS]
        out, _ = pc.run_cl(args, timeout=300, flags=('/nologo', '/TP', '/c', '/W3', '/GX'))
        bad = set(int(m.group(1)) for m in re.finditer(r'szprobe\((\d+)\)\s*:\s*error C2118', out))
        if 'fatal error' in out:
            raise SystemExit('FATAL: ' + [l for l in out.split('\n') if 'fatal' in l][0])
        found += [n for l, n in line2.items() if l not in bad]
    return found

MECH = ['#include <stddef.h>',
        'struct BaseMemberVptr { void *m_nTodo_000; void *m_needscriptdel; };',
        'struct EffA : BaseMemberVptr { int m_nType; int m_life; float m_age; unsigned char m_hold; virtual ~EffA() {} };',
        'struct FadeA1 : EffA { int m_first; };',
        'struct BaseVirtual { virtual ~BaseVirtual() {} void *m_needscriptdel; };',
        'struct EffB : BaseVirtual { int m_nType; int m_life; float m_age; unsigned char m_hold; };',
        'struct FadeB1 : EffB { int m_first; };']

def _run_mech(expr, lo, hi):
    found = []
    for i in range(lo, hi, 18):
        lines = list(MECH); line2 = {}; ln = 9000
        for n in range(i, min(i + 18, hi)):
            ln += 1; line2[ln] = n
            lines.append('#line %d "szprobe"' % ln)
            lines.append('char c_%d[%s==%d?1:-1];' % (n, expr, n))
        open('/tmp/szprobe_mech.cpp', 'w').write('\n'.join(lines) + '\n')
        args = ['/Fo' + pc.wpath('/tmp/szprobe_mech.obj'), pc.wpath('/tmp/szprobe_mech.cpp'),
                '/I' + pc.wpath('tools/compilers/msvc6.0/Include'), '/I' + pc.wpath('tools/vc6/Include')]
        out, _ = pc.run_cl(args, timeout=300, flags=('/nologo', '/TP', '/c', '/W3', '/GX'))
        bad = set(int(m.group(1)) for m in re.finditer(r'szprobe\((\d+)\)\s*:\s*error C2118', out))
        if 'fatal error' in out:
            raise SystemExit('FATAL: ' + [l for l in out.split('\n') if 'fatal' in l][0])
        found += [n for l, n in line2.items() if l not in bad]
    return found

if __name__ == '__main__':
    what = sys.argv[1] if len(sys.argv) > 1 else 'sizeof'
    if what == 'sizeof':
        for c in ['ScreenEffect', 'ScreenFadeIn', 'ScreenFadeOut', 'ScreenFadeWhite', 'ScreenFadeWhite2', 'ScreenEffectMgr']:
            print('sizeof(%s) =' % c, _run(HDR, 'sizeof(%s)' % c, 0, 400))
    elif what == 'mgr':
        for m in ['m_fadeIn', 'm_fadeOut', 'm_fadeWhite', 'm_fadeWhite2', 'm_activeQueue',
                  'm_pAllocBlock', 'm_pAllocBlockEnd', 'm_pAllocPos', 'm_pAllocSlot', 'm_pAllocRest',
                  'm_nAllocFlag1', 'm_nAllocFlag2', 'm_fAllocFactor', 'm_pEffect', 'm_nEffectCount']:
            print('offsetof(ScreenEffectMgr,%s) =' % m,
                  _run(HDR, 'offsetof(ScreenEffectMgr,%s)' % m, 0, 400))
    elif what == 'mech':
        for e, lo, hi in [('sizeof(EffA)', 16, 40), ('offsetof(EffA,m_nType)', 0, 20), ('sizeof(FadeA1)', 16, 44),
                          ('offsetof(FadeA1,m_first)', 16, 40), ('sizeof(EffB)', 16, 40),
                          ('offsetof(EffB,m_nType)', 0, 20), ('sizeof(FadeB1)', 16, 44), ('offsetof(FadeB1,m_first)', 16, 40)]:
            print(e, '=', _run_mech(e, lo, hi))
```
