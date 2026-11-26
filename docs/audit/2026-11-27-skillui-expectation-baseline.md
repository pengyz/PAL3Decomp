# SkillUI 落位预期基准（独立验收 oracle）

任务：#28 · tsk_01M8C9PD4Y26VEM9V1MQ05
日期：2026-11-27
角色：验收 oracle，**独立于实现方**。
**勘误（验收后 2026-11-27，据白砚 rev4 复核）**：§4 第 4 行「约360B」与 §5「0x94–0xa30 零命中」两处措辞已按下文修正；结论不变。未读 #23 在途产物、未读 #27；#20 底稿只作为「待验命题」输入，不当作本报告的偏移证据。

## 0. 结论摘要

1. **尺寸 101,940B（0x18E34）成立**：分配立即数 `push 18E34h`、`??0SkillUI` 调用、类尾闭合三处独立一致。
2. **ctor 建链可完整分区并精确闭合**：`sub_525120` 把 101,940B 切成 19 段对象/数组 span，逐段累加 = 101,940（§3 算式）。本报告给出的分区表是「实现应达到的结构」，与 #20 §4 独立复算一致。
3. **99,428B 洞是「缺类型建模」而非「缺数据」**：按 §3 分区建模后，SkillUI 自身只剩约 **412B** 无构造/无访问缺口（其中 256B 在 `0x60–0x160`）；其余 99,016B 是子对象，应记到各自类名下，不是 SkillUI 的洞。
4. **53 员成员表不可采纳（预期裁法，不下裁决）**：其偏移在 SkillUI 七个方法体里**零访问**，且与 ctor 真实对象从 `0x150` 起结构性互斥。建议的实现方向是「整表移出/删除，按 §3 重建」，而不是「补洞」。
5. 实现完成的可检验底线见 §6，共 7 条。

## 1. 复现命令与原样输出

```bash
# 1) 注解现状
python3 - <<'PY'
import json
d=json.load(open('data/annotations/structs/SkillUI.json'))
print(d['binary_size'], hex(d['binary_size']), 'base', d.get('base_size'),
      'bases', d['bases'], 'members', len(d['known_members']), 'methods', len(d['methods']))
print([v['addr'] for v in d['vtables']])
PY
```

```
101940 0x18e34 base 72 bases [{'base_address': 0, 'class': 'UIListBox'}] members 53 methods 8
['0x005706cc']
```

```bash
# 2) 洞与实例
python3 - <<'PY'
import json
h=json.load(open('data/status/struct_holes_20261125.json'))
print(h['_meta'])
e=[c for c in h['classes'] if c.get('name')=='SkillUI'][0]
print({k:e[k] for k in ('size','members','bases','hole_bytes','total_holes')})
print(e['holes'])
PY
```

```
{'rule': 'v3 对齐感知 + 四修', ...}
{'size': 101940, 'members': 53, 'bases': 1, 'hole_bytes': 99428, 'total_holes': 4}
[['0x48', '0x94', 76], ['0x4b4', '0x4b8', 4], ['0xa10', '0xa30', 32], ['0xa40', '0x18e34', 99316]]
```

```bash
grep -n "push    18E34h" original/PAL3.exe.asm
grep -n "sub_525120.*proc near" original/PAL3.exe.asm
grep -n "sub_525540.*proc near" original/PAL3.exe.asm
```

```
445068:                push    18E34h          ; Size
441504:sub_525120      proc near               ; CODE XREF: sub_527A80+107
441973:sub_525540      proc near               ; CODE XREF: sub_525120+1B4
```

分配与 store：
```
445068: push 18E34h
445070: call ??2@YAPAXI@Z
445076: call sub_525120
445087: mov  [esi+6C0h], eax
```
census 行（`data/status/probe_heap_alloc_census_20261126.json`）：
```json
{"size": 101940, "ctor": "??0SkillUI@@QAE@XZ", "store": "esi+0x6C0",
 "caller": "?CreateSubPanels@SoundContext@@QAEXH@Z", "site": "0x527b6d"}
```

