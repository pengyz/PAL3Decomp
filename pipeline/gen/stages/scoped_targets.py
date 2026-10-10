"""S1：export 射程目标解析（轻量模块，无重依赖）。

为什么单独成模块：`collect.py` 顶层 `from data import store` 在 IDA 环境解析不到
（sys.path 无 pipeline/gen）=> 从它 import resolve_targets 会静默失败、射程降级为全量。
实测证据（2026-10-10）：
    [S1] scoped export unavailable: cannot import name 'store' from 'data'
    [*] Targets: 3651  （射程分支未生效，走了全量）
"""
import json
from pathlib import Path


def resolve_targets(addrs=None, class_name=None):
    """解析射程目标地址集合。

    addrs:      显式地址集合（int 或 hex str，逗号分隔）
    class_name: 按 data/annotations/structs/<Cls>.json 的 methods 归属过滤
    二者都 None  => None（全量，向后兼容）
    二者都给     => 交集（收窄，非并集）
    """
    if addrs is None and class_name is None:
        return None
    out = None
    if addrs is not None:
        out = {int(a, 16) if isinstance(a, str) else int(a) for a in addrs}
    if class_name is not None:
        ann = Path(__file__).resolve().parents[3] / 'data' / 'annotations' / 'structs' / ('%s.json' % class_name)
        if not ann.exists():
            raise ValueError('class annotation not found: %s' % ann)
        d = json.loads(ann.read_text(encoding='utf-8'))
        cls_addrs = {int(k, 16) for k in (d.get('methods') or {})}
        out = cls_addrs if out is None else (out & cls_addrs)
    return out


def scoped_decomp_dir(outdir):
    """射程 export 的输出目录 —— 必须与主 asm/pal3/decomp/ 隔离。

    理由：collect_methods() 从主 decomp 收集类的全部方法签名以生成完整头；
    若射程 export 覆盖主目录，头会残缺。
    """
    return Path(outdir) / 'decomp'
