# 待批决策包：L-VAR 引脚三选一 + cls_43dfc0 建档

- 卡：**#14 tsk_01M8C1YYBJKXA7NNE7D7AM**（只读决策包，writeScopes=`docs/audit/`）
- 生成时间：2026-11-26 22:04；**22:30 返工修正版（按白砚验收意见：更正 §2.3 证据错置、#16 状态、UIListBox 引用计数口径、数据卡 #2 编号）**
- 性质：只读盘点。本卡未改名、未改 annotation、未跑管线（§6 自证）。
- 读数时点重要：生成期间有并发 loop（22:05–22:11，PID 4158799；该轮在 probe 中止）与 `probe all`（PID 4170944）在跑，S2 读数会漂（§2.3 给出区间与原因）。

---

## §0 需 Human 拍板的问题清单（一句一题，可直接复制进 askHuman）

### Q1（L-VAR 引脚怎么处理）

> L-VAR（RoleStatePanel 的 `m_bRtVisible` 引脚写法）导致的 C2440 与 L1 掉 1，选哪种修法？
>
> - **A（推荐方向，验证未完成）**：在 `pipeline/gen/stages/stage5_fixup.py` 的 `_path_is_pointer` 补「数组衰减」判据（工作树已有实现 + 6 条单测，未提交）。它是三条路里唯一能同时修 C2440 且保字节的（B/C 已实测否掉，§2.1）。**但 A 对 L1 的效果目前没有实测**：22:05 那轮 loop 在 probe 就中止、match 未跑；过去唯一一次 L1=188 的读数（19:29）是 A 生效**之前**的（§2.3）。建议拍板为：先修 #16 的 apply 异常并让 probe 通过，再跑一次能到 match 的干净 loop；L1 回 189 则提交 A，不回则转归因卡。
> - B：只改 annotation 引脚类型（成员类型换 `unsigned long *` / `char *` / `void *`）——数据卡 #2（`tsk_01M8BWFAS4FT282VX3NPP2`，与看板 #2 ScreenEffectMgr 不是同一张）的试验已证不可行（§2.1 矩阵）。
> - C：改成员布局（拆成 8 个 byte 员，或改 `unsigned long[2]` 数组视图）——同一张数据卡 #2 的试验已证会退化（字节写变 1 字节 / 索引步长变 4）。

### Q2（cls_43dfc0 建不建档、先做多少）

> 1208 字节的未名类（ctor `0x43DFC0`、表 `0x56AD40`）是否现在建档 `cls_43dfc0.json`，首版做到哪一步？
>
> - **①（推荐）**：只建结构体（`binary_size=1208`、`bases=[UIWnd@0]`、字段图），**不写 vtables 段、不迁方法**，`UIListBox` 名继续绑 72B 类；方法迁移与名义重锚另立战役。
> - ②：建档并把 `UIListBox.json` 里 36 条 1208B 域方法迁到 `cls_43dfc0`（两类无继承关系，会断 1154 行 `UIListBox*` 静态引用/1204 处出现，§3.3/§3.4）。
> - ③：建档 + 名义重锚（`UIListBox` 名改绑 1208B 类），联动 4 个类的 bases 晶格（check C10 约 280 项冲突）。
> - ④：暂不建档，维持现状（36 条方法的归属矛盾留到名义战役一起处理）。

