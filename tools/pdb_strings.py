"""Extract .cpp/.c source file paths from PDB binary."""
import sys

with open('original/PAL3A.pdb', 'rb') as f:
    data = f.read()

print(f"PDB size: {len(data)} bytes", file=sys.stderr)

# Search for .cpp occurrences
results = set()
idx = 0
while True:
    idx = data.find(b'.cpp', idx)
    if idx == -1:
        break
    start = idx
    while start > 0 and 32 <= data[start-1] < 127:
        start -= 1
    end = idx + 4
    while end < len(data) and 32 <= data[end] < 127:
        end += 1
    s = data[start:end].decode('ascii', errors='ignore')
    if len(s) > 5:
        results.add(s)
    idx += 1

# Search for .c\x00 occurrences (C files)
idx = 0
while True:
    idx = data.find(b'.c\x00', idx)
    if idx == -1:
        break
    start = idx
    while start > 0 and 32 <= data[start-1] < 127:
        start -= 1
    end = idx + 2
    s = data[start:end].decode('ascii', errors='ignore')
    if len(s) > 4 and not s.endswith('.cpp') and not s.endswith('.cs'):
        results.add(s)
    idx += 1

for r in sorted(results):
    print(r)

print(f"\nTotal: {len(results)} paths found", file=sys.stderr)
