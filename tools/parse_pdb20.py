"""
Parse PDB 2.0 (JG format) to extract module/source file information.
"""
import sys
import struct

def read_pdb20(filename):
    with open(filename, 'rb') as f:
        data = f.read()

    sig = data[:44]
    assert b'Microsoft C/C++ program database 2.00' in sig

    page_size = struct.unpack_from('<I', data, 44)[0]
    start_page = struct.unpack_from('<H', data, 48)[0]
    num_pages = struct.unpack_from('<H', data, 50)[0]
    dir_size = struct.unpack_from('<I', data, 52)[0]

    dir_num_pages = (dir_size + page_size - 1) // page_size
    dir_pages = []
    for i in range(dir_num_pages):
        p = struct.unpack_from('<H', data, 60 + i * 2)[0]
        dir_pages.append(p)

    print(f"Page size: {page_size}", file=sys.stderr)
    print(f"Num pages: {num_pages} (file: {len(data)//page_size})", file=sys.stderr)
    print(f"Dir size: {dir_size} bytes ({dir_num_pages} pages)", file=sys.stderr)

    # Read root directory stream
    dir_data = b''
    for p in dir_pages:
        offset = p * page_size
        dir_data += data[offset:offset + page_size]
    dir_data = dir_data[:dir_size]

    # Debug: first 32 bytes of directory
    print(f"Dir first 32 bytes:", file=sys.stderr)
    for i in range(0, 32, 8):
        chunk = dir_data[i:i+8]
        vals_h = [struct.unpack_from('<H', chunk, j)[0] for j in range(0, len(chunk)-1, 2)]
        vals_i = [struct.unpack_from('<I', chunk, j)[0] for j in range(0, max(0,len(chunk)-3), 4)]
        print(f"  {i:4d}: {chunk.hex()}  WORD={vals_h}  DWORD={vals_i}", file=sys.stderr)

    # PDB 2.0 directory format:
    # WORD num_streams
    # WORD reserved (0)
    # DWORD stream_sizes[num_streams]
    # WORD stream_pages[...] (flattened page lists)
    #
    # OR:
    # DWORD num_streams
    # DWORD stream_sizes[num_streams]
    # WORD stream_pages[...]

    # Try both interpretations
    num_streams_w = struct.unpack_from('<H', dir_data, 0)[0]
    num_streams_d = struct.unpack_from('<I', dir_data, 0)[0]
    print(f"  num_streams as WORD: {num_streams_w}", file=sys.stderr)
    print(f"  num_streams as DWORD: {num_streams_d}", file=sys.stderr)

    # Heuristic: num_streams should be in range [10, 2000] typically
    if 10 <= num_streams_w <= 2000:
        num_streams = num_streams_w
        # Try sizes at offset 2 (WORD num_streams) vs offset 4 (WORD num_streams + WORD pad)
        # Check which gives valid sizes (all < file size)
        for sizes_start in [2, 4]:
            test_sizes = [struct.unpack_from('<I', dir_data, sizes_start + i*4)[0]
                         for i in range(min(10, num_streams))]
            valid = all(s < len(data) or s == 0xFFFFFFFF for s in test_sizes)
            print(f"  Sizes at offset {sizes_start}: {test_sizes[:5]}... valid={valid}", file=sys.stderr)
    elif 10 <= num_streams_d <= 2000:
        num_streams = num_streams_d
        test_sizes = [struct.unpack_from('<I', dir_data, 4 + i*4)[0]
                     for i in range(min(10, num_streams))]
        print(f"  Sizes at offset 4 (DWORD count): {test_sizes[:5]}...", file=sys.stderr)

    # Based on earlier test: offset 4 gave: [34, 3608304, 73, 3800928, 1024564, 66921784, ...]
    # Stream 5 = 66MB > file size 7MB. So that's wrong.
    # offset 2 gave: [2228224, 250609664, ...] - also too big.
    # Something is wrong with num_streams or the offset.

    # Let me try: DWORD num_streams at offset 0, then DWORD sizes at offset 4
    # With the observation that num_streams_w = 385 but let's check if DWORD = something different
    # First 4 bytes hex was from debug above

    # Alternative: maybe num_streams at offset 0 is WORD=385, then reserved=0,
    # and the sizes use a DIFFERENT size (2 bytes each? unlikely)

    # Let me just try: num_streams=385 with sizes at various offsets
    # and use DWORD page numbers instead of WORD
    print(f"\n  Trying num_streams=385 with sizes at offset 4 (DWORD pages)...", file=sys.stderr)

    # Actually, for PDB 2.0, page indices might be DWORD not WORD if the file is large enough
    # With page_size=1024 and max WORD=65535, max addressable = 65535*1024 = 64MB
    # Our file is 7MB, so WORD should be fine.

    # Let me try a different root directory format:
    # Maybe it's: DWORD num_streams, DWORD sizes[], DWORD pages[]
    # (all DWORD)

    # With DWORD num_streams: first 4 bytes
    # Let's try with the assumption that sizes start immediately after num_streams
    # and are stored as DWORDs, and page numbers are also DWORDs

    # First, let me try the pdbparse library's interpretation
    # pdbparse uses: DWORD num_streams, then DWORD sizes[num_streams], then WORD pages
    # But num_streams from DWORD at offset 0 = ?

    # Let me examine more of the directory data
    print(f"\n  Extended dir dump (first 80 bytes):", file=sys.stderr)
    for i in range(0, 80, 4):
        val = struct.unpack_from('<I', dir_data, i)[0]
        print(f"    offset {i:3d}: 0x{val:08X} = {val}", file=sys.stderr)

    # Now try the most common PDB 2.0 interpretation:
    # num_streams as WORD at offset 0
    num_streams = num_streams_w  # 385
    # reserved WORD at offset 2
    # Then DWORD sizes[num_streams] at offset 4
    sizes_offset = 4

    stream_sizes = []
    for i in range(num_streams):
        s = struct.unpack_from('<I', dir_data, sizes_offset + i * 4)[0]
        stream_sizes.append(s)

    # Validate: sum of sizes (excluding 0xFFFFFFFF) should be < total file size
    valid_sizes = [s for s in stream_sizes if s != 0xFFFFFFFF and s > 0]
    total_stream_bytes = sum(valid_sizes)
    print(f"\n  num_streams: {num_streams}", file=sys.stderr)
    print(f"  Non-zero streams: {len(valid_sizes)}", file=sys.stderr)
    print(f"  Total stream bytes: {total_stream_bytes} (file: {len(data)})", file=sys.stderr)
    print(f"  First 10 sizes: {stream_sizes[:10]}", file=sys.stderr)

    if total_stream_bytes > len(data) * 2:
        print("  WARNING: Stream sizes seem too large, trying alternative format", file=sys.stderr)
        # Try: DWORD num_streams at offset 0, sizes at offset 4
        num_streams = num_streams_d & 0xFFFF  # maybe lower 16 bits
        if num_streams > 2000:
            # Give up on standard parsing, use brute force
            print("  Cannot determine directory format, using raw search", file=sys.stderr)
            return None, page_size, data

    # Read page numbers for each stream
    pages_start = sizes_offset + num_streams * 4
    print(f"  Pages data starts at dir offset: {pages_start}", file=sys.stderr)

    # Check if pages are WORD or DWORD
    # Read first few as both
    if pages_start < len(dir_data) - 4:
        first_page_w = struct.unpack_from('<H', dir_data, pages_start)[0]
        first_page_d = struct.unpack_from('<I', dir_data, pages_start)[0]
        print(f"  First page as WORD: {first_page_w}, as DWORD: {first_page_d}", file=sys.stderr)
        if first_page_w < num_pages:
            page_word_size = 2
            print("  Using WORD page numbers", file=sys.stderr)
        elif first_page_d < num_pages:
            page_word_size = 4
            print("  Using DWORD page numbers", file=sys.stderr)
        else:
            print(f"  WARNING: First page ({first_page_w}/{first_page_d}) >= num_pages ({num_pages})", file=sys.stderr)
            page_word_size = 2

    streams = []
    page_offset = pages_start
    for i, size in enumerate(stream_sizes):
        if size == 0 or size == 0xFFFFFFFF:
            streams.append(b'')
            continue
        num_stream_pages = (size + page_size - 1) // page_size
        stream_pages = []
        for j in range(num_stream_pages):
            if page_offset + page_word_size > len(dir_data):
                print(f"  ERROR: Ran out of directory data at stream {i}", file=sys.stderr)
                streams.append(b'')
                break
            if page_word_size == 2:
                p = struct.unpack_from('<H', dir_data, page_offset)[0]
            else:
                p = struct.unpack_from('<I', dir_data, page_offset)[0]
            stream_pages.append(p)
            page_offset += page_word_size
        else:
            # Read stream data
            stream_data = b''
            for p in stream_pages:
                off = p * page_size
                if off + page_size <= len(data):
                    stream_data += data[off:off + page_size]
                else:
                    stream_data += b'\x00' * page_size
            stream_data = stream_data[:size]
            streams.append(stream_data)
            continue
        # If we broke out of inner loop
        break

    print(f"\n  Successfully read {len(streams)} streams", file=sys.stderr)
    return streams, page_size, data


