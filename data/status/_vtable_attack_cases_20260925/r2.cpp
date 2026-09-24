// 攻击3/4: __cdecl 成员函数 —— callee 读集里 [esp+4] 是 this；调用点 push 含 this
struct Xc { int m; virtual void __cdecl cf(int); virtual void __cdecl cf2(int,int); };
void __cdecl Xc::cf(int x)   { m = x; }              // 读 [esp+4]=this, [esp+8]=x
void __cdecl Xc::cf2(int a,int b) { m = a + b; }     // 读 [esp+4]=this,[esp+8]=a,[esp+0c]=b
void ccall(Xc* p) { p->cf(1); p->cf2(1,2); }
