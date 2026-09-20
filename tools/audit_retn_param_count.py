#!/usr/bin/env python3
"""Audit: annotation-declared stack-argument count vs the binary's callee cleanup.

Runs **inside IDA** (idat -A -S).  Evidence class: A (the callee's own epilogue).

For a callee-cleaned convention the epilogue's `retn N` is exactly N bytes of
stack arguments:
  * `__thiscall`  -> stack args = N/4   (the hidden `this` travels in ECX)
  * `__stdcall`   -> stack args = N/4
  * `__cdecl` / `__fastcall` -> the CALLER cleans the stack, so `retn` carries no
    arity information and those functions are skipped (no evidence, no claim).

The tool only compares COUNTS; it never touches the IDB.  A mismatch means the
annotation signature and the binary disagree about how many stack arguments the
function takes -> call sites lose arguments (Hex-Rays renders only the declared
ones) and/or fail to compile (C2660/C2661/C2664).

Usage:
  idat -A -S"tools/audit_retn_param_count.py" original/PAL3.exe.i64
Output:
  %TEMP%/retn_param_audit.txt   (table)
  %TEMP%/retn_param_audit.json  (machine-readable)
"""
import io
import json
import os
import re
import traceback

import idc
import ida_funcs
import ida_bytes

REPO = os.environ.get('PAL3_REPO') or os.path.dirname(os.path.dirname(
    os.path.abspath(__file__)))  # 2026-09-20 修复：原为硬编码 Windows 路径 D:\\workspace\\PAL3Decomp，
# 在非作者机器上必然 FileNotFoundError ⇒ 改为从脚本位置推导（可用 PAL3_REPO 覆盖）
OUT_TXT = os.path.join(os.environ.get('TEMP', '.'), 'retn_param_audit.txt')
OUT_JSON = os.path.join(os.environ.get('TEMP', '.'), 'retn_param_audit.json')
RX_RETN = re.compile(r'\bretn\s+([0-9A-Fa-f]+h?|\d+)\b')


def split_params(text):
    """Split a parameter list on top-level commas."""
    out, depth, cur = [], 0, ''
    for ch in text:
        if ch in '(<[':
            depth += 1
        elif ch in ')>]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return [p.strip() for p in out if p.strip()]


def declared_stack_args(sig):
    """(convention, declared stack args) or (None, None) when not applicable."""
    if '(' not in sig:
        return (None, None)
    inner = sig[sig.index('(') + 1:sig.rindex(')')].strip()
    params = [] if inner in ('', 'void') else split_params(inner)
    n = len(params)
    has_this = bool(re.search(r'\bthis\b', inner))
    if '__thiscall' in sig:
        # An explicit `Class *this` in the signature IS the hidden this (the
        # applier skips auto-insertion when it sees it); otherwise the project
        # convention omits it and every listed parameter is a stack argument.
        return ('__thiscall', n - 1 if has_this else n)
    if '__stdcall' in sig:
        return ('__stdcall', n)
    return (None, None)


def binary_stack_args(ea):
    """(retn_bytes or None, listing of the last few instructions)."""
    fn = ida_funcs.get_func(ea)
    if fn is None:
        return (None, [])
    tail = []
    cur, guard = fn.end_ea, 0
    while cur > fn.start_ea and guard < 12:
        guard += 1
        prev = ida_bytes.prev_head(cur, fn.start_ea)
        if prev == idc.BADADDR or prev >= cur:
            break
        txt = idc.generate_disasm_line(prev, 0) or ''
        tail.append(txt.strip())
        m = RX_RETN.search(txt)
        if m:
            raw = m.group(1)
            if raw.endswith('h'):
                try:
                    return (int(raw[:-1], 16), tail)
                except ValueError:
                    return (None, tail)
            try:
                return (int(raw, 10), tail)
            except ValueError:
                return (None, tail)
        cur = prev
    return (None, tail)


def load_annotations():
    """{ea: (name, signature, source)} from functions.json + struct methods."""
    out = {}
    fpath = os.path.join(REPO, 'data', 'annotations', 'functions.json')
    if os.path.exists(fpath):
        with io.open(fpath, encoding='utf-8') as fh:
            for addr, info in json.load(fh).items():
                if not isinstance(info, dict):
                    continue
                sig = info.get('signature', '')
                nm = info.get('name', '')
                if info.get('class'):
                    nm = '%s::%s' % (info['class'], nm)
                out[int(addr, 16)] = (nm, sig, 'functions.json')
    for p in os.listdir(os.path.join(REPO, 'data', 'annotations', 'structs')):
        if not p.endswith('.json'):
            continue
        try:
            with io.open(os.path.join(REPO, 'data', 'annotations', 'structs', p),
                         encoding='utf-8') as fh:
                data = json.load(fh)
        except Exception:
            continue
        cls = data.get('name', p[:-5])
        for addr, mi in (data.get('methods') or {}).items():
            try:
                ea = int(addr, 16)
            except ValueError:
                continue
            out.setdefault(ea, ('%s::%s' % (cls, mi.get('name', '?')),
                                mi.get('signature', ''), 'structs/%s' % p))
    return out


def main():
    ann = load_annotations()
    rows, mism = [], []
    for ea, (name, sig, src) in sorted(ann.items()):
        cc, decl = declared_stack_args(sig)
        if cc is None or decl is None:
            continue
        nbytes, tail = binary_stack_args(ea)
        if nbytes is None:
            continue
        if nbytes % 4:
            continue
        binargs = nbytes // 4
        row = {'ea': '0x%08X' % ea, 'name': name, 'src': src, 'cc': cc,
               'sig': sig, 'declared': decl, 'retn': nbytes, 'binary': binargs}
        rows.append(row)
        if decl != binargs:
            mism.append(row)
    with io.open(OUT_TXT, 'w', encoding='utf-8') as fh:
        fh.write('annotated callee-cleaned functions checked: %d\n' % len(rows))
        fh.write('COUNT MISMATCHES: %d\n' % len(mism))
        fh.write('%-14s %-38s %-11s %4s %4s  %s\n'
                 % ('addr', 'name', 'cc', 'dec', 'bin', 'signature'))
        for r in mism:
            fh.write('%-14s %-38s %-11s %4d %4d  %s\n'
                     % (r['ea'], r['name'][:38], r['cc'], r['declared'],
                        r['binary'], r['sig'][:90]))
    with io.open(OUT_JSON, 'w', encoding='utf-8') as fh:
        json.dump({'checked': len(rows), 'mismatches': mism}, fh, indent=1,
                  ensure_ascii=False)
    print('[retn-audit] checked=%d mismatches=%d -> %s'
          % (len(rows), len(mism), OUT_TXT))


try:
    main()
except Exception:
    with io.open(OUT_TXT, 'a', encoding='utf-8') as fh:
        fh.write('EXCEPTION ' + traceback.format_exc())
idc.qexit(0)
