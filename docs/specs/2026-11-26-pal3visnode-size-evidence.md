# PAL3VisNode 尺寸取证：binary_size=88 与 +0x58 读写矛盾（#15，只读）

- 卡片：tsk_01M8C3GWJ1KF2NN2BGH2FV（只读）
- 取证源：`original/PAL3.exe`（经 `data/status/_disasm_cache.txt` 反汇编缓存）、`asm/pal3/ida_structs.json`（IDB 导出）、`asm/pal3/decomp/`、`data/annotations/structs/*.json`（只读）
- 未使用 `pal3/src`（重生成产物）；未跑 apply/export/codegen/probe；未改 data/annotations、pipeline、基线。本文件是唯一新增文件。

## §0 结论

1. **`sizeof(PAL3VisNode) = 0x5C = 92`**，注解的 `binary_size: 88 / base_size: 88` 少了 4 字节。
   依据：ctor 在 `+0x58` 写 4 字节（下界 ≥0x5C）；三个派生类把自有首个成员放在 `0x5C`（上界 ≤0x5C）；两侧夹逼唯一解 0x5C。
2. **`+0x58` 是一个 4 字节 int 状态量，取值 0 / 1 / -1**。写点：PAL3VisNode ctor 清 0、`RenderTargetNode::UpdateParticleEffect` 置 -1、`RenderTargetNode::SetPathMode` 置 1、`ScreenEffectMgr::UpdateAnimation` 清 0、`ScreenEffectMgr` 的 0x4BF680 置入参。读点：无名 getter `0x4B7020`、`RenderTargetNode::UpdateParticleEffect/Stop`、`ScreenEffectMgr::Render/UpdateAnimation`。
3. **88 的来源是「继承值」而非实测**：基类 `gbVisNode` 的最后一个成员 `BlendFlag@0x54`（4B）恰好止于 `0x58`，`gbVisNode` size 就是 88；`PAL3VisNode` 的 `known_members` 为空，导出器便取了基类尺寸。**IDA 自己的 UDT 却把三个派生的自有成员排在偏移 92（0x5C）**，即 IDB 内部认为基类是 92 字节，与导出的 88 自相矛盾。
4. **三类派生的 sizeof 算术闭合在基类 0x5C**：`CEffGroupNode 0x74 = 0x5C + 6×4`、`RenderTargetNode 0x60 = 0x5C + 4`、`UI3DModelNode 0xF8 = 0x5C + 0x9C`，且三处 `operator new` 立即数（0x74 / 0x60 / 0xF8）与 IDB size 逐一相符（§2.3）。
5. **对 ScreenEffectMgr 拆类（#11 结论 B）的影响**：B : PAL3VisNode 的基类边界是 `[0x00, 0x5C)`；B 的自有首成员是 `float@0x5C`（`UpdateAnimation` 的 `fadd/fstp [edi+0x5c]`）；`0x454 + 362860 = 363968` 的 ParticleEffect 闭合**不受影响**。但 `ScreenEffectMgr.json` 目前**没有声明 bases、也没有 base_size**，拆类卡必须先补这两项，否则编译器裁判看不到基类。
6. **建议落地顺序**：先修 PAL3VisNode（`binary_size` 88→92 + `m_nState@0x58`，`base_size` 保持 88），再拆 ScreenEffectMgr。理由：若先拆，派生 B 会以 88 为基类尺寸，B 的 `0x5C` 成员会被判成与基类尾部冲突（假阳性），且 `audit_type_layout` 无法区分是「基类错」还是「派生错」。
7. **顺带发现（不在本卡范围，只列不修）**：`ScreenEffectNode` 的工厂 `new 0x424`（1060B）与注解 `size: 220` 相差 840B；其注解成员 `m_pTexture@0xA4 / m_pRenderEffect@0xA8` 与 B 的 ctor 写点 `[edi+0xA4]=0 / [edi+0xA8]=0` 重合，疑似错归属（见 §4 缺口 G3/G4）。

## §1 访问点清单（PAL3VisNode 家族，+0x58）

### 1.1 归属本族的访问（全部 4 字节宽）

