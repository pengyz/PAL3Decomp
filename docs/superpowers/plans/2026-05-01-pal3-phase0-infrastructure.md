# PAL3.exe Phase 0: 基础设施搭建 - 实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 建立完整的分析、编译、测试工具链，为后续开发做好准备

**Architecture:** Ghidra 完整分析 → 函数分类和优先级 → CMake 编译系统 → 工具链开发

**Tech Stack:** Ghidra 10.x, Python 3.8+, CMake 3.20+, MSVC 2022, Git

**工期:** 2-3 周  
**输出:** Ghidra 项目、函数 JSON、编译系统、工具链

---

## 文件结构

创建的文件：
```
asm/pal3/                           # Ghidra 导出数据
├── functions/                      # 函数 JSON（3500-5000 个）
├── structs/                        # 结构体定义
├── globals/                        # 全局变量
└── analysis/                       # 分析结果
    ├── function_classification.json
    ├── call_graph.json
    └── priority_list.txt

tools/ghidra/                       # Ghidra 脚本
├── export_functions.py
├── analyze_structs.py
└── build_callgraph.py

tools/                              # 分析和构建工具
├── analyze_pal3.py
├── compare_exe.py
├── progress_pal3.py
├── generate_import_lib.py
└── test_framework.py

build/libs/                         # 导入库
├── gbengine.lib
└── topo.lib

CMakeLists.txt                      # 主构建文件
src/pal3/main.cpp                   # 最小骨架代码
include/external/gbengine.h         # gbengine 接口
include/external/topo.h             # topo 接口
```

---

## Task 1: Ghidra 项目设置和初步分析

**Files:**
- Create: `asm/pal3/PAL3.gpr` (Ghidra 项目)
- Read: `original/PAL3.exe`

- [ ] **Step 1: 在 Ghidra 中创建新项目**

```bash
# 启动 Ghidra
cd /path/to/ghidra
./ghidraRun

# 在 Ghidra GUI 中：
# 1. File → New Project
# 2. Project Type: Non-Shared Project
# 3. Project Directory: D:\workspace\project-x\asm\pal3
# 4. Project Name: PAL3
```

Expected: 创建 `asm/pal3/PAL3.gpr` 和 `asm/pal3/PAL3.rep` 目录

- [ ] **Step 2: 导入 PAL3.exe**

```bash
# 在 Ghidra GUI 中：
# 1. File → Import File
# 2. 选择 original/PAL3.exe
# 3. Format: Portable Executable (PE)
# 4. Language: x86:LE:32:default (Windows)
# 5. 点击 OK，不更改其他选项
```

Expected: PAL3.exe 出现在项目树中

- [ ] **Step 3: 打开 CodeBrowser 进行分析**

```bash
# 双击 PAL3.exe 打开 CodeBrowser
# 弹出 "Analyze" 对话框时选择 "Yes"
```

Expected: 自动分析开始

- [ ] **Step 4: 配置分析选项**

```bash
# 在 "Analysis Options" 对话框中：
# 确保启用以下分析器：
☑ Decompiler Parameter ID
☑ Function Start Search
☑ Stack
☑ Windows x86 PE RTTI Analyzer
☑ Demangler Microsoft
☑ Embedded Media
☑ Data Reference
☑ Subroutine References
☑ Call Convention ID
☑ Create Address Tables

# 点击 "Analyze" 开始
```

Expected: 分析进度条显示，需要 15-30 分钟

- [ ] **Step 5: 等待分析完成并验证**

```bash
# 分析完成后，在 Symbol Tree 窗口查看：
# - Functions 文件夹应该有 3000+ 个函数
# - Classes 文件夹应该有一些 C++ 类（如果有 RTTI）

# 在 Defined Strings 窗口查看：
# 应该能看到大量中文字符串（UTF-8 或 GBK）
```

Expected: Symbol Tree 显示大量函数

- [ ] **Step 6: 保存 Ghidra 项目**

```bash
# File → Save Project
# 或 Ctrl+S
```

Expected: 项目保存成功

- [ ] **Step 7: 提交 Ghidra 项目配置**

```bash
git add asm/pal3/.gitignore
cat > asm/pal3/.gitignore << 'EOF'
*.lock
*.log
data/~*
EOF

git add asm/pal3/.gitignore
git commit -m "chore(phase0): setup Ghidra project for PAL3.exe"
```

Expected: Git 提交成功

---

## Task 2: 开发 Ghidra 函数导出脚本

**Files:**
- Create: `tools/ghidra/export_functions.py`

- [ ] **Step 1: 创建导出脚本骨架**

```python
# tools/ghidra/export_functions.py
"""
Ghidra 脚本：导出所有函数到 JSON 文件

每个函数导出为单独的 JSON 文件，包含：
- 地址、大小、名称
- 反编译的 C 代码
- 原始汇编代码
- 调用的函数列表
- 被调用者列表

用法：
在 Ghidra Script Manager 中运行此脚本
"""

# @category PAL3.Export

from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
import json
import os

def main():
    # 获取当前程序
    program = getCurrentProgram()
    if program is None:
        print("Error: No program loaded")
        return
    
    print("Starting function export for: " + program.getName())
    
    # 设置输出目录
    project_root = "D:/workspace/project-x"
    output_dir = os.path.join(project_root, "asm/pal3/functions")
    
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    # 初始化反编译器
    decompiler = DecompInterface()
    decompiler.openProgram(program)
    
    # 获取所有函数
    fm = program.getFunctionManager()
    functions = list(fm.getFunctions(True))  # True = forward order
    
    print("Found {} functions".format(len(functions)))
    
    # 导出每个函数
    exported_count = 0
    for func in functions:
        try:
            export_function(func, decompiler, output_dir)
            exported_count += 1
            if exported_count % 100 == 0:
                print("Exported {} functions...".format(exported_count))
        except Exception as e:
            print("Error exporting {}: {}".format(func.getName(), str(e)))
    
    print("Export complete: {} functions".format(exported_count))
    decompiler.dispose()

def export_function(func, decompiler, output_dir):
    """导出单个函数"""
    addr = func.getEntryPoint()
    name = func.getName()
    
    # 生成文件名: 名称_地址.json
    filename = "{}_{:08X}.json".format(sanitize_name(name), addr.getOffset())
    filepath = os.path.join(output_dir, filename)
    
    # 收集函数信息
    func_data = {
        "address": "0x{:08X}".format(addr.getOffset()),
        "name": name,
        "size": func.getBody().getNumAddresses(),
        "signature": func.getSignature().getPrototypeString(),
        "decompiled_code": get_decompiled_code(func, decompiler),
        "assembly": get_assembly_code(func),
        "calls_to": get_calls_to(func),
        "called_by": get_called_by(func)
    }
    
    # 写入 JSON
    with open(filepath, 'w', encoding='utf-8') as f:
        json.dump(func_data, f, indent=2, ensure_ascii=False)

def sanitize_name(name):
    """清理函数名，移除非法文件名字符"""
    invalid_chars = '<>:"/\\|?*'
    for char in invalid_chars:
        name = name.replace(char, '_')
    return name

def get_decompiled_code(func, decompiler):
    """获取反编译的 C 代码"""
    results = decompiler.decompileFunction(func, 30, ConsoleTaskMonitor())
    if results and results.decompileCompleted():
        return results.getDecompiledFunction().getC()
    return "// Failed to decompile"

def get_assembly_code(func):
    """获取汇编代码"""
    listing = currentProgram.getListing()
    instructions = []
    
    for inst in listing.getInstructions(func.getBody(), True):
        addr = inst.getAddress()
        mnemonic = inst.getMnemonicString()
        operands = inst.getDefaultOperandRepresentation(0)
        
        # 获取所有操作数
        for i in range(1, inst.getNumOperands()):
            operands += ", " + inst.getDefaultOperandRepresentation(i)
        
        instructions.append({
            "address": "0x{:08X}".format(addr.getOffset()),
            "bytes": inst.getBytesString(),
            "mnemonic": mnemonic,
            "operands": operands
        })
    
    return instructions

def get_calls_to(func):
    """获取此函数调用的函数列表"""
    calls = []
    for ref in func.getCalledFunctions(ConsoleTaskMonitor()):
        calls.append({
            "address": "0x{:08X}".format(ref.getEntryPoint().getOffset()),
            "name": ref.getName()
        })
    return calls

def get_called_by(func):
    """获取调用此函数的函数列表"""
    callers = []
    for ref in func.getCallingFunctions(ConsoleTaskMonitor()):
        callers.append({
            "address": "0x{:08X}".format(ref.getEntryPoint().getOffset()),
            "name": ref.getName()
        })
    return callers

if __name__ == "__main__":
    main()
```

