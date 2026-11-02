# 独立对抗复核：重载换轨修复批（cea40a230..6326e7311）

- 复核日：2026-11-02 · 复核人：独立对抗复核（子代理）
- 范围：`git log cea40a230~1..6326e7311`（6 commit）+ 工具实读 + idapro MCP 实测 + PDB 真值比对
- 铁律：字节匹配第一 · 不编造信息 · 少规则=少错误 · 不准确=不判定 · TOS 单源
- 实测基线状态（当场读）：`tools/cxx_gate.py` errs=0 warns=0 ·
  `pipeline/check_annotations.py` 0 errors/121 warnings PASS ·
  批内 4 测试文件 15 测全绿 · cxx_gate_baseline 现 478 键（587−109 合并销账 ±17 键形漂移）

## 总裁定：**需修**（方向成立、闸体系有效，但 2 个 major 缺陷 + 多项主张与实现不符）

批次设计（mangled 冲突裁定升级 / 三门棘轮 / 去戳退役 __ovl_ 旧规 / Fix1 地址字面量）方向正确且全部有测试与实测锚。
驳回不成立；但实测抓到**名称正确性缺陷（D1）**与**合并信息丢失（D2）**两个 major，
以及「_E 留 stage4」「字段非空并集」两处**主张与实现不符**，须修后放行下一步。

---

## 逐项 verdict

### ① cea40a230 vc6_mangler 三件 —— **部分通过（形对、真值标注过强、零参尾 bug）**

- **fp 参 @Z 锚：形正确 ✓**。PDB（PAL3A）真值双形佐证：
  `?_set_new_handler@@YAP6AHI@ZP6AHI@Z@Z`（fp 参 `P6AHI@Z` + 非空参尾 `@Z`）与
  `?_query_new_handler@@YAP6AHI@ZXZ`（fp 返回型 + **零参尾 `XZ`**）。
  ArraySort 测例 `?ArraySort@@YAHHHHP6AHHH@Z@Z` 的嵌套 `P6AHHH@Z@Z` 形与上列同构 ✓。
- **ArraySort「真值锚」标注过强 ✗**：测例输入 `int __cdecl(...,int (*)(int,int))` 与注解实录
  （`functions.json` 0x00401810 = `int __stdcall(int,int,int,int compareFunc)`）**约定与参型均不符**；
  仓内无 ArraySort 真符号源（PDB 无全局 ArraySort、exe 内部函数无符号表）。
  demangle 往返只证明良构性，不是「对照 ArraySort 真值」。措辞应降为「形级锚（PDB 同形佐证）」。
- **零参全局尾 `@Z` 错 ✗（并入 D1）**：`mangle_global` 无条件收 `@Z`，
  `?g@@YAH@Z` ≠ MSVC 真形 `?g@@YAHXZ`（PDB `?_query_new_handler@@YAP6AHI@ZXZ` 实证；
  `validate_mangler.py` 头注亦自述「void-parameter tails ('X@Z' vs 'XXZ')」cl COFF 形为 XXZ）。
  成员形 `mangle()` 是对的（`XZ`）——**两形不一致，又一处双副本分叉**。
- **全局 ctor/dtor**：全局无 ctor/dtor 形，`mangle_global` 不需要 ✓。
- **`_GCC = YA/YG/YI` 完整 ✓**（VC6 全局形就 cdecl/stdcall/fastcall 三门；thiscall 非全局合法）。
  `parse_signature` 对无括号签名回退 `__thiscall`→`YA` 兜底，行为可接受。
- **附加实测缺陷**：stdcall fp 参 `int (__stdcall *)(int)` 被编成 `H`（fp 正则不带约定段，静默降级）→ D6。

### ② 490e24154 apply 全局接线 + preflight mangled 化 —— **需修（D1 落地点 + cv 缺口）**

- 接线本身（`_mangle_vc6(None,...)` → 委派 `vc6_mangler`、失败回退可读名）逻辑正确 ✓。
- **D1 落地**：①零参全局 68 条（functions.json 实测 68 个 `()` 签名）将写错 IDB 名；
  ②**已 mangled 名重绞**：0x00401C70 名为 `?FileSysInit@@YAXXZ`，实测
  `mangle(None,'?FileSysInit@@YAXXZ','int __cdecl()')` → `??FileSysInit@@YAXXZ@@YAH@Z` 垃圾名；
  且该垃圾名过 `emit_headers.demangle_name` 得 **伪类 `('YAXXZ','FileSysInit')`**（实测）→ 头文件面幻影类风险。
  修法见 D1。
