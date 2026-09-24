// vtable_sig_infer 金样本探针 #2 —— f32 vs f64 返回是否可由 callee 字节区分
// 复现: tools/wine_cl.sh /c /Od /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/rw2.obj \
//         data/status/_vtable_sig_probe_20260925/rw2.cpp && objdump -dr /tmp/rw2.obj
struct Rf {
    virtual float  rf(int x);
    virtual double rd(int x);
    virtual float  rfq(double x);   // 参数 double 占 2 槽
};
float  Rf::rf(int x){ return (float)x; }
double Rf::rd(int x){ return (double)x; }
float  Rf::rfq(double x){ return (float)x; }
