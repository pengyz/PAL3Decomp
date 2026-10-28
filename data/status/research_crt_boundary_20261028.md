# CRT/库函数识别与「游戏逻辑 vs 非游戏逻辑」边界调研（2026-10-28 取证版）

> 只读取证调研。唯一产物 = 本文件。证据工具：`mcp__idapro__*`（IDB `original/PAL3.exe.i64`，session 278944bc，PAL3.exe sha256 `1f4612d0…47f13`，5609 函数）+ /tmp 下 MSVC6 只读编译实验（`tools/compilers/msvc6.0` cl 12.00.8168 SP0 经 wine）+ `tools/vc6/Lib`（**SP5** 版库，见遗留未知 §6.4）COFF 归档解析。
> 每结论带地址/字节/实测输出；无实证处标「推测」。引用 L1/字节等同时带 match 三限定（截断比较 / 长度相等 / 重定位 4 字节 don't-care，见 CLAUDE.md「度量盲区」节）。

---

## 1. 结论摘要

### 1.1 边界定义（第一性判据）

**问一个函数的字节由什么决定**，边界就出来了：

| 类 | 定义（字节由什么决定） | 供给方式 | 是否源码重建 | 参与 match |
|---|---|---|---|---|
| **G 游戏逻辑** | 我们写的 C++ 源码 + MSVC6 + 同 flags | source_rebuild | ✅ 必须 | ✅ L1 目标 |
| **E 引擎静态簇** | gbEngine 数学库源码（或同版静态 lib）+ MSVC6 + 同 flags | source_rebuild / lib_relink | ✅（引擎源） | ✅ L1 目标 |
| **L1 库预编译-CRT** | libcmt.lib 里同一 .obj（链接期再供给） | lib_relink | ❌ 禁写 | ✅ 由同版 .lib 保证 |
| **L2 库预编译-STL** | libcpmt.lib 里同一 .obj | lib_relink | ❌ 禁写 | ✅ 同上 |
| **C 编译器合成** | 编译器对同 TU 布局+同 flags 的确定性再生（static-init 桩、deleting dtor、ILT、模板实例化、EH prolog…） | compiler_regenerated | ❌ 禁手写（再生即得） | ✅ 随 TU 编译再生成 |
| **I 导入跳板** | 链接器生成（jmp [IAT]） | import_table | ❌ | ✅ 链接器保证 |
| **K 链接器产物** | 链接器生成（ILT 5B jmp、COMDAT 折叠 alias） | linker_generated | ❌ | ⚠️ 依赖链接模式（/INCREMENTAL 等） |
| **? 待定** | 未定性 | — | — | — |

**关键论证（静态 CRT/STL 字节等同）**：MSVC6 静态链接的 CRT/STL 代码**不是源码问题，是工件问题**——我们链接的 `tools/vc6/Lib/LIBCMT.LIB` / `LIBCPMT.LIB` 里就是当年那份 .obj。实测（§2）：PAL3.exe 内 `_sprintf/_ftol/??3@YAXPAX@Z/?_Xlen@std/?_Xran@std/logic_error ctor` 与库 .obj 字节逐位比较，**全部差异位点落在 COFF 重定位操作数内**，按 match 三限定全部计 match（`__ftol` 39/39 零差异）。⇒ **同版库重链接即字节等同，无需重建源码**；STL 异常族（logic_error/length_error/out_of_range）同理，来自 `libcpmt.lib:string.obj`。

反向推论（WinMain 冤案的根因）：把「非游戏逻辑」的判据误用为「名字可疑/没人调」，会把 **G 类**塞进 skip 筐 ⇒ export 缺 decl ⇒ 函数整体失踪。**边界判据是「字节由什么决定」，不是「叫什么名字」「像不像 CRT」**。

### 1.2 裁决统计

skip_functions.json 共 1910 条（reason 分布实测）：

