"""
Batch demangle all mangled function names from pdb_export.json using undname.exe.
Updates the JSON with proper return types and full signatures.

Usage: python tools/batch_undname.py
"""
import json
import subprocess
import re
import os
import tempfile

INPUT = "asm/pal3a/pdb_export.json"
OUTPUT = "asm/pal3a/pdb_export.json"
UNDNAME = r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\bin\Hostx64\x64\undname.exe"


def batch_undname(mangled_names, batch_size=200):
    """Run undname.exe on batches of names, return dict of mangled->demangled."""
    result = {}

    for i in range(0, len(mangled_names), batch_size):
        batch = mangled_names[i:i+batch_size]

        # Write to temp file
        with tempfile.NamedTemporaryFile(mode='w', suffix='.txt', delete=False, encoding='utf-8') as f:
            for name in batch:
                f.write(name + '\n')
            tmpfile = f.name

        try:
            proc = subprocess.run([UNDNAME, tmpfile],
                                capture_output=True, text=True, timeout=60)
            # File mode: outputs one demangled line per input line
            output_lines = proc.stdout.strip().split('\n')
            for j, demangled_line in enumerate(output_lines):
                if j < len(batch):
                    demangled_line = demangled_line.strip()
                    if demangled_line and demangled_line != batch[j]:
                        result[batch[j]] = demangled_line
        except Exception as e:
            print(f"  Error in batch {i}: {e}")
        finally:
            os.unlink(tmpfile)

        if (i + batch_size) % 2000 == 0:
            print(f"  Demangled {min(i+batch_size, len(mangled_names))}/{len(mangled_names)}...")

    return result


def parse_signature(demangled):
    """Parse a demangled signature into return_type, class, method, params.

    Examples:
      'public: bool __thiscall ConfigFile::Write(char *,char *,char *)'
      'void __cdecl SkipTime(void)'
      'public: __thiscall ConfigFile::ConfigFile(void)'
    """
    sig = demangled.strip()

    # Remove access specifier
    for prefix in ['public: ', 'protected: ', 'private: ', 'public: virtual ',
                   'protected: virtual ', 'private: virtual ', 'virtual ']:
        if sig.startswith(prefix):
            sig = sig[len(prefix):]
            break

    # Remove static
    if sig.startswith('static '):
        sig = sig[len('static '):]

    # Extract calling convention
    calling_conv = ""
    for cc in ['__thiscall ', '__cdecl ', '__stdcall ', '__fastcall ']:
        if cc in sig:
            calling_conv = cc.strip()
            sig = sig.replace(cc, '', 1)
            break

    # Now format is: "return_type Class::Method(params)" or "return_type Function(params)"
    # Special case: constructors/destructors have no return type
    # "ConfigFile::ConfigFile(void)" or "ConfigFile::~ConfigFile(void)"

    # Find the opening paren for params
    paren_idx = sig.find('(')
    if paren_idx == -1:
        return {"return_type": "void", "name": sig, "params": ""}

    before_paren = sig[:paren_idx].strip()
    params_raw = sig[paren_idx+1:].rstrip(')')

    # Clean params
    if params_raw == "void":
        params_raw = ""

    # Split before_paren into return_type + name
    # The name is the last token (possibly Class::Method)
    parts = before_paren.rsplit(' ', 1)
    if len(parts) == 2:
        return_type = parts[0].strip()
        name = parts[1].strip()
    else:
        # No space = constructor/destructor (no return type)
        return_type = "void"
        name = parts[0].strip()

    # Handle "const" suffix on return type that got attached wrong
    if return_type.endswith('const'):
        return_type = return_type[:-5].strip()
        if not return_type:
            return_type = "void"

    return {
        "return_type": return_type,
        "name": name,
        "params": params_raw,
        "calling_convention": calling_conv,
    }


def main():
    print(f"Loading {INPUT}...")
    with open(INPUT) as f:
        data = json.load(f)

    # Collect all mangled names
    mangled_names = []
    for func in data["functions"]:
        mn = func.get("mangled_name", "")
        if mn and (mn.startswith('?') or mn.startswith('_')):
            mangled_names.append(mn)

    print(f"Mangled names to process: {len(mangled_names)}")

    # Batch demangle
    print("Running undname.exe...")
    demangled_map = batch_undname(mangled_names)
    print(f"  Successfully demangled: {len(demangled_map)}")

    # Update functions with return types
    updated = 0
    for func in data["functions"]:
        mn = func.get("mangled_name", "")
        if mn in demangled_map:
            sig = parse_signature(demangled_map[mn])
            func["return_type"] = sig["return_type"]
            func["demangled_full"] = demangled_map[mn]
            # Also update name if we got a better one
            if sig["name"] and '::' in sig["name"]:
                func["name"] = sig["name"]
                func["class"] = sig["name"].rsplit('::', 1)[0]
            elif sig["name"] and not func["name"].startswith('?'):
                pass  # keep existing name
            else:
                func["name"] = sig["name"]
            updated += 1

    # Handle constructors/destructors - they return void
    for func in data["functions"]:
        name = func.get("name", "")
        if '::~' in name or (name.count('::') == 1 and name.split('::')[0] == name.split('::')[1]):
            func["return_type"] = "void"

    print(f"  Updated {updated} functions with return types")

    # Save
    with open(OUTPUT, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)

    print(f"Output: {OUTPUT}")

    # Stats
    has_ret = sum(1 for f in data["functions"] if f.get("return_type") and f["return_type"] != "void")
    print(f"  Functions with non-void return: {has_ret}")


if __name__ == "__main__":
    main()
