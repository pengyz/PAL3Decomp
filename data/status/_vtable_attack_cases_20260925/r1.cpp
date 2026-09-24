// 攻击1-决定性: 把 a2-Der 的【实测槽序】按 §2.2 逆规则重推声明序，再编译看能否还原同一 vtable
// 实测 Der 槽序 = [o(double), o(int), o(), mid(), o(char*), tail]（o 组跨 mid 非连续）
// §2.2 逆规则 => 声明序 = [o(char*), o(), o(int), o(double), mid(), tail]（组内反转 + 组位置=首现）
struct R {
    virtual void o(char*);
    virtual void o();
    virtual void o(int);
    virtual void o(double);
    virtual void mid();
    virtual void tail();
};
void R::o(char*) {} void R::o() {} void R::o(int) {} void R::o(double) {} void R::mid() {} void R::tail() {}
int main() { R x; return 0; }
