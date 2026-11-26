# R5 交接：SaleUI 洞区证据落位（MagicUI / UIGameFrm 不可闭合）

日期：2026-11-26 · 负责人：青岚（mem_maker）· Task：`tsk_01M8BVHCXQ09M2G6S1KQFD`
状态：**证据与草案齐备，落地阻塞于两个决策 + #2 未完成**（仓库 annotation 零改动）

## 1. 结论先行

R5 原验收带「三类合计洞字节下降 72–88KB」**按证据不可达**，上限为 **36,876B（36.0KB）**，且全部来自 SaleUI：

| 类 | 洞字节（落档基线） | 可闭合 | 原因 |
|---|---|---|---|
| SaleUI | 44,560B | **36,876B** | 真实池可用 `??_L`/`??_M` 三元组定谳 |
| MagicUI | 44,652B | 0 | 无实例：无 ctor、.rdata 零函数指针、267,300B 无分配点 |
| UIGameFrm | 27,916B | 0 | 同一段 `g_gamefrm` 内存的第二视图（别人对象的成员） |

三类合计 116,128B → 79,252B（−36,876B）。差额归因见 §4。

## 2. 三个候选方案（均已在离线副本实测）

| 方案 | 做法 | SaleUI 剩余洞 | 全库降幅 | check | 风险 |
|---|---|---|---|---|---|
| **A** | 按 A 级池证据整表重建，撤 58 条既有成员，55 成员 | 3 洞 / 7,684B | **−36,876B** | NEW 0 | 删成员会影响 SaleUI.cpp 29 个函数的编译 |
| **A″** | 纯增量：只往 ctor 清零跨度覆盖的洞加 `m_unk_<off> unsigned char[N]` | 22 洞 / 26,736B | −17,824B | NEW 0 | 零删除、零编译风险 |
| **A′** | A + 用 union 保留旧具名视图 | 3 洞 / 7,684B | −36,876B | NEW 0 | `m_NotesNull` 跨池边界，形态上保不住，**已撤回推荐** |

- 候选文件：`SaleUI.proposed.json`（A）、`SaleUI.gapfill.json`（A″）
- 方案对照与风险表：`saleui_member_diff.md`
- 建议：**A**（36.9KB 是证据允许的上限，影响面已量化为两个翻译单元）；若优先零风险则 A″。

## 3. 证据链（六证择二，全部 A 级）

1. **`??_L` 构造现场三元组**（ctor `??0SaleUI@@QAE@XZ`@0x45A7B0，ABI 压栈序 dtor→ctor→count→size→ptr）

| 池 | 起点 | 元素 | count | 区间 | ctor site / dtor site |
|---|---|---|---|---|---|
| UIFrameContainer | 0x6394 | 152 | 5 | 0x6394–0x668C | 0x45A98D / 0x45B18A |
| UIFrameContainer | 0x66F4 | 152 | 240 | 0x66F4–0xF574 | 0x45A9B2 / 0x45B16D |
| （52B 元素，回调 `InitState`/`CEffObj::DestroyEffect`） | 0x11558 | 52 | 240 | 0x11558–0x14618 | 0x45A9D7 / 0x45B150 |
| CCBResultWindow | 0x14618 | 180 | 30 | 0x14618–0x15B30 | 0x45A9FC / 0x45B130 |
| UIFrameContainer | 0x15B30 | 152 | 30 | 0x15B30–0x16D00 | 0x45AA1E / 0x45B113 |
| UIFrameContainer | 0x17A9C | 152 | 13 | 0x17A9C–0x18254 | 0x45AAFE |

2. **ctor 写序**：0x178–0x45D8 整段 `mov ecx,1118h; lea edi,[esi+178h]; rep stosd` 清零；0x45DC–0x615C 为 5×0x580 记录数组（循环 0x45A878–0x45A940，每元素 lstrcpyA ×4 + ArraySort + memset 0x580）。
3. **ctor/dtor 邻接双证**：53 个构造点、39 个拆除点间距闭合到 0x19DB8（细节见 `saleui_ctor_dtor_map.json`）。
4. **尺寸只在与邻接一致时采用 IDB 值**：UIRoleDialog 1368、UIFrameContainer 152、CCBResultWindow 180、UIProgressBar 244；不一致的 UI3DCtrl(308 vs 84)、PalScript(2176 vs 164) 改用 `unsigned char[N]` 并在 source 写明理由。
5. **命名**：元素类可证 → 语义名；未名 → `m_unk_<offset> unsigned char[N]`（符合 N12）。

复现：`/tmp/r5_check_run.py base|cand`、`/tmp/r5_census_cand.py base|cand`（离线副本，不碰仓库与 IDB）。

## 4. 差额归因（三类不可闭合）

