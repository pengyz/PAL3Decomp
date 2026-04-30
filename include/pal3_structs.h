/**
 * PAL3 Decompilation - Game Structure Definitions
 *
 * All known structures reverse-engineered from the original binary.
 * Source: PAL3patch (zhangboyang)
 *
 * Important: These structures must match the original binary layout exactly.
 * Use sizeof assertions (at bottom) to verify.
 */

#ifndef PAL3_STRUCTS_H
#define PAL3_STRUCTS_H

#include "pal3_types.h"
#include "pal3_config.h"

/* ========================================================================
 * Enumerations
 * ======================================================================== */

enum GAME_STATE {
    GAME_NONE = 0,
    GAME_UI = 1,
    GAME_SCENE = 2,
    GAME_COMBAT = 3,
    GAME_SUBGAME_ENCAMPMENT = 4,
    GAME_SUBGAME_SKEE = 5,
    GAME_SUBGAME_ROWING = 6,
    GAME_SUBGAME_HIDEANDSEEK = 7,
    GAME_SUBGAME_NIGHTADVENTURE = 8,
    GAME_OVER = 9
};

enum PAL3_FRAME {
    FRM_SCENE = 0,
    FRM_FIGHT = 1,       /* unused */
    FRM_DEAL = 2,
    FRM_SMELT = 3,
    FRM_COVER = 4,
    FRM_S_STATE = 5,     /* StateUI */
    FRM_COMBAT = 6,
    FRM_HS_ENTRY = 7,    /* HockShop */
    FRM_APPRAISE = 8,
    FRM_KF = 9,
    FRM_ENCAMPMENT = 10,
    FRM_SKEE = 11,
    FRM_ROWING = 12,
    FRM_BIGMAP = 13,
    FRM_LOADING = 14,
    FRM_GAMEOVER = 15
};

enum gbPixelFmtType {
    GB_PFT_UNKNOWN = 0,
    GB_PFT_R8G8B8 = 1,
    GB_PFT_A8R8G8B8 = 2,
    GB_PFT_R5G6B5 = 3,
    GB_PFT_A1R5G5B5 = 4,
    GB_PFT_A4R4G4B4 = 5,
    GB_PFT_P8 = 6,
    GB_PFT_A8 = 7,
    GB_PFT_X8R8G8B8 = 8,
    GB_PFT_X1R5G5B5 = 9,
    GB_PFT_X4R4G4B4 = 10
};

enum gbFontType {
    GB_FONT_UNICODE12 = 0,
    GB_FONT_UNICODE16 = 1,
    GB_FONT_UNICODE20 = 2,
    GB_FONT_NUMBER = 3,
    GB_FONT_ASC = 4
};

enum VertexProcessingType {
    SOFTWARE_VP = 0,
    MIXED_VP = 1,
    HARDWARE_VP = 2,
    PURE_HARDWARE_VP = 3
};

enum ECBCombatState {
    CBCS_Null = 0,
    CBCS_Deactive = 1,
    CBCS_Running = 2,
    CBCS_Paused = 3,
    CBCS_Flee = 4,
    CBCS_Counting = 5,
    CBCS_FleeCounting = 6,
    CBCS_LoseCounting = 7,
    CBCS_CombatEnd = 8,
    CBCS_End = 9
};

enum ECBCombatResult {
    CBCR_Null = 0,
    CBCR_NoResult = 1,
    CBCR_Win = 2,
    CBCR_Lose = 3,
    CBCR_FleeOK = 4,
    CBCR_End = 5
};

enum CURSOR_TYPE {
    CURSOR_NORMAL = 0,
    CURSOR_TALK = 1,
    CURSOR_CHECK = 2,
    CURSOR_NUM = 3
};

enum ECPKMode {
    CPKM_Null = 0,
    CPKM_Normal = 1,
    CPKM_FileMapping = 2,
    CPKM_Overlapped = 3,
    CPKM_End = 4
};

/* ========================================================================
 * Math / Low-level Structures (gbEngine)
 * ======================================================================== */

enum gbAxis {
    GB_AXIS_X = 0,
    GB_AXIS_Y = 1,
    GB_AXIS_Z = 2
};

// Forward declarations
struct gbMatrix4;

struct gbVec3D {
    float x;
    float y;
    float z;

    // Constructors
    gbVec3D(void);
    gbVec3D(float x, float y, float z);

