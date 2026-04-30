# PAL3 topo.dll Decompilation Status

**Date**: 2026-05-01  
**Status**: ✅ **Build System Working** | 🚧 **27% Complete**

---

## Summary

Successfully established a working build pipeline for matching decompilation of topo.dll.
The project can now compile 114 out of 414 functions, generating a functional 96KB DLL.

## Achievements

### 1. Build System ✅
- **Compiler**: MSVC 2022 (testing mode, targeting MSVC 6.0 compatibility)
- **Output**: topo.dll (96,768 bytes)
- **Status**: Compiles successfully with all major classes
- **Warnings**: `/GX` deprecated (use `/EHsc`), but functional

### 2. Core Math Classes ✅
All major mathematical classes are implemented with member functions:

| Class | Functions | Status |
|-------|-----------|--------|
| gbVec3D | 18/18 | ✅ Complete |
| gbMatrix4 | 35/?? | 🚧 Partial |
| gbQuaternion | 32/?? | 🚧 Partial |
| gbMatrixStack | 15/?? | 🚧 Partial |
| gbRotMatrix | 7/?? | 🚧 Partial |

### 3. API Functions ✅
- `CreateTopoGeom` (0x100034B0, 185 bytes)
- `DestroyTopoGeom` (0x10003570, 12 bytes)

### 4. Toolchain 🛠️
- **Build**: `./run_verify.bat` - One-command build verification
- **Progress**: `python tools/progress_report.py` - Detailed status
- **Compare**: `python tools/compare_function.py <addr> <size>` - Binary matching
- **Docs**: `docs/decompilation_workflow.md` - Complete workflow guide

---

## Current Limitations

### 1. Stub Implementations (3 items)
```
[HIGH] TopoFaceVector_Insert (0x10008940, 714 bytes)
       - Complex STL-like vector::insert implementation
       - Called by TopoGeom_Init
       - Required for full functionality
       
[HIGH] vtable pointers (vtbl_TopoGeomSimple, vtbl_TopoGeomComplex)
       - Currently NULL stubs
       - Need actual virtual function table definitions
       - Required for polymorphism
       
[MED]  Various FUN_* helper functions
       - Internal utility functions
       - May be needed for complex operations
```

### 2. Remaining Functions (300)
Breakdown of unimplemented functions:

| Category | Estimated Count | Priority |
|----------|----------------|----------|
| C Runtime Library | ~80 | Low (use MSVC CRT) |
| Exception Handling (Unwind) | ~60 | Low (compiler-generated) |
| Internal Helpers (FUN_*) | ~100 | Medium |
| Math Operations | ~40 | High |
| TopoGeom Methods | ~20 | High |

### 3. Binary Matching
- No byte-level verification done yet
- Functions may compile but not match original binary exactly
- Compiler differences (MSVC 6.0 vs 2022) affect code generation

---

## Next Steps

### Phase 1: Core Functionality (Priority: HIGH)
**Goal**: Implement critical functions for TopoGeom to work

1. **Implement TopoFaceVector_Insert** (0x10008940)
   - Study Ghidra decompilation carefully
   - Match assembly instruction-by-instruction
   - Test with TopoGeom_Init

2. **Define vtables**
   - Analyze original binary for vtable layout
   - Define virtual methods for ITopoGeom interface
   - Update CreateTopoGeom to use real vtables

3. **Implement remaining TopoGeom methods**
   - Look for FUN_* functions called by TopoGeom_Init
   - Implement in topo_internal.cpp

**Expected outcome**: CreateTopoGeom/DestroyTopoGeom fully functional

### Phase 2: Math Library Completion (Priority: MEDIUM)
**Goal**: Complete all mathematical operations

1. **Find unimplemented math functions**
   ```bash
   python -c "
   # Script to find unimplemented gbVec3D/gbMatrix4/gbQuaternion functions
   "
   ```

