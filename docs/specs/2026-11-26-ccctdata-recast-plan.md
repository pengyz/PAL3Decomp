# CCCTData.json 重铸施工图：402,824 类 Y 的成员/方法/落点与证据缺口（只读）

> 卡片：#18 / tsk_01M8C79N895XJ93AD2Q4PM（只读，QA 4 条）
> 写入域：仅本文件。本卡未跑 apply/export/codegen/probe/match/loop，未改 data/annotations、pal3/src、pipeline、基线。
> 结论先行：**发现身份反证（A 级）——PDB 的 `CCCTData` 不是 402,824 类 Y，而是 430,000B 的池 union**。因此本卡不按「把 CCCTData.json 改成 0x62588」出图，改为出两条路径 + 一个决策门，并单列反证（第 5 节 D-1）。

---

## 0 结论

1. **身份反证成立（A 级）**：`data/pdb/pdb_export.json` 的类表里 `CCCTData` 是 **union，size=430000**，成员 `m_Pool tagCCT[2000]@0`（2000×204=408,000）、`m_bPoolInUse unsigned char[2000]@408000`、`m_nCCTIndex int[50][100]@410000`（20,000B，止于 430,000）；其 17 条 PDB 函数（15 个 API + ctor/dtor）`this_type` 全是 `CCCTData *`，源文件 `Combat\CBStageCam.cpp`（C1、C8）。
2. 402,824（0x62588）那个类的构造链与池 API 无关：它由 `RoleStatePanel::Init`（0x4a4220）里 `new 0x62588 → ctor 0x4a6f10` 造出，ctor 第一句调 `UIListBox::UIListBox`（0x43dcd0），末尾把自有 vptr 写成 **0x56F29C**（C4、C5）——是一个 UIListBox 派生的**对话框数据类**，PDB 类表里没有 402,824 这个名字（C2/P1）。所以 twin 裁决定谳的「类 Y = CCCTData」**与 PDB 冲突**。
3. 本地注解 `CCCTData.json` 现在是 chimera：`binary_size=430256`（= `CCBCamControl` union 的尺寸）且 `known_members={}`、`methods=22 条`（C7）。它既不是池 union（430,000），也不是类 Y（402,824）。
4. `CCBCamControl` 在 PDB 里也是 union：**size 430256**，`m_CCT: CCCTData @0`，尾区 430000..430255 放 `m_pStage/m_pCam/m_pUtil/m_bRunning/m_fp/...`（C2）。即「430,256 类」= 池 union + 256B 相机尾，两层是**包含关系**，不是同一类的两种说法。
5. PDB 的 15 个池方法名与本地 0x505xxx–0x508xxx 段的候选体对得上（`InsertTaskToList` 0x5075E0 首句 `mov eax,[ecx+0x68fd0]` 就是 `m_nCCTIndex` 邻域，C8/D-4）；twin v4 用「disp 0x68FD0=425424 > 402824 ⇒ 池方法属类 X」的推理由此**不再成立**——池 union 在 union 的 offset 0，同一个 `this` 当然能摸到 0x68FD0。
6. 402,824 类目前**只有构造证据、没有名字**：按命名铁律不得编名，`RoleStatePanel+0x2AFC8` 继续留 `void*`+`m_unk_0x2afc8`，命名另立卡（D-2）。
7. 本卡给两条写入路径：**P-1（推荐，按 PDB 证据）**＝`CCCTData.json` 重铸为 430,000 池 union、`CCBCamControl.json` 保持 430,256 并把 `m_CCT` 落成 0 偏移成员；**P-2（委派原样）**＝把 `CCCTData.json` 改成 402,824 类 Y。P-2 与 C1/C2 直接冲突，列为「暂缓」，须先由 PMO/Human 裁决 R6⑥ 的身份句（第 5 节 D-1）。
8. 无论走哪条，**两处落点都不在本卡**：类 Y 的实例槽在 `RoleStatePanel.json` 的 `0x2afc8`（不是 `EquipUI.json`，见 C6），15 个池方法的地址重挂依赖 #6 的管线独占窗口。

9. **卡面口径 vs 实测口径（逐条对照，避免「按 checklist 逐字对不上」的误判）**：

| 卡面口径 | 实测口径 | 证据 | 处理 |
|---|---|---|---|
| store 点 `EquipUI+0x2AFC8` | **`RoleStatePanel+0x2AFC8`** | C6：`44f200 mov [esi+0x6e14],eax` → `44f206 call 0x4a4220`；`0x4a1e40 = RoleStatePanel::InitUI`；`[esi+0x6e14]` 是 RoleStatePanel 实例缓存 | 本卡按实测写；卡面 ① 的字面「EquipUI」不成立，需在卡面同步 |
| 15 个 PDB API 方法属类 Y（402,824） | 15 个 API 属**池 union CCCTData**（430,000）；类 Y 只有 ctor 等少数体 | C1（PDB union 430000 + 17 条 `this_type=CCCTData*`） | 见 D-1；P-2 若坚持，需要重写卡面 |
| `disp 0x68FD0=425424>402824 ⇒ 池方法属类 X` | 池 union 在 union 的 offset 0，`this` 相同 ⇒ 42 万级 disp 合法，池方法属 **CCCTData** | C9 `5075e0 mov eax,[ecx+0x68fd0]` + C1 | §1.4 正读 |
| 类 Y 身份 = CCCTData | 类 Y 是 UIListBox 派生、自有 vtable 0x56F29C 的未名类；PDB 无 402,824 | C5 + PDB classes[] 无该尺寸 | 不命名（D-2） |

---

## 1 身份与边界证据表

### 1.1 三个实体分列

