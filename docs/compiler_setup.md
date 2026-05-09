# PAL3 编译器环境配置指南

## 编译器版本要求（基于 Rich Header @comp.id 验证）

### 分析结果总结

通过 PE Rich Header 解析 + @comp.id 逐字节验证确认：

| 目标 | 编译器 | cl.exe 版本 | @comp.id build | 来源 |
|------|--------|-------------|----------------|------|
| **PAL3.exe** | VC6 SP0 (RTM) | 12.00.8168 | 8168 | decomp.me msvc6.0 |
| **gbengine.dll** | VC6 SP0 (RTM) | 12.00.8168 | 8168 | 同上 |
| **topo.dll** | VC6 SP0 (RTM) | 12.00.8168 | 8168 | 同上 |

### PAL3.exe Rich Header 详解

```
主力编译器 (prodidUtc12 = VC6 系列):
  - prodidUtc12_CPP (0x0B)  build 8168  (x198) ← C++ 主要游戏逻辑代码
  - prodidUtc12_C   (0x0A)  build 8168  (x108) ← C 代码

链接器 / 汇编器:
  - prodidLinker512  (0x13)  build 8034  (x9)
  - prodidLinker600  (0x04)  build 8447  (x13) + build 8168 (x3)
  - prodidMasm613    (0x0E)  build 7299  (x31)
  - prodidMasm614    (0x12)  build 8444  (x6)

StarForce 加壳器添加 (prodidUtc13 = VC7.0 系列):
  - prodidUtc13_CPP (0x1D)  build 9178  (x26)  ← 加壳器代码
  - prodidUtc13_C   (0x1C)  build 9178  (x2)
```

**结论**：PAL3.exe/gbengine.dll/topo.dll 主体代码均由 **Visual C++ 6.0 RTM (SP0)** 编译。
zhangboyang (PAL3patch) 也独立确认："编译器版本经 rich signature 确定是 VC6 SP0"。

---

## 需要安装的编译器

### Visual C++ 6.0 RTM (SP0) — 所有目标统一使用

**用途**: PAL3.exe, gbengine.dll, topo.dll 全部使用此编译器

**获取方式** (Linux + Wine):
```bash
# 已通过 decomp.me Docker registry 下载并安装到:
# tools/compilers/msvc6.0/
#
# 验证:
source tools/wine_vc6.sh
vc6_info
```

**验证版本**：
```
CL.EXE 应显示: Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 12.00.8168 for 80x86
```

**注意**: 不要使用 SP5/SP6 (12.00.8804)，它产生的 @comp.id build=9782，与原始二进制不匹配。

---

## 环境配置 (Linux + Wine)

### 快速开始

```bash
# 编译器已预装在 tools/compilers/msvc6.0/
# 加载 helper 函数:
source tools/wine_vc6.sh

# 编译单个文件并对比:
python tools/pal3_compare.py --compile src/pal3/WinMain.cpp --all
```

### 目录结构

```
tools/compilers/msvc6.0/    ← VC6 RTM (cl 12.00.8168) [用于编译]
  Bin/CL.EXE, LINK.EXE, C1.DLL, C1XX.DLL, C2.DLL ...
  Include/                   ← C/C++ 标准头文件
  ATL/                       ← ATL 头文件

tools/vc6/                   ← VC6 SP5 旧目录 [仅保留 Lib/ 用于链接]
  Lib/                       ← 标准库 (libc.lib, msvcrt.lib, etc.)
  Include/                   ← 不再使用 (SP5 头文件)
```

---

## 验证编译器版本

```bash
source tools/wine_vc6.sh
vc6_info
# 期望: Version 12.00.8168
```

---

## 编译参数 (PAL3.exe / gbengine.dll / topo.dll 统一)

```bash
# PAL3.exe 编译参数 (推测，需通过字节对比逐步验证):
CL.EXE /c /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MD /Gd /W3 \
       /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS source.cpp

# gbengine.dll 编译参数:
CL.EXE /c /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /Zp4 /GX /MD \
       /DNDEBUG /DWIN32 /D_WINDOWS /D_MBCS source.cpp
```

注意:
- `/GX` = VC6 的异常处理 (等效于 VC7+ 的 `/EHsc`)
- `/GR` = 启用 RTTI
- `/Oy` = Frame Pointer Omission (FPO)
- `/Gy` = 函数级链接 (每个函数独立 COMDAT section)
- gbengine 使用 `/Zp4` (4 字节结构体对齐)

---

## 常见问题

### Q: 为什么不用 VC6 SP5/SP6?

SP5/SP6 的 c1.dll/c2.dll 内部 build 号为 9782，而原始二进制的 @comp.id 记录的是 8168。
不同 build 的编译器在指令调度(instruction scheduling)上可能有差异，导致字节不匹配。

### Q: 为什么之前文档说 VC7.0/7.1?

Rich Header 中 prodID=0x000B (prodidUtc12_CPP) 曾被误解为 "MSVC 7.0"。
经过 kirschju/richheader 的 prodids.py 数据库核实:
- prodID 0x000A/0x000B = prodidUtc12_C/CPP = **VC6** (UTC 12.xx = cl 12.xx)
- prodID 0x001C/0x001D = prodidUtc13_C/CPP = **VC7.0** (UTC 13.xx = cl 13.xx)

PAL3 中 x26 个 prodidUtc13_CPP (build 9178) 对象是 StarForce 加壳器添加的。

### Q: decomp.me 的 msvc6.0 ~ msvc6.6 分别是什么?

| ID | 推测版本 | cl.exe 版本 |
|----|----------|-------------|
| msvc6.0 | VC6 RTM (SP0) | 12.00.8168 ← **我们使用这个** |
| msvc6.3 | VC6 SP3 | 12.00.8xxx |
| msvc6.4 | VC6 SP4 | 12.00.8xxx |
| msvc6.5 | VC6 SP5 | 12.00.8804 |
| msvc6.5pp | VC6 SP5 + Processor Pack | 12.00.8804 |
| msvc6.6 | VC6 SP6 | 12.00.8804 |

---

## 参考资料

- [kirschju/richheader](https://github.com/kirschju/richheader) - Rich Header prodID 数据库
- [PAL3patch notes](extra/PAL3patch/notes/pal3/notes20170720.txt) - "编译器版本经 rich signature 确定是 VC6 SP0"
- [decomp.me](https://decomp.me) - 老编译器二进制集合 (Docker registry)
