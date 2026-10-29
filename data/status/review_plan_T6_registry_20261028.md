# 独立对抗复核 · Plan Task 6 注册表落地（commit 499c2a51f）

- **复核对象**：`499c2a51f` · `feat(annotations): T6 注册表落地（spec #7）——thunk_registry + system_lib_statics`
- **变更面**：`data/annotations/system_lib_statics.json`（+552）· `data/annotations/thunk_registry.json`（+105）· `tests/test_registry_schema.py`（+38）
- **复核方式**：objdump 自建解析（73 dword 双表 + 17 条逐址字节形）+ 自写 COFF 解析器与 d3dx9.lib 成员逐字节配对（重定位掩码）+ 两轮测试篡改实验 + 跨文件对账（skip_functions / 调研四档 / dx 复核 / spec）——不采信 commit 自述，逐条独立复验
- **日期**：2026-10-29

---

## 一句话裁决

# ✅ ACCEPT-WITH-FIXES

**必攻 1（73 槽对账）与必攻 2（17 条字节形）全数复验通过**：73 dword 与 JSON 逐槽 0 mismatch；槽#7→0x5450B5=c_D3DXVec3Normalize（157B）、槽#35→0x544777=c_D3DXQuaternionSlerp（227B）经自写 COFF 比对**独立复现逐字节全同**；17/17 条 boundary 标签无一错置。但「unknown 0 = 完备」**与 dx 复核实测（4 槽不可复现）直接矛盾**（D1，核心）；`default_target` 字段语义与 `name` 配对错位（D2，核心）；supply 轴全 4 条错枚举 + d3dx9.lib confidence 虚高（D3）；测试内容零锁（D9）。均**可修**，不构成 REJECT。

---

## 必攻点裁决对照

| # | 必攻点 | 裁决 |
|---|--------|------|
| 1 | 73 槽对账独立复验（含槽#7/#35 复核） | ✅ 数值全对；但 `default_target` 语义错位 + 「unknown 0=完备」虚报（D1/D2） |
| 2 | 17 条 thunk_registry 判据抽查（错置） | ✅ **无错置**（B 组/Site2/F1 逐条字节形全对）；仅 2 处 note/出处 loose（D6/D7） |
| 3 | confidence 轴虚高审计 · 4 库边界标签核 | ⚠️ 边界 4/4 正确；d3dx9.lib confidence+「字节全同」虚高、supply 错枚举（D3） |
| 4 | 测试真锁度（_schema 豁免是否掩盖缺陷） | ⚠️ 形锁有、内容零锁；篡改实验 2/2 静默通过（D9） |

---

## 逐项复验

### ① 73 槽对账独立复验 —— ✅ 数值 PASS（73/73 逐槽 0 mismatch）+ 2 处语义缺陷（D1/D2）

**自建 objdump 解析**（`objdump -s --start-address=0x6090a8 --stop-address=0x6091cc original/PAL3.exe`，小端 dword 独立解码）：
**73 项与 `system_lib_statics.json` 的 `default_target` 逐槽比对 = 73/73 全同、0 mismatch**。commit 自述「objdump 解析 0x6090A8」**属实**。

**槽#7 / 槽#35 复核（任务指定）——CONFIRMED，且发现双表结构**：

0x6090A8（live 表）与 0x6091D0（template/default 表）是**两张 73 dword 表且 73 槽全不相同**（我方全量比对）。槽#7/#35 在两表的值：

| 槽 | live 表初值（JSON `default_target`） | template 表（default 目标） | 复核 |
|---|---|---|---|
| #7 (0x6090C4) | `0x542526` | **`0x5450B5` = c_D3DXVec3Normalize** | ✅ 确认 |
| #35 (0x609134) | `0x54474d` | **`0x544777` = c_D3DXQuaternionSlerp** | ✅ 确认 |

