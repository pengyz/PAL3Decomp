# ScreenEffectMgr 956B 前缀簇取证包（#11）

> 只读取证。证据源：`original/PAL3.exe`（经 `data/status/_disasm_cache.txt` 反汇编投影）、
> `asm/pal3/ida_structs.json`（IDB 导出）、`asm/pal3/decomp/*.json`、`data/status/struct_holes_20261125.json`。
> 未跑 apply/export/codegen/probe/match，未改 `data/annotations/**`、代码或基线。
> 段偏移与 #4 报告 `data/status/screeneffect_diag_20261126.md` §2 对齐。
> 任务：`tsk_01M8C198JA2KAB61Z1D5A3`。

## §0 结论摘要

1. **956B = 0x98..0x454**，分 5 段：`0x98..0xB0`(24) + `0xB0..0x248`(408) + `0x248..0x3E0`(408) +
   `0x3E0..0x410`(48) + `0x410..0x454`(68)，合计 956，与 census 洞
   `[0x98,0x58DC0,363816]` 减 `ParticleEffect.size=362860` 一致（§1）。
2. **census 的「洞」= 注解没有成员覆盖，不等于二进制未使用**。五段中除 `0x98/0x9C/0xA0/0xAC`
   四字外都有实际读写点（§2–§6）；把它们当 padding 处理会丢真实字段。
3. **#4 §3.4 定谳：IDB `ScreenEffectMgr` 把两个类的成员合并到了同一个结构里**，
   不是「PAL3VisNode 基类标错」也不是「fade 偏移标错」（§7）。363,968B 这个类（下称 **B**）
   确实以 PAL3VisNode 为基类；`m_fadeIn@0x4 … m_nEffectCount@0x94` 这 16 个成员属于另一个类
   （下称 **A**：单例，vtable `0x56F508`，实例 `0xDE7DF8`，ctor `0x4BDFB0`，dtor `0x4BE080`）。
4. 可直接落 annotation 的 A 级结构：两段 `6×0x44` 元素数组（每元素前 `0x30`=4×gbVec3D 已由
   ctor 的 `ArrayCtor(base,12,4,gbVec3D ctor)` 证明）、`0x3E0` 的 `gbVec3D[4]`、`0x454`
   的 `ParticleEffect` 内联成员。元素语义名**没有**使用点级证据，按命名铁律留白（B 级）。
5. 下一张填充卡必须先**拆两类归属**再补成员（§8）；只补 `m_particleEffect@0x454` 能把 363,816B
   降到 956B，但会继续把 A 的 16 个错挂成员留在 B 上，属治标。

## §1 段对账（与 #4 报告 §2 一致）

| 段 | 偏移 | 大小 | 形态判定 | 关键证据 | 等级 |
|---|---|---|---|---|---|
| ① 小字段 | `0x98..0xB0` | 24 | 2 个 int + 16B 未使用 | ctor 只写 `+0xA4`/`+0xA8`；其余 4 字在 B 方法域无访问 | A（边界）/ B（语义） |
| ② 数组一 | `0xB0..0x248` | 408 | `6 × 0x44` 元素 | ctor `lea esi,[edi+0xb0]; ebx=6` + `ArrayCtor(…,12,4,…)` | A |
| ③ 数组二 | `0x248..0x3E0` | 408 | `6 × 0x44` 元素，与②同型 | ctor 同型循环 `lea esi,[edi+0x248]; ebx=6` | A |
| ④ 向量块 | `0x3E0..0x410` | 48 | `gbVec3D[4]` | ctor `ebx=4` 逐元素 `call ds:[0x56A56C]`，步长 `0xC` | A |
| ⑤ 参数块 | `0x410..0x454` | 68 | 含颜色/浮点/内嵌容器的数据块（非填充） | Render/UpdateAnimation/LoadResources 多处读写（§6） | B（结构未定） |
| ⑥ 内联粒子 | `0x454..0x58DC0` | 362860 | `ParticleEffect`（既有结论） | ctor `lea ecx,[edi+0x454]; call ctor`；dtor 对称 | A |

算术：`0x454-0x98 = 0x3BC = 956`；`0x454 + 362860 = 363968 = binary_size`。

## §2 ① `0x98..0xB0`（24B）

