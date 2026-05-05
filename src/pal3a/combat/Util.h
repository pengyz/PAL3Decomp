#ifndef PAL3A_UTIL_H
#define PAL3A_UTIL_H

#include "pal3a_types.h"

class CUtil {
public:
    char _data[1];

    bool RectIntersection(tagRECT rc1, tagRECT rc2, tagRECT * rcIntersection);
    bool Create();
    ~CUtil();
    bool CreateLog();
    void WriteLog(char * format);
    CUtil(CCBSystem * pCBSystem);
    long GetFileSize(_iobuf * pFile);
    long GetFileSize(char * pFileName);
    bool Init();
    bool Destroy();
};

class ParabolaCalculator {
public:
    char _data[48];

    gbVec3D CalulateParabola(gbVec3D * __$ReturnUdt, gbVec3D _A, gbVec3D _B, float _H);
    float UpdateParabolaY(float fTime);
    gbVec3D UpdateParabola(gbVec3D * __$ReturnUdt);
};

#endif // PAL3A_UTIL_H
