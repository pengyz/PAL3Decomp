#pragma once
// Auto-generated: scSCEFile

class SceIndex;
class gbVFile;

class scSCEFile {
public:
    gbVFile * m_fp; // +0x0
    struct allocator<scScriptBlock *> > {}; // nested type stub
    allocator<scScriptBlock *> > m_blocks; // +0x4
    unsigned short m_blocknum; // +0x14
    SceIndex * m_pindex; // +0x18
    // total size: 0x1C (28)

};
