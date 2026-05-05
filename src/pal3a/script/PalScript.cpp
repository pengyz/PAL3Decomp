#include "PalScript.h"

int PalScript::Update(float deltatime)
{
    /* stub */
    return 0;
}

void PalScript::ClearAllCamObj()
{
    /* stub */
}

PalScript::~PalScript()
{
    /* stub */
}

void PalScript::ClearAllWaitObj()
{
    /* stub */
}

void PalScript::Destroy()
{
    /* stub */
}

void PalScript::AddCamObj(PalScriptWaitObj * obj)
{
    /* stub */
}

void PalScript::AddWaitObj(PalScriptWaitObj * obj)
{
    /* stub */
}

PalScript::PalScript()
{
    /* stub */
}

PalScript * PalScriptMgr::FindScript(scScriptInstance * pinst)
{
    /* stub */
    return NULL;
}

void PalScriptMgr::RunSceneScript(char * cityname, char * name)
{
    /* stub */
}

void PalScriptMgr::_CON_CloseScript(char * agv)
{
    /* stub */
}

void PalScriptMgr::ClearAllScript()
{
    /* stub */
}

unsigned long PalScriptMgr::FindScriptByDesc(char * desc)
{
    /* stub */
    return 0;
}

void PalScriptMgr::Destroy()
{
    /* stub */
}

PalScriptMgr::~PalScriptMgr()
{
    /* stub */
}

void PalScriptMgr::OpenSCE(char * filename)
{
    /* stub */
}

void PalScriptMgr::InitSys()
{
    /* stub */
}

void PalScriptMgr::_CON_State(char * agv)
{
    /* stub */
}

bool PalScriptMgr::IfAnyScriptRunning()
{
    /* stub */
    return FALSE;
}

void PalScriptMgr::_CON_ReLoadScript(char * agv)
{
    /* stub */
}

bool PalScriptMgr::IfHaveScript(ulong id)
{
    /* stub */
    return FALSE;
}

void PalScriptMgr::Update(float deltatime)
{
    /* stub */
}

PalScriptMgr::PalScriptMgr()
{
    /* stub */
}

PalScript * PalScriptMgr::RunScript(ulong id, uchar bBigMap)
{
    /* stub */
    return NULL;
}

int PalScriptMgr::IsScriptRuning(PalScript * pal)
{
    /* stub */
    return 0;
}

