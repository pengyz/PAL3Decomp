#include "CBStageCam.h"

void CCBCamControl::DoCircleMoveSpeedUnknow()
{
    /* stub */
}

void CCBCamControl::KeepCurCam(tagCam * pCam)
{
    /* stub */
}

void CCBCamControl::ShowCircleSet()
{
    /* stub */
}

void CCBCamControl::Update()
{
    /* stub */
}

CCBCamControl::~CCBCamControl()
{
    /* stub */
}

void CCBCamControl::Reset()
{
    /* stub */
}

void CCBCamControl::DoLineMove()
{
    /* stub */
}

bool CCBCamControl::Create()
{
    /* stub */
    return FALSE;
}

CCBCamControl::CCBCamControl(CCBStage * pStage, CCBStageCam * pCam)
{
    /* stub */
}

bool CCBCamControl::StartList(int nListIndex, int nTaskIndex)
{
    /* stub */
    return FALSE;
}

bool CCBCamControl::StartList(int nListIndex)
{
    /* stub */
    return FALSE;
}

void CCBCamControl::DoCircleMoveTargetUnknow()
{
    /* stub */
}

void CCBCamControl::StopList()
{
    /* stub */
}

void CCBCamControl::SetCircle(gbVec3D * pvecCenter, gbVec3D * pvecEnd)
{
    /* stub */
}

void CCBCamControl::ResetListFlag(int nListIndex)
{
    /* stub */
}

void CCBCamControl::HandleInput()
{
    /* stub */
}

void CCBCamControl::UpdateCircleSet()
{
    /* stub */
}

bool CCBCamControl::Destroy()
{
    /* stub */
    return FALSE;
}

void CCBCamControl::DoLineMoveTargetUnknow()
{
    /* stub */
}

void CCBCamControl::DoLineMoveTimeUnknow()
{
    /* stub */
}

void CCBCamControl::DoList()
{
    /* stub */
}

void CCBCamControl::DoCircleMoveTimeUnknow()
{
    /* stub */
}

bool CCBCamControl::LoadPointer()
{
    /* stub */
    return FALSE;
}

void CCBCamControl::DoCircleMove()
{
    /* stub */
}

void CCBCamControl::DoMechanicsMove()
{
    /* stub */
}

bool CCBCamControl::IsPointerUnderMouse(gbVec3D * pvecPointerPos)
{
    /* stub */
    return FALSE;
}

bool CCBCamControl::Init()
{
    /* stub */
    return FALSE;
}

void CCBCamControl::DoLineMoveSpeedUnknow()
{
    /* stub */
}

int CCBStageCam::AddCurCamToEditor()
{
    /* stub */
    return 0;
}

void CCBStageCam::SaveEditorCam()
{
    /* stub */
}

void CCBStageCam::DelEditorCam(int nCamIndex)
{
    /* stub */
}

void CCBStageCam::ClearFinishedTask()
{
    /* stub */
}

unsigned long CCBStageCam::ProcCamMove(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStageCam::DelTask(int nIndex)
{
    /* stub */
    return FALSE;
}

CCBStageCam::~CCBStageCam()
{
    /* stub */
}

void CCBStageCam::SetCamPos(tagCam * pCamParam)
{
    /* stub */
}

CCBStageCam::CCBStageCam(CCBStage * pStage, gbGfxManager * pGfxMgr)
{
    /* stub */
}

bool CCBStageCam::SwitchEditorCamPos(int nStartPos, int nEndPos, float fExpectTime)
{
    /* stub */
    return FALSE;
}

void CCBStageCam::DoTask()
{
    /* stub */
}

void CCBStageCam::SetCamPosToEditor(int nParamIndex)
{
    /* stub */
}

void CCBStageCam::LoadEditorCam()
{
    /* stub */
}

bool CCBStageCam::Create()
{
    /* stub */
    return FALSE;
}

bool CCBStageCam::Init()
{
    /* stub */
    return FALSE;
}

void CCBStageCam::Update()
{
    /* stub */
}

bool CCBStageCam::IsCamValid(tagCam * pCam)
{
    /* stub */
    return FALSE;
}

bool CCBStageCam::Destroy()
{
    /* stub */
    return FALSE;
}

bool CCBStageCam::IsEditorCamValid(int nCamIndex)
{
    /* stub */
    return FALSE;
}

void CCBStageCam::Reset()
{
    /* stub */
}

bool CCBStageCam::AddTask(void * fp, ulong dwTaskID, float fExpectTime, tagCam * pStartPos, tagCam * pEndPos)
{
    /* stub */
    return FALSE;
}

bool CCCTData::IsTaskValid(int nTaskIndex, int nListIndex)
{
    /* stub */
    return FALSE;
}

void CCCTData::Reset()
{
    /* stub */
}

bool CCCTData::Save()
{
    /* stub */
    return FALSE;
}

bool CCCTData::SwapTask(int nListIndex, int nTaskIndex1, int nTaskIndex2)
{
    /* stub */
    return FALSE;
}

bool CCCTData::DelTaskInList(int nListIndex, int nTaskIndex)
{
    /* stub */
    return FALSE;
}

bool CCCTData::Destroy()
{
    /* stub */
    return FALSE;
}

bool CCCTData::Init()
{
    /* stub */
    return FALSE;
}

bool CCCTData::Load()
{
    /* stub */
    return FALSE;
}

int CCCTData::GetTaskNumInList(int nListIndex)
{
    /* stub */
    return 0;
}

bool CCCTData::AddTaskToList(int nListIndex, tagCCT * pCCT)
{
    /* stub */
    return FALSE;
}

CCCTData::~CCCTData()
{
    /* stub */
}

bool CCCTData::ClearList(int nListIndex)
{
    /* stub */
    return FALSE;
}

CCCTData::CCCTData()
{
    /* stub */
}

bool CCCTData::InsertTaskToList(int nListIndex, int nTaskIndex, tagCCT * pCCT)
{
    /* stub */
    return FALSE;
}

bool CCCTData::Create()
{
    /* stub */
    return FALSE;
}

int CCCTData::GetFreeSpaceInPool()
{
    /* stub */
    return 0;
}

