# 对抗性复核：CRT/游戏边界调研（research_crt_boundary_20261028.md）

> 复核立场：不信任报告，只信实测。复核人独立重跑实验、IDA 独立取证、库内字节比对。
> 复核产物仅本文件；未动任何产品/标注/管线/报告文件。IDA 证据源：`original/PAL3.exe.i64`（session 278944bc）。
> 三限定随数字走：凡引「字节等同/L1」均指①截断到原 size ②截后等长 ③重定位 4B don't-care 下的等同。

---

## 1. 复核总结

**ACCEPT-WITH-FIXES** —— 方法学与绝大多数抽验实测成立（字节实验可复现、7/7 案零越界差异、指名裁决/名字误挂/混桶游戏码全部复验通过），但 **「E 引擎数学簇」归属被 d3dx9.lib 库内逐位实证推翻**（REFUTED，且系三方矛盾的错误一方），迁移清单、reason 台账与完备分母须按 §4 补丁重做后**方可执行迁移**。

---

## 2. 逐项 verdict 表

| # | 复验项 | verdict | 一句话依据 |
|---|---|---|---|
| 1 | 字节等同实验方法学 | **PARTIAL** | ①②③ 实验可复现+比对实现正确+零越界差异（含补验报告缺失的第 6 案）全 CONFIRMED；④ 库版本口径被低估（@comp.id 三值互异、成员时间戳 2000/2004 异质、d3dx9 漂移实锤） |
| 2 | unknown_libname 三群 | **PARTIAL** | 群 A（44B guard 桩）/B（STL 异常族）/C（真 CRT，0xE06D7363 EH magic）抽样全立；但 528 是 42B 双 guard **变体**非「字节全同 44B」，「guard 只有一个字节」不成立 |
| 3 | sub_542xxx = gbEngine 数学库 | **REFUTED** | F16 特征序列就在 `tools/vc6/Lib/d3dx9.lib!d3dxmath.obj`（符号= `c_D3DXFloat32To16Array` 全家）；sub_542169 与该 .obj 逐位全同（143/143，0 重定位）——簇是 D3DX9 PSGP 静态库代码，thunk 报告 T3/T4 为对、本报告为错 |
| 4 | 指名裁决抽验 ≥4 | **CONFIRMED** | 抽 7：$E68=G、_DllMain@12_1=G、start=L1、compiler_init_005090A0=C、crt_sub_005414A0/00541860/00541C40=G 全部 xref+字节面立；仅 crt_sub_00541490 字节面未直接抽 |
| 5 | 新发现审计 | **CONFIRMED** | 名字误挂 3/3 复验（CheckCurRV=44B 桩、GetLinkerIndex=15B 浮点桩、PreLoadEffGroup=5B 跳板）；混桶游戏码 4/4 复验（sub_401070=A* 552B、sub_408010=路径步进 214B、$E68、sub_4014B0 间接）；「须逐条重裁」（42+175=217）工作量口径成立 |
| 6 | schema/迁移清单攻击 | **PARTIAL** | 三轴解耦方向对，但 boundary 枚举缺第三方静态库类（案 3 后暴露）、兼容矩阵禁 lib×dual_def_workaround 组合、§1.2 reason 表不平账（缺 thunk 135 整桶）、923 拆桶明细无 Σ 校验 |
| 7 | 完备性 spec 攻击 | **PARTIAL** | 分母 5611 不可复现（IDA 独立计数=5609，与 survey 一致；「+2」无出处）、与 census 214 单元关系未述、间接调用盲区未进「完备」定义、形状表缺 42B 变体 |
| 8 | 三方互洽 | **PARTIAL** | PSGP 表/初始化器/sentinel、名实错位、_nearby_452570、crt_runtime 923 计数四组共享事实互洽并经实测双确认；但 E 簇归属与 thunk 报告 T3/T4 **直接矛盾**（复核裁定 thunk 报告胜） |

---

## 3. 缺陷清单（按 矛盾 > 实验方法学漏洞 > 证据不足 > spec 缺口 排序）

### 矛盾

