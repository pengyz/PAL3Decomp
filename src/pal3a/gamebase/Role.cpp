#include "Role.h"

void Role::UpdateSteer(float deltaTime)
{
    /* stub */
}

void Role::CGStand()
{
    /* stub */
}

void Role::OnBehaviourFinish()
{
    /* stub */
}

void Role::GotoAction(ACTION_KIND act)
{
    /* stub */
}

int Role::IsTeamOpenA()
{
    /* stub */
    return 0;
}

void Role::Destroy()
{
    /* stub */
}

float Role::GetHeight()
{
    /* stub */
    return 0.0f;
}

void Role::MachineCtrl(int inctrl)
{
    /* stub */
}

void Role::GetArcInfo(ArcLocaleRole * pInfo)
{
    /* stub */
}

void Role::PathMoveCG(gbVec3D * dest, int layer, ACTION_KIND act)
{
    /* stub */
}

int Role::GetMapDist(gbVec3D * nextpt)
{
    /* stub */
    return 0;
}

bool Role::Script_Climb(int objid, int updown)
{
    /* stub */
    return FALSE;
}

float Role::CGGetAttackRange()
{
    /* stub */
    return 0.0f;
}

void Role::Script_SetPos(int x, int z)
{
    /* stub */
}

void Role::SetArcInfo(ArcLocaleRole * pInfo)
{
    /* stub */
}

void Role::GetPetPos(gbVec3D * out)
{
    /* stub */
}

void Role::ShowAct(char * act, int loopcount)
{
    /* stub */
}

void Role::ShowAct(ACTION_KIND act, int loopcount, uchar ascuract)
{
    /* stub */
}

void Role::JumpTo(gbVec3D * dest)
{
    /* stub */
}

void Role::LoadAct(char * name)
{
    /* stub */
}

void Role::PathToLayer(gbVec3D * dest, int layer, ACTION_KIND act)
{
    /* stub */
}

void Role::PetFly(gbVec3D * pt)
{
    /* stub */
}

void Role::UpdateCGMonster(float deltatime)
{
    /* stub */
}

void Role::FaceTo(gbVec3D * pt, int imm)
{
    /* stub */
}

void Role::Climb(int x1, int y1, int x2, int y2, float face, SceneObj * pobj)
{
    /* stub */
}

void Role::DrawView()
{
    /* stub */
}

int Role::IsPointInView2(gbVec3D * pt)
{
    /* stub */
    return 0;
}

int Role::UpdateNPCPath(float t)
{
    /* stub */
    return 0;
}

int Role::IsWaiting()
{
    /* stub */
    return 0;
}

int Role::IsPointInView3(gbVec3D * pt)
{
    /* stub */
    return 0;
}

int Role::UpdateFly(float deltaTime, float maxSpeed)
{
    /* stub */
    return 0;
}

void Role::Evasion()
{
    /* stub */
}

void Role::CGEvasionPlayer(float delta)
{
    /* stub */
}

void Role::UpdateRenderPos(int onlygroundpos, int face)
{
    /* stub */
}

bool Role::UpdateLayer(int tp)
{
    /* stub */
    return FALSE;
}

void Role::SetNavigation(int onlayer)
{
    /* stub */
}

void Role::CopyPos(Role * other)
{
    /* stub */
}

void Role::LoadWeapon(char * actname)
{
    /* stub */
}

int Role::UpdateStar(float delta)
{
    /* stub */
    return 0;
}

void Role::CGPursuit()
{
    /* stub */
}

Role::~Role()
{
    /* stub */
}

void Role::UpdateRotate()
{
    /* stub */
}

void Role::TeamClose(gbVec3D * pt)
{
    /* stub */
}

void Role::Wander()
{
    /* stub */
}

void Role::Scale(float s)
{
    /* stub */
}

void Role::TalkTo(Role * npc)
{
    /* stub */
}

void Role::TeamOpen(gbVec3D * pt)
{
    /* stub */
}

int Role::CGFindPlayer()
{
    /* stub */
    return 0;
}

void Role::UpdateMonster(float deltaTime)
{
    /* stub */
}

void Role::UpdatePetFly(float deltaTime)
{
    /* stub */
}

void Role::UpdateMove(float deltatime, uchar autopos)
{
    /* stub */
}

void Role::CreateNPC(NPCInfo * npc)
{
    /* stub */
}

void Role::Create(char * name)
{
    /* stub */
}

void Role::EnforceNonOverlap(float deltatime)
{
    /* stub */
}

void Role::EnforceNonOverlap(Role * other)
{
    /* stub */
}

void Role::UpdateWolf(float delta)
{
    /* stub */
}

void Role::Script_SetActive(int active)
{
    /* stub */
}

void Role::TurnTo(float rotate, int imm)
{
    /* stub */
}

void Role::Update(float deltaTime)
{
    /* stub */
}

int Role::UpdateNPC(float deltaTime)
{
    /* stub */
    return 0;
}

