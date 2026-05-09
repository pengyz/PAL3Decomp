---
name: pal3-verify
description: 校验 PAL3.exe BFS call_graph 与源码工程的一致性。检查源文件存在性、has_decomp 准确性、size 一致性、实现状态、stub 定义、frontier 一致性。
---

对 PAL3 反编译工程执行全面一致性校验。运行以下检查并报告结果：

## 校验项

1. **源文件存在性** — 所有 call_graph 节点指向的 source 文件是否存在
2. **has_decomp 准确性** — 节点的 has_decomp 字段是否与 asm/pal3/decomp/ 中实际文件一致
3. **size 一致性** — 有 decomp 的节点其 size 是否与 decomp JSON 中 size_bytes 匹配
4. **实现状态** — matched 的函数 match_rate 是否为 1.0；compiled 的函数是否确实有实现代码
5. **stub 定义** — status=stub 的节点在其 source 文件中是否有函数体
6. **frontier 一致性** — frontier 列表是否等于所有 status 为 stub/pending 的节点集合
7. **构建门控** — `cmake --build build/pal3` 是否通过
8. **字节对比** — 对所有 status=matched 的函数运行 compare 工具确认仍为 100%

## 执行方法

```python
python3 << 'SCRIPT'
import json, os, re

cg = json.load(open('asm/pal3/call_graph.json'))
decomp_dir = 'asm/pal3/decomp'
issues = []

# Build decomp address map
decomp_map = {}
for f in os.listdir(decomp_dir):
    if not f.endswith('.json'): continue
    m = re.search(r'([0-9a-f]{8})\.json$', f)
    if m:
        decomp_map['0x' + m.group(1)] = f

print(f"=== PAL3 一致性校验 ===")
print(f"节点: {len(cg['nodes'])}, Decomp 文件: {len(decomp_map)}")

# [1] Source file existence
for addr, node in sorted(cg['nodes'].items()):
    src = node.get('source')
    if src and not os.path.exists(src):
        issues.append(f"[源文件] {addr} {node['name']}: {src} 不存在")

# [2] has_decomp accuracy
for addr, node in sorted(cg['nodes'].items()):
    actual = addr.lower() in decomp_map
    claimed = node.get('has_decomp', False)
    if actual != claimed:
        issues.append(f"[has_decomp] {addr} {node['name']}: claimed={claimed} actual={actual}")

# [3] Size consistency
for addr, node in sorted(cg['nodes'].items()):
    if addr.lower() not in decomp_map: continue
    d = json.load(open(os.path.join(decomp_dir, decomp_map[addr.lower()])))
    if d.get('size_bytes', 0) > 0 and node.get('size', 0) > 0:
        if d['size_bytes'] != node['size']:
            issues.append(f"[size] {addr} {node['name']}: cg={node['size']} decomp={d['size_bytes']}")

# [4] Status sanity
for addr, node in sorted(cg['nodes'].items()):
    if node['status'] == 'matched' and node.get('match_rate') is not None and node['match_rate'] < 1.0:
        issues.append(f"[状态] {addr} {node['name']}: matched 但 rate={node['match_rate']}")

# [5] Stub definitions exist
for addr, node in sorted(cg['nodes'].items()):
    if node['status'] != 'stub': continue
    src = node.get('source')
    if not src or not os.path.exists(src): continue
    with open(src) as f:
        content = f.read()
    short_addr = addr[-6:]
    name = node['name']
    short_name = name.split('(')[0].split('::')[-1] if '::' in name else name.split('(')[0]
    if short_addr not in content and short_name not in content:
        issues.append(f"[stub] {addr} {name}: 在 {src} 中找不到定义")

# [6] Frontier consistency
expected = sorted([a for a, n in cg['nodes'].items() if n['status'] in ('stub', 'pending')])
actual = sorted(cg.get('frontier', []))
if expected != actual:
    missing = set(expected) - set(actual)
    extra = set(actual) - set(expected)
    if missing: issues.append(f"[frontier] 缺少: {missing}")
    if extra: issues.append(f"[frontier] 多余: {extra}")

# Report
print()
if issues:
    print(f"✗ 发现 {len(issues)} 个问题:")
    for i in issues:
        print(f"  {i}")
else:
    print("✓ 全部校验通过")

# Summary
statuses = [n['status'] for n in cg['nodes'].values()]
print(f"\n--- 统计 ---")
print(f"matched: {statuses.count('matched')}")
print(f"compiled: {statuses.count('compiled')}")
print(f"stub: {statuses.count('stub')}")
print(f"pending: {statuses.count('pending')}")
print(f"skipped: {statuses.count('skipped')}")
print(f"frontier: {len(cg.get('frontier', []))}")
SCRIPT
```

然后执行构建门控：
```bash
cmake --build build/pal3
```

对 matched 函数执行字节对比确认：
```bash
python3 tools/pal3_compare.py --compile src/pal3/gamebase/PAL3.cpp --func "?Destroy@PAL3@@SAXXZ"
```

## 输出格式

```
═══ PAL3 校验结果 ═══
[1] 源文件:     ✓/✗
[2] has_decomp:  ✓/✗
[3] size:        ✓/✗
[4] 实现状态:    ✓/✗
[5] stub 定义:   ✓/✗
[6] frontier:    ✓/✗
[7] 构建:        ✓/✗
[8] 字节匹配:    ✓/✗ (N/N matched)
═══════════════════════
```

如有问题，列出具体条目并建议修复方案。
