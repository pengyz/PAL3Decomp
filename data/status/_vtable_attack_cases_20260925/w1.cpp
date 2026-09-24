#include <stddef.h>
// 攻击5d: 断言常量被"错误 A 级证据"污染后的强制效应
struct Inner { int a, b, c; };            // 真实 12 字节
struct Outer { Inner in; int tag; };       // tag 真实偏移 +12
// 假设 IDA 把 mov [ecx+10h] 误归属为 Inner 成员（this 归属错）⇒ 断言常量=20
typedef char a_size [(sizeof(Inner)        == 12)  ? 1 : -1];   // 真值断言
typedef char a_tag  [(offsetof(Outer, tag) == 20)  ? 1 : -1];   // 被污染的断言常量
int main() { return 0; }
