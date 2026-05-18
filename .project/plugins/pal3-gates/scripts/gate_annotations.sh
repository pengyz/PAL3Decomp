#!/bin/bash
cd "${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}" || exit 2
output=$(python3 pipeline/cli.py check 2>&1 || python3 pipeline/check_annotations.py 2>&1)
code=$?
if [ $code -ne 0 ]; then
    echo "{\"reason\": \"Annotations 验证失败，禁止写入：\n${output}\"}"
    exit 2
fi
exit 0