- ctor `0x4BEE60`：`0x4BEE8C mov dword [edi+0xA4],0`、`0x4BEF07 mov dword [edi+0xA8],0`。
- `0xA4` 另有 `0x4BF11B mov dword [esi+0xA4],1`（Create 路径置 1）、`0x4BF19E` 回写；
  `0xA8` 另有 `0x4BF0ED`(写)、`0x4BF17D/0x4BF189/0x4BF2A2/0x4BF2B0/0x4BF2FF/0x4BF320/0x4BF37E/0x4BF45E/0x4BF4CE`(读)。
  ⇒ `0xA4`/`0xA8` 是两个 4B 标量（疑似开关 + 计数/句柄），**有使用点，不是 padding**。
- `0x98/0x9C/0xA0/0xAC`：在 B 的方法域（`0x4BEE60..0x4BF7FF`、`0x52F310..0x52F32F`）全量扫描
  无 `[reg+disp]` 命中（§9 C6）⇒ 目前只能留白（B 级，可能为对齐/预留）。
- 命名：`0xA4/0xA8` 语义未定 ⇐ 无类型级证据，按铁律用 `m_unk_0xA4`/`m_unk_0xA8` 或取证后再命名，
  禁止 `m_nFlag_0A4` 这类地址后缀伪装名。

## §3 ② `0xB0..0x248`（6 × 0x44 = 408B）

- ctor 循环（`0x4BEE96..0x4BEEB5`）：
  `lea esi,[edi+0xB0]`；`mov ebx,6`；循环体 `push ds:[0x56A56C]; push 4; push 0xC; push esi;
  call 0x401810; add esi,0x44; dec ebx; jne`。
  `0x401810` 是 `ArrayCtor(base, count=12, elemSize=4, ctorFn)`（#4 报告 §3.1 已列），
  故每元素前 `0x30` = **4 个 12B `gbVec3D`**，元素步长 `0x44`（`add esi,0x44`）。
- `LoadResources 0x4BEFB0`：`0x4BEFD0..0x4BEFEA` 调 `0x4B63C0(41.0f,28.0f,50.0f,6,base,6)`；
  helper 内部 `fcos/fsin`（`0x4B6424`/`0x4B6435`）按 `add ecx,0x44` 步长写每元素的向量/标量
  ⇒ 元素尾部的 `0x14`B 里至少含一个 float 参数（`41/28/50` 三值按元素分布）。
- 元素尾：`0x4BF033 mov dword [eax-5],0x3F70A3D7`（=0.94f，落在元素 `+0x3C`）；
  `0x4BF028..0x4BF02F` 写 `+0x40/+0x41/+0x42` 三字节 `0x1C/0xBC/0xF5`（颜色/权重形态）。
  ⇒ 元素 = `4×gbVec3D(0x00..0x30)` + `0x30..0x44` 尾部（含 float@0x3C、3 字节@0x40..0x42）。
- 长度 6 的来源：ctor 立即数 `ebx=6` + `LoadResources` 两次 `push 6`，两处一致。

## §4 ③ `0x248..0x3E0`（6 × 0x44 = 408B）

- ctor 同型循环（`0x4BEEB7..0x4BEED7`）：`lea esi,[edi+0x248]; ebx=6`，同一个 `0x401810`、同一步长。
- `LoadResources` 第二次调用（`0x4BEFF4..0x4BF00E`）：`0x4B63C0(34.0f,18.0f,68.0f,6,base,6)`
  —— 与②**同型、参数不同**（41/28/50 vs 34/18/68）。
- 颜色循环（`0x4BF016..0x4BF054`）在同一次迭代里**同时写两段数组**：`eax=esi+0xF1` 时
  `[eax-1]/[eax]/[eax+1]` 命中②元素 `+0x40..+0x42`，`[eax+0x197..0x199]` 命中
  `0x288..0x28A` = ③元素 `+0x40..+0x42`（`0x43/0xE3/0x0A`）。
  ⇒ 两段是**同一元素类型的并行两套 6 元数组**（A 级结构）。
- 语义（第二套是内圈/外圈或前后景）需要额外使用点证据，本卡不命名。

## §5 ④ `0x3E0..0x410`（4 × 0xC = 48B）

- ctor 循环（`0x4BEED9..0x4BEEF0`）：`lea esi,[edi+0x3E0]; ebx=4`；循环体
  `mov ecx,esi; call ds:[0x56A56C]; add esi,0xC; dec ebx`。
  `0x56A56C` 与②③的 `ArrayCtor` 回调是同一构造器指针 ⇒ 每元素 12B = `gbVec3D`。
- `LoadResources 0x4BF062..0x4BF0A9` 依次写 `0x3E0..0x40C` 共 12 个 dword：
  `0x42100000`(36.0)/`0xC2100000`(-36.0)/`0x3F800000`(1.0)/0 —— 12 个 float 覆盖
  `0x3E0..0x410`，与 `4×gbVec3D` 完全吻合。
