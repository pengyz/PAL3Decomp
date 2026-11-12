#!/usr/bin/env python3
"""[idalib 直连 runner 2026-11-12] apply_annotations + export_full 一体执行。

背景定谳: 本环境 idat 直跑必 TVision TTY 崩(core dump); IDA MCP 的 HTTP 层
90s 看门狗 + 断连杀任务(实测全量 export 1103/3674 半途亡)。idalib 库模式
在本进程内直跑 = 零 watchdog 零断连, 全量 export 实测 ~3 分钟完赛。

用法:
  /home/peng/.local/ida-mcp-venv/bin/python tools/run_apply_export_idalib.py [--export-only]

前置: /home/peng/ida-pro-9.1/idalib/python 可 import idapro。
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)
print('[runner] db opened:', db)

import os
os.chdir('/home/peng/workspace/PAL3Decomp')
sys.path.insert(0, '/home/peng/workspace/PAL3Decomp/pipeline')
sys.path.insert(0, '/home/peng/workspace/PAL3Decomp/pipeline/ida')
import idc
idc.qexit = lambda *a, **k: None  # 库模式禁进程退出

EXPORT_ONLY = '--export-only' in sys.argv
if not EXPORT_ONLY:
    import apply_annotations as AA
    AA.apply_annotations()
    print('[runner] apply done')

import export_full as EF
EF.main()
print('[runner] export done')
idapro.close_database(False)
