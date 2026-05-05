#include "SceneObj.h"

int MyMdl::IsOver()
{
    /* stub */
    return 0;
}

MyMdl::~MyMdl()
{
    /* stub */
}

void MyMdl::Load(char * filename, ulong param, int addinparam)
{
    /* stub */
}

void MyMdl::Update(float deltatime)
{
    /* stub */
}

void MyMdl::Attach(gbRenderEffect * eft)
{
    /* stub */
}

MyMdl::MyMdl()
{
    /* stub */
}

void MyMdl::Destroy()
{
    /* stub */
}

bool SceneObj::CanBeCheck(Role * pRole)
{
    /* stub */
    return FALSE;
}

void SceneObj::Glow_Attach(gbRenderEffect * eft)
{
    /* stub */
}

int SceneObj::IsCollideRayEX(gbRay * ray, gbVec3D * vOut)
{
    /* stub */
    return 0;
}

bool SceneObj::IsPushAllow()
{
    /* stub */
    return FALSE;
}

bool SceneObj::MoveActor(float deltatime)
{
    /* stub */
    return FALSE;
}

int SceneObj::IsCollideRay(gbRay * ray)
{
    /* stub */
    return 0;
}

void SceneObj::GetSubObjBox(gbOBBox * box)
{
    /* stub */
}

int SceneObj::IsCollide(int x, int y, gbVec3D * testpos)
{
    /* stub */
    return 0;
}

void SceneObj::Create(ObjectInfo * info, Scene * scene)
{
    /* stub */
}

void SceneObj::InterActRole_CGSpecial(Role * role, uchar touchtype, int react, float deltatime, float fWaitTime)
{
    /* stub */
}

void SceneObj::OnLoad(ObjectInfo * info, void* subobj)
{
    /* stub */
}

void SceneObj::Update(float deltatime)
{
    /* stub */
}

int SceneObj::CanRoleGoto(gbVec3D * rolepos, gbVec3D * pt)
{
    /* stub */
    return 0;
}

void SceneObj::MoveTouchedObj()
{
    /* stub */
}

void SceneObj::FinishBox()
{
    /* stub */
}

void SceneObj::InterActRole_CG(Role * role, uchar touchtype, int react, float deltatime, float fWaitTime)
{
    /* stub */
}

void SceneObj::FillMapRectSubObj(int clear)
{
    /* stub */
}

void SceneObj::Snd_Stop()
{
    /* stub */
}

void SceneObj::SceneRelation()
{
    /* stub */
}

void SceneObj::GetRawOBB(gbOBBox * box)
{
    /* stub */
}

bool SceneObj::IsNULLState()
{
    /* stub */
    return FALSE;
}

void SceneObj::SetFloorCanGo(FLOOR_KIND att, int cango)
{
    /* stub */
}

int SceneObj::CanGoTo(gbVec3D * nextpos)
{
    /* stub */
    return 0;
}

void SceneObj::FillMapORectSubObj(int clear)
{
    /* stub */
}

SceneObj::~SceneObj()
{
    /* stub */
}

void SceneObj::Glow_GetAABB(gbAABBox * _box)
{
    /* stub */
}

int SceneObj::OnCreateMap(SceneMapObj * scenemap, uchar index)
{
    /* stub */
    return 0;
}

void SceneObj::FlowerSwitch_Mdl()
{
    /* stub */
}

void SceneObj::Render(gbMatrixStack * pview, gbRenderEffect * eft)
{
    /* stub */
}

bool SceneObj::IsStatic()
{
    /* stub */
    return FALSE;
}

void SceneObj::OpenSwitch()
{
    /* stub */
}

void SceneObj::MoveLayer()
{
    /* stub */
}

float SceneObj::GetObjHeight(int onlayer, int x, int y)
{
    /* stub */
    return 0.0f;
}

void SceneObj::OnRoleLeave()
{
    /* stub */
}

void SceneObj::FillMapRect(int clear)
{
    /* stub */
}

void SceneObj::Destroy()
{
    /* stub */
}

bool SceneObj::HasInverseStateUniteObj_InLastSaveScene()
{
    /* stub */
    return FALSE;
}

void SceneObj::Script_OpenDoor()
{
    /* stub */
}

void SceneObj::Door_Switch(int state)
{
    /* stub */
}

int SceneObj::IfOnMe(Role * pRole)
{
    /* stub */
    return 0;
}

