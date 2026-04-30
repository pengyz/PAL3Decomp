#!/usr/bin/env python3
"""
AI-Assisted Decompilation Pipeline for PAL3.

Orchestrates the decompilation workflow:
1. Read Ghidra-exported function data (JSON)
2. Construct a prompt with context (known structs, related functions)
3. Call Claude API to rewrite as C/C++
4. Attempt compilation
5. If compile fails, feed errors back to Claude (up to 3 retries)
6. If compile succeeds, run comparison
7. Record results in progress database

Usage:
    python ai_decompile.py process --function asm/FUN_00401000_00401000.json
    python ai_decompile.py batch --input-dir asm/ --max-count 10
    python ai_decompile.py retry --address 0x00401000

Environment:
    ANTHROPIC_API_KEY    - Claude API key
    MSVC_PATH            - Path to MSVC bin directory (optional)
    PAL3_COMPILER        - Compiler version hint (e.g., "msvc71")
"""

import argparse
import json
import os
import sys
import time
from dataclasses import dataclass, asdict
from datetime import datetime
from pathlib import Path
from typing import Optional

try:
    import anthropic
    HAS_ANTHROPIC = True
except ImportError:
    HAS_ANTHROPIC = False

# Project paths
PROJECT_ROOT = Path(__file__).parent.parent
ASM_DIR = PROJECT_ROOT / "asm"
SRC_DIR = PROJECT_ROOT / "src"
INCLUDE_DIR = PROJECT_ROOT / "include"
DOCS_DIR = PROJECT_ROOT / "docs"
BUILD_DIR = PROJECT_ROOT / "build"
PROGRESS_DB = BUILD_DIR / "progress.json"

# Import compare module
sys.path.insert(0, str(Path(__file__).parent))
try:
    from compare import compare_function, MatchLevel
except ImportError:
    compare_function = None
    MatchLevel = None


@dataclass
class DecompileResult:
    address: str
    name: str
    status: str  # "matched", "compiled", "failed", "error"
    match_level: int = 0
    source_file: str = ""
    attempts: int = 0
    timestamp: str = ""
    notes: str = ""
    confidence: str = ""


# Known compiler info (updated after Phase 1 reconnaissance)
COMPILER_CONFIG = {
    'version': 'MSVC 7.1 (VS2003)',  # To be confirmed from Rich Header
    'optimization': '/O2',
    'calling_convention': '/Gd',
    'defines': ['WIN32', '_WINDOWS', 'NDEBUG'],
    'rtti': True,
    'exceptions': True,
}


def load_known_structs() -> str:
    """Load known struct definitions from docs."""
    structs_file = DOCS_DIR / "structs.md"
    if structs_file.exists():
        return structs_file.read_text(encoding='utf-8')
    return "(No known structs yet)"


def load_function_data(json_path: str) -> dict:
    """Load Ghidra-exported function data."""
    with open(json_path, 'r', encoding='utf-8') as f:
        return json.load(f)


def get_related_context(func_data: dict) -> str:
    """Gather context from related functions that have already been decompiled."""
    context_parts = []

    # Check if any callees have been decompiled
    for callee in func_data.get('callees', []):
        callee_name = callee.get('name', '')
        # Search for decompiled source
        for src_file in SRC_DIR.rglob('*.c'):
            content = src_file.read_text(encoding='utf-8', errors='ignore')
            if callee_name in content:
                # Extract just the function signature
                for line in content.split('\n'):
                    if callee_name in line and '(' in line:
                        context_parts.append(
                            "// Callee: {}".format(line.strip()))
                        break
                break

    # Check for related headers
    for header in INCLUDE_DIR.rglob('*.h'):
        content = header.read_text(encoding='utf-8', errors='ignore')
        # Check if any globals referenced by this function are declared
        for gref in func_data.get('global_refs', []):
            if gref.get('name', '') in content:
                context_parts.append(
                    "// See: {} for {}".format(header.name, gref['name']))

    return "\n".join(context_parts) if context_parts else "(No related context available)"


