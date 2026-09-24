// AD4: derived adds TWO new same-name overloads + one distinct name (tail ordering)
struct B3 { virtual void a(); int b; };
struct D3 : B3 { virtual void x(); virtual void y(int); virtual void y(double); int d; };
void B3::a() {}
void D3::x() {}
void D3::y(int) {}
void D3::y(double) {}
int main() { D3 d; return 0; }
