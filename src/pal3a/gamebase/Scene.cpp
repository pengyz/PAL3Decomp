#include "Scene.h"

SceneObj * Scene::GetObjByID(ushort id)
{
    /* stub */
    return NULL;
}

void Scene::OnSceneOut()
{
    /* stub */
}

void Scene::RenderBillBoard()
{
    /* stub */
}

NavTileLayer * Scene::GetTileLayer(int layer)
{
    /* stub */
    return NULL;
}

SceneObj * Scene::GetObjSelect_RoleCtrl()
{
    /* stub */
    return NULL;
}

int Scene::GetAABB(gbAABBox * pbox)
{
    /* stub */
    return 0;
}

void Scene::SceneRelation()
{
    /* stub */
}

Role * Scene::GetNpcByID(uchar id)
{
    /* stub */
    return NULL;
}

int Scene::CanDirectGo(int onlayer, int x1, int y1, int x2, int y2, tagPOINT * nearcango)
{
    /* stub */
    return 0;
}

int Scene::CanDirectGo(int onlayer, int x1, int y1, int x2, int y2)
{
    /* stub */
    return 0;
}

void Scene::RenderSpecNPC(gbMatrixStack * pview)
{
    /* stub */
}

void Scene::AppendObj(SceneObj * pObj, int layer)
{
    /* stub */
}

Scene::Scene()
{
    /* stub */
}

void Scene::RenderWaterObject(gbMatrixStack * pview)
{
    /* stub */
}

void Scene::LoadGardenInfo()
{
    /* stub */
}

Scene::~Scene()
{
    /* stub */
}

void Scene::ClearNpc()
{
    /* stub */
}

SceneObj * Scene::GetObjSelect(gbRay * ray)
{
    /* stub */
    return NULL;
}

void Scene::JT_Exhibit()
{
    /* stub */
}

void Scene::LoadGeom(char * cityname, char * name)
{
    /* stub */
}

bool Scene::Rect_Rect(tagRECT * rc1, tagRECT * rc2)
{
    /* stub */
    return FALSE;
}

SceneMapObj * Scene::GetObjMap(int layer)
{
    /* stub */
    return NULL;
}

int Scene::CanGoTile_NoObj(int onlayer, int x, int y)
{
    /* stub */
    return 0;
}

int Scene::CanGoTile_NoObj(int onlayer, gbVec3D pos)
{
    /* stub */
    return 0;
}

void Scene::Update(double deltaTime)
{
    /* stub */
}

Role * Scene::FindRole(ushort id)
{
    /* stub */
    return NULL;
}

void Scene::LoadDataCG()
{
    /* stub */
}

void Scene::ClearObj()
{
    /* stub */
}

void Scene::InterActPt(gbVec3D _pt, int onlayer)
{
    /* stub */
}

void Scene::DelLastObj()
{
    /* stub */
}

int Scene::CanGoTile(int onlayer, int x, int y, uchar roleid)
{
    /* stub */
    return 0;
}

int Scene::CanGoTile(int onlayer, int x, int y, Role * pRole)
{
    /* stub */
    return 0;
}

int Scene::CanGoTile(int onlayer, gbVec3D * pos, Role * pRole)
{
    /* stub */
    return 0;
}

int Scene::CanGoTile(int onlayer, gbVec3D * pos, uchar roleid)
{
    /* stub */
    return 0;
}

void Scene::AppendNpc(Role * pNPC)
{
    /* stub */
}

void Scene::InterActRole_CG(Role * role, float deltatime)
{
    /* stub */
}

void Scene::InterActRole(Role * role, float deltatime, uchar jump)
{
    /* stub */
}

void Scene::InterActRole_CGSpecial(Role * role, float deltatime)
{
    /* stub */
}

void Scene::Render(gbMatrixStack * pview)
{
    /* stub */
}

int Scene::Obj_CanRoleGoTile(uchar iobj, int onlayer, int x, int y)
{
    /* stub */
    return 0;
}

int Scene::CanJump(int onlayer, int x1, int y1, int x2, int y2, tagPOINT * nearcango)
{
    /* stub */
    return 0;
}

int Scene::CanJump(int onlayer, int x, int y)
{
    /* stub */
    return 0;
}

SceneObj * Scene::GetObjByPos(int onlayer, int tilex, int tilez)
{
    /* stub */
    return NULL;
}

