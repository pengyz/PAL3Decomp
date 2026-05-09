#pragma once

#include "gbengine/gbengine_export.h"

class gbGfxManager;
class gbActor;

class GBAPI gbActorMgr {
public:
    gbActorMgr(gbGfxManager *);
    gbActorMgr(const gbActorMgr &);
    ~gbActorMgr();
    gbActorMgr &operator=(const gbActorMgr &);
    void DestroyActor(gbActor *);
    gbActor *LoadActorFile(char *);
};
