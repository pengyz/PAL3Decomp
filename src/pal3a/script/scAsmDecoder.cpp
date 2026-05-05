#include "scAsmDecoder.h"

int scAsmDecoder::LoadSysInfo(char * filename)
{
    /* stub */
    return 0;
}

int scAsmDecoder::Init(char * scsysfile)
{
    /* stub */
    return 0;
}

void scAsmDecoder::FreeScriptInstance(scScriptInstance * pinstance)
{
    /* stub */
}

scScriptInstance * scAsmDecoder::CreateScriptInstance(scSCEFile * psce, ulong scriptid, ulong startoffset)
{
    /* stub */
    return NULL;
}

void scAsmDecoder::RunNextCmd()
{
    /* stub */
}

int scAsmDecoder::Execute(scScriptInstance * pinst)
{
    /* stub */
    return 0;
}

scAsmDecoder::scAsmDecoder()
{
    /* stub */
}

void scAsmDecoder::FreeAll()
{
    /* stub */
}

scVARIANT * scAsmDecoder::GetUserVar(ushort id, scScriptInstance * pinst)
{
    /* stub */
    return NULL;
}

scGlobalUserVar * scAsmDecoder::GetGlobalUserVar(char * varname)
{
    /* stub */
    return NULL;
}

scAsmDecoder::~scAsmDecoder()
{
    /* stub */
}

int scSCEFile::FindScriptIndex(ulong id)
{
    /* stub */
    return 0;
}

scSCEFile::~scSCEFile()
{
    /* stub */
}

scScriptBlock * scSCEFile::LoadScriptBlock(SceIndex * pIndex)
{
    /* stub */
    return NULL;
}

scScriptBlock * scSCEFile::LoadScriptBlock(ulong id)
{
    /* stub */
    return NULL;
}

void scSCEFile::Close()
{
    /* stub */
}

scSCEFile::scSCEFile()
{
    /* stub */
}

int scSCEFile::Open(char * filename)
{
    /* stub */
    return 0;
}

void _readuservarinfo(scUserVarInfo * tmpinfo, gbVFile * fp)
{
    /* stub */
}

void _getbasicvar(scVARIANT * pvar, scScriptInstance * pinst, uchar vartype)
{
    /* stub */
}

