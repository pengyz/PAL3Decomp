# PAL3.exe Phase 8: 字节匹配调优和全面测试 - 实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 达到 95%+ 核心函数字节匹配，完成 4 级全面测试，准备发布

**Architecture:** 批量对比 → 分类调优 → 回归测试 → 功能测试 → 验收

**工期:** 1-2 个月  
**进度贡献:** 85% → 100%  
**重要性:** ⭐⭐⭐⭐⭐ (质量保证)

---

## 前置条件

- ✅ Phase 0-7 已完成
- ✅ 所有 3500-5000 个函数已实现
- ✅ 游戏基本可玩
- ✅ 无重大崩溃 bug

---

## Phase 8 总体目标

### 字节匹配目标
- **核心函数（前 500 个）:** 95%+ 匹配率
- **重要函数（501-2000）:** 90%+ 匹配率
- **其他函数（2001+）:** 85%+ 匹配率
- **整体平均:** 85%+ 匹配率

### 质量目标
- **Level 1 测试:** 100% 通过（编译验证）
- **Level 2 测试:** 100% 通过（结构验证）
- **Level 3 测试:** 85%+ 通过（字节匹配）
- **Level 4 测试:** 100% 通过（功能测试）

### 时间目标
- **Week 1-3:** 字节匹配调优
- **Week 4-5:** 功能测试
- **Week 6-7:** Bug 修复
- **Week 8:** 最终验收和发布准备

---

## 文件结构

```
tools/
├── compare_exe.py              # 二进制对比工具（已有）
├── batch_compare.py            # 批量对比脚本（新增）
├── match_analyzer.py           # 匹配分析工具（新增）
├── auto_tuner.py               # 自动调优工具（新增）
└── test_runner.py              # 测试运行器（新增）

build/reports/
├── byte_matching/
│   ├── overall_report.html     # 总体匹配报告
│   ├── by_module.html          # 按模块报告
│   ├── by_priority.html        # 按优先级报告
│   └── unmatched_functions.txt # 未匹配函数列表
└── testing/
    ├── level1_compilation.txt
    ├── level2_structure.txt
    ├── level3_matching.html
    └── level4_functional.txt

docs/pal3/
├── byte_matching_guide.md      # 字节匹配指南
├── testing_guide.md            # 测试指南
└── known_issues.md             # 已知问题列表
```

---

## Task 1: 批量对比和分析（Week 1, 3-4 天）

**目标:** 对所有函数进行批量对比，生成详细报告

**Files:**
- Create: `tools/batch_compare.py`
- Create: `tools/match_analyzer.py`

### Step 1: 创建批量对比脚本

```python
# tools/batch_compare.py
#!/usr/bin/env python3
"""
批量对比所有函数，生成详细报告

用法：
    python tools/batch_compare.py --output build/reports/byte_matching/
"""

import os
import json
from pathlib import Path
from compare_exe import compare_single_function, load_all_functions

def main():
    print("Starting batch comparison...")
    
    # 加载所有函数
    functions = load_all_functions()
    print(f"Found {len(functions)} functions")
    
    # 按优先级分类
    core_functions = []      # 核心函数（前 500）
    important_functions = [] # 重要函数（501-2000）
    other_functions = []     # 其他函数（2001+）
    
    # 加载优先级列表
    priority_list = load_priority_list()
    
    for i, func in enumerate(priority_list):
        if i < 500:
            core_functions.append(func)
        elif i < 2000:
            important_functions.append(func)
        else:
            other_functions.append(func)
    
    # 对比每个分类
    results = {
        'core': compare_batch(core_functions, "Core Functions"),
        'important': compare_batch(important_functions, "Important Functions"),
        'other': compare_batch(other_functions, "Other Functions")
    }
    
    # 生成报告
    generate_reports(results)
    
    print("\nBatch comparison complete!")
    print(f"Reports saved to build/reports/byte_matching/")

def compare_batch(functions, category_name):
    """对比一批函数"""
    print(f"\nComparing {category_name} ({len(functions)} functions)...")
    
    results = []
    for i, func in enumerate(functions):
        address = int(func['address'], 16)
        size = func['size']
        name = func['name']
        
        # 对比
        match_rate = compare_single_function(address, size)
        
        results.append({
            'address': address,
            'name': name,
            'size': size,
            'match_rate': match_rate
        })
        
        if (i + 1) % 100 == 0:
            print(f"  Progress: {i + 1}/{len(functions)} ({(i+1)/len(functions)*100:.1f}%)")
    
    return results

def generate_reports(results):
    """生成报告"""
    output_dir = Path("build/reports/byte_matching")
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # 总体报告
    generate_overall_report(results, output_dir / "overall_report.html")
    
    # 按模块报告
    generate_by_module_report(results, output_dir / "by_module.html")
    
    # 未匹配函数列表
    generate_unmatched_list(results, output_dir / "unmatched_functions.txt")

if __name__ == "__main__":
    main()
```

