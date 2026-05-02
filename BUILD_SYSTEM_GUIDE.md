# PAL3 Decompilation - CMake Build System Guide

## Quick Start

### Build PAL3.exe

```bash
mkdir build && cd build
cmake .. -DBUILD_TARGET=pal3 -G "Visual Studio 17 2022" -A Win32
cmake --build . --config Release
```

Output: `build/Release/PAL3.exe`

### Build topo.dll

```bash
mkdir build && cd build
cmake .. -DBUILD_TARGET=topo -G "Visual Studio 17 2022" -A Win32
cmake --build . --config Release
```

Output: `build/Release/topo.dll`

### Build gbengine.dll

```bash
mkdir build && cd build
cmake .. -DBUILD_TARGET=gbengine -G "Visual Studio 17 2022" -A Win32
cmake --build . --config Release
```

Output: `build/Release/gbengine.dll`

## System Requirements

- CMake 3.10 or later
- Visual Studio 2022 (or MSVC 19.x)
- Windows 10 SDK
- DirectX SDK (optional for topo.dll, required for PAL3.exe and gbengine.dll)

### DirectX SDK Setup

Set the `DXSDK_DIR` environment variable to your DirectX SDK location:

```bash
set DXSDK_DIR=C:\DXSDK
```

Or let the FindDirectX module search standard locations:
- `C:\DXSDK`
- `D:\DXSDK`
- `C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)`
- `C:\Program Files (x86)\Microsoft DirectX SDK (August 2007)`

## Compiler Flags

### All Targets
- `/nologo` - Suppress compiler banner
- `/W3` - Warning level 3
- `/Gd` - `__cdecl` calling convention
- `/GS-` - Disable buffer overflow checks (matching original)
- `/Zp4` - Struct packing 4 bytes

### topo.dll / gbengine.dll (VC6 style)
- `/GX` - C++ exception handling (VC6 style)
- `/O2` - Maximum speed optimization
- `/Ob1` - Inline function expansion (suitable only)
- `/Oi` - Enable intrinsic functions
- `/Ot` - Favor speed over size
- `/Oy` - Omit frame pointers
- `/GF` - String pooling
- `/Gy` - Function-level linking
- `/MD` - Multi-threaded DLL runtime

### PAL3.exe (VC7 style)
- `/EHsc` - C++ exception handling (VC7 style)
- `/GR` - Runtime type information (RTTI)
- `/O2` - Maximum speed optimization
- `/Ob2` - Inline function expansion (any suitable)
- `/Oi` - Enable intrinsic functions
- `/Ot` - Favor speed over size
- `/Oy` - Omit frame pointers
- `/GF` - String pooling
- `/Gy` - Function-level linking
- `/MD` - Multi-threaded DLL runtime

## Output Directories

All build output goes to `build/`:
- `build/Release/` - Release build output
- `build/Debug/` - Debug build output (if configured)
- `build/asm/` - Generated assembly listings (if enabled)

## Module Organization

### Root CMakeLists.txt (`CMakeLists.txt`)
- Compiler detection
- Build target selection
- Global compiler flags
- Platform libraries

### MSVC Settings (`cmake/MSVCSettings.cmake`)
- MSVC-specific compiler options
- Release/Debug configuration
- Linker flags

### DirectX Finder (`cmake/FindDirectX.cmake`)
- Locates DirectX SDK
- Sets include paths and libraries

### PAL3 Sub-project (`src/pal3/CMakeLists.txt`)
- PAL3.exe target definition
- DirectX linking
- WinMain entry point
- Assembly generation

## Source File Organization

```
src/pal3/
├── main.cpp           # WinMain entry point (Phase 0 stub)
├── CMakeLists.txt     # Build configuration
```

Future phases will add:
```
src/pal3/
├── framework/         # Phase 1: Window, DirectX init
├── script/            # Phase 2: SCE VM
├── ui/                # Phase 3: UI system
├── battle/            # Phase 4: Combat system
├── scene/             # Phase 5: Scene management
├── save/              # Phase 6: Save/load
└── other/             # Phase 7: Audio, items, NPCs
```

## Development Workflow

### Phase 0 (Current)
- CMake build system: DONE
- WinMain stub: DONE
- Compilation verification: DONE

### Phase 1 (Next)
- Window initialization
- DirectX 9 setup
- Game loop framework
- Message loop

### Phase 2-7
- Additional subsystems added incrementally

## Troubleshooting

### CMake: DirectX SDK not found
```
CMake Error: DirectX SDK not found
```
Solution: Set `DXSDK_DIR` environment variable

### Linker Error: Unresolved external symbol _main
```
error LNK2019: unresolved external symbol _main
```
Solution: Use `/SUBSYSTEM:WINDOWS` and `/ENTRY:WinMainCRTStartup` (already set)

### Warning: Modern MSVC detected
```
CMake Warning: Modern MSVC detected (version 1943). Binary matching NOT guaranteed.
```
This is expected when using Visual Studio 2022. For byte-exact matching, use MSVC 7.1 (VS2003).

## References

- CMake Documentation: https://cmake.org/documentation/
- MSVC Compiler Options: https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options
- DirectX 9 Documentation: DirectX SDK Summer 2003 docs

## Notes

- The original PAL3.exe was compiled with MSVC 7.0/7.1 (VS2003)
- The build system has been tested with Visual Studio 2022 (MSVC 19.43)
- For 100% byte-matching, exact compiler version matching is required
- Current setup prioritizes building functional code over byte-exact matching
