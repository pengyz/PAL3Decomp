# 布局断言探针（Task 4，2026-09-25）—— MSVC6 SP0 实测证据

编译器：`tools/compilers/msvc6.0` cl 12.00.8168（`tools/wine_cl.sh`），`/O2 /GR`（dup2 用 `/Od`）。
本目录为 Task 4（布局断言生成器 `tools/layout_assert_gen.py`）的**金样本**：每条结论都能用下列命令复现。

| 文件 | 作用 |
|---|---|
| `shape.cpp` | PMF 尺寸矩阵（E-4 封闭规则 **+ 本轮扩展的闭包边界**），候选值探针 |
| `off.cpp` | `offsetof` 在各类继承形态下是否**常量表达式**（E-3 跳过判据的精确边界） |
| `dup2.cpp` | 同名 typedef 的真实错误码（简报"C2086"的实测收窄） |
| `pmf_intro.cpp` | **R=1（C-3）**：PMF 还取决于 **vfptr 引入点**（非多态基 + 派生自引入 ⇒ 8），用 `/FAs` 读编译器自己算的常量 |
| `ivb.cpp` | **R=1（C-1）**：**间接**虚基的成员 `offsetof` 也不是常量表达式（C2057+C2466） |
| `verify_generated_asserts.py` | **编译器裁判**：常量由编译器自己发现 → 生成 `_layout_asserts.h` → 正相 0 错误 + 4 类负相被查获 + 虚基 C2057 + 重名族 |
| `verify_emitted_asserts.py` | **R=1（C-3）端到端裁判**：真实**生效断言** × 真实**发射头** 逐条编译 ⇒ 抓"假杀"（`--self-test` 为负相自检） |
| `check_shape_against_binary.py` | 形状输入的**独立二进制佐证**（`original/PAL3.exe.asm` 的 ctor vfptr 写入 + `.rdata` 原始字） |
| `_layout_asserts.census.json` | 真实 annotation **全量 881 类**的生成台账（默认口径：total=10918 / active=**140**；R=0 为 176） |
| `_layout_asserts.sample.h` | 6 个代表类的**可读样张**（含 5 条生效形状断言 + UIEmote 的 `[SUSPECT]` 降级） |
| `_emitted_asserts_judge.json` | R=1 端到端裁判台账（140 编译：132 PASS / 0 假杀 / 8 头文件自身编不过） |

复现全部：

```sh
cd /home/peng/workspace/PAL3Decomp
P=data/status/_layout_assert_probe_20260925
tools/wine_cl.sh /c /nologo /O2 /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/shape.obj $P/shape.cpp
tools/wine_cl.sh /c /nologo /O2 /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/off.obj   $P/off.cpp
tools/wine_cl.sh /c /nologo /Od                        /Fo/tmp/dup2.obj  $P/dup2.cpp
tools/wine_cl.sh /c /nologo /O2 /GR /FAs /Itools/compilers/msvc6.0/Include \
    /Fo/tmp/pmf_intro.obj /Fa/tmp/pmf_intro.asm $P/pmf_intro.cpp   # R=1：读 asm 里的常量
tools/wine_cl.sh /c /nologo /O2 /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/ivb.obj $P/ivb.cpp
python3 $P/verify_generated_asserts.py         # ≈30 次 MSVC6 编译，1–2 分钟
python3 $P/verify_emitted_asserts.py           # R=1 端到端裁判，≈10 秒（140 次编译）
python3 $P/check_shape_against_binary.py
```

---

## 1. PMF 尺寸（E-4）：规则**必须走传递闭包**，不是直接基个数

`shape.cpp` 每条 `(形状, 候选值)` 一个断言；**报 C2118 = 该候选错**，不报 = 正确。

```
$ tools/wine_cl.sh /c /nologo /O2 /GR /I.../Include /Fo/tmp/shape.obj .../shape.cpp
shape.cpp
.../shape.cpp(21) : error C2118: negative subscript or subscript is too large
.../shape.cpp(28) : error C2118: negative subscript or subscript is too large
.../shape.cpp(30) : error C2118: negative subscript or subscript is too large
.../shape.cpp(32) : error C2118: negative subscript or subscript is too large
.../shape.cpp(34) : error C2118: negative subscript or subscript is too large
```

