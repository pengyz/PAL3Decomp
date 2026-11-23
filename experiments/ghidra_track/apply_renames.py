#!/usr/bin/env python3
"""重放 plan（同名消歧根修 2026-11-07 的落地步）——直接复用 import_standard.main
（两遍建型 + 占位预滤 + dryRun 剔环 + expect 乐观锁全纪律继承）。
用法: python3 apply_renames.py <gpr> <plan.json>"""
import sys
from import_standard import main

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
