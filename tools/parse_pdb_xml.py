"""
Parse Ghidra pdb.exe XML output into structured JSON for stub generation.

Usage: python tools/parse_pdb_xml.py
Input:  asm/pal3a/pdb_raw.xml
Output: asm/pal3a/pdb_export.json
"""
import xml.etree.ElementTree as ET
import json
import os
import re
import subprocess
from collections import defaultdict

INPUT = "asm/pal3a/pdb_raw.xml"
OUTPUT = "asm/pal3a/pdb_export.json"


def demangle_msvc(mangled_names):
    """Batch demangle MSVC decorated names using undname or regex fallback."""
    result = {}
    # Try using undname.exe from VS
    undname = r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\bin\Hostx64\x64\undname.exe"
    if os.path.exists(undname):
        # Process in batches
        for i in range(0, len(mangled_names), 500):
            batch = mangled_names[i:i+500]
            input_text = '\n'.join(batch)
            try:
                proc = subprocess.run([undname, "0x0"], input=input_text,
                                     capture_output=True, text=True, timeout=30)
                lines = proc.stdout.strip().split('\n')
                for line in lines:
                    if ' is :- "' in line:
                        mangled = line.split(' is :- "')[0].strip()
                        demangled = line.split(' is :- "')[1].rstrip('"').strip()
                        result[mangled] = demangled
            except:
                pass

    # Fallback: simple regex-based demangling for common patterns
    for name in mangled_names:
        if name in result:
            continue
        # ?Method@Class@@... -> Class::Method
        m = re.match(r'\?(\w+)@(\w+)@@', name)
        if m:
            method, cls = m.group(1), m.group(2)
            result[name] = f"{cls}::{method}"
            continue
        # ??0Class@@... -> Class::Class (constructor)
        m = re.match(r'\?\?0(\w+)@@', name)
        if m:
            cls = m.group(1)
            result[name] = f"{cls}::{cls}"
            continue
        # ??1Class@@... -> Class::~Class (destructor)
        m = re.match(r'\?\?1(\w+)@@', name)
        if m:
            cls = m.group(1)
            result[name] = f"{cls}::~{cls}"
            continue
        # _Function@N -> Function (stdcall)
        m = re.match(r'_(\w+)@\d+', name)
        if m:
            result[name] = m.group(1)
            continue
        # ?Function@@... -> Function (global)
        m = re.match(r'\?(\w+)@@', name)
        if m:
            result[name] = m.group(1)
            continue
        result[name] = name

    return result


def parse_xml(input_path):
    """Parse the full PDB XML."""
    print(f"Parsing {input_path}...")
    tree = ET.parse(input_path)
    root = tree.getroot()

    # === Classes ===
    print("Extracting classes...")
    classes = []
    for cls in root.iter("class"):
        entry = {
            "name": cls.get("name", ""),
            "kind": "class",
            "size": int(cls.get("length", "0"), 16),
            "data_members": [],
            "methods": [],
            "static_members": [],
        }
        for mem in cls.findall("member"):
            name = mem.get("name", "")
            dtype = mem.get("datatype", "")
            kind = mem.get("kind", "")
            length = int(mem.get("length", "0"), 16)
            offset = int(mem.get("offset", "0"), 16)

            if kind == "Member":
                entry["data_members"].append({
                    "name": name,
                    "type": dtype,
                    "offset": offset,
                })
            elif kind == "StaticMember":
                entry["static_members"].append({
                    "name": name,
                    "type": dtype,
                })
            elif kind == "Unknown" and "::" in name:
                # Method - name is already demangled (e.g. "ConfigFile::Open")
                entry["methods"].append({
                    "name": name,
                    "size": length,
                })
        classes.append(entry)
    print(f"  Classes: {len(classes)}")

    # === Enums ===
    print("Extracting enums...")
    enums = []
    for en in root.iter("enum"):
        entry = {
            "name": en.get("name", ""),
            "kind": "enum",
            "type": en.get("type", "int"),
            "size": int(en.get("length", "0"), 16),
            "values": {},
        }
        for mem in en.findall("member"):
            entry["values"][mem.get("name", "")] = mem.get("value", "0")
        enums.append(entry)
    print(f"  Enums: {len(enums)}")

    # === Functions ===
    print("Extracting functions...")
    functions = []
    mangled_names = []

    for func in root.iter("function"):
        mangled = func.get("name", "")
        addr = int(func.get("address", "0"), 16)
        length = int(func.get("length", "0"), 16)

        # Extract parameters from stack_variable
        params = []
        this_type = ""
        for sv in func.findall("stack_variable"):
            kind = sv.get("kind", "")
            if kind == "Parameter":
                params.append({
                    "name": sv.get("name", ""),
                    "type": sv.get("datatype", ""),
                })
            elif kind == "ObjectPointer":
                this_type = sv.get("datatype", "")

        # Get source file from line_number
        source_file = ""
        ln = func.find("line_number")
        if ln is not None:
            source_file = ln.get("source_file", "")

        entry = {
            "mangled_name": mangled,
            "name": "",  # filled after demangling
            "address": f"0x{0x00400000 + addr:08X}",
            "rva": f"0x{addr:08X}",
            "size": length,
            "parameters": params,
            "this_type": this_type,
            "source_file": source_file,
            "class": "",
            "return_type": "",
        }
        functions.append(entry)
        mangled_names.append(mangled)

    print(f"  Functions: {len(functions)}")

    # === Demangle ===
    print("Demangling function names...")
    demangled = demangle_msvc(mangled_names)

    for func in functions:
        mangled = func["mangled_name"]
        dname = demangled.get(mangled, mangled)
        func["name"] = dname
        if "::" in dname:
            parts = dname.rsplit("::", 1)
            func["class"] = parts[0]

    named_count = sum(1 for f in functions if f["name"] != f["mangled_name"])
    print(f"  Demangled: {named_count}/{len(functions)}")

    # === Build source file index ===
    by_source = defaultdict(list)
    for func in functions:
        src = func.get("source_file", "")
        if src:
            by_source[src].append(func)

    # === Datatypes (from <datatypes> section) ===
    print("Extracting datatypes...")
    datatypes = []
    for dt in root.iter("datatype"):
        if dt.get("name") and dt.getparent if hasattr(dt, 'getparent') else True:
            pass  # datatypes are inline, skip standalone parsing

    result = {
        "image_base": "0x00400000",
        "functions": functions,
        "classes": classes,
        "enums": enums,
        "source_file_index": dict(by_source),
    }

    return result


def main():
    result = parse_xml(INPUT)

    # Summary
    si = result["source_file_index"]
    pal3_files = {k: v for k, v in si.items() if 'PAL3A' in k and '.cpp' in k.lower()}
    print(f"\n  PAL3A source files: {len(pal3_files)}")
    print(f"  Total source files: {len(si)}")

    os.makedirs(os.path.dirname(OUTPUT), exist_ok=True)
    with open(OUTPUT, "w", encoding="utf-8") as f:
        json.dump(result, f, indent=2, ensure_ascii=False)

    print(f"\nOutput: {OUTPUT} ({os.path.getsize(OUTPUT) / 1024 / 1024:.1f} MB)")


if __name__ == "__main__":
    main()
