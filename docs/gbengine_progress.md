# gbengine.dll 反编译进度

## 概要

| 指标 | 数值 |
|------|------|
| 编译器 | MSVC 6.0 SP5 (`/O2 /Ob2 /GF /Gy /Zp4 /GX`) |
| DLL 总函数 (IDA 识别) | 3746 |
| 其中已命名 (导出+已恢复) | 1362 |
| 其中未命名 (sub_) | 2384 |
| 源文件数 | 54 |
| 编译通过文件 | **54/54 (100%)** |
| DLL 链接 | **成功 (925KB, 1020 exports)** |
| 当前可比对函数 (已命名) | ~940 |
| 完全匹配函数 | **~485** |
| 最后更新 | 2026-05-08 |

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

### 新增可比对文件 (IDA 重命名后)

| 文件 | 函数数 | 匹配 | 说明 |
|------|--------|------|------|
| gbGfxManager_D3D.cpp | 9 | **7** (88.8%) | 重命名 Present/SetFog/SetLight 等虚函数 |
| gbBladeMgr.cpp | 2 | **2** (100%) | 重命名 Reset/GetLastBladePos |

### 仍无匹配符号文件 (7个)

| 文件 | 原因 | 下一步 |
|------|------|--------|
| gbBaseMesh.cpp | 函数太短(16B)多重匹配 | 需上下文/交叉引用定位 |
| gbCameraControl.cpp | 编译后无外部符号 | 全部被内联或为空 |
| gbDropGroup.cpp | 函数太短多重匹配 | 需上下文定位 |
| gbIndexBubble.cpp | 编译后无外部符号 | 全部被内联或为空 |
| gbPrintFontMgr.cpp | 编译后无外部符号 | 全部被内联或为空 |
| gbTimeCounter.cpp | 编译后无外部符号 | 全部被内联或为空 |
| gbVertPoolMgr.cpp | 编译后无外部符号 | 全部被内联或为空 |

### 未命名内部函数 (sub_) — 待恢复

DLL 中共 2384 个 sub_ 函数尚未识别。这些是非导出的内部函数，需要：
1. **字节匹配恢复**: 用编译后 .obj 字节搜索 DLL 定位地址，应用 mangled name
2. **交叉引用分析**: 从已知调用者推断被调用 sub_ 的身份
3. **签名推断**: 根据调用约定和参数数量缩小候选范围

已恢复 16 个 (gbBladeMgr, gbGfxManager_D3D, gbVertexPool, CArrayList 等)。
歧义跳过 3 个 (SetBladeTime/SetBladeTimeScale, NewIndexPool)。
剩余 ~142 个 .obj 函数待匹配 (需降低阈值或人工确认歧义)。

---

## Stub 函数清单 (二进制对比确认未实现)

以下函数的编译输出远小于原始二进制，说明当前代码只是占位 stub，核心逻辑未实现。
判定标准: SIZE_MISMATCH 且 compiled/original < 50%，或者函数体明显为空。

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

### gbVertPool.cpp (4 stubs)

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
