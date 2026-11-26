# R5 裁决：MagicUI 267,300B 无实例身份

- 卡片：#7 `tsk_01M8BZ439T7VVJ3WVJ3HMZ`
- 作者：玄策（执行）
- 日期：2026-11-26
- 取证对象：`original/PAL3.exe`（image_base 0x400000，.text rva 0x1000 raw_size 0x169000，.rdata rva 0x16a000 vs 0x15158，.data rva 0x180000）
- 工具：objdump（IDA MCP 未在本轮使用，关键结论均为指令级证据，见 §8 复现命令）

## §0 结论

**C. 合成类——`MagicUI` 在 PAL3.exe 中不存在可证实例，应删除该类条目。**
成因同时包含 **B（名字嫁接）**：注解里挂在该类名下的 14 个方法，实际被 4 个不同的 RoleStatePanel 槽对象和 2 个其它类的对象调用，不是同一个类的成员。

因此处置 = C 的动作（删类条目）+ B 的收尾（方法按 §3 迁改到真实类，实施另开卡）。

关键点：
1. `binary_size=267300(0x41424)` 不是分配证据，而是**末成员推导值**：末成员 `0x413d4 m_parRc tagRECT[5]`（80B）⇒ 0x413d4+0x50=0x41424。
2. 全库没有任何 267,300 的分配站点、没有 267,300 立即数、没有任何指向该类 14 个方法的函数指针表。
3. PDB（PAL3A，仅参考）虽然有 `??0MagicUI` 名字，但其地址在 PAL3.exe 里落在**另一个函数（MMX memset 体）的中段**，不可对齐，不能作证据（详见 §1.1）。

证据等级：①③ A 级（指令/字节直证）；② A 级（全段字节扫描）；④ A 级（调用点 ecx 直证）+ B 级（跨类归属推断）。无单证定谳。

## §1 四项要求逐项复核

### 1.1 ① 无 ctor / 无 operator new 站点

| 检查 | 结果 |
|---|---|
| 语料 `??0MagicUI` / `MagicUI::MagicUI` | 0 个文件（`grep -rl "??0MagicUI" data asm docs` 仅命中 `data/pdb/pdb_export.json` 一处，且是 PDB 符号表条目） |
| `data/registry/functions.json`（以 VA 为键） | MagicUI 出现 0 次 |
| 全 .text 立即数 `$0x41424`（267,300） | **0 处**（`grep -c '\$0x41424'` 全量反汇编） |
| 全 .text 立即数 `$0x415f4`（PDB 记的 267,620） | 0 处 |
| `call/jmp 0x551314`（PDB 的 `??0MagicUI@@QAE@XZ`） | 0 处 |
| 注解内以 MagicUI 为类型的成员（内嵌实例） | 0 处（全 `data/annotations` 扫描；`StateUI.json:0x277dc p_MagicUI MagicUI*` 是**指针**，且见下条） |
| `0x277dc(%` 代码命中（该指针的取用点） | **0 处** |

**PDB 反证的处理（重要）**：`data/pdb/pdb_export.json` 记 `??0MagicUI@@QAE@XZ` address=0x00551314 size=1378，`??1MagicUI@@UAE@XZ`=0x00551876，并有 `{"name":"MagicUI","kind":"union","size":267620}`。但把 0x551314 放到 PAL3.exe 里反汇编，落点是：

```
00551314: 3d 40 a7 60 00        cmp    $0x60a740,%eax     ← 不是函数入口
00551319: 0f 61 c6              punpcklwd %mm6,%mm0
0055131c: 0f 61 ce              punpcklwd %mm6,%mm1
...                              (MMX 批量填充循环：movq/pand/paddd/pfsub，末尾 jmp 0x5512ff)
```

即 PDB 的 MagicUI ctor 地址在 PAL3.exe 中落在 memset 类实现的中段，说明 **PDB（PAL3A）与 PAL3.exe 在该处不可对齐**；按项目规则 PDB 只作参考、不能单证定谳。PDB 尺寸 267,620 与注解 267,300 相差 320，也印证两者不是同一份数据。

### 1.2 ② .rdata 是否有 MagicUI 函数指针表

