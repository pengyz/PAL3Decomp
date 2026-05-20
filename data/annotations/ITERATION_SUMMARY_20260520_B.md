# PAL3 标注迭代总结 - 2026-05-20 第二轮

## 概述

本轮迭代聚焦于系统性类型错误修正，特别是 offset 0 字段的类型问题。

## 完成工作

### 1. vfptr 类型修正（batch: 6 类）

修正虚函数表指针从错误的 `float` 类型改为 `int`：

| 类名 | 字段名 | 修改 | 置信度 |
|------|--------|------|--------|
| UIWnd | vfptr | float→int | 95 |
| UIListBox | _todo_000 | 删除（继承自 UIWnd） | 95 |
| UITitle | vfptr | float→int | 95 |
| SceneObj | vfptr | float→int | 95 |
| RoleSystem | m_pVtable | float→int | 95 |
| CGameData | _vftable | float→int | 95 |
| gbFileStream | vfptr | float→int | 95 |

**证据**: 字段名包含 vfptr/vtable/vftable + offset 0 在 C++ 类中的语义位置

### 2. 命名约定驱动类型修正（batch: 5 字段）

基于 MSVC 匈牙利命名约定修正明显的类型错误：

| 类名 | 字段名 | 前缀 | 修改 | 置信度 |
|------|--------|------|------|--------|
| ScriptSystem | m_nSlotID | m_n | float→int | 70 |
| PalScriptMgr | m_bGetSceneScript | m_b | float→unsigned char | 70 |
| RenderTarget | m_iMode | m_i | float→int | 70 |
| CScreenMode | m_pEnumeration | m_p | float→void* | 70 |
| CUtil | m_bCanWarp | m_b | float→unsigned char | 70 |

**命名约定参考**:
- `m_n*`, `m_i*` → int（number, integer）
- `m_b*` → unsigned char（boolean）
- `m_p*` → pointer（具体类型或 void*）

## 统计数据

- 总结构体数: 680
- 已修正 vfptr 类型: 33 个类
- offset 0 仍为 float: 30 个字段
- offset 0 正确类型: 449 个字段

## 发现的问题

### 1. FPU_post_reattrib 工具误判

Source 标记为 `A:FPU_post_reattrib_*` 的字段存在系统性误判，将非浮点类型错误标记为 float：
- 虚函数表指针（vfptr）被误认为 float
- 整数字段（m_n*, m_i*）被误认为 float
- 布尔字段（m_b*）被误认为 float
- 指针字段（m_p*）被误认为 float

**根本原因**: 该工具可能基于指令中的 FPU 操作码（D9/DD）判断字段类型，但未考虑：
1. FPU 指令可能访问其他字段或全局变量
2. 整数寄存器操作（mov/test）无法区分 int 和 float（IEEE 754 正浮点 DWORD > 0）

### 2. IDA query tools 输出可靠性问题

运行了 `query_class_full.py` 和 `query_highref_fields.py`，输出文件已生成但发现：
- **字段偏移不可信**: decomp 中的 `this->_todo_050` 不一定对应真实 offset 0x50
- **原因**: 如果 IDB 中结构体布局不正确，Hex-Rays 推断的偏移会漂移
- **示例**: UIListBox._todo_050 在 decomp 中被各种 cast（UIMap, UIWnd, RoleCameraCtrl），但实际上 offset 80 在 UIWnd 基类中是 m_fScaleY

**结论**: IDA query tools 的输出只能用于**语义推断**（字段用途），不能直接用于**偏移/类型修正**。必须通过二进制指令验证。

### 3. 剩余的 offset 0 float 字段分类

30 个仍为 float 的 offset 0 字段中：
- **15 个**: 可能是正确的 float（fWaitTime, fov, AlphaSpeed 等）
- **8 个**: 可能是正确的向量分量（x, y, z, u, v 等）
- **2 个**: 矩阵/通用字段（_11, val），需进一步调查
- **5 个**: 含义不明（hotspot, dist, m_snaph 等），需进一步调查

## 提交记录

1. `96202fcf` - iter(annotations): vfptr 类型修正（batch: 6 类）
2. `bca036ff` - iter(annotations): 命名约定驱动类型修正（batch: 4 字段）
3. `7682cd4a` - iter(annotations): CUtil.m_bCanWarp float→unsigned char

## 下一步建议

### 短期（本迭代内）

1. **验证编译效果**: 
   ```bash
   python pipeline/cli.py init --force
   python pipeline/cli.py export
   python pipeline/cli.py codegen all
   python pipeline/cli.py compile
   ```
   查看 vfptr 和命名约定修正是否改善了编译结果

2. **处理剩余明显的类型错误**:
   - PAL3 结构体有多个指针字段被错误标记为 float/short
   - 其他类中的 m_p*/m_n*/m_b* 前缀字段

### 中期（后续迭代）

1. **二进制验证优先**:
   - 对修改过的字段，使用 verify_offset.py 或直接读取二进制指令验证
   - 特别是有全局实例的类（SceneMgr, CGameData, PAL3 等）

2. **IDB 布局重建**:
   - 当 annotations 有重大改进后，运行 `init --force` 完全重建 IDB
   - 重新 export 后，IDA query tools 的输出会更可靠

3. **聚焦核心类**:
   - Camera, SceneMgr, CCBStage 系列
   - 这些类的字段命名和类型精化对整体代码质量影响最大

## 经验教训

1. **命名约定是强信号**: MSVC 匈牙利命名（m_n/m_i/m_b/m_p）可作为中等置信度（70）的类型推断依据
2. **Source 标记不是真相**: `FPU_post_reattrib` 等自动标注结果需人工复核
3. **IDA decomp 偏移需验证**: 结构体布局错误时，decomp 中的字段偏移不可信
4. **继承字段不重复**: 子类不应重复定义基类的 offset 0（vfptr）

## 工具链状态

- **check_annotations.py**: ✓ 正常，0 errors, 2 warnings
- **query_todo_fields.py**: ✓ 完成（输出 264K）
- **query_highref_fields.py**: ✓ 完成（输出 2.0K），但数据可靠性受限
- **query_class_full.py**: ✓ 完成（输出 29K），但偏移不可信
- **verify_offset.py**: 未充分使用（仅限全局实例）
