# R4 实施 A（修订写面）：ScreenEffectMgr 洞区落位（首版 T1+T2）交付报告

- 卡：#15 `tsk_01M8C1ZDQNR1H37ETYZNDJ`（替代 #13；#13 内容与本卡完全一致，仅报告落点原为 data/status/）
- 日期：2026-11-26 23:20
- 前置：#2 诊断 `docs/specs/2026-11-26-r4-screen-effect-mgr-hole-diagnosis.md`；#16 共享管线修复（apply 段 `gb_sig_*` NameError）已验收 done
- 本批边界（#13 Thread seq1 声明，本卡沿用）：T1 `0x454–0x58DC0` ParticleEffect 362,860B；T2 `0xA4/0xA8 + 0xB0–0x454` 940B；合计 **363,800B**。⚠️ 口径精确化（独立复核提出）：363,800 是**本批成员尺寸之和/洞字节下降量**，不是「从 0xa4 到 0x58DC0 的跨度」（实际跨度 363,804B，差 0xac–0xb0 的 4B 洞），也不是类尺寸（363,968B）。留白 20B：`0x90–0x94` 4B、`0x98–0xA4` 12B、`0xAC–0xB0` 4B；头区 `0x4–0x90` 归属矛盾（ev_0006）不在本批。

## 1. 落位结果（10 个成员，全部 evidence_level=A）

文件：`data/annotations/structs/ScreenEffectMgr.json`（+60 行，只追加，未重排既有成员，0x0 的 m_pVtable 仍在文件末尾以减小 diff）。
脚本（可复跑、幂等、干跑默认）：`data/status/archive/r4_screen_effect_placement_20261126.py`。

| 偏移 | 类型 | 名称 | 关键 A 级证据（地址可 objdump 复现） |
|---|---|---|---|
| 0xa4 | int | m_nGeometryReady | ctor `0x4BEE8C movl $0,0xa4`；LoadResources `0x4BF11B movl $1,0xa4`；CleanupTextures `0x4BF19E` 清 0 |
| 0xa8 | gbRenderEffect * | m_pGeomRenderEffect | ctor `0x4BEF07` 置 0；`0x4BF0ED` 存 NewRenderEffect 返回值；`0x4BF17D/0x4BF189` 取回/释放 |
| 0xb0 | gbGeomQuad[6] | m_ringQuadsLarge | ctor `0x4BEE96 lea 0xb0` + 6×(`call 0x401810` + `add $0x44`)；6×68=0x198 ⇒ 0x248 闭合 |
| 0x248 | gbGeomQuad[6] | m_ringQuadsSmall | ctor `0x4BEEB7 lea 0x248` 同构；⇒ 0x3E0 闭合 |
| 0x3e0 | gbGeomQuad | m_singleQuad | ctor `0x4BEED9 lea 0x3e0` + 4×(`call *0x56a56c` + `add $0xc`) 构造 gbVec3D[4]；color@0x420（Render `0x4BF4C4`）；⇒ 0x424 |
| 0x424 | float | m_fAnimTime | UpdateAnimation `0x4BF519 fadds`/`0x4BF51F fsts`；`0x4BF531` 重置 4.0f（0x40800000） |
| 0x428 | float | m_fAnimSpeed | `0x4BF587 fstps 0x428`；Render `0x4BF3CE lea 0x428` |
| 0x42c | float[6] | m_aAnimCurve | `0x4BF593 lea 0x42c` + `0x4BF610 add $0x8` ×3（cur 0x42C/0x434/0x43C，派生 0x430/0x438/0x440）；GetPageIndex `0x4BF695 rep stos` ecx=8 从 0x424 清 8 dword |
| 0x444 | int[4] | m_aAnimFlags | `0x4BF53B` 写 0x444=1、`0x4BF572` 读比较；`0x4BF58D lea 0x448` + `add $0x4` 三元素；GetPageIndex `0x4BF69A add $0x444` 清 4 dword ⇒ 0x454 |
| 0x454 | ParticleEffect | m_particleEffect | ctor `0x4BEEF2 lea 0x454` + `0x4BEEF8 call 0x4bc760`；0x454+362860=0x58DC0=363968 与工厂 `0x4B7121 push $0x58dc0` 闭合 |

命名说明：初版 `m_ringQuadsA/B` 被 check 的伪语义门禁拦下（「尾部大写单字母 A–E = CachedA/B 族残种形态，禁止新增」），改为 `m_ringQuadsLarge/Small`，source 明确「仅指 GenerateRingMesh 半径对 41.0/28.0 大于 34.0/18.0，不声称外/内环语义」。

