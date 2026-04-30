# Decompilation Workflow Guide

## Overview

This document describes the workflow for matching decompilation of PAL3 topo.dll.
The goal is to produce C/C++ code that compiles to byte-identical machine code.

## Current Status (as of 2026-05-01)

```
Implemented: 114/414 functions (27%)
Build status: ✅ Compiles successfully
Binary size: 96,768 bytes
```

## Workflow Steps

### 1. Choose a Function to Decompile

```bash
# View progress report
python tools/progress_report.py

# List available JSON exports
ls asm/topo/*.json | head -20

# Pick a function based on:
# - Complexity (start with smaller functions)
# - Dependencies (implement called functions first)
# - Priority (exported/public API functions first)
```

### 2. Analyze the Ghidra Export

```bash
# Read the function's JSON data
cat asm/topo/FunctionName_address.json | jq .
```

The JSON contains:
- `address`: Function start address (RVA)
- `size_bytes`: Function size
- `signature`: Function signature with types
- `decompiled_c`: Ghidra's C pseudocode
- `assembly`: Raw x86 assembly listing
- `callees`: Functions this function calls
- `callers`: Functions that call this function

### 3. Implement in C/C++

#### Create or update the appropriate source file:

```cpp
// src/topo/gbMatrix4.cpp

// ============================================================================
// 0x10001110  gbMatrix4()  (12 bytes)
// public: __thiscall gbMatrix4::gbMatrix4(void)
// ============================================================================
gbMatrix4::gbMatrix4(void)
{
    LoadIdentity();
}
```

#### Key principles:

1. **Preserve exact structure**: Use Ghidra's control flow structure
2. **Match types**: Ensure types match assembly (int vs uint, pointer sizes)
3. **Calling convention**: __cdecl, __thiscall, __fastcall must match
4. **Local variable order**: Affects stack layout
5. **Expression form**: `if (ptr)` vs `if (ptr != NULL)` generates different code

### 4. Compile and Test

```bash
# Build the DLL
./run_verify.bat

# Check for errors
echo $?  # Should be 0 on success
```

### 5. Compare Binary Output

```bash
# Compare specific function
python tools/compare_function.py 0x10001110 12

# Expected output:
# Match rate: 12/12 bytes (100.0%)
# ✓ PERFECT MATCH!
```

### 6. Iterate Until Match

If not matching:

#### Common causes:
- **Wrong optimization level**: /O1 vs /O2 affects code generation
- **Compiler version mismatch**: MSVC 6.0 vs MSVC 2022 differences
- **Calling convention**: Missing __thiscall, __fastcall annotations
- **Register allocation**: Try reordering local variables
- **Constant folding**: Compiler may optimize constants differently
- **Padding/alignment**: struct packing affects layout

#### Debugging steps:
1. Generate assembly listing: `/FA` flag in CMakeLists.txt
2. Compare assembly: `diff original.asm compiled.asm`
3. Look for instruction pattern differences
4. Adjust C code to guide compiler

### 7. Document and Commit

```bash
# Stage changes
git add src/topo/filename.cpp

# Commit with function info
git commit -m "Implement FunctionName (0x10001110, 12 bytes)

- Matches original binary exactly
- Verified with compare_function.py
- Dependencies: LoadIdentity()
"
```

## Tips for Matching

### Compiler Quirks

#### MSVC 6.0 specifics:
```cpp
// Use old-style for loops for better matching
for (int i = 0; i != count; i++)  // Better than i < count
    
// Prefer pointer arithmetic over array indexing
*pDst++ = *pSrc++;  // Better than dst[i] = src[i]

// Use explicit casts
(float)sqrt(x)  // Not just sqrt(x)
```

### Common Patterns

#### Memory copy loops:
```cpp
// Pattern 1: Manual loop (12 dwords)
for (int i = 12; i != 0; i--) {
    *pDst++ = *pSrc++;
}

// Pattern 2: REP MOVSD equivalent
memcpy(dst, src, 48);  // May not match! Use manual loop
```

#### Conditional assignment:
```cpp
// Pattern 1: Ternary (may generate different code)
result = (x > 0) ? a : b;

// Pattern 2: If-else (more predictable)
if (x > 0) {
    result = a;
} else {
    result = b;
}
```

## Testing Checklist

Before marking a function as complete:

- [ ] Compiles without errors or warnings
- [ ] Function signature matches JSON export
- [ ] Byte-perfect match with original binary
- [ ] All dependencies are implemented
- [ ] Comments include address and size
- [ ] Calling convention is correct
- [ ] Local variable types are accurate

## Priority Queue

### High Priority (Exported/Public API):
1. CreateTopoGeom (0x100034B0)
2. DestroyTopoGeom (0x10003570)
3. TopoGeom_Init (0x10007620)

### Medium Priority (Internal but commonly used):
1. TopoFaceVector_Insert (0x10008940) - 714 bytes, complex
2. gbMatrix4 operations (various)
3. gbVec3D operations (various)

### Low Priority (Utilities):
1. Helper functions
2. Internal constructors
3. Rarely called functions

## References

- **Ghidra exports**: `asm/topo/*.json`
- **Original structs**: `docs/community_structs.md`
- **Compiler docs**: VS2003/MSVC 6.0 documentation
- **PAL3patch**: `/tmp/PAL3patch/src/PAL3patch/include/`

## Getting Help

Common issues:

1. **Can't match a function**: Try different optimization flags, reorder code
2. **Linker errors**: Check for missing extern declarations
3. **Crashes at runtime**: Verify struct layouts match original
4. **Wrong calling convention**: Check __thiscall vs __cdecl vs __fastcall

Document your findings in `docs/decompilation_notes.md` for future reference.
