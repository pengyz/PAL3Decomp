# PAL3 编译器环境配置指南

## 🎯 编译器版本要求（基于 PE 分析）

### 分析结果总结

根据 PE Rich Header 和链接器版本分析：

| 目标 | 链接器版本 | 主要编译器 | 次要编译器 | Visual Studio 版本 |
|------|-----------|-----------|-----------|------------------|
| **gbengine.dll** | 6.00 | MSVC 6.0 SP6 | - | Visual C++ 6.0 |
| **topo.dll** | 6.00 | MSVC 6.0 SP6 | - | Visual C++ 6.0 |
| **PAL3.exe** | 75.24 (7.10.8444) | MSVC 7.0 (C++) | MSVC 6.0 (C) | VS .NET 2003 链接，VC7.0 编译 |

### PAL3.exe Rich Header 详解

```
主力编译器：
  - MSVC 7.0 (C++)         build 8168  (x198) ← 主要游戏逻辑代码
  - MSVC 7.0 (C)           build 8168  (x108)

遗留代码/第三方库：
  - MSVC 6.0 (C)           build 8447  (x13)  ← 少量 VC6 编译的库
  - MSVC 6.0 (C)           build 8168  (x3)

链接器：
  - MSVC 7.1 (Linker)      build 8444  (x6)   ← Visual Studio .NET 2003

StarForce 加壳器：
  - MSVC 9.0 (C)           build 9210  (x2)   ← 加壳工具本身用 VC9 编译
```

**结论**：PAL3.exe 主体代码由 **Visual C++ 7.0 (VS .NET 2002)** 编译，使用 **VS .NET 2003 链接器**链接。

---

## 📦 需要安装的编译器

### 方案 A：完整编译环境（推荐用于二进制对齐）

#### 1. Visual C++ 6.0 SP6 (用于 DLL)

**用途**: 反编译 `gbengine.dll` 和 `topo.dll`

**下载来源**：
- 官方 ISO（需 MSDN 订阅或 Archive.org）
- 文件名：`vc6ent.exe` 或 `vc98ent.iso`
- **必须安装 Service Pack 6**

**关键编译选项**：
```batch
cl.exe /O2 /W3 /GX /c source.cpp
link.exe /DLL /DEF:exports.def
```

**验证安装**：
```batch
cl.exe
# 应显示：Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 12.00.8804 for 80x86
```

#### 2. Visual Studio .NET 2002 (VC7.0) (用于 PAL3.exe)

**用途**: 反编译 `PAL3.exe` 主体代码

**下载来源**：
- MSDN ISO: `en_vs.net_2002_enterprise_architect.iso`
- 或使用 VS 2003 + VC7.0 工具集

**编译选项**：
```batch
cl.exe /O2 /W3 /GX /EHsc /c source.cpp
```

**验证**：
```batch
cl.exe
# 应显示：Microsoft (R) C/C++ Optimizing Compiler Version 13.00.xxxx for 80x86
```

#### 3. Visual Studio .NET 2003 (VC7.1) (用于链接)

**用途**: 最终链接 PAL3.exe（Rich Header 显示使用了 VS2003 链接器）

**下载来源**：
- MSDN ISO: `en_vs.net_2003_enterprise_architect.iso`

**链接器版本**：
```batch
link.exe
# 应显示：Microsoft (R) Incremental Linker Version 7.10.xxxx
```

---

### 方案 B：现代工具链（用于开发/测试，无法二进制对齐）

如果只是功能验证而非精确匹配，可以使用：

- **Visual Studio 2022/2019** + `/std:c++98` + `/arch:IA32`
- 或 **mingw-w64** (GCC) + `-m32 -std=c++98`

**⚠️ 注意**：现代编译器产生的代码 **不会** 与原始二进制字节对齐，仅用于快速迭代。

---

## 🛠️ 环境配置步骤

### Step 1: 安装 Visual C++ 6.0

1. 下载 VC6.0 完整安装包
2. 安装到 `C:\Program Files\Microsoft Visual Studio\VC98`
3. 下载并安装 **Service Pack 6**：
   ```
   Vs6sp6.exe
   ```
4. 添加到 PATH（可选）：
   ```batch
   set VC6_ROOT=C:\Program Files\Microsoft Visual Studio\VC98
   set PATH=%VC6_ROOT%\Bin;%PATH%
   set INCLUDE=%VC6_ROOT%\Include;%VC6_ROOT%\ATL\Include;%VC6_ROOT%\MFC\Include
   set LIB=%VC6_ROOT%\Lib;%VC6_ROOT%\MFC\Lib
   ```

