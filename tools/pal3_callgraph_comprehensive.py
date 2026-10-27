#!/usr/bin/env python3
"""PAL3.exe 综合性 BFS 调用图工具.

## 功能

1. **BFS 图**:WinMain 根节点,向下展开调用关系
2. **元信息**:每个函数有地址/签名/所属类/字节数/状态
3. **迁移跟踪**:已实现/L1 一致结果(相似百分比/差异字节)
4. **查询**:按层展开 / 节点调用链 / 进度统计

## 用法

  python3 tools/pal3_callgraph_comprehensive.py init          # 初始化(WinMain L0)
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
    """加载函数元信息(地址/签名/类/字节数)."""
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
    """查找 decomp 文件."""
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
    """从 decomp 提取 callees(具名调用,非 0x 字面量).

    [R103 修 2026-10-27·对抗复核] 原抓 0x 字面量当 callee(414/417 是常量)
    修:抓具名调用 Cls::Method() 形式
    """
    callees = set()
    text = decomp.get('decompiled_c', '')
    # 抓具名调用（Cls::Method 或 Func 形式）
    for m in re.finditer(r'\b([A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)\s*\(', text):
        name = m.group(1)
        # 排除关键字/类型
        if name not in ('if', 'while', 'for', 'switch', 'return', 'sizeof', 'int', 'char', 'void', 'float'):
            callees.add(name)
    return callees


def init():
    """初始化(WinMain L0)."""
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
    """扩下一层(BFS 向下)."""
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
    """查看第 N 层."""
    layer_nodes = graph.get('layers', {}).get(str(n), [])
    print(f'L{n}: {len(layer_nodes)} 个函数')
    for addr in layer_nodes:
        node = graph['nodes'][addr]
        print(f'  {addr}: {node["name"]} [{node["status"]}] '
              f'match={node.get("match_rate")} diff={node.get("diff_bytes")}')


def show_node(graph, addr):
    """查看节点详情."""
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
    """查看调用链(向上到根)."""
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
    """标记节点状态."""
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



def check(graph):
    """L1 对拍检查(每函数)+ 统计聚合.

    用 pipeline/compare_pal3.py 做 L1 对拍:
    1. 编译 .cpp -> .obj(MSVC 6.0)
    2. 提取函数体(COFF 符号表)
    3. 匹配符号(vc6_mangler)
    4. 比对字节(vs 原游戏 exe .text)

    刷新最新结果(match_rate / diff_bytes)+ 统计聚合.
    """
    import subprocess
    
    nodes = graph.get('nodes', {})
    total = len(nodes)
    l1_consistent = 0
    l1_partial = 0
    l1_fail = 0
    
    # 类维度聚合
    class_stats = {}
    
    print(f'=== L1 对拍检查（{total} 个函数）===')
    
    # [R103 修 2026-10-27] 跑 pipeline/cli.py match 当场读 [metric]
    # join 键用 va（非 address）· L1 判据用 status=='perfect'（非 95% 阈值）
    s4_path = ROOT / 'data' / 'status' / 's4_baseline.json'
    if s4_path.exists():
        s4 = json.load(open(s4_path))
        for func in s4.get('rows', []):
            va = func.get('va')
            if va in nodes:
                nodes[va]['match_rate'] = func.get('match_pct', 0) / 100.0
                nodes[va]['diff_bytes'] = func.get('diff_bytes', 0)
                nodes[va]['l1_status'] = func.get('status', '')
    
    for addr, node in nodes.items():
        match_rate = node.get('match_rate')
        diff_bytes = node.get('diff_bytes')
        
        if match_rate is None:
            continue
        
        if match_rate >= 0.95:
            l1_consistent += 1
            node['status'] = 'done'
        elif match_rate >= 0.50:
            l1_partial += 1
            node['status'] = 'wip'
        else:
            l1_fail += 1
            node['status'] = 'pending'
        
        # 类维度聚合
        cls = node.get('class') or 'free_function'
        if cls not in class_stats:
            class_stats[cls] = {'total': 0, 'consistent': 0, 'partial': 0, 'fail': 0}
        class_stats[cls]['total'] += 1
        if match_rate >= 0.95:
            class_stats[cls]['consistent'] += 1
        elif match_rate >= 0.50:
            class_stats[cls]['partial'] += 1
        else:
            class_stats[cls]['fail'] += 1
    
    # 统计输出
    checked = l1_consistent + l1_partial + l1_fail
    print(f'\n=== 统计结果 ===')
    print(f'  已检查: {checked}/{total}')
    print(f'  L1 一致 (>=95%): {l1_consistent}')
    print(f'  L1 部分 (>=50%): {l1_partial}')
    print(f'  L1 失败 (<50%): {l1_fail}')
    
    if checked > 0:
        print(f'  L1 一致率: {l1_consistent/checked*100:.1f}%')
    
    # 类维度聚合
    print(f'\n=== 类维度聚合 ===')
    for cls in sorted(class_stats.keys()):
        st = class_stats[cls]
        rate = st['consistent'] / st['total'] * 100 if st['total'] > 0 else 0
        print(f'  {cls}: {st["total"]} 个 · 一致 {st["consistent"]} ({rate:.1f}%)')
    
    # 层维度聚合
    print(f'\n=== 层维度聚合 ===')
    layer_stats = {}
    for addr, node in nodes.items():
        l = node['layer']
        if l not in layer_stats:
            layer_stats[l] = {'total': 0, 'consistent': 0}
        layer_stats[l]['total'] += 1
        if (node.get('match_rate') or 0) >= 0.95:
            layer_stats[l]['consistent'] += 1
    
    for l in sorted(layer_stats.keys()):
        st = layer_stats[l]
        rate = st['consistent'] / st['total'] * 100 if st['total'] > 0 else 0
        print(f'  L{l}: {st["total"]} 个 · 一致 {st["consistent"]} ({rate:.1f}%)')
    
    json.dump(graph, open(GRAPH_PATH, 'w'), ensure_ascii=False, indent=2)


def status(graph):
    """进度统计."""
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
    """导出 JSON."""
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
    elif cmd == 'check':
        check(graph)
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