- 结论：`gbVec3D m_unk_3E0[4]`（结构 A 级；语义命名待证）。

## §6 ⑤ `0x410..0x454`（68B）

有真实读写的字段（全部 `this` 相对，`esi/edi` = ScreenEffectMgr）：

| 偏移 | 访问 | 证据 |
|---|---|---|
| `0x410` | 写 0 | `0x4BF0B5` |
| `0x414` | 写 0 | `0x4BF0AF` |
| `0x418` | 写 1.0f | `0x4BF0C1` |
| `0x41C` | 写 1.0f | `0x4BF0BB` |
| `0x420` | 写 `0xFFFFFFFF`；按字节写 `0x420/0x421/0x422` | `0x4BF0C7`、`0x4BF4C4`；`0x4BF467/0x4BF46D/0x4BF473` |
| `0x424` | `fadd [edi+0x424]` / `fst` / 置 4.0f | `0x4BF519/0x4BF51F/0x4BF531` |
| `0x428` | 取址 `lea ebx,[esi+0x428]` 传入调用 | `0x4BF3CE` |
| `0x444` | 取址 `lea ecx,[esi+0x444]` 传入调用；另写指针 | `0x4BF3C0`、`0x4BF53B` |

判定：**68B 是一个复合数据块，不是对齐填充**；`0x420` 是颜色 DWORD、`0x424` 是随时间累加的
float、`0x428/0x444` 是内嵌子结构（取址传参）。结构未定（B 级）：填充卡里不能当标量数组，
建议先按 `BYTE m_unk_0x410[0x44]` 保占位，或先做一次 `0x428/0x444` 被调函数的类型取证。

## §7 ⑥ 定谳：`0x454` 边界、vptr、§3.4 两类合并

### 7.1 `0x454` 边界（A 级）

- ctor：`0x4BEEF2 lea ecx,[edi+0x454]` / `0x4BEEF8 call 0x4BC760`（ParticleEffect ctor，
  `_disasm_cache.txt:241509-241510`）。
- dtor：`0x4BEF80 lea ecx,[esi+0x454]` / `0x4BEF8B call 0x4BC7B0`（ParticleEffect dtor）。
- `0x454 + 362860 = 363968` = 结构 `binary_size` ⇒ `0x454` 是最后一个内联成员，后面再无字段。

### 7.2 vptr 与基类（A 级）

- B 的 ctor 在**成员构造完成后**写自有 vptr：`0x4BEF01 mov dword [edi],0x56F580`；
  dtor 同样先写 `0x4BEF6D mov dword [esi],0x56F580`。
- 基类构造/析构对称：ctor `0x4BEE7F call 0x4B6F70`（PAL3VisNode ctor，写 `[esi]=0x56F37C`、
  `[esi+0x58]=0`）；dtor `0x4BEF9A call 0x4B6FB0`（PAL3VisNode 内层 dtor，释放 `+0x1C`）。
  ⇒ **B : PAL3VisNode 成立**，`bases=[]` 是注解缺口而非事实。

### 7.3 §3.4 矛盾的定谳（A 级）

IDB 里 `ScreenEffectMgr` 的 16 个成员（`0x4 m_fadeIn` … `0x94 m_nEffectCount`）**不属于 B**：

1. B 的 ctor 只写 `0xA4`、`0xA8`、`0xB0`、`0x248`、`0x3E0`、`0x454`，**从不触碰 `0x4..0x94`**（§2–§7.1）。
2. 另有一个单例类 **A**：实例 `0xDE7DF8`，guard 字节 `0xDE7E90`；`GetInstance 0x4BE590` 内
   `call 0x4BDFB0`（ctor），atexit 注册 `0x4BE5D0 → 0x4BE080`（dtor）。
3. A 的 ctor `0x4BDFB0` 在 `+4/+0x20/+0x38/+0x50` 依次 `call 0x4BE8D0/0x4BEA60/0x4BEBB0/0x4BED00`
   构造四个子对象（`ScreenFade*`），随后清 `+0x68..+0x94`，最后
   `0x4BE03E mov dword [esi],0x56F508` 写 A 的 vtable。