### Step 2: 创建匹配分析工具

```python
# tools/match_analyzer.py
#!/usr/bin/env python3
"""
分析字节匹配结果，识别模式

用法：
    python tools/match_analyzer.py build/reports/byte_matching/overall_report.json
"""

import json
import sys
from collections import defaultdict

def main():
    if len(sys.argv) < 2:
        print("Usage: python match_analyzer.py <report.json>")
        sys.exit(1)
    
    # 加载报告
    with open(sys.argv[1], 'r') as f:
        report = json.load(f)
    
    # 分析匹配模式
    analyze_match_patterns(report)
    
    # 识别常见不匹配原因
    identify_mismatch_reasons(report)
    
    # 给出调优建议
    suggest_tuning_strategies(report)

def analyze_match_patterns(report):
    """分析匹配模式"""
    print("Match Pattern Analysis")
    print("=" * 60)
    
    # 按函数大小统计
    size_buckets = defaultdict(list)
    for func in report['functions']:
        size = func['size']
        match_rate = func['match_rate']
        
        if size < 50:
            size_buckets['small'].append(match_rate)
        elif size < 200:
            size_buckets['medium'].append(match_rate)
        else:
            size_buckets['large'].append(match_rate)
    
    print("\nMatch Rate by Function Size:")
    for size_cat, rates in size_buckets.items():
        avg_rate = sum(rates) / len(rates) if rates else 0
        print(f"  {size_cat:10s}: {avg_rate:6.2f}% (n={len(rates)})")
    
    # 按模块统计
    module_stats = defaultdict(list)
    for func in report['functions']:
        module = get_module_from_name(func['name'])
        module_stats[module].append(func['match_rate'])
    
    print("\nMatch Rate by Module:")
    for module, rates in sorted(module_stats.items()):
        avg_rate = sum(rates) / len(rates) if rates else 0
        print(f"  {module:15s}: {avg_rate:6.2f}% (n={len(rates)})")

def identify_mismatch_reasons(report):
    """识别不匹配原因"""
    print("\n\nCommon Mismatch Reasons")
    print("=" * 60)
    
    # 统计常见不匹配模式
    reasons = defaultdict(int)
    
    for func in report['functions']:
        if func['match_rate'] < 95.0:
            # 分析汇编差异（简化示例）
            # 实际需要更复杂的汇编比对
            reasons['variable_ordering'] += 1
            reasons['loop_form'] += 1
            # ... 其他原因
    
    print("\nPotential Issues:")
    for reason, count in sorted(reasons.items(), key=lambda x: x[1], reverse=True):
        print(f"  {reason:30s}: ~{count} functions")

def suggest_tuning_strategies(report):
    """给出调优建议"""
    print("\n\nTuning Suggestions")
    print("=" * 60)
    
    # 按优先级给出建议
    unmatched = [f for f in report['functions'] if f['match_rate'] < 95.0]
    unmatched.sort(key=lambda x: (x['priority'], -x['match_rate']))
    
    print(f"\nTop 20 Functions to Tune (by priority):")
    for i, func in enumerate(unmatched[:20], 1):
        print(f"  {i:2d}. 0x{func['address']:08X} {func['name']:40s} "
              f"{func['match_rate']:6.2f}% (size: {func['size']})")

if __name__ == "__main__":
    main()
```

### Step 3: 运行批量对比

```bash
cd D:/workspace/project-x

# 批量对比所有函数
python tools/batch_compare.py --output build/reports/byte_matching/

# 分析结果
python tools/match_analyzer.py build/reports/byte_matching/overall_report.json
```