| 实体 | 尺寸 | 身份判据 | 证据（文件:行 / VA） |
|---|---|---|---|
| **类 X = `CCBCamControl`（union）** | 430,256 = 0x690B0 | 池 union 430,000 + 256B 相机尾；PDB kind=union；本地 new 立即数 0x690B0 唯一 | PDB `classes[]` `CCBCamControl`（C2）；`data/status/_disasm_cache.txt:326056` `4fbc29: push 0x690b0` → `:326057 4fbc2e: call 0x55353b`（operator new）→ `:326068 4fbc50: call 0x5052e0`（`CCBCamControl` ctor，ida_structs 注 flags=ctor）→ `:326073 4fbc62: mov [esi+0x10],eax` |
| **池 union = `CCCTData`** | 430,000 = 0x6901C | PDB kind=union；成员 2000×204 + 2000B 位图 + 20000B 索引；15 方法 this_type=CCCTData* | PDB `classes[]` `CCCTData`（C1）；`data/pdb/pdb_export.json` functions 17 命中（`?InsertTaskToList@CCCTData@@QAE_NHHPAUtagCCT@@@Z` 等） |
| **类 Y（402,824，未名）** | 402,824 = 0x62588 | new 立即数 + ctor + store 三点闭合；UIListBox 派生；PDB 类表无此尺寸 | `data/status/probe_heap_alloc_census_20261126.json` 行（C3）；`_disasm_cache.txt:207274-207290`（C4）：`4a4651 push 0x62588` → `4a4660 call 0x55353b` → `4a4678 mov ecx,eax` → `4a467a call 0x4a6f10` → `4a468c mov [esi+0x2afc8],eax` |

### 1.2 类 Y 的 ctor/vptr/基类

| 项 | 值 | 证据 |
|---|---|---|
| 基类 | `UIListBox`（本地 size 72 = 0x48，vtable 0x56AD20，bases UIWnd@0） | `_disasm_cache.txt` `4a6f32: call 0x43dcd0`；`asm/pal3/ida_structs.json` `43dcd0 = UIListBox::UIListBox (ctor)`、`UIListBox.size=72` |
| 自有 vptr | **0x56F29C** | `_disasm_cache.txt` `4a75a7: c7 06 9c f2 56 00  mov DWORD PTR [esi],0x56f29c`（在所有基类/成员 ctor 之后写，标准派生类尾写） |
| 首组自有成员 | 0x5551/0x5552/0x5553/0x5554/0x5558/0x555C(=180.0f)/0x5B94(=300)/0x5B98/0x5B9C | 同上 `4a6fcb..4a7005`（C5 摘录） |
| 成员子对象 | `UIFrameContainer`（152B）在 0x5BA0(?) / 0x5C38 / 0x5CD0 / 0x5D68 / 0x5E00 / 0x5E0A4 / 0x5E13C / 0x5E228 / 0x5E2C0 / 0x5E358 / 0x5E3F0 / 0x5E488 / 0x60FC0 / 0x61058 / 0x610F0 / 0x61198（步距 0x98，`call 0x4422e0 = UIFrameContainer::ResetContainerState`） | `4a700b..4a7050`、`4a739b..4a74fa` |
| 其它子对象族 | 0x5E98/0x5FF0/…/0x61294/0x6194C（`call 0x43a770`）、0x5F360..0x60AF8（`call 0x43dfc0`，步距 0x4B8）、0x61AD0/0x62028（`call 0x4a12f0`） | `4a705b..4a759a` |
| 末尾写入 | 0x62028 之后无写点；0x62588 − 0x62028 = 0x560 留给最后一个子对象/尾部 | ctor 结束于 `4a7660`（ret） |

### 1.3 池 union 的成员闭合（PDB）

`m_Pool tagCCT[2000]@0` + `m_bPoolInUse unsigned char[2000]@408000` + `m_nCCTIndex int[50][100]@410000` → 408,000 + 2,000 + 20,000 = **430,000** = PDB size，A 级闭合（C1）。池条目 204B 与 `tagCCT.json binary_size=204` 已由 twin v4 闭合，本卡复核无异议。

### 1.4 判别证据的正读

| 观察 | 旧读法（twin v4） | 本卡读法（有 PDB 支撑） |
|---|---|---|
| `0x5075E0: mov eax,[ecx+0x68FD0]`（0x68FD0=425,424 > 402,824） | 池方法属类 X，不属类 Y | 池方法属 **CCCTData**；CCCTData 在 CCBCamControl union 的 offset 0，`this` 相同 ⇒ 42 万级 disp 合法 |
| 402,824 类的 ctor 只调 UIListBox ctor，无池调用 | 类 Y = CCCTData（任务编辑对话框数据类） | 类 Y 与池无关；PDB 里 CCCTData 是 union、方法全在 CBStageCam.cpp |

---

## 2 重铸方案

### 2.1 路径对照

| | **P-1（推荐）** | **P-2（委派原样，暂缓）** |
|---|---|---|
| `CCCTData.json` | binary_size **430000**；3 个成员（1.3）；15 个 PDB 方法 | binary_size **402824**；类 Y 成员（1.2 族）；UI 方法 |
| `CCBCamControl.json` | binary_size 430256；`m_CCT: CCCTData@0` + 25 尾员 | 不动（仍是 chimera 的另一半） |
| 与 PDB 一致性 | 一致（A 级） | 冲突（C1/C2） |
| 命名风险 | 无新名 | 把池类名挪给未名 UI 类 ⇒ 两个类都失去名字 |
| 执行代价 | 中（union 建模 + 15 方法重挂） | 高（先推翻 PDB 证据，或承认注解与 PDB 分叉） |
| 建议 | 先裁 D-1，再按 §4 两阶段执行 | 仅在 D-1 裁定「PDB 不适用本版」时启用 |

