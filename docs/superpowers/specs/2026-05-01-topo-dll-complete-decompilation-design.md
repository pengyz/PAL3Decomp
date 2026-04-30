# topo.dll 完整反编译设计方案

**日期：** 2026-05-01  
**作者：** Claude Sonnet 4.5  
**项目：** PAL3 topo.dll 匹配反编译  
**目标：** 生成字节精确匹配的 topo.dll，完全替代游戏原始 DLL

---

## 1. 项目目标

### 1.1 主要目标
生成一个与原始 topo.dll 字节精确匹配的 DLL 文件，使其能够：
- 完全替代游戏目录中的原版 topo.dll
- 游戏正常启动、运行、无崩溃
- 所有 3D 数学运算功能正确
- 所有导出函数行为与原版一致

### 1.2 质量标准
- **字节匹配率：** 核心函数 ≥ 90%（目标 100%）
- **功能完整性：** 所有 414 个函数可用
- **代码质量：** 无指针偏移操作，使用结构体成员访问
- **可维护性：** 清晰的代码结构，完整的注释

### 1.3 当前状态
- ✅ 已实现：115/414 函数 (27%)
- ✅ 编译系统：完整且工作正常
- ✅ 工具链：进度跟踪、二进制对比
- ❌ 剩余：299 个函数待实现
- ❌ 字节匹配：尚未开始验证

---

## 2. 整体架构

### 2.1 三阶段实施策略

#### 阶段 0：结构体定义和代码重构（1 天）
**目标：** 建立高质量代码基础

**任务：**
1. 完善 `include/pal3_structs.h` 中的所有结构体定义
2. 定义缺失的核心结构体：
   - `TopoGeom` - 拓扑几何主对象
   - `TopoFaceVector` - 面元素向量
   - `TopoFace` - 单个面数据（0x30 字节）
   - `TopoMeshData` - 网格数据（0x34 字节）
3. 重构现有代码（topo_internal.cpp 等）
4. 消除所有指针偏移操作，改用结构体成员访问

**交付标准：**
- ✅ 所有结构体定义完整，字段对齐正确
- ✅ 现有代码无 `(type*)((int)ptr + offset)` 形式
- ✅ 编译通过，sizeof() 验证通过
- ✅ 功能验证：现有测试不退化

#### 阶段 1：快速实现核心函数（3 天）
**目标：** 实现所有需要手工编写的函数（~160 个）

**实施方法：** 按函数大小递进
- **批次 1：** < 50 字节函数（~100 个）→ 1.5 天
- **批次 2：** 50-150 字节函数（~40 个）→ 1 天  
- **批次 3：** > 150 字节函数（~20 个）→ 0.5 天

**实施流程：**
```
1. 运行 python tools/analyze_priority.py
   → 生成按大小排序的函数列表
2. 对每个函数：
   a. 读取 asm/topo/<func>.json
   b. 分析 Ghidra 反编译的 C 代码
   c. 识别数据结构，映射到已定义的 struct
   d. 重写为清晰的 C++ 代码（使用结构体访问）
   e. 添加注释（地址、大小、功能说明）
   f. 编译验证
3. 每完成 20 个函数，提交到 git
```

**交付标准：**
- ✅ 进度：115 → 275 (66%)
- ✅ 所有核心函数编译通过
- ✅ 代码符合质量标准（无偏移操作）
- ✅ 每个函数有完整注释

#### 阶段 2：链接 CRT 和异常处理（0.5 天）
**目标：** 达到 100% 函数覆盖

**任务：**
1. **识别 CRT 函数（~80 个）：**
   - malloc, free, realloc, calloc
   - memcpy, memset, memmove, memcmp
   - sqrt, sin, cos, asin, acos, atan, atan2, pow
   - sprintf, _snprintf 等字符串函数
   - _ftol, _CIpow 等浮点转换

2. **配置链接选项：**
   ```cmake
   # CMakeLists.txt 修改
   target_link_libraries(topo 
       msvcrt.lib      # C 运行时库
       libcmt.lib      # 多线程静态库
   )
   ```

3. **处理异常处理函数（~60 个）：**
   - Unwind@ 系列函数（编译器自动生成）
   - __CxxFrameHandler 系列
   - 使用 `/EHsc` 编译选项自动生成

**交付标准：**
- ✅ 进度：275 → 414 (100%)
- ✅ 链接无错误，无未定义符号
- ✅ DLL 大小接近原始（104 KB ± 10%）

#### 阶段 3：字节匹配调优（4 天）
**目标：** 核心函数字节精确匹配

**实施方法：**
1. **开发匹配工具（0.5 天）：**
   - `tools/batch_compare.py` - 批量对比
   - `tools/disasm_compare.py` - 汇编并排对比
   - `tools/record_match_pattern.py` - 记录匹配技巧

2. **逐函数匹配（3 天）：**
   - 小函数（< 50 字节）：1 天（易匹配）
   - 中等函数（50-150 字节）：1.5 天（中等难度）
   - 大函数（> 150 字节）：0.5 天（难，但数量少）

3. **匹配技术：**
   - 调整变量声明顺序（影响栈布局）
   - 改变循环形式（for/while/do-while）
   - 调整表达式写法（`if (ptr)` vs `if (ptr != NULL)`）
   - 控制内联（`__forceinline` / `__declspec(noinline)`）
   - 调整编译选项（`/O1` vs `/O2`, `/Oy`, `/Oi`）

