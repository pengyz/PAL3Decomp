# Plan Task 1 独立对抗复核 — j_D3DX 三名正名（spec §7 #2）

- **复核对象**：working-tree 变更（`git diff --cached`；注意 **非 HEAD**——HEAD=667a3d8d8 是 T2' tables 提交，与本任务无关。三件 functions.json 变更 + `tests/test_d3dx_naming.py` 均为 **staged 未提交**）
- **复核方法**：不信任自述，只信实测。二进制真相走 IDA MCP（idb_open `original/PAL3.exe.i64`，用完 `save=false` 关闭）；字节二次确认走 `get_bytes`（非 py_eval）；签名形核比对 `tools/vc6/Include/d3dx9math.h` + `build/gbengine.map`；机制面读 `pipeline/gen/data.py`/`emit_cpp.py`/`stages/collect.py`；diff 纯度走 `git diff --cached`。
- **复核时间**：2026-10-28
- **一句话结论**：**ACCEPT-WITH-FIXES** —— 三名（RandLerpF / D3DXVec3Normalize / D3DXQuaternionSlerp）**语义全对、A 级证据扎实**；但 D3DX 两条**签名调用约定写错（`__cdecl` 应为 `__stdcall`/WINAPI）**＝task 自设的"误形=静默坏码"红线，**必修于 Task 1**。

---

## 总裁定：ACCEPT-WITH-FIXES

核心交付（spec §7 #2「三名正名」）**达成**：三个名字经二进制真身逐条实测，语义全部正确，证据可复现。但变更行内的**签名调用约定**有一个真实正确性缺陷（P1），且测试未锁定该维度、skip_functions.json 有双副本分叉（P2/P3）。命名工作可接受，缺陷须在本任务内补正后方可结项。

---

## 逐项 verdict

### 1. 名实复验（IDA 实测） — **CONFIRMED**（附一处证据精度注记）

| 地址 | 旧名（错） | 新名 | 真身实测 | verdict |
|---|---|---|---|---|
| 0x4B8200 | j_D3DXVec3TransformCoord | **RandLerpF** | Hex-Rays：`if(a==b) return a; else a+(rand()%10000+1)*flt_56F494*(b-a)`；字节 `fmul [0x56F494]`·`idiv 0x2710`(10000)·`inc edx`·**plain `c3 ret`**（cdecl）·66B | **CONFIRMED** |
| 0x542533 | j_D3DXVec3TransformCoord_0 | **D3DXVec3Normalize** | 跳板 `ff 25 c4 90 60 00` = `jmp [0x6090C4]` ✓；真身 impl **0x5450B5 = c_D3DXVec3Normalize，157B**（`0x9d`），Hex-Rays = `1/sqrt(dot(v,v))*v` 教科书向量归一化 | **CONFIRMED** |
| 0x544771 | j_D3DXMatrixMultiply | **D3DXQuaternionSlerp** | 跳板 `ff 25 34 91 60 00` = `jmp [0x609134]` ✓；真身 impl **0x544777 = c_D3DXQuaternionSlerp，227B**（`0xe3`），Hex-Rays = 点积+符号翻转+`sin`/`atan2` 教科书四元数球面插值 | **CONFIRMED** |

- **0x4B8200 真身=random-lerp**：反汇编逐字节吻合 claim「if a==b return a; else a+(rand()%10000+1)*flt_56F494*(b-a)」。`flt_56F494`=全局浮点 @0x56F494（`fmul [0x56F494]`），值≈1e-4。调用面 **11 xref**（claim ✓，实测 xref_count=11：sub_4B91E0×4·sub_4B9EA0×1·sg_emission_control `_todo_004BA800`×5·sub_4BABC0×1），全部 2 浮点实参 → 与 `float(float,float)` 兼容。
- **0x542533 / 0x544771 跳板 + 真身**：两跳板确为 `jmp [abs]` PSGP 分发型；两个 impl（0x5450B5 归一化 157B / 0x544777 球面插值 227B）**字节数与反编译语义双双精确吻合 claim**。0x544771 被 **sub_544884 调 3 次**，而 sub_544884 反编译＝`Slerp(Slerp(Q1,C,t),Slerp(A,B,t),2t(1-t))`，**与 d3dx9math.h 的 D3DXQuaternionSquad 注释逐字对应** ⇒ 强 A 级旁证 0x544771=Slerp。
- **调用面佐证**：0x542533 被 sg_emission_control（0x4ba97f）以 `(vec*,vec*)` 调用，生成码 `D3DXVec3Normalize(&v45,&v45)`；0x544771 被 Squad 以 4 参调用，生成码 Slerp×3。

