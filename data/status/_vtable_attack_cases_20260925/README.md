# 对抗性正确性攻击用例集 —— vtable 映射设计 v2（2026-09-25）

攻击目标：`docs/superpowers/specs/2026-09-25-vtable-mapping-design.md`。
方法：**不审文档，构造输入证伪设计规则**。全部用例用真机 MSVC6 SP0（`tools/wine_cl.sh`，
cl 12.00.8168）实测编译，vtable 用 `tools/coff_vtable.py` 提取，反汇编用 objdump/ndisasm。

复现：
```sh
cd /home/peng/workspace/PAL3Decomp
tools/wine_cl.sh /c /Od /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/x.obj \
    data/status/_vtable_attack_cases_20260925/<case>.cpp
python3 tools/coff_vtable.py /tmp/x.obj        # 槽序
objdump -d /tmp/x.obj                          # 函数体 / 调用点
```

方法可信度：先复现 `_vtable_abi_probe_20260925/README.md` 的 #2/#7/#8 三条实测
（T1/T3/DO 槽序），与探针记录**逐槽一致** ✓。

标签：🔴 产出错误二进制（或必然编译停摆）｜🟡 产出错误声明｜🟢 仅影响诊断

---

## 攻击 1 —— §2.2 槽序规则（同名组内逆序）

### A-1 🔴 指定形状：3 同名重载 + 中插 1 不同名 + 继承链同名覆写（`a2.cpp` + `r1.cpp`）

```cpp
struct Base {
    virtual void o();  virtual void o(int);  virtual void mid();  virtual void o(double);
};
struct Der : Base {
    virtual void o(double);   // 同名覆写
    virtual void o(int);      // 同名覆写
    virtual void o(char*);    // 新增重载（名字跨继承边界）
    virtual void tail();
};
```
实测槽序：
```
Base: [o(double), o(int), o(), mid()]                      ← 插队者 mid 被挤到组后（T3 规则 ✓）
Der : [o(double)@Der, o(int)@Der, o()@Base, mid()@Base, o(char*)@Der, tail@Der]
                                          ↑ 名 "o" 占据 {0,1,2,4} 非连续！
```
**§2.2 前向模型（"同名组占据首现位置的连续区段"）被 ABI 证伪**：Der 的槽序里
`o` 组被 `mid` 隔断 + 新重载尾插 ⇒ **不存在任何声明序能在该模型下生成此槽序**。
§3.5 校验 2（声明顺序→槽序按"同名组内逆序"）对该类**不可满足**：
Der 头文件里 `[o(double), o(int), o(char*), tail]` 三个 `o` 会被并成一个组预测成
`[o(char*), o(int), o(double), tail]`，与真值（覆写原位 + 尾插）无关 ⇒ 无论怎么重排
声明序都对不上 ⇒ `per-class-hard` 门禁**永久阻塞**该类头文件生成。

逆规则重发射实证（`r1.cpp`）：按 §2.2"按名分组→组位置=首现位置→组内反转"从 Der 实测槽序
反推声明序 = `[o(char*), o(), o(int), o(double), mid(), tail]`，编译产物槽序 =
`[o(double), o(int), o(), o(char*), mid(), tail]` ⇒ **slot3/4 与真值互换 ⇒ 🔴 错误二进制**。

### A-2 🔴 同名组跨继承边界分裂（`a1.cpp` / `a3.cpp` / `a4.cpp`）

```cpp
struct B { virtual void f(); virtual void o(int); virtual void o(double); virtual void g(); };
struct D : B { virtual void o(float); virtual void o(char); virtual void h(); };
```
实测：`D = [f, o(double)@B, o(int)@B, g, o(char)@D, o(float)@D, h]`。
派生类新增的同名重载**永远追加表尾**（a3/a4 同证），**永不并入基类组区段**；
且派生类自己的新组内部**同样逆序**（decl `[o(float),o(char)]` → 槽 `[o(char),o(float)]`）。
⇒ "组位置=首现位置" 跨类即失效；同一逻辑名的槽位分居 2~3 个不相连区段（c2 里 `o` 甚至
横跨 A 视图表与 V 视图表两张表）。

