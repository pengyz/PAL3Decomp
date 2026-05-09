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

## Phase 3: 代码改进

**仅在 Phase 1-2 完成后才执行代码改动**：

1. **全局变量类型升级**: `extern "C" int g_pActorMgr` → 使用正确类型
2. **消除冗余 class 声明**: 用 #include gbengine 头文件替代
3. **rename 函数**: globals.cpp 中的 stub 名从 sub_ 改为推断名
4. **拆分文件**: 当 suggested_source 确定时，将 stub 移到正确位置

## 执行

每次调用执行一轮完整分析-标注-改进循环：

```
1. 读取所有 compiled/matched 函数的源码
2. 提取类型推断 (Phase 1)
3. 输出推断摘要供人工确认
4. 更新 call_graph.json (Phase 2)
5. 应用代码改进 (Phase 3)
6. cmake --build 验证
7. compare 验证 matched 函数未被破坏
8. commit
```

## 输出格式

```
═══ PAL3 类型推断结果 ═══
[推断] g_pCamera (0xBFDA68): int → gbCamera* (虚析构, gbengine 导出)
[推断] sub_4BDB10: int() → CRenderTarget* GetInstance()  
[推断] sub_53DF70: int() → CScreenMode* GetInstance()
[推断] g_GameData (0xDB9FD0): int → CGameData (thiscall .Destroy())
[BFS更新] 0x004BDB10: name="CRenderTarget::GetInstance", return_type="CRenderTarget*"
[代码] globals.cpp: extern "C" int g_pActorMgr → 类型保持 int (C linkage 限制)
[代码] PAL3.cpp: 新增 #include "gbengine/gbActorMgr.h" ✓
[构建] PASS
[匹配] PAL3::Destroy 100% ✓
═══════════════════════════
```
