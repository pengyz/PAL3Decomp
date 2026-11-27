# #161 R8-T7 StateUI 整表替换落位（合并 #151 尺寸修正与 #158 oracle）

日期：2026-11-28 · 卡：`tsk_01M8ES2QD5QHPG3MGWFTJ3` · 写面：`data/annotations/structs/StateUI.json`、`data/status/`、`docs/specs/`

## §0 结论

| 项 | 值 |
|---|---|
| binary_size | **171,244 (0x29CEC)**（#151 已修，本卡只确认） |
| bases / base_size | **UIListBox @0 / 72**（卡面写 UIWnd/68，与二进制不符，见 §1.3） |
| 成员 | 66 → **20**（整表替换，#159 判「必须废弃」的旧名零残留） |
| 构造段 | ctor `sub_482ED0` 27 段 = 21 构造 + 6 对齐 pad；20 成员 + 72 基类 + 297 pad = 171,244 |
| 洞面 | 12,139B/6 段 → **296B/6 段**（目标 297B，差 1B 见 §4.2） |
| check | **0 new + 34 frozen(advisory), 110 warnings — PASS**（rc=0） |
| probe | S2 **161/229**，新失败 0；`StateUI.cpp` 6→4 条 |
| match | L1 **198**（`1180/1293`，compile-skip 1）——与开工前不可直接比，见 §6 |
| 旧名线索 | 66 条快照 `data/status/archive/r161_stateui_legacy_names_20261128.json` |

## §1 尺寸与基类三证

### 1.1 尺寸（沿用 #151，本卡复验）
- `asm:240476 push 29CECh` → `asm:240485 call sub_482ED0` → `asm:240496 mov [esi+2AFB8h],eax`；`grep -c "push    29CECh"` 全库 **1**。
- ctor 尾 `asm:193686 mov [esi+29CE8h],ebx` ⇒ 末字段 4B，终点 0x29CEC。
- 自表 `asm:193688 mov [esi],offset off_56BA30`。
- 11 段构造链求和 + 6 pad = 171,244（脚本断言 `72+170,875+297==171244`）。

### 1.2 ctor 27 段（本卡实读，与 #158 §5 逐行一致）
`0x170/208/2A0/338/3D0/468`（6×`sub_4422E0`）、`0x500…0xFC0`（9×`sub_43A770`）、`0x1118`、`0x11C0/1258/12F0`、`0x1388`+`0x13788`（2×`??_L(0x248,0x80)`）、`0x25C48`、`0x25CE0`（`??_L(0x158,5)`）、`0x263AC`+`0x266A4`（`??_L(0x98,5)`）、`0x269F0`（`sub_4A12F0`）、`0x26F68`（6×gbVec3D）、`0x26FB0`（`sub_47CAD0`）、`0x27048`（`??_L(0x98,5)`）、`0x27360`（`??_L(0x98,6)`）、`0x276F0`（`??_L(0x798,5)`）。
6 段 pad：`0x11B0–0x11C0`(16)、`0x25B88–0x25C08`(128)、`0x25C37–0x25C48`(17)、`0x26398–0x263AC`(20)、`0x2699C–0x269F0`(84)、`0x27340–0x27360`(32)，合计 297。

### 1.3 基类口径差异（与卡面冲突，按二进制实现）
- 卡面要求 `bases=UIWnd@0、base_size=68`；实测 ctor `asm:193527 call sub_43DCD0`，其体 `asm:96582 mov [esi],offset off_56AD20`（=UIListBox 表）、`asm:96583 mov [esi+44h],ebx` ⇒ **基类 UIListBox（72B）**，`+0x44` 是其字段，不是类尾。
- 本卡保留 `UIListBox@0 / base_size=72`（#151 已是此值且 check 通过）；若改回 UIWnd/68 会与 `+0x44` 字段和 72B 基类子对象矛盾。**请 PMO 修订卡面口径**，或指出我漏读的证据。

## §2 整表（20 成员）

