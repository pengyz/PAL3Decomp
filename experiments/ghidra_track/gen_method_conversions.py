"""methodConversions 生成器（机制配置件）：annotation methods → 调用形映射。
用法: python3 gen_method_conversions.py <ann_dir> <project.json in/out>
[address, className]=flat 调用→成员调用重写映射（method-call-rewrite plugin 启用钥匙）
=删除析构调用形 + thiscall 归属双桶的同根修复。"""
import json, glob, sys, os
ann, cfg_path = sys.argv[1], sys.argv[2]
cfg = json.load(open(cfg_path))
conv, seen = [], set()
for f in glob.glob(os.path.join(ann, 'structs', '*.json')):
    d = json.load(open(f))
    cls = d.get('name')
    for addr, m in (d.get('methods') or {}).items():
        if cls and addr.startswith('0x') and addr not in seen:
            seen.add(addr)
            conv.append({'address': addr, 'className': cls})
cfg['methodConversions'] = conv
json.dump(cfg, open(cfg_path, 'w'), indent=1, ensure_ascii=False)
print('methodConversions: %d 条 -> %s' % (len(conv), cfg_path))
