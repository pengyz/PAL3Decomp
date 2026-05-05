#ifndef PAL3A_ARCHIVE_H
#define PAL3A_ARCHIVE_H

#include "pal3a_types.h"

class ArcScene {
public:
    char _data[64];

    void Write(_iobuf * fp);
    void Read(_iobuf * fp);
};

class Archive {
public:
    char _data[48];

    Archive * Inst();
    int LoadBrief(int index, ArcBrief * out);
    ~Archive();
    void ReadScene(Scene * scene);
    void _ResteScn();
    void SFLB_OnSave(_iobuf * fp, ArcHeader * header);
    ArcScene * GetLastScene();
    bool IsScenePast(char * cityname, char * name);
    void SaveScene(Scene * scene);
    int Delete(int index);
    int Load(int index);
    bool IsObjNotLoad(ulong id);
    void ScenePast(char * cityname, char * name);
    ArcScene * FindScene(char * cityName, char * name);
    void OnLoad(_iobuf * fp, ArcHeader * header);
    int InitGameNotFirst(_iobuf * fp);
    void Init();
    Archive();
    void AddObjNotLoad(ulong id);
    SceneInfo * GetLastSaveScene();
    ObjectInfo * FindObj(char * cityName, char * name, int ID);
    SaveTask * FindObjSavedTask(char * cityName, char * name, int ID);
    int Save(int index);
};

int PrepareDir();
int IfDir(char * pFileName);

#endif // PAL3A_ARCHIVE_H
