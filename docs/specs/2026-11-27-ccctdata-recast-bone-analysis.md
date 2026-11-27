# CCCTData / CCBCamControl 重铸：二进制身份裁决与注解改动清单

- 卡片：#57（拆骨 / 二进制分析），承接 #18（`docs/specs/2026-11-26-ccctdata-recast-plan.md`）与 #89（SwordUI 重铸）
- 下游：#58（落地，writeScopes = `data/annotations/structs/CCCTData.json`、`CCBCamControl.json`、本文件）
- 性质：只读分析。本文件之外未修改任何文件，未跑管线。
- 证据等级：**A** = 指令/数据直读（反汇编、raw vtable、PDB 记录本身）；**B** = 反编译体与语料一致推出的结构事实；**C** = 由 A/B 组合推断，需后续卡确认。

> 读法约定：本文出现的 `[obj+0xNNN]` 一律指该指令里的**原始位移**，不换算成任何注解偏移。
> PDB 记录本身是 A 级（它是链接期产物，不是某个人的推断），但 PDB 的**类型描述**与二进制冲突时以二进制为准（见 §4 实证）。

---

## 0. 结论速览

| 问题 | 结论 | 证据等级 |
|---|---|---|
| CCCTData 是 430000 字节的池 union 吗 | **是**。2000×204 + 2000 + 20000 = 430000，三个成员首尾相接无空洞 | A（PDB 记录 + 指令位移） |
| CCBCamControl 是 430256 = CCCTData + 256 字节相机尾吗 | **是**。尾部 25 个成员从 0x68FB0 起，末成员 0x690AE，430254+2=430256 | A（PDB + 指令位移） |
| 402824（0x62588）是 CCCTData 吗（P-2） | **否，且已不可行**。该尺寸是 SwordUI，已有三证（ev_0029/0030/0031/0033）；PDB 里不存在 402824 的 CCCTData | A |
| 本 exe 里 CCCTData 有没有可归属的独立函数体 | **现有 21 条全部被排除**；PDB 的 17 个 CCCTData 函数在本 exe 未以独立符号体出现（池逻辑被内联进 CCBStageCam/CCBCamControl）；唯一形态吻合的候选 0x5052C0（32B 扫描 m_bPoolInUse[2000]）现挂 `CCBStageCam::IsCamValid`，归属冲突转独立卡（§6.1、§10 B-1） | A/B（逐条见 §5） |
| `m_nCCTIndex` 是 `int[50][100]` 还是 `int[100][50]` | **`int[100][50]`**（行跨度 50 int = 200 字节）。PDB 的 `int[50][100]` 与二进制矛盾 | A（§4 指令逐条） |
| P-1 / P-2 裁决 | **P-1 执行**；P-2 判定「不可行（与 A 级证据冲突）」，不需要 Human 再拍板——它不是方案分歧，是事实否证 | A |

一句话：#18 的方向正确，但 #18 的方法处置表把「相机函数」当成了 CCCTData 的方法，这正是 `binary_size=430256` 污染与 `CCCTData.cpp` 15 条编译错误的机制根因（§5、§6）。

---

## 1. 三方证据对账

### 1.1 PDB（A 级，`data/pdb/pdb_export.json`）

`CCCTData`：

```json
{"name":"CCCTData","kind":"union","size":430000,"bases":[],
 "data_members":[
   {"name":"m_Pool","type":"tagCCT[2000]","offset":0},
   {"name":"m_bPoolInUse","type":"unsigned char[2000]","offset":408000},
   {"name":"m_nCCTIndex","type":"int[50][100]","offset":410000}]}
```

17 个 `this_type=CCCTData*` 的函数，源文件 `D:\PAL3A\PAL3\Combat\CBStageCam.cpp`：
`CCCTData()`、`~CCCTData`、`Create`、`Destroy`、`Init`、`Reset`、`Save`、`Load`、
`GetCCT(int,int)`、`GetTaskNumInList(int)`、`IsTaskValid(int,int)`、`ClearList(int)`、
`AddTaskToList(int,tagCCT*)`、`InsertTaskToList(int,int,tagCCT*)`、`DelTaskInList(int,int)`、
`SwapTask(int,int,int)`、`GetFreeSpaceInPool(void)`。

`CCBCamControl`：`kind=union size=430256`，`m_CCT:CCCTData@0` + 25 个尾部成员（§3.2 表），
43 个不同函数名（44 条 `this_type=CCBCamControl*` 记录，`StartList` 重载重复 1 条；另有 1 条名字解析成 `destructor'` 的 PDB 噪声不计数），同源文件。

`tagCCT` = struct，size **204**，51 个 data_members。204×2000 = 408000，与 `m_bPoolInUse` 起点严丝合缝。

### 1.2 二进制布局（A 级，`data/status/_disasm_cache.txt`）

池三段的真实访问全部落在 0x504E43–0x5052C6（CCBStageCam 构造/初始化区），逐条可查：

```
504e43  lea edi,[edx+0x639c0]          ; m_bPoolInUse 基址（408000）
504e53  lea edi,[edx+0x64190]          ; m_nCCTIndex 基址（410000）
504ef3  push 0x639c0                   ; memset(m_bPoolInUse,0,408000)
5050a9  mov BYTE PTR [esi+edi*1+0x639c0],1
5052c6  mov bl,BYTE PTR [ecx+eax*1+0x639c0]   ; 逐个扫描 2000 个占用位
```

相机尾部访问（同样 A 级）：

```
5058f0  mov edx,[eax]      / mov [ecx+0x69094],edx ... [ecx+0x690a8]   ; 写 circle center/end
505930  mov ... [edi+0x690ac]  ; m_bShowCircleSet（430252）
         mov ... [edi+0x69090] ; m_pPointer（430224）
5061a5  mov edx,[esi+0x68fd0]  ; m_nCurList（430032）
5061ab  mov ebp,[esi+0x68fd4]  ; m_nCurTask（430036）
5061f9  mov BYTE PTR [esi+0x68fbc],0  ; m_bRunning（430012）
```