| reason（现值） | n | 真实归属（抽样实证后） |
|---|---|---|
| crt_runtime | 923 | **筐**：L1 真 CRT（0x55xxxx ~340）+ L2 STL（525-527 等）+ C 静态初始化桩（unknown_libname_287-524/528 共 186）+ E 引擎数学簇（sub_542xxx/Float_AlmostEqual）+ I/K 跳板（j_*、SingletonThunk）+ **G 冤户**（fn、PushMatrixStacks/PopMatrixStacks、?UIInitSystem、?UIDrawText×3、4 个 crt_sub、crt_sub_00541C40 等） |
| compiler_thunk | 217 | K/I（5B jmp alias/ILT；部分是 10B init+atexit 桩） |
| between_std_methods | 175 | **桶名无语义**：抽样 = G/E 真代码（sub_408010 214B thiscall 游戏逻辑）⇒ 待逐条重裁 |
| trivial_accessor | 125 | C（11B `mov eax,[g_src]; mov [g_dst],eax; retn` = 全局拷贝动态初始化） |
| compiler_generated_nop | 90 | ?（3B `retn N` 空函数体；空虚函数覆写 vs COMDAT 折叠残体未逐一定性） |
| compiler_generated_init | 65 | C（57B rdata+imm → 全局数组/结构初始化桩） |
| compiler_global_init_stub | 53 | C（15B `fld; fadd st,st; fstp g; retn` 浮点全局初始化桩） |
| compiler_float_init_stub | 51 | C（同上 15B 形） |
| crt_init | 42 | **混桶**：抽样见 G（sub_401070=AStar 寻路 552B、sub_4014B0=链表摘链）、G（$E68=CEffMgr）、C（compiler_init_005090A0）、K（sub_401860 5B jmp）⇒ 逐条重裁 |
| std_library | 10 | C-模板（`?_Tidy/?_Freeze/?_Eos@basic_string` 等 STL 头实例化） |
| 其余（std_library 小桶/seh_thunk/empty_stub/stl_internal/non_real/compiler_generated/compiler_scalar_dtor/trivial_global_stub/gbVFileSystem_external_class/crt_builtin/no_decomp） | 27 | crt_builtin=`_abort`=L1；seh_thunk= C；其余抽样待定性 |

IDA 侧佐证：`survey_binary` 报 library_functions=595（FLIRT 识别为库函数），与 0x55xxxx CRT 段 + 44B 桩簇（FLIRT 签名「Microsoft VisualC 2-14/net runtime」）吻合。

---

## 2. CRT/STL 字节等同实证

### 2.1 实验设计

1. **取原 exe 参照字节**：IDA 取 PAL3.exe 六个函数的完整字节（`__ftol` 0x553514/39B、`_sprintf` 0x553082/82B、`??3@YAXPAX@Z` 0x541D10/11B、`?_Xlen@std@@YAXXZ` 0x541D1B/90B、`?_Xran@std@@YAXXZ` 0x541F47/90B、`std_logic_error_ctor0/1` 0x541D75/100B、0x541E5C/93B）。
2. **编译小 TU**（/tmp/crttest/t.cpp，只读实验不动仓库）：调 `sprintf`（拉 `_sprintf`）、`(long)double/(int)float` 转换（拉 `_ftol`）、`std::string` 拼接（拉 `_Xlen/_Xran/logic_error` 族）、`operator delete`。编译 flags 对齐本仓：`/GX /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GR /MT`（cmake/MSVCSettings.cmake:64 实测）。
3. **端到端链接**：`LINK.EXE /SUBSYSTEM:CONSOLE … libcmt.lib libcpmt.lib oldnames.lib kernel32.lib` ⇒ t.exe 成功；t.map 证明符号来源：`__ftol ← libcmt:ftol.obj`、`_sprintf ← libcmt:sprintf.obj`、`??3@YAXPAX@Z ← libcmt:delete.obj`、`?_Xlen/?_Xran/logic_error 族 ← libcpmt:string.obj`。
4. **库 .obj 逐位比对**：自解析 COFF 归档（长名表解析）从 LIBCMT/LIBCPMT 抽出对应成员的函数字节+重定位表，与参照逐位 diff，检验「差异位点 ⊆ 重定位操作数（REL32/DIR32 各 4 字节）」——即 match 三限定的第 3 条。

### 2.2 输出摘录（实测）

```
__ftol                 libsize=39 diffs=0   outside_reloc=NONE   relocs=[]
_sprintf               libsize=82 diffs=4   outside_reloc=NONE   relocs=[('0x2a',20,'?'),('0x47',20,'?')]
??3@YAXPAX@Z           libsize=11 diffs=3   outside_reloc=NONE   relocs=[('0x5',20,'?')]
?_Xlen@std@@YAXXZ      libsize=90 diffs=30  outside_reloc=NONE   relocs=[('0x1',6,'??_7logic_error@std@@6B@'),('0x6',20,'.xdata$x'),('0x1a',20,…),('0x1f',6,'.rdata'),('0x25',20,'??1exception@@UAE@XZ'),('0x30',20,…),('0x40',20,'?what@logic_error…'),('0x48',6,'??_R4logic_error@std@@6B@')]
?_Xran@std@@YAXXZ      libsize=90 diffs=33  outside_reloc=NONE   (同型 8 处重定位)
```

（type 20=IMAGE_REL_I386_REL32（call rel32），type 6=IMAGE_REL_I386_DIR32（绝对地址：EH handler/串/vftable））

