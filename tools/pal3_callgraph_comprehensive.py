#!/usr/bin/env python3
"""PAL3.exe 综合性 BFS 调用图工具。

## 功能

1. **BFS 图**：WinMain 根节点，向下展开调用关系
2. **元信息**：每个函数有地址/签名/所属类/字节数/状态
3. **迁移跟踪**：已实现/L1 一致结果（相似百分比/差异字节）
4. **查询**：按层展开 / 节点调用链 / 进度统计

## 用法

  python3 tools/pal3_callgraph_comprehensive.py init          # 初始化（WinMain L0）
  python3 tools/pal3_callgraph_comprehensive.py expand        # 扩下一层
  python3 tools/pal3_callgraph_comprehensive.py status        # 进度统计
  python3 tools/pal3_callgraph_comprehensive.py layer N       # 查看第 N 层
  python3 tools/pal3_callgraph_comprehensive.py node ADDR     # 查看节点详情
  python3 tools/pal3_callgraph_comprehensive.py chain ADDR    # 查看调用链
  python3 tools/pal3_callgraph_comprehensive.py mark ADDR --status S --match-rate R --diff-bytes D
  python3 tools/pal3_callgraph_comprehensive.py export        # 导出 JSON
"""
import json
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
GRAPH_PATH = ROOT / 'asm' / 'pal3' / 'bfs_comprehensive.json'
NAMES_PATH = ROOT / 'asm' / 'pal3' / 'pal3_names.json'
DECOMP_DIR = ROOT / 'asm' / 'pal3' / 'decomp'
IDA_STRUCTS = ROOT / 'asm' / 'pal3' / 'ida_structs.json'


def load_metadata():
    """加载函数元信息（地址/签名/类/字节数）。"""
    meta = {}
    # 从 ida_structs.json
    if IDA_STRUCTS.exists():
        ida = json.load(open(IDA_STRUCTS))
        for cls, v in ida.items():
            if not isinstance(v, dict): continue
            ms = v.get('methods') or {}
            for addr, m in ms.items():
                if isinstance(m, dict) and m.get('name'):
                    meta[addr] = {
                        'name': m['name'],
                        'class': cls,
                        'signature': m.get('signature', ''),
                        'size': m.get('size', 0),
                    }
    # 从 functions.json
    funcs_path = ROOT / 'data' / 'annotations' / 'functions.json'
    if funcs_path.exists():
        d = json.load(open(funcs_path))
        for addr, f in d.items():
            if isinstance(f, dict) and f.get('name'):
                if addr not in meta:
                    meta[addr] = {
                        'name': f['name'],
                        'class': None,
                        'signature': f.get('signature', ''),
                        'size': f.get('size', 0),
                    }
    return meta


def find_decomp(addr):
    """查找 decomp 文件。"""
    addr_int = int(addr, 16) if isinstance(addr, str) else addr
    for f in DECOMP_DIR.glob('*.json'):
        try:
            d = json.load(open(f))
            if d.get('address') == f'0x{addr_int:08X}':
                return d
        except Exception:
            continue
    return None


def extract_callees(decomp):
    """从 decomp 提取 callees（call 目标）。"""
    callees = set()
    text = decomp.get('decompiled_c', '')
    # 找 0xADDR 形式
    for m in re.finditer(r'0x([0-9a-fA-F]{6,8})', text):
        callees.add(f'0x{int(m.group(1), 16):08X}')
    return callees


def init():
    """初始化（WinMain L0）。"""
    meta = load_metadata()
    winmain_addr = '0x00541900'
    
    graph = {
        'root': winmain_addr,
        'layers': {'0': [winmain_addr]},
        'nodes': {
            winmain_addr: {
                'name': 'WinMain',
                'layer': 0,
                'status': 'pending',  # pending/wip/done/mock
                'match_rate': None,
                'diff_bytes': None,
                'callees': [],
                'callers': [],
                **meta.get(winmain_addr, {}),
            }
        },
        'frontier': [winmain_addr],
        'max_depth': 0,
    }
    
    json.dump(graph, open(GRAPH_PATH, 'w'), ensure_ascii=False, indent=2)
    print(f'初始化完成:')
    print(f'  根节点: WinMain ({winmain_addr})')
    print(f'  层: 0 · Frontier: 1')
    return graph


def expand(graph):
    """扩下一层（BFS 向下）。"""
    meta = load_metadata()
    depth = graph.get('max_depth', 0)
    layer_nodes = graph.get('layers', {}).get(str(depth), [])
    
    new_callees = set()
    for addr in layer_nodes:
        node = graph['nodes'][addr]
        decomp = find_decomp(addr)
        if decomp:
            callees = extract_callees(decomp)
            node['callees'] = sorted(callees)
            for callee in callees:
                if callee not in graph['nodes']:
                    new_callees.add(callee)
                    m = meta.get(callee, {})
                    graph['nodes'][callee] = {
                        'name': m.get('name', f'func_{callee}'),
                        'layer': depth + 1,
                        'status': 'mock',
                        'match_rate': None,
                        'diff_bytes': None,
                        'callees': [],
                        'callers': [addr],
                        'class': m.get('class'),
                        'signature': m.get('signature', ''),
                        'size': m.get('size', 0),
                    }
    
    if new_callees:
        next_depth = depth + 1
        graph['layers'][str(next_depth)] = sorted(new_callees)
        graph['max_depth'] = next_depth
        graph['frontier'] = sorted(new_callees)
        print(f'扩层 L{next_depth}: 新增 {len(new_callees)} 个函数')
    else:
        print(f'无新 callees（L{depth} 已到底）')
    
    json.dump(graph, open(GRAPH_PATH, 'w'), ensure_ascii=False, indent=2)
    return graph


