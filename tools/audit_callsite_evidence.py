#!/usr/bin/env python3
"""调用点实参取证（**只读**）——任务 0：恢复 10 个丢绿单元计划的前置取证工具。

回答一个问题：**目标函数的每个静态调用点，在 `call` 之前往寄存器/栈里放了什么**。
产出可复现的证据（objdump 命令 + VA + 原始反汇编行），不给"看起来像"。

关键设计：**先全量反汇编、再按 VA 定位**，绝不手拼 `--start-address`。
（此前三次手搓 objdump 管道均因起点落在指令中间而得到错位解码 —— 例如
`--start-address=0x4b0ae0` 会把 `mov al,ds:0x5cefa8` 解码成 `test al,0xef; pop esp; ...`。
本工具把 `objdump -d -M intel original/PAL3.exe` 的全量输出缓存下来后按行解析，
指令边界由反汇编器从节起点线性给出 ⇒ 边界永远是对的。）

对外接口::

    audit_callsite(target_va) -> {'callsites': [{va, pushes, regs, raw, ...}],
                                  'verdict': 'direct' | 'virtual-only' | 'none', ...}

    callsite['pushes']  每个 push 的实参形态：kind = 'imm' | 'imm_str' | 'reg' | 'mem' | 'other'
    callsite['regs']    窗口内 mov/movzx/movsx/lea 逐条，带 `width` 宽度取证（任务 5 依赖）：
                        mov ⇒ 4B（byte/word 源则 1B/2B）、movzx ⇒ 1B、lea ⇒ 'addr'（取址）
    callsite['raw']     窗口 + call 行的 objdump 原始反汇编行（逐字，可复现）

只读约束：本工具不写任何 annotation / 生成态 / 管线代码；唯一写盘是反汇编缓存
`data/status/_disasm_cache.txt`（简报要求的产物，`--no-cache` 可绕过）。

用法::

    python tools/audit_callsite_evidence.py 0x440960            # 人读报告
    python tools/audit_callsite_evidence.py 0x440960 --width    # 附 mov/movzx/lea 宽度列
    python tools/audit_callsite_evidence.py 0x440960 0x43d890 --json
"""
import argparse
import json
import os
import re
import struct
import subprocess
import sys
from collections import deque

REPO = os.environ.get('PAL3_REPO') or os.path.dirname(os.path.dirname(
    os.path.abspath(__file__)))
DEFAULT_EXE = os.path.join(REPO, 'original', 'PAL3.exe')
DEFAULT_CACHE = os.path.join(REPO, 'data', 'status', '_disasm_cache.txt')

# 反汇编命令（报告里逐字引用；实际执行用绝对路径，与 cwd 无关）
OBJDUMP_CMD = 'objdump -d -M intel original/PAL3.exe'

# 窗口双重上限（简报接口签名 window=0x80 + 实现要点 2「向前取最多 12 条指令」）
DEFAULT_WINDOW_BYTES = 0x80
MAX_LOOKBACK_INSTRS = 12

_REG_SIZE = {}
for _r in ('al', 'cl', 'dl', 'bl', 'ah', 'ch', 'dh', 'bh'):
    _REG_SIZE[_r] = 1
for _r in ('ax', 'cx', 'dx', 'bx', 'sp', 'bp', 'si', 'di'):
    _REG_SIZE[_r] = 2
for _r in ('eax', 'ecx', 'edx', 'ebx', 'esp', 'ebp', 'esi', 'edi'):
    _REG_SIZE[_r] = 4

# 顺序敏感：'WORD PTR' 是 'DWORD PTR'/'QWORD PTR' 的子串、'BYTE PTR' 是 'TBYTE PTR' 的子串
# ⇒ 必须长关键字在前（实测踩过：'DWORD PTR [esp+0x50]' 被误判 2B）
_PTR_SIZE = (('TBYTE PTR', 10), ('QWORD PTR', 8), ('DWORD PTR', 4),
             ('WORD PTR', 2), ('BYTE PTR', 1))

_MEMO = {}          # (exe, cache, target, window, max_instrs) -> result
_SECTIONS = {}      # exe -> [section dicts]
_EXE_BYTES = {}     # exe -> bytes


