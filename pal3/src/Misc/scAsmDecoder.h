#pragma once
// Auto-generated: scAsmDecoder

class scGlobalUserVar;
class scVarStack;

class scAsmDecoder {
public:
    scVarStack * m_stack; // +0x0
    // total size: 0x4 (4)

    int Execute(int nVal, char pData); // 0x0040E5F0
    static struct scGlobalUserVar * GetGlobalUserVar(char *); // 0x004A1A7C
};
