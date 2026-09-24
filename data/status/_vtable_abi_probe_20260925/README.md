# MSVC6 SP0 vtable ABI 探针（2026-09-25，设计审计证据）

编译器：`tools/compilers/msvc6.0` cl 12.00.8168（wine_cl.sh），`/O2 /Ob2 /Oi /Ot /Oy /GR`（vt6/vt7 用 `/Od` 强制发射）。
vtable 读取：`tools/coff_vtable.py` 的 `parse_obj`（按原始 COFF 索引解 reloc）。
本目录为**未跟踪草稿**，可作为 `vtable_decl_check` / `vtable_verify` / `vtable_sig_infer` 的回归金样本；不需要时可整目录删除。

## 实测结论（每条均可由对应源文件复现）

| # | 形态 | 源文件 | 实测 |
|---|---|---|---|
| 1 | MI 多 vptr | vt2.cpp (`D : A, B`) | 两张表 `??_7D@@6BA@@@` / `??_7D@@6BB@@@`，各自 [-1]=`??_R4D@@6B{A,B}@@@`（COL）；**无 offset-to-top 槽**；新增虚函数 `m` 只追加到主表尾；次表只含 B 的槽 |
| 2 | 覆写次基虚函数 | vt2.cpp (`D::h`) | **不生成 thunk**：`?h@D@@UAEHXZ` 本体按 `this`=B 子对象编译（`mov 0x8(%ecx)` 读 d）；槽直接指向本体。wine 运行验证语义正确 |
| 3 | 一函数服务两个子对象槽 | vt3.cpp (`D3::ff`) | 主表槽=`?ff@D3@@UAEHXZ`，次表槽=**静态 adjustor thunk** `?ff@D3@@W7AEHXZ`（`W<n>` 修饰） |
| 4 | 虚继承（无虚析构） | vt2.cpp (`DV : virtual V`) | 独立 **vbtable** `??_8DV@@7B@`（内容 [0]=0,[1]=8）+ vbptr 成员；表槽直接指向 `?v@DV@`（this=V 子对象） |
| 5 | 虚继承+虚析构 | vtprobe/vt2 系 (`DV2`) | 表槽=**动态 adjustor thunk** `?w@DV2@@$4PPPPPPPM@A@AEXXZ`（`sub -0x4(%ecx),%ecx; jmp 本体`）；函数体内另有 vbtable 访问形态 `mov -0xc(%ecx)` |
| 6 | 纯虚 | q2a/q2b.cpp | 槽指向 **`__purecall` 外部符号**；且抽象类 vtable 为**惰性 COMDAT 发射**——vptr 未被写入的 TU 里 `??_7Q2` 根本不出现（多轮探针实测 ??_7O/??_7P/??_7A/??_7B/??_7Q 均缺失） |
| 7 | 虚析构 | vtprobe.cpp (`X`,`V2`) | **每个虚析构只占 1 槽**：槽=deleting dtor（obj 里 `??_E` vector deleting，弱别名 `??_G` scalar deleting，签名 `void*(unsigned)`）；complete dtor `??1X` 不进表。提问前提"complete+deleting 两条目"不符合本编译器 |
| 8 | 同名重载 | vt6/vt7.cpp | 槽序 ≠ 声明序：**同名组内为声明顺序的逆序**，整组占据首个同名声明的槽位区段。T1 decl[o(),o(int),o(double)]→槽[o(double),o(int),o()]；O 4 个重载完全逆序；T3 decl[p,o(int),q,o(double)]→槽[p,o(double),o(int),q] |
| 9 | 多态性断言 | vt5.cpp | 设计文档提议的 `typedef char a[(sizeof(void (C::*)())==4)?1:-1]`：单继承通过；**MI 与虚继承均 C2118 负数组编译失败**（pmfn 尺寸 8/更大） |

## 复现

```sh
VC=tools; INC=tools/compilers/msvc6.0/Include
$VC/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR /I$INC /Fovt2.obj vt2.cpp
python3 -c "import sys; sys.path.insert(0,'tools'); import coff_vtable as cv; ..."  # 见会话记录
```
