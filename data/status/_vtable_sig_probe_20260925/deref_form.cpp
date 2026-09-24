// C1 修复轮 R=1 探针：deref 形态的两种真值逐字节相同（真机 /O2 /Ob2 /Oi /Ot /Oy /GR）
// 复现：tools/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/deref_form.obj deref_form.cpp
// 真值：?wr2@Rn6@@UAEHPAUInnerV@@@Z = __thiscall / 1 指针参 / int
//       ?g@C@@UAGHXZ            = __stdcall 成员 / 0 参
// 两者字节相同：8b 44 24 04 / c7 40 04 01 / c7 40 0c 03 / 33 c0 / c2 04 00
struct InnerV { int a; int b; int c; int d; };       // 无 vptr ⇒ b@+4, d@+0xc
struct Rn6 { virtual int wr2(InnerV* p); };
int Rn6::wr2(InnerV* p) { p->b = 1; p->d = 3; return 0; }
struct C { int p0; int p1; int p2; virtual int __stdcall g(); };  // 含 vptr ⇒ p0@+4, p2@+0xc
int __stdcall C::g() { this->p0 = 1; this->p2 = 3; return 0; }
