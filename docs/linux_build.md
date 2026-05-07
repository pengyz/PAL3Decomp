# Linux 构建指南 (Wine + VC6)

本项目在 Linux 上通过 Wine 运行 MSVC 6.0 SP5 编译器来实现与 Windows 相同的字节精确编译。

## 架构设计

```
┌──────────────────────────────────────────────────────────────┐
│                  Python 逻辑脚本层                            │
│  gbengine_compare.py / gen_import_lib.py / batch_undname.py  │
└──────────────────┬───────────────────────────────────────────┘
                   │ from toolchain import cl, link, undname
┌──────────────────▼───────────────────────────────────────────┐
│               tools/toolchain.py                              │
│   统一接口：cl() / link() / lib() / dumpbin() / undname()    │
│   自动检测平台，路径转换，Wine 环境管理                        │
└──────────────────┬───────────────────────────────────────────┘
                   │ subprocess.run(['wine', 'CL.EXE', ...])
┌──────────────────▼───────────────────────────────────────────┐
│                  Wine + VC6 执行层                            │
│   tools/vc6/Bin/CL.EXE, LINK.EXE, LIB.EXE, DUMPBIN.EXE     │
└──────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────┐
│                     CMake 构建层                              │
│   cmake/toolchain-vc6.cmake                                  │
│   → wine_cl.sh / wine_link.sh / wine_lib.sh (路径转换)       │
│   → 支持 `cmake -G "Unix Makefiles"` 交叉编译               │
└──────────────────────────────────────────────────────────────┘
```

**设计原则**：
- Python 脚本通过 `tools/toolchain.py` 调用工具——不关心平台
- CMake 通过 `cmake/toolchain-vc6.cmake` + shell wrapper 调用工具——不关心平台
- 平台差异完全封装在 toolchain 层和 wrapper 脚本中
- `local_config.json` 的 `"toolchain"` 节可覆盖默认工具路径

## 环境要求

- **OS**: Ubuntu 22.04+ / Debian 12+ (其他发行版亦可)
- **Wine**: 6.0+ (`sudo apt install wine`)
- **Python**: 3.8+ (工具脚本)
- **CMake**: 3.10+ (可选，用于完整构建)

## 快速开始

```bash
# 1. 一次性安装 & 配置
sudo apt install wine
bash tools/setup_wine_vc6.sh

# 2. 编译单个文件并做字节对比
python tools/gbengine_compare.py --compile src/gbengine/BEZIER.cpp --all

# 3. 或者手动编译
source tools/wine_vc6.sh
vc6_compile src/gbengine/BEZIER.cpp /tmp/BEZIER.obj
```

## 工具说明

### `tools/setup_wine_vc6.sh`

一次性运行的初始化脚本：
- 检查 Wine 是否安装
- 为 `vc6/Lib/` 和 `vc6/Include/` 创建小写符号链接（解决 Linux 文件名大小写问题）
- 验证 CL.EXE 能正常工作

### `tools/wine_vc6.sh`

交互式环境脚本，提供以下函数：

| 函数 | 说明 |
|------|------|
| `vc6_cl` | 封装 CL.EXE（直接传递参数） |
| `vc6_link` | 封装 LINK.EXE |
| `vc6_lib` | 封装 LIB.EXE |
| `vc6_compile <src> [obj]` | 使用标准 gbengine 编译参数编译单个文件 |
| `vc6_compile_gbengine <src> [obj]` | 完整 gbengine 优化参数（含 /Oi /Ot /Oy） |
| `vc6_info` | 显示环境信息 |

也可以直接执行：
```bash
bash tools/wine_vc6.sh cl /c /O2 file.cpp
bash tools/wine_vc6.sh compile src/gbengine/BEZIER.cpp
bash tools/wine_vc6.sh info
```

### `tools/wine_cl.sh` / `tools/wine_link.sh` / `tools/wine_lib.sh`

CMake toolchain 使用的最小化封装脚本。

### `tools/gbengine_compare.py`

字节对比工具，自动检测平台：
- Linux: 通过 Wine 调用 CL.EXE
- Windows: 直接调用 CL.EXE

```bash
# 编译并对比所有函数
python tools/gbengine_compare.py --compile src/gbengine/BEZIER.cpp --all

# 对比已有的 .obj
python tools/gbengine_compare.py --obj build/BEZIER.obj --all

# 对比指定函数
python tools/gbengine_compare.py --compile src/gbengine/BEZIER.cpp --func "BEZIER::GetControlPt(void)"
```

## CMake 完整构建

CMake 通过 `cmake/toolchain-vc6.cmake` 支持在 Linux 上交叉编译 Windows DLL/EXE。

```bash
# 配置（指定 toolchain 文件）
cmake -B build/gbengine -G "Unix Makefiles" \
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake \
  -DBUILD_TARGET=gbengine

# 构建（支持并行）
cmake --build build/gbengine -- -j$(nproc)
```

### CMake 交叉编译原理

```
CMake → 生成 Unix Makefiles → make 调用 wine_cl.sh
                                         ↓
                              wine_cl.sh 转换路径参数
                              /home/.../file.cpp → Z:\home\...\file.cpp
                              /I/home/.../include → /IZ:\home\...\include
                                         ↓
                              wine CL.EXE (VC6) 编译
```

`wine_cl.sh` / `wine_link.sh` / `wine_lib.sh` 是 CMake 看到的"编译器"，
它们内部做 Unix→Wine 路径转换后调用真正的 VC6 工具。

### 支持的目标

```bash
# topo.dll (数学库)
cmake -B build/topo -G "Unix Makefiles" \
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake \
  -DBUILD_TARGET=topo

# gbengine.dll (引擎核心)
cmake -B build/gbengine -G "Unix Makefiles" \
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake \
  -DBUILD_TARGET=gbengine
```

## 文件名大小写问题

Linux 文件系统区分大小写，但 VC6 链接器查找 `LIBC.lib`（小写 `.lib`），
而仓库中文件名是 `LIBC.LIB`（全大写）。

解决方案：`setup_wine_vc6.sh` 自动创建小写符号链接。
如果新增了 .LIB 文件，重新运行 setup 脚本即可。

## 已验证的兼容性

| 组件 | 状态 | 备注 |
|------|------|------|
| CL.EXE (编译) | ✓ | 生成与 Windows 相同的 .obj |
| LINK.EXE (链接) | ✓ | 可链接 DLL/EXE |
| gbengine_compare.py | ✓ | 字节对比正常工作 |
| Wine 6.0.3 (Ubuntu 22.04) | ✓ | 主测试环境 |

## 注意事项

- Wine 的 stderr 可能输出 OLE 初始化错误，不影响编译结果
- 设置 `WINEDEBUG=-all` 可以抑制这些噪音（脚本已默认设置）
- 编译产生的 .obj 文件字节完全等同于 Windows 上 VC6 的输出
