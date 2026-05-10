#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageScene.h"

// 0x0050FE50
int CCBStageScene::Update()
{
  this->m_EnemyFiveLineupQuad.eu = 0.0;
  this->m_EnemyFiveLineupQuad.ev = 0.0;
  this->m_EnemyFiveLineupQuad.color.ColorQuadFmt = 0;
  BYTE1(this->m_EnemyFiveLineupQuad.color.Blue) = 1;
  BYTE2(this->m_EnemyFiveLineupQuad.color.Blue) = 1;
  HIBYTE(this->m_EnemyFiveLineupQuad.color.Blue) = 1;
  this->m_EnemyFiveLineupQuad.color.Red = 0;
  LOBYTE(this->m_EnemyFiveLineupQuad.color.Blue) = 0;
  LOBYTE(this->m_EnemyFiveLineupQuad.color.Green) = 0;
  this->m_FiveLineupQuad.vec[1].y = 0.0;
  this->m_FiveLineupQuad.vec[1].z = 0.0;
  this->m_FiveLineupQuad.vec[2].x = 1.0;
  this->m_FiveLineupQuad.vec[2].y = 1.0;
  this->m_FiveLineupCenterQuad.color.ColorQuadFmt = 0;
  this->m_FiveLineupCenterQuad.color.Blue = 0;
  this->m_FiveLineupCenterQuad.color.Green = 1065353216;
  this->m_FiveLineupCenterQuad.color.Red = 1065353216;
  this->m_FiveLineupQuad.color.Color = 0;
  this->m_FiveLineupCenterQuad.vec[0].x = 0.0;
  this->m_FiveLineupCenterQuad.vec[0].y = 1.0;
  this->m_FiveLineupCenterQuad.vec[0].z = 1.0;
  return 0;
}
