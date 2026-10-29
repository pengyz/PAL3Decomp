"""B2a vtable 槽归属对账（2026-10-29）——认领×二进制逐槽对证（T1 27 槽法推广）。
产出 P 档判定：vtable_confirmed / misowned / multi_owned；Q 档证据充实。
用法: python3 tools/audit_vtable_ownership.py
"""
import glob
import json
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CODE_LO, CODE_HI = 0x401000, 0x580000


def _norm(a):
    try:
        return hex(int(str(a), 16))
    except ValueError:
        return None   # 'external' 等哨兵


def verify_slot_claim(claimed_addr, binary_slot_value):
    """认领槽址 == 二进制槽值？"""
    return int(str(claimed_addr), 16) == int(binary_slot_value)


def classify_ownership(claim_cls, addr, ownership, located_classes=frozenset()):
    """归属判定（R2 契约）：absence 禁判 P（不准确=不判定）——
    P:misowned 需正向反证（认领类表已定位且不含该址 + 他类表实含）。"""
    n = _norm(addr)
    recs = ownership.get(n, []) or next(
        (v for k, v in ownership.items() if _norm(k) == n), [])
    if not recs:
        return 'Q:not_in_located_tables'
    clss = {r[0] for r in recs}
    if claim_cls in clss:
        return 'P:multi_owned' if len(clss) > 1 else 'P:vtable_confirmed'
    return 'P:misowned' if claim_cls in located_classes else 'Q:table_not_located'


def dump_segment(lo, hi):
    """objdump -s 区段 → {va: byte}（一次性缓存）。"""
    out = subprocess.run(['objdump', '-s', '--start-address=0x%x' % lo,
                          '--stop-address=0x%x' % hi, str(ROOT / 'original/PAL3.exe')],
                         capture_output=True, text=True).stdout
    mem = {}
    for line in out.splitlines():
        m = re.match(r'^\s([0-9a-f]{6,8})\s((?:[0-9a-f]{2,8}\s+){1,4})', line)
        if not m:
            continue
        va = int(m.group(1), 16)
        off = 0
        for tok in m.group(2).split():
            if re.fullmatch(r'[0-9a-f]{2,8}', tok):
                b = bytes.fromhex(tok)
                for i in range(0, len(b)):
                    mem[va + off + i] = b[i]
                off += len(b)
    return mem


def read_u32(mem, va):
    xs = [mem.get(va + i) for i in range(4)]
    if any(x is None for x in xs):
        return None
    return int.from_bytes(bytes(xs), 'little')


def find_table(mem, func_addrs):
    """认领槽序列（函数址列表）在二进制中定位真表址（序列匹配，认领 addr 约定不可靠）。"""
    vals = []
    for a in func_addrs:
        n = _norm(a)
        if not n:
            return None
        vals.append(int(n, 16))
    if not vals:
        return None
    bases = [va for va in mem if mem.get(va) == vals[0] & 0xFF and read_u32(mem, va) == vals[0]]
    for b in bases:
        ok = True
        for i, v in enumerate(vals):
            if read_u32(mem, b + 4 * i) != v:
                ok = False
                break
        if ok:
            return b
    return None


def main():
    claims = {}
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        nm = d.get('name')
        for vt in d.get('vtables') or []:
            if vt.get('addr') and _norm(vt['addr']):
                claims[_norm(vt['addr'])] = (nm, vt)
    mem = {}
    mem.update(dump_segment(0x550000, 0x580000))
    ownership = {}
    slot_mismatch = []
    located = set()
    for va, (nm, vt) in claims.items():
        seq = [cs.get('addr') for cs in (vt.get('slots') or []) if cs.get('addr')]
        base = find_table(mem, seq)
        if base is None:
            slot_mismatch.append((nm, va, 'TABLE_NOT_FOUND', seq[:2]))
            continue
        located.add(nm)
        for i, cs in enumerate(vt.get('slots') or []):
            faddr = cs.get('addr')
            if not faddr or not _norm(faddr):
                continue
            bv = read_u32(mem, base + 4 * i)
            if bv is None or not verify_slot_claim(faddr, bv):
                slot_mismatch.append((nm, hex(base), faddr, hex(bv) if bv else None))
            else:
                ownership.setdefault(_norm(faddr), []).append((nm, i, hex(base)))
    verdicts = {}
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        nm = d.get('name')
        for addr, info in (d.get('methods') or {}).items():
            if not isinstance(info, dict):
                continue
            v = classify_ownership(nm, _norm(addr), ownership, located)
            if v != 'not_in_vtables':
                verdicts.setdefault(v, []).append((nm, addr, info.get('name')))
    res = {'verdict_counts': {k: len(v) for k, v in verdicts.items()},
           'slot_mismatch': slot_mismatch[:50],
           'misowned': verdicts.get('P:misowned', [])[:100],
           'multi_owned_sample': verdicts.get('P:multi_owned', [])[:30]}
    Path(ROOT / 'data/status/vtable_ownership_census.json').write_text(
        json.dumps(res, ensure_ascii=False, indent=2))
    print('判定分布:', res['verdict_counts'], '| 槽不一致:', len(slot_mismatch))


if __name__ == '__main__':
    main()
