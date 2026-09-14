"""Collect and group functions from decomp JSON files.

Reads all decomp/*.json, parses MSVC mangled names, and groups functions
by class (for class .cpp files) or as free functions.
"""
import json
import re
from collections import defaultdict
from pathlib import Path

from data import store

# Classes to skip entirely (CRT, STL, gbengine wrappers, thunk trampolines)
SKIP_CLASSES = {
    'std', 'stdiobuf', 'exception', 'type_info', 'filebuf',
    'Iostream_init', 'Concurrency',
    'j_std', 'j_j_codecvt_base',
}

# Auto-detect classes defined in gbengine headers
import re as _re
_GBENGINE_DIR = Path(__file__).parent.parent.parent.parent / "include" / "gbengine"
if _GBENGINE_DIR.exists():
    for _hf in _GBENGINE_DIR.glob("*.h"):
        with open(_hf, 'r', encoding='utf-8', errors='replace') as _fh:
            for _line in _fh:
                _m = _re.match(r'^(?:class|struct)\s+(\w+)', _line)
                if _m:
                    SKIP_CLASSES.add(_m.group(1))

# Organize classes into subdirectories by category
CLASS_DIRS = {
    # Combat system
    'CCBSystem': 'Combat', 'CCBRoleState': 'Combat', 'CCBStage': 'Combat',
    'CCBStageCam': 'Combat', 'CCBStageRole': 'Combat', 'CCBStageScene': 'Combat',
    'CCBStageEffect': 'Combat', 'CCBStageShadow': 'Combat',
    'CCBControl': 'Combat', 'CCBAttackSequen': 'Combat',
    'CCBAI': 'Combat', 'CCBUI': 'Combat', 'CCCTData': 'Combat',
    'CCBAIWindow': 'Combat', 'CCBControlWindow': 'Combat',
    'CCBItemWindow': 'Combat', 'CCBLineupWindow': 'Combat',
    'CCBMagicWindow': 'Combat', 'CCBSkillWindow': 'Combat',
    'CCBParabolaWindow': 'Combat', 'CCBProtectWindow': 'Combat',
    'CCBResultWindow': 'Combat', 'CCBCamControl': 'Combat',
    'Combat': 'Combat', 'CUtil': 'Combat',
    # Effects
    'CEffect': 'Effect', 'CEffMgr': 'Effect', 'CEffectSystem': 'Effect',
    'CEffCylinder': 'Effect', 'CEffExplosive': 'Effect', 'CEffGrid': 'Effect',
    'CEffMeteor': 'Effect', 'CEffModel': 'Effect', 'CEffQuad': 'Effect',
    'CEffQuake': 'Effect', 'CEffShock': 'Effect', 'CEffSParticle': 'Effect',
    'CEffgbParticle': 'Effect', 'CMeteorChain': 'Effect',
    'C2DSpark': 'Effect', 'C3DSpark': 'Effect',
    'ScreenEffect': 'Effect', 'ScreenEffectMgr': 'Effect',
    # UI
    'UIWnd': 'UI', 'UIScene': 'UI', 'UIManager': 'UI', 'UISystem': 'UI',
    'UIDialog': 'UI', 'UIBigDialog': 'UI', 'UISelectDialog': 'UI',
    'UIItem': 'UI', 'UIBase': 'UI', 'UICamera': 'UI', 'UICursor': 'UI',
    'UIListBox': 'UI', 'UILBColumn': 'UI', 'UILBItem': 'UI',
    'UINote': 'UI', 'UIQuadManager': 'UI', 'UIRenderObj': 'UI',
    'EquipUI': 'UI', 'MagicUI': 'UI', 'PropUI': 'UI', 'StateUI': 'UI',
    # Render
    'RenderTarget': 'Render', 'RenderTarget2': 'Render',
    'RenderTarget3': 'Render', 'RenderTarget4': 'Render',
    'CRenderTarget': 'Render', 'CRenderTarget2': 'Render',
    'CScreenMode': 'Render', 'TextureLib': 'Render',
    # Game core
    'PAL3': 'GameBase', 'GRPinput': 'GameBase', 'Config': 'GameBase',
    'Logger': 'GameBase', 'InputSystem': 'GameBase',
    'SoundSystem': 'GameBase', 'SoundContext': 'GameBase',
    # Script
    'PalScript': 'Script', 'PalScriptMgr': 'Script',
    'ScriptObj': 'Script', 'ScriptSystem': 'Script',
    # Scene/Role
    'Role': 'Role', 'RoleSystem': 'Role', 'NPC': 'Role',
    'Actor': 'Role', 'Object3D': 'Role', 'ObjectCamera': 'Role',
    'Scene': 'Scene', 'SceneMgr': 'Scene', 'SceneObj': 'Scene',
    'Camera': 'Scene', 'CameraCtrl': 'Scene', 'CameraSystem': 'Scene',
    # Data
    'CGameData': 'Data', 'PAL_GDB': 'Data',
    # Misc
    'MiniGame1': 'MiniGame', 'MiniGame3': 'MiniGame',
    'ParabolaCalculator': 'Misc', 'PtrArray': 'Misc', 'Array': 'Misc',
    'OpenBaseFile': 'Misc', 'OpenNULLFile': 'Misc', 'OpenSceneFile': 'Misc',
    'MvcController': 'Misc', 'MvcViewport': 'Misc',
}


