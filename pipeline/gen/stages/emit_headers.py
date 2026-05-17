"""Header file generation stage.

Delegates to the existing gen_headers.py logic (to be refactored later).
"""
import sys
import os


def run_header_generation():
    """Generate include/pal3/gen/*.h from annotations."""
    # Reuse existing gen_headers.py logic directly
    gen_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    sys.path.insert(0, gen_dir)

    # Import and run the existing gen_headers main
    import gen_headers
    gen_headers.main()
