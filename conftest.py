"""conftest：编码根因修（env 方案——PYTHONIOENCODING 强制）。
注：open() 默认 encoding 的根修=测试文件的显式 encoding（逐件）——覆盖方案脆（参数冲突）故撤。"""
import os

os.environ.setdefault('PYTHONIOENCODING', 'utf-8')
