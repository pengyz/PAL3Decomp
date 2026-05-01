# PAL3 Decompilation Tools Guide

This document describes the tools available for tracking progress and verifying binary matching in the PAL3 decompilation project.

## Progress Tracking Tools

### progress_pal3.py - PAL3.exe Progress Tracker

Track decompilation progress for PAL3.exe by scanning source files and comparing against exported function lists.

**Location:** `tools/progress_pal3.py`

**Usage:**
```bash
# Basic progress report
python tools/progress_pal3.py

# Detailed function list
python tools/progress_pal3.py --detail

# Show breakdown by module
python tools/progress_pal3.py --by-module

# Show both detail and module breakdown
python tools/progress_pal3.py --detail --by-module
```

**Features:**
- Scans all C/C++ source files in `src/pal3/` for implemented functions
- Detects function address comments (e.g., `// 0x00401000`)
- Identifies stub implementations and TODO markers
- Compares against Ghidra exported function list (if available)
- Reports overall progress, quality metrics, and per-module breakdown

**Output:**
- Total implemented functions vs. target count
- Complete vs. stub implementations
- Functions with TODO markers
- Per-module statistics
- Actionable next steps

### progress_report.py - topo.dll Progress Tracker

Similar to `progress_pal3.py` but specifically for topo.dll functions.

**Location:** `tools/progress_report.py`

**Usage:**
```bash
python tools/progress_report.py
```

## Binary Comparison Tools

### compare_exe.py - PAL3.exe Binary Comparison Tool

Compare compiled PAL3.exe against the original binary at specific function addresses to verify byte-perfect matching.

**Location:** `tools/compare_exe.py`

**Usage:**

**Single Function Comparison:**
```bash
# Compare function at address 0x00401000 with size 128 bytes
python tools/compare_exe.py --address 0x00401000 --size 128

# With verbose output (detailed hex diff)
python tools/compare_exe.py --address 0x00401000 --size 128 --verbose

# Custom paths
python tools/compare_exe.py \
    --original original/PAL3.exe \
    --compiled build/pal3_build/Release/PAL3.exe \
    --address 0x00401000 \
    --size 128
```

**Batch Comparison:**
```bash
# Compare multiple functions from JSON file
python tools/compare_exe.py --batch functions.json
```

**Batch JSON Format:**
```json
[
    {
        "name": "WinMain",
        "address": "0x00401000",
        "size": 256
    },
    {
        "name": "InitGame",
        "address": "0x00401100",
        "size": 512
    }
]
```

**Features:**
- Full PE file parsing with section table support
- Automatic RVA to file offset conversion
- Byte-by-byte comparison with match rate calculation
- Colored diff output highlighting differences
- Batch mode for comparing multiple functions
- Handles both RVA and absolute addresses

**Exit Codes:**
- 0: Perfect match (single mode) or all functions matched (batch mode)
- 1: Mismatch found

### compare_function.py - topo.dll Function Comparison

Similar to `compare_exe.py` but specifically for topo.dll functions.

**Location:** `tools/compare_function.py`

**Usage:**
```bash
python tools/compare_function.py 0x10001110 64
```

## Typical Workflow

### 1. Initial Setup
```bash
# Check overall progress
python tools/progress_pal3.py

# If Ghidra analysis not done yet:
python tools/ghidra_export.py --target PAL3.exe
```

### 2. Implementing Functions
```bash
# Work on src/pal3/main.cpp, add functions with address comments:
# // 0x00401000
# int WINAPI WinMain(...) { ... }

# Check progress after implementation
python tools/progress_pal3.py --detail
```

### 3. Verifying Implementation
```bash
# Build the project
cmake --build build --config Release

# Compare specific function
python tools/compare_exe.py --address 0x00401000 --size 256

# If not matching, iterate on implementation and recompile
```

### 4. Batch Verification
```bash
# Create batch file of completed functions
cat > completed_functions.json << EOF
[
    {"name": "WinMain", "address": "0x00401000", "size": 256},
    {"name": "InitDirectX", "address": "0x00401200", "size": 384}
]
EOF

# Run batch comparison
python tools/compare_exe.py --batch completed_functions.json
```

### 5. Progress Tracking
```bash
# Regular progress checks
python tools/progress_pal3.py --by-module

# Detailed analysis
python tools/progress_pal3.py --detail --by-module
```

## Tips

### For compare_exe.py
1. Always rebuild before comparing: `cmake --build build --config Release`
2. Use `--verbose` to see detailed hex diff when debugging mismatches
3. Address can be specified as hex (0x00401000) or decimal (4198400)
4. The tool automatically handles PE image base differences
5. Batch mode is useful for regression testing

### For progress_pal3.py
1. Use address comments consistently: `// 0x00401000` on the line before function
2. Mark incomplete work with TODO, STUB, or FIXME comments
3. Run regularly to track progress over time
4. Use `--detail` to see which functions are stubs vs. complete
5. Use `--by-module` to identify which modules need more work

## Troubleshooting

### "Original file not found"
- Ensure PAL3.exe is placed in `original/` directory
- Check file permissions

### "Compiled file not found"
- Build the project first: `cmake --build build --config Release`
- Check build configuration matches path (Debug vs Release)

### "Could not read bytes from PE"
- Verify the address is valid (within .text section)
- Check function size is correct
- RVA might be outside any section (padding area)

### "No function exports found"
- Run Ghidra analysis first: `python tools/ghidra_export.py`
- The progress tracker will still work, just won't show baseline

## Related Tools

- `run.py compare` - Legacy comparison tool
- `verify_build.py` - Build verification for topo.dll
- `tools/compare_function.py` - topo.dll specific comparison
- `tools/progress.py` - Legacy progress tracking

## See Also

- [Decompilation Workflow](decompilation_workflow.md) - Complete decompilation process
- [Build System Guide](../BUILD_SYSTEM_GUIDE.md) - CMake build setup
- [Compiler Setup](compiler_setup.md) - MSVC toolchain configuration
