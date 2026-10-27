#!/bin/bash
# build.sh - build entry (calls build.py - build logic in Python)
# Out-of-tree build: bash build.sh -> python build.py
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
exec python "$SCRIPT_DIR/build.py" "$@"