## 2. 门禁与读数（#16 修好后重跑，2026-11-26 23:07–23:15）

| 项 | 结果 | 证据 |
|---|---|---|
| `cli.py check` | **PASS**：`0 new errors + 37 frozen(advisory), 109 warnings`，EXIT=0 | 23:16 复跑；无 ScreenEffectMgr 相关 WARN；MemberExtent 仍只有既存 scVARIANT_data 越界 1 个（本批成员末端=0x58DC0=binary_size，不越界） |
| apply | **rc=0 / 15.6s**（#16 修复后，不再有 `[!] import slot signature pass raised`） | `data/status/archive/r4_sefmgr_loop_after16_20261126.log` |
| export | **rc=0 / 149.0s** | 同上 |
| codegen all | rc=1 / 189.7s —— **已知恒红**（loop 显式标 TOLERATED，非本卡） | 同上 |
| probe all | rc=1 / 91.8s —— **外部原因，非本卡**：`tools/regression_detector.py --check --report`（23:12）判「新失败 0」；真新增 6 条全在 `pal3/src/Misc/SaleUI.cpp`（C2107×4 + C2102×2，L755/L756/L9268，属 #9 在途落位）；同时 `pal3/src/Misc/RoleStatePanel.cpp` 已修复。S2 = **158/229**（与 #13 时一致，本批未引入新失败） | regression report 输出贴 #15 Thread |
| match | **单独执行 rc=0**（probe 中止后的独立补跑，23:15）：`matched 1152/1262 | L1 189 | partial 827 | unmatched 245 | unresolved-synth 136`；`[metric] L1 字节 8196 / 重定位覆盖 2308 (28.2%) / 隐藏差异 1646 (20.1% L1 / 71.3% reloc)`；`[metric] 重定位站点值 total=8067 ok=1910 mismatch=0`；**`ScreenEffectMgr.cpp funcs=42 matched=30 L1=2 partial=27`**；无 REGRESSION、无丢失函数 | `data/status/archive/r4_sefmgr_match_after16_20261126.log` |
| L1 棘轮 | `previous 189 -> current 189`（未退化）；`semantic 13 -> 13`（L1+sem 202→202）；`population matched 1152/1262 -> 1152/1262`；`coverage carrier.paired 93 -> 93` | 同上 |
| 基线 | **未执行 `--rebaseline`**；L1 锚点保持 189，population 未变因此本轮无「可比总体变化」提示 | 同上 |

## 3. census v3 逐段闭合

重跑：`python3 tools/census_struct_holes.py`（23:15，loop 之后）。产物 `data/status/struct_holes_20261125.json`（sha256 `0574dc75b8b41085d226f4cd30dc65aaa44e4d4e403e60942707390f1aa7323c`），本批快照 `data/status/archive/struct_holes_after_sefmgr_20261126.json`。

| 段 | 偏移–长度 | 下降字节 | 闭合 |
|---|---|---|---|
| T1 | 0x454–0x58DC0 362,860B | 362,860 | ✅ |
| T2-a | 0xB0–0x248 408B | 408 | ✅ |
| T2-b | 0x248–0x3E0 408B | 408 | ✅ |
| T2-c | 0x3E0–0x424 68B | 68 | ✅ |
| T2-d | 0x424–0x454 48B | 48 | ✅ |
| T2-e | 0xA4 + 0xA8 = 8B | 8 | ✅ |
| 合计 | | **363,800** | 与批次清单和值精确相等（= 洞字节 363,820→20 的下降量；非跨度、非类尺寸） |

结果：ScreenEffectMgr `members 16→26`，`holes [[0x90,0x94,4],[0x98,0xa4,12],[0xac,0xb0,4]]`，`hole_bytes 363,820 → 20`（**仅剩声明的 20B 留白**）；全库 201 类 / 1,123 洞 / **875,232B**（本批前 1,239,032B，差 363,800）。`size 363968` 不变。

独立自检（不复用落位脚本的探针逻辑）：26 成员、`max_end 0x58dc0 == binary_size 0x58dc0`、无重叠、三个洞均未被成员 claim、链式等式 `0xb0+6g=0x248` / `0x248+6g=0x3e0` / `0x3e0+g=0x424` / `0x424+4+4+24+16=0x454` / `0x454+362860=0x58dc0` 全部成立、10 个新成员 source 均含 0x 地址。

## 4. 未覆盖 / 后续

