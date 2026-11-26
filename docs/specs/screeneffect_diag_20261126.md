# ScreenEffectMgr 363,820B 洞结构诊断与 R4 削减路线（只读）

> **已被取代（superseded）**：本文件是 #10 首版迁移件，现行版为 [`data/status/screeneffect_diag_20261126.md`](../../data/status/screeneffect_diag_20261126.md)。保留作历史首版，勿在此新增内容；后续修订只写 canonical，文档关系见其 §7。

任务：#10（tsk_01M8C019RQ8RPG1JR8MVPD，为 #4 tsk_01M8BWGRZZZQCT9Z1BPSZG 的首版拆分交付；#4 原路径 `data/status/` 被 #8 的整目录写域占用，本报告落 `docs/specs/`，结论不变）。数据源：`data/status/struct_holes_20261125.json`、`asm/pal3/ida_structs.json`、`asm/pal3/decomp/*.json`、`data/status/_disasm_cache.txt`。全程只读：未改 `data/annotations`、`pal3/src`、pipeline 生产文件与任何基线，未跑 apply/export/codegen。

## 0. 结论摘要

1. 该类的「355KB 洞」不是未知结构，而是**类尾部一个内联 `ParticleEffect` 子对象**：ctor 在 `0x4bee60` 末尾执行 `lea ecx,[edi+0x454]; call ParticleEffect::ParticleEffect`，且 `0x454 + sizeof(ParticleEffect)=362,860 = 363,968 = binary_size`，分毫不差。
2. 洞 100% 可由 ctor 反汇编闭合：`0x90..0x94`（4B 未触碰）+ `0x98..0x454`（956B，三段数组初始化 + 两处未触碰）+ `0x454..0x58DC0`（362,860B = ParticleEffect）。
3. R4 只需补一个成员 `ParticleEffect m_particleEffect; // +0x454`，大洞即从 363,816B 塌缩到 956B；剩下的 956B 里 24B（0x98..0xB0）、4B（0x90）、68B（0x410..0x454）无 ctor 触碰，应先诚实留白，前缀两段 6×68B 数组需要命名证据。
4. 另发现一处**与洞无关但会影响 R4 落地的布局疑点**：注解 `bases` 为空，但 ctor 首条实语句（`0x4bee7f`）调用 `PAL3VisNode::PAL3VisNode(this)`（`0x4b6f70`，`ida_structs.json` 中 PAL3VisNode size=88），而 `ProcessEffect` 实测把 `this+0x4/0x20/0x38/0x50` 当带 vptr 的 `ScreenFadeIn` 子对象使用。二者不可能同时成立于同一偏移，需单独取证（见 §3.4），本卡不动。

## 1. 洞清单（与 census 对账）

`data/status/struct_holes_20261125.json` → `classes[cls=ScreenEffectMgr]`：

| 字段 | 值 |
|---|---|
| size | 363,968（0x58DC0） |
| members | 16 |
| bases | 0 |
| holes | `[0x90,0x94,4]`、`[0x98,0x58DC0,363816]` |
| hole_bytes / total_holes | 363,820 / 2 |
| vptr_slot_exempt | true |

对账：`4 + 363,816 = 363,820`，与 `_meta.total_hole_bytes` 中该类份额一致；`0x58DC0 - 0x98 = 363,816`（python 复算见 §5 命令 C1）。

## 2. 前 20 簇（按 ctor 闭合结构细分）

大洞 `0x98..0x58DC0` 按 ctor 反汇编可切成 19 簇，加 `0x90` 共 20 簇。簇尺寸合计 = 363,820，与 census 相等（§5 C2）。