### 2.2 P-1 成员表（`CCCTData.json`）

| offset | 名字 | 类型 | 尺寸 | 证据等级 | 备注 |
|---|---|---|---|---|---|
| 0x0 | `m_Pool` | `tagCCT[2000]` | 408,000 | A（PDB+池乘法链） | 池 = `this + 204×handle`，句柄表 0x64190 见 twin v4 |
| 0x63A80 (408000) | `m_bPoolInUse` | `unsigned char[2000]` | 2,000 | A（PDB） | 与 `m_Pool` 尾部相接 |
| 0x64190 (410000) | `m_nCCTIndex` | `int[50][100]`（维度待裁 D-4） | 20,000 | A（PDB）/B（维度） | 现有注解写作 `int[100][50]@410000`，与 `idx=T+50L+102500` 的步距 50 一致；PDB 显示 `[50][100]`，需按消费者复核后定维度 |

### 2.3 P-1 成员表（`CCBCamControl.json`）

| offset | 名字 | 类型 | 证据 |
|---|---|---|---|
| 0x0 | `m_CCT` | `CCCTData`（430,000） | PDB `m_CCT: CCCTData @0`（C2） |
| 0x68FB0 (430000) | `m_pStage` | `CCBStage *` | PDB；PDB 签名 `??0CCBCamControl@@QAE@PAVCCBStage@@PAVCCBStageCam@@@Z` 对齐 |
| 0x68FB4 | `m_pCam` | `CCBStageCam *` | PDB |
| 0x68FB8 | `m_pUtil` | `CUtil *` | PDB |
| 0x68FBC | `m_bRunning` | `unsigned char` | PDB |
| 0x68FC0 | `m_fp` | `void * *` | PDB |
| 0x68FD0 | `m_nCurList` | `int` | PDB + `0x5075E0` 读点 |
| 0x68FD4 | `m_nCurTask` | `int` | PDB |
| 0x68FD8..0x690AE | 速度/震动/位姿族 | 见 PDB 25 员 | PDB（`m_fStartSpeed@0x68FD8` … `m_bCircleEndSelected@0x690AE`） |
| 0x690B0 | — | — | 类尾；430,256−430,255=1B 对齐填充 |

> 注：现有 `CCBCamControl` 注解的 28 员里，`m_Pool/m_bPoolInUse/m_TaskListIndex` 属池 union，应移入 `CCCTData.json`；余下尾员与 PDB 对齐后保留。这与「注解 chimera」是同一处病：两个类的内容被装在一张表里。

### 2.4 15 个 PDB 方法逐条映射

PDB 方法（`this_type=CCCTData*`，源文件 `Combat\CBStageCam.cpp`）与本地候选：

| PDB 方法（mangled 摘要） | PDB 字节 | 本地候选 | 判定 | 依据 |
|---|---|---|---|---|
| `??0CCCTData` | 54 | 0x5058F0 | 候选（体形待核） | 现注解即挂此址；体 16 条指令、写 0x690A8 邻域 |
| `??1CCCTData` | 19 | 0x505930 | **不成立** | 本地 0x505930 有 484 条指令（释放池/尾区），不可能是 19B 平凡 dtor；该址更像 `CCBCamControl` 的析构体 ⇒ 移出 `CCCTData` |
| `?Create` | 21 | 0x506020 | 候选 | 现注解 `Create(bool(float*))`，体 54 条、写 0x68FB0/0x69090 |
| `?Destroy` | 13 | 0x5060D0 | 候选 | 体 59 条、写 0x69090 |
| `?Init` | 13 | 0x5061A0 | 候选 | 体 71 条、读 0x68FD0/0x68FD4 |
| `?Load` | 363 | 0x5062D0 | 候选 | 体 33 条、读 0x68FB4 |
| `?Save` | 410 | 0x506260 | 候选（弱） | 体 53 条、最大 disp 0x280A（未触池尾）⇒ 需体长比对 |
| `?InsertTaskToList` | 474 | 0x5075E0 | 强候选 | 首句读 0x68FD0/0x68FD4，体 389 条 |
| `?SwapTask` | 314 | 0x507B20 | 强候选 | 体 464 条、写 0x69040 |
| `?ClearList` | 160 | 0x508190（**假**） | 待重挂 | 本地是 5B `jmp 0x5081A0`（ICF 折叠体） |
| `?IsTaskValid` | 142 | 0x5081A0（**假**） | 待重挂 | 只读写 `ds:0x56FD88`，无 this |
| `?GetTaskNumInList` | 330 | 0x5081B0（**假**） | 待重挂 | 5B `jmp 0x5081C0` |
| `?GetFreeSpaceInPool` | 223 | 0x5081C0（**假**） | 待重挂 | 是浮点加倍器（`fld ds:0x56FD88`） |
| `?AddTaskToList` | 412 | 未定位 | 缺口 | 全库未见对应体 |
| `?DelTaskInList` | 351 | 未定位 | 缺口 | PDB 有（`?DelTaskInList@CCCTData@@QAE_NHH@Z`），本地注解无对应条目 |
| `?GetCCT` | 276 | 未定位 | 缺口 | twin v4 记「语料 GetData/GetData_B720/GetData_B8D0=GetCCT 误名」 |
| `?Reset` | 80 | 未定位 | 缺口 | — |

