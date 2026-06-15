"""Cross-check annotation names against decomp JSON names."""
import json, os

def load_json(path):
    for enc in ['utf-8', 'gbk', 'gb2312', 'latin-1']:
        try:
            with open(path, encoding=enc) as f:
                return json.load(f)
        except (UnicodeDecodeError, json.JSONDecodeError):
            continue
    return None

checks = ['0x0043DDF0', '0x00445B90', '0x00445E70', '0x00445D10',
          '0x0051B5D0', '0x00445C10', '0x00445CD0', '0x0043DE40',
          '0x00524970', '0x0051B160', '0x0051C9B0', '0x0051A390']
decomp_dir = 'asm/pal3/decomp'
ann_dir = 'data/annotations/structs'

for addr in checks:
    hex_addr = addr.lower().replace('0x', '')
    decomp_file = None
    for f in os.listdir(decomp_dir):
        if hex_addr in f.lower():
            decomp_file = f
            break
    if not decomp_file:
        print(f'=== {addr}: no decomp JSON ===')
        continue
    decomp = load_json(f'{decomp_dir}/{decomp_file}')
    if not decomp:
        print(f'=== {addr}: failed to load decomp JSON ===')
        continue
    decomp_name = decomp.get('name', '?')
    decomp_class = decomp_name.split('::')[0] if '::' in decomp_name else decomp_name
    print(f'=== {addr} ===')
    print(f'  Decomp: {decomp_name} (owner={decomp_class})')
    for ann_file in sorted(os.listdir(ann_dir)):
        if not ann_file.endswith('.json'):
            continue
        ann = load_json(f'{ann_dir}/{ann_file}')
        if not ann:
            continue
        methods = ann.get('methods', {})
        if addr in methods:
            ann_name = methods[addr]['name']
            ann_class = ann_name.split('::')[0] if '::' in ann_name else ann_name
            status = 'OK' if ann_class == decomp_class else 'WRONG'
            print(f'  {ann_file.replace(".json","")}: {ann_name} [{status}]')
    print()
