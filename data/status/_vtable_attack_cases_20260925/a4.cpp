// 攻击1d: 派生类新增 2 个同名重载（跨边界的"新组"内部是否也逆序）
struct B4 {
    virtual void p();
    virtual void q();
};
void B4::p() {} void B4::q() {}
struct D4 : B4 {
    virtual void z();
    virtual void o(char*);   // 新增重载 1
    virtual void o(short);   // 新增重载 2
};
void D4::z() {} void D4::o(char*) {} void D4::o(short) {}
int main() { D4 x; return 0; }
