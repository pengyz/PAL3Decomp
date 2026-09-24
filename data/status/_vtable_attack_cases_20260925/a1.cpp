struct B {
    virtual void f();
    virtual void o(int);
    virtual void o(double);
    virtual void g();
};
void B::f() {} void B::o(int) {} void B::o(double) {} void B::g() {}
struct D : B {
    virtual void o(float);   // 新增重载，名字与基类组相同
    virtual void o(char);    // 再加一个
    virtual void h();
};
void D::o(float) {} void D::o(char) {} void D::h() {}
int main() { D x; return 0; }