    // Operators
    void operator=(const gbVec3D &other);
    void operator+=(const gbVec3D &other);
    void operator-=(const gbVec3D &other);
    void operator*=(float s);
    void operator/=(float s);
    bool operator==(const gbVec3D &other);
    gbVec3D operator-(void) const;

    // Vector operations
    void Normalize();
    void CrossProduct(const gbVec3D *other, gbVec3D *result) const;
    void Inverse(void);
    void Zero(void);

    // Properties
    float Length(void) const;
    float LengthSquare(void) const;
    float DotProduct(const gbVec3D *other) const;
    bool IsValid() const;
    int IsNormal(void);
};

struct gbQuaternion {
    float x;
    float y;
    float z;
    float w;

    // Constructors and operators
    gbQuaternion(void);
    gbQuaternion &operator=(const gbQuaternion &other);

    // Quaternion operations
    void SetUnit(void);
    void SetAxisAngle(gbVec3D *axis, float angle);
    void GetAxisAngle(gbVec3D *axis, float *angle);
    void SetVec3D(float scalar, gbVec3D *vec);
    void GetVec3D(float *scalar, gbVec3D *vec);
    void SetMatrix(gbMatrix4 *mat);
    void GetMatrix(gbMatrix4 *out) const;
    void SetYawPitchRoll(float yaw, float pitch, float roll);
    void SetTwoVector(gbVec3D *from, gbVec3D *to);
    void Slerp(gbQuaternion *q1, gbQuaternion *q2, float t);
    void MultiplyBy(gbQuaternion *other, gbQuaternion *result);
    void Inverse(void);
    void RotateVector(gbVec3D *in, gbVec3D *out);

    // Properties
    int IsNormal(void);
    bool IsValid(void) const;
    bool IsUnit(void) const;
    float Magnitude(void);
    float Normalize(void);
};

struct gbRotMatrix {
    float m[3][3];

    // Constructor
    gbRotMatrix(void);

    // Operators
    void operator=(gbRotMatrix &other);
    void operator*=(gbRotMatrix &other);

    // Operations
    void Rotate(gbVec3D *in, gbVec3D *out);
    void LoadIdentity(void);

    // Validation
    bool IsValid(void);
    bool IsOrthonormal(void);
};

struct gbMatrix4 {
    union {
        struct {
            float xx, xy, xz, xw;
            float yx, yy, yz, yw;
            float zx, zy, zz, zw;
            float tx, ty, tz, tw;
        };
        float m[4][4];
    };

    // Constructor
    gbMatrix4(void);

    // Operators
    void operator=(const gbMatrix4 &other);
    void operator*=(const gbMatrix4 &param);
    void operator*=(const gbQuaternion &q);
    float operator()(int row, int col);

    // Matrix operations
    void LoadIdentity(void);
    void Transpose(void);
    void Transpose(gbMatrix4 *out) const;
    void Invert(void);
    void Invert(gbMatrix4 *out);

    // Multiplication
    void RightMultiply(const gbMatrix4 &param);
    void RightMultiply(const gbQuaternion &q);
    void LeftMultiply(const gbMatrix4 &param);

    // Transformation
    void Transform(const gbVec3D *in, gbVec3D *out) const;
    void Transform(gbVec3D *in, gbVec3D *out, int count) const;
    void Transform(gbVec3D *verts, int count) const;
    void Transform_W(gbVec3D *in, gbVec3D *out, int count) const;
    void Rotate(const gbVec3D *in, gbVec3D *out) const;

    // Translation
    void LeftTranslate(gbVec3D &v);
    void LeftTranslate(float x, float y, float z);
    void RightTranslate(gbVec3D &v);
    void RightTranslate(float x, float y, float z);

    // Scaling
    void LeftScale(float sx, float sy, float sz);
    void RightScale(float sx, float sy, float sz);

    // Rotation
    void SetAxisAngle(gbAxis axis, float cosA, float sinA);
    void SetAxisAngle(gbAxis axis, float angle);
    void SetAxisAngle(gbVec3D *axis, float angle);

    // Accessors
    gbVec3D *GetRow(gbVec3D *out, int row) const;
    gbVec3D *GetColumn(gbVec3D *out, int col) const;
    float *GetRow(float *out, int row) const;
    float *GetColumn(float *out, int col) const;

    // Matrix construction
    void MakeMatrix(gbVec3D &forward, gbVec3D &up, gbVec3D &pos);

    // Validation
    bool IsIdentity() const;
    bool IsValid() const;
    bool IsOrthonormal() const;
};

