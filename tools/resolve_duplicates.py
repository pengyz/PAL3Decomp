"""
Resolve duplicate function definitions across gbengine source files.

Strategy:
1. Parse LNK4006 warnings to find all duplicated symbols
2. For each duplicate: determine CORRECT file ownership (from binary address clustering)
3. Compare implementation quality between the two copies
4. Remove the copy from the WRONG file
5. If the wrong file has a BETTER implementation, move it to the correct file first

Quality heuristics:
- memset/memcpy = stub (lower quality)
- Field-by-field assignment = real decompilation (higher quality)
- Address comments (// 0x1000xxxx) = IDA-derived (higher quality)
- Control flow (if/for/while) = real logic (higher quality)

Binary ownership:
- Functions adjacent in the .text section came from the same compilation unit
- IDA export JSON gives us the original address of each exported function
- We use known address regions to map functions to .cpp files
"""

import re
import os
import sys
import json
from collections import defaultdict

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_DIR = os.path.join(BASE_DIR, 'src', 'gbengine')
IDA_DIR = os.path.join(BASE_DIR, 'asm', 'gbengine_ida')
BUILD_DIR = os.path.join(BASE_DIR, 'build')


def load_ida_addresses():
    """Load function addresses from IDA export JSONs."""
    addr_map = {}  # mangled_name -> address
    if not os.path.exists(IDA_DIR):
        return addr_map
    for fname in os.listdir(IDA_DIR):
        if not fname.endswith('.json'):
            continue
        with open(os.path.join(IDA_DIR, fname), 'r') as f:
            data = json.load(f)
        if 'mangled_name' in data and 'address' in data:
            addr_map[data['mangled_name']] = int(data['address'], 16)
    return addr_map


def parse_duplicates(filepath):
    """Parse LNK4006 warnings from build output.
    Supports both Chinese and English MSVC output.
    Returns list of (mangled_name, kept_obj, ignored_obj)."""
    results = []
    with open(filepath, 'r', encoding='utf-8') as f:
        for line in f:
            # Chinese: xxx.obj : warning LNK4006: "demangled" (mangled) 已在 yyy.obj 中定义；已忽略第二个定义
            m = re.match(
                r'(\w+)\.obj\s*:\s*warning LNK4006:\s*"[^"]*"\s*\(([^)]+)\)\s*.*\s+(\w+)\.obj\s*',
                line
            )
            if m:
                ignored_obj, mangled, kept_obj = m.groups()
                results.append((mangled, kept_obj, ignored_obj))
    return list(set(results))


# =============================================================================
# Binary address regions -> file ownership mapping
# Derived from analyzing the gbengine.dll .text section layout in IDA
# =============================================================================

