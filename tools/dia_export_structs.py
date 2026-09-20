"""
Export missing struct definitions from PAL3A.pdb via DIA SDK.

The original pdb_export.json only has 1057 classes (udtKind=1).
This script exports the 698 structs (udtKind=0) + 5 unions (udtKind=2)
and merges them into pdb_export.json.

Usage: python tools/dia_export_structs.py
"""
import sys, os, json, ctypes, subprocess


# ---- 2026-09-20 审计 P2-4：无参数解析工具的统一护栏 ----------------------------
# 本工具**会写盘**且**没有任何 argparse/sys.argv 处理** ⇒ 传任何 `-` 开头的参数
# （最典型的是 `--help`）此前会被当作普通输入，**执行全流程并覆盖产物**。
# 本次审计期间已因此发生 **2 起事故**（`sig_evidence.py` 删掉 6020 行、
# `misattribution_ledger.py` 把 197 cluster 改写成 3）。
# 统一护栏：见到任何以 `-` 开头的参数即打印用法并**退出，不执行任何工作**。
import sys as _sys_guard
if any(_a.startswith('-') for _a in _sys_guard.argv[1:]):
    print('[%s] 本工具不接受命令行开关；收到 %r ⇒ 不执行任何操作。'
          % (__file__.rsplit('/', 1)[-1], _sys_guard.argv[1:]))
    print('用法: python3 %s    # 无参数，直接运行' % __file__)
    _sys_guard.exit(0)
# ---------------------------------------------------------------------------

CLSID_DiaSource = '{E6756135-1E65-4D17-8576-610761398C3C}'
SymTagData = 7
SymTagBaseClass = 18


# DIA baseType enum -> C type name
BASE_TYPE_MAP = {
    0: "void",      # btNoType
    1: "void",      # btVoid
    2: "char",      # btChar
    3: "wchar_t",   # btWChar
    6: "int",       # btInt
    7: "unsigned int",  # btUInt
    8: "float",     # btFloat (also double depending on length)
    9: "void",      # btBCD
    10: "bool",     # btBool
    13: "long",     # btLong
    14: "unsigned long",  # btULong
    25: "HRESULT",  # btHresult
}


def resolve_type(type_sym):
    """Recursively resolve a DIA type symbol to a C type string."""
    if not type_sym:
        return "int"

    tag = type_sym.symTag

    # UDT (struct/class/union) - use name directly
    if tag == 11:  # SymTagUDT
        name = type_sym.name if type_sym.name else "unknown_struct"
        return name

    # Pointer
    if tag == 14:  # SymTagPointerType
        pointee = type_sym.type
        if pointee:
            base = resolve_type(pointee)
            return base + " *"
        return "void *"

    # Array
    if tag == 15:  # SymTagArrayType
        elem = type_sym.type
        count = type_sym.count if hasattr(type_sym, 'count') else 0
        if elem:
            base = resolve_type(elem)
            if count > 0:
                return "%s[%d]" % (base, count)
            else:
                # Unknown count, use length / elem_length
                elem_len = elem.length if hasattr(elem, 'length') and elem.length > 0 else 1
                arr_len = type_sym.length if hasattr(type_sym, 'length') else 0
                n = arr_len // elem_len if elem_len > 0 else 0
                if n > 0:
                    return "%s[%d]" % (base, n)
                return "%s[]" % base
        return "char[%d]" % (type_sym.length if hasattr(type_sym, 'length') else 4)

    # Base type (int, float, char, etc.)
    if tag == 16:  # SymTagBaseType
        bt = type_sym.baseType if hasattr(type_sym, 'baseType') else 6
        length = type_sym.length if hasattr(type_sym, 'length') else 4
        # Refine by length
        if bt == 8:  # float family
            if length == 8:
                return "double"
            return "float"
        if bt == 6:  # int family
            if length == 1:
                return "char"
            if length == 2:
                return "short"
            if length == 8:
                return "__int64"
            return "int"
        if bt == 7:  # unsigned int family
            if length == 1:
                return "unsigned char"
            if length == 2:
                return "unsigned short"
            if length == 8:
                return "unsigned __int64"
            return "unsigned int"
        if bt == 2:  # char
            return "char"
        if bt == 1 or bt == 0:  # void
            return "void"
        if bt == 10:  # bool
            return "unsigned char"
        if bt == 13:  # long
            if length == 8:
                return "__int64"
            return "long"
        if bt == 14:  # unsigned long
            if length == 8:
                return "unsigned __int64"
            return "unsigned long"
        return BASE_TYPE_MAP.get(bt, "int")

    # Typedef
    if tag == 17:  # SymTagTypedef
        name = type_sym.name if type_sym.name else ""
        if name:
            return name
        # Follow the underlying type
        underlying = type_sym.type
        if underlying:
            return resolve_type(underlying)
        return "int"

    # Enum
    if tag == 12:  # SymTagEnum
        name = type_sym.name if type_sym.name else "int"
        return name

    # FunctionType
    if tag == 13:  # SymTagFunctionType
        return "void *"  # function pointer -> void*

    # Const/Volatile modifier
    if tag == 26 or tag == 27:  # const/volatile
        underlying = type_sym.type
        if underlying:
            return resolve_type(underlying)
        return "int"

    # Fallback
    name = type_sym.name if hasattr(type_sym, 'name') and type_sym.name else ""
    if name:
        return name
    return "char[%d]" % (type_sym.length if hasattr(type_sym, 'length') and type_sym.length else 4)


