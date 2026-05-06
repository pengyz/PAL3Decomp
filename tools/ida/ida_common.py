"""
IDAPython Shared Constants and Utilities Module

Provides common constants, paths, and utility functions used by all
scripts in the PAL3A IDA quality fix pipeline.

PE Section Ranges (post-unpack):
  .text  = 0x401000 - 0x569018
  .rdata = 0x56A000 - 0x57F1F2
  .data  = 0x580000 - 0x60C000
"""

import os
import ida_bytes
import ida_funcs
import ida_hexrays
import ida_name

# ============================================================================
# Directory Paths
# ============================================================================

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

# ============================================================================
# File Paths
# ============================================================================

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
DIAGNOSIS_REPORT = os.path.join(LOG_DIR, "diagnosis_report.json")

# ============================================================================
# PE Section Ranges (post-unpack PAL3A.exe)
# ============================================================================

TEXT_START = 0x00401000
TEXT_END = 0x00569018

RDATA_START = 0x0056A000
RDATA_END = 0x0057F1F2

DATA_START = 0x00580000
DATA_END = 0x0060C000

# ============================================================================
# Confidence Thresholds
# ============================================================================

CONF_AUTO_FIX = 0.8
CONF_MANUAL_REVIEW = 0.5

# ============================================================================
# Utility Functions
# ============================================================================


def is_in_text(addr):
    """Check if address is in .text section"""
    return TEXT_START <= addr < TEXT_END


def is_in_pe(addr):
    """Check if address is in any PE section (.text, .rdata, or .data)"""
    if TEXT_START <= addr < TEXT_END:
        return True
    if RDATA_START <= addr < RDATA_END:
        return True
    if DATA_START <= addr < DATA_END:
        return True
    return False


def is_valid_split_point(addr):
    """
    Check if addr is a valid function split point.

    Returns:
        (bool, evidence_string): (is_valid, description)

    Valid if bytes before addr contain:
      - ret (0xC3)
      - retn (0xC2 xx xx)
      - jmp rel32 (0xE9 xx xx xx xx)
      - jmp rel8 (0xEB xx)
      - int3 (0xCC)
      - nop (0x90)

    AND addr itself starts with function prologue patterns:
      - push ebp; mov ebp,esp (55 8B EC)
      - sub esp (83 EC)
      - push reg (50-57)
    """
    evidence = []

    # Check bytes before addr for termination/padding
    prev_byte = ida_bytes.get_byte(addr - 1) if addr >= 1 else None
    prev2_byte = ida_bytes.get_byte(addr - 2) if addr >= 2 else None
    prev3_byte = ida_bytes.get_byte(addr - 3) if addr >= 3 else None
    prev5_byte = ida_bytes.get_byte(addr - 5) if addr >= 5 else None

    has_terminator = False

    if prev_byte == 0xC3:
        evidence.append("ret (0xC3)")
        has_terminator = True
    elif prev3_byte == 0xC2:
        evidence.append("retn (0xC2 xx xx)")
        has_terminator = True
    elif prev5_byte == 0xE9:
        evidence.append("jmp rel32 (0xE9)")
        has_terminator = True
    elif prev2_byte == 0xEB:
        evidence.append("jmp rel8 (0xEB xx)")
        has_terminator = True
    elif prev_byte == 0xCC:
        evidence.append("int3 (0xCC)")
        has_terminator = True
    elif prev_byte == 0x90:
        evidence.append("nop (0x90)")
        has_terminator = True

    if not has_terminator:
        return (False, "No terminator/padding before address")

    # Check addr itself for function prologue patterns
    byte0 = ida_bytes.get_byte(addr)
    byte1 = ida_bytes.get_byte(addr + 1) if addr + 1 < TEXT_END else None
    byte2 = ida_bytes.get_byte(addr + 2) if addr + 2 < TEXT_END else None

    has_prologue = False
    prologue_type = ""

    # push ebp; mov ebp,esp (55 8B EC)
    if byte0 == 0x55 and byte1 == 0x8B and byte2 == 0xEC:
        has_prologue = True
        prologue_type = "push ebp; mov ebp,esp"
    # sub esp (83 EC ...)
    elif byte0 == 0x83 and byte1 == 0xEC:
        has_prologue = True
        prologue_type = "sub esp"
    # push reg (50-57 = push eax/ecx/edx/ebx/esp/ebp/esi/edi)
    elif 0x50 <= byte0 <= 0x57:
        has_prologue = True
        prologue_type = "push reg"

    if not has_prologue:
        return (False, ", ".join(evidence) + " [but no prologue at addr]")

    evidence_str = ", ".join(evidence) + f"; prologue: {prologue_type}"
    return (True, evidence_str)


def get_func_decompilation(addr):
    """
    Attempt to decompile function at addr using Hex-Rays.

    Args:
        addr: Function address

    Returns:
        str: Decompiled pseudocode, or None if decompilation failed
    """
    try:
        func = ida_funcs.get_func(addr)
        if not func:
            return None

        cfunc = ida_hexrays.decompile(addr)
        if cfunc:
            return str(cfunc)
        return None
    except Exception:
        return None


def make_logger(log_file_path):
    """
    Create a logging system for scripts.

    Args:
        log_file_path: Path to write log file to

    Returns:
        (log_func, save_func, lines_list):
          - log_func(msg): Print and buffer message
          - save_func(): Write buffered lines to file
          - lines_list: List being accumulated
    """
    lines = []

    def log_func(msg):
        msg_str = str(msg)
        lines.append(msg_str)
        print(msg_str)

    def save_func():
        os.makedirs(os.path.dirname(log_file_path), exist_ok=True)
        with open(log_file_path, "w", encoding="utf-8") as f:
            f.write("\n".join(lines))

    return (log_func, save_func, lines)
