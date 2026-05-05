# gbengine.dll Stub 批量实现设计

## 目标

将 gbengine/stubs/ 中剩余的 ~327 个空函数体实现为功能正确的 C++ 代码，涉及 53 个类。每个类新建独立主源文件，删除对应 stub 文件。冗余和空 stub 文件一并清理。

## 约束

- **功能正确优先**：不追求字节匹配，确保逻辑正确可运行
- **一次性完成**：不分批交付，全部 stub 在一轮中处理
- **不确定处标记 `/* UNCERTAIN */`**：缺少参考的复杂函数标记后续校正
- **编译器**：MSVC 6.0 SP5，32-bit x86
- **参考来源**：PDB 符号、已有代码模式、Ghidra 反编译、PAL3patch 社区代码

## 工作范围

| 工作类型 | 数量 |
|----------|------|
| 删除冗余 stub（主文件已有实现） | 11 个文件 |
| 删除空 stub（0 个函数） | 12 个文件 |
| 新建主文件 + 实现函数 | 53 个类 / ~327 个函数 |

### 冗余 stub 文件（直接删除）

已有对应主文件且函数完全重复：
- stub_gbActor.cpp, stub_gbAudioManager.cpp, stub_gbCamera.cpp
- stub_gbGeomNode.cpp, stub_gbGfxManager.cpp, stub_gbPrintFont.cpp
- stub_gbResManager.cpp, stub_gbSceneGraph.cpp, stub_gbTexture.cpp
- stub_gbVFileSystem.cpp, stub_gbVisNode.cpp

### 空 stub 文件（直接删除）

函数体数为 0：
- stub_gbActorMgr.cpp (只有 operator= 返回静态对象，已在别处)
- stub_gbAudioMgrDesc.cpp, stub_gbCamControler.cpp
- stub_gbChain1DNode.cpp, stub_gbChain2DNode.cpp
- stub_gbColorQuad.cpp, stub_gbEmitterData.cpp
- stub_gbEmitterSquare.cpp, stub_gbPartEmitter.cpp
- stub_gbPartParamControl.cpp, stub_gbParticleUnit.cpp
- stub_gbVolumeModifier.cpp

## 分层架构

### L0 — 基础数据类型（~120 函数）

纯数学/几何运算，确定性最高。topo.dll 中有完全相同的实现可参考。

| 类 | 函数数 | 参考 |
|----|--------|------|
| gbMatrix4 | 36 | src/topo/gbMatrix4.cpp |
| gbQuaternion | 18 | src/topo/gbQuaternion.cpp |
| gbVec3D | 13 | src/topo/gbVec3D.cpp |
| gbMatrixStack | 13 | src/topo/gbMatrixStack.cpp |
| gbRotMatrix | 6 | src/topo/gbRotMatrix.cpp |
| gbRay | 8 | 射线相交算法 |
| gbOBBox | 7 | 有向包围盒 |
| BEZIER | 5 | 贝塞尔曲线求值 |
| gbAABBox | 3 | 包围盒操作 |
| gbSphere | 3 | 球体碰撞 |
| gbColorFlt | 2 | PAL3patch 结构体 |
| gbPlane | 2 | 平面方程 |

### L1 — 基础设施（~80 函数）

容器、文件、链表等基础数据结构。

| 类 | 函数数 | 说明 |
|----|--------|------|
| gbChain1D | 9 | 单向链表 |
| gbChain2D | 6 | 双向链表 |
| gbStaticChain | 11 | 静态分配链表 |
| gbNBTreeNode | 10 | N叉树节点 |
| gbNBTree | 2 | N叉树管理 |
| gbBinaryTree | 2 | 二叉树 |
| gbBinaryTreeNode | 3 | 二叉树节点 |
| gbNameVarBuf | 6 | 名称-变量缓冲区 |
| gbVFile1 | 1 | 虚拟文件 |
| gbVTextFile | 4 | 文本文件解析 |
| gbPixelFormat | 6 | 像素格式转换 |
| gbUIRect | 3 | UI 矩形 |
| gbTimeCounter | 2 | 高精度计时器 |
| gbIndexBubble | 1 | 索引冒泡排序 |
| globals | 10 | 全局工具函数 (gbVfgetdir, gbConvertToSBC 等) |

