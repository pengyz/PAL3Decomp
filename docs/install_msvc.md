# MSVC 安装指南

## 快速开始选项

### 选项 1: 现代工具链（推荐用于开发测试）

**优点**: 免费、易安装、现代工具链
**缺点**: 无法产生二进制精确匹配

#### 安装 Visual Studio 2022 Community

1. 下载安装器：https://visualstudio.microsoft.com/zh-hans/downloads/

2. 运行安装器，选择工作负载：
   - ✅ 使用 C++ 的桌面开发
   - 在右侧"安装详细信息"中确保选中：
     - ✅ MSVC v143 - VS 2022 C++ x64/x86 生成工具
     - ✅ Windows 10 SDK (最新版本)
     - ✅ CMake 工具

3. 安装后，测试：
   ```batch
   # 打开"x86 Native Tools Command Prompt for VS 2022"
   cl.exe
   # 应显示: Microsoft (R) C/C++ Optimizing Compiler Version 19.xx
   ```

4. 在项目中使用：
   ```batch
   cd D:\workspace\project-x
   test_build.bat
   ```

---

### 选项 2: 二进制精确匹配工具链（用于最终验证）

需要安装历史版本的 Visual Studio。这些版本不再有官方支持，但可以从归档站点获取。

---

## 安装 Visual C++ 6.0 SP6

**用途**: 编译 topo.dll 和 gbengine.dll（二进制精确匹配）

### 下载链接

可以从以下来源获取：

#### Archive.org（合法归档）
- 搜索: "Visual Studio 6.0" 或 "Visual C++ 6.0"
- 链接示例: https://archive.org/details/vs6ent
- ISO 文件名: `en_vs6_ent.iso` 或 `vs6ent.exe`

#### WinWorld（软件保存项目）
- https://winworldpc.com/product/visual-studio/60
- 下载 "Enterprise Edition" ISO

### 安装步骤

1. **挂载或解压 ISO**
   ```batch
   # Windows 10/11 可直接双击 ISO 挂载
   # 或使用 7-Zip 解压
   ```

2. **运行安装程序**
   - 运行 `SETUP.EXE`
   - 如果在 Windows 10+ 上出现兼容性问题：
     - 右键 → 属性 → 兼容性 → 选择"Windows XP SP3"
     - 以管理员身份运行

3. **选择安装组件**
   - ✅ Visual C++（必选）
   - ❌ Visual Basic（可选）
   - ❌ Visual FoxPro（跳过）
   - ❌ Visual InterDev（跳过）
   
4. **安装到默认路径**
   ```
   C:\Program Files\Microsoft Visual Studio\VC98
   ```

5. **安装 Service Pack 6**
   
   **重要**: 必须安装 SP6 才能获得正确的编译器版本！
   
   - 下载 `Vs6sp6.exe`
   - 来源:
     - Archive.org: 搜索 "Visual Studio 6.0 Service Pack 6"
     - 直接链接: https://archive.org/details/vs6sp6
   
   - 运行 `Vs6sp6.exe`，选择 Visual C++ 组件

6. **验证安装**
   ```batch
   "C:\Program Files\Microsoft Visual Studio\VC98\bin\cl.exe"
   
   # 应显示:
   # Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 12.00.8804 for 80x86
   ```
   
   **关键**: 版本号必须是 **12.00.8804**（SP6 的 build 号）

### 已知问题和解决方案

#### 问题 1: 安装程序无法在 Windows 10+ 运行
**解决方案**:
- 使用 Windows XP/7 虚拟机
- 或在兼容模式下运行（见上文）
- 或使用 Docker + Wine

#### 问题 2: MSDEV.EXE 崩溃
**解决方案**:
- 不影响命令行编译器 (cl.exe)
- 可以忽略，我们只需要 cl.exe

#### 问题 3: 缺少 MSPDB60.DLL
**解决方案**:
```batch
# 从 VC98\bin 复制到 System32
copy "C:\Program Files\Microsoft Visual Studio\VC98\bin\MSPDB60.DLL" ^
     "C:\Windows\System32\"
```

---

## 安装 Visual Studio .NET 2003

**用途**: 编译 PAL3.exe（二进制精确匹配）

### 下载链接

#### Archive.org
- 搜索: "Visual Studio .NET 2003"
- ISO: `en_vs.net_2003_enterprise_architect.iso`
- 链接: https://archive.org/details/vs2003

#### WinWorld
- https://winworldpc.com/product/visual-studio-net/2003
- 选择 Enterprise Architect Edition

### 安装步骤

1. **挂载 ISO**
   ```batch
   # 双击挂载，或使用虚拟光驱软件
   ```

2. **运行安装程序**
   - 运行 `setup.exe`
   - 序列号: 见 ISO 内的 README 或使用 MSDN 订阅号

3. **选择组件**
   - ✅ Visual C++ .NET（必选）
   - ✅ Visual C# .NET（可选）
   - ❌ Crystal Reports（跳过）
   - ❌ Visual SourceSafe（跳过）

4. **安装路径**
   ```
   C:\Program Files\Microsoft Visual Studio .NET 2003
   ```

5. **验证安装**
   ```batch
   call "C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
   cl.exe
   
   # 应显示:
   # Microsoft (R) C/C++ Optimizing Compiler Version 13.10.xxxx for 80x86
   ```

---

## 配置项目使用正确的编译器

安装完成后，使用项目提供的脚本：

### 方法 1: 自动配置（推荐）
```batch
cd D:\workspace\project-x
setup_env.bat
```

选择对应的编译器选项，脚本会自动配置环境变量。

### 方法 2: 手动配置

#### 使用 VC6 编译 topo.dll:
```batch
set PATH=C:\Program Files\Microsoft Visual Studio\VC98\bin;%PATH%
set INCLUDE=C:\Program Files\Microsoft Visual Studio\VC98\include;%INCLUDE%
set LIB=C:\Program Files\Microsoft Visual Studio\VC98\lib;%LIB%

cd D:\workspace\project-x
build.bat topo
```

#### 使用 VS2003 编译 PAL3.exe:
```batch
call "C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"

cd D:\workspace\project-x
build.bat pal3
```

---

## 验证配置

运行完整的环境检查：

```batch
cd D:\workspace\project-x
python run.py check
```

应该看到：
```
Required Tools:
--------------------------------------------------
  [+] Python 3.8+                    OK
  [+] MSVC (cl.exe)                  OK
  [+] Git                            OK

MSVC Details:
  Version: 12.00.8804 (VC6 SP6)
  or: 13.10.xxxx (VS2003)
```

---

## 常见问题

### Q: 需要序列号/激活码吗？
A: VC6 和 VS2003 已停止支持，微软不再执行激活。历史归档中通常包含合法的 MSDN 订阅号。

### Q: 可以在虚拟机中使用吗？
A: 可以！推荐使用 Windows XP/7 虚拟机安装旧版 VC6。

### Q: Linux 用户怎么办？
A: 可以使用 Wine，但不推荐（兼容性问题）。建议用 VirtualBox 运行 Windows 虚拟机。

### Q: 没有 MSDN 订阅怎么办？
A: Archive.org 和 WinWorld 提供的是合法的软件保存副本，用于教育/研究用途。

---

## 下一步

配置好编译器后：

1. 测试编译 topo.dll:
   ```batch
   setup_env.bat
   build.bat topo
   ```

2. 验证二进制匹配:
   ```batch
   python run.py compare src/topo/gbVec3D.cpp 0x10001000 100
   ```

3. 开始反编译新函数
