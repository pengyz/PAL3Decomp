---
name: saleui-r5-campaign-20261126
description: R5 SaleUI 池证据落位战役的可复刻方法——六池 ??_L/??_M 三元组、A/A′/A″ 取舍、独立对抗复核与 7,684B 残留
type: pattern
created: 2026-11-26
sources: [7f9d6a636, b6f6b9385, e5cd8a187, 5b15fc482]
---

# SaleUI R5 战役技术纪要：从 44,560B 到 7,684B

R5 的结论是：SaleUI 的 44,560B 洞不是靠“猜成员”填掉的，而是先用 `??_L`/`??_M` 池三元组把 55 个成员的骨架钉死，再把 3 段共 7,684B 明确留白。MagicUI 与 UIGameFrm 在同一轮被判定为“不能按填洞处理”，没有硬填。

**为什么：** 这轮同时出现了三种容易走错的路——把合成类当真实例（MagicUI）、把同一段内存的第二视图重复建模（UIGameFrm）、用 union 保留旧视图但装不下非 POD 类数组（VC6 C2621）。记下取舍和证据边界，下一轮遇到“大洞 + 旧成员名仍在语料里”时不必重新试错。

**何时使用：** 当一个类的洞跨越多个数组/池、旧注解成员与池证据冲突、或候选方案要在“删旧视图 / union 兼容 / 纯增量”之间选时，按本纪要的顺序做。

> 口径：本文只汇编已提交产物。R5 的四个提交是 `7f9d6a636`、`b6f6b9385`、`e5cd8a187`、`5b15fc482`；工作树里另有未提交的 SaleUI 58 员后续修订，本文单独标注，不把它算成 R5 已生效。

## 1. 一页状态

| 类 | 落档基线 | R5 后 | 处置 |
|---|---:|---:|---|
| SaleUI | 23 洞 / 44,560B | **3 洞 / 7,684B** | 主锚，已提交 |
| MagicUI | 16 洞 / 44,652B | 不变 | 无实例证据，移交裁决 |
| UIGameFrm | 37 洞 / 27,916B | 不变 | `g_gamefrm` 第二视图，不填 |
| 全库 | 1,142 洞 / 1,275,908B | **1,122 洞 / 1,239,032B** | 净降 36,876B |

- 三类合计 117,128B → 80,252B；早期 README 曾把 117,128 写成 116,128，`docs/handoff/r5-20261126/README.md:130` 已按逐类相加更正。
- 提交：`7f9d6a636` 落 annotation + 候选/证据文件；`b6f6b9385` 补提交前自检；`e5cd8a187` 补语料↔布局交叉校验；`5b15fc482` 补六池第二路径复核。
- 读数时点：提交说明与 `docs/handoff/r5-20261126/README.md:118-128` 记的是 2026-11-26 21:30–21:36 的分步读数——`check` PASS（0 new）、`codegen`/`probe` S2 157/229、`match` L1 189→188（唯一 LOST 是 R4 已归因的 RoleStatePanel dtor）。
- **没有同窗口全链 loop 读数**：`docs/handoff/r5-20261126/selfcheck.md:13` 明确 loop 只部分通过；总错误在该窗口没有留下可复核记录。本文不拿后续/中间态数字补这一格。
- 写作时 HEAD 为 `5b15fc482`；`data/annotations/structs/SaleUI.json` 在 HEAD 是 55 员、sha256 `1e7fbaf8…`，工作树另有 58 员未提交版（见 §3.4、§4）。
- 任务卡把产物目录记作 data/handoff/r5-20261126/，该路径在仓库中不存在（勿引用）；实际提交路径是 `docs/handoff/r5-20261126/`，引用以实际路径为准。

## 2. 可复刻路径

### 2.1 先固定“洞的面”和“不能填的面”

