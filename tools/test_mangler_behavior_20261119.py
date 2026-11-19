#!/usr/bin/env python3
"""[行为面钉死 2026-11-19] 双 mangle 器差分测试——收编前钉死 apply 本地
_mangle_vc6 与 vc6_mangler.mangle 的行为全集。

背景: apply 类方法路径走本地 _mangle_vc6（简化拼装，缺 dtor 特形码 ??1/??_G），
全局路径已委派 vc6_mangler（完整实现）——双副本分叉债（文件内 TODO 自证）。
N18 名槽归一后 dtor 名=~X（含 ~），本地版产出 ?~...@ 非法名 → set_name 失败
→ dtor 名永不进 IDB → 语料调用点恒渲染旧名（PalScript::_PalScript 案）。

本测试三层断言:
  [L1 合法性] 输出必为合法 IDA 名（禁 '~'，字符面受控）
  [L2 语法面] VC6 特形码钉死: ~X→??1前缀, deleting(_sdtor/flags)→??_G,
              ctor→??0, 常规→'?' 单前缀 + 类链在场
  [L3 差分面] 双器逐案对比, 分歧分类登记（非法名/良性差异/行为缺失）

用法: python3 tools/test_mangler_behavior_20261119.py [--save-golden]
产出: stdout 结报 + --save-golden 时写 data/status/mangler_golden_20261119.json
"""
import json
import os
import re
import sys
import types
from pathlib import Path

REPO = Path(__file__).parent.parent
sys.path.insert(0, str(REPO / 'pipeline'))
sys.path.insert(0, str(REPO / 'pipeline' / 'ida'))

# ── AST 提取: 本地 _mangle_vc6 + 依赖 (不导入 apply_annotations 整模块) ──
import ast

_src = (REPO / 'pipeline/ida/apply_annotations.py').read_text(encoding='utf-8')
_tree = ast.parse(_src)
_needed = {'_mangle_vc6'}
_funcs = {n.name: n for n in _tree.body if isinstance(n, ast.FunctionDef)}
_segments = []
_seen = set()
_work = list(_needed)
while _work:
    nm = _work.pop()
    if nm in _seen or nm not in _funcs:
        continue
    _seen.add(nm)
    node = _funcs[nm]
    _segments.append(ast.get_source_segment(_src, node))
    for sub in ast.walk(node):
        if isinstance(sub, ast.Name) and sub.id.startswith('_') and sub.id in _funcs and sub.id != nm:
            _work.append(sub.id)
# 常量: 全部模块级 _VC6*/_CC* 赋值
for node in _tree.body:
    if isinstance(node, (ast.Assign, ast.AnnAssign)):
        targets = []
        if isinstance(node, ast.Assign):
            targets = [t.id for t in node.targets if isinstance(t, ast.Name)]
        elif isinstance(node, ast.AnnAssign) and isinstance(node.target, ast.Name):
            targets = [node.target.id]
        if any(tg.startswith('_VC6') or tg.startswith('_CC') for tg in targets):
            _segments.append(ast.get_source_segment(_src, node))
_ns = {'re': re}
import types as _types
for _ida_mod in ('ida_typeinf', 'ida_funcs', 'ida_name', 'idc'):
    _ns[_ida_mod] = _types.ModuleType(_ida_mod)
# 提取只保留 mangle 纯函数; 引用 ida_* 的助手降级为报错桩 (mangle 主路径不触)
for _seg in _segments:
    try:
        exec(_seg, _ns)
    except Exception:
        pass
_local_mangle = _ns.get('_mangle_vc6')
# [收编 2026-11-19] 本地 _mangle_vc6 已删除 — _local_mangle=None 时差分层跳过,
# 测试职能转为 vc6_mangler 单器行为面验收 (L1/L2 全绿 + deleting 支持)

import vc6_mangler as VM

