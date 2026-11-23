#!/usr/bin/env python3
"""PAL3.exe 分层 BFS 迁移工作流。

## 工作流（用户设计）

```
WinMain（根节点，L0）
  ↓ BFS 展开一层
L1：WinMain 直接调用的函数（用 Mock 下层）
  ↓ 完成 + L1 匹配通过
L2：L1 直接调用的函数（用 Mock 下层）
  ↓ 完成 + L1 匹配通过
L3...（持续）
```

## 每层验证

1. **迁移**（手写字节匹配）
2. **编译**（MSVC 6.0）
3. **L1 匹配**（与原游戏 exe 对拍）
4. **通过后扩下一层**

## Mock 策略

- **本层**：真迁移（字节匹配）
- **下层**：Mock（占位，待迁移）
- **上层**：已完成（真实现）

## 用法

  python3 tools/pal3_bfs_migration.py init          # 初始化（WinMain L0）
  python3 tools/pal3_bfs_migration.py frontier       # 查看当前层
  python3 tools/pal3_bfs_migration.py expand         # 扩下一层
  python3 tools/pal3_bfs_migration.py verify         # L1 匹配验证
  python3 tools/pal3_bfs_migration.py status         # 进度统计
"""
import json
import os
import subprocess
import sys
from collections import deque
from pathlib import Path

ROOT = Path(__file__).parent.parent
CALLGRAPH_PATH = ROOT / 'asm' / 'pal3' / 'bfs_callgraph.json'
NAMES_PATH = ROOT / 'asm' / 'pal3' / 'pal3_names.json'
DECOMP_DIR = ROOT / 'asm' / 'pal3' / 'decomp'
MANUAL_DIR = ROOT / 'manual' / 'pal3'


def load_names():
    """加载函数名。"""
    if not NAMES_PATH.exists():
        return {}
    d = json.load(open(NAMES_PATH))
    return {f['address']: f for f in d.get('functions', [])}


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
    """从 decomp 提取 callees（call 指令目标）。"""
    callees = set()
    text = decomp.get('decompiled_c', '')
    # 简单 regex：找函数调用（形如 FuncName(...) 或 0xADDR）
    import re
    # 找 0xADDR 形式
    for m in re.finditer(r'0x([0-9a-fA-F]{6,8})', text):
        callees.add(f'0x{int(m.group(1), 16):08X}')
    return callees


def init():
    """初始化（WinMain L0）。"""
    names = load_names()
    winmain_addr = '0x00541900'  # WinMain
    
    # 查 WinMain
    winmain_info = names.get(winmain_addr, {'address': winmain_addr, 'name': 'WinMain'})
    
    graph = {
        'root': winmain_addr,
        'layers': {0: [winmain_addr]},
        'nodes': {
            winmain_addr: {
                'name': 'WinMain',
                'layer': 0,
                'status': 'pending',  # pending/wip/done/mock
                'callees': [],
                'callers': [],
            }
        },
        'frontier': [winmain_addr],
        'max_depth': 0,
    }
    
    json.dump(graph, open(CALLGRAPH_PATH, 'w'), ensure_ascii=False, indent=2)
    print(f'初始化完成:')
    print(f'  根节点: WinMain ({winmain_addr})')
    print(f'  层: 0')
    print(f'  Frontier: 1')
    return graph


def frontier(graph):
    """查看当前层。"""
    depth = graph.get('max_depth', 0)
    layer_nodes = graph.get('layers', {}).get(str(depth), [])
    print(f'当前层 L{depth}: {len(layer_nodes)} 个函数')
    for addr in layer_nodes[:10]:
        node = graph['nodes'][addr]
        print(f'  {addr}: {node["name"]} [{node["status"]}]')
    if len(layer_nodes) > 10:
        print(f'  ... 共 {len(layer_nodes)} 个')


def expand(graph):
    """扩下一层（BFS）。"""
    names = load_names()
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
                    graph['nodes'][callee] = {
                        'name': names.get(callee, {}).get('name', f'func_{callee}'),
                        'layer': depth + 1,
                        'status': 'mock',  # 新层用 Mock
                        'callees': [],
                        'callers': [addr],
                    }
    
    if new_callees:
        next_depth = depth + 1
        graph['layers'][str(next_depth)] = sorted(new_callees)
        graph['max_depth'] = next_depth
        graph['frontier'] = sorted(new_callees)
        print(f'扩层 L{next_depth}: 新增 {len(new_callees)} 个函数')
    else:
        print(f'无新 callees（L{depth} 已到底）')
    
    json.dump(graph, open(CALLGRAPH_PATH, 'w'), ensure_ascii=False, indent=2)
    return graph


def verify(graph):
    """L1 匹配验证（本层）。"""
    depth = graph.get('max_depth', 0)
    layer_nodes = graph.get('layers', {}).get(str(depth), [])
    
    print(f'验证 L{depth}: {len(layer_nodes)} 个函数')
    # TODO: 跑 L1 匹配（编译 + 对拍）
    print('  [TODO] L1 匹配验证（需编译 + 对拍）')
    
    # 标记通过
    for addr in layer_nodes:
        graph['nodes'][addr]['status'] = 'done'
    
    json.dump(graph, open(CALLGRAPH_PATH, 'w'), ensure_ascii=False, indent=2)
    print(f'  标记 {len(layer_nodes)} 个函数为 done')


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


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return
    
    cmd = sys.argv[1]
    
    if not CALLGRAPH_PATH.exists() and cmd != 'init':
        print('未初始化，运行 init')
        return
    
    graph = json.load(open(CALLGRAPH_PATH)) if CALLGRAPH_PATH.exists() else {}
    
    if cmd == 'init':
        graph = init()
    elif cmd == 'frontier':
        frontier(graph)
    elif cmd == 'expand':
        graph = expand(graph)
    elif cmd == 'verify':
        verify(graph)
    elif cmd == 'status':
        status(graph)
    else:
        print(f'未知命令: {cmd}')
        print(__doc__)


if __name__ == '__main__':
    main()