`0x68FB0` = 430000 恰为对象尾：凡是碰到 ≥0x68FB0 位移的函数体，**不可能**以 CCCTData（430000 字节）为 this——这是 §5 逐条排除的唯一判据，不需要额外假设。

### 1.3 当前注解与 IDA 导出（现况）

- `data/annotations/structs/CCCTData.json`：`binary_size=430256`、`known_members` 只有 1 条 interim `_tail_000: char[430256]`、`methods` 21 条（HEAD 是 22 条，工作区删掉了 `0x004a6f10`，见 §7）。
- `data/annotations/structs/CCBCamControl.json`：`binary_size=430256`、28 个成员 = 25 个尾部 + 3 个池成员（`m_Pool`/`m_bPoolInUse`/`m_TaskListIndex`）、33 条方法。**池成员挂错类**——#18 的 R1 整表重建（commit ed73fd85e）把它们从 CCCTData 搬到了这里。
- `asm/pal3/ida_structs.json`：CCCTData size 430256、CCBCamControl size 430256——IDA 侧尺寸来自注解回写，**不是独立证据**（循环引用）。

---

## 2. 身份裁决：P-1 vs P-2

### 2.1 P-1（执行）

`CCCTData` 恢复为 430000 的池 union（3 成员）；`CCBCamControl` 保持 430256，用 `m_CCT:CCCTData@0` 表达「相机控制对象内嵌一份池数据」这一原始结构（PDB 就是这么记的，`kind=union` 是链接器的形态，不是业务语义；注解 schema 没有整类 union，用 struct+嵌套成员是等价表达，仓内已有 1856 处同类嵌套成员先例）。

### 2.2 P-2（不可行）

P-2 主张「402824（0x62588）= CCCTData」。它被三组 A 级证据否证：

1. `RoleStatePanel::Init` 在 `0x4a4651` push 0x62588 → `operator new` → `0x4a467a` call ctor → `0x4a468c` 存 `[RoleStatePanel+0x2AFC8]`（ev_0029）；
2. 该 ctor（sub_4A6F10）第一句 `0x4a6f32` call 0x43DCD0（UIListBox ctor），末尾 `0x4a75a7` 写自有 vptr 0x56F29C，slot3 与 UIListBox 同值 0x43DE40（ev_0030/0033）；
3. PDB 里没有任何 size=402824 的类，而 SwordUI 的 PDB size 388952 与二进制的 402824 差异已由 #89 的成员普查解释（ev_0031）。

⇒ P-2 不是「另一种建模取舍」，而是把 SwordUI 的对象错认成 CCCTData。**不需要 Human 裁决**，只需要把 402824 明确留在 SwordUI（已由 #89 完成），`RoleStatePanel+0x2AFC8` 保持 `void* m_unk_0x2afc8` 不命名（诚实留白，符合命名铁律的「未知即 `m_unk_`」）。

---

## 3. 成员闭包

### 3.1 CCCTData（430000 = 0x68FB0）

| 偏移 | 成员 | 类型 | 尺寸 | 证据 |
|---|---|---|---|---|
| 0x00000 | m_Pool | tagCCT[2000] | 408000 | PDB A；tagCCT=204 A（51 成员对齐）；2000×204=408000 与下一成员起点相接 A |
| 0x639C0 | m_bPoolInUse | unsigned char[2000] | 2000 | PDB A；`lea [edx+0x639c0]`/`memset(...,0x639c0)`/`[+eax+0x639c0]` A |
| 0x64190 | m_nCCTIndex | int[100][50] | 20000 | PDB 偏移 A；维度以二进制为准，见 §4 |

合计 408000+2000+20000 = 430000 = 0x68FB0 ✓，无空洞、无重叠。

### 3.2 CCBCamControl（430256 = 0x690B0）

尾部 25 个成员（全部 A 级：PDB 记录 + 指令位移），起点 0x68FB0：

| 偏移 | 成员 | 类型 | 指令证据（示例） |
|---|---|---|---|
| 0x68FB0 | m_pStage | CCBStage * | — |
| 0x68FB4 | m_pCam | CCBStageCam * | 0x5062d0 `[this+430004]` |
| 0x68FB8 | m_pUtil | CUtil * | — |
| 0x68FBC | m_bRunning | unsigned char | 0x5061f9 写 0 |
| 0x68FC0 | m_fp | void ** | — |
| 0x68FD0 | m_nCurList | int | 0x5061a5 读 |
| 0x68FD4 | m_nCurTask | int | 0x5061ab 读 |
| 0x68FD8 | m_fStartSpeed | float | — |
| 0x68FDC | m_fNextSpeed | float | — |
| 0x68FE0 | m_vecSpeed | gbVec3D | — |
| 0x68FEC | m_vecNextSpeed | gbVec3D | — |
| 0x68FF8 | m_fDistance | float | — |
| 0x68FFC | m_fQuake | float | — |
| 0x69000 | m_fQuakeDec | float | 0x506020 读 |
| 0x69004 | m_fQuakeFre | float | 0x506020 读 |
| 0x69008 | m_StartPos | tagCam | — |
| 0x69020 | m_CurPos | tagCam | — |
| 0x69038 | m_vecCurPos | gbVec3D | — |
| 0x69044 | m_OBBox | gbOBBox | 0x506020 取址 |
| 0x69090 | m_pPointer | gbGeomNode * | 0x5060d0 写、0x505930 读 |
| 0x69094 | m_vecCircleCenter | gbVec3D | 0x5058f0 写 |
| 0x690A0 | m_vecCircleEnd | gbVec3D | 0x5058f0 写 |
| 0x690AC | m_bShowCircleSet | unsigned char | 0x505930 读 |
| 0x690AD | m_bCircleCenterSelected | unsigned char | — |
| 0x690AE | m_bCircleEndSelected | unsigned char | — |

末成员 430254+1 = 430255，结构体按 gbOBBox/tagCam 的 4 字节对齐补到 430256 ✓。

