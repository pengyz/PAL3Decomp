# R7-T5：LineupUI 洞区落位（#83）

- 卡号：`tsk_01M8CZFQK991E7G4NFCBYQ`（#83）
- 日期：2026-11-27
- 落地文件：`data/annotations/structs/LineupUI.json`、`data/status/bases_adjudications.json`（新增 `LineupUI` 条）
- 分支基线：`140c59b5d`

## 0 结果一页

| 项 | 前 | 后 |
|---|---|---|
| 洞字节（census v3） | 13,928B / 5 段 | **210B / 4 段** |
| 成员数 | 65（大量 unverified 网格视图） | 60（全部有构造点或字节证据） |
| bases | `UIFrameWnd@0`（无 ctor 证据） | **`UIListBox@0`**（ctor 首调直证） |
| binary_size | 162,772 | 162,772（三证一致，未变） |

全库洞字节 326,900B → **313,182B**（−13,718B，恰等于本类降幅）；`check` 0 new PASS；`match` L1 **193**（棘轮基线 189）。

## 1 尺寸三证

1. `push 27BD4h`（汇编池：`original/PAL3.exe.asm` LineupUI 分配点）
2. ctor `sub_47E5C0` 布局末笔闭合到 `0x27BD4`（末员 `0x19C86`…实际末员为 `0x25AD8`+…，见 §3 表逐行相接）
3. census v3 `size=162772`，`r7_check/check_class.py LineupUI` → `162772/162772 +0`

`bases=UIListBox@0` 的证据：ctor 首条 `call sub_43DCD0`（asm L187098，UIListBox ctor，体内 L96584 写 `off_56AD20`）+ ctor 尾部 `mov [esi], offset off_56B90C`（asm L187243，LINEUPUI 自有表，DATA XREF `sub_47E5C0+2FC`）。旧注解 `UIFrameWnd@0` 无 ctor 证据（#63 C2 已判错）。

## 2 段落落位（按 #81 56 行清单逐行）

| 偏移 | 成员 | 类型 | 证据 |
|---|---|---|---|
| 0x48 | rc | tagRECT | ctor 写 `[esi+58h]=320h`/`[esi+5Ch]=258h`（L187102-187104） |
| 0x58/0x5C/0x60/0x64 | bkWndX/bkWndY/i/j | int | 同上 |
| 0x68 | buf | char[256] | 旧名沿用（本条 unverified） |
| 0x168/0x169 | m_IsMsg/m_Is | uchar / uchar[5] | ctor `[esi+168h]=bl`/`[esi+169h]=bl` + `[esi+16Ch]=ebx` |
| 0x170/0x208 | m_unk_0x170 / m_unk_0x208 | UIFrameContainer(152) | ctor `lea ecx,[esi+170h]/[esi+208h]` + `call sub_4422E0`（写 `0x56ADD0`） |
| 0x2A0/0x338/0x3D0 | stp_BarL/M/R | UIFrameContainer | 同上（`StpCtl\StpBa…` 资产串三元组） |
| 0x468…0xF28 | stp_State/Magic/Equip/Prop/Sword/Justice/BattleArray/m_TimeMoney/Exit | `unsigned char[344]` | `lea ecx,[esi+Xh]` + 资产串 `StpCtl\*` + `call [edx+1Ch]`（asm 192860–193175）；ctor `call sub_43A770`（写 `0x56AC70`） |
| 0x1080 | stp_Effect | UIFrameContainer | ctor `call sub_4422E0`（资产串 `StpCtl\Effec…`） |
| 0x1128/0x11C0 | m_unk_* | UIFrameContainer | 同上 |
| 0x1258/0x13658 | m_btnPar / m_btnPar2 | UIParticle[128]（584B×128） | `??_L` 三元组 `push 80h`(128) × `push 248h`(584)，ctor/dtor 回调 `sub_4B4690`/`sub_4B47E0`；修正旧注解 112×584 |
| 0x25A58 | — | 残洞 128B | 页签矩形缓存（A1 写 32 dword，asm 192942–193185），未被成员覆盖 |
| 0x25AD8/0x25C18 | m_unk_* | `unsigned char[308]` | ctor `call sub_439030`（写 `0x56AC20`） |
| 0x25D4C/0x25DE4/0x25E7C, 0x25F14/0x2620C/0x26504, 0x267A4/0x2683C | m_unk_* | UIFrameContainer / 152B 组 | ctor `sub_4422E0` + `??_L(push 98h ×5/5/4)` |
| 0x268D4/0x26A2C | m_unk_* | `unsigned char[344]` | ctor `sub_43A770`（`0x56AC70`） |
| 0x26B84…0x2705C（6 个） | m_unk_* | **UIPushButton**(248) | ctor `call sub_440740` 体内 L101045 写 `0x56AD88` == `ida_structs.json` 的 UIPushButton(248B, vtable `0x56AD88`) |
| 0x27154 | m_lineupScratch | `unsigned char[2432]` | `sub_47EC00`：`[27154]=0/[27158]=0`、`rep stosd` 6 dword @0x2715C、`rep stosd` 600 dword @0x27174 |
| 0x27AD4 | m_lineupActionState | `unsigned char[256]` | `sub_47EC00` 逐字段写；Update/OnMessage 135 处读写 |

