#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Role.h"

// 0x00408D10
int Role::CreateXueJian(int a1, int a2)
{
  int result; // eax

  result = 0;
  switch ( a1 )
  {
    case 0:
      result = 8 * a2 + 80;
      break;
    case 1:
      result = 7 * a2 + 75;
      break;
    case 2:
      result = 9 * a2 + 80;
      break;
    case 3:
      result = 7 * a2 + 60;
      break;
    case 4:
      result = 9 * a2 + 100;
      break;
    default:
      return result;
  }
  return result;
}

// 0x00408D80
int Role::CreateLongKui(int a1, int a2)
{
  double v2; // st7
  long double v3; // st7
  float v5; // [esp+0h] [ebp-4h]
  float a2a; // [esp+10h] [ebp+Ch]

  v2 = (double)a2;
  a2a = 0.0;
  v5 = v2;
  switch ( a1 )
  {
    case 0:
      v3 = sqrt(v5) * 9.0 + 8.0;
      goto LABEL_7;
    case 1:
      v3 = sqrt(v5) * 9.0 + 6.0;
      goto LABEL_7;
    case 2:
      v3 = sqrt(v5) * 9.0 + 7.0;
      goto LABEL_7;
    case 3:
      v3 = sqrt(v5) * 9.0 + 5.0;
      goto LABEL_7;
    case 4:
      v3 = (sqrt(v5) + 1.0) * 9.0;
LABEL_7:
      a2a = v3;
      break;
    default:
      return (int)a2a;
  }
  return (int)a2a;
}

// 0x00408E30
int Role::CreateZiXuan(int a1, int a2)
{
  int result; // eax

  result = 0;
  switch ( a1 )
  {
    case 0:
      result = 4 * a2 + 25;
      break;
    case 1:
      result = 5 * a2 + 25;
      break;
    case 2:
      result = 4 * a2 + 22;
      break;
    case 3:
      result = 2 * (3 * a2 + 15);
      break;
    case 4:
      result = 4 * a2 + 20;
      break;
    default:
      return result;
  }
  return result;
}

// 0x00408E90
int Role::CreateChangQing(int a1, int a2)
{
  double v2; // st7
  float v4; // [esp+0h] [ebp-4h]
  float a2a; // [esp+10h] [ebp+Ch]

  v4 = 0.0;
  a2a = (float)a2;
  switch ( a1 )
  {
    case 0:
      v2 = a2a * 4.5 + 26.0;
      goto LABEL_7;
    case 1:
      v2 = a2a * 4.0 + 24.0;
      goto LABEL_7;
    case 2:
      v2 = a2a * 4.5 + 20.0;
      goto LABEL_7;
    case 3:
      v2 = a2a * 4.0 + 22.0;
      goto LABEL_7;
    case 4:
      v2 = a2a * 5.0 + 35.0;
LABEL_7:
      v4 = v2;
      break;
    default:
      return (int)v4;
  }
  return (int)v4;
}

// 0x00408F30
int Role::CreateHuaYing(int a1, int a2)
{
  double v2; // st7
  float v4; // [esp+0h] [ebp-4h]
  float a2a; // [esp+10h] [ebp+Ch]

  v4 = 0.0;
  a2a = (float)a2;
  switch ( a1 )
  {
    case 0:
      v2 = a2a * 3.3 + 17.0;
      goto LABEL_7;
    case 1:
      v2 = a2a * 3.0 + 13.0;
      goto LABEL_7;
    case 2:
      v2 = a2a * 3.5 + 16.0;
      goto LABEL_7;
    case 3:
      v2 = a2a * 3.0 + 16.0;
      goto LABEL_7;
    case 4:
      v2 = a2a * 3.0 + 18.0;
LABEL_7:
      v4 = v2;
      break;
    default:
      return (int)v4;
  }
  return (int)v4;
}
