# PAL3 反编译管线

从 PAL3.exe 二进制到可编译 C++ 源码的完整工作流。

## 目录结构

```
pipeline/
├── ida/                          # IDAPython 脚本（在 IDA Pro 中运行）
│   ├── master_pipeline.py        # Stage 1: PDB 导入 + FLIRT + 全局变量 + 首次导出
│   ├── apply_annotations.py      # Stage 2: 应用标注到 IDB
│   ├── export_full.py            # Stage 3a: 全量导出 decomp JSON
│   ├── export_incremental.py     # Stage 3b: 增量导出（只导出签名变化的函数）
│   ├── pal3a_text.sig            # FLIRT 签名文件
│   └── pal3a_text.pat            # FLIRT 模式文件
├── gen/                          # 代码生成（Python，命令行运行）
│   ├── gen_headers.py            # Stage 4a: 生成 .h 头文件
│   ├── gen_cpp.py                # Stage 4b: 生成 .cpp 源码
│   └── ast_transform.py          # OOP 调用转换（被 gen_cpp 调用）
├── data/                         # 数据文件
│   ├── annotations/              # 标注数据（唯一手工编辑的数据源）
│   │   ├── manifest.json         # 索引和统计
│   │   ├── functions.json        # 函数名 + 签名 (2183 个)
│   │   ├── globals.json          # 全局变量名 + 类型 (5001 个)
│   │   ├── vtables.json          # 虚函数表定义 (112 个)
│   │   ├── enums.json            # 枚举定义
│   │   └── structs/              # 结构体定义（每个类一个文件）
│   │       ├── CCBSystem.json
│   │       ├── RoleSystem.json
│   │       └── ...               # 751 个文件
│   └── pdb/                      # PDB 导出数据（预生成，只读参考）
│       ├── pdb_export.json       # PAL3A.PDB 完整类导出 (1251 classes)
│       └── globals_export.json   # PAL3A 全局变量名
├── check_annotations.py          # 校验标注数据合法性
├── compare.py                    # 字节对比工具
├── callgraph.py                  # 调用图管理
└── README.md                     # 本文件
```

## 工作流

### 首次初始化（从零创建 IDB）

```bash
# 1. 创建 IDB
~/ida-pro-9.1/idat -B -o original/PAL3.exe.i64 original/PAL3.exe

# 2. 运行 master pipeline (导入 PDB 类型 + FLIRT + 全局变量 + 首次导出)
~/ida-pro-9.1/idat -A -S"pipeline/ida/master_pipeline.py" original/PAL3.exe.i64

# 3. 应用标注 (函数名、签名、结构体、vtable)
~/ida-pro-9.1/idat -A -S"pipeline/ida/apply_annotations.py" original/PAL3.exe.i64

# 4. 导出反编译 JSON
~/ida-pro-9.1/idat -A -S"pipeline/ida/export_full.py" original/PAL3.exe.i64

# 5. 生成 C++ 头文件和源码
python3 pipeline/gen/gen_headers.py
python3 pipeline/gen/gen_cpp.py --force-all
```

### 日常迭代（修改标注后）

```bash
# 1. 编辑标注（直接编辑 struct 文件）
vim pipeline/data/annotations/structs/CCBSystem.json

# 2. 校验
python3 pipeline/check_annotations.py

# 3. 应用到 IDA + 增量导出
~/ida-pro-9.1/idat -A -S"pipeline/ida/apply_annotations.py" original/PAL3.exe.i64
~/ida-pro-9.1/idat -A -S"pipeline/ida/export_incremental.py" original/PAL3.exe.i64

# 4. 增量生成（只重新生成变化的文件）
python3 pipeline/gen/gen_headers.py
python3 pipeline/gen/gen_cpp.py
```

### 编译验证

```bash
# 配置（首次）
cmake -B build/pal3 -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake -DBUILD_TARGET=pal3

# 编译
cmake --build build/pal3

# 字节对比
python3 pipeline/compare.py --compile src/pal3/GameBase/PAL3.cpp --func "?Destroy@PAL3@@SAXXZ"
```

## 数据源优先级

```
Layer 3 (最高): annotations/ — 人工标注 + 二进制推断
Layer 2:        pdb/         — PAL3A 调试符号（成员名可靠，偏移需验证）
Layer 1 (最低): IDA auto     — FLIRT 签名 + 类型传播
```

annotations 数据会覆盖 PDB 数据（通过 IDA 的 `NTF_REPLACE` 标志）。

## 标注文件格式

### functions.json
```json
{
  "0x004014F0": {
    "name": "CCBAI::GetValue",
    "signature": "char __thiscall(CCBAI *this, int a1, int a2)"
  }
}
```

### structs/CCBSystem.json
```json
{
  "name": "CCBSystem",
  "binary_size": 90840,
  "pdb_size": 90840,
  "base_class": null,
  "base_size": 0,
  "known_members": {
    "0": { "name": "m_pUtil", "type": "CCBSystem *", "source": "pdb_verified" },
    "4": { "name": "m_pUI", "type": "CCBUI *", "source": "pdb_verified" }
  }
}
```

### vtables.json
```json
{
  "off_56AE10": {
    "address": "0x0056AE10",
    "class": "UIWnd",
    "methods": [
      { "address": "0x00445E70", "name": "UIWnd::Destroy", "signature": "..." }
    ]
  }
}
```

## 输出

- `include/pal3/gen/` — 自动生成的头文件（581 个）
- `src/pal3/` — 自动生成的 C++ 源码（151 个）
- `asm/pal3/decomp/` — IDA 反编译 JSON（5399 个，gitignored）

这些都是**生成物**，不手动编辑。改进代码质量的方式是修改 `pipeline/data/annotations/` 中的标注数据。