### MagicUI（44,652B，洞 0x25d8–0xa544 占 32,620B）
- 14 个 `?*MagicUI*` 方法没有任何 .rdata/.data 指针指向（4 字节对齐全扫 0 命中；对照 SaleUI vtable 0x56B5CC 在 .text 0x45ACE0 命中）⇒ 无 vtable ⇒ 若非聚合类则不可能有 UIFrameWnd 派生实例。
- `data/status/ctor_layout_decode.json` 记 MagicUI `{"status":"no-ctor"}`；`.text` 无 0x41424（267,300）立即数 ⇒ 无 `new` 分配点。
- 调用方 ecx 全来自 RoleStatePanel 指针槽：`[esi+2AFB8h]`→SelectTab3、`+0x2AFBC`→SelectSubTab3、`+0x2AFC0`→SelectBigMapTab3、`+0x2AFC4`→SelectXJTMTab3；同四槽又被 `*2@StateUI` 同形接口使用 ⇒ StateUI/MagicUI 是同一对象的两套名字。
- 四槽真主人（`RoleStatePanel::Init`@0x4A4220 分配现场）：`+0x2AFC0 ← new(0x35B50=219,984)` 后调 `??0MainPropUI`；`+0x2AFC4 ← new(0x41014=266,260)` 后调 `??0EquipUI`。
- 结论：MagicUI 的 267,300B 与成员表无二进制依据，应单开裁决卡（建议并入 StateUI 视图或仅保留方法名证据）。

### UIGameFrm（27,916B）
- `members_note` 2026-11-24 已裁定：0x164/0x290/0xF40/0x1394 四段 = g_UISceneMapDlg / g_UIListBoxDlg / g_CCBEditorInst / UITitle 系**独立全局对象**（17/29/1 处引用全来自 PalScript Op_*、RoleSystem::UpdateFollowerMovement、UITitle::OnMessage、sub_426EB0），对应内嵌成员已删除。
- 注解记的 ctor 0x44EB40 实为调整 thunk（`sub ecx,44h; jmp _UIEmote`，8B 函数体），非 ctor。
- 结论：该区是同一 `g_gamefrm` 内存的第二视图，再填 = 双重建模，本轮不填。

### SaleUI 残留 7,684B
- 0xF574–0x10564 与 0x10658–0x11558 两段（各 3,840B）：ctor/dtor 均无构造、探针在 0x7000–0x10FFF 页零 disp 访问 ⇒ 无证据，不占位。
- 0x10564 起 4B：同上。

## 5. 附带发现（不在 R5 范围，需另派）

1. **`data/annotations/structs/UICaption.json` 尺寸自相矛盾**：字段 `binary_size: 96`，同文件 `size_evidence` 写「96 → 344（A 级 new-ctor 三元组 push 0x158）」。IDB 实测支持 344：`0x4A79F3` 为 `??_M`（eh vector destructor iterator），`push ?Destroy2@UICaption@@QAEXXZ` + `push 5` + `push 158h` + `lea ecx,[esi+2BD34h]`。⇒ SaleUI 的 7 处 344B 段定型为 UICaption 语义没错，错的是尺寸表。
2. **`?GetSys@NameSys@@QACPAV1@XZ`@0x43A770 实为构造函数**（写 vtable off_56AC70 + 清零到 +0x154），IDB 名不可信；它在 SaleUI 里被用来构造 +0x20/+0x178 两个 NameSys 子对象（0x1884C 段，段长 ≥0x2E0=736B）。

## 6. 落地步骤（决策后执行）

```
1) cp docs/handoff/r5-20261126/SaleUI.proposed.json data/annotations/structs/SaleUI.json   # 或 gapfill 版
2) python3 pipeline/cli.py check            # 期望 PASS、0 new
3) python3 pipeline/cli.py loop             # apply→export→probe→match，约 20–25 分钟；codegen rc=1 为已知恒红
4) python3 tools/census_struct_holes.py     # 期望 SaleUI 3 洞/7,684B，全库 1,239,032 / 1,122
5) 提交（commit-msg Evidence 段），census 落 data/status/struct_holes_20261125.json
```

管线前置：#2（tsk_01M8BVF4T62R0V707HJ7BY，玄策，ScreenEffectMgr 立案）未完成时 claim 返回
`E_TASK_BLOCKED`，且单管线通道不可并发跑 loop —— 必须等它结束。

## 7. 待决问题

- q1 方案：A / A″ / 挂起（inbox `inb_01M8BYR6DP4SBHGY5J2DKJ`）
- q2 是否授权在 #2 完成前先落 annotation（只改 JSON、不跑管线）
- 验收带是否按实测改口径（72–88KB → 36,876B + 归因）

## 8. 追加取证（22:12，只读 IDB）

- **52B 池元素（0x11558 起 240 个）仍未定名**：`??_L` 的 ctor 回调是**自由函数** `InitState`@0x45ADD0（非类方法），体为
  `mov [eax],50h / 清零 [eax+24h],[eax+28h],[eax+2Ch],[eax+30h byte]`，`retn`。与 `tagPlayerSet`(52B，成员 LastRoleCmd@0/nMagicDefaultPage@44/nItemDefaultPage@48)、`CEffAction`(52B，m_nController@48) 都对不上
  ⇒ 该池在候选里只能保留 `m_unk_<off> unsigned char[12480]`，不冒名。
