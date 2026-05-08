# gbengine.dll 反编译进度

## 概要

| 指标 | 数值 |
|------|------|
| 编译器 | MSVC 6.0 SP5 (`/O2 /Ob2 /GF /Gy /Zp4 /GX`) |
| DLL 总函数 (IDA 识别) | 3742 |
| 引擎自身代码 | ~1396 |
| D3DX9 静态库 (不需实现) | ~1909 |
| CRT/编译器运行时 (不需实现) | ~364 |
| 已命名函数 | 1360 (36%) |
| 未命名函数 (sub_) | 2382 (64%) |
| 引擎范围 sub_ (0x10000000-0x10031FFF) | 295 |
| 源文件数 | 54 |
| 编译通过文件 | **54/54 (100%)** |
| DLL 链接 | **成功 (925KB, 1020 exports)** |
| **已实现函数 (非空函数体)** | **~794** |
| **引擎覆盖率** | **~78.8%** |
| IDA已命名但未实现 | 167 |
| 引擎范围 sub_ 未实现 | 295 |
| 完全匹配函数 | **~485** |
| 最后更新 | 2026-05-08 |

## IDA 导出数据统计 (2026-05-08 更新)

### 函数分布 (按地址范围)

| 范围 | 数量 | 内容 |
|------|------|------|
| 0x10000000 - 0x10031FFF | ~1396 | 引擎代码 (需要实现) |
| 0x10032000 - 0x100DFFFF | ~1909 | D3DX9.LIB 静态链接 (不需实现) |
| 0x100E0000 - 0x100FFFFF | ~364 | CRT运行时 + 编译器生成 (不需实现) |

### 调用约定统计

| 约定 | 数量 | 占比 |
|------|------|------|
| __thiscall (C++方法) | 2154 | 57.5% |
| __stdcall (Windows API) | 828 | 22.1% |
| __cdecl (C函数) | 393 | 10.5% |
| 其他 | 290 | 7.7% |
| __userpurge (自定义) | 78 | 2.1% |

### 按类统计 (已命名函数 Top 25)

| 类名 | 函数数 | 类名 | 函数数 |
|------|--------|------|--------|
| gbCamera | 42 | gbAudioManager | 28 |
| gbGfxManager | 38 | gbVisNode | 25 |
| gbMatrix4 | 36 | CIniFile | 20 |
| gbActor | 31 | gbQuaternion | 19 |
| gbGeomNode | 30 | gbVFileSystem | 19 |
| CPK | 30 | gbVec3D | 17 |
| gbRenderEffect | 16 | gbDynVertBuf | 16 |
| gbSound3DNode | 16 | gbParticleEffect | 16 |
| gbImage2D | 15 | gbAnimNodeGroup | 15 |
| gbBaseMesh | 15 | gbMatrixStack | 14 |
| gbEffectMgr | 14 | gbSceneGraph | 13 |
| gbVertPoolMgr | 13 | gbTexture | 13 |
| gbStaticChain | 13 | | |

---

## 全文件二进制匹配进度

