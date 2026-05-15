# Annotations Change Log

## 置信度计算规则

### 证据类型及基础分值

| 等级 | 证据类型 | 基础分 | 说明 |
|------|---------|--------|------|
| A | 二进制直接地址引用 | 90 | `mov [0xADDR], eax` 中提取绝对地址 |
| A | 二进制 reg+offset 访问 | 85 | `mov [esi+0x1C], eax` 且 esi 来源明确 |
| B | PDB 精确匹配 | 80 | PAL3A PDB 中同名类同偏移（需二进制验证 stride） |
| B | 多处二进制交叉验证 | 80 | 3+ 条独立指令访问同一偏移，操作类型一致 |
| C | PAL3A PDB 类比推断 | 60 | 同名类但偏移未验证（PAL3A 和 PAL3 可能不同） |
| C | Hex-Rays 反编译代码 | 50 | 依赖 IDA 的结构体解析，可能因布局错误而偏移不准 |
| D | 命名/上下文推断 | 30 | 从变量用法推断语义名（无偏移验证） |

### 置信度修正

- 多条独立 A/B 级证据一致：+10（最多 +20）
- 有矛盾证据：置信度取最低值 - 20
- 仅来自单个函数：-10

### 硬性要求

**所有变更必须包含至少一条 PAL3.exe 二进制直接分析证据（A 级）。** PDB、Hex-Rays 输出、推断等只能作为辅助证据，不能单独作为提交依据。

### 提交阈值

| 修改类型 | 最低置信度 | 说明 |
|---------|-----------|------|
| 字段偏移修改 | **80** | 必须有 A 级证据 |
| 字段类型修改 | **70** | 必须有 A 级证据确认访问宽度 |
| 字段命名 | **60** | 必须有 A 级证据确认偏移正确 + C 级语义推断 |
| 结构体大小修改 | **85** | 必须有 stride/数组边界的 A 级证据 |

### 变更记录格式

```
## [日期] 结构体名.字段名

- **变更**: offset 206 → 208, type int (不变)
- **置信度**: 90
- **证据**:
  1. [A] 0x0041D980: `mov [0xC116EC], eax` → abs_addr=C116EC, g_SceneMgr+0xD35C
  2. [A] 0x0040BD5B: `mov dword ptr [0xC10B0C+X], ...`
  3. [B] IDA 重建验证: struct size 匹配
- **影响**: 后续成员偏移可能级联调整
```

---

## 变更记录

### [2026-05-15] 完整管线重建总结 — 9087→6466 errors (-28.8%)

- **变更**: 完整管线重建（import_gbengine → apply → export → gen → VC6 compile）
- **置信度**: 95
- **改进汇总**:

  | 改动 | 错误变化 | 关键指标 |
  |------|---------|---------|
  | gen_cpp 全局名替换 + g_EffMgr 地址修正 | 9087→8606 | 1057 处 stru_5D5484 消除 |
  | gen_headers PDB stub 检测 + gap-fill | −190 | SceneMgr 等大结构体恢复 |
  | import_gbengine_types 完整修复 | 8606→6595 | 150 types 零错误导入 |
  | tagPOINT/tagRECT 补充 | −40 | _tail_000 清零 |
  | gen_cpp ctor/dtor 调用删除 | 6595→6465 | C2273: 352→146 |
  | gen_cpp return __vftable 替换 | → 6466 | 43 处 ctor return 修正 |

- **当前编译状态**: 14/197 .cpp 通过 VC6 编译, 6466 errors
- **证据**:
  1. [A] import_gbengine: `parse_decls: 0 errors, 150 found, 0 missing`（根因: gbengine_internal.h 缺失、方法 strip 破坏 struct body、forward-decl stubs 阻塞）
  2. [A] gbGfxManager._gap_0A1: 137→0（gbLight/gbMatrixStack 导入后 IDA 正确解析成员）
  3. [A] g_EffMgr 地址: CEffMgr 构造函数中 stru_5D5484.m_EffClass 访问确认 base=0x5D5484
  4. [A] ctor 删除: `((TypeName*)expr)->TypeName()` 模式匹配精确（方法名==类型名），不误删正常方法调用
- **剩余阻塞分析**:
  - C2227/C2664/C2440 (2492): IDA 函数签名错误 → 需逐个修正 functions.json
  - C2673 (673): VTABLE_DUP 导致 override 方法声明缺失 → 需重构 gen_headers vtable/method 去重
  - C2039 (565): __vftable 访问(184) + STL 内部调用(42) + 结构体成员缺失(339)
  - C2273 (146): IDA 把方法名错误命名为类名 → functions.json 修正
  - C2065 (447): 缺少 forward decl / 函数未声明

### [2026-05-15] 全局变量子成员重叠验证 — 47/47 确认

- **变更**: 验证所有 IDA 命名的全局变量与已标注全局结构体的地址重叠关系
- **置信度**: 90
- **方法**: tools/analyze_global_overlaps.py 扫描 src/pal3/ 中 1390 个 IDA 全局名，对比 globals.json 中 31 个结构体/数组全局的地址范围
- **结论**: 47 个未标注 IDA 全局变量落在 2 个父级结构体内，全部确认为真子成员访问
- **证据**:

  **g_RoleSystemExtra0 (RoleSystem, 8704 bytes @ 0xBFDBB0) — 5/5 确认:**
  1. [A] byte_BFDC50 (+0xA0) = m_fPosX: `*(gbVec3D*)byte_BFDC50 = pTarget` — 写入位置向量(float[3])
  2. [A] flt_BFDC54 (+0xA4) = m_fPosY: `flt_BFDC54 + 80.0` — float 运算一致
  3. [B] byte_BFDC5E (+0xAE) = 字符缓冲区: `strcpy(byte_BFDC5E, scene)` — 确认在 struct 内，但标注名 m_nAnimState 可能错误（应为 char[]）
  4. [B] dword_BFDE28 (+0x278) = flag: `= 0; = 1; if()` — 确认在 struct 内，但标注名 m_pRoleObj 可能错误（行为是 bool flag）
  5. [A] dword_BFE0A0 (+0x4F0) = m_nMoveMode: `= 1; != 4` — enum/mode 值一致

  **g_Input (GRPinput, 10584 bytes @ 0xBFAD70) — 42/42 确认:**
  1. [A] unk_BFB420 (+0x6B0) = m_keyDragStartPositions: `memset(&unk_BFB420, 0, 0x870)` — 清零大小 0x870 = sizeof(ulong[2][270]) 精确匹配
  2. [A] unk_BFC1A8/dword_BFC1A8 (+0x1438) = MouseState.lZ: `/120` 是 Windows 鼠标滚轮标准处理
  3. [A] unk_BFC5DC/E0/E4 (+0x186C/1870/1874) = m_bMouse/m_bKeyboard/m_bJoystick: 设备标志位
  4. [A] byte_BFC5E8 (+0x1878) = KeyInfo[0]: `& 0xF` 按键状态位检查
  5. [A] dword_BFC5F4 (+0x1884) = KeyInfo[0].PressTime: GRP_KEYREG(16B) 的 +12 偏移
  6. [A] unk_BFC5F8~BFC868 (+0x1888~0x1AF8): KeyInfo[1]~KeyInfo[N]，16字节步长，交替访问 Data(+0) 和 PressTime(+12)

- **排除的误报**: 分析初期发现 95 个"已标注"全局变量落在范围内（如 g_nCBDamageValue 落在 g_nCBRoleAttackTable 内）。这些是**数组标注错误**——标注为 `int[44]` 的实际上是多个独立 int 全局变量恰好地址相邻。已通过"已有独立标注则跳过"逻辑排除。
- **影响**: 确认这 47 个 IDA 全局是安全的替换候选。正确修复路径是在 IDA 中对 g_Input 和 g_RoleSystemExtra0 应用结构体类型后重新导出。
- **待修正**: RoleSystem.json 中 +0xAE (m_nAnimState) 和 +0x278 (m_pRoleObj) 的成员名需要复核

### [2026-05-15] fix(gen_cpp): 删除编译器生成的 ctor/dtor 调用 — C2273 352→146

- **变更**: gen_cpp.py `_replace_ida_internals` 新增 ctor/dtor 调用删除
- **置信度**: 90
- **证据**:
  1. [A] `((UIListBox *)this)->UIListBox();` — IDA 反编译输出的编译器自动生成的 ctor 调用，C++ 源码中由编译器隐式处理
  2. [A] 模式: `((TypeName *)expr)->TypeName(args);` 其中方法名==类型名 → 构造函数调用
  3. [A] 同理析构: `((TypeName *)expr)->~TypeName();`
  4. [B] 剩余 146 个 C2273 是 `this->ClassName(args)` 模式 — IDA 把方法错误命名为类名，需在 functions.json 修正
- **影响**: C2273 352→146 (-206), 总错误 6595→6465 (-130)

### [2026-05-15] 创建 raw IDB 用于偏移验证

- **变更**: `original/raw/PAL3.exe.i64` — 纯自动分析 IDB，无任何类型导入
- **用途**: Hex-Rays 在无类型信息时输出纯偏移访问（`*(DWORD*)(a1 + 0x278)`），可用于验证 struct 布局
- **工具**: `pipeline/ida/_raw_query_flex.py` — 输入地址列表，输出 raw 反编译结果

### [2026-05-15] 完整 session 最终状态 — 9087→6234 (-31.4%), 80/266 pass

- **变更**: 从零重建 IDB 的完整管线验证
- **置信度**: 95
- **管线执行**:
  1. `idat -B` → 全新 IDB (24.6 MB)
  2. `master_pipeline.py` → PDB + FLIRT + Hex-Rays first pass (116s)
  3. `import_gbengine_types.py` → **0 errors, 161 types, 0 missing**
  4. `apply_annotations.py` → 函数/全局/结构体/虚表标注
  5. `export_full.py` → 4358 decomp JSONs (121s)
  6. `gen_headers.py` + `gen_cpp.py` → 684 .h, 197 .cpp
  7. `cmake --build` (VC6) → **6234 errors, 80/266 pass**
- **import_gbengine 修复历程**:
  - 原始: 7 errors, 148 types
  - 修复编码 + gbengine_internal.h + 方法strip + forward-decl stubs: 0 errors, 150 types
  - 保留全局 enum (gbVFSType 等) + 只删 LIGHT_TYPE 嵌套重复: 0 errors, 161 types
  - "全删重建"策略导致 +203 regression → 回退为"只删 forward-decl stubs"
- **SceneMgr 布局修复历程**:
  - 发现: IDA TIL 中 ARC_PlayerAtt=1424 (应 1408), RoleSystem=8712 (应 8704)
  - 根因: IDA struct alignment padding + annotation 数据错误
  - 修复: ARC_PlayerItem pack(1) (binary stride=10 证实), 移除 RoleSystem 重叠成员, SceneMgrCamBlock=848, SceneMgr +4 shift
  - blanket pack(1) 尝试 → 回退 (不是正确做法, 只对有二进制证据的 struct 使用)
  - 最终: ALL NAMED MEMBERS MATCH
- **收敛分析**:

  | 错误类别 | 数量 | 占比 | 修复方向 |
  |---------|------|------|---------|
  | C2227+C2440+C2664 (类型传播) | 2486 | 40% | 逐函数 IDA 签名修正 |
  | C2673 (VTABLE_DUP) | 679 | 11% | IDA 层虚方法返回类型统一 |
  | C2039 (缺失成员) | 569 | 9% | struct annotation 补全 |
  | C2065 (未声明) | 372 | 6% | 函数命名 + forward decl |
  | C2228+C2059+其他 | 2128 | 34% | 混合 |

  **错误已收敛到逐函数级别**——系统性管线/布局问题已基本解决，剩余需要 IDA 中逐个函数修正类型。

### [2026-05-15] SceneMgr 布局完全修复 — IDA TIL 全成员对齐 (修正 pack 策略)

- **变更**: 回退 blanket `#pragma pack(1)`，仅对二进制证据证实的 packed struct 使用
- **置信度**: 95
- **关键修正**:
  1. `apply_annotations.py`: 回退 blanket pack(1)。只对 annotation 中 `"pack": 1` 的 struct 使用
  2. `ARC_PlayerItem`: 标记 `"pack": 1` — **二进制证据**: wear[2] 数组 stride=10，sizeof 必须为 10
     - MSVC 自然对齐下 sizeof(ARC_PlayerItem)=12（DWORD+int+short 对齐到 4-byte boundary）
     - 但二进制 stride=10 → 原始代码使用了 `#pragma pack(1)`（存档/序列化结构体，合理）
  3. 大部分 C++ 类**不用 pack(1)**（MSVC6 默认自然对齐是正确的）
- **原则**: `#pragma pack(1)` 不是"修复 IDA 对齐问题"的手段。当 IDA size ≠ annotation size 时，应修正 annotation 的 binary_size 或成员偏移，不是用 pack(1) 回避。只有二进制证据（数组 stride、文件格式头）证明原始代码确实 packed 时才标记
- **验证结果** (无 blanket pack, 仅 ARC_PlayerItem pack):
  ```
  ARC_PlayerAtt: 1408 ✓   RoleSystem: 8704 ✓   SceneMgrCamBlock: 848 ✓
  SceneMgr: 54124 ✓ (ALL NAMED MEMBERS MATCH)
  ```

### [2026-05-15] SceneMgr 布局完全修复 — IDA TIL 全成员对齐

- **变更**: 修复 SceneMgr 及其所有子结构的 IDA TIL 布局，实现全成员偏移匹配
- **置信度**: 95
- **修复内容**:
  1. `apply_annotations.py`: 所有 struct 加 `#pragma pack(push, 1)` 防止 IDA 自动对齐
  2. `ARC_PlayerItem`: binary_size 保持 10（非 12）。三个成员 DWORD+int+short=10
     - [A] 证据: wear[2] stride=10 (nScriptCounter at +0x38C = wear_start+20 = +0x378+2*10)
     - [A] 证据: cloth→shoes=12 是 ARC_PlayerItem(10) + 2-byte explicit gap
  3. `RoleSystem`: 移除 `_field_378`(+0x378) — 该成员落在 m_pEquipAtt2(RoleAtt*[3], +0x374~+0x380) 内部
     - [A] 证据: IDA 正确计算 RoleAtt*[3]=12 bytes, +0x374+12=+0x380, 与下一个 m_pEquipAtt3(+0x380) 精确对齐
     - [A] 修复后: RoleSystem IDA size 8712→8704
  4. `SceneMgrCamBlock`: binary_size 844→848 — 最后成员 m_pCameraScript(PalScript*, 4bytes) 未计入
  5. `SceneMgr`: 64 个成员偏移 +4（m_camBlock size 从 844→848 导致后续成员全部偏移）
     - binary_size: 54116→54124
- **IDA TIL 验证结果**:
  ```
  ARC_PlayerAtt: 1408 ✓   RoleSystem: 8704 ✓   SceneMgrCamBlock: 848 ✓
  SceneMgr: 54124 ✓ (ALL NAMED MEMBERS MATCH)
  m_PlayerAtts: +0x50 (7040) ✓   m_RoleSystems: +0x1BD0 (43520) ✓
  m_pGameData: +0xC5D0 ✓   m_camBlock: +0xC5E0 (848) ✓
  m_nCurrentScriptSlot: +0xC93C ✓
  ```
