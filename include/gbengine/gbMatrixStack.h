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

    // [导入引擎类方法 2026-11-18] 方法体在引擎DLL(IAT槽=GBENGINE.DLL导入 thunk),
    // PAL3.exe仅声明调用; 签名权威=PAL3.exe导入表mangle(20261120 AAU=引用修正)
    // + structs/gbMatrixStack.json
    void Rotate(float angle, gbVec3D &axis);              // 0x0056a244 mangle QAEXMAAUgbVec3D: AAU=引用
    void Translate(gbVec3D &v);                           // 0x0056a260 mangle QAEXAAUgbVec3D: AAU=引用
    void MultMatrix(gbMatrix4 *m);                        // 0x0056a2a0
    void Rotate(gbQuaternion &q);                         // 0x0056a33c 重载 mangle QAEXAAUgbQuaternion: AAU=引用
    void Translate(float x, float y, float z);            // 0x0056a370 重载
    gbMatrix4* GetTop();                                  // 0x0056a570
    void Push();                                          // 0x0056a578
    void LoadIdentity();                                  // 0x0056a57c
    void Pop();                                           // 0x0056a588
    void LoadMatrix(gbMatrix4 *m);                        // 0x0056a5c0
    // [Scale 补 20261120] 导出表 ?Scale@gbMatrixStack@@QAEXAAUgbVec3D@@@Z + QAEXMMM
    // (双重载; 语料限定调用 UIBigMap::RenderRole/UIProgressBar::Render/RoleSystem::RenderRole
    // /CCBPanelSlot::Render/sub_442E90 五处实证)——头族重建时漏, N13c 预测兑现案
    void Scale(gbVec3D &v);                               // AAUgbVec3D 重载(mangle真值=引用; 指针形系旧注解牵连)
    void Scale(float x, float y, float z);                // MMM 重载
};