4. A 的方法使用 `+0x94`（队列计数）与 `+4/+0x20/+0x38/+0x50`（fade 子对象），
   例 `ProcessEffect 0x4BE1A0` 的 `switch(n-1)` 由 `lea ebp,[esi+0x4/0x20/0x38/0x50]` 选目标后
   `mov edx,[ebp]; call [edx+0xC]`（虚调用，`0x4BE1D8-0x4BE1DF`）；`ClearAllEffects 0x4BE080`
   用 `+0x94` 计数、`+0x6C..+0x7C` 分配器、`+0x8C` 缓冲，并在尾部以
   `lea ecx,[esi+0x50]/[+0x38]/[+0x20]/[+0x4]` 走四个 fade 子对象的入口（`0x4BE157..0x4BE179`）。

⇒ 结论：**`m_fadeIn@0x4` 与 PAL3VisNode 基类不是同一对象的两个视图，而是两个类被合并进一个
IDB 结构**。`ScreenEffectMgr` 的成员表需要先拆分（A 的 16 个成员迁出），B 的基类补
`PAL3VisNode`，B 的真实成员从 `0x5C` 起（`0x5C` float / `0x60` dword / `0x64` dword，本卡不展开）。

### 7.4 连带发现（B 级，需另一张卡）

`PAL3VisNode.binary_size=88` 与自身 ctor 的 `mov dword [esi+0x58],0`（`0x4B6F7F`）及 getter
`0x4B7020 mov eax,[ecx+0x58]` 冲突 ⇒ 真实 size 至少 `0x5C`(92)。不影响本卡段边界（`0xB0` 起算），
但影响 B 的 `0x5C..0x98` 区域解释，建议单独立项。

## §8 下一张填充卡草案（只写草案，不改 data/annotations）

**标题**：ScreenEffectMgr 拆类 + 956B 前缀填充（B 侧）
**writeScopes**：`data/annotations/structs/ScreenEffectMgr.json`、`data/annotations/functions.json`
（A 方法归属迁出）、`tests/test_annotation_read_single_point.py` 同目录下新增布局回归、
`docs/specs/2026-11-26-screeneffect-prefix-evidence.md`（本文件，引用）。
**不动**：`pal3/src/**`、`pipeline/**`、基线文件。

步骤（每步独立可回滚）：

1. **拆类**：把 A 的 16 个成员与 A 的方法（`0x4BDFB0..0x4BE5DA` 段：StartFade/ClearAllEffects/
   ProcessEffect/GetInstance/IsFadeWhiteHolding/DrainQueue/AllocEffectBlock/GetFadeFlags/
   RenderFadeOut/ToggleFade/StartFadeIn/RenderFadeIn/RenderFadeWhiteOut/RenderFadeWhiteIn）
   迁到 A 自己的 struct 条目；B 的 `bases` 补 `PAL3VisNode`。
2. **B 的前缀小字段**：`m_unk_0xA4`/`m_unk_0xA8`（int）；`0x98/0x9C/0xA0/0xAC` 继续留白。
3. **两段数组**：新增元素类型 `struct ScreenEffectElem_unk { gbVec3D v[4]; float f_3C; BYTE rgb_40[3]; BYTE pad_43; }`
   （`0x44` 字节，字段名先 `unk`，取证后再正名），B 侧声明 `ScreenEffectElem_unk m_unk_0xB0[6]`、
   `m_unk_0x248[6]`。
4. **向量块**：`gbVec3D m_unk_0x3E0[4]`。
5. **参数块**：先 `BYTE m_unk_0x410[0x44]` 占位（结构未定，见 §6），或先取证 `0x428/0x444` 再落。
6. **内联粒子**：`ParticleEffect m_particleEffect;` @`0x454`（既有 A 级归属）。

**洞收敛算法**：`363816 →（补 0x454）956 →（补 §3–§5 与 §2 两字）0x98..0xB0 剩 16B →（0x410 块定名）0`。
**验收**：`sizeof(ScreenEffectMgr)==363968` 不变；`struct_holes` 的 `hole_bytes` 从 363816 降到目标值；
`apply→export` 后 `ida_structs.json` 时间戳更新；`audit_type_layout --only ScreenEffectMgr` 通过；
不重锚 `s4_baseline.json`。
**风险**：迁出 A 的成员会改变 `functions.json` 归属与 vtable 槽名解析，可能波及其他类的
`base_size` 推导；回滚 = `git checkout` 两个 json + 重跑 `apply→export`（不许只 checkout 不重跑，
否则 IDB 保留已落库类型）。

## §9 复现命令与输出