### Step 2: 安装 Visual Studio .NET 2003

1. 挂载 ISO 或运行安装程序
2. 选择 **Visual C++** 组件（必选）
3. 默认安装路径：`C:\Program Files\Microsoft Visual Studio .NET 2003`

### Step 3: 配置 CMake 环境

在项目中使用 **VC6 命令提示符** 或 **VS2003 命令提示符**：

#### 使用 VC6 编译 topo.dll：

```batch
cd /d D:\workspace\project-x
set PATH=C:\Program Files\Microsoft Visual Studio\VC98\Bin;%PATH%
cmake -B build_topo -S . -G "NMake Makefiles" ^
  -DCMAKE_C_COMPILER=cl ^
  -DCMAKE_CXX_COMPILER=cl ^
  -DCMAKE_BUILD_TYPE=Release
cd build_topo
nmake
```

#### 使用 VS2003 编译 PAL3.exe：

```batch
cd /d D:\workspace\project-x
call "C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
cmake -B build_pal3 -G "NMake Makefiles" ^
  -DCMAKE_C_COMPILER=cl ^
  -DCMAKE_CXX_COMPILER=cl
cd build_pal3
nmake
```

---

## 🔍 验证编译器版本

运行以下脚本确认环境：

```python
# python run.py check
```

或手动检查：

```batch
cl.exe 2>&1 | findstr "Version"
link.exe 2>&1 | findstr "Version"
```

**期望输出**：
- VC6: `Version 12.00.8804`
- VC7.0: `Version 13.00.xxxx`
- VS2003: `Version 13.10.xxxx`

---

## 📊 编译参数映射

### topo.dll / gbengine.dll (VC6)

```c
// 原始编译命令（推测）
cl.exe /O2 /Ob1 /GF /Gy /W3 /GX /DWIN32 /D_WINDOWS /D_MBCS /D_USRDLL /c
link.exe /DLL /OPT:REF /OPT:ICF
```

**CMake 等效**：
```cmake
set(CMAKE_CXX_FLAGS "/O2 /W3 /GX /DWIN32 /D_WINDOWS")
```

### PAL3.exe (VC7.0)

```c
// 原始编译命令（推测）
cl.exe /O2 /GL /W3 /EHsc /GR /DWIN32 /D_WINDOWS /DNDEBUG /c
link.exe /LTCG /OPT:REF /OPT:ICF /VERSION:7.10
```

**CMake 等效**：
```cmake
set(CMAKE_CXX_FLAGS "/O2 /W3 /EHsc /GR /DWIN32 /D_WINDOWS /DNDEBUG")
set(CMAKE_EXE_LINKER_FLAGS "/LTCG /OPT:REF /OPT:ICF")
```

---

## ⚠️ 常见问题

### Q1: VC6 在 Windows 10/11 上无法安装？

**解决方案**：
- 使用兼容模式运行安装程序
- 或使用虚拟机（Windows XP/7）
- 或使用 Docker（wine）

### Q2: 编译出来的二进制不匹配？

**可能原因**：
1. 编译器版本不精确（需要 SP6 for VC6）
2. 优化选项不匹配（检查 `/O2` 细节）
3. 结构体对齐不一致（检查 `/Zp` 选项）
4. 浮点运算模式（检查 `/fp:precise` vs `/fp:fast`）

**解决方法**：
- 使用 `python run.py compare` 逐字节对比
- 调整 CMake 编译选项
- 参考 Rich Header 中的精确 build 号

### Q3: 没有 MSDN 订阅怎么办？

合法途径：
- Archive.org 提供旧版 Visual Studio ISO
- 微软官方已停止支持，但允许用于教育/研究用途

---

## 📚 参考资料

- [MSVC 版本对照表](https://en.wikipedia.org/wiki/Microsoft_Visual_C%2B%2B)
- [Rich Header 格式文档](https://0xrick.github.io/win-internals/pe8/)
- [PAL3patch 脱壳工具](https://github.com/zhangboyang/PAL3patch)
- CMakeLists.txt（本项目根目录）

---

**下一步**: 安装完成后，运行 `python run.py check` 验证环境，然后开始编译 `src/topo/` 进行二进制对齐测试。
