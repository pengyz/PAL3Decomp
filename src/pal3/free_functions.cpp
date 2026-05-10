#include "pal3/ida_defs.h"
#include "pal3/globals.h"

// Free functions (not belonging to any class)

// Forward declarations for unnamed functions
int ArraySort(...);
int CombatEffectUpdate(...);
int EffectUpdate(...);
int InputUpdate(...);
int NPCAnimUpdate(...);
int SceneMgrUpdate(...);
int SceneUpdate(...);
int ScriptUpdate(...);
int UINotifyUpdate(...);
int UIPostUpdate(...);
int UISceneUpdate(...);
int sub_401000(...);
int sub_4083D0(...);
int sub_40CC60(...);
int sub_40CCD0(...);
int sub_40DCD0(...);
int sub_410BD0(...);
int sub_410DF0(...);
int sub_411900(...);
int sub_4142E0(...);
int sub_416220(...);
int sub_418130(...);
int sub_419690(...);
int sub_419EF0(...);
int sub_41C190(...);
int sub_41CBC0(...);
int sub_41CEE0(...);
int sub_41D5C0(...);
int sub_41EB50(...);
int sub_420730(...);
int sub_420B40(...);
int sub_421560(...);
int sub_423600(...);
int sub_424570(...);
int sub_426EB0(...);
int sub_430180(...);
int sub_4307D0(...);
int sub_430B30(...);
int sub_431870(...);
int sub_4318A0(...);
int sub_434BD0(...);
int sub_434C40(...);
int sub_43A3E0(...);
int sub_444F60(...);
int sub_445010(...);
int sub_445720(...);
int sub_44A790(...);
int sub_44E530(...);
int sub_44E5E0(...);
int sub_44F8D0(...);
int sub_450320(...);
int sub_450390(...);
int sub_450A60(...);
int sub_450DC0(...);
int sub_451850(...);
int sub_457260(...);
int sub_457340(...);
int sub_478C00(...);
int sub_4B70B0(...);
int sub_4BE080(...);
int sub_4BE1A0(...);
int sub_4E0A60(...);
int sub_523E60(...);
int sub_527D40(...);
int sub_52B030(...);
int sub_52B2A0(...);
int sub_52EBE0(...);
int sub_52F570(...);
int sub_52FE30(...);
int sub_5303C0(...);
int sub_531260(...);
int sub_533250(...);
int sub_533F50(...);
int sub_534210(...);
int sub_534810(...);
int sub_534BA0(...);
int sub_534BF0(...);
int sub_534CF0(...);
int sub_534E60(...);
int sub_534FB0(...);
int sub_5359B0(...);
int sub_537060(...);
int sub_5375F0(...);
int sub_53C250(...);
int sub_53D100(...);
int sub_53D3F0(...);
int sub_53DB90(...);
int sub_53DC50(...);
int sub_542059(...);
int sub_553108(...);
int sub_557C4C(...);

// Unnamed globals (extern)
extern char aBadCommandOrFi[];
extern char aEnginelogTxt[];
extern char aSGameC[];
extern char aSoftwareSoftst[];
extern unsigned char byte_17B3AAC;
extern unsigned char byte_17B41E8;
extern unsigned char byte_189598E;
extern unsigned char byte_189598F;
extern unsigned char byte_56A634;
extern unsigned char byte_60B710;
extern unsigned char byte_60B72C;
extern unsigned char byte_D8B938;
extern unsigned char byte_D92784;
extern unsigned char byte_D92785;
extern unsigned char byte_DBA25C;
extern unsigned char byte_DBA830;
extern unsigned char byte_DBD8A0;
extern unsigned char byte_DE93EC;
extern int dword_17A94E0;
extern int dword_17B3EB0;
extern int dword_1895310;
extern int dword_1895348;
extern int dword_189534C;
extern int dword_1895350;
extern int dword_1895354;
extern int dword_1896D10;
extern int dword_586154;
extern int dword_58B230;
extern int dword_58B234;
extern int dword_5A3748;
extern int dword_BFE0A0;
extern int dword_BFFDB0;
extern int dword_C00028;
extern int dword_C002A0;
extern int dword_C020F8;
extern int dword_C02370;
extern int dword_C025EC;
extern int dword_C116F4;
extern int dword_C12B38;
extern int dword_C12B3C;
extern int dword_D8BBEC;
extern int dword_D8C2B0;
extern int dword_D8C2C8;
extern int dword_D8C2E8;
extern int dword_D8C308;
extern int dword_D8C31C;
extern int dword_D8C320;
extern int dword_D92788;
extern int dword_DBA0D4;
extern int dword_DBA134;
extern int dword_DBA254;
extern int dword_DBA260;
extern int dword_DBD898;
extern int dword_DC0DE8;
extern int dword_DC10FC;
extern int dword_DC1100;
extern int dword_DE6A40;
extern int dword_DE6CD8;
extern int dword_DE6F70;
extern int dword_DE7AA0;
extern int dword_DE8B40;
extern float flt_58B238;
extern float flt_58DE64;
extern float flt_5F4B9C;
extern float flt_60B720;
extern float flt_60B724;
extern float flt_60B728;
extern float flt_C116F8;
extern int nullsub_1;
extern int nullsub_103;
extern int nullsub_2;
extern int nullsub_3;
extern int nullsub_96;
extern void *off_56A6D0;
extern void *off_56AA90;
extern void *off_56B094;
extern void *off_6088D8;
extern int stru_17B3ED8;
extern int stru_BFAB60;
extern int stru_D8C328;
extern int stru_D8C348;
extern int stru_DBAF10;
extern int stru_DE7DF8;
extern int unk_17B1550;
extern int unk_1894D90;
extern int unk_C12B38;
extern int unk_C12B3C;
extern int unk_C12B40;
extern int unk_D8C338;
extern int unk_DBA258;
extern int unk_DBB364;
extern int unk_DBD894;
extern int unk_DC0DE0;
extern int unk_DE6A44;
extern int unk_DE6A48;
extern int unknown_libname_287;
extern int unknown_libname_288;
extern int unknown_libname_289;
extern int unknown_libname_290;
extern int unknown_libname_291;
extern int unknown_libname_292;
extern int unknown_libname_293;
extern int unknown_libname_294;
extern int unknown_libname_295;
extern int unknown_libname_296;
extern int unknown_libname_297;
extern int unknown_libname_298;
extern int unknown_libname_299;
extern int unknown_libname_300;
extern int unknown_libname_301;
extern int unknown_libname_302;
extern int unknown_libname_303;
extern int unknown_libname_304;
extern int unknown_libname_305;
extern int unknown_libname_306;
extern int unknown_libname_307;
extern int unknown_libname_308;
extern int unknown_libname_309;
extern int unknown_libname_310;
extern int unknown_libname_311;
extern int unknown_libname_312;
extern int unknown_libname_313;
extern int unknown_libname_314;
extern int unknown_libname_315;
extern int unknown_libname_316;
extern int unknown_libname_317;
extern int unknown_libname_318;
extern int unknown_libname_319;
extern int unknown_libname_320;
extern int unknown_libname_321;
extern int unknown_libname_322;
extern int unknown_libname_323;
extern int unknown_libname_324;
extern int unknown_libname_325;
extern int unknown_libname_326;
extern int unknown_libname_327;
extern int unknown_libname_328;
extern int unknown_libname_329;
extern int unknown_libname_330;
extern int unknown_libname_331;
extern int unknown_libname_332;
extern int unknown_libname_333;
extern int unknown_libname_334;
extern int unknown_libname_335;
extern int unknown_libname_336;
extern int unknown_libname_337;
extern int unknown_libname_338;
extern int unknown_libname_339;
extern int unknown_libname_340;
extern int unknown_libname_341;
extern int unknown_libname_342;
extern int unknown_libname_343;
extern int unknown_libname_344;
extern int unknown_libname_345;
extern int unknown_libname_346;
extern int unknown_libname_347;
extern int unknown_libname_348;
extern int unknown_libname_349;
extern int unknown_libname_350;
extern int unknown_libname_351;
extern int unknown_libname_352;
extern int unknown_libname_353;
extern int unknown_libname_354;
extern int unknown_libname_355;
extern int unknown_libname_356;
extern int unknown_libname_357;
extern int unknown_libname_358;
extern int unknown_libname_359;
extern int unknown_libname_360;
extern int unknown_libname_361;
extern int unknown_libname_362;
extern int unknown_libname_363;
extern int unknown_libname_364;
extern int unknown_libname_365;
extern int unknown_libname_366;
extern int unknown_libname_367;
extern int unknown_libname_368;
extern int unknown_libname_369;
extern int unknown_libname_370;
extern int unknown_libname_371;
extern int unknown_libname_372;
extern int unknown_libname_373;
extern int unknown_libname_374;
extern int unknown_libname_375;
extern int unknown_libname_376;
extern int unknown_libname_377;
extern int unknown_libname_378;
extern int unknown_libname_379;
extern int unknown_libname_380;
extern int unknown_libname_381;
extern int unknown_libname_382;
extern int unknown_libname_383;
extern int unknown_libname_384;
extern int unknown_libname_385;
extern int unknown_libname_386;
extern int unknown_libname_387;
extern int unknown_libname_388;
extern int unknown_libname_389;
extern int unknown_libname_390;
extern int unknown_libname_391;
extern int unknown_libname_392;
extern int unknown_libname_393;
extern int unknown_libname_394;
extern int unknown_libname_395;
extern int unknown_libname_396;
extern int unknown_libname_397;
extern int unknown_libname_398;
extern int unknown_libname_399;
extern int unknown_libname_400;
extern int unknown_libname_401;
extern int unknown_libname_402;
extern int unknown_libname_403;
extern int unknown_libname_404;
extern int unknown_libname_405;
extern int unknown_libname_406;
extern int unknown_libname_407;
extern int unknown_libname_408;
extern int unknown_libname_409;
extern int unknown_libname_410;
extern int unknown_libname_411;
extern int unknown_libname_412;
extern int unknown_libname_413;
extern int unknown_libname_414;
extern int unknown_libname_415;
extern int unknown_libname_416;
extern int unknown_libname_417;
extern int unknown_libname_418;
extern int unknown_libname_419;
extern int unknown_libname_420;
extern int unknown_libname_421;
extern int unknown_libname_422;
extern int unknown_libname_423;
extern int unknown_libname_424;
extern int unknown_libname_425;
extern int unknown_libname_426;
extern int unknown_libname_427;
extern int unknown_libname_428;
extern int unknown_libname_429;
extern int unknown_libname_430;
extern int unknown_libname_431;
extern int unknown_libname_432;
extern int unknown_libname_433;
extern int unknown_libname_434;
extern int unknown_libname_435;
extern int unknown_libname_436;
extern int unknown_libname_437;
extern int unknown_libname_438;
extern int unknown_libname_439;
extern int unknown_libname_440;
extern int unknown_libname_441;
extern int unknown_libname_442;
extern int unknown_libname_443;
extern int unknown_libname_444;
extern int unknown_libname_445;
extern int unknown_libname_446;
extern int unknown_libname_447;
extern int unknown_libname_448;
extern int unknown_libname_449;
extern int unknown_libname_450;
extern int unknown_libname_451;
extern int unknown_libname_452;
extern int unknown_libname_453;
extern int unknown_libname_454;
extern int unknown_libname_455;
extern int unknown_libname_456;
extern int unknown_libname_457;
extern int unknown_libname_458;
extern int unknown_libname_459;
extern int unknown_libname_460;
extern int unknown_libname_461;
extern int unknown_libname_462;
extern int unknown_libname_463;
extern int unknown_libname_464;
extern int unknown_libname_465;
extern int unknown_libname_466;
extern int unknown_libname_467;
extern int unknown_libname_468;
extern int unknown_libname_469;
extern int unknown_libname_470;
extern int unknown_libname_471;
extern int unknown_libname_472;
extern int unknown_libname_473;
extern int unknown_libname_474;
extern int unknown_libname_475;
extern int unknown_libname_476;
extern int unknown_libname_477;
extern int unknown_libname_478;
extern int unknown_libname_479;
extern int unknown_libname_480;
extern int unknown_libname_481;
extern int unknown_libname_482;
extern int unknown_libname_483;
extern int unknown_libname_484;
extern int unknown_libname_485;
extern int unknown_libname_486;
extern int unknown_libname_487;
extern int unknown_libname_488;
extern int unknown_libname_489;
extern int unknown_libname_490;
extern int unknown_libname_491;
extern int unknown_libname_492;
extern int unknown_libname_493;
extern int unknown_libname_494;
extern int unknown_libname_495;
extern int unknown_libname_496;
extern int unknown_libname_497;
extern int unknown_libname_498;
extern int unknown_libname_499;
extern int unknown_libname_500;
extern int unknown_libname_501;
extern int unknown_libname_502;
extern int unknown_libname_503;
extern int unknown_libname_504;
extern int unknown_libname_505;
extern int unknown_libname_506;
extern int unknown_libname_507;
extern int unknown_libname_508;
extern int unknown_libname_509;
extern int unknown_libname_510;
extern int unknown_libname_511;
extern int unknown_libname_512;
extern int unknown_libname_513;
extern int unknown_libname_514;
extern int unknown_libname_515;
extern int unknown_libname_516;
extern int unknown_libname_517;
extern int unknown_libname_518;
extern int unknown_libname_519;
extern int unknown_libname_520;
extern int unknown_libname_521;
extern int unknown_libname_522;
extern int unknown_libname_523;
extern int unknown_libname_524;
extern int unknown_libname_525;
extern int unknown_libname_526;
extern int unknown_libname_527;
extern int unknown_libname_528;
extern int unknown_libname_529;
extern int unknown_libname_530;
extern int unknown_libname_531;
extern int unknown_libname_532;
extern int unknown_libname_533;
extern int unknown_libname_534;
extern int unknown_libname_535;
extern int unknown_libname_536;
extern int unknown_libname_537;
extern int unknown_libname_538;
extern int unknown_libname_539;
extern int unknown_libname_540;
extern int unknown_libname_541;
extern int unknown_libname_542;
extern int unknown_libname_543;
extern int unknown_libname_544;
extern int unknown_libname_545;
extern int unknown_libname_546;
extern int unknown_libname_547;
extern int unknown_libname_548;
extern int unknown_libname_549;
extern int unknown_libname_550;
extern int unknown_libname_551;
extern int unknown_libname_552;

// 0x004017D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_287()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00401810
// likely CEffShock method (near Create)
int __stdcall ArraySort(int base, int count, int elemSize, int compareFunc)
{
  int result; // eax
  int v6; // edi

  result = elemSize - 1;
  if ( elemSize - 1 >= 0 )
  {
    v6 = elemSize;
    do
    {
      result = ((int (__thiscall *)(int))compareFunc)(base);
      base += count;
      --v6;
    }
    while ( v6 );
  }
  return result;
}

// 0x00401B40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_288()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00401FA0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_289()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004021E0
int __thiscall WinProc_HWND_4021E0(GRPinput *_this, int a2, int a3, int a4)
{
  _this->m_shiftedKeyStates[201] = a2;
  if ( a2 )
    GRPinput::AcquireDevices(_this);
  else
    WinProc_HWND_402360((int *)_this);
  _this->m_shiftedKeyStates[202] = a3;
  if ( a3 )
    return GRPinput::ReleaseDevices(_this);
  else
    return EnumJoystick((int)_this);
}

// 0x00402360
int __thiscall WinProc_HWND_402360(int *_this)
{
  int v1; // ecx
  int result; // eax

  *(_this + 1563) = 0;
  v1 = *(_this + 2);
  if ( v1 )
    return (*(int (__stdcall **)(int))(*(_DWORD *)v1 + 32))(v1);
  return result;
}

// 0x00402B30
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_290()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00403110
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_291()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00404430
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_292()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004044B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_293()
{
  return sub_431870(&stru_BFAB60);
}

// 0x004044D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_294()
{
  sub_4318A0((int)&stru_BFAB60);
}

// 0x004044F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
char *unknown_libname_295()
{
  return sub_53C250(&g_GDB.m_ItemData[360].desc[144]);
}

// 0x00404510
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_296()
{
  std::strstreambuf::~strstreambuf((std::strstreambuf *)&g_GDB.m_ItemData[360].desc[144]);
}

// 0x00404570
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
GRPinput *unknown_libname_297()
{
  g_Input.m_mouseMaxX = 0x7FFFFFFF;
  g_Input.m_mouseMaxY = 0x7FFFFFFF;
  g_Input.m_joystickMaxX = 0x7FFFFFFF;
  g_Input.m_joystickMaxY = 0x7FFFFFFF;
  g_Input.m_lpDI = 0;
  g_Input.m_lpDIDKeyboard = 0;
  g_Input.m_lpDIDMouse = 0;
  g_Input.m_shiftedKeyStates[201] = 0;
  g_Input.m_shiftedKeyStates[202] = 0;
  g_Input.m_shiftedKeyStates[203] = 0;
  g_Input.m_mouseSensitivity = 1.0;
  g_Input.m_mouseMinX = 0x80000000;
  g_Input.m_mouseMinY = 0x80000000;
  g_Input.m_joystickMinX = 0x80000000;
  g_Input.m_joystickMinY = 0x80000000;
  g_Input.m_mouseX = 0;
  g_Input.m_mouseY = 0;
  g_Input.m_mouseFreeX = 0;
  g_Input.m_mouseFreeY = 0;
  g_Input.m_mouseDeltaX = 0;
  g_Input.m_mouseDeltaY = 0;
  g_Input.m_joystickX = 0;
  g_Input.m_joystickY = 0;
  g_Input.m_joystickFreeX = 0;
  g_Input.m_joystickFreeY = 0;
  g_Input.m_joystickDeltaX = 0;
  g_Input.m_joystickDeltaY = 0;
  memset(g_Input.m_keyStates, 0, 0x10Cu);
  LOWORD(g_Input.m_keyStates[67]) = 0;
  memset((char *)&g_Input.m_keyStates[67] + 2, 0, 0x10Cu);
  HIWORD(g_Input.m_keyStates[134]) = 0;
  memset(&g_Input.m_keyStates[132], 0, 0x438u);
  memset(&g_Input.m_keyRaw[132], 0, 0x870u);
  return &g_Input;
}

// 0x00404590
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_298()
{
  if ( g_Input.m_lpDI )
  {
    if ( g_Input.m_lpDIDKeyboard )
    {
      EnumJoystick((int)&g_Input);
      (*(void (__stdcall **)(IDirectInputDevice8A *))(*(_DWORD *)g_Input.m_lpDIDKeyboard + 8))(g_Input.m_lpDIDKeyboard);
      g_Input.m_lpDIDKeyboard = 0;
    }
    if ( g_Input.m_lpDIDMouse )
    {
      WinProc_HWND_402360((int *)&g_Input);
      (*(void (__stdcall **)(IDirectInputDevice8A *))(*(_DWORD *)g_Input.m_lpDIDMouse + 8))(g_Input.m_lpDIDMouse);
      g_Input.m_lpDIDMouse = 0;
    }
    (*(void (__stdcall **)(IDirectInput8A *))(*(_DWORD *)g_Input.m_lpDI + 8))(g_Input.m_lpDI);
    g_Input.m_lpDI = 0;
  }
}

// 0x004045B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_299()
{
  return sub_478C00(&g_GDB);
}

// 0x004045D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_300()
{
  nullsub_3(&g_GDB);
}

// 0x004045F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_301()
{
  return sub_457260((_DWORD *)&g_PAL3Data + 82);
}

// 0x00404610
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_302()
{
  sub_457340((int)(&g_PAL3Data + 328));
}

// 0x00404630
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_BYTE *unknown_libname_303()
{
  return sub_430180((_BYTE *)&g_PAL3Data + 312);
}

// 0x00404650
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_304()
{
  SceneObj *v0; // [esp+0h] [ebp-4h] BYREF

  v0 = &g_PAL3Data + 312;
  sub_430B30((_DWORD *)&g_PAL3Data + 78, &v0, **((_DWORD ***)&g_PAL3Data + 79), *((_DWORD **)&g_PAL3Data + 79));
  operator delete(*((void **)&g_PAL3Data + 79));
  *((_DWORD *)&g_PAL3Data + 79) = 0;
  *((_DWORD *)&g_PAL3Data + 81) = 0;
  if ( !--*(_DWORD *)&String[256] )
  {
    operator delete(dword_D8C2B0);
    dword_D8C2B0 = 0;
  }
}

// 0x00407D50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_305()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00408640
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_306()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004086C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void unknown_libname_307()
{
  UIWnd::ctor_A160((UIWnd *)&g_SceneMgr.m_pCameraCtrl);
}

// 0x004086E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_308()
{
  UIWnd::ctor_A1F0((UIWnd *)&g_SceneMgr.m_pCameraCtrl);
}

// 0x00408700
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
Iostream_init *unknown_libname_309()
{
  return Iostream_init::Iostream_init((Iostream_init *)&g_SceneMgr.m_pGameData);
}

