#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/AStarPathFinder.h"

// 0x00401000
AStarPathFinder::AStarPathFinder()
{
  this->Stack = (AStarPathFinder::STACK *)calloc(1u, 8u);
  this->OPEN = 0;
  this->CLOSED = 0;
  this->PATH = 0;
}

// 0x00401030
void * AStarPathFinder::_AStarPathFinder(char a2)
{

  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00401050
void AStarPathFinder::ReleaseAll()
{

  free(this->Stack);
}

// 0x004012A0
int AStarPathFinder::TryExpand(
        
        AStarPathFinder::NODE *pNode,
        int nTileX,
        int nTileY,
        int nGoalX,
        int nGoalY)
{
  int result; // eax
  AStarPathFinder::NODE *v8; // ecx
  AStarPathFinder::NODE **stack; // edx
  double v10; // st7
  AStarPathFinder::NODE *v11; // ecx
  AStarPathFinder::NODE **v12; // edx
  double v13; // st7
  AStarPathFinder::NODE *v14; // esi
  long double v15; // st7
  int v16; // ecx
  AStarPathFinder::NODE **v17; // eax
  float v18; // [esp+0x20] [ebp-0x8]
  float v19; // [esp+0x20] [ebp-0x8]
  int v20; // [esp+0x24] [ebp-0x4]

  result = this->IsInBounds(nTileX, nTileY);
  if ( result )
  {
    v20 = 0;
    this->GetHeuristicIdx(nTileX, nTileY);
    v18 = (float)((pNode->x - nTileX) * (pNode->x - nTileX) + (pNode->y - nTileY) * (pNode->y - nTileY));
    v19 = sqrt(v18)
        * g_fHeuristicScale[this->GetHeuristicIdx(nTileX,
                              nTileY)]
        + pNode->g;
    v8 = (AStarPathFinder::NODE *)this->FindInOpen(nTileX + (nTileY << 9));
    if ( v8 )
    {
      stack = pNode->stack;
      do
      {
        if ( !*stack )
          break;
        ++stack;
        ++v20;
      }
      while ( v20 < 8 );
      pNode->stack[v20] = v8;
      if ( v19 < (double)v8->g )
      {
        v10 = v19 + v8->h;
        v8->parent = pNode;
        v8->g = v19;
        v8->f = v10;
        return 1;
      }
    }
    else
    {
      v11 = (AStarPathFinder::NODE *)this->FindInClosed(nTileX + (nTileY << 9));
      if ( v11 )
      {
        v12 = pNode->stack;
        do
        {
          if ( !*v12 )
            break;
          ++v12;
          ++v20;
        }
        while ( v20 < 8 );
        pNode->stack[v20] = v11;
        if ( v19 < (double)v11->g )
        {
          v13 = v19 + v11->h;
          v11->parent = pNode;
          v11->g = v19;
          v11->f = v13;
          this->UpdateNeighbors(v11);
          return 1;
        }
      }
      else
      {
        v14 = (AStarPathFinder::NODE *)calloc(1u, 0x40u);
        v14->parent = pNode;
        v14->g = v19;
        v15 = sqrt((double)((nTileX - nGoalX) * (nTileX - nGoalX) + (nTileY - nGoalY) * (nTileY - nGoalY)))
            * g_fHeuristicScale[this->GetHeuristicIdx(nGoalX,
                                  nGoalY)];
        v14->h = v15;
        v14->x = nTileX;
        v14->y = nTileY;
        v14->key = nTileX + (nTileY << 9);
        v14->f = v15 + v19;
        this->PushOpen(v14);
        v16 = 0;
        v17 = pNode->stack;
        do
        {
          if ( !*v17 )
            break;
          ++v16;
          ++v17;
        }
        while ( v16 < 8 );
        pNode->stack[v16] = v14;
      }
    }
    return 1;
  }
  return result;
}

// 0x004014E0
int AStarPathFinder::IsInBounds(int nX, int nY)
{
  return 0;
}

// 0x004014F0
unsigned __int8 AStarPathFinder::GetHeuristicIdx(int nX, int nY)
{
  return 0;
}

// 0x00401500
int AStarPathFinder::FindInOpen(int nTileIdx)
{
  AStarPathFinder::NODE *OPEN; // ecx
  AStarPathFinder::NODE *i; // eax

  OPEN = this->OPEN;
  for ( i = OPEN->next; i; i = i->next )
  {
    if ( i->key == nTileIdx )
      break;
    OPEN = i;
  }
  return (int)OPEN->next;
}

// 0x00401530
int AStarPathFinder::FindInClosed(int nTileIdx)
{
  AStarPathFinder::NODE *CLOSED; // ecx
  AStarPathFinder::NODE *i; // eax

  CLOSED = this->CLOSED;
  for ( i = CLOSED->next; i; i = i->next )
  {
    if ( i->key == nTileIdx )
      break;
    CLOSED = i;
  }
  return (int)CLOSED->next;
}

// 0x00401560
int AStarPathFinder::PushOpen(AStarPathFinder::NODE *pNode)
{
  AStarPathFinder::NODE *OPEN; // edx
  AStarPathFinder::NODE *i; // ecx
  int result; // eax

  OPEN = this->OPEN;
  for ( i = OPEN->next; i; i = i->next )
  {
    if ( i->f >= (double)pNode->f )
      break;
    OPEN = i;
  }
  result = (int)OPEN->next;
  pNode->next = (AStarPathFinder::NODE *)result;
  OPEN->next = pNode;
  return result;
}

// 0x00401590
int AStarPathFinder::Release(AStarPathFinder::NODE *pNode)
{
  int result; // eax
  int v3; // esi

  result = (int)pNode;
  if ( pNode )
  {
    do
    {
      v3 = *(_DWORD *)(result + 60);
      free((void *)result);
      result = v3;
    }
    while ( v3 );
  }
  return result;
}

// 0x004015B0
int AStarPathFinder::UpdateNeighbors(AStarPathFinder::NODE *pNode)
{
  AStarPathFinder::NODE *v2; // ebp
  AStarPathFinder::NODE *v4; // esi
  int v5; // eax
  long double v6; // st7
  long double v7; // st7
  bool v8; // cc
  int result; // eax
  AStarPathFinder::NODE *v10; // edi
  float f; // esi
  int v12; // ebp
  long double v13; // st7
  long double v14; // st7
  int v15; // [esp+0x10] [ebp-0x10]
  int v16; // [esp+0x10] [ebp-0x10]
  AStarPathFinder::NODE **stack; // [esp+0x14] [ebp-0xC]
  float v18; // [esp+0x18] [ebp-0x8]
  float g; // [esp+0x1C] [ebp-0x4]
  float v20; // [esp+0x1C] [ebp-0x4]
  AStarPathFinder::NODE *pNodea; // [esp+0x24] [ebp+0x4]

  v2 = pNode;
  g = pNode->g;
  v15 = 0;
  stack = pNode->stack;
  do
  {
    v4 = *stack;
    if ( !*stack )
      break;
    v5 = v2->y - v4->y;
    v18 = (float)(v5 * v5 + (v2->x - v4->x) * (v2->x - v4->x));
    v6 = sqrt(v18)
       * g_fHeuristicScale[this->GetHeuristicIdx(v4->x,
                             v4->y)]
       + g;
    if ( v6 >= v4->g )
    {
      v2 = pNode;
    }
    else
    {
      v4->g = v6;
      v7 = v6 + v4->h;
      v2 = pNode;
      v4->parent = pNode;
      v4->f = v7;

    }
    v8 = ++v15 < 8;
    ++stack;
  }
  while ( v8 );
  for ( result = (int)this->Stack->top; result; result = (int)this->Stack->top )
  {
    v10 = this->PopStack();
    v16 = 0;
    pNodea = (AStarPathFinder::NODE *)v10->stack;
    do
    {
      f = pNodea->f;
      if ( !LODWORD(pNodea->f) )
        break;
      v12 = v10->x - *(_DWORD *)(LODWORD(f) + 12);
      v20 = (float)((v10->y - *(_DWORD *)(LODWORD(f) + 16)) * (v10->y - *(_DWORD *)(LODWORD(f) + 16)) + v12 * v12);
      v13 = sqrt(v20)
          * g_fHeuristicScale[this->GetHeuristicIdx(*(_DWORD *)(LODWORD(f) + 12),
                                *(_DWORD *)(LODWORD(f) + 16))]
          + v10->g;
      if ( v13 < *(float *)(LODWORD(f) + 8) )
      {
        *(float *)(LODWORD(f) + 8) = v13;
        v14 = v13 + *(float *)(LODWORD(f) + 4);
        *(_DWORD *)(LODWORD(f) + 24) = v10;
        *(float *)LODWORD(f) = v14;

      }
      v8 = ++v16 < 8;
      pNodea = (AStarPathFinder::NODE *)((char *)pNodea + 4);
    }
    while ( v8 );
  }
  return result;
}

// 0x00401750
int AStarPathFinder::ResortNode()
{
  int result; // eax
  int v3; // [esp+0x8] [ebp+0x4]

  result = (int)calloc(1u, 8u);
  *(_DWORD *)result = v3;
  *(_DWORD *)(result + 4) = this->Stack->top;
  this->Stack->top = (AStarPathFinder::NODE *)result;
  return result;
}

// 0x00401780
AStarPathFinder::NODE * AStarPathFinder::PopStack()
{
  AStarPathFinder::STACK *Stack; // ecx
  AStarPathFinder::NODE *v2; // esi
  AStarPathFinder::NODE **top; // [esp-0x4] [ebp-0x8]

  Stack = this->Stack;
  top = (AStarPathFinder::NODE **)Stack->top;
  v2 = *top;
  Stack->top = top[1];
  free(top);
  return v2;
}

// 0x004017A0
int AStarPathFinder::Reset()
{
  this->Release(this->OPEN);
  this->Release(this->CLOSED);
  this->OPEN = 0;
  this->CLOSED = 0;
  this->PATH = 0;
  return 0;
}
