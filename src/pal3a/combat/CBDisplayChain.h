#ifndef PAL3A_CBDISPLAYCHAIN_H
#define PAL3A_CBDISPLAYCHAIN_H

#include "pal3a_types.h"

class CCBDisplayChain {
public:
    char _data[17944];

    void Reset();
    bool Destroy();
    void ShowRoleState(int nX, int nY, int nNum, ulong dwColor);
    ~CCBDisplayChain();
    void Update();
    void ShowEnemyFiveLineup(uchar byAlpha);
    void ShowTxt(char * pStr, int nX, int nY, ulong dwColor);
    void ShowTxt(char * pStr, float fX, float fY, float fSize);
    void ShowTxt(char * pStr, float fX, float fY, tagRGBQUAD color);
    bool Init();
    bool Create();
    void ShowCombatDialog(char * pStr, float fX, float fY, tagRGBQUAD color, float fSize);
    void DrawScreenQuad();
    void PrintTxt(int nX, int nY, char * pFormatStr);
    void PrintTxt(char * pStr, int nX, int nY);
    CCBDisplayChain(CCBStage * pStage);
    void RenderLineup();
    void SetScreenQuad(float fAlpha, ulong dwColor);
    void Render();
    void ShowFiveLineup(float fX, float fY, float fZ, float fRadius, uchar byAlpha);
};

#endif // PAL3A_CBDISPLAYCHAIN_H
