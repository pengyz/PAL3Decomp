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
  probe [s1|s2|all]   S1/S2 probe 编译普查 + 自动回归对账（vs latest 基线）
  match               S4 字节匹配裁判（假设旗标组 + L1 棘轮检查）
  iterate [opts]      不可用（pipeline/iterate.py 不存在；会明确报错并退出 2）
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
    _env = dict(os.environ)
    _env['TVHEADLESS'] = '1'
    if env:
        _env.update(env)
    result = subprocess.run(cmd, shell=True, env=_env)
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
         "源码根目录（生成代码在 gen/ 子目录下）",
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
    ok_master = _run_ida('master_pipeline.py', cfg.idb_work)
    print("      -> %s" % ("OK" if ok_master else "WARN: non-zero exit"))

    # Step 4: Apply annotations
    print()
    print("[4/4] Apply annotations: importing from %s/ ..." % cfg.annotations_dir.name)
    ok = _run_ida('apply_annotations.py', cfg.idb_work)
    print("      -> %s" % ("OK" if ok else "WARN: non-zero exit"))

    # Step 5: Fix vtable types (post-processing)
    print("[5/5] Fix vtable types: setting __cppobj and typed vtable pointers ...")
    vtok = _run_ida('fix_vtable_types.py', cfg.idb_work)
    print("      -> %s" % ("OK" if vtok else "WARN: non-zero exit"))

    # Done
    print()
    print("=" * 55)
    if not (ok_master and ok and vtok):
        # Same defect class as cmd_apply: this used to print "INIT COMPLETE.
        # IDB is ready" even after a failed step, so export/codegen/match ran
        # against a half-built IDB and the numbers looked plausible.
        failed = [name for name, good in (('master_pipeline.py', ok_master),
                                          ('apply_annotations.py', ok),
                                          ('fix_vtable_types.py', vtok)) if not good]
        print("INIT INCOMPLETE - failed step(s): %s" % ", ".join(failed))
        print("The IDB is NOT ready; fix the failure and re-run 'init' (or the")
        print("individual step) before export/codegen/match.")
        print("=" * 55)
        sys.exit(1)
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
    vtok = _run_ida('fix_vtable_types.py', cfg.idb_work)
    if not ok:
        # 'apply' is the first link of the `apply && export && codegen all &&
        # probe all && match` gate chain. Returning 0 here made a FAILED apply
        # look like success, so the chain kept running against a half-updated
        # IDB and produced plausible-but-wrong baselines.
        print()
        print("-> ERROR: apply FAILED (apply_annotations.py exited non-zero).")
        print("   Check pipeline/ida/_logs/apply_annotations_log.txt ([3] Structs line).")
        print("   NOTE: _logs/apply_status.json is written by a separate script")
        print("   (pipeline/ida/check_apply_status.py) and can be a stale value.")
        print("   Refusing to report success; the gate chain stops here.")
        sys.exit(1)
    print("-> OK: annotations applied")
    if not vtok:
        print("-> [WARN] fix_vtable_types.py exited non-zero: vtable pointer types in the")
        print("   IDB may be stale. Do not trust export/codegen/match output before")
        print("   re-running apply and verifying.")
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
        # R5（2026-09-15 独立复核）：原先此处只打 WARN，**恒 exit 0**，
        # 使 `apply && export && codegen` 链对 export 完全失效。
        # export 失败必须让链停下：decomp 是 codegen 的唯一输入，
        # 用它继续生成会产出一份与 IDB 不符的源码（且看起来一切正常）。
        print("-> ERROR: export FAILED (export_full.py exited non-zero).")
        print("   The decomp JSON is stale/incomplete; codegen would produce source "
              "that does not match the IDB. Stopping the chain here.")
        sys.exit(1)
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
        snap = subprocess.run([sys.executable, snap_script, 'capture'])
        if snap.returncode != 0:
            print("[ERROR] snapshot capture failed (exit %d) -- not swallowing it; "
                  "'codegen all' fails." % snap.returncode)
            sys.exit(snap.returncode if snap.returncode > 0 else 1)

        # Auto-run regression detection
        tools_dir = os.path.join(_PROJECT_DIR, 'tools')

        # Generated-source lint：形参名不得为纯数字。
        # 缘起（2026-09-15 独立复核 M1）：stage5 的 H 块曾把普通函数的形参名替换成常量，
        # 产出 `int CEffCylinder::Update(int 1)` —— **语义损坏**（不只是语法错）。
        # 受害文件本来就全是 fail，故 compile_regression（只比 ok/fail）**发现不了**；
        # 更糟的是解析崩塌让 error_count **下降**，度量反而变好看。
        # 放在回归检测**之前**：源码正确性优先于编译 ok/fail 统计。
        lint_script = os.path.join(tools_dir, 'codegen_param_lint.py')
        if os.path.exists(lint_script):
            print("\n[Lint] Checking generated source for numeric parameter names...")
            lint = subprocess.run([sys.executable, lint_script, '--quiet'])
            if lint.returncode != 0:
                print("[ERROR] codegen_param_lint.py exited %d — generated source has "
                      "numeric parameter names (semantic corruption, not style)."
                      % lint.returncode)
                sys.exit(lint.returncode if lint.returncode > 0 else 1)

        regression_script = os.path.join(tools_dir, 'compile_regression.py')
        if os.path.exists(regression_script):
            print("\n[Regression] Checking for compile regressions...")
            reg = subprocess.run([sys.executable, regression_script])
            if reg.returncode != 0:
                # Propagate instead of silently discarding: a regression (or a
                # frozen baseline) must break the `&&` chain, not scroll past.
                print("[ERROR] compile_regression.py exited %d." % reg.returncode)
                print("        If the ratchet baseline is stale, refresh it deliberately with")
                print("        'python3 tools/compile_regression.py --update-baseline' after")
                print("        confirming there is no real regression.")
                sys.exit(reg.returncode if reg.returncode > 0 else 1)


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


