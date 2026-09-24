// SYN probes: where does the deleting-dtor slot land when NOT declared first?
struct P1 { virtual void o(); virtual ~P1(); virtual void o(int); };
void P1::o() {} P1::~P1() {} void P1::o(int) {}

struct P2 { virtual void o() const; virtual ~P2(); virtual void o(int); };
void P2::o() const {} P2::~P2() {} void P2::o(int) {}

struct P2b { virtual void o(); virtual void o(int); virtual ~P2b(); virtual void o(double); };
void P2b::o() {} void P2b::o(int) {} P2b::~P2b() {} void P2b::o(double) {}

struct B5 { virtual void a(); };
void B5::a() {}
struct D5 : B5 { virtual void o(); virtual ~D5(); virtual void o(int); };
void D5::o() {} D5::~D5() {} void D5::o(int) {}

struct B6 { virtual void a(); };
void B6::a() {}
struct D6 : B6 { virtual void x(); virtual void y(int); virtual void z(); virtual void y(double); };
void D6::x() {} void D6::y(int) {} void D6::z() {} void D6::y(double) {}

struct B7 { virtual ~B7(); virtual void f(); };
B7::~B7() {} void B7::f() {}
struct D7 : B7 { virtual ~D7(); virtual void g(); };
D7::~D7() {} void D7::g() {}

struct B8 { virtual void f(); virtual ~B8(); virtual void h(); };
void B8::f() {} B8::~B8() {} void B8::h() {}
struct D8 : B8 { virtual ~D8(); virtual void g(); };
D8::~D8() {} void D8::g() {}

struct B9 { virtual void o(int); };
void B9::o(int) {}
struct D9 : B9 { virtual void o(char*); virtual void o(int); virtual void o(short); };
void D9::o(char*) {} void D9::o(int) {} void D9::o(short) {}

int main() { P1 a; P2 b; P2b c; D5 d; D6 e; D7 f; D8 g; D9 h; return 0; }