Expected: 生成详细的匹配报告和分析

### Step 4: 提交对比工具

```bash
git add tools/batch_compare.py
git add tools/match_analyzer.py
git add build/reports/byte_matching/
git commit -m "feat(phase8): add batch comparison and analysis tools

- Batch compare all functions
- Categorize by priority (core/important/other)
- Analyze match patterns
- Identify common mismatch reasons
- Generate HTML reports"
```

Expected: Git 提交成功

---

## Task 2: 核心函数调优（Week 1-2, 10-12 天）

**目标:** 对前 500 个核心函数进行精细调优，达到 95%+ 匹配率

**策略:** 逐个函数调优，应用匹配技术库

### 调优流程（每个函数）

**Step 1: 识别不匹配原因**
```bash
# 对比单个函数
python tools/compare_exe.py 0x004XXXXX <size> --verbose

# 查看汇编差异
python tools/disasm_compare.py 0x004XXXXX
```

**Step 2: 应用匹配技术**

根据差异类型应用技术：

**技术 1: 变量声明顺序**
```cpp
// Before (不匹配)
void Function() {
    int a;
    float b;
    char* c;
    double d;
}

// After (匹配)
void Function() {
    double d;      // 8 字节，先声明
    char* c;       // 4 字节
    float b;       // 4 字节
    int a;         // 4 字节
}
```

**技术 2: 循环形式**
```cpp
// Before
for (int i = 0; i < count; i++) { }

// After (MSVC 7.1 优化偏好)
for (int i = 0; i != count; i++) { }
```

**技术 3: 条件表达式**
```cpp
// Before
if (ptr != NULL) { }

// After
if (ptr) { }
```

**技术 4: 内联控制**
```cpp
// 小函数强制内联
__forceinline int Add(int a, int b) {
    return a + b;
}

// 需要地址的函数禁止内联
__declspec(noinline) void ComplexFunction() {
    // ...
}
```

**技术 5: 函数调用约定**
```cpp
// 确保调用约定匹配
int __cdecl CdeclFunc(int a);      // C 默认
int __stdcall StdcallFunc(int a);  // Win32 API
int __thiscall MemberFunc(int a);  // C++ 成员函数
```

**Step 3: 重新编译和对比**
```bash
# 重新编译
cd build
cmake --build . --config Release

# 再次对比
python tools/compare_exe.py 0x004XXXXX <size>
```

**Step 4: 迭代直到匹配**

重复 Step 1-3 直到匹配率达标。

### 重点函数（必须 100% 匹配）

1. **WinMain** (0x0055507C)
2. **Game_MainLoop** (0x004XXXXX)
3. **SCE_VM_Execute** (0x004XXXXX) - VM 主循环
4. **Window_WndProc** (0x004XXXXX)
5. **Game_Update** (0x004XXXXX)
6. **Game_Render** (0x004XXXXX)
7. **Battle_ExecuteTurn** (0x004XXXXX)
8. **UI_ProcessInput** (0x004XXXXX)

### 每日目标

- **Day 1-3:** 调优 WinMain, 主循环, 窗口过程（前 10 个函数）
- **Day 4-6:** 调优 VM 核心函数（11-50 个函数）
- **Day 7-9:** 调优战斗核心函数（51-100 个函数）
- **Day 10-12:** 调优其他核心函数（101-500 个函数）

### 验收标准

- [ ] 前 10 个函数 100% 匹配
- [ ] 前 100 个函数平均 98%+ 匹配
- [ ] 前 500 个函数平均 95%+ 匹配
- [ ] 记录所有调优技巧

---

## Task 3: 重要函数和其他函数调优（Week 2-3, 8-10 天）

**目标:** 对剩余函数进行批量调优

**策略:** 按模块批量调优，接受功能等价

### 批量调优流程

**Step 1: 按模块分组**
```bash
# 生成模块列表
python tools/analyze_pal3.py --group-by module
```

**Step 2: 每个模块批量调优**
```bash
# 对比整个模块
python tools/batch_compare.py --module script --threshold 90

# 生成调优建议
python tools/match_analyzer.py --module script --suggest
```

**Step 3: 应用常见修复**