4. **匹配流程：**
   ```
   实现函数 → 编译 → compare_function.py
      ↓                       ↓
      └─ 不匹配? → 查看汇编差异 → 调整代码/选项 → 重编译
      ↓
      匹配! → record_match_pattern.py → 下一个
   ```

**交付标准：**
- ✅ 核心函数匹配率 ≥ 90%
- ✅ 所有导出函数字节匹配
- ✅ 匹配模式记录到 `docs/matching_patterns.md`
- ✅ 生成 HTML 匹配报告

#### 阶段 4：测试和修复（1 天）
**目标：** 验证 DLL 在游戏中正常工作

**测试层次：**

1. **Level 1：编译验证**
   ```bash
   ./run_verify.bat
   # 检查：编译通过、链接成功、DLL 生成
   ```

2. **Level 2：结构验证**
   ```bash
   dumpbin /exports build/verify/topo.dll > exports_new.txt
   dumpbin /exports original/topo.dll > exports_old.txt
   diff exports_old.txt exports_new.txt
   # 检查：导出函数数量、序号、地址是否匹配
   ```

3. **Level 3：字节匹配验证**
   ```bash
   python tools/batch_compare.py --all --report html
   # 生成 reports/match_report.html
   # 检查：整体匹配率、失败函数列表
   ```

4. **Level 4：游戏功能验证**
   - 备份原版 topo.dll
   - 替换为新生成的 DLL
   - 启动游戏，观察：
     - 能否加载到主菜单
     - 能否进入游戏场景
     - 3D 渲染是否正常
     - 移动、旋转、缩放是否流畅
   - 运行 30 分钟，检查稳定性

**交付标准：**
- ✅ 所有验证层次通过
- ✅ 游戏运行 30 分钟无崩溃
- ✅ 无明显的渲染或逻辑错误
- ✅ 测试报告完整

---

## 3. 函数分类和实现顺序

### 3.1 函数分类

#### A. 核心函数（需手工实现+匹配）：~160 个

**A1. 数学类函数（~60 个）**
| 类 | 已实现 | 剩余 | 优先级 |
|---|--------|------|--------|
| gbVec3D | 18 | ~5 | 高 |
| gbMatrix4 | 35 | ~15 | 高 |
| gbQuaternion | 32 | ~10 | 高 |
| gbMatrixStack | 15 | ~5 | 中 |
| gbRotMatrix | 7 | ~5 | 中 |
| 其他数学辅助 | - | ~20 | 低 |

**A2. TopoGeom 函数（~30 个）**
- TopoGeom 核心方法：~15 个
- TopoFaceVector 操作：已完成（Insert, Erase, Size）
- TopoMeshData 相关：~10 个
- vtable 定义和虚函数：~5 个

**A3. 内部辅助函数（~70 个）**
- 向量操作包装函数
- 内存管理包装（operator new/delete 变体）
- 数据结构操作（类似 FUN_10005040 的 vector size 系列）

#### B. CRT 函数（链接库）：~80 个
- 内存：malloc, free, realloc, calloc, memcpy, memset, memmove
- 数学：sqrt, sin, cos, asin, acos, atan, atan2, pow, floor, ceil
- 字符串：sprintf, _snprintf, strlen, strcmp, strcpy
- 浮点：_ftol, _CIpow, _fltused

#### C. 异常处理（编译器生成）：~60 个
- Unwind@ 系列：栈展开函数
- __CxxFrameHandler: C++ 异常处理帧
- SEH 相关：结构化异常处理

### 3.2 实现顺序（阶段 1）

#### 批次 1：< 50 字节函数（~100 个，1.5 天）
**特点：** 简单、快速、易匹配

**示例函数类型：**
- Getter/Setter：返回或设置单个字段
- 简单算术：a + b, a - b, a * b
- 向量长度查询：TopoFaceVector_Size 类似函数
- 常量返回：返回固定值

**实施策略：**
- 每天实现 60-70 个函数
- 使用半自动化工具辅助（extract_structs.py）
- 编译频率：每 10 个函数编译一次
- 提交频率：每 20 个函数提交一次

#### 批次 2：50-150 字节函数（~40 个，1 天）
**特点：** 中等复杂度，有分支和循环

**示例函数类型：**
- 中等数学运算：矩阵乘法的小型辅助函数
- 条件逻辑：if-else 分支处理
- 简单循环：for/while 循环的数组操作
- 结构体初始化：多字段赋值

**实施策略：**
- 每天实现 35-45 个函数
- 重点关注循环和分支的写法（影响匹配）
- 编译频率：每 5 个函数编译一次
- 及时记录匹配技巧

#### 批次 3：> 150 字节函数（~20 个，0.5 天）
**特点：** 复杂逻辑，多层嵌套

**示例函数类型：**
- 复杂矩阵运算：矩阵求逆、特征值分解
- 多分支逻辑：switch-case 或多层 if-else
- 嵌套循环：双重或三重循环
- 大型数据结构操作：复杂的向量/列表操作

**实施策略：**
- 每个函数单独处理，仔细分析
- 参考 Ghidra 反编译的控制流图
- 先实现功能，后期专门匹配
- 编译频率：每个函数编译一次

---

## 4. 代码质量标准

### 4.1 结构体访问强制要求

**禁止形式：**
```cpp
// ❌ 不允许 - 指针偏移操作
int value = *(int*)((int)pThis + 0x0C);
*(int*)((int)pThis + 0x14) = pMesh;
int* pEnd = *(int**)((int)pThis + 0x08);
```

