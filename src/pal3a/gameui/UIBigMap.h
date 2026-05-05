#ifndef PAL3A_UIBIGMAP_H
#define PAL3A_UIBIGMAP_H

#include "pal3a_types.h"

class UIBigMap {
public:
    char _data[10336];

    void UpdateElement(float deltatime);
    ~UIBigMap();
    void Create1024();
    void SetSpiritOnElement(int element);
    void Render();
    void SetSpiritDefault();
    void GoingTo(_BIGMAP_ELEMENT element);
    int Update(float deltatime, int haveinput);
    void Create();
    void Create800();
    void UpdateSpirit(float deltatime);
    void UpdateAlpha();
    void MoveSpiritTo(_BIGMAP_ELEMENT element);
    void MoveSpiritTo(tagPOINT pt);
    void SetElementVisible(_BIGMAP_ELEMENT element, uint visible);
    UIBigMap();
    void CheckSpiritDirect(tagPOINT pt);
    void EnableElement(uchar enable);
    void ResetMap();
    void Destroy();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
};

#endif // PAL3A_UIBIGMAP_H
