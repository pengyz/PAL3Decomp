"""
Export PAL3A.pdb symbols using Microsoft DIA SDK via comtypes.
Works with PDB 2.0 (JG format) on Windows with VS2022 installed.

Usage: python tools/dia_export_pdb.py
Output: asm/pal3a/pdb_export.json
"""
import sys
import os
import json
import ctypes
from ctypes import wintypes

# DIA SDK GUIDs
CLSID_DiaSource = '{E6756135-1E65-4D17-8576-610761398C3C}'
IID_IDiaDataSource = '{79F1BB5F-B66E-48E5-B6A9-1545C323CA3D}'

def find_msdia_dll():
    """Find msdia140.dll from Visual Studio installation."""
    candidates = [
        r"C:\Program Files\Microsoft Visual Studio\2022\Community\DIA SDK\bin\amd64\msdia140.dll",
        r"C:\Program Files\Microsoft Visual Studio\2022\Professional\DIA SDK\bin\amd64\msdia140.dll",
        r"C:\Program Files\Microsoft Visual Studio\2022\Enterprise\DIA SDK\bin\amd64\msdia140.dll",
        r"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\DIA SDK\bin\amd64\msdia140.dll",
    ]
    for path in candidates:
        if os.path.exists(path):
            return path
    return None


def create_dia_source(dll_path):
    """Create DiaSource COM object without registry using DllGetClassObject."""
    import comtypes
    import comtypes.client

    # Load DLL
    dll = ctypes.OleDLL(dll_path)

    # Get class factory
    from comtypes import GUID, HRESULT, IUnknown, COMMETHOD, POINTER
    import comtypes.automation

    clsid = GUID(CLSID_DiaSource)
    iid_factory = GUID('{00000001-0000-0000-C000-000000000046}')  # IClassFactory

    factory = ctypes.POINTER(IUnknown)()
    hr = dll.DllGetClassObject(ctypes.byref(clsid), ctypes.byref(iid_factory), ctypes.byref(factory))
    if hr != 0:
        raise OSError(f"DllGetClassObject failed: 0x{hr:08X}")

    # Use comtypes to work with the DIA interfaces
    # Load the type library
    tlb_path = dll_path.replace('.dll', '.dll')  # Same file contains typelib
    try:
        comtypes.client.GetModule(dll_path)
    except:
        pass

    # Create instance via CoCreateInstance with the DLL loaded
    from comtypes import CoCreateInstance, CLSCTX_INPROC_SERVER

    # Register DLL temporarily in process
    ole32 = ctypes.windll.ole32
    ole32.CoInitialize(None)

    # Try to create the source object
    source = comtypes.client.CreateObject(CLSID_DiaSource, interface=None)
    return source