**必须形式：**
```cpp
// ✅ 必须 - 结构体成员访问
TopoGeom* geom = (TopoGeom*)pThis;
int value = geom->field_0C;
geom->pMeshData = pMesh;
int* pEnd = geom->faceVector.pEnd;
```

### 4.2 核心结构体定义

#### TopoGeom（拓扑几何对象）
```cpp
struct TopoGeom {
    void* vtable;              // +0x00: 虚函数表指针
    int type;                  // +0x04: 类型标识
    TopoFaceVector faceVector; // +0x08: 面向量（内嵌，12字节）
    TopoMeshData* pMeshData;   // +0x14: 网格数据指针
};
// 总大小: 0x18 (24 字节)
```

#### TopoFaceVector（面元素向量）
```cpp
struct TopoFaceVector {
    TopoFace* pBegin;    // +0x00: 起始指针
    TopoFace* pEnd;      // +0x04: 结束指针（指向最后一个元素之后）
    TopoFace* pCapacity; // +0x08: 容量指针（分配的结束位置）
};
// 总大小: 0x0C (12 字节)
// 类似 std::vector 的内存布局
```

#### TopoFace（单个面数据）
```cpp
struct TopoFace {
    int indices[3];      // +0x00: 顶点索引 (12 字节)
    int adjacency[3][2]; // +0x0C: 邻接数据 (24 字节)
    int extra[3];        // +0x24: 额外数据 (12 字节)
};
// 总大小: 0x30 (48 字节)
```

#### TopoMeshData（网格数据）
```cpp
struct TopoMeshData {
    void* pVertexBuffer;    // +0x00: 顶点缓冲区指针
    int vertexStride;       // +0x04: 顶点步长
    int vertexFlags;        // +0x08: 顶点标志
    int field_0C;           // +0x0C: 未知字段
    int field_10;           // +0x10: 未知字段
    int field_14;           // +0x14: 未知字段
    int field_18;           // +0x18: 未知字段
    int field_1C;           // +0x1C: 未知字段
    int bufferRowSize;      // +0x20: 缓冲区行大小
    int vertexCount;        // +0x24: 顶点数量
    int allocRowCount;      // +0x28: 分配的行数（至少16）
    int field_2C;           // +0x2C: 未知字段
    int field_30;           // +0x30: 未知字段
};
// 总大小: 0x34 (52 字节)
```

### 4.3 代码重构示例

**重构前（当前 topo_internal.cpp）：**
```cpp
int __fastcall TopoFaceVector_Size(void *pThis)
{
    int pBegin = *(int *)((int)pThis + 0x04);
    if (pBegin == 0) {
        return 0;
    }
    return (*(int *)((int)pThis + 0x08) - pBegin) / 0x30;
}
```

**重构后：**
```cpp
int __fastcall TopoFaceVector_Size(void *pThis)
{
    TopoFaceVector* vec = (TopoFaceVector*)pThis;
    if (vec->pBegin == NULL) {
        return 0;
    }
    // 指针相减自动计算元素数量
    return (vec->pEnd - vec->pBegin);
}
```

### 4.4 代码质量检查

**自动检查工具：** `tools/check_code_quality.py`
```bash
python tools/check_code_quality.py
# 输出：
# [ERROR] src/topo/file.cpp:123 - 发现指针偏移操作
# [WARN] src/topo/file.cpp:456 - TODO 标记未解决
```

**检查项目：**
- ✅ 无指针偏移操作（`(type*)((int)ptr + offset)`）
- ✅ 无 TODO/FIXME/STUB 标记
- ✅ 所有函数有注释（地址、大小、功能）
- ✅ 结构体 sizeof() 验证通过
- ✅ 无编译警告（/W3 级别）

---

## 5. 字节匹配调优方法

### 5.1 匹配工具链

#### 现有工具
- ✅ `python tools/compare_function.py <addr> <size>` - 单函数对比
- ✅ `python tools/progress_report.py` - 进度跟踪
- ✅ CMake `/FAcs` 选项 - 生成汇编列表

#### 新增工具

**1. 批量对比工具** `tools/batch_compare.py`
```bash
# 对比所有数学函数
python tools/batch_compare.py --category math

# 对比所有已实现函数
python tools/batch_compare.py --all

# 生成 HTML 报告
python tools/batch_compare.py --all --report html
# 输出: reports/match_report_2026-05-01.html
```

**输出示例：**
```
=== 匹配率统计 ===
总计: 160 个函数
完全匹配: 144 (90.0%)
部分匹配: 12 (7.5%)
不匹配: 4 (2.5%)

=== 不匹配函数 ===
0x10001234 (45 bytes) - 差异: 3 字节 (帧指针)
0x10005678 (128 bytes) - 差异: 8 字节 (循环展开)
...
```

**2. 汇编对比工具** `tools/disasm_compare.py`
```bash
python tools/disasm_compare.py 0x10001110 12 --side-by-side
```

**输出示例：**
```
原始 DLL                           编译输出
────────────────────────────────────────────────────────
10001110: PUSH EBP               PUSH EBP
10001111: MOV EBP, ESP           MOV EBP, ESP
10001113: MOV EAX, [ECX+0x4]     MOV EAX, [ECX+0x4]
10001116: TEST EAX, EAX        ! PUSH EBX            <- 差异
10001118: JZ 0x1000111b          TEST EAX, EAX
1000111a: RET                    JZ 0x1000111d
                                 POP EBX
                                 RET
```