创建自动化修复脚本：
```python
# tools/auto_tuner.py
#!/usr/bin/env python3
"""
自动应用常见的字节匹配修复

用法：
    python tools/auto_tuner.py src/pal3/script/
"""

import re
import sys
from pathlib import Path

def main():
    if len(sys.argv) < 2:
        print("Usage: python auto_tuner.py <directory>")
        sys.exit(1)
    
    dir_path = Path(sys.argv[1])
    
    for cpp_file in dir_path.rglob("*.cpp"):
        print(f"Processing {cpp_file}...")
        
        content = cpp_file.read_text(encoding='utf-8')
        
        # 应用修复
        content = fix_loop_forms(content)
        content = fix_null_checks(content)
        content = fix_variable_ordering(content)
        
        cpp_file.write_text(content, encoding='utf-8')
    
    print("Auto-tuning complete!")

def fix_loop_forms(content):
    """修复循环形式"""
    # for (i = 0; i < n; i++) => for (i = 0; i != n; i++)
    pattern = r'for\s*\(\s*(\w+)\s*=\s*0\s*;\s*\1\s*<\s*(\w+)\s*;'
    replacement = r'for (\1 = 0; \1 != \2;'
    return re.sub(pattern, replacement, content)

def fix_null_checks(content):
    """修复 NULL 检查"""
    # if (ptr != NULL) => if (ptr)
    pattern = r'if\s*\(\s*(\w+)\s*!=\s*NULL\s*\)'
    replacement = r'if (\1)'
    return re.sub(pattern, replacement, content)

def fix_variable_ordering(content):
    """修复变量声明顺序（简化版）"""
    # 这个比较复杂，需要解析 AST
    # 简化版：只给出警告
    return content

if __name__ == "__main__":
    main()
```

**Step 4: 验证修复**
```bash
# 重新编译
cmake --build build --config Release

# 批量对比
python tools/batch_compare.py --module script
```

### 接受功能等价

对于某些难以匹配的函数，接受功能等价：

**标准:**
- 函数功能完全相同
- 输入输出一致
- 无副作用差异
- 匹配率 ≥ 70%

**标记方式:**
```cpp
// 0x004XXXXX  FunctionName (~150 bytes)
// MATCH: 75% (功能等价，接受)
void FunctionName() {
    // 实现...
}
```

### 验收标准

- [ ] 501-2000 函数平均 90%+ 匹配
- [ ] 2001+ 函数平均 85%+ 匹配
- [ ] 整体平均 ≥ 85%
- [ ] 功能等价函数有明确标记

---

## Task 4: Level 1 - 编译验证（Week 4, 1 天）

**目标:** 验证代码能成功编译，无错误无警告

**Tests:**

```bash
# Test 1: 清理构建
rm -rf build/
mkdir build
cd build

# Test 2: CMake 配置
cmake .. -G "Visual Studio 17 2022" -A Win32

# Test 3: 编译 Release
cmake --build . --config Release

# Test 4: 检查编译输出
# 应该无错误，无警告

# Test 5: 检查生成的 exe
ls -lh bin/Release/PAL3.exe

# Test 6: 检查 exe 大小
# 应该接近原版大小（±5%）
```

**验收标准:**
- [ ] CMake 配置成功
- [ ] 编译成功，无错误
- [ ] 无编译警告
- [ ] exe 文件生成
- [ ] exe 大小在合理范围（1.9-2.3 MB）

---

## Task 5: Level 2 - 结构验证（Week 4, 1 天）

**目标:** 验证 PE 结构与原版一致

**Tests:**

```bash
# Test 1: 基地址检查
dumpbin /headers build/bin/Release/PAL3.exe | grep "image base"
# Expected: 400000 image base

# Test 2: 子系统检查
dumpbin /headers build/bin/Release/PAL3.exe | grep "subsystem"
# Expected: Windows GUI

# Test 3: 入口点检查
dumpbin /headers build/bin/Release/PAL3.exe | grep "entry point"
# Expected: 接近原版

# Test 4: 段（Section）结构检查
dumpbin /headers build/bin/Release/PAL3.exe > new_headers.txt
dumpbin /headers original/PAL3.exe > old_headers.txt
diff old_headers.txt new_headers.txt

# Test 5: 导入表检查
dumpbin /imports build/bin/Release/PAL3.exe > new_imports.txt
dumpbin /imports original/PAL3.exe > old_imports.txt
diff old_imports.txt new_imports.txt
# 应该导入相同的 DLL

# Test 6: 资源检查
dumpbin /resources build/bin/Release/PAL3.exe
```

