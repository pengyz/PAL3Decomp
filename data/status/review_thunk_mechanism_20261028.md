# 对抗性复核：跳板机制调研（research_thunk_mechanism_20261028.md）

> 复核人：对抗性复核员（独立攻击式复核）。复核时间 2026-10-28。
> 立场：不信任报告，只信二进制与实测。取证路径：idapro MCP（session `278944bc`，与报告同 IDB 但**全部查询独立重做**：get_bytes 原始字节、py_eval 全量普查、xref 反查）+ 原始 PE 导入表解析（独立于 IDA）+ `data/annotations/` JSON 全量审计 + `pal3/src`/`phase2` 源面核对 + `tools/vc6/Lib/d3dx9.lib` nm 语料。
> 本文件为唯一写入物；未动任何产品/标注/管线/报告文件。

---

## 1. 复核总结

**ACCEPT-WITH-FIXES** —— 核心机制结论（PSGP 定性与 (c) 裁决、T5 字节形正误反转、T11 名实错位与事故链、T7/T8 筐拆分）经独立字节级复验全部站得住，但存在 2 处计数/普查被证伪、1 处"链上不可见"断言被证伪、1 处与 dtor 姊妹报告的重大定性矛盾（`_nearby_452570`）、1 处现状处置描述与实测相反（T6），以及 (d) 手工合成路线与「勿手写」纪律/用户边界判据的正面冲突——须修复后才可作为落地依据。

---

## 2. 逐项 verdict 表