行号 → 结论（`shape.cpp` 逐行）：

| 行 | 形状 | 断言 | 结果 ⇒ 真值 |
|---|---|---|---|
| 21 | `SI : A1` | `pmf == 8` | C2118 ⇒ **4** |
| 22 | `MI2 : A1,B1` | `pmf == 8` | 通过 ⇒ **8** |
| 23 | `MI3 : A1,B1,C1` | `pmf == 8` | 通过 ⇒ **8** |
| 24 | `VOnly : virtual V1` | `== 12` | 通过 ⇒ **12** |
| 25 | `MIV : A1,B1,virtual V1` | `== 12` | 通过 ⇒ **12**（虚基优先于多继承） |
| 26/27 | `MIVV : A1,virtual V1,V2` | `== 12` | 通过 ⇒ **12**（多虚基不是 16） |
| 28 | `DERofMI2 : MI2` | `pmf == 4` | **C2118 ⇒ 不是 4** |
| 29 | `DERofMI2 : MI2` | `pmf == 8` | 通过 ⇒ **8** ★ |
| 30 | `DERofMI2 : MI2` | `pmf == 12` | C2118 ⇒ 不是 12 |
| 31 | `DERofSI : SI` | `pmf == 4` | 通过 ⇒ **4** |
| 32 | `DERofV : VOnly` | `pmf == 4` | **C2118 ⇒ 不是 4** |
| 33 | `DERofV : VOnly` | `pmf == 12` | 通过 ⇒ **12** |
| 34 | `DERofDERofMI2 : DERofMI2` | `pmf == 4` | **C2118 ⇒ 不是 4** |
| 35 | 同上 | `pmf == 8` | 通过 ⇒ **8** |

★ **本轮新增的关键边界**：`DERofMI2` 只有**一个**直接基，但真值是 **8**（不是 4）——
只看"直接基个数 > 1"的朴素规则会预测 4 ⇒ **假 C2118 ⇒ 管线停摆**。
这与 `p3.cpp` 的 E-4（MI+虚继承不封闭）是同一类停摆风险，只是发生在**闭包深度**方向。

⇒ 实现规则（`tools/layout_assert_gen.py: shape_info`）：

```
继承闭包内有虚基        ⇒ 12      （多虚基仍是 12）
否则闭包内出现多继承分支 ⇒ 8       （含"单直接基但基类是多继承类"）
否则                    ⇒ 4
```

**攻击集复现**（`data/status/_vtable_attack_cases_20260925/p3.cpp`，与 README E-4 逐字一致）：

```
p3.cpp(19) : error C2118   ← t_MIV8   （MI+虚继承不是 8）
p3.cpp(21) : error C2118   ← t_MIVV8
p3.cpp(23) : error C2118   ← t_MIVV16  （多虚基不是 16）
p3.cpp(25) : error C2118   ← t_VV16
p3.cpp(28) : error C2057   ← offsetof(VOnly, vv) 虚基成员
p3.cpp(29) : error C2118   ← offsetof(MI2, b) == 8 错（真值 12）
```

## 2. `offsetof` 的可用边界（E-3）：只跳过**虚基区域**

`off.cpp` 逐行结论：

```
off.cpp(14) : error C2118   ← o4: offsetof(NV, x)==8 错 ⇒ 本类成员是常量（真值 12）
off.cpp(15) : error C2057   ← o5: offsetof(NV, vv)  虚基成员 ⇒ 不是常量表达式
off.cpp(16) : error C2118   ← o6: offsetof(DV, dm)==4 错 ⇒ 本类成员是常量（真值 8）
off.cpp(17) : error C2057   ← o7: offsetof(DV, vv)  虚基成员 ⇒ 不是常量表达式
off.cpp(18) : error C2057   ← o8: offsetof(DV2, w)  **虚基的非虚基之成员** ⇒ 也不是常量表达式
（11/12/13/19/21 行无错误 ⇒ o1..o3/o9/o10 通过）
```