装配后：`CCBCamControl` = `{ CCCTData m_CCT @0; …256 字节尾部… }`，**不再单独持有** m_Pool / m_bPoolInUse / m_TaskListIndex（那三份是同一个存储的第二视图，保留即双份声明、布局自检必报 overlap）。

---

## 4. m_nCCTIndex 维度：二进制 vs PDB（A 级冲突，以二进制为准）

`0x5061A0` 实体（`_disasm_cache.txt` 原文，逐条）：

```
5061a5  mov edx,[esi+0x68fd0]        ; list 下标
5061ab  mov ebp,[esi+0x68fd4]        ; task 下标
5061b1  lea eax,[edx+edx*4+0x280a]   ; eax = 5*list + 0x280a(10250)
5061b8  lea eax,[eax+eax*4]          ; eax = 5*eax = 25*list + 51250
5061bb  lea ecx,[ebp+eax*2+0]        ; ecx = 2*eax + task = 50*list + 102500 + task
5061bf  mov ecx,[esi+ecx*4]          ; 取 int 元素
```

即元素下标 = `102500 + 50*list + task`。410000 字节 = 102500 个 int ⇒ 表基址；`list` 的倍数 50 = **行跨度 50 int（200 字节）**，`task` 在行内连续 ⇒ `int[100][50]`。

PDB 写 `int[50][100]`（行跨度 100 int），与上式直接矛盾。二进制是唯一的最终裁判（PDB 的数组维度来自编译期源码声明，但该声明在优化/类型合并中可能被 IDA/PDB 侧误记；此处指令是硬证据）。⇒ 注解保留 `int[100][50]`，并在成员 note 里写明「PDB 记 int[50][100]，与 0x5061A0 的 200 字节行跨度矛盾，以二进制为准」。

同一函数的另外两条结构事实（B/A）：
- 池条目跨度：`shl eax,4; add eax,ecx; lea eax,[eax+eax*2]; lea edi,[esi+eax*4]` ⇒ idx×(16+1)×3×4 = idx×204 = sizeof(tagCCT) ✓
- `entry[+0x16]` 字节是「已完成」标志；`entry[+0x64]` 是「特效需清理」标志（随后 call 0x4C6410 两次）。

---

## 5. 方法处置：CCCTData 现有 21 条逐条裁决

判据：反编译体中 `this` 的原始位移（`_tail_000[N]` 字面量）与函数体形态；≥430000 一律排除（§1.2）。

| VA | 现注解名 | 体证据（位移/形态） | 裁决 |
|---|---|---|---|
| 0x005058F0 | CCCTData（ctor） | 只写 430228/430232/430236（`m_vecCircleCenter`）与 430240/430244/430248（`m_vecCircleEnd`）**两个 vec3**，随后 `ret $8`；不触 430252+ | **CCBCamControl::SetCircle(gbVec3D*,gbVec3D*)**（PDB 同名同形，ret 8） |
| 0x00505930 | ~CCCTData（1746B） | 读 430252（m_bShowCircleSet）、430224（m_pPointer）、取址 430228 | **CCBCamControl::UpdateCircleSet** 一类；不是 19 字节的 `??1CCCTData`（PDB 记 ~CCCTData 很短） |
| 0x00506020 | Create | 读 430224/430000/430004，构造 m_OBBox，射线拾取 | **CCBCamControl::IsPointerUnderMouse** |
| 0x005060D0 | Destroy | `operator new(0x118)` → 存 430224 → LoadFromFile("ui\\combat\\pointe…") | **CCBCamControl::LoadPointer** |
| 0x005061A0 | Init | 读 430032/430036，走 200 字节行表 | 相机+池混合 → **CCBCamControl** 一类（DoList/Init） |
| 0x00506260 | Save | 102B，仅触 410000 行表（`&_tail_000[200*nVal+410000]`），把 entry[21]/[22] 置 0 并 call 0x505290 | 池专有（A），但 PDB `bool ClearList(int)` 形态不符 ⇒ **移出，不硬安名** |
| 0x005062D0 | Load | 读 430004（m_pCam）→ 相机字段 492/496/500/452/456/464 | **CCBCamControl** |
| 0x005075E0 | InsertTaskToList | 1342B，触 430144（m_OBBox 区） | **CCBCamControl** |
| 0x00507B20 | SwapTask | 1588B，触 430144 | **CCBCamControl** |
| 0x00508190 | ClearList | 5B `jmp 0x5081a0` | ICF 桩，**删** |
| 0x005081A0 | IsTaskValid | 11B 全局拷贝 `0x56fd88→0x17ab51c` | ICF 桩，**删** |
| 0x005081B0 | GetTaskNumInList | 5B `jmp 0x5081c0` | ICF 桩，**删** |
| 0x005081C0 | GetFreeSpaceInPool | 15B float 自乘写 `0x17ab518` | ICF 桩，**删** |
| 0x0041C900 | CalcDist | 149B，无 this 位移 | 非池，**移出** |
| 0x005044C0 | UpdateCamera | 35B，无 this 位移 | 非池，**移出** |
| 0x0044D780 | InitEntries | 688B，最大 this 位移 8584 | 他类，**移出** |
| 0x004533F0 | ProcessTask | 1193B，位移 28 | 他类，**移出** |
| 0x004A8770 | Create_8770 | 4339B，位移 399692 | 他类，**移出** |
| 0x004E7D70 | UpdateDebugDialog | 1746B，位移 8056 | 他类，**移出** |
| 0x004A6730 | InitImages | 120B，位移 424 | 他类，**移出** |
| 0x004A67B0 | DestroyImage | 283B，位移 420 | 他类，**移出** |

结论：**一条都不能留**。8 条是相机尾（A 级排除），4 条是 ICF 桩（A 级），8 条属他类（B 级：位移语义明显不是池；0x41C900/0x5044C0/0x44D780/0x4533F0/0x4A8770/0x4E7D70/0x4A6730/0x4A67B0），1 条（0x506260）虽只碰 410000 行表，但其体调用 0x505290 且返回形态与 PDB `bool ClearList(int)` 不符，命名无据 ⇒ 一并移出，不硬安一个名字。

