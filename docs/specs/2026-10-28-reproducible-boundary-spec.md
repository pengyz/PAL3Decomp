# 可再生产件边界 spec（判定流程 v2 · 标注 schema · 完备性验证环）

> 2026-10-28 · 综合 4 份调研 + 4 份对抗复核定稿。输入：research_dtor_identity / research_thunk_mechanism /
> research_crt_boundary / research_dx_static_boundary（均 20261028）+ 同名 review_* 四份。
> 复核状态：四份均 ACCEPT-WITH-FIXES，本 spec 已吸收全部 D1-D13 级缺陷修正。

## 0. 边界定义（用户裁定，原文）

> **「构建系统可再生产 ⇒ 无需逆向」**——静态链接与否只是表象，真判据 = 是否持有**可重现的构建输入**
> （同版库 / 同版头 / 同编译器+flags）。可再生产者链接/重编即再产；不可再生产者才需逆向重建。

字节等同实证（match 三限定：截断到原 size / 等长 / 重定位 4B don't-care）是唯一验收；
引用等同结论**必须带 hidden diff 量化**（实测口径：CRT 7 案 23.4% 被三限定掩盖、DX 3 案 6.6%、越界差异均 0）。

## 1. 边界枚举（9 类）

| 类 | 定义 | 供给源 | 逆向？ | 实证锚点 |
|---|---|---|---|---|
| `game` (G) | 游戏自有逻辑 | 无 ⇒ 源码重建 | ✓ | — |
| `engine_static` (E) | gbEngine 静态并入件 | gbengine 源/重建线 | ✓（有源线）| F16 争议后仅余待清点项 |
| `lib_crt` | MSVC6 静态 CRT | libcmt/工具链 | ✗ | __ftol 39B 零 hidden diff |
| `lib_stl` | MSVC6 静态 STL | libcpmt | ✗ | logic_error 族 76.6% 实证 |
| `lib_thirdparty` | **D3DX9 等第三方静态库** | d3dx9.lib（⚠版本敏感）| ✗（条件性）| c_D3DXVec3Normalize 157B 逐字节 |
| `compiler_synthesized` | deleting dtor/adjthunk/init 桩/SEH/ctor 跳板 | MSVC6 自动再生 | ✗ | 45/45 SingletonThunk 字节形 |
| `import_thunk` | IAT 跳板（7 DLL：ADVAPI32/DINPUT8/KERNEL32/USER32/WINMM/BINKW32/GBENGINE） | 导入表 | ✗ | DirectInput8Create/RtlUnwind |
| `linker_artifact` | 布局桩/COMDAT 折叠/尾跳别名 | 链接器 | ✗（逐个裁）| T7 217 筐拆分 |
| `unknown` | 未分类 | — | 待裁 | 完备判据=0 存量 |

**条件性可再生产（重要修正，dx 复核 D8）**：`lib_thirdparty` 逐单元状态化——73 槽 PSGP 面
67 可复现 + 2 psgpmesh + **4 个实现体残差**（#39/#67/#71/#72，#39 有 268B masked diff=内核版本分叉实证）。
在手 d3dx9.lib（obj 2002-12-11，71 槽）≠ exe 精确构建输入（73 槽+new/delete 检查）⇒ 精确件待补给
（MS FamilyId 9216652F-…），未补给前该 4 单元降级 `unknown`/定点重建。

## 2. 判定流程 v2（六步，吸收全部 spec 缺陷修正）

1. **字节形分诊**（禁名字结论——名字双向错位实证：`_scalar_dtor_BE80`=纯析构、`j_D3DXVec3TransformCoord`=game
   random-lerp、`Destroy__ovl_03`=真虚方法、GetVertexBuf=PDB 错名）：`test flags,1+delete`=deleting dtor；
   `mov vptr+jmp base`=纯析构；`sub this+forward`=adjthunk；`FF 25 [IAT]`=import_thunk；
   `FF 25 [.data 表]`=PSGP 分发；`B9 imm32 E9`=ctor/dtor 跳板；SEH 全形=析构包装（v1 STEP1 漏项，已补）。
