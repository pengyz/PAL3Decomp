# R4 边界二落地施工图：四个 fade 类各减 4B 与 ScreenEffectMgr 168→152

> 卡：#39 `tsk_01M8CJ3SJ09SHVX217PJPV`（只读施工图，不改仓库）
> 上游证据：#34 `docs/specs/2026-11-27-screenfade-size-4b-evidence.md`（已验收）
> 本图只回答「改哪个文件、改哪个字段、怎么验、失败怎么退」，不执行任何改动。

---

## §0 结论摘要

1. **四个 fade 类的注解值本来就是对的**（ScreenFadeIn 28 / FadeOut 24 / ScreenFadeWhite 24 / ScreenFadeWhite2 24），ScreenEffect 24、ScreenEffectMgr 152 也都对。错的是**编译期布局**：生成侧多出 4B（Mgr 多 16B）。
2. 根因唯一：基类 `PalScriptWaitObj` 被注解建模成**非多态**（`0x0 m_nTodo_000 void*` 当普通数据成员）。派生类一旦声明虚函数，MSVC 就在 offset 0 插 vfptr、基类子对象整体后移 4。
3. 因此**改动不落在四个 fade 的 JSON 上**，只落在 `data/annotations/structs/PalScriptWaitObj.json`（+ 一处重复表清理 `UICaption.json`）。
4. 方案 A（推荐）：把 PSWO 建模为多态——删 `0x0` 成员、加 `vtables:[0x0056AFA4, 3 槽]`、`binary_size` 仍 8。自包含模型探针实测：PSWO 8 / ScreenEffect 24（`m_nType@8`）/ FadeIn 28（`m_first@24`）/ FadeOut·White·White2 24 / **Mgr 152**（16 员偏移 4·0x20·0x38·0x50·0x68·0x6C…0x94）。
5. **阻断项 G1（必须先解决）**：`0x56AFA4` 的三个槽在 IDB 与注解里**只有地址、没有方法名**；而命名铁律禁止 `slot_N` / `_todo_` 占位。方案 A 必须把这 3 个虚函数声明在 PSWO 上 ⇒ 落地前必须先给三槽正名（另开取证小卡）。不自行编名。
6. 方案 B（每类加 `void* m_pVtable` 数据成员）**不能解决问题**：ScreenEffect 自身声明了 `virtual ~ScreenEffect()`，编译器照样在 offset 0 插 vfptr，成员仍在 12。已用探针否证（§5.2）。

---

## §1 四类目标表（真值 / 注解 / 生成 / 4B 机理）

### 1.1 目标值（二进制真值，来源 #34 §2，A 级）

| 类 | 真 sizeof | 关键成员末端 | 二进制证据（#34 原文） |
|---|---|---|---|
| `ScreenEffect` | **24 (0x18)** | `m_nType@8`、`m_life@0xC`、`m_age@0x10`、`m_hold@0x14` | ctor `0x4BDF10` 最大写 `[eax+0x14]`，终点 0x18 |
| `ScreenFadeIn` | **28 (0x1C)** | `m_first@0x18` | ctor `0x4BE8D0` 写 `[esi+0x18]=1`，终点 0x1C |
| `ScreenFadeOut` | **24 (0x18)** | 无自有成员 | ctor `0x4BEA60` 最大写 `[esi+0x14]` |
| `ScreenFadeWhite` | **24 (0x18)** | 无自有成员 | ctor `0x4BEBB0` 最大写 `[esi+0x14]` |
| `ScreenFadeWhite2` | **24 (0x18)** | 无自有成员 | ctor `0x4BED00` 最大写 `[esi+0x0C]` |
| `ScreenEffectMgr` | **152 (0x98)** | `m_nEffectCount@0x94` | ctor `0x4BDFB0` 最大写 `[esi+0x94]`；实例 `0xDE7DF8` 与 guard `0xDE7E90` 间距 0x98 |

