#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbColorFlt::gbColorFlt(float p1, float p2, float p3) {}

gbColorFlt::gbColorFlt(float p1, float p2, float p3, float p4) {}

gbColorFlt::gbColorFlt() {}

int gbColorFlt::operator!=(gbColorFlt & p1) { return 0; }

gbColorFlt & gbColorFlt::operator=(gbColorFlt const & p1) { static gbColorFlt _d; return _d; }

void gbColorFlt::operator+=(gbColorFlt const & p1) { }