| 成员位置 | offsetof 是否常量 | 例 |
|---|---|---|
| 非虚基成员（类有虚基也无妨） | **是** | `o3: offsetof(NV, a)==4` 通过 |
| 本类成员（虚继承/多继承下） | **是** | `o4`（值 12）、`o6`（值 8）、`o9` |
| 虚基成员 | **否**（C2057） | `o5`、`o7`；攻击集 `p3.cpp:28` |
| **虚基的非虚基之成员** | **否**（C2057） | `o8` ★ |

⇒ 跳过判据 = **虚基 + 其传递闭包**（`virtual_base_region`），不是"有虚基就整类跳过"，
也不是"只跳过虚基本身"。两个方向都会出事：少跳 ⇒ C2057 停摆；多跳 ⇒ 静默丢覆盖。

## 3. `#include <stddef.h>` 是硬前置

```
$ tools/wine_cl.sh ... /Fo/tmp/p2.obj data/status/_vtable_attack_cases_20260925/p2.cpp
p2.cpp(4) : error C2065: 'offsetof' : undeclared identifier
p2.cpp(4) : error C2275: 'DV2' : illegal use of this type as an expression
p2.cpp(4) : error C2057: expected constant expression          ← 连带噪声
```

⇒ 生成头必须无条件注入 `#include <stddef.h>`（否则真错误被 C2065/C2275 掩盖）。

## 4. 编译器裁判（`verify_generated_asserts.py`）逐字输出

```
== 1. 常量发现（真机 MSVC6 SP0，唯一不报错的候选即真值）==
  pmf      SI=4  MI2=8  MI3=8  VOnly=12  MIV=12  MIVV=12  VV=12  DERofMI2=8  DERofSI=4  DERofV=12
  size     SI=8  MI2=16  N=12  NV=24  DV=20
  offset   SI.a=4  MI2.a=4  MI2.b=12  N.a=4  N.n=8  NV.a=4  NV.x=12  DV.dm=8
  offset   NV.vv ⇒ **非虚基区域**：全候选 C2057（不是常量表达式）⇒ 必须跳过
  offset   DV.vv ⇒ **非虚基区域**：全候选 C2057（不是常量表达式）⇒ 必须跳过

== 2. 正相：生成的 _layout_asserts.h 必须 0 错误 ==
  census: active=31 commented=0 skipped=2
  生效断言 31 条 ⇒ 编译 0 错误 ✓
  首条生效断言在 TU 第 53 行（共 31 条）

== 3. 负相：改错常量必须被编译器抓到（C2118）==
  sizeof 改错 (+4)                ⇒ 查获 ['C2118']
  成员偏移改错 (+4)               ⇒ 查获 ['C2118']
  继承形状改错 (MI 写成 SI)        ⇒ 查获 ['C2118']
  闭包判据退回直接基 (DERofMI2)    ⇒ 查获 ['C2118']

== 4. 虚基区域成员的 offsetof 硬写进去 ⇒ 必须 C2057（E-3）==
  朴素生成器（不跳过虚基成员）⇒ C2057 ✓ ['C2057', 'C2466']
  ⇒ 与生成器的跳过判据一致：NV::vv / DV::vv 在发现阶段即为 NOT_CONSTANT

== 5. 断言类型名重复（命名唯一性要求的实证）==
  同名 typedef 但数组尺寸不同 ⇒ C2369 ✓ ['C2369']
  同名 typedef 且形态冲突（数组 vs 指针）⇒ 查获 ✓ ['C2372']
  同名 typedef 且类型相同 ⇒ 0 错误（MSVC6 允许冗余 typedef）

ALL CHECKS PASSED（真机 MSVC6 SP0：发现 25 个常量；正相 0 错误；4 类负相均被查获；虚基成员 C2057；重名 C2369/C2372（重定义族，非 C2086））
```