def show_layer(graph, n):
    """查看第 N 层。"""
    layer_nodes = graph.get('layers', {}).get(str(n), [])
    print(f'L{n}: {len(layer_nodes)} 个函数')
    for addr in layer_nodes:
        node = graph['nodes'][addr]
        print(f'  {addr}: {node["name"]} [{node["status"]}] '
              f'match={node.get("match_rate")} diff={node.get("diff_bytes")}')


def show_node(graph, addr):
    """查看节点详情。"""
    node = graph['nodes'].get(addr)
    if not node:
        print(f'节点不存在: {addr}')
        return
    print(f'节点详情: {addr}')
    print(f'  名称: {node["name"]}')
    print(f'  类: {node.get("class")}')
    print(f'  签名: {node.get("signature")}')
    print(f'  字节数: {node.get("size")}')
    print(f'  层: {node["layer"]}')
    print(f'  状态: {node["status"]}')
    print(f'  L1 匹配率: {node.get("match_rate")}')
    print(f'  差异字节: {node.get("diff_bytes")}')
    print(f'  callees: {len(node.get("callees", []))} 个')
    print(f'  callers: {len(node.get("callers", []))} 个')


def show_chain(graph, addr):
    """查看调用链（向上到根）。"""
    chain = []
    current = addr
    while current in graph['nodes']:
        node = graph['nodes'][current]
        chain.append(f'{current}: {node["name"]}')
        callers = node.get('callers', [])
        if not callers:
            break
        current = callers[0]
    
    print(f'调用链（{addr} → WinMain）:')
    for i, c in enumerate(reversed(chain)):
        print(f'  {"  " * i}{c}')


def mark(graph, addr, status, match_rate=None, diff_bytes=None):
    """标记节点状态。"""
    if addr not in graph['nodes']:
        print(f'节点不存在: {addr}')
        return
    node = graph['nodes'][addr]
    node['status'] = status
    if match_rate is not None:
        node['match_rate'] = match_rate
    if diff_bytes is not None:
        node['diff_bytes'] = diff_bytes
    json.dump(graph, open(GRAPH_PATH, 'w'), ensure_ascii=False, indent=2)
    print(f'标记 {addr}: {status} match={match_rate} diff={diff_bytes}')


def status(graph):
    """进度统计。"""
    nodes = graph.get('nodes', {})
    status_count = {}
    layer_count = {}
    for addr, node in nodes.items():
        s = node['status']
        status_count[s] = status_count.get(s, 0) + 1
        l = node['layer']
        layer_count[l] = layer_count.get(l, 0) + 1
    
    print(f'=== PAL3.exe BFS 迁移状态 ===')
    print(f'  总节点: {len(nodes)}')
    print(f'  状态分布: {status_count}')
    print(f'  层分布: {layer_count}')
    print(f'  最大深度: {graph.get("max_depth", 0)}')


def export(graph):
    """导出 JSON。"""
    out_path = ROOT / 'data' / 'status' / 'bfs_callgraph_export.json'
    json.dump(graph, open(out_path, 'w'), ensure_ascii=False, indent=2)
    print(f'导出: {out_path}')


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return
    
    cmd = sys.argv[1]
    
    if not GRAPH_PATH.exists() and cmd != 'init':
        print('未初始化，运行 init')
        return
    
    graph = json.load(open(GRAPH_PATH)) if GRAPH_PATH.exists() else {}
    
    if cmd == 'init':
        graph = init()
    elif cmd == 'expand':
        graph = expand(graph)
    elif cmd == 'status':
        status(graph)
    elif cmd == 'layer':
        if len(sys.argv) < 3:
            print('用法: layer N')
            return
        show_layer(graph, int(sys.argv[2]))
    elif cmd == 'node':
        if len(sys.argv) < 3:
            print('用法: node ADDR')
            return
        show_node(graph, sys.argv[2])
    elif cmd == 'chain':
        if len(sys.argv) < 3:
            print('用法: chain ADDR')
            return
        show_chain(graph, sys.argv[2])
    elif cmd == 'mark':
        if len(sys.argv) < 4:
            print('用法: mark ADDR --status S [--match-rate R] [--diff-bytes D]')
            return
        addr = sys.argv[2]
        mark_status = None
        match_rate = None
        diff_bytes = None
        i = 3
        while i < len(sys.argv):
            if sys.argv[i] == '--status':
                mark_status = sys.argv[i+1]
                i += 2
            elif sys.argv[i] == '--match-rate':
                match_rate = float(sys.argv[i+1])
                i += 2
            elif sys.argv[i] == '--diff-bytes':
                diff_bytes = int(sys.argv[i+1])
                i += 2
            else:
                i += 1
        mark(graph, addr, mark_status, match_rate, diff_bytes)
    elif cmd == 'export':
        export(graph)
    else:
        print(f'未知命令: {cmd}')
        print(__doc__)


if __name__ == '__main__':
    main()
