"""转换器 v2：annotation plan → apply_changeset 标准批（2026-11-03 标准数据通路）。
约束（apply_changeset schema）：1-250 ops/批 · 同目标禁双 op（去重保后）· description 必填。"""


def norm_key_addr(a):
    """地址键归一（切片形——禁 lstrip('0x')：字符集剥离会把 '0x0abc' 吃成 'abc'）。"""
    s = (a or '').strip().lower()
    return s[2:] if s.startswith('0x') else s


def plan_to_changesets(plan):
    """plan ops → [{description, ops:[...]}] 批列表。
    映射：set_name→rename_function/rename_global · set_func_sig→set_prototype
          define_global→rename_global+set_global_type(裸名型) · define_struct/union=创建段（不入 changeset）。"""
    seen = {}
    order = []
    for op in plan:
        k = op.get('kind')
        addr = op.get('addr') or ''
        na = norm_key_addr(addr)
        if k == 'set_name':
            # [T2] targetKey 分立：fn-name:/global-name: 对齐 Changeset.java:313-322
            # （旧 'name:'+addr 同址函数+全局互吃）；na 归一（前缀异写同址去重保后）
            key = 'fn-name:' + na
            seen[key] = {'op': 'rename_function', 'address': addr, 'name': op.get('name')}
        elif k == 'set_func_sig':
            key = 'proto:' + na
            params = ', '.join(op.get('params') or [])
            # set_prototype 契约（Changeset.java:233）：signature 含函数名+
            # callingConvention 独立（__x 形）+ expect 双键（执行层 enrich）
            # 裸名修：'int GRPinput::InitKeyMappings(...)' 的 :: 限定名被 daemon
            # 吞进返回型（Can't resolve return type 实锤）→ 取末段
            _bn = (op.get('name') or '').split('::')[-1]
            _ret = op.get('ret') or 'void'
            # ret 内 :: 限定名剥离（annotation 签名形 'int GRPinput::InitKeyMappings
            # __thiscall'——honest_signature 未剥名 ⇒ 整串被吞进返回型实锤）
            if '::' in _ret and ' ' in _ret:
                _ret = _ret.rsplit(' ', 1)[0].strip()
            seen[key] = {'op': 'set_prototype', 'address': addr,
                         'signature': '%s %s(%s)' % (_ret, _bn, params),
                         'callingConvention': op.get('conv') or '__thiscall'}
        elif k == 'define_global':
            key = 'global-name:' + na
            seen[key] = {'op': 'rename_global', 'address': addr, 'name': op.get('name')}
            if op.get('type'):
                # [T7②] 带 type 的全局必须发 set_global_type（词表支持 Changeset.java:252）
                _gtk = 'global-type:' + na
                seen[_gtk] = {'op': 'set_global_type', 'address': addr,
                              'type': op['type']}
                if _gtk not in order:
                    order.append(_gtk)   # 发射序表补挂（seen-only=不发射）
        else:
            continue
        if key not in order:
            order.append(key)
    ops = [seen[k] for k in order]
    return [{'description': 'pal3-import batch %d' % (i // 250 + 1), 'ops': ops[i:i + 250]}
            for i in range(0, len(ops), 250)]