要点：
* **常量不是手抄**：对每个目标枚举候选值，唯一"不报错"的候选即真值（C2118 = 常量但值不符）；
  虚基成员的 offsetof 对**所有**候选都只报 C2057 ⇒ "跳过"不是保守过头，是**必须**。
* 生成头的正相里 `commented=0`：探针布局的常量全部来自编译器发现（A 形态 ∧ 独立）⇒ 全部生效。

## 5. 独立二进制佐证（`check_shape_against_binary.py`）

形状断言的**输入**（"这个类是不是多继承"）来自 annotation。用两个独立来源核对：

```
$ python3 check_shape_against_binary.py
imagebase=0x00400000 sections=['.text', '.rdata', '.data', '.rsrc']

== CEffSParticle (sub_4D4EA0) ==
   mov     dword ptr [eax+0Ch], offset off_56FB70
   mov     dword ptr [eax+0Ch], offset off_56FB28
   ⇒ +0xC 处写入 off_56FB28，其 .rdata 内容 = 004D5850 004C2850 004D5860 004D4F00 ⇒ vtable（内容全是代码地址）
   ⇒ 结论：该类的**二进制**继承形状 = 多继承（注解记 2 个直接基）

== UIEmote (sub_44E530) ==
   mov     dword ptr [esi+44h], offset off_56A9C0
   mov     dword ptr [esi+44h], offset off_56B044
   ⇒ +0x44 处写入 off_56B044，其 .rdata 内容 = 0044EB40 0044AB00 004AF760 00445E70 ⇒ vtable（内容全是代码地址）
   ⇒ 结论：该类的**二进制**继承形状 = 多继承（注解记 2 个直接基）

BINARY CROSS-CHECK PASSED（形状输入 = 多继承，由二进制独立佐证）
```

* **CEffSParticle**：ctor 在 `+0` 与 `+0x0C` 各写一次 vfptr，且 `+0x0C` 目标是**vtable**
  （内容是代码地址，不是 vbtable 的小整数偏移）⇒ 多继承、无虚基 ⇒ PMF **8**
  ⇒ 生成器对它的生效断言 `sizeof(void (CEffSParticle::*)()) == 8` 有二进制支撑。
  （同一族的 `sub ecx, 0Ch; jmp ...` 静态 adjustor thunk 亦与 MI 相符；虚基 adjustor 是
  `sub ecx, [ecx-4]` 动态形，见 `_vtable_abi_probe_20260925/README.md` #5。）
* **UIEmote**：二进制同样是 MI（`+0x44` 处第二张 vtable），但注解把第二个基记成了
  **内嵌成员**（`baseclass2`，source=`PAL3patch:multi_inheritance_as_embed`）⇒
  **声明形状（可能是单继承）与二进制形状（多继承）不一致** ⇒ 生成器对它的形状断言
  **降级为 `[SUSPECT]`（不生效）** 是唯一安全的选择：4 与 8 都可能与 codegen 的声明不符。

## 6. 同名 typedef 的真实错误码（简报收窄）

`dup2.cpp`（四种重名形态各一对）：

```
dup2.cpp(2) : error C2371: 'a1' : redefinition; different basic types
dup2.cpp(4) : error C2369: 'b1' : redefinition; different subscripts
dup2.cpp(6) : error C2040: 'c1' : 'int *' differs in levels of indirection from 'int'
dup2.cpp(8) : error C2369: 'd1' : redefinition; different subscripts   ← 负数组技巧形
```

⇒ MSVC6 SP0 对重名 typedef 走 **C2371 / C2369 / C2040（以及数组 vs 指针时的 C2372）**，
**没有出现 C2086**；且**类型完全相同**的冗余 typedef **被接受**（`dup_typedef_same` 0 错误）。
⇒ 简报"同名 ⇒ C2086"按实测收窄（见交付报告"顾虑 1"）；**命名唯一性要求本身仍然成立**
（否则一条通过一条失败时错误码交织、定位含混；且一旦改用带尺寸的数组类型立刻变硬错误）。

---

## 已知缺口

1. `shape.cpp` / `off.cpp` 的"候选值"写法会把错误行**挤在一起**（每条候选一行），
   候选集合固定为 4/8/12/16/20 与 0..32 步进 4；若将来出现非 4 字节对齐的成员偏移，
   需扩候选表。