**3. 匹配模式记录工具** `tools/record_match_pattern.py`
```bash
python tools/record_match_pattern.py \
  --addr 0x10001110 \
  --technique "去除 EBX 保存" \
  --before "使用局部变量导致 EBX 入栈" \
  --after "改为直接计算，避免使用 EBX"
# 自动追加到 docs/matching_patterns.md
```

### 5.2 常见匹配技术

#### 技术 1：变量声明顺序
**问题：** 栈布局不匹配

**解决：**
```cpp
// 可能不匹配
int a, b, c;

// 尝试调整顺序
int c;
int a;
int b;
```

#### 技术 2：循环形式
**问题：** 循环生成的汇编不同

**解决：**
```cpp
// 前向计数
for (int i = 0; i < n; i++) { }

// 后向计数（MSVC 6.0 常用）
for (int i = n; i > 0; i--) { }

// != 而不是 <（更接近原始汇编）
for (int i = 0; i != n; i++) { }

// while 代替 for
int i = n;
while (i--) { }
```

#### 技术 3：表达式形式
**问题：** 条件判断生成不同代码

**解决：**
```cpp
// 显式比较
if (ptr != NULL) { }  vs  if (ptr) { }

// 自增形式
x = x + 1;  vs  x += 1;  vs  ++x;  vs  x++;

// 三元运算符 vs if-else
result = (cond ? a : b);
// vs
if (cond) result = a; else result = b;
```

#### 技术 4：内联控制
**问题：** 函数被意外内联或未内联

**解决：**
```cpp
// 强制内联
__forceinline void must_inline() { }

// 禁止内联
__declspec(noinline) void must_not_inline() { }
```

#### 技术 5：寄存器使用
**问题：** 寄存器分配不同

**解决：**
```cpp
// 减少局部变量（减少寄存器压力）
// 合并相似的计算
// 调整计算顺序
```

#### 技术 6：编译选项
**问题：** 优化策略不匹配

**解决：**
```cmake
# 尝试不同优化级别
/O1  # 最小化大小（通常更接近 MSVC 6.0）
/O2  # 最大化速度

# 控制内联
/Ob0  # 禁用内联
/Ob1  # 仅 inline/__forceinline
/Ob2  # 任何合适的函数

# 帧指针
/Oy   # 省略帧指针（启用 EBP 优化）
/Oy-  # 保留帧指针

# 内部函数
/Oi   # 启用（memcpy → REP MOVSD）
/Oi-  # 禁用
```

### 5.3 匹配工作流程

```
┌─────────────────┐
│ 实现函数（C++） │
└────────┬────────┘
         ↓
┌─────────────────┐
│   编译 DLL      │
└────────┬────────┘
         ↓
┌─────────────────────────┐
│ compare_function.py     │
│ 字节对比                │
└────────┬────────────────┘
         ↓
    ┌────┴────┐
    │ 匹配？  │
    └────┬────┘
         │
    不匹配 ↓
┌─────────────────────────┐
│ disasm_compare.py       │
│ 查看汇编差异            │
└────────┬────────────────┘
         ↓
┌─────────────────────────┐
│ 分析差异原因：          │
│ - 变量顺序？            │
│ - 循环形式？            │
│ - 表达式写法？          │
│ - 编译选项？            │
└────────┬────────────────┘
         ↓
┌─────────────────────────┐
│ 调整代码或编译选项      │
└────────┬────────────────┘
         ↓
    重新编译 ─────┐
         ↑        │
         └────────┘
         
    匹配！ ↓
┌─────────────────────────┐
│ record_match_pattern.py │
│ 记录匹配技巧            │
└────────┬────────────────┘
         ↓
     下一个函数
```

### 5.4 匹配模式库

**文件位置：** `docs/matching_patterns.md`

**内容结构：**
```markdown
# MSVC 2022 字节匹配模式库

## 模式 1：去除栈帧指针
**问题：** 函数多了 PUSH EBP / MOV EBP, ESP / POP EBP
**原因：** 默认保留帧指针
**解决：** 添加 /Oy 编译选项
**适用：** 小函数（< 50 字节），不使用局部数组

## 模式 2：循环后向计数
**问题：** for 循环生成的汇编不同
**原因：** MSVC 6.0 倾向于后向计数
**解决：** 改为 for (int i = n; i > 0; i--)
**适用：** 简单的计数循环

## 模式 3：指针相减优化
**问题：** (pEnd - pBegin) / sizeof(T) 生成除法指令
**原因：** 编译器未识别为指针运算
**解决：** 确保 pEnd 和 pBegin 是正确类型的指针
**示例：** TopoFace* 相减自动得到元素数量

...（更多模式随着匹配过程积累）
```

---

## 6. 工具和自动化

### 6.1 新增工具开发

#### 工具 1：优先级分析器
**文件：** `tools/analyze_priority.py`

**功能：**
- 扫描 `asm/topo/*.json`
- 按大小、调用次数、是否导出等打分
- 生成实现优先级列表

**用法：**
```bash
python tools/analyze_priority.py --output priority_queue.txt
```

**输出示例：**
```
=== 函数实现优先级列表 ===
生成时间: 2026-05-01 14:30

批次 1: < 50 字节 (103 个函数)
────────────────────────────────────────
1. 0x10001234 (32 bytes) FUN_10001234
   - 调用者: 15 个函数
   - 导出: 否
   
2. 0x10005678 (45 bytes) FUN_10005678
   - 调用者: 8 个函数
   - 导出: 是

批次 2: 50-150 字节 (38 个函数)
────────────────────────────────────────
...
```

#### 工具 2：结构体提取器
**文件：** `tools/extract_structs.py`

