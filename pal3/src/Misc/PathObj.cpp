#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/PathObj.h"

// 0x00407DC0
int PathObj::CalcLength()
{
  int numpoint; // ecx
  float *v3; // ebp
  float *p_m_nPathLen; // esi
  double v5; // st7
  float *v6; // edi
  double v7; // st6
  double v8; // st7
  double v9; // st7
  bool v10; // sf
  bool v11; // of
  int result; // eax
  int v13; // [esp+0x4] [ebp-0x10]
  float v14; // [esp+0xC] [ebp-0x8]
  float v15; // [esp+0x10] [ebp-0x4]

  numpoint = this->numpoint;
  this->totallength = 0.0;
  v13 = 1;
  if ( numpoint > 1 )
  {
    v3 = &this->length[1];
    p_m_nPathLen = (float *)&this->m_nPathLen;
    do
    {
      v5 = *(p_m_nPathLen - 1027) - *(p_m_nPathLen - 1030);
      v6 = p_m_nPathLen - 1;
      v14 = *(p_m_nPathLen - 1026) - *(p_m_nPathLen - 1029);
      v7 = *(p_m_nPathLen - 1025) - *(p_m_nPathLen - 1028);
      *p_m_nPathLen = v14;
      v15 = v7;
      *(p_m_nPathLen - 1) = v5;
      p_m_nPathLen[1] = v15;
      v8 = ((gbVec3D *)(p_m_nPathLen - 1))->Length();
      *v3 = v8;
      v9 = 1.0 / v8;
      ++v3;
      p_m_nPathLen += 3;
      ++v13;
      *v6 = v9 * *v6;
      *(p_m_nPathLen - 3) = v9 * *(p_m_nPathLen - 3);
      *(p_m_nPathLen - 2) = v9 * *(p_m_nPathLen - 2);
      v11 = __OFSUB__(v13, this->numpoint);
      v10 = v13 - this->numpoint < 0;
      this->totallength = *(v3 - 1) + this->totallength;
    }
    while ( v10 != v11 );
  }
  this->normal = this->m_pPathDir;
  result = this->m_nPathLen;
  this->m_nCurPathLen = result;
  this->_todo_1010 = this->_todo_101C;
  this->length[0] = this->length[1];
  return result;
}

// 0x0041F120
int * PathObj::GetPosition(float pPos,   float *pfVal,   int *p_DWORD)
{
  int *result; // eax
  int numpoint; // esi
  int v6; // edx
  double v7; // st7
  float *v8; // edi
  gbVec3D *v9; // eax
  int v10; // edx
  int *v11; // eax
  double v12; // st7
  int v13; // eax
  float *v14; // eax
  double v15; // st6
  float v16; // [esp+0x0] [ebp-0xC]
  float v17; // [esp+0x8] [ebp-0x4]
  float pPosa; // [esp+0x10] [ebp+0x4]

  if ( pPos >= 0.0 )
  {
    numpoint = this->numpoint;
    v6 = 1;
    v7 = pPos;
    if ( numpoint <= 1 )
    {
LABEL_7:
      v9 = &this->points[numpoint - 1];
      *pfVal = v9->x;
      pfVal[1] = v9->y;
      pfVal[2] = v9->z;
      v10 = 3 * (this->numpoint + 341);
    }
    else
    {
      v8 = &this->length[1];
      while ( 1 )
      {
        pPosa = *v8;
        this->segmentlength = pPosa;
        if ( pPosa >= v7 )
          break;
        v7 = v7 - pPosa;
        ++v6;
        ++v8;
        if ( v6 >= numpoint )
          goto LABEL_7;
      }
      v12 = v7 / pPosa;
      v13 = 3 * v6;
      v10 = 3 * v6 + 1026;
      v14 = (float *)((char *)this + 4 * v13);
      v16 = (*v14 - *(v14 - 3)) * v12 + *(v14 - 3);
      v15 = (v14[1] - *(v14 - 2)) * v12 + *(v14 - 2);
      v17 = (v14[2] - *(v14 - 1)) * v12 + *(v14 - 1);
      *pfVal = v16;
      pfVal[2] = v17;
      pfVal[1] = v15;
    }
    v11 = (int *)((char *)this + 4 * v10);
    *p_DWORD = *v11;
    p_DWORD[1] = v11[1];
    result = (int *)v11[2];
    p_DWORD[2] = (int)result;
  }
  else
  {
    *(gbVec3D *)pfVal = this->points[0];
    *p_DWORD = (int)this->m_pPathDir;
    p_DWORD[1] = this->m_nPathLen;
    p_DWORD[2] = this->_todo_101C;
    return p_DWORD;
  }
  return result;
}
