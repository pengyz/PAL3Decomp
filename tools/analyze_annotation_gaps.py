#!/usr/bin/env python3
"""Analyze which annotation gaps cause the most compile errors.
Focuses on actionable fixes: struct member types, function signatures."""
import json, re, os
from collections import Counter, defaultdict

BUILD_LOG = 'build_log_new.txt'

text = open(BUILD_LOG, encoding='utf-16-le', errors='replace').read()
lines = text.split('\n')

# Parse errors with file:line info
errors = []
for line in lines:
    m = re.match(r'.*\\([^\\]+\.cpp)\((\d+)\)\s*:\s*error (C\d+):\s*(.*)', line)
    if m:
        errors.append({'file': m.group(1), 'line': int(m.group(2)),
                       'code': m.group(3), 'msg': m.group(4)})

print("Total errors: %d" % len(errors))

# Category 1: Struct member access errors → need struct annotation fixes
# C2039 "X is not a member of Y"
c2039 = [e for e in errors if e['code'] == 'C2039']
member_issues = Counter()
for e in c2039:
    m = re.search(r"'(\w+)'\s*:\s*is not a member of\s*'(\w+)'", e['msg'])
    if m:
        member, struct = m.group(1), m.group(2)
        member_issues[(struct, member)] += 1

print("\n=== C2039: Missing struct members (annotation fixes needed) ===")
# Filter out __vftable (codegen issue) and _tail/_gap (gen_headers issue)
actionable = [(k,v) for k,v in member_issues.most_common(30)
              if k[1] not in ('__vftable',) and not k[1].startswith('_tail_') and not k[1].startswith('_gap_')]
for (struct, member), cnt in actionable[:15]:
    print("  %3d  %s.%s" % (cnt, struct, member))

# Category 2: Function signature mismatches → need functions.json fixes
# C2511 "overloaded member function not found in Class"
c2511 = [e for e in errors if e['code'] == 'C2511']
print("\n=== C2511: Method signature mismatch (need functions.json fix) ===")
sig_issues = Counter()
for e in c2511:
    m = re.search(r"'(\w+)'", e['msg'])
    if m:
        sig_issues[m.group(1)] += 1
for name, cnt in sig_issues.most_common(10):
    print("  %3d  %s" % (cnt, name))

# Category 3: C2660 "function does not take N parameters"
c2660 = [e for e in errors if e['code'] == 'C2660']
print("\n=== C2660: Wrong parameter count (need signature fix) ===")
param_issues = Counter()
for e in c2660:
    m = re.search(r"'(\w+)'", e['msg'])
    if m:
        param_issues[m.group(1)] += 1
for name, cnt in param_issues.most_common(10):
    print("  %3d  %s" % (cnt, name))

# Category 4: C2065 undeclared — which are annotation-fixable?
c2065 = [e for e in errors if e['code'] == 'C2065']
print("\n=== C2065: Undeclared identifiers (fixable via annotation) ===")
undecl = Counter()
for e in c2065:
    m = re.search(r"'(\w+)'", e['msg'])
    if m:
        name = m.group(1)
        # Skip IDA internal patterns
        if name.startswith(('_ET', 'asc_', 'loc_')):
            continue
        undecl[name] += 1
for name, cnt in undecl.most_common(15):
    print("  %3d  %s" % (cnt, name))

# Summary: top annotation actions by estimated error reduction
print("\n=== TOP ANNOTATION ACTIONS (estimated error reduction) ===")
print("1. Fix struct member types causing C2227/C2664 cascades")
print("   → RoleSystem.m_pVObj (int→PalScriptMgr*) already done")
print("   → Need to identify more struct members with wrong types")
print("2. Fix function signatures (C2511 + C2660)")
print("3. Add missing struct members (C2039 actionable)")
print("4. Fix undeclared identifiers (C2065)")
