// PAL3.exe ui/UIQuadManager.cpp — UIQuadManager 单例 + 资源管理
// Address range: 0x00541470-0x005415F0
// 无 PDB 对应 (PAL3 特有)

#include <stdlib.h>
#include <string.h>

// gbRefObject: gbengine.dll 导出类
// 使用最小前向声明，Release 通过 lib 链接
class gbRefObject {
public:
    void Release(void);
};

// UIQuadManager 布局从 Destroy 逆推:
// this+4 起连续 3 个 gbRefObject* (偏移 +16, +20, +24 字节)
class UIQuadManager {
public:
    char m_base[16];                // +0x00: 基类/前置数据
    gbRefObject *m_pTexture[3];     // +0x10: 3 个引用计数纹理对象

    void Destroy(void);
};

static UIQuadManager g_UIQuadManager_inst;
static unsigned char g_UIQuadManager_guard;

static void __cdecl UIQuadManager_Dtor_atexit(void) {}

extern "C" void __cdecl UIQuadManager_Ctor(UIQuadManager *pThis);

// 0x005415F0 - UIQuadManager::GetInstance (51B)
extern "C" UIQuadManager *__cdecl UIQuadManager_GetInstance(void)
{
    if ((g_UIQuadManager_guard & 1) == 0)
    {
        g_UIQuadManager_guard |= 1;
        UIQuadManager_Ctor(&g_UIQuadManager_inst);
        atexit(UIQuadManager_Dtor_atexit);
    }
    return &g_UIQuadManager_inst;
}

// 0x005415C0 - UIQuadManager::Destroy (41B)
// 释放 3 个 gbRefObject* 纹理引用
void UIQuadManager::Destroy(void)
{
    gbRefObject **pTex = m_pTexture;
    int nCount = 3;
    do
    {
        if (*pTex)
        {
            (*pTex)->Release();
            *pTex = 0;
        }
        ++pTex;
        --nCount;
    }
    while (nCount);
}

// === STUB: UIQuadManager 构造函数 (0x00541470) ===
void __cdecl UIQuadManager_Ctor(UIQuadManager *pThis)
{
    memset(pThis, 0, sizeof(UIQuadManager));
}