// 0x00408720
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_310()
{
  nullsub_3(&g_SceneMgr.m_pGameData);
}

// 0x004087B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_311()
{
  return sub_40CC60((int)&g_SceneMgr.m_slot4[792]);
}

// 0x00408800
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
gbVec3D *unknown_libname_312()
{
  g_SceneMgr.m_slot4[776] = (unsigned int)&g_SceneMgr.m_slot4[776] >> 24;
  *(_DWORD *)&g_SceneMgr.m_slot4[780] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[784] = 0;
  *(_DWORD *)&g_SceneMgr.m_slot4[788] = 0;
  return (gbVec3D *)&g_SceneMgr.m_slot4[776];
}

// 0x00408A20
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void unknown_libname_313()
{
  sub_411900(dword_C020F8);
}

// 0x00408A70
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void unknown_libname_314()
{
  sub_411900(dword_BFFDB0);
}

// 0x00408AC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void unknown_libname_315()
{
  sub_411900(&g_Input.KeyInfo[198].Data);
}

// 0x00408B40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_316()
{
  return PtrArray::Clear((PtrArray *)&g_Input.KeyInfo[195]);
}

// 0x00408B90
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
UIWnd *unknown_libname_317()
{
  return sub_444F60((UIWnd *)&g_Input.KeyInfo[182]);
}

// 0x00408BB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_318()
{
  sub_445010((UIWnd *)&g_Input.KeyInfo[182]);
}

// 0x0040C230
// between_std_methods (0x407D40-0x411B80)
__int8 *__cdecl ScriptUpdate(int dt)
{
  __int8 *v1; // esi
  double v2; // st7
  double v3; // st7
  __int8 *v4; // ecx
  double v5; // st7
  double v6; // st7
  __int8 *result; // eax
  bool v8; // cl
  int v9; // edx
  int v10; // [esp+14h] [ebp-24h]
  int v11; // [esp+18h] [ebp-20h]
  int v12; // [esp+1Ch] [ebp-1Ch]
  _BYTE v13[12]; // [esp+20h] [ebp-18h]
  gbVec3D v14; // [esp+2Ch] [ebp-Ch] BYREF

  v1 = &g_SceneMgr.m_slot4[840];
  do
  {
    ScriptSystem::UpdateTimers(*(float *)&dt);
    v1 += 8704;
  }
  while ( (int)v1 < (int)&g_SceneMgr.m_pGameData );
  if ( dword_C025EC == 10 )
  {
    if ( *(_DWORD *)&g_SceneMgr._midRegion[632] )
      ScriptSystem::UpdateObjects(*(float *)&dt);
  }
  else if ( dword_C025EC == 11 )
  {
    sub_419690((int)dword_C020F8, *(float *)&dt);
  }
  else if ( dword_C02370 )
  {
    ScriptSystem::UpdateTimers(*(float *)&dt);
  }
  if ( dword_C00028 )
  {
    if ( dword_C002A0 != 4 )
    {
      dword_C00028 = 0;
      RoleSystemNotify((int)dword_BFFDB0);
    }
    ScriptSystem::UpdateTimers(*(float *)&dt);
  }
  if ( g_Input.KeyInfo[237].CountMode )
  {
    if ( dword_BFE0A0 != 4 )
    {
      g_Input.KeyInfo[237].CountMode = 0;
      RoleSystemNotify((int)&g_Input.KeyInfo[198]);
    }
    ScriptSystem::UpdateTimers(*(float *)&dt);
    *(float *)&g_Input.KeyInfo[208].HoldTime = *(float *)&g_Input.KeyInfo[208].HoldTime + 80.0;
  }
  if ( g_Input.KeyInfo[197].HoldTime <= 4u )
  {
    if ( g_Input.KeyInfo[196].Data )
    {
      v3 = *(float *)&g_Input.KeyInfo[197].PressTime + *(float *)&dt;
      *(float *)&g_Input.KeyInfo[197].PressTime = v3;
      if ( v3 >= 4.0 )
      {
        g_Input.KeyInfo[197].PressTime = 0;
        switch ( g_Input.KeyInfo[197].HoldTime )
        {
          case 0:
          case 1:
            ScriptSystem::RunScript(1, 0, 1);
            break;
          case 2:
            ScriptSystem::RunWithDelay(0.5, 0, 1);
            break;
          case 3:
            ScriptSystem::RunScript(
              (__int64)((double)*(int *)&g_SceneMgr.m_slot0[1408 * g_SceneMgr.m_nCameraState + 292] * 0.050000001),
              0,
              1);
            break;
          case 4:
            *(float *)&g_Input.KeyInfo[197].CountMode = *(float *)&g_Input.KeyInfo[197].CountMode * 1.5;
            ScriptSystem::RunScript((__int64)*(float *)&g_Input.KeyInfo[197].CountMode, 0, 1);
            break;
          default:
            break;
        }
      }
    }
    else
    {
      switch ( g_Input.KeyInfo[197].HoldTime )
      {
        case 0:
          v2 = (double)*(int *)&g_SceneMgr.m_slot0[1408 * g_SceneMgr.m_nCameraState + 340] * 0.5;
          if ( v2 < 1.0 )
            v2 = 1.0;
          ScriptSystem::RunScript(
            *(_DWORD *)&g_SceneMgr.m_slot0[1408 * g_SceneMgr.m_nCameraState + 340] - (__int64)v2,
            1,
            1);
          break;
        case 1:
        case 2:
          ScriptSystem::RunWithDelay(0.5, 1, 1);
          break;
        case 3:
          ScriptSystem::RunScript(
            (__int64)((double)*(int *)&g_SceneMgr.m_slot0[1408 * g_SceneMgr.m_nCameraState + 292] * 0.050000001),
            1,
            1);
          break;
        case 4:
          *(float *)&g_Input.KeyInfo[197].CountMode = (double)*(int *)&g_SceneMgr.m_slot0[1408
                                                                                        * g_SceneMgr.m_nCameraState
                                                                                        + 292]
                                                    * 0.5;
          ScriptSystem::RunScript((__int64)*(float *)&g_Input.KeyInfo[197].CountMode, 1, 1);
          break;
        default:
          break;
      }
    }
    ++g_Input.KeyInfo[196].Data;
    v4 = &g_SceneMgr.m_slot4[8704 * g_SceneMgr.m_nCameraState + 844];
    v10 = *(_DWORD *)v4;
    v11 = *((int *)v4 + 1);
    *(float *)v13 = *(float *)v4 - *(float *)&g_Input.KeyInfo[196].CountMode;
    v12 = *((int *)v4 + 2);
    *(float *)&v13[4] = *(float *)&v11 - *(float *)&g_Input.KeyInfo[196].PressTime;
    *(float *)&v13[8] = *(float *)&v12 - *(float *)&g_Input.KeyInfo[197].Data;
    v14 = *(gbVec3D *)v13;
    v5 = gbVec3D::Length(&v14) + *(float *)&g_Input.KeyInfo[196].HoldTime;
    g_Input.KeyInfo[196].PressTime = v11;
    g_Input.KeyInfo[196].CountMode = v10;
    g_Input.KeyInfo[197].Data = v12;
    *(float *)&g_Input.KeyInfo[196].HoldTime = v5;
    if ( v5 >= 12.0 * 100.0 )
      ScriptSystem::RunEvent(31, 1, 0);
  }
  v6 = *(float *)&g_SceneMgr._gap_c93c[4] + *(float *)&dt;
  *(float *)&g_SceneMgr._gap_c93c[4] = v6;
  if ( v6 >= 60.0 )
  {
    g_SceneMgr.m_slot0[79] = 0;
    g_SceneMgr.m_slot0[80] = 0;
    g_SceneMgr.m_slot0[81] = 0;
    g_SceneMgr.m_slot0[82] = 0;
    g_SceneMgr._gap_c5e0[849] = 0;
  }
  NPCAnimUpdate(*(float *)&dt);
  result = (__int8 *)sub_43A3E0((int)&g_SceneMgr.m_pCameraCtrl, dt, 0);
  if ( g_SceneMgr._gap_c5e0[848] )
  {
    v8 = 1;
    v9 = 0;
    result = &g_SceneMgr._postSlots[660];
    do
    {
      if ( v9 != g_SceneMgr.m_nCameraState )
        v8 = v8 && (*((_DWORD *)result + 9) != 4 || *(_DWORD *)result != 10);
      result += 8704;
      ++v9;
    }
    while ( (int)result < (int)&g_SceneMgr.m_szUIString[244] );
    if ( v8 )
    {
      g_SceneMgr._gap_c5e0[848] = 0;
      result = (__int8 *)sub_41D5C0((_DWORD *)g_Input.KeyInfo[177].CountMode, dword_586154);
    }
  }
  if ( *(_DWORD *)&g_SceneMgr._gap_c5e0[844] )
    return (__int8 *)(*(_DWORD *(__thiscall **)(_DWORD))(**(_DWORD **)&g_SceneMgr._gap_c5e0[844] + 20))(*(_DWORD *)&g_SceneMgr._gap_c5e0[844]);
  return result;
}

// 0x0040CC90
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void __thiscall CCBStageRole_Init(int _this)
{
  operator delete(*(void **)(_this + 24));
  *(_DWORD *)(_this + 24) = 0;
  *(_DWORD *)(_this + 28) = 0;
  *(_DWORD *)(_this + 32) = 0;
  operator delete(*(void **)(_this + 4));
  *(_DWORD *)(_this + 4) = 0;
  *(_DWORD *)(_this + 8) = 0;
  *(_DWORD *)(_this + 12) = 0;
}

// 0x0040CCF0
// between_std_methods (0x407D40-0x411B80)
char *__thiscall CCBStageRole_GetAlive(int _this, _DWORD *pConfig)
{
  char *result; // eax
  char *v4; // ecx
  char *v5; // edi
  int v6; // ebx
  unsigned int v7; // ebp
  int v8; // edx
  unsigned int v9; // eax
  char *v10; // eax
  char *v11; // ebp
  char *j; // ebx
  int v13; // eax
  int v14; // ecx
  char *v15; // ecx
  char *i; // eax
  char *v17; // edi
  int v18; // ecx
  unsigned int v19; // [esp+10h] [ebp-8h]
  char *v20; // [esp+14h] [ebp-4h]

  result = (char *)CCBStageRole_GetByIndex((_DWORD *)_this, pConfig);
  if ( result )
  {
    v18 = pConfig[1] + *((_DWORD *)result + 1);
    if ( v18 > 99 )
      v18 = 99;
    *((_DWORD *)result + 1) = v18;
  }
  else
  {
    v4 = *(char **)(_this + 8);
    v5 = v4;
    if ( (*(_DWORD *)(_this + 12) - (int)v4) / 12 )
    {
      Array::Insert(v4, v4, v4 + 12);
      Array::Erase(*(void **)(_this + 8), 1 - (*(_DWORD *)(_this + 8) - (int)v5) / 12, pConfig);
      v15 = *(char **)(_this + 8);
      for ( i = v5; i != v15; *((_DWORD *)v17 + 2) = pConfig[2] )
      {
        v17 = i;
        i += 12;
        *(_DWORD *)v17 = *pConfig;
        *((_DWORD *)v17 + 1) = pConfig[1];
      }
      result = (char *)(*(_DWORD *)(_this + 8) + 12);
      *(_DWORD *)(_this + 8) = result;
    }
    else
    {
      v6 = *(_DWORD *)(_this + 4);
      if ( !v6 || (v7 = (int)&v4[-v6] / 12, v7 <= 1) )
        v7 = 1;
      if ( v6 )
        v8 = (int)&v4[-v6] / 12;
      else
        v8 = 0;
      v9 = v8 + v7;
      v19 = v8 + v7;
      if ( (int)(v8 + v7) < 0 )
        v9 = 0;
      v10 = (char *)operator new(12 * v9);
      v11 = *(char **)(_this + 4);
      v20 = v10;
      for ( j = v10; v11 != v5; j += 12 )
      {
        Array::Copy(j, v11);
        v11 += 12;
      }
      Array::Erase(j, 1, pConfig);
      Array::Insert(v5, *(void **)(_this + 8), j + 12);
      nullsub_2(*(_DWORD *)(_this + 4), *(_DWORD *)(_this + 8));
      operator delete(*(void **)(_this + 4));
      *(_DWORD *)(_this + 12) = &v20[12 * v19];
      v13 = *(_DWORD *)(_this + 4);
      if ( v13 )
      {
        v14 = *(_DWORD *)(_this + 8);
        *(_DWORD *)(_this + 4) = v20;
        result = &v20[12 * ((v14 - v13) / 12) + 12];
        *(_DWORD *)(_this + 8) = result;
      }
      else
      {
        *(_DWORD *)(_this + 4) = v20;
        *(_DWORD *)(_this + 8) = v20 + 12;
        return v20 + 12;
      }
    }
  }
  return result;
}

// 0x0040CF60
// between_std_methods (0x407D40-0x411B80)
int __thiscall CCBStageRole_PassCmd(_DWORD *_this, _DWORD *a2)
{
  _DWORD *v3; // eax
  int v4; // ecx
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  _DWORD *v7; // ecx
  _DWORD *v8; // edi
  _DWORD *v9; // ebx

  v3 = CCBStageRole_GetByIndex(_this, a2);
  if ( !v3 )
    return 0;
  v4 = v3[1] - a2[1];
  v3[1] = v4;
  if ( v4 > 0 )
    return 1;
  v5 = (_DWORD *)*(_this + 2);
  v6 = v3 + 3;
  if ( v6 != v5 )
  {
    v7 = v6 - 3;
    do
    {
      v8 = v6;
      v9 = v7;
      v6 += 3;
      v7 += 3;
      *v9 = *v8;
      v9[1] = v8[1];
      v9[2] = v8[2];
    }
    while ( v6 != v5 );
  }
  *(_this + 2) -= 12;
  return 2;
}

// 0x0040D010
// between_std_methods (0x407D40-0x411B80)
int __thiscall CCBStageRole_CheckValid(int *_this, int a2)
{
  int *v2; // ebp
  int *v3; // esi
  int v4; // ebx
  int v5; // eax
  int v6; // ecx
  _DWORD *v7; // eax
  bool v8; // zf
  int v9; // ecx
  int v10; // edx
  char v11; // al
  int v12; // eax
  int v13; // ecx
  char v14; // al
  char v15; // al
  int v16; // eax
  int v17; // eax
  int v18; // ecx
  char v19; // dl
  int v20; // eax
  _WORD *v21; // edi
  int v22; // ecx
  char *v23; // edi
  int v24; // ebx
  unsigned int v25; // ebp
  int v26; // edx
  unsigned int v27; // eax
  char *v28; // eax
  char *v29; // ebx
  char *j; // ebp
  char *v31; // ebx
  char *k; // ebp
  int v33; // eax
  char *i; // eax
  _DWORD *v35; // edx
  int result; // eax
  _DWORD *src; // [esp+Ch] [ebp-18h]
  int v39; // [esp+14h] [ebp-10h]
  unsigned int v40; // [esp+18h] [ebp-Ch]
  int v41; // [esp+1Ch] [ebp-8h]
  int v42; // [esp+20h] [ebp-4h]

  v2 = _this;
  v3 = _this + 5;
  sub_410DF0(_this + 5, (_DWORD *)*(_this + 6), (_DWORD *)*(_this + 7));
  v4 = 0;
  v42 = sub_40CCD0(v2);
  v39 = 0;
  if ( v42 > 0 )
  {
    do
    {
      switch ( a2 )
      {
        case 0:
          v5 = v2[1];
          v6 = *(_DWORD *)(v5 + 12 * v4 + 8);
          v7 = (_DWORD *)(v5 + 12 * v4);
          v8 = *(_BYTE *)(v6 + 612) == 1;
          goto LABEL_13;
        case 1:
          v7 = (_DWORD *)(v2[1] + 12 * v4);
          v8 = *(_BYTE *)(v7[2] + 612) == 3;
          goto LABEL_13;
        case 2:
          v9 = v2[1];
          if ( *(_BYTE *)(*(_DWORD *)(v9 + 12 * v4 + 8) + 612) == 2 )
            goto LABEL_5;
          break;
        case 3:
          v10 = v2[1];
          v11 = *(_BYTE *)(*(_DWORD *)(v10 + 12 * v4 + 8) + 612);
          if ( v11 == 5 || v11 == 12 )
            sub_410BD0((int)v3, (char *)v3[2], (_DWORD *)(v10 + 12 * v4));
          break;
        case 4:
          v9 = v2[1];
          if ( *(_BYTE *)(*(_DWORD *)(v9 + 12 * v4 + 8) + 612) == 4 )
LABEL_5:
            sub_410BD0((int)v3, (char *)v3[2], (_DWORD *)(v9 + 12 * v4));
          break;
        case 5:
          v12 = v2[1];
          v13 = *(_DWORD *)(v12 + 12 * v4 + 8);
          v7 = (_DWORD *)(v12 + 12 * v4);
          v8 = *(_BYTE *)(v13 + 612) == 6;
LABEL_13:
          if ( v8 )
            sub_410BD0((int)v3, (char *)v3[2], v7);
          break;
        case 6:
          v14 = *(_BYTE *)(*(_DWORD *)(v2[1] + 12 * v4 + 8) + 612);
          if ( v14 == 7 || v14 == 8 || v14 == 9 || v14 == 10 || v14 == 11 )
            goto LABEL_45;
          break;
        case 7:
          if ( *(_BYTE *)(*(_DWORD *)(v2[1] + 12 * v4 + 8) + 612) == 11 )
            goto LABEL_45;
          break;
        case 8:
          v15 = *(_BYTE *)(*(_DWORD *)(v2[1] + 12 * v4 + 8) + 612);
          if ( v15 == 7 || v15 == 8 || v15 == 9 )
            goto LABEL_45;
          break;
        case 9:
          if ( *(_BYTE *)(*(_DWORD *)(v2[1] + 12 * v4 + 8) + 612) == 10 )
            goto LABEL_45;
          break;
        case 10:
          if ( *(_BYTE *)(*(_DWORD *)(v2[1] + 12 * v4 + 8) + 612) == 12 )
            goto LABEL_45;
          break;
        case 11:
          if ( *(_BYTE *)(*(_DWORD *)(v2[1] + 12 * v4 + 8) + 612) == 7 )
            goto LABEL_45;
          break;
        case 12:
          if ( *(_BYTE *)(*(_DWORD *)(v2[1] + 12 * v4 + 8) + 612) == 8 )
            goto LABEL_45;
          break;
        case 13:
          if ( *(_BYTE *)(*(_DWORD *)(v2[1] + 12 * v4 + 8) + 612) == 9 )
            goto LABEL_45;
          break;
        case 14:
          v16 = *(_DWORD *)(v2[1] + 12 * v4 + 8);
          if ( *(_BYTE *)(v16 + 612) == 1
            && (*(_WORD *)(v16 + 748) == 2
             || *(_BYTE *)(v16 + 631) == 2
             || *(__int16 *)(v16 + 644) > 0
             || *(_BYTE *)(v16 + 632) == 2
             || *(__int16 *)(v16 + 646) > 0
             || *(_BYTE *)(v16 + 633) == 2
             || *(__int16 *)(v16 + 648) > 0) )
          {
LABEL_45:
            RoleSystem::CheckVisible(v3[2]);
          }
          break;
        case 15:
          v17 = v2[1];
          v18 = *(_DWORD *)(v17 + 12 * v4 + 8);
          src = (_DWORD *)(v17 + 12 * v4);
          if ( *(_BYTE *)(v18 + 612) == 1 )
          {
            v19 = 0;
            v20 = 0;
            v21 = (_WORD *)(v18 + 700);
            do
            {
              if ( v20 != 24 && v20 != 23 && (*v21 == 1 || *v21 == 2) )
                v19 = 1;
              ++v20;
              ++v21;
            }
            while ( v20 < 26 );
            if ( v19 )
            {
              v22 = v3[2];
              v23 = (char *)v22;
              if ( (v3[3] - v22) / 12 )
              {
                Array::Insert((void *)v22, (void *)v22, (void *)(v22 + 12));
                Array::Erase((void *)v3[2], 1 - (v3[2] - (int)v23) / 12, src);
                for ( i = (char *)v3[2]; v23 != i; v35[2] = src[2] )
                {
                  v35 = v23;
                  v23 += 12;
                  *v35 = *src;
                  v35[1] = src[1];
                }
                v2 = _this;
                v3[2] += 12;
              }
              else
              {
                v24 = v3[1];
                if ( !v24 || (v25 = (v22 - v24) / 12, v25 <= 1) )
                  v25 = 1;
                if ( v24 )
                  v26 = (v22 - v24) / 12;
                else
                  v26 = 0;
                v27 = v26 + v25;
                v40 = v26 + v25;
                if ( (int)(v26 + v25) < 0 )
                  v27 = 0;
                v28 = (char *)operator new(12 * v27);
                v29 = (char *)v3[1];
                v41 = (int)v28;
                for ( j = v28; v29 != v23; j += 12 )
                {
                  Array::Copy(j, v29);
                  v29 += 12;
                }
                Array::Copy(j, src);
                v31 = (char *)v3[2];
                for ( k = j + 12; v23 != v31; k += 12 )
                {
                  Array::Copy(k, v23);
                  v23 += 12;
                }
                nullsub_2(v3[1], v3[2]);
                operator delete((void *)v3[1]);
                v3[3] = v41 + 12 * v40;
                v33 = Array::Size(v3);
                v4 = v39;
                v2 = _this;
                v3[1] = v41;
                v3[2] = v41 + 12 * (v33 + 1);
              }
            }
          }
          break;
        default:
          break;
      }
      v39 = ++v4;
    }
    while ( v4 < v42 );
  }
  result = v3[1];
  if ( result )
    return (v3[2] - result) / 12;
  return result;
}

