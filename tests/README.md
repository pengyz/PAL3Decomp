# PAL3 Decompilation Test Suite

This directory contains automated tests to verify the correctness of the PAL3 decompilation project.

## Overview

The test suite validates three key aspects of the decompilation:

1. **Compilation Tests** (`test_compilation.py`) - Ensures the source code compiles successfully
2. **PE Structure Tests** (`test_pe_structure.py`) - Verifies PE headers match expected structure
3. **Byte Matching Tests** (TODO) - Validates byte-for-byte function matching

## Quick Start

### Install Dependencies

```bash
pip install pytest
# Or install all project requirements:
pip install -r requirements.txt
```

### Run All Tests

```bash
# Windows
tests\run_tests.bat

# Or directly with pytest
python -m pytest tests/ -v
```

### Run Specific Tests

```bash
# Run only compilation tests
python -m pytest tests/test_compilation.py -v

# Run only PE structure tests
python -m pytest tests/test_pe_structure.py -v

# Run tests matching a pattern
python -m pytest tests/ -k "test_cmake" -v
```

## Test Files

### `conftest.py`

Shared pytest configuration and fixtures:
- `project_root` - Path to project root directory
- `original_exe` - Path to original PAL3.exe (skips if missing)
- `original_topo_dll` - Path to original topo.dll (skips if missing)
- `compiled_topo_dll` - Path to compiled topo.dll (skips if missing)
- `compiled_exe` - Path to compiled PAL3.exe (skips if missing)

### `test_compilation.py`

Tests the build system and compilation:

- `test_cmake_configure` - CMake configuration succeeds
- `test_build_release` - Release build completes without errors
- `test_topo_dll_exists` - Output DLL is generated
- `test_topo_dll_size` - Output DLL has reasonable size
- `test_clean_build_warnings` - Build produces minimal warnings

### `test_pe_structure.py`

Tests PE (Portable Executable) structure:

- `test_compiled_topo_is_valid_pe` - Output is valid PE file
- `test_compiled_topo_is_32bit` - Output is 32-bit x86
- `test_compiled_topo_has_code_section` - Has .text section
- `test_original_vs_compiled_machine_type` - Machine type matches
- `test_original_vs_compiled_subsystem` - Subsystem is compatible
- `test_original_vs_compiled_dll_flag` - Both marked as DLL
- `test_compiled_topo_section_count` - Reasonable section count
- `test_compiled_topo_alignment` - Standard section alignment
- `test_original_topo_structure_info` - Display original structure (info)
- `test_compiled_topo_structure_info` - Display compiled structure (info)

### `run_tests.bat`

Convenient batch file to run all tests with proper error handling.

## Test Philosophy

### Graceful Degradation

Tests skip gracefully when prerequisites are missing:
- No original binary? Skip comparison tests
- No compiled output? Skip structure tests
- Build not configured? Skip build tests

This allows the test suite to run in any state of the project.

### Informational Tests

Some tests are informational rather than pass/fail:
- `test_original_topo_structure_info` - Shows original PE structure
- `test_compiled_topo_structure_info` - Shows compiled PE structure

These help with debugging by displaying relevant information.

### Acceptable Differences

The test suite accounts for acceptable differences between VC6 (original) and modern MSVC:
- Subsystem may differ (GUI vs Console for DLLs)
- Section count may differ (extra .rsrc, etc.)
- Entry point addresses will differ

The goal is binary compatibility at the function level, not bit-identical PE structure.

## Current Status

```
✅ 15/15 tests passing
✅ Compilation verification working
✅ PE structure validation working
⏳ Byte matching tests (TODO)
```

## Future Enhancements

1. **Byte Matching Tests**
   - Compare specific functions byte-by-byte
   - Integration with `tools/compare_function.py`
   - Track matching percentage over time

2. **Export Table Tests**
   - Verify all expected exports are present
   - Check export ordinals match

3. **Import Table Tests**
   - Verify all required imports are present
   - Check for unexpected dependencies

4. **Resource Tests**
   - Validate resources (if any) match original

5. **Continuous Integration**
   - GitHub Actions workflow
   - Automated testing on commits

## Troubleshooting

### "pytest not installed"

Install pytest:
```bash
pip install pytest
```

### "Original PAL3.exe not found"

Place the original binaries in `original/` directory:
- `original/PAL3.exe`
- `original/topo.dll`
- `original/gbengine.dll`

### "Compiled topo.dll not found"

Build the project first:
```bash
.\build.bat
# Or
python verify_build.py
```

### Encoding Errors (Windows Chinese System)

The tests handle MSVC output encoding issues automatically using `errors='replace'` parameter.

## Integration with Existing Tools

The test framework complements existing project tools:

- `verify_build.py` - Build and verify (can be wrapped in tests)
- `tools/compare_function.py` - Compare specific functions
- `tools/progress_report.py` - Track decompilation progress

Future versions will integrate these tools into pytest test cases.

## Contributing

When adding new tests:

1. Use descriptive test names (`test_what_is_being_tested`)
2. Add docstrings explaining what the test verifies
3. Use fixtures from `conftest.py` for common paths
4. Skip gracefully if prerequisites are missing
5. Include helpful error messages on failure
6. Consider informational tests for debugging

Example:
```python
def test_my_feature(compiled_topo_dll):
    """Test that feature X works correctly."""
    if not some_prerequisite:
        pytest.skip("Prerequisite not met")

    # Test implementation
    assert something, "Clear error message if this fails"
```
