# 对抗性复核：DX/系统库静态件边界调研（research_dx_static_boundary_20261028.md）

> 2026-10-28 · 独立攻击式复核（复核员≠调研员）。只写此一个文件；全部实验在 `/tmp/review_dx/` 只读复现
> （自写 COFF 解析/比对脚本，**不依赖**被复核方 `/tmp/dx_research/coff_cmp2.py` 的输出，仅交叉对读）。
> IDA 取证走 `mcp__idapro__*`（复用 session `278944bc`，`original/PAL3.exe.i64`）。
> 复核立场：不信任报告，只信实测；抽验不到者标「未复验」。

---

## 1. 复核总结

**ACCEPT-WITH-FIXES** —— 报告核心反转（D3DX=静态 PSGP 面、三条 `j_D3DX*` 全错名）经独立字节+语义双重实测**成立**，
且与姊妹报告（thunk）的矛盾以本报告为对；但「头内联逐字节同」实为 14B 片段命中（表述过强、16B/12B 自相矛盾）、
hidden diff 未按姊妹口径量化、以及「风险收敛为 73 槽脚手架 + 2 表项」低估了残差（实测 73 槽中 **4 个 default 实现体在手库无法复现**）——三处须修正后方可作为边界裁决底稿。

---

## 2. 逐项 verdict 表

| # | 复验项 | verdict | 一句话依据 |
|---|---|---|---|
| 1 | 三条 `j_D3DX*` 错名裁定 + 与 thunk 报告矛盾裁决 | **CONFIRMED** | ①0x4B8200=游戏 rand-lerp（23 指令语义 + 11 xref）✓ ②0x542533→`jmp[0x6090C4]`槽#7→0x5450B5=c_D3DXVec3Normalize 157B 逐字节同 ✓ ③0x544771→`jmp[0x609134]`槽#35→0x544777=c_D3DXQuaternionSlerp 227B 逐字节同 ✓；thunk 报告「矩阵×向量变换/矩阵乘法」语义猜测被字节+反编译双证**证伪**（真 MatrixMultiply=槽#3 @0x543098/566B，真 Vec3TransformCoord=槽#10 @0x545152/188B） |
| 2 | 字节等同实验方法学 | **PARTIAL** | coff_cmp2.py 可复跑 ✓（我方独立重实现同结果）；MSVC6 wine cl 重跑 .text 全同 ✓；**但 hidden diff 未量化**（本复核补：3 例共 31/471B 被 reloc 免比吞掉，6.6%）；例 D「头内联逐字节同」**过强**——实测最大等长仅 **14B 前向/0B 反向**，其后指令交错即分叉；且摘要「16B 核心序列」与 §3.2「12B+」自相矛盾 |
| 3 | 版本偏斜 | **PARTIAL** | ①73 vs 71 槽 **CONFIRMED**（exe `push 49h`+双 73 项表；cpudetect.obj `push $0x47`）②new/delete 检查 0x547B27 + 4 WARN 串 **CONFIRMED**（反编译逐句吻合；在手库确无该串）③「在手库≠精确构建输入」结论成立且**实际更强**：73 槽 default 目标全量配对实测 **69/73 在手库可复现，4 个不可复现**（#39/#67/#71/#72，见 §3.3）——「风险收敛=73 槽脚手架+2 表项」**低估残差** |
| 4 | 其它系统库裁决 | **CONFIRMED** | exe 导入 7 DLL 零 D3DX ✓；Bink(10 符号)/DINPUT8(DirectInput8Create) 导入表实证 ≥2 ✓；gbengine→mss32/ijl15/topo/d3d9 ✓；libpng/zlib 串在 gbengine 不在 exe（exe 0 命中）✓；d3dx9.lib 确含 libpng 1.0.5+zlib 1.1.4 成员（png\*/deflate\*/inflate\* obj）⇒推测依据成立（gbengine 链接归属仍属推测）；topo/ + original/build/（topo.dll/lib/map）重建线存在 ✓ |
| 5 | \_\_m64/\_\_m128 簇归类 | **CONFIRMED**（附注） | 3 安装器仅被 0x546F41 单点调用，门控 PF(6)=SSE→0x547042(状态3) / CPUID SSE2→0x5471BA(状态2) / PF(7)=3DNow→0x54740C(状态1)，与 sse_/sse2_/x3d_D3DXInitFastTable 对应 ✓「归 D3DX PSGP 变体件」成立；附注：安装器与在手库仅**近似**字节同（1–3 处 masked diff + 长度差 376/366/634 vs 366/356/654），亦带版本偏斜 |
| 6 | schema/spec 攻击 | **PARTIAL** | system_lib_statics.json 尚不存在（纯提案）；与 crt 报告 boundary/supply/skip 三轴**粒度不同但 `supply` 语义撞名**；dx schema 缺证据等级/confidence 字段与 check_annotations 校验挂钩；四步验证环对「精确件不可得」**未闭环**（无条目落库、无逐单元 verify 状态强制）；命名更正环仅「提议」不落改——与 annotation 纪律自洽 ✓，但**缺跨报告冲突的裁决/勘误机制**（thunk 报告错名仍留存在册） |
| 7 | 数字审计 | **PARTIAL** | 157/227/87 ✓（独立测量同值）；3 reloc 站点 ✓（0x3B/0x56/0x6B、0x2D/0x56/0x67、0x18/0x2E/0x4C=十进 59/86/107、45/86/103、24/46/76 与报告逐一对上）；73 槽 ✓（`push 49h`+表跨 0x6090A8–0x6091CB/0x6091D0–0x6092F3+哨兵 0xFFFF）；205 库成员 ✓（208 归档条目−`/`×2−`//`）；214 D3DXINLINE ✓；库 4,383,332B ✓；**「782 符号」（thunk 报告）不可复现**（全库唯一 D3DX 符号 3876、d3dxmath.obj 符号条目 917，计数口径未声明）；「16B 核心序列」数字错（实测 14B 上限） |
| 8 | 完备性 | **PARTIAL→大幅可改善** | 「73 槽只命名 2 项」经本复核全量配对**基本可闭**（67 槽精确命名 + #69/#70=psgpmesh 件；报告自己的环 2 方法即可做）；但闭合后暴露 4 个不可复现实现体 ⇒ 头内联抽样窄（3 算符仅 1 命中且非全同）+ 内核 blanket「可再生产」需改为**逐单元状态**（byte-match / partial / unmatched） |