# --------------------------------------------------------------------- PE 布局
def pe_sections(exe_path):
    """PE 节表（VA/文件偏移/可执行位）。与 tools/fpu_type_audit.py 的解析同语义。"""
    exe_path = os.path.abspath(exe_path)
    if exe_path in _SECTIONS:
        return _SECTIONS[exe_path]
    data = open(exe_path, 'rb').read()
    e_lfanew = struct.unpack_from('<I', data, 0x3c)[0]
    nsec = struct.unpack_from('<H', data, e_lfanew + 6)[0]
    optsz = struct.unpack_from('<H', data, e_lfanew + 20)[0]
    imagebase = struct.unpack_from('<I', data, e_lfanew + 24 + 28)[0]
    sect = e_lfanew + 24 + optsz
    out = []
    for i in range(nsec):
        h = sect + i * 40
        name = data[h:h + 8].rstrip(b'\x00').decode('ascii', 'replace')
        vsz, vaddr, rsz, roff = struct.unpack_from('<IIII', data, h + 8)
        chars = struct.unpack_from('<I', data, h + 36)[0]
        out.append({'name': name,
                    'va': imagebase + vaddr,
                    'vsize': max(vsz, rsz),
                    'raw_off': roff,
                    'raw_size': rsz,
                    'exec': bool(chars & 0x20000000)})
    _SECTIONS[exe_path] = out
    _EXE_BYTES[exe_path] = data
    return out


def _section_at(sections, va):
    for s in sections:
        if s['va'] <= va < s['va'] + s['vsize']:
            return s
    return None


def _string_at(exe_path, va, max_len=256):
    """va 指向**非可执行节**里的可打印 ASCII（NUL 结尾）⇒ 返回字符串，否则 None。"""
    sections = pe_sections(exe_path)
    sec = _section_at(sections, va)
    if sec is None or sec['exec']:
        return None
    data = _EXE_BYTES[exe_path]
    off = sec['raw_off'] + (va - sec['va'])
    end = sec['raw_off'] + sec['raw_size']
    stop = min(off + max_len, end, len(data))
    chunk = data[off:stop]
    nul = chunk.find(b'\x00')
    if nul <= 0:
        return None
    body = chunk[:nul]
    if not all(0x20 <= b <= 0x7e for b in body):
        return None
    return body.decode('ascii')


# ------------------------------------------------------- 全量反汇编（缓存复用）
def disasm_cache(exe_path=DEFAULT_EXE, cache_path=DEFAULT_CACHE, use_cache=True):
    """返回全量反汇编文本的缓存路径。缺失/陈旧（exe 比缓存新）/use_cache=False ⇒ 重新生成。"""
    exe_path = os.path.abspath(exe_path)
    cache_path = os.path.abspath(cache_path)
    fresh = (use_cache and os.path.exists(cache_path)
             and os.path.getsize(cache_path) > 0
             and os.path.getmtime(cache_path) >= os.path.getmtime(exe_path))
    if not fresh:
        os.makedirs(os.path.dirname(cache_path), exist_ok=True)
        cmd = ['objdump', '-d', '-M', 'intel', exe_path]
        with open(cache_path, 'wb') as fh:
            proc = subprocess.run(cmd, stdout=fh, stderr=subprocess.PIPE)
        if proc.returncode != 0:
            raise RuntimeError('objdump 失败 (%d): %s'
                               % (proc.returncode, proc.stderr.decode('utf-8', 'replace')[-400:]))
        if os.path.getsize(cache_path) == 0:
            raise RuntimeError('objdump 输出为空：%s' % ' '.join(cmd))
    return cache_path


# ------------------------------------------------------------ 反汇编行解析
_RX_ADDR = re.compile(r'^\s*([0-9a-fA-F]+):$')


def iter_instructions(cache_path):
    """逐条产出 (va, mnemonic, operands, bytes, raw)。

    objdump 的行形如::

        "  4b0b2f:\\t68 f8 37 5d 00       \\tpush   0x5d37f8"      ← 指令行（3 个 tab 字段）
        "  4b0b22:\\t00 "                                          ← 续行（2 个 tab 字段，字节没排完）

    续行的字节并入上一条指令的 `bytes`，绝不当作独立指令 —— 这就是"边界不错位"的来源。
    """
    cur = None
    with open(cache_path, 'r', encoding='utf-8', errors='replace') as fh:
        for line in fh:
            line = line.rstrip('\n')
            parts = line.split('\t')
            if len(parts) >= 3:
                m = _RX_ADDR.match(parts[0])
                if cur is not None:
                    yield cur
                    cur = None
                if not m:
                    continue
                va = int(m.group(1), 16)
                raw_bytes = ' '.join(p.strip() for p in parts[1:-1] if p.strip())
                asm = parts[-1].strip()
                sp = asm.find(' ')
                if sp < 0:
                    mnemonic, operands = asm, ''
                else:
                    mnemonic, operands = asm[:sp], asm[sp + 1:].strip()
                cur = [va, mnemonic, operands, raw_bytes, line]
            elif len(parts) == 2 and cur is not None and _RX_ADDR.match(parts[0]):
                extra = parts[1].strip()
                if extra:
                    cur[3] = (cur[3] + ' ' + extra).strip()
                continue
            else:
                if cur is not None:
                    yield cur
                cur = None
    if cur is not None:
        yield cur