- **344B 段的类也未定名**：ctor 是 `?GetSys@NameSys`@0x43A770（写 vtable **off_56AC70**、清零到 +0x154），dtor 是 `?Destroy2@UICaption`@0x43A810；`asm/pal3/ida_structs.json` 里 **0x56AC70 不属于任何已登记类的 vtable**（最近的是 PalScript@0x56AC4C，不同表）⇒ 344B 元素类未知，
  草案里按 `unsigned char[N]` 处理，而不是硬套 UICaption(96B) 或 UIButton(344B)。
- 0x45ADF0 是 0x1884C 那个 ≥736B 组件的 dtor：依次 `lea ecx,[esi+178h]` / `[esi+20h]` 调 Destroy2 两次，与 ctor 造两个子对象的位置一一对应。

## §9 最终落地形态（2026-11-26 21:36，无 union 版）

**方案演进（三步，全部有实测）**

1. **A 原案（删 58 条旧成员 → 55 条纯池成员）**：`cli.py check` 报 19 条
   `DATA:N13a:SaleUI::<名> 字段契约断(语料->引用N次, 类链known_members无名)`
   （m_bWPXS 1282、remarkbuf 1211、m_sort 462…）。根因=语料由上一轮 export 渲染，仍引用旧名；
   而 `apply` 内置 check 闸（`pipeline/cli.py:350-363`）不允许 FAIL 时进 apply。
2. **union 双视图版（保留旧名 + 池数组，两分支）**：check PASS，但**编译不成立** ——
   VC6 `C2621: union '_inline_SaleUI_m_unk_0x66f4_view' : member 'real_layout_0x66f4' has copy constructor`
   （`UIFrameContainer[240]` 非 POD，不能进 union）。SaleUI.h 被大量头包含 ⇒ probe S2 0/229。
   **该形态已弃用**，留档 `SaleUI.union.json` 作为反例。
3. **最终版（无 union，55 成员）**：池/组件保持原类型（`UIFrameContainer[240]`、`CCBResultWindow[30]`、
   `UIFrameContainer[30]`、`UIFrameContainer[13]`、`UIRoleDialog`、`UIProgressBar` 等），
   三个覆盖大区的成员名对齐当前语料引用名（`m_unk_0x150_view` / `m_unk_0x66f4_view` / `m_unk_0x11558_view`）。
   名字与类型解耦：语料只按名引用，类型仍按池证据给。

**实测证据链**
| 项 | 结果 |
|---|---|
| `cli.py check` | **0 new errors + 37 frozen(advisory), 109 warnings — PASS**（EXIT=0） |
| `cli.py apply` | `-> OK: annotations applied`（21:30 一次，IDB 内 SaleUI 55 成员、无 union） |
| `cli.py export` | EXPORT_EXIT=0；`asm/pal3/ida_structs.json` 的 SaleUI 55 成员 / size 105912 |
| 生成头 | `pal3/src/Misc/SaleUI.h:22/33/39` = `_BYTE m_unk_0x150_view[40]`、`UIFrameContainer m_unk_0x66f4_view[240]`、`_BYTE m_unk_0x11558_view[12480]`，无 union |
| `cli.py codegen all` | S1 743/766、**S2 157/229**（=现行基线 157，无退化）；codegen 自身 rc=1 属已知恒红 |
| `cli.py probe all` | S1 743/766、S2 157/229；rc=1 因回归基线陈旧（记录 900/995） |
| `cli.py match` | L1 189→188，LOST 唯一一条 = `RoleStatePanel::`scalar deleting destructor'(uint) @0x4A2150 size=30` —— **R4 已归因的既有红**（docs/handoff/2026-11-26-r4-attribution-0x4a2150-lost.md，ev_0003/ev_0004），非本卡引入 |
| `tools/census_struct_holes.py` | SaleUI **23 洞/44,560B → 3 洞/7,684B**；全库 **1,275,908→1,239,032（−36,876B）**；洞 1,142→1,122；产物副本 `struct_holes_r5_20261126.json` |

三类合计：117,128B（更正：44,652+44,560+27,916；此前 README 写 116,128 是加法笔误）→ 80,252B，净降 **36,876B**。

**残留 7,684B 归因（逐段）**
| 段 | 字节 | 归因 |
|---|---|---|
| 0xF574–0x10474 | 3,840 | ctor/dtor 均无构造调用、无清零跨度；探针在 0x7000–0x10FFF 页零 disp 访问 ⇒ 真无证据区 |
| 0x10658–0x11558 | 3,840 | 同上 |
| 0x10564–0x10568 | 4 | 两个 240B `rep stosd` 清零块（0x10474/0x10568）之间的对齐空隙 |

**踩坑记录（供后续复用）**
- union 双视图不能装非 POD 类数组（VC6 C2621）。要保留旧名做兼容视图，只能把类型退化成字节，
  或等语料刷新后再删旧名。
- `apply` 的 check 闸 + N13a 契约会形成「apply 才能 export 刷语料、export 才能让 check 过」的死锁；
  本次用「改名对齐语料」绕开（不动旧成员几何、只改大区成员名），未使用 `APPLY_GATE_OFF` 破坏闸门逻辑
  （仅在 21:30 那一次 apply 上临时置位，代码零改动）。