**D1（重大·REFUTED）「E 引擎数学簇」归属错误，与 thunk 报告矛盾，迁移清单被污染**
- 报告 §3.2 裁决：F16 特征序列 `C1EE10 81E2FFFFFF7F 81E600800000 81FAFFEFFF47` 在 PAL3.exe/PAL3A.exe/gbengine.dll 各恰 1 份、Mss32.dll 0 份 ⇒ 「gbEngine 引擎数学库（引擎 DLL 与 exe 各编一份）」。
- **复核实测**：该序列在 `tools/vc6/Lib/d3dx9.lib` 的 `obj\i386\d3dxmath.obj` 内**恰 1 份**（d3dx9dt.lib 亦有）。该成员符号表即 D3DX 数学 API 全家：`?c_D3DXFloat32To16Array`（=sub_542169 F32→F16 打包）、`?c_D3DXFloat16To32Array`（=sub_542205）、`?c_D3DXVec2/3/4Hermite`+`CatmullRom`（=报告所称 5 个「4 控制点三次插值」）、`?c_D3DXVec2/3/4Lerp`（=3 个 lerp）、`?init_D3DX*`（=A 形 13B `push 1; call init; jmp [slot]` 懒初始化跳板）、`?g_D3DXFastTable`（=分发表）。
- **字节实证**：PAL3.exe `sub_542169`（0x542169，143B）与 d3dxmath.obj 内对应 COMDAT .text 段**逐位全同**（该段 0 重定位 ⇒ hidden diff = 0，lib_relink 即重现，无需任何源码重建）。
- **裁别问题的回答**（任务预判的两解释）：「各恰 1 份」对「引擎各编一份」与「各链同一静态库」两个解释**同等预测**，报告证据不足以裁别；决定性实验（查库内序列）落在「d3dx9.lib 静态链接」一侧。thunk 报告 T3/T4 另有库证（d3dx9.lib 782 个 PSGP 符号、`__imp__D3DX*`=0、init 读 `"DisableD3DXPSGP"` 注册表）。报告内部亦自相矛盾：§3.3 承认分发表项是 `D3DXVec3TransformCoord`，却把提供其实现的簇判为「引擎数学库」。
- **后果**：§1.1 E 类判定、§3.2「裁决 E：需引擎源码/同版静态库编译再现」、§4.3 迁移（sub_542xxx→E、`Float_AlmostEqual`「E，unskip+建 decl」）全部须改判 **lib_relink（d3dx9.lib，库已在仓）**。按用户判据「构建系统可再生产 ⇒ 无需逆向」，该簇（含 `__m64/__m128::_static_*` ×86 MMX/SSE 实现）无需逆向重建。若按报告执行：会把 ~200 个库供给函数错误推向源码重建/decl 路径，且 `Float_AlmostEqual` unskip+建 decl 与库供给冲突（重复定义/字节漂移风险）。
- 部分可救：E 类定义含「或同版静态 lib」+supply=lib_relink，方向兼容库供给；错在供给者命名（gbEngine→D3DX9）、缺口叙事（库已在仓无缺口）与迁移动作。

**D2（矛盾·三方事实层）同一簇在 thunk 报告判 (c) d3dx9.lib、本报告判 E 引擎源**
- 同地址段 0x542169–0x546B0E（thunk T4 明列「generic 42–209B」含 sub_5422B7/542539/542563/54263B，与本报告「E 簇」名单交叠）。复核裁定：thunk 报告对。其余共享事实（PSGP 表 0x6090A8、初始化器 0x546F41、模板 0x6091D0、sentinel 0xFFFF@0x6092F8、名实错位、_nearby_452570、crt_runtime 923 筐）三方互洽 ✓（实测双确认，见 §2-8）。

### 实验方法学漏洞

**D3 hidden diff 占比未量化（任务要求的核心量）；「6/6」的第 6 案库侧机器比对缺失**
- 复核补做并量化（7 案，比对字节总数 505）：

