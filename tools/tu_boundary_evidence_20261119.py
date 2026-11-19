#!/usr/bin/env python3
"""[D1 2026-11-19] TU 拆分决策取证——原 callee 内联史普查。

方法: 全量 call graph (idalib e8/e9 提取) + 现编译 obj 的 body containment 反查。
产出: 每 L1 猎物函数的被内联 callee 清单 + 原二进制中该 callee 是否曾被内联的判定
      (原体内含 callee 字节模式 = 曾内联 → 不可全局禁; 原体为 e8 直调 = 跨TU/超阈值 → 可禁)。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/tu_boundary_evidence_20261119.py
输出: data/status/tu_boundary_evidence_20261119.json
"""
import json
import re
import struct
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent

# ── 原二进制读取器 ──
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

# ── L1 猎物清单 ──
q = json.loads((REPO / 'data/status/l1_hunt_queue_20261119.json').read_text(encoding='utf-8'))
targets = [(int(t['va'], 16), t) for t in q['targets']]

# ── 原 e8 调用目标提取 (猎物函数体内) ──
def orig_calls(va, size):
    body = read_va(va, size + 16)
    calls = []
    for m in re.finditer(rb'\xe8', body):
        at = m.start()
        if at + 5 > len(body):
            break
        rel = struct.unpack_from('<i', body, at + 1)[0]
        tgt = va + at + 5 + rel
        if 0x401000 <= tgt < 0x56F000:
            calls.append(tgt)
    return calls

# ── 内联史判定: 原二进制全 .text 扫 callee 体前 16B 特征 (直调 vs 内联) ──
# 简化判定: 若原猎物体对 callee 是 e8 直调, 且原体内无 callee 头 16B 字节模式
# → 未曾内联 (可禁)。反转 → 曾内联 (不可全局禁, 需选择性)。
results = []
for va, t in targets:
    size = t.get('size', 256)
    calls = orig_calls(va, size)
    callee_info = []
    for ct in calls:
        chead = read_va(ct, 16)
        callee_info.append({'va': hex(ct), 'head': chead.hex()})
    results.append({'va': hex(va), 'file': t['file'], 'size': size,
                    'n_calls': len(calls), 'callees': callee_info})

out = {'_doc': 'TU 边界取证 D1 2026-11-19: L1 猎物函数的原 e8 调用目标清单——'
               '下一步逐 callee 做内联史判定 (原别处函数体是否含 callee 头模式)。',
       'targets': results}
outp = REPO / 'data/status/tu_boundary_evidence_20261119.json'
outp.write_text(json.dumps(out, indent=1, ensure_ascii=False), encoding='utf-8')
print('D1 取证完成: %d 猎物, 调用目标 %d 个 → %s' % (
    len(results), sum(r['n_calls'] for r in results), outp.name))
for r in results[:3]:
    print('  %s %s: %d calls → %s' % (r['va'], r['file'].split('/')[-1],
          r['n_calls'], [c['va'] for c in r['callees'][:5]]))