### 1.2 现状三列对照

| 类 | 注解 `binary_size` | 生成 sizeof（#34 §2 实测） | 差 | 备注 |
|---|---|---|---|---|
| `ScreenEffect` | 24 | **28** | +4 | `m_nType` 生成在 12（真值 8） |
| `ScreenFadeIn` | 28 | **32** | +4 | `m_first` 生成在 28（真值 24） |
| `ScreenFadeOut` | 24 | **28** | +4 | — |
| `ScreenFadeWhite` | 24 | **28** | +4 | — |
| `ScreenFadeWhite2` | 24 | **28** | +4 | — |
| `ScreenEffectMgr` | 152 | **168** | **+16** | 四个 fade 子对象各 +4，4×4=16；生成间距 0x1C/0x18/0x18/0x18 |

### 1.3 4B 机理（四类同因）

- `PalScriptWaitObj` 注解把 `0x0` 当成数据成员、且没有任何 `vtables` ⇒ codegen 生成的是**纯数据类**（`pal3/src/Misc/PalScriptWaitObj.h` 里就是 `void* m_nTodo_000; gbImage2D* m_needscriptdel;`，无 `virtual`）。
- `ScreenEffect` 注解声明了 `vtables:[0x0056F4F0]`（`emit_headers.py:4376/:4416` 的 `has_vtable`）⇒ codegen 发出 `virtual ~ScreenEffect()`；基类非多态 ⇒ 编译器把 vfptr 放 offset 0、PSWO 子对象挤到 +4 ⇒ 成员整体 +4。
- 不是「多一个成员」、不是对齐、也不是幻影尾员：#34 §3.4 已逐项否证，并做了最小机理探针（占位式基类 28/12 → 派生 32/28；真多态基类 24/8 → 派生 28/24），变量只剩「基类有没有 vptr」。

---

## §2 改动表（精确到 JSON 字段；本卡只写不执行）

### 2.1 `data/annotations/structs/PalScriptWaitObj.json`（唯一的结构性改动）

现状（mtime 11-23 17:31）：

```json
{
  "name": "PalScriptWaitObj",
  "binary_size": 8,
  "known_members": {
    "0x0": {"name": "m_nTodo_000", "type": "void *"},
    "0x4": {"name": "m_needscriptdel", "type": "gbImage2D *"}
  },
  "methods": {"0x004a68d0": {"name": "ReleaseObject", ...}}
}
```

方案 A 改后（**只列变化**）：

| 字段 | before | after | 依据 |
|---|---|---|---|
| `known_members["0x0"]` | `{"name":"m_nTodo_000","type":"void *"}` | **删除** | 二进制 `0x0` 是 vptr：`UICaption` ctor `0x44A7B0 mov [esi+0x44],0x56afa4`、`0x44A801 mov [edx],0x56afa4`（#34 §2.3 C8） |
| `known_members["0x4"]` | 保留 | 保留 | `m_needscriptdel` 在 +4（`0x4BDF10` 等派生 ctor 均从 +8 起写成员，反推 +4..+8 属基类） |
| `vtables` | 不存在 | `[{"addr":"0x0056AFA4","base":null,"slots":[{"addr":"0x0044AB40"},{"addr":"0x0044AB00"},{"addr":"0x004AF760"}],"source":"binary rdata 直读（C5）+ UICaption 次基表原样迁移","evidence_level":"B"}]` | `.rdata` 0x56AFA4 前三槽 = 0x44AB40/0x44AB00/0x4AF760（C5 实测）；与 `UICaption.json` 现有次表逐字一致 |
| `methods` | 1 条 | 新增 3 条虚函数条目（**名字待 G1 正名**） | 槽名解析见 `emit_headers.py:765-810`；未命中会回落 `slot_{位置}`，违反命名铁律 |
| `binary_size` | 8 | **8（不变）** | vptr 4 + `m_needscriptdel` 4 = 8 |
| `base_size` | 无 | **不设**（PSWO 无基类） | `pipeline/ida/apply_annotations.py:497` 用 `base_size` 过滤成员；PSWO 自身不需要 |

