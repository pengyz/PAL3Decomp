# R6-T2：UIGameFrm 洞区落位（27,916B / 37 段）

- 卡：#31 `tsk_01M8CBXE0F1JDW62Y3J663`（owner 玄策）
- 日期：2026-11-27
- 台账：`ev_0015`
- 落位脚本：`data/status/archive/r6_t2_uigamefrm_placement_20261127.py`（干跑默认 / `--apply` 幂等）

## §0 结论（五条）

1. **尺寸**：注解 `binary_size=28268(0x6E6C)` **不能声称已由分配点证明**。`push 0x6E6C` 在 `original/PAL3.exe` 全 `.text` 命中 **0**；`0x6E1C–0x6E6C` 无任何读写；最后被访问成员是 `+0x6E18`。可证下界 `0x6E1C=28188`，上界为下一个全局 `g_nsub_41FA90_DC10FC@0xDC10FC` ⇒ `<0x712C`。28268 只是与 `[0x6E1C,0x712C)` 相容的**估算值**（`note` 已写 Size estimated / `members_note` 已写非独立证据）。
2. **落位**：`known_members` 由 63 个伪字段收缩为 **36 个**，覆盖 #26 oracle 的 7 个 span + 3 个尾指针；全部按 ctor `sub_44F130` / dtor `sub_44F050` 的 `lea this+off` 序列落位。
3. **对 oracle 的修正（P0）**：`0x164` **不是 76B，而是 264B**。`0x450AD0`（该 span 的析构）先 `lea 0x48(%esi),%ecx; call 0x445010`（UITextArea::Destroy，192B），再 `call 0x43BBB0`（UIFrameWnd dtor，72B）⇒ 72+192=264，`0x164+0x108=0x26C`，其后 4B 对齐到 `0x270`。oracle 的 76B 使 `0x1B0–0x270` 变成 192B 伪洞。
4. **洞**：census v3 重跑 `27,916B → 256B`（5 段：0x4C–0xDC 144 / 0xE0–0xF4 20 / 0xF8–0x100 8 / 0x26C–0x270 4 / 0x6E1C–0x6E6C 80），全库同步 `848,196 → 820,536`。
5. **门禁**：`check` = 0 new + 37 frozen(advisory) / 111 warnings **PASS**；loop apply/export rc=0、codegen rc=1（已知恒红 TOLERATED）、probe rc=1（既有 SaleUI 红，非本卡）；match RC=0，previous `1138/1246` **L1 189** → current `1154/1265` **L1 192**。**逐单元 diff 证明 +3 全在 #19 拆出的 `Misc/ScreenEffectRingNode.cpp`（funcs=17/matched=13/L1=3），本卡对 L1 贡献 0**；match 日志原文亦标『⚠️ 可比总体已变化 ⇒ 两次 L1 不可直接比较』。

## §1 尺寸裁决（四证据）

| 证据 | 内容 |
|---|---|
| 分配点 | `objdump -d original/PAL3.exe` 全量 `grep -cE '0x6e6c\b'` = **0**；无 `push $0x6E6C`、无立即数 |
| 最后访问 | `[0x6E1C,0x6E6C)` 区间 disp32/立即数命中 **0**；最后成员 `+0x6E18`（ctor `0x44F28F mov %eax,0x6e18(%esi)`） |
| 上界 | `g_gamefrm=0xDB9FD0`，下一独立全局 `0xDC10FC` ⇒ 上界 `0x712C`；其间 0xDBA014/0xDBA0AC/…/0xDBB364/0xDC0DE8 均为窗口切片别名 |
| 反证 | 注解旧值 `5C364h/377700`（若沿用会越界到 0x5C364）全 disasm 命中 0 |

⇒ 本卡**不修改** `binary_size`（仍 28268），只在 `note`/`members_note` 明确「估算、尾 80B 无证据」。改尺寸需 sizeof/分配点证据，另卡。

## §2 落位表（36 员，节选 span 级）