```bash
# 3) 方法体内偏移访问普查（7 个方法）
python3 - <<'PY'
import re
txt=open('original/PAL3.exe.asm',encoding='utf-8',errors='ignore').read().splitlines()
starts={'sub_525120','sub_525540','sub_5257B0','sub_526660','sub_526740','sub_526A40','sub_527510'}
cur=None; hits={}
for line in txt:
    m=re.match(r'^(sub_[0-9A-Fa-f]+)\s+proc near',line)
    if m: cur=m.group(1); hits.setdefault(cur,set()); continue
    if cur in starts:
        for off in re.findall(r'\[\s*e[a-z]{2}\+([0-9A-Fa-f]+)h\s*\]',line):
            v=int(off,16)
            if 0x48<=v<0x18E34: hits[cur].add(v)
allv=set().union(*hits.values())
print('distinct',len(allv)); print(sorted(hex(v) for v in allv)[:40])
print('hits in 0x60..0x160:',[v for v in allv if 0x60<=v<0x160])
PY
```

```
distinct 109
['0x48','0x4c','0x50','0x54','0x58','0x5c','0x160','0x1a4','0x1b0', ...]
hits in 0x60..0x160: []
```

说明：0x94–0xa30 区间内有 9 个命中（0x160/0x1a4/0x1b0/0x658/0x6cc/0x6dc/0x6f0/0x788/0x820），均为 ctor 对象起点或内部；53 个成员键本身零命中。

## 2. 总量分区（101,940 = 99,428 洞 + 53 员 + 4 段）

| 量 | 值 | 来源 |
|---|---|---|
| 类尺寸 | 101,940（0x18E34） | 注解 = 分配立即数 = ctor 闭合 |
| 洞字节 | 99,428（97.5%） | `struct_holes_20261125.json`（rule v3） |
| 成员 | 53 | 注解（证据等级 D，见 §5） |
| 洞段 | 4 | 0x48–0x94 / 0x4b4–0x4b8 / 0xa10–0xa30 / 0xa40–0x18e34 |

**咬合关系**：53 员覆盖 `0x94–0xa30`（含 `fp@0xa30`），洞是「不被这 53 员覆盖的字节」。因此 99,428 这个数**只是「注解覆盖率」的补集**，不代表这些字节没有结构——它完全取决于 53 员对不对。§3 证明 53 员与 ctor 对象冲突，所以 99,428 不能读成「SkillUI 有 99KB 未知数据」。

## 3. ctor/dtor 建链闭包算式（A 级）

`sub_525120`（asm:441504–441716）与 dtor `sub_525540`（asm:441973，逆序析构 + 基类最后）逐段对应。分区求和（脚本核验 = 101,940）：

| 起始 | span | 内容 | 证据 |
|---|---|---|---|
| 0x000 | 72 | UIListBox 基类（ctor 首调 `sub_43DCD0`；vtable 覆写 `0x5706CC`） | A |
| 0x048 | 16 | 窗口矩形 4×dword（0x48/4c/50/54） | A |
| 0x058 | 8 | 宽 0x320、高 0x258 | A |
| 0x060 | 256 | **零访问区** | 无 |
| 0x160 | 1,240 | UIPushButton[5] ×248（`??_L(0x160,0xF8,5,sub_440740,…)`） | A |
| 0x638 | 32 | 对齐/未知 | 无 |
| 0x658 | 456 | UIFrameContainer[3] ×152（`sub_4422E0`） | A |
| 0x820 | 1,032 | 344B 类[3]（`??_L(0x820,0x158,3,sub_43A770,sub_43A810)`） | A(span) / B(类名) |
| 0xC28 | 52 | 未知 gap | 无 |
| 0xC5C | 496 | UIPushButton[2] ×248（`sub_440740`） | A |
| 0xE4C | 344 | 344B 类[1]（`sub_43A770`；末 16B 尾缝 0xF94–0xFA4） | A(span) |
| 0xFA4 | 924 | 308B 类[3]（`sub_439030`） | A(span) / B |
| 0x1340 | 24 | gbVec3D[2] ×12 | A |
| 0x1358 | 1,216 | UIFrameContainer[8]（`sub_4422E0`） | A |
| 0x1818 | 8 | 对齐/未知 | 无 |
| 0x1820 | 32 | 标量区（0x1820…0x183C） | A |
| 0x1840 | 260 | 260B 类（`sub_43F7F0`，表 0x56AD64） | A(span) / B |
| 0x1944 | 192 | UITextArea（`sub_444F60`） | A |
| 0x1A04 | 304 | UIFrameContainer[2] | A |
| 0x1B34 | 8 | 对齐/未知 | 无 |
| 0x1B3C | 8,040 | 800B 记录[5]，步长 0x648（`sub_401810(edi,0x320,2,sub_5254C0)`） | A(span) |
| 0x3AA4 | 56 | 未知 gap | 无 |
| 0x3ADC | 84,096 | UIParticle[36] ×4 段（`??_L(ptr,0x248,0x24,sub_4B4690,sub_4B47E0)`），四段首尾相接止 0x1835C | A |
| 0x1835C | 40 | 标量/零填（0x1835C…0x18383） | A |
| 0x18384 | 1,368 | UIRoleDialog（`sub_4A12F0`） | A |
| 0x188DC | 1,368 | UIRoleDialog（`sub_4A12F0`），末 `0x188DC+0x558=0x18E34` | A |

