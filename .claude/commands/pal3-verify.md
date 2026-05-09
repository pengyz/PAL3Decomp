---
name: pal3-verify
description: 从已实现代码中推断类型信息，更新 BFS 节点标注，优化源码质量。核心是类型推理→标注→代码改进的闭环。
---

## 目标

从当前已实现的代码中提取类型知识，完善 BFS call_graph 的类型标注，最终改善代码质量。

**顺序**: 分析推断 → 更新标注 → 改进代码（不能跳步）

## Phase 1: 类型推断（只读分析）

扫描所有 `src/pal3/` 中已实现的 .cpp 文件，识别以下模式：

### 1.1 类型强转暴露的真实类型

```cpp
// 模式: (ClassName *)global_var → global_var 的真实类型是 ClassName*
((CCBSystem_D *)g_pCBSystem)->ProcFling();   // → g_pCBSystem 应为 CCBSystem*
((VObj *)g_pCamera)->Release(1);             // → g_pCamera 有虚析构函数
((gbActorMgr *)g_pActorMgr)->~gbActorMgr(); // → g_pActorMgr 应为 gbActorMgr*
```

### 1.2 函数返回值暴露的类型

```cpp
// 模式: (ClassName *)sub_XXXX() → sub_XXXX 返回 ClassName*
((CRenderTarget *)sub_4BDB10())->Destroy();  // → sub_4BDB10 返回 CRenderTarget*
```

### 1.3 thiscall 调用模式暴露类身份

```cpp
// 模式: obj.Method() 或 ptr->Method() → obj/ptr 的类名和方法签名
g_GameData.Destroy();           // → g_GameData 是 CGameData 类型
sub_53DF70()->Restore();        // → sub_53DF70() 返回 CScreenMode*
```

### 1.4 全局变量地址注释暴露结构体布局

```cpp
// 模式: extern "C" int dword_BFDA78; // 0x00BFDA78 - scene manager
// 相邻地址暗示结构体成员:
// g_pCBSystem  @ 0xBFDA74  (offset +0x00)
// dword_BFDA78 @ 0xBFDA78  (offset +0x04) 
// → 可能是同一结构体的成员
```

### 1.5 gbengine.lib 导出符号提供的签名

```bash
# 从 lib/gbengine.def 中 demangle 可获得精确函数签名
grep "gbActorMgr\|gbGfxManager\|gbCamera" lib/gbengine.def
```

### 1.6 PAL3A PDB 类定义（交叉验证）

`asm/pal3a/pdb_export.json` 包含 1057 个类的完整定义（data_members + methods）。

```python
# 查询类定义
import json
d = json.load(open('asm/pal3a/pdb_export.json'))
for c in d['classes']:
    if c['name'] == 'CCBSystem':
        for m in c['data_members']:
            print(f"+0x{m['offset']:04X} {m['type']:30s} {m['name']}")
```

**关键约束: PAL3A PDB 与 PAL3 是不同版本！**

- **成员名和类型**: 可直接参考（命名权威）
- **偏移量**: **必须从 PAL3.exe 二进制验证**，不能直接照搬
  - 例: PDB 说 CCBSystem::m_pStage @ +0x14，但 PAL3 二进制中实际是 +0x1C
- **类大小**: 可能不同（成员增减导致布局变化）
- **方法列表**: 名称可参考，但地址和大小对应 PAL3A 不是 PAL3

**工作流**: PDB 提供命名 → 从 PAL3.exe 反汇编确认偏移 → 生成头文件用 PDB 名+二进制偏移

## Phase 2: 更新 BFS 标注

将推断结果写入 `asm/pal3/call_graph.json`：

```json
{
  "0x004BDB10": {
    "name": "CRenderTarget::GetInstance",    // 从 sub_4BDB10 改名
    "return_type": "CRenderTarget*",         // 新增字段
    "suggested_source": "Render/RenderTarget.cpp",  // 推断源文件
    ...
  }
}
```

**更新规则**:
- `name`: 当推断出有意义的类名+方法名时更新（替代 sub_XXXXXX）
- `suggested_source`: 当确认类归属时填入 PDB 路径格式
- `signature`: 当推断出完整签名时更新
- `return_type`/`param_types`: 新增辅助字段供迭代使用

## Phase 3: 代码位置调整与文件拆分

**仅在 Phase 1-2 完成后才执行代码改动。核心原则：代码放到 PDB 规定的位置。**