| 函数 | size | 差异位点 | hidden diff | 重定位 don't-care 覆盖 | 越界差异 |
|---|---|---|---|---|---|
| __ftol | 39 | 0 | **0%** | 0/39 | 无 |
| _sprintf | 82 | 4 | 4.9% | 8/82 | 无 |
| ??3@YAXPAX@Z | 11 | 3 | 27.3% | 4/11 | 无 |
| ?_Xlen | 90 | 30 | 33.3% | 32/90 | 无 |
| ?_Xran | 90 | 33 | 36.7% | ≥32/90 | 无 |
| logic_error_ctor0 | 100 | 25 | 25.0% | 36/100 | 无 |
| logic_error_ctor1 | 93 | 23 | 24.7% | 32/93 | 无 |

- **合计：118/505 = 23.4% 字节被三限定掩盖**（don't-care 覆盖 28.5%）。旗舰结论 __ftol 39/39 是真·零 hidden diff（该函数 0 重定位）——可信强度最高；string.obj 家族约 1/4~1/3 字节依赖「重定位 don't-care」语义。「重链即重现」的准确表述：**非重定位字节由同一 .obj 结构性保证逐位相等，整体等同强度 = 76.6% 字节实证 + 23.4% 依赖三限定第 3 条**。报告只给差异计数不给占比，引用「6/6 字节等同」时强度被高估。
- 「6/6」口径瑕疵：§2.1 列 7 个函数体（ctor0/1 算一 bullet），`final_cmp.py` 的 REF 只有 5 条——`std_logic_error_ctor0/1` 的**库侧**重定位裁剪机器比对在报告可复现实验中缺失（t.exe 侧 cmp.py 无重定位分析）。复核补做：libcpmt:string.obj 侧 ctor0 diffs=25/100、ctor1=23/93，outside_reloc=NONE ⇒ 补验后成立（应表述为「5 案机器证 + 2 案手工断言」→ 复核补成 7/7）。
- 附：报告「同型 forwarding ctor」（0x541F2F/0x542017）仅形状推断——复核字节补验成立：与 libcpmt `??0length_error/??0out_of_range@std@@QAE@ABV01@@Z` 各 24B 逐位一致（22/24 同 + 2 差异恰为 rel32+dir32 两处重定位操作数），L2 判定升级为字节级证据。
- 参照字节来源核验 ✓：IDA 独立抽取 0x553514/0x553082/0x541D10 与脚本 ref hex 逐位一致（参照非伪造）。①② 结论：/tmp/crttest 重跑输出与 §2.2 摘录逐字一致；cmp.py/final_cmp.py 的截断（min(len,size)）与重定位 4B 覆盖集逻辑审计正确。

**D4 库 provenance 口径被低估（§6.4「SP0 vs SP5」不是准确形态）**
- 复核实测 @comp.id：本仓 SP0 cl（12.00.8168）产 .obj = `0x000B1FE8`（低位=build 8168）；`tools/vc6/Lib/LIBCMT.LIB!ftol.obj` = `0x000E1C83`（build 7299）；`LIBCPMT.LIB!string.obj` = `0x000B1F6F`（build 8047）——**与我们编译器不同构建，且库内成员彼此也非同构建**；成员时间戳异质（string.obj 2000-02、ftol.obj **2004-02**，晚于 SP5 发布）；「SP5 版库」仅凭 `cmake/toolchain-vc6.cmake:20` 自述。
- 杀伤力已非假设：同类漂移在 d3dx9.lib 实际发生——`Float_AlmostEqual`（0x54212C，48B）在 d3dx9.lib 内有同算法副本但**指令选择不同**（库：`DF E0 F6 C4 41 7A…EB 04` vs exe：`DF E0 80 E4 41 74…EB 02`），即现库不能逐位重现该函数。libcmt/libcpmt 抽测 7 函数码字节稳定（差异全落重定位），但 0x55xxxx ~340 个 CRT 函数无实证指纹，不能外推。
- 报告 §2 结论措辞「同版库重链接即字节等同」为同义反复（"同版"是前提），真正的断言应是「**在仓库 = 原版库**」——该断言未证且 d3dx9.lib 已见反例。

### 证据不足

