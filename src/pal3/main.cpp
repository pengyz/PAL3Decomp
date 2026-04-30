/*
 * PAL3.exe Main Entry Point - Phase 0 Stub
 *
 * This file contains the WinMain function, which is the entry point for PAL3.exe.
 * The Phase 0 version is only used to verify that the build system can successfully
 * generate an executable file.
 *
 * Phase 1 will implement the complete WinMain function, including:
 *   - Window initialization
 *   - DirectX initialization
 *   - Game loop
 *   - Resource management
 */

#include <windows.h>
#include <stdio.h>

extern int __cdecl WinMainCRTStartup(void);

/*
 * _main - Dummy entry point for dynamic CRT
 *
 * The CRT expects this when /SUBSYSTEM:WINDOWS is used with /MD or /MDd.
 * This function is never called; instead, WinMainCRTStartup is invoked.
 */
int __cdecl main(void)
{
    /* This should never be reached */
    return 0;
}

/*
 * WinMain - Windows Application Entry Point
 *
 * Parameters:
 *   hInstance      - Application instance handle
 *   hPrevInstance  - Previous instance handle (always NULL in modern Windows)
 *   lpCmdLine      - Command line arguments
 *   nCmdShow       - Window display mode (SW_SHOW, etc.)
 *
 * Return value:
 *   Application exit code
 */
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    /*
     * Phase 0: Minimal stub for build system verification
     *
     * This minimal implementation is capable of:
     *   1. Being compiled into a valid PE executable
     *   2. Running successfully on Windows
     *   3. Demonstrating that the build system works correctly
     *
     * Phase 1 will replace this section with complete game initialization code.
     */

    /* Display stub message box indicating Phase 0 */
    MessageBoxA(
        NULL,
        "PAL3 Decompilation Project - Phase 0\n\n"
        "Build system verification successful.\n"
        "Placeholder implementation ready for Phase 1 development.",
        "PAL3 Phase 0 Stub",
        MB_OK | MB_ICONINFORMATION);

    /* Return success code */
    return 0;
}