| 文件 | 总函数 | 完全匹配 | 平均匹配率 | 状态 |
|------|--------|----------|-----------|------|
| gbVec3D.cpp | 16 | **16** | **100%** | DONE |
| gbColorFlt.cpp | 3 | **3** | **100%** | DONE |
| gbTextureArray.cpp | 5 | **5** | **100%** | DONE |
| gbImage2DInfo.cpp | 1 | **1** | **100%** | DONE |
| gbSoundNode.cpp | 26 | **21** | 86.3% | GOOD |
| gbGfxManager.cpp | 44 | **33** | 82.1% | GOOD |
| gbChain.cpp | 61 | **45** | 82.1% | GOOD |
| gbRenderEffect.cpp | 16 | **12** | 78.1% | GOOD |
| gbEffectMgr.cpp | 8 | **6** | 77.0% | GOOD |
| gbAABBox.cpp | 3 | **2** | 76.0% | GOOD |
| gbMatrixStack.cpp | 14 | **10** | 75.3% | GOOD |
| gbResManager.cpp | 20 | **10** | 69.1% | WIP |
| gbQuaternion.cpp | 19 | **11** | 67.9% | WIP |
| gbMatrix4.cpp | 31 | **16** | 67.5% | WIP |
| gbAudioManager.cpp | 56 | **34** | 66.9% | WIP |
| gbImage2D.cpp | 14 | **8** | 66.5% | WIP |
| gbMesh.cpp | 35 | **20** | 66.3% | WIP |
| gbVisNode.cpp | 35 | **15** | 66.2% | WIP |
| gbRotMatrix.cpp | 7 | **4** | 65.7% | WIP |
| gbVFileSystem.cpp | 83 | **43** | 64.1% | WIP |
| gbCamera.cpp | 53 | **26** | 62.1% | WIP |
| gbGeomNode.cpp | 30 | **14** | 61.2% | WIP |
| gbGlobals.cpp | 18 | **8** | 57.3% | WIP |
| gbPrintFont.cpp | 17 | **8** | 56.8% | WIP |
| gbLightObj.cpp | 8 | **4** | 56.0% | WIP |
| gbNameVarBuf.cpp | 1 | 0 | 55.6% | WIP |
| gbSceneGraph.cpp | 15 | **7** | 55.4% | WIP |
| gbMisc.cpp | 41 | **15** | 52.9% | WIP |
| gbActor.cpp | 34 | **16** | 52.3% | WIP |
| gbWeather.cpp | 18 | **7** | 50.5% | WIP |
| gbTexture.cpp | 24 | **10** | 49.8% | WIP |
| gbVertPool.cpp | 44 | **14** | 46.2% | WIP |
| gbParticle.cpp | 67 | **22** | 46.1% | WIP |
| gbMath_extra.cpp | 5 | **2** | 44.5% | WIP |
| gbVTextFile.cpp | 4 | 0 | 42.7% | WIP |
| gbOBBox.cpp | 9 | **2** | 42.3% | WIP |
| gbPixelFormat.cpp | 6 | **2** | 40.8% | WIP |
| gbVolModNode.cpp | 3 | **1** | 39.1% | WIP |
| BEZIER.cpp | 8 | **2** | 35.1% | WIP |
| gbPlane.cpp | 3 | 0 | 23.8% | WIP |
| gbRay.cpp | 10 | 0 | 21.5% | WIP |
| gbSphere.cpp | 5 | 0 | 18.5% | WIP |
| gbDynVertBuf.cpp | 5 | 0 | 12.5% | WIP |
| gbGfxManager_D3D.cpp | 1 | 0 | 3.7% | WIP |
| CPK.cpp | 1 | 0 | 0.5% | WIP |

---

## 缺口分析 (2026-05-08 IDA全量导出后)

### 高优先级：关键未命名函数 (需重命名+实现)

| 地址 | 大小 | 推断名称 | 所属类 | 优先级 |
|------|------|----------|--------|--------|
| 0x10011C60 | 3222B | LoadFromStream | gbBaseMesh | HIGH |
| 0x10008420 | 1462B | LoadFromIni | gbActor | HIGH |
| 0x10023A90 | 1315B | Flush | gbPrintFont | HIGH |
| 0x1001A790 | 1208B | CreateDevice | gbGfxManager_D3D | HIGH |
| 0x1000A100 | 1083B | LoadBones | gbAnimNodeGroup | HIGH |
| 0x100064E0 | 1028B | BuildIndexBuffer | gbGeomNode | HIGH |
| 0x10007DA0 | 923B | LoadSkeleton | gbActor | HIGH |
| 0x10008140 | 735B | LoadMaterials | gbActor | HIGH |
| 0x1000BC50 | 485B | LoadAnimData | gbAnimNodeGroup | HIGH |
| 0x10012BA0 | 788B | LoadMaterial | gbGeomNode | HIGH |
| 0x1002E850 | 158B | gbErrorBox | 全局 | HIGH |
| 0x1002E820 | 44B | gbMessageBox | 全局 | HIGH |
| 0x1002E900 | 35B | gbGetTime | 全局 | HIGH |
| 0x10020D20 | 97B | gbGetVertexSize | 全局 | HIGH |
| 0x100275E0 | 62B | gbRandRange | 全局 | MED |
| 0x100276A0 | 100B | gbFloatToInt | 全局 | MED |
| 0x10017000 | 199B | ReleaseResources | gbGfxManager_D3D | HIGH |
| 0x1001BB10 | 490B | ConvertPixelFormat | gbTexture_D3D | MED |
| 0x100172F0 | 1413B | EnumAdapterModes | gbGfxManager_D3D | MED |
| 0x10017BD0 | 961B | FindBestMode | gbGfxManager_D3D | MED |

