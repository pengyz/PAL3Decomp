#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbVTextFile::gbVTextFile(char * p1) {}

gbVTextFile::gbVTextFile() {}

gbVTextFile::~gbVTextFile() {}

char * gbVTextFile::ReadLine() { return 0; }

gbVTextFile & gbVTextFile::operator=(gbVTextFile const & p1) { static gbVTextFile _d; return _d; }

void gbVTextFile::Close() { }

void gbVTextFile::Open(char * p1) { }

void gbVTextFile::Rewind() { }