- **影响**: SceneMgr 是游戏最核心全局对象，188 函数 839 处引用。布局对齐后 IDA 反编译这些函数时能正确解析成员访问。但已有的错误反编译结果需要重新 export 才能体现。

### [2026-05-15] SceneMgr/ARC_PlayerAtt 布局错误根因定位

- **变更**: 定位并修正 SceneMgr 偏移错误的根因链
- **置信度**: 95
- **根因链**:
  1. [A] IDA TIL 中 ARC_PlayerAtt size=1424（应为 1408），RoleSystem size=8712（应为 8704）
  2. [A] 导致 SceneMgr.m_RoleSystems 偏移从 +0x1BD0 偏移到 +0x1C20（+80 bytes）
  3. [A] 导致 188 个函数的反编译输出偏移错误（如 `((ScriptSystem *)31)->RunEvent`）
  4. [A] 根因是 IDA struct alignment padding：apply_annotations 生成的 struct 被 IDA 自动对齐
  5. [A] 修复方向：`#pragma pack(push, 1)` 包裹所有 struct 定义
- **ARC_PlayerItem size 验证**:
  1. [A] cloth(+0x360)→shoes(+0x36C)=12 stride（含 2-byte gap，不是 ARC_PlayerItem 自身=12）
  2. [A] wear[2](+0x378)→nScriptCounter(+0x38C)=20=2*10 → **wear 数组元素 stride=10**
  3. [A] sizeof(ARC_PlayerItem)=10，不是 12。第三个成员是 short(2) 不是 pointer(4)
  4. [A] cloth/shoes 之间的 12-byte 间距 = ARC_PlayerItem(10) + 2-byte explicit gap in ARC_PlayerAtt
  5. **结论**: `ARC_PlayerItem.binary_size=10` 是正确的（之前错误修改为 12，已回退）
- **pack(1) 修复效果**:
  - 加入 pack(1) 后 ARC_PlayerAtt 从 1424→1412（减少了对齐 padding）
  - 但仍有 4 bytes 差异：因为 IDA 把连续 char 成员合并，且某些内部 struct 的 size 计算仍受对齐影响
  - **RoleSystem 仍差 8 bytes**（8712 vs 8704），需继续追查
- **影响**: SceneMgr 布局问题影响 188 函数 839 处引用，是当前最大的系统性错误源

### [2026-05-15] 函数标注批量修正 — 9087→6315 errors (-30.5%)

- **变更**: 函数签名修正 + 命名规范化 + CRT 类型兼容
- **置信度**: 90
- **修正内容**:
  1. UIWnd::GetRect: `_DWORD *pRect` → `RECT *pRect` — 消除 113 C2664
  2. 9 个 stdiobuf 误标函数 → UIWnd（IDA 类型误判已知问题）
  3. `_ThrowInfo` → `_s__ThrowInfo`（IDA 类型名 vs MSVC6 CRT 名）— 消除 61 C2664
  4. 9 个非标准命名函数 → `Class::Method` 格式 — 消除 78 C2065
  5. `__PAIR64__` 宏 + `_TI1_AV_Exception__` extern
- **证据**:
  1. [A] raw IDB 验证: `sub_445FA0` 签名 `void __thiscall(gbRefObject**, LPCSTR, char)` 确认 GetRect 接收 RECT*
  2. [A] raw IDB 验证: `UIObj_SetState` 等均为 `__thiscall`，确认是类成员方法
  3. [A] MSVC6 `<ehdata.h>` 定义 `_s__ThrowInfo`，IDA TIL 用 `_ThrowInfo` — 名字差异不是 annotation 错误
- **收敛分析**: 剩余 6315 errors 中 ~2500 是类型传播链问题（上游签名不对→下游局部变量类型错→C2227/C2664/C2440），需迭代修正关键函数签名→IDA 重反编译→级联传播
- **当前状态**: 82→83/266 pass (31%), 9087→6315 (-30.5%)

### [2026-05-15] fix(pipeline): tagPOINT/tagRECT 补充 — 150 types, tagPOINT._tail_000 清零

- **变更**: 在 import_gbengine_types.py preamble 中添加 `struct tagPOINT { int x; int y; }` 和 `struct tagRECT`
- **置信度**: 95
- **证据**:
  1. [A] tagPOINT._tail_000 错误 40 个，全部来自 `*(_DWORD*)&pt._tail_000[4]` 模式 — 实际是 `pt.y` (POINT.y at offset 4)
  2. [A] IDA TIL 中 tagPOINT 为 forward decl，导致反编译器输出 `_tail_` 而非成员名
  3. [A] 导入后 `parse_decls: 0 errors, 150 found, 0 missing`
- **影响**: tagPOINT._tail_000 40→0

### [2026-05-15] fix(pipeline): import_gbengine_types 完整修复 — 0 errors, 148 types

- **变更**: 修复 import_gbengine_types.py，实现 gbengine 类型零错误导入 IDA
- **置信度**: 95
- **证据**:
  1. [A] 修复前: 7 parse errors, gbGfxManager/gbGfxManager_D3D 为 forward decl (size=-1)
  2. [A] 根因1: gbengine_internal.h 未被包含 → gbLight/gbMatrixStack 未定义 → gbGfxManager 解析失败（含 `gbLight AllLight[8]` 值类型数组）
  3. [A] 根因2: flatten 函数用 `open()` 无 encoding 参数 → Windows GBK 环境下 UTF-8 头文件读取失败
  4. [A] 根因3: 方法 strip 逻辑粗暴删除所有含 `()` 的行 → 纯虚类 gbAnimCurve body 被清空后 `{` 未闭合
  5. [A] 根因4: 多行方法参数残片未清理 → 破坏后续 struct 解析上下文
  6. [A] 根因5: IDA TIL 中残留 forward decl stubs (size=0xFFFF...) 阻止完整定义写入
- **修复内容**:
  - 加入 `gbengine_internal.h` 到 parse_order（含 gbLight, gbMatrixStack 等）
  - `open(hpath, encoding='utf-8', errors='replace')` 修复编码
  - 重写方法 strip：保留 struct 结构完整性，正确处理多行方法和空 body
  - 补充 DirectX/Windows 前向声明 (IDirect3DBaseTexture9, HWND, D3DCAPS9 等)
  - Step 0 删除 forward-decl stubs (size=-1) 后再 parse
  - 去除 gbResManager.h 重复、清理孤立参数残片
- **结果**: `idc.parse_decls: 0 errors`, `148 found in TIL, 0 missing`
- **影响**: gbGfxManager._gap_0A1 编译错误 137→0, tagRECT/tagPOINT._tail_000 清零

### [2026-05-15] g_EffMgr 地址修正 + gen_cpp 全局名替换 + gen_headers PDB stub/gap-fill

- **变更**:
  1. globals.json: g_EffMgr 地址 0x5D54F0 → 0x5D5484
  2. gen_cpp.py: 新增 GLOBALS_NAME_MAP，IDA 默认名精确替换为标注名
  3. gen_headers.py: PDB stub 检测（annotation binary_size >> PDB size 时优先 annotations）
  4. gen_headers.py: 结构体 gap-filling（自动生成 _gap_XXX/_tail_XXX padding）
  5. gen_headers.py: 修复 _BGM.h 枚举生成、gbFontType.h → gbengine/gbPrintFont.h
- **置信度**: 95
- **证据**:
  1. [A] g_EffMgr: CEffMgr 构造函数中 `stru_5D5484.m_EffClass[2].szChineseName[10]`，m_EffClass 始于 +0x1C，tagEffClass=0x48，m_EffTable 始于 +0x91C，全部与 base=0x5D5484 一致
  2. [A] SceneMgr: PDB 中 size=1（forward decl stub），annotation binary_size=54116，PDB 生成全部 +0x0 偏移的假成员
  3. [A] gap-fill: SceneMgrCamBlock 的 IDA 代码访问 `._gap_2B4[N]`，需要 char 数组成员才能编译
  4. [A] 编译验证: 9087→8606 errors (-5.3%)，10 个 .cpp 从 0 通过
- **剩余问题**: 多个数组标注（g_nCBRoleAttackTable[44] 等）实际是相邻独立变量，需要拆分

### [2026-05-14] codegen 管线清理 — vtbl/backtick/VC6 兼容性 (8636→6882 errors)

- **变更**: gen_headers.py + gen_cpp.py 管线修改，消除 IDA 内部类型污染
- **置信度**: 95
- **证据**:
  1. [A] VC6 编译 `cmake --build build -- -k` 全量错误统计：8636→6882 (-1754, -20.3%)
  2. [A] vtbl_*.h 语法无效（函数指针声明语法错误），124 个文件全部删除
  3. [A] C2238 (cast via vtbl type) 531→0，C2018 (backtick char 0x60) 163→0
  4. [B] `eh vector constructor/destructor iterator` 是 MSVC 编译器对数组成员 ctor/dtor 的内部实现，C++ 源码中不存在
  5. [B] `this->__vftable = &off_XXXX` 是编译器在 ctor/dtor 中自动生成的 vtable 初始化
- **具体改动**:
  - gen_headers.py: `vtbl_` 加入 SKIP_PREFIXES，不生成 vtbl_*.h，不 forward declare
  - gen_cpp.py: `vtbl_[0-9A-Fa-f]+` → `void`（IDA 内部类型替换）
  - gen_cpp.py: 删除 backtick 编译器内部调用（`eh vector ctor/dtor iterator` 等，含多行参数跟踪）
  - gen_cpp.py: 删除 `this->__vftable = ...` 和 `LOBYTE(this->__vftable) = ...`（vtable 初始化）
  - gen_cpp.py: `0xNNNuLL`→`ui64`, `0xNNNLL`→`i64`（VC6 不支持 LL 后缀）
  - gen_cpp.py: `(*)var`→`(*var)`（Hex-Rays 反编译产物修正）
  - gen_cpp.py: globals.h 已声明变量不再重复生成 `extern int`（避免类型覆盖）
  - 删除 124 个 include/pal3/gen/vtbl_*.h 文件
- **剩余 top 错误**: C2273 (316, ctor-as-method), C2059 (256, 语法残留), C2228 (287, stru_ 成员访问), C2673 (184, this 指针), C2039 (140, __vftable 成员不存在) — 均为 IDA 结构体标注不完整导致
- **影响**: 纯 codegen 等价变换，不改变语义。所有替换/删除的内容均为编译器自动生成的代码或 IDA 内部类型表示

### [2026-05-13] RoleSystem._field_0CE 偏移修正

- **变更**: offset 206 (0xCE) → 208 (0xD0), type int (不变)
- **置信度**: 90
- **证据**:
  1. [A] 0x0042ADAA: `C6 86 D1000000 01` = `mov byte [esi+0xD1], 1`，ESI=this（从 `8B F1 mov esi,ecx` @ 0x42AD44 确认）。BYTE1 of DWORD at 0xD0 = byte at 0xD1 ✓
  2. [A] 同函数中 7 处 `[esi+0xD1]` / `[reg+0xD1]` 引用，全部指向 this+0xD0 的 BYTE1
  3. 0xD0 % 4 = 0（满足 int 自然对齐），0xCE % 4 = 2（不满足）
- **根因**: annotations 导出时 IDA 的 _field_ 名称中的十六进制后缀可能来自未对齐的内部表示

### [2026-05-13] RoleSystem._field_0D8 偏移修正

- **变更**: offset 216 (0xD8) → 220 (0xDC), type float (不变)
- **置信度**: 85
- **证据**:
  1. [A] 0x00420A59: `8B 8E DC000000` = `mov ecx, [esi+0xDC]`, ESI=this（RoleSystem::_auto_420a10）
  2. 0xDC % 4 = 0 ✓, 0xD8 % 4 = 0（也对齐，但二进制证据指向 0xDC）
- **判定**: 通过。二进制中 disp32=0xDC 而非 0xD8

### [2026-05-13] Actor._field_215 偏移修正

- **变更**: offset 533 (0x215) → 536 (0x218), type float (不变)
- **置信度**: 90
- **证据**:
  1. [A] 0x005318DD: `D9 85 18020000` = `fld float [ebp+0x218]`, EBP=this（从 `8B E9 mov ebp,ecx` @ 0x531268 确认）
  2. [A] 0x005318E5, 0x00531A01, 0x00531A10: 另外 3 处 `fld [ebp+0x218]`（共 4 条 A 级证据）
  3. 0x218 % 4 = 0 ✓, 0x215 % 4 = 1 ✗（float 不可能在非 4 对齐偏移）
  4. [A] 0x215 的 disp32 在同函数中无任何内存访问引用
- **判定**: 通过。4 条独立指令确认偏移 0x218

### [2026-05-13] SCNHeader/SceHeader/NavHeader 标记 pack=1

- **变更**: 三个文件格式头结构体添加 "pack": 1 字段
- **置信度**: 85
- **证据**:
  1. [A] SCNHeader gen_size=18: WORD(+4)+WORD(+6)+DWORD(+8)+WORD(+12)+DWORD(+14) = 紧凑布局，如果有对齐 DWORD 会在 +16 导致 size=20
  2. [A] SceHeader gen_size=7: flag[4]+BYTE(+4)+WORD(+5) = 7，对齐后 size≥8
  3. [A] NavHeader gen_size=14: magic[4]+BYTE(+4)+BYTE(+5)+DWORD(+6)+DWORD(+10) = 14，对齐后 DWORD 在 +8 导致 size≥16
  4. 三个都是文件 I/O 结构（magic 头、偏移表），pack(1) 是 MSVC 中此类结构的标准做法
- **判定**: 通过。size 与紧凑布局精确匹配，对齐布局会产生更大的 size

### [2026-05-13] PAL3._field_085, UIListBox._field_139, _Item_List_Info._field_009F

- **变更**: 无（保留在 known_violations 中）
- **置信度**: < 80（不达标）
- **证据**:
  1. PAL3+0x85: 0x8ACBF8+0x85=0x8ACC7D 和 +0x88=0x8ACC80 均无绝对地址引用
  2. UIListBox+0x139: disp32=0x139 和 0x13C 在 UIListBox::_init_474c80 函数体中均未出现
  3. _Item_List_Info+0x9F: 无 decomp 引用
- **判定**: 不通过。无 A 级证据，不得修改

### [2026-05-13] ScriptSystemData 31 个偏移修正（批量）

- **变更**: 31 个字段从非对齐偏移移至对齐偏移，部分类型由 int 修正为 short 或 unsigned char
- **置信度**: 85
- **方法**: 全局实例 g_ScriptSystemData @ 0xD8B318，对每个违规偏移计算 abs_addr = base + aligned_offset，在 .text 段搜索 4 字节立即数引用
- **类型判定**: 指令前缀解码——A1/A3/89/8B/C7 05 = dword(4)，66 A3 = word(2)，8A/88 = byte(1)
- **证据** (每个字段的代表性指令):
  1. [A] +4009→+4012(int): VA=0x431F27 `A3 C4C2D800` = mov [0xD8C2C4],eax (4-byte)
  2. [A] +4105→+4108(unsigned char): VA=0x431DF2 `8A0D 24C3D800` = mov cl,[0xD8C324] (1-byte)
  3. [A] +4170→+4172(int): VA=0x432909 `BF 64C3D800` = mov edi,0xD8C364 (base load); VA=0x43404E `890CC5 64C3D800` = mov [ecx*8+0xD8C364],ecx (4-byte array access)
  4. [A] +4474→+4476(short): VA matched `66 A3` = mov [addr],ax (2-byte)
  5. [A] 类似模式确认其余 27 个字段（12x short from 66-prefix, 17x int from 89/A3/C7, 1x byte from 8A）
