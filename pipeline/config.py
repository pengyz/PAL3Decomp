"""Pipeline configuration loader.

Reads pipeline.toml from project root. All scripts use this module
to get paths instead of hardcoding.

Usage:
    from pipeline.config import cfg
    print(cfg.ida_path)
    print(cfg.exe_path)

If pipeline.toml is missing or invalid, raises ConfigError with
a clear message that an LLM can act on to help fix the config.
"""
import os
import sys
from pathlib import Path

try:
    import tomllib
except ImportError:
    try:
        import tomli as tomllib
    except ImportError:
        tomllib = None


class ConfigError(Exception):
    """Raised when pipeline.toml is missing, malformed, or has invalid paths."""
    pass


def _find_project_root():
    d = Path(__file__).resolve().parent.parent
    while d != d.parent:
        if (d / 'pipeline.toml').exists():
            return d
        d = d.parent
    return Path(__file__).resolve().parent.parent


PROJECT_ROOT = _find_project_root()
_TOML_PATH = PROJECT_ROOT / 'pipeline.toml'


class Config:
    def __init__(self):
        # Check toml parser available
        if tomllib is None:
            raise ConfigError(
                "No TOML parser available. Install tomli: pip install tomli\n"
                "(Python 3.11+ has built-in tomllib, older versions need tomli)")

        # Check pipeline.toml exists
        if not _TOML_PATH.exists():
            raise ConfigError(
                "pipeline.toml not found at: %s\n\n"
                "This file is gitignored by design (per-environment paths).\n"
                "Quickest fix (template is tracked):\n"
                "    cp pipeline.toml.example pipeline.toml\n"
                "  then edit the [ida] path / [binary] paths for this machine.\n\n"
                "Or create it with the following content:\n\n"
                "[ida]\n"
                'path = "D:\\\\Program Files\\\\IDA Professional 9.2\\\\idat.exe"\n\n'
                "[binary]\n"
                'exe = "original/PAL3.exe"\n'
                'idb_raw = "original/PAL3.exe.raw.i64"\n'
                'idb_work = "original/PAL3.exe.i64"\n\n'
                "[paths]\n"
                'annotations = "data/annotations"\n'
                'pdb = "data/pdb"\n'
                'decomp = "asm/pal3/decomp"\n'
                'output_src = "src/pal3"\n'
                'output_headers = "include/pal3/gen"\n'
                % _TOML_PATH)

        # Parse
        try:
            with open(_TOML_PATH, 'rb') as f:
                data = tomllib.load(f)
        except Exception as e:
            raise ConfigError(
                "pipeline.toml parse error: %s\n"
                "File: %s\n"
                "Fix the TOML syntax and retry." % (e, _TOML_PATH))

        # Extract sections
        ida = data.get('ida', {})
        binary = data.get('binary', {})
        paths = data.get('paths', {})

        # Validate required fields
        errors = []
        if not ida.get('path'):
            errors.append("[ida] path is required (path to idat.exe)")
        if not binary.get('exe'):
            errors.append("[binary] exe is required (path to PAL3.exe)")

        if errors:
            raise ConfigError(
                "pipeline.toml validation failed:\n  " +
                "\n  ".join(errors) +
                "\n\nFile: %s" % _TOML_PATH)

        # Resolve paths
        self.ida_path = ida['path']
        self.exe_path = PROJECT_ROOT / binary.get('exe', 'original/PAL3.exe')
        self.idb_raw = PROJECT_ROOT / binary.get('idb_raw', 'original/PAL3.exe.raw.i64')
        self.idb_work = PROJECT_ROOT / binary.get('idb_work', 'original/PAL3.exe.i64')
        self.annotations_dir = PROJECT_ROOT / paths.get('annotations', 'data/annotations')
        self.pdb_dir = PROJECT_ROOT / paths.get('pdb', 'data/pdb')
        self.decomp_dir = PROJECT_ROOT / paths.get('decomp', 'asm/pal3/decomp')
        self.output_src = PROJECT_ROOT / paths.get('output_src', 'pal3/src')
        self.output_headers = PROJECT_ROOT / paths.get('output_headers', 'pal3/src')

        # Validate paths exist
        warnings = []
        if not Path(self.ida_path).exists():
            warnings.append("IDA not found: %s" % self.ida_path)
        if not self.exe_path.exists():
            warnings.append("Binary not found: %s" % self.exe_path)
        if not self.annotations_dir.exists():
            warnings.append("Annotations dir not found: %s" % self.annotations_dir)

        if warnings:
            print("[config] WARNING:", file=sys.stderr)
            for w in warnings:
                print("  %s" % w, file=sys.stderr)


try:
    cfg = Config()
except ConfigError as e:
    print("=" * 60, file=sys.stderr)
    print("PIPELINE CONFIG ERROR", file=sys.stderr)
    print("=" * 60, file=sys.stderr)
    print(str(e), file=sys.stderr)
    print("=" * 60, file=sys.stderr)
    sys.exit(1)