def build_prompt(func_data: dict, attempt: int = 1,
                 prev_errors: str = "", prev_diff: str = "") -> str:
    """Construct the prompt for Claude."""
    known_structs = load_known_structs()
    related_context = get_related_context(func_data)

    # Base prompt
    prompt = """You are an x86 reverse engineering expert specializing in matching decompilation.
Below is Ghidra's decompiled output for function {name} (address {address}).
Rewrite it as compilable C/C++ code that, when compiled with {compiler}, produces
byte-identical machine code to the original.

REQUIREMENTS:
1. Infer meaningful variable and function names where possible
2. Restore proper data types (int, float, struct pointers, etc.)
3. Restore control flow (if/else, for, while, switch/case)
4. Use the exact calling convention: {calling_conv}
5. Mark uncertain parts with /* UNCERTAIN */ comments
6. If you recognize known patterns (DirectX calls, STL usage, Win32 API), note them

CONTEXT:
- Compiler: {compiler}
- Optimization: {optimization}
- Callers: {callers}
- Callees: {callees}
- Global variables referenced: {globals}
- Related context: {related}

KNOWN STRUCTS:
{structs}

GHIDRA DECOMPILED CODE:
```c
{decompiled_c}
```

ORIGINAL ASSEMBLY:
```asm
{assembly}
```
""".format(
        name=func_data.get('name', 'unknown'),
        address=func_data.get('address', '0x????????'),
        compiler=COMPILER_CONFIG['version'],
        optimization=COMPILER_CONFIG['optimization'],
        calling_conv=COMPILER_CONFIG['calling_convention'],
        callers=json.dumps(func_data.get('callers', []), indent=2),
        callees=json.dumps(func_data.get('callees', []), indent=2),
        globals=json.dumps(func_data.get('global_refs', []), indent=2),
        related=related_context,
        structs=known_structs[:2000],  # Limit struct context
        decompiled_c=func_data.get('decompiled_c', '// No decompiled code available'),
        assembly=func_data.get('assembly', '; No assembly available'),
    )

    # Add retry context if this is a subsequent attempt
    if attempt > 1 and prev_errors:
        prompt += """

PREVIOUS ATTEMPT FAILED TO COMPILE. Errors:
```
{errors}
```

Please fix the compilation errors and try again.
""".format(errors=prev_errors)

    if attempt > 1 and prev_diff:
        prompt += """

PREVIOUS ATTEMPT compiled but DID NOT MATCH the original. Assembly diff:
```
{diff}
```

Please adjust the C code to produce assembly closer to the original.
TIPS:
- MSVC generates different code for `if (ptr)` vs `if (ptr != NULL)`
- Local variable declaration order affects stack layout
- `for` vs `while` loops may generate different code
- Explicit casts can change instruction selection
- Register variable hints (__declspec) may be needed
""".format(diff=prev_diff[:3000])

    prompt += """

OUTPUT FORMAT:
Respond with ONLY the following sections:

## Code
```c
// Your rewritten C/C++ code here
```

## New Structs
```c
// Any new struct/typedef definitions discovered (or "None")
```

## Confidence
High/Medium/Low

## Notes
- Any observations or uncertainties
"""

    return prompt


def call_claude_api(prompt: str) -> Optional[str]:
    """Call the Claude API with the decompilation prompt."""
    if not HAS_ANTHROPIC:
        print("[!] anthropic package not installed. Install with: pip install anthropic")
        return None

    api_key = os.environ.get('ANTHROPIC_API_KEY')
    if not api_key:
        print("[!] ANTHROPIC_API_KEY not set")
        return None

    client = anthropic.Anthropic(api_key=api_key)

    try:
        message = client.messages.create(
            model="claude-sonnet-4-20250514",
            max_tokens=4096,
            messages=[
                {"role": "user", "content": prompt}
            ]
        )
        return message.content[0].text
    except Exception as e:
        print("[!] Claude API error: {}".format(e))
        return None


