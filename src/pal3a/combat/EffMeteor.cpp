#include "EffMeteor.h"

void CEffMeteor::CreateTask(tagEffTaskParam * p)
{
    /* stub */
}

void CEffMeteor::CreateGeom()
{
    /* stub */
}

void CEffMeteor::UpdateMeteor(float fDeltaTime, float fTime)
{
    /* stub */
}

bool CEffMeteor::Create(tagEffObjType * pType)
{
    /* stub */
    return FALSE;
}

char * CEffMeteor::GetEditorObjDescription(int nIndex)
{
    /* stub */
    return NULL;
}

void CEffMeteor::Update(float fCurTime)
{
    /* stub */
}

unsigned long CEffMeteor::ProcCommonTask(ulong dwParam)
{
    /* stub */
    return 0;
}

void CEffMeteor::Render()
{
    /* stub */
}

void CEffMeteor::LoadTexture(char * pFileName)
{
    /* stub */
}

unsigned long CEffMeteor::ProcInitTask(ulong dwParam)
{
    /* stub */
    return 0;
}

void CEffMeteor::Attach()
{
    /* stub */
}

void CEffMeteor::Destroy()
{
    /* stub */
}

char * CEffMeteor::GetEditorTaskDescription(int nIndex)
{
    /* stub */
    return NULL;
}

CEffMeteor::~CEffMeteor()
{
    /* stub */
}

CEffMeteor::CEffMeteor()
{
    /* stub */
}

void CEffMeteor::Init(tagEffObjType * pType, float fx, float fy, float fz)
{
    /* stub */
}

void CEffMeteor::InitDefaultUVSet(int nFramePerRow, int nFramePerCol)
{
    /* stub */
}

void CEffMeteor::StartMeteor()
{
    /* stub */
}

void CMeteorChain::AddNewNode(gbVec3D * pVec, float fCurTime)
{
    /* stub */
}

CMeteorChain::~CMeteorChain()
{
    /* stub */
}

bool CMeteorChain::Create(CEffMgr * pEM, int nNumOfNode, uchar bTexture, gbTextureArray * t)
{
    /* stub */
    return FALSE;
}

void CMeteorChain::Update(float fCurTime)
{
    /* stub */
}

CMeteorChain::CMeteorChain()
{
    /* stub */
}

void CMeteorChain::GetFirstNodePos(gbVec3D * vecPos)
{
    /* stub */
}

void CMeteorChain::ClearAllNode()
{
    /* stub */
}

void CMeteorChain::Render()
{
    /* stub */
}

