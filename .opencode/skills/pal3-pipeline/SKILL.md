# PAL3 标注迭代管线

<CRITICAL-INSTRUCTION>
当前阶段：**IDA 标注阶段**。源码是生成物，不手动编辑。
唯一的工作目标：提升 `data/annotations/` 的数据质量。
所有结构体字段修改必须有 PAL3.exe 二进制直接证据。

**阶段分离原则**：反编译项目明确拆分为两个独立阶段：

1. **标注阶段**（当前）：还原编译过程中丢失的信息（类型、名称、结构、继承关系）。
   评价指标：decomp_quality 四维指标 + 命名率 + check_annotations 0 errors。
   **不关注**：codegen 输出、编译错误。

2. **codegen 阶段**（未来）：将标注成果转化为可编译源码。
   评价指标：编译错误数、pass rate、字节匹配率。
   **前提**：标注质量足够高。

编译错误是 codegen 适配度的指标，不是标注正确性的指标。更精确的标注可能导致更多编译
错误（因为 codegen 尚未适配强类型代码），这是正常现象，不构成标注回退的理由。
</CRITICAL-INSTRUCTION>

## 环境

所有路径在 `pipeline.toml` 中配置。查看/验证：`python pipeline/cli.py config`

```
配置文件:   pipeline.toml (gitignored, 每环境独立)
IDA:        [ida] path (pipeline.toml 中配置)
Binary:     [binary] exe / idb_raw / idb_work
Annotations: data/annotations/ (唯一可信源)
Decomp:     asm/pal3/decomp/*.json (export 生成, gitignored)
PDB参考:    data/pdb/ (PAL3A, 只读参考)
```

如果配置缺失: `python pipeline/cli.py config` 会列出所有 [!] 项及修复命令。

## 数据架构

```
data/annotations/
  ├── functions.json        — {addr: {name, signature}}
  ├── globals.json          — {addr: {name, type}}
  ├── skip_functions.json   — {addr: {name, reason}}
  ├── vtables.json          — {vtbl_name: {address, class, methods}}
  ├── structs/ClassName.json — {name, binary_size, known_members: {offset: {name, type, source}}}
  └── CHANGE_LOG.md         — 变更审计记录（证据+置信度）
```

## 禁止行为

<HARD-REQUIREMENT>
1. **禁止从 Hex-Rays 反编译文本推断偏移**——反编译中的 `this->_field_0CE` 不等于真实偏移 0xCE（结构体布局可能错误）。但如果 IDB 已 apply_annotations 且结构体定义正确，Hex-Rays 输出的偏移可用于**语义命名**（不可用于偏移/类型修改）。
2. **禁止批量修改未验证字段**——每个偏移/类型变更必须逐一验证
3. **禁止仅凭 PDB 数据修改**——PDB 来自 PAL3A，偏移可能与 PAL3 不同
4. **禁止提交无 A 级证据的偏移/类型修改**
5. **禁止假设对齐方向**——偏移违规时不能假设"应该向上对齐"，必须从二进制确认真实值
6. **禁止伪语义命名**——`m_nState_4968`、`m_fParam_0A0` 这种用地址后缀伪装的名字没有语义价值，和 `_todo_4968` 没有区别。只有能确定具体含义时才命名（如 `m_szTooltip`、`m_fAngle`、`m_nBlendState`），否则保留 `_todo_` 占位符。宁可诚实地标记未知，不可用噪声掩盖无知。
7. **禁止对 IDA 查询工具的输出不加验证直接命名**——IDA 工具提供**候选列表**，每个候选仍需人工判断语义是否足够明确。不明确的保留 `_todo_`。
8. **禁止用编译错误评判标注质量**——编译错误是 codegen 层的适配度问题，不是标注正确性
   问题。更精确的类型标注可能导致更多编译错误（codegen 尚未适配），这不构成回退标注的
   理由。标注阶段的验证手段：`check_annotations` + `decomp_quality.py`，不含 compile。
