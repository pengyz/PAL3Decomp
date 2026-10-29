# Plan Task 2 独立对抗复核 — 三 G 冤户 unskip（spec #3）+ 0x541490 裁决改判

- **复核对象**：commit `f7b4faa96`（HEAD；`git show HEAD` 三件：functions.json +3 条 / skip_functions.json −3 条 / tests/test_crt_sub_unskip.py 新增）
- **复核方法**：不信任自述，只信实测。二进制真相双通道：①原始字节（PE 直读 + capstone 全量反汇编，.text RawPtr==VA 1:1 映射已验）②IDA MCP（idb_open `original/PAL3.exe.i64` session dca84168，`get_bytes` 二次确认 + `xrefs_to` + `lookup_funcs`，用完 `save=false` 关闭）。生成树实效面读 `pal3/src/free_functions.{h,cpp}` + `asm/pal3/decomp/*.json`（loop 自产件，mtime 21:49-21:50 晚于 annotation 21:45 = 新鲜）。机制面读 `pipeline/gen/data.py` `free_sig_decl` + `pipeline/check_annotations.py:739-780`。取证前 `ps` 核 R14（loop 21:46-21:53 持 IDB 期间只做文件级取证，loop 结束后才开 IDB）。
- **复核时间**：2026-10-28
- **一句话结论**：**ACCEPT-WITH-FIXES** —— 三户身份 A 级全部成立（unskip 方向对、名实对、调用面引证逐字对），但 **0x541C40 签名 `int __cdecl()` 是错的（真身 3 参）＝SetBlend 型误登红线已触发并已实锤进生成代码**（P1 必修）；0x5414A0 的 thiscall→cdecl 降级是同族地雷（P2）；0x541490「留 skip」处置正确但「linker_artifact A 级」裁决理由降级（P3）。

---

## 总裁定：ACCEPT-WITH-FIXES

核心交付（三 G 冤户出 skip + 补 decl + 名实钉立）经二进制逐条实测**成立**：三个函数全部是游戏侧真代码（UICursor 装载 / CD 盘扫描 / 注册表读），unskip 正确、名字语义正确、调用面引证（sub_404800 / WinMain@0x5419A7 / WinMain@0x54199B）**逐字精确**。0x541490 裁决改判「留 skip」的**处置**也正确（唯一消费方是编译器合成 atexit 桩，无源码消费面）。但签名层有一个已实锤的正确性缺陷（P1：0x541C40 参数个数误登，生成树里 WinMain 已按 0 参调用⇒静默坏码+字节必失配），这正是 task 自设红线「SetBlend 型误登=静默坏码」。**P1 修完 + P2 挂账后方可结项**。

---

## 逐项 verdict

### 1. 三户身份复验（IDA get_bytes 二次确认） — **3/3 CONFIRMED**

| 地址 | claim | 真身实测（双通道） | IDA size | verdict |
|---|---|---|---|---|
| 0x5414A0 | UICursor 装载：235B SEH + "ui\cursor\jt.tga" + OpenBaseFile，thiscall `mov ebp,ecx`，caller sub_404800 | SEH prolog 字节 `6A FF 68 38 8F 56 00 64 A1 00 00 00 00 50 64 89…`（push -1; push 0x568F38 scope; fs:[0] 挂链）✓；三串 0x608F94/0x608F80/0x608F6C = `"ui\cursor\jt.tga"`/`"ui\cursor\sb_s.tga"`/`"ui\cursor\sb_n.tga"` ✓；`mov ebp,ecx` ✓（thiscall）；尾 `83 C4 20 C3`（add esp,0x20; **plain ret** ⇒ 无栈参）✓；本地对象 ctor/dtor 调 0x401F50/0x401F90 + SEH scope `[esp+2C]=0/-1` ✓ | 0xEB=235B ✓ | **CONFIRMED** |
| 0x541860 | CD 盘扫描：118B sprintf %c:\\ + GetDriveTypeA==5，caller WinMain@0x5419A7 | `mov bl,0x41`('A')→`cmp bl,0x5A`('Z') 循环 ✓；sprintf 格式 0x608FC0 = `"%c:\\"` ✓，call 0x553082=_sprintf（与 research §2 同址）✓；`mov esi,[0x56A040]`（GetDriveTypeA IAT）`call esi` `cmp eax,5`（DRIVE_CDROM）✓；命中后 rep movsd/movsb 拷入全局 0x1894970（=生成码 `Data`）✓；尾 `83 C4 0C C3` ⇒ 0 栈参 ✓ | 0x76=118B ✓ | **CONFIRMED** |
| 0x541C40 | 注册表读：114B RegOpenKeyExA HKLM + RegQueryValueEx，caller WinMain@0x54199B | `call [0x56A008]`=RegOpenKeyExA，push 序 `0x80000002`(HKLM)/0/0x20019(KEY_READ) ✓；`call [0x56A014]`=RegQueryValueExA（lpcbData=0x144=324、lpType=1=REG_SZ）✓；`call [0x56A010]`=RegCloseKey ✓；al=1/0 返回 ✓ | 0x72=114B ✓ | **CONFIRMED**（身份✓；但签名形错——见 §3 P1） |

