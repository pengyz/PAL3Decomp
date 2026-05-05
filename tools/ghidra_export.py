#!/usr/bin/env python3
"""
Ghidra Headless Export Script for PAL3 Decompilation.

Run via Ghidra's analyzeHeadless:
    analyzeHeadless <project_dir> <project_name> \
        -process PAL3.exe \
        -postScript ghidra_export.py [options]

Options (passed as script args):
    --output-dir <dir>    Output directory for JSON files (default: ../asm)
    --min-size <n>        Minimum function size in bytes to export (default: 8)
    --address <addr>      Export only a specific function at this address
    --module <name>       Export only functions in a given address range/module
    --list-only           Only list functions without exporting decompiled code

This script exports each function as a JSON file containing:
- Function address and name
- Ghidra decompiled C code
- Raw assembly listing
- Callee/caller references
- Global variable references
- Function size
"""

# Ghidra imports (available when running inside Ghidra's Jython/Python environment)
try:
    from ghidra.app.decompiler import DecompInterface, DecompileOptions
    from ghidra.program.model.listing import CodeUnit
    from ghidra.program.model.symbol import SourceType, RefType
    from ghidra.util.task import ConsoleTaskMonitor
    GHIDRA_ENV = True
except ImportError:
    GHIDRA_ENV = False

import json
import os
import sys


def get_script_args():
    """Parse script arguments passed via Ghidra's analyzeHeadless."""
    args = {
        'output_dir': None,
        'min_size': 8,
        'address': None,
        'addr_file': None,
        'module': None,
        'list_only': False,
    }

    if GHIDRA_ENV:
        script_args = getScriptArgs()  # noqa: F821 - Ghidra built-in
    else:
        script_args = sys.argv[1:]

    i = 0
    while i < len(script_args):
        arg = script_args[i]
        if arg == '--output-dir' and i + 1 < len(script_args):
            args['output_dir'] = script_args[i + 1]
            i += 2
        elif arg == '--min-size' and i + 1 < len(script_args):
            args['min_size'] = int(script_args[i + 1])
            i += 2
        elif arg == '--address' and i + 1 < len(script_args):
            args['address'] = script_args[i + 1]
            i += 2
        elif arg == '--addr-file' and i + 1 < len(script_args):
            args['addr_file'] = script_args[i + 1]
            i += 2
        elif arg == '--module' and i + 1 < len(script_args):
            args['module'] = script_args[i + 1]
            i += 2
        elif arg == '--list-only':
            args['list_only'] = True
            i += 1
        else:
            i += 1

    return args


def setup_decompiler(program):
    """Initialize the Ghidra decompiler interface."""
    decompiler = DecompInterface()
    options = DecompileOptions()
    decompiler.setOptions(options)
    decompiler.openProgram(program)
    return decompiler


def get_function_assembly(func, listing):
    """Extract the assembly listing for a function."""
    lines = []
    addr_set = func.getBody()
    code_units = listing.getCodeUnits(addr_set, True)

    for cu in code_units:
        addr = cu.getAddress()
        mnemonic = cu.getMnemonicString()
        # Get the full representation including operands
        rep = cu.toString()
        lines.append("  {:08x}:  {}".format(addr.getOffset(), rep))

    return "\n".join(lines)


def get_callees(func, program):
    """Get list of functions called by this function."""
    callees = []
    ref_mgr = program.getReferenceManager()
    addr_set = func.getBody()
    func_mgr = program.getFunctionManager()

    iter_refs = ref_mgr.getReferenceIterator(addr_set.getMinAddress())
    while iter_refs.hasNext():
        ref = iter_refs.next()
        if not addr_set.contains(ref.getFromAddress()):
            continue
        if ref.getReferenceType().isCall():
            to_addr = ref.getToAddress()
            called_func = func_mgr.getFunctionAt(to_addr)
            if called_func:
                callees.append({
                    'address': "0x{:08x}".format(to_addr.getOffset()),
                    'name': called_func.getName(),
                })
            else:
                callees.append({
                    'address': "0x{:08x}".format(to_addr.getOffset()),
                    'name': None,
                })

    return callees


