#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"

// 0x004B6FB0
// [overlay-fix 2026-10-27] C2556/C2371/C2491: gbengine dllimport 方法被重复定义
// （int Process() 与头文件 void dllimport Process() 冲突——归属/边界问题）——待归属定谳
// int gbChain1DNode::Process()
// {
//   int result; // eax
//
//   operator delete(this[3].next);
//   (((gbChain1D *)&this[1].next))->gbChain1D::~gbChain1D();
//   this->~gbChain1DNode();
//   return result;
// }
