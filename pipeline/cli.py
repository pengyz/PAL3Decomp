#!/usr/bin/env python3
"""PAL3 反编译管线 CLI

用法:
  python pipeline/cli.py <command> [options]

命令:
  config              显示当前配置并验证路径
  config --set K=V    设置配置项（如: config --set ida.path="D:\\IDA\\idat.exe"）
  init [--force]      初始化完整可用的 IDB (exe → raw → work → PDB → annotations)
  apply               重新应用 annotations 到已有 work IDB（标注变更后使用）
  export              导出 Hex-Rays 反编译 JSON（IDB → decomp/）
  check               校验 annotations 数据合法性
  codegen all         生成 headers + cpp
  codegen headers     只生成 .h
  codegen cpp         只生成 .cpp
  compile             CMake 配置 + ninja 编译 (-k 0 全量)
  iterate [opts]      自动迭代引擎（annotation 修正直到收敛）
  tool --list         列出所有可用工具脚本
  tool <name> [args]  运行 tools/ 下的脚本

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


def _config_set(args):
    """Set a config value in pipeline.toml."""
    toml_path = Path(_PROJECT_DIR) / 'pipeline.toml'
    example_path = Path(_PROJECT_DIR) / 'pipeline.toml.example'

    # Create from example if not exists
    if not toml_path.exists():
        if example_path.exists():
            shutil.copy2(str(example_path), str(toml_path))
            print("Created pipeline.toml from example")
        else:
            # Write minimal template
            toml_path.write_text(
                '[ida]\npath = ""\n\n[binary]\nexe = "original/PAL3.exe"\n'
                'idb_raw = "original/PAL3.exe.raw.i64"\nidb_work = "original/PAL3.exe.i64"\n\n'
                '[paths]\nannotations = "data/annotations"\npdb = "data/pdb"\n'
                'decomp = "asm/pal3/decomp"\noutput_src = "src/pal3"\n'
                'output_headers = "include/pal3/gen"\n', encoding='utf-8')
            print("Created pipeline.toml with defaults")

    if not args:
        print("[ERROR] Usage: config --set section.key=value")
        print("  Examples:")
        print('    config --set ida.path="D:\\\\Program Files\\\\IDA Professional 9.2\\\\idat.exe"')
        print('    config --set binary.exe="original/PAL3.exe"')
        sys.exit(1)

    for arg in args:
        if '=' not in arg:
            print("[ERROR] Invalid format: %s (expected section.key=value)" % arg)
            sys.exit(1)
        key, value = arg.split('=', 1)
        value = value.strip('"').strip("'")

        if '.' not in key:
            print("[ERROR] Key must be section.key format (e.g., ida.path)")
            sys.exit(1)

        section, field = key.split('.', 1)
        # Escape backslashes for TOML string
        value = value.replace('\\', '\\\\')

        # Read, modify, write toml
        content = toml_path.read_text(encoding='utf-8')
        lines = content.split('\n')
        in_section = False
        found = False
        for i, line in enumerate(lines):
            if line.strip() == '[%s]' % section:
                in_section = True
                continue
            if in_section:
                if line.strip().startswith('['):
                    # New section started, insert before it
                    lines.insert(i, '%s = "%s"' % (field, value))
                    found = True
                    break
                if line.strip().startswith(field + ' ') or line.strip().startswith(field + '='):
                    lines[i] = '%s = "%s"' % (field, value)
                    found = True
                    break

        if not found:
            # Append to end of file (or end of section)
            if in_section:
                lines.append('%s = "%s"' % (field, value))
            else:
                lines.append('')
                lines.append('[%s]' % section)
                lines.append('%s = "%s"' % (field, value))

        toml_path.write_text('\n'.join(lines), encoding='utf-8')
        print("Set %s.%s = %s" % (section, field, value))

    print()
    print("Config saved to: %s" % toml_path)


def _run_ida(script_name, idb_path, env=None):
    """Run an IDA script on the given IDB."""
    script = os.path.join(_PIPELINE_DIR, 'ida', script_name)
    if not os.path.exists(script):
        print("  [ERROR] Script not found: %s" % script)
        return False
    cmd = '"%s" -A -S"%s" "%s"' % (cfg.ida_path, script, idb_path)
    result = subprocess.run(cmd, shell=True, env=env)
    return result.returncode == 0


def _check_ida():
    if not Path(cfg.ida_path).exists():
        print("[ERROR] IDA not found: %s" % cfg.ida_path)
        print("  Fix [ida] path in pipeline.toml")
        sys.exit(1)


def cmd_config(args=None):
    """Print, validate, or set configuration."""
    args = args or []

    # config --set key=value
    if args and args[0] == '--set':
        _config_set(args[1:])
        return

    print("Pipeline Configuration (%s)" % (Path(_PROJECT_DIR) / 'pipeline.toml'))
    print("=" * 60)

    checks = [
        ("ida.path", cfg.ida_path, Path(cfg.ida_path).exists(),
         "IDA Pro 可执行文件 (idat.exe / idat64.exe)",
         'config --set ida.path="<IDA安装路径>/idat.exe"'),
        ("binary.exe", str(cfg.exe_path), cfg.exe_path.exists(),
         "待反编译的目标二进制",
         'config --set binary.exe="original/PAL3.exe"'),
        ("binary.idb_raw", str(cfg.idb_raw), cfg.idb_raw.exists(),
         "原始 IDB (init 自动生成，无需手动设置)",
         None),
        ("binary.idb_work", str(cfg.idb_work), cfg.idb_work.exists(),
         "工作 IDB (init 自动生成，无需手动设置)",
         None),
        ("paths.annotations", str(cfg.annotations_dir), cfg.annotations_dir.exists(),
         "标注数据目录 (structs/, functions.json 等)",
         'config --set paths.annotations="data/annotations"'),
        ("paths.pdb", str(cfg.pdb_dir), cfg.pdb_dir.exists(),
         "PDB 导出数据 (PAL3A 参考)",
         None),
        ("paths.decomp", str(cfg.decomp_dir), cfg.decomp_dir.exists(),
         "Hex-Rays 反编译 JSON (export 生成)",
         None),
        ("paths.output_src", str(cfg.output_src), cfg.output_src.exists(),
         "生成的 .cpp 输出目录",
         None),
        ("paths.output_headers", str(cfg.output_headers), cfg.output_headers.exists(),
         "生成的 .h 输出目录",
         None),
    ]

    has_error = False
    for key, value, exists, desc, fix_cmd in checks:
        status = "OK" if exists else "MISSING"
        icon = "[+]" if exists else "[!]"
        print("  %s %-22s = %s" % (icon, key, value))
        if not exists:
            print("      %s" % desc)
            if fix_cmd:
                print("      Fix: python pipeline/cli.py %s" % fix_cmd)
                has_error = True
            else:
                print("      (auto-generated by pipeline commands)")

    print("=" * 60)
    if has_error:
        print()
        print("REQUIRED ACTIONS:")
        print("  Fix the [!] items above, then run: python pipeline/cli.py config")
        sys.exit(1)
    else:
        print("  All required configurations OK.")


def cmd_init(force=False):
    """Initialize a fully usable IDB (raw + PDB + annotations)."""
    _check_ida()
    if not cfg.exe_path.exists():
        print("[ERROR] Binary not found: %s" % cfg.exe_path)
        print("  Place PAL3.exe at the path configured in pipeline.toml [binary] exe")
        print("  Current: %s" % cfg.exe_path)
        sys.exit(1)
    if not cfg.annotations_dir.exists():
        print("[ERROR] Annotations not found: %s" % cfg.annotations_dir)
        print("  Ensure data/annotations/ exists with structs/, functions.json, etc.")
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
        # IDA -B creates .i64 next to exe: PAL3.exe → PAL3.exe.i64
        # Note: Path.with_suffix('.i64') on 'PAL3.exe' gives 'PAL3.i64' (wrong!)
        # IDA appends .i64 to the full filename including .exe
        generated = Path(str(cfg.exe_path) + '.i64')
        if generated.exists() and generated != cfg.idb_raw:
            shutil.move(str(generated), str(cfg.idb_raw))
        if cfg.idb_raw.exists():
            print("      -> CREATED: %s" % cfg.idb_raw.name)
        else:
            print("  [ERROR] IDA failed to create IDB")
            print("  Expected: %s" % generated)
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


def cmd_export(fast=False):
    """Export Hex-Rays decompilation to JSON."""
    _check_ida()
    if not cfg.idb_work.exists():
        print("[ERROR] Work IDB not found: %s" % cfg.idb_work)
        print("  Run 'python pipeline/cli.py init' first.")
        sys.exit(1)

    env = None
    if fast:
        env = dict(os.environ, PAL3_EXPORT_NO_REFRESH="1")
        print("EXPORT (fast, no refresh): decompiling to %s/ ..." % cfg.decomp_dir.name)
    else:
        print("EXPORT: decompiling to %s/ ..." % cfg.decomp_dir.name)
    ok = _run_ida('export_full.py', cfg.idb_work, env=env)
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
    if not args:
        print("[ERROR] codegen requires a subcommand: all, headers, or cpp")
        print("  python pipeline/cli.py codegen all")
        sys.exit(1)

    # Check decomp exists for cpp generation
    if args[0] in ('all', 'cpp'):
        if not cfg.decomp_dir.exists() or not any(cfg.decomp_dir.glob('*.json')):
            print("[ERROR] Decomp JSON not found in: %s" % cfg.decomp_dir)
            print("  Run 'python pipeline/cli.py export' first.")
            print("  (Requires initialized IDB: 'python pipeline/cli.py init')")
            sys.exit(1)

    script = os.path.join(_PIPELINE_DIR, 'gen', 'codegen.py')
    result = subprocess.run([sys.executable, script] + args)
    if result.returncode != 0:
        sys.exit(result.returncode)

    # Auto-snapshot after 'codegen all'
    if args[0] == 'all' and '--no-snapshot' not in args:
        print("\n[Snapshot] Capturing compile baseline...")
        snap_script = os.path.join(_PIPELINE_DIR, 'snapshots', 'snapshot.py')
        subprocess.run([sys.executable, snap_script, 'capture'])


def _get_script_info(path):
    """Extract description and usage from script's module docstring."""
    import ast
    try:
        tree = ast.parse(open(path, encoding='utf-8').read())
        doc = ast.get_docstring(tree)
    except Exception:
        return '', ''
    if not doc:
        return '', ''
    lines = doc.strip().split('\n')
    desc = lines[0].strip()
    # Extract usage section if present
    usage = ''
    in_usage = False
    for line in lines[1:]:
        if line.strip().lower().startswith('usage'):
            in_usage = True
            continue
        if in_usage:
            if line.strip() and not line.startswith(' '):
                break
            if line.strip():
                usage += line.strip() + '\n'
    return desc, usage.strip()


