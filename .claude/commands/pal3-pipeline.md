# PAL3 标注迭代管线

<CRITICAL-INSTRUCTION>
当前阶段：**IDA 标注阶段**。源码是生成物，不手动编辑。
唯一的工作目标：提升 annotations.json 的数据质量。
编译验证/字节匹配是标注收敛后的工作，当前不做。
</CRITICAL-INSTRUCTION>

## 数据架构

```
annotations.json (唯一可信源，存差分)
  ├── functions: {addr → {name, signature}}        — 幂等覆盖
  ├── globals:   {addr → {name, type}}             — 幂等覆盖
  ├── structs:   {class → {size, known_members}}   — 增量叠加
  └── enums:     {name → {values}}                 — 幂等覆盖

恢复流程 (任意机器):
  idat -B PAL3.exe                                    → 空 IDB
  idat -A -S"pal3_master_pipeline.py" xxx.i64         → PDB base
  idat -A -S"pal3_apply_annotations.py" xxx.i64       → 差分层
  idat -A -S"pal3_export_only.py" xxx.i64             → decomp JSON
  python3 tools/gen_headers.py && python3 tools/gen_cpp.py --force-all
```

## 单轮迭代流程

### Step 1: 选择焦点

从 annotations.json 中找改进空间最大的方向：

```bash
# 函数：还有多少 sub_ 未命名？
python3 -c "
import json; ann=json.load(open('asm/pal3/annotations.json'))
print(f'Named functions: {len(ann[\"functions\"])}')
"

# 结构体：哪些类成员最少（空洞最多）？
python3 -c "
import json; ann=json.load(open('asm/pal3/annotations.json'))
for name, s in sorted(ann['structs'].items(), key=lambda x: len(x[1].get('known_members',{}))):
    n = len(s.get('known_members', {}))
    if n < 5: print(f'  {name}: {n} members')
" | head -20

# 全局变量：多少缺类型？
python3 -c "
import json; ann=json.load(open('asm/pal3/annotations.json'))
no_type = sum(1 for g in ann['globals'].values() if not g.get('type'))
print(f'Globals without type: {no_type}/{len(ann[\"globals\"])}')
"
```

选择策略（按 ROI 排序）：
1. **高引用 sub_ 函数命名** — 从 xref 找被最多函数引用的 sub_，分析其逻辑命名
2. **核心类结构体填充** — CCBSystem/Stage/RoleState/UI 的空洞成员
3. **全局变量类型标注** — 高引用的无类型全局变量
4. **函数签名修正** — void* 参数 → 具体类型

### Step 2: 分析 + 标注

**工作方式**：读 decomp JSON + 二进制字节 → 推断信息 → 更新 annotations.json

```bash
# 读取函数反编译
python3 -c "
import json, os
for f in os.listdir('asm/pal3/decomp'):
    if 'TARGET' in f:
        print(json.load(open(f'asm/pal3/decomp/{f}'))['decompiled_c'][:500])
"

# 读取二进制字节 (确认偏移)
python3 -c "
with open('original/PAL3.exe','rb') as f:
    f.seek(ADDR - 0x400000)
    print(f.read(SIZE).hex(' '))
"

# 查询 xref
python3 tools/pal3_callgraph.py xref QUERY

# 查询 PDB 类定义 (参考，偏移需验证)
python3 -c "
import json
for c in json.load(open('asm/pal3a/pdb_export.json'))['classes']:
    if c['name'] == 'TARGET':
        for m in c['data_members']:
            print(f'+0x{m[\"offset\"]:04X} {m[\"type\"]:30s} {m[\"name\"]}')
"
```

### Step 3: 更新 annotations.json

直接编辑 JSON 或用脚本更新：

```python
# 添加函数名
ann['functions']['0x00XXXXXX'] = {"name": "ClassName::MethodName", "signature": "..."}

# 添加全局变量类型
ann['globals']['0x00XXXXXX']['type'] = "ClassName *"

# 添加结构体成员 (增量)
ann['structs']['ClassName']['known_members']['OFFSET'] = {
    "name": "m_fieldName", "type": "int", "source": "binary:EVIDENCE"
}
```

### Step 4: 验证 (apply → export → 检查质量)

```bash
# Apply 到 IDA
~/ida-pro-9.1/idat -A -S"tools/ida/pal3_apply_annotations.py" original/PAL3.exe.91.i64

# 重新导出
~/ida-pro-9.1/idat -A -S"tools/ida/pal3_export_only.py" original/PAL3.exe.91.i64

# 检查改进：目标函数的 decomp 是否用了成员名
python3 -c "
import json
d = json.load(open('asm/pal3/decomp/TARGET_ADDR.json'))
print(d['decompiled_c'][:1000])
"
```

### Step 5: 提交

```bash
git add -f asm/pal3/annotations.json
git commit -m "iter(pal3): #N — [本轮焦点简述]

[Metrics]
  Functions named: XXXX
  Struct members: XXXX
  Focus: [聚焦的类/模块]
  Result: [具体改善]"
git push
```

## 质量指标

```
=== annotations.json status ===
functions: XXXX (目标: 覆盖所有有意义的函数)
globals:   XXXX with type / XXXX total
structs:   XXX classes, XXXX members
  verified: XXXX (pdb_verified / binary / gen_headers)
  unverified: XXXX
```

## 核心原则

1. **annotations.json 是唯一输出** — 每轮迭代的成果必须体现在 JSON 中
2. **PDB 是参考不是权威** — 偏移需要从 PAL3 二进制验证
3. **增量叠加** — 结构体成员只加不删，新发现的字段直接追加
4. **不做编译修复** — 那是标注收敛后的工作
5. **ROI 驱动** — 选收益最大的改进点，不做边角优化

## 退出条件

当以下指标趋于稳定（边际收益递减）时，结束标注阶段：
- sub_ 函数数量不再下降
- 结构体空洞不再减少
- 新增函数名/类型的速度明显放缓

然后切换到：编译修复 → 字节匹配阶段。
