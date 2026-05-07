# gbengine.dll 反编译进度

## 概要

| 指标 | 数值 |
|------|------|
| 编译器 | MSVC 6.0 SP5 (`/O2 /Ob2 /GF /Gy /Zp4 /GX`) |
| IDA 导出函数 | 1344 |
| 源文件数 | 54 |
| 编译通过文件 | **54/54 (100%)** |
| DLL 链接 | **成功 (925KB, 1020 exports)** |
| 可比对文件 | 44/54 (10个文件无匹配符号) |
| 可比对函数 | 901 |
| 完全匹配函数 | **223/901 (24.8%)** |
| 最后更新 | 2026-05-07 |

## 全文件二进制匹配进度

| 文件 | 总函数 | 完全匹配 | 平均匹配率 | 状态 |
|------|--------|----------|-----------|------|
| gbVec3D.cpp | 16 | **16** | **100%** | DONE |
| gbColorFlt.cpp | 3 | **3** | **100%** | DONE |
| gbTextureArray.cpp | 5 | **4** | 86.4% | GOOD |
| gbGfxManager.cpp | 44 | **33** | 81.1% | GOOD |
| gbAABBox.cpp | 3 | **2** | 76.0% | GOOD |
| gbRenderEffect.cpp | 16 | **10** | 74.9% | GOOD |
| gbChain.cpp | 61 | **36** | 66.9% | GOOD |
| gbMatrix4.cpp | 31 | **16** | 66.2% | GOOD |
| gbRotMatrix.cpp | 7 | **4** | 65.7% | GOOD |
| gbQuaternion.cpp | 19 | **11** | 65.6% | GOOD |
| gbResManager.cpp | 20 | **2** | 57.9% | WIP |
| gbNameVarBuf.cpp | 1 | 0 | 55.6% | WIP |
| gbGeomNode.cpp | 30 | **9** | 51.6% | WIP |
| gbImage2D.cpp | 14 | **5** | 49.1% | WIP |
| gbVisNode.cpp | 35 | **10** | 48.0% | WIP |
| gbMesh.cpp | 35 | **12** | 46.3% | WIP |
| gbMath_extra.cpp | 5 | **2** | 44.5% | WIP |
| gbEffectMgr.cpp | 8 | **1** | 42.4% | WIP |
| gbPrintFont.cpp | 17 | **4** | 39.3% | WIP |
| gbGlobals.cpp | 18 | **3** | 36.5% | WIP |
| gbVertPool.cpp | 44 | **4** | 36.1% | WIP |
| gbCamera.cpp | 53 | **9** | 35.4% | WIP |
| BEZIER.cpp | 8 | **1** | 34.6% | WIP |
| gbImage2DInfo.cpp | 1 | 0 | 31.8% | WIP |
| gbActor.cpp | 34 | **6** | 31.7% | WIP |
| gbAudioManager.cpp | 56 | **8** | 30.0% | WIP |
| gbLightObj.cpp | 8 | 0 | 29.5% | WIP |
| gbMatrixStack.cpp | 14 | **3** | 27.3% | WIP |
| gbVolModNode.cpp | 3 | 0 | 26.6% | WIP |
| gbPlane.cpp | 3 | 0 | 23.8% | WIP |
| gbSceneGraph.cpp | 15 | 0 | 22.9% | WIP |
| gbTexture.cpp | 24 | 0 | 22.3% | WIP |
| gbOBBox.cpp | 9 | 0 | 22.2% | WIP |
| gbRay.cpp | 10 | 0 | 21.6% | WIP |
| gbVFileSystem.cpp | 83 | **4** | 20.8% | WIP |
| gbVTextFile.cpp | 4 | 0 | 20.8% | WIP |
| gbWeather.cpp | 18 | **1** | 20.4% | WIP |
| gbSphere.cpp | 5 | 0 | 19.3% | WIP |
| gbParticle.cpp | 67 | **2** | 18.3% | WIP |
| gbMisc.cpp | 41 | **2** | 16.5% | WIP |
| gbDynVertBuf.cpp | 5 | 0 | 12.5% | WIP |
| gbPixelFormat.cpp | 6 | 0 | 10.0% | WIP |
| gbGfxManager_D3D.cpp | 1 | 0 | 3.7% | WIP |
| CPK.cpp | 1 | 0 | 0.5% | WIP |

### 无匹配符号文件 (10个)

这些文件编译通过但 .obj 中的 mangled name 与 IDA 索引不匹配，需要修正类名或函数签名：

