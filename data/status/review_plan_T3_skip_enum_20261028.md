# T3 skip_reason 枚举化 · 独立对抗复核（plan Task 3 / spec #4）

> 2026-10-28 · 复核对象 = HEAD **341760df7**（`data/annotations/skip_functions.json` 1907 条全落六枚举 + `tests/test_skip_reason_schema.py` 3 测）。
> 方法：git 账目考古（d2b87339d→f7b4faa96→341760df7 三态对账）+ **分桶抽样 17 条 objdump 字节形核对**（original/PAL3.exe）+ 普查/调研/勘误三档对照 + 六消费点代码走读 + **变异测试 10 组**测真锁度 + 测试与 check_annotations 实跑。
> 复核只读裁定；唯一落盘物 = 本文件。

## 0. 裁决

# **ACCEPT-WITH-FIXES**

| # | 攻击点 | 裁定 | 一句话 |
|---|---|---|---|
| 1 | 分桶抽查（5 条/桶对二进制/普查档） | **REJECT 级发现**（修复后收） | 553 具名桶中 **134 条误桶**：`_static_` 90 供源错、PSGP 簇 40 供源错、**4 条真代码体被标「真跳板」**（SetBlend 同类实锤） |
| 2 | 保守默认桶 1408 合理性 | **ACCEPT**（纪律正确）+ FOLLOWUP | 禁猜测红线守住了（默认桶零错误正向主张），但 73.8% 过肥=枚举判别力实损，须后续拆分或台账声明 |
| 3 | reason 镜像 / 6 消费点零改动 | **ACCEPT**（核实成立 ✓） | 1907 条 keys/name/reason **0 漂移**；六消费点只读 keys/name/reason-`=='thunk'`；0 管线文件改动；check_annotations PASS |
| 4 | 测试真锁度 | **ACCEPT-WITH-FIXES** | 3/3 绿但锁面仅 3 规则族；**误桶被正锁**（正确修复反而红）；计划承诺的六消费点对账测试缺 |
| 5 | 计划缺陷回写（1910→1907 平账） | **ACCEPT-WITH-FIXES** | 平账算术 ✓ 核实无误；**回写未做**——plan/spec 四处仍写 1910 |

**升级条款**：F1/F2（§1b/§1c MUST-FIX）必须落在 **Task 7 注册表落地消费枚举标签之前**；若下游把 `linker_generated`/`compiler_regenerated` 当供源真相消费而未修，本裁决升级 REJECT。

---

## 1. 分桶抽查（攻击点 1）——逐桶字节形核对

### 1a. `lib_relink_ok` 309 条 —— 处置对，但「真 CRT 件」不全（3/5 严格 CRT）

| 抽样 | 字节形 | 判 |
|---|---|---|
| `start` 0x55507C | `push ebp; … fs:0 SEH 链 …` WinMainCRTStartup 形 | ✓ 真 CRT（libcmt） |
| `_sprintf` 0x553082 | 标准 stdio 包装形 | ✓ 真 CRT |
| `?_JumpToContinuation@@…` 0x5530D4 | EH runtime（fs:0 链操作） | ✓ 真 CRT（EH） |
| `frsqrt_3dnow` 0x552440 | `movd mm6,…; pand; pfmul`（3DNow!） | ✗ **d3dx9.lib PSGP 变体**，非 CRT |
| `__m64::_sub_550B93` 0x550B93 | `movq/punpckldq/pfmul` MMX 矩阵 | ✗ **PSGP MMX 实现**（`_static_` 簇同族，仅名形不同） |

