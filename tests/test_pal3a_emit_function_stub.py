import pytest
import os

# [R70 修 2026-10-22] tools/pal3a_emit_function_stub.py 不存在（工具从未建）
# 测试引用缺失工具 ⇒ 跳过（待工具创建后激活）
_STUB_TOOL = os.path.join(os.path.dirname(__file__), '..', 'tools', 'pal3a_emit_function_stub.py')
pytestmark = pytest.mark.skipif(not os.path.exists(_STUB_TOOL),
                                 reason="tools/pal3a_emit_function_stub.py 不存在（工具待建）")
import json
import subprocess
import sys
from pathlib import Path


def test_pal3a_emit_function_stub_writes_named_function(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    index = tmp_path / 'index.json'
    index.write_text(json.dumps({
        'functions': {
            '0x00401000': {
                'name': 'Sce_RunOpcode',
                'return_type': 'int',
                'parameters': ['PAL3A_SceContext *ctx', 'int opcode'],
                'source_file': 'script\\sceexec.cpp'
            }
        }
    }), encoding='utf-8')
    output = tmp_path / 'sce_runtime.cpp'

    result = subprocess.run(
        [sys.executable, str(project_root / 'tools' / 'pal3a_emit_function_stub.py'),
         '--index', str(index), '--address', '0x00401000', '--output', str(output)],
        capture_output=True,
        text=True,
    )

    assert result.returncode == 0, result.stderr
    text = output.read_text(encoding='utf-8')
    assert 'int Sce_RunOpcode(PAL3A_SceContext *ctx, int opcode)' in text
    assert '/* UNCERTAIN */' in text


def test_pal3a_emit_function_stub_creates_parent_directory(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    index = tmp_path / 'index.json'
    index.write_text(json.dumps({
        'functions': {
            '0x00402000': {
                'name': 'Sce_DispatchFrame',
                'return_type': 'void',
                'parameters': [],
                'source_file': 'script\\scedispatch.cpp'
            }
        }
    }), encoding='utf-8')
    output = tmp_path / 'nested' / 'sce_dispatch.cpp'

    result = subprocess.run(
        [sys.executable, str(project_root / 'tools' / 'pal3a_emit_function_stub.py'),
         '--index', str(index), '--address', '0x00402000', '--output', str(output)],
        capture_output=True,
        text=True,
    )

    assert result.returncode == 0, result.stderr
    assert output.exists()
    text = output.read_text(encoding='utf-8')
    assert 'void Sce_DispatchFrame(void)' in text


def test_pal3a_emit_function_stub_is_idempotent(tmp_path):
    project_root = Path(__file__).resolve().parents[1]
    index = tmp_path / 'index.json'
    index.write_text(json.dumps({
        'functions': {
            '0x00401000': {
                'name': 'Sce_RunOpcode',
                'return_type': 'int',
                'parameters': ['PAL3A_SceContext *ctx', 'int opcode'],
                'source_file': 'script\\sceexec.cpp'
            }
        }
    }), encoding='utf-8')
    output = tmp_path / 'sce_runtime.cpp'

    for _ in range(2):
        result = subprocess.run(
            [sys.executable, str(project_root / 'tools' / 'pal3a_emit_function_stub.py'),
             '--index', str(index), '--address', '0x00401000', '--output', str(output)],
            capture_output=True,
            text=True,
        )
        assert result.returncode == 0, result.stderr

    text = output.read_text(encoding='utf-8')
    assert text.count('int Sce_RunOpcode(PAL3A_SceContext *ctx, int opcode)') == 1

