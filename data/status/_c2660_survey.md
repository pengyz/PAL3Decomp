# C2660 亚族调研（只读）

- 日期：2026-09-18
- 范围：`data/status/probe_census.json` → `s2.results`
- 总量：**C2660 = 418 条 / 77 个编译单元**；其中 **8 个单元除 C2660 外无其它错误码**
- 本次未运行 `match`、未运行 `codegen all`、未改动任何仓库文件（唯一写入 = 本报告）

---

## 0. 方法与证据源（先说清可信度）

| 证据 | 来源 | 用法 | 等级 |
|---|---|---|---|
| 真实栈参数字节数 `retn N` | `original/PAL3.exe.asm`（IDA 列表，逐函数 `proc near … endp` 取全部 `retn`，要求一致） | `slots = N/4`（`__thiscall`：ecx=this 不计入） | **A（指令级）** |
| DLL 侧真实原型 | `original/gbengine.dll.asm` 的 `; <ret> <conv> Cls::M(params)` 注释行 | 参数个数 + 调用约定 | **A** |
| DLL 侧 `retn N` | 自写 PE 导出表解析（`original/topo.dll`、`original/gbengine.dll` 的 export RVA）＋按「下一个导出 RVA」界定函数体取尾部 `retn` | `slots` | **B**（抽样对 IDA 原型验证 525 通过 / 21 不一致 / 32 为 cdecl；个别需人工复核） |
| 编译器 mangled name | `gbengine/gbengine.def`、`topo/topo.def` | `PAU`=指针 `AAU`=引用 `W4`=枚举；`@@QAEX…@Z` 可直接数参数 | **A** |
| 生成头里的**被编译声明** | `pal3/src/**/*.h`（codegen 产物） | `D` = 声明参数个数 | **A（就是编译器看到的那个）** |
| 调用点形态 | 生成 `.cpp` 原文（418/418 全部逐行解析成功） | 显式 this / 成员限定调用 / 参数个数 | **A** |
| Hex-Rays 原始输出 | `asm/pal3/decomp/*.json` 的 `decompiled_c` | 判断"错在 decomp 还是 codegen" | **A** |
| 调用点实参 push 数 | `original/PAL3.exe.asm` 调用点前后 6 行 | 佐证真实实参个数 | **A** |
| codegen 实际用的门槛值 | 直接 `import ast_transform; _ret_param_slots(cls,method)` | 复现 codegen 的判定 | **A** |

**已确认的两个测量陷阱（本报告已规避）**

1. `sig_evidence.py` 的 `RET_RE` 把 `h` 后缀**排除在捕获组之外**：
   `r'^(?:retn|ret)(?:\s+([0-9A-Fa-f]+)h?)?\s*$'` → 对 `retn 0Ch` 得 `rest='0C'` → `int('0C',10)` 抛错（`C-DISASM-ERR`）；对 `retn 20h` 得 `rest='20'` → **按十进制读到 20（真值 32）**，`slots` 静默偏小。
   实测影响：`_sig_evidence_pack.json` 337 条带 `slots` 中，9 条 `C-DISASM-ERR`、3 条覆盖成错误值（`CCBStage::GetRoleName` 8→5、`CCBSystem::FindFreeThread` 10→7、`CCCTData::CalcDist` 8→5）。
2. `_load_ret_slots()` 的裸字节扫描 `ret_n_at`（向前 0x600 字节找第一个 `0xC2/0xC3`）会把函数体内的**提前 return** 当成函数尾。
   实测：`RoleSystem::RecalcAggregatedStats`（真值 `retn 4`→1 槽）被读成 `+695` 处的 `0xC2 40 00`→**16 槽**；`Array::InsertBlocks`（真值 `retn 0Ch`→3 槽）被读成 `+274` 处的 `0xC3`→**0 槽**。
   这两个错误值直接造成 `SwordUI.cpp`、`TextureLib.cpp` 各自唯一的 C2660（见 §2）。

**口径纪律**：15 个 C1003 截断单元中有 **11 个**带 C2660（`PAL3.cpp`、`free_functions.cpp`、`PalScript.cpp`、`CCBSystem.cpp`、`CCBUI.cpp`、`CScreenMode.cpp`、`RoleSystem.cpp`、`SceneObj.cpp`、`UIScenePanel.cpp`、`CEffCylinder.cpp`、`CEffgbParticle.cpp`）。这 11 个文件的 C2660 条数只是**窗口下界**，不得用于"逐码增减"或"某族是否灭净"的判断。"只被 C2660 卡住"的判断一律用 `errors` 里 code 的**集合**（本报告 8 个文件即如此得出）。

---

## 1. C2660 亚族分解（按被调函数名聚类，前 12 族）

`N` = 调用点实参个数；`D` = 生成头里被编译的声明参数个数；`S` = 二进制真值栈参数个数（`retn N/4`）；`gate` = codegen 实际用于显式-this 改写门的 `_ret_param_slots` 值。

