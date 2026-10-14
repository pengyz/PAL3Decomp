import json, os, collections, re
import os as _os
_REPO=_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__)))
STRUCTS_DIR=_os.path.join(_REPO,'data','annotations','structs')
def param_list(sig):
    last=None; depth=0; start=None
    for j,ch in enumerate(sig):
        if ch=='(':
            if depth==0: start=j
            depth+=1
        elif ch==')':
            depth-=1
            if depth==0: last=(start,j)
    return None if not last else sig[last[0]+1:last[1]]
def split_params(p):
    if p is None: return None
    p=p.strip()
    if p=='' : return []
    parts=[]; depth=0; cur=''
    for ch in p:
        if ch in '([<': depth+=1
        elif ch in ')]>': depth-=1
        if ch==',' and depth==0: parts.append(cur.strip()); cur=''
        else: cur+=ch
    if cur.strip(): parts.append(cur.strip())
    return parts
TK={'int','char','short','long','float','double','void','bool','unsigned','signed','const','struct','class','enum','union','_BYTE','_WORD','_DWORD','_QWORD','_BOOL','BOOL','DWORD','WORD','BYTE','UINT','HWND','HANDLE','HRESULT','size_t'}
def norm(params):
    out=[]
    for pr in params:
        pr=pr.split('=')[0].strip()
        if not pr: continue
        if pr=='this': continue
        toks=pr.replace('*',' * ').replace('&',' & ').split()
        if toks and toks[-1]=='this': continue
        t=pr.split()
        typ=' '.join(t[:-1]) if (len(t)>=2 and re.fullmatch(r'[A-Za-z_]\w*',t[-1]) and t[-1] not in TK) else pr
        out.append(re.sub(r'\s+','',typ))
    return tuple(out)
def load():
    rows=[]
    for fn in sorted(os.listdir(STRUCTS_DIR)):
        if not fn.endswith('.json'): continue
        cls=fn[:-5]; d=json.load(open(os.path.join(STRUCTS_DIR,fn),encoding='utf-8'))
        for addr,info in (d.get('methods') or {}).items():
            sig=info.get('signature','') or ''
            rows.append((cls,addr,info.get('name',''),sig,norm(split_params(param_list(sig)) or [])))
    fj=json.load(open(_os.path.join(_REPO,'data','annotations','functions.json'),encoding='utf-8'))
    for addr,info in fj.items():
        sig=info.get('signature','') or ''
        rows.append(('<free>',addr,info.get('name',''),sig,norm(split_params(param_list(sig)) or [])))
    return rows
rows=load()
groups=collections.defaultdict(list)
for cls,addr,name,sig,tl in rows: groups[(cls,name)].append((addr,sig,tl))
clusters={k:v for k,v in groups.items() if len(v)>=2}
def is_dtor_name(n): return n.startswith('~') or 'deleting destructor' in n or n.startswith('_scalar_dtor') or 'scalar_dtor' in n or 'dtor' in n.lower()
buckets=collections.Counter()
rows_out=[]
for (cls,name),items in sorted(clusters.items()):
    bysig=collections.defaultdict(list)
    for addr,sig,tl in items: bysig[tl].append((addr,sig))
    clash=[g for g in bysig.values() if len(g)>=2]
    dtor=is_dtor_name(name)
    if clash and dtor: b='BOTH(真clash+dtor)'
    elif clash: b='真clash'
    elif dtor: b='删除析构族'
    else: b='合法重载'
    buckets[b]+=1
    rows_out.append((b,cls,name,len(items)))
print("=== SCAN: python3 /tmp/scan_scope.py ===")
print("structural same-name clusters ((cls,name)>=2 methods + <free> funcs): %d" % len(clusters))
print("cluster-size dist:", dict(sorted(collections.Counter(len(v) for v in clusters.values()).items())))
print()
print("=== SCOPE BUCKETS (captain 三分类) ===")
for b in ['真clash','BOTH(真clash+dtor)','删除析构族','合法重载']:
    print("  %-22s : %d 簇" % (b, buckets[b]))
print()
print("=== IN-SCOPE this task (真-clash ∪ 删除析构族) ===")
for b,cls,name,n in rows_out:
    if b in ('真clash','BOTH(真clash+dtor)','删除析构族'):
        print("  [%s] %s::%s (n=%d)"%(b,cls,name,n))
print()
print("=== OUT-OF-SCOPE (合法重载 → 698 语义命名战役): %d 簇 ==="%buckets['合法重载'])
