# gbengine.dll 架构清理设计文档

## 目标

消除 gbengine.dll 构建中的 `/FORCE` 链接标志，使所有 1020 个 DEF 导出符号均有正确定义，实现干净链接。同时将现有函数从临时文件归位到正确源文件，并搭建 VC6 SP5 工具链用于后续 byte-exact 编译。

## 背景

当前状态：
- DEF 文件声明 1020 个导出符号（含 1 个 DATA: `stamp`）
- 已实现 ~394 个导出（在各源文件 + gbengine_exports.cpp）
- 626 个符号未解析，依赖 `/FORCE:MULTIPLE` 强制链接
- LNK4088 警告意味着 DLL 无法实际运行
- gbengine_exports.cpp (2904 行) 作为过渡文件存放大量实现

## 架构

三阶段按序执行：
1. **Phase 1**: 为 626 个未解析符号生成正确签名的 stub 函数，消除 `/FORCE`
2. **Phase 2**: 将 gbengine_exports.cpp 中的函数移至对应模块源文件
3. **Phase 3**: 搭建 VC6 SP5 工具链，实现 CMake 双编译器切换

---

## Phase 1: 消除 /FORCE 链接

### 1.1 符号分类（626 个）

| 类别 | 数量 | 说明 |
|------|------|------|
| `__thiscall` 成员函数 | 598 | 类方法（构造/析构/普通方法） |
| `__cdecl` 自由函数 | 15 | 全局工具函数 |
| `vftable` 虚表 | 11 | 类的虚函数表 |
| `static` 静态成员 | 2 | CPK::CrcTable 等 |

### 1.2 类分布（前 15 大类）

| 类名 | 未解析数 | 说明 |
|------|----------|------|
| gbCamera | 42 | 摄像机（大部分方法） |
| gbGfxManager | 40 | 图形管理器 |
| gbMatrix4 | 37 | 4x4矩阵 |
| gbGeomNode | 29 | 几何节点 |
| gbQuaternion | 20 | 四元数 |
| gbRenderEffect | 17 | 渲染效果 |
| gbImage2D | 17 | 2D图像 |
| gbMatrixStack | 16 | 矩阵栈 |
| gbEffectMgr | 15 | 效果管理器 |
| gbTexture | 14 | 纹理基类 |
| gbDynVertBuf | 14 | 动态顶点缓冲 |
| gbAnimNodeGroup | 14 | 动画节点组 |
| CPK | 14 | CPK包文件系统 |
| gbVec3D | 13 | 3D向量 |
| gbStaticChain | 13 | 静态链表 |

### 1.3 自动生成方案

**输入**: `unresolved.txt` — 每行格式 `"demangled signature" (mangled_name)`

**生成规则**:
1. 解析 demangled signature 提取：返回类型、调用约定、类名、函数名、参数列表
2. 按类分组，每个类生成一个 stub 源文件：`src/gbengine/stubs/stub_ClassName.cpp`
3. 自由函数统一生成到 `src/gbengine/stubs/stub_globals.cpp`
4. vtable 由 C++ 编译器自动生成（只要类有 virtual 方法实现）

**函数体策略**:
- 返回 `void`: 空函数体 `{}`
- 返回 `int/bool`: `{ return 0; }`
- 返回指针: `{ return NULL; }`
- 返回 `float/double`: `{ return 0.0f; }`
- 返回对象引用: `{ static T dummy; return dummy; }` 或 `{ return *this; }`
- 构造函数/析构函数: `{}`

**vtable 处理**:
11 个 vtable 符号需要对应类至少有一个非内联虚函数定义在 stub 文件中。如果类已在其他 .cpp 中有虚函数实现，vtable 自动生成；否则需要在 stub 中提供一个占位虚函数。

### 1.4 生成工具

创建 `tools/gen_stubs.py`：
- 解析 `unresolved.txt`
- 按类分组
- 为每个类生成 `src/gbengine/stubs/stub_<ClassName>.cpp`
- 生成 `src/gbengine/stubs/stub_globals.cpp`（自由函数）
- 输出 CMakeLists.txt 片段用于包含 stubs 目录

### 1.5 CMake 变更

```cmake
# 在 gbengine 构建配置中：
file(GLOB GBENGINE_STUBS "src/gbengine/stubs/*.cpp")
target_sources(gbengine PRIVATE ${GBENGINE_STUBS})

# 移除 /FORCE:MULTIPLE
set_target_properties(gbengine PROPERTIES
    LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/src/gbengine/gbengine.def\""
)
```

### 1.6 验证

- 编译无 `/FORCE` 且无 LNK2001/LNK2019 错误
- 所有 1020 个符号均成功导出（用 `dumpbin /exports` 验证）
- 无 LNK4088 警告

---

## Phase 2: gbengine_exports.cpp 归位

### 2.1 现有计划

已有详细归位计划（按目标文件分组的 236 个函数移动方案），核心策略：
- 按类/模块将函数移至对应 .cpp 文件
- 每批移动后编译验证
- 移完后删除 gbengine_exports.cpp

### 2.2 目标文件映射

