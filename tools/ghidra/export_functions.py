# export_functions.py
# @category PAL3.Export
# @description Export all PAL3.exe functions to JSON files
# @author PAL3 Decompilation Project
# @menupath Tools.PAL3.Export Functions to JSON

from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.symbol import RefType
import json
import os
import sys

def get_decompiled_code(func, decompiler):
    """Get decompiled C code for a function."""
    try:
        results = decompiler.decompileFunction(func, 30, ConsoleTaskMonitor())
        if results and results.decompileCompleted():
            decomp_func = results.getDecompiledFunction()
            if decomp_func:
                return decomp_func.getC()
        return None
    except Exception as e:
        print("  WARNING: Failed to decompile {}: {}".format(func.getName(), str(e)))
        return None

def get_assembly(func, listing):
    """Get assembly instructions for a function."""
    try:
        instructions = []
        addr_set = func.getBody()
        if addr_set is None or addr_set.isEmpty():
            return ""

        # Get assembly as text
        asm_lines = []
        instr = listing.getInstructionAt(addr_set.getMinAddress())
        while instr is not None and addr_set.contains(instr.getAddress()):
            addr_str = "{:08x}".format(instr.getAddress().getOffset())
            instr_str = instr.toString()
            asm_lines.append("  {}:  {}".format(addr_str, instr_str))
            instr = instr.getNext()
            if instr is None or not addr_set.contains(instr.getAddress()):
                break

        return "\n".join(asm_lines)
    except Exception as e:
        print("  WARNING: Failed to get assembly for {}: {}".format(func.getName(), str(e)))
        return ""

def get_callees(func, ref_mgr, func_mgr):
    """Get functions called by this function."""
    callees = []
    try:
        addr_set = func.getBody()
        if addr_set is None or addr_set.isEmpty():
            return callees

        seen = set()
        addr_iter = addr_set.getAddresses(True)
        while addr_iter.hasNext():
            addr = addr_iter.next()
            refs = ref_mgr.getReferencesFrom(addr)
            for ref in refs:
                ref_type = ref.getReferenceType()
                if ref_type.isCall():
                    target = ref.getToAddress()
                    target_offset = target.getOffset()

                    # Skip duplicates
                    if target_offset in seen:
                        continue
                    seen.add(target_offset)

                    target_func = func_mgr.getFunctionAt(target)
                    if target_func:
                        callees.append({
                            "address": "0x{:08x}".format(target_offset),
                            "name": target_func.getName()
                        })

        return callees
    except Exception as e:
        print("  WARNING: Failed to get callees for {}: {}".format(func.getName(), str(e)))
        return []

def get_callers(func, ref_mgr, func_mgr):
    """Get functions that call this function."""
    callers = []
    try:
        entry = func.getEntryPoint()
        refs = ref_mgr.getReferencesTo(entry)

        seen = set()
        for ref in refs:
            ref_type = ref.getReferenceType()
            if ref_type.isCall():
                from_addr = ref.getFromAddress()
                caller_func = func_mgr.getFunctionContaining(from_addr)
                if caller_func:
                    caller_offset = caller_func.getEntryPoint().getOffset()

                    # Skip duplicates
                    if caller_offset in seen:
                        continue
                    seen.add(caller_offset)

                    callers.append({
                        "address": "0x{:08x}".format(caller_offset),
                        "name": caller_func.getName()
                    })

        return callers
    except Exception as e:
        print("  WARNING: Failed to get callers for {}: {}".format(func.getName(), str(e)))
        return []

def get_global_refs(func, ref_mgr, program):
    """Get global data references in this function."""
    global_refs = []
    try:
        addr_set = func.getBody()
        if addr_set is None or addr_set.isEmpty():
            return global_refs

        seen = set()
        addr_iter = addr_set.getAddresses(True)
        while addr_iter.hasNext():
            addr = addr_iter.next()
            refs = ref_mgr.getReferencesFrom(addr)
            for ref in refs:
                ref_type = ref.getReferenceType()
                if ref_type.isData():
                    target = ref.getToAddress()
                    target_offset = target.getOffset()

                    # Skip duplicates
                    if target_offset in seen:
                        continue
                    seen.add(target_offset)

                    # Get symbol name if available
                    symbol = program.getSymbolTable().getPrimarySymbol(target)
                    symbol_name = symbol.getName() if symbol else "DAT_{:08x}".format(target_offset)

                    global_refs.append({
                        "address": "0x{:08x}".format(target_offset),
                        "type": None,
                        "name": symbol_name
                    })

        return global_refs
    except Exception as e:
        print("  WARNING: Failed to get global refs for {}: {}".format(func.getName(), str(e)))
        return []