生成头核对（`pal3/src/Misc/LineupUI.h`）：`_BYTE stp_State[344]; // +0x468`、`_BYTE m_TimeMoney[344]; // +0xDD0`、`UIParticle m_btnPar2[128]; // +0x13658`、`UIPushButton m_unk_0x26b84; // +0x26B84`。

## 3 类型判定说明（两处与初稿相反，以二进制为准）

1. **344B 元素类未登记**：11 处 344B 段 ctor 均 `sub_43A770`，写 vtable `0x56AC70`；该表**不在 `asm/pal3/ida_structs.json` 任何类名下**，也不等于 `UIPushButton(248/0x56AD88)`、`UIButton(344/0x56AD64)`、`UIScene(344/0x56ACB8)`、`UICaption(96/0x56AFB0)`。若硬套 `UIPushButton`（248B）会与 344B 跨度冲突并被 check 的 span 校验拒绝，故按命名铁律保 `unsigned char[344]` 并在 source 写明理由。
2. **248B 6 个按钮确为 UIPushButton**：ctor `sub_440740` 写 `0x56AD88`，与 IDB 登记一致，尺寸 248 亦合；早期把 344B 与 248B 两族混判，已在本卡内自纠。

## 4 旧名处置（`pStateUI` / `m_CtrlPlank` 等）

旧注解把这两个名字当作结构基址，语料里出现 `&this->pStateUI + N` 的**绝对偏移锚**：N 以旧注解 `0x26730` 为基，`+1257 dword→0x27AD4`、`+1316/1317→0x27BC0/0x27BC4`、`+5260/5261→0x27BBC/0x27BBD`、`+5280→0x27BD0`、`+105/191/…→0x268D4/0x26A2C` 的虚调用锚点。按真实布局重排后这些锚点消失，故**不为它们建占位成员**（否则把旧错误偏移再固化一次），由语料重渲消除引用——这是本卡的「改名收口」而非布局新增。

`0x00482ED0`：旧标 `LineupUI::Save`，按 #42（写 `off_56BA30` 第 7 槽 / StateUI 表；LineupUI 自有表为 `off_56B90C`）实为 **StateUI ctor `sub_482ED0`**，已自本类 `methods` 删除（36 条），并在 json 加 `_methods_note` 说明；StateUI.json 补条不在本卡写面（仅 `structs/LineupUI.json`），交后续归属卡。

## 5 门禁实测（同树串行，每步先 ps 判空窗）