def cmd_tool(args):
    """List or run tools/ scripts."""
    tools_dir = Path(_PROJECT_DIR) / 'tools'
    scripts = sorted([f[:-3] for f in os.listdir(tools_dir)
                      if f.endswith('.py') and not f.startswith('_')])

    if not args or args[0] == '--list':
        print("Available tools (%d):" % len(scripts))
        print()
        for name in scripts:
            path = tools_dir / ('%s.py' % name)
            desc, _ = _get_script_info(str(path))
            print("  %-28s %s" % (name, desc[:50]))
        print()
        print("Usage: python pipeline/cli.py tool <name> [args...]")
        print("  Add --help after tool name for detailed usage.")
        return

    if len(args) >= 2 and args[1] == '--help':
        # Show detailed info for specific tool
        name = args[0]
        path = tools_dir / ('%s.py' % name)
        if not path.exists():
            print("[ERROR] Tool not found: %s" % name)
            sys.exit(1)
        desc, usage = _get_script_info(str(path))
        print("Tool: %s" % name)
        print("  %s" % desc)
        if usage:
            print()
            print("Usage:")
            for line in usage.split('\n'):
                print("  %s" % line)
        return

    name = args[0]
    script_path = tools_dir / ('%s.py' % name)
    if not script_path.exists():
        print("[ERROR] Tool not found: %s" % name)
        print("  Run 'python pipeline/cli.py tool --list' to see available tools.")
        sys.exit(1)

    # Run with project root as cwd, inject pipeline.config access
    env = os.environ.copy()
    env['PYTHONPATH'] = _PROJECT_DIR + os.pathsep + env.get('PYTHONPATH', '')
    result = subprocess.run(
        [sys.executable, str(script_path)] + args[1:],
        cwd=_PROJECT_DIR, env=env)
    sys.exit(result.returncode)


