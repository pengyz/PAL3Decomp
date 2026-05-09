/**
 * PAL3 Decompilation - Global Variable Declarations
 *
 * Known global variables with their addresses in the original binary.
 * Source: PAL3patch reverse engineering (zhangboyang)
 *
 * Address format:
 *   0x00XXXXXX - PAL3.exe address
 *   gboffset + 0xXXXXXXXX - GBENGINE.dll relative offset
 */

#ifndef PAL3_GLOBALS_H
#define PAL3_GLOBALS_H

#include "pal3_types.h"

/* Forward declarations */
struct gbGfxManager_D3D;
struct gbGfxDriverInfo;
struct gbVFileSystem;
struct gbImage2D;
struct gbRenderEffect;
struct gbBinkVideo;
struct UIGameFrm;
struct UIStaticFlex;
struct GRPinput;
struct CCBSystem;

/* ========================================================================
 * Engine State Globals
 * ======================================================================== */

/* 图形管理器指针 @ 0x00BFDA60 */
extern struct gbGfxManager_D3D *GB_GfxMgr;

/* 图形驱动信息 @ 0x00BFD6C8 */
extern struct gbGfxDriverInfo PAL3_s_drvinfo;

/* 游戏状态 @ 0x00BFDA6C */
extern int PAL3_s_gamestate;

/* 程序活动状态 @ 0x005833B8 */
extern int PAL3_s_bActive;

/* 全局标志位 @ 0x005833BC
 * bit 0: 声音开关 (0=开启)
 * bit 2: 音乐开关 (0=开启)
 */
extern unsigned int PAL3_s_flag;

/* 游戏时间 @ 0x00BFDAA0 */
extern float PAL3_m_gametime;

/* ========================================================================
 * Game System Globals
 * ======================================================================== */

/* 战斗系统指针 @ 0x00BFDA74 */
extern struct CCBSystem *PAL3_m_pCBSystem;

/* 屏幕截图缓冲 @ 0x008ACC10 */
extern struct gbImage2D PAL3_m_screenImg;

/* 全局时间 (GBENGINE.dll + 0x1015D338) */
extern double g_CurrentTime;

/* ========================================================================
 * UI Globals
 * ======================================================================== */

/* 游戏主框架 @ 0x00DB9FD0 */
extern struct UIGameFrm g_gamefrm;

/* 消息背景 @ 0x00BFDAB0 */
extern struct UIStaticFlex g_msgbk;

/* UI 贴图渲染效果 @ 0x01895058 */
extern struct gbRenderEffect *ui_tex_color_gbf;

/* ========================================================================
 * IO/Media Globals
 * ======================================================================== */

/* 虚拟文件系统 (GBENGINE.dll + 0x1015D3A8) */
extern struct gbVFileSystem *g_pVFileSys;

/* Bink 视频播放器 @ 0x00A3A7D8 */
extern struct gbBinkVideo g_bink;

/* ========================================================================
 * Input Globals
 * ======================================================================== */

/* 输入管理器 @ 0x00BFAD70 */
extern struct GRPinput g_input;

/* ========================================================================
 * Misc Globals
 * ======================================================================== */

/* 上次加载画面更新时间 @ 0x00C12B20 */
extern unsigned long g_lastupdateloading;

#endif /* PAL3_GLOBALS_H */