> 为什么这不是「删证据」：这些 VA 的函数体在二进制里都真实存在，只是**不属于 CCCTData**。把它们留在 CCCTData 会产生两个后果：① `CCCTData.cpp` 用 `char*/__int16*` 的错误签名编译，15 条 C2664（§6.2 实测）；② 即使编译通过，符号名是 `CCCTData::SetCircle`，与原二进制 mangled name 不符，永远不可能 L1。移出是**止损**，不是抹除。

---

## 6. PDB 的 17 个 CCCTData 函数在哪 / 0x5052C0 冲突登记

### 6.1 观察

- 池三段的读写指令只出现在 0x504E43–0x5052C6 这一段（CCBStageCam 构造/初始化内联区），没有一处独立函数体以 CCCTData 为 this 做完整池 API。
- `0x5052C0`（32B）的体是 `while (m_bPoolInUse[i]) i++; return i>=2000 ? -1 : i`——形态与 PDB `CCCTData::GetFreeSpaceInPool(void) int` 完全吻合（A）。
- 但该 VA 当前被 `CCBStageCam.json` 注解为 `CCBStageCam::IsCamValid(void)`，反编译体甚至写成 `this[65].pControl[11]`（因为注解给的类没有 0x639C0 成员，Hex-Rays 只能按 CCBStageCam 尺寸硬折）。而 PDB 的 `CCBStageCam::IsCamValid` 签名是 `IsCamValid(tagCam*)`——**带参**，与这个无参扫描函数不是同一个东西。

⇒ 0x5052C0 高度可能是 `CCCTData::GetFreeSpaceInPool` 被错挂到 CCBStageCam。这属于 **CCBStageCam/CCBCamControl 方法归属**问题，跨出 #58 的 writeScopes（#58 只有两个 JSON），**不在本卡处置**，登记为后续卡（§10 B-1）。

### 6.2 与编译错误的因果链（实测）

`data/status/probe_census.json`（**generated_at=2026-11-27T11:59:37**，mtime 12:01:16）：
`CCCTData.cpp` fail，15 条错误：12×C2664（签名把参数当 `__int16*`）、C2227+C2653（`CCCTData` 不是类，L1393）、C2039（`InputSystem::ProcessKeyboard`）。
`CCBCamControl.cpp` fail，1 条 C2440（gbRenderEffect*→unsigned long）。
`CCBStageCam.cpp` fail，5 条，其中 L569 正是 `CCCTData : is not a class`。

即：CCCTData 被清成空 chimera（`known_members` 只剩 `_tail_000`）后，别的类里 `CCCTData` 前向声明/成员类型全部失效；而 CCCTData.cpp 自己又背着 21 条错名函数。P-1 重铸同时治好这两头。

> **该 census 的来源必须一并读**：它由 2026-11-27 11:53 启动的 loop 链产出，同一链 `codegen all` rc=1（`pipeline/gen/stages/emit_headers.py:3404` `RuntimeError: generate_header(PalScriptWaitObj): 槽0x0044ab40 名呈dtor形态('~PalScriptWaitObj')但flags缺dtor`），随后 `probe` rc=1 且打印 `[Baseline] NOT refreshing: regressions detected`（日志 `/tmp/loop84b.log:21-27` 与末尾 12 行）。⇒ 158/230/606 是**失败链上的观测值**，不是已认证基线；门槛比较必须在同一链内用 `match` 输出，或以本卡落地后的干净链为准。

---

## 7. 工作区 `CCCTData.json` 未提交改动分析（#57 要求 4）

`git diff` 实测：9 insertions / 15 deletions，内容三处：

1. `known_members["0x0"] = {name:_tail_000, type:char[430256], interim:true, note:"IDA标准未名尾数组 interim 2026-11-27（#89）…语料 this->_tail_000[N] 按字节索引访问 475 处"}`
2. 删除 `methods["0x004a6f10"]`（CCCTData_6F10，即 SwordUI 的 ctor 被错挂进来）
3. 删除 `binary_size_contested.candidates["402824"]`，并在文件 note 追加「2026-11-27 #89: 删除 0x4A6F10 与 402824 跨类占位（真值归 SwordUI，见 ev_0029/ev_0032）」

**provenance 明确**：来自 #89（SwordUI 402824 重铸）落地时的清理动作，与 ev_0029/ev_0032/ev_0033 一致，不是来历不明的改动。
**处置：保留**。三条都与 P-1 同向（402824 归 SwordUI、class-Y ctor 移出、空类 interim 尾数组保持可编译）。#58 落地时把 interim `_tail_000` 整体替换为 §3.1 的三个真成员即可（`interim` 字段随之消失），不必回滚。

---

## 8. 注解 diff 清单（#58 照此执行）

### 8.1 `data/annotations/structs/CCCTData.json`

| 项 | 现状 | 目标 | 依据 |
|---|---|---|---|
| binary_size | 430256 | **430000** | §3.1 A |
| known_members["0x0"] | `_tail_000: char[430256]`（interim） | **`m_Pool: tagCCT[2000]`，offset 0** | PDB A + 布局闭包 |
| known_members 新增 | — | `0x639c0: m_bPoolInUse: unsigned char[2000]`（offset 408000） | PDB A + `lea [edx+0x639c0]` |
| known_members 新增 | — | `0x64190: m_nCCTIndex: int[100][50]`（offset 410000，note 记 PDB 维度冲突，§4） | 0x5061A0 指令 A |
| methods | 21 条（§5） | **全部删除**（相机 8 条、ICF 桩 4 条、他类 8 条、池专有 1 条 = 21；遗留 0x4a6f10 已删） | §5 逐条 |
| binary_size_contested | 存在（402824 已删） | **删除整个字段**（身份已裁决，不再「争议」） | §2 |
| 新增 `_identity_note` | — | 一句话：本 exe CCCTData 无独立函数体；402824=SwordUI(ev_0029)；池成员视图见 CCBCamControl.m_CCT | §2/§6 |
| source | 保留 | 保留（来源链） | — |

