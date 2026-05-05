"""
Search PAL3A.PDB for gbengine-related compiland/source file information.
Specifically look for .cpp and .obj references that indicate gbEngine9 source files.
"""
import sys

with open('original/PAL3A.pdb', 'rb') as f:
    data = f.read()

print(f"PDB size: {len(data)} bytes", file=sys.stderr)

# Strategy: find ALL null-terminated strings that contain recognizable gbengine class names
# combined with file extensions (.cpp, .obj, .c)
# These would be in the DBI module info section

# First, let's find the gbEngine.lib reference and look around it
idx = data.find(b'gbEngine.lib')
if idx != -1:
    print(f"\n=== Context around gbEngine.lib (offset {idx}) ===")
    # Show a wider region around this reference
    region_start = max(0, idx - 200)
    region_end = min(len(data), idx + 500)
    region = data[region_start:region_end]
    # Extract null-terminated strings from this region
    strings = []
    i = 0
    while i < len(region):
        if 32 <= region[i] < 127:
            start = i
            while i < len(region) and 32 <= region[i] < 127:
                i += 1
            s = region[start:i].decode('ascii', errors='ignore')
            if len(s) > 3:
                strings.append((start + region_start, s))
        else:
            i += 1
    for offset, s in strings:
        print(f"  [{offset:7d}] {s}")

# Now search for patterns that look like gbEngine9 source paths
# The obj files might be listed as relative paths within the lib
print("\n=== Searching for gbEngine9 source patterns ===")

# Common gbengine class names that would appear in file paths
class_names = [
    'gbActor', 'gbCamera', 'gbGeom', 'gbGfx', 'gbPrint', 'gbRes',
    'gbScene', 'gbTexture', 'gbVFile', 'gbVis', 'gbAudio',
    'gbMatrix', 'gbVec', 'gbQuat', 'gbRot', 'gbMatrixStack',
    'gbRay', 'gbOBBox', 'gbAABBox', 'gbSphere', 'gbPlane',
    'gbColor', 'gbChain', 'gbNBTree', 'gbBinary',
    'gbImage', 'gbRender', 'gbDynVert', 'gbBaseMesh', 'gbStatic',
    'gbLight', 'gbVert', 'gbPixel',
    'gbName', 'gbVText', 'gbUIRect', 'gbTime', 'gbIndex',
    'gbEffect', 'gbAnim', 'gbParticle', 'gbPart',
    'gbVolMod', 'gbRain', 'gbSnow', 'gbDrop', 'gbSound',
    'gbCam', 'CPK', 'gbMath', 'gbMesh',
]

# Search for each class name preceded by path separator and followed by .cpp or .obj
all_source_files = set()

for name in class_names:
    name_bytes = name.encode('ascii')
    idx = 0
    while True:
        idx = data.find(name_bytes, idx)
        if idx == -1:
            break
        # Try to extract a full path string around this
        start = idx
        while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
            start -= 1
        end = idx + len(name_bytes)
        while end < len(data) and data[end] != 0 and 32 <= data[end] < 127:
            end += 1
        s = data[start:end].decode('ascii', errors='ignore')
        # Check if this is a source file or object file path
        lower = s.lower()
        if ('.cpp' in lower or '.obj' in lower or lower.endswith('.c')):
            if len(s) > 6:
                all_source_files.add(s)
        idx += 1

print(f"\nFound {len(all_source_files)} potential source/object file references:")
for f in sorted(all_source_files):
    print(f"  {f}")

# Also look for the Release directory (gbEngine9 was compiled in Release mode for the final DLL)
print("\n=== Release build paths ===")
idx = 0
release_paths = set()
while True:
    idx = data.find(b'Release', idx)
    if idx == -1:
        break
    start = idx
    while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
        start -= 1
    end = idx + 7
    while end < len(data) and data[end] != 0 and 32 <= data[end] < 127:
        end += 1
    s = data[start:end].decode('ascii', errors='ignore')
    if 'gb' in s.lower() and ('.obj' in s.lower() or '.cpp' in s.lower() or '.lib' in s.lower()):
        release_paths.add(s)
    idx += 1

for p in sorted(release_paths):
    print(f"  {p}")

# Look for .h files with gb prefix to understand directory structure
print("\n=== gbEngine9 header files (.h) ===")
idx = 0
header_files = set()
while True:
    idx = data.find(b'gbEngine9', idx)
    if idx == -1:
        break
    start = idx
    while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
        start -= 1
    end = idx + 9
    while end < len(data) and data[end] != 0 and 32 <= data[end] < 127:
        end += 1
    s = data[start:end].decode('ascii', errors='ignore')
    if '.h' in s:
        header_files.add(s)
    idx += 1

for h in sorted(header_files):
    print(f"  {h}")
