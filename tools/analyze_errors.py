#!/usr/bin/env python3
"""Analyze build errors to find highest-ROI function signature fixes."""
import json, re, os, sys
from collections import Counter, defaultdict

BUILD_LOG = 'build_log_new.txt'
FUNCS_JSON = 'pipeline/data/annotations/functions.json'
SRC_DIR = 'src/pal3'

# Read build log (UTF-16 LE from PowerShell Out-File)
with open(BUILD_LOG, encoding='utf-16-le', errors='replace') as f:
    text = f.read()
lines = text.split('\n')

# Parse all errors
errors_by_file = defaultdict(list)
all_codes = []
for line in lines:
    m = re.match(r'.*\\([^\\]+\.cpp)\((\d+)\)\s*:\s*((?:error|fatal error) (C\d+).*)', line)
    if m:
        fname, lineno, full_err, code = m.group(1), int(m.group(2)), m.group(3), m.group(4)
        errors_by_file[fname].append((lineno, code, full_err))
        all_codes.append(code)

code_counts = Counter(all_codes)
total = sum(code_counts.values())
print("=== Total errors: %d ===" % total)
print()
print("=== Error codes ===")
for code, cnt in code_counts.most_common(12):
    print("  %s: %4d (%.1f%%)" % (code, cnt, cnt*100/total))

# C2664: "cannot convert parameter N from 'X' to 'Y'" — extract function name
print()
print("=== C2664 target functions ===")
c2664_targets = []
for fname, errs in errors_by_file.items():
    for ln, code, full in errs:
        if code == 'C2664':
            m2 = re.search(r"'(\w+)'", full)
            if m2:
                c2664_targets.append(m2.group(1))
for name, cnt in Counter(c2664_targets).most_common(15):
    print("  %3d  %s" % (cnt, name))

# C2065: undeclared identifiers
print()
print("=== C2065 undeclared identifiers ===")
c2065_ids = []
for fname, errs in errors_by_file.items():
    for ln, code, full in errs:
        if code == 'C2065':
            m3 = re.search(r"'(\w+)'", full)
            if m3:
                c2065_ids.append(m3.group(1))
for name, cnt in Counter(c2065_ids).most_common(15):
    print("  %3d  %s" % (cnt, name))

# Which source files have the most type-mismatch errors?
print()
print("=== Files with most C2227+C2664+C2440 (type mismatch) ===")
type_err_files = {}
for fname, errs in errors_by_file.items():
    cnt = sum(1 for _, code, _ in errs if code in ('C2227', 'C2664', 'C2440'))
    if cnt > 0:
        type_err_files[fname] = cnt
for f, cnt in sorted(type_err_files.items(), key=lambda x: -x[1])[:15]:
    print("  %3d  %s" % (cnt, f))

# Cross-reference: which functions from functions.json are called in error lines?
print()
print("=== Analysis: functions called in C2664 error context ===")
funcs = json.load(open(FUNCS_JSON, encoding='utf-8'))
# Build name→addr map
func_by_name = {}
for addr, info in funcs.items():
    name = info.get('name', '')
    if name and '::' in name:
        short = name.split('::')[-1]
        func_by_name[short] = (addr, info)
    elif name:
        func_by_name[name] = (addr, info)

# Check which C2664 targets are in functions.json
matched = 0
for name, cnt in Counter(c2664_targets).most_common(15):
    if name in func_by_name:
        addr, info = func_by_name[name]
        print("  %3d  %s @ %s — sig: %s" % (cnt, name, addr, info.get('signature', '?')[:60]))
        matched += cnt
print("  Matched: %d / %d C2664 errors have function in annotations" % (matched, len(c2664_targets)))