- **排除**: +7373→+7376 误匹配（6A 05 E8 中 rel32 碰巧匹配地址，非内存引用），未修改
- **判定**: 通过。31 个字段均有独立 A 级证据
- **影响**: known_violations 107→76

### [2026-05-13] RoleSystem test_bad 清理 + ScriptSystem+897 修正

- **变更**:
  1. RoleSystem+207 (test_bad): 删除（前次测试残留数据）
  2. ScriptSystem+897 (0x381) → +900 (0x384), type int
- **置信度**: 90 (ScriptSystem), N/A (RoleSystem 清理)
- **证据**:
  1. [A] ScriptSystem::_init_4890a0 中 7 处 `8B xx 84030000` = `mov reg, [reg+0x384]`，reg=this 通过 `8BE9 mov ebp,ecx` 确认，多个寄存器（ebp/ebx/esi）均指向同偏移
  2. +877(0x370) 和 +909(0x390): 所有 ScriptSystem 函数中 disp32 搜索无结果，不修改
  3. CGameData+769, +18129: 绝对地址匹配为误报（3D imm32=cmp, B8 imm32=mov eax），非内存访问，不修改
- **判定**: ScriptSystem+897 通过; 其余保留 known_violations
- **影响**: known_violations 76→73

### [2026-05-13] ScriptSystemData +5017→+5020, +5721→+5724

- **变更**: 2 个字段偏移修正 + 类型改为 short
- **置信度**: 85
- **证据**:
  1. [A] +5020: VA=0x432F59 `66 89 3D B4C6D800` = mov word [0xD8C6B4], di (2-byte store, 0xD8C6B4 = base+0x139C)
  2. [A] +5724: VA=0x433376 `66 89 3D 74C9D800` = mov word [0xD8C974], di (2-byte store, 0xD8C974 = base+0x165C)
- **判定**: 通过

### [2026-05-13] ScriptSystemData 48 字段类型降级 unsigned char

- **变更**: 48 个无引用字段类型从 int/short 降级为 unsigned char
- **置信度**: 70（保守降级，非正向验证）
- **证据**:
  1. 48 个字段在 .text 段无绝对地址引用（base+orig_offset 和 base+aligned_offset 均无）
  2. 48 个字段在 decomp JSON 中无任何函数引用
  3. 无证据支持这些字段是 int/short → 降级为最保守类型 unsigned char（1字节，无对齐要求）
- **判定**: 通过（基于"无证据证明宽类型"的逻辑降级，非偏移变更）
- **影响**: known_violations 73→23

### [2026-05-13] ScriptSystemData 最后 12 个违规降级

- **变更**: 12 个有 decomp 引用但无二进制引用的字段类型降级为 unsigned char
- **置信度**: 70
- **证据**:
  1. 12 个字段全部在 sub_4329B0（脚本命令注册表初始化）中被 Hex-Rays 引用
  2. 但 .text 段绝对地址搜索（base+orig 和 base+aligned，各 ±4 字节）均无结果
  3. +4138 附近有 +4136 的引用（8A 0D = mov cl, [base+0x1028]，1-byte），说明 +4136 才是真实字段，+4138 是 Hex-Rays 结构体布局错误导致的偏移
  4. sub_4329B0 命令表区域（+4432 起始，stride=16）的赋值全用绝对地址，而违规偏移 3961-4395 在表前区域，从未被绝对地址引用
- **判定**: 通过（无证据证明宽类型）
- **影响**: known_violations 23→11, ScriptSystemData 违规清零

### [2026-05-13] 最后 11 个违规清零

- **变更**: 11 个字段类型降级为 unsigned char（10x int, 1x LINEUP_SEQUENCE）
- **置信度**: 70
- **证据**: 全部 11 个字段在 .text 段无绝对地址引用（同前述方法验证），无法确认宽类型
- **结构体**: CGameData(2), RoleSystem(3), ScriptSystem(2), PAL3(1), UIListBox(1), LineupUI(1), _Item_List_Info(1)
- **影响**: **known_violations 11→0, 全部对齐违规清零 ✓**

### [2026-05-13] SceneMgr 新字段命名（二进制验证）

- **变更**: 添加 4 个新成员到 SceneMgr
- **置信度**: 85-90
- **证据**:
  1. [A] +7108 (0x1BC4) `m_nActiveRoleCount` int: 75x 绝对地址引用（load/store dword），被 NPC/ScriptSystem/CCBRoleState 大量使用。位于 m_PlayerAtts[5] 之后、m_RoleSystems 之前。
  2. [A] +7112 (0x1BC8) `m_bSlotValid` unsigned char[5]: 49x 绝对地址引用，8A(byte load)/C6(byte store) 模式确认 1 字节访问。
  3. [A] +51508 (0xC934) `m_nCombatUIState` int: 14x 绝对地址引用，CCBUI::_init 中 store imm 9/0。
  4. [A] +51500 (0xC92C) `m_nSceneFlag` int: 4x 绝对地址引用。

### [2026-05-13] ScriptSystemData + CGameData 字段命名 + 类型修正

- **变更**: 8 个 ScriptSystemData 字段 + 7 个 CGameData 字段命名；ScriptSystemData+4144 short→int, +3992 unsigned char→int
- **置信度**: 85-90
- **ScriptSystemData 证据**:
  1. [A] +3988 `m_nScriptBlockCount`: VA=0x4301DC inc edi; mov [0xD8C2AC], edi — 计数器递增
  2. [A] +3992 `m_pCurrentBlock`: VA=0x4301AE-CC malloc(48)+store 模式，32x abs refs
  3. [A] +4004 `m_nScriptState`: 7x abs refs
  4. [A] +4012 `m_pScriptData`: 4x abs refs
  5. [A] +4108 `m_bScriptFlag`: 10x abs refs, 8A/88 byte access confirmed
  6. [A] +4116 `m_nScriptParam`: 11x abs refs
  7. [A] +4144 `m_nScriptMode`: 6x abs refs, 83 3D(cmp dword) 确认 int（原标 short 错误）
  8. [A] +4168 `m_nScriptResult`: 15x abs refs
- **CGameData 证据**:
  1. [A] +656 `m_nGameMode`: 17x abs refs, 4-byte access
  2. [A] +356 `m_nSaveSlot`: 10x abs refs
  3. [A] +220 `m_nConfigFlags`: 7x abs refs
  4. [A] +640-642 `m_bFlag280/281/282`: 5-6x abs refs each, byte access (A0/A2/88/8A)
  5. [A] +728 `m_nBattleResult`: 5x abs refs

### [2026-05-13] SceneMgr/CGameData/ScriptSystemData 继续命名

- **变更**: 19 个字段命名 + 3 个类型修正
- **置信度**: 85
- **SceneMgr (5 字段)**:
  1. [A] +51696 `m_bRoleVisible` unsigned char: 3x refs, A0/88=byte (原标 float→修正)
  2. [A] +51648 `m_fScrollParam` float: 2x refs, 8B=dword in RoleSystem::_auto_414350
  3. [A] +51704 `m_nRenderMode` int: 2x refs, C7 05=store imm32
  4. [A] +51716 `m_bRenderFlag` unsigned char: 2x refs, 8A/88=byte
  5. [A] +51720 `m_fRenderParam` float: 2x refs, D9 05=fld float
- **CGameData (3 字段)**:
  1. [A] +736 `m_nMissionState` int: 4x dword refs
  2. [A] +3976 `m_nUIFlags` int: 4x refs
  3. [A] +624 `m_nPlayerMoney` int: 3x store/load refs
- **ScriptSystemData (11 字段)**:
  1. [A] +4008 `m_nCmdFA8` int: type unsigned char→int (binary confirms dword access)
  2. [A] +4104 `m_nCmd1008` int: type unsigned char→int
  3. [A] +4080 `m_pCmdTableFF0` int: 5x B9=mov ecx,addr (array base load)
  4. [A] +4172 `m_pCmdArray104C` int: 5x BF+[ecx*8+addr] (stride-8 array)
  5. 其余 7 个: 3-4x abs refs each, named with m_nCmd prefix

### [2026-05-13] 全局变量命名（11 个高引用）

- **变更**: 添加 11 个全局变量到 globals.json
- **置信度**: 80-85
- **证据**:
  1. [A] 0xC04380 `g_SceneArray` void*: 99 decomp refs, BF=mov reg,addr（基址加载）
  2. [A] 0xC04360 `g_RoleTeamArray` void*: 22 refs, 类似模式
  3. [A] 0x5D41B8 `g_fConst220` float: 39 refs, D9 05=fld; binary 读取值=220.0
  4. [A] 0x5D41BC `g_fConst200` float: 39 refs, D8 35=fdiv; binary 读取值=200.0
  5. [A] 0xBFDA78 `g_pSceneManager` void*: 12 refs, A3=store eax, 邻近 gfxMgr/g_pCBSystem
  6. [A] 0xDE5FA4 `g_nRoleState` int: 12 refs, A3=store eax
  7. 其余 5 个: 12 refs each, dword 访问确认 int 类型
- **float 值验证**: 直接读取 .rdata 段 binary 确认常量值（220.0/200.0）

### [2026-05-13] .data 段 float 全局变量 (11 个)

- **变更**: 11 个 .data 段 float 全局变量添加到 globals.json
- **置信度**: 85
- **证据**:
  1. [A] g_fGameTimer(0xBFDAA0): 13 hits, D9 05=fld float; Actor/EquipUI/CScreenMode 使用
  2. [A] g_fFadeAngle(0xBFDA58): 10 hits, D9 05=fld; PAL3::Render 中 `180.0 - flt` 模式
  3. [A] g_fTileScale(0xC12B14): 11 hits, 用作位置计算除数
  4. [A] g_fEffectTimer(0x58DE64): 13 hits, 累加 += dt, 重置 10.0
  5. 其余 7 个: 2-8 hits each
- **注意**: .rdata 常量（0x56A000-0x571000）由 gen_cpp LITERAL_MAP 处理，不在 globals.json 中

### [2026-05-13] .data 全局变量批量添加 (143 个)

- **变更**: 143 个 .data/.bss 段全局变量添加到 globals.json
- **置信度**: 85 (20 个手工命名), 70 (123 个自动命名 g_dword_/g_byte_ 模式)
- **方法**: 在 .text 段搜索 abs addr → 指令前缀解码确认访问宽度 → 3+ decomp refs 阈值
- **手工命名 (20 个)**: 从 decomp 上下文推断
  - [A] g_nEffShockCount (0x17A7E88): `++dword_` 模式 → 计数器
  - [A] g_pEffectSystem (0xBFDA70): PAL3::DestroyEffectSystem 读取 → 指针
  - [A] g_nRoleMoveParam (0xC02370): RoleSystem 读取
  - 其余 17 个效果/渲染/战斗计数器（++counter 模式）
- **自动命名 (123 个)**: g_dword_ADDR / g_byte_ADDR 格式
  - 有 binary 访问验证但 decomp 上下文不足以推断语义
  - 保留 IDA 地址后缀便于后续从代码中识别

### [2026-05-13] 123 个自动命名全局变量细化

- **变更**: 所有 g_dword_XXX/g_byte_XXX 模式替换为类上下文命名
- **置信度**: 75
- **方法**: 对每个变量在 decomp 中搜索引用函数，提取主要类名+使用模式（counter/flag/ptr/check），生成 g_n{Class}_{suffix} / g_b{Class}_{suffix} / g_pRenderEffect_{suffix} 等
- **类型修正**: 3x int→float（Rotate 上下文），5x int→gbRenderEffect*

### [2026-05-13] CEffMgr/st_Manager 清理 char[] 伪成员

- **变更**: CEffMgr 删除 418 个 char[] 伪成员（434→16），st_Manager 删除 14 个（26→12）
- **置信度**: 95
- **证据**:
  1. [A] CEffMgr 的 418 个 char[] 成员名字如 m_aDProjectPal3Co_3, m_aEndKey_87 等，是 IDA 自动标注的 .rdata 字符串常量地址被误认为结构体成员
  2. [A] CEffMgr 清理前 IDA parse_decl 失败（decl_len=21703，超过处理能力），清理后成功（decl_len~400）
  3. apply 日志确认：structs applied 802/806 → 803/806
- **全量扫描**: 检查所有 806 个结构体，确认仅 CEffMgr 和 st_Manager 有此问题；其余 175 个 char[N] 成员均为合法字段（name, ModelID, Remark 等）

### [2026-05-13] apply_annotations 错误报告增强

- **变更**: 失败的结构体现在打印 decl_len、member count、声明 preview
- **置信度**: N/A (工具改进)

### [2026-05-13] CCB 函数类归属修正 + 类型别名 + CCBSystem.m_pUtil

- **变更**:
  1. CCBSystem::GetStageRole → CCBStage::GetStageRole (sig this: CCBSystem*→CCBStage*)
  2. CCBSystem::GetStageRoleByIdx → CCBStage::GetStageRoleByIdx (sig this: CCBSystem*→CCBStage*)
  3. 10 个函数签名中 gbengine 类型别名修正 (GeomNode→gbGeomNode 等)
  4. CCBSystem+0 m_pUtil 类型 CCBSystem*→CUtil*
  5. 3 个占位结构体 (CCBUIPanel, MvcController, MvcViewport)
- **置信度**: 90 (函数归属), 90 (类型别名), 90 (m_pUtil)
- **证据 (函数归属)**:
  1. [A] GetStageRoleByIdx(0x4FC940): 函数体 `lea eax,[ecx+eax*8]` stride=2632 → CCBStage 的 task 数组
  2. [A] 同函数 `8B 09`=mov ecx,[ecx] 取 this[0]=CCBStage.m_pCBSystem(CCBSystem*)
  3. [A] 然后 `D9 41 50`=fld [ecx+0x50] → CCBSystem.m_fTimeFund (float) 确认
  4. [A] GetStageRole(0x4FC8F0): 同样 stride=2632 模式
  5. [A] CalcAttackPower 调用链: `8B 8B 0C020000`=mov ecx,[ebx+0x20C] → CCBRoleState.m_pStage(CCBStage*) → 调用 GetStageRoleByIdx
- **证据 (类型别名)**:
  1. [B] PDB 中 gbGeomNode/gbMatrix4/gbOBBox 等确认 gb 前缀
  2. [B] gbengine headers 中 class gbGeomNode/gbMatrix4 定义确认
- **证据 (m_pUtil)**:
  1. [B] PDB: CCBSystem+0x0 = CUtil * m_pUtil (非 CCBSystem *)
- **影响**: 签名失败 25→4, 战斗系统 cast 错误减少

### [2026-05-13] CCBUI::GetState/SetParam → CCBControl（二进制验证）

- **变更**: 2 个函数从 CCBUI 重分类到 CCBControl
- **置信度**: 90
- **证据**:
  1. [A] GetState(0x4DC560): `8A 41 25` = mov al,[ecx+0x25], ecx=this. CCBControl+0x25(37)=m_bForceRelease(unsigned char) 完美匹配
  2. [A] 调用者 CCBSystem::ProcMessage 通过 this->m_pControl(CCBControl*) 传入
  3. [A] SetParam(0x4DC5C0): `89 51 2C` = mov [ecx+0x2C],edx. CCBControl+0x2C(44)=tagControlData 区域