2. **Implement by size** (easiest first)
   - Start with < 30 byte functions
   - Move to 30-60 byte functions
   - Tackle complex functions (> 60 bytes) last

3. **Verify binary matching**
   ```bash
   for addr in <implemented_addresses>; do
       python tools/compare_function.py $addr <size>
   done
   ```

**Expected outcome**: All math classes 100% implemented

### Phase 3: Binary Matching (Priority: HIGH)
**Goal**: Achieve byte-perfect matching with original DLL

1. **Setup comparison infrastructure**
   - Extract original topo.dll to `original/`
   - Create batch comparison script

2. **For each function**:
   ```
   a. Compare binary output
   b. If not matching:
      - Analyze assembly differences
      - Adjust C code (reorder variables, change expressions)
      - Adjust compiler flags if needed
   c. Iterate until 100% match
   ```

3. **Document patterns**
   - Record successful matching techniques
   - Note MSVC 6.0 vs 2022 differences
   - Update `docs/decompilation_workflow.md`

**Expected outcome**: All implemented functions match original binary

### Phase 4: Remaining Functions (Priority: LOW)
**Goal**: Complete the entire DLL

1. **CRT functions**: Link against MSVC 6.0 CRT instead of reimplementing
2. **Exception handling**: Use compiler-generated code
3. **Helper functions**: Implement as discovered needed

**Expected outcome**: 100% function coverage, fully working DLL

---

## Resource Requirements

### Tools Needed
- ✅ Ghidra (for analysis)
- ✅ MSVC 2022 (currently used)
- ⚠️ MSVC 6.0 SP5 (for binary-exact matching) - optional but recommended
- ✅ Python 3.x (for tooling)
- ✅ Git (for version control)

### Knowledge Required
- x86 Assembly (reading Ghidra output)
- C/C++ (implementing functions)
- MSVC compiler behavior (optimization, calling conventions)
- PE format (DLL structure, vtables)

### Time Estimates
Based on current progress (114 functions in ~X time):

| Phase | Functions | Est. Time | Notes |
|-------|-----------|-----------|-------|
| Phase 1 | ~25 functions | 2-3 days | Critical path, high complexity |
| Phase 2 | ~80 functions | 5-7 days | Medium complexity, parallelizable |
| Phase 3 | 114 functions | 7-10 days | Iterative matching, time-consuming |
| Phase 4 | ~95 functions | 3-5 days | Low complexity, may skip some |
| **Total** | **~300 functions** | **17-25 days** | Assuming focused work |

---

## Success Criteria

### Minimum Viable Product (MVP)
- [x] topo.dll compiles successfully
- [ ] CreateTopoGeom/DestroyTopoGeom fully functional
- [ ] All math classes (gbVec3D, gbMatrix4, etc.) complete
- [ ] Basic tests pass (if available)

### Full Release
- [ ] All 414 functions implemented
- [ ] Binary-perfect match on critical functions (>80%)
- [ ] Can replace original topo.dll in PAL3
- [ ] No crashes or functional regressions

### Stretch Goals
- [ ] 100% binary match on all functions
- [ ] Comprehensive test suite
- [ ] Documentation of all reverse-engineered structures
- [ ] gbengine.dll and PAL3.exe started

---

## References

- **Main Doc**: `docs/decompilation_workflow.md`
- **Project Context**: `CLAUDE.md`
- **Progress Script**: `python tools/progress_report.py`
- **Comparison Tool**: `python tools/compare_function.py`
- **Build**: `./run_verify.bat`

---

## Contact & Collaboration

This is an open reverse engineering project for preservation and education.

**Contributing**:
1. Pick a function from `asm/topo/*.json`
2. Follow `docs/decompilation_workflow.md`
3. Submit PR with matching implementation
4. Include binary comparison results

**Need Help**:
- Join project discussion (if available)
- Check existing docs first
- Ask specific technical questions with context

---

*Last Updated: 2026-05-01*  
*Next Review: After Phase 1 completion*
