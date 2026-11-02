// 黄金夹具（2026-11-02）：布局全知的集成测试 exe——验证注解→Ghidra→丑C→编译全链
#include <cstdio>
#include <cstring>

extern const char* g_message;

struct Vec3 { float x, y, z; };

struct Complex {
    int id;
    Vec3 pos;                    // 内嵌 struct
    union { float fval; int ival; };   // 位面复用（inline union）
    char name[16];
};

class Base {
public:
    virtual ~Base();
    virtual int update(int dt);
    int m_baseVal;
};

class Derived : public Base {
public:
    virtual ~Derived();
    virtual int update(int dt);          // override
    virtual void render(Complex* c);
    Complex m_complex;
    Derived* m_pNext;
    int m_flags;
    int calc(int a, int b);              // 重载 1
    double calc(double a);               // 重载 2
};

Base::~Base() {}
int Base::update(int dt) { m_baseVal += dt; return m_baseVal; }

Derived::~Derived() {}
int Derived::update(int dt) { return Base::update(dt) + m_flags; }
void Derived::render(Complex* c) {
    c->pos.x = (float)c->id;
    c->ival = m_flags;
    strcpy(c->name, g_message);
}
int Derived::calc(int a, int b) { return a * b + m_flags; }
double Derived::calc(double a) { return (int)(a * 2.0); }

// 全局
Derived g_root;
int g_counter = 0;
const char* g_message = "hello from fixture";

void fixture_init() { g_root.m_baseVal = 0; g_root.m_flags = 7; g_root.m_pNext = 0; }
int fixture_get() { return g_counter; }
void fixture_tick(int n) {
    for (int i = 0; i < n; i++) g_counter += g_root.update(1) + g_root.calc(i, 2) + (int)g_root.calc(1.5);
}

int main() {
    fixture_init();
    Complex c; c.id = 3; c.fval = 0.0f;
    g_root.render(&c);
    fixture_tick(3);
    std::printf("%s counter=%d name=%s\n", g_message, fixture_get(), c.name);
    return 0;
}