def main():
    pdb_path = os.path.abspath("original/PAL3A.pdb")
    export_path = os.path.abspath("asm/pal3a/pdb_export.json")

    dll_path = r"C:\Program Files\Microsoft Visual Studio\2022\Community\DIA SDK\bin\amd64\msdia140.dll"
    if not os.path.exists(dll_path):
        print("ERROR: msdia140.dll not found")
        return False

    import comtypes, comtypes.client
    comtypes.client.GetModule(dll_path)
    from comtypes.gen import Dia2Lib as DIA
    comtypes.CoInitialize()

    try:
        subprocess.run(["regsvr32", "/s", dll_path], check=False)
        source = comtypes.CoCreateInstance(
            comtypes.GUID(CLSID_DiaSource), interface=DIA.IDiaDataSource)
        source.loadDataFromPdb(pdb_path)
        session = source.openSession()
        gs = session.globalScope

        print("Enumerating all UDTs...")
        all_udts = gs.findChildren(DIA.SymTagUDT, None, 0)
        total = all_udts.Count
        print(f"  Total UDTs: {total}")

        new_entries = []
        for i in range(total):
            udt = all_udts.Item(i)
            udt_name = udt.name if udt.name else ""
            udt_kind = udt.udtKind  # 0=struct, 1=class, 2=union

            # Skip template types and unnamed
            if '<' in udt_name or not udt_name:
                continue

            entry = {
                "name": udt_name,
                "kind": "struct" if udt_kind == 0 else "union",
                "size": udt.length,
                "data_members": [],
                "methods": [],
                "static_members": [],
                "bases": [],
            }

            # Get children
            children = udt.findChildren(0, None, 0)
            if children:
                for j in range(children.Count):
                    child = children.Item(j)
                    tag = child.symTag

                    if tag == SymTagBaseClass:
                        base_name = child.name if child.name else ""
                        base_offset = child.offset if hasattr(child, 'offset') else 0
                        if base_name:
                            entry["bases"].append({
                                "name": base_name,
                                "offset": base_offset,
                                "virtual": False,
                            })
                    elif tag == SymTagData:
                        mname = child.name if child.name else ""
                        moffset = child.offset if hasattr(child, 'offset') else 0
                        mtype_sym = child.type
                        mtype_name = resolve_type(mtype_sym) if mtype_sym else "int"

                        entry["data_members"].append({
                            "name": mname,
                            "type": mtype_name,
                            "offset": moffset,
                        })

            new_entries.append(entry)

            if (i + 1) % 200 == 0:
                print(f"  [{i+1}/{total}]")

        print(f"\nNew struct/union entries: {len(new_entries)}")

        # Show some examples
        for e in new_entries[:10]:
            bases_str = ""
            if e["bases"]:
                bases_str = " : " + ", ".join(b["name"] for b in e["bases"])
            print(f"  {e['name']} ({e['kind']}, size={e['size']}, {len(e['data_members'])} members){bases_str}")

        # Replace classes in pdb_export.json with DIA-exported data
        print(f"\nUpdating {export_path}...")
        with open(export_path, 'r', encoding='utf-8') as f:
            data = json.load(f)

        # Build lookup of new entries by name (DIA has correct types)
        new_by_name = {}
        for entry in new_entries:
            # Keep first occurrence (avoid duplicates)
            if entry['name'] not in new_by_name:
                new_by_name[entry['name']] = entry

        # Replace existing classes with DIA versions, keep others
        updated = 0
        preserved = 0
        final_classes = []
        seen = set()
        for entry in new_entries:
            if entry['name'] not in seen:
                final_classes.append(entry)
                seen.add(entry['name'])

        # Preserve any old entries not in DIA output (shouldn't be many)
        for old in data.get('classes', []):
            if old['name'] not in seen:
                final_classes.append(old)
                preserved += 1

        data['classes'] = final_classes

        with open(export_path, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2, ensure_ascii=False)

        print(f"Total classes: {len(final_classes)} (DIA: {len(seen)}, preserved: {preserved})")
        return True

    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        return False
    finally:
        comtypes.CoUninitialize()


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
