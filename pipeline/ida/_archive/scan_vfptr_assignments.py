"""IDAPython: Scan all functions for vfptr assignments (mov [reg], offset vtable_addr).

Finds ground-truth vtable ownership by detecting constructor patterns:
  mov dword ptr [ecx], offset off_56XXXX  (this->vfptr = &vtable)
  mov dword ptr [eax], offset off_57XXXX

Output: pipeline/ida/_logs/vfptr_assignments.json
"""
import ida_bytes
import ida_funcs
import ida_name
import ida_segment
import idautils
import idc
import json
import os
import re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_FILE = os.path.join(LOG_DIR, "vfptr_assignments.json")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
RDATA_START = 0x0056A000
RDATA_END = 0x0057F178


def is_rdata_addr(addr):
    return RDATA_START <= addr < RDATA_END


def scan_function(ea):
    """Scan a function for 'mov [reg], offset rdata_addr' patterns (vfptr assignment)."""
    results = []
    func = ida_funcs.get_func(ea)
    if not func:
        return results

    for head in idautils.FuncItems(ea):
        mnem = idc.print_insn_mnem(head)
        if mnem != 'mov':
            continue

        # Check: operand 0 is [reg] or [reg+0] (writing to this->vfptr at offset 0)
        op0_type = idc.get_operand_type(head, 0)
        if op0_type not in (idc.o_phrase, idc.o_displ):
            continue

        # For o_displ, check displacement is 0 (vfptr is at offset 0)
        if op0_type == idc.o_displ:
            displ = idc.get_operand_value(head, 0)
            # IDA encodes displacement differently; check if it's small
            # Actually get_operand_value for displ gives the displacement
            # We want displacement == 0 for vfptr
            pass  # We'll check operand 1 regardless

        # Check: operand 1 is an immediate address in .rdata
        op1_type = idc.get_operand_type(head, 1)
        if op1_type != idc.o_imm:
            continue

        imm_val = idc.get_operand_value(head, 1)
        if not is_rdata_addr(imm_val):
            continue

        # This is a "mov [something], rdata_address" - likely vfptr assignment
        # Get the displacement of operand 0 to confirm it's offset 0
        # For mov [ecx], imm -> displacement is 0
        # For mov [ecx+8], imm -> displacement is 8 (not vfptr)
        disasm = idc.GetDisasm(head)
        # Check if it's [reg] or [reg+0] (no offset or offset 0)
        if re.search(r'\[e\w\w\+[1-9]', disasm):
            continue  # has non-zero displacement, not vfptr at +0
        if re.search(r'\[e\w\w\+0\]', disasm) or re.search(r'\[e\w\w\]', disasm):
            pass  # good: [reg] or [reg+0]
        elif '+' not in disasm.split(',')[0]:
            pass  # no + in first operand = [reg]
        else:
            continue

        vtable_addr = imm_val
        vtable_name = ida_name.get_name(vtable_addr) or ("off_%X" % vtable_addr)
        results.append({
            'insn_addr': "0x%08X" % head,
            'vtable_addr': "0x%08X" % vtable_addr,
            'vtable_name': vtable_name,
        })

    return results


def main():
    print("[*] Scanning all functions for vfptr assignments...")
    os.makedirs(LOG_DIR, exist_ok=True)

    assignments = {}  # vtable_addr -> [{'func_addr', 'func_name', 'insn_addr'}]
    total_funcs = 0
    found = 0

    for ea in idautils.Functions(TEXT_START, TEXT_END):
        total_funcs += 1
        func_name = ida_name.get_name(ea) or ("sub_%X" % ea)
        results = scan_function(ea)
        for r in results:
            vt_addr = r['vtable_addr']
            if vt_addr not in assignments:
                assignments[vt_addr] = []
            assignments[vt_addr].append({
                'func_addr': "0x%08X" % ea,
                'func_name': func_name,
                'insn_addr': r['insn_addr'],
                'vtable_name': r['vtable_name'],
            })
            found += 1

    print("[*] Scanned %d functions, found %d vfptr assignments for %d vtables" %
          (total_funcs, found, len(assignments)))

    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        json.dump(assignments, f, indent=2)
    print("[*] Output: %s" % OUTPUT_FILE)

    idc.qexit(0)


if __name__ == '__main__':
    main()