结论：**零表**。对 14 个方法地址逐个在 `.rdata`（rva 0x16a000 / raw 0x16a000 起，raw_size 0x16000）与 `.data`（rva 0x180000 / raw_size 0x8c000）做 4 字节小端 dword 扫描，命中数全为 0：

```
NextRole 0x55cce4 data_refs= []      InitComItem 0x551c66 data_refs= []
ProcessInput 0x494660 data_refs= []  RefreshAndLayout 0x48a010 data_refs= []
SelectBigMapTab3 0x494620 data_refs= []  SelectBigMapTab4 0x494640 data_refs= []
SelectTab3 0x484ed0 data_refs= []    SelectTab4 0x484ef0 data_refs= []
SelectSubTab3 0x48a350 data_refs= [] SelectSubTab4 0x48a370 data_refs= []
InitUILayout 0x48a390 data_refs= []  UpdateViewListItems 0x48b8f0 data_refs= []
SelectXJTMTab3 0x49e8a0 data_refs= [] SelectXJTMTab4 0x49e8c0 data_refs= []
```

⇒ 这 14 个函数没有任何 vtable / 消息表条目，不可能构成一个多态类的实例布局。

### 1.3 ③ .text 是否存在 267,300 立即数（分配/尺寸证据）

结论：**不存在**。三项扫描（`push $0x41424` / `mov $0x41424` / `and|sub $0x41424`）合计 0 处；`$0x415f4`（PDB 267,620）同样 0 处。作为正向对照，同类类尺寸在别处是可观测的——例如 ScreenEffectMgr 的分配点 `0x4B7121 push $0x58dc0` + `0x4B7126 call 0x55353b`（见 #2 报告），说明本工具链能抓到这种形态；MagicUI 抓不到不是方法问题。

`operator new` 全部调用点（`0x55353b`）的紧邻尺寸立即数里，也没有 267,300。

### 1.4 ④ 调用方 ecx 来源追溯

**RoleStatePanel 的 7 个槽对象**（`InitUI` 区 0x4a4560 起，形态统一为 `push $size` → `call 0x55353b`(operator new) → `call ctor` → `mov %eax,0x2afXX(%esi)`）：

| 注解成员 | 槽偏移 | new 尺寸 | ctor | 注解类型 |
|---|---|---|---|---|
| m_pTabPanel | 0x2afb8 | 0x29cec = **171,244** | 0x482ed0 | void* |
| m_pSubTabPanel | 0x2afbc | 0x56630 = **353,840** | 0x4867f0 | void* |
| m_pMainPropUI | 0x2afc0 | 0x35b50 = 219,984 | 0x4909f0 | MainPropUI* |
| m_pEquipUI | 0x2afc4 | 0x41014 = **266,260** | 0x498820 | EquipUI* |
| （0x2afc8） | 0x2afc8 | 0x62588 = 402,824 | 0x4a6f10 | — |
| （0x2afcc） | 0x2afcc | 0x27bd4 = 162,772 | 0x47e5c0 | LineupUI* |
| （0x2afd0） | 0x2afd0 | 0x46eb8 = 290,488 | 0x4b01d0 | — |

**没有任何槽对象尺寸等于 267,300**（最近的是 171,244，相差 96,056）。

`RoleStatePanel::SetSelectedData@0x4a4ac0` 内，「MagicUI 方法」的 ecx 全部取自这四个槽：

```
SelectTab3/4        ← mov 0x2afb8(%esi),%ecx   (调用点 0x4a4b0e / 0x4a4b57 / 0x4a4bbe / 0x4a4c07)
SelectSubTab3/4     ← mov 0x2afbc(%esi),%ecx   (0x4a4ae7 / 0x4a4b33 / 0x4a4b97 / 0x4a4be3)
SelectBigMapTab3/4  ← mov 0x2afc0(%esi),%ecx   (0x4a4af4 / 0x4a4b3f / 0x4a4ba4 / 0x4a4bef)
SelectXJTMTab3/4    ← mov 0x2afc4(%esi),%ecx   (0x4a4b01 / 0x4a4b4b / 0x4a4bb1 / 0x4a4bfb)
```

即同一「MagicUI」名字下的方法，被 **4 个不同的真实对象** 调用，而其中一个（0x2afc0）已被注解确认为 MainPropUI、另一个（0x2afc4）为 EquipUI。

**跨类调用点（A 级）**：

