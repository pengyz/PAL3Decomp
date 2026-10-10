"""S1：export 射程过滤 —— 测试。

设计要点（对抗复核裁决，不得偏离）：
0. **射程 export 必须写独立目录，严禁污染主 asm/pal3/decomp/** ——
   `collect_methods()` :829-835 从主 decomp 收集类的全部方法签名以生成完整头，
   污染则头残缺。
1. `apply` 保持全量（IDB 是共享状态）
2. 非函数产物（ida_structs.json、_globals）保持全量
3. 只射程「函数反编译」这一步（148.5s 的大头）

⚠️ export_full.py 在 IDA 内执行（import ida_*），无法直接单测其 main()。
   本测试只测**可纯化的部分**：resolve_targets（地址/类名解析）与目标过滤逻辑。
"""
import json
import sys
from pathlib import Path

import pytest

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))

from pipeline.gen.stages.collect import resolve_targets   # noqa: E402


# Object3D 的方法地址（取自 data/annotations/structs/Object3D.json 的 methods 键）
OBJECT3D_METHOD_ADDRS = set()


def _load_object3d_addrs():
    global OBJECT3D_METHOD_ADDRS
    if OBJECT3D_METHOD_ADDRS:
        return OBJECT3D_METHOD_ADDRS
    d = json.loads((REPO / 'data' / 'annotations' / 'structs' / 'Object3D.json')
                   .read_text(encoding='utf-8'))
    OBJECT3D_METHOD_ADDRS = {int(k, 16) for k in (d.get('methods') or {})}
    return OBJECT3D_METHOD_ADDRS


def test_resolve_targets_none_is_full():
    """二者都 None = 全量（向后兼容）。"""
    assert resolve_targets(None, None) is None


def test_resolve_targets_by_addr():
    out = resolve_targets({0x429ee0}, None)
    assert out == {0x429ee0}


def test_resolve_targets_by_class():
    addrs = _load_object3d_addrs()
    assert addrs, 'Object3D.json 应有 methods'
    out = resolve_targets(None, 'Object3D')
    assert out == addrs


def test_resolve_targets_unknown_class_raises():
    with pytest.raises(ValueError):
        resolve_targets(None, 'NoSuchClass_ZZZ')


def test_resolve_targets_addr_and_class_conjunction():
    """addr 与 class 同时给 ⇒ 取交集（收窄，非并集）。"""
    addrs = _load_object3d_addrs()
    one = next(iter(addrs))
    assert resolve_targets({one}, 'Object3D') == {one}
    assert resolve_targets({0x1}, 'Object3D') == set()     # 不相交 => 空


# ---- 射程 export 不污染主目录（守卫，实现后必须过）----

def test_scoped_export_output_dir_is_isolated():
    """射程 export 的输出目录必须与主 decomp 目录不同。

    这是设计要点 0 的守卫：若实现把射程结果写进主 asm/pal3/decomp/，
    collect_methods() 生成的头会残缺（只剩 1 个方法签名）。
    """
    from pipeline.gen.stages.collect import scoped_decomp_dir
    main_dir = REPO / 'asm' / 'pal3' / 'decomp'
    scoped = scoped_decomp_dir('/tmp/scoped_out')
    assert Path(scoped) != main_dir
    assert main_dir not in Path(scoped).parents
