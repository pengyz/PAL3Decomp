"""j_D3DX 三名正名（spec §7 #2）测试——A 级证据三定谳（dx_static §2.2 / thunk T11）。

  0x4B8200 j_D3DXVec3TransformCoord = 错名：真身 random-lerp（if a==b return a;
  else a+(rand()%10000+1)*flt_56F494*(b-a)，66B）⇒ 语义名 RandLerpF + float(float,float)
  0x542533 j_D3DXVec3TransformCoord_0 = PSGP 跳板 jmp[0x6090C4]，槽#7=c_D3DXVec3Normalize
    （157B 逐字节）⇒ 声明走 <d3dx9math.h> D3DXVec3Normalize
  0x544771 j_D3DXMatrixMultiply = PSGP 跳板 jmp[0x609134]，槽#35=c_D3DXQuaternionSlerp
    （227B 逐字节）⇒ 声明走 <d3dx9math.h> D3DXQuaternionSlerp

运行: python3 tests/test_d3dx_naming.py
"""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

FN = json.load(open(ROOT / 'data/annotations/functions.json'))


def test_4b8200_randlerpf_semantic_name_and_signature():
    e = FN['0x004B8200']
    assert e['name'] == 'RandLerpF'                      # 语义名（行为证据：random-lerp）
    assert e['name'] != 'j_D3DXVec3TransformCoord'       # 错名退役
    assert 'float' in e['signature'] and 'void *' not in e['signature']  # 真形 float(float,float)
    assert '__cdecl' in e['signature'] and '__stdcall' not in e['signature']  # plain ret=cdecl（P3 约定锁）
    assert '_todo_' not in e['name'] and 'j_' not in e['name']


def test_542533_routes_d3dxvec3normalize():
    e = FN.get('0x00542533')
    assert e and e['name'] == 'D3DXVec3Normalize'        # 槽#7 157B 逐字节证据
    assert 'D3DXVec3Normalize' in e['signature'] or 'D3DXVECTOR3' in e['signature']
    assert 'd3dx9math' in e.get('source', '')            # 声明路由证据入账
    assert '__stdcall' in e['signature']                  # WINAPI 约定锁（P1/P3，map YG 实证）
    assert e.get('declaration_only') is True              # 声明收编形（防真双注）


def test_544771_routes_d3dxquaternionslerp():
    e = FN.get('0x00544771')
    assert e and e['name'] == 'D3DXQuaternionSlerp'      # 槽#35 227B 逐字节证据
    assert 'D3DXQuaternionSlerp' in e['signature'] or 'D3DXQUATERNION' in e['signature']
    assert 'd3dx9math' in e.get('source', '')
    assert '__stdcall' in e['signature']                  # WINAPI 约定锁
    assert e.get('declaration_only') is True              # 声明收编形