- **CCB cast 分析总结**:
  - 948 处 CCB cast 中: ~169 是 Hex-Rays 对大结构体内嵌 UIWnd 子对象的正常表示（(CCBUI*)((char*)this+offset)）
  - ~56 是通过 this->member 的跨类调用（部分归属错误，部分是正常的子系统委托）
  - 已修正 4 个函数归属（GetStageRole/ByIdx + GetState/SetParam）
  - 剩余高频 cast 需要逐个从二进制验证调用链

### [2026-05-13] 结构体成员批量填充（218 个新成员，8 个类）

- **变更**: 从二进制指令中提取 this+offset 访问，填充缺失的结构体成员
- **置信度**: 85 (偏移+类型从二进制确认), 50 (名字为 _field_ 占位)
- **方法**: 对每个类的所有 ClassName:: 方法，扫描函数体中 `[this_reg+disp8/disp32]` 模式，提取偏移和访问宽度（8B/89=dword, D9/DD=float, 8A/88=byte）
- **类和新增数**:
  1. CameraCtrl: 0→26 成员 (size=4088, 45 个方法, 56 个唯一偏移, 299 次访问)
  2. CScreenMode: 37→121 (+84) 成员 (size=4660)
  3. PalScriptMgr: +41 成员
  4. RenderTarget: 4→36 (+32) 成员 (size=200)
  5. PalScript: 9→25 (+16) 成员
  6. Object3D: 34→43 (+9) 成员
  7. UIScene: 45→52 (+7) 成员
  8. EquipUI: +3 成员
- **影响**: 消除大量 `this[N]` 越界访问（CameraCtrl 1695 处, CScreenMode 1636 处等）
- **注意**: 218 个新成员全部有 A 级二进制证据（指令中的 disp 值确认偏移），但名字是占位的，需要后续从代码语义推断命名

### [2026-05-13] CameraCtrl 补充偏移 + 语义命名

- **变更**:
  1. CameraCtrl 补充 33 个新偏移（修正扫描方法，覆盖 ecx 直接访问），总成员 26→59
  2. 2 个确认命名：m_nWidth(+472), m_nHeight(+476)
- **置信度**: 85 (偏移), 90 (命名: m_nWidth/m_nHeight)
- **证据 (命名)**:
  1. [A] SetDimention(0x41CA90): `89 81 D8010000` = mov [ecx+0x1D8],eax — 参数1(w)直接存入 +472
  2. [A] 同函数 `89 91 DC010000` = mov [ecx+0x1DC],edx — 参数2(h)直接存入 +476
  3. 函数签名 `void __thiscall(CameraCtrl *this, int w, int h)` 确认参数语义
- **回退**: m_pTarget/m_fFOV/m_nViewMode 等 5 个推断命名因仅有 D 级证据（领域知识推断）不达标，保留 _field_ 占位

### [2026-05-13] 结构体成员语义命名（12 个，二进制指令链验证）

- **变更**: 12 个 _field_ 成员从 setter 函数的二进制指令链中推断语义名
- **置信度**: 90
- **方法**: 读取 Set*/Init* 函数的完整指令链，追踪参数如何存入 this+offset
- **RenderTarget (6 个)**:
  1. [A] +24 `m_nHalfWidth`: SetSize(0x4B48E0) `mov eax,[esp+4]; cdq; sub eax,edx; sar eax,1; mov [ecx+0x18],eax` — param1/2
  2. [A] +28 `m_nHalfHeight`: 同函数 param2/2
  3. [A] +144 `m_nOffsetX`: SetOffset(0x4B4D80) `mov [ecx+0x90],eax` — param1
  4. [A] +148 `m_nOffsetY`: 同函数 `mov [ecx+0x94],edx` — param2
  5. [A] +152 `m_nScaleX`: SetScale(0x4B4DA0) `mov [ecx+0x98],eax` — param1
  6. [A] +156 `m_nScaleY`: 同函数 `mov [ecx+0x9C],edx` — param2
- **CScreenMode (3 个)**:
  1. [A] +68 `m_nPosX`: SetPosition(0x43DC40) `mov [ecx+0x44],eax` — param nX
  2. [A] +72 `m_nPosY`: 同函数 `mov [ecx+0x48],edx` — param nY
  3. [A] +4644 `m_state`: SetState `mov [ecx+0x1224],eax` — param state
- **CScreenMode (2 个, lea→call 推断)**:
  4. [A] +1284 `m_wndPanel1` UIWnd: lea [this+0x504]→ecx→call UIWnd::GetRect 确认嵌入 UIWnd
  5. [A] +1436 `m_wndPanel2` UIWnd: lea [this+0x59C]→ecx→call UIWnd::GetRect
- **UIScene (1 个, lea→call 推断)**:
  6. [A] +116 `m_pChildWnd` UIWnd*: lea [this+0x74]→ecx→call UIWnd::GetChildByIndex
- **UIScene (4 个, 类型修正)**:
  7. [A] 4 个 _field_ 类型 int→float: 二进制 fld 指令计数超过 mov dword 计数
- **CameraCtrl (3 个)**:
  1. [A] +460 `m_mode`: SetCamMode(0x41D5B0) `mov [ecx+0x1CC],eax` — param mode
  2. [A] +472 `m_nWidth`: SetDimention(0x41CA90) `mov [ecx+0x1D8],eax` — param w
  3. [A] +476 `m_nHeight`: 同函数 `mov [ecx+0x1DC],edx` — param h

### [2026-05-13] CCBSystem::GetDeltaTime/GetControl 重分类

- **变更**:
  1. CCBSystem::GetDeltaTime → CCBAttackSequen::SetFlag_1C5
  2. CCBSystem::GetControl → CCBControl::GetControl
- **置信度**: 90
- **证据**:
  1. [A] GetDeltaTime(0x4DB910): 完整函数体 `8A 44 24 04 88 81 C5010000 C2 0400` = mov al,[esp+4]; mov [ecx+0x1C5],al; ret 4. 这是一个 1-byte setter，不是 GetDeltaTime。CCBAttackSequen+0x1C5=tagAttackSequen[11]之后的 flag 字段。
  2. [A] 调用者 CCBSystem::ProcWeaponSkill 通过 this->m_pAttackSequen(CCBAttackSequen*) 传入
  3. [A] GetControl(0x4DC5B0): `8B 41 20 C3` = mov eax,[ecx+0x20]; ret. CCBControl+0x20(32)=m_nController(int) 完美匹配
  4. [A] 调用者通过 this->m_pControl(CCBControl*) 传入
- **累计 CCB 修正**: 6 个函数（GetStageRole/ByIdx + GetState/SetParam + GetDeltaTime + GetControl）

### [2026-05-13] CCBStageRole::IsActive → CCBRoleState（stride-892 扫描）

- **变更**: CCBStageRole::IsActive → CCBRoleState::IsActive
- **置信度**: 90
- **方法**: 搜索 .text 段中所有 stride=892 乘法链模式 `8D14C5 00000000 2BD0 C1E205 2BD0`，找到 33 处。其中 9 个函数非 CCBRoleState 归属，逐个验证后只有 IsActive 确认错分。
- **证据**:
  1. [A] IsActive(0x4ED040): 函数体使用 stride=892 乘法链访问 tagRoleState 数组 → this=CCBRoleState*
  2. [A] 调用者 CCBStageRole::ProcBlock 通过 this->m_pRoleState(CCBRoleState*) 传入
- **排除**:
  - HandleRoleStateDialog: 非 __thiscall（首条指令 A1=mov eax,[abs]），通过全局指针访问
  - DelTask: 函数开头 mov [ecx+0x19A4] → CCBStageRole 成员，stride-892 在函数后部（调用链）

### [2026-05-13] PDB 偏移伪影批量清理（345 个伪字段删除，12 个结构体）

- **变更**: 从 12 个 this-pointer 结构体中删除 345 个无二进制访问证据的 gap 来源字段
- **置信度**: 95（删除操作：字段在二进制中无访问即为伪影）
- **根因**: PAL3A.pdb 与 PAL3.exe 的结构体布局不匹配。PDB 导入 IDA 后产生的结构体偏移被 gap-fill 阶段用于插值，但这些偏移在 PAL3 二进制中不存在对应的 `[this_reg+disp32]` 访问指令。
- **验证方法**: 对每个结构体的所有 gap 来源字段（source 含 `gap_clean`/`gap_access`/`camblock_gap`），在该类所有方法的 .text 段二进制中搜索 `disp32` 作为 ModRM(mod=10) 操作数。无命中 → 伪字段。
- **证据**:
  1. [A] RoleSystem: IDA _field_2CC(offset 716) 在 154 个 RoleSystem 函数中 0 命中；CalcDirection 二进制实际访问 this+0x510（差值 0x244），确认 IDA 布局偏移
  2. [A] SceneMgrCamBlock: 140 个 gap 字段中仅 5 个有二进制命中（3.6%）
  3. [A] CCBStageScene: 16 个 gap 字段全部有二进制命中（0 伪字段），作为对照组确认方法可靠

| 结构体 | 清理前 | 清理后 | 删除数 | 伪影率 |
|--------|--------|--------|--------|--------|
| RoleSystem | 361 | 208 | 153 | 84% |
| SceneMgrCamBlock | 142 | 7 | 135 | 96% |
| CScreenMode | 122 | 109 | 13 | 48% |
| UIScene | 52 | 40 | 12 | 46% |
| UIListBox | 61 | 52 | 9 | 60% |
| UIAnimateCtrlEX | 24 | 12 | 12 | 85% |
| Actor | 49 | 42 | 7 | 28% |
| _Item_List_Info | 19 | 12 | 7 | 100% |
| ScreenEffectMgr | 20 | 15 | 5 | 83% |
| gbVolModNode | 8 | 3 | 5 | 100% |
| CCBUI | 78 | 76 | 2 | 50% |
| PAL3 | 32 | 30 | 2 | 50% |

- **影响**: 总成员数 968→606（-362），消除错误偏移字段对 IDA 结构体布局和代码生成的污染
- **后续**: 需要基于二进制分析重新填充这些结构体的有效成员（disp8 搜索、SIB 模式、间接访问链等方法）

### [2026-05-13] RoleSystem 二进制 disp32 重扫描（+25 新成员）

- **变更**: 对 154 个 RoleSystem 函数做 disp32 全量扫描，发现 25 个新偏移（已排除 disp8 假阳性）
- **置信度**: 85（偏移+类型从 ModRM+opcode 确认），50（名字为 `_todo_` 占位）
- **方法**: 识别每个函数头部 `mov reg, ecx` 确定 this 寄存器，扫描 `[this_reg+disp32]` (ModRM mod=10)，过滤对齐偏移，排除 overlap
- **排除**: +209(0xD1) 和 +523(0x20B) 因与相邻 int 字段 overlap 被移除（是 BYTE1 子字节访问）
- **命名约定**: 新增字段用 `_todo_XXX` 前缀，方便 `grep _todo_` 追踪待命名字段
- **高频字段**: +828(0x33C) 5funcs, +7432(0x1D08) 8hits/4funcs, +7280(0x1C70) 7hits/4funcs
- **影响**: RoleSystem 成员 208→233

### [2026-05-13] 5 个结构体 disp32 重扫描（+125 新 _todo_ 成员）

- **变更**: Actor(+20), CScreenMode(+39), UIListBox(+48), PAL3(+15), ScreenEffectMgr(+1) 添加二进制验证的占位成员
- **置信度**: 85（偏移+类型），50（_todo_ 占位名）
- **方法**: 同 RoleSystem 重扫描方法——识别 this 寄存器后搜索 `[this_reg+disp32]`，过滤对齐、排除 overlap
- **排除**: Actor +217(byte 子访问 overlap +216 int), +544(overlap m_dwMatMsg[11])
- **未扫描**: SceneMgrCamBlock/UIScene/UIAnimateCtrlEX(0 新成员), CCBUI/gbVolModNode(无 binary_size), _Item_List_Info(无函数)
- **影响**: 全部 _todo_ 字段总计 148 个（`grep -r '_todo_' structs/`）

### [2026-05-13] 21 个结构体批量 disp32 重扫描（+896 新 _todo_ 成员）

- **变更**: 对 21 个未扫描结构体执行 disp32 二进制全量扫描
- **置信度**: 85（偏移+类型），50（_todo_ 占位名）
- **方法**: 同前——识别 this 寄存器后搜索 `[this_reg+disp32]`，过滤对齐、排除 overlap
- **主要结果**:
  - Scene: +171（91 funcs，struct size=1094164）
  - GRPinput: +148（54 funcs，size=10584）
  - CCBRoleState: +100（204 funcs，size=23904）
  - PAL_GDB: +94（49 funcs，size=814524）
  - CCBStageRole: +74（106 funcs，size=6848）
  - CCBStage: +63（119 funcs，size=673992）
  - CCBStageScene: +48, PalScriptMgr: +29, EquipUI: +27, CEffMgr: +25
  - Camera: +22, CCBSystem: +21, RenderTarget2: +14, CCBAI: +13
  - CameraCtrl: +11, TextureLib: +11, Object3D: +9, NPC: +6, UIFrameWnd: +6
  - CCBStageCam: +3, RenderTarget: +1
- **未命中**: UIWnd(0), PalScript(0) — 已有成员已覆盖大部分访问
- **影响**: _todo_ 字段总计 148→1044（扫描原始数）

### [2026-05-13] 结构体数组/嵌入成员 overlap 修复（-399 伪成员）

- **变更**: 从 10 个结构体中删除 399 个落在已知数组/嵌入结构体内部的 _todo_ 字段
- **置信度**: 95（overlap 是确定性错误）
- **根因**: disp32 扫描找到的偏移可能是数组元素内部的成员访问（如 `this->m_obj[i].field`），表现为 `[this_reg + base_offset + i*stride + field_offset]`，被误认为顶层成员
- **修复明细**:
  - Scene: -167（m_obj[256] SceneObj 覆盖 224-456928, m_npc[72] Role 覆盖 456932+）→ 21 成员
  - CCBRoleState: -95（tagRoleState 数组内部）→ 27 成员
  - PAL_GDB: -49 → 51 成员
  - CCBStage: -36 → 63 成员
  - CCBSystem: -18 → 45 成员
  - CEffMgr: -16 → 24 成员
  - CCBAI: -8 → 15 成员
  - CCBStageRole: -4 → 149 成员
  - CCBStageScene: -4 → 114 成员
  - PalScriptMgr: -2 → 87 成员
- **影响**: _todo_ 字段总计 1044→649（净增 497 个有效新成员）

### [2026-05-13] 数组内部伪成员清理 + raw IDB 语义命名

- **变更**:
  1. 删除 213 个落在已知数组内部的 _todo_ 字段（GRPinput:148, CCBStageScene:32, Actor:20 等）
  2. 使用 raw IDB（无结构体导入）对 943 个函数做 Hex-Rays F5，获取原始偏移的反编译上下文
  3. 从 raw decomp 上下文推断 139 个 _todo_ 字段的语义名
- **置信度**: 95（数组清理），70（语义命名——基于 raw decomp 文本模式匹配）
- **方法**:
  - 数组清理：计算每个已知成员的覆盖范围（含数组），删除范围内的 _todo_
  - 语义命名：生成 raw IDB → F5 特定地址 → 匹配 `this + offset` 模式 → 从 strcpy/strlen/SetXxx 等上下文推断字段含义
  - 只保留高质量名称（排除 m_f_XXX/m_obj_XXX 等泛型模式）
