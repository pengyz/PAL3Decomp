# PAL3 标注迭代管线

<CRITICAL-INSTRUCTION>
当前阶段：**IDA 标注阶段**。源码是生成物，不手动编辑。
唯一的工作目标：提升 `pipeline/data/annotations/` 的数据质量。
所有结构体字段修改必须有 PAL3.exe 二进制直接证据。
</CRITICAL-INSTRUCTION>

## 环境

```
IDA:         $IDA (首次使用时从系统搜索 idat 并设置)
IDB:         original/PAL3.exe.i64 (可重建，不提交 git)
Annotations: pipeline/data/annotations/ (唯一可信源)
Decomp:      asm/pal3/decomp/*.json (IDA 导出，gitignored)
PDB参考:     pipeline/data/pdb/ (PAL3A，只读参考)
Binary:      original/PAL3.exe (最终权威)
Scripts:     pipeline/ida/
Tools:       pipeline/verify_offset.py, pipeline/check_annotations.py
```

## 数据架构

```
pipeline/data/annotations/
  ├── functions.json        — {addr: {name, signature}}
  ├── globals.json          — {addr: {name, type}}
  ├── skip_functions.json   — {addr: {name, reason}}
  ├── vtables.json          — {vtbl_name: {address, class, methods}}
  ├── structs/ClassName.json — {name, binary_size, known_members: {offset: {name, type, source}}}
  └── CHANGE_LOG.md         — 变更审计记录（证据+置信度）
```

## 禁止行为

<HARD-REQUIREMENT>
1. **禁止从 Hex-Rays 反编译文本推断偏移**——反编译中的 `this->_field_0CE` 不等于真实偏移 0xCE（结构体布局可能错误）
2. **禁止批量修改未验证字段**——每个偏移/类型变更必须逐一验证
3. **禁止仅凭 PDB 数据修改**——PDB 来自 PAL3A，偏移可能与 PAL3 不同
4. **禁止提交无 A 级证据的偏移/类型修改**
5. **禁止假设对齐方向**——偏移违规时不能假设"应该向上对齐"，必须从二进制确认真实值
6. **禁止伪语义命名**——`m_nState_4968`、`m_fParam_0A0` 这种用地址后缀伪装的名字没有语义价值，和 `_todo_4968` 没有区别。只有能确定具体含义时才命名（如 `m_szTooltip`、`m_fAngle`、`m_nBlendState`），否则保留 `_todo_` 占位符。宁可诚实地标记未知，不可用噪声掩盖无知。
</HARD-REQUIREMENT>

## 置信度规则

| 证据等级 | 类型 | 分值 | 示例 |
|---------|------|------|------|
| A | 二进制指令中的绝对地址 | 90 | `mov [0xC116EC], eax` → abs addr |
| A | 二进制指令中的 reg+disp32 | 85 | `mov byte [esi+0xD1], 1` 且 esi=this |
| B | 3+ 条 A 级证据交叉确认 | 80+ | 多个函数中同偏移同访问模式 |
| C | Hex-Rays 文本推断 | 50 | `this->_field_0CE` — **不可单独用于偏移修改** |
| D | 命名/语义推断 | 30 | 从调用上下文猜测字段含义 |

**提交阈值**：

| 修改类型 | 最低置信度 | 必须条件 |
|---------|-----------|---------|
| 偏移修改 | 80 | 至少 1 条 A 级证据 |
| 类型修改 | 70 | A 级证据确认访问宽度 |
| 字段命名 | 60 | A 级证据确认偏移正确 + 语义推断 |
| 结构体 size | 85 | stride/数组边界的 A 级证据 |

## 单字段验证流程（逐一执行，不可跳步）

### Step V1: 定位二进制证据

**输入**: 结构体名、字段偏移（来自 annotations）
**输出**: 包含该偏移的函数地址 + 机器码

```bash
# 对全局结构体实例：计算绝对地址并搜索
python3 pipeline/verify_offset.py --global BASE_ADDR StructName FIELD_OFFSET
```

对于 this 指针访问（非全局实例）：
```bash
# 1. 找一个访问该字段的函数
python3 -c "
import json, os
for f in sorted(os.listdir('asm/pal3/decomp')):
    if not f.endswith('.json') or f.startswith('_'): continue
    d = json.load(open('asm/pal3/decomp/' + f))
    if 'STRUCT::' in d.get('name','') and '_field_XXX' in d.get('decompiled_c',''):
        print(d['name'], d['address'], d['size_bytes'])
        break
"
# 2. 读取该函数的二进制
python3 -c "
import struct
with open('original/PAL3.exe','rb') as f:
    f.seek(FUNC_VA - 0x400000)
    code = f.read(FUNC_SIZE)
# 搜索可能的 disp32 值（当前标注偏移 和 对齐后偏移）
for test in [CURRENT_OFFSET, ALIGNED_OFFSET]:
    needle = struct.pack('<I', test)
    pos = 0
    while pos < len(code):
        idx = code.find(needle, pos)
        if idx == -1: break
        pre = code[max(0,idx-3):idx]
        print(f'disp={hex(test)} at func+{idx}: pre={pre.hex()}')
        pos = idx + 1
"
```

**判定**: 如果找不到任何引用 → 无法验证，**不得修改**。

### Step V2: 确认 this/base 来源

**输入**: Step V1 找到的指令位置
**输出**: 确认 [reg+disp] 中 reg 的值来源

