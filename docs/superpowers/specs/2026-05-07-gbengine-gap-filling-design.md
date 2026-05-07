# gbengine.dll 实现缺口填充设计

**日期**: 2026-05-07
**范围**: gbengine.dll 中的 stub/TODO/质量差 的函数实现
**策略**: 自底向上，先基础设施再上层逻辑

## 背景

gbengine.dll 已完成约 85% 的反编译，但仍有以下类型的缺口：
1. 完全空的 stub 函数（有 Ghidra 导出数据）
2. 假实现（如 LZO memcpy stub）
3. 标记 TODO 的不完整实现
4. 无 Ghidra 导出数据的内部函数（暂跳过）

## 依赖关系图

```
Layer 1 (基础设施 - 无依赖):
├── gbDynVertBuf_D3D::Lock/Unlock/Draw  [虚函数覆写, D3D顶点渲染]
└── sub_1002DC60 (LZO统一入口)         [CPK包解压依赖]

Layer 2 (中间层 - 依赖 L1):
├── gbParticleGroup::Render             [依赖 DynVertBuf::Lock+Draw]
├── gbImage2D::LoadImageFile 修复       [D3DX纹理加载修正]
└── gbImage2D::ScaleTo + sub_100244D0   [双线性缩放]

Layer 3 (小修复 - 独立):
├── gbBaseMesh::GetFVF                  [应返回 m_fvf]
├── gbLightObj::GetType                 [应返回 lightType]
├── gbMisc Profile 系列                 [保持空即可,原始也是stub]
└── gbGeomNode blade 函数               [无导出数据, 跳过]

Layer X (无数据, 跳过):
├── CollectVisibleNodes (0x100145A0区域) [无 Ghidra 导出]
├── gbScalePixelData (0x100244D0)       [无 Ghidra 导出]
└── gbBladeSystem_Submit (0x1000ED80)   [无 Ghidra 导出]
```

## 阶段 1: gbDynVertBuf_D3D 虚函数 (Lock/Unlock/Draw)

**现状**: 基类 `gbDynVertBuf` 有 Lock/Unlock/Draw 虚函数声明为空。
D3D 子类 `gbDynVertBuf_D3D` 的构造函数已实现，但虚函数覆写未实现。

**Ghidra 数据**: 无直接导出（虚函数通过 vtable 调用），但可从 `RenderUIQuad` 等调用者的反编译中推断行为：
- `vtable[3]` = Lock(int numVerts) → 返回顶点缓冲区指针
- `vtable[4]` = Unlock() → 解锁缓冲区
- `vtable[5]` = Draw(int primType, gbRenderEffect*, gbTextureArray*) → 设置状态并 DrawPrimitive

**实现方案**:
- Lock: IDirect3DVertexBuffer9::Lock，返回顶点数据指针，更新 m_currentVertex
- Unlock: IDirect3DVertexBuffer9::Unlock
- Draw: 调用 effect->Apply()，设置纹理，SetStreamSource，SetFVF，DrawPrimitive

**验证**: RenderUIQuad/RenderGeomQuad 已有实现，它们调用 Lock→填充→Draw。
编译通过且 vtable 布局正确即为成功。

## 阶段 2: LZO 压缩核心 (sub_1002DC60)

**现状**: `lzo1x_1_compress` 和 `lzo1x_decompress` 是 memcpy stub。
原始二进制中 CPK::Compress/DeCompress 调用的是 `sub_1002DC60`，
传入一个结构体控制压缩/解压方向。

**Ghidra 数据**: sub_1002DC60 无直接导出。但 CPK::Compress (72B) 和
CPK::DeCompress (79B) 的反编译显示它们构造一个结构体后调用 sub_1002DC60：

```c
// 结构体布局 (从 Compress/DeCompress 推断):
struct LZOContext {
    int algorithm;      // +0x00: =2 (LZO)
    char direction;     // +0x04: 1=compress, 0=decompress
    void* dst;          // +0x08
    void* src;          // +0x0C
    uint srcLen;        // +0x10
    int/uint field_14;  // +0x14: outLen for compress, 0?
    uint dstBufSize;    // +0x18: =srcLen or =2*srcLen
    int result;         // +0x1C: 返回值
    char field_20;      // +0x20: DeCompress中=0
};
```