### L2 — 引擎核心（~80 函数）

渲染资源管理，部分需要 UNCERTAIN 标记。

| 类 | 函数数 | 说明 |
|----|--------|------|
| gbImage2D | 15 | 2D 图像加载/操作 |
| gbImage2DInfo | 1 | 图像信息 |
| gbRenderEffect | 13 | 渲染效果/材质 |
| gbDynVertBuf | 11 | 动态顶点缓冲区 (D3D) |
| gbBaseMesh | 7 | 网格基类 |
| gbStaticMesh | 2 | 静态网格 |
| gbTexture_D3D | 7 | D3D 纹理实现 |
| gbTextureArray | 1 | 纹理数组 |
| gbLightObj | 7 | 灯光对象 |
| gbVertPoolMgr | 1 | 顶点池管理 |
| gbPrintFontMgr | 1 | 字体管理器 |

### L3 — 高层功能（~50 函数）

粒子系统、天气、动画、音频、文件包。

| 类 | 函数数 | 说明 |
|----|--------|------|
| CPK | 16 | CPK 文件包 (LZO + CRC32) |
| gbAnimNodeGroup | 12 | 动画节点组 |
| gbEffectMgr | 11 | 特效管理器 |
| gbParticleGroup | 6 | 粒子组 |
| gbPartGroupParam | 6 | 粒子参数 |
| gbParticleEffect | 3 | 粒子效果 |
| gbVolModNode | 5 | 体积变形节点 |
| gbRain | 2 | 雨效果 |
| gbSnow | 2 | 雪效果 |
| gbDropGroup | 1 | 水滴组 |
| gbSound2DNode | 1 | 2D 音频 |
| gbSound3DNode | 1 | 3D 音频 |
| gbCamQuakeControl | 1 | 相机震动 |
| gbCamSpringControl | 1 | 相机弹簧 |
| gbGfxManager_D3D | 1 | D3D 图形管理器 (SetTexture) |

## 实现策略

### 函数分类处理

| 类型 | 占比 | 处理方式 |
|------|------|----------|
| Getter/Setter/转发 | ~40% | 从类布局直接推断，返回成员变量 |
| 数学/几何算法 | ~25% | 复用 topo.dll 已有实现 |
| 数据结构操作 | ~15% | 标准链表/树操作模式 |
| 资源/渲染管理 | ~15% | 参考 PAL3patch + D3D 常见模式，部分标记 UNCERTAIN |
| 高复杂度 | ~5% | 标记 UNCERTAIN，写出最合理推断 |

### 每个类的输出文件结构

```
src/gbengine/gbXXX.cpp:
  - 文件头注释（类名、简要说明、类布局）
  - #include 对应头文件
  - 所有方法实现
  - UNCERTAIN 标记处附加推断依据注释
```

### 头文件处理

- 已有头文件（`include/gbengine/gbXXX.h`）：直接引用
- 缺少头文件的类：在实现文件中前向声明或 include `gbengine_types.h`
- 不在本次范围内新建大量头文件，保持与现有代码一致的风格

### 编译验证

实现完成后应能通过 `cmake -B build -DBUILD_TARGET=gbengine && cmake --build build` 编译。链接阶段可能因外部库（d3d9, Miles Sound）缺失而失败，但编译阶段不应有错误。

## 成功标准

1. `src/gbengine/stubs/` 目录为空或被删除
2. 53 个新建的 `src/gbengine/gbXXX.cpp` 文件包含功能正确的实现
3. 所有不确定实现标记 `/* UNCERTAIN */`
4. gbengine target 编译通过（不要求链接通过）
5. 现有已实现的主文件（gbCamera.cpp 等）不受影响