---

## 3. 跨报告矛盾裁决专节

### 3.1 0x5450B5 / 0x544777 身份（thunk 报告 vs 本报告）——裁决：**本报告对，thunk 报告错**

thunk 报告（`research_thunk_mechanism_20261028.md:83`）称：
「槽[7] tmpl=0x5450B5（字节 `55 8B EC 83 EC 0C 56 8B 75 0C D9 46 08 …` = **矩阵×向量变换真身**）、
槽[35] tmpl=0x544777（**矩阵乘法真身**）」；`:143` 进一步称「槽7=真 D3DXVec3TransformCoord 分发位」。

独立复验（以 d3dx9.lib 符号字节为准 + 反编译语义双证）：

1. **字节证据**（自写 COFF 解析 + 三限定比对，与被复核方脚本独立）：
   - 0x5450B5（157B）↔ `?c_D3DXVec3Normalize@@YGPAUD3DXVECTOR3@@PAU1@PBU1@@Z`（d3dxmath.obj 节 542，157B，reloc [0x3B,0x56,0x6B]）：masked mismatch **0**；
   - 0x544777（227B）↔ `?c_D3DXQuaternionSlerp@@YGPAUD3DXQUATERNION@@PAU1@PBU1@1M@Z`（节 453，227B，reloc [0x2D,0x56,0x67]）：masked mismatch **0**；
   - 反证长度：`c_D3DXVec3TransformCoord`=节 544/**188B**、`c_D3DXMatrixMultiply`=节 237/**566B**——与 157/227 均不等长，三限定下**根本不可能配对**。
2. **语义证据**（反编译）：0x5450B5 = `dot(v,v)→Float_AlmostEqual→1/sqrt→分量缩放`（=Vec3Normalize）；
   0x544777 = `四元数点积→符号修正→atan2/sin 球面插值（4 分量）`（=QuaternionSlerp）。
   thunk 报告引的前缀 `D9 46 08`（`fld [esi+8]`）恰是 3-向量 z 分量点积起步——与「矩阵×向量」（应读 4×4 行）不符。
   调用面：sub_544884（=c_D3DXQuaternionSquad，87B 逐字节同）恰在 reloc 站点 24/46/76 三处 `call 0x544771`
   （实测 rel32 目标 0x54489B/0x5448B1/0x5448CF→0x544771）＝Slerp×3，与 d3dx9math.h `D3DXQuaternionSquad` 定义吻合。
3. **正名归位**（本复核全量 73 槽配对，见 §3.3 表）：真 `c_D3DXMatrixMultiply` 在 **槽#3 @0x543098**，
   真 `c_D3DXVec3TransformCoord` 在 **槽#10 @0x545152** —— 均另行字节落位。
   thunk 报告把两者的语义按「名字像什么」贴到了槽#7/#35 上（其 `j_*` 拆分框架本身没错，槽位语义标签错）。

⇒ **定谳**：以库符号字节为准的本报告正确；thunk 报告槽位语义标签应出勘误（§4 缺陷 D1）。
另：报告 §2.2 提议的更正名 `_D3DXVec3Normalize@8` 与库内真实 extern 拼写一致（实测 `_D3DXVec3Normalize@8` 在 d3dxmath.obj 等 9 个成员中作为 undefined extern 出现）✓。

### 3.2 与 `research_crt_boundary_20261028.md` / `crt_skip_census_20261028.md`

- PSGP 分发表 0x6090A8 / 初始化器 0x546F41 的定性：crt 报告 `:119`「73 入口函数指针表一次性初始化
  （rep movsd 0x6091D0→0x6090A8，sentinel dword_6092F8=0xFFFF）」与本报告**一致**，本次实测复核成立 ✓（无矛盾）。
- **但** crt 报告 `:113/:115` 把 `push 1; call …; jmp [tbl]` 13B 桩标为「C（scalar deleting destructor thunk）」
  （例 `crt_sub_005424BA`）——实测该 `call` 目标是 `_D3DXCpuOptimizations@4`（0x546F41，注册表 DisablePSGP 读取+
  表拷贝+CPU 安装器分派），**不是析构/delete**，此形状类标签应更正为「PSGP 惰性初始化桩」（本报告 §2.1 的
  「push 1; call 0x546F41; jmp [slot]」描述为对）。crt 报告 `:240` 遗留的「??3@YAXPAX@Z 出现在 0x546F41 首行」
  亦由本次实测闭合：那是 0x546F41 调 **0x547B27**（IDA 错名 `??3@YAXPAX@Z_0`，实为 new/delete 一致性检查）。
- crt_skip_census 的 `__m64/__m128::_static_*` 归类更正（census `:52` 已采纳本报告口径）——本次实测支持 ✓。

### 3.3 与 `research_dtor_identity_20261028.md`

全文 grep 无 `j_D3DX`/D3DX 引用 ⇒ **无冲突**。其「命名不可信、判据回字节形」总纲与本报告互相印证。

### 3.4 本复核新增：73 槽 default 目标全量配对（对报告 §6.1「只命名 2 项」的实测闭合）

用 d3dx9.lib 全部 205 成员（11077 个 .text COMDAT 符号索引）对 73 个 default 目标做三限定全配：

- **67/73 精确命名**（等长 + masked diff=0），与报告已命名 2 项吻合（#7=Vec3Normalize、#35=QuaternionSlerp ✓）；
  其余例：#3=MatrixMultiply(0x543098)、#10=Vec3TransformCoord(0x545152)、#43=QuaternionSquad(0x544884)、
  #36=QuaternionBaryCentric(0x54491B，恰为 0x544771 的另 3 处调用者)…（#8/#20 为 QuaternionNormalize/Vec4Normalize
  COMDAT 折叠二义，两可）；
- **2/73** = psgpmesh.obj：#69(0x546667)=`c_D3DXPSGPUpdateSkinnedMesh`(1034B)、#70(0x546B0E)=`c_D3DXPSGPTessellateNPatch`(817B)；
- **4/73 在手库不可复现**：
  | 槽 | exe | IDA 长度 | 最近候选 | 差异 |
  |---|---|---|---|---|
  | #39 | 0x545B40 | 794B | `c_D3DXMatrixTransformation`(692B) | 等长失败 + **268 masked diff**（内核函数版本分叉实证） |
  | #67 | 0x545820 | 529B | `c_D3DXVec3UnprojectArray`(561B) | 长度差 32B + 前缀 3 diff |
  | #71 | 0x545E5A | 666B | 无（全库最近=582 diff） | 候选缺席或大改 |
  | #72 | 0x543FE7 | 215B | 无（语义=D3DXMatrixTransformation2D 型，在手库**无此符号**） | 库缺席 |

另闭合报告 §6.2 遗留项：0x54474D = `?init_D3DXQuaternionSlerp`（36B，masked diff=0）——报告「未做逐字节配对（待核）」可直接关单。

⇒ 「73 槽脚手架 + 2 新增表项」的收敛说法**部分成立**：脚手架侧成立（73 槽可全量枚举命名），
但实现体侧残差是 **4 个不可复现函数体**（≥2 个疑似新/改函数 + ≥1 个已证内核分叉），不是 2 个表项。

---

## 4. 缺陷清单（按 矛盾 > 实验方法学 > 证据不足 > spec 缺口 排序）

**矛盾类**
- **D1（跨报告）**：thunk 报告槽#7/#35 语义标签与字节证据直接冲突（§3.1）。本报告已指出冲突但只给了自己的正名，
  未给出「真 MatrixMultiply/Vec3TransformCoord 落位」这类**排他性证据**（本复核 §3.4 补齐）。
  建议向 thunk 报告发勘误（erratum），并把「槽位语义以库符号字节配对为准、禁止按名字推断」写进共享纪律。
- **D2（报告内部）**：头内联序列长度自相矛盾——摘要 §1「16B 核心序列」vs §3.2 例 D「12B+」vs 本复核实测 **14B 上限**。
- **D3（报告内部）**：「头内联 D3DXVECTOR3::operator- 与 MSVC6 TU 产物**逐字节同**」表述过强：
  实测 exe@0x41380B 与 TU `f_vec_sub` 体自 `d9 00` 起前向仅 **14B** 连续相等（反向 0B），其后 TU 插 `fstps 4(esp)`、
  exe 插 `mov edx,[esp]` 即分叉——同源同头同 flags 但**指令交错不同**（上下文寄存器分配，与报告解释 operator+ 0 命中
  的理由同因）。⇒ 该实验只支撑「14B 片段同源」，不支撑「展开逐字节同」；例 D 的「✅ 头内联字节同」应降级为 partial。
- **D4（数字）**：成员时间戳「2002-12-11 13:23（obj/i386/\*.obj）」过度概括——实测 d3dxmath/cpudetect 为 2002-12-11，
  d3dxmathx3d/sse/sse2 为 2002-12-04（小错，但影响「同一次构建」直觉）。

**实验方法学类**
- **D5**：hidden diff 未按姊妹复核口径量化。本复核补测（三限定吞了多少）：
  | 例 | 比对字节 | reloc 覆盖 | **实差但被免比（hidden）** | masked mismatch |
  |---|---|---|---|---|
  | Vec3Normalize 157B | 157 | 12 | **10** | 0 |
  | QuaternionSlerp 227B | 227 | 12 | **9** | 0 |
  | QuaternionSquad 87B | 87 | 12 | **12** | 0 |
  | 合计 | 471 | 36（7.6%） | **31（6.6%）** | 0 |
  即 reloc 免比字节的 86% 双侧真不同（均为 call rel32 目标地址差，良性），但**引用「字节全同」必须带此三限定+hidden 数字**，
  报告只写了 reloc-covered=12 未写 hidden。
- **D6**：例 D 实验的「同 flags 同头」条件本身**可复现**（本复核重跑 wine cl：4 个 .text COMDAT 80/80/48/80B 与原 obj 全同；
  obj 文件 1564→1582B 差异在符号/路径串，不影响代码）——这部分无缺陷，列此以示「表述过强≠实验不可复现」。
- **D7**：0x542533 调用面「未逐调用点复核」（报告自认 §6.3）——本复核抽验 1 处：`sg_emission_control` 调用点
  上下文为粒子发射随机化（rand-lerp × 缩放），与 `_D3DXVec3Normalize@8` 语义相容；但 Normalize 的 stdcall @8
  与该处调用的参数编组未逐点对账，维持「未全部复验」。

**证据不足类**
- **D8**：「内核面=可再生产」以 3 例外推整个 d3dxmath 内核；本复核证明至少 1 个内核函数（MatrixTransformation 家族）
  在手库/exe 分叉（§3.4），2 个函数在手库缺席 ⇒ 该结论应改为「已抽样 N 个 byte-match；73 槽全量中 4 个不可复现」。
- **D9**：三安装器「分别对应 sse_/sse2_/x3d_」结论正确（门控+状态字实证）但报告未附该证据链；
  字节层仅近似（1–3 diff + 长度差），报告若暗示同版供给应注明偏斜。
- **D10**：0x5450B5/0x544777 的 hidden diff 未量化（并入 D5）。

**spec 缺口类**
- **D11**：`system_lib_statics.json` schema 无 `confidence`/证据等级字段，与 crt 报告 §4.2「无证据不得入库」红线及
  check_annotations 校验未挂钩；`supply` 字段名与 crt 三轴 schema 撞名异义（dx=路径+exact_version_match，
  crt=source_rebuild|lib_relink|compiler_regenerated 枚举）。
- **D12**：四步验证环对「精确件不可得」不闭环：环 1 只处理 mismatch→降级，不处理 **unmatched/unreproducible**
  （恰是本次 4 槽的处境）；无逐单元登记强制，导致「内核可再生产」这种 blanket 结论无法被环自动驳回。
- **D13**：命名更正环（环 4）缺**跨报告勘误机制**：j_D3DX 三例更正后，thunk 报告的槽位错名仍无流程强制修正
  （annotation 纪律管不到 status 报告），本次 D1 即实例。

---

## 5. spec/schema 补丁建议

1. **verify 状态扩枚举 + 逐单元强制**：`verify.status ∈ {byte-match, byte-match-exact-version, partial-match, unmatched, unverified}`；
   每个 PSGP 槽位/函数体一条目（73 槽全量），`disposition` 由状态机器导出（`unmatched ⇒ reverse-edge`），
   禁止在存在 unmatched 条目时给上层 blanket `no-reverse-needed`（D8/D12 的闸）。
2. **hidden diff 计量入 evidence**：`evidence[]` 增 `reloc_covered_bytes / hidden_diff_bytes` 两字段，
   引用「字节全同」必须三限定+hidden 数字随行（对齐姊妹口径，D5）。
3. **confidence 轴对齐 crt 报告**：条目带 `evidence_grade ∈ {A,B,C}`（字节配对=A 级；语义推测=C 级），
   并把 `system_lib_statics.json` 的校验挂进 check_annotations 或独立 lint（D11）。
4. **supply 撞名消歧**：dx schema 的 `supply` 改名 `supply_source`，或在两 schema 间建映射表文档；
   `exact_version_match=false` 必须列**实测偏斜清单**（如「73v71；#39 268B diff；#71/#72 缺席」而非泛称）。
5. **跨报告勘误流程**：review 发现错名/错语义 → 在被引报告头部加 erratum 块（指向裁决报告 §3.x）+
   `data/status/_errata_index.md` 登记；本复核 D1 应即刻走此流程（thunk 报告 :83/:143）。
6. **环 2 批量配对固化**：把本复核 §3.4 的「default 表全量×库 COMDAT 索引」配对脚本纳入管线工具
   （一次跑出 73 槽名表 + unmatched 清单），使「只命名 2 项」类完备性缺口不再靠人工收敛。

---

## 6. 未复验清单（显式）

1. **§3.4 网络下载尝试**（archive.org DNS 污染、legacyupdate 403、GitHub 镜像无 Summer 2003）——未重测可达性；
   「精确件暂未到手」依赖此叙述，未独立复验。
2. **d3dx9d.lib / d3dx9dt.lib `push 0x47`=71 项**——未抽查。
3. **gbengine.dll 内 `"Microsoft (R) D3DX9 Shader Assembler 4.09.00.1126"` 版本横幅**——未抽查。
4. **PAL3A PDB 逐符号地址**（0x32462a/0x32e83e 等）——只验了家族存在（PSGP 特征串 198 命中、`j_D3DX*` 0 命中），未逐址核对。
5. **「782 符号」计数口径**（thunk 报告数字）——本复核三种口径均不吻合（全库唯一 D3DX 符号 3876 / d3dxmath.obj 917 条目），标未复验。
6. **0x546F41「86 条指令」精确计数、`dword_6092F8 reloc -4 偏差`细节**——未逐条核。
7. **gbengine.def 内容、gbengine.dll↔d3dx9.lib 字节比对**（libpng/zlib 链接归属）——报告自标推测，维持推测。
8. **0x542533 全部 5 处调用点的参数编组逐点核对**（仅抽验 1 处，见 D7）。
9. **头内联 operator+/operator\*(scale) 的「未抽到同型样本」**——未做更宽的形态检索（报告已自认待做）。