- SaleUI：`binary_size=105912`、`bases=[UIListBox@0]`（基类 72B），成员从 0x48 起；census 基线 23 洞 / 44,560B。证据见 `docs/handoff/r5-20261126/struct_holes_r5_20261126.json` 的 SaleUI 条目。
- MagicUI：`binary_size=267300`、76 员，但 `data/status/ctor_layout_decode.json` 记 `{"status":"no-ctor"}`，`.text` 无 267,300 的 `new` 立即数，14 个 `?*MagicUI*` 方法在 `.rdata/.data` 的 4 字节对齐扫描中 0 命中；四个调用点的 `ecx` 分别来自 `RoleStatePanel` 的 `+0x2AFB8/+0x2AFBC/+0x2AFC0/+0x2AFC4`，后两个槽的真实分配是 `new(0x35B50)→??0MainPropUI` 与 `new(0x41014)→??0EquipUI`。证据链：`docs/handoff/r5-20261126/r5_magicui_dossier.md:5-33`。
- UIGameFrm：`binary_size=28268`、37 洞 / 27,916B；四段 `0x164/0x290/0xF40/0x1394` 已在 2026-11-24 被裁定为 `g_UISceneMapDlg`/`g_UIListBoxDlg`/`g_CCBEditorInst`/UITitle 系独立全局对象，注解里的 ctor `0x44EB40` 实为 `sub ecx,44h; jmp _UIEmote` 的调整 thunk。证据：`docs/handoff/r5-20261126/README.md:59-62`。
- 先做这一步的收益：SalesUI 可以按池重建，MagicUI/UIGameFrm 的 72,568B 从一开始就不进入“可回收”账，避免为了凑验收带宽而伪造成员。

### 2.2 用 vtable + ctor/dtor + 池三元组推出六个池

入口锚点：vtable `0x56B5CC`（dtor 首部写 `[esi]`）、`operator new(0x19DB8)` @0x459729、ctor `0x45A7B0`、dtor `0x45AE60`。`original/PAL3.exe.asm` 的文本清单里对应 `sub_45A7B0` / `sub_45AE60`；ctor 调用方在 `sub_4593C0`：`:139310 push 19DB8h` → `call ??2` → `:139318 call sub_45A7B0`。证据：`docs/handoff/r5-20261126/pool_crosscheck_asm_listing.md:9-15`、`docs/audit/2026-11-26-saleui-adversarial-review.md:45`。

`??_L` 的 cdecl 压栈序是 **dtor → ctor → count → size → ptr**，`??_M` 是 **dtor → count → size → ptr**。六个池的 `(offset, stride, count)`：

| 池 | offset | stride | count | 末端（offset+stride×count） |
|---|---:|---:|---:|---:|
| UIFrameContainer[5] | 0x6394 | 152 | 5 | 0x668C |
| UIFrameContainer[240] | 0x66F4 | 152 | 240 | 0xF574 |
| 52B 未名元素[240] | 0x11558 | 52 | 240 | 0x14618 |
| CCBResultWindow[30] | 0x14618 | 180 | 30 | 0x15B30 |
| UIFrameContainer[30] | 0x15B30 | 152 | 30 | 0x16D00 |
| UIFrameContainer[13] | 0x17A9C | 152 | 13 | 0x18254 |

- 乘法链逐段闭合，池之间没有缝隙：0x6394+0x2F8=0x668C；0x66F4+0x8E80=0xF574；0x11558+0x30C0=0x14618；0x14618+0x1518=0x15B30；0x15B30+0x11D0=0x16D00；0x17A9C+0x7B8=0x18254。
- 每个池在 ctor 的 `??_L` 与 dtor 的 `??_M` 两侧都能对上同一个 ptr/size/count；这是 A 级，不是“按名字猜类型”。
- 第二路径复核：直接 `grep`/`sed` `original/PAL3.exe.asm` 的 ctor/dtor 区间，复现六个三元组；命令与原文在 `docs/handoff/r5-20261126/pool_crosscheck_asm_listing.md:17-53`。这条路径不依赖 idalib 探针，也不需要开 IDB。
- 池外还有 53 个构造点 / 39 个拆除点的 ctor-dtor 邻接双证（`docs/handoff/r5-20261126/saleui_binary_layout.md:3-4`）。邻接只用于“这段归谁”，不能单独当类型证据。

### 2.3 四个候选文件各自的作用与准入

| 文件 | 方案 | 关键数字 | 准入结果 |
|---|---|---|---|
| `SaleUI.proposed.json` | A：按池重建、删 58 条旧成员 | 55 员；预计 3 洞 / 7,684B | `check` 报 19 条 `DATA:N13a`——语料仍按旧名引用，字段契约断，不能直接 apply |
| `SaleUI.union.json` | A′：池 + 旧名 union 双视图 | 19 个顶层成员、3 个 union | `check` PASS，但 VC6 `C2621`（`UIFrameContainer[240]` 非 POD 不能进 union）；S2 0/229，弃用留档 |
| `SaleUI.gapfill.json` | A″：不删旧成员，只往清零跨度覆盖的洞加字节区 | 65 员；22 洞 / 26,736B（−17,824B） | 可用但不满足 36.9KB 目标；未选 |
| `SaleUI.final.json` | A 的落地版：55 员、无 union；三个大区成员改名为 `_view` 对齐语料 | 3 洞 / 7,684B | `check` 0 new；apply/export OK；已提交 |

