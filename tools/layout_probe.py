#!/usr/bin/env python3
"""MSVC 真实布局读取器：对指定类生成探针 TU（每成员一函数返回真实偏移），
用管线同款 CL 编译，dumpbin 解析，与注解偏移对表，报告漂移折点。

用法:
  python tools/layout_probe.py <ClassName> [ClassName2 ...]

原理（2026-09-25 Role +4 链验证）:
  `int __stdcall off_<member>() { return &((C*)0)-><member>; }` 被 MSVC6 折叠为
  `mov eax, IMM` 常量 ⇒ dumpbin 直读真实偏移。与 known_members 注解偏移对表：
  一致 ⇒ 布局正确；首个分歧点 = 注解/发射的折点成员。
管线工具（tools/，复用）。
"""
import json, os, re, struct, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'pipeline'))
import probe_compile as pc                                    # noqa: E402

STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')
LOG = os.path.join(ROOT, 'pipeline', '_logs')


def find_header(cls):
    for dirpath, _dirs, files in os.walk(os.path.join(ROOT, 'pal3', 'src')):
        if cls + '.h' in files:
            rel = os.path.relpath(os.path.join(dirpath, cls + '.h'), ROOT)
            return rel.replace('\\', '/')
    return None


def parse_members(hdr_path, cls):
    """从头文件提取 (member_name, annotated_offset, decl)。"""
    h = open(os.path.join(ROOT, hdr_path), encoding='utf-8').read()
    out = []
    for line in h.split('\n'):
        m = re.search(r'//\s*\+(0x[0-9A-Fa-f]+|\d+)\s*$', line)
        if not m:
            continue
        decl = line[:m.start()].strip().rstrip(';').strip()
        nm = re.findall(r'(\w+)\s*(?:\[[^\]]*\])?\s*$', decl)
        if nm:
            off = m.group(1)
            a = int(off, 16) if off.startswith('0x') else int(off)
            out.append((nm[-1], a, decl))
    return out


def gen_probe_tu(cls, hdr_path, members):
    cpp = os.path.join(LOG, '%s_layout_probe.cpp' % cls)
    lines = ['#include "%s"' % os.path.relpath(
        os.path.join(ROOT, hdr_path), os.path.dirname(cpp)).replace(os.sep, '/'),
        '', 'extern "C" {']
    for name, _off, _decl in members:
        lines.append('int __stdcall off_%s() { return (int)((size_t)&((%s*)0)->%s); }'
                     % (name, cls, name))
    lines.append('int __stdcall sizeof_%s() { return (int)sizeof(%s); }' % (cls, cls))
    lines.append('}')
    p = os.path.join(LOG, '%s_layout_probe.cpp' % cls)
    open(p, 'w', encoding='utf-8').write('\n'.join(lines))
    return p


def compile_tu(cpp, obj):
    out, err = pc.run_cl([os.path.abspath(cpp), '/Iinclude', '/Ipal3/src',
                          '/Itools/compilers/msvc6.0/Include', '/Itools/vc6/Include',
                          '/Fopipeline/_logs/%s' % os.path.basename(obj)])
    return os.path.exists(obj), (out or '') + (err or '')


def parse_dumpbin(obj):
    r = subprocess.run([os.path.abspath('tools/vc6/Bin/DUMPBIN.EXE'), '/disasm',
                        os.path.abspath(obj)], capture_output=True, text=True,
                       errors='replace', timeout=120)
    cur, real, sizes = None, {}, {}
    for line in r.stdout.split('\n'):
        m = re.match(r'^_?off_(\w+)@\d+:\s*$', line.strip())
        if m:
            cur = m.group(1); real.setdefault(cur, None); continue
        m2 = re.match(r'^_?sizeof_(\w+)@\d+:\s*$', line.strip())
        if m2:
            cur = 'sizeof:' + m2.group(1); continue
        mv = re.search(r'mov\s+eax,([0-9A-Fa-f]+)h?\s*$', line.strip())
        if mv and cur and real.get(cur if not cur.startswith('sizeof:') else cur) is None \
                and (cur not in real or real[cur] is None):
            real[cur] = int(mv.group(1).rstrip('h'), 16)
        elif mv and cur and cur.startswith('sizeof:'):
            sizes[cur.split(':')[1]] = int(mv.group(1).rstrip('h'), 16)
    return real, sizes


def main():
    classes = sys.argv[1:]
    if not classes:
        print(__doc__)
        return
    os.makedirs(LOG, exist_ok=True)
    for cls in classes:
        hdr = find_header(cls)
        if not hdr:
            print(cls, ': header not found'); continue
        ann_path = os.path.join(STRUCTS, cls + '.json')
        d = json.load(open(ann_path, encoding='utf-8'))
        members = parse_members(hdr, cls)
        if not members:
            print(cls, ': no annotated-offset members parsed from', hdr); continue
        cpp = gen_probe_tu(cls, hdr, members)
        obj = os.path.join(LOG, '%s_layout_probe.obj' % cls)
        ok, errout = compile_tu(cpp, obj)
        if not ok:
            print(cls, ': COMPILE FAIL'); print('   ', errout[-300:]); continue
        real, sizes = parse_dumpbin(obj)
        msvc_size = sizes.get(cls)
        ann_size = d.get('binary_size')
        crease = None
        ndrift = 0
        for name, a, _decl in members:
            rv = real.get(name)
            if rv is None:
                continue
            if rv != a and crease is None:
                crease = (name, a, rv, rv - a)
            if rv != a:
                ndrift += 1
        status = 'OK' if crease is None and (msvc_size in (None, ann_size)) else 'DRIFT'
        print('%-16s ann_size=%-7s msvc_size=%-7s drift=%d  %s' % (
            cls, ann_size, msvc_size, ndrift, status))
        if crease:
            print('   首个分歧: %s 注解 %s → 实际 %s (Δ%+d)' % crease)
        # 额外：列出与注解 binary_size 的差（若 size 漂移）
        if msvc_size is not None and ann_size and msvc_size != ann_size:
            print('   尺寸差: MSVC %d vs 注解 %d (Δ%+d)' % (msvc_size, ann_size, msvc_size - ann_size))


if __name__ == '__main__':
    main()
