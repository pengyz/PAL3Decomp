// 攻击3d: int vs 指针等价类 + 同体 ICF 折叠 + 同名重载坍缩
struct E {
    virtual void o(int);
    virtual void o(void*);
    virtual void o(float);
    virtual void other(int);
};
void E::o(int) {}
void E::o(void*) {}
void E::o(float) {}
void E::other(int) {}
int main() { E x; return 0; }
