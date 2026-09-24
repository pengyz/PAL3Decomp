// 攻击2: 虚继承 + 多重继承 + 虚析构 + 同名重载 + 协变返回 + 覆写虚基虚函数
struct CVBase { virtual CVBase* clone(); virtual void o(); int cv; };
struct CVDer : CVBase { virtual CVDer* clone(); virtual void o(int); int cvd; };  // 协变返回 + 新增重载
CVBase* CVBase::clone() { return this; } void CVBase::o() {}
CVDer* CVDer::clone() { return this; } void CVDer::o(int) {}
int main() { CVDer x; return 0; }