### A-3 🟡 逆映射不可逆（`vt7/T3` 与 `t4.cpp`）

`decl [p, o(int), q, o(double)] → 槽 [p, o(double), o(int), q] → 逆规则 → [p, o(int), o(double), q]`
≠ 原声明序（插队者 q 的声明位置丢失）。同型：`t4.cpp` `decl [z, o(char*), w, o(short)]`
→ 槽 `[z, o(short), o(char*), w]` → 逆推 `[z, o(char*), o(short), w]`。本例 vtable 恰好可
还原 ⇒ 仅 🟡（发射的声明序与真实源不同；与 PDB/人工表核对会假失败），与 A-1 合并即不可还原。

---

## 攻击 2 —— §2.1 合成槽模型（`c2.cpp`：虚继承 + MI + 虚析构 + 同名重载）

```cpp
struct V  { virtual ~V();  virtual void o();      int v_; };
struct A  : virtual V { virtual ~A(); virtual void o(int); int a_; };
struct Bx { virtual ~Bx(); virtual void b();      int b_; };
struct D : A, Bx {
    virtual ~D();  virtual void o();  virtual void b();  virtual void o(double);  int d_;
};
```
实测 7 张表（`??_7D@@6B@`(Bx 视图) / `??_7D@@6BA@@@`(A 视图) / `??_7D@@6BV@@@`(V 视图) …）
+ vbtable `??_8D@@7B@` / `??_8A@@7B@`。暴露 4 个模型缺口：

### B-1 🟡 混合槽：deleting dtor × 动态 vbase adjustor × 常量 delta —— 无 kind 可归
`??_ED@@$4PPPPPPPM@BA@AEPAXI@Z`（V 视图 dtor 槽），本体 11 字节：
```
sub ecx, [ecx-4]      ; 动态 vbtable 调整（不是常量 delta）
sub ecx, 0x10         ; 常量调整
jmp  <本体>
```
§2.1 分类特征两条都命中不了：`??_E` 命中 `deleting_dtor`（则"不推断、1 声明↔1 槽"，把 thunk
性质丢了）；adjustor 特征 `$4..@A@A` 匹配不到 `@BA@A`，序言也不是文档写的
"`sub -N(%ecx),%ecx; jmp`" 两指令形态（多一条 `sub ecx,imm`）。
⇒ 记账不映射 ⇒ §8.3"每槽必有声明"无法满足（要么永久 warn，要么编造声明）。

### B-2 🟡 1 声明 ↔ 多视图多槽（析构）—— 与 `deleting_dtor` 的 "1↔1" 映射矛盾
`virtual ~D()` 在 Bx 视图表 = 裸 `??_ED@@UAEPAXI@Z`（`??_E` 是 `??_G` 的弱别名，
同一节同址），在 V 视图表 = B-1 的 thunk ⇒ 一个声明挂 2 槽、2 个符号、2 种 this 约定。

### B-3 🟡 声明落在"异己视图"表 —— 校验 1 无规则可循
`~A` 覆写 `~V` ⇒ **A 自己的视图表 `??_7A@@6B0@@` 里没有析构槽**（只有 `o(int)@A`），
析构槽在 V 视图表。§3.5 校验 1"声明数量 == slots 数量（按 view 对）"：
按 A 视图数 = 声明 2（`~A`,`o(int)`）vs 槽 1 ⇒ 必然假失败。模型缺
"某类声明可以落在基类/虚基类视图表"这条规则。

### B-4 🟡→🔴 动态 delta 无法归一成 §3.6 的二元组
§3.6 对比项"每槽归一化二元组（目标函数, this 调整量）——thunk 归一后对比"：
B-1 的调整量 = 运行期 vbtable 值 + 常量 0x10，**不是标量** ⇒ 二元组不成立，至少要
(target, kind=dynamic, const)。若发射侧归一成 (target,0x10) 而 .obj 侧归一成 (target,dyn)
⇒ 对比**永久不匹配**，把正确类判死（升级 🔴）。

