#ifndef PAL3A_BILLBOARDFACE_H
#define PAL3A_BILLBOARDFACE_H

#include "pal3a_types.h"

class BillBoardFace {
public:
    char _data[92];

    ~BillBoardFace();
    void Create(int id, gbVec3D * pos);
    void Render();
    BillBoardFace();
    void Destroy();
};

#endif // PAL3A_BILLBOARDFACE_H
