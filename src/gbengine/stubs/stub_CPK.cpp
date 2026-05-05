#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

bool CPK::GetFileSize(unsigned long & p1, unsigned long & p2, unsigned long p3) { return false; }

bool CPK::IsDir(unsigned long p1) { return false; }

int CPK::GetTableIndex(char const * p1) { return 0; }

int CPK::GetTableIndexFromCRC(unsigned long p1) { return 0; }

unsigned long * CPK::CrcTable;

unsigned long CPK::Crc(char const * p1) { return 0; }

void CPK::InitCrcTable() { }

unsigned long CPK::GetAllocationGranularity() { return 0; }

void CPK::Reset() { }

bool CPK::Close(CPKFile * p1) { return false; }

bool CPK::IsFileExist(char const * p1) { return false; }

bool CPK::IsLoaded() { return false; }

bool CPK::IsValidCPK(char const * p1) { return false; }

bool CPK::Load(char const * p1) { return false; }

bool CPK::Read(void * p1, unsigned long p2, CPKFile * p3) { return false; }

bool CPK::Unload() { return false; }

unsigned long CPK::Seek(CPKFile * p1, int p2, unsigned long p3) { return 0; }