- **`0x5450B5` = c_D3DXVec3Normalize** ✅：自写 COFF 解析器从 `tools/vc6/Lib/d3dx9.lib` 抽 `d3dxmath.obj`（自解析 ar 长名表），`?c_D3DXVec3Normalize@@YGPAUD3DXVECTOR3@@PAU1@PBU1@@Z` COMDAT = **157B（=宣称 157）**，与 exe@0x5450B5 比对：**3 重定位站点 / 12B don't-care / unmasked mismatch = 0** ⇒ 逐字节全同**独立复现**（hidden diff=12/157=7.6%，全部为重定位覆盖字节）。
- **`0x544777` = c_D3DXQuaternionSlerp** ✅：`?c_D3DXQuaternionSlerp@@YGPAUD3DXQUATERNION@@PAU1@PBU1@1M@Z` = **227B（=宣称 227）**，exe@0x544777：**3 站点 / 12B / 0 mismatch**（hidden diff=5.3%）。
- 附加复核：live 表初值**也是库符号**——`0x542526` = `?init_D3DXVec3Normalize`（13B，2 站点 8B 掩码，0 mismatch）、`0x54474d` = `?init_D3DXQuaternionSlerp`（36B，2 站点 8B，0 mismatch）。0x54474d 字节形 = `push 1; call 0x546F41; flds/push 重推 4 参; call [0x609134]; ret 0x10`（惰性 init + 参数重整包装），与 dx 复核关单项「0x54474D = init_D3DXQuaternionSlerp 36B masked diff=0」互证 ✓。

> **缺陷 D2（核心）——`default_target` 语义错位 + name↔address 错配**：
> JSON 每槽只记 **live 表初值**（= `init_*` 惰性桩），却把 `name: c_D3DXVec3Normalize` 与之并列 ⇒ 读表者会得出「0x542526 = c_D3DXVec3Normalize」的**错误地址↔名映射**（实为 13B init 桩；真身在 0x5450B5）。表注「默认目标=槽初始值，PSGPInit 后重指向」自定义了「默认目标」，但调研/复核谱系里「槽 #7 default 目标」明指 **template 表值 0x5450B5**（research_dx §2.2/§3.2 例 B/C、review_dx 残差表同义）——**同一术语两个所指**。JSON 内 `template_va: 0x6091D0` 有记录但**无逐槽 template 值**，被命名实现体（0x5450B5/0x544777）地址全缺。修法：逐槽分 `live_init`（init_* 桩）/ `default_impl`（template 表值）两字段，`name` 挂 default_impl。

> **缺陷 D1（核心）——「unknown 0 = 完备」虚报，4 个残差单元被标 paired**：
> commit 称「2 named + 71 paired = 与调研『2+71』精确吻合；unknown 0 = 完备」。但 **dx 对抗复核已全量配对并推翻该态**（review_dx_static_boundary_20261028.md）：73 槽实测 = **69 在手库可复现（67 精确命名 + 2 psgpmesh）+ 4 不可复现**，且 spec §1 已吸收（「4 个实现体残差（#39/#67/#71/#72）…未补给前该 4 单元**降级 `unknown`/定点重建**」「版本偏斜须**逐单元状态化**」）。4 残差实测表（复核档原样）：
>
> | 槽 | exe | 长度 | 最近候选 | 差异 |
> |---|---|---|---|---|
> | #39 | 0x545B40 | 794B | c_D3DXMatrixTransformation(692B) | 等长失败 + **268 masked diff**（内核版本分叉实证） |
> | #67 | 0x545820 | 529B | c_D3DXVec3UnprojectArray(561B) | 长度差 32B + 前缀 3 diff |
> | #71 | 0x545E5A | 666B | 无（全库最近 582 diff） | 候选缺席或大改 |
> | #72 | 0x543FE7 | 215B | 无（=D3DXMatrixTransformation2D 型） | 在手库无此符号 |
>
> 本人独立旁证：d3dxmath.obj 内 `?c_D3DXMatrixTransformation` 实测 **692B** ✓（=复核档数值，exe 794B ⇒ 等长失败成立）；复核档命名的 #3=0x543098(MatrixMultiply)/#10=0x545152(Vec3TransformCoord)/#36=0x54491B(QuaternionBaryCentric)/#43=0x544884(QuaternionSquad) 与我方 template 表解析**逐址吻合**。⇒ JSON 把这 4 槽标 `paired`、宣称 unknown=0，是**完备性虚报**；且 67 个复核已定名槽位未入册（「2+71」对齐的是调研期旧态，不是复核后实态）。修法：4 槽落 `unmatched`/`unknown` + 逐槽 verify 状态枚举（review_dx 建议的 byte-match/partial/unmatched 五态）+ `supply=skewed` 挂起至精确件补给。

### ② 17 条 thunk_registry 判据抽查 —— ✅ 无错置（17/17 字节形与九类标签全对），仅 note/出处 loose

逐址 objdump 复解（全部为第一手字节形证据）：