**阴性结果**（省得再查）：协变返回 `c1.cpp` 直接 **C2555**（MSVC6 不支持）⇒ 不构成槽型缺口。

---

## 攻击 3 —— 签名推断（`s1/s3/r2/e1/b1`）

### C-1 🔴 未用参数：callee 主证据给 0 参，真值 2 参
`void S::unused(int,int) {}` 本体 = **3 字节 `ret 8`**，prologue 后 `[esp+4..]` 读取集合 = **∅**。
§3.2 第 3 步"主证据 = 读取集合"⇒ 0 参（真值 2）。且该形态三条约定规则全部落空
（不碰 ecx、非裸 C3）⇒ 约定也推不出来。thiscall 参数个数直接决定 `ret N` 与调用点 push 数
⇒ 🔴 必然错二进制。

### C-2 🔴 __fastcall 寄存器传参：三条证据全部收敛到错误值（并连带打穿 §5.1）
`virtual void __fastcall freg(int,int)`：本体 `ret 4`、读集 ∅；调用点
`mov edx,1; push 2; mov ecx,obj; call *4(vt)` —— **push 计数 = 1**。真值 2 参 + fastcall。
推断结果 = "thiscall 1 参"（`mov ecx,esi` 被规则"ecx 存 this ⇒ __thiscall"吃掉）。
**设计规则集根本没有 __fastcall 分支** ⇒ 发射 `p->freg(x)`（push 形态）vs 真值
（mov edx + push）⇒ 🔴，而 callee/调用点/vtable 三层全部无感。

### C-3 🔴 __cdecl 成员函数：`this` 被计成第一个参数（两侧同时确认错误个数）
```cpp
struct Xc { int m; virtual void __cdecl cf(int); virtual void __cdecl cf2(int,int); };
void __cdecl Xc::cf(int x){ m = x; }
```
实测 `cf` 本体读 `[esp+4]`(=**this**)、`[esp+8]`(=x) ⇒ 读集 = 2 ⇒ 推断 "2 参"（真值 1 参）；
调用点 `push 1; push this; call` ⇒ **push 计数 = 2** ⇒ 旁证也说 2。
`cf2` 同理 3 vs 2。⇒ **交叉验证会"确认"错误答案**，发射 `void cf(int,int)` 后调用点变 3 push ⇒ 🔴。
设计没有任何"this 在栈上（cdecl 成员/变参成员）"的规则。

### C-4 🟡/🔴 变参：无 `...` 表达 + mangling 特征写错
`virtual void log(const char*, ...)` mangling = **`?log@S@@UAAXPBDZZ`**（虚变参是
`UAA…ZZ`；设计写的 "mangle QAA" **匹配不到**）。本体裸 `ret`、读集 ∅ ⇒ 推断 0 参、无 `...`。
调用点 `push 7; push str; push this`（this 也压栈）⇒ push=3。
无调用点 ⇒ 🟡 错误声明；有调用点 ⇒ 要么"签名不匹配"挡下转换（🟢），要么 🔴。

### C-5 🔴 同体折叠 + 等价类不可分：`methods[addr]` 表达力不足
```cpp
struct E { virtual void o(int); virtual void o(void*); virtual void o(float); virtual void other(int); };
```
四个空体实测：`o(int)/o(void*)/o(float)` 三条 COMDAT **字节完全相同（`c2 04 00`）**
（`idi(int)`/`idp(void*)` 亦同）⇒ ICF 折叠后**一地址对 3 签名 3 槽**。
- §3.2 的 `methods[addr]` 按地址键控 ⇒ **放不下同地址多签名**；
- §5 表的缓解"按调用点栈槽数分账"对**同槽数**（1 槽 int / 1 槽指针 / 1 槽 float）**不可分**；
- 其中 **float vs int 属设计自认"必须区分"的维度**，但空体时 callee/调用点均无证据 ⇒
  A 级门禁照样写入错误等价类。调用实参是变量时（`p->o(f)`）int 声明会物化 cvt 代码 ⇒ 🔴。

