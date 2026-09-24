# vtable_sig_infer 金样本探针（2026-09-25，Task 3）

本目录是 `tools/vtable_sig_infer.py`（候选签名生成器）**全部测试夹具的出处**。
每条夹具都是真机 MSVC 6.0 SP0（`tools/wine_cl.sh`，cl 12.00.8168）编译 + objdump
**原始指令字节**反汇编的逐字输出（**禁止 decomp JSON**）。

## 复现

```sh
cd /home/peng/workspace/PAL3Decomp
# 一键复现 + 与 tests/test_vtable_sig_infer.py 的夹具逐指令比对（需 wine/objdump）
python3 data/status/_vtable_sig_probe_20260925/verify_fixtures.py
```

⚠️ 依赖：脚本还会编译 `data/status/_vtable_attack_cases_20260925/` 的 `s1/s3/r2/e1/b1.cpp`
（C-1~C-6 用例源，属 Task 1/2 范围，**当前未入库**）—— 缺该目录时脚本报错退出（不静默通过）。

单独编译某个探针：

```sh
# /Od 探针（rw1-rw4）
tools/wine_cl.sh /c /Od /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/rw1.obj \
    data/status/_vtable_sig_probe_20260925/rw1.cpp && objdump -dr /tmp/rw1.obj
# /O2 探针（opt1/opt2：真实项目开关 /O2 /Ob2 /Oi /Ot /Oy /GR，无帧指针）
tools/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/opt1.obj \
    data/status/_vtable_sig_probe_20260925/opt1.cpp && objdump -dr /tmp/opt1.obj
```

## 探针清单与用途

| 文件 | 开关 | 证明什么 |
|---|---|---|
| `rw1.cpp` | /Od | 返回宽度（i32/i8/i16/void/未知）、x87 返回、**sret**（16B 结构返回隐藏首参）、cdecl 成员（this 在栈）、fastcall 成员（edx 溢出 + **裸 ret**）、thiscall 0 参（裸 ret 与 cdecl 形同 ⇒ 靠 ecx 证据分开） |
| `rw2.cpp` | /Od | `float rf(int)` 与 `double rd(int)` **逐字节同形**（`fildl`）⇒ f32/f64 不可分；`fldl`+`fsts` 宽度可见 ⇒ 可判；qword 载入认出 double 参数（2 槽） |
| `rw3.cpp` | /Od | `bool` 返回是 `setcc %al` 物化（与 `char` 的 `mov ...,%al` 形不同）；`__int64` 返回 `cltd`（只看 32 位 eax 会误判 int） |
| `rw4.cpp` | /Od | **sret 阴性**：`int retp(Inner* p){写12B; return (int)p;}` 与真 sret **只差基址寄存器个数** ⇒ 必须 `sret_ambiguous` 降级而不是猜；`retp2`（只写4B）与 `wr`（void）不得判 sret；`mk0/mk0b`（0 实参 sret）必须判出 |
| `opt1.cpp` | /O2 /Oy | 真实开关下 this **不溢出**（`0x4(%ecx)` 成员写 = thiscall 证据）；esp 相对栈参（无帧指针）；`ret 4` 槽数 |
| `opt2.cpp` | /O2 /Oy | `__stdcall` 成员（`ret 8`，this 在栈）vs `__cdecl` 成员（裸 `ret`）**只差清栈方**；fastcall 成员 `/O2` 下 edx 作源（`mov %edx,0x4(%ecx)`）仍可判；**fastcall 未用实参盲区**（`?fu` 与 thiscall 0 参逐字节同形） |

`_vtable_attack_cases_20260925/`（C-1~C-6 攻击用例源）与 `_vtable_abi_probe_20260925/`
是 Task 1/2 的既有金样本，本任务直接复用了 `s1.cpp`/`s3.cpp`/`r2.cpp`/`e1.cpp`/`b1.cpp`。

## 实测要点（供后续任务引用）

1. `?unused@S@@UAEXHH@Z`（thiscall，未用参数）本体 11 字节、读集 ∅、`ret 8`
   ⇒ 读集单独只能给 0 参（真值 2）；`ret N/4` 才是槽数证据。
2. `?freg@S@@UAIXHH@Z`（fastcall）`sub $8,%esp; mov %edx,-8(%ebp); mov %ecx,-4(%ebp); ret 4`
   ⇒ 成员 fastcall = ecx:this + edx:首实参 + 栈其余；调用点 `push $2; mov $1,%edx; lea -4(%ebp),%ecx`
   ⇒ push 计数只有 1（单侧证据必错）。
3. `?cf@Xc@@UAAXH@Z`（cdecl 成员）读 `[ebp+8]=this`、`[ebp+0xc]=x` ⇒ 读集 2（真值 1 参）；
   调用点 `push 1; push this` ⇒ push 2（两侧同错）。
4. `?log@S@@UAAXPBDZZ`：虚变参 mangling **`UAA…ZZ`**（设计文档写的 `QAA` 匹配不到）。
5. `?o@E@@UAEXH@Z` / `?o@E@@UAEXPAX@Z` / `?o@E@@UAEXM@Z` **13 字节完全相同**
   ⇒ ICF 折叠后一地址对 3 签名 3 槽。
6. `?fb@SB@@UAEX_N@Z` 与 `?fi@SB@@UAEXH@Z` 本体逐字节相同；BOOL 只在**调用点**可见：
   `p->fb(i)` = `xor %eax,%eax; cmpl $0x0,0xc(%ebp); setne %al; push %eax`（比裸 `push` 多 5 字节）。
7. `?rb@Rn@@UAE?AUBig@@H@Z`（16B 结构返回）与 `?retp@Rn2@@UAEHPAUInner@@@Z`（int 返回、
   经指针写 12B）在"末次 eax 载入首槽 + ≥9 字节 store-through"上**同形** ⇒ 唯一区别是
   store-through 的**基址寄存器个数**（真 sret = 1）与 `ret N`；判不出时必须降级。
8. `/O2 /Oy` 下 `?fu@Os@@UAIXH@Z`（fastcall、实参未用）与 thiscall 0 参**逐字节同形**
   ⇒ 寄存器实参漏检是**结构性盲区**，只能标 `real_param_blind_spot` + arity 下界。

## 方法可信度与已知缺口

* 全部 38 条夹具（36 个函数 + 3 个调用点片段）经 `verify_fixtures.py` 与真机 objdump 输出
  **逐指令（mnem + 操作数）比对一致**（仅对跳转/call 的地址文本做归一，因为夹具重写过地址）。
* 缺口 1：探针均为**独立小 TU**的 COMDAT 切片，与真实 PAL3.exe 的 `/O2` 内联/寄存器分配
  不保证同形 ⇒ 真实二进制的 A 级比例需在 PAL3.exe 上实测（本任务不做）。
* 缺口 2：`ret N` 只给栈**字节数**；无 qword 证据时 `arity` 是槽数估计（带
  `hidden_param_suspicion`），double/`__int64`/按值结构会占双槽。
* 缺口 3：`fildl`（整数→x87）形态的返回宽度 f32/f64 不可分（`rw2.cpp` 实测同体）。
* 缺口 4：多返回路径函数只取**最后**一个 `ret`；尾部 `jmp` 尾调用形态不看。