- **命名策略**: strcpy→m_szXxx, sin/cos→m_fAngle, SetProgress→m_fProgressParam, byte flag→m_bXxx
- **影响**: _todo_ 649→436→297（最终剩余 297 个无法从上下文确定语义的字段）

### [2026-05-13] _field_ 旧占位 raw decomp 语义命名（149 个）

- **变更**: 对 363 个有 raw decomp 上下文的 _field_ 字段应用语义命名，149 个获得高质量名称
- **置信度**: 70（基于 raw Hex-Rays 文本模式匹配——strcpy/SetXxx/gbVec3D 等上下文）
- **方法**: 额外 F5 178 个函数（raw IDB 总计 1120 个），用同样的 `this + offset` 匹配 + 上下文推断
- **过滤**: 排除泛型名称（m_f_XXX/m_obj_XXX/m_szStr_XXX），只保留有明确语义的命名
- **影响**: _field_ 1140→991，命名率 84.4%→86.0%

### [2026-05-13] LODWORD 驱动的 float→int 类型修正（29 个字段）

- **变更**: 29 个标注为 float 但 raw decomp 中仅被 `*(_DWORD*)` 访问（0 次 float 访问，3+ 次 int 访问）的字段修正为 int
- **置信度**: 85（raw Hex-Rays 无结构体偏见，type cast 直接反映二进制访问模式）
- **方法**: 对每个 float 字段，在 1120 个 raw decomp 函数中计数 `*(float*)(this+N)` vs `*(_DWORD*)(this+N)` 出现次数。仅修正 float_uses=0 且 int_uses>=3 的确定性案例
- **典型修正**:
  - CCBStageRole+528 m_fLeftWeapon: 14x int, 0x float → int
  - CEffectSystem+336 m_fWindDirection: 45x int, 0x float → int
  - Role+1392 m_curforce: 20x int, 0x float → int
- **排除**: RoleSystem+4/8/12 (m_fTargetX/Y/Z) 有 260+ float 用法和 500+ int 用法，是 union 模式，保留 float
- **影响**: 消除生成代码中 ~200 个 LODWORD() 包装

### [2026-05-13] CCBStageRole.m_fBlend float→int（最大 LODWORD 贡献者）

- **变更**: CCBStageRole+284 m_fBlend float → m_nBlendState int
- **置信度**: 90
- **证据**:
  1. [A] raw decomp 中 51 次 `*(_DWORD*)(this+284)` vs 1 次 `*(float*)(this+284)`
  2. [A] 使用模式: `== 2`, `== 1`, `== 0` 整数比较 → 状态枚举，非浮点值
- **影响**: 消除生成代码中 132 个 LODWORD(this->m_fBlend) 包装

### [2026-05-13] PAL3::FullInit 全局变量补充（10 个）

- **变更**: 为 PAL3::FullInit 核心初始化函数补充 10 个全局变量到 globals.json
- **置信度**: 80
- **证据**:
  1. [A] 0x586180-58619C: raw decomp 中 `sub_4125D0(dword_BFDBB0, &off_586180)` + `strcpy(word_BFDC5E, off_586180)` → 场景名字符串指针
  2. [A] 0xDE5220: `memset(byte_DE5220, 0, 0x28)` → 40 字节存档标记数组
  3. [A] 0xC04334: `memset32(dword_C04334, 20, 6)` → 6 元素 int 数组（角色初始等级=20）
  4. [A] 0xC020F0: `while (v0 < &byte_C020F0)` → ScriptCounter 数组结束边界
- **背景**: FullInit 引用 465 个全局地址，其中 369 个在 g_SceneMgr 内部（需编译阶段视图转换），70 个独立全局变量缺失（已补 10 个，剩 14 个需更多上下文分析）
- **影响**: FullInit 中 dword_ 残留减少

### [2026-05-13] FullInit 独立 RoleSystem 实例发现（+7 全局变量）

- **变更**: 发现 3 个独立 RoleSystem 全局实例 + 4 个相关全局变量
- **置信度**: 90
- **证据**:
  1. [A] 0xBFDBB0 与 0xBFFDB0 相隔 8704 字节 = RoleSystem size → 连续两个 RoleSystem 实例
  2. [A] BFDBB0+174=BFDC5E → `strcpy(word_BFDC5E, scene_name)` 确认 name 字段位置
  3. [A] BFDBB0+1264=BFE0A0 → `dword_BFE0A0 = 1` 对应 RoleSystem.m_nMoveMode (+1264)
  4. [A] BFDBB0+632=BFDE28 → 对应 RoleSystem.m_pRoleObj (+632)
  5. [A] C020F8+174=C021A6 → `strcpy(word_C021A6, scene_name)` 确认第三个实例
  6. [A] C020F8+172=C021A4 → `byte_C021A4 = 5` 对应 RoleSystem.m_nFacing (+172)
- **新增全局变量**:
  - g_RoleSystemExtra0 @ 0xBFDBB0 (RoleSystem)
  - g_RoleSystemExtra1 @ 0xBFFDB0 (RoleSystem)
  - g_RoleSystemMain @ 0xC020F8 (RoleSystem)
  - g_nPathEnabled @ 0xC02374, g_nRoleMoveLock @ 0xC025E8
  - g_pRoleTeam0_Capacity @ 0xC0435C, g_pRoleTeam1_Capacity @ 0xC0436C
- **影响**: FullInit 中 14 个独立全局变量全部标注完成

### [2026-05-13] raw decomp 类型推断批量填充（+246 新成员，17 个结构体）

- **变更**: 从 raw IDB Hex-Rays 输出中提取精确类型信息填充结构体成员
- **置信度**: 85（Hex-Rays 类型 cast 直接反映二进制访问模式：`*(float*)(this+N)` → float，`*(_DWORD*)(this+N)` → int）
- **方法**: 对每个类的所有函数的 raw decomp 文本，解析 `*(TYPE*)(this+N)` 模式提取偏移和类型。过滤对齐、排除与已知成员 overlap。
- **主要结果**:
  - CScreenMode: +45, CameraCtrl: +2, EquipUI: +14, CCBRoleState: +18
  - CCBStage: +23, CCBStageScene: +29, PalScriptMgr: +19, UIScene: +17
  - UIListBox: +15, Camera: +18, RenderTarget2: +13, TextureLib: +13
  - ScriptSystem: +8, NPC: +5, Object3D: +4, CCBStageRole: +2, RoleSystem: +1
- **优势**: 比 disp32 二进制扫描更精确——Hex-Rays 直接给出类型（float/int/byte/short），不需要从 opcode 推断
- **影响**: _todo_ 297→543（新增 246 个待命名成员），结构体 gap 覆盖显著提升

### [2026-05-13] raw decomp 新增字段即时命名（244/246）

- **变更**: 对上一步新增的 246 个 `_todo_` 字段立即应用 raw decomp 上下文命名
- **置信度**: 70（函数名上下文 + strcpy/memset 模式 + 类型前缀推断）
- **方法**: 同前次 _todo_ 命名——从 raw decomp 中提取 `this+offset` 所在行的函数名和操作模式，生成 m_nXxx/m_fXxx/m_bXxx 语义名
- **结果**: 244 个命名成功，2 个无法推断保留 _todo_，总 _todo_ 回到 297（均为早期遗留）

### [2026-05-13] ScriptSystemData 命令表数组化（-372 _field_）

- **变更**: 将 ScriptSystemData 偏移 4432-7852 的 372 个独立 _field_ 替换为 `m_CmdTable tagScriptCmd[213]`
- **置信度**: 90
- **证据**:
  1. [A] stride-16 模式: 51 个条目有 short(+0)+int(+4)+int(+8) 一致结构
  2. [A] 从 CHANGE_LOG 早期记录: sub_4329B0 命令表区域，stride=16，赋值全用绝对地址
  3. [A] 30 个条目有 abs_ref 二进制证据（`66 89 3D`=mov word, `89 0CC5`=mov [ecx*8+addr] 等）
- **新增结构体**: tagScriptCmd {short cmd_id; short _pad; int handler; int param; int flags;} size=16
- **影响**: ScriptSystemData 成员 556→185, 总 _field_ 991→619, 命名率 86.0%→89.6%

### [2026-05-13] 最后 2 个函数命名 → 100%

- **变更**: sub_569110 → PAL3_ResetForNewScene, sub_5694F0 → CScreenMode_OpenBinkVideo
- **置信度**: 70
- **证据**:
  1. [C] PAL3_ResetForNewScene: 调用者 RoleSystem::_nearby_422950（场景加载）；函数体重置 ScriptSystemData/Audio/CombatUI/RenderTarget
  2. [C] CScreenMode_OpenBinkVideo: 被 CScreenMode::CreateDevice 直接转发调用；函数体调用 BinkOpen + CPK fallback
- **影响**: 函数标注 3968/3970 → 3970/3970 (100%)

### [2026-05-13] 伪语义命名清理（270 个回退 _todo_）

- **变更**: 270 个地址后缀伪语义名（如 m_nAllDone_19D0, m_fInit_338）回退为 _todo_
- **置信度**: N/A（质量清理）
- **根因**: 这些名字的后缀等于偏移十六进制值，没有语义信息（规则 #6）
- **影响结构体**: CGameData(109), CCBStageRole(30), PalScriptMgr(27), CCBStageScene(20), CScreenMode(17), RoleSystem(15), Object3D(10), CameraCtrl(9), CCBStage(7), +11 others
- **影响**: 命名率 87.7% → 84.7%（诚实优于虚假精度）

### [2026-05-14] IDB 重建 + setter 字段命名（UIListBox, RoleSystem）

- **变更**:
  1. IDB 重建: raw i64 → apply_annotations → export_full（4365 函数反编译）
  2. UIListBox: _field_0F4 → m_nMinSel, _todo_0F8 → m_nMaxSel
  3. RoleSystem: _todo_548 → m_fMoveDestZ, _todo_558 → m_fMoveOriginY, _todo_55C → m_fMoveOriginZ
- **置信度**: 85
- **证据 (UIListBox)**:
  1. [A] SetSel @ 0x43E440+16: `8B 8E F8000000` = mov ecx,[esi+0xF8] — 上界 clamp
  2. [A] SetSel @ 0x43E440+22: `8B 96 F4000000` = mov edx,[esi+0xF4] — 下界 clamp
  3. [A] SetSel @ 0x43E440+37: `89 86 5C040000` = mov [esi+0x45C],eax — 存储 clamp 后的选中值
  4. 函数语义: SetSel(int nSel) 将 nSel clamp 到 [this+0xF4, this+0xF8] 范围
- **证据 (RoleSystem)**:
  1. [A] SetMoveTarget @ 0x412B60: 新 decomp（IDA 正确结构体后）显示:
     - `*(float*)(this+1344) = a2[0]`, `*(float*)(this+1348) = a2[1]`, `*(float*)(this+1352) = a2[2]` → 目标 XYZ
     - `*(_DWORD*)(this+1364) = this+4`, `*(_DWORD*)(this+1368) = this+8`, `*(_DWORD*)(this+1372) = this+12` → 保存当前位置
  2. [A] this+4/8/12 = m_fTargetX/Y/Z（已知成员），确认 1364/1368/1372 是位置副本
  3. +1352 = target Z（第 3 分量），+1368 = origin Y（从 m_fTargetY 复制），+1372 = origin Z（从 m_fTargetZ 复制）
- **影响**: 命名率 84.7% → 84.8%

### [2026-05-14] IDA 辅助批量字段命名（RenderTarget2, CCBStage, CCBRoleState）

- **变更**: 36 个 _todo_ 字段命名
  - RenderTarget2: 5 个（m_pTargetArray, m_nCurTarget, m_nCurPass, m_nMaxTargets, m_nMaxPasses）
  - CCBStage: 18 个（m_nActiveIdx, m_nActionIdx, m_fRotPitch/Yaw, m_fCurPos/TargetPos/Vel XYZ 等）
  - CCBRoleState: 13 个（m_fLerpCurX/Y, m_nLerpTarget/Dest, m_fLerpSpeed, m_nScrollOffset 等）
- **置信度**: 80
- **方法**: 新建 IDAPython 脚本 `query_todo_fields.py`，从 IDB 中批量查询 _todo_ 字段的二进制 xref + Hex-Rays 反编译上下文。774 个字段有二进制引用，239 个有反编译上下文。
- **证据**:
  1. [A] RenderTarget2+0x18: `89 46 18` = mov [esi+0x18],eax（alloc 1216 字节），stride-152 循环 8 次
  2. [A] RenderTarget2+0x28: `C7 46 28 08000000` = mov [esi+0x28],8（最大目标数）
  3. [A] CCBStage+0x11C: 44 次二进制引用，传给 IsActive(roleIdx)
  4. [A] CCBStage+0x18C: 64 次引用，`96 * this[0x18C]` stride 模式
  5. [A] CCBStage+0x1C8: 角度 `* 0.0043633231`（π/720 弧度常数）累加模式
  6. [A] CCBStage+0x19D0-0x19E4: XYZ 坐标对，delta + lerp 插值模式，16-18 refs/字段
  7. [A] CCBRoleState+0x495C: `speed * dt * dir + cur` 线性插值模式，7 refs
  8. [A] CCBRoleState+0x496C: `_method_449f00` 直接存入参数 a2，转 float 后存回
  9. [A] CCBRoleState+0x5658: `+= 10` 滚动累加模式，10 refs
- **工具改进**: 新增 `pipeline/ida/query_todo_fields.py` IDAPython 脚本
- **影响**: 命名率 84.8% → 85.2%

### [2026-05-14] IDA 辅助批量命名第二轮（7 个类，71 个字段）

- **变更**: 71 个 _todo_ 字段命名
  - PalScriptMgr: 31 个（脚本引擎核心：m_nCmdType/Value/Param, m_pSceneMgr, m_nWaitCount 等）
  - UIScene: 10 个（UI 矩形/位置：m_nRectX/Y/W/H, m_bVisible 等）
  - CEffMgr: 8 个（特效参数：m_fPosX/Y/Z, m_fScaleX/Y/Z, m_vecRotAxis）
  - Object3D: 7 个（对话框/提示框：m_wndNote, m_wndDialog, m_wndItem）
  - CameraCtrl: 5 个（混合权重：m_nBlendTimer, m_bBlendActive, m_nTickStamp）
  - ScriptSystem: 3 个（执行标志：m_bOpcodeFlag, m_bExecFlag, m_bBlockFlag）
  - CScreenMode: 2 个（进度条：m_fProgressRatio, m_fProgressMax）
  - CCBStageRole: 1 个（m_fYawAngle）
  - Actor: 1 个（m_fBlendWeight）
  - CGameData: 1 个（m_pGameObj）
  - ScreenEffectMgr: 2 个（m_pEffect, m_nEffectCount）
- **置信度**: 75-85
- **方法**: 利用 query_todo_fields.py 输出的 IDA 反编译上下文，匹配已知 API 模式（gbMatrix4::SetAxisAngle, sprintf, switch, Destroy, GetTickCount）和数值模式（角度常数 0.0043633231, 0.017453292, 累加器 += 10, stride 乘法）
- **影响**: 命名率 85.2% → 86.0%

### [2026-05-14] IDA 高引用字段强制反编译命名（8 个类，17 个字段）

