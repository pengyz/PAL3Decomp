#include "Archive.h"

void ArcScene::Write(_iobuf * fp)
{
    /* stub */
}

void ArcScene::Read(_iobuf * fp)
{
    /* stub */
}

Archive * Archive::Inst()
{
    /* stub */
    return NULL;
}

int Archive::LoadBrief(int index, ArcBrief * out)
{
    /* stub */
    return 0;
}

Archive::~Archive()
{
    /* stub */
}

void Archive::ReadScene(Scene * scene)
{
    /* stub */
}

void Archive::_ResteScn()
{
    /* stub */
}

void Archive::SFLB_OnSave(_iobuf * fp, ArcHeader * header)
{
    /* stub */
}

ArcScene * Archive::GetLastScene()
{
    /* stub */
    return NULL;
}

bool Archive::IsScenePast(char * cityname, char * name)
{
    /* stub */
    return FALSE;
}

void Archive::SaveScene(Scene * scene)
{
    /* stub */
}

int Archive::Delete(int index)
{
    /* stub */
    return 0;
}

int Archive::Load(int index)
{
    /* stub */
    return 0;
}

bool Archive::IsObjNotLoad(ulong id)
{
    /* stub */
    return FALSE;
}

void Archive::ScenePast(char * cityname, char * name)
{
    /* stub */
}

ArcScene * Archive::FindScene(char * cityName, char * name)
{
    /* stub */
    return NULL;
}

void Archive::OnLoad(_iobuf * fp, ArcHeader * header)
{
    /* stub */
}

int Archive::InitGameNotFirst(_iobuf * fp)
{
    /* stub */
    return 0;
}

void Archive::Init()
{
    /* stub */
}

Archive::Archive()
{
    /* stub */
}

void Archive::AddObjNotLoad(ulong id)
{
    /* stub */
}

SceneInfo * Archive::GetLastSaveScene()
{
    /* stub */
    return NULL;
}

ObjectInfo * Archive::FindObj(char * cityName, char * name, int ID)
{
    /* stub */
    return NULL;
}

SaveTask * Archive::FindObjSavedTask(char * cityName, char * name, int ID)
{
    /* stub */
    return NULL;
}

int Archive::Save(int index)
{
    /* stub */
    return 0;
}

int PrepareDir()
{
    /* stub */
    return 0;
}

int IfDir(char * pFileName)
{
    /* stub */
    return 0;
}