def export_via_dia_direct(pdb_path, output_path):
    """Use DIA SDK directly through comtypes."""
    import comtypes
    import comtypes.client

    dll_path = find_msdia_dll()
    if not dll_path:
        print("ERROR: msdia140.dll not found")
        return False

    print(f"Using DIA SDK: {dll_path}")

    # Initialize COM
    comtypes.CoInitialize()

    try:
        # Load the DIA type library from the DLL
        comtypes.client.GetModule(dll_path)
        from comtypes.gen import DIA

        # Create DiaSource using DllGetClassObject (no registry needed)
        dll = ctypes.OleDLL(dll_path)
        clsid = comtypes.GUID(CLSID_DiaSource)
        iid_classfactory = comtypes.GUID('{00000001-0000-0000-C000-000000000046}')

        factory = ctypes.POINTER(comtypes.IUnknown)()
        hr = dll.DllGetClassObject(ctypes.byref(clsid), ctypes.byref(iid_classfactory), ctypes.byref(factory))
        if hr != 0:
            raise OSError(f"DllGetClassObject failed: 0x{hr:08X}")

        # QI for IClassFactory
        from comtypes.hresult import S_OK

        class IClassFactory(comtypes.IUnknown):
            _iid_ = comtypes.GUID('{00000001-0000-0000-C000-000000000046}')
            _methods_ = [
                comtypes.COMMETHOD([], comtypes.HRESULT, 'CreateInstance',
                    (['in'], ctypes.POINTER(comtypes.IUnknown), 'pUnkOuter'),
                    (['in'], ctypes.POINTER(comtypes.GUID), 'riid'),
                    (['out'], ctypes.POINTER(ctypes.c_void_p), 'ppvObject')),
                comtypes.COMMETHOD([], comtypes.HRESULT, 'LockServer',
                    (['in'], ctypes.c_int, 'fLock')),
            ]

        cf = factory.QueryInterface(IClassFactory)

        # Create DiaSource instance
        iid_datasource = comtypes.GUID(IID_IDiaDataSource)
        obj_ptr = ctypes.c_void_p()
        hr = cf.CreateInstance(None, ctypes.byref(iid_datasource), ctypes.byref(obj_ptr))
        if hr != 0:
            raise OSError(f"CreateInstance failed: 0x{hr:08X}")

        # Cast to IDiaDataSource
        source = ctypes.POINTER(DIA.IDiaDataSource)(obj_ptr.value)
        # Actually need to properly wrap it
        source = comtypes.cast(obj_ptr, ctypes.POINTER(DIA.IDiaDataSource))

        print(f"Loading PDB: {pdb_path}")
        source.loadDataFromPdb(pdb_path)

        print("Opening session...")
        session = source.openSession()

        # Get global scope
        global_scope = session.globalScope

        result = {
            "image_base": "0x00400000",
            "functions": [],
            "globals": [],
            "types": [],
            "source_files": [],
            "compilands": []
        }

        # Enumerate compilands (source files / obj modules)
        print("Enumerating compilands...")
        compilands = global_scope.findChildren(DIA.SymTagCompiland, None, 0)

        comp_count = 0
        for i in range(compilands.Count):
            compiland = compilands.Item(i)
            comp_name = compiland.name if compiland.name else ""

            comp_entry = {
                "name": comp_name,
                "source_files": [],
                "functions": []
            }

            # Get source files for this compiland
            src_files = session.findFile(compiland, None, 0)
            if src_files:
                for j in range(src_files.Count):
                    sf = src_files.Item(j)
                    if sf.fileName:
                        comp_entry["source_files"].append(sf.fileName)

            # Get functions in this compiland
            funcs = compiland.findChildren(DIA.SymTagFunction, None, 0)
            if funcs:
                for j in range(funcs.Count):
                    func = funcs.Item(j)
                    fname = func.name if func.name else ""
                    faddr = func.relativeVirtualAddress if hasattr(func, 'relativeVirtualAddress') else 0
                    flen = func.length if hasattr(func, 'length') else 0

                    # Get function type for signature
                    ret_type = ""
                    params = []
                    ftype = func.type
                    if ftype:
                        ret_sym = ftype.type
                        if ret_sym:
                            ret_type = ret_sym.name if ret_sym.name else str(ret_sym.baseType)

                        # Parameters
                        param_children = ftype.findChildren(DIA.SymTagFunctionArgType, None, 0)
                        if param_children:
                            for k in range(param_children.Count):
                                p = param_children.Item(k)
                                pt = p.type
                                ptype_name = pt.name if pt and pt.name else "unknown"
                                params.append({"type": ptype_name, "name": f"param_{k}"})

                    func_entry = {
                        "address": "0x{:08X}".format(0x00400000 + faddr),
                        "rva": "0x{:08X}".format(faddr),
                        "name": fname,
                        "namespace": func.classParent.name if hasattr(func, 'classParent') and func.classParent else "",
                        "return_type": ret_type,
                        "parameters": params,
                        "size": flen,
                        "source_file": comp_entry["source_files"][0] if comp_entry["source_files"] else "",
                    }
                    comp_entry["functions"].append(func_entry)
                    result["functions"].append(func_entry)

            result["compilands"].append(comp_entry)
            comp_count += 1
            if comp_count % 20 == 0:
                print(f"  Processed {comp_count} compilands...")

        # Enumerate UDTs (user-defined types: structs, classes)
        print("Enumerating types...")
        udts = global_scope.findChildren(DIA.SymTagUDT, None, 0)
        if udts:
            for i in range(min(udts.Count, 5000)):
                udt = udts.Item(i)
                udt_name = udt.name if udt.name else ""
                udt_size = udt.length if hasattr(udt, 'length') else 0
                udt_kind = udt.udtKind if hasattr(udt, 'udtKind') else 0
                # 0=struct, 1=class, 2=union
                kind_map = {0: "struct", 1: "class", 2: "union"}

                members = []
                mem_children = udt.findChildren(DIA.SymTagData, None, 0)
                if mem_children:
                    for j in range(mem_children.Count):
                        mem = mem_children.Item(j)
                        mname = mem.name if mem.name else ""
                        moffset = mem.offset if hasattr(mem, 'offset') else 0
                        mtype = mem.type
                        mtype_name = mtype.name if mtype and mtype.name else "unknown"
                        msize = mtype.length if mtype and hasattr(mtype, 'length') else 0
                        members.append({
                            "name": mname,
                            "type": mtype_name,
                            "offset": moffset,
                            "size": msize
                        })

                result["types"].append({
                    "name": udt_name,
                    "kind": kind_map.get(udt_kind, "struct"),
                    "size": udt_size,
                    "members": members
                })

        # Enumerate global data
        print("Enumerating globals...")
        gdata = global_scope.findChildren(DIA.SymTagData, None, 0)
        if gdata:
            for i in range(min(gdata.Count, 20000)):
                g = gdata.Item(i)
                gname = g.name if g.name else ""
                if not gname or gname.startswith("__"):
                    continue
                grva = g.relativeVirtualAddress if hasattr(g, 'relativeVirtualAddress') else 0
                gtype = g.type
                gtype_name = gtype.name if gtype and gtype.name else "unknown"
                gsize = gtype.length if gtype and hasattr(gtype, 'length') else 0

                result["globals"].append({
                    "address": "0x{:08X}".format(0x00400000 + grva),
                    "name": gname,
                    "datatype": gtype_name,
                    "size": gsize
                })

        print(f"\nExport complete:")
        print(f"  Compilands: {len(result['compilands'])}")
        print(f"  Functions: {len(result['functions'])}")
        print(f"  Types: {len(result['types'])}")
        print(f"  Globals: {len(result['globals'])}")

        # Write output
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
        with open(output_path, 'w', encoding='utf-8') as f:
            json.dump(result, f, indent=2, ensure_ascii=False)

        print(f"Output: {output_path}")
        return True

    except Exception as e:
        print(f"DIA error: {e}")
        import traceback
        traceback.print_exc()
        return False
    finally:
        comtypes.CoUninitialize()


if __name__ == "__main__":
    pdb_path = os.path.abspath("original/PAL3A.pdb")
    output_path = os.path.abspath("asm/pal3a/pdb_export.json")

    if not os.path.exists(pdb_path):
        print(f"PDB not found: {pdb_path}")
        sys.exit(1)

    success = export_via_dia_direct(pdb_path, output_path)
    sys.exit(0 if success else 1)