**验收标准:**
- [ ] 基地址为 0x00400000
- [ ] 子系统为 Windows GUI
- [ ] 段结构相似
- [ ] 导入表包含所有必需的 DLL
- [ ] 资源存在（图标、清单等）

---

## Task 6: Level 3 - 字节匹配验证（Week 4, 2-3 天）

**目标:** 批量验证字节匹配率达标

**Tests:**

```bash
# Test 1: 批量对比所有函数
python tools/batch_compare.py --all --output build/reports/final_matching/

# Test 2: 生成最终报告
python tools/match_analyzer.py build/reports/final_matching/overall_report.json

# Test 3: 检查核心函数匹配率
python tools/check_core_functions.py --threshold 95

# Test 4: 检查整体匹配率
python tools/check_overall_match.py --threshold 85

# Test 5: 生成未匹配函数列表
python tools/list_unmatched.py --threshold 70 > build/reports/unmatched.txt

# Test 6: 生成 HTML 可视化报告
python tools/generate_html_report.py build/reports/final_matching/
```

**验收标准:**
- [ ] 核心函数（前 500）≥ 95% 匹配
- [ ] 重要函数（501-2000）≥ 90% 匹配
- [ ] 其他函数（2001+）≥ 85% 匹配
- [ ] 整体平均 ≥ 85% 匹配
- [ ] 生成详细的匹配报告

---

## Task 7: Level 4 - 功能测试（Week 4-5, 7-10 天）

**目标:** 全面测试游戏功能，确保无回归

### 测试用例设计

**Test Suite 1: 启动和菜单（Day 1）**

```
Test 1.1: 游戏启动
- 启动 PAL3.exe
- 验证: 窗口显示
- 验证: 无崩溃
- 验证: 显示主菜单

Test 1.2: 主菜单导航
- 操作: 在主菜单间切换
- 验证: 菜单正常响应
- 验证: 音效播放

Test 1.3: 设置菜单
- 操作: 进入设置
- 操作: 修改分辨率、音量
- 验证: 设置保存

Test 1.4: 退出游戏
- 操作: 选择退出
- 验证: 正常退出
- 验证: 配置已保存
```

**Test Suite 2: 新游戏和剧情（Day 2-3）**

```
Test 2.1: 开始新游戏
- 操作: 选择新游戏
- 验证: 播放开场动画
- 验证: 进入游戏场景

Test 2.2: 开场对话
- 操作: 播放开场对话
- 验证: 对话显示正确
- 验证: 能跳过/自动播放

Test 2.3: 剧情推进
- 操作: 触发剧情点
- 验证: 过场动画播放
- 验证: 剧情推进正常

Test 2.4: 长时间剧情
- 操作: 播放长段剧情（30分钟）
- 验证: 无卡顿
- 验证: 音视频同步
```

**Test Suite 3: 场景和移动（Day 3-4）**

```
Test 3.1: 角色移动
- 操作: 键盘/鼠标移动角色
- 验证: 移动流畅
- 验证: 动画正确

Test 3.2: 场景切换
- 操作: 进入不同场景
- 验证: 场景加载正常
- 验证: 淡入淡出流畅

Test 3.3: 碰撞检测
- 操作: 与障碍物碰撞
- 验证: 无穿模
- 验证: 碰撞响应正确

Test 3.4: NPC 互动
- 操作: 与 NPC 对话
- 验证: 对话触发
- 验证: 对话内容正确

Test 3.5: 互动对象
- 操作: 打开宝箱、触发机关
- 验证: 互动生效
- 验证: 获得物品
```

**Test Suite 4: 战斗系统（Day 4-6）**

