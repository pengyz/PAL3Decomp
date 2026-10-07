import pytest
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
    project_root = Path(__file__).resolve().parents[1]
    build_dir = project_root / 'build'
    build_dir.mkdir(exist_ok=True)
    config_path = build_dir / 'project_config.json'
    original = config_path.read_text(encoding='utf-8') if config_path.exists() else None
    try:
        config_path.write_text(json.dumps({
            'total_functions': 111,
            'text_section_size': 222,
            'pal3a_total_functions': 333,
            'pal3a_text_section_size': 444,
            'modules': {}
        }), encoding='utf-8')

        result = subprocess.run(
            [sys.executable, str(project_root / 'tools' / 'progress.py'), '--target', 'pal3a', '--export', 'json', '--output', str(tmp_path / 'progress.json')],
            capture_output=True,
            text=True,
        )

        assert result.returncode == 0, result.stderr
        data = json.loads((tmp_path / 'progress.json').read_text(encoding='utf-8'))
        assert data['stats']['total_functions'] == 333
    finally:
        if original is None:
            config_path.unlink(missing_ok=True)
        else:
            config_path.write_text(original, encoding='utf-8')


def test_progress_set_total_keeps_pal3_and_pal3a_separate(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    build_dir = project_root / 'build'
    build_dir.mkdir(exist_ok=True)
    config_path = build_dir / 'project_config.json'
    original = config_path.read_text(encoding='utf-8') if config_path.exists() else None
    try:
        config_path.write_text(json.dumps({
            'total_functions': 111,
            'text_section_size': 222,
            'pal3a_total_functions': 333,
            'pal3a_text_section_size': 444,
            'modules': {}
        }), encoding='utf-8')

        result = subprocess.run(
            [sys.executable, str(project_root / 'tools' / 'progress.py'), '--target', 'pal3a', '--set-total', '555'],
            capture_output=True,
            text=True,
        )

        assert result.returncode == 0, result.stderr
        config = json.loads(config_path.read_text(encoding='utf-8'))
        assert config['total_functions'] == 111
        assert config['pal3a_total_functions'] == 555
    finally:
        if original is None:
            config_path.unlink(missing_ok=True)
        else:
            config_path.write_text(original, encoding='utf-8')