| 阶段 | rc | 读数 |
|---|---|---|
| check（落地前） | 1 | 16 new：3 条 PalScriptWaitObj C7（他人在飞，见 §7）+ 13 条 LineupUI N13a（语料陈旧） |
| apply（`APPLY_GATE_OFF=1`，通道 1） | **0** | `-> OK: annotations applied` |
| export | **0** | `asm/pal3/ida_structs.json` LineupUI size=162772 / members=60 / bases=UIListBox |
| check（重渲后） | **0** | `0 new errors + 34 frozen(advisory), 110 warnings — PASS` |
| codegen all | 1 | 已知恒红（`probe s2 exited 1`），S1 743/766 |
| probe all | 1 | S1 743/766、**S2 159/230**；新失败 0，`LineupUI.cpp 23→11（消失 12）`，真新增 1 条 C2664（同码站点变化：L507 形参 `unsigned char*` vs `char*`） |
| match | **0** | `matched 1162/1277`、**L1 193**、partial 831、compile-skip 0、`[L1 ratchet] previous 189 → current 193`、L1+sem 201→206、`[metric] L1 字节 8347 / 重定位覆盖 2328(27.9%) / 隐藏差异 1657(19.9%)` |
| census v3 | 0 | LineupUI 13,928B → **210B**（4 段）；全库 943→942 洞、313,254→**313,182B** |

probe rc=1 归因（`tools/regression_detector.py --check`）：总文件 997、**新失败 0**、真新增 1、已修复 1（RoleStatePanel.cpp）、持续失败 94；真新增集中在 SaleUI.cpp（35→33，6 条 C2107/C2102，属上一卡遗留的整数下标伪影）与本次 LineupUI.cpp 的 1 条 C2664（站点/消息变化，非新错误种类）。match `[metric]` 已当场读，L1 193 ≥ 189。

## 6 残洞 210B（4 段，全部有解释）

| 段 | 字节 | 解释 |
|---|---|---|
| 0x16E–0x170 | 2 | 头块尾部对齐 pad（`char buf[256]` 后接 152B 容器） |
| 0x1118–0x1128 | 16 | 共用层状态块（`sub_47E5C0` 只清 16B，无逐字段语义证据）→ 保洞不占位 |
| 0x25A58–0x25AD8 | 128 | 页签矩形缓存（A1 写 32 dword，未被单独成员覆盖；语义为 9 页签的 rect 数组，元素类/长度无 A 级定论） |
| 0x26764–0x267A4 | 64 | 段间对齐 pad |

## 7 披露（不属本卡，但影响读数）

1. 落地前 check 的 3 条 `CANON:C7 PalScriptWaitObj(0x44ab00/0x44ab40/0x4af760)` 来自 `data/annotations/structs/PalScriptWaitObj.json` 的他人未提交改动（`git status` 为 `M`），不是本卡引入；重渲后已自然消失。
2. `structs/` 下同时有他人未提交文件（EquipUI/MainPropUI/PropUI/SaleUI/SwordUI/UIGameFrm/UITitle_JDHY 等）。本卡 `apply` 在其**之前**执行（10:35），因此只把当时已落盘的注解写进 IDB；若他人随后 apply，会以他们的文件为准。
3. `match` 的 population 变化（matched 1152→1162、paired 93→94）说明两次 L1 分母不同；本卡按「L1 绝对值 ≥189 且 rc=0」验收，未 rebaseline。

## 8 复现命令

```bash
cd /home/peng/workspace/PAL3Decomp
python3 tools/r7_check/check_class.py LineupUI        # 162772/162772 +0 60 段 - 待落位
python3 pipeline/cli.py check                          # 0 new + 34 frozen PASS
APPLY_GATE_OFF=1 python3 pipeline/cli.py apply         # rc=0（通道 1：语料陈旧 N13a 需重渲）
python3 pipeline/cli.py export                         # rc=0
python3 pipeline/cli.py codegen all                    # rc=1 已知恒红
python3 pipeline/cli.py probe all                      # rc=1；新失败 0
python3 pipeline/cli.py match                          # rc=0；L1 193
python3 tools/regression_detector.py --check --format text
python3 tools/census_struct_holes.py                   # LineupUI 210B
```
