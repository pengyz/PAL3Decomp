// AD3: const-qualifier overloads + deleting-dtor inside name group
struct C3 { virtual ~C3(); virtual void o() const; virtual void o(int); int z; };
C3::~C3() {}
void C3::o() const {}
void C3::o(int) {}
int main() { C3 c; return 0; }
