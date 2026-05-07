# gbengine.dll 反编译进度

## 概要

| 指标 | 数值 |
|------|------|
| 编译器 | MSVC 6.0 SP5 (`/O2 /Ob2 /GF /Gy /Zp4 /GX`) |
| IDA 导出函数 | 1344 |
| 源文件数 | 55 |
| 编译通过文件 | **55/55 (100%)** |
| DLL 链接 | **成功 (925KB, 1020 exports)** |
| 最后更新 | 2026-05-07 |

## 二进制匹配进度 (活跃文件)

| 文件 | 总函数 | 完全匹配 | 匹配率 | 状态 |
|------|--------|----------|--------|------|
| gbVec3D.cpp | 16 | **16** | **100%** | DONE |
| gbGfxManager.cpp | 44 | **33** | 75% | WIP |
| gbMatrix4.cpp | 31 | **16** | 51.6% | WIP |
| gbQuaternion.cpp | 19 | **11** | 57.9% | WIP |

---

## gbVec3D.cpp — 16/16 (100%) DONE

所有函数完全匹配，无需进一步工作。

---

## gbGfxManager.cpp — 33/44 (75%)

### 完全匹配 (33个)

gbGfxManager::~gbGfxManager, EnableEmissive, GetAmbientLight, GetCurTick,
GetCurTime, GetDeltaTick, GetDeltaTime, GetEffectMgr, GetEmissiveFactor,
GetFog, GetGfxCaps, GetLight, GetMatrixStack, GetPrintFont, GetPrintFontMgr,
GetResManager, GetSceneGraph, GetStatistic, GetVertPoolMgr, GetViewMatrix,
GetViewport, GetWorldMatrix(70.9%→需修), IdentityWorldMatrix, IsLightEnable,
IsWireMode, OffsetZBuffer, SetAmbientLight, SetCameraMatrix, SetClearParam,
SetEmissiveFactor, SetFog, SetSceneGraph, SetWireMode, gbEffectMgr::~gbEffectMgr

### 未匹配函数详情

| 函数 | 大小 | 匹配率 | 未匹配原因 |
|------|------|--------|-----------|
| gbGfxManager::gbGfxManager(int&,gbGfxDriverInfo*) | 394B | 16.0% | 尺寸不符(320vs394)。缺少完整初始化逻辑：matrix stack创建、pVertPoolMgr/pEffectMgr/pTexResMgr/pFontMgr分配、Viewport初始化等。需要完整反汇编。 |
| gbGfxManager::BeginScene | 222B | 39.6% | 逻辑正确，指令调度(scheduling)不同。VC6优化器对FPU操作和整数操作的交错顺序不同。可能需要调整局部变量声明顺序或表达式分解方式。 |
| gbGfxManager::GetTMMatrix | 265B | 43.4% | switch/case 的跳转表实现不同，以及虚函数调用(Invert/RightMultiply)的参数传递方式。需要精确匹配vtable调用模式。 |
| gbGfxManager::GetWorldMatrix | 55B | 70.9% | LEA指令调度不同：编译器将RightMultiply参数地址计算放在call之前vs之后。可能是内联影响。 |
| gbGfxManager::ClipBoundVolume | 158B | 20.9% | 虚函数调用方式不匹配。当前使用手动vtable偏移，原始可能通过不同的接口调用GetFrustumPlanes。 |
| gbGfxManager::NewMesh | 189B | 37.0% | 尺寸不符(144vs189)。缺少完整的mesh类型分发逻辑，可能涉及更多mesh type（skinned mesh有独立类）。 |
| gbEffectMgr::gbEffectMgr(void) | 12B | 0% | 12字节的默认构造函数，当前实现过于复杂（初始化了过多成员）。原始可能只设置了2-3个关键成员。 |
| gbEffectMgr::gbEffectMgr(copy) | 148B | 17.6% | 拷贝构造函数逻辑推测不准确。需要准确的gbEffectMgr类布局和成员偏移。 |
| gbEffectMgr::operator= | 191B | 9.9% | 尺寸不符(176vs191)。赋值操作符逻辑推测错误。 |
| gbEffectMgr::Init | 786B | 2.4% | 尺寸严重不符(128vs786)。当前实现过于简化。原始Init创建了多个RenderEffect实例、注册vertex declarations等。 |
| gbEffectMgr::Release | 67B | 9.0% | 释放逻辑不匹配。需要匹配原始的析构顺序和条件检查。 |

---

## gbMatrix4.cpp — 16/31 (51.6%) | 平均匹配率 66.2%