t.exe 侧比对（同参数）结论一致：`__ftol` 39/39 全同；`_sprintf` 差异恰在两个 `call rel32` 操作数（偏移 42,43/71,72）；`?_Xlen` 等 22-28 个差异位点全部位于 `mov eax,imm32`（EH 记录）/`push/mov imm32`（字符串、vftable 地址）/`call rel32` 的 4 字节操作数内。

**判定**：6/6 函数在 match 三限定下**字节等同** ⇒ 静态 CRT/STL 由 MSVC6 库链接期再供给，字节等同由「同一 .lib 同一 .obj」结构性保证；**不需要也不应该源码重建**。`std_logic_error_ctor0/1`、`std_length_error_ctor/std_out_of_range_ctor`（0x541F2F/0x542017，24B `call logic_error_ctor; mov [esi],vftable; retn 4`）与 libcpmt 的 `??0length_error/??0out_of_range` 家族同源（同型 forwarding ctor）——STL 异常族同判 L2。

**限定**（随数字走）：此为「库函数字节等同」验证；未验证 SP0-原版 lib 与现 SP5 lib 一致性（见 §6.4）；重定位字节 don't-care 属 match 既有语义。

---

## 3. 逐类裁决表

### 3.1 `unknown_libname_351-552`（任务指定抽查 ≥15；实抽 31+）

skip 表内 unknown_libname 共 210 条（287-552），任务所述 ~200 条（351-552，0x438FC0-0x55D348）实为 184 条。**按地址/形状分三群**：

**群 A（287-524 + 528，~186 条）：编译器合成的动态初始化/清理注册桩（C）** — 抽查 31 个（351/352/355/357/366/370/374/380/387/390/393/399/403/407/420/440/453/460/469/471/473/475/480/483/487/496/500/504/508/516/523/524）**字节全同**（44B，仅 call rel32 随地址变）：

```asm
438FC0  mov  cl, g_bStaticInitFlags      ; 共享 guard 0x189598E
438FC6  mov  al, 1
438FC8  test al, cl
438FCA  jnz  short loc_438FD4            ; 仅跳过 flag 更新
438FCC  or   cl, al
438FCE  mov  g_bStaticInitFlags, cl
438FD4: jmp  loc_438FE0
438FE0: push offset j_j_codecvt_base     ; 空 dtor 桩 0x401800（=retn）
438FE5  call _atexit                     ; 0x553041
438FEA  pop  ecx
438FEB  retn
```

证据链：①31 抽样全同；②guard 只有一个字节 0x189598E（370 处 xref = 185 函数×2）；③dtor 是空 `retn`（0x401800）；④每条被 0x5801xx-0x5809xx 指针表收编（`5801E0 -> 438FC0`…，.CRT$XCU 并入 .data 的动态初始化表），无直接代码调用者；⑤FLIRT 注释「Microsoft VisualC 2-14/net runtime」（unknown_libname_524 decompile 头实录）⇒ IDA 自己都认它是 MSVC 运行时系合成件。**不是 CRT 库函数、不是游戏逻辑**——是编译器为「static 对象/清理注册」编译期合成的 per-copy 桩。名字误挂实证：该簇上挂着 `?CheckCurRV@PlayerAtt@@QAEXXZ`（0x43A690，44B 同型）、`?_todo_52B9A0@ParticleVisNode`、`sub_530200`——即**类方法名被挂到初始化桩上**（见 §4.3 迁移项）。

**群 B（525-527，3 条，0x541E03/0x541EB9/0x541FA1，61B）：STL 异常族成员（L2）** — 落在 `?_Xlen@std`(0x541D1B)/`std_logic_error_ctor0/1`/`?_Xran@std`(0x541F47)/`std_length_error_ctor` 之间，与 libcpmt:string.obj 的 logic_error/length_error/out_of_range 成员（what/_Doraise/ctor）同族。

**群 C（529-552，24 条，0x5577E1-0x55D348）：真 CRT（L1）** — 全在 0x55xxxx CRT 段。抽 3 个：`unknown_libname_531`(0x55C5C0,279B) `fld; xor eax,0E000000h; test; fdivp; cmp byte_60B710[eax],0` 与 533(0x55CB76,19B) 调用 531 ⇒ **x87 FDIV 异常/精度辅助**（Pentium FDIV 修补系）；`unknown_libname_532`(0x55C6D7,**1183B**) `and eax,3Fh; switch 64 cases → fdiv/fdivr/int 6` ⇒ 浮点核心辅助。典型 MSVC6 CRT fp 支持代码。

