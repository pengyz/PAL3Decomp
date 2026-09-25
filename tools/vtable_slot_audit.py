"""vtable 槽签名审计：对全部槽位做「声明签名 × ret-N 指令级证据」逐槽核对。

用法: python tools/vtable_slot_audit.py [--apply-dry | --emit-plan]
输出: data/status/_vtable_slot_audit.json
  per-slot: {class, vtable_idx, slot_idx, addr, resolve, tier, declared_arity,
             evidence_retn, verdict}
  proposals: 按「槽地址」分组的一致签名修正计划（同地址跨类必须同签名）。

判定基准（MSVC6 __thiscall 被调方自清栈）：函数尾 `ret N` 的 N = 栈参数字节数
（4/槽）。声明签名剥掉 `Cls *this` 后的参数个数 == N/4 ⇒ OK。
证据缺失/多值(mixedret) ⇒ unknown（不提案，不猜）。

门禁口径对齐 vtable_mapper：own 槽须在本类 methods；继承槽可在基类 methods 或
基类 vtable 声明。管线工具（tools/，复用）。
"""
import json, os, re, sys, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STRUCTS_DIR = os.path.join(ROOT, 'data', 'annotations', 'structs')
RET_PATH = os.path.join(ROOT, 'data', 'status', '_ret_n_batch.json')
OUT_PATH = os.path.join(ROOT, 'data', 'status', '_vtable_slot_audit.json')


def load_structs():
    out = {}
    for fn in sorted(os.listdir(STRUCTS_DIR)):
        if not fn.endswith('.json'):
            continue
        d = json.load(open(os.path.join(STRUCTS_DIR, fn), encoding='utf-8'))
        out[fn[:-5]] = d          # 按文件名键（与 vtable_mapper.load_all 对齐；重名类不互相覆盖）
    return out


def parse_declared(sig):
    """声明签名 -> (ret, stack_params)。剥 `Cls *this`/`Cls *__hidden this` 首参。"""
    if not sig:
        return None
    m = re.search(r'^(.*?)\b__thiscall\b\s*(?:[\w:]+\s*)?\((.*)\)\s*$', sig.strip())
    if m:
        ret, params = m.group(1).strip(), m.group(2)
    else:
        m = re.search(r'^([\w:]+)\s*\((.*)\)\s*$', sig.strip())
        if not m:
            return None
        ret, params = m.group(1), m.group(2)
    plist = [p.strip() for p in params.split(',') if p.strip()]
    if plist and re.match(r'^\w+\s*\*+\s*(?:__hidden\s+)?this$', plist[0]):
        plist = plist[1:]
    if plist == ['void'] or plist == ['']:
        plist = []
    return ret, plist


def slot_entry(structs, cn, slot):
    """门禁同款解析：返回 (entry_dict|None, resolve_path)。"""
    addr = slot.get('addr')
    ai = int(addr, 16)
    variants = (addr, '0x%08X' % ai, hex(ai), str(ai))
    d = structs.get(cn)
    for v in variants:
        if v in (d.get('methods') or {}):
            return d['methods'][v], 'own'
    fb = slot.get('from')
    if fb and fb in structs:
        bd = structs[fb]
        bm = bd.get('methods') or {}
        for v in variants:
            if v in bm:
                return bm[v], 'inherit-table'
        for bvt in (bd.get('vtables') or []):
            if isinstance(bvt, dict) and any(bs.get('addr') == addr for bs in (bvt.get('slots') or [])):
                return None, 'inherit-decl-only'
    return None, 'unresolved'


def main():
    structs = load_structs()
    rets = json.load(open(RET_PATH))
    per_slot = []
    proposals = {}   # addr -> {'classes': [...], 'evidence': N, 'cur': [...], 'decl': ret}
    for cn in sorted(structs):
        d = structs[cn]
        methods = d.get('methods') or {}
        for vi, vt in enumerate(d.get('vtables') or []):
            if not isinstance(vt, dict):
                continue
            for si, slot in enumerate(vt.get('slots') or []):
                addr = slot.get('addr')
                e, path = slot_entry(structs, cn, slot)
                rec = {'class': cn, 'vt': vi, 'slot': si, 'addr': addr, 'resolve': path}
                if e is None:
                    rec['verdict'] = 'unresolved' if path == 'unresolved' else 'decl-only'
                    rec['name'] = (e or {}).get('name') if e else None
                    per_slot.append(rec)
                    continue
                name = e.get('name', '')
                rec['name'] = name
                if '_scalar_dtor' in name or name.startswith('_sdtor') or 'scalar_deleting_dtor' in name:
                    rec['verdict'] = 'dtor-placeholder'
                elif re.match(r'^(sub_|nullsub|_\w*sub_)', name):
                    rec['verdict'] = 'unnamed-member'
                else:
                    rec['verdict'] = 'named'
                sig = e.get('signature', '') or ''
                dec = parse_declared(sig)
                rec['declared_sig'] = sig
                ev = rets.get(addr)
                rec['evidence_retn'] = ev
                if dec is None:
                    rec['verdict'] += '|sig-unparseable'
                    rec['declared_sig'] = sig
                    per_slot.append(rec)
                    continue
                ret, params = dec
                rec['declared_arity'] = len(params)
                if not ev or len(set(ev)) != 1 or ev[0] % 4:
                    rec['verdict'] += '|evidence-none' if not ev else '|evidence-mixed'
                    per_slot.append(rec)
                    continue
                arity = ev[0] // 4
                rec['evidence_arity'] = arity
                if len(params) == arity:
                    rec['verdict'] += '|OK'
                else:
                    rec['verdict'] += '|ARITY-MISMATCH'
                    p = proposals.setdefault(addr, {'classes': [], 'evidence': ev[0],
                                                    'ret': ret, 'cur_sigs': set(),
                                                    'names': set()})
                    p['classes'].append(cn)
                    p['cur_sigs'].add(sig)
                    p['names'].add(name)
                per_slot.append(rec)
    # sig-unparseable 样本
    bad = [r for r in per_slot if 'sig-unparseable' in r.get('verdict', '')]
    for r in bad[:8]:
        print('  UNPARSEABLE:', r['class'], r['addr'], repr(r.get('declared_sig', ''))[:90])
    for v in proposals.values():
        v['cur_sigs'] = sorted(v['cur_sigs'])
        v['names'] = sorted(v['names'])
    json.dump({'per_slot': per_slot, 'proposals': proposals},
              open(OUT_PATH, 'w', encoding='utf-8'), indent=1, ensure_ascii=False)
    c = collections.Counter(r['verdict'].split('|')[0] + ('/' + r['verdict'].split('|')[-1] if '|' in r['verdict'] else '')
                            for r in per_slot)
    print('slots audited:', len(per_slot))
    for k, v in c.most_common():
        print('  %4d  %s' % (v, k))
    print('arity-mismatch addresses (proposals):', len(proposals))


if __name__ == '__main__':
    main()