| # | 亚族（被调方） | 形态 | 条数 | 文件数 | N / D / S / gate | 这条 msg 说的是哪种情形 | 归因层 |
|---|---|---|---|---|---|---|---|
| 1 | `gbVFileSystem::Read` | 成员限定 | **33** | 8 | 0 / 3 / 3 / 3 | **Hex-Rays 把 3 个实参全丢了**：decomp 渲染成 `gbVFileSystem::Read(g_pVFileSys)`（`this` 也算在里面），codegen 再把 `g_pVFileSys` 当 this 吞掉 → 0 参。DLL 真值 3 参（`?Read@gbVFileSystem@@QAEXPAXIPAVgbVFile@@@Z`，`retn 0Ch`） | IDB/annotation（DLL 原型未落到 exe 侧 IDB） |
| 2 | `gbVec3D::operator=` | 显式 this | **27** | 11 | 2 / 1 / 1 / **None** | 声明正确（`include/topo_api.h:101` 1 参）、二进制正确（`??4gbVec3D@@QAEXABU0@@Z` `retn 4`），**只是 gate 拿不到槽位数**（gbVec3D 在 topo.dll，`_load_ret_slots` 只读 PAL3.exe）→ 显式 this 形态被保留 → 2 参 vs 1 参 | codegen 证据面 |
| 3 | `CCBControl::SetParam` | 显式 this | **17** | 6 | 3 / 2 / 3 / 3 | **原型少 1 个参数使 Hex-Rays 丢 1 个实参**。真值 `retn 0Ch` = 3 栈参 + ecx=this；调用点 `push 0 / push ebx / push edi / mov ecx,[eax+8]`（`sub_5195E0:loc_51964A`）确证 3 实参，而 decomp 只渲染 `SetParam(thisptr, a2, a3)`（丢 1 个）→ gate 要求 `S == N-1`（3≠2）→ 不放行 | annotation（补第 3 个参数） |
| 4 | `gbDynVertBuf::RenderGeomQuad` | 成员限定 | **15** | 9 | 3 / 4 / 4 / 4 | **codegen 把第 1 个实参当 this 吞掉**。decomp 本来是 `gbDynVertBuf::RenderGeomQuad((gbGeomQuad*)(v16+7216), v18, effect, tex)` 4 参（C3DSpark）、`(this->m_ShadowQuad, v18, …)`（CCBStageShadow），第一个实参类型是 `gbGeomQuad*` 而**不是** `gbDynVertBuf*`；DLL 真值 4 参（`retn 16`） | codegen |
| 5 | `PAL_GDB::~PAL_GDB` | 成员限定 | **14** | 4 | 1 / 0 / 1 / None | **scalar-deleting 析构函数的 `int` 参数没标注**。`0x00478FD0` `retn 4`×2 = 1 栈参；调用点 `~PAL_GDB((PAL_GDB*)&g_pGDB, x)` 2 参；生成头声明 `~PAL_GDB()` 0 参 | annotation |
| 6 | `UIScene::ProcessInput` | 成员限定 | **11** | 4 | 1 / 2 / cdecl / 0 | **codegen 把 static 成员的实参当 this 吞掉**。生成头 `static BOOL ProcessInput(char*, char*)`；decomp `UIScene::ProcessInput(aM22, 0)` 本来就 2 参可编译；codegen 输出 `(((UIScene*)"M22"))->UIScene::ProcessInput(0)` ——第 1 个实参（字符串字面量）被当成 `this` | codegen |
| 7 | `CCBStage::GetRoleName` | 显式 this | **10** | 1 | 9 / 8 / 8 / **5** | 声明对（8 参）、真值对（`retn 20h`=32=8 槽，函数体 `arg_0..arg_1C` 8 个），**gate 值被 pack 用十进制误读成 5** → 不放行 | codegen 证据面 |
| 8 | `VideoPlayer::SetRegion` | 成员限定 | **10** | 1 | 1 / 2 / cdecl / 0 | 同 #6：`static void SetRegion(int nX, int nY)`，decomp 2 参被吞成 1 参 | codegen |
| 9 | `::ShowWindow`（Win32） | 显式调用 | **9** | 2 | 2 / — / — / — | **名字遮蔽**：`CCBStage.h:395 void ShowWindow();`（`CCBUI`/`CCBStage` 成员）遮蔽全局 `::ShowWindow(HWND,int)`，类内无限定调用解析到成员 → "does not take 2" | codegen（补 `::` 限定） |
| 10 | `ScriptVM::GetObjectByID` | 成员限定 | **9** | 1 | 0 / 1 / cdecl / 0 | 同 #6（`int __cdecl(int nObjID)` → `static int GetObjectByID(int)`） | codegen |
| 11 | `Array::Copy` | 成员限定 | **8** | 4 | 0 / 1 / cdecl(2 实参) / 0 | 同 #6，**且叠加 annotation 少参**：`sub_411240` 是 cdecl **2** 参（`arg_0`/`arg_4` 都被读写、裸 `retn`、调用点 `push ebp; push edi`），声明是 `static void* Copy(void* dst)` 1 参 | codegen（+ annotation） |
| 12 | `std::string::_Eos` | 成员限定 | **8** | 4 | 0 / 1 / 1 / None | **同一机制**：二进制 `?_Eos@…AAEXI@Z`（1 参 `I`），decomp 渲染 `std::string::_Eos(v6)`（`this` 独占，size 实参被丢），codegen 再吞成 0 参 | IDB/annotation（STL 内部签名） |
| 13 | `gbVec3D::operator+=` | 显式 this | **8** | 2 | 2 / 1 / 1 / **None** | 同 #2（`??YgbVec3D@@QAEXABU0@@Z` `retn 4`） | codegen 证据面 |
| 14 | `InputSystem::ProcessFrame` | 成员限定 | **8** | 4 | 0 / 1 / cdecl / 0 | 同 #6（`void __cdecl InputSystem::ProcessFrame(char*)`） | codegen |
| 15 | `CreateFromMemory` | 成员限定 | **12** | 5 | 1–2 / 6 / 6 / None | **vtable「命名形」调用 + 原型不全**：decomp 里是 `obj->__vftable->CreateFromMemory(...)`，IDB 对该槽的 DLL 原型不完整（真值 `?CreateFromMemory@gbTexture_D3D@@UAEXHHW4…@Z` 6 参 `retn 24`）→ 只渲染出 1~2 个实参 | IDB/annotation（DLL 虚函数原型） |
| 16 | `NewIndexPool` / `NewMesh` | 成员限定 | **14 / 6** | 4 / 2 | 0–2 / 3 或 2 / — / None | **vtable 槽位换算 4× 缩放错误**（见 §1.1） | codegen |

