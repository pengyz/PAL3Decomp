// Task4 R=1（C-1）探针：**间接**虚基的成员 offsetof 也不是常量表达式（C2057）。
//
// 形状（评审给的实测反例）：V1 是 VB2 的虚基，VB2 是 IVB 的**非虚**基
//   struct V1  { virtual void v(); int vv; };
//   struct VB2 : virtual V1 { int x; };
//   struct IVB : VB2 { int dm; };
//
// 读法（真机 MSVC 6.0 SP0）：
//   tools/wine_cl.sh /c /nologo /O2 /GR /Itools/compilers/msvc6.0/Include \
//       /Fo/tmp/ivb.obj ivb.cpp
// 逐字输出（本轮实测）：
//   ivb.cpp(22) : error C2057: expected constant expression     ← offsetof(IVB, vv) 间接虚基
//   ivb.cpp(22) : error C2466: cannot allocate an array of constant size 0
//   ivb.cpp(25) : error C2118: negative subscript …             ← offsetof(IVB, x) 常量但值不是 8
//   ivb.cpp(26) : error C2118: negative subscript …             ← offsetof(IVB, dm) 常量但值不是 4
//   ivb.cpp(30) : error C2057 / C2466                           ← offsetof(DV, vv) 直接虚基（对照组）
//   ⇒ 只有**虚基区域**（22/30）出 C2057；非虚基/本类成员（25/26）只出 C2118（常量、值不符）
//
// 结论：R=0 的 `virtual_base_region` 只看**直接**虚基（IVB 的直接基 VB2 是**非虚**的）
// ⇒ 返回空集 ⇒ `offsetof(IVB, vv)` 被当作常量表达式 ⇒ 编译停摆。
#include <stddef.h>

struct V1  { virtual void v(); int vv; };
struct VB2 : virtual V1 { int x; };
struct IVB : VB2 { int dm; };

// 间接虚基的成员 ⇒ 不是常量表达式（本条会报 C2057）
typedef char t_ivb_vv[(offsetof(IVB, vv) == 0) ? 1 : -1];

// 对照：非虚基 VB2 的成员、本类成员仍是常量表达式（只报 C2118 值不符，**无** C2057）
typedef char t_ivb_x[(offsetof(IVB, x) == 8) ? 1 : -1];
typedef char t_ivb_dm[(offsetof(IVB, dm) == 4) ? 1 : -1];

// 直接虚基（对照组，R=0 已覆盖）⇒ C2057
struct DV : virtual V1 { int dm2; };
typedef char t_dv_vv[(offsetof(DV, vv) == 0) ? 1 : -1];
typedef char t_dv_dm2[(offsetof(DV, dm2) == 4) ? 1 : -1];

int main() { return 0; }