9. **禁止仅凭 signature this 类型修正函数归属**——IDA 的 signature this 类型来自 caller
   推断，如果 caller 本身标注错误则连锁传播错误。函数归属修正**必须有 decomp member
   access evidence**：即函数内 `this->member` 引用的成员在目标类中存在且不在原类中存在。
   signature this ≠ name class 仅作为**候选筛选条件**，不可直接作为修正依据。
</HARD-REQUIREMENT>

## 置信度规则

| 证据等级 | 类型 | 分值 | 示例 |
|---------|------|------|------|
| A | 二进制指令中的绝对地址 | 90 | `mov [0xC116EC], eax` → abs addr |
| A | 二进制指令中的 reg+disp32 | 85 | `mov byte [esi+0xD1], 1` 且 esi=this |
| A+ | IDA apply 后 Hex-Rays 偏移（结构体正确时） | 85 | apply_annotations 后反编译中 `this + 484` |
| B | 3+ 条 A 级证据交叉确认 | 80+ | 多个函数中同偏移同访问模式 |
| C | Hex-Rays 文本推断（无 apply） | 50 | `this->_field_0CE` — **不可单独用于偏移修改** |
| D | 命名/语义推断 | 30 | 从调用上下文猜测字段含义 |

**提交阈值**：

| 修改类型 | 最低置信度 | 必须条件 |
|---------|-----------|---------|
| 偏移修改 | 80 | 至少 1 条 A 级证据 |
| 类型修改 | 70 | A 级证据确认访问宽度 |
| 字段命名 | 60 | A 级证据确认偏移正确 + 语义推断 |
| 结构体 size | 85 | stride/数组边界的 A 级证据 |

## IDA 工具集

### 基础工具