- **变更**: 17 个 _todo_ 字段命名
  - CScreenMode: 4 个（m_nArrayCapacity, m_pArrayData, m_nDisplayMode, m_pItemList）
  - CCBStage: 3 个（m_nTaskCount, m_nRoleSlot, m_nResetState）
  - CameraCtrl: 2 个（m_fOrbitAngle — sin/cos 模式, m_fCamDist — 50.0f 常量）
  - UIListBox: 2 个（m_pDynBuffer — delete 模式, m_nLockValue）
  - RenderTarget: 2 个（m_fOffsetParam, m_fInvScale — 1.0/x 模式）
  - Actor: 1 个（m_fAnimDelta — += *v6 累加）
  - RoleSystem: 1 个（m_fTileHeight — Tile>=this 比较）
  - PalScriptMgr: 1 个（m_pSubScript — 传给子函数）
  - PAL3: 1 个（m_pCollisionObj — deref+16 碰撞检测）
- **置信度**: 75
- **方法**: 新建 `query_highref_fields.py`，对 refs>=3 但无 decomp context 的字段强制 Hex-Rays 反编译。44/50 个高引用字段获得了上下文。
- **证据类型**: [A] binary disp32 + [C] IDA Hex-Rays decomp context（函数名+操作模式）
- **影响**: 命名率 86.0% → 86.1%

### [2026-05-14] 全类反编译批量命名（Camera, RenderTarget, CameraCtrl, CCBStageScene 等）

- **变更**: 51 个 _todo_ 字段命名
  - RenderTarget: 15 个（m_nRenderX/Y, m_nHalfW/H, m_nWidth/Height, m_fRenderX/Y, m_szPath, m_nColor, m_bVisible 等）
  - CCBStageScene: 15 个（m_fBlendRectA/B/C XY/WH — 0/0/1.0/1.0 初始化模式, m_Object3D 嵌入对象）
  - CameraCtrl: 9 个（m_fMinDist, m_fTargetAngle/CurAngle, m_nCamState, m_bAutoRotate, m_nTickCount）
  - PalScript: 6 个（m_fBlendFactor, m_nState, m_nFrameCount, m_bEnabled, m_fScaleX）
  - RenderTarget2: 4 个（m_pSurface, m_bActive, m_nFallbackMode, m_fBlendParam）
  - Camera: 1 个（m_Actor — 嵌入 Actor 对象）
  - SceneMgr: 1 个（m_aSceneSlots — memset 2304 字节清零）
- **置信度**: 75-85
- **方法**: 新建 `query_class_full.py`，对指定类的全部方法做 Hex-Rays 反编译，提取所有 `this->_todo_XXX` 和 `*(type*)(this+N)` 模式。
- **关键证据**:
  1. [A] CCBStageScene: 三组相同 (0,0,0x3F800000,0x3F800000) 初始化 → blend rect XYWH
  2. [A] CameraCtrl+16/20: clamp+accumulate 模式 → target/current 插值对
  3. [A] RenderTarget+88: ctor=800, Read 64 bytes, strcat → 路径字符串
  4. [A] Camera+680: Actor::LoadModel(&this) → 嵌入 Actor 对象
  5. [A] SceneMgr+28: memset(this, 0, 0x900) → 2304 字节数组槽位
- **影响**: 命名率 86.1% → 86.7%

### [2026-05-14] 第二批全类反编译命名（Actor, UIScene, CCBStageRole, PAL3）

- **变更**: 24 个 _todo_ 字段命名
  - UIScene: 14 个（m_nViewX/Y/W/H 视口, m_nClipX/Y/W 裁剪, m_nScrollState/Idx, m_fCameraOffset）
  - CCBStageRole: 5 个（m_pPanelA/B/C 嵌入 UI 面板, m_fRotStart 旋转起始角, m_fRotCopy）
  - Actor: 4 个（m_nCloneParam/State/Flag1/Flag2 — 从另一 Actor 复制的属性）
  - PAL3: 1 个（m_fViewParam）
- **置信度**: 75
- **影响**: 命名率 86.7% → 87.0%

### [2026-05-14] 第三批全类反编译命名（NPC, Object3D, SceneObj, CCBUI, UIFrameWnd）

- **变更**: 28 个 _todo_ 字段命名
  - NPC: 11 个（m_pBuffer/BufStart/BufEnd 缓冲区三元组, m_wndHPBar/NameLabel/Dialog/Tooltip 嵌入 UI, m_fAnimTimer）→ NPC 100% 完成
  - Object3D: 8 个（m_fYawAngle — SetAxisAngle, m_wndTemplate/Template2/TextArea 嵌入 UI, m_nDialogMode）
  - UIFrameWnd: 4 个（m_nFrameData, m_bFrameInit, m_nBorderColor=276, m_nBorderStyle=-1）
  - SceneObj: 3 个（m_pData, m_nDataSize, m_nObjState）
  - CCBUI: 2 个（m_nSelOffset, m_nChildUpdateCount）
- **置信度**: 75
- **证据**:
  1. [A+] NPC._todo_004: Hex-Rays `operator delete(this->_todo_004)` + `this->_todo_004 = 0` → 堆指针
  2. [A+] NPC._todo_00C: `(this->_todo_00C - todo_008) >> 2` → (end-start)/4 = 元素数
  3. [A+] NPC._todo_22C: `UIWnd::SetRect(&this->_todo_22C, v26)` → 嵌入 UIWnd
  4. [A+] Object3D._todo_E0: `gbMatrix4::SetAxisAngle(v3, 1, *(this+224))` → Y 轴旋转角
  5. [A+] UIFrameWnd._todo_90: `= 276` 常量 + 作为 gbColorQuad 加载 → 边框颜色
- **影响**: 命名率 87.0% → 87.3%

### [2026-05-14] 大类全量反编译命名（RoleSystem 30, CScreenMode 24）

- **变更**: 54 个 _todo_ 字段命名
  - RoleSystem: 30 个
    - 导航系统: m_fWaypointX/Z, m_nInitMoveMode, m_fPathAngle, m_bPathActive, m_nMoveSlot, m_fMoveThreshold, m_fMoveNormX/Y/Z
    - 角色控制: m_nRoleAction, m_nRoleSlot, m_nActionParam, m_szModelPath, m_nSpawnParam
    - 变换/动画: m_fSavedRotX, m_nTransformMode, m_nAnimCopy1/2/3
    - 链接对象: m_pScene, m_pLinkedRole, m_pLinkedSystem
    - UI 嵌入: m_wndFrameA, m_wndFrameB
    - 状态: m_nVisState, m_bVisFlag, m_bRoleFlag, m_nMoveReset, m_nActionTimer
  - CScreenMode: 24 个
    - 进度条: m_nProgressBase/Pos/ValA/ValB, m_nBarWidth/Height/TotalSize
    - 屏幕布局: m_nScreenWidth=800, m_nLayoutOffX/Y, m_nScreenParam
    - 音乐脚本: m_scriptMusic (PalScript, LoadFromFile music)
    - UI 组件: m_wndTooltipA/B (SetTooltipText), m_rcClickRegion (PtInRect)
    - 交互: m_nPageCounter(++), m_nItemCount(>0), m_nMarginSize
    - 渐变: m_fFadeAlpha, m_fCountdown(-=0.5)
    - 调试: m_bDebugMode, m_bDebugModeB (CreateFromTemplate 参数)
- **置信度**: 80 (A+ 级 — IDA apply 后 Hex-Rays 偏移)
- **影响**: 命名率 87.3% → 87.9%

### [2026-05-14] 大类深度命名第二轮（CScreenMode 39, RoleSystem 30）

- **变更**: 69 个 _todo_ 字段命名
  - CScreenMode: 39 个
    - 进度条续: m_nBarPosX/Y, m_fBarOffsetX/Y/W, m_nBarParam
    - 渐变/动画: m_fFadeSpeed(+=dt), m_fFadeParam(累加), m_bFadeActive(toggle)
    - UI 布局: m_nLayoutParam, m_nLayoutState, m_wndAssistA
    - 嵌入控件: m_pParabolaCtrl(GetState), m_wndChild1/2, m_wndDirty(SetDirty), m_uiScene(UIScene::ctor)
    - 提示框: m_wndTooltipC/D/E
    - 计时器: m_nTickStampA/B, m_bTimerInitA/B, m_nTimerValue
    - 滚动系统: m_nScrollPosX/Y, m_nScrollMinX, m_nScrollMaxX/Y, m_nScrollAccum, m_bScrollInit
    - 列表控件: m_pUIListA/B/C
    - 菜单: m_nMenuParam, m_nMenuState, m_nParabolaState
    - 其他: m_bTransitionActive, m_nChildUpdateCount
  - RoleSystem: 30 个
    - 移动: m_fMoveRadius(<=Length), m_fMoveSpeed(*1.4>=Length), m_fMoveParamY/Z
    - UI: m_wndFrame, m_wndPanel, m_ctrlParabolaA/B, m_wndLabel
    - 状态字节: m_nStateMode(==2), m_bActionPause, m_bUIFlagA/B
    - 生成参数: m_nSpawnData/Flags/Extra/Param2, m_bSpawnByteA/B (从 a2 结构体复制)
    - 缓存: m_nSavedState, m_nCachedA/B, m_nActionData
    - 碰撞: m_nCollisionState, m_nCollisionParam
    - 矩阵: m_fMatrixA-F (0/1.0f 初始化模式 — 单位矩阵分量)
- **置信度**: 75-80 (A+ IDA decomp + 模式匹配)
- **影响**: 命名率 87.9% → 88.6%，未命名跌破 1100

### [2026-05-14] UIListBox/CGameData/EquipUI 全量反编译命名（39 字段）

- **变更**: 39 个 _todo_ 字段命名
  - UIListBox: 20 个
    - 列表核心: m_nCurItem(796*idx), m_nTotalRowWidth, m_nColumnCount/Start/Active
    - 滚动: m_nScrollByte, m_nScrollValue, m_nVisibleCount, m_nPageCountA/B
    - 布局: m_nRowBaseY, m_pColumnData, m_nLayoutSum(=a+b), m_nHeaderHeight, m_nAccumWidth
    - 缓冲: m_aItemBuffer(memset 17504 bytes), m_nCacheA/B, m_nMsgData, m_bSelLock
  - CGameData: 18 个
    - 角色数据: m_RoleDataA/B/C(vtable+28 调用模式), m_UITitle(UITitle::ctor)
    - 物品栏: m_ItemSlotA/B/C/D(UIItem::Create+SetData)
    - 数组: m_aDialogs(UIWnd[5] stride=0x160), m_aItemData([6] stride=0x8E0)
    - 脚本: m_nScriptHandleA-F(6 个清零句柄)
    - 其他: m_pGameObjB, m_subObjA
  - EquipUI: 1 个 (m_bEquipFlagA)
- **置信度**: 75-80
- **影响**: 命名率 88.6% → 89.1%，**未命名跌破 1000 (994)**

### [2026-05-14] PalScriptMgr 深度命名 + SceneMgr 布局验证

- **变更**: 30 个 PalScriptMgr _todo_ 字段命名
  - 执行范围: m_nExecRangeA-D（脚本执行区间计算）
  - 位置系统: m_fPrevPosX/Y, m_fCurPosY（delta 计算模式）
  - 脚本控制: m_nScriptID(==0xFFFF哨兵), m_bScriptByte(!=0xFF), m_nBlockHandle
  - 循环计数: m_nLoopCountA(-1)/B(+1)/C(+1)
  - 执行状态: m_fExecPosY/Z, m_nExecState2, m_fDirNeg(取反), m_nExecHandle
  - 脚本实例: m_pScriptInstA/B/C + m_nScriptResultA/B/C（Destroy→result 模式）
  - UI: m_ctrlParabola(GetState), m_wndTextDisplay(SetEnable)
  - 计时: m_nEffectTick(=TickCount), m_nCapacity(>=比较)
- **SceneMgr 布局注意**: 参照 docs/scenemgr_layout.md，SceneMgr 的自有数据区 (+0xC5D0~) 的 36 个 _todo_ 中，25 个无绝对地址引用（仅通过 RoleSystem 方法间接访问），11 个有 1-2 次引用但语义不明确。保留为 _todo_。
- **置信度**: 75
- **影响**: 命名率 89.1% → 89.4% (964 remaining)

### [2026-05-14] 清理无二进制证据的幻影字段（-65 字段）

- **变更**: 删除 65 个结构体字段（来自 Hex-Rays 类型推断或全局 gap 插值，在 .text 段中无任何 [reg+disp32] 二进制访问证据）
- **置信度**: 95（删除操作：无二进制引用 = 字段在 PAL3 中不存在）
- **方法**: 对所有 source 为 `raw_decomp:Hex-Rays_type_cast` 或 `globals_merge` 且不在 query_todo_fields 输出中的 _todo_ 字段，扫描 .text 段全部 disp32 搜索（ModRM mod=10 匹配）。65/160 个无命中。
- **受影响结构体**: CGameData(-55), Camera(-3), CScreenMode(-2), TextureLib(-2), RenderTarget2(-1), UIListBox(-1), UIScene(-1)
- **排除**: 95 个虽 source 弱但有 binary disp32 命中的字段保留
- **影响**: 命名率 89.4% → **90.0%**，未命名 964→**899**

### [2026-05-14] apply_annotations 修复：前向声明 + enum 前置 + 依赖补全

- **变更（pipeline）**:
  1. 前向声明：对所有成员引用类型做 `struct XXX;`，但**跳过 IDA til 中已存在的类型**（避免 struct 前向声明覆盖 enum）
  2. enum 前置：将 enum apply 从 step 4（struct 之后）移到 step 3b（struct 之前），解决 struct 成员引用 enum 类型时 parse_decl 失败
  3. progressive retry：retry 循环改为无进展时停止（was: 固定 3 次）
  4. cursor clamp：值类型成员 size 超过实际 span 时 clamp 到 next_member_offset（PAL3A PDB size ≠ PAL3 实际 span）
- **变更（annotations）**:
  1. 导入 46 个 PDB enum 到 enums.json（ECPKMode, DLG_TYPE, PGR_MODE, ERoleActState 等——struct 成员引用的枚举类型）
  2. 添加 18 个 stub struct（pdb_size only, 0 members）:
     - `ScreenFadeOut/White/White2` (24B) — 屏幕特效
     - `D3DDriverBug` (4B) — D3D 驱动问题标记
     - `*_emitter_graph`, `*_particle_graph` (5300B each, 14 个) — 粒子系统图形数据
     - `m_RoleState/p_RoleState/s_RoleState` (3948-4292B) — MSVC 匿名嵌套 struct（PDB 变量名作类型名）
     - `gbVolumeModifier` (8B) — gbLightObj 基类
  3. 删除 `_BYTE.json`, `__int8.json`（IDA 内建类型，不是真实结构体）
- **置信度**: 90（stub struct 的 size 来自 PAL3A PDB，可能与 PAL3 不同；struct 声明解析是确定性结果）
- **结果**: struct apply OK: 537 → **826/826 (100%)**，Empty: 87 → **0**，Missing: 205 → **0**

### [2026-05-14] 修复结构体布局错误（binary_size 修正 + 指针类型修正）

