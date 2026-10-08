# tools/size_grid_gate.py
"""尺寸格门：假继承链的零假阴性检测。

判据（2026-10-08 对抗复核定稿）：
  1. 派生类尺寸 ≥ 每个基类尺寸（C++ 布局定理：派生类必须包含基类子对象）
  2. base_size 语义在本仓不一致（Role=96 是 sum；CEffSParticle=16 非 sum）
     ⇒ 仅 informational，不硬拒

实测：本门禁一票否决 KB 链（UIWnd=68 < SceneObj=1784 < CGameData=28268）。
"""
from typing import List, Tuple


def check_chain(derived_size: int,
                base_sizes: List[int],
                declared_base_size: int = None) -> Tuple[bool, str]:
    """检查继承链的尺寸格。返回 (ok, reason)。"""
    if not base_sizes:
        return True, 'no bases'
    for bs in base_sizes:
        if derived_size < bs:
            return False, (f'derived size {derived_size} < base size {bs} — '
                           '派生类必须包含基类子对象')
    # base_size 语义在本仓**不一致**（Role: 56+8+32=96 是 sum；
    # CEffSParticle: bases=12+36=48 但 base_size=16）⇒ **不做硬检查**，
    # 仅 informational（2026-10-08 对抗复核修正：原 sum 判据会误拒合法链）。
    if declared_base_size is not None:
        return True, f'ok (declared base_size {declared_base_size} not enforced)'
    return True, 'ok'
