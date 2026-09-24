// 攻击5c: PMF 尺寸矩阵（形状 x 候选值），看设计的 4/8/12 三档是否完备
#include <stddef.h>
struct A1 { virtual void f(); int a; };
struct B1 { virtual void g(); int b; };
struct C1 { virtual void c(); int c_; };
struct V1 { virtual void v(); int vv; };
struct V2 { virtual void w(); int ww; };
struct SI   : A1 { void h(); };                        // 单继承
struct MI2  : A1, B1 { void h(); };                    // 纯多继承
struct VOnly: virtual V1 { void h(); };                // 仅一个虚基
struct MIV  : A1, B1, virtual V1 { void h(); };        // MI + 虚继承
struct MIVV : A1, virtual V1, virtual V2 { void h(); };// MI + 两个虚基
struct VV   : virtual V1, virtual V2 { void h(); };    // 两个虚基（无非虚基）
struct MI3  : A1, B1, C1 { void h(); };                // 三基
// 候选值探测：每行一个 (形状, 期望值)；编译失败=C2118 说明该期望值错
typedef char t_SI4   [(sizeof(void (SI::*)())    == 4)  ? 1 : -1];
typedef char t_MI28  [(sizeof(void (MI2::*)())   == 8)  ? 1 : -1];
typedef char t_VI12  [(sizeof(void (VOnly::*)()) == 12) ? 1 : -1];
typedef char t_MIV8  [(sizeof(void (MIV::*)())   == 8)  ? 1 : -1];
typedef char t_MIV12 [(sizeof(void (MIV::*)())   == 12) ? 1 : -1];
typedef char t_MIVV8 [(sizeof(void (MIVV::*)())  == 8)  ? 1 : -1];
typedef char t_MIVV12[(sizeof(void (MIVV::*)())  == 12) ? 1 : -1];
typedef char t_MIVV16[(sizeof(void (MIVV::*)())  == 16) ? 1 : -1];
typedef char t_VV12  [(sizeof(void (VV::*)())    == 12) ? 1 : -1];
typedef char t_VV16  [(sizeof(void (VV::*)())    == 16) ? 1 : -1];
typedef char t_MI38  [(sizeof(void (MI3::*)())   == 8)  ? 1 : -1];
// offsetof：本类成员 / 虚基类成员
typedef char t_off1 [(offsetof(VOnly, vv) == 8)  ? 1 : -1];  // 虚基成员
typedef char t_off2 [(offsetof(MI2, b)   == 8)  ? 1 : -1];   // 次基成员
int main() { return 0; }
