#!/usr/bin/env python3
"""PAL3 反编译管线 CLI

用法:
  python pipeline/cli.py <command> [options]

命令:
  config              显示当前配置并验证路径
  init [--force]      初始化/更新 IDB（从 exe 生成 raw → copy work → 导入 PDB + annotations）
  check               校验 annotations 数据合法性
  codegen all         生成 headers + cpp
  codegen headers     只生成 .h
  codegen cpp         只生成 .cpp
  codegen cpp Class   只生成指定类

init 命令详解:
  不带 --force: 已有文件保留，只做数据合并导入
    - raw IDB 存在 → 跳过创建
    - work IDB 存在 → 直接在其上 apply（增量更新）
    - master_pipeline → 合并 PDB 类型（已有的不覆盖）
    - apply_annotations → 合并标注（增量）

  带 --force: 删除已有文件，从零重建
    - 删除 raw IDB 和 work IDB
    - 从 exe 重新生成 raw IDB
    - copy raw → work
    - 重新运行 master_pipeline + apply_annotations

配置:
  pipeline.toml（不跟踪 git，每环境独立）
  首次: cp pipeline.toml.example pipeline.toml && 编辑路径

IDA 脚本（需在 IDA 中运行，init 自动调用）:
  pipeline/ida/master_pipeline.py      初始化 IDB (PDB + FLIRT)
  pipeline/ida/apply_annotations.py    应用标注到 IDB
  pipeline/ida/export_full.py          导出 Hex-Rays 反编译 JSON
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
    """Run an IDA script on the given IDB. Returns True on success."""
    script = os.path.join(_PIPELINE_DIR, 'ida', script_name)
    if not os.path.exists(script):
        print("  [ERROR] Script not found: %s" % script)
        return False
    cmd = [cfg.ida_path, '-A', '-S"%s"' % script, str(idb_path)]
    # IDA needs the -S arg without shell quoting on Windows
    cmd = '"%s" -A -S"%s" "%s"' % (cfg.ida_path, script, idb_path)
    result = subprocess.run(cmd, shell=True, capture_output=True)
    return result.returncode == 0


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
        print("  [i] Decomp not found (run init + export first)")
    if issues:
        for i in issues:
            print("  [!] %s" % i)
        sys.exit(1)
    else:
        print("  [OK] All paths valid")


def cmd_init(force=False):
    """Initialize/update IDB with PDB + annotations."""
    print("=" * 55)
    print("Pipeline Init%s" % (" (--force: full rebuild)" if force else " (incremental update)"))
    print("=" * 55)

    # Validate prerequisites
    if not Path(cfg.ida_path).exists():
        print("[ERROR] IDA not found: %s" % cfg.ida_path)
        sys.exit(1)
    if not cfg.exe_path.exists():
        print("[ERROR] Binary not found: %s" % cfg.exe_path)
        sys.exit(1)

    # Step 1: Raw IDB
    print()
    if force and cfg.idb_raw.exists():
        cfg.idb_raw.unlink()
        print("[1/4] Raw IDB: DELETED existing, regenerating...")

    if cfg.idb_raw.exists():
        print("[1/4] Raw IDB: EXISTS, skipping creation")
    else:
        print("[1/4] Raw IDB: CREATING from %s ..." % cfg.exe_path.name)
        cmd = '"%s" -B "%s"' % (cfg.ida_path, cfg.exe_path)
        result = subprocess.run(cmd, shell=True, capture_output=True)
        # IDA -B creates .i64 next to exe, rename to raw
        generated = cfg.exe_path.with_suffix('.i64')
        if generated.exists():
            shutil.move(str(generated), str(cfg.idb_raw))
            print("         → CREATED: %s" % cfg.idb_raw)
        else:
            print("  [ERROR] IDA failed to create IDB")
            sys.exit(1)

    # Step 2: Work IDB
    print()
    if force and cfg.idb_work.exists():
        cfg.idb_work.unlink()
        print("[2/4] Work IDB: DELETED existing, copying from raw...")

    if cfg.idb_work.exists():
        if force:
            pass  # already deleted above
        else:
            print("[2/4] Work IDB: EXISTS, will update in-place")
    else:
        print("[2/4] Work IDB: CREATING (copy from raw)...")
        shutil.copy2(str(cfg.idb_raw), str(cfg.idb_work))
        print("         → CREATED: %s" % cfg.idb_work)

    # Step 3: Master pipeline (PDB + FLIRT)
    print()
    if cfg.idb_work.exists():
        action = "IMPORTING" if not force else "RE-IMPORTING"
        print("[3/4] Master pipeline: %s PDB types + FLIRT signatures..." % action)
        ok = _run_ida('master_pipeline.py', cfg.idb_work)
        if ok:
            print("         → OK: PDB types + FLIRT applied")
        else:
            print("  [WARN] master_pipeline returned non-zero (may still work)")

    # Step 4: Apply annotations
    print()
    action = "MERGING" if not force else "APPLYING"
    print("[4/4] Apply annotations: %s from %s ..." % (action, cfg.annotations_dir.name))
    ok = _run_ida('apply_annotations.py', cfg.idb_work)
    if ok:
        print("         → OK: annotations applied to IDB")
    else:
        print("  [WARN] apply_annotations returned non-zero (check _logs/apply_status.json)")

    # Summary
    print()
    print("=" * 55)
    if force:
        print("DONE: IDB rebuilt from scratch.")
    else:
        print("DONE: IDB updated with latest annotations.")
    print("Next: python pipeline/cli.py codegen all")
    print("  Or: $IDA -A -S\"pipeline/ida/export_full.py\" %s" % cfg.idb_work)


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


def main():
    args = sys.argv[1:]
    if not args or args[0] in ('-h', '--help', 'help'):
        print(__doc__)
        sys.exit(0)

    command = args[0]

    if command == 'config':
        cmd_config()
    elif command == 'init':
        force = '--force' in args
        cmd_init(force=force)
    elif command == 'check':
        cmd_check()
    elif command == 'codegen':
        cmd_codegen(args[1:])
    else:
        print("Unknown command: %s" % command)
        print("Run with --help for usage.")
        sys.exit(1)


if __name__ == '__main__':
    main()
