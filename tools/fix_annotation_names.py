"""Fix annotation names based on decomp JSON evidence.

Usage: python tools/fix_annotation_names.py
"""
import json, os, glob

def load_json(path):
    for enc in ['utf-8', 'gbk', 'latin-1']:
        try:
            with open(path, encoding=enc) as f:
                return json.load(f)
        except (UnicodeDecodeError, json.JSONDecodeError):
            continue
    return None

def save_json(path, data):
    with open(path, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
        f.write('\n')

ann_dir = 'data/annotations/structs'

# Map of address -> correct name (verified from decomp JSON)
fixes = {
    '0x0043DDF0': 'CCBControlWindow::Render',
    '0x0043DE40': 'CCBRoleState::Destroy',
    '0x00524970': 'CCBRoleState::Render',
    '0x0051C9B0': 'CCBFiveNimbusWindow::OnMessage',
}

fixed_count = 0
for ann_file in sorted(os.listdir(ann_dir)):
    if not ann_file.endswith('.json'):
        continue
    path = f'{ann_dir}/{ann_file}'
    ann = load_json(path)
    if not ann or 'methods' not in ann:
        continue
    changed = False
    for addr, correct_name in fixes.items():
        if addr in ann['methods']:
            old_name = ann['methods'][addr]['name']
            if old_name != correct_name:
                print(f'{ann_file}: {addr} "{old_name}" -> "{correct_name}"')
                ann['methods'][addr]['name'] = correct_name
                changed = True
                fixed_count += 1
    if changed:
        save_json(path, ann)

print(f'\nFixed {fixed_count} entries across {len(fixes)} addresses')
