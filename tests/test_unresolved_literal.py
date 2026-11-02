"""Fix1（2026-11-02）UNRESOLVED 标记机制裁撤——地址承载形→地址字面量（零新规则，
既有「就地 extern/地址」原则完成态）；_E/_L 无形址→时序反转（stage3 不判死，留 stage4）。
运行: pytest tests/test_unresolved_literal.py -q"""
import importlib.util
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
_spec = importlib.util.spec_from_file_location(
    'stage3c', str(ROOT / 'pipeline/gen/stages/stage3_cleanup.py'))
# 注：stage3 顶层依赖管线 store——仅取纯函数：AST 摘取
import ast as _ast
src = (ROOT / 'pipeline/gen/stages/stage3_cleanup.py').read_text()
mod = _ast.parse(src)
fn = next(n for n in mod.body if isinstance(n, _ast.FunctionDef) and n.name == 'resolve_unresolved_labels')
ns = {}
exec(compile(_ast.Module(body=[fn], type_ignores=[]), '<fn>', 'exec'), ns)
resolve_unresolved_labels = ns['resolve_unresolved_labels']


def test_addr_bearing_to_literal():
    out, marked = resolve_unresolved_labels('x = loc_5667EA;\ny = &qword_60C010;\nz = *(int*)loc_5667EA;')
    assert '((void*)0x5667EA)' in out and '((void*)0x60C010)' in out
    assert 'UNRESOLVED' not in out
    assert marked == {'loc_5667EA', 'qword_60C010'}


def test_E_L_passthrough_for_stage4():
    out, marked = resolve_unresolved_labels('UNRESOLVED__E68(x); _L1234: a = _L5;')
    assert '_E68(x)' in out or 'UNRESOLVED__E68' not in out   # _E 不判死
    assert '_L5' in out
