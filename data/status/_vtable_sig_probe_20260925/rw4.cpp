// vtable_sig_infer 金样本探针 #4 —— sret 阴性（别把"指针参数 + 大范围写"误判成 sret）
// 复现: tools/wine_cl.sh /c /Od /GR /Itools/compilers/msvc6.0/Include /Fo/tmp/rw4.obj \
//         data/status/_vtable_sig_probe_20260925/rw4.cpp && objdump -dr /tmp/rw4.obj
struct Inner { int a, b, c; };            // 12B，但**不是**返回值
struct Rn2 {
    virtual int  retp(Inner* p);          // 写 12B 后返回指针值 ⇒ 不得判 sret
    virtual int  retp2(int* p);           // 写 4B 后返回指针值 ⇒ 不得判 sret
    virtual void wr(Inner* p);            // 写 12B、void 返回 ⇒ 不得判 sret
    virtual Inner mk(int x);              // 真 sret（12B 结构返回）
};
int  Rn2::retp(Inner* p)  { p->a = 1; p->b = 2; p->c = 3; return (int)p; }
int  Rn2::retp2(int* p)   { *p = 7; return (int)p; }
void Rn2::wr(Inner* p)    { p->a = 1; p->b = 2; p->c = 3; }
Inner Rn2::mk(int x)      { Inner i; i.a = x; i.b = 0; i.c = 0; return i; }
// 追加：0 实参 sret（ret 4 = 仅 sret 指针）—— Ruling 6 的边界形态
struct Big16 { int a[4]; };
struct Rn3 { virtual Inner mk0(); virtual Big16 mk0b(); };;
Inner Rn3::mk0()   { Inner i; i.a = 1; i.b = 2; i.c = 3; return i; }
Big16 Rn3::mk0b()  { Big16 b; b.a[0]=1; b.a[1]=2; b.a[2]=3; b.a[3]=4; return b; }