**D5 群 A 边界与细节瑕疵**
- `unknown_libname_528`（0x54202F）不是 44B 同型：实测 42B **双 guard 变体**（guard1=0x189598E + guard2=0x189598F，中间 `call crt_sub_00542059`，atexit(nullsub_96=0x542071)）。报告将其划入群 A「~186 条字节全同 44B」但抽查清单恰好不含 528。「guard 只有一个字节 0x189598E」不成立（0x189598F 有 2 处 xref）。guard 计数 370 xref / 185 函数 ✓ 与报告一致。
- §3.2 特征序列地址：报告「PAL3.exe@file 0x142169(=VA 0x542169)」应为 **0x142181**（=VA 0x542181，序列在函数入口后 0x18 处）；「22 字节」实为 **21 字节**。命中计数（各 1 份/0 份）复核一致。
- 31 抽样中除 351/523/524 外的 28 个未逐字节重扫（以 3 抽样 + guard xref 全量佐证，风险低）。

**D6 186 桩 supply=compiler_regenerated 与报告自身 §6.1 矛盾**
- §6.1 自认 44B guard 形的源级触发形态未定、MSVC6 实验只重现 12B 无 guard 形——供给路径未证，schema 却把 supply 写死为「compiler_regenerated（再生即得）」。thunk 报告 T5 的措辞（(b) 优先、(d) 保底）更稳。裁决 C（编译器合成、非 CRT 非游戏）成立，但 supply 一栏应降级为推定（confidence=B）直至 §6.1 实验闭环。

### spec 缺口

**D7 §1.2 reason 表不平账**
- 实测 skip_functions.json 1910 条：`thunk` 桶 **135 条整桶缺失**于报告表；「其余」实为 24（表写 27）；表列合计 1778 ≠ 1910。923 桶拆分明细（§4.3）亦无 Σ=923 校验行。附：crt_runtime 筐内实测 522 具名 / 401 无名（210 unknown_libname + 136 sub_ + 55 crt_sub_），与普查「512 具名」差 10 属具名判据口径差，非矛盾但口径未钉死。

**D8 boundary 枚举缺类 + 兼容矩阵冲突**
- 8 类枚举没有「第三方静态库（d3dx9）」的位置：lib_crt/lib_stl 装不下、engine_static 语义错（案 3 之后暴露）。
- 兼容矩阵规则「boundary=lib_crt|lib_stl ⇒ skip_reason=lib_relink_ok」**禁止** lib 类登记 dual_def_workaround（任务预判的重叠情形不可登记）；`skip_reason=lib_relink_ok` 把 CRT/STL/d3dx9 三种 provenance 混作一值。
- check_annotations 新增矩阵 = 跨 skip_functions/functions.json 的职责扩张（现行只查 annotation 内部一致性），报告未明示。18 个 skip∩functions.json 双注件（6 SingletonThunk + 2 _DllMain + 4 compiler_init + 3 accessor + ?UIInitSystem/?UIDestorySystem + crt_sub_005415C0）是矩阵的实际考题，报告未列对账清单。

**D9 完备性 spec 口径**
- 分母「5611（survey 5609 + 复核 2 计差属工具口径）」不可复现：IDA `idautils.Functions()` 独立计数 = **5609**，与 survey 一致，「+2」无出处。与 census 214 编译单元的关系完全未述（两个 universe：函数级分类 vs 单元级 S2/match，spec 未桥接）。
- 「未分类=0」可检查（方向可行）；但「G/E 无 decl 清单=0」对 E 类是伪命题（E 的供给是 lib_relink 非 decl），判据须随案 3 改写。
- 可达性红旗扫描的间接调用盲区（函数指针/虚槽）在普查 §四 自认（「孤立≠永不被调」），但 §5.1 完备判据未把该限定写入「完备」定义——虚槽可达的 G 冤户漏检时红旗仍可为 0。建议补 vtable 槽扫描。
- §5.1-6 形状分类器表缺 528 的 42B 双 guard 变体（另有 8B `mov eax,1; retn 0Ch` 形、22B EH-magic 过滤形未入表）。

---

## 4. spec/schema 补丁建议