def cmd_match():
    """S4 byte-match referee: compile S2-green units with the calibrated
    hypothesis flags and diff function bytes against PAL3.exe .text.
    L1 (perfect match) count is the ratchet: it must never regress."""
    import json
    s4 = Path('data/status/s4_baseline.json')
    prev_l1 = 0
    prev_text = None
    if s4.exists():
        try:
            prev_text = s4.read_text(encoding='utf-8')
            prev_l1 = json.loads(prev_text).get('stats', {}).get('match_L1', 0)
        except (json.JSONDecodeError, OSError):
            pass
    script = os.path.join(_PIPELINE_DIR, 'compare_pal3.py')
    flags = "/nologo /TP /c /W3 /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MD /Gd"
    rc = subprocess.run([sys.executable, script, '--flags', flags]).returncode

    # R1（2026-09-15 独立复核 M2-a）：
    # 原先这里**捕获 rc 后从未使用**，且函数没有任何 sys.exit ⇒ `match` 恒 exit 0。
    # 连 compare_pal3.py 的前置守卫（census 缺失时 sys.exit(2)）也被一并吞掉。
    # 现在：非零即传出（`match` 是验收硬线之一，不能恒报成功）。
    if rc != 0:
        print()
        print("[ERROR] compare_pal3.py exited %d — the byte-match referee did not "
              "complete (e.g. missing probe_census.json). Stopping." % rc)
        sys.exit(rc if rc > 0 else 1)

    if s4.exists():
        try:
            cur_l1 = json.loads(s4.read_text(encoding='utf-8')).get('stats', {}).get('match_L1', 0)
            print()
            print("[L1 ratchet] previous %d -> current %d" % (prev_l1, cur_l1))
            if cur_l1 < prev_l1:
                # 棘轮失忆修复（同 R1）：compare_pal3.py 在**脚本结尾**才覆盖
                # s4_baseline.json，而棘轮判断在它之后 ⇒ 若不把旧内容写回，
                # 下一轮 prev_l1 读到的就是**退化后**的值，棘轮永久滑落、不再报警。
                # 故：失败时把旧基线写回，使基线**只能显式前进**
                # （与 tools/compile_regression.py 的 `--update-baseline` 语义一致）。
                if prev_text is not None:
                    try:
                        s4.write_text(prev_text, encoding='utf-8')
                        print("[L1 ratchet] baseline restored to previous value "
                              "(ratchet may only advance explicitly)")
                    except OSError as e:
                        print("[L1 ratchet] WARN: could not restore baseline: %s" % e)
                print("[L1 ratchet] REGRESSION: byte-perfect functions lost — "
                      "investigate before committing")
                sys.exit(1)
        except (json.JSONDecodeError, OSError):
            pass