# Known compilation unit boundaries from binary address analysis
# Format: (start_addr, end_addr, canonical_file)
KNOWN_REGIONS = [
    # Small utility functions (mixed classes, near start of .text)
    (0x100038A0, 0x10003A00, 'gbColorFlt'),      # gbColorFlt ctors
    (0x100039F0, 0x10003D10, 'gbMesh'),           # gbDynVertBuf simple getters (in gbMesh unit)
    (0x10004110, 0x10004220, 'gbImage2D'),        # gbImage2D simple getters
    (0x100041B0, 0x10004220, 'gbTexture'),        # gbTextureArray ctors
    (0x10004240, 0x10004270, 'gbMesh'),           # gbDynVertBuf GetColor1/2
    (0x10004450, 0x10004500, 'gbPrintFont'),      # gbPrintFont simple
    (0x100047B0, 0x10004BD0, 'gbMesh'),           # gbBaseMesh methods
    (0x10004BD0, 0x10004C90, 'gbGfxManager'),     # gbDynVertBuf::GetXYZ, gbRenderEffect simple
    (0x10004D20, 0x10004E90, 'gbGfxManager'),     # gbEffectMgr ctor/dtor/op= (in gbGfxManager unit)
    (0x10004EA0, 0x10005060, 'gbGfxManager'),     # gbGfxManager getters/setters
    (0x10005380, 0x10005580, 'gbLightObj'),       # gbLightObj methods
    (0x100056E0, 0x10005B20, 'gbVisNode'),        # gbVisNode, gbVolModNode
    (0x10005B20, 0x10005E80, 'gbCamera'),         # gbCamera + gbCamControler + gbCam*Control
    (0x10005DB0, 0x10005E80, 'gbVFileSystem'),    # CPK::IsLoaded near VFileSystem
    (0x10005EF0, 0x10006200, 'gbVFileSystem'),    # gbVFile1, gbVTextFile ctors

    # Main implementation regions
    (0x1000D960, 0x1000DA00, 'gbImage2D'),        # gbImage2D::GetPixelFmtType
    (0x10011940, 0x10013100, 'gbMesh'),           # gbBaseMesh/gbStaticMesh heavy methods
    (0x10013190, 0x10013400, 'gbVisNode'),        # gbVisNode/gbVolModNode heavy
    (0x10013350, 0x10013700, 'gbSceneGraph'),     # gbSceneGraph/gbLightObj heavy
    (0x10015E60, 0x10016500, 'gbTexture'),        # gbTexture methods
    (0x1001B410, 0x1001B800, 'gbGfxManager_D3D'), # gbGfxManager_D3D
    (0x1001BA60, 0x1001C200, 'gbTexture'),        # gbTexture_D3D all methods
    (0x1001C790, 0x1001CF00, 'gbMesh'),           # gbDynVertBuf heavy (Render methods)
    (0x1001CEF0, 0x1001D900, 'gbGfxManager'),     # gbRenderEffect all methods
    (0x1001D8F0, 0x1001E400, 'gbGfxManager'),     # gbGfxManager heavy, gbEffectMgr complex
    (0x1001E3E0, 0x1001F700, 'gbImage2D'),        # gbImage2D heavy methods
    (0x1001FCA0, 0x10020100, 'gbMisc'),           # gbPixelFormat functions
    (0x10020900, 0x10021300, 'gbVertPool'),        # gbVertPool/gbVertPoolMgr/gbIndexBubble
    (0x10021830, 0x10022600, 'gbCamera'),          # gbCamera heavy methods
    (0x100226E0, 0x10022800, 'gbMisc'),            # gbUIRect
    (0x10024FE0, 0x100293B0, 'gbMath'),           # ALL math: Vec3D complex, Matrix4, RotMatrix, Quat, Stack
    (0x100293B0, 0x10029500, 'gbMath'),           # CRC32, Sphere, AABBox, OBBox, Ray, Plane
    (0x1002C3E0, 0x1002DB00, 'gbVFileSystem'),    # CPK all methods
    (0x1002ED80, 0x10030100, 'gbMisc'),           # gbNameVarBuf, gbTimeCounter, misc
    (0x10031190, 0x10031800, 'gbVFileSystem'),     # gbVTextFile methods
    (0x10031E40, 0x10032C00, 'gbWeather'),         # gbDropGroup, gbRain, gbSnow
]


def get_file_for_address(addr):
    """Look up which file owns a given binary address."""
    if addr is None:
        return None
    for start, end, fname in KNOWN_REGIONS:
        if start <= addr <= end:
            return fname
    return None


def get_canonical_file(mangled, addr_map, kept_obj, ignored_obj):
    """Determine which .cpp file should own this function.
    Returns file name (without .cpp) or None if uncertain."""
    addr = addr_map.get(mangled)
    region_file = get_file_for_address(addr)
    if region_file:
        return region_file

    # Fallback: class name heuristic
    # Demangle: extract class name from mangled symbol
    # ?Method@ClassName@@ or ??0ClassName@@
    m = re.search(r'@(\w+)@@', mangled)
    if m:
        classname = m.group(1)
        # If one of the two files matches the class name, prefer it
        if classname == kept_obj:
            return kept_obj
        if classname == ignored_obj:
            return ignored_obj

    return None


# =============================================================================
# Function body extraction (FIXED version)
# =============================================================================