其余较长尾：`gbMatrix4::RotateIn` 5、`UIItem::SetData` 5、`Logger::Write` 5、`Camera::CheckCollision2` 5、`gbMatrix4::Rotate` 4、`Array::Insert` 4、`Array::Erase` 3、`UIScene::GetChildCount/GetChildAt/SetTextParam` 各 3、`CCBSystem::GetCmdData` 3、`Role::Calc*Init` 各 3、`PtrArray::CopyRange` 3。

### 1.1 vtable 槽位换算 4× 缩放错误（A 级证据）

`pipeline/gen/stages/stage3_cleanup.py:_resolve_vtbl_method`：

```python
if d['offset'] is not None and d['cls_hint']:
    slots = sv.get(d['cls_hint'], {})
    if d['cls_hint'] in sv:
        return slots.get(d['offset'] // 4)      # ← 除以 4
```

但 Hex-Rays 的 `__vftable + N` 里 **N 已经是槽位下标**（cast 把 `__vftable` 变成 4 字节元素指针，指针算术按元素计）。二进制核对：

| Pal3 函数 | 真实指令 | 字节偏移 | 真实槽位 | decomp 文本 | 4× 后的查表键 | 生成的名字 |
|---|---|---|---|---|---|---|
| `PAL3::Render` | `call dword ptr [eax+30h]` | 48 | **12 BeginScene** | `__vftable + 12` | 3 | `NewMesh()` ✗ |
| `PAL3::Render` | `call dword ptr [edx+34h]` | 52 | **13 Present** | `__vftable + 13` | 3 | `NewMesh()` ✗ |
| `PAL3::PrintScreen` | `call dword ptr [eax+54h]` | 84 | **21 CreateDepthStencil** | `__vftable + 21` | 5 | `NewIndexPool(&v24,1)` ✗ |
| `PAL3::PrintScreen` | `call dword ptr [eax+58h]` | 88 | **22 RestoreDepthStencil** | `__vftable + 22` | 5 | `NewIndexPool()` ✗ |

槽位真名取自 `include/gbengine/gbGfxManager.h`（"Vtable: 29 slots (verified from binary)"）。`data/annotations/structs/gbGfxManager.json` 只标了 7 个槽（0–6），所以 12/13/21/22 被 `//4` 折叠成 3/5——**落在已标注范围内，产出一个"看起来对"的错名字，而不是走 stub 分支**。

---

## 2. 8 个「只被 C2660 卡住」的文件