**功能：**
- 从 Ghidra JSON 中分析内存访问模式
- 识别重复的偏移使用（如 +0x04, +0x08）
- 生成 struct 定义建议

**用法：**
```bash
python tools/extract_structs.py asm/topo/FUN_*.json
```

**输出示例：**
```c
// 从 32 个函数中识别到的访问模式:
// +0x00: 28 次访问 (void*)
// +0x04: 32 次访问 (int)
// +0x08: 25 次访问 (int)
// +0x0C: 18 次访问 (int)

建议结构体定义:
struct UnknownStruct {
    void* field_00;  // 高频访问
    int field_04;    // 高频访问
    int field_08;    // 高频访问
    int field_0C;    // 中频访问
};
```

#### 工具 3：代码质量检查器
**文件：** `tools/check_code_quality.py`

**功能：**
- 扫描 `src/topo/*.cpp`
- 检测指针偏移操作（违反规则）
- 检测 TODO/FIXME/STUB 标记
- 验证函数注释完整性

**用法：**
```bash
python tools/check_code_quality.py
```

**输出示例：**
```
=== 代码质量检查报告 ===

[ERROR] src/topo/topo_internal.cpp:123
  发现指针偏移操作: *(int*)((int)pThis + 0x0C)
  建议: 使用结构体成员访问

[WARN] src/topo/gbMatrix4.cpp:456
  TODO 标记未解决: // TODO: optimize this loop

[INFO] 检查通过: 所有函数有地址注释
[INFO] 检查通过: 无编译警告
```

#### 工具 4：进度仪表板生成器
**文件：** `tools/generate_dashboard.py`

**功能：**
- 读取进度数据
- 生成可视化 HTML 报告
- 包含图表、统计、预测

**用法：**
```bash
python tools/generate_dashboard.py
# 生成 reports/dashboard.html
```

**输出内容：**
- 总体进度条（115/414）
- 分类进度条（数学/TopoGeom/辅助）
- 字节匹配率统计
- 最近实现的函数列表
- 剩余工作时间估算

### 6.2 自动化脚本

#### 每日工作流
**文件：** `scripts/daily_workflow.bat`

```batch
@echo off
echo ========================================
echo   topo.dll 每日开发流程
echo ========================================

echo [1/5] 拉取最新代码...
git pull

echo [2/5] 编译验证...
call run_verify.bat
if %ERRORLEVEL% neq 0 (
    echo [错误] 编译失败，请检查代码
    exit /b 1
)

echo [3/5] 代码质量检查...
python tools/check_code_quality.py

echo [4/5] 生成进度报告...
python tools/progress_report.py > reports/progress_%DATE:~0,10%.txt
python tools/generate_dashboard.py

echo [5/5] 提交今日进度...
git add -A
git commit -m "Daily progress: %DATE%"
git push

echo ========================================
echo   完成！查看 reports/dashboard.html
echo ========================================
```

#### 批量实现助手（半自动）
**文件：** `scripts/implement_batch.py`

**警告：** 此工具生成的代码需要人工审查

**用法：**
```bash
# 辅助实现接下来 20 个小函数
python scripts/implement_batch.py --batch 1 --count 20
```

**功能：**
1. 读取优先级列表
2. 对每个函数：
   - 读取 JSON 文件
   - 提取 Ghidra C 代码
   - 简单转换为结构体访问
   - 插入到对应 .cpp 文件的正确位置
   - 添加注释（地址、大小）
3. 编译验证
4. 如果编译失败，标记该函数需要人工处理

**输出：**
```
处理函数: FUN_10001234 (32 bytes)
  ✓ 提取 JSON
  ✓ 转换代码
  ✓ 插入到 src/topo/gbVec3D.cpp
  ✓ 编译通过

处理函数: FUN_10005678 (45 bytes)
  ✓ 提取 JSON
  ✗ 转换失败: 无法识别结构体类型
  → 需要人工处理

总计: 18/20 成功, 2 需要人工处理
```

---

## 7. 风险管理

### 7.1 潜在风险和应对

#### 风险 1：MSVC 2022 无法完美匹配某些函数
**概率：** 中等  
**影响：** 少数函数可能存在字节差异

**应对策略：**
1. **识别无法匹配的函数（预计 < 5%）**
   - 记录差异原因（编译器版本、优化算法）
   - 评估对游戏运行的实际影响
   
2. **功能匹配作为备选标准**
   - 如果字节不同但功能完全正确
   - 通过游戏测试验证
   - 标记为"功能匹配"而非"字节匹配"

3. **最坏情况：手写汇编**
   - 对于关键的导出函数
   - 如果必须字节匹配且无法调优
   - 使用 inline assembly 或单独的 .asm 文件

#### 风险 2：结构体定义不完整或错误
**概率：** 高（初期）  
**影响：** 编译通过但运行时崩溃

**应对策略：**
1. **Ghidra 深度分析**
   - 使用 Ghidra 的数据类型分析
   - 查看 RTTI 信息（如果有）
   - 参考 PAL3patch 的结构体定义

2. **验证机制**
   ```cpp
   // 编译时验证大小
   static_assert(sizeof(TopoGeom) == 0x18, "Size mismatch");
   
   // 运行时验证偏移
   assert(offsetof(TopoGeom, pMeshData) == 0x14);
   ```

3. **增量测试**
   - 每定义一个结构体，立即用现有代码测试
   - 使用 sizeof() 和 offsetof() 验证
   - 运行游戏测试（如果可以加载）

#### 风险 3：vtable 定义复杂
**概率：** 中等  
**影响：** 虚函数调用错误，游戏崩溃