| 脚本 | 用途 | 输入 | 输出 |
|------|------|------|------|
| `pipeline/ida/master_pipeline.py` | 初始化 IDB（PDB 类型+FLIRT+全局变量） | raw i64 | 初始化后的 i64 |
| `pipeline/ida/apply_annotations.py` | 将 annotations 应用到 IDB | i64 + annotations/ | 更新后的 i64 |
| `pipeline/ida/export_full.py` | 导出所有函数的 Hex-Rays 反编译 | i64 | asm/pal3/decomp/*.json |

### 查询工具（只读，不修改 IDB）

| 脚本 | 用途 | 适用场景 | 输出 |
|------|------|---------|------|
| `query_todo_fields.py` | 批量扫描全部 _todo_ 字段的二进制 xref + decomp 上下文 | 迭代开始时，了解全局状态 | `_logs/todo_field_context.json` |
| `query_highref_fields.py` | 对高引用但无上下文的字段强制反编译 | query_todo_fields 之后，补充缺失上下文 | `_logs/highref_field_context.json` |
| `query_class_full.py` | 对指定类的全部方法做完整反编译 | 聚焦单个类时，获取最完整的字段语义 | `_logs/class_full_context.json` |

### 非 IDA 工具

| 脚本 | 用途 |
|------|------|
| `pipeline/verify_offset.py` | 验证全局实例的字段偏移（搜索 .text 段绝对地址引用） |
| `pipeline/check_annotations.py` | 校验 annotations 数据合法性（JSON格式、重名、基类存在性） |

## 管线 CLI

所有操作通过统一入口执行。首次使用先检查配置：

```bash
python pipeline/cli.py config              # 查看配置状态，[!] 标记缺失项
python pipeline/cli.py config --set ida.path="D:\...\idat.exe"  # 设置 IDA 路径
```

### IDB 重建

IDB 是生成物，可随时从 annotations 重建：

```bash
# 首次初始化（从 exe 创建 raw + 导入 PDB + 导入 annotations）
python pipeline/cli.py init

# 强制重建（删除已有 IDB，从零开始）
python pipeline/cli.py init --force
```

### 标注变更后更新

```bash
python pipeline/cli.py apply               # 重新应用 annotations 到 IDB
python pipeline/cli.py export              # 刷新 decomp JSON
python pipeline/cli.py codegen all         # 重新生成源码
python pipeline/cli.py compile             # 编译验证
```

### 仅重新生成代码（标注未变，只改了 codegen）

```bash
python pipeline/cli.py codegen all
python pipeline/cli.py compile
```

**何时需要 init --force**：annotations 有重大结构变更（binary_size、base_class）导致 IDB 布局过期时。

## IDA 查询工具典型用法

IDA 路径从 pipeline.toml 读取: `python pipeline/cli.py config` 查看。
以下示例用 `$IDA` 代替完整路径，`$IDB` 代替 work IDB 路径。

**前置**：IDB 已 init（`python pipeline/cli.py init`）。

### 1. query_todo_fields.py — 全局 _todo_ 扫描

**适用**：迭代开始时，了解哪些 _todo_ 字段有二进制引用、哪些有反编译上下文。

```bash
$IDA -A -S"pipeline/ida/query_todo_fields.py" $IDB
# 输出: pipeline/ida/_logs/todo_field_context.json
# 结构: {ClassName: {offset: {hex, type, refs: [...], decomp_context: [...]}}}
```

**结果解读**：
- `refs` 数量高 → 字段被频繁使用，命名价值大
- 有 `decomp_context` → 可直接从上下文推断语义
- 无 `decomp_context` 但 refs 多 → 需要 query_highref_fields 补充

**禁止**：直接将 refs 数量作为命名依据。refs 只说明使用频率，不说明语义。

### 2. query_highref_fields.py — 补充高引用字段的反编译上下文

**适用**：query_todo_fields 之后，对 refs≥3 但无 decomp_context 的字段强制反编译。
**前置**：已运行 query_todo_fields（依赖其输出 JSON）。

```bash
$IDA -A -S"pipeline/ida/query_highref_fields.py" $IDB
# 输出: pipeline/ida/_logs/highref_field_context.json
```

**禁止**：跳过 query_todo_fields 直接运行——它依赖前者的输出。

### 3. query_class_full.py — 单类全量反编译

**适用**：聚焦某个类时，需要该类所有方法中所有 _todo_ 字段的完整上下文。
**参数**：逗号分隔的类名列表。

```bash
# 对 Camera 和 TextureLib 做全量反编译扫描
$IDA -A -S"pipeline/ida/query_class_full.py Camera,TextureLib,PalScript" $IDB
# 输出: pipeline/ida/_logs/class_full_context.json
```

**选择目标类的原则**（优先级从高到低）：
1. 未命名字段少（接近完成）但有关键缺失 → 快速收尾
2. 有清晰领域语义的类（Camera, RenderTarget, Actor）→ 命名准确率高
3. 方法多、引用频繁的核心类 → 上下文丰富

**禁止**：
- 一次传入超过 10 个类——每个类都要反编译全部方法，太多会导致 IDA 运行过久
- 对 ScriptSystemData、CGameData 这种巨型结构体（1000+ 成员）使用——上下文过于分散，效率低

### 4. verify_offset.py — 全局实例偏移验证

**适用**：验证全局结构体实例的字段偏移是否有绝对地址引用。
**限制**：仅适用于有全局实例（globals.json 中有地址）的结构体。对纯 this 指针访问的类无效。

```bash
# 验证全局实例的特定字段
python pipeline/verify_offset.py --global 0xC04390 SceneMgr 0xD35C

# 自动查找全局实例
python pipeline/verify_offset.py SceneMgr 0x1BC4
```

**禁止**：将"0 引用"解读为"字段不存在"——该字段可能仅通过 this 指针间接访问。

## 单字段验证流程（逐一执行，不可跳步）

### Step V1: 定位二进制证据

**输入**: 结构体名、字段偏移（来自 annotations）
**输出**: 包含该偏移的函数地址 + 机器码

优先使用 IDA 查询工具：
```bash
# 方法 A（推荐）：从 query_todo_fields 或 query_class_full 的输出 JSON 中查找
# refs 列表已包含 VA、access type、base_reg、disasm

# 方法 B：对全局实例，使用 verify_offset.py
python pipeline/verify_offset.py --global BASE_ADDR StructName FIELD_OFFSET

# 方法 C（兜底）：手动从二进制搜索 disp32
python -c "
import struct
with open('original/PAL3.exe','rb') as f:
    f.seek(FUNC_VA - 0x400000)
    code = f.read(FUNC_SIZE)
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
python -c "
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
python -c "
import json
d = json.load(open('data/annotations/structs/STRUCT.json'))
m = d['known_members']
# ... 修改 ...
with open('data/annotations/structs/STRUCT.json', 'w') as f:
    json.dump(d, f, indent=2, ensure_ascii=False)
"

# 必须立即校验
python pipeline/check_annotations.py
```

**判定**: check_annotations 报错 → 回退修改，分析原因。

### Step V6: 提交

```bash
git add data/annotations/
git commit -m "iter(annotations): [描述]

Evidence: [VA=0xADDR: 指令摘要]
Confidence: [最低值]

Co-Authored-By: Sisyphus (Mify-Xiaomi3/xiaomi/mimo-v2-pro) <noreply@opencode.ai>"
```

## 典型迭代工作流

### 批量命名迭代（高效路径）

```
1. 重建 IDB        → python pipeline/cli.py init (或 apply 如果只更新标注)
2. 导出 decomp     → python pipeline/cli.py export
3. 全局扫描        → $IDA -A -S"pipeline/ida/query_todo_fields.py" $IDB
4. 补充上下文      → $IDA -A -S"pipeline/ida/query_highref_fields.py" $IDB
5. 聚焦目标类      → $IDA -A -S"pipeline/ida/query_class_full.py ClassName" $IDB
6. 人工判断命名    → 从 JSON 输出中筛选语义明确的字段，逐个命名
7. 校验+提交       → python pipeline/cli.py check → git commit
8. 重复 5-7        → 选下一个类
```

### 验证改进效果

**标注阶段验证（不含编译）：**

```bash
# 数据一致性
python pipeline/check_annotations.py     # 必须 0 errors

# 反编译质量（需要 init+export 刷新 decomp）
python pipeline/cli.py init --force      # 重建 IDB
python pipeline/cli.py export            # 刷新 decomp JSON
python pipeline/decomp_quality.py        # 四维指标（不可回退>5%）
```

**decomp_quality.py 指标**：
- type_correctness: this 参数类型正确率
- field_coverage: this->name vs *(this+N) 比率
- global_coverage: g_name vs dword_XXXXX 比率
- attribution_accuracy: 函数归属正确率

**注意**：init --force + export 是为了刷新 decomp JSON 以度量反编译质量。
codegen 和 compile 是**另一个阶段的工作**，标注迭代中不运行。

**经验教训**: 更精确的标注（正确的 this 类型、更多 struct 成员）会导致 Hex-Rays 产出
更强类型化的代码，可能增加 codegen 编译错误。这是**正确行为**——信息还原本身是目标，
编译适配是 codegen 阶段的责任。不因编译错误增加而回退标注改进。

### 单字段精确验证（偏移/类型修改时）

```
1. 定位证据 (V1)   → IDA 查询工具或 verify_offset.py
2. 确认来源 (V2)   → 函数头部 this 赋值模式
3. 确认宽度 (V3)   → 指令前缀解码
4. 记录证据 (V4)   → CHANGE_LOG
5. 修改+校验 (V5)  → annotations + python pipeline/cli.py check
6. 提交 (V6)       → git commit
```

## 标注质量度量

标注阶段的唯一评价维度是**信息还原程度**，不含编译结果。

```bash
# 1. 数据一致性（门槛：必须 0 errors）
python pipeline/check_annotations.py

# 2. 反编译质量（四维指标 + 回归检测）
python pipeline/decomp_quality.py            # 完整报告
python pipeline/decomp_quality.py --brief    # 一行摘要
python pipeline/decomp_quality.py --threshold  # CI 门控（任一维度退化>5%则 exit 1）

# 3. 命名率
python -c "
import json, os, re
total = unnamed = 0
for f in os.listdir('data/annotations/structs'):
    if f.endswith('.json'):
        d = json.load(open('data/annotations/structs/' + f, encoding='utf-8'))
        for m in d.get('known_members', {}).values():
            total += 1
            if re.match(r'^_field_|^_todo_', m['name']): unnamed += 1
print(f'命名率: {(total-unnamed)/total*100:.1f}% ({total-unnamed}/{total})')
"

# 4. 对齐违规数（目标: 0，跳过 pack=1 结构体）
python -c "
import json, os
violations = 0
for f in os.listdir('data/annotations/structs'):
    if not f.endswith('.json'): continue
    d = json.load(open('data/annotations/structs/' + f, encoding='utf-8'))
    if d.get('pack') == 1: continue
    for off, m in d.get('known_members', {}).items():
        t = m['type']
        if any(x in t for x in ['int','float','DWORD','unsigned long']) or '*' in t:
            if int(off) % 4 != 0: violations += 1
        elif any(x in t for x in ['short','WORD']):
            if int(off) % 2 != 0: violations += 1
print(f'对齐违规: {violations}')
"
```

**不在标注阶段使用的指标**：
- 编译错误数（codegen 适配度，非标注质量）
- pass rate（codegen 输出质量）
- 字节匹配率（最终验收指标，标注阶段不可用）

## 核心原则

1. **annotations 是唯一输出** — 所有逆向进度落入 annotations
2. **二进制是唯一权威** — PAL3.exe 中的指令是最终真相
3. **PDB 是参考不是权威** — PAL3A 偏移/结构需从 PAL3 二进制验证
4. **IDB 是生成物** — 可随时从 raw + annotations 重建
5. **Hex-Rays 有条件可信** — apply_annotations 后结构体正确时，偏移可信度升至 A+；未 apply 时不可信
6. **IDA 工具提供候选，人工判断拍板** — 工具输出是线索不是结论
7. **逐一验证** — 每个字段修改独立验证，不批量推断
8. **MSVC 6.0 对齐** — int/float/ptr 在 4 倍偏移，short 在 2 倍偏移，pack(1) 结构体除外

## 验证方法论（经验总结）

### 类型判定规则

| 证据 | 结论 | 确定性 |
|------|------|--------|
| `fld dword [reg+off]` / `fadd` / `fst` / `fcomp` | **float** | 确定 |
| `fild` / `fistp` | 整数↔浮点转换 | 确定（源/目标分别是 int/float） |
| `mov eax,[reg+off]; test eax,eax` | **不确定**（int 或 float 均可） | 不可判定 |
| `movzx byte` / `cmp byte` / `mov byte` | **unsigned char** | 确定 |
| `lea reg,[reg+off]; push reg; call Func(char*)` | 该偏移是 **char[]** 缓冲区 | 高 |
| `lea reg,[reg+off]; mov ecx,reg; call ctor` | 该偏移是 **嵌入子对象** | 确定 |

**关键教训**: 整数寄存器操作（mov/test/cmp）对 4 字节字段**无法区分** int 和 float。IEEE 754 正浮点数的 DWORD 表示 > 0，所以 `test eax,eax; jle` 对正 float 等效于"非零检测"。只有 FPU 指令能确定性证明 float。

### IEEE 754 常量识别

IDA decomp 中整数赋值可能暴露 float 类型——当赋值的整数值恰好是常见 IEEE 754 编码：

| 整数值 | 十六进制 | float 值 | 判定 |
|--------|---------|----------|------|
| 1065353216 | 0x3F800000 | 1.0 | **float** |
| 1073741824 | 0x40000000 | 2.0 | **float** |
| 1056964608 | 0x3F000000 | 0.5 | **float** |
| 1045220557 | 0x3E4CCCCD | 0.2 | **float** |
| 1036831949 | 0x3DCCCCCD | 0.1 | **float** |
| 1092616192 | 0x41200000 | 10.0 | **float** |
| 1120403456 | 0x42C80000 | 100.0 | **float** |

当 decomp 显示 `this->field = 1065353216` 且该字段在 4 字节对齐偏移上，置信度 **85** 可判定为 float。

### 嵌入子对象发现

构造函数中 `lea ecx,[esi+offset]; call CtorFunc` 模式是发现嵌入子对象的高效路径：
- 连续 LEA 的 stride = 子对象大小（验证与目标类 binary_size 匹配）
- 调用目标 = 子对象类的构造函数（通过 functions.json 确认）
- 多个相同 stride 的连续 LEA = 嵌入数组
- stride > binary_size 时：每个 slot 含子对象 + 额外数据（不要假设 slot==子对象）

**关键教训（CScreenMode 案例）**:
- **二进制 LEA 是嵌入偏移的最终权威**，即使 apply_annotations 后的 Hex-Rays decomp 也可能给出错误偏移
- CScreenMode 的 UIFrameWnd/UIScene embed 全部从 decomp cast 标注，结果系统性偏移 -8
- 原因：struct 布局不正确时，Hex-Rays 解析的字段偏移会产生漂移
- **正确流程**: 先从二进制 ctor/dtor 中 LEA 解码确认精确偏移，再验证 decomp 是否一致
- 如果 decomp 偏移与二进制 LEA 矛盾 → **以二进制为准，decomp 偏移作废**

### 管理器 vs 元素判别

对于包含对象数组的类（如 PalScript）：
- **管理器方法**: 访问 count 字段 + 遍历数组（stride 循环）
- **元素方法**: 在 vtable 中定义（off_XXXXXXXX），操作单个元素内偏移
- **判别**: 检查函数是否在 annotations vtables.json 中归属该类 vtable
- **偏移空间**: 管理器字段在数组起始前，元素字段在 stride 范围内

### 全局实例验证

有全局实例（globals.json）的类可用 verify_offset.py：
- 搜索 .text 段中绝对地址 `g_Instance + offset` 的引用
- 适用于 SceneMgr、CScreenMode 等单例
- 不适用于 this 指针间接访问的类（如 CCBRoleState）

### raw IDB 辅助分析

`original/PAL3.exe.raw.i64` 无类型信息但可用于：
- 纯粹的 Hex-Rays 类型推断（不受错误结构体干扰）
- 函数参数类型/返回值的初始猜测
- **注意**: raw decomp 中 `this + N` 的 N 是字节偏移（当 this 为 char*/void*）或 DWORD 偏移（当 this 为 _DWORD*）——看是否有 `(_TYPE *)` cast 来判断

