# PAL3 迭代管线

**持续执行，直到达成里程碑目标或被用户中断。** 不等待确认，不主动停止，每轮迭代结束后立即开始下一轮。

## 核心原则（不可违背）

1. **质量优先于通过率** — 宁可一个高质量文件，不要十个 hack 通过的文件
2. **IDA 是唯一的质量来源** — 代码中的类型/偏移/命名问题，只通过 IDA 标注解决，不在后处理中编造信息
3. **ROI 驱动选择** — 每轮迭代选收益最大的改进点，不做边角优化
4. **不降级** — 禁止任何让代码信息量减少的操作（void* 替代具体类型、char[] 替代结构体、注释掉继承等）
5. **可重复** — `gen_cpp.py --force-all` 任何时候跑都应该得到同样或更好的结果

## 进度控制

### 量化指标（每轮迭代必须记录）

```
=== Iteration #N (YYYY-MM-DD) ===
[IDA]   Named functions: XXXX / 5413
[IDA]   Structs with full layout: XXX / 869
[GEN]   Generated cpp: XXX files, XXXX functions
[VC6]   Compile pass: XX / XXX
[Quality]
  sub_ refs in code: XXXX
  unnamed globals (dword_/byte_): XXXX
  hardcoded offsets *(this+N): XXXX
  void* params (named funcs): XX / XXXX
  stdiobuf/ios_base refs: XXX
[Focus] 本轮聚焦: (e.g. "CCBRoleState 结构体成员完善")
[Result] 改善: (e.g. "CCBRoleState 相关 12 个函数从偏移访问变为成员名")
```

### 里程碑

| 阶段 | 目标 | 衡量标准 |
|------|------|----------|
| M1 | 核心类结构完整 | CCBSystem/Stage/RoleState/UI 的成员访问全部用字段名 |
| M2 | 函数签名完善 | void* 参数 < 20，sub_ 引用 < 500 |
| M3 | 核心逻辑可编译 | Combat/ + Script/ + Scene/ 全部 VC6 通过 |
| M4 | 全量可编译 | 113 文件全部 VC6 通过 |
| M5 | 字节匹配验证 | 核心函数 binary compare 通过 |

## 终止条件

### 单轮迭代终止

- 本轮标注完成（脚本已跑、IDB 已保存）
- 导出完成（decomp JSON 已更新）
- 重新生成完成（cpp/headers 已刷新）
- 编译结果已记录
- 质量指标已对比上轮
- **如果某项指标没有改善或回退**：停下来分析原因，不继续盲目迭代

### 管线整体终止

达到 M3（核心逻辑可编译）后转入字节匹配阶段，工作流从"IDA 标注循环"变为"单函数字节匹配循环"。

## 反馈循环

### 从编译错误到 IDA 动作的映射

```
编译错误 → 根因分析 → IDA 修复动作
    ↓
C2027 "未定义类型 XXX"
  → 找到 XXX 的 PDB 定义 (dia_export_structs.py)
  → 写 IDA 脚本导入结构体 (udt_type_data_t)
  → 验证: Hex-Rays 输出中 *(this+N) 变为 this->field

C2440 "void* 转 TypedPtr*"
  → 找到该函数的 IDA 签名
  → 用 DIA 或调用上下文确定正确参数类型
  → idc.SetType(addr, corrected_sig)
  → 验证: Hex-Rays 输出参数类型正确

C2065 "未声明标识符 dword_XXX"
  → 在 IDA 中找到该地址
  → 分析 xref 确定变量的类型和含义
  → ida_name.set_name + apply_tinfo
  → 验证: 导出代码中用正确变量名

C2065 "未声明标识符 sub_XXX"
  → 在 IDA 中分析该函数
  → 从 callers 的 this-source 或 vtable 确定类归属
  → set_name 标注
  → 验证: 导出代码中用 Class::Method 名
```

### 从质量指标到优先级的映射

```
"hardcoded offsets 多" (*(this+N) 模式)
  → 优先完善对应类的结构体成员定义
  → 选影响面最大的类（被最多函数引用的）

"sub_ refs 多"
  → 优先标注高频 sub_（从调用统计中选 top N）
  → 通过 vtable 分析批量标注同一类的方法

"void* params 多"
  → 优先修正高频函数的签名
  → 从调用者传入的实参类型反推参数类型

"某个类的代码质量特别差"
  → 集中处理该类: 结构体导入 → 签名修正 → 重新生成 → 验证
```

### 自检清单（每轮迭代结束前）

