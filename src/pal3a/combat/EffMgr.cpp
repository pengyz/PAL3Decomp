#include "EffMgr.h"

bool CEffMgr::LoadAllEffParam()
{
    /* stub */
    return FALSE;
}

bool CEffMgr::Init()
{
    /* stub */
    return FALSE;
}

void CEffMgr::StopRunningGroup(ulong dwRunningID)
{
    /* stub */
}

unsigned long CEffMgr::RunEffGroup(int nGroup, float fx, float fy, float fz, ulong dwID)
{
    /* stub */
    return 0;
}

CEffMgr::CEffMgr(gbGfxManager * pDisplay, gbCamera * pCam, CCBSystem * pCBSystem)
{
    /* stub */
}

CEffMgr::~CEffMgr()
{
    /* stub */
}

bool CEffMgr::RegAllEff()
{
    /* stub */
    return FALSE;
}

void CEffMgr::DelObjTask(int nGroup, int nObj, int nTask)
{
    /* stub */
}

void CEffMgr::Attach()
{
    /* stub */
}

bool CEffMgr::IsAllEffGroupStop()
{
    /* stub */
    return FALSE;
}

int CEffMgr::GetEffClassIndex(ulong dwClassCRC)
{
    /* stub */
    return 0;
}

void CEffMgr::DelAllIdleObj()
{
    /* stub */
}

void CEffMgr::SetTimeScale(float fScale)
{
    /* stub */
}

bool CEffMgr::SetEffObjTypeAtt(tagEffObjType * pType, int nEffObjTypeIndex)
{
    /* stub */
    return FALSE;
}

void CEffMgr::StopAllEffGroup()
{
    /* stub */
}

bool CEffMgr::IsEffGroupRunning(ulong dwRunningID)
{
    /* stub */
    return FALSE;
}

void CEffMgr::DelObjType(int nType)
{
    /* stub */
}

void CEffMgr::Update(float fCurTime)
{
    /* stub */
}

void CEffMgr::DelObjInGroup(int nGroup, int nObj)
{
    /* stub */
}

void CEffMgr::DelAllCreatedObj()
{
    /* stub */
}

bool CEffMgr::SaveAllEffParam()
{
    /* stub */
    return FALSE;
}

unsigned long CEffMgr::PreLoadEffGroup(int nGroup)
{
    /* stub */
    return 0;
}

void CEffMgr::Render()
{
    /* stub */
}

void CEffMgr::CopyObjType(int nType)
{
    /* stub */
}

int CEffMgr::CreateEff(ulong dwTypeCRC, ulong dwRunID, float fx, float fy, float fz)
{
    /* stub */
    return 0;
}

int CEffMgr::CreateEff(char * szEffTypeName, ulong dwRunID, float fx, float fy, float fz)
{
    /* stub */
    return 0;
}

int CEffMgr::GetEffObjTypeIndex(ulong dwTypeCRC)
{
    /* stub */
    return 0;
}

void CEffMgr::SwapObjInGroup(int nGroup, int nObj1, int nObj2)
{
    /* stub */
}

void CEffMgr::CopyObjInGroup(int nGroup, int nObj, int nObjType)
{
    /* stub */
}