**应对策略：**
1. **使用 Ghidra 的 RTTI 恢复**
   - 查找 RTTI 结构（type_info）
   - 恢复类层次结构
   - 识别虚函数顺序

2. **参考 PAL3patch**
   - `/tmp/PAL3patch/src/PAL3patch/include/pal3.h`
   - 查找已有的 vtable 定义

3. **渐进式实现**
   ```cpp
   // 先定义简单的 vtable
   struct ITopoGeom_vtbl {
       void* destructor;
       void* method1;
       void* method2;
       // ... 先保留为 void*
   };
   
   // 后续逐个替换为正确的函数指针类型
   ```

#### 风险 4：CRT 链接导致符号冲突
**概率：** 低  
**影响：** 链接失败或运行时错误

**应对策略：**
1. **精确控制链接库**
   ```cmake
   target_link_options(topo PRIVATE
       /NODEFAULTLIB  # 不使用默认库
   )
   target_link_libraries(topo
       msvcrt.lib     # 明确指定需要的库
   )
   ```

2. **符号冲突检测**
   ```bash
   dumpbin /symbols build/verify/topo.dll > symbols.txt
   # 检查是否有重复符号
   ```

3. **必要时手工实现**
   - 如果某个 CRT 函数导致冲突
   - 可以手工实现一个简化版本
   - 使用不同的名称或命名空间

#### 风险 5：游戏加载 DLL 后崩溃
**概率：** 中等（初期）  
**影响：** 无法验证功能

**应对策略：**
1. **分阶段测试**
   - **阶段 1：** 只替换 DLL，不调用任何函数
     - 验证 DllMain 正确
     - 验证导出表正确
   
   - **阶段 2：** 使用调试器跟踪
     - x64dbg 或 WinDbg 附加到游戏进程
     - 设置断点在 DLL 入口和导出函数
     - 观察调用栈和参数
   
   - **阶段 3：** 逐个启用函数
     - 先让所有函数返回固定值
     - 逐个替换为真实实现
     - 定位引起崩溃的具体函数

2. **添加日志记录（调试用）**
   ```cpp
   // 可选的调试日志（发布版本移除）
   #ifdef DEBUG_TOPO
   void log_call(const char* func, void* arg) {
       FILE* f = fopen("topo_debug.log", "a");
       fprintf(f, "[%s] called with %p\n", func, arg);
       fclose(f);
   }
   #endif
   ```

3. **备份和回滚**
   - 始终保留原版 topo.dll 备份
   - 游戏目录使用版本控制（如 git）
   - 快速回滚到上一个工作版本

---

## 8. 时间估算和里程碑

### 8.1 时间估算

| 阶段 | 任务 | 预计时间 | 累计时间 |
|------|------|----------|----------|
| **阶段 0** | 结构体定义和重构 | 1 天 | 1 天 |
| ├─ | 完善结构体定义 | 4 小时 | |
| └─ | 重构现有代码 | 4 小时 | |
| **阶段 1** | 快速实现核心函数 | 3 天 | 4 天 |
| ├─ | 批次 1 (< 50 字节) | 1.5 天 | |
| ├─ | 批次 2 (50-150 字节) | 1 天 | |
| └─ | 批次 3 (> 150 字节) | 0.5 天 | |
| **阶段 2** | 链接 CRT 和异常处理 | 0.5 天 | 4.5 天 |
| ├─ | 识别 CRT 函数 | 2 小时 | |
| └─ | 配置链接选项 | 2 小时 | |
| **阶段 3** | 字节匹配调优 | 4 天 | 8.5 天 |
| ├─ | 开发匹配工具 | 0.5 天 | |
| ├─ | 匹配小函数 | 1 天 | |
| ├─ | 匹配中等函数 | 1.5 天 | |
| └─ | 匹配大函数 | 1 天 | |
| **阶段 4** | 测试和修复 | 1 天 | 9.5 天 |
| └─ | 游戏测试和问题修复 | 1 天 | |
| **总计** | | **9.5 天** | **~2 周** |

**注意：** 
- 时间估算基于全职开发（每天 8 小时）
- 实际时间可能因经验积累而减少
- 包含了学习和调试的缓冲时间

### 8.2 项目里程碑

#### M0: 代码质量基础（第 1 天结束）
**目标：** 建立高质量代码基础

**交付标准：**
- ✅ 所有核心结构体定义完整（TopoGeom, TopoFace, TopoMeshData 等）
- ✅ 现有代码（~115 个函数）全部重构
- ✅ 代码无指针偏移操作
- ✅ 编译通过，功能不退化
- ✅ sizeof() 和 offsetof() 验证通过

**验收测试：**
```bash
python tools/check_code_quality.py
# 输出: 无 [ERROR] 项
./run_verify.bat
# 输出: [PASS] 编译成功
```

---

#### M1: 批次 1 完成（第 2.5 天结束）
**目标：** 实现所有小函数（< 50 字节）

**交付标准：**
- ✅ 进度：115 → 215 (52%)
- ✅ 新增 ~100 个函数，全部 < 50 字节
- ✅ 编译通过，无链接错误
- ✅ 代码符合质量标准

**验收测试：**
```bash
python tools/progress_report.py
# 输出: Implemented: 215+ functions
git log --oneline -10
# 输出: 至少 5 次提交（每 20 个函数一次）
```

---

#### M2: 批次 2 完成（第 3.5 天结束）
**目标：** 实现所有中等函数（50-150 字节）