def get_callers(func, program):
    """Get list of functions that call this function."""
    callers = []
    func_mgr = program.getFunctionManager()
    entry = func.getEntryPoint()
    ref_mgr = program.getReferenceManager()

    refs_to = ref_mgr.getReferencesTo(entry)
    for ref in refs_to:
        if ref.getReferenceType().isCall():
            from_addr = ref.getFromAddress()
            caller_func = func_mgr.getFunctionContaining(from_addr)
            if caller_func:
                callers.append({
                    'address': "0x{:08x}".format(caller_func.getEntryPoint().getOffset()),
                    'name': caller_func.getName(),
                })

    return callers


def get_global_refs(func, program):
    """Get global variables referenced by this function."""
    globals_refs = []
    ref_mgr = program.getReferenceManager()
    addr_set = func.getBody()
    listing = program.getListing()

    iter_refs = ref_mgr.getReferenceIterator(addr_set.getMinAddress())
    while iter_refs.hasNext():
        ref = iter_refs.next()
        if not addr_set.contains(ref.getFromAddress()):
            continue
        if ref.getReferenceType().isData():
            to_addr = ref.getToAddress()
            data = listing.getDefinedDataAt(to_addr)
            data_type = None
            if data:
                data_type = str(data.getDataType())
            globals_refs.append({
                'address': "0x{:08x}".format(to_addr.getOffset()),
                'name': "DAT_{:08x}".format(to_addr.getOffset()),
                'type': data_type,
            })

    # Deduplicate by address
    seen = set()
    unique = []
    for g in globals_refs:
        if g['address'] not in seen:
            seen.add(g['address'])
            unique.append(g)

    return unique


def decompile_function(decompiler, func, monitor):
    """Decompile a single function and return the C code."""
    results = decompiler.decompileFunction(func, 60, monitor)
    if results is not None:
        decomp_func = results.getDecompiledFunction()
        if decomp_func is not None:
            return decomp_func.getC()
        # Try alternative: check if decompilation completed successfully
        if results.decompileCompleted():
            c_markup = results.getCCodeMarkup()
            if c_markup is not None:
                return c_markup.toString()
    return None


def get_function_info(func):
    """Get basic function metadata."""
    return {
        'address': "0x{:08x}".format(func.getEntryPoint().getOffset()),
        'name': func.getName(),
        'signature': str(func.getSignature()),
        'size_bytes': func.getBody().getNumAddresses(),
        'is_thunk': func.isThunk(),
        'calling_convention': str(func.getCallingConventionName()),
        'has_custom_name': func.getSymbol().getSource() != SourceType.DEFAULT,
    }


def export_function(func, decompiler, program, listing, monitor, output_dir):
    """Export a single function to a JSON file."""
    info = get_function_info(func)

    # Decompile
    decompiled_c = decompile_function(decompiler, func, monitor)

    # Get assembly
    assembly = get_function_assembly(func, listing)

    # Get references
    callees = get_callees(func, program)
    callers = get_callers(func, program)
    global_refs = get_global_refs(func, program)

    export_data = {
        'address': info['address'],
        'name': info['name'],
        'signature': info['signature'],
        'size_bytes': info['size_bytes'],
        'is_thunk': info['is_thunk'],
        'calling_convention': info['calling_convention'],
        'has_custom_name': info['has_custom_name'],
        'decompiled_c': decompiled_c,
        'assembly': assembly,
        'callees': callees,
        'callers': callers,
        'global_refs': global_refs,
    }

    # Write to file
    addr_str = info['address'].replace('0x', '')
    filename = "{}_{}.json".format(info['name'], addr_str)
    filepath = os.path.join(output_dir, filename)

    with open(filepath, 'w') as f:
        json.dump(export_data, f, indent=2)

    return filepath


def get_text_section_range(program):
    """Get the address range of the .text section."""
    memory = program.getMemory()
    for block in memory.getBlocks():
        if block.getName() == '.text':
            return (block.getStart(), block.getEnd())
    return None


