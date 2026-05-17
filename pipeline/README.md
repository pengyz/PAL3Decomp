# PAL3 反编译管线

从 PAL3.exe 二进制到可编译 C++ 源码的完整工作流。

## 目录结构

```
pipeline/
├── ida/                          # IDA Pro 脚本（在 IDA 中运行）
│   ├── master_pipeline.py        # 初始化 IDB: PDB 导入 + FLIRT + 全局变量
│   ├── apply_annotations.py      # 应用标注到 IDB（structs + functions + vtables）
│   ├── export_full.py            # 全量导出 Hex-Rays 反编译 → decomp JSON
│   ├── query_todo_fields.py      # 查询: 扫描所有 _todo_ 字段 xref + 上下文
│   ├── query_highref_fields.py   # 查询: 补充高引用字段的反编译上下文
│   ├── query_class_full.py       # 查询: 指定类全部方法的字段上下文
│   ├── query_method.py           # 查询: 指定偏移的所有内存访问
│   ├── query_offsets.py          # 查询: 结构体特定偏移的访问模式
│   ├── query_range.py            # 查询: 偏移范围内的所有访问
│   ├── import_gbengine_types.py  # 导入 gbengine PDB 类型
│   ├── find_strides.py           # 分析嵌入子对象 stride
│   ├── find_bad_lines.py         # 检测 decomp 中的问题行
│   └── _logs/                    # 查询输出（gitignored）
├── gen/                          # 代码生成管线（命令行 Python）
│   ├── codegen.py                # 入口: python codegen.py all/headers/cpp
│   ├── data.py                   # DataStore: 加载 annotations + binary
│   ├── ast_transform.py          # tree-sitter OOP 调用变换
│   └── stages/                   # 4-stage transform pipeline
│       ├── stage1_structural.py  # AST: 函数签名修改
│       ├── stage2_semantic.py    # AST: OOP 调用重写
│       ├── stage3_cleanup.py     # AST: IDA 残留清理
│       ├── stage4_substitution.py# AST: token 替换
│       ├── collect.py            # 从 decomp JSON 收集函数
│       ├── emit_cpp.py           # 生成 .cpp
│       └── emit_headers.py       # 生成 .h
├── check_annotations.py          # 校验标注合法性（0 errors 门槛）
├── verify_offset.py              # 验证全局实例字段偏移
├── compare.py                    # 字节对比（生成 vs 原始）
└── callgraph.py                  # 调用图分析
```

## 完整工作流

### 从零开始（首次设置）

```bash
# 1. 创建 raw IDB（只做一次）
$IDA -B original/PAL3.exe
mv original/PAL3.exe.i64 original/PAL3.exe.raw.i64

# 2. 初始化 + 应用标注 + 导出
cp original/PAL3.exe.raw.i64 original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/master_pipeline.py" original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/apply_annotations.py" original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/export_full.py" original/PAL3.exe.i64

# 3. 生成源码
python pipeline/gen/codegen.py all

# 4. 编译
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake
ninja -C build -k 0
```

### 日常迭代（标注更新后）

```bash
# 标注变更后重建 IDB + 导出 + 生成
cp original/PAL3.exe.raw.i64 original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/master_pipeline.py" original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/apply_annotations.py" original/PAL3.exe.i64
$IDA -A -S"pipeline/ida/export_full.py" original/PAL3.exe.i64
python pipeline/gen/codegen.py all
ninja -C build -k 0
```

### 仅重新生成代码（标注未变，只改了 codegen）

```bash
python pipeline/gen/codegen.py all
ninja -C build -k 0
```

## 数据流

```
原始二进制 (original/PAL3.exe)
    ↓ master_pipeline (PDB + FLIRT)
IDB (original/PAL3.exe.i64)
    ↓ apply_annotations (data/annotations/)
IDB (带完整类型信息)
    ↓ export_full
反编译 JSON (asm/pal3/decomp/*.json)
    ↓ codegen.py (4-stage AST pipeline)
C++ 源码 (src/pal3/ + include/pal3/)
    ↓ CMake + VC6
PAL3.exe (字节匹配验证)
```

## 关键约束

- `data/annotations/` 是唯一手工编辑的数据源
- IDB 是生成物（可随时从 raw + annotations 重建）
- decomp JSON 是生成物（可随时从 IDB 重新导出）
- src/ + include/ 是生成物（可随时从 decomp JSON 重新生成）
- 所有修改必须回到 data/annotations/ 层