> **[注记 P4·非致命]** claim 文字「槽#7/#35 default=0x5450B5/0x544777」的**分发槽机制描述不精确**：静态分发单元 `[0x6090C4]`=0x542526、`[0x609134]`=0x54474D（冷/初始化桩），而 normalize/slerp impl 注册在**另一数据单元** 0x6091ec=0x5450B5 / 0x60925c=0x544777（xrefs_to 证实）。PSGP 分发是**运行时重指向**的，静态单元值非 0x5450B5。但 claim 的**实体部分**「X=c_Y（NB 逐字节）」经 impl 直测**完全成立**（0x5450B5=157B 归一化、0x544777=227B 球面插值）。⇒ 命名结论不受影响，仅证据叙述的"default target"框架需措辞收紧。

### 2. 签名形核 — **PARTIAL / DEFECT（P1）**

**RandLerpF**：`float __cdecl(float a, float b)` —— **正确**。函数尾 `pop ecx; ret`（plain `c3`，调用方清栈）=cdecl ✓；11 xref 全 2 浮点参兼容 ✓。

**D3DX 两条 —— 逐字段比对 d3dx9math.h，形参/返回全中，唯调用约定错**：

| 字段 | d3dx9math.h 原型 | functions.json | verdict |
|---|---|---|---|
| D3DXVec3Normalize 返回 | `D3DXVECTOR3*` | `D3DXVECTOR3 *` | ✓ |
| 参数1 | `D3DXVECTOR3 *pOut` | `D3DXVECTOR3 *pOut` | ✓ |
| 参数2 | `CONST D3DXVECTOR3 *pV` | `const D3DXVECTOR3 *pV` | ✓ |
| **调用约定** | **`WINAPI` = `__stdcall`** | **`__cdecl`** | ✗ **MISMATCH** |
| D3DXQuaternionSlerp 返回/4参 | `D3DXQUATERNION*` / `pOut,pQ1,pQ2,FLOAT t` | 同形 | ✓ |
| **调用约定** | **`WINAPI` = `__stdcall`** | **`__cdecl`** | ✗ **MISMATCH** |

**调用约定＝`__stdcall` 的三重独立实证**：
1. **gbengine.map**（原链图，Jun 22 2026）：`_D3DXVec3Normalize@8`（@8=stdcall，8B=2 指针）+ `?c_D3DXVec3Normalize@@YGPAUD3DXVECTOR3@@PAU1@PBU1@@Z`（**`YG`=stdcall** 名字修饰）；`_D3DXQuaternionSlerp@16` + `@@YG...`。
2. **d3dx9math.h**：两条原型均为 `WINAPI`（=`__stdcall`）。
3. **调用点无栈清理**（IDA 实测）：`0x4ba97f call D3DXVec3Normalize` 后紧接 `mov ecx,[edi+9050h]`（**无 `add esp`**）；`0x54489b call D3DXQuaternionSlerp` 后紧接 `fld [ebp+arg_14]`（**无 `add esp`**）⇒ 调用方不清栈=stdcall（cdecl 会 `add esp,8/16`）。

**后果**：`free_sig_decl` 对 `__cdecl` 去约定产出 cdecl 声明 ⇒ `pal3/src/free_functions.h:112-113` 实发
`D3DXVECTOR3 * D3DXVec3Normalize(...)` / `D3DXQUATERNION * D3DXQuaternionSlerp(...)`（无 cc=cdecl），调用点编译成 `call; add esp,N`，而真身 stdcall（`ret N`）自清 ⇒ **双重清栈＝栈破坏 + 每调用点多 3 字节＝字节失配**。这正是 task 自设红线「误形=SetBlend 静默坏码」。**结论：D3DX 两签名 `__cdecl`→`__stdcall`（WINAPI），必修。**（RandLerpF 的 `__cdecl` 是对的，勿连带改。）

### 3. 机制面（skip 罩下 decl 会否发射） — **DECL 已发射（无 C2065）；但暴露 P1 约定缺陷 + P2 双副本分叉**

