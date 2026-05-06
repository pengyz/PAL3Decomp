# gbengine.dll 反编译进度

## 概要

| 指标 | 数值 |
|------|------|
| 编译器 | MSVC 6.0 SP5 (cl.exe 12.00.8804) |
| IDA 导出函数 | 1344 |
| 源文件数 | 55 (删除 gbengine.cpp, gbMath.cpp) |
| 编译通过文件 | **55/55 (100%)** |
| DLL 链接 | **成功 (925KB, 1020 exports)** |
| 验证函数总数 | 680+ |
| 完全匹配函数 | **~170** |
| 剩余 STUB 函数 | 120 |
| 最后更新 | 2026-05-07 |

## 编译选项

```
CL.EXE /c /O2 (后续可能需要 /Ob1 /GF /Gy 等微调)
```

## 按文件进度

| 文件 | 总函数 | 匹配 | 匹配率 | 状态 |
|------|--------|------|--------|------|
| gbColorFlt.cpp | 3 | 3 | 100% | DONE |
| gbVec3D.cpp | 16 | 12 | 75% | WIP (93.1% avg) |
| gbAABBox.cpp | 3 | 2 | 66.7% | WIP (76% avg) |
| gbQuaternion.cpp | 19 | 8 | 42.1% | WIP (66.7% avg) |
| gbRotMatrix.cpp | 7 | 4 | 57.1% | WIP (65.7% avg) |
| BEZIER.cpp | 8 | 1 | 12.5% | WIP (34.2% avg) |
| gbMatrix4.cpp | 31 | 11 | 35.5% | WIP (52.6% avg) |
| gbImage2D.cpp | 15 | 5 | 33.3% | |
| gbNameVarBuf.cpp | 9 | 2 | 22.2% | |
| gbPrintFont.cpp | 17 | 4 | 23.5% | |
| gbMatrixStack.cpp | 14 | 3 | 21.4% | |
| gbChain.cpp | 61 | 41 | 67.2% | WIP |
| gbBaseMesh.cpp | 6 | 1 | 16.7% | |
| gbAudioManager.cpp | 56 | 7 | 12.5% | |
| gbTexture.cpp | 40 | 5 | 12.5% | |
| gbWeatherEffects.cpp | 8 | 1 | 12.5% | |
| gbVolModNode.cpp | 9 | 1 | 11.1% | |
| gbResManager.cpp | 20 | 9 | 45% | WIP |
| gbDynVertBuf.cpp | 13 | 1 | 7.7% | 6 funcs implemented |
| gbEffectMgr.cpp | 14 | 1 | 7.1% | |
| CPK.cpp | 16 | 1 | 6.2% | |
| gbWeather.cpp | 18 | 1 | 5.6% | |
| gbParticle.cpp | 66 | 1 | 1.5% | |
| gbAABBox.cpp | 3 | 2 | 66.7% | |
| gbCamera.cpp | 52 | 9 | 17.3% | |
| gbCameraControl.cpp | 8 | 0 | 0% | |
| gbDropGroup.cpp | 3 | 0 | 0% | |
| gbGlobals.cpp | 10 | 0 | 0% | |
| gbImage2DInfo.cpp | 2 | 0 | 0% | |
| gbIndexBubble.cpp | 1 | 0 | 0% | |
| gbLightObj.cpp | 10 | 0 | 0% | |
| gbOBBox.cpp | 9 | 0 | 0% | |
| gbPixelFormat.cpp | 7 | 0 | 0% | |
| gbPlane.cpp | 3 | 0 | 0% | |
| gbPrintFontMgr.cpp | 1 | 0 | 0% | |
| gbRay.cpp | 10 | 0 | 0% | |
| gbSoundNode.cpp | 2 | 0 | 0% | |
| gbSphere.cpp | 5 | 0 | 0% | |
| gbTextureArray.cpp | 5 | 0 | 0% | |
| gbTexture_D3D.cpp | 5 | 0 | 0% | |
| gbTimeCounter.cpp | 3 | 0 | 0% | |
| gbUIRect.cpp | 3 | 0 | 0% | |
| gbVFile1.cpp | - | 0 | - | 无匹配导出函数 |
| gbVTextFile.cpp | 8 | 0 | 0% | |
| gbActor.cpp | 34 | 5 | 14.7% | |
| gbGeomNode.cpp | 26 | 0 | 0% | |
| gbGfxManager.cpp | 40 | - | - | 编译通过 |
| gbGfxManager_D3D.cpp | 1 | 0 | 0% | 编译通过 |
| gbMesh.cpp | 40 | 3 | 7.5% | |
| gbMisc.cpp | 50 | 2 | 4% | |
| gbRenderEffect.cpp | 14 | - | - | 全部实现, 编译通过 |
| gbSceneGraph.cpp | 23 | 0 | 0% | |
| gbVertPool.cpp | 44 | 2 | 4.5% | |
| gbVertPoolMgr.cpp | 1 | 0 | 0% | |
| gbVFileSystem.cpp | 87 | 4 | 4.6% | |
| gbVisNode.cpp | 36 | 2 | 5.6% | 0 STUBs remain |

