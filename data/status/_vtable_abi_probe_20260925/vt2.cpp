#include <stdio.h>
struct A { virtual int f(); virtual int g(int); int a; };
struct B { virtual int h(); virtual int k(double); int b; };
struct D : A, B {
    virtual int f();
    virtual int h();      // override secondary-base virtual -> expect adjustor thunk
    virtual int m();      // new virtual
    int d;
};
int A::f() { return a; }  int A::g(int x) { return x; }
int B::h() { return b; }  int B::k(double x) { return (int)x; }
int D::f() { return a + d; }
int D::h() { return d; }        // uses this (D layout)
int D::m() { return d; }

struct V { virtual int v(); int v_; };
struct DV : virtual V { virtual int v(); int d_; };
int V::v() { return v_; }
int DV::v() { return d_; }      // needs dynamic vbase adjust

struct Q { Q() { q = 1; } virtual int p() = 0; virtual int r(); int q; };
int Q::r() { return q; }
struct DQ : Q { virtual int p(); };
int DQ::p() { return 2; }

int main() {
    D d; d.a = 1; d.b = 2; d.d = 4;
    A *pa = &d; B *pb = &d;
    printf("obj=%p pa=%p pb=%p\n", (void*)&d, (void*)pa, (void*)pb);
    printf("f=%d h_viaB=%d m=%d\n", pa->f(), pb->h(), d.m());
    DV dv; dv.v_ = 7; dv.d_ = 9;
    V *pv = &dv;
    printf("dv=%p pv=%p v=%d\n", (void*)&dv, (void*)pv, pv->v());
    DQ dq; Q *pq = &dq;
    printf("p=%d r=%d\n", pq->p(), pq->r());
    return 0;
}
