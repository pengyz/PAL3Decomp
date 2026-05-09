"""
Export class inheritance (base classes) from PAL3A.pdb using DIA SDK.

Reads the PDB via DIA, enumerates all UDTs, and for each class finds its
SymTagBaseClass children to determine inheritance relationships.

Updates asm/pal3a/pdb_export.json in-place, adding "bases" field to each class.

Usage: python tools/dia_export_bases.py
"""
import sys
import os
import json
import ctypes
from ctypes import wintypes

CLSID_DiaSource = '{E6756135-1E65-4D17-8576-610761398C3C}'
IID_IDiaDataSource = '{79F1BB5F-B66E-48E5-B6A9-1545C323CA3D}'

# DIA SymTag enum values (from Dia2Lib)
SymTagUDT = 11
SymTagBaseClass = 18
SymTagData = 7


def find_msdia_dll():
    candidates = [
        r"C:\Program Files\Microsoft Visual Studio\2022\Community\DIA SDK\bin\amd64\msdia140.dll",
        r"C:\Program Files\Microsoft Visual Studio\2022\Professional\DIA SDK\bin\amd64\msdia140.dll",
        r"C:\Program Files\Microsoft Visual Studio\2022\Enterprise\DIA SDK\bin\amd64\msdia140.dll",
        r"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\DIA SDK\bin\amd64\msdia140.dll",
        r"D:\Program Files\Microsoft Visual Studio\2022\Community\DIA SDK\bin\amd64\msdia140.dll",
    ]
    for path in candidates:
        if os.path.exists(path):
            return path
    return None


def main():
    pdb_path = os.path.abspath("original/PAL3A.pdb")
    export_path = os.path.abspath("asm/pal3a/pdb_export.json")

    if not os.path.exists(pdb_path):
        print(f"PDB not found: {pdb_path}")
        return False

    dll_path = find_msdia_dll()
    if not dll_path:
        print("ERROR: msdia140.dll not found")
        return False

    print(f"DIA SDK: {dll_path}")
    print(f"PDB: {pdb_path}")

    import comtypes
    import comtypes.client

    comtypes.CoInitialize()

    try:
        # Load DIA type library
        try:
            comtypes.client.GetModule(dll_path)
        except Exception:
            pass  # May already be generated
        from comtypes.gen import Dia2Lib as DIA

        # Create DiaSource - register DLL and use CoCreateInstance
        import subprocess
        # Register the DLL
        subprocess.run(["regsvr32", "/s", dll_path], check=False)

        # Create via CoCreateInstance
        source = comtypes.CoCreateInstance(
            comtypes.GUID(CLSID_DiaSource),
            interface=DIA.IDiaDataSource,
        )

        print("Loading PDB...")
        source.loadDataFromPdb(pdb_path)
        session = source.openSession()
        global_scope = session.globalScope

        # Enumerate all UDTs and find base classes
        print("Enumerating UDTs for base class info...")
        udts = global_scope.findChildren(SymTagUDT, None, 0)

        inheritance = {}  # class_name -> [{"name": base_name, "offset": N, "virtual": bool}]
        total = udts.Count
        print(f"  Total UDTs: {total}")

        for i in range(total):
            udt = udts.Item(i)
            udt_name = udt.name if udt.name else ""
            if not udt_name or '<' in udt_name or '::' in udt_name:
                continue

            # Find base class children - use SymTagNull (0) to get all, filter by symTag
            all_children = udt.findChildren(0, None, 0)
            if all_children and all_children.Count > 0:
                base_list = []
                for j in range(all_children.Count):
                    child = all_children.Item(j)
                    if child.symTag == SymTagBaseClass:
                        base_name = child.name if child.name else ""
                        base_offset = child.offset if hasattr(child, 'offset') else 0
                        is_virtual = bool(child.virtualBaseClass) if hasattr(child, 'virtualBaseClass') else False
                        if base_name:
                            base_list.append({
                                "name": base_name,
                                "offset": base_offset,
                                "virtual": is_virtual,
                            })
                if base_list:
                    inheritance[udt_name] = base_list

            if (i + 1) % 200 == 0:
                print(f"  [{i+1}/{total}]")

        print(f"\nFound inheritance for {len(inheritance)} classes")

        # Show some examples
        for name in sorted(list(inheritance.keys()))[:10]:
            bases = inheritance[name]
            base_strs = [f"{b['name']}(+0x{b['offset']:X})" for b in bases]
            print(f"  {name} : {', '.join(base_strs)}")

        # Update pdb_export.json
        print(f"\nUpdating {export_path}...")
        with open(export_path, 'r', encoding='utf-8') as f:
            data = json.load(f)

        updated = 0
        for cls in data.get('classes', []):
            name = cls['name']
            if name in inheritance:
                cls['bases'] = inheritance[name]
                updated += 1
            else:
                cls['bases'] = None

        with open(export_path, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2, ensure_ascii=False)

        print(f"Updated {updated} classes with base class info")
        return True

    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        return False
    finally:
        comtypes.CoUninitialize()


if __name__ == "__main__":
    success = main()
    sys.exit(0 if success else 1)
