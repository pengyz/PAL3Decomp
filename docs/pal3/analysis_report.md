# PAL3.exe 初步分析报告

## 基本信息

| 属性 | 值 |
|------|------|
| 文件名 | PAL3.exe |
| 文件大小 | ~2.1 MB (脱壳后) |
| 文件类型 | PE32 Executable |
| 加壳状态 | 已脱壳 (原版 StarForce 3.x) |
| 编译器 | MSVC 7.0 (游戏代码) + MSVC 7.1 链接器 (VS2003) |
| 图形 API | DirectX 9 (D3D9) |
| 音频 | Miles Sound System (Mss32.dll) |
| 视频 | Bink Video (binkw32.dll) |
| 脚本 | SCE 字节码虚拟机 (~140 操作码) |

## 依赖分析

### DLL 依赖
- **gbengine.dll** - 游戏引擎核心 (1019 导出函数)
- **topo.dll** - 数学库 (100 导出函数)
- **Mss32.dll** - Miles Sound System
- **binkw32.dll** - Bink Video
- **ijl15.dll** - Intel JPEG Library
- **Windows 系统 DLL** - kernel32, user32, gdi32, advapi32, etc.

### 静态链接库
- **D3DX9.lib** (DirectX SDK Summer 2003) - 3D 数学和工具库
- **C Runtime Library** (MSVCRT) - C 标准库

## 预估函数数量

基于同类项目和文件大小分析：
- **预计总函数**: 3000-5000
- **游戏逻辑**: ~2000-3000 (需要反编译)
- **CRT/库函数**: ~500-800 (识别即可)
- **D3DX 函数**: ~200-400 (静态链接)
- **Thunks/跳转**: ~100-200

## 已知技术细节

### 编译选项 (从 Rich Header)
- **/O2** - 最大速度优化
- **/EHsc** - C++ 异常处理
- **/GR** - RTTI 启用
- **/MD** - 动态运行时库
- **/Gy** - 函数级链接

### 内存布局 (从 PE Header)
- **Image Base**: 0x00400000
- **Entry Point**: 需要Ghidra分析确认
- **.text section**: 代码段
- **.rdata section**: 只读数据
- **.data section**: 可写数据

## 已知模块架构

### 游戏逻辑层 (PAL3.exe 核心)
- **战斗系统** - 回合制战斗框架
- **剧情系统** - 场景管理、NPC、对话
- **UI 系统** - 菜单、对话框、HUD
- **脚本系统** - SCE VM 执行引擎
- **存档系统** - 游戏数据序列化

### 引擎层 (通过 gbengine.dll)
- **渲染子系统** - DirectX 9 渲染, 场景树, 灯光
- **资源管理** - 模型, 纹理, 动画加载
- **输入管理** - 键盘, 鼠标, 游戏手柄
- **音频子系统** - Miles Sound System 整合
- **文件系统** - CPK 存档解析

### 数学库 (通过 topo.dll)
- **向量运算** - 3D 向量 (gbVec3D)
- **矩阵运算** - 变换矩阵 (gbMatrix4)
- **四元数** - 旋转表示 (gbQuaternion)
- **拓扑结构** - 网格数据结构 (TopoGeom)

## Phase 0 基础设施状态

| 工具 | 状态 | 说明 |
|------|------|------|
| CMake 编译系统 | ✅ 就绪 | PAL3.exe stub 编译成功 |
| 导入库 | ✅ 就绪 | topo.lib + gbengine.lib (1119 导出总数) |
| 字节对比工具 | ✅ 就绪 | tools/compare_exe.py |
| 进度跟踪 | ✅ 就绪 | tools/progress_pal3.py |
| 函数分类器 | ✅ 就绪 | tools/classify_functions.py |
| Ghidra 导出脚本 | ✅ 就绪 | tools/ghidra/export_functions.py |
| 测试框架 | ✅ 就绪 | 15/15 测试通过 |
| Ghidra 分析 | ⏳ 待完成 | 需要手动 GUI 操作或自动化脚本 |

## 脱壳状态

**重要**: PAL3.exe 原版用 StarForce 3.x 加壳，需要脱壳后才能分析。

脱壳工具和资源:
- **PAL3patch** 项目包含脱壳工具 (`extra/PAL3patch/extra/unpack/`)
- **脱壳步骤**:
  1. 准备原始 PAL3.exe (已脱壳)
  2. 放入 `original/PAL3.exe`
  3. Ghidra 可直接分析脱壳版本

**参考文档**: `docs/unpacking.md` - StarForce 脱壳完整指南

## 逆向工程进度

| 阶段 | 优先级 | 依赖 | 状态 |
|------|--------|------|------|
| Phase 0: 基础设施 | 最高 | 无 | ✅ 95% 完成 |
| Phase 1: 程序框架 | 高 | Phase 0 | ⏳ 待开始 |
| Phase 2: 核心系统 | 中 | Phase 1 | ⏳ 待开始 |
| Phase 3: 完整实现 | 低 | Phase 2 | ⏳ 待开始 |

## 参考资源

### 社区项目
- **PAL3patch** (zhangboyang) - C 语言补丁工具，包含大量 RE 数据
  - 详细结构定义: `extra/PAL3patch/notes/pal3/`
  - 脱壳工具: `extra/PAL3patch/extra/unpack/`
  
- **OpenPAL3** (dontpanic92) - Rust 重实现项目
  - 文件格式解析器: `/tmp/OpenPAL3/yaobow/shared/src/`
  - SCE 脚本虚拟机: `/tmp/OpenPAL3/yaobow/shared/src/scripting/sce/`

### 文件格式文档
- `docs/file_formats.md` - CPK, SCN, SCE 二进制格式说明
- `docs/sce_opcodes.md` - SCE 虚拟机完整操作码表
- `docs/community_structs.md` - 已知结构体定义表

### 编译配置
- `build/project_config.json` - 项目元数据
- `include/pal3_config.h` - 编译器/平台宏定义

## 下一步行动计划

### 即时任务
1. ✅ 创建 Phase 0 基础设施
2. ⏳ 运行 Ghidra GUI 分析
3. ⏳ 执行导出脚本获取函数列表
4. ⏳ 运行分类器生成优先级队列

### Phase 1 计划 (程序框架)
1. 实现主程序入口点 (_main/WinMain)
2. 初始化全局状态
3. 加载核心系统 (gbengine, topo)
4. 游戏循环框架
5. 错误处理和清理

### 质量保证
- 每个函数实现后进行字节对比
- 保留 Ghidra 反编译结果用于验证
- 逐步提高覆盖率和匹配度

---

*最后更新: 2026-05-01*  
*下次审查: Phase 0 完成后*
