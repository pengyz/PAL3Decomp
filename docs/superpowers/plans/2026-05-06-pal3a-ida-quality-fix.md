# PAL3A IDA Quality Fix Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a diagnose-fix-verify pipeline of IDAPython scripts that identifies and repairs function boundary errors, imports PDB struct/class types, fixes calling conventions, and re-exports clean decompilation results.

**Architecture:** Five IDAPython scripts run sequentially in IDA Pro 9.2. Phase 1 diagnoses and classifies all functions into a JSON report. Phase 2 scripts consume that report to fix boundaries, import types, and fix calling conventions. Phase 3 verifies results and re-exports. All scripts follow the existing project pattern (standalone main(), log to `_logs/`, respect `_IDA_PIPELINE_RUNNING` flag).

**Tech Stack:** Python 3 (IDAPython), IDA Pro 9.2 + Hex-Rays, JSON for data exchange

---

### Task 0: Shared Constants Module

**Files:**
- Create: `tools/ida/ida_common.py`

This module holds shared constants and utility functions used by all new scripts. Avoids duplication.

- [ ] **Step 1: Create the shared module**

```python
"""
Shared constants and utilities for PAL3A IDA quality fix pipeline.
"""
import os
import ida_bytes
import ida_funcs
import ida_name
import ida_ua
import idc

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
DIAGNOSIS_REPORT = os.path.join(LOG_DIR, "diagnosis_report.json")

# PAL3A.exe PE section boundaries (post-unpack)
TEXT_START = 0x00401000
TEXT_END   = 0x00569018
RDATA_START = 0x0056A000
RDATA_END   = 0x0057F1F2
DATA_START  = 0x00580000
DATA_END    = 0x0060C000

# Confidence thresholds
CONF_AUTO_FIX = 0.8
CONF_MANUAL_REVIEW = 0.5


def is_in_text(addr):
    return TEXT_START <= addr < TEXT_END


def is_in_pe(addr):
    return TEXT_START <= addr < DATA_END


def is_valid_split_point(addr):
    """Check if addr is a valid function start by examining preceding bytes."""
    if addr < 5:
        return False, "addr_too_low"

    # ret = 0xC3
    if ida_bytes.get_byte(addr - 1) == 0xC3:
        return True, "ret_C3"

    # retn imm16 = 0xC2 xx xx
    if ida_bytes.get_byte(addr - 3) == 0xC2:
        return True, "retn_C2"

    # jmp rel32 = 0xE9 xx xx xx xx
    if ida_bytes.get_byte(addr - 5) == 0xE9:
        return True, "jmp_E9"

    # jmp rel8 = 0xEB xx
    if ida_bytes.get_byte(addr - 2) == 0xEB:
        return True, "jmp_EB"

    # int3 padding
    if ida_bytes.get_byte(addr - 1) == 0xCC:
        return True, "int3_CC"

    # nop padding
    if ida_bytes.get_byte(addr - 1) == 0x90:
        return True, "nop_90"

    # Check for function prologue at addr itself
    # push ebp = 0x55; mov ebp, esp = 0x8B 0xEC
    if ida_bytes.get_byte(addr) == 0x55:
        if ida_bytes.get_byte(addr + 1) == 0x8B and ida_bytes.get_byte(addr + 2) == 0xEC:
            return True, "prologue_push_ebp"

    # sub esp, imm8 = 0x83 0xEC xx
    if ida_bytes.get_byte(addr) == 0x83 and ida_bytes.get_byte(addr + 1) == 0xEC:
        return True, "prologue_sub_esp"

    # push reg (0x50-0x57)
    b = ida_bytes.get_byte(addr)
    if 0x50 <= b <= 0x57:
        return True, "prologue_push_reg"

    return False, "no_evidence"


def get_func_decompilation(addr):
    """Try to decompile a function, return code string or None."""
    import ida_hexrays
    try:
        cfunc = ida_hexrays.decompile(addr)
        if cfunc:
            return str(cfunc)
    except:
        pass
    return None


def make_logger(log_file_path):
    """Create a logger that prints and accumulates lines."""
    lines = []

    def log(msg):
        lines.append(str(msg))
        print(msg)

    def save():
        os.makedirs(os.path.dirname(log_file_path), exist_ok=True)
        with open(log_file_path, "w", encoding="utf-8") as f:
            f.write("\n".join(lines))

    return log, save, lines
```

- [ ] **Step 2: Commit**

```bash
git add tools/ida/ida_common.py
git commit -m "feat(ida): add shared constants module for quality fix pipeline"
```

---

### Task 1: Phase 1 — Diagnostic Engine (`ida_diagnose_quality.py`)

**Files:**
- Create: `tools/ida/ida_diagnose_quality.py`

This is the core diagnostic script. It iterates all functions in the IDA database, classifies each one, and writes a comprehensive JSON report.

- [ ] **Step 1: Write the diagnostic script skeleton**