**注意**：`vtables` 一旦声明，codegen 会跳过在 +0 发 `void* vfptr` 成员（`emit_headers.py:3126`），并据此发出 `virtual` 方法组（`:4376/:4416`）。这正是我们要的语义：vptr 由编译器按虚函数隐式提供，而不是当成数据成员摆在那里。

### 2.2 `data/annotations/structs/UICaption.json`（去重，同次必改）

| 字段 | before | after | 依据 |
|---|---|---|---|
| `vtables[1]` | `{"addr":"0x0056afa4","slots":[0x44ab40,0x44ab00,0x4af760],...}` | **删除这一条**（只保留主表 `0x0056AFB0`） | PSWO 已是多态，其次基表由 PSWO 自己的 `vtables` 承担；同一地址保留两份会导致同表重复发射/槽名分叉 |
| `base_size` | 76 | 76（不变） | `UIWnd@0`(72) + `PSWO@0x44`(8) = 76；PSWO 尺寸不变 |
| `binary_size` | 96 | 96（不变） | 现有生成已与二进制一致（#34 §2 实测 96） |

### 2.3 四个 fade 类：**无改动**

| 文件 | `binary_size` | `base_size` | 成员 | 说明 |
|---|---|---|---|---|
| `ScreenFadeIn.json` | 28 | 24 | `m_first@0x18` | 值已正确；布局错的来源在基类 |
| `ScreenFadeOut.json` | 24 | 24 | 无 | 同上 |
| `ScreenFadeWhite.json` | 24 | 24 | 无 | 同上 |
| `ScreenFadeWhite2.json` | 24 | 24 | 无 | 同上 |

`base_size` 保持 24 = `ScreenEffect` 尺寸；`ScreenEffect` 一旦回到 24，四类自然回到 28/24/24/24。

### 2.4 `ScreenEffectMgr.json`：**无成员改动**

16 员偏移在正确基类模型下自动回归，无需改任何一条：

| 成员 | 现注解 | 改后编译期（模型探针实测） | Δ |
|---|---|---|---|
| `m_fadeIn` | 0x4 | **0x4** | 0 |
| `m_fadeOut` | 0x20 | **0x20** | 0 |
| `m_fadeWhite` | 0x38 | **0x38** | 0 |
| `m_fadeWhite2` | 0x50 | **0x50** | 0 |
| `m_activeQueue` | 0x68 | **0x68** | 0 |
| `m_pAllocBlock`…`m_pAllocRest` | 0x6C/0x70/0x74/0x78/0x7C | **同** | 0 |
| `m_nAllocFlag1/2`、`m_fAllocFactor` | 0x80/0x84/0x88 | **同** | 0 |
| `m_pEffect` | 0x8C | **0x8C** | 0 |
| `m_nEffectCount` | 0x94 | **0x94** | 0 |

Mgr 自己的 `0x0 m_pVtable` 伪成员与 `virtual ~ScreenEffectMgr()` 保持不变：codegen 已把它当 vfptr 槽处理（生成头注释「布局由编译器隐式 vfptr 提供」），不属于本卡范围。

### 2.5 改动前后编译期数值对照（自包含模型探针，C3）

| 表达式 | 现行模型（PSWO 当 POD） | 方案 A 模型（PSWO 多态） | 二进制真值 |
|---|---|---|---|
| `sizeof(PalScriptWaitObj)` | 8 | **8** | 8 |
| `sizeof(ScreenEffect)` | 28 | **24** | 24 |
| `offsetof(ScreenEffect,m_nType)` | 12 | **8** | 8 |
| `sizeof(ScreenFadeIn)` | 32 | **28** | 28 |
| `offsetof(ScreenFadeIn,m_first)` | 28 | **24** | 24 |
| `sizeof(ScreenFadeOut/White/White2)` | 28 | **24** | 24 |
| `sizeof(ScreenEffectMgr)` | 168 | **152** | 152 |
| `offsetof(Mgr,m_fadeIn/out/white/white2)` | 4/0x24/0x40/0x5C | **4/0x20/0x38/0x50** | 同真值 |