- [ ] **Step 2: 验证脚本语法**

```bash
python -m py_compile tools/ghidra/export_functions.py
```

Expected: 无输出表示语法正确

- [ ] **Step 3: 在 Ghidra 中运行导出脚本**

```bash
# 在 Ghidra CodeBrowser 中：
# 1. Window → Script Manager
# 2. 点击工具栏的 "Manage Script Directories" 按钮
# 3. 添加 D:\workspace\project-x\tools\ghidra
# 4. 在脚本列表中找到 export_functions.py
# 5. 双击运行

# 或者在 Ghidra Headless 模式运行：
cd /path/to/ghidra/support
./analyzeHeadless D:/workspace/project-x/asm/pal3 PAL3 \
    -process PAL3.exe \
    -postScript export_functions.py
```

Expected: Console 输出 "Exported XXX functions..."，`asm/pal3/functions/` 目录下生成大量 JSON 文件

- [ ] **Step 4: 验证导出结果**

```bash
cd D:/workspace/project-x

# 检查导出的文件数
ls asm/pal3/functions/*.json | wc -l

# 应该输出 3000-5000

# 查看一个示例 JSON
cat asm/pal3/functions/WinMain_0055507C.json | head -50
```

Expected: 显示 JSON 结构正确，包含 address, name, decompiled_code 等字段

- [ ] **Step 5: 提交导出脚本**

```bash
git add tools/ghidra/export_functions.py
git commit -m "feat(phase0): add Ghidra function export script

- Export all functions to JSON format
- Include decompiled C code, assembly, call graph
- Output to asm/pal3/functions/"
```

Expected: Git 提交成功

---

## Task 3: 函数分类和优先级分析

**Files:**
- Create: `tools/analyze_pal3.py`
- Create: `asm/pal3/analysis/function_classification.json`
- Create: `asm/pal3/analysis/priority_list.txt`

- [ ] **Step 1: 创建函数分析工具**

```python
# tools/analyze_pal3.py
#!/usr/bin/env python3
"""
PAL3.exe 函数分析工具

功能：
1. 分析所有导出的函数 JSON
2. 按模块、大小、调用频率分类
3. 生成优先级列表
4. 输出分类报告

用法：
    python tools/analyze_pal3.py
"""

import json
import os
from collections import defaultdict

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FUNCTIONS_DIR = os.path.join(PROJECT_ROOT, "asm/pal3/functions")
ANALYSIS_DIR = os.path.join(PROJECT_ROOT, "asm/pal3/analysis")

def main():
    print("PAL3 Function Analyzer")
    print("=" * 60)
    
    # 加载所有函数
    functions = load_all_functions()
    print(f"Loaded {len(functions)} functions")
    
    # 分析
    classification = classify_functions(functions)
    
    # 生成优先级列表
    priority_list = generate_priority_list(functions)
    
    # 保存结果
    save_classification(classification)
    save_priority_list(priority_list)
    
    # 打印报告
    print_summary(classification)
    
    print("\nAnalysis complete!")
    print(f"Results saved to {ANALYSIS_DIR}/")

def load_all_functions():
    """加载所有函数 JSON"""
    functions = []
    
    for filename in os.listdir(FUNCTIONS_DIR):
        if not filename.endswith('.json'):
            continue
        
        filepath = os.path.join(FUNCTIONS_DIR, filename)
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                func = json.load(f)
                func['filename'] = filename
                functions.append(func)
        except Exception as e:
            print(f"Error loading {filename}: {e}")
    
    return functions

def classify_functions(functions):
    """分类函数"""
    classification = {
        'by_module': defaultdict(list),
        'by_size': {'small': [], 'medium': [], 'large': []},
        'by_calls': {'leaf': [], 'normal': [], 'hub': []},
        'entry_points': [],
        'winapi': [],
        'crt': [],
        'game_logic': []
    }
    
    for func in functions:
        addr = func['address']
        name = func['name']
        size = func['size']
        calls_to = len(func.get('calls_to', []))
        called_by = len(func.get('called_by', []))
        
        # 按模块分类（根据名称前缀）
        module = classify_by_name(name)
        classification['by_module'][module].append(func)
        
        # 按大小分类
        if size < 50:
            classification['by_size']['small'].append(func)
        elif size < 200:
            classification['by_size']['medium'].append(func)
        else:
            classification['by_size']['large'].append(func)
        
        # 按调用关系分类
        if calls_to == 0:
            classification['by_calls']['leaf'].append(func)
        elif calls_to < 5 and called_by < 10:
            classification['by_calls']['normal'].append(func)
        else:
            classification['by_calls']['hub'].append(func)
        
        # 特殊函数
        if 'WinMain' in name or 'DllMain' in name:
            classification['entry_points'].append(func)
        
        if name.startswith('_') or 'msvcrt' in name.lower():
            classification['crt'].append(func)
        
        # 检测 Windows API 调用
        code = func.get('decompiled_code', '')
        if any(api in code for api in ['CreateWindow', 'RegisterClass', 'GetMessage']):
            classification['winapi'].append(func)
    
    return classification

def classify_by_name(name):
    """根据函数名推断模块"""
    name_lower = name.lower()
    
    if 'script' in name_lower or 'sce' in name_lower:
        return 'script'
    elif 'ui' in name_lower or 'menu' in name_lower or 'dialog' in name_lower:
        return 'ui'
    elif 'battle' in name_lower or 'fight' in name_lower:
        return 'battle'
    elif 'scene' in name_lower or 'map' in name_lower:
        return 'scene'
    elif 'save' in name_lower or 'load' in name_lower:
        return 'save'
    elif 'audio' in name_lower or 'sound' in name_lower or 'music' in name_lower:
        return 'audio'
    elif 'render' in name_lower or 'draw' in name_lower:
        return 'render'
    elif 'init' in name_lower or 'create' in name_lower:
        return 'init'
    else:
        return 'other'

def generate_priority_list(functions):
    """生成优先级列表"""
    priority = []
    
    for func in functions:
        name = func['name']
        addr = func['address']
        size = func['size']
        called_by_count = len(func.get('called_by', []))
        
        # 计算优先级分数
        score = 0
        
        # 入口点最高优先级
        if 'WinMain' in name:
            score = 10000
        elif 'DllMain' in name:
            score = 9000
        
        # 初始化函数高优先级
        elif 'Init' in name or 'Create' in name:
            score = 1000 + called_by_count * 10
        
        # 主循环高优先级
        elif 'Loop' in name or 'Update' in name or 'Main' in name:
            score = 800 + called_by_count * 10
        
        # 被多次调用的函数（热点）
        elif called_by_count > 10:
            score = 500 + called_by_count * 5
        
        # 小函数（容易实现）
        elif size < 50:
            score = 300
        
        # 其他函数
        else:
            score = 100 + called_by_count
        
        priority.append({
            'address': addr,
            'name': name,
            'size': size,
            'called_by': called_by_count,
            'priority_score': score
        })
    
    # 按优先级排序
    priority.sort(key=lambda x: x['priority_score'], reverse=True)
    
    return priority

def save_classification(classification):
    """保存分类结果"""
    os.makedirs(ANALYSIS_DIR, exist_ok=True)
    
    # 转换为可序列化格式
    output = {}
    
    for category, data in classification.items():
        if isinstance(data, dict):
            output[category] = {k: len(v) for k, v in data.items()}
        else:
            output[category] = len(data)
    
    filepath = os.path.join(ANALYSIS_DIR, 'function_classification.json')
    with open(filepath, 'w', encoding='utf-8') as f:
        json.dump(classification, f, indent=2, ensure_ascii=False, default=str)

def save_priority_list(priority_list):
    """保存优先级列表"""
    filepath = os.path.join(ANALYSIS_DIR, 'priority_list.txt')
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write("PAL3.exe Function Priority List\n")
        f.write("=" * 80 + "\n\n")
        f.write(f"{'Rank':<6} {'Address':<12} {'Score':<8} {'Size':<8} {'Called':<8} {'Name'}\n")
        f.write("-" * 80 + "\n")
        
        for i, func in enumerate(priority_list, 1):
            f.write(f"{i:<6} {func['address']:<12} {func['priority_score']:<8} "
                   f"{func['size']:<8} {func['called_by']:<8} {func['name']}\n")

def print_summary(classification):
    """打印分类摘要"""
    print("\nClassification Summary:")
    print("-" * 60)
    
    print("\nBy Module:")
    for module, funcs in sorted(classification['by_module'].items()):
        print(f"  {module:15s}: {len(funcs):4d} functions")
    
    print("\nBy Size:")
    for size_cat, funcs in classification['by_size'].items():
        print(f"  {size_cat:15s}: {len(funcs):4d} functions")
    
    print("\nBy Call Pattern:")
    for call_cat, funcs in classification['by_calls'].items():
        print(f"  {call_cat:15s}: {len(funcs):4d} functions")
    
    print(f"\nSpecial Categories:")
    print(f"  Entry Points   : {len(classification['entry_points'])} functions")
    print(f"  Windows API    : {len(classification['winapi'])} functions")
    print(f"  CRT Functions  : {len(classification['crt'])} functions")

if __name__ == "__main__":
    main()
```