- **调用面引证逐字核**（xref 双通道一致，各恰 1 处）：0x5414A0←0x4049C3（sub_404800 内，`call 0x5415F0`（单例 getter）`mov ecx,eax` `call 0x5414A0`＝**thiscall、零栈参** ✓）；0x541860←0x5419A7（WinMain=0x541900，`call 0x541860` 前**零 push** ✓）；0x541C40←0x54199B（WinMain，**3 push：0x1894970=&Data、0x609028="CDriver"、0x609010="software\softstar\pal3" + `add esp,0xc` + `cmp al,bl`** ✗✗ ——与 `int __cdecl()` 冲突，见 P1）。
- **名字语义**：3/3 合格——`PAL3_LoadUICursor`（3 游标纹理装载 ✓）、`PAL3_FindCDRomDrive`（A-Z 扫 DRIVE_CDROM 写 `Data` ✓）、`PAL3_ReadRegistryStr`（读 HKLM\software\softstar\pal3\CDriver REG_SZ ✓，「草稿钉名」自述诚实）。functions.json 名字唯一性实测 1/1/1 ✓，无 `_todo_`/伪语义形态 ✓。

### 2. 0x541490 裁决复核（5B jmp 别名=linker_artifact 留 skip） — **处置成立 / 理由降级（P3）**

- **字节面**：IDA get_bytes `E9 2B 01 00 00` = `jmp 0x5415C0`，恰 5B（size 0x5）✓ 纯尾转发形。
- **引用面**（全文件 4 字节绝对引用扫描 + E8/E9 相对扫描 + IDA xrefs_to 三重一致）：**全二进制恰 1 处引用** = 0x541635 `jmp 0x541490`，所在函数 0x541630（10B，IDA 名 `InitUIQuadManagerSingleton`，实为 **atexit 清理桩**：`mov ecx,0x1894D90; jmp 0x541490`，由单例 getter 0x5415F0 `push 0x541630; call _atexit(0x553041)` 注册）。链 = atexit 桩→别名→0x5415C0（真身 41B：循环释放 this+0x10/14/18 三个 gbTexture，即 LoadUICursor 写入的同一组槽）。
- **「linker_artifact」不成立于 A 级**：5B `jmp` 形**只证明「纯转发」，证不出「链接器生成」**。三假说同形：①ILT/COMDAT 折叠别名（K）②源码级转发函数 `f(){g();}` 尾调用（G）③编译器尾跳 thunk。反证 ILT：0x5415C0 被 0x406251 **直接 `call`**，而别名仅被 atexit 桩尾跳——ILT/ICF 语义下所有引用应统一走别名/统一改写，混合直接+别名引用不符；且全文件 **0 处** 0x541490 绝对引用（无 vtable 槽）。⇒ 裁决理由应从「A 级 linker_artifact」降为「K/G-forwarder 未定谳（形状 B 级）」。
- **但「留 skip」处置本身成立**，换一个更硬的理由：**唯一消费方 0x541630 是编译器合成 atexit 桩（C 类，supply=compiler_regenerated，永不源码重建）**，重建面无人需要 0x541490 的符号；其行为 100% 被 0x5415C0 承载且 0x5415C0 保留 decl（functions.json declaration_only）✓。无论 K 还是 G-forwarder，skip 都不产生 WinMain 冤案型失踪（无 G 侧调用面）。**结论：keep skip ✓；label 改措辞 + 测试名/docstring 的 "linker_artifact" 字样降级**（测试断言的只是「留 skip」这一处置，label 是搭车断言）。
- 附注：research_crt_boundary §3.3 的「caller InitUIQuadManagerSingleton(0x541635)」措辞不精确——0x541635 是 10B 桩内 jmp 指令位，且该 IDB 名（误挂，实为清理桩非 init）被引证传播；不影响处置。

