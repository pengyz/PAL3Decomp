#pragma once
// Auto-generated: Actor

class gbActor;

class Actor {
public:
    std::vector<gbActor *,std::allocator<gbActor *> > m_actarray; // +0x0
    gbActor * m_pact; // +0x10
    char m_name[260]; // +0x14
    char m_szTexture[260]; // +0x118
    unsigned long m_dwMatMsg[11]; // +0x21C
    unsigned char m_bChangedMat; // +0x248
    char m_curact[8]; // +0x249
    // total size: 0x254 (596)

    int SetParam(int a2); // 0x00536160
    static int GetDefaultFOV_thunk(); // 0x00536220
    static int SetDefaultFOV(); // 0x00536230
    static int GetDefaultDist_thunk(); // 0x00536240
    static void SetDefaultDist(); // 0x00536250
    int ResetState(); // 0x005363A0
    int Cleanup(); // 0x005363C0
    void SetAction(int actionId); // 0x005363E0
    int InitComponents(); // 0x005364B0
    char ProcessFrame(); // 0x00536560
    BOOL HandleEvent(int a2, int a3); // 0x005368A0
    static int GetDefaultFOV2_thunk(); // 0x00536A40
    static int SetDefaultFOV2(); // 0x00536A50
    static int GetDefaultDist2_thunk(); // 0x00536A60
    static void SetDefaultDist2(); // 0x00536A70
    static int FastInit(int a1); // 0x00536A80
    int LoadAction(char *name); // 0x00536AC0
    int CompareAction(int actionIdx, int a3); // 0x00536C50
    unsigned int GetAnimDuration(int animId); // 0x00536CC0
    void EnableTransition(int a2, int a3); // 0x00536CE0
    void SetTimeScale(float scale); // 0x00536D00
    void * LoadModel(); // 0x00536D20
    int QueryState(); // 0x00536FB0
    int DispatchAction(int actionId); // 0x00536FC0
    int PlayAction(int actionId); // 0x00536FD0
    int UpdateAllActions(); // 0x00536FF0
    void SetVisible(int bVisible); // 0x005371B0
};