## 已匹配函数明细

### BEZIER.cpp (5/8 = 62.5%)

| 函数 | 大小 | 状态 | 备注 |
|------|------|------|------|
| BEZIER::BEZIER(gbVec3D*) | 50 | OK | 循环清零 ctrlPt + memcpy |
| BEZIER::BEZIER(void) | 47 | OK | 循环清零 + memset + dirty=0 |
| BEZIER::~BEZIER() | - | N/A | 析构函数未导出 |
| BEZIER::operator= | 81 | FAIL | 两循环结构对但寄存器分配不同 |
| BEZIER::GetControlPt | 4 | OK | lea eax,[ecx+16]; ret |
| BEZIER::SetControlPt | 27 | OK | 无 NULL 检查，直接 memcpy |
| BEZIER::computerCoefficient | 25 | OK | coeff = {1,3,3,1} |
| BEZIER::getInterpolatePoint | 233 | FAIL | 原始内联 computerCoefficient，无 clamp |
| BEZIER::getTangentVector | 363 | FAIL | 原始完全展开循环，导数分析形式 |

### gbMatrix4.cpp (12/36 = 33.3%)

| 函数 | 大小 | 状态 | 备注 |
|------|------|------|------|
| gbMatrix4::gbMatrix4 | 34 | FAIL | 构造函数 codegen 不同 |
| gbMatrix4::operator= | 27 | FAIL (77.8%) | 循环展开差异 |
| gbMatrix4::operator*=(gbMatrix4) | 122 | 未测 | |
| gbMatrix4::RightMultiply(gbMatrix4) | 126 | FAIL (23%) | |
| gbMatrix4::LeftMultiply(gbMatrix4) | 122 | FAIL (0%) | 被内联为 *=, 原始不同 |
| gbMatrix4::Transform(const*,*) | 90 | OK | |
| gbMatrix4::Rotate | 81 | OK | |
| gbMatrix4::LoadIdentity | 32 | FAIL (68.8%) | memset offset 差异 |
| gbMatrix4::IsIdentity | 57 | FAIL (71.9%) | |
| gbMatrix4::IsValid | 42 | FAIL (7.1%) | |
| gbMatrix4::operator() | 17 | OK | |
| gbMatrix4::Transpose(void) | 60 | FAIL (21.7%) | |
| gbMatrix4::Transpose(out) | 44 | FAIL (15.9%) | |
| gbMatrix4::GetRow(gbVec3D*) | 32 | FAIL (50%) | |
| gbMatrix4::GetRow(gbVec4D*) | 38 | FAIL (52.6%) | |
| gbMatrix4::GetColumn(gbVec3D*) | 32 | OK | |
| gbMatrix4::GetColumn(gbVec4D*) | 39 | OK | |
| gbMatrix4::SetAxisAngle(axis,cos,sin) | 143 | FAIL (20.3%) | |
| gbMatrix4::SetAxisAngle(axis,angle) | 37 | FAIL (78.4%) | |
| gbMatrix4::SetAxisAngle(vec,angle) | 73 | FAIL (6.8%) | |
| gbMatrix4::Invert(void) | 402 | FAIL (2%) | |
| gbMatrix4::Invert(out) | 351 | FAIL (61.8%) | |
| gbMatrix4::RightMultiply(quat) | 198 | FAIL (2%) | |
| gbMatrix4::operator*=(quat) | - | 未测 | |
| gbMatrix4::LeftTranslate(gbVec3D&) | 87 | OK | |
| gbMatrix4::LeftTranslate(f,f,f) | 95 | OK | |
| gbMatrix4::RightTranslate(gbVec3D&) | 33 | OK | |
| gbMatrix4::RightTranslate(f,f,f) | 33 | OK | |
| gbMatrix4::RightScale | 121 | OK | |
| gbMatrix4::LeftScale | 91 | OK | |
| gbMatrix4::Transform(*,*,int) | 126 | FAIL (13.5%) | |
| gbMatrix4::Transform(*,int) | 116 | FAIL (12.1%) | |
| gbMatrix4::Transform_W | 185 | FAIL (3.2%) | |
| gbMatrix4::IsOrthonormal | 563 | FAIL (3.7%) | |
| gbMatrix4::MakeMatrix | 307 | FAIL (3.6%) | |
| gbMatrix4::RotateIn | 77 | OK | |
| gbMatrix4::TransformPlane | 259 | FAIL (58.7%) | |
| gbMatrix4::operator*=(float*) | - | 未测 | |
| gbMatrix4::LeftMultiply(quat) | 198 | FAIL (9.1%) | |

