import json, os, collections

STRUCTS_DIR = 'data/annotations/structs'

def load():
    addr_to_classes = collections.defaultdict(set)
    class_vtable_from = {}   # (cls, addr) -> from
    for fn in sorted(os.listdir(STRUCTS_DIR)):
        if not fn.endswith('.json'):
            continue
        cls = fn[:-5]
        d = json.load(open(os.path.join(STRUCTS_DIR, fn), encoding='utf-8'))
        for addr in (d.get('methods') or {}).keys():
            addr_to_classes[addr].add(cls)
        for vt in d.get('vtables') or []:
            for slot in vt.get('slots') or []:
                a = slot.get('addr')
                if a:
                    class_vtable_from[(cls, a)] = slot.get('from')
    return addr_to_classes, class_vtable_from

def audit():
    addr_to_classes, class_vtable_from = load()
    multi = {a: c for a, c in addr_to_classes.items() if len(c) > 1}
    resolvable, unresolved = [], []
    for addr, classes in sorted(multi.items()):
        # vtable 槽 from=None 的类 = 自认原创（根）
        roots = [c for c in classes
                 if class_vtable_from.get((c, addr), '_') is None]
        if len(roots) == 1:
            resolvable.append({
                'addr': addr, 'owner': roots[0],
                'evidence': 'vtable_from_null_unique',
                'claimants': sorted(classes)})
        else:
            unresolved.append({
                'addr': addr, 'claimants': sorted(classes),
                'reason': 'multiple_from_null' if roots else 'no_from_null',
                'roots': sorted(roots)})
    return {'multi_decl_addrs': sorted(multi.keys()),
            'resolvable': resolvable, 'unresolved': unresolved}

if __name__ == '__main__':
    out = audit()
    json.dump(out, open('data/status/_naming_audit_A1.json', 'w'),
              indent=2, ensure_ascii=False)
    print('multi=%d resolvable=%d unresolved=%d'
          % (len(out['multi_decl_addrs']), len(out['resolvable']),
             len(out['unresolved'])))
