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
    gen_dirs = [
        cfg.output_headers,           # include/pal3/gen/
        cfg.output_src / "gen",       # src/pal3/gen/
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
    if not args or args[0] in ('-h', '--help', 'help'):
        print(__doc__)
        sys.exit(0)

    command = args[0]
    filter_classes = set()
    for arg in args[1:]:
        if not arg.startswith('-'):
            filter_classes.add(arg)

    if command == 'config':
        cmd_config()
    elif command == 'clean':
        cmd_clean()
    elif command == 'headers':
        cmd_headers()
    elif command == 'cpp':
        cmd_cpp(filter_classes=filter_classes or None)
    elif command == 'all':
        cmd_clean()
        cmd_headers()
        cmd_cpp(filter_classes=filter_classes or None)
    else:
        print("Unknown command: %s" % command)
        print("Run with --help for usage.")
        sys.exit(1)


if __name__ == '__main__':
    main()
