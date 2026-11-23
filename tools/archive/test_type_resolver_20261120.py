#!/usr/bin/env python3
"""[REF resolver 行为测试 2026-11-20] pipeline/type_resolver.py 正确性回归网。

背景: REF 门=硬门(check 阻断), 但 resolver 解析逻辑此前只有普查迭代式验证
(门活性 84:1 + 零假阳性校准 + [5b] 同源交叉)——无行为测试=无回归安全网
(C9 门禁双重死因教训: 门禁写了≠跑过, 行为未测=未知)。

覆盖:
  A. _base_token 星号粘合/const 尾/修饰前缀/数组 (实病回归: 'X * *'案)
  B. _split_top 模板深度感知切分
  C. _resolve_param 参数名剥除 ('int *pRect'/'**ppOnes'/复合primitive/...)
  D. _resolve_one 病形捕获 (it/*/cha/*this/static int/名吞return) —
     每形=普查84项的一个实病代表
  E. _resolve_one 合法形态 (函数指针/签名形/模板/嵌套四形/内联dict/信任前缀)
  F. registry 变体与信任域活性
  G. near_miss 拼写侦察

用法: python3 tools/test_type_resolver_20261120.py
"""
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__))), 'pipeline'))

import type_resolver as tr

_PASS = 0
_FAIL = []


def check(name, cond, detail=''):
    global _PASS
    if cond:
        _PASS += 1
    else:
        _FAIL.append('%s %s' % (name, detail))


# ---------------------------------------------------------------- A. base_token

def test_base_token():
    bt = tr._base_token
    # 实病回归: 'X * *' 星号带空格(首跑多令牌误报根因)
    check('A1 星号粘合', bt('gbTexture * *') == 'gbTexture', repr(bt('gbTexture * *')))
    check('A2 单星', bt('gbTexture *') == 'gbTexture', repr(bt('gbTexture *')))
    check('A3 双星无空', bt('UIWnd**') == 'UIWnd', repr(bt('UIWnd**')))
    check('A4 const指针', bt('int *const') == 'int', repr(bt('int *const')))
    check('A5 const前缀', bt('const char *') == 'char', repr(bt('const char *')))
    check('A6 unsigned修饰', bt('unsigned int') == 'int', repr(bt('unsigned int')))
    check('A7 数组后缀', bt('int[10]') == 'int', repr(bt('int[10]')))
    check('A8 数组+指针', bt('ARC_RoleAtt[200]') == 'ARC_RoleAtt')
    check('A9 struct前缀', bt('struct gbOBBox &') == 'gbOBBox', repr(bt('struct gbOBBox &')))
    check('A10 纯名', bt('Actor') == 'Actor')
    check('A11 嵌套名保真', bt('SceneObj::Common_State') == 'SceneObj::Common_State')
    check('A12 空串', bt('') == '')
    check('A13 裸星', bt('*') == '', repr(bt('*')))


# ---------------------------------------------------------------- B. split_top

def test_split_top():
    st = tr._split_top
    r = st('SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> >')
    check('B1 模板深度感知', len(r) == 2, repr(r))
    check('B2 首元', r[0] == 'SceneObj::Common_State')
    check('B3 次元含嵌套', r[1].startswith('std::deque<'), repr(r[1]))
    r2 = st('int, char *, float')
    check('B4 平参数', r2 == ['int', 'char *', 'float'], repr(r2))


# ---------------------------------------------------------------- C. resolve_param

def _param_fail(r, pt):
    n0 = len(r.failures)
    r._resolve_param(pt, 'T', 'x', 'p')
    return len(r.failures) > n0


def test_resolve_param():
    # live resolver: 已知类=Actor/gbTexture/BOOL/HWND 等
    r = tr.Resolver()
    check('C1 类型+名(int *pRect)', not _param_fail(r, 'int *pRect'))
    check('C2 双星名(**ppOnes)', not _param_fail(r, 'UIWnd **ppOnes'))
    check('C3 无星名(HWND hWnd)', not _param_fail(r, 'HWND hWnd'))
    check('C4 复合primitive(unsigned __int64 volume)',
          not _param_fail(r, 'unsigned __int64 volume'))
    check('C5 const类型名(const D3DXQUATERNION *pQ1)',
          not _param_fail(r, 'const D3DXQUATERNION *pQ1'))
    check('C6 varargs(...)', not _param_fail(r, '...'))
    check('C7 纯类型(void)', not _param_fail(r, 'void'))
    # 参数名剥不掉的病型: 名含寄存器注记 = 病, 必须失败
    check('C8 寄存器注记名(int a1@<ecx>)', _param_fail(r, 'int a1@<ecx>'))
    # 拼写基型必须失败
    check('C9 拼写基型 unsined', _param_fail(r, 'unsined char bFlag'))
    check('C10 拼写基型 cha', _param_fail(r, 'cha c'))