- 全 309 条落在 0x550B93–0x55EF90（0x55xxxx 段规则命中）；244 条 CRT/EH 名 + 65 条其他（3DNow/MMX/PSGP 溢出件）。
- **skip 轴处置无误**（两类均为链接期库供给，skip=正确）；但桶语义若被读作「真 CRT」则含假。边界轴（lib_crt vs lib_thirdparty）应留 Task 7 注册表逐件状态化。
- **规则自洽缺陷**：同一 PSGP 簇被名形撕成两桶——`__m64::_static_*` → compiler_regenerated（90）、`__m64::_sub_*`/`frsqrt_3dnow` → lib_relink_ok。`_static_` vs `_sub_` 是 IDA 命名噪声，不是语义边界。

### 1b. `compiler_regenerated` 135 条 —— **90/135 误桶**（MUST-FIX F1）

| 抽样 | 字节形 | 判 |
|---|---|---|
| `SingletonThunk_004044B0/44D0/44F0` | `B9 imm32; E9 rel32` + NOP 对齐（`mov ecx,[global]; jmp target`） | ✓ 编译器单件访问跳板，**真合成物**（spec §1 锚「45/45 SingletonThunk 字节形」） |
| `__m128::_static_547042` | `mov eax,[esp+4]; mov [eax+8],ecx…` 写函数指针表 | ✗ **sse_D3DXInitFastTable 安装器** = d3dx9.lib 产物 |
| `__m128i::_static_552116` | `movaps xmm0,…` SSE 实现体 | ✗ **d3dxmath.obj 实现变体** |

- 90 条 `*_static_*`（`__m64::`59/`__m128::`18/`double::`11/其他 2，0x547042–0x552116）三档一致判定为 **D3DX PSGP 变体件**：
  ① `crt_skip_census_20261028.md` 【更正】节原文「应归 D3DX PSGP 变体件…**理由须换**为『可再生产件（d3dx9.lib 供给）』，非『真 CRT/静态簇』」；
  ② `research_dx_static_boundary` :61-62「`__m64::_static_*`/`__m128::_static_*` 是 MMX/SSE 实现…**D3DX 库产物**」；
  ③ spec §6 跨报勘误表「普查文：__m64 簇归 D3DX PSGP｜裁决方 dx 调研」（spec 已吸收）。
- **误桶机理**：T3 规则源取了普查 **§分类正文（更正前）**，漏掉同文件【更正】节；「名形证据>段启发」Ruling 把 `_static_` 名形读作「编译器静态合成」，与勘误后的簇定谳相反。写源码（`~X()+delete`/static 对象）**不会再生**这些件——它们由 d3dx9.lib 供给且带版本偏斜（73 槽 vs 在手库 71 槽，spec §1），归 `compiler_regenerated` 掩盖了 Task 8 的补给依赖。
- **正确桶** = `lib_relink_ok`（skip 轴：库供给可再链）；版本偏斜记在 supply 轴（Task 7）。

### 1c. `linker_generated` 53 条 —— **44/53 误桶**（MUST-FIX F2，含 SetBlend 同类）

**13 条 `j_*` 全量字节审计**（非抽样）：

| 形 | n | 判 |
|---|---|---|
| `jmp rel32` + NOP（尾跳别名/ILT） | 9 | ✓ 真跳板 |
| **真实代码体** | **4** | ✗✗ **「真跳板」主张被字节证伪** |

4 条真代码（旧 reason='thunk' 的主张被 T3 直接继承，未做 spec §2.1 字节形分诊——「禁名字结论」违例）：

| 地址 | 名 | 字节形首几条 | 实为 |
|---|---|---|---|
| 0x0041CA30 | `j_InputSystem::ProcessKeyboard` | `mov [ecx+0x1c4],eax; mov [ecx+0x1c8],edx` | thiscall 成员写 = **真方法体** |
| 0x0041D590 | `j_InputSystem::ProcessKeyboard_2` | `mov [ecx+0x1c8],eax; push 1` | 真方法体 |
| 0x00485DC0 | `j_NPC::UpdateAnim` | `mov edx,[esp+8]; push ecx; mov eax,esp` | 真方法体 |
| 0x005044F0 | `j_CCCTData::UpdateCamera` | `lea eax,[eax+eax*2+0x23d]; lea edx,[ecx+eax*8]` | 真方法体（数组寻址） |

