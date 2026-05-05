#ifndef PAL3A_PLAYERMGR_H
#define PAL3A_PLAYERMGR_H

#include "pal3a_types.h"

class Inventory {
public:
    char _data[40];

    void Read(_iobuf * fp);
    PlayerItem GetItem(PlayerItem * __$ReturnUdt);
    int TypeArrayUsable(PlayerItem_Type type, int Role);
    void Write(_iobuf * fp);
    ~Inventory();
    void ReadNot1st(_iobuf * fp);
    int RemoveItem(PlayerItem * item);
    void AddItem(PlayerItem * item);
    Inventory();
    void Read2(_iobuf * fp);
    int TypeArraySize();
    PlayerItem * Find(PlayerItem * item);
    void TypeArraySort(int by);
    int FindItemByMdl(char * mdl);
    PlayerItem TypeArray(PlayerItem * __$ReturnUdt);
    int TypeArrayBuild(PlayerItem_Type type);
    int GetTotalNum();
    void Clear();
};

class PlayerAtt {
public:
    char _data[64];

    void CalMaxRV(uchar isAll);
};

class PlayerMgr {
public:
    char _data[1];

    int GetRoleValue(ushort id, RoleValue valuekind);
    void UseBee();
    int CalRoleFull_HP(int role, int level);
    void UpdateMsg(float deltatime);
    void Update(float deltatime);
    void SetRoleLevel(int nRoleID, int nLevel, uchar bCalExp, uchar bShowMsg);
    void SetInitState();
    void TeamOpenA(int blockscript);
    void TeamCloseA(int blockscript);
    void TeamClose(int blockscript);
    ~PlayerMgr();
    int CalRoleFull_ATK(int role, int level);
    void ClearMsg();
    PlayerMgr();
    int CalRoleFull_MP(int role, int level);
    void AddSkill(int roleid, int skillid);
    void StartFightState(FightState fs);
    void SetRoleValue(ushort id, RoleValue valuekind, int val);
    void OnLoad2(_iobuf * fp);
    void WaterMagic(int bActive);
    void StartNGHEffect();
    void Hurt(int num, uchar bSnd, uchar bSingle);
    int GetNumInTeam();
    void Create();
    void OnLoad(_iobuf * fp);
    void UpdateMagicByLV(int RoleID, uchar bShowMsg);
    void LoadUseableMagic(int nRoleIndex);
    void GetRoleMagicByLv(int nRoleID, int lv, uchar bShowMsg);
    void RenderWPX(gbMatrixStack * pview);
    void Obj_Hurt(float percent, uchar bSnd, uchar bSingle);
    void ActiveFYS(int index, ACTION_KIND act);
    void SetHuaYingMode(int mode);
    void DrawMsg();
    void TeamOpen(int blockscript);
    void AddMoney(int add);
    void Destroy();
    void SetPoison(FightState p, uchar check, int nInitCounter);
    void ActivePlayer(int index);
    void OnSceneChanged();
    void LoadUseableSkill(int nRoleIndex);
    void StopNGHEffect();
    void SetCtrl(int i, uchar bCopyLast);
    int CalRoleFull_DEF(int role, int level);
    void FullRoleValue(ushort id, RoleValue valuekind);
    void Init();
    void CombatSkill2UISkill();
    void UISkill2CombatSkill();
    void PushMsg(char * msg);
    void InitNot1st();
    void RenderNGHVarianceEffect(gbMatrixStack * pView);
    void Render(gbMatrixStack * pview);
    int CalRoleFull_GP(int role, int level);
    void OnSave(_iobuf * fp);
    void DrawHuaying(gbMatrixStack * pview);
    void AddFavor(int roleid, int add);
    Role * GetRole(ushort id);
    void UpdateFYS(float deltatime);
};

class Reoccupy {
public:
    char _data[16];

    unsigned long GetID(int cur);
    int GetNum();
    bool Remove(ulong id);
    ~Reoccupy();
    bool AddNew(ulong id);
    void Write(_iobuf * fp);
    void Read(_iobuf * fp);
    bool FindID(ulong id);
    Reoccupy();
};

#endif // PAL3A_PLAYERMGR_H
