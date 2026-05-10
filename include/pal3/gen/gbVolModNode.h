#pragma once
// Auto-generated: gbVolModNode

#include "gbVisNode.h"

class gbVolumeModifier;

class gbVolModNode : public gbVisNode {
public:
    gbMatrix4 m_ToWorld; // +0x58
    gbMatrix4 m_ToView; // +0x98
    gbVolumeModifier * m_pModObj; // +0xD8
    // total size: 0xDC (220)

};
