"""IDA -S script: auto-start the ida-pro-mcp HTTP server (port 13337).

Run:  ida.exe -A -S"path\\to\\start_mcp_server.py" work.i64
The script returns immediately; the GUI keeps pumping so the server's
execute_sync marshalling works, and MCP clients can query the live IDB.
"""
import importlib.util
import os
import sys

PLUGIN = os.path.join(os.environ.get('APPDATA', ''), 'Hex-Rays', 'IDA Pro',
                      'plugins', 'mcp-plugin.py')

spec = importlib.util.spec_from_file_location('mcp_plugin', PLUGIN)
mod = importlib.util.module_from_spec(spec)
sys.modules['mcp_plugin'] = mod
spec.loader.exec_module(mod)

plugin = mod.MCP()
plugin.init()
plugin.run(None)  # starts MCPHTTPServer on 13337 (daemon thread)
print('[MCP] server auto-started via start_mcp_server.py')