### 3. 签名保守形与真身兼容性（调用面参数数） — **1/3 合格；P1 + P2**

| 地址 | functions.json 签名 | 真身实测（参数/约定） | 兼容性 |
|---|---|---|---|
| 0x5414A0 | `void __thiscall(this)` | thiscall（ecx→ebp），**零显式栈参**，plain ret；调用面 `mov ecx,eax; call` 零 push | **参数个数 ✓**；但约定**在发射层丢失**（P2） |
| 0x541860 | `int __cdecl()` | **零参**（帧内仅局部，无 [esp+N] 入参读取；尾 `add esp,0xc; ret` 清局部）；调用面零 push；返回值被调用方忽略（eax=长度/末次 GetDriveTypeA 残值，保守 int 不越权） | **✓ 兼容** |
| 0x541C40 | `int __cdecl()` | **3 参**：`mov ecx,[esp+4]`（IDB get_bytes 首指令 `8B 4C 24 04`）＝arg1 lpSubKey；arg2 lpValueName；arg3 lpData（失败路径 `mov [edx],0` 写 *arg3）；cdecl（plain ret，调用方 `add esp,0xc` 清栈） | **✗✗ 不兼容（P1）** |

- **P1 实锤链**（不是潜在，是已落盘）：`int __cdecl()` → apply→export 透传（decomp JSON `signature=int __cdecl()`，把 3 入参渲成 `[ebp+4/8/C]` **BYREF 未初始化局部**）→ codegen 发射 `int PAL3_ReadRegistryStr(void);`（free_functions.h:219）→ **生成 WinMain 按 0 参调用**：free_functions.cpp:26967-26968 `if ( !(unsigned __int8)PAL3_ReadRegistryStr() ) PAL3_FindCDRomDrive();`——对照真身缺 **3×push + `add esp,0xc`** ⇒ ①注册表读拿垃圾栈当参数（静默坏码）②调用面字节必失配（L1 永黑）。编译期零报错（声明/调用同形）＝**正是「SetBlend 型误登」红线的静默形态**。修法（任一）：签名改 3 参形 `int __cdecl(const char *pszSubKey, const char *pszValueName, char *pszOutBuf)`（A 级证据已齐：调用面 3 push+add esp,0xc + 体首指令读 [esp+4] + 体读 [esp+8]/[esp+0xC]），或按 check_annotations 认可的保守收编形 `int __cdecl(...)`（变参形，事实 0 断言）；改后须 apply→export→codegen 复跑让 decomp 形随 IDB 原型翻正。
- **P2**（同族，当下潜伏）：`void __thiscall(this)` 经 `free_sig_decl`（pipeline/gen/data.py:23-42）**降级为 cdecl** `void PAL3_LoadUICursor(_BYTE *_this)`（free_functions.h:218 实发）——MSVC6 禁自由函数 __thiscall 是事实（0x5415C0 条目 source_note 有同款记载），但降级产物是 **ABI 错载体**：真身 this 入 **ecx**、零栈参，cdecl 形调用面将是 `push _this; call; add esp,4` ⇒ this 走栈、ecx=垃圾 ⇒ 静默坏码。data.py:17 自己的结论就是正解：「__fastcall 是唯一 ABI 等价自由形（ecx 传首参）」——建议 0x5414A0 改 `void __fastcall(_BYTE *_this)` 载体形（1 参 fastcall 纯 ecx 传、callee plain ret，字节级等价），或像 0x5415C0 一样显式挂「ECX vs 栈传 A/B 对拍」账。当下潜伏（唯一 caller sub_404800 尚未重建、无生成调用面），但属结构性地雷。
- 附（P6 相关面，非本 diff）：新生成的 PAL3_LoadUICursor 体尾部已把同款错形烙进去——`crt_sub_00541590();`（free_functions.cpp:26869）零参调用，而真身是 `push 0; mov ecx,ebp; call 0x541590`（thiscall+1 栈参）；0x541590 现有 decl `int __cdecl()` 同族误登（pre-existing）。unskip 使这个错从「无体」变成「有体」，建议随 P1/P2 一并列修或挂账。

