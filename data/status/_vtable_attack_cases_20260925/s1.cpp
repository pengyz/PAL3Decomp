// 攻击3: callee 侧证据盲区 —— 未用参数 / 寄存器传参 / 变参 / 同体折叠
struct S {
    virtual void unused(int, int);          // 未用参数
    virtual void __fastcall freg(int, int); // 寄存器传参 + 未用
    virtual void log(const char*, ...);     // 变参（强制 __cdecl）
    virtual int  idi(int x);                // int
    virtual int  idp(void* p);              // 指针（等价类主张字节等价）
};
void S::unused(int, int) {}
void __fastcall S::freg(int, int) {}
void S::log(const char*, ...) {}
int  S::idi(int x) { return x; }
int  S::idp(void* p) { return (int)p; }
int main() { S x; x.unused(1,2); x.freg(1,2); x.log("a", 1); return x.idi(3) + x.idp(0); }