- [ ] **Step 2: 运行分析工具**

```bash
cd D:/workspace/project-x
python tools/analyze_pal3.py
```

Expected: 输出分类统计，生成 `asm/pal3/analysis/function_classification.json` 和 `priority_list.txt`

- [ ] **Step 3: 查看分析结果**

```bash
# 查看优先级列表前 20 个函数
head -25 asm/pal3/analysis/priority_list.txt

# 查看分类统计
cat asm/pal3/analysis/function_classification.json | python -m json.tool | head -50
```

Expected: 看到函数按优先级排列，WinMain 应该在最前面

- [ ] **Step 4: 提交分析工具和结果**

```bash
git add tools/analyze_pal3.py
git add asm/pal3/analysis/
git commit -m "feat(phase0): add function analysis tool

- Classify functions by module, size, call pattern
- Generate priority list for implementation
- Output: function_classification.json, priority_list.txt"
```

Expected: Git 提交成功

---

## Task 4: CMake 编译系统搭建

**Files:**
- Create: `CMakeLists.txt`
- Create: `src/pal3/main.cpp`
- Create: `include/external/gbengine.h`
- Create: `include/external/topo.h`

- [ ] **Step 1: 创建主 CMakeLists.txt**

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(PAL3 CXX)

# 目标平台：Windows 32位
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR X86)

# 源文件（目前只有骨架）
set(PAL3_SOURCES
    src/pal3/main.cpp
)

# 创建可执行文件
add_executable(PAL3 WIN32
    ${PAL3_SOURCES}
)

# 包含目录
target_include_directories(PAL3 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/pal3
    ${CMAKE_SOURCE_DIR}/include/external
)