⇒ **SetBlend 同类风险实锤**：游戏代码被登记为「链接器跳板=构建期供给、无需逆向」。当 Task 7/8 按标签处置时 = 真代码静默漏建。此 4 条须立即改判（最低限度 → `awaiting_signature` + 挂「疑似冤户」复裁标记；是否 unskip 须调用面/声明收编面（批0 闸）调查后另裁）。

**40 条 0x5424xx–0x543Axx 簇**（sub_542xxx + `D3DXVec3Normalize`@0x542533 + `_purecall`@0x543092）：

| 抽样 | 字节形 | 实为 |
|---|---|---|
| 0x542533 `D3DXVec3Normalize` | `jmp dword ptr [0x6090c4]`（dispatch 表项，**非 IAT**） | PSGP 公开入口跳板 |
| 0x542526 | `push 1; call 0x546F41; jmp [0x6090c4]` | PSGP 惰性初始化桩 |
| 0x543092 `_purecall` | `jmp dword ptr [0x6090b4]` | PSGP 分发入口（名亦可疑） |
| 0x542448 | `push 1; call 0x546F41; fld …` | PSGP 包装（懒初始化序言+真体） |
| 0x543AED | 同上形 | PSGP 包装 |

- 整簇三档判定 = **d3dxmath.obj / d3dx9.lib 产物**（research_dx :61「入口跳板+惰性桩簇…**D3DX 库产物**」；spec §6「sub_542xxx=D3DX9 PSGP（d3dxmath.obj 逐位）」）——**不是链接器产物**。`linker_generated`（链接器生成）字面即错；正确 = `lib_relink_ok`（库供给）。
- 另注意 research §4.3 自己也要求「sub_542xxx 按 §3.2 形状表**分流**（E / import_thunk / compiler_synthesized / linker_artifact）」——T3 整簇一桶，分流未做。

### 1d. `dual_def_workaround` 2 条 ✓

`PushMatrixStacks`/`PopMatrixStacks`@0x540F60/0x540FA0——entry `source` 自述「批0 复位…skip 挡 C2556/2373 ×144 爆=双定义 workaround」，与 research §4.3 映射、spec §4 枚举语义（批0 教训）三方一致。✓

### 1e. 规则源一致性核查（commit 自称「research §197 点名」= §4.3 迁移清单）——**映射违例清单**

| research §4.3 明文映射 | T3 实际 | 违例 |
|---|---|---|
| 186×群 A 桩（unknown_libname_287-524/528）→ `compiler_regenerated` | awaiting_signature（全部 unknown_libname_） | ✗ ~186 条（测试规则还锁死修正） |
| unknown_libname_529-552 → `lib_crt`（真 CRT，0x5577E1-0x55D348 实测 24 条在 0x55xxxx） | awaiting_signature | ✗ 24 条（名形规则盖过段规则） |
| `compiler_init_005090A0` reason→`compiler_regenerated`（「与其他 compiler_init 65 条统一」） | awaiting_signature | ✗ 点名件直接违例 |
| `DirectInput8Create`→`import_thunk` | lib_relink_ok（段规则） | ✗（枚举无 import_thunk 值，`linker_generated` 更近——枚举欠表达） |
| `SingletonThunk_*`→`compiler_synthesized` | compiler_regenerated | ✓ |
| Push/PopMatrixStacks→`dual_def_workaround` | ✓ | ✓ |

⇒ 裁决「名形证据>段启发」本身可立（`_static_` 簇冲突场景），但**被泛化到了无名形证据的占位名**（`unknown_libname_`/`crt_sub_` 是自动名，零证据内容），且与自引规则源 §4.3 的点名映射冲突时未记录改判理由。Ruling 需限缩 + 与 §4.3 逐条对账（F3）。

