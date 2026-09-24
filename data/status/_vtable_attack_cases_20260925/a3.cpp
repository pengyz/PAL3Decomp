// 攻击1c: 派生类只新增同名重载（无覆写），看新槽插在基类组区段内还是表尾
struct B3 {
    virtual void p();
    virtual void o(int);
    virtual void o(double);
    virtual void q();
};
void B3::p() {} void B3::o(int) {} void B3::o(double) {} void B3::q() {}
struct D3 : B3 {
    virtual void z();
    virtual void o(char*);   // 新增同名重载
};
void D3::z() {} void D3::o(char*) {}
int main() { D3 x; return 0; }
