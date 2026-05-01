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