```
Test 4.1: 触发战斗
- 操作: 遭遇敌人
- 验证: 进入战斗场景
- 验证: 战斗 UI 显示

Test 4.2: 普通攻击
- 操作: 执行普通攻击
- 验证: 伤害计算正确
- 验证: 动画播放

Test 4.3: 技能释放
- 操作: 释放各种技能
- 验证: MP 消耗正确
- 验证: 特效显示
- 验证: 伤害/效果正确

Test 4.4: 使用物品
- 操作: 使用恢复物品
- 验证: HP/MP 恢复
- 验证: 物品消耗

Test 4.5: 战斗 AI
- 操作: 观察敌人行为
- 验证: AI 合理
- 验证: 目标选择正确

Test 4.6: 战斗胜利
- 操作: 击败所有敌人
- 验证: 战斗结束
- 验证: 经验/物品获得

Test 4.7: 战斗失败
- 操作: 全灭
- 验证: 返回上次存档点
- 验证: 无数据丢失

Test 4.8: 逃跑
- 操作: 尝试逃跑
- 验证: 逃跑成功/失败概率合理

Test 4.9: 复杂战斗
- 操作: 进行 BOSS 战
- 验证: 战斗流畅
- 验证: 无卡顿/崩溃
```

**Test Suite 5: 物品和装备（Day 6-7）**

```
Test 5.1: 物品使用
- 操作: 使用各类物品
- 验证: 效果正确

Test 5.2: 装备穿戴
- 操作: 装备武器/防具
- 验证: 属性变化正确

Test 5.3: 物品排序
- 操作: 排序物品
- 验证: 排序正确

Test 5.4: 商店购买
- 操作: 购买物品
- 验证: 金钱扣除
- 验证: 物品获得

Test 5.5: 商店出售
- 操作: 出售物品
- 验证: 金钱增加
- 验证: 物品移除
```

**Test Suite 6: 存档系统（Day 7）**

```
Test 6.1: 保存游戏
- 操作: 保存到槽位
- 验证: 存档文件生成
- 验证: 缩略图正确

Test 6.2: 加载游戏
- 操作: 加载存档
- 验证: 游戏状态恢复
- 验证: 位置、物品、任务正确

Test 6.3: 多槽位
- 操作: 使用多个存档槽位
- 验证: 互不干扰

Test 6.4: 存档覆盖
- 操作: 覆盖已有存档
- 验证: 数据更新

Test 6.5: 快速存档
- 操作: F5 快速存档
- 验证: 自动存档成功
```

**Test Suite 7: 稳定性测试（Day 8-9）**

```
Test 7.1: 6 小时连续运行
- 操作: 游戏运行 6 小时
- 验证: 无崩溃
- 验证: 无内存泄漏
- 验证: 性能稳定

Test 7.2: 反复存档/读档
- 操作: 存档/读档 100 次
- 验证: 无数据损坏
- 验证: 无崩溃

Test 7.3: 反复进出战斗
- 操作: 战斗 50 次
- 验证: 无崩溃
- 验证: 内存正常

Test 7.4: 场景切换压力测试
- 操作: 场景切换 100 次
- 验证: 无崩溃
- 验证: 无内存泄漏
```

**Test Suite 8: 完整通关测试（Day 9-10）**

```
Test 8.1: 完整流程
- 操作: 从头通关游戏
- 验证: 所有主线任务完成
- 验证: 所有关键剧情触发
- 验证: 能进入结局

Test 8.2: 支线任务
- 操作: 完成支线任务
- 验证: 任务可完成
- 验证: 奖励获得

Test 8.3: 隐藏内容
- 操作: 触发隐藏内容
- 验证: 隐藏 BOSS
- 验证: 隐藏物品
```

### 自动化测试框架

