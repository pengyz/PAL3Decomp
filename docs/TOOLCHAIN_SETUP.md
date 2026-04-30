# PAL3 Decompilation Project - 工具链配置完成

## ✅ 配置状态

你的开发环境已配置完成：

- ✅ **Python 3.12.1** - 脚本工具运行环境
- ✅ **Visual Studio 2022** - 可用于功能测试（非二进制精确）
- ✅ **CMake 4.0.1** - 构建系统
- ✅ **游戏文件** - PAL3.exe, gbengine.dll, topo.dll 已定位
- ✅ **源代码** - topo.dll 7个文件 (2,340 行) 已完成反编译

---

## 🚀 快速开始

### 方案 1: 功能测试编译（使用 VS 2022）

**用途**: 验证代码逻辑正确性，快速迭代开发

```batch
# 1. 运行快速测试构建
test_build.bat

# 输出将在 build\test\ 目录
```

**优点**: 
- 无需安装额外软件
- 编译速度快
- 适合验证代码功能

**缺点**: 
- ⚠️ **无法产生与原始二进制字节一致的输出**
- 不能用于最终验证

---

### 方案 2: 二进制精确匹配（需要 VC6/VS2003）

**用途**: 产生与原始游戏完全相同的机器码

#### 安装历史版本编译器

详细安装指南请查看: **`install_msvc.md`**

需要安装：
- **Visual C++ 6.0 SP6** - 用于 topo.dll 和 gbengine.dll
- **Visual Studio .NET 2003** - 用于 PAL3.exe

#### 使用二进制精确编译

```batch
# 1. 配置编译器环境
setup_env.bat
# 选择选项 1 (VC6) 或 2 (VS2003)

# 2. 编译 topo.dll
build.bat topo

# 3. 验证二进制匹配
python run.py compare src/topo/gbVec3D.cpp 0x10001000 100
```

---

## 📂 项目脚本说明

| 脚本 | 用途 |
|------|------|
| `check_toolchain.py` | 检测和验证工具链安装 |
| `test_build.bat` | 使用当前可用的 MSVC 快速测试编译 |
| `setup_env.bat` | 配置特定版本编译器环境（VC6/VS2003） |
| `build.bat` | 主构建脚本，支持多目标编译 |
| `run.py` | 项目管理工具（分析、比对、进度跟踪） |

---

## 🎯 构建目标

### topo.dll - 数学库（✅ 已完成反编译）

```batch
build.bat topo
```

**状态**: 7个源文件，2,340行代码
- ✅ gbVec3D.cpp - 3D向量类
- ✅ gbMatrix4.cpp - 4x4矩阵
- ✅ gbQuaternion.cpp - 四元数
- ✅ gbRotMatrix.cpp - 旋转矩阵
- ✅ gbMatrixStack.cpp - 矩阵栈
- ✅ topo_global.cpp - 全局函数
- ✅ topo_internal.cpp - 内部函数

**编译器要求**: VC++ 6.0 SP6 (build 8804)

---

### gbengine.dll - 游戏引擎（🔄 待开始）

```batch
build.bat gbengine
```

**状态**: 3,213 个函数 JSON 数据已导出，等待反编译

**包含模块**:
- 渲染引擎 (DirectX 9)
- 输入系统 (DirectInput 8)
- 音频系统 (Miles Sound System)
- 资源管理
- 场景管理
- 物理系统

**编译器要求**: VC++ 6.0 SP6

---

### PAL3.exe - 主程序（🔒 待脱壳）

```batch
build.bat pal3
```

**状态**: StarForce 加壳，需先脱壳后才能反编译

**包含模块**:
- 游戏主循环
- 战斗系统
- 剧情系统
- UI 系统
- SCE 脚本引擎

**编译器要求**: VC++ 7.0 (VS .NET 2002) + VS 2003 链接器

脱壳指南: `docs/unpacking.md`

---

