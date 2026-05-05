#include "EffectSystem.h"

void CEffect::Destroy()
{
    /* stub */
}

void CEffect::Reset()
{
    /* stub */
}

CEffect::~CEffect()
{
    /* stub */
}

void CEffect::Update(double gbTime)
{
    /* stub */
}

void CEffect::DestroyAllPartical()
{
    /* stub */
}

void CEffect::HandleViewMove(float x, float y)
{
    /* stub */
}

bool CEffect::SetOnePartical(int n, tagPartical * pPartical)
{
    /* stub */
    return FALSE;
}

bool CEffect::Init()
{
    /* stub */
    return FALSE;
}

void CEffect::LoadTexture(char * pFileName)
{
    /* stub */
}

void CEffect::ToNextFrame(int nParticalIndex)
{
    /* stub */
}

void CEffect::DestroyOnePartical(int n)
{
    /* stub */
}

CEffect::CEffect(CEffectSystem * pES)
{
    /* stub */
}

void CEffect::DestroyTexture()
{
    /* stub */
}

void CEffect::FillQuadByPartical(int nParticalIndex)
{
    /* stub */
}

void CEffect::Render()
{
    /* stub */
}

bool CEffect::CreateOnePartical(tagPartical * pPartical)
{
    /* stub */
    return FALSE;
}

bool CEffectBubble::CreateGroup(float fX, float fY, float fZ, float fSize, float fFramePerSec, int nNum)
{
    /* stub */
    return FALSE;
}

CEffectBubble::CEffectBubble(CEffectSystem * pES)
{
    /* stub */
}

CEffectSimple::CEffectSimple(CEffectSystem * pES)
{
    /* stub */
}

bool CEffectSimple::CreateOne(float fX, float fY, float fZ, float fSize, float fFramePerSec)
{
    /* stub */
    return FALSE;
}

bool CEffectSystem::Init()
{
    /* stub */
    return FALSE;
}

void CEffectSystem::Render()
{
    /* stub */
}

void CEffectSystem::DestroyEffect(int nIndex)
{
    /* stub */
}

void CEffectSystem::DestroyEffect(EEffect effect)
{
    /* stub */
}

void CEffectSystem::FillDefaultUVSet()
{
    /* stub */
}

CEffect * CEffectSystem::CreateEffect(EEffect effect)
{
    /* stub */
    return NULL;
}

CEffectSystem::~CEffectSystem()
{
    /* stub */
}

CEffect * CEffectSystem::GetEffect(int nIndex)
{
    /* stub */
    return NULL;
}

void CEffectSystem::Set256UV(tagUVSet * pUVSet, int nIndex, int nSizePerPic)
{
    /* stub */
}

void CEffectSystem::Destroy()
{
    /* stub */
}

int CEffectSystem::GetEffectIndex(CEffect * pEffect)
{
    /* stub */
    return 0;
}

int CEffectSystem::GetEffectIndex(EEffect effect)
{
    /* stub */
    return 0;
}

void CEffectSystem::SetVisible(EEffect effect, uchar bVisible)
{
    /* stub */
}

void CEffectSystem::DestroyAllEffect()
{
    /* stub */
}

void CEffectSystem::HandleViewMove(float x, float y)
{
    /* stub */
}

bool CEffectSystem::IsVisible(EEffect effect)
{
    /* stub */
    return FALSE;
}

void CEffectSystem::Reset()
{
    /* stub */
}

void CEffectSystem::Update(double gbTime)
{
    /* stub */
}

CEffectSystem::CEffectSystem(gbGfxManager * pDisplay)
{
    /* stub */
}

bool CEffectSystem::IsValid(EEffect effect)
{
    /* stub */
    return FALSE;
}

