"""Extract all PAL3A source file paths from PAL3A.PDB."""
import sys

with open('original/PAL3A.pdb', 'rb') as f:
    data = f.read()

# Extract all source paths that reference PAL3A source code
# Pattern: D:\PAL3A\PAL3\...\*.cpp
results = set()

# Search for .cpp files
idx = 0
while True:
    idx = data.find(b'.cpp', idx)
    if idx == -1:
        break
    # Walk back to find start (stop at null or non-printable)
    start = idx
    while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
        start -= 1
    end = idx + 4
    s = data[start:end].decode('ascii', errors='ignore')
    # Only keep paths that look like PAL3A source files
    if len(s) > 10 and 'PAL3' in s and ('\\' in s or '/' in s):
        # Clean up: remove length prefix bytes that got captured
        while s and not s[0].isalpha() and s[0] not in ('.', '\\', '/'):
            s = s[1:]
        if s.startswith('D:') or s.startswith('d:') or s.startswith('/PAL3'):
            results.add(s)
    idx += 1

# Also get .obj paths to understand compilation units
obj_results = set()
idx = 0
while True:
    idx = data.find(b'.obj', idx)
    if idx == -1:
        break
    start = idx
    while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
        start -= 1
    end = idx + 4
    s = data[start:end].decode('ascii', errors='ignore')
    if 'PAL3' in s and len(s) > 10:
        while s and not s[0].isalpha() and s[0] not in ('.', '\\', '/'):
            s = s[1:]
        if 'PAL3A_Debug' in s:
            obj_results.add(s)
    idx += 1

# Group source files by directory
from collections import defaultdict
by_dir = defaultdict(list)

for path in sorted(results):
    # Normalize: extract relative path after PAL3A\PAL3\ or PAL3A/PAL3/
    rel = path
    for prefix in ['D:\\PAL3A\\PAL3\\', 'd:\\PAL3A\\PAL3\\', 'D:/PAL3A/PAL3/']:
        if prefix in rel:
            rel = rel[rel.index(prefix) + len(prefix):]
            break

    parts = rel.replace('/', '\\').split('\\')
    if len(parts) > 1:
        by_dir[parts[0]].append(parts[-1])
    else:
        by_dir['(root)'].append(parts[0])

print(f"PAL3A 源文件: {len(results)} 个 .cpp 文件")
print(f"PAL3A 编译单元: {len(obj_results)} 个 .obj 文件")

print(f"\n=== 目录结构 ({len(by_dir)} 个子目录) ===\n")
for dirname in sorted(by_dir.keys(), key=lambda x: (-len(by_dir[x]), x)):
    files = sorted(set(by_dir[dirname]))
    print(f"  {dirname}/ ({len(files)} 个文件)")
    for f in files:
        print(f"    {f}")

# Also extract obj file names (these are definitive compilation units)
print(f"\n=== 编译单元 (.obj) 列表 ===\n")
obj_names = set()
for obj in sorted(obj_results):
    # Extract just the filename
    name = obj.split('\\')[-1]
    obj_names.add(name)

for name in sorted(obj_names):
    print(f"  {name}")