## 🔍 验证和比对

### 检查环境

```batch
python check_toolchain.py
```

### 编译并比对单个函数

```python
# 1. 编译源文件
python run.py compile src/topo/gbVec3D.cpp

# 2. 提取原始二进制
python run.py extract-function 0x10001000 100

# 3. 逐字节比对
python run.py compare src/topo/gbVec3D.cpp 0x10001000 100
```

### 查看项目进度

```batch
python run.py progress
```

---

## 📚 文档索引

| 文档 | 内容 |
|------|------|
| `CLAUDE.md` | 项目总体介绍，工作流程，规则 |
| `docs/compiler_setup.md` | 编译器详细配置指南 |
| `install_msvc.md` | MSVC 安装步骤和下载链接 |
| `docs/unpacking.md` | PAL3.exe 脱壳指南 |
| `docs/community_structs.md` | 社区逆向的结构体定义 |
| `docs/sce_opcodes.md` | SCE 脚本虚拟机操作码 |
| `docs/file_formats.md` | CPK/SCN/SCE 文件格式 |

---

## 🔧 常见任务

### 添加新的反编译函数

1. 找到 Ghidra 导出的 JSON:
   ```
   asm/gbengine/FunctionName_ADDRESS.json
   ```

2. 转换为 C++ 代码并放入对应目录:
   ```
   src/gbengine/filename.cpp
   ```

3. 编译并验证:
   ```batch
   build.bat gbengine
   python run.py compare src/gbengine/filename.cpp 0xADDRESS SIZE
   ```

### 批量反编译

```python
# AI 辅助反编译（需要 Anthropic API key）
python run.py batch --count 10

# 查看待处理队列
python run.py queue
```

---

## ⚙️ CMake 配置说明

项目已配置为支持多编译器和多目标构建：

```cmake
# CMakeLists.txt 自动检测编译器版本：
# - MSVC 12.00 (VC6)     -> 启用 VC6 特定优化
# - MSVC 13.10 (VS2003)  -> 启用 VS2003 特定优化
# - 其他                 -> 警告：二进制不匹配

# 通过 BUILD_TARGET 选择构建目标：
cmake -B build -DBUILD_TARGET=topo       # 或 gbengine, pal3
```

---

## 🎓 下一步学习

### 如果你想...

**快速验证已有代码**:
```batch
test_build.bat
```

**进行二进制精确反编译**:
1. 阅读 `install_msvc.md`
2. 安装 VC++ 6.0 SP6
3. 运行 `setup_env.bat` 和 `build.bat topo`

**开始反编译 gbengine.dll**:
1. 创建 `src/gbengine/` 目录
2. 选择简单函数开始（0-32字节）
3. 参考 `src/topo/` 的实现风格

**脱壳 PAL3.exe**:
1. 阅读 `docs/unpacking.md`
2. 准备 Windows XP/7 环境或虚拟机
3. 使用 PAL3patch 工具链

---

## 💡 提示

- ✅ **优先使用 test_build.bat** 快速验证代码逻辑
- ✅ **定期运行 check_toolchain.py** 确保环境正常
- ✅ **小步迭代** 每次只反编译几个函数
- ✅ **保持编译通过** 不要积累太多编译错误
- ⚠️ **二进制匹配需要精确的编译器版本** 否则字节级对比会失败

---

## 🐛 遇到问题？

1. **编译失败**: 运行 `check_toolchain.py` 检查环境
2. **找不到头文件**: 检查 `include/` 目录和 CMakeLists.txt
3. **二进制不匹配**: 确认使用的是正确版本的编译器（VC6 SP6 或 VS2003）
4. **脚本错误**: 确保 Python 3.8+ 和 `pip install -r requirements.txt`

---

**工具链配置完成！现在可以开始反编译工作了。** 🎉

推荐第一步: 运行 `test_build.bat` 验证 topo.dll 能够正常编译。
