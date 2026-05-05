#ifndef PAL3A_PARTICLEEFFECT_H
#define PAL3A_PARTICLEEFFECT_H

#include "pal3a_types.h"

class ParticleEffect {
public:
    char _data[362860];

    bool LoadFromFile(char * sFullName);
    bool LoadFromFile(char * dir, char * filename);
    void SetSpaceScale(float scale);
    int Render();
    void SetLoopEmit(int loop);
    ParticleEffect();
    ~ParticleEffect();
    void Update(float deltatime, gbVec3D _offset);
    void Update(float _deltatime);
};

#endif // PAL3A_PARTICLEEFFECT_H