def get_class_dir(cls_name):
    """Get subdirectory for a class."""
    return CLASS_DIRS.get(cls_name, 'Misc')


def _get_skip_classes():
    """Build the full skip set including thunk classes from annotations."""
    skip = set(SKIP_CLASSES)

    # Add thunk class names from skip_functions.json
    skip_path = store.annotations_dir / "skip_functions.json"
    if skip_path.exists():
        skip_data = json.load(open(skip_path, encoding='utf-8'))
        for info in skip_data.values():
            if info.get('reason') == 'thunk':
                name = info.get('name', '')
                # Only skip the entire class if the thunk is a class-level
                # wrapper (j_ClassName). Method-level thunks (ClassName::method)
                # should not suppress the whole class -- they're individual stubs.
                if '::' not in name and name.startswith('j_'):
                    skip.add(name[2:])
    return skip


def collect_functions(decomp_dir=None):
    """Collect all functions from decomp, grouped by class and free functions.

    Args:
        decomp_dir: Path to decomp JSON directory. Defaults to store.decomp_dir.

    Returns:
        (by_class, free_funcs) where:
            by_class: dict mapping class name -> list of method dicts
            free_funcs: list of free function dicts
    """
    if decomp_dir is None:
        decomp_dir = store.decomp_dir
    decomp_dir = Path(decomp_dir)

    skip_classes = _get_skip_classes()
    by_class = defaultdict(list)
    free_funcs = []

    for f in sorted(decomp_dir.glob("*.json")):
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                d = json.load(fh)
        except Exception:
            continue

        name = d.get('name', '')
        code = d.get('decompiled_c', '')
        addr = d.get('address', '')
        sig = d.get('signature', '')

        if not code or not name:
            continue
        if name.startswith('sub_'):
            continue


        # Demangle MSVC names: ?Method@Class@@... -> Class::Method
        cls = None
        method = None
        if name.startswith('?'):
            inner = name[1:]
            if inner.startswith('?0') or inner.startswith('?1'):
                code_ch = inner[1]
                rest = inner[2:]
                at_pos = rest.find('@')
                if at_pos > 0:
                    cls = rest[:at_pos]
                    method = cls if code_ch == '0' else '~' + cls
            else:
                at_pos = inner.find('@')
                if at_pos > 0:
                    method = inner[:at_pos]
                    rest = inner[at_pos + 1:]
                    at_pos2 = rest.find('@')
                    if at_pos2 > 0:
                        cls = rest[:at_pos2]
            if cls and ('$' in cls or '<' in cls or not (cls[0].isalpha() or cls[0] == '_')):
                cls = None
        elif '::' in name:
            parts = name.rsplit('::', 1)
            cls = parts[0]
            method = parts[1].split('(')[0] if '(' in parts[1] else parts[1]

        # IDA same-name dedup suffix (__ovl_1 / __ovl_2 / ...) is a decompiler
        # bookkeeping artifact — the original C++ source never had such
        # identifiers. Strip it so cpp definitions match header declarations
        # (emit_headers applies the same strip for declarations). The ordinal
        # can flip between exports when IDB types are re-applied, turning a
        # previously-fine method into an undeclared-member cascade.
        if method:
            _stripped = re.sub(r'__ovl_[0-9a-fA-F]+$', '', method)
            if _stripped != method:
                # rename inside the body too: stage1 rebuilds the definition
                # from the code text's own signature line
                code = re.sub(r'\b%s\b' % re.escape(method), _stripped, code)
            method = _stripped

        if cls and method:
            if cls in skip_classes:
                continue

            # Skip compiler-generated _scalar_dtor functions.
            # These are vtable wrappers around virtual destructors; the compiler
            # generates them automatically from 'virtual ~ClassName()' declarations.
            if '_scalar_dtor' in method or method.startswith('_sdtor'):
                store.scalar_dtor_classes.add(cls)
                continue

            # Strip _misattrib_ prefix: put function back under the original class
            # with a comment marking it as misattributed (attribution unconfirmed)
            if cls.startswith('_misattrib_'):
                original_cls = cls
                cls = cls[len('_misattrib_'):]
                code = '// [MISATTRIB] attribution unconfirmed\n' + code
                # Also strip _misattrib_ references in function body
                code = code.replace('_misattrib_' + cls + '::', cls + '::')
                code = code.replace('misattrib_' + cls + '::', cls + '::')

            # Strip __ovl_XXXX suffix to match header declaration (emit_headers.py does the same)
            ovl_stripped = re.sub(r'__ovl_[0-9a-fA-F]+$', '', method)
            if ovl_stripped != method:
                collides = False
                for existing in by_class.get(cls, []):
                    if existing['method'] == ovl_stripped:
                        if existing.get('sig') == sig:
                            collides = True
                            break
                if not collides:
                    method = ovl_stripped

            by_class[cls].append({
                'name': '%s::%s' % (cls, method),
                'method': method,
                'code': code,
                'addr': addr,
                'sig': sig,
                '_source_file': str(f),
            })
        else:
            free_funcs.append({
                'name': name,
                'code': code,
                'addr': addr,
                'sig': sig,
            })

    return by_class, free_funcs
