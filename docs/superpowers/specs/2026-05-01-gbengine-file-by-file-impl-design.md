# gbengine.dll 按文件逐步实现设计

## Goal

系统性地实现 gbengine.dll 中剩余 326 个 stub/incomplete 函数，按 .cpp 文件为单位工作，遵循依赖层级自底向上的顺序。每个函数以 Ghidra JSON 反编译数据为主要参考源，目标是功能等价（不要求字节匹配）。

## 当前状态

| 指标 | 数值 |
|------|------|
| DLL 导出总数 | 1020 |
| 字节级验证通过 | 587 |
| 源码函数总数 | 931 |
| IMPLEMENTED | 330 (35.4%) |
| TRIVIAL | 275 (29.5%) |
| INCOMPLETE | 25 (2.7%) |
| STUB | 301 (32.3%) |
| **待实现** | **326** |

## 约束

- MSVC 编译通过（当前用 VS2022 /W3 配置）
- 导出符号名修饰不变（name mangling 一致）
- 功能等价：逻辑正确即可，不要求字节匹配
- 参考源：`asm/gbengine/` 下的 Ghidra JSON 反编译数据
- 每完成一个文件需通过 `cmake --build build_gbengine --config Release`

## 文件处理顺序（依赖层级）

按照依赖图从底层到顶层，确保每步实现的函数只依赖已实现的底层代码：

### Phase 1: 数学与基础工具（8 functions）

| # | 文件 | 待实现 | 内容 |
|---|------|--------|------|
| 1 | `gbMath.cpp` | 3 | gbOBBox::IsColOBB, gbRay::IsColOBB, gbRay::IsColOBB_H |
| 2 | `gbMisc.cpp` | 2 | gbUIRect::Release, gbUIRect::Render |

### Phase 2: 资源管理（19 functions）

| # | 文件 | 待实现 | 内容 |
|---|------|--------|------|
| 3 | `gbVertPool.cpp` | 5 | gbVertexPool/gbIndexPool/gbVertPoolMgr 方法 |
| 4 | `gbMesh.cpp` | 11 | gbBaseMesh/gbStaticMesh/gbDynVertBuf 方法 |
| 5 | `gbTexture.cpp` | 3 | gbImage2D::LoadImageFile/WriteJpegImage, gbTexture 创建 |

### Phase 3: 系统服务（20 functions）

| # | 文件 | 待实现 | 内容 |
|---|------|--------|------|
| 6 | `gbAudioManager.cpp` | 2 | gbResManagerStub::Init, gbSoundData::IncRef |
| 7 | `gbCamera.cpp` | 4 | gbCamControler::Update, gbCamSpringControl::Update, ZBuffer 操作 |
| 8 | `gbGfxManager.cpp` | 14 | gbGfxManager getter/setter, gbEffectMgr 方法 |

### Phase 4: 场景图（32 functions）

| # | 文件 | 待实现 | 内容 |
|---|------|--------|------|
| 9 | `gbSceneGraph.cpp` | 10 | gbSceneGraph 构造/AddVisNode/DelVisNode/End 等 |
| 10 | `gbVisNode.cpp` | 8 | gbVisNode 渲染/更新/附加方法 |
| 11 | `gbGeomNode.cpp` | 14 | gbGeomNode::LoadFromFile/LoadCVD/Render 全部方法 |

### Phase 5: 模型与效果（32 functions）

| # | 文件 | 待实现 | 内容 |
|---|------|--------|------|
| 12 | `gbActor.cpp` | 15 | gbActor::Render/GotoAction/Shadow 等 |
| 13 | `gbParticle.cpp` | 15 | gbParticleGroup/gbPartEmitter/LoadFromFile 等 |
| 14 | `gbWeather.cpp` | 2 | 天气效果渲染 |

### Phase 6: 全局导出存根（218 functions）

| # | 文件 | 待实现 | 内容 |
|---|------|--------|------|
| 15 | `gbengine_stubs.cpp` | 218 | 需拆分到各自归属的 .cpp 文件中实现 |

## 单文件工作流程

对每个 .cpp 文件中的每个 stub/incomplete 函数：

1. **定位 Ghidra JSON**：在 `asm/gbengine/` 中按函数名或地址查找对应 JSON 文件
2. **阅读反编译代码**：理解函数逻辑、参数、返回值
3. **写出 C++ 实现**：
   - 保持与 Ghidra 输出等价的控制流
   - 使用正确的类型（参考 PDB 信息和 header 定义）
   - 移除 Ghidra 伪代码的瑕疵（强转、临时变量）
4. **移除 stub 标记**：删除 `// Stub` 等注释
5. **编译验证**：`cmake --build build_gbengine --config Release`
6. **运行进度工具**：确认函数状态变为 IMPLEMENTED/TRIVIAL

## gbengine_stubs.cpp 处理策略

`gbengine_stubs.cpp` 包含 218 个自动生成的空函数体，这些函数的声明已存在于各 header 中。处理策略：

1. 每处理一个 Phase 1-5 的文件时，检查 `gbengine_stubs.cpp` 中是否有属于同一类的函数
2. 将这些函数移到对应的 .cpp 文件并实现
3. 从 `gbengine_stubs.cpp` 中删除已移走的函数
4. 最终目标：`gbengine_stubs.cpp` 清空或只留真正无法归类的全局函数

## Ghidra JSON 数据格式

每个 JSON 文件（`asm/gbengine/FUNCNAME_ADDR.json`）包含：
```json
{
  "name": "gbCamera::SetLookAt",
  "address": "0x10012340",
  "decompiled_c": "void __thiscall gbCamera::SetLookAt(...) { ... }",
  "size": 128,
  "calling_convention": "__thiscall"
}
```

## 验证标准

每个文件完成后需满足：
- [ ] `cmake --build build_gbengine --config Release` 零错误
- [ ] `python tools/gbengine_progress.py --class <ClassName>` 显示无 STUB/INCOMPLETE
- [ ] 导出符号数量不减少（当前 1020）

## 成功标准

- 所有 326 个 stub/incomplete 函数实现为 IMPLEMENTED 或 TRIVIAL
- `gbengine_stubs.cpp` 中的函数全部迁移到归属文件
- 编译零错误，导出 1020 个符号
- 进度报告显示 0 STUB + 0 INCOMPLETE
