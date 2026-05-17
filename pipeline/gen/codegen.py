#!/usr/bin/env python3
"""PAL3 code generator — pipeline architecture.

Usage:
  python codegen.py config            # Show current configuration
  python codegen.py headers           # Generate .h files only
  python codegen.py cpp               # Generate .cpp files
  python codegen.py cpp ClassName     # Regenerate specific class only
  python codegen.py all               # headers + cpp
"""
import sys
import os

# Set up package path so all imports work regardless of how this is invoked
_GEN_DIR = os.path.dirname(os.path.abspath(__file__))
_PIPELINE_DIR = os.path.dirname(_GEN_DIR)
_PROJECT_DIR = os.path.dirname(_PIPELINE_DIR)
if _GEN_DIR not in sys.path:
    sys.path.insert(0, _GEN_DIR)
if _PIPELINE_DIR not in sys.path:
    sys.path.insert(0, _PIPELINE_DIR)
if _PROJECT_DIR not in sys.path:
    sys.path.insert(0, _PROJECT_DIR)

from pipeline.config import cfg


def cmd_config():
    """Print current configuration."""
    print("Pipeline Configuration (from pipeline.toml)")
    print("=" * 50)
    print("  IDA path:       %s" % cfg.ida_path)
    print("  Binary (exe):   %s" % cfg.exe_path)
    print("  IDB (raw):      %s" % cfg.idb_raw)
    print("  IDB (work):     %s" % cfg.idb_work)
    print("  Annotations:    %s" % cfg.annotations_dir)
    print("  PDB:            %s" % cfg.pdb_dir)
    print("  Decomp:         %s" % cfg.decomp_dir)
    print("  Output src:     %s" % cfg.output_src)
    print("  Output headers: %s" % cfg.output_headers)
    print("=" * 50)
    # Validation
    ok = True
    from pathlib import Path
    if not Path(cfg.ida_path).exists():
        print("  [!] IDA not found")
        ok = False
    if not cfg.exe_path.exists():
        print("  [!] Binary not found")
        ok = False
    if not cfg.annotations_dir.exists():
        print("  [!] Annotations dir not found")
        ok = False
    if not cfg.decomp_dir.exists():
        print("  [!] Decomp dir not found (run IDA export first)")
    if ok:
        print("  [OK] All required paths exist")


def cmd_headers():
    """Generate header files from annotations."""
    from stages.emit_headers import run_header_generation
    run_header_generation()


def cmd_cpp(filter_classes=None):
    """Generate .cpp implementation files from decomp JSONs."""
    from data import store
    store.load()
    from stages.emit_cpp import run_cpp_generation
    run_cpp_generation(filter_classes=filter_classes)


def main():
    args = sys.argv[1:]
    if not args:
        print(__doc__)
        sys.exit(1)

    command = args[0]
    filter_classes = set()
    for arg in args[1:]:
        if not arg.startswith('-'):
            filter_classes.add(arg)

    if command == 'config':
        cmd_config()
    elif command == 'headers':
        cmd_headers()
    elif command == 'cpp':
        cmd_cpp(filter_classes=filter_classes or None)
    elif command == 'all':
        cmd_headers()
        cmd_cpp(filter_classes=filter_classes or None)
    else:
        print("Unknown command: %s" % command)
        print("Use: config, headers, cpp, or all")
        sys.exit(1)


if __name__ == '__main__':
    main()