| # | 复验项 | verdict | 一句话依据 |
|---|---|---|---|
| 1 | T3/T4 PSGP 定性 | **CONFIRMED**（定性+裁决 (c) 成立；计数另见 §3-B1） | ①0x6090A8 表 292B=73 槽全指针、slot[7]=0x542526/槽址 0x6090C4 ✓；②init@0x546F41 反汇编逐条吻合（`rep movsd` 0x49 dword 模板→表、注册表 `"DisablePSGP"`@0x572B78/`"DisableD3DXPSGP"`@0x572B68、IsProcessorFeaturePresent(7)/(6)+`crt_sub_00546E9C()&8` 三路改表）；③槽位链 byte-exact：tmpl[7]=0x5450B5（`55 8B EC 83 EC 0C 56 8B 75 0C D9 46 08 …` 矩阵×向量真身）、tmpl[35]=0x544777（矩阵乘真身）；④d3dx9.lib 含 `?c_D3DXVec3TransformCoord`/`?SSE_D3DXVec3TransformArray`/`?D3DXPSGP*`/`?_C@_0BA@…DisableD3DXPSGP`、`__imp__D3DX*`=0 ✓ |
| 2 | T5 SingletonThunk 字节形 | **CONFIRMED**（报告对、skip_reason 错） | **45/45 全量**（非抽样）均为 10B `B9 imm32 E9 rel32`（mov ecx,&obj; jmp），0x431D90 `B9 38 C3 D8 00 E9 26 6E FD FF`=mov ecx,0x00D8C338;jmp 0x408BC0 逐字节与报告引文一致 ⇒ skip_reason「mov ecx,[0x..]」内存取址口径**错误**（同址值、错寻址模式）；0x53C890 同形误归 compiler_thunk ✓。ctor/dtor 对定性成立：45 件按对象 imm32 分 31 组、**14 组同对象双跳板**（0xBFAB60 组 `0x4044B0→??0TxtFile / 0x4044D0→…`、0xD8C338 组等）+ 胶水 `E8..E9..`+push dtor→`_atexit`(0x553041) 链 + `$E187` 复合初始化段名 ⇒ MSVC6 静态对象产物定谳 |
| 3 | T5 LNK2001 三要素 | **PARTIAL** | 三要素 ≥2 例 ✓（0x431D90/0x431DB0：声明 free_functions.h:279-280 ✓、调用 PalScript.cpp:1462-1463 ✓、无定义体 ✓；0x4B6D70/0x4BFD60：声明 :283-284 ✓、调用 PAL3.cpp:3660/3698 ✓、无定义体 ✓）；但**调用面漏 PalScriptMgr.cpp:3135/3142**（0x431E70/0x431EC0 实际所在），且「其余 39 个…现链上不可见」**被证伪**（见 §3-B4）。(b) 裁决方向成立，但须按对象类型分三子族再生（见 §4-C） |
| 4 | T11 名实错位三例 | **CONFIRMED**（正解基本完备，措辞需限定） | 0x4B8200：66B 浮点相等短路+`rand()%10000+1` 插值 random-lerp ✓（`99 B9 10 27 00 00 F7 F9 42` 逐字节），IDA 名 `j_D3DXVec3TransformCoord` ✓，free_functions.h:393 + free_functions.cpp:20093 伪签名体 ✓（行号精确）；0x41CA30=90B 真 setter（8 字段写+call 0x41C710+`C2 18 00`）✓、0x41D590=20B wrapper（call 0x41C710+`C2 04 00`）✓、二者 IDA 名 j_ 前缀且在 skip(reason:thunk) ✓；overlay sg_emission_control.cpp:381-382 + phase2/base:377 引用**行号精确** ✓；语义损伤面（404/463/623/625/627 五处以 `(0, LODWORD(浮点), …)` 形落进伪定义体）实测存在 ✓。但「0x4BA800 内 0x4BA97F 等 5 处」误导（5 xref 仅 1 处在 0x4BA800 内），修复措辞有误改风险（§3-C3/§3-D8） |
| 5 | T7 5B 别名 ~300+ / 39 件闭环 | **PARTIAL** | 抽验 5/5 中（0x401840→0x401850 +0x10 ✓、0x44BE70→0x442390 `??1UIFrameContainer` ✓、0x452560→0x452570 ✓、0x401BB0 10B 胶水三段 ✓、0x53C890 ✓）；compiler_thunk 217 拆分 **byte-exact**：E9×188+E8E9×28+误归 1 ✓（全量普查非抽样）；但 spec 对三分（ILT/COMDAT/tail-jmp）无判据、(d) 路线冲突（§3-A2）、39 件字节承担者未闭环且「不可见」前提已被 §3-B4 打破 |
| 6 | spec 攻击 | **PARTIAL（多缺口）** | ①「误归仅 1/1910」自相矛盾（§3-B5）；②registry/skip 正交性概念成立但迁移/共存/冲突/批0 爆炸风险全未虑（§3-D2）；③(b) 字节漂移判据缺失（§3-D3）；④unknown_libname 族 210 条未覆盖（§3-D4），另有 12 个 `B9 imm32 FF 25 [IAT]` 变体落在 8 类签名外（§3-D5）——「充分判据」不成立 |
| 7 | 数字审计 | **PARTIAL** | 计数 ✓：T5×45、T6×10、T10×85（decomp 语料 grep 实测 85）、T1 31+2（0x542072–0x54212B 实测 31 格×6B+T2 2 件）、T7 188/28/1、T9×3（0x43A1F0=92B/0x43A810=92B/0x4411D0=108B 名+尺寸精确）、T11×6、T8×28、T2=2、adjthunk 污染=25 ✓；计数 ✗：T3 A 形（17/11→实测 **33/15**）、导入表 KERNEL32/GBENGINE（28/80→实测 **67/249**）；另 1 处地址错（0x431DA5→0x431DA0） |
| 8 | 与 dtor 报告互洽 | **PARTIAL（含 1 重大矛盾）** | `_UICaption_adjthunk→_sdtor_15` 互洽 ✓（0x4506C0 `83 E9 48 E9 A8 FC FF FF`→0x450370，目标体 `56 8B F1 E8 … F6 44 24 08 01 74 09 56 E8 …` scalar deleting dtor 形，两报告口径一致）；`_nearby_452570` **定性互相矛盾**（§3-A1）；合成物处置原则**互相矛盾**（§3-A2）；T6 现状描述与 dtor 反模式表冲突（§3-A3） |

---

## 3. 缺陷清单

### A. 矛盾类（重大，须修）

