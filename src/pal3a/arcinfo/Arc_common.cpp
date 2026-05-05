#include "Arc_common.h"

ARC_PlayerItem ARC_Inventory::GetItem(ARC_PlayerItem * __$ReturnUdt)
{
    /* stub */
    static ARC_PlayerItem _ret; memset(&_ret, 0, sizeof(_ret)); return _ret;
}

bool ARC_Inventory::Read(_iobuf * fp)
{
    /* stub */
    return FALSE;
}

int ARC_Inventory::TypeArrayBuild(ARC_PlayerItem_Type type)
{
    /* stub */
    return 0;
}

ARC_PlayerItem ARC_Inventory::TypeArray(ARC_PlayerItem * __$ReturnUdt)
{
    /* stub */
    static ARC_PlayerItem _ret; memset(&_ret, 0, sizeof(_ret)); return _ret;
}

void ARC_Inventory::Clear()
{
    /* stub */
}

int ARC_Inventory::GetTotalNum()
{
    /* stub */
    return 0;
}

ARC_PlayerItem * ARC_Inventory::Find(ARC_PlayerItem * item)
{
    /* stub */
    return NULL;
}

int ARC_Inventory::TypeArraySize()
{
    /* stub */
    return 0;
}

void ARC_PlayerAtt::CalMaxRV(uchar isAll)
{
    /* stub */
}

bool ARC_PlayerMgrInfo::LoadData(_iobuf * fp)
{
    /* stub */
    return FALSE;
}

unsigned long ARC_Reoccupy::GetID(int cur)
{
    /* stub */
    return 0;
}

int ARC_Reoccupy::GetNum()
{
    /* stub */
    return 0;
}

bool ARC_Reoccupy::Read(_iobuf * fp)
{
    /* stub */
    return FALSE;
}

bool LoadARCFile(_iobuf * fp)
{
    /* stub */
    return FALSE;
}

bool LoadArcBrief(int index, ARC_ArcBrief * brief)
{
    /* stub */
    return FALSE;
}

