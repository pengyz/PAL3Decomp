# CCCTData 430,256B 全洞根因清册

- 日期：2026-11-27
- 卡号：tsk_01M8CHJTMBJ7GK6MT2EZJV（#46）
- 性质：只读清册（未跑管线、未改 annotation、未改生成树）
- 数据时点：annotation/asm 为 2026-11-27 02:25 工作树；census `data/status/struct_holes_20261125.json` mtime 2026-11-27 00:40（并发卡在途，#31/#40 未落盘）
- 独立声明：本卡只读 asm 文本、annotation、PDB 导出、census；不引用 #23/#31 的在途改写产物

## §0 结论（先看这五条）

1. **CCCTData 没有独立实例。** 430,256 字节那一块的真实所有者是 **CCBCamControl**（`CCBStage.cpp` 里 new、挂在宿主 `CCBStage+0x10`、错误串 "new failed at create stage cam control"）。
2. **CCCTData 是 CCBCamControl 内嵌的 union 成员**（PDB：`CCBCamControl` union 430,256 含 `m_CCT: CCCTData @0`；`CCCTData` union 430,000，仅 3 个成员）。它不是类，是一个内存视图类型。
3. **「100% 洞」的机制 = 成员零建模 + 尺寸抄了外层实例值**：`CCCTData.json` 的 `known_members` 为空、`binary_size` 写成 430,256（外层实例大小），census 对「零成员类」按整类计洞 ⇒ 1 段 430,256B、100%。
4. 它与 #29 挂账的 **402,824B 类是两个不同对象**：402,824 在 `sub_4A4220` 里 new(0x62588)、ctor `0x4A6F10`、挂 `RoleStatePanel+0x2AFC8`；两者只被 annotation 的 7 条方法**错误混装**，内存上无邻接关系。
5. **三档结论：应删独立实例类档**——把 CCCTData 还原为 `CCBCamControl` 的结构内嵌 union（`m_CCT`，尺寸 430,000），并把 15 条 PDB API 方法迁到 CCBCamControl；7 条污染方法退回 402,824B 类的挂账卡。直接删会导致 `pal3/src` 三处 `#include "Combat/CCCTData.h"` 与 101 处 `CCCTData` 引用断链，故路线是「先并档、后删档」，不是一刀删。

## §1 复现命令与原样输出

```bash
# 1) 唯一分配点
$ grep -c "690B0h" original/PAL3.exe.asm
1

# 2) 分配上下文（asm 行号 379982–380003）
$ sed -n '379982,380003p' original/PAL3.exe.asm
                push    690B0h          ; Size
                call    ??2@YAPAXI@Z    ; operator new(uint)
                add     esp, 4
                mov     [esp+101Ch+var_1010], eax
                test    eax, eax
                mov     [esp+101Ch+var_4], 3
                jz      short loc_4FBC57
                mov     ecx, [esi+0Ch]
                push    ecx
                push    esi
                mov     ecx, eax
                call    sub_5052E0
                jmp     short loc_4FBC59
loc_4FBC57:
                xor     eax, eax
loc_4FBC59:
                test    eax, eax
                mov     [esp+101Ch+var_4], edi
                mov     [esi+10h], eax
```

```bash
# 3) 注解读数（CCCTData vs CCBCamControl）
$ python3 -c "..."
CCCTData       size=430256(0x690b0) members=0  methods=22 vtables=None bases=None
CCBCamControl  size=430256(0x690b0) members=28 methods=33 vtables=None bases=None

# 4) PDB 类型（两类都是 union）
CCBCamControl union 430256  26 members：m_CCT: CCCTData @0；m_pStage* @430000；m_pCam* @430004；m_pUtil* @430008；m_bRunning @430012；m_fp @430016；m_nCurList @430032；m_nCurTask @430036…
CCCTData      union 430000   3 members：m_Pool tagCCT[2000] @0；m_bPoolInUse uchar[2000] @408000；m_nCCTIndex int[50][100] @410000

# 5) census
CCCTData      size 430256  hole_bytes 430256  total_holes 1  members 0
CCBCamControl size 430256  hole_bytes 12      total_holes 1  members 28
```