## 待解决: IDA 函数重名 mangling (TODO)

IDA 不支持函数重载——同类中相同名字的函数必须重命名。当前 apply_annotations 直接用
IDA 默认加 `_0`/`_1` 后缀，导致 export 出的 cpp 方法名和 header 声明不匹配。

**冲突的三种情况**（不可自动区分）：

| 类型 | 表现 | 正确处理 |
|------|------|---------|
| 真重载 | 同名不同参数（C++ overload） | mangling 导入 IDA → codegen 还原 |
| 归属错误 | 函数不属于该类 | 修正 annotations 中 class 归属 |
| 多态误归 | 子类虚方法被归到基类 | 修正归属到正确子类 |

**第 3 类最隐蔽**：UIXXXX 系列有大量子类，如果把子类的 `Create`/`Destroy` 等虚方法
归属到 `UIWnd` 基类，就会出现多个同签名同名函数，表面像重载实际是多态继承。

**设计方向**：
1. apply_annotations: 冲突时用显式 mangling（如 `__ovl_ADDR`），而非 IDA 默认 `_0`
2. codegen: 检测 `__ovl_` 标记还原原始名
3. 归属错误和多态误归需人工审查——自动化无法区分

**当前状态**: 未实现。PtrArray 无参构造器等少数 case 暂时保持现状。

