#!/usr/bin/env python3
"""Access-radius measurement for PAL3Decomp annotation adjudication.

For a function VA, reports max(this + disp) over its .text bytes — the
compiler-generated evidence of how large the `this` object must be.
Covers ALL [reg+disp] modrm forms (the ad-hoc probes used during the
inheritance investigation only matched [esi/edi+disp], systematically
underestimating — e.g. IsRunning's mov eax,[ecx+368h] was invisible).

Usage:  python3 tools/access_radius.py 0xFUNCTION [0xFN2 ...]
"""
import json
import struct
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
EXE = REPO / 'original' / 'PAL3.exe'
IMGBASE = 0x400000


def max_this_disp(seg):
    big = 0
    i = 0
    while i < len(seg) - 7:
        op = seg[i]
        if op in (0x8B, 0x89, 0xC7, 0x88, 0xC6, 0x3B, 0x39, 0x83):
            modrm = seg[i + 1]
            mod, rm = modrm >> 6, modrm & 7
            rm_eff = rm - (4 if rm == 4 else 0)  # skip SIB detail
            if mod == 1 and rm != 4:
                d = seg[i + 2]
                if d > 0x7F:
                    d -= 0x100
                big = max(big, abs(d))
                i += 3
                continue
            if mod == 2 and rm != 4:
                d = struct.unpack_from('<I', seg, i + 2)[0]
                if d < 0x30000:
                    big = max(big, d)
                i += 6
                continue
        i += 1
    return big


def main():
    data = EXE.read_bytes()
    fns = sorted({int(k, 16) for k in
                  json.loads((REPO / 'data' / 'annotations' / 'functions.json').read_text(encoding='utf-8'))
                  if 0x401000 <= int(k, 16) <= 0x5695D0})
    import bisect
    for arg in sys.argv[1:]:
        va = int(arg, 16)
        idx = bisect.bisect_right(fns, va) - 1
        f0 = fns[idx]
        f1 = fns[idx + 1] if idx + 1 < len(fns) else 0x5695D0
        seg = data[f0 - IMGBASE:f1 - IMGBASE]
        print('%08X-%08X (%dB) max this+disp = 0x%X' % (f0, f1, f1 - f0, max_this_disp(seg)))


if __name__ == '__main__':
    main()