### 完全匹配 (16个)

gbMatrix4::gbMatrix4(void), operator=, operator(), GetColumn(gbVec3D*),
GetRow(gbVec3D*), IsIdentity, LeftScale, LeftTranslate(gbVec3D&),
LeftTranslate(float,float,float), LoadIdentity, RightScale,
RightTranslate(gbVec3D&), RightTranslate(float,float,float),
Rotate, SetAxisAngle(gbAxis,float), Transform(const gbVec3D*,gbVec3D*)

### 未匹配函数详情

| 函数 | 大小 | 匹配率 | 未匹配原因 | 暂时放弃原因 |
|------|------|--------|-----------|-------------|
| Invert(void) | 402B | **85.3%** | 已手动内联。剩余差异：FPU操作数加载顺序(m[1][1]↔m[2][2])和det存储策略(fst vs fstp)。 | VC6对乘法操作数顺序的选择不受源码控制；det的FPU栈vs内存存储策略由编译器启发式决定。 |
| Transpose(void) | 60B | **83.3%** | 寄存器分配ESI↔EDX系统性替换。 | VC6寄存器分配器内部启发式，变量声明重排/register关键字/循环变换均无效。 |
| Invert(gbMatrix4*) | 351B | **63.0%** | 3x3子矩阵求逆逻辑正确。差异在于det存储策略：编译器用fst保持det在FPU栈，原始用fstp存到[esp]再从内存加载。 | FPU寄存器分配策略由编译器内部决定，无法从源码控制。 |
| SetAxisAngle(gbAxis,float,float) | 143B | **35.0%** | 已改用switch+memset+int存储。差异：(1)编译器用EAX+ECX双寄存器避免重载，原始只用EAX需重载cosA；(2)FPU fld调度位置不同。 | 编译器生成比原始更优的代码（少4字节/case），无法从源码让编译器生成更差的代码。 |
| IsValid | 42B | **31.0%** | 大小匹配，for循环结构正确。纯寄存器分配差异：编译器将this复制到EDX用ECX做计数器，原始直接用ECX做指针。 | VC6寄存器分配器对this指针的处理无法从源码控制。 |
| RightMultiply(gbQuaternion&) | 198B | **27.8%** | GetMatrix+RightMultiply组合正确。差异在gbQuaternion临时变量的初始化方式(memset vs逐字段)。 | 可能需要内联GetMatrix或调整gbQuaternion构造方式。 |
| RightMultiply(gbMatrix4&) | 126B | **23.8%** | 已用memcpy做temp拷贝。差异：memcpy后的指针初始化指令调度不同(lea位置)。 | 指令调度受编译器FPU管线优化影响。 |
| LeftMultiply | 122B | **19.7%** | 已改为完整内联矩阵乘法。差异：栈帧大小4字节(sub esp,0x44 vs 0x48)和指令调度。原始复用param栈槽做局部变量。 | 栈帧优化由编译器内部决定。 |
| SetAxisAngle(gbVec3D*,float) | 73B | **16.4%** | 差异在gbQuaternion构造/SetAxisAngle/GetMatrix调用序列。原始可能部分内联。 | 需要分析原始是否内联了某些调用。 |
| Transpose(gbMatrix4*) | 44B | **15.9%** | 大小匹配。原始用整数mov传输float，编译器无论用float*还是int*都生成不同的寄存器分配。 | FPU vs整数传输+寄存器分配的双重问题。 |
| Transform(gbVec3D*,gbVec3D*,int) | 126B | **13.5%** | 大小匹配。原始使用ESI保存中间浮点结果(整数传输)，FPU调度完全不同。 | FPU调度+整数传输优化无法从源码控制。 |
| IsOrthonormal | 563B | **13.0%** | 尺寸不符(384vs563)。原始内联了Normalize和CrossProduct。 | 需要手动内联向量操作。工作量大。 |
| Transform(gbVec3D*,int) | 116B | **12.1%** | 尺寸差4字节(112vs116)。原始用push/pop esi保存寄存器做整数浮点传输。 | VC6对in-place变换选择了整数寄存器传输float的优化路径，无法从源码触发。 |
| MakeMatrix | 307B | **8.8%** | 尺寸不符(224vs307)。原始内联了CrossProduct和Normalize。 | 需要手动内联向量操作。 |
| Transform_W | 185B | **3.2%** | 尺寸差9字节(176vs185)。循环结构和W除法FPU序列完全不同。 | 需要分析原始的具体循环结构和FPU操作序列。 |

---

## gbQuaternion.cpp — 11/19 (57.9%)

