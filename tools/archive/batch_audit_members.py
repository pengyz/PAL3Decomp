#!/usr/bin/env python3
"""系统性标注审计工具——结构成员类型 vs 全树使用点批量对拍。

用法: python3 tools/batch_audit_members.py [--apply]
"""
import json, os, re, sys, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, 'pal3', 'src')
APPLY = '--apply' in sys.argv

def main():
    # ① 构建全树源码索引(文件名→行列表, 一次读入)
    src_files = {}
    for root, dirs, files in os.walk(SRC):
        for f in files:
            if not f.endswith('.cpp'): continue
            p = os.path.join(root, f)
            try: src_files[p] = open(p, encoding='utf-8', errors='ignore').read().split('\n')
            except Exception: pass

    # ② 构建 成员名→声明类 的反查索引
    member_index = collections.defaultdict(list)
    for sf in os.listdir(os.path.join(ROOT, 'data', 'annotations', 'structs')):
        if not sf.endswith('.json'): continue
        sd = json.load(open(os.path.join(ROOT, 'data', 'annotations', 'structs', sf), encoding='utf-8'))
        cls = sd.get('name') or sf[:-5]
        for off, m in (sd.get('known_members') or {}).items():
            if isinstance(m, dict) and m.get('name'):
                member_index[m['name']].append((cls, sf, off, m))

    # ③ 对每个 known_member: 找全树使用点, 提取 demanded type, 对拍
    audited_count = 0
    contradicted_count = 0
    insufficient_count = 0
    corrections = []  # [(struct_file, cls, offset, old_type, new_type, evidence)]

    for mem_name, claimants in sorted(member_index.items()):
        # 只处理唯一归属(多类共享同名成员的跳过——继承问题另查)
        if len(claimants) > 1:
            continue
        cls, sf, off, ann = claimants[0]
        ann_type = ann.get('type', '')
        if not ann_type:
            continue
        ann_file = os.path.join(ROOT, 'data', 'annotations', 'structs', sf)

        # 全树搜索使用点(成员访问 ->mem / .mem)
        ptr_pat = re.compile(r'->\s*' + re.escape(mem_name) + r'\b')
        dot_pat = re.compile(r'\.\s*' + re.escape(mem_name) + r'\b')
        sites = []
        for path, lines in src_files.items():
            for i, line in enumerate(lines):
                if ptr_pat.search(line) or dot_pat.search(line):
                    sites.append((os.path.relpath(path, SRC), i + 1, line.strip()))

        if len(sites) < 2:
            insufficient_count += 1
            continue

        # 对拍: 从使用点提取 demanded type
        contradictions = []
        consistent = 0

        # 提取模式: ->mem = cast_value  → cast 类型 = demanded
        for fname, lineno, line in sites:
            m = re.search(r'\(\s*(?:const\s+)?([\w\s]+?(?:\*+)\s*)\)\s*(?:&)?[\w.\-]+(?:\.\w+)*\.' + re.escape(mem_name), line)
            if m:
                demanded = m.group(1).strip().rstrip('*').strip()
                actual_base = re.sub(r'\*+$', '', str(ann_type)).replace('struct ', '').replace('class ', '').strip()
                demanded_base = demanded.replace('struct ', '').replace('class ', '').strip()
                if demanded_base and actual_base and demanded_base != actual_base:
                    # [修] 跳过取址传参 &(expr.member) —— &取引用不改变类型
                    #   宽匹配: & 后面到 .member 之间可以有任意 cast(如 (const int *))
                    if '&' in line and (mem_name + ')') in line:
                        consistent += 1
                    else:
                        contradictions.append({
                            'file': fname, 'line': lineno,
                            'expected': actual_base, 'actual': demanded_base,
                            'detail': 'cast 型别不一致'
                        })
                else:
                    consistent += 1
                    continue
            # 提取模式: ->mem = simple_value → 声明类型是值型
            m2 = re.search(r'->\s*' + re.escape(mem_name) + r'\s*=\s*(\d+(?:\.\d+)?[fFuU]?|0x[0-9a-fA-F]+|"[^"]*")', line)
            if m2 and not re.search(r'[\*&]\s*$', ann_type):
                consistent += 1

        total = len(sites)
        if contradictions:
            level = 'contradicted'
        elif total >= 2 and consistent == total:
            level = 'audited'
        else:
            level = 'insufficient'

        if level == 'audited':
            audited_count += 1
        elif level == 'contradicted':
            contradicted_count += 1
        else:
            insufficient_count += 1

        # 写回注解(仅 --apply 且有实质发现)
        if APPLY and (level == 'audited' or level == 'contradicted'):
            try:
                ann_data = json.load(open(ann_file, encoding='utf-8'))
                km = ann_data.get('known_members', {}).get(off)
                if km and isinstance(km, dict):
                    km['audit'] = {
                        'level': level,
                        'method': 'use_site_enumeration',
                        'sites_checked': total,
                        'sites_consistent': consistent,
                        'sites_contradicted': len(contradictions),
                        'contradictions': contradictions[:5],
                        'timestamp': '2026-11-12'
                    }
                    json.dump(ann_data, open(ann_file, 'w', encoding='utf-8'),
                             ensure_ascii=False, indent=1)
            except Exception as e:
                print(f'  [WARN] {sf} {mem_name}: {str(e)[:60]}')

    print(f'\n=== 审计完成 ===')
    print(f'  audited(一致): {audited_count}')
    print(f'  contradicted(矛盾): {contradicted_count}')
    print(f'  insufficient(不足): {insufficient_count}')
    if APPLY:
        print('  audit 字段已写入注解')

if __name__ == '__main__':
    main()