**求和**：72+16+8+256+1240+32+456+1032+52+496+344+924+24+1216+8+32+260+192+304+8+8040+56+84096+40+1368+1368 = **101,940** ✓（脚本核验）。

其中：
- 有 ctor/dtor 直接指定的对象/数组 span：**101,360B（99.4%）**；
- 类头 72 + 矩形/尺寸 24 + 标量区 72 = 168B，有构造证据但类型名待定；
- **真未知 gap = 412B**：0x60–0x160(256)、0x638–0x658(32)、0xC28–0xC5C(52)、0x1818–0x1820(8)、0x1B34–0x1B3C(8)、0x3AA4–0x3ADC(56)。

## 4. 四段洞逐段预期

| 洞段 | 现洞 | 预期 | 依据 |
|---|---|---|---|
| 0x48–0x94 | 76B | **约 52B**（0x48–0x60 的 24B 是矩形+宽高；0x60–0x94 的 52B 属零访问区，难以闭合） | ctor 只写 0x48/4C/50/54/58/5C；0x60–0x160 无任何访问 |
| 0x4b4–0x4b8 | 4B | **0B**：这是 `m_Task` 前 4B 对齐；表不采纳后该段并入更大的未知区，随模型改善而消失 | `??_L` 无对应；0x4b4 无访问 |
| 0xa10–0xa30 | 32B | **0B**：落在 0x820 数组第 1 元素（0x978–0xAD0）体内，属 344B 对象的内部（其自身洞记到该类名下） | ctor `sub_43A770` |
| 0xa40–0x18e34 | 99,316B | **124B**：该段内真 gap 只有 0xC28–0xC5C(52)/0x1818–0x1820(8)/0x1B34–0x1B3C(8)/0x3AA4–0x3ADC(56)；其余是子对象/数组（§3）。0x1835C 标量区 40B 已在 span 内，不重复计洞 | §3 分区 |

**验收口径**：实现完成后，全类残差 ≤ 412B 即可认为「结构已建模」，分区报 **52（0x60–0x94）+ 204（0x94–0x160，删表释放区）+ 32（0x638）+ 124（0xa40–0x18e34 段内）**；0x1835C 标量区 40B 已在 span 内，勿重复计洞。若仍接近 99,428，说明子对象没有建成员，只是把表删了。

## 5. 53 员：直接证据与推定（含预期裁法，不下裁决）