### 4. 双源面 + unskip 后定义体生成路径 — **双源 ✓ 零；生成路径 ✓ 自产闭环；残留 2 个面（P4/P5）**

- **双源实测 ✓**：`grep` data/annotations/structs/ 对 4 地址 + 3 名 = **0 命中**；functions.json 名唯一 1/1/1 ✓；check_annotations:739-780 的双注闸（skip∩(methods∪functions)，declaration_only 豁免）对三户无旗 ✓——commit 自述「structs 零双源」成立。
- **但有两个残留面**：
  - **P5（闸缺口）**：双注闸只覆盖 **skip∩(methods∪functions)**，不覆盖 **functions.json ∩ structs methods** 的重叠（check_annotations.py:739-780 实测无此轴）；测试也不锁「三地址不在 structs methods」。今日零双源靠的是人工 grep（Batch-0 前置），无自动闸。
  - **归属预告**（双源未来风险）：0x5414A0 的体访问 this+0x10/0x14/0x18（写 3 个 gbTexture*）+ this+0x1D（分支 flag）与 `data/annotations/structs/UICursor.json` 的 `m_tex: gbTexture*[3]@16`、`m_bSoftMode@29` **逐偏移吻合**，且 UICursor 方法簇（0x541160-0x541FFB）覆盖 0x5414A0——真身极可能是 **UICursor 类方法**（名字自身也说 UICursor）。现作自由函数是过渡形（诚实标注「草稿钉名」）；将来 R91 式归属时若不摘 functions.json 条目 ⇒ functions∩methods 双源（恰是 P5 缺口盖不住的轴）。
- **定义体生成路径 ✓ 机制自洽**：unskip 后 export 不再跳过 ⇒ loop 链自产实证：`asm/pal3/decomp/PAL3_ReadRegistryStr_00541c40.json` 等 3 件（21:49）→ `pal3/src/free_functions.cpp:26818/26903/27031` 三具函数体（21:50，mtime 晚于 functions.json 21:45 = 新鲜）⇒ 「decomp 缺=export skip 所致（loop 链自产）」**证实**，当前树无「有 decl 无体」的 LNK2001 面。
- **LNK2001 残留风险面**：①annotation commit 与首次 export 之间的窗口若有人编译则 decl 有体无（本次未见该窗口被使用）②`data/status/link_census.json` 停在 20:52（**早于本 commit**），链接层「无新增 unresolved」本轮未读数（probe 只编译不链接的盲区照旧）③名称链任一环节漂移（name 改了 decomp 文件名/体没跟上）会静默产生 decl-only，link_probe 是唯一闸但不在 loop 的强断言里。⇒ 建议补「G 类必有体」例行对账（research §5.1-2 双闭环方案未实现）。

### 5. 测试真锁度 — **结构性锁，锁不住 P1（P4）**

