// Task4 R=1（C-3）探针：PMF 尺寸不仅取决于**继承形状**，还取决于 **vfptr 引入点**。
//
// 读法（真机 MSVC 6.0 SP0，cl 12.00.8168）：
//   tools/wine_cl.sh /c /nologo /O2 /GR /FAs /Itools/compilers/msvc6.0/Include \
//       /Fo/tmp/pmf_intro.obj /Fa/tmp/pmf_intro.asm pmf_intro.cpp
//   grep -E '^\?' /tmp/pmf_intro.asm      # 常量由**编译器自己**算进 .data，不手抄
//
// 结论（见 README §1.1）：
//   4 字节 PMF 要求 vfptr 在**偏移 0**。基类非多态而派生类自己引入 vfptr 时，
//   MSVC 把 vfptr **排在基类子对象之后**（偏移 != 0）⇒ 8 字节表示。
//   ⇒ 单继承链也不再是"一律 4"；只看继承形状的规则会**假杀**（RoleCameraCtrl 实测 C2118）。
#include <stddef.h>

struct NP_A { int a; };              // 非多态
struct NP_B { int b; };              // 非多态
struct P_A  { virtual void f(); int a; };   // 多态（自带 vfptr）
struct P_B  { virtual void g(); int b; };

struct MI_NP  : NP_A, NP_B { int x; };              // 非多态多继承
struct MI_P   : P_A, P_B {};                        // 多态多继承
struct SI_P   : P_A {};                             // 多态基 ⇒ vfptr 在 0
struct SI_NP  : NP_A {};                            // 全非多态
struct INTRO  : NP_A { virtual void f(); int x; };  // ★ 非多态基 + 派生自己引入 vfptr
struct INTRO_D : INTRO {};                          // 载体是祖先
struct INTRO_D2 : INTRO { virtual void g(); };
struct NP_MID : NP_A {};
struct INTRO_MID : NP_MID { virtual void f(); };    // ★ 载体在中间层
struct DER_INTRO_MID : INTRO_MID {};
struct VB_NP  : virtual NP_A {};                    // 虚基（非多态基）
struct VB_P   : virtual P_A {};
struct MI_INTRO : NP_A, P_B { virtual void f(); };  // 混合

int p_MI_NP  = sizeof(void (MI_NP::*)());
int p_MI_P   = sizeof(void (MI_P::*)());
int p_SI_P   = sizeof(void (SI_P::*)());
int p_SI_NP  = sizeof(void (SI_NP::*)());
int p_INTRO  = sizeof(void (INTRO::*)());
int p_INTRO_D = sizeof(void (INTRO_D::*)());
int p_INTRO_D2 = sizeof(void (INTRO_D2::*)());
int p_INTRO_MID = sizeof(void (INTRO_MID::*)());
int p_DER_INTRO_MID = sizeof(void (DER_INTRO_MID::*)());
int p_VB_NP  = sizeof(void (VB_NP::*)());
int p_VB_P   = sizeof(void (VB_P::*)());
int p_MI_INTRO = sizeof(void (MI_INTRO::*)());

// 尺寸对照：vfptr 不在偏移 0 时，`sizeof` 同时 +4（INTRO = 8，而"基类多态"的 SI_P = 8）
int z_MI_NP  = sizeof(MI_NP);
int z_INTRO  = sizeof(INTRO);
int z_INTRO_D = sizeof(INTRO_D);
int z_DER_INTRO_MID = sizeof(DER_INTRO_MID);
int z_VB_NP  = sizeof(VB_NP);
int z_MI_INTRO = sizeof(MI_INTRO);

int main() { return 0; }