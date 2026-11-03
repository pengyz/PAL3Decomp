"""typeOwnership 生成器（B 面质量线）：annotation structs → reconstruct 配置归属。
用法: python3 gen_type_ownership.py <ann_dir> <project.json in/out>
每型一 header（type → <name>.h）——类组织树形；配合 modules 归属后续演进。"""
import json, glob, sys, os
ann, cfg_path = sys.argv[1], sys.argv[2]
cfg = json.load(open(cfg_path))
own = []
seen = set()
for f in glob.glob(os.path.join(ann, 'structs', '*.json')):
    d = json.load(open(f))
    n = d.get('name')
    if n and n not in seen:
        seen.add(n)
        own.append({'type': n, 'header': n + '.h'})
cfg['typeOwnership'] = own
json.dump(cfg, open(cfg_path, 'w'), indent=1, ensure_ascii=False)
print('typeOwnership: %d 型 → %s' % (len(own), cfg_path))
