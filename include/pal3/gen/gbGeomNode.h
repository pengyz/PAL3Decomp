#pragma once
// Auto-generated from IDA decomp - gbGeomNode
// 9 methods

class gbGeomNode {
public:
    void EnableShadow(int a2);  // 0x00542072
    int GetAABBox(struct gbAABBox *a2);  // 0x00542078
    void GetBoundSphere(struct gbSphere *a2);  // 0x0054207E
    void Reset(float a2);  // 0x00542084
    void Update();  // 0x0054208A
    int Attach(struct gbRenderEffect *a2);  // 0x00542090
    void AttachSelf(struct gbRenderEffect *a2);  // 0x00542096
    void RenderShadowVolume(struct gbRenderInfoObj *a2);  // 0x0054209C
    void Render(struct gbRenderInfoObj *a2);  // 0x005420A2
};