- **RED→GREEN 机械成立** ✓：pre-state 三地址在 skip_functions、functions.json 无条目 ⇒ 三条断言必红；现绿。
- **「测试 6/6 绿」核账**：`pytest tests/test_crt_sub_unskip.py tests/test_d3dx_naming.py` = 3+3=6 passed ✓（commit 口径含 T1 测试文件，可复现；单文件只有 3 测）。
- **锁了什么**：3 地址出 skip ✓ / functions.json 有条目且 signature 非空 ✓ / source 不含 'crt_runtime' ✓ / registry 名 ✓ / 0x541490 留 skip ✓。
- **锁不住什么**（P4）：①**签名正确性/参数个数**——P1 状态下测试全绿（`int __cdecl()` 有 signature 非空即过）⇒ 锁是「动作锁」不是「正确性锁」；②调用面兼容（真身/调用面参数数与签名元数对账）；③0x541490 **不在** functions.json（防双注反向）；④structs 零双源/名字唯一；⑤「unskip ⇒ 体存在」（LNK2001 闸）；⑥0x541490 测试函数名 `test_541490_alias_retained_linker_artifact` 把未定谳的 label 织进测试名（处置锁对、label 搭车）。
- **建议补测**（低成本高锁度）：`assert FN['0x00541C40']['signature'].count(',') == 2` 型元数断言或直比调用面 push 数；`assert not (set(FN) & set(all_struct_methods))`；`assert Path(asm/pal3/decomp/<name>_00541c40.json).exists()`。
- 另：plan Task 2 正文写的是「删 4 条 + `test_four_crt_sub_not_skipped_and_declared`」，实现是 3 删 + 1 改判留 + 3 测——偏离已由测试 docstring/commit 记载（且方向正确：K 类本不该 unskip 进源码重建），但 **plan 文件本身未回写**，台账小疵。

---

## 缺陷清单（按 红线 > ABI > 裁决理由 > 测试/闸缺口 > 台账 排序）

| # | 级 | 缺陷 | 修法 | 状态 |
|---|---|---|---|---|
| **P1** | **必修（红线：SetBlend 型静默坏码，已实锤）** | 0x541C40 `int __cdecl()` 元数误登（真身 3 参：lpSubKey/lpValueName/lpData）；生成 WinMain 零参调用（free_functions.cpp:26967）⇒ 注册表读垃圾参数 + 调用面字节必失配 | functions.json 改 `int __cdecl(const char *pszSubKey, const char *pszValueName, char *pszOutBuf)`（A 级证据已齐）或保守 `int __cdecl(...)`；apply→export→codegen 复跑；测试加元数断言 | **本任务内必修** |
| **P2** | **必修或显式挂账** | 0x5414A0 `void __thiscall(this)` 被 free_sig_decl 降级为 cdecl `_BYTE *_this`（ABI 错载体：ecx vs 栈传）；与 0x5415C0 同族（其 source_note 有挂账，本条没有） | `void __fastcall(_BYTE *_this)` 载体形（data.py:17 自家结论，字节级等价）；或照 0x5415C0 挂「ECX vs 栈传 A/B 对拍」账 | 本任务内处理 |
| **P3** | **建议（裁决理由降级）** | 0x541490「5B jmp 别名=linker_artifact（A 级）」过度定级：形状只证纯转发；ILT/ICF 与「0x5415C0 被直接 call + 0 处绝对引用」矛盾。处置（留 skip）成立但理由应换 | label 改「K/G-forwarder 未定谳；skip 依据=唯一消费方为编译器合成 atexit 桩（C 类）无源码消费面」；测试名/docstring 去 "linker_artifact" 断言 | 措辞/label 修正 |
| **P4** | **建议（测试锁度）** | 测试为动作锁：P1 存在时全绿；无元数/调用面/双源/体存在断言；"linker_artifact" 搭车进测试名 | 补 §5 建议断言 | 增测 |
| **P5** | **建议（闸缺口）** | check_annotations 双注闸不覆盖 functions.json ∩ structs methods 轴；0x5414A0 未来归属 UICursor 时恰踩此缺口 | 闸补该轴，或测试锁「三地址 ∉ structs methods」 | 防回归 |
| **P6** | **相关面（pre-existing，建议随修）** | 新生成体 `crt_sub_00541590();` 零参调用 vs 真身 thiscall+push 0（0x541590 decl `int __cdecl()` 同族误登） | 0x541590 签名按调用面正名（12 处调用面可逐一对账） | 挂账/随修 |
| P7 | 台账小疵 | plan Task 2「删 4 条/four_crt_sub」与实现（3+改判）不一致，plan 未回写 | 回写 plan 勾选项 | 可选 |