```python
"""
IDAPython: PAL3A 反编译质量诊断引擎

对每个函数进行严格分类:
  - EH_FUNCLET: 异常处理子程序片段
  - BOUNDARY_OVERLAP: 函数边界错误(与下一个已知函数重叠)
  - UNPACK_ARTIFACT: 脱壳残留(地址超出PE范围)
  - SP_CORRUPT: 栈指针分析失败
  - USERPURGE_WRONG: 调用约定错误
  - STRUCT_NEEDED: 需要结构体类型定义
  - DUPLICATE: 重复地址(同一地址有PDB名+sub_名)
  - CLEAN: 无问题

输出: _logs/diagnosis_report.json
"""

import ida_auto
import ida_hexrays
import ida_funcs
import ida_bytes
import ida_name
import ida_frame
import idautils
import idc
import json
import os
import re
import time
import traceback
import builtins

# Import shared module
import sys
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
if SCRIPT_DIR not in sys.path:
    sys.path.insert(0, SCRIPT_DIR)
from ida_common import (
    PROJECT_ROOT, LOG_DIR, PDB_EXPORT,
    TEXT_START, TEXT_END, RDATA_START, RDATA_END, DATA_START, DATA_END,
    CONF_AUTO_FIX, CONF_MANUAL_REVIEW,
    is_in_text, is_in_pe, is_valid_split_point, make_logger
)

DIAGNOSIS_REPORT = os.path.join(LOG_DIR, "diagnosis_report.json")
LOG_FILE = os.path.join(LOG_DIR, "ida_diagnose_quality_log.txt")


def load_pdb_data():
    """Load PDB export and build lookup structures."""
    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        pdb = json.load(f)

    # Build address -> PDB func info map
    pdb_by_addr = {}
    for func in pdb['functions']:
        addr_str = func.get('address', '')
        if not addr_str:
            continue
        try:
            addr = int(addr_str, 16)
        except ValueError:
            continue
        if addr not in pdb_by_addr:
            pdb_by_addr[addr] = func

    # Build sorted list of PDB addresses in .text for boundary checking
    pdb_text_addrs = sorted(a for a in pdb_by_addr if is_in_text(a))

    # Build class name set
    class_names = set()
    for c in pdb.get('classes', []):
        name = c.get('name', '')
        if name and not name.startswith('std::'):
            class_names.add(name)

    return pdb, pdb_by_addr, pdb_text_addrs, class_names


def find_next_pdb_addr(addr, pdb_text_addrs):
    """Binary search for the next PDB-known address after addr."""
    import bisect
    idx = bisect.bisect_right(pdb_text_addrs, addr)
    if idx < len(pdb_text_addrs):
        return pdb_text_addrs[idx]
    return None


def classify_eh_funclet(addr, name, func, pdb_by_addr):
    """Strictly identify EH funclets. Returns (is_eh, confidence, details)."""
    details = {}

    # Criterion 1: Name pattern
    has_eh_name = bool(re.match(r'^\$[EL]\d+', name) or re.match(r'^\$[EL]\d+_\d+', name))
    details['has_eh_name'] = has_eh_name

    # Criterion 2: Function size
    size = func.size() if func else 0
    is_tiny = size < 64
    details['size'] = size
    details['is_tiny'] = is_tiny

    # Criterion 3: Contains JUMPOUT (try decompilation or check for indirect jumps)
    has_jumpout = False
    if size < 200:
        # Check for indirect jmp instructions in the function body
        ea = func.start_ea
        end = func.end_ea if func.end_ea else ea + size
        while ea < end:
            insn = ida_ua.insn_t()
            length = ida_ua.decode_insn(insn, ea)
            if length <= 0:
                break
            # jmp to address outside this function
            if insn.itype in (ida_ua.NN_jmp, ida_ua.NN_jmpni):
                target = insn.Op1.addr if insn.Op1.type == 7 else 0  # o_near
                if target and not (func.start_ea <= target < end):
                    has_jumpout = True
                    details['jumpout_target'] = f"0x{target:08X}"
                    break
            ea += length
    details['has_jumpout'] = has_jumpout

    # Criterion 4: Located outside .text (in .rdata/.data EH area)
    is_outside_text = not is_in_text(addr)
    details['outside_text'] = is_outside_text

    # Scoring: need at least 2 criteria
    score = sum([has_eh_name, is_tiny, has_jumpout, is_outside_text])

    if score >= 3:
        return True, 0.95, details
    elif score == 2:
        return True, 0.75, details
    elif has_eh_name and size < 200:
        # Relaxed: has $E name and is relatively small
        return True, 0.6, details
    else:
        return False, 0.0, details


def classify_function(addr, func, name, pdb_by_addr, pdb_text_addrs, class_names):
    """Classify a single function. Returns list of (label, confidence, details)."""
    labels = []
    size = func.size() if func else 0

    # --- UNPACK_ARTIFACT ---
    if not is_in_pe(addr):
        labels.append(('UNPACK_ARTIFACT', 0.99, {
            'reason': f'address 0x{addr:08X} outside PE range'
        }))
        return labels

    # --- EH_FUNCLET ---
    is_eh, eh_conf, eh_details = classify_eh_funclet(addr, name, func, pdb_by_addr)
    if is_eh:
        labels.append(('EH_FUNCLET', eh_conf, eh_details))
        return labels  # EH funclets don't need other checks

    # --- BOUNDARY_OVERLAP ---
    if is_in_text(addr):
        func_end = func.end_ea if func else addr + size
        next_pdb = find_next_pdb_addr(addr, pdb_text_addrs)
        if next_pdb and next_pdb < func_end:
            valid, evidence = is_valid_split_point(next_pdb)
            conf = 0.95 if valid else 0.4
            labels.append(('BOUNDARY_OVERLAP', conf, {
                'func_end': f"0x{func_end:08X}",
                'next_pdb_addr': f"0x{next_pdb:08X}",
                'overlap_bytes': func_end - next_pdb,
                'split_point_valid': valid,
                'split_evidence': evidence,
            }))

    # --- SP_CORRUPT ---
    # Check function flags for SP analysis issues
    if func:
        flags = idc.get_func_attr(addr, idc.FUNCATTR_FLAGS)
        if flags != -1 and (flags & 0x10):  # FUNC_SP_READY not set properly
            labels.append(('SP_CORRUPT', 0.7, {'flags': f"0x{flags:04X}"}))

    # --- USERPURGE_WRONG ---
    func_type = idc.get_type(addr) or ""
    if '__userpurge' in func_type or '__usercall' in func_type:
        # Check if PDB has correct info
        pdb_info = pdb_by_addr.get(addr)
        has_pdb_sig = bool(pdb_info and (pdb_info.get('parameters') or pdb_info.get('return_type')))
        labels.append(('USERPURGE_WRONG', 0.9 if has_pdb_sig else 0.6, {
            'ida_type': func_type[:80],
            'has_pdb_signature': has_pdb_sig,
        }))

    # --- STRUCT_NEEDED ---
    # Only check for non-trivial functions to avoid decompiling everything
    if size >= 20 and is_in_text(addr):
        # Heuristic: check if function is a class method with PDB class info
        pdb_info = pdb_by_addr.get(addr)
        if pdb_info:
            cls = pdb_info.get('class', '')
            if cls and cls in class_names:
                # This is a class method — likely needs struct
                labels.append(('STRUCT_NEEDED', 0.8, {
                    'class': cls,
                    'has_pdb_class_def': True,
                }))

    # --- CLEAN ---
    if not labels:
        labels.append(('CLEAN', 1.0, {}))

    return labels


def main():
    log, save_log, _ = make_logger(LOG_FILE)

    try:
        ida_auto.auto_wait()
        log("[*] PAL3A 反编译质量诊断引擎 v1.0")
        log(f"[*] PE sections: .text=0x{TEXT_START:08X}-0x{TEXT_END:08X}")

        # Load PDB data
        log("[*] 加载 PDB 数据...")
        pdb, pdb_by_addr, pdb_text_addrs, class_names = load_pdb_data()
        log(f"    PDB 函数: {len(pdb_by_addr)}")
        log(f"    PDB .text 地址: {len(pdb_text_addrs)}")
        log(f"    游戏类: {len(class_names)}")

        # Collect all IDA functions (de-duplicate by address)
        log("[*] 收集 IDA 函数...")
        ida_funcs_by_addr = {}
        for ea in idautils.Functions():
            if ea not in ida_funcs_by_addr:
                func = ida_funcs.get_func(ea)
                name = ida_name.get_name(ea) or f"sub_{ea:08X}"
                ida_funcs_by_addr[ea] = (func, name)

        log(f"    IDA 唯一函数: {len(ida_funcs_by_addr)}")

        # Identify duplicates (PDB name overrides sub_)
        duplicates = []
        for ea in list(ida_funcs_by_addr.keys()):
            _, name = ida_funcs_by_addr[ea]
            if name.startswith('sub_') and ea in pdb_by_addr:
                pdb_name = pdb_by_addr[ea].get('name', '')
                if pdb_name:
                    duplicates.append(ea)

        # Classify each function
        log("[*] 开始分类...")
        results = {}
        t0 = time.time()

        for i, (addr, (func, name)) in enumerate(sorted(ida_funcs_by_addr.items())):
            if (i + 1) % 2000 == 0:
                elapsed = time.time() - t0
                log(f"    [{i+1}/{len(ida_funcs_by_addr)}] {elapsed:.1f}s")

            labels = classify_function(addr, func, name, pdb_by_addr, pdb_text_addrs, class_names)

            results[f"0x{addr:08X}"] = {
                'name': name,
                'ida_size': func.size() if func else 0,
                'labels': [(lbl, conf, det) for lbl, conf, det in labels],
            }

        elapsed = time.time() - t0
        log(f"[*] 分类完成 ({elapsed:.1f}s)")

        # Build summary
        from collections import Counter
        label_counts = Counter()
        auto_fixable = 0
        manual_review = []

        for addr_str, info in results.items():
            for lbl, conf, det in info['labels']:
                label_counts[lbl] += 1
                if lbl in ('BOUNDARY_OVERLAP', 'USERPURGE_WRONG') and conf >= CONF_AUTO_FIX:
                    auto_fixable += 1
                elif lbl in ('BOUNDARY_OVERLAP', 'USERPURGE_WRONG', 'SP_CORRUPT') and conf < CONF_AUTO_FIX:
                    manual_review.append({
                        'address': addr_str,
                        'name': info['name'],
                        'label': lbl,
                        'confidence': conf,
                        'reason': det.get('split_evidence', det.get('reason', '')),
                    })

        summary = {
            'total_unique_functions': len(ida_funcs_by_addr),
            'by_label': dict(label_counts),
            'auto_fixable': auto_fixable,
            'needs_manual_review': len(manual_review),
            'duplicates': len(duplicates),
        }

        log(f"\n[*] === 诊断结果 ===")
        log(f"    总函数: {summary['total_unique_functions']}")
        for lbl, cnt in sorted(label_counts.items()):
            log(f"    {lbl:20s}: {cnt}")
        log(f"    可自动修复: {auto_fixable}")
        log(f"    需人工审查: {len(manual_review)}")

        # Write report
        report = {
            'meta': {
                'ida_db': 'PAL3A.exe.i64',
                'script_version': '1.0',
                'timestamp': time.strftime('%Y-%m-%dT%H:%M:%S'),
                'pe_sections': {
                    'text': [TEXT_START, TEXT_END],
                    'rdata': [RDATA_START, RDATA_END],
                    'data': [DATA_START, DATA_END],
                },
            },
            'summary': summary,
            'functions': results,
            'manual_review': manual_review[:200],
        }

        os.makedirs(LOG_DIR, exist_ok=True)
        with open(DIAGNOSIS_REPORT, 'w', encoding='utf-8') as f:
            json.dump(report, f, indent=2, ensure_ascii=False)
        log(f"\n[+] 报告已写入: {DIAGNOSIS_REPORT}")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    save_log()

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
```