| VA | 原始字节 | 指令 | 所在函数（IDB 名） | 性质 |
|---|---|---|---|---|
| `0x4B6F7F` | `c7 46 58 00 00 00 00` | `mov DWORD PTR [esi+0x58],0x0` | `PAL3VisNode::PAL3VisNode`（ctor `0x4B6F70`） | 写 4B，唯一一次 |
| `0x4B7020` | `8b 41 58` | `mov eax,DWORD PTR [ecx+0x58]` | 无名 getter（紧随 dtor 之后，IDB methods 未登记） | 读 4B |
| `0x42B21A` | `e8 01 be 08 00` | `call 0x4B7020`（随后 `cmp eax,0xffffffff; sete cl`） | 调用方（外部，`ecx=[esi+4]`） | 读 4B，判 `== -1` |
| `0x4BD903` | `8b 46 58` | `mov eax,DWORD PTR [esi+0x58]` | `RenderTargetNode::UpdateParticleEffect`（`0x4BD900`） | 读 4B，作 switch 值 |
| `0x4BD92B` | `c7 46 58 ff ff ff ff` | `mov DWORD PTR [esi+0x58],0xffffffff` | 同上 | 写 4B = -1 |
| `0x4BD950` | `83 79 58 ff` | `cmp DWORD PTR [ecx+0x58],0xffffffff` | `RenderTargetNode::Stop`（`0x4BD950`） | 读 4B，判 -1 提前返回 0 |
| `0x4BD997` | `c7 41 58 01 00 00 00` | `mov DWORD PTR [ecx+0x58],0x1` | `RenderTargetNode::SetPathMode`（`0x4BD990`） | 写 4B = 1（入参==1 时） |
| `0x4BF39F` | `83 7e 58 01` | `cmp DWORD PTR [esi+0x58],0x1` | `ScreenEffectMgr::Render`（`0x4BF260`） | 读 4B，门控 |
| `0x4BF509` | `83 7f 58 01` | `cmp DWORD PTR [edi+0x58],ebx`（ebx=1） | `ScreenEffectMgr::UpdateAnimation`（`0x4BF4F0`） | 读 4B，门控 |
| `0x4BF645` | `c7 47 58 00 00 00 00` | `mov DWORD PTR [edi+0x58],0x0` | `ScreenEffectMgr::UpdateAnimation` | 写 4B = 0（结束时） |
| `0x4BF686` | `89 42 58` | `mov DWORD PTR [edx+0x58],eax` | `ScreenEffectMgr` 的 `0x4BF680`（IDB 名 `GetPageIndex`，体是 setter） | 写 4B = 入参 |

**`+0x5C` / `+0x60` 在 PAL3VisNode 自身代码中零访问**：ctor 全文只有 `[esi]=vptr`、`[esi+0x58]=0` 两处写，dtor 只读 `[esp+8]` 参数位。这也是「类自身止于 0x5C」的直接依据。

### 1.2 同一地址窗口内但**不归属本族**的 `+0x58` 访问（排除，避免把别类字段算进来）

| VA | 指令 | 排除理由 |
|---|---|---|
| `0x4B77BC` / `0x4B78EA` | `fstp DWORD PTR [esp+0x58]` | 栈槽，非对象成员 |
| `0x4B87CE` / `0x4B88B1` | `lea edi,[edx+0x58]` / `fst DWORD PTR [ebx+0x58]` | 该函数 this 含 `[ebx+0x9050]`、`[ebx+0x9024]`，是别的大类，不是 PAL3VisNode 家族 |
| `0x4BA242` / `0x4BAECF` / `0x4BB00C` | `fst [ecx+0x58]` / `lea [ebx+0x58]` 后 `rep movs` | 目标对象含大数组（`[ebx+0x1568]`、`[ebx+0x2a1c]` 等），是另一类；`0x58` 在此是拷贝目标而非 4B 字段 |
| `0x4BDBBD` | `call DWORD PTR [edx+0x58]` | 经函数指针表项调用，`edx` 非本类 this |
| `0x4BDE08` | `mov eax,DWORD PTR [esi+0x58]` | 另一函数（`0x4BDD..`），其 this 与本族方法域不重合，未归属 |
| `0x4BF7E7` | `mov ecx,DWORD PTR [esp+0x58]` | 栈槽 |

