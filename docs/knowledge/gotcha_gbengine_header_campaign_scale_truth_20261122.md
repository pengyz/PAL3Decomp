# gotcha: gbengine 共享头完成度战役——规模评估的真相修正（2026-11-22）

## 结论：战役原立项前提已过时，真实错误面=13 条 C2039/5 单元

立项记忆（"gbCamera/gbMatrixStack/gbLightObj/gbOBBox 仅前置在树，定义需从
ida_structs 重建，解锁 SceneRenderWithRotation/RenderPost C2039 族"）**与现状不符**：

- gbCamera.h / gbMatrixStack.h 已在早前批次重建（2026-10-06 暴露批1 / 2026-11-18 导入类方法批）；
- gbLightObj/gbOBBox 语料仅指针用法（decl_ptr），无按值布局需求 ⇒ 前置声明已足；
- RenderPost 已在头（2026-10-06）；SceneRenderWithRotation 是唯一真缺口（PAL3 侧扩展方法）。

**普查工具**：`tools/census_gbsdk_header_gap_20261122.py`（四问：Q1 S2 错误面 gb 族归因 /
Q2 使用形态 / Q3 IAT 域归属 / Q4 api.h×共享头方法数差额）。
报告：`data/status/gbsdk_header_gap_20261122.json`。

## Q4 的大差额不等于需求面（ completeness ≠ neededness ）

gbengine_api.h（DLL 导出快照）与共享头的方法数差额很大（gbMatrix4 缺 23、gbQuaternion 缺 19、
gbOBBox 缺 8…），但 **S2 错误面零命中**——PAL3 侧代码不调 DLL 内部方法（矩阵运算等经
free 函数或成员直访），补齐不解锁任何编译错误。第一性口径：**错误面驱动的完备度**，
不是导出表驱动的完备度。导出表差额只在未来出现调用站时才成为需求。

## 本批三个真修（各自独立取证）

1. **gbMatrixStack += `void SceneRenderWithRotation();`**（F70 普通声明——0x52F2E0 在
   PAL3 .text，不在 GBENGINE IAT；体访 this->pMatBuf/ValidFlag=本类字段体证）
2. **CIniFile 成员名对齐注解**：m_pFile/m_nState（人写重建名）→ m_fp/m_bRead
   （structs/CIniFile.json=IDA 真值, size=8）。双管线共享标注律：头随注解。
   改名前查重：decomp m_pFile=0 站 ⇒ 改名安全。
3. **P-A13d-2 接收者前缀 ctor 守卫**（pipeline stage5，见下节）+ UIPostUpdate（上批已落）。

## 连带发现（挂账非本批）

- **gbChain1DNode dtor 冒名**：`Method`@0x4B7090=删除式 dtor 形（sub_4B70B0+条件
  operator delete=??_G 铁证）、`Process`@0x4B6FB0=完全形 dtor 体（双基表写+成员析构链）
  —— 最早占位名时代产物，与 census_dtor_misattrib Q1 同族，归槽5闭环族深裁。
- **CScreenMode::SetMode 的 v9 病灶不是头缺口**：是 codegen P-A13d 规则宽门误吞
  （见下节），头签名本就正确（IAT mangle 对齐）。
- gbengine_api.h 的 CIniFile 12 方法 vs 共享头 9：DLL 导出方法多数已声明，其余仅未来需求。

## 折叠载体别名误档案（机制三重不适格，fail-loud 活性实证）

上批收尾把 EffCallBackNode.UpdateDelta@0x4C2600 归档进 `fold_carrier_aliases.json`（ICF
折叠机制），且**提交晚于最后一次 codegen**——门禁从未跑过新数据。本批 codegen 首跑即拦：

1. **体非空**：0x4C2600 是真 delta 计算（8 指令），与空别名体不可能字节等价折叠（机制前提=空体）；
2. **无 atexit 证据**：证据行引的是 vtable 槽证据（DestroyEffect 先例引的是 128 站 atexit 注册）——机制错配；
3. **门禁契约不可满足**：无 methods 条目（cc=None）+ 地址属 CEffSParticle（唯一所有者）。

**教训**：机制归档前先核机制前提（体形态/注册站证据/契约可满足性）；提交必须在最后一次
全管线验证**之后**。修正=条目回退+`_retired_20261122` 留痕+multi_claim_ledger 同步修正。
深归属（0x4C2600 六类共享 vtable_walk 账 vs 唯一所有者账并存）归 EffNode 族余战役。

## P-A13d 接收者前缀 ctor 宽门（TDD 修复实录）

病灶链：decomp `gbAudioManager::gbAudioManager(v3, &v9, &v13)`（this-首参+引用 out 参）
→ stage2 方法化 `v3->gbAudioManager::gbAudioManager(&v9, &v13)` → P-A13d
`\bCls::Cls(&obj, args)` 的 `\b` 在 `->` 后照样命中 ⇒ `v3->v9 = gbAudioManager(&v13)`
假成员访问（C2039 'v9' + C2440 级联）。

修法（窄门纪律，A/B 定爆炸半径=1 站）：
- 新规则 P-A13d-2（先于 P-A13d）：`PTR->Cls::Cls(&V, args)` →
  `new ((void *)PTR) Cls(V, args);`（placement new 兄弟形，P-A13/P-A13b/P-A13e 同律）；
- P-A13d 加 lookbehind `(?<![.\w>])`：接收者形态不再被吞，未覆盖形态留未改写=fail-loud。
- 测试：`pipeline/gen/test_pa13d_receiver_ctor.py`（4 测：placement 形/this 接收者/
  自由形保持/双保险不静默错形）。

## 方法论增量

- **scoped probe 会覆写 probe_census.json**（全量读数被清）——census 缓存坑已知实例；
  读基线前先确认 census 是全量产物。
- **scoped 模式伪影**：scoped codegen 跳过 overlay 套用 ⇒ 自由调用不限定名 ⇒ C2065 群。
  A/B（stash 对照）定性伪影 vs 真回归：双臂都在=伪影。scoped 读数不进回归台账。
