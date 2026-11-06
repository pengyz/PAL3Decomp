# B面战役进展 2026-11-06 Session 2（接 progress_handoff_20261106.md 第七节 1/2/3 全做）

## 一、战果总览（build43 → build54）

| 指标 | build43（交接时） | build54（本 session） |
|---|---|---|
| 总错误 | 203 | 203（**错误构成换了新的一层**） |
| _unnamespaced.cpp 截断点 | 7336 | **7796（+460 行深体解锁）** |
| .h 层错误 | 有（C2061/C2371 族涌现后清零） | **0** |
| C2039（Type::method 族） | 17 | **2** |
| h/i/j 违例 | 3 处未取证选边 | **3 处全 A 级证据落注释** |
| nsfix（Type::method 解析器） | 无 | 829 签名/1446 调用点/48 类声明/幂等 |

轨迹：43(203)→44(408,nsfix自坑:marker裸文本)→45(408)→46(408,fwd不可见)→47(176)→48(122)
→49(122,pragma位)→50(20)→51(203*,backref)→52(237,链序)→53(312,pass0过贪)→**54(203 稳定)**。
*51/54 同为 203 但构成不同：51 后 emit_missing 重跑暴露 defs 缺口，54 为全链收敛稳态。

## 二、纠正三修（质询承诺兑现·全部 A 级取证）

### h) TryExpand 3vs5 → **5 参对**（原选边正确，升级为 A 级）
- `0x4012c1: ret 0x14` = 被调方清栈 20B = **5 个栈参数**（__thiscall：`0x4012ae mov edi,ecx` this 从 ECX）
- `0x4012a4 mov ebp,[esp+0x18]`=param_4、`0x4012a9 mov esi,[esp+0x18]`=param_5 —— 函数体实际消费
- 字节回访账更新：**声明渲染为自由函数（this 作第一实参 __cdecl 形态），二进制是 __thiscall（ECX）——链接层 ABI 项**

### i) FUN_004014b0 void vs 赋值 → **int 返回对**（补真 return 非假 return）
- `0x4014b3: eax=[edx+0x3c]`（链头节点），**全路径 eax 无覆盖**（后续写内存/写 ecx）
- 空链路径 `0x4014ba: ret`（eax=0，刚被 test）／尾路径 `0x4014d2: ret`（eax=链头）
- 调用点 `while (iVar3 && *(int*)(iVar3+0x14)…)` 作节点指针消费 ✓
- 落地：`return 0;`（空链路径）+ `return iVar1;`（尾路径）—— eax 数据流直接推导，注释在案
- 关联记账：函数体 `int in_ECX;` 幽灵变量 = __thiscall this（ECX）被 Ghidra 渲染成未初始化局部——**__thiscall 剥欠账族**

### j) Dialog → **删除发射**（原 extern 补声明是编造，重做）
- `Rsrc_Dialog_6a_804` = **.rsrc RT_DIALOG ID 0x6a LANG 0x804**（rva 0x149893c, 1438 字节，PE 资源目录解析实证）
- Ghidra builtin DialogResource size=-1（"Dialog stored as a Resource"）非 struct 非 C++ 全局
- 产物内**零代码引用** → 资源数据属 .rsrc（.rc 编译产物），C++ 源码不发射 → 删 3 行（extern/定义/globals.h 前向声明）
- 链内自洽：regen/emit 每轮重发 → deepfix j 每轮删（幂等链成立）

## 三、nsfix：Type::method → 成员解析器（vc6_ns_freefn.py·adapt 链 10b 步）

**问题定性**（病灶层三问答毕）：
- Ghidra FID 给静态链接的 GBENGINE 函数标类限定名（`gbVec3D::Length`）
- **extract 跳过 FID/library 函数**（`targets/index.ts: if (func.isLibrary) continue` 旁证 +
  GBENGINE.DLL/ 目录 4 TU 均空壳 + plan 3824 条 set_name 零点号、cls 全是游戏层）→ 函数体+声明双缺
- 调用点渲染 `T::m(A0,...)`（A0=对象指针），声明零发射 → C2039×17（藏于截断层后，更多在 7796 后）