## §2 尺寸证据

### 2.1 下界：ctor 在 `+0x58` 写 4 字节 ⇒ 尺寸 ≥ 0x5C

`0x4B6F7F` 的 `c7 46 58 00 00 00 00` 是 4 字节立即数写 `[esi+0x58]`，且 ctor 在它之后没有任何 `+0x5C` 访问就 `ret`。一个类若只有 0x58 字节，这条写就越界 4 字节。⇒ `sizeof(PAL3VisNode) ≥ 0x5C`。

### 2.2 上界：三个派生类把自有首个成员放在 `0x5C` ⇒ 基类 ≤ 0x5C

| 派生类 | 自有成员起点证据 | 若基类 >0x5C 的后果 |
|---|---|---|
| `CEffGroupNode` | ctor `0x4B72E0` 在 `0x4B72F3` 写 `[esi+0x5c]`（字节 `89 46 5c`），`0x4B72F6` 写 `[esi+0x60]` | `0x5C` 落在基类内 ⇒ 与基类成员重叠，违反 C++ 布局 |
| `UI3DModelNode` | ctor `0x4B74A0` 在 `0x4B74C6` 写 `[esi+0x5c]`（`89 56 5c`），`0x4B74C9` 写 `[esi+0x60]` | 同上 |
| `RenderTargetNode` | ctor `0x4BD830` 在 `0x4BD83E` 写 `[esi+0x5c]=0`（`c7 46 5c 00 00 00 00`） | 同上 |

三个独立类的 ctor 都把「自己新加的成员」放在 `0x5C`，没有任何一个放到 `0x58` 或 `0x5A`，说明编译器认为基类正好占满 `[0x00,0x5C)`。

注：IDB 导出里 `RenderTargetNode` 的 `bases` 为空、`base_size` 缺失，是导出缺口（它的 ctor `0x4BD830` 首条即 `call 0x4B6F70`，且自有首成员在 `0x5C`，派生关系成立），不影响本节的「上界」论证。

### 2.3 算术闭合：`operator new` 立即数 × 派生 sizeof

| 工厂 new 点 | 立即数 | 紧随的 ctor | 类 | IDB size | 与基类 0x5C 的关系 |
|---|---|---|---|---|---|
| `0x4B70EB` | `push 0x60` | `0x4BD830` | `RenderTargetNode` | 96 (0x60) | `0x5C + 4` |
| `0x4B718F` | `push 0xf8` | `0x4B74A0` | `UI3DModelNode` | 248 (0xF8) | `0x5C + 0x9C` |
| `0x4B71C4` | `push 0x74` | `0x4B72E0` | `CEffGroupNode` | 116 (0x74) | `0x5C + 0x18` |
| `0x4B715A` | `push 0x424` | `0x4B7C30` | `ScreenEffectNode` | 注解 220 (0xDC) **不符** | `0x5C + 0x3C8`（缺口 G3） |
| `0x4B7121` | `push 0x58dc0` | `0x4BEE60` | `ScreenEffectMgr` | 363968 (0x58DC0) | 派生 B，基类边界同 0x5C |

前 3 行是本节主证据：new 的字节数 = 派生 sizeof，且都恰好等于 `0x5C + 自有成员区`；若基类是 0x58，三者会各多出 4 字节无法解释的空洞，IDB 也不会把首成员放在 92。

### 2.4 88 的失真机制

| 类 | IDB size | 自有成员范围 | 说明 |
|---|---|---|---|
| `gbChain1DNode` | 8 | `next@4` | 基类链最底 |
| `gbNBTreeNode` | 28 | `pFather@8`、`children@12` | — |
| `gbVisNode` | 88 = 0x58 | `pSceneGraph@0x1C` … `BlendFlag@0x54`(4B) | 自身恰好止于 0x58 |
| `PAL3VisNode` | **88（应为 92）** | 注解 `known_members` 为 `{}`；实际仅 ctor 新建 `+0x58` 一个 4B 字段 | 导出器取到「继承来的 0x58」，没算新字段 |
| `CEffGroupNode` | 116 | 92(0x5C) 起 6×int | IDB 内部按「基类 92」排布 |
| `UI3DModelNode` | 248 | 92(0x5C) 起 8 项 | 同上 |