**结论**：15 个 API 名 + ctor/dtor 都可保留（PDB 权威），但只有 4 个地址可强判（InsertTaskToList/SwapTask/Init/Load 级）、8 个候选待体长比对（含 ctor/Create/Destroy/Save）、1 个现挂地址不成立（dtor 0x505930 实为 1776B 大函数）、4 个现挂地址是 FLIRT/ICF 假体、4 个未定位（AddTaskToList/DelTaskInList/GetCCT/Reset）。写卡时按「名字保留、地址逐条重挂」执行，禁止整表照抄。

### 2.5 类 Y（402,824）逐字段表（P-2 骨架；证据全部来自 ctor 0x4a6F10）

> 说明：本表只列 **ctor 写点可证** 的区段；类型是「按写入宽度/被调 ctor 推断」，等级统一标 B（无消费者用点证据），名字一律 `m_unk_<offset>`（命名铁律，不编语义）。

| offset | ctor 写点 | 值 / 形态 | 类型推断 | 等级 |
|---|---|---|---|---|
| 0x0 | `4a75a7 mov [esi],0x56f29c` | vptr 0x56F29C | 自有 vtable | A（尾写） |
| 0x58 | `4a6f39 c7 46 58 20 03 00 00` | 800 | `int` | B |
| 0x5C | `4a6f4a c7 46 5c 58 02 00 00` | 600 | `int` | B |
| 0x60 / 0x64 | `4a6f51/4a6f54` | 0 / 0 | `int` | B |
| 0x16C | `4a6f57 call 0x4422e0`（`UIFrameContainer::ResetContainerState`，`ida_structs` 名） | 152B 子对象 → 0x16C..0x204 | `UIFrameContainer` | B（A 级旁证：调用目标名） |
| 0x224 | `4a6f5c..4a6fc3` 循环：计数器 `0x1C`=28、步长 `0x2F8`（760B），每记录 3 个内嵌 UI 子件 + `rep stos` 6 dword 清零 | 28×0x2F8=0x5320 → 0x224..0x5544 | `unsigned char[0x5320]`（不拆） | B |
| 0x5544 | `4a761b mov [esi+0x5544],ebx` | 0 | `int` | B |
| 0x5551 / 0x5552 / 0x5553 | `4a6fcb/4a6fd1/4a6fd8` | 0 / 1 / 1 | `unsigned char`×3 | B |
| 0x5554 / 0x5558 | `4a6fdf/4a6fe5` | 0 / 0 | `int` | B |
| 0x555C | `4a6feb c7 86 5c 55 00 00 00 00 34 43` | 180.0f（0x43340000） | `float` | B |
| 0x5B94 | `4a6ff5` | 300 | `int` | B |
| 0x5B98 / 0x5B9C | `4a6fff/4a7005` | 0 / 0 | `int` | B |
| 0x5BA0 / 0x5C38 / 0x5CD0 / 0x5D68 / 0x5E00 | `4a6fc5/4a700b`、`4a7010/…`，各 `call 0x4422e0` | 5 个连排，步长 0x98 | `UIFrameContainer[5]` | B |
| 0x5E98 / 0x5FF0 / … / 0x5E520 / 0x5EC40 / 0x61294 / 0x613EC / 0x61544 / 0x6169C / 0x617F4 / 0x6194C | `call 0x43a770`，步长 0x158 | 子件族 | 未定（不命名） | B |
| 0x5D378 / 0x5D4D0 / 0x5D718 | `call 0x43a770` | 步长 0x158 | 未定 | B |
| 0x5D8C4 / 0x5D8C8 / 0x5D8CC / 0x5D8D0..0x5D8D3 / 0x5D8D4 / 0x5D8D8 / 0x5D8DC / 0x5D8E0 / 0x5D8E4=1000 / 0x5D8E8=100 | `4a7335..4a7607` | 混合 int/byte | 逐字段待拆 | B |
| 0x5D944 / 0x5D998 | `call 0x43d830` | 子件 | 未定 | B |
| 0x5F360 / 0x5F818 / 0x5FCD0 / 0x60188 / 0x60640 / 0x60AF8 | `call 0x43dfc0`，步长 0x4B8 | 6 个连排 | 未定 | B |
| 0x61AA4 / 0x61AA8 | `4a757a` | 0 | `int` | B |
| 0x61AD0 / 0x62028 | `call 0x4a12f0` | 子件 | 未定 | B |
| 0x62588 | 类尾 | 0x62028+… 余 0x560 未写 | 尾部未知 | 缺口 |

类 Y 的 **dtor 未定**（D-6）：PDB 无 402,824 类名，vtable 0x56F29C 的槽表也未导出；`??1` 可能在 0x56F29C 的槽位里，需另跑一次 vtable 反查。

### 2.6 现有 22 条 methods 逐条处置（对账 PDB 17 条）

> 卡面 ② 要求「15 个 PDB API 方法逐条映射」，QA 指出还需把**现有 22 条**逐条交代去处。下表按 P-1 处置；行序=注解顺序。

