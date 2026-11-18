#pragma once
// [重建 2026-11-18] gbengine内部类——注解known_members真值渲染
// (语料引用 pMatBuf×83/MaxVol×15/CurPos×3/ValidFlag 12 断链实证)
#include "gbengine/gbengine_types.h"

class gbMatrix4;
class gbQuaternion;

class gbMatrixStack {  // 内部类非导出(GBAPI会在fwd声明链上引发C2011)
public:
    gbMatrix4* pMatBuf;    // +0x0
    int MaxVol;            // +0x4
    int CurPos;            // +0x8
    int ValidFlag;         // +0xC
    // total size: 0x10 (16)

    // [导入引擎类方法 2026-11-18] 方法体在引擎DLL(vtable项=0xffffffff=import
    // thunk实证), PAL3.exe仅声明调用; sig_model真值见structs/gbMatrixStack.json
    void Rotate(float angle, gbVec3D *axis);              // 0x0056a244
    void Translate(gbVec3D *v);                           // 0x0056a260
    void MultMatrix(gbMatrix4 *m);                        // 0x0056a2a0
    void Rotate(gbQuaternion *q);                         // 0x0056a33c 重载
    void Translate(float x, float y, float z);            // 0x0056a370 重载
    gbMatrix4* GetTop();                                  // 0x0056a570
    void Push();                                          // 0x0056a578
    void LoadIdentity();                                  // 0x0056a57c
    void Pop();                                           // 0x0056a588
    void LoadMatrix(gbMatrix4 *m);                        // 0x0056a5c0
};
