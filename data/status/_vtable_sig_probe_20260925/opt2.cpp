// vtable_sig_infer 金样本探针 #6 —— stdcall/cdecl/fastcall 成员在 /O2 /Oy 下的形态
// 复现: tools/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR /Itools/compilers/msvc6.0/Include \
//         /Fo/tmp/opt2.obj data/status/_vtable_sig_probe_20260925/opt2.cpp && objdump -dr /tmp/opt2.obj
struct Os {
    int m;
    virtual void __stdcall  sd(int x);        // this 在栈 + callee 清栈
    virtual void __cdecl    cd(int x);        // this 在栈 + caller 清栈
    virtual void __fastcall fe(int x);        // ecx=this, edx=x（x 被使用 ⇒ edx 可见）
    virtual void __fastcall fu(int x);        // x 未用 ⇒ /O2 下 edx 证据消失（已知盲区）
    virtual int  t2(int a, int b);            // thiscall 2 参（a/b 都被用）
};
void __stdcall  Os::sd(int x){ m = x; }
void __cdecl    Os::cd(int x){ m = x; }
void __fastcall Os::fe(int x){ m = x; }
void __fastcall Os::fu(int x){ m = 0; (void)x; }
int  Os::t2(int a, int b){ return a + b; }
