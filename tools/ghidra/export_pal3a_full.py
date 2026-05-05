# Ghidra headless postScript: export PAL3A symbols to JSON
# Run via: analyzeHeadless <project_dir> PAL3A_Project -import PAL3A.exe -postScript export_pal3a_full.py <output_path>
# @category PAL3A

import json
import os
from ghidra.program.model.symbol import SymbolType
from ghidra.program.model.listing import CodeUnit
from ghidra.app.decompiler import DecompInterface
from ghidra.program.model.data import Structure, Union, Enum, TypeDef

args = getScriptArgs()
if args:
    output_file = args[0]
else:
    output_file = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
        getSourceFile().getAbsolutePath()))), "asm", "pal3a", "pdb_export.json")

program = currentProgram
listing = program.getListing()
dtm = program.getDataTypeManager()
sym_table = program.getSymbolTable()
func_mgr = program.getFunctionManager()

# Initialize decompiler
decomp = DecompInterface()
decomp.openProgram(program)
decomp.setSimplificationStyle("decompile")

result = {
    "image_base": "0x{:08X}".format(program.getImageBase().getOffset()),
    "functions": [],
    "globals": [],
    "types": []
}

# Export all functions
monitor.setMessage("Exporting functions...")
func_iter = func_mgr.getFunctions(True)
func_count = 0
total_funcs = func_mgr.getFunctionCount()

for func in func_iter:
    if monitor.isCancelled():
        break

    addr = func.getEntryPoint().getOffset()
    name = func.getName()
    sig = func.getSignature()

    # Get source file info from symbol
    source_file = ""
    sym = sym_table.getPrimarySymbol(func.getEntryPoint())
    if sym:
        # Try to get source mapping from PDB
        src_info = func.getProgram().getListing().getComment(
            CodeUnit.PLATE_COMMENT, func.getEntryPoint())
        if src_info and ("PAL3" in src_info or ".cpp" in src_info):
            source_file = src_info

    # Get namespace (class name)
    namespace = ""
    parent = func.getParentNamespace()
    if parent and not parent.isGlobal():
        namespace = parent.getName(True)

    # Build parameter list
    params = []
    for p in func.getParameters():
        params.append({
            "name": p.getName(),
            "type": p.getDataType().getDisplayName(),
            "size": p.getLength()
        })

    # Get function size
    body = func.getBody()
    size = body.getNumAddresses() if body else 0

    # Decompile (skip thunks and tiny functions)
    decompiled_c = ""
    if not func.isThunk() and size > 4:
        try:
            results = decomp.decompileFunction(func, 60, monitor)
            if results and results.decompileCompleted():
                df = results.getDecompiledFunction()
                if df:
                    decompiled_c = df.getC()
        except:
            pass

    func_entry = {
        "address": "0x{:08X}".format(addr),
        "name": name,
        "namespace": namespace,
        "return_type": sig.getReturnType().getDisplayName(),
        "parameters": params,
        "source_file": source_file,
        "size": size,
        "calling_convention": func.getCallingConventionName(),
        "is_thunk": func.isThunk(),
        "decompiled_c": decompiled_c
    }
    result["functions"].append(func_entry)
    func_count += 1

    if func_count % 200 == 0:
        monitor.setMessage("Exported {}/{} functions...".format(func_count, total_funcs))

# Export global variables
monitor.setMessage("Exporting globals...")
for sym in sym_table.getAllSymbols(True):
    if monitor.isCancelled():
        break
    if sym.getSymbolType() == SymbolType.LABEL:
        addr = sym.getAddress()
        if func_mgr.getFunctionAt(addr):
            continue
        data = listing.getDataAt(addr)
        if data:
            result["globals"].append({
                "address": "0x{:08X}".format(addr.getOffset()),
                "name": sym.getName(),
                "namespace": sym.getParentNamespace().getName(True) if not sym.getParentNamespace().isGlobal() else "",
                "datatype": data.getDataType().getDisplayName(),
                "size": data.getLength()
            })

# Export composite types
monitor.setMessage("Exporting types...")
for dt in dtm.getAllDataTypes():
    if monitor.isCancelled():
        break
    if isinstance(dt, (Structure, Union)):
        members = []
        for i in range(dt.getNumComponents()):
            comp = dt.getComponent(i)
            members.append({
                "name": comp.getFieldName() if comp.getFieldName() else "field_{:X}".format(comp.getOffset()),
                "type": comp.getDataType().getDisplayName(),
                "offset": comp.getOffset(),
                "size": comp.getLength()
            })
        kind = "union" if isinstance(dt, Union) else "struct"
        result["types"].append({
            "name": dt.getDisplayName(),
            "category": dt.getCategoryPath().toString(),
            "kind": kind,
            "size": dt.getLength(),
            "members": members
        })
    elif isinstance(dt, Enum):
        values = {}
        for name in dt.getNames():
            values[name] = dt.getValue(name)
        result["types"].append({
            "name": dt.getDisplayName(),
            "category": dt.getCategoryPath().toString(),
            "kind": "enum",
            "size": dt.getLength(),
            "values": values
        })

decomp.dispose()

# Write output
out_dir = os.path.dirname(output_file)
if not os.path.exists(out_dir):
    os.makedirs(out_dir)

with open(output_file, 'w') as f:
    json.dump(result, f, indent=2, ensure_ascii=False)

println("Export complete: {} functions, {} globals, {} types".format(
    len(result["functions"]), len(result["globals"]), len(result["types"])))
println("Output: " + output_file)