| 方法 | 调用点 | 调用发生时 ecx 来自 |
|---|---|---|
| RefreshAndLayout 0x48a010 | 0x48f3ee | `UITitle_XJTM::UpdateNPCAnims2`（0x48f360, size 56）体内 esi |
| ProcessInput 0x494660 | 0x4974fa | `MainPropUI::OnMessage`（0x4974a0）体内 |

**同族相邻地址被拆给两个类名（B 级）**：StateUI.json 自带 `SelectTab1@0x484e90` / `SelectTab2@0x484eb0`、`SelectSubTab1@0x48a310` / `SelectSubTab2@0x48a330`、`SelectXJTMTab1@0x49e860` / `SelectXJTMTab2@0x49e880`；MagicUI 拿到的 `0x484ed0/0x484ef0`、`0x48a350/0x48a370`、`0x49e8a0/0x49e8c0` 恰好是它们的紧邻后继（同一片包装函数区）。

**布局反证（B 级）**：`InitUILayout`（0x48a390，4026B）体内访问 `this->ml_TuList`（偏移 0x34f94）等 ≥0x34f94 的成员，远超槽 1 对象的 171,244(0x29cec)，也远超注解的 267,300 之外？——不，0x34f94 < 0x41424，所以它与 267,300 的布局并不冲突；但它与「调用它的 RefreshAndLayout 被 UITitle_XJTM 调用」合起来说明这批方法不是槽 1 那 171,244 对象的成员。

## §2 尺寸 267,300 的来源与成员质量

- `data/annotations/structs/MagicUI.json`：`binary_size=267300`，`base_size=72`，`bases=[{"UIFrameWnd",0}]`，`known_members=76`，`methods=14`。
- 末成员 `0x413d4 m_parRc tagRECT[5]`（5×16B=80B）⇒ 0x413d4+0x50 = **0x41424 = 267,300**，与 binary_size 精确相等 ⇒ **尺寸是从成员表尾推出来的，不是从分配点读出来的**。
- 成员证据多为 `unverified`，`source` 多为 `gen_headers_9.2` / `pdb_fill_incomplete`（即 PDB/旧导出填充），不是 PAL3.exe 指令证据。
- `bases=UIFrameWnd` 与「这批方法真实分布在 StateUI 家族包装函数 / MainPropUI / EquipUI」互相矛盾，进一步说明该类条目是拼接产物。

## §3 影响面与迁改清单（本卡不执行）

删除清单：
1. `data/annotations/structs/MagicUI.json` —— 整条删除（76 成员 + 14 方法）。
2. `data/annotations/structs/StateUI.json` 的 `0x277dc p_MagicUI` —— 删除（该偏移全 .text 0 取用点，无代码证据）。
3. `asm/pal3/decomp` 的 13 个 `MagicUI_*` 语料文件 —— 导出后按新归属重新生成（不手改）。

方法迁改清单（实施卡按此逐条走证据）：

| 方法 | 建议真实归属 | 依据 |
|---|---|---|
| SelectTab3 0x484ed0 / SelectTab4 0x484ef0 | StateUI（vtable 0x56ba30 家族） | 槽 0x2afb8 对象 ctor 0x482ed0 末尾 `movl $0x56ba30,(%esi)`；该 vtable 在 StateUI.json 登记，槽位 Render/Update/~StateUI/OnMessage 与 StateUI 方法同址；且与 StateUI 的 SelectTab1/2 紧邻 |
| SelectSubTab3 0x48a350 / SelectSubTab4 0x48a370 | 槽 0x2afbc 的真实类（353,840B，目前注解为 void*，类名未定） | 调用点取 `0x2afbc` |
| SelectBigMapTab3 0x494620 / SelectBigMapTab4 0x494640 | MainPropUI | 调用点取 `0x2afc0`（注解 m_pMainPropUI，尺寸 219,984 匹配） |
| SelectXJTMTab3 0x49e8a0 / SelectXJTMTab4 0x49e8c0 | EquipUI | 调用点取 `0x2afc4`（注解 m_pEquipUI，尺寸 266,260 匹配） |
| ProcessInput 0x494660 | MainPropUI | 调用点在 `MainPropUI::OnMessage` 0x4974fa |
| RefreshAndLayout 0x48a010 / InitUILayout 0x48a390 / UpdateViewListItems 0x48b8f0 | 待定（调用链在 UITitle_XJTM::UpdateNPCAnims2 与 0x48a1xx 内部，体访问 ≥0x34f94） | 需另开取证卡，禁止本卡猜测 |
| NextRole 0x55cce4 / InitComItem 0x551c66 | 待定（全 .text 无直接 call，无数据引用） | 同上 |

