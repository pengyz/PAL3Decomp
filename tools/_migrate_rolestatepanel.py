"""Migrate the RoleStatePanel (0x56F040 / 0x2B080) method block annotations.

One-time surgery per data/status/_rolestatepanel_verdict.json (2026-09-14).
Moves 16 adjudicated methods from EquipUI/MagicUI/StateUI/MainEquipUI/UIBase
into the new RoleStatePanel class annotation and renames the functions.json
entries. Idempotent: skips addresses already owned by RoleStatePanel.
"""
import json
from pathlib import Path

ROOT = Path(__file__).parent.parent
SDIR = ROOT / 'data' / 'annotations' / 'structs'
FNS = ROOT / 'data' / 'annotations' / 'functions.json'

# addr(lower) -> (method_name, source_class, evidence)
MOVES = {
    '0x004a1e40': ('InitUI',          'EquipUI',     'installs vtable 0x56F040 at this+0'),
    '0x004a2450': ('~RoleStatePanel', 'MainEquipUI', 'dtor; xref to vtable 0x56F040 at 0x4a246d'),
    '0x004a3900': ('SetItemData',     'UIBase',      'stride this+id*3788 = s_RoleState; fields +0x25E04..'),
    '0x004a4780': ('HandleDeviceLostB','MainEquipUI','writes +0x2B07C/+0x2B078 (last fields, size 0x2B080)'),
    '0x004a4820': ('Render',          'MainEquipUI', 'max_offset 176252 = size-4'),
    '0x004a4890': ('GetSelected',     'EquipUI',     'scans +0x169[5] slot flags'),
    '0x004a48b0': ('InitSlots',       'EquipUI',     '0xa1 family; ecx=[parent+0x6E14] call chain'),
    '0x004a4960': ('InitLayout',      'StateUI',     '0xa1 family (byte-identical variant)'),
    '0x004a4a10': ('CreateWidgets',   'StateUI',     '0xa1 family'),
    '0x004a4ac0': ('SetSelectedData', 'MagicUI',     '0xa1 family'),
    '0x004a4b70': ('Init',            'MagicUI',     '0xa1 family'),
    '0x004a4c20': ('Create',          'EquipUI',     'calls 0xa1 family on this'),
    '0x004a4fc0': ('SetEquipSlotData','MainEquipUI', 'writes +0x2AFD4..0x2AFD9'),
    '0x004a5930': ('RenderThrottled', 'MainEquipUI', 'max_offset 176084'),
    '0x004a5a80': ('LayoutHandleNav', 'MainEquipUI', 'max_offset 176084'),
    '0x004a5b30': ('UpdateCaptions',  'MainEquipUI', 'max_offset 176084'),
}

KNOWN_MEMBERS = {
    '0x60':     {'name': 'm_nScanIndex', 'type': 'int', 'source': 'GetSelected loop counter'},
    '0x169':    {'name': 'm_bSlotFlags', 'type': 'unsigned char[5]', 'source': 'GetSelected 5-slot scan'},
    '0x25e04':  {'name': 'm_roles', 'type': 's_RoleState[5]', 'source': 'SetItemData stride 3788 x5'},
    '0x2afbc':  {'name': 'm_pSubTab1', 'type': 'void *', 'source': '0xa1 family sub-control (has vtable)'},
    '0x2afc0':  {'name': 'm_pSubTab2', 'type': 'void *', 'source': '0xa1 family sub-control (has vtable)'},
    '0x2afd4':  {'name': 'm_nEquipSlot', 'type': 'int', 'source': 'SetEquipSlotData'},
    '0x2afd8':  {'name': 'm_bFlag2afd8', 'type': 'unsigned char', 'source': 'SetEquipSlotData'},
    '0x2afd9':  {'name': 'm_bFlag2afd9', 'type': 'unsigned char', 'source': 'SetEquipSlotData'},
    '0x2b078':  {'name': 'm_nDevLost1', 'type': 'int', 'source': 'HandleDeviceLostB (last fields)'},
    '0x2b07c':  {'name': 'm_nDevLost2', 'type': 'int', 'source': 'HandleDeviceLostB (size-4 anchor)'},
}


def main():
    moved, skipped = [], []
    # 1. collect existing method dicts from source classes
    entries = {}
    for p in SDIR.glob('*.json'):
        d = json.loads(p.read_text(encoding='utf-8'))
        methods = d.get('methods') or {}
        hit = {a: m for a, m in methods.items() if a.lower() in MOVES}
        if hit:
            entries[p] = (d, hit)

    # 2. build RoleStatePanel annotation
    new_methods = {}
    for al, (name, srcclass, evidence) in MOVES.items():
        src = None
        for p, (d, hit) in entries.items():
            for a, m in hit.items():
                if a.lower() == al:
                    src = dict(m)
                    break
        if src is None:
            skipped.append((al, 'no existing annotation entry'))
            continue
        old_name = src.get('name', '?')
        src['name'] = name
        src['_misattrib_evidence'] = 'rolestatepanel: %s (was %s.%s)' % (
            evidence, srcclass, old_name)
        new_methods[al] = src
        moved.append((al, srcclass, old_name, name))

    panel = {
        'name': 'RoleStatePanel',
        'binary_size': 176256,
        'size_evidence': 'operator new(0x2B080) at sub_44F130+0x44f1d5; HandleDeviceLostB writes +0x2B07C (size-4)',
        'vtables': [{
            'addr': '0x0056F040',
            'base': 'UIWnd',
            'note': 'installed by InitUI@0x4A1E40; slot ownership beyond slot0 unverified',
        }],
        'methods': new_methods,
        'known_members': KNOWN_MEMBERS,
        '_naming_note': 'descriptive name (5-role state panel, equip/magic/state tabs); original source name unrecoverable — see _rolestatepanel_verdict.json',
    }
    out = SDIR / 'RoleStatePanel.json'
    out.write_text(json.dumps(panel, ensure_ascii=False, indent=1) + '\n',
                   encoding='utf-8')
    print('wrote', out, 'with', len(new_methods), 'methods')

    # 3. remove moved entries from source classes
    for p, (d, hit) in entries.items():
        methods = d.get('methods') or {}
        for a in hit:
            methods.pop(a, None)
        d['methods'] = methods
        p.write_text(json.dumps(d, ensure_ascii=False, indent=1) + '\n',
                     encoding='utf-8')
        print('cleaned', p.name, '(-%d)' % len(hit))

    # 4. functions.json renames (flat names, no param tails)
    fns = json.loads(FNS.read_text(encoding='utf-8'))
    ren = 0
    for k, v in fns.items():
        if not isinstance(v, dict):
            continue
        al = k.lower()
        if al in MOVES:
            name = MOVES[al][0]
            new = 'RoleStatePanel_%s' % name.replace('~', '~')
            if v.get('name') != new:
                v['name'] = new
                ren += 1
    FNS.write_text(json.dumps(fns, ensure_ascii=False, indent=1) + '\n',
                   encoding='utf-8')
    print('functions.json renamed:', ren)
    if skipped:
        print('SKIPPED:', skipped)


if __name__ == '__main__':
    main()
