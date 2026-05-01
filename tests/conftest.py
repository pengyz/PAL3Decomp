"""Shared test configuration for PAL3 decompilation tests."""
import os
import pytest

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

@pytest.fixture
def project_root():
    """Return the project root directory path."""
    return PROJECT_ROOT

@pytest.fixture
def original_exe():
    """Return path to original PAL3.exe, skip test if not found."""
    path = os.path.join(PROJECT_ROOT, 'original', 'PAL3.exe')
    if not os.path.exists(path):
        pytest.skip("Original PAL3.exe not found")
    return path

@pytest.fixture
def original_topo_dll():
    """Return path to original topo.dll, skip test if not found."""
    path = os.path.join(PROJECT_ROOT, 'original', 'topo.dll')
    if not os.path.exists(path):
        pytest.skip("Original topo.dll not found")
    return path

@pytest.fixture
def compiled_topo_dll():
    """Return path to compiled topo.dll, skip test if not found."""
    path = os.path.join(PROJECT_ROOT, 'build', 'Release', 'topo.dll')
    if not os.path.exists(path):
        pytest.skip("Compiled topo.dll not found - run build first")
    return path

@pytest.fixture
def compiled_exe():
    """Return path to compiled PAL3.exe, skip test if not found."""
    path = os.path.join(PROJECT_ROOT, 'build', 'pal3_test', 'Release', 'PAL3.exe')
    if not os.path.exists(path):
        pytest.skip("Compiled PAL3.exe not found - run build first")
    return path