## 常见不匹配原因

| 原因 | 修复方法 | 优先级 |
|------|----------|--------|
| memset/memcpy 被 inline 展开方式不同 | 用显式循环代替 memset | 高 |
| 循环展开差异 | 匹配原始的循环形式 (do-while vs for) | 高 |
| 编译器自动内联 | 在调用点直接写内联代码 | 中 |
| 寄存器分配不同 | 调整变量声明顺序/局部变量使用方式 | 中 |
| 浮点常量引用方式 | 检查 IDA 中的常量使用模式 | 低 |
| 函数 prologue/epilogue 差异 | 可能需要调整 calling convention | 低 |

## 工具链

| 工具 | 路径 | 用途 |
|------|------|------|
| VC6 CL.EXE | tools/vc6/VC6.0 完整绿色版/VC98/Bin/CL.EXE | 编译 |
| IDA Pro 9.2 | D:\Program Files\IDA Professional 9.2\idat.exe | 反编译 |
| gbengine_compare.py | tools/gbengine_compare.py | 字节比对 |
| gbengine_fill_stubs.py | tools/gbengine_fill_stubs.py | 填充 stub |
| gbengine_export_all.py | tools/ida/gbengine_export_all.py | IDA 批量导出 |

## 剩余 STUB 函数 (16个)

| 文件 | 函数 | 难度 | 备注 |
|------|------|------|------|
| gbActor.cpp | UpdateExportNodes | 高 | 256B, SEH, 骨骼变换 |
| gbActor.cpp | GetMixInfo | 低 | 简单访问器，需确认数据位置 |
| gbBaseMesh.cpp | (unknown) | 中 | |
| gbGeomNode.cpp | LoadFromFile | 高 | 文件加载 |
| gbGeomNode.cpp | LoadCVDFile | 高 | CVD 文件解析 |
| gbGeomNode.cpp | LoadCVDFromStream (2arg) | 高 | 流式加载 |
| gbGeomNode.cpp | LoadCVDFromStream (4arg) | 高 | 流式加载 |
| gbGeomNode.cpp | Update | 中 | 动画更新 |
| gbGfxManager_D3D.cpp | (unknown) | 中 | D3D 管理 |
| gbImage2D.cpp | (unknown) | 中 | |
| gbParticle.cpp | LoadFromFile (emitter) | 中 | 文件格式解析 |
| gbParticle.cpp | ComputeEmitterData | 中 | 发射器计算 |
| gbParticle.cpp | LoadFromFile (group) | 中 | 文件格式解析 |
| gbParticle.cpp | Render (group) | 中 | 粒子渲染 |
| gbTexture.cpp | (unknown) | 中 | |
| gbUIRect.cpp | (unknown) | 低 | |

## 验证命令

```bash
# 编译单个文件
powershell: $env:INCLUDE="...VC98\Include;...\include"; $env:LIB="...VC98\Lib"
& CL.EXE /c /O2 /Fo<out.obj> <src.cpp>

# 字节比对
python tools/gbengine_compare.py --obj tools/vc6/XXX.obj --all
python tools/gbengine_compare.py --compile src/gbengine/XXX.cpp --all
```