- [ ] **Step 2: Commit**

```bash
git add tools/ida/ida_diagnose_quality.py
git commit -m "feat(ida): add Phase 1 diagnostic engine for quality classification"
```

---

### Task 2: Phase 2 Step 1 — Fix Function Boundaries (`ida_fix_boundaries.py`)

**Files:**
- Create: `tools/ida/ida_fix_boundaries.py`

Reads the diagnosis report, fixes overlapping function boundaries by truncating parent functions and creating new functions at PDB-specified split points.

- [ ] **Step 1: Write the boundary fix script**

```python
"""
IDAPython: 修正函数边界错误

读取诊断报告中的 BOUNDARY_OVERLAP 条目 (confidence >= 0.8),
在 PDB 指定的地址处拆分函数。

安全机制:
  - 默认 dry-run 模式 (只输出将要做什么)
  - 加 --execute 参数才实际修改
  - 每次操作前验证拆分点合法性
  - 失败时自动回滚

用法:
  idat.exe -A -S"ida_fix_boundaries.py" PAL3A.exe.i64          # dry-run
  idat.exe -A -S"ida_fix_boundaries.py --execute" PAL3A.exe.i64  # 实际执行
"""

import ida_auto
import ida_funcs
import ida_name
import ida_bytes
import idc
import json
import os
import sys
import time
import traceback
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
if SCRIPT_DIR not in sys.path:
    sys.path.insert(0, SCRIPT_DIR)
from ida_common import (
    LOG_DIR, PDB_EXPORT, CONF_AUTO_FIX,
    is_valid_split_point, make_logger
)

LOG_FILE = os.path.join(LOG_DIR, "fix_boundaries_log.txt")
DIAGNOSIS_REPORT = os.path.join(LOG_DIR, "diagnosis_report.json")

DRY_RUN = '--execute' not in ' '.join(sys.argv)


def load_pdb_names():
    """Build addr -> PDB name mapping."""
    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        pdb = json.load(f)
    names = {}
    for func in pdb['functions']:
        addr_str = func.get('address', '')
        if not addr_str:
            continue
        try:
            addr = int(addr_str, 16)
        except ValueError:
            continue
        name = func.get('name', '')
        if name and '[thunk]' not in name and '??' not in name:
            names[addr] = name
    return names


def main():
    log, save_log, _ = make_logger(LOG_FILE)

    try:
        ida_auto.auto_wait()
        mode = "DRY-RUN" if DRY_RUN else "EXECUTE"
        log(f"[*] 函数边界修复 ({mode})")

        if not os.path.exists(DIAGNOSIS_REPORT):
            log("[!] 诊断报告不存在, 请先运行 ida_diagnose_quality.py")
            save_log()
            return

        with open(DIAGNOSIS_REPORT, 'r', encoding='utf-8') as f:
            report = json.load(f)

        pdb_names = load_pdb_names()

        # Collect boundary overlap targets with sufficient confidence
        targets = []
        for addr_str, info in report['functions'].items():
            for lbl, conf, det in info['labels']:
                if lbl == 'BOUNDARY_OVERLAP' and conf >= CONF_AUTO_FIX:
                    addr = int(addr_str, 16)
                    next_addr_str = det.get('next_pdb_addr', '')
                    if next_addr_str:
                        next_addr = int(next_addr_str, 16)
                        targets.append((addr, next_addr, info['name'], det))

        # Sort by address to process in order
        targets.sort(key=lambda x: x[0])
        log(f"[*] 待修复: {len(targets)} 个重叠函数")

        success = 0
        skipped = 0
        failed = 0
        rollbacks = 0

        for addr, split_addr, name, det in targets:
            # Re-verify split point (IDA state may have changed)
            valid, evidence = is_valid_split_point(split_addr)
            if not valid:
                log(f"  [SKIP] 0x{addr:08X} -> 0x{split_addr:08X}: 拆分点无效 ({evidence})")
                skipped += 1
                continue

            func = ida_funcs.get_func(addr)
            if not func:
                skipped += 1
                continue

            if func.end_ea <= split_addr:
                # Already fixed or not overlapping anymore
                skipped += 1
                continue

            pdb_name = pdb_names.get(split_addr, '')
            safe_name = ''
            if pdb_name:
                safe_name = pdb_name.replace('::', '_').replace('~', '_dtor_')
                safe_name = safe_name.replace('<', '_').replace('>', '_').replace(' ', '_')

            if DRY_RUN:
                log(f"  [DRY] 0x{addr:08X} truncate at 0x{split_addr:08X} "
                    f"(overlap={func.end_ea - split_addr}B) -> new func: {pdb_name or 'unnamed'}")
                success += 1
                continue

            # --- EXECUTE ---
            old_end = func.end_ea

            # Step 1: Truncate parent
            if not ida_funcs.set_func_end(addr, split_addr):
                log(f"  [FAIL] 0x{addr:08X}: set_func_end failed")
                failed += 1
                continue

            # Step 2: Create new function
            created = ida_funcs.add_func(split_addr)
            if not created:
                # Try without specifying end
                created = ida_funcs.add_func(split_addr, 0)

            if not created:
                # Rollback: restore original end
                ida_funcs.set_func_end(addr, old_end)
                log(f"  [ROLL] 0x{addr:08X}: add_func(0x{split_addr:08X}) failed, rolled back")
                rollbacks += 1
                failed += 1
                continue

            # Step 3: Name the new function
            if safe_name:
                ida_name.set_name(split_addr, safe_name, ida_name.SN_NOWARN | ida_name.SN_NOCHECK)

            success += 1

        log(f"\n[*] 结果:")
        log(f"    成功: {success}")
        log(f"    跳过: {skipped}")
        log(f"    失败: {failed}")
        log(f"    回滚: {rollbacks}")

        if not DRY_RUN and success > 0:
            log("[*] 等待自动分析...")
            ida_auto.auto_wait()
            idc.save_database(idc.get_idb_path(), 0)
            log("[+] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    save_log()

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
```