---

## §3 爆炸半径：PSWO 的 11 个派生类（C6 实测）

| 类 | 注解 size | `base_size` | PSWO 偏移 | PSWO 段长度 | 是否重复编码 0x56AFA4 |
|---|---|---|---|---|---|
| `PalScriptIdleObj` | 16 | 8 | 0 | 8 | 否（无表） |
| `RoleFadeIn` | 20 | 8 | 0 | 8 | 否（无表） |
| `RoleFadeOut` | 20 | 8 | 0 | 8 | 否（无表） |
| `RotateInvObj` | 28 | 8 | 0 | 8 | 否（无表） |
| `RotateObj` | 36 | 8 | 0 | 8 | 否（无表） |
| `ScreenEffect` | 24 | 8 | 0 | 8 | 否（主表 0x56F4F0） |
| `ScriptWaitFrm` | 12 | 8 | 0 | 8 | 否（无表） |
| `XJ_Pic` | 16 | 8 | 0 | 8 | 否（无表） |
| `Role` | 8704 | 96 | 56 (0x38) | 40 | 否（3 张表均非 0x56AFA4）**G2** |
| `UICaption` | 96 | 76 | 68 (0x44) | 8 | **是**（`vtables[1]`=0x56AFA4，须删） |
| `ChoseCompose` | 3770 | 80 | 72 (0x48) | 8 | 否（无表） |

- 8 个「PSWO@0 + base_size 8」的类：PSWO 段长度不变（vptr 4 + 指针 4），且它们自身没有虚函数表 ⇒ 尺寸不变。
- `UICaption`：PSWO 段 8B 不变，尺寸 96 不变；只需要删重复表。
- `Role`（**G2，未知缺口**）：PSWO 在 0x38，但 Role 的 3 张表（0x56A9C0/0x56A9BC/0x56A9CC）都不等于 0x56AFA4。落地前必须核对 Role ctor 是否在 0x38 写 vptr、写的是哪张表；若不是 0x56AFA4，说明 Role 的 PSWO 子对象在二进制里并不挂 PSWO 的表，需要在实现卡里先补一条对照证据。

---

## §4 验收

### 4.1 编译期断言（实现卡必须先过这一关，再进管线）

```cpp
// sizeof
PSWO 8; ScreenEffect 24; ScreenFadeIn 28; FadeOut/White/White2 24; ScreenEffectMgr 152
// offsetof
ScreenEffect.m_nType 8; ScreenEffect.m_hold 0x14;
ScreenFadeIn.m_first 0x18;
ScreenEffectMgr: m_fadeIn 0x4 / m_fadeOut 0x20 / m_fadeWhite 0x38 / m_fadeWhite2 0x50 /
                m_activeQueue 0x68 / m_pAllocBlock 0x6C / m_pAllocRest 0x7C /
                m_nAllocFlag1 0x80 / m_fAllocFactor 0x88 / m_pEffect 0x8C / m_nEffectCount 0x94
// 不得回退的既有尺寸
UICaption 96; Role 8704; ChoseCompose 3770
```

### 4.2 全链门槛（以本卡当场重取的基线为准，C7）

| 读数 | 当前值（2026-11-27 02:45 当场重取，C7） | 门槛 |
|---|---|---|
| S2 单元 | **159/230**（`probe_census.json` @ 02:45:39） | ≥ 159，不得下降 |
| 总错误 | **622** | ≤ 622 |
| L1 棘轮记录 | **192**（`s4_baseline.json`，mtime 02:42:23，sha `66c193fe51cd4752`） | loop 的 L1 ≥ 192 |
| `cli.py check` | 秒级闸 | EXIT 0 |
| `audit_type_layout --only` | — | PSWO/ScreenEffect/四 fade/Mgr 无类型尺寸失配 |

