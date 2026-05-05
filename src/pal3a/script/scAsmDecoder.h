#ifndef PAL3A_SCASMDECODER_H
#define PAL3A_SCASMDECODER_H

#include "pal3a_types.h"

class scAsmDecoder {
public:
    char _data[4];

    int LoadSysInfo(char * filename);
    int Init(char * scsysfile);
    void FreeScriptInstance(scScriptInstance * pinstance);
    scScriptInstance * CreateScriptInstance(scSCEFile * psce, ulong scriptid, ulong startoffset);
    void RunNextCmd();
    int Execute(scScriptInstance * pinst);
    scAsmDecoder();
    void FreeAll();
    scVARIANT * GetUserVar(ushort id, scScriptInstance * pinst);
    scGlobalUserVar * GetGlobalUserVar(char * varname);
    ~scAsmDecoder();
};

class scSCEFile {
public:
    char _data[28];

    int FindScriptIndex(ulong id);
    ~scSCEFile();
    scScriptBlock * LoadScriptBlock(SceIndex * pIndex);
    scScriptBlock * LoadScriptBlock(ulong id);
    void Close();
    scSCEFile();
    int Open(char * filename);
};

void _readuservarinfo(scUserVarInfo * tmpinfo, gbVFile * fp);
void _getbasicvar(scVARIANT * pvar, scScriptInstance * pinst, uchar vartype);

#endif // PAL3A_SCASMDECODER_H