---

## 未复验清单（显式）

| 项 | 状态 |
|---|---|
| LNK2001 链接层读数（link_census 停在 20:52 早于本 commit；「无新增 unresolved」未当场读） | **未复验**（体已在 free_functions.cpp，当前树无 LNK2001 面；链接层闸建议下轮 link_probe 当场读） |
| codegen 对 `[ebp+4/8/C]` BYREF 局部的栈槽安置行为（callee 是否「碰巧」读到入参槽） | **未复验**（不影响裁定：caller 侧缺 3 push+add esp,0xc 已独立致坏） |
| 0x5414A0 真身类归属定谳（UICursor 方法 vs UIQuadManager 单例成员；UICursor binary_size=64 与 guard 0x1894DB0=单例基+0x20 的间距存疑） | **未复验**（偏移吻合 m_tex[3]@16/m_bSoftMode@29 为强旁证；归属变更须按「禁止仅凭 signature this」纪律另行取证） |
| 0x541490 三假说（K-ILT / G 源码转发 / 编译器尾跳 thunk）的终审定谳 | **未复验**（处置不受影响；需原 map/增量链接证据或 PAL3A 对照才能定） |
| 0x5415C0 自身 cdecl vs thiscall 挂账（A/B 对拍族） | **未复验**（非 T2 diff 范围，未动） |
| RED→GREEN 对 pre-state 的重放 | **未重放**（membership 翻转机械成立，3 断言 pre-state 必红） |
| 0x541860 返回值语义（成功=串长、失败=残值 eax）与原始源码意图 | **未复验**（调用方忽略返回值 ⇒ `int` 保守形不越权，不影响裁定） |
| loop 全绿/读数台账（S2/L1/总错误） | 未复验（属 Task2 Step6 编排者读数，非本次裁决面；probe_census 21:53:15 overlay=pure 标签已见） |

---

## 附：复现索引

| 结论 | 证据位置 |
|---|---|
| 三户字节/身份 | IDA `get_bytes`（0x541490/0x5414A0/0x541583/0x541860/0x5418CE/0x541C40/0x541CA8 七段）+ PE 直读 capstone 全量反汇编（.text RawPtr==VA 1:1）|
| 调用面参数数 | 0x54199B（3 push + add esp,0xc）· 0x5419A7（零 push）· 0x4049C3（`mov ecx,eax` 零 push）；IDA `xrefs_to` 各 xref_count=1 双通道一致 |
| P1 实锤 | pal3/src/free_functions.h:217-219（decl 三行）· free_functions.cpp:26967-26968（0 参调用）·27031-27055（3 入参渲成 BYREF 局部）· asm/pal3/decomp/PAL3_ReadRegistryStr_00541c40.json |
| 0x541490 引用面 | 全文件 E8/E9 扫描 + 4 字节绝对引用扫描（0 命中）+ IDA xrefs_to（恰 1：0x541635∈InitUIQuadManagerSingleton 0x541630 10B atexit 桩）|
| 约定降级机制 | pipeline/gen/data.py:23-42 `free_sig_decl`（__thiscall→丢 cc+this→_this）· :17（__fastcall=唯一 ABI 等价自由形自述）|
| 双源闸缺口 | pipeline/check_annotations.py:739-780（仅 skip∩(methods∪functions) 轴）|
| 测试锁 | tests/test_crt_sub_unskip.py（3 测）+ tests/test_d3dx_naming.py（3 测）= 6 passed |