### C-6 🔴 "int/DWORD/BOOL/enum/同宽指针字节等价" 被证伪（BOOL 不等价）
```cpp
struct SB { virtual void fb(bool); virtual void fi(int); };
void c2(SB* p, int i){ p->fb(i); p->fi(i); }
```
实测调用点：`p->fi(i)` = `push %edi`（2 字节）；`p->fb(i)` = `test edi,edi; setne cl; push ecx`
（**+5 字节的物化转换**）。`bool` 变量方向同样不同（`and $0xff`）。
⇒ 参数等价类**影响调用点字节**，BOOL 必须单独成类。错误等价类 + A 级写入 ⇒ 🔴。

---

## 攻击 4 —— §5.1 "双侧独立证据"

### D-1 🟡→🔴 签名维度上"双侧"是 f(证据) vs f(证据)，恒真
左侧"callee 侧签名证据"= vtable_sig_infer 的**输入**；右侧"从 methods 发射的声明"= 同一推断的
**输出** ⇒ 校验 3（声明签名 == callee 等价类推断结果）在签名维度恒真。
"不消费同一缓存"只是绕开缓存文件，**不构成独立信源**。独立性只存在于槽数/槽序维度。

### D-2 🔴 共享 ABI 模型 ⇒ 两侧同时出错且互相确认（C-2/C-3 实证）
同源不必是"同一份反编译"：两侧共用同一套参数传递模型（this 只在 ecx / 只数 push）时，
模型错 ⇒ callee 读集与调用点 push 数**独立地**给出同一个错误值并互相"验证"通过。

### D-3 🔴 同函数同反编译 + 反馈成环
递归虚函数（`virtual void f(int){ f(x-1); }`）的 callee 证据与调用点证据来自**同一份**伪代码；
更糟的是数据流成环：`methods → apply_annotations(IDB 原型) → Hex-Rays 反编译 → callee 证据
→ methods`。CLAUDE.md 明文"禁止仅凭 Hex-Rays 反编译文本推断偏移（除非 IDB 已 apply 且结构正确）"
——即伪代码**注解相关**。第二轮迭代会"自证"第一轮的错（比 v1 的同缓存循环更隐蔽）。
⇒ callee 证据必须落在**原始指令字节**上（reg+disp32 / push 序列的反汇编），不能落在 decomp JSON 上。

### D-4 🟡 ICF 共享代码体 ⇒ 两侧读同一段物理代码
折叠后一地址多符号，IDA/Hex-Rays 只见一个函数一份伪代码 ⇒ 与"同源"无异。

**两侧何时同时出错**：当错误来自共同上游（ABI 规则模型 / IDB this 归属 / IDA 函数边界 /
注解反馈）而非单次读数噪声时。⇒ 建议给签名维度引入第三方裁判：**用发射的 .obj 实测
prologue/epilogue/调用序列与二进制逐字节比对**（即把 L1 的签名维度前移），否则 §5.1 只能拦槽数/槽序错。

---

## 攻击 5 —— §3.4 布局断言

### E-1 🔴 被污染的断言常量会"判死"正确注解（`w1.cpp` / `w2.cpp`）
正确布局 `Inner{a,b,c}=12B`、`Outer{in,tag}` 的 `tag@+12`；断言常量来自**误归属的 A 级证据**
（this 归属错 ⇒ 把 `mov [ecx+10h]` 读成 Inner 成员 ⇒ sizeof=20）：
```cpp
typedef char a_tag[(offsetof(Outer, tag) == 20) ? 1 : -1];   // 实测 C2118
typedef char a_size[(sizeof(Inner) == 20) ? 1 : -1];         // 实测 C2118
```
错误处理表只有"布局断言失败 ⇒ 编译报错，定位到具体成员"，**没有"断言常量本身可疑"分支**
⇒ 工程师唯一"合规"出路是把正确注解改坏 ⇒ 全下游成员位移连环错 ⇒ 🔴。

### E-2 🔴 同源污染 ⇒ 错误注解编译通过（零判别力）
把注解也改成 20B（与污染模型自洽）+ 同源断言常量 ⇒ **编译通过**。
⇒ §3.4 只校验"头文件 vs 常量"，二者同源自同一次误读时，对"注解 vs 二进制"零判别力。
"断言常量源自二进制 A 级证据（非同源 annotation）"低估了同源性：**A 级是证据形态等级，
不是独立性等级** —— 常量与 annotation 常常来自同一条指令的同一次误读。