```bash
# C1 census 洞
python3 - <<'EOF'
import json
d=json.load(open('data/status/struct_holes_20261125.json'))
v=[c for c in d['classes'] if c.get('cls')=='ScreenEffectMgr'][0]
print(v['size'], v['holes'], v['hole_bytes'])
EOF
# 期望 ScreenEffectMgr 363968 holes [[0x90,0x94,4],[0x98,0x58dc0,363816]] hole_bytes 363820

# C2 段算术
python3 -c "print(hex(0x454-0x98), 0x454-0x98, 0x454+362860)"

# C3 ctor 关键三条
grep -n -E "4bee96:|4beea1:|4beeb7:|4beed9:|4beef2:|4beef8:|4bef01:" data/status/_disasm_cache.txt

# C4 dtor 基类与粒子析构
grep -n -E "4bef80:|4bef8b:|4bef9a:" data/status/_disasm_cache.txt

# C5 A 的 ctor/析构与单例
grep -n -E "4bdfd0:|4bdfda:|4bdfe6:|4bdff3:|4be03e:|4be5ab:" data/status/_disasm_cache.txt

# C6 B 方法域内 0x98..0xB0 的访问点（应只命中 0xA4/0xA8）
python3 - <<'EOF'
import re
pat=re.compile(r'^\s*([0-9a-f]{5,8}):.*?\[(e?[a-z]{2,3})(?:\+0x([0-9a-f]+))?\]')
for line in open('data/status/_disasm_cache.txt',errors='ignore'):
    m=pat.match(line)
    if not m: continue
    a=int(m.group(1),16)
    if not (0x4bee60<=a<0x4bf800): continue
    if m.group(3) and 0x98<=int(m.group(3),16)<0xb0: print(line.rstrip())
EOF
```

实测输出（2026-11-26 本机）：

- C1：`363968 [['0x90', '0x94', 4], ['0x98', '0x58dc0', 363816]] 363820`
- C2：`0x3bc 956 363968`
- C3：`4bee96 lea esi,[edi+0xb0]` / `4beea1 push ds:0x56a56c` / `4beeb7 lea esi,[edi+0x248]` /
  `4beed9 lea esi,[edi+0x3e0]` / `4beef2 lea ecx,[edi+0x454]` / `4beef8 call 0x4bc760` /
  `4bef01 mov [edi],0x56f580`
- C4：`4bef80 lea ecx,[esi+0x454]` / `4bef8b call 0x4bc7b0` / `4bef9a call 0x4b6fb0`
- C5：`4bdfd0 lea ecx,[esi+0x4]` / `4bdfda lea ecx,[esi+0x20]` / `4bdfe6 lea ecx,[esi+0x38]` /
  `4bdff3 lea ecx,[esi+0x50]` / `4be03e mov [esi],0x56f508` / `4be5ab call 0x4bdfb0`
- C6：仅 `0x4bee8c +0xa4`、`0x4bef07 +0xa8`、`0x4bf0ed +0xa8`、`0x4bf11b +0xa4`、
  `0x4bf17d +0xa8`、`0x4bf189 +0xa8`、`0x4bf19e +0xa4`、`0x4bf2a2 +0xa8`、`0x4bf2b0 +0xa8`、
  `0x4bf2ff +0xa8`、`0x4bf320 +0xa8`、`0x4bf37e +0xa8`、`0x4bf45e +0xa8`、`0x4bf4ce +0xa8`

## §10 证据等级与缺口

- **A 级**（指令直证）：段边界与尺寸；`6×0x44` 与 `4×0xC` 的构造循环与步长；`0x454` 边界；
  B 的 vptr 写入与 PAL3VisNode 基类构造/析构对称；A/B 两类分离（不同 vtable、不同 ctor、成员互不重叠）。
- **B 级**（结构成立、语义未定）：两段元素的语义名；`0xA4/0xA8` 语义；`0x410` 块结构；
  `PAL3VisNode` size 应为 92。
- **明确缺口**：`0x428/0x444` 被调函数未展开（其真实类型未知）；`0x5C/0x60/0x64` 字段语义未取证
  （不在本卡 956B 内，但影响 B 的完整成员表）；A 类的真实语义名（当前 IDB 缩写挂在
  `ScreenEffectMgr` 名下）需 `misattribution_ledger` 流程。
- **边界**：本文件只新增；未改 `data/annotations/**`、代码、基线。实测 `git status --porcelain`
  对本文件为 `??`，四份基线（`s4_baseline.json`/`s4_diff_detail.json`/`compile_baseline.json`/
  `baselines/latest.json`）与 `asm/pal3/ida_structs.json` 无输出（未改）；工作区另有他人改动
  （`data/annotations/structs/RoleStatePanel.json`、`UIFrameContainer.json` 属 #8 在办，非本卡）。
