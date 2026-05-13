# PAL3 标注迭代管线

<CRITICAL-INSTRUCTION>
当前阶段：**IDA 标注阶段**。源码是生成物，不手动编辑。
唯一的工作目标：提升 `pipeline/data/annotations/` 的数据质量。
所有结构体字段修改必须有 PAL3.exe 二进制直接证据。
</CRITICAL-INSTRUCTION>

## 环境

```
IDA:         ~/ida-pro-9.1/idat
IDB:         original/PAL3.exe.i64 (可重建，不提交到 git)
Annotations: pipeline/data/annotations/ (唯一可信源)
  ├── functions.json      — 函数名 + 签名
  ├── globals.json        — 全局变量名 + 类型
  ├── skip_functions.json — 排除的函数（CRT/库/thunk）
  ├── vtables.json        — 虚函数表
  ├── structs/            — 每个类一个 JSON 文件
  └── CHANGE_LOG.md       — 变更记录（含置信度和证据）
Decomp:      asm/pal3/decomp/*.json (IDA 导出，gitignored)
PDB参考:     pipeline/data/pdb/     (PAL3A，只读参考)
Scripts:     pipeline/ida/          (IDAPython 脚本)
Tools:       pipeline/verify_offset.py (二进制偏移验证)
```

## 数据架构

```
pipeline/data/annotations/ (唯一手工编辑的数据源)
  ├── functions.json        — {addr: {name, signature}}
  ├── globals.json          — {addr: {name, type}}
  ├── skip_functions.json   — {addr: {name, reason}}
  ├── vtables.json          — {vtbl_name: {address, class, methods}}
  ├── structs/              — 每个类一个 JSON
  │     └── ClassName.json  — {name, binary_size, known_members: {offset: {name, type, source}}}
  └── CHANGE_LOG.md         — 变更审计记录
```

## IDB 重建流程（从零）

IDB 是生成物，可随时从 annotations 重建：

```bash
IDA=~/ida-pro-9.1/idat
$IDA -B -o original/PAL3.exe.i64 original/PAL3.exe
$IDA -A -S"pipeline/ida/master_pipeline.py" original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/apply_annotations.py" original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/export_full.py" original/PAL3.exe.i64
```

## 代码生成

```bash
python3 pipeline/gen/gen_headers.py
python3 pipeline/gen/gen_cpp.py --force-all
```

## 标注变更工作流

### 置信度规则

所有标注变更必须有 **PAL3.exe 二进制直接分析证据（A 级）**。

| 证据等级 | 类型 | 分值 |
|---------|------|------|
| A | 二进制指令直接提取（绝对地址 / reg+disp） | 85-90 |
| B | 多处交叉验证 / PDB + 二进制确认 | 80 |
| C | Hex-Rays 反编译推断（可能因布局错误偏移不准） | 50 |
| D | 命名/上下文推断（无偏移验证） | 30 |

**提交阈值**：偏移修改 ≥80，类型修改 ≥70，命名 ≥60，size 修改 ≥85。
**PDB 是参考不是权威**——PAL3A PDB 的偏移/结构必须从 PAL3 二进制验证。

### 结构体字段验证流程

```bash
# 1. 找引用该字段的函数
python3 -c "
import json, os
for fname in os.listdir('asm/pal3/decomp'):
    if fname.endswith('.json') and not fname.startswith('_'):
        d = json.load(open('asm/pal3/decomp/' + fname))
        if '_field_TARGET' in d.get('decompiled_c', ''):
            print(f'{d[\"name\"]} @ {d[\"address\"]}')
            break
"

# 2. 读取函数二进制，搜索 displacement
python3 -c "
import struct
with open('original/PAL3.exe', 'rb') as f:
    f.seek(FUNC_VA - 0x400000)
    code = f.read(FUNC_SIZE)
# 搜索 disp32 值
needle = struct.pack('<I', EXPECTED_OFFSET)
for i in range(len(code)):
    if code[i:i+4] == needle:
        pre = code[max(0,i-2):i]
        print(f'offset={i} pre={pre.hex()} disp={needle.hex()}')
"

# 3. 确认 this 来源（thiscall: ecx → 通常 mov esi/edi, ecx）
# 4. 读取完整指令确认访问模式和宽度
# 5. 记录到 CHANGE_LOG.md
```

### 全局变量/函数验证流程

```bash
# 用 verify_offset.py 搜索绝对地址引用
python3 pipeline/verify_offset.py --global BASE_ADDR StructName FIELD_OFFSET

# 或搜索全局变量的直接引用
python3 -c "
import struct
with open('original/PAL3.exe', 'rb') as f:
    data = f.read()
needle = struct.pack('<I', GLOBAL_ADDR)
# 在 .text 段搜索
"
```

### 迭代步骤

1. **选择焦点**：统计 `_field_` 引用频率，选最高的开始
2. **二进制验证**：从 PAL3.exe 提取真实偏移和访问宽度
3. **记录证据**：写入 `CHANGE_LOG.md`，包含指令地址、字节、置信度
4. **修改 annotations**：只在置信度达标时修改
5. **校验**：`python3 pipeline/check_annotations.py`
6. **提交**：

```bash
git add pipeline/data/annotations/
git commit -m "iter(annotations): [描述]

Evidence: [关键二进制证据摘要]
Confidence: [最低置信度]

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
git push
```

## 核心原则

1. **annotations 是唯一输出** — 所有逆向进度必须落入 annotations
2. **二进制是唯一权威** — PAL3.exe 中的指令是最终真相
3. **PDB 是参考不是权威** — PAL3A 偏移/结构需从 PAL3 二进制验证
4. **IDB 是生成物** — 可随时从 annotations 重建
5. **Hex-Rays 不可信** — 反编译输出依赖 IDA 结构体定义，可能偏移错误
6. **置信度先行** — 无 A 级证据不得修改偏移/类型
7. **MSVC 6.0 对齐** — 默认 4 字节自然对齐，int/float/ptr 不可能在非 4 倍偏移

## 质量指标

```bash
# 检查 annotations 合法性
python3 pipeline/check_annotations.py

# 统计 _field_ 残留
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

# 统计对齐违规
python3 -c "
import json, os
# ... (见 verify_offset.py)
"
```

## 退出条件

标注阶段结束条件：
- `_field_` 字段数趋于稳定
- 对齐违规降至 0
- sub_ 前向声明趋于稳定
- 重建一致性 ≥95%

然后切换到：编译修复 → 字节匹配阶段。