⚠️ 卡面写的 158/230、606、189 已漂移（并发管线推进到 159/230、622、192）。**实现卡每次执行前必须重取**，不得沿用本表数字。基线文件每次 match 都会重写（sha 变化），所以「不重锚」的判据不能写成固定 sha，只能写：**loop 输出无 REBASELINE 行，且 L1 读数不低于执行前记录值**。

### 4.3 census 预期

当前（`struct_holes_20261125.json`，mtime 与并发相关）：`classes_with_holes 200 / total_holes 1073 / total_hole_bytes 820,536`；族内只有 `ScreenEffectMgr 152 / 16 员 / 4B 洞（0x90..0x94）`。改动只影响**编译期布局**，不新增/删除注解成员，因此：
- Mgr 仍是 152 / 4B 洞（不变）；
- ScreenEffect / 四个 fade 类当前不在 census 类列表中（无条目）⇒ 无洞变化；
- 若实现卡顺手补了成员，才需要重算，本卡不预期。

---

## §5 风险、回退与顺序

### 5.1 风险表

| 编号 | 风险 | 触发条件 | 处置 |
|---|---|---|---|
| R1 | **三槽正名缺失（G1）** | 直接按方案 A 落地 | 阻断：先开正名小卡（3 槽：0x44AB40/0x44AB00/0x4AF760），或用 Human 批准的临时语义名 + `name_note` |
| R2 | UICaption 同表重复发射 | 只改 PSWO、忘了删 `UICaption.vtables[1]` | 两处必须同次提交；落地后 grep 生成的 `UICaption.h` 不应出现两张 0x56AFA4 注释 |
| R3 | Role 的 PSWO 子对象表归属不明（G2） | Role 0x38 处 vptr 不是 0x56AFA4 | 实现卡先在反汇编核对 Role ctor 的 `[esi+0x38]` 写点；不符则本卡不动 Role，单列后续 |
| R4 | 派生类虚析构被意外虚化 | 若改用「基类加虚析构」这种临时手法 | 不采用该手法（会让 8 个无 dtor 声明的派生类凭空多出虚析构，签名层风险）；方案 A 只在 PSWO 上加 3 个**非析构**虚函数 |
| R5 | C1003 掩盖 | 单文件错误爆 100 条 | 本改动只影响 11 个类的头文件，`ScreenEffect*.cpp` 不在截断单元；若见 C1003，按「最大行号是否前进」判断 |
| R6 | 与 #30（codegen 基指针偏移）撞车 | 两者都改 `_ns_udts.h` 的布局 | 串行：**本卡先**（只动 1 个基类、影响面可枚举），#30 在其后用稳定布局做基指针偏移；同一时间只允许一张卡跑 loop |

### 5.2 被否证的备选（写出来防止重复试错）

- **方案 B：给 ScreenEffect 加 `void* m_pVtable` 数据成员**。不行：`ScreenEffect` 仍是多态类，编译器照样在 0 插 vfptr，成员仍在 12（模型探针：`EffB` 带数据成员 vfptr + 虚析构 → 28，`m_nType` 12）。只有「类完全没有虚函数」时这个手法才成立（Mgr 那种情况）。
- **方案 C：只改 Mgr**。不行：Mgr 的 16B 是四个 fade 各 +4 累出来的；fade 的 +4 又来自 ScreenEffect 的 vfptr 前置；根在 PSWO。

### 5.3 回退

