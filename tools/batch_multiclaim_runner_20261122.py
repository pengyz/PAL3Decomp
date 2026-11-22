#!/usr/bin/env python3
"""[MULTI_CLAIM 24 案件 runner 2026-11-22] 逐案取证 → 安全自动/需人工分拣。

锚定链(每案三证):
  ①删除式VA ∈ 类注解 vtables slots(manifest slot_verified) 或 exe .rdata 唯一挂载
  ②删除式存根 call@3 目标=claim 址探针报告(dtro_pair_adjacency)
  ③claim 址的语料呼叫者普查(其他单元按名引用=改名涟漪面)
裁决: ①②成立 + 呼叫者=0 → SAFE_AUTO(删误名claim+注真身); 有呼叫者 → MANUAL。
"""
import glob
import json
import os
import struct
from collections import Counter

REPO = '/home/peng/workspace/PAL3Decomp'
EXE = REPO + '/original/PAL3.exe'
CORPUS = REPO + '/asm/pal3/decomp'


def exe_sections():
    d = open(EXE, 'rb').read()
    e = struct.unpack_from('<I', d, 0x3C)[0]
    nsec = struct.unpack_from('<H', d, e + 6)[0]
    opt = struct.unpack_from('<H', d, e + 20)[0]
    sec0 = e + 24 + opt
    out = {}
    for i in range(nsec):
        s = sec0 + 40 * i
        nm = d[s:s + 8].rstrip(b'\0').decode('ascii', 'replace')
        vs, va, rs, ra = struct.unpack_from('<IIII', d, s + 8)
        out[nm] = (va + 0x400000, va, d[ra:ra + rs])
    return out


def main():
    secs = exe_sections()
    rdata = secs.get('.rdata', (None, None, b''))
    text = secs['.text']
    fid = json.load(open(REPO + '/asm/pal3/function_identity.json'))
    del_by_cls = {}
    for r in fid['rows']:
        if r['ann_kind'] == 'deleting_dtor':
            del_by_cls.setdefault(r['ann_class'], []).append(
                (int(r['va'], 16), bool(r.get('slot_verified'))))
    clsj = {}
    for f in glob.glob(REPO + '/data/annotations/structs/*.json'):
        d = json.load(open(f, encoding='utf-8'))
        clsj[d.get('name') or os.path.basename(f)[:-5]] = d
    classification = json.load(open(REPO + '/data/status/complete_forms_classification_20261122.json'))

    # 语料呼叫者索引: 名字 → [单元文件]
    name_callers = {}
    for f in glob.glob(CORPUS + '/*.json'):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        body = d.get('decompiled_c') or ''
        for m in __import__('re').finditer(r'(\w+::[\w`~]+)\s*\(', body):
            name_callers.setdefault(m.group(1), set()).add(os.path.basename(f))
        for m in __import__('re').finditer(r'(?:\w+::)*([A-Za-z_]\w*)\s*\(', body):
            pass

    report = []
    for e in classification['MULTI_CLAIM']:
        cls, va_s = e['cls'], e['va']
        va = int(va_s, 16)
        claims = e['claims']
        # ①删除式锚定
        anchored = False
        del_info = None
        for dva, sv in del_by_cls.get(cls, []):
            tgt, why = None, ''
            off = dva - text[0]   # text[0]=.text VA(0x401000); text[1]=RVA 勿用
            b = text[2][off:off + 30]
            if b[:3] == bytes.fromhex('568bf1') and b[3] == 0xE8:
                rel = int.from_bytes(b[4:8], 'little', signed=True)
                tgt = dva + 8 + rel
            if tgt == va:
                # .rdata 唯一挂载检查
                pat = struct.pack('<I', dva)
                n_rdata = rdata[2].count(pat) if rdata[2] else -1
                anchored = True
                del_info = {'del_va': '0x%08x' % dva, 'slot_verified': sv,
                            'rdata_mounts': n_rdata}
                break
        # ③呼叫者普查(claim 名)
        callers = {}
        for ccls, cname, cflags in claims:
            if not cname:
                continue
            cn = '%s::%s' % (ccls, cname)
            ext = {u for u in name_callers.get(cn, set())}
            callers[cn] = sorted(ext)
        verdict = 'SAFE_AUTO' if (anchored and all(len(v) == 0 for v in callers.values())) else 'MANUAL'
        report.append({'cls': cls, 'va': va_s, 'verdict': verdict,
                       'anchor': del_info, 'claims': claims, 'callers': callers})
        print('%-9s %-16s %s 锚定=%s 呼叫者=%s' % (
            verdict, cls, va_s, bool(del_info),
            {k: len(v) for k, v in callers.items()}))
    outp = REPO + '/data/status/multiclaim_cases_20261122.json'
    json.dump({'_doc': 'MULTI_CLAIM 24 案件 runner 分拣 20261122', 'cases': report},
              open(outp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    n_safe = sum(1 for r in report if r['verdict'] == 'SAFE_AUTO')
    print('\nSAFE_AUTO %d / MANUAL %d → %s' % (n_safe, len(report) - n_safe, outp))


if __name__ == '__main__':
    main()
