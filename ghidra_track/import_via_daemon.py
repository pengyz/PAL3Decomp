"""annotation plan → ghidra-mcp daemon 通道回放（产品路径写入面，2026-11-02 换轨）。
用法: python3 import_via_daemon.py <binaryPath> <plan.json>
MCP Streamable HTTP 直连（urllib，无三方依赖）。"""
import json, os, sys, urllib.request

URL = 'http://localhost:8432/mcp'

_SID = {'v': None}

def rpc(method, params=None, rid=1):
    body = json.dumps({'jsonrpc': '2.0', 'id': rid, 'method': method, 'params': params or {}}).encode()
    h = {'Content-Type': 'application/json', 'Accept': 'application/json, text/event-stream'}
    if _SID['v']:
        h['Mcp-Session-Id'] = _SID['v']
    req = urllib.request.Request(URL, data=body, headers=h)
    with urllib.request.urlopen(req, timeout=600) as r:
        sid = r.headers.get('Mcp-Session-Id')
        if sid:
            _SID['v'] = sid
        raw = r.read().decode()
    for ln in raw.splitlines():
        if ln.startswith('data:'):
            raw = ln[5:].strip()
            break
    return json.loads(raw)

def notify(method, params=None):
    body = json.dumps({'jsonrpc': '2.0', 'method': method, 'params': params or {}}).encode()
    h = {'Content-Type': 'application/json', 'Accept': 'application/json, text/event-stream'}
    if _SID['v']:
        h['Mcp-Session-Id'] = _SID['v']
    req = urllib.request.Request(URL, data=body, headers=h)
    try:
        urllib.request.urlopen(req, timeout=30).read()
    except Exception:
        pass

_RE_VIRTUAL = __import__('re').compile(r'\bvirtual\s+')
_RE_CONST = __import__('re').compile(r'\bconst\s+')

def norm_type(ty):
    """注解类型形 → daemon 解析形：virtual 剥（签名串混入）· const 剥（解析器不认修饰形）。"""
    ty = _RE_VIRTUAL.sub('', ty or '')
    ty = _RE_CONST.sub('', ty)
    return ty.strip()

def type_candidates(ty):
    """型解析回退链（2026-11-03 修缮）：daemon 解析拒时的渐进降级候选。
    实测残余形：X*→X · A::B*→B*→B · __int64→longlong · _BYTE*→byte*→byte。"""
    t0 = (ty or '').strip()
    out = [t0]
    if '::' in t0:
        out.append(t0.split('::')[-1].strip())
    core = out[-1]
    if core.endswith('*'):
        plain = core[:-1].strip()
        out.append(plain)
        if '::' in plain:
            out.append(plain.split('::')[-1].strip())
    aliases = {'__int64': 'longlong', '_BYTE': 'byte', '__int32': 'int',
               '__int16': 'short', '__int8': 'char', 'BOOL': 'int', 'DWORD': 'uint',
               'WORD': 'ushort', 'BYTE': 'uchar', 'FLOAT': 'float'}
    extra = []
    for cand in out:
        base = cand.rstrip('*').strip()
        if base in aliases:
            al = aliases[base]
            extra.append(al + (' *' if cand.endswith('*') else ''))
            if cand.endswith('*'):
                extra.append(al)
    out.extend(extra)
    seen, res = set(), []
    for x in out:
        if x and x not in seen:
            seen.add(x)
            res.append(x)
    return res


def norm_name(n):
    """名 sanitizer：反引号等非法字符（Ghidra 符号规则）。"""
    return (n or '').replace('`', "'")

def tool(name, args, rid=1):
    r = rpc('tools/call', {'name': name, 'arguments': args}, rid)
    return r.get('result', r)

