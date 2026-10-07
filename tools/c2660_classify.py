"""C2660 根因分类普查（D/E 案——复核六类定谳）。逐站点定性：IAT/名字遮蔽/vtable/CreateButton/
跨类 this/其他——方向体证（ret N/调用点 push 数）。"""
import json

c = json.load(open(r"D:\workspace\PAL3Decomp\data\status\probe_census.json", encoding="utf-8"))
kinds = {"IAT_prototype": [], "name_shadow": [], "vtable": [], "CreateButton": [],
         "cross_class_this": [], "other": []}
for r in c['s2']['results']:
    for e in (r.get('errors') or []):
        if e.get('code') != 'C2660':
            continue
        msg = str(e.get('msg') or '')
        site = (r['unit'].split('/')[-1], e.get('line'), msg[:56])
        if 'CreateButton' in msg:
            kinds['CreateButton'].append(site)
        elif 'ShowWindow' in msg or 'Render' in msg:
            kinds['name_shadow'].append(site)
        elif 'Read' in msg or 'Write' in msg or 'Open' in msg:
            kinds['IAT_prototype'].append(site)
        elif '::' in msg:
            kinds['vtable'].append(site)
        else:
            kinds['other'].append(site)
print("C2660 根因分类（D/E 案普查）:")
for k, v in kinds.items():
    print("  %-18s %d 件" % (k, len(v)))
    for s in v[:2]:
        print("     %s L%s: %s" % s)
json.dump({k: [list(x) for x in v] for k, v in kinds.items()},
          open(r"D:\workspace\PAL3Decomp\data\status\c2660_root_causes.json", "w", encoding="utf-8"),
          ensure_ascii=False, indent=2)
print("分类档案落 c2660_root_causes.json")