// 0x0040DCF0
// between_std_methods (0x407D40-0x411B80)
_DWORD *__thiscall CCBStageRole_GetByIndex(_DWORD *_this, _DWORD *a2)
{
  _DWORD *v3; // edi
  _DWORD *i; // esi

  v3 = (_DWORD *)*(_this + 2);
  for ( i = (_DWORD *)*(_this + 1); i != v3; i += 3 )
  {
    if ( sub_40DCD0(i, a2) )
      break;
  }
  return *(_this + 2) != (_DWORD)i ? i : 0;
}

// 0x0040DD30
// between_std_methods (0x407D40-0x411B80)
int __thiscall CCBStageRole_Find(_DWORD *_this, char *String1)
{
  int v3; // esi

  v3 = *(_this + 1);
  if ( v3 == *(_this + 2) )
    return 0;
  while ( _strcmpi(String1, (const char *)(*(_DWORD *)(v3 + 8) + 36)) )
  {
    v3 += 12;
    if ( v3 == *(_this + 2) )
      return 0;
  }
  return 1;
}

// 0x0040DD80
// between_std_methods (0x407D40-0x411B80)
int __thiscall CCBStageRole_Reset(_DWORD *_this)
{
  int v1; // edx
  int result; // eax

  v1 = *(_this + 1);
  *(_this + 4) = -1;
  *(_this + 9) = 0;
  *(_this + 2) = v1;
  result = *(_this + 7);
  *(_this + 7) = *(_this + 6);
  return result;
}

// 0x004105B0
// between_std_methods (0x407D40-0x411B80)
int __cdecl NPCAnimUpdate(float a1)
{
  char v1; // bl
  int v2; // edi
  int v3; // esi
  double v4; // st7
  double v5; // st6
  double v6; // st6
  double v7; // st7
  int HoldTime; // edx
  int i; // esi
  int v10; // edi
  int v11; // esi
  GRPinput *v12; // ecx
  int v14; // eax
  int Data; // ecx
  int v16; // ecx
  unsigned __int8 v17; // [esp+13h] [ebp-15h]
  int v18; // [esp+14h] [ebp-14h]
  _DWORD a2[4]; // [esp+18h] [ebp-10h] BYREF
  int v20; // [esp+2Ch] [ebp+4h]

  v1 = 0;
  v2 = 0;
  v18 = -1;
  v17 = 0;
  if ( g_Input.KeyInfo[195].HoldTime <= 0 )
    return sub_445720((UIWnd *)&g_Input.KeyInfo[182], 0);
  do
  {
    v3 = *(_DWORD *)(g_Input.KeyInfo[195].Data + 4 * v2);
    GRPinput::SetJoystickFreePos(v3, a1);
    if ( *(_BYTE *)(v3 + 4) )
    {
      if ( *(_DWORD *)(v3 + 28) == 1 )
      {
        if ( *(_DWORD *)(v3 + 16) > v18 )
          v18 = *(_DWORD *)(v3 + 16);
        v4 = *(float *)(v3 + 24) - 1.5;
        if ( v4 >= 0.0 )
          v5 = v4;
        else
          v5 = 0.0;
        v6 = 1.0 - v5 * 0.40000001;
        if ( v6 < 0.0 )
          v6 = 0.0;
        if ( (unsigned __int8)(__int64)(v6 * 255.0) > v17 )
        {
          if ( v4 < 0.0 )
            v4 = 0.0;
          v7 = 1.0 - v4 * 0.40000001;
          if ( v7 < 0.0 )
            v7 = 0.0;
          v17 = (__int64)(v7 * 255.0);
        }
      }
    }
    else
    {
      if ( v3 )
        (**(void (__thiscall ***)(int, int))v3)(v3, 1);
      if ( v2 >= 0 && v2 < g_Input.KeyInfo[195].HoldTime )
        *(_DWORD *)(g_Input.KeyInfo[195].Data + 4 * v2) = 0;
      v1 = 1;
    }
    HoldTime = g_Input.KeyInfo[195].HoldTime;
    ++v2;
  }
  while ( v2 < g_Input.KeyInfo[195].HoldTime );
  if ( v1 )
  {
    for ( i = 0; i < g_Input.KeyInfo[195].HoldTime; HoldTime = g_Input.KeyInfo[195].HoldTime )
    {
      if ( i >= 0 && i < HoldTime && *(_DWORD *)(g_Input.KeyInfo[195].Data + 4 * i) )
        ++i;
      else
        PtrArray::InsertAt((PtrArray *)&g_Input.KeyInfo[195], i, 1);
    }
    v10 = 0;
    v11 = 40;
    if ( HoldTime > 0 )
    {
      do
      {
        v12 = *(GRPinput **)(g_Input.KeyInfo[195].Data + 4 * v10);
        if ( v12->m_mouseMaxY == 1 )
        {
          GRPinput::GetMouseSensitivity(v12, v11);
          v11 += 24;
        }
        HoldTime = g_Input.KeyInfo[195].HoldTime;
        ++v10;
      }
      while ( v10 < g_Input.KeyInfo[195].HoldTime );
    }
  }
  if ( v18 == -1 )
    return sub_445720((UIWnd *)&g_Input.KeyInfo[182], 0);
  v14 = 0;
  if ( HoldTime > 0 )
  {
    Data = g_Input.KeyInfo[195].Data;
    do
    {
      if ( *(_DWORD *)(*(_DWORD *)Data + 28) == 1 )
        ++v14;
      Data += 4;
      --HoldTime;
    }
    while ( HoldTime );
  }
  a2[1] = 5;
  v16 = 10 * v18 + 64;
  a2[3] = 24 * v14 + 30;
  a2[0] = (g_Input.KeyInfo[120].Data - v16) / 2 < 0 ? 0 : (g_Input.KeyInfo[120].Data - v16) / 2;
  a2[2] = v16 + a2[0];
  UIWnd::GetRect((UIWnd *)&g_Input.KeyInfo[182], a2);
  sub_445720((UIWnd *)&g_Input.KeyInfo[182], 1);
  UIWnd::SetState((UIWnd *)&g_Input.KeyInfo[182], 1);
  *(_WORD *)((char *)&v20 + 1) = -1;
  LOBYTE(v20) = -1;
  HIBYTE(v20) = v17;
  return NPC::UpdateAnim(v20);
}

// 0x00411260
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_319()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004117A0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
__int8 *unknown_libname_320()
{
  sub_401000(&g_SceneMgr.m_szUIString[184]);
  *(_DWORD *)&g_SceneMgr.m_szUIString[184] = &off_56A6D0;
  *(_DWORD *)&g_SceneMgr.m_szUIString[208] = 0;
  *(_DWORD *)&g_SceneMgr.m_szUIString[212] = 0;
  g_SceneMgr.m_szUIString[216] = -1;
  return &g_SceneMgr.m_szUIString[184];
}

// 0x004117C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_321()
{
  sub_4083D0((void **)&g_SceneMgr.m_szUIString[184]);
}

// 0x004181E0
// between_std_methods (0x411BB0-0x430790)
int __thiscall RoleSystemNotify(int _this)
{
  int result; // eax

  sub_4142E0((RoleSystem *)_this);
  *(_DWORD *)(_this + 1284) = 0;
  RoleSystem::UpdateTransform((RoleSystem *)_this);
  *(_DWORD *)(_this + 8692) = *(_DWORD *)(_this + 4);
  *(_DWORD *)(_this + 8696) = *(_DWORD *)(_this + 8);
  *(_DWORD *)(_this + 8700) = *(_DWORD *)(_this + 12);
  result = *(_DWORD *)(_this + 1264);
  if ( result == 4 )
  {
    result = *(_DWORD *)(_this + 1260);
    *(_DWORD *)(_this + 1264) = result;
    if ( result == 4 )
      *(_DWORD *)(_this + 1264) = 1;
  }
  if ( *(_BYTE *)(_this + 173) == 3 )
    *(_BYTE *)(_this + 173) = 0;
  *(_DWORD *)(_this + 1460) = 0;
  return result;
}

// 0x0041B6A0
// between_std_methods (0x411BB0-0x430790)
gbGfxManager *__cdecl GetGfxManager_1()
{
  int v0; // ecx
  gbGfxManager *result; // eax
  int a3; // [esp+4h] [ebp+4h]

  RoleSystem::RenderRole((RoleSystem *)(v0 - 64), *(void **)(g_Input.KeyInfo[177].Data + 216), a3);
  return result;
}

// 0x0041BDF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_322()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0041C280
// between_std_methods (0x411BB0-0x430790)
int __thiscall InputUpdate(int _this, int a1)
{
  int result; // eax
  _DWORD *v4; // eax
  int v5; // eax
  _DWORD *v6; // eax
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st4
  double v11; // st5
  double v12; // st7
  double v13; // st7
  long double v14; // st7
  double v15; // st7
  float v16; // [esp+4h] [ebp-34h]
  gbVec3D v17; // [esp+8h] [ebp-30h] BYREF
  gbVec3D v18; // [esp+14h] [ebp-24h] BYREF
  float v19; // [esp+20h] [ebp-18h]
  float v20; // [esp+24h] [ebp-14h]
  float v21; // [esp+28h] [ebp-10h]
  float v22; // [esp+2Ch] [ebp-Ch]
  float y; // [esp+30h] [ebp-8h]
  float z; // [esp+34h] [ebp-4h]

  result = *(_DWORD *)(_this + 448);
  if ( !result )
    return result;
  v4 = *(_DWORD **)(_this + 380);
  memset(&v17, 0, sizeof(v17));
  if ( v4 )
  {
    *(_DWORD *)(_this + 388) = v4[40];
    *(_DWORD *)(_this + 392) = v4[41];
    v5 = v4[42];
LABEL_6:
    *(_DWORD *)(_this + 396) = v5;
    goto LABEL_7;
  }
  v6 = *(_DWORD **)(_this + 384);
  if ( v6 )
  {
    *(_DWORD *)(_this + 388) = v6[10];
    *(_DWORD *)(_this + 392) = v6[11];
    v5 = v6[12];
    goto LABEL_6;
  }
LABEL_7:
  if ( dword_D8BBEC == 1 )
    *(float *)(_this + 392) = *(float *)(_this + 540) + *(float *)(_this + 392);
  v7 = *(float *)(_this + 480) - *(float *)(_this + 388);
  y = *(float *)(_this + 484) - *(float *)(_this + 392);
  v8 = *(float *)(_this + 488) - *(float *)(_this + 396);
  v17.y = y;
  z = v8;
  v17.x = v7;
  v17.z = z;
  v9 = gbVec3D::Length(&v17);
  if ( v9 > 0.050000001 )
  {
    v17.y = v17.y / v9;
    v17.z = v17.z / v9;
    v10 = v17.x / v9;
    v22 = v10;
    z = v17.z;
    y = v17.y;
    v11 = (20.0 - v9) * 4.5999999 * *(float *)&a1;
    v16 = v11;
    v17.x = v11 * v10;
    v17.y = v17.y * v16;
    v17.z = v17.z * v16;
    *(float *)(_this + 480) = v17.x + *(float *)(_this + 480);
    *(float *)(_this + 484) = v17.y + *(float *)(_this + 484);
    *(float *)(_this + 488) = v17.z + *(float *)(_this + 488);
    v19 = *(float *)(_this + 480) - *(float *)(_this + 388);
    v12 = *(float *)(_this + 484) - *(float *)(_this + 392);
    v18.x = v19;
    v20 = v12;
    v13 = *(float *)(_this + 488) - *(float *)(_this + 396);
    v18.y = v20;
    v21 = v13;
    v18.z = v21;
    gbVec3D::Normalize(&v18);
    if ( z * v18.z + y * v18.y + v18.x * v22 <= 0.0 )
    {
      *(_DWORD *)(_this + 480) = *(_DWORD *)(_this + 388);
      *(_DWORD *)(_this + 484) = *(_DWORD *)(_this + 392);
      *(_DWORD *)(_this + 488) = *(_DWORD *)(_this + 396);
    }
  }
  v14 = *(float *)&a1 * *(float *)(_this + 460) * 32.0;
  if ( fabs(*(float *)(_this + 460)) > fabs(v14) )
  {
    *(float *)(_this + 456) = v14 + *(float *)(_this + 456);
    *(float *)(_this + 460) = *(float *)(_this + 460) - v14;
  }
  else
  {
    v15 = *(float *)(_this + 460) + *(float *)(_this + 456);
    *(_DWORD *)(_this + 460) = 0;
    *(float *)(_this + 456) = v15;
  }
  if ( dword_D8BBEC == 1 )
    InputSystem::ProcessMouse(a1);
  return InputSystem::ProcessKeyboard(1);
}

// 0x0041D8A0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_323()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0041D920
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
Iostream_init *unknown_libname_324()
{
  return Iostream_init::Iostream_init((Iostream_init *)&g_SceneMgr._gap_cd10[920]);
}

// 0x0041D940
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_325()
{
  nullsub_3(&g_SceneMgr._gap_cd10[920]);
}

// 0x0041D9A0
// between_std_methods (0x411BB0-0x430790)
void __cdecl CameraUpdate_Internal(float a1)
{
  double v1; // st7
  double v2; // st7
  float *v3; // eax
  double v4; // st7
  CScreenMode *Instance; // eax
  CScreenMode *v6; // eax
  int v7; // eax
  __int32 m_pCollisionNode; // esi
  __int32 *v9; // eax
  int v10; // edx
  int v11; // ebp
  int v12; // ebx
  int Target; // eax
  int v14; // edi
  float *v15; // eax
  int v16; // esi
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  char v22; // al
  bool v23; // cl
  __int32 v24; // ecx
  int v25; // eax
  int v26; // esi
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // esi
  int State; // eax
  int ViewMode; // eax
  float v34; // edx
  float v35; // eax
  float v36; // eax
  float v37; // eax
  double v38; // st7
  int v39; // [esp+0h] [ebp-5Ch]
  float pDist; // [esp+10h] [ebp-4Ch] BYREF
  int v41; // [esp+14h] [ebp-48h]
  float pOut2; // [esp+18h] [ebp-44h] BYREF
  float v43; // [esp+1Ch] [ebp-40h] BYREF
  gbVec3D a2; // [esp+20h] [ebp-3Ch] BYREF
  struct gbVec3D pOut[2]; // [esp+2Ch] [ebp-30h] BYREF
  float pMat[6]; // [esp+44h] [ebp-18h] BYREF

  if ( dword_58B230 <= 0 || !g_SceneMgr.m_pCollisionNode )
    return;
  GRPinput::GetCursorPos(&g_SceneMgr._gap_cd10[912]);
  if ( dword_58B234 && dword_D8BBEC != 1 )
  {
    v41 = g_Input.m_keyDragStartPositions[1][202];
    if ( g_Input.m_keyDragStartPositions[1][202] )
    {
      v1 = (double)v41 * 0.0013962634;
      pDist = v1;
      if ( v1 <= 1.5700001 )
      {
        if ( pDist < -1.5700001 )
          pDist = -1.5700001;
        CameraCtrl::SetCamMode((CameraCtrl *)g_Input.KeyInfo[177].CountMode, SLODWORD(pDist));
      }
      else
      {
        pDist = 1.5700001;
        CameraCtrl::SetCamMode((CameraCtrl *)g_Input.KeyInfo[177].CountMode, 1070134723);
      }
    }
    else if ( (g_Input.m_shiftedKeyStates[256] & 0xF) == 1 )
    {
      CameraCtrl::SetCamMode((CameraCtrl *)g_Input.KeyInfo[177].CountMode, 1034147594);
    }
    else if ( (g_Input.m_shiftedKeyStates[260] & 0xF) == 1 )
    {
      CameraCtrl::SetCamMode((CameraCtrl *)g_Input.KeyInfo[177].CountMode, -1113336054);
    }
  }
  if ( g_SceneMgr._tail )
  {
    v2 = 0.0;
    if ( (g_Input.m_shiftedKeyStates[220] & 0xF) == 1 )
    {
      v2 = 1.0;
    }
    else if ( (g_Input.m_shiftedKeyStates[224] & 0xF) == 1 )
    {
      v2 = -1.0;
    }
    if ( (g_Input.m_DIKToKEY[86] & 0xF) == 1 )
    {
      v3 = (float *)(g_Input.KeyInfo[177].CountMode + 4);
      v4 = v2 + *(float *)(g_Input.KeyInfo[177].CountMode + 4);
      *(_DWORD *)(g_Input.KeyInfo[177].CountMode + 8) = 0;
      *v3 = v4;
    }
    else if ( (g_Input.m_DIKToKEY[90] & 0xF) == 1 )
    {
      *(float *)(g_Input.KeyInfo[177].CountMode + 468) = v2 * 8.0 + *(float *)(g_Input.KeyInfo[177].CountMode + 468);
    }
    else if ( (g_Input.m_DIKToKEY[94] & 0xF) == 1 )
    {
      *(float *)(g_Input.KeyInfo[177].CountMode + 452) = v2 * 0.039250001
                                                       + *(float *)(g_Input.KeyInfo[177].CountMode + 452);
    }
    else if ( (g_Input.m_shiftedKeyStates[204] & 0xF) == 1 )
    {
      *(float *)(g_Input.KeyInfo[177].CountMode + 540) = v2 + v2 + *(float *)(g_Input.KeyInfo[177].CountMode + 540);
    }
    return;
  }
  Instance = (CScreenMode *)SoundContext::GetInstance();
  CScreenMode::SetAudioParam(Instance);
  v6 = (CScreenMode *)SoundContext::GetInstance();
  if ( CScreenMode::IsAudioReady(v6) && !g_SceneMgr._gap_c5e0[848] )
  {
    if ( g_Input.KeyInfo[177].PressTime == 2
      && dword_D8BBEC == 2
      && g_Input.m_shiftedKeyStates[255] == 1
      && (g_Input.m_shiftedKeyStates[252] & 0xF) == 1
      && !(*(int (__thiscall **)(__int32))(*(_DWORD *)(g_SceneMgr.m_pCollisionNode + 56) + 4))(g_SceneMgr.m_pCollisionNode + 56) )
    {
      v7 = g_SceneMgr.m_nCameraState + 1;
      if ( g_SceneMgr.m_nCameraState + 1 > 4 )
        v7 = 0;
      if ( !g_SceneMgr.m_slot4[v7 + 832] )
      {
        do
        {
          if ( ++v7 > 4 )
            v7 = 0;
        }
        while ( v7 != g_SceneMgr.m_nCameraState && !g_SceneMgr.m_slot4[v7 + 832] );
      }
      ScriptSystem::Execute(v7, 1);
    }
    m_pCollisionNode = g_SceneMgr.m_pCollisionNode;
    if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1264) != 4 )
      goto LABEL_51;
    if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1228) == 44 )
    {
      v9 = &g_Input.m_shiftedKeyStates[204];
      v10 = 0;
      while ( (*(_BYTE *)v9 & 0xF) != 1 )
      {
        v10 += 16;
        v9 += 4;
        if ( v10 >= 656 )
          goto LABEL_50;
      }
      RoleSystemNotify(g_SceneMgr.m_pCollisionNode);
      m_pCollisionNode = g_SceneMgr.m_pCollisionNode;
    }