**签名源（A 级）**：`original/gbengine.dll` 导出表 1019 条 C++ 修饰名（同代码静态链入 PAL3.exe，
FID 字节匹配 ⇒ dll 签名即二进制真值）。轻量 MSVC demangler 覆盖 GBENGINE 子集：829/1019 解析
（106 unsupported = 函数指针参数等复杂形态，记账）。

**MSVC mangled 规则实证**（本 session 定谳，写进脚本注释）：
1. 约定段：`QAE`/`QBE`=public __thiscall 非 const/const（访问码首字母还有 U=virtual）
2. ctor/op 形态 `??<op码><Class>@@`——**op 码与类名间无 @**（`??0gbVec3D@@`）
3. 指针/引用：P/A 后必跟 A/B（pointee 修饰）：`PAX`=void*、`PBD`=const char*、`AAU`=struct&、`ABU`=const struct&
4. backref 双语义：`U<n>`/`V<n>` 后数字=**名字表**（普通方法 [方法名,类名]→1=类名；ctor/op [类名]→0=类名；
   表随签名内完整拼写命名类型**动态增长**——`?GetColumn@gbMatrix4@@QBEPAUgbVec3D@@PAU2@H@Z` 的 2=ret 的 gbVec3D）
5. 参数位置裸数字=**类型复用**（`IPAD0@Z`=(unsigned, char*, char*)）
6. 返回值 `?A`/`?B` 前缀=按值类返回；`W4<name>@@`=enum（按值，VC6 ABI=int）

**产出**：48 类成员声明（带 mangled 溯源注释）+ 1446 调用点改写（`T::m(&x,rest)`→`x.m(rest)`／
`T::m(p,rest)`→`p->m(rest)`）+ pass0 通用成员可见性清扫（kind-aware fwd batch hoist 文件顶、
pragma once 后；enum/typedef 名绝不 struct-fwd 防 C2371；按值缺口归 emit_missing hoist）。
ctor×370 处与 operator 形态 v1 记账跳过（需语句级改写，下一批）。

**unmatched 记账**：`_default_constructor_closure_`×30（FID 闭包名，dll 无导出）／CCB*/CRect/SSystem
（PAL3 主模块类，靠 plan 游戏层）／exception（CRT 排除族）。

## 四、任务 3 定性：C2552×4/C2078×4 = 两套数据源分裂（记账不硬修）

- 初始化器：**A 面 annotation 语义成员布局**（m_pVtable/m_fStateX…）
- 定义：**gapfill fieldUndef 逐字节快照布局**（UIListBox 定义 31+ 字段 vs 初始化器 75 项 → C2078）
- C2552=布局数不匹配+非聚合判定；`m_pVtable=(char*)0x0` 即"fnptr 值记作 char*"记账项本体
- **根修归 annotation 层**（RoleSystem 属 runaway 族被 size>4096 SKIP 防爆——语义定义本就未生成）
- adapt 层无诚实修法（造定义=编造，改初始化器=丢数据字节）→ 数据层欠账挂账

## 五、下一步（优先级）

1. **截断层 7796 前的 203 攻坚**：C2143×53（语法族）→ C2065×34（LAB_0055f02b 符号遗漏族+FileExistNum
   声明缺）→ C2440×33（类型转换）——LAB_/全局符号遗漏 = reconstruct 漏发（第七节 4 老账）
2. **nsfix v2**：ctor×370（`T::T(&obj,args)` → 语句级拆解/显式 ctor 调用）+ operator 形态 +
   106 unsupported mangled（fnptr 参数）+ _default_constructor_closure_ 的 FID 对账
3. **数据层根修**（annotation 轨道）：RoleSystem/UIListBox 语义布局回填（解锁 C2552/C2078×8）；
   GBENGINE 函数体进 B 面 plan（isLibrary skip 假设待 Ghidra 工程内终验）
4. → 0 错 → 链接层（wine_link·LNK 族）→ B 字节率首数（.cpp.map 已备）

## 六、字节回访账更新（本 session 增补）
- TryExpand：调用约定 __cdecl 渲染 vs __thiscall 真值（链接层 ABI）——新记
- FUN_004014b0：return 0/return iVar1 有 eax 路径证据（**不再是待回滚项**）——销账
- Dialog extern：整项销账（资源不进源码）——销账
- nsfix 成员声明：**声明源=A 级（dll 导出），但函数体仍缺**（链接层 LNK2001 预期）——新记
