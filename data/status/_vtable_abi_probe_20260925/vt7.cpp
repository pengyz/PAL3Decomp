// T1: overloads, decl order o(), o(int), o(double)
struct T1 { virtual void o(); virtual void o(int); virtual void o(double); int z; };
void T1::o() {} void T1::o(int) {} void T1::o(double) {}
// T2: control, distinct names a,b,c,d
struct T2 { virtual void a(); virtual void b(); virtual void c(); virtual void d(); int z; };
void T2::a() {} void T2::b() {} void T2::c() {} void T2::d() {}
// T3: overloads with a distinct-name virtual interleaved
struct T3 { virtual void p(); virtual void o(int); virtual void q(); virtual void o(double); int z; };
void T3::p() {} void T3::o(int) {} void T3::q() {} void T3::o(double) {}
int main() { T1 a; T2 b; T3 c; return 0; }
