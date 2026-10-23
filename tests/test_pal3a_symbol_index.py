import pytest
import os

# [R100 修 2026-10-23] tools/pal3a_build_index.py 不存在（工具未建）=> skip
_TOOL = os.path.join(os.path.dirname(__file__), '..', 'tools', 'pal3a_build_index.py')
pytestmark = pytest.mark.skipif(not os.path.exists(_TOOL), reason="tools/pal3a_build_index.py 不存在")
import json
import subprocess
import sys
from pathlib import Path


def test_pal3a_build_index_creates_function_and_global_maps(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    fixture = project_root / 'tests' / 'fixtures' / 'pal3a' / 'pdb_export_sample.json'
    output = tmp_path / 'pdb_index.json'

    result = subprocess.run(
        [sys.executable, str(project_root / 'tools' / 'pal3a_build_index.py'),
         '--input', str(fixture), '--output', str(output)],
        capture_output=True,
        text=True,
    )

    assert result.returncode == 0, result.stderr
    data = json.loads(output.read_text(encoding='utf-8'))
    assert data['functions']['0x00401000']['name'] == 'Sce_RunOpcode'
    assert data['globals']['0x00600000']['name'] == 'g_SceContext'
    assert data['types']['PAL3A_SceContext']['size'] == 64


def test_pal3a_build_index_normalizes_uppercase_hex_addresses(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    fixture = tmp_path / 'pdb_export_raw.json'
    fixture.write_text(json.dumps({
        'image_base': '401000',
        'functions': [
            {
                'address': '401230',
                'name': 'RawFunc',
                'source_file': 'script\\raw.cpp',
                'return_type': 'void',
                'parameters': []
            }
        ],
        'globals': [
            {
                'address': '600010',
                'name': 'g_Raw',
                'datatype': 'int'
            }
        ],
        'types': []
    }), encoding='utf-8')
    output = tmp_path / 'pdb_index.json'

    result = subprocess.run(
        [sys.executable, str(project_root / 'tools' / 'pal3a_build_index.py'),
         '--input', str(fixture), '--output', str(output)],
        capture_output=True,
        text=True,
    )

    assert result.returncode == 0, result.stderr
    data = json.loads(output.read_text(encoding='utf-8'))
    assert data['image_base'] == '0x00401000'
    assert '0x00401230' in data['functions']
    assert '0x00600010' in data['globals']