def _imm_value(operands):
    op = operands.split()[0] if operands else ''
    if op.startswith('0x') or op.startswith('0X'):
        try:
            return int(op, 16)
        except ValueError:
            return None
    return None


def scan_callsites(cache_path, exe_path, target_va,
                   window=DEFAULT_WINDOW_BYTES, max_instrs=MAX_LOOKBACK_INSTRS):
    """全量扫描一次：返回 target_va 的全部静态 call 调用点的原始窗口快照。

    窗口 = call 之前**最多 `max_instrs` 条指令**且**不超过 `window` 字节**（双重上限）。
    """
    hits = []
    recent = deque()
    for va, mnemonic, operands, raw_bytes, raw in iter_instructions(cache_path):
        if mnemonic == 'call' and _imm_value(operands) == target_va:
            win = []
            for entry in recent:
                if va - entry[0] > window:
                    continue
                win.append(entry)
            hits.append({'call': {'va': va, 'mnemonic': mnemonic,
                                  'operands': operands, 'bytes': raw_bytes, 'raw': raw},
                         'window': win})
        recent.append((va, mnemonic, operands, raw_bytes, raw))
        if len(recent) > max_instrs:
            recent.popleft()
    return hits


# ------------------------------------------------------------ 形态/宽度分类
def _split_operands(operands):
    """按括号深度 0 的逗号切操作数（'eax,BYTE PTR [esi+0x5c]' → ['eax','BYTE PTR [esi+0x5c]']）。"""
    out, depth, cur = [], 0, ''
    for ch in operands:
        if ch == '[':
            depth += 1
        elif ch == ']':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def _operand_size(op):
    up = op.upper()
    for kw, sz in _PTR_SIZE:
        if kw in up:
            return sz
    return _REG_SIZE.get(op.strip().lower())


def instr_width(mnemonic, operands):
    """宽度取证（任务 5 依赖）：mov 4B / movzx 1B / lea 取址。

    返回 1/2/4/8/10（字节数）、'addr'（lea 取址）、None（非 mov/movzx/movsx/lea）。
    尺寸优先取操作数的显式 `BYTE/WORD/DWORD PTR`，否则按寄存器名宽度。
    """
    mn = mnemonic.lower()
    if mn == 'lea':
        return 'addr'
    if mn not in ('mov', 'movzx', 'movsx'):
        return None
    ops = _split_operands(operands)
    if not ops:
        return None
    if mn in ('movzx', 'movsx'):
        # 零/符号扩展：宽度看**源**操作数（movzx eax, BYTE PTR … ⇒ 1B）
        return _operand_size(ops[1]) if len(ops) > 1 else None
    return _operand_size(ops[0])


def _push_entry(exe_path, va, operands, raw_bytes, raw):
    op = operands.strip()
    entry = {'va': va, 'text': op, 'width': 4,
             'bytes': raw_bytes, 'raw': raw}
    if op.lower() in _REG_SIZE:
        entry['kind'] = 'reg'
        entry['reg'] = op.lower()
    else:
        val = _imm_value(op)
        if val is not None:
            entry['kind'] = 'imm'
            entry['value'] = val
            s = _string_at(exe_path, val)
            if s is not None:
                entry['kind'] = 'imm_str'      # 简报要点 3：数据节可打印 ASCII ⇒ imm_str
                entry['string'] = s
        elif '[' in op or ':' in op:
            entry['kind'] = 'mem'
        else:
            entry['kind'] = 'other'
    return entry


def _reg_entry(va, mnemonic, operands, raw_bytes, raw):
    ops = _split_operands(operands)
    dst = ops[0] if ops else ''
    return {'va': va, 'mnemonic': mnemonic, 'operands': operands,
            'dst': dst, 'dst_is_reg': dst.lower() in _REG_SIZE,
            'width': instr_width(mnemonic, operands),
            'bytes': raw_bytes, 'raw': raw}


