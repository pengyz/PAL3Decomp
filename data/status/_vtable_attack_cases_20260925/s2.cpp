// 攻击3b: 两个类的空函数体字节相同（ICF 折叠候选），签名不同
struct P1 { virtual void a(int, int); };
struct P2 { virtual void b(); };
void __cdecl P1::a(int, int) {}   // 强制 __cdecl => 本体裸 ret
void P2::b() {}                    // thiscall 0 参 => 裸 ret
int main() { P1 x; P2 y; x.a(1,2); y.b(); return 0; }