| 文件 | C2660 | 具体函数 | 被调方 | 判定机制 | 最小修复层 | 证据等级 |
|---|---|---|---|---|---|---|
| `Misc/CCBFiveNimbusWindow.cpp` | 6 | `OnMessage(int,int,int)` L272/285/296/309/315/328、`HandleInput` L296 | `CCBControl::SetParam` | 原型少 1 参 → Hex-Rays 丢 1 实参（族 #3） | **annotation**（`int __thiscall(int,int)` → `(int,int,int)`） | **A**：`retn 0Ch` + 调用点 3 次 `push` |
| `Combat/CCBStageShadow.cpp` | 2 | `Create()` L114 / `Render()` L232 | `gbMatrix4::operator=`；`gbDynVertBuf::RenderGeomQuad` | L114 = 族 #2（gate 无槽位）；L232 = 族 #4（首参 `this->m_ShadowQuad` 是 `gbGeomQuad*` 被当 this） | **两者**：L114 走 codegen 证据面；L232 走 codegen（把 ret-N/类型门推广到该分支） | **A**（L114：topo/gbengine `retn 4` + `.def` 1 参；L232：DLL 原型 4 参 + `retn 16`） |
| `Effect/C3DSpark.cpp` | 1 | `Render(gbVec3D*)` L380 | `gbDynVertBuf::RenderGeomQuad` | 族 #4 | **codegen** | **A**：decomp 4 实参 `(gbGeomQuad*)(v16+7216), v18, effect, tex`；生成物只剩 3 参 |
| `Misc/Comp_DonateUI.cpp` | 1 | `ProcessInput(int)` L42 | `NPC::UpdateAnim` | 声明 0 参 / 真值 1 槽（`sub_446020` `retn 4`，`arg_0` 被读）→ annotation 的 `void __thiscall(NPC *this)` 把唯一真参数写成了 this 标记 → 实际调用 1 参 | **annotation**（签名补 `int`） | **A**：`retn 4` + `arg_0` 被读 |
| `Misc/SwordUI.cpp` | 1 | `RenderSword()` L218 | `RoleSystem::RecalcAggregatedStats` | 形态完全正确（N=2、S=1、2=1+1），**gate 值被裸字节扫描误读为 16** → 不放行 | **codegen 证据面**（改用指令级真值） | **A**：`sub_40BE80` 唯一 `retn 4`；误读点在函数体内 +695 |
| `Render/TextureLib.cpp` | 1 | `InsertBlocks(char*,uint,int*)` L173 | `Array::InsertBlocks` | 形态正确（N=4、S=3），**gate 值被误读为 0**（函数体内 +274 的提前 `ret`）；pack 侧同族还因 `0Ch` 解析崩溃而缺席 | **codegen 证据面** | **A**：`sub_4AF450` 4 处 `retn 0Ch`；误读点 +274 |
| `Role/Role.cpp` | 1 | L180 | `gbOBBox::GetAABBox` | 族 #2 同型：`gbOBBox` 在 DLL，gate 拿不到槽位（None）；形态正确（N=2、S=1） | **codegen 证据面**（补 DLL 槽位） | **A**：`?GetAABBox@gbOBBox@@QAEXAAUgbAABBox@@@Z` + `retn 4` |
| `Scene/Scene.cpp` | 1 | `AddRoleEntry(int[3])` L143 | `Array::Copy` | 族 #6：`Array::Copy` 是 `static`（`static void* Copy(void*)`），decomp 是 `Array::Copy(i)`（1 参，**本来就能编译**），codegen 因 `static_methods` 门失效把它改写成 `((Array*)i)->Array::Copy()` → 0 参 | **codegen** | **A**：`sub_411240` 是 cdecl 2 参（`arg_0`/`arg_4`、裸 `retn`、调用点 2 次 `push`）+ 头里 `static` 关键字 |

> 注意：8 个文件的解锁**不是互相独立的**。`CCBStageShadow.cpp`、`C3DSpark.cpp` 共享族 #4；`Role.cpp`/`SwordUI.cpp`/`TextureLib.cpp` 共享"补 gate 证据值"这一类改动。因此"修一族就 +8 文件"的说法**不成立**——按最小独立改动切分是 **6 类改动解锁 8 个文件**。

### 2.1 阻塞这些文件的 codegen 侧缺陷（A 级）

**(a) `static_methods` 守卫是死代码** → 影响 **118 条 / 44 簇 / 20 个文件**

- `pipeline/gen/data.py:336`：`self.static_methods.add(_name)`，而 `_name` 来自 decomp JSON 的 `name` 字段，形如 `'Array::Copy(void *)'`、`'UIScene::ProcessInput(char *,char *)'`（**带参数表**）。全库 3162 个 decomp name 里 3139 个带括号。
- `pipeline/gen/ast_transform.py:447`：`qualified = '%s::%s' % (class_name, method_name)` 形如 `'Array::Copy'`（**不带括号**）→ `qualified in static_methods` **恒为假**。
- 后果：`__cdecl`（static）成员的调用被当成成员调用重写，第 1 个实参（数据）被当作 `this` 丢弃。
- 铁证链（`UIScene::ProcessInput`，11 条）：头 `static BOOL ProcessInput(char*, char*)`（2 参）→ decomp `UIScene::ProcessInput(aM22, 0)`（2 参，可编译）→ 生成 `(((UIScene *)"M22"))->UIScene::ProcessInput(0)`（1 参）→ C2660。

