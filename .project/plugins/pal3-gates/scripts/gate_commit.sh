#!/bin/bash
cd "${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}" || exit 2
staged=$(git diff --cached --name-only -- pipeline/data/annotations/ 2>/dev/null)
if [ -n "$staged" ]; then
    output=$(python3 pipeline/cli.py check 2>&1 || python3 pipeline/check_annotations.py 2>&1)
    if [ $? -ne 0 ]; then
        echo "{\"reason\": \"Git commit 阻止：annotations 验证失败\n${output}\"}"
        exit 2
    fi
fi
exit 0