不要给 tagCCT 数组元素起「池条目」之外的伪语义；tagCCT 本身是 PDB 类名，直接用。

### 8.2 `data/annotations/structs/CCBCamControl.json`

| 项 | 现状 | 目标 | 依据 |
|---|---|---|---|
| binary_size | 430256 | 保持 430256 | §3.2 |
| known_members["0x0"] | `m_Pool tagCCT[2000]` | **改成 `m_CCT: CCCTData`，offset 0**（嵌套成员，仓内 1856 处先例） | PDB `m_CCT:CCCTData@0` A |
| known_members["0x639c0"] | `m_bPoolInUse uchar[2000]` | **删除**（经 m_CCT 可达） | 同一存储双视图必须唯一声明 |
| known_members["0x64190"] | `m_TaskListIndex int[100][50]` | **删除**（真名 m_nCCTIndex，属 CCCTData） | §4 A |
| tail 25 成员 | 已有，偏移/类型与 PDB 一致 | 保持（可把 evidence_level 从 unverified 升为 binary，因 §3.2 每条都有指令位移） | §3.2 |
| methods 33 条 | 见下 | **保持现状不动**（不在本卡重排）；本轮不新增（0x5052C0 归属冲突待 §10 B-1） | — |
| bases | 无 | **不加**（union 无继承） | PDB bases=[] |

methods 33 条的处理边界（本卡只做「不引入新错误」的最小集）：
- 0x5081D0 / 0x5081E0（`jmp` 两跳的 dtor thunk 对）——保留现状，不动（`declaration_only` 等细化留给 dtor 专项）。
- 其余 31 条不动——与上一条合计 33 条全部保持现状（它们当前已让 `CCBCamControl.cpp` 仅剩 1 条 C2440，重铸后仍应保持 ≤1）。
- **不**把 §5 移出的 8 条相机函数塞回 CCBCamControl：它们的正确 PDB 名（SetCircle/LoadPointer/IsPointerUnderMouse/UpdateCircleSet/DoList/…）与 VA 的对应关系虽有体证据支持 4 条，但一次性新增 8 个方法会引入新的编译面（每个都要对 sig_model），超出 #58 的「重铸」范围，转 §10 B-2。

---

## 9. 落地步骤与门禁（#58 执行）

### 9.1 前置

```bash
python pipeline/cli.py status          # 记录进入时基线
git status --porcelain                 # 确认只有两个 JSON 会被改 + 本文件
```

进入时实测基线（本文成文时，**不是** #18 的陈旧数字）：

| 指标 | 当前实测 | 来源 |
|---|---|---|
| S2 | **158 / 230** | `data/status/probe_census.json`（generated_at **2026-11-27T11:59:37**） |
| 编译错误总数 | **606** | 同上逐单元求和 |
| L1 | **198** | `data/status/s4_diff_detail.json` |
| partial | 852（150 单元） | 同上 |

> ⚠️ ① 本表数字来自 2026-11-27 11:53 启动的 loop 链，该链 `codegen` 在 `PalScriptWaitObj` 头生成处抛 `RuntimeError`、`probe` 报 `[Baseline] NOT refreshing: regressions detected`（`/tmp/loop84b.log:21-27`）——是**失败链观测值**，须以落地后干净链读数复核。
> ⚠️ ② #58 卡片里写的 `S2≥159 / errors≤606 / L1≥189` 中，**L1≥189 是陈旧值**。工作区 `data/status/s4_baseline.json` 在 12:16:09 前后出现过一次 `match_L1=198 / matched=1194 / symbols=1309` 的写入，但**该写者与来源未坐实**（`/tmp/loop84b.log` 结束于 12:01，那轮 codegen 也 rc=1；lead 记为 03:xx 旧总体 1194/1309 的残留），故 **198 不作为门禁依据**。门禁按 lead 2026-11-27 14:06 裁定：`L1≥192 且 population 与上一轮一致`（实测见 §11.5）。
> ⚠️ ③ baseline 人口已变（symbols 1309），**禁止**用旧基线文件做前后差；一切比较用同一次 `match` 运行的 `[metric]` 行。

### 9.2 步骤

1. 改两个 JSON（§8），用 `python tools/check_annotations.py --only CCCTData CCBCamControl`（若有更细入口以 `pipeline/cli.py check` 为准）先过一致性。
2. 独占 apply+export：`python tools/run_apply_export_idalib.py`（同一时刻不得有别的会话持有 IDB）。
3. **强制**确认 `asm/pal3/ida_structs.json` mtime 晚于两个 JSON 的 mtime（否则读数无效——历史教训：缺 export 导致 S2 误判）。
4. `python pipeline/cli.py codegen all` → `python tools/compile_regression.py`。
5. `python pipeline/cli.py probe all` → `python tools/error_classifier.py --summary`。
6. `python pipeline/cli.py match`，**当场读** `[metric]` 行（三限定：截断 / 长度 / 重定位 don't-care），不得事后查基线文件。
7. `python tools/audit_type_layout.py --only CCCTData CCBCamControl`（编译器裁判：sizeof 必须 430000 / 430256）。
8. 把实测数字追加到本文件 §11，然后才提交 #58 验收。

### 9.3 门禁（全满足才可交）