**(b) 首参当 this 的改写只在 `pointer_expression` 分支有证据门** → 影响 **29 条 / 18 个文件**（不含 (a) 的部分）

同一个"显式 this → 成员调用"改写，`ast_transform.py` 在 `pointer_expression` 分支（L744-780）要求 `_ret_param_slots(cls,m) == len(args)-1` 才改写，但在 `cast_expression`（L615-728）、`field_expression`、`identifier` 等分支**没有这个门**，一律把首参当 this。族 #4（`RenderGeomQuad`，15 条）就是这个分支漏掉的典型：首参类型是 `gbGeomQuad*`，与 `gbDynVertBuf` 无关。

**(c) `_drop_self_arg` 只剥离 `(Type*)` 形式** → 影响 `ShowWindow` 成员限定形 5 条（`this->m_nTodo_07C->ShowWindow(&this->m_nTodo_07C, 0)`），`(int)this` 之类不含 `*` 的 cast 不被识别为 self 实参。**证据等级 C**（这 5 条的 decomp 原文未逐条定位到，判为证据不足）。

**(d) `_resolve_vtbl_method` 的 `//4`** → 影响 `NewIndexPool` 14 + `NewMesh` 6 + `NewDynVertBuf` 1（≥21 条 / 6 个文件），见 §1.1。

---

## 3. ROI 排序（解锁文件数 / 风险）

排序口径：**解锁的"只被 C2660 卡住"文件数**（硬收益）＋ **解锁的 C2660 条数**（回归面收敛）÷ **改动风险**（是否动语义 / 是否需二进制新证据 / 单点 blast radius）。

| 排名 | 改动 | 直接解锁的 8 文件中 | 涉及 C2660 条数 / 簇 | 风险 | 依据 |
|---|---|---|---|---|---|
| **1** | 修 `static_methods` 成员判定（去掉参数表后缀 / 改存 `Cls::M`） | **1**（`Scene.cpp`） | **118 / 44**（含 `PalScript.cpp` 26、`free_functions.cpp` 30、`Actor.cpp` 20、`PtrArray.cpp` 15、`PAL3.cpp` 中的一部分） | **低**：纯"少改一次"——让已经正确的 decomp 文本原样通过；不改任何类型/签名；可用 `pipeline/gen/test_pipeline.py`（已有 `static_methods={'Foo::StaticMethod'}` 用例）验证 | `data.py:336` vs `ast_transform.py:447`；`UIScene.h:70 static`；decomp 2 参 vs 生成 1 参 |
| **2** | 把 gate 的证据来源从"裸字节扫描"改为指令级真值（并修 `RET_RE` 的 `h` 后缀解析） | **2**（`SwordUI.cpp`、`TextureLib.cpp`） | **55 / 27**（其中 30 条形态完全正确的"纯证据问题"） | **中**：只改判定输入，不改判定规则；但 `_load_ret_slots` 是 CLAUDE.md 明文"声明在案"的 C1 架构例外（`ast_transform.py` L30-51），动它需同步更新该声明。单点 blast radius 大（改写面可从 30 条扩到更多），必须用 `regression_detector.py --before/--after` 逐条对账 | `RoleSystem::RecalcAggregatedStats` 16→真 1；`Array::InsertBlocks` 0→真 3；`CCBStage::GetRoleName` 5→真 8 |
| **3** | 给 gate 补 **DLL 侧** `retn` 证据（topo.dll / gbengine.dll） | **1**（`Role.cpp`）＋ 助 `CCBStageShadow.cpp` | **30+ 条**（`gbVec3D::operator=` 27、`+=` 8、`gbMatrix4::RotateIn` 5、`Rotate` 4、`gbOBBox::IsColOBB` 3、`GetAABBox` 2、`gbQuaternion::SetYawPitchRoll` 2、`gbVertPoolMgr::GetDynVertBuf` 2、`gbGeomNode::SetAnimLoop` 1、`CPK::SetOpenMode` 1、`gbImage2D::ScaleTo/WriteJpegImage` 2） | **中低**：证据来自已存在的 `original/topo.dll` + `topo.def`（mangled 可数参）与 `original/gbengine.dll.asm`；`sig_evidence.py` 目前只解析 `addrs=[]` 的类（`C-NOADDR` 76 条） | §1 #2/#13；`include/topo_api.h:101` 1 参 vs 生成调用 2 参 |
| **4** | 修 `_resolve_vtbl_method` 的 `//4` | 0 | **21 / 6** | **中**：修完这些调用会落到 stub 分支（`pal3_vtbl_unk_N`，实现体是 `return 0;`）——**编译过了但语义丢了**，字节不可能匹配。若要既编译又保真，必须同时把 `gbGfxManager_D3D` 的 7–28 槽标进 annotation（`data/annotations/structs/gbGfxManager.json` 现在只有 7 槽） | §1.1 表；`gbGfxManager.h` 29 槽注释 |
| **5** | annotation 补参（`CCBControl::SetParam`、`NPC::UpdateAnim`、`PAL_GDB` scalar dtor、`UIItem::SetData`、`Array::Insert`、`Array::Erase`、`UIStatic::SetText`、`UIScene::GetChildCount/GetChildAt/SetTextParam`、`CCBSystem::GetCmdData`、`CCBStage::EndTurnAndAdvance` …） | **2**（`CCBFiveNimbusWindow.cpp`、`Comp_DonateUI.cpp`） | **59 / 19** | **中**：每一条都必须"从真值反推缺失参数"，不能猜类型；但 `retn 0Ch`/3 次 `push` 这类证据已达 A 级。改动会连带改变被调函数**自身**的 decomp（新增 `nVal3` 的使用），属于双面改动，必须同时看 L1 | `retn 0Ch` + `sub_5195E0:loc_51964A` 3 push；`sub_446020 retn 4` |
| **6** | 把"显式 this 门"推广到 `cast_expression`/`field_expression` 等分支 | **2**（`CCBStageShadow.cpp`、`C3DSpark.cpp`） | **29 / 18** | **中高**：这是改判定**规则**（不是输入），一次可动 100+ 站点；必须有"首参静态类型 == 被调类（或其基类）"的类型证据，或直接用 ret-N 门（`gbDynVertBuf` 的 DLL 真值 4 → 3≠4-1 自然挡掉） | decomp 4 实参 vs 生成 3 参；DLL `retn 16` |
| **7** | Win32 名字遮蔽（`::ShowWindow`） | 0 | **9 / 1** | **中**：需要判断"无限定名解析到的是全局还是成员"。IDB 里该调用目标是 import（`user32`），但 codegen 只看文本。可先用"类内有同名成员且实参个数不匹配"做保守判据 | `CCBStage.h:395 void ShowWindow();`；decomp `ShowWindow(g_hMainWnd, 4)` |

