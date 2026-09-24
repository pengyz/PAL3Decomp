// 判别实验: 插队者(w)在同名组中间 —— 单类 vs 派生类尾插两种形态
struct T4 { virtual void z(); virtual void o(char*); virtual void w(); virtual void o(short); };
void T4::z() {} void T4::o(char*) {} void T4::w() {} void T4::o(short) {}
struct B5 { virtual void q(); };
void B5::q() {}
struct D5 : B5 { virtual void z(); virtual void o(char*); virtual void w(); virtual void o(short); };
void D5::z() {} void D5::o(char*) {} void D5::w() {} void D5::o(short) {}
int main() { T4 a; D5 b; return 0; }