struct gbMatrixStack {
    struct gbMatrix4 *pStack;   /* +0x00: pointer to array of gbMatrix4 */
    int maxDepth;               /* +0x04: maximum stack depth */
    int curDepth;               /* +0x08: current stack index */
    int dirty;                  /* +0x0C: invalidation flag */

    // Constructor / Destructor
    gbMatrixStack(int depth);
    ~gbMatrixStack(void);
    gbMatrixStack &operator=(const gbMatrixStack &other);

    // Stack operations
    void Push(void);
    void Pop(void);
    void LoadIdentity(void);
    void LoadMatrix(gbMatrix4 *mat);
    void MultMatrix(gbMatrix4 *mat);

    // Transformation
    void Rotate(float angle, gbVec3D &axis);
    void Rotate(gbQuaternion &q);
    void Translate(gbVec3D &v);
    void Translate(float x, float y, float z);
    void Scale(gbVec3D &v);
    void Scale(float sx, float sy, float sz);

    // Accessor
    gbMatrix4 *GetTop(void);
};
/* sizeof = 0x10 */

struct gbColorQuad {
    union {
        int ColorQuadFmt;
        struct {
            u8 Blue;
            u8 Green;
            u8 Red;
            u8 Alpha;
        };
        u32 Color;
    };
};

/* ========================================================================
 * Graphics Structures
 * ======================================================================== */

struct gbGfxDriverInfo {
    int type;
    int subtype;
    int width;
    int height;
    int colorbits;
    int depthbits;
    int stensilbits;
    int nbackbuf;
    int fullscreen;
    int refreshrate;
    char winname[0x80];
    u32 hinst;              /* HINSTANCE */
    u32 hgfxwnd;            /* HWND */
    int newwindow;
    int waitforverticalblank;
};

struct gbViewPort {
    int x;
    int y;
    int width;
    int height;
    float minz;
    float maxz;
};

struct gbPixelFormat {
    enum gbPixelFmtType Type;
    int Bpp;
    struct gbColorQuad *Pal;
    unsigned int r_mask;
    unsigned int g_mask;
    unsigned int b_mask;
    unsigned int a_mask;
    unsigned int r_shift;
    unsigned int g_shift;
    unsigned int b_shift;
    unsigned int a_shift;
};

struct gbSurfaceDesc {
    int width;
    int height;
    enum gbPixelFmtType format;
    int pitch;
    void *pbits;
};

/* ========================================================================
 * Resource System
 * ======================================================================== */

struct gbRefObject {
    void *vfptr;            /* gbRefObjectVtbl* */
    int RefCount;
};

struct gbResManager {
    void **pBuffer;         /* gbResource** */
    int MaxNum;
    int CurNum;
};

struct gbResource {
    struct gbRefObject baseclass;
    char *pName;
    unsigned int NameCrc32;
    int IsLoaded;
    struct gbResManager *pMgr;
};

struct gbTexture {
    struct gbResource baseclass;
    int Width;
    int Height;
    void *pTexImage;        /* gbImage2D* */
    struct gbPixelFormat InFmt;
    int nLevels;
};

/* ========================================================================
 * Camera
 * ======================================================================== */

struct gbCamera {
    float fov;
    float OrthoSize;
    float Wscreen;
    float Hscreen;
    float zNear;
    float zFar;
    struct gbViewPort Viewport;
    float Plane[6][4];
    int numPlane;
    struct gbMatrix4 ViewMatrix;
    struct gbMatrix4 InvVMatrix;
    void *pControl[16];     /* gbCamControler* */
    int CurCtrl;
    void *pGfxMgr;          /* gbGfxManager* */
    struct gbVec3D eyeLoc;
    struct gbQuaternion eyeDir;
};
/* sizeof = 0x178 */

struct ObjectCamera {
    struct gbCamera *m_pCamera;
    struct gbVec3D m_camFrom;
    struct gbVec3D m_camTo;
    struct gbVec3D m_camUp;
    struct gbVec3D m_camDirect;
    float m_yaw;
    float m_pitch;
    float m_roll;
    float m_dist;
    float m_nyaw;
    float m_npitch;
    float m_nroll;
    struct gbVec3D m_forward;
    struct gbVec3D m_side;
    float m_stepRotSpeed;
    float m_stepRot;
    int m_stepRotMode;
    int m_stepRotAxis;
    char m_bStepRot;
};
/* sizeof = 0x7C */

/* ========================================================================
 * File System (CPK)
 * ======================================================================== */