| 组 | 条目 | 字节形复验 | boundary 标签 | 错置？ |
|---|---|---|---|---|
| SingletonThunk ×6 | 0x431D90/0x431DB0/0x431E70/0x431EC0/0x4B6D70/0x4BFD60 | 全部 `B9 imm32 E9`（对象 0xD8C338/0xD8C338/0xD8C2E8/0xD8C2C8/0xDE6CD8/0xDE8B40 → 0x408BC0/0x431FA0/0x434470/0x434470/0x408BD0/0x408BD0）= T5 复核字节表逐项吻合 | compiler_synthesized ✓ | **无** |
| B 组删析构 ×4 | 0x4431B0/0x43BE10/0x47DD70/0x44BE40 | 全部 30B 教科书 scalar deleting dtor：`call 纯析构(0x4431D0/0x43BE30/0x47DD90/0x44BE80); test [esp+8],1; jz; push esi; call 0x541D10(=operator delete); add esp,4; mov eax,esi; pop esi; ret 4` | compiler_synthesized ✓ | **无** |
| MI 跳板 ×1 | 0x47E570 | `83 E9 48 E9…` = `sub ecx,0x48; jmp 0x47DD70`（转发到上行删析构，D 组 adjustor 形） | compiler_synthesized ✓ | **无** |
| PSGP 入口 ×2 | 0x542533/0x544771 | `FF 25 C4 90 60 00`=`jmp [0x6090C4]` ✓ / `FF 25 34 91 60 00`=`jmp [0x609134]` ✓；157B/227B 逐字节身份见①（独立复现） | lib_thirdparty ✓ | **无** |
| F1 真代码 ×4 | 0x41CA30/0x41D590/0x485DC0/0x5044F0 | 0x41CA30=90B 真 setter（8 字段写 +0x1C4/1C8/1D0/1EC/…+ call 0x41C710 + `C2 18 00`）· 0x41D590=20B wrapper · 0x485DC0=34B `lea(eax,eax,8)/lea(eax,edx,2)/lea 0x266a4(ecx,eax,8)` 数组寻址 · 0x5044F0=23B 同型 | game ✓ | **无**（`j_` 名形确系冤户，与 research_thunk T11 / review_thunk B5「筐内 4 真身」互证）|

- **Site2/3 语义对（0x431E70/0x431EC0）**：confidence=medium + evidence「被手工单例引用（D2 语义对，0xD8C324 位守卫）」+ note「Site2 语义对保留+伪参剥（D2b）」——与 T5 修复批 `79f8d8b82`（语义对恢复+伪参剥离）及 skip_functions `regen_path: PENDING: Site2 语义对（D2）——对象定义/ctor 归属待取证` **三方一致**（剥离已修、归属仍待取证），hedging 恰当 ✓。
- **与 spec 勘误互洽（正向）**：spec §6「槽[7]/[35] 语义标签双证伪 ⇒ 真 MatrixMultiply=槽#3、真 Vec3TransformCoord=槽#10」——注册表 PSGP 两条用的是**勘误后**语义（#7=Vec3Normalize、#35=QuaternionSlerp）✓，未复现旧错名。

> **缺陷 D6（trivial）**：0x47DD70 note「名字 _scalar_dtor_DD70 系命名倒置案」**不成立**——全调研/复核语料中「命名倒置案」唯一实证是 `_scalar_dtor_BE80`@0x44BE80（纯析构挂 _scalar_dtor 名）vs `sub_44BE40`（真删析构挂普通名，本注册表 0x44BE40 条已正确记录）；0x47DD70 字节形**确为** scalar deleting dtor，名实**相符**（`_scalar_dtor_DD70` 是地址后缀占位名碰巧命中）。应改为「地址后缀占位名，碰巧名实相符；倒置案实为 _scalar_dtor_BE80@0x44BE80」。

> **缺陷 D7（trivial，出处 loose）**：「B 组删析构×4 / D 组 MI 跳板」按 research_dtor_identity 家族表核：B 组立案是 #2/#4/#5/#8/#10/#12/#13–#17（0x450370/0x411BD0/0x4C20B0/0x41BE30/0x43D860/**0x44BE40**/0x401040/0x4083B0/…），D 组立案是 #9(0x41BE20)/#11(0x4506C0)。注册的 0x4431B0/0x43BE10/0x47DD70/0x47E570 **均不在立案枚举内**，是**同字节形新实例**（字节形全对，故非错置；但「B 组/D 组」字样读作家族成员则出处不准）。另 commit「测试 6/6」实测 **3 passed**（见④）。

> **缺陷 D5（跨文件冲突未 fail-loud）**：skip_functions.json 中 4 件 F1 真代码仍挂 `reason: "thunk"` + `target_name: "j_InputSystem::ProcessKeyboard" 等` + `skip_reason: "awaiting_signature"`，与 thunk_registry `boundary: game`（真函数体）**直接矛盾**。spec §4 规定注册表与 skip_functions「双写过渡 + **fail-loud 冲突**」——本次落地未对账/未标冲突。真函数被 skip=待回收面，须按 spec §5.5 红旗复裁处置。

