#include <cstdio>
#include <cstddef>
struct Vec3 { float x, y, z; };
struct Complex {
    int id; Vec3 pos;
    union { float fval; int ival; };
    char name[16];
};
class Base { public: virtual ~Base(); virtual int update(int dt); int m_baseVal; };
class Derived : public Base {
public:
    virtual ~Derived(); virtual int update(int dt); virtual void render(Complex* c);
    Complex m_complex; Derived* m_pNext; int m_flags;
    int calc(int a, int b); double calc(double a);
};
#define P(s, m) std::printf("%s %s %zu\n", #s, #m, offsetof(s, m))
int main() {
    std::printf("SIZE Vec3 %zu\n", sizeof(Vec3));
    std::printf("SIZE Complex %zu\n", sizeof(Complex));
    std::printf("SIZE Base %zu\n", sizeof(Base));
    std::printf("SIZE Derived %zu\n", sizeof(Derived));
    P(Complex, id); P(Complex, pos); P(Complex, fval); P(Complex, name);
    P(Base, m_baseVal);
    P(Derived, m_complex); P(Derived, m_pNext); P(Derived, m_flags);
    return 0;
}
