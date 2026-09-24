// vtable_sig_infer 金样本探针 #5 —— 真实项目编译开关 /O2 /Ob2 /Oi /Ot /Oy /GR（无帧指针）
// 复现: tools/wine_cl.sh /c /O2 /Ob2 /Oi /Ot /Oy /GR /Itools/compilers/msvc6.0/Include \
//         /Fo/tmp/opt1.obj data/status/_vtable_sig_probe_20260925/opt1.cpp && objdump -dr /tmp/opt1.obj
struct Op {
    int m;
    virtual void zero(int x);        // thiscall + 1 参 + ret 4
    virtual int  add1(int x);        // 返回 int
    virtual void freg(int a, int b); // 未使用参数（O2 下溢出可能被优化掉）
};
void Op::zero(int x){ m = 0; (void)x; }
int  Op::add1(int x){ return x + 1; }
void Op::freg(int a, int b){ m = 0; (void)a; (void)b; }
