# 存量占位名冻结登记（方向 A，2026-11-28）

## 0. 一句话
按 Human 2026-11-27 的裁定：**存量占位名 = 合法过渡态**，登记在
`data/annotations/archive/placeholder_names_frozen_20261127.json`（149 类 / 619 条，`generated_at` 见文件头）；
**新增占位名一律禁止**（新名必须有 A/B 级证据链）。

## 1. 冻结边界
- 只冻结**形态**：`m_unk_*`、`m_nTodo_*`、`m_todo_*`、`_tail_*`、`_gap_*`、`_pad_*`、纯地址后缀（`*_0x…`）。
- 每条记录 `class / offset / name / kind / type / frozen / frozen_reason`，不含任何语义断言。
- 冻结不是免检牌：任一偏移出现不在本表的占位名 ⇒ 违规；正名卡落地后对应条目必须从本表删除。
- 本表与两张既有台账的分工：
  - `data/annotations/archive/pseudo_semantic_names_20261118.json`：伪语义名（CachedA/RoleParam0 类，58 类）——回答「哪类形态非法但暂留」；
  - `data/status/misattribution_ledger.json`：工具自动扫描的「当前名与证据冲突」候选——回答「现在哪些名字错了」；
  - 本表：回答「谁被允许暂时存在」。三表只互指、不互抄；两表类别不相交，同一成员同时命中时归属以本表为准并在 `frozen_reason` 注明。

## 2. 数字对齐（先把历史快照和漂移分开）
| 数字 | 出处 | 口径/时点 |
|---|---|---|
| 583 | 拆骨 2026-11-27 23:43 初版脚本 | 141 类；口径 `m_unk_/m_nTodo_/_tail_/_view`（`_view` 命中 0） |
| 593 | 拆骨 2026-11-28 00:02 扩展口径 | 147 类；583 口径 + `_gap_/_pad_/_0x…` ⇒ +10 |
| 585 | lead 2026-11-27 独立扫描 | `m_unk_250 + m_nTodo_239 + _tail_94 + m_todo_1 + 地址后缀1` |
| 598 | #70 文档（更早快照） | `m_unk_263 + m_nTodo_240 + _tail_94 + 地址后缀1` |
| 610（143 类） | #74 首版落库（02:02） | 只收五类形态；`m_unk_275 + m_nTodo_239 + m_todo_1 + _tail_94 + addr_1` |
| **619（149 类）** | **本表 `generated_at=2026-11-28T02:22`** | 冻结基数；610 + `_gap_`7 + `_pad_`2（见 §2.3） |

- **583 → 593 = +10**：`_gap_`7 + `_pad_`2 + 地址后缀1 进入口径。
- **598 → 585 = 13**：`m_unk +13`（250→263）、`m_nTodo +1`（239→240）、`m_todo −1`（1→0），净 +13。逐条原因见下节。
- **598 → 610 = +12**：移除 15 条、新增 27 条（§2.1/§2.2）。
- **610 → 619 = +9**：`_gap_`7 + `_pad_`2 纳入冻结口径（§2.3）；**619 / 149 类为冻结基线**。

### 2.1 移除的 15 条（逐条）
| 类 | 偏移 | 原占位名 | 原因 |
|---|---|---|---|
| RoleSystem | 0x1968 | `dword_17AA450` | 形态外（`dword_` 前缀不在本卡清单），偏移与名字仍在，不计入占位 |
| SaleUI | 0x66f4 | `m_unk_0x66f4_view` | #71 正名 → `m_PageItemFrames`（`UIFrameContainer[240]`） |
| SaleUI | 0x14618 | `m_unk_0x14618` | #71 正名 → `m_ResultWindows`（`CCBResultWindow[30]`） |
| SaleUI | 0x15b30 | `m_unk_0x15b30` | #71 正名 → `m_ResultWindowFrames`（`UIFrameContainer[30]`） |
| SaleUI | 0x18384 | `m_unk_0x18384` | #71 正名 → `m_ListBoxes`（`UIListBox[17]`） |
| UITitle_JDHY | 0x168 | `m_unk_0x168` | #71 正名 → `m_nLayoutRowOffset` |
| UITitle_JDHY | 0x16c | `m_unk_0x16c` | #71 正名 → `m_pMainEquipUI` |
| UITitle_JDHY | 0x658 | `m_unk_0x658` | #71 正名 → `m_PageCaptions`（`unsigned char[8][344]`） |
| UITitle_JDHY | 0x12f0 | `m_unk_0x12F0` | #71 正名 → `m_ParticlesBack` |
| UITitle_JDHY | 0x136f0 | `m_unk_0x136F0` | #71 正名 → `m_ParticlesFront` |
| UITitle_JDHY | 0x25b70 | `m_unk_0x25B70` | #71 正名 → `m_PageSelected` |
| UITitle_JDHY | 0x25e9c | `m_unk_0x25E9C` | #71 正名 → `m_ButtonCaptions` |
| UITitle_JDHY | 0x45768 | `m_unk_0x45768` | #71 正名 → `m_ItemCaptions` |
| UITitle_JDHY | 0x45b38 | `m_unk_0x45B38` | #71 正名 → `m_ScrollPage` |
| UITitle_JDHY | 0x45e90 | `m_unk_0x45E90` | #71 正名 → `m_ScrollParams` |

