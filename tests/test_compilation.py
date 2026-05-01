"""Test that PAL3 decompilation project compiles without errors.

This test verifies the build system works correctly by:
1. Configuring CMake with the appropriate generator
2. Building the project in Release mode
3. Verifying the output binary exists

The test uses a separate build directory (pal3_test) to avoid
interfering with the main build directory.
"""
import subprocess
import os
import sys
import pytest

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD_DIR = os.path.join(PROJECT_ROOT, 'build', 'pal3_test')
PAL3A_BUILD_DIR = os.path.join(PROJECT_ROOT, 'build', 'pal3a_test')


def test_cmake_configure(project_root):
    """Test that CMake configuration succeeds for topo.dll."""
    os.makedirs(BUILD_DIR, exist_ok=True)

    # Use Visual Studio generator for MSVC builds on Windows
    # Default to topo target as it's most complete
    result = subprocess.run(
        ['cmake', project_root, '-G', 'Visual Studio 17 2022', '-A', 'Win32',
         '-DBUILD_TARGET=topo'],
        cwd=BUILD_DIR,
        capture_output=True,
        text=True,
        timeout=60
    )

    # Check if cmake succeeded
    if result.returncode != 0:
        print("CMake STDOUT:", result.stdout)
        print("CMake STDERR:", result.stderr)
        pytest.fail(f"CMake configure failed with return code {result.returncode}")

    assert result.returncode == 0, f"CMake configure failed:\n{result.stderr}"


def test_build_release(project_root):
    """Test that Release build succeeds."""
    if not os.path.exists(os.path.join(BUILD_DIR, 'CMakeCache.txt')):
        pytest.skip("CMake not configured - run test_cmake_configure first")

    result = subprocess.run(
        ['cmake', '--build', BUILD_DIR, '--config', 'Release'],
        capture_output=True,
        text=True,
        encoding='utf-8',
        errors='replace',
        timeout=300
    )

    if result.returncode != 0:
        print("Build STDOUT:", result.stdout)
        print("Build STDERR:", result.stderr)
        pytest.fail(f"Build failed with return code {result.returncode}")

    assert result.returncode == 0, f"Build failed:\n{result.stderr}"


def test_topo_dll_exists():
    """Test that topo.dll was generated."""
    dll_path = os.path.join(BUILD_DIR, 'Release', 'topo.dll')
    assert os.path.exists(dll_path), f"topo.dll not found at {dll_path}"


def test_topo_dll_size():
    """Test that topo.dll has reasonable size (>10KB)."""
    dll_path = os.path.join(BUILD_DIR, 'Release', 'topo.dll')
    if not os.path.exists(dll_path):
        pytest.skip("topo.dll not found")

    size = os.path.getsize(dll_path)
    assert size > 10240, f"topo.dll is too small ({size} bytes), build may have failed"


def test_clean_build_warnings(project_root):
    """Test that build produces minimal warnings."""
    if not os.path.exists(os.path.join(BUILD_DIR, 'CMakeCache.txt')):
        pytest.skip("CMake not configured")

    # Rebuild to capture warnings
    # Use errors='replace' to handle non-UTF8 output from MSVC
    result = subprocess.run(
        ['cmake', '--build', BUILD_DIR, '--config', 'Release', '--clean-first'],
        capture_output=True,
        text=True,
        encoding='utf-8',
        errors='replace',
        timeout=300
    )

    # Count warning occurrences in output
    stdout_str = result.stdout if result.stdout else ""
    stderr_str = result.stderr if result.stderr else ""
    warning_count = stdout_str.count('warning') + stderr_str.count('warning')

    # Allow some warnings but flag if excessive
    if warning_count > 50:
        print(f"Warning: Build produced {warning_count} warnings")
        print("Consider reviewing compiler warnings")

    # This is informational, not a hard failure
    assert result.returncode == 0, "Build must succeed"


def test_pal3a_cmake_configure(project_root):
    os.makedirs(PAL3A_BUILD_DIR, exist_ok=True)
    result = subprocess.run(
        ['cmake', project_root, '-G', 'Visual Studio 17 2022', '-A', 'Win32',
         '-DBUILD_TARGET=pal3a'],
        cwd=PAL3A_BUILD_DIR,
        capture_output=True,
        text=True,
        timeout=60,
    )
    assert result.returncode == 0, result.stderr


def test_pal3a_build_release(project_root):
    if not os.path.exists(os.path.join(PAL3A_BUILD_DIR, 'CMakeCache.txt')):
        pytest.skip('PAL3A CMake not configured')
    result = subprocess.run(
        ['cmake', '--build', PAL3A_BUILD_DIR, '--config', 'Release'],
        capture_output=True,
        text=True,
        encoding='utf-8',
        errors='replace',
        timeout=300,
    )
    assert result.returncode == 0, result.stderr


def test_pal3a_exe_exists():
    exe_path = os.path.join(PAL3A_BUILD_DIR, 'Release', 'PAL3A.exe')
    assert os.path.exists(exe_path), exe_path