**A1. `_nearby_452570` 定性与 dtor 姊妹报告矛盾（任务点名项）**
- dtor 报告（research_dtor_identity_20261028.md §2.7）：**定谳**「编译器全局初始化存根（`flt_DC25B8 = dword_56B1B8*2`），skip reason=`compiler_global_init_stub`，非 dtor」，并显式记录「GetVertexBuf(0x452560) 尾跳到存全局 float、返回 void 的 init 存根 = 语义不一致，未定谳」的矛盾条目。
- thunk 报告（§2 T10 / §5.7）：称 0x452570 真身为「**float 访问器**语义仅从字节推测」，且把 0x542560→0x452570 当普通 5B 别名样例，对 GetVertexBuf 语义矛盾**只字未提**。
- 独立字节复验（get_bytes 0x452570）：`D9 05 B8 B1 56 00 DC C0 D9 1D B8 25 DC 00 C3` = fld [0x56B1B8]; fadd st,st; fstp [0xDC25B8]; ret——**写全局的初始化存根，不是访问器**（访问器不写内存）。skip_functions.json 实条目 `{"name":"UITitle_BBTY::_nearby_452570","reason":"compiler_global_init_stub"}` ✓ dtor 报告口径与字节、skip 三重一致；thunk 报告的「float 访问器」为**误读**。按任务纪律「两报告定性互相矛盾即重大缺陷」记重大。

**A2. 合成物处置路线与「勿手写」纪律/用户边界判据正面冲突**
- dtor 报告原则：「合成物该由 MSVC6 重生成，**不该手写**」（scalar deleting dtor/adjustor thunk/纯析构 thunk 均 COMDAT 合成）；用户边界判据：「构建系统可再生产 ⇒ 无需逆向」「编译器合成物/库供给件无需源码重建」。
- thunk 报告 T5 裁决「(b) 优先，**(d) 保底**」、T7「**(d)** 纯布局桩：保底用 `__declspec(naked)`+`_asm jmp` 手工合成」、落地项 9「T9 …asm 层重建定义体（SEH 序言可模板化）」——三处手工合成路线均未评估：(a) 与勿手写原则的冲突；(b) 若 MSVC6 同时自动产出同形件 ⇒ **LNK2005 重复符号**（正是批0 单源清 C2556/2373×144 同族风险）；(c) T9 自身裁决 (b)（「源码成员 ctor 可抛/有 try 时 MSVC6 自动包 SEH prologue」）与落地项 asm 重建**自相矛盾**。
- 另：T5/T7 的 (d) 恰恰违反「编译器合成物无需源码重建」边界——(b) 成立时 (d) 不该存在；(b) 不成立时正确的兜底是 (c)（链接期供给）或修正构建条件，而不是手写。

**A3. T6 现状处置描述与实测相反（并遮蔽了一个活的「合成物被当手写」案例）**
- 报告 T6 行「现状处置 | skip(compiler_thunk/thunk)」。实测：10 个 T6 地址（0x41BE20/0x4506C0/0x451800/0x451C70/0x47E570/0x4C88B0/0x4C9530/0x4CB340/0x4CD9F0/0x4D5850）**全部不在 skip_functions.json、也不在 functions.json**（大小写不敏感双查 + 原文 grep 零命中）；真实处置是**正常导出+codegen 渲染为类成员方法**（`UICaption.h:41 virtual void _UICaption_adjthunk(); // 0x004506C0`、`CEffect.cpp:690 void CEffect::CreateOnePartical_adjthunk() { ((CEffect*)((char*)this-12))->CreateOnePartical(v1); }`，decomp 语料 5+ 件同名 JSON 在库）。
- 这恰是 dtor 报告反模式表首行「合成物被当手写 ⇒ 把编译器合成 COMDAT 当源码可写方法」的**活案例**：adjustor 被渲成 this-adjust C 体，编出来既不会是 8B `83 E9 imm8 E9 rel32`，还可能与编译器自动合成的 adjustor 撞 LNK2005/vtable 布局。thunk 报告因处置描述错误而未发现此风险。