### 3.2 `sub_542xxx` 微跳板簇（0x542017-0x543Axx，110 函数全量形状分类）

| 形状（首字节） | n | 裁决 | 证据 |
|---|---|---|---|
| `FF 25 xx xx xx xx`（jmp [ptr]，6B） | ~35 | **I/K**（导入/表跳板） | `j_D3DXVec3TransformCoord_0`(0x542533)→`jmp [0x6090C4]`（**dispatch 表**项，非 IAT！见下）；`?EnableShadow@gbGeomNode`(0x542072) 等 WeatherEffectNode/ParticleVisNode/SceneVisNode adjthunk×20+ 也是 jmp [0x56A2xx]=真 IAT（GBENGINE 导入） |
| `6A 01 E8 ..`（push 1; call）13B | 8 | **C**（scalar deleting destructor thunk） | `crt_sub_005424BA`: `push 1; call CRT_scalar_delete; jmp [0x6090A8]` |
| `55 8B EC 6A 01 E8 ..` 17B | 12 | **C**（同上 stdcall 形） | `crt_sub_005424CD` 等 |
| 42/46/47/28B `6A 01 E8` + 转发 | 6 | **C+E**（dtor 部分 + 转发 dispatch） | `sub_5422B7`(42B)：`push 1; call 0x546F41(dispatch 一次性初始化); call [0x6090EC]`（**dispatch 包装**） |
| 5B `jmp X` | 2 | **K**（alias/ILT） | `nullsub_96`(0x542071)=`retn`；相邻 jmp |
| 真代码 67-927B | ~45 | **E 引擎数学簇** | `sub_542169`=F32→F16 打包（`cmp edx,47FFEFFFh` 序列）、`sub_542205`=F16→F32、`sub_5422E1/542399/542563/54263B/542C93`=4 控制点三次插值（Bezier/Hermite）、`sub_542477/54273B/542DB5`=lerp、`Float_AlmostEqual`(0x54212C,48B)、`sub_543098/54335B`(各 566B 同尺寸双实现) |

**dispatch 机制**（新发现，超出普查范围）：0x546F41（IDB 误名 `CRT_scalar_delete`，257B）是 **73 入口函数指针表的一次性初始化**（`rep movsd` 0x6091D0 默认表 → 0x6090A8 活动表，sentinel `dword_6092F8=0xFFFF`）；各包装 `push 1; call 0x546F41` 做懒初始化后 `call [tbl+N]`。默认表 73 项实测全指向 0x542xxx-0x546xxx 标量实现；`__m64::_static_*`/`__m128::_static_*`（86 个，0x54FD78-0x552xxx）是 **MMX/SSE 实现**（`__m64::_static_551400`：count<4 走 `sub_542169` 标量路径，≥4 走 `movq mm0…`，`and esp,0FFFFFFF8h` 对栈 8 对齐）。

**簇归属实证**：F16 打包的 22 字节特征序列 `C1EE10 81E2FFFFFF7F 81E600800000 81FAFFEFFF47` 全盘搜索——**PAL3.exe@file 0x142169(=VA 0x542169)、PAL3A.exe@0x12E165、gbengine.dll@0x46C4F 各恰 1 份**，Mss32.dll 0 份 ⇒ 该数学簇是 **gbEngine 引擎数学库**（引擎 DLL 与 exe 各编一份）。裁决 **E**：需引擎源码/同版静态库编译再现，不是手写游戏业务，也不是 MSVC CRT/STL。

### 3.3 指名条目裁决