## Stub/Thunk 函数处理系统

IDA 反编译产出中大量函数实际上是编译器生成的 stub/wrapper，它们不包含独立逻辑，
只是转发调用到另一个函数。这些 stub 仍被虚函数表引用或被其他函数调用，无法物理消除，
但可以通过 annotation 和 codegen 联动自动替换为对目标函数的直接调用。

### 识别 stub 函数

通过 decomp JSON 的函数体分析识别 stub：

```python
# 模式: { return TargetFunc(args...); } 或 { TargetFunc(args...); }
body = decompiled.split('{',1)[-1].rsplit('}',1)[0]
calls = re.findall(r'(?:return\s+)?(\w+(?:::\w+)?)\s*\(', body)
if len(calls) == 1 and body.count(';') <= 2:
    target = calls[0]
    # target 不是 sub_/_nearby_/unknown_libname 时判定为 stub
```

典型 stub 模式：
- **类方法委托**：`ClassName::Method(...)` → 直接替换为 `TargetClass::Method(...)`
- **析构包装**：`~ClassName(...)` → 替换为 `ClassName::Destroy(...)`
- **操作符包装**：`operator=(...)` → 替换为 `Assign(...)`
- **CRT 包装**：`j_XXXX(...)` → 编译器生成的 import 包装

