// Task 3 修复轮 R=2 探针：多基址 + covered 不连续 ⇒ sret_ambiguous 安全网（真机 /Od /GR）
// 真值：?mwp@Rn7@@UAEHPAUInnerV@@@Z = __thiscall / 1 指针参 / int
// objdump -dr：多基址（eax/ecx）+ covered={0..3}∪{8..0xb}（max=11 ≥ 8 但不连续）
// 形态既非真 sret（连续复制）也非单基址散写（?poff）⇒ 必须留 sret_ambiguous 痕迹并降级 B
struct InnerV { int a; int b; int c; int d; };
struct Rn7 { virtual int mwp(InnerV* p); };
int Rn7::mwp(InnerV* p) { p->a = 1; p->c = 2; return (int)p; }
