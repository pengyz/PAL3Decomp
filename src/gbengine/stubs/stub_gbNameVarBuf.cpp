#include "gbengine/gbMisc.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbNameVarBuf::gbNameVarBuf() {}

gbNameVarBuf::~gbNameVarBuf() {}

gbNameVarBuf & gbNameVarBuf::operator=(gbNameVarBuf const & p1) { static gbNameVarBuf _d; return _d; }

int gbNameVarBuf::IsVarExist(unsigned int p1) { return 0; }

void * gbNameVarBuf::LockVariant(unsigned int p1, int * p2) { return 0; }

void gbNameVarBuf::GetVariant(unsigned int p1, void * p2) { }

void gbNameVarBuf::RegVariant(unsigned int p1, int p2, int p3) { }

void gbNameVarBuf::SetVariant(unsigned int p1, void * p2) { }

void gbNameVarBuf::UnlockVariant() { }