非 stub（保留反编译）：
- 函数体包含条件判断、循环、switch 等逻辑语句
- 调用了 `sub_`/`_nearby_` 等未命名函数
- body 中的调用数 > 1 或语句数 > 2

### 标记 thunk

在 `data/annotations/skip_functions.json` 中添加条目：

```json
{
  "0x0043BBB0": {
    "name": "UIWnd::sub_43BBB0",
    "reason": "thunk",
    "target_name": "UIWnd::_UIWnd"
  }
}
```

字段说明：
- `reason: "thunk"` — 标记为跳转型 stub
- `target_name` — 替换目标函数的全限定名（必须包含 `ClassName::`）

### codegen 替换机制

```
skip_functions.json
    ↓ data.py: 加载 thunks
    store.thunks = {
      "sub_43bbb0": "UIWnd::_UIWnd",     # 地址短名
      "UIWnd::sub_43BBB0": "UIWnd::_UIWnd",  # 全限定名
      "sub_43BBB0": "UIWnd::_UIWnd",         # 函数短名（OOP 变换后）
      "_UIWnd": "UIWnd::_UIWnd",             # 方法短名
    }
    ↓ stage4_substitution.py: _build_identifier_map() + thunk_map
    ↓ AST 级别标识符替换
    sub_43BBB0(...) → UIWnd::_UIWnd(...)
    this->sub_43BBB0(...) → this->_UIWnd(...)
```