| 文件 | 原因 |
|------|------|
| gbBaseMesh.cpp | 类名/虚函数签名与 IDA 不匹配 |
| gbCameraControl.cpp | 无导出函数符号 |
| gbDropGroup.cpp | 无导出函数符号 |
| gbIndexBubble.cpp | 无导出函数符号 |
| gbPrintFontMgr.cpp | 无导出函数符号 |
| gbSoundNode.cpp | 无导出函数符号 |
| gbTimeCounter.cpp | 无导出函数符号 |
| gbUIRect.cpp | mangled name 不匹配 (有1个函数但未对上) |
| gbVFile1.cpp | mangled name 不匹配 (有1个函数但未对上) |
| gbVertPoolMgr.cpp | 无导出函数符号 |

---

## 详细分析：高优先级文件

### gbVec3D.cpp — 16/16 (100%) DONE

所有函数完全匹配，无需进一步工作。

### gbColorFlt.cpp — 3/3 (100%) DONE

所有函数完全匹配，无需进一步工作。

---

### gbGfxManager.cpp — 33/44 (75%) | 平均 81.1%

#### 完全匹配 (33个)

gbGfxManager::~gbGfxManager, EnableEmissive, GetAmbientLight, GetCurTick,
GetCurTime, GetDeltaTick, GetDeltaTime, GetEffectMgr, GetEmissiveFactor,
GetFog, GetGfxCaps, GetLight, GetMatrixStack, GetPrintFont, GetPrintFontMgr,
GetResManager, GetSceneGraph, GetStatistic, GetVertPoolMgr, GetViewMatrix,
GetViewport, IdentityWorldMatrix, IsLightEnable, IsWireMode, OffsetZBuffer,
SetAmbientLight, SetCameraMatrix, SetClearParam, SetEmissiveFactor, SetFog,
SetSceneGraph, SetWireMode, gbEffectMgr::~gbEffectMgr

#### 未匹配函数 (11个)

| 函数 | 大小 | 匹配率 | 未匹配原因 |
|------|------|--------|-----------|
| gbGfxManager::gbGfxManager | 394B | 16.0% | 尺寸不符(320vs394)。缺少完整初始化 |
| gbGfxManager::BeginScene | 222B | 39.6% | FPU/整数指令交错调度不同 |
| gbGfxManager::GetTMMatrix | 265B | 43.4% | switch跳转表+虚函数调用方式不同 |
| gbGfxManager::GetWorldMatrix | 55B | 70.9% | LEA指令调度差异 |
| gbGfxManager::ClipBoundVolume | 158B | 20.9% | 虚函数调用方式不匹配 |
| gbGfxManager::NewMesh | 189B | 37.0% | 尺寸不符，缺少mesh类型分发逻辑 |
| gbEffectMgr::gbEffectMgr(void) | 12B | 0% | 12B构造函数，当前实现过于复杂 |
| gbEffectMgr::gbEffectMgr(copy) | 148B | 17.6% | 类布局/成员偏移不准确 |
| gbEffectMgr::operator= | 191B | 9.9% | 尺寸不符，逻辑推测错误 |
| gbEffectMgr::Init | 786B | 2.4% | 尺寸严重不符(128vs786)，实现过于简化 |
| gbEffectMgr::Release | 67B | 9.0% | 释放逻辑/条件检查不匹配 |

---

### gbMatrix4.cpp — 16/31 (51.6%) | 平均 66.2%

#### 完全匹配 (16个)

gbMatrix4::gbMatrix4(void), operator=, operator(), GetColumn, GetRow,
IsIdentity, LeftScale, LeftTranslate(gbVec3D&), LeftTranslate(float,float,float),
LoadIdentity, RightScale, RightTranslate(gbVec3D&), RightTranslate(float,float,float),
Rotate, SetAxisAngle(gbAxis,float), Transform(const gbVec3D*,gbVec3D*)

#### 未匹配函数 (15个)