LABEL_50:
    if ( *(_DWORD *)(m_pCollisionNode + 1264) != 4 )
    {
LABEL_51:
      LOBYTE(v41) = 0;
      if ( dword_D8BBEC == 2 )
        LOBYTE(v41) = Camera::IsTransitioning();
      UIWnd::Destroy((UIWnd *)&g_SceneMgr.m_pCameraCtrl, (unsigned __int8)v41);
      if ( (_BYTE)v41 )
      {
        memset(pOut, 0, 12);
        RoleSystem::GetDirection((RoleSystem *)g_SceneMgr.m_pCollisionNode, &pOut[0].x);
        pOut[0].y = pOut[0].y + 10.0;
        gbCamera::PointWorldToScr((gbCamera *)(g_Input.KeyInfo[177].CountMode + 4), pOut, &v43, &pOut2);
        UIWnd::ScreenToClient(
          (UIWnd *)&g_SceneMgr.m_pCameraCtrl,
          (__int64)((v43 + 1.0) * (double)g_Input.KeyInfo[120].Data * 0.5),
          (__int64)((1.0 - pOut2) * (double)g_Input.KeyInfo[120].HoldTime * 0.5));
      }
      v11 = 0;
      v12 = 0;
      pDist = 0.0;
      qmemcpy(
        pMat,
        CameraCtrl::GetViewTarget(
          (CameraCtrl *)g_Input.KeyInfo[177].CountMode,
          pOut,
          (float *)&g_SceneMgr._gap_cd10[912]),
        sizeof(pMat));
      if ( g_Input.KeyInfo[177].PressTime != 2 && g_Input.KeyInfo[177].PressTime != 8 )
        goto LABEL_107;
      Target = UICamera::GetTarget(pMat);
      v14 = Target;
      if ( Target && *(_DWORD *)(Target + 1264) == 7 )
        v14 = 0;
      UISceneUpdate();
      v15 = UICamera::CalcPosition(pMat);
      v16 = (int)v15;
      if ( !v15 )
      {
LABEL_90:
        if ( v14 && *(_BYTE *)(v14 + 173) != 2 && *(_DWORD *)(v14 + 264) )
        {
          UIQuadManager::GetInstance();
          UIQuadManager_Reset();
        }
        if ( v16 )
        {
          UIQuadManager::GetInstance();
          UIQuadManager_Reset();
        }
        if ( !v14 && !v16 )
        {
          UIQuadManager::GetInstance();
          UIQuadManager_Reset();
        }
        v24 = g_Input.m_shiftedKeyStates[207];
        if ( g_Input.m_shiftedKeyStates[207] != 1 )
          goto LABEL_109;
        if ( (g_Input.m_shiftedKeyStates[204] & 0xF) != 1 )
          goto LABEL_108;
        if ( v14 )
        {
          RoleSystem::UpdateAnimation((RoleSystem *)g_SceneMgr.m_pCollisionNode, v14);
          v11 = 1;
        }
        else
        {
          RoleSystem::GetActiveRole((RoleSystem *)g_SceneMgr.m_pCollisionNode);
        }
        if ( v16 )
        {
          RoleSystem::SetState((RoleSystem *)g_SceneMgr.m_pCollisionNode, v16);
          goto LABEL_153;
        }
        if ( v11 )
          goto LABEL_153;
LABEL_107:
        v24 = g_Input.m_shiftedKeyStates[207];
        if ( g_Input.m_shiftedKeyStates[207] == 1 )
        {
LABEL_108:
          if ( (g_Input.m_shiftedKeyStates[204] & 0xF) == 1 )
            goto LABEL_115;
        }
LABEL_109:
        v25 = g_Input.m_shiftedKeyStates[204] & 0xF;
        if ( v25 != 1
          && (v24 != 1 || v25 != 2)
          && (g_Input.m_shiftedKeyStates[204] & 0xFu) <= 1
          && (g_Input.m_shiftedKeyStates[211] != 1 || (g_Input.m_shiftedKeyStates[208] & 0xF) != 1) )
        {
          goto LABEL_153;
        }
LABEL_115:
        if ( !Camera::CheckCollision1(&g_SceneMgr._gap_cd10[912], &g_SceneMgr._gap_cd10[896], &pDist)
          && !Camera::CheckCollision2(
                &g_SceneMgr._gap_cd10[912],
                *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628),
                &g_SceneMgr._gap_cd10[896]) )
        {
          goto LABEL_153;
        }
        a2.x = *(float *)&g_SceneMgr._gap_cd10[896];
        a2.z = *(float *)&g_SceneMgr._gap_cd10[904];
        a2.y = 0.0;
        v26 = 0;
        GRPinput::GetMousePos(&g_Input, &v43, &pOut2);
        if ( v43 != 0.0 || pOut2 != 0.0 )
          v26 = 1;
        *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1460) = 0;
        if ( g_Input.m_shiftedKeyStates[207] == 1 && (g_Input.m_shiftedKeyStates[204] & 0xF) == 1 )
        {
          RoleSystem::UpdateRole((RoleSystem *)g_SceneMgr.m_pCollisionNode, (int)&a2, SLODWORD(pDist), 1);
          v27 = *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628);
          if ( LODWORD(pDist) != v27
            && !*(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1268)
            && Camera::CheckCollision2(&g_SceneMgr._gap_cd10[912], v27, &a2) )
          {
            a2.y = 0.0;
            RoleSystem::UpdateRole(
              (RoleSystem *)g_SceneMgr.m_pCollisionNode,
              (int)&a2,
              *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628),
              1);
          }
        }
        else if ( (g_Input.m_shiftedKeyStates[204] & 0xF) == 1 && (double)g_Input.m_shiftedKeyStates[207] * a1 > 0.5 )
        {
          RoleSystem::MoveRole((RoleSystem *)g_SceneMgr.m_pCollisionNode, &a2.x, SLODWORD(pDist), 1, v26);
          v28 = *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628);
          if ( LODWORD(pDist) != v28
            && !*(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1268)
            && Camera::CheckCollision2(&g_SceneMgr._gap_cd10[912], v28, &a2) )
          {
            a2.y = 0.0;
            RoleSystem::MoveRole(
              (RoleSystem *)g_SceneMgr.m_pCollisionNode,
              &a2.x,
              *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628),
              1,
              1);
          }
        }
        else if ( g_Input.m_shiftedKeyStates[207] == 1 && (g_Input.m_shiftedKeyStates[204] & 0xF) == 2 )
        {
          RoleSystem::UpdateRole((RoleSystem *)g_SceneMgr.m_pCollisionNode, (int)&a2, SLODWORD(pDist), 2);
          v29 = *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628);
          if ( LODWORD(pDist) != v29
            && !*(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1268)
            && Camera::CheckCollision2(&g_SceneMgr._gap_cd10[912], v29, &a2) )
          {
            a2.y = 0.0;
            RoleSystem::UpdateRole(
              (RoleSystem *)g_SceneMgr.m_pCollisionNode,
              (int)&a2,
              *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628),
              2);
          }
        }
        else
        {
          if ( (g_Input.m_shiftedKeyStates[204] & 0xFu) <= 1 || (double)g_Input.m_shiftedKeyStates[207] * a1 <= 0.5 )
          {
LABEL_145:
            if ( (g_SceneMgr._gap_cd10[1610] || (_BYTE)v41 && dword_D8BBEC == 2)
              && g_Input.m_shiftedKeyStates[211] == 1
              && (g_Input.m_shiftedKeyStates[208] & 0xF) == 1
              && *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628) == LODWORD(pDist) )
            {
              RoleSystem::PathFind((RoleSystem *)g_SceneMgr.m_pCollisionNode, &a2.x);
              v12 = 4;
              goto LABEL_166;
            }
            if ( v12 )
              goto LABEL_166;
LABEL_153:
            v31 = 0;
            memset(&a2, 0, sizeof(a2));
            if ( g_Input.m_shiftedKeyStates[231] == 1 && (g_Input.m_shiftedKeyStates[228] & 0xF) == 1 )
            {
              if ( g_Input.KeyInfo[177].PressTime == 2 )
              {
                State = UICamera::GetState();
                if ( State && *(_DWORD *)(State + 1264) != 7 )
                {
                  if ( *(_BYTE *)(State + 173) != 2 && *(_DWORD *)(State + 264) )
                    RoleSystem::UpdateAnimation((RoleSystem *)g_SceneMgr.m_pCollisionNode, State);
                }
                else
                {
                  UISceneUpdate();
                  ViewMode = UICamera::GetViewMode(v39);
                  if ( ViewMode )
                    RoleSystem::SetState((RoleSystem *)g_SceneMgr.m_pCollisionNode, ViewMode);
                }
              }
              goto LABEL_163;
            }
            if ( (g_Input.m_shiftedKeyStates[216] & 0xF) == 1 )
            {
              v31 = 1;
              a2.x = *(float *)(g_Input.KeyInfo[177].CountMode + 528);
              a2.y = *(float *)(g_Input.KeyInfo[177].CountMode + 532);
              a2.z = *(float *)(g_Input.KeyInfo[177].CountMode + 536);
LABEL_176:
              v12 = 3;
              goto LABEL_177;
            }
            if ( (g_Input.m_shiftedKeyStates[216] & 0xFu) <= 1 )
            {
              if ( (g_Input.m_shiftedKeyStates[212] & 0xF) == 1 )
              {
                a2.x = -*(float *)(g_Input.KeyInfo[177].CountMode + 528);
                a2.y = -*(float *)(g_Input.KeyInfo[177].CountMode + 532);
                a2.z = -*(float *)(g_Input.KeyInfo[177].CountMode + 536);
                v31 = 1;
                goto LABEL_176;
              }
              if ( (g_Input.m_shiftedKeyStates[212] & 0xFu) <= 1 )
              {
LABEL_177:
                if ( (g_Input.m_shiftedKeyStates[220] & 0xF) == 1 )
                {
                  pOut[0].x = *(float *)(g_Input.KeyInfo[177].CountMode + 504);
                  pOut[0].y = *(float *)(g_Input.KeyInfo[177].CountMode + 508);
                  v34 = *(float *)(g_Input.KeyInfo[177].CountMode + 512);
                  pOut[0].y = 0.0;
                  pOut[0].z = v34;
                  gbVec3D::Normalize(pOut);
                  v31 = 1;
                  v12 = 3;
                  a2.x = pOut[0].x + a2.x;
                  a2.y = a2.y + pOut[0].y;
                  a2.z = a2.z + pOut[0].z;
                }
                else if ( (g_Input.m_shiftedKeyStates[220] & 0xFu) <= 1 )
                {
                  if ( (g_Input.m_shiftedKeyStates[224] & 0xF) == 1 )
                  {
                    pOut[0].x = *(float *)(g_Input.KeyInfo[177].CountMode + 504);
                    pOut[0].y = *(float *)(g_Input.KeyInfo[177].CountMode + 508);
                    v36 = *(float *)(g_Input.KeyInfo[177].CountMode + 512);
                    pOut[0].y = 0.0;
                    pOut[0].z = v36;
                    gbVec3D::Normalize(pOut);
                    v31 = 1;
                    v12 = 3;
                    a2.x = a2.x - pOut[0].x;
                    a2.y = a2.y - pOut[0].y;
                    a2.z = a2.z - pOut[0].z;
                  }
                  else if ( (g_Input.m_shiftedKeyStates[224] & 0xFu) <= 1 )
                  {
                    if ( v12 != 3 )
                    {
LABEL_163:
                      if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1264) == 3 )
                      {
                        memset(pOut, 0, 12);
                        RoleSystem::GetPosition((RoleSystem *)g_SceneMgr.m_pCollisionNode, pOut, 0);
                      }
                      v38 = flt_C116F8[0] + a1;
                      flt_C116F8[0] = v38;
                      if ( v38 > flt_58B238 )
                      {
                        flt_C116F8[0] = 0.0;
                        RoleSystem::GetCount((RoleSystem *)g_SceneMgr.m_pCollisionNode);
                        flt_58B238 = (float)(rand() % 30 + 30);
                      }
                      return;
                    }
                  }
                  else
                  {
                    pOut[0].x = *(float *)(g_Input.KeyInfo[177].CountMode + 504);
                    pOut[0].y = *(float *)(g_Input.KeyInfo[177].CountMode + 508);
                    v37 = *(float *)(g_Input.KeyInfo[177].CountMode + 512);
                    pOut[0].y = 0.0;
                    pOut[0].z = v37;
                    gbVec3D::Normalize(pOut);
                    v31 = 2;
                    v12 = 3;
                    a2.x = a2.x - pOut[0].x;
                    a2.y = a2.y - pOut[0].y;
                    a2.z = a2.z - pOut[0].z;
                  }
                }
                else
                {
                  pOut[0].x = *(float *)(g_Input.KeyInfo[177].CountMode + 504);
                  pOut[0].y = *(float *)(g_Input.KeyInfo[177].CountMode + 508);
                  v35 = *(float *)(g_Input.KeyInfo[177].CountMode + 512);
                  pOut[0].y = 0.0;
                  pOut[0].z = v35;
                  gbVec3D::Normalize(pOut);
                  v31 = 2;
                  v12 = 3;
                  a2.x = pOut[0].x + a2.x;
                  a2.y = a2.y + pOut[0].y;
                  a2.z = a2.z + pOut[0].z;
                }
                RoleSystem::GetActiveRole((RoleSystem *)g_SceneMgr.m_pCollisionNode);
                if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1284) == 2 )
                  v31 = 2;
                RoleSystem::GetPosition((RoleSystem *)g_SceneMgr.m_pCollisionNode, &a2, v31);
LABEL_166:
                *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1264) = v12;
                flt_C116F8[0] = 0.0;
                return;
              }
              a2.x = -*(float *)(g_Input.KeyInfo[177].CountMode + 528);
              a2.y = -*(float *)(g_Input.KeyInfo[177].CountMode + 532);
              a2.z = -*(float *)(g_Input.KeyInfo[177].CountMode + 536);
            }
            else
            {
              a2.x = *(float *)(g_Input.KeyInfo[177].CountMode + 528);
              a2.y = *(float *)(g_Input.KeyInfo[177].CountMode + 532);
              a2.z = *(float *)(g_Input.KeyInfo[177].CountMode + 536);
            }
            v31 = 2;
            goto LABEL_176;
          }
          RoleSystem::MoveRole((RoleSystem *)g_SceneMgr.m_pCollisionNode, &a2.x, SLODWORD(pDist), 2, v26);
          v30 = *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628);
          if ( LODWORD(pDist) != v30
            && !*(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1268)
            && Camera::CheckCollision2(&g_SceneMgr._gap_cd10[912], v30, &a2) )
          {
            a2.y = 0.0;
            RoleSystem::MoveRole(
              (RoleSystem *)g_SceneMgr.m_pCollisionNode,
              &a2.x,
              *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628),
              2,
              1);
          }
        }
        v12 = 2;
        goto LABEL_145;
      }
      if ( v14 )
      {
        pOut[0].x = *(float *)(g_SceneMgr.m_pCollisionNode + 160) - v15[10];
        v17 = *(float *)(g_SceneMgr.m_pCollisionNode + 164) - v15[11];
        a2.x = pOut[0].x;
        pOut[0].y = v17;
        v18 = *(float *)(g_SceneMgr.m_pCollisionNode + 168) - v15[12];
        a2.y = pOut[0].y;
        pOut[0].z = v18;
        a2.z = pOut[0].z;
        v43 = gbVec3D::Length(&a2);
        pOut[0].x = *(float *)(g_SceneMgr.m_pCollisionNode + 160) - *(float *)(v14 + 160);
        v19 = *(float *)(g_SceneMgr.m_pCollisionNode + 164) - *(float *)(v14 + 164);
        a2.x = pOut[0].x;
        pOut[0].y = v19;
        v20 = *(float *)(g_SceneMgr.m_pCollisionNode + 168) - *(float *)(v14 + 168);
        a2.y = pOut[0].y;
        pOut[0].z = v20;
        a2.z = pOut[0].z;
        v21 = gbVec3D::Length(&a2);
        if ( v21 < v43 )
        {
LABEL_89:
          v16 = 0;
          goto LABEL_90;
        }
        v14 = 0;
      }
      if ( *(_BYTE *)(v16 + 173) )
      {
        v22 = *(_BYTE *)(v16 + 244);
        if ( v22 != 14 || *(unsigned __int8 *)(v16 + 246) == *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628) )
        {
          v23 = v22 == 11
             || v22 == 12
             || v22 == 14
             || v22 == 15
             || v22 == 16
             || v22 == 20
             || v22 == 23
             || v22 == 24
             || v22 == 26
             || v22 == 27
             || v22 == 42
             || v22 == 41;
          if ( v22 == 26 && (*(_BYTE *)(v16 + 80) || *(_BYTE *)(v16 + 81) >= 3u) )
            v23 = 0;
          if ( (v22 != 23 || *(_BYTE *)(v16 + 174) && *(_DWORD *)(v16 + 252) != 1) && v23 )
            goto LABEL_90;
        }
      }
      goto LABEL_89;
    }
  }
}

// 0x0041EB80
// between_std_methods (0x411BB0-0x430790)
void __thiscall UIPostUpdate(void *_this)
{
  RoleSystem *v1; // eax
  int RolePtr; // esi
  int v3; // edi
  __int64 v4; // rax
  int v5; // ecx
  int v6; // edi
  gbSound2DNode *v7; // esi
  int v8; // [esp-8h] [ebp-10h]

  if ( g_SceneMgr.m_pCollisionNode )
  {
    v8 = *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628);
    v1 = (RoleSystem *)UISceneUpdate();
    RolePtr = RoleSystem::GetRolePtr(v1, v8);
    v3 = (__int64)((*(float *)(g_SceneMgr.m_pCollisionNode + 4) - *(float *)(RolePtr + 128))
                 / *(float *)&g_SceneMgr._gap_cd10[1572]);
    v4 = (__int64)((*(float *)(g_SceneMgr.m_pCollisionNode + 12) - *(float *)(RolePtr + 136))
                 / *(float *)&g_SceneMgr._gap_cd10[1572]);
    if ( v3 < 0 || (v5 = *(_DWORD *)(RolePtr + 152), v3 >= v5) || (int)v4 < 0 || (int)v4 >= *(_DWORD *)(RolePtr + 156) )
    {
      v6 = 2;
    }
    else
    {
      v6 = *(unsigned __int8 *)(*(_DWORD *)(RolePtr + 160) + 8 * (v3 + v4 * v5) + 5);
      if ( v6 == 6 )
      {
        if ( g_Input.KeyInfo[197].HoldTime != 2 )
          ScriptSystem::RunEvent(2, 1, 0);
      }
      else if ( v6 == 10 )
      {
        if ( g_Input.KeyInfo[197].HoldTime )
          ScriptSystem::RunEvent(0, 1, 0);
      }
      else if ( v6 == 13 && g_Input.KeyInfo[197].HoldTime != 3 )
      {
        ScriptSystem::RunEvent(3, 1, 0);
      }
    }
    if ( (g_nGameFlags & 1) != 0 )
    {
      v7 = 0;
      if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1284) )
      {
        if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1284) == 1 )
        {
          v7 = *(gbSound2DNode **)&g_SceneMgr._gap_cd10[4 * sub_41EB50(v6) + 800];
        }
        else if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1284) == 2 )
        {
          v7 = *(gbSound2DNode **)&g_SceneMgr._gap_cd10[4 * sub_41EB50(v6) + 704];
        }
      }
      else
      {
        v7 = 0;
      }
      if ( dword_C116F4 )
      {
        if ( v7 )
        {
          if ( dword_C116F4 != v7 )
          {
            gbSound2DNode::Stop(dword_C116F4);
            dword_C116F4 = v7;
            gbSound2DNode::Play(v7);
          }
        }
        else
        {
          gbSound2DNode::Stop(dword_C116F4);
          dword_C116F4 = 0;
        }
      }
      else if ( v7 )
      {
        dword_C116F4 = v7;
        gbSound2DNode::Play(v7);
      }
    }
  }
}

// 0x0041EEF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_326()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0041F250
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_327()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0041F680
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_328()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00420150
// between_std_methods (0x411BB0-0x430790)
int __userpurge UIUpdate@<eax>(_DWORD *_this@<ecx>, double a2@<st1>, double a3)
{
  int result; // eax
  int v5; // ecx
  int v6; // edi
  _DWORD *v7; // ebx
  int v8; // edi
  double v9; // st7
  _DWORD *v10; // ebx
  float dt; // [esp+10h] [ebp-4h]
  int dta; // [esp+10h] [ebp-4h]

  result = *(_this + 123285);
  if ( result )
  {
    v5 = *(_this + 123284);
    if ( v5 )
      (*(void (__thiscall **)(int))(*(_DWORD *)v5 + 20))(v5);
    result = *(_this + 14392);
    v6 = 0;
    if ( result > 0 )
    {
      v7 = _this + 14393;
      do
      {
        dt = a3;
        ScriptSystem::UpdateTimers(dt);
        result = *(_this + 14392);
        ++v6;
        v7 += 2176;
      }
      while ( v6 < result );
    }
    if ( g_Input.KeyInfo[177].PressTime != 9 )
    {
      result = *(_this + 55);
      v8 = 0;
      if ( result > 0 )
      {
        v9 = a3;
        v10 = _this + 56;
        do
        {
          *(float *)&dta = a3;
          v9 = sub_426EB0(v10, v9, a2, dta);
          result = *(_this + 55);
          ++v8;
          v10 += 224;
        }
        while ( v8 < result );
      }
    }
  }
  return result;
}

// 0x00421830
// between_std_methods (0x411BB0-0x430790)
gbGfxManager *__cdecl GetGfxManager_2()
{
  int v0; // ecx
  int v1; // esi
  gbGfxManager *result; // eax

  v1 = v0;
  result = *(gbGfxManager **)(v0 + 132);
  if ( result && !*(_DWORD *)(v0 + 493144) )
    gbSceneGraph::AddVisNode(*(gbSceneGraph **)(g_Input.KeyInfo[177].Data + 448), (struct gbVisNode *)result);
  *(_DWORD *)(v1 + 493144) = 1;
  return result;
}