- **preflight mangled 冲突键丢 cv ✗**：`idb_name(cls,name,sig)` 不传 cv，`mangle` 尾部 `const` 随参表截除
  （实测 `void __thiscall() const` 与 `void __thiscall()` 同键 `?f@A@@QAEXXZ`）⇒
  合法 const 重载会被误判「mangled 冲突」。当前注解 0 条尾 cv 签名（实测）= 潜伏态，
  但与 cxx_gate 的 `cxx_sig_key`（含 cv）**判定键不一致 = 双规分叉** → D5。
- `_strip` 形 `__ovl_[0-9a-fA-F]+$` 仅收 hex 尾戳，`OnMessage_ovl`（无 hex 尾）类残留不归一 → 并入 D7。

### ③ a5b600fa1 强闸 cxx_gate 三门 —— **通过（机制健全；留 2 个洗白面）**

- 三门实测健全：①same_addr 键含名册（改名即键漂=fail-loud）②same_name 键含计数 xN（增长必红）
  ③cxx_rule 严格键 = (类, 归一名, (cc, **cv**, 归一参表))，**cv 参与 ✓**（直接回答必攻 4 的 cv 问题：
  cxx_gate 侧含 cv；preflight mangled 侧不含 = 唯一缺口）。
- 587 键自举 → 3d2c37fb6 销 109（同址双录合并，真销账）→ 46e671785 ±17（实测 **17−/17+，
  每地址恰一对，全部为 same_addr 名册键形漂移**，无夹带新违规键）⇒ 「17 对销」结论**复核通过 ✓**。
- 洗白面（必攻 4「还有无他洗白路径」）：
  1. `--bootstrap` 整表重写**无理由参数**（对比 link_census 须 `--rebaseline "<理由>"`）→ D8；
  2. 46e671785 同 commit 内「闸②签名感知化 + 147 去戳」= **规则随数据放宽**——有用户规则背书
     （同名异签=合法重载）但与勘误 4 同族，建议规则变更与数据变更分 commit 且互相引用；
  3. gate③ SYNTH 正则（`_scalar_dtor|_vector_dtor|_sdtor|~|thunk|_init_`）豁免面可经改名伪造，
     gate② 无 SYNTH 豁免可兜同名-同签底 ✓，但换新名即双门皆脱（名字域检测固有极限，记录在案）。
- 478 基线现存真挂账（重名必被查出 ✓、尚未裁决）：ActVec/PtrVec 跨注册 5 址双录、
  0x4B7F70 nullsub ×4 类、0x4C0610 `nullsub_75_override` 跨 2 文件异签、
  0x451AA0 UILoadingFrm::OnMessage vs UIListBox::OnMessage_ovl 跨类双认领。

### ④ 3d2c37fb6 层①113 组合并 —— **需修（D2：「字段非空并集」不实，语义择一丢失）**

对 3d2c37fb6~1 → 3d2c37fb6 全量对账（脚本复核 113 组）：

- **86 组** = 纯大小写双录（`GetAlive_CCF0`/`GetAlive_ccf0` 型），合并正当 ✓；
  戳名残留由层② G1 收走（当前 `GetAlive` ✓——必攻 3 的「戳名残留」答：G1 收了）。
- **27 组 = 两键同址但语义异名/异签的冲突条目**，合并=**整条目择一**（键取规范形、内容取异侧，
  实测 0x00445FE0：键留大写、内容留小写侧），**非字段并集**：131 处字段值静默丢失——
  - **10 处语义名被 `sub_XXXX` 桩名压掉**：CopyFields/CopyFieldsFrom/CalcSize/GetRectRight
    （0x445FE0/43FEC0/445DB0/445E50）、CheckStateLimit/ShowCategory1-4（CCBStage）、
    OnMessage（CUtil 0x523B90）、GetData_EEF0；
  - **1 处带 caller-evidence 的签名被丢**：0x445FE0 `unsigned long *`
    （`name_source: "P2 类型修 2026-11-02（调用方实证：解引用+数组访问=unsigned long*）"`）→ `void *`；
  - **1 处类属/虚性冲突被择一**：0x43ddf0 留 `virtual void __thiscall(CCBMagicWindow *this)`
    却挂名 `CCBControlWindow::Render`（CCBControlWindow.json）——this 型与类属互斥；
  - 另 5 组语义异名冲突（0x5099A0 ApplyTaskTimeScale vs IsTaskFinished_99a0 等）择一未裁。
