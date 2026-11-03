"""转换器 v2：annotation plan → apply_changeset 标准批（2026-11-03 标准数据通路）。
约束（apply_changeset schema）：1-250 ops/批 · 同目标禁双 op（去重保后）· description 必填。"""


def plan_to_changesets(plan):
    """plan ops → [{description, ops:[...]}] 批列表。
    映射：set_name→rename_function/rename_global · set_func_sig→set_prototype
          define_global→rename_global+set_global_type(裸名型) · define_struct/union=创建段（不入 changeset）。"""
    seen = {}
    order = []
    for op in plan:
        k = op.get('kind')
        addr = op.get('addr') or ''
        if k == 'set_name':
            key = 'name:' + addr
            seen[key] = {'op': 'rename_function', 'address': addr, 'name': op.get('name')}
        elif k == 'set_func_sig':
            key = 'proto:' + addr
            params = ', '.join(op.get('params') or [])
            seen[key] = {'op': 'set_prototype', 'address': addr,
                         'prototype': '%s %s(%s)' % (op.get('ret') or 'void', op.get('name'), params)}
        elif k == 'define_global':
            key = 'name:' + addr
            seen[key] = {'op': 'rename_global', 'address': addr, 'name': op.get('name')}
        else:
            continue
        if key not in order:
            order.append(key)
    ops = [seen[k] for k in order]
    return [{'description': 'pal3-import batch %d' % (i // 250 + 1), 'ops': ops[i:i + 250]}
            for i in range(0, len(ops), 250)]