- 只改了两份注解 JSON（`PalScriptWaitObj.json`、`UICaption.json`）：回退 = `git checkout -- data/annotations/structs/PalScriptWaitObj.json data/annotations/structs/UICaption.json`，再 `apply → export → codegen` 让 IDB 与生成头回到旧态。
- **回退后必须补一次 apply/export**：注解回退不会自动撤销已落库的 IDB 类型信息（本仓已知陷阱），否则下一次 export 仍带旧改动。
- 若已跑 loop：不重锚，只在 thread 记录读数；s4_baseline 由 match 自身维护，不要手工改。

---

## §6 下一张实现卡草案（不建卡）

- **标题**：R4 边界二落地：PSWO 多态化 + UICaption 去重（4 fade 各 −4B、Mgr 168→152）
- **前置**：`blockedBy` = 三槽正名小卡（G1）；若 Human 批准临时语义名可并行。
- **owner**：实现型成员（非本卡）；**writeScopes**：
  - `data/annotations/structs/PalScriptWaitObj.json`
  - `data/annotations/structs/UICaption.json`
  - `tests/`（新增 sizeof/offsetof 回归断言）
- **验收**：
  1. §4.1 全部编译期断言通过（含 UICaption 96 / Role 8704 不回退）；
  2. `python3 pipeline/cli.py check` EXIT 0；
  3. `python3 tools/audit_type_layout.py --only PalScriptWaitObj --only ScreenEffect --only ScreenEffectMgr` 无失配；
  4. 独占窗口 `python3 pipeline/cli.py loop`：S2 ≥ 执行前值、总错误 ≤ 执行前值、L1 ≥ 执行前值，且输出无 REBASELINE 行；
  5. census 中 Mgr 仍 152 / 4B 洞，未新增其他族条目；
  6. 生成头 `pal3/src/Misc/PalScriptWaitObj.h` 出现 3 个 `virtual` 声明、`UICaption.h` 只剩一张次表注释。

---

## §7 复现命令（C1–C8，原样执行）

### C1 注解现状（六类 + PSWO）

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import json
for c in ['PalScriptWaitObj','ScreenEffect','ScreenFadeIn','ScreenFadeOut','ScreenFadeWhite','ScreenFadeWhite2','ScreenEffectMgr','UICaption']:
    d=json.load(open('data/annotations/structs/%s.json'%c))
    print('%-20s size=%-6s base_size=%-4s bases=%s vts=%s members=%d'%(
        c,d.get('binary_size'),d.get('base_size'),
        [b.get('name') for b in (d.get('bases') or [])],
        [(v.get('addr'),len(v.get('slots') or [])) for v in (d.get('vtables') or [])],
        len(d.get('known_members') or {})))
