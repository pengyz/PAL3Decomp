# PAL3 Workaround 记录

迭代中发现的问题及临时解决方案。`/pal3-verify` 时检查并修复。

---

## [已修复] [0x004B65F0] RenderTarget3_Init — gbEffectMgr::NewRenderEffect
- **修复**: 从 `src/gbengine/gbengine.def` 重新生成 `lib/gbengine.lib`，包含完整导出
- **根因**: lib/gbengine.lib 是从不完整的 .def 生成的，缺少部分导出符号
- **额外修复**: gbRenderEffect 必须声明为 `class`（不是 struct），否则 mangled name 不匹配
- **迭代**: #27 修复

## [0x004226F0] GetActiveUIScene — 依赖绝对地址常量
- **问题**: 函数返回 `0x78764 * (dword_D8BBEC == 1) + 0xC22BE8`，使用编译时硬编码的全局对象地址
- **Workaround**: 保留 stub `return 0;`
- **影响**: 所有依赖 UI 场景对象的函数无法正确工作
- **正确修复**: 在 globals.cpp 中定义对应全局对象（g_UISceneNormal, g_UISceneCombat），通过符号引用而非硬编码地址实现。需要确定这两个对象的结构体类型和大小。
- **迭代**: #12

## [全局] CScreenMode 结构体缺失
- **问题**: CScreenMode 不在 PAL3A.PDB 中（PAL3 特有类），无法从 PDB 获取完整成员定义。IDA 反编译显示 this 偏移从 +0x04 到 +0x380000+（显然是多个不同类被混淆到同一地址范围）
- **Workaround**: 对 CScreenMode 区域的函数，仅实现不依赖偏移的（GetInstance、thunk），需要偏移的标记为 stub
- **影响**: 0x53C2D0-0x53EA60 范围约 13 个 frontier 函数无法实现
- **正确修复**: 在 IDA 中细分该地址范围，按 this 指针来源将函数分组到不同类（DisplayConfig, AudioContext, CScreenMode 本体等）。逐个类定义结构体。
- **迭代**: #11+

## [全局] gbGfxManager 偏移未完全验证
- **问题**: gbGfxManager_Partial 中的 pEffectMgr (+0xC8) 和 pMatrixStack (+0xD4) 偏移来自 PAL3A.PDB，但 PAL3 的 gbGfxManager 布局可能不同（不同编译版本）
- **Workaround**: 暂时信任 PDB 偏移（两个版本同源代码、同编译器，布局一致的可能性高）
- **影响**: 如果偏移不一致，使用这些成员的函数字节匹配会失败
- **正确修复**: 通过 `pal3_compare.py` 验证编译产物字节，如果匹配则偏移正确
- **迭代**: #13

## [全局] PAL3.cpp 中 thiscall 方法被误声明为 extern "C" __cdecl
- **问题**: IDA 反编译 PAL3::Create/Update/Render 时，未识别出部分调用通过 ecx 传递 this
- **影响**: sub_41C630, sub_41CA90, sub_41BE80 等实际是 __thiscall 但被当作 __cdecl
- **Workaround**: 实现侧用 __cdecl 包装函数内部访问 g_pCamera
- **正确修复**: 修改 PAL3.cpp，把这些调用改为 `((CameraCtrl*)g_pCamera)->Method(arg)`
- **迭代**: #28, #29

## [全局] extern "C" 清理 — 需要类型统一后才能执行
- **问题**: 500+ 处 extern "C" 不必要，阻止正确的 C++ OOP 使用
- **障碍**: 全局变量在不同 TU 中有不同类型 (如 g_pGfxManager 是 int 还是 gbGfxManager_Partial*)
- **前置任务**: 
  1. 创建 pal3_globals.h 统一类型声明
  2. 把 g_pGfxManager 等统一为正确的指针类型
  3. 解决 WinMain.cpp 的 char[] vs const char[] 不一致
- **正确修复**: 先做类型统一重构，再批量去 extern "C"
- **迭代**: 尝试于 #30 但因类型冲突回退
