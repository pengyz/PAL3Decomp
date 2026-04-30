# PAL3.exe 脱壳指南

## 概述

PAL3.exe 使用 StarForce 保护方案加壳。加壳后的 PE 结构包含 `.sforce` 和 `.brick` 段，
原始代码在运行时由 `pal3.dll`（StarForce 解密器）动态解密。

要进行反编译，必须先获得脱壳后的二进制文件。

## 脱壳后 PE 信息

| 属性 | 值 |
|------|------|
| Image Base | `0x00400000` |
| OEP (原始入口点) | `0x0055507C` |
| .text 大小 | `0x168018` (1,474,584 bytes) |
| .rdata 大小 | `0x0151F2` (86,514 bytes) |
| .data 大小 | `0x08C000` (573,440 bytes) |
| .rsrc 大小 | `0x0053CA` (21,450 bytes) |
| 导入 DLL | ADVAPI32, binkw32, dinput8, gbengine, KERNEL32, USER32, WINMM |

## 段布局（脱壳后）

```
Section   VA Range                  Size       Flags
.text     0x00401000 - 0x00569018   0x168018   Execute+Read (代码)
.rdata    0x0056A000 - 0x0057F1F2   0x0151F2   ReadOnly (只读数据/IAT)
.data     0x00580000 - 0x0060C000   0x08C000   ReadWrite (全局数据)
.rsrc     0x01897000 - 0x0189C3CA   0x0053CA   ReadOnly (资源)
```

## 脱壳方法

脱壳基于 PAL3patch 项目的 `extra/unpack/pal3/` 工具链，需要在 **Windows** 上执行。

### 原理

StarForce 保护的工作方式：
1. 游戏启动时加载 `pal3.dll`（StarForce 解密存根）
2. `pal3.dll` 解密 `.text`/`.rdata`/`.data` 段到内存
3. 向 `.text` 中注入约 40 个 JMP 跳板（指向 DLL 内的代码）
4. 动态解析所有导入函数（绕过正常 IAT）
5. 跳转到 OEP 开始执行游戏代码

脱壳流程的关键思路：**让 StarForce 自己完成解密，然后在它跳转到 OEP 之前 dump 内存**。

### 详细步骤

#### 前置条件

- Windows 系统（虚拟机也可以）
- MinGW GCC（推荐 Dev-C++ 4.9.9.2 中附带的 GCC 3.4.2）
- DUMPBIN.exe（来自 VC6 或更高版本的 Visual Studio）
- 原版 PAL3.exe（MD5: `52ca2bfcb773714f55b5e1c951653a27`）
- 破解补丁 pal3.dll，需重命名为 `pal3unpack.dll`（MD5: `f1f500d877baabd03e04d0c69dbc5633`）
- VC6 的 LIB 文件：ADVAPI32.LIB, KERNEL32.lib, USER32.LIB, WINMM.LIB
- DirectX SDK (Summer 2004) 的 dinput8.lib
- 游戏 DLL：Mss32.dll, binkw32.dll, gbengine.dll, ijl15.dll, topo.dll

#### 执行流程

```
1. make                  # 编译所有工具
2. lshint *.lib *.dll    # 提取导入提示值
3. copy pal3dump.dll → pal3.dll  # 用 dump DLL 替代 StarForce 存根
4. 运行 PAL3.exe         # StarForce 解密后，pal3dump.dll 拦截并 dump
   → 输出: dump.text, dump.rdata, dump.data, dump.rsrc
5. PAL3analyse           # 分析 pal3unpack.dll 中的补丁/导入数据
   → 输出: analysis.txt
6. PAL3fixdump           # 修复 JMP 跳板、注入函数、IAT 引用
   → 输出: dump.text.fixed, dump.rdata.fixed
7. PAL3mkimport          # 重建导入表
   → 输出: iat.bin, import.bin
8. PAL3makepe            # 组装最终 PE
   → 输出: PAL3unpacked.exe
```

## 对于本项目的实际操作

### 方案 A：使用 PAL3patch 工具脱壳（推荐）

如果你有 Windows 环境，可以直接使用 PAL3patch 的脱壳工具：

```bash
cd /tmp/PAL3patch/extra/unpack/pal3/
# 按上述步骤操作，获得 PAL3unpacked.exe
# 将脱壳后的文件放到游戏目录或 original/ 下
```

然后在 `local_config.json` 中指定脱壳后的 exe：

```json
{
  "game_dir": "/path/to/game",
  "exe_name": "PAL3unpacked.exe"
}
```

### 方案 B：使用已有脱壳版本

如果你有已脱壳的 PAL3unpacked.exe，直接配置即可。

### 方案 C：暂时先分析 gbengine.dll 和 topo.dll

这两个 DLL **没有加壳**，可以直接用 Ghidra 分析。其中：
- `gbengine.dll` (1.2 MB) - 引擎核心，1019 个 C++ 导出函数（有符号名）
- `topo.dll` (104 KB) - 数学/拓扑库，100 个导出函数

**建议先从这两个 DLL 开始**，因为：
1. 无需脱壳
2. 有导出符号名（C++ mangled names 可以还原函数名和参数类型）
3. 是 PAL3.exe 的主要依赖，先理解引擎有助于后续反编译 exe

## 不需要脱壳的目标

| 文件 | 大小 | 描述 | 导出函数 |
|------|------|------|----------|
| gbengine.dll | 1.2 MB | GameBryo 引擎（渲染、场景、动画等） | 1019 个 |
| topo.dll | 104 KB | 数学/几何库（矩阵、向量、碰撞等） | 100 个 |

这些是反编译的第一优先目标。

## 验证脱壳结果

脱壳后的 exe 应满足：
- Entry Point 为 `0x0055507C`（而非加壳版的 `0x0189D000`）
- 有正常的 `.text`/`.rdata`/`.data`/`.rsrc` 四段
- 导入表包含 7 个 DLL
- 文件大小约 2.2 MB（而非加壳版的 1.8 MB）
- 可以直接在 Ghidra 中正常反编译