| 现有条目 | 现名 / 签名 | 体形（条数 / max disp） | P-1 处置 | 依据 |
|---|---|---|---|---|
| 0x0041C900 | `CalcDist` void(float,float) | 54 / 0x30，无 this | **移出类表 → functions.json**（自由函数） | 无 this 访问；调用点全在池代码 0x506826/0x506D8E/0x5073F4/0x507A64/0x508003 |
| 0x005044C0 | `UpdateCamera` int(int) | 28 / 0x14，无 this | **移出 → functions.json**（归属待定） | 无 this；调用点 0x4E6BD7/0x4E6C60/0x5044FF/0x504D42/0x505579/0x506938 |
| 0x005058F0 | `CCCTData` ctor void(int*,int*) | 16 / 0x690A8 | **留 CCCTData**（ctor 候选，体形待核） | 写 0x690A8 属 union 尾 |
| 0x00505930 | `~CCCTData` void() | 484 条（0x505930..0x50601F），max disp 0x690AC | **移 CCBCamControl**（大析构体） | PDB `??1CCCTData` 仅 19B；本地 1776B 不符 |
| 0x00506020 | `Create` bool(float*) | 54 / 0x69090 | 留 CCCTData | 池域写点 |
| 0x005060D0 | `Destroy` bool() | 59 / 0x69090 | 留 CCCTData | 同上 |
| 0x005061A0 | `Init` void() | 71 / 0x68FD4 | 留（强） | 读 0x68FD0/0x68FD4 |
| 0x00506260 | `Save` char*(int) | 53 / 0x280A | 留（弱，体长比对） | PDB Save 410B，本地 53 条 |
| 0x005062D0 | `Load` bool(float*) | 33 / 0x68FB4 | 留（强） | 读 0x68FB4（`m_pCam`） |
| 0x005075E0 | `InsertTaskToList` void() | 389 / 0x6903C | 留（强） | 首句读 0x68FD0/4 |
| 0x00507B20 | `SwapTask` void() | 464 / 0x69040 | 留（强） | 写 0x69040 |
| 0x00508190 | `ClearList` bool() | `jmp 0x5081A0`（5 字节 thunk；C10 扫描越界至 0x5083AF 系 thunk 目标未作入口） | **删除条目**（假体） | ICF 折叠 thunk |
| 0x005081A0 | `IsTaskValid` bool() | 8（读 `ds:0x56FD88`） | **删除条目**（假体） | FLIRT 假名，无 this |
| 0x005081B0 | `GetTaskNumInList` void() | `jmp 0x5081C0`（5 字节 thunk，同上） | **删除条目**（假体） | 同上 |
| 0x005081C0 | `GetFreeSpaceInPool` void() | 195（`fld ds:0x56FD88`） | **删除条目**（假体） | 浮点加倍器，非池逻辑 |
| 0x004A6F10 | `CCCTData_6F10` void() | 415 / 0x62028 | **移出**（类 Y ctor） | `4a467a call 0x4a6f10` 紧随 `new 0x62588` |
| 0x0044D780 | `InitEntries` int(float) | 204 / 0x2188 | **移出，归属待定** | 0x2188 同时落在 430,000 与 402,824 内，单凭 disp 不能定 |
| 0x004533F0 | `ProcessTask` int(int) | 395 / 0xD0 | **移出，归属待定** | 无大 disp，且无 PDB 对应名 |
| 0x004A8770 | `Create_8770` int() | 1284 / 0x6194C | **移出**（类 Y 方法候选） | 与类 Y ctor 同段、造 0x5E3F0 起 UI 子件 |
| 0x004E7D70 | `UpdateDebugDialog` LRESULT() | 554 / 0x280A | **移出，归属待定** | 0x280A 不区分类；调用点集中 0x4E6xxx |
| 0x004A6730 | `InitImages` CCCTData* | 42 / 0x1A8 | **移出，归属待定** | 返回类型 `CCCTData*` 是旧假设，无证据 |
| 0x004A67B0 | `DestroyImage` void() | 93 / 0x1A4 | **移出，归属待定** | 同上 |

小计：留 CCCTData **8**、移 CCBCamControl **1**、删除假体 **4**、移出待定 **9** = 22。

### 2.7 类 Y（402,824）的方案

- **本卡不命名、不建类**。按铁律，无 PDB 名/无调用点语义证据时不得编名。
- 保留 `RoleStatePanel.json:0x2afc8` 的 `m_unk_0x2afc8`（void*），把现有 source 里的「402824B 类Y 身份未名」改成指向本文件与 PDB 反证（D-1），避免第三人再按「类 Y=CCCTData」重做。
- 若后续要落成员，需要的是**新类条目**（名字待定）+ 一次体形普查；这是 D-2 的独立卡，不在 #18。

---

## 3 写入点 → 文件映射

| 文件 | 改什么 | 属 P-1 / P-2 | 不能碰 |
|---|---|---|---|
| `data/annotations/structs/CCCTData.json` | `binary_size`；`known_members`（3 员）；`methods`（15 条，逐条地址）；`bases` 不设 | P-1：430000 / P-2：402824 | 不得保留 `_tail_000` 兜底成员；不得把 `CCBCamControl` 尾员塞进来 |
| `data/annotations/structs/CCBCamControl.json` | `binary_size` 430256 不变；`known_members` 去池三员、加 `m_CCT`；尾员按 PDB 对齐 | P-1 | 不改 `m_CCT` 以外成员的语义名（尾员名已 A 级） |
| `data/annotations/functions.json` | 当前无 CCCTData 地址条目（C7 实测 0 命中）⇒ 无需改动；若执行时新增自由函数条目再改 | 两路径 | 不为 15 方法新增函数表条目（类方法走 structs） |
| `data/annotations/vtables.json` | 本仓**无独立 vtables.json**；vtable 内嵌 `structs/<Cls>.json` 的 `vtables` 数组（`pipeline/ida/apply_annotations.py:508-511`） | 两路径 | 类 Y 的 0x56F29C 若要落，必须落新类条目，不能挂到 CCCTData |
| `data/annotations/structs/RoleStatePanel.json` | 仅 `0x2afc8` 的 source 文本（指向本文件/D-1），不升级类型 | 两路径 | 不把 `0x2afc8` 改成 `CCCTData*`（反证未裁前就是错的类型） |
| `data/annotations/globals.json` | 无 EquipUI 槽需要改（C6 证明槽主是 RoleStatePanel，不是 EquipUI） | 两路径 | 不改 `0x17AAF64`（BSS 块，twin v2 已证非对象） |
| `data/annotations/structs/tagCCT.json` | 不动（204B 已闭合） | — | 不动 |