def run():
    """Main entry point for the Ghidra script."""
    if not GHIDRA_ENV:
        print("ERROR: This script must be run inside Ghidra's headless analyzer.")
        print("Usage: analyzeHeadless <project_dir> <project_name> \\")
        print("         -process PAL3.exe -postScript ghidra_export.py [options]")
        sys.exit(1)

    args = get_script_args()

    # Resolve output directory
    if args['output_dir']:
        output_dir = args['output_dir']
    else:
        # Default: asm/ directory relative to the script location
        script_dir = os.path.dirname(os.path.abspath(sourceFile.getAbsolutePath()))  # noqa: F821
        output_dir = os.path.join(os.path.dirname(script_dir), 'asm')

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Get program references (Ghidra globals)
    program = currentProgram  # noqa: F821
    listing = program.getListing()
    func_mgr = program.getFunctionManager()
    monitor = ConsoleTaskMonitor()

    # Setup decompiler
    decompiler = setup_decompiler(program)

    # Get text section info
    text_range = get_text_section_range(program)
    if text_range:
        print("[*] .text section: {} - {}".format(text_range[0], text_range[1]))

    # Collect functions to export
    functions = []
    if args['address']:
        # Export single function
        addr_factory = program.getAddressFactory()
        addr = addr_factory.getAddress(args['address'])
        func = func_mgr.getFunctionAt(addr)
        if func:
            functions.append(func)
        else:
            print("ERROR: No function found at address {}".format(args['address']))
            return
    elif args.get('addr_file'):
        # Export functions listed in address file
        addr_set = set()
        with open(args['addr_file'], 'r') as f:
            for line in f:
                line = line.strip()
                if line:
                    addr_set.add(line.lower().replace('0x', ''))

        func_iter = func_mgr.getFunctions(True)
        for func in func_iter:
            if func.isExternal() or func.isThunk():
                continue
            addr_hex = "{:08x}".format(func.getEntryPoint().getOffset())
            if addr_hex in addr_set:
                functions.append(func)
    else:
        # Export all functions matching criteria
        func_iter = func_mgr.getFunctions(True)  # Forward iterator
        for func in func_iter:
            if func.isExternal():
                continue
            if func.getBody().getNumAddresses() < args['min_size']:
                continue
            if func.isThunk():
                continue
            functions.append(func)

    print("[*] Found {} functions to process".format(len(functions)))

    if args['list_only']:
        # Just list functions
        summary = []
        for func in functions:
            info = get_function_info(func)
            summary.append(info)
            print("  {} {} ({} bytes)".format(
                info['address'], info['name'], info['size_bytes']))

        # Write summary
        summary_path = os.path.join(output_dir, '_function_list.json')
        with open(summary_path, 'w') as f:
            json.dump(summary, f, indent=2)
        print("[*] Function list written to: {}".format(summary_path))
        return

    # Export each function
    exported = 0
    errors = 0
    for i, func in enumerate(functions):
        try:
            filepath = export_function(func, decompiler, program, listing, monitor, output_dir)
            exported += 1
            if (i + 1) % 200 == 0:
                print("[*] Progress: {}/{} functions exported".format(i + 1, len(functions)))
        except Exception as e:
            errors += 1
            if errors <= 10:
                print("[!] Error exporting {}: {}".format(func.getName(), str(e)))

    print("[*] Export complete: {} exported, {} errors".format(exported, errors))

    # Write export summary
    summary = {
        'total_functions': len(functions),
        'exported': exported,
        'errors': errors,
        'output_dir': output_dir,
    }
    summary_path = os.path.join(output_dir, '_export_summary.json')
    with open(summary_path, 'w') as f:
        json.dump(summary, f, indent=2)


# Entry point
if GHIDRA_ENV:
    run()
elif __name__ == '__main__':
    print("This script is designed to run inside Ghidra's headless analyzer.")
    print("")
    print("Usage:")
    print("  analyzeHeadless /path/to/project PAL3Project \\")
    print("    -process PAL3.exe \\")
    print("    -postScript ghidra_export.py --output-dir ./asm")
    print("")
    print("Options:")
    print("  --output-dir <dir>   Output directory for JSON files")
    print("  --min-size <n>       Min function size in bytes (default: 8)")
    print("  --address <addr>     Export only one function (e.g., 0x00401000)")
    print("  --list-only          List functions without decompiling")
