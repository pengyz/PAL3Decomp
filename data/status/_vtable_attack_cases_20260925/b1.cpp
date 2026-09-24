// 攻击3f: BOOL 是否真与 int "字节等价"？实参是 int 变量 / bool 变量两种形态
struct SB { virtual void fb(bool); virtual void fi(int); };
void SB::fb(bool) {}
void SB::fi(int) {}
void c1(SB* p, bool b) { p->fb(b); p->fi(b); }
void c2(SB* p, int  i) { p->fb(i); p->fi(i); }
