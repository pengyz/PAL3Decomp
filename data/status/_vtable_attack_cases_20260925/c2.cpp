// 攻击2b: 虚继承 + MI + 虚析构 + 覆写虚基函数 + 同名重载
struct V { virtual ~V(); virtual void o(); int v_; };
struct A : virtual V { virtual ~A(); virtual void o(int); int a_; };
struct Bx { virtual ~Bx(); virtual void b(); int b_; };
struct D : A, Bx {
    virtual ~D();
    virtual void o();        // 覆写虚基虚函数（动态 thunk 路径）
    virtual void b();        // 覆写次基虚函数（静态 thunk 路径）
    virtual void o(double);  // 同名重载
    int d_;
};
V::~V() {} void V::o() {}
A::~A() {} void A::o(int) {}
Bx::~Bx() {} void Bx::b() {}
D::~D() {} void D::o() {} void D::b() {} void D::o(double) {}
int main() { D x; return 0; }
