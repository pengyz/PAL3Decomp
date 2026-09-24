// I2 修复轮 R=1 探针：store-through 不连续不得判 sret（真机 /Od /GR）
// 真值：?poff@RnA@@UAEHPAH@Z = __thiscall / 1 指针参 / int，只写 +0xc
struct RnA { virtual int poff(int* p); };
int RnA::poff(int* p) { p[3] = 3; return (int)p; }