| # | 偏移区间 | 大小 | 形态判定 | 证据等级 | 证据路径 |
|---|---|---|---|---|---|
| 1 | 0x90..0x94 | 4 | 未映射标量/对齐填充（`m_pEffect@0x8c` 与 `m_nEffectCount@0x94` 之间） | B | ctor 与 ProcessEffect 均未触碰 [0x90,0x94) |
| 2 | 0x98..0xB0 | 24 | ctor 只写 `[edi+0xa4]=0`、收尾 `[edi+0xa8]=0`，其余未触碰 ⇒ 未映射头区/填充 | B | `_disasm_cache.txt` 4bee8c、4bef07 |
| 3 | 0xB0..0xF4 | 68 | 记录块：`ArraySort(esi,0xc,4,gbVec3D::ctor)` 在块首构造 4×12B `gbVec3D`（48B），余 20B 未解释 | A | 4bee96–4beeb5：`lea esi,[edi+0xb0]`、`push 0xc/0x4`、`call 0x401810`、`add esi,0x44` |
| 4 | 0xF4..0x138 | 68 | 同上（第 2 块） | A | 同上循环 |
| 5 | 0x138..0x17C | 68 | 同上（第 3 块） | A | 同上循环 |
| 6 | 0x17C..0x1C0 | 68 | 同上（第 4 块） | A | 同上循环 |
| 7 | 0x1C0..0x204 | 68 | 同上（第 5 块） | A | 同上循环 |
| 8 | 0x204..0x248 | 68 | 同上（第 6 块，循环终点 0xB0+6×0x44=0x248） | A | 同上循环 |
| 9 | 0x248..0x28C | 68 | 第二组记录块，同 4×gbVec3D+20B 结构 | A | 4beeb7–4beed7：`lea esi,[edi+0x248]`、`add esi,0x44`、6 次 |
| 10 | 0x28C..0x2D0 | 68 | 同上（第 2 块） | A | 同上循环 |
| 11 | 0x2D0..0x314 | 68 | 同上（第 3 块） | A | 同上循环 |
| 12 | 0x314..0x358 | 68 | 同上（第 4 块） | A | 同上循环 |
| 13 | 0x358..0x39C | 68 | 同上（第 5 块） | A | 同上循环 |
| 14 | 0x39C..0x3E0 | 68 | 同上（第 6 块，终点 0x248+6×0x44=0x3E0） | A | 同上循环 |
| 15 | 0x3E0..0x3EC | 12 | `gbVec3D` 单元素（经 `[0x56a56c]` 闭包直接构造） | A | 4beed9–4beef0：`lea esi,[edi+0x3e0]`、`call [0x56a56c]`、`add esi,0xc`、4 次 |
| 16 | 0x3EC..0x3F8 | 12 | 同上（第 2 个） | A | 同上循环 |
| 17 | 0x3F8..0x404 | 12 | 同上（第 3 个） | A | 同上循环 |
| 18 | 0x404..0x410 | 12 | 同上（第 4 个，终点 0x3E0+4×0xC=0x410） | A | 同上循环 |
| 19 | 0x410..0x454 | 68 | ctor 未触碰；尺寸恰为一个记录块 0x44，疑似第 7 块或尾部填充 | B | 4beef2 直接 `lea ecx,[edi+0x454]`，跳过本区间 |
| 20 | 0x454..0x58DC0 | 362,860 | **内联 `ParticleEffect` 子对象** | A | 4beef2–4beef8：`lea ecx,[edi+0x454]; call 0x4bc760`；0x4bc760 归属见 §3.1（IDB methods 表）；`0x454+362860=0x58DC0` |

关键闭合算式（§5 C3）：`0x454 + 362,860 = 363,968 = ScreenEffectMgr.size`。

## 3. 形态判定与代价

### 3.1 簇 20：内联 ParticleEffect（A 级，确定）

- `ParticleEffect` 在 `asm/pal3/ida_structs.json` 中 size=362,860，bases=[sg_particle_scene@0]。
- `0x4bc760` 的归属：`asm/pal3/ida_structs.json` 的 `ParticleEffect.methods["0x004bc760"]` = `ParticleEffect`（ctor），`evidence_level=A`；`source` 记录 new-ctor 三元组 `push 0x5896C; call 0x55353B(new); mov ecx,eax; call 0x4BC760` @site `0x4C8B05`，SIZE=362860 与 PDB 双源独立一致。**注意：该函数没有对应的 decomp JSON**（`asm/pal3/decomp/` 下无 `*_004bc760.json`），因此本条不引用 decomp 文本，只引 IDB methods 表 + 反汇编调用点。
- 反汇编双重印证：`0x4beef2 lea ecx,[edi+0x454]` / `0x4beef8 call 0x4bc760`（ScreenEffectMgr ctor 内联构造）；`0x4c8b03 mov ecx,eax` / `0x4c8b05 call 0x4bc760`（`operator new(0x5896C)` 之后，独立于本类）。两处调用同一函数，且 `0x5896C = 362,860` 与类尺寸相同。
- `ParticleEffect` 自身在 census 中只剩 1 个 4B 洞（`0x58950..0x58954`），说明其内部已标得相当完整。
- 因此它不是「未映射子对象」，而是**完全可表达的成员**：补 `ParticleEffect m_particleEffect; // +0x454` 即可。
- 影响面：ScreenEffectMgr 的 sizeof 不变（仍 363,968），新成员落在所有现有成员之后（最大现有成员 0x94），无 overlap；风险仅在于 codegen 头会引用 ParticleEffect 类型（需确认头包含关系，见 §3.5）。

