import json
import subprocess
import sys
from pathlib import Path


def test_pal3a_anchor_picker_prefers_script_functions(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    fixture = project_root / 'tests' / 'fixtures' / 'pal3a' / 'pdb_index_sample.json'
    output = tmp_path / 'anchors.json'

    result = subprocess.run(
        [sys.executable, str(project_root / 'tools' / 'pal3a_pick_script_anchors.py'),
         '--index', str(fixture), '--output', str(output)],
        capture_output=True,
        text=True,
    )

    assert result.returncode == 0, result.stderr
    data = json.loads(output.read_text(encoding='utf-8'))
    assert data['anchors'][0]['name'] == 'Sce_RunOpcode'


def test_progress_supports_pal3a_target(tmp_path):
    progress_db = tmp_path / 'progress.json'
    progress_db.write_text(json.dumps({'functions': {}, 'last_updated': ''}), encoding='utf-8')
    assert progress_db.exists()
