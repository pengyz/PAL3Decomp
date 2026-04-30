# PAL3.exe 脱壳指南

## 工具来源

已将 PAL3patch 项目添加为 git submodule:
```bash
git submodule add https://github.com/zhangboyang/PAL3patch.git extra/PAL3patch
```

脱壳工具位于: `extra/PAL3patch/extra/unpack/pal3/`

## 所需文件

根据 `extra/PAL3patch/extra/unpack/pal3/md5sum.txt`，需要以下文件:

### 原始游戏文件（需要从正版游戏获取）
- `PAL3.exe` (MD5: 52ca2bfcb773714f55b5e1c951653a27)
- `gbengine.dll` (MD5: ce0213b1734f8cae1e1a0ea5213dd03f)
- `topo.dll` (MD5: fce747b978f3130810d47eadf960ee13)
- `binkw32.dll` (MD5: ae21d55ba68440490d9cbf2fd4130928)
- `Mss32.dll` (MD5: 2552e9cffd352ff5b939d88af6fc6b61)
- `ijl15.dll` (MD5: 1aa06c81a0621e277e755b965b5e4b5f)
- `pal3unpack.dll` (免CD补丁, MD5: f1f500d877baabd03e04d0c69dbc5633)
  - 注意：这是将免CD补丁 `pal3.dll` 重命名为 `pal3unpack.dll`

### 编译工具库文件
- `KERNEL32.lib` (MD5: b5f6e0964e7907b9b82f9530acebfb6d) - 来自 VC6
- `USER32.LIB` (MD5: 9cd97635b91d15b8654f27a8b4d3c6a6) - 来自 VC6
- `ADVAPI32.LIB` (MD5: d0dcedabbd3843b5b1d6fc7552e91c04) - 来自 VC6
- `WINMM.LIB` (MD5: 5a8ef13965d1d019f18a4058c9e32c15) - 来自 VC6
- `dinput8.lib` (MD5: 84de6d92f62cca5c65d9b84a07eb3e1d) - 来自 DXSDK

## 所需工具

1. **DUMPBIN** - 来自 Visual C++ 6.0 (版本 6.00.8447 已测试)
2. **LIB files** - 来自 VC6 和 DirectX SDK (dxsdk_sum2004.exe 已测试)
3. **MinGW GCC** - gcc 3.4.2 (来自 Dev-C++ 4.9.9.2 已测试)

## 脱壳步骤

### 1. 编译脱壳工具
```bash
cd extra/PAL3patch/extra/unpack/pal3
make
```

### 2. 准备文件
将 `md5sum.txt` 中列出的所有文件复制到 `extra/PAL3patch/extra/unpack/pal3/` 目录

注意事项:
- 免CD补丁需要重命名: `pal3.dll` → `pal3unpack.dll`
- 所有文件的 MD5 必须匹配 `md5sum.txt` 中的值

### 3. 执行脱壳
```bash
cd extra/PAL3patch/extra/unpack/pal3
unpack.bat
```

### 4. 获得结果
脱壳完成后会生成 `pal3unpacked.exe`

## 脱壳原理

脱壳流程（通过 `unpack.bat` 执行）:

1. **lshint** - 为各个 DLL/LIB 生成提示信息
2. **pal3dump.dll** - 注入到 PAL3.exe，在运行时转储解密后的内存
3. **PAL3analyse** - 分析转储的内存镜像
4. **PAL3fixdump** - 修复转储数据
5. **PAL3mkimport** - 重建导入表
6. **PAL3makepe** - 生成最终的 PE 文件

## 注意事项

- 这是针对 **StarForce 加壳版本** 的脱壳工具
- 需要原始游戏文件（不在 git 中）
- 脱壳后的 `pal3unpacked.exe` 应放在 `original/` 目录供后续反编译使用

## 下一步

将脱壳后的 `pal3unpacked.exe` 复制到项目的 `original/` 目录:
```bash
mkdir -p original
cp extra/PAL3patch/extra/unpack/pal3/pal3unpacked.exe original/PAL3.exe
```

然后可以开始用 Ghidra 分析和反编译。