void Role::SetCGPos(gbVec3D pos)
{
    /* stub */
}

void Role::RotateFly(gbVec3D * pt, int flag)
{
    /* stub */
}

void Role::SetPosition(gbVec3D * pt)
{
    /* stub */
}

void Role::SetPosition(int tilex, int tilez)
{
    /* stub */
}

void Role::TransToLayer(int layer, int portal)
{
    /* stub */
}

int Role::UpdatePath(float deltatime)
{
    /* stub */
    return 0;
}

void Role::UpdateTalk()
{
    /* stub */
}

void Role::OnChangeAct()
{
    /* stub */
}

int Role::IsCollideRay(gbRay * ray)
{
    /* stub */
    return 0;
}

void Role::UpdatePetFollow(float deltaTime)
{
    /* stub */
}

bool Role::WalkToByAct(int tilex, int tilez, char * act_name)
{
    /* stub */
    return FALSE;
}

void Role::Tired()
{
    /* stub */
}

void Role::ShowActEnd()
{
    /* stub */
}

float Role::GetWalkSpeed()
{
    /* stub */
    return 0.0f;
}

bool Role::PathTo(int tilex, int tilez, ACTION_KIND act)
{
    /* stub */
    return FALSE;
}

bool Role::PathTo(gbVec3D * dest, ACTION_KIND act)
{
    /* stub */
    return FALSE;
}

void Role::SetAlpha(float alpha)
{
    /* stub */
}

void Role::GetHeadPos(gbVec3D * out)
{
    /* stub */
}

int Role::mFindPlayer()
{
    /* stub */
    return 0;
}

void Role::Glow_Attach(gbRenderEffect * eft)
{
    /* stub */
}

void Role::TalkCancle()
{
    /* stub */
}

void Role::EvasionPlayer(float delta)
{
    /* stub */
}

void Role::Velocity2Steer(gbVec3D * velocity)
{
    /* stub */
}

void Role::MoveTo(gbVec3D * dest, ACTION_KIND act)
{
    /* stub */
}

void Role::MoveTo(ulong tilex, ulong tilez, ACTION_KIND act)
{
    /* stub */
}

int Role::IsPointInView(gbVec3D * pt, uchar bDist)
{
    /* stub */
    return 0;
}

void Role::Render(gbMatrixStack * pview, gbRenderEffect * eft)
{
    /* stub */
}

void Role::CGWander()
{
    /* stub */
}

void Role::SetTexture(char * texname)
{
    /* stub */
}

void Role::MoveBack(float dist)
{
    /* stub */
}

int Role::IsCollideOBB(gbOBBox * box)
{
    /* stub */
    return 0;
}

int Role::IsCollideRayByScale(gbRay * ray, float scale)
{
    /* stub */
    return 0;
}

void Role::PathMove(gbVec3D * dest, int layer, ACTION_KIND act, int forceRePath)
{
    /* stub */
}

void Role::mPursuit()
{
    /* stub */
}

float Role::GetATKSpeed()
{
    /* stub */
    return 0.0f;
}

void Role::Stand()
{
    /* stub */
}

void Role::Monster_Wander()
{
    /* stub */
}

void Role::Glow_GetAABB(gbAABBox * _box)
{
    /* stub */
}

Role::Role()
{
    /* stub */
}

void Role::CtrlSetVelocity(gbVec3D * vel, ACTION_KIND act)
{
    /* stub */
}

int Role::AutoPosition(gbVec3D * nextpt)
{
    /* stub */
    return 0;
}

void Role::NPC_Wander()
{
    /* stub */
}

void Role::Init()
{
    /* stub */
}

void Role::Check(SceneObj * obj)
{
    /* stub */
}

void Role::DumpCmdQueue()
{
    /* stub */
}

int Role::GetShadowQuad(gbGeomQuad * quad)
{
    /* stub */
    return 0;
}

void Role::AMove(float destX, float destZ, ACTION_KIND act)
{
    /* stub */
}

void Role::AMove(gbVec3D * dest, ACTION_KIND act)
{
    /* stub */
}

void Role::UpdateSeek(float param)
{
    /* stub */
}

int Role::UpdateSpecialAct(float deltaTime, ulong dwMsg)
{
    /* stub */
    return 0;
}

void SFLB_MakeFightInfo(int numMonster, ulong id0, ulong id1, ulong id2, ulong bossid, FightInfo * pInfo)
{
    /* stub */
}

void MakeFightInfo(int numMonster, ulong id0, ulong id1, ulong id2, ulong bossid, FightInfo * pInfo)
{
    /* stub */
}

ACTION_KIND _MapNpcAct(ACTION_KIND act, uchar kind, Role * pRole)
{
    /* stub */
    return (ACTION_KIND)0;
}

bool myPointInRect(tagPOINT * pt, tagRECT * rc)
{
    /* stub */
    return FALSE;
}

