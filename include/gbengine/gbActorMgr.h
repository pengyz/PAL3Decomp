#pragma once

#ifndef GBAPI
#ifdef GBENGINE_EXPORTS
#define GBAPI __declspec(dllexport)
#else
#define GBAPI __declspec(dllimport)
#endif
#endif

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