| 函数 | 大小 | 匹配率 | 未匹配原因 | 暂时放弃原因 |
|------|------|--------|-----------|-------------|
| Invert(void) | 402B | **85.3%** | FPU操作数顺序+det存储策略(fst vs fstp) | 编译器启发式，不受源码控制 |
| Transpose(void) | 60B | **83.3%** | 寄存器ESI↔EDX系统性替换 | VC6寄存器分配器内部启发式 |
| Invert(gbMatrix4*) | 351B | **63.0%** | det存储策略：fst vs fstp | FPU寄存器分配策略 |
| SetAxisAngle(axis,cos,sin) | 143B | **35.0%** | 编译器生成更优代码（双寄存器） | 无法让编译器生成更差代码 |
| IsValid | 42B | **31.0%** | 纯寄存器分配差异 | VC6 this指针处理 |
| RightMultiply(gbQuaternion&) | 198B | **27.8%** | 临时变量初始化方式不同 | 需内联GetMatrix |
| RightMultiply(gbMatrix4&) | 126B | **23.8%** | memcpy后指针初始化调度不同 | 编译器FPU管线优化 |
| LeftMultiply | 122B | **19.7%** | 栈帧大小4字节差异 | 栈帧优化由编译器决定 |
| SetAxisAngle(gbVec3D*,float) | 73B | **16.4%** | 调用序列差异，可能部分内联 | 需分析原始内联情况 |
| Transpose(gbMatrix4*) | 44B | **15.9%** | 整数mov vs FPU传输+寄存器分配 | 双重不可控因素 |
| Transform(in,out,count) | 126B | **13.5%** | ESI保存浮点+FPU调度完全不同 | 不受源码控制 |
| IsOrthonormal | 563B | **13.0%** | 尺寸不符，原始内联Normalize+CrossProduct | 需手动内联，工作量大 |
| Transform(verts,count) | 116B | **12.1%** | 整数寄存器传输float优化路径 | 无法从源码触发 |
| MakeMatrix | 307B | **8.8%** | 尺寸不符，原始内联CrossProduct+Normalize | 需手动内联 |
| Transform_W | 185B | **3.2%** | 循环结构+FPU序列完全不同 | 需分析原始实现 |

---

### gbQuaternion.cpp — 11/19 (57.9%) | 平均 65.6%

#### 完全匹配 (11个)

gbQuaternion::gbQuaternion(void), GetAxisAngle, GetMatrix, GetVec3D,
Inverse, IsUnit, IsValid, Magnitude, Normalize, SetUnit, SetVec3D

#### 未匹配函数 (8个)

| 函数 | 大小 | 匹配率 | 未匹配原因 |
|------|------|--------|-----------|
| Slerp | 320B | 49.4% | FPU sin/cos/acos调度顺序不同 |
| SetAxisAngle | 52B | 42.3% | sin/cos FPU操作顺序差异 |
| SetMatrix | 326B | 17.5% | 条件分支+数组索引方式不同 |
| SetTwoVector | 248B | 12.1% | 尺寸不符，原始内联CrossProduct+Normalize |
| RotateVector | 158B | 9.5% | 尺寸不符，原始内联了旋转计算 |
| SetYawPitchRoll | 216B | 9.3% | 原始内联了SetAxisAngle |
| IsNormal | 35B | 5.7% | Magnitude返回值处理方式不同 |
| MultiplyBy | 234B | 0.9% | 尺寸严重不符，乘法展开形式不同 |

---

### gbChain.cpp — 36/61 (59.0%) | 平均 66.9%

简单的链表/树操作。36个完全匹配的函数多为简短的节点操作（insert/remove/iterate）。
未匹配函数主要是较复杂的排序和遍历操作。

### gbRenderEffect.cpp — 10/16 (62.5%) | 平均 74.9%

渲染效果管理器。已匹配的多为简单的状态设置函数。
未匹配函数涉及D3D状态管理和着色器切换逻辑。

### gbRotMatrix.cpp — 4/7 (57.1%) | 平均 65.7%

旋转矩阵类。已匹配：LoadIdentity, Rotate(in,out), 构造函数。
未匹配：IsOrthonormal(内联问题), IsValid(寄存器分配), 部分Rotate变体。

---

## 匹配瓶颈分类

### 1. 寄存器分配差异 (难度：极高，不可控)

VC6寄存器分配器的内部启发式无法从源码影响。
影响范围：几乎所有未完全匹配的函数都有此问题的成分。

### 2. FPU指令调度差异 (难度：高)

VC6 /O2 的 FPU 调度器重排 fld/fmul/fadd/fstp 顺序以减少管线延迟。
可能修复：拆分/合并子表达式、引入临时变量。

### 3. 函数内联差异 (难度：高，但可解)

原始 /Ob2 编译内联了部分小函数（Normalize, CrossProduct, GetMatrix等）。
修复方向：手动内联（已对 Invert 成功验证，从 2.2% 提升到 85.3%）。

### 4. 实现逻辑不完整 (难度：中)

许多文件的实现是 stub 或推测性代码，与原始逻辑不一致。
修复方向：参考 IDA 反汇编补全实现。

### 5. 栈帧/调用约定差异 (难度：中)

VC6 对栈帧大小的优化、参数传递方式有时与我们的代码生成不一致。

---

## 编译选项

```
CL.EXE /c /O2 /Ob2 /GF /Gy /Zp4 /GX /Fo<output.obj> <source.cpp>
```

| 标志 | 作用 | 确认方式 |
|------|------|----------|
| /O2 | 速度优化 | 必须，原始使用 |
| /Ob2 | 自动内联 | IDA分析确认有内联函数 |
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
