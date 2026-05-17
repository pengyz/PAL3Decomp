#!/usr/bin/env python3
"""PAL3 反编译管线 CLI

用法:
  python pipeline/cli.py <command> [options]

命令:
  config              显示当前配置并验证路径
  init [--force]      初始化完整可用的 IDB (exe → raw → work → PDB → annotations)
  apply               重新应用 annotations 到已有 work IDB（标注变更后使用）
  export              导出 Hex-Rays 反编译 JSON（IDB → decomp/）
  check               校验 annotations 数据合法性
  codegen all         生成 headers + cpp
  codegen headers     只生成 .h
  codegen cpp         只生成 .cpp
  compile             CMake 配置 + ninja 编译 (-k 0 全量)

典型工作流:
  # 首次设置
  python pipeline/cli.py init
  python pipeline/cli.py export
  python pipeline/cli.py codegen all
  python pipeline/cli.py compile

  # 标注变更后
  python pipeline/cli.py apply
  python pipeline/cli.py export
  python pipeline/cli.py codegen all
  python pipeline/cli.py compile

  # 强制从零重建
  python pipeline/cli.py init --force

配置:
  pipeline.toml（gitignored，每环境独立）
  首次: cp pipeline.toml.example pipeline.toml && 编辑路径
"""
import sys
import os
import shutil
import subprocess
from pathlib import Path

_PIPELINE_DIR = os.path.dirname(os.path.abspath(__file__))
_PROJECT_DIR = os.path.dirname(_PIPELINE_DIR)
if _PIPELINE_DIR not in sys.path:
    sys.path.insert(0, _PIPELINE_DIR)
if _PROJECT_DIR not in sys.path:
    sys.path.insert(0, _PROJECT_DIR)

from pipeline.config import cfg


def _run_ida(script_name, idb_path):
    """Run an IDA script on the given IDB."""
    script = os.path.join(_PIPELINE_DIR, 'ida', script_name)
    if not os.path.exists(script):
        print("  [ERROR] Script not found: %s" % script)
        return False
    cmd = '"%s" -A -S"%s" "%s"' % (cfg.ida_path, script, idb_path)
    result = subprocess.run(cmd, shell=True)
    return result.returncode == 0


def _check_ida():
    if not Path(cfg.ida_path).exists():
        print("[ERROR] IDA not found: %s" % cfg.ida_path)
        print("  Fix [ida] path in pipeline.toml")
        sys.exit(1)


def cmd_config():
    """Print and validate configuration."""
    print("Pipeline Configuration (pipeline.toml)")
    print("=" * 55)
    print("  IDA:          %s" % cfg.ida_path)
    print("  Binary:       %s" % cfg.exe_path)
    print("  IDB (raw):    %s" % cfg.idb_raw)
    print("  IDB (work):   %s" % cfg.idb_work)
    print("  Annotations:  %s" % cfg.annotations_dir)
    print("  PDB:          %s" % cfg.pdb_dir)
    print("  Decomp:       %s" % cfg.decomp_dir)
    print("  Output src:   %s" % cfg.output_src)
    print("  Output .h:    %s" % cfg.output_headers)
    print("=" * 55)
    issues = []
    if not Path(cfg.ida_path).exists():
        issues.append("IDA not found: %s" % cfg.ida_path)
    if not cfg.exe_path.exists():
        issues.append("Binary not found: %s" % cfg.exe_path)
    if not cfg.annotations_dir.exists():
        issues.append("Annotations not found: %s" % cfg.annotations_dir)
    if not cfg.decomp_dir.exists():
        print("  [i] Decomp not found (run: pipeline/cli.py export)")
    if issues:
        for i in issues:
            print("  [!] %s" % i)
        sys.exit(1)
    else:
        print("  [OK] All paths valid")