| 条目 | 地址 | 裁决 | 证据 |
|---|---|---|---|
| `compiler_init_005090A0` | 0x5090A0 | **C**（全局动态初始化桩）——**不是游戏函数** | 57B 写常量 119/314/510/707→`g_StageRoleData.m_nEffParamBase4+2..5`；与 65 个 `compiler_generated_init` 同型（如 `compiler_init_00509230` 写 `g_StageRoleData+5C..68`=rdata+0x52）；xref 0x56FF88=初始化表指针。**名字是误挂**：所谓 caller `?PreLoadEffGroup@CCBStageEffect`@0x509090 实为 5B `jmp 0x5090A0` 跳板，0x509080 `?GetLinkerIndex@CCBStageEffect` 实为 15B `fld; fadd st,st; fstp g_StageRoleData.m_nEffParamBase0` 浮点初始化桩——桩/跳板上挂了类方法名 |
| `$E68` | 0x4CEAF0 | **G 游戏逻辑** | 104B，`?CreateEffect@CEffMgr@@QAEHHHHHH@Z` 直调（0x4CDD34）；2048 槽效果表遍历（this+587×5dwords）、调虚函数、`--this[10823]` 计数——CEffMgr 效果槽清理。`$E*` 名是共享尾块/自动名，非 CRT |
| `_DllMain@12_*` | 0x47E536 / 0x5329BE | **G 游戏逻辑**（模块接口桩） | 8B `mov eax,1; retn 0Ch`（stdcall DllMain 形）；caller 分别是 `?HandleMsgDLL@UITitle_YXXX@@QAEHHKH@Z`(0x47E4E0)、`?HandleMsgDLL@RoleSystem@@QAEHHKH@Z` —— 游戏的「模块消息/DllMain 模拟」体系。exe 无 DLL 语义，非 CRT |
| `start` | 0x55507C | **L1 真 CRT**（WinMainCRTStartup） | 246B：`GetVersion→_heap_init→_ioinit→GetCommandLineA→__crtGetEnvironmentStringsA→_setargv→_setenvp→_cinit→GetStartupInfoA→_wincmdln→WinMain→exit`，入口点（PE entry）。链接期 libcmt 供给，skip 正确（reason 应改 `lib_relink_ok`） |
| `sub_542xxx` 微跳板 | 见 §3.2 | I/K/C/E 四分 | 见上 |
| `crt_sub_00541490` | 0x541490 | **K**（5B `jmp crt_sub_005415C0`，alias/ILT）→ 其目标 0x5415C0 为 G | caller `InitUIQuadManagerSingleton`(0x541635) |
| `crt_sub_005414A0` | 0x5414A0 | **G 冤户**（UICursor 装载） | 235B SEH prolog+`"ui\\cursor\\jt.tga"\\sb_s.tga\\sb_n.tga`+`OpenBaseFile::OpenBaseFile`，thiscall（`mov ebp,ecx`）；caller `sub_404800` |
| `crt_sub_00541860` | 0x541860 | **G 冤户**（CD 盘扫描） | 118B：`sprintf("%c:\\\\", 'A'..'Z')+GetDriveTypeA==5(DRIVE_CDROM)`；caller `WinMain`(0x5419A7) |
| `crt_sub_00541C40` | 0x541C40 | **G 冤户**（注册表读） | 114B：`RegOpenKeyExA(HKLM=0x80000002,…)+RegQueryValueEx`；caller `WinMain`(0x54199B) |
| `fn` | — | **G**（WinMain 传 `SetWindowsHookExA` 的钩子回调 + ScriptVM/PAL_GDB 调用，21 引用，普查 §二） | 普查证据 |
| `PushMatrixStacks`/`PopMatrixStacks` | — | **G/E**（渲染栈 helper，11+11 引用）；现 skip 是**双定义 workaround**（source 自述「挡 C2556 ×144」），不是 CRT 判断 | 普查 §二 |
| `j_D3DXVec3TransformCoord_0` | 0x542533 | **K**（jmp [dispatch 表 0x6090C4]）——sg_emission_control overlay 注释债根因 | code caller 含 `?_todo_004BA800@sg_emission_control`、`sub_4B9330` |
| `DirectInput8Create` | — | **I**（DINPUT8 导入跳板） | 普查 §二 |
| `SingletonThunk_*` ×7 | — | **C**（`mov ecx,[global]; jmp target` 单例跳板，编译器/链接器产物） | 普查 §二 |
| `__m64/__m128::_static_*` ×86 | 0x54FD78-0x552xxx | **E**（MMX/SSE 实现，dispatch 簇成员） | §3.2 |
| `std_logic_error_ctor*`/`?_Xlen/?_Xran` | 0x541Dxx-0x5420xx | **L2**（libcpmt:string.obj） | §2 字节实证 |
| `Float_AlmostEqual` | 0x54212C | **E**（48B 在数学簇内），游戏可达 1 处 ⇒ 需 unskip+建 decl | 普查 §一 + §3.2 |
| `?UIInitSystem@@YAXXZ`、`?UIDrawText@@…`×3 | — | **G** | 普查 §二 |
| `?_Tidy/?_Eos@basic_string` 等 10 条 | 0x402FB0 等 | **C-模板**（STL 头在 TU 内实例化；`?_Eos` 17B `mov [ecx+8],eax; mov [ecx+4],ecx; mov byte [ecx+eax],0; retn 4` 实录） | §3.1 抽样 |
| `compiler_float_init_stub`（51）/`compiler_global_init_stub`（53） | 0x411780 等 | **C**（15B `fld ds:flt_x; fadd st,st; fstp g; retn` 浮点全局初始化桩） | 实录 |
| `compiler_generated_init`（65） | 0x40FDA0 等 | **C**（57B rdata+imm→全局数组初始化桩） | 实录 |
| `trivial_accessor`（125） | 0x401850 等 | **C**（11B 全局拷贝初始化桩；`accessor_00404470`: `mov eax,flt_56A65C; mov g_nGameTime,eax; retn`） | 实录 |
| `compiler_thunk`（217） | 0x401840 等 | **K**（5B `jmp X`）+ 少量 10B init+atexit 桩（C） | `thunk_00401BB0`(10B): `call ?InitVFileSystem@PAL3; jmp loc; push offset sub_401BE0; call _atexit` |
| `between_std_methods`（175） | 0x408010 等 | **桶名无效，待重裁**；抽样=**G**（sub_408010 214B thiscall `[esi+0C00h]` 游戏循环逻辑） | 实录 |
| `crt_init`（42） | 混 | **逐条重裁**：sub_401070=**G**（552B A* 寻路 `AStarPathFinder::Reset`）、sub_4014B0=**G**（链表摘链）、$E68=G、compiler_init_005090A0=C、sub_401860=K | 实录 |

