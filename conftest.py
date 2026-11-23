"""conftest：编码根治（P1——复核方案：PYTHONUTF8=1 启动层）。
PYTHONIOENCODING 不影响 open() 默认 encoding（locale GBK）——撤换为 UTF-8 mode。"""
import os
os.environ['PYTHONUTF8'] = '1'

# [目录组织 20261123] 实验线迁入 experiments/ —— 测试 `from ghidra_track.xxx import`
# 语义不变（命名空间包经 sys.path 解析）。
import sys as _sys
_sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'experiments'))
