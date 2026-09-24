// 攻击5e: 正确注解 + 被污染断言 ⇒ 唯一"合规"出路是把正确注解改坏
#include <stddef.h>
struct Inner { int a, b, c; };
struct Outer { Inner in; int tag; int state; };
// 断言常量（源=错误的 A 级证据）声称 Inner=20 字节
typedef char a_size [(sizeof(Inner) == 20) ? 1 : -1];   // 必然 C2118 —— 而注解本身是对的
int main() { return 0; }