- 两跳板确在 `skip_functions.json`：`0x00542533={name:j_D3DXVec3TransformCoord, reason:crt_runtime}`、`0x00544771={name:j_D3DXMatrixMultiply, reason:crt_runtime}`（全表 1910 项，crt_runtime 923）。
- **消费点实测**：`data.py:252` 的 skip 循环**只处理 `reason=='thunk'`** ⇒ crt_runtime 两跳板**不入 thunk 表**；functions.json 增补路径（`data.py:541-580`）**无 skip_funcs 过滤** ⇒ 新名 decl **照发**进 `free_func_sigs`。发射端 `emit_cpp.py:171,182` 实证：`free_functions.h:112-113/239` 已含 D3DXVec3Normalize/D3DXQuaternionSlerp/RandLerpF 声明（mtime 21:14:45 晚于 functions.json 21:09:35＝新鲜）。
- **⇒ 「skip 罩下 decl 不发射⇒调用点 C2065＝修复未闭环」这条担忧不成立**：decl 已发射，调用点名实相符，无 C2065。**发射轴闭环 ✓**。
- **但发射的是 `__cdecl` 形**（见 §2）⇒ 机制把 decl 发出来了，却发成了错约定。**「声明走 <d3dx9math.h>」的自述与实发不符**：free_functions.h 不含 `<d3dx9.h>`，实发的是 functions.json 的 cdecl 形，未路由到 WINAPI 头。
- **裁定**：skip/decl 机制本身**可接受**（发射无碍、C2065 不会复发）；但其暴露的**签名约定缺陷（P1）属 Task 1 必修**（就在被改条目内，是签名交付的一部分）。skip_functions.json 陈旧名分叉（P2）建议同批修，最迟挂 Task 3。

### 4. 测试质量 — **PARTIAL**（真锁名与部分证据，但未锁约定、未全带错名退役）

- 3 测**全绿**（`python3 tests/test_d3dx_naming.py` / pytest 3 passed）。
- **真锁面**：test1 带显式错名退役 `name != 'j_D3DXVec3TransformCoord'` ✓ + 证据源断言缺；test2/3 带 `'d3dx9math' in source` 证据入账 ✓ + 名锁 `name==`。
- **缺口**：
  - **未锁调用约定**：断言只查 `'float' in sig and 'void *' not in sig`（test1）/'D3DXVec3Normalize' in sig or 'D3DXVECTOR3' in sig（test2/3，子串宽松）⇒ **即便签名是错的 `__cdecl` 也照过**，抓不到 §2 主缺陷。
  - test2/3 **无显式错名退役断言**（仅靠 `name==` 隐含）；test1 **无 source 证据入账断言**。
  - 测的是 JSON 状态锁（非二进制真相），作回归锁合理，但**锁住了含错约定的现状**。
- **建议**：增补「签名含 `__stdcall`（D3DX）/`__cdecl`（RandLerpF）」约定断言 + test2/3 显式 `name != 'j_D3DXVec3TransformCoord_0'/'j_D3DXMatrixMultiply'`。

### 5. JSON 全文件重写面（diff 纯度） — **CONFIRMED 纯净**

- `git diff --cached -- data/annotations/functions.json` = **2 hunk / 3 条目**（0x4B8200 改 1、0x542533+0x544771 增 2），`13 insertions(+), 3 deletions(-)`。
- **无格式 churn**：`json.dump(indent=2)` 重写未混入缩进/排序/空白噪声，diff 恰为三件意图变更。
- 尾换行一致（新旧皆无 trailing newline，字节 `}.}` 收尾）；JSON 合法（616 项）；新条目缩进 2 与既有风格一致。
- **⇒ 纯三件变更 ✓，无格式缺陷。**

---

## 缺陷清单

