"""Annotation regression tests - verify known fixes remain effective."""
import json
import os
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent.parent
STRUCTS_DIR = PROJECT_ROOT / "data" / "annotations" / "structs"
IDA_FILE = PROJECT_ROOT / "asm" / "pal3" / "ida_structs.json"
FUNCS_FILE = PROJECT_ROOT / "data" / "annotations" / "functions.json"


def load_ida_data():
    with open(IDA_FILE) as f:
        return json.load(f)


def test_pointer_level_mismatches():
    """Verify: 0 pointer level mismatches between annotation and IDA export."""
    ida_data = load_ida_data()
    mismatches = 0
    for f in sorted(STRUCTS_DIR.glob("*.json")):
        with open(f) as fh:
            ann = json.load(fh)
        name = ann.get('name', '?')
        ida_entry = ida_data.get(name, {})
        ida_dms = {dm['offset']: dm for dm in ida_entry.get('data_members', [])}
        for offset, info in ann.get('known_members', {}).items():
            try:
                off = int(offset, 16) if 'x' in offset.lower() else int(offset)
            except:
                continue
            ann_type = info.get('type', '')
            if isinstance(ann_type, dict):
                continue
            if off in ida_dms:
                ida_type = ida_dms[off].get('type', '')
                if isinstance(ida_type, dict):
                    continue
                if str(ann_type).count('*') != str(ida_type).count('*') and ann_type != 'skip':
                    mismatches += 1
    assert mismatches == 0, f"Pointer level mismatches: {mismatches}"


def test_ceffmgr_efftable_type():
    """Verify: CEffMgr.m_EffTable type is _BYTE[584], not tagEffObj[2048]."""
    effmgr_file = STRUCTS_DIR / "CEffMgr.json"
    if not effmgr_file.exists():
        return  # Skip if file doesn't exist
    with open(effmgr_file) as f:
        data = json.load(f)
    members = data.get('known_members', {})
    efftable = members.get('2332', {})
    assert efftable.get('type') == '_BYTE[584]', \
        f"CEffMgr.m_EffTable type is {efftable.get('type')}, expected _BYTE[584]"


def test_uiwnd_onmessage():
    """Verify: UIWnd has OnMessage in known_methods."""
    uiwnd_file = STRUCTS_DIR / "UIWnd.json"
    if not uiwnd_file.exists():
        return
    with open(uiwnd_file) as f:
        data = json.load(f)
    methods = data.get('known_methods', {})
    has_onmessage = any(m.get('name') == 'OnMessage' for m in methods.values() if isinstance(m, dict))
    assert has_onmessage, "UIWnd missing OnMessage in known_methods"


def test_nullcallback_in_free_functions():
    """Verify: NullCallback is declared in free_functions.h."""
    ff_path = PROJECT_ROOT / "pal3" / "src" / "free_functions.h"
    if not ff_path.exists():
        return
    content = ff_path.read_text()
    assert 'NullCallback' in content, "NullCallback not in free_functions.h"


def test_flt_d90060_in_globals():
    """Verify: flt_D90060 is declared in globals.h."""
    gh_path = PROJECT_ROOT / "pal3" / "src" / "globals.h"
    if not gh_path.exists():
        return
    content = gh_path.read_text()
    assert 'flt_D90060' in content, "flt_D90060 not in globals.h"


if __name__ == "__main__":
    tests = [
        test_pointer_level_mismatches,
        test_ceffmgr_efftable_type,
        test_uiwnd_onmessage,
        test_nullcallback_in_free_functions,
        test_flt_d90060_in_globals,
    ]
    passed = 0
    failed = 0
    for test in tests:
        try:
            test()
            print(f"  ✅ {test.__name__}")
            passed += 1
        except AssertionError as e:
            print(f"  ❌ {test.__name__}: {e}")
            failed += 1
        except Exception as e:
            print(f"  ⚠️  {test.__name__}: {e}")
            failed += 1
    print(f"\nResults: {passed} passed, {failed} failed")
    sys.exit(1 if failed else 0)