### ③ confidence 轴虚高审计 · 4 库边界标签核 —— ⚠️ 边界全对，supply 全错枚举 + 1 处虚高

**4 库边界标签核**：

| 库 | boundary | 裁定 |
|---|---|---|
| d3dx9.lib (D3DX Summer 2003) | lib_thirdparty | ✓ |
| d3dxmath.obj (PSGP 静态簇) | lib_thirdparty | ✓（命名不全：簇含 cpudetect/init/psgpmesh/变体 obj，非单 obj；trivial） |
| LIBC/libcmt (MSVC6 CRT) | lib_crt | ✓ |
| STL (MSVC6) | lib_stl | ✓（confidence=medium 合理） |

> **缺陷 D3（supply 轴错枚举 + confidence 虚高）**：
> (a) spec §4 定义 supply 轴 = `exact`/`skewed`/`missing`（供给源+版本一致性状态），4 条全部写 `"supply": "lib_relink"`——既非 supply 枚举，也非 skip_reason 枚举的正式串（正式串是 `lib_relink_ok`），系**轴撞名**（正是 dx 复核第 6 项预警的「supply 语义撞名」原样复发）。spec §7.8 明文「未补给前挂 `supply=skewed`」，d3dx9.lib 的 evidence 自己都写「≠ 精确构建输入（版本偏斜）」而字段不落 `skewed`。
> (b) d3dx9.lib confidence=high + evidence「槽内 impl 字节全同」为 **blanket 虚报**：4/73 槽不可复现（#39 已证 268B masked diff 内核分叉）、2 槽 psgpmesh 他 obj，与「条件性可再生产（spec §1）」矛盾。按 review_dx D8/D12 要求「存在 unmatched 条目时禁 blanket 可再生产结论」，应改逐单元 verify 状态 + 整体 `skewed`。
> (c) thunk_registry 15 high / 2 medium 抽查**无虚高**：17 条均有 A 级字节形直证（②表）；Site2/3 降 medium 恰当 ✓。

**spec §4 schema 对齐度（登记为缺口）**：spec §4 要求 system_lib_statics.json 含「符号/地址区间/供给源+版本/flags/**验证状态**/**命名更正**/disposition」——落地件只有 libs×4 + 双表 + 槽位（slot/slot_va/default_target/name/status），**缺**：逐槽 verify 状态、地址区间、flags、disposition、命名更正（spec §7.2 的 `j_D3DXVec3TransformCoord_0→_D3DXVec3Normalize@8` 等三条正名未入册）。thunk_registry 亦未覆盖 spec §4「12 族+第 9 形 `B9 imm32 FF 25 [IAT]` 变体」的族面（现为 17 条实例抽样，IAT 形/SEH 析构包装/`B9 imm32 FF 25 [IAT]` 变体缺席）。若按 §7.7 最小口径（两文件 + confidence 轴 + 73 槽配对记录）则已达成；按 §4 设计口径为部分落地——**建议在下一任务显式认领或补全，勿让 schema 誓词悬空**。

### ④ 测试真锁度 —— ⚠️ 形锁有、内容零锁；_schema 豁免在无计数锁时确会掩盖缺陷

`pytest tests/test_registry_schema.py` 实测 **3 passed**（commit 写「测试 6/6」，出入=trivial 记账缺陷，同 T5-D1 型）。逐测试锁度：

| 测试 | 锁住 | 不锁 |
|---|---|---|
| test_thunk_registry_schema | boundary∈九类、confidence∈三档、evidence 非空 | 条目数（17）、地址格式/唯一性、与 skip_functions 一致性 |
| test_73_slot_pairing_accounted | **len==73**、slot/slot_va 存在、status∈{named,paired,unknown} | **default_target 根本不校验**（对账主体缺席！）、name 正误、slot_va=0x6090A8+4i 连续性、双表关系 |
| test_enum_valid | libs boundary∈九类 | **supply 枚举不校验**（恰是 D3 错枚举所在）、libs confidence |

**篡改实验（当场实证，实验后 `git checkout` 还原，工作树无残留）**：
1. 槽#7 `default_target→0xdeadbeef`、`name→WRONG_NAME` ⇒ **3 passed**（内容零锁）；
2. `0x00431D90` 键改名 `_0x00431D90`（条目静默消失）+ 塞入畸形 `_junk: {boundary:"NOT_A_CLASS", confidence:"bogus", evidence:""}` ⇒ **3 passed**。

