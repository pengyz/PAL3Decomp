"""annotation plan → ghidra-mcp daemon 通道回放（产品路径写入面，2026-11-02 换轨）。
用法: python3 import_via_daemon.py <binaryPath> <plan.json>
MCP Streamable HTTP 直连（urllib，无三方依赖）。"""
import json, sys, urllib.request

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
                r = tool('create_label', dict(S, address=op['addr'], name=op['name']), rid)
            elif op['kind'] == 'set_func_sig':
                cc = {'__thiscall': 'thiscall', '__cdecl': 'cdecl', '__stdcall': 'stdcall'}.get(op.get('conv'), 'cdecl')
                r = tool('set_prototype', dict(S, functionAddress=op['addr'],
                          prototype='%s %s(%s)' % (op.get('ret') or 'void', op.get('name'),
                                                   ', '.join(op.get('params') or [])),
                          callingConvention=cc), rid)
            elif op['kind'] == 'define_global':
                r = tool('create_label', dict(S, address=op['addr'], name=op['name']), rid)
            else:
                continue
            txt = ((r.get('content') or [{}])[0].get('text', '') if isinstance(r, dict) else '')
            bad = (isinstance(r, dict) and (r.get('isError') or 'Error' in txt[:20] or 'error' in txt[:20].lower()))
            if bad:
                fail += 1
                if fail <= 3: print('  [fail]', op['kind'], op.get('name'), txt[:110])
            else:
                ok += 1
        except Exception as e:
            fail += 1
            if fail <= 3: print('  [exc]', op['kind'], e)
    print('replay done: ok=%d fail=%d / %d ops' % (ok, fail, len(plan)))

if __name__ == '__main__':
    main()
