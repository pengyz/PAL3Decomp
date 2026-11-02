"""统一 plan 生成器（G8 可重放）：annotation 目录 → plan.json。
用法: python3 gen_plan.py <ann_dir> <out_plan.json> [--structs a,b,c]
吃 functions.json + structs/*.json（methods 自动并入）+ globals.json。
plan 头插 _meta 版本锚；apply 遇未知 op 必报错（禁静默跳过）。"""
import json, glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_annotation import build_import_plan

PLAN_VERSION = 1

def load(ann_dir, only=None):
    funcs = {}
    fp = os.path.join(ann_dir, 'functions.json')
    if os.path.exists(fp):
        funcs.update(json.load(open(fp)))
    structs = {}
    for f in glob.glob(os.path.join(ann_dir, 'structs', '*.json')):
        d = json.load(open(f))
        n = d.get('name')
        if not n or (only and n not in only):
            continue
        structs[n] = d
        for addr, m in (d.get('methods') or {}).items():
            if isinstance(m, dict) and m.get('name'):
                funcs[addr] = {'name': m['name'], 'signature': m.get('signature') or '', 'class': n}
    g = {}
    gp = os.path.join(ann_dir, 'globals.json')
    if os.path.exists(gp):
        g = json.load(open(gp))
    return funcs, structs, g

def main():
    ann, out = sys.argv[1], sys.argv[2]
    only = None
    if '--structs' in sys.argv:
        only = set(sys.argv[sys.argv.index('--structs') + 1].split(','))
    funcs, structs, g = load(ann, only)
    plan = [{'kind': '_meta', 'version': PLAN_VERSION, 'source': ann}] + \
           build_import_plan(functions=funcs, structs=structs, globals=g)
    json.dump(plan, open(out, 'w'), indent=1, ensure_ascii=False)
    print('plan v%d: %d ops -> %s' % (PLAN_VERSION, len(plan), out))

if __name__ == '__main__':
    main()
