#!/bin/bash
# Quick helper to decompile a single function interactively with Claude Code.
#
# Usage:
#   ./tools/decompile_func.sh asm/FUN_00401000_00401000.json
#   ./tools/decompile_func.sh asm/FUN_00401000_00401000.json --dry-run
#
# This script:
# 1. Shows the function info
# 2. Runs ai_decompile.py in process mode
# 3. Shows the result

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

if [ -z "$1" ]; then
    echo "Usage: $0 <function_json_file> [--dry-run]"
    echo ""
    echo "Available functions:"
    ls "$PROJECT_ROOT/asm/"*.json 2>/dev/null | head -20
    if [ "$(ls "$PROJECT_ROOT/asm/"*.json 2>/dev/null | wc -l)" -eq 0 ]; then
        echo "  (No exported functions yet. Run Ghidra export first.)"
    fi
    exit 1
fi

JSON_FILE="$1"
shift

if [ ! -f "$JSON_FILE" ]; then
    echo "Error: File not found: $JSON_FILE"
    exit 1
fi

echo "============================================"
echo "  PAL3 Function Decompilation"
echo "============================================"
echo ""

# Show function info
python3 -c "
import json, sys
with open('$JSON_FILE') as f:
    data = json.load(f)
print('Function: {} ({})'.format(data.get('name','?'), data.get('address','?')))
print('Size:     {} bytes'.format(data.get('size_bytes', '?')))
print('Callees:  {}'.format(len(data.get('callees', []))))
print('Callers:  {}'.format(len(data.get('callers', []))))
print('Globals:  {}'.format(len(data.get('global_refs', []))))
print()
# Show first few lines of decompiled C
dc = data.get('decompiled_c', '')
if dc:
    lines = dc.split('\n')
    print('Ghidra output ({} lines):'.format(len(lines)))
    for line in lines[:15]:
        print('  ' + line)
    if len(lines) > 15:
        print('  ... ({} more lines)'.format(len(lines) - 15))
"

echo ""
echo "Processing with AI pipeline..."
echo ""

python3 "$SCRIPT_DIR/ai_decompile.py" process --function "$JSON_FILE" "$@"
