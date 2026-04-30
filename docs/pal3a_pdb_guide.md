# PAL3A.PDB 使用指南

## 概述

**重要发现**: 仙剑奇侠传3外传·问情篇（PAL3A）的发行版附带了 **PAL3A.PDB** 调试符号文件，这是一个巨大的礼物！

这个 PDB 文件包含：
- 完整的类型定义（结构体、类、枚举）
- 函数名称和地址
- 全局变量名称和地址
- 源文件路径和行号映射
- 成员变量的偏移和类型

## PAL3 vs PAL3A 的关系

仙剑3（PAL3）和问情篇（PAL3A）都使用 **GBENGINE** 引擎：

| 组件 | PAL3 | PAL3A | 关系 |
|------|------|-------|------|
| gbengine.dll | 无 PDB | **有 PDB** (在 PAL3A.PDB 中) | 几乎完全相同 |
| topo.dll | 无 PDB | 无 PDB | 相同 |
| 主程序 | PAL3.exe (无 PDB) | PAL3A.exe (有 PDB) | 游戏逻辑有差异 |

**关键点**: PAL3A 的 gbengine.dll 与 PAL3 的 gbengine.dll **几乎完全相同**，因此 PAL3A.PDB 中的 gbengine 符号可以直接用于反编译 PAL3 的 gbengine.dll！

## 编译器和 SDK 版本

根据 PAL3patch 笔记：
- **GBENGINE.DLL**: DirectX SDK Summer 2003
- **PAL3.EXE**: 可能是 dx90asdk.exe 或 Summer 2003
- **D3DX9.LIB**: 静态链接到 gbengine.dll 和 PAL3.exe

DXSDK Summer 2003 SHA1 校验和：
```
86eee764eac5d5a0f0864d6ba10d4061184f86ef  dx90update_extras.exe
51a0edf2859177445279993efb5238b9b157fe52  dx90update_managed.exe
38a7581d727503f0401cfd2a3bf084418e7eda44  dx90updatesdk.exe
```

## PDB 查看工具

### 1. PDB Explorer (推荐用于结构体)
- **功能**: 将 PDB 中的数据结构导出为 C/C++ 代码
- **下载**: http://blog.titilima.com/pdbexp.html
- **依赖**: VC2005 运行库 + msdia80.dll
- **注册 msdia80.dll** (必须用 32位):
  ```cmd
  C:\Windows\SysWOW64\regsvr32.exe "C:\Program Files (x86)\Common Files\microsoft shared\VC\msdia80.dll"
  ```

### 2. Microsoft CVDUMP (官方工具)
- **功能**: 微软官方 PDB 转储工具
- **下载**: https://github.com/Microsoft/microsoft-pdb/blob/master/cvdump/cvdump.exe

### 3. DBH (用于全局变量和函数)
- **功能**: 
  - 查看全局变量名称和大小: `dbh -v PAL3A.pdb enum > enum.txt`
  - 查看函数地址和行号: `dbh -v PAL3A.pdb`
  - 推测变量类型: `type SYMBOL` 查看符号大小，`type TYPENAME` 查看类型大小
- **来源**: Windows SDK 示例代码
- **文档**: https://msdn.microsoft.com/en-us/library/windows/hardware/ff540441%28v=vs.85%29.aspx

### 4. DebugInfosViewer
- **功能**: 导出为 HTML，方便搜索函数原型
- **后处理命令**:
  ```bash
  grep 'Section Index' functions.html | grep -v '^.*TABLE BORDER.*TABLE BORDER.*$' | \
    sed -r -e 's/<\/{0,1}(TD|TR|TABLE)>//g' -e 's/<TABLE BORDER="1">.*$//g'
  ```

## 在 IDA Pro 中使用 PDB

### 导入 PDB 到 gbengine.dll

1. **File → Load File → PDB File** 导入 PAL3A.PDB
2. 效果：反编译器生成的代码更漂亮，有完整类型信息

### 修正 DirectX 函数显示

PDB 导入后，DirectX 函数调用需要手工设置才能显示函数名。

以 IDirect3D9 为例：

