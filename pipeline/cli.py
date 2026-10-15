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
  match [--rebaseline R] S4 字节匹配裁判（假设旗标组 + L1 棘轮检查；--rebaseline 显式推进，需给理由）
  status [--strict]   只读状态预检：阶段顺序 / 三份基线对照 / 已知恒红门禁
  loop [opts]         一次跑完 apply→export→codegen→probe→match（可 --expect-* 断言基线）
                      --stages probe,match   只跑部分
                      --dry-run              只打印计划
                      --expect-s2 75/205 --expect-errors 2150 --expect-l1 35
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
import json
import re
import shutil
import subprocess
import time
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

    # Step 4b: second apply — REQUIRED on a freshly built IDB.
    # 单趟走不完"造 item → 挂类型 → 命名"的依赖链：[2] 命名时 struct/item 还不存在，
    # [6b3] 只补名字不补类型。同一 IDB 上实测（IDAPython 副本探测）：
    #   1 趟后 0xC10968 = unk_C10968 (item size 1)；2 趟后 = g_palScript (size 2176)。
    # 少这一趟的读数是 S2 67/201 · L1 20 · globals 2182/2151，
    # 多这一趟是 S2 70/201 · L1 21 · globals 2743/2686。
    # ⚠️ 2026-09-19 实测：**再加趟数（3/5 趟、以及 apply+fix_vtable 成对跑 5 趟）都停在
    #    S2 70/201 · matched 222/256**，而"apply 与 export 交替多轮"的历史 IDB 是
    #    71/201 · 225/259 ⇒ 收敛驱动**不是**单纯的 apply 趟数（疑与 export 也会改 IDB 有关），
    #    该问题**仍开放**；在查清之前只保留"两趟"这一条已被验证的最小修复，不加更多趟数。
    # 见 docs/knowledge/gotcha_apply_single_pass_leaves_globals_untyped.md
    print()
    print("[4b/4] Apply annotations AGAIN (fresh-IDB fixpoint; one pass leaves "
          "globals unnamed/untyped) ...")
    ok2 = _run_ida('apply_annotations.py', cfg.idb_work)
    print("      -> %s" % ("OK" if ok2 else "WARN: non-zero exit"))

    # Step 5: Fix vtable types (post-processing)
    print("[5/5] Fix vtable types: setting __cppobj and typed vtable pointers ...")
    vtok = _run_ida('fix_vtable_types.py', cfg.idb_work)
    print("      -> %s" % ("OK" if vtok else "WARN: non-zero exit"))

    # Done
    print()
    print("=" * 55)
    if not (ok_master and ok and ok2 and vtok):
        # Same defect class as cmd_apply: this used to print "INIT COMPLETE.
        # IDB is ready" even after a failed step, so export/codegen/match ran
        # against a half-built IDB and the numbers looked plausible.
        failed = [name for name, good in (('master_pipeline.py', ok_master),
                                          ('apply_annotations.py', ok),
                                          ('apply_annotations.py (2nd pass)', ok2),
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
    _run_invariants_advisory()
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

    # ---- S1 射程 export（2026-10-09）----
    # 经环境变量传给 export_full.py（idat -S 场景下最可靠的参数通道）。
    # 设计要点 0：EXPORT_OUTDIR 使射程结果写独立目录，主 asm/pal3/decomp/ 零改动。
    _sc = {k: v for k, v in (('EXPORT_FUNC', os.environ.get('EXPORT_FUNC')),
                             ('EXPORT_CLASS', os.environ.get('EXPORT_CLASS')),
                             ('EXPORT_OUTDIR', os.environ.get('EXPORT_OUTDIR'))) if v}
    if _sc:
        env = dict(env or os.environ, **_sc)
        print("EXPORT (scoped): %s" % _sc)
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
    # 2026-09-20 审计 P1-4：export 有 8 处 [t4-DECLARED-EXCEPTION] 会把注解字段
    # **透传**到 asm/pal3/ida_structs.json（取舍理由与量化证据见 export_full.py 头部声明块）。
    # 风险：若有人手改 IDB 而没同步注解 ⇒ 产物与注解漂移，而下游（data.py 读
    # ida_structs.json）**按注解值工作** ⇒ "看起来像 IDB 状态"的静默不一致。
    # 此处加一道**只读**校验并**报警（不阻断）**：迁移期允许漂移，但必须看得见。
    checker = os.path.join(_PROJECT_DIR, 'tools',
                           'check_export_annotation_consistency.py')
    if os.path.exists(checker):
        print("\n[Consistency] 校验导出产物与注解的透传字段（vtables / methods）...")
        chk = subprocess.run([sys.executable, checker])
        if chk.returncode != 0:
            print("[WARN] 导出产物与注解的透传字段不一致（详见上表）。下游按**注解**值"
                  "工作 —— 请确认这是预期内的迁移期状态，否则先同步注解或 IDB。")
    _run_invariants_advisory()
    print()
    print("Next: python pipeline/cli.py codegen all")


def _run_invariants_advisory():
    """advisory 地跑 codegen_invariants：只报告计数，**不影响调用方的退出码**。

    缘起：`cmd_check` 已接该工具，但 `cmd_check` 是手动命令；`apply`/`export` 才是写盘路径，
    三路独立复核点名"只改 cmd_check 就是空门" ⇒ 本 helper 把它们也挂上（仍 advisory）。
    """
    inv = os.path.join(_PROJECT_DIR, 'tools', 'codegen_invariants.py')
    if not os.path.exists(inv):
        return 0
    # 2026-09-21 F2：flush=True —— stdout 被重定向时调用方的行缓冲会把本标题行排到
    # 子进程输出**之后**（实测：块头出现在 `=> ADVISORY-ONLY` 之后 ✗），日志里框定失去前置性。
    print(flush=True)
    print("[Invariants] advisory 模式（只报告计数，不影响退出码）...", flush=True)
    r = subprocess.run([sys.executable, inv, '--advisory'])
    if r.returncode != 0:
        print("[WARN] codegen_invariants 在 advisory 模式下仍非零退出（%d）—— 不影响本次结果，"
              "但说明工具行为与预期不符 ✓" % r.returncode)
    return r.returncode


def cmd_check():
    """Run check_annotations.py（并 advisory 地跑 codegen_invariants）。

    缘起（2026-09-20 三路复核"先做一小步"#1）：该工具的默认检查集是 A/B/D，而**当前就已失败**
    （实测 A=132/B=56/D=10 全 exit 1）⇒ 直接接会**立刻全红**、把整条工作流堵住 ✗。
    advisory 只报告、恒 exit 0 ⇒ 先"看得见计数"，存量清零后去掉 `--advisory` 即可升为硬失败 ✓
    （"逐闸毕业生效"）。

    2026-09-21 F1（评审后续项）：此处原先有一份**内联副本**（由 f74edaa7b 引入），与
    `_run_invariants_advisory()` 是同一逻辑两份 ⇒ 收敛为一处调用（DRY）。
    """
    script = os.path.join(_PIPELINE_DIR, 'check_annotations.py')
    result = subprocess.run([sys.executable, script])
    _run_invariants_advisory()   # 返回值刻意丢弃：advisory 不得改变 check 退出码
    # 2026-09-21 B34 复核（两路一致）：把 union 平凡性门禁**接进 check** ✓
    # 为什么直接**硬失败**（而非像 invariants 那样 advisory）：本闸的**自身存量 = 0** ✓
    # （实测"无 landmine"），按"逐闸毕业生效"规则可立即升硬 ✓ —— 一旦有人给 union 按值成员类
    # 加 ctor/dtor（B34 的成因 ✗），本闸会**真的失败** ✓，而不是静默放过。
    _ug = os.path.join(_PROJECT_DIR, 'tools', 'check_union_member_triviality.py')
    _ug_rc = 0
    if os.path.exists(_ug):
        print(flush=True)
        print("[UnionTriviality] 检查 union 按值成员的平凡性（B34 成因，存量=0 ⇒ 硬失败）...", flush=True)
        _ug_rc = subprocess.run([sys.executable, _ug]).returncode
        if _ug_rc != 0:
            print("[FAIL] union 平凡性被破坏 —— 参见工具输出的处置建议（B34 曾因此 208 单元 C2620 ✗）", flush=True)
    # 2026-09-21（方向复核 e0ea83d9 的 E6 建议）：注解级不变量闸「成员末端 < binary_size」✓
    # 为什么硬失败：本闸**自身存量 = 0** ✓（实测 0 越界 / 0 解析失败），且它**正是 apply 拒绝的前置** ✓
    # —— 一旦"成员末端 ≥ binary_size"，apply 会拒绝该 UDT ⇒ 生成头消失（UIStatic 152→248 那次
    # 76 单元 C2079 的直接成因 ✓）。成对判别力已证：无注入 exit0 / --self-test 注入 exit1 ✓。
    _me = os.path.join(_PROJECT_DIR, 'tools', 'check_member_extent.py')
    _me_rc = 0
    if os.path.exists(_me):
        print(flush=True)
        print("[MemberExtent] **advisory**：检查「成员末端 < binary_size」（apply 拒绝的前置）...", flush=True)
        _me_rc = subprocess.run([sys.executable, _me]).returncode
        if _me_rc != 0:
            # 2026-09-21：本闸改为**真实类型尺寸**后（原先 1 字节/元素 ⇒ 判别力=0 ✗，复核 7f6a52cd 查出）
            # 报出 **1 处既存违反**（Comp_DonateUI: 46192 vs 末端 462284 ✗）——**非本批次引入** ✓。
            # 该发现**未取证** ⇒ 不据它改注解 ✗；但也不能让 check 失败（会掩盖其它判据 ✗）
            # ⇒ **暂降为 advisory** ✓，并把该缺陷登记待查 ✓。
            print("[WARN] MemberExtent 报出违反（advisory，不影响退出码）—— 见上方清单；"
                  "已登记为既存缺陷（Comp_DonateUI m_state），未取证前不改注解 ✓", flush=True)
            _me_rc = 0
    sys.exit(result.returncode or _ug_rc or _me_rc)


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
        # 2026-09-20 审计 P1-2：**先跑 probe s2**，再让 snapshot /
        # compile_regression 去看 census。
        #
        # 为什么：`tools/compile_regression.py` 只读**缓存**的
        # `data/status/probe_census.json`（`docs/knowledge/gotcha_compile_regression_reads_cached_census.md`），
        # 而本钩子此前**从不调用 probe** ⇒ 它门禁的是"上一次不知何时跑的 probe 快照"，
        # 不是本次 codegen 的实际编译结果。CLAUDE.md 的检查点表也缺了这一步。
        #
        # 成本实测：`probe s2` 约 21 秒（206 单元），可接受，故**默认开启**。
        # 需要快速迭代时可传 `--skip-probe` 明确放弃这道门（此时 compile_regression
        # 验的是陈旧快照，其结论无意义 —— 会在日志里明示）。
        if '--skip-probe' in args:
            print("\n[Probe] SKIPPED (--skip-probe)：compile_regression 将基于**陈旧** "
                  "census 下结论，该结论无意义。")
        else:
            print("\n[Probe] Running probe s2 so compile_regression sees THIS codegen's census...")
            probe = subprocess.run([sys.executable, os.path.join(_PIPELINE_DIR, 'cli.py'),
                                    'probe', 's2'])
            if probe.returncode != 0:
                # 不吞掉：probe 非零既可能是"检出真退化"，也可能是工具错误。
                # 两者都必须断链；操作者若确知当前状态可传 --skip-probe 继续。
                print("[ERROR] probe s2 exited %d — 本次 codegen 的编译普查未通过"
                      "（新失败/退化，或 probe 自身出错）。" % probe.returncode)
                print("        修好退化后再跑；若确要只跑 codegen，可加 '--skip-probe'"
                      "（会使 compile_regression 的结论失去意义）。")
                sys.exit(probe.returncode if probe.returncode > 0 else 1)

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


def cmd_match(args=()):
    """S4 byte-match referee: compile S2-green units with the calibrated
    hypothesis flags and diff function bytes against PAL3.exe .text.
    L1 (perfect match) count is the ratchet: it must never regress.

    `--rebaseline "<reason>"`：**显式推进棘轮**（与 `tools/compile_regression.py
    --update-baseline` 对称）。必须给理由，理由会写进 `s4_baseline.json` 的
    `rebaseline` 字段。仅在确认退化已被理解/已接受时使用。
    """
    import json
    args = list(args)
    rebase_reason = None
    for i, a in enumerate(args):
        if a == '--rebaseline' and i + 1 < len(args):
            rebase_reason = args[i + 1]
        elif a.startswith('--rebaseline='):
            rebase_reason = a.split('=', 1)[1]
    if '--rebaseline' in args and not rebase_reason:
        print('[match] --rebaseline 需要理由，例：--rebaseline "总体从 372→319 符号，重新对齐可比集"')
        sys.exit(2)

    # P0-5（多路分析，v2 修法）：射程 match 严禁读写 s4_baseline.json
    # （否则 stats.match_L1 从 86 骤降 => 棘轮误判 => L1 记录永久损坏）。
    # v2：**不包块、不 early-return**（v1 跳过了整个 match 导致 0.07s 空跑），
    # 而是让棘轮**在 scoped 文件上跑** —— 比对照常，基线分离。
    _sc = os.environ.get('MATCH_SCOPED')
    if _sc:
        s4 = Path('data/status') / ('s4_scoped_%s.json' % _sc)
        print('[S2] scoped match: L1 ratchet runs on %s (baseline untouched)' % s4.name)
    else:
        s4 = Path('data/status/s4_baseline.json')
    prev_l1 = 0
    prev_text = None
    prev_pop = (None, None)
    if s4.exists():
        try:
            prev_text = s4.read_text(encoding='utf-8')
            _pd = json.loads(prev_text)
            prev_l1 = _pd.get('stats', {}).get('match_L1', 0)
            prev_pop = (_pd.get('stats', {}).get('matched'), _pd.get('stats', {}).get('symbols'))
        except (json.JSONDecodeError, OSError):
            pass
    script = os.path.join(_PIPELINE_DIR, 'compare_pal3.py')
    flags = "/nologo /TP /c /W3 /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MT /Gd"
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
            cur = json.loads(s4.read_text(encoding='utf-8'))
            cur_l1 = cur.get('stats', {}).get('match_L1', 0)
            cur_pop = (cur.get('stats', {}).get('matched'), cur.get('stats', {}).get('symbols'))
            print()
            print("[L1 ratchet] previous %d -> current %d" % (prev_l1, cur_l1))
            # 总体（matched/symbols）必须一并打印：L1 是"可比符号集内"的计数，
            # 总体变了 ⇒ 两次 L1 **不可比**（2026-09-21：记录 38 出自 symbols=372 的树，
            # 实况 symbols=319 ⇒ 38→35 很大程度是总体收缩，不是丢了逐字节函数）。
            print("[L1 ratchet] population: previous matched=%s/%s -> current matched=%s/%s"
                  % (prev_pop[0], prev_pop[1], cur_pop[0], cur_pop[1]))
            pop_changed = prev_pop[1] is not None and cur_pop[1] is not None and prev_pop != cur_pop
            if pop_changed:
                print("[L1 ratchet] ⚠️ 可比总体**已变化** ⇒ 两次 L1 不可直接比较；"
                      "若确认可接受，用 `cli.py match --rebaseline \"<理由>\"` 显式重新对齐")
            if rebase_reason:
                cur['rebaseline'] = {
                    'reason': rebase_reason,
                    'at': time.strftime('%Y-%m-%dT%H:%M:%S'),
                    'prev_match_L1': prev_l1, 'cur_match_L1': cur_l1,
                    'prev_population': {'matched': prev_pop[0], 'symbols': prev_pop[1]},
                    'cur_population': {'matched': cur_pop[0], 'symbols': cur_pop[1]},
                }
                s4.write_text(json.dumps(cur, ensure_ascii=False, indent=1), encoding='utf-8')
                print("[L1 ratchet] ✅ 已显式推进基线至 %d（理由已记入 s4_baseline.json.rebaseline）"
                      % cur_l1)
                print("[L1 ratchet]    理由: %s" % rebase_reason)
            elif cur_l1 < prev_l1:
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
    # 2026-09-20 审计 P0-2：此前本函数**恒 exit 0**（只打印不传播），
    # 使 `compile && ...` 链失效、门禁无法断链。
    sys.exit(0 if result.returncode == 0 else 1)


# ---------------------------------------------------------------------------
# status / loop：把"可持续、可迭代"落到入口层（2026-09-21）
#
# 背景：`iterate` 是**空槽**（pipeline/iterate.py 不存在 ⇒ exit 2），全链路只能手工拼；
# 且三份基线互相矛盾 ⇒ `codegen all` 与 `match` 在干净 HEAD 上**恒 exit 1**，
# 自动化循环分不清信号与噪声。`status` 把状态如实打印出来，`loop` 把一轮跑成**一条命令**，
# 并支持 `--expect-*`（把"先断言基线再测量"这条纪律**机械化**，不再靠人记得）。
# ---------------------------------------------------------------------------

def cmd_status(argv):
    """只读状态预检（不刷新任何基线）。"""
    from pipeline import preflight
    state = preflight.collect_state()
    print(preflight.render(state))
    if '--strict' in argv:
        rows = preflight.baseline_rows(state)
        inconsistent = (rows[0]['ok'] is not None and rows[1]['ok'] is not None
                        and (rows[0]['ok'], rows[0]['total']) != (rows[1]['ok'], rows[1]['total']))
        if inconsistent or preflight.known_red_gates(state):
            print('[status --strict] 基线不一致或存在恒红门禁 ⇒ exit 1')
            sys.exit(1)
    sys.exit(0)


# 阶段 → 传给 cli.py 的参数；顺序即依赖顺序，不可乱序
LOOP_STAGES = {
    'apply': [],
    'export': [],
    'codegen': ['all'],
    'probe': ['all'],
    'match': [],
}
LOOP_ORDER = ['apply', 'export', 'codegen', 'probe', 'match']


def _loop_parse(stage, text):
    """从阶段输出里抽取关键读数（纯文本解析，容错：抽不到就返回 {}）。"""
    out = {}
    if stage == 'probe' or stage == 'codegen':
        m = re.search(r'S2 cpp:\s*(\d+)/(\d+)\s*ok', text) or \
            re.search(r'S2-passing units:\s*(\d+)', text)
        if m:
            if m.lastindex == 2:
                out['s2_ok'], out['s2_total'] = int(m.group(1)), int(m.group(2))
            else:
                out['s2_ok'] = int(m.group(1))
    if stage == 'match':
        m = re.search(r'matched\s+(\d+)/(\d+)\s+symbols\s*\|\s*L1\s+(\d+)', text)
        if m:
            out['matched'], out['symbols'], out['L1'] = int(m.group(1)), int(m.group(2)), int(m.group(3))
        m2 = re.search(r'\[L1 ratchet\] previous (\d+) -> current (\d+)', text)
        if m2:
            out['L1_prev'], out['L1_cur'] = int(m2.group(1)), int(m2.group(2))
    return out


def cmd_loop(argv):
    """一次跑完完整迭代（apply→export→codegen→probe→match），可选 `--expect-*` 断言基线。

    用法::

        python pipeline/cli.py loop                        # 全链路
        python pipeline/cli.py loop --stages probe,match   # 只跑部分
        python pipeline/cli.py loop --dry-run              # 只打印计划
        python pipeline/cli.py loop --expect-s2 75/205 --expect-errors 2150 --expect-l1 35
    """
    from pipeline import preflight

    if '--dry-run' in argv:
        print('loop 计划（顺序即依赖顺序）：')
        for i, s in enumerate(LOOP_ORDER, 1):
            print('  %d. python pipeline/cli.py %s %s' % (i, s, ' '.join(LOOP_STAGES[s])))
        sys.exit(0)

    stages = LOOP_ORDER
    for i, a in enumerate(argv):
        if a == '--stages' and i + 1 < len(argv):
            stages = [x.strip() for x in argv[i + 1].split(',') if x.strip()]
        elif a.startswith('--stages='):
            stages = [x.strip() for x in a.split('=', 1)[1].split(',') if x.strip()]
    unknown = [s for s in stages if s not in LOOP_STAGES]
    if unknown:
        print('[loop] 未知阶段: %s（可选 %s）' % (', '.join(unknown), ', '.join(LOOP_ORDER)))
        sys.exit(2)

    def _opt(name):
        for i, a in enumerate(argv):
            if a == name and i + 1 < len(argv):
                return argv[i + 1]
            if a.startswith(name + '='):
                return a.split('=', 1)[1]
        return None

    try:
        exp = preflight.parse_expect(_opt('--expect-s2'), _opt('--expect-errors'),
                                    _opt('--expect-l1'))
    except ValueError as e:
        print('[loop] %s' % e)
        sys.exit(2)

    # 跑之前先如实展示"已知恒红"，避免把这些当成真失败
    red = preflight.known_red_gates(preflight.collect_state())
    red_gates = {g['gate'].split(' → ')[0] for g in red}
    if red:
        print('[loop] 已知恒红门禁 %d 条（出现时会被标为 TOLERATED，不会被静默吞掉）：' % len(red))
        for g in red:
            print('   ❌ %s（记录 %s / 实况 %s）' % (g['gate'], g['recorded'], g['live_baseline']))
    print()

    logdir = os.path.join(_PROJECT_DIR, 'pipeline', '_logs')
    os.makedirs(logdir, exist_ok=True)
    report = {'stages': {}, 'expect': exp, 'tolerated': [], 'failed': []}
    for name in stages:
        cmd = [sys.executable, os.path.join(_PIPELINE_DIR, 'cli.py'), name] + LOOP_STAGES[name]
        print('=' * 72)
        print('[loop] %s: %s' % (name, ' '.join(cmd[2:])))
        t0 = time.time()
        proc = subprocess.run(cmd, cwd=_PROJECT_DIR, capture_output=True, text=True, errors='replace')
        secs = round(time.time() - t0, 1)
        text = (proc.stdout or '') + (proc.stderr or '')
        logfile = os.path.join(logdir, 'loop_%s.log' % name)
        try:
            with open(logfile, 'w', encoding='utf-8') as f:
                f.write(text)
        except OSError:
            logfile = None
        entry = {'rc': proc.returncode, 'secs': secs, 'log': logfile}
        entry.update(_loop_parse(name, text))
        report['stages'][name] = entry

        verdict = 'OK' if proc.returncode == 0 else 'RC=%d' % proc.returncode
        if proc.returncode != 0:
            # 该阶段是否属于"已知恒红"（按阶段名匹配 gate 前缀）
            tolerated = name in red_gates
            verdict += '  [TOLERATED: 已知恒红]' if tolerated else '  [FAIL]'
            if tolerated:
                report['tolerated'].append(name)
            else:
                report['failed'].append(name)
            tail = [l for l in text.splitlines() if l.strip()][-12:]
            print('[loop] %s EXIT=%d (%ss) —— 末尾 12 行：' % (name, proc.returncode, secs))
            for l in tail:
                print('    | %s' % l)
        else:
            print('[loop] %s EXIT=0 (%ss)' % (name, secs))
        if entry.get('s2_ok') is not None and entry.get('s2_total'):
            print('[loop]   S2 读数: %s/%s' % (entry['s2_ok'], entry['s2_total']))
        if entry.get('L1') is not None:
            print('[loop]   match 读数: matched %s/%s · L1 %s' % (entry.get('matched'),
                                                                 entry.get('symbols'), entry['L1']))
        if report['failed']:
            print('[loop] 出现**非容错**失败（%s）⇒ 中止后续阶段' % ', '.join(report['failed']))
            break

    # [Phase2 留存 2026-10-15] retain 状态可见性（条目数/漂移数——verifier 步骤 3）
    try:
        _tp = os.path.join(_PROJECT_DIR, 'tools')
        if _tp not in sys.path:
            sys.path.insert(0, _tp)
        import phase2_retain as _pr
        _ctx = _pr.Ctx(os.path.join(_PROJECT_DIR, 'pal3', 'src'),
                       os.path.join(_PROJECT_DIR, 'phase2'))
        _m = _pr.load_manifest(_ctx.manifest_path)
        if _m['entries']:
            _plan = _pr.plan_apply(_m, _ctx.root_hashes(), _ctx.overlay_hashes())
            print('[loop] phase2-retain: 条目 %d · 在位 %d · 待套 %d · 漂移 %d'
                  % (len(_m['entries']), len(_plan['inplace']),
                     len(_plan['actions']), len(_plan['drift'])))
        else:
            print('[loop] phase2-retain: 条目 0（no-op）')
    except Exception as _e:
        print('[loop] phase2-retain: 状态不可读（%s）' % _e)

    # 汇总 + 断言
    print()
    print('=' * 72)
    print('[loop] 汇总: ' + ' · '.join(
        '%s rc=%s/%ss' % (k, v['rc'], v['secs']) for k, v in report['stages'].items()))
    if report['tolerated']:
        print('[loop] 容错通过（已知恒红，非本次引入）: %s' % ', '.join(report['tolerated']))
    # ⚠️ 必须**先落盘** `_loop_last.json` 再收集状态/断言 —— 否则 `--expect-l1` 读不到本次读数
    #（2026-09-21 实测踩到：断言在落盘之前 ⇒ L1 恒失败）
    try:
        with open(os.path.join(_PROJECT_DIR, 'data', 'status', '_loop_last.json'), 'w',
                  encoding='utf-8') as f:
            json.dump(report, f, ensure_ascii=False, indent=1)
        print('[loop] 已写入 data/status/_loop_last.json（供 `status` 显示实测耗时与 L1）')
    except OSError as e:
        print('[loop] 警告: 无法写入 _loop_last.json: %s' % e)
    state = preflight.collect_state()
    fails = preflight.check_expectations(state, exp)
    if exp:
        if fails:
            print('[loop] ❌ 基线断言未满足：')
            for f in fails:
                print('      - %s' % f)
        else:
            print('[loop] ✓ 基线断言全部满足：%s' % exp)

    if report['failed'] or fails:
        sys.exit(1)
    sys.exit(0)


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
        cmd_match(args[1:])
    elif command == 'probe':
        cmd_probe(args[1:])
    elif command == 'status':
        cmd_status(args[1:])
    elif command == 'loop':
        cmd_loop(args[1:])
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


# ---------------------------------------------------------------------------
# S2：射程三档入口（2026-10-10）
# ---------------------------------------------------------------------------
# 用法（经环境变量，与 S1 的 EXPORT_* 同通道）：
#   CODEGEN_CLASS=Object3D PROBE_ONLY=Role/Object3D.cpp MATCH_SCOPED=Object3D ...
def apply_scoped_env():
    """把射程参数注入到 codegen/probe/compare 三阶段。"""
    import pipeline.gen.codegen as _cg
    import pipeline.probe_compile as _pc
    import pipeline.compare_pal3 as _cp
    _cg.CODEGEN_CLASS = os.environ.get('CODEGEN_CLASS') or None
    _cg.CODEGEN_FUNC = os.environ.get('CODEGEN_FUNC') or None
    _only = os.environ.get('PROBE_ONLY')
    _pc.PROBE_ONLY = set(x.strip() for x in _only.split(',')) if _only else None
    _cp.SCOPED_OUTPUT = os.environ.get('MATCH_SCOPED') or None