**门禁风险（2026-11-26 QA 退回后修正版）**

1. **该单元是活的交付单元，且两个文件分属两个不同的 census**（我先前把两个 census 混成了一个 229）：`s1`（头文件单元，总数 766，ok 743）里有 `s1.results[743] {"unit":"pal3/src/UI/MagicUI.h","status":"ok","warnings":45}`；`s2`（cpp 单元，总数 229，ok **157@19:14 / 160@21:01**）里有 `s2.results[212] {"unit":"pal3/src/UI/MagicUI.cpp","status":"ok","warnings":82}`。⇒ **229 里只有 1 个**（cpp），头文件那个不算在 S2 的 229 内。
2. **删类的两种情形都要写清**：
   - 情形 a（codegen 不再产出 cpp 单元）：S2 的 total 229→228、ok −1 ⇒ **156/228**（19:14 基准；按 21:01 现值则是 **159/228**），比率 68.56% → 68.42%，**略降 0.14pp**（157/228 不可能出现，那是只减分母不减分子的算法）；
   - 情形 b（类条目删了但文件仍被生成/残留，头里的 `char _gap_25D8[32620]` 等洞占位或 `#include` 链断）：该 cpp 单元可能转 fail，S2 会低于上述值。
   实施卡第一步必须实测是 a 还是 b，不能预设。
3. **人口影响必须列 13 条 partial 行，不是「无 L1 行」就完了**：`data/status/s4_baseline.json` 的 rows 里有 **13 条 `MagicUI::*`**（file=`pal3/src/UI/MagicUI.cpp`，status **全部 partial**，例如 `?RefreshAndLayout` 340B、`?InitUILayout` 4026B）。删类后这 13 条退出 matched 人口：**matched −13、符号分母 −13、L1 分子不变**（因为一条 L1 都没有）。⇒ 表述应为「无 L1 行、但有 13 条 partial 行」，ratchet 的 coverage carrier 会随之变化，须在实施卡的 loop 里当场读 `[metric]` 行记录。
4. 若迁改方法到 StateUI/MainPropUI/EquipUI，则这三个类的 methods 增加，需按常规跑 `check_annotations` + `loop`，且**归属改动必须有 decomp member access 证据**（项目铁律），所以实施卡要先逐条取「方法体内 this->成员 ⊂ 目标类成员」的证据。
5. census 洞面 −44,652B（16 个洞）——这是删类唯一确定会发生、且可先量化的可见变化。

## §4 未决与后续

1. MagicUI 的 14 个方法里，RefreshAndLayout / InitUILayout / UpdateViewListItems / NextRole / InitComItem 的归属本卡不给结论（证据不足），交实施卡单独取证。
2. 槽 0x2afbc（353,840B, ctor 0x4867f0）的真实类名未定；StateUI.json 的 binary_size=162,000 与槽 0x2afb8 实际 171,244 不符（差 9,244）——这是**另一个独立的尺寸问题**，不在本卡裁决范围，建议另立卡。
3. PDB 存在 `MagicUI` union 267,620 与 0x551–0x55D 区的方法名，与 PAL3.exe 不对齐（§1.1）；若后续确认 PAL3A 独有代码在 PAL3 被裁掉，则该 PDB 片段应记入「PDB 参考但不适用」清单。

## §5 QA checklist 对照

| 清单项 | 对应证据 |
|---|---|
| ① 无 ctor / .rdata 零函数指针 / .text 无 267,300 立即数 / 调用方 ecx 来源，逐项可复现 | §1.1–§1.4，§8 命令全可重跑 |
| ② 三选一结论明确 + 证据等级，无单证定谳 | §0 结论 C（成因含 B）；证据等级 A/A/A/A+B，四项互相独立 |
| ③ 若判删：删除清单、影响面、门禁风险，不执行删除 | §3（本卡未改任何 annotation，见 §6） |
| ④ 本轮未改 annotation，结论已登记证据台账带 ev id | §6 git 证明；ev_0007 / ev_0008（§7） |

