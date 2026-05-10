#include "pal3/ida_defs.h"
#include "pal3/globals.h"

// Free functions (not belonging to any class)

// Forward declarations for unnamed functions
int ArraySort(...);
int CombatEffectUpdate(...);
int EffectUpdate(...);
int ExitProcess(...);
int FileSysInit(...);
int GetCurrentProcess(...);
int HeapCreate(...);
int HeapDestroy(...);
int InputUpdate(...);
int NPCAnimUpdate(...);
int SceneMgrUpdate(...);
int SceneUpdate(...);
int ScriptUpdate(...);
int TerminateProcess(...);
int UINotifyUpdate(...);
int UIPostUpdate(...);
int UISceneUpdate(...);
int sub_401000(...);
int sub_402220(...);
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
int sub_4319C0(...);
int sub_431C00(...);
int sub_432680(...);
int sub_434BD0(...);
int sub_434C40(...);
int sub_43A3E0(...);
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
int sub_4F6C60(...);
int sub_4F6DA0(...);
int sub_4FA210(...);
int sub_4FA280(...);
int sub_4FA330(...);
int sub_4FA3A0(...);
int sub_4FA440(...);
int sub_4FA4E0(...);
int sub_5025C0(...);
int sub_502950(...);
int sub_502CC0(...);
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
int sub_55310F(...);
int sub_55437D(...);
int sub_55444D(...);
int sub_554722(...);
int sub_557C4C(...);
int sub_55BA88(...);
int sub_55BAB4(...);
int sub_55BAE1(...);
int sub_55D67E(...);

// Unnamed globals (extern)
extern char aBadCommandOrFi[];
extern char aBasedata[];
extern char aBasedataCpk[];
extern char aCdriver[];
extern char aDProjectPal3Ui_0[];
extern char aEnginelogTxt[];
extern char aNotFoundSInUiO[];
extern char aPal3[];
extern char aSGameC[];
extern char aSoftwareSoftst[];
extern char aSoftwareSoftst_1[];
extern char aUiCursorJtTga[];
extern char aUiCursorSbNTga[];
extern char aUiCursorSbSTga[];
extern char aUiGamemainuiCo_0[];
extern char aUiGamemainuiCo_33[];
extern char aUiGamemainuiCo_34[];
extern char aUiGamemainuiCo_35[];
extern char aUiGamemainuiCo_36[];
extern char aUiGamemainuiCo_37[];
extern char aUiGamemainuiSt_0[];
extern char aUiGamemainuiSt_2[];
extern unsigned char byte_17B3AAC;
extern unsigned char byte_17B41E8;
extern unsigned char byte_1895330;
extern unsigned char byte_1895338;
extern unsigned char byte_189537C;
extern unsigned char byte_18953F0;
extern unsigned char byte_1895502;
extern unsigned char byte_189598F;
extern unsigned char byte_18969C0;
extern unsigned char byte_56A634;
extern unsigned char byte_573298;
extern unsigned char byte_60AF10;
extern unsigned char byte_60AF58;
extern unsigned char byte_60B710;
extern unsigned char byte_60B72C;
extern unsigned char byte_BFDA88;
extern unsigned char byte_BFDA91;
extern unsigned char byte_D8B938;
extern unsigned char byte_D92784;
extern unsigned char byte_D92785;
extern unsigned char byte_DBA25C;
extern unsigned char byte_DBA830;
extern unsigned char byte_DBD8A0;
extern int dword_17A94E0;
extern int dword_17B3EB0;
extern int dword_1895050;
extern int dword_189505C;
extern int dword_1895060;
extern int dword_1895064;
extern int dword_1895068;
extern int dword_189506C;
extern int dword_18952FC;
extern int dword_1895310;
extern int dword_1895314;
extern int dword_1895320;
extern int dword_1895324;
extern int dword_1895328;
extern int dword_189532C;
extern int dword_1895334;
extern int dword_1895344;
extern int dword_1895348;
extern int dword_189534C;
extern int dword_1895350;
extern int dword_1895354;
extern int dword_1895358;
extern int dword_189535C;
extern int dword_1895364;
extern int dword_1895374;
extern int dword_1895380;
extern int dword_1895384;
extern int dword_189538C;
extern int dword_1895390;
extern int dword_189539C;
extern int dword_18953A8;
extern int dword_18953B8;
extern int dword_18953D8;
extern int dword_18953DC;
extern int dword_18953E0;
extern int dword_18953E8;
extern int dword_18953EC;
extern int dword_18954F4;
extern int dword_18954F8;
extern int dword_1895520;
extern int dword_1895524;
extern int dword_1895528;
extern int dword_189552C;
extern int dword_1895530;
extern int dword_1895534;
extern int dword_1895544;
extern int dword_1895548;
extern int dword_189554C;
extern int dword_1895550;
extern int dword_18969BC;
extern int dword_1896CE4;
extern int dword_1896CE8;
extern int dword_1896CEC;
extern int dword_1896CF0;
extern int dword_1896CF4;
extern int dword_1896CF8;
extern int dword_1896CFC;
extern int dword_1896D04;
extern int dword_1896D10;
extern int dword_580000;
extern int dword_5809E8;
extern int dword_580A04;
extern int dword_580A0C;
extern int dword_580A10;
extern int dword_580A18;
extern int dword_586154;
extern int dword_58B230;
extern int dword_58B234;
extern int dword_5A3748;
extern int dword_60AC60;
extern int dword_60ACA4;
extern int dword_60ACB4;
extern int dword_60B128;
extern int dword_60B34C;
extern int dword_60B4B0;
extern int dword_60B4B4;
extern int dword_60B528;
extern int dword_60B52C;
extern int dword_60B530;
extern int dword_60B538;
extern int dword_60B870;
extern int dword_6EBFA0;
extern int dword_7CC178;
extern int dword_8ACD40;
extern int dword_BFDA48;
extern int dword_BFDA64;
extern int dword_BFDA80;
extern int dword_BFDA84;
extern int dword_BFDE28;
extern int dword_BFE0A0;
extern int dword_C00028;
extern int dword_C002A0;
extern int dword_C020F8;
extern int dword_C02370;
extern int dword_C025EC;
extern int dword_C12B38;
extern int dword_C12B3C;
extern int dword_C12B40;
extern int dword_D8C2B0;
extern int dword_D92788;
extern int dword_DBA0D4;
extern int dword_DBA134;
extern int dword_DBA254;
extern int dword_DBA260;
extern int dword_DBD898;
extern int dword_DC0DE8;
extern int dword_DC10FC;
extern int dword_DC1100;
extern int dword_DE5CE4;
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
extern float flt_BFDB94;
extern float flt_BFDBA8;
extern float flt_BFDBAC;
extern float flt_BFDC54;
extern float flt_C116F8;
extern int nullsub_1;
extern int nullsub_103;
extern int nullsub_2;
extern int nullsub_3;
extern int nullsub_96;
extern void *off_56A6D0;
extern void *off_56AA90;
extern void *off_56AE84;
extern void *off_56AEA4;
extern void *off_56B094;
extern void *off_56F018;
extern void *off_56F02C;
extern void *off_592DA4;
extern void *off_6088D8;
extern void *off_60AC20;
extern void *off_60ACA0;
extern void *off_60ACB8;
extern void *off_60ACBC;
extern void *off_60ACC0;
extern void *off_60ACC4;
extern void *off_60ACC8;
extern void *off_60ACCC;
extern void *off_60ACD0;
extern void *off_60ACD4;
extern void *off_60ACE4;
extern void *off_60AF50;
extern void *off_60B0B8;
extern void *off_60B53C;
extern int stru_17B3ED8;
extern int stru_573370;
extern int stru_BFAB60;
extern int stru_DBAF10;
extern int stru_DE7DF8;
extern int stru_DE93B0;
extern int unk_1010100;
extern int unk_17B1550;
extern int unk_1894D90;
extern int unk_1895504;
extern int unk_18969B0;
extern int unk_18969B4;
extern int unk_18969B8;
extern int unk_1896AC0;
extern int unk_1896BC0;
extern int unk_1896BE4;
extern int unk_5731D8;
extern int unk_60AC30;
extern int unk_60AC34;
extern int unk_60AC38;
extern int unk_60ACF0;
extern int unk_60AF3D;
extern int unk_60AF60;
extern int unk_60AF64;
extern int unk_60AF70;
extern int unk_60B0C8;
extern int unk_60B0D8;
extern int unk_60B0F8;
extern int unk_60B348;
extern int unk_60B878;
extern int unk_60B9D8;
extern int unk_60BDC8;
extern int unk_8ACD30;
extern int unk_8ACD34;
extern int unk_8ACD3C;
extern int unk_A3A7D8;
extern int unk_BFDAA4;
extern int unk_BFDAB0;
extern int unk_DBA258;
extern int unk_DBB364;
extern int unk_DBD894;
extern int unk_DC0DE0;
extern int unk_DE6A44;
extern int unk_DE6A48;
extern int unk_FF0000;
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
extern int word_1895500;

// 0x004017D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_287()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00401C30
int _E153()
{
  _E158();
  return atexit(_E163);
}

// 0x00401C40
gbVFileSystem *_E158()
{
  return gbVFileSystem::gbVFileSystem((gbVFileSystem *)&unk_60BDC8);
}

// 0x00401C60
void __cdecl _E163()
{
  gbVFileSystem::~gbVFileSystem((gbVFileSystem *)&unk_60BDC8);
}

// 0x00401C70
// strings: Basedata system init failed.; basedata.cpk
// write access to const memory has been detected, the output may be wrong!
int FileSysInit()
{
  _DWORD (__thiscall *v0)(gbVFileSystem *__hidden, char *); // esi
  char v2[324]; // [esp+8h] [ebp-944h] BYREF
  char pExceptionObject[1024]; // [esp+14Ch] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+54Ch] [ebp-400h] BYREF

  if ( (g_nGameFlags & 2) != 0 )
  {
    strcpy(v2, aBasedata);
    strcat(v2, aBasedataCpk);
    v0 = gbVFileSystem::Init;
    if ( !gbVFileSystem::Init((gbVFileSystem *)&dword_7CC178, v2) )
    {
      qmemcpy(pExceptionObject, Logger::FormatException((Logger *)ArgList, msg, file, 23), sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
  }
  else
  {
    v0 = gbVFileSystem::Init;
    if ( !gbVFileSystem::Init((gbVFileSystem *)&dword_7CC178, aBasedata) )
    {
      qmemcpy(pExceptionObject, Logger::FormatException((Logger *)ArgList, msg, file, 28), sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
  }
  g_pVFileSys = (struct gbVFileSystem *)&dword_7CC178;
  return v0((gbVFileSystem *)&unk_60BDC8, 0);
}

// 0x00401DA0
// write access to const memory has been detected, the output may be wrong!
struct gbVFileSystem *FileSysDestory()
{
  struct gbVFileSystem *result; // eax

  if ( dword_7CC178 )
    gbVFileSystem::Release((gbVFileSystem *)&dword_7CC178);
  result = (struct gbVFileSystem *)dword_6EBFA0;
  if ( dword_6EBFA0 )
  {
    gbVFileSystem::Release((gbVFileSystem *)&dword_6EBFA0);
    result = g_pVFileSys;
  }
  g_pVFileSys = 0;
  return result;
}

// 0x00401FA0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_289()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004021E0
int __thiscall WinProc_HWND_4021E0(GRPinput *_this, int a2, int a3, int a4)
{
  _this->m_bMouse = a2;
  if ( a2 )
    GRPinput::AcquireDevices(_this);
  else
    WinProc_HWND_402360((int *)_this);
  _this->m_bKeyboard = a3;
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

// 0x004023D0
int __thiscall EnumJoystick(int _this)
{
  int result; // eax
  int v3; // esi

  result = sub_402220((_WORD *)_this);
  *(_DWORD *)(_this + 6256) = 0;
  v3 = *(_DWORD *)(_this + 4);
  if ( v3 )
    return (*(int (__stdcall **)(int))(*(_DWORD *)v3 + 32))(v3);
  return result;
}

// 0x00402B30
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_290()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00402FB0
void __thiscall std::string::_Tidy(_DWORD *_this, char a2)
{
  int v3; // eax
  _BYTE *v4; // ecx
  char v5; // al

  if ( a2 )
  {
    v3 = *(_this + 1);
    if ( v3 )
    {
      v4 = (_BYTE *)(v3 - 1);
      v5 = *(_BYTE *)(v3 - 1);
      if ( !v5 || v5 == -1 )
        operator delete(v4);
      else
        *v4 = v5 - 1;
    }
  }
  *(_this + 1) = 0;
  *(_this + 2) = 0;
  *(_this + 3) = 0;
}

// 0x00403110
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_291()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004031D0
// between_std_methods (0x402FB0-0x407AB0)
int __thiscall GRPinput_GetState(GRPinput *_this)
{
  float m_mouseSensitivity; // ecx
  int v3; // ecx
  int v4; // edx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st7
  double v13; // st6
  double v14; // st5
  float v16; // [esp+10h] [ebp-44h]
  float v17; // [esp+10h] [ebp-44h]
  float v18; // [esp+10h] [ebp-44h]
  float v19; // [esp+10h] [ebp-44h]
  float v20; // [esp+14h] [ebp-40h]
  float v21; // [esp+14h] [ebp-40h]
  float v22; // [esp+14h] [ebp-40h]
  float v23; // [esp+14h] [ebp-40h]
  int v24; // [esp+18h] [ebp-3Ch] BYREF
  float v25; // [esp+1Ch] [ebp-38h]
  int v26; // [esp+20h] [ebp-34h]
  int v27; // [esp+24h] [ebp-30h]
  int v28; // [esp+28h] [ebp-2Ch]
  int v29; // [esp+2Ch] [ebp-28h]
  int base; // [esp+30h] [ebp-24h] BYREF
  float v31; // [esp+34h] [ebp-20h]
  float v32; // [esp+38h] [ebp-1Ch]
  float v33; // [esp+3Ch] [ebp-18h]
  float v34; // [esp+40h] [ebp-14h]
  float v35; // [esp+44h] [ebp-10h]
  float v36; // [esp+48h] [ebp-Ch]
  float v37; // [esp+4Ch] [ebp-8h]
  float v38; // [esp+50h] [ebp-4h]
  gbRay *v39; // [esp+58h] [ebp+4h]
  int v40; // [esp+5Ch] [ebp+8h]
  gbVec3D *v41; // [esp+60h] [ebp+Ch]

  v25 = 0.0;
  v26 = 0;
  v27 = 0;
  ArraySort((int)&base, 12, 3, gbVec3D::`default constructor closure');
  m_mouseSensitivity = _this->m_mouseSensitivity;
  v24 = 2139095039;
  LOBYTE(v28) = 0;
  v29 = 0;
  GRPinput::DecideKeyStatus((GRPinput *)LODWORD(m_mouseSensitivity), v39, (int)&v24);
  v3 = v26;
  v4 = v27;
  *(float *)v40 = v25;
  *(_DWORD *)(v40 + 4) = v3;
  *(_DWORD *)(v40 + 8) = v4;
  if ( (_BYTE)v28 && v41 )
  {
    v5 = v33 - *(float *)&base;
    v16 = v34 - v31;
    v6 = v35 - v32;
    v41[1].y = v16;
    v20 = v6;
    v41[1].x = v5;
    v41[1].z = v20;
    gbVec3D::Normalize(v41 + 1);
    v7 = v36 - *(float *)&base;
    v17 = v37 - v31;
    v8 = v38 - v32;
    v41[2].y = v17;
    v21 = v8;
    v41[2].x = v7;
    v41[2].z = v21;
    gbVec3D::Normalize(v41 + 2);
    v9 = v41[1].y * v41[2].z - v41[1].z * v41[2].y;
    v18 = v41[1].z * v41[2].x - v41[1].x * v41[2].z;
    v10 = v41[1].x * v41[2].y;
    v11 = v41[1].y * v41[2].x;
    v41->y = v18;
    v22 = v10 - v11;
    v41->x = v9;
    v41->z = v22;
    gbVec3D::Normalize(v41);
    v12 = v41->z * v41[1].y - v41[1].z * v41->y;
    v19 = v41[1].z * v41->x - v41->z * v41[1].x;
    v13 = v41->y * v41[1].x;
    v14 = v41->x * v41[1].y;
    v41[2].y = v19;
    v23 = v13 - v14;
    v41[2].x = v12;
    v41[2].z = v23;
    gbVec3D::Normalize(v41 + 2);
  }
  return (unsigned __int8)v28;
}

// 0x00404430
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_292()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004044B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_293()
{
  return ctor_0x431870(&stru_BFAB60);
}

// 0x004044D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_294()
{
  PalScript_Cleanup(&stru_BFAB60);
}

// 0x004044F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
char *unknown_libname_295()
{
  return sub_53C250((char *)&unk_A3A7D8);
}

// 0x00404510
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_296()
{
  std::strstreambuf::~strstreambuf((std::strstreambuf *)&unk_A3A7D8);
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
  g_Input.m_bMouse = 0;
  g_Input.m_bKeyboard = 0;
  g_Input.m_bJoystick = 0;
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
  *(_WORD *)&g_Input.m_keyStates[268] = 0;
  memset(g_Input.m_keyRaw, 0, 0x10Cu);
  HIWORD(g_Input.m_keyPressTimes[2]) = 0;
  memset(g_Input.m_keyPressTimes, 0, sizeof(g_Input.m_keyPressTimes));
  memset(g_Input.m_keyDragStartPositions, 0, sizeof(g_Input.m_keyDragStartPositions));
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
  return sub_457260(dword_8ACD40);
}

// 0x00404610
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_302()
{
  sub_457340((int)dword_8ACD40);
}

// 0x00404620
// between_std_methods (0x402FB0-0x407AB0)
int _E187()
{
  unknown_libname_303();
  return atexit(unknown_libname_304);
}

// 0x00404630
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_BYTE *unknown_libname_303()
{
  return sub_430180(&unk_8ACD30);
}

// 0x00404650
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_304()
{
  PalScript *v0; // [esp+0h] [ebp-4h] BYREF

  v0 = &unk_8ACD30;
  sub_430B30(&unk_8ACD30, &v0, (_DWORD *)*unk_8ACD34, unk_8ACD34);
  operator delete(unk_8ACD34);
  unk_8ACD34 = 0;
  unk_8ACD3C = 0;
  if ( !--*(_DWORD *)&String[256] )
  {
    operator delete(dword_D8C2B0);
    dword_D8C2B0 = 0;
  }
}

// 0x00404660
// between_std_methods (0x402FB0-0x407AB0)
int _E202()
{
  _E207();
  return atexit(_E212);
}

// 0x00404670
// between_std_methods (0x402FB0-0x407AB0)
gbImage2D *_E207()
{
  return gbImage2D::gbImage2D((gbImage2D *)&g_PAL3Data._tail[8]);
}

// 0x00404690
// between_std_methods (0x402FB0-0x407AB0)
void __cdecl _E212()
{
  if ( (g_PAL3Data._tail[0] & 1) == 0 )
  {
    g_PAL3Data._tail[0] |= 1u;
    gbImage2D::~gbImage2D((gbImage2D *)&g_PAL3Data._tail[8]);
  }
}

// 0x004046B0
// between_std_methods (0x402FB0-0x407AB0)
int __thiscall _E217(void *_this)
{
  _E222((int)_this);
  return atexit(_E228);
}

// 0x004046C0
// between_std_methods (0x402FB0-0x407AB0)
int __fastcall _E222(int a1)
{
  LOBYTE(g_PAL3Data._p000) = HIBYTE(a1);
  g_PAL3Data._d004 = 0;
  g_PAL3Data._d008 = 0;
  g_PAL3Data._d00C = 0;
  return 0;
}

// 0x004046F0
// between_std_methods (0x402FB0-0x407AB0)
void __cdecl _E228()
{
  char v0; // al

  if ( (g_PAL3Data._tail[0] & 2) == 0 )
  {
    g_PAL3Data._tail[0] |= 2u;
    if ( g_PAL3Data._d004 )
    {
      v0 = *(_BYTE *)(g_PAL3Data._d004 - 1);
      if ( !v0 || v0 == -1 )
        operator delete((void *)(g_PAL3Data._d004 - 1));
      else
        *(_BYTE *)(g_PAL3Data._d004 - 1) = v0 - 1;
    }
    g_PAL3Data._d004 = 0;
    g_PAL3Data._d008 = 0;
    g_PAL3Data._d00C = 0;
  }
}

// 0x00404750
// between_std_methods (0x402FB0-0x407AB0)
void _E233()
{
  PAL3::PAL3();
  JUMPOUT(0x404770);
}

// 0x00404D60
// between_std_methods (0x402FB0-0x407AB0)
int __stdcall WinProc(HWND hWnd, UINT Msg, unsigned int pvParam, LPARAM lParam)
{
  WPARAM v4; // ebx
  UIRenderObj *Instance; // eax
  int result; // eax
  gbGfxManager *v7; // esi
  struct tagPOINT Point; // [esp+Ch] [ebp-8h] BYREF

  v4 = pvParam;
  if ( Msg > 0x4A )
  {
    if ( Msg == 258 )
    {
      WinProc_HWND_53CB10((int)g_Logger, pvParam);
    }
    else
    {
      if ( Msg != 274 )
      {
        if ( Msg == 512 && !*((_BYTE *)UIQuadManager::GetInstance() + 29) )
        {
          if ( byte_BFDA91 )
          {
            v7 = g_pGfxMgr;
            if ( g_pGfxMgr )
            {
              if ( *(_DWORD *)&g_pGfxMgr[1].InvViewMatrix[4] && GetCursorPos(&Point) )
                (*(void (__stdcall **)(_DWORD, int, int, int))(**(_DWORD **)&v7[1].InvViewMatrix[4] + 44))(
                  *(_DWORD *)&v7[1].InvViewMatrix[4],
                  Point.x,
                  Point.y,
                  1);
            }
          }
        }
        return DefWindowProcA(hWnd, Msg, v4, lParam);
      }
      if ( pvParam > 0xF060 )
      {
        if ( pvParam != 61696 && pvParam != 61760 && pvParam != 61808 )
          return DefWindowProcA(hWnd, Msg, v4, lParam);
      }
      else if ( pvParam != 61536 && pvParam != 61440 && pvParam != 61456 && pvParam != 61488 )
      {
        return DefWindowProcA(hWnd, Msg, v4, lParam);
      }
    }
    return 0;
  }
  if ( Msg == 74 )
  {
    WinProc_HWND_53CDE0(g_Logger, *(char **)(lParam + 8));
    return DefWindowProcA(hWnd, Msg, v4, lParam);
  }
  switch ( Msg )
  {
    case 1u:
      pvParam = 0;
      SystemParametersInfoA(0x61u, 1u, 0, 0);
      SystemParametersInfoA(0x26u, 1u, 0, 0);
      SystemParametersInfoA(0x24u, 1u, &pvParam, 0);
      SystemParametersInfoA(0x61u, 1u, &pvParam, 0);
      return DefWindowProcA(hWnd, Msg, v4, lParam);
    case 2u:
      pvParam = 0;
      SystemParametersInfoA(0x61u, 0, 0, 0);
      SystemParametersInfoA(0x26u, 0, 0, 0);
      SystemParametersInfoA(0x24u, 1u, &pvParam, 0);
      SystemParametersInfoA(0x61u, 0, &pvParam, 0);
      g_nGameState = 0;
      PostQuitMessage(0);
      return DefWindowProcA(hWnd, Msg, v4, lParam);
    case 6u:
      if ( (_WORD)pvParam )
      {
        WinProc_HWND_4021E0(&g_Input, 1, 1, 0);
        g_bGameActive = 1;
      }
      else
      {
        g_bGameActive = 0;
        WinProc_HWND_4021E0(&g_Input, 0, 0, 0);
      }
      result = 0;
      break;
    case 0x20u:
      if ( !g_pGfxMgr )
        return DefWindowProcA(hWnd, Msg, v4, lParam);
      SetCursor(0);
      UIQuadManager::GetInstance();
      UIQuadManager_Reset();
      if ( dword_DBD898 != 9 )
      {
        Instance = (UIRenderObj *)UIQuadManager::GetInstance();
        UIRenderObj::~UIRenderObj(Instance, 1u);
      }
      result = 1;
      break;
    default:
      return DefWindowProcA(hWnd, Msg, v4, lParam);
  }
  return result;
}

// 0x00407AB0
char __thiscall std::string::_Freeze(unsigned int *_this)
{
  int v2; // eax
  unsigned int v3; // edi
  int v4; // ecx
  int v5; // esi
  int v7; // [esp+0h] [ebp-8h]

  v2 = *(_this + 1);
  if ( v2 )
  {
    LOBYTE(v2) = *(_BYTE *)(v2 - 1);
    if ( (_BYTE)v2 )
    {
      if ( (_BYTE)v2 != 0xFF )
      {
        v3 = *(_this + 2);
        if ( v3 > 0xFFFFFFFD )
          std::_Xlen(v7);
        v4 = *(_this + 1);
        if ( v4 )
        {
          LOBYTE(v2) = *(_BYTE *)(v4 - 1);
          if ( (_BYTE)v2 )
          {
            if ( (_BYTE)v2 != 0xFF )
            {
              if ( !v3 )
              {
                LOBYTE(v2) = v2 - 1;
                *(_BYTE *)(v4 - 1) = v2;
                *(_this + 1) = 0;
                *(_this + 2) = 0;
                *(_this + 3) = 0;
                goto LABEL_16;
              }
LABEL_15:
              LOBYTE(v2) = (unsigned __int8)GRPinput::GetKeyState((GRPinput *)_this, *(_this + 2));
              goto LABEL_16;
            }
          }
        }
        if ( v3 )
        {
          if ( *(_this + 3) >= v3 )
            goto LABEL_16;
          goto LABEL_15;
        }
        if ( v4 )
          LOBYTE(v2) = std::string::_Eos(_this, *(_this + 2));
      }
    }
  }
LABEL_16:
  v5 = *(_this + 1);
  if ( v5 )
    *(_BYTE *)(v5 - 1) = -1;
  return v2;
}

// 0x00407B30
int __thiscall std::string::_Eos(_DWORD *_this, int a2)
{
  *(_this + 2) = a2;
  *(_BYTE *)(*(_this + 1) + a2) = 0;
  return a2;
}

// 0x00407C70
void __thiscall std::string::_Split(int _this)
{
  const char *v2; // ecx
  char v3; // al
  const char *v4; // esi
  unsigned int v5; // kr04_4
  unsigned int v6; // ebx
  int v7; // ecx
  char v8; // al
  unsigned int v9; // eax
  int v10; // ecx
  int v11; // [esp+0h] [ebp-10h]

  v2 = *(const char **)(_this + 4);
  if ( v2 )
  {
    v3 = *(v2 - 1);
    if ( v3 )
    {
      if ( v3 != -1 )
      {
        v4 = v2;
        *((_BYTE *)v2 - 1) = v3 - 1;
        *(_DWORD *)(_this + 4) = 0;
        *(_DWORD *)(_this + 8) = 0;
        *(_DWORD *)(_this + 12) = 0;
        v5 = strlen(v2) + 1;
        v6 = v5 - 1;
        if ( v5 - 1 > 0xFFFFFFFD )
          std::_Xlen(v11);
        v7 = *(_DWORD *)(_this + 4);
        if ( v7 && (v8 = *(_BYTE *)(v7 - 1)) != 0 && v8 != -1 )
        {
          if ( v5 == 1 )
          {
            *(_BYTE *)(v7 - 1) = v8 - 1;
            std::string::_Tidy((_DWORD *)_this, 0);
            return;
          }
        }
        else
        {
          if ( v5 == 1 )
          {
            std::string::_Tidy((_DWORD *)_this, 1);
            return;
          }
          v9 = *(_DWORD *)(_this + 12);
          if ( v9 <= 0x1F && v9 >= v6 )
            goto LABEL_17;
          std::string::_Tidy((_DWORD *)_this, 1);
        }
        GRPinput::GetKeyState((GRPinput *)_this, v6);
LABEL_17:
        qmemcpy(*(void **)(_this + 4), v4, v6);
        v10 = *(_DWORD *)(_this + 4);
        *(_DWORD *)(_this + 8) = v6;
        *(_BYTE *)(v6 + v10) = 0;
      }
    }
  }
}

// 0x00407D40
int std::string::max_size()
{
  return -3;
}

// 0x00407D50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_305()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00408640
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_306()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  return sub_40CC60((int)&g_SceneMgr._gap_1888[792]);
}

// 0x00408800
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
gbVec3D *unknown_libname_312()
{
  g_SceneMgr._gap_1888[776] = (unsigned int)&g_SceneMgr._gap_1888[776] >> 24;
  *(_DWORD *)&g_SceneMgr._gap_1888[780] = 0;
  *(_DWORD *)&g_SceneMgr._gap_1888[784] = 0;
  *(_DWORD *)&g_SceneMgr._gap_1888[788] = 0;
  return (gbVec3D *)&g_SceneMgr._gap_1888[776];
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
  sub_411900(&g_pNPCSystem);
}

// 0x00408AC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void unknown_libname_315()
{
  sub_411900(&g_pActorSystem);
}

// 0x00408B40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_316()
{
  return PtrArray::Clear((PtrArray *)&g_pScriptSystem);
}

// 0x00408B90
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
UIWnd *unknown_libname_317()
{
  return UIWnd_Init_444F60((UIWnd *)&unk_BFDAB0);
}

// 0x00408BB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_318()
{
  UIWnd_Destructor((UIWnd *)&unk_BFDAB0);
}

// 0x0040C230
// between_std_methods (0x407D40-0x411B80)
__int8 *__cdecl ScriptUpdate(int dt)
{
  RoleSystem *m_RoleSystem; // esi
  double v2; // st7
  double v3; // st7
  float *p_f004; // ecx
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

  m_RoleSystem = g_SceneMgr.m_RoleSystem;
  do
  {
    ScriptSystem::UpdateTimers(*(float *)&dt);
    ++m_RoleSystem;
  }
  while ( (int)m_RoleSystem < (int)&g_SceneMgr.m_pGameData );
  if ( dword_C025EC == 10 )
  {
    if ( g_SceneMgr.m_RoleSystem[1]._d278 )
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
      RoleSystemNotify((int)&g_pNPCSystem);
    }
    ScriptSystem::UpdateTimers(*(float *)&dt);
  }
  if ( dword_BFDE28 )
  {
    if ( dword_BFE0A0 != 4 )
    {
      dword_BFDE28 = 0;
      RoleSystemNotify((int)&g_pActorSystem);
    }
    ScriptSystem::UpdateTimers(*(float *)&dt);
    flt_BFDC54 = flt_BFDC54 + 80.0;
  }
  if ( (unsigned int)g_nScreenH <= 4 )
  {
    if ( g_pSoundMgr )
    {
      v3 = flt_BFDBAC + *(float *)&dt;
      flt_BFDBAC = v3;
      if ( v3 >= 4.0 )
      {
        flt_BFDBAC = 0.0;
        switch ( g_nScreenH )
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
            flt_BFDBA8 = flt_BFDBA8 * 1.5;
            ScriptSystem::RunScript((__int64)flt_BFDBA8, 0, 1);
            break;
          default:
            break;
        }
      }
    }
    else
    {
      switch ( g_nScreenH )
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
          flt_BFDBA8 = (double)*(int *)&g_SceneMgr.m_slot0[1408 * g_SceneMgr.m_nCameraState + 292] * 0.5;
          ScriptSystem::RunScript((__int64)flt_BFDBA8, 1, 1);
          break;
        default:
          break;
      }
    }
    g_pSoundMgr = (char *)g_pSoundMgr + 1;
    p_f004 = &g_SceneMgr.m_RoleSystem[g_SceneMgr.m_nCameraState]._f004;
    v10 = *(_DWORD *)p_f004;
    v11 = *((int *)p_f004 + 1);
    *(float *)v13 = *p_f004 - *(float *)&g_hWnd;
    v12 = *((int *)p_f004 + 2);
    *(float *)&v13[4] = *(float *)&v11 - *(float *)&g_hInstance;
    *(float *)&v13[8] = *(float *)&v12 - *(float *)&g_nScreenW;
    v14 = *(gbVec3D *)v13;
    v5 = gbVec3D::Length(&v14) + flt_BFDB94;
    g_hInstance = v11;
    g_hWnd = v10;
    g_nScreenW = v12;
    flt_BFDB94 = v5;
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
    result = (__int8 *)&g_SceneMgr.m_RoleSystem[0]._d4CC;
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
      result = (__int8 *)sub_41D5C0(g_pCameraCtrl, dword_586154);
    }
  }
  if ( *(_DWORD *)&g_SceneMgr._gap_c5e0[844] )
    return (*(__int8 *(__thiscall **)(_DWORD))(**(_DWORD **)&g_SceneMgr._gap_c5e0[844] + 20))(*(_DWORD *)&g_SceneMgr._gap_c5e0[844]);
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
  _DWORD *v10; // eax
  char *v11; // ebp
  _DWORD *j; // ebx
  int v13; // eax
  int v14; // ecx
  char *v15; // ecx
  char *i; // eax
  char *v17; // edi
  int v18; // ecx
  unsigned int v19; // [esp+10h] [ebp-8h]
  _DWORD *v20; // [esp+14h] [ebp-4h]

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
      v10 = operator new(12 * v9);
      v11 = *(char **)(_this + 4);
      v20 = v10;
      for ( j = v10; v11 != v5; j += 3 )
      {
        Array::Copy(j, v11);
        v11 += 12;
      }
      Array::Erase(j, 1, pConfig);
      Array::Insert(v5, *(void **)(_this + 8), j + 3);
      nullsub_2(*(_DWORD *)(_this + 4), *(_DWORD *)(_this + 8));
      operator delete(*(void **)(_this + 4));
      *(_DWORD *)(_this + 12) = &v20[3 * v19];
      v13 = *(_DWORD *)(_this + 4);
      if ( v13 )
      {
        v14 = *(_DWORD *)(_this + 8);
        *(_DWORD *)(_this + 4) = v20;
        result = (char *)&v20[3 * ((v14 - v13) / 12) + 3];
        *(_DWORD *)(_this + 8) = result;
      }
      else
      {
        *(_DWORD *)(_this + 4) = v20;
        *(_DWORD *)(_this + 8) = v20 + 3;
        return (char *)(v20 + 3);
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
  _DWORD *v28; // eax
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
  _DWORD *v41; // [esp+1Ch] [ebp-8h]
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
                v28 = operator new(12 * v27);
                v29 = (char *)v3[1];
                v41 = v28;
                for ( j = (char *)v28; v29 != v23; j += 12 )
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
                v3[3] = (int)&v41[3 * v40];
                v33 = Array::Size(v3);
                v4 = v39;
                v2 = _this;
                v3[1] = (int)v41;
                v3[2] = (int)&v41[3 * v33 + 3];
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
  char *v8; // edx
  int i; // esi
  int v10; // edi
  int v11; // esi
  GRPinput *v12; // ecx
  int v14; // eax
  char *v15; // ecx
  int v16; // ecx
  unsigned __int8 v17; // [esp+13h] [ebp-15h]
  int v18; // [esp+14h] [ebp-14h]
  _DWORD a2[4]; // [esp+18h] [ebp-10h] BYREF
  int v20; // [esp+2Ch] [ebp+4h]

  v1 = 0;
  v2 = 0;
  v18 = -1;
  v17 = 0;
  if ( (int)g_pUIManager2 <= 0 )
    return sub_445720((UIWnd *)&unk_BFDAB0, 0);
  do
  {
    v3 = *((_DWORD *)g_pScriptSystem + v2);
    GRPinput::SetJoystickFreePos((GRPinput *)v3, a1);
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
      if ( v2 >= 0 && v2 < (int)g_pUIManager2 )
        *((_DWORD *)g_pScriptSystem + v2) = 0;
      v1 = 1;
    }
    v8 = (char *)g_pUIManager2;
    ++v2;
  }
  while ( v2 < (int)g_pUIManager2 );
  if ( v1 )
  {
    for ( i = 0; i < (int)g_pUIManager2; v8 = (char *)g_pUIManager2 )
    {
      if ( i >= 0 && i < (int)v8 && *((_DWORD *)g_pScriptSystem + i) )
        ++i;
      else
        PtrArray::InsertAt((PtrArray *)&g_pScriptSystem, i, 1);
    }
    v10 = 0;
    v11 = 40;
    if ( (int)v8 > 0 )
    {
      do
      {
        v12 = (GRPinput *)*((_DWORD *)g_pScriptSystem + v10);
        if ( v12->m_mouseMaxY == 1 )
        {
          GRPinput::GetMouseSensitivity(v12, v11);
          v11 += 24;
        }
        v8 = (char *)g_pUIManager2;
        ++v10;
      }
      while ( v10 < (int)g_pUIManager2 );
    }
  }
  if ( v18 == -1 )
    return sub_445720((UIWnd *)&unk_BFDAB0, 0);
  v14 = 0;
  if ( (int)v8 > 0 )
  {
    v15 = (char *)g_pScriptSystem;
    do
    {
      if ( *(_DWORD *)(*(_DWORD *)v15 + 28) == 1 )
        ++v14;
      v15 += 4;
      --v8;
    }
    while ( v8 );
  }
  a2[1] = 5;
  v16 = 10 * v18 + 64;
  a2[3] = 24 * v14 + 30;
  a2[0] = ((int)g_pGameTime - v16) / 2 < 0 ? 0 : ((int)g_pGameTime - v16) / 2;
  a2[2] = v16 + a2[0];
  UIWnd::GetRect((UIWnd *)&unk_BFDAB0, a2);
  sub_445720((UIWnd *)&unk_BFDAB0, 1);
  UIWnd::SetState((UIWnd *)&unk_BFDAB0, 1);
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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

  RoleSystem::RenderRole((RoleSystem *)(v0 - 64), g_pGfxMgr->pMatrixStack[1], a3);
  return result;
}

// 0x0041BDF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_322()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( g_GameDataFlags == 1 )
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
  if ( g_GameDataFlags == 1 )
    InputSystem::ProcessMouse(a1);
  return InputSystem::ProcessKeyboard(1);
}

// 0x0041D8A0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_323()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  int m_pCollisionNode; // esi
  GRP_KEYREG *KeyInfo; // eax
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
  int PressTime; // ecx
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
  if ( dword_58B234 && g_GameDataFlags != 1 )
  {
    v41 = *(_DWORD *)&g_Input.MouseState[8];
    if ( *(_DWORD *)&g_Input.MouseState[8] )
    {
      v1 = (double)v41 * 0.0013962634;
      pDist = v1;
      if ( v1 <= 1.5700001 )
      {
        if ( pDist < -1.5700001 )
          pDist = -1.5700001;
        CameraCtrl::SetCamMode(g_pCameraCtrl, SLODWORD(pDist));
      }
      else
      {
        pDist = 1.5700001;
        CameraCtrl::SetCamMode(g_pCameraCtrl, 1070134723);
      }
    }
    else if ( (g_Input.KeyInfo[13].Data & 0xF) == 1 )
    {
      CameraCtrl::SetCamMode(g_pCameraCtrl, 1034147594);
    }
    else if ( (g_Input.KeyInfo[14].Data & 0xF) == 1 )
    {
      CameraCtrl::SetCamMode(g_pCameraCtrl, -1113336054);
    }
  }
  if ( *(_DWORD *)g_SceneMgr._tail )
  {
    v2 = 0.0;
    if ( (g_Input.KeyInfo[4].Data & 0xF) == 1 )
    {
      v2 = 1.0;
    }
    else if ( (g_Input.KeyInfo[5].Data & 0xF) == 1 )
    {
      v2 = -1.0;
    }
    if ( (g_Input.KeyInfo[38].Data & 0xF) == 1 )
    {
      v3 = (float *)((char *)g_pCameraCtrl + 4);
      v4 = v2 + *((float *)g_pCameraCtrl + 1);
      *((_DWORD *)g_pCameraCtrl + 2) = 0;
      *v3 = v4;
    }
    else if ( (g_Input.KeyInfo[39].Data & 0xF) == 1 )
    {
      *((float *)g_pCameraCtrl + 117) = v2 * 8.0 + *((float *)g_pCameraCtrl + 117);
    }
    else if ( (g_Input.KeyInfo[40].Data & 0xF) == 1 )
    {
      *((float *)g_pCameraCtrl + 113) = v2 * 0.039250001 + *((float *)g_pCameraCtrl + 113);
    }
    else if ( (g_Input.KeyInfo[0].Data & 0xF) == 1 )
    {
      *((float *)g_pCameraCtrl + 135) = v2 + v2 + *((float *)g_pCameraCtrl + 135);
    }
    return;
  }
  Instance = (CScreenMode *)SoundContext::GetInstance();
  CScreenMode::SetAudioParam(Instance);
  v6 = (CScreenMode *)SoundContext::GetInstance();
  if ( CScreenMode::IsAudioReady(v6) && !g_SceneMgr._gap_c5e0[848] )
  {
    if ( g_nGameState == 2
      && g_GameDataFlags == 2
      && g_Input.KeyInfo[12].PressTime == 1
      && (g_Input.KeyInfo[12].Data & 0xF) == 1
      && !(*(int (__thiscall **)(int))(*(_DWORD *)(g_SceneMgr.m_pCollisionNode + 56) + 4))(g_SceneMgr.m_pCollisionNode + 56) )
    {
      v7 = g_SceneMgr.m_nCameraState + 1;
      if ( g_SceneMgr.m_nCameraState + 1 > 4 )
        v7 = 0;
      if ( !g_SceneMgr._gap_1888[v7 + 832] )
      {
        do
        {
          if ( ++v7 > 4 )
            v7 = 0;
        }
        while ( v7 != g_SceneMgr.m_nCameraState && !g_SceneMgr._gap_1888[v7 + 832] );
      }
      ScriptSystem::Execute(v7, 1);
    }
    m_pCollisionNode = g_SceneMgr.m_pCollisionNode;
    if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1264) != 4 )
      goto LABEL_51;
    if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1228) == 44 )
    {
      KeyInfo = g_Input.KeyInfo;
      v10 = 0;
      while ( (KeyInfo->Data & 0xF) != 1 )
      {
        v10 += 16;
        ++KeyInfo;
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
      if ( g_GameDataFlags == 2 )
        LOBYTE(v41) = Camera::IsTransitioning();
      UIWnd::Destroy((UIWnd *)&g_SceneMgr.m_pCameraCtrl, (unsigned __int8)v41);
      if ( (_BYTE)v41 )
      {
        memset(pOut, 0, 12);
        RoleSystem::GetDirection((RoleSystem *)g_SceneMgr.m_pCollisionNode, &pOut[0].x);
        pOut[0].y = pOut[0].y + 10.0;
        gbCamera::PointWorldToScr((gbCamera *)((char *)g_pCameraCtrl + 4), pOut, &v43, &pOut2);
        UIWnd::ScreenToClient(
          (UIWnd *)&g_SceneMgr.m_pCameraCtrl,
          (__int64)((v43 + 1.0) * (double)(int)g_pGameTime * 0.5),
          (__int64)((1.0 - pOut2) * (double)(int)g_pAbsTime * 0.5));
      }
      v11 = 0;
      v12 = 0;
      pDist = 0.0;
      qmemcpy(pMat, CameraCtrl::GetViewTarget(g_pCameraCtrl, pOut, (float *)&g_SceneMgr._gap_cd10[912]), sizeof(pMat));
      if ( g_nGameState != 2 && g_nGameState != 8 )
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
        PressTime = g_Input.KeyInfo[0].PressTime;
        if ( g_Input.KeyInfo[0].PressTime != 1 )
          goto LABEL_109;
        if ( (g_Input.KeyInfo[0].Data & 0xF) != 1 )
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
        PressTime = g_Input.KeyInfo[0].PressTime;
        if ( g_Input.KeyInfo[0].PressTime == 1 )
        {
LABEL_108:
          if ( (g_Input.KeyInfo[0].Data & 0xF) == 1 )
            goto LABEL_115;
        }
LABEL_109:
        v25 = g_Input.KeyInfo[0].Data & 0xF;
        if ( v25 != 1
          && (PressTime != 1 || v25 != 2)
          && (g_Input.KeyInfo[0].Data & 0xFu) <= 1
          && (g_Input.KeyInfo[1].PressTime != 1 || (g_Input.KeyInfo[1].Data & 0xF) != 1) )
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
        if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
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
        else if ( (g_Input.KeyInfo[0].Data & 0xF) == 1 && (double)g_Input.KeyInfo[0].PressTime * a1 > 0.5 )
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
        else if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 )
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
          if ( (g_Input.KeyInfo[0].Data & 0xFu) <= 1 || (double)g_Input.KeyInfo[0].PressTime * a1 <= 0.5 )
          {
LABEL_145:
            if ( (g_SceneMgr._gap_cd10[1610] || (_BYTE)v41 && g_GameDataFlags == 2)
              && g_Input.KeyInfo[1].PressTime == 1
              && (g_Input.KeyInfo[1].Data & 0xF) == 1
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
            if ( g_Input.KeyInfo[6].PressTime == 1 && (g_Input.KeyInfo[6].Data & 0xF) == 1 )
            {
              if ( g_nGameState == 2 )
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
            if ( (g_Input.KeyInfo[3].Data & 0xF) == 1 )
            {
              v31 = 1;
              a2 = *(gbVec3D *)((_BYTE *)g_pCameraCtrl + 44);
LABEL_176:
              v12 = 3;
              goto LABEL_177;
            }
            if ( (g_Input.KeyInfo[3].Data & 0xFu) <= 1 )
            {
              if ( (g_Input.KeyInfo[2].Data & 0xF) == 1 )
              {
                a2.x = -*((float *)g_pCameraCtrl + 132);
                a2.y = -*((float *)g_pCameraCtrl + 133);
                a2.z = -*((float *)g_pCameraCtrl + 134);
                v31 = 1;
                goto LABEL_176;
              }
              if ( (g_Input.KeyInfo[2].Data & 0xFu) <= 1 )
              {
LABEL_177:
                if ( (g_Input.KeyInfo[4].Data & 0xF) == 1 )
                {
                  pOut[0].x = *((float *)g_pCameraCtrl + 126);
                  pOut[0].y = *((float *)g_pCameraCtrl + 127);
                  v34 = *((float *)g_pCameraCtrl + 128);
                  pOut[0].y = 0.0;
                  pOut[0].z = v34;
                  gbVec3D::Normalize(pOut);
                  v31 = 1;
                  v12 = 3;
                  a2.x = pOut[0].x + a2.x;
                  a2.y = a2.y + pOut[0].y;
                  a2.z = a2.z + pOut[0].z;
                }
                else if ( (g_Input.KeyInfo[4].Data & 0xFu) <= 1 )
                {
                  if ( (g_Input.KeyInfo[5].Data & 0xF) == 1 )
                  {
                    pOut[0].x = *((float *)g_pCameraCtrl + 126);
                    pOut[0].y = *((float *)g_pCameraCtrl + 127);
                    v36 = *((float *)g_pCameraCtrl + 128);
                    pOut[0].y = 0.0;
                    pOut[0].z = v36;
                    gbVec3D::Normalize(pOut);
                    v31 = 1;
                    v12 = 3;
                    a2.x = a2.x - pOut[0].x;
                    a2.y = a2.y - pOut[0].y;
                    a2.z = a2.z - pOut[0].z;
                  }
                  else if ( (g_Input.KeyInfo[5].Data & 0xFu) <= 1 )
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
                    pOut[0].x = *((float *)g_pCameraCtrl + 126);
                    pOut[0].y = *((float *)g_pCameraCtrl + 127);
                    v37 = *((float *)g_pCameraCtrl + 128);
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
                  pOut[0].x = *((float *)g_pCameraCtrl + 126);
                  pOut[0].y = *((float *)g_pCameraCtrl + 127);
                  v35 = *((float *)g_pCameraCtrl + 128);
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
              a2.x = -*((float *)g_pCameraCtrl + 132);
              a2.y = -*((float *)g_pCameraCtrl + 133);
              a2.z = -*((float *)g_pCameraCtrl + 134);
            }
            else
            {
              a2 = *(gbVec3D *)((_BYTE *)g_pCameraCtrl + 44);
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
        if ( g_nScreenH != 2 )
          ScriptSystem::RunEvent(2, 1, 0);
      }
      else if ( v6 == 10 )
      {
        if ( g_nScreenH )
          ScriptSystem::RunEvent(0, 1, 0);
      }
      else if ( v6 == 13 && g_nScreenH != 3 )
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
      if ( g_pSceneNode )
      {
        if ( v7 )
        {
          if ( g_pSceneNode != v7 )
          {
            gbSound2DNode::Stop((gbSound2DNode *)g_pSceneNode);
            g_pSceneNode = v7;
            gbSound2DNode::Play(v7);
          }
        }
        else
        {
          gbSound2DNode::Stop((gbSound2DNode *)g_pSceneNode);
          g_pSceneNode = 0;
        }
      }
      else if ( v7 )
      {
        g_pSceneNode = v7;
        gbSound2DNode::Play(v7);
      }
    }
  }
}

// 0x0041EEE0
void __setargv()
{
  dword_58B230 = 1;
}

// 0x0041EEF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_326()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0041F250
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_327()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0041F680
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_328()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00420150
// between_std_methods (0x411BB0-0x430790)
double __userpurge UIUpdate@<st0>(_DWORD *_this@<ecx>, double result@<st0>, double a3)
{
  int v4; // ecx
  int v5; // edi
  _DWORD *v6; // ebx
  int v7; // edi
  _DWORD *v8; // ebx
  float dt; // [esp+10h] [ebp-4h]
  int dta; // [esp+10h] [ebp-4h]

  if ( *(_this + 123285) )
  {
    v4 = *(_this + 123284);
    if ( v4 )
      (*(void (__thiscall **)(int))(*(_DWORD *)v4 + 20))(v4);
    v5 = 0;
    if ( (int)*(_this + 14392) > 0 )
    {
      v6 = _this + 14393;
      do
      {
        dt = a3;
        ScriptSystem::UpdateTimers(dt);
        ++v5;
        v6 += 2176;
      }
      while ( v5 < *(_this + 14392) );
    }
    if ( g_nGameState != 9 )
    {
      v7 = 0;
      if ( (int)*(_this + 55) > 0 )
      {
        v8 = _this + 56;
        do
        {
          *(float *)&dta = a3;
          result = sub_426EB0(v8, result, a3, dta);
          ++v7;
          v8 += 224;
        }
        while ( v7 < *(_this + 55) );
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
    gbSceneGraph::AddVisNode(g_pGfxMgr->pSceneGraph, (struct gbVisNode *)result);
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
    gbSceneGraph::DelVisNode(g_pGfxMgr->pSceneGraph, (struct gbVisNode *)result);
  *(_DWORD *)(v1 + 493144) = 0;
  return result;
}

// 0x00421C40
// between_std_methods (0x411BB0-0x430790)
int __thiscall UINotifyUpdate(int *_this)
{
  int m_pCollisionNode; // ebx
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004224E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_330()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00422560
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
char *unknown_libname_331()
{
  dword_C12B38 = 0;
  dword_C12B3C = 0;
  dword_C12B40 = 0;
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
  return 493156 * (g_GameDataFlags == 1) + 12722152;
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
  RoleSystem *m_RoleSystem; // ebx
  int *p_d4F0; // esi
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
      v1 = dword_C12B40;
      if ( *(_DWORD *)(dword_C12B40 + 88) == 3 )
      {
        gbVisNode::SetTimeScale(*(gbVisNode **)(dword_C12B40 + 92), 0.0);
        (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)(dword_C12B40 + 92) + 24))(
          *(_DWORD *)(dword_C12B40 + 92),
          0);
        v1 = dword_C12B40;
      }
      *(_BYTE *)(v1 + 80) = 0;
    }
    dword_C12B38 = 0;
    dword_C12B3C = 0;
    dword_C12B40 = 0;
  }
  v2 = 493156 * (g_GameDataFlags == 1) + 12722152;
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
      if ( g_GameDataFlags != 2 )
      {
        v17 = 0;
        m_RoleSystem = g_SceneMgr.m_RoleSystem;
        do
        {
          if ( m_RoleSystem->_d278 && m_RoleSystem->_d4F0 != 4 )
          {
            if ( (int)m_RoleSystem < (int)&g_SceneMgr.m_RoleSystem[4] )
            {
              p_d4F0 = &g_SceneMgr.m_RoleSystem[4]._d4F0;
              v12 = 4 - v17;
              do
              {
                if ( *(p_d4F0 - 158) && *p_d4F0 != 4 )
                  sub_416220((int)m_RoleSystem, (int)(p_d4F0 - 316));
                p_d4F0 -= 2176;
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
                  sub_416220((int)m_RoleSystem, (int)(v14 - 36));
                ++v13;
                v14 += 2176;
              }
              while ( v13 < *(_DWORD *)(v18 + 57568) );
            }
          }
          ++m_RoleSystem;
          ++v17;
        }
        while ( (int)m_RoleSystem < (int)&g_SceneMgr.m_pGameData );
        v2 = v18;
      }
      if ( g_SceneMgr.m_pCollisionNode && *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 1264) != 4 )
        sub_420B40((float *)v2, (RoleSystem *)g_SceneMgr.m_pCollisionNode, a1, 0);
    }
  }
  if ( g_GameDataFlags != 1 )
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
gbGfxManager *CombatEnter()
{
  gbGfxManager *result; // eax

  result = (gbGfxManager *)UISceneUpdate();
  if ( *(_DWORD *)&result->DrvInfo[88] != 1
    || (result = (gbGfxManager *)UIScene::ProcessInput(aM19, 0), (_BYTE)result)
    || (result = (gbGfxManager *)UIScene::ProcessInput(aM20, 0), (_BYTE)result)
    || (result = (gbGfxManager *)UIScene::ProcessInput(aM25, 0), (_BYTE)result) )
  {
    g_pGfxMgr->fSelfIllum = 0.69999999;
  }
  else
  {
    result = g_pGfxMgr;
    g_pGfxMgr->fSelfIllum = 0.0;
  }
  return result;
}

// 0x00423630
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_332()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
        gbActorMgr::DestroyActor(dword_BFDA64, *(struct gbActor **)(v0 + 4));
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

  sub_424570(v0 - 8, g_pGfxMgr->pMatrixStack[1], v2);
  return result;
}

// 0x0042C8A0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_333()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0042FD70
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_334()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0042FE80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_335()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00430150
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_336()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00430790
void __thiscall std::string::~string(_DWORD *_this)
{
  int v2; // eax
  _BYTE *v3; // ecx
  char v4; // al

  v2 = *(_this + 1);
  if ( v2 )
  {
    v3 = (_BYTE *)(v2 - 1);
    v4 = *(_BYTE *)(v2 - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      *v3 = v4 - 1;
  }
  *(_this + 1) = 0;
  *(_this + 2) = 0;
  *(_this + 3) = 0;
}

// 0x00431840
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_337()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00431870
// between_std_methods (0x430790-0x445B40)
_DWORD *__thiscall ctor_0x431870(_DWORD *_this)
{
  *(_this + 128) = 0;
  *(_this + 129) = 0;
  *(_this + 130) = 0;
  memset(_this, 0, 0x200u);
  return _this;
}

// 0x004318A0
// between_std_methods (0x430790-0x445B40)
// attributes: thunk
void __thiscall PalScript_Cleanup(PalScript *_this)
{
  sub_4319C0((int)_this);
}

// 0x00431C10
// between_std_methods (0x430790-0x445B40)
char __thiscall Script_Method_431C10(PalScript *String1, char *String2, char *Destination, int a4)
{
  int v5; // edi

  sub_431C00(String1);
  v5 = 0;
  while ( 1 )
  {
    if ( !PalScript::HasNext(String1) )
      return 0;
    if ( !_strcmpi(String1->_pad_000, String2) )
      break;
    if ( _strcmpi(String1->_pad_000, off_592DA4) )
    {
      if ( ++v5 < 1024 )
        continue;
    }
    return 0;
  }
  PalScript::LoadNext(String1);
  strncpy(Destination, String1->_pad_000, a4 - 1);
  return 1;
}

// 0x00431C80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_338()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00431D90
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
Iostream_init *unknown_libname_339()
{
  return Iostream_init::Iostream_init((Iostream_init *)&g_InputState.m_keyStates[24]);
}

// 0x00431DB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_340()
{
  PalScript::ClearAllWaitObj((PalScript *)&g_InputState.m_keyStates[24]);
}

// 0x00431DC0
// between_std_methods (0x430790-0x445B40)
int _E58()
{
  unknown_libname_341();
  return atexit(_E69);
}

// 0x00431DD0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_341()
{
  return PtrArray::Clear((PtrArray *)&g_InputState.m_keyStates[8]);
}

// 0x00431DF0
// between_std_methods (0x430790-0x445B40)
void __cdecl _E69()
{
  if ( (g_InputState.m_keyStates[4] & 1) == 0 )
  {
    g_InputState.m_keyStates[4] |= 1u;
    sub_432680((void **)&g_InputState.m_keyStates[8]);
  }
}

// 0x00431E10
// between_std_methods (0x430790-0x445B40)
int _E74()
{
  unknown_libname_342();
  return atexit(_E84);
}

// 0x00431E20
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int *unknown_libname_342()
{
  LOBYTE(g_InputState.m_joystickY) = (unsigned int)&g_InputState.m_joystickX >> 24;
  g_InputState.m_joystickFreeX = 0;
  g_InputState.m_joystickFreeY = 0;
  g_InputState.m_joystickDeltaX = 0;
  LOWORD(g_InputState.m_joystickDeltaY) = 0;
  *(_DWORD *)g_InputState.m_keyStates = 0;
  g_InputState.m_joystickX = 0;
  return &g_InputState.m_joystickX;
}

// 0x00431E40
// between_std_methods (0x430790-0x445B40)
void __cdecl _E84()
{
  if ( (g_InputState.m_keyStates[4] & 2) == 0 )
  {
    g_InputState.m_keyStates[4] |= 2u;
    PtrArray::Remove((PtrArray *)&g_InputState.m_joystickX);
  }
}

// 0x00431E70
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
tagPOINT *unknown_libname_343()
{
  LOBYTE(g_InputState.m_mousept.y) = (unsigned int)&g_InputState.m_mousept >> 24;
  g_InputState.m_mouseX = 0;
  g_InputState.m_mouseY = 0;
  g_InputState.m_mouseFreeX = 0;
  LOWORD(g_InputState.m_mouseFreeY) = 0;
  g_InputState.m_mouseDeltaX = 0;
  g_InputState.m_mousept.x = 0;
  return &g_InputState.m_mousept;
}

// 0x00431EC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int *unknown_libname_344()
{
  LOBYTE(g_InputState.m_mouseMinY) = (unsigned int)&g_InputState.m_mouseMinX >> 24;
  g_InputState.m_mouseMaxX = 0;
  g_InputState.m_mouseMaxY = 0;
  g_InputState.m_joystickMinX = 0;
  LOWORD(g_InputState.m_joystickMinY) = 0;
  g_InputState.m_joystickMaxX = 0;
  g_InputState.m_mouseMinX = 0;
  return &g_InputState.m_mouseMinX;
}

// 0x00432630
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_345()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004326A0
// between_std_methods (0x430790-0x445B40)
void __thiscall String_Assign_4326A0(void *_this, char *src, int len)
{
  const void *v5; // eax
  int v6; // eax
  char *v7; // eax
  char *srca; // [esp+10h] [ebp+4h]
  int lena; // [esp+14h] [ebp+8h]

  if ( len > 0 )
    *((_DWORD *)_this + 3) = len;
  v5 = *(const void **)_this;
  if ( src )
  {
    if ( v5 )
    {
      if ( (int)src > *((_DWORD *)_this + 2) )
      {
        lena = (int)src;
        if ( (int)src <= *((_DWORD *)_this + 3) + *((_DWORD *)_this + 1) )
          lena = *((_DWORD *)_this + 3) + *((_DWORD *)_this + 1);
        srca = (char *)malloc(4 * lena);
        qmemcpy(srca, *(const void **)_this, 4 * *((_DWORD *)_this + 1));
        free(*(void **)_this);
        *((_DWORD *)_this + 1) = src;
        *(_DWORD *)_this = srca;
        *((_DWORD *)_this + 2) = lena;
      }
      else
      {
        *((_DWORD *)_this + 1) = src;
      }
    }
    else
    {
      v6 = *((_DWORD *)_this + 3);
      *((_DWORD *)_this + 1) = src;
      v7 = &src[v6];
      *((_DWORD *)_this + 2) = v7;
      *(_DWORD *)_this = malloc(4 * (_DWORD)v7);
    }
  }
  else
  {
    if ( v5 )
    {
      free(*(void **)_this);
      *(_DWORD *)_this = 0;
    }
    *((_DWORD *)_this + 2) = 0;
    *((_DWORD *)_this + 1) = 0;
  }
}

// 0x00432830
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_346()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004328B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
_DWORD *unknown_libname_347()
{
  return PtrArray::Clear((PtrArray *)&g_InputState.m_keyStates[40]);
}

// 0x00434B20
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_348()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00434BA0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
GRP_KEYREG *unknown_libname_349()
{
  g_InputState.KeyInfo[156].HoldTime = 0;
  g_InputState.KeyInfo[156].CountMode = 0;
  g_InputState.KeyInfo[156].PressTime = 0;
  g_InputState.KeyInfo[157].Data = 0;
  g_InputState.KeyInfo[157].HoldTime = 0;
  g_InputState.KeyInfo[157].CountMode = 0;
  g_InputState.KeyInfo[153].Data = (int)&off_56AA90;
  g_InputState.KeyInfo[153].HoldTime = 0;
  g_InputState.KeyInfo[153].CountMode = 0;
  g_InputState.KeyInfo[153].PressTime = 0;
  g_InputState.KeyInfo[154].PressTime = 1143930880;
  g_InputState.KeyInfo[154].Data = 0;
  g_InputState.KeyInfo[154].HoldTime = 0;
  g_InputState.KeyInfo[154].CountMode = 0;
  return &g_InputState.KeyInfo[153];
}

// 0x00434BC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_350()
{
  sub_41CBC0(&g_InputState.KeyInfo[153].Data);
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
      return (gbCamera *)CameraCtrl::InitParams(g_pCameraCtrl, pParams);
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
    return (gbCamera *)RoleSystem::SetActive((RoleSystem *)g_pCameraCtrl, (int)v1);
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
    return (gbCamera *)sub_41C190(g_pCameraCtrl, (int)v2);
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
    *((_DWORD *)g_pCameraCtrl + 112) = result;
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
        &g_InputState.KeyInfo[153].Data,
        (int)g_pCameraCtrl,
        *((_DWORD *)String + 1),
        *((_DWORD *)v1 + 1),
        LODWORD(result->OrthoSize));
      sub_434C40((int)&g_InputState.KeyInfo[153]);
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

// 0x00438E90
filebuf *__thiscall filebuf::`scalar deleting destructor'(filebuf *_this, char a2)
{
  filebuf::~filebuf(_this);
  if ( (a2 & 1) != 0 )
    operator delete(_this);
  return _this;
}

// 0x00438FC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_351()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00439930
// between_std_methods (0x430790-0x445B40)
void __thiscall Camera_Method_439930(int _this, int a2, int a3, int a4)
{
  gbCamera *v5; // ecx
  double v6; // st7
  float y; // edx
  float z; // eax
  struct gbVec3D v9; // [esp+Ch] [ebp-30h] BYREF
  struct gbVec3D v10; // [esp+18h] [ebp-24h] BYREF
  struct gbVec3D v11; // [esp+24h] [ebp-18h] BYREF
  float v12; // [esp+34h] [ebp-8h]

  v5 = *(gbCamera **)(_this + 292);
  v11.x = 0.0;
  v11.y = 1.0;
  v11.z = 0.0;
  v9.z = 1600.0;
  v10.z = 0.0;
  v6 = (((double)a2 + (double)a2) / (double)(int)g_pGameTime - 1.0) * *(float *)(_this + 232);
  v12 = (1.0 - ((double)a3 + (double)a3) / (double)(int)g_pAbsTime) * *(float *)(_this + 232);
  v9.y = (float)a4;
  v9.x = -v6;
  v9.y = v9.y - v12;
  v10.x = v9.x;
  v10.y = -v12;
  gbCamera::SetLookAt(v5, &v9, &v10, &v11);
  y = v10.y;
  *(float *)(_this + 296) = v10.x;
  z = v10.z;
  *(float *)(_this + 300) = y;
  *(float *)(_this + 304) = z;
  *(float *)(_this + 296) = *(float *)(_this + 296) - v9.x;
  *(float *)(_this + 300) = *(float *)(_this + 300) - v9.y;
  *(float *)(_this + 304) = *(float *)(_this + 304) - v9.z;
  gbVec3D::Normalize((gbVec3D *)(_this + 296));
}

// 0x0043A070
// between_std_methods (0x430790-0x445B40)
int __thiscall SetFloatParam(void *_this, float value)
{
  int v3; // ecx

  *((float *)_this + 58) = value;
  v3 = *((_DWORD *)_this + 73);
  *(float *)(v3 + 4) = value;
  *(_DWORD *)v3 = 0;
  return LODWORD(value);
}

// 0x0043A0F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_352()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0043A690
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_353()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0043A700
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_354()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0043BB00
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_355()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0043BC70
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_356()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0043BE10
// between_std_methods (0x430790-0x445B40)
UIWnd *__thiscall UIWnd::`scalar deleting destructor'(UIWnd *Block, char a2)
{
  UIWnd::~UIWnd(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0043D7C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_357()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0043DC60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_358()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0043DE60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_359()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0043EBB0
// between_std_methods (0x430790-0x445B40)
void __thiscall GetGridOffset(void *_this, int *pOut, int index)
{
  int v3; // eax
  int v4; // edx

  v3 = *((_DWORD *)_this + 5);
  v4 = *((_DWORD *)_this + 277) * (index - *((_DWORD *)_this + 279));
  *pOut = *((_DWORD *)_this + 4);
  pOut[1] = v3 + v4;
}

// 0x0043F780
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_360()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0043FD90
// between_std_methods (0x430790-0x445B40)
int __thiscall SetIntParam(void *_this, int value)
{
  int result; // eax

  result = value;
  if ( value >= 0 )
    *((float *)_this + 33) = (float)value;
  return result;
}

// 0x004406D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_361()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00441080
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_362()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00442270
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_363()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00442C90
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_364()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00442DA0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_365()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00444AC0
// between_std_methods (0x430790-0x445B40)
void __thiscall UIFrameWnd_Destructor_444AC0(UIWnd *_this)
{
  _this->_vftable = (void **)&off_56AE84;
  UIFrameWnd::_UIFrameWnd((UIFrameWnd *)_this);
}

// 0x00444EF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_366()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00444F60
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
UIWnd *__thiscall UIWnd_Init_444F60(UIWnd *_this)
{
  char v3; // [esp+Bh] [ebp-11h]

  UIWnd::UIWnd(_this);
  *((_BYTE *)_this + 72) = v3;
  *((_DWORD *)_this + 19) = 0;
  *((_DWORD *)_this + 20) = 0;
  *((_DWORD *)_this + 21) = 0;
  UIWnd::DestroyChildren((UIWnd *)((char *)_this + 104));
  *((_DWORD *)_this + 44) = 0;
  BYTE2(_this->m_fontcolor) = -1;
  BYTE1(_this->m_fontcolor) = -1;
  *((_DWORD *)_this + 47) = 0;
  _this->_vftable = (void **)&off_56AEA4;
  *((_DWORD *)_this + 43) = 2;
  LOBYTE(_this->m_fontcolor) = -6;
  *((_DWORD *)_this + 17) = 1056964608;
  return _this;
}

// 0x00445010
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void __thiscall UIWnd_Destructor(UIWnd *_this)
{
  int v2; // eax
  _BYTE *v3; // ecx
  char v4; // al

  _this->_vftable = (void **)&off_56AEA4;
  j_UIWnd::MoveWindow((UIWnd **)_this + 26);
  v2 = *((_DWORD *)_this + 19);
  if ( v2 )
  {
    v3 = (_BYTE *)(v2 - 1);
    v4 = *(_BYTE *)(v2 - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      *v3 = v4 - 1;
  }
  *((_DWORD *)_this + 19) = 0;
  *((_DWORD *)_this + 20) = 0;
  *((_DWORD *)_this + 21) = 0;
  UIWnd::_UIWnd(_this);
}

// 0x00445970
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_367()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004459E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_368()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00445E50
// between_std_methods (0x445B40-0x44BDA0)
int __thiscall UIObj_SetState(UIWnd *_this, int state)
{
  int result; // eax

  result = _this->m_bcreateok;
  if ( result )
  {
    _this->m_benable = state;
    return state;
  }
  return result;
}

// 0x00446060
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_369()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0044AB10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_371()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0044B890
// between_std_methods (0x445B40-0x44BDA0)
// attributes: thunk
void __thiscall j_PalScript_Cleanup(PalScript *_this)
{
  PalScript_Cleanup(_this);
}

// 0x0044B9F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_372()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0044BD60
// between_std_methods (0x445B40-0x44BDA0)
void __thiscall PtrArray_Init(void *_this)
{
  *(_DWORD *)_this = 0;
  *((_DWORD *)_this + 1) = 0;
  *((_DWORD *)_this + 2) = 0;
  *((_DWORD *)_this + 3) = 32;
}

// 0x0044BD80
// between_std_methods (0x445B40-0x44BDA0)
void __thiscall SafeDelete_44BD80(void **_this)
{
  if ( *_this )
  {
    operator delete(*_this);
    *_this = 0;
  }
}

// 0x0044E4C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_373()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0044EB10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_374()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  UIWnd::ctor_AB90((UIWnd *)&unk_DBB364);
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
  RoleSystem *v6; // esi
  ScreenEffect *Instance; // eax
  int v8; // eax
  int (__thiscall ***v9)(_DWORD, _DWORD); // ecx
  int v10; // eax
  int v11; // ecx
  GRPinput *v12; // esi

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
        if ( byte_BFDA88 )
        {
          v6 = dword_BFDA84;
          if ( dword_BFDA84 )
          {
            sub_534FB0((void **)dword_BFDA84);
            operator delete(v6);
            dword_BFDA84 = 0;
            byte_BFDA88 = 0;
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
          v12 = dword_BFDA80;
          if ( dword_BFDA80 )
          {
            sub_52B2A0((void ***)dword_BFDA80);
            operator delete(v12);
            dword_BFDA80 = 0;
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
        g_nGameState = 1;
      }
    }
    switch ( (unsigned int)v2 )
    {
      case 0u:
        g_nGameState = 2;
        result = (int)CombatEnter();
        break;
      case 6u:
        g_nGameState = 3;
        break;
      case 9u:
      case 0xDu:
      case 0xEu:
        g_nGameState = 1;
        break;
      case 0xAu:
        g_nGameState = 4;
        break;
      case 0xBu:
        g_nGameState = 5;
        break;
      case 0xCu:
        g_nGameState = 6;
        break;
      case 0xFu:
        g_nGameState = 9;
        result = (int)CombatEnter();
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004502B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_377()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00450690
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_378()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004509F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_379()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00450D50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_380()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004517D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_381()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00451C40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_382()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00452510
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_383()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00452720
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_384()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00452F60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_385()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00453CA0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_386()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004547C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_387()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00456A40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_388()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00457230
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_389()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00459000
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_390()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0045A740
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_391()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0046D0D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_392()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004709F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_393()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00478810
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_394()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00478BD0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_395()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00479290
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_396()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0047BB80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_397()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0047C520
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_398()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0047DC30
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_399()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0047E536
BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  return 1;
}

// 0x0047E540
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_400()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00482E60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_401()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00486780
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_402()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00490980
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_403()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004987B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_404()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004A1280
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_405()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004A1530
// between_std_methods (0x44BDA0-0x4A7690)
int __thiscall UIWnd_SetByte(UIWnd *_this, char value)
{
  *((_BYTE *)_this + 1365) = value;
  if ( *((_DWORD *)_this + 331) )
  {
    if ( *((_DWORD *)_this + 331) == 2 )
    {
      (**((void (__thiscall ***)(char *, int))_this + 76))((char *)_this + 304, 1);
      (**((void (__thiscall ***)(char *, int))_this + 114))((char *)_this + 456, 1);
      (**((void (__thiscall ***)(char *, int))_this + 158))((char *)_this + 632, 1);
      (**((void (__thiscall ***)(char *, int))_this + 244))((char *)_this + 976, 1);
      *((_BYTE *)_this + 732) = 0;
      *((_BYTE *)_this + 1076) = 0;
    }
    else if ( *((_DWORD *)_this + 331) == 3 )
    {
      (**((void (__thiscall ***)(char *, int))_this + 28))((char *)_this + 112, 1);
    }
  }
  else
  {
    (**((void (__thiscall ***)(char *, int))_this + 76))((char *)_this + 304, 1);
    (**((void (__thiscall ***)(char *, int))_this + 114))((char *)_this + 456, 1);
    (**((void (__thiscall ***)(char *, int))_this + 158))((char *)_this + 632, 1);
    *((_BYTE *)_this + 732) = 0;
  }
  ++dword_DE5CE4;
  *((_DWORD *)_this + 17) = 1;
  *((_BYTE *)_this + 1364) = 0;
  *((_BYTE *)_this + 1341) = 1;
  *((_BYTE *)_this + 1340) = 1;
  return UIWnd::Destroy(_this, 1);
}

// 0x004A1DD0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_406()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004A2BD0
// between_std_methods (0x44BDA0-0x4A7690)
UIWnd *__thiscall UIWnd_GetChild(UIWnd *_this, int index)
{
  int v2; // edi
  int v4; // ecx
  char *v5; // edi
  int v6; // esi
  int v7; // edx
  UIWnd **v8; // edi
  UIWnd *result; // eax
  int v11; // [esp+20h] [ebp-20h]
  int v12; // [esp+30h] [ebp-10h] BYREF
  int v13; // [esp+34h] [ebp-Ch]
  _DWORD v14[2]; // [esp+38h] [ebp-8h] BYREF
  int *v15; // [esp+48h] [ebp+8h]
  int id; // [esp+4Ch] [ebp+Ch] BYREF
  int v17; // [esp+50h] [ebp+10h] BYREF

  if ( index <= 5 )
  {
    v11 = v2;
    v4 = *v15;
    v13 = v15[1];
    v14[1] = v13 + 12;
    v12 = v4;
    v14[0] = v4 + 85;
    v5 = (char *)_this + 3788 * index;
    (*(void (__thiscall **)(char *, _DWORD, int *, UIWnd *, int))(*((_DWORD *)v5 + 38937) + 16))(
      v5 + 155748,
      *(&off_56F02C + index),
      &v12,
      _this,
      v11);
    UIWnd::GetChildCount((UIWnd **)v5 + 38937, aUiGamemainuiCo_34, g_bConsoleOpen);
    UIWnd::GetChildAt((UIWnd **)v5 + 38937, aUiGamemainuiCo_35, g_bConsoleOpen);
    *((_DWORD *)v5 + 38955) = 1;
    v5[155918] = -30;
    v5[155917] = -51;
    v5[155916] = 58;
    v5[155919] = -1;
    SetIntParam(v5 + 155748, 4);
    UIWnd::GetWidth((UIWnd *)(v5 + 155748), -4);
    UIWnd::SetFrameRate((UIWnd *)(v5 + 155748), 1);
    UIWnd::GetPosition((UIWnd *)(v5 + 155748), -3);
    (*(void (__thiscall **)(char *, _DWORD, _DWORD *, UIWnd *))(*((_DWORD *)v5 + 39211) + 16))(
      v5 + 156844,
      *(&off_56F02C + index),
      v14,
      _this);
    UIWnd::GetChildCount((UIWnd **)v5 + 39211, aUiGamemainuiCo_34, g_bConsoleOpen);
    UIWnd::GetChildAt((UIWnd **)v5 + 39211, aUiGamemainuiCo_36, g_bConsoleOpen);
    *((_DWORD *)v5 + 39229) = 1;
    v5[157014] = -30;
    v5[157013] = -51;
    v5[157012] = 58;
    v5[157015] = -1;
    SetIntParam(v5 + 156844, 4);
    UIWnd::GetWidth((UIWnd *)(v5 + 156844), -4);
    UIWnd::SetFrameRate((UIWnd *)(v5 + 156844), 1);
    UIWnd::GetPosition((UIWnd *)(v5 + 156844), -3);
    (*(void (__thiscall **)(char *, _DWORD, _DWORD *, UIWnd *))(*((_DWORD *)v5 + 39074) + 16))(
      v5 + 156296,
      *(&off_56F02C + index),
      v14,
      _this);
    UIWnd::GetChildCount((UIWnd **)v5 + 39074, aUiGamemainuiCo_34, g_bConsoleOpen);
    UIWnd::GetChildAt((UIWnd **)v5 + 39074, aUiGamemainuiCo_37, g_bConsoleOpen);
    *((_DWORD *)v5 + 39092) = 1;
    v5[156466] = -30;
    v5[156465] = -51;
    v5[156464] = 58;
    v5[156467] = -1;
    SetIntParam(v5 + 156296, 4);
    UIWnd::GetWidth((UIWnd *)(v5 + 156296), -4);
    UIWnd::SetFrameRate((UIWnd *)(v5 + 156296), 1);
    UIWnd::GetPosition((UIWnd *)(v5 + 156296), -3);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v5 + 38998) + 16))(
      v5 + 155992,
      *(&off_56F02C + index),
      v17,
      _this);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&id + 1) = 3103;
      LOBYTE(id) = 0;
    }
    else
    {
      *(_WORD *)((char *)&id + 1) = 31;
      LOBYTE(id) = 12;
    }
    HIBYTE(id) = -1;
    UIWnd::GetChild((UIWnd *)v5 + 2294, (int)&id);
    v6 = v17;
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v5 + 39272) + 16))(
      v5 + 157088,
      *(&off_56F02C + index),
      v17,
      _this);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&v17 + 1) = 3103;
      LOBYTE(v17) = 0;
    }
    else
    {
      *(_WORD *)((char *)&v17 + 1) = 31;
      LOBYTE(v17) = 12;
    }
    HIBYTE(v17) = -1;
    UIWnd::GetChild((UIWnd *)(v5 + 157088), (int)&v17);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v5 + 39135) + 16))(
      v5 + 156540,
      *(&off_56F02C + index),
      v6,
      _this);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&v17 + 1) = 3103;
      LOBYTE(v17) = 0;
    }
    else
    {
      *(_WORD *)((char *)&v17 + 1) = 31;
      LOBYTE(v17) = 12;
    }
    HIBYTE(v17) = -1;
    UIWnd::GetChild((UIWnd *)(v5 + 156540), (int)&v17);
    (*(void (__thiscall **)(char *, _DWORD))(*((_DWORD *)v5 + 38785) + 16))(v5 + 155140, *(&off_56F02C + index));
    UIWnd::CreateFromTemplate((UIWnd **)v5 + 38785, aUiGamemainuiCo_33, g_bConsoleOpen);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v5 + 38823) + 16))(
      v5 + 155292,
      *(&off_56F02C + index),
      v6,
      _this);
    UIWnd::CreateFromTemplate((UIWnd **)v5 + 38823, &aUiGamemainuiCo_0[256 * index], g_bConsoleOpen);
    v7 = *((_DWORD *)v5 + 38861);
    v8 = (UIWnd **)(v5 + 155444);
    (*(void (__thiscall **)(UIWnd **, _DWORD, int, UIWnd *))(v7 + 16))(v8, *(&off_56F02C + index), v6, _this);
    UIWnd::CreateFromTemplate(v8, (&off_56F018)[index], g_bConsoleOpen);
    return (UIWnd *)UIWnd::SetShow((UIWnd *)v8, 0);
  }
  return result;
}

// 0x004A2F90
// between_std_methods (0x44BDA0-0x4A7690)
UIWnd *__thiscall UIWnd_FindChild(UIWnd *_this, int id)
{
  int v2; // ebx
  int v3; // ebp
  int v4; // esi
  int v6; // ebx
  char *v7; // ebp
  int v8; // edx
  UIWnd *v9; // ebp
  UIWnd *result; // eax
  int v11; // [esp+64h] [ebp-10h]
  int v12; // [esp+68h] [ebp-Ch]
  int v13; // [esp+7Ch] [ebp+8h]
  int ida; // [esp+80h] [ebp+Ch] BYREF

  v4 = id;
  if ( id <= 5 )
  {
    v12 = v2;
    v6 = v13;
    v11 = v3;
    v7 = (char *)_this + 3788 * id;
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *, int, int))(*((_DWORD *)v7 + 39310) + 16))(
      v7 + 157240,
      *(&off_56F02C + id),
      v13,
      _this,
      v11,
      v12);
    UIWnd::CreateFromTemplate((UIWnd **)v7 + 39310, aUiGamemainuiSt_2, g_bConsoleOpen);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v7 + 39348) + 16))(
      v7 + 157392,
      *(&off_56F02C + v4),
      v6,
      _this);
    UIWnd::CreateFromTemplate((UIWnd **)v7 + 39348, &aUiGamemainuiSt_0[256 * v4], g_bConsoleOpen);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v7 + 39386) + 16))(
      v7 + 157544,
      *(&off_56F02C + v4),
      v6,
      _this);
    UIWnd::SetShow((UIWnd *)(v7 + 157544), 0);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&ida + 1) = 3103;
      LOBYTE(ida) = 0;
    }
    else
    {
      *(_WORD *)((char *)&ida + 1) = 31;
      LOBYTE(ida) = 12;
    }
    HIBYTE(ida) = -1;
    UIWnd::GetChild((UIWnd *)(v7 + 157544), (int)&ida);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v7 + 39424) + 16))(
      v7 + 157696,
      *(&off_56F02C + v4),
      v6,
      _this);
    UIWnd::SetShow((UIWnd *)(v7 + 157696), 0);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&ida + 1) = 3103;
      LOBYTE(ida) = 0;
    }
    else
    {
      *(_WORD *)((char *)&ida + 1) = 31;
      LOBYTE(ida) = 12;
    }
    HIBYTE(ida) = -1;
    UIWnd::GetChild((UIWnd *)(v7 + 157696), (int)&ida);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v7 + 39462) + 16))(
      v7 + 157848,
      *(&off_56F02C + v4),
      v6,
      _this);
    UIWnd::SetShow((UIWnd *)(v7 + 157848), 0);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&ida + 1) = 3103;
      LOBYTE(ida) = 0;
    }
    else
    {
      *(_WORD *)((char *)&ida + 1) = 31;
      LOBYTE(ida) = 12;
    }
    HIBYTE(ida) = -1;
    UIWnd::GetChild((UIWnd *)(v7 + 157848), (int)&ida);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v7 + 39500) + 16))(
      v7 + 158000,
      *(&off_56F02C + v4),
      v6,
      _this);
    UIWnd::SetShow((UIWnd *)(v7 + 158000), 0);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&ida + 1) = 3103;
      LOBYTE(ida) = 0;
    }
    else
    {
      *(_WORD *)((char *)&ida + 1) = 31;
      LOBYTE(ida) = 12;
    }
    HIBYTE(ida) = -1;
    UIWnd::GetChild((UIWnd *)(v7 + 158000), (int)&ida);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v7 + 39538) + 16))(
      v7 + 158152,
      *(&off_56F02C + v4),
      v6,
      _this);
    UIWnd::SetShow((UIWnd *)(v7 + 158152), 0);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&ida + 1) = 3103;
      LOBYTE(ida) = 0;
    }
    else
    {
      *(_WORD *)((char *)&ida + 1) = 31;
      LOBYTE(ida) = 12;
    }
    HIBYTE(ida) = -1;
    UIWnd::GetChild((UIWnd *)(v7 + 158152), (int)&ida);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v7 + 39614) + 16))(
      v7 + 158456,
      *(&off_56F02C + v4),
      v6,
      _this);
    UIWnd::SetShow((UIWnd *)(v7 + 158456), 0);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&ida + 1) = 3103;
      LOBYTE(ida) = 0;
    }
    else
    {
      *(_WORD *)((char *)&ida + 1) = 31;
      LOBYTE(ida) = 12;
    }
    HIBYTE(ida) = -1;
    UIWnd::GetChild((UIWnd *)(v7 + 158456), (int)&ida);
    (*(void (__thiscall **)(char *, _DWORD, int, UIWnd *))(*((_DWORD *)v7 + 39576) + 16))(
      v7 + 158304,
      *(&off_56F02C + v4),
      v6,
      _this);
    UIWnd::SetShow((UIWnd *)v7 + 2328, 0);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&ida + 1) = 3103;
      LOBYTE(ida) = 0;
    }
    else
    {
      *(_WORD *)((char *)&ida + 1) = 31;
      LOBYTE(ida) = 12;
    }
    HIBYTE(ida) = -1;
    UIWnd::GetChild((UIWnd *)v7 + 2328, (int)&ida);
    v8 = *((_DWORD *)v7 + 39652);
    v9 = (UIWnd *)(v7 + 158608);
    (*(void (__thiscall **)(UIWnd *, _DWORD))(v8 + 16))(v9, *(&off_56F02C + v4));
    UIWnd::SetShow(v9, 0);
    if ( gbColorQuad::ColorQuadFmt )
    {
      *(_WORD *)((char *)&id + 1) = 3103;
      LOBYTE(id) = 0;
    }
    else
    {
      *(_WORD *)((char *)&id + 1) = 31;
      LOBYTE(id) = 12;
    }
    HIBYTE(id) = -1;
    return (UIWnd *)UIWnd::GetChild(v9, (int)&id);
  }
  return result;
}

// 0x004A66C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_407()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004AFD50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_408()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004B45B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_409()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004B4620
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_410()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004B4690
// between_std_methods (0x4A7690-0x4BEF50)
// write access to const memory has been detected, the output may be wrong!
void __thiscall UIObj_Reset(UIWnd *_this)
{
  _this->m_rect_left = 0;
  _this->m_rect_top = 0;
  _this->m_rect_right = 0;
  _this->m_rect_bottom = 0;
  _this->m_pfather = (UIWnd *)100;
  _this->m_childs_data = (void *)200;
  LOBYTE(_this->m_childs_count) = 0;
  BYTE1(_this->m_childs_count) = 1;
  _this->m_childs_capacity = 0;
  _this->m_childs_elemsize = 0;
  _this->m_bcreateok = 0;
  _this->m_bvisible = 0;
  _this->m_benable = 0;
  LOBYTE(_this->m_bfocus) = 1;
  *((_DWORD *)_this + 17) = 0;
  *((_DWORD *)_this + 18) = 0;
  *((_DWORD *)_this + 19) = 2;
  *((_BYTE *)_this + 80) = 1;
  *((_BYTE *)_this + 88) = 0;
  *((_DWORD *)_this + 23) = 0;
  *((_DWORD *)_this + 24) = 0;
  *((_DWORD *)_this + 25) = 0;
  *((_BYTE *)_this + 104) = 1;
  *((_BYTE *)_this + 116) = 0;
  *((_DWORD *)_this + 28) = 0;
  *((_DWORD *)_this + 27) = 0;
  *((_DWORD *)_this + 30) = 10;
  *((_BYTE *)_this + 128) = 0;
  *((_DWORD *)_this + 33) = 1065353216;
  *((_DWORD *)_this + 34) = 0;
  *((_DWORD *)_this + 35) = 0;
  *((_DWORD *)_this + 36) = 0;
  *((_DWORD *)_this + 37) = 0;
  *((_DWORD *)_this + 38) = 0;
  *((_DWORD *)_this + 39) = 0;
  *((_DWORD *)_this + 104) = 0;
  UIFrameWnd::UIFrameWnd((UIFrameWnd *)((char *)_this + 420));
  *((_DWORD *)_this + 143) = 0;
  *((_DWORD *)_this + 144) = 0;
  *((_DWORD *)_this + 145) = 1058642330;
  *((_DWORD *)_this + 31) = -16777216;
  _this->m_fontcolor = 100;
  _this->_vftable = (void **)100;
  _this->m_wndcolor = 200;
  _this->m_id = 400;
  gbColorQuad::ColorQuadFmt = 1;
  *((_DWORD *)_this + 21) = -16777216;
}

// 0x004B47E0
// between_std_methods (0x4A7690-0x4BEF50)
void __thiscall UIFrameWnd_Destructor_4B47E0(UIWnd *_this)
{
  UIFrameWnd::_UIFrameWnd((UIFrameWnd *)((char *)_this + 420));
}

// 0x004B6390
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_411()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004B64E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_412()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004B6CB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_415()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004B7050
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_418()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004B7430
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_421()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004B7BC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_422()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004B81D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_423()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004BC6F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_424()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004BD800
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_425()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004BD9F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_426()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004BDF80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_429()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004BE9F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_432()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004BEB40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_433()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004BEC90
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_434()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004BEDF0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_435()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004BF6F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_436()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004C1520
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_439()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004C2000
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_440()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004C2790
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_441()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004C33D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_442()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004C3C40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_443()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004C57D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_444()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004C6450
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
void __cdecl unknown_libname_446()
{
  `eh vector destructor iterator'((char *)&stru_DE93B0.m_DefaultUVSet[2].ev, 0x60u, 8, gbTexture_D3D::~gbTexture_D3D);
}

// 0x004C6840
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_447()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004C8880
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_448()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004C9500
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_449()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004CB310
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_450()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004CD9C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_451()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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

// 0x004CEAF0
// between_std_methods (0x4C2840-0x4D70B0)
char __thiscall _E68(_DWORD *_this)
{
  int v2; // ebx
  _DWORD *v3; // esi
  char result; // al
  _DWORD *v5; // ecx

  v2 = 2048;
  v3 = _this + 587;
  do
  {
    result = *((_BYTE *)v3 - 4);
    if ( result )
    {
      result = *((_BYTE *)v3 - 3);
      if ( result )
      {
        (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v3 + 12))(*v3);
        if ( !*((_BYTE *)v3 - 2) )
        {
          if ( *v3 )
            (**(void (__thiscall ***)(_DWORD, int))*v3)(*v3, 1);
        }
        v5 = v3 - 4;
        --*(_this + 10823);
        result = 0;
        *v3 = 0;
        *v5 = 0;
        v5[1] = 0;
        v5[2] = 0;
        v5[3] = 0;
        *v3 = 0;
      }
    }
    v3 += 5;
    --v2;
  }
  while ( v2 );
  return result;
}

// 0x004CFC40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_452()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D0C60
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_453()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D0CB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_454()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D31F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_455()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D3830
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_456()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D4DB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_457()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D4E00
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_458()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D4E30
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_459()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D5820
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_460()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D5870
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_461()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D5A40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_462()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D6600
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_463()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004D6E30
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_464()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004DBF10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_466()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004DF460
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_467()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004E0080
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_468()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x004F2C30
// between_std_methods (0x4D70B0-0x504E20)
void *__thiscall CCBRoleState_GetRole(CCBRoleState *_this, int index)
{
  char v3; // [esp+8h] [ebp+8h]

  if ( v3 == 1 )
    return (void *)*(&_this->m_Role[0].nFullMP + 223 * index);
  else
    return (void *)*(&_this->m_Role[0].nMP + 223 * index);
}

// 0x004F4AA0
// between_std_methods (0x4D70B0-0x504E20)
CCBStageRole *__thiscall CCBStage_GetRole(CCBStage *_this, int index)
{
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int *i; // eax
  int RoleNum; // eax
  _DWORD v9[11]; // [esp+Ch] [ebp-2Ch] BYREF
  int a2; // [esp+40h] [ebp+8h]

  memset(v9, 0, sizeof(v9));
  v3 = CCBRoleState::GetRoleHP((CCBRoleState *)_this, index) - 1;
  if ( v3 )
  {
    if ( v3 == 1 )
    {
      v4 = PAL_GDB::~PAL_GDB(&g_GDB, *((_DWORD *)&_this->m_Task[0].SubTask[2].param.f3 + 223 * index));
      v5 = 0;
      for ( i = (int *)(v4 + 760); a2 != *i; ++i )
      {
        if ( ++v5 >= 4 )
          return 0;
      }
      RoleNum = PAL_GDB::GDB_GetRoleNum(&g_GDB, *i);
      return (CCBStageRole *)*(__int16 *)(RoleNum + 592);
    }
    return 0;
  }
  v9[2] = index;
  v9[0] = 261;
  v9[1] = a2;
  LOBYTE(v9[10]) = 1;
  if ( !sub_4F6DA0(_this, v9) )
  {
    v9[0] = 260;
    if ( !sub_4F6DA0(_this, v9) )
      return 0;
  }
  RoleNum = PAL_GDB::GDB_GetRoleNum(&g_GDB, a2);
  return (CCBStageRole *)*(__int16 *)(RoleNum + 592);
}

// 0x004FA930
// between_std_methods (0x4D70B0-0x504E20)
char __thiscall CCBStage_Method_4FA930(CCBRoleState *_this, char arg0, int a2)
{
  int v3; // ebx
  char result; // al
  unsigned __int8 *v6; // ecx
  unsigned __int8 *v7; // eax
  unsigned int v8; // edi
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // edi
  int v26; // eax
  int v27; // edi
  int v28; // eax
  unsigned __int8 *v29; // edi
  unsigned __int8 v30; // al
  int *v31; // eax
  bool v32; // cc
  unsigned __int8 *v33; // edi
  int *v34; // eax
  int v35; // ecx
  int v36; // eax
  int v37; // eax
  _BYTE *v38; // ecx
  unsigned __int8 v39; // al
  int v40; // ecx
  bool v41; // zf
  int *v42; // eax
  int v43; // ecx
  int v44; // eax
  int v45; // eax
  int v46; // eax
  char *v47; // eax
  int v48; // eax
  int v49; // ecx
  int *v50; // eax
  int v51; // ecx
  int v52; // eax
  int v53; // eax
  unsigned __int8 *v54; // edx
  int v55; // edx
  int a7; // [esp+Ch] [ebp-50h] BYREF
  int v57; // [esp+10h] [ebp-4Ch]
  int v58; // [esp+14h] [ebp-48h]
  unsigned __int8 *v59; // [esp+18h] [ebp-44h]
  int v60; // [esp+1Ch] [ebp-40h]
  int v61; // [esp+20h] [ebp-3Ch]
  int v62; // [esp+24h] [ebp-38h]
  int v63; // [esp+28h] [ebp-34h]
  int v64; // [esp+2Ch] [ebp-30h]
  int v65; // [esp+30h] [ebp-2Ch]
  int v66; // [esp+34h] [ebp-28h]
  int *RoleNum; // [esp+38h] [ebp-24h]
  int v68; // [esp+3Ch] [ebp-20h]
  char *v69; // [esp+40h] [ebp-1Ch]
  int v70; // [esp+44h] [ebp-18h]
  int v71; // [esp+48h] [ebp-14h]
  int v72; // [esp+4Ch] [ebp-10h] BYREF
  unsigned __int8 *p_bAlive; // [esp+50h] [ebp-Ch]
  int v74; // [esp+54h] [ebp-8h]
  int v75; // [esp+58h] [ebp-4h] BYREF
  int v76; // [esp+64h] [ebp+8h]
  int v77; // [esp+64h] [ebp+8h]
  int v78; // [esp+64h] [ebp+8h]
  int *v79; // [esp+64h] [ebp+8h]
  char v80; // [esp+67h] [ebp+Bh]

  v3 = 0;
  v70 = 0;
  v71 = 0;
  v69 = 0;
  v75 = -1;
  if ( arg0 )
  {
    CCBRoleState::GetRoleMP(_this, 2);
    v68 = v70;
    CCBRoleState::Update(_this, 1);
    return CCBRoleState::GetRoleMP(_this, 1);
  }
  else
  {
    v68 = 0;
    p_bAlive = &_this->m_Role[0].bAlive;
    v6 = &_this->m_Role[0].bAlive;
    v65 = 0;
    v69 = &g_SceneMgr.m_slot0[8];
    v61 = -578 - (_DWORD)_this;
    do
    {
      if ( *(v6 - 1) && *v6 )
      {
        v7 = p_bAlive;
        v8 = *(_DWORD *)(p_bAlive + 130) + *(_DWORD *)(p_bAlive + 126);
        *(_DWORD *)(p_bAlive + 126) = v8;
        v76 = *(_DWORD *)(v7 + 6);
        v9 = sub_4FA4E0((unsigned int *)_this, v8);
        v74 = v9;
        if ( v9 > v76 )
        {
          a7 = v3;
          v57 = v9;
          CCBStage::GetRoleName(_this->m_pStage, a2, (int)sub_5025C0, 0, 0, 0, &a7, -1082130432, 1084227584);
          *(_DWORD *)(p_bAlive + 6) = v9;
          v62 = sub_4FA210(v3, v76);
          v10 = sub_4FA210(v3, v9);
          *((_DWORD *)v69 - 1) += v10 - v62;
          v11 = sub_4FA280(v3, v76);
          v12 = sub_4FA280(v3, v74);
          *(_DWORD *)v69 += v12 - v11;
          v13 = sub_4FA330(v3, v76);
          v14 = sub_4FA330(v3, v74);
          *((_DWORD *)v69 + 1) += v14 - v13;
          v15 = sub_4FA3A0(v3, v76);
          v16 = sub_4FA3A0(v3, v74);
          *((_DWORD *)v69 + 2) += v16 - v15;
          v17 = sub_4FA440(v3, v76);
          v18 = sub_4FA440(v3, v74);
          *((_DWORD *)v69 + 3) += v18 - v17;
          v19 = sub_4FA210(v3, v76);
          v20 = sub_4FA210(v3, v74);
          *(_DWORD *)(p_bAlive + 14) += v20 - v19;
          v21 = sub_4FA280(v3, v76);
          v22 = sub_4FA280(v3, v74);
          *(_DWORD *)(p_bAlive + 22) += v22 - v21;
          v23 = sub_4FA330(v3, v76);
          v24 = sub_4FA330(v3, v74);
          *(_DWORD *)(p_bAlive + 30) += v24 - v23;
          v25 = sub_4FA3A0(v3, v76);
          v26 = sub_4FA3A0(v3, v74);
          *(_DWORD *)(p_bAlive + 34) += v26 - v25;
          v27 = sub_4FA440(v3, v76);
          v28 = sub_4FA440(v3, v74) - v27;
          v29 = p_bAlive;
          v77 = 0;
          *(_DWORD *)(p_bAlive + 38) += v28;
          *(_DWORD *)(v29 + 10) = *(_DWORD *)(v29 + 14);
          *(_DWORD *)(v29 + 18) = *(_DWORD *)(v29 + 22);
          *(_DWORD *)(v29 + 26) = *(_DWORD *)(v29 + 30);
          RoleNum = (int *)(v29 + 134);
          do
          {
            if ( *RoleNum )
            {
              if ( !v29[v77 + 158] )
              {
                v30 = *(_BYTE *)(PAL_GDB::GDB_GetRoleNum(&g_GDB, *RoleNum) + 713);
                if ( v30 )
                {
                  if ( v74 >= v30 )
                  {
                    v31 = RoleNum;
                    a7 = v3;
                    v29[v77 + 158] = 1;
                    v57 = *v31;
                    CCBStage::GetRoleName(_this->m_pStage, a2, (int)sub_502950, 0, 0, 0, &a7, -1082130432, 1084227584);
                  }
                }
              }
            }
            v32 = ++v77 < 6;
            ++RoleNum;
          }
          while ( v32 );
        }
        v33 = &p_bAlive[v61];
        do
        {
          v64 = 6;
          v34 = (int *)(p_bAlive + 166);
          v78 = (int)(p_bAlive + 454);
          v62 = (int)v34;
          v63 = -48 - (_DWORD)_this;
          do
          {
            v35 = 0;
            v66 = (int)v34;
            v74 = 0;
            do
            {
              v36 = *v34;
              if ( v36 )
              {
                if ( *(_BYTE *)(v78 + v35 - 96) )
                {
                  RoleNum = (int *)PAL_GDB::GDB_GetRoleNum(&g_GDB, v36);
                  if ( *(unsigned __int8 *)(v78 + v74) < 3u
                    && *((_BYTE *)RoleNum + *(unsigned __int8 *)(v78 + v74) + 710) <= *(_BYTE *)(v78 + v74 - 48) )
                  {
                    v37 = 2;
                    v38 = RoleNum + 178;
                    while ( _this->m_sCombatDialog[v74 + v78 + v63] < *v38 )
                    {
                      --v37;
                      --v38;
                      if ( v37 < 0 )
                        goto LABEL_26;
                    }
                    v39 = v37 + 1;
                    *(_BYTE *)(v78 + v74) = v39;
                    a7 = v3;
                    v40 = *(_DWORD *)v66;
                    v58 = v39 + 1;
                    v57 = v40;
                    CCBStage::GetRoleName(_this->m_pStage, a2, (int)sub_502CC0, 0, 0, 0, &a7, -1082130432, 1084227584);
                  }
                }
              }
LABEL_26:
              v35 = v74 + 1;
              v34 = (int *)(v66 + 4);
              v32 = ++v74 < 8;
              v66 += 4;
            }
            while ( v32 );
            v41 = v64 == 1;
            v78 += 8;
            --v64;
          }
          while ( !v41 );
          v63 = 6;
          v59 = v33 + 1032;
          v66 = (int)(v33 + 1032);
          v42 = (int *)v62;
          do
          {
            v43 = 0;
            v64 = (int)v42;
            v74 = 0;
            do
            {
              v44 = *v42;
              if ( v44 && _this->m_sCombatDialog[v43 - 96 + v66] )
              {
                v45 = PAL_GDB::GDB_GetRoleNum(&g_GDB, v44);
                RoleNum = (int *)(v45 + 754);
                v79 = (int *)(v45 + 724);
                v60 = -754 - v45;
                do
                {
                  if ( *v79 )
                  {
                    if ( *((unsigned __int8 *)RoleNum - 3) <= (unsigned __int8)_this->m_sCombatDialog[v74 + v66] + 1
                      && *(unsigned __int8 *)RoleNum <= *(int *)(p_bAlive + 6) )
                    {
                      v46 = v79[3];
                      if ( v46 )
                      {
                        if ( sub_4F6C60(_this->m_sCombatDialog, v3, v46, &v72, &v75) )
                        {
                          if ( v33[8 * v72 + 936 + v75 + (_DWORD)_this] )
                          {
                            if ( *((unsigned __int8 *)RoleNum - 6) <= v33[8 * v72 + 1032 + v75 + (_DWORD)_this] + 1 )
                            {
                              if ( sub_4F6C60(_this->m_sCombatDialog, v3, *v79, &v72, &v75) )
                              {
                                v47 = (char *)&v33[8 * v72 + 936 + v75 + (_DWORD)_this];
                                if ( !*v47 )
                                {
                                  *v47 = 1;
                                  v33[8 * v72 + 1032 + v75 + (_DWORD)_this] = 0;
                                  v48 = v65;
                                  v33[8 * v72 + 984 + v75 + (_DWORD)_this] = 0;
                                  a7 = v3;
                                  v57 = *(_DWORD *)&_this->m_Role[0]._rest[32 * v72 + 116 + 4 * v75 + 4 * v48];
                                  CCBStage::GetRoleName(
                                    _this->m_pStage,
                                    a2,
                                    (int)sub_502950,
                                    0,
                                    0,
                                    0,
                                    &a7,
                                    -1082130432,
                                    1084227584);
                                  v3 = v68;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                  ++v79;
                  v49 = (int)RoleNum + v60 + 1;
                  RoleNum = (int *)((char *)RoleNum + 1);
                }
                while ( v49 < 3 );
              }
              v43 = v74 + 1;
              v42 = (int *)(v64 + 4);
              v32 = ++v74 < 8;
              v64 += 4;
            }
            while ( v32 );
            v41 = v63 == 1;
            v66 += 8;
            --v63;
          }
          while ( !v41 );
          v50 = (int *)v62;
          v80 = 0;
          v66 = (int)v59;
          v63 = 6;
          do
          {
            v51 = 0;
            v62 = (int)v50;
            v74 = 0;
            do
            {
              v52 = *v50;
              if ( v52 )
              {
                if ( _this->m_sCombatDialog[v51 - 96 + v66] )
                {
                  v53 = PAL_GDB::GDB_GetRoleNum(&g_GDB, v52);
                  v59 = *(unsigned __int8 **)(v53 + 716);
                  if ( v59 )
                  {
                    if ( *(unsigned __int8 *)(v53 + 714) <= (unsigned __int8)_this->m_sCombatDialog[v74 + v66] + 1
                      && *(unsigned __int8 *)(v53 + 713) <= *(int *)(p_bAlive + 6) )
                    {
                      sub_4F6C60(_this->m_sCombatDialog, v3, (int)v59, &v72, &v75);
                      v54 = &v33[8 * v72 + 936 + v75];
                      if ( !_this->m_sCombatDialog[(_DWORD)v54] )
                      {
                        _this->m_sCombatDialog[(_DWORD)v54] = 1;
                        v80 = 1;
                        v33[8 * v72 + 1032 + v75 + (_DWORD)_this] = 0;
                        v55 = v65;
                        v33[8 * v72 + 984 + v75 + (_DWORD)_this] = 0;
                        a7 = v3;
                        v57 = *(_DWORD *)&_this->m_Role[0]._rest[32 * v72 + 116 + 4 * v75 + 4 * v55];
                        CCBStage::GetRoleName(
                          _this->m_pStage,
                          a2,
                          (int)sub_502950,
                          0,
                          0,
                          0,
                          &a7,
                          -1082130432,
                          1084227584);
                      }
                    }
                  }
                }
              }
              v51 = v74 + 1;
              v50 = (int *)(v62 + 4);
              v32 = ++v74 < 8;
              v62 += 4;
            }
            while ( v32 );
            v41 = v63 == 1;
            v66 += 8;
            --v63;
          }
          while ( !v41 );
        }
        while ( v80 );
      }
      result = (_BYTE)v69 + 0x80;
      ++v3;
      v6 = p_bAlive + 892;
      v32 = (int)(v69 + 1408) < (int)&g_SceneMgr.m_RoleSystem[0]._pad_200[64];
      v68 = v3;
      v69 += 1408;
      p_bAlive += 892;
      v65 += 223;
    }
    while ( v32 );
  }
  return result;
}

// 0x004FB750
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_470()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00503AE0
// between_std_methods (0x4D70B0-0x504E20)
int __thiscall CCBRoleState_Method_503AE0(void **_this, int a2, int a3, int a4)
{
  int v5; // edi
  void **v6; // ecx
  int v7; // esi

  v5 = 0;
  v6 = _this + 23;
  v7 = 2;
  *v6 = 0;
  v6[1] = 0;
  *((_WORD *)v6 + 4) = 0;
  *((_BYTE *)v6 + 10) = 0;
  do
  {
    if ( ((unsigned int)(__int64)pow(2.0, (double)(v7 - 1)) & a3) != 0 )
      ++v5;
    ++v7;
  }
  while ( v7 < 5 );
  if ( v5 <= 1 )
  {
    if ( (a3 & 1) != 0 )
      CCBRoleState::GetRoleMP((CCBRoleState *)*(_this + 1), 2);
    else
      CCBRoleState::GetRoleMP((CCBRoleState *)*(_this + 1), 1);
    return 0;
  }
  else
  {
    *((_BYTE *)_this + a2 + 92) = 1;
    return a2;
  }
}

// 0x00503D50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_471()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00509020
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_473()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0050FAB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_474()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00511BD0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_475()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x005122B0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_476()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00515E10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_477()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0051D550
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_478()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0051D6A0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_479()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00521FC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_480()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x005230C0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_481()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00523EC0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_482()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x005278E0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_484()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00528270
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_485()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00529580
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_486()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0052AE80
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_487()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0052B170
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_488()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
    Object3D::CaculateRelative((Object3D *)(v3 - 2), v6);
    if ( sub_537060((gbVisNode **)*v3) == 1 )
      Actor::CompareAction(*v3, (int)v3[35], 0);
    v3 += 38;
    --v4;
  }
  while ( v4 );
  Object3D::CaculateRelative((Object3D *)(_this + 214), v6);
  ObjectCamera::SetStepRotate((ObjectCamera *)*(_this + 3));
  return sub_52B030(*_this, a2);
}

// 0x0052B9A0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_489()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0052D740
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_490()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0052EC20
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_493()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00530200
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_495()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x005303D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_496()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00531CB0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_497()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x005329BE
BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  return 1;
}

// 0x005329D0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_498()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00533C40
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_499()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00534D50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_500()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00534EE0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_501()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00535A00
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_503()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x005361F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_504()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00536A10
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_505()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00537540
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_506()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0053C810
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_509()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0053CF30
// between_std_methods (0x53C2D0-0x541D1B)
char *__thiscall Texture_Info_53CF30(char *ArgList, const char *a2, const char *a3, const char *a4, int a5)
{
  *(ArgList + 1023) = 0;
  _snprintf(ArgList, 0x400u, "%s(%d):%s,%s", a4, a5, a2, a3);
  LogMessage("_Exception: %s\r\n", ArgList);
  return ArgList;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0053F1F0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_520()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0053FCF0
// between_std_methods (0x53C2D0-0x541D1B)
Scene *__thiscall _Texture_Info::_CalculateUV(int _this, LPCSTR lpString)
{
  int v3; // edi
  int v4; // ebx
  char pExceptionObject[1024]; // [esp+10h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+410h] [ebp-400h] BYREF

  if ( !*(_BYTE *)(_this + 532) || lstrlenA(lpString) <= 0 )
    return (Scene *)g_SceneMgr.m_szUIString;
  v3 = 0;
  if ( *(int *)(_this + 524) <= 0 )
  {
LABEL_7:
    qmemcpy(
      pExceptionObject,
      Texture_Info_53CF30(ArgList, aNotFoundSInUiO, lpString, aDProjectPal3Ui_0, 552),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v4 = 0;
  while ( _strcmpi(lpString, (const char *)(v4 + *(_DWORD *)(_this + 528))) )
  {
    ++v3;
    v4 += 1088;
    if ( v3 >= *(_DWORD *)(_this + 524) )
      goto LABEL_7;
  }
  return (Scene *)(1088 * v3 + *(_DWORD *)(_this + 528) + 512);
}

// 0x0053FE50
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_521()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x0053FFA0
// between_std_methods (0x53C2D0-0x541D1B)
void _TextureLib_Data::_TextureLib_Data()
{
  if ( g_PlayerHP )
  {
    gbRefObject::Release((gbRefObject *)g_PlayerHP);
    g_PlayerHP = 0;
  }
  if ( g_PlayerData_04C )
  {
    gbRefObject::Release((gbRefObject *)g_PlayerData_04C);
    g_PlayerData_04C = 0;
  }
  if ( g_PlayerMP )
  {
    gbRefObject::Release((gbRefObject *)g_PlayerMP);
    g_PlayerMP = 0;
  }
  if ( dword_189505C )
  {
    gbRefObject::Release((gbRefObject *)dword_189505C);
    dword_189505C = 0;
  }
  if ( dword_1895068 )
  {
    gbRefObject::Release((gbRefObject *)dword_1895068);
    dword_1895068 = 0;
  }
  if ( dword_1895050 )
  {
    gbRefObject::Release((gbRefObject *)dword_1895050);
    dword_1895050 = 0;
  }
  if ( g_PlayerGP )
  {
    gbRefObject::Release((gbRefObject *)g_PlayerGP);
    g_PlayerGP = 0;
  }
  if ( dword_1895060 )
  {
    gbRefObject::Release((gbRefObject *)dword_1895060);
    dword_1895060 = 0;
  }
  if ( dword_1895064 )
  {
    gbRefObject::Release((gbRefObject *)dword_1895064);
    dword_1895064 = 0;
  }
  if ( dword_189506C )
  {
    gbRefObject::Release((gbRefObject *)dword_189506C);
    dword_189506C = 0;
  }
}

// 0x00540070
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl _TextureLib_Data::~_TextureLib_Data(int a1, int a2, int a3, int a4, float *a5)
{
  gbDynVertBuf *DynVertBuf; // eax
  float v6[10]; // [esp+4h] [ebp-28h] BYREF

  v6[8] = 0.0;
  v6[0] = (float)a1;
  v6[9] = *a5;
  v6[3] = (float)a2;
  v6[2] = (float)a3;
  v6[1] = (float)a4;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x114u);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v6, 1, (struct gbRenderEffect *)dword_1895050, 0);
}

// 0x005400E0
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl _TextureLib_Data::_GetItemNum(int *a1, struct gbTextureArray *a2, int a3, int a4)
{
  float v4; // ecx
  gbTexture *v5; // ecx
  long double v6; // st7
  double v7; // st7
  struct gbRenderEffect *v8; // esi
  gbDynVertBuf *DynVertBuf; // eax
  float v10[4]; // [esp+8h] [ebp-28h] BYREF
  int v11; // [esp+18h] [ebp-18h]
  int v12; // [esp+1Ch] [ebp-14h]
  float v13; // [esp+20h] [ebp-10h]
  float v14; // [esp+24h] [ebp-Ch]
  int v15; // [esp+28h] [ebp-8h]
  int v16; // [esp+2Ch] [ebp-4h]
  int v17; // [esp+3Ch] [ebp+Ch]
  int v18; // [esp+3Ch] [ebp+Ch]
  float v19; // [esp+3Ch] [ebp+Ch]

  v16 = a3;
  v15 = 0;
  if ( a4 )
  {
    v11 = *(_DWORD *)(a4 + 1048);
    v12 = *(_DWORD *)(a4 + 1052);
    v4 = *(float *)(a4 + 1068);
    v13 = *(float *)(a4 + 1064);
    v14 = v4;
  }
  else
  {
    v5 = a2->pTexPt[0];
    v17 = a1[2] - *a1;
    v12 = 0;
    v11 = 0;
    v6 = (fabs((double)v17) + -0.5) / (double)v5->Width;
    v18 = a1[3] - a1[1];
    v13 = v6;
    v14 = (fabs((double)v18) + -0.5) / (double)v5->Height;
  }
  v7 = (double)(int)g_pGameTime;
  v8 = (struct gbRenderEffect *)g_PlayerHP;
  v10[0] = ((double)*a1 + (double)*a1) / v7 - 1.0;
  v19 = (float)(int)g_pAbsTime;
  v10[3] = 1.0 - ((double)a1[1] + (double)a1[1]) / v19;
  v10[2] = ((double)a1[2] + (double)a1[2]) / v7 - 1.0;
  v10[1] = 1.0 - ((double)a1[3] + (double)a1[3]) / v19;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x15u);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v10, 1, v8, a2);
}

// 0x00540210
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl _TextureLib_Data::_CheckItem(
        _DWORD *a1,
        int *a2,
        struct gbTextureArray *a3,
        int a4,
        unsigned int a5,
        float *a6)
{
  int v6; // edx
  float v7; // eax
  float v8; // ecx
  gbTexture *v9; // ecx
  unsigned int v10; // eax
  struct gbRenderEffect *v11; // esi
  double v12; // st7
  double v14; // st7
  __int64 v15; // rax
  double v16; // st7
  gbDynVertBuf *DynVertBuf; // eax
  __int64 v18; // [esp+10h] [ebp-30h]
  __int64 v19; // [esp+10h] [ebp-30h]
  float v20; // [esp+18h] [ebp-28h] BYREF
  float v21; // [esp+1Ch] [ebp-24h]
  float v22; // [esp+20h] [ebp-20h]
  float v23; // [esp+24h] [ebp-1Ch]
  int v24; // [esp+28h] [ebp-18h]
  int v25; // [esp+2Ch] [ebp-14h]
  float v26; // [esp+30h] [ebp-10h]
  float v27; // [esp+34h] [ebp-Ch]
  int v28; // [esp+38h] [ebp-8h]
  int v29; // [esp+3Ch] [ebp-4h]
  float v30; // [esp+48h] [ebp+8h]
  int v31; // [esp+50h] [ebp+10h]

  v28 = 0;
  v29 = a4;
  if ( a6 )
  {
    v6 = *((_DWORD *)a6 + 263);
    v7 = a6[266];
    v24 = *((_DWORD *)a6 + 262);
    v8 = a6[267];
    v25 = v6;
    v26 = v7;
    v27 = v8;
  }
  else
  {
    v9 = a3->pTexPt[0];
    v25 = 0;
    v24 = 0;
    v31 = a1[3] - a1[1];
    v26 = (fabs((double)(a1[2] - *a1)) + -0.5) / (double)v9->Width;
    v27 = (fabs((double)v31) + -0.5) / (double)v9->Height;
  }
  if ( (a5 & 0x100) != 0 )
  {
    v20 = (float)*a2;
    v23 = (double)a2[1] - 0.5;
    if ( a6 )
    {
      v10 = *((_DWORD *)a6 + 260);
      v18 = v10;
      *(float *)&v18 = a6[261];
      v11 = (struct gbRenderEffect *)g_PlayerData_04C;
      v22 = (double)v10 + v20 + 0.5;
      v12 = (double)v18 + v23 + 0.5;
    }
    else
    {
      v11 = (struct gbRenderEffect *)g_PlayerData_04C;
      v22 = (float)a2[2];
      v12 = (double)a2[3];
    }
    v21 = v12;
  }
  else
  {
    v14 = (double)(int)g_pGameTime;
    v20 = ((double)*a2 + (double)*a2) / v14 - 1.0;
    v30 = (float)(int)g_pAbsTime;
    v23 = 1.0 - ((double)a2[1] + (double)a2[1]) / v30;
    if ( a6 )
    {
      v15 = (__int64)((double)*((unsigned int *)a6 + 260) + v20 + 0.5);
      v19 = *((unsigned int *)a6 + 261);
      v22 = ((double)(int)v15 + (double)(int)v15) / v14 - 1.0;
      v16 = (double)(int)(__int64)((double)v19 + v23 + 0.5);
    }
    else
    {
      v22 = ((double)a2[2] + (double)a2[2]) / v14 - 1.0;
      v16 = (double)a2[3];
    }
    v11 = (struct gbRenderEffect *)g_PlayerHP;
    v21 = 1.0 - (v16 + v16) / v30;
  }
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, a5);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)&v20, 1, v11, a3);
}

// 0x00540440
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl _TextureLib_Data::SetLibFolder(
        int *a1,
        unsigned int *a2,
        struct gbTextureArray *a3,
        unsigned int a4,
        unsigned int *a5,
        float a6)
{
  __int64 v6; // rcx
  unsigned int v7; // ecx
  unsigned int v8; // edx
  unsigned int v9; // ecx
  gbTexture *v10; // ecx
  long double v11; // st7
  double v12; // st7
  struct gbRenderEffect *v13; // esi
  double v14; // st6
  __int64 v15; // rax
  double v16; // st5
  gbDynVertBuf *DynVertBuf; // eax
  __int64 v18; // [esp+10h] [ebp-30h]
  float v19; // [esp+18h] [ebp-28h] BYREF
  float v20; // [esp+1Ch] [ebp-24h]
  float v21; // [esp+20h] [ebp-20h]
  float v22; // [esp+24h] [ebp-1Ch]
  unsigned int v23; // [esp+28h] [ebp-18h]
  unsigned int v24; // [esp+2Ch] [ebp-14h]
  float v25; // [esp+30h] [ebp-10h]
  float v26; // [esp+34h] [ebp-Ch]
  int v27; // [esp+38h] [ebp-8h]
  int v28; // [esp+3Ch] [ebp-4h]
  int v29; // [esp+48h] [ebp+8h]
  int v30; // [esp+48h] [ebp+8h]
  float v31; // [esp+48h] [ebp+8h]
  float v32; // [esp+58h] [ebp+18h]

  v6 = *a2;
  v27 = 0;
  v28 = v6;
  if ( a5 )
  {
    v7 = a5[263];
    v23 = a5[262];
    v8 = a5[266];
    v24 = v7;
    v9 = a5[267];
    v25 = *(float *)&v8;
    v26 = *(float *)&v9;
  }
  else
  {
    v10 = a3->pTexPt[0];
    v29 = a1[2] - *a1;
    v24 = 0;
    v23 = 0;
    v11 = (fabs((double)v29) + -0.5) / (double)v10->Width;
    v30 = a1[3] - a1[1];
    v25 = v11;
    v26 = (fabs((double)v30) + -0.5) / (double)v10->Height;
  }
  if ( (a4 & 0x100) != 0 )
  {
    v12 = (double)*a1;
    v22 = (float)a1[1];
    if ( a5 == (unsigned int *)HIDWORD(v6) || LOBYTE(a6) == BYTE4(v6) )
    {
      v14 = (double)a1[2];
      v13 = (struct gbRenderEffect *)g_PlayerData_04C;
      v20 = (float)a1[3];
    }
    else
    {
      LODWORD(v6) = a5[261];
      v13 = (struct gbRenderEffect *)g_PlayerData_04C;
      v14 = (double)a5[260] + v12;
      v20 = (double)v6 + v22;
    }
  }
  else
  {
    v32 = (float)(int)g_pGameTime;
    v12 = ((double)*a1 + (double)*a1) / v32 - 1.0;
    v31 = (float)(int)g_pAbsTime;
    v22 = 1.0 - ((double)a1[1] + (double)a1[1]) / v31;
    if ( a5 == (unsigned int *)HIDWORD(v6) )
    {
      v14 = ((double)a1[2] + (double)a1[2]) / v32 - 1.0;
      v16 = (double)a1[3];
    }
    else
    {
      v15 = (__int64)((double)__SPAIR64__(HIDWORD(v6), a5[260]) + v12);
      LODWORD(v18) = a5[261];
      HIDWORD(v18) = HIDWORD(v6);
      v14 = ((double)(int)v15 + (double)(int)v15) / v32 - 1.0;
      v16 = (double)(int)(__int64)((double)v18 + v22);
    }
    v13 = (struct gbRenderEffect *)g_PlayerHP;
    v20 = 1.0 - (v16 + v16) / v31;
  }
  v19 = v12 - -0.5;
  v21 = v14 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, a4);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)&v19, 1, v13, a3);
}

// 0x00540650
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl _TextureLib_Data::GetLibInfo(
        int a1,
        int a2,
        int a3,
        int a4,
        int *a5,
        struct gbTextureArray *a6,
        int a7,
        unsigned int *a8)
{
  unsigned int v8; // ecx
  unsigned int v9; // edx
  unsigned int v10; // ecx
  gbTexture *v11; // ecx
  double v12; // st7
  double v13; // st6
  double v14; // st5
  gbDynVertBuf *DynVertBuf; // eax
  struct gbRenderEffect *v16; // edx
  struct gbTextureArray *v17; // [esp-4h] [ebp-38h]
  float v18[3]; // [esp+Ch] [ebp-28h] BYREF
  float v19; // [esp+18h] [ebp-1Ch]
  unsigned int v20; // [esp+1Ch] [ebp-18h]
  unsigned int v21; // [esp+20h] [ebp-14h]
  float v22; // [esp+24h] [ebp-10h]
  float v23; // [esp+28h] [ebp-Ch]
  int v24; // [esp+2Ch] [ebp-8h]
  int v25; // [esp+30h] [ebp-4h]

  v24 = 0;
  v25 = *a5;
  if ( a8 )
  {
    v8 = a8[263];
    v20 = a8[262];
    v9 = a8[266];
    v21 = v8;
    v10 = a8[267];
    v22 = *(float *)&v9;
    v23 = *(float *)&v10;
  }
  else
  {
    v11 = a6->pTexPt[0];
    v21 = 0;
    v20 = 0;
    v22 = (fabs((double)(a3 - a1)) + -0.5) / (double)v11->Width;
    v23 = (fabs((double)(a4 - a2)) + -0.5) / (double)v11->Height;
  }
  v12 = (double)a1;
  v19 = (float)a2;
  if ( a8 )
  {
    v13 = (double)a8[260] + v12;
    v14 = (double)a8[261] + v19;
  }
  else
  {
    v13 = (double)a3;
    v14 = (double)a4;
  }
  v18[1] = v14;
  v18[0] = v12 - -0.5;
  v18[2] = v13 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x114u);
  if ( !a7 )
  {
    v17 = a6;
    goto LABEL_11;
  }
  v17 = a6;
  if ( a7 != 1 )
  {
LABEL_11:
    v16 = (struct gbRenderEffect *)g_PlayerGP;
    goto LABEL_12;
  }
  v16 = (struct gbRenderEffect *)g_PlayerMP;
LABEL_12:
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v18, 1, v16, v17);
}

// 0x005407A0
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl _TextureLib_Data::GetLib(
        int a1,
        int a2,
        int a3,
        int a4,
        int *a5,
        struct gbTextureArray *a6,
        unsigned int a7)
{
  int v7; // ecx
  __int64 v8; // rax
  gbTexture *v9; // ecx
  double v10; // st7
  double v11; // st6
  double v12; // st5
  gbDynVertBuf *DynVertBuf; // eax
  float v14[3]; // [esp+Ch] [ebp-28h] BYREF
  float v15; // [esp+18h] [ebp-1Ch]
  int v16; // [esp+1Ch] [ebp-18h]
  int v17; // [esp+20h] [ebp-14h]
  float v18; // [esp+24h] [ebp-10h]
  float v19; // [esp+28h] [ebp-Ch]
  int v20; // [esp+2Ch] [ebp-8h]
  int v21; // [esp+30h] [ebp-4h]

  v7 = *a5;
  v8 = a7;
  v20 = 0;
  v21 = v7;
  if ( a7 )
  {
    v16 = *(_DWORD *)(a7 + 1048);
    v17 = *(_DWORD *)(a7 + 1052);
    v18 = *(float *)(a7 + 1064);
    v19 = *(float *)(a7 + 1068);
  }
  else
  {
    v9 = a6->pTexPt[0];
    v17 = 0;
    v16 = 0;
    v18 = (fabs((double)(a3 - a1)) + -0.5) / (double)v9->Width;
    v19 = (fabs((double)(a4 - a2)) + -0.5) / (double)v9->Height;
  }
  v10 = (double)a1;
  v15 = (float)a2;
  if ( a7 )
  {
    LODWORD(v8) = *(_DWORD *)(a7 + 1044);
    v11 = (double)*(unsigned int *)(a7 + 1040) + v10;
    v12 = (double)v8 + v15;
  }
  else
  {
    v11 = (double)a3;
    v12 = (double)a4;
  }
  v14[1] = v12;
  v14[0] = v10 - -0.5;
  v14[2] = v11 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x114u);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v14, 1, (struct gbRenderEffect *)dword_189505C, a6);
}

// 0x005408E0
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl _TextureLib_Data::GetTextureInfo(
        _DWORD *a1,
        int *a2,
        int *a3,
        struct gbTextureArray *a4,
        unsigned int *a5)
{
  unsigned int v5; // ecx
  unsigned int v6; // edx
  unsigned int v7; // ecx
  gbTexture *v8; // edx
  int v9; // ebx
  double v10; // st7
  gbDynVertBuf *DynVertBuf; // eax
  __int64 v12; // [esp+4h] [ebp-30h]
  float v13[2]; // [esp+Ch] [ebp-28h] BYREF
  float v14; // [esp+14h] [ebp-20h]
  float v15; // [esp+18h] [ebp-1Ch]
  unsigned int v16; // [esp+1Ch] [ebp-18h]
  unsigned int v17; // [esp+20h] [ebp-14h]
  float v18; // [esp+24h] [ebp-10h]
  float v19; // [esp+28h] [ebp-Ch]
  int v20; // [esp+2Ch] [ebp-8h]
  int v21; // [esp+30h] [ebp-4h]
  int v22; // [esp+40h] [ebp+Ch]

  v20 = 0;
  v21 = *a3;
  if ( a5 )
  {
    v5 = a5[263];
    v16 = a5[262];
    v6 = a5[266];
    v17 = v5;
    v7 = a5[267];
    v18 = *(float *)&v6;
    v19 = *(float *)&v7;
  }
  else
  {
    v8 = a4->pTexPt[0];
    v9 = a1[2] - *a1;
    v17 = 0;
    v16 = 0;
    v22 = a1[3] - a1[1];
    v18 = (fabs((double)v9) + -0.5) / (double)v8->Width;
    v19 = (fabs((double)v22) + -0.5) / (double)v8->Height;
  }
  v13[0] = (float)*a2;
  v15 = (float)a2[1];
  if ( a5 )
  {
    v12 = a5[261];
    v14 = (double)a5[260] + v13[0];
    v10 = (double)v12 + v15;
  }
  else
  {
    v14 = (float)a2[2];
    v10 = (double)a2[3];
  }
  v13[1] = v10;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x114u);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v13, 1, (struct gbRenderEffect *)g_PlayerMP, a4);
}

// 0x00540A20
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl _TextureLib_Data::GetTextureInfo(
        int a1,
        int a2,
        int a3,
        int a4,
        int *a5,
        struct gbTextureArray *a6,
        unsigned int *a7)
{
  double v7; // st7
  double v8; // st6
  double v9; // st5
  gbDynVertBuf *DynVertBuf; // eax
  float v11[3]; // [esp+8h] [ebp-28h] BYREF
  float v12; // [esp+14h] [ebp-1Ch]
  unsigned int v13; // [esp+18h] [ebp-18h]
  unsigned int v14; // [esp+1Ch] [ebp-14h]
  unsigned int v15; // [esp+20h] [ebp-10h]
  unsigned int v16; // [esp+24h] [ebp-Ch]
  int v17; // [esp+28h] [ebp-8h]
  int v18; // [esp+2Ch] [ebp-4h]

  v17 = 0;
  v18 = *a5;
  if ( a7 )
  {
    v13 = a7[262];
    v14 = a7[263];
    v15 = a7[266];
    v16 = a7[267];
  }
  else
  {
    v13 = 0;
    v14 = 0;
    v15 = 1065353216;
    v16 = 1065353216;
  }
  v7 = (double)a1;
  v12 = (float)a2;
  if ( a7 )
  {
    v8 = (double)a7[260] + v7;
    v9 = (double)a7[261] + v12;
  }
  else
  {
    v8 = (double)a3;
    v9 = (double)a4;
  }
  v11[1] = v9;
  v11[0] = v7 - -0.5;
  v11[2] = v8 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x114u);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v11, 1, (struct gbRenderEffect *)g_PlayerGP, a6);
}

// 0x00540B20
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl UIInitSystem(int *a1, int *a2, struct gbTextureArray *a3, int a4, unsigned int *a5)
{
  int v5; // ecx
  double v6; // st7
  double v7; // st6
  double v8; // st5
  gbDynVertBuf *DynVertBuf; // eax
  float v10[3]; // [esp+8h] [ebp-28h] BYREF
  float v11; // [esp+14h] [ebp-1Ch]
  unsigned int v12; // [esp+18h] [ebp-18h]
  unsigned int v13; // [esp+1Ch] [ebp-14h]
  unsigned int v14; // [esp+20h] [ebp-10h]
  unsigned int v15; // [esp+24h] [ebp-Ch]
  int v16; // [esp+28h] [ebp-8h]
  int v17; // [esp+2Ch] [ebp-4h]

  v5 = a4;
  if ( a4 >= 0 )
  {
    if ( a4 > 1 )
      v5 = 1;
  }
  else
  {
    v5 = 0;
  }
  v16 = 0;
  v17 = *a2;
  if ( a5 )
  {
    v12 = a5[262];
    v13 = a5[263];
    v14 = a5[266];
    v15 = a5[267];
    goto LABEL_12;
  }
  if ( v5 )
  {
    if ( v5 != 1 )
      goto LABEL_12;
    v12 = 0;
    v13 = 0;
    v14 = 1065353216;
  }
  else
  {
    v12 = 1065353216;
    v13 = 0;
    v14 = 0;
  }
  v15 = 1065353216;
LABEL_12:
  v6 = (double)*a1;
  v11 = (float)a1[1];
  if ( a5 )
  {
    v7 = (double)a5[260] + v6;
    v8 = (double)a5[261] + v11;
  }
  else
  {
    v7 = (double)a1[2];
    v8 = (double)a1[3];
  }
  v10[1] = v8;
  v10[0] = v6 - -0.5;
  v10[2] = v7 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x114u);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v10, 1, (struct gbRenderEffect *)g_PlayerData_04C, a3);
}

// 0x00540C60
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl UIDestorySystem(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6)
{
  int v6; // ecx
  gbTexture *v7; // eax
  gbDynVertBuf *DynVertBuf; // eax
  float v9[2]; // [esp+4h] [ebp-28h] BYREF
  float v10; // [esp+Ch] [ebp-20h]
  float v11; // [esp+10h] [ebp-1Ch]
  int v12; // [esp+14h] [ebp-18h]
  int v13; // [esp+18h] [ebp-14h]
  int v14; // [esp+1Ch] [ebp-10h]
  float v15; // [esp+20h] [ebp-Ch]
  int v16; // [esp+24h] [ebp-8h]
  int v17; // [esp+28h] [ebp-4h]

  v6 = *a5;
  v16 = 0;
  v17 = v6;
  v7 = a6->pTexPt[0];
  v13 = 0;
  v12 = 0;
  v14 = 1065353216;
  v15 = (fabs((double)(a4 - a2)) + -0.5) / (double)v7->Height;
  v11 = (float)a2;
  v10 = (float)a3;
  v9[1] = (float)a4;
  v9[0] = (double)a1 - -0.5;
  v10 = v10 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x114u);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v9, 1, (struct gbRenderEffect *)g_PlayerGP, a6);
}

// 0x00540D20
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl UIRenderQuad(int a1, int a2, int a3, int a4, int a5, int a6, int *a7, struct gbTextureArray *a8)
{
  gbDynVertBuf *DynVertBuf; // eax
  float v9[2]; // [esp+4h] [ebp-28h] BYREF
  float v10; // [esp+Ch] [ebp-20h]
  float v11; // [esp+10h] [ebp-1Ch]
  int v12; // [esp+14h] [ebp-18h]
  int v13; // [esp+18h] [ebp-14h]
  int v14; // [esp+1Ch] [ebp-10h]
  int v15; // [esp+20h] [ebp-Ch]
  int v16; // [esp+24h] [ebp-8h]
  int v17; // [esp+28h] [ebp-4h]

  v16 = 0;
  v12 = 0;
  v11 = (float)a2;
  v17 = *a7;
  v13 = a5;
  v10 = (float)a3;
  v14 = 1065353216;
  v15 = 0;
  v9[1] = (float)a4;
  v9[0] = (double)a1 - -0.5;
  v10 = v10 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x114u);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v9, 1, (struct gbRenderEffect *)g_PlayerGP, a8);
}

// 0x00540DC0
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl UIRenderQuadEX(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, int a7, char a8)
{
  int v8; // ecx
  gbTexture *v9; // ecx
  long double v10; // st7
  gbTexture *v11; // ecx
  double v12; // st7
  double v13; // st6
  double v14; // st5
  gbDynVertBuf *DynVertBuf; // eax
  float v16[3]; // [esp+14h] [ebp-28h] BYREF
  float v17; // [esp+20h] [ebp-1Ch]
  float v18; // [esp+24h] [ebp-18h]
  float v19; // [esp+28h] [ebp-14h]
  float v20; // [esp+2Ch] [ebp-10h]
  float v21; // [esp+30h] [ebp-Ch]
  int v22; // [esp+34h] [ebp-8h]
  int v23; // [esp+38h] [ebp-4h]

  v8 = *a5;
  v22 = 0;
  v23 = v8;
  if ( !a7 )
  {
    v11 = a6->pTexPt[0];
    v19 = 0.0;
    v18 = 0.0;
    v20 = (fabs((double)(a3 - a1)) + -0.5) / (double)v11->Width;
    v10 = (fabs((double)(a4 - a2)) + -0.5) / (double)v11->Height;
    goto LABEL_6;
  }
  v18 = *(float *)(a7 + 1048);
  v19 = *(float *)(a7 + 1052);
  if ( !a8 )
  {
    v9 = a6->pTexPt[0];
    v20 = (fabs((double)(a3 - a1)) + -0.5) / (double)a6->pTexPt[0]->Width + v18;
    v10 = (fabs((double)(a4 - a2)) + -0.5) / (double)v9->Height + v19;
LABEL_6:
    v21 = v10;
    goto LABEL_7;
  }
  v20 = *(float *)(a7 + 1064);
  v21 = *(float *)(a7 + 1068);
LABEL_7:
  v12 = (double)a1;
  v17 = (float)a2;
  if ( a7 && a8 )
  {
    v13 = (double)*(unsigned int *)(a7 + 1040) + v12;
    v14 = (double)*(unsigned int *)(a7 + 1044) + v17;
  }
  else
  {
    v13 = (double)a3;
    v14 = (double)a4;
  }
  v16[1] = v14;
  v16[0] = v12 - -0.5;
  v16[2] = v13 - -0.5;
  DynVertBuf = gbVertPoolMgr::GetDynVertBuf(g_pGfxMgr->pVertPoolMgr, 0x114u);
  gbDynVertBuf::RenderUIQuad(DynVertBuf, (struct gbUIQuad *)v16, 1, (struct gbRenderEffect *)dword_1895060, a6);
}

// 0x00540F60
// between_std_methods (0x53C2D0-0x541D1B)
gbGfxManager *__cdecl PushMatrixStacks()
{
  gbGfxManager *v0; // ecx
  gbMatrixStack *v1; // esi
  gbGfxManager *v2; // ebx
  gbMatrixStack *v3; // edi

  v1 = g_pGfxMgr->pMatrixStack[1];
  v2 = v0;
  v3 = g_pGfxMgr->pMatrixStack[0];
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

  v0 = g_pGfxMgr->pMatrixStack[1];
  gbMatrixStack::Pop(g_pGfxMgr->pMatrixStack[0]);
  gbMatrixStack::Pop(v0);
  return result;
}

// 0x00540FD0
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl UIRenderQuad(int a1, int a2, int a3, _BYTE *a4, int a5)
{
  int v5; // eax
  gbPrintFont *v6; // esi
  bool v7; // cc
  bool v8; // cc
  double v9; // st7
  double v10; // st6
  float v11; // [esp+0h] [ebp-20h]
  float v12; // [esp+4h] [ebp-1Ch]
  int v13; // [esp+28h] [ebp+8h]
  int v14; // [esp+34h] [ebp+14h]

  if ( !a3 )
    return;
  v5 = a5;
  v6 = 0;
  v13 = a5 + a2;
  if ( a5 > 24 )
    goto LABEL_15;
  if ( a5 >= 12 )
  {
    if ( a5 <= 12 )
    {
      v7 = a5 <= 16;
    }
    else
    {
      v7 = a5 <= 16;
      if ( a5 < 16 )
      {
        v5 = 16;
        goto LABEL_16;
      }
    }
    if ( v7 )
    {
      v8 = a5 <= 20;
    }
    else
    {
      v8 = a5 <= 20;
      if ( a5 < 20 )
      {
        v5 = 20;
        goto LABEL_16;
      }
    }
    if ( v8 || a5 >= 24 )
      goto LABEL_17;
LABEL_15:
    v5 = 24;
    goto LABEL_16;
  }
  v5 = 12;
LABEL_16:
  a5 = v5;
LABEL_17:
  switch ( v5 )
  {
    case 12:
      v6 = g_pGfxMgr->pFontMgr->pAllFont[0];
      break;
    case 16:
      v6 = g_pGfxMgr->pFontMgr->pAllFont[1];
      break;
    case 20:
      v6 = g_pGfxMgr->pFontMgr->pAllFont[2];
      break;
    case 24:
      v6 = g_pGfxMgr->pFontMgr->pAllFont[3];
      break;
    default:
      break;
  }
  v9 = (double)a5 + (double)a5;
  v10 = v9 / (double)(int)g_pAbsTime;
  *(float *)&v6->curColor.Blue = v9 / (double)(int)g_pGameTime;
  *(float *)&v6->curColor.Color = v10;
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(v14) = *a4;
    BYTE1(v14) = a4[1];
    LOBYTE(v14) = a4[2];
  }
  else
  {
    *(_WORD *)((char *)&v14 + 1) = *(_WORD *)(a4 + 1);
    LOBYTE(v14) = *a4;
  }
  HIBYTE(v14) = a4[3];
  v6->curColor.ColorQuadFmt = v14;
  v12 = 1.0 - ((double)v13 + (double)v13) / (double)(int)g_pAbsTime;
  v11 = ((double)a1 + (double)a1) / (double)(int)g_pGameTime - 1.0;
  (*(void (__thiscall **)(gbPrintFont *, int, _DWORD, _DWORD, int, int))(*(_DWORD *)v6->_pad_0000 + 16))(
    v6,
    a3,
    LODWORD(v11),
    LODWORD(v12),
    1176256512,
    1176256512);
  (*(void (__thiscall **)(gbPrintFont *))(*(_DWORD *)v6->_pad_0000 + 8))(v6);
}

// 0x00541160
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl UIRenderPar(const char *a1, int *a2, _BYTE *a3, int a4, int a5)
{
  gbPrintFont *v6; // edi
  int v7; // eax
  int v8; // [esp+20h] [ebp+10h]

  v6 = g_pGfxMgr->pFontMgr->pAllFont[a4];
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(v8) = *a3;
    BYTE1(v8) = a3[1];
    LOBYTE(v8) = a3[2];
  }
  else
  {
    *(_WORD *)((char *)&v8 + 1) = *(_WORD *)(a3 + 1);
    LOBYTE(v8) = *a3;
  }
  HIBYTE(v8) = a3[3];
  v6->curColor.ColorQuadFmt = v8;
  v7 = 16;
  switch ( a4 )
  {
    case 0:
      v7 = 12;
      break;
    case 1:
      v7 = 16;
      break;
    case 2:
      v7 = 20;
      break;
    case 3:
      v7 = 24;
      break;
    default:
      break;
  }
  UIRenderQuad(a1, a2, (float *)v6->_pad_0000, v7, a5);
}

// 0x00541210
// between_std_methods (0x53C2D0-0x541D1B)
void __cdecl UIRenderQuad(const char *a1, int *a2, float *a3, int a4, int a5)
{
  int v5; // ebp
  unsigned int v6; // kr10_4
  int v7; // ecx
  int v8; // edi
  bool v9; // zf
  double v10; // st7
  double v11; // st6
  int v12; // esi
  int *v13; // ebx
  char v14; // al
  int v15; // edi
  char v16; // al
  char v17; // cl
  int v18; // ebx
  unsigned int v19; // kr18_4
  float v20; // [esp+0h] [ebp-40h]
  float v21; // [esp+4h] [ebp-3Ch]
  int v22; // [esp+20h] [ebp-20h]
  int v23; // [esp+24h] [ebp-1Ch]
  int v24; // [esp+28h] [ebp-18h]
  int v25; // [esp+2Ch] [ebp-14h]
  int v26; // [esp+30h] [ebp-10h]
  int v27; // [esp+34h] [ebp-Ch]

  v5 = 0;
  if ( a1 )
  {
    if ( a3 )
    {
      v6 = strlen(a1) + 1;
      v7 = v6 - 1;
      if ( (int)(v6 - 1) > 0 )
      {
        v8 = 1;
        v9 = a5 == 1;
        v10 = (double)a4 + (double)a4;
        v22 = 0;
        v25 = 0;
        v26 = 0;
        v11 = v10 / (double)(int)g_pAbsTime;
        a3[12] = v10 / (double)(int)g_pGameTime;
        a3[13] = v11;
        v12 = a4;
        v13 = a2;
        if ( v9 )
        {
          v25 = (a2[2] - a4 * v7 / 2 - *a2) / 2;
          v26 = (a2[3] - a2[1] - a4) / 2;
        }
        v24 = 1;
        v23 = a4;
        while ( 1 )
        {
          v14 = a1[v5];
          if ( v14 == 92 )
          {
            ++v5;
            v15 = v8 + 1;
            if ( v5 >= v7 )
              goto LABEL_23;
            v16 = a1[v5];
            if ( v16 == 110 )
            {
              v22 = 0;
              v23 += v12;
            }
            else if ( v16 == 116 )
            {
              v22 = 8 * ((v22 + 8) / 8);
            }
          }
          else
          {
            LOWORD(a5) = 0;
            BYTE2(a5) = 0;
            if ( v14 <= 0 || v14 == 127 )
            {
              if ( v8 >= v7 )
                goto LABEL_23;
              LOBYTE(a5) = v14;
              v17 = a1[++v5];
              BYTE1(a5) = v17;
              v24 = v8 + 1;
            }
            else
            {
              LOBYTE(a5) = v14;
            }
            v18 = *v13;
            v27 = v25 + v18 + v12 * v22 / 2;
            if ( (int)(v27 + a4 / 2 * strlen((const char *)&a5)) > a2[2] )
            {
              v22 = 0;
              v27 = v18;
              v23 += a4;
            }
            if ( v26 + v23 + a2[1] > a2[3] )
            {
LABEL_23:
              (*(void (__thiscall **)(float *))(*(_DWORD *)a3 + 8))(a3);
              return;
            }
            v21 = 1.0 - ((double)(v26 + v23 + a2[1]) + (double)(v26 + v23 + a2[1])) / (double)(int)g_pAbsTime;
            v20 = ((double)v27 + (double)v27) / (double)(int)g_pGameTime - 1.0;
            (*(void (__stdcall **)(int *, _DWORD, _DWORD, int, int))(*(_DWORD *)a3 + 16))(
              &a5,
              LODWORD(v20),
              LODWORD(v21),
              1176256512,
              1176256512);
            v12 = a4;
            v19 = strlen((const char *)&a5) + 1;
            v13 = a2;
            v15 = v24;
            v7 = v6 - 1;
            v22 += v19 - 1;
          }
          ++v5;
          v8 = v15 + 1;
          v24 = v8;
          if ( v5 >= v7 )
            goto LABEL_23;
        }
      }
    }
  }
}

// 0x00541490
// between_std_methods (0x53C2D0-0x541D1B)
// attributes: thunk
void __thiscall UIRenderQuadFlip(UIQuadManager *_this)
{
  UIQuadManager::Destroy(_this);
}

// 0x005414A0
// between_std_methods (0x53C2D0-0x541D1B)
struct gbVFileSystem *__thiscall UIRenderQuadList(_BYTE *_this)
{
  char v2; // al
  gbTexture **v3; // edi
  _DWORD *v4; // esi
  int v5; // ebx
  gbTexture *v6; // eax
  _DWORD *v7; // esi
  int v8; // ebx
  OpenBaseFile v10; // [esp+14h] [ebp-1Ch] BYREF
  _DWORD v11[3]; // [esp+18h] [ebp-18h] BYREF
  int v12; // [esp+2Ch] [ebp-4h]

  v11[0] = aUiCursorJtTga;
  v11[1] = aUiCursorSbSTga;
  v11[2] = aUiCursorSbNTga;
  OpenBaseFile::OpenBaseFile(&v10);
  v2 = *(_this + 29);
  v12 = 0;
  if ( v2 )
  {
    v3 = (gbTexture **)(_this + 16);
    v4 = v11;
    v5 = 3;
    do
    {
      v6 = (gbTexture *)(*(int (__thiscall **)(gbGfxManager *, _DWORD))(*(_DWORD *)g_pGfxMgr->_vftable + 8))(
                          g_pGfxMgr,
                          *v4);
      *v3 = v6;
      gbTexture::LoadTexture(v6, 1);
      ++v4;
      ++v3;
      --v5;
    }
    while ( v5 );
  }
  else
  {
    v7 = _this;
    v8 = 3;
    do
    {
      *v7 = (*(int (__thiscall **)(gbGfxManager *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)g_pGfxMgr->_vftable + 96))(
              g_pGfxMgr,
              *(_DWORD *)((char *)v7 + (char *)v11 - _this),
              0,
              0);
      ++v7;
      --v8;
    }
    while ( v8 );
    (*(void (__thiscall **)(gbGfxManager *, int))(*(_DWORD *)g_pGfxMgr->_vftable + 104))(g_pGfxMgr, 1);
  }
  UIQuadManager_Reset();
  v12 = -1;
  return OpenNULLFile::OpenNULLFile((OpenNULLFile **)&v10);
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
    *(_DWORD *)result->DrvInfo = v3;
    if ( !v2 )
      return (gbGfxManager *)(*(int (__thiscall **)(gbGfxManager *, _DWORD))(*(_DWORD *)g_pGfxMgr->_vftable + 100))(
                               g_pGfxMgr,
                               *(_DWORD *)&result->_vftable[4 * v3]);
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  return atexit(nullsub_1);
}

// 0x00541780
// between_std_methods (0x53C2D0-0x541D1B)
// attributes: thunk
int UIDrawText()
{
  return ?UIDrawText@@YAXPBDABUtagRECT@@PAVgbPrintFont@@HH@Z();
}

// 0x00541790
// between_std_methods (0x53C2D0-0x541D1B)
int UIDrawText()
{
  dword_18952FC = 1094713344;
  return 1094713344;
}

// 0x005417A0
// between_std_methods (0x53C2D0-0x541D1B)
// attributes: thunk
void UIDrawRichText()
{
  UICursor::UICursor();
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

// 0x00541900
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  HWND WindowA; // esi
  BOOL i; // eax
  char *v7; // eax
  _DWORD *v8; // esi
  double v9; // st7
  int v10; // edx
  HWND ActiveWindow; // eax
  int v12; // [esp+0h] [ebp-698h] BYREF
  CHAR Text[256]; // [esp+40Ch] [ebp-28Ch] BYREF
  char Buffer[324]; // [esp+50Ch] [ebp-18Ch] BYREF
  struct tagMSG Msg; // [esp+650h] [ebp-48h] BYREF
  int v16; // [esp+66Ch] [ebp-2Ch]
  _DWORD *v17; // [esp+670h] [ebp-28h]
  int v18; // [esp+678h] [ebp-20h]
  char v19; // [esp+680h] [ebp-18h]
  char v20; // [esp+681h] [ebp-17h]
  char v21; // [esp+682h] [ebp-16h]
  HHOOK hhk; // [esp+684h] [ebp-14h]
  int *v23; // [esp+688h] [ebp-10h]
  int v24; // [esp+694h] [ebp-4h]
  int hInstancea; // [esp+6A0h] [ebp+8h]

  v23 = &v12;
  WindowA = FindWindowA(WindowName, WindowName);
  if ( IsWindow(WindowA) )
  {
    ShowWindow(WindowA, 1);
    return 0;
  }
  dword_BFDA48 = hInstance;
  hhk = SetWindowsHookExA(13, (HOOKPROC)fn, hInstance, 0);
  memset(Data, 0, sizeof(Data));
  v24 = 0;
  if ( !UICursor::Inst(aSoftwareSoftst_1, aCdriver, (LPBYTE)Data) )
    UICursor::Init();
  if ( !strrchr(Data, 92) )
    strcat(Data, asc_5D41EC);
  sprintf(Buffer, "%sMovie", Data);
  for ( i = CheckDirectoryExists(Buffer); !i; i = CheckDirectoryExists(Buffer) )
  {
    sprintf(Text, "Please Insert Disc4 to Dirver %c:", Data[0]);
    if ( MessageBoxA(0, Text, aPal3, 0x41u) == 2 )
      return 0;
  }
  memset(Filename, 0, sizeof(Filename));
  GetModuleFileNameA(0, Filename, 0x104u);
  v7 = strrchr(Filename, 92);
  if ( v7 )
    *v7 = 0;
  PAL3::Create((char *)&g_PlayerBase, hInstance);
  gbUpdateCurTime();
  v16 = 20;
  *(_QWORD *)&dbl_1895070 = __PAIR64__(HIDWORD(g_CurrentTime), LODWORD(g_CurrentTime));
  v8 = operator new(0x50u);
  v17 = v8;
  memset(v8, 0, 0x50u);
  v18 = 0;
  v19 = 1;
  v20 = 0;
  v21 = 0;
  LOBYTE(v24) = 1;
  while ( 1 )
  {
    if ( !PeekMessageA(&Msg, 0, 0, 0, 0) )
      goto LABEL_20;
    if ( !GetMessageA(&Msg, 0, 0, 0) )
      break;
    TranslateMessage(&Msg);
    DispatchMessageA(&Msg);
LABEL_20:
    gbUpdateCurTime();
    v9 = g_CurrentTime - dbl_1895070;
    v10 = HIDWORD(g_CurrentTime);
    LODWORD(dbl_1895070) = LODWORD(g_CurrentTime);
    HIDWORD(dbl_1895070) = v10;
    if ( g_bGameActive || (ActiveWindow = GetActiveWindow(), CCBSystem::ProcUseItem(ActiveWindow)) )
    {
      *(float *)&hInstancea = v9;
      PAL3::Update(hInstancea);
      PAL3::Render();
    }
    else
    {
      Sleep(0x64u);
    }
  }
  if ( v8 )
    operator delete(v8);
  v24 = -1;
  UnhookWindowsHookEx(hhk);
  PAL3::Destroy();
  return Msg.wParam;
}

// 0x00541CE0
// Microsoft VisualC 2-14/net runtime
// Microsoft VisualC 2-14/net runtime
int unknown_libname_524()
{
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
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
  if ( (g_bInitFlags & 1) == 0 )
    g_bInitFlags |= 1u;
  sub_542059();
  if ( (byte_189598F & 1) == 0 )
    byte_189598F |= 1u;
  return atexit(nullsub_96);
}

// 0x00552ED8
void *__cdecl calloc(size_t Count, size_t Size)
{
  SIZE_T v2; // esi
  size_t v3; // ebx
  void *v4; // edi
  _DWORD *v5; // eax

  v2 = Size * Count;
  v3 = Size * Count;
  if ( Size * Count <= 0xFFFFFFE0 )
  {
    if ( !v2 )
      v2 = 1;
    v2 = (v2 + 15) & 0xFFFFFFF0;
  }
  do
  {
    v4 = 0;
    if ( v2 <= 0xFFFFFFE0 )
    {
      if ( v3 <= dword_60ACB4 )
      {
        v5 = __sbh_alloc_block(v3);
        v4 = v5;
        if ( v5 )
        {
          memset(v5, 0, v3);
          return v4;
        }
      }
      v4 = HeapAlloc(hHeap, 8u, v2);
      if ( v4 )
        return v4;
    }
    if ( !dword_1895328 )
      return v4;
  }
  while ( _callnewh(v2) );
  return 0;
}

// 0x00552F55
void __cdecl free(void *Block)
{
  char *v1; // eax

  if ( Block )
  {
    v1 = __sbh_find_block((int)Block);
    if ( v1 )
      __sbh_free_block(v1, (unsigned int)Block);
    else
      HeapFree(hHeap, 0, Block);
  }
}

// 0x00552F84
unsigned int _fpmath()
{
  unsigned int result; // eax

  _cfltcvt_init();
  dword_1895310 = _ms_p5_mp_test_fdiv();
  result = _setdefaultprecision();
  __asm { fnclex }
  return result;
}

// 0x00552F9C
char *(__cdecl *_cfltcvt_init())(double *, char *Src, int, char *Size, int)
{
  off_60ACBC[0] = (void (__noreturn *)())_cropzeros;
  off_60ACB8[0] = (void (__noreturn *)())_cfltcvt;
  off_60ACC0[0] = (void (__noreturn *)())_fassign;
  off_60ACC4[0] = (void (__noreturn *)())_forcdecpt;
  off_60ACC8[0] = (void (__noreturn *)())_positive;
  off_60ACCC = (void (__noreturn *)())_cfltcvt;
  return _cfltcvt;
}

// 0x00552FD4
_onexit_t __cdecl _onexit(_onexit_t Func)
{
  size_t v1; // eax
  _onexit_t *v2; // ecx
  size_t v3; // eax
  _onexit_t result; // eax
  int v5; // ecx

  v1 = _msize(dword_1896CF0);
  v2 = (_onexit_t *)dword_1896CEC;
  if ( v1 < dword_1896CEC - (int)dword_1896CF0 + 4 )
  {
    v3 = _msize(dword_1896CF0);
    result = (_onexit_t)realloc(dword_1896CF0, v3 + 16);
    if ( !result )
      return result;
    v5 = dword_1896CEC - (_DWORD)dword_1896CF0;
    dword_1896CF0 = result;
    v2 = (_onexit_t *)((char *)result + 4 * (v5 >> 2));
    dword_1896CEC = (int)v2;
  }
  *v2 = Func;
  dword_1896CEC += 4;
  return Func;
}

// 0x00553041
int __cdecl atexit(void (__cdecl *Func)())
{
  return (_onexit((_onexit_t)Func) != 0) - 1;
}

// 0x00553053
void *__onexitinit()
{
  _DWORD *v0; // eax

  v0 = malloc(0x80u);
  dword_1896CF0 = v0;
  if ( !v0 )
    _amsg_exit(0x18u);
  *v0 = 0;
  dword_1896CEC = (int)dword_1896CF0;
  return dword_1896CF0;
}

// 0x00553082
int sprintf(char *const Buffer, const char *const Format, ...)
{
  int v2; // eax
  bool v3; // sf
  int v4; // esi
  FILE File; // [esp+4h] [ebp-20h] BYREF
  va_list va; // [esp+34h] [ebp+10h] BYREF

  va_start(va, Format);
  File._base = Buffer;
  File._ptr = Buffer;
  File._flag = 66;
  File._cnt = 0x7FFFFFFF;
  v2 = _output(&File, (char *)Format, (int)va);
  v3 = --File._cnt < 0;
  v4 = v2;
  if ( v3 )
    _flsbuf(0, &File);
  else
    *File._ptr = 0;
  return v4;
}

// 0x005530D4
void __stdcall _JumpToContinuation(
        void (__stdcall *a1)(void *, struct EHRegistrationNode *),
        struct EHRegistrationNode *a2)
{
  a1(a1, a2);
}

// 0x00553116
void __userpurge _UnwindNestedFrames(
        struct _EXCEPTION_REGISTRATION_RECORD **a1@<ebx>,
        PVOID TargetFrame,
        PEXCEPTION_RECORD ExceptionRecord)
{
  __int32 ExceptionFlags; // eax

  RtlUnwind(TargetFrame, &_ReturnPoint_16567, ExceptionRecord, 0);
  ExceptionFlags = ExceptionRecord->ExceptionFlags;
  LOBYTE(ExceptionFlags) = ExceptionFlags & 0xFD;
  ExceptionRecord->ExceptionFlags = ExceptionFlags;
  *a1 = NtCurrentTeb()->NtTib.ExceptionList;
}

// 0x00553165
int __usercall __CxxFrameHandler@<eax>(
        EXCEPTION_POINTERS *a1@<eax>,
        struct EHExceptionRecord *ExceptionRecord,
        struct EHRegistrationNode *a3,
        struct _CONTEXT *a4,
        void *a5)
{
  return __InternalCxxFrameHandler(ExceptionRecord, a3, a4, a5, a1, 0, 0, 0);
}

// 0x0055319B
void __cdecl _CallCatchBlock2(
        struct EHRegistrationNode *a1,
        const struct _s_FuncInfo *a2,
        void *a3,
        int a4,
        unsigned int a5)
{
  _CallSettingFrame((int)a3, (int)a1, a5);
}

// 0x005531EF
int __cdecl CatchGuardHandler(struct EHExceptionRecord *ExceptionRecord, PVOID TargetFrame, struct _CONTEXT *a3)
{
  return __InternalCxxFrameHandler(
           ExceptionRecord,
           *((struct EHRegistrationNode **)TargetFrame + 3),
           a3,
           0,
           *((EXCEPTION_POINTERS **)TargetFrame + 2),
           *((_DWORD *)TargetFrame + 4),
           (struct EHRegistrationNode *)TargetFrame,
           0);
}

// 0x00553214
int __cdecl _CallSETranslator(
        struct EHExceptionRecord *a1,
        struct EHRegistrationNode *a2,
        void *a3,
        void *a4,
        const struct _s_FuncInfo *a5,
        int a6,
        struct EHRegistrationNode *a7)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // ebx
  int v9; // [esp+0h] [ebp-40h] BYREF
  int v10; // [esp+Ch] [ebp-34h]
  _DWORD v11[11]; // [esp+10h] [ebp-30h] BYREF
  int v12; // [esp+3Ch] [ebp-4h]
  int savedregs; // [esp+40h] [ebp+0h] BYREF

  v11[3] = TranslatorGuardHandler;
  v11[4] = a5;
  v11[5] = a2;
  v11[6] = a6;
  v11[7] = a7;
  v12 = 0;
  v11[8] = &_ExceptionContinuation_16667;
  v11[9] = &v9;
  v11[10] = &savedregs;
  v11[2] = NtCurrentTeb()->NtTib.ExceptionList;
  v10 = 1;
  v11[0] = a1;
  v11[1] = a3;
  dword_1895390(a1->ExceptionCode, v11);
  v10 = 0;
  if ( v12 )
  {
    ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
    ExceptionList->Next = ExceptionList->Next;
  }
  return v10;
}

// 0x005532C8
enum _EXCEPTION_DISPOSITION __usercall TranslatorGuardHandler@<eax>(
        struct _EXCEPTION_REGISTRATION_RECORD **a1@<ebx>,
        struct EHExceptionRecord *ExceptionRecord,
        PVOID TargetFrame,
        struct _CONTEXT *a4)
{
  if ( (ExceptionRecord->ExceptionFlags & 0x66) != 0 )
  {
    *((_DWORD *)TargetFrame + 9) = 1;
    return ExceptionContinueSearch;
  }
  else
  {
    __InternalCxxFrameHandler(
      ExceptionRecord,
      *((struct EHRegistrationNode **)TargetFrame + 3),
      a4,
      0,
      *((EXCEPTION_POINTERS **)TargetFrame + 2),
      *((_DWORD *)TargetFrame + 4),
      *((struct EHRegistrationNode **)TargetFrame + 5),
      1);
    if ( !*((_DWORD *)TargetFrame + 9) )
      _UnwindNestedFrames(a1, TargetFrame, (PEXCEPTION_RECORD)ExceptionRecord);
    return (*((enum _EXCEPTION_DISPOSITION (**)(void))TargetFrame + 6))();
  }
}

// 0x0055333D
TryBlockMapEntry *__cdecl _GetRangeOfTrysToCheck(
        const struct _s_FuncInfo *a1,
        int a2,
        EXCEPTION_POINTERS *a3,
        unsigned int *a4,
        unsigned int *a5)
{
  unsigned int nTryBlocks; // esi
  TryBlockMapEntry *pTryBlockMap; // ebx
  unsigned int v8; // eax
  unsigned int v9; // esi
  struct _EXCEPTION_POINTERS *v11; // [esp+0h] [ebp-10h]
  unsigned int v12; // [esp+Ch] [ebp-4h]
  const struct _s_FuncInfo *v13; // [esp+18h] [ebp+8h]

  nTryBlocks = a1->nTryBlocks;
  pTryBlockMap = a1->pTryBlockMap;
  v8 = nTryBlocks;
  v13 = (const struct _s_FuncInfo *)nTryBlocks;
  v12 = nTryBlocks;
  if ( a2 >= 0 )
  {
    do
    {
      if ( nTryBlocks == -1 )
        UnhandledExceptionFilter_0(v11);
      if ( pTryBlockMap[--nTryBlocks].tryHigh < (int)a3 && (int)a3 <= pTryBlockMap[nTryBlocks].catchHigh
        || nTryBlocks == -1 )
      {
        --a2;
        v12 = (unsigned int)v13;
        v13 = (const struct _s_FuncInfo *)nTryBlocks;
      }
    }
    while ( a2 >= 0 );
    v8 = v12;
  }
  v9 = nTryBlocks + 1;
  *a4 = v9;
  *a5 = v8;
  if ( v8 > a1->nTryBlocks || v9 > v8 )
    UnhandledExceptionFilter_0(v11);
  return &pTryBlockMap[v9];
}

// 0x005533B8
void __cdecl _global_unwind2(PVOID TargetFrame)
{
  RtlUnwind(TargetFrame, &gu_return, 0, 0);
}

// 0x005533D8
int __cdecl _unwind_handler(int a1, int a2, int a3, _DWORD *a4)
{
  int result; // eax

  result = 1;
  if ( (*(_DWORD *)(a1 + 4) & 6) != 0 )
  {
    *a4 = a2;
    return 3;
  }
  return result;
}

// 0x005533FA
int __usercall _local_unwind2@<eax>(int a1@<ebp>, int a2, int a3)
{
  int result; // eax
  int v4; // ebx
  int v5; // esi
  int v6; // esi
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp-8h] [ebp-1Ch]
  int (__cdecl *v8)(int, int, int, _DWORD *); // [esp-4h] [ebp-18h]

  v8 = _unwind_handler;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  while ( 1 )
  {
    result = a2;
    v4 = *(_DWORD *)(a2 + 8);
    v5 = *(_DWORD *)(a2 + 12);
    if ( v5 == -1 || v5 == a3 )
      break;
    v6 = 3 * v5;
    *(_DWORD *)(a2 + 12) = *(_DWORD *)(v4 + 4 * v6);
    if ( !*(_DWORD *)(v4 + 4 * v6 + 4) )
    {
      _NLG_Notify(*(_DWORD *)(v4 + 4 * v6 + 8), a1, 257);
      (*(void (__cdecl **)(struct _EXCEPTION_REGISTRATION_RECORD *, int (__cdecl *)(int, int, int, _DWORD *)))(v4 + 4 * v6 + 8))(
        ExceptionList,
        v8);
    }
  }
  return result;
}

// 0x00553462
int __cdecl _abnormal_termination()
{
  int result; // eax
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // ecx

  result = 0;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  if ( (int (__cdecl *)(int, int, int, _DWORD *))ExceptionList->Handler == _unwind_handler )
    return ExceptionList[1].Next == (struct _EXCEPTION_REGISTRATION_RECORD *)*((_DWORD *)ExceptionList[1].Handler + 3);
  return result;
}

// 0x00553485
void __stdcall _NLG_Notify1(int a1)
{
  JUMPOUT(0x553498);
}

// 0x0055348E
int __userpurge _NLG_Notify@<eax>(int result@<eax>, int a2@<ebp>, int a3)
{
  unk_60AC34 = *(_DWORD *)(a2 + 8);
  unk_60AC30 = result;
  unk_60AC38 = a2;
  return result;
}

// 0x005534BB
type_info *__thiscall type_info::`scalar deleting destructor'(type_info *_this, char a2)
{
  type_info::~type_info(_this);
  if ( (a2 & 1) != 0 )
    operator delete(_this);
  return _this;
}

// 0x005534D7
void __stdcall __noreturn _CxxThrowException(void *pExceptionObject, _ThrowInfo *pThrowInfo)
{
  DWORD dwExceptionCode[8]; // [esp+8h] [ebp-20h] BYREF

  qmemcpy(dwExceptionCode, &unk_5731D8, sizeof(dwExceptionCode));
  dwExceptionCode[6] = (DWORD)pExceptionObject;
  dwExceptionCode[7] = (DWORD)pThrowInfo;
  RaiseException(dwExceptionCode[0], dwExceptionCode[1], dwExceptionCode[4], &dwExceptionCode[5]);
}

// 0x00553514
__int64 __usercall _ftol@<edx:eax>(double a1@<st0>)
{
  return (__int64)a1;
}

// 0x005535C9
void __stdcall __ArrayUnwind(char *a1, unsigned int a2, int a3, void (*a4)(void))
{
  while ( --a3 >= 0 )
  {
    a1 -= a2;
    a4();
  }
}

// 0x005536A9
void *__cdecl malloc(size_t Size)
{
  return _nh_malloc(Size, dword_1895328);
}

// 0x005536BB
_DWORD *__cdecl _nh_malloc(size_t Size, int a2)
{
  _DWORD *result; // eax

  if ( Size > 0xFFFFFFE0 )
    return 0;
  while ( 1 )
  {
    result = _heap_alloc(Size);
    if ( result || !a2 )
      break;
    if ( !_callnewh(Size) )
      return 0;
  }
  return result;
}

// 0x005536E7
_DWORD *__cdecl _heap_alloc(unsigned int a1)
{
  unsigned int v1; // esi
  _DWORD *result; // eax

  v1 = a1;
  if ( a1 > dword_60ACB4 || (result = __sbh_alloc_block(a1)) == 0 )
  {
    if ( !a1 )
      v1 = 1;
    return HeapAlloc(hHeap, 0, (v1 + 15) & 0xFFFFFFF0);
  }
  return result;
}

// 0x0055371D
int __cdecl fclose(FILE *Stream)
{
  int v1; // edi
  int flag; // eax
  int result; // eax

  v1 = -1;
  flag = Stream->_flag;
  if ( (flag & 0x40) != 0 )
  {
    result = -1;
  }
  else
  {
    if ( (flag & 0x83) != 0 )
    {
      v1 = _flush(Stream);
      _freebuf((int)Stream);
      if ( _close(Stream->_file) >= 0 )
      {
        if ( Stream->_tmpfname )
        {
          free(Stream->_tmpfname);
          Stream->_tmpfname = 0;
        }
      }
      else
      {
        v1 = -1;
      }
    }
    result = v1;
  }
  Stream->_flag = 0;
  return result;
}

// 0x00553773
int __cdecl fseek(FILE *Stream, int Offset, int Origin)
{
  int flag; // eax
  int v4; // edi
  int v5; // eax

  flag = Stream->_flag;
  if ( (flag & 0x83) != 0 && (v4 = Origin, (unsigned int)Origin <= 2) )
  {
    LOBYTE(flag) = flag & 0xEF;
    Stream->_flag = flag;
    if ( Origin == 1 )
    {
      Offset += ftell(Stream);
      v4 = 0;
    }
    _flush(Stream);
    v5 = Stream->_flag;
    if ( (v5 & 0x80u) == 0 )
    {
      if ( (v5 & 1) != 0 && (v5 & 8) != 0 && (v5 & 0x400) == 0 )
        Stream->_bufsiz = 512;
    }
    else
    {
      LOBYTE(v5) = v5 & 0xFC;
      Stream->_flag = v5;
    }
    return (_lseek(Stream->_file, Offset, v4) != -1) - 1;
  }
  else
  {
    g_PlayerData_33C = 22;
    return -1;
  }
}

// 0x005537FF
int __cdecl ftell(FILE *Stream)
{
  int file; // esi
  int v3; // eax
  int flag; // edx
  char *ptr; // eax
  char *base; // ecx
  char *i; // edx
  int cnt; // edx
  int v10; // eax
  _DWORD *v11; // ebx
  int v12; // esi
  char *v13; // eax
  char *v14; // ecx
  bool v15; // zf
  int bufsiz; // eax
  int v17; // ecx
  int FileHandle; // [esp+Ch] [ebp-Ch]
  char *v19; // [esp+10h] [ebp-8h]
  int Offset; // [esp+14h] [ebp-4h]
  int Streama; // [esp+20h] [ebp+8h]

  file = Stream->_file;
  FileHandle = file;
  if ( Stream->_cnt < 0 )
    Stream->_cnt = 0;
  v3 = _lseek(file, 0, 1);
  Offset = v3;
  if ( v3 < 0 )
    return -1;
  flag = Stream->_flag;
  if ( (flag & 0x108) == 0 )
    return v3 - Stream->_cnt;
  ptr = Stream->_ptr;
  base = Stream->_base;
  v19 = (char *)(Stream->_ptr - base);
  if ( (flag & 3) != 0 )
  {
    if ( *(char *)(*(&g_nUIState + (file >> 5)) + 8 * (file & 0x1F) + 4) < 0 )
    {
      for ( i = Stream->_base; i < ptr; ++i )
      {
        if ( *i == 10 )
          ++v19;
      }
    }
    goto LABEL_16;
  }
  if ( (flag & 0x80u) == 0 )
  {
    g_PlayerData_33C = 22;
    return -1;
  }
LABEL_16:
  if ( !Offset )
    return (int)v19;
  if ( (Stream->_flag & 1) != 0 )
  {
    cnt = Stream->_cnt;
    if ( cnt )
    {
      Streama = cnt + ptr - base;
      v10 = file >> 5;
      v11 = (_DWORD *)(4 * (file >> 5) + 25783264);
      v12 = 8 * (file & 0x1F);
      if ( *(char *)(v12 + *(&g_nUIState + v10) + 4) < 0 )
      {
        if ( _lseek(FileHandle, 0, 2) == Offset )
        {
          v13 = Stream->_base;
          v14 = &v13[Streama];
          while ( v13 < v14 )
          {
            if ( *v13 == 10 )
              ++Streama;
            ++v13;
          }
          v15 = (Stream->_flag & 0x2000) == 0;
        }
        else
        {
          _lseek(FileHandle, Offset, 0);
          bufsiz = 512;
          if ( (unsigned int)Streama > 0x200 || (v17 = Stream->_flag, (v17 & 8) == 0) || (v17 & 0x400) != 0 )
            bufsiz = Stream->_bufsiz;
          Streama = bufsiz;
          v15 = (*(_BYTE *)(v12 + *v11 + 4) & 4) == 0;
        }
        if ( !v15 )
          ++Streama;
      }
      Offset -= Streama;
    }
    else
    {
      v19 = 0;
    }
  }
  return (int)&v19[Offset];
}

// 0x00553957
size_t __cdecl fwrite(const void *Buffer, size_t ElementSize, size_t ElementCount, FILE *Stream)
{
  size_t v4; // edi
  size_t v5; // ebx
  unsigned int cnt; // eax
  size_t v9; // edi
  unsigned int v10; // edi
  unsigned int v11; // eax
  size_t v12; // eax
  int Streama; // [esp+24h] [ebp+14h]

  v4 = ElementCount * ElementSize;
  v5 = ElementCount * ElementSize;
  if ( !(ElementCount * ElementSize) )
    return 0;
  if ( (Stream->_flag & 0x10C) != 0 )
    Streama = Stream->_bufsiz;
  else
    Streama = 4096;
  while ( 1 )
  {
    if ( (Stream->_flag & 0x108) != 0 )
    {
      cnt = Stream->_cnt;
      if ( cnt )
      {
        v9 = v5;
        if ( v5 >= cnt )
          v9 = Stream->_cnt;
        memcpy_0(Stream->_ptr, Buffer, v9);
        Stream->_cnt -= v9;
        Stream->_ptr += v9;
        v5 -= v9;
        Buffer = (char *)Buffer + v9;
LABEL_19:
        v4 = ElementCount * ElementSize;
        goto LABEL_23;
      }
    }
    if ( v5 >= Streama )
      break;
    if ( _flsbuf(*(char *)Buffer, Stream) == -1 )
      goto LABEL_26;
    Buffer = (char *)Buffer + 1;
    --v5;
    Streama = Stream->_bufsiz;
    if ( Streama <= 0 )
      Streama = 1;
LABEL_23:
    if ( !v5 )
      return ElementCount;
  }
  if ( (Stream->_flag & 0x108) == 0 || !_flush(Stream) )
  {
    if ( Streama )
      v10 = v5 - v5 % Streama;
    else
      v10 = v5;
    v11 = _write(Stream->_file, Buffer, v10);
    if ( v11 == -1 || (Buffer = (char *)Buffer + v11, v5 -= v11, v11 < v10) )
    {
      Stream->_flag |= 0x20u;
      v12 = ElementCount * ElementSize;
      return (v12 - v5) / ElementSize;
    }
    goto LABEL_19;
  }
LABEL_26:
  v12 = v4;
  return (v12 - v5) / ElementSize;
}

// 0x00553A61
FILE *__cdecl _fsopen(const char *FileName, const char *Mode, int ShFlag)
{
  FILE *result; // eax

  result = (FILE *)_getstream();
  if ( result )
    return (FILE *)_openfile((char *)FileName, Mode, ShFlag, result);
  return result;
}

// 0x00553A81
FILE *__cdecl fopen(const char *FileName, const char *Mode)
{
  return _fsopen(FileName, Mode, 64);
}

// 0x00553AA0
char *__cdecl strncat(char *Destination, const char *Source, size_t Count)
{
  size_t v3; // ecx
  char *v4; // edi
  int v6; // eax
  int v7; // eax
  char *v8; // edi
  const char *v9; // esi
  char v10; // bl
  size_t v11; // ecx
  int v12; // edx
  char v13; // dl
  int v15; // eax

  v3 = Count;
  if ( !Count )
    return Destination;
  v4 = Destination;
  if ( ((unsigned __int8)Destination & 3) == 0 )
    goto find_end_of_front_string_loop;
  do
  {
    if ( !*v4++ )
    {
start_byte_3:
      v8 = v4 - 1;
      goto copy_start;
    }
  }
  while ( ((unsigned __int8)v4 & 3) != 0 );
  while ( 1 )
  {
    do
    {
find_end_of_front_string_loop:
      v6 = (*(_DWORD *)v4 + 2130640639) ^ ~*(_DWORD *)v4;
      v4 += 4;
    }
    while ( (v6 & 0x81010100) == 0 );
    v7 = *((_DWORD *)v4 - 1);
    if ( !(_BYTE)v7 )
      break;
    if ( !BYTE1(v7) )
    {
      v8 = v4 - 3;
      goto copy_start;
    }
    if ( ((unsigned int)&unk_FF0000 & v7) == 0 )
    {
      v8 = v4 - 2;
      goto copy_start;
    }
    if ( (v7 & 0xFF000000) == 0 )
      goto start_byte_3;
  }
  v8 = v4 - 4;
copy_start:
  v9 = Source;
  if ( ((unsigned __int8)Source & 3) == 0 )
  {
    v10 = Count;
    v11 = Count >> 2;
    if ( Count >> 2 )
      goto main_loop_entrance;
tail_loop_start:
    v3 = v10 & 3;
    if ( (v10 & 3) != 0 )
    {
      while ( 1 )
      {
        v13 = *v9++;
        *v8++ = v13;
        if ( !v13 )
          break;
        if ( !--v3 )
          goto empty_counter;
      }
    }
    else
    {
empty_counter:
      *v8 = v3;
    }
    return Destination;
  }
  do
  {
    LOBYTE(v12) = *v9++;
    if ( !(_BYTE)v12 )
    {
_byte_0:
      *v8 = v12;
      return Destination;
    }
    *v8++ = v12;
    if ( !--v3 )
      goto empty_counter;
  }
  while ( ((unsigned __int8)v9 & 3) != 0 );
  v10 = v3;
  v11 = v3 >> 2;
  if ( !v11 )
    goto tail_loop_start;
  while ( 1 )
  {
main_loop_entrance:
    v15 = (*(_DWORD *)v9 + 2130640639) ^ ~*(_DWORD *)v9;
    v12 = *(_DWORD *)v9;
    v9 += 4;
    if ( (v15 & 0x81010100) == 0 )
      goto main_loop;
    if ( !(_BYTE)v12 )
      goto _byte_0;
    if ( !BYTE1(v12) )
      break;
    if ( ((unsigned int)&unk_FF0000 & v12) == 0 )
    {
      *(_WORD *)v8 = v12;
      v8[2] = 0;
      return Destination;
    }
    if ( (v12 & 0xFF000000) == 0 )
    {
      *(_DWORD *)v8 = v12;
      return Destination;
    }
main_loop:
    *(_DWORD *)v8 = v12;
    v8 += 4;
    if ( !--v11 )
      goto tail_loop_start;
  }
  *(_WORD *)v8 = (unsigned __int8)v12;
  return Destination;
}

// 0x00553BD0
void __usercall _alloca_probe(unsigned int a1@<eax>, char a2)
{
  char *i; // ecx

  for ( i = &a2; a1 >= 0x1000; a1 -= 4096 )
    i -= 4096;
  __asm { retn }
}

// 0x00553C00
char *__cdecl strstr(const char *Str, const char *SubStr)
{
  char v2; // dl
  const char *v3; // edi
  char v4; // dh
  const char *v5; // ecx
  char *v6; // esi
  char v7; // al
  char v9; // ah
  char v10; // al
  char v11; // al

  v2 = *SubStr;
  v3 = Str;
  if ( !*SubStr )
    return (char *)Str;
  v4 = SubStr[1];
  if ( !v4 )
    JUMPOUT(0x554566);
findnext:
  v5 = SubStr;
  v6 = (char *)(v3 + 1);
  if ( *v3 == v2 )
    goto first_char_found;
  if ( *v3 )
  {
    while ( 2 )
    {
      v7 = *v6++;
      while ( v7 == v2 )
      {
first_char_found:
        v7 = *v6++;
        if ( v7 == v4 )
        {
          v3 = v6 - 1;
          while ( 1 )
          {
            v9 = v5[2];
            if ( !v9 )
              break;
            v10 = *v6;
            v6 += 2;
            if ( v10 != v9 )
              goto findnext;
            v11 = v5[3];
            if ( !v11 )
              break;
            v5 += 2;
            if ( v11 != *(v6 - 1) )
              goto findnext;
          }
          return (char *)(v3 - 1);
        }
      }
      if ( v7 )
        continue;
      break;
    }
  }
  return 0;
}

// 0x00553C80
char *__cdecl _strlwr(char *String)
{
  char *result; // eax
  char *i; // edx
  char v3; // cl
  size_t v4; // eax
  int v5; // edi
  CHAR *v6; // eax
  char *Block; // [esp+4h] [ebp-4h]

  Block = 0;
  if ( dword_18953A8 )
  {
    v4 = __crtLCMapStringA(dword_18953A8, 0x100u, String, (_BYTE *)0xFFFFFFFF, 0, 0, 0, 1);
    v5 = v4;
    if ( v4 )
    {
      v6 = (CHAR *)malloc(v4);
      Block = v6;
      if ( v6 )
      {
        if ( __crtLCMapStringA(dword_18953A8, 0x100u, String, (_BYTE *)0xFFFFFFFF, v6, v5, 0, 1) )
          strcpy(String, Block);
      }
    }
    free(Block);
    return String;
  }
  else
  {
    result = String;
    for ( i = String; *i; ++i )
    {
      v3 = *i;
      if ( *i >= 65 && v3 <= 90 )
        *i = v3 + 32;
    }
  }
  return result;
}

// 0x00553D20
void *__cdecl memcpy(void *a1, const void *Src, size_t Size)
{
  char *v3; // esi
  char *v4; // edi
  size_t v5; // ecx
  void *result; // eax
  char *v7; // esi
  char *v8; // edi
  size_t v9; // ecx

  v3 = (char *)Src;
  v4 = (char *)a1;
  if ( a1 > Src && a1 < (char *)Src + Size )
  {
    v7 = (char *)Src + Size - 4;
    v8 = (char *)a1 + Size - 4;
    if ( ((unsigned __int8)v8 & 3) == 0 )
    {
      v9 = Size >> 2;
      if ( Size >> 2 >= 8 )
      {
        while ( v9 )
        {
          *(_DWORD *)v8 = *(_DWORD *)v7;
          v7 -= 4;
          v8 -= 4;
          --v9;
        }
        switch ( Size & 3 )
        {
          case 0u:
            goto TrailDown0;
          case 1u:
            goto TrailDown1;
          case 2u:
            goto TrailDown2;
          case 3u:
            goto TrailDown3;
        }
      }
      switch ( Size & 3 )
      {
        case 0u:
          goto TrailDown0;
        case 1u:
          goto TrailDown1;
        case 2u:
          goto TrailDown2;
        case 3u:
          goto TrailDown3;
      }
    }
    switch ( Size )
    {
      case 0u:
TrailDown0:
        result = a1;
        break;
      case 1u:
TrailDown1:
        v8[3] = v7[3];
        result = a1;
        break;
      case 2u:
TrailDown2:
        v8[3] = v7[3];
        v8[2] = v7[2];
        result = a1;
        break;
      case 3u:
TrailDown3:
        v8[3] = v7[3];
        v8[2] = v7[2];
        v8[1] = v7[1];
        result = a1;
        break;
      default:
        __asm { jmp     dword ptr ds:loc_553F04+4[eax*4] }
        return result;
    }
  }
  else
  {
    if ( ((unsigned __int8)a1 & 3) != 0 )
    {
      if ( Size >= 4 )
        __asm { jmp     dword ptr ds:loc_553D7C+4[eax*4] }
      __asm { jmp     dword ptr ds:TrailUp0[ecx*4]; jumptable 00553D55 case 0 }
    }
    v5 = Size >> 2;
    switch ( v5 )
    {
      case 0u:
        goto UnwindUp0;
      case 1u:
        goto UnwindUp1;
      case 2u:
        goto UnwindUp2;
      case 3u:
        goto UnwindUp3;
      case 4u:
        goto UnwindUp4;
      case 5u:
        goto UnwindUp5;
      case 6u:
        goto UnwindUp6;
      case 7u:
        *((_DWORD *)a1 + v5 - 7) = *((_DWORD *)Src + v5 - 7);
UnwindUp6:
        *((_DWORD *)a1 + v5 - 6) = *((_DWORD *)Src + v5 - 6);
UnwindUp5:
        *((_DWORD *)a1 + v5 - 5) = *((_DWORD *)Src + v5 - 5);
UnwindUp4:
        *((_DWORD *)a1 + v5 - 4) = *((_DWORD *)Src + v5 - 4);
UnwindUp3:
        *((_DWORD *)a1 + v5 - 3) = *((_DWORD *)Src + v5 - 3);
UnwindUp2:
        *((_DWORD *)a1 + v5 - 2) = *((_DWORD *)Src + v5 - 2);
UnwindUp1:
        *((_DWORD *)a1 + v5 - 1) = *((_DWORD *)Src + v5 - 1);
        v3 = (char *)Src + 4 * v5;
        v4 = (char *)a1 + 4 * v5;
UnwindUp0:
        switch ( Size & 3 )
        {
          case 0u:
            goto TrailUp0;
          case 1u:
            goto TrailUp1;
          case 2u:
            goto TrailUp2;
          case 3u:
            goto TrailUp3;
        }
      default:
        qmemcpy(a1, Src, 4 * v5);
        v3 = (char *)Src + 4 * v5;
        v4 = (char *)a1 + 4 * v5;
        switch ( Size & 3 )
        {
          case 0u:
TrailUp0:
            result = a1;
            break;
          case 1u:
TrailUp1:
            *v4 = *v3;
            result = a1;
            break;
          case 2u:
TrailUp2:
            *v4 = *v3;
            v4[1] = v3[1];
            result = a1;
            break;
          case 3u:
TrailUp3:
            *v4 = *v3;
            v4[1] = v3[1];
            v4[2] = v3[2];
            result = a1;
            break;
        }
        break;
    }
  }
  return result;
}

// 0x00554055
int __cdecl atol(const char *String)
{
  int v3; // esi
  const char *v4; // edi
  int v5; // ebp
  int v6; // ebx
  int result; // eax

  while ( (int)cbMultiByte <= 1
        ? *((_BYTE *)g_pVtbl_SceneMgr + 2 * *(unsigned __int8 *)String) & 8
        : _isctype(*(unsigned __int8 *)String, 8) )
    ++String;
  v3 = *(unsigned __int8 *)String;
  v4 = String + 1;
  v5 = v3;
  if ( v3 == 45 || v3 == 43 )
    v3 = *(unsigned __int8 *)v4++;
  v6 = 0;
  while ( (int)cbMultiByte <= 1 ? *((_BYTE *)g_pVtbl_SceneMgr + 2 * v3) & 4 : _isctype(v3, 4) )
  {
    v6 = v3 + 10 * v6 - 48;
    v3 = *(unsigned __int8 *)v4++;
  }
  result = v6;
  if ( v5 == 45 )
    return -v6;
  return result;
}

// 0x005540E0
int __cdecl atoi(const char *String)
{
  return atol(String);
}

// 0x005540F0
char *__cdecl strncpy(char *Destination, const char *Source, size_t Count)
{
  size_t v3; // ecx
  size_t v4; // ebx
  const char *v5; // esi
  char *v6; // edi
  size_t v7; // ecx
  char v8; // al
  size_t v10; // ecx
  int v11; // eax
  int v12; // edx

  v3 = Count;
  if ( !Count )
    return Destination;
  v4 = Count;
  v5 = Source;
  v6 = Destination;
  if ( ((unsigned __int8)Source & 3) == 0 )
  {
    v7 = Count >> 2;
    if ( Count >> 2 )
      goto main_loop_entrance_0;
copy_tail_loop:
    while ( 1 )
    {
      v8 = *v5++;
      *v6++ = v8;
      if ( !v8 )
        break;
      if ( !--v4 )
        return Destination;
    }
    while ( --v4 )
finish_loop:
      *v6++ = v8;
    return Destination;
  }
  do
  {
    v8 = *v5++;
    *v6++ = v8;
    if ( !--v3 )
      return Destination;
    if ( !v8 )
    {
      while ( ((unsigned __int8)v6 & 3) != 0 )
      {
        *v6++ = 0;
        if ( !--v3 )
          return Destination;
      }
      v4 = v3;
      v10 = v3 >> 2;
      if ( !v10 )
        goto finish_loop;
      goto fill_dwords_with_EOS;
    }
  }
  while ( ((unsigned __int8)v5 & 3) != 0 );
  LOBYTE(v4) = v3;
  v7 = v3 >> 2;
  if ( !v7 )
  {
tail_loop_start_0:
    v4 &= 3u;
    if ( v4 )
      goto copy_tail_loop;
    return Destination;
  }
  while ( 1 )
  {
main_loop_entrance_0:
    v11 = (*(_DWORD *)v5 + 2130640639) ^ ~*(_DWORD *)v5;
    v12 = *(_DWORD *)v5;
    v5 += 4;
    if ( (v11 & 0x81010100) == 0 )
      goto main_loop_0;
    if ( !(_BYTE)v12 )
      break;
    if ( !BYTE1(v12) )
    {
      *(_DWORD *)v6 = (unsigned __int8)v12;
      goto fill_with_EOS_dwords;
    }
    if ( ((unsigned int)&unk_FF0000 & v12) == 0 )
    {
      *(_DWORD *)v6 = (unsigned __int16)v12;
      goto fill_with_EOS_dwords;
    }
    if ( (v12 & 0xFF000000) == 0 )
    {
      *(_DWORD *)v6 = v12;
      goto fill_with_EOS_dwords;
    }
main_loop_0:
    *(_DWORD *)v6 = v12;
    v6 += 4;
    if ( !--v7 )
      goto tail_loop_start_0;
  }
  *(_DWORD *)v6 = 0;
fill_with_EOS_dwords:
  v6 += 4;
  v8 = 0;
  v10 = v7 - 1;
  if ( v10 )
  {
fill_dwords_with_EOS:
    v8 = 0;
    do
    {
      *(_DWORD *)v6 = 0;
      v6 += 4;
      --v10;
    }
    while ( v10 );
  }
  v4 &= 3u;
  if ( v4 )
    goto finish_loop;
  return Destination;
}

// 0x005541F8
int __cdecl rand()
{
  dword_60AC60 = 214013 * dword_60AC60 + 2531011;
  return (dword_60AC60 >> 16) & 0x7FFF;
}

// 0x00554216
size_t __cdecl fread(void *Buffer, size_t ElementSize, size_t ElementCount, FILE *Stream)
{
  size_t v4; // edi
  size_t v6; // ecx
  unsigned int cnt; // eax
  size_t v10; // edi
  unsigned int v11; // eax
  int v12; // eax
  int v13; // eax
  size_t Buffera; // [esp+18h] [ebp+8h]
  unsigned int Streama; // [esp+24h] [ebp+14h]

  v4 = ElementCount * ElementSize;
  v6 = ElementCount * ElementSize;
  Buffera = ElementCount * ElementSize;
  if ( !(ElementCount * ElementSize) )
    return 0;
  if ( (Stream->_flag & 0x10C) != 0 )
    Streama = Stream->_bufsiz;
  else
    Streama = 4096;
  while ( 1 )
  {
    if ( (Stream->_flag & 0x10C) != 0 )
    {
      cnt = Stream->_cnt;
      if ( cnt )
      {
        v10 = v6;
        if ( v6 >= cnt )
          v10 = Stream->_cnt;
        memcpy_0(Buffer, Stream->_ptr, v10);
        Buffera -= v10;
        Stream->_cnt -= v10;
        Stream->_ptr += v10;
        Buffer = (char *)Buffer + v10;
        v4 = ElementCount * ElementSize;
        goto LABEL_20;
      }
    }
    if ( v6 >= Streama )
      break;
    v13 = _filbuf(Stream);
    if ( v13 == -1 )
      return (v4 - Buffera) / ElementSize;
    *(_BYTE *)Buffer = v13;
    Buffer = (char *)Buffer + 1;
    --Buffera;
    Streama = Stream->_bufsiz;
LABEL_20:
    if ( !Buffera )
      return ElementCount;
    v6 = Buffera;
  }
  v11 = v6;
  if ( Streama )
    v11 = v6 - v6 % Streama;
  v12 = _read(Stream->_file, Buffer, v11);
  if ( !v12 )
  {
    Stream->_flag |= 0x10u;
    return (v4 - Buffera) / ElementSize;
  }
  if ( v12 != -1 )
  {
    Buffera -= v12;
    Buffer = (char *)Buffer + v12;
    goto LABEL_20;
  }
  Stream->_flag |= 0x20u;
  return (v4 - Buffera) / ElementSize;
}

// 0x005542FE
int _snprintf(char *const Buffer, const size_t BufferCount, const char *const Format, ...)
{
  int v3; // eax
  bool v4; // sf
  int v5; // esi
  FILE File; // [esp+4h] [ebp-20h] BYREF
  va_list va; // [esp+38h] [ebp+14h] BYREF

  va_start(va, Format);
  File._base = Buffer;
  File._ptr = Buffer;
  File._flag = 66;
  File._cnt = BufferCount;
  v3 = _output(&File, (char *)Format, (int)va);
  v4 = --File._cnt < 0;
  v5 = v3;
  if ( v4 )
    _flsbuf(0, &File);
  else
    *File._ptr = 0;
  return v5;
}

// 0x0055434F
void __noreturn _purecall()
{
  _amsg_exit(0x19u);
}

// 0x00554360
double __usercall _CIacos@<st0>(unsigned __int64 x@<st0>)
{
  int v2; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  _checkTOS_withFB(x, HIDWORD(x));
  return sub_55437D(v2, v3);
}

// 0x00554374
double __cdecl acos(double X)
{
  int v1; // ecx

  _fload_withFB(v1, &X);
  return sub_55437D(LODWORD(X), HIDWORD(X));
}

// 0x00554430
double __usercall _CIasin@<st0>(unsigned __int64 x@<st0>)
{
  int v2; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  _checkTOS_withFB(x, HIDWORD(x));
  return sub_55444D(v2, v3);
}

// 0x00554444
double __cdecl asin(double X)
{
  int v1; // ecx

  _fload_withFB(v1, &X);
  return sub_55444D(LODWORD(X), HIDWORD(X));
}

// 0x005544FB
double __cdecl atof(const char *String)
{
  while ( (int)cbMultiByte <= 1
        ? *((_BYTE *)g_pVtbl_SceneMgr + 2 * *(unsigned __int8 *)String) & 8
        : _isctype(*(unsigned __int8 *)String, 8) )
    ++String;
  strlen(String);
  return *((double *)_fltin((char *)String) + 2);
}

// 0x00554560
char *__cdecl strchr(const char *Str, int Val)
{
  const char *v2; // edx
  char v3; // cl
  int v4; // ecx
  int v5; // esi
  int v6; // eax
  unsigned int v7; // eax
  unsigned int v9; // eax
  unsigned int v10; // eax

  v2 = Str;
  if ( ((unsigned __int8)Str & 3) != 0 )
  {
    while ( 1 )
    {
      v3 = *v2++;
      if ( v3 == (_BYTE)Val )
        return (char *)(v2 - 1);
      if ( !v3 )
        return 0;
      if ( ((unsigned __int8)v2 & 3) == 0 )
        goto main_loop_1;
    }
  }
  else
  {
    while ( 1 )
    {
main_loop_1:
      while ( 1 )
      {
        v4 = (((unsigned __int8)Val << 8)
            | (unsigned __int8)Val
            | ((((unsigned __int8)Val << 8) | (unsigned __int8)Val) << 16))
           ^ *(_DWORD *)v2;
        v5 = *(_DWORD *)v2 + 2130640639;
        v6 = v5 ^ ~*(_DWORD *)v2;
        v2 += 4;
        if ( (((v4 + 2130640639) ^ ~v4) & 0x81010100) != 0 )
          break;
        v7 = v6 & 0x81010100;
        if ( v7 && (((unsigned int)&unk_1010100 & v7) != 0 || (v5 & 0x80000000) == 0) )
          return 0;
      }
      v9 = *((_DWORD *)v2 - 1);
      if ( (_BYTE)v9 == (_BYTE)Val )
        break;
      if ( !(_BYTE)v9 )
        return 0;
      if ( BYTE1(v9) == (_BYTE)Val )
        return (char *)(v2 - 3);
      if ( !BYTE1(v9) )
        return 0;
      v10 = HIWORD(v9);
      if ( (_BYTE)v10 == (_BYTE)Val )
        return (char *)(v2 - 2);
      if ( !(_BYTE)v10 )
        return 0;
      if ( BYTE1(v10) == (_BYTE)Val )
        return (char *)(v2 - 1);
      if ( !BYTE1(v10) )
        return 0;
    }
    return (char *)(v2 - 4);
  }
}

// 0x0055461C
int __cdecl vsprintf(char *const Buffer, const char *const Format, va_list ArgList)
{
  int v3; // eax
  bool v4; // sf
  int v5; // esi
  FILE File; // [esp+4h] [ebp-20h] BYREF

  File._base = Buffer;
  File._ptr = Buffer;
  File._flag = 66;
  File._cnt = 0x7FFFFFFF;
  v3 = _output(&File, (char *)Format, (int)ArgList);
  v4 = --File._cnt < 0;
  v5 = v3;
  if ( v4 )
    _flsbuf(0, &File);
  else
    *File._ptr = 0;
  return v5;
}

// 0x00554670
char *__cdecl strrchr(const char *Str, int Ch)
{
  unsigned int v2; // ecx
  const char *v3; // edi
  bool v4; // zf
  char *v5; // edi

  v2 = strlen(Str) + 1;
  v3 = &Str[v2 - 1];
  do
  {
    if ( !v2 )
      break;
    v4 = *v3-- == (unsigned __int8)Ch;
    --v2;
  }
  while ( !v4 );
  v5 = (char *)(v3 + 1);
  if ( *v5 == (_BYTE)Ch )
    return v5;
  else
    return 0;
}

// 0x00554697
unsigned __int8 *__cdecl _mbsrchr(const unsigned __int8 *String, unsigned int C)
{
  unsigned __int8 *result; // eax
  const unsigned __int8 *i; // edx
  unsigned __int8 v4; // bl
  int v5; // ecx
  bool v6; // zf

  result = 0;
  if ( dword_18969BC )
  {
    for ( i = String; ; ++i )
    {
      v4 = *i;
      v5 = *i;
      if ( (*(&g_bQuestActive + (unsigned __int8)v5) & 4) == 0 )
        break;
      v4 = *++i;
      if ( !v4 )
      {
        v6 = result == 0;
        goto LABEL_10;
      }
      if ( C == (v4 | (v5 << 8)) )
        result = (unsigned __int8 *)(i - 1);
LABEL_12:
      if ( !v4 )
        return result;
    }
    v6 = C == v5;
LABEL_10:
    if ( v6 )
      result = (unsigned __int8 *)i;
    goto LABEL_12;
  }
  return (unsigned __int8 *)strrchr((const char *)String, C);
}

// 0x00554700
long double __usercall _CIpow@<st0>(unsigned __int64 x@<st0>, long double y@<st1>)
{
  return sub_554722(
           HIDWORD(*(unsigned __int64 *)&y),
           *(double *)&x,
           y,
           x,
           HIDWORD(x),
           SLODWORD(y),
           HIDWORD(*(unsigned __int64 *)&y));
}

// 0x00554719
double __cdecl pow(double X, double Y)
{
  int v2; // ecx
  double v3; // st6
  int v4; // eax
  double v5; // st7

  v5 = _fload_withFB(v2, &Y);
  return sub_554722(v4, v3, v5, SLODWORD(X), SHIDWORD(X), SLODWORD(Y), SHIDWORD(Y));
}

// 0x0055491D
int __cdecl fflush(FILE *Stream)
{
  if ( !Stream )
    return flsall(0);
  if ( _flush(Stream) )
    return -1;
  if ( (Stream->_flag & 0x4000) != 0 )
    return -(_commit(Stream->_file) != 0);
  return 0;
}

// 0x00554958
int __cdecl _flush(_DWORD *a1)
{
  int v1; // ebx
  const void *v2; // eax
  unsigned int v3; // edi
  int v4; // eax
  int v5; // eax

  v1 = 0;
  if ( (a1[3] & 3) == 2 && (a1[3] & 0x108) != 0 )
  {
    v2 = (const void *)a1[2];
    if ( *a1 - (int)v2 > 0 )
    {
      v3 = *a1 - (_DWORD)v2;
      if ( _write(a1[4], v2, v3) == v3 )
      {
        v4 = a1[3];
        if ( (v4 & 0x80u) != 0 )
        {
          LOBYTE(v4) = v4 & 0xFD;
          a1[3] = v4;
        }
      }
      else
      {
        a1[3] |= 0x20u;
        v1 = -1;
      }
    }
  }
  v5 = a1[2];
  a1[1] = 0;
  *a1 = v5;
  return v1;
}

// 0x005549B4
int __cdecl _flushall()
{
  return flsall(1);
}

// 0x005549BD
int __cdecl flsall(int a1)
{
  signed int v1; // esi
  int v2; // ebx
  int i; // edi
  FILE *v4; // eax
  int flag; // ecx
  int result; // eax

  v1 = 0;
  v2 = 0;
  for ( i = 0; v1 < (int)Count; ++v1 )
  {
    v4 = *(FILE **)(g_PlayerLevel + 4 * v1);
    if ( v4 )
    {
      flag = v4->_flag;
      if ( (flag & 0x83) != 0 )
      {
        if ( a1 == 1 )
        {
          if ( fflush(v4) != -1 )
            ++v2;
        }
        else if ( !a1 && (flag & 2) != 0 && fflush(*(FILE **)(g_PlayerLevel + 4 * v1)) == -1 )
        {
          i = -1;
        }
      }
    }
  }
  result = v2;
  if ( a1 != 1 )
    return i;
  return result;
}

// 0x00554A2A
char *__cdecl fgets(char *Buffer, int MaxCount, FILE *Stream)
{
  char *v3; // ebx
  char *v4; // edi
  int v7; // eax
  int MaxCounta; // [esp+14h] [ebp+Ch]

  v3 = Buffer;
  v4 = Buffer;
  if ( MaxCount <= 0 )
    return 0;
  MaxCounta = MaxCount - 1;
  if ( !MaxCounta )
    goto LABEL_10;
  while ( 1 )
  {
    if ( --Stream->_cnt < 0 )
      v7 = _filbuf(Stream);
    else
      v7 = *(unsigned __int8 *)Stream->_ptr++;
    if ( v7 == -1 )
      break;
    *v4++ = v7;
    if ( (_BYTE)v7 != 10 )
    {
      if ( --MaxCounta )
        continue;
    }
    goto LABEL_10;
  }
  if ( v4 == Buffer )
    return 0;
LABEL_10:
  *v4 = 0;
  return v3;
}

// 0x00554A81
int fscanf(FILE *const Stream, const char *const Format, ...)
{
  va_list va; // [esp+Ch] [ebp+Ch] BYREF

  va_start(va, Format);
  return _input(Stream, (char *)Format, (int)va);
}

// 0x00554AA0
void *__cdecl memchr(const void *Buf, int Val, size_t MaxCount)
{
  void *result; // eax
  unsigned __int8 *v4; // edx
  int v5; // ebx
  unsigned __int8 v6; // cl
  bool v7; // cf
  char *v8; // eax
  unsigned __int8 v9; // cl
  int v10; // ecx
  unsigned int v11; // ecx
  unsigned int v12; // ecx

  result = (void *)MaxCount;
  if ( MaxCount )
  {
    v4 = (unsigned __int8 *)Buf;
    LOBYTE(v5) = Val;
    if ( ((unsigned __int8)Buf & 3) != 0 )
    {
      do
      {
        v6 = *v4++;
        if ( (unsigned __int8)Val == v6 )
          return v4 - 1;
        result = (char *)result - 1;
        if ( !result )
          return result;
      }
      while ( ((unsigned __int8)v4 & 3) != 0 );
    }
    v7 = (unsigned int)result < 4;
    v8 = (char *)result - 4;
    if ( !v7 )
    {
      v5 = 16843009 * (unsigned __int8)Val;
      do
      {
        v10 = v5 ^ *(_DWORD *)v4;
        v4 += 4;
        if ( (((v10 + 2130640639) ^ ~v10) & 0x81010100) != 0 )
        {
          v11 = *((_DWORD *)v4 - 1);
          LOBYTE(v11) = Val ^ v11;
          if ( !(_BYTE)v11 )
            return v4 - 4;
          BYTE1(v11) ^= Val;
          if ( !BYTE1(v11) )
            return v4 - 3;
          v12 = HIWORD(v11);
          if ( (unsigned __int8)Val == (unsigned __int8)v12 )
            return v4 - 2;
          if ( (unsigned __int8)Val == BYTE1(v12) )
            return v4 - 1;
        }
        v7 = (unsigned int)v8 < 4;
        v8 -= 4;
      }
      while ( !v7 );
    }
    result = v8 + 4;
    if ( result )
    {
      while ( 1 )
      {
        v9 = *v4++;
        if ( (unsigned __int8)v5 == v9 )
          break;
        result = (char *)result - 1;
        if ( !result )
          return result;
      }
      return v4 - 1;
    }
  }
  return result;
}

// 0x00554B45
char *__cdecl _strtime(char *Buffer)
{
  int v1; // edi
  __int64 v2; // rax
  int SystemTime; // [esp+Ch] [ebp-10h] BYREF
  unsigned __int16 SystemTime_8; // [esp+14h] [ebp-8h]
  unsigned __int16 SystemTime_10; // [esp+16h] [ebp-6h]
  unsigned __int16 SystemTime_12; // [esp+18h] [ebp-4h]

  GetLocalTime((LPSYSTEMTIME)&SystemTime);
  v1 = SystemTime_8;
  v2 = SystemTime_8;
  Buffer[8] = 0;
  Buffer[5] = 58;
  Buffer[2] = 58;
  *Buffer = v2 / 10 + 48;
  LODWORD(v2) = SystemTime_10;
  Buffer[1] = v1 % 10 + 48;
  Buffer[3] = (int)v2 / 10 + 48;
  LODWORD(v2) = SystemTime_12;
  Buffer[4] = SystemTime_10 % 10 + 48;
  Buffer[6] = (int)v2 / 10 + 48;
  Buffer[7] = SystemTime_12 % 10 + 48;
  return Buffer;
}

// 0x00554BBE
char *__cdecl _strdate(char *Buffer)
{
  int v1; // edx
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  unsigned __int16 SystemTime; // [esp+Ch] [ebp-14h] BYREF
  unsigned __int16 SystemTime_2; // [esp+Eh] [ebp-12h]
  unsigned __int16 SystemTime_6; // [esp+12h] [ebp-Eh]
  int v10; // [esp+1Ch] [ebp-4h]

  GetLocalTime((LPSYSTEMTIME)&SystemTime);
  v1 = SystemTime % 100;
  v2 = SystemTime_2;
  v3 = SystemTime_2;
  Buffer[8] = 0;
  Buffer[5] = 47;
  Buffer[2] = 47;
  v10 = v1;
  *Buffer = v3 / 10 + 48;
  v4 = SystemTime_6;
  Buffer[1] = v2 % 10 + 48;
  Buffer[3] = v4 / 10 + 48;
  v5 = v10;
  Buffer[4] = SystemTime_6 % 10 + 48;
  Buffer[6] = v5 / 10 + 48;
  Buffer[7] = v10 % 10 + 48;
  return Buffer;
}

// 0x00554C42
int fprintf(FILE *const Stream, const char *const Format, ...)
{
  int v2; // esi
  int v3; // edi
  va_list va; // [esp+18h] [ebp+10h] BYREF

  va_start(va, Format);
  v2 = _stbuf((int)Stream);
  v3 = _output(Stream, (char *)Format, (int)va);
  _ftbuf(v2, (int)Stream);
  return v3;
}

// 0x00554C74
int __cdecl _close(int FileHandle)
{
  int v1; // esi
  intptr_t osfhandle; // ebp
  void *v3; // eax
  DWORD LastError; // ebp

  if ( FileHandle < uNumber
    && (v1 = 8 * (FileHandle & 0x1F), (*(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + v1 + 4) & 1) != 0) )
  {
    if ( _get_osfhandle(FileHandle) == -1
      || (FileHandle == 1 || FileHandle == 2) && (osfhandle = _get_osfhandle(2), _get_osfhandle(1) == osfhandle)
      || (v3 = (void *)_get_osfhandle(FileHandle), CloseHandle(v3)) )
    {
      LastError = 0;
    }
    else
    {
      LastError = GetLastError();
    }
    _free_osfhnd(FileHandle);
    *(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + v1 + 4) = 0;
    if ( !LastError )
      return 0;
    _dosmaperr(LastError);
  }
  else
  {
    g_PlayerData_340 = 0;
    g_PlayerData_33C = 9;
  }
  return -1;
}

// 0x00554D27
int _sopen(const char *FileName, int OpenFlag, int ShareFlag, ...)
{
  unsigned int v3; // ecx
  DWORD v4; // esi
  int v5; // ebx
  HANDLE v6; // eax
  void *v7; // esi
  DWORD FileType; // eax
  DWORD LastError; // eax
  char v11; // al
  int v12; // esi
  bool v13; // zf
  struct _SECURITY_ATTRIBUTES SecurityAttributes; // [esp+Ch] [ebp-1Ch] BYREF
  DWORD dwShareMode; // [esp+18h] [ebp-10h]
  DWORD dwDesiredAccess; // [esp+1Ch] [ebp-Ch]
  DWORD dwCreationDisposition; // [esp+20h] [ebp-8h]
  char v18; // [esp+27h] [ebp-1h]
  char lpFileName_3; // [esp+33h] [ebp+Bh]
  int v20; // [esp+3Ch] [ebp+14h]
  va_list va; // [esp+40h] [ebp+18h] BYREF

  va_start(va, ShareFlag);
  v20 = va_arg(va, _DWORD);
  SecurityAttributes.nLength = 12;
  SecurityAttributes.lpSecurityDescriptor = 0;
  if ( (OpenFlag & 0x80u) == 0 )
  {
    v18 = 0;
    SecurityAttributes.bInheritHandle = 1;
  }
  else
  {
    SecurityAttributes.bInheritHandle = 0;
    v18 = 16;
  }
  if ( (OpenFlag & 0x8000) == 0 && ((OpenFlag & 0x4000) != 0 || dword_18953E8 != 0x8000) )
    v18 |= 0x80u;
  if ( (OpenFlag & 3) != 0 )
  {
    if ( (OpenFlag & 3) == 1 )
    {
      dwDesiredAccess = 0x40000000;
    }
    else
    {
      if ( (OpenFlag & 3) != 2 )
      {
LABEL_11:
        g_PlayerData_33C = 22;
        g_PlayerData_340 = 0;
        return -1;
      }
      dwDesiredAccess = -1073741824;
    }
  }
  else
  {
    dwDesiredAccess = 0x80000000;
  }
  switch ( ShareFlag )
  {
    case 16:
      dwShareMode = 0;
      break;
    case 32:
      dwShareMode = 1;
      break;
    case 48:
      dwShareMode = 2;
      break;
    case 64:
      dwShareMode = 3;
      break;
    default:
      goto LABEL_11;
  }
  v3 = OpenFlag & 0x700;
  if ( v3 > 0x400 )
  {
    if ( v3 != 1280 )
    {
      if ( v3 == 1536 )
        goto LABEL_36;
      if ( v3 != 1792 )
        goto LABEL_11;
    }
    dwCreationDisposition = 1;
    goto LABEL_38;
  }
  if ( v3 == 1024 || (OpenFlag & 0x700) == 0 )
  {
    dwCreationDisposition = 3;
    goto LABEL_38;
  }
  if ( v3 == 256 )
  {
    dwCreationDisposition = 4;
    goto LABEL_38;
  }
  if ( v3 == 512 )
  {
LABEL_36:
    dwCreationDisposition = 5;
    goto LABEL_38;
  }
  if ( v3 != 768 )
    goto LABEL_11;
  dwCreationDisposition = 2;
LABEL_38:
  v4 = 128;
  if ( (OpenFlag & 0x100) != 0 && (v20 & ~(_BYTE)dword_1895344 & 0x80u) == 0 )
    v4 = 1;
  if ( (OpenFlag & 0x40) != 0 )
  {
    v4 |= 0x4000000u;
    BYTE2(dwDesiredAccess) |= 1u;
  }
  if ( (OpenFlag & 0x1000) != 0 )
    v4 |= 0x100u;
  if ( (OpenFlag & 0x20) != 0 )
  {
    v4 |= 0x8000000u;
  }
  else if ( (OpenFlag & 0x10) != 0 )
  {
    v4 |= 0x10000000u;
  }
  v5 = _alloc_osfhnd();
  if ( v5 == -1 )
  {
    g_PlayerData_340 = 0;
    g_PlayerData_33C = 24;
    return -1;
  }
  v6 = CreateFileA(FileName, dwDesiredAccess, dwShareMode, &SecurityAttributes, dwCreationDisposition, v4, 0);
  v7 = v6;
  if ( v6 == (HANDLE)-1 )
  {
LABEL_54:
    LastError = GetLastError();
    _dosmaperr(LastError);
    return -1;
  }
  FileType = GetFileType(v6);
  switch ( FileType )
  {
    case 0u:
      CloseHandle(v7);
      goto LABEL_54;
    case 2u:
      v18 |= 0x40u;
      break;
    case 3u:
      v18 |= 8u;
      break;
  }
  _set_osfhnd(v5, v7);
  v11 = v18 | 1;
  v12 = 8 * (v5 & 0x1F);
  v13 = (v18 & 0x48) == 0;
  lpFileName_3 = v18 & 0x48;
  *(_BYTE *)(*(&g_nUIState + (v5 >> 5)) + v12 + 4) = v18 | 1;
  if ( v13 && v11 < 0 && (OpenFlag & 2) != 0 )
  {
    dwShareMode = _lseek(v5, -1, 2);
    if ( dwShareMode == -1 )
    {
      if ( g_PlayerData_340 != 131 )
      {
LABEL_70:
        _close(v5);
        return -1;
      }
    }
    else
    {
      HIBYTE(ShareFlag) = 0;
      if ( !_read(v5, (char *)&ShareFlag + 3, 1u) && HIBYTE(ShareFlag) == 26 && _chsize(v5, dwShareMode) == -1
        || _lseek(v5, 0, 0) == -1 )
      {
        goto LABEL_70;
      }
    }
  }
  if ( !lpFileName_3 && (OpenFlag & 8) != 0 )
    *(_BYTE *)(*(&g_nUIState + (v5 >> 5)) + v12 + 4) |= 0x20u;
  return v5;
}

// 0x00554FE0
char *__cdecl strtok(char *String, const char *Delimiter)
{
  char v3; // dl
  char *v4; // edx
  char *v5; // ebx
  _BYTE v7[32]; // [esp+Ch] [ebp-20h] BYREF

  memset(v7, 0, sizeof(v7));
  do
  {
    v3 = *Delimiter;
    v7[*(unsigned __int8 *)Delimiter >> 3] |= 1 << (*Delimiter & 7);
    ++Delimiter;
  }
  while ( v3 );
  v4 = String;
  if ( !String )
    v4 = (char *)dword_1895314;
  while ( ((unsigned __int8)(1 << (*v4 & 7)) & v7[(unsigned __int8)*v4 >> 3]) != 0 && *v4 )
    ++v4;
  v5 = v4;
  while ( *v4 )
  {
    if ( ((unsigned __int8)(1 << (*v4 & 7)) & v7[(unsigned __int8)*v4 >> 3]) != 0 )
    {
      *v4++ = 0;
      break;
    }
    ++v4;
  }
  dword_1895314 = (int)v4;
  return v4 != v5 ? v5 : 0;
}

// 0x0055507C
void __noreturn start()
{
  DWORD Version; // eax
  int wShowWindow; // eax
  HMODULE ModuleHandleA; // eax
  int v3; // [esp-4h] [ebp-78h]
  CHAR *lpCmdLine; // [esp+10h] [ebp-64h]
  int v5; // [esp+14h] [ebp-60h]
  struct _STARTUPINFOA StartupInfo; // [esp+18h] [ebp-5Ch] BYREF
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
  StartupInfo.dwFlags = 0;
  GetStartupInfoA(&StartupInfo);
  lpCmdLine = _wincmdln();
  if ( (StartupInfo.dwFlags & 1) != 0 )
    wShowWindow = StartupInfo.wShowWindow;
  else
    wShowWindow = 10;
  v3 = wShowWindow;
  ModuleHandleA = GetModuleHandleA(0);
  v5 = WinMain(ModuleHandleA, 0, lpCmdLine, v3);
  exit(v5);
}

// 0x00555172
void __cdecl __noreturn _amsg_exit(DWORD NumberOfBytesWritten)
{
  if ( dword_1895320 == 1 )
    _FF_MSGBANNER();
  _NMSG_WRITE(NumberOfBytesWritten);
  off_60ACA0(255);
}

// 0x00555197
void __cdecl __noreturn fast_error_exit(DWORD NumberOfBytesWritten)
{
  if ( dword_1895320 == 1 )
    _FF_MSGBANNER();
  _NMSG_WRITE(NumberOfBytesWritten);
  ExitProcess(0xFFu);
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

// 0x00555290
size_t __cdecl strlen(const char *Str)
{
  const char *v1; // ecx
  int v3; // eax
  int v4; // eax

  v1 = Str;
  if ( ((unsigned __int8)Str & 3) == 0 )
    goto main_loop_3;
  do
  {
    if ( !*v1++ )
      return v1 - 1 - Str;
  }
  while ( ((unsigned __int8)v1 & 3) != 0 );
  while ( 1 )
  {
    do
    {
main_loop_3:
      v3 = (*(_DWORD *)v1 + 2130640639) ^ ~*(_DWORD *)v1;
      v1 += 4;
    }
    while ( (v3 & 0x81010100) == 0 );
    v4 = *((_DWORD *)v1 - 1);
    if ( !(_BYTE)v4 )
      break;
    if ( !BYTE1(v4) )
      return v1 - 3 - Str;
    if ( ((unsigned int)&unk_FF0000 & v4) == 0 )
      return v1 - 2 - Str;
    if ( (v4 & 0xFF000000) == 0 )
      return v1 - 1 - Str;
  }
  return v1 - 4 - Str;
}

// 0x0055530C
void _EH_prolog()
{
  __asm { retn }
}

// 0x00555330
void *__cdecl memcpy_0(void *a1, const void *Src, size_t Size)
{
  char *v3; // esi
  char *v4; // edi
  size_t v5; // ecx
  void *result; // eax
  char *v7; // esi
  char *v8; // edi
  size_t v9; // ecx

  v3 = (char *)Src;
  v4 = (char *)a1;
  if ( a1 > Src && a1 < (char *)Src + Size )
  {
    v7 = (char *)Src + Size - 4;
    v8 = (char *)a1 + Size - 4;
    if ( ((unsigned __int8)v8 & 3) == 0 )
    {
      v9 = Size >> 2;
      if ( Size >> 2 >= 8 )
      {
        while ( v9 )
        {
          *(_DWORD *)v8 = *(_DWORD *)v7;
          v7 -= 4;
          v8 -= 4;
          --v9;
        }
        switch ( Size & 3 )
        {
          case 0u:
            goto TrailDown0_0;
          case 1u:
            goto TrailDown1_0;
          case 2u:
            goto TrailDown2_0;
          case 3u:
            goto TrailDown3_0;
        }
      }
      switch ( Size & 3 )
      {
        case 0u:
          goto TrailDown0_0;
        case 1u:
          goto TrailDown1_0;
        case 2u:
          goto TrailDown2_0;
        case 3u:
          goto TrailDown3_0;
      }
    }
    switch ( Size )
    {
      case 0u:
TrailDown0_0:
        result = a1;
        break;
      case 1u:
TrailDown1_0:
        v8[3] = v7[3];
        result = a1;
        break;
      case 2u:
TrailDown2_0:
        v8[3] = v7[3];
        v8[2] = v7[2];
        result = a1;
        break;
      case 3u:
TrailDown3_0:
        v8[3] = v7[3];
        v8[2] = v7[2];
        v8[1] = v7[1];
        result = a1;
        break;
      default:
        __asm { jmp     dword ptr ds:loc_555514+4[eax*4] }
        return result;
    }
  }
  else
  {
    if ( ((unsigned __int8)a1 & 3) != 0 )
    {
      if ( Size >= 4 )
        __asm { jmp     dword ptr ds:loc_55538C+4[eax*4] }
      __asm { jmp     dword ptr ds:TrailUp0_0[ecx*4]; jumptable 00555365 case 0 }
    }
    v5 = Size >> 2;
    switch ( v5 )
    {
      case 0u:
        goto UnwindUp0_0;
      case 1u:
        goto UnwindUp1_0;
      case 2u:
        goto UnwindUp2_0;
      case 3u:
        goto UnwindUp3_0;
      case 4u:
        goto UnwindUp4_0;
      case 5u:
        goto UnwindUp5_0;
      case 6u:
        goto UnwindUp6_0;
      case 7u:
        *((_DWORD *)a1 + v5 - 7) = *((_DWORD *)Src + v5 - 7);
UnwindUp6_0:
        *((_DWORD *)a1 + v5 - 6) = *((_DWORD *)Src + v5 - 6);
UnwindUp5_0:
        *((_DWORD *)a1 + v5 - 5) = *((_DWORD *)Src + v5 - 5);
UnwindUp4_0:
        *((_DWORD *)a1 + v5 - 4) = *((_DWORD *)Src + v5 - 4);
UnwindUp3_0:
        *((_DWORD *)a1 + v5 - 3) = *((_DWORD *)Src + v5 - 3);
UnwindUp2_0:
        *((_DWORD *)a1 + v5 - 2) = *((_DWORD *)Src + v5 - 2);
UnwindUp1_0:
        *((_DWORD *)a1 + v5 - 1) = *((_DWORD *)Src + v5 - 1);
        v3 = (char *)Src + 4 * v5;
        v4 = (char *)a1 + 4 * v5;
UnwindUp0_0:
        switch ( Size & 3 )
        {
          case 0u:
            goto TrailUp0_0;
          case 1u:
            goto TrailUp1_0;
          case 2u:
            goto TrailUp2_0;
          case 3u:
            goto TrailUp3_0;
        }
      default:
        qmemcpy(a1, Src, 4 * v5);
        v3 = (char *)Src + 4 * v5;
        v4 = (char *)a1 + 4 * v5;
        switch ( Size & 3 )
        {
          case 0u:
TrailUp0_0:
            result = a1;
            break;
          case 1u:
TrailUp1_0:
            *v4 = *v3;
            result = a1;
            break;
          case 2u:
TrailUp2_0:
            *v4 = *v3;
            v4[1] = v3[1];
            result = a1;
            break;
          case 3u:
TrailUp3_0:
            *v4 = *v3;
            v4[1] = v3[1];
            v4[2] = v3[2];
            result = a1;
            break;
        }
        break;
    }
  }
  return result;
}

// 0x00555665
int __cdecl _finite(double X)
{
  return (HIWORD(X) & 0x7FF0) != 32752;
}

// 0x00555679
int __cdecl _fpclass(double X)
{
  int v1; // eax
  int v2; // eax
  int v4; // eax
  int v5; // eax

  if ( (HIWORD(X) & 0x7FF0) == 0x7FF0 )
  {
    v1 = _sptype(SLODWORD(X), SHIDWORD(X)) - 1;
    if ( v1 )
    {
      v2 = v1 - 1;
      if ( !v2 )
        return 4;
      if ( v2 == 1 )
        return 2;
      return 1;
    }
    else
    {
      return 512;
    }
  }
  else if ( (HIWORD(X) & 0x7FF0) == 0 && ((HIDWORD(X) & 0xFFFFF) != 0 || LODWORD(X)) )
  {
    v4 = -((HIWORD(X) & 0x8000) != 0);
    LOBYTE(v4) = v4 & 0x90;
    return v4 + 128;
  }
  else
  {
    v5 = -((HIWORD(X) & 0x8000) != 0);
    LOBYTE(v5) = 0;
    if ( X == 0.0 )
      return v5 + 64;
    else
      return v5 + 256;
  }
}

// 0x00555714
int __cdecl _except_handler3(int a1, _DWORD *TargetFrame, int a3)
{
  int *v3; // ebp
  _DWORD *v4; // ebx
  int v5; // esi
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // ecx
  _DWORD v11[2]; // [esp+10h] [ebp-8h] BYREF
  int savedregs; // [esp+18h] [ebp+0h] BYREF

  v3 = &savedregs;
  v4 = TargetFrame;
  if ( (*(_DWORD *)(a1 + 4) & 6) != 0 )
  {
    _local_unwind2((int)(TargetFrame + 4), (int)TargetFrame, -1);
    return 1;
  }
  else
  {
    v11[0] = a1;
    v11[1] = a3;
    *(TargetFrame - 1) = v11;
    v5 = TargetFrame[3];
    v6 = TargetFrame[2];
    while ( v5 != -1 )
    {
      if ( *(_DWORD *)(v6 + 12 * v5 + 4) )
      {
        v7 = (*(int (**)(void))(v6 + 12 * v5 + 4))();
        v4 = (_DWORD *)v3[3];
        if ( v7 )
        {
          if ( v7 < 0 )
            return 0;
          v8 = v4[2];
          _global_unwind2((PVOID)v3[3]);
          v3 = v4 + 4;
          _local_unwind2((int)(v4 + 4), (int)v4, v5);
          _NLG_Notify(*(_DWORD *)(v8 + 12 * v5 + 8), (int)(v4 + 4), 1);
          v4[3] = *(_DWORD *)(v8 + 4 * v9);
          (*(void (**)(void))(v8 + 4 * v9 + 8))();
        }
      }
      v6 = v4[2];
      v5 = *(_DWORD *)(v6 + 12 * v5);
    }
    return 1;
  }
}

// 0x005557D1
int __stdcall _seh_longjmp_unwind(int *a1)
{
  return _local_unwind2(*a1, a1[6], a1[7]);
}

// 0x005557F0
void *__cdecl memset(void *a1, int Val, size_t Size)
{
  size_t v3; // edx
  int v4; // eax
  _BYTE *v5; // edi
  int v6; // ecx
  size_t v7; // ecx
  unsigned int v8; // ecx

  v3 = Size;
  if ( !Size )
    return a1;
  LOBYTE(v4) = Val;
  v5 = a1;
  if ( Size < 4 )
    goto LABEL_13;
  v6 = -(int)a1 & 3;
  if ( v6 )
  {
    v3 = Size - v6;
    do
    {
      *v5++ = Val;
      --v6;
    }
    while ( v6 );
  }
  v4 = 16843009 * (unsigned __int8)Val;
  v7 = v3;
  v3 &= 3u;
  v8 = v7 >> 2;
  if ( !v8 || (memset32(v5, v4, v8), v5 += 4 * v8, v3) )
  {
LABEL_13:
    do
    {
      *v5++ = v4;
      --v3;
    }
    while ( v3 );
  }
  return a1;
}

// 0x00555848
int __cdecl _callnewh(size_t Size)
{
  return dword_1895324 && dword_1895324(Size);
}

// 0x00555863
int __cdecl _heap_init(int a1)
{
  hHeap = HeapCreate(a1 == 0, 0x1000u, 0);
  if ( !hHeap )
    return 0;
  if ( !__sbh_heap_init() )
  {
    HeapDestroy(hHeap);
    return 0;
  }
  return 1;
}

// 0x0055589F
int __sbh_heap_init()
{
  int result; // eax

  result = (int)HeapAlloc(hHeap, 0, 0x140u);
  lpMem = (LPVOID)result;
  if ( result )
  {
    g_SaveData = 0;
    dword_1896D04 = 0;
    dword_1896CFC = result;
    dword_1896CF4 = 16;
    return 1;
  }
  return result;
}

// 0x005558DD
char *__cdecl __sbh_find_block(int a1)
{
  char *result; // eax

  for ( result = (char *)lpMem; result < (char *)lpMem + 20 * dword_1896D04; result += 20 )
  {
    if ( (unsigned int)(a1 - *((_DWORD *)result + 3)) < 0x100000 )
      return result;
  }
  return 0;
}

// 0x00555908
_DWORD *__cdecl __sbh_free_block(_DWORD *a1, unsigned int a2)
{
  int v2; // eax
  int *v3; // edx
  unsigned int v4; // esi
  int v5; // ebx
  int v6; // ecx
  _BYTE *v7; // ecx
  unsigned int v8; // edi
  bool v9; // zf
  _BYTE *v10; // ecx
  unsigned int v11; // edi
  int v12; // ecx
  int v13; // edi
  unsigned int v14; // edi
  unsigned int v15; // ecx
  _BYTE *v16; // ecx
  unsigned int v17; // edx
  _BYTE *v18; // ecx
  unsigned int v19; // edx
  _DWORD *v20; // ecx
  _DWORD *result; // eax
  int v22; // eax
  _DWORD *v23; // [esp+10h] [ebp-10h]
  int v24; // [esp+14h] [ebp-Ch]
  int v25; // [esp+18h] [ebp-8h]
  int *v26; // [esp+18h] [ebp-8h]
  int v27; // [esp+1Ch] [ebp-4h]
  char v28; // [esp+2Fh] [ebp+Fh]

  v2 = a1[4];
  v3 = (int *)(a2 - 4);
  v4 = (a2 - a1[3]) >> 15;
  v5 = *(_DWORD *)(a2 - 4) - 1;
  v27 = *(_DWORD *)(a2 - 8);
  v24 = v5;
  v23 = (_DWORD *)(516 * v4 + v2 + 324);
  v6 = *(_DWORD *)(v5 + a2 - 4);
  v25 = v6;
  if ( (v6 & 1) == 0 )
  {
    a2 = (v6 >> 4) - 1;
    if ( a2 > 0x3F )
      a2 = 63;
    if ( *(int *)((char *)v3 + v5 + 4) == *(int *)((char *)v3 + v5 + 8) )
    {
      if ( a2 >= 0x20 )
      {
        v10 = (_BYTE *)(a2 + v2 + 4);
        v11 = ~(0x80000000 >> (a2 - 32));
        *(_DWORD *)(v2 + 4 * v4 + 196) &= v11;
        v9 = (*v10)-- == 1;
        if ( v9 )
          a1[1] &= v11;
      }
      else
      {
        v7 = (_BYTE *)(a2 + v2 + 4);
        v8 = ~(0x80000000 >> a2);
        *(_DWORD *)(v2 + 4 * v4 + 68) &= v8;
        v9 = (*v7)-- == 1;
        if ( v9 )
          *a1 &= v8;
      }
    }
    *(_DWORD *)(*(int *)((char *)v3 + v5 + 8) + 4) = *(int *)((char *)v3 + v5 + 4);
    v12 = *(int *)((char *)v3 + v5 + 4);
    v13 = *(int *)((char *)v3 + v5 + 8);
    v5 += v25;
    *(_DWORD *)(v12 + 8) = v13;
    v24 = v5;
  }
  v14 = (v5 >> 4) - 1;
  if ( v14 > 0x3F )
    v14 = 63;
  if ( (v27 & 1) == 0 )
  {
    v26 = (int *)((char *)v3 - v27);
    v15 = (v27 >> 4) - 1;
    a2 = v15;
    if ( v15 > 0x3F )
    {
      a2 = 63;
      v15 = 63;
    }
    v5 += v27;
    v24 = v5;
    v14 = (v5 >> 4) - 1;
    if ( v14 > 0x3F )
      v14 = 63;
    if ( v15 != v14 )
    {
      if ( v26[1] == v26[2] )
      {
        if ( a2 >= 0x20 )
        {
          v18 = (_BYTE *)(a2 + v2 + 4);
          v19 = ~(0x80000000 >> (a2 - 32));
          *(_DWORD *)(v2 + 4 * v4 + 196) &= v19;
          v9 = (*v18)-- == 1;
          if ( v9 )
            a1[1] &= v19;
        }
        else
        {
          v16 = (_BYTE *)(a2 + v2 + 4);
          v17 = ~(0x80000000 >> a2);
          *(_DWORD *)(v2 + 4 * v4 + 68) &= v17;
          v9 = (*v16)-- == 1;
          if ( v9 )
            *a1 &= v17;
        }
      }
      *(_DWORD *)(v26[2] + 4) = v26[1];
      *(_DWORD *)(v26[1] + 8) = v26[2];
    }
    v3 = v26;
  }
  if ( (v27 & 1) != 0 || a2 != v14 )
  {
    v3[1] = v23[2 * v14 + 1];
    v20 = &v23[2 * v14];
    v3[2] = (int)v20;
    v20[1] = v3;
    *(_DWORD *)(v3[1] + 8) = v3;
    if ( v3[1] == v3[2] )
    {
      v28 = *(_BYTE *)(v14 + v2 + 4);
      *(_BYTE *)(v14 + v2 + 4) = v28 + 1;
      if ( v14 >= 0x20 )
      {
        if ( !v28 )
          a1[1] |= 0x80000000 >> (v14 - 32);
        *(_DWORD *)(v2 + 4 * v4 + 196) |= 0x80000000 >> (v14 - 32);
      }
      else
      {
        if ( !v28 )
          *a1 |= 0x80000000 >> v14;
        *(_DWORD *)(v2 + 4 * v4 + 68) |= 0x80000000 >> v14;
      }
      v5 = v24;
    }
  }
  result = (_DWORD *)(516 * v4 + v2 + 324);
  *v3 = v5;
  *(int *)((char *)v3 + v5 - 4) = v5;
  v9 = (*v23)-- == 1;
  if ( v9 )
  {
    if ( !g_SaveData )
      goto LABEL_46;
    VirtualFree((LPVOID)(*(_DWORD *)(g_SaveData + 12) + (dword_1896CF8 << 15)), 0x8000u, 0x4000u);
    *(_DWORD *)(g_SaveData + 8) |= 0x80000000 >> dword_1896CF8;
    *(_DWORD *)(*(_DWORD *)(g_SaveData + 16) + 4 * dword_1896CF8 + 196) = 0;
    --*(_BYTE *)(*(_DWORD *)(g_SaveData + 16) + 67);
    v22 = g_SaveData;
    if ( !*(_BYTE *)(*(_DWORD *)(g_SaveData + 16) + 67) )
    {
      *(_DWORD *)(g_SaveData + 4) &= ~1u;
      v22 = g_SaveData;
    }
    if ( *(_DWORD *)(v22 + 8) == -1 )
    {
      VirtualFree(*(LPVOID *)(v22 + 12), 0, 0x8000u);
      HeapFree(hHeap, 0, *(LPVOID *)(g_SaveData + 16));
      memcpy((void *)g_SaveData, (const void *)(g_SaveData + 20), (size_t)lpMem + 20 * dword_1896D04 - g_SaveData - 20);
      result = a1;
      --dword_1896D04;
      if ( (unsigned int)a1 > g_SaveData )
        result = a1 - 5;
      dword_1896CFC = (int)lpMem;
    }
    else
    {
LABEL_46:
      result = a1;
    }
    g_SaveData = (int)result;
    dword_1896CF8 = v4;
  }
  return result;
}

// 0x00555C33
_DWORD *__cdecl __sbh_alloc_block(int a1)
{
  int v1; // ecx
  unsigned int v2; // esi
  char *i; // ebx
  bool v4; // zf
  bool v5; // zf
  bool v6; // zf
  _DWORD *v8; // eax
  int v9; // edx
  _DWORD *v10; // ecx
  int v11; // edx
  int v12; // edi
  int v13; // ecx
  int *v14; // edx
  int v15; // ecx
  int v16; // esi
  unsigned int v17; // ebx
  _BYTE *v18; // edi
  unsigned int v19; // ebx
  _BYTE *v20; // edi
  int v21; // ebx
  _DWORD *v22; // ecx
  char v23; // cl
  _DWORD *v24; // edx
  int v25; // [esp+Ch] [ebp-14h]
  int v26; // [esp+Ch] [ebp-14h]
  signed int v27; // [esp+10h] [ebp-10h]
  unsigned int v28; // [esp+14h] [ebp-Ch]
  _DWORD *v29; // [esp+14h] [ebp-Ch]
  unsigned int v30; // [esp+18h] [ebp-8h]
  int v31; // [esp+18h] [ebp-8h]
  char *v32; // [esp+1Ch] [ebp-4h]
  int v33; // [esp+1Ch] [ebp-4h]
  char *v34; // [esp+28h] [ebp+8h]

  v32 = (char *)lpMem + 20 * dword_1896D04;
  v27 = (a1 + 23) & 0xFFFFFFF0;
  v1 = (v27 >> 4) - 1;
  if ( v1 >= 32 )
  {
    v2 = 0;
    v28 = 0;
    v30 = 0xFFFFFFFF >> ((v27 >> 4) - 33);
  }
  else
  {
    v2 = 0xFFFFFFFF >> v1;
    v30 = -1;
    v28 = 0xFFFFFFFF >> v1;
  }
  i = (char *)dword_1896CFC;
  v34 = (char *)dword_1896CFC;
  if ( dword_1896CFC < (unsigned int)lpMem + 20 * dword_1896D04 )
  {
    do
    {
      if ( v2 & *(_DWORD *)i | v30 & *((_DWORD *)i + 1) )
        break;
      i += 20;
      v34 = i;
    }
    while ( i < v32 );
  }
  if ( i == v32 )
  {
    for ( i = (char *)lpMem; ; i += 20 )
    {
      v4 = i == (char *)dword_1896CFC;
      v34 = i;
      if ( (unsigned int)i >= dword_1896CFC )
        break;
      if ( v2 & *(_DWORD *)i | v30 & *((_DWORD *)i + 1) )
      {
        v4 = i == (char *)dword_1896CFC;
        break;
      }
    }
    if ( v4 )
    {
      while ( 1 )
      {
        v5 = i == v32;
        if ( i >= v32 )
          break;
        if ( *((_DWORD *)i + 2) )
        {
          v5 = i == v32;
          break;
        }
        i += 20;
        v34 = i;
      }
      if ( v5 )
      {
        for ( i = (char *)lpMem; ; i += 20 )
        {
          v6 = i == (char *)dword_1896CFC;
          v34 = i;
          if ( (unsigned int)i >= dword_1896CFC )
            break;
          if ( *((_DWORD *)i + 2) )
          {
            v6 = i == (char *)dword_1896CFC;
            break;
          }
        }
        if ( v6 )
        {
          i = __sbh_alloc_new_region();
          v34 = i;
          if ( !i )
            return 0;
        }
      }
      **((_DWORD **)i + 4) = __sbh_alloc_new_group(i);
      if ( **((_DWORD **)i + 4) == -1 )
        return 0;
    }
  }
  dword_1896CFC = (int)i;
  v8 = (_DWORD *)*((_DWORD *)i + 4);
  v9 = *v8;
  v33 = *v8;
  if ( *v8 == -1 || !(v2 & v8[v9 + 17] | v30 & v8[v9 + 49]) )
  {
    v33 = 0;
    v10 = v8 + 17;
    v2 = v28;
    if ( !(v28 & v8[17] | v30 & v8[49]) )
    {
      do
      {
        v11 = v10[33];
        ++v33;
        ++v10;
      }
      while ( !(*v10 & v28 | v30 & v11) );
    }
    v9 = v33;
  }
  v12 = 0;
  v29 = &v8[129 * v9 + 81];
  v13 = v2 & v8[v9 + 17];
  if ( !v13 )
  {
    v13 = v30 & v8[v9 + 49];
    v12 = 32;
  }
  while ( v13 >= 0 )
  {
    v13 *= 2;
    ++v12;
  }
  v14 = (int *)v29[2 * v12 + 1];
  v31 = *v14 - v27;
  v15 = v31;
  v16 = (v31 >> 4) - 1;
  if ( v16 > 63 )
    v16 = 63;
  if ( v16 == v12 )
    goto LABEL_57;
  if ( v14[1] != v14[2] )
    goto LABEL_47;
  if ( v12 >= 32 )
  {
    v19 = 0x80000000 >> (v12 - 32);
    v20 = (char *)v8 + v12 + 4;
    v21 = ~v19;
    v8[v33 + 49] &= v21;
    v4 = (*v20)-- == 1;
    v26 = v21;
    if ( v4 )
    {
      i = v34;
      *((_DWORD *)v34 + 1) &= v26;
      goto LABEL_47;
    }
  }
  else
  {
    v17 = 0x80000000 >> v12;
    v18 = (char *)v8 + v12 + 4;
    v25 = ~v17;
    v8[v33 + 17] &= ~v17;
    v4 = (*v18)-- == 1;
    if ( v4 )
    {
      i = v34;
      *(_DWORD *)v34 &= v25;
      goto LABEL_47;
    }
  }
  i = v34;
LABEL_47:
  *(_DWORD *)(v14[2] + 4) = v14[1];
  *(_DWORD *)(v14[1] + 8) = v14[2];
  if ( v31 )
  {
    v22 = &v29[2 * v16];
    v14[1] = v22[1];
    v14[2] = (int)v22;
    v22[1] = v14;
    *(_DWORD *)(v14[1] + 8) = v14;
    if ( v14[1] == v14[2] )
    {
      v23 = *((_BYTE *)v8 + v16 + 4);
      if ( v16 >= 32 )
      {
        *((_BYTE *)v8 + v16 + 4) = v23 + 1;
        if ( !v23 )
          *((_DWORD *)i + 1) |= 0x80000000 >> (v16 - 32);
        v8[v33 + 49] |= 0x80000000 >> (v16 - 32);
      }
      else
      {
        *((_BYTE *)v8 + v16 + 4) = v23 + 1;
        if ( !v23 )
          *(_DWORD *)i |= 0x80000000 >> v16;
        v8[v33 + 17] |= 0x80000000 >> v16;
      }
    }
    v15 = v31;
LABEL_57:
    if ( v15 )
    {
      *v14 = v15;
      *(int *)((char *)v14 + v15 - 4) = v15;
    }
    goto LABEL_60;
  }
  v15 = 0;
LABEL_60:
  v24 = (int *)((char *)v14 + v15);
  *v24 = v27 + 1;
  *(_DWORD *)((char *)v24 + v27 - 4) = v27 + 1;
  v4 = (*v29)++ == 0;
  if ( v4 && i == (char *)g_SaveData && v33 == dword_1896CF8 )
    g_SaveData = 0;
  *v8 = v33;
  return v24 + 1;
}

// 0x00555F3C
char *__sbh_alloc_new_region()
{
  int v0; // eax
  void *v1; // eax
  char *v2; // esi
  LPVOID v3; // eax
  LPVOID v4; // eax

  v0 = dword_1896D04;
  if ( dword_1896D04 == dword_1896CF4 )
  {
    v1 = HeapReAlloc(hHeap, 0, lpMem, 4 * (5 * dword_1896CF4 + 80));
    if ( !v1 )
      return 0;
    dword_1896CF4 += 16;
    lpMem = v1;
    v0 = dword_1896D04;
  }
  v2 = (char *)lpMem + 20 * v0;
  v3 = HeapAlloc(hHeap, 8u, 0x41C4u);
  *((_DWORD *)v2 + 4) = v3;
  if ( !v3 )
    return 0;
  v4 = VirtualAlloc(0, 0x100000u, 0x2000u, 4u);
  *((_DWORD *)v2 + 3) = v4;
  if ( !v4 )
  {
    HeapFree(hHeap, 0, *((LPVOID *)v2 + 4));
    return 0;
  }
  *((_DWORD *)v2 + 2) = -1;
  *(_DWORD *)v2 = 0;
  *((_DWORD *)v2 + 1) = 0;
  ++dword_1896D04;
  **((_DWORD **)v2 + 4) = -1;
  return v2;
}

// 0x00555FED
int __cdecl __sbh_alloc_new_group(_DWORD *a1)
{
  int v1; // esi
  int v2; // eax
  int v3; // ebx
  int v4; // edx
  int v5; // eax
  _DWORD *v6; // edi
  _DWORD *v8; // eax

  v1 = a1[4];
  v2 = a1[2];
  v3 = 0;
  while ( v2 >= 0 )
  {
    v2 *= 2;
    ++v3;
  }
  v4 = 63;
  v5 = 516 * v3 + v1 + 324;
  do
  {
    *(_DWORD *)(v5 + 8) = v5;
    *(_DWORD *)(v5 + 4) = v5;
    v5 += 8;
    --v4;
  }
  while ( v4 );
  v6 = (_DWORD *)(a1[3] + (v3 << 15));
  if ( !VirtualAlloc(v6, 0x8000u, 0x1000u, 4u) )
    return -1;
  if ( v6 < v6 + 7168 )
  {
    v8 = v6 + 4;
    do
    {
      *(v8 - 2) = -1;
      v8[1019] = -1;
      *(v8 - 1) = 4080;
      *v8 = v8 + 1023;
      v8[1] = v8 - 1025;
      v8[1018] = 4080;
      v8 += 1024;
    }
    while ( v8 - 4 <= v6 + 7168 );
  }
  *(_DWORD *)(516 * v3 + v1 + 832) = v6 + 3;
  v6[5] = 516 * v3 + v1 + 828;
  *(_DWORD *)(516 * v3 + v1 + 836) = v6 + 7171;
  v6[7172] = 516 * v3 + v1 + 828;
  *(_DWORD *)(v1 + 4 * v3 + 68) = 0;
  *(_DWORD *)(v1 + 4 * v3 + 196) = 1;
  if ( (*(_BYTE *)(v1 + 67))++ == 0 )
    a1[1] |= 1u;
  a1[2] &= ~(0x80000000 >> v3);
  return v3;
}

// 0x005560E8
int __cdecl __sbh_resize_block(_DWORD *a1, int a2, int a3)
{
  int v3; // eax
  signed int v4; // esi
  unsigned int v5; // edx
  int v6; // ecx
  int v7; // ebx
  int v8; // edi
  unsigned int v9; // ecx
  unsigned int v10; // ebx
  _BYTE *v11; // ecx
  int v12; // ebx
  bool v13; // zf
  unsigned int v14; // ebx
  _BYTE *v15; // ecx
  int v16; // ebx
  unsigned int v17; // edi
  int v18; // ecx
  _DWORD *v19; // eax
  char v20; // cl
  int v21; // edx
  int *v22; // eax
  int v24; // ecx
  int *v25; // ebx
  unsigned int v26; // esi
  unsigned int v27; // esi
  unsigned int v28; // ebx
  _BYTE *v29; // esi
  int v30; // ebx
  _BYTE *v31; // ecx
  unsigned int v32; // ebx
  unsigned int v33; // ecx
  _DWORD *v34; // eax
  char v35; // cl
  int v36; // [esp+Ch] [ebp-Ch]
  int v37; // [esp+10h] [ebp-8h]
  int v38; // [esp+14h] [ebp-4h]
  int v39; // [esp+14h] [ebp-4h]
  int *v40; // [esp+24h] [ebp+Ch]
  char v41; // [esp+27h] [ebp+Fh]
  int v42; // [esp+28h] [ebp+10h]
  unsigned int v43; // [esp+28h] [ebp+10h]
  int v44; // [esp+28h] [ebp+10h]
  char v45; // [esp+2Bh] [ebp+13h]

  v3 = a1[4];
  v4 = (a3 + 23) & 0xFFFFFFF0;
  v5 = (unsigned int)(a2 - a1[3]) >> 15;
  v36 = 516 * v5 + v3 + 324;
  v6 = *(_DWORD *)(a2 - 4) - 1;
  v42 = v6;
  v7 = *(_DWORD *)(v6 + a2 - 4);
  v8 = v6 + a2 - 4;
  v38 = v7;
  if ( v4 <= v6 )
  {
    if ( v4 < v6 )
    {
      v44 = v6 - v4;
      v24 = v4 + 1;
      *(_DWORD *)(a2 - 4) = v4 + 1;
      v25 = (int *)(a2 + v4 - 4);
      v40 = v25;
      v26 = (v44 >> 4) - 1;
      *(v25 - 1) = v24;
      if ( v26 > 0x3F )
        v26 = 63;
      if ( (v38 & 1) == 0 )
      {
        v27 = (v38 >> 4) - 1;
        if ( v27 > 0x3F )
          v27 = 63;
        if ( *(_DWORD *)(v8 + 4) == *(_DWORD *)(v8 + 8) )
        {
          if ( v27 >= 0x20 )
          {
            v31 = (_BYTE *)(v27 + v3 + 4);
            v32 = ~(0x80000000 >> (v27 - 32));
            *(_DWORD *)(v3 + 4 * v5 + 196) &= v32;
            v13 = (*v31)-- == 1;
            if ( v13 )
              a1[1] &= v32;
          }
          else
          {
            v28 = 0x80000000 >> v27;
            v29 = (_BYTE *)(v27 + v3 + 4);
            v30 = ~v28;
            *(_DWORD *)(v3 + 4 * v5 + 68) &= v30;
            v13 = (*v29)-- == 1;
            if ( v13 )
              *a1 &= v30;
          }
          v25 = v40;
        }
        *(_DWORD *)(*(_DWORD *)(v8 + 8) + 4) = *(_DWORD *)(v8 + 4);
        *(_DWORD *)(*(_DWORD *)(v8 + 4) + 8) = *(_DWORD *)(v8 + 8);
        v44 += v38;
        v26 = (v44 >> 4) - 1;
        if ( v26 > 0x3F )
          v26 = 63;
      }
      v33 = v36 + 8 * v26;
      v25[1] = *(_DWORD *)(v33 + 4);
      v25[2] = v33;
      *(_DWORD *)(v33 + 4) = v25;
      *(_DWORD *)(v25[1] + 8) = v25;
      if ( v25[1] == v25[2] )
      {
        v41 = *(_BYTE *)(v26 + v3 + 4);
        *(_BYTE *)(v26 + v3 + 4) = v41 + 1;
        if ( v26 >= 0x20 )
        {
          if ( !v41 )
            a1[1] |= 0x80000000 >> (v26 - 32);
          v34 = (_DWORD *)(v3 + 4 * v5 + 196);
          v35 = v26 - 32;
        }
        else
        {
          if ( !v41 )
            *a1 |= 0x80000000 >> v26;
          v34 = (_DWORD *)(v3 + 4 * v5 + 68);
          v35 = v26;
        }
        *v34 |= 0x80000000 >> v35;
      }
      *v25 = v44;
      *(int *)((char *)v25 + v44 - 4) = v44;
    }
  }
  else
  {
    if ( (v7 & 1) != 0 || v4 > v6 + v7 )
      return 0;
    v9 = (v7 >> 4) - 1;
    v37 = v9;
    if ( v9 > 0x3F )
    {
      v9 = 63;
      v37 = 63;
    }
    if ( *(_DWORD *)(v8 + 4) == *(_DWORD *)(v8 + 8) )
    {
      if ( v9 >= 0x20 )
      {
        v14 = 0x80000000 >> (v9 - 32);
        v15 = (_BYTE *)(v37 + v3 + 4);
        v16 = ~v14;
        *(_DWORD *)(v3 + 4 * v5 + 196) &= v16;
        v13 = (*v15)-- == 1;
        if ( v13 )
          a1[1] &= v16;
      }
      else
      {
        v10 = 0x80000000 >> v9;
        v11 = (_BYTE *)(v37 + v3 + 4);
        v12 = ~v10;
        *(_DWORD *)(v3 + 4 * v5 + 68) &= v12;
        v13 = (*v11)-- == 1;
        if ( v13 )
          *a1 &= v12;
      }
    }
    *(_DWORD *)(*(_DWORD *)(v8 + 8) + 4) = *(_DWORD *)(v8 + 4);
    *(_DWORD *)(*(_DWORD *)(v8 + 4) + 8) = *(_DWORD *)(v8 + 8);
    v39 = v42 - v4 + v38;
    if ( v39 <= 0 )
    {
      v21 = a2;
    }
    else
    {
      v17 = (v39 >> 4) - 1;
      v18 = a2 + v4 - 4;
      if ( v17 > 0x3F )
        v17 = 63;
      v43 = v36 + 8 * v17;
      *(_DWORD *)(a2 + v4) = *(_DWORD *)(v43 + 4);
      *(_DWORD *)(v18 + 8) = v43;
      *(_DWORD *)(v43 + 4) = v18;
      *(_DWORD *)(*(_DWORD *)(a2 + v4) + 8) = a2 + v4 - 4;
      if ( *(_DWORD *)(a2 + v4) == *(_DWORD *)(a2 + v4 - 4 + 8) )
      {
        v45 = *(_BYTE *)(v17 + v3 + 4);
        *(_BYTE *)(v17 + v3 + 4) = v45 + 1;
        if ( v17 >= 0x20 )
        {
          if ( !v45 )
            a1[1] |= 0x80000000 >> (v17 - 32);
          v19 = (_DWORD *)(v3 + 4 * v5 + 196);
          v20 = v17 - 32;
        }
        else
        {
          if ( !v45 )
            *a1 |= 0x80000000 >> v17;
          v19 = (_DWORD *)(v3 + 4 * v5 + 68);
          v20 = v17;
        }
        *v19 |= 0x80000000 >> v20;
      }
      v21 = a2;
      v22 = (int *)(a2 + v4 - 4);
      *v22 = v39;
      *(int *)((char *)v22 + v39 - 4) = v39;
    }
    *(_DWORD *)(v21 - 4) = v4 + 1;
    *(_DWORD *)(v21 + v4 - 8) = v4 + 1;
  }
  return 1;
}

// 0x005563DE
unsigned int _setdefaultprecision()
{
  return _controlfp(0x10000u, 0x30000u);
}

// 0x005563F0
BOOL _ms_p5_test_fdiv()
{
  return 4195835.0 - 4195835.0 / 3145727.0 * 3145727.0 > 1.0;
}

// 0x0055642E
int _ms_p5_mp_test_fdiv()
{
  HMODULE ModuleHandleA; // eax
  BOOL (__stdcall *IsProcessorFeaturePresent)(DWORD); // eax

  ModuleHandleA = GetModuleHandleA("KERNEL32");
  if ( ModuleHandleA
    && (IsProcessorFeaturePresent = (BOOL (__stdcall *)(DWORD))GetProcAddress(
                                                                 ModuleHandleA,
                                                                 "IsProcessorFeaturePresent")) != 0 )
  {
    return IsProcessorFeaturePresent(0);
  }
  else
  {
    return _ms_p5_test_fdiv();
  }
}

// 0x00556457
char __cdecl _forcdecpt(char *a1)
{
  char *v1; // esi
  int v2; // eax
  char result; // al
  char *v4; // esi
  char v5; // cl

  v1 = a1;
  if ( tolower(*a1) != 101 )
  {
    do
    {
      ++v1;
      if ( (int)cbMultiByte <= 1 )
        v2 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * *v1) & 4;
      else
        v2 = _isctype(*v1, 4);
    }
    while ( v2 );
  }
  result = *v1;
  *v1 = byte_60AF10;
  v4 = v1 + 1;
  do
  {
    v5 = *v4;
    *v4 = result;
    result = v5;
  }
  while ( *v4++ );
  return result;
}

// 0x005564B1
char *__cdecl _cropzeros(char *a1)
{
  char *v1; // eax
  char i; // cl
  char v3; // cl
  char *result; // eax
  char v5; // cl
  char *v6; // ecx
  char v7; // dl

  v1 = a1;
  for ( i = *a1; i; i = *++v1 )
  {
    if ( i == byte_60AF10 )
      break;
  }
  v3 = *v1;
  result = v1 + 1;
  if ( v3 )
  {
    while ( 1 )
    {
      v5 = *result;
      if ( !*result || v5 == 101 || v5 == 69 )
        break;
      ++result;
    }
    v6 = result;
    do
      --result;
    while ( *result == 48 );
    if ( *result == byte_60AF10 )
      --result;
    do
    {
      v7 = *v6;
      ++result;
      ++v6;
      *result = v7;
    }
    while ( v7 );
  }
  return result;
}

// 0x005564FF
BOOL __cdecl _positive(double *a1)
{
  return *a1 >= 0.0;
}

// 0x00556517
char **__cdecl _fassign(int a1, char **a2, char *a3)
{
  unsigned int v4[2]; // [esp+0h] [ebp-8h] BYREF

  if ( a1 )
  {
    sub_55BAB4(v4, a3);
    *a2 = (char *)v4[0];
    a2[1] = (char *)v4[1];
    return a2;
  }
  else
  {
    sub_55BAE1((unsigned int *)&a3, a3);
    *a2 = a3;
    return a2;
  }
}

// 0x00556555
_BYTE *__cdecl _cftoe(double *a1, _BYTE *a2, int a3, int a4)
{
  int *v4; // esi
  _BYTE *v5; // eax
  char *v6; // eax
  int v7; // ebx

  if ( byte_1895330 )
  {
    v4 = (int *)dword_189532C;
    _shift(&a2[*(_DWORD *)dword_189532C == 45], a3 > 0);
  }
  else
  {
    v4 = _fltout(COERCE_UNSIGNED_INT64(*a1));
    _fptostr(&a2[(*v4 == 45) + (a3 > 0)], (char *)(a3 + 1), (int)v4);
  }
  v5 = a2;
  if ( *v4 == 45 )
  {
    *a2 = 45;
    v5 = a2 + 1;
  }
  if ( a3 > 0 )
  {
    *v5 = v5[1];
    *++v5 = byte_60AF10;
  }
  v6 = strcpy(&v5[(byte_1895330 == 0) + a3], "e+000");
  if ( a4 )
    *v6 = 69;
  if ( *(_BYTE *)v4[3] != 48 )
  {
    v7 = v4[1] - 1;
    if ( v7 < 0 )
    {
      v7 = 1 - v4[1];
      v6[1] = 45;
    }
    if ( v7 >= 100 )
    {
      v6[2] += v7 / 100;
      v7 %= 100;
    }
    if ( v7 >= 10 )
    {
      v6[3] += v7 / 10;
      v7 %= 10;
    }
    v6[4] += v7;
  }
  return a2;
}

// 0x00556659
char *__cdecl _cftof(double *a1, char *Src, size_t Size)
{
  int v3; // ebx
  int *v4; // esi
  char *v5; // eax
  char *v6; // edi
  int v7; // eax
  char *v8; // edi
  int v9; // esi
  char *v10; // edi
  int v11; // esi

  if ( byte_1895330 )
  {
    v3 = Size;
    v4 = (int *)dword_189532C;
    if ( dword_1895334 == Size )
    {
      v5 = &Src[dword_1895334 + (*(_DWORD *)dword_189532C == 45)];
      *v5 = 48;
      v5[1] = 0;
    }
  }
  else
  {
    v3 = Size;
    v4 = _fltout(COERCE_UNSIGNED_INT64(*a1));
    _fptostr(&Src[*v4 == 45], (char *)(Size + v4[1]), (int)v4);
  }
  v6 = Src;
  if ( *v4 == 45 )
  {
    *Src = 45;
    v6 = Src + 1;
  }
  v7 = v4[1];
  if ( v7 > 0 )
  {
    v8 = &v6[v7];
  }
  else
  {
    _shift(v6, 1);
    *v6 = 48;
    v8 = v6 + 1;
  }
  if ( v3 > 0 )
  {
    _shift(v8, 1);
    *v8 = byte_60AF10;
    v9 = v4[1];
    v10 = v8 + 1;
    if ( v9 < 0 )
    {
      if ( byte_1895330 )
      {
        v11 = -v9;
      }
      else
      {
        v11 = -v9;
        if ( v3 < v11 )
        {
LABEL_16:
          _shift(v10, v3);
          memset(v10, 48, v3);
          return Src;
        }
      }
      v3 = v11;
      goto LABEL_16;
    }
  }
  return Src;
}

// 0x00556737
char *__cdecl _cftog(double *a1, char *Src, char *Size, int a4)
{
  char *v4; // esi
  bool v5; // cl

  dword_189532C = (int)_fltout(COERCE_UNSIGNED_INT64(*a1));
  dword_1895334 = *(_DWORD *)(dword_189532C + 4) - 1;
  v4 = &Src[*(_DWORD *)dword_189532C == 45];
  _fptostr(v4, Size, dword_189532C);
  v5 = dword_1895334 < *(_DWORD *)(dword_189532C + 4) - 1;
  byte_1895338 = v5;
  dword_1895334 = *(_DWORD *)(dword_189532C + 4) - 1;
  if ( dword_1895334 < -4 || dword_1895334 >= (int)Size )
    return _cftoe_g(a1, Src, (int)Size, a4);
  if ( v5 )
    v4[strlen(v4) - 1] = 0;
  return _cftof_g(a1, Src, (size_t)Size);
}

// 0x005567D2
_BYTE *__cdecl _cftoe_g(double *a1, _BYTE *a2, int a3, int a4)
{
  _BYTE *result; // eax

  byte_1895330 = 1;
  result = _cftoe(a1, a2, a3, a4);
  byte_1895330 = 0;
  return result;
}

// 0x005567F9
char *__cdecl _cftof_g(double *a1, char *Src, size_t Size)
{
  char *result; // eax

  byte_1895330 = 1;
  result = _cftof(a1, Src, Size);
  byte_1895330 = 0;
  return result;
}

// 0x0055681C
char *__cdecl _cfltcvt(double *a1, char *Src, int a3, char *Size, int a5)
{
  if ( a3 == 101 || a3 == 69 )
    return _cftoe(a1, Src, (int)Size, a5);
  if ( a3 == 102 )
    return _cftof(a1, Src, (size_t)Size);
  return _cftog(a1, Src, Size, a5);
}

// 0x0055686D
void __cdecl _shift(const char *Src, int a2)
{
  size_t v2; // eax

  if ( a2 )
  {
    v2 = strlen(Src);
    memcpy((void *)&Src[a2], Src, v2 + 1);
  }
}

// 0x00556892
void *__cdecl realloc(void *Block, size_t Size)
{
  size_t v3; // esi
  void *v4; // edi
  char *v5; // eax
  char *v6; // ebp
  size_t v7; // eax
  size_t v8; // eax

  if ( !Block )
    return malloc(Size);
  v3 = Size;
  if ( !Size )
  {
    free(Block);
    return 0;
  }
  while ( 1 )
  {
    v4 = 0;
    if ( v3 > 0xFFFFFFE0 )
      goto LABEL_26;
    v5 = __sbh_find_block((int)Block);
    v6 = v5;
    if ( !v5 )
    {
      if ( !v3 )
        v3 = 1;
      v3 = (v3 + 15) & 0xFFFFFFF0;
      v4 = HeapReAlloc(hHeap, 0, Block, v3);
      goto LABEL_25;
    }
    if ( v3 <= dword_60ACB4 )
    {
      if ( __sbh_resize_block(v5, (int)Block, v3) )
        return Block;
      v4 = __sbh_alloc_block(v3);
      if ( v4 )
        break;
    }
    if ( !v3 )
      v3 = 1;
    v3 = (v3 + 15) & 0xFFFFFFF0;
    v4 = HeapAlloc(hHeap, 0, v3);
    if ( !v4 )
      goto LABEL_26;
    v8 = *((_DWORD *)Block - 1) - 1;
    if ( v8 >= v3 )
      v8 = v3;
    memcpy_0(v4, Block, v8);
    __sbh_free_block(v6, (unsigned int)Block);
LABEL_25:
    if ( v4 )
      return v4;
LABEL_26:
    if ( !dword_1895328 )
      return v4;
    if ( !_callnewh(v3) )
      return 0;
  }
  v7 = *((_DWORD *)Block - 1) - 1;
  if ( v7 >= v3 )
    v7 = v3;
  memcpy_0(v4, Block, v7);
  __sbh_free_block(v6, (unsigned int)Block);
  return v4;
}

// 0x005569B2
void _cinit()
{
  if ( off_60AC20 )
    off_60AC20();
  _initterm(&First, &Last);
  _initterm(&dword_580000, &dword_5809E8);
}

// 0x005569DF
void __cdecl __noreturn exit(int Code)
{
  doexit(Code, 0, 0);
}

// 0x005569F0
void __cdecl __noreturn _exit(int Code)
{
  doexit(Code, 1, 0);
}

// 0x00556A01
void __cdecl doexit(UINT uExitCode, int a2, int a3)
{
  HANDLE CurrentProcess; // eax
  void (**v4)(void); // esi

  if ( dword_1895384 == 1 )
  {
    CurrentProcess = GetCurrentProcess();
    TerminateProcess(CurrentProcess, uExitCode);
  }
  dword_1895380 = 1;
  byte_189537C = a3;
  if ( !a2 )
  {
    if ( dword_1896CF0 )
    {
      v4 = (void (**)(void))(dword_1896CEC - 4);
      if ( dword_1896CEC - 4 >= (unsigned int)dword_1896CF0 )
      {
        do
        {
          if ( *v4 )
            (*v4)();
          --v4;
        }
        while ( v4 >= dword_1896CF0 );
      }
    }
    _initterm(&dword_580A04, &dword_580A0C);
  }
  _initterm(&dword_580A10, &dword_580A18);
  if ( !a3 )
  {
    dword_1895384 = 1;
    ExitProcess(uExitCode);
  }
}

// 0x00556A9A
void __cdecl _initterm(_PVFV *First, _PVFV *Last)
{
  while ( First < Last )
  {
    if ( *First )
      (*First)();
    ++First;
  }
}

// 0x00556AB4
size_t __cdecl _msize(void *Block)
{
  if ( __sbh_find_block((int)Block) )
    return *((_DWORD *)Block - 1) - 9;
  else
    return HeapSize(hHeap, 0, Block);
}

// 0x00556ADD
int __cdecl _flsbuf(int Ch, FILE *File)
{
  FILE *v2; // esi
  int flag; // eax
  int v4; // ebx
  int v5; // eax
  char *base; // eax
  signed int v7; // edi
  _BYTE *v8; // eax

  v2 = File;
  flag = File->_flag;
  v4 = File->_file;
  if ( (flag & 0x82) == 0 || (flag & 0x40) != 0 )
    goto LABEL_24;
  if ( (flag & 1) == 0 )
    goto LABEL_6;
  File->_cnt = 0;
  if ( (flag & 0x10) == 0 )
  {
LABEL_24:
    LOBYTE(flag) = flag | 0x20;
    v2->_flag = flag;
    return -1;
  }
  LOBYTE(flag) = flag & 0xFE;
  v2->_ptr = v2->_base;
  v2->_flag = flag;
LABEL_6:
  v5 = v2->_flag;
  v2->_cnt = 0;
  File = 0;
  LOBYTE(v5) = v5 & 0xED | 2;
  v2->_flag = v5;
  if ( (v5 & 0x10C) == 0 && (v2 != (FILE *)&unk_60B0D8 && v2 != (FILE *)&unk_60B0F8 || !_isatty(v4)) )
    _getbuf(v2);
  if ( (v2->_flag & 0x108) != 0 )
  {
    base = v2->_base;
    v7 = v2->_ptr - base;
    v2->_ptr = base + 1;
    v2->_cnt = v2->_bufsiz - 1;
    if ( v7 <= 0 )
    {
      if ( v4 == -1 )
        v8 = &unk_60ACF0;
      else
        v8 = (_BYTE *)(*(&g_nUIState + (v4 >> 5)) + 8 * (v4 & 0x1F));
      if ( (v8[4] & 0x20) != 0 )
        _lseek(v4, 0, 2);
    }
    else
    {
      File = (FILE *)_write(v4, base, v7);
    }
    *v2->_base = Ch;
  }
  else
  {
    v7 = 1;
    File = (FILE *)_write(v4, &Ch, 1u);
  }
  if ( File == (FILE *)v7 )
    return (unsigned __int8)Ch;
  v2->_flag |= 0x20u;
  return -1;
}

// 0x00556BF2
int __cdecl _output(FILE *File, char *a2, int a3)
{
  int v3; // esi
  char v4; // bl
  char *v5; // edi
  bool v6; // zf
  int v7; // ecx
  int v8; // eax
  int int_arg; // eax
  int v10; // eax
  int v11; // esi
  int v12; // eax
  char *v13; // ecx
  char *i; // eax
  int v15; // edx
  wchar_t short_arg; // ax
  __int16 *v17; // eax
  int v18; // ecx
  unsigned int v19; // eax
  int v20; // eax
  char *j; // eax
  int v22; // edx
  _WORD *v23; // eax
  __int64 int64_arg; // rax
  unsigned __int64 v25; // rdi
  int v26; // eax
  int v27; // ebx
  unsigned __int64 v28; // kr08_8
  _BYTE *v29; // eax
  char *v30; // eax
  char v31; // bl
  char *v32; // esi
  wchar_t *v33; // ebx
  int v34; // edi
  wchar_t v35; // ax
  char *v36; // eax
  char Str; // [esp+Ch] [ebp-248h] BYREF
  char v40; // [esp+20Bh] [ebp-49h] BYREF
  int v41; // [esp+20Ch] [ebp-48h]
  int v42; // [esp+210h] [ebp-44h]
  __int64 v43; // [esp+214h] [ebp-40h]
  char MbCh[4]; // [esp+21Ch] [ebp-38h] BYREF
  int v45; // [esp+220h] [ebp-34h]
  int v46; // [esp+224h] [ebp-30h]
  int v47; // [esp+228h] [ebp-2Ch]
  int v48; // [esp+22Ch] [ebp-28h]
  int v49; // [esp+230h] [ebp-24h]
  int v50; // [esp+234h] [ebp-20h]
  int v51; // [esp+238h] [ebp-1Ch]
  _WORD v52[3]; // [esp+23Eh] [ebp-16h] BYREF
  int v53; // [esp+244h] [ebp-10h]
  int v54; // [esp+248h] [ebp-Ch]
  int p_Str; // [esp+24Ch] [ebp-8h]
  int v56; // [esp+250h] [ebp-4h]
  char *v57; // [esp+260h] [ebp+Ch]

  v3 = 0;
  v4 = *a2;
  v5 = a2 + 1;
  v6 = *a2 == 0;
  v54 = 0;
  *(_DWORD *)&v52[1] = 0;
  v57 = a2 + 1;
  if ( !v6 )
  {
    v7 = v53;
    while ( 1 )
    {
      if ( *(int *)&v52[1] < 0 )
        return *(_DWORD *)&v52[1];
      if ( v4 < 32 || v4 > 120 )
        v8 = 0;
      else
        v8 = ProcName[v4 + 16] & 0xF;
      v46 = byte_573298[8 * v8 + v3] >> 4;
      switch ( v46 )
      {
        case 0:
          goto $NORMAL_STATE$1535;
        case 1:
          v53 = -1;
          v45 = 0;
          v48 = 0;
          v50 = 0;
          v51 = 0;
          v56 = 0;
          v49 = 0;
          goto LABEL_171;
        case 2:
          switch ( v4 )
          {
            case ' ':
              v56 |= 2u;
              break;
            case '#':
              LOBYTE(v56) = v56 | 0x80;
              break;
            case '+':
              v56 |= 1u;
              break;
            case '-':
              v56 |= 4u;
              break;
            case '0':
              v56 |= 8u;
              break;
          }
          goto LABEL_171;
        case 3:
          if ( v4 == 42 )
          {
            int_arg = get_int_arg(&a3);
            v50 = int_arg;
            if ( int_arg >= 0 )
              goto LABEL_171;
            v56 |= 4u;
            v10 = -int_arg;
          }
          else
          {
            v10 = v4 + 10 * v50 - 48;
          }
          v50 = v10;
          goto LABEL_171;
        case 4:
          v53 = 0;
          goto LABEL_171;
        case 5:
          if ( v4 == 42 )
          {
            v53 = get_int_arg(&a3);
            if ( v53 < 0 )
              v53 = -1;
          }
          else
          {
            v53 = v4 + 10 * v7 - 48;
          }
          goto LABEL_171;
        case 6:
          switch ( v4 )
          {
            case 'I':
              if ( *v5 == 54 && v5[1] == 52 )
              {
                BYTE1(v56) |= 0x80u;
                v57 = v5 + 2;
              }
              else
              {
                v46 = 0;
$NORMAL_STATE$1535:
                v49 = 0;
                if ( *((char *)g_pVtbl_SceneMgr + 2 * (unsigned __int8)v4 + 1) < 0 )
                {
                  write_char(v4, File, &v52[1]);
                  v4 = *v5;
                  v57 = v5 + 1;
                }
                write_char(v4, File, &v52[1]);
              }
              break;
            case 'h':
              v56 |= 0x20u;
              break;
            case 'l':
              v56 |= 0x10u;
              break;
            case 'w':
              BYTE1(v56) |= 8u;
              break;
          }
          goto LABEL_171;
        case 7:
          if ( v4 > 103 )
          {
            switch ( v4 )
            {
              case 'i':
                goto LABEL_114;
              case 'n':
                v23 = (_WORD *)get_int_arg(&a3);
                if ( (v56 & 0x20) != 0 )
                  *v23 = v52[1];
                else
                  *(_DWORD *)v23 = *(_DWORD *)&v52[1];
                v48 = 1;
                goto LABEL_171;
              case 'o':
                v54 = 8;
                if ( (v56 & 0x80u) != 0 )
                  BYTE1(v56) |= 2u;
                break;
              default:
                switch ( v4 )
                {
                  case 'p':
                    v53 = 8;
LABEL_105:
                    v47 = 7;
                    break;
                  case 's':
                    goto LABEL_55;
                  case 'u':
                    goto LABEL_115;
                  case 'x':
                    v47 = 39;
                    break;
                  default:
                    goto LABEL_148;
                }
                v54 = 16;
                if ( (v56 & 0x80u) != 0 )
                {
                  LOBYTE(v52[0]) = 48;
                  v51 = 2;
                  HIBYTE(v52[0]) = v47 + 81;
                }
                break;
            }
LABEL_116:
            if ( (v56 & 0x8000) == 0 )
            {
              if ( (v56 & 0x20) != 0 )
              {
                if ( (v56 & 0x40) != 0 )
                  LODWORD(int64_arg) = (__int16)get_int_arg(&a3);
                else
                  LODWORD(int64_arg) = (unsigned __int16)get_int_arg(&a3);
              }
              else
              {
                if ( (v56 & 0x40) == 0 )
                {
                  int64_arg = (unsigned int)get_int_arg(&a3);
                  goto LABEL_126;
                }
                LODWORD(int64_arg) = get_int_arg(&a3);
              }
              int64_arg = (int)int64_arg;
            }
            else
            {
              int64_arg = get_int64_arg(&a3);
            }
LABEL_126:
            if ( (v56 & 0x40) != 0 && int64_arg < 0 )
            {
              HIDWORD(v25) = -(int)int64_arg;
              BYTE1(v56) |= 1u;
              LODWORD(v25) = (unsigned __int64)-int64_arg >> 32;
            }
            else
            {
              v25 = __PAIR64__(int64_arg, HIDWORD(int64_arg));
            }
            if ( (v56 & 0x8000) == 0 )
              LODWORD(v25) = 0;
            if ( v53 >= 0 )
              v56 &= ~8u;
            else
              v53 = 1;
            if ( !v25 )
              v51 = 0;
            p_Str = (int)&v40;
            while ( 1 )
            {
              v26 = v53--;
              if ( v26 <= 0 && !v25 )
                break;
              v43 = v54;
              v27 = __PAIR64__(v25, HIDWORD(v25)) % v54 + 48;
              v28 = __PAIR64__(v25, HIDWORD(v25)) / v54;
              v25 = __PAIR64__(v28, HIDWORD(v28));
              if ( v27 > 57 )
                LOBYTE(v27) = v47 + v27;
              v29 = (_BYTE *)p_Str--;
              *v29 = v27;
            }
            v30 = &v40 - p_Str++;
            v54 = (int)v30;
            if ( (v56 & 0x200) != 0 && (*(_BYTE *)p_Str != 48 || !v30) )
            {
              --p_Str;
              v20 = (int)(v30 + 1);
              *(_BYTE *)p_Str = 48;
              goto LABEL_147;
            }
            goto LABEL_148;
          }
          if ( v4 >= 101 )
            goto LABEL_65;
          if ( v4 > 88 )
          {
            if ( v4 == 90 )
            {
              v17 = (__int16 *)get_int_arg(&a3);
              if ( v17 && (v18 = *((_DWORD *)v17 + 1)) != 0 )
              {
                if ( (v56 & 0x800) != 0 )
                {
                  v19 = (unsigned int)*v17 >> 1;
                  p_Str = v18;
                  v54 = v19;
                  v49 = 1;
                  goto LABEL_148;
                }
                v49 = 0;
                p_Str = v18;
                v20 = *v17;
              }
              else
              {
                p_Str = (int)off_60ACD0;
                v20 = strlen(off_60ACD0);
              }
              goto LABEL_147;
            }
            if ( v4 == 99 )
              goto LABEL_69;
            if ( v4 != 100 )
              goto LABEL_148;
LABEL_114:
            v56 |= 0x40u;
LABEL_115:
            v54 = 10;
            goto LABEL_116;
          }
          switch ( v4 )
          {
            case 'X':
              goto LABEL_105;
            case 'C':
              if ( (v56 & 0x830) == 0 )
                BYTE1(v56) |= 8u;
LABEL_69:
              if ( (v56 & 0x810) != 0 )
              {
                short_arg = get_short_arg(&a3);
                v54 = wctomb(&Str, short_arg);
                if ( v54 < 0 )
                  v48 = 1;
              }
              else
              {
                Str = get_int_arg(&a3);
                v54 = 1;
              }
              p_Str = (int)&Str;
              break;
            case 'E':
            case 'G':
              v45 = 1;
              v4 += 32;
LABEL_65:
              v56 |= 0x40u;
              p_Str = (int)&Str;
              if ( v7 >= 0 )
              {
                if ( !v7 && v4 == 103 )
                  v53 = 1;
              }
              else
              {
                v53 = 6;
              }
              a3 += 8;
              v41 = *(_DWORD *)(a3 - 8);
              v42 = *(_DWORD *)(a3 - 4);
              off_60ACB8[0]();
            case 'S':
              if ( (v56 & 0x830) == 0 )
                BYTE1(v56) |= 8u;
LABEL_55:
              v11 = v53;
              if ( v53 == -1 )
                v11 = 0x7FFFFFFF;
              v12 = get_int_arg(&a3);
              v13 = (char *)v12;
              p_Str = v12;
              if ( (v56 & 0x810) != 0 )
              {
                if ( !v12 )
                {
                  v13 = (char *)off_60ACD4;
                  p_Str = (int)off_60ACD4;
                }
                v49 = 1;
                for ( i = v13; ; i += 2 )
                {
                  v15 = v11--;
                  if ( !v15 || !*(_WORD *)i )
                    break;
                }
                v20 = (i - v13) >> 1;
              }
              else
              {
                if ( !v12 )
                {
                  v13 = off_60ACD0;
                  p_Str = (int)off_60ACD0;
                }
                for ( j = v13; ; ++j )
                {
                  v22 = v11--;
                  if ( !v22 || !*j )
                    break;
                }
                v20 = j - v13;
              }
LABEL_147:
              v54 = v20;
              break;
          }
LABEL_148:
          if ( v48 )
            goto LABEL_171;
          v31 = v56;
          if ( (v56 & 0x40) == 0 )
            goto LABEL_157;
          if ( (v56 & 0x100) != 0 )
          {
            LOBYTE(v52[0]) = 45;
LABEL_156:
            v51 = 1;
            goto LABEL_157;
          }
          if ( (v56 & 1) != 0 )
          {
            LOBYTE(v52[0]) = 43;
            goto LABEL_156;
          }
          if ( (v56 & 2) != 0 )
          {
            LOBYTE(v52[0]) = 32;
            goto LABEL_156;
          }
LABEL_157:
          v32 = (char *)(v50 - v51 - v54);
          if ( (v56 & 0xC) == 0 )
            write_multi_char(32, (char *)(v50 - v51 - v54), File, &v52[1]);
          write_string((char *)v52, (char *)v51, File, &v52[1]);
          if ( (v31 & 8) != 0 && (v31 & 4) == 0 )
            write_multi_char(48, v32, File, &v52[1]);
          if ( v49 && v54 > 0 )
          {
            v33 = (wchar_t *)p_Str;
            v34 = v54 - 1;
            do
            {
              v35 = *v33++;
              v36 = (char *)wctomb(MbCh, v35);
              if ( (int)v36 <= 0 )
                break;
              write_string(MbCh, v36, File, &v52[1]);
            }
            while ( v34-- );
          }
          else
          {
            write_string((char *)p_Str, (char *)v54, File, &v52[1]);
          }
          if ( (v56 & 4) != 0 )
            write_multi_char(32, v32, File, &v52[1]);
LABEL_171:
          v4 = *v57;
          v5 = v57 + 1;
          v6 = *v57++ == 0;
          if ( v6 )
            return *(_DWORD *)&v52[1];
          v7 = v53;
          v3 = v46;
          break;
        default:
          goto LABEL_171;
      }
    }
  }
  return *(_DWORD *)&v52[1];
}

// 0x00557333
_DWORD *__cdecl write_char(int a1, FILE *File, _DWORD *a3)
{
  int v4; // eax
  bool v5; // zf
  _DWORD *result; // eax

  if ( --File->_cnt < 0 )
  {
    v4 = _flsbuf(a1, File);
  }
  else
  {
    *File->_ptr++ = a1;
    v4 = (unsigned __int8)a1;
  }
  v5 = v4 == -1;
  result = a3;
  if ( v5 )
    *a3 = -1;
  else
    ++*a3;
  return result;
}

// 0x00557368
char *__cdecl write_multi_char(int a1, char *a2, FILE *File, _DWORD *a4)
{
  char *result; // eax
  char *i; // edi

  result = a2;
  for ( i = a2 - 1; (int)result > 0; result = i-- )
  {
    result = (char *)write_char(a1, File, a4);
    if ( *a4 == -1 )
      break;
  }
  return result;
}

// 0x00557399
char *__cdecl write_string(char *a1, char *a2, FILE *File, _DWORD *a4)
{
  char *result; // eax
  char *i; // ebx
  int v7; // eax

  result = a2;
  for ( i = a2 - 1; (int)result > 0; result = i-- )
  {
    v7 = *a1++;
    result = (char *)write_char(v7, File, a4);
    if ( *a4 == -1 )
      break;
  }
  return result;
}

// 0x005573D1
int __cdecl get_int_arg(_DWORD *a1)
{
  *a1 += 4;
  return *(_DWORD *)(*a1 - 4);
}

// 0x005573DE
__int64 __cdecl get_int64_arg(_DWORD *a1)
{
  *a1 += 8;
  return *(_QWORD *)(*a1 - 8);
}

// 0x005573EE
__int16 __cdecl get_short_arg(_DWORD *a1)
{
  *a1 += 4;
  return *(_WORD *)(*a1 - 4);
}

// 0x005573FC
int __cdecl __InternalCxxFrameHandler(
        struct EHExceptionRecord *ExceptionRecord,
        struct EHRegistrationNode *a2,
        struct _CONTEXT *a3,
        void *a4,
        EXCEPTION_POINTERS *a5,
        int a6,
        struct EHRegistrationNode *TargetFrame,
        unsigned __int8 a8)
{
  int (__cdecl *pForwardCompat)(); // ecx
  struct _EXCEPTION_POINTERS *v10; // [esp+0h] [ebp-8h]

  if ( a5->ExceptionRecord != (_EXCEPTION_RECORD *)429065504 )
    UnhandledExceptionFilter_0(v10);
  if ( (ExceptionRecord->ExceptionFlags & 0x66) != 0 )
  {
    if ( a5->ContextRecord )
    {
      if ( !a6 )
        __FrameUnwindToState((int)a2, (int)a4, (int)a5, -1);
    }
  }
  else if ( a5[1].ContextRecord )
  {
    if ( ExceptionRecord->ExceptionCode == -529697949 && ExceptionRecord->params.magicNumber > 0x19930520 )
    {
      pForwardCompat = ExceptionRecord->params.pThrowInfo->pForwardCompat;
      if ( pForwardCompat )
        return ((int (__cdecl *)(struct EHExceptionRecord *, struct EHRegistrationNode *, struct _CONTEXT *, void *, EXCEPTION_POINTERS *, int, struct EHRegistrationNode *, _DWORD))pForwardCompat)(
                 ExceptionRecord,
                 a2,
                 a3,
                 a4,
                 a5,
                 a6,
                 TargetFrame,
                 a8);
    }
    FindHandler(ExceptionRecord, a2, a3, a4, a5, a8, a6, TargetFrame);
  }
  return 1;
}

// 0x00557497
void __cdecl FindHandler(
        struct EHExceptionRecord *ExceptionRecord,
        struct EHRegistrationNode *a2,
        struct _CONTEXT *a3,
        void *a4,
        EXCEPTION_POINTERS *a5,
        char a6,
        int a7,
        struct EHRegistrationNode *TargetFrame)
{
  struct EHExceptionRecord *v8; // esi
  int v9; // edi
  const struct _s_TryBlockMapEntry *v10; // ebx
  CatchableTypeArray *pCatchableTypeArray; // eax
  const struct _s_CatchableType **arrayOfCatchableTypes; // edi
  struct _EXCEPTION_POINTERS *v13; // [esp-Ch] [ebp-24h]
  unsigned int v14; // [esp+0h] [ebp-18h] BYREF
  unsigned __int8 v15[4]; // [esp+4h] [ebp-14h]
  int state; // [esp+8h] [ebp-10h]
  int nCatches; // [esp+Ch] [ebp-Ch]
  int nCatchableTypes; // [esp+10h] [ebp-8h]
  unsigned int v19; // [esp+14h] [ebp-4h] BYREF
  struct _s_HandlerType *ExceptionRecorda; // [esp+20h] [ebp+8h]

  v15[0] = 0;
  state = a2->state;
  if ( state < -1 || state >= (int)a5->ContextRecord )
    UnhandledExceptionFilter_0((struct _EXCEPTION_POINTERS *)v14);
  v8 = ExceptionRecord;
  if ( ExceptionRecord->ExceptionCode != -529697949 )
    goto LABEL_35;
  if ( ExceptionRecord->NumberParameters == 3
    && ExceptionRecord->params.magicNumber == 429065504
    && !ExceptionRecord->params.pThrowInfo )
  {
    v8 = (struct EHExceptionRecord *)lp;
    if ( !lp )
      return;
    a3 = (struct _CONTEXT *)dword_189538C;
    v15[0] = 1;
    if ( !_ValidateRead(lp, 1u) )
      UnhandledExceptionFilter_0(v13);
    if ( v8->ExceptionCode != -529697949 )
      goto LABEL_35;
    if ( v8->NumberParameters == 3 && v8->params.magicNumber == 429065504 && !v8->params.pThrowInfo )
      UnhandledExceptionFilter_0(v13);
  }
  if ( v8->ExceptionCode != -529697949 || v8->NumberParameters != 3 || v8->params.magicNumber != 429065504 )
  {
LABEL_35:
    if ( a6 )
      sub_557C4C();
    FindHandlerForForeignException(
      v8,
      a2,
      a3,
      a4,
      (const struct _s_FuncInfo *)a5,
      (EXCEPTION_POINTERS *)state,
      a7,
      TargetFrame);
    return;
  }
  v9 = state;
  v10 = (const struct _s_TryBlockMapEntry *)_GetRangeOfTrysToCheck(
                                              (const struct _s_FuncInfo *)a5,
                                              a7,
                                              (EXCEPTION_POINTERS *)state,
                                              &v19,
                                              &v14);
  while ( v19 < v14 )
  {
    if ( v10->tryLow <= v9 && v9 <= v10->tryHigh )
    {
      ExceptionRecorda = (struct _s_HandlerType *)v10->pHandlerArray;
      nCatches = v10->nCatches;
      if ( nCatches > 0 )
      {
        while ( 1 )
        {
          pCatchableTypeArray = v8->params.pThrowInfo->pCatchableTypeArray;
          arrayOfCatchableTypes = (const struct _s_CatchableType **)pCatchableTypeArray->arrayOfCatchableTypes;
          nCatchableTypes = pCatchableTypeArray->nCatchableTypes;
          if ( nCatchableTypes > 0 )
            break;
LABEL_27:
          --nCatches;
          ++ExceptionRecorda;
          if ( nCatches <= 0 )
            goto LABEL_30;
        }
        while ( !TypeMatch(ExceptionRecorda, *arrayOfCatchableTypes, v8->params.pThrowInfo) )
        {
          --nCatchableTypes;
          ++arrayOfCatchableTypes;
          if ( nCatchableTypes <= 0 )
            goto LABEL_27;
        }
        CatchIt(
          v8,
          a2,
          a3,
          a4,
          (const struct _s_FuncInfo *)a5,
          ExceptionRecorda,
          *arrayOfCatchableTypes,
          v10,
          a7,
          TargetFrame);
      }
LABEL_30:
      v9 = state;
    }
    ++v19;
    ++v10;
  }
  if ( a6 )
    unknown_libname_530((int)v8);
}

// 0x0055763E
void __cdecl FindHandlerForForeignException(
        struct EHExceptionRecord *ExceptionRecord,
        struct EHRegistrationNode *a2,
        struct _CONTEXT *a3,
        void *a4,
        const struct _s_FuncInfo *a5,
        EXCEPTION_POINTERS *a6,
        int a7,
        struct EHRegistrationNode *TargetFrame)
{
  const struct _s_TryBlockMapEntry *v8; // esi
  int v9; // eax
  int v10; // ecx
  unsigned int v11; // [esp+8h] [ebp-8h] BYREF
  unsigned int v12; // [esp+Ch] [ebp-4h] BYREF

  if ( !dword_1895390 || !_CallSETranslator(ExceptionRecord, a2, a3, a4, a5, a7, TargetFrame) )
  {
    v8 = (const struct _s_TryBlockMapEntry *)_GetRangeOfTrysToCheck(a5, a7, a6, &v12, &v11);
    while ( v12 < v11 )
    {
      if ( (int)a6 >= v8->tryLow && (int)a6 <= v8->tryHigh )
      {
        v9 = (int)&v8->pHandlerArray[v8->nCatches];
        v10 = *(_DWORD *)(v9 - 12);
        if ( !v10 || !*(_BYTE *)(v10 + 8) )
          CatchIt(ExceptionRecord, a2, a3, a4, a5, (struct _s_HandlerType *)(v9 - 16), 0, v8, a7, TargetFrame);
      }
      ++v12;
      ++v8;
    }
  }
}

// 0x005576E6
BOOL __cdecl TypeMatch(
        const struct _s_HandlerType *a1,
        const struct _s_CatchableType *a2,
        const struct _s_ThrowInfo *a3)
{
  TypeDescriptor *pType; // eax
  TypeDescriptor *v4; // ecx
  BOOL result; // eax

  pType = a1->pType;
  result = 1;
  if ( pType && pType->name[0] )
  {
    v4 = a2->pType;
    if ( pType != v4 )
    {
      if ( strcmp(pType->name, v4->name) )
        return 0;
    }
    if ( (a2->properties & 2) != 0 && (a1->adjectives & 8) == 0
      || (a3->attributes & 1) != 0 && (a1->adjectives & 1) == 0
      || (a3->attributes & 2) != 0 && (a1->adjectives & 2) == 0 )
    {
      return 0;
    }
  }
  return result;
}

// 0x00557743
void __cdecl __FrameUnwindToState(int a1, int a2, int a3, int a4)
{
  int i; // esi
  int v5; // eax
  struct _EXCEPTION_POINTERS *v6; // [esp+0h] [ebp-28h]

  for ( i = *(_DWORD *)(a1 + 8); i != a4; i = *(_DWORD *)(*(_DWORD *)(a3 + 8) + 8 * i) )
  {
    if ( i <= -1 || i >= *(_DWORD *)(a3 + 4) )
      UnhandledExceptionFilter_0(v6);
    v5 = *(_DWORD *)(*(_DWORD *)(a3 + 8) + 8 * i + 4);
    if ( v5 )
      _CallSettingFrame(v5, a1, 259);
  }
  *(_DWORD *)(a1 + 8) = i;
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

// 0x005577F7
void __cdecl CatchIt(
        struct EHExceptionRecord *ExceptionRecord,
        struct EHRegistrationNode *a2,
        struct _CONTEXT *a3,
        void *a4,
        const struct _s_FuncInfo *a5,
        struct _s_HandlerType *a6,
        const struct _s_CatchableType *a7,
        const struct _s_TryBlockMapEntry *a8,
        int a9,
        PVOID TargetFrame)
{
  void (__stdcall *v10)(void *, struct EHRegistrationNode *); // eax

  if ( a7 )
    BuildCatchObject(ExceptionRecord, a2, a6, a7);
  if ( TargetFrame )
    _UnwindNestedFrames((struct _EXCEPTION_REGISTRATION_RECORD **)a6, TargetFrame, (PEXCEPTION_RECORD)ExceptionRecord);
  else
    _UnwindNestedFrames((struct _EXCEPTION_REGISTRATION_RECORD **)a6, a2, (PEXCEPTION_RECORD)ExceptionRecord);
  __FrameUnwindToState((int)a2, (int)a4, (int)a5, a8->tryLow);
  a2->state = a8->tryHigh + 1;
  v10 = (void (__stdcall *)(void *, struct EHRegistrationNode *))CallCatchBlock(
                                                                   ExceptionRecord,
                                                                   a2,
                                                                   a3,
                                                                   a5,
                                                                   a6->addressOfHandler,
                                                                   a9,
                                                                   0x100u);
  if ( v10 )
    _JumpToContinuation(v10, a2);
}

// 0x00557872
int __cdecl CallCatchBlock(
        struct EHExceptionRecord *a1,
        struct EHRegistrationNode *a2,
        struct _CONTEXT *a3,
        const struct _s_FuncInfo *a4,
        void *a5,
        int a6,
        unsigned int a7)
{
  int v7; // eax
  int v9; // [esp+Ch] [ebp-2Ch]
  __ehstate_t state; // [esp+10h] [ebp-28h]
  int v11; // [esp+18h] [ebp-20h]
  void *v12; // [esp+1Ch] [ebp-1Ch]

  state = a2[-1].state;
  v12 = lp;
  v11 = dword_189538C;
  lp = a1;
  dword_189538C = (int)a3;
  _CallCatchBlock2(a2, a4, a5, a6, a7);
  v9 = v7;
  a2[-1].state = state;
  lp = v12;
  dword_189538C = v11;
  if ( a1->ExceptionCode == -529697949 && a1->NumberParameters == 3 && a1->params.magicNumber == 429065504 && v7 )
  {
    _abnormal_termination();
    unknown_libname_530((int)a1);
  }
  return v9;
}

// 0x0055797E
BOOL __cdecl ExFilterRethrow(struct _EXCEPTION_POINTERS *a1)
{
  _EXCEPTION_RECORD *ExceptionRecord; // eax

  ExceptionRecord = a1->ExceptionRecord;
  return a1->ExceptionRecord->ExceptionCode == -529697949
      && ExceptionRecord->NumberParameters == 3
      && ExceptionRecord->ExceptionInformation[0] == 429065504
      && !ExceptionRecord->ExceptionInformation[2];
}

// 0x005579A8
void __cdecl BuildCatchObject(
        struct EHExceptionRecord *a1,
        struct EHRegistrationNode *a2,
        const struct _s_HandlerType *a3,
        const struct _s_CatchableType *a4)
{
  TypeDescriptor *pType; // eax
  ptrdiff_t dispCatchObj; // eax
  char **v6; // edi
  char *pExceptionObject; // eax
  char *v8; // eax
  char *v9; // eax
  void *v10; // [esp-8h] [ebp-30h]
  size_t sizeOrOffset; // [esp-4h] [ebp-2Ch]
  struct _EXCEPTION_POINTERS *v12; // [esp+0h] [ebp-28h]

  pType = a3->pType;
  if ( pType )
  {
    if ( pType->name[0] )
    {
      dispCatchObj = a3->dispCatchObj;
      if ( dispCatchObj )
      {
        v6 = (char **)((char *)&a2[1] + dispCatchObj);
        if ( (a3->adjectives & 8) != 0 )
        {
          if ( _ValidateRead(a1->params.pExceptionObject, 1u) && _ValidateWrite(v6, 1u) )
          {
            pExceptionObject = (char *)a1->params.pExceptionObject;
            *v6 = pExceptionObject;
            v8 = AdjustPointer(pExceptionObject, &a4->thisDisplacement);
LABEL_8:
            *v6 = v8;
            return;
          }
LABEL_25:
          UnhandledExceptionFilter_0(v12);
        }
        if ( (a4->properties & 1) != 0 )
        {
          if ( !_ValidateRead(a1->params.pExceptionObject, 1u) || !_ValidateWrite(v6, 1u) )
            goto LABEL_25;
          memcpy(v6, a1->params.pExceptionObject, a4->sizeOrOffset);
          if ( a4->sizeOrOffset == 4 && *v6 )
          {
            v8 = AdjustPointer(*v6, &a4->thisDisplacement);
            goto LABEL_8;
          }
        }
        else
        {
          v10 = a1->params.pExceptionObject;
          if ( a4->copyFunction )
          {
            if ( !_ValidateRead(v10, 1u) || !_ValidateWrite(v6, 1u) || !_ValidateExecute((FARPROC)a4->copyFunction) )
              goto LABEL_25;
            if ( (a4->properties & 4) != 0 )
            {
              AdjustPointer((char *)a1->params.pExceptionObject, &a4->thisDisplacement);
              sub_55310F((int)v6, (int)a4->copyFunction);
            }
            else
            {
              AdjustPointer((char *)a1->params.pExceptionObject, &a4->thisDisplacement);
              sub_553108((int)v6, (int)a4->copyFunction);
            }
          }
          else
          {
            if ( !_ValidateRead(v10, 1u) || !_ValidateWrite(v6, 1u) )
              goto LABEL_25;
            sizeOrOffset = a4->sizeOrOffset;
            v9 = AdjustPointer((char *)a1->params.pExceptionObject, &a4->thisDisplacement);
            memcpy(v6, v9, sizeOrOffset);
          }
        }
      }
    }
  }
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

// 0x00557BD3
char *__cdecl AdjustPointer(char *a1, const struct PMD *a2)
{
  int pdisp; // edx
  char *result; // eax

  pdisp = a2->pdisp;
  result = &a1[a2->mdisp];
  if ( pdisp >= 0 )
    result += pdisp + *(_DWORD *)(*(_DWORD *)&a1[pdisp] + a2->vdisp);
  return result;
}

// 0x00557C00
void __stdcall _CallSettingFrame(int a1, int a2, int a3)
{
  void (*v3)(void); // eax
  int v4; // ecx

  _NLG_Notify1(a3);
  v3();
  v4 = a3;
  if ( a3 == 256 )
    v4 = 2;
  _NLG_Notify1(v4);
}

// 0x00557CA2
LONG __stdcall __noreturn UnhandledExceptionFilter_0(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
  EXCEPTION_POINTERS *v1; // ecx
  int v2; // [esp-Ch] [ebp-24h] BYREF
  CPPEH_RECORD ms_exc; // [esp+0h] [ebp-18h]

  ms_exc.registration.ScopeTable = stru_573370;
  ms_exc.registration.ExceptionHandler = _except_handler3;
  ms_exc.registration.Next = (struct _EH3_EXCEPTION_REGISTRATION *)NtCurrentTeb()->NtTib.ExceptionList;
  ms_exc.exc_ptr = v1;
  ms_exc.old_esp = (DWORD)&v2;
  ms_exc.registration.TryLevel = 0;
  if ( off_60ACE4 )
  {
    ms_exc.registration.TryLevel = 1;
    off_60ACE4();
  }
  ms_exc.registration.TryLevel = -1;
  sub_557C4C();
}

// 0x00557D00
int __cdecl strcmp(const char *Str1, const char *Str2)
{
  const char *v2; // edx
  const char *v3; // ecx
  unsigned int v4; // eax
  bool v5; // cf
  unsigned int v6; // eax
  __int16 v8; // ax

  v2 = Str1;
  v3 = Str2;
  if ( ((unsigned __int8)Str1 & 3) == 0 )
  {
dodwords:
    while ( 1 )
    {
      v4 = *(_DWORD *)v2;
      v5 = (unsigned __int8)*(_DWORD *)v2 < (unsigned int)*v3;
      if ( (unsigned __int8)*(_DWORD *)v2 != *v3 )
        break;
      if ( !(_BYTE)v4 )
        return 0;
      v5 = BYTE1(v4) < (unsigned int)v3[1];
      if ( BYTE1(v4) != v3[1] )
        break;
      if ( !BYTE1(v4) )
        return 0;
      v6 = HIWORD(v4);
      v5 = (unsigned __int8)v6 < (unsigned int)v3[2];
      if ( (_BYTE)v6 != v3[2] )
        break;
      if ( !(_BYTE)v6 )
        return 0;
      v5 = BYTE1(v6) < (unsigned int)v3[3];
      if ( BYTE1(v6) != v3[3] )
        break;
      v3 += 4;
      v2 += 4;
      if ( !BYTE1(v6) )
        return 0;
    }
    return -2 * v5 + 1;
  }
  if ( ((unsigned __int8)Str1 & 1) != 0 )
  {
    v2 = Str1 + 1;
    v5 = *Str1 < (unsigned int)*Str2;
    if ( *Str1 != *Str2 )
      return -2 * v5 + 1;
    v3 = Str2 + 1;
    if ( !*Str1 )
      return 0;
    if ( ((unsigned __int8)v2 & 2) == 0 )
      goto dodwords;
  }
  v8 = *(_WORD *)v2;
  v2 += 2;
  v5 = (unsigned __int8)v8 < (unsigned int)*v3;
  if ( (_BYTE)v8 != *v3 )
    return -2 * v5 + 1;
  if ( !(_BYTE)v8 )
    return 0;
  v5 = HIBYTE(v8) < (unsigned int)v3[1];
  if ( HIBYTE(v8) == v3[1] )
  {
    if ( HIBYTE(v8) )
    {
      v3 += 2;
      goto dodwords;
    }
    return 0;
  }
  return -2 * v5 + 1;
}

// 0x00557D84
LONG __stdcall __CxxUnhandledExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
  _EXCEPTION_RECORD *ExceptionRecord; // eax

  ExceptionRecord = ExceptionInfo->ExceptionRecord;
  if ( ExceptionInfo->ExceptionRecord->ExceptionCode == -529697949
    && ExceptionRecord->NumberParameters == 3
    && ExceptionRecord->ExceptionInformation[0] == 429065504 )
  {
    sub_557C4C();
  }
  if ( lpTopLevelExceptionFilter && _ValidateExecute((FARPROC)lpTopLevelExceptionFilter) )
    return lpTopLevelExceptionFilter(ExceptionInfo);
  else
    return 0;
}

// 0x00557DE8
int __cdecl _freebuf(int a1)
{
  int result; // eax

  result = *(_DWORD *)(a1 + 12);
  if ( (result & 0x83) != 0 && (result & 8) != 0 )
  {
    free(*(void **)(a1 + 8));
    *(_WORD *)(a1 + 12) &= 0xFBF7u;
    *(_DWORD *)a1 = 0;
    *(_DWORD *)(a1 + 8) = 0;
    *(_DWORD *)(a1 + 4) = 0;
    return 0;
  }
  return result;
}

// 0x00557E13
int __cdecl _lseek(int FileHandle, int Offset, int Origin)
{
  int v3; // esi
  void *osfhandle; // eax
  DWORD v5; // ebx
  DWORD LastError; // eax

  if ( FileHandle < uNumber
    && (v3 = 8 * (FileHandle & 0x1F), (*(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + v3 + 4) & 1) != 0) )
  {
    osfhandle = (void *)_get_osfhandle(FileHandle);
    if ( osfhandle == (void *)-1 )
    {
      g_PlayerData_33C = 9;
    }
    else
    {
      v5 = SetFilePointer(osfhandle, Offset, 0, Origin);
      if ( v5 == -1 )
        LastError = GetLastError();
      else
        LastError = 0;
      if ( !LastError )
      {
        *(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + v3 + 4) &= ~2u;
        return v5;
      }
      _dosmaperr(LastError);
    }
  }
  else
  {
    g_PlayerData_340 = 0;
    g_PlayerData_33C = 9;
  }
  return -1;
}

// 0x00557EAD
UINT _ioinit()
{
  char *v0; // eax
  char *v1; // esi
  unsigned int i; // eax
  signed int v3; // esi
  unsigned __int8 *v4; // ebp
  HANDLE *v5; // ebx
  _DWORD *v6; // edi
  char *v7; // eax
  unsigned int j; // ecx
  int k; // edi
  int v10; // eax
  int m; // ebx
  int v12; // esi
  DWORD v13; // eax
  HANDLE StdHandle; // eax
  HANDLE v15; // edi
  DWORD FileType; // eax
  struct _STARTUPINFOA StartupInfo; // [esp+10h] [ebp-44h] BYREF

  v0 = (char *)malloc(0x100u);
  v1 = v0;
  if ( !v0 )
    _amsg_exit(0x1Bu);
  g_nUIState = (int)v0;
  uNumber = 32;
  for ( i = (unsigned int)(v0 + 256); (unsigned int)v1 < i; i = g_nUIState + 256 )
  {
    v1[4] = 0;
    *(_DWORD *)v1 = -1;
    v1[5] = 10;
    v1 += 8;
  }
  GetStartupInfoA(&StartupInfo);
  if ( StartupInfo.cbReserved2 && StartupInfo.lpReserved2 )
  {
    v3 = *(_DWORD *)StartupInfo.lpReserved2;
    v4 = StartupInfo.lpReserved2 + 4;
    v5 = (HANDLE *)&StartupInfo.lpReserved2[*(_DWORD *)StartupInfo.lpReserved2 + 4];
    if ( *(int *)StartupInfo.lpReserved2 >= 2048 )
      v3 = 2048;
    if ( (int)uNumber < v3 )
    {
      v6 = &unk_1896BE4;
      while ( 1 )
      {
        v7 = (char *)malloc(0x100u);
        if ( !v7 )
          break;
        uNumber += 32;
        *v6 = v7;
        for ( j = (unsigned int)(v7 + 256); (unsigned int)v7 < j; j = *v6 + 256 )
        {
          v7[4] = 0;
          *(_DWORD *)v7 = -1;
          v7[5] = 10;
          v7 += 8;
        }
        ++v6;
        if ( (int)uNumber >= v3 )
          goto LABEL_19;
      }
      v3 = uNumber;
    }
LABEL_19:
    for ( k = 0; k < v3; ++v5 )
    {
      if ( *v5 != (HANDLE)-1 && (*v4 & 1) != 0 && ((*v4 & 8) != 0 || GetFileType(*v5)) )
      {
        v10 = *(&g_nUIState + (k >> 5)) + 8 * (k & 0x1F);
        *(_DWORD *)v10 = *v5;
        *(_BYTE *)(v10 + 4) = *v4;
      }
      ++k;
      ++v4;
    }
  }
  for ( m = 0; m < 3; ++m )
  {
    v12 = g_nUIState + 8 * m;
    if ( *(_DWORD *)v12 == -1 )
    {
      *(_BYTE *)(v12 + 4) = -127;
      if ( m )
        v13 = -(m != 1) - 11;
      else
        v13 = -10;
      StdHandle = GetStdHandle(v13);
      v15 = StdHandle;
      if ( StdHandle == (HANDLE)-1
        || (FileType = GetFileType(StdHandle)) == 0
        || (*(_DWORD *)v12 = v15, (unsigned __int8)FileType == 2) )
      {
        *(_BYTE *)(v12 + 4) |= 0x40u;
      }
      else if ( (unsigned __int8)FileType == 3 )
      {
        *(_BYTE *)(v12 + 4) |= 8u;
      }
    }
    else
    {
      *(_BYTE *)(v12 + 4) |= 0x80u;
    }
  }
  return SetHandleCount(uNumber);
}

// 0x00558058
int __cdecl _write(int FileHandle, const void *Buf, unsigned int MaxCharCount)
{
  _DWORD *v3; // ebx
  int v4; // esi
  char v5; // al
  int v7; // eax
  char *v8; // eax
  char *v9; // ecx
  char v10; // cl
  signed int v11; // edi
  _BYTE Buffer[1028]; // [esp+Ch] [ebp-414h] BYREF
  int v13; // [esp+410h] [ebp-10h]
  DWORD NumberOfBytesWritten; // [esp+414h] [ebp-Ch] BYREF
  DWORD v15; // [esp+418h] [ebp-8h]
  char *v16; // [esp+41Ch] [ebp-4h]
  DWORD FileHandlea; // [esp+428h] [ebp+8h]

  if ( FileHandle < uNumber
    && (v3 = (_DWORD *)(4 * (FileHandle >> 5) + 25783264),
        v4 = 8 * (FileHandle & 0x1F),
        v5 = *(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + v4 + 4),
        (v5 & 1) != 0) )
  {
    v15 = 0;
    v13 = 0;
    if ( !MaxCharCount )
      return 0;
    if ( (v5 & 0x20) != 0 )
      _lseek(FileHandle, 0, 2);
    v7 = v4 + *(&g_nUIState + (FileHandle >> 5));
    if ( *(char *)(v7 + 4) >= 0 )
    {
      if ( WriteFile(*(HANDLE *)v7, Buf, MaxCharCount, &NumberOfBytesWritten, 0) )
      {
        FileHandlea = 0;
        v15 = NumberOfBytesWritten;
      }
      else
      {
        FileHandlea = GetLastError();
      }
    }
    else
    {
      v16 = (char *)Buf;
      FileHandlea = 0;
      while ( 1 )
      {
        v8 = Buffer;
        do
        {
          if ( v16 - (_BYTE *)Buf >= MaxCharCount )
            break;
          v9 = v16++;
          v10 = *v9;
          if ( v10 == 10 )
          {
            ++v13;
            *v8++ = 13;
          }
          *v8++ = v10;
        }
        while ( v8 - Buffer < 1024 );
        v11 = v8 - Buffer;
        if ( !WriteFile(*(HANDLE *)(*v3 + v4), Buffer, v8 - Buffer, &NumberOfBytesWritten, 0) )
          break;
        v15 += NumberOfBytesWritten;
        if ( (int)NumberOfBytesWritten < v11 || v16 - (_BYTE *)Buf >= MaxCharCount )
          goto LABEL_17;
      }
      FileHandlea = GetLastError();
    }
LABEL_17:
    if ( v15 )
      return v15 - v13;
    if ( FileHandlea )
    {
      if ( FileHandlea == 5 )
      {
        g_PlayerData_33C = 9;
        g_PlayerData_340 = 5;
      }
      else
      {
        _dosmaperr(FileHandlea);
      }
    }
    else
    {
      if ( (*(_BYTE *)(*v3 + v4 + 4) & 0x40) != 0 && *(_BYTE *)Buf == 26 )
        return 0;
      g_PlayerData_33C = 28;
      g_PlayerData_340 = 0;
    }
  }
  else
  {
    g_PlayerData_340 = 0;
    g_PlayerData_33C = 9;
  }
  return -1;
}

// 0x00558205
_DWORD *__cdecl _openfile(char *FileName, _BYTE *a2, int ShareFlag, _DWORD *a4)
{
  _BYTE *v4; // edi
  char v5; // al
  unsigned int v6; // ecx
  unsigned int v7; // esi
  int v8; // edx
  char v9; // al
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // ecx
  int v18; // [esp+Ch] [ebp-8h]
  int v19; // [esp+10h] [ebp-4h]

  v4 = a2;
  v18 = 0;
  v19 = 0;
  v5 = *a2;
  if ( *a2 == 97 )
  {
    v6 = 265;
LABEL_7:
    v7 = dword_1895530 | 2;
    goto LABEL_8;
  }
  if ( v5 != 114 )
  {
    if ( v5 != 119 )
      return 0;
    v6 = 769;
    goto LABEL_7;
  }
  v6 = 0;
  v7 = dword_1895530 | 1;
LABEL_8:
  v8 = 1;
  while ( 1 )
  {
    v9 = *++v4;
    if ( !v9 || !v8 )
      break;
    if ( v9 > 84 )
    {
      v13 = v9 - 98;
      if ( v13 )
      {
        v14 = v13 - 1;
        if ( v14 )
        {
          v15 = v14 - 11;
          if ( v15 )
          {
            if ( v15 != 6 || (v6 & 0xC000) != 0 )
LABEL_38:
              v8 = 0;
            else
              BYTE1(v6) |= 0x40u;
          }
          else
          {
            if ( v18 )
              goto LABEL_38;
            v18 = 1;
            v7 &= ~0x4000u;
          }
        }
        else
        {
          if ( v18 )
            goto LABEL_38;
          v18 = 1;
          v7 |= 0x4000u;
        }
      }
      else
      {
        if ( (v6 & 0xC000) != 0 )
          goto LABEL_38;
        BYTE1(v6) |= 0x80u;
      }
    }
    else if ( v9 == 84 )
    {
      if ( (v6 & 0x1000) != 0 )
        goto LABEL_38;
      v6 |= 0x1000u;
    }
    else
    {
      v10 = v9 - 43;
      if ( v10 )
      {
        v11 = v10 - 25;
        if ( v11 )
        {
          v12 = v11 - 14;
          if ( v12 )
          {
            if ( v12 != 1 || v19 )
              goto LABEL_38;
            v19 = 1;
            v6 |= 0x20u;
          }
          else
          {
            if ( v19 )
              goto LABEL_38;
            v19 = 1;
            v6 |= 0x10u;
          }
        }
        else
        {
          if ( (v6 & 0x40) != 0 )
            goto LABEL_38;
          v6 |= 0x40u;
        }
      }
      else
      {
        if ( (v6 & 2) != 0 )
          goto LABEL_38;
        v6 = v6 & 0xFFFFFFFC | 2;
        v7 = v7 & 0xFFFFFF7C | 0x80;
      }
    }
  }
  v16 = _sopen(FileName, v6, ShareFlag, 420);
  if ( v16 < 0 )
    return 0;
  ++dword_18953DC;
  a4[3] = v7;
  a4[1] = 0;
  *a4 = 0;
  a4[2] = 0;
  a4[7] = 0;
  a4[4] = v16;
  return a4;
}

// 0x00558375
_DWORD *_getstream()
{
  _DWORD *v0; // esi
  int v1; // eax
  int i; // edi
  int v3; // edi
  _DWORD *v4; // edi

  v0 = 0;
  v1 = 0;
  if ( (int)Count > 0 )
  {
    for ( i = g_PlayerLevel; *(_DWORD *)i; i += 4 )
    {
      if ( (*(_BYTE *)(*(_DWORD *)i + 12) & 0x83) == 0 )
      {
        v0 = *(_DWORD **)(g_PlayerLevel + 4 * v1);
        goto LABEL_10;
      }
      if ( ++v1 >= (int)Count )
        return v0;
    }
    v3 = 4 * v1;
    *(_DWORD *)(v3 + g_PlayerLevel) = malloc(0x20u);
    v4 = *(_DWORD **)(v3 + g_PlayerLevel);
    if ( !v4 )
      return v0;
    v0 = v4;
LABEL_10:
    if ( v0 )
    {
      v0[4] = -1;
      v0[1] = 0;
      v0[3] = 0;
      v0[2] = 0;
      *v0 = 0;
      v0[7] = 0;
    }
  }
  return v0;
}

// 0x005583F0
char *__cdecl strcpy(char *Destination, const char *Source)
{
  JUMPOUT(0x558461);
}

// 0x00558400
char *__cdecl strcat(char *Destination, const char *Source)
{
  char *v2; // ecx
  int v4; // eax
  int v5; // eax
  char *v6; // edi
  const char *v7; // ecx
  int v8; // edx
  int v9; // eax

  v2 = Destination;
  if ( ((unsigned __int8)Destination & 3) == 0 )
    goto find_end_of_dest_string_loop;
  do
  {
    if ( !*v2++ )
    {
start_byte_3_0:
      v6 = v2 - 1;
      goto copy_start_0;
    }
  }
  while ( ((unsigned __int8)v2 & 3) != 0 );
  while ( 1 )
  {
    do
    {
find_end_of_dest_string_loop:
      v4 = (*(_DWORD *)v2 + 2130640639) ^ ~*(_DWORD *)v2;
      v2 += 4;
    }
    while ( (v4 & 0x81010100) == 0 );
    v5 = *((_DWORD *)v2 - 1);
    if ( !(_BYTE)v5 )
      break;
    if ( !BYTE1(v5) )
    {
      v6 = v2 - 3;
      goto copy_start_0;
    }
    if ( ((unsigned int)&unk_FF0000 & v5) == 0 )
    {
      v6 = v2 - 2;
      goto copy_start_0;
    }
    if ( (v5 & 0xFF000000) == 0 )
      goto start_byte_3_0;
  }
  v6 = v2 - 4;
copy_start_0:
  v7 = Source;
  if ( ((unsigned __int8)Source & 3) == 0 )
    goto main_loop_entrance_1;
  while ( 1 )
  {
    LOBYTE(v8) = *v7++;
    if ( !(_BYTE)v8 )
      break;
    *v6++ = v8;
    if ( ((unsigned __int8)v7 & 3) == 0 )
    {
      while ( 1 )
      {
main_loop_entrance_1:
        v9 = (*(_DWORD *)v7 + 2130640639) ^ ~*(_DWORD *)v7;
        v8 = *(_DWORD *)v7;
        v7 += 4;
        if ( (v9 & 0x81010100) != 0 )
        {
          if ( !(_BYTE)v8 )
            goto LABEL_26;
          if ( !BYTE1(v8) )
          {
            *(_WORD *)v6 = (unsigned __int8)v8;
            return Destination;
          }
          if ( ((unsigned int)&unk_FF0000 & v8) == 0 )
          {
            *(_WORD *)v6 = v8;
            v6[2] = 0;
            return Destination;
          }
          if ( (v8 & 0xFF000000) == 0 )
          {
            *(_DWORD *)v6 = v8;
            return Destination;
          }
        }
        *(_DWORD *)v6 = v8;
        v6 += 4;
      }
    }
  }
LABEL_26:
  *v6 = v8;
  return Destination;
}

// 0x005584E0
int __cdecl __crtLCMapStringA(
        LCID Locale,
        DWORD dwMapFlags,
        CHAR *lpSrcStr,
        _BYTE *cchSrc,
        LPSTR lpDestStr,
        int cchDest,
        UINT CodePage,
        int a8)
{
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  void *v12; // esp
  int v13; // eax
  int v14; // esi
  int v15; // eax
  void *v16; // esp
  int v17; // eax
  WCHAR v18[8]; // [esp+0h] [ebp-38h] BYREF
  int v19; // [esp+10h] [ebp-28h]
  LPWSTR lpWideCharStr; // [esp+14h] [ebp-24h]
  WCHAR *v21; // [esp+18h] [ebp-20h]
  int v22; // [esp+1Ch] [ebp-1Ch]
  CPPEH_RECORD ms_exc; // [esp+20h] [ebp-18h]

  if ( !dword_189539C )
  {
    if ( LCMapStringW(0, 0x100u, &SrcStr, 1, 0, 0) )
    {
      dword_189539C = 1;
    }
    else
    {
      if ( !LCMapStringA(0, 0x100u, unk_BFDAA4, 1, 0, 0) )
        return 0;
      dword_189539C = 2;
    }
  }
  if ( (int)cchSrc > 0 )
    cchSrc = strncnt(lpSrcStr, (int)cchSrc);
  if ( dword_189539C == 2 )
    return LCMapStringA(Locale, dwMapFlags, lpSrcStr, (int)cchSrc, lpDestStr, cchDest);
  if ( dword_189539C != 1 )
    return 0;
  if ( !CodePage )
    CodePage = dword_18953B8;
  v9 = MultiByteToWideChar(CodePage, a8 != 0 ? 9 : 1, lpSrcStr, (int)cchSrc, 0, 0);
  v10 = v9;
  v22 = v9;
  if ( !v9 )
    return 0;
  v11 = 2 * v9 + 3;
  LOBYTE(v11) = v11 & 0xFC;
  v12 = alloca(v11);
  ms_exc.old_esp = (DWORD)v18;
  lpWideCharStr = v18;
  ms_exc.registration.TryLevel = -1;
  if ( !v18 )
    return 0;
  if ( !MultiByteToWideChar(CodePage, 1u, lpSrcStr, (int)cchSrc, lpWideCharStr, v10) )
    return 0;
  v13 = LCMapStringW(Locale, dwMapFlags, lpWideCharStr, v10, 0, 0);
  v14 = v13;
  v19 = v13;
  if ( !v13 )
    return 0;
  if ( (dwMapFlags & 0x400) != 0 )
  {
    if ( cchDest && (v13 > cchDest || !LCMapStringW(Locale, dwMapFlags, lpWideCharStr, v10, (LPWSTR)lpDestStr, cchDest)) )
      return 0;
  }
  else
  {
    v15 = 2 * v13 + 3;
    LOBYTE(v15) = v15 & 0xFC;
    v16 = alloca(v15);
    ms_exc.old_esp = (DWORD)v18;
    v21 = v18;
    ms_exc.registration.TryLevel = -1;
    if ( !v18 || !LCMapStringW(Locale, dwMapFlags, lpWideCharStr, v22, v18, v14) )
      return 0;
    v17 = cchDest
        ? WideCharToMultiByte(CodePage, 0x220u, v18, v14, lpDestStr, cchDest, 0, 0)
        : WideCharToMultiByte(CodePage, 0x220u, v18, v14, 0, 0, 0, 0);
    v14 = v17;
    if ( !v17 )
      return 0;
  }
  return v14;
}

// 0x00558704
_BYTE *__cdecl strncnt(_BYTE *a1, int a2)
{
  _BYTE *v2; // eax
  int v3; // ecx

  v2 = a1;
  v3 = a2 - 1;
  if ( a2 )
  {
    do
    {
      if ( !*v2 )
        break;
      ++v2;
    }
    while ( v3-- );
  }
  if ( *v2 )
    return (_BYTE *)a2;
  else
    return (_BYTE *)(v2 - a1);
}

// 0x0055872F
int __cdecl _isctype(int C, int Type)
{
  int v2; // ecx
  int v3; // eax
  int result; // eax
  int SrcStr; // [esp+0h] [ebp-4h] BYREF

  SrcStr = v2;
  if ( (unsigned int)(C + 1) <= 0x100 )
  {
    v3 = *((unsigned __int16 *)g_pVtbl_SceneMgr + C);
    return Type & v3;
  }
  if ( *((char *)g_pVtbl_SceneMgr + 2 * BYTE1(C) + 1) >= 0 )
  {
    LOWORD(SrcStr) = (unsigned __int8)C;
    result = __crtGetStringTypeA(1u, (LPCSTR)&SrcStr, 1, (LPWORD)&C + 1, 0, 0, 1);
  }
  else
  {
    LOBYTE(SrcStr) = BYTE1(C);
    *(_WORD *)((char *)&SrcStr + 1) = (unsigned __int8)C;
    result = __crtGetStringTypeA(1u, (LPCSTR)&SrcStr, 2, (LPWORD)&C + 1, 0, 0, 1);
  }
  if ( result )
  {
    v3 = HIWORD(C);
    return Type & v3;
  }
  return result;
}

// 0x005587B0
__int64 __stdcall _allmul(__int64 a1, __int64 a2)
{
  if ( HIDWORD(a1) | HIDWORD(a2) )
    return a1 * a2;
  else
    return (unsigned int)a2 * (unsigned __int64)(unsigned int)a1;
}

// 0x005587E4
int __cdecl _filbuf(FILE *File)
{
  int flag; // eax
  int v2; // eax
  int v3; // edx
  _BYTE *v4; // edi
  int v5; // ecx
  char *ptr; // ecx
  int result; // eax

  flag = File->_flag;
  if ( (flag & 0x83) == 0 || (flag & 0x40) != 0 )
    return -1;
  if ( (flag & 2) != 0 )
  {
    LOBYTE(flag) = flag | 0x20;
    File->_flag = flag;
    return -1;
  }
  LOBYTE(flag) = flag | 1;
  File->_flag = flag;
  if ( (flag & 0x10C) != 0 )
    File->_ptr = File->_base;
  else
    _getbuf(File);
  v2 = _read(File->_file, File->_base, File->_bufsiz);
  File->_cnt = v2;
  if ( !v2 || v2 == -1 )
  {
    File->_flag |= v2 != 0 ? 32 : 16;
    File->_cnt = 0;
    return -1;
  }
  v3 = File->_flag;
  if ( (v3 & 0x82) == 0 )
  {
    v4 = File->_file == -1 ? &unk_60ACF0 : (_BYTE *)(*(&g_nUIState + (File->_file >> 5)) + 8 * (File->_file & 0x1F));
    if ( (v4[4] & 0x82) == 0x82 )
    {
      BYTE1(v3) |= 0x20u;
      File->_flag = v3;
    }
  }
  if ( File->_bufsiz == 512 )
  {
    v5 = File->_flag;
    if ( (v5 & 8) != 0 && (v5 & 0x400) == 0 )
      File->_bufsiz = 4096;
  }
  ptr = File->_ptr;
  File->_cnt = v2 - 1;
  result = (unsigned __int8)*ptr;
  File->_ptr = ptr + 1;
  return result;
}

// 0x005588BD
int __cdecl _read(int FileHandle, void *DstBuf, unsigned int MaxCharCount)
{
  int v3; // esi
  int v4; // eax
  char v5; // dl
  char *v6; // edi
  char *v7; // ecx
  char v8; // al
  int v9; // eax
  DWORD LastError; // eax
  int v12; // eax
  char *v13; // ecx
  char v14; // al
  char v15; // al
  char *v16; // ecx
  bool v17; // cf
  char v18; // al
  char v19; // al
  _BYTE *v20; // esi
  DWORD NumberOfBytesRead; // [esp+Ch] [ebp-Ch] BYREF
  unsigned int v22; // [esp+10h] [ebp-8h]
  char Buffer; // [esp+17h] [ebp-1h] BYREF
  char *nNumberOfBytesToRead; // [esp+28h] [ebp+10h]

  if ( FileHandle >= uNumber
    || (v3 = 8 * (FileHandle & 0x1F),
        v4 = v3 + *(&g_nUIState + (FileHandle >> 5)),
        v5 = *(_BYTE *)(v4 + 4),
        (v5 & 1) == 0) )
  {
    g_PlayerData_340 = 0;
    g_PlayerData_33C = 9;
    return -1;
  }
  v22 = 0;
  v6 = (char *)DstBuf;
  v7 = (char *)DstBuf;
  if ( !MaxCharCount || (v5 & 2) != 0 )
    return 0;
  if ( (v5 & 0x48) != 0 )
  {
    v8 = *(_BYTE *)(v4 + 5);
    if ( v8 != 10 )
    {
      --MaxCharCount;
      *(_BYTE *)DstBuf = v8;
      v9 = *(&g_nUIState + (FileHandle >> 5));
      v7 = (char *)DstBuf + 1;
      v22 = 1;
      *(_BYTE *)(v9 + v3 + 5) = 10;
    }
  }
  if ( ReadFile(
         *(HANDLE *)(*(&g_nUIState + (FileHandle >> 5)) + 8 * (FileHandle & 0x1F)),
         v7,
         MaxCharCount,
         &NumberOfBytesRead,
         0) )
  {
    v12 = *(&g_nUIState + (FileHandle >> 5));
    v22 += NumberOfBytesRead;
    v13 = (char *)(v12 + v3 + 4);
    v14 = *v13;
    if ( *v13 < 0 )
    {
      if ( NumberOfBytesRead && *(_BYTE *)DstBuf == 10 )
        v15 = v14 | 4;
      else
        v15 = v14 & 0xFB;
      *v13 = v15;
      nNumberOfBytesToRead = (char *)DstBuf;
      v16 = (char *)DstBuf + v22;
      v17 = DstBuf < (char *)DstBuf + v22;
      v22 += (unsigned int)DstBuf;
      if ( v17 )
      {
        do
        {
          v18 = *nNumberOfBytesToRead;
          if ( *nNumberOfBytesToRead == 26 )
          {
            v20 = (_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + v3 + 4);
            if ( (*v20 & 0x40) == 0 )
              *v20 |= 2u;
            return v6 - (_BYTE *)DstBuf;
          }
          if ( v18 == 13 )
          {
            if ( nNumberOfBytesToRead >= v16 - 1 )
            {
              ++nNumberOfBytesToRead;
              if ( !ReadFile(
                      *(HANDLE *)(*(&g_nUIState + (FileHandle >> 5)) + 8 * (FileHandle & 0x1F)),
                      &Buffer,
                      1u,
                      &NumberOfBytesRead,
                      0)
                && GetLastError()
                || !NumberOfBytesRead )
              {
LABEL_37:
                *v6 = 13;
                goto LABEL_38;
              }
              if ( (*(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + v3 + 4) & 0x48) != 0 )
              {
                v19 = Buffer;
                if ( Buffer == 10 )
                  goto LABEL_35;
                *v6++ = 13;
                *(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + v3 + 5) = v19;
              }
              else
              {
                if ( v6 == DstBuf && Buffer == 10 )
                  goto LABEL_35;
                _lseek(FileHandle, -1, 1);
                if ( Buffer != 10 )
                  goto LABEL_37;
              }
            }
            else
            {
              if ( nNumberOfBytesToRead[1] == 10 )
              {
                nNumberOfBytesToRead += 2;
LABEL_35:
                *v6 = 10;
LABEL_38:
                ++v6;
                goto LABEL_39;
              }
              *v6++ = 13;
              ++nNumberOfBytesToRead;
            }
          }
          else
          {
            *v6++ = v18;
            ++nNumberOfBytesToRead;
          }
LABEL_39:
          v16 = (char *)v22;
        }
        while ( (unsigned int)nNumberOfBytesToRead < v22 );
      }
      return v6 - (_BYTE *)DstBuf;
    }
    return v22;
  }
  LastError = GetLastError();
  if ( LastError != 5 )
  {
    if ( LastError != 109 )
    {
      _dosmaperr(LastError);
      return -1;
    }
    return 0;
  }
  g_PlayerData_33C = 9;
  g_PlayerData_340 = 5;
  return -1;
}

// 0x00558AC0
int __usercall _trandisp1@<eax>(int a1@<edx>, __int16 a2@<cx>, int a3@<ebp>, __int16 a4@<fpstat>, double _ST7@<st0>)
{
  __int16 v5; // bx

  if ( *(_BYTE *)(a1 + 14) == 5 )
  {
    HIBYTE(v5) = HIBYTE(*(_WORD *)(a3 - 164)) & 0xFC | 2;
    LOBYTE(v5) = 63;
  }
  else
  {
    v5 = 4927;
  }
  *(_WORD *)(a3 - 162) = v5;
  _EBX = &unk_60AF3D;
  __asm { fxam }
  *(_DWORD *)(a3 - 148) = a1;
  *(_WORD *)(a3 - 160) = a4;
  *(_BYTE *)(a3 - 144) = 0;
  LOBYTE(a2) = __ROL1__((char)(2 * *(_BYTE *)(a3 - 159)) >> 1, 1);
  _AL = a2 & 0xF;
  __asm { xlat }
  return (*(int (__thiscall **)(int))(_AL + a1 + 16))(a2 & 0x404);
}

// 0x00558C79
void __usercall _rttosnpopde(int a1@<ebp>)
{
  *(_BYTE *)(a1 - 144) = 1;
}

// 0x00558C89
void chsifnegret()
{
  ;
}

// 0x00558C90
void _startTwoArgErrorHandling()
{
  JUMPOUT(0x558CB0);
}

// 0x00558CA7
double __usercall _startOneArgErrorHandling@<st0>(
        int a1@<eax>,
        int a2@<edx>,
        int a3@<ecx>,
        double a4@<st0>,
        __int16 a5,
        int a6,
        int a7,
        int a8)
{
  _DWORD v9[6]; // [esp+0h] [ebp-20h] BYREF
  double v10; // [esp+18h] [ebp-8h]

  v9[0] = a1;
  v10 = a4;
  v9[1] = a3;
  v9[2] = a7;
  v9[3] = a8;
  _87except(a2, (int)v9, (int)&a5);
  return v10;
}

// 0x00558CF0
long double __usercall _twoToTOS@<st0>(double a1@<st0>)
{
  _ST6 = a1;
  __asm { frndint }
  return __FSCALE__(__F2XM1__(-(_ST6 - a1)) + 1.0, _ST6);
}

// 0x00558D05
void _load_CW()
{
  ;
}

// 0x00558D1C
double __usercall _convertTOStoQNaN@<st0>(int a1@<eax>, double result@<st0>)
{
  if ( (a1 & 0x80000) == 0 )
    return result + 1.0;
  return result;
}

// 0x00558D35
double __fastcall _fload_withFB(int a1, _DWORD *a2)
{
  double result; // st7

  if ( (a2[1] & 0x7FF00000) != 0x7FF00000 )
    return *(double *)a2;
  *(_QWORD *)&result = *(_QWORD *)a2 << 11;
  return result;
}

// 0x00558D78
int __cdecl _checkTOS_withFB(int a1, int a2)
{
  int result; // eax

  result = a2 & 0x7FF00000;
  if ( (a2 & 0x7FF00000) == 0x7FF00000 )
    return a2;
  return result;
}

// 0x00558DC5
void _check_overflow_exit()
{
  __asm { fst     [esp+8+var_8] }
  JUMPOUT(0x558DED);
}

// 0x00558E7C
void *__cdecl _fltin(char *a1)
{
  int v1; // edi
  char v2; // bl
  int v3; // eax
  unsigned __int16 v5[6]; // [esp+Ch] [ebp-18h] BYREF
  double v6; // [esp+18h] [ebp-Ch] BYREF
  char *v7; // [esp+20h] [ebp-4h] BYREF

  v1 = 0;
  v2 = __strgtold12((int)v5, &v7, a1, 0, 0, 0, 0);
  if ( (v2 & 4) != 0 )
  {
    v1 = 512;
    v6 = 0.0;
  }
  else
  {
    v3 = sub_55BA88(v5, (unsigned int *)&v6);
    if ( (v2 & 2) != 0 || v3 == 1 )
      v1 = 128;
    if ( (v2 & 1) != 0 || v3 == 2 )
      v1 |= 0x100u;
  }
  *(_DWORD *)off_60AF50 = v1;
  *((_DWORD *)off_60AF50 + 1) = v7 - a1;
  *((double *)off_60AF50 + 2) = v6;
  return off_60AF50;
}

// 0x00558F0D
int __cdecl _setmbcp(int CodePage)
{
  UINT SystemCP; // eax
  UINT v2; // esi
  int v3; // edx
  _DWORD *v4; // eax
  unsigned __int8 *v5; // ecx
  unsigned __int8 v6; // dl
  unsigned int i; // eax
  int v8; // esi
  char *v9; // ebx
  unsigned __int8 *v10; // ecx
  unsigned __int8 v11; // dl
  unsigned int v12; // eax
  unsigned int v13; // edi
  char v14; // dl
  int v15; // eax
  _DWORD *v16; // esi
  unsigned int j; // eax
  struct _cpinfo CPInfo; // [esp+Ch] [ebp-18h] BYREF
  unsigned int v20; // [esp+20h] [ebp-4h]
  UINT CodePagea; // [esp+2Ch] [ebp+8h]

  SystemCP = getSystemCP(CodePage);
  v2 = SystemCP;
  CodePagea = SystemCP;
  if ( SystemCP == ::CodePage )
    return 0;
  if ( !SystemCP )
  {
LABEL_30:
    setSBCS();
LABEL_31:
    setSBUpLow();
    return 0;
  }
  v3 = 0;
  v4 = &unk_60AF60;
  do
  {
    if ( *v4 == v2 )
    {
      memset(&unk_1896AC0, 0, 0x100u);
      v20 = 0;
      v8 = 48 * v3;
      unk_1896BC0 = 0;
      v9 = (char *)&unk_60AF70 + 48 * v3;
      do
      {
        v10 = (unsigned __int8 *)v9;
        if ( *v9 )
        {
          do
          {
            v11 = v10[1];
            if ( !v11 )
              break;
            v12 = *v10;
            v13 = v11;
            if ( v12 <= v11 )
            {
              v14 = byte_60AF58[v20];
              do
                *(&g_bQuestActive + v12++) |= v14;
              while ( v12 <= v13 );
            }
            v10 += 2;
          }
          while ( *v10 );
        }
        ++v20;
        v9 += 8;
      }
      while ( v20 < 4 );
      dword_18969BC = 1;
      ::CodePage = CodePagea;
      v15 = CPtoLCID(CodePagea);
      v16 = (_DWORD *)((char *)&unk_60AF64 + v8);
      unk_18969B0 = *v16++;
      unk_18969B4 = *v16;
      Locale = v15;
      unk_18969B8 = v16[1];
      goto LABEL_31;
    }
    v4 += 12;
    ++v3;
  }
  while ( (int)v4 < (int)&tbyte_60B050 );
  if ( GetCPInfo(v2, &CPInfo) )
  {
    ::CodePage = v2;
    memset(&unk_1896AC0, 0, 0x100u);
    unk_1896BC0 = 0;
    Locale = 0;
    if ( CPInfo.MaxCharSize <= 1 )
    {
      dword_18969BC = 0;
    }
    else
    {
      if ( CPInfo.LeadByte[0] )
      {
        v5 = &CPInfo.LeadByte[1];
        do
        {
          v6 = *v5;
          if ( !*v5 )
            break;
          for ( i = *(v5 - 1); i <= v6; ++i )
            *(&g_bQuestActive + i) |= 4u;
          v5 += 2;
        }
        while ( *(v5 - 1) );
      }
      for ( j = 1; j < 0xFF; ++j )
        *(&g_bQuestActive + j) |= 8u;
      Locale = CPtoLCID(v2);
      dword_18969BC = 1;
    }
    unk_18969B0 = 0;
    unk_18969B4 = 0;
    unk_18969B8 = 0;
    goto LABEL_31;
  }
  if ( dword_18953D8 )
    goto LABEL_30;
  return -1;
}

// 0x005590A6
UINT __cdecl getSystemCP(UINT a1)
{
  UINT result; // eax

  result = a1;
  dword_18953D8 = 0;
  switch ( a1 )
  {
    case 0xFFFFFFFE:
      dword_18953D8 = 1;
      return GetOEMCP();
    case 0xFFFFFFFD:
      dword_18953D8 = 1;
      return GetACP();
    case 0xFFFFFFFC:
      dword_18953D8 = 1;
      return dword_18953B8;
  }
  return result;
}

// 0x005590F0
int __cdecl CPtoLCID(int a1)
{
  switch ( a1 )
  {
    case 932:
      return 1041;
    case 936:
      return 2052;
    case 949:
      return 1042;
    case 950:
      return 1028;
  }
  return 0;
}

// 0x00559123
int setSBCS()
{
  memset(&unk_1896AC0, 0, 0x100u);
  unk_1896BC0 = 0;
  CodePage = 0;
  dword_18969BC = 0;
  Locale = 0;
  unk_18969B0 = 0;
  unk_18969B4 = 0;
  unk_18969B8 = 0;
  return 0;
}

// 0x0055914C
unsigned int setSBUpLow()
{
  unsigned int i; // eax
  unsigned __int8 v1; // al
  unsigned __int8 *v2; // edx
  unsigned int v3; // ecx
  unsigned int result; // eax
  WORD *j; // ecx
  char v6; // dl
  char v7; // cl
  WORD CharType[256]; // [esp+4h] [ebp-514h] BYREF
  CHAR v9[256]; // [esp+204h] [ebp-314h] BYREF
  CHAR DestStr[256]; // [esp+304h] [ebp-214h] BYREF
  CHAR SrcStr[256]; // [esp+404h] [ebp-114h] BYREF
  struct _cpinfo CPInfo; // [esp+504h] [ebp-14h] BYREF

  if ( GetCPInfo(CodePage, &CPInfo) )
  {
    for ( i = 0; i < 0x100; ++i )
      SrcStr[i] = i;
    v1 = CPInfo.LeadByte[0];
    SrcStr[0] = 32;
    if ( CPInfo.LeadByte[0] )
    {
      v2 = &CPInfo.LeadByte[1];
      do
      {
        v3 = *v2;
        if ( v1 <= v3 )
          memset(&SrcStr[v1], 0x20u, v3 - v1 + 1);
        v2 += 2;
        v1 = *(v2 - 1);
      }
      while ( v1 );
    }
    __crtGetStringTypeA(1u, SrcStr, 256, CharType, CodePage, Locale, 0);
    __crtLCMapStringA(Locale, 0x100u, SrcStr, (_BYTE *)0x100, DestStr, 256, CodePage, 0);
    __crtLCMapStringA(Locale, 0x200u, SrcStr, (_BYTE *)0x100, v9, 256, CodePage, 0);
    result = 0;
    for ( j = CharType; ; ++j )
    {
      if ( (*j & 1) != 0 )
      {
        *(&g_bQuestActive + result) |= 0x10u;
        v6 = DestStr[result];
      }
      else
      {
        if ( (*j & 2) == 0 )
        {
          byte_18969C0[result] = 0;
          goto LABEL_16;
        }
        *(&g_bQuestActive + result) |= 0x20u;
        v6 = v9[result];
      }
      byte_18969C0[result] = v6;
LABEL_16:
      if ( ++result >= 0x100 )
        return result;
    }
  }
  for ( result = 0; result < 0x100; ++result )
  {
    if ( result >= 0x41 && result <= 0x5A )
    {
      *(&g_bQuestActive + result) |= 0x10u;
      v7 = result + 32;
LABEL_22:
      byte_18969C0[result] = v7;
      continue;
    }
    if ( result >= 0x61 && result <= 0x7A )
    {
      *(&g_bQuestActive + result) |= 0x20u;
      v7 = result - 32;
      goto LABEL_22;
    }
    byte_18969C0[result] = 0;
  }
  return result;
}

// 0x005592D1
int __initmbctable()
{
  int result; // eax

  if ( !dword_1896CE8 )
  {
    result = _setmbcp(-3);
    dword_1896CE8 = 1;
  }
  return result;
}

// 0x005592F0
long double __usercall fFYTOX@<st0>(int a1@<ebp>, char a2@<ch>, long double a3@<st1>, long double a4@<st0>)
{
  long double result; // st7
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

// 0x00559368
void __usercall _rtinfpopse(int a1@<ebp>)
{
  __asm
  {
    fstp    st
    fstp    st
    fld     tbyte_60B050
  }
  *(_BYTE *)(a1 - 144) = 2;
}

// 0x0055937A
long double __usercall _fFLN@<st0>(int a1@<ebp>, long double a2@<st0>)
{
  __int16 v2; // fps
  bool v3; // c0
  char v4; // c2
  bool v5; // c3

  v3 = a2 < 0.0;
  v4 = 0;
  v5 = a2 == 0.0;
  *(_WORD *)(a1 - 160) = v2;
  if ( (*(_BYTE *)(a1 - 159) & 0x41) != 0 )
    JUMPOUT(0x559363);
  return __FYL2X__(a2, 0.6931471805599453094);
}

// 0x00559394
void __usercall rtforln0(int a1@<ebp>)
{
  *(_BYTE *)(a1 - 144) = 2;
  __asm
  {
    fstp    st
    fld     tbyte_60B05A
  }
}

// 0x005593A4
void __fastcall rtforloginf(char a1)
{
  if ( a1 )
    JUMPOUT(0x5593FB);
}

// 0x005593A9
long double __usercall fFLOGm@<st0>(char a1@<cl>, long double a2@<st0>)
{
  if ( a1 )
    JUMPOUT(0x559363);
  return __FYL2X__(a2, 0.3010299956639811952);
}

// 0x005593B8
// attributes: thunk
void rtforyto0()
{
  __asm
  {
    fstp    st
    fstp    st
    fld1
  }
}

// 0x005593BD
void __usercall rtfor0tox(double a1@<st0>, int a2@<ebp>)
{
  char v2; // cl

  isintTOS(a1);
  if ( v2 )
    rtfor0toneg(a2);
  else
    zerotoxdone();
}

// 0x005593D7
void zerotoxdone()
{
  ;
}

// 0x005593D8
void __usercall rtfor0toneg(int a1@<ebp>)
{
  *(_BYTE *)(a1 - 144) = 2;
  zerotoxdone();
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

// 0x00559422
void expbigret()
{
  ;
}

// 0x0055942F
void __usercall _rtinfpop(int a1@<ebp>)
{
  __asm
  {
    fstp    st
    fstp    st
    fld     tbyte_60B050
  }
  *(_BYTE *)(a1 - 144) = 3;
}

// 0x00559441
void __fastcall rtforexpinf(char a1)
{
  if ( a1 )
    JUMPOUT(0x5593F4);
  __asm
  {
    fstp    st
    fld     tbyte_60B050
  }
}

// 0x0055944E
// positive sp value has been detected, the output may be wrong!
void __usercall _ffexpm1(char a1@<ch>, int _EBP@<ebp>)
{
  __asm
  {
    fld     st
    fabs
    fld     tbyte_60B06E
    fcompp
    fstsw   word ptr [ebp-0A0h]
  }
  if ( (*(_BYTE *)(_EBP - 159) & 0x41) != 0 )
  {
    __asm
    {
      ftst
      fstsw   word ptr [ebp-0A0h]
    }
    if ( (*(_BYTE *)(_EBP - 159) & 1) != 0 )
    {
      *(_BYTE *)(_EBP - 144) = 4;
      __asm
      {
        fstp    st
        fldz
      }
    }
    else
    {
      __asm
      {
        fstp    st
        fld     tbyte_60B050
      }
      if ( a1 )
        __asm { fchs }
      expbigret();
    }
  }
  else
  {
    __asm
    {
      fld     st
      frndint
      ftst
      fstsw   word ptr [ebp-0A0h]
    }
    __asm
    {
      fxch    st(1)
      fsub    st, st(1)
      ftst
      fstsw   word ptr [ebp-0A0h]
      fabs
      f2xm1
    }
  }
}

// 0x00559491
void __usercall isintTOS(double a1@<st0>)
{
  _ST6 = a1;
  __asm { frndint }
  if ( _ST6 == a1 )
  {
    _ST5 = a1 * dbl_60B082;
    __asm { frndint }
    if ( _ST5 == a1 * dbl_60B082 )
      evenint();
    else
      isintTOSret();
  }
  else
  {
    notanint();
  }
}

// 0x005594B6
void isintTOSret()
{
  ;
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

// 0x005594C5
double __usercall usepowhlp@<st0>(int a1@<ebp>, double a2@<st1>, double a3@<st0>)
{
  int v4; // eax
  double result; // st7
  double *v6; // [esp+10h] [ebp-7Ch]
  double v7[15]; // [esp+14h] [ebp-78h] BYREF

  _ESI = v7;
  v6 = v7;
  __asm { fsave   byte ptr [esi+8] }
  v4 = _powhlp(a3, a2, v7);
  __asm { frstor  byte ptr [esi+8] }
  result = v7[0];
  if ( v4 )
    _rttosnpopde(a1);
  return result;
}

// 0x005594F7
int __cdecl _powhlp(double a1, double a2, double *a3)
{
  double v4; // st7
  int v5; // esi
  char v6; // c0
  double v7; // st7
  int v8; // ecx

  v4 = a1;
  v5 = 0;
  if ( v6 )
    v4 = -a1;
  if ( HIDWORD(a2) != 2146435072 )
  {
    if ( a2 == -INFINITY )
    {
      if ( v4 > 1.0 )
        goto LABEL_17;
      if ( v4 >= 1.0 )
        goto LABEL_7;
LABEL_15:
      v7 = dbl_60B5C8;
LABEL_28:
      *a3 = v7;
      return v5;
    }
LABEL_12:
    if ( HIDWORD(a1) == 2146435072 )
    {
      if ( LODWORD(a1) )
        return v5;
      if ( a2 > 0.0 )
        goto LABEL_15;
      if ( a2 < 0.0 )
        goto LABEL_17;
    }
    else
    {
      if ( a1 != -INFINITY )
        return v5;
      v8 = _d_inttype(a2);
      if ( a2 > 0.0 )
      {
        v7 = dbl_60B5C8;
        if ( v8 == 1 )
          v7 = -dbl_60B5C8;
        goto LABEL_28;
      }
      if ( a2 < 0.0 )
      {
        if ( v8 == 1 )
          v7 = dbl_60B5E8;
        else
          v7 = 0.0;
        goto LABEL_28;
      }
    }
    v7 = 1.0;
    goto LABEL_28;
  }
  if ( LODWORD(a2) )
    goto LABEL_12;
  if ( v4 > 1.0 )
    goto LABEL_15;
  if ( v4 < 1.0 )
  {
LABEL_17:
    v7 = 0.0;
    goto LABEL_28;
  }
LABEL_7:
  v5 = 1;
  *a3 = dbl_60B5D0;
  return v5;
}

// 0x00559627
int __cdecl _d_inttype(double X)
{
  if ( (_fpclass(X) & 0x90) != 0 || _frnd(X) != X )
    return 0;
  if ( _frnd(X / 2.0) == X / 2.0 )
    return 2;
  else
    return 1;
}

// 0x0055968C
int __cdecl _commit(int FileHandle)
{
  void *osfhandle; // eax
  int result; // eax

  if ( FileHandle >= uNumber || (*(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + 8 * (FileHandle & 0x1F) + 4) & 1) == 0 )
    goto LABEL_8;
  osfhandle = (void *)_get_osfhandle(FileHandle);
  if ( FlushFileBuffers(osfhandle) )
    result = 0;
  else
    result = GetLastError();
  if ( result )
  {
    g_PlayerData_340 = result;
LABEL_8:
    g_PlayerData_33C = 9;
    return -1;
  }
  return result;
}

// 0x005596E3
int __initstdio()
{
  size_t v0; // eax
  int v1; // ecx
  _UNKNOWN **v2; // eax
  int v3; // edx
  _DWORD *v4; // ecx
  int result; // eax

  v0 = Count;
  if ( !Count )
  {
    v0 = 512;
LABEL_5:
    Count = v0;
    goto LABEL_6;
  }
  if ( (int)Count < 20 )
  {
    v0 = 20;
    goto LABEL_5;
  }
LABEL_6:
  g_PlayerLevel = (int)calloc(v0, 4u);
  if ( !g_PlayerLevel )
  {
    Count = 20;
    g_PlayerLevel = (int)calloc(0x14u, 4u);
    if ( !g_PlayerLevel )
      _amsg_exit(0x1Au);
  }
  v1 = 0;
  v2 = &off_60B0B8;
  do
  {
    *(_DWORD *)(v1 + g_PlayerLevel) = v2;
    v2 += 8;
    v1 += 4;
  }
  while ( (int)v2 < (int)asc_60B338 );
  v3 = 0;
  v4 = &unk_60B0C8;
  do
  {
    result = *(_DWORD *)(*(&g_nUIState + (v3 >> 5)) + 8 * (v3 & 0x1F));
    if ( result == -1 || !result )
      *v4 = -1;
    v4 += 8;
    ++v3;
  }
  while ( (int)v4 < (int)dword_60B128 );
  return result;
}

// 0x00559788
int __endstdio()
{
  int result; // eax

  result = _flushall();
  if ( byte_189537C )
    return _fcloseall();
  return result;
}

// 0x0055979C
int __cdecl _stbuf(int a1)
{
  int v1; // eax
  int *v2; // edi
  void *v3; // eax
  int v4; // edi

  if ( !_isatty(*(_DWORD *)(a1 + 16)) )
    return 0;
  if ( (_UNKNOWN *)a1 == &unk_60B0D8 )
  {
    v1 = 0;
  }
  else
  {
    if ( (_UNKNOWN *)a1 != &unk_60B0F8 )
      return 0;
    v1 = 1;
  }
  ++dword_18953DC;
  if ( (*(_WORD *)(a1 + 12) & 0x10C) != 0 )
    return 0;
  v2 = (int *)(4 * v1 + 25777120);
  if ( dword_18953E0[v1] || (v3 = malloc(0x1000u), (*v2 = (int)v3) != 0) )
  {
    v4 = *v2;
    *(_DWORD *)(a1 + 24) = 4096;
    *(_DWORD *)(a1 + 8) = v4;
    *(_DWORD *)a1 = v4;
    *(_DWORD *)(a1 + 4) = 4096;
  }
  else
  {
    *(_DWORD *)(a1 + 8) = a1 + 20;
    *(_DWORD *)a1 = a1 + 20;
    *(_DWORD *)(a1 + 24) = 2;
    *(_DWORD *)(a1 + 4) = 2;
  }
  *(_WORD *)(a1 + 12) |= 0x1102u;
  return 1;
}

// 0x00559829
int __cdecl _ftbuf(int a1, int a2)
{
  int result; // eax

  if ( a1 )
  {
    if ( (*(_BYTE *)(a2 + 13) & 0x10) != 0 )
    {
      result = _flush((_DWORD *)a2);
      *(_BYTE *)(a2 + 13) &= 0xEEu;
      *(_DWORD *)(a2 + 24) = 0;
      *(_DWORD *)a2 = 0;
      *(_DWORD *)(a2 + 8) = 0;
    }
  }
  else
  {
    result = a2;
    if ( (*(_BYTE *)(a2 + 13) & 0x10) != 0 )
      return _flush((_DWORD *)a2);
  }
  return result;
}

// 0x00559866
int __cdecl _input(FILE *Stream, char *a2, int a3)
{
  char *v3; // esi
  unsigned __int8 v4; // al
  FILE *v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int i; // eax
  int v10; // eax
  int v11; // edi
  int v12; // ebx
  int v13; // eax
  int v14; // esi
  int v15; // eax
  int v16; // ebx
  int v17; // ebx
  char *v18; // esi
  FILE *v19; // edi
  int v26; // eax
  char *v30; // edi
  int v31; // eax
  unsigned int v32; // edx
  unsigned __int8 v33; // al
  unsigned __int8 v34; // cl
  unsigned __int8 v35; // al
  int v36; // esi
  wchar_t *v37; // esi
  int v39; // eax
  int v40; // eax
  int v41; // eax
  __int64 v42; // rax
  int v43; // eax
  int v44; // edi
  int v45; // eax
  int v46; // ebx
  int v47; // eax
  int v48; // eax
  int v49; // ecx
  int result; // eax
  int v51; // [esp-4h] [ebp-1D4h]
  char v52; // [esp+Ch] [ebp-1C4h] BYREF
  char v53; // [esp+Dh] [ebp-1C3h] BYREF
  _BYTE v54[32]; // [esp+16Ch] [ebp-64h] BYREF
  int v55; // [esp+18Ch] [ebp-44h]
  wchar_t DstCh; // [esp+192h] [ebp-3Eh] BYREF
  int v57; // [esp+194h] [ebp-3Ch]
  char SrcCh[3]; // [esp+198h] [ebp-38h] BYREF
  char v59; // [esp+19Bh] [ebp-35h]
  int v60; // [esp+19Ch] [ebp-34h]
  wchar_t *v61; // [esp+1A0h] [ebp-30h]
  wchar_t *v62; // [esp+1A4h] [ebp-2Ch]
  __int64 v63; // [esp+1A8h] [ebp-28h]
  int v64; // [esp+1B0h] [ebp-20h]
  int v65; // [esp+1B4h] [ebp-1Ch]
  char v66; // [esp+1B8h] [ebp-18h]
  char v67; // [esp+1B9h] [ebp-17h]
  char v68; // [esp+1BAh] [ebp-16h]
  char v69; // [esp+1BBh] [ebp-15h]
  int C; // [esp+1BCh] [ebp-14h]
  char v71; // [esp+1C1h] [ebp-Fh]
  char v72; // [esp+1C2h] [ebp-Eh]
  char v73; // [esp+1C3h] [ebp-Dh]
  int v74; // [esp+1C4h] [ebp-Ch]
  char v75; // [esp+1CBh] [ebp-5h]
  int v76; // [esp+1CCh] [ebp-4h] BYREF
  char *v77; // [esp+1DCh] [ebp+Ch]
  int v78; // [esp+1DCh] [ebp+Ch]

  v69 = 0;
  v3 = a2;
  v4 = *a2;
  v76 = 0;
  v60 = 0;
  if ( !v4 )
    goto LABEL_256;
  v5 = Stream;
  while ( 2 )
  {
    if ( (int)cbMultiByte <= 1 )
      v6 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * v4) & 8;
    else
      v6 = _isctype(v4, 8);
    if ( v6 )
    {
      --v76;
      v7 = _whiteout(&v76, v5);
      _un_inc(v7, v5);
      v8 = (unsigned __int8)*++v3;
      for ( i = isspace(v8); i; i = isspace(v10) )
        v10 = (unsigned __int8)*++v3;
    }
    if ( *v3 != 37 )
    {
      ++v76;
      v46 = fgetc(v5);
      v47 = (unsigned __int8)*v3++;
      C = v46;
      v78 = (int)v3;
      if ( v47 == v46 )
      {
        if ( *((char *)g_pVtbl_SceneMgr + 2 * (unsigned __int8)v46 + 1) >= 0 )
          goto LABEL_247;
        ++v76;
        v48 = fgetc(v5);
        v49 = (unsigned __int8)*v3++;
        v78 = (int)v3;
        if ( v49 == v48 )
        {
          --v76;
          goto LABEL_247;
        }
        --v76;
        _un_inc(v48, v5);
        --v76;
        _un_inc(v46, v5);
      }
      else
      {
        --v76;
        _un_inc(v46, v5);
      }
      break;
    }
    v59 = 0;
    v66 = 0;
    v67 = 0;
    v72 = 0;
    v71 = 0;
    v68 = 0;
    v11 = 0;
    v75 = 0;
    v65 = 0;
    v64 = 0;
    v74 = 0;
    v73 = 1;
    v61 = 0;
    do
    {
      v12 = (unsigned __int8)*++v3;
      if ( (int)cbMultiByte <= 1 )
        v13 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * (unsigned __int8)v12) & 4;
      else
        v13 = _isctype((unsigned __int8)v12, 4);
      if ( v13 )
      {
        ++v64;
        v74 = v12 + 10 * v74 - 48;
        continue;
      }
      if ( v12 <= 78 )
      {
        switch ( v12 )
        {
          case 'N':
            continue;
          case '*':
            ++v72;
            continue;
          case 'F':
            continue;
          case 'I':
            if ( v3[1] == 54 && v3[2] == 52 )
            {
              v61 = (wchar_t *)((char *)v61 + 1);
              v63 = 0;
              v3 += 2;
              continue;
            }
            break;
          case 'L':
            ++v73;
            continue;
        }
LABEL_32:
        ++v71;
        continue;
      }
      if ( v12 == 104 )
      {
        --v73;
        --v75;
      }
      else
      {
        if ( v12 == 108 )
        {
          ++v73;
        }
        else if ( v12 != 119 )
        {
          goto LABEL_32;
        }
        ++v75;
      }
    }
    while ( !v71 );
    v77 = v3;
    if ( !v72 )
    {
      v55 = a3;
      a3 += 4;
      v62 = *(wchar_t **)(a3 - 4);
    }
    v71 = 0;
    if ( !v75 )
    {
      if ( *v3 == 83 || *v3 == 67 )
        v75 = 1;
      else
        v75 = -1;
    }
    v57 = (unsigned __int8)*v3 | 0x20;
    v14 = v57;
    if ( v57 != 110 )
    {
      if ( v57 == 99 || v57 == 123 )
      {
        ++v76;
        v15 = fgetc(Stream);
      }
      else
      {
        v15 = _whiteout(&v76, Stream);
      }
      C = v15;
    }
    if ( v64 && !v74 )
    {
LABEL_253:
      --v76;
      _un_inc(C, Stream);
      break;
    }
    if ( v14 > 111 )
    {
      switch ( v14 )
      {
        case 'p':
          v73 = 1;
          goto LABEL_181;
        case 's':
          if ( v75 > 0 )
            v68 = 1;
          v30 = asc_60B338;
          break;
        case 'u':
          goto LABEL_181;
        case 'x':
LABEL_63:
          v16 = C;
          if ( C == 45 )
          {
            v67 = 1;
          }
          else if ( C != 43 )
          {
LABEL_129:
            if ( v16 != 48 )
              goto LABEL_189;
            ++v76;
            v31 = fgetc(Stream);
            v16 = v31;
            C = v31;
            if ( (_BYTE)v31 == 120 || (_BYTE)v31 == 88 )
            {
              ++v76;
              v16 = fgetc(Stream);
              C = v16;
              v51 = 120;
              goto LABEL_134;
            }
            v65 = 1;
            if ( v14 != 120 )
            {
              v51 = 111;
LABEL_134:
              v14 = v51;
              goto LABEL_189;
            }
            --v76;
            _un_inc(v31, Stream);
            v16 = 48;
            goto LABEL_188;
          }
          if ( --v74 || !v64 )
          {
            ++v76;
            v16 = fgetc(Stream);
            C = v16;
          }
          else
          {
            v71 = 1;
          }
          goto LABEL_129;
        case '{':
          if ( v75 > 0 )
            v68 = 1;
          v30 = v77 + 1;
          v77 = v30;
          if ( *v30 != 94 )
          {
LABEL_141:
            memset(v54, 0, sizeof(v54));
            if ( v57 == 123 && *v30 == 93 )
            {
              LOBYTE(v32) = 93;
              ++v30;
              v54[11] = 32;
            }
            else
            {
              LOBYTE(v32) = v59;
            }
            while ( 1 )
            {
              v33 = *v30;
              if ( *v30 == 93 )
                break;
              ++v30;
              if ( v33 == 45 && (_BYTE)v32 && (v34 = *v30, *v30 != 93) )
              {
                ++v30;
                if ( (unsigned __int8)v32 >= v34 )
                {
                  v35 = v32;
                  LOBYTE(v32) = v34;
                }
                else
                {
                  v35 = v34;
                }
                if ( (unsigned __int8)v32 <= v35 )
                {
                  v32 = (unsigned __int8)v32;
                  v36 = v35 - (unsigned __int8)v32 + 1;
                  do
                  {
                    v54[v32 >> 3] |= 1 << (v32 & 7);
                    ++v32;
                    --v36;
                  }
                  while ( v36 );
                }
                LOBYTE(v32) = 0;
              }
              else
              {
                LOBYTE(v32) = v33;
                v54[v33 >> 3] |= 1 << (v33 & 7);
              }
            }
            if ( *v30 )
            {
              if ( v57 == 123 )
                v77 = v30;
              v37 = v62;
              --v76;
              v61 = v62;
              _un_inc(C, Stream);
              while ( 1 )
              {
                if ( v64 )
                {
                  if ( !v74-- )
                    break;
                }
                ++v76;
                v39 = fgetc(Stream);
                C = v39;
                if ( v39 == -1 || ((1 << (v39 & 7)) & (v66 ^ (char)v54[v39 >> 3])) == 0 )
                {
                  --v76;
                  _un_inc(v39, Stream);
                  break;
                }
                if ( v72 )
                {
                  v61 = (wchar_t *)((char *)v61 + 1);
                }
                else
                {
                  if ( v68 )
                  {
                    SrcCh[0] = v39;
                    if ( *((char *)g_pVtbl_SceneMgr + 2 * (unsigned __int8)v39 + 1) < 0 )
                    {
                      ++v76;
                      SrcCh[1] = fgetc(Stream);
                    }
                    mbtowc(&DstCh, SrcCh, cbMultiByte);
                    *v37++ = DstCh;
                  }
                  else
                  {
                    *(_BYTE *)v37 = v39;
                    v37 = (wchar_t *)((char *)v37 + 1);
                  }
                  v62 = v37;
                }
              }
              if ( v61 != v37 )
              {
                if ( !v72 )
                {
                  ++v60;
                  if ( v57 != 99 )
                  {
                    if ( v68 )
                      *v62 = 0;
                    else
                      *(_BYTE *)v62 = 0;
                  }
                }
                goto LABEL_242;
              }
            }
            goto LABEL_256;
          }
          ++v30;
          break;
        default:
LABEL_117:
          if ( (unsigned __int8)*v77 == C )
          {
            --v69;
            if ( !v72 )
              a3 = v55;
            goto LABEL_242;
          }
          goto LABEL_253;
      }
LABEL_140:
      v66 = -1;
      goto LABEL_141;
    }
    switch ( v14 )
    {
      case 'o':
LABEL_181:
        v16 = C;
        if ( C == 45 )
        {
          v67 = 1;
        }
        else if ( C != 43 )
        {
          goto LABEL_189;
        }
        if ( !--v74 && v64 )
        {
          v71 = 1;
          goto LABEL_189;
        }
        ++v76;
        v16 = fgetc(Stream);
LABEL_188:
        C = v16;
LABEL_189:
        if ( v61 )
        {
          if ( !v71 )
          {
            while ( 1 )
            {
              if ( v14 == 120 )
              {
                if ( (int)cbMultiByte <= 1 )
                  v40 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * v16) & 0x80;
                else
                  v40 = _isctype(v16, 128);
                if ( !v40 )
                  goto LABEL_209;
                v63 *= 16;
                v16 = _hextodec(v16);
                C = v16;
              }
              else
              {
                if ( (int)cbMultiByte <= 1 )
                  v41 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * v16) & 4;
                else
                  v41 = _isctype(v16, 4);
                if ( !v41 )
                {
LABEL_209:
                  --v76;
                  _un_inc(v16, Stream);
                  break;
                }
                if ( v14 == 111 )
                {
                  if ( v16 >= 56 )
                    goto LABEL_209;
                  v42 = 8 * v63;
                }
                else
                {
                  v42 = 10 * v63;
                }
                v63 = v42;
              }
              ++v65;
              v63 += v16 - 48;
              if ( v64 )
              {
                if ( !--v74 )
                  break;
              }
              ++v76;
              v16 = fgetc(Stream);
              C = v16;
            }
          }
          if ( v67 )
            v63 = -v63;
        }
        else
        {
          if ( !v71 )
          {
            while ( 1 )
            {
              if ( v14 == 120 || v14 == 112 )
              {
                if ( (int)cbMultiByte <= 1 )
                  v45 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * v16) & 0x80;
                else
                  v45 = _isctype(v16, 128);
                if ( !v45 )
                {
LABEL_231:
                  --v76;
                  _un_inc(v16, Stream);
                  break;
                }
                v44 = 16 * v11;
                v16 = _hextodec(v16);
                C = v16;
              }
              else
              {
                if ( (int)cbMultiByte <= 1 )
                  v43 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * v16) & 4;
                else
                  v43 = _isctype(v16, 4);
                if ( !v43 )
                  goto LABEL_231;
                if ( v14 == 111 )
                {
                  if ( v16 >= 56 )
                    goto LABEL_231;
                  v44 = 8 * v11;
                }
                else
                {
                  v44 = 10 * v11;
                }
              }
              ++v65;
              v11 = v44 + v16 - 48;
              if ( v64 )
              {
                if ( !--v74 )
                  break;
              }
              ++v76;
              v16 = fgetc(Stream);
              C = v16;
            }
          }
          if ( v67 )
            v11 = -v11;
        }
        if ( v65 )
        {
          if ( v72 )
            goto LABEL_242;
          ++v60;
          goto LABEL_237;
        }
        goto LABEL_256;
      case 'c':
        if ( !v64 )
        {
          ++v74;
          v64 = 1;
        }
        if ( v75 > 0 )
          v68 = 1;
        v30 = asc_60B340;
        goto LABEL_140;
      case 'd':
        goto LABEL_181;
    }
    if ( v14 <= 100 )
      goto LABEL_117;
    if ( v14 <= 103 )
    {
      v17 = C;
      v18 = &v52;
      if ( C == 45 )
      {
        v52 = 45;
        v18 = &v53;
      }
      else if ( C != 43 )
      {
        v19 = Stream;
        goto LABEL_70;
      }
      v19 = Stream;
      --v74;
      ++v76;
      v17 = fgetc(Stream);
      C = v17;
LABEL_70:
      if ( !v64 || v74 > 349 )
        v74 = 349;
      while ( (int)cbMultiByte <= 1 ? *((_BYTE *)g_pVtbl_SceneMgr + 2 * v17) & 4 : _isctype(v17, 4) )
      {
        if ( !v74-- )
          break;
        ++v65;
        *v18++ = v17;
        ++v76;
        v17 = fgetc(v19);
        C = v17;
      }
      if ( byte_60AF10 == (_BYTE)v17 )
      {
        if ( v74-- )
        {
          ++v76;
          v17 = fgetc(v19);
          *v18 = byte_60AF10;
          C = v17;
          ++v18;
          while ( (int)cbMultiByte <= 1 ? *((_BYTE *)g_pVtbl_SceneMgr + 2 * v17) & 4 : _isctype(v17, 4) )
          {
            if ( !v74-- )
              break;
            ++v65;
            *v18++ = v17;
            ++v76;
            v17 = fgetc(v19);
            C = v17;
          }
        }
      }
      if ( v65 && (v17 == 101 || v17 == 69) )
      {
        if ( v74-- )
        {
          *v18++ = 101;
          ++v76;
          v26 = fgetc(v19);
          v17 = v26;
          C = v26;
          if ( v26 == 45 )
          {
            *v18++ = 45;
            goto LABEL_95;
          }
          if ( v26 == 43 )
          {
LABEL_95:
            if ( !v74-- )
            {
              v74 = 0;
              goto LABEL_98;
            }
            goto LABEL_97;
          }
LABEL_98:
          while ( (int)cbMultiByte <= 1 ? *((_BYTE *)g_pVtbl_SceneMgr + 2 * v17) & 4 : _isctype(v17, 4) )
          {
            if ( !v74-- )
              break;
            ++v65;
            *v18++ = v17;
LABEL_97:
            ++v76;
            v17 = fgetc(v19);
            C = v17;
          }
        }
      }
      --v76;
      _un_inc(v17, v19);
      if ( v65 )
      {
        if ( !v72 )
        {
          ++v60;
          *v18 = 0;
          off_60ACC0[0]();
        }
        goto LABEL_242;
      }
      break;
    }
    if ( v14 == 105 )
    {
      v14 = 100;
      goto LABEL_63;
    }
    if ( v14 != 110 )
      goto LABEL_117;
    v11 = v76;
    if ( v72 )
      goto LABEL_242;
LABEL_237:
    if ( v61 )
    {
      *(_QWORD *)v62 = v63;
    }
    else if ( v73 )
    {
      *(_DWORD *)v62 = v11;
    }
    else
    {
      *v62 = v11;
    }
LABEL_242:
    ++v69;
    v78 = (int)(v77 + 1);
    v3 = (char *)v78;
LABEL_247:
    if ( C == -1 )
    {
      if ( *v3 == 37 && *(_BYTE *)(v78 + 1) == 110 )
      {
        v3 = (char *)v78;
        goto LABEL_251;
      }
LABEL_257:
      result = v60;
      if ( !v60 && !v69 )
        return -1;
      return result;
    }
LABEL_251:
    v4 = *v3;
    if ( *v3 )
    {
      v5 = Stream;
      continue;
    }
    break;
  }
LABEL_256:
  if ( C == -1 )
    goto LABEL_257;
  return v60;
}

// 0x0055A28B
unsigned int __cdecl _hextodec(int C)
{
  int v1; // esi
  int v2; // eax

  v1 = C;
  if ( (int)cbMultiByte <= 1 )
    v2 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * C) & 4;
  else
    v2 = _isctype(C, 4);
  if ( !v2 )
    return (C & 0xFFFFFFDF) - 7;
  return v1;
}

// 0x0055A2C2
int __cdecl fgetc(FILE *Stream)
{
  if ( --Stream->_cnt < 0 )
    return _filbuf(Stream);
  return *(unsigned __int8 *)Stream->_ptr++;
}

// 0x0055A2DC
int __cdecl _un_inc(int Character, FILE *Stream)
{
  int result; // eax

  if ( Character != -1 )
    return ungetc(Character, Stream);
  return result;
}

// 0x0055A2F3
int __cdecl _whiteout(_DWORD *a1, FILE *Stream)
{
  int v2; // edi

  do
  {
    ++*a1;
    v2 = fgetc(Stream);
  }
  while ( isspace(v2) );
  return v2;
}

// 0x0055A317
int *__cdecl _dosmaperr(unsigned int a1)
{
  int v1; // edx
  int *result; // eax

  v1 = 0;
  g_PlayerData_340 = a1;
  result = (int *)&unk_60B348;
  do
  {
    if ( a1 == *result )
    {
      result = (int *)dword_60B34C[2 * v1];
      g_PlayerData_33C = (int)result;
      return result;
    }
    result += 2;
    ++v1;
  }
  while ( (int)result < (int)&dword_60B4B0 );
  if ( a1 < 0x13 || a1 > 0x24 )
  {
    if ( a1 < 0xBC || (g_PlayerData_33C = 8, a1 > 0xCA) )
      g_PlayerData_33C = 22;
  }
  else
  {
    g_PlayerData_33C = 13;
  }
  return result;
}

// 0x0055A37E
int _alloc_osfhnd()
{
  int v0; // ebx
  int v1; // edi
  int v2; // esi
  int *v3; // ecx
  unsigned int v4; // eax
  unsigned int v5; // edx
  char *v6; // eax
  unsigned int v7; // edx

  v0 = -1;
  v1 = 0;
  v2 = 0;
  v3 = &g_nUIState;
  while ( 1 )
  {
    v4 = *v3;
    if ( !*v3 )
      break;
    v5 = v4 + 256;
    while ( v4 < v5 )
    {
      if ( (*(_BYTE *)(v4 + 4) & 1) == 0 )
      {
        *(_DWORD *)v4 = -1;
        v0 = v2 + ((int)(v4 - *v3) >> 3);
        if ( v0 != -1 )
          return v0;
        break;
      }
      v4 += 8;
    }
    ++v3;
    ++v1;
    v2 += 32;
    if ( (int)v3 >= (int)&uNumber )
      return v0;
  }
  v6 = (char *)malloc(0x100u);
  if ( v6 )
  {
    uNumber += 32;
    v7 = (unsigned int)(v6 + 256);
    *(&g_nUIState + v1) = (int)v6;
    while ( (unsigned int)v6 < v7 )
    {
      v6[4] = 0;
      *(_DWORD *)v6 = -1;
      v6[5] = 10;
      v6 += 8;
      v7 = *(&g_nUIState + v1) + 256;
    }
    return 32 * v1;
  }
  return v0;
}

// 0x0055A413
int __cdecl _set_osfhnd(int a1, HANDLE hHandle)
{
  if ( a1 < uNumber && *(_DWORD *)(*(&g_nUIState + (a1 >> 5)) + 8 * (a1 & 0x1F)) == -1 )
  {
    if ( dword_60ACA4 == 1 )
    {
      if ( a1 )
      {
        if ( a1 == 1 )
        {
          SetStdHandle(0xFFFFFFF5, hHandle);
        }
        else if ( a1 == 2 )
        {
          SetStdHandle(0xFFFFFFF4, hHandle);
        }
      }
      else
      {
        SetStdHandle(0xFFFFFFF6, hHandle);
      }
    }
    *(_DWORD *)(*(&g_nUIState + (a1 >> 5)) + 8 * (a1 & 0x1F)) = hHandle;
    return 0;
  }
  else
  {
    g_PlayerData_340 = 0;
    g_PlayerData_33C = 9;
    return -1;
  }
}

// 0x0055A48A
int __cdecl _free_osfhnd(int a1)
{
  int v1; // eax

  if ( a1 >= uNumber
    || (v1 = 8 * (a1 & 0x1F) + *(&g_nUIState + (a1 >> 5)), (*(_BYTE *)(v1 + 4) & 1) == 0)
    || *(_DWORD *)v1 == -1 )
  {
    g_PlayerData_340 = 0;
    g_PlayerData_33C = 9;
    return -1;
  }
  else
  {
    if ( dword_60ACA4 == 1 )
    {
      if ( a1 )
      {
        if ( a1 == 1 )
        {
          SetStdHandle(0xFFFFFFF5, 0);
        }
        else if ( a1 == 2 )
        {
          SetStdHandle(0xFFFFFFF4, 0);
        }
      }
      else
      {
        SetStdHandle(0xFFFFFFF6, 0);
      }
    }
    *(_DWORD *)(*(&g_nUIState + (a1 >> 5)) + 8 * (a1 & 0x1F)) = -1;
    return 0;
  }
}

// 0x0055A504
intptr_t __cdecl _get_osfhandle(int FileHandle)
{
  int v1; // eax

  if ( FileHandle < uNumber )
  {
    v1 = *(&g_nUIState + (FileHandle >> 5)) + 8 * (FileHandle & 0x1F);
    if ( (*(_BYTE *)(v1 + 4) & 1) != 0 )
      return *(_DWORD *)v1;
  }
  g_PlayerData_340 = 0;
  g_PlayerData_33C = 9;
  return -1;
}

// 0x0055A541
int __cdecl _chsize(int FileHandle, int Size)
{
  int v3; // esi
  int v4; // eax
  int v5; // edi
  unsigned int v6; // eax
  int v7; // eax
  void *osfhandle; // eax
  BOOL v9; // eax
  _BYTE Buf[4096]; // [esp+8h] [ebp-1000h] BYREF
  int FileHandlea; // [esp+1010h] [ebp+8h]
  int Offset; // [esp+1014h] [ebp+Ch]

  v3 = 0;
  if ( FileHandle >= uNumber || (*(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + 8 * (FileHandle & 0x1F) + 4) & 1) == 0 )
  {
    g_PlayerData_33C = 9;
    return -1;
  }
  FileHandlea = _lseek(FileHandle, 0, 1);
  if ( FileHandlea == -1 )
    return -1;
  v4 = _lseek(FileHandle, 0, 2);
  if ( v4 == -1 )
    return -1;
  v5 = Size - v4;
  if ( Size - v4 <= 0 )
  {
    if ( Size - v4 < 0 )
    {
      _lseek(FileHandle, Size, 0);
      osfhandle = (void *)_get_osfhandle(FileHandle);
      v9 = SetEndOfFile(osfhandle);
      v3 = v9 - 1;
      if ( !v9 )
      {
        g_PlayerData_33C = 13;
        g_PlayerData_340 = GetLastError();
      }
    }
  }
  else
  {
    memset(Buf, 0, sizeof(Buf));
    Offset = _setmode(FileHandle, 0x8000);
    while ( 1 )
    {
      v6 = 4096;
      if ( v5 < 4096 )
        v6 = v5;
      v7 = _write(FileHandle, Buf, v6);
      if ( v7 == -1 )
        break;
      v5 -= v7;
      if ( v5 <= 0 )
        goto LABEL_15;
    }
    if ( g_PlayerData_340 == 5 )
      g_PlayerData_33C = 13;
    v3 = -1;
LABEL_15:
    _setmode(FileHandle, Offset);
  }
  _lseek(FileHandle, FileHandlea, 0);
  return v3;
}

// 0x0055A687
LONG __cdecl _XcptFilter(int a1, struct _EXCEPTION_POINTERS *ExceptionInfo)
{
  int *v2; // eax
  void (__cdecl *v3)(int); // ebx
  int v5; // ecx
  int v6; // edx
  _DWORD *v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // [esp+Ch] [ebp+8h]

  v2 = xcptlookup(a1);
  if ( !v2 )
    return UnhandledExceptionFilter(ExceptionInfo);
  v3 = (void (__cdecl *)(int))v2[2];
  if ( !v3 )
    return UnhandledExceptionFilter(ExceptionInfo);
  if ( v3 == (void (__cdecl *)(int))5 )
  {
    v2[2] = 0;
    return 1;
  }
  else
  {
    if ( v3 != (void (__cdecl *)(int))1 )
    {
      v10 = dword_18953EC;
      dword_18953EC = (int)ExceptionInfo;
      v5 = v2[1];
      if ( v5 == 8 )
      {
        if ( dword_60B528 < dword_60B528 + dword_60B52C )
        {
          v6 = dword_60B52C;
          v7 = (_DWORD *)(12 * dword_60B528 + 6337720);
          do
          {
            *v7 = 0;
            v7 += 3;
            --v6;
          }
          while ( v6 );
        }
        v8 = *v2;
        v9 = g_nFrameCount;
        switch ( v8 )
        {
          case -1073741682:
            g_nFrameCount = 131;
            break;
          case -1073741680:
            g_nFrameCount = 129;
            break;
          case -1073741679:
            g_nFrameCount = 132;
            break;
          case -1073741677:
            g_nFrameCount = 133;
            break;
          case -1073741683:
            g_nFrameCount = 130;
            break;
          case -1073741681:
            g_nFrameCount = 134;
            break;
          case -1073741678:
            g_nFrameCount = 138;
            break;
        }
        v3(8);
        g_nFrameCount = v9;
      }
      else
      {
        v2[2] = 0;
        v3(v5);
      }
      dword_18953EC = v10;
    }
    return -1;
  }
}

// 0x0055A7C8
int *__cdecl xcptlookup(int a1)
{
  int *result; // eax

  result = &dword_60B4B0;
  if ( dword_60B4B0 != a1 )
  {
    do
      result += 3;
    while ( (unsigned int)result < 12 * dword_60B530 + 6337712 && *result != a1 );
  }
  if ( (unsigned int)result >= 12 * dword_60B530 + 6337712 || *result != a1 )
    return 0;
  return result;
}

// 0x0055A80B
_BYTE *_wincmdln()
{
  _BYTE *v0; // esi
  unsigned __int8 v1; // al

  if ( !dword_1896CE8 )
    __initmbctable();
  v0 = (_BYTE *)dword_1896D10;
  if ( *(_BYTE *)dword_1896D10 != 34 )
  {
    if ( *(_BYTE *)dword_1896D10 > 0x20u )
    {
      do
        ++v0;
      while ( *v0 > 0x20u );
    }
    goto LABEL_12;
  }
  while ( 1 )
  {
    v1 = *++v0;
    if ( v1 == 34 || !v1 )
      break;
    if ( _ismbblead(v1) )
      ++v0;
  }
  if ( *v0 != 34 )
    goto LABEL_12;
  do
  {
    ++v0;
LABEL_12:
    ;
  }
  while ( *v0 && *v0 <= 0x20u );
  return v0;
}

// 0x0055A863
void _setenvp()
{
  char *v0; // esi
  int v1; // edi
  char **v2; // esi
  const char *i; // edi
  size_t v4; // eax
  size_t v5; // ebp
  char *v6; // eax

  if ( !dword_1896CE8 )
    __initmbctable();
  v0 = Str;
  v1 = 0;
  while ( *v0 )
  {
    if ( *v0 != 61 )
      ++v1;
    v0 += strlen(v0) + 1;
  }
  v2 = (char **)malloc(4 * v1 + 4);
  dword_1895364 = (int)v2;
  if ( !v2 )
    _amsg_exit(9u);
  for ( i = Str; *i; i += v5 )
  {
    v4 = strlen(i);
    v5 = v4 + 1;
    if ( *i != 61 )
    {
      v6 = (char *)malloc(v4 + 1);
      *v2 = v6;
      if ( !v6 )
        _amsg_exit(9u);
      strcpy(*v2++, i);
    }
  }
  free(Str);
  Str = 0;
  *v2 = 0;
  dword_1896CE4 = 1;
}

// 0x0055A91C
int _setargv()
{
  unsigned __int8 *v0; // edi
  unsigned __int8 **v1; // esi
  int v3; // [esp+Ch] [ebp-8h] BYREF
  int v4; // [esp+10h] [ebp-4h] BYREF

  if ( !dword_1896CE8 )
    __initmbctable();
  GetModuleFileNameA(0, byte_18953F0, 0x104u);
  dword_1895374 = (int)byte_18953F0;
  v0 = (unsigned __int8 *)byte_18953F0;
  if ( *(_BYTE *)dword_1896D10 )
    v0 = (unsigned __int8 *)dword_1896D10;
  parse_cmdline(v0, 0, 0, &v4, &v3);
  v1 = (unsigned __int8 **)malloc(v3 + 4 * v4);
  if ( !v1 )
    _amsg_exit(8u);
  parse_cmdline(v0, v1, (unsigned __int8 *)&v1[v4], &v4, &v3);
  dword_189535C = (int)v1;
  dword_1895358 = v4 - 1;
  return v4 - 1;
}

// 0x0055A9B5
_DWORD *__cdecl parse_cmdline(unsigned __int8 *a1, unsigned __int8 **a2, unsigned __int8 *a3, _DWORD *a4, _DWORD *a5)
{
  unsigned __int8 *v6; // esi
  unsigned __int8 **v7; // edi
  unsigned __int8 *v8; // eax
  unsigned __int8 v9; // dl
  unsigned __int8 v10; // dl
  unsigned int v11; // ebx
  unsigned int v12; // edx
  unsigned int v13; // ebx
  unsigned int v14; // ebx
  unsigned __int8 v15; // dl
  int v17; // [esp+14h] [ebp+8h]
  BOOL v18; // [esp+24h] [ebp+18h]

  *a5 = 0;
  v6 = a3;
  v7 = a2;
  *a4 = 1;
  v8 = a1;
  if ( a2 )
  {
    *a2 = a3;
    v7 = ++a2;
  }
  if ( *a1 == 34 )
  {
    while ( 1 )
    {
      v9 = *++v8;
      if ( v9 == 34 || !v9 )
        break;
      if ( (*(&g_bQuestActive + v9) & 4) != 0 )
      {
        ++*a5;
        if ( v6 )
          *v6++ = *v8++;
      }
      ++*a5;
      if ( v6 )
        *v6++ = *v8;
    }
    ++*a5;
    if ( v6 )
      *v6++ = 0;
    if ( *v8 == 34 )
      ++v8;
  }
  else
  {
    do
    {
      ++*a5;
      if ( v6 )
        *v6++ = *v8;
      v10 = *v8++;
      if ( (*(&g_bQuestActive + v10) & 4) != 0 )
      {
        ++*a5;
        if ( v6 )
          *v6++ = *v8;
        ++v8;
      }
      if ( v10 == 32 )
        break;
      if ( !v10 )
      {
        --v8;
        goto LABEL_28;
      }
    }
    while ( v10 != 9 );
    if ( v6 )
      *(v6 - 1) = 0;
  }
LABEL_28:
  v18 = 0;
  while ( *v8 )
  {
    while ( *v8 == 32 || *v8 == 9 )
      ++v8;
    if ( !*v8 )
      break;
    if ( v7 )
    {
      *v7++ = v6;
      a2 = v7;
    }
    ++*a4;
    while ( 1 )
    {
      v17 = 1;
      v11 = 0;
      while ( *v8 == 92 )
      {
        ++v8;
        ++v11;
      }
      if ( *v8 == 34 )
      {
        if ( (v11 & 1) == 0 )
        {
          if ( v18 && v8[1] == 34 )
            ++v8;
          else
            v17 = 0;
          v7 = a2;
          v18 = !v18;
        }
        v11 >>= 1;
      }
      v12 = v11;
      v13 = v11 - 1;
      if ( v12 )
      {
        v14 = v13 + 1;
        do
        {
          if ( v6 )
            *v6++ = 92;
          ++*a5;
          --v14;
        }
        while ( v14 );
      }
      v15 = *v8;
      if ( !*v8 || !v18 && (v15 == 32 || v15 == 9) )
        break;
      if ( v17 )
      {
        if ( v6 )
        {
          if ( (*(&g_bQuestActive + v15) & 4) != 0 )
          {
            *v6++ = v15;
            ++v8;
            ++*a5;
          }
          *v6++ = *v8;
        }
        else if ( (*(&g_bQuestActive + v15) & 4) != 0 )
        {
          ++v8;
          ++*a5;
        }
        ++*a5;
      }
      ++v8;
    }
    if ( v6 )
      *v6++ = 0;
    ++*a5;
  }
  if ( v7 )
    *v7 = 0;
  ++*a4;
  return a4;
}

// 0x0055AB69
CHAR *__crtGetEnvironmentStringsA()
{
  CHAR *v0; // ebx
  WCHAR *EnvironmentStringsW; // esi
  LPCH EnvironmentStrings; // edi
  WCHAR *i; // eax
  size_t v4; // eax
  int v5; // ebp
  CHAR *v6; // eax
  LPCH j; // eax
  size_t v9; // ebp
  void *v10; // eax
  void *v11; // esi
  CHAR *Block; // [esp+10h] [ebp-8h]
  int cchWideChar; // [esp+14h] [ebp-4h]

  v0 = 0;
  EnvironmentStringsW = 0;
  EnvironmentStrings = 0;
  if ( dword_18954F4 )
  {
    if ( dword_18954F4 == 1 )
      goto LABEL_7;
    if ( dword_18954F4 != 2 )
      return 0;
  }
  else
  {
    EnvironmentStringsW = GetEnvironmentStringsW();
    if ( EnvironmentStringsW )
    {
      dword_18954F4 = 1;
LABEL_7:
      if ( EnvironmentStringsW || (EnvironmentStringsW = GetEnvironmentStringsW()) != 0 )
      {
        for ( i = EnvironmentStringsW; *i; ++i )
        {
          do
            ++i;
          while ( *i );
        }
        cchWideChar = i - EnvironmentStringsW + 1;
        v4 = WideCharToMultiByte(0, 0, EnvironmentStringsW, cchWideChar, 0, 0, 0, 0);
        v5 = v4;
        if ( v4 )
        {
          v6 = (CHAR *)malloc(v4);
          Block = v6;
          if ( v6 )
          {
            if ( !WideCharToMultiByte(0, 0, EnvironmentStringsW, cchWideChar, v6, v5, 0, 0) )
            {
              free(Block);
              Block = 0;
            }
            v0 = Block;
          }
        }
        FreeEnvironmentStringsW(EnvironmentStringsW);
        return v0;
      }
      return 0;
    }
    EnvironmentStrings = GetEnvironmentStrings();
    if ( !EnvironmentStrings )
      return 0;
    dword_18954F4 = 2;
  }
  if ( !EnvironmentStrings )
  {
    EnvironmentStrings = GetEnvironmentStrings();
    if ( !EnvironmentStrings )
      return 0;
  }
  for ( j = EnvironmentStrings; *j; ++j )
  {
    do
      ++j;
    while ( *j );
  }
  v9 = j - EnvironmentStrings + 1;
  v10 = malloc(v9);
  v11 = v10;
  if ( v10 )
    memcpy_0(v10, EnvironmentStrings, v9);
  else
    v11 = 0;
  FreeEnvironmentStringsA(EnvironmentStrings);
  return (CHAR *)v11;
}

// 0x0055AC9B
int *_FF_MSGBANNER()
{
  int *result; // eax

  result = (int *)dword_1895320;
  if ( dword_1895320 == 1 || !dword_1895320 && dword_60ACA4 == 1 )
  {
    _NMSG_WRITE(0xFCu);
    if ( dword_18954F8 )
      dword_18954F8();
    return _NMSG_WRITE(0xFFu);
  }
  return result;
}

// 0x0055ACD4
int *__cdecl _NMSG_WRITE(DWORD NumberOfBytesWritten)
{
  int v1; // ecx
  int *result; // eax
  int v3; // esi
  char *v4; // edi
  const char **v5; // esi
  HANDLE StdHandle; // eax
  const char *v7; // [esp-14h] [ebp-1B8h]
  DWORD v8; // [esp-10h] [ebp-1B4h]
  DWORD *p_NumberOfBytesWritten; // [esp-Ch] [ebp-1B0h]
  int v10; // [esp-8h] [ebp-1ACh]
  CHAR Filename[260]; // [esp+0h] [ebp-1A4h] BYREF
  char Destination[160]; // [esp+104h] [ebp-A0h] BYREF
  int savedregs; // [esp+1A4h] [ebp+0h] BYREF

  v1 = 0;
  result = dword_60B538;
  do
  {
    if ( NumberOfBytesWritten == *result )
      break;
    result += 2;
    ++v1;
  }
  while ( (int)result < (int)&dbl_60B5C8 );
  v3 = 2 * v1;
  if ( NumberOfBytesWritten == dword_60B538[2 * v1] )
  {
    result = (int *)dword_1895320;
    if ( dword_1895320 == 1 || !dword_1895320 && dword_60ACA4 == 1 )
    {
      v5 = (const char **)&(&off_60B53C)[v3];
      v10 = 0;
      p_NumberOfBytesWritten = &NumberOfBytesWritten;
      v8 = strlen(*v5);
      v7 = *v5;
      StdHandle = GetStdHandle(0xFFFFFFF4);
      return (int *)WriteFile(StdHandle, v7, v8, &NumberOfBytesWritten, 0);
    }
    else if ( NumberOfBytesWritten != 252 )
    {
      if ( !GetModuleFileNameA(0, Filename, 0x104u) )
        strcpy(Filename, "<program name unknown>");
      v4 = Filename;
      if ( strlen(Filename) + 1 > 0x3C )
      {
        v4 = (char *)&savedregs + strlen(Filename) - 479;
        strncpy(v4, "...", 3u);
      }
      strcpy(Destination, "Runtime Error!\n\nProgram: ");
      strcat(Destination, v4);
      strcat(Destination, "\n\n");
      strcat(Destination, (&off_60B53C)[v3]);
      return (int *)__crtMessageBoxA(Destination, "Microsoft Visual C++ Runtime Library", 0x12010u);
    }
  }
  return result;
}

// 0x0055AE27
double __cdecl _set_exp(double a1, __int16 a2)
{
  double v3; // [esp+0h] [ebp-8h]

  v3 = a1;
  HIWORD(v3) = HIWORD(a1) & 0x800F | (16 * (a2 + 1022));
  return v3;
}

// 0x0055AE50
int __cdecl _sptype(int a1, int a2)
{
  if ( a2 == 2146435072 )
  {
    if ( !a1 )
      return 1;
  }
  else if ( a2 == -1048576 && !a1 )
  {
    return 2;
  }
  if ( (HIWORD(a2) & 0x7FF8) == 0x7FF8 )
    return 3;
  if ( (HIWORD(a2) & 0x7FF8) == 0x7FF0 && ((a2 & 0x7FFFF) != 0 || a1) )
    return 4;
  return 0;
}

// 0x0055AEAA
// local variable allocation has failed, the output may be wrong!
double __cdecl _decomp(double a1, int *a2)
{
  int v2; // esi
  BOOL v3; // eax
  double v5; // [esp+10h] [ebp-8h]

  if ( a1 == 0.0 )
  {
    v2 = 0;
    v5 = 0.0;
  }
  else if ( (HIWORD(a1) & 0x7FF0) == 0 && ((HIDWORD(a1) & 0xFFFFF) != 0 || LODWORD(a1)) )
  {
    v2 = -1021;
    v3 = a1 < 0.0;
    while ( (BYTE6(a1) & 0x10) == 0 )
    {
      HIDWORD(a1) *= 2;
      if ( SBYTE3(a1) < 0 )
        HIDWORD(a1) |= 1u;
      LODWORD(a1) *= 2;
      --v2;
    }
    HIWORD(a1) &= ~0x10u;
    if ( v3 )
      HIBYTE(a1) |= 0x80u;
    v5 = _set_exp(a1, 0);
  }
  else
  {
    v5 = _set_exp(a1, 0);
    v2 = ((*(_DWORD *)((char *)&a1 + 6) >> 4) & 0x7FF) - 1022;
  }
  *a2 = v2;
  return v5;
}

// 0x0055AF6B
int __usercall _raise_exc@<eax>(
        __int16 a1@<fpstat>,
        ULONG_PTR Arguments,
        unsigned int *a3,
        DWORD dwExceptionCode,
        __int16 a5,
        double *a6,
        double *a7)
{
  char v7; // cl
  unsigned int *v8; // esi
  char v9; // al
  int v10; // eax
  unsigned int *v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  unsigned int *v14; // eax
  unsigned int v15; // ecx
  double *v16; // edi
  __int16 v17; // fps
  int result; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  unsigned int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  unsigned int v25; // ecx

  *(_DWORD *)(Arguments + 4) = 0;
  *(_DWORD *)(Arguments + 8) = 0;
  *(_DWORD *)(Arguments + 12) = 0;
  v7 = dwExceptionCode;
  if ( (dwExceptionCode & 0x10) != 0 )
  {
    dwExceptionCode = -1073741681;
    *(_DWORD *)(Arguments + 4) |= 1u;
  }
  if ( (v7 & 2) != 0 )
  {
    dwExceptionCode = -1073741677;
    *(_DWORD *)(Arguments + 4) |= 2u;
  }
  if ( (v7 & 1) != 0 )
  {
    dwExceptionCode = -1073741679;
    *(_DWORD *)(Arguments + 4) |= 4u;
  }
  if ( (v7 & 4) != 0 )
  {
    dwExceptionCode = -1073741682;
    *(_DWORD *)(Arguments + 4) |= 8u;
  }
  if ( (v7 & 8) != 0 )
  {
    dwExceptionCode = -1073741680;
    *(_DWORD *)(Arguments + 4) |= 0x10u;
  }
  v8 = a3;
  *(_DWORD *)(Arguments + 8) = *(_DWORD *)(Arguments + 8) & 0xFFFFFFEF | (16 * ((*a3 & 1) == 0));
  *(_DWORD *)(Arguments + 8) = *(_DWORD *)(Arguments + 8) & 0xFFFFFFF7 | (2 * (~(unsigned __int8)*v8 & 4));
  *(_DWORD *)(Arguments + 8) = *(_DWORD *)(Arguments + 8) & 0xFFFFFFFB | (~*v8 >> 1) & 4;
  *(_DWORD *)(Arguments + 8) = *(_DWORD *)(Arguments + 8) & 0xFFFFFFFD | (~*v8 >> 3) & 2;
  *(_DWORD *)(Arguments + 8) = *(_DWORD *)(Arguments + 8) & 0xFFFFFFFE | (~*v8 >> 5) & 1;
  v9 = _statfp(a1);
  if ( (v9 & 1) != 0 )
    *(_DWORD *)(Arguments + 12) |= 0x10u;
  if ( (v9 & 4) != 0 )
    *(_DWORD *)(Arguments + 12) |= 8u;
  if ( (v9 & 8) != 0 )
    *(_DWORD *)(Arguments + 12) |= 4u;
  if ( (v9 & 0x10) != 0 )
    *(_DWORD *)(Arguments + 12) |= 2u;
  if ( (v9 & 0x20) != 0 )
    *(_DWORD *)(Arguments + 12) |= 1u;
  v10 = *v8 & 0xC00;
  switch ( v10 )
  {
    case 0:
      *(_DWORD *)Arguments &= 0xFFFFFFFC;
      break;
    case 1024:
      v11 = (unsigned int *)Arguments;
      v12 = *(_DWORD *)Arguments & 0xFFFFFFFC | 1;
      goto LABEL_28;
    case 2048:
      v11 = (unsigned int *)Arguments;
      v12 = *(_DWORD *)Arguments & 0xFFFFFFFC | 2;
LABEL_28:
      *v11 = v12;
      break;
    case 3072:
      *(_DWORD *)Arguments |= 3u;
      break;
  }
  v13 = *v8 & 0x300;
  switch ( v13 )
  {
    case 0:
      v14 = (unsigned int *)Arguments;
      v15 = *(_DWORD *)Arguments & 0xFFFFFFE3 | 8;
      goto LABEL_36;
    case 512:
      v14 = (unsigned int *)Arguments;
      v15 = *(_DWORD *)Arguments & 0xFFFFFFE3 | 4;
LABEL_36:
      *v14 = v15;
      break;
    case 768:
      *(_DWORD *)Arguments &= 0xFFFFFFE3;
      break;
  }
  *(_DWORD *)Arguments = *(_DWORD *)Arguments & 0xFFFE001F | (32 * (a5 & 0xFFF));
  *(_DWORD *)(Arguments + 32) |= 1u;
  *(_DWORD *)(Arguments + 32) = *(_DWORD *)(Arguments + 32) & 0xFFFFFFE1 | 2;
  *(double *)(Arguments + 16) = *a6;
  *(_DWORD *)(Arguments + 80) |= 1u;
  v16 = a7;
  *(_DWORD *)(Arguments + 80) = *(_DWORD *)(Arguments + 80) & 0xFFFFFFE1 | 2;
  *(double *)(Arguments + 64) = *v16;
  _clrfp(v17);
  RaiseException(dwExceptionCode, 0, 1u, &Arguments);
  result = Arguments;
  if ( (*(_BYTE *)(Arguments + 8) & 0x10) != 0 )
    *v8 &= ~1u;
  if ( (*(_BYTE *)(result + 8) & 8) != 0 )
    *v8 &= ~4u;
  if ( (*(_BYTE *)(result + 8) & 4) != 0 )
    *v8 &= ~8u;
  if ( (*(_BYTE *)(result + 8) & 2) != 0 )
    *v8 &= ~0x10u;
  if ( (*(_BYTE *)(result + 8) & 1) != 0 )
    *v8 &= ~0x20u;
  v19 = *(_DWORD *)result & 3;
  if ( !v19 )
  {
    *v8 &= 0xFFFFF3FF;
    goto LABEL_56;
  }
  v20 = v19 - 1;
  if ( !v20 )
  {
    v22 = *v8;
    BYTE1(v22) = BYTE1(*v8) & 0xF3 | 4;
    goto LABEL_54;
  }
  v21 = v20 - 1;
  if ( !v21 )
  {
    v22 = *v8;
    BYTE1(v22) = BYTE1(*v8) & 0xF3 | 8;
LABEL_54:
    *v8 = v22;
    goto LABEL_56;
  }
  if ( v21 == 1 )
    *((_BYTE *)v8 + 1) |= 0xCu;
LABEL_56:
  v23 = (*(_DWORD *)result >> 2) & 7;
  if ( !v23 )
  {
    v25 = *v8 & 0xFFFFF3FF;
    BYTE1(v25) |= 3u;
    goto LABEL_62;
  }
  v24 = v23 - 1;
  if ( !v24 )
  {
    v25 = *v8 & 0xFFFFF3FF;
    BYTE1(v25) |= 2u;
LABEL_62:
    *v8 = v25;
    goto LABEL_63;
  }
  if ( v24 == 1 )
    *v8 &= 0xFFFFF3FF;
LABEL_63:
  *v16 = *(double *)(result + 64);
  return result;
}

// 0x0055B21E
BOOL __cdecl _handle_exc(char a1, double *a2, __int16 a3)
{
  int v3; // edi
  int v4; // ecx
  double *v5; // ecx
  double v7; // st7
  char v8; // c0
  char v9; // c3
  char v11; // c0
  char v12; // c3
  BOOL v13; // esi
  int v14; // ecx
  BOOL v15; // edx
  __int16 v16; // ax
  int v17; // eax
  double v19; // [esp+18h] [ebp-Ch]
  double v20; // [esp+18h] [ebp-Ch]
  int v21; // [esp+20h] [ebp-4h] BYREF

  v3 = a1 & 0x1F;
  if ( (a1 & 8) != 0 && (a3 & 1) != 0 )
  {
    _set_statfp();
    v3 = a1 & 0x17;
    goto LABEL_46;
  }
  if ( (a1 & 4) != 0 && (a3 & 4) != 0 )
  {
    _set_statfp();
    v3 = a1 & 0x1B;
    goto LABEL_46;
  }
  if ( (a1 & 1) != 0 && (a3 & 8) != 0 )
  {
    _set_statfp();
    v4 = a3 & 0xC00;
    if ( (a3 & 0xC00) != 0 )
    {
      switch ( v4 )
      {
        case 1024:
          v5 = a2;
          if ( *a2 <= 0.0 )
            v7 = -dbl_60B5C8;
          else
            v7 = dbl_60B5D8;
          break;
        case 2048:
          v5 = a2;
          if ( *a2 <= 0.0 )
            v7 = -dbl_60B5D8;
          else
            v7 = dbl_60B5C8;
          break;
        case 3072:
          v5 = a2;
          v7 = dbl_60B5D8;
          if ( v8 != 0 || v9 != 0 )
            v7 = -dbl_60B5D8;
          break;
        default:
LABEL_25:
          v3 = a1 & 0x1E;
          goto LABEL_46;
      }
    }
    else
    {
      v5 = a2;
      v7 = dbl_60B5C8;
      if ( v11 != 0 || v12 != 0 )
        v7 = -dbl_60B5C8;
    }
    *v5 = v7;
    goto LABEL_25;
  }
  if ( (a1 & 2) != 0 && (a3 & 0x10) != 0 )
  {
    v13 = (a1 & 0x10) != 0;
    v19 = *a2;
    if ( v19 == 0.0 )
    {
      v13 = 1;
    }
    else
    {
      v20 = _decomp(v19, &v21);
      v14 = v21 - 1536;
      if ( v21 - 1536 >= -1074 )
      {
        v15 = v20 < 0.0;
        v16 = BYTE6(v20) & 0xF;
        LOBYTE(v16) = v16 | 0x10;
        HIWORD(v20) = v16;
        if ( v14 < -1021 )
        {
          v17 = -1021 - v14;
          do
          {
            if ( (LOBYTE(v20) & 1) != 0 && !v13 )
              v13 = 1;
            LODWORD(v20) >>= 1;
            if ( (BYTE4(v20) & 1) != 0 )
              BYTE3(v20) |= 0x80u;
            HIDWORD(v20) >>= 1;
            --v17;
          }
          while ( v17 );
        }
        if ( v15 )
          v20 = -v20;
      }
      else
      {
        v13 = 1;
        v20 = 0.0;
      }
      *a2 = v20;
    }
    if ( v13 )
      _set_statfp();
    v3 = a1 & 0x1D;
  }
LABEL_46:
  if ( (a1 & 0x10) != 0 && (a3 & 0x20) != 0 )
  {
    _set_statfp();
    v3 &= ~0x10u;
  }
  return v3 == 0;
}

// 0x0055B435
errno_t __cdecl _set_errno(int Value)
{
  errno_t result; // eax

  result = Value;
  if ( Value == 1 )
  {
    g_PlayerData_33C = 33;
  }
  else if ( Value > 1 && Value <= 3 )
  {
    g_PlayerData_33C = 34;
  }
  return result;
}

// 0x0055B45B
int __usercall _statfp@<eax>(__int16 a1@<fpstat>)
{
  return a1;
}

// 0x0055B469
int __usercall _clrfp@<eax>(__int16 a1@<fpstat>)
{
  __asm { fnclex }
  return a1;
}

// 0x0055B478
int __fastcall _ctrlfp(__int16 a1)
{
  return a1;
}

// 0x0055B49B
void _set_statfp()
{
  ;
}

// 0x0055B4F1
unsigned int __cdecl _control87(unsigned int NewValue, unsigned int Mask)
{
  int v2; // eax
  unsigned int v3; // esi
  __int16 v5; // [esp+4h] [ebp-4h]

  LOBYTE(v2) = _abstract_cw(v5);
  v3 = Mask & NewValue | ~Mask & v2;
  _hw_cw(v3);
  return v3;
}

// 0x0055B526
unsigned int __cdecl _controlfp(unsigned int NewValue, unsigned int Mask)
{
  return _control87(NewValue, Mask & 0xFFF7FFFF);
}

// 0x0055B53C
char __cdecl _abstract_cw(__int16 a1)
{
  char result; // al

  result = 0;
  if ( (a1 & 1) != 0 )
    result = 16;
  if ( (a1 & 4) != 0 )
    result |= 8u;
  if ( (a1 & 8) != 0 )
    result |= 4u;
  if ( (a1 & 0x10) != 0 )
    result |= 2u;
  if ( (a1 & 0x20) != 0 )
    return result | 1;
  return result;
}

// 0x0055B5CE
char __cdecl _hw_cw(int a1)
{
  char result; // al

  result = (a1 & 0x10) != 0;
  if ( (a1 & 8) != 0 )
    result |= 4u;
  if ( (a1 & 4) != 0 )
    result |= 8u;
  if ( (a1 & 2) != 0 )
    result |= 0x10u;
  if ( (a1 & 1) != 0 )
    result |= 0x20u;
  if ( (a1 & 0x80000) != 0 )
    return result | 2;
  return result;
}

// 0x0055B657
int __cdecl tolower(int C)
{
  int result; // eax
  int v2; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  CHAR DestStr[4]; // [esp+Ch] [ebp-4h] BYREF

  if ( dword_18953A8 )
  {
    v2 = C;
    if ( (C >= 256
       || ((int)cbMultiByte <= 1 ? (v3 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * C) & 1) : (v3 = _isctype(C, 1)), v3))
      && (*((char *)g_pVtbl_SceneMgr + 2 * BYTE1(v2) + 1) >= 0
        ? (LOWORD(C) = (unsigned __int8)v2, v4 = 1)
        : (LOBYTE(C) = BYTE1(v2), *(_WORD *)((char *)&C + 1) = (unsigned __int8)v2, v4 = 2),
          (v5 = __crtLCMapStringA(dword_18953A8, 0x100u, (CHAR *)&C, (_BYTE *)v4, DestStr, 3, 0, 1)) != 0) )
    {
      if ( v5 == 1 )
        return (unsigned __int8)DestStr[0];
      else
        return *(unsigned __int16 *)DestStr;
    }
    else
    {
      return v2;
    }
  }
  else
  {
    result = C;
    if ( C >= 65 && C <= 90 )
      return C + 32;
  }
  return result;
}

// 0x0055B722
int __cdecl _ZeroTail(int a1, int a2)
{
  int v2; // esi
  _DWORD *i; // eax

  if ( (~(-1 << (31 - a2 % 32)) & *(_DWORD *)(a1 + 4 * (a2 / 32))) == 0 )
  {
    v2 = a2 / 32 + 1;
    if ( v2 >= 3 )
      return 1;
    for ( i = (_DWORD *)(a1 + 4 * v2); !*i; ++i )
    {
      if ( ++v2 >= 3 )
        return 1;
    }
  }
  return 0;
}

// 0x0055B76B
int __cdecl _IncMan(int a1, int a2)
{
  int result; // eax
  int v3; // esi
  unsigned int *v4; // edi

  result = __addl(*(_DWORD *)(a1 + 4 * (a2 / 32)), 1 << (31 - a2 % 32), (unsigned int *)(a1 + 4 * (a2 / 32)));
  v3 = a2 / 32 - 1;
  if ( v3 >= 0 )
  {
    v4 = (unsigned int *)(a1 + 4 * v3);
    do
    {
      if ( !result )
        break;
      result = __addl(*v4, 1u, v4);
      --v3;
      --v4;
    }
    while ( v3 >= 0 );
  }
  return result;
}

// 0x0055B7C1
int __cdecl _RoundMan(int a1, int a2)
{
  int v2; // edi
  int v4; // edx
  _DWORD *v5; // eax
  char v6; // si
  int v8; // [esp+Ch] [ebp-8h]
  int v9; // [esp+10h] [ebp-4h]
  _DWORD *v10; // [esp+20h] [ebp+Ch]

  v2 = a2 - 1;
  v9 = 0;
  v4 = a2 % 32;
  v8 = a2 / 32;
  v5 = (_DWORD *)(a1 + 4 * (a2 / 32));
  v10 = v5;
  v6 = 31 - v4;
  if ( ((1 << (31 - v4)) & *v5) != 0 )
  {
    if ( !_ZeroTail(a1, a2 + 1) )
      v9 = _IncMan(a1, v2);
    v5 = v10;
  }
  *v5 &= -1 << v6;
  if ( v8 + 1 < 3 )
    memset((void *)(a1 + 4 * (v8 + 1)), 0, 4 * (3 - (v8 + 1)));
  return v9;
}

// 0x0055B84D
_DWORD *__cdecl _CopyMan(int a1, _DWORD *a2)
{
  _DWORD *result; // eax
  int v3; // edx

  result = a2;
  v3 = 3;
  do
  {
    *(_DWORD *)((char *)result + a1 - (_DWORD)a2) = *result;
    ++result;
    --v3;
  }
  while ( v3 );
  return result;
}

// 0x0055B868
int __cdecl _FillZeroMan(_DWORD *a1)
{
  *a1 = 0;
  a1[1] = 0;
  a1[2] = 0;
  return 0;
}

// 0x0055B874
int __cdecl _IsZeroMan(_DWORD *a1)
{
  int v2; // ecx

  v2 = 0;
  while ( !*a1 )
  {
    ++v2;
    ++a1;
    if ( v2 >= 3 )
      return 1;
  }
  return 0;
}

// 0x0055B88F
int *__cdecl _ShrMan(int *a1, int a2)
{
  int *v2; // edi
  int v3; // edx
  bool v4; // zf
  int v5; // ebx
  int i; // ecx
  int *result; // eax
  int v8; // [esp+Ch] [ebp-Ch]
  int v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]
  int v11; // [esp+24h] [ebp+Ch]

  v2 = a1;
  v10 = 3;
  v8 = a2 / 32;
  v3 = a2 % 32;
  v11 = 0;
  do
  {
    v9 = ~(-1 << v3) & *v2;
    *v2 = v11 | ((unsigned int)*v2 >> v3);
    ++v2;
    v4 = v10-- == 1;
    v11 = v9 << (32 - v3);
  }
  while ( !v4 );
  v5 = 2;
  for ( i = 2; i >= 0; --i )
  {
    if ( v5 < v8 )
    {
      result = a1;
      a1[i] = 0;
    }
    else
    {
      result = *(int **)((char *)a1 + i * 4 - 4 * v8);
      a1[i] = (int)result;
    }
    --v5;
  }
  return result;
}

// 0x0055B91C
int __cdecl _ld12cvt(unsigned __int16 *a1, unsigned int *a2, int *a3)
{
  unsigned __int16 v4; // bx
  unsigned int v5; // ecx
  int v6; // eax
  int v7; // ebx
  int v8; // esi
  int result; // eax
  int v10; // eax
  int v11; // esi
  int v12; // esi
  int v13; // edi
  unsigned int v14; // esi
  unsigned int v15; // edx
  int v16; // [esp-8h] [ebp-2Ch]
  int v17; // [esp-4h] [ebp-28h]
  int v18; // [esp-4h] [ebp-28h]
  _DWORD v19[3]; // [esp+Ch] [ebp-18h] BYREF
  int v20; // [esp+18h] [ebp-Ch] BYREF
  unsigned int v21; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h]
  int v23; // [esp+2Ch] [ebp+8h]

  v4 = a1[5];
  v23 = v4 & 0x8000;
  v20 = *(_DWORD *)(a1 + 3);
  v5 = *(_DWORD *)(a1 + 1);
  v6 = *a1;
  v7 = (v4 & 0x7FFF) - 0x3FFF;
  v21 = v5;
  v22 = v6 << 16;
  if ( v7 != -16383 )
  {
    _CopyMan((int)v19, &v20);
    if ( _RoundMan((int)&v20, a3[2]) )
      ++v7;
    v10 = a3[1];
    if ( v7 >= v10 - a3[2] )
    {
      if ( v7 > v10 )
      {
        if ( v7 >= *a3 )
        {
          _FillZeroMan(&v20);
          v16 = a3[3];
          HIBYTE(v20) |= 0x80u;
          _ShrMan(&v20, v16);
          v8 = *a3 + a3[5];
          v17 = 1;
          goto LABEL_5;
        }
        v18 = a3[3];
        v12 = a3[5];
        HIBYTE(v20) &= ~0x80u;
        v8 = v7 + v12;
        _ShrMan(&v20, v18);
        goto LABEL_16;
      }
      v11 = v10 - v7;
      _CopyMan((int)&v20, v19);
      _ShrMan(&v20, v11);
      _RoundMan((int)&v20, a3[2]);
      _ShrMan(&v20, a3[3] + 1);
    }
    else
    {
      _FillZeroMan(&v20);
    }
    v8 = 0;
    goto LABEL_4;
  }
  v8 = 0;
  if ( !_IsZeroMan(&v20) )
  {
    _FillZeroMan(&v20);
LABEL_4:
    v17 = 2;
LABEL_5:
    result = v17;
    goto LABEL_17;
  }
LABEL_16:
  result = 0;
LABEL_17:
  v13 = a3[4];
  v14 = v20 | (v23 != 0 ? 0x80000000 : 0) | (v8 << (31 - *((_BYTE *)a3 + 12)));
  if ( v13 == 64 )
  {
    v15 = v21;
    a2[1] = v14;
    *a2 = v15;
  }
  else if ( v13 == 32 )
  {
    *a2 = v14;
  }
  return result;
}

// 0x0055BB0E
char *__cdecl _fptostr(char *a1, char *a2, int a3)
{
  int v3; // edx
  char *v4; // ebx
  char *v6; // ecx
  const char *v7; // edi
  char *result; // eax
  char v9; // dl
  size_t v10; // eax
  char *v11; // [esp+14h] [ebp+8h]

  v3 = a3;
  v4 = a2;
  v6 = *(char **)(a3 + 12);
  v7 = a1 + 1;
  *a1 = 48;
  result = a1 + 1;
  if ( (int)a2 > 0 )
  {
    v11 = a2;
    v4 = 0;
    do
    {
      v9 = *v6;
      if ( *v6 )
        ++v6;
      else
        v9 = 48;
      *result++ = v9;
      --v11;
    }
    while ( v11 );
    v3 = a3;
  }
  *result = 0;
  if ( (int)v4 >= 0 && *v6 >= 53 )
  {
    while ( *--result == 57 )
      *result = 48;
    ++*result;
  }
  if ( *a1 == 49 )
  {
    ++*(_DWORD *)(v3 + 4);
  }
  else
  {
    v10 = strlen(v7);
    return (char *)memcpy(a1, v7, v10 + 1);
  }
  return result;
}

// 0x0055BB85
int *__cdecl _fltout(int a1)
{
  int v2; // [esp-10h] [ebp-24h]
  __int64 v3; // [esp+8h] [ebp-Ch] BYREF
  __int16 v4; // [esp+10h] [ebp-4h]

  __dtold((unsigned int)&v3, (int)&v3, &a1);
  LOWORD(v2) = v4;
  dword_1895528 = _I10_OUTPUT(v3, v2, 17, 0, (int)&word_1895500);
  dword_1895520 = byte_1895502;
  dword_1895524 = word_1895500;
  dword_189552C = (int)&unk_1895504;
  return &dword_1895520;
}

// 0x0055BBE9
int __usercall __dtold@<eax>(unsigned int a1@<eax>, int a2, int *a3)
{
  unsigned int v4; // ecx
  int v5; // eax
  unsigned int v6; // edx
  int v7; // eax
  __int16 v8; // di
  int result; // eax
  int v10; // ecx
  int v11; // ecx
  unsigned __int64 v12; // rcx
  unsigned int v13; // [esp+Ch] [ebp-4h]
  __int16 v14; // [esp+1Ch] [ebp+Ch]

  LOWORD(a1) = *((_WORD *)a3 + 3);
  v4 = (a1 >> 4) & 0x7FF;
  v14 = a1 & 0x8000;
  v5 = a3[1];
  v6 = *a3;
  v7 = v5 & 0xFFFFF;
  v13 = 0x80000000;
  if ( (_WORD)v4 )
  {
    if ( (unsigned __int16)v4 == 2047 )
      v8 = 0x7FFF;
    else
      v8 = v4 + 15360;
  }
  else
  {
    if ( !v7 && !v6 )
    {
      *(_DWORD *)(a2 + 4) = 0;
      *(_DWORD *)a2 = 0;
      *(_WORD *)(a2 + 8) = 0;
      return a2;
    }
    v8 = v4 + 15361;
    v13 = 0;
  }
  v10 = (v7 << 11) | (v6 >> 21);
  result = a2;
  v11 = v13 | v10;
  *(_DWORD *)(a2 + 4) = v11;
  *(_DWORD *)a2 = v6 << 11;
  while ( (v11 & 0x80000000) == 0 )
  {
    v12 = 2 * __PAIR64__(v11, *(_DWORD *)a2);
    *(_QWORD *)a2 = v12;
    --v8;
    v11 = HIDWORD(v12);
  }
  *(_WORD *)(a2 + 8) = v8 | v14;
  return result;
}

// 0x0055BC9F
void __noreturn _fptrap()
{
  _amsg_exit(2u);
}

// 0x0055BCA8
int __cdecl _getbuf(_DWORD *a1)
{
  void *v1; // eax
  int result; // eax

  ++dword_18953DC;
  v1 = malloc(0x1000u);
  a1[2] = v1;
  if ( v1 )
  {
    a1[3] |= 8u;
    a1[6] = 4096;
  }
  else
  {
    a1[3] |= 4u;
    a1[2] = a1 + 5;
    a1[6] = 2;
  }
  result = a1[2];
  a1[1] = 0;
  *a1 = result;
  return result;
}

// 0x0055BCEC
int __cdecl _isatty(int FileHandle)
{
  if ( FileHandle < uNumber )
    return *(_BYTE *)(*(&g_nUIState + (FileHandle >> 5)) + 8 * (FileHandle & 0x1F) + 4) & 0x40;
  else
    return 0;
}

// 0x0055BD12
int __cdecl wctomb(char *MbCh, wchar_t WCh)
{
  int result; // eax

  result = (int)MbCh;
  if ( MbCh )
  {
    if ( !dword_18953A8 )
    {
      if ( WCh <= 0xFFu )
      {
        *MbCh = WCh;
        return 1;
      }
      goto LABEL_7;
    }
    MbCh = 0;
    result = WideCharToMultiByte(dword_18953B8, 0x220u, &WCh, 1, (LPSTR)result, cbMultiByte, 0, (LPBOOL)&MbCh);
    if ( !result || MbCh )
    {
LABEL_7:
      g_PlayerData_33C = 42;
      return -1;
    }
  }
  return result;
}

// 0x0055BD80
unsigned int __stdcall _aulldiv(unsigned __int64 a1, __int64 a2)
{
  unsigned __int64 v3; // rtt
  unsigned int v4; // ecx
  unsigned int v5; // ebx
  unsigned __int64 v6; // rax
  char v7; // cf
  unsigned int v8; // esi
  unsigned __int64 v9; // rax

  if ( HIDWORD(a2) )
  {
    v4 = HIDWORD(a2);
    v5 = a2;
    v6 = a1;
    do
    {
      v7 = v4 & 1;
      v4 >>= 1;
      v5 = (v5 >> 1) | (v7 << 31);
      v6 >>= 1;
    }
    while ( v4 );
    v8 = v6 / v5;
    v9 = v8 * (unsigned __int64)(unsigned int)a2;
    if ( __CFADD__(HIDWORD(a2) * v8, HIDWORD(v9)) || (HIDWORD(v9) = (a2 * (unsigned __int64)v8) >> 32, v9 > a1) )
      --v8;
    return v8;
  }
  else
  {
    LODWORD(v3) = a1;
    HIDWORD(v3) = HIDWORD(a1) % (unsigned int)a2;
    return v3 / (unsigned int)a2;
  }
}

// 0x0055BDF0
unsigned __int64 __stdcall _aullrem(unsigned __int64 a1, __int64 a2)
{
  unsigned __int64 v2; // rtt
  unsigned int v4; // ecx
  unsigned int v5; // ebx
  unsigned __int64 v6; // rax
  bool v7; // cf
  int v8; // ecx
  unsigned __int64 v9; // rax

  if ( HIDWORD(a2) )
  {
    v4 = HIDWORD(a2);
    v5 = a2;
    v6 = a1;
    do
    {
      v7 = v4 & 1;
      v4 >>= 1;
      v5 = (v5 >> 1) | (v7 << 31);
      v6 >>= 1;
    }
    while ( v4 );
    v8 = HIDWORD(a2) * (v6 / v5);
    v9 = (unsigned int)a2 * (unsigned __int64)(unsigned int)(v6 / v5);
    v7 = __CFADD__(v8, HIDWORD(v9));
    HIDWORD(v9) += v8;
    if ( v7 || v9 > a1 )
      v9 -= a2;
    return a1 - v9;
  }
  else
  {
    LODWORD(v2) = a1;
    HIDWORD(v2) = HIDWORD(a1) % (unsigned int)a2;
    return v2 % (unsigned int)a2;
  }
}

// 0x0055BE65
BOOL __cdecl _ValidateRead(void *lp, UINT_PTR ucb)
{
  return !IsBadReadPtr(lp, ucb);
}

// 0x0055BE81
BOOL __cdecl _ValidateWrite(void *lp, UINT_PTR ucb)
{
  return !IsBadWritePtr(lp, ucb);
}

// 0x0055BE9D
BOOL __cdecl _ValidateExecute(FARPROC lpfn)
{
  return !IsBadCodePtr(lpfn);
}

// 0x0055BEB5
void __cdecl __noreturn abort()
{
  _NMSG_WRITE(0xAu);
  raise(22);
  _exit(3);
}

// 0x0055BECC
BOOL __cdecl __crtGetStringTypeA(
        DWORD dwInfoType,
        LPCSTR lpSrcStr,
        int cchSrc,
        LPWORD lpCharType,
        UINT CodePage,
        LCID Locale,
        int a7)
{
  int v7; // eax
  LCID v8; // eax
  int v10; // eax
  size_t v11; // edi
  int v12; // eax
  void *v13; // esp
  int v14; // eax
  WCHAR v15[8]; // [esp+0h] [ebp-34h] BYREF
  WCHAR *v16; // [esp+10h] [ebp-24h]
  int cchWideChar; // [esp+14h] [ebp-20h]
  WORD CharType; // [esp+18h] [ebp-1Ch] BYREF
  CPPEH_RECORD ms_exc; // [esp+1Ch] [ebp-18h]

  v7 = dword_1895534;
  if ( !dword_1895534 )
  {
    if ( GetStringTypeW(1u, &SrcStr, 1, &CharType) )
    {
      v7 = 1;
    }
    else
    {
      if ( !GetStringTypeA(0, 1u, unk_BFDAA4, 1, &CharType) )
        return 0;
      v7 = 2;
    }
    dword_1895534 = v7;
  }
  if ( v7 != 2 )
  {
    if ( v7 == 1 )
    {
      if ( !CodePage )
        CodePage = dword_18953B8;
      v10 = MultiByteToWideChar(CodePage, a7 != 0 ? 9 : 1, lpSrcStr, cchSrc, 0, 0);
      cchWideChar = v10;
      if ( v10 )
      {
        v11 = 2 * v10;
        v12 = 2 * v10 + 3;
        LOBYTE(v12) = v12 & 0xFC;
        v13 = alloca(v12);
        ms_exc.old_esp = (DWORD)v15;
        v16 = v15;
        memset(v15, 0, v11);
        ms_exc.registration.TryLevel = -1;
        if ( v15 )
        {
          v14 = MultiByteToWideChar(CodePage, 1u, lpSrcStr, cchSrc, v15, cchWideChar);
          if ( v14 )
            return GetStringTypeW(dwInfoType, v15, v14, lpCharType);
        }
      }
    }
    return 0;
  }
  v8 = Locale;
  if ( !Locale )
    v8 = dword_18953A8;
  return GetStringTypeA(v8, dwInfoType, lpSrcStr, cchSrc, lpCharType);
}

// 0x0055C015
int __cdecl _87except(int a1, int a2, int a3)
{
  __int16 v3; // cx
  bool v4; // zf
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  DWORD v11; // ebx
  __int16 v12; // fps
  int result; // eax
  int v17; // [esp-4h] [ebp-68h]
  ULONG_PTR Arguments[10]; // [esp+Ch] [ebp-58h] BYREF
  double v19; // [esp+34h] [ebp-30h]
  unsigned int v20; // [esp+44h] [ebp-20h]

  v3 = *(_WORD *)a3;
  v5 = *(_DWORD *)a2 - 1;
  v4 = *(_DWORD *)a2 == 1;
  a3 = *(unsigned __int16 *)a3;
  if ( v4 )
    goto LABEL_13;
  v6 = v5 - 1;
  if ( !v6 )
  {
    v17 = 4;
    goto LABEL_14;
  }
  v7 = v6 - 1;
  if ( !v7 )
  {
    v17 = 17;
    goto LABEL_14;
  }
  v8 = v7 - 1;
  if ( !v8 )
  {
    v17 = 18;
    goto LABEL_14;
  }
  v9 = v8 - 1;
  if ( !v9 )
  {
LABEL_13:
    v17 = 8;
LABEL_14:
    v11 = v17;
    if ( !_handle_exc(v17, (double *)(a2 + 24), v3) )
    {
      if ( a1 == 16 || a1 == 22 || a1 == 29 )
      {
        v19 = *(double *)(a2 + 16);
        v20 = v20 & 0xFFFFFFE0 | 3;
      }
      else
      {
        v20 &= ~1u;
      }
      _raise_exc(v12, (ULONG_PTR)Arguments, (unsigned int *)&a3, v11, a1, (double *)(a2 + 8), (double *)(a2 + 24));
    }
    goto LABEL_21;
  }
  v10 = v9 - 2;
  if ( !v10 )
  {
    *(_DWORD *)a2 = 1;
    goto LABEL_21;
  }
  if ( v10 == 1 )
  {
    v17 = 16;
    goto LABEL_14;
  }
LABEL_21:
  _ctrlfp(v3);
  if ( *(_DWORD *)a2 == 8 )
    return _set_errno(*(_DWORD *)a2);
  if ( dword_60B870 )
    return _set_errno(*(_DWORD *)a2);
  result = sub_55D67E();
  if ( !result )
    return _set_errno(*(_DWORD *)a2);
  return result;
}

// 0x0055C0E5
int __cdecl __strgtold12(int a1, char **a2, char *a3, int a4, int a5, int a6, int a7)
{
  char *v7; // edi
  int v8; // eax
  char v9; // cl
  char v10; // bl
  char *v12; // eax
  char *v14; // eax
  int v15; // eax
  char *v16; // ecx
  char *v17; // edi
  int v18; // esi
  int v19; // eax
  bool v21; // zf
  char *v22; // eax
  int v23; // eax
  int v24; // eax
  char *v25; // ebx
  char *v26; // esi
  __int16 v27; // ax
  __int16 v28; // dx
  __int16 v29; // ax
  int result; // eax
  int v31; // [esp-4h] [ebp-6Ch]
  int v32; // [esp-4h] [ebp-6Ch]
  char v33[23]; // [esp+Ch] [ebp-5Ch] BYREF
  char v34; // [esp+23h] [ebp-45h]
  _WORD v35[3]; // [esp+28h] [ebp-40h] BYREF
  char *v36; // [esp+2Eh] [ebp-3Ah]
  int v37; // [esp+32h] [ebp-36h]
  int v38; // [esp+38h] [ebp-30h]
  int v39; // [esp+3Ch] [ebp-2Ch]
  int v40; // [esp+40h] [ebp-28h]
  int v41; // [esp+44h] [ebp-24h]
  int v42; // [esp+48h] [ebp-20h]
  int v43; // [esp+4Ch] [ebp-1Ch]
  int v44; // [esp+50h] [ebp-18h]
  int v45; // [esp+54h] [ebp-14h]
  int v46; // [esp+58h] [ebp-10h]
  char *v47; // [esp+5Ch] [ebp-Ch]
  int v48; // [esp+60h] [ebp-8h]
  unsigned int v49; // [esp+64h] [ebp-4h]

  v7 = a3;
  v47 = v33;
  v8 = 0;
  v40 = 0;
  v44 = 1;
  v49 = 0;
  v46 = 0;
  v41 = 0;
  v42 = 0;
  v39 = 0;
  v38 = 0;
  v43 = 0;
  v48 = 0;
  v45 = 0;
  while ( 1 )
  {
    v9 = *v7;
    if ( *v7 != 32 && v9 != 9 && v9 != 10 && v9 != 13 )
      break;
    ++v7;
  }
  while ( 2 )
  {
    v10 = *v7++;
    switch ( v8 )
    {
      case 0:
        if ( v10 >= 49 && v10 <= 57 )
          goto LABEL_10;
        if ( v10 == byte_60AF10 )
          goto LABEL_12;
        if ( v10 == 43 )
        {
          v40 = 0;
          v8 = 2;
          continue;
        }
        if ( v10 == 45 )
        {
          v40 = 0x8000;
          v8 = 2;
          continue;
        }
        if ( v10 != 48 )
          goto LABEL_106;
        goto LABEL_35;
      case 1:
        v46 = 1;
        if ( v10 >= 49 && v10 <= 57 )
          goto LABEL_10;
        if ( v10 == byte_60AF10 )
          goto LABEL_46;
        if ( v10 == 43 || v10 == 45 )
          goto LABEL_30;
        if ( v10 != 48 )
          goto LABEL_25;
        goto LABEL_35;
      case 2:
        if ( v10 >= 49 && v10 <= 57 )
        {
LABEL_10:
          v31 = 3;
LABEL_80:
          v8 = v31;
LABEL_81:
          --v7;
        }
        else
        {
          if ( v10 == byte_60AF10 )
          {
LABEL_12:
            v32 = 5;
            goto LABEL_89;
          }
          if ( v10 != 48 )
          {
LABEL_91:
            v17 = a3;
            goto LABEL_108;
          }
LABEL_35:
          v8 = 1;
        }
        continue;
      case 3:
        v46 = 1;
        while ( (int)cbMultiByte <= 1
              ? *((_BYTE *)g_pVtbl_SceneMgr + 2 * (unsigned __int8)v10) & 4
              : _isctype((unsigned __int8)v10, 4) )
        {
          if ( v49 >= 0x19 )
          {
            ++v48;
          }
          else
          {
            v12 = v47;
            ++v49;
            ++v47;
            *v12 = v10 - 48;
          }
          v10 = *v7++;
        }
        if ( v10 != byte_60AF10 )
          goto LABEL_57;
LABEL_46:
        v8 = 4;
        continue;
      case 4:
        v46 = 1;
        v41 = 1;
        if ( !v49 )
        {
          while ( v10 == 48 )
          {
            --v48;
            v10 = *v7++;
          }
        }
        while ( (int)cbMultiByte <= 1
              ? *((_BYTE *)g_pVtbl_SceneMgr + 2 * (unsigned __int8)v10) & 4
              : _isctype((unsigned __int8)v10, 4) )
        {
          if ( v49 < 0x19 )
          {
            v14 = v47;
            ++v49;
            ++v47;
            --v48;
            *v14 = v10 - 48;
          }
          v10 = *v7++;
        }
LABEL_57:
        if ( v10 == 43 || v10 == 45 )
        {
LABEL_30:
          --v7;
          v32 = 11;
        }
        else
        {
LABEL_25:
          if ( v10 <= 67 || v10 > 69 && (v10 <= 99 || v10 > 101) )
          {
LABEL_106:
            v17 = v7 - 1;
            goto LABEL_108;
          }
          v32 = 6;
        }
        goto LABEL_89;
      case 5:
        v41 = 1;
        if ( (int)cbMultiByte <= 1 )
          v15 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * (unsigned __int8)v10) & 4;
        else
          v15 = _isctype((unsigned __int8)v10, 4);
        if ( !v15 )
          goto LABEL_91;
        v8 = 4;
        goto LABEL_81;
      case 6:
        v16 = v7 - 2;
        a3 = v7 - 2;
        if ( v10 >= 49 && v10 <= 57 )
          goto LABEL_79;
        if ( v10 == 43 )
          goto LABEL_88;
        if ( v10 == 45 )
          goto LABEL_87;
        if ( v10 != 48 )
          goto LABEL_107;
LABEL_70:
        v32 = 8;
        goto LABEL_89;
      case 7:
        if ( v10 >= 49 && v10 <= 57 )
          goto LABEL_79;
        if ( v10 == 48 )
          goto LABEL_70;
        goto LABEL_91;
      case 8:
        v42 = 1;
        while ( v10 == 48 )
          v10 = *v7++;
        if ( v10 < 49 || v10 > 57 )
          goto LABEL_106;
LABEL_79:
        v31 = 9;
        goto LABEL_80;
      case 9:
        v42 = 1;
        v18 = 0;
        while ( 2 )
        {
          if ( (int)cbMultiByte <= 1 )
            v19 = *((_BYTE *)g_pVtbl_SceneMgr + 2 * (unsigned __int8)v10) & 4;
          else
            v19 = _isctype((unsigned __int8)v10, 4);
          if ( v19 )
          {
            v18 = v10 + 10 * v18 - 48;
            if ( v18 <= 5200 )
            {
              v10 = *v7++;
              continue;
            }
            v18 = 5201;
          }
          break;
        }
        v43 = v18;
        while ( (int)cbMultiByte <= 1
              ? *((_BYTE *)g_pVtbl_SceneMgr + 2 * (unsigned __int8)v10) & 4
              : _isctype((unsigned __int8)v10, 4) )
          v10 = *v7++;
        goto LABEL_106;
      case 11:
        if ( !a7 )
        {
          v17 = v7 - 1;
          goto LABEL_108;
        }
        v16 = v7 - 1;
        a3 = v7 - 1;
        if ( v10 == 43 )
        {
LABEL_88:
          v32 = 7;
LABEL_89:
          v8 = v32;
          continue;
        }
        if ( v10 == 45 )
        {
LABEL_87:
          v44 = -1;
          v8 = 7;
          continue;
        }
LABEL_107:
        v17 = v16;
LABEL_108:
        v21 = v46 == 0;
        *a2 = v17;
        if ( v21 )
        {
          v28 = 0;
          v27 = 0;
          v26 = 0;
          v25 = 0;
          v45 = 4;
        }
        else
        {
          if ( v49 <= 0x18 )
          {
            v22 = v47;
          }
          else
          {
            if ( v34 >= 5 )
              ++v34;
            v49 = 24;
            v22 = v47 - 1;
            ++v48;
          }
          if ( v49 )
          {
            while ( !*--v22 )
            {
              --v49;
              ++v48;
            }
            __mtold12(v33, v49, (int)v35);
            v23 = v43;
            if ( v44 < 0 )
              v23 = -v43;
            v24 = v48 + v23;
            if ( !v42 )
              v24 += a5;
            if ( !v41 )
              v24 -= a6;
            if ( v24 > 5200 )
            {
              v39 = 1;
              goto LABEL_125;
            }
            if ( v24 >= -5200 )
            {
              __multtenpow12(v35, v24, a4);
              v28 = v35[0];
              v25 = *(char **)&v35[1];
              v26 = v36;
              v27 = v37;
            }
            else
            {
              v38 = 1;
LABEL_125:
              v25 = a3;
              v26 = a3;
              v27 = (__int16)a3;
              v28 = (__int16)a3;
            }
          }
          else
          {
            v28 = 0;
            v27 = 0;
            v26 = 0;
            v25 = 0;
          }
          if ( v39 )
          {
            v25 = 0;
            v27 = 0x7FFF;
            v26 = (char *)0x80000000;
            v28 = 0;
            v45 = 2;
          }
          else if ( v38 )
          {
            v28 = 0;
            v27 = 0;
            v26 = 0;
            v25 = 0;
            v45 = 1;
          }
        }
        v29 = v40 | v27;
        *(_DWORD *)(a1 + 6) = v26;
        *(_DWORD *)(a1 + 2) = v25;
        *(_WORD *)(a1 + 10) = v29;
        result = v45;
        *(_WORD *)a1 = v28;
        return result;
    }
  }
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

// 0x0055D34B
double __cdecl _frnd(double a1)
{
  double result; // st7

  _ST7 = a1;
  __asm { frndint }
  return result;
}

// 0x0055D35D
int __cdecl _fcloseall()
{
  int v0; // edi
  int i; // esi
  int v2; // eax

  v0 = 0;
  for ( i = 3; i < (int)Count; ++i )
  {
    v2 = *(_DWORD *)(g_PlayerLevel + 4 * i);
    if ( v2 )
    {
      if ( (*(_BYTE *)(v2 + 12) & 0x83) != 0 && fclose(*(FILE **)(g_PlayerLevel + 4 * i)) != -1 )
        ++v0;
      if ( i >= 20 )
      {
        free(*(void **)(g_PlayerLevel + 4 * i));
        *(_DWORD *)(g_PlayerLevel + 4 * i) = 0;
      }
    }
  }
  return v0;
}

// 0x0055D3B5
int __cdecl mbtowc(wchar_t *DstCh, const char *SrcCh, size_t SrcSizeInBytes)
{
  unsigned __int8 v3; // al
  int result; // eax
  bool v5; // zf

  if ( !SrcCh || !SrcSizeInBytes )
    return 0;
  v3 = *SrcCh;
  if ( !*SrcCh )
  {
    if ( DstCh )
      *DstCh = 0;
    return 0;
  }
  if ( !dword_18953A8 )
  {
    if ( DstCh )
      *DstCh = v3;
    return 1;
  }
  if ( *((char *)g_pVtbl_SceneMgr + 2 * v3 + 1) >= 0 )
  {
    if ( MultiByteToWideChar(dword_18953B8, 9u, SrcCh, 1, DstCh, DstCh != 0) )
      return 1;
    goto LABEL_18;
  }
  result = cbMultiByte;
  if ( (int)cbMultiByte > 1 )
  {
    if ( (int)SrcSizeInBytes >= (int)cbMultiByte )
    {
      v5 = MultiByteToWideChar(dword_18953B8, 9u, SrcCh, cbMultiByte, DstCh, DstCh != 0) == 0;
      result = cbMultiByte;
      if ( !v5 )
        return result;
      goto LABEL_16;
    }
LABEL_18:
    g_PlayerData_33C = 42;
    return -1;
  }
LABEL_16:
  if ( SrcSizeInBytes < result || !SrcCh[1] )
    goto LABEL_18;
  return result;
}

// 0x0055D47D
int __cdecl isspace(int C)
{
  if ( (int)cbMultiByte <= 1 )
    return *((_BYTE *)g_pVtbl_SceneMgr + 2 * C) & 8;
  else
    return _isctype(C, 8);
}

// 0x0055D4B0
int __usercall _allshl@<eax>(__int64 a1@<edx:eax>, unsigned __int8 a2@<cl>)
{
  __int64 v2; // rax

  if ( a2 >= 0x40u )
  {
    LODWORD(v2) = 0;
  }
  else if ( a2 >= 0x20u )
  {
    LODWORD(v2) = 0;
  }
  else
  {
    return a1 << (a2 & 0x1F);
  }
  return v2;
}

// 0x0055D4CF
int __cdecl ungetc(int Character, FILE *Stream)
{
  int flag; // eax
  int v4; // eax

  if ( Character == -1 )
    return -1;
  flag = Stream->_flag;
  if ( (flag & 1) == 0 && ((flag & 0x80u) == 0 || (flag & 2) != 0) )
    return -1;
  if ( !Stream->_base )
    _getbuf(Stream);
  if ( Stream->_ptr == Stream->_base )
  {
    if ( Stream->_cnt )
      return -1;
    ++Stream->_ptr;
  }
  if ( (Stream->_flag & 0x40) != 0 )
  {
    if ( *--Stream->_ptr != (_BYTE)Character )
    {
      ++Stream->_ptr;
      return -1;
    }
  }
  else
  {
    *--Stream->_ptr = Character;
  }
  v4 = Stream->_flag;
  ++Stream->_cnt;
  LOBYTE(v4) = v4 & 0xEE | 1;
  Stream->_flag = v4;
  return (unsigned __int8)Character;
}

// 0x0055D53D
int __cdecl _setmode(int FileHandle, int Mode)
{
  char *v2; // edx
  char v3; // cl
  int v4; // eax
  char v5; // cl
  int v6; // eax

  if ( FileHandle < uNumber
    && (v2 = (char *)(*(&g_nUIState + (FileHandle >> 5)) + 8 * (FileHandle & 0x1F) + 4), v3 = *v2, (*v2 & 1) != 0) )
  {
    v4 = v3 & 0x80;
    if ( Mode == 0x8000 )
    {
      v5 = v3 & 0x7F;
LABEL_7:
      v6 = -(v4 != 0);
      *v2 = v5;
      LOWORD(v6) = v6 & 0xC000;
      return v6 + 0x8000;
    }
    if ( Mode == 0x4000 )
    {
      v5 = v3 | 0x80;
      goto LABEL_7;
    }
    g_PlayerData_33C = 22;
  }
  else
  {
    g_PlayerData_33C = 9;
  }
  return -1;
}

// 0x0055D5B3
int __cdecl _ismbblead(unsigned int Ch)
{
  return x_ismbbtype(Ch, 0, 4u);
}

// 0x0055D5C4
int __cdecl x_ismbbtype(unsigned __int8 a1, int a2, unsigned __int8 a3)
{
  int result; // eax

  if ( (a3 & *(&g_bQuestActive + a1)) != 0 )
    return 1;
  result = a2 ? (unsigned __int16)(a2 & _ctype[a1 + 1]) : 0;
  if ( result )
    return 1;
  return result;
}

// 0x0055D5F5
int __cdecl __crtMessageBoxA(const CHAR *lpText, const CHAR *lpCaption, UINT uType)
{
  HWND ActiveWindow_0; // ebx
  HMODULE LibraryA; // eax
  HMODULE v5; // edi

  ActiveWindow_0 = 0;
  if ( !MessageBoxA_0 )
  {
    LibraryA = LoadLibraryA("user32.dll");
    v5 = LibraryA;
    if ( !LibraryA )
      return 0;
    MessageBoxA_0 = (int (__stdcall *)(HWND, LPCSTR, LPCSTR, UINT))GetProcAddress(LibraryA, "MessageBoxA");
    if ( !MessageBoxA_0 )
      return 0;
    GetActiveWindow_0 = (HWND (__stdcall *)())GetProcAddress(v5, "GetActiveWindow");
    GetLastActivePopup = (HWND (__stdcall *)(HWND))GetProcAddress(v5, "GetLastActivePopup");
  }
  if ( GetActiveWindow_0 )
  {
    ActiveWindow_0 = GetActiveWindow_0();
    if ( ActiveWindow_0 )
    {
      if ( GetLastActivePopup )
        ActiveWindow_0 = GetLastActivePopup(ActiveWindow_0);
    }
  }
  return MessageBoxA_0(ActiveWindow_0, lpText, lpCaption, uType);
}

// 0x0055D681
int __cdecl __addl(unsigned int a1, unsigned int a2, unsigned int *a3)
{
  int result; // eax
  unsigned int v4; // ecx

  result = 0;
  v4 = a1 + a2;
  if ( a1 + a2 < a1 || v4 < a2 )
    result = 1;
  *a3 = v4;
  return result;
}

// 0x0055D6A2
int __cdecl __add_12(unsigned int *a1, unsigned int *a2)
{
  if ( __addl(*a1, *a2, a1) && __addl(a1[1], 1u, a1 + 1) )
    ++a1[2];
  if ( __addl(a1[1], a2[1], a1 + 1) )
    ++a1[2];
  return __addl(a1[2], a2[2], a1 + 2);
}

// 0x0055D700
unsigned int *__cdecl __shl_12(unsigned int *a1)
{
  unsigned int v2; // edi
  unsigned int v3; // ecx
  int v4; // esi
  unsigned int v5; // ecx

  v2 = a1[1];
  v3 = *a1;
  *a1 *= 2;
  v4 = (v3 >> 31) | (2 * v2);
  v5 = a1[2];
  a1[1] = v4;
  a1[2] = (v2 >> 31) | (2 * v5);
  return a1;
}

// 0x0055D72E
unsigned int *__cdecl __shr_12(unsigned int *a1)
{
  unsigned int v2; // edx
  unsigned int v3; // edi
  unsigned int v4; // ecx

  v2 = a1[2];
  v3 = a1[1];
  a1[1] = *(__int64 *)(a1 + 1) >> 1;
  v4 = (v3 << 31) | (*a1 >> 1);
  a1[2] = v2 >> 1;
  *a1 = v4;
  return a1;
}

// 0x0055D75B
__int16 __cdecl __mtold12(char *a1, int a2, int a3)
{
  unsigned int v4; // ecx
  int v5; // esi
  int v6; // eax
  __int16 result; // ax
  unsigned int v8; // [esp+8h] [ebp-10h] BYREF
  int v9; // [esp+Ch] [ebp-Ch]
  int v10; // [esp+10h] [ebp-8h]
  int v11; // [esp+14h] [ebp-4h]
  int v12; // [esp+28h] [ebp+10h]

  v11 = 16462;
  *(_DWORD *)a3 = 0;
  *(_DWORD *)(a3 + 4) = 0;
  *(_DWORD *)(a3 + 8) = 0;
  if ( a2 )
  {
    v12 = a2;
    do
    {
      v8 = *(_DWORD *)a3;
      v9 = *(_DWORD *)(a3 + 4);
      v10 = *(_DWORD *)(a3 + 8);
      __shl_12((unsigned int *)a3);
      __shl_12((unsigned int *)a3);
      __add_12((unsigned int *)a3, &v8);
      __shl_12((unsigned int *)a3);
      v9 = 0;
      v10 = 0;
      v8 = *a1;
      __add_12((unsigned int *)a3, &v8);
      ++a1;
      --v12;
    }
    while ( v12 );
  }
  while ( !*(_DWORD *)(a3 + 8) )
  {
    v4 = *(_DWORD *)(a3 + 4);
    *(_DWORD *)(a3 + 8) = HIWORD(v4);
    v5 = (v4 << 16) | HIWORD(*(_DWORD *)a3);
    v6 = *(_DWORD *)a3 << 16;
    v11 += 65520;
    *(_DWORD *)(a3 + 4) = v5;
    *(_DWORD *)a3 = v6;
  }
  while ( (*(_DWORD *)(a3 + 8) & 0x8000) == 0 )
  {
    __shl_12((unsigned int *)a3);
    v11 += 0xFFFF;
  }
  result = v11;
  *(_WORD *)(a3 + 10) = v11;
  return result;
}

// 0x0055D822
int __cdecl _I10_OUTPUT(__int64 a1, int a2, int a3, char a4, int a5)
{
  int v5; // ebx
  __int16 v6; // cx
  unsigned __int16 v7; // dx
  int v8; // edi
  int v9; // esi
  bool v10; // zf
  int v11; // edi
  int v12; // esi
  int i; // esi
  int v14; // eax
  char v15; // al
  _BYTE *v16; // ecx
  char v17; // cl
  _BYTE *v18; // eax
  bool v19; // cc
  _BYTE *v20; // ecx
  char v21; // al
  _BYTE v23[12]; // [esp+Ch] [ebp-1Ch] BYREF
  _BYTE v24[12]; // [esp+18h] [ebp-10h] BYREF
  int v25; // [esp+24h] [ebp-4h]

  v5 = a5;
  v6 = a2 & 0x8000;
  memset(v23, 204, 10);
  v23[10] = -5;
  v23[11] = 63;
  v25 = 1;
  v7 = a2 & 0x7FFF;
  if ( (a2 & 0x8000u) == 0 )
    *(_BYTE *)(a5 + 2) = 32;
  else
    *(_BYTE *)(a5 + 2) = 45;
  v8 = HIDWORD(a1);
  if ( !v7 && !a1 )
    goto LABEL_6;
  if ( v7 == 0x7FFF )
  {
    *(_WORD *)v5 = 1;
    if ( (v8 != 0x80000000 || (_DWORD)a1) && (v8 & 0x40000000) == 0 )
    {
      strcpy((char *)(v5 + 4), "1#SNAN");
LABEL_22:
      *(_BYTE *)(v5 + 3) = 6;
      return 0;
    }
    if ( v6 && v8 == -1073741824 )
    {
      if ( !(_DWORD)a1 )
      {
        strcpy((char *)(v5 + 4), "1#IND");
LABEL_19:
        *(_BYTE *)(v5 + 3) = 5;
        return 0;
      }
    }
    else if ( v8 == 0x80000000 && !(_DWORD)a1 )
    {
      strcpy((char *)(v5 + 4), "1#INF");
      goto LABEL_19;
    }
    strcpy((char *)(v5 + 4), "1#QNAN");
    goto LABEL_22;
  }
  *(_WORD *)v24 = 0;
  *(_WORD *)&v24[10] = v7;
  v9 = (77 * (HIBYTE(v7) + 2 * HIBYTE(HIDWORD(a1))) + 19728 * v7 - 323162868) >> 16;
  *(_QWORD *)&v24[2] = a1;
  __multtenpow12(v24, -(__int16)v9, 1);
  if ( *(_WORD *)&v24[10] >= 0x3FFFu )
  {
    LOWORD(v9) = v9 + 1;
    __ld12mul((int)v24, (int)v23);
  }
  v10 = (a4 & 1) == 0;
  *(_WORD *)v5 = v9;
  if ( v10 )
  {
    v11 = a3;
    goto LABEL_29;
  }
  v11 = (__int16)v9 + a3;
  if ( v11 > 0 )
  {
LABEL_29:
    if ( v11 > 21 )
      v11 = 21;
    v12 = *(unsigned __int16 *)&v24[10] - 16382;
    *(_WORD *)&v24[10] = 0;
    a5 = 8;
    do
    {
      __shl_12((unsigned int *)v24);
      --a5;
    }
    while ( a5 );
    if ( v12 < 0 )
    {
      for ( i = (unsigned __int8)-(char)v12; i; --i )
        __shr_12((unsigned int *)v24);
    }
    v14 = v5 + 4;
    a5 = v5 + 4;
    if ( v11 + 1 > 0 )
    {
      a3 = v11 + 1;
      do
      {
        a1 = *(_QWORD *)v24;
        a2 = *(_DWORD *)&v24[8];
        __shl_12((unsigned int *)v24);
        __shl_12((unsigned int *)v24);
        __add_12((unsigned int *)v24, (unsigned int *)&a1);
        __shl_12((unsigned int *)v24);
        v15 = v24[11];
        v16 = (_BYTE *)a5;
        v24[11] = 0;
        ++a5;
        v10 = a3-- == 1;
        *v16 = v15 + 48;
      }
      while ( !v10 );
      v14 = a5;
    }
    v17 = *(_BYTE *)(v14 - 1);
    v18 = (_BYTE *)(v14 - 2);
    v19 = v17 < 53;
    v20 = (_BYTE *)(v5 + 4);
    if ( v19 )
    {
      while ( v18 >= v20 )
      {
        if ( *v18 != 48 )
        {
          if ( v18 >= v20 )
            goto LABEL_47;
          break;
        }
        --v18;
      }
      *(_WORD *)v5 = 0;
      *(_BYTE *)(v5 + 2) = 32;
      *(_BYTE *)(v5 + 3) = 1;
      *v20 = 48;
      goto LABEL_54;
    }
    while ( v18 >= v20 )
    {
      if ( *v18 != 57 )
      {
        if ( v18 >= v20 )
          goto LABEL_46;
        break;
      }
      *v18-- = 48;
    }
    ++v18;
    ++*(_WORD *)v5;
LABEL_46:
    ++*v18;
LABEL_47:
    v21 = (_BYTE)v18 - v5 - 3;
    *(_BYTE *)(v5 + 3) = v21;
    *(_BYTE *)(v21 + v5 + 4) = 0;
    return v25;
  }
LABEL_6:
  *(_WORD *)v5 = 0;
  *(_BYTE *)(v5 + 2) = 32;
  *(_BYTE *)(v5 + 3) = 1;
  *(_BYTE *)(v5 + 4) = 48;
LABEL_54:
  *(_BYTE *)(v5 + 5) = 0;
  return 1;
}

// 0x0055DAB5
int __cdecl raise(int Signal)
{
  int v1; // edi
  void (__cdecl *v3)(int); // esi
  int *v4; // eax
  int *v5; // eax
  int v6; // ebx
  int v7; // edx
  int v8; // ecx
  _DWORD *v9; // edx

  v1 = Signal;
  switch ( Signal )
  {
    case 2:
      v3 = (void (__cdecl *)(int))dword_1895544;
      v4 = &dword_1895544;
      break;
    case 4:
    case 8:
    case 11:
      v5 = siglookup(Signal);
      v3 = (void (__cdecl *)(int))v5[2];
      v4 = v5 + 2;
      break;
    case 15:
      v3 = (void (__cdecl *)(int))dword_1895550;
      v4 = &dword_1895550;
      break;
    case 21:
      v3 = (void (__cdecl *)(int))dword_1895548;
      v4 = &dword_1895548;
      break;
    case 22:
      v3 = (void (__cdecl *)(int))dword_189554C;
      v4 = &dword_189554C;
      break;
    default:
      return -1;
  }
  if ( v3 == (void (__cdecl *)(int))1 )
    return 0;
  if ( !v3 )
    _exit(3);
  if ( Signal == 8 || Signal == 11 || Signal == 4 )
  {
    v6 = dword_18953EC;
    dword_18953EC = 0;
    if ( Signal != 8 )
    {
LABEL_29:
      *v4 = 0;
      v3(v1);
      if ( v1 != 11 && v1 != 4 )
        return 0;
      goto LABEL_33;
    }
    v7 = g_nFrameCount;
    g_nFrameCount = 140;
    Signal = v7;
  }
  else
  {
    v6 = Signal;
  }
  if ( v1 != 8 )
    goto LABEL_29;
  if ( dword_60B528 < dword_60B528 + dword_60B52C )
  {
    v8 = dword_60B52C;
    v9 = (_DWORD *)(12 * dword_60B528 + 6337720);
    do
    {
      *v9 = 0;
      v9 += 3;
      --v8;
    }
    while ( v8 );
  }
  ((void (__cdecl *)(int, int))v3)(8, g_nFrameCount);
LABEL_33:
  dword_18953EC = v6;
  if ( v1 == 8 )
    g_nFrameCount = Signal;
  return 0;
}

// 0x0055DBE2
int *__cdecl siglookup(int a1)
{
  int *result; // eax

  result = &dword_60B4B0;
  if ( dword_60B4B4 != a1 )
  {
    do
      result += 3;
    while ( (unsigned int)result < 12 * dword_60B530 + 6337712 && result[1] != a1 );
  }
  if ( (unsigned int)result >= 12 * dword_60B530 + 6337712 || result[1] != a1 )
    return 0;
  return result;
}

// 0x0055DC27
int __cdecl __ld12mul(int a1, int a2)
{
  __int16 v4; // cx
  __int16 v5; // ax
  __int16 v6; // di
  int result; // eax
  int v8; // ecx
  int v9; // edi
  unsigned __int16 v10; // dx
  int v11; // eax
  int v12; // ebx
  unsigned int v13[3]; // [esp+Ch] [ebp-24h] BYREF
  int v14; // [esp+18h] [ebp-18h]
  int v15; // [esp+1Ch] [ebp-14h]
  int v16; // [esp+20h] [ebp-10h]
  unsigned __int16 *v17; // [esp+24h] [ebp-Ch]
  unsigned __int16 *v18; // [esp+28h] [ebp-8h]
  unsigned int *v19; // [esp+2Ch] [ebp-4h]
  int v20; // [esp+38h] [ebp+8h]
  int v21; // [esp+38h] [ebp+8h]
  int i; // [esp+3Ch] [ebp+Ch]

  v4 = *(_WORD *)(a2 + 10);
  v15 = 0;
  memset(v13, 0, sizeof(v13));
  v5 = *(_WORD *)(a1 + 10);
  v6 = v5 ^ v4;
  result = v5 & 0x7FFF;
  v8 = v4 & 0x7FFF;
  v9 = v6 & 0x8000;
  v10 = v8 + result;
  v20 = v8 + result;
  if ( (unsigned __int16)result < 0x7FFFu && (unsigned __int16)v8 < 0x7FFFu && v10 <= 0xBFFDu )
  {
    if ( v10 <= 0x3FBFu )
    {
      result = 0;
LABEL_16:
      *(_DWORD *)(a1 + 8) = 0;
      *(_DWORD *)(a1 + 4) = 0;
      *(_DWORD *)a1 = 0;
      return result;
    }
    if ( (_WORD)result || (++v20, (*(_DWORD *)(a1 + 8) & 0x7FFFFFFF) != 0) )
    {
      result = 0;
    }
    else
    {
      result = 0;
      if ( !*(_DWORD *)(a1 + 4) && !*(_DWORD *)a1 )
        goto LABEL_45;
    }
    if ( !(_WORD)v8 )
    {
      ++v20;
      if ( (*(_DWORD *)(a2 + 8) & 0x7FFFFFFF) == 0 && !*(_DWORD *)(a2 + 4) && !*(_DWORD *)a2 )
        goto LABEL_16;
    }
    v16 = 0;
    v19 = &v13[1];
    for ( i = 5; i > 0; --i )
    {
      v18 = (unsigned __int16 *)(a1 + 2 * v16);
      v17 = (unsigned __int16 *)(a2 + 8);
      v14 = i;
      do
      {
        if ( __addl(*(v19 - 1), *v17 * *v18, v19 - 1) )
          ++*(_WORD *)v19;
        ++v18;
        --v17;
        --v14;
      }
      while ( v14 );
      v19 = (unsigned int *)((char *)v19 + 2);
      ++v16;
    }
    v21 = v20 + 49154;
    if ( (__int16)v21 <= 0 )
      goto LABEL_49;
    do
    {
      if ( (v13[2] & 0x80000000) != 0 )
        break;
      __shl_12(v13);
      v21 += 0xFFFF;
    }
    while ( (__int16)v21 > 0 );
    if ( (__int16)v21 <= 0 )
    {
LABEL_49:
      v21 += 0xFFFF;
      if ( (v21 & 0x8000u) != 0 )
      {
        v11 = -(__int16)v21;
        v21 -= (__int16)v21;
        v12 = v11;
        do
        {
          if ( (v13[0] & 1) != 0 )
            ++v15;
          __shr_12(v13);
          --v12;
        }
        while ( v12 );
        if ( v15 )
          LOBYTE(v13[0]) |= 1u;
      }
    }
    if ( LOWORD(v13[0]) > 0x8000u || (v13[0] & 0x1FFFF) == 0x18000 )
    {
      if ( *(unsigned int *)((char *)v13 + 2) == -1 )
      {
        *(unsigned int *)((char *)v13 + 2) = 0;
        if ( *(unsigned int *)((char *)&v13[1] + 2) == -1 )
        {
          *(unsigned int *)((char *)&v13[1] + 2) = 0;
          if ( HIWORD(v13[2]) == 0xFFFF )
          {
            ++v21;
            HIWORD(v13[2]) = 0x8000;
          }
          else
          {
            ++HIWORD(v13[2]);
          }
        }
        else
        {
          ++*(unsigned int *)((char *)&v13[1] + 2);
        }
      }
      else
      {
        ++*(unsigned int *)((char *)v13 + 2);
      }
    }
    result = v21;
    if ( (unsigned __int16)v21 < 0x7FFFu )
    {
      result = v9 | v21;
      *(_WORD *)a1 = HIWORD(v13[0]);
      *(_DWORD *)(a1 + 2) = v13[1];
      *(_DWORD *)(a1 + 6) = v13[2];
LABEL_45:
      *(_WORD *)(a1 + 10) = result;
      return result;
    }
  }
  *(_DWORD *)(a1 + 4) = 0;
  *(_DWORD *)a1 = 0;
  *(_DWORD *)(a1 + 8) = (_WORD)v9 != 0 ? -32768 : 2147450880;
  return result;
}

// 0x0055DE47
void __cdecl __multtenpow12(_WORD *a1, int a2, int a3)
{
  char *v3; // ebx
  char v4; // al
  int v5; // eax
  char *v6; // esi
  _DWORD *v7; // esi
  __int64 v8; // [esp+4h] [ebp-Ch] BYREF
  int v9; // [esp+Ch] [ebp-4h]

  v3 = (char *)&unk_60B878 - 96;
  if ( a2 )
  {
    if ( a2 < 0 )
    {
      a2 = -a2;
      v3 = (char *)&unk_60B9D8 - 96;
    }
    if ( !a3 )
      *a1 = 0;
    while ( a2 )
    {
      v4 = a2;
      v3 += 84;
      a2 >>= 3;
      v5 = v4 & 7;
      if ( v5 )
      {
        v6 = &v3[12 * v5];
        if ( *(_WORD *)v6 >= 0x8000u )
        {
          LODWORD(v8) = *(_DWORD *)v6;
          v7 = v6 + 4;
          HIDWORD(v8) = *v7;
          v9 = v7[1];
          --*(_DWORD *)((char *)&v8 + 2);
          v6 = (char *)&v8;
        }
        __ld12mul((int)a1, (int)v6);
      }
    }
  }
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

// 0x0055EF90
int __cdecl _strcmpi(const char *String1, const char *String2)
{
  int result; // eax
  char v5; // t0
  int v6; // ebx
  int v7; // [esp-4h] [ebp-10h]

  if ( dword_18953A8 )
  {
    result = 255;
    v6 = 0;
    while ( (_BYTE)result )
    {
      LOBYTE(result) = *String2++;
      LOBYTE(v6) = *String1++;
      if ( (_BYTE)result != (_BYTE)v6 )
      {
        v7 = result;
        v6 = tolower(v6);
        result = tolower(v7);
        if ( (_BYTE)v6 != (_BYTE)result )
          return -((unsigned __int8)v6 < (unsigned __int8)result)
               - (((unsigned __int8)v6 < (unsigned __int8)result)
                - 1);
      }
    }
  }
  else
  {
    LOBYTE(result) = -1;
    while ( (_BYTE)result )
    {
      LOBYTE(result) = *String2++;
      BYTE1(result) = *String1++;
      if ( BYTE1(result) != (_BYTE)result )
      {
        v5 = BYTE1(result);
        BYTE1(result) = ((unsigned __int8)(result - 65) < 0x1Au ? 0x20 : 0) + result;
        LOBYTE(result) = ((unsigned __int8)(v5 - 65) < 0x1Au ? 0x20 : 0) + v5;
        if ( (_BYTE)result != BYTE1(result) )
        {
          LOBYTE(result) = -((unsigned __int8)result < BYTE1(result)) - (((unsigned __int8)result < BYTE1(result)) - 1);
          return (char)result;
        }
      }
    }
    return (char)result;
  }
  return result;
}
