# PAL3.exe 脱壳完成记录

## 脱壳日期
2026-05-01

## 输入文件
- **源文件**: Steam 版 PAL3.exe (E:\Program Files (x86)\Steam\steamapps\common\PAL3\)
- **MD5**: 52ca2bfcb773714f55b5e1c951653a27 (StarForce 加壳)
- **大小**: 1.8 MB

## 输出文件
- **脱壳文件**: original/PAL3.exe
- **MD5**: a9ec0cc6730b68b39f02c58d646c5984
- **大小**: 2.1 MB

## 脱壳工具链

### 编译器
- **MinGW GCC**: 13.2.0 (i686-posix-dwarf-rev1)
- **TCC**: 0.9.27 (用于部分工具)
- **DUMPBIN**: VS2022 MSVC 14.43.34810.0

### 脱壳工具（已编译）
1. **lshint.exe** - 生成导入表 hint 文件
2. **PAL3dump.dll** - 注入到游戏进程，转储解密后的内存
3. **PAL3analyse.exe** - 分析转储的内存镜像
4. **PAL3fixdump.exe** - 修复转储数据中的跳转和函数调用
5. **PAL3mkimport.exe** - 重建导入表
6. **PAL3makepe.exe** - 生成最终的 PE 可执行文件

### 辅助文件
- **pal3unpack.dll** - 免CD补丁（MD5: f1f500d877baabd03e04d0c69dbc5633）
- **hint 文件**: advapi32.lib, kernel32.lib, user32.lib, winmm.lib, dinput8.lib, gbengine.dll, binkw32.dll

## 脱壳流程

1. **准备环境**
   - 安装 MinGW GCC (便携版)
   - 准备 DUMPBIN (VS2022)
   - 复制游戏文件和库文件

2. **生成 Hint 文件** (使用 lshint.exe + DUMPBIN)
   ```
   lshint.exe advapi32.lib  → 772 functions
   lshint.exe kernel32.lib  → 1353 functions
   lshint.exe user32.lib    → 781 functions
   lshint.exe winmm.lib     → 191 functions
   lshint.exe dinput8.lib   → 1 function
   lshint.exe gbengine.dll  → 1019 functions
   lshint.exe binkw32.dll   → 81 functions
   ```

3. **内存转储** (PAL3dump.dll 注入)
   - 复制 PAL3dump.dll 为 pal3.dll
   - 运行 PAL3.exe（游戏加载 pal3.dll）
   - PAL3dump.dll 加载 pal3unpack.dll 并转储内存
   - 生成文件:
     - dump.text (1.5 MB) - 代码段
     - dump.rdata (85 KB) - 只读数据段
     - dump.data (560 KB) - 数据段
     - dump.rsrc (21 KB) - 资源段
     - dump.summary.txt - 段信息摘要

4. **分析转储** (PAL3analyse.exe)
   - 检测 DLL 基址: 0x10000000
   - 分析段结构
   - 输出: analyse OK!

5. **修复转储** (PAL3fixdump.exe)
   - 修复跳转指令（JMP）
   - 修复函数调用
   - 重定位导入函数
   - 生成 dump.text.fixed, dump.rdata.fixed

6. **重建导入表** (PAL3mkimport.exe)
   - 导入 7 个库，共 368 个函数:
     - ADVAPI32.dll: 6 functions
     - BINKW32.DLL: 10 functions
     - DINPUT8.DLL: 1 function
     - GBENGINE.DLL: 249 functions
     - USER32.DLL: 34 functions
     - WINMM.dll: 1 function
     - kernel32.dll: 67 functions
   - 生成 import.dat, importtable.bin

7. **生成 PE 文件** (PAL3makepe.exe)
   - 从原始 PAL3.exe 提取 DOS 头部
   - 组装所有段
   - 写入导入表
   - 输出 pal3unpacked.exe

## 验证

脱壳后的文件结构：
```
PAL3unpacked.exe (2.1 MB)
├── .text   段: 1.4 MB (代码)
├── .rdata  段: 86 KB (只读数据)
├── .data   段: 560 KB (数据)
└── .rsrc   段: 21 KB (资源)
```

## 已知问题

- 游戏运行时出现 "Reset3DEnvironment Error"（DirectX 初始化错误），但不影响脱壳流程
- 内存转储在游戏崩溃前已完成

## 下一步

现在可以使用 Ghidra 分析 `original/PAL3.exe` 进行反编译工作。
