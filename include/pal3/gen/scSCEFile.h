#pragma once
// Auto-generated: scSCEFile

class SceIndex;
class gbVFile;

class scSCEFile {
public:
    gbVFile * m_fp; // +0x0
    char m_blocks[16]; // +0x4 (std::vector<scScriptBlock *,std::allocator<scScriptBlock *> >)
    WORD m_blocknum; // +0x14
    SceIndex * m_pindex; // +0x18
    // total size: 0x1C (28)

};