# ---------------------------------------------------------------- D/E. resolve_one

def _one_fail(r, t):
    n0 = len(r.failures)
    r._resolve_one(t, 'T', 'x', 'f')
    return len(r.failures) > n0


def _one_reason(r, t):
    n0 = len(r.failures)
    r._resolve_one(t, 'T', 'x', 'f')
    if len(r.failures) > n0:
        return r.failures[-1][5]
    return None


def test_resolve_one_diseases():
    r = tr.Resolver()
    check('D1 裸star(PopStack案)', _one_fail(r, '*'))
    check('D2 it(CCBStage案)', _one_fail(r, 'it'))
    check('D3 this污染(UISceneMap案)', _one_fail(r, 'CCBFiveNimbusWindow *this'))
    check('D4 static int', _one_fail(r, 'static int'))
    check('D5 名吞return(RandomPickValues案)', _one_fail(r, 'int RandomPickValues'))
    check('D6 限定名吞(CEffCylinder::Update案)',
          _one_fail(r, 'int CEffCylinder::Update'))
    check('D7 寄存器注记', _one_fail(r, 'int a1@<ecx>'))
    check('D8 拼写unsined', _one_fail(r, 'unsined char'))
    check('D9 拼写cha', _one_fail(r, 'cha'))
    check('D10 拼写unsigned cha', _one_fail(r, 'unsigned cha'))
    check('D11 幽灵嵌套(Role::ScriptCmd案)',
          _one_fail(r, 'Role::ScriptCmd'))
    # D12 翻案20261120: gbOBBox有声明(struct GBAPI gbOBBox, gbengine_types.h:217
    # ——初判漏看GBAPI前缀形)。真病=OBBox拼写(struct OBBox *, GetBBox return案)
    check('D12a gbOBBox可解析(GBAPI形)', not _one_fail(r, 'gbOBBox'))
    check('D12b OBBox拼写病', _one_fail(r, 'struct OBBox *'))
    check('D13 空串不报(被上层空守卫)',
          not _one_fail(r, ''))
    # 病因文案侦察
    check('D14 near_miss提示(int案)', 'int?' in (_one_reason(r, 'it') or ''))


def test_resolve_one_legal():
    r = tr.Resolver()
    check('E1 函数指针形', not _one_fail(r, 'int (__thiscall *)(void *, unsigned int)'))
    check('E2 签名形带名', not _one_fail(
        r, 'BOOL __cdecl PointInRect(int *pRect, int *pPoint)'))
    check('E3 签名形无名', not _one_fail(r, 'BOOL __cdecl(HWND hWnd)'))
    check('E4 签名形无cc', not _one_fail(r, 'bool(CHAR *lpSubKey, DWORD dwDisposition)'))
    check('E5 模板std::vector', not _one_fail(
        r, 'std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >'))
    check('E6 模板嵌套queue', not _one_fail(
        r, 'std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >'))
    check('E7 嵌套::形(SceneObj案)', not _one_fail(r, 'SceneObj::Common_State'))
    check('E8 嵌套_形(json名)', not _one_fail(r, 'SceneObj_Common_State'))
    check('E9 内联dict类型', not _one_fail(
        r, {'struct': [{'offset': 0, 'name': 'a', 'type': 'int'}]}))
    check('E10 D3D前缀信任', not _one_fail(r, 'D3DXVECTOR3 *'))
    check('E11 IUnknown信任', not _one_fail(r, 'IUnknown *'))
    check('E12 CHAR信任', not _one_fail(r, 'CHAR *'))
    check('E13 嵌套双_形(_Console案)',
          not _one_fail(r, '_Console__ConCmd') or 'Console' in r.reg)
    # FP 模板混嵌: FP 参数里带模板
    check('E14 FP参数含模板', not _one_fail(
        r, 'int (__thiscall *)(std::vector<int> &)'))


# ---------------------------------------------------------------- F. registry