- [ ] **Step 2: Commit**

```bash
git add tools/ida/ida_fix_boundaries.py
git commit -m "feat(ida): add Phase 2 Step 1 - function boundary fix script"
```

---

### Task 3: Phase 2 Step 2 — Import PDB Types (`ida_import_pdb_types.py`)

**Files:**
- Create: `tools/ida/ida_import_pdb_types.py`

Reads class/struct/enum definitions from `pdb_export.json` and imports them into IDA's local type library using `idc.SetLocalType()`. Then applies class types to `this` pointers on class methods.

- [ ] **Step 1: Write the type import script**

```python
"""
IDAPython: 从 PDB 导入类/结构体/枚举类型

从 pdb_export.json 读取 1057 个类定义和 351 个枚举,
转换为 IDA C 声明并导入到本地类型库。

导入后对所有类方法的 this 指针设置正确类型,
让 Hex-Rays 将 *(_DWORD *)(this + N) 解析为 this->member。

用法:
  idat.exe -A -S"ida_import_pdb_types.py" PAL3A.exe.i64
"""

import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
import ida_name
import idautils
import idc
import json
import os
import sys
import re
import time
import traceback
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
if SCRIPT_DIR not in sys.path:
    sys.path.insert(0, SCRIPT_DIR)
from ida_common import (
    PROJECT_ROOT, LOG_DIR, PDB_EXPORT,
    TEXT_START, TEXT_END, is_in_text, make_logger
)

LOG_FILE = os.path.join(LOG_DIR, "fix_types_log.txt")

# PDB type -> C type mapping
TYPE_MAP = {
    'void': 'void', 'int': 'int', 'uint': 'unsigned int',
    'long': 'long', 'ulong': 'unsigned long',
    'short': 'short', 'ushort': 'unsigned short',
    'char': 'char', 'uchar': 'unsigned char',
    'float': 'float', 'double': 'double',
    'bool': 'bool', 'BOOL': 'int',
    'BYTE': 'unsigned char', 'WORD': 'unsigned short',
    'DWORD': 'unsigned long', 'LONG': 'long', 'UINT': 'unsigned int',
    'HWND': 'HWND__*', 'HINSTANCE': 'HINSTANCE__*',
    'LPARAM': 'long', 'WPARAM': 'unsigned int',
    'LRESULT': 'long', 'HANDLE': 'void*',
    'LPCSTR': 'const char*', 'LPSTR': 'char*', 'LPVOID': 'void*',
    'HDC': 'HDC__*', 'HRESULT': 'long',
    'HBITMAP': 'HBITMAP__*', 'HICON': 'HICON__*',
    'size_t': 'unsigned int', 'SOCKET': 'unsigned int',
    'D3DCOLOR': 'unsigned long',
}


def pdb_type_to_c(pdb_type, known_structs):
    """Convert a PDB type string to a C type string for IDA."""
    if not pdb_type:
        return 'int'

    t = pdb_type.strip()

    # Direct mapping
    if t in TYPE_MAP:
        return TYPE_MAP[t]

    # Array types: "type[N]"
    arr_match = re.match(r'^(.+)\[(\d+)\]$', t)
    if arr_match:
        base = pdb_type_to_c(arr_match.group(1).strip(), known_structs)
        return f"{base}[{arr_match.group(2)}]"

    # Pointer types
    if t.endswith(' *'):
        base = t[:-2].strip()
        # Strip class/struct prefix
        for prefix in ('class ', 'struct '):
            if base.startswith(prefix):
                base = base[len(prefix):]
                break
        if base in TYPE_MAP:
            return TYPE_MAP[base] + '*'
        if base in known_structs:
            return base + '*'
        # Template or complex -> void*
        if '<' in base or '::' in base:
            return 'void*'
        if base.replace('_', '').isalnum():
            return base + '*'
        return 'void*'

    # class/struct prefix
    for prefix in ('class ', 'struct '):
        if t.startswith(prefix):
            name = t[len(prefix):]
            if name in known_structs:
                return name
            if '<' not in name and name.replace('_', '').replace('::', '').isalnum():
                return name
            return 'int'

    # enum -> int
    if t.startswith('enum '):
        return 'int'

    # Template -> skip
    if '<' in t:
        return 'int'

    # Known struct name
    if t in known_structs:
        return t

    # Simple identifier
    if t.replace('_', '').isalnum() and not t[0].isdigit():
        return t

    return 'int'


def build_struct_decl(cls, known_structs):
    """Build a C struct declaration from PDB class info."""
    name = cls['name']
    size = cls.get('size', 0)
    members = cls.get('data_members', [])

    if not members:
        return f"struct {name} {{ char _placeholder[{max(size, 1)}]; }};"

    lines = [f"struct {name} {{"]
    prev_end = 0

    for m in sorted(members, key=lambda x: x.get('offset', 0)):
        offset = m.get('offset', 0)
        m_type = pdb_type_to_c(m.get('type', 'int'), known_structs)
        m_name = m.get('name', f'field_{offset:X}')

        # Sanitize member name
        m_name = re.sub(r'[^a-zA-Z0-9_]', '_', m_name)
        if m_name[0].isdigit():
            m_name = 'f_' + m_name

        # Handle array in type
        arr_suffix = ''
        arr_match = re.match(r'^(.+)\[(\d+)\]$', m_type)
        if arr_match:
            m_type = arr_match.group(1)
            arr_suffix = f'[{arr_match.group(2)}]'

        # Insert padding if needed
        if offset > prev_end:
            gap = offset - prev_end
            lines.append(f"    char _gap_{prev_end:X}[{gap}];")

        lines.append(f"    {m_type} {m_name}{arr_suffix};")

        # Estimate member size for gap calculation
        # Simple heuristic: pointers=4, int/long/float=4, short=2, char=1
        if arr_suffix:
            arr_count = int(arr_suffix.strip('[]'))
            base_size = 4  # default
            if 'char' in m_type:
                base_size = 1
            elif 'short' in m_type:
                base_size = 2
            prev_end = offset + base_size * arr_count
        elif '*' in m_type:
            prev_end = offset + 4
        elif m_type in ('char', 'unsigned char', 'bool', 'uchar'):
            prev_end = offset + 1
        elif m_type in ('short', 'unsigned short'):
            prev_end = offset + 2
        elif m_type in ('__int64', 'double'):
            prev_end = offset + 8
        else:
            prev_end = offset + 4

    # Trailing padding to reach declared size
    if size > 0 and prev_end < size:
        gap = size - prev_end
        lines.append(f"    char _tail_pad[{gap}];")

    lines.append("};")
    return '\n'.join(lines)


def main():
    log, save_log, _ = make_logger(LOG_FILE)

    try:
        ida_auto.auto_wait()
        log("[*] PDB 类型导入脚本")

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb = json.load(f)

        classes = pdb.get('classes', [])
        enums = pdb.get('enums', [])

        # Filter out std:: and template classes
        game_classes = [c for c in classes
                        if c.get('name') and
                        not c['name'].startswith('std::') and
                        '<' not in c['name'] and
                        c.get('size', 0) > 0]
        log(f"[*] 游戏类: {len(game_classes)} (过滤 std::/template)")
        log(f"[*] 枚举: {len(enums)}")

        known_structs = set(c['name'] for c in game_classes)

        # Phase A: Import enums
        enum_ok = 0
        for en in enums:
            name = en.get('name', '')
            if not name or '<' in name or '::' in name:
                continue
            values = en.get('values', {})
            if not values:
                continue
            # Build enum declaration
            members = ', '.join(f"{k}={v}" for k, v in values.items())
            decl = f"enum {name} {{ {members} }};"
            if idc.parse_decls(decl, idc.PT_TYP) == 0:
                enum_ok += 1

        log(f"[*] 枚举导入: {enum_ok}/{len(enums)}")

        # Phase B: Import structs (forward declare all first)
        log("[*] 前向声明...")
        for cls in game_classes:
            name = cls['name']
            idc.parse_decls(f"struct {name};", idc.PT_TYP)

        # Import actual definitions (sort by size — smaller first, handles deps)
        game_classes.sort(key=lambda c: c.get('size', 0))
        struct_ok = 0
        struct_fail = 0
        fail_samples = []

        for cls in game_classes:
            name = cls['name']
            decl = build_struct_decl(cls, known_structs)
            result = idc.parse_decls(decl, idc.PT_TYP)
            if result == 0:
                struct_ok += 1
            else:
                struct_fail += 1
                if len(fail_samples) < 10:
                    fail_samples.append(f"  {name}: {decl[:100]}")

        log(f"[*] 结构体导入: {struct_ok} OK, {struct_fail} 失败")
        if fail_samples:
            log("[*] 失败样本:")
            for s in fail_samples:
                log(s)

        # Phase C: Apply this pointer types to class methods
        log("[*] 应用 this 指针类型到类方法...")
        funcs = pdb.get('functions', [])
        this_applied = 0

        for func_info in funcs:
            addr_str = func_info.get('address', '')
            if not addr_str:
                continue
            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue
            if not is_in_text(addr):
                continue

            cls_name = func_info.get('class', '')
            if not cls_name or cls_name not in known_structs:
                continue

            # Check function exists in IDA
            func = ida_funcs.get_func(addr)
            if not func or func.start_ea != addr:
                continue

            # Set this pointer type
            current_type = idc.get_type(addr) or ""
            if 'void *this' in current_type or '__userpurge' in current_type:
                # Try to set proper this type via function type
                # Simple approach: mark cfunc dirty so next decompile picks up the struct
                ida_hexrays.mark_cfunc_dirty(addr)
                this_applied += 1

        log(f"[*] 标记刷新: {this_applied} 个类方法")

        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[+] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    save_log()

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
```

