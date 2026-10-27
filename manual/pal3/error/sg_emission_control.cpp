#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/sg_emission_control.h"
#include "Script/PalScriptMgr.h"
#include "Misc/sg_emitter.h"
#include "Misc/sg_particle.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4B8290(...);
int sub_4B8570(...);

// 0x004B8890
void sg_emission_control::_todo_004B8890(int a2, int a3)
{
  int v4; // ecx
  float *name; // esi
  int v6; // edi
  double v7; // st7
  double v8; // st7
  float *v9; // edx
  float v10; // eax
  float v11; // ecx
  float v12; // edx
  int v13; // ecx
  int v14; // edi
  float *v15; // edx
  float *v16; // edx
  int v17; // eax
  float *v18; // edx
  double v19; // st7
  double v20; // st6
  float *v21; // edx
  float *v22; // edx
  float *v23; // edx
  int v24; // edi
  int v25; // ecx
  float *v26; // edx
  float v27; // ecx
  double v28; // st7
  __int64 v29; // rax
  float *v30; // edx
  float *v31; // edx
  float v32; // ecx
  double v33; // st7
  bool v34; // c0
  bool v35; // c3
  int v36; // ecx
  int v37; // edi
  float *v38; // edx
  float *v39; // edx
  float *v40; // edx
  float v41; // [esp+0xC] [ebp-0x28]
  float tval; // [esp+0xC] [ebp-0x28]
  float v43; // [esp+0xC] [ebp-0x28]
  float v44; // [esp+0xC] [ebp-0x28]
  float v45; // [esp+0x10] [ebp-0x24]
  float v46; // [esp+0x10] [ebp-0x24]
  float v47; // [esp+0x10] [ebp-0x24]
  float v48; // [esp+0x14] [ebp-0x20]
  float v49; // [esp+0x14] [ebp-0x20]
  float v50; // [esp+0x14] [ebp-0x20]
  float v51; // [esp+0x14] [ebp-0x20]
  float v52; // [esp+0x18] [ebp-0x1C]
  float v53; // [esp+0x1C] [ebp-0x18]
  float v54; // [esp+0x1C] [ebp-0x18]
  float v55; // [esp+0x1C] [ebp-0x18]
  float v56; // [esp+0x20] [ebp-0x14]
  float v57; // [esp+0x20] [ebp-0x14]
  float v58; // [esp+0x20] [ebp-0x14]
  float v59; // [esp+0x28] [ebp-0xC]

  v4 = 0;
  name = (float *)this->pemitter->name;
  v6 = 100;
  v7 = name[39] - name[40];
  this->cyclelength = v7;
  v8 = this->total_elatime / v7;
  this->emitter.tval = v8;
  v41 = v8;
  if ( name[611] > (double)v41 )
    v6 = 50;
  else
    v4 = 50;
  if ( name[3 * v4 + 461 + 3 * ((v6 - v4) / 2)] > (double)v41 )
    v6 = v4 + (v6 - v4) / 2;
  else
    v4 += (v6 - v4) / 2;
  if ( name[3 * v4 + 461 + 3 * ((v6 - v4) / 2)] > (double)v41 )
    v6 = v4 + (v6 - v4) / 2;
  else
    v4 += (v6 - v4) / 2;
  if ( name[3 * v4 + 461 + 3 * ((v6 - v4) / 2)] > (double)v41 )
    v6 = v4 + (v6 - v4) / 2;
  else
    v4 += (v6 - v4) / 2;
  if ( name[3 * v4 + 461 + 3 * ((v6 - v4) / 2)] > (double)v41 )
    v6 = v4 + (v6 - v4) / 2;
  else
    v4 += (v6 - v4) / 2;
  if ( v4 >= v6 )
  {
LABEL_21:
    v10 = 0.0f;
    v11 = 0.0f;
    v12 = 0.0f;
  }
  else
  {
    v9 = (float *)&name[3 * v4 + 464];
    while ( *(v9 - 3) > (double)v41 || *v9 < (double)v41 )
    {
      ++v4;
      v9 += 3;
      if ( v4 >= v6 )
        goto LABEL_21;
    }
    v15 = (float *)&name[3 * v4 + 462];
    v45 = (v41 - name[3 * v4 + 461]) / (name[3 * v4 + 464] - name[3 * v4 + 461]) * (name[3 * v4 + 465] - *v15) + *v15;
    v16 = (float *)&name[3 * v4 + 765];
    v48 = (v41 - name[3 * v4 + 764]) / (name[3 * v4 + 767] - name[3 * v4 + 764]) * (name[3 * v4 + 768] - *v16) + *v16;
    v17 = 3 * v4 + 1026;
    v18 = (float *)&name[3 * v4 + 1068];
    v19 = (v41 - name[3 * v4 + 1067]) / (name[3 * v4 + 1070] - name[3 * v4 + 1067]);
    v11 = v48;
    v20 = name[v17 + 45] - *v18;
    v10 = v45;
    v52 = v19 * v20 + *v18;
    v12 = v52;
  }
  this->emitter.curdir.x = v10;
  this->emitter.curdir.y = v11;
  tval = this->emitter.tval;
  this->emitter.curdir.z = v12;
  v13 = 0;
  v14 = 100;
  if ( name[1936] > (double)tval )
    v14 = 50;
  else
    v13 = 50;
  if ( name[3 * v13 + 1786 + 3 * ((v14 - v13) / 2)] > (double)tval )
    v14 = v13 + (v14 - v13) / 2;
  else
    v13 += (v14 - v13) / 2;
  if ( name[3 * v13 + 1786 + 3 * ((v14 - v13) / 2)] > (double)tval )
    v14 = v13 + (v14 - v13) / 2;
  else
    v13 += (v14 - v13) / 2;
  if ( name[3 * v13 + 1786 + 3 * ((v14 - v13) / 2)] > (double)tval )
    v14 = v13 + (v14 - v13) / 2;
  else
    v13 += (v14 - v13) / 2;
  if ( name[3 * v13 + 1786 + 3 * ((v14 - v13) / 2)] > (double)tval )
    v14 = v13 + (v14 - v13) / 2;
  else
    v13 += (v14 - v13) / 2;
  if ( v13 >= v14 )
  {
LABEL_43:
    v46 = 0.0f;
    v49 = 0.0f;
  }
  else
  {
    v21 = (float *)&name[3 * v13 + 1789];
    while ( *(v21 - 3) > (double)tval || *v21 < (double)tval )
    {
      ++v13;
      v21 += 3;
      if ( v13 >= v14 )
        goto LABEL_43;
    }
    v22 = (float *)&name[3 * v13 + 1787];
    v53 = (tval - name[3 * v13 + 1786]) / (name[3 * v13 + 1789] - name[3 * v13 + 1786]) * (name[3 * v13 + 1790] - *v22)
        + *v22;
    v23 = (float *)&name[3 * v13 + 2090];
    v56 = (tval - name[3 * v13 + 2089]) / (name[3 * v13 + 2092] - name[3 * v13 + 2089]) * (name[3 * v13 + 2093] - *v23)
        + *v23;
    v46 = v53;
    v49 = v56;
  }
  if ( v46 <= (double)v49 )
  {
    this->emitter.elerandvel_min = v46;
    this->emitter.elerandvel_max = v49;
  }
  else
  {
    this->emitter.elerandvel_max = v46;
    this->emitter.elerandvel_min = v49;
  }
  v24 = 100;
  v43 = this->emitter.tval;
  v25 = 0;
  if ( name[3261] > (double)v43 )
    v24 = 50;
  else
    v25 = 50;
  if ( name[3 * v25 + 3111 + 3 * ((v24 - v25) / 2)] > (double)v43 )
    v24 = v25 + (v24 - v25) / 2;
  else
    v25 += (v24 - v25) / 2;
  if ( name[3 * v25 + 3111 + 3 * ((v24 - v25) / 2)] > (double)v43 )
    v24 = v25 + (v24 - v25) / 2;
  else
    v25 += (v24 - v25) / 2;
  if ( name[3 * v25 + 3111 + 3 * ((v24 - v25) / 2)] > (double)v43 )
    v24 = v25 + (v24 - v25) / 2;
  else
    v25 += (v24 - v25) / 2;
  if ( name[3 * v25 + 3111 + 3 * ((v24 - v25) / 2)] > (double)v43 )
    v24 = v25 + (v24 - v25) / 2;
  else
    v25 += (v24 - v25) / 2;
  if ( v25 >= v24 )
  {
LABEL_68:
    v27 = 0.0f;
    v59 = 0.0f;
  }
  else
  {
    v26 = (float *)&name[3 * v25 + 3114];
    while ( *(v26 - 3) > (double)v43 || *v26 < (double)v43 )
    {
      ++v25;
      v26 += 3;
      if ( v25 >= v24 )
        goto LABEL_68;
    }
    v30 = (float *)&name[3 * v25 + 3112];
    v54 = (v43 - name[3 * v25 + 3111]) / (name[3 * v25 + 3114] - name[3 * v25 + 3111]) * (name[3 * v25 + 3115] - *v30)
        + *v30;
    v31 = (float *)&name[3 * v25 + 3415];
    v57 = (v43 - name[3 * v25 + 3414]) / (name[3 * v25 + 3417] - name[3 * v25 + 3414]) * (name[3 * v25 + 3418] - *v31)
        + *v31;
    v27 = v57;
    v59 = v54;
  }
  v28 = name[43] * v59;
  v50 = name[43] * v27;
  if ( v28 <= v50 )
  {
    this->emitter.emissionrate_max = (__int64)v50;
  }
  else
  {
    v29 = (__int64)v28;
    v28 = v50;
    this->emitter.emissionrate_max = v29;
  }
  v32 = this->emitter.tval;
  this->emitter.emissionrate_min = (__int64)v28;
  v33 = name[4586];
  v44 = v32;
  v34 = v33 < v32;
  v35 = v33 == v32;
  v36 = 0;
  v37 = 100;
  if ( v34 || v35 )
    v36 = 50;
  else
    v37 = 50;
  if ( name[3 * v36 + 4436 + 3 * ((v37 - v36) / 2)] > (double)v44 )
    v37 = v36 + (v37 - v36) / 2;
  else
    v36 += (v37 - v36) / 2;
  if ( name[3 * v36 + 4436 + 3 * ((v37 - v36) / 2)] > (double)v44 )
    v37 = v36 + (v37 - v36) / 2;
  else
    v36 += (v37 - v36) / 2;
  if ( name[3 * v36 + 4436 + 3 * ((v37 - v36) / 2)] > (double)v44 )
    v37 = v36 + (v37 - v36) / 2;
  else
    v36 += (v37 - v36) / 2;
  if ( name[3 * v36 + 4436 + 3 * ((v37 - v36) / 2)] > (double)v44 )
    v37 = v36 + (v37 - v36) / 2;
  else
    v36 += (v37 - v36) / 2;
  if ( v36 >= v37 )
  {
LABEL_93:
    v47 = 0.0f;
    v51 = 0.0f;
  }
  else
  {
    v38 = (float *)&name[3 * v36 + 4439];
    while ( *(v38 - 3) > (double)v44 || *v38 < (double)v44 )
    {
      ++v36;
      v38 += 3;
      if ( v36 >= v37 )
        goto LABEL_93;
    }
    v39 = (float *)&name[3 * v36 + 4437];
    v55 = (v44 - name[3 * v36 + 4436]) / (name[3 * v36 + 4439] - name[3 * v36 + 4436]) * (name[3 * v36 + 4440] - *v39)
        + *v39;
    v40 = (float *)&name[3 * v36 + 4740];
    v58 = (v44 - name[3 * v36 + 4739]) / (name[3 * v36 + 4742] - name[3 * v36 + 4739]) * (name[3 * v36 + 4743] - *v40)
        + *v40;
    v47 = v55;
    v51 = v58;
  }
  if ( v47 <= (double)v51 )
  {
    this->emitter.elelifetime_min = v47;
    this->emitter.elelifetime_max = v51;
  }
  else
  {
    this->emitter.elelifetime_max = v47;
    this->emitter.elelifetime_min = v51;
  }
}

