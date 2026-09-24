// vtable_sig_infer 金样本探针 #3 —— bool 返回物化 / __int64 返回 / 显式 thiscall 无溢出
// 复现: tools/wine_cl.sh /c /Od /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/rw3.obj \
//         data/status/_vtable_sig_probe_20260925/rw3.cpp && objdump -dr /tmp/rw3.obj
struct Rb {
    virtual bool    rbool(int x);      // setcc 物化
    virtual char    rchar(int x);      // 真 8 位
    virtual __int64 r64(int x);        // edx:eax
};
bool    Rb::rbool(int x){ return x != 0; }
char    Rb::rchar(int x){ return (char)x; }
__int64 Rb::r64(int x){ return (__int64)x; }
