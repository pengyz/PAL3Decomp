#!/usr/bin/env python3
"""[S1 签名模型层 2026-11-16 用户裁定] 签名的结构化唯一真值。

背景: 签名以字符串承接导致每个消费端各自解析、各自缺陷
(C9三轮解析bug/C6限定名误报/slot sig覆盖methods真值)。
本模块 = 唯一摄取解析器 + 确定性渲染器 + 校验器 + 结构比较。

结构节点(SigNode dict):
  {"return": "void",            # 返回类型表达式(规范串)
   "cc": "thiscall",            # 调用约定(无__前缀)
   "params": [                  # 有序参数对象数组
     {"type": "int", "name": "nMsg"},          # name可null(未知不伪造)
     {"type": "unsigned int", "name": "wParam"}],
   "varargs": false,            # 可变参
   "pending": false}            # 零证据诚实中间态

双消费边界: 门禁读 type序列+return存在性; 语义层读参数名; 发射器全读。
"""
import re

KNOWN_CC = {'thiscall', 'cdecl', 'stdcall', 'fastcall'}
BUILTIN_WORDS = {'int', 'char', 'float', 'double', 'bool', 'void', 'long', 'short',
                 'unsigned', 'signed', 'const', 'BOOL', 'DWORD', 'WORD', 'BYTE',
                 'UINT', 'ULONG', 'LONG', 'LPCTSTR', 'LPCTSTR'}


def parse_signature(s):
    """Hex-Rays形态签名字符串 → SigNode dict。失败返回 None(调用方如实记账)。"""
    if not s or not isinstance(s, str):
        return None
    t = s.strip()
    if not t or '(' not in t or ')' not in t:
        return None
    if t.startswith('virtual'):
        t = t[7:].strip()  # decomp形带virtual前缀
    m = re.match(r'^(.*?)\s*(__\w+)?\s*\((.*)\)\s*$', t)
    if not m:
        return None
    head = (m.group(1) + ' ' + (m.group(2) or '')).strip()
    ret_cc = head.split()
    # head形态: [ret] [__cc] [QualName] — QualName含::或紧跟(前的末段标识符
    cc = None
    ret_words = []
    qual = None
    for w in ret_cc:
        if w.startswith('__') and w[2:].lower() in KNOWN_CC:
            cc = w[2:].lower()
        elif '::' in w:
            qual = w
        else:
            ret_words.append(w)
    ret = ' '.join(ret_words)
    if not ret:
        return None  # 无返回型='()'类退化输入, 拒绝
    # varargs
    raw_params = m.group(3)
    varargs = '...' in raw_params
    raw_params = raw_params.replace('...', '').strip()
    params = []
    if raw_params:
        for p in raw_params.split(','):
            p = p.strip()
            if not p:
                continue
            words = p.split()
            if len(words) >= 2 and re.match(r'^[A-Za-z_]\w*$', words[-1]) \
                    and words[-1].lower() not in BUILTIN_WORDS and not words[-1].startswith('__'):
                params.append({'type': ' '.join(words[:-1]), 'name': words[-1]})
            else:
                params.append({'type': ' '.join(words), 'name': None})
    # this参数剥除(decomp形: 'CEffObj *this'/'UIWnd *this'首参——含无名'X *this')
    if params:
        p0 = params[0]
        _t0 = (p0.get('type') or '').rstrip()
        if p0.get('name') == 'this' or _t0.endswith('* this') or _t0.endswith('*this'):
            params.pop(0)
    return {'return': ret or None, 'cc': cc, 'params': params,
            'varargs': varargs, 'pending': False}


def render(node):
    """SigNode → 确定性规范声明串(无类限定名, 参数名保留)。"""
    if not node:
        return None
    if node.get('pending'):
        return None
    cc = ('__' + node['cc']) if node.get('cc') else ''
    ps = []
    for p in (node.get('params') or []):
        ps.append(('%s %s' % (p['type'], p['name'])).strip() if p.get('name') else p['type'])
    if node.get('varargs'):
        ps.append('...')
    return '%s %s(%s)' % (node.get('return') or 'void', cc, ', '.join(ps))


def render_decl(node, cls_name, name):
    """SigNode → 成员声明行 'ret name(params)'(无cc——成员声明不带)。"""
    if not node or node.get('pending'):
        return None
    ps = []
    for p in (node.get('params') or []):
        ps.append(('%s %s' % (p['type'], p['name'])).strip() if p.get('name') else p['type'])
    if node.get('varargs'):
        ps.append('...')
    return '%s %s(%s)' % (node.get('return') or 'void', name, ', '.join(ps))