1. **boundary 枚举加 `lib_vendor`（第三方静态库；如 d3dx9.lib）**，supply=lib_relink，evidence 记 `lib_member`（`d3dx9:d3dxmath.obj`）。E 类重新定义为「gbengine/src 有源的引擎代码」并**从 0x542xxx 簇清空**；或在 8 类表中新增 L3「库预编译-第三方静态」。
2. **§4.3 迁移改判**：sub_542xxx 真代码簇、`__m64/__m128::_static_*` ×86、`Float_AlmostEqual` → lib_vendor(d3dx9)，**不 unskip、不建 decl**；调用点按 thunk 报告 T3/T4 用 D3DX API 真名 + SDK 头声明（C2065 修复路径不变）。`sub_542xxx` 分流表中「E」列改「lib_vendor」。
3. **兼容矩阵加法**：允许 `(boundary=lib_*, skip_reason=dual_def_workaround)` 白名单（如实登记 decl 双源事实），或拆 `decl_state ∈ {none, decl_only, full}` 独立轴；补「skip∩functions.json 双注件」机器对账（现存 18 件即考题，含 _DllMain@12_1/3 的 dup_decl_elsewhere 路由）。
4. **§1.2 表重出**：补 `thunk` 135 桶、其余改 24、行末加「合计=1910」断言；§4.3 拆桶明细加 Σ=923 校验行。
5. **实证指纹（§5.1-5）字段扩展**：`lib_member` + `hidden_diff_ratio` + `outside_reloc=NONE 机器输出`；按 D3 的 7 案格式为每个 lib_* 家族留存。引用「字节等同」必须带占比（本复核：23.4%）或指向本文件。
6. **完备分母**改「idautils.Functions()=5609」并记口径（或解释 5611 来源）；补「函数→probe_census 编译单元」映射；「完备」定义显式携带「间接调用盲区」限定 + 补 vtable 槽扫描。
7. **形状表（§5.1-6）补形**：42B 双 guard 桩、8B stdcall 恒真 stub、22B `cmp [eax],0E06D7363h` EH 过滤器。
8. **supply=compiler_regenerated 锁定前置**：完成 §6.1 的 44B 形 MSVC6 再现实验；未完成前 confidence=B + supply 标「推定」（对齐 thunk T5 的 (b)/(d) 双路径措辞）。
9. **库版本约束**：把「lib 版本=工件版本」写入约束文档，并对 libcmt/libcpmt 的 0x55xxxx 桶补 ≥N 个实证指纹（d3dx9 已有反例，禁止从 7 函数外推全库）。

---

## 5. 未复验清单（显式）

| 项 | 状态 |
|---|---|
| unknown_libname 526/527 逐个字节（525 抽 1 支撑群 B 家族定性） | 未复验 |
| 群 C 531/532/533 的 x87 FDIV 叙述（279B/1183B/19B 形状） | 未复验（529=EH magic 已验，群 C 定性成立） |
| 报告 31 抽样中其余 28 个「字节全同」逐字节重扫 | 未复验（3 抽样 + guard xref 370/185 佐证） |
| `?_todo_52B9A0@ParticleVisNode` 名字误挂第 4 例 | 未复验（前 3 例已验） |
| `crt_sub_00541490` 字节面（5B jmp 形） | 未复验（普查语料+报告互证） |
| `fn`/`PushMatrixStacks`/`PopMatrixStacks`/`?UIInitSystem`/`?UIDrawText`×3/`SingletonThunk`×7 逐条裁决 | 未复验（引普查 §二，未逐一 xref+字节） |
| start 的 PE entry-point 字段核对 | 未复验（反编译序列已足证 L1） |
| 90 条 compiler_generated_nop 逐一定性 | 未复验（报告自认未做） |
| PAL3A.exe 体系对照（除特征序列 1 命中外） | 未复验 |
| t.exe 侧 ctor1 diff=22 vs 库侧 23 的 1 字节出入根因 | 未复验（不影响 outside_reloc=NONE 结论） |
| `__m64/__m128::_static_*` 86 个与 d3dxmath.obj 成员逐一对应 | 未复验（符号表全家佐证推断） |
| libcmt/libcpmt 未抽样 ~340 个 CRT 函数的版本漂移 | 未复验（D4 风险敞口） |

---

*附：全部复验可按本文件地址/偏移复现。实验复跑件在 /tmp/crttest（原报告）与 /tmp/crt_review（本复核补验脚本 verify_lib.py/verify_fwd.py）。*
