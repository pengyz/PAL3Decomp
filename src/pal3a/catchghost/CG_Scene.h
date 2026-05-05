#ifndef PAL3A_CG_SCENE_H
#define PAL3A_CG_SCENE_H

#include "pal3a_types.h"

class CG_Scene {
public:
    char _data[474200];

    OBJHELPER * GetLastObjHelper();
    void UpdateBossHurt(float deltatime);
    void BeAttack(int ATKNum);
    void BeAttack(Role * pRole);
    void CGPROP_BLOOD_CANTRIP();
    void RenderFling(gbMatrixStack * pView);
    void OverMaster(Role * pRole);
    void DestroyNPC();
    void RoleFlingProp(ulong dwItemID);
    void ConfigOBJ(int ObjType, gbVec3D pos);
    void HitObj(Role * pRole, int type, gbVec3D pos, int id);
    void CGPROP_MIRROR();
    int IsInRattrapArea(Role * pRole);
    gbVec3D GetValidPos();
    gbVec3D GetValidPos(gbVec3D * __$ReturnUdt);
    void ConfigNPC(char * name, ulong roleid, gbVec3D pos, Role * role, int id);
    void UpdateFling(float fTime);
    void CheckGameResult();
    void CheckSpecialAttack(gbVec3D pos, float radius, int nHPHit);
    void Run();
    void CGPROP_FIRE_SIGNAL(SceneProp * prop);
    void UpdateMonsterRelive(float deltatime);
    void UpdateNGHHurt(float deltatime);
    void DelObj(int index);
    ~CG_Scene();
    void CGPROP_RATTRAP();
    void Render(gbMatrixStack * pView);
    gbVec3D GetValidRandPos(gbVec3D * __$ReturnUdt, gbVec3D pos);
    void DestroyOBJ();
    void UpdateFlingAct(float fTime);
    void AppendObj(SceneObj * pObj);
    void Init(int nLevel);
    void UseFlingAct(CG_PROPINFO CGPROP, ulong propid, gbVec3D * pos);
    void EffectOverAndCheckLink(float deltatime);
    int FindNearestMoney(Role * pRole, SceneProp * * Out);
    void CGPROP_TARTAREAN_MONEY(SceneProp * prop);
    CG_Scene(CG_Entry * pFather);
    void Update(float deltatime);
    void LoadScene(char * cityname, char * area);
    void BeHurt(int nHurt);
    void DelLastObj();
    void DrawObjArea(uchar bTex);
    void ParseBarrierByRect();
    bool IsSegColTriangle(gbVec3D rayStart, gbVec3D rayEnd, gbVec3D tv1, gbVec3D tv2, gbVec3D tv3, gbVec3D * vOut);
    void SetLastObjHelper(tagRECT rTouchArea, tagPOINT pGroundPt);
    bool ColBarrier(gbVec3D start, gbVec3D end, gbVec3D * vOut);
    void RenderBarrier(uchar bFill);
    void LoadObjParam();
    void ParseBarrier();
    int GetKeyVal(char** srcKey, char * cmpKey);
};

class ObjParam {
public:
    char _data[64];

    bool CanBeLink(int nType, float * fWaitTime);
};

class SceneProp {
public:
    char _data[64];

    SceneProp(ulong dwID, float validtime, gbVec3D * pos);
};

#endif // PAL3A_CG_SCENE_H
