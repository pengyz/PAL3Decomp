// Task4 复核：PMF 尺寸封闭规则（含"直接基是 MI 类"的关键边界）
#include <stddef.h>
struct A1 { virtual void f(); int a; };
struct B1 { virtual void g(); int b; };
struct C1 { virtual void c(); int c_; };
struct V1 { virtual void v(); int vv; };
struct V2 { virtual void w(); int ww; };
struct SI    : A1 { void h(); };
struct MI2   : A1, B1 { void h(); };
struct MI3   : A1, B1, C1 { void h(); };
struct VOnly : virtual V1 { void h(); };
struct MIV   : A1, B1, virtual V1 { void h(); };
struct MIVV  : A1, virtual V1, virtual V2 { void h(); };
struct VV    : virtual V1, virtual V2 { void h(); };
struct DERofMI2 : MI2 { void h(); };          // 单直接基，但基是 MI
struct DERofSI  : SI  { void h(); };          // 深链单继承
struct DERofV   : VOnly { void h(); };        // 基含虚基
struct DERofDERofMI2 : DERofMI2 { void h(); };
// 每条 (形状, 候选值)；编译失败 = C2118 ⇒ 该候选值错
typedef char t_SI4     [(sizeof(void (SI::*)())     == 4)  ? 1 : -1];
typedef char t_SI8     [(sizeof(void (SI::*)())     == 8)  ? 1 : -1];
typedef char t_MI28    [(sizeof(void (MI2::*)())    == 8)  ? 1 : -1];
typedef char t_MI38    [(sizeof(void (MI3::*)())    == 8)  ? 1 : -1];
typedef char t_VOnly12 [(sizeof(void (VOnly::*)())  == 12) ? 1 : -1];
typedef char t_MIV12   [(sizeof(void (MIV::*)())    == 12) ? 1 : -1];
typedef char t_MIVV12  [(sizeof(void (MIVV::*)())   == 12) ? 1 : -1];
typedef char t_VV12    [(sizeof(void (VV::*)())     == 12) ? 1 : -1];
typedef char t_DERofMI2_4  [(sizeof(void (DERofMI2::*)()) == 4)  ? 1 : -1];
typedef char t_DERofMI2_8  [(sizeof(void (DERofMI2::*)()) == 8)  ? 1 : -1];
typedef char t_DERofMI2_12 [(sizeof(void (DERofMI2::*)()) == 12) ? 1 : -1];
typedef char t_DERofSI_4   [(sizeof(void (DERofSI::*)())  == 4)  ? 1 : -1];
typedef char t_DERofV_4    [(sizeof(void (DERofV::*)())   == 4)  ? 1 : -1];
typedef char t_DERofV_12   [(sizeof(void (DERofV::*)())   == 12) ? 1 : -1];
typedef char t_DERofDERofMI2_4 [(sizeof(void (DERofDERofMI2::*)()) == 4) ? 1 : -1];
typedef char t_DERofDERofMI2_8 [(sizeof(void (DERofDERofMI2::*)()) == 8) ? 1 : -1];
int main() { return 0; }
