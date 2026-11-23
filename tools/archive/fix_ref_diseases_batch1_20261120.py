#!/usr/bin/env python3
"""[REF 病修复战 batch1 2026-11-20] 31→0 逐项定谳——resolver 84 普查的注解修复。

每项=REF 普查一个实病, 证据逐项落注。resolver 侧三启发式修同步(行为测试护网):
  R1. 签名形 left 剥 virtual/static 关键字('virtual BOOL __thiscall(...)'案:
      名剥启发误把 BOOL 当函数名——真名缺省形)
  R2. 签名形尾名剥正则放行限定名('int __cdecl CEffCylinder::Update(...)'案)
  R3. _resolve_param 剥尾名前先剥 @<reg> 注记('__userpurge(int a1@<ecx>...)'案)
  R4. REF 遍历跳过 pending sig_model(pending=声明未定谳, 非类型契约; CPK::Load 案)

注解修复(逐项证据):
  N1  CCBStage 'it'×6 + CEffQuad 'it'×1 → int
      (同条目兄弟参数 int 直证 + 参数名 n=任务索引语义)
  N2  CCBStageCam/CCBUI 'static int'×4 → int (存储类剥除)
  N3  PAL3::RandomPickValues 'int RandomPickValues' → int (名吞 return 剥名)
  N4  RenderTarget 0x4b4850 'unsigned cha'+'unsined char' → unsigned char ×2
  N5  Scene::AddRoleEntry 0x410990 'const int pRoleTriple[3]' → 'const int *'
      (导出直证: 'const int *__attribute__((...))' 指针形)
  N6  UISceneMap 0x451800 adjustor thunk 'CCBFiveNimbusWindow *this' 参数删
      (this 形参数永非 sig_model 合法项; thunk 体 jmp 转发, 参数表空)
  N7  AStarPathFinder::PopStack '*' → 'AStarPathFinder::NODE *'
      (导出直证: 'AStarPathFinder::NODE *__thiscall(...)')
  N8  gbOBBox::GetBBox 0x52f6c0 'struct OBBox *' → 'gbOBBox *'
      (拼写病: OBBox 无档案无声明; gbOBBox 有声明 gbengine_types.h:217)
  N9  CPK::Load return='Load' → pending=true
      (idb_name 反查档无体证据, return=名字污染; pending=未定谳正当态)
  N10 Role::ScriptCmd + CParticleSystem::TexCoordQuad → detached_nested_types
      (幽灵嵌套引用→detached 名字载体收录, PlayerMgr::PoisonState 先例:
       只被引用无成员数据的嵌套名)

用法: python3 tools/fix_ref_diseases_batch1_20261120.py [--dry]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
S = REPO / 'data' / 'annotations'

# ------------------------------------------------ resolver 启发式修 (R1-R3)
rp = REPO / 'pipeline' / 'type_resolver.py'
src = rp.read_text(encoding='utf-8')

# R1: left 剥 virtual/static
old = "                left_nocc = re.sub(r'\\b__\\w+\\b', ' ', left)"
new = ("                left_nocc = re.sub(r'\\b(__\\w+|virtual|static)\\b', ' ', left)"
       "   # R1: virtual/static 关键字剥(nameless form 案)")
if old in src:
    src = src.replace(old, new)
else:
    print('  R1 已应用过, 跳过(幂等)')

# R2: 尾名剥放行限定名
old = "                if ltoks and re.match(r'^[A-Za-z_]\\w*$', ltoks[-1]) and len(ltoks) > 1:"
new = "                if ltoks and re.match(r'^[A-Za-z_][\\w:]*$', ltoks[-1]) and len(ltoks) > 1:"
if old in src:
    src = src.replace(old, new)
else:
    print('  R2 已应用过, 跳过(幂等)')

# R3: 尾名剥前剥 @<reg> 注记
old = "        toks = s.split()\n        if (len(toks) >= 2 and re.match(r'^\\**[A-Za-z_]\\w*$', toks[-1])"
new = ("        toks = s.split()\n"
       "        if toks:\n"
       "            toks[-1] = re.sub(r'@<[^>]*>$', '', toks[-1])  # R3: @<reg> 注记剥\n"
       "        if (len(toks) >= 2 and re.match(r'^\\**[A-Za-z_]\\w*$', toks[-1])")
if old in src:
    src = src.replace(old, new)
else:
    print('  R3 已应用过, 跳过(幂等)')

# R4: REF 遍历跳过 pending
old = """        for addr, m in (d.get('methods') or {}).items():
            sm = m.get('sig_model') or {}
            if sm.get('return'):"""
new = """        for addr, m in (d.get('methods') or {}).items():
            sm = m.get('sig_model') or {}
            if sm.get('pending'):
                continue  # R4: pending=声明未定谳, 非类型契约(CPK::Load 案)
            if sm.get('return'):"""
if old in src:
    src = src.replace(old, new)
else:
    print('  R4 已应用过, 跳过(幂等)')

if not DRY:
    rp.write_text(src, encoding='utf-8')
print('resolver R1-R4 落地 (dry=%s)' % DRY)

# ------------------------------------------------ 注解修复 (N1-N10)
OPS = []


def fix_struct(cls, addr, mutate, note):
    fp = S / 'structs' / ('%s.json' % cls)
    d = json.loads(fp.read_text(encoding='utf-8'))
    m = d['methods'][addr]
    sm = m['sig_model']
    before = json.dumps(sm, ensure_ascii=False)[:90]
    if note in (m.get('name_note') or ''):
        OPS.append('%s %s: 已修过, 跳过(幂等)' % (cls, addr))
        return
    mutate(sm)
    m['name_note'] = (m.get('name_note') or '') + ' | ' + note
    if not DRY:
        fp.write_text(json.dumps(d, ensure_ascii=False, indent=1),
                      encoding='utf-8')
    OPS.append('%s %s: %s' % (cls, addr, before))


def _set_param_type(cls, addr, pidx, new_type, note):
    fix_struct(cls, addr, lambda sm: sm['params'][pidx].__setitem__(
        'type', new_type), note)


def _set_return(cls, addr, new_type, note):
    fix_struct(cls, addr, lambda sm: sm.__setitem__('return', new_type), note)


IT_NOTE = ('REF修复20261120: it→int (同条目兄弟参数int直证+参数名n任务索引语义, '
           'N1拼写病)')
for a in ('0x004fce00', '0x004fce70', '0x004fcfb0', '0x004fd0b0',
          '0x004fd1a0', '0x004fece0'):
    _set_param_type('CCBStage', a, 0, 'int', IT_NOTE)
_set_param_type('CEffQuad', '0x004d1ca0', 0, 'int', IT_NOTE)

ST_NOTE = ('REF修复20261120: static int→int (存储类关键字污染剥除, N2)')
for cls, a in (('CCBStageCam', '0x004e8450'), ('CCBStageCam', '0x004ea590'),
               ('CCBUI', '0x004e1f70'), ('CCBUI', '0x004e2430')):
    _set_return(cls, a, 'int', ST_NOTE)

_set_return('PAL3', '0x00569020', 'int',
            'REF修复20261120: int RandomPickValues→int (名吞return剥名, N3)')
_set_param_type('RenderTarget', '0x004b4850', 0, 'unsigned char',
                'REF修复20261120: unsigned cha→unsigned char (N4拼写)')
_set_param_type('RenderTarget', '0x004b4850', 1, 'unsigned char',
                'REF修复20261120: unsined char→unsigned char (N4拼写)')
_set_param_type('Scene', '0x00410990', 0, 'const int *',
                'REF修复20261120: const int pRoleTriple[3]→const int * '
                '(导出直证const int*指针形, N5参数名污染清除)')


def _drop_this_param(sm):
    sm['params'] = [p for p in (sm.get('params') or [])
                    if 'this' not in str(p.get('type') or '')]  # '*this'子串形实证


fix_struct('UISceneMap', '0x00451800', _drop_this_param,
           'REF修复20261120: CCBFiveNimbusWindow *this参数删(this形永非'
           'sig_model合法项; adjustor thunk jmp转发, N6)')
_set_return('AStarPathFinder', '0x00401780', 'AStarPathFinder::NODE *',
            'REF修复20261120: *→AStarPathFinder::NODE * (导出直证, N7空基型)')
_set_return('gbOBBox', '0x0052f6c0', 'gbOBBox *',
            'REF修复20261120: struct OBBox *→gbOBBox * (OBBox无档案无声明, '
            'gbOBBox声明gbengine_types.h:217, N8拼写)')


def _pending(sm):
    sm['pending'] = True
    sm['return'] = 'void'


fix_struct('CPK', '0x004b6d80', _pending,
           'REF修复20261120: return=Load(名字污染, idb_name反查档无体证据)'
           '→pending=true未定谳正当态, 真返回型待体证据(N9)')

# N10: detached 收录幽灵嵌套引用
dfp = S / 'detached_nested_types.json'
dj = json.loads(dfp.read_text(encoding='utf-8'))
for owner, nt in (('Role', 'ScriptCmd'),
                  ('CParticleSystem', 'TexCoordQuad')):
    dj.setdefault(owner, {}).setdefault(nt, {
        'kind': 'struct',
        '_note': ('REF修复20261120(N10): 幽灵嵌套引用收录——%s::%s 被引用'
                  '(std::queue元素形)但全树零声明; 本文件=名字载体'
                  '(PlayerMgr::PoisonState先例); 尺寸未定谳, 布局重划时随'
                  '成员普查定谳' % (owner, nt)),
    })
if not DRY:
    dfp.write_text(json.dumps(dj, ensure_ascii=False, indent=1),
                   encoding='utf-8')
OPS.append('detached_nested_types: Role::ScriptCmd + CParticleSystem::'
           'TexCoordQuad 收录')

if not DRY:
    print('归档位: ops=%d' % len(OPS))
for op in OPS:
    print(' ', op)
print('done (dry=%s)' % DRY)