2. `check_shape_against_binary.py` 只核了 **2 个类**（CEffSParticle / UIEmote）——
   其余 29 个多基类的 ctor 与次基偏移未逐个核对（属 Task 8 管线集成范围）。
3. `verify_generated_asserts.py` 的常量发现按"每目标一次编译"实现（25 次编译，1–2 分钟）；
   若扩展到全量类，需要分批 + C1003 截断防护。
4. 全量头文件（12715 行 / 2.3 MB）**不入库**，按需重生成：
   ```sh
   python3 tools/layout_assert_gen.py --out /tmp/_layout_asserts.h \
       --census-json data/status/_layout_assert_probe_20260925/_layout_asserts.census.json
   ```
   默认口径下生效的 176 条**全是形状断言**；size/offset 断言因常量与 annotation 同源（E-2）
   而留痕不生效（`[SAME-SOURCE]` 68 条 / `[SUSPECT]` 10674 条）。

---

# R=1 修复轮实测（2026-09-25，评审 3 Critical + 1 Important）

## 7. PMF 还取决于 **vfptr 引入点**（C-3）：`pmf_intro.cpp`

`shape.cpp` 的封闭规则只覆盖"继承形状"，漏了"vfptr 在哪"。R=0 实测反例
`RoleCameraCtrl : public PalScriptWaitObj` 的真实发射头编译 **C2118**（生成器给 4，真值 8）。

`pmf_intro.cpp` 把判据逐行测出来（常量由编译器自己算进 `.data`，不手抄）：

```sh
$ tools/wine_cl.sh /c /nologo /O2 /GR /FAs /Itools/compilers/msvc6.0/Include \
      /Fo/tmp/pmf_intro.obj /Fa/tmp/pmf_intro.asm $P/pmf_intro.cpp
$ grep -E '^\?' /tmp/pmf_intro.asm
?p_MI_NP@@3HA DD 08H          ; MI_NP  : NP_A, NP_B      （非多态多继承）⇒ 8
?p_MI_P@@3HA DD 08H           ; MI_P   : P_A, P_B
?p_SI_P@@3HA DD 04H           ; SI_P   : P_A             （基类自带 vfptr）⇒ 4
?p_SI_NP@@3HA DD 04H          ; SI_NP  : NP_A            （全非多态）⇒ 4
?p_INTRO@@3HA DD 08H          ; INTRO  : NP_A {virtual f} ★ 非多态基 + 派生自引入 vfptr ⇒ 8
?p_INTRO_D@@3HA DD 08H        ; INTRO_D : INTRO
?p_INTRO_D2@@3HA DD 08H       ; INTRO_D2 : INTRO {virtual g}
?p_INTRO_MID@@3HA DD 08H      ; INTRO_MID : NP_MID {virtual f}   （载体在中间层）
?p_DER_INTRO_MID@@3HA DD 08H  ; DER_INTRO_MID : INTRO_MID
?p_VB_NP@@3HA DD 0cH          ; VB_NP  : virtual NP_A    ⇒ 12（虚基优先）
?p_VB_P@@3HA DD 0cH           ; VB_P   : virtual P_A
?p_MI_INTRO@@3HA DD 08H       ; MI_INTRO : NP_A, P_B {virtual f}
?z_MI_NP@@3HA DD 0cH          ; sizeof(MI_NP)
?z_INTRO@@3HA DD 0cH          ; sizeof(INTRO) = 4(基) + 4(vfptr) + 4(x)
?z_INTRO_D@@3HA DD 0cH
?z_DER_INTRO_MID@@3HA DD 08H
?z_VB_NP@@3HA DD 08H
?z_MI_INTRO@@3HA DD 0cH
```

⇒ **4 字节 PMF 要求 vfptr 在偏移 0**。基类非多态而派生类自己引入 vfptr 时，MSVC6 把 vfptr
**排在基类子对象之后**（`INTRO` 与 `SI_P` 同为"单继承 + 一个 vfptr"，`sizeof` 差 4）⇒ 8 字节表示。
实现规则（`shape_info`）：