def cmd_compile():
    """CMake configure (if needed) + ninja build with -k 0."""
    build_dir = Path(_PROJECT_DIR) / 'build'
    toolchain = Path(_PROJECT_DIR) / 'cmake' / 'toolchain-vc6.cmake'

    # Check source files exist
    src_dir = cfg.output_src
    if not src_dir.exists() or not any(src_dir.rglob('*.cpp')):
        print("[ERROR] No .cpp source files found in: %s" % src_dir)
        print("  Run 'python pipeline/cli.py codegen all' first.")
        print("  (Requires decomp JSON: 'python pipeline/cli.py export')")
        sys.exit(1)

    # Check toolchain
    if not toolchain.exists():
        print("[ERROR] VC6 toolchain not found: %s" % toolchain)
        sys.exit(1)

    # Check cmake and ninja available
    if shutil.which('cmake') is None:
        print("[ERROR] cmake not found in PATH")
        sys.exit(1)
    if shutil.which('ninja') is None:
        print("[ERROR] ninja not found in PATH")
        sys.exit(1)

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
        print("  Fix annotations or codegen, then re-run:")
        print("  python pipeline/cli.py compile")


def main():
    args = sys.argv[1:]
    if not args or args[0] in ('-h', '--help', 'help'):
        print(__doc__)
        sys.exit(0)

    command = args[0]

    if command == 'config':
        cmd_config(args[1:])
    elif command == 'init':
        cmd_init(force='--force' in args)
    elif command == 'apply':
        cmd_apply()
    elif command == 'export':
        cmd_export(fast='--fast' in args)
    elif command == 'check':
        cmd_check()
    elif command == 'compile':
        cmd_compile()
    elif command == 'codegen':
        cmd_codegen(args[1:])
    elif command == 'snapshot':
        snap_script = os.path.join(_PIPELINE_DIR, 'snapshots', 'snapshot.py')
        sub = args[1] if len(args) > 1 else 'list'
        subprocess.run([sys.executable, snap_script, sub])
    elif command == 'tool':
        cmd_tool(args[1:])
    elif command == 'iterate':
        from pipeline.iterate import main as iterate_main
        sys.argv = ['iterate'] + args[1:]
        iterate_main()
    else:
        print("Unknown command: %s" % command)
        print("Run with --help for usage.")
        sys.exit(1)


if __name__ == '__main__':
    main()
