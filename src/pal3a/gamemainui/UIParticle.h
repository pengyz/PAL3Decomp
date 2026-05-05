#ifndef PAL3A_UIPARTICLE_H
#define PAL3A_UIPARTICLE_H

#include "pal3a_types.h"

class UIPar_Meteor {
public:
    char _data[276];

    void Render();
    int Update(float deltatime, int haveinput);
    void Create(uint id, tagRECT rect, UIWnd * pwnd, uchar bCalFrameRate);
    ~UIPar_Meteor();
    UIPar_Meteor();
};

class UIPar_Star {
public:
    char _data[124];

    int Update(float deltatime, int haveinput);
    void Create(uint id, tagPOINT pt, UIWnd * pWnd, int ntex, uchar bCalFrameRate);
    void Render();
    ~UIPar_Star();
    UIPar_Star();
    void ResetStar();
};

class UIParticle {
public:
    char _data[592];

    void Set_Direction(float dir_x, float dir_y);
    void UIPar_eidolon(tagRECT _rect);
    void Set_Active(uchar isReady);
    bool Get_Active();
    void UIPar_surround_ccw(tagRECT _rect);
    void UIPar_helixdoublediffuse(tagRECT _rect);
    void Set_Size(int par_sizeX, int par_sizeY);
    void UIPar_surround_cw(tagRECT _rect);
    void Set_FPS(int fps);
    ~UIParticle();
    void Set_Position(float pos_x, float pos_y);
    void UIPar_rainbowbounce(tagRECT _rect);
    void UIPar_disperse(tagRECT _rect);
    void Set_Fade(float par_Fade);
    void Set_AreaSize(tagRECT rect);
    void Set_AreaSize(int w, int h);
    float Get_Speed();
    void Set_Speed(float speed);
    void UIPar_risehelix(tagRECT _rect);
    void Set_Alpha(int col_a);
    void UIPar_rainbow(tagRECT _rect);
    void UIPar_falling(tagRECT _rect);
    void UIPar_helix(tagRECT _rect);
    void UIPar_bomb(tagRECT _rect);
    void Set_Gravity(float gra_x, float gra_y);
    void Set_Texture(char * texName);
    UIParticle();
    void Set_Color(int col_r, int col_g, int col_b);
    void Render(UIPar_Type m_Type);
    void UIPar_rise(tagRECT _rect);
    void UIPar_helixsinglediffuse(tagRECT _rect);
};

#endif // PAL3A_UIPARTICLE_H