def parse_claude_response(response: str) -> dict:
    """Parse Claude's response into code, structs, confidence, and notes."""
    result = {
        'code': '',
        'new_structs': '',
        'confidence': 'unknown',
        'notes': '',
    }

    # Extract code block
    sections = response.split('## ')
    for section in sections:
        if section.startswith('Code'):
            # Extract code between ```c and ```
            lines = section.split('\n')
            in_code = False
            code_lines = []
            for line in lines:
                if line.strip().startswith('```c') or line.strip().startswith('```cpp'):
                    in_code = True
                    continue
                elif line.strip() == '```' and in_code:
                    in_code = False
                    continue
                elif in_code:
                    code_lines.append(line)
            result['code'] = '\n'.join(code_lines)

        elif section.startswith('New Structs'):
            lines = section.split('\n')
            in_code = False
            struct_lines = []
            for line in lines:
                if line.strip().startswith('```'):
                    if in_code:
                        in_code = False
                    else:
                        in_code = True
                    continue
                elif in_code:
                    struct_lines.append(line)
            result['new_structs'] = '\n'.join(struct_lines)

        elif section.startswith('Confidence'):
            conf_line = section.split('\n')[1].strip() if len(section.split('\n')) > 1 else ''
            result['confidence'] = conf_line.lower()

        elif section.startswith('Notes'):
            lines = section.split('\n')[1:]
            result['notes'] = '\n'.join(lines).strip()

    return result


def save_decompiled_code(func_data: dict, code: str, module: str = "core") -> str:
    """Save decompiled C code to the appropriate source file."""
    # Determine output path based on function name/address
    func_name = func_data.get('name', 'unknown')
    address = func_data.get('address', '0x00000000').replace('0x', '')

    # Create a file per function for now (can be merged later)
    output_dir = SRC_DIR / module
    output_dir.mkdir(parents=True, exist_ok=True)

    filename = "{}_{}.c".format(func_name, address)
    output_path = output_dir / filename

    # Add header comment
    header = """/**
 * Decompiled function: {name}
 * Original address: {address}
 * Size: {size} bytes
 * Auto-generated by ai_decompile.py - REQUIRES HUMAN REVIEW
 */

""".format(
        name=func_name,
        address=func_data.get('address', ''),
        size=func_data.get('size_bytes', 0),
    )

    output_path.write_text(header + code, encoding='utf-8')
    return str(output_path)


def update_structs(new_structs: str):
    """Append newly discovered structs to the structs documentation."""
    if not new_structs or new_structs.strip().lower() == 'none':
        return

    structs_file = DOCS_DIR / "structs.md"
    if structs_file.exists():
        existing = structs_file.read_text(encoding='utf-8')
    else:
        existing = "# Known Data Structures\n\n"

    # Avoid duplicates (simple check)
    if new_structs.strip() in existing:
        return

    with open(structs_file, 'a', encoding='utf-8') as f:
        f.write("\n\n```c\n{}\n```\n".format(new_structs.strip()))


def load_progress() -> dict:
    """Load the progress database."""
    if PROGRESS_DB.exists():
        with open(PROGRESS_DB, 'r') as f:
            return json.load(f)
    return {'functions': {}, 'last_updated': ''}


def save_progress(progress: dict):
    """Save the progress database."""
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    progress['last_updated'] = datetime.now().isoformat()
    with open(PROGRESS_DB, 'w') as f:
        json.dump(progress, f, indent=2)