# ── 电池 ──
# [合成族] 形态全集覆盖
SYNTH = [
    # 常规方法 (返型×参数×cc)
    ('UIListBox', 'Update', 'void __thiscall(UIListBox *this)'),
    ('UIListBox', 'Render', 'char __thiscall(UIListBox *this)'),
    ('CCBUI', 'GetTargetRole', 'CCBUI *__thiscall(CCBUI *this, int a2)'),
    ('Array', 'Insert', 'void *__thiscall(Array *this, void *pElem, void *pEnd)'),
    ('LineupUI', 'Update', 'int __thiscall(LineupUI *this, int a2, int a3)'),
    ('gbActor', 'GetActionDuration', 'float __thiscall(gbActor *this)'),
    ('Foo', 'Bar', 'int __cdecl(void)'),                       # 静态/cdecl
    ('AStarPathFinder::NODE', 'FindInOpen', 'int __thiscall(AStarPathFinder::NODE *this, int a2)'),  # 嵌套类
    # ctor
    ('CUtil', 'CUtil', 'CUtil *__thiscall(CUtil *this)'),
    # dtor complete 形 (~X, 无形参)
    ('PalScript', '~PalScript', 'void __thiscall(PalScript *this)'),
    ('SceneMgr', '~SceneMgr', 'void __thiscall(SceneMgr *this)'),
    # dtor deleting 形 (hexrays 渲染: 返 int/void* + flags 参)
    ('Actor', '~Actor', 'void __thiscall(Actor *this, int a2)'),
    ('ParticleEffect', '~ParticleEffect', 'virtual int __thiscall(ParticleEffect *this, int a2)'),
    ('UIMap', '~UIMap', 'virtual void *__thiscall(UIMap *this, UIWnd Block, char a3)'),
    ('WeatherEffectNode', '~WeatherEffectNode', 'void *__thiscall(WeatherEffectNode *this, gbGeomNode Block, char a3)'),
    # 旧形态名 (下划线时代产物, N18 前的 IDB 地层)
    ('PalScript', '_PalScript', 'void __thiscall(PalScript *this)'),
    ('UIWnd', '_scalar_dtor', 'void __thiscall(UIWnd *this)'),
    ('UIButton', '_sdtor_14', 'void __thiscall(UIButton *this)'),
]

IDA_SAFE_RE = re.compile(r'^[?@$_A-Za-z0-9]+$')

def l1_valid(out):
    """[L1] 合法 IDA 名: 禁 '~', 字符面受控, 非空"""
    if not out:
        return False, '空输出'
    if '~' in out:
        return False, '含 ~ (IDA 标识符非法)'
    if not IDA_SAFE_RE.match(out):
        return False, '字符面越界: %r' % out
    return True, ''

def l2_grammar(cls, meth, out, deleting=False):
    """[L2] VC6 特形码语法"""
    errs = []
    base = cls.split('::')[-1]
    if meth == cls or meth == base and meth[0].isupper() and cls.endswith(meth) and meth == base:
        if not out.startswith('??0'):
            errs.append('ctor 应 ??0 前缀: %r' % out)
        return errs
    if meth.startswith('~'):
        want = '??_G' + '@'.join(reversed(cls.split('::'))) + '@@UAEPAXI@Z' if deleting else None
        if deleting:
            if not out.startswith('??_G'):
                errs.append('deleting 应 ??_G 前缀: %r' % out)
        elif not out.startswith('??1'):
            errs.append('dtor 应 ??1 前缀: %r' % out)
        if '@' not in out or (base + '@') not in out:
            errs.append('类链缺失: %r' % out)
        return errs
    if re.match(r'^(_s(dtor|calar_dtor)(_\d+)?)$', meth):
        if not out.startswith('??_G'):
            errs.append('_sdtor 形应 ??_G 前缀: %r' % out)
        return errs
    if not out.startswith('?') or out.startswith('??'):
        errs.append('常规方法应 ? 单前缀: %r' % out)
    if (base + '@') not in out:
        errs.append('类链缺失: %r' % out)
    return errs