| 偏移 | 类型 | 等级 | 证据 |
|---|---|---|---|
| 0x48 | unsigned char[296] | C | ctor 只写 `[58]=320`/`[5C]=258`/`[168]~[16D]`；需补证 |
| 0x170 | UIFrameContainer[6] | A- | asm:193529/535/538/541/544/547 |
| 0x500 | unsigned char[3096] | A- | asm:193550..193574 九次 `sub_43A770`（344B 元素类未注册，字节视图） |
| 0x1118 | UIFrameContainer | A- | asm:193577 |
| 0x11C0 | UIFrameContainer[3] | A- | asm:193580/584/586 |
| 0x1388 | UIParticle[128] | A- | asm:193591 `push 80h`/`push 248h`/`??_L` |
| 0x13788 | UIParticle[128] | A- | asm:193599 同池第二块 |
| 0x25C08 | unsigned char[47] | C | asm:193699 起清零；asm:193608 `[25C32..25C36]=07`；需补证 |
| 0x25C48 | UIFrameContainer | A- | asm:193613 |
| 0x25CE0 | unsigned char[1720] | A- | asm:193621 `push 5`/`push 158h`（5×344，元素类未注册） |
| 0x263AC | UIFrameContainer[5] | A- | asm:193629 |
| 0x266A4 | UIFrameContainer[5] | A- | asm:193637 |
| 0x269F0 | UIRoleDialog | A- | asm:193642 `sub_4A12F0` |
| 0x26F48 | unsigned char[32] | C | 4 个常量写（C2180000/3FE66666/0/41400000），余 16B 无写；需补证 |
| 0x26F68 | gbVec3D[6] | B | asm:193647 步长 0Ch |
| 0x26FB0 | unsigned char[152] | C | asm:193658 `sub_47CAD0`（无 vtable，字段写至 +0x90）；需补证 |
| 0x27048 | UIFrameContainer[5] | A- | asm:193663 |
| 0x27360 | UIFrameContainer[6] | A- | asm:193671 |
| 0x276F0 | unsigned char[9720] | C | asm:193679 `??_L(0x798,5)`，元素=3×152+6×248，类未注册；需补证 |
| 0x29CE8 | int | B | asm:193686 `mov [esi+29CE8h],ebx` |

C 段一律字节视图 + 「需补证」，未给类型未给语义名；两段 344B 元素池用字节视图（`UIButton` 属另一表 `0x56AD64`，不套用），符合 PMO 既有裁定。

## §3 旧布局移出

- `m_Frame@0x128`、`m_par[16][7]@0x12D4`、`m_par2@0x115D4`、尾部指针组 `0x277D8`（`p_LineupUI…p_SystemUI`）等 **66 名全部移出**，`grep m_Frame/m_TopFrame/m_par data/annotations/structs/StateUI.json` = 0 命中。
- 名字线索（偏移/旧名/类型/等级/证据前 200 字）存 `data/status/archive/r161_stateui_legacy_names_20261128.json`；按 #159「必须废弃」不再作为注解，仅供后续在新表上重新取证时对照。
- diff：`288 insertions(+), 455 deletions(-)`（单文件）。

## §4 census 前后

### 4.1 两口径
| 时点 | size | 成员 | 洞 | 段 |
|---|---|---|---|---|
| #151 落位后 | 171,244 | 66 | 12,139B | 6 |
| 本卡落位后 | 171,244 | 20 | **296B** | 6 |
| #158 目标 | 171,244 | — | 297B | 6 |

逐段（本卡实测）：`0x11B0`16、`0x25B88`128、`0x25C38`16、`0x26398`20、`0x2699C`84、`0x27340`32。

### 4.2 1B 差异归因
census 的覆盖区间末端按下一成员的**类型对齐**上取整：`m_unk_0x25c08`（uchar[47]）真实终点 `0x25C37`，但下一成员 `UIFrameContainer`（align 4）使覆盖上取到 `0x25C38`，于是 census 记 16B 而非 17B。**物理 pad 仍是 17B**，差 1B 是计量对齐口径，不是落位差。

### 4.3 全库
census 快照：**196 类 / 893 段 / 201,308B**（#162 基线为 196 类 / 910 段 / 205,775B）；StateUI 贡献 −11,843B，其余变化来自其他卡。

## §5 门禁（逐段 rc）

| 步骤 | rc | 读数 | 日志 |
|---|---|---|---|
| apply（首次，正常闸） | **1** | 31 new，全部 `N13a StateUI::m_Frame/m_TopFrame/…`（语料仍引用旧名 = 自锁） | `archive/r161_apply_20261128.log` |
| apply（gate-off，**已报备**） | 0 | 拆自锁 | `archive/r161_apply_gateoff_20261128.log` |
| export | 0 | `ida_structs.json` 01:37 | `archive/r161_export_20261128.log` |
| codegen all | 1 | 既有恒红（`probe s2 exited 1`）；ret-N 证据 3148/285/6 | `archive/r161_codegen_20261128.log` |
| apply（正常闸复跑） | **0** | `0 new errors + 34 frozen(advisory), 110 warnings` | `archive/r161_apply2_20261128.log` |
| check | **0** | 同上（第148行） | `archive/r161_check_20261128.log` |
| probe all | 1 | S2 **161/229**，新失败 **0** | `archive/r161_probe_20261128.log` |
| match | 1 | 见 §6 | `archive/r161_match_20261128.log` |