⇒ `binary_size: 88` 与 IDB 自身 `data_members` 的偏移 92 互相矛盾；88 是基类 `gbVisNode` 的值。

## §3 对 ScreenEffectMgr 拆类的影响

### 3.1 基类边界

B（ScreenEffectMgr，`new 0x58DC0` / ctor `0x4BEE60`）在 ctor 首条语句 `0x4BEE7F call 0x4B6F70` 调 PAL3VisNode ctor，dtor `0x4BEF30` 在收尾 `0x4BEF9A call 0x4B6FB0` 调其 complete dtor ⇒ **B : PAL3VisNode 成立**，基类子对象占 `[0x00,0x5C)`。

B 的自有首成员：`UpdateAnimation`（`0x4BF4F0`）的 `fadd DWORD PTR [edi+0x5c]` / `fstp DWORD PTR [edi+0x5c]`（`0x4BF506`/`0x4BF50C`）⇒ `float@0x5C`（时间累加器）。这与「基类止于 0x5C」严格一致：0x5C 是 B 的第一个自有字节。

### 3.2 `0x454` 闭合不受影响

`ParticleEffect` 内联在 `0x454`，其 `binary_size = 362860`，`0x454 + 362860 = 0x58DC0 = 363968 = B.size`。PAL3VisNode 的 88→92 修正只改**基类段的解释**，不改 B 的绝对偏移与总尺寸，闭合等式保持 `True`（复现命令 C6 的子项）。

### 3.3 注解现状缺口：`ScreenEffectMgr.json` 没有基类

实测（C6）：`bases = None`、`base_size = None`、`binary_size = 363968`。也就是说当前注解把 B 当作「无基类、从 0x4 起全是自有成员」的类，这正是 `m_fadeIn@0x4 … m_nEffectCount@0x94` 等 A 侧成员被挂到 B 上的原因（#11 的「两类合并」结论）。

补充（工作区实况，非本卡改动）：`data/annotations/structs/ScreenEffectMgr.json` 当前还有他卡未提交的 60 行新增（`0xa4 m_nGeometryReady`、`0xa8 m_pGeomRenderEffect`、`0xb0 m_ringQuadsLarge[6]`、`0x248 m_ringQuadsSmall[6]`、`0x3e0 m_singleQuad`、`0x424` 等，均标 A 级并引用同一批 ctor/Render 指令）。这些正好是 B 侧 `0x5C` 之后的成员，拆类卡可直接沿用，不必重命名；本卡未改该文件。

### 3.4 落地顺序与理由

1. **先修 PAL3VisNode**（`binary_size` 88→92、`base_size` **保持 88**、新增 `m_nState@0x58`）。成本 4 文件各 1–2 行，收益：派生类基类边界正确，后续拆类不会被 `audit_type_layout` 判为「0x5C 成员与基类尾部重叠」。
2. **再拆 ScreenEffectMgr**：`bases: [{"name":"PAL3VisNode","offset":0}]`、`base_size: 92`（此字段=直接基类尺寸；**只有在卡 A 把 PAL3VisNode.binary_size 改成 92 之后才等于 92**，否则仍是 88），删掉 0x4..0x94 的 A 侧成员，补 B 自有成员（0x5C float、0xA4、0xA8、0xB0/0x248 两段数组、0x3E0 4×0xC、0x424/0x444、0x454 ParticleEffect）。
3. 顺序反了会制造假阳性：B 以 base_size=88 计算时，`m_fTime@0x5C` 距基类尾只剩 0 字节，任何「基类尾部对齐」检查都会报重叠；且无法区分是基类尺寸错还是成员偏移错。

### 3.5 A/B 成员归属原则（拆类时不动 A）