### 完全匹配 (11个)

gbQuaternion::gbQuaternion(void), GetAxisAngle, GetMatrix, GetVec3D,
Inverse, IsUnit, IsValid, Magnitude, Normalize, SetUnit, SetVec3D

### 未匹配函数详情

| 函数 | 大小 | 匹配率 | 未匹配原因 |
|------|------|--------|-----------|
| IsNormal | 35B | 5.7% | `Magnitude()`返回值处理方式不同。原始可能内联了Magnitude或使用不同的浮点比较模式。 |
| MultiplyBy | 234B | 0.9% | **尺寸严重不符**(176vs234)。原始使用完全不同的乘法展开形式，可能有额外的临时变量或不同的FPU操作序列。 |
| RotateVector | 158B | 9.5% | **尺寸不符**(64vs158)。当前实现调用GetMatrix+Rotate，但原始内联了整个旋转计算（直接用四元数公式 q*v*q^-1）。 |
| SetAxisAngle | 52B | 42.3% | **尺寸不符**(48vs52)。sin/cos的FPU操作顺序差异，可能与弧度转换表达式的分解方式有关。 |
| SetMatrix | 326B | 17.5% | 复杂的条件分支（trace>0 vs 对角选择）。原始的数组索引方式和寄存器使用模式与当前实现显著不同。 |
| SetTwoVector | 248B | 12.1% | **尺寸不符**(160vs248)。原始可能内联了CrossProduct和Normalize，或有额外的边界检查。 |
| SetYawPitchRoll | 216B | 9.3% | 原始可能内联了SetAxisAngle调用，避免了函数调用开销。当前代码生成3个call。 |
| Slerp | 320B | 49.4% | 逻辑框架正确（49.4%），但FPU sin/cos/acos操作的具体调度顺序不同。可能需要调整条件分支中的表达式求值顺序。 |

---

## 未匹配原因分类汇总

### 1. 寄存器分配差异 (难度：极高)

**症状**：所有指令类型和顺序正确，但使用不同的寄存器编码。
**影响函数**：Transpose(void), Transpose(out), 部分Transform函数
**根因**：MSVC 6.0的寄存器分配器基于内部启发式选择寄存器。变量声明顺序、使用频率、循环深度都影响分配。
**尝试过的修复**：变量声明重排、register关键字、循环形式变换——均无效。
**结论**：需要逆向理解VC6分配器的优先级规则，或接受此类差异。

### 2. FPU指令调度差异 (难度：高)

**症状**：相同的数学运算，但FPU load/store/compute的交错顺序不同。
**影响函数**：BeginScene, Invert(out), Transform系列, Slerp
**根因**：VC6 /O2的FPU调度器重排操作以减少管线延迟，但其具体启发式与我们的表达式写法产生不同结果。
**可能修复**：拆分或合并子表达式、引入临时变量、改变求值顺序。

### 3. 函数内联差异 (难度：高)

**症状**：编译尺寸远小于原始（函数被外部调用替代了内联代码）。
**影响函数**：Invert(void), LeftMultiply, RotateVector, SetYawPitchRoll, MakeMatrix, IsOrthonormal
**根因**：原始编译使用了/Ob1或/Ob2，部分函数在原始代码中被内联展开。
**修复方向**：在调用点手动写内联代码（模仿编译器的内联展开）。

### 4. 循环/条件结构差异 (难度：中)

**症状**：do-while vs for, 条件跳转方向不同, switch代码生成不同。
**影响函数**：IsIdentity(已修复!), SetAxisAngle(axis,cos,sin)
**修复方向**：尝试不同循环形式(for/while/do-while)和条件写法。

### 5. 数据传输方式差异 (难度：中)

**症状**：float值通过FPU(fld/fstp)还是整数寄存器(mov)传输。
**影响函数**：Transpose(out)
**根因**：float*类型的指针解引用默认走FPU路径。使用int*可强制整数路径但改变寄存器分配。
**状态**：两种方式各有不同的不匹配点，暂无完美解决方案。

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
# 完整对比（编译+比对所有函数）
python tools/gbengine_compare.py --compile src/gbengine/gbVec3D.cpp --all
python tools/gbengine_compare.py --compile src/gbengine/gbMatrix4.cpp --all
python tools/gbengine_compare.py --compile src/gbengine/gbQuaternion.cpp --all
python tools/gbengine_compare.py --compile src/gbengine/gbGfxManager.cpp --all

# 对比指定函数
python tools/gbengine_compare.py --compile src/gbengine/gbMatrix4.cpp --func "Transpose"
```