2. **槽→目标追踪**（v1 缺失，已补）：vtable/分发表槽位须追到默认目标体并字节配对库符号
   （槽号不固定——槽6 实例；73 槽全量配对法）。
3. **兄弟清点**（v1 缺失，已补）：`__ovl_NN`/`_NN` 地址后缀占位名须清点全部兄弟
   （实测 __ovl 10 兄弟三制式混用），防孤证。
4. **PDB 名降级分支**（v1 缺失，已补）：`source=pdb` 的名字证据等级=unverified，不得作结论依据。
5. **供给源归类**：按 §1 九类；「三文件各恰 1 份」不能裁别「各编 vs 各链同库」（crt 复核 D1 教训）——须字节配对 .lib 成员。
6. **名实一致性校验**：??_G/??_E 前缀、语义名、地址后缀名三制式分别对待；结论落地时**改名走语义不走字面**
   （T11 教训：sg_emission_control 5 处调用是 random-lerp 语义，禁照字面改 D3DX 真名）。

## 3. 处置矩阵与红线

| 组 | 处置 | 红线 |
|---|---|---|
| G/E | 源码重建 + decl 必有（含 Destroy__ovl_03：真虚方法，修归属+声明可见性，禁再当合成物）| 归属须 vtable 槽+共享类证据（「挂 UIWnd」已被字节证伪）|
| lib_* | 链接期供给，**禁写源码**（写=伪定义体，如 free_functions.h:393 的 random-lerp 伪体）| 版本偏斜须逐单元状态化 |
| compiler_synthesized | 源写 `~X()+delete`/static 对象即再生，**勿手写** | thunk 的「(d) 手工合成保底」已废除（LNK2005 风险）|
| import_thunk | 导入表供给 | — |
| linker_artifact | 逐个裁（(b) 优先，(d) 须批0 级评估）| — |

**C2065 多机制教训（dtor 复核）**：「无定义/声明」症状 ≠ 二进制缺失——可能同时是
归属错置（18 structs 抢同一地址）+ NullCallback 机制（`__thiscall` 自由函数 codegen 跳过声明）
+ 单类归属假设错。修 annotation 须按机制分派，不许一招鲜。

## 4. 标注 schema（三轴解耦 + 注册表）

- **三轴**：`boundary`（§1 九类）/ `supply`（供给源+版本一致性状态：`exact`/`skewed`/`missing`）/
  `skip`（是否导出）——现行 `reason: crt_runtime` 923 条混装三义须拆分。
- **skip_reason 枚举**（替换 crt_runtime）：`lib_relink_ok` / `compiler_regenerated` / `linker_generated` /
  `dual_def_workaround`（批0 教训：与 decl 收编不同源，动它须防 C2556/2373 ×144）/ `dup_decl_elsewhere` /
  `awaiting_signature`。**枚举须与 1910 总账平账**（crt 复核：现表 1778≠1910，缺 thunk=135 桶）。
- **注册表**：`thunk_registry.json`（12 族+第 9 形 `B9 imm32 FF 25 [IAT]` 变体）+ `system_lib_statics.json`
  （符号/地址区间/供给源+版本/flags/验证状态/命名更正/disposition + **confidence 轴**（dx 复核 D11））。
  与 skip_functions 的关系：**单一读点聚合 + 双写过渡 + fail-loud 冲突**（thunk 复核补丁；
  迁移须对账 export_full/collect/data/apply/check/annotation_view 六消费点）。
- 作用域约束：分母以 IDB 实测 **5609** 为准（5611 不可复现，crt 复核）；与 214 编译单元的关系须在册。

## 5. 完备性验证环