```
闭包内有虚基                      ⇒ 12
否则闭包内出现多继承分支          ⇒ 8
否则最基层 vfptr 载体**有直接基** ⇒ 8      ← R=1 新增
否则                              ⇒ 4
```

**载体判据只能看 `vtables`，不能看 `methods`**：codegen 发射 `virtual` 的判据是
`pipeline/gen/stages/emit_headers.py:2460` 的 `_addr_int_vt in _vtable_addr_order`（来自注解
`vtables` 的槽位）⇒ 只有 `methods` 的类在发射头里**没有** virtual（实测
`pal3/src/Misc/PalScriptWaitObj.h`：`char ReleaseObject(char *pszBuf);` 非虚）。

**兜底（过判防护）**：`gbTexture` 的声明在 `include/gbengine/gbTexture.h`（手写 spec 头，
`gbRefObject` 自带 `virtual ~`）⇒ 真值 **4**，而注解链（`gbResource`/`gbRefObject` 无 `vtables`）
按载体规则会算 **8**。⇒ 外部前缀（`gb*`，可用 `--external-prefix` 改）与 `--declared-classes`
名单之外的类**一律 SUSPECT**（含闭包内出现的这类基类）。

## 8. `offsetof` 跳过集合必须走**整个闭包**（C-1）

R=0 只看**直接**虚基。实测反例（间接虚基，`ivb.cpp`）：

```cpp
struct V1  { virtual void v(); int vv; };
struct VB2 : virtual V1 { int x; };
struct IVB : VB2 { int dm; };            // IVB 的**直接**基 VB2 是非虚的
typedef char t_ivb_vv[(offsetof(IVB, vv) == 0) ? 1 : -1];
```

```sh
$ tools/wine_cl.sh /c /nologo /O2 /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/ivb.obj $P/ivb.cpp
ivb.cpp(22) : error C2057: expected constant expression      ← offsetof(IVB, vv) 间接虚基
ivb.cpp(22) : error C2466: cannot allocate an array of constant size 0
ivb.cpp(25) : error C2118: negative subscript …              ← offsetof(IVB, x) 常量但值不是 8
ivb.cpp(26) : error C2118: negative subscript …              ← offsetof(IVB, dm) 常量但值不是 4
ivb.cpp(30) : error C2057 / C2466                            ← offsetof(DV, vv) 直接虚基（对照组）
```

⇒ 只有**虚基区域**（22/30 行）出 C2057；非虚基/本类成员（25/26 行）只出 C2118（是常量、值不符）。
跳过集合 = `{layout} ∪ 闭包` 里**每个类**的虚基 + 该虚基的传递闭包；
**非虚**基（VB2）本身**不进**集合（`off.cpp` o3 实测其成员仍是常量表达式）。

## 9. `--virtual-bases` 必须**加入** bases（C-2）

R=0 的 `is_virtual=bn in vb`（bn 只遍历 `base_names`）等价于把覆盖文件与 `base_class`
**求交** ⇒ 注解里没有的虚基被**静默丢弃**，零 warning。实测（喂 `{'D': ['V1']}`，
D 的 `base_class=['VB2']`）：

```
R=0:  D.bases=[('VB2',False)]  pmf=4（应 12）  region=[]      零 warning   ← 静默失效
R=1:  D.bases=[('VB2',False), ('V1',True)]    pmf=12          region={V1}
      未知名额外 WARN（"无布局信息 ⇒ 形状不可证 ⇒ 断言降级"）
```

这是 Task 8 **唯一**的虚基回填入口 ⇒ 静默失效等于整条虚基判据失效。

## 10. 端到端裁判（`verify_emitted_asserts.py`）：唯一能抓假杀的手段