**结论**：ROI 最高的是 **#1（`static_methods` 死守卫）**——118 条 / 44 簇、纯 codegen、零标注风险、并且已有单测护栏。其次是 **#2 / #3 合并成一次"证据面修复"**：它们本质是同一件事（gate 的输入不可信），合起来覆盖 85 条、直接解锁 3 个文件，且能顺带消掉 `CCBSystem.cpp` 的 10 条 `GetRoleName`（该文件另有其它错误码，不直接解锁，但显著减面）。

---

## 4. 不可修 / 不应硬凑的清单

| 类别 | 条目 | 为什么不能在本层修 |
|---|---|---|
| **Hex-Rays 能力上限** | `std::string::_Eos` / `_Split` / `_Xran` / `_Tidy` 等 STL 内部成员 | 这些是 CRT/STL 边界函数，函数体不在 exe 的 IDB 语义范围内；`?_Eos@…AAEXI@Z` 的 1 个 `I` 参数在 decomp 里被完全丢掉（Hex-Rays 只渲染出 `this`）。要修必须把 Dinkumware STL 的私有成员签名写进 IDB，而 CLAUDE.md 明确把"CRT 边界"列为 Phase-1 的核心困难之一。**证据充分但方案不成立**，记录待办 |
| **Hex-Rays 能力上限** | `Copy` / `CreateFromMemory` / `Read` 的"实参被丢" | 同族：当 IDB 原型参数个数少于真实个数时，Hex-Rays **静默丢弃多出来的 push**（`gbVFileSystem::Read` 3 个全丢）。这是 Hex-Rays 的确定行为，不是 codegen 能补的——codegen 看不到被丢掉的实参。唯一正解是 annotation/IDB 补原型。`Read` 的 33 条因此不属于"codegen 可修" |
| **需人工 IDB 调查** | `NewIndexPool` / `NewMesh` / `NewDynVertBuf` 的正确名字 | 真名字要求 `gbGfxManager_D3D` 的槽位 7–28 逐个进 annotation。`gbGfxManager.h` 有名字与 ordinal（`0x10018CD0` 等），但那是 **DLL 侧 VA**，要落到 exe 侧 IDB 的 vtable 结构上需要一次专门的 vtable 归属调查（项目已有 `gotcha_vtables_not_derivable_from_bytes.md` 的教训：vtable 布局不能只从字节推）。仅修 `//4` 会得到语义错误的 stub |
| **需人工 IDB 调查** | `ShowWindow` 名字遮蔽的 9 条 | 需要区分"无限定 `ShowWindow(...)` 指向 user32 import 还是类成员"。文本层无法判定；IDB 层能（调用目标是 import thunk）。在 codegen 层做启发式判断属于"猜"，风险不可控 |
| **证据不足，暂不判定** | `CCBStageShadow.cpp:114` 之外的 `gbMatrix4::operator=` 2 条、`gbImage2D::~gbImage2D` / `gbTexture_D3D::~gbTexture_D3D`（各 1–2 条，STATICLIKE + 析构） | 这些是 DLL 侧 dtor 的显式 this 形态。DLL 侧 `retn` 我用 PE 导出表界定函数体取得（B 级），个别函数落在"下一个导出 RVA"边界之外时不可靠；需要 `topo.dll`/`gbengine.dll` 的 IDA 列表（本仓库只有 `gbengine.dll.asm`，没有 `topo.dll.asm`）才能升到 A 级 |
| **证据不足，暂不判定** | `ResetAll(this)`、`FindFreeThread(this, 10 参)`、`ScriptPoolPage_Alloc((_Console*)this)`、`GetInstance_db10(this)`、`_ftol()` | 这些是"把别的类的成员函数调用渲染成自由函数 + 显式 this"（`[MISATTRIBUTED]` 族）。判它们要同时满足 ret-N 门 **和** vtable 槽位归属（`ast_transform.py` L661-715 的 Track-1 例外），而其中多条连类归属都未定。不能只看 C2660 就改 |
| **测量噪声，不得用于判定** | 11 个 C1003 截断单元里的 C2660 条数 | 列表 = 前 ~100 条 + C1003，属报告窗口位移。任何"这一族修完就少 N 条"的说法在这 11 个文件上都不成立 |

