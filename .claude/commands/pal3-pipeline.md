# PAL3 标注迭代管线

<CRITICAL-INSTRUCTION>
当前阶段：**IDA 标注阶段**。源码是生成物，不手动编辑。
唯一的工作目标：提升 annotations.json 的数据质量。
编译验证/字节匹配是标注收敛后的工作，当前不做。
</CRITICAL-INSTRUCTION>

## 环境

```
IDA:         $IDA  (从 CLAUDE.md 或用户环境获取，典型值: idat.exe 的完整路径)
IDB:         original/PAL3.exe.i64
Annotations: asm/pal3/annotations.json
Decomp:      asm/pal3/decomp/*.json
Scripts:     tools/ida/pal3_*.py
```

首次使用时，确认 IDA 路径并设置变量：
```powershell
# 确认 IDA 安装位置（用户提供或搜索）
$IDA = (Get-ChildItem "D:\Program Files\IDA*","C:\Program Files\IDA*" -Filter "idat.exe" -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1).FullName
$I64 = "D:\workspace\PAL3Decomp\original\PAL3.exe.i64"
```

## 数据架构

```
annotations.json (唯一可信源，存差分)
  ├── functions: {addr → {name, signature}}        — 幂等覆盖
  ├── globals:   {addr → {name, type}}             — 幂等覆盖
  ├── structs:   {class → {size, known_members}}   — 增量叠加
  └── enums:     {name → {values}}                 — 幂等覆盖
```

## 单轮迭代流程

### Step 1: 选择焦点

从 annotations.json 中找改进空间最大的方向：

```powershell
# 函数统计
python -c "import json; ann=json.load(open('asm/pal3/annotations.json')); print('Named functions:', len(ann['functions']))"

# 结构体空洞
python -c "import json; ann=json.load(open('asm/pal3/annotations.json')); [print('  %s: %d members' % (n, len(s.get('known_members',{})))) for n,s in sorted(ann['structs'].items(), key=lambda x: len(x[1].get('known_members',{}))) if len(s.get('known_members',{})) < 5]"

# 全局变量缺类型
python -c "import json; ann=json.load(open('asm/pal3/annotations.json')); print('Globals without type:', sum(1 for g in ann['globals'].values() if not g.get('type')), '/', len(ann['globals']))"
```

选择策略（按 ROI 排序）：
1. **高引用 sub_ 函数命名** — 从 xref 找被最多函数引用的 sub_，分析其逻辑命名
2. **核心类结构体填充** — CCBSystem/Stage/RoleState/UI 的空洞成员
3. **全局变量类型标注** — 高引用的无类型全局变量
4. **函数签名修正** — void* 参数 → 具体类型

### Step 2: 分析 + 标注

**工作方式**：读 decomp JSON + 二进制字节 → 推断信息 → 更新 annotations.json

```powershell
# 读取函数反编译（从已有 decomp JSON）
python -c "import json; d=json.load(open('asm/pal3/decomp/FILENAME.json')); print(d['decompiled_c'][:1000])"

# 读取二进制字节 (确认偏移，注意 file_offset = VA - 0x400000)
python -c "
with open('original/PAL3.exe','rb') as f:
    f.seek(0xVA_ADDR - 0x400000)
    print(f.read(SIZE).hex(' '))
"

# 查询 PDB 类定义 (PAL3A 参考，偏移需从 PAL3 二进制验证)
python -c "import json; [print('+0x%04X %-30s %s' % (m['offset'], m['type'], m['name'])) for c in json.load(open('asm/pal3a/pdb_export.json'))['classes'] if c['name']=='TARGET' for m in c.get('data_members',[])]"
```

### Step 3: 更新 annotations.json

<HARD-REQUIREMENT>
**函数标注必须同时包含：名字 + 完整签名（返回类型、调用约定、类限定、参数类型、参数名）。**
**全局变量标注必须同时包含：语义名 + 类型。**
缺少任何一项不得提交。禁止提交 `_DWORD *this, int a2` 这种 IDA 原始参数名。
</HARD-REQUIREMENT>

```python
# 函数：必须有 name + signature（含类限定名、参数类型、参数名）
ann['functions']['0x00XXXXXX'] = {
    "name": "UIListBox::GetItem",
    "signature": "int __thiscall UIListBox::GetItem(int nIndex)"
    # 禁止: "int __thiscall(_DWORD *this, int a2)"
}

# 全局变量：必须有 name + type
ann['globals']['0x00XXXXXX'] = {
    "name": "g_pGfxManager",
    "type": "gbGfxManager *"
    # 禁止: {"name": "dword_BFDA60"} 或 {"name": "g_pGfxManager"} (缺type)
}

# 结构体成员 (增量叠加)
ann['structs']['ClassName']['known_members']['OFFSET'] = {
    "name": "m_fieldName", "type": "int", "source": "binary:EVIDENCE"
}
```

