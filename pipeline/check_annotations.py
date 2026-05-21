#!/usr/bin/env python3
"""
校验 annotations.json 数据合法性。
用法: python tools/check_annotations.py
      或作为 git pre-commit hook 调用

检查项:
  1. JSON 格式合法
  2. functions: 每个必须有 name + signature
  3. globals: 每个必须有 name（type 可选但缺失会警告）
  4. structs: 无重复成员名，offset 递增，base_class 如有则必须存在
  5. 地址格式: 0x00XXXXXX
"""

import json
import sys
import os
import re

ANN_DIR = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'data', 'annotations')

def load_annotations():
    """从拆分目录加载标注数据。"""
    funcs = json.load(open(os.path.join(ANN_DIR, 'functions.json'), encoding='utf-8'))
    globs = json.load(open(os.path.join(ANN_DIR, 'globals.json'), encoding='utf-8'))
    structs = {}
    structs_dir = os.path.join(ANN_DIR, 'structs')
    for fname in os.listdir(structs_dir):
        if fname.endswith('.json'):
            sdata = json.load(open(os.path.join(structs_dir, fname), encoding='utf-8'))
            sname = sdata.pop('name', fname.replace('.json', ''))
            structs[sname] = sdata
    vtables = json.load(open(os.path.join(ANN_DIR, 'vtables.json'), encoding='utf-8'))
    enums = {}
    enums_path = os.path.join(ANN_DIR, 'enums.json')
    if os.path.exists(enums_path):
        enums = json.load(open(enums_path, encoding='utf-8'))
    return {'functions': funcs, 'globals': globs, 'structs': structs, 'vtables': vtables, 'enums': enums}

def _estimate_member_size(mtype, structs):
    """Estimate member size for overlap detection."""
    if '*' in mtype:
        return 4
    arr = re.search(r'\[(\d+)\]', mtype)
    if arr:
        base = re.sub(r'\[\d+\].*', '', mtype).strip()
        elem = _estimate_member_size(base, structs)
        total = elem
        for m in re.finditer(r'\[(\d+)\]', mtype):
            total = int(m.group(1)) * elem
        return total
    t = mtype.strip().replace('struct ', '').replace('class ', '')
    if t in ('char', 'unsigned char', 'BYTE', '_BYTE', 'bool'):
        return 1
    if t in ('short', 'unsigned short', 'WORD', '_WORD'):
        return 2
    if t in ('int', 'unsigned int', 'long', 'unsigned long', 'DWORD', '_DWORD',
             'float', 'BOOL', 'HRESULT', 'HWND', 'HANDLE', 'UINT', 'LONG'):
        return 4
    if t in ('double', '__int64', 'LONGLONG'):
        return 8
    if 'RECT' in t or 'tagRECT' in t:
        return 16
    if t in ('gbVec3D',):
        return 12
    if t in ('gbMatrix',):
        return 64
    if t in structs:
        sz = structs[t].get('binary_size', 0)
        if sz:
            return int(sz)
    return 4


def check():
    errors = []
    warnings = []

    # 1. Load JSON
    try:
        ann = load_annotations()
    except Exception as e:
        errors.append(f"JSON parse error: {e}")
        return errors, warnings

    # 2. Functions
    funcs = ann.get('functions', {})
    for addr, info in funcs.items():
        if not re.match(r'^0x[0-9A-F]{8}$', addr):
            errors.append(f"functions[{addr}]: invalid address format")
        if not info.get('name'):
            errors.append(f"functions[{addr}]: missing name")
        if not info.get('signature'):
            errors.append(f"functions[{addr}]: missing signature (name={info.get('name')})")

    # 3. Globals
    globs = ann.get('globals', {})
    no_type = 0
    for addr, info in globs.items():
        if not info.get('name'):
            errors.append(f"globals[{addr}]: missing name")
        if not info.get('type'):
            no_type += 1
    if no_type > 0:
        warnings.append(f"globals: {no_type}/{len(globs)} missing type")

    # 4. Structs
    structs = ann.get('structs', {})
    all_struct_names = set(structs.keys())
    for sname, sinfo in structs.items():
        members = sinfo.get('known_members', {})

        # Check duplicate member names
        names_seen = {}
        for off, m in members.items():
            mname = m.get('name', '')
            if mname in names_seen:
                errors.append(f"structs[{sname}]: duplicate member '{mname}' at offsets {names_seen[mname]} and {off}")
            names_seen[mname] = off

        # Check member overlap (using known struct sizes)
        sorted_m = sorted(members.items(), key=lambda x: int(x[0]))
        for i in range(len(sorted_m) - 1):
            off1 = int(sorted_m[i][0])
            m1 = sorted_m[i][1]
            off2 = int(sorted_m[i + 1][0])
            size1 = _estimate_member_size(m1.get('type', 'int'), structs)
            if off1 + size1 > off2:
                msg = (f"structs[{sname}]: member overlap: "
                       f"{m1.get('name')}({m1.get('type')}, size={size1})@{off1} "
                       f"ends@{off1+size1} > next {sorted_m[i+1][1].get('name')}@{off2}")
                # Type size not in annotations = estimate unreliable, warn only
                # Exception: types with known fixed sizes (gbengine source)
                KNOWN_FIXED_SIZES = {'gbVec3D', 'gbMatrix', 'tagRECT', 'RECT'}
                mtype_clean = m1.get('type', '').replace('struct ', '').replace('class ', '').strip()
                if mtype_clean in structs or mtype_clean in KNOWN_FIXED_SIZES:
                    errors.append(msg)
                else:
                    warnings.append(msg + " (type size estimated)")

        # Check base_class exists
        base = sinfo.get('base_class')
        if base:
            # Handle both single base (string) and multiple bases (list)
            bases = [base] if isinstance(base, str) else base
            for b in bases:
                if b not in all_struct_names:
                    warnings.append(f"structs[{sname}]: base_class '{b}' not in structs (may be in PDB)")

        # Check struct has size
        size = max(sinfo.get('binary_size', 0), sinfo.get('pdb_size', 0), sinfo.get('gen_size', 0))
        if size == 0 and members:
            warnings.append(f"structs[{sname}]: no size (has {len(members)} members but size=0)")

    return errors, warnings


if __name__ == '__main__':
    errors, warnings = check()

    for w in warnings:
        print(f"WARN: {w}")
    for e in errors:
        print(f"ERROR: {e}")

    if errors:
        print(f"\n{len(errors)} errors, {len(warnings)} warnings — FAIL")
        sys.exit(1)
    else:
        print(f"\n0 errors, {len(warnings)} warnings — PASS")
        sys.exit(0)