- **裁定**：同址=同函数，条目级合并成立；但**字段级「非空并集」主张不实**，
  且 27 组冲突本应「不准确=不判定」→ 挂待裁，而不是机械择一（择一方向与证据强弱无关：
  有证据的 CopyFields 输给了 sub_ 桩名）。→ D2。

### ⑤ 46e671785 层② G1+G2 去戳 147 件 + 2c 退役 —— **基本通过（判据机械可靠；证据面挂账）**

- 147 rename 全量提取 ✓（147 old/147 new）；制造同名组 13 个（OnMessage×7、Method×7、Update×4、
  Remove/UpdateRoleMP/CalcCombatDamage/GetTaskState/PassCmdToThread/DlgProcEffect/
  UpdateCameraLookAt/UpdateMovement/SetRect/nullsub 各×2）。**改撞检查**：
  cxx_gate 当场 errs=0 ⇒ 记录签名域内**无同(类,归一名,严格键)双址** ✓——
  「真不同函数改撞」在机械判据层面未发生。
- **G2「参型实异」判据（this 噪声）**：`cxx_sig_key` 剥 this（`X *this`/`__hidden this` 形实测剥净）
  + 剥参名 + 去空白 ⇒ 判据机械可靠 ✓。但**证据层不可靠面**：PtrVec_InsertN 对
  （0x53A340 `const char*` vs 0x53ACA0 `const void*`，均 `evidence_level: unverified`）
  的「实异」建立在未验签名上——若两者真型相同则是真冲突被签名猜测封印（闸看不见记录外的真相）。
  按「不准确=不判定」，此类 G2 降级为**观测挂账**而非「合法重载」定论 → D9。
- 2c「needs __ovl_」旧规退役 → mangled 裁定（同名异签放行、仅同签双址报错）与用户规则一致 ✓；
  退役面无残留 grep 核实 ✓。
- 语义质量回退（记录、非阻断）：`Method_XXXX→Method` ×7、`nullsub_XX→nullsub` ×2 =
  伪语义名批量产生（项目规则「禁止伪语义命名」精神上不鼓励，但属用户重载换轨规则的直接后果）。

### ⑥ 6326e7311 Fix1 UNRESOLVED 裁撤 —— **部分通过（地址形语义正确；「_E 留 stage4」主张不实）**

- **`&loc_X`→`((void*)0xX)` 取址等价 ✓**：`&loc_X` 语义=代码标号 X 的地址=数值 0xX，
  代码**消费 `&`**（`_lit` 返回整段替换），不产生 `&(void*)0xX` 形。
  观测面核实：全 decomp 语料 `&loc_` 恰 6 处（SEH handler/filter 赋值 `vNN = &loc_XXXX;`，
  承接型 `void *vNN`）——6/6 形态等价、可编译（void*←void*）。
  字节面：`mov [ebp-x], 56686Eh` 型 imm32 与原链 `offset` 形同字节，绝对址随链接器落 0x400000 基址，
  我方无 reloc 的 4 字节在 match 严格比对下仍同值 ✓。
- **`*(T*)loc_X` 形**：`*(T*)((void*)0xX)` 可编译可链接（cast-deref 恒等）✓；
  但**裸载入形 `x = loc_X`（读内存）被换成地址值 = 语义改变**（应为 `*(T*)0xX`）——
  **当前语料 0 例裸 loc_/qword_**（qword_ 全语料 0 例；word 边界复核）⇒ 潜伏边、不判死，
  记入未复验（若未来出现裸形须回改读值形）。