def process_function(json_path: str, module: str = "core",
                     max_retries: int = 3, dry_run: bool = False) -> DecompileResult:
    """
    Process a single function through the full decompilation pipeline.
    """
    func_data = load_function_data(json_path)
    address = func_data.get('address', '0x00000000')
    name = func_data.get('name', 'unknown')

    print("\n" + "=" * 60)
    print("[*] Processing: {} ({})".format(name, address))
    print("    Size: {} bytes".format(func_data.get('size_bytes', 0)))
    print("=" * 60)

    result = DecompileResult(
        address=address,
        name=name,
        status="error",
        timestamp=datetime.now().isoformat(),
    )

    prev_errors = ""
    prev_diff = ""

    for attempt in range(1, max_retries + 1):
        print("\n[*] Attempt {}/{}".format(attempt, max_retries))
        result.attempts = attempt

        # Step 1: Build prompt
        prompt = build_prompt(func_data, attempt, prev_errors, prev_diff)

        if dry_run:
            print("[DRY RUN] Would send prompt ({} chars) to Claude API".format(len(prompt)))
            print("[DRY RUN] First 500 chars of prompt:")
            print(prompt[:500])
            result.status = "dry_run"
            return result

        # Step 2: Call Claude
        print("[*] Calling Claude API...")
        response = call_claude_api(prompt)
        if not response:
            result.status = "error"
            result.notes = "Claude API call failed"
            return result

        # Step 3: Parse response
        parsed = parse_claude_response(response)
        if not parsed['code']:
            print("[!] No code in Claude's response")
            result.status = "error"
            result.notes = "No code in API response"
            return result

        result.confidence = parsed['confidence']
        print("[*] Confidence: {}".format(parsed['confidence']))

        # Step 4: Save code
        source_path = save_decompiled_code(func_data, parsed['code'], module)
        result.source_file = source_path
        print("[*] Saved to: {}".format(source_path))

        # Step 5: Update structs
        update_structs(parsed['new_structs'])

        # Step 6: Compile and compare
        if compare_function is None:
            print("[!] compare module not available, skipping comparison")
            result.status = "compiled"
            result.notes = "Comparison not available"
            return result

        func_size = func_data.get('size_bytes', 256)
        comp_result = compare_function(
            source_file=source_path,
            func_address=address,
            func_size=func_size,
            func_name=name,
            config=COMPILER_CONFIG,
        )

        # Check results
        if comp_result.compile_errors:
            print("[!] Compilation failed:")
            print("    {}".format(comp_result.compile_errors[:200]))
            prev_errors = comp_result.compile_errors
            prev_diff = ""
            continue

        result.match_level = comp_result.match_level

        if comp_result.match_level == MatchLevel.BYTE_IDENTICAL:
            print("[+] BYTE-IDENTICAL MATCH!")
            result.status = "matched"
            result.match_level = 1
            return result
        elif comp_result.match_level == MatchLevel.INSTRUCTION:
            print("[~] Instruction-level match (register differences)")
            result.status = "matched"
            result.match_level = 2
            # Could try one more time to get byte-identical
            prev_diff = "\n".join(comp_result.diff_lines)
            if attempt < max_retries:
                continue
            return result
        elif comp_result.match_level == MatchLevel.FUNCTIONAL:
            print("[-] Functional match only (different instructions)")
            result.status = "compiled"
            result.match_level = 3
            prev_diff = "\n".join(comp_result.diff_lines)
            prev_errors = ""
            continue
        else:
            print("[-] No match")
            prev_diff = "\n".join(comp_result.diff_lines)
            prev_errors = ""
            continue

    # Exhausted retries
    if result.status not in ("matched",):
        result.status = "compiled" if not prev_errors else "failed"
        result.notes = "Max retries reached. Last diff available in build/"

    return result


def process_batch(input_dir: str, module: str = "core",
                  max_count: int = 10, max_retries: int = 3,
                  dry_run: bool = False, sort_by_size: bool = True):
    """Process multiple functions in batch mode."""
    input_path = Path(input_dir)
    json_files = list(input_path.glob("*.json"))

    # Filter out summary files
    json_files = [f for f in json_files if not f.name.startswith('_')]

    if sort_by_size:
        # Sort by function size (smallest first for better match rates)
        sized_files = []
        for jf in json_files:
            try:
                data = json.load(open(jf))
                sized_files.append((data.get('size_bytes', 999999), jf))
            except Exception:
                sized_files.append((999999, jf))
        sized_files.sort(key=lambda x: x[0])
        json_files = [f for _, f in sized_files]

    # Load progress to skip already-processed functions
    progress = load_progress()

    # Filter out already-matched functions
    to_process = []
    for jf in json_files:
        try:
            data = json.load(open(jf))
            addr = data.get('address', '')
            if addr in progress.get('functions', {}):
                existing = progress['functions'][addr]
                if existing.get('status') == 'matched' and existing.get('match_level', 0) <= 2:
                    continue  # Skip already matched
            to_process.append(jf)
        except Exception:
            to_process.append(jf)

    to_process = to_process[:max_count]
    print("[*] Processing {} functions (of {} available)".format(
        len(to_process), len(json_files)))

    results = []
    for i, jf in enumerate(to_process):
        print("\n[{}/{}] Processing: {}".format(i + 1, len(to_process), jf.name))

        result = process_function(
            str(jf), module=module, max_retries=max_retries, dry_run=dry_run)
        results.append(result)

        # Update progress
        progress['functions'][result.address] = asdict(result)
        save_progress(progress)

        # Rate limiting for API calls
        if not dry_run:
            time.sleep(2)

    # Print summary
    print("\n" + "=" * 60)
    print("BATCH PROCESSING SUMMARY")
    print("=" * 60)
    matched = sum(1 for r in results if r.status == "matched")
    compiled = sum(1 for r in results if r.status == "compiled")
    failed = sum(1 for r in results if r.status in ("failed", "error"))
    print("Processed: {}".format(len(results)))
    print("Matched:   {} ({:.1f}%)".format(matched, 100*matched/max(1, len(results))))
    print("Compiled:  {} ({:.1f}%)".format(compiled, 100*compiled/max(1, len(results))))
    print("Failed:    {} ({:.1f}%)".format(failed, 100*failed/max(1, len(results))))