```python
# tools/test_runner.py
#!/usr/bin/env python3
"""
自动化测试运行器

用法：
    python tools/test_runner.py --suite all
    python tools/test_runner.py --suite startup
"""

import subprocess
import time
import psutil

class TestRunner:
    def __init__(self):
        self.results = []
    
    def run_test_suite(self, suite_name):
        """运行测试套件"""
        print(f"Running test suite: {suite_name}")
        
        if suite_name == "startup":
            self.test_startup()
        elif suite_name == "stability":
            self.test_stability()
        elif suite_name == "all":
            self.run_all_suites()
    
    def test_startup(self):
        """测试启动"""
        print("Test 1: Game startup...")
        
        # 启动游戏
        proc = subprocess.Popen(["build/bin/Release/PAL3.exe"])
        
        # 等待 5 秒
        time.sleep(5)
        
        # 检查进程是否还在运行
        if proc.poll() is None:
            print("✅ Game started successfully")
            proc.terminate()
            return True
        else:
            print("❌ Game crashed on startup")
            return False
    
    def test_stability(self):
        """测试稳定性（6 小时）"""
        print("Test 2: 6-hour stability test...")
        
        # 启动游戏
        proc = subprocess.Popen(["build/bin/Release/PAL3.exe"])
        
        # 监控 6 小时
        start_time = time.time()
        duration = 6 * 3600  # 6 hours
        
        while time.time() - start_time < duration:
            # 检查进程
            if proc.poll() is not None:
                print(f"❌ Game crashed after {(time.time() - start_time) / 3600:.2f} hours")
                return False
            
            # 检查内存
            try:
                process = psutil.Process(proc.pid)
                mem_mb = process.memory_info().rss / 1024 / 1024
                print(f"Memory usage: {mem_mb:.1f} MB")
                
                # 内存泄漏检测（简化）
                if mem_mb > 2000:  # > 2GB
                    print("⚠️  High memory usage detected")
            except:
                pass
            
            # 每 5 分钟检查一次
            time.sleep(300)
        
        print("✅ 6-hour stability test passed")
        proc.terminate()
        return True

if __name__ == "__main__":
    runner = TestRunner()
    runner.run_test_suite("all")
```

### 验收标准

- [ ] 所有启动测试通过
- [ ] 所有剧情测试通过
- [ ] 所有场景测试通过
- [ ] 所有战斗测试通过
- [ ] 所有物品测试通过
- [ ] 所有存档测试通过
- [ ] 6 小时稳定性测试通过
- [ ] 完整通关测试通过

---

## Task 8: Bug 修复和回归测试（Week 6-7, 持续）

**目标:** 修复测试中发现的所有 P0/P1 bug

### Bug 跟踪

使用 GitHub Issues 或 Excel 表格跟踪：

| ID | 标题 | 严重性 | 状态 | 修复者 | 验证者 |
|----|------|--------|------|--------|--------|
| #1 | 游戏启动崩溃 | P0 | Fixed | XXX | XXX |
| #2 | 战斗卡死 | P0 | Open | XXX | - |
| #3 | 存档损坏 | P1 | Fixed | XXX | XXX |
| ... | ... | ... | ... | ... | ... |

**严重性定义:**
- **P0 (Blocker):** 崩溃、数据损坏、无法游玩
- **P1 (Critical):** 主要功能异常
- **P2 (Major):** 次要功能异常
- **P3 (Minor):** 体验问题、美化

### 修复流程

1. **复现 Bug**
   - 记录复现步骤
   - 确认必现/偶现

2. **诊断原因**
   - 调试器定位
   - 日志分析
   - 代码审查

3. **实施修复**
   - 修改代码
   - 本地测试

4. **回归测试**
   - 验证修复有效
   - 确认无新引入 bug
   - 重新运行相关测试用例

5. **提交修复**
   - Git commit
   - 更新 bug 状态

### 每日目标

- 每天修复 5-10 个 bug
- 每天运行回归测试
- 保持 bug 队列 < 50 个

### 验收标准

- [ ] 所有 P0 bug 修复
- [ ] 所有 P1 bug 修复
- [ ] P2 bug < 10 个
- [ ] 回归测试通过

---

## Task 9: 最终验收和发布准备（Week 8, 3-5 天）

**目标:** 最终检查，准备发布

### 最终检查清单

**代码质量:**
- [ ] 所有代码提交到 Git
- [ ] 代码注释完整
- [ ] 无 TODO/FIXME
- [ ] 代码风格统一

**文档完整:**
- [ ] README.md 完整
- [ ] BUILD.md 构建指南
- [ ] TESTING.md 测试指南
- [ ] KNOWN_ISSUES.md 已知问题列表
- [ ] CHANGELOG.md 更新日志

**字节匹配:**
- [ ] 核心函数 ≥ 95%
- [ ] 整体 ≥ 85%
- [ ] 生成最终匹配报告

**功能测试:**
- [ ] 所有测试用例通过
- [ ] 完整通关测试通过
- [ ] 无 P0/P1 bug

