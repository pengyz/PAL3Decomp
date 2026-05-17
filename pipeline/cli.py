#!/usr/bin/env python3
"""PAL3 反编译管线 CLI

用法:
  python pipeline/cli.py <command> [options]

命令:
  config              显示当前配置（pipeline.toml）并验证路径
  check               校验 annotations 数据合法性
  codegen all         生成 headers + cpp
  codegen headers     只生成 .h
  codegen cpp         只生成 .cpp
  codegen cpp Class   只生成指定类

工作流:
  # 完整重建（标注有重大变更时）
  python pipeline/cli.py config                    # 确认配置正确
  python pipeline/cli.py check                     # 校验标注
  # 然后在 IDA 中运行:
  #   master_pipeline.py → apply_annotations.py → export_full.py
  python pipeline/cli.py codegen all               # 生成代码
  ninja -C build -k 0                              # 编译

  # 仅重新生成代码
  python pipeline/cli.py codegen all
  ninja -C build -k 0

配置:
  所有路径在项目根目录 pipeline.toml 中定义。
  首次使用时如果缺失会报错并给出模板。

IDA 脚本（需在 IDA 中运行）:
  pipeline/ida/master_pipeline.py      初始化 IDB (PDB + FLIRT)
  pipeline/ida/apply_annotations.py    应用标注到 IDB
  pipeline/ida/export_full.py          导出 Hex-Rays 反编译 JSON
  pipeline/ida/query_todo_fields.py    查询 _todo_ 字段上下文
  pipeline/ida/query_class_full.py     查询指定类全量反编译
"""
import sys
import os

_PIPELINE_DIR = os.path.dirname(os.path.abspath(__file__))
_PROJECT_DIR = os.path.dirname(_PIPELINE_DIR)
if _PIPELINE_DIR not in sys.path:
    sys.path.insert(0, _PIPELINE_DIR)
if _PROJECT_DIR not in sys.path:
    sys.path.insert(0, _PROJECT_DIR)

from pipeline.config import cfg


def cmd_config():
    """Print and validate configuration."""
    from pathlib import Path
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
        print("  [i] Decomp not found (run IDA export_full.py first)")
    if issues:
        for i in issues:
            print("  [!] %s" % i)
        sys.exit(1)
    else:
        print("  [OK] All paths valid")


def cmd_check():
    """Run check_annotations.py."""
    import subprocess
    script = os.path.join(_PIPELINE_DIR, 'check_annotations.py')
    result = subprocess.run([sys.executable, script])
    sys.exit(result.returncode)


def cmd_codegen(args):
    """Delegate to codegen.py."""
    script = os.path.join(_PIPELINE_DIR, 'gen', 'codegen.py')
    import subprocess
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
