"""统一 plan 生成器（G8 可重放）：annotation 目录 → plan.json。
用法: python3 gen_plan.py <ann_dir> <out_plan.json> [--structs a,b,c]
吃 functions.json + structs/*.json（methods 自动并入）+ globals.json。
plan 头插 _meta 版本锚；apply 遇未知 op 必报错（禁静默跳过）。"""
import json, glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_annotation import build_import_plan, load_ann_dir

PLAN_VERSION = 1

def load(ann_dir, only=None):
    # [T2] 确定性单源：委托 import_annotation.load_ann_dir（sorted glob+merge_method_claims）
    return load_ann_dir(ann_dir, only=only)

def main():
    ann, out = sys.argv[1], sys.argv[2]
    only = None
    if '--structs' in sys.argv:
        only = set(sys.argv[sys.argv.index('--structs') + 1].split(','))
    funcs, structs, g = load(ann, only)
    ep = os.path.join(ann, 'enums.json')
    enums = json.load(open(ep)) if os.path.exists(ep) else {}
    plan = [{'kind': '_meta', 'version': PLAN_VERSION, 'source': ann}] + \
           build_import_plan(functions=funcs, structs=structs, globals=g, enums=enums)
    json.dump(plan, open(out, 'w'), indent=1, ensure_ascii=False)
    print('plan v%d: %d ops -> %s' % (PLAN_VERSION, len(plan), out))

if __name__ == '__main__':
    main()
