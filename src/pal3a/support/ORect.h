#ifndef PAL3A_ORECT_H
#define PAL3A_ORECT_H

#include "pal3a_types.h"

class ORect {
public:
    POINT m_pt[4];
    int m_numpt;

    ORect();
    ~ORect();
    bool IsOK();
    void Clear();
    void AddPoint(int x, int y);
    void GetRangeX(int *minx, int *maxx);
    bool GetRangeY(int x, tagRECT *cliprect, int *miny, int *maxy);
    bool LineSeg(int x, tagPOINT *pt1, tagPOINT *pt2, int *y);
};

#endif // PAL3A_ORECT_H