## §6 本轮未改 annotation

本卡（#7）未改动任何 annotation 文件。工作树里现有 3 处改动 + 1 个未跟踪归档，均来自**并发成员**，不是本卡产物：

```
$ git status --porcelain data/annotations
 M data/annotations/structs/RoleStatePanel.json     (1 行：base_size，20:52:54 他人写入)
 M data/annotations/structs/SaleUI.json             (1020 行：青岚 R5-SaleUI 洞填，21:02:48)
 M data/annotations/structs/UIFrameContainer.json   (1 行：base_size，20:52:54 他人写入)
?? data/annotations/archive/gbBinkVideo_retired_20261125.json
```

本卡只新增：`docs/specs/2026-11-26-r5-magicui-identity-verdict.md` + `data/status/evidence_ledger.json` 的 ev_0007/ev_0008 两条。`pal3/src` 未重新生成，`data/status/struct_holes_20261125.json` 未重跑（#7 不需要重跑普查；该文件在 20:39 已由 #2 落盘）。

## §7 证据台账

- `ev_0007`（authority A）：MagicUI 267,300B 在 PAL3.exe 中无实例身份——无 ctor/无分配立即数/无操作符 new 站点/无函数指针表；尺寸 267,300 由末成员 0x413d4 推导（非分配证据）；PDB 的 `??0MagicUI@0x551314` 在 PAL3.exe 落在 memset 体中段不可对齐。裁决 = 合成类，应删条目。
- `ev_0008`（authority A）：注解 MagicUI 名下 14 个方法实为 4 个 RoleStatePanel 槽对象（171,244 / 353,840 / 219,984=MainPropUI / 266,260=EquipUI）与 UITitle_XJTM::UpdateNPCAnims2、MainPropUI::OnMessage 调用面上的方法，属名字嫁接；迁改清单见报告 §3。

## §8 复现命令

```bash
cd /home/peng/workspace/PAL3Decomp

# ① 反汇编全量（后续 grep 用）
objdump -d original/PAL3.exe > /tmp/pal3_full_disasm.txt
grep -c '\$0x41424' /tmp/pal3_full_disasm.txt     # 267,300 → 0
grep -c '\$0x415f4' /tmp/pal3_full_disasm.txt     # 267,620 → 0
grep -c 'call.*0x551314' /tmp/pal3_full_disasm.txt # PDB ctor 被调用 → 0

# PDB 的 ctor 地址在 PAL3.exe 里是什么
objdump -d --start-address=0x551314 --stop-address=0x5513f0 original/PAL3.exe

# ② .rdata/.data 函数指针扫描（4 字节小端）
python3 - <<'EOF'
import struct
d=open('original/PAL3.exe','rb').read(); pe=struct.unpack_from('<I',d,0x3c)[0]
nsec=struct.unpack_from('<H',d,pe+6)[0]; opt=struct.unpack_from('<H',d,pe+20)[0]
base=pe+24+opt; secs=[]
for i in range(nsec):
    o=base+i*40; name=d[o:o+8].rstrip(b'\0').decode()
    vs,va,rs,ra=struct.unpack_from('<IIII',d,o+8); secs.append((name,vs,ra,rs))
for n,va in {'SelectTab3':0x484ed0,'ProcessInput':0x494660}.items():
    for name,sv,ra,rs in secs:
        if name!='.text': print(n, hex(va), name, d[ra:ra+rs].find(struct.pack('<I',va)))
EOF

# ③ 槽对象分配链（尺寸 + ctor）
objdump -d --start-address=0x4a45e0 --stop-address=0x4a4700 original/PAL3.exe | grep -E "push +\\\$0x|call +0x55353b|call +0x4[0-9a-f]{5}|0x2af[bc]"

# ④ SetSelectedData 内的 ecx 来源
objdump -d --start-address=0x4a4ac0 --stop-address=0x4a4c60 original/PAL3.exe | grep -E "0x2af(b8|bc|c0|c4)|call"

# ⑤ 0x2afb8 对象 ctor 末尾的 vtable 写入
objdump -d --start-address=0x482ed0 --stop-address=0x483200 original/PAL3.exe | grep -E "movl +\\\$0x56ba30|movl +\\\$0x56ad20"
```
