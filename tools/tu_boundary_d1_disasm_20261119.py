#!/usr/bin/env python3
"""[D1v2 2026-11-19] TU 边界取证反汇编级重建——capstone 线性反汇编提取真 e8 调用目标。

替换 v1 朴素字节扫描 (伪 e8 于操作数/边界错位)。线性反汇编自函数起点, 指令边界
由 capstone 保证; 调用目标 = va + insn.address + 5 + rel (e8 rel32)。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/tu_boundary_d1_disasm_20261119.py
输出: data/status/tu_boundary_evidence_20261119.json (v2 覆盖, reliability=DISASM)
"""
import json
import struct
import sys
from pathlib import Path

import capstone
import re

REPO = Path(__file__).parent.parent

exe = open(REPO / 'original/PAL3.exe', 'rb').read()
_pe = struct.unpack_from('<I', exe, 0x3C)[0]
_nsec = struct.unpack_from('<H', exe, _pe + 6)[0]
_opt = struct.unpack_from('<H', exe, _pe + 20)[0]
_secoff = _pe + 24 + _opt
_ib = struct.unpack_from('<I', exe, _pe + 24 + 28)[0]
_secs = []
for _i in range(_nsec):
    so = _secoff + _i * 40
    vsize, sva, rsize, raw = struct.unpack_from('<IIII', exe, so + 8)
    _secs.append((sva, vsize, raw, rsize))

def read_va(va, n):
    rva = va - _ib
    for sva, vsize, raw, rsize in _secs:
        if sva <= rva < sva + vsize:
            off = raw + (rva - sva)
            return exe[off:off + n]
    return b''

_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_md.detail = True

def disasm_calls(va, size):
    """线性反汇编, 返回 (调用目标表, 尾跳目标)。指令边界由 capstone 保证。"""
    code = read_va(va, size + 16)
    calls, tail_jumps = [], []
    for insn in _md.disasm(code, va):
        if insn.mnemonic == 'call':
            mm = re.match(r'^0x([0-9a-f]+)$', insn.op_str)
            if mm:
                tgt = int(mm.group(1), 16)
                if 0x401000 <= tgt < 0x570000:
                    calls.append(tgt)
        elif insn.mnemonic == 'jmp':
            mm = re.match(r'^0x([0-9a-f]+)$', insn.op_str)
            if mm:
                tgt = int(mm.group(1), 16)
                if va <= tgt < va + size:
                    continue  # 函数内跳转
                tail_jumps.append(tgt)
        if insn.address > va + size:
            break
    return calls, tail_jumps

q = json.loads((REPO / 'data/status/l1_hunt_queue_20261119.json').read_text(encoding='utf-8'))
results = []
for t in q['targets']:
    va = int(t['va'], 16)
    size = t.get('size', 256)
    calls, tails = disasm_calls(va, size)
    results.append({'va': t['va'], 'file': t['file'], 'size': size,
                    'n_calls': len(calls),
                    'calls': [hex(c) for c in calls],
                    'tail_jumps': [hex(c) for c in tails]})

out = {'_doc': 'D1v2 反汇编级调用目标 2026-11-19 (capstone 线性反汇编, 指令边界保证)。',
       'reliability': 'DISASM',
       'targets': results}
outp = REPO / 'data/status/tu_boundary_evidence_20261119.json'
outp.write_text(json.dumps(out, indent=1, ensure_ascii=False), encoding='utf-8')
print('D1v2 完成:')
for r in results:
    print('  %s %-24s %d calls %s' % (r['va'], r['file'].split('/')[-1],
          r['n_calls'], r['calls'][:6]))