---

## 5. 下一步：3 条具体建议（含证据与风险）

### 建议 1（最高 ROI）：修 `static_methods` 成员判定 —— 死守卫

- **改动**：`pipeline/gen/data.py:329-336` 建 `static_methods` 时只存 `_name.split('(')[0]`（即 `Cls::M`），使 `ast_transform.py:447 / 596 / 620` 的 `qualified in static_methods` 真正命中。
- **证据（A）**：`pal3/src/UI/UIScene.h:70` `static BOOL ProcessInput(char *String1, char *pszBuf);`；decomp `UIScene::ProcessInput(aM22, 0)`（2 实参，本来可编译）；生成物 `(((UIScene *)"M22"))->UIScene::ProcessInput(0)`（1 实参）→ C2660 由 codegen 引入。同型 118 条 / 44 簇 / 20 文件。
- **验证**：`pipeline/gen/test_pipeline.py` 已有 `transform_oop_calls(code, static_methods={'Foo::StaticMethod'})` 用例（L76）——先补一个"带参数表的名字也必须命中"的用例作为护栏，再跑 `regression_detector.py --before/--after` 对账 `(code,msg)` 多重集，剔除 C1003 单元。
- **风险**：低。只让"本来正确的文本原样通过"，不改类型/签名/字节；但会**减少**改写站点，若某处 `__cdecl` 声明本身是错的（annotation 层面），修完会从 C2660 变成别的错误码——这正是诚实信号，不是退化。

### 建议 2：把 gate 的证据输入换成指令级真值（并修 `RET_RE` 的 `h` 后缀）

- **改动**：(i) `tools/sig_evidence.py` 的 `RET_RE` 捕获组改为含 `h`（`([0-9A-Fa-f]+h?)`）并在 `parse_ret_num` 里判后缀——否则 `0Ch` 永远崩溃、`20h` 永远按十进制误读；(ii) `ast_transform._load_ret_slots` 里对"裸字节扫描"结果要求与 pack 的指令级结果一致，不一致时以指令级为准（或直接禁用 `ret_n_at` 的提前 `ret` 命中）。
- **证据（A）**：`RoleSystem::RecalcAggregatedStats`（`0x0040BE80`）：`sub_40BE80` 唯一 `retn 4`（1 槽），裸扫描在 **+695** 处命中函数体内的 `0xC2 40 00` → gate 拿到 **16**；`Array::InsertBlocks`（`0x004AF450`）：`sub_4AF450` 4 处 `retn 0Ch`（3 槽），裸扫描在 **+274** 处命中提前 `ret` → gate 拿到 **0**。两者的调用形态**完全正确**（N = S+1），仅因这两个错值被挡。另 `_sig_evidence_pack.json` 里 `CCBStage::GetRoleName` 被覆盖成 5（真值 8），`CCBSystem::FindFreeThread` 7（真值 10），`CCCTData::CalcDist` 5（真值 8）。
- **收益**：30 条"纯证据问题"里含 3 条 `RoleSystem::RecalcAggregatedStats`（解锁 `SwordUI.cpp`）、1 条 `Array::InsertBlocks`（解锁 `TextureLib.cpp`）、10 条 `CCBStage::GetRoleName`（`CCBSystem.cpp` 减面）。**直接 +2 个 ok 文件。**
- **风险**：中。`_load_ret_slots` 读 annotation + exe 是 CLAUDE.md 红线下的**声明在案例外**（`ast_transform.py` L30-51 与 AR-002 C1）：改它必须同步更新该声明块，并跑全量 `regression_detector --self-test` + `--before/--after`。**另注意**：`_ret_param_slots` 现在只读 `PAL3.exe`，任何"顺带接 DLL"的改动都在扩大这个例外，建议一次只做输入可信化，不做证据源扩张。