### 3.2 簇 3–18：两段 6×68B 记录 + 4×12B 尾部（A 级结构，B 级命名）

- ctor 用 `ArraySort(base, count=0xc, elemSize=4, ctor)`：`ArraySort`（0x401810）实现是 `for i in 0..elemSize: ctor(base); base += count`，即**步长 12B、构造 4 个 12B 对象**（`gbVec3D`，其 ctor 闭包在 `[0x56a56c]`）。
- 每组记录块实际占用 68B（`add esi,0x44`），块首 48B 是 4 个 `gbVec3D`，块尾 20B 无 ctor 触碰。
- 两段各 6 块：`0xB0..0x248`、`0x248..0x3E0`；第三段 4×12B：`0x3E0..0x410`。
- 结构可确定，但**语义名不可从 ctor 得出**：需要看 `ProcessEffect`/`RenderFade*` 对这些块的读写语义（颜色帧？淡入淡出关键帧表？）。按命名铁律不得用 `slot_N`/位置名，故 R4 只提出建模方案、不落名。

### 3.3 簇 1/2/19：未触碰区（B 级，先诚实留白）

- `0x90..0x94`（4B）：`m_pEffect@0x8c`（char*，4B）之后、`m_nEffectCount@0x94` 之前；ctor/ProcessEffect 均未触碰 ⇒ 对齐填充或未使用。
- `0x98..0xB0`（24B）：ctor 只写 `0xa4`、`0xa8` 两个 dword 为 0，其余无写入。
- `0x410..0x454`（68B）：ctor 直接跳到 0x454，说明本区间不被构造；尺寸恰为一个记录块（0x44），存在「少构造一块」或「尾部填充」两种解释，需新证据。
- 三处按命名铁律只能 `m_unk_<offset>` 留白，不能编造语义。

### 3.4 布局疑点（与洞无关，但会挡住 R4 落地）

- ctor 首条实语句 `call 0x4b6f70`（`0x4bee7f`，SEH 序言之后）= `PAL3VisNode::PAL3VisNode`（decomp 文件名与签名均确认），而 `ida_structs.json` 中 `PAL3VisNode.size=88`。
- 但 `ProcessEffect`（0x4be1a0）实测：`lea ebp,[esi+0x4]` / `[esi+0x20]` / `[esi+0x38]` / `[esi+0x50]` 后 `mov edx,[ebp]; call [edx+0xc]`（虚调用），即 +0x4/+0x20/+0x38/+0x50 是**自带 vptr 的 ScreenFadeIn 子对象**（与注解 `m_fadeIn@0x4`、`m_fadeOut@0x20`、`m_fadeWhite@0x38`、`m_fadeWhite2@0x50` 一致）。
- 若 ScreenEffectMgr 真以 PAL3VisNode(88B) 为基类，这四个子对象就落在基类区间内，矛盾。
- 结论：要么 `0x4b6f70` 不是基类构造（复用 ctor 设置 vptr 后又被 `[edi]=0x56f580` 覆盖），要么该类没有 PAL3VisNode 基类。**需单独取证**（vtable 0x56f580 的槽位/类型、`[0x56a3b0]` 间接调用目标、`0x56f37c` 归属），本卡不下结论，也不改 `bases`。
- 风险提示：若按 #8 的 bases 修复路线给 ScreenEffectMgr 补 bases，可能把现有 16 个成员整体推后，制造新的 offset 漂移 ⇒ 该类必须走独立取证，不能套用 #8。

### 3.5 落地前置检查（给后续实现卡）

1. `ParticleEffect` 是否有完整注解与头文件发射（`data/annotations/structs/ParticleEffect.json` 存在、`ida_structs.json` 有 size）。
2. 头包含方向：`ScreenEffectMgr` 头需要能见到 `ParticleEffect` 定义（避免前向声明导致的 incomplete type）。
3. `check_annotations` 的 union/overlap 检查：新成员 0x454 与现有成员无交集，预期通过。
4. codegen 后必须跑 `audit_type_layout --only ScreenEffectMgr`：sizeof 应保持 363,968，`offsetof(m_particleEffect)==0x454`。

## 4. R4 削减路线

