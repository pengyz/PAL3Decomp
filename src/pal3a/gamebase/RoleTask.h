#ifndef PAL3A_ROLETASK_H
#define PAL3A_ROLETASK_H

#include "pal3a_types.h"

class RoleTaskPool {
public:
    char _data[684];

    char * GetTaskRemark(int lineid);
    bool CheckTaskFinish(int lineid);
    void InitTask();
    void LoadTask(_iobuf * fp);
    void GetTaskFromFile(char * filename);
    void AppendTask(char * taskname);
    char * GetTaskTitle(int lineid);
    void SaveTask(_iobuf * fp);
    int GetTaskType(int lineid);
    ~RoleTaskPool();
    bool HasMainTask();
    int GetTaskNum();
    void FinishTask(char * taskname);
    void SetTaskPicFolder(char * path);
    RoleTaskPool();
    char * GetTaskPic(int lineid);
};

#endif // PAL3A_ROLETASK_H