def has_custom_name(func):
    """Check if function has a custom (non-default) name."""
    name = func.getName()
    # Default Ghidra names are like FUN_00401000, thunk_FUN_00401000, etc.
    if name.startswith("FUN_") or name.startswith("thunk_FUN_"):
        return False
    return True

def export_function(func, decompiler, listing, ref_mgr, func_mgr, program, output_dir):
    """Export a single function to JSON."""
    addr = func.getEntryPoint()
    addr_offset = addr.getOffset()
    name = func.getName()
    size = func.getBody().getNumAddresses() if func.getBody() else 0

    # Build function data matching the existing format
    func_data = {
        "address": "0x{:08x}".format(addr_offset),
        "size_bytes": size,
        "calling_convention": func.getCallingConventionName() or "__cdecl",
        "signature": func.getSignature().getPrototypeString() if func.getSignature() else "",
        "callees": get_callees(func, ref_mgr, func_mgr),
        "global_refs": get_global_refs(func, ref_mgr, program),
        "has_custom_name": has_custom_name(func),
        "decompiled_c": get_decompiled_code(func, decompiler),
        "is_thunk": func.isThunk(),
        "name": name,
        "assembly": get_assembly(func, listing),
        "callers": get_callers(func, ref_mgr, func_mgr)
    }

    # Save to file using format: FunctionName_ADDRESS.json
    safe_name = name.replace("::", "_").replace("<", "_").replace(">", "_").replace("?", "_")
    filename = "{}_{:08x}.json".format(safe_name, addr_offset)
    filepath = os.path.join(output_dir, filename)

    with open(filepath, 'w') as f:
        json.dump(func_data, f, indent=2)

    return func_data

def main():
    """Main export function."""
    try:
        # Setup
        program = currentProgram
        fm = program.getFunctionManager()
        listing = program.getListing()
        ref_mgr = program.getReferenceManager()

        # Setup decompiler
        decompiler = DecompInterface()
        decompiler.openProgram(program)

        # Output directory - use hardcoded path for reliability
        project_root = "D:/workspace/project-x"
        output_dir = os.path.join(project_root, "asm", "pal3", "functions")

        # Ensure output directory exists
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        # Export all functions
        func_count = fm.getFunctionCount()
        print("=" * 70)
        print("PAL3.exe Function Export")
        print("=" * 70)
        print("Program: {}".format(program.getName()))
        print("Total functions: {}".format(func_count))
        print("Output directory: {}".format(output_dir))
        print("=" * 70)
        print("")

        all_functions = []
        count = 0
        skipped = 0

        for func in fm.getFunctions(True):  # True = forward iteration
            # Skip external functions (imports)
            if func.isExternal():
                skipped += 1
                continue

            try:
                func_data = export_function(func, decompiler, listing, ref_mgr, fm, program, output_dir)

                # Add to summary (without heavy data like assembly and decompiled code)
                all_functions.append({
                    "address": func_data["address"],
                    "name": func_data["name"],
                    "size_bytes": func_data["size_bytes"],
                    "signature": func_data["signature"],
                    "calling_convention": func_data["calling_convention"],
                    "has_custom_name": func_data["has_custom_name"],
                    "is_thunk": func_data["is_thunk"],
                    "callees_count": len(func_data["callees"]),
                    "callers_count": len(func_data["callers"]),
                    "global_refs_count": len(func_data["global_refs"])
                })

                count += 1
                if count % 100 == 0:
                    print("  Exported {}/{} functions...".format(count, func_count - skipped))

            except Exception as e:
                print("  ERROR: Failed to export function {}: {}".format(func.getName(), str(e)))
                continue

        print("")
        print("Exported {} functions (skipped {} external)".format(count, skipped))
        print("")

        # Save summary index
        summary = {
            "program": program.getName(),
            "image_base": "0x{:08x}".format(program.getImageBase().getOffset()),
            "total_functions": len(all_functions),
            "exported_count": count,
            "external_count": skipped,
            "functions": all_functions
        }

        summary_path = os.path.join(project_root, "asm", "pal3", "pal3_functions.json")
        with open(summary_path, 'w') as f:
            json.dump(summary, f, indent=2)

        print("=" * 70)
        print("Export Complete!")
        print("=" * 70)
        print("Functions exported: {}".format(len(all_functions)))
        print("Output directory: {}".format(output_dir))
        print("Summary file: {}".format(summary_path))
        print("=" * 70)

        decompiler.dispose()

    except Exception as e:
        print("FATAL ERROR: {}".format(str(e)))
        import traceback
        traceback.print_exc()
        return 1

    return 0

# Run the export
if __name__ == "__main__":
    sys.exit(main())
