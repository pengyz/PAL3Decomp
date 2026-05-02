# gbengine.dll Architecture Cleanup Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Eliminate `/FORCE` linking from gbengine.dll by auto-generating stub functions for 626 unresolved symbols, then relocate functions from gbengine_exports.cpp to proper source files.

**Architecture:** Python script parses demangled C++ signatures from unresolved.txt, groups by class, generates stub source files with correct signatures and minimal bodies. CMake is updated to include stubs directory and remove /FORCE flag.

**Tech Stack:** Python 3 (code generation), CMake, MSVC (32-bit)

---

### Task 1: Create stub generation script (tools/gen_unresolved_stubs.py)

**Files:**
- Create: `tools/gen_unresolved_stubs.py`

- [ ] **Step 1: Write the stub generator script**

```python
#!/usr/bin/env python3
"""
Generate C++ stub source files from unresolved.txt.
Parses MSVC demangled signatures, groups by class, generates minimal stub implementations.
"""
import re
import os
import sys
from collections import defaultdict

UNRESOLVED_FILE = "unresolved.txt"
OUTPUT_DIR = "src/gbengine/stubs"

# Parse one line of unresolved.txt: "demangled sig" (mangled_name)
LINE_RE = re.compile(r'^"(.+)"\s+\(([^)]+)\)$')

# Parse demangled signature components
# Examples:
#   "public: __thiscall gbCamera::gbCamera(class gbGfxManager *)"
#   "public: void __thiscall gbCamera::SetFov(float)"
#   "public: bool __thiscall gbMatrix4::IsIdentity(void)const "
#   "char * __cdecl gbVfgetdir(char const *,char *,int)"
#   "const gbBinaryTreeNode::`vftable'"
MEMBER_RE = re.compile(
    r'^(public|private|protected):\s+'
    r'(.*?)\s*'  # return type (may be empty for ctors/dtors)
    r'__thiscall\s+'
    r'(\w+)::(.+)$'  # class::rest
)
FREE_FN_RE = re.compile(
    r'^(.*?)\s*'  # return type
    r'__cdecl\s+'
    r'(\w+)\((.+)\)$'  # name(params)
)
VFTABLE_RE = re.compile(r"^const (\w+)::`vftable'$")
STATIC_DATA_RE = re.compile(
    r'^(public|private|protected):\s+static\s+(.+?)\s+(\w+)::(\w+)$'
)

def parse_return_type_and_name(rest):
    """Parse 'RetType ClassName::FuncName(params)' or 'ClassName::~ClassName()'"""
    # Check for const suffix
    is_const = False
    if rest.endswith('const '):
        is_const = True
        rest = rest[:-6]
    elif rest.endswith('const'):
        is_const = True
        rest = rest[:-5]

    # Find the function name and params
    paren_start = rest.rfind('(')
    if paren_start == -1:
        return rest, '', '', False
    
    params_str = rest[paren_start+1:]
    if params_str.endswith(')'):
        params_str = params_str[:-1]
    
    name_part = rest[:paren_start]
    return name_part, params_str, '', is_const

def get_default_return(return_type):
    """Generate default return statement for a given type."""
    rt = return_type.strip()
    if not rt or rt == 'void':
        return ''
    if '*' in rt:
        return 'return 0;'
    if '&' in rt:
        # Reference return - need a static instance
        base_type = rt.replace('&', '').strip()
        if base_type.startswith('class '):
            base_type = base_type[6:]
        elif base_type.startswith('struct '):
            base_type = base_type[7:]
        return f'static {base_type} _dummy; return _dummy;'
    if rt in ('int', 'long', 'unsigned int', 'unsigned long', 'short', 'unsigned short'):
        return 'return 0;'
    if rt in ('bool', 'bool const'):
        return 'return false;'
    if rt in ('float',):
        return 'return 0.0f;'
    if rt in ('double',):
        return 'return 0.0;'
    if rt in ('char', 'unsigned char'):
        return 'return 0;'
    # Enum or unknown
    return 'return 0;'

