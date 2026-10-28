"""共享逻辑表（收敛双副本）· 阶段 3。

## 背景

_GB_REF_PARAM_FUNCS 在 stage3_cleanup.py / stage5_fixup.py 双副本
（stage3 26 键 · stage5 30 键 · 仅 stage5 多 4 键）

## 收敛

单一定义，双侧引用。
"""
_GB_REF_PARAM_FUNCS = {
    'Translate': {0},
    'Scale': {0},
    'LeftTranslate': {0},
    'RightTranslate': {0},
    'MakeMatrix': {0, 1, 2},
    'IntersectPlane': {0, 1},
    'IsColAABB': {0},
    'IsColOBB_H': {0},
    # 【B 修同款（方案复核）】PAU 指针形出表/AAU 引用形留表——限定键+元数感知
    'gbMatrixStack::Rotate': {2: {1}, 1: {0}},
    'gbRay::IsColOBB': {0}, 'gbPlane::IsColOBB': {0},
    'IsColPoint': {0},
    'IsColQuad': {0, 1, 2},
    'IsColSphere': {0},
    'IsColTriangle': {0, 1, 2, 3},
    'gbOBBox::GetAABBox': {0},
    # [T2' 首键 2026-10-28] mangled A 级：PAUgbVec3D@@AAM1 = ptr,ref,ref ⇒ {1,2}
    # （单载可证：gbengine.def 恰 1 条 + gbCamera.h 唯一 decl）
    'gbCamera::PointWorldToScr': {1, 2},  # [C8·B 修补条 2026-10-14 落表] 跨类形参形态相反：gbOBBox=AAU 引用形留表；
    # gbVisNode/gbGeomNode=PAU 指针形出表（裸键曾误解引用实参 ⇒ ScreenEffectMgr C2664）
    'GetSphere': {0},
    'GetCollideOBB': {0},
    'SetPosition': {0},
    # [挂账3 修 2/3 2026-10-16] GetPosition 裸键删除（限定化无目标——已知全形无 ref）：mangled A 级：?GetPosition@PathObj@@QAEPAHMPAMPAH@Z(float,float*,int*)=指针形 · ?GetPosition@RoleSystem(float*,int)=指针形 · ?GetPosition@UIProgressBar@@QAEXH@Z(int)=值形 · ?GetPosition@Object3D@@QAE?AUgbVec3D@@XZ=无参 —— 无 AAU/AAV ref 形 ⇒ 裸键剥& 会打断 RoleSystem::GetPosition(&pOut[0].x,…) 指针实参（reviewer B 组 float*/GetPosition 实症）
    'SetVelocity': {0},
    'SetOrientation': {0},
    'SetListenerPosition': {0},
    'SetListenerOrientation': {0, 1},
    'GetListenerPosition': {0},
    'PushMessage': {0},
    'PopMessage': {0},
    'GetViewport': {0},
    'GetViewSizeOnNearPlane': {0, 1},
    'GetViewPort': {0, 1, 2, 3},}
