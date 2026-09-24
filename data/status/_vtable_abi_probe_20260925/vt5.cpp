struct A { virtual void f(); int a; };
struct B { virtual void h(); int b; };
struct D : A, B { virtual void f(); virtual void h(); int d; };
struct V { virtual void v(); int v_; };
struct DV : virtual V { virtual void v(); int d_; };
struct S : A { virtual void f(); int s; };          // single inheritance control

// design doc's proposed assert, applied per class:
typedef char _assert_S[(sizeof(void (S::*)()) == 4) ? 1 : -1];   // expect pass
//typedef char _assert_D[(sizeof(void (D::*)()) == 4) ? 1 : -1];   // MI: expect FAIL
typedef char _assert_DV[(sizeof(void (DV::*)()) == 4) ? 1 : -1]; // virtual inh: expect FAIL
int main() { return 0; }