### E-3 🔴（停摆型）`offsetof` 虚基成员不是常量表达式（`p2/p3.cpp`）
实测 `offsetof(VOnly, vv)`（vv 在虚基 V1 里）⇒ **C2057 "expected constant expression"**
（偏移需运行期查 vbtable）。§3.4 **默认开启 + 全期持续** ⇒ 任何含虚基成员的类生成断言即
编译不过 ⇒ 管线停摆，或被迫 `--no-layout-assert` ⇒ 静默丢覆盖。
§6 的"非 POD offsetof 兼容性 1 例再批量"没覆盖这个**结构性**不可用（不是兼容性问题）。
（对照：非虚基成员 offsetof 在非 POD 类上是常量、可用 ✓）

### E-4 🔴（停摆型，选错档时）/🟡（规则封闭性）PMF 三档规则不封闭（`p3.cpp` 实测矩阵）

| 形状 | 实测 `sizeof(void (C::*)())` | 设计规则预测 |
|---|---|---|
| 单继承 | 4 | 4 ✓ |
| 多继承 2/3 基 | 8 | 8 ✓ |
| 仅虚继承 | 12 | 12 ✓ |
| **多继承 + 虚继承** | **12** | **无规则（8 还是 12？）** |
| 多继承 + 2 虚基 | 12 | 无规则 |
| 2 虚基（无非虚基） | 12 | 无规则 |

"单继承 4 / 多继承 8 / 虚继承 12"对同时命中"多继承"与"虚继承"的类**没有优先级**：
若先判多继承=8 ⇒ **C2118 假失败 ⇒ 停摆**。正确封闭规则："有虚基 ⇒ 12；否则基>1 ⇒ 8；否则 4"
（多个虚基仍是 12，不是 16）。

---

## 结论一览

| # | 用例 | 命中条款 | 后果 |
|---|---|---|---|
| A-1 | a2/r1 | §2.2 / §3.5-2 / §8.3 | 🔴 重发射 vtable 逐槽不匹配；校验 2 不可满足 ⇒ per-class-hard 永久阻塞 |
| A-2 | a1/a3/a4 | §2.2"组位置=首现位置" | 🔴 同名组跨继承边界分裂，规则失效 |
| A-3 | vt7/T3/t4 | §2.2 逆映射 | 🟡 声明序不可还原 |
| B-1..B-4 | c2 | §2.1 / §3.5-1 / §3.6 | 🟡 混合槽无 kind、1 声明↔多视图多槽、异己视图声明、动态 delta 不可归一（可升级 🔴） |
| C-1 | s1 | §3.2 步骤 3 | 🔴 未用参数 ⇒ 0 参 |
| C-2 | s1/s3 | §3.2 步骤 2 | 🔴 fastcall 无规则分支，三层无感 |
| C-3 | r2 | §3.2 步骤 3 | 🔴 this 入读集 ⇒ 两侧同时确认错误个数 |
| C-4 | s1 | §3.2 变参规则 | 🟡/🔴 无 `...`；mangle 特征 `QAA` 匹配不到 `UAA…ZZ` |
| C-5 | e1 | §3.2/§5 表 | 🔴 `methods[addr]` 表达力不足；同槽数签名不可分账 |
| C-6 | b1 | §3.2 等价类 | 🔴 BOOL≠int 字节等价 |
| D-1..D-4 | — | §5.1 | 🟡→🔴 签名维度恒真 / 共同上游同源 / 反馈成环 |
| E-1/E-2 | w1/w2 | §3.4 | 🔴 污染常量判死正确注解；同源零判别力 |
| E-3 | p2/p3 | §3.4 默认开启 | 🔴 虚基成员 offsetof 非常量 ⇒ 编译停摆 |
| E-4 | p3 | §3.4 PMF 断言 | 🔴/🟡 三档规则对 MI+虚继承不封闭（实测=12） |
