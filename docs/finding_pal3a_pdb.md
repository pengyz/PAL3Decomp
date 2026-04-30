# PAL3A.PDB 获取指南

## 问题

Steam 版的 PAL3A（问情篇）已移除 PDB 调试符号文件。但根据 PAL3patch 作者的笔记，原版光盘应该包含 PAL3A.PDB。

## PDB 文件信息

- **文件名**: PAL3A.PDB
- **作用**: 包含 PAL3A.exe 的完整调试符号，包括：
  - 所有函数名和地址
  - 所有类型定义（结构体、类、枚举）
  - 全局变量名和地址
  - 源文件路径和行号
- **大小**: 约 10-20 MB（估计）
- **编译器**: MSVC 6.0 或 7.0

## 可能的获取途径

### 1. 原版光盘

PAL3A 的原版光盘（非 Steam 版）应该包含 PAL3A.PDB。如果你有光盘或光盘镜像：

```
检查路径：
- 光盘根目录/PAL3A.PDB
- 安装目录下
```

### 2. 旧版本安装包

早期的数字发行版本可能包含 PDB：
- 方正、目标等早期数字版本
- 国内游戏平台的早期版本

### 3. 反编译社区

可能的资源：
- 游侠网（ali213.net）- 仙剑系列 MOD 区
- 3DM 论坛
- 仙剑论坛/贴吧

### 4. 在线搜索关键词

中文搜索：
```
PAL3A.PDB 下载
仙剑奇侠传3外传 PDB
问情篇 调试符号
PAL3A 开发版
```

英文搜索：
```
"PAL3A.PDB" download
Chinese Paladin 3A PDB symbols
```

### 5. 联系开发者社区

- **PAL3patch 作者** (zhangboyang) - GitHub Issues
- **OpenPAL3 项目** - 可能有人保存了 PDB
- **仙剑 modding 社区**

## 验证 PDB 文件

找到 PDB 后，验证其有效性：

```powershell
# 使用 DBH 验证
dbh -v PAL3A.pdb

# 或使用 dumpbin
dumpbin /headers PAL3A.pdb
```

预期输出应包含：
- 大量函数符号
- 类型信息
- 全局变量

## 替代方案

如果实在找不到 PDB：

### 方案 1: 部分信息仍然可用

PAL3patch 笔记中已经记录了很多从 PDB 提取的信息：
- `extra/PAL3patch/notes/pal3/known_classes.txt` - 已知类列表
- 笔记中的结构体定义
- 函数名和地址

### 方案 2: 使用 RTTI 信息

PAL3A.exe 和 gbengine.dll 包含 RTTI 信息，可以恢复：
- 类名
- 虚函数表
- 类层次结构

使用 Ghidra 或 IDA Pro 的 RTTI 分析功能。

### 方案 3: 继续反编译 PAL3

即使没有 PDB，PAL3 的反编译仍然可以进行：
- topo.dll 已经在反编译中（27% 完成）
- PAL3.exe 已脱壳，可以直接分析
- gbengine.dll 虽然没有 PDB，但有 RTTI 和导出函数

## 下一步

1. **检查是否有原版光盘** - 这是最可靠的来源
2. **在社区论坛发帖询问** - 可能有人保存了 PDB
3. **联系 PAL3patch 作者** - 询问是否可以分享 PDB
4. **继续反编译工作** - 即使没有 PDB 也可以进行

## 更新记录

- 2026-05-01: 确认 Steam 版 PAL3A 不包含 PDB
- 需要寻找原版光盘或其他来源

## 参考

- PAL3patch notes/pal3/notes20160711.txt - 首次提到 PAL3A.PDB
- PAL3patch notes/pal3/notes20160813.txt - 使用 PDB 的方法