---

## 2. 保守默认桶 1408（攻击点 2）——裁定：**纪律正确，桶过肥，FOLLOWUP**

- **支持保守默认（裁定采纳）**：① 项目禁猜测红线（无逐条二进制证据不得改判）；② 普查 §二实证旧标签会说谎（`crt_runtime` 筐里塞着 `fn` 钩子回调、渲染栈 helper）——旧 reason 字符串（compiler_thunk 217 / between_std_methods 175 / trivial_accessor 125 …）自述性不可直接当证据；③ `awaiting_signature` 是**无主张桶**，不产生 SetBlend 型错误正向声明——与 1b/1c 的误桶有本质区别。
- **桶过肥实锤（判别力损耗量化）**：1408/1907 = **73.8%** 入默认；其中约 **481 条**旧 reason 为 compiler_* 家族（compiler_thunk 217 + generated_nop 90 + generated_init 65 + global_init_stub 53 + float_init_stub 51 + generated 5），且 research §3.1/§3.3 已给**簇级字节实证**（44B guard+atexit 同型 31 抽样全同、`.CRT$XCU` 收编表 xref、FLIRT「MSVC runtime」自注）+ spec §1 `compiler_synthesized` 明文含「init 桩」——这批本可簇级 Ruling 提升，未做。
- **裁定**：不否决（纪律 > 判别力，且默认桶无害）；**FOLLOWUP F4**：① 或按 research §4.3 + 簇级字节形把 compiler_* 家族提升入 `compiler_regenerated`（每簇记录 Ruling+证据）；② 或在台账显式声明 `awaiting_signature` 是双义桶（「crt 待定名」+「未裁非 crt」），防下游误读为「全部待签名」。

## 3. reason 镜像 / 6 消费点零改动（攻击点 3）——**核实成立 ✓**

- **数据面**：a73106582→341760df7 全 1907 共同键 **keys/name/reason 三字段 0 漂移**（程序化对账）；commit 仅动 2 文件（skip 表 + 新测试），**0 管线文件改动** ✓。
- **代码面**（六消费点逐走读）：`export_full.py:333`（keys→skip_addrs）· `export_full.py:1154+1165`（name + `reason=='thunk'` 过滤）· `collect.py:96-106`（`reason=='thunk'` 收 thunk 类名）· `data.py:252-266`（`reason!='thunk'` 导非 thunk 名）· `apply_annotations.py:2290/:2365`（keys+name）· `check_annotations.py:743-780`（keys+name，declaration_only 语义）· `annotation_view.py:129`（单一读点 loader）。**无任何消费点读条目级 `skip_reason`** ⇒ 枚举新增字段对六消费点完全不可见，「零改动兼容」主张**成立** ✓。
- **实跑**：`check_annotations` **0 errors PASS**（110 warnings 均存量 WARN 类）。
- 计划引用漂移（不影响结论）：`data.py:221` 实际在 :252-266；`pipeline/ida/check_annotations.py` 实为 `pipeline/check_annotations.py`。
- 附带发现：45 条旧 `skip_reason` 描述串（singleton 跳板的 A 级字节形实录 `mov ecx,[0x00DB9FD0]; jmp 0x0044EF30` 等）被枚举值**覆盖且未迁移 `source`**（0 条留存）——消费者无损但**证据文本灭失**（仅存 git 历史），违反「证据随数据走」惯例（F5）。

## 4. 测试真锁度（攻击点 4）——变异实测

实跑 `pytest tests/test_skip_reason_schema.py` ⇒ **3/3 绿** ✓（与 commit 主张一致）；`tests/test_crt_sub_unskip.py`（T2 件）对 1907 账无冲突断言。变异测试（10 组，测试三断言复刻跑）：