### B. 与字节/数据矛盾（须改数）

**B1. T3 A 形计数被全量普查证伪**：按报告自己的签名（`6A 01 E8 rel32 FF 25 [分发表]`，且 FF 25 目标在 0x6090A8–0x6091D0 内——报告 A 样本全部满足）全量扫描：**A=33（全区）/15（微簇 0x5424BA–0x543A00）**，B=22/C=16（全区）、B=12/C=11（微簇）——**B/C 与报告逐个吻合，A 报告记 17/11 为漏数**（微簇 15 个 A：0x5424BA/5424DE/542502/542526/542798/5428EE/542918/542A64/542B61/542E2C/542FAE/543085/5432CE/54334E/543591；其中 0x54215C/0x5421F8/0x5422AA 等还是分发表初值槽，排除误扫）。总数应为全区 71 / 微簇 38（报告 55/34）。33 个 A 的 call 目标全部=0x546F41 ✓ 形态同质，无「另一 init」解释空间。
**B2. 导入表 census 被双路径证伪**：报告称「导入表全量（enum_import_names 实测）：ADVAPI32(6)/DINPUT8(1)/**KERNEL32(28)**/USER32(34)/WINMM(1)/BINKW32(10)/**GBENGINE(80)**」。实测 IDA enum_import_names（named=total）与**原始 PE 导入表解析**（独立于 IDA）双路一致：KERNEL32=**67**、GBENGINE=**249**（其余 5 模块 6/1/34/1/10 逐一吻合，总 368）。定性结论（无 d3dx*.dll/d3d9.dll 导入）✓ 不受影响。
**B3. 0x431D80 胶水 jmp 目标地址错 5 字节**：实测字节 `E8 0B 00 00 00 E9 16 00 00 00`（call 0x431D90 ✓；jmp **0x431DA0**），登记段 `68 B0 1D 43 00 E8 97 12 12 00 59 C3`（push 0x431DB0; call `_atexit`@0x553041; pop; ret）起于 **0x431DA0**（xref_to 0x431DB0 自 0x431DA0 佐证）。报告写「jmp 0x431DA5(登记段)」落在 push 与 call 之间，错。
**B4. 「其余 39 个无声明无定义…现链上不可见」被证伪**：`SingletonThunk_00539530`（45 件之一，`B9 50 15 7B 01 E9 B6 E0 FF FF` 形）在 `pal3/src/free_functions.cpp:24963` 有渲染调用 `atexit(SingletonThunk_00539530);`（GetSaveDataManager@0x5394F0 的函数局部 static 守卫模式），而**全 pal3/src+phase2 无任何其声明** ⇒ C2065/LNK2001 暴露面比报告所述更大（free_functions.cpp 属 C1003 截断单元（CLAUDE.md），错误可能被 102 条截断遮蔽）。二进制层「调用面仅胶水」仍成立（45 件 xref 全部为胶水 call×27 或 atexit push×18，零例外），但**渲染层可见性**判断错误。
**B5. 「误归仅 1/1910」与报告自身 T11 冲突**：报告 §4.1 称字节签名充分判据、全普查「误归仅 1/1910（0x53C890）」；但 T11 自证 reason:thunk 筐内 0x41CA30/0x41D590/0x485DC0/0x5044F0 四件是**真函数体误归**（全量字节普查确认该筐 135=5B×131+真身×4），加 0x53C890 至少 **5/1910**。另有签名未覆盖族（§3-D5）——「充分」不成立。
**B6. 字符串地址配对颠倒**：实测 `"DisablePSGP"`@**0x572B78**、`"DisableD3DXPSGP"`@**0x572B68**；报告写「"DisablePSGP"/"DisableD3DXPSGP"（字符串 @0x572B68/0x572B78）」按序读为反。

### C. 证据不足

**C1. 「782 个相关符号」不可复现**：d3dx9.lib 实测 PSGP 族 mangled 名 83 条（去重 76：c_D3DX 88 计重复、SSE_/D3DXPSGP/Disable* 各若干）、strings 相关 322、全 D3DX 行 5521——均非 782。报告四个点名符号族逐一存在 ✓、`__imp__D3DX*`=0 ✓，唯 782 数字存疑（无复现路径）。**未复验到**。
**C2. 0x41CA30「存 this+0x1C4 等 4 字段」不准**：实测 8 处字段写（+0x1C4/0x1C8/0x1D0/0x1EC/0x1CC=0/0x1D4=0x42C80000/0x1F0/0x1F4）+ push 0 + call 0x41C710 + `C2 18 00`（stdcall 6 参清栈）。核心定性（真函数误 skip）不受影响。
**C3. 「sg_emission_control::_todo_004BA800 内 0x4BA97F 等 5 处」误导**：xref_to 0x542533 = 0x4B9350/0x4BA97F/0x543C84/0x544288/0x544BD2 ✓（5 个地址全对），但仅 0x4BA97F 在 0x4BA800 内；0x543C84/0x544288/0x544BD2 在 **PSGP 库体内部**（generic 实现互调，(c) 供给，无需游戏源码处置）；0x4B9350 在 sub_4B9330（skip reason=`between_std_methods`，已抑制导出，调用不渲染）。⇒ (c) 修复面实际=**sg_emission_control.cpp:382 一处**（+ random-lerp 5 处改名），报告「5 处」框架夸大修复面。
**C4. init 的 CPU 特性映射为推测且疑互换**：实测顺序 PF(7)→`__m64::_static_54740C`(flag 1)、`crt_sub&8`→`__m128::_static_5471BA`(flag 2)、PF(6)→`__m128::_static_547042`(flag 3)；PF7=3DNow、PF6=SSE，故 54740C 更像 3DNow 而非报告标的「MMX」（报告对 5471BA 已挂「?」，对 54740C 的 MMX 标签无 hedge）。机制结论不受影响。

### D. spec 缺口

**D1.** (d) 手工合成无防撞护栏（详见 A2）：缺「(b) 探针证明不可再生」前置门、缺 LNK2005 探针对账、缺与边界判据的裁决记录。
**D2.** thunk_registry 迁移爆炸半径未评估：skip_functions.json 实际消费点 ≥6 处——`pipeline/ida/export_full.py:333-337`（**[t4-DECLARED-EXCEPTION]** 明文例外）+ `:1154-1161`（_skip_function_names 透传）、`pipeline/gen/stages/collect.py:96`、`pipeline/gen/data.py:56,221`（codegen thunk 替换）、`pipeline/ida/apply_annotations.py:2290`、`pipeline/check_annotations.py:743`、`pipeline/gen/annotation_view.py:129`。报告落地项 2「crt_runtime 筐拆筐迁入 thunk_registry」若执行时某一层仍只认 skip_functions ⇒ 抑制失效 ⇒ 大量跳板体涌入 codegen ⇒ 批0 同族 C2556/2373×144 爆炸。报告通篇**未提批0 教训与共存/冲突处理**。「语义正交」作为概念成立（skip=不导出抑制，registry=分类登记），作为迁移方案不完整。
**D3.** (b) 类字节漂移无判据：环 C 只说「探针编译确认输出形态签名」——形态同、字节异（padding CC/90、COMDAT 折叠、链接顺序、重定位位）时算 pass 还是回归，无规则；环 A 对 (b)(d)「按普通函数字节比对」在编译器再生场景即为漂移陷阱。
**D4.** unknown_libname 族未覆盖：skip_functions.json 中 **210 条** unknown_libname_*（主体 182 条以 `8A 0D …` 起真身），T1–T12 分类学与 8 类签名均未提其归类/处置。
**D5.** 签名表缺第 9 形：实测 **12 个** `B9 imm32 FF 25 [IAT]` 静态对象构造跳板（0x401BC0/0x401BE0/0x401C00/0x401C20/0x401C40/0x401C60/0x404530/0x404550/0x404670/0x4046A4/0x4CE0D0/0x4CE0F0，即 `mov ecx,&obj; jmp [IAT]`——T8 样本 0x401BC0 报告自己引用过）：不匹配 T5 的 `B9 imm32 E9`，会被 `FF 25 [IAT]` 规则误归 T1/T2 导入跳板。「8 类充分判据」在已知字节上即失败。
**D6.** 39 件字节承担者无闭环路径：遗留未知 #4 承认敞开，但 spec 缺关键一步——**thunk→对象全局（imm32）→源码归属 TU** 映射（45 件已可按 31 个对象 imm32 分组、14 组成对），无此映射则 (b) 再生无从写源、match 字节无承担者。
**D7.** T7 三分（ILT/COMDAT/tail-jmp）无裁决规则：(b)/(d) 路由「逐个」但无判据（何种 xref/布局证据判 ILT、何种判尾跳别名、各自字节可再生性）。
**D8.** 修复清单措辞风险：落地项 4「调用点改 `D3DXVec3TransformCoord` 真名」若照字面执行，会把 sg_emission_control.cpp:404/463/623/625/627 五处 **random-lerp 调用**（0x4B8200）也改成 D3DX 真名——语义二次损伤。应限定：0x542533 调用面（仅 :382）→D3DX API 真名；0x4B8200 调用面（5 处）→random-lerp 新名+真签名（浮点参）。

### E. 措辞

**E1.** 「全区 55」与 T1/T2 段「6B FF 25 全文共 55」两个 55 异义并存（后者=33 IAT+22 PSGP ✓ 经 6B FF 25 全量核对成立），易误读。
**E2.** T5 机制定性「命名空间级静态对象」应收窄外延：0x539530/g_ActorSaveData 是**函数局部 static + 守卫字**模式产物（GetSaveDataManager 懒初始化），同形同机制，但再生路径不同。
**E3.** T5 调用面清单应补 PalScriptMgr.cpp:3135/3142（且该二件的 atexit 目标在 IDA 另挂 `ConditionalCleanup`/`FindScript` 伪名——名不可信原则又一实证）。

---

## 4. spec 缺口与补丁建议

**A. thunk_registry 与 skip_functions 共存的可行形态**（回应 D2）：
1. **职责切分**：`skip_functions.json` 保留单一职责=「不导出」抑制表；`thunk_registry.json` 只做分类登记（family/shape/target/object_addr/provider/evidence/regen_path/verify_policy）。不迁移抑制权，只**迁移理由文本**。
2. **单一读点聚合**：抑制判定收口到 `pipeline/gen/annotation_view.py`（现有唯一读点纪律）：`suppress(addr) = addr∈skip_functions ∨ (addr∈thunk_registry ∧ decl_policy=='suppress_export')`；export/apply/check/collect/data 全部经此。export 侧读取属 `[t4-DECLARED-EXCEPTION]` 既有例外，须在 export_full.py 头部同步登记并写明理由（对齐现行惯例）。
3. **双写过渡期**：先建 registry 全量登记 + `check_annotations` 一致性校验（registry 标 suppress ⇒ skip 必须有同址条目；反向不要求）；跑四道门（布局等价/loop-errors 不增/l1 不降/证据自校验）+ `link_probe --check` 后，才允许删 skip 条目。**禁止一步单源清**（2026-10-06 批0 C2556/2373×144 教训）。
4. **冲突处理**：同址两表矛盾（如 registry 记 export、skip 记 suppress）⇒ check_annotations fail-loud，禁止静默优先级。

**B. 识别层补丁**（回应 D4/D5/B5）：签名表加第 9 形 `B9 imm32 FF 25 [IAT]`→`static_obj_ctor_thunk_to_import`；unknown_libname 族按字节形分流（真身→非跳板、E9/E8E9→既有筐），并把「误归率」定义改窄为「跳板形条目的族间误归」，或把 T11 四件计入误归——两选一，禁止维持「1/1910」原表述。

**C. (b) 再生路径按对象类型分派**（回应 item3/D6）：
- 游戏全局对象（如 0x8ACD30 组→InitSceneScriptLoader）：写 `Foo g_obj;` 于正确 TU ⇒ MSVC6 自动产 ctor/dtor 跳板对+胶水；
- 函数局部 static（0x539530/g_ActorSaveData 型）：写局部 `static`+守卫即再生；
- CRT 注入件（0x431D90/0x431DB0 = `??0Iostream_init`）：**不是「恢复全局对象源码」**，是正确 TU include <iostream> 触发 CRT 头注入——报告处置文本须改。
- registry 增 `object_addr`/`source_owner`/`regen_path(header|global|local-static)` 三字段，31 个对象组逐组排期；每组先探针编译验形（环 C），再入 match 地址清单（环 A）。

**D. (b) 漂移判据**（回应 D3）：两级判据——①形同：指令序列等价（助记符+操作数结构一致，重定位位 don't-care，尾部填充 CC/90 白名单）；②字节同：进 match。①过②不过 ⇒ registry 记 `byte_drift: tolerated|fatal` 人工裁决，不直接计回归；①不过 ⇒ (b) 不成立，转 (c)/修构建条件，**不转 (d)**（除非批0 级风险评估+LNK2005 对账通过——回应 A2/D1）。

**E. 修复清单文本修订**（回应 D8/C3/A3）：
- 项 4 拆两句：「0x542533 调用面（sg_emission_control.cpp:382）改 `D3DXVec3TransformCoord`+#include <d3dx9math.h>」与「0x4B8200 正名 random-lerp，5 处调用点（404/463/623/625/627）随名改签名（浮点参）」；并注明 0x543C84/0x544288/0x544BD2 属 (c) 库体内部、sub_4B9330 已抑制，均不在修复面。
- 项「T6」改为：现状=已导出当成员方法（勿手写风险进行时），处置=从 codegen 面移除+转 (b) 探针验证（源写继承布局让 MSVC6 合成），并同步 dtor 报告反模式表口径。
- 项「T9」删除 asm 重建路线，统一走 (b)（源写 ctor 触发 SEH 包装）；`decompile None` 改由 asm 语料辅助人工写源，产出不算合成物。

---

## 5. 未复验清单（显式）

1. **T4「generic 真身约 30 个（42–209B）」的逐个尺寸**：仅抽验 0x5450B5/0x544777 为真身（字节确认），30 个计数与尺寸区间未逐一核。
2. **d3dx9.lib 版本=「D3DX9 Summer 2003」及链接布局与原 exe 一致**（报告遗留#2）：符号存在性已验，版本指纹与落位未验。
3. **gbengine 导入库重建后 T1 31 件的 .text 落位**（报告遗留#3）未验。
4. **39 件未声明 SingletonThunk 的逐一对象归属/字节承担者**（报告遗留#4）：仅实证 0x539530 一例，其余未逐一排。
5. **0x53C890 的最终归位**（报告遗留#5）：同形确认为 T5，其对象 0x017B1EC0 语义未查。
6. **j_InputSystem::ProcessKeyboard(0x41CA30) 真语义**（报告遗留#6）：字节面（8 字段写+call 0x41C710）已验，与真 ProcessKeyboard 的关系未做语义定谳。
7. **T7 逐个三分（ILT/COMDAT/尾跳）**（报告遗留#1）：抽验 5 件形对，生成器归属未逐个 xref+布局复核。
8. **A 形 13B 与 C 形 17B 语义差**（报告遗留#8）未验。
9. **match/L1 实跑**：本复核与两报告同口径为只读取证，未跑 match 验证任何再生主张。
10. **「782 个相关符号」**（C1）：三种口径均无法复现，按未复验处理。
11. T5 胶水链的 `_atexit` 目标 0x553041 仅核名，未核其 CRT 归属/版本一致性。
12. PalScriptMgr.cpp:3135-3142 atexit 目标（IDA 名 `ConditionalCleanup`/`FindScript`）的真实身份（名不可信），未查。

---

*附：本复核全部 IDA 取证经 idapro MCP（session 278944bc）只读进行（get_bytes/py_eval/xrefs/name），导入表另经原始 PE 解析独立交叉；未修改 IDB/标注/管线/任何报告。字节证据均可按地址复验。*