def find_source_file_info(streams):
    """Search streams for source file path information."""
    print("\n=== Searching streams for source file paths ===")

    for i, stream in enumerate(streams):
        if not stream:
            continue

        # Check for known gbengine symbols or paths
        has_gb = (b'gbEngine9' in stream or b'gbengine' in stream.lower() or
                  b'gbCamera' in stream or b'gbMatrix' in stream or
                  b'gbActor' in stream or b'gbScene' in stream)

        if has_gb:
            print(f"\n  Stream {i} ({len(stream)} bytes) - contains gb* references")

            # Extract all readable strings that look like file paths
            paths = set()
            idx = 0
            while idx < len(stream):
                if stream[idx] == 0:
                    idx += 1
                    continue
                if 32 <= stream[idx] < 127:
                    start = idx
                    while idx < len(stream) and stream[idx] != 0 and 32 <= stream[idx] < 127:
                        idx += 1
                    s = stream[start:idx].decode('ascii', errors='ignore')
                    # Check if it's a file path related to gbEngine
                    sl = s.lower()
                    if ('gb' in sl or 'cpk' in sl) and ('\\' in s or '/' in s) and len(s) > 8:
                        if '.cpp' in sl or '.c' in sl or '.h' in sl or '.obj' in sl:
                            paths.add(s)
                else:
                    idx += 1

            if paths:
                for p in sorted(paths):
                    print(f"    {p}")
            else:
                # Show first few strings that contain 'gb'
                idx = 0
                count = 0
                while idx < len(stream) and count < 20:
                    if stream[idx] == 0:
                        idx += 1
                        continue
                    if 32 <= stream[idx] < 127:
                        start = idx
                        while idx < len(stream) and stream[idx] != 0 and 32 <= stream[idx] < 127:
                            idx += 1
                        s = stream[start:idx].decode('ascii', errors='ignore')
                        if 'gb' in s.lower() and len(s) > 3:
                            print(f"    [{start}] {s}")
                            count += 1
                    else:
                        idx += 1