### 高优先级：已命名但未实现的函数

| 地址 | 大小 | 函数名 | 说明 |
|------|------|--------|------|
| 0x100102C0 | 1478B | gbGeomNode::LoadFromFile | 加载.pol/.cvd几何文件 |
| 0x10028F80 | 1067B | gbIntersectTriangle | 射线-三角形碰撞 |
| 0x100135A0 | 735B | gbLoadLightFile | 加载灯光场景 |
| 0x1002F170 | 580B | gbChangeDispMode | 切换显示模式 |
| 0x1002F690 | 332B | gbGetCPU_MHZ | CPU频率检测 |
| 0x1002FD70 | 283B | gbTimeCounterInit | 计时器初始化 |
| 0x10031890 | 277B | ProfileEnd | 性能剖析结束 |
| 0x10031780 | 258B | ProfileBegin | 性能剖析开始 |
| 0x1002FB90 | 206B | gbstricmp | 不区分大小写字符串比较 |
| 0x1002F530 | 193B | gbEnableSystemKeys | 启用/禁用系统键 |

### 中优先级：Stub 函数 (已有文件但函数体为空)

共 42 个函数当前为空/严重不完整：

| 文件 | Stub数 | 主要缺失 |
|------|--------|----------|
| gbParticle.cpp | 13 | LoadFromFile、构造/拷贝、Attach |
| gbActor.cpp | 5 | ActorMgr初始化/析构、Attach |
| gbVertPool.cpp | 6 | VertPoolMgr的Del/New/Get系列 |
| gbMisc.cpp | 3 | ProfileBegin/End/Dump |
| gbGfxManager.cpp | 3 | 构造函数、EffectMgr拷贝/赋值 |
| gbTexture.cpp | 2 | LoadTexture、LoadFromImage2D |
| gbVFileSystem.cpp | 2 | CPK::LoadFile、CPK::Open |
| gbWeather.cpp | 2 | gbRain/gbSnow拷贝构造 |
| gbLightObj.cpp | 2 | 拷贝构造、Init |
| gbVisNode.cpp | 2 | gbVolModNode拷贝/默认构造 |
| gbGeomNode.cpp | 2 | 拷贝构造、operator= |
| gbSceneGraph.cpp | 1 | 析构函数 |
| gbAudioManager.cpp | 1 | 构造函数(Miles初始化) |

### 低优先级：大量简单函数 (operator=、拷贝构造、析构)

167个已命名未实现函数中，85个(51%)为 operator= 或拷贝构造函数。
这些多为编译器生成的 memcpy 模式，可批量处理。

---

## Stub 函数详细清单

### gbMisc.cpp (3 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| ProfileBegin(char*) | 16B | 258B | 空实现，需要全局数组遍历逻辑 |
| ProfileEnd(char*) | 16B | 277B | 空实现，需要计时结算逻辑 |
| ProfileDumpOutputToFile(char*) | 16B | 79B | 空实现，需要 fopen+fprintf |

### gbGfxManager.cpp (3 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbGfxManager::gbGfxManager(ctor) | 320B | 394B | 部分实现，缺少完整初始化 |
| gbEffectMgr::gbEffectMgr(copy) | 32B | 148B | 拷贝构造函数逻辑不完整 |
| gbEffectMgr::operator= | 32B | 191B | 赋值运算符逻辑不完整 |