def run_battery(save_golden=False):
    rows = []
    l1_fail_local = l1_fail_vc6 = 0
    l2_fail_local = l2_fail_vc6 = 0
    print('=== L1/L2 行为面 (合成电池 %d 案) ===' % len(SYNTH))
    for cls, meth, sig in SYNTH:
        deleting = 'deleting' in (SYNTH_FLAGS.get((cls, meth), []))
        b = VM.mangle(cls, meth, sig, deleting=deleting)
        ok_b, why_b = l1_valid(b)
        e2_b = l2_grammar(cls, meth, b, deleting)
        l1_fail_vc6 += 0 if ok_b else 1
        l2_fail_vc6 += len(e2_b)
        rows.append({'cls': cls, 'meth': meth, 'sig': sig, 'deleting': deleting,
                     'vc6': b, 'l1': why_b or 'ok', 'l2': e2_b})
        print(' %-18s L=%-46s %s' % (meth[:18], (b or '(空)')[:46],
              '✓' if ok_b and not e2_b else '✗'))
        if not ok_b:
            print('   [L1✗] %s' % why_b)
        if e2_b:
            print('   [L2✗] %s' % '; '.join(e2_b))
    print()
    print('L1 失败: 本地 %d / vc6 %d' % (l1_fail_local, l1_fail_vc6))
    print('L2 失败: 本地 %d / vc6 %d' % (l2_fail_local, l2_fail_vc6))

    # ── [L3 全量差分] 注解 methods 真实条目 (dtor 族全量 + 常规抽样) ──
    print()
    print('=== L3 真实注解全量差分 ===')
    SDIR = REPO / 'data/annotations/structs'
    n_total = n_eq = n_div = 0
    div_classes = {}
    div_dtor_invalid = []
    for fp in sorted(SDIR.glob('*.json')):
        try:
            d = json.loads(fp.read_text(encoding='utf-8'))
        except Exception:
            continue
        cls = d.get('name') or fp.stem
        for k, m in (d.get('methods') or {}).items():
            if not isinstance(m, dict):
                continue
            sm = m.get('sig_model') or {}
            params = sm.get('params') or []
            psig = '%s __thiscall(%s *this%s)' % (
                sm.get('return') or 'void', cls,
                ''.join(', %s %s' % (p.get('type') or 'int', p.get('name') or ('a%d' % i))
                        for i, p in enumerate(params)))
            meth = str(m.get('name') or '')
            if not meth:
                continue
            b = VM.mangle(cls, meth, psig,
                          deleting='deleting' in (m.get('flags') or []))
            n_total += 1
            ok, why = l1_valid(b)
            e2 = l2_grammar(cls, meth, b,
                            'deleting' in (m.get('flags') or []))
            if not ok or e2:
                n_div += 1
                div_classes[why or ';'.join(e2)] = div_classes.get(why or ';'.join(e2), 0) + 1
                if n_div <= 5:
                    div_dtor_invalid.append((cls, meth, b, why or ';'.join(e2)))
            else:
                n_eq += 1
    print('真实条目 %d: 验收通过 %d / 违规 %d' % (n_total, n_eq, n_div))
    print('违规分类:', div_classes)
    if div_dtor_invalid:
        print('样例:', div_dtor_invalid)

    if save_golden:
        out = {
            '_doc': '双 mangle 器行为面钉死 golden 2026-11-19 (收编前快照)',
            'battery': rows,
            'summary': {'l1_fail_local': l1_fail_local, 'l1_fail_vc6': l1_fail_vc6,
                        'l2_fail_local': l2_fail_local, 'l2_fail_vc6': l2_fail_vc6,
                        'real_total': n_total, 'real_eq': n_eq, 'real_div': n_div,
                        'div_classes': div_classes},
        }
        gp = REPO / 'data/status/mangler_golden_20261119.json'
        gp.write_text(json.dumps(out, indent=1, ensure_ascii=False), encoding='utf-8')
        print('\ngolden -> %s' % gp)

SYNTH_FLAGS = {
    ('Actor', '~Actor'): ['deleting'],
    ('ParticleEffect', '~ParticleEffect'): ['deleting'],
    ('UIMap', '~UIMap'): ['deleting'],
    ('WeatherEffectNode', '~WeatherEffectNode'): ['deleting'],
}

if __name__ == '__main__':
    run_battery(save_golden='--save-golden' in sys.argv)