---

## 4 分阶段验证与回滚

前置：`#6`（玄策，RoleStatePanel C2440）处于 `pending_acceptance`，基线读数以其验收后为准；本卡不与其并发跑管线。执行卡 blockedBy 见 §6。

### 阶段 A：池 union 落地（`CCCTData.json`）

1. 改 JSON（3 员 + 15 方法名，地址只填 §2.4「强候选」4 条，其余标 `unverified` 并留 note）。
2. `python tools/audit_type_layout.py --only CCCTData`（编译器裁判；size 430000 必须与 `sizeof` 探针一致）。
3. `python pipeline/cli.py check`（union 平凡性 + overlap 门；`m_Pool` 与 `m_bPoolInUse` 相接不重叠，应 PASS）。
4. `python tools/struct_holes.py`（或现有洞普查入口）→ 预期 `CCCTData.hole_bytes` 从 **430,256 归零**（现有 1 洞 `[0x0,0x690b0,430256]`，C8）。
5. 独占窗口 `python pipeline/cli.py loop --expect-s2 158/229 --expect-l1 189`；不满足预期即停（S2 < 158 或 L1 < 189 ⇒ 回滚）。

### 阶段 B：union 包装（`CCBCamControl.json`）

1. 去池三员、加 `m_CCT`（type=`CCCTData`，offset 0），尾员按 PDB 校名。
2. `python pipeline/cli.py check`：`m_CCT` 覆盖 0..430000 与尾区 430000..430256 相接，**不应报 overlap**；若报，按 CLAUDE.md「union 即 overlap 声明」用 `type={"union":[...]}` 或 `source` 显式声明，而不是删成员。
3. `python tools/audit_type_layout.py --only CCBCamControl`（430256）。
4. 洞普查 → 预期 `CCBCamControl` 12B 洞（0x68FC4..0x68FD0，C8）保留或按 `m_fp` 4 字节 + 4B 垫片消解；CCTData 侧无新洞。
5. `loop` 同上；另跑 `python pipeline/cli.py match` 读 `[metric]` 行（L1 不降；三限定随数字走）。

### 回滚

- 两文件均为已跟踪文件 ⇒ `git checkout -- data/annotations/structs/CCCTData.json data/annotations/structs/CCBCamControl.json`。
- **禁止** `git clean -fd` / `git stash -u`（工作区有他人未跟踪产物，已实证）。
- 回滚触发：`check` 失败且 30 分钟内修不掉 / `audit_type_layout` 尺寸不符 / S2 或 L1 低于阈值 / 洞数反增。
- 回滚后补一次 `apply → export`（禁止只回滚注解不重跑导出；`ida_structs.json` 会陈旧）。

---

## 5 证据缺口与风险

**D-1（阻断，身份反证 — 单列，不自行改判）**：PDB 证 `CCCTData` = 430,000 union（C1），twin 裁决证「402,824 类 Y = CCCTData」（v4 §架构模型）。两者不可同时成立；本卡判 PDB 侧更硬（类定义 + 15 方法 + 尺寸闭合三重），但 twin 是**已定谳**结论，按纪律交 PMO/Human 裁决：是否把 R6⑥ 的身份句改为「402,824 类是未名 UIListBox 派生类；CCCTData 是 430,000 池 union」。裁决前 P-2 不执行、P-1 不开工。

**D-2（命名缺口）**：402,824 类无 PDB 名、无调用点语义证据（只有 ctor 体 + RoleStatePanel 槽）；按铁律不编名。另立命名卡（需 PDB 交叉 + 调用点语义），本卡只把 `m_unk_0x2afc8` 的 note 指向本文件。

**D-3（方法地址缺口）**：15 个 API 中 4 个现挂 FLIRT/ICF 假体（ClearList/IsTaskValid/GetTaskNumInList/GetFreeSpaceInPool）、4 个未定位（AddTaskToList/DelTaskInList/GetCCT/Reset）、7 个候选待体长比对；另有 ctor 候选、dtor 现挂地址不成立（0x505930 是 1776B 大函数，对应 PDB 19B 平凡 dtor 不可能）。重挂需要逐条反汇编比对，不能整表照抄。

**D-4（维度分歧）**：`m_nCCTIndex` PDB 写 `int[50][100]`，本地表达式 `idx = T + 50L + 102500` 的步距是 50 ⇒ 声明应为 `int[100][50]`。执行前用 2 个消费者（`0x5075E0` 读、`0x507B20` 写）复核维度顺序，不要按 PDB 字面改。

**D-5（union 建模）**：C++ 层 `CCBCamControl` 是 union，注解 schema 没有「整类 union」；用「struct + `CCCTData m_CCT@0` + 尾员」等价表达（布局等价，语义上丢了 union 约束）。若 `check_annotations` 对 `m_CCT` 与尾员报 overlap，按 union 声明处理（CLAUDE.md「union 即 overlap 声明」）。

**D-6（类 Y 的 vtable/dtor）**：0x56F29C 已由 ctor 尾写实证，但当前无类条目承载它；若后续建类，需同时确认 `??1` 在哪个槽、是否伴生（`??_G`）。本卡不落。

**D-7（管线单通道）**：#6 未验收前基线会漂（s2 158/229、L1 189 是开工前读数）。执行卡必须 `blockedBy: [#6]` 且取独占窗口，否则读数不可归因。本报告的基线读数时点为 **2026-11-26 23:36:20**（`s4_baseline.json`：L1 189 / matched 1152 / symbols 1262 / partial 827）；该文件在工作树已被并发管线改写（sha 已非旧值 f3aa…），**执行前必须用当前文件重取**，不得沿用本句数字。