// 0x00421870
// between_std_methods (0x411BB0-0x430790)
gbGfxManager *__cdecl GetGfxManager_3()
{
  int v0; // ecx
  int v1; // esi
  gbGfxManager *result; // eax

  v1 = v0;
  result = *(gbGfxManager **)(v0 + 132);
  if ( result && *(_DWORD *)(v0 + 493144) )
    gbSceneGraph::DelVisNode(*(gbSceneGraph **)(g_Input.KeyInfo[177].Data + 448), (struct gbVisNode *)result);
  *(_DWORD *)(v1 + 493144) = 0;
  return result;
}

// 0x00421C40
// between_std_methods (0x411BB0-0x430790)
int __thiscall UINotifyUpdate(int *_this)
{
  __int32 m_pCollisionNode; // ebx
  int v3; // edi
  int *i; // esi

  m_pCollisionNode = g_SceneMgr.m_pCollisionNode;
  v3 = 0;
  if ( *(_this + 14392) <= 0 )
    return 0;
  for ( i = _this + 14393; *((_BYTE *)i + 173) != 4 || !sub_419EF0((int)i, (float *)(m_pCollisionNode + 4)); i += 2176 )
  {
    if ( ++v3 >= *(_this + 14392) )
      return 0;
  }
  return 1;
}

// 0x00422110
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_329()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004224E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_330()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00422560
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
char *unknown_libname_331()
{
  unk_C12B38 = 0;
  unk_C12B3C = 0;
  unk_C12B40 = 0;
  return byte_D8B938;
}

// 0x004226E0
// between_std_methods (0x411BB0-0x430790)
// attributes: thunk
int j_PAL3_422DF0()
{
  return UISystem::Destroy();
}

// 0x004226F0
// between_std_methods (0x411BB0-0x430790)
int UISceneUpdate()
{
  return 493156 * (dword_D8BBEC == 1) + 12722152;
}

// 0x00422E40
// between_std_methods (0x411BB0-0x430790)
void __cdecl EffectUpdate(float a1)
{
  int v1; // eax
  int v2; // ebx
  CScreenMode *Instance; // eax
  int v4; // eax
  int v5; // edi
  _DWORD *v6; // ebp
  int v7; // eax
  _DWORD *v8; // esi
  int v9; // ebx
  __int8 *v10; // ebx
  __int8 *v11; // esi
  int v12; // edi
  int v13; // edi
  _DWORD *v14; // esi
  int i; // esi
  int v16; // eax
  int v17; // [esp+8h] [ebp-8h]
  int v18; // [esp+Ch] [ebp-4h]

  flt_58DE64 = flt_58DE64 + a1;
  if ( dword_C12B3C && !PalScriptMgr::ClearAllScript(dword_C12B3C) )
  {
    if ( (_BYTE)dword_C12B38 == 6 || (_BYTE)dword_C12B38 == 14 )
    {
      sub_418130((_DWORD *)g_SceneMgr.m_pCollisionNode, 0);
      v1 = unk_C12B40;
      if ( *(_DWORD *)(unk_C12B40 + 88) == 3 )
      {
        gbVisNode::SetTimeScale(*(gbVisNode **)(unk_C12B40 + 92), 0.0);
        (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)(unk_C12B40 + 92) + 24))(*(_DWORD *)(unk_C12B40 + 92), 0);
        v1 = unk_C12B40;
      }
      *(_BYTE *)(v1 + 80) = 0;
    }
    dword_C12B38 = 0;
    dword_C12B3C = 0;
    unk_C12B40 = 0;
  }
  v2 = 493156 * (dword_D8BBEC == 1) + 12722152;
  v18 = v2;
  if ( dword_58B230 > 0 )
  {
    Instance = (CScreenMode *)SoundContext::GetInstance();
    if ( CScreenMode::IsAudioReady(Instance) )
    {
      v4 = *(_DWORD *)(v2 + 57568);
      v5 = 0;
      if ( v4 > 0 )
      {
        v6 = (_DWORD *)(v2 + 58204);
        do
        {
          if ( *(v6 - 122) )
          {
            if ( *v6 )
            {
              v7 = v4 - 1;
              if ( v7 > v5 )
              {
                v8 = (_DWORD *)(8704 * v7 + v2 + 57716);
                v9 = v7 - v5;
                do
                {
                  if ( v8[122] && *v8 )
                    sub_416220((int)(v6 - 158), (int)(v8 - 36));
                  v8 -= 2176;
                  --v9;
                }
                while ( v9 );
                v2 = v18;
              }
            }
          }
          v4 = *(_DWORD *)(v2 + 57568);
          ++v5;
          v6 += 2176;
        }
        while ( v5 < v4 );
      }
      if ( dword_D8BBEC != 2 )
      {
        v17 = 0;
        v10 = &g_SceneMgr.m_slot4[840];
        do
        {
          if ( *((_DWORD *)v10 + 158) && *((_DWORD *)v10 + 316) != 4 )
          {
            if ( (int)v10 < (int)&g_SceneMgr._midRegion[26112] )
            {
              v11 = &g_SceneMgr._midRegion[27376];
              v12 = 4 - v17;
              do
              {
                if ( *((_DWORD *)v11 - 158) && *(_DWORD *)v11 != 4 )
                  sub_416220((int)v10, (int)(v11 - 1264));
                v11 -= 8704;
                --v12;
              }
              while ( v12 );
            }
            v13 = 0;
            if ( *(int *)(v18 + 57568) > 0 )
            {
              v14 = (_DWORD *)(v18 + 57716);
              do
              {
                if ( v14[122] && *v14 )
                  sub_416220((int)v10, (int)(v14 - 36));
                ++v13;
                v14 += 2176;
              }
              while ( v13 < *(_DWORD *)(v18 + 57568) );
            }
          }
          v10 += 8704;
          ++v17;
        }
        while ( (int)v10 < (int)&g_SceneMgr.m_pGameData );
        v2 = v18;
      }
      if ( g_SceneMgr.m_pCollisionNode && *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1264) != 4 )
        sub_420B40((float *)v2, (RoleSystem *)g_SceneMgr.m_pCollisionNode, a1, 0);
    }
  }
  if ( dword_D8BBEC != 1 )
  {
    for ( i = 0; i < *(_DWORD *)(v2 + 492772); ++i )
    {
      v16 = sub_423600(i);
      sub_420730(v16, 1);
    }
  }
}

// 0x00423540
// between_std_methods (0x411BB0-0x430790)
int CombatEnter()
{
  int result; // eax

  result = UISceneUpdate();
  if ( *(_DWORD *)(result + 100) != 1
    || (result = UIScene::ProcessInput(aM19, 0), (_BYTE)result)
    || (result = UIScene::ProcessInput(aM20, 0), (_BYTE)result)
    || (result = UIScene::ProcessInput(aM25, 0), (_BYTE)result) )
  {
    *(_DWORD *)(g_Input.KeyInfo[177].Data + 444) = 1060320051;
  }
  else
  {
    result = g_Input.KeyInfo[177].Data;
    *(_DWORD *)(g_Input.KeyInfo[177].Data + 444) = 0;
  }
  return result;
}

// 0x00423630
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_332()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00429CA0
// between_std_methods (0x411BB0-0x430790)
gbActorMgr *__cdecl GetActorMgr()
{
  int v0; // ecx
  _DWORD *v1; // esi
  gbActorMgr *result; // eax
  int (__thiscall ***v3)(_DWORD, int); // ecx
  int (__thiscall ***v4)(_DWORD, int); // ecx

  v1 = (_DWORD *)v0;
  result = (gbActorMgr *)(*(_DWORD *)v0 - 1);
  switch ( *(_DWORD *)v0 )
  {
    case 1:
      result = *(gbActorMgr **)(v0 + 4);
      if ( result )
      {
        gbActorMgr::DestroyActor((gbActorMgr *)g_Input.KeyInfo[177].HoldTime, *(struct gbActor **)(v0 + 4));
        v1[1] = 0;
      }
      goto LABEL_4;
    case 2:
    case 3:
LABEL_4:
      v3 = (int (__thiscall ***)(_DWORD, int))v1[1];
      if ( v3 )
      {
        result = (gbActorMgr *)(**v3)(v3, 1);
        v1[1] = 0;
      }
      goto LABEL_6;
    case 4:
LABEL_6:
      v4 = (int (__thiscall ***)(_DWORD, int))v1[1];
      if ( v4 )
      {
        result = (gbActorMgr *)(**v4)(v4, 1);
        v1[1] = 0;
      }
      break;
    default:
      break;
  }
  *v1 = 0;
  return result;
}

// 0x00429DA0
// between_std_methods (0x411BB0-0x430790)
// attributes: thunk
void __thiscall j_GetActorMgr(struct gbActor **_this)
{
  GetActorMgr();
}

// 0x0042C6E0
// between_std_methods (0x411BB0-0x430790)
gbGfxManager *__cdecl GetGfxManager_4()
{
  int v0; // ecx
  gbGfxManager *result; // eax
  int v2; // [esp+4h] [ebp+4h]

  sub_424570(v0 - 8, *(gbMatrixStack **)(g_Input.KeyInfo[177].Data + 216), v2);
  return result;
}

// 0x0042C8A0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_333()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0042FD70
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_334()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0042FE80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_335()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00430150
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_336()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00431840
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_337()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00431C80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_338()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00431D90
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
Iostream_init *unknown_libname_339()
{
  return Iostream_init::Iostream_init((Iostream_init *)&unk_D8C338);
}

// 0x00431DB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_340()
{
  PalScript::ClearAllWaitObj((PalScript *)&unk_D8C338);
}

// 0x00431DD0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_341()
{
  return PtrArray::Clear(&stru_D8C328);
}

// 0x00431E20
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_342()
{
  LOBYTE(dword_D8C308[1]) = (unsigned int)dword_D8C308 >> 24;
  dword_D8C308[2] = 0;
  dword_D8C308[3] = 0;
  dword_D8C308[4] = 0;
  LOWORD(dword_D8C31C) = 0;
  dword_D8C320 = 0;
  dword_D8C308[0] = 0;
  return dword_D8C308;
}

// 0x00431E70
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_343()
{
  LOBYTE(dword_D8C2E8[1]) = (unsigned int)dword_D8C2E8 >> 24;
  dword_D8C2E8[2] = 0;
  dword_D8C2E8[3] = 0;
  dword_D8C2E8[4] = 0;
  LOWORD(dword_D8C2E8[5]) = 0;
  dword_D8C2E8[6] = 0;
  dword_D8C2E8[0] = 0;
  return dword_D8C2E8;
}

// 0x00431EC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_344()
{
  LOBYTE(dword_D8C2C8[1]) = (unsigned int)dword_D8C2C8 >> 24;
  dword_D8C2C8[2] = 0;
  dword_D8C2C8[3] = 0;
  dword_D8C2C8[4] = 0;
  LOWORD(dword_D8C2C8[5]) = 0;
  dword_D8C2C8[6] = 0;
  dword_D8C2C8[0] = 0;
  return dword_D8C2C8;
}

// 0x00432630
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_345()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00432830
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_346()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004328B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_347()
{
  return PtrArray::Clear(&stru_D8C348);
}

// 0x00434B20
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_348()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00434BA0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
CGameData *unknown_libname_349()
{
  *(_DWORD *)&g_GameData_0._data[52] = 0;
  *(_DWORD *)&g_GameData_0._data[56] = 0;
  *(_DWORD *)&g_GameData_0._data[60] = 0;
  *(_DWORD *)&g_GameData_0._data[64] = 0;
  *(_DWORD *)&g_GameData_0._data[68] = 0;
  *(_DWORD *)&g_GameData_0._data[72] = 0;
  *(_DWORD *)g_GameData_0._data = &off_56AA90;
  *(_DWORD *)&g_GameData_0._data[4] = 0;
  *(_DWORD *)&g_GameData_0._data[8] = 0;
  *(_DWORD *)&g_GameData_0._data[12] = 0;
  *(_DWORD *)&g_GameData_0._data[28] = 1143930880;
  *(_DWORD *)&g_GameData_0._data[16] = 0;
  *(_DWORD *)&g_GameData_0._data[20] = 0;
  *(_DWORD *)&g_GameData_0._data[24] = 0;
  return &g_GameData_0;
}

// 0x00434BC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_350()
{
  sub_41CBC0(&g_GameData_0);
}

// 0x004352D0
// between_std_methods (0x430790-0x445B40)
gbCamera *__cdecl GetCamera_1()
{
  char *String; // esi
  char *v1; // edi
  gbCamera *result; // eax
  float pParams[3]; // [esp+8h] [ebp-Ch] BYREF

  String = PalScript::GetString();
  v1 = PalScript::GetString();
  result = (gbCamera *)PalScript::GetString();
  if ( String && v1 )
  {
    if ( result )
    {
      pParams[0] = *((float *)String + 1);
      pParams[1] = *((float *)v1 + 1);
      pParams[2] = result->OrthoSize;
      return (gbCamera *)CameraCtrl::InitParams((CameraCtrl *)g_Input.KeyInfo[177].CountMode, pParams);
    }
  }
  return result;
}

// 0x00435320
// between_std_methods (0x430790-0x445B40)
gbCamera *__cdecl GetCamera_2()
{
  gbCamera *result; // eax
  char *v1; // eax

  result = (gbCamera *)PalScript::GetString();
  if ( result )
  {
    v1 = sub_434BD0(LOWORD(result->OrthoSize));
    return (gbCamera *)RoleSystem::SetActive((RoleSystem *)g_Input.KeyInfo[177].CountMode, (int)v1);
  }
  return result;
}

// 0x00435350
// between_std_methods (0x430790-0x445B40)
gbCamera *__cdecl GetCamera_3()
{
  gbCamera *result; // eax
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  __int16 OrthoSize_low; // [esp-4h] [ebp-4h]

  result = (gbCamera *)PalScript::GetString();
  if ( result )
  {
    OrthoSize_low = LOWORD(result->OrthoSize);
    v1 = (_DWORD *)UISceneUpdate();
    v2 = sub_421560(v1, OrthoSize_low);
    return (gbCamera *)sub_41C190((_DWORD *)g_Input.KeyInfo[177].CountMode, (int)v2);
  }
  return result;
}

// 0x00435380
// between_std_methods (0x430790-0x445B40)
gbCamera *__cdecl GetCamera_4()
{
  gbCamera *result; // eax

  result = (gbCamera *)PalScript::GetString();
  if ( result )
  {
    result = (gbCamera *)LODWORD(result->OrthoSize);
    *(_DWORD *)(g_Input.KeyInfo[177].CountMode + 448) = result;
  }
  return result;
}

// 0x004353A0
// between_std_methods (0x430790-0x445B40)
gbCamera *__cdecl GetCamera_5()
{
  char *String; // esi
  char *v1; // edi
  gbCamera *result; // eax

  String = PalScript::GetString();
  v1 = PalScript::GetString();
  result = (gbCamera *)PalScript::GetString();
  if ( String && v1 )
  {
    if ( result )
    {
      sub_41CEE0(
        &g_GameData_0,
        g_Input.KeyInfo[177].CountMode,
        *((_DWORD *)String + 1),
        *((_DWORD *)v1 + 1),
        LODWORD(result->OrthoSize));
      sub_434C40((int)&g_GameData_0);
    }
  }
  return result;
}

// 0x00437C30
// between_std_methods (0x430790-0x445B40)
// attributes: thunk
int PAL3::StartHideFight()
{
  return ?StartHideFight@PAL3@@SAXXZ();
}

// 0x004386A0
// attributes: thunk
int j_nullsub_103()
{
  return nullsub_103();
}

// 0x00438FC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_351()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0043A0F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_352()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0043A690
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_353()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0043A700
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_354()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0043BB00
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_355()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0043BC70
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_356()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0043D7C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_357()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0043DC60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_358()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0043DE60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_359()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0043F780
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_360()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004406D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_361()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00441080
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_362()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00442270
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_363()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00442C90
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_364()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00442DA0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_365()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00444EF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_366()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00445970
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_367()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004459E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_368()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00446060
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_369()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00449990
// between_std_methods (0x445B40-0x44BDA0)
// attributes: thunk
int __thiscall UIListBox::SetScrollPos(UIListBox **_this)
{
  return ?SetScrollPos@UIListBox@@QAEXH@Z(_this);
}

// 0x0044A720
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_370()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0044AB10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_371()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0044B9F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_372()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0044E4C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_373()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0044EB10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_374()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0044ED80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
UIWnd *unknown_libname_375()
{
  UIWnd::UIWnd((UIWnd *)&g_GameData);
  sub_44A790((UIWnd *)dword_DBA0D4);
  sub_450A60((int)dword_DBA134);
  sub_451850((int)dword_DBA260);
  `eh vector constructor iterator'(
    byte_DBA830,
    0x160u,
    5,
    (void (__thiscall *)(void *))sub_450320,
    (void (__thiscall *)(void *))sub_450390);
  sub_450DC0((int)&stru_DBAF10);
  UIWnd::ctor_AB90((int)&unk_DBB364);
  `eh vector constructor iterator'(
    byte_DBD8A0,
    0x8E0u,
    6,
    (void (__thiscall *)(void *))sub_44E530,
    (void (__thiscall *)(void *))sub_44E5E0);
  *(_DWORD *)g_GameData._data = &off_56B094;
  unk_DBD894 = 0;
  dword_DBD898 = 16;
  unk_DC0DE0 = 0;
  dword_DC0DE8 = 0;
  byte_DBA25C = 0;
  unk_DBA258 = 0;
  algn_DBA25D[0] = 1;
  return &g_GameData;
}