| 目标文件 | 函数数 | 类 |
|----------|--------|-----|
| gbMath.cpp | 129 | gbMatrix4, gbQuaternion, gbRotMatrix, gbVec3D, gbMatrixStack, gbOBBox, gbAABBox, gbSphere, gbPlane, gbRay, BEZIER |
| gbMisc.cpp | 24 | gbColorFlt, gbColorQuad, gbNameVarBuf, gbTimeCounter, gbPixelFormat |
| gbParticle.cpp | 21 | gbAnimNodeGroup, gbEmitterData, gbEmitterSquare, gbParticleUnit |
| gbVisNode.cpp | 12 | gbVolModNode, gbVolumeModifier, gbLightObj |
| gbCamera.cpp | 9 | gbCamera, gbCamControler, gbCamQuakeControl, gbCamSpringControl |
| gbVFileSystem.cpp | 7 | gbVTextFile |
| gbTexture.cpp | 6 | gbTexture_D3D, gbTextureArray |
| gbGfxManager.cpp | 5 | gbEffectMgr, gbGfxManager_D3D, gbGfxManager, gbRenderEffect, gbImage2DInfo |
| gbGeomNode.cpp | 5 | gbGeomNode |
| gbSceneGraph.cpp | 2 | gbSceneGraph, gbLightObj |

### 2.3 步骤

1. 逐模块搬移（先大后小：gbMath → gbMisc → gbParticle → ...）
2. 每移完一个模块，编译验证
3. 最终删除 gbengine_exports.cpp，从 CMakeLists 的特殊编译选项中移除

---

## Phase 3: VC6 SP5 工具链搭建

### 3.1 需要提取的文件

从 VC6 SP5 安装媒体中提取：

**编译器核心** (`tools/vc6/bin/`):
- `cl.exe` — C/C++ 编译器前端
- `c1.dll` — C 编译器后端
- `c1xx.dll` — C++ 编译器后端
- `c2.dll` — 代码生成器/优化器
- `link.exe` — 链接器
- `lib.exe` — 库管理器
- `mspdb60.dll` — PDB 支持
- `msobj10.dll` / `msdis100.dll` — 目标文件支持

**标准头文件** (`tools/vc6/include/`):
- C/C++ 标准库头文件
- ATL/MFC 头文件（如果用到）
- Windows SDK 兼容头文件子集

**标准库** (`tools/vc6/lib/`):
- `libc.lib` / `libcmt.lib` / `msvcrt.lib`
- `libcp.lib` / `libcpmt.lib` / `msvcprt.lib`
- `oldnames.lib`
- `uuid.lib`

**Platform SDK 子集** (`tools/vc6/platformsdk/`):
- Windows 头文件（windows.h 等）
- DirectX 9 头文件和 lib（来自 DirectX SDK Summer 2003）

### 3.2 提取方式

VC6 安装包通常是 .cab 压缩格式或 InstallShield 格式：
- 使用 7-Zip 解压 .cab 文件
- 从已安装的 VC6 SP5 环境直接复制（如果有访问权限）
- 提取后验证 `cl.exe /?` 输出版本 12.00.8804（VC6 SP5）

### 3.3 CMake 集成

创建 `cmake/VC6Toolchain.cmake`：

```cmake
# VC6 SP5 Toolchain File
set(CMAKE_C_COMPILER "${CMAKE_SOURCE_DIR}/tools/vc6/bin/cl.exe")
set(CMAKE_CXX_COMPILER "${CMAKE_SOURCE_DIR}/tools/vc6/bin/cl.exe")
set(CMAKE_LINKER "${CMAKE_SOURCE_DIR}/tools/vc6/bin/link.exe")
set(CMAKE_AR "${CMAKE_SOURCE_DIR}/tools/vc6/bin/lib.exe")

# Include and lib paths
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/tools/vc6/include")
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/tools/vc6/include")
set(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/tools/vc6/lib")

# VC6-specific flags (matching original build)
set(CMAKE_C_FLAGS_INIT "/nologo /W3")
set(CMAKE_CXX_FLAGS_INIT "/nologo /W3 /GX")
```

使用方式：
```bash
cmake -B build_vc6 -DBUILD_TARGET=gbengine -DCMAKE_TOOLCHAIN_FILE=cmake/VC6Toolchain.cmake
cmake --build build_vc6 --config Release
```

### 3.4 双编译器切换

- 默认（无 toolchain file）：使用当前系统 MSVC（开发调试用）
- `-DCMAKE_TOOLCHAIN_FILE=cmake/VC6Toolchain.cmake`：VC6 精确匹配编译
- 两者共存，互不影响

---

## 约束和风险

1. **Phase 1 风险**: 复杂模板类型的 demangle 可能不完美 → 手动修正个别签名
2. **Phase 2 风险**: 移动函数时可能触发重复定义 → 逐步移动，每步验证
3. **Phase 3 风险**: VC6 工具链文件获取（需要用户提供安装包）→ 用户需自行准备 VC6 SP5 安装媒体或已安装目录
4. **vtable 生成**: 需确保含虚函数的类在某个 .cpp 中有非内联虚函数定义

## 成功标准

- [ ] `cmake --build` 无 `/FORCE` 且无链接错误
- [ ] `dumpbin /exports gbengine.dll` 显示 1020 个导出
- [ ] gbengine_exports.cpp 文件不存在
- [ ] CMakeLists.txt 无 `/Ob0` 特殊处理
- [ ] VC6 工具链可成功编译至少 topo.dll
- [ ] 双编译器配置可切换
