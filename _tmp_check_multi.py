"""Check: are conflict addresses in multiple struct files?"""
import json, os

conflicts = ['0x00519380', '0x004EDF10', '0x00519FE0', '0x0051A930',
             '0x0047F590', '0x00528190', '0x00449C20', '0x004422E0']

struct_dir = 'data/annotations/structs'

for addr in conflicts:
    files = []
    for sf in sorted(os.listdir(struct_dir)):
        if not sf.endswith('.json'): continue
        with open(os.path.join(struct_dir, sf), 'r', encoding='utf-8') as f:
            d = json.load(f)
        if addr in d.get('methods', {}):
            files.append(sf + ':' + d['methods'][addr].get('name', '?'))
    print(addr + ' -> ' + ' | '.join(files))