替换发生在 codegen 的 Stage 4（token 替换阶段），在所有 OOP 变换之后执行，
因此 thunk_map 中同时包含全限定名（`ClassName::method`）和短名（`method`），
以匹配 OOP 变换前后的不同代码形态。

### 语法 vs 语义 stub

| 类型 | 函数体模式 | 示例 | 处理 |
|------|-----------|------|------|
| 纯语法 stub | `{ Target(this); }` | `UIWnd::Destroy` → `UIWnd::_UIWnd` | thunk |
| 带参数转发 | `{ return Target(this, args...); }` | `Actor::GetAnimDuration` → `gbActor::GetActionDuration` | thunk |
| 字段设置器 | `{ this->field = val; }` | `CameraCtrl::SetCamMode` → `LODWORD(this->m_mode)=mode` | 保持原样 |
| 简单条件 | `{ if (cond) return X; else return Y; }` | `PAL_GDB::GDB_GetRoleNum` | 保持原样 |

**经验**：字段设置器和简单条件函数虽然代码短，但包含真实语义逻辑，不应标记为 thunk。
thunk 只应用于函数体仅包含一次函数调用且无其他逻辑的函数。

### 批量检测脚本

```bash
# 步1: 扫描所有未分类函数，检测 stub 模式
python -c "
import json, os, re
d = 'asm/pal3/decomp'
for f in os.listdir(d):
    if not f.endswith('.json'): continue
    j = json.load(open(d+'/'+f))
    if j.get('class'): continue  # 已归属的跳过
    dec = (j.get('decompiled_c') or j.get('decompiled','')).replace('\\\\n','\\n')
    body = dec.split('{',1)[-1].rsplit('}',1)[0] if '{' in dec else ''
    calls = re.findall(r'(?:return\\s+)?([A-Za-z_]\\w*(?:::\\w+)?)\\s*\\(', body)
    if len(calls)==1 and body.count(';')<=2 and '::' in calls[0]:
        print(f'{j[\"address\"]}: {j[\"name\"]} -> {calls[0]}')
" > stubs.txt

# 步2: 人工审核后批量添加到 skip_functions.json
# （需要确认 target_name 正确，排除设置了字段但看起来像 stub 的函数）
```

### 验证

