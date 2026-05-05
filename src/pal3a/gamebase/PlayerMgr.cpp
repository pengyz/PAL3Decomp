#include "PlayerMgr.h"

void Inventory::Read(_iobuf * fp)
{
    /* stub */
}

PlayerItem Inventory::GetItem(PlayerItem * __$ReturnUdt)
{
    /* stub */
    static PlayerItem _ret; memset(&_ret, 0, sizeof(_ret)); return _ret;
}

int Inventory::TypeArrayUsable(PlayerItem_Type type, int Role)
{
    /* stub */
    return 0;
}

void Inventory::Write(_iobuf * fp)
{
    /* stub */
}

Inventory::~Inventory()
{
    /* stub */
}

void Inventory::ReadNot1st(_iobuf * fp)
{
    /* stub */
}

int Inventory::RemoveItem(PlayerItem * item)
{
    /* stub */
    return 0;
}

void Inventory::AddItem(PlayerItem * item)
{
    /* stub */
}

Inventory::Inventory()
{
    /* stub */
}

void Inventory::Read2(_iobuf * fp)
{
    /* stub */
}

int Inventory::TypeArraySize()
{
    /* stub */
    return 0;
}

PlayerItem * Inventory::Find(PlayerItem * item)
{
    /* stub */
    return NULL;
}

void Inventory::TypeArraySort(int by)
{
    /* stub */
}

int Inventory::FindItemByMdl(char * mdl)
{
    /* stub */
    return 0;
}

PlayerItem Inventory::TypeArray(PlayerItem * __$ReturnUdt)
{
    /* stub */
    static PlayerItem _ret; memset(&_ret, 0, sizeof(_ret)); return _ret;
}

int Inventory::TypeArrayBuild(PlayerItem_Type type)
{
    /* stub */
    return 0;
}

int Inventory::GetTotalNum()
{
    /* stub */
    return 0;
}

void Inventory::Clear()
{
    /* stub */
}

void PlayerAtt::CalMaxRV(uchar isAll)
{
    /* stub */
}

int PlayerMgr::GetRoleValue(ushort id, RoleValue valuekind)
{
    /* stub */
    return 0;
}

void PlayerMgr::UseBee()
{
    /* stub */
}

int PlayerMgr::CalRoleFull_HP(int role, int level)
{
    /* stub */
    return 0;
}

void PlayerMgr::UpdateMsg(float deltatime)
{
    /* stub */
}

void PlayerMgr::Update(float deltatime)
{
    /* stub */
}

void PlayerMgr::SetRoleLevel(int nRoleID, int nLevel, uchar bCalExp, uchar bShowMsg)
{
    /* stub */
}

void PlayerMgr::SetInitState()
{
    /* stub */
}

void PlayerMgr::TeamOpenA(int blockscript)
{
    /* stub */
}

void PlayerMgr::TeamCloseA(int blockscript)
{
    /* stub */
}

void PlayerMgr::TeamClose(int blockscript)
{
    /* stub */
}

PlayerMgr::~PlayerMgr()
{
    /* stub */
}

int PlayerMgr::CalRoleFull_ATK(int role, int level)
{
    /* stub */
    return 0;
}

void PlayerMgr::ClearMsg()
{
    /* stub */
}

PlayerMgr::PlayerMgr()
{
    /* stub */
}

int PlayerMgr::CalRoleFull_MP(int role, int level)
{
    /* stub */
    return 0;
}

void PlayerMgr::AddSkill(int roleid, int skillid)
{
    /* stub */
}

void PlayerMgr::StartFightState(FightState fs)
{
    /* stub */
}

void PlayerMgr::SetRoleValue(ushort id, RoleValue valuekind, int val)
{
    /* stub */
}

void PlayerMgr::OnLoad2(_iobuf * fp)
{
    /* stub */
}

void PlayerMgr::WaterMagic(int bActive)
{
    /* stub */
}

void PlayerMgr::StartNGHEffect()
{
    /* stub */
}

void PlayerMgr::Hurt(int num, uchar bSnd, uchar bSingle)
{
    /* stub */
}

