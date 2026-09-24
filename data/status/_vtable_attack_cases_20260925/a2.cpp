// 攻击1b: 3 同名重载 + 中间插 1 不同名虚函数 + 继承链上同名覆写
struct Base {
    virtual void o();
    virtual void o(int);
    virtual void mid();
    virtual void o(double);
};
void Base::o() {} void Base::o(int) {} void Base::mid() {} void Base::o(double) {}
struct Der : Base {
    virtual void o(double);   // 同名覆写
    virtual void o(int);      // 同名覆写
    virtual void o(char*);    // 新增重载
    virtual void tail();
};
void Der::o(double) {} void Der::o(int) {} void Der::o(char*) {} void Der::tail() {}
int main() { Der x; return 0; }
