// 攻击5: PMF 尺寸矩阵 + offsetof 虚基成员
struct A1 { virtual void f(); int a; };
struct B1 { virtual void g(); int b; };
struct V1 { virtual void v(); int vv; };
struct MI2 : A1, B1 { void h(); };                  // 多继承(非虚)
struct VOnly : virtual V1 { void h(); };            // 仅虚继承
struct MIV : A1, B1, virtual V1 { void h(); };      // 多继承 + 虚继承
struct Deep : virtual V1 { virtual void z(); };
struct MIV2 : Deep, B1 { void h(); };               // 虚继承在中间层 + MI
typedef char a_SI  [(sizeof(void (A1::*)())    == 4)  ? 1 : -1];
typedef char a_MI  [(sizeof(void (MI2::*)())   == 8)  ? 1 : -1];
typedef char a_VI  [(sizeof(void (VOnly::*)()) == 12) ? 1 : -1];
// 设计文档只有 4/8/12 三档，下面两个形状文档未定义：
typedef char a_MIV [(sizeof(void (MIV::*)())   == 12) ? 1 : -1];   // MI+虚继承=??
typedef char a_MIV2[(sizeof(void (MIV2::*)())  == 12) ? 1 : -1];   // 深虚继承+MI=??
int main() { return 0; }