### 建议 3：给 gate 补 DLL 侧 `retn`（topo.dll / gbengine.dll），一次性覆盖 30+ 条

- **改动**：`_load_ret_slots`（或 pack 生成器）增加 DLL 证据表：`gbengine.dll.asm` 已有 `; <ret> <conv> Cls::M(params)` 原型注释行可直读参数个数；`topo.dll` 没有 asm，但有 `topo/topo.def`（mangled，`AAU`/`PAU`/`W4` 可数参，A 级）＋ `original/topo.dll` 的 PE 导出表（RVA→函数尾 `retn`，B 级）。优先补这几个高频：`gbVec3D::operator=`(27)、`gbVec3D::operator+=`(8)、`gbMatrix4::RotateIn`(5)/`Rotate`(4)、`gbOBBox::IsColOBB`(3)/`GetAABBox`(2)、`gbQuaternion::SetYawPitchRoll`(2)、`gbVertPoolMgr::GetDynVertBuf`(2)。
- **证据（A/B）**：`include/topo_api.h:101 void __thiscall gbVec3D::operator=(struct gbVec3D const &);`（1 参）＋ `??4gbVec3D@@QAEXABU0@@Z`（`AAU0@`=1 引用参）＋ `retn 4`；调用点 `gbVec3D::operator=(&v21.Direction, ViewTarget)` 显式 this，`&v21.Direction` 的静态类型就是 `gbVec3D*`。`gbOBBox::GetAABBox`：`?GetAABBox@gbOBBox@@QAEXAAUgbAABBox@@@Z` + `retn 4`，调用 `gbOBBox::GetAABBox(pMatrix, &v20.z)`（解锁 `Role.cpp`）。
- **收益**：解锁 `Role.cpp`，并消除 `CCBStageShadow.cpp` 的 L114。
- **风险**：中低（证据本身 A 级），但**实现上有两种路线，风险不同**：
  (a) 走"扩大 `_ret_param_slots` 的证据源"——必须同步更新 CLAUDE.md 的红线声明，且 pack 生成器依赖 IDA MCP（`tools/mcp_query.py`），环境不可用时需走 .def/PE 路线；
  (b) 不走证据源、改走**类型判据**——"首参静态类型 == 被调类（或其基类）⇒ 首参就是 this"，这不需要任何二进制新证据，也能覆盖这 27+8+5+4+3+2+2 条；但它把"证据门"降级成"类型门"，需要先用 §3#6 的方式界定好适用分支，否则会重犯 §1#4 的错。**建议先做 (b) 的小范围原型（只覆盖 `pointer_expression` 分支里的 `&x` 且 `x` 声明类型 == 被调类），用 `regression_detector` 单文件对账后再决定是否扩大。**

---

## 6. 未解决 / 证据不足（诚实清单）

1. `CreateFromMemory` 系 (12 条) 与 `NewIndexPool/NewMesh` (20 条) 的**正确名字**未定：需要 `gbGfxManager_D3D` / `gbTexture_D3D` 的完整 vtable 归属调查。只知道当前名字是错的（§1.1）。
2. `ShowWindow` 成员限定形 5 条的 decomp 原文未逐条定位（`_drop_self_arg` 假说为 **C 级**），需要先在 `asm/pal3/decomp/` 里定位 `m_nTodo_07C` / `m_ani.m_pfather` 对应的实际表达式。
3. `PAL_GDB::~PAL_GDB`（14 条）：`retn 4` 足以说明有 1 个 `int` 栈参（scalar dtor），但**参数语义**（是 `unsigned int flags` 还是别的）未从二进制确认——`sub_478FD0` 的函数体我没有逐指令读完，只读了 `retn`。补参前必须确认。
4. `Array::Copy` 的第二个参数（`arg_4`，`const void* src`）类型是我从 `mov ecx,[esp+arg_4]; mov edx,[ecx]…` 推断的"指针"，属 **B 级**；annotation 若要补，先做一次逐指令确认。
5. `gbMatrix4::operator=` / `gbImage2D::~gbImage2D` / `gbTexture_D3D::~gbTexture_D3D` 的 DLL `retn` 是 PE 导出表界定得来的 **B 级**证据，需 `topo.dll.asm` / 逐指令复核才能升 A。
6. `Z-未定` 桶里剩下约 50 条（`ResetAll`、`FindFreeThread`、`_ftol`、`ScriptPoolPage_Alloc`、`GetInstance_db10` 等）单条站点，**类归属与真值都未定**，本报告不给结论。它们的共同形态是"别的类的成员函数被渲染成自由函数 + 显式 this"，属于 `[MISATTRIBUTED]`（Track-1 双轨）族，需要 vtable 槽位归属 + ret-N 双证据才能动。