NavFaceLayer * Scene::GetFaceLayer(int layer)
{
    /* stub */
    return NULL;
}

void Scene::DelObj(int index)
{
    /* stub */
}

float Scene::GetTileHeight(int onlayer, gbVec3D * pos, tagPOINT * out, int * kind)
{
    /* stub */
    return 0.0f;
}

float Scene::GetTileHeight(int onlayer, int x, int y, int * kind)
{
    /* stub */
    return 0.0f;
}

void Scene::Render2(gbMatrixStack * pview)
{
    /* stub */
}

float Scene::GetFloorHeight(int onlayer, gbVec3D * pos)
{
    /* stub */
    return 0.0f;
}

void Scene::OnSceneIn()
{
    /* stub */
}

void Scene::RenderSceneCVD(gbMatrixStack * pview)
{
    /* stub */
}

int Scene::Obj_CanDirectGo(uchar obj, int onlayer, int x1, int y1, int x2, int y2)
{
    /* stub */
    return 0;
}

void Scene::LoadData(SCNFile * file, int reload)
{
    /* stub */
}

void Scene::RefreshSpecialObjFloor()
{
    /* stub */
}

void Scene::ResetSceneObj()
{
    /* stub */
}

void Scene::RenderNPC(gbMatrixStack * pview)
{
    /* stub */
}

void Scene::ClearFloor(int onlayer)
{
    /* stub */
}

void Scene::Destroy()
{
    /* stub */
}

void Scene::DrawNPCView()
{
    /* stub */
}

int Scene::IsPlayerInNPCView()
{
    /* stub */
    return 0;
}

void Scene::UseSeekingMouse()
{
    /* stub */
}

int Scene::CanGoTileEX(int onlayer, gbVec3D * pos, Role * pRole)
{
    /* stub */
    return 0;
}

void SceneMap::Destroy()
{
    /* stub */
}

unsigned char SceneMap::Get(uint x, uint y)
{
    /* stub */
    return 0;
}

void SceneMap::Create(NavTileLayer * layer)
{
    /* stub */
}

void SceneMap::Clip(tagRECT * rc)
{
    /* stub */
}

void SceneMap::WriteRect(tagRECT * rc, uchar val)
{
    /* stub */
}

void SceneMap::Clear()
{
    /* stub */
}

SceneMap::SceneMap()
{
    /* stub */
}

void SceneMap::Init(uchar val)
{
    /* stub */
}

void SceneMap::WriteRectO(ORect * rc, uchar val)
{
    /* stub */
}

SceneMap::~SceneMap()
{
    /* stub */
}

void SceneMap::WriteCircle(tagPOINT center, int r, uchar val)
{
    /* stub */
}

void SceneMapObj::Append(Scene * scene, int onlayer)
{
    /* stub */
}

SceneMapObj::~SceneMapObj()
{
    /* stub */
}

void SceneMapObj::Destroy()
{
    /* stub */
}

SceneMapObj::SceneMapObj()
{
    /* stub */
}

void SceneMapObj::Create(Scene * scene, int onlayer)
{
    /* stub */
}

void SceneMapPlayer::Build()
{
    /* stub */
}

void SceneMapPlayer::UpdateRect(tagRECT rc, uchar bTest)
{
    /* stub */
}

void SceneMapPlayer::Update_CG()
{
    /* stub */
}

void SceneMapPlayer::Destroy()
{
    /* stub */
}

bool SceneMapPlayer::IsScene(SceneInfo * info)
{
    /* stub */
    return FALSE;
}

void SceneMapPlayer::Read(_iobuf * fp)
{
    /* stub */
}

void SceneMapPlayer::Create(NavTileLayer * layer, SceneInfo * info)
{
    /* stub */
}

void SceneMapPlayer::ClearName()
{
    /* stub */
}

SceneMapPlayer::~SceneMapPlayer()
{
    /* stub */
}

SceneMapPlayer::SceneMapPlayer()
{
    /* stub */
}

void SceneMapPlayer::Write(_iobuf * fp)
{
    /* stub */
}

void SceneMapPlayer::Update(int type)
{
    /* stub */
}

char * GetQ02CPK_FromArea(char * area)
{
    /* stub */
    return NULL;
}

void GeomLoadProgress(int maxnode, int loadnode)
{
    /* stub */
}

void UpdateLoading()
{
    /* stub */
}

