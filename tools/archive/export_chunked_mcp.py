#!/usr/bin/env python3
"""[分片导出 2026-11-12] 经 IDA MCP(idalib) 分片驱动 export_full。

背景: 全量 export 单次 py_eval 需 ~3-4 分钟, 超 MCP 90s 看门狗且 HTTP 断连
会杀死任务(实测 1103/3674 半途亡)。EXPORT_FUNC 支持逗号地址表 + 每片
~600 函数 ≈ 25-30s → 分片绕开看门狗; 每片写独立 EXPORT_OUTDIR 再并入
主 asm/pal3/decomp/。

用法: python3 tools/export_chunked_mcp.py [--chunk 600]
前置: IDA MCP server 运行中; 本脚本自行 idb_open 管理会话。
"""
import json
import os
import shutil
import sys
import urllib.request

MCP_URL = "http://127.0.0.1:13337/mcp"
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ADDRS_FILE = os.path.join(ROOT, 'data', 'status', 'export_addrs_tmp.json')
OUTDIR = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
WORKDIR = '/tmp/pal3_export_chunks'


def call(name, args, timeout=600):
    payload = {"jsonrpc": "2.0", "id": 2, "method": "tools/call",
               "params": {"name": name, "arguments": args}}
    req = urllib.request.Request(MCP_URL, data=json.dumps(payload).encode(),
                                 headers={"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=timeout) as resp:
        return json.loads(resp.read())


def main():
    chunk_size = 600
    for i, a in enumerate(sys.argv):
        if a == '--chunk' and i + 1 < len(sys.argv):
            chunk_size = int(sys.argv[i + 1])

    addrs = json.load(open(ADDRS_FILE))
    sid = open('/tmp/mcp_sid.txt').read().strip()
    os.makedirs(WORKDIR, exist_ok=True)
    ok_chunks = 0
    for ci in range(0, len(addrs), chunk_size):
        batch = addrs[ci:ci + chunk_size]
        env_code = '''
import os, json, sys
sys.path.insert(0, "%s/pipeline")
sys.path.insert(0, "%s/pipeline/ida")
os.chdir("%s")
os.environ["EXPORT_FUNC"] = "%s"
os.environ["EXPORT_OUTDIR"] = "%s/c%d"
out = {}
try:
    import export_full as EF
    EF.main()
    out["ok"] = True
except Exception as e:
    import traceback
    out["ok"] = False
    out["err"] = str(e)[:200]
    out["tb"] = traceback.format_exc()[-400:]
json.dumps(out)
''' % (ROOT, ROOT, ROOT, ','.join(batch), WORKDIR, ci)
        r = call('py_eval', {'database': sid, 'code': env_code}, timeout=600)
        res = json.loads(r['result']['content'][0]['text'])
        if not res.get('ok'):
            print('[chunk %d] FAIL: %s' % (ci, res.get('err')))
            print(res.get('tb', ''))
            break
        # 并入主目录
        src = os.path.join(WORKDIR, 'c%d' % ci, 'decomp')
        n = 0
        for f in os.listdir(src):
            if f.startswith('_'):
                continue  # 非函数产物主目录已有, 不覆盖
            shutil.copy2(os.path.join(src, f), os.path.join(OUTDIR, f))
            n += 1
        ok_chunks += 1
        print('[chunk %d] ok +%d files (cum %d)' % (ci, n, ok_chunks * chunk_size))

    print('done: %d chunks' % ok_chunks)


if __name__ == '__main__':
    main()
