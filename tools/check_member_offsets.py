#!/usr/bin/env python3
"""tools/check_member_offsets.py — 逐类核对"编译期成员偏移 vs 注解偏移"。

背景（第 108–112 轮的长线计划）：
  * 有虚函数的类，MSVC 会在 +0 隐式插入 vfptr ⇒ **所有成员整体 +4** 是"正常"的（
    除非该类的 +0 成员已被 F59 的 `static` 别名处理）；
  * 但若出现**非均匀**漂移（某些成员 +4、之后的成员 −20 之类），就说明发射出的结构布局
    与注解不一致（gap/union/_variants 的记账 bug）——这类 bug 会直接毁掉整类的字节匹配，
    而 `s4_diff_explain` 只会报"某一处 disp 不同"，看不出全貌。
  实测（第 111/112 轮，SceneMgr）：`m_pGfxMgr`…`m_nTodo_C660` 全部 +4（正常 vfptr 位移），
  但 `m_nRoleCount`(注解 0xE0E0) 编成 0xE0CC、`sizeof` 0xE530（注解 0xE544）= **−20**，
  漂移发生在那段只存在于 IDA `_variants` 的联合（+0xC67E）附近。

用法：
    python tools/check_member_offsets.py SceneMgr TextureLib [--limit 40]
输出：每个类一行汇总 + 首个非均匀漂移的成员；有非均匀漂移时退出码 1。

只读：写出的探针 .cpp/.obj 都在 %TEMP%\\pal3_offset_probe 下，不碰仓库源码。
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / 'tools'))
import capstone                      # noqa: E402
import gbengine_compare as gc        # noqa: E402

CL = REPO / 'tools' / 'compilers' / 'msvc6.0' / 'Bin' / 'CL.EXE'
INCS = [REPO / 'include', REPO / 'pal3' / 'src',
        REPO / 'tools' / 'compilers' / 'msvc6.0' / 'Include', REPO / 'tools' / 'vc6' / 'Include']
WORK = Path(tempfile.gettempdir()) / 'pal3_offset_probe'

MEMBER_RE = re.compile(r'^\s+(?!virtual|static|//)([A-Za-z_][\w:<>,\* ]*?)\s+([A-Za-z_]\w*)\s*(\[[^\]]*\])?;\s*//\s*\+0x([0-9A-Fa-f]+)')


def find_header(cls):
    for p in (REPO / 'pal3' / 'src').rglob('%s.h' % cls):
        return p
    return None


def annotated_members(cls, limit):
    hdr = find_header(cls)
    if hdr is None:
        return None, []
    out = []
    for line in hdr.read_text(encoding='utf-8', errors='replace').split('\n'):
        m = MEMBER_RE.match(line)
        if not m:
            continue
        if m.group(3):                       # arrays: skip (naming/size differences)
            continue
        out.append((m.group(2), int(m.group(4), 16)))
        if len(out) >= limit:
            break
    return hdr, out


def probe(cls, members):
    WORK.mkdir(parents=True, exist_ok=True)
    src = WORK / ('probe_%s.cpp' % cls)
    body = ['#include "pal3/ida_defs.h"', '#include "globals.h"',
            '#include "%s"' % _include_path(cls), '']
    for name, _off in members:
        body.append('int off_%s() { return (int)(unsigned long)&((( %s *)(unsigned long)16)->%s) - 16; }'
                    % (name, cls, name))
    body.append('int off_sizeof() { return (int)sizeof(%s); }' % cls)
    src.write_text('\n'.join(body) + '\n', encoding='utf-8')
    obj = WORK / ('probe_%s.obj' % cls)
    cmd = [str(CL), '/nologo', '/TP', '/c', '/W3'] + ['/I' + str(p) for p in INCS] + \
          ['/Fo%s' % obj, str(src)]
    r = subprocess.run(cmd, capture_output=True, text=True, errors='replace', cwd=str(REPO))
    errs = [l for l in (r.stdout + r.stderr).split('\n') if ' error ' in l]
    if errs or not obj.exists():
        return None, errs[:3]
    syms = gc.parse_coff_obj(str(obj))
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    got = {}
    for name, info in syms.items():
        short = name.split('@@')[0].replace('?off_', '')
        for ins in md.disasm(info['bytes'], 0):
            if ins.mnemonic == 'mov' and 'eax' in ins.op_str:
                try:
                    got[short] = int(ins.op_str.split(', ')[-1], 16)
                except ValueError:
                    pass
                break
    return got, []


def _include_path(cls):
    hdr = find_header(cls)
    if hdr is None:
        return '%s.h' % cls
    rel = hdr.relative_to(REPO / 'pal3' / 'src')
    return str(rel).replace('\\', '/')


def scan_all(limit):
    """Inventory: for every generated header that declares `virtual`, probe a member sample
    and classify the layout as {uniform} or {drifting}.

    Motivation (long-term plan §19): a class is byte-matchable only if its member offsets are
    right; a *non-uniform* drift means the emitted struct disagrees with the annotation
    (gap/inline-UDT accounting). This inventory sizes that structural bucket.
    """
    classes = []
    for hdr in (REPO / 'pal3' / 'src').rglob('*.h'):
        txt = hdr.read_text(encoding='utf-8', errors='replace')
        if not re.search(r'^\s+virtual\s', txt, re.M):
            continue
        m = re.search(r'^(?:class|struct)\s+(?:GBAPI\s+)?([A-Za-z_]\w*)\s*(?::|\{|$)', txt, re.M)
        if m and m.group(1) not in classes:
            classes.append(m.group(1))
    print('polymorphic headers: %d classes' % len(classes))
    uniform, drifting, failed = [], [], []
    for cls in classes:
        _hdr, members = annotated_members(cls, limit)
        if not members:
            continue
        got, errs = probe(cls, members)
        if got is None:
            failed.append(cls)
            continue
        deltas = sorted({got[n] - a for n, a in members if n in got})
        (uniform if len(deltas) == 1 else drifting).append((cls, deltas, len(members)))
    print('\nUNIFORM drift (layout consistent; +4 = the implicit vfptr): %d' % len(uniform))
    for cls, d, n in uniform:
        if d != [4]:
            print('   %-28s deltas=%-10s members=%d' % (cls, d, n))
    print('\nNON-UNIFORM drift (annotation/emitter disagree): %d' % len(drifting))
    for cls, d, n in drifting:
        print('   %-28s deltas=%-16s members=%d' % (cls, d, n))

    # R117/R118: a drifted member is almost always a *cascade* from an embedded class whose
    # reconstructed sizeof exceeds its annotated binary_size (e.g. UIListBox's +96 ==
    # UIScrollBar being 0x1C0 instead of 0x160).  Report those root classes here.
    print('\nSIZE-WRONG classes (compiled sizeof > annotated binary_size) — cascade roots:')
    roots = []
    for cls in classes:
        ann = REPO / 'data' / 'annotations' / 'structs' / ('%s.json' % cls)
        if not ann.exists():
            continue
        try:
            want = json.loads(ann.read_text(encoding='utf-8')).get('binary_size')
        except Exception:
            continue
        if not isinstance(want, int) or want <= 0:
            continue
        _hdr, members = annotated_members(cls, limit)
        if not members:
            continue
        got, errs = probe(cls, members)
        if got is None or 'sizeof' not in got:
            continue
        if got['sizeof'] != want:
            roots.append((got['sizeof'] - want, cls, got['sizeof'], want))
    for d, cls, got_s, want in sorted(roots, reverse=True):
        print('   %-28s compiled=0x%-6X annotated=0x%-6X %+d' % (cls, got_s, want, d))
    if not roots:
        print('   (none)')
    if failed:
        print('\nprobe compile failed: %d (%s)' % (len(failed), ', '.join(failed[:6])))
    return 1 if drifting else 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('classes', nargs='*')
    ap.add_argument('--limit', type=int, default=40, help='max members probed per class')
    ap.add_argument('--verbose', action='store_true',
                    help='print the full member table (name, annotated, compiled, delta)')
    ap.add_argument('--all', action='store_true',
                    help='scan every generated class header that declares virtual methods '
                         '(the "polymorphic" set) and report the drift inventory')
    args = ap.parse_args()
    if args.all:
        return scan_all(args.limit)
    bad = 0
    for cls in args.classes:
        hdr, members = annotated_members(cls, args.limit)
        if not members:
            print('%-24s (no annotated members found / header missing)' % cls)
            continue
        got, errs = probe(cls, members)
        if got is None:
            print('%-24s COMPILE FAILED: %s' % (cls, errs[:1]))
            continue
        deltas = []
        for name, ann in members:
            if name in got:
                deltas.append((name, ann, got[name], got[name] - ann))
        uniq = sorted({d for _n, _a, _g, d in deltas})
        first_bad = next(((n, a, g, d) for n, a, g, d in deltas
                          if d != deltas[0][3]), None)
        size_got = got.get('sizeof')
        print('%-24s members=%-3d deltas=%s sizeof=0x%X' % (
            cls, len(deltas), uniq, size_got if size_got is not None else 0))
        if first_bad:
            print('      first non-uniform drift: %s ann=0x%X compiled=0x%X (%+d)' % first_bad)
            bad += 1
        if args.verbose:
            prev = None
            for name, ann, got_, delta in deltas:
                flag = '' if prev is None or delta == prev else '   <-- drift changes here'
                print('        %-30s ann=0x%-6X compiled=0x%-6X %+d%s' % (name, ann, got_, delta, flag))
                prev = delta
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