**性能测试:**
- [ ] FPS ≥ 30
- [ ] 内存 < 1GB
- [ ] 启动时间 < 10 秒

**兼容性测试:**
- [ ] Windows 10 测试通过
- [ ] Windows 11 测试通过
- [ ] 多种显卡测试（NVIDIA, AMD, Intel）

### 发布准备

**生成发布包:**
```bash
# 清理构建
rm -rf build/
cmake -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release

# 复制文件到发布目录
mkdir release
cp build/bin/Release/PAL3.exe release/
cp original/gbengine.dll release/
cp original/topo.dll release/
cp README.md release/
cp LICENSE release/

# 打包
cd release
zip -r PAL3_Decompiled_v1.0.zip *
```

**发布说明:**
```markdown
# PAL3.exe 反编译版本 v1.0

**发布日期:** 2026-XX-XX

## 项目信息
- **总函数数:** XXXX
- **字节匹配率:** XX%
- **开发时间:** 9-10 个月

## 特性
- ✅ 100% 功能完整
- ✅ 核心函数 95%+ 字节匹配
- ✅ 完整通关测试通过
- ✅ 长时间稳定运行

## 已知问题
[列出所有已知问题]

## 安装
1. 解压到游戏目录
2. 备份原版 PAL3.exe
3. 运行新的 PAL3.exe

## 致谢
- Ghidra 逆向工程工具
- PAL3patch 项目（zhangboyang）
- OpenPAL3 项目（dontpanic92）
- PAL3 社区

## 许可证
[指定许可证]
```

---

## Phase 8 验收标准（总体）

### 字节匹配验收
- [x] 核心函数（前 500）≥ 95% 匹配
- [x] 重要函数（501-2000）≥ 90% 匹配
- [x] 其他函数（2001+）≥ 85% 匹配
- [x] 整体平均 ≥ 85% 匹配

### 测试验收
- [x] Level 1 编译测试 100% 通过
- [x] Level 2 结构测试 100% 通过
- [x] Level 3 字节匹配测试通过
- [x] Level 4 功能测试 100% 通过

### 质量验收
- [x] 所有 P0 bug 修复
- [x] 所有 P1 bug 修复
- [x] P2 bug < 10 个
- [x] 代码质量达标

### 文档验收
- [x] 所有文档完整
- [x] 匹配技巧记录完整
- [x] 测试报告完整
- [x] 发布说明完整

---

## Phase 8 完成报告模板

```markdown
# PAL3.exe Phase 8 完成报告

**完成日期:** 2026-XX-XX  
**工期:** X 周  
**最终进度:** 100%

## 字节匹配统计
- 核心函数（前 500）: XX% (目标: 95%)
- 重要函数（501-2000）: XX% (目标: 90%)
- 其他函数（2001+）: XX% (目标: 85%)
- **整体平均: XX%** (目标: 85%)

## 测试统计
- Level 1 编译测试: PASS
- Level 2 结构测试: PASS
- Level 3 字节匹配: PASS
- Level 4 功能测试: XX/XX PASS

## Bug 统计
- P0 bug: 0 (全部修复)
- P1 bug: 0 (全部修复)
- P2 bug: X (可接受)
- P3 bug: XX (待修复)

## 性能统计
- 平均 FPS: XX
- 内存使用: XXX MB
- 启动时间: X 秒
- 6 小时稳定性: PASS

## 交付物
- [x] PAL3.exe 源代码
- [x] 完整文档
- [x] 测试报告
- [x] 匹配报告
- [x] 发布包

## 总结
[项目总结]

## 致谢
[感谢名单]
```

---

**Phase 8 计划完成！全部 8 个 Phase 计划已创建！**

---

## 全部计划总览

1. ✅ **Phase 0:** 基础设施搭建（2-3 周）
2. ✅ **Phase 1:** 程序框架和主循环（1 个月）
3. ✅ **Phase 2:** SCE 脚本引擎（1.5 个月）
4. ✅ **Phase 3-7:** 核心游戏系统（6-7 个月，概要）
5. ✅ **Phase 8:** 字节匹配调优和测试（1-2 个月）

**总工期:** 9-10 个月  
**总函数数:** 3500-5000 个  
**总代码行数:** 20000-30000 行