`0x4 / 0x20 / 0x38 / 0x50` 四个多态子对象（`ProcessEffect` 跳表 + 虚调用 `[edx+0xC]`，`ClearAllEffects` 逆序析构）属于 A 侧，**不在 B 的成员表里**；`0x68..0x94`（队列/分配器/计数）同理。B 侧从 `0x5C` 起算，`0x5C..0xA4` 之间除 `0x5C` float 外无已知成员（洞），按命名铁律留白，不猜。

## §4 证据等级与缺口

### 4.1 结论分级

| 结论 | 等级 | 依据 |
|---|---|---|
| `sizeof(PAL3VisNode) = 0x5C` | **A** | 下界（ctor 4B 写）+ 上界（三派生首成员 0x5C）+ 三处 new 立即数算术闭合，四路独立 |
| `+0x58` 是 4B int 状态量（0/1/-1） | **A**（存在/宽度/取值域） | 11 处访问全为 4B；取值域由 `-1/0/1` 三处立即数与 switch/cmp 结构确定 |
| 语义名 `m_nState` | **B**（建议名） | 行为形是状态机（setter 0x4BF680 置入参、UpdateAnimation 结束时清 0、Render 以 `==1` 门控、Stop 以 `==-1` 提前返回），但无符号/PDB 直证；落地卡须在 name_note 写这条链 |
| `ScreenEffectMgr : PAL3VisNode` | **A** | ctor 首调 `0x4B6F70`、dtor 尾调 `0x4B6FB0`，且 B 自有首成员正好落在 0x5C |
| `ScreenEffectMgr` 注解缺 bases/base_size | **A**（实测字段为空） | C6 输出 |
| B 的 `0x454` 闭合不变 | **A** | 算术等式与 new 立即数互证 |
| `ScreenEffectNode` 真尺寸 1060 | **A**（new 立即数 0x424） | `0x4B715A push 0x424` → `0x4B7C30` ctor；与注解 220 冲突，属新缺口 |

### 4.2 缺口清单（本卡不修，供后续卡立项）

| 编号 | 缺口 | 现状 | 影响 |
|---|---|---|---|
| G1 | `m_nState` 的最终命名 | 只有行为形证据（B 级） | 落地卡可先用 `m_nState` + name_note，或保守写 `m_unk_0x58` |
| G2 | `PAL3VisNode` 是否还有 0x5C 之后的成员 | ctor 无、dtor 无 ⇒ 无 | 已闭合，列此仅为留痕 |
| G3 | `ScreenEffectNode` 尺寸 220 vs new 0x424 | 相差 840B | 其 0xA4/0xA8 成员偏移也不可信，需单独取证 |
| G4 | `ScreenEffectNode.m_pTexture@0xA4 / m_pRenderEffect@0xA8` 归属 | 与 B ctor 写点 `[edi+0xA4]/[edi+0xA8]=0` 重合 | 疑错归属；拆类前不要用这两个成员做 B 的布局依据 |
| G5 | `ScreenEffectMgr` 的 `0x4BF680` 方法名 | IDB 名 `GetPageIndex`，体是 `mov [edx+0x58],eax` + 触发 fade | 命名待正名（vtable slot13），不影响尺寸结论 |

## §5 下一张落地卡输入清单（草案，不改数据）

### 卡 A：PAL3VisNode 尺寸与 `+0x58` 字段（最小改动）

- 文件：`data/annotations/structs/PAL3VisNode.json`（`base_size` 语义 = **直接基类 `gbVisNode` 的尺寸**，不是本类尺寸，故保持 88 不动；`pipeline/ida/apply_annotations.py:497` 用 `offset >= base_size` 过滤成员，若误改成 92，新增的 `0x58` 成员会被当基类成员滤掉）
- 改动：
  - `"binary_size": 88` → `92`（本类尺寸）
  - `"base_size"` **保持 88**（直接基类 gbVisNode 的尺寸，实测 88）
  - `known_members` 增加：`"0x58": {"name": "m_nState", "type": "int", "evidence_level": "B", "source": "A: ctor 0x4B6F7F 写 0；getter 0x4B7020 读；RenderTargetNode::UpdateParticleEffect 0x4BD903/0x4BD92B 读写 -1；Stop 0x4BD950 比较 -1；SetPathMode 0x4BD997 置 1；ScreenEffectMgr::Render 0x4BF39F 门控；UpdateAnimation 0x4BF509 比较/0x4BF645 清 0；0x4BF686 置入参；宽度 4B，取值域 {0,1,-1}"}`