---

## 4. 标注 schema 草案 + 迁移清单

### 4.1 现状问题（拆理由）

现行 `reason` 单字段混装**三种语义**：①归属判断（`crt_runtime`）②动作性 workaround（`between_std_methods` 挡双定义、批0「skip 挡 C2556 ×144」）③待查（`no_decomp: …`长文本）。导致：无法机器校验「G 类必有 decl」「C 类必无 decl」、无法统计覆盖率、WinMain 冤案无闸可拦。

### 4.2 schema 草案（三轴分离：归属 / 供给 / 动作）

```jsonc
// data/annotations/skip_functions.json 条目升级形（新增字段向后兼容，reason 暂留作镜像）
"0x00541C40": {
  "name": "PAL3_ReadRegistryStr",        // 语义名；不确定保 _todo_/原 IDA 名
  "boundary": "game",                    // game | engine_static | lib_crt | lib_stl
                                         // | compiler_synthesized | import_thunk | linker_artifact | unknown
  "supply": "source_rebuild",            // source_rebuild | lib_relink | compiler_regenerated
                                         // | linker_generated | import_table
  "skip": true,                          // 体生成开关（与分类解耦）
  "skip_reason": "awaiting_signature",   // 单一语义枚举：
                                         // lib_relink_ok          —— 库供给，无需源码
                                         // compiler_regenerated   —— 合成件，编译再生，禁手写
                                         // linker_generated       —— 链接器产物
                                         // dual_def_workaround    —— 双定义 workaround（如实记）
                                         // dup_decl_elsewhere     —— 声明已收编 structs/methods（declaration_only）
                                         // awaiting_signature     —— 待查（唯一允许的"待定"）
  "evidence": ["ida:xrefs:WinMain@0x54199B", "ida:disasm:RegOpenKeyExA@0x541C59"],
  "confidence": "A",                     // A=指令级证据 / B=形状+簇证据 / C=推断
  "reviewed": "2026-10-28"
}
```

配套校验（check_annotations 新增，非风格规范而是矛盾检测）：
- `boundary=game|engine_static` ⇒ `skip=false` 或 `skip_reason=dual_def_workaround|awaiting_signature|dup_decl_elsewhere`（G/E 禁以 `lib_relink_ok` 静默跳过）；
- `boundary=lib_crt|lib_stl` ⇒ `skip_reason=lib_relink_ok` 且 functions.json **不得**有函数体 decl（允许可选签名 decl）；
- `boundary=compiler_synthesized|linker_artifact|import_thunk` ⇒ 不得有 decl，`supply≠source_rebuild`；
- `skip_reason` 不再允许承载「归属」信息（迁移期 reason 字段仅镜像打印）。

### 4.3 迁移清单（改判条目）

1. **crt_runtime 923 条拆桶**：
   - 186×群 A 桩（unknown_libname_287-524/528）→ `compiler_synthesized / compiler_regenerated`，改名建议 `staticinit_atexit_<addr>`（或保留 IDA 名+boundary 注记）；
   - unknown_libname_525-527 → `lib_stl`；unknown_libname_529-552 → `lib_crt`；
   - sub_542xxx/crt_sub_00542xxx：按 §3.2 形状表分流（E / import_thunk / compiler_synthesized(deleting dtor) / linker_artifact）；
   - **G 冤户**（立即可办，普查 §三1）：`crt_sub_00541490/005414A0/00541860/00541C40` 复核无双源声明后 unskip（0x541490 判 linker_artifact，目标 0x5415C0 归 G）；`fn`→正名 `WinHookProc`；`PushMatrixStacks/PopMatrixStacks`→`dual_def_workaround`（摘掉 crt_runtime 伪装）；`?UIInitSystem@@YAXXZ`、`?UIDrawText`×3、`Float_AlmostEqual`（E，unskip+decl）；
   - `j_D3DXVec3TransformCoord_0`→`linker_artifact`（dispatch 跳板）——解决后回收 sg_emission_control 的 `[overlay-fix]` 注释（普查 §三3）；`DirectInput8Create`→`import_thunk`；`SingletonThunk_*`→`compiler_synthesized`。