// 0x0044F4C0
// between_std_methods (0x44BDA0-0x4A7690)
int __thiscall SceneUpdate(int _this, int a2, int a3)
{
  int v4; // ecx
  _BYTE *v5; // ecx
  BOOL v6; // edi
  int result; // eax

  if ( !*(_BYTE *)(_this + 653) )
  {
    if ( *(_BYTE *)(_this + 652) )
    {
      v4 = *(_DWORD *)(_this + 648);
      if ( v4 )
      {
        if ( !(*(int (__thiscall **)(int))(*(_DWORD *)v4 + 4))(v4) )
        {
          *(_BYTE *)(_this + 652) = 1;
          *(_BYTE *)(_this + 653) = 1;
          *(_DWORD *)(_this + 648) = 0;
          CGameData_Load(_this, (CUtil *)0xA);
        }
      }
    }
  }
  if ( *(_DWORD *)(_this + 14536) == 12 )
    (*(void (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(_this + 28176) + 8))(*(_DWORD *)(_this + 28176), a2, a3);
  v5 = *(_BYTE **)(_this + 28184);
  if ( v5 && v5[3829] )
    (*(void (__thiscall **)(_BYTE *, int, int))(*(_DWORD *)v5 + 8))(v5, a2, a3);
  v6 = UIWnd::HitTest((UIWnd *)_this, a2, a3);
  if ( !*(_DWORD *)(_this + 14536)
    && ((*(int (__thiscall **)(int, int, int))(*(_DWORD *)(_this + 3904) + 8))(_this + 3904, a2, a3) || v6) )
  {
    v6 = 1;
  }
  result = (*(int (__thiscall **)(_DWORD, int, bool))(**(_DWORD **)(_this + 14532) + 8))(
             *(_DWORD *)(_this + 14532),
             a2,
             !v6);
  if ( result || v6 )
    return 1;
  return result;
}

// 0x0044F610
// between_std_methods (0x44BDA0-0x4A7690)
int __thiscall CGameData_Load(int _this, CUtil *a2)
{
  CUtil *v2; // ebx
  int result; // eax
  int v5; // ecx
  void *HoldTime; // esi
  ScreenEffect *Instance; // eax
  int v8; // eax
  int (__thiscall ***v9)(_DWORD, _DWORD); // ecx
  int v10; // eax
  int v11; // ecx
  void *Data; // esi

  v2 = a2;
  if ( a2 != (CUtil *)8 || *(_DWORD *)(_this + 14536) || (result = (unsigned __int8)byte_D92785, !byte_D92785) )
  {
    result = *(_DWORD *)(_this + 14536);
    if ( (CUtil *)result != a2 )
    {
      *(_DWORD *)(_this + 14540) = result;
      if ( result == 7 )
        qmemcpy(&dword_D92788, (const void *)sub_523E60(*(_DWORD **)(_this + 14532)), 0x27848u);
      if ( *(_DWORD *)(_this + 14536) == 8 )
        sub_527D40(*(_DWORD *)(_this + 14532), &byte_D92784);
      if ( *(_DWORD *)(_this + 14536) == 9 )
      {
        v5 = *(_DWORD *)(_this + 14532);
        if ( v5 )
          (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v5 + 24))(v5, 1000, 0, 0);
      }
      if ( dword_5A3748 == dword_DC1100 )
      {
        if ( LOBYTE(g_Input.KeyInfo[179].CountMode) )
        {
          HoldTime = (void *)g_Input.KeyInfo[179].HoldTime;
          if ( g_Input.KeyInfo[179].HoldTime )
          {
            sub_534FB0((void **)g_Input.KeyInfo[179].HoldTime);
            operator delete(HoldTime);
            g_Input.KeyInfo[179].HoldTime = 0;
            LOBYTE(g_Input.KeyInfo[179].CountMode) = 0;
            dword_5A3748 = 1;
            dword_DC1100 = 0;
          }
        }
      }
      if ( a2 != (CUtil *)10 || *(_BYTE *)(_this + 652) )
      {
        v10 = *(_DWORD *)(_this + 14536);
        *(_BYTE *)(_this + 652) = 0;
        if ( v10 != 6 )
        {
          if ( v10 )
          {
            if ( v10 != 5 && v10 != 12 && v10 != 10 )
            {
              v11 = *(_DWORD *)(_this + 14532);
              if ( v11 )
              {
                (*(void (__thiscall **)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
                *(_DWORD *)(_this + 14532) = 0;
              }
            }
          }
        }
        if ( *(_DWORD *)(_this + 14536) == 10 )
        {
          Data = (void *)g_Input.KeyInfo[179].Data;
          if ( g_Input.KeyInfo[179].Data )
          {
            sub_52B2A0((void ***)g_Input.KeyInfo[179].Data);
            operator delete(Data);
            g_Input.KeyInfo[179].Data = 0;
          }
        }
        result = (int)sub_44F8D0((int *)_this, (int)a2);
        *(_DWORD *)(_this + 14532) = result;
        *(_DWORD *)(_this + 14536) = a2;
      }
      else
      {
        Instance = ScreenEffectMgr::GetInstance();
        v8 = sub_4BE1A0((int)Instance, 1);
        v9 = *(int (__thiscall ****)(_DWORD, _DWORD))(_this + 28176);
        *(_DWORD *)(_this + 648) = v8;
        result = (**v9)(v9, 0);
        v2 = *(CUtil **)(_this + 14536);
        *(_BYTE *)(_this + 652) = 1;
        *(_BYTE *)(_this + 653) = 0;
        g_Input.KeyInfo[177].PressTime = 1;
      }
    }
    switch ( (unsigned int)v2 )
    {
      case 0u:
        g_Input.KeyInfo[177].PressTime = 2;
        result = CombatEnter();
        break;
      case 6u:
        g_Input.KeyInfo[177].PressTime = 3;
        break;
      case 9u:
      case 0xDu:
      case 0xEu:
        g_Input.KeyInfo[177].PressTime = 1;
        break;
      case 0xAu:
        g_Input.KeyInfo[177].PressTime = 4;
        break;
      case 0xBu:
        g_Input.KeyInfo[177].PressTime = 5;
        break;
      case 0xCu:
        g_Input.KeyInfo[177].PressTime = 6;
        break;
      case 0xFu:
        g_Input.KeyInfo[177].PressTime = 9;
        result = CombatEnter();
        break;
      default:
        break;
    }
    if ( *(_DWORD *)(_this + 408) )
      result = (**(int (__thiscall ***)(int, _DWORD))(_this + 356))(_this + 356, 0);
    if ( *(_DWORD *)(_this + 14536) == 14 )
    {
      result = *(_DWORD *)(_this + 14532);
      dword_DC10FC = result;
    }
    else
    {
      dword_DC10FC = 0;
    }
  }
  return result;
}

// 0x0044FF70
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_376()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004502B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_377()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00450690
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_378()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004509F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_379()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00450D50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_380()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004517D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_381()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00451C40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_382()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00452510
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_383()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00452720
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_384()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00452F60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_385()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00453CA0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_386()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004547C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_387()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00456A40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_388()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00457230
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_389()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00459000
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_390()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0045A740
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_391()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0046D0D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_392()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004709F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_393()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00478810
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_394()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00478BD0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_395()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00479290
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_396()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0047BB80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_397()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0047C520
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_398()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0047DC30
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_399()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0047E540
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_400()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00482E60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_401()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00486780
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_402()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00490980
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_403()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004987B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_404()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004A1280
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_405()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004A1DD0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_406()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004A66C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_407()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004AFD50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_408()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B45B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_409()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B4620
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_410()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B6390
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_411()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B64E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_412()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B65E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_413()
{
  operator delete(dword_DE6A40);
  dword_DE6A40 = 0;
  unk_DE6A44 = 0;
  unk_DE6A48 = 0;
}

// 0x004B6BF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_414()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B6CB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_415()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B6D70
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_416()
{
  nullsub_3(dword_DE6CD8);
}

// 0x004B6F40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_417()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B7050
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_418()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B7260
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_419()
{
  sub_4B70B0(&dword_DE6F70);
}

// 0x004B7270
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_420()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B7430
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_421()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B7BC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_422()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004B81D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_423()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BC6F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_424()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BD800
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_425()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BD9F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_426()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BDB50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_427()
{
  RenderTarget::RenderTarget((RenderTarget *)dword_DE7AA0);
}

// 0x004BDEE0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_428()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BDF80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_429()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BE460
// between_std_methods (0x4A7690-0x4BEF50)
int __thiscall RenderPost(int _this, int a2)
{
  int result; // eax

  result = *(_DWORD *)(_this + 148);
  if ( result )
    return (*(int (__thiscall **)(_DWORD, int))(***(_DWORD ***)(_this + 116) + 20))(**(_DWORD **)(_this + 116), a2);
  return result;
}

// 0x004BE5D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_430()
{
  sub_4BE080((void ***)&stru_DE7DF8);
}

// 0x004BE860
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_431()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BE9F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_432()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BEB40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_433()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BEC90
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_434()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BEDF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_435()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BF6F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_436()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004BFD60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_437()
{
  nullsub_3(dword_DE8B40);
}

// 0x004C0200
// between_std_methods (0x4BEF50-0x4C0620)
void __thiscall CRenderTarget2_Update(float *_this, float a2)
{
  int v3; // eax
  double v4; // st7
  int v5; // eax
  double v6; // st7
  double v7; // st6
  float v8; // eax
  int v9; // eax
  int v10; // ecx
  long double v11; // st5
  long double v12; // st5
  double v13; // st4
  float v14; // [esp+14h] [ebp-10h]
  int v15; // [esp+14h] [ebp-10h]
  float v16; // [esp+18h] [ebp-Ch]
  int v17; // [esp+1Ch] [ebp-8h]
  float v18; // [esp+1Ch] [ebp-8h]
  float v19; // [esp+20h] [ebp-4h]

  if ( *(_BYTE *)_this )
  {
    v3 = *((_DWORD *)_this + 2);
    if ( v3 )
    {
      v4 = a2 * 0.40000001;
      a2 = 0.0;
      *(_this + 5) = v4 + *(_this + 5);
      if ( (*(int (__stdcall **)(int, _DWORD, _DWORD, float *, _DWORD))(*(_DWORD *)v3 + 44))(v3, 0, 0, &a2, 0) >= 0 )
      {
        v5 = *((_DWORD *)_this + 4);
        if ( v5 )
        {
          if ( v5 == 1 )
          {
            v14 = 1.0;
            if ( !*CRenderTarget::GetInstance() )
              v14 = 0.75;
            v6 = 0.0;
            v7 = v14 * 0.1;
            v8 = v14;
            v15 = 0;
            v16 = v8;
            v9 = 0;
            do
            {
              v10 = 0;
              v17 = 0;
              do
              {
                ++v10;
                v9 += 28;
                v6 = v6 + 0.1;
                v11 = ((double)v17 * 0.1 - 0.5 + (double)v15 * 0.1 - 0.5) * 12.566371 + *(_this + 5) * 4.0;
                v18 = cos(v11) * 0.0099999998;
                v12 = sin(v11) * 0.0099999998;
                *(float *)(v9 + LODWORD(a2) - 16) = (v12 + v18) * 0.5 + v6;
                v13 = v18 + v16;
                v17 = v10;
                *(float *)(v9 + LODWORD(a2) - 12) = v13 - v12;
              }
              while ( v10 < 10 );
              v6 = 0.0;
              ++v15;
              v19 = v7;
              v16 = v16 - v19;
            }
            while ( v9 < 2800 );
          }
          (*(void (__stdcall **)(_DWORD))(**((_DWORD **)_this + 2) + 48))(*((_DWORD *)_this + 2));
        }
        else
        {
          if ( *(_this + 5) > 2.0 )
            *(_this + 5) = *(_this + 5) - 2.0;
          *(_DWORD *)(LODWORD(a2) + 12) = 0;
          *(float *)(LODWORD(a2) + 16) = *(_this + 5) * 0.5 + 1.0;
          *(_DWORD *)(LODWORD(a2) + 40) = 0;
          *(float *)(LODWORD(a2) + 44) = *(_this + 5) * 0.5;
          *(_DWORD *)(LODWORD(a2) + 68) = 1065353216;
          *(float *)(LODWORD(a2) + 72) = *(_this + 5) * 0.5;
          *(_DWORD *)(LODWORD(a2) + 96) = 1065353216;
          *(float *)(LODWORD(a2) + 100) = *(_this + 5) * 0.5 + 1.0;
          (*(void (__stdcall **)(_DWORD))(**((_DWORD **)_this + 2) + 48))(*((_DWORD *)_this + 2));
        }
      }
    }
  }
}

// 0x004C0450
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_438()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C1520
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_439()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C2000
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_440()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C2790
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_441()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C33D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_442()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C3C40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_443()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C57D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_444()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C5BB0
// between_std_methods (0x4C2840-0x4D70B0)
int __thiscall CombatEffectUpdate(int _this, double a2)
{
  int v3; // edi
  double v4; // st7
  int result; // eax
  double v6; // st7
  _DWORD *v7; // ebx

  v3 = 0;
  v4 = *(float *)(_this + 332) * a2;
  result = *(_DWORD *)(_this + 276);
  *(double *)(_this + 312) = v4;
  v6 = v4 + *(double *)(_this + 320);
  *(double *)(_this + 320) = v6;
  *(float *)(_this + 328) = v6;
  if ( result > 0 )
  {
    v7 = (_DWORD *)(_this + 280);
    do
    {
      (*(void (__thiscall **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)*v7 + 20))(
        *v7,
        *(_DWORD *)(_this + 312),
        *(_DWORD *)(_this + 316));
      result = *(_DWORD *)(_this + 276);
      ++v3;
      ++v7;
    }
    while ( v3 < result );
  }
  return result;
}

// 0x004C6300
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_445()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C6450
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_446()
{
  `eh vector destructor iterator'(byte_DE93EC, 0x60u, 8, gbTexture_D3D::~gbTexture_D3D);
}

// 0x004C6840
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_447()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C8880
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_448()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004C9500
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_449()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004CB310
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_450()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004CD9C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_451()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004CDB70
// between_std_methods (0x4C2840-0x4D70B0)
char __thiscall SceneMgrUpdate(float *_this, float a2)
{
  double v2; // st7
  float *v3; // esi
  int v4; // edi
  int v5; // eax

  v2 = a2 - *(_this + 10824);
  *(_this + 10824) = a2;
  v3 = _this + 587;
  *(_this + 10825) = v2;
  v4 = 2048;
  *(_this + 10826) = *(_this + 10826) + *(_this + 10825);
  do
  {
    LOBYTE(v5) = *((_BYTE *)v3 - 4);
    if ( (_BYTE)v5 )
    {
      if ( !*((_BYTE *)v3 - 3) )
        (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)v3 + 20))(*(_DWORD *)v3, LODWORD(a2));
      LOBYTE(v5) = *((_BYTE *)v3 - 4);
      if ( (_BYTE)v5 )
      {
        v5 = *(_DWORD *)v3;
        if ( *(_BYTE *)(*(_DWORD *)v3 + 8) )
          *((_BYTE *)v3 - 3) = 1;
      }
    }
    v3 += 5;
    --v4;
  }
  while ( v4 );
  return v5;
}

// 0x004CFC40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_452()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D0C60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_453()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D0CB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_454()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D31F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_455()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D3830
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_456()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D4DB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_457()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D4E00
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_458()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D4E30
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_459()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D5820
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_460()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D5870
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_461()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D5A40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_462()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D6600
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_463()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D6E30
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_464()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004D6FE0
// between_std_methods (0x4C2840-0x4D70B0)
// attributes: thunk
int CCBAI::CCBAI()
{
  return ??0CCBAI@@QAE@PAVCCBSystem@@@Z();
}

// 0x004DB240
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_465()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004DBF10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_466()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004DF460
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_467()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004E0080
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_468()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004E0A30
INT_PTR __stdcall DialogFunc(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  return sub_4E0A60((void *)dword_17A94E0, hDlg, a2, a3, a4);
}

// 0x004EC430
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_469()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x004FB750
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_470()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00503D50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_471()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00504E20
// attributes: thunk
char __thiscall std::codecvt_base::do_always_noconv(std::codecvt_base *_this)
{
  return ?do_always_noconv@codecvt_base@std@@MBE_NXZ_0(_this);
}

// 0x00505400
// attributes: thunk
char __thiscall j_std::codecvt_base::do_always_noconv(std::codecvt_base *_this)
{
  return std::codecvt_base::do_always_noconv(_this);
}

// 0x00508160
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_472()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00509020
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_473()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0050FAB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_474()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00511BD0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_475()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x005122B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_476()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00515E10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_477()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0051D550
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_478()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0051D6A0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_479()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00521FC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_480()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x005230C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_481()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00523EC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_482()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00524970
// between_std_methods (0x504E20-0x53C2B0)
// attributes: thunk
int __thiscall UIListBox::SetScroll(UIListBox *_this)
{
  return ?SetScroll@UIListBox@@QAEXPBDAAUtagRECT@@HH_N@Z(_this);
}

// 0x005250B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_483()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x005278E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_484()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00528270
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_485()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00529580
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_486()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0052AE80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_487()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0052B170
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_488()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0052B900
// between_std_methods (0x504E20-0x53C2B0)
int __thiscall MiniGame1Update(_DWORD ***_this, double a2)
{
  Actor **v3; // esi
  int v4; // ebx
  float v6; // [esp+0h] [ebp-4h]

  v6 = a2;
  v3 = (Actor **)(_this + 6);
  v4 = 5;
  do
  {
    Object3D::CaculateRelative((int)(v3 - 2), v6);
    if ( sub_537060((gbVisNode **)*v3) == 1 )
      Actor::CompareAction(*v3, (int)v3[35], 0);
    v3 += 38;
    --v4;
  }
  while ( v4 );
  Object3D::CaculateRelative((int)(_this + 214), v6);
  ObjectCamera::SetStepRotate((int)*(_this + 3));
  return sub_52B030(*_this, a2);
}

// 0x0052B9A0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_489()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0052D740
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_490()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0052D770
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *__thiscall unknown_libname_491(_DWORD *_this)
{
  *_this = 0;
  *(_this + 1) = 0;
  *(_this + 2) = 0;
  return _this;
}

// 0x0052DCF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_492()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0052EC20
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_493()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0052F350
// between_std_methods (0x504E20-0x53C2B0)
void __thiscall MiniGame2Update(_DWORD **_this, int a2)
{
  int v3; // ecx
  char *v4; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v6; // esi
  char *v7; // eax
  char *v8; // eax
  ScreenEffect *Instance; // eax
  double v10; // st7
  char v11; // al
  _DWORD *v12; // ecx
  _DWORD *v13; // edx
  unsigned int v14; // ecx
  float *v15; // eax
  unsigned int v16; // edx
  double v17; // st7
  double v18; // st6
  float v19; // [esp+14h] [ebp+4h]

  PalScriptMgr::RunSceneScript(a2);
  if ( *((_BYTE *)_this + 24) )
  {
    v3 = (int)*(_this + 5);
    if ( v3 && !(*(int (__thiscall **)(int))(*(_DWORD *)v3 + 4))(v3) )
    {
      sub_52F570(aSoftwareSoftst, (DWORD)aSGameC, 1);
      CGameData_Load((int)&g_GameData, (CUtil *)*(_this + 75));
      if ( *(_this + 75) )
      {
        Instance = ScreenEffectMgr::GetInstance();
        sub_4BE1A0((int)Instance, 2);
      }
      else
      {
        PalScriptMgr::Destroy(dword_DBA254, 0);
        if ( (g_nGameFlags & 4) != 0 )
        {
          v4 = CScreenMode::GetInstance();
          AudioManager = (gbAudioManager *)CScreenMode::GetAudioManager((CScreenMode *)v4);
          v6 = AudioManager;
          if ( AudioManager )
          {
            gbAudioManager::StopSoundStream(AudioManager, 1);
            gbAudioManager::StopSoundStream(v6, 2);
          }
          if ( CScreenMode::GetInstance()[4] )
          {
            v7 = CScreenMode::GetInstance();
            CScreenMode::AudioFadeOut((CScreenMode *)v7);
          }
          else
          {
            v8 = CScreenMode::GetInstance();
            CScreenMode::AudioStopAll((CScreenMode *)v8);
          }
        }
      }
    }
  }
  else
  {
    if ( *((_BYTE *)_this + 293) )
    {
      v10 = *(float *)&a2;
    }
    else
    {
      if ( *((_BYTE *)_this + 292) )
        *((_BYTE *)_this + 292) = 0;
      (*(_this + 69))[(_DWORD)*(_this + 71)] = a2;
      v11 = *((_BYTE *)_this + 294);
      v12 = (_DWORD *)((char *)*(_this + 71) + 1);
      *(_this + 71) = v12;
      v13 = v12;
      if ( !v11 )
        *((_BYTE *)_this + 294) = v12 >= *(_this + 68);
      v14 = (unsigned int)*(_this + 68);
      *(_this + 70) = 0;
      *(_this + 71) = (unsigned int)v13 < v14 ? v13 : 0;
      if ( v14 )
      {
        v15 = (float *)*(_this + 69);
        v16 = v14;
        do
        {
          v17 = *v15++ + *((float *)_this + 70);
          --v16;
          *((float *)_this + 70) = v17;
        }
        while ( v16 );
      }
      v10 = *((float *)_this + 70) / (double)v14;
    }
    if ( *((_BYTE *)_this + 296) )
    {
      v19 = flt_5F4B9C * v10;
    }
    else if ( *((_BYTE *)_this + 294) )
    {
      v18 = flt_5F4B9C * v10;
      *((_BYTE *)_this + 296) = 1;
      v19 = v18;
    }
    else
    {
      v19 = 1.0;
    }
    sub_52EBE0((gbCamera **)*(_this + 1), SLODWORD(v19));
    sub_531260((gbVisNode ***)*_this, v19);
    sub_5303C0(*(_this + 3), SLODWORD(v19));
    sub_52FE30((int)*(_this + 4), v19);
  }
}

// 0x0052F650
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_494()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00530200
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_495()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x005303D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_496()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00531CB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_497()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x005329D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_498()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00533C40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_499()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00534D50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_500()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00534EE0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_501()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x005353A0
// between_std_methods (0x504E20-0x53C2B0)
void __thiscall MiniGame3Update(int *_this, float a2)
{
  DWORD TickCount; // eax
  DWORD v4; // eax
  unsigned int v5; // edx
  char v6; // al
  unsigned int v7; // ecx
  unsigned int v8; // edx
  unsigned int v9; // ecx
  float *v10; // eax
  unsigned int v11; // edx
  double v12; // st7
  __int128 v13; // [esp-10h] [ebp-2Ch]

  sub_533F50(*(_this + 3), *(float *)(*_this + 192));
  sub_534210(*(_this + 3), *(_DWORD *)(*_this + 168), *(_DWORD *)(*_this + 172), *(_DWORD *)(*_this + 176));
  *(_QWORD *)&v13 = 0;
  *((_QWORD *)&v13 + 1) = 0x43820000BF800000LL;
  sub_534810(*(_this + 3), v13, 168.0);
  if ( *(_BYTE *)(*_this + 216) )
    *((_BYTE *)_this + 36) = 1;
  else
    *((_BYTE *)_this + 37) = 1;
  if ( *((_BYTE *)_this + 36) && *((_BYTE *)_this + 37) )
  {
    sub_534BA0(*(_this + 3), 1086324736, 1086324736, 1086324736, 1091567616, 1070386381, 1, 0);
    if ( !*((_BYTE *)_this + 32) )
    {
      TickCount = GetTickCount();
      *(_this + 6) = TickCount;
      *(_this + 7) = TickCount;
      *((_BYTE *)_this + 32) = 1;
    }
    v4 = GetTickCount();
    v5 = v4 - *(_this + 7);
    *(_this + 6) = v4;
    if ( v5 > 0x3E8 )
    {
      *(_this + 7) = v4;
      *((_BYTE *)_this + 32) = 0;
      sub_534BF0(*(_this + 3));
      *((_BYTE *)_this + 36) = 0;
      *((_BYTE *)_this + 37) = 0;
    }
  }
  if ( !*((_BYTE *)_this + 61) )
  {
    if ( *((_BYTE *)_this + 60) )
      *((_BYTE *)_this + 60) = 0;
    *(float *)(*(_this + 11) + 4 * *(_this + 13)) = a2;
    v6 = *((_BYTE *)_this + 62);
    v7 = *(_this + 13) + 1;
    *(_this + 13) = v7;
    v8 = v7;
    if ( !v6 )
      *((_BYTE *)_this + 62) = v7 >= *(_this + 10);
    v9 = *(_this + 10);
    *(_this + 13) = v8 < v9 ? v8 : 0;
    *(_this + 12) = 0;
    if ( v9 )
    {
      v10 = (float *)*(_this + 11);
      v11 = v9;
      do
      {
        v12 = *((float *)_this + 12) + *v10++;
        --v11;
        *((float *)_this + 12) = v12;
      }
      while ( v11 );
    }
    a2 = *((float *)_this + 12) / (double)v9;
  }
  if ( *((_BYTE *)_this + 62) )
  {
    sub_533250(*(_this + 4), a2);
    sub_534E60((float **)*(_this + 2), COERCE_UNSIGNED_INT64(a2), HIDWORD(COERCE_UNSIGNED_INT64(a2)));
    Actor::SetParam((Actor *)*_this, COERCE_UNSIGNED_INT64(a2));
    sub_5359B0((char *)*(_this + 1), a2);
    sub_534CF0(*(_this + 3), COERCE_UNSIGNED_INT64(a2), HIDWORD(COERCE_UNSIGNED_INT64(a2)));
  }
}

// 0x00535590
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_502()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00535A00
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_503()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x005361F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_504()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00536A10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_505()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00537540
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_506()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x005382D0
// between_std_methods (0x504E20-0x53C2B0)
BOOL __cdecl CheckDirectoryExists(LPCSTR lpFileName)
{
  HANDLE FirstFileA; // eax
  BOOL v3; // esi
  struct _WIN32_FIND_DATAA FindFileData; // [esp+4h] [ebp-140h] BYREF

  FirstFileA = FindFirstFileA(lpFileName, &FindFileData);
  if ( FirstFileA == (HANDLE)-1 )
    return 0;
  v3 = (FindFileData.dwFileAttributes & 0x10) != 0;
  FindClose(FirstFileA);
  return v3;
}

// 0x00539530
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_507()
{
  sub_5375F0((int)&unk_17B1550);
}

// 0x0053C1E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_508()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0053C810
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_509()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0053C8B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_510()
{
  nullsub_3(g_Logger);
}

// 0x0053CB10
// between_std_methods (0x53C2D0-0x541D1B)
int __thiscall WinProc_HWND_53CB10(int _this, char a2)
{
  int result; // eax
  unsigned int v4; // ecx
  _BYTE *v5; // ebx
  int v6; // ecx

  if ( a2 == 96 )
  {
    result = *(_DWORD *)(_this + 4644) == 0;
    *(_DWORD *)(_this + 4644) = result;
  }
  else
  {
    result = *(_DWORD *)(_this + 4644);
    if ( result )
    {
      switch ( a2 )
      {
        case 8:
          result = 0;
          v6 = strlen((const char *)(_this + 4656));
          if ( v6 >= 2 )
          {
            *(_BYTE *)(v6 + _this + 4655) = 0;
            *(_BYTE *)(v6 + _this + 4654) = 95;
          }
          break;
        case 13:
          v5 = (_BYTE *)(_this + 4656);
          *(_BYTE *)(strlen((const char *)(_this + 4656)) + _this + 4655) = 0;
          Logger::Write((Logger *)_this, off_6088D8, _this + 4656);
          WinProc_HWND_53CCF0((char *)_this);
          memset(v5, 0, 0x64u);
          *v5 = 95;
          return 0;
        case 27:
          memset((void *)(_this + 4656), 0, 0x64u);
          *(_BYTE *)(_this + 4656) = 95;
          return 0;
        default:
          result = 0;
          v4 = strlen((const char *)(_this + 4656));
          if ( v4 < 0x63 )
          {
            *(_BYTE *)(v4 + _this + 4655) = a2;
            *(_BYTE *)(v4 + _this + 4656) = 95;
          }
          break;
      }
    }
  }
  return result;
}

// 0x0053CCF0
// between_std_methods (0x53C2D0-0x541D1B)
char *__thiscall WinProc_HWND_53CCF0(char *_this)
{
  char *result; // eax
  char *v3; // eax
  char *v4; // ebp
  int v5; // esi
  const char *i; // edi
  char Str[100]; // [esp+10h] [ebp-64h] BYREF

  if ( *((_DWORD *)_this + 1162) )
  {
    strcpy(Str, _this + 4656);
    v3 = strchr(Str, 32);
    v4 = v3;
    if ( v3 )
    {
      *v3 = 0;
      v4 = v3 + 1;
    }
    v5 = 0;
    if ( *(int *)_this <= 0 )
    {
      return Logger::Write((Logger *)_this, aBadCommandOrFi);
    }
    else
    {
      for ( i = _this + 4; _strcmpi(i, Str); i += 136 )
      {
        if ( ++v5 >= *(_DWORD *)_this )
          return Logger::Write((Logger *)_this, aBadCommandOrFi);
      }
      return (*((char *(__cdecl **)(char *))_this + 34 * v5 + 34))(v4);
    }
  }
  else
  {
    result = (char *)gbCrc32Compute(_this + 4656);
    *((_DWORD *)_this + 1162) = result + 706426632 == 0;
  }
  return result;
}

// 0x0053CDE0
// between_std_methods (0x53C2D0-0x541D1B)
int __thiscall WinProc_HWND_53CDE0(char *_this, char *Source)
{
  char *v3; // esi

  v3 = _this + 4656;
  strncpy(_this + 4656, Source, 0x64u);
  WinProc_HWND_53CCF0(_this);
  memset(v3, 0, 0x64u);
  *v3 = 95;
  return 0;
}

// 0x0053CEC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_511()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0053CF80
// between_std_methods (0x53C2D0-0x541D1B)
FILE *InitLogFiles()
{
  FILE *v0; // esi
  FILE *result; // eax
  FILE *v2; // edi
  CHAR Filename[512]; // [esp+8h] [ebp-200h] BYREF

  v0 = fopen("Pal3Log.txt", aWt);
  result = fopen(aEnginelogTxt, aWt);
  v2 = result;
  if ( v0 )
  {
    if ( result )
    {
      GetModuleFileNameA(0, Filename, 0x200u);
      fprintf(v0, "[%s Log at ", Filename);
      _strdate(Filename);
      fprintf(v0, Filename);
      _strtime(Filename);
      fprintf(v0, " %s]\r\n\r\n", Filename);
      fclose(v0);
      fprintf(v2, "Log At:%s\r\n", Filename);
      return (FILE *)fclose(v2);
    }
  }
  return result;
}

// 0x0053D030
// between_std_methods (0x53C2D0-0x541D1B)
FILE *LogMessage(char *Format, ...)
{
  FILE *result; // eax
  FILE *v2; // esi
  va_list ArgList; // [esp+Ch] [ebp+8h] BYREF

  va_start(ArgList, Format);
  vsprintf(byte_17B3AAC, Format, ArgList);
  result = fopen("Pal3Log.txt", aAt);
  v2 = result;
  if ( result )
  {
    fprintf(result, byte_17B3AAC);
    return (FILE *)fclose(v2);
  }
  return result;
}

// 0x0053D080
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_512()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0053D190
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_513()
{
  sub_53D100((void **)dword_17B3EB0);
}

// 0x0053D1A0
// between_std_methods (0x53C2D0-0x541D1B)
void __thiscall CScreenMode_SetResolution(PtrArray *_this, int a3, int arg4)
{
  if ( a3 )
    PtrArray::SetAt(_this, _this->m_nSize, a3);
  if ( arg4 )
    PtrArray::SetAt(_this + 1, *((_DWORD *)_this + 5), arg4);
}

// 0x0053D330
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_514()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0053DB10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_515()
{
  sub_53D3F0((int)&stru_17B3ED8);
}

// 0x0053DB20
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_516()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0053DF40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
char *unknown_libname_517()
{
  return sub_53DB90(byte_17B41E8);
}

// 0x0053DF60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_518()
{
  sub_53DC50(byte_17B41E8);
}

// 0x0053F1C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_519()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0053F1F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_520()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x0053FE50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_521()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00540F60
// between_std_methods (0x53C2D0-0x541D1B)
gbGfxManager *__cdecl PushMatrixStacks()
{
  gbGfxManager *v0; // ecx
  gbMatrixStack *v1; // esi
  gbGfxManager *v2; // ebx
  gbMatrixStack *v3; // edi

  v1 = *(gbMatrixStack **)(g_Input.KeyInfo[177].Data + 216);
  v2 = v0;
  v3 = *(gbMatrixStack **)(g_Input.KeyInfo[177].Data + 212);
  gbMatrixStack::Push(v1);
  gbMatrixStack::Push(v3);
  gbMatrixStack::LoadIdentity(v1);
  gbMatrixStack::LoadIdentity(v3);
  return v2;
}

// 0x00540FA0
// between_std_methods (0x53C2D0-0x541D1B)
gbGfxManager *__cdecl PopMatrixStacks()
{
  gbMatrixStack *v0; // esi
  gbGfxManager *result; // eax

  v0 = *(gbMatrixStack **)(g_Input.KeyInfo[177].Data + 216);
  gbMatrixStack::Pop(*(gbMatrixStack **)(g_Input.KeyInfo[177].Data + 212));
  gbMatrixStack::Pop(v0);
  return result;
}

// 0x00541590
// between_std_methods (0x53C2D0-0x541D1B)
gbGfxManager *__cdecl UIQuadManager_Reset()
{
  int v0; // ecx
  gbGfxManager *result; // eax
  char v2; // cl
  int v3; // [esp+4h] [ebp+4h]

  result = (gbGfxManager *)v0;
  if ( v3 != *(_DWORD *)(v0 + 12) )
  {
    v2 = *(_BYTE *)(v0 + 29);
    *(_DWORD *)&result[12] = v3;
    if ( !v2 )
      return (gbGfxManager *)(*(int (__thiscall **)(int, _DWORD))(*(_DWORD *)g_Input.KeyInfo[177].Data + 100))(
                               g_Input.KeyInfo[177].Data,
                               *(_DWORD *)&result[4 * v3]);
  }
  return result;
}

// 0x00541630
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_522()
{
  UIRenderQuadFlip((UIQuadManager *)&unk_1894D90);
}

// 0x00541750
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_523()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x005417C0
LRESULT __stdcall fn(int code, WPARAM wParam, int *lParam)
{
  int v3; // eax
  LRESULT result; // eax

  if ( code )
    return CallNextHookEx(0, code, wParam, (LPARAM)lParam);
  switch ( wParam )
  {
    case 0x100u:
    case 0x101u:
    case 0x104u:
    case 0x105u:
      v3 = *lParam;
      if ( *lParam != 91
        && v3 != 92
        && v3 != 93
        && (v3 != 9 || (lParam[2] & 0x20) == 0)
        && (v3 != 27 || (lParam[2] & 0x20) == 0 && (((unsigned __int16)GetKeyState(17) >> 8) & 0x80u) == 0) )
      {
        return CallNextHookEx(0, code, wParam, (LPARAM)lParam);
      }
      result = 1;
      break;
    default:
      return CallNextHookEx(0, code, wParam, (LPARAM)lParam);
  }
  return result;
}

// 0x00541CE0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_524()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  return atexit(nullsub_1);
}

// 0x00541D75
exception *__thiscall std_logic_error_ctor0(exception *_this, _DWORD *a2)
{
  char *v4[4]; // [esp+10h] [ebp-10h] BYREF

  v4[0] = g_SceneMgr.m_szUIString;
  exception::exception(_this, (const char **)v4);
  v4[3] = 0;
  *((_BYTE *)_this + 12) = *(_BYTE *)a2;
  std::string::_Tidy((_DWORD *)_this + 3, 0);
  sub_4307D0((int)_this + 12, a2, 0, 0xFFFFFFFF);
  _this->_m_what = (char *)&vtbl_std_logic_error;
  return _this;
}

// 0x00541DD9
// ?what@runtime_error@@UBEPBDXZ
// doubtful name
_BYTE *__thiscall std_logic_error_vf1_logic_error(_DWORD *_this)
{
  _BYTE *result; // eax

  result = (_BYTE *)*(_this + 4);
  if ( !result )
    return byte_56A634;
  return result;
}

// 0x00541DE6
// between_std_methods (0x541D1B-0x541F47)
void __thiscall __noreturn logic_error_std_vf2(struct exception *_this)
{
  _BYTE pExceptionObject[28]; // [esp+0h] [ebp-1Ch] BYREF

  std_logic_error_ctor1((exception *)pExceptionObject, _this);
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI2_AVlogic_error_std__);
}

// 0x00541E03
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __thiscall unknown_libname_525(_DWORD *_this)
{
  *_this = &vtbl_std_logic_error;
  std::string::_Tidy(_this + 3, 1);
  exception_ctor(_this);
}

// 0x00541E40
_DWORD *__thiscall std_logic_error_vf0_logic_error(_DWORD *Block, char a2)
{
  unknown_libname_525(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00541E5C
exception *__thiscall std_logic_error_ctor1(exception *_this, struct exception *a2)
{
  exception::exception(_this, a2);
  *((_BYTE *)_this + 12) = a2[1]._m_doFree;
  std::string::_Tidy((_DWORD *)_this + 3, 0);
  sub_4307D0((int)_this + 12, &a2[1]._m_doFree, 0, 0xFFFFFFFF);
  _this->_m_what = (char *)&vtbl_std_logic_error;
  return _this;
}

// 0x00541EB9
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __thiscall unknown_libname_526(_DWORD *_this)
{
  *_this = &vtbl_std_logic_error;
  std::string::_Tidy(_this + 3, 1);
  exception_ctor(_this);
}

// 0x00541EF6
void __thiscall __noreturn std_length_error_vf2_length_error(struct exception *_this)
{
  _BYTE pExceptionObject[28]; // [esp+0h] [ebp-1Ch] BYREF

  std_length_error_ctor((exception *)pExceptionObject, _this);
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}

// 0x00541F13
_DWORD *__thiscall std_length_error_vf0_logic_error(_DWORD *Block, char a2)
{
  unknown_libname_526(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00541F2F
exception *__thiscall std_length_error_ctor(exception *_this, struct exception *a2)
{
  std_logic_error_ctor1(_this, a2);
  _this->_m_what = (char *)&vtbl_std_length_error;
  return _this;
}

// 0x00541FA1
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __thiscall unknown_libname_527(_DWORD *_this)
{
  *_this = &vtbl_std_logic_error;
  std::string::_Tidy(_this + 3, 1);
  exception_ctor(_this);
}

// 0x00541FDE
void __thiscall __noreturn std_out_of_range_vf2_out_of_range(struct exception *_this)
{
  _BYTE pExceptionObject[28]; // [esp+0h] [ebp-1Ch] BYREF

  std_out_of_range_ctor((exception *)pExceptionObject, _this);
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}

// 0x00541FFB
_DWORD *__thiscall std_out_of_range_vf0_logic_error(_DWORD *Block, char a2)
{
  unknown_libname_527(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00542017
exception *__thiscall std_out_of_range_ctor(exception *_this, struct exception *a2)
{
  std_logic_error_ctor1(_this, a2);
  _this->_m_what = (char *)&vtbl_std_out_of_range;
  return _this;
}

// 0x0054202F
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_528()
{
  if ( (byte_189598E & 1) == 0 )
    byte_189598E |= 1u;
  sub_542059();
  if ( (byte_189598F & 1) == 0 )
    byte_189598F |= 1u;
  return atexit(nullsub_96);
}

// 0x0055507C
void __noreturn start()
{
  DWORD Version; // eax
  int v1; // eax
  HMODULE ModuleHandleA; // eax
  int v3; // [esp-4h] [ebp-78h]
  CHAR *lpCmdLine; // [esp+10h] [ebp-64h]
  int v5; // [esp+14h] [ebp-60h]
  _DWORD StartupInfo[17]; // [esp+18h] [ebp-5Ch] BYREF
  CPPEH_RECORD ms_exc; // [esp+5Ch] [ebp-18h]

  Version = GetVersion();
  dword_1895354 = BYTE1(Version);
  dword_1895350 = (unsigned __int8)Version;
  dword_189534C = BYTE1(Version) + ((unsigned __int8)Version << 8);
  dword_1895348 = HIWORD(Version);
  if ( !_heap_init(0) )
    fast_error_exit(0x1Cu);
  ms_exc.registration.TryLevel = 0;
  _ioinit();
  dword_1896D10 = (int)GetCommandLineA();
  Str = __crtGetEnvironmentStringsA();
  _setargv();
  _setenvp();
  _cinit();
  StartupInfo[11] = 0;
  GetStartupInfoA((LPSTARTUPINFOA)StartupInfo);
  lpCmdLine = _wincmdln();
  if ( (StartupInfo[11] & 1) != 0 )
    v1 = LOWORD(StartupInfo[12]);
  else
    v1 = 10;
  v3 = v1;
  ModuleHandleA = GetModuleHandleA(0);
  v5 = WinMain(ModuleHandleA, 0, lpCmdLine, v3);
  exit(v5);
}

// 0x005551BB
void *__thiscall exception_vf0(void *Block, char a2)
{
  exception_ctor(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0055525E
void __thiscall exception_ctor(void *_this)
{
  bool v1; // zf

  v1 = *((_DWORD *)_this + 2) == 0;
  *(_DWORD *)_this = &vtbl_exception;
  if ( !v1 )
    operator delete(*((void **)_this + 1));
}

// 0x005577E1
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int __cdecl unknown_libname_529(_DWORD **a1)
{
  if ( **a1 == -529697949 )
    sub_557C4C();
  return 0;
}

// 0x00557B6C
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int __cdecl unknown_libname_530(int a1)
{
  int result; // eax
  int v2; // ecx

  result = a1;
  if ( a1 )
  {
    v2 = *(_DWORD *)(*(_DWORD *)(a1 + 28) + 4);
    if ( v2 )
      return sub_553108(*(_DWORD *)(a1 + 24), v2);
  }
  return result;
}

// 0x00558C89
void chsifnegret()
{
  ;
}

// 0x005592F0
double __usercall fFYTOX@<st0>(int a1@<ebp>, char a2@<ch>, long double a3@<st1>, long double a4@<st0>)
{
  double result; // st7
  long double v6; // st6
  long double v7; // st7
  long double v8; // st7
  char v9; // dl
  char v10; // ch
  long double v11; // st6
  int v12; // eax

  *(_BYTE *)(a1 - 144) = -2;
  if ( !a2 )
  {
    v6 = a4;
    v7 = a3;
fFXTOY:
    v8 = __FYL2X__(v6, v7);
    _ffexpm1(a2, a1);
    v11 = v6 + 1.0;
    if ( (*(_BYTE *)(a1 - 159) & 1) != 0 )
    {
      if ( dword_1895310 == 1 )
        unknown_libname_544(v11, v8);
      else
        v11 = 1.0 / v11;
    }
    if ( (v9 & 0x40) == 0 )
      v11 = __FSCALE__(v11, v8);
    if ( v10 )
      return -v11;
    return v11;
  }
  isintTOS(a4);
  if ( v12 )
  {
    a2 = 0;
    if ( v12 != 2 )
      a2 = -1;
    v7 = a3;
    v6 = fabs(a4);
    goto fFXTOY;
  }
  result = *(double *)&tbyte_60AF20;
  if ( *(char *)(a1 - 144) > 0 )
    JUMPOUT(0x558C80);
  _rttosnpopde(a1);
  return result;
}

// 0x005593A9
long double __usercall fFLOGm@<st0>(char a1@<cl>, long double a2@<st0>)
{
  if ( a1 )
    JUMPOUT(0x559363);
  return __FYL2X__(a2, 0.3010299956639811952);
}

// 0x005593D7
void zerotoxdone()
{
  ;
}

// 0x005593F2
// positive sp value has been detected, the output may be wrong!
void tranzeropop()
{
  __asm { fstp    st }
  __asm
  {
    fstp    st
    fldz
  }
}

// 0x005593F9
void tranindfpop()
{
  __asm { fstp    st }
  JUMPOUT(0x558C68);
}

// 0x005594B7
void notanint()
{
  isintTOSret();
}

// 0x005594BE
void evenint()
{
  isintTOSret();
}

// 0x0055C5C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
double __cdecl unknown_libname_531(_TBYTE a1, _TBYTE a2)
{
  double v2; // st7
  double v3; // st6
  unsigned int v4; // eax

  v2 = *(double *)&a2;
  v3 = *(double *)&a1;
  while ( !__CFADD__(DWORD1(a1), DWORD1(a1)) )
  {
    if ( !*(_QWORD *)&a1 || (HIWORD(a1) & 0x7FFF) != 0 )
      return v2 / v3;
    if ( (HIWORD(a2) & 0x7FFF) != 0 )
    {
      if ( (HIWORD(a2) & 0x7FFF) == 0x7FFF || !__CFADD__(DWORD1(a2), DWORD1(a2)) )
        return v2 / v3;
    }
    else if ( __CFADD__(DWORD1(a2), DWORD1(a2)) )
    {
      return v2 / v3;
    }
    *(double *)&a1 = v3 * flt_60B728;
    v2 = *(double *)&a2;
  }
  v4 = (2 * DWORD1(a1)) ^ 0xE000000;
  if ( (v4 & 0xE000000) != 0 )
    return v2 / v3;
  if ( !byte_60B710[v4 >> 28] )
    return v2 / v3;
  if ( (HIWORD(a1) & 0x7FFF) == 0 || (HIWORD(a1) & 0x7FFF) == 0x7FFF )
    return v2 / v3;
  if ( (HIWORD(a2) & 0x7FFF) == 1 )
    return v2 * flt_60B724 / (v3 * flt_60B724);
  else
    return v2 * flt_60B720 / (v3 * flt_60B720);
}

// 0x0055C6D7
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
// positive sp value has been detected, the output may be wrong!
void __usercall unknown_libname_532(char a1@<al>)
{
  _TBYTE v1; // [esp-2Ch] [ebp-58h]
  _TBYTE v2; // [esp-20h] [ebp-4Ch]
  _TBYTE v17; // [esp+0h] [ebp-2Ch]
  _TBYTE v18; // [esp+Ch] [ebp-20h]

  switch ( a1 & 0x3F )
  {
    case 0:
      __asm { fdiv    st, st; jumptable 0055C6DD case 0 }
      return;
    case 1:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_4;
    case 2:
LABEL_4:
      __asm { fdivr   st, st; jumptable 0055C6DD case 2 }
      return;
    case 3:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_6;
    case 4:
LABEL_6:
      __asm { fdiv    st, st; jumptable 0055C6DD case 4 }
      return;
    case 5:
      __asm { fdivp   st, st; jumptable 0055C6DD case 5 }
      return;
    case 6:
      __asm { fdivr   st, st; jumptable 0055C6DD case 6 }
      return;
    case 7:
      __asm { fdivrp  st, st; jumptable 0055C6DD case 7 }
      return;
    case 8:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 8
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fld     [esp+2Ch+var_C]
        fxch    st(1)
      }
      return;
    case 9:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_12;
    case 0xA:
LABEL_12:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0055C6DD case 10
        fstp    [esp+arg_8]; _TBYTE
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fld     [esp+arg_8]
        fxch    st(1)
      }
      return;
    case 0xB:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_14;
    case 0xC:
LABEL_14:
      __asm
      {
        fxch    st(1); jumptable 0055C6DD case 12
        fstp    [esp+arg_8]; _TBYTE
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      unknown_libname_531(v17, v18);
      __asm { fld     [esp+arg_1C] }
      return;
    case 0xD:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0055C6DD case 13
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      return;
    case 0xE:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 14
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fld     [esp+2Ch+var_20] }
      return;
    case 0xF:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 15
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      return;
    case 0x10:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 16
        fxch    st(1)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(1)
        fld     [esp+2Ch+var_C]
        fxch    st(2)
      }
      return;
    case 0x11:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_20;
    case 0x12:
LABEL_20:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0055C6DD case 18
        fxch    st(1)
        fstp    [esp+arg_8]; _TBYTE
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(1)
        fld     [esp+arg_8]
        fxch    st(2)
      }
      return;
    case 0x13:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_22;
    case 0x14:
LABEL_22:
      __asm
      {
        fxch    st(2); jumptable 0055C6DD case 20
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(1)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(1)
        fld     [esp+arg_1C]
      }
      return;
    case 0x15:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0055C6DD case 21
        fxch    st(1)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(1) }
      return;
    case 0x16:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 22
        fxch    st(1)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(1)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x17:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 23
        fxch    st(1)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(1) }
      return;
    case 0x18:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 24
        fxch    st(2)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(2)
        fld     [esp+2Ch+var_C]
        fxch    st(3)
      }
      return;
    case 0x19:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_28;
    case 0x1A:
LABEL_28:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0055C6DD case 26
        fxch    st(2)
        fstp    [esp+arg_8]; _TBYTE
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(2)
        fld     [esp+arg_8]
        fxch    st(3)
      }
      return;
    case 0x1B:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_30;
    case 0x1C:
LABEL_30:
      __asm
      {
        fxch    st(3); jumptable 0055C6DD case 28
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(2)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(2)
        fld     [esp+arg_1C]
      }
      return;
    case 0x1D:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0055C6DD case 29
        fxch    st(2)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(2) }
      return;
    case 0x1E:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 30
        fxch    st(2)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(2)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x1F:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 31
        fxch    st(2)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(2) }
      return;
    case 0x20:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 32
        fxch    st(3)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(3)
        fld     [esp+2Ch+var_C]
        fxch    st(4)
      }
      return;
    case 0x21:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_36;
    case 0x22:
LABEL_36:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0055C6DD case 34
        fxch    st(3)
        fstp    [esp+arg_8]; _TBYTE
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(3)
        fld     [esp+arg_8]
        fxch    st(4)
      }
      return;
    case 0x23:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_38;
    case 0x24:
LABEL_38:
      __asm
      {
        fxch    st(4); jumptable 0055C6DD case 36
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(3)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(3)
        fld     [esp+arg_1C]
      }
      return;
    case 0x25:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0055C6DD case 37
        fxch    st(3)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(3) }
      return;
    case 0x26:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 38
        fxch    st(3)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(3)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x27:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 39
        fxch    st(3)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(3) }
      return;
    case 0x28:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 40
        fxch    st(4)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(4)
        fld     [esp+2Ch+var_C]
        fxch    st(5)
      }
      return;
    case 0x29:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_44;
    case 0x2A:
LABEL_44:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0055C6DD case 42
        fxch    st(4)
        fstp    [esp+arg_8]; _TBYTE
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(4)
        fld     [esp+arg_8]
        fxch    st(5)
      }
      return;
    case 0x2B:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_46;
    case 0x2C:
LABEL_46:
      __asm
      {
        fxch    st(5); jumptable 0055C6DD case 44
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(4)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(4)
        fld     [esp+arg_1C]
      }
      return;
    case 0x2D:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0055C6DD case 45
        fxch    st(4)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(4) }
      return;
    case 0x2E:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 46
        fxch    st(4)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(4)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x2F:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 47
        fxch    st(4)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(4) }
      return;
    case 0x30:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 48
        fxch    st(5)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(5)
        fld     [esp+2Ch+var_C]
        fxch    st(6)
      }
      return;
    case 0x31:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_52;
    case 0x32:
LABEL_52:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0055C6DD case 50
        fxch    st(5)
        fstp    [esp+arg_8]; _TBYTE
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(5)
        fld     [esp+arg_8]
        fxch    st(6)
      }
      return;
    case 0x33:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_54;
    case 0x34:
LABEL_54:
      __asm
      {
        fxch    st(6); jumptable 0055C6DD case 52
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(5)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(5)
        fld     [esp+arg_1C]
      }
      return;
    case 0x35:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0055C6DD case 53
        fxch    st(5)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(5) }
      return;
    case 0x36:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 54
        fxch    st(5)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(5)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x37:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 55
        fxch    st(5)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(5) }
      return;
    case 0x38:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 56
        fxch    st(6)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(6)
        fld     [esp+2Ch+var_C]
        fxch    st(7)
      }
      return;
    case 0x39:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_60;
    case 0x3A:
LABEL_60:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0055C6DD case 58
        fxch    st(6)
        fstp    [esp+arg_8]; _TBYTE
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(6)
        fld     [esp+arg_8]
        fxch    st(7)
      }
      return;
    case 0x3B:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_62;
    case 0x3C:
LABEL_62:
      __asm
      {
        fxch    st(7); jumptable 0055C6DD case 60
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(6)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      unknown_libname_531(v17, v18);
      __asm
      {
        fxch    st(6)
        fld     [esp+arg_1C]
      }
      break;
    case 0x3D:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0055C6DD case 61
        fxch    st(6)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(6) }
      break;
    case 0x3E:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 62
        fxch    st(6)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm
      {
        fxch    st(6)
        fld     [esp+2Ch+var_20]
      }
      break;
    case 0x3F:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0055C6DD case 63
        fxch    st(6)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      unknown_libname_531(v1, v2);
      __asm { fxch    st(6) }
      break;
  }
}

// 0x0055CB76
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __usercall unknown_libname_533(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-2Ch]
  _TBYTE v3; // [esp+Ch] [ebp-20h]

  *(double *)&v2 = a1;
  *(double *)&v3 = a2;
  unknown_libname_531(v2, v3);
}

// 0x0055CB89
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __usercall unknown_libname_534(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-2Ch]
  _TBYTE v3; // [esp+Ch] [ebp-20h]

  *(double *)&v3 = a1;
  *(double *)&v2 = a2;
  unknown_libname_531(v2, v3);
}

// 0x0055CB9C
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __userpurge unknown_libname_535(__int16 a1@<fpstat>, double a2@<st1>, double a3@<st0>, float a4)
{
  if ( (LODWORD(a4) & 0x7F800000) != 0x7F800000 )
  {
    if ( (a1 & 0x3800) != 0 )
      unknown_libname_533(a2, a3);
    else
      unknown_libname_533(a4, a2);
  }
}

// 0x0055CBE8
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __userpurge unknown_libname_536(__int16 a1@<fpstat>, double a2@<st1>, double a3@<st0>, double a4)
{
  if ( (HIDWORD(a4) & 0x7FF00000) != 0x7FF00000 )
  {
    if ( (a1 & 0x3800) != 0 )
      unknown_libname_533(a2, a3);
    else
      unknown_libname_533(a4, a2);
  }
}

// 0x0055CC34
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __userpurge unknown_libname_537(__int16 a1@<fpstat>, double a2@<st1>, double a3@<st0>, __int16 a4)
{
  if ( (a1 & 0x3800) != 0 )
    unknown_libname_533(a2, a3);
  else
    unknown_libname_533((double)a4, a2);
}

// 0x0055CC68
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __userpurge unknown_libname_538(__int16 a1@<fpstat>, double a2@<st1>, double a3@<st0>, int a4)
{
  if ( (a1 & 0x3800) != 0 )
    unknown_libname_533(a2, a3);
  else
    unknown_libname_533((double)a4, a2);
}

// 0x0055CC9C
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __userpurge unknown_libname_539(__int16 a1@<fpstat>, double a2@<st1>, double a3@<st0>, float a4)
{
  if ( (LODWORD(a4) & 0x7F800000) != 0x7F800000 )
  {
    if ( (a1 & 0x3800) != 0 )
      unknown_libname_534(a2, a3);
    else
      unknown_libname_534(a4, a2);
  }
}

// 0x0055CCE8
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __userpurge unknown_libname_540(__int16 a1@<fpstat>, double a2@<st1>, double a3@<st0>, double a4)
{
  if ( (HIDWORD(a4) & 0x7FF00000) != 0x7FF00000 )
  {
    if ( (a1 & 0x3800) != 0 )
      unknown_libname_534(a2, a3);
    else
      unknown_libname_534(a4, a2);
  }
}

// 0x0055CD34
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __userpurge unknown_libname_541(__int16 a1@<fpstat>, double a2@<st1>, double a3@<st0>, __int16 a4)
{
  if ( (a1 & 0x3800) != 0 )
    unknown_libname_534(a2, a3);
  else
    unknown_libname_534((double)a4, a2);
}

// 0x0055CD68
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __userpurge unknown_libname_542(__int16 a1@<fpstat>, double a2@<st1>, double a3@<st0>, int a4)
{
  if ( (a1 & 0x3800) != 0 )
    unknown_libname_534(a2, a3);
  else
    unknown_libname_534((double)a4, a2);
}

// 0x0055CD9C
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __usercall unknown_libname_543(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-30h]
  _TBYTE v3; // [esp+Ch] [ebp-24h]

  *(double *)&v2 = a1;
  *(double *)&v3 = a2;
  unknown_libname_531(v2, v3);
}

// 0x0055CDB1
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __usercall unknown_libname_544(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-30h]
  _TBYTE v3; // [esp+Ch] [ebp-24h]

  *(double *)&v3 = a1;
  *(double *)&v2 = a2;
  unknown_libname_531(v2, v3);
}

// 0x0055CDC6
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
unsigned int __usercall unknown_libname_545@<eax>(char a1@<dl>, __int128 a2, int a3, int a4, __int128 a5)
{
  unsigned int result; // eax
  int v6; // ecx
  double v7; // st7
  __int16 v8; // fps
  double v9; // st6
  bool v10; // c0
  char v11; // c2
  bool v12; // c3
  __int16 v13; // fps

  result = *(_DWORD *)((char *)&a2 + 6) ^ 0x700;
  if ( ((*(_DWORD *)((char *)&a2 + 6) ^ 0x700) & 0x700) == 0 )
  {
    result = (result >> 11) & 0xF;
    if ( byte_60B72C[result] )
    {
      result = *(_DWORD *)((_BYTE *)&a2 + 6) & 0x7FFF0000;
      if ( (*(_DWORD *)((_BYTE *)&a2 + 6) & 0x7FFF0000) != 0x7FFF0000 )
      {
        result = *(_DWORD *)((_BYTE *)&a5 + 6) & 0x7FFF0000;
        if ( (*(_DWORD *)((_BYTE *)&a5 + 6) & 0x7FFF0000) != 0 && result != 2147418112 )
        {
          result = 2 * DWORD1(a5);
          if ( !(2 * DWORD1(a5)) )
          {
            result = 2 * DWORD1(a2);
            if ( !(2 * DWORD1(a2)) )
            {
              if ( (WORD4(a5) & 0x7FFFu) > (WORD4(a2) & 0x7FFFu) + 63 )
              {
                v6 = ((BYTE8(a5) - BYTE8(a2)) & 0x3F | 0x20) + 1;
                v7 = fabs(*(long double *)&a2);
                v9 = fabs(*(long double *)&a5);
                do
                {
                  v10 = v9 < v7;
                  v11 = 0;
                  v12 = v9 == v7;
                  result = v8 & 0x100;
                  if ( (v8 & 0x100) == 0 )
                    v9 = v9 - v7;
                  v7 = v7 * dbl_60B75C;
                  --v6;
                }
                while ( v6 );
              }
              else
              {
                while ( 1 )
                {
                  result = (WORD4(a2) & 0x7FFF) + 10;
                  if ( (int)((WORD4(a5) & 0x7FFF) - result) < 0 )
                    break;
                  *(double *)&a5 = __FPREM__(*(long double *)&a5, *(long double *)&a2);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( (a1 & 3) != 0 )
  {
    __asm { fnstenv [esp+28h+var_28] }
    __asm { fldenv  [esp+28h+var_28] }
    return v13 & 0x4300;
  }
  return result;
}

// 0x0055CFCC
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int __usercall __spoils<ecx,st0> unknown_libname_546@<eax>(double a1@<st1>, double a2@<st0>)
{
  int result; // eax
  char v3; // dl
  _BYTE v4[20]; // [esp+0h] [ebp-34h]
  int v5; // [esp+14h] [ebp-20h]
  __int128 v6; // [esp+18h] [ebp-1Ch]

  *(double *)&v6 = a1;
  *(double *)v4 = a2;
  if ( (*(_DWORD *)&v4[6] & 0x7FFF0000) != 0 )
    return unknown_libname_545(0, *(__int128 *)v4, *(int *)&v4[16], v5, v6);
  result = *(_DWORD *)&v4[4] | *(_DWORD *)v4;
  if ( a2 != 0.0 )
  {
    *(double *)&v4[12] = a2;
    v3 = 2;
    if ( (WORD4(v6) & 0x7FFFu) <= 0x7FBE )
    {
      v3 = 3;
      *(double *)&v6 = a1 * dbl_60B744;
    }
    *(double *)v4 = a2 * dbl_60B744;
    return unknown_libname_545(v3, *(__int128 *)v4, HIDWORD(*(unsigned __int64 *)&a2), v5, v6);
  }
  return result;
}

// 0x0055D07E
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
unsigned int __usercall unknown_libname_547@<eax>(char a1@<dl>, __int128 a2, int a3, int a4, __int128 a5)
{
  unsigned int result; // eax
  int v6; // ecx
  double v7; // st7
  __int16 v8; // fps
  double v9; // st6
  bool v10; // c0
  char v11; // c2
  bool v12; // c3
  __int16 v13; // fps

  result = *(_DWORD *)((char *)&a2 + 6) ^ 0x700;
  if ( ((*(_DWORD *)((char *)&a2 + 6) ^ 0x700) & 0x700) == 0 )
  {
    result = (result >> 11) & 0xF;
    if ( byte_60B72C[result] )
    {
      result = *(_DWORD *)((_BYTE *)&a2 + 6) & 0x7FFF0000;
      if ( (*(_DWORD *)((_BYTE *)&a2 + 6) & 0x7FFF0000) != 0x7FFF0000 )
      {
        result = *(_DWORD *)((_BYTE *)&a5 + 6) & 0x7FFF0000;
        if ( (*(_DWORD *)((_BYTE *)&a5 + 6) & 0x7FFF0000) != 0 && result != 2147418112 )
        {
          result = 2 * DWORD1(a5);
          if ( !(2 * DWORD1(a5)) )
          {
            result = 2 * DWORD1(a2);
            if ( !(2 * DWORD1(a2)) )
            {
              if ( (WORD4(a5) & 0x7FFFu) > (WORD4(a2) & 0x7FFFu) + 63 )
              {
                v6 = ((BYTE8(a5) - BYTE8(a2)) & 0x3F | 0x20) + 1;
                v7 = fabs(*(long double *)&a2);
                v9 = fabs(*(long double *)&a5);
                do
                {
                  v10 = v9 < v7;
                  v11 = 0;
                  v12 = v9 == v7;
                  result = v8 & 0x100;
                  if ( (v8 & 0x100) == 0 )
                    v9 = v9 - v7;
                  v7 = v7 * dbl_60B75C;
                  --v6;
                }
                while ( v6 );
              }
              else
              {
                while ( 1 )
                {
                  result = (WORD4(a2) & 0x7FFF) + 10;
                  if ( (int)((WORD4(a5) & 0x7FFF) - result) < 0 )
                    break;
                  *(double *)&a5 = __FPREM__(*(long double *)&a5, *(long double *)&a2);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( (a1 & 3) != 0 )
  {
    __asm { fnstenv [esp+28h+var_28] }
    __asm { fldenv  [esp+28h+var_28] }
    return v13 & 0x4300;
  }
  return result;
}

// 0x0055D284
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int __usercall __spoils<ecx,st0> unknown_libname_548@<eax>(double a1@<st1>, double a2@<st0>)
{
  int result; // eax
  char v3; // dl
  _BYTE v4[20]; // [esp+0h] [ebp-34h]
  int v5; // [esp+14h] [ebp-20h]
  __int128 v6; // [esp+18h] [ebp-1Ch]

  *(double *)&v6 = a1;
  *(double *)v4 = a2;
  if ( (*(_DWORD *)&v4[6] & 0x7FFF0000) != 0 )
    return unknown_libname_547(0, *(__int128 *)v4, *(int *)&v4[16], v5, v6);
  result = *(_DWORD *)&v4[4] | *(_DWORD *)v4;
  if ( a2 != 0.0 )
  {
    *(double *)&v4[12] = a2;
    v3 = 2;
    if ( (WORD4(v6) & 0x7FFFu) <= 0x7FBE )
    {
      v3 = 3;
      *(double *)&v6 = a1 * dbl_60B744;
    }
    *(double *)v4 = a2 * dbl_60B744;
    return unknown_libname_547(v3, *(__int128 *)v4, HIDWORD(*(unsigned __int64 *)&a2), v5, v6);
  }
  return result;
}

// 0x0055D339
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
// attributes: thunk
int __usercall unknown_libname_549@<eax>(double a1@<st1>, double a2@<st0>)
{
  return unknown_libname_546(a1, a2);
}

// 0x0055D33F
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
// attributes: thunk
int __usercall unknown_libname_550@<eax>(double a1@<st1>, double a2@<st0>)
{
  return unknown_libname_548(a1, a2);
}

// 0x0055D345
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
long double __usercall unknown_libname_551@<st0>(long double a1@<st1>, long double a2@<st0>)
{
  return atan2(a2, a1);
}

// 0x0055D348
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void unknown_libname_552()
{
  __asm { fptan }
}

// 0x0055EF80
// attributes: thunk
HRESULT __stdcall DirectInput8Create(
        HINSTANCE hinst,
        DWORD dwVersion,
        const IID *const riidltf,
        LPVOID *ppvOut,
        LPUNKNOWN punkOuter)
{
  return __imp_DirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

// 0x0055EF86
// attributes: thunk
void __stdcall RtlUnwind(PVOID TargetFrame, PVOID TargetIp, PEXCEPTION_RECORD ExceptionRecord, PVOID ReturnValue)
{
  __imp_RtlUnwind(TargetFrame, TargetIp, ExceptionRecord, ReturnValue);
}