### gbParticle.cpp (13 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbPartEmitter::gbPartEmitter(void) | 176B | 520B | 构造函数大部分初始化缺失 |
| gbParticleEffect::gbParticleEffect(copy) | 112B | 541B | 拷贝构造逻辑缺失 |
| gbAnimNodeGroup::Attach(void) | 16B | 68B | 空实现 |
| gbParticleEffect::Attach(gbRenderEffect*) | 16B | 346B | 空实现 |
| gbAnimNodeGroup::Clone(void) | 112B | 319B | 大部分逻辑缺失 |
| gbParticleGroup::CreateOneParticle(gbEmitterData*) | 400B | 747B | 部分实现 |
| gbAnimNodeGroup::LoadFromFile(char*) | 176B | 307B | 部分实现 |
| gbPartEmitter::LoadFromFile(gbVFile*) | 304B | 1486B | 大部分字段读取缺失 |
| gbPartGroupParam::LoadFromFile(gbVFile*) | 704B | 1414B | 部分实现 |
| gbAnimNodeGroup::Reset(void) | 32B | 103B | 空实现 |
| gbAnimNodeGroup::SetPriority(int) | 16B | 85B | 空实现 |
| gbAnimNodeGroup::gbAnimNodeGroup(gbGfxManager*) | 80B | 145B | 部分初始化缺失 |
| gbParticleUnit::gbParticleUnit(copy) | 64B | 144B | 拷贝逻辑缺失 |

### gbActor.cpp (5 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbActorMgr::gbActorMgr(gbGfxManager*) | 32B | 125B | 空实现 |
| gbActorMgr::~gbActorMgr(void) | 16B | 95B | 空实现 |
| gbActor::Attach(gbRenderEffect*) | 16B | 81B | 空实现 |
| gbActor::~gbActor(void) | 64B | 162B | 部分实现 |
| gbActorMgr::LoadActorFile(char*) | 192B | 337B | 部分实现 |

### gbVertPool.cpp (6 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbVertPoolMgr::DelIndexBubble(gbIndexBubble*) | 32B | 85B | 空实现 |
| gbVertPoolMgr::DelSrcVertBub(gbVertexBubble*) | 32B | 145B | 空实现 |
| gbVertPoolMgr::DelVertexBubble(gbVertexBubble*) | 32B | 144B | 空实现 |
| gbVertPoolMgr::GetDynVertBuf(uint) | 16B | 121B | 空实现 |
| gbVertPoolMgr::NewSrcVertBub(uint,int) | 32B | 185B | 空实现 |
| gbVertPoolMgr::NewVertexBubble(uint,int) | 128B | 182B | 部分实现 |

### gbWeather.cpp (2 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbRain::gbRain(copy) | 32B | 117B | 空实现 |
| gbSnow::gbSnow(copy) | 48B | 129B | 空实现 |

### gbTexture.cpp (2 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbTexture::LoadTexture(int) | 16B | 443B | 空实现 |
| gbTexture::LoadFromImage2D(gbImage2D*) | 64B | 269B | 空实现 |

### gbVFileSystem.cpp (2 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| CPK::LoadFile(void*,char const*) | 112B | 744B | 大部分逻辑缺失 |
| CPK::Open(char const*) | 720B | 1336B | 部分实现 |

### gbSceneGraph.cpp (1 stub)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbSceneGraph::~gbSceneGraph(void) | 32B | 101B | 空实现 |

### gbLightObj.cpp (2 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbLightObj::gbLightObj(copy) | 48B | 218B | 空实现 |
| gbLightObj::Init(LIGHT_TYPE) | 48B | 123B | 空实现 |

### gbVisNode.cpp (2 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbVolModNode::gbVolModNode(copy) | 64B | 188B | 空实现 |
| gbVolModNode::gbVolModNode(void) | 64B | 106B | 部分实现 |

### gbGeomNode.cpp (2 stubs)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbGeomNode::gbGeomNode(copy) | 144B | 356B | 部分实现 |
| gbGeomNode::operator=(copy) | 80B | 336B | 空实现 |

### gbAudioManager.cpp (1 stub)

| 函数 | compiled | original | 说明 |
|------|----------|----------|------|
| gbAudioManager::gbAudioManager(ctor) | 400B | 675B | 部分实现，Miles Sound System 初始化缺失 |

---

## 实施计划 (2026-05-08 修订)

### 精确范围

经过系统分析，需要实现的 gbengine 内部函数:
- **总计: 308 个函数, 86.2 KB**
- 排除: Concurrency/std/type_info (CRT库, 450+函数), D3DX (1367函数), 编译器生成(42个)

### Phase 1: 填充已有文件 Stub (42个函数)