### Step 4: 验证

验证分两种模式。**日常迭代用快速验证**，只在需要全量重生成代码时才做全量导出。

#### 4a. 快速验证（单函数，~15 秒）

Apply annotations 后，用 `pal3_quick_decompile.py` 验证目标函数的 Hex-Rays 输出是否改善：

```powershell
# 1. Apply annotations 到 IDB（修改 i64，~30s）
& $IDA -A "-Stools\ida\pal3_apply_annotations.py" $I64

# 2. 快速反编译目标函数查看效果（不修改 decomp JSON）
$env:PAL3_VERIFY_ADDR = "0x004CDA10"
& $IDA -A "-Stools\ida\pal3_quick_decompile.py" $I64
```

验证要点：
- 函数名、参数类型是否正确显示
- 结构体成员访问是否用了语义名（不再是 `_gap_XXX` 或 `field_XXX`）
- `sub_XXXXXX` 调用是否变成了有意义的名字

#### 4b. 全量导出（更新所有 decomp JSON + 重生成代码，~3 分钟）

仅在以下情况执行：
- 一轮标注完成，准备提交并观察整体改进效果
- 需要重新生成 .cpp/.h 文件

```powershell
# 1. Apply annotations（如果 4a 还没做）
& $IDA -A "-Stools\ida\pal3_apply_annotations.py" $I64

# 2. 全量导出 decomp JSON（~130s，5400+ 函数）
& $IDA -A "-Stools\ida\pal3_export_only.py" $I64

# 3. 重生成头文件 + 源码
python tools/gen_headers.py
python tools/gen_cpp.py --force-all

# 4. 检查改善效果
# sub_ 前向声明数量
Select-String -Path "src\pal3\**\*.cpp" -Pattern "^int sub_" | Measure-Object
# 未命名全局变量数量
Select-String -Path "src\pal3\**\*.cpp" -Pattern "^extern.*dword_" | Measure-Object
```

### Step 5: 提交

```powershell
git add asm/pal3/annotations.json
git commit -m "iter(pal3): #N — [本轮焦点简述]

[Metrics]
  Functions named: XXXX
  Struct members: XXXX
  Focus: [聚焦的类/模块]
  Result: [具体改善]

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
git push
```

## IDA 脚本清单

| 脚本 | 用途 | 耗时 | 调用方式 |
|------|------|------|----------|
| `pal3_apply_annotations.py` | 把 annotations.json 写入 IDB | ~30s | `& $IDA -A "-Stools\ida\pal3_apply_annotations.py" $I64` |
| `pal3_quick_decompile.py` | 快速反编译单函数（验证） | ~15s | 设 `$env:PAL3_VERIFY_ADDR="0xADDR"` 后调用 |
| `pal3_export_only.py` | 全量导出 decomp JSON | ~130s | `& $IDA -A "-Stools\ida\pal3_export_only.py" $I64` |
| `pal3_master_pipeline.py` | 从零搭建 IDB（PDB 基础层） | 一次性 | 仅首次或重建时 |

## 恢复流程（从空 IDB 重建）

```powershell
# Layer 1-3: PDB base + FLIRT + basic names
& $IDA -A "-Stools\ida\pal3_master_pipeline.py" $I64

# Layer 4: annotations 差分层
& $IDA -A "-Stools\ida\pal3_apply_annotations.py" $I64

# Layer 5: 导出
& $IDA -A "-Stools\ida\pal3_export_only.py" $I64

# Layer 6: 代码生成
python tools/gen_headers.py
python tools/gen_cpp.py --force-all
```

## 核心原则

1. **annotations.json 是唯一输出** — 每轮迭代的成果必须体现在 JSON 中
2. **函数标注 = 名字 + 签名** — 禁止只标名字不标签名，签名必须有语义参数名和正确类型
3. **全局变量标注 = 名字 + 类型** — 禁止只标名字不标类型
4. **PDB 是参考不是权威** — PAL3A PDB 的偏移/结构需从 PAL3 二进制验证
5. **增量叠加** — 结构体成员只加不删，新发现的字段直接追加
6. **快速验证优先** — 日常用 quick_decompile 验证单函数，全量导出仅在提交前
7. **ROI 驱动** — 选收益最大的改进点，不做边角优化

## 退出条件

当以下指标趋于稳定（边际收益递减）时，结束标注阶段：
- sub_ 函数数量不再下降
- 结构体空洞不再减少
- 新增函数名/类型的速度明显放缓

然后切换到：编译修复 → 字节匹配阶段。