- `0x90–0x94`（4B）：**不是「没被用过」而是「归属未定」**——另一 ctor `sub_4BDFB0`（vtable `0x56F508`，与 ScreenEffectMgr 的 `0x56F580` 不同）在 `0x4BE032 mov DWORD PTR [esi+0x90],edi`（edi=0）写过该槽，并构造 +4/+0x20/+0x38/+0x50 四个 fade 子对象；该 ctor 的类归属与 ScreenEffectMgr 的关系即 ev_0006 的矛盾（ScreenEffect/ScreenEffectNode 侧），故本批留白不命名，交 #2 后继逐案裁决。
- `0x98–0xA4`（12B）、`0xAC–0xB0`（4B）：`0x4BDF30–0x4BF7E0` 全方法扫描对 `[reg+0x98/0x9c/0xa0/0xac]` **零命中**；本批留白、不命名。
- 头区 `0x4–0x90` 归属矛盾（ev_0006：ctor 调 PAL3VisNode ctor，与注解 bases 空 / vtable base=UIRoleDialog 冲突）：不在本批，需单独裁决。
- `ParticleEffect` 自身 1 洞 4B（0x58950–0x58954，非本批）。
- 外部红：`SaleUI.cpp` 6 条真新增错误（#9 在途）；待 #9 收敛后 probe 可望转绿，本卡不重锚、不代修。
- probe 全链 rc=0 在 #9 收敛前无法达成；已按 PMO seq4 第 4 条附归因记录（新失败 0 + 真新增全在 SaleUI.cpp + S2 持平）。

## 5. Evidence（台账）

- `ev_0005`（A/open）：ScreenEffectMgr 355KB 洞分解（#2 产出，本卡实施依据）
- `ev_0006`（B/open）：头区 0x4–0x90 归属矛盾（本批不涉）
- 本卡新增登记：`ev_0011`（A/open）本批 10 成员落位与逐段闭合；`ev_0012`（A/open）loop 门禁读数与外部红归因

## 6. 复现命令

```bash
python3 data/status/archive/r4_screen_effect_placement_20261126.py            # 干跑
python3 data/status/archive/r4_screen_effect_placement_20261126.py --apply    # 写盘（幂等）
python3 pipeline/cli.py check
ps aux | grep -E "pipeline/cli\.py" | grep -v grep      # loop 前确认无并发
python3 pipeline/cli.py loop        # 本环境会在 probe 因 SaleUI 外部红早停（rc=1，已归因）
python3 pipeline/cli.py match       # 独立补跑：RC=0，L1 189，ScreenEffectMgr L1=2
python3 tools/census_struct_holes.py
```

## 7. 独立对抗复核（checklist ⑥）

- 执行方式：独立 agent（workflow 子代理，**未复用本卡任何探针脚本**；只读 `objdump -d original/PAL3.exe` + annotation/status JSON；未跑 apply/export/codegen/match，未写文件）。
- 结论：10 个成员的偏移/尺寸**逐个成立**（A 级 reg+disp32）；ctor/工厂分配/0x454 构造三条假设**成立**（`68 c0 8d 05 00` 在 .text 仅 1 处 ⇒ 0x58DC0 唯一分配点；ctor 尾写恰落在 0x58DC0）。
- 它提出的两处必须修正/限定的措辞，已落进本报告：
  1. **「首尾相接/总长 363,800」不成立**：0xa8 指针 4B 后是 0xac–0xb0 的 4B 洞；363,800 只是成员尺寸和/洞下降量（跨度 363,804、类尺寸 363,968）。见 §0 与 §3 的限定。
  2. **0x90 不是「空」而是「归属未定」**：由另一 ctor `sub_4BDFB0`（vtable 0x56F508）在 0x4BE032 写过；故留白理由由「无证据」改为「归属矛盾（ev_0006）」。见 §4。
  3. 附注：`call 0x401810` 是 MSVC 数组构造 helper，**真正的 sizeof 证据是 stride 0x44**，不是这个调用——报告 §1 的证据列以 stride/尾端闭合为主。
- 另有一条不影响本批的观察：ParticleEffect 的基类子对象在二进制里是 `+4`（`lea ecx,[esi+4]`），annotation `bases[].offset:0` 不是字节偏移；因基类 0x58950+4=0x58954 恰为首个派生成员，绝对偏移与总尺寸仍闭合。

## 8. 门禁边界自证

- 本卡只做首版 T1+T2（与 §0 边界一致），未夹带 R5/R6 段、未动 SaleUI/其他类成员、未重锚基线。
- probe 全链 rc=0 依赖 #9 在途的 SaleUI 收敛；本卡按 PMO seq4 第 4 条以「新失败 0 + 真新增全在 SaleUI.cpp + S2 持平 + match 独立 rc=0」归因通过，未做任何基线写入。