### 3.1 类声明拆分为头文件

当一个类的方法在多处使用（多个 TU 中出现强转或调用）时，必须创建独立头文件：

```
include/pal3/<suggested_source_path>.h   ← 类声明
src/pal3/<suggested_source_path>.cpp     ← 方法实现/stub
```

**规则**:
- gbengine 类 → `include/gbengine/ClassName.h`（使用 GBAPI 宏）
- PAL3 游戏类 → `include/pal3/ClassName.h`（本地声明）
- 如果头文件/cpp 已存在，将声明/实现合并进去，不重复创建

**示例**:
```
// globals.cpp 中有:
class CCBSystem { public: void ProcFling(); ~CCBSystem(); };
CCBSystem::~CCBSystem() {}
void CCBSystem::ProcFling() {}

// 应拆分为:
// include/pal3/CCBSystem.h  ← 类声明
// src/pal3/Combat/CBSystem.cpp ← stub 合并到已有文件
```

### 3.2 Stub 实现归位

当 call_graph 节点有 `suggested_source` 时，将 stub 从 globals.cpp 移到对应文件：
- 如果目标 .cpp 已存在 → 将 stub 追加到该文件
- 如果目标 .cpp 不存在 → 创建文件，添加到 CMakeLists.txt
- globals.cpp 中只保留**无法确定归属**的 stub（suggested_source=null）

### 3.3 全局变量与函数重命名

1. **全局变量类型升级**: `extern "C" int g_pActorMgr` → 使用正确类型（受 C linkage 限制时保持 int）
2. **消除冗余 class 声明**: 用 `#include` 头文件替代各 TU 中的重复 class 定义
3. **rename 函数**: globals.cpp 中的 stub 名从 sub_ 改为推断名

### 3.4 CMakeLists.txt 同步

新增 .cpp 文件时必须更新 `PAL3_SOURCES` 列表，确保构建门控通过。

## 执行

每次调用**必须**执行完整循环，**不得跳过文件拆分步骤**：

```
0. **BFS ↔ 代码同步检查** (新增，最先执行)
   - 扫描所有 src/pal3/*.cpp 中的 sub_XXXXXX stub 定义
   - 检查每个 stub 是否已在 call_graph.json 中注册
   - 未注册的立即用 `python tools/pal3_callgraph.py add` 补充
   - 检查 call_graph 中 status=compiled/matched 的节点是否真的有实现（非空 stub）
   - 检查 .claude/pal3_workarounds.md 中记录的问题，尝试修复
1. 读取所有 compiled/matched/wip 函数的源码
2. 提取类型推断 (Phase 1)
3. 输出推断摘要
4. 更新 call_graph.json + xref (Phase 2)
5. **强制检查: 代码位置是否匹配 PDB/推断位置**
   - 遍历所有已识别类的方法，检查它们是否在正确的 .cpp 文件中
   - 如果 globals.cpp 中有已确定归属的类方法 → 必须拆分到对应文件
   - 如果某个类的方法散落在多个文件 → 合并到一个正确位置
6. 执行文件拆分 + CMakeLists 更新 (Phase 3)
7. 全局变量重命名 (Phase 3)
8. cmake --build 验证 + 输出 PAL3.exe size
9. compare 验证 matched 函数未被破坏
10. commit
```

**关键**: Phase 5 是强制的。如果发现任何类方法在 globals.cpp 中而该类已有明确归属，必须立即拆分。不拆分就不提交。

## 输出格式

```
═══ PAL3 类型推断结果 ═══
[推断] g_pCamera (0xBFDA68): int → gbCamera* (虚析构, gbengine 导出)
[推断] sub_4BDB10: int() → CRenderTarget* GetInstance()  
[推断] sub_53DF70: int() → CScreenMode* GetInstance()
[推断] g_GameData (0xDB9FD0): int → CGameData (thiscall .Destroy())
[BFS更新] 0x004BDB10: name="CRenderTarget::GetInstance", return_type="CRenderTarget*"
[拆分] CCBSystem::ProcFling → src/pal3/Combat/CBSystem.cpp (合并到已有文件)
[拆分] 新建 include/pal3/CCBSystem.h ← 类声明
[代码] PAL3.cpp: #include "pal3/CCBSystem.h" 替代内联 class 声明
[构建] PASS — PAL3.exe 16,384 bytes
[匹配] PAL3::Destroy 100% ✓
═══════════════════════════
```