2. **`crt_init` 42 条逐条重裁**（抽样已见 A*、链表、CEffMgr 等 G 类）。
3. **`between_std_methods` 175 条重裁**（桶名无语义，抽样=G）。
4. **名字误挂批量复核**（新发现）：凡 44B/15B/11B/5B 形状且特征为 guard+atexit / `fld;fadd;fstp` / `mov eax,[g];mov [g],eax` / `jmp X` 的函数上挂着 `?Method@Class@@` 名（实录：`?CheckCurRV@PlayerAtt@@`@0x43A690、`?GetLinkerIndex@CCBStageEffect@@`@0x509080、`?PreLoadEffGroup@CCBStageEffect@@`@0x509090、`?_todo_52B9A0@ParticleVisNode`@0x52B9A0）⇒ 逐个把名字迁回真实函数（判据：函数体含该类成员访问者才配该名，遵守「禁止仅凭 signature this」纪律）。
5. `compiler_init_005090A0` 的 reason `crt_init`→`compiler_regenerated`（与其他 compiler_init 65 条统一）。
6. **风险闸保留**（普查 §三5）：unskip 必须先查 functions.json/methods 同址声明防 C2556/2373 双定义（×144 实录）；逐个来不批量。

---

## 5. 完备性 spec（分类完备判据 + 防回归）

### 5.1 完备判据（"边界分类已完备"当且仅当）

1. **全集覆盖**：IDB 全部 5611 个 .text 函数（survey 5609 + 复核 2 计差属工具口径）每条有 `boundary ∈ 8 类` 且 `confidence ∈ {A,B,C}`；**未分类清单 = 0**（boundary=unknown 的产出列表必须为空才可宣称完备）。
2. **覆盖率度量**：`classified_total / func_total = 100%`；分桶计数落 `data/status/crt_boundary_census.json`（含每桶 n、抽查样本数、证据等级分布）。**双闭环**：`boundary=game|engine_static` 的每条必须在 functions.json/structs methods 有 decl（decl 存在率=100%）；`boundary=lib_*|compiler_*|import_*` 必须无函数体 decl（违例=0）。
3. **互斥一致性**：reason↔(boundary,supply,skip_reason) 兼容矩阵由 check_annotations 校验（§4.2 配套校验全部为 0 违例）。
4. **可达性反向扫描**（普查方法固化）：`asm/pal3/decomp/*.json` 引用扫描 ⇒ `boundary ∈ {lib_crt, lib_stl, compiler_synthesized}` 且**被游戏 decomp 直调**的条目输出红旗清单（WinMain 冤案同型）；红旗必须逐条给出「库/编译器确实供给该符号」的证据或改判。
5. **字节实证抽检**：每个 `lib_*` 家族 ≥1 函数留存「实证指纹」（库成员名+函数字节哈希+重定位表+三限定声明），如 §2 格式；新家族入册时补测。
6. **形状分类器校验**：§3.2 形状表（44B guard 桩 / 13-17B deleting dtor / 6B jmp[ptr] / 5B jmp / 15B float-init / 11B copy-init / 57B array-init）对未知条目自动预判，与人工裁决不一致率入统计。

### 5.2 防回归（新符号自动入册流程）

```
export 发现新 unnamed/新地址函数
  → 形状分类器（§5.1-6）预标 boundary+confidence=C
  → 生成 pending_crt_boundary 条目（skip 默认 true, skip_reason=awaiting_signature）
  → 人工复核升级 confidence（B/A）或改判
  → check_annotations 兼容矩阵 + 双闭环断言
  → 入册落盘（crt_boundary_census.json 计数+1）
```

- `pipeline/cli.py status` 增打「未分类清单」与「G/E 无 decl 清单」两列；`match` 前断言两清单为 0（不满足 ⇒ 显式失败，防再发 WinMain 型失踪）；
- 新增 skip 条目强制带 `evidence` 字段（无证据不得入库，对齐 annotation「每一处修改必须有二进制直接证据」红线）；
- unskip 沿用普查 §三5 风险闸（先查双源声明，逐个来）；
- 年度/大版本跑一次 §5.1 全套（覆盖=100%、红旗=0、抽检指纹齐）。