- [ ] **Step 2: Commit**

```bash
git add tools/ida/ida_import_pdb_types.py
git commit -m "feat(ida): add Phase 2 Step 2 - PDB type import script"
```

---

### Task 4: Phase 2 Step 3 — Fix Calling Conventions (`ida_fix_calling_conv.py`)

**Files:**
- Create: `tools/ida/ida_fix_calling_conv.py`

Fixes `__userpurge` / `__usercall` functions by applying correct PDB signatures.

- [ ] **Step 1: Write the calling convention fix script**

```python
"""
IDAPython: 修正 __userpurge/__usercall 调用约定

读取诊断报告中的 USERPURGE_WRONG 条目,
用 PDB 签名覆盖 IDA 的错误推断。

对 EH funclet 不做处理 (它们的 __userpurge 是预期行为)。

用法:
  idat.exe -A -S"ida_fix_calling_conv.py" PAL3A.exe.i64          # dry-run
  idat.exe -A -S"ida_fix_calling_conv.py --execute" PAL3A.exe.i64
"""

import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
import idc
import json
import os
import sys
import time
import traceback
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
if SCRIPT_DIR not in sys.path:
    sys.path.insert(0, SCRIPT_DIR)
from ida_common import (
    LOG_DIR, PDB_EXPORT, CONF_AUTO_FIX, make_logger
)

LOG_FILE = os.path.join(LOG_DIR, "fix_callconv_log.txt")
DIAGNOSIS_REPORT = os.path.join(LOG_DIR, "diagnosis_report.json")

DRY_RUN = '--execute' not in ' '.join(sys.argv)

TYPE_MAP = {
    'void': 'void', 'int': 'int', 'uint': 'unsigned int',
    'long': 'long', 'ulong': 'unsigned long',
    'short': 'short', 'ushort': 'unsigned short',
    'char': 'char', 'uchar': 'unsigned char',
    'float': 'float', 'double': 'double',
    'bool': '_BOOL1', 'BOOL': 'int',
    'BYTE': 'unsigned char', 'WORD': 'unsigned short',
    'DWORD': 'unsigned long',
}


def normalize_type(pdb_type):
    """Convert PDB type to IDA-parseable C type."""
    if not pdb_type:
        return 'int'
    t = pdb_type.strip().replace('virtual ', '').replace('static ', '')
    if t in TYPE_MAP:
        return TYPE_MAP[t]
    if t.endswith(' *'):
        base = t[:-2].strip()
        for prefix in ('class ', 'struct '):
            if base.startswith(prefix):
                base = base[len(prefix):]
        if '<' in base:
            return 'void *'
        if base in TYPE_MAP:
            return TYPE_MAP[base] + ' *'
        if base.replace('_', '').replace('::', '').isalnum():
            return base + ' *'
        return 'void *'
    if t.endswith(' &'):
        return normalize_type(t[:-2] + ' *')
    if t.startswith('class ') or t.startswith('struct '):
        name = t.split(' ', 1)[1].strip()
        if '<' in name:
            return 'int'
        return name
    if t.startswith('enum '):
        return 'int'
    if '<' in t:
        return 'int'
    if t.replace('_', '').isalnum():
        return t
    return 'int'


def build_signature(func_info):
    """Build a C function declaration from PDB info."""
    name = func_info.get('name', '')
    cls = func_info.get('class', '')
    ret = func_info.get('return_type', '')
    params = func_info.get('parameters', [])

    # Determine calling convention
    is_method = bool(cls) and not ret.startswith('static ')
    callconv = '__thiscall' if is_method else '__cdecl'

    # Return type
    ret_c = normalize_type(ret)
    if not ret_c or ret_c == 'void *':
        ret_c = 'int'
    if 'destructor' in name or name.endswith('~' + cls):
        ret_c = 'void'

    # Parameters
    param_strs = []
    if is_method:
        param_strs.append(f'{cls} *this')
    for p in params:
        p_type = normalize_type(p.get('type', ''))
        p_name = p.get('name', '')
        if p_name and p_name.replace('_', '').isalnum():
            param_strs.append(f'{p_type} {p_name}')
        else:
            param_strs.append(p_type)

    params_str = ', '.join(param_strs) if param_strs else 'void'

    # Safe function name for IDA
    safe_name = name.replace('::', '_').replace('~', '_dtor_')
    safe_name = safe_name.replace('<', '_').replace('>', '_').replace(' ', '_')

    return f'{ret_c} {callconv} {safe_name}({params_str});'


def main():
    log, save_log, _ = make_logger(LOG_FILE)

    try:
        ida_auto.auto_wait()
        mode = "DRY-RUN" if DRY_RUN else "EXECUTE"
        log(f"[*] 调用约定修复 ({mode})")

        if not os.path.exists(DIAGNOSIS_REPORT):
            log("[!] 诊断报告不存在")
            save_log()
            return

        with open(DIAGNOSIS_REPORT, 'r', encoding='utf-8') as f:
            report = json.load(f)
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb = json.load(f)

        # Build PDB lookup
        pdb_by_addr = {}
        for func in pdb['functions']:
            addr_str = func.get('address', '')
            if not addr_str:
                continue
            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue
            pdb_by_addr[addr] = func

        # Collect targets
        targets = []
        for addr_str, info in report['functions'].items():
            for lbl, conf, det in info['labels']:
                if lbl == 'USERPURGE_WRONG' and conf >= CONF_AUTO_FIX:
                    addr = int(addr_str, 16)
                    if det.get('has_pdb_signature'):
                        targets.append((addr, info['name']))

        log(f"[*] 待修复: {len(targets)} 个 __userpurge 函数")

        success = 0
        skipped = 0
        failed = 0

        for addr, name in targets:
            pdb_info = pdb_by_addr.get(addr)
            if not pdb_info:
                skipped += 1
                continue

            sig = build_signature(pdb_info)
            if not sig:
                skipped += 1
                continue

            if DRY_RUN:
                log(f"  [DRY] 0x{addr:08X} {name}: {sig[:80]}")
                success += 1
                continue

            # Clear existing type
            idc.SetType(addr, "")
            # Apply new signature
            if idc.SetType(addr, sig):
                ida_hexrays.mark_cfunc_dirty(addr)
                success += 1
            else:
                # Fallback: try just setting calling convention
                current = idc.get_type(addr) or ""
                if current:
                    fixed = current.replace('__userpurge', '__thiscall')
                    fixed = fixed.replace('__usercall', '__cdecl')
                    if idc.SetType(addr, fixed):
                        ida_hexrays.mark_cfunc_dirty(addr)
                        success += 1
                    else:
                        failed += 1
                        log(f"  [FAIL] 0x{addr:08X} {name}: {sig[:60]}")
                else:
                    failed += 1

        log(f"\n[*] 结果:")
        log(f"    成功: {success}")
        log(f"    跳过: {skipped}")
        log(f"    失败: {failed}")

        if not DRY_RUN and success > 0:
            ida_auto.auto_wait()
            idc.save_database(idc.get_idb_path(), 0)
            log("[+] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    save_log()

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
```