int PlayerMgr::GetNumInTeam()
{
    /* stub */
    return 0;
}

void PlayerMgr::Create()
{
    /* stub */
}

void PlayerMgr::OnLoad(_iobuf * fp)
{
    /* stub */
}

void PlayerMgr::UpdateMagicByLV(int RoleID, uchar bShowMsg)
{
    /* stub */
}

void PlayerMgr::LoadUseableMagic(int nRoleIndex)
{
    /* stub */
}

void PlayerMgr::GetRoleMagicByLv(int nRoleID, int lv, uchar bShowMsg)
{
    /* stub */
}

void PlayerMgr::RenderWPX(gbMatrixStack * pview)
{
    /* stub */
}

void PlayerMgr::Obj_Hurt(float percent, uchar bSnd, uchar bSingle)
{
    /* stub */
}

void PlayerMgr::ActiveFYS(int index, ACTION_KIND act)
{
    /* stub */
}

void PlayerMgr::SetHuaYingMode(int mode)
{
    /* stub */
}

void PlayerMgr::DrawMsg()
{
    /* stub */
}

void PlayerMgr::TeamOpen(int blockscript)
{
    /* stub */
}

void PlayerMgr::AddMoney(int add)
{
    /* stub */
}

void PlayerMgr::Destroy()
{
    /* stub */
}

void PlayerMgr::SetPoison(FightState p, uchar check, int nInitCounter)
{
    /* stub */
}

void PlayerMgr::ActivePlayer(int index)
{
    /* stub */
}

void PlayerMgr::OnSceneChanged()
{
    /* stub */
}

void PlayerMgr::LoadUseableSkill(int nRoleIndex)
{
    /* stub */
}

void PlayerMgr::StopNGHEffect()
{
    /* stub */
}

void PlayerMgr::SetCtrl(int i, uchar bCopyLast)
{
    /* stub */
}

int PlayerMgr::CalRoleFull_DEF(int role, int level)
{
    /* stub */
    return 0;
}

void PlayerMgr::FullRoleValue(ushort id, RoleValue valuekind)
{
    /* stub */
}

void PlayerMgr::Init()
{
    /* stub */
}

void PlayerMgr::CombatSkill2UISkill()
{
    /* stub */
}

void PlayerMgr::UISkill2CombatSkill()
{
    /* stub */
}

void PlayerMgr::PushMsg(char * msg)
{
    /* stub */
}

void PlayerMgr::InitNot1st()
{
    /* stub */
}

void PlayerMgr::RenderNGHVarianceEffect(gbMatrixStack * pView)
{
    /* stub */
}

void PlayerMgr::Render(gbMatrixStack * pview)
{
    /* stub */
}

int PlayerMgr::CalRoleFull_GP(int role, int level)
{
    /* stub */
    return 0;
}

void PlayerMgr::OnSave(_iobuf * fp)
{
    /* stub */
}

void PlayerMgr::DrawHuaying(gbMatrixStack * pview)
{
    /* stub */
}

void PlayerMgr::AddFavor(int roleid, int add)
{
    /* stub */
}

Role * PlayerMgr::GetRole(ushort id)
{
    /* stub */
    return NULL;
}

void PlayerMgr::UpdateFYS(float deltatime)
{
    /* stub */
}

unsigned long Reoccupy::GetID(int cur)
{
    /* stub */
    return 0;
}

int Reoccupy::GetNum()
{
    /* stub */
    return 0;
}

bool Reoccupy::Remove(ulong id)
{
    /* stub */
    return FALSE;
}

Reoccupy::~Reoccupy()
{
    /* stub */
}

bool Reoccupy::AddNew(ulong id)
{
    /* stub */
    return FALSE;
}

void Reoccupy::Write(_iobuf * fp)
{
    /* stub */
}

void Reoccupy::Read(_iobuf * fp)
{
    /* stub */
}

bool Reoccupy::FindID(ulong id)
{
    /* stub */
    return FALSE;
}

Reoccupy::Reoccupy()
{
    /* stub */
}

