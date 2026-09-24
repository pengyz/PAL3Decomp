// I2 阴性对照探针：连续性判据不得误杀"带填充的真 sret"（真机 /Od /GR）
// 真值：?mkp@Rn11@@UAE?AUPad16@@XZ = sret（MSVC 连填充一起复制 ⇒ covered 连续）
//       ?pwrite@Rn11@@UAEHPAUPad16@@@Z = 非 sret（只写 +0x8/+0xc，单基址 eax max=15 但散写）
struct Pad16 { char c; double d; };  // sizeof 16（1..7 填充）
struct Rn11 { virtual Pad16 mkp(); virtual int pwrite(Pad16* q); };
Pad16 Rn11::mkp() { Pad16 p; p.c='a'; p.d=1.5; return p; }
int Rn11::pwrite(Pad16* q) { q->d = 2.5; return 0; }