struct CPKHeader {
    u32 dwLable;            /* 0x1A545352 "RST\x1A" */
    u32 dwVersion;
    u32 dwTableStart;
    u32 dwDataStart;
    u32 dwMaxFileNum;
    u32 dwFileNum;
    u32 dwIsFormatted;
    u32 dwSizeOfHeader;
    u32 dwValidTableNum;
    u32 dwMaxTableNum;
    u32 dwFragmentNum;
    u32 dwPackageSize;
    u32 dwReserved[0x14];
};

struct CPKTable {
    u32 dwCRC;
    u32 dwFlag;
    u32 dwFatherCRC;
    u32 dwStartPos;
    u32 dwPackedSize;
    u32 dwOriginSize;
    u32 dwExtraInfoSize;
};

struct CPK {
    u32 m_dwAllocGranularity;
    enum ECPKMode m_eMode;
    struct CPKHeader m_CPKHeader;
    struct CPKTable m_CPKTable[0x8000];
    void *m_pgbVFile[0x8];   /* gbVFile* */
    u8 m_bLoaded;
    u32 m_dwCPKHandle;
    u32 m_dwCPKMappingHandle;
    char m_szCPKFileName[0x104];
    int m_nOpenedFileNum;
};

struct gbVFileSystem {
    int IsInit;
    char *rtDirectory;
    void *pFileBuffer;       /* gbVFile* */
    int Type;
    void *m_pckfp;           /* FILE* */
    u32 m_itemcount;
    struct CPK m_cpk;
};

/* ========================================================================
 * UI System
 * ======================================================================== */

struct PtrArray {
    void **m_pData;
    int m_nSize;
    int m_nMaxSize;
    int m_nGrowBy;
};

struct UIWnd {
    void *vfptr;             /* UIWndVtbl* */
    struct gbColorQuad m_fontcolor;
    struct gbColorQuad m_wndcolor;
    u32 m_id;
    s32 m_rect[4];           /* RECT: left, top, right, bottom */
    struct UIWnd *m_pfather;
    struct PtrArray m_childs;
    int m_bcreateok;
    int m_bvisible;
    int m_benable;
    int m_bfocus;
};

struct UIFrameWnd {
    struct UIWnd baseclass;
    struct gbTexture *m_pbktex;
};

/* ========================================================================
 * Input System
 * ======================================================================== */

struct GRP_KEYREG {
    int Data;
    int HoldTime;
    int CountMode;
    int PressTime;
};

/* sizeof = 0x2958 */
/* Full GRPinput struct defined in community_structs.md */

/* ========================================================================
 * Audio System
 * ======================================================================== */

struct gbAudioMgrDesc {
    unsigned int frequence;
    unsigned int bits;
    unsigned int channels;
    char provider[256];
};

/* ========================================================================
 * Cursor
 * ======================================================================== */

struct UICursor {
    unsigned int m_dwID[3];
    enum CURSOR_TYPE m_active;
    struct gbTexture *m_tex[3];
    char m_bShow;
    char m_bSoftMode;
};
/* sizeof = 0x20 */

/* ========================================================================
 * Combat System (partial)
 * ======================================================================== */

struct tagCmdData {
    unsigned int dwCmdKind;
    union {
        unsigned long dwCmdID;
        unsigned long dwItemID;
    };
    int nSrcRole;
    int nDestRole;
    char bMultiSrcRole;
    char bMultiDestRole;
    char bSrcRole[11];
    char bDestRole[11];
    char bValid;
};
/* sizeof = 0x2C */

struct tagPlayerSet {
    struct tagCmdData LastRoleCmd;
    int nMagicDefaultPage;
    int nItemDefaultPage;
};
/* sizeof = 0x34 */

/* ========================================================================
 * Compile-time Structure Size Verification
 * ======================================================================== */

#ifdef PAL3_VERIFY_STRUCT_SIZES

#include <assert.h>

#define PAL3_STRUCT_SELFCHECK() do { \
    assert(sizeof(struct gbCamera) == 0x178); \
    assert(sizeof(struct ObjectCamera) == 0x7C); \
    assert(sizeof(struct UICursor) == 0x20); \
    assert(sizeof(struct tagCmdData) == 0x2C); \
    assert(sizeof(struct tagPlayerSet) == 0x34); \
} while (0)

#endif /* PAL3_VERIFY_STRUCT_SIZES */

#endif /* PAL3_STRUCTS_H */