> **附带需知晓（不单独拍板）**：工作树里方案 A 的实现（`stage5_fixup.py` 10+/3−、`tests/test_stage5_array_decay.py` 6 tests）**不是本卡写的，也没有任何卡的 writeScope 覆盖 `pipeline/gen/`**；测试文件 docstring 自述「[#6 B 变体]」。提交前需要有人认领这条改动（或回溯来源），否则管线改动无归属。

---

## §1 账目锚点

| 项 | 一手材料 | 时点/状态 |
|---|---|---|
| L-VAR 归因卷宗 | `docs/handoff/2026-11-26-r4-attribution-0x4a2150-lost.md`（256 行），ev_0003/ev_0004 | 2026-11-26，两条 A/open |
| L-VAR 可行性试验 | `data/status/lvar_feasibility_20261126.md`（161 行，头部自注卡号 `#2（tsk_01M8BWFAS4FT282VX3NPP2）`，**非看板 #2**） | 数据卡 #2 产物 |
| 双类裁决卷宗 | `data/status/uilistbox_chain_adjudication_20261126.json`：`class_big_1208B` / `class_small_72B` / `debt_ledger` #1–#6 | 2026-11-26 |
| 知识库对应段 | `docs/knowledge/struct_hole_fill_campaign_20261126.md:140/143/186/232` | — |
| 交接文档挂账 | `docs/handoff/2026-11-26-struct-hole-campaign-handoff.md:84-85`（三选一 + cls_43dfc0） | 已加修正注 #10 |
| base_size 修复 | `data/annotations/structs/{RoleStatePanel,UIFrameContainer}.json` 各 `"base_size": 72`；`tests/test_base_size_projection.py`；`pipeline/_logs/apply_export_basefix_20261126.log` | #8 已验收 |

---

## §2 L-VAR 引脚三选一

### §2.1 三个选项逐项

| 维度 | A：stage5 补数组衰减（推荐） | B：改 annotation 引脚类型（L-VAR） | C：改成员布局 |
|---|---|---|---|
| **做法** | `_path_is_pointer(path, vt, ctx, array_decays=False)` 增末段 `[...]` 判据；调用点 `stage5_fixup.py:871` 传 `array_decays=('[' not in e)`，让 `this->m_bRtVisible`（数组成员）在需要指针时产出 `(_DWORD *)` | 把 `m_bRtVisible` 声明改成 `unsigned long *` / `unsigned char *` / `char *` / `void *` 之一 | 拆成 8 个 byte 员，或改 `unsigned long[2]` / union dword 视图 |
| **影响面（文件/单元）** | `pipeline/gen/stages/stage5_fixup.py`（+1 参、1 判据、1 调用点）+ `tests/test_stage5_array_decay.py`；产物侧只影响「C2440 cast 规则」命中的表达式，当前语料里命中单元=**`pal3/src/Misc/RoleStatePanel.cpp` 一个**（R4 §3.2；改前仅此单元有该形态） | `data/annotations/structs/RoleStatePanel.json` 一个字段 → apply→export→codegen 全链重渲；影响面同 C（该结构体被 RoleStatePanel 单元与其它引用该结构的单元使用） | 同 B，且成员布局变化会牵动 `sizeof(RoleStatePanel)` 与所有 `m_bRtVisible[i]` 使用点 |
| **L1 风险（棘轮 189 / 实况 188）** | 中：R4 有单函数复现（补 `(_DWORD *)` 后 30/30 字节全同、2 处 REL32 don't-care、18/18 基线行恢复），但**尚未通过一次完整的真实 loop 复现**——22:05 那轮在 probe 中止、match 未跑（§2.3），故 L1 是回 189 还是仍 188，目前**无实测** | 高：C 变体编译过但把两笔 dword 清零改成 1+1 字节写（`88 9e 20 5e 02 00` / `88 9e 21 5e 02 00`），`??_G @0x4A2150` 不可能回字节全同 ⇒ L1 回不到 189，且新增字节差异扩散到 OnMessage 清零段 | 最高：F 变体实测 `[4]` 步长变 4（+0x10 而非 +0x4），污染 6+ 处按字节索引（`mov ecx,[esi+eax*4+...]` vs 原始 `[esi+eax*1+...]`）⇒ 多处 partial 恶化 |
| **S2 风险** | 低：R4 补 cast 后该单元可编译；22:02:33 实测 `pal3/src/Misc/RoleStatePanel.cpp` status=**ok**、errors=[]。全局风险=规则收紧误伤其它数组衰减表达式（6 条单测覆盖 true/false、指针/标量不变） | 中：A/B 变体仍 C2440（编译不过），C 变体编译过但语义退化，D 变体 C2100+C2036/C2120 编译失败 | 中：F 变体编译过但索引语义污染；拆 8 员还需改 `[m_nRtIndex]` 逐字节判断逻辑 |
| **回退成本** | 低：`git checkout pipeline/gen/stages/stage5_fixup.py` 即回到原状（10 行 diff），不涉及 annotation/IDB，零 apply 成本 | 高：annotation 改动需 apply→export→codegen→probe 全链（约 6 分钟 apply/export + 20–25 分钟 loop），且改过 IDB 后回退要显式钉回类型 | 高：同 B，且成员增删触发 `check_annotations` 布局校验与 s4 全量重比 |
| **是否管线改动** | **是**（codegen stage5 规则 + 单测）——需按管线改动报批、且要有归属 | 否（纯 annotation） | 否（纯 annotation） |
| **证据** | ev_0003/ev_0004（A/open）；R4 §3.2/§4 实测 | 数据卡 #2（`tsk_01M8BWFAS4FT282VX3NPP2`）矩阵 A/B/C/D 全败（`data/status/lvar_feasibility_20261126.md`） | 数据卡 #2 矩阵 E/F：E=赋值行 cast 可编译且 4+4 字节（正因如此才需要 A 在生成侧统一产出；F 拒绝） |

证据引用：ev_0003（`??_G @0x4A2150` 30B 丢失）与 ev_0004（`m_bRtVisible` 引脚冲突）均为 A 级/open，登记于 `data/status/evidence_ledger.json`；归因全文见 `docs/handoff/2026-11-26-r4-attribution-0x4a2150-lost.md` §3.2/§4。

**推荐 A，否决 B 与 C 的理由**：
1. B 的四个变体没有一种同时满足「编译过」+「保持两笔 dword 清零」——`unsigned long*`/`unsigned char*` 仍 C2440，`char*` 退化字节写，`void*` 不可解引用（C2100 等）。数据卡 #2（`tsk_01M8BWFAS4FT282VX3NPP2`）已实测，不是推断。
2. C 的两种布局改法分别破坏 `[m_nRtIndex]` 逐字节判断（拆 8 员）与索引步长（`unsigned long[2]`）。数据卡 #2 的 F 变体实测污染 6+ 处。
3. A 的机制在 `pipeline/gen/stages/emit_cpp.py:797-807`：当前正则只替换声明行、不插 cast ⇒ 单靠 annotation 改不出「赋值行带 cast」的形态（E 变体的 4+4 字节正确性只能由生成侧产 cast 才能稳定复现）。A 是唯一既修 C2440 又保字节的路径，且 R4 已用 30/30 字节与 18/18 基线行证明。

### §2.2 关键机制（为什么单靠 annotation 不够）

- R3 `ac9c67673` 把 `0x25B78` 落 `unsigned char[8]` → export 重渲 OnMessage → hexrays 局部变量成 `_DWORD *m_bRtVisible` → stage5 `_fix_c2440_casts` 未命中（路径判据只看「指针形」，数组成员被判非指针）→ 生成源 L777 裸赋值 → C2440。
- `data/status/lvar_feasibility_20261126.md` 结论句：**「L-VAR 只改声明行，无法同时满足 C2440 与两笔 dword 清零」**。
- 生成源现状（工作树）：`pal3/src/Misc/RoleStatePanel.cpp:777` = `        m_bRtVisible = (_DWORD *)this->m_bRtVisible;`，L99 = `*(_DWORD *)this->m_bRtVisible = 0;` ⇒ 说明工作树里的 stage5 改动已经生效。

### §2.3 工作树现状与验证状态（重要，2026-11-26 22:29 按验收意见更正）

| 事实 | 证据 |
|---|---|
| 方案 A 实现已在工作树，**未提交、无卡认领** | `git status --short` = ` M pipeline/gen/stages/stage5_fixup.py`、`?? tests/test_stage5_array_decay.py`；`git log -S array_decays` 无提交 |
| diff 规模 | `git diff pipeline/gen/stages/stage5_fixup.py` = 10+/3−；参数 `array_decays=False`、末段判据 `if array_decays and idx == last and re.search(r'\[[^\]]*\]\s*$', mt): return True`、调用点 `stage5_fixup.py:871` |
| 单测 | `python3 -m pytest tests/test_stage5_array_decay.py -q` → **6 passed in 0.05s**（含 Family2 断言 `m_bRtVisible = (unsigned long *)this->m_bRtVisible;`） |
| codegen 已吃到改动 | `pal3/src/Misc/RoleStatePanel.cpp:777` = `m_bRtVisible = (_DWORD *)this->m_bRtVisible;`，L99/L100 为 `*(_DWORD *)... = 0;` 与 `m_bRtVisible[1] = 0;` |
| 单元编译 | 22:10:49 普查：`pal3/src/Misc/RoleStatePanel.cpp` status=**ok**、errors=[] |
| 结构体偏移正确 | `pal3/src/Misc/RoleStatePanel.h:56` `_BYTE m_bRtVisible[8]; // +0x25B78`、`:87` `// total size: 0x2B080 (176256)` —— #8 的 base_size 修复在 export 后仍生效 |
| **22:05 loop 只跑到 probe，未到 match** | `data/status/archive/r4_sefmgr_loop_20261126.log`（22:04:28）尾行：`[loop] 出现**非容错**失败（probe）⇒ 中止后续阶段`；汇总 `apply rc=0/18.5s · export rc=0/152.2s · codegen rc=1/186.9s · probe rc=1/87.7s`（无 match）。`data/status/_loop_last.json`（22:11:58）stages=`{apply:0, export:0, codegen:1, probe:1}`、`failed=["probe"]`。`pipeline/_logs/loop_match.log` mtime=**19:29:02**（本轮未重写）。 |
| 22:05 的 probe 为何失败 | codegen/probe 均 rc=1、S2 158/229；`r4_sefmgr_loop_20261126.log` 内为 `[Baseline] NOT refreshing: regressions detected (exit 1)`（回归检测判 not refresh），属并发卡 annotation 在途改动引出的回归，不是本卡可控项 |
| **19:29 的 ratchet 数字（不是本轮）** | `pipeline/_logs/loop_match.log`（19:29:02）：`[L1 ratchet] previous 189 -> current 188`、`population matched=1152/1259 -> 1132/1238`、`carrier.paired 93 -> 91`、LOST `RoleStatePanel::scalar deleting destructor'(uint) @4858192 size=30`、`REGRESSION`；对应档案 `data/status/archive/s4_diff_detail_regressed_20261126T192902.json`。**这些是 A 生效前的读数**，不能当作 A 的效果。 |
| apply rc=0 但不等于 #16 已修 | `pipeline/ida/apply_annotations.py` 无 diff（mtime 20:36）；`:2026` 仍用 `gb_sig_ok/gb_sig_try/gb_sig_skip`，三变量 `:2194` 才初始化；调用点 `:4123` 的 `_fix_gbengine_import_slots()` 在 `try/except` 内并只 log `[!] import slot signature pass raised` ⇒ 异常被吞、apply 仍 rc0，**#16 仍 pending**，apply 产物可能缺 import-slot 签名修正 |
| 其他 match 档案的用途限制 | `...T214644.json`（21:46:44，l1=188/partial810/units148）是另一次 match 的 regressed detail；`...T221209.json`（l1=31/units39）只是子集产物，二者都**没有对应的本轮运行日志**，无法证明是否消费了 A 的改动。同期 baseline/detail 现为 189/827/149。 |

⇒ **结论（更正后）**：A 的实现已被 codegen 吃到（源里有 cast、单元 ok、偏移正确），但**还没有任何一次跑到 match 的 run 能给出「A 之后 L1 是多少」**。要拍板落地，先补这一次 run；不能拿 19:29 的 188 当证据说「A 没用」，也不能说「A 已修好」。

---

## §3 cls_43dfc0 建档

### §3.1 现状（可复现）

双类并存（纯二进制定谳，`data/status/uilistbox_chain_adjudication_20261126.json`）：

| | 72B 类（现 `UIListBox` 名） | 1208B 类（待建档 `cls_43dfc0`） |
|---|---|---|
| ctor | `0x43DCD0` | `0x43DFC0` |
| vtable | `0x56AD20`（7 槽） | `0x56AD40`（8 槽：`0x445E70,0x43E8A0,0x43EBE0,0x43E520,0x445B90,0x43E100,0x43E480,0x43E1C0`） |
| dtor | deleting `0x43DCF0` / full `0x43DD10` | deleting `0x43E100` / full `0x43E120` |
| 尺寸证据 | ctor 字段写最大 `[esi+0x44]`、尾 `0x48=72` | 写面收口 `[esi+0x4B4]+4=0x4B8=1208`；真 new 面 `push 0x4B8→operator new 0x55353B→call 0x43DFC0` ×3（`0x519D05/0x51A558/0x51AEAA`） |
| 字段图 | `m_selcolor@0x44` | `m_selcolor@0x44`、`m_showGrayBk@0x48`、`m_scrollbar@0x50`（`UIScrollBar` ctor `0x4410F0`/dtor `0x4411D0`）、列数组 `@0x1B4`（elem `0x43DF10/0x43DF20`，stride 8，count `0x54`）、`m_firstshow/m_onsel/m_locksel@0x4AC/0x4B0/0x4B4` |

PDB 参考（仅参考，REPO 铁律）：PAL3A `<class name=UIListBox length=0x508>`，比 PAL3 实测 `0x4B8` 多 `0x50` 尾段——**说明 PDB 的 UIListBox 是续作版本，不能直接拿名字定谳**（这也是名义重锚必须由 Human 拍板的原因之一）。

### §3.2 方法数（命令核实「约 34」）

命令（只读）：

```bash
python3 - <<'PY'
import json
d=json.load(open('data/annotations/structs/UIListBox.json'))
ms=d['methods']; a=lambda k:int(k,16)
ranges=[(0x43DFC0,0x43DFC0),(0x43E100,0x43E120),(0x43E000,0x440000),(0x451850,0x451C80),(0x452600,0x452600)]
hits=[(k,v.get('name')) for k,v in ms.items() if any(lo<=a(k)<=hi for lo,hi in ranges)]
print('total methods entries:',len(ms)); print('1208B domain hits:',len(hits))
for k,n in sorted(hits,key=lambda x:a(x[0])): print(k,n)
PY
```

输出（2026-11-26 22:04 实测；22:35 复核时把域上界从 0x43F800 放到 0x440000，补回 `0x43FE90 GetCurSel`）：**`total methods entries: 68`，`1208B domain hits: 36`**。

- 36 条全部属 `UIListBox.json`（现归属 72B 类 `UIListBox`），逐条清单见附录 A。
- 现归属落点：注解 `data/annotations/structs/UIListBox.json`（`binary_size=72`、`base_size=68`、`bases=[UIWnd@0]`）；生成树 `pal3/src/UI/UIListBox.h`（3511B，`class UIListBox : public UIWnd`，成员 `m_selcolor@+0x44`，`// total size: 0x48 (72)`）与 `pal3/src/UI/UIListBox.cpp`（71,764B）。1208B 类当前**没有任何注解文件**，即 `cls_43dfc0.json` 尚不存在。
- 36 条内 **4 条带 `_misattrib_evidence`**（`0x43F560/0x43F690/0x43F6A0/0x43F6D0`）、5 条证据等级 A/chain_unified；全表 68 条口径下 misattrib 共 10 条（其余 6 条落在 1208B 域外，随 #5 误名普查单独处理）。
- 1208B 类的 **ctor `0x43DFC0` 与两个 dtor `0x43E100/0x43E120` 在 methods 中 ABSENT**（三条都没录）⇒ 「约 34」核实为 **36 条存量 + 3 条未录 = 39 个函数条目**。`debt_ledger` #1 列的 36 址与这 36 条存量**逐一对上**（36⊂methods 全命中，差集为空，22:35 复核）；上一版写「差 1」是我的域上界取 0x43F800 漏了 `0x43FE90`，已更正。
- 另有既存误名：`0x43DF10 CalHeightCount` / `0x43DF20 GetItemPos` 实为 1208B 类列数组的 elem ctor/dtor；`0x43DEA0 AddColumn` 实为读表尾 float 12.0 的 stub，`0x43DEB0/0x43DEC0` 同型（`debt_ledger` #5）。

### §3.3 调用点

| 面 | 数量 | 证据 |
|---|---|---|
| 1208B ctor `0x43DFC0` 的 call 位点 | **35 个** | `class_big_1208B.consumers`：new 3 + `InitState` 7 + `LoadStateUIRenderTarget` 8 + `LoadBigMapRenderTarget` 6 + `LoadGameFrmRenderTarget` 6 + `GetDataPtr` 2 + `0x451890` 等 |
| 其中真 `new` 面 | 3 | `0x519D05/0x51A558/0x51AEAA`（`push 0x4B8 → operator new 0x55353B → call 0x43DFC0`） |
| 嵌入构造面 | 8 | `LoadStateUIRenderTarget` 内 `lea ecx,[esi+0x3A8C4]…[esi+0x3AD7C]` 步距 `0x4B8` |
| 静态类型引用面（迁移风险度量） | **1154 行**含 `UIListBox *`/`UIListBox*` 模式（`-o` 计 **1204 处出现**，分布 63 个 cpp 文件） | `grep -rn "UIListBox \*\|UIListBox\*" pal3/src --include='*.cpp' \| wc -l` = 1154；`grep -rho "UIListBox \*\|UIListBox\*" pal3/src --include='*.cpp' \| wc -l` = 1204；`grep -rl … \| wc -l` = 63 |

### §3.4 建/不建两种后果

| 方案 | 对 S2/L1 | 对命名/后续 | 风险 |
|---|---|---|---|
**不建档** | 零影响 | 36 条方法继续挂在 72B 类 `UIListBox` 名下；`UIListBox.json` 声明 `binary_size=72` 却含访问到 `0x4B8` 的方法（归属矛盾持续）；误名普查（#5）无法收敛；名义重锚战役缺目标结构 | 低（但债务持续累积） |
**建档、首版只建结构体（推荐 ①）** | 零影响（新类无人实例化；不写 vtables 段可避开槽函数归属未定的发射断链） | 先把 1208B 的 `binary_size/bases/字段图` 固化为可引用结构；名义重锚与方法迁移可随后按批做 | 低 |
**建档 + 迁 36 条方法（②）** | 编译面无收益，且**很可能断链**：两类无继承关系（1208B 只派生 UIWnd），方法定义换 owner 后，1154 行/1204 处 `UIListBox*` 静态引用找不到成员（C2039 类） | 方法归属变正确，但调用点全断 | **高** |
**建档 + 名义重锚（③）** | 需重渲 4 个下游类的 bases 晶格（SkillUI/StateUI/CCBUICtrl/RoleStatePanel），check C10 **约 280 项布局冲突** | 命名最终正确（若 Human 认可 PDB/表证据） | **最高**，非单卡可落 |
**暂不建档（④）** | 零影响 | 同「不建档」，债务原样留到名义战役 | 低 |

> 说明：②的「断链」是按 C++ 类型的静态推断（成员函数定义在另一个无继承关系的类上，调用点类型是 72B 类）；本项目对 1154 行/1204 处引用未做逐点复核，故标为**未验证风险**而非已实测。

### §3.5 若建档，建议的实施切分（首版做多少方法）

- **首版（本建议）**：`data/annotations/structs/cls_43dfc0.json` —— 只写 `binary_size=1208`、`bases=[UIWnd@0]`、`known_members`（0x44/0x48/0x50/0x1B4/0x4AC/0x4B0/0x4B4 七处字段图；语义按 PDB 参考 + 二进制写面，不新造名），**methods 0 条、vtables 段不写**。
- **第二批（名义裁决后）**：8 个虚槽函数（`0x43E8A0/0x43EBE0/0x43E520/0x43E100/0x43E480/0x43E1C0` + ctor/dtor）迁归 `cls_43dfc0`，同时建 `vtables` 8 槽；此时 `UIListBox` 名归属已定，调用点类型跟着改。
- **第三批**：剩余 27 条非虚方法逐条按「body 最大 this 偏移 / 字段引用」取证迁移（先排除 #5 的 10 条误名与 8 处疑似非成员）。
- 不建议「全 36 条一次迁」：既断调用点，又把 10 条已标 misattrib 的条目一起搬错家。

### §3.6 归属证据缺口（还缺哪条才能定谳）

1. **类名**：PDB `UIListBox` 尺寸 `0x508` ≠ PAL3 实测 `0x4B8`（尾段差 `0x50`），不能直接继承名；需要「表 `0x56AD40` 曾是 UIListBox 本体」的独立佐证（REPO 20261016 注记）与 Human 裁决。
2. **36 条方法逐条归属**：现在只有「地址域聚类」这一层证据；10 条已标 misattrib。定谳需要每条 body 的 `this` 偏移上界 + 字段引用落在 1208B 布局内（A 级）。
3. **字段语义**：0x44/0x48/0x50/0x1B4/0x4AC-0x4B4 有 PDB 逐位吻合（强），但 PAL3≠PAL3A，字段名仍属「参考级」；`m_scrollbar` 子对象内布局尚无独立证据。

---

## §4 两项的关系与建议顺序

- 两项**互不阻塞**：L-VAR 只碰 `pipeline/gen/stages/stage5_fixup.py`（+单测）；cls_43dfc0 只碰 `data/annotations/structs/`（新增文件）。无文件重叠。
- 但**共用同一条验证链**：都要跑 loop（apply→export→codegen→probe→match）。当前链路的实测状态是：22:05 loop 在 probe 中止（回归检测 exit1）、**match 未跑**；apply 虽 rc=0，但异常被 `try/except` 吞掉（#16 仍 pending，§2.3）⇒ 两项都还缺一次干净 run。
- 建议拍板与排期（2026-11-26 22:29 更正）：

```
① 修 #16 的 apply 异常（gb_sig_* 先用后定义，apply_annotations.py:2026 / :2194；现被 :4123 try/except 吞成 rc0）
② 让 probe 过：并发卡的 annotation 改动落地/稳定后再跑；否则 loop 永远停在 probe
③ 跑一次能到 match 的干净 loop（apply→export→codegen→probe→match）→ 拿 A 的真实 L1 读数
   · L1 回 189 ⇒ 批准 A 落地（10 行 diff + 单测一并提交，指定归属卡）
   · L1 仍 188 ⇒ 转归因卡（谁丢失了 19:29 那轮的 matched −20 / carrier −2，为什么 identity diff 指 0x4A2150）
④ Q2 首版 cls_43dfc0 结构体（只建 struct，不写 vtables、不迁方法）：与①②并行，无文件冲突
⑤ 名义重锚战役（Human 裁 Q2③ 才开；约 280 项 C10 冲突单独评估）
⑥ 批 A 方法迁移 / #5 误名普查（随名义战役）
```

- 与在跑卡：L-VAR 与 #8（已 done）有依赖（#8 的 base_size 修复是 §5 偏移风险的前提）；cls_43dfc0 与 #9 SaleUI（改 `SaleUI.json`）、#7 MagicUI 无文件交集，但 #9 的 loop 会刷新 probe/struct_holes 时点。

---

## §5 未决与口径不一致（需后续统一，不影响本次拍板）

1. **A 的 L1 效果无实测（已按验收更正）**：22:05 loop 在 probe 中止、match 未跑；此前唯一的 188 读数是 19:29（A 生效前）。所以「A 能回 189」只有 R4 的单函数级证据，缺一次完整 run。**上一版报告把 19:29 的 ratchet 数字误当 22:05 本轮，已更正**（§2.3）。
2. **stage5 改动的归属未登记**：工作树 `stage5_fixup.py` 10+/3− 与 `tests/test_stage5_array_decay.py` 无卡认领（测试 docstring 写「[#6 B 变体]」）。Q1 批准前建议先指定归属卡，否则违反「管线改动须有证据与归属」的常规。
3. **L1 尚无任何「A 之后」的实测**：match 自 19:29 未再跑；本包既不宣称已恢复、也不宣称无效。
4. **方法数口径（22:35 已闭合）**：`debt_ledger` #1 的 36 址 = 域扫 36 条存量（差集为空），外加 ctor 与两 dtor 3 条 ABSENT ⇒ 共 39 个函数条目。建议名义战役开工前把「迁移清单」固定成一份文件（含算入/排除理由）。
5. **S2 读数时点**：本包引用 21:52:56（161/229）与 22:02:33 / 22:10:49（158/229）三个样本，均为并发卡在跑期间的中间值；不作为门禁依据。
6. **apply 异常吞掉的治理项**：#16 修好前，所有 loop 的 apply 段都可能「rc0 但漏修」，后续引用 loop 产物时要注明这一点。
7. **PDB 版本差**：`UIListBox` PDB 0x508 vs PAL3 0x4B8，字段名/方法名只能参考，不能当 A 级证据。

---

## §6 只读自证

```bash
$ git status --short | grep -E "docs/audit|stage5|test_stage5"
 M pipeline/gen/stages/stage5_fixup.py        # 非本卡改动（§2.3）
?? docs/audit/                                # 本卡唯一新增（含本报告）
?? tests/test_stage5_array_decay.py          # 非本卡改动
$ ps aux | grep pipeline/cli.py | grep -v grep
... timeout 1900 python3 pipeline/cli.py loop      # 他卡在跑（PID 4158799）
... python3 pipeline/cli.py probe all               # 他卡在跑（PID 4170944）
```

- 本卡执行的命令全部只读：`git status/grep/diff/log`、`python3` 读取 JSON、`pytest` 单跑既有未提交单测（读源码，不写仓库）。
- 未改任何 `data/annotations/**`、基线（`data/status/s4_baseline.json` 等）、生成树（`pal3/src/**`）。
- 未启动任何 `pipeline/cli.py` 子命令。

---

## 附录 A：1208B 域 36 条方法逐条（来源文件均为 `data/annotations/structs/UIListBox.json`）

命令与 §3.2 同一条；表由该命令输出的 `methods` 字段渲染（偏移=现 name 键，现名=`methods[*].name`，等级=`evidence_level`）。

| # | 偏移 | 现名 | 等级/标记 |
|---|---|---|---|
| 1 | `0x0043E1C0` | `CalScrollBarRange` | unverified |
| 2 | `0x0043E330` | `GetSel` | unverified |
| 3 | `0x0043E3B0` | `GetLockSel` | unverified |
| 4 | `0x0043E440` | `SetSel` | unverified |
| 5 | `0x0043E480` | `OnMessage` | chain_unified |
| 6 | `0x0043E520` | `Destroy` | - |
| 7 | `0x0043E560` | `SetColumnHead` | unverified |
| 8 | `0x0043E5C0` | `LoadListItems` | unverified |
| 9 | `0x0043E7D0` | `SetMouseMoveSel` | unverified |
| 10 | `0x0043E8A0` | `Render_E8A0` | - |
| 11 | `0x0043EBA0` | `SetDefaultSel` | unverified |
| 12 | `0x0043EBB0` | `GetGridOffset` | unverified |
| 13 | `0x0043EBE0` | `Update` | chain_unified |
| 14 | `0x0043F080` | `ProcessSelection` | unverified |
| 15 | `0x0043F360` | `ClearAll` | unverified |
| 16 | `0x0043F410` | `AdjustScroll` | unverified |
| 17 | `0x0043F520` | `InitScrollbar` | unverified |
| 18 | `0x0043F560` | `CreateChild` | unverified +misattrib |
| 19 | `0x0043F590` | `GetLockedSel` | unverified |
| 20 | `0x0043F5B0` | `GetItem` | unverified |
| 21 | `0x0043F640` | `SetLockSel` | unverified |
| 22 | `0x0043F650` | `GetItemData` | unverified |
| 23 | `0x0043F670` | `SetItemOffset` | unverified |
| 24 | `0x0043F690` | `SetItemData` | unverified +misattrib |
| 25 | `0x0043F6A0` | `SetChildParam` | unverified +misattrib |
| 26 | `0x0043F6D0` | `SetFirstShow` | unverified +misattrib |
| 27 | `0x0043FE90` | `GetCurSel` | unverified |
| 28 | `0x00451850` | `UIListBox_Init` | unverified |
| 29 | `0x00451900` | `DestroyContent` | A |
| 30 | `0x00451AA0` | `OnMessage_1AA0` | - |
| 31 | `0x00451AD0` | `ReinitScrollbar` | unverified |
| 32 | `0x00451AF0` | `CalcVisibleRange` | unverified |
| 33 | `0x00451B40` | `ResizeToContent` | unverified |
| 34 | `0x00451C10` | `IsVisible` | unverified |
| 35 | `0x00451C70` | `~UIListBox` | A |
| 36 | `0x00452600` | `~UIListBox` | A |

未录（ABSENT，需在迁移清单中补条目）：`0x0043DFC0`（1208B ctor）、`0x0043E100`（deleting dtor）、`0x0043E120`（full dtor）。