def main():
    parser = argparse.ArgumentParser(
        description="AI-Assisted Decompilation Pipeline for PAL3"
    )

    subparsers = parser.add_subparsers(dest='command')

    # Process single function
    proc_parser = subparsers.add_parser('process',
                                        help='Process a single function')
    proc_parser.add_argument('--function', '-f', required=True,
                            help='Path to Ghidra-exported JSON file')
    proc_parser.add_argument('--module', '-m', default='core',
                            help='Target module (core/game/script)')
    proc_parser.add_argument('--retries', '-r', type=int, default=3,
                            help='Max retry attempts')
    proc_parser.add_argument('--dry-run', action='store_true',
                            help='Show prompt without calling API')

    # Batch process
    batch_parser = subparsers.add_parser('batch',
                                         help='Batch process multiple functions')
    batch_parser.add_argument('--input-dir', '-i', default=str(ASM_DIR),
                             help='Directory with exported JSON files')
    batch_parser.add_argument('--module', '-m', default='core',
                             help='Target module')
    batch_parser.add_argument('--max-count', '-c', type=int, default=10,
                             help='Maximum functions to process')
    batch_parser.add_argument('--retries', '-r', type=int, default=3,
                             help='Max retry attempts per function')
    batch_parser.add_argument('--dry-run', action='store_true',
                             help='Show prompts without calling API')
    batch_parser.add_argument('--no-sort', action='store_true',
                             help='Do not sort by size (process in order)')

    # Retry a specific function
    retry_parser = subparsers.add_parser('retry',
                                         help='Retry a previously failed function')
    retry_parser.add_argument('--address', '-a', required=True,
                             help='Function address to retry')
    retry_parser.add_argument('--module', '-m', default='core',
                             help='Target module')

    # Show status
    subparsers.add_parser('status', help='Show current progress')

    args = parser.parse_args()

    if args.command == 'process':
        result = process_function(
            args.function, module=args.module,
            max_retries=args.retries, dry_run=args.dry_run)
        print("\nResult: {} (match level: {})".format(result.status, result.match_level))

    elif args.command == 'batch':
        process_batch(
            args.input_dir, module=args.module,
            max_count=args.max_count, max_retries=args.retries,
            dry_run=args.dry_run, sort_by_size=not args.no_sort)

    elif args.command == 'retry':
        # Find the JSON file for this address
        addr_str = args.address.replace('0x', '')
        json_files = list(ASM_DIR.glob("*_{}.json".format(addr_str)))
        if json_files:
            result = process_function(str(json_files[0]), module=args.module)
            print("\nResult: {} (match level: {})".format(result.status, result.match_level))
        else:
            print("[!] No exported JSON found for address {}".format(args.address))

    elif args.command == 'status':
        progress = load_progress()
        funcs = progress.get('functions', {})
        total = len(funcs)
        matched = sum(1 for f in funcs.values() if f.get('status') == 'matched')
        print("Progress: {}/{} functions matched".format(matched, total))
        print("Last updated: {}".format(progress.get('last_updated', 'never')))

    else:
        parser.print_help()


if __name__ == '__main__':
    main()
