#include "SParticleEffect.h"

void CEmitter::UpdateTrackPos(float fElapsedTime)
{
    /* stub */
}

void CEmitter::Emit(void* pUnit)
{
    /* stub */
}

CEmitter::CEmitter()
{
    /* stub */
}

CParticleEffect::~CParticleEffect()
{
    /* stub */
}

void CParticleEffect::Update()
{
    /* stub */
}

void CParticleEffect::Setup(gbGfxManager * pGfxMgr)
{
    /* stub */
}

float CParticleEffect::GetTime()
{
    /* stub */
    return 0.0f;
}

void CParticleEffect::SetTimeScale(float fTimeScale)
{
    /* stub */
}

unsigned long CParticleEffect::GetNumOfParticles()
{
    /* stub */
    return 0;
}

void CParticleEffect::Start()
{
    /* stub */
}

void CParticleEffect::Display(int bVisible)
{
    /* stub */
}

int CParticleEffect::IsPlay()
{
    /* stub */
    return 0;
}

CParticleSystem * CParticleEffect::GetParticleSystem(ulong dwParticleIndex)
{
    /* stub */
    return NULL;
}

CParticleSystem * CParticleEffect::GetParticleSystem(char * strParticleName)
{
    /* stub */
    return NULL;
}

unsigned long CParticleEffect::GetNumOfParticleSystem()
{
    /* stub */
    return 0;
}

int CParticleEffect::Render()
{
    /* stub */
    return 0;
}

void CParticleEffect::SetTransform(gbMatrix4 * matTransform, float fWidthScale, float fHeightScale)
{
    /* stub */
}

void CParticleEffect::Stop()
{
    /* stub */
}

CParticleEffect::CParticleEffect()
{
    /* stub */
}

int CParticleEffect::Load(char * strFileName)
{
    /* stub */
    return 0;
}

CEmitter * CParticleSystem::GetEmitter()
{
    /* stub */
    return NULL;
}

unsigned long CParticleSystem::GetId()
{
    /* stub */
    return 0;
}

void CParticleSystem::Setup(gbGfxManager * pGfxMgr)
{
    /* stub */
}

void CParticleSystem::Update(float fElapsedTime)
{
    /* stub */
}

CParticleSystem::~CParticleSystem()
{
    /* stub */
}

void CParticleSystem::Start()
{
    /* stub */
}

int CParticleSystem::GetNumOfParticles()
{
    /* stub */
    return 0;
}

void CParticleSystem::UpdateOneParticle(void* pUnit, float fElapsedTime)
{
    /* stub */
}

void CParticleSystem::SetMode(int bManual)
{
    /* stub */
}

void* CParticleSystem::CreateOneParticle()
{
    /* stub */
    return NULL;
}

int CParticleSystem::LoadTexture(char * strTexFile)
{
    /* stub */
    return 0;
}

void CParticleSystem::UpdateAllUnits(float fElapsedTime)
{
    /* stub */
}

int CParticleSystem::GetMode()
{
    /* stub */
    return 0;
}

void CParticleSystem::UpdateFrameData(float fElapsedTime)
{
    /* stub */
}

void CParticleSystem::Stop()
{
    /* stub */
}

char const * CParticleSystem::GetName()
{
    /* stub */
    return NULL;
}

void CParticleSystem::SetTransform(gbMatrix4 * matTransform, float fWidthScale, float fHeightScale)
{
    /* stub */
}

gbVec3D const & CParticleSystem::GetEmitterPos()
{
    /* stub */
    static char _buf[256] = {0}; return *(gbVec3D*)_buf;
}

void CParticleSystem::UpdateEmitter(float fElapsedTime)
{
    /* stub */
}

unsigned long CParticleSystem::GetNumOfUnitFrames()
{
    /* stub */
    return 0;
}

int CParticleSystem::Emit(int nNumOfUnits)
{
    /* stub */
    return 0;
}

void CParticleSystem::SetEmitterPos(gbVec3D * vPos)
{
    /* stub */
}

void CParticleSystem::Display(int bVisible)
{
    /* stub */
}

void CParticleSystem::EmitUnits(float fElapsedTime)
{
    /* stub */
}

int CParticleSystem::Render()
{
    /* stub */
    return 0;
}

CParticleSystem::CParticleSystem(char * strParticleName, int nMaxNum, int nChunk)
{
    /* stub */
}

KeyFrame::~KeyFrame()
{
    /* stub */
}

KeyFrame::KeyFrame()
{
    /* stub */
}

