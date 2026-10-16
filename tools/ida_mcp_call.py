#!/usr/bin/env python3
"""IDA MCP 直接调用助手（绕过 DSH MCP client）

用法：
  python tools/ida_mcp_call.py <tool_name> [args_json]
  
示例：
  python tools/ida_mcp_call.py server_health
  python tools/ida_mcp_call.py idb_open '{"input_path":"original/PAL3.exe.i64"}'
  python tools/ida_mcp_call.py xrefs_to '{"database":"<sid>","address":"0x401000"}'
"""
import json
import sys
import urllib.request

MCP_URL = "http://127.0.0.1:13337/mcp"

def call_mcp(method, params=None, req_id=1):
    payload = {
        "jsonrpc": "2.0",
        "id": req_id,
        "method": method,
        "params": params or {}
    }
    req = urllib.request.Request(
        MCP_URL,
        data=json.dumps(payload).encode(),
        headers={"Content-Type": "application/json"}
    )
    with urllib.request.urlopen(req, timeout=30) as resp:
        return json.loads(resp.read())

def call_tool(tool_name, arguments, req_id=2):
    return call_mcp("tools/call", {
        "name": tool_name,
        "arguments": arguments
    }, req_id)

def list_tools():
    return call_mcp("tools/list", {}, 1)

def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return
    
    tool_name = sys.argv[1]
    
    if tool_name == "list_tools":
        result = list_tools()
        tools = result.get("result", {}).get("tools", [])
        for t in tools:
            print(f"  {t['name']}")
        return
    
    if tool_name == "health":
        result = call_tool("server_health", {})
    else:
        args = {}
        if len(sys.argv) > 2:
            args = json.loads(sys.argv[2])
        result = call_tool(tool_name, args)
    
    print(json.dumps(result, indent=2, ensure_ascii=False))

if __name__ == "__main__":
    main()