| 命题 | 等级 | 依据 |
|---|---|---|
| SkillUI 是真类、有真实例 | A | `push 18E34h`→`??2`→`??0SkillUI`；工厂 `sub_527A80 → mov [esi+6C0],eax`；`UIGameFrm::_init_44F8D0` case8 创建链；析构对 |
| ctor/dtor 建链（§3 表） | A | asm 逐段 `??_L`/`lea/call` 与 dtor 逆序逐条对应 |
| 53 个成员键在 SkillUI 自身无访问 | A（否定） | 7 方法体 109 个 distinct 偏移与 53 个成员键**交集为空**；`0x94–0xa30` 区间内的 9 个命中（0x160/0x1a4/0x1b0/0x658/0x6cc/0x6dc/0x6f0/0x788/0x820）全是 ctor 对象起点/内部，不是成员 |
| 53 员与 ctor 对象结构互斥 | A（否定） | `0x150[11]` 止 0x17C 跨 0x160 按钮；`m_Task[19]@0x4b8` 止 0xa10 覆盖 0x658/0x6F0/0x788 与 0x820 控件；`fp@0xa30` 落在 0x978–0xAD0 体内 |
| 53 员来自 CCBUI（同名同偏移） | B | 52/59 同偏移同名同型（#20 P1）；**但 CCBUI 自己的 ctor `sub_5160A0` 仅 34 行、零构造，同样无自身证据**，只能算几何可容（0xA48 内） |
| 界面域=鉴定/展厅 | C（推定） | #20 字符串与界面资源；本卡未独立复核，不作验收依据 |

**预期裁法（供拍板，不下裁决）**：
- 方向一（推荐）：53 员**整表移出 SkillUI**，按 §3 分区重建成员（类型名未定者用 span + 来源 ctor 地址标注），洞从 99,428 降到约 412。
- 方向二：保留 53 员但仅 `0x94–0x150` 区间（与 ctor 不冲突的 6 员），其余删除——仍无访问证据，只能算「可用占位」，不解决 99KB 洞。
- 不建议：把 `m_Task[19]` 等保留并同时建 ctor 对象（两套结构重叠，必触发越界/对齐错误）。

## 6. 实现可疑检查点（≥5）

1. `binary_size` 仍 101,940 且分区求和 ≠ 101,940（§3 表中任何 span 写错都会破坏闭合）。
2. `0x160` 不是 `UIPushButton[5]×248`（或用 `??_L` 之外的构造、span ≠ 1,240）。
3. 四段 UIParticle 不是 `36×584` 或不再首尾相接（0x3ADC→0x1835C 连续 84,096B）。
4. 类尾不是 `0x188DC` 起两个 `1368`（末 `+0x558=0x18E34`）。
5. 成员里仍出现 `m_Task@0x4b8` 或 `fp_0xa30`（与 ctor 对象重叠）。
6. 洞字节仍≈99,428（说明子对象没建成成员，只删了表）。
7. 基类仍是 UIListBox 且 vtable 为 `0x5706CC`（7 槽，`~SkillUI@0x525520`）。

## 7. 未决

1. `0x60–0x160`（256B）无任何 ctor/dtor/方法访问——需要 IDA UDT readback 或 init 之外的初始化路径才能闭合；本卡判「预期留洞」。
2. `0x638–0x658`(32)/`0xC28–0xC5C`(52)/`0x1818–0x1820`(8)/`0x1B34–0x1B3C`(8)/`0x3AA4–0x3ADC`(56)：对齐或未知；VC6 对齐规则可解释一部分，剩余无证据。
3. 344B 类（`0x43A770`，表 `0x56AC70`）在注解中无登记类；308B 类（表 `0x56AC20`）注解只有 UIProgressBar(244)；260B 类（表 `0x56AD64`）无登记——三者需归位后才能给成员级预期。
4. `0x1840` 260B 与 UIButton(344) 的冲突（#20 E2）：本卡按 ctor span 取 260，类名待定。
5. 800B 记录（5×1608）的元素语义（#20 推定「记录表」，元素内 4 个 lstrcpyA + int[6]）未独立取证。
6. `InitSkillUI` 名字 vs 鉴定/展厅域（#20 E5）——命名待命战役。

## 8. 只读自证

- 本卡只写 `docs/audit/`；未改 `data/annotations/`、未改 `pal3/src/`、未改基线。
- 未运行任何 `pipeline/cli.py` 命令（无 apply/export/codegen/probe/match）。
- 复核所用输入：`data/annotations/structs/SkillUI.json`、`data/status/struct_holes_20261125.json`、`data/status/probe_heap_alloc_census_20261126.json`、`original/PAL3.exe.asm`、`docs/ui-inventory/2026-11-26-skillui-ui-inventory.md`（#20，仅作待验命题）。
- 独立声明：未读 #23 在途产物、未读 #27；本报告与 #20 的结论一致处均为本卡独立复算所得，冲突处已单列（§5 第 5 行、§7 第 4/5 行）。