```bash
# 读取函数头部，确认 this 指针赋值
python3 -c "
with open('original/PAL3.exe','rb') as f:
    f.seek(FUNC_VA - 0x400000)
    head = f.read(20)
print(head.hex())
# 常见模式:
# 8B F1 = mov esi, ecx (this → esi)
# 8B F9 = mov edi, ecx (this → edi)
# 56 8B F1 = push esi; mov esi, ecx
"
```

**判定**: 如果 reg 来源不明确（多次赋值/间接来源）→ 置信度 -20。

### Step V3: 确认访问宽度和类型

**输入**: 完整指令字节
**输出**: 访问宽度（1/2/4/8）+ 操作类型（load/store/float/compare）

| 指令前缀 | 宽度 | 类型 |
|---------|------|------|
| `8B xx` (mod=10) | 4 | load dword |
| `89 xx` (mod=10) | 4 | store dword |
| `C6 xx` | 1 | store byte |
| `66 8B/89` | 2 | load/store word |
| `D9 xx` (mod=10) | 4 | fld float |
| `DD xx` (mod=10) | 8 | fld double |
| `0F B6` | 1→4 | movzx byte |
| `0F B7` | 2→4 | movzx word |

**判定**: 宽度确定后检查对齐：
- 4 字节访问 + 偏移 % 4 ≠ 0 → **annotations 偏移错误**（需修正为二进制中的实际 disp 值）
- 1 字节访问 + 任意偏移 → annotations 中类型应为 char/BYTE

### Step V4: 记录证据

将以上结果写入 `CHANGE_LOG.md`：
```markdown
### [日期] StructName._field_XXX

- **变更**: [具体修改内容]
- **置信度**: [数值]
- **证据**:
  1. [A] VA=0xADDR: `完整指令字节` = `反汇编` (reg=this 来源: `mov esi,ecx` @ func+0)
  2. [A/B] 交叉验证: [其他佐证]
- **判定**: [通过/不通过 + 理由]
```

### Step V5: 修改（仅在置信度达标时）

```bash
# 修改 annotations
python3 -c "
import json
d = json.load(open('pipeline/data/annotations/structs/STRUCT.json'))
m = d['known_members']
# ... 修改 ...
with open('pipeline/data/annotations/structs/STRUCT.json', 'w') as f:
    json.dump(d, f, indent=2, ensure_ascii=False)
"

# 必须立即校验
python3 pipeline/check_annotations.py
```

**判定**: check_annotations 报错 → 回退修改，分析原因。

### Step V6: 提交

```bash
git add pipeline/data/annotations/
git commit -m "iter(annotations): [描述]

Evidence: [VA=0xADDR: 指令摘要]
Confidence: [最低值]

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
git push
```

## IDB 重建流程

```bash
$IDA -B -o original/PAL3.exe.i64 original/PAL3.exe
$IDA -A -S"pipeline/ida/master_pipeline.py" original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/apply_annotations.py" original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/export_full.py" original/PAL3.exe.i64
python3 pipeline/gen/gen_headers.py
python3 pipeline/gen/gen_cpp.py --force-all
```

## 代码质量度量

```bash
# annotations 校验（必须 0 errors）
python3 pipeline/check_annotations.py

# _field_ 命名率
python3 -c "
import json, os, re
total = unnamed = 0
for f in os.listdir('pipeline/data/annotations/structs'):
    if f.endswith('.json'):
        d = json.load(open('pipeline/data/annotations/structs/' + f))
        for m in d.get('known_members', {}).values():
            total += 1
            if re.match(r'^_field_', m['name']): unnamed += 1
print(f'命名率: {(total-unnamed)/total*100:.1f}% ({total-unnamed}/{total})')
"

# 对齐违规数（目标: 0）
python3 -c "
import json, os
violations = 0
for f in os.listdir('pipeline/data/annotations/structs'):
    if not f.endswith('.json'): continue
    d = json.load(open('pipeline/data/annotations/structs/' + f))
    for off, m in d.get('known_members', {}).items():
        t = m['type']
        if any(x in t for x in ['int','float','DWORD','unsigned long']) or '*' in t:
            if int(off) % 4 != 0: violations += 1
        elif any(x in t for x in ['short','WORD']):
            if int(off) % 2 != 0: violations += 1
print(f'对齐违规: {violations}')
"

# 生成代码中 sub_ 残留
grep -roh 'sub_[0-9A-Fa-f]\{6,8\}' src/pal3/ 2>/dev/null | sort -u | wc -l
```

## 核心原则

1. **annotations 是唯一输出** — 所有逆向进度落入 annotations
2. **二进制是唯一权威** — PAL3.exe 中的指令是最终真相
3. **PDB 是参考不是权威** — PAL3A 偏移/结构需从 PAL3 二进制验证
4. **IDB 是生成物** — 可随时从 annotations 重建
5. **Hex-Rays 不可信** — 反编译偏移可能因布局错误而不准确
6. **逐一验证** — 每个字段修改独立验证，不批量推断
7. **MSVC 6.0 对齐** — int/float/ptr 在 4 倍偏移，short 在 2 倍偏移

## 退出条件

- 对齐违规 = 0
- `_field_` 数趋于稳定（边际收益递减）
- 重建一致性 ≥95%
- sub_ 数趋于稳定

然后切换到：编译修复 → 字节匹配阶段。