- `proposed` 与 `final` 的成员集合相同，只有 3 个名字不同：`m_unk_0x150` / `0x66f4` / `0x11558` → 加 `_view` 后缀。这样做是“名字与类型解耦”：语料按名字引用，类型仍按池证据给 `UIFrameContainer[240]` 等。
- A 方案被 N13a 挡住后，A′ 想用 union 同时保旧名，但非 POD 数组进不了 union；A″ 不删成员只能降到 26,736B。最终选择 A + 改名，既保住 36,876B 降幅，也不丢池类型。
- 候选文件与最终注解的关系：`SaleUI.final.json` 就是 HEAD 提交版本的源文件，二者 sha256 同 `1e7fbaf8…`；`SaleUI.union.json` 是反例，不得再作为候选。

### 2.4 残留 7,684B 的逐段口径

| 段 | 字节 | 证据口径 |
|---|---:|---|
| 0xF574–0x10474 | 3,840 | ctor/dtor 无固定 disp 构造；探针在 0x7000–0x10FFF 页零 disp 访问 |
| 0x10564–0x10568 | 4 | 两个 240B `rep stosd` 清零块之间的对齐空隙（R5 当时的保守判断） |
| 0x10658–0x11558 | 3,840 | 同 0xF574 段 |

`docs/handoff/r5-20261126/selfcheck.md:20-27` 与 `README.md:132-137` 是这一口径的原始记录；其中 0x10564 的 4B 后来被对抗复核证伪为真实字段，见 §3.3。

## 3. 判据、证据分级与新增坑

### 3.1 证据分级

- **A 级**：`??_L`/`??_M` 三元组（ptr/size/count 双侧一致）、ctor 直接写、ctor-dtor 邻接两侧都闭合、`rep stosd` 的起止与成员 span 精确相等。
- **B 级**：只有单侧邻接、只有“相邻构造点空隙”、元素类由上下文推断但无独立 ctor/dtor 对照。
- **留白**：无构造/使用证据，或声明类型尺寸与邻接段长矛盾且无法解释。留白名用 `m_unk_<offset>`，不占位、不编语义。
- **IDB 尺寸只在“与邻接段长一致”时采用**：UIFrameContainer 152、CCBResultWindow 180、UIRoleDialog 1368 可用；UI3DCtrl 的 IDB 308 与邻接 84 不符、PalScript 的 2176 与邻接 164 不符，这两段改记 `unsigned char[N]`，理由写进 source。

### 3.2 命名现状

HEAD 的 55 员：49 个精确 `m_unk_<hex>`、3 个语义名（`bkWidth`/`bkHeight`/`buf`）、3 个 `m_unk_<hex>_view`。`_view` 后缀是语料兼容的过渡形态，但它逃过 `^m_unk_(0x)?[0-9a-f]+$` 的普查正则——`docs/audit/munk_census_20261126.json` 对 SaleUI 只数到 49 条即由此而来。后续 export 刷新语料后应迁回规范形态，不能把 `_view` 当成新约定。

### 3.3 独立对抗复核（#22）驳回了什么

`docs/audit/2026-11-26-saleui-adversarial-review.md` 用另一条证据路径（`original/PAL3.exe.asm` 文本 + JSON 区间算术，不复用作者的 idalib 探针）复核，结论 **PASS-WITH-NOTES**：六个池三元组、55 员无重叠/不越界、span 语义、命名合规、证据字段都通过或有条件通过。两处必须修：