- 级联（同一提交内必须一起改，否则派生成员会被 `base_size=88` 判成与基类重叠）：三个直接派生的 `base_size` 由 `88` → `92` ——
  `data/annotations/structs/CEffGroupNode.json`、`data/annotations/structs/UI3DModelNode.json`、`data/annotations/structs/ScreenEffectNode.json`（三者实测当前均为 88）。
  这正是 `tools/cascade_plan.py:236` 的 `set_base_size` 逻辑（`base_size` 应 = 直接基类的新尺寸）。
  `RenderTargetNode.json` 现状 `bases` 缺失、`base_size` 缺失（导出缺口，§2.2 注），是否补 `bases: [PAL3VisNode@0]` + `base_size: 92` 需在该卡单独评估（补 bases 会改变 IDB/导出面，不在「最小改动」范围）。
- 预期：`sizeof(PAL3VisNode)=92`；`gbVisNode`(88) 不变；级联三件 sizeof 不变（CEffGroupNode 116 / UI3DModelNode 248 / ScreenEffectNode 220），其 `base_size` 变 92。`RenderTargetNode`(96) 不在级联内（bases/base_size 缺失，另卡评估）。
- 验收命令（只读闸口，不跑全链）：
  1. `python tools/audit_type_layout.py --only PAL3VisNode --only CEffGroupNode --only UI3DModelNode --only RenderTargetNode`
  2. `python -m pytest tests/ -k "layout or struct" -q`（若存在对应测试）
  3. 复跑本文件 C1–C6，确认 C1 首成员偏移 92 仍成立、C6 `0x454` 闭合仍 `True`
- 回滚：4 个 json 各 1–2 行，`git checkout -- data/annotations/structs/{PAL3VisNode,CEffGroupNode,UI3DModelNode,ScreenEffectNode}.json`。

### 卡 B：ScreenEffectMgr 拆类（依赖卡 A）

- 文件：`data/annotations/structs/ScreenEffectMgr.json`（+ 新增 A 侧类的注解）
- 改动要点：`bases: [{"name":"PAL3VisNode","offset":0}]`、`base_size: 92`；删 `0x4..0x94` 的 A 侧成员；B 保留/新增 `0x5C float m_fTime`、`0xA4`、`0xA8`、`0xB0/0x248` 两段、`0x3E0` 4×0xC、`0x424`、`0x444`、`0x454 ParticleEffect`。
- 预期：B `sizeof` 仍 363968；`0x454+362860=363968`；A 侧 `sizeof ≥ 0x98`（A 自身尺寸定谳属另一缺口）。
- 验收命令：卡 A 的三条 + `python tools/audit_type_layout.py --only ScreenEffectMgr` + `python pipeline/cli.py match`（L1 不降，按三限定口径读 `[metric]`）。

### 卡 C（可选）：`ScreenEffectNode` 尺寸与 0xA4/0xA8 归属

- 输入：`0x4B715A push 0x424`、ctor `0x4B7C30` 的 12×0x44 循环止于 `0x420`、注解 220。
- 目标：定 1060 与成员表；顺带裁定 `m_pTexture/m_pRenderEffect` 是否属 B。

## §6 复现命令与实测输出

```bash
cd /home/peng/workspace/PAL3Decomp
```

### C1 注解/IDB 尺寸与派生首成员偏移

```bash
python3 - <<'PY'
import json
s=json.load(open('asm/pal3/ida_structs.json'))
for cls in ['gbVisNode','PAL3VisNode','CEffGroupNode','UI3DModelNode','RenderTargetNode','ScreenEffectNode']:
    v=s[cls]; ms=v.get('data_members') or []
    print(cls,'size',v['size'],'bases',[b['name'] for b in (v.get('bases') or [])],
          'first_own_offset',(min(m['offset'] for m in ms) if ms else None))
a=json.load(open('data/annotations/structs/PAL3VisNode.json'))
print('annotation PAL3VisNode binary_size',a['binary_size'],'base_size',a.get('base_size'),'known_members',a['known_members'])
PY
```