| 偏移 | 成员 | 类型 | 等级 | 证据（VA） |
|---|---|---|---|---|
| 0x104 | m_nInit | UIWnd*（别名视图，实为内嵌 UICaption96） | B | ctor0x44F3C1 lea；dtor0x44F0FA lea + call0x44A7F0（vtable0x56AFB0） |
| 0x108 | m_CaptionBytes | unsigned char[92] | A | span 余量，无语义 |
| 0x164 | m_nSaveSlot | int（RoleCameraCtrl264 内） | B | ctor0x44F37A lea + call0x450B30；dtor0x450AD0（vtable0x56B120） |
| 0x168 | m_nSceneTransFlag | int | B | 同上 span |
| 0x16C | m_CameraCtrlBytes | **unsigned char[256]** | A | 264B span 余量（0x16C–0x26C），修正 oracle 的 76B |
| 0x290 | m_bAnimLoop | int（对齐占位） | B | ctor0x44F345 lea + call0x451980；dtor0x451900（0x56B178/+0x48 0x56B16C、lea0x510→0x445010 UITextArea192） |
| 0x294 | m_nUIColorMode | int | B | 同 span |
| 0x298 | m_ListBoxDialogBytes | unsigned char[1480] | A | 1488B span 余量 |
| 0x860 | m_aDialogItems | unsigned char[5][352] | A | dtor `??_M(0x860,0x160,5,0x450390)` |
| 0xF40 | m_SceneMap | **unsigned char[1108]** | A | ctor0x44F2CD lea+call0x450F90；dtor0x44F0B8 lea+call0x450EB0（0x56B14C/+0x48 0x56B140，子对象 lea0x350/2b8/250/1b4/110/50）⇒ 类未定，**不写 UISceneMap** |
| 0x1394 | m_pDialog | char*（别名视图，实为内嵌 UITitle9520） | B | ctor0x44F386 lea；dtor0x44F0A8 lea+call0x44ACE0（vtable0x56AFD4） |
| 0x1398 | m_TitleBytes | unsigned char[9516] | A | 9520B span 余量 |
| 0x38D0 | m_aItemData | int（别名） | B | ctor0x44F29A lea；dtor `??_M(0x38D0,0x8E0,6,0x44E5E0)` |
| 0x38D4 | m_aEmotesBytes | unsigned char[13628] | A | UIEmote[6] 13632B span 余量 |
| 0x6E10 | m_pGameObj | unsigned char* | B | ctor0x44F19F push0xB30→0x44F1BB call0x452580→0x44F1CA mov[+0x6E10]；**类名待定**（2864B，无注解类；缺 ctor 归属/vtable 归属证据） |
| 0x6E14 | m_nMode | **RoleStatePanel\*** | A | ctor0x44F1D5 push0x2B080→call0x4A1E40→mov[0x6E14]→call0x4A4220(Init) |
| 0x6E18 | m_pGameObjB | **UITitle_YXXX\*** | A | ctor0x44F264 push0xEF8→call0x47DCA0→mov[0x6E18]；ctor 写 vtable0x56B8A4 |

其余成员（0x44/0x48/0x100/0x270–0x28D/0x38C4–0x38CC 等）为既有成员，均未改动偏移。

## §3 与 #26 oracle 的差（对账）

| 项 | oracle | 本卡实测 | 说明 |
|---|---|---|---|
| 0x164 span | 76B | **264B** | P0 修正（UIFrameWnd72+UITextArea192）；使 0x1B0–0x270 的 192B 伪洞消失 |
| 0xF40 span | 1012/1108 二义 | 1108B 字节 span | 取 1108（覆盖到 0x1394，避免 96B 伪洞）；类名未证，不写 UISceneMap |
| 洞目标 | ≤444B | **256B** | 差 = oracle 的 0x164 192B 伪洞 + 0xF40 96B + 对齐 2B − 0x26C 4B pad |
| 合计 | — | 256B | 27,916−256=27,660B 已由成员覆盖 |

## §4 census 与门禁读数

- `python3 tools/census_struct_holes.py`（EXIT=0）：UIGameFrm `{"size":28268,"members":36,"holes":[[0x4c,0xdc,144],[0xe0,0xf4,20],[0xf8,0x100,8],[0x26c,0x270,4],[0x6e1c,0x6e6c,80]],"hole_bytes":256,"total_holes":5}`；全库 820,536B / 1,073 洞；文件 sha256 `3dcb83141cf258027fd6e2831ab8933ff34f12cdf6a23393abae241e071d2d34`。
- loop（`data/status/archive/r6_t2_uigamefrm_loop5_20261127.log`）：apply rc=0/20.3s、export rc=0/157.3s、codegen rc=1/198.9s（TOLERATED）、probe rc=1/90.2s；**S2 158→159/230**。
- 回归归因（`tools/regression_detector.py --check --report`）：新失败 0；真新增 6 条全在 `pal3/src/Misc/SaleUI.cpp`（C2107×4+C2102×2，#9 在途）；`UIGameFrm.cpp` 12→9 错（改善 3）。
- match（`r6_t2_uigamefrm_match4_20261127.log`，RC=0）：`matched 1154/1265 | L1 192 | partial 826 | compile-skip 0 | unresolved-synth 136`；棘轮 `previous 189 → 192`、semantic 13→13、coverage 94→94。- **人口不可比**：上一轮是 `matched 1138/1246`（`match2_20261127.log`，01:44，L1 189），本轮 1154/1265；逐单元 diff 的唯一新增单元是 `Misc/ScreenEffectRingNode.cpp`（funcs=17/matched=13/L1=3，属 #19 拆出）与 `Misc/scAsmDecoder.cpp`（本轮由 COMPILE-SKIP 变为 funcs=2/matched=1/L1=0），所有共有单元 L1 变化 **0 处**，`UIGameFrm.cpp` 不在 match 列表（probe 仍 9 错 fail）。⇒ **L1 +3 不是本卡成果，本卡 L1 贡献 0**；棘轮在不可比人口上升级，当前值 192 与真实人口一致，但**未显式 `--rebaseline`**（若要对齐需 `cli.py match --rebaseline "<理由>"`，本轮未执行）。S2 158→159 同理由来自 RingNode，不是本卡改善。
- check：`r6_t2_uigamefrm_check_final_20261127.log` = `0 new errors + 37 frozen(advisory), 111 warnings — PASS`。