**目标**: 把已有 .cpp 文件中的空/不完整函数补全
- gbParticle.cpp: 13 stubs (LoadFromFile、构造、Attach)
- gbVertPool.cpp: 6 stubs (Del/New/Get系列)
- gbActor.cpp: 5 stubs (ActorMgr、Attach、析构)
- gbMisc.cpp: 3 stubs (Profile系列)
- gbGfxManager.cpp: 3 stubs
- gbTexture.cpp: 2 stubs (LoadTexture, LoadFromImage2D)
- gbVFileSystem.cpp: 2 stubs (CPK::Open, CPK::LoadFile)
- 其他: 8 stubs (各文件1-2个)

### Phase 2: gbGfxManager_D3D (29个函数, 9.4KB)

**目标**: D3D9 渲染核心实现
- CreateDevice, ResetDevice, Present
- SetLight, SetMaterial, DrawIndexedPrimitive
- SetFrustum, SetOrtho, SetViewport
- OnLostDevice, OnResetDevice

### Phase 3: gbLightObj (34个函数, 9.2KB)

**目标**: 灯光系统完整实现
- LoadFromFile, Init, Apply
- 各种灯光类型的处理方法

### Phase 4: CIniFile (38个函数, 11.6KB)

**目标**: 配置文件读写系统
- Open, Close, ReadString, ReadInt, ReadFloat
- Section/Key 管理

### Phase 5: (global) 引擎函数 (74个, 23.5KB)

**目标**: 各种全局工具函数
- 图像格式加载 (TGA, HDR, DDS 解码)
- gbIntersectTriangle, gbCrc32Compute
- ProfileBegin/End, gbChangeDispMode
- 其他杂项辅助函数

### Phase 6: 中优先级模块 (80+个函数, ~25KB)

- CPK (20个) - 文件包系统
- gbStaticMesh (10个) - 网格渲染
- gbImage2D (5个) - 图像加载
- gbPrintFontMgr (11个) - 字体管理
- gbActor (7个) - 角色动画
- gbTexture_D3D (12个) - 纹理D3D实现
- gbVertexPool (8个) - 顶点缓冲
- BEZIER (2个) - 贝塞尔曲线
- gbParticleEffect (4个) - 粒子效果
- CArrayList (8个) - 容器类

---

## 匹配瓶颈分类

### 1. Stub/未实现 (难度：中，可补全)

约 42 个函数当前为空或严重不完整，补全后可直接提升匹配数。
重点目标：ProfileBegin/End (小函数)、gbTexture::LoadTexture、gbVertPoolMgr 系列。

### 2. 寄存器分配差异 (难度：极高，不可控)

VC6寄存器分配器的内部启发式无法从源码影响。
影响范围：几乎所有 SIZE_OK 但未完全匹配的函数。

### 3. FPU指令调度差异 (难度：高)

VC6 /O2 的 FPU 调度器重排 fld/fmul/fadd/fstp 顺序。
可能修复：拆分/合并子表达式、引入临时变量。

### 4. 函数内联差异 (难度：高，但可解)

原始 /Ob2 编译内联了部分小函数（Normalize, CrossProduct, GetMatrix等）。
修复方向：手动内联（已对 GetSphere/Invert 成功验证）。

### 5. 栈帧/调用约定差异 (难度：中)

VC6 对栈帧大小的优化、参数传递方式有时与我们的代码生成不一致。

---

## 编译选项

```
CL.EXE /c /O2 /Ob2 /Oi /GF /Gy /Zp4 /GX /Fo<output.obj> <source.cpp>
```

| 标志 | 作用 | 确认方式 |
|------|------|----------|
| /O2 | 速度优化 | 必须，原始使用 |
| /Ob2 | 自动内联 | IDA分析确认有内联函数 |
| /Oi | 启用内建函数 | 匹配 memcpy/strlen 等的内联展开 |
| /GF | 字符串池 | 减少重复常量 |
| /Gy | 函数级链接 | COMDAT节，每函数独立节 |
| /Zp4 | 4字节对齐 | gbGfxManager偏移验证确认 |
| /GX | C++异常 | NewMesh中SEH帧 |

## 验证命令

```bash
# 批量对比所有文件
for f in src/gbengine/*.cpp; do python tools/gbengine_compare.py --compile "$f" --all; done

# 对比指定文件
python tools/gbengine_compare.py --compile src/gbengine/gbMatrix4.cpp --all

# 对比指定函数
python tools/gbengine_compare.py --compile src/gbengine/gbMatrix4.cpp --func "Transpose"
```