def find_function_in_file(filepath, mangled_name):
    """Find a function definition in a source file by its mangled name.

    We search for the class::method pattern extracted from the mangled name.
    Returns (start_line, end_line, body_text) or None.

    start_line includes any preceding comment (// 0x... address comment).
    """
    # Extract class and method from mangled name
    # ??0ClassName@@... = constructor
    # ??1ClassName@@... = destructor
    # ?MethodName@ClassName@@... = regular method
    # ??4ClassName@@... = operator=
    # ??HClassName@@... = operator+
    # etc.

    class_name = None
    method_name = None

    # Constructor: ??0ClassName@@
    m = re.match(r'\?\?0(\w+)@@', mangled_name)
    if m:
        class_name = m.group(1)
        method_name = class_name  # ctor has same name as class

    # Destructor: ??1ClassName@@
    if not class_name:
        m = re.match(r'\?\?1(\w+)@@', mangled_name)
        if m:
            class_name = m.group(1)
            method_name = '~' + class_name

    # operator=: ??4ClassName@@
    if not class_name:
        m = re.match(r'\?\?4(\w+)@@', mangled_name)
        if m:
            class_name = m.group(1)
            method_name = 'operator='

    # Regular method: ?MethodName@ClassName@@
    if not class_name:
        m = re.match(r'\?(\w+)@(\w+)@@', mangled_name)
        if m:
            method_name = m.group(1)
            class_name = m.group(2)

    # Static data member: ?VarName@ClassName@@
    if not class_name:
        m = re.match(r'\?(\w+)@(\w+)@@', mangled_name)
        if m:
            method_name = m.group(1)
            class_name = m.group(2)

    if not class_name or not method_name:
        return None

    # Build search pattern: "ClassName::MethodName(" for definitions
    search_str = f'{class_name}::{method_name}'

    try:
        with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
            lines = f.readlines()
    except:
        return None

    # For static data members (no parentheses), look for "Type ClassName::member = ..."
    is_static_data = '@@0' in mangled_name or '@@1' in mangled_name or '@@2' in mangled_name
    if is_static_data and '(' not in method_name and 'operator' not in method_name:
        # Look for static member definition: Type Class::member = value;
        pattern = re.compile(re.escape(f'{class_name}::') + re.escape(method_name) + r'\s*[=;]')
        for i, line in enumerate(lines):
            if pattern.search(line):
                return (i, i, line)
        return None

    # Search for function definition
    search_pattern = re.compile(
        r'(?:^|\s)' + re.escape(class_name) + r'\s*::\s*' + re.escape(method_name) + r'\s*\('
    )

    candidates = []
    for i, line in enumerate(lines):
        if search_pattern.search(line):
            # Verify this is a definition, not a declaration or call
            # A definition has '{' within a few lines (not just ';')
            is_definition = False
            brace_line = -1

            # Check if same line has '{'
            if '{' in line and ';' not in line.split('{')[0].split('(')[0]:
                brace_line = i
                is_definition = True
            else:
                # Look ahead up to 10 lines for opening brace
                for j in range(i + 1, min(i + 10, len(lines))):
                    stripped = lines[j].strip()
                    if stripped == '{' or stripped.startswith('{'):
                        brace_line = j
                        is_definition = True
                        break
                    if stripped.endswith(';'):
                        # This is just a declaration
                        break
                    if stripped == '' or stripped.startswith('//'):
                        continue

            if not is_definition or brace_line < 0:
                continue

            # Count braces to find end of function
            depth = 0
            end_line = -1
            for j in range(brace_line, len(lines)):
                for ch in lines[j]:
                    if ch == '{':
                        depth += 1
                    elif ch == '}':
                        depth -= 1
                        if depth == 0:
                            end_line = j
                            break
                if end_line >= 0:
                    break

            if end_line < 0:
                continue

            # Include preceding comment lines (address comments, doc comments)
            start_line = i
            while start_line > 0:
                prev = lines[start_line - 1].strip()
                if prev.startswith('//') or prev == '':
                    start_line -= 1
                else:
                    break
            # Don't include blank lines at the very start
            while start_line < i and lines[start_line].strip() == '':
                start_line += 1

            body = ''.join(lines[start_line:end_line + 1])
            candidates.append((start_line, end_line, body))

    if not candidates:
        return None

    # If multiple candidates (e.g., overloads), try to match by parameter count
    if len(candidates) == 1:
        return candidates[0]

    # For overloads, we need to be more careful
    # Use parameter count from mangled name as a hint
    # Count '@' segments after method name to estimate param types
    # For now, return the first match (most common case)
    return candidates[0]