## §2 实例前提逐项核（卡面 ①）

| 前提 | 结果 | 证据（asm 行号 / 文件） |
|---|---|---|
| alloc 立即数 0x690B0 | **命中 1 处（全库唯一）** | `original/PAL3.exe.asm:379982 push 690B0h`；`grep -c "690B0h"` = 1 |
| ctor | **命中 `sub_5052E0`**，即 CCBCamControl 的 ctor | 调用点 `asm:379993 call sub_5052E0`（实参 `push [esi+0Ch]`、`push esi`）；`CCBCamControl.json` methods 含 `0x005052e0 CCBCamControl` |
| 写 vtable | **零命中** | `sub_5052E0`/`sub_505930`/`sub_504DD0`/`sub_4FBA70` 四周体内 `off_5xxxx` 引用数均为 0；PDB 两类型均为 `union`；两注解 `vtables=None`、`bases=None` |
| 槽位存储 | **命中 1 处**：宿主 `CCBStage+0x10` | `asm:380003 mov [esi+10h], eax`，宿主 `sub_4FBA70`（`esi=this`，SEH 函数） |
| 全局持有 | 名称存在：`g_CCBCamControlData` | `grep -o '"[^"]*CCBCam[^"]*"' data/annotations/globals.json` ⇒ `g_CCBCamControlData` 1 条 |

补充：`sub_5052E0` 体（asm:394831–394900，69 行）——`mov esi,ecx`；`call sub_504DD0`（maxoff 0x28，疑基类/工具 ctor）；`lea ecx,[esi+69044h]` + `??0gbMatrix4`；清零 0x68FE0–0x69040、0x69094–0x690A8；`[68FB0]=arg0`、`[68FB4]=arg4`、`[68FB8]=*(*arg0)`、`[68FD4]=-1`；`retn 8`。**写界 max 0x690AC < 0x690B0**，与分配常量闭合。

dtor：`sub_505930`（asm:395403–395887，484 行）max this offset 0x690AC；调用点 `asm:380993`（`sub_4FBA70` 内，删除式）与 `sub_4FC3A0+2D1`（=CCBStage::EditorUpdate，重新初始化前销毁）。同样无 vtable 写。

宿主身份：`sub_4FBA70`（asm:379816–380159）由 `sub_5125E0+2E4`（CCBSystem ctor）调用，错误串 `"D:\Project\PAL3\Combat\CBStage.cpp"` / `"new failed at create stage cam control"`（asm:380006–380008）；同函数还分配 0x3CC/0x1A18/0x17E8/0x690B0/0x4618/0x614/0x6390。

## §3 「430,256B 100% 洞」的机制（卡面 ②）

三层原因，按贡献排序：

1. **成员零建模**：`CCCTData.json` 的 `known_members` 为空对象（0 员）。census v3 对「零成员类」的规则是把整个 `binary_size` 记为一个洞 ⇒ 1 段、430,256B。
2. **尺寸抄错**：`binary_size=430,256` 是外层实例（CCBCamControl 的分配常量）大小；CCCTData 自身作为 union 类型只有 **430,000（0x68FB0）**。注解里已有的 `binary_size_contested` 记录了这个二义（候选 430256/402824/425136）。
3. **不是「类名错配到别的对象」**：它不是把某类的名字贴错到另一块内存，而是「一个内嵌 union 类型被误当成独立类建档」；类名 CCCTData 本身在 PDB 里是真实类型名（union），错的是**建档层级**（应为 CCBCamControl 的成员，而非独立类）与**尺寸**。

因此把它当独立类去「补成员」会补错方向：它的 3 个字段已经在 `CCBCamControl.json` 里（`m_Pool`/`m_bPoolInUse`/`m_TaskListIndex` @0/0x639C0/0x64190），只是没有以 `m_CCT` 这个名字体现层级。

