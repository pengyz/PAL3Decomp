# PAL3 Decompilation Project

仙剑奇侠传3（PAL3.exe）匹配反编译项目

## 🚀 快速开始

### 1. 检查工具链

```batch
python check_toolchain.py
```

### 2. 测试编译

```batch
test_build.bat
```

### 3. 查看文档

- **[工具链配置指南](docs/TOOLCHAIN_SETUP.md)** - 如何使用构建系统
- **[MSVC 安装教程](docs/install_msvc.md)** - 如何安装历史版本编译器
- **[项目总览](CLAUDE.md)** - 项目结构和工作流程

---

## 📁 项目结构

```
├── src/              # 反编译的源代码
│   ├── topo/         # topo.dll (数学库) ✅ 已完成
│   ├── gbengine/     # gbengine.dll (游戏引擎) 🔄 进行中
│   └── pal3/         # PAL3.exe (主程序) ⏳ 待开始
├── asm/              # Ghidra 导出的函数数据 (JSON)
├── include/          # 头文件和结构体定义
├── docs/             # 技术文档
└── tools/            # 自动化工具

构建脚本：
├── check_toolchain.py  # 环境检查
├── test_build.bat      # 快速测试编译
├── setup_env.bat       # 编译器环境配置
└── build.bat           # 主构建脚本
```

---

## 🎯 反编译目标

| 二进制 | 大小 | 编译器 | 状态 |
|--------|------|--------|------|
| topo.dll | 106 KB | VC6 SP6 | ✅ 24% (7 文件, 2340 行) |
| gbengine.dll | 1.26 MB | VC6 SP6 | 🔄 数据已导出 (3213 函数) |
| PAL3.exe | 1.87 MB | VC7.0 + VS2003 | ⏳ 需要脱壳 |

---

## 🛠️ 工具链

### 当前可用
- ✅ Python 3.12.1
- ✅ Visual Studio 2022（测试用）
- ✅ CMake 4.0.1
- ✅ Git

### 二进制匹配需要（可选）
- ⏳ Visual C++ 6.0 SP6 - 用于 DLL
- ⏳ Visual Studio .NET 2003 - 用于 PAL3.exe

**安装指南**: [docs/install_msvc.md](docs/install_msvc.md)

---

## 📚 文档索引

| 文档 | 内容 |
|------|------|
| [docs/TOOLCHAIN_SETUP.md](docs/TOOLCHAIN_SETUP.md) | 工具链使用完整指南 ⭐ |
| [docs/SETUP_COMPLETE.md](docs/SETUP_COMPLETE.md) | 配置完成报告 |
| [docs/install_msvc.md](docs/install_msvc.md) | MSVC 安装详细步骤 |
| [CLAUDE.md](CLAUDE.md) | 项目总体介绍 |
| [docs/compiler_setup.md](docs/compiler_setup.md) | 编译器技术细节 |
| [docs/unpacking.md](docs/unpacking.md) | PAL3.exe 脱壳指南 |

---

## ⚡ 常用命令

```batch
# 环境检查
python check_toolchain.py

# 快速测试
test_build.bat

# 配置特定编译器
setup_env.bat

# 编译特定目标
build.bat topo      # 数学库
build.bat gbengine  # 游戏引擎
build.bat pal3      # 主程序
build.bat all       # 全部

# 清理构建
build.bat clean
```

---

## 🎓 贡献指南

### 反编译新函数

1. 找到 JSON 数据：`asm/gbengine/FunctionName_ADDRESS.json`
2. 转换为 C++ 代码：`src/gbengine/filename.cpp`
3. 编译验证：`build.bat gbengine`
4. 二进制比对：`python run.py compare src/gbengine/filename.cpp 0xADDR SIZE`

---

## 📊 技术栈

- **编译器**: MSVC 6.0, MSVC 7.0, MSVC 7.1
- **构建系统**: CMake + NMake
- **逆向工具**: Ghidra
- **脚本语言**: Python 3, Batch
- **版本控制**: Git

---

## 🔗 相关项目

- [PAL3patch](https://github.com/zhangboyang/PAL3patch) - C 补丁，提供结构体定义
- [OpenPAL3](https://github.com/dontpanic92/OpenPAL3) - Rust 重实现，提供文件格式文档

---

## 📄 许可证

本项目用于教育和研究目的。仙剑奇侠传3 版权归原作者所有。

---

**最后更新**: 2026-05-01  
**工具链状态**: ✅ 已配置
