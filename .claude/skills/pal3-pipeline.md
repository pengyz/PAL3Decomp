# PAL3 迭代管线

持续执行 IDA 标注 → 导出 → 生成 → 编译 → 质量评估 → 规划 循环，直到目标达成。

## 核心循环

```
┌─────────────────────────────────────────────────────────────┐
│  1. 质量评估 (评估当前代码状态，确定改进方向)                    │
│  2. IDA 标注 (在 IDA 中修复类型/签名/命名)                      │
│  3. IDA 导出 (重新导出反编译结果)                               │
│  4. 代码生成 (gen_headers + gen_cpp)                           │
│  5. 编译验证 (VC6 编译，统计通过率和错误分布)                    │
│  6. 方案探讨 (分析失败原因，确定下一轮改进点)                    │
│  └──→ 回到 1                                                  │
└─────────────────────────────────────────────────────────────┘
```

## Phase 1: 质量评估

对当前生成的代码进行定量分析：

```bash
# 编译通过率
python tools/pal3_quality.py compile    # VC6 编译所有文件，报告 pass/fail

# 代码质量指标
python tools/pal3_quality.py metrics    # 统计: sub_ 引用、unnamed globals、void* 参数、硬编码偏移

# 对比上次
python tools/pal3_quality.py diff       # 与上次评估结果对比
```

指标定义：
- **sub_ 引用数**: 代码中调用未命名函数的次数（越少越好）
- **unnamed globals**: dword_/byte_/off_ 等未命名全局变量引用
- **硬编码偏移**: `*(this + N)` 或 `member[N * stride + offset]` 模式
- **void* 参数**: 函数参数类型为 void* 的数量
- **stdiobuf/ios_base 引用**: IDA 类型误判残留
- **VC6 编译通过率**: 能通过 VC6 单独编译的 .cpp 文件比例

## Phase 2: IDA 标注

根据质量评估确定的改进方向，在 IDA 中做标注。

### 优先级排序

1. **结构体成员完善**（ROI 最高）— 一个类的布局修好，所有引用该类的函数都改善
2. **函数签名修正**（高 ROI）— 修正参数类型后 Hex-Rays 输出正确
3. **函数命名**（中 ROI）— 可读性提升
4. **全局变量类型**（中 ROI）— 传播效应

### 操作方式

```bash
# 写 IDAPython 脚本
# tools/ida/pal3_iter_NNN.py

# 运行
idat.exe -A -S"tools/ida/pal3_iter_NNN.py" original/PAL3.exe.i64

# 检查日志
cat tools/ida/_logs/pal3_iter_NNN_log.txt
```

### 标注规则

- **结构体导入**: 使用 `udt_type_data_t` API 精确设置偏移（不用 parse_decl）
- **函数签名**: 使用 `idc.SetType(addr, sig)` 设置完整签名
- **函数命名**: 使用 `ida_name.set_name(addr, name, SN_FORCE)`
- **全局变量**: `ida_name.set_name` + `ida_typeinf.apply_tinfo`
- **数据来源**: PAL3A PDB (`asm/pal3a/pdb_export.json`) + DIA SDK + 二进制分析

### 验证标注效果

标注后选 2-3 个受影响的函数，用 Hex-Rays 反编译检查输出质量是否改善。

## Phase 3: IDA 导出

```bash
idat.exe -A -S"tools/ida/pal3_export_only.py" original/PAL3.exe.i64
# 输出: asm/pal3/decomp/*.json (5414 函数)
# 日志: tools/ida/_logs/pal3_export_only_log.txt
```

验证导出成功：检查 named 函数数是否增加。

## Phase 4: 代码生成

```bash
# 重新生成头文件（始终全量）
python tools/gen_headers.py

# 重新生成 cpp（增量或全量）
python tools/gen_cpp.py --force-all     # IDA 改动后全量
python tools/gen_cpp.py ClassName       # 只更新指定类

# 清理不应存在的系统头文件
# (gen_headers.py 的 SKIP_CLASSES 控制)
```

生成后快速验证：
```bash
# 检查关键指标
python -c "统计 sub_ 和 unnamed globals 数量"
```

## Phase 5: 编译验证

```bash
# VC6 单文件编译
$cl = "tools/compilers/msvc6.0/Bin/CL.EXE"
& $cl /c /nologo /W0 /I"include" /I"tools/compilers/msvc6.0/Include" /I"tools/vc6/Include" src/pal3/XXX.cpp /FoNUL

# 批量编译统计
# 使用 PowerShell 遍历所有 .cpp，统计 pass/fail 和错误码分布
```

### 编译错误分类

| 错误码 | 含义 | 修复方向 |
|--------|------|----------|
| C2027 | 未定义类型使用 | IDA: 导入完整结构体 |
| C2065 | 未声明标识符 | IDA: 命名全局变量/函数 |
| C2440 | 类型转换 | IDA: 修正函数签名参数类型 |
| C2511 | 成员函数未找到 | gen_headers: 签名不匹配 |
| C2533 | ctor 有返回类型 | gen_cpp: 构造函数处理 |
| C2673 | 全局函数用 this | gen_cpp: 函数归属错误 |
| C4234 | __thiscall 关键字 | gen_cpp: 去除调用约定 |

### 错误根因判定

- **是 IDA 类型问题** → Phase 2 修 IDA
- **是 gen_cpp/gen_headers 逻辑问题** → 修管线脚本
- **是边角代码/系统库** → 低优先级，记录跳过

## Phase 6: 方案探讨

每轮迭代后分析：

1. **本轮收益**: 哪些指标改善了，改善多少
2. **瓶颈分析**: 当前最大的阻塞是什么
3. **ROI 评估**: 下一步做什么收益最大
4. **是否需要新工具**: DIA SDK 导出、新后处理规则等

### 停止条件

- 核心游戏逻辑的主要类（CCBSystem、CCBStage、SceneMgr、RoleSystem、PalScript、UI 系统）的代码质量达标
- "达标"定义: 成员访问用正确字段名、函数调用用正确方法名、控制流清晰可读
- 边角函数（CRT stub、系统回调、纯算术小函数）可以不追求完美

## 工具命令速查

```bash
# IDA 操作
idat.exe -A -S"tools/ida/SCRIPT.py" original/PAL3.exe.i64

# DIA SDK 导出结构体/继承
python tools/dia_export_structs.py
python tools/dia_export_bases.py

# 代码生成
python tools/gen_headers.py
python tools/gen_cpp.py --force-all

# VC6 编译单文件
& "tools/compilers/msvc6.0/Bin/CL.EXE" /c /nologo /W0 /I"include" /I"tools/compilers/msvc6.0/Include" /I"tools/vc6/Include" FILE.cpp /FoNUL

# 质量统计
python -c "import os,re; ..."  # 自定义统计脚本
```

## 关键原则回顾

- **不做 workaround**: 不为了编译通过而降低代码质量
- **IDA 先行**: 代码中的硬编码偏移、错误类型 → 回 IDA 修
- **ROI 驱动**: 聚焦核心游戏逻辑，边角代码宽容度高
- **累积效应**: 结构体/签名修复一次，所有引用函数受益
- **可重复**: 每次 gen_cpp --force-all 应该得到一致的高质量输出
