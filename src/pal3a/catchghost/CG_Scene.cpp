#include "CG_Scene.h"

OBJHELPER * CG_Scene::GetLastObjHelper()
{
    /* stub */
    return NULL;
}

void CG_Scene::UpdateBossHurt(float deltatime)
{
    /* stub */
}

void CG_Scene::BeAttack(int ATKNum)
{
    /* stub */
}

void CG_Scene::BeAttack(Role * pRole)
{
    /* stub */
}

void CG_Scene::CGPROP_BLOOD_CANTRIP()
{
    /* stub */
}

void CG_Scene::RenderFling(gbMatrixStack * pView)
{
    /* stub */
}

void CG_Scene::OverMaster(Role * pRole)
{
    /* stub */
}

void CG_Scene::DestroyNPC()
{
    /* stub */
}

void CG_Scene::RoleFlingProp(ulong dwItemID)
{
    /* stub */
}

void CG_Scene::ConfigOBJ(int ObjType, gbVec3D pos)
{
    /* stub */
}

void CG_Scene::HitObj(Role * pRole, int type, gbVec3D pos, int id)
{
    /* stub */
}

void CG_Scene::CGPROP_MIRROR()
{
    /* stub */
}

int CG_Scene::IsInRattrapArea(Role * pRole)
{
    /* stub */
    return 0;
}

gbVec3D CG_Scene::GetValidPos()
{
    /* stub */
    gbVec3D _ret = {0}; return _ret;
}

gbVec3D CG_Scene::GetValidPos(gbVec3D * __$ReturnUdt)
{
    /* stub */
    gbVec3D _ret = {0}; return _ret;
}

void CG_Scene::ConfigNPC(char * name, ulong roleid, gbVec3D pos, Role * role, int id)
{
    /* stub */
}

void CG_Scene::UpdateFling(float fTime)
{
    /* stub */
}

void CG_Scene::CheckGameResult()
{
    /* stub */
}

void CG_Scene::CheckSpecialAttack(gbVec3D pos, float radius, int nHPHit)
{
    /* stub */
}

void CG_Scene::Run()
{
    /* stub */
}

void CG_Scene::CGPROP_FIRE_SIGNAL(SceneProp * prop)
{
    /* stub */
}

void CG_Scene::UpdateMonsterRelive(float deltatime)
{
    /* stub */
}

void CG_Scene::UpdateNGHHurt(float deltatime)
{
    /* stub */
}

void CG_Scene::DelObj(int index)
{
    /* stub */
}

CG_Scene::~CG_Scene()
{
    /* stub */
}

void CG_Scene::CGPROP_RATTRAP()
{
    /* stub */
}

void CG_Scene::Render(gbMatrixStack * pView)
{
    /* stub */
}

gbVec3D CG_Scene::GetValidRandPos(gbVec3D * __$ReturnUdt, gbVec3D pos)
{
    /* stub */
    gbVec3D _ret = {0}; return _ret;
}

void CG_Scene::DestroyOBJ()
{
    /* stub */
}

void CG_Scene::UpdateFlingAct(float fTime)
{
    /* stub */
}

void CG_Scene::AppendObj(SceneObj * pObj)
{
    /* stub */
}

void CG_Scene::Init(int nLevel)
{
    /* stub */
}

void CG_Scene::UseFlingAct(CG_PROPINFO CGPROP, ulong propid, gbVec3D * pos)
{
    /* stub */
}

void CG_Scene::EffectOverAndCheckLink(float deltatime)
{
    /* stub */
}

int CG_Scene::FindNearestMoney(Role * pRole, SceneProp * * Out)
{
    /* stub */
    return 0;
}

void CG_Scene::CGPROP_TARTAREAN_MONEY(SceneProp * prop)
{
    /* stub */
}

CG_Scene::CG_Scene(CG_Entry * pFather)
{
    /* stub */
}

void CG_Scene::Update(float deltatime)
{
    /* stub */
}

void CG_Scene::LoadScene(char * cityname, char * area)
{
    /* stub */
}

void CG_Scene::BeHurt(int nHurt)
{
    /* stub */
}

void CG_Scene::DelLastObj()
{
    /* stub */
}

void CG_Scene::DrawObjArea(uchar bTex)
{
    /* stub */
}

void CG_Scene::ParseBarrierByRect()
{
    /* stub */
}

bool CG_Scene::IsSegColTriangle(gbVec3D rayStart, gbVec3D rayEnd, gbVec3D tv1, gbVec3D tv2, gbVec3D tv3, gbVec3D * vOut)
{
    /* stub */
    return FALSE;
}

void CG_Scene::SetLastObjHelper(tagRECT rTouchArea, tagPOINT pGroundPt)
{
    /* stub */
}

bool CG_Scene::ColBarrier(gbVec3D start, gbVec3D end, gbVec3D * vOut)
{
    /* stub */
    return FALSE;
}

void CG_Scene::RenderBarrier(uchar bFill)
{
    /* stub */
}

void CG_Scene::LoadObjParam()
{
    /* stub */
}

void CG_Scene::ParseBarrier()
{
    /* stub */
}

int CG_Scene::GetKeyVal(char** srcKey, char * cmpKey)
{
    /* stub */
    return 0;
}

bool ObjParam::CanBeLink(int nType, float * fWaitTime)
{
    /* stub */
    return FALSE;
}

SceneProp::SceneProp(ulong dwID, float validtime, gbVec3D * pos)
{
    /* stub */
}