PY
```

### C2 生成头现状（PSWO 是纯数据类、ScreenEffect 自带虚析构）

```bash
cd /home/peng/workspace/PAL3Decomp && grep -n "class PalScriptWaitObj" -A6 pal3/src/Misc/PalScriptWaitObj.h; echo ---; grep -n "class ScreenEffect" -A10 pal3/src/Effect/ScreenEffect.h | head -14
```

### C3 自包含模型探针（现行模型 vs 方案 A 模型）

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import sys; sys.path.insert(0,'pipeline'); import probe_compile as pc
src = r'''
#include <stddef.h>
struct PSWO_POD  { void *m_nTodo_000; void *m_needscriptdel; };
struct EffPOD    : PSWO_POD  { int m_nType; int m_life; float m_age; unsigned char m_hold; virtual ~EffPOD() {} };
struct FadeInPOD : EffPOD    { int m_first; };
struct MgrPOD    { virtual ~MgrPOD(); FadeInPOD a; EffPOD b; EffPOD c; EffPOD d; char q[4];
                   void *p1; void *p2; void *p3; void *p4; void *p5; int f1; int f2; int f3; char *e; char gap[4]; int cnt; };
struct PSWO_POLY { virtual void v0(int); virtual void v1(); virtual void v2(int); void *m_needscriptdel; };
struct EffPOLY   : PSWO_POLY { int m_nType; int m_life; float m_age; unsigned char m_hold; virtual ~EffPOLY() {} };
struct FadeInPOLY: EffPOLY   { int m_first; };
struct MgrPOLY   { virtual ~MgrPOLY(); FadeInPOLY a; EffPOLY b; EffPOLY c; EffPOLY d; char q[4];
                   void *p1; void *p2; void *p3; void *p4; void *p5; int f1; int f2; int f3; char *e; char gap[4]; int cnt; };
#define SZ(T,N) char sz_##T[sizeof(T)==N?1:-1]
SZ(PSWO_POD,8); SZ(EffPOD,28); SZ(FadeInPOD,32); SZ(MgrPOD,168);
SZ(PSWO_POLY,8); SZ(EffPOLY,24); SZ(FadeInPOLY,28); SZ(MgrPOLY,152);
#define OFF(T,F,N) char off_##T##_##F[(int)offsetof(T,F)==N?1:-1]
OFF(EffPOD,m_nType,12); OFF(EffPOLY,m_nType,8);
OFF(FadeInPOD,m_first,28); OFF(FadeInPOLY,m_first,24);
OFF(MgrPOLY,a,4); OFF(MgrPOLY,b,0x20); OFF(MgrPOLY,c,0x38); OFF(MgrPOLY,d,0x50);
OFF(MgrPOLY,q,0x68); OFF(MgrPOLY,p5,0x7c); OFF(MgrPOLY,f1,0x80); OFF(MgrPOLY,f3,0x88);
OFF(MgrPOLY,e,0x8c); OFF(MgrPOLY,gap,0x90); OFF(MgrPOLY,cnt,0x94);
'''
open('/tmp/model_probe.cpp','w').write(src)
args=['/Fo'+pc.wpath('/tmp/model_probe.obj'), pc.wpath('/tmp/model_probe.cpp'),
      '/I'+pc.wpath('tools/compilers/msvc6.0/Include'), '/I'+pc.wpath('tools/vc6/Include')]
out,rc=pc.run_cl(args, timeout=300, flags=('/nologo','/TP','/c','/W3','/GX'))
bad=[l for l in out.split('\n') if 'error' in l]
print('C2118 count =', len(bad)); print('PASS' if not bad else bad[:5])
PY
```

### C4 现行生成的 sizeof（依赖当前 pal3/src 头，可能被并发 codegen 改动）

```bash
cd /home/peng/workspace/PAL3Decomp && ls -l pal3/src/Misc/PalScriptWaitObj.h pal3/src/Effect/ScreenEffect.h && grep -c "virtual" pal3/src/Misc/PalScriptWaitObj.h pal3/src/Effect/ScreenEffect.h
```

### C5 三张 vtable 的实际槽（直接从 original/PAL3.exe 的 .rdata 读）

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import struct
d=open('original/PAL3.exe','rb').read()
pe=struct.unpack_from('<I',d,0x3c)[0]; n=struct.unpack_from('<H',d,pe+6)[0]; opt=pe+24
base=struct.unpack_from('<I',d,opt+28)[0]; o0=opt+struct.unpack_from('<H',d,pe+20)[0]
secs=[]
for i in range(n):
    o=o0+i*40; name=d[o:o+8].rstrip(b'\0').decode(); vs,va,rs,ro=struct.unpack_from('<IIII',d,o+8)
    secs.append((name,base+va,vs,ro,rs))
def rd(va,k=32):
    for name,sva,vs,ro,rs in secs:
        if sva<=va<sva+max(vs,rs):
            b=d[ro+va-sva: ro+va-sva+k]
            return [struct.unpack_from('<I',b,i)[0] for i in range(0,k,4)]
for vt in (0x56afa4,0x56f4f0,0x56f510,0x56f52c,0x56f548,0x56f564):
    print(hex(vt), [hex(v) for v in rd(vt)])
