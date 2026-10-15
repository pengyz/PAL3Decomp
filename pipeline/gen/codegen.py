#!/usr/bin/env python3
"""PAL3 代码生成管线 (tree-sitter AST pipeline)

用法:
  python pipeline/gen/codegen.py <command> [options]

命令:
  clean               清空 gen/ 目录（生成代码 + 头文件）
  headers             生成 .h 头文件 (include/pal3/gen/)
  cpp                 生成 .cpp 实现文件 (src/pal3/gen/)
  cpp ClassName       只生成指定类
  all                 clean + headers + cpp 全量生成

提示: 用 python pipeline/cli.py config 查看/验证配置

工作流:
  # 完整重建（标注有重大变更时）
  cp original/PAL3.exe.raw.i64 original/PAL3.exe.i64
  $IDA -A -S"pipeline/ida/master_pipeline.py" original/PAL3.exe.i64
  $IDA -A -S"pipeline/ida/apply_annotations.py" original/PAL3.exe.i64
  $IDA -A -S"pipeline/ida/export_full.py" original/PAL3.exe.i64
  python pipeline/gen/codegen.py all
  ninja -C build -k 0

  # 仅重新生成代码（只改了 codegen/annotations，IDB 不变）
  python pipeline/gen/codegen.py all
  ninja -C build -k 0

配置:
  所有路径在项目根目录 pipeline.toml 中定义。
  首次使用时如果缺失会报错并给出模板。

依赖:
  - Python 3.8+
  - tree-sitter, tree-sitter-cpp (pip install tree-sitter tree-sitter-cpp)
"""
import os
import sys
import os

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
    from pathlib import Path
    ok = True
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
        print("  [i] Decomp dir not found (run IDA export first)")
    if ok:
        print("  [OK] All required paths exist")


def cmd_clean():
    """Clean all previously generated files in gen/ directories."""
    import shutil
    from pipeline.config import PROJECT_ROOT as _PR
    gen_dirs = [
        _PR / "pal3" / "src",  # pal3/src/
    ]
    for d in gen_dirs:
        if d.exists():
            shutil.rmtree(d)
            print("  Cleaned: %s/" % d)
        else:
            print("  (empty) %s/" % d)
    print("[clean] Done")


def cmd_headers():
    """Generate header files from annotations."""
    from data import store
    store.load()
    from stages.emit_headers import run_header_generation
    run_header_generation()


def cmd_cpp(filter_classes=None):
    # S2 射程接线（2026-10-10）：CODEGEN_CLASS 注入 filter_classes
    # —— 前两版只写了 scoped_cpp_filter() 函数却没接进调用点（「搭桥不接线」）
    if filter_classes is None and CODEGEN_CLASS:
        filter_classes = {CODEGEN_CLASS}
    """Generate .cpp implementation files from decomp JSONs."""
    from data import store
    store.load()
    from stages.emit_cpp import run_cpp_generation
    run_cpp_generation(filter_classes=filter_classes)


def _retain_apply(no_retain=False):
    """[Phase2 留存 2026-10-15] codegen 产物落盘后套用 phase2/overlay 手工 fix。

    零管线侵入钩子（verifier 方案 A'）：manifest 空 = no-op；`--no-retain` 逃生阀；
    rc 原样传播（override 漂移 = exit 2 fail-loud）。仅挂 headers/cpp/all 三分支
    （clean/config 不挂——clean 无产物可套，config 不产码）。
    """
    if no_retain:
        print('[phase2-retain] --no-retain ⇒ 跳过 overlay 套用')
        return 0
    try:
        _tools = os.path.join(os.path.dirname(os.path.dirname(
            os.path.dirname(os.path.abspath(__file__)))), 'tools')
        if _tools not in sys.path:
            sys.path.insert(0, _tools)
        import phase2_retain as pr
    except Exception as e:  # 工具缺失不得拖垮 codegen（但要出声）
        print('[phase2-retain][WARN] phase2_retain 不可用（%s）⇒ 跳过' % e)
        return 0
    from pipeline.config import PROJECT_ROOT as _PR
    ctx = pr.Ctx(str(_PR / 'pal3' / 'src'), str(_PR / 'phase2'))
    return pr.cmd_apply(ctx)


def main():
    args = sys.argv[1:]
    if not args or args[0] in ('-h', '--help', 'help'):
        print(__doc__)
        sys.exit(0)

    command = args[0]
    filter_classes = set()
    no_retain = False
    for arg in args[1:]:
        if arg == '--no-retain':
            no_retain = True
        elif not arg.startswith('-'):
            filter_classes.add(arg)

    rc = 0
    if command == 'config':
        cmd_config()
    elif command == 'clean':
        cmd_clean()
    elif command == 'headers':
        cmd_headers()
        rc = _retain_apply(no_retain)
    elif command == 'cpp':
        cmd_cpp(filter_classes=filter_classes or None)
        rc = _retain_apply(no_retain)
    elif command == 'all':
        cmd_clean()
        cmd_headers()
        cmd_cpp(filter_classes=filter_classes or None)
        rc = _retain_apply(no_retain)
    else:
        print("Unknown command: %s" % command)
        print("Run with --help for usage.")
        sys.exit(1)
    if rc:
        sys.exit(rc)


# ---------------------------------------------------------------------------
# S2：射程 codegen（2026-10-10）
# ---------------------------------------------------------------------------
# 对抗复核裁决：
#   1. **头全量生成**（S0 已把 decomp 派生头决策缓存化 => 头全量安全，
#      且天然解决依赖闭包）—— 头生成分支不得被射程过滤
#   2. **`.cpp` 射程** —— 只生成目标 TU 的 .cpp
# S2 修复（病灶层三问第①问答出）：原为 `CODEGEN_CLASS = None` 模块全局，
# 但**没有任何地方从 os.environ 赋值** —— cli.py 的 apply_scoped_env() 写了却没调用，
# codegen.py 自己也不读环境变量 => 射程过滤永远拿不到值 => 三次端到端全失败。
# 修：直接从环境变量初始化（与 S1 的 EXPORT_* 同通道）。
CODEGEN_CLASS = os.environ.get('CODEGEN_CLASS') or None   # None=全量；str = 只生成该类的 .cpp
CODEGEN_FUNC = os.environ.get('CODEGEN_FUNC') or None    # None=全量；hex str = 只生成该函数所在 TU 的 .cpp


def scoped_cpp_filter(tu_name):
    """判断某 TU 的 .cpp 是否在射程范围内。头不受此过滤。"""
    if CODEGEN_CLASS is None and CODEGEN_FUNC is None:
        return True
    if CODEGEN_CLASS is not None:
        return tu_name == CODEGEN_CLASS
    return True   # CODEGEN_FUNC 按地址过滤，需调用方另判

if __name__ == '__main__':
    main()