- [ ] 本轮标注是否基于数据分析（不是猜测）？
- [ ] 有没有做任何降级操作？
- [ ] 新增的修复是否在管线脚本中（可重复）？
- [ ] 指标是否改善？如果没有，原因是什么？
- [ ] 下一轮的改进方向是否明确？

## 单轮迭代详细流程

### Step 1: 质量评估（全局 + 局部）

每轮迭代**必须**先跑全局评估，记录基线。

```bash
# 全局编译评估（CMake 整编，几十秒完成）
cmake --build build/pal3 -- -k 0 2>&1 | tee build/pal3/build_log.txt
# 从日志统计: 通过文件数、错误总数、错误码分布

# 全局代码质量指标
python -c "
import os, re
src = 'src/pal3'
metrics = {'sub_': 0, 'unnamed_globals': 0, 'offset_access': 0, 'void_ptr': 0, 'stdiobuf': 0}
for root, _, files in os.walk(src):
    for f in files:
        if not f.endswith('.cpp'): continue
        c = open(os.path.join(root, f)).read()
        metrics['sub_'] += len(re.findall(r'\bsub_[0-9A-Fa-f]+', c))
        metrics['unnamed_globals'] += len(re.findall(r'\b(dword|byte|word|off|stru)_[0-9A-Fa-f]+', c))
        metrics['offset_access'] += len(re.findall(r'\*\(\(_DWORD \*\)\w+ \+', c))
        metrics['void_ptr'] += len(re.findall(r'void \*\w+', c))
        metrics['stdiobuf'] += c.count('stdiobuf') + c.count('ios_base')
for k, v in sorted(metrics.items()):
    print(f'  {k}: {v}')
"
```

**全局质量原则**：
- **轮次结束时**全局指标不劣于轮次开始时（允许中间过程波动）
- 允许计划内的暂时劣化（如：导入新结构体暴露更多类型错误，重新生成后消失）
- 暂时劣化前必须明确预期（"这步会导致 +N 错误"）和恢复路径（"完成 X 后恢复"）
- 如果轮次结束时仍然劣化且无法恢复：回退变更，重新分析方案

**局部评估**：对本轮聚焦的类/模块，深入看代码质量（成员访问是否用字段名、调用是否用方法名）。

### Step 2: 确定本轮焦点

基于指标选择**一个**改进方向（不贪多）：
- 如果某个类被大量硬编码偏移引用 → 完善该类结构体
- 如果某些高频 sub_ 可以通过 vtable 分析批量标注 → 做 vtable 扫描
- 如果某个函数的签名导致大量 void* 传播 → 修正该签名

### Step 3: IDA 标注

```bash
# 写脚本 tools/ida/pal3_iter_NNN.py
# 内容根据 Step 2 确定的焦点

# 执行
idat.exe -A -S"tools/ida/pal3_iter_NNN.py" original/PAL3.exe.i64

# 检查结果
cat tools/ida/_logs/pal3_iter_NNN_log.txt
```

### Step 4: 导出 + 生成

```bash
# 导出
idat.exe -A -S"tools/ida/pal3_export_only.py" original/PAL3.exe.i64

# 生成
python tools/gen_headers.py
python tools/gen_cpp.py --force-all
```

### Step 5: 验证

```bash
# VC6 编译
# 重点验证本轮焦点涉及的文件

# 质量对比
# 对比 Step 1 的指标，确认改善
```

### Step 6: 记录 + 规划下轮

记录本轮结果到迭代日志，确定下一轮方向。

## 工具命令速查

```bash
# === 构建 (CMake + VC6 + Ninja) ===
cmake -B build/pal3 -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake -DBUILD_TARGET=pal3 -G Ninja
cmake --build build/pal3              # 编译到第一个错误就停
cmake --build build/pal3 -- -k 0     # 编译所有文件（不停止）

# === IDA ===
idat.exe -A -S"tools/ida/SCRIPT.py" original/PAL3.exe.i64

# === DIA SDK ===
python tools/dia_export_structs.py   # 导出所有结构体+成员（含类型递归解析）
python tools/dia_export_bases.py     # 导出继承关系

# === 代码生成 ===
python tools/gen_headers.py          # 头文件（总是全量）
python tools/gen_cpp.py --force-all  # cpp 全量
python tools/gen_cpp.py ClassName    # cpp 单类（不覆盖其他手动修改）

# === 质量统计 ===
# 编译通过率从 cmake 输出直接获取
# 代码指标用 python 脚本扫描 src/pal3/
```