- **`_E68(` 过 stage4 解不出 ✗——主张不实**：stage4 解析面实测仅
  `dword_/byte_/word_/off_/flt_/unk_/stru_/asc_` + `sub_XXXXX` thunk + 成员解析，
  **无任何 `_E\d+`/`_L\d+` 器**（全 pipeline/gen grep 0 命中）。`_E68` 实为 IDB 名 `$E68`
  （idapro 实测 refs：`0x4ceaf0 → $E68`，skip_functions.json 挂 `crt_init/awaiting_signature`；
  `$E/$L` = EH funclet，见 tools/ida/ida_diagnose_quality.py:8）。
  ⇒ Fix1 后 `_E68(this)` 仍是**裸名 C2065**（`emit_cpp.collect_sub_refs` 模式不收 `_E\d+`），
  与 UNRESOLVED 形等价失败——**非新增 C2065，是同病换皮**，但 census 可见性净丢失。
  「P0-3 时序倒置：本可解析符号被提前判死」的「可解析」在 stage4 面**未获证实** → D4。
- `_E/_L` 语料量：`_E\d+(` 6 文件 10 处（真量小）、`_L\d+` 0 处。
- 2 测覆盖合成形；`'loc' 的 c 是 hex 越界修` 注释指 `alloc_` 之类子串越界（regex 带 `\b` 已免疫 ✓ 实测）。

### 必攻 5 TOS（apply 局部 _mangle_vc6 委派=绷带）—— **分叉实锤 10 面 + 共享件反向 bug**

局部件（apply_annotations.py `_mangle_vc6`）与共享件（vc6_mangler.mangle）逐面 diff：

| # | 面 | 局部副本 | 共享件 | 判定 |
|---|----|---------|--------|------|
| 1 | ctor/dtor `??0/??1` | 无（`?Name@Cls@@`） | 有 | 局部缺 |
| 2 | `_scalar_dtor`→`??_G` | 无 | 有（0b-④） | 局部缺 |
| 3 | cv（const→Q**B**E） | 无 cv 参、恒 QAE | cv 参存在（但尾 const 解析也丢） | 双缺/分叉 |
| 4 | virtual `U`/static `SA` | 无、恒 Q...E | 有 flags | 局部缺 |
| 5 | 零参尾 | `@Z`（错） | `XZ`（对） | **局部分叉且错** |
| 6 | LPCSTR→PBD（0b-②） | 无（落 'H'） | 有 | 局部缺 |
| 7 | 嵌套类 `U<seg>@<d>@`（0b-③） | `U<全::名>@@` | 正确形 | 局部缺 |
| 8 | 裸类指针 U/V 投票（0b-①） | 恒 'U' | 'V' 多数 | 局部缺 |
| 9 | strip_param_name 词表守卫 | 裸正则（`unsigned int`→`unsigned`→'H'，实测） | _TYPE_WORDS 守卫 | 局部缺 |
| 10 | ret 尾剥 | `\s+\w+::\w+$` 锚（**正确**） | `\w+::\w+` 任意位——**实测打烂嵌套返回型**：`AStarPathFinder::NODE *`→`?GetNode@...@@QAEPAV@@XZ` 垃圾 | **共享件缺** |

⇒ 委派=绷带定性成立；成员形分叉确凿，且分叉**双向**（共享件 ret-strip 有局部已修的 bug）。
收编不能整体替换，须按上表逐面归并 + 补真值测。→ D3。

---

## 缺陷分级与修法

