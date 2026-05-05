import json
from pathlib import Path

from tools import project_config


def test_get_target_exe_path_reads_pal3a_keys(tmp_path, monkeypatch):
    game_dir = tmp_path / 'PAL3A'
    game_dir.mkdir()
    exe_path = game_dir / 'PAL3Aunpacked.exe'
    exe_path.write_bytes(b'MZ')
    pdb_path = game_dir / 'PAL3A.pdb'
    pdb_path.write_bytes(b'RSDS')

    local_config = tmp_path / 'local_config.json'
    local_config.write_text(json.dumps({
        'pal3a_game_dir': str(game_dir),
        'pal3a_exe_name': 'PAL3Aunpacked.exe',
        'pal3a_pdb_path': str(pdb_path),
    }), encoding='utf-8')

    monkeypatch.setattr(project_config, 'LOCAL_CONFIG_FILE', local_config)
    monkeypatch.setattr(project_config, 'BUILD_CONFIG_FILE', tmp_path / 'build_config.json')

    assert project_config.get_target_exe_path('pal3a') == exe_path
    assert project_config.get_target_pdb_path('pal3a') == pdb_path


def test_get_target_exe_path_keeps_pal3_default(tmp_path, monkeypatch):
    game_dir = tmp_path / 'PAL3'
    game_dir.mkdir()
    exe_path = game_dir / 'PAL3.exe'
    exe_path.write_bytes(b'MZ')

    local_config = tmp_path / 'local_config.json'
    local_config.write_text(json.dumps({'game_dir': str(game_dir)}), encoding='utf-8')

    monkeypatch.setattr(project_config, 'LOCAL_CONFIG_FILE', local_config)
    monkeypatch.setattr(project_config, 'BUILD_CONFIG_FILE', tmp_path / 'build_config.json')

    assert project_config.get_target_exe_path('pal3') == exe_path