def cmd_probe(args):
    """S1/S2 probe-compile census + 自动回归对账.

    Runs pipeline/probe_compile.py, then diffs the census against the
    `latest` baseline (data/status/baselines/) — pass→fail flips are
    regressions and listed with their new errors — and refreshes the
    baseline afterwards so the next loop has a fresh reference.
    """
    script = os.path.join(_PIPELINE_DIR, 'probe_compile.py')
    rc = subprocess.run([sys.executable, script] + args).returncode
    if rc != 0:
        sys.exit(rc)

    tools_dir = os.path.join(_PROJECT_DIR, 'tools')
    det_script = os.path.join(tools_dir, 'regression_detector.py')

    # 1. 对账：当前 census vs 上次基线（有基线才比）
    #
    # R2（2026-09-15 独立复核 M2-b）：原先本步的 returncode **被丢弃**，
    # 随后**无条件** `--save-baseline` ⇒ 任何退化都在同一轮被"洗白"进基线，
    # `probe` 恒 exit 0。已实际发生的危害实例：`compile_baseline.json`(16:13) 记录的
    # ChoseCompose/UIStatic 两个 ok→fail，在 20:07 的无条件刷新后
    # `regression_detector --check` 已看不见（new_failures/new_errors 均为 0）。
    baselines = Path(_PROJECT_DIR) / 'data' / 'status' / 'baselines'
    has_baseline = (baselines / 'latest.json').exists()
    check_rc = 0
    if has_baseline:
        print("\n[Regression] diff vs latest baseline:")
        check_rc = subprocess.run(
            [sys.executable, det_script, '--check', '--format', 'text']).returncode

    # regression_detector.py 的退出码语义（已核验 :369-370）：
    #   has_regression = new_failures > 0 or new_errors > 0  →  return 1
    if check_rc != 0:
        # 跳过刷新 = 棘轮语义（与 tools/compile_regression.py 只在显式
        # `--update-baseline` 时前进同构）。**不是**"基线永久停旧"缺陷：
        # 退化修好后 --check 自动通过，刷新即恢复；操作者也可在确认后手动刷新。
        # 但必须给出逃生口提示 + 把退化报告落盘留痕，否则证据会随下次刷新消失。
        print("\n[Baseline] NOT refreshing: regressions detected (exit %d)." % check_rc)
        print("        The baseline is intentionally left unchanged so the regression "
              "stays visible on the next run.")
        # 证据落盘：调用 det 的 `--report`，它**自己**决定落盘路径。
        # ⚠️ 注意：`regression_detector.py:323-337` 的 `save_report()` **忽略** `args.output`
        # （总是写 `self.report_dir/regression_<timestamp>.txt`），故**不要**传 `--output`
        # ——传了也无效，且会让人误以为文件在别处（captain 首版即因此写了个不存在的路径）。
        # `--report` 的返回码遵循 "有回归→1"，那是本分支的正常情形；2 = 内部错误。
        try:
            _rep = subprocess.run([sys.executable, det_script, '--report',
                                   '--format', 'text'])
            if _rep.returncode == 2:
                print("        WARN: --report exited 2 (evidence may be incomplete).")
            elif _rep.returncode != 0:
                # 非 0 非 2：仍属"有回归"，但提示实际落盘目录以便查证
                print("        Evidence saved under pipeline/_logs/regression_detection/")
        except OSError as e:
            print("        WARN: could not run --report: %s" % e)
        print("        After confirming the regressions are understood, refresh "
              "deliberately with:")
        print("          python3 tools/regression_detector.py --save-baseline")
        sys.exit(check_rc if check_rc > 0 else 1)

    # 2. 无退化 → 刷新基线，供下一轮对账
    print("\n[Baseline] refreshing latest baseline...")
    save_rc = subprocess.run([sys.executable, det_script, '--save-baseline']).returncode
    if save_rc != 0:
        # 原先此处的 rc 也被丢弃（census 缺失时该脚本会抛错 → rc 2）。
        print("[ERROR] regression_detector.py --save-baseline exited %d." % save_rc)
        sys.exit(save_rc if save_rc > 0 else 1)


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
    elif command == 'match':
        cmd_match()
    elif command == 'probe':
        cmd_probe(args[1:])
    elif command == 'snapshot':
        snap_script = os.path.join(_PIPELINE_DIR, 'snapshots', 'snapshot.py')
        sub = args[1] if len(args) > 1 else 'list'
        subprocess.run([sys.executable, snap_script, sub])
    elif command == 'tool':
        cmd_tool(args[1:])
    elif command == 'iterate':
        # UNAVAILABLE: this used to `from pipeline.iterate import main`, but
        # pipeline/iterate.py does not exist in this repository, so the command
        # died with a bare ModuleNotFoundError traceback. Fail loudly instead.
        print("[ERROR] 'iterate' is UNAVAILABLE: pipeline/iterate.py does not exist.")
        print("        No automatic annotation-iteration engine is implemented in this")
        print("        repository. Drive the pipeline step by step instead:")
        print("          python pipeline/cli.py apply")
        print("          python pipeline/cli.py export")
        print("          python pipeline/cli.py codegen all")
        print("          python pipeline/cli.py probe all")
        print("          python pipeline/cli.py match")
        sys.exit(2)
    else:
        print("Unknown command: %s" % command)
        print("Run with --help for usage.")
        sys.exit(1)


if __name__ == '__main__':
    main()
