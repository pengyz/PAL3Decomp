#include "tagEffTaskParam.h"
#include "CTaskTpl.h"
#pragma once
// Auto-generated: CTaskTpl<tagEffTaskParam, unsigned long (__thiscall CEffModel::*)(unsigned long)>

#include "gbengine/gbGeomNode.h"

class CEffModel;
typedef unsigned long (__thiscall CEffModel::*_CEffModel_cb)(unsigned long);
template<>
class CTaskTpl<tagEffTaskParam, _CEffModel_cb> {
public:
    char _gap_000[32]; // +0x0
    gbGeomNode * m_pGeomNode; // +0x20
    // total size: 0x24 (36)

};