```
步骤：
1. Local Types 中，将 IDirect3D9 重命名为 IDirect3D9_cppobj
2. Structures 中，按 Ins 导入标准结构体:
   - IDirect3D9
   - IDirect3D9Vtbl
3. Local Types 中，将 IDirect3D9_cppobj 映射到 IDirect3D9 (Map to another type)
4. Local Types 中，编辑一次 IDirect3D9 (打开编辑窗口并保存，无需修改)
5. 此时反编译器应该可以显示函数名了
```

**效果对比**:

修正前:
```c
v1->lpD3D9->lpVtbl->func_ptr[3](...)
```

修正后:
```c
result = v1->lpD3D9->lpVtbl->CreateDevice(
    v1->lpD3D9,  // this 指针
    *v9,
    *(D3DDEVTYPE *)(v23 + 4),
    v1->hFocusWindow,
    v5,
    (D3DPRESENT_PARAMETERS *)&v1->pPresentParameters,
    &v1->lpD3DDevice9);
```

### 导入 DirectInput8 头文件

IDA Pro 默认没有 DirectInput8A 结构体定义：

```
1. Option → Compiler 设置 Include Directories 为 VC6 的 Include 目录
   例如: C:\VC98\Include;其他...
2. File → Load File → Parse C Header 导入 dinput.h
```

## 在 Ghidra 中使用 PDB

Ghidra 支持直接加载 PDB 文件：

```
1. File → Load PDB File
2. 选择 PAL3A.PDB
3. Ghidra 会自动应用类型信息和函数名
```

## 版本差异注意事项

虽然 PAL3A 的 gbengine.dll 与 PAL3 几乎相同，但仍有细微差别：

### 已知差异
1. **游戏内容变化**: PAL3A 增加了新的剧情和地图
2. **删除的代码**: PAL3A 删除了 PAL3 中的小游戏代码，这些类在 PDB 中找不到
3. **函数优化**: PDB 中有些函数在 PAL3 中未使用，被链接器优化掉了

### 使用建议
1. **优先使用 PDB 的类型信息**: 结构体定义通常完全正确
2. **函数名需要验证**: 对比函数地址，确认匹配
3. **全局变量名可直接使用**: 从 PDB 提取，避免胡乱命名
4. **注意地址偏移**: PAL3 和 PAL3A 的基址可能不同

## 提取 PDB 信息的工作流

### 1. 提取结构体定义
```bash
# 使用 PDB Explorer
1. 打开 PAL3A.PDB
2. 导航到感兴趣的类型
3. 导出为 C/C++ 代码
4. 保存到 include/pal3_structs.h
```

### 2. 提取全局变量
```bash
# 使用 DBH
dbh -v PAL3A.pdb enum > global_vars.txt

# 排序并查找感兴趣的变量
sort global_vars.txt > sorted_vars.txt
grep "gbCamera" sorted_vars.txt
```

### 3. 提取函数信息
```bash
# 使用 DebugInfosViewer 或 DBH
# 获取函数名、地址、参数类型
```

### 4. 应用到反编译

将提取的信息应用到 Ghidra/IDA Pro 中：
1. 导入类型定义
2. 重命名函数
3. 设置函数签名
4. 标注全局变量

## D3DX 静态链接

**重要**: gbengine.dll 静态链接了 D3DX9.LIB，超过一半的代码是 D3DX 库代码！

使用 IDA FLAIR 生成签名：
```bash
1. 从 DirectX SDK Summer 2003 获取 D3DX9.LIB
2. 使用 FLAIR 生成 .sig 文件
3. 在 IDA Pro 中应用签名
4. 大量 D3DX 函数会被自动识别
```

**注意**: SDK 版本必须严格匹配，否则识别率很低。

## 参考资料

来源: PAL3patch 项目 `notes/pal3/` 目录
- `notes20160711.txt` - PDB 工具介绍
- `notes20160813.txt` - IDA Pro 中使用 PDB
- `notes20170112.txt` - DBH 工具使用
- `notes20160717.txt` - PDB 数据验证

## 下一步行动

1. **获取 PAL3A.PDB** (从 PAL3A 游戏目录)
2. **提取 gbengine 类型定义** (用 PDB Explorer)
3. **在 Ghidra 中加载 PDB** (用于 gbengine.dll 反编译)
4. **提取全局变量名** (用 DBH)
5. **导出所有结构体到 `include/gbengine_types.h`**

这将大大加速 gbengine.dll 的反编译进程！