def search_raw_for_source_mapping(data):
    """
    Brute-force search the raw PDB data for source file information.
    Look for the file checksum/name table which contains all source file paths.
    """
    print("\n\n=== Raw PDB search for source file name table ===")

    # In PDB format, there's a "file info" substream in the DBI that contains
    # a file name table with all source file paths used in the program.
    # These are null-terminated strings packed together.
    #
    # We already found PAL3A source paths. Let's look specifically for
    # patterns that indicate gbEngine source organization.
    #
    # Key insight: The gbEngine9 lib was built separately. Its PDB info
    # was merged when PAL3A linked against it. The module entries for
    # gbEngine9 should reference its source files.

    # Look for the "gbengine.dll" module entry context
    idx = data.find(b'gbengine.dll')
    if idx != -1:
        print(f"\n  'gbengine.dll' found at offset {idx}")
        # Dump 512 bytes around it to understand the module record format
        region_start = max(0, idx - 100)
        region_end = min(len(data), idx + 500)
        region = data[region_start:region_end]

        # Extract all null-terminated strings in this region
        strings = []
        i = 0
        while i < len(region):
            if 32 <= region[i] < 127:
                start = i
                while i < len(region) and region[i] != 0 and 32 <= region[i] < 127:
                    i += 1
                s = region[start:i].decode('ascii', errors='ignore')
                if len(s) > 2:
                    strings.append((start + region_start, s))
            else:
                i += 1
        for off, s in strings:
            print(f"    [{off:7d}] {s}")

    # Now look for gbEngine9 specific content near the module list area
    # The DBI module list in PDB contains entries with:
    #   module_name (null term) + obj_file_name (null term)
    # For library modules, module_name = source file, obj_file_name = lib_name

    # Search for any path containing common gbengine subdirs
    # that we haven't found yet
    print("\n  Searching for gbEngine9 .cpp source paths...")
    search_patterns = [
        b'gbEngine9\\actor\\',
        b'gbEngine9\\gfx\\',
        b'gbEngine9\\math\\',
        b'gbEngine9\\support\\',
        b'gbEngine9\\physics\\',
        b'gbEngine9/actor/',
        b'gbEngine9/gfx/',
        b'gbEngine9/math/',
        b'gbEngine9/support/',
        b'gbEngine9/physics/',
        b'gbEngine9\\Actor\\',
        b'gbEngine9\\Gfx\\',
        b'gbEngine9\\Math\\',
        b'gbEngine9\\Support\\',
        b'gbEngine9\\Physics\\',
    ]

    found_any = False
    for pattern in search_patterns:
        idx = 0
        while True:
            idx = data.find(pattern, idx)
            if idx == -1:
                break
            start = idx
            while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
                start -= 1
            end = idx + len(pattern)
            while end < len(data) and data[end] != 0 and 32 <= data[end] < 127:
                end += 1
            s = data[start:end].decode('ascii', errors='ignore')
            if s not in [p.decode() for p in search_patterns]:  # skip bare pattern matches
                print(f"    [{start:7d}] {s}")
                found_any = True
            idx += 1

    if not found_any:
        print("    No gbEngine9 source .cpp paths found in PDB")
        print("\n  This likely means:")
        print("    1. gbengine.dll was built separately with its own PDB")
        print("    2. PAL3A.pdb only contains TYPE info imported from gbEngine headers")
        print("    3. The gbEngine9 source file structure is NOT in this PDB")
        print("    4. We should look for a separate gbEngine9.pdb or gbengine.pdb")

    # Check if there's a reference to a separate gbengine PDB
    print("\n  Searching for gbEngine/gbengine PDB references...")
    for pattern in [b'gbEngine9.pdb', b'gbengine.pdb', b'gbEngine.pdb']:
        idx = data.find(pattern)
        if idx != -1:
            start = idx
            while start > 0 and data[start-1] != 0 and 32 <= data[start-1] < 127:
                start -= 1
            end = idx + len(pattern)
            s = data[start:end].decode('ascii', errors='ignore')
            print(f"    [{idx:7d}] {s}")


def main():
    pdb_path = 'original/PAL3A.pdb'
    print(f"Parsing {pdb_path}...", file=sys.stderr)

    result = read_pdb20(pdb_path)
    if result is None or result[0] is None:
        # Stream parsing failed, use raw search
        with open(pdb_path, 'rb') as f:
            data = f.read()
        search_raw_for_source_mapping(data)
        return

    streams, page_size, raw_data = result

    # Search streams
    if streams:
        find_source_file_info(streams)

    # Also do raw search
    search_raw_for_source_mapping(raw_data)


if __name__ == "__main__":
    main()