1. **0x10564 的 4B 不是无证据洞**：ctor `mov [esi+10564h], ebx`（`asm:141136`，ebx=0），`sub_4623A0` 里还有读 `asm:150262`、写 `asm:150274`；4B 整对齐、按 dword 用。它是真实字段（#18 判为 `CCBUIPanel*`，本卡只保留数值型）：若只补这 4B、两段大洞仍留白，残留应记 7,680B / 2 段；若两段也按 16B 表的覆盖区间建成成员，残留归零（工作树 58 员即把两段记为 `unsigned char[3840]`）。
2. **两段 3,840B 不是“无证据”**：ctor 确实不逐元素初始化，但 SaleUI 自己的方法按 16B 元素读写它们——`sub_45E9F0` 的 `[edx+esi+0F574h]`（asm:145625/145629/145643）、`sub_4623A0` 的 `lea edx,[ecx+esi+0F574h]` 后连取 +0/+4/+8/+0Ch（asm:150403）、`sub_46B040` 的 `[esi+eax*8+10568h]` 与 `lea edx,[edx+esi+10658h]`（asm:160345-160372）。两段是 2×(240×16B) 的同构矩形表（0xF574 源表、0x10658 目标表），应建成 `tagRECT[240]` 类成员（B/C 级）或至少把措辞改成“ctor 不初始化、运行期填充”，不能写“无证据”。

其他未关闭的弱项：4 员只有“相邻构造点空隙”（`0x615C[16]`、`0x668C[104]`、`0x16EA4[64]`、`0x189A4[404]`）；6 员声明 `uchar[168]` 而同位置 IDB 组件是 `UIFrameContainer(152)`，168 与 152 的 16B 差没有结构解释；`buf` 是唯一 unverified。

### 3.4 工作树后续（未提交，不算 R5 已生效）

写作时 `data/annotations/structs/SaleUI.json` 在工作树是 58 员（HEAD 是 55 员），新增的正是 0x10564、0xF574、0x10658 三段，source 已引用上述 asm site 和 #22 复核。但这是 **`M` 未提交**，R5 的 census 产物仍是 55 员 / 3 洞 / 7,684B。验收/引用时必须区分：

- 已提交：`7f9d6a636` 的 55 员、3 洞、7,684B。
- 工作树未提交：58 员（吸收了 #22 的 D 项），尚无对应的 census/基线读数。
- 仅盘点：MagicUI 的 44,652B、UIGameFrm 的 27,916B 都还没有落 annotation。

### 3.5 与 R1–R3 的差异与新增坑

- **从“单成员闭合”升级为“池集合闭合”**：R1–R3 多数是按单个成员/数组做 ctor-dtor 或邻接；R5 是先用六个 `??_L`/`??_M` 三元组定池，再处理池内旧视图。池证据比“逐成员猜”强，因为它同时锁住 offset/stride/count 和末端。
- **双副本分叉**：`SaleUI.proposed/final` 与 `data/annotations/structs/SaleUI.json`、`struct_holes_r5` 与 `data/status/struct_holes_20261125.json` 都可能各有一份。`selfcheck.md:10` 已记录 census 脚本没有 `--out`，运行时会顺带重写 `data/status/`；本轮靠“提交 handoff 副本、不提交 data/status”避免分叉。后续引用一律先比 sha256/成员数。
- **合成类 chimera**：MagicUI 有名字、有 76 个成员、有 267,300B 尺寸，但没有 ctor、没有分配点、没有 vtable 表项；这类“注解存在≠实例存在”的合成类，不能按填洞处理，应走错名/合成类裁决。它和 CCCTData 的 chimera 是同一类风险。
- **union 不是万能兼容层**：VC6 下非 POD 类数组不能进 union（C2621）；`m_NotesNull` 还跨过 `CCBResultWindow[30]` 池起点，数组成员本身就越界，union 也救不了。要保旧视图，只能退字节或等语料刷新。
- **apply 的 N13a 闸与语料刷新会互锁**：删旧名 → check 报 N13a → 不能 apply → 不能 export 刷新语料。本轮用“只改三个大区成员名、不动几何”绕开，没有关闸。
- **池方法 disp 判别不是 R5 的产物**：R5 用的是 ctor/dtor 三元组；`0x68FD0` 这类“池 disp 越界判类 X/Y”是 R6 的 CCBCamControl 孪生裁决方法，不要把它写成 R5 的判据。

## 4. 未完成 / 移交