# ------------------------------------------------------------------- 对外接口
def audit_callsite(target_va, window=DEFAULT_WINDOW_BYTES, exe_path=DEFAULT_EXE,
                   cache_path=DEFAULT_CACHE, use_cache=True):
    """返回 target_va 的静态调用点与每个调用点紧邻的 push/reg 形态。

    返回结构::

        {'callsites': [{'va': 调用指令 VA,
                        'pushes': [push 形态…], 'regs': [mov/lea 形态…],
                        'widths': [regs 的宽度…], 'raw': [objdump 原始行…]}],
         'verdict': 'direct'            # 找到静态 call
                 | 'virtual-only'      # 全量扫描无 call 命中（virtual/间接调用/死码）
                 | 'none',             # target_va 不在任何可执行节内
         'target_va': …, 'window': …, 'max_instrs': …,
         'objdump_cmd': 'objdump -d -M intel original/PAL3.exe',
         'exe': …, 'cache': …}
    """
    exe_path = os.path.abspath(exe_path)
    cache_path = os.path.abspath(cache_path)
    key = (exe_path, cache_path, int(target_va), int(window), MAX_LOOKBACK_INSTRS, use_cache)
    if key in _MEMO:
        return _MEMO[key]

    cache = disasm_cache(exe_path, cache_path, use_cache=use_cache)
    hits = scan_callsites(cache, exe_path, int(target_va), window=window)

    callsites = []
    for hit in hits:
        call = hit['call']
        pushes = [_push_entry(exe_path, e[0], e[2], e[3], e[4])
                  for e in hit['window'] if e[1] == 'push']
        regs = [_reg_entry(e[0], e[1], e[2], e[3], e[4])
                for e in hit['window'] if e[1] in ('mov', 'movzx', 'movsx', 'lea')]
        raw = [e[4] for e in hit['window']] + [call['raw']]
        callsites.append({'va': call['va'], 'pushes': pushes, 'regs': regs,
                          'widths': [r['width'] for r in regs], 'raw': raw})

    if callsites:
        verdict = 'direct'
    elif _section_at(pe_sections(exe_path), int(target_va)) is not None and \
            _section_at(pe_sections(exe_path), int(target_va))['exec']:
        verdict = 'virtual-only'
    else:
        verdict = 'none'

    result = {'callsites': callsites, 'verdict': verdict,
              'target_va': int(target_va), 'window': int(window),
              'max_instrs': MAX_LOOKBACK_INSTRS,
              'objdump_cmd': OBJDUMP_CMD, 'exe': exe_path, 'cache': cache_path}
    _MEMO[key] = result
    return result


def _fmt_width(w):
    if w is None:
        return '-'
    if w == 'addr':
        return 'addr'
    return '%dB' % w


def format_report(result, show_width=False):
    """人读报告：objdump 命令 + VA + 逐条原始证据。"""
    lines = []
    t = result['target_va']
    lines.append('# audit_callsite(%#x) verdict=%s' % (t, result['verdict']))
    lines.append('# objdump 取证命令: %s   （全量反汇编后按 VA 定位；禁止手拼 --start-address）'
                 % result['objdump_cmd'])
    lines.append('# cache: %s' % result['cache'])
    if not result['callsites']:
        lines.append('  (无静态 call 命中)')
        return '\n'.join(lines)
    for c in result['callsites']:
        lines.append('callsite %#x' % c['va'])
        for p in c['pushes']:
            extra = ''
            if p['kind'] == 'imm_str':
                extra = " str='%s'" % p['string']
            elif 'value' in p:
                extra = ' value=%#x' % p['value']
            elif 'reg' in p:
                extra = ' reg=%s' % p['reg']
            lines.append('  push   %#x kind=%-7s text=%s%s width=%s'
                         % (p['va'], p['kind'], p['text'], extra, _fmt_width(p['width'])))
        if show_width:
            for r in c['regs']:
                lines.append('  %-6s %#x %-4s %-28s width=%s'
                             % ('regs', r['va'], r['mnemonic'], r['operands'],
                                _fmt_width(r['width'])))
        for raw in c['raw']:
            lines.append('    | %s' % raw)
    return '\n'.join(lines)


def main(argv=None):
    ap = argparse.ArgumentParser(description='调用点实参取证（只读）')
    ap.add_argument('vas', nargs='+', help='目标函数 VA（十六进制，如 0x440960）')
    ap.add_argument('--width', action='store_true',
                    help='逐条报告窗口内 mov/movzx/lea 的宽度（mov 4B / movzx 1B / lea addr）')
    ap.add_argument('--json', action='store_true', help='输出 JSON（width 字段始终包含）')
    ap.add_argument('--window', type=lambda s: int(s, 0), default=DEFAULT_WINDOW_BYTES,
                    help='向前回溯的最大字节数（默认 %#x）' % DEFAULT_WINDOW_BYTES)
    ap.add_argument('--exe', default=DEFAULT_EXE, help='目标二进制（默认 original/PAL3.exe）')
    ap.add_argument('--cache', default=DEFAULT_CACHE,
                    help='反汇编缓存路径（默认 data/status/_disasm_cache.txt）')
    ap.add_argument('--no-cache', action='store_true', help='强制重新全量反汇编')
    args = ap.parse_args(argv)

    results = []
    for va_s in args.vas:
        va = int(va_s, 0)
        results.append(audit_callsite(va, window=args.window, exe_path=args.exe,
                                      cache_path=args.cache, use_cache=not args.no_cache))
    if args.json:
        print(json.dumps(results if len(results) > 1 else results[0],
                         ensure_ascii=False, indent=2))
    else:
        for res in results:
            print(format_report(res, show_width=args.width))
            print()
    return 0


if __name__ == '__main__':
    sys.exit(main())
