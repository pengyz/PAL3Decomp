struct A3 { virtual int ff(); virtual int onlyA(); int a; };
struct B3 { virtual int ff(); virtual int onlyB(); int b; };
struct D3 : A3, B3 { virtual int ff(); int d; };  // one body overrides BOTH bases at different this
int A3::ff() { return a; }  int A3::onlyA() { return a; }
int B3::ff() { return b; }  int B3::onlyB() { return b; }
int D3::ff() { return d; }
int main() {
    D3 d; d.a=1; d.b=2; d.d=4;
    A3 *pa=&d; B3 *pb=&d;
    return pa->ff() + pb->ff();   // expect 8
}