```sh
$ python3 $P/verify_emitted_asserts.py --jobs 6            # R=1（修复后）
=== 端到端裁判（真实生效断言 × 真实发射头，MSVC6）===
生成口径: total=10918 active=140 commented=10778 consistency-only=0
编译: total=140 pass=132 false_kill=0 unreliable=0 assert_error=0 header_error=8
未编译: no_header=0 spec_header=0 by_root={'pal3/src': 140}
  HEADER-ERROR CCBParabolaWindow (Combat/CCBParabolaWindow.h): ['C2555@32']
  HEADER-ERROR CEffTrackCustomShape (Misc/CEffTrackCustomShape.h): ['C2584@7']
  … CEffTrackCylinder / CEffTrackGrid / CEffTrackModel / CEffTrackQuad / CEffTrackSParticle（同 C2584）
  HEADER-ERROR PlayerAtt (Misc/PlayerAtt.h): ['C2061@91']
=== ALL CHECKS PASSED ===
```

8 个头文件自身编不过的类 = 评审独立复算的同一集合（其中 6 个 `CEffTrack*` 是 **I-1**
"重复间接基"注解问题，按裁定转注解修复；`PlayerAtt` 的 C2061 在 `RoleAtt.h:91`；
`CCBParabolaWindow` 是 C2555 覆盖返回类型）。

**变体检验（把 C-3 判据退回 R=0）⇒ 裁判立刻抓到假杀**：

```
$ （临时把 `elif carrier is not None and not vfptr_at_zero` 改为 `elif False`）
编译: total=140 pass=131 false_kill=1 …
  FALSE-KILL RoleCameraCtrl: sizeof(void (RoleCameraCtrl::*)()) == 4
    _a_RoleCameraCtrl_pmf.cpp(3) : error C2118: negative subscript or subscript is too large
```

**负相自检**（`--self-test`，故意写错一条断言）：

```
$ python3 $P/verify_emitted_asserts.py --self-test
SELF-TEST OK: pass=1 false_kill=1
```

分类按**行号**区分"断言行"与"头文件自身"：断言行 C2118 且 TU 无其它错误 ⇒ `false_kill`；
断言行 C2118 但头也编不过 ⇒ `unreliable`（连锁噪声，不判生成器）；其余 ⇒ `header_error`/
`assert_error`；找不到声明该类的头 ⇒ `no_header`。

## 11. `consistency-only` 档（I-2）在真实数据上的实测（⚠️ 给 Task 8 的警告）

`--untrusted-policy consistency-only` 把 size/offset 断言按"**codegen 声明 vs 注解常量**"
一致性口径放开（默认口径逐字不变）。真实数据上：

```
$ python3 tools/layout_assert_gen.py --untrusted-policy consistency-only \
      --declared-classes /tmp/declared_pal3src.json --out /tmp/_la_consistency.h
wrote /tmp/_la_consistency.h | total=10918 active=8986 commented=1932 skipped=2
      (trusted=140 same-source=0 suspect=1932)
by_trust = {'consistency-only': 8846, 'trusted': 140, 'suspect': 1932}
```

⇒ 默认口径下 size/offset 生效 **0** 条；该档下 **8846** 条（= 名单内、非疑误归属的全部
size/offset）。

抽样 14 个成员最多的类（1841 条断言）逐条编译：

```
抽样结果 total=1841 pass=1706 false_kill=64 unreliable=0 assert_error=71 header_error=0
  FALSE-KILL CCBRoleState sizeof(CCBRoleState) == 22224
  FALSE-KILL CCBRoleState offsetof(CCBRoleState, m_byteFlags) == 7676
  ASSERT-ERR CCBRoleState offsetof(CCBRoleState, m_sCombatDialog) == 0   ['C2039@3']
```

⇒ **该档是"漂移探测器"，不是可常开的一致性闸**：它立刻暴露三类既有漂移 ——
① 注解把基类成员**摊平**进本类（发射头改走继承 ⇒ `offsetof(Cls, 基类成员)` C2039）；
② 基类 `sizeof`/vfptr 模型与发射头不一致 ⇒ 成员整体位移（C2118）；
③ 同源常量本就不保证与声明一致（E-2）。低成本启用路径：**按类试运行**
（`--only <类> --untrusted-policy consistency-only`），不要一次性全开。