## §4 真实构造链与 402,824B 的关系（卡面 ③）

```
CCBSystem ctor (sub_5125E0+2E4)
  └─ sub_4FBA70  (CCBStage 代码区, this=CCBStage*, 错误串 CBStage.cpp)
       ├─ push 690B0h → operator new → call sub_5052E0 (CCBCamControl ctor)
       └─ mov [CCBStage+0x10], eax        ← 唯一持有槽位（注解 CCBStage 未建模 +0x10）

402,824B（另一对象，与本块无邻接）：
  sub_4A4220 → push 62588h → operator new → call 0x4A6F10 (ctor, 写表 off_56F29C)
  └─ mov [RoleStatePanel+0x2AFC8], eax
```

- 两者**不是同一对象、也不是相邻对象**：不同分配点、不同宿主、不同尺寸；共同点只有 annotation `CCCTData.methods` 里混进的 7 条（见 §6）。
- 402,824B 类仍缺身份（表 0x56F29C 槽归属），与 #29 同挂账；本卡不动它。

## §5 PDB 证据链

- `data/pdb/pdb_export.json`：
  - `{name: CCBCamControl, kind: union, size: 430256, data_members: [m_CCT: CCCTData @0, m_pStage @430000, m_pCam @430004, m_pUtil @430008, m_bRunning @430012, m_fp @430016, m_nCurList @430032, m_nCurTask @430036, …]}`（26 员）
  - `{name: CCCTData, kind: union, size: 430000, data_members: [m_Pool: tagCCT[2000] @0, m_bPoolInUse: unsigned char[2000] @408000, m_nCCTIndex: int[50][100] @410000]}`（3 员）
- 尺寸闭合：2000×204 = 408,000；+2000 = 410,000；+20,000 = 430,000 = 0x68FB0 = 旧热修链外的真实尾巴。
- annotation 侧：`CCBCamControl.json` 28 员的前 3 条与 union 字段一一对应（`m_TaskListIndex int[100][50]` 与 PDB `m_nCCTIndex int[50][100]` 尺寸相同、维度次序不同；属已知的注解写法差异，不影响布局）。

## §6 方法归属清理表（22 条 → 两个去处）

`CCCTData.methods`（22）与 `CCBCamControl.methods`（33）**交集为 0**，说明这 22 条是按「PDB CCCTData API 名」挂上去的，不是按二进制接收者。

A. 应迁 CCBCamControl（15 条，二进制接收者是 430,256B 实例：体内 `[this+…]` 最大到 0x68FD4）：
`0x5044C0 UpdateCamera` · `0x5058F0`（注解标 ctor，实为 setter：写 `[ecx+69094..690A8]` 6 个 dword，`retn 8`） · `0x505930 ~CCCTData`（实为 CCBCamControl 删除式 dtor，写界 0x690AC） · `0x506020 Create` · `0x5060D0 Destroy` · `0x5061A0 Init` · `0x506260 Save` · `0x5062D0 Load` · `0x5075E0 InsertTaskToList` · `0x507B20 SwapTask` · `0x508190 ClearList` · `0x5081A0 IsTaskValid` · `0x5081B0 GetTaskNumInList` · `0x5081C0 GetFreeSpaceInPool` · `0x41C900 CalcDist`

B. 应退回 402,824B 类挂账（7 条，与 430,256B 实例无构造/表证）：`0x4A6F10 CCCTData_6F10`（402,824 的 ctor，写表 off_56F29C）· `0x4A6730 InitImages` · `0x4A67B0 DestroyImage`（注解自带 `_misattrib_evidence: max_offset=420 > class_size=124`）· `0x44D780 InitEntries` · `0x4533F0 ProcessTask` · `0x4A8770 Create_8770` · `0x4E7D70 UpdateDebugDialog`

C. 说明：`0x5058F0` 的 `retn 8` + 仅 22 行也证明它不是 ctor——真正的 ctor 是 `0x5052E0`（69 行、有 `??0gbMatrix4` 与全字段清零）。注解把它标成 ctor 是**误名**，不是重载。