| ID | 级 | 缺陷 | 修法 |
|----|----|------|------|
| **D1** | **major** | ①`mangle_global` 零参尾 `@Z`（应 `XZ`，68 条将写错 IDB 名）②已 mangled 名重绞（0x00401C70 实测出 `??...@@YAH@Z` 垃圾 + demangle 伪类 YAXXZ） | ①`if not params: 尾 'XZ' else '@Z'`（对齐成员形）②`idb_name`/调用侧 `name.startswith('?')` 短路直接回原名；各补真值测 |
| **D2** | **major** | 层①合并非「字段并集」而是整条目择一：10 语义名→sub_ 桩、1 处 caller-evidence 签名被丢、1 处类属/虚性互斥被择一、5 组语义异名未裁 | 从 3d2c37fb6~1 恢复 27 组冲突字段为 `alt_name/alt_signature`（或独立待裁台账），语义名与 evidence 字段回滚后按证据重裁；合并脚本如再跑须字段级冲突→显式告警拒择一 |
| **D3** | medium | TOS 双副本 10 面分叉（局部缺 0b-①②③④/cv/virtual/static/零参尾/词表守卫；共享件 ret-strip 反向 bug） | 先修共享件 ret-strip（锚定 `\s+\w+::\w+$`）+ 嵌套返回型真值测；再按面清单逐面收编局部副本，收编完成前禁再扩局部副本 |
| **D4** | medium | 「_E 留 stage4 解析」不实（stage4 无 `_E/_L` 器），census 可见性净丢失 | 二选一：补 stage4 `_E\d+`→按址名路由（`$E68`→0x4CEAF0→skip_functions 表）；或改口径为「_E/_L 维持裸名 C2065（与 UNRESOLVED 等价）」并把 `_E\d+` 加进 emit_cpp.collect_sub_refs/就地 extern 兜底（记取批 11 全撤教训） |
| **D5** | low | preflight mangled 冲突键丢 cv（与 cxx_sig_key 双规分叉；当前 0 条 cv 签名=潜伏） | `idb_name` 增 cv 形参，或 parse_signature 吸收尾 const/volatile 喂 `mangle(cv=...)` |
| **D6** | low | stdcall/fastcall fp 参静默编成 'H'（fp 正则无约定段） | fp 正则支持 `ret (__X *)(args)`，`P6A/P6G/P6I` 分派；零参 fp 尾同修 `XZ` |
| **D7** | low | 戳/戳名剥离正则 4 处分叉（preflight hex-only / cxx_detector `__ovl_.*` / compare_pal3 `_[0-9a-fA-F]{3,}$` / G1 实际形）——双副本病在规则面重现；`OnMessage_ovl` 残留实证 | 收敛单源 `strip_stamp()`（TOS 纪律），4 处改调单源 |
| **D8** | low(流程) | `cxx_gate --bootstrap` 整表重写无理由参数（link_census 须 `--rebaseline "<理由>"`） | 对齐理由参数+落盘；闸规则变更与数据变更分 commit |
| **D9** | low | G2「参型实异」在 unverified 签名上自封证据（PtrVec_InsertN 对 char*/void* 型差是猜测） | G2 定论要求双侧 evidence_level≥A，否则标 `overload_unverified` 入台账随访 |

## 未复验（本复核未做/做不了的面）

1. **apply→export→codegen→match 全链实效未跑**（本复核=静态+定点工具实测；D1 的 IDB 写名实效须 loop 当场读数验证）。
2. 147 rename 的**二进制证据未逐条抽验**（机械判据层面闸绿；G2 判据依赖记录签名）。
3. ArraySort 真符号源**不存在**于仓内——@Z 锚只能以 PDB 同形佐证，无法字节级对照原符号。
4. `$E68` 家族的 EH-funclet 定性仅据注释（ida_diagnose_quality.py:8），未反编译 0x4CEAF0 体确认。
5. 27 组语义异名冲突（0x5099A0 ApplyTaskTimeScale vs IsTaskFinished_99a0 等 5 组 + 0x43ddf0 类属冲突）**正确侧未裁**——需二进制归属证据。
6. 跨注册双录挂账（ActVec/PtrVec 5 址、nullsub 0x4B7F70×4 类、0x4C0610 跨 2 文件异签、0x451AA0 跨类双认领）**仍未裁**，仅被基线隔离。
7. 裸 `loc_/qword_` 载入形当前 0 例——若未来出现，Fix1 形需回改读值形（潜伏边）。

## 附：当场读数存档

- cxx_gate：errs=0 warns=0（baseline 478 键）
- check_annotations：0 errors / 121 warnings — PASS
- tests/test_msvc6_mangle.py + test_unresolved_literal.py + test_cxx_gate.py + test_cxx_collision_detector.py：15 passed
- 113 组合并对账：86 组纯大小写（合法）/ 27 组语义冲突择一 / 131 处字段值丢失 / 0 处字段空洞
- 17−/17+ 基线键漂移逐地址核对：每地址恰一对，全部 same_addr 名册键形漂移 ✓
- mangle 实测：cv 同键 ✓复现 · 零参全局 `?g@@YAH@Z` ✓复现 · 已 mangled 名重绞 ✓复现 ·
  嵌套返回型 `PAV@@` 垃圾 ✓复现 · stdcall fp→H ✓复现