// 0x004BA800
void sg_emission_control::_todo_004BA800(int a2, int a3, int a4, int a5)
{
    unsigned long reg_EAX = 0;
    unsigned long reg_ECX = 0;
    unsigned long reg_ESI = 0;

  void *v5; // ebp
  sg_emitter *pemitter; // eax
  int emitter_shape; // ecx
  float v9; // esi
  float v10; // ebx
  float v11; // ebp
  D3DXVECTOR3 *v14; // ecx
  float v15; // ecx
  D3DXVECTOR3 *p_relative_position; // edx
  float z; // edx
  D3DXVECTOR3 *v32; // edx
  float v34; // edx
  D3DXVECTOR3 *v46; // ecx
  float v48; // ecx
  void *v55; // [esp-0xC] [ebp-0x3C]
  float v56; // [esp-0x4] [ebp-0x34]
  void *v57; // [esp-0x4] [ebp-0x34]
  float v58; // [esp+0x0] [ebp-0x30]
  void *v59; // [esp+0x4] [ebp-0x2C]
  void *pV; // [esp+0x8] [ebp-0x28]
  void *v61; // [esp+0xC] [ebp-0x24]
  int v62; // [esp+0x14] [ebp-0x1C]
  int v63; // [esp+0x14] [ebp-0x1C]
  int v64; // [esp+0x14] [ebp-0x1C]
  float v65; // [esp+0x18] [ebp-0x18] BYREF
  float v66; // [esp+0x1C] [ebp-0x14]
  float v67; // [esp+0x20] [ebp-0x10]
  float x; // [esp+0x24] [ebp-0xC]
  float y; // [esp+0x28] [ebp-0x8]
  void *pOut; // [esp+0x2C] [ebp-0x4]

  pemitter = (sg_emitter *)this->pemitter;
  emitter_shape = pemitter->emitter_shape;
  if ( emitter_shape )
  {
    if ( emitter_shape == 1 )
    {
      v62 = rand() % 201 - 100;
      __asm
      {
        fild    [esp+0x24+var_1C]
        fstp    [esp+0x24+var_18]
      }
      v63 = rand() % 201 - 100;
      __asm
      {
        fild    [esp+0x24+var_1C]
        fstp    [esp+0x24+var_14]
      }
      v64 = rand() % 201 - 100;
      // __asm { fild    [esp+0x24+var_1C] }
      // __asm { fstp    [esp+0x2C+var_10] }
      j_D3DXVec3TransformCoord_0(&v65, &v65);
      reg_ECX = (unsigned long)this->pemitter;
      __asm
      {
        fld     dword ptr [ecx+0x0B0]
        fld     st
        fmul    [esp+0x24+var_18]
        fstp    [esp+0x24+var_18]
        fld     st
        fmul    [esp+0x24+var_14]
        fstp    [esp+0x24+var_14]
        fmul    [esp+0x24+var_10]
        fstp    [esp+0x24+var_10]
      }
      if ( sub_4B8290() )
      {
        j_D3DXVec3TransformCoord(0, (void *)LODWORD(this->pemitter->sphere.hotspot), v61);
        __asm
        {
          fld     st
          fmul    [esp+0x24+var_18]
        }
        // __asm { fstp    [esp+0x24+var_C] }
        __asm
        {
          fld     st
          fmul    [esp+0x24+var_14]
        }
        reg_EAX = (unsigned long)&this->particle_array[a2].curpos;
        // __asm { fstp    [esp+0x24+var_8] }
        (this->particle_array[a2].curpos).x = x;
        // __asm { fmul    [esp+0x24+var_10] }
        (this->particle_array[a2].curpos).y = y;
        // __asm { fstp    [esp+0x24+pOut] }
        (this->particle_array[a2].curpos).z = *(float *)&pOut;
        p_relative_position = (D3DXVECTOR3 *)&this->pemitter->relative_position;
        x = p_relative_position->x;
        __asm
        {
          fld     [esp+0x1C+var_C]
          fadd    dword ptr [eax]
        }
        y = p_relative_position->y;
        z = p_relative_position->z;
        __asm { fstp    dword ptr [eax] }
        (this->particle_array[a2].curpos).x = _ET1;
        __asm
        {
          fld     [esp+0x1C+var_8]
          fadd    dword ptr [eax+4]
        }
        *(float *)&pOut = z;
        __asm { fstp    dword ptr [eax+4] }
        (this->particle_array[a2].curpos).y = _ET1;
        __asm
        {
          fld     [esp+0x1C+pOut]
          fadd    dword ptr [eax+8]
          fstp    dword ptr [eax+8]
        }
        (this->particle_array[a2].curpos).z = _ET1;
      }
      else
      {
        reg_EAX = (unsigned long)this->pemitter;
        __asm
        {
          fld     dword ptr [eax+0x7D08]
          fadd    dword ptr [eax+0x7D04]
          fstp    [esp+0x28+pV]; pV
        }
        j_D3DXVec3TransformCoord(0, pV, v61);
        __asm
        {
          fld     st
          fmul    [esp+0x24+var_18]
        }
        // __asm { fstp    [esp+0x24+var_C] }
        __asm
        {
          fld     st
          fmul    [esp+0x24+var_14]
        }
        reg_EAX = (unsigned long)&this->particle_array[a2].curpos;
        // __asm { fstp    [esp+0x24+var_8] }
        (this->particle_array[a2].curpos).x = x;
        // __asm { fmul    [esp+0x24+var_10] }
        (this->particle_array[a2].curpos).y = y;
        // __asm { fstp    [esp+0x24+pOut] }
        (this->particle_array[a2].curpos).z = *(float *)&pOut;
        v32 = (D3DXVECTOR3 *)&this->pemitter->relative_position;
        x = v32->x;
        __asm
        {
          fld     [esp+0x1C+var_C]
          fadd    dword ptr [eax]
        }
        y = v32->y;
        reg_ECX = a3;
        v34 = v32->z;
        __asm { fstp    dword ptr [eax] }
        (this->particle_array[a2].curpos).x = _ET1;
        __asm
        {
          fld     [esp+0x1C+var_8]
          fadd    dword ptr [eax+4]
        }
        *(float *)&pOut = v34;
        __asm { fstp    dword ptr [eax+4] }
        (this->particle_array[a2].curpos).y = _ET1;
        __asm
        {
          fld     [esp+0x1C+pOut]
          fadd    dword ptr [eax+8]
          fstp    dword ptr [eax+8]
        }
        (this->particle_array[a2].curpos).z = _ET1;
        __asm
        {
          fld     dword ptr [ecx]
          fadd    dword ptr [eax]
          fstp    dword ptr [eax]
        }
        (this->particle_array[a2].curpos).x = _ET1;
        __asm
        {
          fld     dword ptr [ecx+4]
          fadd    dword ptr [eax+4]
          fstp    dword ptr [eax+4]
        }
        (this->particle_array[a2].curpos).y = _ET1;
        __asm
        {
          fld     dword ptr [ecx+8]
          fadd    dword ptr [eax+8]
          fstp    dword ptr [eax+8]
        }
        (this->particle_array[a2].curpos).z = _ET1;
      }
    }
    else if ( emitter_shape == 2 )
    {
      reg_ESI = (unsigned long)&this->particle_array[a2].curpos;
      sub_4B8570(reg_ESI);
      reg_EAX = (unsigned long)this->pemitter;
      __asm
      {
        fld     dword ptr [eax+0x0B0]
        fld     st
        fmul    dword ptr [esi]
        fstp    dword ptr [esi]
      }
      (this->particle_array[a2].curpos).x = _ET1;
      __asm
      {
        fld     st
        fmul    dword ptr [esi+4]
        fstp    dword ptr [esi+4]
      }
      (this->particle_array[a2].curpos).y = _ET1;
      __asm
      {
        fmul    dword ptr [esi+8]
        fstp    dword ptr [esi+8]
      }
      (this->particle_array[a2].curpos).z = _ET1;
      v46 = (D3DXVECTOR3 *)&this->pemitter->relative_position;
      x = v46->x;
      __asm
      {
        fld     [esp+0x24+var_C]
        fadd    dword ptr [esi]
      }
      y = v46->y;
      reg_EAX = a3;
      v48 = v46->z;
      __asm { fstp    dword ptr [esi] }
      (this->particle_array[a2].curpos).x = _ET1;
      __asm
      {
        fld     [esp+0x24+var_8]
        fadd    dword ptr [esi+4]
      }
      *(float *)&pOut = v48;
      __asm { fstp    dword ptr [esi+4] }
      (this->particle_array[a2].curpos).y = _ET1;
      __asm
      {
        fld     [esp+0x24+pOut]
        fadd    dword ptr [esi+8]
        fstp    dword ptr [esi+8]
      }
      (this->particle_array[a2].curpos).z = _ET1;
      __asm
      {
        fld     dword ptr [esi]
        fadd    dword ptr [eax]
        fstp    dword ptr [esi]
      }
      (this->particle_array[a2].curpos).x = _ET1;
      __asm
      {
        fld     dword ptr [eax+4]
        fadd    dword ptr [esi+4]
        fstp    dword ptr [esi+4]
      }
      (this->particle_array[a2].curpos).y = _ET1;
      __asm
      {
        fld     dword ptr [eax+8]
        fadd    dword ptr [esi+8]
        fstp    dword ptr [esi+8]
      }
      (this->particle_array[a2].curpos).z = _ET1;
    }
  }
  else
  {
    v59 = (void *)v5;
    v58 = pemitter->square.max.x;
    v9 = pemitter->square.max.y;
    v10 = pemitter->square.max.z;
    v56 = pemitter->square.min.x;
    v11 = pemitter->square.min.y;
    pOut = (void *)LODWORD(pemitter->square.min.z);
    j_D3DXVec3TransformCoord((void *)LODWORD(v56), (void *)LODWORD(v58), v59);
    // __asm { fstp    [esp+0x34+var_18] }
    j_D3DXVec3TransformCoord((void *)LODWORD(v11), (void *)LODWORD(v9), v57);
    // __asm { fstp    [esp+0x40+var_14] }
    j_D3DXVec3TransformCoord(pOut, (void *)LODWORD(v10), v55);
    reg_ECX = (unsigned long)this->pemitter;
    __asm
    {
      fstp    [esp+0x44+var_10]
      fld     dword ptr [ecx+0x0B0]
      fld     st
      fmul    [esp+0x44+var_18]
    }
    // __asm { fstp    [esp+0x28+var_18] }
    reg_EAX = (unsigned long)&this->particle_array[a2].curpos;
    __asm
    {
      fld     st
      fmul    [esp+0x28+var_14]
    }
    (this->particle_array[a2].curpos).x = v65;
    // __asm { fstp    [esp+0x24+var_14] }
    // __asm { fmul    [esp+0x24+var_10] }
    (this->particle_array[a2].curpos).y = v66;
    // __asm { fstp    [esp+0x24+var_10] }
    (this->particle_array[a2].curpos).z = v67;
    v14 = (D3DXVECTOR3 *)&this->pemitter->relative_position;
    x = v14->x;
    __asm
    {
      fld     [esp+0x1C+var_C]
      fadd    dword ptr [eax]
    }
    y = v14->y;
    v15 = v14->z;
    __asm { fstp    dword ptr [eax] }
    (this->particle_array[a2].curpos).x = _ET1;
    __asm
    {
      fld     [esp+0x1C+var_8]
      fadd    dword ptr [eax+4]
    }
    *(float *)&pOut = v15;
    reg_ECX = a3;
    __asm { fstp    dword ptr [eax+4] }
    (this->particle_array[a2].curpos).y = _ET1;
    __asm
    {
      fld     [esp+0x1C+pOut]
      fadd    dword ptr [eax+8]
      fstp    dword ptr [eax+8]
    }
    (this->particle_array[a2].curpos).z = _ET1;
    __asm
    {
      fld     dword ptr [eax]
      fadd    dword ptr [ecx]
      fstp    dword ptr [eax]
    }
    (this->particle_array[a2].curpos).x = _ET1;
    __asm
    {
      fld     dword ptr [ecx+4]
      fadd    dword ptr [eax+4]
      fstp    dword ptr [eax+4]
    }
    (this->particle_array[a2].curpos).y = _ET1;
    __asm
    {
      fld     dword ptr [ecx+8]
      fadd    dword ptr [eax+8]
      fstp    dword ptr [eax+8]
    }
    (this->particle_array[a2].curpos).z = _ET1;
  }
}