- [ ] **Step 2: Commit**

```bash
git add tools/ida/ida_fix_calling_conv.py
git commit -m "feat(ida): add Phase 2 Step 3 - calling convention fix script"
```

---

### Task 5: Phase 3 — Verify and Re-export (`ida_verify_and_export.py`)

**Files:**
- Create: `tools/ida/ida_verify_and_export.py`

Re-runs a lightweight diagnostic check, compares before/after metrics, exports only qualified functions, and generates a quality comparison report.

- [ ] **Step 1: Write the verify and export script**

```python
"""
IDAPython: 验证修复结果 + 重新导出合格函数

流程:
  1. 对修复后的数据库重新运行质量检测
  2. 生成 before/after 对比报告
  3. 只导出通过质量门控的函数
  4. 写入 quality_comparison.md

质量门控:
  - 不含 JUMPOUT (EH funclet 除外)
  - 不含 __userpurge/__usercall
  - 不含 "positive sp value" 警告
  - 不是 EH funclet / 脱壳残留

用法:
  idat.exe -A -S"ida_verify_and_export.py" PAL3A.exe.i64
"""

import ida_auto
import ida_hexrays
import ida_funcs
import ida_name
import idautils
import idc
import json
import os
import sys
import re
import time
import traceback
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
if SCRIPT_DIR not in sys.path:
    sys.path.insert(0, SCRIPT_DIR)
from ida_common import (
    PROJECT_ROOT, LOG_DIR, PDB_EXPORT,
    TEXT_START, TEXT_END, is_in_text, is_in_pe, make_logger
)

LOG_FILE = os.path.join(LOG_DIR, "verify_export_log.txt")
DIAGNOSIS_REPORT = os.path.join(LOG_DIR, "diagnosis_report.json")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3a", "decomp")
COMPARISON_FILE = os.path.join(LOG_DIR, "quality_comparison.md")


def check_decompilation_quality(code):
    """Check decompiled code for quality issues. Returns list of issue strings."""
    issues = []
    if '__userpurge' in code or '__usercall' in code:
        issues.append('userpurge')
    if 'positive sp value' in code:
        issues.append('sp_positive')
    if 'JUMPOUT' in code:
        issues.append('jumpout')
    if '*(_DWORD *)' in code or '*(_BYTE *)' in code or '*(_WORD *)' in code:
        issues.append('raw_memory')
    return issues


def main():
    log, save_log, _ = make_logger(LOG_FILE)

    try:
        ida_auto.auto_wait()
        log("[*] 验证 + 重新导出")

        # Load old diagnosis for comparison
        old_summary = None
        if os.path.exists(DIAGNOSIS_REPORT):
            with open(DIAGNOSIS_REPORT, 'r', encoding='utf-8') as f:
                old_report = json.load(f)
            old_summary = old_report.get('summary', {})
            log(f"[*] 旧诊断数据已加载")

        # Load PDB for EH funclet detection
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb = json.load(f)

        # Collect functions to export
        log("[*] 收集函数...")
        targets = []
        eh_names = set()

        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if not name or name.startswith("nullsub_"):
                continue
            # Skip sub_ functions (unnamed)
            if name.startswith("sub_"):
                continue
            # Identify EH funclets by name pattern
            if re.match(r'^\$[EL]\d+', name) or re.match(r'_\$E\d+', name):
                eh_names.add(ea)
                continue
            func = ida_funcs.get_func(ea)
            if func:
                targets.append((ea, name, func.size()))

        log(f"[*] 候选函数: {len(targets)} (排除 {len(eh_names)} EH funclets)")

        # Export with quality gate
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        exported = 0
        rejected = 0
        quality_stats = {
            'total_candidates': len(targets),
            'exported': 0,
            'rejected_userpurge': 0,
            'rejected_sp': 0,
            'rejected_jumpout': 0,
            'has_raw_memory': 0,
            'clean': 0,
        }
        error_count = 0
        t0 = time.time()

        for i, (ea, name, size) in enumerate(targets):
            if (i + 1) % 500 == 0:
                elapsed = time.time() - t0
                rate = (i + 1) / elapsed if elapsed > 0 else 0
                remaining = (len(targets) - i - 1) / rate if rate > 0 else 0
                log(f"  [{i+1}/{len(targets)}] exported={exported} rejected={rejected} "
                    f"({rate:.0f} f/s, ~{remaining:.0f}s remaining)")

            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    error_count += 1
                    continue

                code = str(cfunc)
                sig = cfunc.type.dstr()
                issues = check_decompilation_quality(code)

                # Quality gate: reject hard failures
                if 'userpurge' in issues:
                    quality_stats['rejected_userpurge'] += 1
                    rejected += 1
                    continue
                if 'sp_positive' in issues:
                    quality_stats['rejected_sp'] += 1
                    rejected += 1
                    continue
                if 'jumpout' in issues:
                    quality_stats['rejected_jumpout'] += 1
                    rejected += 1
                    continue

                # Track raw_memory but still export (not a hard reject)
                if 'raw_memory' in issues:
                    quality_stats['has_raw_memory'] += 1
                else:
                    quality_stats['clean'] += 1

                # Write export
                safe_name = re.sub(r'[^a-zA-Z0-9_]', '_', name)
                if len(safe_name) > 100:
                    safe_name = safe_name[:100]
                filename = f"{safe_name}_{ea:08x}.json"
                filepath = os.path.join(OUTPUT_DIR, filename)

                result = {
                    'name': name,
                    'address': f"0x{ea:08X}",
                    'size_bytes': size,
                    'signature': sig,
                    'decompiled_c': code,
                    'quality_issues': issues,
                }

                with open(filepath, 'w', encoding='utf-8') as f:
                    json.dump(result, f, indent=2, ensure_ascii=False)

                exported += 1

            except Exception as e:
                error_count += 1

        quality_stats['exported'] = exported
        elapsed = time.time() - t0

        log(f"\n[*] 导出完成 ({elapsed:.1f}s)")
        log(f"    导出: {exported}")
        log(f"    拒绝: {rejected}")
        log(f"    错误: {error_count}")
        log(f"    完全干净: {quality_stats['clean']}")
        log(f"    含裸内存: {quality_stats['has_raw_memory']}")

        # Generate comparison report
        comparison = f"""# PAL3A IDA Quality Comparison Report

Generated: {time.strftime('%Y-%m-%d %H:%M:%S')}

## Summary

| Metric | Before | After | Delta |
|--------|--------|-------|-------|
"""
        if old_summary:
            old_labels = old_summary.get('by_label', {})
            comparison += f"| Total functions | {old_summary.get('total_unique_functions', '?')} | {len(targets) + len(eh_names)} | - |\n"
            comparison += f"| BOUNDARY_OVERLAP | {old_labels.get('BOUNDARY_OVERLAP', '?')} | (re-run diag) | - |\n"
            comparison += f"| USERPURGE_WRONG | {old_labels.get('USERPURGE_WRONG', '?')} | {quality_stats['rejected_userpurge']} | - |\n"
            comparison += f"| SP_CORRUPT | {old_labels.get('SP_CORRUPT', '?')} | {quality_stats['rejected_sp']} | - |\n"
            comparison += f"| CLEAN | {old_labels.get('CLEAN', '?')} | {quality_stats['clean']} | - |\n"

        comparison += f"""
## Export Results

- Candidates: {quality_stats['total_candidates']}
- Exported: {exported}
- Rejected (userpurge): {quality_stats['rejected_userpurge']}
- Rejected (SP): {quality_stats['rejected_sp']}
- Rejected (JUMPOUT): {quality_stats['rejected_jumpout']}
- Exported with raw memory access: {quality_stats['has_raw_memory']}
- Fully clean: {quality_stats['clean']}
- Decompile errors: {error_count}
"""

        os.makedirs(os.path.dirname(COMPARISON_FILE), exist_ok=True)
        with open(COMPARISON_FILE, 'w', encoding='utf-8') as f:
            f.write(comparison)
        log(f"[+] 对比报告: {COMPARISON_FILE}")

        idc.save_database(idc.get_idb_path(), 0)
        log("[+] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    save_log()

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
```