def normalize_type(t):
    """Normalize type for C++ declaration (remove 'class '/'struct ' prefixes for known types)."""
    t = t.strip()
    # Keep 'struct' for POD types but remove 'class' prefix
    t = re.sub(r'\bclass\s+', '', t)
    t = re.sub(r'\bstruct\s+', '', t)
    # Fix 'const' placement
    t = t.strip()
    return t

def parse_params(params_str):
    """Parse parameter list string into C++ parameter declarations."""
    if params_str.strip() == 'void' or params_str.strip() == '':
        return ''
    
    # Split by comma, handling nested templates/types
    params = []
    depth = 0
    current = ''
    for ch in params_str:
        if ch in ('(', '<'):
            depth += 1
            current += ch
        elif ch in (')', '>'):
            depth -= 1
            current += ch
        elif ch == ',' and depth == 0:
            params.append(current.strip())
            current = ''
        else:
            current += ch
    if current.strip():
        params.append(current.strip())
    
    # Generate parameter declarations with names
    result = []
    for i, p in enumerate(params):
        p = normalize_type(p)
        result.append(f'{p} p{i+1}')
    
    return ', '.join(result)

def generate_stub_for_entry(demangled, mangled):
    """Generate a stub function/declaration for one unresolved symbol."""
    
    # Check for vftable
    m = VFTABLE_RE.match(demangled)
    if m:
        return None, m.group(1), 'vftable'
    
    # Check for static data member
    m = STATIC_DATA_RE.match(demangled)
    if m:
        access, data_type, class_name, member_name = m.groups()
        data_type = normalize_type(data_type)
        return f'{data_type} {class_name}::{member_name};', class_name, 'static_data'
    
    # Check for free function
    m = FREE_FN_RE.match(demangled)
    if m:
        ret_type, func_name, params = m.groups()
        ret_type = normalize_type(ret_type)
        params = parse_params(params)
        ret_stmt = get_default_return(ret_type)
        body = f' {ret_stmt} ' if ret_stmt else ' '
        return f'{ret_type} __cdecl {func_name}({params}) {{{body}}}', '__globals__', 'free_fn'
    
    # Check for member function
    m = MEMBER_RE.match(demangled)
    if m:
        access, prefix, class_name, rest = m.groups()
        
        # Parse rest: could be "RetType FuncName(params)" or "ClassName(params)" or "~ClassName()"
        rest = rest.strip()
        is_const = rest.endswith('const ') or rest.endswith('const')
        if is_const:
            rest = rest.rstrip()
            if rest.endswith('const'):
                rest = rest[:-5].rstrip()
        
        # Find params
        paren_start = rest.rfind('(')
        if paren_start == -1:
            return None, class_name, 'unknown'
        
        params_str = rest[paren_start+1:]
        if params_str.endswith(')'):
            params_str = params_str[:-1]
        
        name_part = rest[:paren_start].strip()
        
        # Determine if constructor, destructor, or normal method
        is_ctor = False
        is_dtor = False
        return_type = ''
        func_name = ''
        
        if name_part == class_name or name_part == '':
            is_ctor = True
            func_name = class_name
        elif name_part == f'~{class_name}':
            is_dtor = True
            func_name = f'~{class_name}'
        elif name_part.startswith('virtual __thiscall '):
            # "virtual __thiscall ClassName::~ClassName()"
            inner = name_part[len('virtual __thiscall '):]
            if inner == f'~{class_name}':
                is_dtor = True
                func_name = f'~{class_name}'
            else:
                func_name = inner
        elif name_part.startswith('virtual '):
            # "virtual void __thiscall ClassName::Func()"
            remaining = name_part[len('virtual '):]
            func_name = remaining
        else:
            # "RetType FuncName" or just "FuncName" or operator
            # Split: everything before last word is return type
            # But it could be "operator==" or "operator[]" etc.
            if 'operator' in name_part:
                # Find 'operator' and split there
                op_idx = name_part.find('operator')
                return_type = name_part[:op_idx].strip()
                func_name = name_part[op_idx:]
            else:
                parts = name_part.rsplit(' ', 1)
                if len(parts) == 2:
                    return_type = parts[0]
                    func_name = parts[1]
                else:
                    func_name = parts[0]
        
        # Handle prefix containing return type + virtual
        if not return_type and prefix:
            prefix = prefix.strip()
            if prefix.startswith('virtual '):
                prefix = prefix[8:]
            if prefix.startswith('static '):
                prefix = prefix[7:]
            return_type = prefix
        
        # Normalize
        return_type = normalize_type(return_type)
        params_decl = parse_params(params_str)
        const_suffix = ' const' if is_const else ''
        
        # Generate stub
        if is_ctor:
            return f'{class_name}::{class_name}({params_decl}) {{}}', class_name, 'ctor'
        elif is_dtor:
            virtual_prefix = 'virtual ' if 'virtual' in demangled else ''
            return f'{class_name}::~{class_name}() {{}}', class_name, 'dtor'
        else:
            ret_stmt = get_default_return(return_type)
            body = f' {ret_stmt} ' if ret_stmt else ' '
            ret_decl = f'{return_type} ' if return_type else 'void '
            return f'{ret_decl}{class_name}::{func_name}({params_decl}){const_suffix} {{{body}}}', class_name, 'method'
    
    # Fallback: couldn't parse
    return f'// UNPARSED: {demangled}', '__unparsed__', 'unknown'