```bash
# 验证 thunk 替换是否生效
grep -c 'EnableActionTransMtl' src/pal3/gen/Role/Actor.cpp
# >0 表示 thunk 替换成功

# 检查 thunk 函数是否不再导出
ls asm/pal3/decomp/ | wc -l
# 每次添加 thunk 后导出文件数应减少

# 检查前向声明变化
python -c "
import os, re
c=0
for r,d,f in os.walk('src/pal3/gen'):
    for fn in f:
        if not fn.endswith('.cpp'): continue
        t=open(r+'/'+fn).read()
        m=t.find('\\n// 0x')
        for x in re.findall(r'int (sub_\\\\w+)\\\\(\\\\.\\\\.\\\\.\\\\)', t[:m if m>0 else len(t)]):
            c+=1
print(f'Remaining sub_ forward decls: {c}')
```

## 退出条件

- 对齐违规 = 0
- `_todo_` + `_field_` 数趋于稳定（边际收益递减）
- 重建一致性 ≥95%
- sub_ 数趋于稳定

然后切换到：编译修复 → 字节匹配阶段。

## 实践经验总结

### Annotation 修改后必须 apply/export

修改 `data/annotations/` 后必须执行完整管线才能看到效果：

```bash
# 方式 A（推荐，彻底）：重建 IDB → export → codegen
python pipeline/cli.py init --force
python pipeline/cli.py export
python pipeline/cli.py codegen all

# 方式 B（增量，只改 annotation 未改结构体 layout）：
python pipeline/cli.py apply
python pipeline/cli.py export
python pipeline/cli.py codegen all
```

**跳过 export 导致 decomp JSON 与 annotation 不一致**——codegen 始终基于 decomp JSON 生成。

### 伪全局变量 → 大结构体子对象

`globals.json` 中的某些全局变量实际上是更大结构体（SceneMgr、RoleSystem 等）的内部字段。codegen 的 `struct_instances` 机制可以自动将其分解为 `g_StructName.field`。

**处理流程**：

1. 确认该全局变量的地址落在某 struct_instance 范围内
2. 在该结构体的 annotation（`structs/ClassName.json`）中添加对应偏移的字段定义
3. 在 `globals.json` 中将该全局变量标记为 `"type": "skip"`，`"reason"` 注明它是哪个结构体的成员
4. 重新 export + codegen 后，codegen 自动通过 `_resolve_offset` 递归解析为 `g_StructName.member.sub_member`

**示例**（SceneMgrCamBlock）：
```
g_pScriptArrayEnd (0xC10960) → g_SceneMgr.m_camBlock.m_pScriptArrayEnd
g_UIScript (0xC10968)       → g_SceneMgr.m_camBlock.m_pUIScript
g_pScriptArrayEnd2 (0xC1096C) → g_SceneMgr.m_camBlock.m_pScriptArrayEndSub
```

### 嵌套 struct 的递归解析

`_resolve_offset` 支持多级嵌套（SceneMgr → SceneMgrCamBlock → member），代码在 `stage4_substitution.py` 的 `_resolve_offset()` 函数中：

1. 先在该类型 `known_members` 中精确匹配偏移
2. 无精确匹配时遍历所有成员，找到包含该偏移的嵌入子对象
3. 递归调用 `_resolve_offset(子对象类型, 相对偏移, prefix)`
4. 返回 `.member.sub_member` 形式的后缀

**必要条件**：
- 每级结构体必须有 `binary_size` 且 ≥ 成员实际范围
- 嵌入子对象成员必须定义为非指针类型（`*` 在 type 中则不递归）
- struct_instances 中必须有该全局实例的地址范围

### IDA 未命名全局变量（Buffer 等）

IDA 给大型无名称的全局结构体会生成默认名如 `Buffer`、`Block`、`Src` 等。这些不是 `dword_`/`byte_` 前缀，codegen 的 `_try_struct_member_resolution` 不会捕捉。

**修复方式**：在 `stage4_substitution.py` 的 `_build_identifier_map()` 中添加映射：

```python
m['Buffer'] = 'g_RoleSystemMain'
```

**需验证**：确认所有使用该名称的函数都指向同一个内存地址（搜索 `Buffer.vfptr` 或 `Buffer.m_nAnimCopy` 确认引用关系）。