**交付标准：**
- ✅ 进度：215 → 255 (62%)
- ✅ 新增 ~40 个函数，50-150 字节
- ✅ 编译通过
- ✅ 开始积累匹配模式到 `docs/matching_patterns.md`

**验收测试：**
```bash
python tools/progress_report.py
# 输出: Implemented: 255+ functions
cat docs/matching_patterns.md
# 输出: 至少 5 个匹配模式记录
```

---

#### M3: 批次 3 完成（第 4 天结束）
**目标：** 实现所有大函数（> 150 字节）

**交付标准：**
- ✅ 进度：255 → 275 (66%)
- ✅ 新增 ~20 个函数，> 150 字节
- ✅ 所有核心函数实现完成
- ✅ 编译通过

**验收测试：**
```bash
python tools/progress_report.py
# 输出: Implemented: 275+ functions
# 输出: [TODO] Next Steps: 1. Link CRT functions
```

---

#### M4: 功能完整（第 4.5 天结束）
**目标：** 达到 100% 函数覆盖

**交付标准：**
- ✅ 进度：275 → 414 (100%)
- ✅ CRT 函数正确链接（~80 个）
- ✅ 异常处理函数编译器生成（~60 个）
- ✅ DLL 大小接近原始（104 KB ± 10%）
- ✅ 无未定义符号

**验收测试：**
```bash
python tools/progress_report.py
# 输出: Implemented: 414/414 functions (100%)

dir build\verify\topo.dll
# 输出: 96,768 - 110,000 字节

dumpbin /exports build/verify/topo.dll | findstr "ordinal"
# 输出: 导出函数数量与原版一致
```

---

#### M5: 字节匹配完成（第 8.5 天结束）
**目标：** 核心函数字节精确匹配

**交付标准：**
- ✅ 核心函数匹配率 ≥ 90%
- ✅ 所有导出函数字节匹配
- ✅ 匹配模式库完整（至少 20 个模式）
- ✅ 生成 HTML 匹配报告

**验收测试：**
```bash
python tools/batch_compare.py --all --report html
# 生成 reports/match_report.html
# 报告显示: 匹配率 ≥ 90%

cat docs/matching_patterns.md | grep "## 模式" | wc -l
# 输出: ≥ 20
```

---

#### M6: 游戏测试通过（第 9.5 天结束）
**目标：** DLL 在游戏中正常工作

**交付标准：**
- ✅ 游戏能正常启动到主菜单
- ✅ 能进入游戏场景
- ✅ 3D 渲染正常（无黑屏、花屏）
- ✅ 运行 30 分钟无崩溃
- ✅ 移动、旋转、缩放流畅

**验收测试：**
1. 备份原版 DLL
2. 替换为新 DLL
3. 启动游戏
4. 进入游戏场景
5. 游玩 30 分钟
6. 记录测试日志

**测试报告示例：**
```
=== topo.dll 游戏测试报告 ===
日期: 2026-05-XX
DLL 版本: 匹配反编译版本 v1.0
测试时长: 35 分钟

[✓] 游戏启动成功
[✓] 主菜单显示正常
[✓] 进入游戏场景成功
[✓] 3D 模型渲染正常
[✓] 摄像机旋转流畅
[✓] 角色移动正常
[✓] 缩放功能正常
[✓] 无崩溃、无异常
[✓] 内存使用稳定

结论: 测试通过，DLL 可以完全替代原版
```

---

## 9. 交付标准

### 9.1 必须满足（Blocker）

这些是项目成功的最低标准，缺一不可：

1. **功能完整性**
   - ✅ 所有核心函数（~160 个）实现完成
   - ✅ DLL 编译通过，无链接错误
   - ✅ 所有导出函数可调用

2. **字节匹配**
   - ✅ 至少 90% 的核心函数字节精确匹配
   - ✅ 所有导出函数字节匹配
   - ✅ 关键函数（CreateTopoGeom, DestroyTopoGeom 等）100% 匹配

3. **基本功能验证**
   - ✅ 替换游戏 DLL 后，游戏能启动到主菜单
   - ✅ 无明显的加载错误或崩溃

4. **代码质量**
   - ✅ 无指针偏移操作，全部使用结构体访问
   - ✅ 无未解决的 TODO/FIXME/STUB
   - ✅ 所有函数有完整注释（地址、大小、功能）

### 9.2 应该满足（Important）

这些标准显著提升项目质量，应尽力达成：

1. **高匹配率**
   - ✅ 95% 的核心函数字节精确匹配
   - ✅ 记录所有不匹配函数的原因

2. **深度功能验证**
   - ✅ 游戏能进入游戏场景并运行 10 分钟
   - ✅ 3D 渲染正常，无黑屏或花屏
   - ✅ 基本操作（移动、旋转、缩放）流畅

3. **完整文档**
   - ✅ 匹配模式库（至少 15 个模式）
   - ✅ 项目 README 更新
   - ✅ 结构体定义文档化

4. **工具完善**
   - ✅ 批量对比工具可用
   - ✅ 进度仪表板可用
   - ✅ 代码质量检查自动化

### 9.3 最好满足（Nice to have）

这些是理想目标，时间允许时追求：

1. **完美匹配**
   - ✅ 100% 字节精确匹配
   - ✅ 所有函数（包括辅助函数）匹配

2. **全面测试**
   - ✅ 游戏通关测试无问题
   - ✅ 所有功能（战斗、剧情、UI）验证通过
   - ✅ 性能测试（FPS、内存）无退化

