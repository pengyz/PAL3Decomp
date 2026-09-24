// 攻击5b: offsetof 于虚基类成员 / 非 POD 类
struct V2 { virtual void v(); int vm; };
struct DV2 : virtual V2 { int dm; virtual void q(); };
typedef char a_vm[(offsetof(DV2, vm) == 8) ? 1 : -1];   // 虚基成员偏移是否可作常量?
typedef char a_dm[(offsetof(DV2, dm) == 4) ? 1 : -1];
int main() { return 0; }