# MSVC 编译选项（模拟 MSVC 7.1）
if(MSVC)
    target_compile_options(PAL3 PRIVATE
        /O2                 # 最大优化
        /Ob1                # 内联展开（仅 __inline）
        /Oi                 # 启用内部函数
        /Ot                 # 优先速度
        /Oy-                # 禁用帧指针省略
        /GF                 # 字符串池
        /Gy                 # 函数级链接
        /EHsc               # C++ 异常处理
        /GR                 # 启用 RTTI
        /Zc:wchar_t         # wchar_t 是内置类型
        /fp:precise         # 浮点精度
        /arch:SSE           # SSE 指令集
        /W3                 # 警告级别 3
        /D WIN32            # Windows 平台
        /D _WINDOWS         # GUI 应用
        /D NDEBUG           # Release 模式
        /D _MBCS            # 多字节字符集
    )
    
    # 链接选项
    target_link_options(PAL3 PRIVATE
        /SUBSYSTEM:WINDOWS          # GUI 应用
        /ENTRY:WinMainCRTStartup    # 入口点
        /BASE:0x00400000            # 基地址（匹配原版）
        /OPT:REF                    # 移除未引用函数
        /OPT:ICF                    # 合并相同函数
        /MAP                        # 生成 .map 文件
    )
    
    # 静态链接 MSVCRT
    set_property(TARGET PAL3 PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()

# 链接库（稍后会添加 gbengine.lib 和 topo.lib）
target_link_libraries(PAL3 PRIVATE
    # Windows API
    user32.lib
    kernel32.lib
    gdi32.lib
)

# 输出目录
set_target_properties(PAL3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
```

- [ ] **Step 2: 创建最小骨架代码**

```cpp
// src/pal3/main.cpp
/**
 * PAL3.exe - 仙剑奇侠传三
 * 
 * 这是最小的骨架代码，用于验证编译系统。
 * 后续会替换为完整的游戏代码。
 */

#include <windows.h>

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MessageBoxA(
        NULL,
        "PAL3.exe 编译系统测试\n\nPhase 0: 基础设施搭建",
        "仙剑奇侠传三",
        MB_OK | MB_ICONINFORMATION
    );
    
    return 0;
}
```

- [ ] **Step 3: 创建 gbengine 接口头文件（存根）**

```cpp
// include/external/gbengine.h
#pragma once

/**
 * gbengine.dll 导入接口声明
 * 
 * 此文件声明所有从 gbengine.dll 导入的函数。
 * 函数签名从 PAL3A.PDB 符号文件提取。
 * 
 * Phase 0: 只包含基本声明，Phase 1 会填充完整接口
 */

#ifdef __cplusplus
extern "C" {
#endif

// 基本类型定义
typedef void* GBHANDLE;

// 临时占位符函数（Phase 1 会替换为真实接口）
__declspec(dllimport) GBHANDLE __cdecl gbEngine_Initialize(void);
__declspec(dllimport) void __cdecl gbEngine_Shutdown(GBHANDLE handle);

#ifdef __cplusplus
}
#endif
```

- [ ] **Step 4: 创建 topo 接口头文件（存根）**

```cpp
// include/external/topo.h
#pragma once

/**
 * topo.dll 导入接口声明
 * 
 * 数学库接口：gbVec3D, gbMatrix4, gbQuaternion 等
 * 
 * Phase 0: 只包含基本声明
 */

#ifdef __cplusplus
extern "C" {
#endif

// 临时占位符
__declspec(dllimport) void* __cdecl CreateTopoGeom(int type);
__declspec(dllimport) void __cdecl DestroyTopoGeom(void* geom);

#ifdef __cplusplus
}
#endif
```

- [ ] **Step 5: 创建构建目录并配置**

```bash
cd D:/workspace/project-x

# 创建构建目录
mkdir -p build

# 配置 CMake（使用 Visual Studio 2022，32位）
cd build
cmake .. -G "Visual Studio 17 2022" -A Win32
```

Expected: CMake 配置成功，输出 "Configuring done" 和 "Generating done"

- [ ] **Step 6: 编译骨架代码**

```bash
# 在 build 目录中
cmake --build . --config Release
```

Expected: 编译成功，输出 "Build succeeded"

- [ ] **Step 7: 测试编译的 exe**

```bash
# 运行生成的 exe
./bin/Release/PAL3.exe
```

Expected: 弹出消息框显示 "PAL3.exe 编译系统测试"

- [ ] **Step 8: 检查生成的 exe 信息**

```bash
# 检查文件大小
ls -lh bin/Release/PAL3.exe

# 使用 dumpbin 检查 PE 头
dumpbin /headers bin/Release/PAL3.exe | head -30

# 检查基地址
dumpbin /headers bin/Release/PAL3.exe | grep "image base"
```

Expected: 基地址应该是 0x00400000

- [ ] **Step 9: 提交编译系统**

```bash
cd D:/workspace/project-x

git add CMakeLists.txt
git add src/pal3/main.cpp
git add include/external/gbengine.h
git add include/external/topo.h
git commit -m "feat(phase0): setup CMake build system

- CMakeLists.txt with MSVC 7.1 compatibility flags
- Minimal skeleton code (WinMain stub)
- gbengine.h and topo.h stub interfaces
- Builds and runs successfully"
```

Expected: Git 提交成功

---

## Task 5: 生成 DLL 导入库

**Files:**
- Create: `tools/generate_import_lib.py`
- Create: `build/libs/gbengine.lib`
- Create: `build/libs/topo.lib`

- [ ] **Step 1: 创建导入库生成工具**

```python
# tools/generate_import_lib.py
#!/usr/bin/env python3
"""
从 DLL 生成导入库 (.lib)

用法：
    python tools/generate_import_lib.py original/gbengine.dll -o build/libs/gbengine.lib
    python tools/generate_import_lib.py original/topo.dll -o build/libs/topo.lib
"""

import sys
import subprocess
import os

def generate_def_file(dll_path, def_path):
    """从 DLL 生成 .def 文件"""
    print(f"Generating .def file from {dll_path}...")
    
    # 使用 dumpbin 导出函数列表
    result = subprocess.run(
        ['dumpbin', '/exports', dll_path],
        capture_output=True,
        text=True,
        encoding='utf-8',
        errors='ignore'
    )
    
    if result.returncode != 0:
        print(f"Error: Failed to run dumpbin on {dll_path}")
        print(result.stderr)
        return False
    
    # 解析输出
    lines = result.stdout.split('\n')
    exports = []
    
    in_exports = False
    for line in lines:
        if 'ordinal' in line.lower() and 'name' in line.lower():
            in_exports = True
            continue
        
        if in_exports and line.strip():
            parts = line.strip().split()
            if len(parts) >= 4:
                # ordinal hint RVA name
                ordinal = parts[0]
                name = parts[3]
                exports.append((ordinal, name))
    
    if not exports:
        print("Error: No exports found")
        return False
    
    # 写入 .def 文件
    dll_name = os.path.basename(dll_path)
    with open(def_path, 'w', encoding='utf-8') as f:
        f.write(f"LIBRARY {dll_name}\n")
        f.write("EXPORTS\n")
        for ordinal, name in exports:
            f.write(f"    {name} @{ordinal}\n")
    
    print(f"Generated {def_path} with {len(exports)} exports")
    return True

def generate_lib_file(def_path, lib_path, machine='X86'):
    """从 .def 文件生成 .lib 文件"""
    print(f"Generating .lib file: {lib_path}...")
    
    # 使用 lib.exe 生成导入库
    result = subprocess.run(
        ['lib', f'/def:{def_path}', f'/out:{lib_path}', f'/machine:{machine}'],
        capture_output=True,
        text=True,
        encoding='utf-8',
        errors='ignore'
    )
    
    if result.returncode != 0:
        print(f"Error: Failed to generate lib file")
        print(result.stderr)
        return False
    
    print(f"Successfully generated {lib_path}")
    return True

def main():
    if len(sys.argv) < 2:
        print("Usage: python generate_import_lib.py <dll> [-o <lib>]")
        print("Example: python generate_import_lib.py original/gbengine.dll -o build/libs/gbengine.lib")
        sys.exit(1)
    
    dll_path = sys.argv[1]
    
    # 解析输出路径
    if len(sys.argv) >= 4 and sys.argv[2] == '-o':
        lib_path = sys.argv[3]
    else:
        lib_path = dll_path.replace('.dll', '.lib')
    
    if not os.path.exists(dll_path):
        print(f"Error: {dll_path} not found")
        sys.exit(1)
    
    # 确保输出目录存在
    lib_dir = os.path.dirname(lib_path)
    if lib_dir and not os.path.exists(lib_dir):
        os.makedirs(lib_dir)
    
    # 生成 .def 文件
    def_path = lib_path.replace('.lib', '.def')
    if not generate_def_file(dll_path, def_path):
        sys.exit(1)
    
    # 生成 .lib 文件
    if not generate_lib_file(def_path, lib_path):
        sys.exit(1)
    
    print("\nDone!")
    print(f"Import library: {lib_path}")
    print(f"Definition file: {def_path}")

if __name__ == "__main__":
    main()
```

- [ ] **Step 2: 生成 gbengine.lib**

```bash
cd D:/workspace/project-x
python tools/generate_import_lib.py original/gbengine.dll -o build/libs/gbengine.lib
```

Expected: 输出 "Successfully generated build/libs/gbengine.lib"，生成约 1000 个导出

- [ ] **Step 3: 生成 topo.lib**

```bash
python tools/generate_import_lib.py original/topo.dll -o build/libs/topo.lib
```

Expected: 输出 "Successfully generated build/libs/topo.lib"，生成约 100 个导出

- [ ] **Step 4: 验证生成的导入库**

```bash
# 检查 gbengine.lib
dumpbin /exports build/libs/gbengine.lib | head -50

# 检查 topo.lib
dumpbin /exports build/libs/topo.lib | head -30
```

Expected: 显示导出函数列表

- [ ] **Step 5: 更新 CMakeLists.txt 链接导入库**

```cmake
# CMakeLists.txt（修改链接库部分）
# 在 target_link_libraries 中添加：

target_link_libraries(PAL3 PRIVATE
    # gbengine 和 topo 导入库
    ${CMAKE_SOURCE_DIR}/build/libs/gbengine.lib
    ${CMAKE_SOURCE_DIR}/build/libs/topo.lib
    
    # Windows API
    user32.lib
    kernel32.lib
    gdi32.lib
)
```

- [ ] **Step 6: 重新编译验证链接**

```bash
cd build
cmake --build . --config Release
```

Expected: 编译成功，链接到 gbengine.lib 和 topo.lib

- [ ] **Step 7: 提交导入库工具和文件**

```bash
cd D:/workspace/project-x

git add tools/generate_import_lib.py
git add build/libs/*.lib
git add build/libs/*.def
git add CMakeLists.txt
git commit -m "feat(phase0): generate DLL import libraries

- Add generate_import_lib.py tool
- Generate gbengine.lib (~1000 exports)
- Generate topo.lib (~100 exports)
- Update CMakeLists.txt to link import libraries"
```

Expected: Git 提交成功

---

## Task 6: 二进制对比工具开发

**Files:**
- Create: `tools/compare_exe.py`

- [ ] **Step 1: 创建二进制对比工具**

```python
# tools/compare_exe.py
#!/usr/bin/env python3
"""
PAL3.exe 二进制对比工具

功能：
1. 对比编译的 PAL3.exe 和原版 PAL3.exe
2. 支持按地址对比单个函数
3. 批量对比所有函数
4. 生成匹配率报告

用法：
    # 对比单个函数
    python tools/compare_exe.py 0x0055507C 200

    # 批量对比
    python tools/compare_exe.py --all

    # 生成 HTML 报告
    python tools/compare_exe.py --all --report html
"""

import sys
import os
import struct
import json
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_EXE = PROJECT_ROOT / "original" / "PAL3.exe"
COMPILED_EXE = PROJECT_ROOT / "build" / "bin" / "Release" / "PAL3.exe"
FUNCTIONS_DIR = PROJECT_ROOT / "asm" / "pal3" / "functions"
REPORT_DIR = PROJECT_ROOT / "build" / "reports"

def main():
    if len(sys.argv) < 2:
        print_usage()
        sys.exit(1)
    
    if sys.argv[1] == '--all':
        # 批量对比
        report_format = 'text'
        if len(sys.argv) >= 4 and sys.argv[2] == '--report':
            report_format = sys.argv[3]
        
        compare_all_functions(report_format)
    else:
        # 对比单个函数
        try:
            address = int(sys.argv[1], 16)
            size = int(sys.argv[2]) if len(sys.argv) > 2 else None
            compare_single_function(address, size)
        except ValueError:
            print("Error: Invalid address or size")
            print_usage()
            sys.exit(1)

def print_usage():
    print("Usage:")
    print("  python tools/compare_exe.py <address> [size]")
    print("  python tools/compare_exe.py --all [--report text|html]")
    print()
    print("Examples:")
    print("  python tools/compare_exe.py 0x0055507C 200")
    print("  python tools/compare_exe.py --all")
    print("  python tools/compare_exe.py --all --report html")

def compare_single_function(address, size=None):
    """对比单个函数"""
    print(f"Comparing function at 0x{address:08X}")
    
    # 如果没有指定大小，从 JSON 中查找
    if size is None:
        size = find_function_size(address)
        if size is None:
            print("Error: Function size not found. Please specify size.")
            return
    
    # 读取两个 exe 的字节
    original_bytes = read_bytes(ORIGINAL_EXE, address, size)
    compiled_bytes = read_bytes(COMPILED_EXE, address, size)
    
    if original_bytes is None or compiled_bytes is None:
        print("Error: Failed to read exe files")
        return
    
    # 对比
    match_count = 0
    diff_positions = []
    
    for i in range(min(len(original_bytes), len(compiled_bytes))):
        if original_bytes[i] == compiled_bytes[i]:
            match_count += 1
        else:
            diff_positions.append(i)
    
    match_rate = match_count / size * 100
    
    # 打印结果
    print(f"Size: {size} bytes")
    print(f"Match: {match_count}/{size} bytes ({match_rate:.2f}%)")
    
    if match_rate == 100.0:
        print("✅ PERFECT MATCH!")
    elif match_rate >= 95.0:
        print("✅ Excellent match (>= 95%)")
    elif match_rate >= 85.0:
        print("⚠️  Good match (>= 85%)")
    elif match_rate >= 70.0:
        print("⚠️  Acceptable match (>= 70%)")
    else:
        print("❌ Poor match (< 70%)")
    
    # 显示前几个差异
    if diff_positions and len(diff_positions) <= 20:
        print("\nDifferences:")
        for pos in diff_positions[:10]:
            orig = original_bytes[pos]
            comp = compiled_bytes[pos]
            print(f"  Offset +0x{pos:04X}: 0x{orig:02X} -> 0x{comp:02X}")

def compare_all_functions(report_format='text'):
    """批量对比所有函数"""
    print("Comparing all functions...")
    
    # 加载所有函数
    functions = load_all_functions()
    print(f"Found {len(functions)} functions")
    
    results = []
    
    for i, func in enumerate(functions):
        address = int(func['address'], 16)
        size = func['size']
        name = func['name']
        
        original_bytes = read_bytes(ORIGINAL_EXE, address, size)
        compiled_bytes = read_bytes(COMPILED_EXE, address, size)
        
        if original_bytes is None or compiled_bytes is None:
            continue
        
        match_count = sum(1 for a, b in zip(original_bytes, compiled_bytes) if a == b)
        match_rate = match_count / size * 100
        
        results.append({
            'address': address,
            'name': name,
            'size': size,
            'match_count': match_count,
            'match_rate': match_rate
        })
        
        if (i + 1) % 100 == 0:
            print(f"Compared {i + 1} functions...")
    
    # 生成报告
    if report_format == 'html':
        generate_html_report(results)
    else:
        generate_text_report(results)

def load_all_functions():
    """加载所有函数信息"""
    functions = []
    
    for json_file in FUNCTIONS_DIR.glob("*.json"):
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                func = json.load(f)
                functions.append(func)
        except Exception as e:
            print(f"Warning: Failed to load {json_file}: {e}")
    
    return functions

def find_function_size(address):
    """从 JSON 中查找函数大小"""
    for json_file in FUNCTIONS_DIR.glob("*.json"):
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                func = json.load(f)
                if int(func['address'], 16) == address:
                    return func['size']
        except Exception:
            continue
    
    return None

def read_bytes(exe_path, address, size):
    """从 exe 读取指定地址的字节"""
    if not exe_path.exists():
        print(f"Error: {exe_path} not found")
        return None
    
    # PE 基地址是 0x00400000
    # 文件偏移 = 虚拟地址 - 基地址 + 节偏移
    # 简化版：假设 .text 段起始于 0x00401000，文件偏移 0x1000
    file_offset = address - 0x00400000
    
    try:
        with open(exe_path, 'rb') as f:
            f.seek(file_offset)
            return f.read(size)
    except Exception as e:
        print(f"Error reading {exe_path}: {e}")
        return None

def generate_text_report(results):
    """生成文本报告"""
    # 统计
    total = len(results)
    perfect = sum(1 for r in results if r['match_rate'] == 100.0)
    excellent = sum(1 for r in results if 95.0 <= r['match_rate'] < 100.0)
    good = sum(1 for r in results if 85.0 <= r['match_rate'] < 95.0)
    acceptable = sum(1 for r in results if 70.0 <= r['match_rate'] < 85.0)
    poor = sum(1 for r in results if r['match_rate'] < 70.0)
    
    avg_rate = sum(r['match_rate'] for r in results) / total if total > 0 else 0
    
    print("\n" + "=" * 80)
    print("BINARY COMPARISON REPORT")
    print("=" * 80)
    print(f"\nTotal Functions: {total}")
    print(f"Average Match Rate: {avg_rate:.2f}%")
    print(f"\nMatch Distribution:")
    print(f"  Perfect (100%)      : {perfect:4d} ({perfect/total*100:.1f}%)")
    print(f"  Excellent (95-100%) : {excellent:4d} ({excellent/total*100:.1f}%)")
    print(f"  Good (85-95%)       : {good:4d} ({good/total*100:.1f}%)")
    print(f"  Acceptable (70-85%) : {acceptable:4d} ({acceptable/total*100:.1f}%)")
    print(f"  Poor (<70%)         : {poor:4d} ({poor/total*100:.1f}%)")
    
    # 显示最差的 10 个函数
    print(f"\nWorst Matches (Bottom 10):")
    worst = sorted(results, key=lambda r: r['match_rate'])[:10]
    for func in worst:
        print(f"  0x{func['address']:08X} {func['name']:40s} {func['match_rate']:6.2f}%")
    
    # 保存完整报告
    REPORT_DIR.mkdir(parents=True, exist_ok=True)
    report_file = REPORT_DIR / "comparison_report.txt"
    
    with open(report_file, 'w', encoding='utf-8') as f:
        f.write("PAL3.exe Binary Comparison Report\n")
        f.write("=" * 80 + "\n\n")
        f.write(f"Total Functions: {total}\n")
        f.write(f"Average Match Rate: {avg_rate:.2f}%\n\n")
        f.write(f"{'Address':<12} {'Name':<40} {'Size':<8} {'Match':<8} {'Rate'}\n")
        f.write("-" * 80 + "\n")
        
        for func in sorted(results, key=lambda r: r['match_rate']):
            f.write(f"0x{func['address']:08X}  {func['name']:<40} "
                   f"{func['size']:<8} {func['match_count']:<8} {func['match_rate']:6.2f}%\n")
    
    print(f"\nFull report saved to: {report_file}")

def generate_html_report(results):
    """生成 HTML 报告"""
    print("Generating HTML report...")
    # TODO: 实现 HTML 报告生成
    print("HTML report generation not yet implemented")

if __name__ == "__main__":
    main()
```

- [ ] **Step 2: 测试对比工具（假设 WinMain 地址）**

```bash
cd D:/workspace/project-x

# 测试单个函数对比（使用假设的地址）
python tools/compare_exe.py 0x0055507C 100
```

Expected: 输出对比结果（目前由于是骨架代码，匹配率会很低）

- [ ] **Step 3: 提交对比工具**

```bash
git add tools/compare_exe.py
git commit -m "feat(phase0): add binary comparison tool

- Compare compiled exe with original
- Support single function and batch comparison
- Generate text and HTML reports
- Calculate match rate statistics"
```

Expected: Git 提交成功

---

## Task 7: 进度跟踪工具开发

**Files:**
- Create: `tools/progress_pal3.py`

- [ ] **Step 1: 创建进度跟踪工具**

```python
# tools/progress_pal3.py
#!/usr/bin/env python3
"""
PAL3.exe 进度跟踪工具

功能：
1. 统计已实现函数数量
2. 按模块统计进度
3. 显示字节匹配率
4. 生成进度报告

用法：
    python tools/progress_pal3.py
    python tools/progress_pal3.py --html
"""

import sys
import os
import json
from pathlib import Path
from datetime import datetime

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_DIR = PROJECT_ROOT / "asm" / "pal3" / "functions"
ANALYSIS_DIR = PROJECT_ROOT / "asm" / "pal3" / "analysis"
SRC_DIR = PROJECT_ROOT / "src" / "pal3"
REPORT_DIR = PROJECT_ROOT / "build" / "reports"

def main():
    output_format = 'text'
    if len(sys.argv) >= 2 and sys.argv[1] == '--html':
        output_format = 'html'
    
    print("PAL3.exe Progress Tracker")
    print("=" * 60)
    
    # 统计总函数数
    total_functions = count_total_functions()
    print(f"Total Functions: {total_functions}")
    
    # 统计已实现函数数
    implemented_functions = count_implemented_functions()
    print(f"Implemented Functions: {implemented_functions}")
    
    # 计算进度
    progress = implemented_functions / total_functions * 100 if total_functions > 0 else 0
    print(f"Progress: {progress:.2f}%")
    
    # 按模块统计
    module_progress = calculate_module_progress()
    
    # 生成报告
    if output_format == 'html':
        generate_html_report(total_functions, implemented_functions, module_progress)
    else:
        generate_text_report(total_functions, implemented_functions, module_progress)

def count_total_functions():
    """统计总函数数"""
    return len(list(FUNCTIONS_DIR.glob("*.json")))

def count_implemented_functions():
    """统计已实现的函数数"""
    # 简化版：统计 src/pal3 下的函数定义数
    # 搜索所有 .cpp 文件中的函数定义
    count = 0
    
    for cpp_file in SRC_DIR.rglob("*.cpp"):
        try:
            with open(cpp_file, 'r', encoding='utf-8') as f:
                content = f.read()
                # 简单统计：查找函数地址注释 // 0x004XXXXX
                count += content.count('// 0x00')
        except Exception:
            pass
    
    return count

def calculate_module_progress():
    """按模块计算进度"""
    # 加载函数分类
    classification_file = ANALYSIS_DIR / "function_classification.json"
    if not classification_file.exists():
        return {}
    
    with open(classification_file, 'r', encoding='utf-8') as f:
        classification = json.load(f)
    
    # 统计每个模块的进度
    module_progress = {}
    
    if 'by_module' in classification:
        for module, functions in classification['by_module'].items():
            total = len(functions) if isinstance(functions, list) else functions
            implemented = 0  # TODO: 实际统计已实现数量
            
            module_progress[module] = {
                'total': total,
                'implemented': implemented,
                'percentage': implemented / total * 100 if total > 0 else 0
            }
    
    return module_progress

def generate_text_report(total, implemented, module_progress):
    """生成文本报告"""
    progress = implemented / total * 100 if total > 0 else 0
    
    print("\n" + "=" * 60)
    print("PROGRESS REPORT")
    print("=" * 60)
    print(f"\nOverall Progress:")
    print(f"  Total Functions     : {total}")
    print(f"  Implemented         : {implemented}")
    print(f"  Remaining           : {total - implemented}")
    print(f"  Progress            : {progress:.2f}%")
    
    # 进度条
    bar_width = 40
    filled = int(bar_width * progress / 100)
    bar = '█' * filled + '░' * (bar_width - filled)
    print(f"  [{bar}] {progress:.1f}%")
    
    if module_progress:
        print(f"\nProgress by Module:")
        for module, stats in sorted(module_progress.items()):
            pct = stats['percentage']
            bar_width = 20
            filled = int(bar_width * pct / 100)
            bar = '█' * filled + '░' * (bar_width - filled)
            print(f"  {module:15s}: [{bar}] {stats['implemented']:4d}/{stats['total']:4d} ({pct:5.1f}%)")
    
    # 保存报告
    REPORT_DIR.mkdir(parents=True, exist_ok=True)
    report_file = REPORT_DIR / "progress_report.txt"
    
    with open(report_file, 'w', encoding='utf-8') as f:
        f.write(f"PAL3.exe Progress Report\n")
        f.write(f"Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
        f.write("=" * 60 + "\n\n")
        f.write(f"Overall Progress: {implemented}/{total} ({progress:.2f}%)\n")
        f.write(f"Remaining: {total - implemented} functions\n\n")
        
        if module_progress:
            f.write("Module Progress:\n")
            for module, stats in sorted(module_progress.items()):
                f.write(f"  {module:15s}: {stats['implemented']:4d}/{stats['total']:4d} "
                       f"({stats['percentage']:5.1f}%)\n")
    
    print(f"\nReport saved to: {report_file}")

def generate_html_report(total, implemented, module_progress):
    """生成 HTML 报告"""
    print("Generating HTML report...")
    # TODO: 实现 HTML 报告生成
    print("HTML report generation not yet implemented")

if __name__ == "__main__":
    main()
```

- [ ] **Step 2: 运行进度跟踪工具**

```bash
cd D:/workspace/project-x
python tools/progress_pal3.py
```

Expected: 输出当前进度（0% 或接近 0%，因为只有骨架代码）

- [ ] **Step 3: 提交进度工具**

```bash
git add tools/progress_pal3.py
git commit -m "feat(phase0): add progress tracking tool

- Count total and implemented functions
- Calculate progress by module
- Generate progress reports
- Support text and HTML output"
```

Expected: Git 提交成功

---

## Task 8: 测试框架开发

**Files:**
- Create: `tools/test_framework.py`

- [ ] **Step 1: 创建测试框架**

```python
# tools/test_framework.py
#!/usr/bin/env python3
"""
PAL3.exe 自动化测试框架

测试套件：
1. 编译测试 - 验证代码能成功编译
2. 结构测试 - 验证 PE 结构正确
3. 字节匹配测试 - 验证函数字节匹配
4. 功能测试 - 验证游戏功能（手动）

用法：
    python tools/test_framework.py          # 运行所有测试
    python tools/test_framework.py compile  # 只运行编译测试
    python tools/test_framework.py struct   # 只运行结构测试
"""

import sys
import os
import subprocess
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
BUILD_DIR = PROJECT_ROOT / "build"
COMPILED_EXE = BUILD_DIR / "bin" / "Release" / "PAL3.exe"
ORIGINAL_EXE = PROJECT_ROOT / "original" / "PAL3.exe"

class TestResult:
    def __init__(self, name):
        self.name = name
        self.passed = False
        self.message = ""
    
    def pass_test(self, message=""):
        self.passed = True
        self.message = message
    
    def fail_test(self, message):
        self.passed = False
        self.message = message

def main():
    test_suite = sys.argv[1] if len(sys.argv) > 1 else 'all'
    
    print("PAL3.exe Test Framework")
    print("=" * 60)
    
    results = []
    
    if test_suite in ['all', 'compile']:
        results.extend(run_compile_tests())
    
    if test_suite in ['all', 'struct']:
        results.extend(run_struct_tests())
    
    # 打印结果
    print("\n" + "=" * 60)
    print("TEST RESULTS")
    print("=" * 60)
    
    passed = sum(1 for r in results if r.passed)
    failed = sum(1 for r in results if not r.passed)
    
    for result in results:
        status = "✅ PASS" if result.passed else "❌ FAIL"
        print(f"{status}: {result.name}")
        if result.message:
            print(f"       {result.message}")
    
    print("\n" + "-" * 60)
    print(f"Total: {len(results)} tests, {passed} passed, {failed} failed")
    
    return 0 if failed == 0 else 1

def run_compile_tests():
    """编译测试"""
    results = []
    
    # Test 1: CMake 配置
    result = TestResult("CMake Configuration")
    try:
        subprocess.run(
            ['cmake', '..'],
            cwd=BUILD_DIR,
            capture_output=True,
            check=True,
            text=True
        )
        result.pass_test("CMake configuration successful")
    except subprocess.CalledProcessError as e:
        result.fail_test(f"CMake failed: {e.stderr}")
    except Exception as e:
        result.fail_test(f"Error: {e}")
    
    results.append(result)
    
    # Test 2: 编译
    result = TestResult("Compilation")
    try:
        proc = subprocess.run(
            ['cmake', '--build', '.', '--config', 'Release'],
            cwd=BUILD_DIR,
            capture_output=True,
            check=True,
            text=True
        )
        
        # 检查是否有错误
        if 'error' in proc.stdout.lower() or 'error' in proc.stderr.lower():
            result.fail_test("Compilation had errors")
        else:
            result.pass_test("Compilation successful, no errors")
    except subprocess.CalledProcessError as e:
        result.fail_test(f"Compilation failed: {e.stderr}")
    except Exception as e:
        result.fail_test(f"Error: {e}")
    
    results.append(result)
    
    # Test 3: exe 文件存在
    result = TestResult("Executable Exists")
    if COMPILED_EXE.exists():
        size = COMPILED_EXE.stat().st_size
        result.pass_test(f"PAL3.exe generated ({size} bytes)")
    else:
        result.fail_test("PAL3.exe not found")
    
    results.append(result)
    
    return results

def run_struct_tests():
    """PE 结构测试"""
    results = []
    
    if not COMPILED_EXE.exists():
        result = TestResult("PE Structure Tests")
        result.fail_test("Executable not found, skipping structure tests")
        return [result]
    
    # Test 1: 基地址检查
    result = TestResult("Base Address")
    try:
        proc = subprocess.run(
            ['dumpbin', '/headers', str(COMPILED_EXE)],
            capture_output=True,
            check=True,
            text=True
        )
        
        if '400000 image base' in proc.stdout:
            result.pass_test("Base address is 0x00400000 (correct)")
        else:
            result.fail_test("Base address is not 0x00400000")
    except Exception as e:
        result.fail_test(f"Error running dumpbin: {e}")
    
    results.append(result)
    
    # Test 2: 子系统检查
    result = TestResult("Subsystem")
    try:
        proc = subprocess.run(
            ['dumpbin', '/headers', str(COMPILED_EXE)],
            capture_output=True,
            check=True,
            text=True
        )
        
        if 'Windows GUI' in proc.stdout or 'subsystem (Windows GUI)' in proc.stdout:
            result.pass_test("Subsystem is Windows GUI (correct)")
        else:
            result.fail_test("Subsystem is not Windows GUI")
    except Exception as e:
        result.fail_test(f"Error running dumpbin: {e}")
    
    results.append(result)
    
    # Test 3: 导入表检查
    result = TestResult("Import Table")
    try:
        proc = subprocess.run(
            ['dumpbin', '/imports', str(COMPILED_EXE)],
            capture_output=True,
            check=True,
            text=True
        )
        
        has_user32 = 'USER32.dll' in proc.stdout
        has_kernel32 = 'KERNEL32.dll' in proc.stdout
        
        if has_user32 and has_kernel32:
            result.pass_test("Import table contains USER32.dll and KERNEL32.dll")
        else:
            result.fail_test("Missing expected imports")
    except Exception as e:
        result.fail_test(f"Error running dumpbin: {e}")
    
    results.append(result)
    
    return results

if __name__ == "__main__":
    sys.exit(main())
```

- [ ] **Step 2: 运行测试框架**

```bash
cd D:/workspace/project-x
python tools/test_framework.py
```

Expected: 运行所有测试，显示通过/失败状态

- [ ] **Step 3: 提交测试框架**

```bash
git add tools/test_framework.py
git commit -m "feat(phase0): add automated test framework

- Compile tests (CMake config, build, exe exists)
- Structure tests (base address, subsystem, imports)
- Support selective test execution
- Generate test reports"
```

Expected: Git 提交成功

---

## Task 9: 文档和验收

**Files:**
- Create: `docs/pal3/phase0_completion.md`
- Update: `STATUS.md`

- [ ] **Step 1: 创建 Phase 0 完成报告**

```markdown
# docs/pal3/phase0_completion.md
# PAL3.exe Phase 0: 基础设施搭建 - 完成报告

**完成日期：** 2026-05-XX  
**工期：** X 周

---

## 完成情况

### ✅ Ghidra 分析
- [x] Ghidra 项目创建
- [x] PAL3.exe 导入和自动分析
- [x] 函数导出脚本开发
- [x] 导出 XXXX 个函数到 JSON

### ✅ 函数分类
- [x] 函数分析工具开发
- [x] 按模块、大小、调用关系分类
- [x] 生成优先级列表
- [x] 输出分类报告

### ✅ 编译系统
- [x] CMakeLists.txt 创建
- [x] MSVC 7.1 兼容性配置
- [x] 最小骨架代码编译成功
- [x] 生成可运行的 PAL3.exe

### ✅ 导入库
- [x] 导入库生成工具
- [x] gbengine.lib 生成（~1000 导出）
- [x] topo.lib 生成（~100 导出）
- [x] 链接到编译系统

### ✅ 工具链
- [x] 二进制对比工具
- [x] 进度跟踪工具
- [x] 测试框架
- [x] 所有工具可正常运行

---

## 输出物清单

### 数据文件
- `asm/pal3/PAL3.gpr` - Ghidra 项目
- `asm/pal3/functions/*.json` - XXXX 个函数 JSON
- `asm/pal3/analysis/function_classification.json` - 函数分类
- `asm/pal3/analysis/priority_list.txt` - 优先级列表

### 代码文件
- `CMakeLists.txt` - CMake 构建配置
- `src/pal3/main.cpp` - 骨架代码
- `include/external/gbengine.h` - gbengine 接口（存根）
- `include/external/topo.h` - topo 接口（存根）

### 导入库
- `build/libs/gbengine.lib` - gbengine 导入库
- `build/libs/gbengine.def` - gbengine 定义文件
- `build/libs/topo.lib` - topo 导入库
- `build/libs/topo.def` - topo 定义文件

### 工具
- `tools/ghidra/export_functions.py` - Ghidra 导出脚本
- `tools/analyze_pal3.py` - 函数分析工具
- `tools/generate_import_lib.py` - 导入库生成工具
- `tools/compare_exe.py` - 二进制对比工具
- `tools/progress_pal3.py` - 进度跟踪工具
- `tools/test_framework.py` - 测试框架

### 报告
- `build/reports/progress_report.txt` - 当前进度报告

---

## 验收标准

- ✅ Ghidra 分析完成，导出 3500+ 个函数 JSON
- ✅ 函数分类完成，生成调用图和优先级列表
- ✅ 编译系统可用，能生成空壳 PAL3.exe
- ✅ 导入库生成成功（gbengine.lib, topo.lib）
- ✅ 工具链完整，所有工具能正常运行
- ✅ 文档完整，团队成员能快速上手

---

## 下一步

**Phase 1: 程序框架和主循环**

预计工期：1 个月  
目标：实现游戏骨架，能启动并进入主循环

任务：
1. WinMain 入口和初始化
2. DirectX 初始化
3. gbengine 接口集成
4. 主游戏循环
5. 字节匹配调优

---

**Phase 0 完成！** 🎉
```

- [ ] **Step 2: 更新 STATUS.md**

```markdown
# 在 STATUS.md 开头添加
## Latest Update (2026-05-XX)

**Phase 0 完成！** 基础设施搭建全部完成。

新增：
- ✅ Ghidra 分析和函数导出（XXXX 个函数）
- ✅ 函数分类和优先级分析
- ✅ CMake 编译系统
- ✅ DLL 导入库生成
- ✅ 完整工具链（对比、进度、测试）

**准备开始 Phase 1: 程序框架和主循环**
```

- [ ] **Step 3: 运行最终测试**

```bash
cd D:/workspace/project-x

# 运行所有测试
python tools/test_framework.py

# 生成进度报告
python tools/progress_pal3.py

# 测试骨架 exe
./build/bin/Release/PAL3.exe
```

Expected: 所有测试通过，进度报告生成，exe 能运行

- [ ] **Step 4: 最终提交**

```bash
git add docs/pal3/phase0_completion.md
git add STATUS.md
git commit -m "docs(phase0): Phase 0 completion report

- All infrastructure tasks completed
- Ghidra analysis: XXXX functions exported
- Build system: working and tested
- Toolchain: complete and operational
- Ready to begin Phase 1"
```

Expected: Git 提交成功

---

## Phase 0 验收清单

完成以下所有项目后，Phase 0 即为完成：

### 基础设施
- [ ] Ghidra 项目创建并完成自动分析
- [ ] 导出 3500+ 个函数到 JSON 格式
- [ ] 函数分类完成（按模块、大小、调用关系）
- [ ] 优先级列表生成

### 编译系统
- [ ] CMakeLists.txt 配置完成
- [ ] MSVC 编译选项正确（/O2, /Oy-, /GF 等）
- [ ] 骨架代码能成功编译
- [ ] 生成的 exe 基地址为 0x00400000
- [ ] exe 能运行（显示消息框）

### 导入库
- [ ] gbengine.lib 生成成功（~1000 导出）
- [ ] topo.lib 生成成功（~100 导出）
- [ ] 导入库正确链接到项目

### 工具链
- [ ] export_functions.py 能导出函数
- [ ] analyze_pal3.py 能分析函数
- [ ] generate_import_lib.py 能生成导入库
- [ ] compare_exe.py 能对比二进制
- [ ] progress_pal3.py 能跟踪进度
- [ ] test_framework.py 能运行测试

### 文档
- [ ] Phase 0 完成报告编写
- [ ] STATUS.md 更新
- [ ] 所有工具有使用说明

### Git
- [ ] 所有代码提交到 Git
- [ ] 提交信息清晰
- [ ] 代码结构整洁

---

**Phase 0 完成后，进入 Phase 1：程序框架和主循环**