def score_implementation(body):
    """Score an implementation. Higher = better quality."""
    if body is None:
        return -1

    lines = body.strip().split('\n')
    score = 0

    # Line count (more detail = usually better)
    score += len(lines) * 2

    # Heavy penalty for memset/memcpy stubs
    if 'memset(this' in body or 'memset( this' in body:
        score -= 30
    if 'memcpy(this' in body or 'memcpy( this' in body:
        score -= 25

    # Bonus for field-by-field assignments (real decompilation)
    field_assigns = len(re.findall(r'\b\w+\s*=\s*(?!.*memset|.*memcpy)', body))
    score += field_assigns * 3

    # Bonus for address comments (IDA-derived, verified)
    if re.search(r'//\s*0x[0-9a-fA-F]+', body):
        score += 15

    # Bonus for real logic
    score += len(re.findall(r'\b(if|for|while|switch)\b', body)) * 5

    # Bonus for meaningful function calls
    calls = re.findall(r'[a-zA-Z_]\w*\(', body)
    score += len(calls) * 2

    # Penalty for /* UNCERTAIN */ comments
    if 'UNCERTAIN' in body:
        score -= 20

    # Penalty for empty/trivial bodies
    # Strip comments, braces, whitespace
    stripped = re.sub(r'//[^\n]*', '', body)
    stripped = re.sub(r'/\*.*?\*/', '', stripped, flags=re.DOTALL)
    stripped = re.sub(r'[{}\s]', '', stripped)
    if len(stripped) < 5:
        score -= 15

    # Bonus for return statements with computation
    score += len(re.findall(r'return\s+[^;]+;', body))

    return score


def remove_function_from_file(filepath, start_line, end_line):
    """Remove lines [start_line, end_line] from file.
    Also removes trailing blank line if it would create a double-blank."""
    with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.readlines()

    # Remove the function lines
    del lines[start_line:end_line + 1]

    # Clean up: remove double blank lines at the removal point
    if start_line < len(lines) and start_line > 0:
        if lines[start_line - 1].strip() == '' and lines[start_line].strip() == '':
            del lines[start_line]

    with open(filepath, 'w', encoding='utf-8', newline='') as f:
        f.writelines(lines)


