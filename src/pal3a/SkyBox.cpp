#include "SkyBox.h"

void SkyBox::ActiveSkyBox(uchar bActive)
{
    /* stub */
}

void SkyBox::Destroy()
{
    /* stub */
}

SkyBox * SkyBox::Inst()
{
    /* stub */
    return NULL;
}

void SkyBox::Create(int id, gbVec3D size)
{
    /* stub */
}

SkyBox::~SkyBox()
{
    /* stub */
}

SkyBox::SkyBox()
{
    /* stub */
}

void SkyBox::Render(gbRenderInfoObj * pobj)
{
    /* stub */
}

void SkyboxEff::GetRandomRenderArea(float xOffset, float yOffset)
{
    /* stub */
}

void SkyboxEff::RenderEffect()
{
    /* stub */
}

SkyboxEff::~SkyboxEff()
{
    /* stub */
}

void SkyboxEff::GetEnumPos(float fSize, eSkyEffPos ePos, uchar bAreaRand, float * fx, float * fy, float * fz)
{
    /* stub */
}

void SkyboxEff::DestroyEffect()
{
    /* stub */
}

void SkyboxEff::CreateEffect(float fSkysize, char * name, EffModeParam effMode, float xOffset, float yOffset, float scale, float fps, float fValidtime, float fWaitTime)
{
    /* stub */
}

void SkyboxEff::UpdateEffect(float deltatime)
{
    /* stub */
}

SkyboxEff::SkyboxEff()
{
    /* stub */
}

void SkyboxEffMgr::DestroyAllEff()
{
    /* stub */
}

void SkyboxEffMgr::StopEffect(char * effName)
{
    /* stub */
}

SkyboxEffMgr::~SkyboxEffMgr()
{
    /* stub */
}

void SkyboxEffMgr::PreLoadEffect(char * name)
{
    /* stub */
}

void SkyboxEffMgr::PreLoadEffect()
{
    /* stub */
}

void SkyboxEffMgr::Update(float deltatime)
{
    /* stub */
}

void SkyboxEffMgr::RunEffect(char * effName, int nSide, float xOffset, float yOffset, float scale, float fps, float fValidTime, float fWaitTime)
{
    /* stub */
}

void SkyboxEffMgr::DestroyEffectThorough()
{
    /* stub */
}

void SkyboxEffMgr::Render()
{
    /* stub */
}

SkyboxEffMgr::SkyboxEffMgr()
{
    /* stub */
}

void SkyboxEffMgr::UnPreLoadEffect(char * name)
{
    /* stub */
}