**D-8（工作树脏）**：`data/annotations/structs/RoleStatePanel.json` 当前 `M`（他人/#6 在办，mtime 见 git status），本卡未改它；执行前先用 `git diff --stat` 确认归属，避免把他人改动算进本卡。

**D-9（文档重复）**：`docs/specs/2026-11-26-r4-screen-effect-mgr-hole-diagnosis.md` 与本卡无主题重叠；但 R6 决策简报（#17）里第六项写「CCCTData 430,256 chimera vs 类 Y 402,824，推荐重铸」——该句需按 D-1 同步，否则执行者会按旧句动手（本卡不改 #17）。

---

## 6 下一张执行卡草案

```
title: CCCTData 池 union 落地（430,000）+ CCBCamControl union 包装（430,256）
owner: coder（建议玄策/墨痕，须避开 #6）
writeScopes:
  - data/annotations/structs/CCCTData.json
  - data/annotations/structs/CCBCamControl.json
  - data/annotations/structs/RoleStatePanel.json   # 仅 0x2afc8 的 source 文本
  - tests/test_ccctdata_pool_union.py              # 新增：size/member offset 断言
blockedBy: [tsk_01M8C57MHSA8FVE53WQY5G?]  # 实际填 #6（RoleStatePanel C2440）验收后的卡号
qaRequired: true
resultDefinition:
  1. CCCTData.json: binary_size=430000，3 员（m_Pool@0 tagCCT[2000] / m_bPoolInUse@408000 uint8[2000] / m_nCCTIndex@410000 int[100][50]），15 个 PDB 方法名保留、地址按 §2.4 逐条重挂（4 假体必须换成真体）
  2. CCBCamControl.json: binary_size=430256，m_CCT CCCTData@0 + 25 尾员按 PDB 校名；check_annotations PASS；audit_type_layout --only 两类的 sizeof 分别 430000/430256
  3. loop 读数：S2 ≥ 158/229、L1 ≥ 189（三限定随数字走）；洞普查 CCCTData.hole_bytes 430256→0，CCBCamControl 12B 不变
  4. 回滚演练一次（checkout 两文件 + apply→export），记录耗时
  5. 未做：类 Y 命名（D-2）、0x2afc8 类型升级（D-1 未裁前禁止）
验收命令：见本文件 §7 C1–C9
```

---

## 7 复现命令（只读；原样执行）

```bash
# C1 PDB: CCCTData = union 430000
python3 -c "import json;d=json.load(open('data/pdb/pdb_export.json'));c=[x for x in d['classes'] if x['name']=='CCCTData'][0];print(c['kind'],c['size'],[(m['name'],m['type'],m['offset']) for m in c['data_members']])"
# 实测：union 430000 [('m_Pool','tagCCT[2000]',0),('m_bPoolInUse','unsigned char[2000]',408000),('m_nCCTIndex','int[50][100]',410000)]

# C2 PDB: CCBCamControl = union 430256，m_CCT@0
python3 -c "import json;d=json.load(open('data/pdb/pdb_export.json'));c=[x for x in d['classes'] if x['name']=='CCBCamControl'][0];print(c['kind'],c['size'],c['data_members'][0],c['data_members'][-1])"
# 实测：union 430256 {'name':'m_CCT','type':'CCCTData','offset':0} {'name':'m_bCircleEndSelected','type':'unsigned char','offset':430254}

# C3 堆分配金表两行
python3 -c "import json;d=json.load(open('data/status/probe_heap_alloc_census_20261126.json'));print([a for a in d['allocs'] if a['size'] in (402824,430256)])"
# 实测：430256 site 0x4fbc2e；402824 site 0x4a4660 / store esi+0x2AFC8 / ctor ?CCCTData_6F10

# C4 new→ctor→store 三点（类 Y）
sed -n '207274,207290p' data/status/_disasm_cache.txt
# 实测：4a4651 push 0x62588 / 4a4660 call 0x55353b / 4a467a call 0x4a6f10 / 4a468c mov [esi+0x2afc8],eax

# C5 类 Y ctor：基类别 + 自有 vptr
grep -n -m1 '  4a6f32:' data/status/_disasm_cache.txt; grep -n -m1 '  4a75a7:' data/status/_disasm_cache.txt
# 实测：4a6f32 call 0x43dcd0（UIListBox ctor）；4a75a7 mov [esi],0x56f29c

# C6 槽主是 RoleStatePanel（不是 EquipUI）
sed -n '104997,104999p' data/status/_disasm_cache.txt
# 实测：44f200 mov [esi+0x6e14],eax / 44f206 call 0x4a4220；0x4a1e40 = RoleStatePanel::InitUI（ida_structs）

# C7 注解 chimera 现状
python3 -c "import json;d=json.load(open('data/annotations/structs/CCCTData.json'));print(d['binary_size'],len(d['known_members']),len(d['methods']),d.get('bases'))"
# 实测：430256 0 22 None

# C7b RoleStatePanel 0x2afc8 现状
python3 -c "import json;d=json.load(open('data/annotations/structs/RoleStatePanel.json'));print(d['known_members']['0x2afc8']['name'],d['known_members']['0x2afc8']['type'])"
# 实测：m_unk_0x2afc8 void *

# C8 洞账
python3 -c "import json;h=json.load(open('data/status/struct_holes_20261125.json'));print([(c['cls'],c['size'],c['hole_bytes'],c['holes'][:2]) for c in h['classes'] if c['cls'] in ('CCCTData','CCBCamControl')])"
# 实测：CCCTData 430256 430256 [['0x0','0x690b0',430256]]；CCBCamControl 430256 12 [['0x68fc4','0x68fd0',12]]

# C9 池方法读点（判别证据）
sed -n "$(grep -n -m1 '  5075e0:' data/status/_disasm_cache.txt | cut -d: -f1),+1p" data/status/_disasm_cache.txt
# 实测：5075e0 mov eax,[ecx+0x68fd0] / 5075e6 mov edx,[ecx+0x68fd4]

# C10 现有 22 条 methods 的体形（条数/max disp；用于 §2.6 的处置判据）
python3 - <<'PY2'
import json,re,bisect
lines=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().splitlines()
pat=re.compile(r'^\s*([0-9a-f]{5,8}):\s+(?:[0-9a-f]{2} )+\s*(.*)$')
ins=[(int(m.group(1),16),m.group(2).strip()) for l in lines if (m:=pat.match(l))]
pos={a:i for i,(a,t) in enumerate(ins)}
ent=sorted({int(m.group(1),16) for a,t in ins if (m:=re.match(r'call\s+(?:DWORD PTR )?0x([0-9a-f]+)',t))})
for x in sorted(json.load(open('data/annotations/structs/CCCTData.json'))['methods']):
    s0=int(x,16); i=pos[s0]; k=bisect.bisect_right(ent,s0)
    nxt=ent[k] if k<len(ent) and ent[k] in pos else s0+0x1000
    j=i
    while j<len(ins) and ins[j][0]<nxt: j+=1
    out=ins[i:j]; offs=[int(m.group(1),16) for _,t in out for m in re.finditer(r'\[[a-z]{2,3}(?:\+[a-z]{2,3}\*[1248])?([+-]0x[0-9a-f]+)\]',t)]
    print(f"{s0:#08x} {len(out):4d} {out[0][0]:#08x}..{out[-1][0]:#08x} maxdisp={max(offs):#07x}" if offs else f"{s0:#08x} {len(out):4d} no-disp")
PY2
# 实测（摘）：0x505930 484 条 / 0x4a6f10 415 条 / 0x4a8770 1284 条 / 0x5075e0 389 条；
# 0x508190 首条 jmp 0x5081a0（5B thunk）、0x5081b0 首条 jmp 0x5081c0、0x5081a0 8 条读 ds:0x56fd88、0x5081c0 195 条 fld ds:0x56fd88。

# C11 工作区 M 归属（并发管线 vs 本卡）
git status --porcelain data/annotations data/status pipeline | grep -c '^ M'
git status --porcelain data/status | grep '^ M' | awk '{print $2}' | xargs -r ls -l --time-style=+%H:%M:%S | awk '{print $6, $7}'
# 实测：29 个 M（annotations+status+pipeline）；四份基线均 23:36:20（pal3_registry/s4_baseline/s4_diff_detail/s4_l1_identity_cur），
# struct_holes 23:36:24；本卡目标文件未在 M 列表内（C7 读数未变）。
```

