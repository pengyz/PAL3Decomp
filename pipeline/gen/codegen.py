#!/usr/bin/env python3
"""PAL3 code generator — pipeline architecture.

Usage:
  python codegen.py headers          # Generate .h files only
  python codegen.py cpp              # Generate .cpp files
  python codegen.py cpp ClassName    # Regenerate specific class only
  python codegen.py all              # headers + cpp
"""
import sys
import os

# Set up package path so all imports work regardless of how this is invoked
_GEN_DIR = os.path.dirname(os.path.abspath(__file__))
_PIPELINE_DIR = os.path.dirname(_GEN_DIR)
if _GEN_DIR not in sys.path:
    sys.path.insert(0, _GEN_DIR)
if _PIPELINE_DIR not in sys.path:
    sys.path.insert(0, _PIPELINE_DIR)

from data import store


def cmd_headers():
    """Generate header files from annotations."""
    from stages.emit_headers import run_header_generation
    run_header_generation()


def cmd_cpp(filter_classes=None):
    """Generate .cpp implementation files from decomp JSONs."""
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

    store.load()

    if command == 'headers':
        cmd_headers()
    elif command == 'cpp':
        cmd_cpp(filter_classes=filter_classes or None)
    elif command == 'all':
        cmd_headers()
        cmd_cpp(filter_classes=filter_classes or None)
    else:
        print("Unknown command: %s" % command)
        print("Use: headers, cpp, or all")
        sys.exit(1)


if __name__ == '__main__':
    main()
