# PAL3 Workaround 记录

迭代中发现的问题及临时解决方案。`/pal3-verify` 时检查并修复。

---

## [0x004B65F0] RenderTarget3_Init — gbEffectMgr::NewRenderEffect 不在 gbengine.lib
- **问题**: `gbEffectMgr::NewRenderEffect` 符号不在 `lib/gbengine.lib` 中，链接失败
- **Workaround**: 在 `src/pal3/gamebase/GfxHelper.cpp` 中提供空 stub: `return 0;`
- **影响**: 运行时不会创建 glow/geom 渲染效果
- **正确修复**: 检查 gbengine.dll 导出表中该函数的 mangled name（可能是不同的 name mangling），或确认是通过 vtable 间接调用。若是 vtable 调用则不需要直接链接。
- **迭代**: #15

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
