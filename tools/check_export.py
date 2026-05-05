import json
from collections import defaultdict

with open('asm/pal3a/pdb_export.json') as f:
    d = json.load(f)

si = d['source_file_index']
pal3_files = {k: v for k, v in si.items() if 'PAL3A' in k and '.cpp' in k.lower()}

# Show by directory
by_dir = defaultdict(list)
for path in sorted(pal3_files.keys()):
    rel = path
    prefixes = ['D:\\PAL3A\\PAL3\\', 'd:\\PAL3A\\PAL3\\']
    for prefix in prefixes:
        if path.startswith(prefix):
            rel = path[len(prefix):]
            break
    parts = rel.split('\\')
    d_name = parts[0] if len(parts) > 1 else '(root)'
    by_dir[d_name].append((rel, len(pal3_files[path])))

print(f'PAL3A source directories:')
for dname in sorted(by_dir.keys()):
    files = by_dir[dname]
    total_funcs = sum(f[1] for f in files)
    print(f'  {dname}/ ({len(files)} files, {total_funcs} funcs)')

# Sample: ConfigFile
print('\n--- ConfigFile.cpp ---')
for path, funcs in si.items():
    if 'ConfigFile.cpp' in path:
        for func in funcs[:10]:
            params = ', '.join(f'{p["type"]} {p["name"]}' for p in func.get('parameters', []))
            cls = func.get('class', '')
            name = func['name']
            print(f'  {name}({params})')
        break

# Sample: a class definition
print('\n--- Class: ConfigFile ---')
for cls in d['classes']:
    if cls['name'] == 'ConfigFile':
        print(f'  Size: {cls["size"]} bytes')
        print(f'  Data members:')
        for m in cls['data_members']:
            print(f'    {m["type"]} {m["name"]} @ offset {m["offset"]}')
        print(f'  Methods:')
        for m in cls['methods'][:10]:
            print(f'    {m["name"]} (size={m["size"]})')
        break

# Check how many functions still have mangled names
funcs_still_mangled = [f for f in d['functions'] if f['name'].startswith('?') or f['name'].startswith('_')]
print(f'\nStill mangled: {len(funcs_still_mangled)}/{len(d["functions"])}')