---

## 6. 遗留未知

1. **44B guard 桩的源级触发形态未定**：185 份全同拷贝共享一个 guard 字节（0x189598E）与一个空 dtor（0x401800），且 atexit 在 guard 分支之外**无条件注册**——与 MSVC6 常规「static 对象 guard 包住 atexit+ctor」形态不符。本仓 MSVC6 实验只重现了 **12B 无 guard 形**（`push dtor; call _atexit; pop ecx; retn`，/tmp/crttest/s.obj `_$E4` + `.CRT$XCU` 槽 `_$S5`）与 44B 形的「12B 部分」一致。**推测**：inline 函数+extern 共享 guard（大静态库逐 .obj 编译、无 /Gy COMDAT 折叠）或模板逐实例化；待做「inline+static、模板 static、多 TU」组合实验定谳。
2. **0x5420xx-0x552xxx 数学簇的源码缺口**：已定归属=gbEngine 数学库（gbengine.dll/PAL3.exe/PAL3A.exe 三处同序列），但 `gbengine/src`（59 文件，含 gbMath_extra.cpp/BEZIER.cpp）**未见 F16/spline/MMX-dispatch 实现** ⇒ 重建源码缺失（引擎重建进度外的源），字节重现路径（引擎源重编 vs 静态 lib 链接）未定。
3. **dispatch 双态机制未完全逆明**：0x546F41（误名 CRT_scalar_delete）`Type==0` 全量拷表 / `Type!=0` 懒初始化（sentinel 0xFFFF）两分支语义、以及 `push 0` 调用点是否存在（谁做 MMX/标量表切换）未查全；`??3@YAXPAX@Z`(operator delete) 出现在其首行的原因（疑误名/共享尾）未定。
4. **库版本口径**：编译器=SP0（cl 12.00.8168）而 `tools/vc6/Lib`=**SP5**（toolchain-vc6.cmake:20 自述「lib files are compatible」）；本次实验全同（__ftol 39/39）说明 CRT 核心函数稳定，但不等于「SP5 lib ≡ 原版 SP0-SP3 lib」。建议把「lib 版本=工件版本」写入约束并补 SP0 lib 对照（若可得）。
5. **两桶逐条重裁未做**：`crt_init`(42) 与 `between_std_methods`(175) 仅抽样（已证含 G 类）；`compiler_generated_nop` 90 条 `retn N` 空体未逐一定性（源码空函数 vs COMDAT 折叠残体）。
6. **导出失踪面未全扫**：WinMain 冤案「skip ⇒ export 缺 decl ⇒ 函数整体失踪」的同型风险，除普查的可达性扫描外，尚无「exe 全函数 ↔ functions.json decl 全集对账」的例行闸（§5.1-2 双闭环是本次提出的方案，未实现）。
7. **PAL3A.exe 对照未做**（本次仅特征序列抽查 1 份命中 0x12E165）：PAL3A 的 PDB/差异可反哺命名，但按红线只能作参考。

---

### 附：本次实证速查索引

| 结论 | 证据位置 |
|---|---|
| CRT/STL 字节等同 | §2：/tmp/crttest/{t.cpp,cmp.py,final_cmp.py} 实测输出；lib 成员 `libcmt:{ftol,sprintf,delete}.obj`、`libcpmt:string.obj` |
| 44B 桩 31 抽查全同 | §3.1：IDA py_eval 批量反汇编输出（438FC0…541750） |
| 数学簇归属 gbEngine | §3.2：特征序列 `C1EE10 81E2FFFFFF7F 81E600800000 81FAFFEFFF47` 三文件各 1 命中 |
| dispatch 73 入口表 | §3.2：0x6091D0 默认表 73 项 dump；0x546F41 反编译 |
| 冤户 4 条=G | §3.3：0x5414A0(UICursor)/0x541860(CD)/0x541C40(registry) 反编译+caller |
| start=CRT 启动 | §3.3：0x55507C 反编译（WinMainCRTStartup 序列） |
| 名字误挂 | §3.3/§4.3：0x43A690、0x509080、0x509090 实录 |

---

## 【勘误 2026-10-28 · DX 对抗复核】（review_dx_static_boundary_20261028.md）

- :113/:115 将 `push 1; call` 13B 桩标「scalar deleting destructor thunk」**误**——call 目标是 `_D3DXCpuOptimizations`，正名应为 **「PSGP 惰性初始化桩」**（D3DX9 调度面）。sub_542xxx 簇归属 D3DX9（非 gbEngine）已在正篇 D1 勘定。
