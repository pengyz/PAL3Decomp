"""conftest：编码根治（P1——复核方案：PYTHONUTF8=1 启动层）。
PYTHONIOENCODING 不影响 open() 默认 encoding（locale GBK）——撤换为 UTF-8 mode。"""
import os
os.environ['PYTHONUTF8'] = '1'
