# PAL3 Decompilation Project

仙剑奇侠传3 匹配反编译项目。目标：生成与原始二进制字节相同的 C/C++ 源码。

## 反编译目标

| 二进制 | 编译器 | 函数数 | 源码状态 | 备注 |
|--------|--------|--------|----------|------|
| topo.dll | VC6 SP5 | ~414 | 7 文件, 2885 行 | 数学库，27% 匹配 |
| gbengine.dll | VC6 SP5 | 1020 导出 | 56 文件, 17553 行, 全部编译通过 | 引擎核心 |
| PAL3A.exe | VC7.0 | 4530 (in .text) | IDA pipeline 99.1% exported | 有完整 PDB |
| PAL3.exe | VC7.0+7.1 | ~5000+ | 待脱壳 | StarForce 保护 |

## 项目结构

```
src/
├── topo/           # topo.dll 数学库 (gbVec3D, gbMatrix4, gbQuaternion...)
├── gbengine/       # gbengine.dll 引擎核心 (56 .cpp, VC6 编译通过)
└── pal3a/          # PAL3A.exe 游戏逻辑 (逐文件填充中)

include/            # 头文件和结构体定义
asm/
├── gbengine_ida/   # gbengine.dll IDA 反编译 JSON (1344 函数)
└── pal3a/          # PAL3A.exe 反编译数据

tools/
├── vc6/            # VC6 SP5 工具链 (Git LFS)
├── gbengine_compare.py    # 字节比对工具
├── gbengine_fill_stubs.py # Stub 自动填充
├── pal3a_fill_stubs.py    # PAL3A stub 填充
├── pal3a_file_export.py   # PAL3A 文件导出
└── ida/            # IDA 自动化管线脚本

cmake/              # CMake 构建配置 (VC6 toolchain, DirectX, MSVC flags)
original/           # 原始二进制 (Git LFS)
extra/PAL3patch/    # 社区补丁项目 (submodule)
```

## 构建

### gbengine.dll (VC6 SP5)

```batch
# 单文件编译验证
python tools/gbengine_compare.py --compile src/gbengine/gbCamera.cpp

# 字节比对
python tools/gbengine_compare.py --func gbCamera::SetLookAt
```

### CMake 构建 (VS2022 测试)

```batch
cmake -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release
```

### VC6 原生构建

```batch
cmake -B build/gbengine -G "NMake Makefiles" ^
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake ^
  -DBUILD_TARGET=gbengine
cmake --build build/gbengine
```

## 当前进度 (2026-05-07)

### gbengine.dll — 主要工作方向

- 56 个 .cpp 文件全部通过 VC6 编译
- 1020 个导出函数中约 680+ 已实现
- 157 个函数完全字节匹配 (23.1%)
- IDA 反编译数据完整覆盖 (1344 函数 JSON)
- 下一步：继续实现 stub 函数，推进字节匹配率

### topo.dll — 基本完成

- 114/414 函数已实现 (27%)
- 核心数学类 (gbVec3D, gbMatrix4, gbQuaternion) 已完成

### PAL3A.exe — IDA 管线就绪

- PDB 完整符号 (11412 函数, 1057 类, 479 源文件)
- IDA 7-phase pipeline: 5012/5057 函数已导出 (99.1%)
- 等待 gbengine 完成后全面推进

## 工具链要求

- Python 3.x
- Visual C++ 6.0 SP5 (已含于 `tools/vc6/`, Git LFS)
- DirectX SDK Summer 2003 (d3d9, d3dx9, dinput8)
- IDA Pro 9.x (反编译管线)

## 参考项目

- [PAL3patch](https://github.com/zhangboyang/PAL3patch) — 结构体定义、逆向笔记
- [OpenPAL3](https://github.com/dontpanic92/OpenPAL3) — 文件格式文档

## 许可证

本项目用于教育和研究目的。仙剑奇侠传3 版权归原作者所有。