| ID | 级别 | 位置 | 缺陷 | 修复 | 归属 |
|---|---|---|---|---|---|
| **P1** | **高（静默坏码）** | functions.json `0x00542533`·`0x00544771` 的 `signature` | D3DX 两签名调用约定 `__cdecl`，真身 `__stdcall`/WINAPI（map @8/@16+YG·头 WINAPI·调用点无清栈三重证实）⇒ free_functions.h 发 cdecl 形 → 调用点 `call;add esp,N` 对 stdcall `ret N` 双清栈＝栈破坏+字节失配 | 两签名 `__cdecl`→`__stdcall`（WINAPI）；RandLerpF 保持 `__cdecl` | **Task 1 必修** |
| **P2** | 中（双副本分叉） | `skip_functions.json` `0x00542533`·`0x00544771` | 陈旧名 `j_D3DXVec3TransformCoord`/`j_D3DXMatrixMultiply` 未随 functions.json 正名同步（`_skip_function_names` 仍导出旧名；apply_annotations 亦读此文件命名，存在回写竞序/回归风险） | 同步 skip_functions.json 两名为 D3DXVec3Normalize/D3DXQuaternionSlerp（或统一单一命名权威） | 建议 Task 1 同批，最迟 Task 3 |
| **P3** | 中（测试锁不全） | tests/test_d3dx_naming.py | 未锁调用约定（错 `__cdecl` 也过）；test2/3 无显式错名退役断言；test1 无 source 证据断言；形核断言子串过松 | 增约定断言（D3DX=`__stdcall`/RandLerpF=`__cdecl`）+ 显式 `name != 旧名` + 收紧形核 | Task 1 |
| **P4** | 低（证据措辞/自相矛盾） | functions.json source 字段 | ①「slot#N default=0x5450B5/0x544777」框架不精确（静态分发单元 0x542526/0x54474D，impl 注册于 0x6091ec/0x60925c，PSGP 运行时重指向）；②0x4B8200 source 保留旧「3 参 D3DX 真形」与追加的 float(float,float) 自相矛盾（追加式勘误，单看误导） | ①措辞改「impl 0x5450B5=c_D3DXVec3Normalize（157B），经 PSGP 槽分发」；②旧断言标注「已废弃」或删除 | 可选 |

---

## 未复验清单（本轮未做/无法做，非遗漏即否定）

1. **P1 缺陷的实效读数**：未跑全链 `apply→export→codegen→probe→match` 观察 cdecl/stdcall 在字节匹配与运行时的实际爆点。**静态证据（调用点无清栈 vs cdecl 声明）已足以定性 P1**，但未产出「match 该调用点 partial/字节 diff」的当场读数（受 match 恒红棘轮 + 管线占用 IDB 影响）。
2. **PSGP 分发单元→impl 的完整重指向链**：确认了 impl 静态注册于 0x6091ec/0x60925c 且 thunk 读 0x6090C4/0x609134，但未逐拍追 `init_D3DXVec3Normalize/…Slerp` 的运行时 repoint 全过程（不影响命名结论）。
3. **skip_functions.json 陈旧名的全部下游消费面**：已核 data.py/collect.py/emit_cpp.py/export_full.py 主消费点（crt_runtime 名不入 thunk 表、不抑制新名 decl），但未穷举 apply_annotations.py:2364 命名回写的时序竞态后果。
4. **cdecl 声明是否被 `<d3dx9.h>` stdcall 声明覆盖/冲突**：已证 free_functions.h 不含 d3dx9 头、实发 cdecl，判定 cdecl 形即调用点所用；但未跑一次实编译观察生成的 call 序列字节。
5. **RandLerpF 11 个调用点逐点实参形态**：抽验了 sg_emission_control 的 5 处（全 2 浮点），其余 6 处（sub_4B91E0/4B9EA0/4BABC0）未逐点反汇编实参，按 xref 计数与统一签名推定兼容。

---

## 附：复核可复现要点

- **名实**：`idb_open original/PAL3.exe.i64` → `decompile 0x4B8200/0x5450B5/0x544777/0x544884` + `get_bytes 0x4B8200(70)/0x542533(16)/0x544771(16)/0x6090C4(4)/0x609134(4)` + `xrefs_to 0x4B8200/0x542533/0x544771` + `lookup_funcs 0x5450B5/0x544777`（尺寸 0x9d/0xe3）→ 用完 `idb_close save=false`。
- **签名**：`sed -n '720,735p;1105,1125p' tools/vc6/Include/d3dx9math.h` + `grep _D3DX…@ build/gbengine.map` + 调用点 `disasm 0x4ba97f/0x54489b`。
- **机制**：`sed -n '23,70p;480,600p' pipeline/gen/data.py` + `grep free_func_sigs pipeline/gen/stages/emit_cpp.py` + `grep skip_functions pipeline/gen/stages/collect.py`。
- **diff 纯度**：`git diff --cached --stat/-- data/annotations/functions.json` + `tail -c20|xxd`（尾换行）+ `json.load`（616 项合法）。

> 注：复核期间 `original/PAL3.exe.i64` 曾被并行 `export_full.py`（idat）占用（R14：管线持 IDB 期间不得并发 idat），待其释放后方 idb_open，未并发写库。
