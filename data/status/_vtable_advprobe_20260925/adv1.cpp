// AD1: covariant return override in MI
struct Oth { int o; };
struct CB { virtual CB* clone(); virtual void f(); int b; };
struct CD : Oth, CB { virtual CD* clone(); int d; };
CB* CB::clone() { return this; }
void CB::f() {}
CD* CD::clone() { return this; }
int main() { CD d; CB* p = d.clone(); return 0; }