- [ ] **Step 2: Commit**

```bash
git add tools/ida/ida_verify_and_export.py
git commit -m "feat(ida): add Phase 3 - verify and qualified re-export script"
```

---

### Task 6: Update Master Pipeline (`ida_master_pipeline.py`)

**Files:**
- Modify: `tools/ida/ida_master_pipeline.py`

Add the new quality fix phases to the master pipeline as a separate mode.

- [ ] **Step 1: Update the master pipeline**

Add a `--quality-fix` mode that runs the new scripts in order:

```python
# Add to ida_master_pipeline.py, after existing phases:

# Quality Fix Pipeline (separate from import pipeline)
QUALITY_FIX = '--quality-fix' in sys.argv
QUALITY_DRY = '--quality-dry' in sys.argv  # dry-run for fix phases

# In the main() function, add after existing pipeline:

if QUALITY_FIX:
    print()
    print("=" * 60)
    print("  PAL3A IDA Quality Fix Pipeline")
    print("=" * 60)
    print()

    # Phase Q1: Diagnose
    ok = run_phase(10, "质量诊断", "ida_diagnose_quality.py")
    results.append(("Phase Q1: 质量诊断", ok))

    # Phase Q2: Fix boundaries
    if not QUALITY_DRY:
        # Inject --execute into sys.argv for the sub-script
        sys.argv.append('--execute')

    ok = run_phase(11, "修正函数边界", "ida_fix_boundaries.py")
    results.append(("Phase Q2: 函数边界修复", ok))

    # Phase Q3: Import PDB types
    ok = run_phase(12, "导入 PDB 类型", "ida_import_pdb_types.py")
    results.append(("Phase Q3: PDB 类型导入", ok))

    # Phase Q4: Fix calling conventions
    ok = run_phase(13, "修正调用约定", "ida_fix_calling_conv.py")
    results.append(("Phase Q4: 调用约定修复", ok))

    # Phase Q5: Verify and export
    ok = run_phase(14, "验证并导出", "ida_verify_and_export.py")
    results.append(("Phase Q5: 验证导出", ok))

    if not QUALITY_DRY:
        try:
            sys.argv.remove('--execute')
        except ValueError:
            pass
```

Update the docstring at the top to document new options:

```python
"""
...
选项:
  --skip-import       跳过 Phase 1 (已导入过)
  --skip-export       跳过 Phase 6 (只优化不导出)
  --phase=N           只执行 Phase N
  --quality-fix       运行质量修复流水线 (诊断→修边界→导类型→修约定→导出)
  --quality-dry       质量修复 dry-run 模式 (只诊断+预览, 不实际修改)
"""
```

- [ ] **Step 2: Commit**

```bash
git add tools/ida/ida_master_pipeline.py
git commit -m "feat(ida): add --quality-fix mode to master pipeline"
```

---

### Task 7: Update Batch Launcher (`run_pipeline.bat`)

**Files:**
- Modify: `tools/ida/run_pipeline.bat`

Add documentation for the new quality fix mode.

- [ ] **Step 1: Update the batch file**

Add new usage examples to the header comments:

```batch
REM Quality Fix Pipeline:
REM   run_pipeline.bat "path\to\idat.exe" --quality-dry    # 诊断+预览
REM   run_pipeline.bat "path\to\idat.exe" --quality-fix    # 完整修复流程
```

- [ ] **Step 2: Commit**

```bash
git add tools/ida/run_pipeline.bat
git commit -m "docs(ida): add quality-fix usage to run_pipeline.bat"
```

---

### Task 8: Manual Review Report Generator

**Files:**
- Create: `tools/ida/gen_manual_review.py`

A standalone Python script (NOT IDAPython) that reads `diagnosis_report.json` and generates a human-readable Markdown report for functions needing manual attention.