def main():
    binary, plan_path = sys.argv[1], sys.argv[2]
    init = rpc('initialize', {'protocolVersion': '2025-03-26',
                              'capabilities': {}, 'clientInfo': {'name': 'pal3-import', 'version': '1'}})
    notify('notifications/initialized')
    print('MCP init:', init.get('result', {}).get('serverInfo'))
    sidr = tool('create_session', {'binaryPath': binary, 'programPath': 'fixture'}, 2)
    txt = (sidr.get('content') or [{}])[0].get('text', '')
    import re as _re
    m = _re.search(r'"sessionId"\s*:\s*"([^"]+)"', txt)
    sid = m.group(1) if m else None
    print('create_session sid:', sid, '|', txt[:160])
    plan = json.load(open(plan_path))
    ok = fail = 0
    rid = 10
    S = {'sessionId': sid} if sid else {}
    _FAILS = []
    # 拓扑序: union→struct（型先立）→name→sig→global（sig 引用型须后行）
    _order = {'define_union': 0, 'define_struct': 1, 'set_name': 2, 'set_func_sig': 3, 'define_global': 4}
    plan = sorted((o for o in plan if o.get('kind') != '_meta'), key=lambda o: _order.get(o['kind'], 9))
    _counts = {}
    for op in plan:
        _counts[op['kind']] = _counts.get(op['kind'], 0) + 1
    print('拓扑序:', _counts)
    for op in plan:
        rid += 1
        try:
            if op['kind'] == 'define_struct':
                fields = [{'name': m.get('name'), 'offset': m.get('offset'),
                           'type': m.get('type') if isinstance(m.get('type'), str) else 'byte'}
                          for m in (op.get('members') or [])]
                r = tool('create_structure', dict(S, name=op['name'], fields=fields), rid)
            elif op['kind'] == 'define_union':
                r = tool('create_union', dict(S, name=op['name']), rid)
            elif op['kind'] == 'set_name':
                r = tool('create_label', dict(S, address=op['addr'], name=norm_name(op['name'])), rid)
            elif op['kind'] == 'set_func_sig':
                cc = {'__thiscall': 'thiscall', '__cdecl': 'cdecl', '__stdcall': 'stdcall'}.get(op.get('conv'), 'cdecl')
                _ret = norm_type(op.get('ret') or 'void')
                _params = ', '.join(norm_type(p) for p in (op.get('params') or []))
                proto = '%s %s(%s)' % (_ret, norm_name(op.get('name')), _params)
                r = tool('set_prototype', dict(S, functionAddress=op['addr'],
                          prototype=proto, callingConvention=cc), rid)
                txt = str((r.get('content') or [{}])[0].get('text', '')) if isinstance(r, dict) else ''
                # [修缮①] 边界缺口: 函数不存在则先建（真函数 848/856 实证=Ghidra 发现缺）
                if 'No function at or containing' in txt:
                    tool('create_function', dict(S, address=op['addr']), rid)
                    r = tool('set_prototype', dict(S, functionAddress=op['addr'],
                              prototype=proto, callingConvention=cc), rid)
                    txt = str((r.get('content') or [{}])[0].get('text', '')) if isinstance(r, dict) else ''
                # [修缮②] 型解析回退链重试
                if isinstance(r, dict) and (r.get('isError') or 'Can\'t resolve' in txt):
                    txt0 = str((r.get('content') or [{}])[0].get('text', ''))
                    import re as _re2
                    m = _re2.search(r"Can't resolve (?:datatype|return type): (.+)", txt0)
                    if m:
                        bad = m.group(1).strip()
                        for cand in type_candidates(bad):
                            proto2 = ('%s %s(%s)' % (_ret, norm_name(op.get('name')), _params)).replace(bad, cand)
                            r = tool('set_prototype', dict(S, functionAddress=op['addr'],
                                      prototype=proto2, callingConvention=cc), rid)
                            txt = str((r.get('content') or [{}])[0].get('text', ''))
                            if not (isinstance(r, dict) and (r.get('isError') or 'Can\'t resolve' in txt)):
                                break
            elif op['kind'] == 'define_global':
                r = tool('create_label', dict(S, address=op['addr'], name=norm_name(op['name'])), rid)
            else:
                continue
            txt = ((r.get('content') or [{}])[0].get('text', '') if isinstance(r, dict) else '')
            bad = (isinstance(r, dict) and (r.get('isError') or 'Error' in txt[:20] or 'error' in txt[:20].lower()))
            if bad:
                fail += 1
                _FAILS.append({'kind': op['kind'], 'name': op.get('name'), 'addr': op.get('addr'),
                               'err': txt[:160]})
            else:
                ok += 1
        except Exception as e:
            fail += 1
            if fail <= 3: print('  [exc]', op['kind'], e)
    import json as _j
    _p = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'out', 'import_failures.jsonl')
    with open(_p, 'w') as _fh:
        for _f in _FAILS:
            _fh.write(_j.dumps(_f, ensure_ascii=False) + '\n')
    print('replay done: ok=%d fail=%d / %d ops -> %s' % (ok, fail, len(plan), _p))
    assert ok > 0, '零成功=通道断（禁吞）'

if __name__ == '__main__':
    main()