void SceneObj::GetCollideOBB(gbOBBox * box, gbVec3D * testpos)
{
    /* stub */
}

void SceneObj::GetCollideOBB(gbOBBox * box)
{
    /* stub */
}

void SceneObj::InterActRole(Role * role, uchar touchtype, int react, float deltatime)
{
    /* stub */
}

void SceneObj::RefreshMapRect()
{
    /* stub */
}

void SceneObj::Flower_Switch(uchar open)
{
    /* stub */
}

SceneObj::SceneObj()
{
    /* stub */
}

void SceneObj::PlaySnd(int s)
{
    /* stub */
}

void SceneObj::SetRectDist(tagRECT * rect, uchar val)
{
    /* stub */
}

void SceneObj::AddInventory(int itemID)
{
    /* stub */
}

int SceneObj::IsWaiting()
{
    /* stub */
    return 0;
}

bool SceneObj::IfNeedSave()
{
    /* stub */
    return FALSE;
}

SceneObj * SceneObj::LinkObject()
{
    /* stub */
    return NULL;
}

void SceneObj::Common_SwitchSpecialState(uchar nextstate, int waitMode)
{
    /* stub */
}

void SceneObj::Common_SetActive(uchar active)
{
    /* stub */
}

void SceneObj::Common_Delay(float time)
{
    /* stub */
}

void SceneObj::Common_OnSwitchCommonState()
{
    /* stub */
}

void SceneObj::Common_ShowAnimation(uchar holdLastFrame)
{
    /* stub */
}

void SceneObj::Common_Position(gbVec3D * newpos, float time, uchar liftplayer, uchar savepos)
{
    /* stub */
}

void SceneObj::Common_Update(float deltatime)
{
    /* stub */
}

void SceneObj::Common_FillMapRect(uchar clear)
{
    /* stub */
}

void SceneObj::Common_MovePlayer(gbVec3D * pos, uchar nav, uchar mapheight)
{
    /* stub */
}

void SceneObj::Common_DistRestrict()
{
    /* stub */
}

void SceneObj::Common_EnableRoleCtrl(uchar enable)
{
    /* stub */
}

void SceneObj::Common_Snd(int p)
{
    /* stub */
}

void SceneObj::Common_GravityDown()
{
    /* stub */
}

void SceneObj::Common_SetPlayerLayer(int newlayer, uchar self)
{
    /* stub */
}

void SceneObj::Common_SetCameraFree(uchar bFree)
{
    /* stub */
}

void SceneObj::Common_Switch(uchar bSwitch)
{
    /* stub */
}

void SceneObj::Common_RunScript(int scriptid, uchar wait)
{
    /* stub */
}

void SceneObj::Common_PlayerFace(gbVec3D * pt)
{
    /* stub */
}

void SceneObj::Common_MovePlayerPath()
{
    /* stub */
}

void SceneObj::Common_MachineCtrl(uchar bMachine)
{
    /* stub */
}

void SceneObj::Common_SetCanGo(uchar cango)
{
    /* stub */
}

void SceneObj::Common_CameraMove(gbVec3D DestLookAt, uchar duration)
{
    /* stub */
}

void SceneObj::Common_CameraLockPlayer()
{
    /* stub */
}

void SceneObj::Common_LinkObject(uchar wait)
{
    /* stub */
}

void SceneObj::Common_OnSwitchSpecial(uchar state)
{
    /* stub */
}

void SceneObj::Common_PlayerShowAct(ACTION_KIND act, int loop)
{
    /* stub */
}