3. **完整工具链**
   - ✅ 所有计划的工具开发完成
   - ✅ 工具有完整文档和示例
   - ✅ CI/CD 自动化测试

4. **开源贡献**
   - ✅ 清理代码，准备开源
   - ✅ 编写贡献指南
   - ✅ 提供详细的反编译教程

---

## 10. 文档交付物

### 10.1 核心文档

1. **本设计文档**
   - 文件：`docs/superpowers/specs/2026-05-01-topo-dll-complete-decompilation-design.md`
   - 状态：✅ 已完成

2. **实现计划**（后续生成）
   - 文件：`docs/superpowers/plans/<date>-topo-dll-implementation.md`
   - 工具：由 writing-plans 技能生成
   - 内容：详细的任务分解和执行步骤

3. **代码规范**
   - 文件：`docs/coding_standards.md`
   - 内容：
     - 禁止指针偏移操作
     - 结构体定义规范
     - 注释格式要求
     - 命名约定

4. **匹配模式库**
   - 文件：`docs/matching_patterns.md`
   - 内容：MSVC 2022 字节匹配技巧
   - 状态：阶段 3 时积累

5. **结构体定义文档**
   - 文件：`docs/structures.md`
   - 内容：
     - 所有结构体的详细说明
     - 字段用途、偏移、大小
     - 内存布局图

### 10.2 报告文档

1. **进度报告**（自动生成）
   - 文件：`reports/progress_<date>.txt`
   - 生成：每日运行 `python tools/progress_report.py`

2. **匹配报告**（自动生成）
   - 文件：`reports/match_report_<date>.html`
   - 生成：阶段 3 运行 `python tools/batch_compare.py --all --report html`

3. **测试报告**
   - 文件：`reports/game_test_<date>.md`
   - 内容：游戏测试结果、截图、日志
   - 状态：阶段 4 手工编写

4. **最终报告**
   - 文件：`docs/final_report.md`
   - 内容：
     - 项目总结
     - 最终匹配率统计
     - 遇到的问题和解决方案
     - 经验教训
     - 后续建议

---

## 11. 项目成功标准总结

### 11.1 技术指标

| 指标 | 最低标准 | 目标标准 |
|------|----------|----------|
| 函数实现完成率 | 100% | 100% |
| 核心函数字节匹配率 | ≥ 90% | ≥ 95% |
| 导出函数字节匹配率 | 100% | 100% |
| 代码质量检查通过率 | 100% | 100% |
| DLL 大小误差 | ± 10% | ± 5% |

### 11.2 功能验证

| 验证项 | 最低标准 | 目标标准 |
|--------|----------|----------|
| 游戏启动 | 能到主菜单 | 正常启动 |
| 游戏运行 | 无立即崩溃 | 运行 30 分钟 |
| 3D 渲染 | 无黑屏 | 完全正常 |
| 基本操作 | 可移动 | 流畅操作 |

### 11.3 文档完整性

- ✅ 设计文档
- ✅ 实现计划
- ✅ 代码规范
- ✅ 匹配模式库（≥ 15 个模式）
- ✅ 测试报告
- ✅ 最终报告

---

## 12. 风险评估矩阵

| 风险 | 概率 | 影响 | 优先级 | 应对 |
|------|------|------|--------|------|
| MSVC 2022 无法完美匹配 | 中 | 中 | 中 | 识别差异，功能验证，必要时手写汇编 |
| 结构体定义错误 | 高 | 高 | 高 | Ghidra 深度分析，增量测试，验证机制 |
| vtable 定义复杂 | 中 | 中 | 中 | RTTI 分析，参考 PAL3patch，渐进实现 |
| CRT 链接冲突 | 低 | 中 | 低 | 精确控制链接，符号检测，手工实现 |
| 游戏崩溃 | 中 | 高 | 高 | 分阶段测试，调试器跟踪，日志记录 |

---

## 13. 下一步行动

### 13.1 立即行动（阶段 0）

1. **审查本设计文档**
   - 用户审查本文档
   - 确认所有部分符合预期
   - 批准后进入实施阶段

2. **生成实施计划**
   - 调用 writing-plans 技能
   - 生成详细的任务清单
   - 分配优先级和时间

3. **开始结构体定义**
   - 完善 `include/pal3_structs.h`
   - 定义 TopoGeom, TopoFace, TopoMeshData
   - 添加 sizeof 验证

### 13.2 短期目标（第 1 周）

- 完成阶段 0（结构体定义和重构）
- 完成阶段 1 批次 1（小函数实现）
- 完成阶段 1 批次 2（中等函数实现）
- 达到 M1 和 M2 里程碑

### 13.3 中期目标（第 2 周）

- 完成阶段 1 批次 3（大函数实现）
- 完成阶段 2（链接 CRT）
- 开始阶段 3（字节匹配）
- 达到 M3, M4, M5 里程碑

### 13.4 最终目标（第 2 周末）

- 完成阶段 3（字节匹配）
- 完成阶段 4（测试验证）
- 达到 M6 里程碑
- 生成最终报告
- 项目交付

---

**项目总结：**
- **目标：** 生成字节精确匹配的 topo.dll，完全替代游戏原版
- **策略：** 三阶段实施（快速实现 → 链接库 → 字节匹配）
- **方法：** 按函数大小递进，智能分类，强制代码质量
- **工期：** 9.5 天（约 2 周）
- **成功标准：** 核心函数 ≥ 90% 匹配，游戏正常运行 30 分钟

**预计在 2 周内完成完整的 topo.dll 反编译，实现字节级精确匹配。**