实测：

```
gbVisNode size 88 bases ['gbNBTreeNode'] first_own_offset 28
PAL3VisNode size 88 bases ['gbVisNode'] first_own_offset None
CEffGroupNode size 116 bases ['PAL3VisNode'] first_own_offset 92
UI3DModelNode size 248 bases ['PAL3VisNode'] first_own_offset 92
RenderTargetNode size 96 bases [] first_own_offset 0
ScreenEffectNode size 220 bases ['PAL3VisNode'] first_own_offset 164
annotation PAL3VisNode binary_size 88 base_size 88 known_members {}
```

### C2 ctor 的 `+0x58` 写、getter 读、getter 调用点

```bash
grep -nE '^\s*4b6f7f:|^\s*4b7020:|call\s+0x4b7020' data/status/_disasm_cache.txt
```

实测：

```
55566:  42b21a:	e8 01 be 08 00       	call   0x4b7020
230666:  4b6f7f:	c7 46 58 00 00 00 00 	mov    DWORD PTR [esi+0x58],0x0
230721:  4b7020:	8b 41 58             	mov    eax,DWORD PTR [ecx+0x58]
```

### C3 三个派生 ctor 在 `0x5C` 写自有首成员

```bash
grep -nE '^\s*4b72f3:|^\s*4b74c6:|^\s*4bd83e:' data/status/_disasm_cache.txt
```

实测：

```
230998:  4b72f3:	89 46 5c             	mov    DWORD PTR [esi+0x5c],eax
231202:  4b74c6:	89 56 5c             	mov    DWORD PTR [esi+0x5c],edx
239295:  4bd83e:	c7 46 5c 00 00 00 00 	mov    DWORD PTR [esi+0x5c],0x0
```

### C4 `operator new` 立即数 → 紧随的类 ctor（sizeof 算术）

```bash
python3 - <<'PY'
import re
lines=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().splitlines()
recs=[]
for l in lines:
    m=re.match(r'^\s*([0-9a-fA-F]{6,8}):\t(.*)$',l)
    if m: recs.append((int(m.group(1),16),m.group(2).split('\t')[-1].strip()))
for i,(a,t) in enumerate(recs):
    if 0x4b7000<=a<0x4b7250 and t.startswith('call') and '0x55353b' in t:
        prev=recs[i-1]
        nxt=next(((a2,t2) for a2,t2 in recs[i+1:i+40]
                  if t2.startswith('call') and re.search(r'call\s+0x4b[0-9a-f]{4}\b',t2)), None)
        print(f'{prev[0]:08x} {prev[1]}  ->  new  ->  {nxt[1] if nxt else None}')
PY
```

实测：

```
004b70eb push   0x60  ->  new  ->  call   0x4bd830
004b7121 push   0x58dc0  ->  new  ->  call   0x4bee60
004b715a push   0x424  ->  new  ->  call   0x4b7c30
004b718f push   0xf8  ->  new  ->  call   0x4b74a0
004b71c4 push   0x74  ->  new  ->  call   0x4b72e0
```

### C5 家族范围内 `+0x58` 访问全表（含需排除项）

```bash
python3 - <<'PY'
import re
lines=open('data/status/_disasm_cache.txt',encoding='utf-8',errors='replace').read().splitlines()
recs=[]
for l in lines:
    m=re.match(r'^\s*([0-9a-fA-F]{6,8}):\t(.*)$',l)
    if m: recs.append((int(m.group(1),16),m.group(2)))
for a,t in recs:
    ins=t.split('\t')[-1].strip()
    if 0x4b6f70<=a<0x4bfa00 and re.search(r'\[e[a-z]{2}\+0x58\]',ins):
        print(f'{a:08x} {ins}')
PY
```

实测（20 行，其中归属本族的 11 行见 §1.1，其余 9 行为 §1.2 的排除项）：