### 4.1 先补（A 级证据，可直接落 annotation）

| 动作 | 预计收益 | 风险 |
|---|---|---|
| 补 `ParticleEffect m_particleEffect; // +0x454` | 洞 363,816B → 956B（−99.74%） | 低：无 overlap、sizeof 不变；需确认头包含 |

### 4.2 需命名证据后再补（结构已明，名字未定）

| 区间 | 建模建议 | 缺什么 |
|---|---|---|
| 0xB0..0x248 | `结构体 m_recA[6]`（每项 4×gbVec3D + 20B 保留） | 从 `ProcessEffect`/`RenderFade*` 取语义读写证据后命名 |
| 0x248..0x3E0 | `结构体 m_recB[6]`（同上） | 同上 |
| 0x3E0..0x410 | `gbVec3D m_vecC[4]` | 同上（4 个是否同一数组） |

### 4.3 诚实留白（B 级，暂不命名）

`0x90..0x94`（4B）、`0x98..0xB0`（24B）、`0x410..0x454`（68B）→ `m_unk_0x90` / `m_unk_0x98` / `m_unk_0x410`，等新证据再正名。

### 4.4 需新二进制探针（C 级）

1. `0x410..0x454` 的 68B：查 `ProcessEffect`/`Render`/`ClearAllEffects` 是否以 `0x410` 为基址访问（`_disasm_cache.txt` 全量 grep `+0x410`/`+0x41`）。
2. 每块尾部 20B：查 `0xB0+0x30` 起的字段读写。
3. 布局疑点 §3.4：`0x56f580` vtable 槽位、`[0x56a3b0]` 目标、`0x56f37c` 归属。

### 4.5 建议拆卡

- **卡 A（低风险，先做）**：ScreenEffectMgr 补 `ParticleEffect m_particleEffect` + `m_unk_*` 三处留白；验收：洞 363,820 → 956B，sizeof 不变，audit_type_layout 通过。
- **卡 B（命名）**：两段 6×68B 记录 + 4×gbVec3D 的语义取证与命名；验收：每条命名带 decomp/汇编证据链。
- **卡 C（布局疑点）**：ScreenEffectMgr 的 bases/PAL3VisNode 关系定谳；验收：给出 ctor 首调与 0x4 子对象共存的解释或修正方案。

## 5. 复现命令

```bash
# C1 洞清单与总数
python - <<'PY'
import json
d=json.load(open('data/status/struct_holes_20261125.json'))
e=[x for x in d['classes'] if x['cls']=='ScreenEffectMgr'][0]
print(e)                      # holes [[0x90,0x94,4],[0x98,0x58dc0,363816]] size 363968
print(hex(e['size']), e['hole_bytes'], 0x58dc0-0x98)
PY

# C2 20 簇尺寸合计 = hole_bytes（实测输出 363820 0x58d2c True）
python - <<'PY'
import json
e=[x for x in json.load(open('data/status/struct_holes_20261125.json'))['classes']
   if x['cls']=='ScreenEffectMgr'][0]
clusters=[0x4,0x18]+[0x44]*6+[0x44]*6+[0xc]*4+[0x44]+[0x5896c]
print(sum(clusters), hex(sum(clusters)), sum(clusters)==e['hole_bytes'])
PY

# C3 内联 ParticleEffect 闭合
python - <<'PY'
print(hex(0x454+362860), 0x454+362860==363968)   # 0x58dc0 True
PY

# C4 ctor 证据
sed -n '/^  4bee60:/,/^  4bef20:/p' data/status/_disasm_cache.txt | tail -40

# C5 ParticleEffect ctor 归属（IDB methods 表 + 两处调用点；该函数无 decomp JSON）
python - <<'PY'
import json
s=json.load(open('asm/pal3/ida_structs.json'))
m=s['ParticleEffect']['methods']['0x004bc760']
print(m['name'], m['flags'], m['evidence_level'])
print(m['source'][:60])
print(s['ParticleEffect']['size'], s['ParticleEffect']['bases'], s['ScreenEffectMgr']['size'])
PY
grep -n -B4 "call   0x4bc760" data/status/_disasm_cache.txt | head -12
```

## 6. 边界与未覆盖

- 未改任何生产文件/基线；本文件是唯一新增。
- 未做：前缀数组的语义命名（缺证据）、0x410 区的新探针（本卡只读现有 census/decomp/汇编缓存）、§3.4 布局疑点的定谳。
- 未跑 apply/export/codegen/probe/match。
