"""
Deep search of PAL3A.PDB for gbEngine9 source file structure.
Uses known subdirectory names and searches for source file paths.
"""
import sys
import struct

with open('original/PAL3A.pdb', 'rb') as f:
    data = f.read()

print(f"PDB size: {len(data)} bytes", file=sys.stderr)

# We know gbEngine9 has subdirectories: actor, gfx, math, support, physics
# Search for these as path components
subdirs = [b'actor\\', b'gfx\\', b'math\\', b'support\\', b'physics\\',
           b'actor/', b'gfx/', b'math/', b'support/', b'physics/',
           b'Actor\\', b'Gfx\\', b'Math\\', b'Support\\', b'Physics\\']

print("=== Searching for subdirectory path patterns ===\n")

all_paths = {}  # path -> list of offsets

for subdir in subdirs:
    idx = 0
    while True:
        idx = data.find(subdir, idx)
        if idx == -1:
            break
        # Walk back to find start of string (null byte or non-printable)
        start = idx
        while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
            start -= 1
        # Walk forward to find end
        end = idx + len(subdir)
        while end < len(data) and data[end] != 0 and 32 <= data[end] < 127:
            end += 1
        s = data[start:end].decode('ascii', errors='ignore')
        if len(s) > 5 and 'gbEngine9' in s:
            if s not in all_paths:
                all_paths[s] = []
            all_paths[s].append(start)
        idx += 1

for path in sorted(all_paths.keys()):
    offsets = all_paths[path]
    print(f"  [{offsets[0]:7d}] ({len(offsets)}x) {path}")

# Now let's try a completely different approach:
# Parse the PDB 2.0 structure to find streams
print("\n\n=== PDB 2.0 Header Analysis ===")
# PDB 2.0 (JG) format:
# - First 0x2C bytes: signature + page_size + other header fields
# The signature we already know: "Microsoft C/C++ program database 2.00\r\n\x1a"

# After the signature at 0x2C (44 bytes):
# DWORD page_size
# WORD  start_page (typically 0)
# WORD  file_pages (total pages in file)
# After that, the root stream directory info

# Actually for PDB 2.0 JG format, the header after the 44-byte signature is:
# offset 44: DWORD page_size
# offset 48: WORD  start_page
# offset 50: DWORD file_pages
# offset 54: DWORD root_stream_size (bytes)
# offset 58: DWORD reserved
# offset 62: array of page numbers for root stream

header_start = 44  # After "Microsoft C/C++ program database 2.00\r\n\x1a\0"
# Actually the signature is exactly 44 bytes including trailing JG\0
sig = data[:44]
print(f"  Signature: {sig}")

# Let me find where actual struct data starts by looking for the page size
# Common page sizes for PDB 2.0: 0x400 (1024) or 0x800 (2048) or 0x1000 (4096)
# Check a few offsets
for offset in [40, 42, 44, 46, 48]:
    val = struct.unpack_from('<I', data, offset)[0]
    if val in (512, 1024, 2048, 4096):
        print(f"  Possible page_size at offset {offset}: {val}")

# Try interpreting the header
# Standard PDB 2.0 JG header after signature:
# The signature for JG is "Microsoft C/C++ program database 2.00\r\n\x1aJG\0\0"
# Let's check
jg_sig = b'Microsoft C/C++ program database 2.00\r\n\x1aJG\x00\x00'
if data[:len(jg_sig)] == jg_sig:
    print(f"  Confirmed JG signature ({len(jg_sig)} bytes)")
    hdr_offset = len(jg_sig)
else:
    # Try without the double null
    jg_sig2 = b'Microsoft C/C++ program database 2.00\r\n\x1aJG\x00'
    if data[:len(jg_sig2)] == jg_sig2:
        print(f"  JG signature variant ({len(jg_sig2)} bytes)")
        hdr_offset = len(jg_sig2)
    else:
        print(f"  Looking for signature end...")
        # Find end of signature (null terminated)
        end = data.find(b'\x00', 0)
        print(f"  First null at offset {end}")
        hdr_offset = end + 1
        # Skip any padding
        while hdr_offset < 64 and data[hdr_offset] == 0:
            hdr_offset += 1

print(f"  Header data starts at offset: {hdr_offset}")
print(f"  Next 32 bytes: {data[hdr_offset:hdr_offset+32].hex()}")

# For PDB 2.0, header after signature:
# DWORD page_size
# DWORD ???
# DWORD file_page_count
# DWORD root_size (bytes of root stream)
# DWORD ??? (reserved)
# followed by page number array for root stream

page_size = struct.unpack_from('<I', data, hdr_offset)[0]
print(f"  page_size (attempt 1): {page_size}")

# If that doesn't look right, try offset+4
if page_size not in (512, 1024, 2048, 4096):
    page_size = struct.unpack_from('<I', data, hdr_offset + 4)[0]
    print(f"  page_size (attempt 2): {page_size}")

# Let's just dump bytes after signature to understand the format
print(f"\n  Raw header bytes ({hdr_offset} to {hdr_offset+64}):")
for i in range(0, 64, 16):
    chunk = data[hdr_offset+i:hdr_offset+i+16]
    hex_str = ' '.join(f'{b:02x}' for b in chunk)
    ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in chunk)
    print(f"    {hdr_offset+i:4d}: {hex_str}  {ascii_str}")


# Alternative: search for function names we KNOW are in gbengine
# and look at surrounding data structure
print("\n\n=== Searching for known gbengine function symbol strings ===")
known_funcs = [b'gbMatrix4::Invert', b'gbCamera::SetPosition',
               b'gbVec3D::Normalize', b'gbImage2D::LoadFromFile',
               b'CPK::Open', b'gbActor::Render']

for func in known_funcs:
    idx = data.find(func)
    if idx != -1:
        # Get the full string
        start = idx
        while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
            start -= 1
        end = idx + len(func)
        while end < len(data) and data[end] != 0 and 32 <= data[end] < 127:
            end += 1
        full_str = data[start:end].decode('ascii', errors='ignore')
        print(f"  [{idx:7d}] {full_str}")
    else:
        # Try with decorations
        decorated = b'?' + func.replace(b'::', b'@@')
        idx2 = data.find(decorated)
        if idx2 != -1:
            print(f"  [{idx2:7d}] (decorated) found near: {data[idx2:idx2+60]}")
        else:
            print(f"  NOT FOUND: {func.decode()}")