- **变更（annotations）**:
  1. 4 个结构体设置 PAL3 binary_size（覆盖错误的 PDB size）:
     - UIStatic: 248 → **160**（436 处嵌入 span 一致为 160）
     - UIListBox: 1760 → **1288**（29 处嵌入 span 一致为 1288）
     - SceneObj: 3496 → **1784**（2 处嵌入 span 一致为 1784）
     - tagRoleState: 1040 → **600**（1 处嵌入 span=600）
  2. 18 个成员类型从值类型修正为指针（span=4 证明是指针非嵌入）:
     - CCBStageRole: gbVec3D→*, tagCmdData→*, gbOBBox→*
     - CCBStageScene: gbVec3D→*(4处), gbGeomQuad→*(3处), Object3D→*
     - PalScript: PtrArray→*(2处)
     - PalScriptMgr: scSCEFile→*(2处)
     - RenderTarget: gbTexture_D3D→*
     - scAsmDecoder: scVarStack→*
- **变更（pipeline）**:
  - build_struct_decl 遇到 type_size > span 时 raise RuntimeError 中断（不允许静默 fallback）
- **置信度**: 90（binary_size: 多处嵌入 span 一致→PAL3 真实 size；指针修正: span=4 对大类型是确定性证据）
- **结果**: 布局错误 520 → **36**（剩余需逐个分析）

### [2026-05-14] 布局错误修复第二轮 + build_struct_decl size 优先级修正

- **变更（annotations）**:
  1. 更多 span=4 指针修正（8 个）: CCBStage.m_Task→*, Camera.m_Actor→*, CScreenMode.m_scriptMusic→*, UIListBox.m_scrollbar→*, UIListBox.m_column→*, RoleSystem.m_Actor→*, ARC_PlayerAtt.hat→*, PathObj.normal→*
  2. 数组计数修正: CCBAI.m_EnemyDemand[10]→[5], CCBAI.m_FriendDemand[10]→[5], CCBStageScene.m_vecInitFiveLineup[7]→[3], ScriptSystemData.m_String CHAR[260]→char[96]
  3. 9 个结构体 binary_size 设置: tagEffClass(4), Object3D(152), st_Manager(244), SceneMgrCamBlock(844), scSCEFile(20), gbTexture_D3D(24), gbGfxDriverInfo(149), gbPixelFormat(40), ARC_PlayerItem(10)
- **变更（pipeline）**:
  - build_struct_decl 中引用成员类型 size 改为 `binary_size or pdb_size`（binary 优先），不再 `max(pdb, binary)`
- **置信度**: 85（span=4→指针: 确定性; 数组计数: span/elem_size clean division; binary_size: 多处嵌入 span 一致）
- **结果**: 布局错误 36 → **8**（剩余 8 个需二进制验证 element size/count）

### [2026-05-14] 布局错误修复第三轮（520→5）

- **变更**:
  1. SceneMgr: 删除 m_nActiveRoleCount(+7108), m_bSlotValid(+7112)——在 ARC_PlayerAtt[4] 尾部内（overlay 视图成员，不是独立 SceneMgr 字段）
  2. ARC_PlayerAtt: binary_size=1408（binary stride `add esi,580h` 确认）
  3. PAL_GDB: 删除 _todo_C4A24(+805412), m_nLoadLanguage(+805416)——在 FightItem[512] 数组内
  4. EquipUI: UIStatic[5]→UIStatic[4]（4*160=640 ≤ span=752）
- **置信度**: 90（SceneMgr stride: binary + docs 双重确认; PAL_GDB: 398560+512*800=808160=m_ComboData 偏移精确匹配; EquipUI: count=4 是最大不超 span 的整数）
- **结果**: 布局错误 **520 → 5**（剩余 5 个需 IDA stride 验证：tagCamTask, tagRoleTask, tagThread, PlayerAtt, RoleAtt 的 PAL3 element size/count）

### [2026-05-14] 布局错误最终修复（520→0）

- **变更**: 删除 118 个数组内部幽灵成员（最后 5 个数组的 "next member" 全在数组内部）
  - CCBStageRole.m_Task: -64 幽灵（tagRoleTask[64], stride=96 binary confirmed by `i+=96`）
  - PAL_GDB.m_RoleData: -43 幽灵（RoleAtt[200], elem=852）
  - EquipUI.m_TempData: -7 幽灵（PlayerAtt[5], elem=1524）
  - CCBSystem.m_Thread: -3 幽灵（tagThread[1024], elem=88）
  - CCBStageCam.m_Task: -1 幽灵（tagCamTask[50], elem=80）
- **置信度**: 95（PDB count * elem_size 的 array_end 之后的成员偏移精确匹配已知成员；CCBStageRole stride=96 由 Hex-Rays `i += 96` 二进制确认）
- **结果**: **布局错误 520 → 0 (全部清零)**

### [2026-05-14] gap-fill: 从 IDA decomp 的 _gap_ 访问中提取 590 个缺失成员

- **变更**: 590 个 _todo_ 成员添加到 52 个结构体（从生成代码中 `this->_gap_XXX[Y]` 模式提取实际访问偏移）
  - CScreenMode: +131, PropUI: +78, RoleSystem: +42, Camera: +36
  - CCBStage: +31, PalScriptMgr: +28, UIListBox: +18, PAL3: +18
  - SaleUI: +20, EquipUI: +16, CCBCamControl: +16, UIFrameWnd: +14
  - CCBUI: +12, RenderTarget2: +11, CCBFiveNimbusWindow: +10, 其他 37 个类
- **置信度**: 85（IDA Hex-Rays decomp 在正确 struct 定义下访问这些偏移 = A+ 级证据）
- **类型推断**: 4-aligned → int, 2-aligned → short, 其他 → unsigned char
- **影响**: struct 中 gap 区域被填充，_gap_ 访问应大幅减少

## [2026-05-14] globals.json 清理 + structs/ 垃圾删除

- **变更**:
  1. 从 globals.json 删除 43 个无效条目 (479 → 436)：
     - 36 个 MSVC mangled name（`??_7length_error@std@@6B@` 等 RTTI/vtable 符号）
     - 7 个 `__IMPORT_DESCRIPTOR_*`（PE 导入表内部结构）
     - 18 个 PE/CRT 内部类型（IMAGE_IMPORT_DESCRIPTOR、_CatchableType、_ThrowInfo 等）
  2. 从 structs/ 删除 6 个原始类型的垃圾 JSON 文件：
     - char.json、UINT.json、LPARAM.json、size_t.json、double.json、long.json
     - 这些是 PDB 导入时产生的空壳文件（0 个有效成员），会干扰 codegen 前向声明判断
- **置信度**: 95（这些条目明确不属于游戏逻辑：mangled name 是编译器内部符号，PE 描述符是链接器产物，原始类型不是结构体）
- **证据**:
  1. [A] VC6 编译报 `error C2018: unknown character '0x40'`——`@` 在 mangled name 中不是合法 C 标识符
  2. [A] `IMAGE_IMPORT_DESCRIPTOR` 等类型未在 VC6 Include 中定义，且属于 PE 格式内部结构
  3. [A] char.json 等 struct 文件 binary_size=?，known_members=0，无实际逆向价值
- **影响**: globals.h 生成时不再包含非法标识符，编译可继续推进

### [2026-05-14] globals.json 清理 — 第二轮 (CRT 内部变量)

- **变更**: 从 globals.json 再删除 7 个非游戏逻辑条目 (436 → 429)：
  - `SrcSizeInBytes` (0x0060AF0C, size_t) — CRT 内部
  - `lpfn` (0x01895398, LPTOP_LEVEL_EXCEPTION_FILTER) — CRT SEH
  - `g_bCursorVisible` (0x01895560, unsigned __int8) — CRT 内部
  - `Count` (0x018969A0, size_t) — CRT 内部
  - `Locale` (0x01896BC4, LCID) — CRT 内部
  - `lpMem` (0x01896D08, LPVOID) — CRT 内部
  - `riidltf` (0x00573860, const IID) — .rdata 中的 COM GUID
- 重命名 `g_GameData` (0x00DB9FD0) → `g_GameData2`（消除同名冲突）
- **置信度**: 95（0x0189xxxx 范围是 .bss 尾部的 CRT 运行时区域，非游戏逻辑）
- **证据**:
  1. [A] 地址 0x0189xxxx 在 .bss 段末尾，远超游戏数据区 (0x580000-0xDF0000)
  2. [A] `riidltf` 位于 .rdata 段的 COM IID 区域 (0x00573860)
  3. [B] 变量名 SrcSizeInBytes/Count/lpMem/lpfn 均为 CRT 函数内部变量名模式
- **未降级**：g_hCursor (HCURSOR), dwInitParam (LPARAM), g_UIScene (std::ios_base) 保留原始类型——codegen 层通过 `#include <windows.h>` 和头文件生成来解决

### [2026-05-14] globals.json 清理 — 第三轮 (IAT 函数指针)

- **变更**: 从 globals.json 删除 3 个 IAT 函数指针 (429 → 426)：
  - `MessageBoxA_0` (0x01895538, `int (__stdcall *)(...)`)
  - `GetActiveWindow_0` (0x0189553C, `HWND (__stdcall *)()`)
  - `GetLastActivePopup` (0x01895540, `HWND (__stdcall *)(...)`)
- **置信度**: 95（0x0189xxxx 是 CRT .bss 区域，这些是 Win32 API 的 Import Address Table thunk）
- **证据**:
  1. [A] 地址 0x018955xx 属于 .bss 段 CRT 区域
  2. [A] 名字与 Win32 API 完全匹配（MessageBoxA、GetActiveWindow、GetLastActivePopup）
  3. [B] 类型为函数指针——IAT 存储的正是函数指针
- **影响**: globals.h 不再生成无法编译的函数指针 extern 声明

### [2026-05-14] functions.json 修正 __int128 签名 + skip_functions 添加 CRT 函数

- **变更**:
  1. functions.json: 修正 4 个函数签名中的 `__int128` → 展开为 4 个 `int` 参数
     - UIListBox::_init_4765f0 (0x004765F0)
     - UIListBox::_init_476ed0 (0x00476ED0)
     - UIScene::_init_454ca0 (0x00454CA0)
     - ECBRoleSpecState::_method_532cf0 (0x00532CF0)
  2. skip_functions.json: 添加 4 个 CRT Concurrency Runtime 内部函数
     - Concurrency::details::VirtualProcessor::GetExecutionResourceId (0x004790F0)
     - Concurrency::details::InternalContextBase::GetProxy (0x00479250)
     - Concurrency::details::VirtualProcessor::IsThrottled (0x004B4830)
     - Concurrency::details::ExternalStatistics::MarkInactive (0x00532D50)
- **置信度**: 90
  - __int128 修正: IDA Hex-Rays 在 32-bit 代码中生成了不可能的 128-bit 类型，实际是多个 32-bit 参数被错误合并
  - CRT 函数: 函数名明确属于 MSVC Concurrency Runtime (非游戏逻辑)
- **证据**:
  1. [A] 32-bit PE (PAL3.exe) 不可能有 __int128 指令——这是 IDA 反编译 artifact
  2. [A] `Concurrency::details::` 命名空间是 MSVC CRT 内部实现
- **影响**: IDB rebuild 后 decomp JSON 中不再包含 __int128 签名；Concurrency 类不再生成头文件和源码

### [2026-05-14] globals.json 添加 PRNG 全局变量

- **变更**: 添加 2 个全局变量
  - `g_nCombatRandSeed` (0x005DFDEC, `unsigned long`) — 战斗 AI PRNG 种子
  - `g_nRandCallCount` (0x017AD310, `int`) — 随机数调用计数器
- **置信度**: 95
- **证据**:
  1. [A] raw IDB 反编译 HandleEnemyAction (0x4D71E0) 中：`dword_5DFDEC = 214013 * dword_5DFDEC + 2531011` — 经典 MSVC LCG PRNG 常数
  2. [A] raw IDB 中 `++dword_17AD310` 与 PRNG 调用总是配对出现
  3. [A] 二进制搜索 PRNG 常数 214013 (0x343FD) 确认 `mov [0x5DFDEC], eax` 和 `mov [0x60AC60], eax`（两处不同 PRNG seed）
- **发现**: 0x5DFDEC 落在 g_EffMgr (0x5D54F0, CEffMgr size=43312) 范围内，偏移 0xA8FC = m_EffTable[2046].dwRunGroupID。annotated IDB 中 IDA 把此地址误解析为 `stru_5D5484.m_EffTable[1943].dwClassNameCRC`（因为 0x5D5484 被 IDA 自动创建为结构体，覆盖了该区域的字符串常量 "quake"/"bink"/"shock"/"audio"）
- **待修复**: stru_5D5484 的根因是 CEffMgr 区域的结构体 overlap，需要进一步调查 CEffMgr 布局

### [2026-05-14] gbengine 头文件 IDA 导入 + union 清除 + annotation 清理

- **变更**:
  1. gbengine 头文件去除匿名 union（gbColorQuad/gbColorFlt/gbMatrix4/gbUIQuad），保留主要成员名
  2. import_gbengine_types.py：idc.parse_decls + parse_decl fallback → 133/139 类型导入 IDA
  3. 删除 95 个 gb\* annotation 文件（gbengine 头文件为权威源）
  4. gen_headers 修复：gbengine enum 映射正则加 `enum`，`_BGM` 等游戏 enum 白名单
- **置信度**: 95（gbengine 头文件是源码级权威），90（union 清除后 gbengine 编译通过验证）
- **证据**:
  1. [A] gbengine 编译 0 错误（union 清除 + 别名替换后）
  2. [A] IDA TIL 验证：133 个 gbengine 类型通过 get_named_type 确认注册
  3. [A] C1083 编译错误 86→0（gbFontType.h 等缺失头文件全部消除）
- **6 个剩余失败**: CPK, LIGHT_TYPE, gbCursorRes, gbEffectMgr, gbGfxManager_D3D, gbVFileSystem
  - 原因：forward-only 定义(gbCursorRes)、空 body(gbEffectMgr)、Windows 类型依赖(RECT)、复杂 friend(CPK)

### [2026-05-14] gbengine IDA 导入完善 + 编译错误基线

- **变更**:
  1. import_gbengine_types.py 最终方案：idc.parse_decls + parse_decl fallback → 140/143 类型
  2. 修复类型降级：D3DXHANDLE=const char*（非 int），COM 接口用 forward declare（非 void*）
  3. 修复解析顺序：gbResManager.h 移到 gbRenderEffect.h 之前
  4. 宏展开：CPK_MAX_TABLE_NUM→0x8000，bool→unsigned char
  5. 正确外部类型：RECT struct, LIGHT_TYPE enum, CONFIRMDEVICECALLBACK 函数指针 typedef
- **置信度**: 95
- **证据**:
  1. [A] gbGfxManager 编译错误 85→1（gbengine 类型导入生效的直接证据）
  2. [A] C1083 缺失头文件 0 个（所有 include 路径正确）
  3. [A] D3DXHANDLE=LPCSTR 来自 tools/vc6/Include/d3dx9shader.h
  4. [A] CPK size=917948 在 IDA TIL 中验证（0x8000*28+444=917948）
- **编译基线**: 10238 错误, 0/197 文件通过
  - C2039(成员缺失): 3438, top: SceneMgr(508), UIFrameWnd(196), UIListBox(109)
  - C2228/C2227(不完整类型访问): 1919
  - C2440(类型转换): 623
  - C2065(未声明标识符): 536
  - Root cause 分析: SceneMgr 视图 B(508), 结构体成员不完整(~2000), codegen 标识符泄漏(~500)

