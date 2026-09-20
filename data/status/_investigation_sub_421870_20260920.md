# 调查：`UISystem.cpp:23` 的 C2664（`sub_421870`）—— 根因是**一个未注解的 493156 字节类**

**结论先行**：这**不是**一个错别字或类型笔误。它是**一个尚未注解的类**（3 个实例、每个 **493156 字节**）的
成员函数被当成自由函数发射所致。**在识别出这个类之前，不能改注解** ——
任何"给它安一个类名"的做法都违反 `CLAUDE.md` 的「禁止猜测性修改」与「禁止伪语义命名」。
本轮**未改任何注解**，只把证据链固化（下面每条都可复核）。

## 1. 报错本体
`pal3/src/UI/UISystem.cpp:23`（生成物，源函数 `0x00422DF0` = `UISystem::Destroy`）：
```
L23  C2664  'sub_421870' : cannot convert parameter 1 from 'class SceneMgr *' to 'unsigned long *'
```

## 2. 调用点（asm，A 级）
```asm
sub_422DF0:  push esi
             call sub_4226F0          ; eax = 对象指针（getter）
             mov  ecx, eax            ; ⇒ this 走 ecx
             call sub_421870          ; ⇒ __thiscall，**零个栈参数**（前面没有 push）
             mov  esi, offset byte_C21FE8
loc_422E02:  mov  ecx, esi
             call sub_41F8C0          ; 同一元素上的 __thiscall
             add  esi, 78664h         ; 步长 493156
             ...                      ; while ((int)esi < (int)&byte_D8B314)
```
⇒ **`sub_421870` 真实是 `__thiscall` + 0 个栈参数**；而生成的调用是 `sub_421870(v1)`
（自由函数、1 个 `unsigned long *` 形参）⇒ **约定与参数个数两处都不符**。

## 3. 那片区域是"3 个 493156 字节对象"（A 级，双证据）
1. **跨度恰好整除**：`0xD8B314 − 0xC21FE8 = 0x16932C = 1479468 = 493156 × 3` ✓
2. **getter 的算术就是该步长**（`sub_4226F0`，0x004226F0）：
```asm
mov  eax, dword_D8BBEC      ; 状态（0/1/2）
xor  ecx, ecx / mov ecx,1   ; ecx = 状态
lea eax,[ecx+ecx*4] / shl 6 / add ecx / shl 4 / add ecx / lea [eax+eax*2] / lea [ecx+eax*8]
                            ; ⇒ ecx*123289
lea  eax, ds:0C21FE8h[ecx*4]; ⇒ base + 状态*493156 ✓
retn
```

## 4. 该类已证实的成员（A 级：来自指令级 `[reg+imm]`）
| 偏移 | 证据 |
|---|---|
| `+0x84` = **`gbVisNode *`** | `sub_421870`: `mov eax,[esi+84h]` ⇒ `push eax` ⇒ `call gbSceneGraph::DelVisNode(gbVisNode*)` |
| `+0x78650` 指针（带虚调用）| `sub_41F8C0`: `mov ecx,[esi+78650h]; mov edx,[ecx]; push 1; call dword ptr [edx]` |
| `+0x78658` dword | `sub_421870`: `mov ecx,[esi+78658h]` / `mov dword ptr [esi+78658h],0` |
| `+0x7865C` byte | `sub_41F8C0`: `mov byte ptr [esi+7865Ch], 0FFh` |
| `+0x78660` dword | `sub_41F8C0`: `mov [esi+78660h], ebp`(0) |
⇒ 成员都 < `0x78664`，且 `0x78660 = 尺寸−4` ⇒ **类尺寸 = 493156 自洽** ✓
（`+0x84` 与 `+0x78650..60` 的**巨大间距**暗示中间是一大片内嵌数组/池）

## 5. 为什么它没被注解
* **`0x00421870`（`sub_421870`）在任何注解文件里都搜不到** ⇒ 生成物里那个
  `unsigned long *` 来自 **PDB/IDA 推断**，不是注解 ⇒ 按项目规则「PDB 只能作参考、
  不能单独作为证据」它**本就可更正**；
* **`0x0041F8C0` 在 `skip_functions.json` 里**（`reason: between_std_methods`）⇒ 被有意跳过、不参与生成 ✓
* **没有任何已注解类的 `binary_size` 等于 493156**；也**没有任何类**在 `[0x78600,0x78664]`
  有成员（全库扫描命中 **0**）⇒ **该类确实未注解** ✓

## 6. 一个**被本轮推翻的旧结论**（重要）
`CHANGE_LOG.md` 的 **F61（2026-09-19）** 把 `UISceneUpdate`(0x004226F0) 的返回类型
从 `int` 改成 **`SceneMgr *`**，依据是"返回值被当对象基址用：`[eax+0xe0e0]` = `SceneMgr.m_nRoleCount`、
`[eax+0xe35c]`"。
**但**：该 getter 返回的是**本类的对象**（步长 493156），而 `SceneMgr.binary_size = 58692` ✗
⇒ `0xe0e0` 落在一个 **493156 字节对象内部**是**另一个字段**，只是**偏移量巧合**地等于
`SceneMgr` 的 `m_nRoleCount` 位置。**⇒ F61 的"类型选择（SceneMgr）"缺乏依据**；
它"返回指针被当对象基址用"这一观察仍然成立，但**该指针的类不是 `SceneMgr`**。

## 7. 还缺什么（下一步的决定性取证）
* 该区域在 **BSS**（`pe_probe.py` 三个地址都报 `not in any section`）⇒ 元素**运行时构造**，
  静态数据里没有 vtable 线索；
* asm 里对该区域的 11 处引用**全是读**（`lea` / `mov esi,offset`）⇒ **构造发生在计算出的指针上**；
* **⇒ 决定性步骤（需要 IDA 窗口或一个只读探针）**：找到构造这些元素的代码
  （谁以 `0xc21fe8 + i*493156` 为参数调用构造函数 / 写入 vptr），
  由**写入的 vptr 地址**在注解的 `vtables` 表中反查出类名；
  若该类**也没有 vtable**，则退而为它**新建一个注解**（尺寸 493156 + 上表 5 个成员），
  名字**必须来自证据**（例如由构造函数/其它已注解引用给出），否则只能保留 `_todo_` 风格的占位 —— 
  而**本仓目前没有 `_todo_` 类名的先例**（已扫描：0 个）⇒ 这需要一次**明确的规范决策**。

## 8. 本轮处置
**未改任何注解**（遵守「禁止猜测性修改」）。因此 `UISystem.cpp` 的这条 C2664 **仍然存在**，
`codegen all` 的正常路径与 `tests/e2e/test_smoke.py` 的 `compile_regression` 项**继续保持红色** —— 
这是**如实反映**，不是故障（`--skip-probe` 可在只跑 codegen 时绕过）。
**不建议**用"刷新基线"把它洗白（那正是审计警告过的恒真式做法）。