unsigned long SceneObj::Proc_DoAction(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_AddItemFromTreasureBox(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_ObjectMoveUPDN(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_UnHideSelf(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_UnLockCamera(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_UnLockRole(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_VerticalMove(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_ShowDialog(ulong dw)
{
    /* stub */
    return 0;
}

float SceneObj::CalculateExp(WuLing att)
{
    /* stub */
    return 0.0f;
}

unsigned long SceneObj::Proc_CG_MoveToAndFro(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_LinkObject(ulong dw)
{
    /* stub */
    return 0;
}

void SceneObj::SetUniteObjectsRight(uchar inverse)
{
    /* stub */
}

float SceneObj::VecAngle(gbVec3D * v1, gbVec3D * v2)
{
    /* stub */
    return 0.0f;
}

unsigned long SceneObj::Proc_RunScript(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_RefreshMapRect(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_CG_VerticalMove(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_MutualPropUI(ulong dw)
{
    /* stub */
    return 0;
}

gbVec3D SceneObj::CalculateRelate(gbVec3D * __$ReturnUdt, gbVec3D * other, float * yaw)
{
    /* stub */
    gbVec3D _ret = {0}; return _ret;
}

unsigned long SceneObj::Proc_MoveOnObject(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_LockCamera(ulong dw)
{
    /* stub */
    return 0;
}

void SceneObj::SetTasks(SaveTask * task)
{
    /* stub */
}

void SceneObj::Init()
{
    /* stub */
}

unsigned long SceneObj::Proc_DirectionMove(ulong dw)
{
    /* stub */
    return 0;
}

bool SceneObj::GetObjectTouchPoint(Role * role, gbVec3D * dest)
{
    /* stub */
    return FALSE;
}

unsigned long SceneObj::Proc_RelativeRotateYaw(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_HandleSwitch(ulong dw)
{
    /* stub */
    return 0;
}

SaveTask & SceneObj::GetTasks()
{
    /* stub */
    static char _buf[256] = {0}; return *(SaveTask*)_buf;
}

unsigned long SceneObj::Proc_ChangeState(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_ShowRoleInPosition(ulong dw)
{
    /* stub */
    return 0;
}

bool SceneObj::CheckToTouch(Role * role, gbVec3D position, gbVec3D * dest)
{
    /* stub */
    return FALSE;
}

unsigned long SceneObj::Proc_HiddenOther(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_RunScriptWait(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_HorizontalMove(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_SetRoleLevel(ulong dw)
{
    /* stub */
    return 0;
}

void SceneObj::HandleTreasureBox()
{
    /* stub */
}

int SceneObj::HandleUpgrade(int nRoleIndex)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_ObjectMoveOnPath(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_Test3(ulong dw)
{
    /* stub */
    return 0;
}

void SceneObj::SetUniteObjectsMove()
{
    /* stub */
}

bool SceneObj::CheckLinkObject()
{
    /* stub */
    return FALSE;
}

void SceneObj::SetUniteObjectsLeft(uchar inverse)
{
    /* stub */
}

unsigned long SceneObj::Proc_Test2(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_CG_PlayerCVD(ulong dw)
{
    /* stub */
    return 0;
}

gbVec3D SceneObj::GetVectorFromYawPitchRoll(gbVec3D * __$ReturnUdt, float yaw, float pitch)
{
    /* stub */
    gbVec3D _ret = {0}; return _ret;
}

void SceneObj::Lerp(float * val, float start, float target, float r)
{
    /* stub */
}

unsigned long SceneObj::Proc_DisplayPointer(ulong dw)
{
    /* stub */
    return 0;
}

void SceneObj::HandleCGObj(Role * pRole, int type, gbVec3D pos, int bShow)
{
    /* stub */
}

unsigned long SceneObj::Proc_HandleObject(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_Test1(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_CG_Thunder(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_HandleLittleBox(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_PlayCVD(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_PlaySnd(ulong dw)
{
    /* stub */
    return 0;
}

void SceneObj::SetUniteObjectsZero()
{
    /* stub */
}

unsigned long SceneObj::Proc_MoveWithPath(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_MoveRole(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_CameraRefer(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_CG_RotateAndMove(ulong dw)
{
    /* stub */
    return 0;
}

void SceneObj::HandleObject()
{
    /* stub */
}

unsigned long SceneObj::Proc_Rotate(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_RoleToPosition(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_RoleFalling(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_DirectionMoveEX(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_HideSelf(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_UniteObjectsRight(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_UniteObjectsZero(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_LockRole(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_CG_VerticalMoveToAndFro(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_DisableRole(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_CG_PointAct(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_ShowLinkObj(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_CG_Fire(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_UniteObjectsMove(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_MoveToAndFro(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_RiseAndFall(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_CG_DirectionMove(ulong dw)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_Test4(ulong dw)
{
    /* stub */
    return 0;
}

int SceneObj::ProcessGroupObj(Role * role, uchar touchtype, int react, float deltatime)
{
    /* stub */
    return 0;
}

unsigned long SceneObj::Proc_UniteObjectsLeft(ulong dw)
{
    /* stub */
    return 0;
}

int _PtInRect(tagRECT * rc, tagPOINT * pt)
{
    /* stub */
    return 0;
}