| 项 | 状态 | 入口 |
|---|---|---|
| #22 的 0x10564 / 两段 3,840B 修正 | 工作树 58 员已写、**未提交** | 先跑干净 loop/census，再决定是否随下一张卡提交 |
| MagicUI 身份（267,300B / 44,652B） | 仅盘点，未裁决 | 错名/合成类裁决卡；四指针主人逐一正名 |
| UIGameFrm 第二视图（27,916B） | 仅盘点，R5 不填 | 若再填必须先证 `g_gamefrm` 的宿主关系 |
| UICaption 尺寸 96 vs 344 | 发现，未修 | 结构表/导出层缺陷；7 处 344B 段的类名与尺寸要一起定 |
| `NameSys::GetSys` 实为 ctor | 发现，未修 | IDB 名不可信；344B 元素类仍未名 |
| 4 个弱成员 + 6 个 `uchar[168]` | 未补证 | 补 ctor/dtor 邻接算式，或降级/解释 16B 差 |
| `_view` 命名迁移 | 过渡态 | 下次 export 刷新语料后改回 `m_unk_<hex>` |
| `buf` unverified | 既有成员 | 补二进制证据或降级说明 |

R5 原验收带“72–88KB”按证据不可达，实测上限 36,876B，全部来自 SaleUI；这个口径更正本身就是 R5 的交付之一，不要把 MagicUI/UIGameFrm 的字节算进降幅。

## 5. 复现与引用

只读命令（不跑 apply/export/codegen/probe/match）：

```bash
# 1) 读 R5 的 census 副本，确认三个类的数字
python3 - <<'PY'
import json
d=json.load(open('docs/handoff/r5-20261126/struct_holes_r5_20261126.json'))
print(d['_meta'])
for x in d['classes']:
    if x['cls'] in ('SaleUI','MagicUI','UIGameFrm'):
        print(x['cls'], x['size'], x['members'], x['hole_bytes'], x['total_holes'])
PY

# 2) 读最终候选的成员数/名字（与 HEAD 注解比对）
python3 - <<'PY'
import json,hashlib
for f in ['SaleUI.proposed.json','SaleUI.union.json','SaleUI.gapfill.json','SaleUI.final.json']:
    p='docs/handoff/r5-20261126/'+f; d=json.load(open(p))
    print(f,len(d['known_members']),hashlib.sha256(open(p,'rb').read()).hexdigest()[:12])
PY

# 3) 第二路径复核六池：定位 ctor/dtor 后看 ??_L/??_M 压栈
grep -n "^sub_45A7B0 " original/PAL3.exe.asm
grep -n "^sub_45AE60 " original/PAL3.exe.asm
sed -n '141113,141200p' original/PAL3.exe.asm
sed -n '141600,141652p' original/PAL3.exe.asm

# 4) 区分 HEAD 的 55 员与工作树未提交版（58 员）
git status --short data/annotations/structs/SaleUI.json
python3 - <<'PY'
import json, subprocess
for tag, raw in [('HEAD', subprocess.check_output(['git','show','HEAD:data/annotations/structs/SaleUI.json'])),
                 ('WORK', open('data/annotations/structs/SaleUI.json','rb').read())]:
    d=json.loads(raw); print(tag, len(d['known_members']), d['known_members'].get('0x10564',{}).get('name'))
PY
```

引用索引：

- `docs/handoff/r5-20261126/README.md:12-16`（三类洞与可闭合上限）、`:32-46`（六池与 ctor 写序）、`:101-128`（最终形态与分步读数）、`:132-137`（残留三段）。
- `docs/handoff/r5-20261126/saleui_binary_layout.md:3-4`（ctor/dtor 邻接方法）、`:19-25`（六池段）、`:64-69`（读法与 IDB 尺寸矛盾）。
- `docs/handoff/r5-20261126/saleui_member_diff.md:3-6`（覆盖/残留）、`:113-125`（21:30 字节闭合重测）、`:159-182`（A/A′/A″ 取舍）。
- `docs/handoff/r5-20261126/r5_magicui_dossier.md:5-33`（MagicUI 无实例证据）、`:39-41`（建议）。
- `docs/handoff/r5-20261126/selfcheck.md:20-27`（残留表）、`:61-63`（池尾索引访问）。
- `docs/handoff/r5-20261126/pool_crosscheck_asm_listing.md:17-53`（第二路径六池）、`:57-65`（0x10564/0x3E08 旁证）。
- `docs/audit/2026-11-26-saleui-adversarial-review.md:15-16`（必须修两处）、`:51-67`（D 项逐段）。
- `data/annotations/structs/SaleUI.json`（HEAD 55 员）；`data/annotations/structs/MagicUI.json`（76 员/267,300）；`data/annotations/structs/UIGameFrm.json`（63 员/28,268）。
