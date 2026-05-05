#ifndef PAL3A_SCENE_H
#define PAL3A_SCENE_H

#include "pal3a_types.h"

class Scene {
public:
    char _data[1094164];

    SceneObj * GetObjByID(ushort id);
    void OnSceneOut();
    void RenderBillBoard();
    NavTileLayer * GetTileLayer(int layer);
    SceneObj * GetObjSelect_RoleCtrl();
    int GetAABB(gbAABBox * pbox);
    void SceneRelation();
    Role * GetNpcByID(uchar id);
    int CanDirectGo(int onlayer, int x1, int y1, int x2, int y2, tagPOINT * nearcango);
    int CanDirectGo(int onlayer, int x1, int y1, int x2, int y2);
    void RenderSpecNPC(gbMatrixStack * pview);
    void AppendObj(SceneObj * pObj, int layer);
    Scene();
    void RenderWaterObject(gbMatrixStack * pview);
    void LoadGardenInfo();
    ~Scene();
    void ClearNpc();
    SceneObj * GetObjSelect(gbRay * ray);
    void JT_Exhibit();
    void LoadGeom(char * cityname, char * name);
    bool Rect_Rect(tagRECT * rc1, tagRECT * rc2);
    SceneMapObj * GetObjMap(int layer);
    int CanGoTile_NoObj(int onlayer, int x, int y);
    int CanGoTile_NoObj(int onlayer, gbVec3D pos);
    void Update(double deltaTime);
    Role * FindRole(ushort id);
    void LoadDataCG();
    void ClearObj();
    void InterActPt(gbVec3D _pt, int onlayer);
    void DelLastObj();
    int CanGoTile(int onlayer, int x, int y, uchar roleid);
    int CanGoTile(int onlayer, int x, int y, Role * pRole);
    int CanGoTile(int onlayer, gbVec3D * pos, Role * pRole);
    int CanGoTile(int onlayer, gbVec3D * pos, uchar roleid);
    void AppendNpc(Role * pNPC);
    void InterActRole_CG(Role * role, float deltatime);
    void InterActRole(Role * role, float deltatime, uchar jump);
    void InterActRole_CGSpecial(Role * role, float deltatime);
    void Render(gbMatrixStack * pview);
    int Obj_CanRoleGoTile(uchar iobj, int onlayer, int x, int y);
    int CanJump(int onlayer, int x1, int y1, int x2, int y2, tagPOINT * nearcango);
    int CanJump(int onlayer, int x, int y);
    SceneObj * GetObjByPos(int onlayer, int tilex, int tilez);
    NavFaceLayer * GetFaceLayer(int layer);
    void DelObj(int index);
    float GetTileHeight(int onlayer, gbVec3D * pos, tagPOINT * out, int * kind);
    float GetTileHeight(int onlayer, int x, int y, int * kind);
    void Render2(gbMatrixStack * pview);
    float GetFloorHeight(int onlayer, gbVec3D * pos);
    void OnSceneIn();
    void RenderSceneCVD(gbMatrixStack * pview);
    int Obj_CanDirectGo(uchar obj, int onlayer, int x1, int y1, int x2, int y2);
    void LoadData(SCNFile * file, int reload);
    void RefreshSpecialObjFloor();
    void ResetSceneObj();
    void RenderNPC(gbMatrixStack * pview);
    void ClearFloor(int onlayer);
    void Destroy();
    void DrawNPCView();
    int IsPlayerInNPCView();
    void UseSeekingMouse();
    int CanGoTileEX(int onlayer, gbVec3D * pos, Role * pRole);
};

class SceneMap {
public:
    char _data[16];

    void Destroy();
    unsigned char Get(uint x, uint y);
    void Create(NavTileLayer * layer);
    void Clip(tagRECT * rc);
    void WriteRect(tagRECT * rc, uchar val);
    void Clear();
    SceneMap();
    void Init(uchar val);
    void WriteRectO(ORect * rc, uchar val);
    ~SceneMap();
    void WriteCircle(tagPOINT center, int r, uchar val);
};

class SceneMapObj {
public:
    char _data[20];

    void Append(Scene * scene, int onlayer);
    ~SceneMapObj();
    void Destroy();
    SceneMapObj();
    void Create(Scene * scene, int onlayer);
};

class SceneMapPlayer {
public:
    char _data[392];

    void Build();
    void UpdateRect(tagRECT rc, uchar bTest);
    void Update_CG();
    void Destroy();
    bool IsScene(SceneInfo * info);
    void Read(_iobuf * fp);
    void Create(NavTileLayer * layer, SceneInfo * info);
    void ClearName();
    ~SceneMapPlayer();
    SceneMapPlayer();
    void Write(_iobuf * fp);
    void Update(int type);
};

char * GetQ02CPK_FromArea(char * area);
void GeomLoadProgress(int maxnode, int loadnode);
void UpdateLoading();

#endif // PAL3A_SCENE_H
