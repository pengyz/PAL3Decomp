"""MCP query helper: bare JSON-RPC POST to the IDA MCP server."""
import json, sys, urllib.request

URL = 'http://127.0.0.1:13337/mcp'


def call(method, params=None, timeout=30):
    body = json.dumps({'jsonrpc': '2.0', 'id': 1,
                       'method': method, 'params': params or {}}).encode()
    req = urllib.request.Request(URL, data=body,
                                 headers={'Content-Type': 'application/json'})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        return json.loads(r.read().decode())


if __name__ == '__main__':
    method = sys.argv[1]
    params = json.loads(sys.argv[2]) if len(sys.argv) > 2 else {}
    r = call(method, params, timeout=int(sys.argv[3]) if len(sys.argv) > 3 else 30)
    out = json.dumps(r.get('result', r), ensure_ascii=False, indent=1)
    if len(out) > 6000 and '--full' not in sys.argv:
        print(out[:6000] + '\n...[truncated]')
    else:
        print(out)
