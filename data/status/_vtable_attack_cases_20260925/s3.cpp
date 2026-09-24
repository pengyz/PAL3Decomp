// 攻击3c: 调用点证据 vs callee 证据（经虚表调用，不可去虚化）
struct SC {
    virtual void unu(int, int);           // 未用参数 thiscall
    virtual void __fastcall freg(int, int);// fastcall
    virtual void log(const char*, ...);    // 变参
    virtual void two(int, double);         // double 占双槽
};
void SC::unu(int,int) {}
void __fastcall SC::freg(int,int) {}
void SC::log(const char*, ...) {}
void SC::two(int, double) {}
void caller(SC* p) { p->unu(1,2); p->freg(1,2); p->log("a", 7); p->two(3, 1.5); }