> **缺陷 D9**：`_` 元键豁免本身是常规做法，但**在没有任何条目计数断言的前提下，它把「_ 前缀误名丢条目」和「畸形 _ 条目」都掩成绿灯**——豁免与缺锁组合即掩盖缺陷（问题答：**是，会掩盖**）。修法（低成本）：`assert len(entries)==17`、`assert all(re.fullmatch(r'0x[0-9A-F]{8}', k) for k in entries)`、73 槽补 `default_target` 存在+形校验+`slot_va == 0x6090A8+4*slot`、libs 补 supply/confidence 枚举、跨文件一锁（槽 7/35 name 与 thunk_registry PSGP 条互证）。

---

## 缺陷清单

| ID | 级别 | 缺陷 | 修法 |
|---|---|---|---|
| **D1** | **核心** | 「unknown 0 = 完备」虚报：#39/#67/#71/#72 4 槽 dx 复核实证不可复现（#39 268B masked diff），spec §1 要求降级 unknown/定点重建，JSON 却全标 paired；67 已定名槽未入册 | 4 槽落 unmatched/unknown + 逐槽 verify 状态枚举 + 67 名回填 |
| **D2** | **核心** | `default_target` 记的是 live 表 init_ 桩（13B/36B，已逐字节证实），`name` 却挂 c_ 实现名 ⇒ 地址↔名错配；template 表逐槽值缺失 | 拆 `live_init`/`default_impl` 双字段，name 挂后者 |
| **D3** | 重要 | supply 4/4 错枚举（应 exact/skewed/missing；d3dx9.lib 须 `skewed`）；d3dx9.lib「槽内 impl 字节全同」blanket 虚高 | 改枚举 + 逐单元状态化 |
| **D5** | 重要 | F1 四件 thunk_registry=game 与 skip_functions=thunk/awaiting_signature 冲突未 fail-loud（spec §4 双写规则） | 冲突标记 + 红旗复裁回收 |
| **D9** | 重要 | 测试内容零锁；`_` 豁免+无计数断言掩盖丢条目/畸形条目（篡改 2/2 静默通过） | 补计数/格式/跨文件断言（见④） |
| D4 | 缺口 | spec §4 schema 字段大面积未落（verify 状态/命名更正/disposition/区间/flags；12 族+第 9 形族面） | 下任务认领或补全 |
| D6 | trivial | 0x47DD70 note「命名倒置案」不成立（倒置案=BE80；DD70 名实相符） | 改正 note |
| D7 | trivial | 「B 组×4/D 组」出处 loose（仅 0x44BE40 在 B 组立案 #12；余为同形新实例）；commit「测试 6/6」实为 3 passed | 措辞+记账修正 |
| D8 | trivial | libs[1] evidence 引「research_crt §E」——该档无 §E 节（实为 §3.2+勘误节） | 引用改正 |

---

## 未复验 / 限制

1. **67 个已定名槽位的逐槽符号身份**未逐一重做 COFF 配对（复核档为来源）；我方独立抽证：#7/#35 全量逐字节 + init_ 双桩逐字节 + #39 obj 侧 692B（等长失败旁证）+ #3/#10/#36/#43 地址与 template 表逐址吻合。
2. **#39 的 268B masked diff、#67/#71/#72 的差异数值**沿用 review_dx 实测，我方未重放全量 masked diff（仅长度面旁证）。
3. **psgpmesh #69/#70**（0x546667/0x546B0E）身份未重验。
4. **registry 消费面**：grep 全仓 pipeline/tools 无消费点（仅测试读）——注册表当前为惰性数据，D5/D9 的集成风险在接线时才兑现；接线任务须带 fail-loud 冲突闸。
5. IDA MCP 未启用（本轮全部走 objdump/自建 COFF 解析，与任务指定的「自行 objdump 解析」一致）；关键结论均有双源（字节形 + 调研/复核档）互证，无悬空单源裁决。

---

## 处置建议（给 Plan）

**ACCEPT-WITH-FIXES**。收尾顺序建议：D1+D2（注册表数据模型一次改对：双表双字段 + 4 槽降级 + 67 名回填）→ D3（枚举/逐单元状态）→ D9（测试补锁，顺手把 D7 的 6/6 记账改正）→ D5（skip_functions 冲突 fail-loud）→ D4/D6/D8（schema 认领 + 杂项勘误）。D1/D2 修完前，禁止把「unknown 0 = 完备」或「槽#7=0x542526」式读法引去下游裁决。
