// vtable_sig_infer 金样本探针 #1 —— 返回宽度 / sret / fastcall / stdcall
// 复现: tools/wine_cl.sh /c /Od /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/rw1.obj \
//         data/status/_vtable_sig_probe_20260925/rw1.cpp && objdump -dr /tmp/rw1.obj
struct Big { int a[4]; };                       // 16B > 8B ⇒ sret 隐藏首参
struct Rn {
    int m;
    virtual int   ri(int x);                    // 32 位返回
    virtual char  rc(int x);                    // 8 位返回
    virtual short rs(int x);                    // 16 位返回
    virtual float rf(int x);                    // x87 返回
    virtual void  rv(int x);                    // void 返回
    virtual Big   rb(int x);                    // sret
    virtual void __cdecl   cv(int x);           // cdecl 成员（this 在栈）
    virtual void __fastcall f1(int x);          // fastcall 成员（ecx=this, edx=x, 裸 ret）
    virtual void           f0(int x);           // thiscall 有参
    virtual void           f0u();               // thiscall 0 参（裸 ret ⇒ 与 cdecl 形同）
};
int   Rn::ri(int x){ return x; }
char  Rn::rc(int x){ return (char)x; }
short Rn::rs(int x){ return (short)x; }
float Rn::rf(int x){ return (float)x; }
void  Rn::rv(int x){ m = x; }
Big   Rn::rb(int x){ Big b; b.a[0]=x; b.a[1]=0; b.a[2]=0; b.a[3]=0; return b; }
void __cdecl   Rn::cv(int x){ m = x; }
void __fastcall Rn::f1(int x){ m = x; }
void Rn::f0(int x){ m = x; }
void Rn::f0u(){ m = 1; }
