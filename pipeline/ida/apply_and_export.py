"""
Combined: apply annotations + export decomp in one IDA run.

Usage:
  idat.exe -A -S"pipeline/ida/apply_and_export.py" original/PAL3.exe.i64
"""
import sys, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, SCRIPT_DIR)

# Step 1: apply annotations
import apply_annotations

# Step 2: export decomp
import export_full