| 变异 | 结果 | 说明 |
|---|---|---|
| 删 1 条 / 非法枚举值 / 0x55xxxx 翻桶 / SingletonThunk 翻桶 / unknown_libname 翻桶 | **DETECTED** ✓ | 枚举+总数+三规则族锁有效 |
| 翻 0x41CA30（j_ 真代码）linker_generated→awaiting_signature | **UNDETECTED** | linker_generated 桶**零规则锁** |
| 翻 0x542533（PSGP 簇）→lib_relink_ok | **UNDETECTED** | 同上 |
| 翻 dual_def_workaround→awaiting_signature | **UNDETECTED** | dual_def 桶零锁 |
| **按普查更正把 `_static_` 修为 lib_relink_ok（正确修复）** | **DETECTED** ✗ | **测试锁死误桶——修正必红** |
| 135 条 reason 值 `thunk`→`linker_trampoline` | **UNDETECTED** | **六消费点 `=='thunk'` 契约无锁**（镜像测试只断言非空，不断言值不变） |

结论：锁面 = 枚举合法性 + 总数 + 3 规则族；**桶内容对错几乎不锁、误桶反被正锁、消费者契约不锁**。计划 Step 1 承诺的 `test_six_consumers_agree_on_new_schema`（六消费点对账）**未交付**（3 测替代，其中 `test_rules_from_census_applied` 为计划外新增）。⇒ F6：① 补 reason 值不变断言（对照 git 基线或按 `=='thunk'` 135 条钉数）；② 补 linker_generated/dual_def 桶规则断言；③ 修 `_static_` 误桶时同步修规则（勿让锁挡勘误）。

## 5. 平账 1910→1907 + 回写（攻击点 5）

- **平账算术 ✓ 核实**：d2b87339d（T1 后）= **1910**（crt_runtime 923）→ f7b4faa96（T2）= **1907**，程序化 diff 确认 T2 恰移除 3 条且全是 crt_runtime：`0x005414A0`（UICursor 装载）/`0x00541860`（CD 盘扫描）/`0x00541C40`（注册表读）；`0x00541490` 裁决改判**留 skip**（5B jmp 别名，ILT/ICF 三假说未定谳——落 `awaiting_signature` 诚实 ✓，T2 测试 `test_541490_alias_retained_linker_artifact` 钉住）。commit 所称「1907=T2 unskip 3 户后真账，计划 1910 陈旧基线」**属实** ✓；测试 `assert len(SK)==1907` 锁的是正确账。
- **回写 ✗ 未做**：plan（:98「总数仍 1910」、:104 `test_all_1910_…`）+ spec（:69「枚举须与 1910 总账平账」、:105「平账 1910」）**四处原文未勘误**；git log 显示两文档最后改动 = T3 之前的 spec 定稿（9b49bc027）。勘误仅存 commit message + 测试注释。按 spec §5.6「跨报勘误必须回写原报告勘误节」⇒ **违例**，下一个读 plan 的会话仍会拿 1910 断言（F7）。顺带：plan/spec 的「923 条 crt_runtime」在 T2 后实为 920，同须勘误。

## 6. 缺陷清单（按严重度）