```
004b6f7f mov    DWORD PTR [esi+0x58],0x0
004b7020 mov    eax,DWORD PTR [ecx+0x58]
004b77bc fstp   DWORD PTR [esp+0x58]
004b78ea fstp   DWORD PTR [esp+0x58]
004b87ce lea    edi,[edx+0x58]
004b88b1 fst    DWORD PTR [ebx+0x58]
004ba242 fst    DWORD PTR [ecx+0x58]
004baecf lea    eax,[ebx+0x58]
004bb00c lea    edi,[ebx+0x58]
004bd903 mov    eax,DWORD PTR [esi+0x58]
004bd92b mov    DWORD PTR [esi+0x58],0xffffffff
004bd950 cmp    DWORD PTR [ecx+0x58],0xffffffff
004bd997 mov    DWORD PTR [ecx+0x58],0x1
004bdbbd call   DWORD PTR [edx+0x58]
004bde08 mov    eax,DWORD PTR [esi+0x58]
004bf39f cmp    DWORD PTR [esi+0x58],0x1
004bf509 cmp    DWORD PTR [edi+0x58],ebx
004bf645 mov    DWORD PTR [edi+0x58],0x0
004bf686 mov    DWORD PTR [edx+0x58],eax
004bf7e7 mov    ecx,DWORD PTR [esp+0x58]
```

### C6 `ScreenEffectMgr` 注解基类现状 + B 的 `0x5C` float

```bash
python3 - <<'PY'
import json
j=json.load(open('data/annotations/structs/ScreenEffectMgr.json'))
print('bases',j.get('bases'),'base_size',j.get('base_size'),'binary_size',j['binary_size'])
PY
grep -nE '^\s*4bf506:|^\s*4bf50c:|^\s*4bf39f:' data/status/_disasm_cache.txt
python3 -c "print(0x454+362860, hex(0x454+362860), 0x454+362860==363968)"
```

实测：

```
bases None base_size None binary_size 363968
241884:  4bf39f:	83 7e 58 01          	cmp    DWORD PTR [esi+0x58],0x1
241982:  4bf506:	d8 47 5c             	fadd   DWORD PTR [edi+0x5c]
241984:  4bf50c:	d9 5f 5c             	fstp   DWORD PTR [edi+0x5c]
363968 0x58dc0 True
```

## §7 自检

| QA 项 | 结论 | 证据 |
|---|---|---|
| 访问点有 VA/指令且与 IDB/反汇编对得上 | ✅ | §1.1 十一行全部给出 VA + 原始字节 + 指令，C2/C5 可逐行复现；函数归属取 IDB methods 表（RenderTargetNode 四方法、ScreenEffectMgr 两方法） |
| 候选值有算术或 new/邻类边界证据并给取舍 | ✅ | §2.1 下界、§2.2 上界、§2.3 new 立即数×sizeof 闭合；候选 0x58/0x5C/0x60 的取舍写在 §0.1/§2.4（0x58 与 IDB 自身成员偏移 92 矛盾；0x60 与三派生首成员 0x5C 矛盾） |
| 明确回答是否影响拆类与 0x454 闭合、无证据写缺口不用「可能」 | ✅ | §3.1 基类边界、§3.2 闭合不变、§3.3 注解缺 bases（实测 None）；无法定论的两项进 §4.2 G3/G4 缺口表，未用「可能」作结论 |
| 只新增该文档、不改 data/annotations/pal3/src/pipeline/基线、不跑全链 | ✅ | 本卡只写本文件；未执行 apply/export/codegen/probe/match；`git status` 见下 |

### 只读边界（实测）

```bash
git status --porcelain data/annotations asm/pal3 docs/specs/2026-11-26-pal3visnode-size-evidence.md
```

本文件为新增（`??`）；`asm/pal3/` 无改动。`data/annotations/` 下有三处他人改动：`RoleStatePanel.json`、`UIFrameContainer.json`（#8 写域）与 `ScreenEffectMgr.json`（+60 行，补 0xa4/0xa8/0xb0/0x248/0x3e0/0x424 成员，见 §3.3 补充）——本卡均未触碰。