def main():
    dup_file = os.path.join(BUILD_DIR, 'duplicates.txt')
    if not os.path.exists(dup_file):
        print(f"Error: {dup_file} not found. Run build first and capture LNK4006 warnings.")
        sys.exit(1)

    print("Loading IDA address map...")
    addr_map = load_ida_addresses()
    print(f"  {len(addr_map)} function addresses loaded")

    print("Parsing duplicate warnings...")
    duplicates = parse_duplicates(dup_file)
    print(f"  {len(duplicates)} unique duplicate pairs found")

    # Analysis phase
    print("\nAnalyzing each duplicate...")
    decisions = []  # (mangled, keep_file, remove_file, reason, score_keep, score_remove)
    unresolved = []

    for mangled, kept_obj, ignored_obj in duplicates:
        # Determine canonical ownership
        canonical = get_canonical_file(mangled, addr_map, kept_obj, ignored_obj)

        # Find implementations in both files
        kept_path = os.path.join(SRC_DIR, kept_obj + '.cpp')
        ignored_path = os.path.join(SRC_DIR, ignored_obj + '.cpp')

        result_kept = find_function_in_file(kept_path, mangled)
        result_ignored = find_function_in_file(ignored_path, mangled)

        score_kept = score_implementation(result_kept[2] if result_kept else None)
        score_ignored = score_implementation(result_ignored[2] if result_ignored else None)

        if canonical:
            # We know where it belongs
            if canonical == kept_obj:
                keep_file = kept_obj
                remove_file = ignored_obj
                reason = f"binary_ownership({canonical})"
            elif canonical == ignored_obj:
                keep_file = ignored_obj
                remove_file = kept_obj
                reason = f"binary_ownership({canonical})"
            else:
                # canonical is a third file? Shouldn't happen normally
                keep_file = kept_obj if score_kept >= score_ignored else ignored_obj
                remove_file = ignored_obj if keep_file == kept_obj else kept_obj
                reason = f"quality(canonical={canonical} not in pair)"
        else:
            # Unknown ownership - use quality
            if score_kept >= score_ignored:
                keep_file = kept_obj
                remove_file = ignored_obj
            else:
                keep_file = ignored_obj
                remove_file = kept_obj
            reason = "quality_only"

        # Check for conflict: better implementation in wrong file
        keep_score = score_kept if keep_file == kept_obj else score_ignored
        remove_score = score_ignored if keep_file == kept_obj else score_kept
        conflict = remove_score > keep_score + 10  # significant quality difference

        decisions.append({
            'mangled': mangled,
            'keep_file': keep_file,
            'remove_file': remove_file,
            'reason': reason,
            'keep_score': keep_score,
            'remove_score': remove_score,
            'conflict': conflict,
            'addr': addr_map.get(mangled),
        })

    # Report
    print(f"\n{'='*80}")
    print("RESOLUTION PLAN")
    print(f"{'='*80}")

    # Group by removal file
    by_remove_file = defaultdict(list)
    for d in decisions:
        by_remove_file[d['remove_file']].append(d)

    for fname, items in sorted(by_remove_file.items(), key=lambda x: -len(x[1])):
        print(f"\n  Remove from {fname}.cpp: {len(items)} functions")
        conflicts_in_file = [d for d in items if d['conflict']]
        if conflicts_in_file:
            print(f"    !! {len(conflicts_in_file)} CONFLICTS (better impl being removed):")
            for d in conflicts_in_file[:5]:
                print(f"       {d['mangled'][:60]}")
                print(f"         keep={d['keep_file']}(score={d['keep_score']}) "
                      f"remove={d['remove_file']}(score={d['remove_score']}) "
                      f"reason={d['reason']}")

    total_conflicts = sum(1 for d in decisions if d['conflict'])
    print(f"\n  Total: {len(decisions)} removals, {total_conflicts} conflicts")

    if '--apply' not in sys.argv:
        print("\n  Dry run complete. Use --apply to execute removals.")
        print("  Conflicts will be handled by MOVING better impl to correct file first.")
        return

    # =========================================================================
    # APPLY PHASE
    # =========================================================================
    print(f"\n{'='*80}")
    print("APPLYING CHANGES")
    print(f"{'='*80}")

    # Phase 1: Handle conflicts - move better implementations to correct file
    print("\n--- Phase 1: Move better implementations to correct files ---")
    move_count = 0
    for d in decisions:
        if not d['conflict']:
            continue

        keep_path = os.path.join(SRC_DIR, d['keep_file'] + '.cpp')
        remove_path = os.path.join(SRC_DIR, d['remove_file'] + '.cpp')

        result_keep = find_function_in_file(keep_path, d['mangled'])
        result_remove = find_function_in_file(remove_path, d['mangled'])

        if result_keep and result_remove:
            # Replace the implementation in keep_file with the better one from remove_file
            with open(keep_path, 'r', encoding='utf-8', errors='replace') as f:
                keep_lines = f.readlines()

            better_body_lines = result_remove[2].rstrip('\n').split('\n')
            better_body_lines = [l + '\n' for l in better_body_lines]

            keep_lines[result_keep[0]:result_keep[1] + 1] = better_body_lines

            with open(keep_path, 'w', encoding='utf-8', newline='') as f:
                f.writelines(keep_lines)
            move_count += 1

    print(f"  Moved {move_count} better implementations")

    # Phase 2: Remove duplicate definitions from wrong files
    print("\n--- Phase 2: Remove duplicates from wrong files ---")

    # Group removals by file and process each file once
    for fname, items in sorted(by_remove_file.items(), key=lambda x: -len(x[1])):
        filepath = os.path.join(SRC_DIR, fname + '.cpp')
        if not os.path.exists(filepath):
            print(f"  SKIP {fname}.cpp (not found)")
            continue

        # Re-find all functions (positions may have shifted in Phase 1)
        removals = []
        for d in items:
            result = find_function_in_file(filepath, d['mangled'])
            if result:
                removals.append((result[0], result[1], d['mangled']))
            else:
                # Static data member or not found
                pass

        if not removals:
            continue

        # Sort by line number descending to avoid offset issues
        removals.sort(key=lambda x: x[0], reverse=True)

        removed = 0
        for start, end, mangled in removals:
            # Re-verify position (file changes as we delete)
            result = find_function_in_file(filepath, mangled)
            if result:
                remove_function_from_file(filepath, result[0], result[1])
                removed += 1

        print(f"  {fname}.cpp: removed {removed}/{len(items)} functions")

    print("\nDone. Run build to verify.")


if __name__ == '__main__':
    main()