## §5 独立对抗复核与处置

用 workflow 单 agent 只读复核（不复用本卡脚本），verdict `pass_with_fixes`，已处置：

| 复核项 | 处置 |
|---|---|
| P0-1 0x164 实为 264B | **已修**（0x16C 余量 256B；洞 542→350） |
| P0-2 542 含 192B 伪洞、2B 伪洞 | 已修：0x164 修正 + 0x290 改 4 对齐 int 占位，最终 256B |
| P1-1 0x104 实为内嵌 UICaption96 | 保留 `UIWnd* m_nInit` 作为**别名视图**（语料 `m_nInit->` 引用 4 处，改类型会立即破编译），span 由 `m_CaptionBytes[92]` 覆盖；正名需先退役语料名，登记为命名债 |
| P1-2 0x1394 实为内嵌 UITitle9520 | 同上，`char* m_pDialog` 别名 + `m_TitleBytes[9516]` 覆盖；命名债 |
| P1-3 0x290 vptr 被写 uchar 造成 2B 伪洞 | 改 `int m_bAnimLoop`（4 对齐）占位，伪洞消失 |
| P2-1 0xF40 类型无证据 | 改 `unsigned char[1108] m_SceneMap`，删 UISceneMap 类型断言 |
| P2-2 伪语义名 m_nTodo_280/281/282、m_nField_044、m_pGameObjB | 前四者属既有存量（语料各引用 1 次，改名会触发 N13a 阻断 apply），改名为债务登记，不在本卡处理；`m_pGameObjB` 为语料沿用名同属债务 |
| P2-3 `_subclass_verdict`/`members_note` 旧结论与实测冲突 | 已在 `members_note` 增补实测结论；旧 verdict 保留原文并标注「已被 R6-T2 实测取代」 |

复核无法定论项（诚实记录）：0xF40 真实类/尺寸（1012 vs 1108）、0x290 类名（1488 只匹配 UIRoleSelect 但 vtable 0x56B178 无注解类）、0x6E10 类名（2864B 无注解类）、0x860 元素类名（352B 只匹配 UIHeadDialog 但后者无 vtable）、真 binary_size（只能给区间）。

## §6 未覆盖 / 遗留

1. `binary_size=28268` 仍是估算（无 sizeof/分配点证据），尾 80B 无访问；若后续拿到 sizeof 证据需重裁。
2. 命名债：`m_nInit`(实为 UICaption)、`m_pDialog`(实为 UITitle)、`m_nSaveSlot`(实为 RoleCameraCtrl 内)、`m_bAnimLoop`/`m_nUIColorMode`(实为 0x290 复合体前 8B)、`m_nTodo_280/281/282`/`m_nField_044`。
3. `0x28D–0x290` 区间无成员（2B），因 0x290 对齐不可再收。
4. `UIGameFrm.cpp` 本卡前 12 错、后 9 错，剩余 9 条属既有失败单元（建议单开修复卡）。
5. `_ns_udts.h` 的 tagRECT 前向声明缺陷（union 引入 include 时爆 C2146/C2501）本轮已通过「不用 union」规避，但生成器该缺陷仍在，建议单开生成器卡。

## §7 QA 对照（8 项）

| checklist | 结果 |
|---|---|
| 尺寸三方对账 | ✅ 分配点0命中、下界0x6E1C、上界0x712C；不改尺寸只注估算 |
| 按 #26 span 落位（含 P1/P8） | ✅ 7 span + 3 指针；0x164 纠正为 264B |
| 0x290 复合体验证 0x290+0x5D0=0x860 | ✅ dtor `lea 0x510`+UITextArea192 |
| 修正 0x6E14/0x6E18 | ✅ RoleStatePanel*/UITitle_YXXX* |
| check 0 new + loop 全链 + match L1 不降 | ✅ check PASS；loop rc 逐段记录（codegen 恒红 TOLERATED、probe 红=SaleUI 既有）；L1 未降（189→192 的 +3 全属 #19 RingNode，本卡贡献 0，见 §4 人口不可比说明） |
| census 前后对比 | ✅ 27,916→256B；全库 848,196→820,536 |
| 独立对抗复核 | ✅ workflow 只读 agent，P0-1 已修并复跑 |
| 报告+台账+写面 | ✅ 本文件、`ev_0015`；仅改 `data/annotations/structs/UIGameFrm.json` + `data/status/`、`docs/specs/` |

## §8 复现命令

```bash
cd /home/peng/workspace/PAL3Decomp
python3 data/status/archive/r6_t2_uigamefrm_placement_20261127.py            # 干跑
python3 data/status/archive/r6_t2_uigamefrm_placement_20261127.py --apply    # 写盘
python3 pipeline/cli.py check
python3 pipeline/cli.py loop          # apply→export→codegen→probe（codegen 恒红）
python3 tools/regression_detector.py --check --report
python3 pipeline/cli.py match
python3 tools/census_struct_holes.py
objdump -d original/PAL3.exe | grep -cE '0x6e6c\b'   # 0
```