def main():
    if not os.path.exists(UNRESOLVED_FILE):
        print(f"Error: {UNRESOLVED_FILE} not found")
        sys.exit(1)
    
    # Parse all entries
    entries = defaultdict(list)  # class_name -> [(stub_code, kind)]
    vftable_classes = set()
    
    with open(UNRESOLVED_FILE, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            m = LINE_RE.match(line)
            if not m:
                print(f"WARNING: Could not parse line: {line}")
                continue
            demangled, mangled = m.groups()
            
            stub_code, class_name, kind = generate_stub_for_entry(demangled, mangled)
            
            if kind == 'vftable':
                vftable_classes.add(class_name)
            elif stub_code:
                entries[class_name].append((stub_code, kind))
    
    # Create output directory
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    
    # Generate stub files per class
    files_written = 0
    for class_name, stubs in sorted(entries.items()):
        if class_name == '__globals__':
            filename = 'stub_globals.cpp'
        elif class_name == '__unparsed__':
            filename = 'stub_unparsed.cpp'
        else:
            filename = f'stub_{class_name}.cpp'
        
        filepath = os.path.join(OUTPUT_DIR, filename)
        
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write('#include "pal3.h"\n')
            f.write('#pragma optimize("", off)\n\n')
            
            for stub_code, kind in stubs:
                f.write(stub_code + '\n\n')
        
        files_written += 1
        print(f"  Generated: {filepath} ({len(stubs)} stubs)")
    
    # Report vftable classes that need virtual method definitions
    if vftable_classes:
        print(f"\nVFTABLE classes (need at least one virtual method in a .cpp file):")
        for cls in sorted(vftable_classes):
            print(f"  - {cls}")
    
    print(f"\nDone: {files_written} files, {sum(len(s) for s in entries.values())} total stubs")
    print(f"Output directory: {OUTPUT_DIR}")

if __name__ == '__main__':
    main()
```

- [ ] **Step 2: Run the generator and verify output**

Run: `python tools/gen_unresolved_stubs.py`
Expected: ~50+ stub files generated in src/gbengine/stubs/

- [ ] **Step 3: Review generated stubs for obvious parse errors**

Run: `grep -r "UNPARSED" src/gbengine/stubs/`
Expected: Few or no unparsed entries. Fix parser for any missed patterns.

- [ ] **Step 4: Commit generator script**

```bash
git add tools/gen_unresolved_stubs.py
git commit -m "Add stub generation script for unresolved gbengine symbols"
```

---

### Task 2: Generate and integrate stub files

**Files:**
- Create: `src/gbengine/stubs/*.cpp` (generated)
- Modify: `CMakeLists.txt:99-139`

- [ ] **Step 1: Run the generator**

```bash
python tools/gen_unresolved_stubs.py
```

- [ ] **Step 2: Update CMakeLists.txt to include stubs and remove /FORCE**

Replace the gbengine section in CMakeLists.txt:

```cmake
elseif(BUILD_TARGET STREQUAL "gbengine")
    message(STATUS "Configuring gbengine.dll build")
    file(GLOB_RECURSE GBENGINE_SOURCES "src/gbengine/*.cpp" "src/gbengine/*.c")

    if(GBENGINE_SOURCES)
        add_library(gbengine SHARED ${GBENGINE_SOURCES})
        target_include_directories(gbengine PUBLIC include)
        set_target_properties(gbengine PROPERTIES
            OUTPUT_NAME "gbengine"
            PREFIX ""
            SUFFIX ".dll"
        )

        # Link DirectX and other dependencies
        target_link_libraries(gbengine ${PLATFORM_LIBS}
            ${CMAKE_SOURCE_DIR}/lib/ijl15.lib
        )

        # Use .def file for exports (matching original DLL export table)
        # No /FORCE needed - all symbols have definitions
        set_target_properties(gbengine PROPERTIES
            LINK_FLAGS "/DEF:\"${CMAKE_SOURCE_DIR}/src/gbengine/gbengine.def\""
        )

        # Disable inlining for exports file so class-inline methods
        # produce standalone symbols required by the .def exports
        if(MSVC)
            set_source_files_properties(src/gbengine/gbengine_exports.cpp
                PROPERTIES COMPILE_FLAGS "/Ob0"
            )
        endif()

        if(MSVC)
            file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/asm)
            target_compile_options(gbengine PRIVATE /FAcs /Fa${CMAKE_BINARY_DIR}/asm/)
        endif()

        message(STATUS "gbengine.dll: ${CMAKE_CURRENT_LIST_FILE} source files")
    else()
        message(WARNING "No source files found in src/gbengine/")
    endif()
```

Key change: `/FORCE:MULTIPLE` removed from LINK_FLAGS.

- [ ] **Step 3: Build and check for remaining link errors**

```bash
cmake -B build_gbengine -DBUILD_TARGET=gbengine
cmake --build build_gbengine --config Release 2>&1 | grep -c "LNK2001\|LNK2019"
```

Expected: 0 unresolved external errors. If some remain, fix the generator or add manual stubs.

- [ ] **Step 4: Verify exports**

```bash
dumpbin /exports build_gbengine/Release/gbengine.dll | grep -c "ordinal"
```

Expected: Shows 1020 (or 1019 functions + 1 data) exported symbols.

- [ ] **Step 5: Verify no LNK4088 warning**

```bash
cmake --build build_gbengine --config Release 2>&1 | grep "LNK4088"
```

Expected: No output (warning eliminated).

- [ ] **Step 6: Commit stubs and CMake changes**

```bash
git add src/gbengine/stubs/ CMakeLists.txt
git commit -m "Add auto-generated stubs for 626 unresolved symbols, remove /FORCE linking"
```

---

### Task 3: Fix compilation errors in generated stubs

**Files:**
- Modify: `src/gbengine/stubs/*.cpp` (various fixes)
- Possibly modify: `include/gbengine/*.h` (forward declarations)

This task handles the inevitable compilation errors from auto-generated code:
- Missing forward declarations
- Incorrect type parsing (templates, nested types)
- Duplicate definitions (if a symbol was already partially defined elsewhere)

- [ ] **Step 1: Attempt build, capture errors**

```bash
cmake --build build_gbengine --config Release 2>&1 | head -100
```

- [ ] **Step 2: Fix errors iteratively**

Common fixes:
- Add `class X;` forward declarations to stub files
- Fix return type parsing for complex types (e.g., `ID3DXEffect *`)
- Remove stubs that duplicate existing implementations
- Add missing `#include` directives

- [ ] **Step 3: Verify clean build**

```bash
cmake --build build_gbengine --config Release 2>&1 | grep -c "error"
```

Expected: 0 errors.

- [ ] **Step 4: Commit fixes**

```bash
git add -u
git commit -m "Fix compilation errors in generated stubs"
```

---

### Task 4: Handle vtable symbols

**Files:**
- Modify: `src/gbengine/stubs/stub_*.cpp` (affected classes)

11 vtable symbols need resolution. A vtable is emitted when a class has at least one virtual method defined (not inline) in a translation unit.

Classes needing vtables:
- gbBinaryTreeNode
- gbCamControler
- gbCamQuakeControl
- gbCamSpringControl
- gbChain2DNode
- gbDynVertBuf
- gbGeomNode
- gbLightObj
- gbRenderEffect
- gbVolModNode
- gbVolumeModifier

- [ ] **Step 1: Check which classes already have vtables emitted**

```bash
# Build and check which vtable symbols are still unresolved
cmake --build build_gbengine --config Release 2>&1 | grep "vftable"
```

- [ ] **Step 2: For each class still missing a vtable, add a virtual destructor to its stub**

For each class X that still has an unresolved vftable, ensure the stub file has:
```cpp
X::~X() {}
```
(The destructor is virtual for all these classes, so defining it produces the vtable.)

- [ ] **Step 3: Verify all vtables resolved**

```bash
cmake --build build_gbengine --config Release 2>&1 | grep "vftable"
```

Expected: No output.

- [ ] **Step 4: Commit**

```bash
git add -u
git commit -m "Ensure vtable emission for 11 classes with unresolved vftable symbols"
```

---

### Task 5: Final verification of Phase 1

**Files:** None (verification only)

- [ ] **Step 1: Clean build from scratch**

```bash
rm -rf build_gbengine
cmake -B build_gbengine -DBUILD_TARGET=gbengine
cmake --build build_gbengine --config Release
```

- [ ] **Step 2: Verify zero link errors/warnings**

```bash
cmake --build build_gbengine --config Release 2>&1 | grep -c "LNK2001\|LNK2019\|LNK4088\|FORCE"
```

Expected: 0

- [ ] **Step 3: Verify export count**

```bash
dumpbin /exports build_gbengine/Release/gbengine.dll | tail -5
```

Expected: Summary line showing 1020 exports.

- [ ] **Step 4: Run progress script**

```bash
python -X utf8 tools/gbengine_progress.py
```

- [ ] **Step 5: Commit and tag milestone**

```bash
git tag phase1-no-force-linking
```

---

### Task 6: Relocate gbMath functions from gbengine_exports.cpp (129 functions)

**Files:**
- Modify: `src/gbengine/gbMath.cpp`
- Modify: `src/gbengine/gbengine_exports.cpp`

- [ ] **Step 1: Extract math class implementations from gbengine_exports.cpp**

Move all implementations for: gbMatrix4, gbQuaternion, gbRotMatrix, gbVec3D, gbMatrixStack, gbOBBox, gbAABBox, gbSphere, gbPlane, gbRay, BEZIER

Cut from gbengine_exports.cpp and append to gbMath.cpp.

- [ ] **Step 2: Add necessary includes to gbMath.cpp**

Ensure gbMath.cpp has:
```cpp
#include "pal3.h"
#include <math.h>
#include <string.h>
```

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

Expected: Successful build.

- [ ] **Step 4: Commit**

```bash
git add src/gbengine/gbMath.cpp src/gbengine/gbengine_exports.cpp
git commit -m "Move 129 math class functions from exports to gbMath.cpp"
```

---

### Task 7: Relocate gbMisc functions (24 functions)

**Files:**
- Modify: `src/gbengine/gbMisc.cpp`
- Modify: `src/gbengine/gbengine_exports.cpp`

- [ ] **Step 1: Move gbColorFlt, gbColorQuad, gbNameVarBuf, gbTimeCounter, gbPixelFormat implementations**

- [ ] **Step 2: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 3: Commit**

```bash
git add src/gbengine/gbMisc.cpp src/gbengine/gbengine_exports.cpp
git commit -m "Move 24 utility class functions from exports to gbMisc.cpp"
```

---

### Task 8: Relocate gbParticle functions (21 functions)

**Files:**
- Modify: `src/gbengine/gbParticle.cpp`
- Modify: `src/gbengine/gbengine_exports.cpp`

- [ ] **Step 1: Move gbAnimNodeGroup, gbEmitterData, gbEmitterSquare, gbParticleUnit implementations**

- [ ] **Step 2: Build and verify**

- [ ] **Step 3: Commit**

```bash
git add src/gbengine/gbParticle.cpp src/gbengine/gbengine_exports.cpp
git commit -m "Move 21 particle/animation functions from exports to gbParticle.cpp"
```

---

### Task 9: Relocate remaining functions (62 functions across 7 files)

**Files:**
- Modify: `src/gbengine/gbVisNode.cpp` (12 functions: gbVolModNode, gbVolumeModifier, gbLightObj)
- Modify: `src/gbengine/gbCamera.cpp` (9 functions: gbCamera, gbCamControler, gbCamQuakeControl, gbCamSpringControl)
- Modify: `src/gbengine/gbVFileSystem.cpp` (7 functions: gbVTextFile)
- Modify: `src/gbengine/gbTexture.cpp` (6 functions: gbTexture_D3D, gbTextureArray)
- Modify: `src/gbengine/gbGfxManager.cpp` (5 functions: gbEffectMgr, gbGfxManager_D3D, etc.)
- Modify: `src/gbengine/gbGeomNode.cpp` (5 functions)
- Modify: `src/gbengine/gbSceneGraph.cpp` (2 functions)
- Modify: `src/gbengine/gbengine_exports.cpp`

- [ ] **Step 1: Move functions to gbVisNode.cpp**
- [ ] **Step 2: Move functions to gbCamera.cpp**
- [ ] **Step 3: Move functions to gbVFileSystem.cpp**
- [ ] **Step 4: Move functions to gbTexture.cpp**
- [ ] **Step 5: Move functions to gbGfxManager.cpp**
- [ ] **Step 6: Move functions to gbGeomNode.cpp**
- [ ] **Step 7: Move functions to gbSceneGraph.cpp**
- [ ] **Step 8: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 9: Commit**

```bash
git add src/gbengine/*.cpp
git commit -m "Move remaining 62 functions from exports to proper source files"
```

---

### Task 10: Delete gbengine_exports.cpp and clean up CMakeLists.txt

**Files:**
- Delete: `src/gbengine/gbengine_exports.cpp`
- Modify: `CMakeLists.txt`

- [ ] **Step 1: Verify gbengine_exports.cpp is empty (or only has the header)**

```bash
wc -l src/gbengine/gbengine_exports.cpp
```

Expected: Should be near 0 (just includes/pragmas if any).

- [ ] **Step 2: Delete the file**

```bash
rm src/gbengine/gbengine_exports.cpp
```

- [ ] **Step 3: Remove /Ob0 special handling from CMakeLists.txt**

Remove:
```cmake
if(MSVC)
    set_source_files_properties(src/gbengine/gbengine_exports.cpp
        PROPERTIES COMPILE_FLAGS "/Ob0"
    )
endif()
```

- [ ] **Step 4: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 5: Commit**

```bash
git add -A
git commit -m "Remove gbengine_exports.cpp - all functions relocated to proper modules"
```

---

### Task 11: Set up VC6 toolchain directory structure

**Files:**
- Create: `tools/vc6/README.md`
- Create: `cmake/VC6Toolchain.cmake`
- Modify: `.gitignore`

- [ ] **Step 1: Create VC6 directory structure**

```bash
mkdir -p tools/vc6/bin tools/vc6/include tools/vc6/lib
```

- [ ] **Step 2: Create VC6 toolchain CMake file**

```cmake
# cmake/VC6Toolchain.cmake
# Visual C++ 6.0 SP5 Toolchain for binary-exact decompilation builds
#
# Usage:
#   cmake -B build_vc6 -DBUILD_TARGET=gbengine -DCMAKE_TOOLCHAIN_FILE=cmake/VC6Toolchain.cmake
#
# Prerequisites:
#   Extract VC6 SP5 compiler files to tools/vc6/:
#   - tools/vc6/bin/cl.exe, c1.dll, c1xx.dll, c2.dll, link.exe, lib.exe, mspdb60.dll
#   - tools/vc6/include/ (standard headers)
#   - tools/vc6/lib/ (standard libraries)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

# Compiler paths
set(VC6_ROOT "${CMAKE_CURRENT_LIST_DIR}/../tools/vc6")
set(CMAKE_C_COMPILER "${VC6_ROOT}/bin/cl.exe")
set(CMAKE_CXX_COMPILER "${VC6_ROOT}/bin/cl.exe")
set(CMAKE_LINKER "${VC6_ROOT}/bin/link.exe")
set(CMAKE_AR "${VC6_ROOT}/bin/lib.exe")

# Standard include/lib paths
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${VC6_ROOT}/include")
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${VC6_ROOT}/include")
set(CMAKE_FIND_ROOT_PATH "${VC6_ROOT}")

# VC6-specific flags matching original gbengine.dll build
set(CMAKE_C_FLAGS_INIT "/nologo /W3 /GX /O2 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\"")
set(CMAKE_CXX_FLAGS_INIT "/nologo /W3 /GX /O2 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\"")
set(CMAKE_EXE_LINKER_FLAGS_INIT "/nologo /subsystem:windows /machine:I386")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "/nologo /dll /machine:I386")

# Force 32-bit
set(CMAKE_SIZEOF_VOID_P 4)
```

- [ ] **Step 3: Create README for VC6 toolchain setup**

```markdown
# VC6 SP5 Toolchain

This directory should contain extracted VC6 SP5 compiler binaries.

## Required files

### bin/
- cl.exe (compiler driver)
- c1.dll (C frontend)
- c1xx.dll (C++ frontend)
- c2.dll (code generator/optimizer)
- link.exe (linker)
- lib.exe (library manager)
- mspdb60.dll (PDB support)
- msobj10.dll (object file support)

### include/
- C/C++ standard library headers
- windows.h and Windows SDK headers

### lib/
- msvcrt.lib, msvcprt.lib
- kernel32.lib, user32.lib, gdi32.lib, etc.
- oldnames.lib

## How to extract

From a VC6 SP5 installation (or ISO):
1. Use 7-Zip to extract .cab files
2. Copy cl.exe, c1.dll, c1xx.dll, c2.dll, link.exe, lib.exe from VC98/Bin/
3. Copy mspdb60.dll from Common/MSDev98/Bin/
4. Copy VC98/Include/ to include/
5. Copy VC98/Lib/ to lib/

Verify: `tools/vc6/bin/cl.exe /?` should show version 12.00.8804
```

- [ ] **Step 4: Update .gitignore**

Add:
```
tools/vc6/bin/
tools/vc6/include/
tools/vc6/lib/
```

- [ ] **Step 5: Commit**

```bash
git add cmake/VC6Toolchain.cmake tools/vc6/README.md .gitignore
git commit -m "Add VC6 SP5 toolchain structure and CMake integration"
```

---

### Task 12: Final validation

**Files:** None (verification only)

- [ ] **Step 1: Full clean rebuild**

```bash
rm -rf build_gbengine
cmake -B build_gbengine -DBUILD_TARGET=gbengine
cmake --build build_gbengine --config Release
```

- [ ] **Step 2: Verify success criteria**

```bash
# No /FORCE, no link errors
cmake --build build_gbengine --config Release 2>&1 | grep -c "error\|LNK4088"
# Expected: 0

# gbengine_exports.cpp doesn't exist
ls src/gbengine/gbengine_exports.cpp 2>&1
# Expected: No such file

# Export count
dumpbin /exports build_gbengine/Release/gbengine.dll | grep "number of functions"
# Expected: 1020

# Progress report
python -X utf8 tools/gbengine_progress.py
```

- [ ] **Step 3: Tag completion**

```bash
git tag phase2-exports-relocated
```
