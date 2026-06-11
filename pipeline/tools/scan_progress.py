#!/usr/bin/env python3
"""
Scan all generated .cpp files for true hardcoded offsets (vN + literal),
aggregate by class, and report the baseline for tracking annotation progress.

Usage:
    python pipeline/tools/scan_progress.py                 # JSON output
    python pipeline/tools/scan_progress.py --brief          # One-line summary
    python pipeline/tools/scan_progress.py --top 10        # Top 10 classes
    python pipeline/tools/scan_progress.py --class RoleSystem  # Single class detail
"""

import re, os, json, sys
from collections import defaultdict

SRC_DIR = os.path.join(os.path.dirname(__file__), '..', '..', 'src', 'pal3', 'gen')
OUT_DIR = os.path.join(os.path.dirname(__file__), '..', 'progress')
os.makedirs(OUT_DIR, exist_ok=True)


def scan_one(path):
    """Scan a single .cpp file for true hardcoded offsets."""
    with open(path) as f:
        content = f.read()

    # Patterns: *(type *)(vN + literal) — untyped register arithmetic
    dw = re.findall(r'\*\(_DWORD \*\)\(v(\d+)\s*\+\s*(0x[0-9a-fA-F]+|\d+)\)', content)
    by = re.findall(r'\*\((?:unsigned )?_BYTE \*\)\(v(\d+)\s*\+\s*(0x[0-9a-fA-F]+|\d+)\)', content)
    wo = re.findall(r'\*\(_WORD \*\)\(v(\d+)\s*\+\s*(0x[0-9a-fA-F]+|\d+)\)', content)
    fl = re.findall(r'\*\(float \*\)\(v(\d+)\s*\+\s*(0x[0-9a-fA-F]+|\d+)\)', content)
    do = re.findall(r'\*\(double \*\)\(v(\d+)\s*\+\s*(0x[0-9a-fA-F]+|\d+)\)', content)
    lod = re.findall(r'LODWORD\(v(\d+)\)', content)
    hid = re.findall(r'HIDWORD\(v(\d+)\)', content)

    hc = len(dw) + len(by) + len(wo) + len(fl) + len(do) + len(lod) + len(hid)
    return hc, {
        'DWORD': len(dw), 'BYTE': len(by), 'WORD': len(wo),
        'float': len(fl), 'double': len(do),
        'LODWORD': len(lod), 'HIDWORD': len(hid),
    }


def scan_all():
    """Scan all .cpp files and aggregate by class name."""
    results = []
    total_hc = 0

    for root, dirs, files in os.walk(SRC_DIR):
        for fn in sorted(files):
            if not fn.endswith('.cpp'):
                continue
            path = os.path.join(root, fn)
            hc, details = scan_one(path)
            class_name = fn.replace('.cpp', '')
            if hc > 0:
                total_hc += hc
                results.append({
                    'class': class_name,
                    'file': os.path.relpath(path, SRC_DIR),
                    'hc': hc,
                    'details': details,
                })

    results.sort(key=lambda x: -x['hc'])
    return {'total_hc': total_hc, 'files_scanned': len(results), 'classes': results}


def format_brief(data):
    """One-line summary."""
    top3 = ', '.join(c['class'] for c in data['classes'][:3])
    return (f"HC={data['total_hc']}  files={data['files_scanned']}  "
            f"top={top3}")


def format_top(data, n):
    """Top N classes."""
    lines = [f"{'Class':35s} {'HC':>5s}  DWORD BYTE WORD float LODWORD", '-' * 75]
    for c in data['classes'][:n]:
        d = c['details']
        lines.append(f"{c['class']:35s} {c['hc']:5d}  {d['DWORD']:4d} {d['BYTE']:3d} "
                     f"{d['WORD']:3d} {d['float']:4d} {d['LODWORD']:3d}")
    return '\n'.join(lines)


def format_class(data, cls_name):
    """Detail for a single class."""
    for c in data['classes']:
        if c['class'] == cls_name:
            d = c['details']
            return (f"{c['class']} ({c['file']}): HC={c['hc']}\n"
                    f"  DWORD={d['DWORD']} BYTE={d['BYTE']} WORD={d['WORD']} "
                    f"float={d['float']} LODWORD={d['LODWORD']}")
    return f"Class '{cls_name}' not found in scan."


if __name__ == '__main__':
    data = scan_all()
    out_path = os.path.join(OUT_DIR, 'current.json')
    with open(out_path, 'w') as f:
        json.dump(data, f, indent=2)
    print(f"Wrote {out_path}")

    if '--brief' in sys.argv:
        print(format_brief(data))
    elif '--top' in sys.argv:
        idx = sys.argv.index('--top')
        n = int(sys.argv[idx + 1]) if idx + 1 < len(sys.argv) else 10
        print(format_top(data, n))
    elif '--class' in sys.argv:
        idx = sys.argv.index('--class')
        cls = sys.argv[idx + 1] if idx + 1 < len(sys.argv) else ''
        print(format_class(data, cls))
    else:
        print(format_brief(data))
        print()
        print(format_top(data, 20))