### 2.2 新增的 27 条（逐条：StateUI 20 + UICoverFrm 6 + UIScenePanel 1）

| 类 | 偏移 | 占位名 | 声明类型 |
|---|---|---|---|
| StateUI | `0x48` | `m_unk_0x048` | `unsigned char[296]` |
| StateUI | `0x170` | `m_unk_0x170` | `UIFrameContainer[6]` |
| StateUI | `0x500` | `m_unk_0x500` | `unsigned char[3096]` |
| StateUI | `0x1118` | `m_unk_0x1118` | `UIFrameContainer` |
| StateUI | `0x11c0` | `m_unk_0x11c0` | `UIFrameContainer[3]` |
| StateUI | `0x1388` | `m_unk_0x1388` | `UIParticle[128]` |
| StateUI | `0x13788` | `m_unk_0x13788` | `UIParticle[128]` |
| StateUI | `0x25c08` | `m_unk_0x25c08` | `unsigned char[47]` |
| StateUI | `0x25c48` | `m_unk_0x25c48` | `UIFrameContainer` |
| StateUI | `0x25ce0` | `m_unk_0x25ce0` | `unsigned char[1720]` |
| StateUI | `0x263ac` | `m_unk_0x263ac` | `UIFrameContainer[5]` |
| StateUI | `0x266a4` | `m_unk_0x266a4` | `UIFrameContainer[5]` |
| StateUI | `0x269f0` | `m_unk_0x269f0` | `UIRoleDialog` |
| StateUI | `0x26f48` | `m_unk_0x26f48` | `unsigned char[32]` |
| StateUI | `0x26f68` | `m_unk_0x26f68` | `gbVec3D[6]` |
| StateUI | `0x26fb0` | `m_unk_0x26fb0` | `unsigned char[152]` |
| StateUI | `0x27048` | `m_unk_0x27048` | `UIFrameContainer[5]` |
| StateUI | `0x27360` | `m_unk_0x27360` | `UIFrameContainer[6]` |
| StateUI | `0x276f0` | `m_unk_0x276f0` | `unsigned char[9720]` |
| StateUI | `0x29ce8` | `m_unk_0x29ce8` | `int` |
| UICoverFrm | `0x488` | `m_unk_0x488` | `UIFrameContainer` |
| UICoverFrm | `0x520` | `m_unk_0x520` | `unsigned char[180]` |
| UICoverFrm | `0x848` | `m_unk_0x848` | `UIFrameContainer` |
| UICoverFrm | `0x8e0` | `m_unk_0x8e0` | `UIFrameContainer` |
| UICoverFrm | `0x27e0` | `m_unk_0x27e0` | `UIRoleDialog` |
| UICoverFrm | `0x2d38` | `m_unk_0x2d38` | `UIRoleDialog` |
| UIScenePanel | `0x3799` | `m_gap_0x3799` | `unsigned char[3]` |

合计 20 + 6 + 1 = **27**，与 §2 的「598 → 610 = +12（−15 + 27）」一致。

