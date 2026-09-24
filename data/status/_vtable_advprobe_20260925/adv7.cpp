// AD7: virtual call on virtual-base subobject inside ctor (vtordisp territory)
struct V { virtual void f(); virtual ~V(); int v; };
struct DV : virtual V { DV(); ~DV(); void f(); int d; };
V::~V() {}
DV::DV() { f(); }
DV::~DV() {}
void V::f() {}
void DV::f() {}
int main() { DV d; return 0; }
