#ifndef PAL3A_OBJLOCKINPUT_H
#define PAL3A_OBJLOCKINPUT_H

#include "pal3a_types.h"

class ObjLockInput {
public:
    char _data[48];

    void Update();
    bool IfHaveScript(PalScript * pScript);
    void AddAbs(PalScript * script);
    ~ObjLockInput();
    void OnLoadScene();
    ObjLockInput * Inst();
    void Add(SceneObj * obj, PalScript * script);
    ObjLockInput();
    bool IsNull();
};

#endif // PAL3A_OBJLOCKINPUT_H