说明（其余条目不是新增，不在此表重复）：
- **UIScenePanel**：本表只列新增的 `m_gap_0x3799` 一条；该类的另外 56 条占位已在 598 快照里，属既有存量，全量见白名单 `classes.UIScenePanel.placeholders`。
- 与 #70 的 598 快照逐条对差（`/tmp/ccct70/final_data.json`），真实新增就是 20+6+1；移除 = UITitle_JDHY 10 + SaleUI 4 + RoleSystem 1 = 15。
- 来源与提交状态（以 git 为准）：**StateUI** 20 条在白名单生成时点（2026-11-28T02:02:08）仍在工作树，随后由 `bb90a2e53`（2026-11-28 02:03:35，「annotations(#161): StateUI 整表替换（66→20 成员 + 6 段 pad 297B，size 171,244）」）提交；**UICoverFrm** 6 条由 `14ba2cd40`（2026-11-28 00:36:36，「annotations(UICoverFrm): 按 #164 核对补两段长度/base_size，并把五个单字母后缀名改留白形」）提交；**UIScenePanel** 的 `m_gap_0x3799` 来自并行 R8-T2 的整表改动（该 JSON 尚未提交，故本卡未动它，承接卡待另开）。
- 白名单 JSON 的 `count_reconciliation.current_vs_598` 文本把 StateUI 写成「21、未提交」，是生成时点（02:02）的笔误；按 QA 返工要求本次只改本文档、不动 JSON，**以本节 20 条与上面的提交状态为准**。
- 这 27 条不是本卡新造的占位名，也不是 #71/#72 的产物；若上述改动被回退，本表需按本节重算。

### 2.3 610 → 619 增量 9 条来源（本轮基线从 610 前移到 619）

**口径说明**：这 9 条不是我方新增的注解，也不是 #74/#77 造的名字。它们的形态是 `_gap_*` / `_pad_*`，#74 卡面的形态清单里没有这两类，所以 610 版没有收；619 版把这两类纳入冻结口径后，它们按「本类已有成员」被登记进来。**全部来自已提交的 struct 文件**，逐条可回查：

| 类 | 偏移 | 占位名 | 声明类型 | 来源（该文件最近一次提交） |
|---|---|---|---|---|
| RoleSystem | `0x169` | `_gap_169` | `unsigned char[3]` | `4ae0bdc1d`（11-24 12:06，critical 退役） |
| SceneMgrCamBlock | `0x0` | `_gap_000` | `char[84]` | `3ce252684`（11-16 22:17，C9/C10 门禁） |
| String | `0xc` | `_gap_000` | `int` | `e524aef68`（11-25 16:07，String 定谳） |
| UIManager | `0x4` | `_gap_004` | `char[12]` | `8b9f4042a`（11-25 00:22，binary_size 4→0xEAC） |
| UIRoleDialog | `0x551` | `_gap_551` | `char[4]` | `ac3799b43`（11-27 01:05，r4 拆分） |
| tagCmdDataDestRoleView | `0x0` | `_pad_7` | `_BYTE[7]` | `3ce252684`（11-16 22:17） |
| tagCpkAudioOvl | `0x0` | `_pad_tableprefix` | `char[656]` | `d6f1f3022`（11-25 19:56，W2 union） |
| tagPartyInitView | `0x0` | `_gap_50814` | `_BYTE[2]` | `3ce252684`（11-16 22:17） |
| tagRoleTaskData | `0x18` | `_gap_18` | `char[48]` | `3ce252684`（11-16 22:17） |

来源判定方法（可复跑）：
```bash
for c in RoleSystem SceneMgrCamBlock String UIManager UIRoleDialog tagCmdDataDestRoleView tagCpkAudioOvl tagPartyInitView tagRoleTaskData; do
  echo "$c $(git log -1 --format='%h %ad' --date=short -- data/annotations/structs/$c.json)"
  git status --porcelain data/annotations/structs/$c.json   # 9/9 输出为空 ⇒ 均为已提交内容
done
```

**610 结论作废**：610 是「只收五类形态」口径下的快照，已被 619 取代；本表后续以 **619 / 149 类**为冻结基线。

## 3. 解除条件与在飞卡关系
- 解除条件：某成员由取证战役给出 A/B 级语义名并落库后，**从本表删除该条**（不是保留成"已解决"）。
- 与 #71 的关系：`UITitle_JDHY` 10 条、`SaleUI` 4 条已被 #71 正名，因此本表不再包含它们（见 §2.1）。
- 与 #72 的关系：#72 的 10 个 `*_graph` 类**没有改名**（PDB `data_members=[]`、无字段锚点），其 `_tail_000` 仍在本表并以 note 记录 5300B 结构定界；#72 的正文只描述了结构，不产生新占位名。
- UIScenePanel 目前无承接卡（其 JSON 正被并行 R8-T2 改动），需另开卡后按本表逐条消费。

## 4. 复跑
```
python3 pipeline/check_annotations.py         # 期望 0 new errors + 34 frozen(advisory)
python3 - <<'PY'                              # 本表条目数 vs 工作树实测
import json,glob,os,re
FORM=re.compile(r'^(m_unk_|m_nTodo_|m_todo_|_tail_)|_0x[0-9A-Fa-f]+$')
n=sum(1 for f in glob.glob('data/annotations/structs/*.json') for k,v in (json.load(open(f)).get('known_members') or {}).items() if FORM.search(v.get('name','')))
print('live placeholders',n)
PY
```