- `audit_type_layout` 对两类的 sizeof 断言通过（430000 / 430256），无 overlap 告警；
- S2 ≥ 158（实测 158/**229**：`CCCTData.cpp` 因 method-less 不再生成、其 15 条错误随单元一起消失，ok 不变；若 `CCBStageCam.cpp` 转 ok 则为 159/229。原「期望 +1~+2 ⇒ 160」的预期**作废**——见 §11.2）；
- 总错误 ≤ 606（不得新增）；
- L1 ≥ 192（lead 2026-11-27 改判；population 须与上一轮一致。原卡面的 198 无对应基线文件、全仓查不到——见 §9.1 ⚠️②。若 `CCBStageCam.cpp` 转 ok，可能出现新比对单元，L1 只应升不应降）。**引用 L1 必带三限定**（`pipeline/compare_pal3.py` + `tools/gbengine_compare.py` 判据）：① 编译产物先**截断到原函数长度**再比，编译多出的尾部不可见（实测 L1 例里多数尾部是 0x90 对齐填充）；② 截断后**长度必须相等**，编译偏短直接 partial；③ **重定位覆盖的 4 字节是 don't care**（实测覆盖 L1 字节约 27.65%，其中双侧真不同者约占 L1 字节 19.24%）。⇒ 「L1=192」≠「每字节已验证」；且本卡比较的人口是 symbols=1253 / matched=1140（§11.5），与历史 1309 那代不可直接相减；
- `python pipeline/link_probe.py --check` 不低于现有 census（新符号可能带来 LNK 面，属 advisory 但须记录）；
- 基线 `data/status/s4_baseline.json` **不被重锚**：`match` 固定会重写该文件（本卡 chain3 于 14:35:52 重写；锚值 192→192 未变、`matched 1140/1253`、无 `rebaseline` 键）。棘轮禁止事后判断，见 CLAUDE.md；「未被写过」这种措辞不成立，只可宣称「未重锚」。

---

## 10. 风险与后续卡（不在 #58 范围）

- **B-1（推荐下一张卡）0x5052C0 归属**：证据指向 `CCCTData::GetFreeSpaceInPool`，现挂 `CCBStageCam::IsCamValid`。处置需同时改 `CCBStageCam.json`（删该条）+ 决定是否在 CCCTData 重新登记该方法；会影响 `CCBStageCam.cpp` 的 L122/L2001/L2233 之外的编译面，必须单独取证。
- **B-2 相机 8 函数回填 CCBCamControl**：SetCircle(0x5058F0)、LoadPointer(0x5060D0)、IsPointerUnderMouse(0x506020)、UpdateCircleSet(0x505930) 四条体证据较强；0x5061A0/0x5062D0/0x5075E0/0x507B20 需先定 PDB 名再落。一次性 8 条会带来 8 套 sig_model，建议拆两张卡（先 4 条强证据）。
- **B-3 dtor 对**：0x505930 不是 `~CCCTData`（PDB 的 ~CCCTData 是 19B 级），别按 dtor 命名。CCBCamControl 的 0x5081D0/0x5081E0 thunk 对是否应标 `declaration_only`，留给 dtor 专项。
- **R-1 风险**：删掉 CCCTData 的 21 条方法后，这 21 个 VA 在本轮不会被任何单元发射 ⇒ 它们不可能变 L1。这是**已知且接受**的：它们现在符号名错、且所在单元编译失败，本来就 0 贡献（`s4_diff_detail` 的 149 个单元里没有 CCCTData/CCBCamControl/CCBStageCam）。B-1/B-2 完成后才可能回收。
- **R-2 风险**：`CCBStageCam` 里可能有人按 `CCBCamControl.m_Pool` 这种旧视图编码（例如 `this[65].pControl[11]` 那种畸形折叠）。重铸后 `CCCTData` 成为完整类，这些折叠会变成编译错误或语义变化——需在 probe 后逐条看 `CCBStageCam.cpp` 的新错误，属预期阵痛，不是回退理由（衰退纪律：先定位再决策）。

---

## 11. #58 落地实测记录（预留，落地后填写）

| 指标 | 进入时 | 落地后 | 判定 |
|---|---|---|---|
| audit_type_layout sizeof | — | | |
| S2 | 158/230 | | |
| 总错误 | 606 | | |
| L1 | 198 | | |
| partial | 852 | | |
| link_probe | — | | |
| 新增错误族 | — | | |

---

## 附：复跑本文所有断言的最小命令集

```bash
# PDB 记录
python3 -c "import json;d=json.load(open('data/pdb/pdb_export.json'));
[print(c['name'],c['kind'],c['size'],[(m['name'],m['offset']) for m in c['data_members']]) for c in d['classes'] if c['name'] in ('CCCTData','CCBCamControl')]"
# 指令位移
grep -n "0x639c0\|0x64190\|0x68fd0\|0x69094" data/status/_disasm_cache.txt | head -40
# 当前度量
python3 -c "import json;c=json.load(open('data/status/probe_census.json'));
r=c['s2']['results'];print(sum(1 for x in r if x['status']=='ok'),len(r),sum(len(x.get('errors',[])) for x in r))"
python3 -c "import json;d=json.load(open('data/status/s4_diff_detail.json'));print(d['l1'],d['partial'])"
# 方法体位移（逐条）
python3 - <<'EOF'
import json,glob,re
ann=json.load(open('data/annotations/structs/CCCTData.json'))
for va,m in ann['methods'].items():
    tag=va[2:].lower(); fs=glob.glob(f'asm/pal3/decomp/CCCTData_*_{tag}.json')
    if not fs: print(va,m['name'],'NO_DECOMP'); continue
    d=json.load(open(fs[0])); offs=[int(x) for x in re.findall(r'_tail_000\[(\d+)\]',d.get('decompiled_c',''))]
    print(va,m['name'],d.get('size_bytes'),max(offs) if offs else None)
EOF
```

## 11. 落地实测结果（#58，2026-11-27）

> 本节只记录**实测**读数与命令；每条都可按命令复现。所有链路运行在独占窗口（启动前 `ps` 确认无 `idat`/`apply|export|codegen|probe|match|loop`）。

### 11.1 落地的文件与 diff

| 文件 | diff（`git diff --numstat`） | 内容 |
|---|---|---|
| `data/annotations/structs/CCCTData.json` | +25 / −326 | binary_size 430256→**430000(0x68FB0)**；known_members 换成 3 员：`m_Pool tagCCT[2000]@0`、`m_bPoolInUse unsigned char[2000]@0x639c0`、`m_nCCTIndex int[100][50]@0x64190`；methods 21→**0** |
| `data/annotations/structs/CCBCamControl.json` | +8 / −19 | 三份重复池成员删除，新增 `m_CCT: CCCTData@0`；保留 25 员相机尾（0x68fb0..0x690ae）与 33 methods；binary_size 仍 430256 |
| `data/status/bases_adjudications.json` | +27 / −0 | 文件内本日共 3 条新裁决：**本卡补 2 条**（SwordUI / MainPropUI，引用两类 bases_note 原文；SwordUI ctor 0x4A6F10→0x43DCD0、表 0x56F29C slot3=0x43DE40；MainPropUI 表 0x56D618 slot3=0x43DE40），另 1 条 `PropUI` 是**玄策**当日所加（`verdict_by` 署名玄策），随同一工作树出现在本文件 diff 里、非本卡产出 |
| `data/status/check_baseline_errors.json` | +2 / −3 | 先临时冻结本卡两条 N13a 过渡串（export 后已如预期消失），再把临时项**删除**并连带清掉一条同前缀的陈旧 `…561次` 记录；净效果：门禁恢复 0 new |

合计 `4 files changed, 62 insertions(+), 348 deletions(-)`。

> ⚠️ 写域说明（明账）：本卡 `resultDefinition` 的写域只有「两份 JSON + #57 文档」，上面两个 `data/status/*` 文件是 lead 2026-11-27 13:14 显式**临时扩权**才改的——目的是解锁 C11（bases 变更无裁决条目）与 N13a（旧语料字段契约断）两道闸口，且只写这两处、只加/删与这两个类相关的条目；`s4_baseline.json` 不在扩权内、未用 `--rebaseline`。

### 11.2 单元数 230→229（预期内）

`codegen all` 生成 715 个头、**229** 个 cpp（`find pal3/src -name '*.cpp' | wc -l`=229）。CCCTData 落地后 method-less ⇒ 不再生成 `CCCTData.cpp`，与 §3.3/§8.2 的预判一致。

### 11.3 IDA 导出核对（apply→export 之后）

`asm/pal3/ida_structs.json` 实测：

- `CCCTData`：`size=430000`，`data_members = [m_Pool tagCCT[2000]@0, m_bPoolInUse _BYTE[2000]@408000, m_nCCTIndex int[100][50]@410000]`，`methods={}`（0 条）
- `CCBCamControl`：`size=430256`，26 员（`m_CCT CCCTData@0` … `m_bCircleEndSelected unsigned char@430254`），33 methods
- 21 个旧 `CCCTData::*` VA 在导出后全部**无名**（脚本断言 `still_prefixed=0`）：0x41C900、0x5044C0、0x5058F0、0x505930、0x506020、0x5060D0、0x5061A0、0x506260、0x5062D0、0x5075E0、0x507B20、0x508190、0x5081A0、0x5081B0、0x5081C0、0x44D780、0x4533F0、0x4A8770、0x4E7D70、0x4A6730、0x4A67B0

机制（可复核）：`pipeline/ida/apply_annotations.py:2494-2568` 的 step0 会把“不再出现在注解里的具名函数”`set_name('')`，因此删 methods 会真正回退 IDB 名，export 侧（`export_full.py:277-345` 的 `_addr_to_class` 只由 struct JSON 构建）不会再把类前缀补回来。

### 11.4 check / 静态布局

- `python3 pipeline/check_annotations.py`：`0 new errors + 34 frozen(advisory), 110–111 warnings — PASS`（warnings 数在相邻两次运行间 110/111 波动，见 §11.5 复跑记录）
- `tools/audit_type_layout.py --only CCCTData` 与 `--only CCBCamControl`：均只剩 `__tail_drift__ 声明 +0x0 但实际不是`；对照跑 `--only UIListBox`（未改动的类）同样报这一条 ⇒ 该告警是工具既有缺陷（`tools/audit_type_layout.py:69-87` 的 `tail_drift_conflict` 用 `str(k).lstrip('-').isdigit()` 过滤，仓库的十六进制成员键全部被跳过），不是本次重铸引入。

### 11.5 全链读数（独占窗口，2026-11-27 14:23–14:36）

命令与退出码（日志 `/tmp/ccct58/chain3.log`）：

```
apply      rc=0      export   rc=0
codegen all rc=1（外部阻塞，见 11.6）
probe all   rc=1（因 regression_detector 报新失败，见 11.6）
match       rc=0
```

`probe_census.json`（`generated_at=2026-11-27T14:28:35`）：

| 指标 | 落地前 | 落地后 | 门禁 |
|---|---|---|---|
| 单元数 | 230 | **229** | method-less 预期 |
| ok | 158 | **158** | ≥158 ✓ |
| fail_own | 72 | **71** | ≤71 ✓ |
| 总错误 | 606 | **589** | ≤606 ✓ |

`match`（同一份输出，`[metric]` 行原样）：

```
L1 字节 8338 | 重定位覆盖字节 2292 (27.5%) | 被跳过且双侧不同的隐藏差异字节 1632 (19.6% 的 L1 字节 / 71.2% 的重定位字节)
重定位站点值核对：total=8682 ok=1991 mismatch=0 unresolved=6691
重定位目标核对（符号法）：total=8682 ok=99 mismatch=10 unresolved=13 unaligned=8109
```

- 函数级 L1 = **192**（`s4_diff_detail.json`），partial = 812。
- 对照口径：**git HEAD 的 S4 基线 match_L1=189**（`git show HEAD:data/status/s4_diff_detail.json` 的 `l1=189`），当前 **192 = +3**；本轮 population symbols=1253。
- 「198」这个数来自工作区 `s4_baseline.json` 一次**未坐实**的写入（12:16:09 前后，`match_L1=198 / matched=1194 / symbols=1309`；`/tmp/loop84b.log` 结束于 12:01、那轮 codegen 亦 rc=1，lead 记为 03:xx 旧总体残留），不作为门禁依据。lead 2026-11-27 14:06 改判门禁为 `L1≥192 且 population 与上一轮一致`，当前 **192 = 达标**（相对 HEAD 189 为 +3；不得表述为「相对 198 达标」——198 无对应基线文件）。
- **`data/status/s4_baseline.json` 的实际写入（写者已坐实）**：本卡 chain3 的 `match` 于 14:35:52 结束，该文件 mtime=**14:35:52**（`match` 每跑必写，是固定副作用；对影 14:51 复跑又把它重写到 14:51:45，stats 不变）。对影 14:59 补证：`pipeline/_logs/` 的 loop 日志止于 14:10（apply 14:02 / export 14:04 / codegen 14:08 / probe 14:10），loop116 在 probe 中止、没跑 match，`loop_match.log` mtime 仍是 03:12，14:2x–14:35 无第二个 match 进程 ⇒ **写者就是本卡 chain3 的 match，不是「并发 loop 重写」**。写入结果：锚值 **192→192 未变**、`matched 1140/1253`、**无 `rebaseline` 键**。⇒ 本卡只宣称「未重锚」，不宣称「未被写过」。

L1 三限定（引用该数字时必须随行）：① 编译产物先**截断到原函数长度**再比较，尾部多出的字节不可见；② 截断后**两侧长度必须相等**；③ 每处重定位覆盖的 **4 字节计 don't-care**（本轮覆盖 27.5%，其中双侧真不同 19.6% 的 L1 字节 / 71.2% 的重定位字节）。

### 11.6 外部阻塞与已知残留（不属本卡）

1. `codegen all` rc=1：`pipeline/gen/stages/emit_headers.py:3404` 抛
   `RuntimeError: generate_header(PalScriptWaitObj): 槽0x0044ab40 名呈dtor形态('~PalScriptWaitObj')但flags缺dtor——身份标注缺失(注解bug), 先修flags再跑`。
   该 struct 的改动不是本卡（git ` M`，另有卡在处理），本卡不回滚、不绕闸；日志 `/tmp/loop84b.log`、`/tmp/ccct58/chain3.log`。已单列 #59 处理。
   **机理更正（对影 15:03 复核代码）**：`raise RuntimeError` 在 `pipeline/gen/stages/emit_headers.py:3404` 的 try 内，被同文件 **`:3508` 的 `except Exception as _e_slot:`** 捕获（`traceback.print_exc()` + `_slot_decls_emitted = False`），只跳过该类 vtable 槽声明、codegen 继续。
   `codegen all` 的 rc=1 **不是** 这个异常给出的：`pipeline/cli.py:553-563` 在 codegen 结束后自动跑 `probe s2`，`if probe.returncode != 0: … sys.exit(probe.returncode)`。
   ⇒ **只补 PSWO 的 dtor flags 不会让 codegen rc=0**；只要 probe 仍有失败单元（当前为 ScreenEffectMgr），`codegen all` 就仍是 rc=1。这条直接决定 #59 怎么验收。
2. `probe all` rc=1 中的「新失败 1」= `pal3/src/Effect/ScreenEffectMgr.cpp`（C2274×3/C2273×2，全部落在 `m_fadeOut.PalScriptWaitObj` 这类 PSWO 基类子对象转换上）。该单元不引用 CCCTData/CCBCamControl，归因给 PSWO 槽身份（#59），不是本卡。
3. CCBStageCam.cpp L122 新增 1 条 `C2039 'UpdateCamera' : is not a member of 'CCCTData'`：根因是 `skip_functions.json` 里 `0x005044F0` 仍写 `j_CCCTData::UpdateCamera`（该地址体为 `&this->tagCam[n] @+0x11E8 → call 0x5044C0`，不是 thunk，也不属 CCCTData）。本卡试改 `name`/`target_name` 后只把错误换成 `C2065 'UpdateCameraByIndex' : undeclared identifier`（count 不变），证明单改名字不足以修复，已**回退**该文件（`git diff` 为空），留后续卡按真实归属处理（§12 B-2）。
4. CCBCamControl.cpp L1096 `C2440`（`m_Pool[11].dwReserved[0]` 与 `fStartTracePosZ` 的赋值链）与 CCBStageCam.cpp L2001 `C2512 RoleCamera 无默认构造` 都是落地前既有错误，本卡未触碰。
5. SaleUI 那 6 条真新增（C2107×4 / C2102×2，L755/L756）已由对影 14:59 定位：`data/annotations/structs/SaleUI.json` 工作树未提交改动（+53/−23）把 0x17604/0x1795C 的 `unsigned char[168]` 拆成 `UIFrameContainer`(152B) + 尾随 `tagRECT`(16B)（新增 0x1769C/0x179F4），正是该错误形态；不属本卡，由该改动所属卡在落地后重跑 probe 复核，不必单开卡。

### 11.7 结论

- P-1 落地完成：两份 JSON、IDB、导出、check 全部一致；21 条错挂方法已退出，CCCTData 洞（430,256B chimera）闭合为“3 员 / 0 方法 / 430,000B”。
- 门禁按 lead 修订口径全绿：ok 158、fail 71、总错误 589（−17）、L1 192（vs HEAD 189，+3）、check PASS、0x4A2150 仍在 L1、baseline 未重锚（192→192、无 rebaseline 键；但 `match` 固定会重写该文件，见 §11.5）。
- 洞归属（checklist④）：CCCTData 目标洞已闭合（0→408000→410000→430000，0 洞）；CCBCamControl 仍有 **3 段既有尾域空洞**，均为落地前就存在的成员间隙、与本次重铸无关：`0x68FBD–0x68FBF`（3B，m_bRunning@0x68FBC 之后到 m_fp@0x68FC0）、`0x68FC4–0x68FCF`（12B，m_fp 之后到 m_nCurList@0x68FD0）、`0x690AF`（1B，m_bCircleEndSelected@0x690AE 之后的对象尾对齐 pad，对象止于 0x690B0）。402,824 类 Y 的洞**不计入**这两类（只在 `_identity_note` 提及，未进 known_members）。
- 决定性外部项（PSWO 槽 dtor flags、ScreenEffectMgr）已转 #59；`skip_functions` 悬空名与 4 条相机函数的真实归属留后续卡（B-2）。
