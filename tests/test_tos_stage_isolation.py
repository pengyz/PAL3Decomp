"""[TOS 宪法守卫 2026-10-28·E7/T6] stage↔stage 零互引棘轮。
冻结集=现状边（含既定分层豁免与 C6 待清违例）；新增边必红。
运行: python3 tests/test_tos_stage_isolation.py
"""
import ast, glob, os, sys
from pathlib import Path
PROJECT_ROOT = Path(__file__).resolve().parents[1]

FROZEN = [('emit_cpp', 'collect'), ('emit_cpp', 'emit_headers'), ('emit_cpp', 'transform'), ('emit_headers', 'collect'), ('emit_headers', 'scope_tree'), ('emit_headers', 'stage4_substitution')]


def _edges():
    edges = set()
    mods = {os.path.basename(f)[:-3] for f in glob.glob(str(PROJECT_ROOT / 'pipeline/gen/stages/*.py'))}
    for f in sorted(glob.glob(str(PROJECT_ROOT / 'pipeline/gen/stages/*.py'))):
        me = os.path.basename(f)[:-3]
        for n in ast.walk(ast.parse(open(f).read())):
            if isinstance(n, ast.ImportFrom) and n.module:
                tgt = n.module.split('.')[-1]
                if tgt in mods and tgt != me: edges.add((me, tgt))
            if isinstance(n, ast.Import):
                for a in n.names:
                    if a.name in mods and a.name != me: edges.add((me, a.name))
    return sorted(edges)


def test_stage_edges_frozen_no_new_cross_refs():
    got = _edges()
    new = [e for e in got if tuple(e) not in {tuple(x) for x in FROZEN}]
    assert not new, '新增 stage↔stage 边（宪法违例）: %s' % new
