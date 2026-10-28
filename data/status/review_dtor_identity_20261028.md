# 对抗性复核 · dtor 身份取证报告（2026-01-28 复核，对象 research_dtor_identity_20261028.md）

> **复核立场**：不信任报告，只信二进制。所有关键结论经 IDA MCP（session `278944bc`，与报告同库但换路径：py_eval 字节扫描/xrefs_to 穷举/get_bytes 逐槽）+ objdump 独立复验。
> **本复核只写本文件**，未改任何产品/标注/管线/报告文件。

---

## 1. 复核总结

**ACCEPT-WITH-FIXES** —— 五个身份判定（#2/#3/#4/#5/#6/#12）经双路字节形复验全部成立，"命名倒置/名不可信/合成物不手写"的核心论点站得住；但存在 1 处计数硬错（22 槽→实 27）、1 处地址硬错（#13 0x401040→真入口 0x401030）、C2065 因果链单类前提与标注面矛盾（实为 18 路多重归属）、GetVertexBuf 矛盾主假说（COMDAT 折叠）被字节证伪（应为 PDB 名字挂错）、以及完备性 spec 无法分诊其自身案例 #6、缺 PDB 名分支等缺口。

---

## 2. 逐项 verdict 表

| # | 复验项 | verdict | 证据（独立取证） |
|---|---|---|---|
| 1-① | `Destroy__ovl_03`@0x43DE40 是共享虚方法而非合成物 | **CONFIRMED** | disasm 双路（IDA+objdump）：32B 体=`mov ecx,[esi+44h]; test; call gbRefObject::Release(IAT 0x56a58c); mov [esi+44h],0; call 0x445c10; pop esi; ret`——成员访问+API 调用，无 vptr 写、无 flags/delete、bare ret ⇒ 非 dtor 非合成物；25/27 个 vtable 表在 **+0x0c（槽3）** 持有 0x43DE40 ⇒ 确系虚方法共享 override |
| 1-② | 18 code xref + 22 vtable 槽 | **PARTIAL** | code xref **18 ✓ 精确**（IDA CodeRefsTo 逐条与报告列表同）；vtable 槽 **✗ 实测 27**（DataRefsTo 27 址逐一 get_bytes 复核：25 表槽3@+0x0c；0x56B898 槽6@+0x18；0x5705D0/0x5706CC 的二重命中=相邻表同址槽3）。报告"22"为欠数 5 |
| 1-③ | 「公共基类归属」是否站得住 | **PARTIAL（UIWnd 分支被证伪）** | 决定性 get_bytes：**UIWnd 自身 vtable 0x56AEC8 槽3=0x445c10（基实现，标注 HideAll）≠ 0x43DE40** ⇒ 挂 UIWnd 实现体与字节矛盾；持有表抽验 7 个（UIListBox 0x56AD20/0x56B1BC、UILoadingFrm 0x56B100、RenderTarget 0x56C590、CCBStage 0x5705D0、CCBRoleState 0x56B364、UITitle_YXXX 0x56B898、CUtil 0x5705F4）多标 base=UIWnd 但横跨 UI 窗口+CCBStage/RoleSystem 等 ⇒ 共享 override 出自 UIWnd 层级下**某中间类**，或逐类同体 override 经 COMDAT 折叠（两说未区分，见 §3-D4）；UIWnd.json bases=null、槽3 基实现标注 source=vtable_gap_fill_v1(unverified) ⇒ UIWnd/SceneObj 归属**均未定谳**（报告标"推测"诚实，但处置矩阵 A"挂公共基类 methods.json"若照字面挂 UIWnd 即与 vtable 字节矛盾） |
| 1-④ | C2065 根因=归属错置的因果链 | **PARTIAL** | decomp 名 `CCBRoleState::Destroy__ovl_03` ✓（文件+name 字段实证）；CCBRoleState.json methods["0x0043DE40"]=`CCBRoleState::Destroy`(evidence_level:**unverified**) ✓ 有单类表象。**但**：①0x0043DE40 同时被 **18 个 structs 的 methods 索取**（CCBRoleState/CCBResultWindow/UILoadingFrm/UIBigMap/EquipUI/LineupUI/SystemUI/JusticeBookUI/UIRoleSelectDialog/RoleSystem/MainEquipUI/UIListBox/UICoverFrm/CScreenMode/ParabolaCalculator/CCBUI/RenderTarget/UITitle_YXXX）——是 18 路多重归属非"单类成员"；②functions.json 该条**无 class 字段**（类自由签名 `int __thiscall Destroy(int nMode)`）；③同型机制先例就在 functions.json：0x00408BD0 NullCallback 注记「__thiscall caused codegen to skip declaration in free_functions.h (9 C2065 undeclared hits)」；④pal3/src grep 证 Destroy__ovl_03 **无任何定义/声明产出**（仅调用点；UIScene.cpp:2053/PropUI.cpp:341/CCBControlWindow.cpp:361/free_functions.cpp 调用仍在）。⇒ "归属错置→调用点不可见"大方向 ✓，"被当成 CCBRoleState 单类成员"单因链 ✗ 不完整 |
| 1-附 | overlay 注释与二进制的矛盾是否成立 | **CONFIRMED（成立，带保留）** | phase2/overlay/UI/UIListBox.cpp:82 称「无定义/声明（IDA overlay 合成名）」——0x43DE40 有定义体+functions.json 条目（provenance=[R93 修 2026-10-23] 命名碰撞=>__ovl_03，非"IDA overlay 合成"）+27 vtable 在册 ⇒ 对二进制/命名来源的定性确与事实矛盾 ✓。**保留**："无定义/声明"在生成源层面为真（codegen 未产出，grep 实证），报告"与二进制矛盾"措辞未分层；且同句"22 个 vtable 在册"数字错 |
| 2 | `_scalar_dtor_BE80`@0x44BE80=纯析构 vs `sub_44BE40`=真 deleting dtor | **CONFIRMED** | 0x44BE80：入口 `c7 06 fc af 56 00`（mov [esi],0x56AFFC 设 vptr）+SEH 序言+成员析构串（含成员指针 delete@0x44bede，后随 `movl $0,0x3634(%esi)` 清成员——**非 delete this**）+尾 `call 0x43dd10`（??1UIListBox）+0x44c11a bare ret（单参无 flags）⇒ 纯析构 ✓；667B=0x29B ✓。0x44BE40：`call _scalar_dtor_BE80; test [esp+8],1; jz; push esi; call ??3(0x541d10); add esp,4; mov eax,esi; pop esi; retn 4` ⇒ 教科书 scalar deleting dtor ✓ 30B ✓。命名倒置 ✓ 成立 |
| 3 | `UIFrameWnd__deleting_view`@0x43D880=纯析构 thunk | **CONFIRMED** | disasm 恰 2 指令：`mov [ecx], offset stru_56ACFC; jmp 0x445b40`（??1UIWnd 体）——无 delete、无 flags、无 this-adjust ⇒ 纯析构 thunk ✓ 名 "deleting" 误导 ✓。xref 抽验全中：`??1SystemUI`×4(0x4a7768/78a2/78ef/78ff) ✓、SaleUI/PropUI/LineupUI×2/MainEquipUI/EquipUI/RenderTarget_InitNPCPanel/UIMap::UIMap ✓（报告 xref 列表逐条准确）；作 UI3DCtrl::_scalar_dtor_D860 析构步 ✓（0x43d863 code xref）；0x43D860 xref 恰=1（data 0x56acfc）✓ 报告"仅 vtable 0x56acfc" ✓ |
| 4 | `sdtor_15`@0x450370=scalar deleting dtor + `_UICaption_adjthunk` 调用链 | **CONFIRMED** | 0x450370：`push esi; mov esi,ecx; call 0x450390; test [esp+8],1; jz; push esi; call ??3(0x541d10); add esp,4; mov eax,esi; pop esi; retn 4` ⇒ test flags,1 形 scalar deleting dtor ✓ 30B ✓（析构步 0x450390 名 DelegateRender 确为名错位，报告引用一致）。链：0x4506C0 `?_UICaption_adjthunk`=`sub ecx,48h; jmp _sdtor_15`（8B）⇒ MI this-adjust→deleting dtor ✓ |
| 5 | `_nearby_452570`=compiler_global_init_stub（非 dtor）+ GetVertexBuf 尾跳矛盾 | **CONFIRMED（主判）+ 子问题独立裁定：COMDAT 折叠证伪，名字挂错成立（最可能解）** | 0x452570：`fld dword_56B1B8(=0x41400000=12.0f); fadd st,st; fstp flt_DC25B8; retn` ⇒ 全局浮点初始化存根非 dtor ✓；skip_functions["0x00452570"].reason=compiler_global_init_stub ✓。**报告未给的补强**：0x580380 为函数指针表（0x452540/0x452560/0x452720/0x452750/0x452770…），其中 4 个皆 `e9 0b 00 00 00 90 90 90`（jmp +0x10 越 NOP 对齐入口）；0x452550（GetVertexNum 真身体）=`mov eax,[0x56B1B8]; mov [0xDC25BC],eax; ret`——**同样是全局初始化存根**。⇒ 该区=static-init 存根+对齐 thunk 群。GetVertexBuf 矛盾裁定：①COMDAT 折叠**证伪**（折叠需字节全同体，无第二体；邻址同形 thunk 表明 5B-jmp=对齐入口形）；②**名字挂错（PDB 漂移）**证据直取：NavFaceLayer.json methods["0x00452560"]=`{"name":"GetVertexBuf","source":"pdb","evidence_level":"unverified"}`；真 accessor 应 `mov eax,[ecx+4];ret` 形（known_members vertbuf@+4），实际两体皆全局存写；同区 0x452580 已有 2026-10-16「错位修正」先例。报告以 COMDAT 折叠打头且"未定谳"收尾=方向错 |
| 6 | 完备性 spec 攻击（MI adjustor/COMDAT 折叠/__ovl 兄弟/矩阵可扩展性） | **REFUTED（存在缺口）** | 详见 §4。要点：STEP 1 形态判据分诊不了报告自身 #6（667B 全形 SEH 纯析构带成员 delete→按字面掉 A 组）；STEP 6 无 PDB 名分支且自身"??_G 前缀=真"即按名下结论（#13 即以此为"强"）；矩阵缺 ??_E/COMDAT 折叠/SEH 析构/ctor 形/无独立符号（局部类·模板）行；STEP 3 固定槽号假设不成立（0x56B898 槽6、复合表重叠）；无"槽→adjustor→目标"追踪步；__ovl 兄弟清点步缺失 |
| 7 | 数字审计（≥3 项抽验） | **PARTIAL** | ✓18 code xref 精确；✗"22 vtable 槽"→**27**；✓923 crt_runtime 精确（reason 直方图）；✓附加全中：32B(#1)/667B(#6)/30B(#2#4#12)/8B(#9#11)/decomp 语料 3695 文件。另 **#13 地址错**：`??_GAStarPathFinder@@UAEPAXI@Z` 真入口 **0x401030**（IDA func=0x401030–0x40104E，前邻 ??1AStarPathFinder@0x401000；0x401040 处是体内 push esi+call delete），报告写 0x401040。"12+ 案例"口径含糊（摘要实列 17 行） |
| 8 | `_empty_dtor_retirement.json` 存在且主张一致 | **CONFIRMED** | 文件在 data/status/_empty_dtor_retirement.json ✓；报告 §3.3 引文与原文逐句一致（vtable 存储自动生成/类上下文正确性路线/不设专项 codegen 修复）✓；status=RETIRED 2026-09-14（退役对象是"空析构尾跳 codegen 修复"记账项，报告引用其 implication 忠实）。附引文件 crt_skip_census_20261028.md / _cleanup_correction_scalar_dtor_orphan.md 均存在 ✓。**边界判据核对**：处置矩阵 A=必须源码写、B/C/D/E=源写 ~X()+delete 交 MSVC6 合成或不写 ⇒ 与「构建系统可再生产⇒无需逆向；真游戏方法必须源码重建」**无冲突** ✓ |

---

## 3. 缺陷清单（按严重度）

### 矛盾（与二进制/事实不符）
- **D1 计数硬错**：「22 vtable 槽」（摘要表+§2.1+矛盾记录段）→ 实测 **27**（25×槽3 + 1×槽6 + 2 处相邻表同址复命中）。报告列表尾"……"自知未穷尽，却在摘要以 22 作定数。
- **D2 #13 地址硬错 + 名字式举证**：`??_GAStarPathFinder@@UAEPAXI@Z` 报告记 0x401040，真入口 **0x401030**（30B `test flags,1` 形 deleting dtor 在 0x401030–0x40104D）；且"证据强度：强（真 MSVC 名 ??_G）"纯按名字下结论——直接违反「名不可信原则」（该 ??_G 名不在 functions.json/skip_functions，来源疑 PDB，未溯源）。
- **D3 C2065 因果链单类前提错**：「被当成 CCBRoleState 单类成员」与标注面实态矛盾——18 路 methods 多重归属 + functions.json 类自由条目 + NullCallback 同型注记（__thiscall 自由函数 codegen 跳过声明 ⇒ 9 C2065）。

### 证据不足
- **D4 归属推测未做决定性一查**：「UIWnd/SceneObj 系公共基类」的 UIWnd 分支被 UIWnd 自身 vtable 槽3=0x445c10 一票证伪（本复核一次 get_bytes 即得）；「共享基类 override vs 多类同体 COMDAT 折叠」两说未区分（27 表同址槽3 亦可由逐类同体 override 折叠成，需类层次/源级证据排除）。处置矩阵 A"归属公共基类 methods.json"按字面执行有挂错 UIWnd 的风险。
- **D5 GetVertexBuf 矛盾主假说无据**：COMDAT 折叠被字节证伪；名字挂错（source=pdb/unverified + 真 accessor 应为成员载入形 + 同区错位修正先例）证据就在 NavFaceLayer.json，报告未引，反以折叠打头。
- **D6 #15/#16/#17 证据仅分类互证**：skip reason/compiler_generated/decomp 名均为管线自产分类，无字节形（报告自标"中"可接受，但 #14 的"强（skip_functions 实证）"与 #5 的"强"含 reason 循环自证成分——reason 即被检定对象）。
- **D7 "12+ 案例"口径不明**（摘要表 17 行 vs STEP 4"本批 12+"未给基数）。

### spec 缺口
- **D8** STEP 1 判据与正文判定标准不一致（见 §4）。
- **D9** STEP 6 名字校验缺 PDB 名分支；且"??_G/??_E 前缀=真 MSVC 删除析构"本身是名字结论。
- **D10** 处置矩阵缺行：vector deleting dtor（??_E，循环 delete[] 形）/ COMDAT 折叠 / SEH 包装析构（~UIWnd 型）/ ctor 形符号（ovl 家族内即有）/ 局部类·模板实例无独立符号情形。
- **D11** STEP 3 固定槽号假设（槽3 不恒定）。
- **D12** __ovl 兄弟清点步缺失。

### 措辞
- **D13** 「与二进制矛盾」掩盖分层：overlay 注释的"无定义/声明"在生成源层面为真（codegen 未产出），错的是归因（"IDA overlay 合成名"）与"不存在"暗示。
- **D14** #7 证据强度"强"内含 skip_functions reason 循环自证；"compiler_"前缀（compiler 合成）是分类推断（存根无独立 init-table 引用：ptrs_to_452570=0，执行入口仅 0x452560 thunk），"非 dtor"铁、"compiler 合成"弱。

---

## 4. spec 缺口与补丁建议

| 缺口 | 现状 | 补丁 |
|---|---|---|
| STEP 1 形态分诊不闭合 | C 组="mov [ecx],vtable; jmp/call base_dtor，无 delete"、B 组="test flags,1→delete"——报告自身 #6（0x44BE80：vptr 写+SEH+成员 delete+尾基析构，单参 bare ret）按字面**三组全不匹配**，会掉入 A 组"游戏逻辑"误判（正文实际用的是"尾无 flags-delete + 单参签名"另一套判据） | C 组判据改**签名+尾形**为主：「单参（bare ret）+ 尾部无 flags-delete + vptr 重置/成员清理/基析构任一」；B 组以「栈参 flags + retn 4 + delete(this)」为充要；SEH 序言列为中性特征不参与分组 |
| STEP 6 名字校验 | 只认 ??_G/??_E 与 _<ADDR> 占位名；"??_G 前缀=真"即名字结论 | 增加 **PDB 名分支**：source=pdb/unverified 的语义名一律降级为线索，身份必须字节形独立成立（GetVertexBuf 案例族）；??_G 名只作"候选身份"，须 test-flags 形背书后才可定谳（#13 教训） |
| STEP 2 adjthunk 一刀切 | "仅 vtable 槽 + adjthunk 调用 ⇒ B/D 合成物" | 增加分支：adjthunk 目标若是 A 组体（共享方法 adjust 转发），按 A 组处置；合成物判定以**目标体字节形**为准 |
| STEP 3 槽号定位 | 假设同名方法跨表同槽 | 改为「逐表定位槽位+记录槽号离散度」（实测 25×槽3/1×槽6/复合表重叠），槽号仅作辅助不作归属判据 |
| COMDAT 折叠 | §4.3 仅"标折叠嫌疑回退 objdump" | 矩阵加 **F 行（折叠嫌疑）**：同址多表共享 ≠ 自动 A 组；需排除"逐类同体 override 折叠"（比对持有类是否有共同中间基 / 构造函数 vptr 写入链）后才可挂基类 |
| 矩阵缺行 | — | 增加 **??_E（vector deleting）**行（循环/数组 delete 形）、**SEH 构造/析构包装**行、**ctor 形符号**行（ovl 家族含 UIFrameWnd_UIFrameWnd_ovl_*）、**无独立符号**注记（局部类/模板实例可能整体内联，处置=不出现于符号清单） |
| vtable 槽含 adjustor | spec 无"槽→adjustor→目标"追踪 | STEP 2 增加：槽值若为 adjustor（sub this,N; jmp），剥 thunk 后按目标体字节形定组 |
| __ovl 兄弟清点 | 未知⑦悬置，spec 无清点步 | STEP 2 前置**撞名家族清点**：grep `__ovl` 全标注面+decomp 语料成表。本次复核实测 10 兄弟（CCBFiveNimbusWindow_sdtor_ovl@0x443530 · Destroy_ovl_02@0x4C6290 · Create_ovl_1@0x4A16C0 · Create_ovl_1_0@0x4A8770 · ProcCommonTask_ovl_@0x4C7680 · UIFrameWnd_UIFrameWnd_ovl_00442d40 · _00443550 · UILoadingFrm_OnMessage_ovl_1aa0 · DestroyEffect__ovl_0a60 · Destroy__ovl_03），后缀三制式混用（序数/短址/全址）；functions.json 仅见 Destroy__ovl_02/03，「__ovl_03 暗示存在 00/01/04」未获证（序数按撞名组局部编号）——清点步应显式记录制式并放弃全序假设 |

---

## 5. 未复验清单（显式）

1. `??_GRole@@UAEPAXI@Z`@0x41BE30 的 8B thunk 形（未 disasm；同型 `Object_adjthunk_1be20`@0x41BE20=`sub ecx,38h; jmp _scalar_dtor_1BD0` 已验 ✓）。
2. `UI3DCtrl::_scalar_dtor_D860`@0x43D860 的伪码体（只验了 xref=1@0x56acfc 与调用 UIFrameWnd__deleting_view 的关系）。
3. #15 `_scalar_dtor_2BD0`、#16 weather 族 4 个、#17 0x411B80/0x411BB0 的字节形（报告自标"中"，沿用其 skip/decomp 名证据，未单独 disasm）。
4. 27 个持有 vtable 的逐一 IDA 类名核对（抽验 7 个）；「中间基类 vs COMDAT 折叠」的终审区分。
5. 0x580380 表的性质终审（static-init 表 vs vtable）——影响 0x452570 的 "compiler_" 合成定性（"非 dtor"不受影响）。
6. C2065 因果链的 codegen 发射代码路径（未追 codegen 源码；以 functions.json NullCallback 注记为同型旁证）。
7. match/L1 字节验证（报告自报未跑；复核同为只读取证，不适用）。
8. `DelegateRender`@0x450390"多 vptr 重置析构"的逐指令复验（引用报告 disasm 摘录，未独立反汇编全文）。

---

## 附：复核工具与关键地址账目

- IDA MCP session `278944bc`（original/PAL3.exe.i64）：py_eval 字节扫描（vtable 逐槽/指针表/函数边界）、xrefs_to 穷举（more:false 闭合）、disasm、get_bytes；objdump（0x43de40/0x44be80/0x44bec0 区）交叉。
- 关键实测值：Destroy__ovl_03 code xref=18/data xref=27（槽3×25、槽6×1@0x56B898）；UIWnd vtable 0x56AEC8 槽=[0x445E70,0x445CD0,0x445C60,**0x445C10**,0x445B90,0x445B20,0x445D10]；0x44BE80=0x29B/667B、0x44BE40=0x1E、0x450370=0x1E、0x43D880=0xB/2 指令、0x4506C0=8B、0x41BE20=8B；crt_runtime=923、compiler_scalar_dtor=1、compiler_global_init_stub=53；AStarPathFinder deleting dtor 真入口=0x401030（0x401030–0x40104E）；0x452550=`a1 b8 b1 56 00 a3 bc 25 dc 00 c3`；0x56B1B8=0x41400000(12.0f)；ptrs_to(0x452560)={0x580384}、ptrs_to(0x452570)=∅；decomp 语料=3695 文件。