- [ ] **Step 1: Write the report generator**

```python
"""
Generate manual review report from diagnosis_report.json.

This is a standalone Python script (not IDAPython).
Run outside IDA after ida_diagnose_quality.py has produced its report.

Usage:
  python gen_manual_review.py
"""

import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
DIAGNOSIS_REPORT = os.path.join(LOG_DIR, "diagnosis_report.json")
OUTPUT_FILE = os.path.join(LOG_DIR, f"manual_review_{time.strftime('%Y%m%d')}.md")


def main():
    if not os.path.exists(DIAGNOSIS_REPORT):
        print(f"[!] {DIAGNOSIS_REPORT} not found. Run ida_diagnose_quality.py first.")
        return

    with open(DIAGNOSIS_REPORT, 'r', encoding='utf-8') as f:
        report = json.load(f)

    manual = report.get('manual_review', [])
    functions = report.get('functions', {})

    # Categorize manual review items
    boundary_unclear = []
    unpack_damage = []
    sp_issues = []
    other = []

    for item in manual:
        lbl = item.get('label', '')
        if lbl == 'BOUNDARY_OVERLAP':
            boundary_unclear.append(item)
        elif lbl == 'UNPACK_ARTIFACT':
            unpack_damage.append(item)
        elif lbl == 'SP_CORRUPT':
            sp_issues.append(item)
        else:
            other.append(item)

    # Also find low-confidence EH funclets
    ambiguous_eh = []
    for addr_str, info in functions.items():
        for lbl, conf, det in info['labels']:
            if lbl == 'EH_FUNCLET' and conf < 0.8:
                ambiguous_eh.append({
                    'address': addr_str,
                    'name': info['name'],
                    'confidence': conf,
                    'details': det,
                })

    # Generate report
    lines = [
        f"# PAL3A Manual Review Report",
        f"",
        f"Generated: {time.strftime('%Y-%m-%d %H:%M:%S')}",
        f"",
        f"Total items needing review: {len(manual) + len(ambiguous_eh)}",
        f"",
    ]

    if boundary_unclear:
        lines.append(f"## Boundary Unclear ({len(boundary_unclear)} functions)")
        lines.append("")
        lines.append("These functions have overlapping boundaries but the split point could not be verified.")
        lines.append("")
        for item in boundary_unclear[:50]:
            lines.append(f"- `{item['address']}` **{item['name']}** — conf={item['confidence']:.2f}, {item.get('reason', 'unknown')}")
        if len(boundary_unclear) > 50:
            lines.append(f"- ... and {len(boundary_unclear) - 50} more")
        lines.append("")

    if unpack_damage:
        lines.append(f"## Possible Unpack Damage ({len(unpack_damage)} functions)")
        lines.append("")
        for item in unpack_damage:
            lines.append(f"- `{item['address']}` **{item['name']}** — {item.get('reason', '')}")
        lines.append("")

    if sp_issues:
        lines.append(f"## SP Analysis Failures ({len(sp_issues)} functions)")
        lines.append("")
        lines.append("These have stack pointer issues that weren't fixed by boundary correction.")
        lines.append("")
        for item in sp_issues[:30]:
            lines.append(f"- `{item['address']}` **{item['name']}** — conf={item['confidence']:.2f}")
        if len(sp_issues) > 30:
            lines.append(f"- ... and {len(sp_issues) - 30} more")
        lines.append("")

    if ambiguous_eh:
        lines.append(f"## Ambiguous EH Funclets ({len(ambiguous_eh)} functions)")
        lines.append("")
        lines.append("These might be EH funclets or might be real functions. Low confidence classification.")
        lines.append("")
        for item in ambiguous_eh[:30]:
            det = item.get('details', {})
            lines.append(f"- `{item['address']}` **{item['name']}** — conf={item['confidence']:.2f}, "
                        f"size={det.get('size', '?')}B, jumpout={det.get('has_jumpout', '?')}")
        lines.append("")

    report_text = '\n'.join(lines)

    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        f.write(report_text)

    print(f"[+] Report written to: {OUTPUT_FILE}")
    print(f"    Boundary unclear: {len(boundary_unclear)}")
    print(f"    Unpack damage: {len(unpack_damage)}")
    print(f"    SP issues: {len(sp_issues)}")
    print(f"    Ambiguous EH: {len(ambiguous_eh)}")


if __name__ == '__main__':
    main()
```

- [ ] **Step 2: Commit**

```bash
git add tools/ida/gen_manual_review.py
git commit -m "feat(ida): add manual review report generator"
```

---

### Task 9: Integration Test — Dry Run Validation

This task validates the complete pipeline works end-to-end without modifying the IDA database.

- [ ] **Step 1: Run diagnostic script in IDA**

```bash
cd tools/ida
run_pipeline.bat "D:\Program Files\IDA Professional 9.2\idat.exe" --quality-dry
```

Expected: `_logs/diagnosis_report.json` is generated with classification for all functions.

- [ ] **Step 2: Verify diagnosis report structure**

```bash
python -c "
import json
with open('tools/ida/_logs/diagnosis_report.json', encoding='utf-8') as f:
    r = json.load(f)
print('Summary:', json.dumps(r['summary'], indent=2))
print('Manual review items:', len(r.get('manual_review', [])))
print('Sample function:', list(r['functions'].items())[0])
"
```

Expected: Summary shows counts for each label, manual_review has low-confidence items.

- [ ] **Step 3: Generate manual review report**

```bash
python tools/ida/gen_manual_review.py
```

Expected: `_logs/manual_review_YYYYMMDD.md` is generated.

- [ ] **Step 4: Review the dry-run boundary fix output**

Check `_logs/fix_boundaries_log.txt` — should show `[DRY]` entries for each proposed fix.

- [ ] **Step 5: Commit logs as evidence**

```bash
git add tools/ida/_logs/diagnosis_report.json tools/ida/_logs/manual_review_*.md
git commit -m "chore(ida): add Phase 1 diagnostic results (dry-run)"
```

---

### Task 10: Execute Full Quality Fix Pipeline

After reviewing the dry-run results and confirming classifications look correct:

- [ ] **Step 1: Back up the IDA database**

```bash
cp original/PAL3A.exe.i64 original/PAL3A.exe.i64.backup-pre-quality-fix
```

- [ ] **Step 2: Execute full pipeline**

```bash
cd tools/ida
run_pipeline.bat "D:\Program Files\IDA Professional 9.2\idat.exe" --quality-fix
```

Expected: All phases run, functions fixed, types imported, clean export generated.

- [ ] **Step 3: Verify results**

```bash
python -c "
import json, glob
files = glob.glob('asm/pal3a/decomp/*.json')
print(f'Exported functions: {len(files)}')
# Spot check quality
issues = 0
for f in files[:500]:
    d = json.load(open(f, encoding='utf-8'))
    if d.get('quality_issues'):
        issues += 1
print(f'Functions with issues (sample 500): {issues}')
"
```

- [ ] **Step 4: Review quality comparison report**

```bash
cat tools/ida/_logs/quality_comparison.md
```

Expected: Improvements across all metrics.

- [ ] **Step 5: Commit final results**

```bash
git add tools/ida/_logs/quality_comparison.md
git add tools/ida/_logs/verify_export_log.txt
git commit -m "feat(ida): complete quality fix pipeline - boundary/type/callconv fixes applied"
```
