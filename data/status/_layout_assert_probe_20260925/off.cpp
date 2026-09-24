// Task4 复核：offsetof 在各类继承形态下的可用性（哪类成员必须跳过）
#include <stddef.h>
struct A1 { virtual void f(); int a; };
struct V1 { virtual void v(); int vv; };
struct N  : A1 { int n; };                       // 普通单继承
struct NV : A1, virtual V1 { int x; };           // 有虚基：非虚基成员 / 本类成员
struct DV : virtual V1 { int dm; virtual void q(); };
struct VBase2 : V1 { int w; };                   // V1 的非虚派生（V1 本身不是虚基）
struct DV2 : virtual VBase2 { int dm2; };        // 虚基是 VBase2（其内 w 来自 V1）
// 每组一个候选；编译失败 = 该 offsetof 不是常量表达式(C2057)或值不符
typedef char o1[(offsetof(N, a)  == 4)  ? 1 : -1];   // 非虚基成员（非 POD）
typedef char o2[(offsetof(N, n)  == 8)  ? 1 : -1];   // 本类成员（非 POD 单继承）
typedef char o3[(offsetof(NV, a) == 4)  ? 1 : -1];   // 有虚基类里的非虚基成员
typedef char o4[(offsetof(NV, x) == 8)  ? 1 : -1];   // 有虚基类的本类成员
typedef char o5[(offsetof(NV, vv) == 12) ? 1 : -1];  // 虚基成员  ← 预期 C2057
typedef char o6[(offsetof(DV, dm) == 4)  ? 1 : -1];  // 虚继承类的本类成员
typedef char o7[(offsetof(DV, vv) == 8)  ? 1 : -1];  // 虚基成员  ← 预期 C2057
typedef char o8[(offsetof(DV2, w) == 8)  ? 1 : -1];  // 虚基的非虚基之成员 ← ?
typedef char o9[(offsetof(DV2, dm2) == 4) ? 1 : -1]; // 虚继承类的本类成员
struct SZ { virtual void f(); int a; };              // sizeof 断言不涉及 offsetof
typedef char o10[(sizeof(SZ) == 8) ? 1 : -1];
int main() { return 0; }