| ID | 级 | 缺陷 | 修法 |
|---|---|---|---|
| **F1** | **MUST-FIX**（SetBlend 同类） | 4 条真代码体（0x41CA30/0x41D590/0x485DC0/0x5044F0）标 `linker_generated`=「真跳板」被字节证伪 | 改判 `awaiting_signature` + 挂「疑似冤户·真方法体」复裁标记；批0 闸后调研是否 unskip（调用面/声明收编面） |
| **F2** | **MUST-FIX** | 供源错置 130 条：`_static_` 90（→`lib_relink_ok`，吸收普查【更正】）+ PSGP 簇 40（→`lib_relink_ok` 或按 §4.2 形状表分流）；`_purecall`/`DirectInput8Create` 名实亦存疑 | 逐簇改判 + `source` 记勘误引证（普查更正节/ spec §6）；同步修测试规则（勿锁误桶） |
| **F3** | 高 | research §4.3 点名映射违例（群 A ~186 / 群 C 24 / compiler_init_005090A0 / DirectInput8Create）；「名形>段」Ruling 泛化到零证据占位名 | 与 §4.3 逐条对账：改判或落 Ruling 理由（census「另行审计」与 §4.3「已裁」冲突须明裁） |
| **F4** | 中（FOLLOWUP） | 默认桶 73.8% 过肥（compiler_* 家族 ~481 条有簇级证据未提升） | 簇级提升或台账声明双义桶 |
| **F5** | 中 | 45 条 A 级字节形证据文本（旧 skip_reason 串）被枚举覆盖、未迁 `source` | 从 git 历史（a73106582）回收进各条 `source` |
| **F6** | 中 | 测试锁面缺口：六消费点对账测试缺、reason 值契约无锁、linker_generated/dual_def 零锁、误桶被正锁 | 见 §4 修法三条 |
| **F7** | 中 | 1910→1907（及 923→920）勘误未回写 plan/spec（违 spec §5.6） | plan :98/:104 + spec :69/:105 四处勘误 + spec §6 勘误表补行 |
| **F8** | 低 | `dup_decl_elsewhere` 枚举值 0 使用；已知双注件 0x5415C0（functions.json 有真签名 decl）与 22 条 declaration_only 收编件全落 awaiting_signature | 随 F3/F4 对账一并裁（或删枚举值/记注） |
| **F9** | 低 | commit message 无 S2/L1 读数台账引用（plan 四段纪律「当场读」形不合规）；`_loop_last.json` 22:17:58（s2 134/214 · L1 159/159 · rc 全 0）与 T3 commit 22:22:07 之间夹有 T2 提交 22:18:16 ⇒ **该 loop 读数归属 T3 提交字节未复验**（loop 全程 ~19min，4 分钟窗口不可能重跑） | 下任务起 commit message 钉读数；本次不追溯 |

## 7. 未复验项（诚实申报）

1. **loop 读数归属**（F9）：未复验 22:17:58 的 loop 是否覆盖 T3 提交的 skip_functions.json 字节终态；S2 134/214 · L1 159/159 读数本身已当场读到。
2. **1408 默认桶逐条合法性**：未抽（裁为无主张桶，抽样意义低）；其中 compiler_* 481 条的簇级证据仅引 research §3.1/§3.3，未逐条复验字节形。
3. **40 条 PSGP 簇全量**：抽 5/40；其余 35 条按同址段+同形推定（簇级证据，孤证风险低但未逐一）。
4. **45 条 SingletonThunk 全量字节形**：抽 3/45；其余沿用 spec §1「45/45 SingletonThunk 字节形」锚（上游实证）。
5. **lib_relink_ok 309 条 vs 库成员字节配对**（spec §2.5「须字节配对 .lib 成员」）：未做——「真 CRT vs d3dx9.lib 溢出件」的边界轴细分留给 Task 7 注册表。
6. **4 条真代码 j_* 的调用面/归属**：仅字节形定性「非跳板」；是否 unskip（冤户）未裁（须批0 声明收编面检查）。
7. **IDB/IDA MCP 交叉复核**：本次取证走 objdump 直读 PE 字节（同源证据，A 级字节形）；IDA MCP 未连（无 idb 冲突操作），结论不依赖 IDB 状态。

---

*附：证据定位速查——普查 `data/status/crt_skip_census_20261028.md`（§分类 + 【更正】节）· `research_crt_boundary_20261028.md` §3.1/§3.2/§4.3 · `research_dx_static_boundary_20261028.md` :61-62/:73 · spec `docs/specs/2026-10-28-reproducible-boundary-spec.md` §1/§2.1/§4/§5.6/§6 · 账目 d2b87339d/f7b4faa96/341760df7 · loop 读数 `data/status/_loop_last.json`。*
