# Export specific functions at known addresses from PAL3patch
# @category PAL3.Export
# Run in Ghidra headless mode:
#   analyzeHeadless asm/pal3 PAL3 -process PAL3.exe -postScript export_known_functions.py

from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.symbol import SourceType
import json
import os

KNOWN_FUNCTIONS = {
    0x00404800: ("PAL3_Create", "void PAL3_Create(HINSTANCE hInstance)"),
    0x00404D60: ("WndProc", "LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)"),
    0x00404FF0: ("PAL3_InitGFX", "void PAL3_InitGFX(void)"),
    0x004055D0: ("PAL3_Update", "void PAL3_Update(float deltaTime)"),
    0x00405C00: ("FrameRender", "void FrameRender(void)"),
    0x00406230: ("PAL3_Destroy", "void PAL3_Destroy(void)"),
}

OUTPUT_DIR = "D:/workspace/project-x/asm/pal3/functions_known"

def main():
    program = getCurrentProgram()
    if program is None:
        print("ERROR: No program loaded")
        return

    fm = program.getFunctionManager()
    listing = program.getListing()
    af = program.getAddressFactory()

    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    decompiler = DecompInterface()
    decompiler.openProgram(program)

    print("=" * 70)
    print("Exporting known PAL3 functions")
    print("=" * 70)

    for addr_int, (name, sig) in KNOWN_FUNCTIONS.items():
        addr = af.getDefaultAddressSpace().getAddress(addr_int)
        print("\nProcessing 0x%08X (%s)..." % (addr_int, name))

        func = fm.getFunctionAt(addr)
        if func is None:
            print("  Function not found at address, creating...")
            createFunction(addr, name)
            func = fm.getFunctionAt(addr)
            if func is None:
                print("  ERROR: Could not create function at 0x%08X" % addr_int)
                continue

        if func.getName().startswith("FUN_"):
            func.setName(name, SourceType.USER_DEFINED)
            print("  Renamed to: %s" % name)

        func_size = func.getBody().getNumAddresses()
        print("  Size: %d bytes" % func_size)

        # Decompile
        results = decompiler.decompileFunction(func, 60, ConsoleTaskMonitor())
        decomp_c = ""
        if results and results.decompileCompleted():
            decomp_c = results.getDecompiledFunction().getC()
            print("  Decompilation: OK")
        else:
            print("  Decompilation: FAILED")
            decomp_c = "// Decompilation failed"

        # Get assembly
        asm_lines = []
        for inst in listing.getInstructions(func.getBody(), True):
            iaddr = inst.getAddress()
            mnem = inst.getMnemonicString()
            ops = ""
            for i in range(inst.getNumOperands()):
                if i > 0:
                    ops += ","
                ops += inst.getDefaultOperandRepresentation(i)
            asm_lines.append("  %s:  %s %s" % (iaddr, mnem, ops))

        # Get callees
        callees = []
        for called in func.getCalledFunctions(ConsoleTaskMonitor()):
            callees.append({
                "address": "0x%08X" % called.getEntryPoint().getOffset(),
                "name": called.getName()
            })

        # Save JSON
        func_data = {
            "address": "0x%08X" % addr_int,
            "name": name,
            "size_bytes": func_size,
            "signature": sig,
            "decompiled_c": decomp_c,
            "assembly": "\n".join(asm_lines),
            "callees": callees,
            "source": "PAL3patch + Ghidra"
        }

        outpath = os.path.join(OUTPUT_DIR, "%s_%08X.json" % (name, addr_int))
        with open(outpath, 'w') as f:
            json.dump(func_data, f, indent=2, ensure_ascii=False)
        print("  Saved: %s" % outpath)

    decompiler.dispose()
    print("\n" + "=" * 70)
    print("Done! Exported %d functions to %s" % (len(KNOWN_FUNCTIONS), OUTPUT_DIR))
    print("=" * 70)

if __name__ == "__main__":
    main()