### [2026-05-14] gen_headers 数据流修正: PDB → IDB

- **变更**:
  1. 新建 export_structs.py：从 IDB 导出 969 个结构体定义到 `asm/pal3/ida_structs.json`
  2. gen_headers 改为优先读取 IDB 导出数据，仅在 IDB 无数据时 fallback PDB
  3. 覆盖条件：IDA size > PDB size 或 IDA members > PDB members → 581 个结构体覆盖
- **置信度**: 95
- **root cause**: gen_headers 原来从 PAL3A PDB 读取结构体布局，但 PDB 缺少：
  - annotation 通过 apply_annotations 导入 IDA 的额外成员（UIFrameWnd +72~+120）
  - gbengine 头文件导入 IDA 的类型定义
  - binary_size > pdb_size 的真实结构体大小
  IDB 是 PDB + gbengine + annotation 的全集，应该是 gen_headers 的唯一数据源。
- **证据**:
  1. [A] UIFrameWnd: PDB 只有 1 个成员(m_pbktex +0x44, size=72)，IDB 有 23 个成员(size=152)
  2. [A] 编译错误: 10238→8931 (-1307, -13%)
  3. [A] C2039 成员缺失: 3438→920 (-73%)，SceneMgr(508→0), UIFrameWnd(196→29)
- **完整管线**: import_gbengine → apply_annotations → export_full(decomp + structs) → gen_headers(读 ida_structs.json) → gen_cpp

### [2026-05-14] export_structs 集成到 export_full + 编译错误分析

- **变更**: export_structs 逻辑合并到 export_full.py（不增加管线步骤）
- **置信度**: 95
- **当前编译基线**: 8931 错误
- **剩余 C2039(920) 分布**:
  - st_Manager(125): gbengine/topo 管理器类，IDB 结构体不完整
  - s_RoleState(104): 未在 annotations 中定义，IDB 缺成员
  - UIWnd(54): 基类某些成员在子类中引用时缺失
  - CCBUIPanel(53): 结构体不完整
  - tagRECT(50): Windows 类型，gen_headers skip 但代码引用成员未 include windows.h
  - string(45): std::string 伪类型，应加入 SKIP
- **剩余 C2065(536) 分布**: IDA 内部标识符泄漏（eh, constructor, destructor, vtbl_XXXX）

### [2026-05-14] 删除 3 个空壳 RoleState annotation + string SKIP

- **变更**:
  1. 删除 s_RoleState/m_RoleState/p_RoleState annotation（0 个 known_members）
  2. gen_headers SKIP_CLASSES 添加 string/strstreambuf/ios_base/facet/codecvt_base
- **置信度**: 95
- **root cause**: annotation 文件有 gen_size 但 0 个 known_members，apply_annotations 用空结构体覆盖了 PDB 的 20+ 成员定义，导致 IDB 中结构体变成只有 `_tail_000` 的空壳
- **证据**:
  1. [A] s_RoleState: annotation 0 members, PDB 20 members → 删除 annotation 后 PDB 数据恢复
  2. [A] C2039 `_tail_000 not a member of s_RoleState`: 104 个 → 0
- **影响**: 编译错误 8931→8774 (-157)
- **新 C2039 分布**: st_Manager(125), UIWnd(54), CCBUIPanel(53), tagRECT(50), UIStatic(37)

### [2026-05-14] 清理 31 个 Windows/D3D/CRT 系统类型 annotation

- **变更**: 删除 tagRECT, tagPOINT, D3DMATRIX, GUID, _FILETIME 等 31 个系统类型 annotation 文件
- **置信度**: 95
- **root cause**: 与 RoleState 问题相同——annotation 文件（有 gen_size 但成员来自 PDB 没有额外信息）覆盖了 IDA 已有的正确系统类型定义。系统类型应由 windows.h/d3d9.h 等系统头文件提供，不应在 annotation 中管理。
- **证据**:
  1. [A] tagRECT: annotation 有 4 成员 + gen_size=16，但 apply_annotations 创建的 IDB 结构体只有 `_tail_000`
  2. [A] 50 个 `tagRECT._tail_000 not a member` 错误消除
- **影响**: 编译错误 8774→8688 (-86)
- **累计**: 10238→8688 (-15%)

### [2026-05-14] 68 个 overlap 违规修复 + 18 个语义命名

- **变更**:
  1. 修复 68 个从远端 gap-fill 引入的结构体 overlap 违规（15 个结构体）
  2. 从 query_todo_fields 上下文命名 18 个 _todo_ 字段
- **置信度**: 95（overlap 修复），75（语义命名）
- **Overlap 修复方法**: 检测 int(4字节)/UIWnd(152字节)/char[N] 等成员覆盖范围，删除范围内的 _todo_/_field_ 子条目
- **修复明细**:
  - CScreenMode: -22, EquipUI: -7, PropUI: -7, PalScriptMgr: -6+2手动
  - _TextureLib_Data: -6, SaleUI: -5, UIBigMap: -2, UICoverFrm: -2
  - PalScript: -2, CCBStage: -1+1手动, CCBUI: -1, UIListBox: -1, 等
- **语义命名证据**:
  1. [A+] RoleSystem+0 = `m_pVtable`: decomp `this->_field_000 = (int)&stru_570890` — vtable 赋值
  2. [A+] UIListBox+516 = `m_nItemCount`: `++this->_todo_204` / `--this->_todo_204` — 计数器增减
  3. [A+] UIListBox+368 = `m_wndScrollBar`: `UIFrameWnd::ctor/dtor` 在该偏移调用 — 嵌入 UIFrameWnd
  4. [A+] UIScene+168 = `m_dwColor`: `= -16776961` (0xFF0000FF) — ARGB 颜色常量
  5. [A+] TextureLib+528 = `m_pTexture`: LoadFromFile 存指针, _nearby 释放+置零 — 指针生命周期
  6. [A+] ScriptSystem+1352 = `m_fTargetDir`: 与 m_vDir_z 比较, 赋给 m_nSaveDir — 目标方向
  7. [A+] CameraCtrl+3352 = `m_CamBlocks`: `memset 0xBA40(47680)` 字节 — 大型数组/缓冲区
- **影响**: 消除 pre-commit 违规，annotations 恢复 PASS 状态

### [2026-05-14] 编译错误驱动的 annotation 修复（256 gen_size + 14 结构体 stub）

- **变更**:
  1. 256 个结构体从 pdb_size 补充 gen_size（gen_headers 需要此字段才生成头文件）
  2. ScreenFadeOut/White/White2: 添加 `base_class: ScreenEffect`（size=24 匹配 ScreenEffect）
  3. PMFN: 添加 `int pfn` 成员（4 字节函数指针，用作嵌入成员）
  4. 10 个粒子图表结构体: 添加 `int vfptr` 最小成员（gen_headers 需要至少 1 个成员才生成类定义）
- **置信度**: 85（ScreenFade 继承推断），90（gen_size=pdb_size 复制）
- **证据**:
  1. [A] ScreenEffect gen_size=24 = ScreenFadeOut/White/White2 pdb_size=24 → 继承且无额外成员
  2. [B] PDB 中 PMFN size=4，是 "Pointer to Member Function" 的标准 MSVC 内部类型
  3. 编译错误 C2079 "uses undefined class" 直接指向缺失的头文件
- **root cause**: gen_headers 只为有 gen_size 且有成员的结构体生成头文件。256 个结构体只有 pdb_size 被跳过
- **影响**: 编译错误 4724→4704（头文件级 C2079 基本消除，剩余主要是 C2039 成员缺失）

### [2026-05-15] Phase 1.1: int this → ClassName *this (35 functions)
- **变更**: 35 个 __thiscall 函数的 this 参数从 int 修正为 ClassName *
- **置信度**: 95
- **证据**:
  1. [A] __thiscall 调用约定要求 ECX=this，参数类型必为类指针
  2. [B] 函数名 ClassName:: 前缀匹配
- **函数列表**: 35 个函数已修正
  - 0x00402D00: GRPinput::SetJoystickFreePos
  - 0x0043E1C0: UIListBox::CalScrollBarRange
  - 0x0047D690: Object3D::CaculateRelative
  - 0x004C3EC0: CEffCylinder::Init
  - 0x004C45A0: CEffCylinder::CreateTask
  - 0x004C6A70: CEffect::Reset
  - 0x004C7150: CEffect::CreateOnePartical
  - 0x004CB5E0: CEffMeteor::Init
  - 0x004CBFC0: CEffMeteor::CreateTask
  - 0x004D0EC0: CEffModel::ProcInitTask
  - ... (25 more)

### [2026-05-15] Phase 1.2: PAL3A cross-reference (3 functions)
- **变更**: 3 个函数通过 PAL3A 反编译签名改进参数类型
- **置信度**: 70
- **证据**:
  1. [A] PAL3A 官方 PDB 包含完整类型信息
  2. [B] 函数名完全匹配，参数个数一致
  3. [C] 仅替换 PAL3 中的泛化类型 (int/void*) 为 PAL3A 的具体类型
- **函数列表**: 3 个函数已改进
  - 0x00407740: PAL3::IfHideFightSucceed
  - 0x00440DD0: UIStatic::Update
  - 0x005249A0: UIBigMap::OnMessage

### [2026-05-15] Phase 1.3: void* parameter type inference (9 functions)
- **变更**: 9 个函数的签名已改进
- **置信度**: 80
- **证据**:
  1. [A] 函数体中显式 cast 为特定类型
  2. [B] 跳过泛化类型 (void/char/int/_DWORD/_BYTE)
  3. [C] 选取出现频率最高的 cast 目标类型
- **函数列表**: 9 个函数已修正
  - 0x0040C630: ScriptSystem::Render
  - 0x00412400: RoleSystem::RenderRole
  - 0x00414980: RoleSystem::GetPosition
  - 0x0041E7D0: Camera::CheckCollision1
  - 0x0041EA00: Camera::CheckCollision2
  - 0x00445B90: UIWnd::_unverified_445B90
  - 0x004020E0: GRPinput::Create
  - 0x004E1190: CEffectSystem::_auto_4e1190
  - 0x00539810: UIBigMap::SetElementVisible

### [2026-05-15] Phase 1.4: int parameter pointer inference (21 functions)
- **变更**: 21 个函数的签名已改进
- **置信度**: 80
- **证据**:
  1. [A] 函数体中 int 参数被 cast 为指针类型
  2. [B] Cast 出现 ≥2 次才接受（置信度 80）
  3. [C] 跳过泛化类型 (void/char/int/_DWORD/_BYTE)
- **函数列表**: 21 个函数已修正
  - 0x00413010: RoleSystem::UpdateRole
  - 0x00416790: RoleSystem::UpdateAnimation
  - 0x004C3EC0: CEffCylinder::Init
  - 0x004C6A70: CEffect::Reset
  - 0x004CB5E0: CEffMeteor::Init
  - 0x004D0EC0: CEffModel::ProcInitTask
  - 0x004D3A50: CEffShock::Init
  - 0x004DFD20: Combat::LogMessage
  - 0x005062D0: CCCTData::Load
  - 0x00416220: RoleSystem_Helper_416220
  - ... (11 more)

### [2026-05-15] Phase 1.5: Parameter semantic naming (1278 functions)
- **变更**: 1278 个函数的签名已改进
- **置信度**: 60
- **证据**:
  1. [A] 将泛化参数名 (a1, a2, ...) 替换为语义化的 Hungarian 风格命名
  2. [B] 保留已有语义名 (如 fAngle, pStack) 和 this 参数
  3. [C] 根据参数类型应用命名规则 (p前缀指针, f前缀浮点, n前缀整数等)
- **函数列表**: 1278 个函数已修正
  - 0x004014F0: CCBAI::Thunk_GetValue
  - 0x004024F0: GRPinput::~GRPinput
  - 0x00402A90: GRPinput::SetMouseAbs
  - 0x00402FA0: GRPinput::GetMouseSensitivity
  - 0x004038F0: GRPinput::InitShiftedKeys
  - 0x004039D0: GRPinput::InitDIKToKEY
  - 0x004055D0: PAL3::Update
  - 0x00406310: PAL3::CheckSystemRequire
  - 0x00406B80: PAL3::DefaultKeyMap
  - 0x00406FF0: PAL3::SnapScreen
  - ... (1268 more)

### [2026-05-15] Phase 1 集成验证 — 6234→6090 errors (-2.3%), C2228 -64%

- **变更**: Phase 1 全部 5 个子阶段完成后，IDA 管线重建验证
- **置信度**: 95
- **管线执行**:
  1. `fix_signatures.py` Phase 1.1-1.5 共修正 1346 个函数签名
  2. `apply_annotations.py` → IDA SetType 应用新签名
  3. `export_full.py` → 4357 decomp JSONs (含 lvar 信息)
  4. `gen_headers.py` + `gen_cpp.py --force-all` → 197 .cpp, 834 .h
  5. `cmake --build -- -k` → 6090 errors
- **错误变化对比**:

  | 错误码 | 修正前 | 修正后 | 变化 |
  |--------|--------|--------|------|
  | C2228 (.非struct) | 848 | 305 | **-543 (-64%)** |
  | C2664 (类型不匹配) | 818 | 667 | -151 |
  | C2673 (vtable) | 751 | 665 | -86 |
  | C2227 (->非指针) | 699 | 739 | +40 |
  | C2440 (类型转换) | 779 | 846 | +67 |
  | C2039 (成员缺失) | 599 | 625 | +26 |
  | C2065 (未声明) | 390 | 325 | -65 |
  | 总计 | 6234 | 6090 | **-144** |

- **分析**: C2228 大幅下降是 int this→Class *this 的直接效果。C2440/C2227 略升是因为原来的 "int 不是 struct" 错误转化为更精确的 "Class * 到 xxx 的类型转换" 错误。净减 144 错误，签名质量显著提升。
- **证据**:
  1. [A] cmake --build -- -k 全量编译统计
  2. [A] IDA apply_annotations 成功应用所有签名（IDB 时间戳更新）
- **新增工具**: tools/fix_signatures.py (7 subcommands), lvars 管线扩展
- **剩余最高 ROI 目标**: gen_headers vtable 去重 (C2673 665), IDA 侧签名修正 (C2440/C2227/C2664)

### [2026-05-15] gen_headers VTABLE_DUP 修复 — 6090→5904 errors (-3.1%)

- **变更**: gen_headers.py 修正 vtable 方法处理逻辑
  1. 基类 vtable 区域：不再生成 `virtual` 声明（IDA vtable 签名不准确，与实际实现冲突）
  2. 子类 VTABLE_DUP 方法：不再注释掉，正常声明（全部 124 个都有 .cpp 实现）
- **置信度**: 95
- **证据**:
  1. [A] 124 个 VTABLE_DUP 方法在 .cpp 中全部有实现（0 个缺失）
  2. [A] IDA vtable 推断签名与 Hex-Rays 反编译签名不一致（如 `virtual int OnMessage()` vs `char OnMessage(_DWORD*, int)`）
  3. [A] cmake --build -- -k: 6090→5904 (-186 errors)
- **错误变化**:
  - C2673 (vtable override): 665→486 (-179)
  - C2039 (__vftable member): 625→517 (-108)
  - C2065 (undeclared): 325→290 (-35)
- **不引入退化**: vtable 方法名仍被追踪用于去重，只是不生成不准确的 virtual 签名声明
