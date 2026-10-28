"""[TOS 宪法守卫·三闸 2026-10-28·F2] 零 stage↔stage（含 alias 形）+
跨文件同名顶层 def 棘轮 + 共享层禁上行。新增违例必红。运行: pytest tests/test_tos_stage_isolation.py
"""
import ast, glob, os
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
FROZEN_EDGES = [('codegen', 'emit_cpp'), ('codegen', 'emit_headers'), ('emit_cpp', 'collect'), ('emit_cpp', 'emit_headers'), ('emit_cpp', 'transform'), ('emit_headers', 'collect'), ('emit_headers', 'scope_tree'), ('test_base_suffix_rewrite', 'base_suffix_rewrite'), ('test_base_suffix_rewrite', 'stage3_cleanup'), ('test_call_route', 'stage5_fixup'), ('test_cast_reg_assignments', 'stage5_fixup'), ('test_hang3_nails', 'transform'), ('test_hook_order', 'stage2_semantic'), ('test_noreturn_strip', 'stage5_fixup'), ('test_pipeline', 'emit_cpp'), ('test_pipeline', 'emit_headers'), ('test_pipeline', 'stage3_cleanup'), ('test_plain_call_decl', 'emit_cpp'), ('test_r1_cprime_a', 'stage5_fixup'), ('test_ref_param_table_b', 'stage5_fixup'), ('transform', 'stage1_structural'), ('transform', 'stage2_semantic'), ('transform', 'stage3_cleanup'), ('transform', 'stage4_substitution'), ('transform', 'stage5_fixup')]
FROZEN_DUPS = {'main': ['codegen', 'emit_headers'], 'resolve_targets': ['collect', 'scoped_targets'], 'scoped_decomp_dir': ['collect', 'scoped_targets'], 'run': ['stage1_structural', 'stage2_semantic', 'stage3_cleanup', 'stage4_substitution', 'stage5_fixup']}


def _scan():
    mods = {os.path.basename(f)[:-3] for f in glob.glob(str(ROOT / 'pipeline/gen/stages/*.py'))}
    edges, topdefs = set(), {}
    for f in sorted(glob.glob(str(ROOT / 'pipeline/gen/*.py')) + glob.glob(str(ROOT / 'pipeline/gen/stages/*.py'))):
        me = os.path.basename(f)[:-3]
        tree = ast.parse(open(f).read())
        for n in ast.walk(tree):
            if isinstance(n, ast.ImportFrom):
                tgt = n.module.split('.')[-1] if n.module else ''
                if tgt in mods and tgt != me: edges.add((me, tgt))
                if n.module == 'stages':
                    for a in n.names:
                        if a.name in mods and a.name != me: edges.add((me, a.name))
            if isinstance(n, ast.Import):
                for a in n.names:
                    k = a.name.split('.')[-1]
                    if k in mods and k != me: edges.add((me, k))
        for n in tree.body:
            if isinstance(n, ast.FunctionDef):
                topdefs.setdefault(n.name, set()).add(me)
    return sorted(edges), {k: sorted(v) for k, v in topdefs.items() if len(v) > 1}


def test_t6_stage_edges_frozen():
    got, _ = _scan()
    new = [e for e in got if tuple(e) not in {tuple(x) for x in FROZEN_EDGES}]
    gone = [e for e in FROZEN_EDGES if tuple(e) not in {tuple(x) for x in got}]
    assert not new, '新增 stage↔stage 边: %s' % new
    assert not gone, '冻结边消失（收紧须显式改测）: %s' % gone


def test_t7_same_name_toplevel_def_ratchet():
    _, dup = _scan()
    assert dup == FROZEN_DUPS, '同名顶层 def 集变化（新增双定义 or 消减未改棘轮）: %s vs %s' % (dup, FROZEN_DUPS)


def test_t8_shared_layer_no_upward_import():
    shared = ('tables', 'ref_params', 'textutil', 'sig_resolve', 'data', 'annotation_view')
    mods = {os.path.basename(f)[:-3] for f in glob.glob(str(ROOT / 'pipeline/gen/stages/*.py'))}
    bad = []
    for f in glob.glob(str(ROOT / 'pipeline/gen/*.py')):
        me = os.path.basename(f)[:-3]
        if me not in shared: continue
        for n in ast.walk(ast.parse(open(f).read())):
            if isinstance(n, ast.ImportFrom) and (n.module or '').split('.')[-1] in mods:
                bad.append((me, n.module))
    assert not bad, '共享层上行引用 stage: %s' % bad