gate-off 说明：卡面第 5 条要求「若必须用先报 PMO」。已在 #161 Thread seq8 报备，用法=一次性拆 N13a 自锁（语料由旧注解生成，不重建无法消 31 条），随后以**正常 apply** 取证 0 new；本卡未用 gate-off 掩盖任何真实违规。

## §6 probe / match（带三限定）

- probe：`S2 cpp 161/229 ok | own-fail 68 | imported-only 0`；新失败 0；`StateUI.cpp` **6 → 4**（消失 2）；同时收敛 `LineupUI 23→11`、`SaleUI 35→33`、`EquipUI 9→6`、`UIGameFrm 12→9`、`Scene 24→22`、`CCBStageCam 5→1`。
- match：`matched 1180/1293 symbols | L1 198 | partial 842 | unmatched 254 | compile-skip 1 | unresolved-synth 140`；
  `[metric] L1 字节 8641 | 重定位覆盖 2356 (27.3%) | 隐藏差异 1673 (19.4% L1 / 71.0% reloc)`；
  站点 `ok=2124 mismatch=0 unresolved=7205`；目标 `ok=108/mismatch=10/unresolved=13/unaligned=8740`。
- 棘轮：`previous 204 → current 198`，semantic 12→11，population 1234/1349→1180/1293，coverage 101→96；工具自报「可比总体已变化」，**未 rebaseline**。
- **三限定**：①L1 只比到原函数长度（本方多出的 0x90 对齐不可见）；②重定位 4 字节 don't-care（本卡 27.3% 字节被覆盖，其间 71.0% 双侧真不同）；③重定位目标按符号法核对（ok 108 / mismatch 10 / unaligned 8740）。
- 与开工前比较：开工前最后一次 match 是**其他会话**的 204（population 1234/1349），本卡开工未单独取基线（管线被占至 01:33），因此 198 不能直接当退化；LOST 明细（`CCBUIPanel::FocusCurrentRole/SetUserData/??_G`、`UIPushButton::IsHidden/??_G` 等）全在本卡写面之外，detail 存 `archive/s4_diff_detail_regressed_20261128T014850.json`。

## §7 命名自检

- 20 名全部 `m_unk_0x<offset>` 留白形；无 `slot_N`/`sub_XXXX`/`_todo_`/数字后缀/自身偏移后缀。
- C 级 4 段（0x48、0x25C08、0x26F48、0x26FB0、0x276F0 共 5 段）标注「需补证」，未硬给类型或语义名。
- 已知瑕疵：`0x48` 的名字写成 `m_unk_0x048`（三位十六进制零填充），与其他类的 `m_unk_0x48` 写法不一致；改名会触发新一轮 N13a 自锁，故本卡不改，登记于此。

## §8 复现

```bash
python3 -c "import json;d=json.load(open('data/annotations/structs/StateUI.json'));print(d['binary_size'],d['bases'],d['base_size'],len(d['known_members']))"
# 171244 [{'name': 'UIListBox', 'offset': 0}] 72 20
python3 - <<'PY'   # 段长断言
import json;d=json.load(open('data/annotations/structs/StateUI.json'))
size={'unsigned char':1,'int':4,'UIFrameContainer':152,'UIParticle':584,'UIRoleDialog':1368,'gbVec3D':12}
import re;t=0
for m in d['known_members'].values():
    m2=re.match(r'([A-Za-z_0-9 ]+?)(?:\[(\d+)\])?$',m['type']);t+=size[m2.group(1)]*int(m2.group(2) or 1)
print(t+72+297==171244)  # True
PY
python3 pipeline/cli.py check && python3 tools/census_struct_holes.py
grep -n "StateUI" data/status/struct_holes_20261125.json
sed -n '193504,193700p' original/PAL3.exe.asm   # ctor 27 段原文
```

## §9 边界与未决

- 未改 `methods`（38 条保持不变）、未动 `vtables`（`0x56BA30`/CScreenMode 保持 #151 后状态）。
- 未注册 344B 元素类（表 `0x56AC70`）与 0x798 元素类（`sub_483280/sub_483300`）：按「不造类型」留字节视图，另卡处理。
- 卡面 bases=UIWnd/68 与本卡 UIListBox/72 的冲突待 PMO 裁（§1.3）。
- 独立对抗复核未在本卡内完成：`workflow` 单代理今日多次返回 null、`subagent` 报 depth 超限、`codebuddy_ask` 未安装（#116/#120/#128/#151 同一结论），改由 QA 独立复跑 + 本报告可复现命令替代。