def validate(node):
    """Schema校验 → 错误列表(空=合法)。"""
    errs = []
    if not isinstance(node, dict):
        return ['node非dict']
    if not node.get('pending'):
        if not node.get('return'):
            errs.append('return缺失')
        if node.get('cc') is not None and node.get('cc') not in KNOWN_CC:
            errs.append('cc未知: %s' % node.get('cc'))
        for i, p in enumerate(node.get('params') or []):
            if not p.get('type'):
                errs.append('param[%d]缺type' % i)
            nm = p.get('name')
            if nm is not None and not re.match(r'^[A-Za-z_]\w*$', nm):
                errs.append('param[%d] name非法: %r' % (i, nm))
    return errs


def params_equal(a, b):
    """可观测契约判等: 参数类型序列一致(参数名不参与——C2555不看名字)。"""
    pa = [p['type'] for p in (a.get('params') or [])]
    pb = [p['type'] for p in (b.get('params') or [])]
    return pa == pb


def returns_absent(node):
    """返回存在性: void=True(无返回)。"""
    return (node.get('return') or 'void').split()[-1].lower() == 'void'


def c2555_conflict(derived, base):
    """C2555精确判据: 参数契约一致 而返回存在性不同。"""
    return params_equal(derived, base) and returns_absent(derived) != returns_absent(base)


def _norm_type(t):
    """类型串归一: 折叠空白 + 补*/&前空格(仅排版差异, 不做语义等价改写)。
    'void*' vs 'void *' 同型实证(CEffAction AllocEffect假阳性20261116)。"""
    s = ' '.join(str(t or '').split())
    s = s.replace('*', ' * ').replace('&', ' & ')
    return ' '.join(s.split())


def override_check(derived, base):
    """[重载正确性判定 2026-11-16] C++ virtual override 签名一致性判定。

    派生虚函数 override 基类同名虚函数 ⟺ cc相同 + 参数类型序列相同(参数名不参与,
    C2555不看名字) + 返回型相同 + varargs相同。逐维度报告结构化差异, 不做协变放宽
    (MSVC6本工程无协变返回实例, 放宽=伪造兼容)。
    返回 {'compatible': bool, 'mismatches': [str]}; 任一节点pending → {'pending': True}。
    """
    if derived.get('pending') or base.get('pending'):
        return {'pending': True}
    mm = []
    if (derived.get('cc') or None) != (base.get('cc') or None):
        mm.append('cc: %s vs %s' % (derived.get('cc'), base.get('cc')))
    dr = _norm_type(derived.get('return'))
    br = _norm_type(base.get('return'))
    if dr != br:
        mm.append('return_type: %s vs %s' % (dr, br))
    dp = derived.get('params') or []
    bp = base.get('params') or []
    if len(dp) != len(bp):
        mm.append('param_count: %d vs %d' % (len(dp), len(bp)))
    else:
        for i, (a, b) in enumerate(zip(dp, bp)):
            ta, tb = _norm_type(a.get('type')), _norm_type(b.get('type'))
            if ta != tb:
                mm.append('param[%d]: %s vs %s' % (i, ta, tb))
    if bool(derived.get('varargs')) != bool(base.get('varargs')):
        mm.append('varargs: %s vs %s' % (derived.get('varargs'), base.get('varargs')))
    return {'compatible': not mm, 'mismatches': mm}


# ── [S2 消费装载器/迁移 2026-11-16 TDD] ──

def pending_node():
    return {'return': None, 'cc': None, 'params': None, 'varargs': False, 'pending': True}


def node_of(entry):
    """注解方法条目 → SigNode。结构优先, 字符串回退解析, 双缺=pending诚实态(不伪造)。"""
    sm = entry.get('sig_model')
    if isinstance(sm, dict):
        return sm
    n = parse_signature(entry.get('signature'))
    return n if n else pending_node()


def migrate_entry(entry):
    """单条迁移: 字符串sig解析→sig_model落盘; 原串保留(S5前兼容); 幂等。
    返回报告: {status: migrated|noop|pending}。"""
    if entry.get('sig_model') is not None:
        return {'status': 'noop'}
    n = parse_signature(entry.get('signature'))
    if n:
        entry['semantic_sig'] = n.get('return')  # 兼容占位: 返回型速读
        entry['sig_model'] = n
        return {'status': 'migrated'}
    entry['sig_model'] = pending_node()
    return {'status': 'pending'}