def cmd_init(force=False):
    """Initialize a fully usable IDB (raw + PDB + annotations)."""
    _check_ida()
    if not cfg.exe_path.exists():
        print("[ERROR] Binary not found: %s" % cfg.exe_path)
        sys.exit(1)

    print("=" * 55)
    print("INIT%s" % (" --force (full rebuild)" if force else ""))
    print("=" * 55)

    # Step 1: Raw IDB
    print()
    if force and cfg.idb_raw.exists():
        cfg.idb_raw.unlink()
        print("[1/4] Raw IDB: DELETED, recreating...")
    if force and cfg.idb_work.exists():
        cfg.idb_work.unlink()
        print("      Work IDB: DELETED")

    if cfg.idb_raw.exists():
        print("[1/4] Raw IDB: EXISTS (%s)" % cfg.idb_raw.name)
    else:
        print("[1/4] Raw IDB: CREATING from %s ..." % cfg.exe_path.name)
        cmd = '"%s" -B "%s"' % (cfg.ida_path, cfg.exe_path)
        subprocess.run(cmd, shell=True)
        # IDA -B creates .i64 next to exe
        generated = cfg.exe_path.with_suffix('.i64')
        if generated.exists() and generated != cfg.idb_raw:
            shutil.move(str(generated), str(cfg.idb_raw))
        if cfg.idb_raw.exists():
            print("      -> CREATED: %s" % cfg.idb_raw.name)
        else:
            print("  [ERROR] IDA failed to create IDB")
            sys.exit(1)

    # Step 2: Work IDB (copy from raw)
    print()
    if cfg.idb_work.exists():
        print("[2/4] Work IDB: EXISTS, overwriting with fresh raw copy")
    else:
        print("[2/4] Work IDB: CREATING (copy from raw)")
    shutil.copy2(str(cfg.idb_raw), str(cfg.idb_work))
    print("      -> %s" % cfg.idb_work.name)

    # Step 3: Master pipeline (PDB + FLIRT)
    print()
    print("[3/4] Master pipeline: importing PDB types + FLIRT ...")
    ok = _run_ida('master_pipeline.py', cfg.idb_work)
    print("      -> %s" % ("OK" if ok else "WARN: non-zero exit"))

    # Step 4: Apply annotations
    print()
    print("[4/4] Apply annotations: importing from %s/ ..." % cfg.annotations_dir.name)
    ok = _run_ida('apply_annotations.py', cfg.idb_work)
    print("      -> %s" % ("OK" if ok else "WARN: non-zero exit"))

    # Done
    print()
    print("=" * 55)
    print("INIT COMPLETE. IDB is ready for export/codegen.")
    print()
    print("Next steps:")
    print("  python pipeline/cli.py export    # export decomp JSON")
    print("  python pipeline/cli.py codegen all")


def cmd_apply():
    """Re-apply annotations to existing work IDB."""
    _check_ida()
    if not cfg.idb_work.exists():
        print("[ERROR] Work IDB not found: %s" % cfg.idb_work)
        print("  Run 'python pipeline/cli.py init' first.")
        sys.exit(1)

    print("APPLY: updating annotations in %s ..." % cfg.idb_work.name)
    ok = _run_ida('apply_annotations.py', cfg.idb_work)
    if ok:
        print("-> OK: annotations applied")
    else:
        print("-> WARN: non-zero exit (check _logs/apply_status.json)")
    print()
    print("Next: python pipeline/cli.py export")


def cmd_export():
    """Export Hex-Rays decompilation to JSON."""
    _check_ida()
    if not cfg.idb_work.exists():
        print("[ERROR] Work IDB not found: %s" % cfg.idb_work)
        print("  Run 'python pipeline/cli.py init' first.")
        sys.exit(1)

    print("EXPORT: decompiling to %s/ ..." % cfg.decomp_dir.name)
    ok = _run_ida('export_full.py', cfg.idb_work)
    if ok:
        print("-> OK: decomp JSON exported")
    else:
        print("-> WARN: non-zero exit")
    print()
    print("Next: python pipeline/cli.py codegen all")


def cmd_check():
    """Run check_annotations.py."""
    script = os.path.join(_PIPELINE_DIR, 'check_annotations.py')
    result = subprocess.run([sys.executable, script])
    sys.exit(result.returncode)


def cmd_codegen(args):
    """Delegate to codegen.py."""
    script = os.path.join(_PIPELINE_DIR, 'gen', 'codegen.py')
    result = subprocess.run([sys.executable, script] + args)
    sys.exit(result.returncode)


def cmd_compile():
    """CMake configure (if needed) + ninja build with -k 0."""
    build_dir = Path(_PROJECT_DIR) / 'build'
    toolchain = Path(_PROJECT_DIR) / 'cmake' / 'toolchain-vc6.cmake'

    # Configure if build dir doesn't exist or has no build.ninja
    if not (build_dir / 'build.ninja').exists():
        print("COMPILE: configuring CMake ...")
        build_dir.mkdir(exist_ok=True)
        cmake_cmd = ['cmake', '-B', str(build_dir), '-G', 'Ninja',
                     '-DCMAKE_TOOLCHAIN_FILE=%s' % toolchain,
                     str(_PROJECT_DIR)]
        result = subprocess.run(cmake_cmd)
        if result.returncode != 0:
            print("[ERROR] CMake configure failed")
            sys.exit(1)
        print("-> CMake configured")
        print()

    # Build with -k 0 (continue on error, report all failures)
    print("COMPILE: building with ninja -k 0 ...")
    result = subprocess.run(['ninja', '-C', str(build_dir), '-k', '0'])

    # Count results
    print()
    if result.returncode == 0:
        print("-> BUILD SUCCESS: all files compiled")
    else:
        print("-> BUILD INCOMPLETE: some files failed (see errors above)")


def main():
    args = sys.argv[1:]
    if not args or args[0] in ('-h', '--help', 'help'):
        print(__doc__)
        sys.exit(0)

    command = args[0]

    if command == 'config':
        cmd_config()
    elif command == 'init':
        cmd_init(force='--force' in args)
    elif command == 'apply':
        cmd_apply()
    elif command == 'export':
        cmd_export()
    elif command == 'check':
        cmd_check()
    elif command == 'compile':
        cmd_compile()
    elif command == 'codegen':
        cmd_codegen(args[1:])
    else:
        print("Unknown command: %s" % command)
        print("Run with --help for usage.")
        sys.exit(1)


if __name__ == '__main__':
    main()