PY
```

### C6 爆炸半径（谁以 PSWO 为基类、PSWO 在哪个偏移、谁重复编码 0x56AFA4）

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import json,glob
rows=[]
for p in glob.glob('data/annotations/structs/*.json'):
    try: d=json.load(open(p))
    except Exception: continue
    for b in (d.get('bases') or []):
        if b.get('name')=='PalScriptWaitObj':
            vts=[(v.get('addr') or '').lower() for v in (d.get('vtables') or [])]
            rows.append((b.get('offset') or 0, d.get('name'), d.get('binary_size'), d.get('base_size'),
                         (d.get('base_size') or 0)-(b.get('offset') or 0), '0x0056afa4' in vts))
rows.sort()
for r in rows: print('PSWO@%-5s %-18s size=%-6s base_size=%-4s seg=%-4s dup56AFA4=%s'%r)
print('count', len(rows))
PY
```

### C7 当场基线（读数会随后台管线漂移，必须看时间戳）

```bash
cd /home/peng/workspace/PAL3Decomp && python3 pipeline/cli.py status 2>&1 | sed -n '13,30p'; python3 - <<'PY'
import json,hashlib,time,os
p='data/status/s4_baseline.json'; b=open(p,'rb').read(); d=json.loads(b)
print('s4 sha256', hashlib.sha256(b).hexdigest()[:16], 'mtime', time.strftime('%H:%M:%S', time.localtime(os.path.getmtime(p))))
print('stats', {k:d.get('stats',{}).get(k) for k in ('match_L1','matched','symbols')})
PY
```

### C8 census 族内现状

```bash
cd /home/peng/workspace/PAL3Decomp && python3 - <<'PY'
import json
c=json.load(open('data/status/struct_holes_20261125.json'))
print('meta', {k:c['_meta'].get(k) for k in ('classes_with_holes','total_holes','total_hole_bytes')})
names={r['cls'] for r in c['classes']}
for n in ['PalScriptWaitObj','ScreenEffect','ScreenFadeIn','ScreenFadeOut','ScreenFadeWhite','ScreenFadeWhite2','ScreenEffectMgr']:
    r=[x for x in c['classes'] if x['cls']==n]
    print(n, 'in census' if n in names else 'NOT in census', (r[0]['size'], r[0].get('hole_bytes'), r[0].get('holes')) if r else '')
PY
```

---

## §8 边界与自检

- 本卡**只新增这一份文档**；未改 `data/annotations/**`、`pal3/src/**`、`pipeline/**`、`tests/**`、任何基线；未跑 `apply/export/codegen/probe/match/loop`。
- 只跑了：JSON 读取、`git status`、`original/PAL3.exe` 的 .rdata 只读解析、以及**自包含模型探针**（在 `/tmp` 下的独立 TU，用仓库自带 MSVC6 编译，不引用仓库生成头）。
- 文档行数：**384**（`wc -l` 实测）；`git status --porcelain` 共 94 条，本卡唯一新增为 `?? docs/specs/2026-11-27-r4-screenfade-landing-plan.md`，其余 93 条为他人在办文件/并发管线产物。
- 已知并发：`s4_baseline.json`、`struct_holes_20261125.json` 的 mtime 在 02:4x 持续变化（后台管线在跑），本图所有读数都标了时点；实现卡执行前必须重取。
- QA 自检：
  1. 四个 fade 类逐个给了真尺寸、注解值、4B 机理，并引用 #34 的原样数字与证据等级（§1.1/§1.2/§1.3）；
  2. 改动表精确到 JSON 字段（§2.1/§2.2），并明确四个 fade 类与 Mgr **不改**；
  3. 验收含 offsetof/sizeof 断言、Mgr 16 员逐项偏移、全链门槛（当场重取的 159/230·622·192）、census 预期与「不重锚」的可执行判据（§4）；
  4. 风险/回退与顺序写清（§5），并与 #30 明确串行；
  5. 只新增本文件，未改注解/代码/基线，未跑管线。