**实现方案**:
- 由于 sub_1002DC60 无 Ghidra 导出，且 LZO 算法已知，
  采用方案: 保留 CPK::Compress/DeCompress 的结构体构造逻辑（匹配字节），
  sub_1002DC60 内部调用 miniLZO 的 lzo1x_1_compress/lzo1x_decompress。
- 这样 CPK 层字节匹配，LZO 核心功能正确但不追求匹配。

**验证**: 能正确解压 .cpk 包中的压缩文件即为成功。

## 阶段 3: gbParticleGroup::Render (885B)

**现状**: 完全空 stub，只有 RenderEffect 检查。

**Ghidra 数据**: 完整反编译已有 (`gbParticleGroup_Rendervoid_1002b770.json`)。
核心逻辑：
1. 从 VertPoolMgr 获取 DynVertBuf (fvf=0x15)
2. Lock 顶点缓冲 (6 verts * numParticles)
3. 对每个粒子：变换位置 → 计算旋转后的 billboard 四边形 → 写入6个顶点
4. Push/Load identity matrix → Draw → Pop matrix

**依赖**: gbDynVertBuf::Lock + Draw (阶段1), gbMatrixStack (已实现)

**实现方案**: 直接翻译 Ghidra 输出为 C++，使用已知结构体偏移。

## 阶段 4: gbImage2D 修复

### 4a. LoadImageFile 修正

**现状**: 代码调用 D3DXGetImageInfoFromFile / D3DXLoadSurfaceFromFile，但
传入 NULL 的 device/surface 指针。

**Ghidra 数据**: `gbImage2D_LoadImageFilechar___int_1001e490.json` 有完整反编译。

**修复**: 对照 Ghidra 输出重写，正确获取 D3D device 和创建 surface。

### 4b. ScaleTo (sub_100244D0 缺数据)

**现状**: `gbScalePixelData` 是空 stub。

**Ghidra 数据**: sub_100244D0 **无导出**。但 ScaleTo 有导出，可看到调用签名：
`sub_100244D0(5, bytesPerPixel, srcW, srcH, srcBits, dstW, dstH, dstBuf)`

**实现方案**: 由于无 Ghidra 数据，实现标准双线性插值算法（功能等价，不追求字节匹配）。
参数1=5 推测为插值模式（bilinear）。

## 阶段 5: 简单一行修复

这些是明显的 accessor 错误，每个只需改一行：

| 函数 | 文件 | 修复 |
|------|------|------|
| `gbBaseMesh::GetFVF()` | gbMesh.cpp | `return m_fvf;` |
| `gbLightObj::GetType()` | gbLightObj.cpp | `return lightType;` |

**Profile 系列** (gbMisc.cpp): 保持空。原始二进制中这些也是空函数
（编译时通过宏控制是否启用 profiling）。

## 跳过的项目 (无 Ghidra 数据)

| 函数 | 原因 |
|------|------|
| CollectVisibleNodes | 无导出，地址 0x100145A0 区域无覆盖 |
| gbScalePixelData (sub_100244D0) | 无导出（ScaleTo 中标记功能等价实现） |
| gbBladeSystem_Submit (0x1000ED80) | 无导出 |
| gbVolModNode::Render | 无具体逻辑导出 |
| gbUIRect::Render | UIRect 导出只有 Init/Release，无 Render |

## 实施顺序

1. **阶段5** (简单修复) → 立即可做，5分钟
2. **阶段1** (gbDynVertBuf_D3D Lock/Unlock/Draw) → 核心基础设施
3. **阶段2** (LZO sub_1002DC60) → 资源加载基础设施
4. **阶段3** (gbParticleGroup::Render) → 依赖阶段1
5. **阶段4** (gbImage2D 修复) → 独立

每阶段完成后 cmake 编译验证。

## 成功标准

- 所有修改后 `cmake --build build` 编译通过
- 无新增 TODO/STUB（除明确标注"无数据跳过"的）
- 有 Ghidra 数据的函数实现与反编译逻辑一致