## §7 三档结论与影响面（卡面 ④）

**结论：应删独立实例类档（并档后删）**，不是「可开」、也不是单纯的「类名应改」。

- 为什么不是「可开」：没有独立实例可开。开实施卡去补 430,256 个字节的成员，会与 `CCBCamControl` 已有 28 员重复，且尺寸仍是抄来的外层值。
- 为什么不是单纯「类名应改」：类名在 PDB 里是真的（union），错的是**层级与尺寸**；改名不解决 100% 洞。
- 推荐路线（两阶段）：
  1. **并档**：`CCBCamControl` 增加 `m_CCT`（inline union，CCCTData 类型，@0，430,000B），现有 3 个字段改为 `m_CCT.m_Pool` 等视图；`CCCTData` 尺寸改 430,000、成员 3 条、方法清空；15 条 API 方法迁到 `CCBCamControl`；7 条污染方法登记到 402,824B 挂账卡。
  2. **删档**：确认生成树无 `CCCTData.h` 依赖后删除独立类（或保留 `typedef` 兼容 `pal3/src` 三处 include）。
- 影响面（实测）：
  - `pal3/src` 中 `CCCTData` 引用 **101 处**，分布 3 个 `.cpp`（`Scene/SceneObj.cpp`、`Scene/Scene.cpp`、`UI/EquipUI.cpp`）+ 生成头 `Combat/CCCTData.h`。
  - `CCBCamControl` 引用 **149 处**。
  - `EquipUI.cpp:1837` 把 `operator new(0x62588)`（402,824B）强转成 `CCCTData *` 并调 `CCCTData_6F10` ⇒ 这是 402,824B 类的**错名**，属另一张卡（与 #29 同挂账），本卡只登记不改。
  - globals 中无 `CCCTData` 类型全局（`grep -c "CCCTData" data/annotations/globals.json` = 0），删除不影响全局。
- 否证范围（已扫消费面）：全库 `690B0h` 仅 1 处分配；无第二 ctor；四个相关函数体内 `off_5xxxx` 引用 0 次；注解 `vtables=None`/PDB `union`；census 仅 CCBCamControl 与 CCCTData 两类同尺寸 430,256；无 `push 402,824`/`push 425,136` 指向本块。

## §8 未决（写清下一步取哪条证据）

1. **CCBStage+0x10 字段无注解**：需在 CCBStage.json 补 `m_pCamControl CCBCamControl*`（A 级：唯一存储点 asm:380003 + 错误串）。归属卡由实施方决定。
2. **`sub_4FBA70` 的正式名字**：代码区在 CCBStage 段、this=CCBStage*，但不在 CCBStage.methods 的 229 条里；需查 PDB/XREF 定名（候选 `CCBStage::CreateStageCam`）。
3. **402,824B 类身份**：表 `0x56F29C` 7 槽归属裁决（与 #29 同一挂账），本卡只把 7 条污染方法登记出去。
4. **`m_nCCTIndex` 维度次序**：注解 `int[100][50]` vs PDB `int[50][100]`，尺寸一致但索引语义不同；需取一处 `[a*100+b]` vs `[b*50+a]` 的寻址证据。
5. **census 口径**：本卡只解释，不放宽规则。若并档落地，census 应自然从 430,256 降到 0（CCCTData 类消失），总量降 430,256B——这是「账面下降」而非「字节修正」，实施卡报告里必须写清。

## §9 只读自证

- `git status --short` 本卡仅 `?? docs/audit/`（其余 M/?? 为并发卡：#31/#40/#44 等在途产物）。
- `git diff data/annotations/structs/CCCTData.json data/annotations/structs/CCBCamControl.json pal3/src` 为空。
- 未运行任何 `pipeline/cli.py` 子命令；未触发 idat/export/codegen/probe/match；只读 asm、annotation、pdb_export、census。