1. **未分类=0**：5609 函数全入册（九类无 unknown 存量）。
2. **双闭环**：G/E 必有 decl；lib/compiler 必无 decl（抓伪定义体）。
3. **每供给源 ≥1 例字节实证 + hidden diff 量化随行**（三限定引用纪律）。
4. **两门禁**：LNK2005 对账（伪定义体/合成物手写必撞）+ link_probe expected 集合（(c) 类 unresolved=回归）。
5. **可达性红旗扫描**（WinMain 冤案闸）：skip 条目被游戏 decomp 直调 ⇒ 红旗复裁（crt 普查法固化）。
6. **跨报勘误流程**（dx 复核 D13 新增）：复核裁决推翻报告结论时，**必须回写原报告勘误节**（本次 2 处已回写）。
7. **防回归**：形状分类器自动入册（8+1 形签名）+ 新符号六步入册流程。

## 6. 跨报勘误表（已回写原报告）

| 被勘误 | 勘误内容 | 裁决方 |
|---|---|---|
| thunk :83/:143 | 槽[7]/[35] 语义标签双证伪 ⇒ 真 MatrixMultiply=槽#3@0x543098、真 Vec3TransformCoord=槽#10@0x545152 | dx 复核 |
| crt :113/:115 | 13B 桩非「scalar deleting dtor thunk」⇒「PSGP 惰性初始化桩」 | dx 复核 |
| crt §3 | sub_542xxx=gbEngine **REFUTED** ⇒ D3DX9 PSGP（d3dxmath.obj 逐位） | crt 复核 |
| thunk T6 | 现状「已 skip」**反了** ⇒ 已被 codegen 渲成手写成员方法（反模式活案例） | thunk 复核 |
| dtor #13 | ??_GAStarPathFinder=0x401030 非 0x401040；禁名字举证 | dtor 复核 |
| dx §3.2 | 头内联「逐字节同」过强 ⇒ 最大连续相等 14B | dx 复核 |
| 普查文 | j_D3DX* 三条错名 + __m64 簇归 D3DX PSGP | dx 调研 |

## 7. 落地清单（优先级序）

1. **Destroy__ovl_03 修复**（A 组唯一真游戏方法）：归属定谳（中间类 vs COMDAT 折叠两说待分）+
   声明可见性（NullCallback/`__thiscall` 无 `::` 机制，pre-commit WARN 同源）⇒ 可回收 10 处 overlay 注释。
2. **j_D3DX 三名正名**：0x4B8200=random-lerp 新名（**语义命名**，5 处调用点同步）；0x542533/0x544771 声明
   改走 `<d3dx9math.h>`（D3DXVec3Normalize/D3DXQuaternionSlerp）⇒ 回收 sg_emission_control 注释债。
3. **4 个 crt_sub 冤户 unskip**（0x541490/005414A0/00541860/00541C40）——批0 前置检查（先查 decl 收编）。
4. **skip_functions reason 拆分**（923 条 crt_runtime → 枚举化）+ 6 消费点对账 + 平账 1910。
5. **T6 adjustthunk 反模式清理**：codegen 合成物渲染成手写成员方法 ⇒ 逐个回收 + 编译器再生验证。
6. **T5 LNK2001 排雷**：6 个 declaration_only 无定义体被调用（PalScriptMgr.cpp:3135/3142 补入调用面）。
7. **注册表落地**：thunk_registry.json + system_lib_statics.json（含 confidence 轴 + 73 槽全量配对记录）。
8. **D3DX 精确件补给**（网络渠道另寻）→ 4 残差单元终裁；未补给前挂 `supply=skewed`。
9. overlay 47 条注释债按上述修复逐条回收（纯态验收）。

## 8. 遗留未知（八份文档汇总）

73 槽仅 2 项槽内名 / 0x54474D 已闭合（init_D3DXQuaternionSlerp）/ T7 三分判据 / 39 件字节承担者 /
Destroy__ovl_03 确切归属类 / ??_GRole@0x41BE30 thunk 形 / nullsub 90 条 / 44B 桩源级触发形态 /
lib 版本三值互异全貌（cl 8168/ftol 7299/string 8047）/ 782 符号口径 / gbengine 内 libpng/zlib 边缘 /
`__ovl_00/01/02/04` 兄弟中未获证者 / match/L1 未实跑项。