def test_registry():
    reg = tr.build_registry()
    check('F1 实类(Actor)', 'Actor' in reg)
    check('F2 ida型(_DWORD)', '_DWORD' in reg)
    check('F3 gbengine(gbVec3D)', 'gbVec3D' in reg)
    check('F4 聚合typedef(_PVFV)', '_PVFV' in reg)
    check('F5 枚举(ARC_WuLing)', 'ARC_WuLing' in reg)
    check('F6 嵌套变体(::形)', 'SceneObj::Common_State' in reg)
    check('F7 嵌套变体(_形)', 'SceneObj_Common_State' in reg)
    check('F8 detached(PlayerMgr::PoisonState)', 'PlayerMgr::PoisonState' in reg)
    check('F9 builtin域', reg.get('void', ('',))[0] == 'builtin')
    check('F10 win32域', reg.get('BOOL', ('',))[0] == 'win32sdk')


# ---------------------------------------------------------------- G. near_miss

def test_near_miss():
    reg = tr.build_registry()
    check('G1 cha→char', tr._near_miss('cha', reg) == 'char',
          repr(tr._near_miss('cha', reg)))
    check('G2 it→int', tr._near_miss('it', reg) == 'int',
          repr(tr._near_miss('it', reg)))


# ---------------------------------------------------------------- H. 门活性锚

def test_live_anchor():
    """活数据锚: 现行普查=84。数据修复战每消一项, 此锚同步降数——
    锚失配=数据或resolver变更信号(防静默漂移)。"""
    failures, _w, nrefs, nreg, edges = tr.collect()
    check('H1 普查位点数稳定', nrefs == 18099, 'nrefs=%d' % nrefs)
    check('H2b 边模型kind齐全', all(e[2] in ('value', 'ref') for e in edges))
    # include优化语义: 值边必须远多于...? 无先验, 只断言两类都非零
    check('H2c value/ref边都存在',
          any(e[2] == 'value' for e in edges) and any(e[2] == 'ref' for e in edges))
    check('H2 普查失败锚84', len(failures) == 84,
          'failures=%d (数据修复后更新此锚)' % len(failures))
    # 已知实病必须在列(门活性:C9教训)
    owners = set((f[0], str(f[1])) for f in failures)
    check('H3 PopStack(*)在列', ('AStarPathFinder', '0x00401780') in owners)
    check('H4 CCBStage(it)在列', any(o[0] == 'CCBStage' for o in owners))


def test_classify_kind():
    ck = tr.classify_kind
    check('K1 成员按值', ck('CameraCtrl') == 'value')
    check('K2 指针', ck('CameraCtrl *') == 'ref')
    check('K3 引用', ck('CameraCtrl &') == 'ref')
    check('K4 值数组', ck('ARC_RoleAtt[200]') == 'value')
    check('K5 指针数组', ck('gbTexture * *[4]') == 'ref')
    check('K6 函数指针', ck('int (__thiscall *)(void *, unsigned int)') == 'ref')
    check('K7 值模板', ck('std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >') == 'value')
    check('K8 指针模板', ck('std::vector<gbTexture *>') == 'ref')
    check('K9 内联dict', ck({'struct': []}) == 'value')
    check('K10 基类子对象(调用方强制value)',
          ck('UIWnd') == 'value')


def test_gbengine_harvest():
    edges = tr.harvest_header_edges(tr._GBENGINE_DIR, 'gbengine')
    check('V1 收割非空', len(edges) > 50, 'edges=%d' % len(edges))
    # gbActor.h 引用 gbOBBox(真产物边实证)
    owners = {}
    for h, base, kind, dom in edges:
        owners.setdefault(h, set()).add((base, kind))
    check('V2 gbActor→gbOBBox边', ('gbOBBox', 'ref') in owners.get('gbActor.h', set()),
          repr(sorted(owners.get('gbActor.h', set()))[:6]))
    check('V3 kind合法', all(e[2] in ('value', 'ref') for e in edges))


def main():
    test_base_token()
    test_split_top()
    test_resolve_param()
    test_resolve_one_diseases()
    test_resolve_one_legal()
    test_registry()
    test_near_miss()
    test_classify_kind()
    test_gbengine_harvest()
    test_live_anchor()
    total = _PASS + len(_FAIL)
    print('== type_resolver 行为测试 ==')
    print('PASS %d / %d' % (_PASS, total))
    for f in _FAIL:
        print('  FAIL:', f)
    return 1 if _FAIL else 0


if __name__ == '__main__':
    sys.exit(main())
