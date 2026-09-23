"""D3DX 类型尺寸经 sdk_types 供表 —— sg_* 家族漂移根因（TDD）。

真值证据：二进制步长（sg_emitter relative_position@0x40→emission_scope@0x4C = 12；
sg_particle_data currgbcolor D3DXCOLOR@0x44→rotation@0x54 = 16）+ DirectX8 SDK。
"""
import sys
from pathlib import Path
PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT)); sys.path.insert(0, str(PROJECT_ROOT/'pipeline')); sys.path.insert(0, str(PROJECT_ROOT/'pipeline'/'gen'))
from stages import emit_headers as E

def test_d3dx_sizes():
    for t, want in (('D3DXVECTOR3',12),('D3DXVECTOR2',8),('D3DXVECTOR4',16),
                    ('D3DXMATRIX',64),('D3DXCOLOR',16),('D3DVECTOR',12)):
        got = E._estimate_member_size(t)
        assert got == want, '%s: 期望 %d 实得 %s' % (t, want, got)

if __name__ == '__main__':
    ok=fail=0
    for nm,fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try: fn(); print('  PASS',nm); ok+=1
            except Exception as e: print('  FAIL',nm,e); fail+=1
    print('Results: %d passed, %d failed'%(ok,fail)); sys.exit(1 if fail else 0)