---

## 8 自检（QA 四条逐条）

1. **身份链证据齐全**：类 X（`push 0x690b0`+ctor 0x5052e0+store [esi+0x10]）、池 union（PDB C1）、类 Y（`push 0x62588`+ctor 0x4a6f10+store +0x2AFC8+自有 vptr 0x56F29C+基类 UIListBox）分列于 §1.1/§1.2，每条带 VA 或文件:行；disp 0x68FD0 判别另立 §1.4 正读。——通过。
2. **方案覆盖**：binary_size（430000/430256/402824 三值都写了归属）、bases（UIListBox@0，size 72）、15 个 API + ctor/dtor 逐条（§2.4 含「候选/不成立/假体重挂/未定位」四态）、成员布局（§2.2/§2.3 逐字段 + 证据等级）、`+0x2AFC8` 类型化（§2.7 明确「暂不升级」并给理由）、写入点文件清单（§3）、回滚与分阶段（§4）。——通过。
3. **已提交/工作树/待执行**：本卡**未改**任何 data/annotations 文件（§0 第 8 条、§3 表头均有声明）；`CCCTData.json` 仍是 430256/0 员（C7）；`RoleStatePanel.json` 的 `M` 状态属他人（D-8）。全文未出现「已重铸/已生效」；未取证成员不编名（类 Y 不命名）。反证单列 D-1。——通过。
4. **只读边界**：本卡只跑 `grep/sed/python` 读 JSON 与 `_disasm_cache.txt`；未跑 apply/export/codegen/probe/match/loop。`data/annotations`/`data/status`/`pipeline` 下共 **29 个 `M`**（C11），均为并发管线/他人产物：`data/annotations` 10 个（`functions.json`/`CEffGroupNode`/`PAL3VisNode`/`RenderTarget`/`ScreenEffect`/`ScreenEffectNode`/`UI3DModelNode`/`UIRoleDialog` 均 23:36:29，`ScreenEffectMgr` 23:40:32，`UITitle_JDHY` 23:50:11；`RoleStatePanel`/`UIFrameContainer` 20:52:54 属 #6）；四份基线 `s4_baseline`/`s4_diff_detail`/`s4_l1_identity_cur`/`pal3_registry` 均 **23:36:20**（loop 日志 22:20–23:14 同步），`struct_holes` 23:36:24，`pipeline/ida/apply_annotations.py` 22:59:07、`pipeline/gen/stages/stage5_fixup.py` 23:04:43 亦为他人改动。本卡的目标文件 `CCCTData.json` **不在 M 列表**（C7 读数 430256/0/22 与 mtime 09:51:40 均未变）；本卡新增仅本文件（`??`）。——通过（口径：本卡新增只有本文件；工作区其余 M 归并发方，非本卡）。
