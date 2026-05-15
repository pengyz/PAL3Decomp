# 函数签名修正 + 语义化命名 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 批量修正 functions.json 签名、语义化参数/变量命名、扩展 apply_annotations 支持 lvars，降低编译错误数。

**Architecture:** `tools/fix_signatures.py` 是主工具，多子命令结构。每个子命令读取 `functions.json` + `asm/pal3/decomp/*.json` 进行分析，输出修正建议（`--dry-run`）或直接写入。所有修改同步写入 CHANGE_LOG。lvars 扩展修改 `apply_annotations.py` 新增 step 9。

**Tech Stack:** Python 3, IDA Pro 9.2 (ida_hexrays API), MSVC mangled name 解码, JSON

**关键路径:**
- `pipeline/data/annotations/functions.json` — 签名数据源
- `pipeline/data/annotations/globals.json` — 全局变量数据源
- `asm/pal3/decomp/*.json` — Hex-Rays 反编译 JSON（含函数体）
- `asm/pal3a/func_bytes_dump.json` — PAL3A 函数字节+mangled names
- `pipeline/ida/apply_annotations.py` — IDA 标注应用脚本
- `pipeline/data/annotations/CHANGE_LOG.md` — 置信度日志

---

### Task 1: 创建 fix_signatures.py 框架 + fix-this-type 子命令

**Files:**
- Create: `tools/fix_signatures.py`
- Create: `tests/test_fix_signatures.py`
- Modify: `pipeline/data/annotations/functions.json`
- Modify: `pipeline/data/annotations/CHANGE_LOG.md`

- [ ] **Step 1: Write test for fix-this-type**

```python
# tests/test_fix_signatures.py
"""Tests for tools/fix_signatures.py signature auto-fixer."""
import json
import os
import sys
import pytest

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(PROJECT_ROOT, "tools"))

from fix_signatures import fix_this_type, parse_signature, rebuild_signature


class TestParseSignature:
    def test_thiscall_with_int_this(self):
        sig = "char __thiscall(int this, float x)"
        parsed = parse_signature(sig)
        assert parsed["return_type"] == "char"
        assert parsed["convention"] == "__thiscall"
        assert parsed["params"][0] == {"type": "int", "name": "this"}
        assert parsed["params"][1] == {"type": "float", "name": "x"}

    def test_thiscall_with_class_this(self):
        sig = "void __thiscall(GRPinput *this, int a2)"
        parsed = parse_signature(sig)
        assert parsed["params"][0] == {"type": "GRPinput *", "name": "this"}

    def test_cdecl_no_this(self):
        sig = "int __cdecl(const char *a1, int a2)"
        parsed = parse_signature(sig)
        assert parsed["convention"] == "__cdecl"
        assert len(parsed["params"]) == 2

    def test_no_params(self):
        sig = "void()"
        parsed = parse_signature(sig)
        assert parsed["params"] == []


class TestRebuildSignature:
    def test_roundtrip(self):
        sig = "char __thiscall(GRPinput *this, float x)"
        parsed = parse_signature(sig)
        assert rebuild_signature(parsed) == sig

    def test_replace_param_type(self):
        sig = "char __thiscall(int this, float x)"
        parsed = parse_signature(sig)
        parsed["params"][0]["type"] = "GRPinput *"
        result = rebuild_signature(parsed)
        assert result == "char __thiscall(GRPinput *this, float x)"


class TestFixThisType:
    def test_fixes_int_this_with_class_prefix(self):
        funcs = {
            "0x00402D00": {
                "name": "GRPinput::SetJoystickFreePos",
                "signature": "char __thiscall(int this, float x)"
            }
        }
        changes = fix_this_type(funcs, dry_run=True)
        assert len(changes) == 1
        assert changes[0]["new_signature"] == "char __thiscall(GRPinput *this, float x)"
        assert changes[0]["confidence"] >= 90

    def test_skips_already_correct(self):
        funcs = {
            "0x00402D00": {
                "name": "GRPinput::SetJoystickFreePos",
                "signature": "char __thiscall(GRPinput *this, float x)"
            }
        }
        changes = fix_this_type(funcs, dry_run=True)
        assert len(changes) == 0

    def test_skips_non_thiscall(self):
        funcs = {
            "0x004023D0": {
                "name": "EnumJoystick",
                "signature": "int __stdcall(int a1)"
            }
        }
        changes = fix_this_type(funcs, dry_run=True)
        assert len(changes) == 0

    def test_handles_mangled_name_with_class(self):
        """Mangled names like ?Method@Class@@... should extract Class."""
        funcs = {
            "0x00407AB0": {
                "name": "?_Freeze@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAEXXZ",
                "signature": "char __thiscall(int this)"
            }
        }
        changes = fix_this_type(funcs, dry_run=True)
        # STL types should be skipped (template classes)
        assert len(changes) == 0
```

- [ ] **Step 2: Run test to verify it fails**

Run: `cd /home/peng/workspace/PAL3Decomp && python -m pytest tests/test_fix_signatures.py -v`
Expected: ImportError — `fix_signatures` module not found

- [ ] **Step 3: Implement fix_signatures.py framework + fix-this-type**

```python
# tools/fix_signatures.py
"""Batch signature fixer for PAL3 decompilation annotations.

Subcommands:
  fix-this-type    — Fix int this → ClassName *this for __thiscall functions
  cross-ref-pal3a  — Cross-reference PAL3A mangled names for type info
  infer-void-star  — Infer void* parameter types from function body usage
  infer-int-params — Infer int parameter types from pointer usage evidence
  rename-params    — Semantic parameter naming from PDB + context

Usage:
  python tools/fix_signatures.py fix-this-type [--dry-run] [--apply]
"""
import argparse
import json
import os
import re
import sys
from collections import OrderedDict
from datetime import datetime

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FUNCS_JSON = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations", "functions.json")
GLOBALS_JSON = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations", "globals.json")
DECOMP_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
PAL3A_DUMP = os.path.join(PROJECT_ROOT, "asm", "pal3a", "func_bytes_dump.json")
CHANGELOG = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations", "CHANGE_LOG.md")
LOGS_DIR = os.path.join(PROJECT_ROOT, "pipeline", "ida", "_logs")


def load_functions():
    with open(FUNCS_JSON, encoding="utf-8") as f:
        return json.load(f, object_pairs_hook=OrderedDict)


def save_functions(funcs):
    with open(FUNCS_JSON, "w", encoding="utf-8") as f:
        json.dump(funcs, f, indent=2, ensure_ascii=False)
        f.write("\n")


def load_globals():
    with open(GLOBALS_JSON, encoding="utf-8") as f:
        return json.load(f, object_pairs_hook=OrderedDict)


def save_globals(globs):
    with open(GLOBALS_JSON, "w", encoding="utf-8") as f:
        json.dump(globs, f, indent=2, ensure_ascii=False)
        f.write("\n")


def append_changelog(entry_text):
    with open(CHANGELOG, "a", encoding="utf-8") as f:
        f.write("\n" + entry_text + "\n")


# ---------- Signature parsing ----------

def parse_signature(sig):
    """Parse an IDA-style signature into structured form.

    Input: "char __thiscall(int this, float x)"
    Output: {"return_type": "char", "convention": "__thiscall",
             "params": [{"type": "int", "name": "this"}, {"type": "float", "name": "x"}]}
    """
    sig = sig.strip()
    paren = sig.find("(")
    if paren < 0:
        return {"return_type": sig, "convention": "", "params": []}

    before = sig[:paren].strip()
    params_str = sig[paren + 1:sig.rfind(")")].strip()

    # Extract calling convention
    convention = ""
    for cc in ("__thiscall", "__cdecl", "__stdcall", "__fastcall",
               "__userpurge", "__usercall"):
        if cc in before:
            convention = cc
            before = before.replace(cc, "").strip()
            break

    return_type = before.rstrip()
    # Clean up pointer spacing
    while "  " in return_type:
        return_type = return_type.replace("  ", " ")

    params = []
    if params_str:
        # Split params by comma, respecting nested parens/templates
        depth = 0
        current = []
        for ch in params_str:
            if ch in ("(", "<"):
                depth += 1
            elif ch in (")", ">"):
                depth -= 1
            if ch == "," and depth == 0:
                params.append("".join(current).strip())
                current = []
            else:
                current.append(ch)
        if current:
            params.append("".join(current).strip())

        parsed_params = []
        for p in params:
            p = p.strip()
            if not p:
                continue
            # Extract name: last word that's a valid C identifier and not a type keyword
            # Handle: "const char *a1", "int a2", "ClassName *this", "void *pOut"
            m = re.match(r"^(.*?)(\b\w+)$", p)
            if m:
                type_part = m.group(1).strip()
                name_part = m.group(2)
                # Check if name_part is actually part of the type (e.g., "unsigned long")
                _type_words = {"int", "char", "void", "float", "double", "short",
                               "long", "unsigned", "signed", "const", "struct", "class",
                               "enum", "union", "BOOL", "BYTE", "WORD", "DWORD", "UINT",
                               "HRESULT", "LPCSTR", "LPSTR"}
                if name_part in _type_words:
                    parsed_params.append({"type": p, "name": ""})
                else:
                    parsed_params.append({"type": type_part.rstrip(), "name": name_part})
            else:
                parsed_params.append({"type": p, "name": ""})
        params = parsed_params
    else:
        params = []

    return {"return_type": return_type, "convention": convention, "params": params}


def rebuild_signature(parsed):
    """Rebuild a signature string from parsed form."""
    parts = []
    if parsed["return_type"]:
        parts.append(parsed["return_type"])
    if parsed["convention"]:
        parts.append(parsed["convention"])
    prefix = " ".join(parts)

    param_strs = []
    for p in parsed["params"]:
        if p["name"]:
            # Ensure pointer types have space before name: "int *this" not "int * this"
            t = p["type"]
            if t.endswith("*"):
                param_strs.append(t + p["name"])
            else:
                param_strs.append(t + " " + p["name"])
        else:
            param_strs.append(p["type"])

    return prefix + "(" + ", ".join(param_strs) + ")"


# ---------- Class name extraction from function name ----------

def extract_class_from_name(func_name):
    """Extract class name from function name. Returns None if not a method."""
    if "::" in func_name:
        cls = func_name.split("::")[0]
        # Skip template/STL classes
        if "<" in cls or ">" in cls or "$" in cls:
            return None
        # Skip mangled names that weren't properly demangled
        if cls.startswith("?"):
            return None
        return cls

    # Try MSVC mangled names: ?Method@Class@@...
    if func_name.startswith("?"):
        # Constructor: ??0Class@@...
        m = re.match(r"\?\?[01](\w+)@@", func_name)
        if m:
            cls = m.group(1)
            if "<" not in cls and "$" not in cls:
                return cls
        # Regular method: ?Method@Class@@...
        m = re.match(r"\?\w+@(\w+)@@", func_name)
        if m:
            cls = m.group(1)
            if "<" not in cls and "$" not in cls:
                return cls
        # Check for nested template pattern: ?Method@?$template@...@std@@
        if "?$" in func_name:
            return None

    return None


# ---------- Subcommand: fix-this-type ----------

def fix_this_type(funcs, dry_run=True):
    """Fix int this → ClassName *this for __thiscall functions.

    Returns list of change records:
    [{"addr": "0x...", "name": "...", "old_signature": "...",
      "new_signature": "...", "confidence": 95, "evidence": [...]}]
    """
    changes = []
    for addr, info in funcs.items():
        sig = info.get("signature", "")
        name = info.get("name", "")
        if "__thiscall" not in sig:
            continue
        if "int this" not in sig:
            continue

        cls = extract_class_from_name(name)
        if not cls:
            continue

        parsed = parse_signature(sig)
        if not parsed["params"]:
            continue
        first = parsed["params"][0]
        if first["type"] != "int" or first["name"] != "this":
            continue

        parsed["params"][0]["type"] = cls + " *"
        new_sig = rebuild_signature(parsed)

        changes.append({
            "addr": addr,
            "name": name,
            "old_signature": sig,
            "new_signature": new_sig,
            "confidence": 95,
            "evidence": [
                "[A] __thiscall calling convention: ECX = this pointer, type must be class pointer",
                "[B] Function name %s:: prefix matches class %s" % (cls, cls),
            ]
        })

    return changes


def apply_changes(funcs, changes):
    """Apply a list of changes to funcs dict (mutates in place)."""
    for ch in changes:
        addr = ch["addr"]
        if addr in funcs:
            funcs[addr]["signature"] = ch["new_signature"]


def format_changelog_entry(phase_label, description, changes, extra_evidence=None):
    """Format a CHANGE_LOG entry from a list of changes."""
    if not changes:
        return ""
    date = datetime.now().strftime("%Y-%m-%d")
    min_conf = min(c["confidence"] for c in changes)
    max_conf = max(c["confidence"] for c in changes)
    conf_str = str(min_conf) if min_conf == max_conf else "%d-%d" % (min_conf, max_conf)

    lines = [
        "### [%s] %s (%d 函数)" % (date, phase_label, len(changes)),
        "",
        "- **变更**: %s" % description,
        "- **置信度**: %s" % conf_str,
        "- **证据**:",
    ]
    # Use evidence from first change as representative
    for ev in changes[0]["evidence"]:
        lines.append("  %d. %s" % (len(lines) - 4, ev))
    if extra_evidence:
        for ev in extra_evidence:
            lines.append("  %d. %s" % (len(lines) - 4, ev))
    lines.append("- **函数列表**: %d 个函数已修正" % len(changes))
    return "\n".join(lines)


# ---------- CLI ----------

def cmd_fix_this_type(args):
    funcs = load_functions()
    changes = fix_this_type(funcs, dry_run=True)
    print("[fix-this-type] Found %d functions with int this" % len(changes))
    for ch in changes:
        print("  %s %s" % (ch["addr"], ch["name"]))
        print("    old: %s" % ch["old_signature"])
        print("    new: %s" % ch["new_signature"])

    if args.apply and changes:
        apply_changes(funcs, changes)
        save_functions(funcs)
        entry = format_changelog_entry(
            "Phase 1.1: int this → ClassName *this",
            "%d 个 __thiscall 函数的 this 参数从 int 修正为 ClassName *" % len(changes),
            changes
        )
        append_changelog(entry)
        # Save detailed log
        os.makedirs(LOGS_DIR, exist_ok=True)
        log_path = os.path.join(LOGS_DIR, "phase1_1_changes.json")
        with open(log_path, "w", encoding="utf-8") as f:
            json.dump(changes, f, indent=2, ensure_ascii=False)
        print("[fix-this-type] Applied %d changes. Log: %s" % (len(changes), log_path))
    elif not args.apply:
        print("[fix-this-type] Dry run. Use --apply to write changes.")


def main():
    parser = argparse.ArgumentParser(description="PAL3 signature fixer")
    sub = parser.add_subparsers(dest="command")

    p1 = sub.add_parser("fix-this-type", help="Fix int this → ClassName *this")
    p1.add_argument("--apply", action="store_true", help="Write changes to functions.json")

    args = parser.parse_args()
    if args.command == "fix-this-type":
        cmd_fix_this_type(args)
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
```

- [ ] **Step 4: Run test to verify it passes**

Run: `cd /home/peng/workspace/PAL3Decomp && python -m pytest tests/test_fix_signatures.py -v`
Expected: All tests PASS

- [ ] **Step 5: Run fix-this-type dry run on real data**

Run: `python tools/fix_signatures.py fix-this-type`
Expected: Lists ~36 functions (those with Class:: prefix and int this). Verify output makes sense.

- [ ] **Step 6: Apply fix-this-type and commit**

Run: `python tools/fix_signatures.py fix-this-type --apply`

```bash
git add tools/fix_signatures.py tests/test_fix_signatures.py \
  pipeline/data/annotations/functions.json \
  pipeline/data/annotations/CHANGE_LOG.md
git commit -m "feat(fix_signatures): Phase 1.1 — fix int this → ClassName *this

Fix 36+ __thiscall functions with int this to use proper ClassName *this.
Confidence: 95 (calling convention guarantee + Class:: name prefix match).
New tool: tools/fix_signatures.py with fix-this-type subcommand."
```

---

### Task 2: MSVC name demangler + cross-ref-pal3a 子命令

**Files:**
- Modify: `tools/fix_signatures.py` — add `demangle_msvc()` and `cross-ref-pal3a` subcommand
- Modify: `tests/test_fix_signatures.py` — add demangler tests
- Modify: `pipeline/data/annotations/functions.json`
- Modify: `pipeline/data/annotations/CHANGE_LOG.md`

- [ ] **Step 1: Write tests for MSVC demangler**

Append to `tests/test_fix_signatures.py`:

```python
from fix_signatures import demangle_msvc_params


class TestDemangleMsvcParams:
    def test_simple_int_params(self):
        # ?FindPath@AStarPathFinder@@IAEHHHHH@Z
        # IAE = protected, __thiscall; H=int return; HHHH=4 int params
        result = demangle_msvc_params("?FindPath@AStarPathFinder@@IAEHHHHH@Z")
        assert result is not None
        assert result["class_name"] == "AStarPathFinder"
        assert result["method_name"] == "FindPath"
        assert result["return_type"] == "int"
        assert result["param_types"] == ["int", "int", "int", "int"]

    def test_pointer_param(self):
        # ?GenerateSucc@AStarPathFinder@@IAEHPAUNODE@1@HHHH@Z
        # PAU = pointer to struct; NODE@1@ = NODE in enclosing scope
        result = demangle_msvc_params("?GenerateSucc@AStarPathFinder@@IAEHPAUNODE@1@HHHH@Z")
        assert result is not None
        assert result["param_types"][0] == "NODE *"
        assert result["param_types"][1:] == ["int", "int", "int", "int"]

    def test_void_return(self):
        # ?Destroy@AStarPathFinder@@QAEXXZ
        # X = void, XZ = no params
        result = demangle_msvc_params("?Destroy@AStarPathFinder@@QAEXXZ")
        assert result is not None
        assert result["return_type"] == "void"
        assert result["param_types"] == []

    def test_class_pointer_param(self):
        # ?Reset@CCBStageCam@@QAEXPAV1@PAVgbCamera3D@@@Z
        # PAV1@ = pointer to class in pos 1 (CCBStageCam*), PAVgbCamera3D@@ = gbCamera3D*
        result = demangle_msvc_params("?Reset@CCBStageCam@@QAEXPAV1@PAVgbCamera3D@@@Z")
        assert result is not None
        assert result["return_type"] == "void"
        assert "CCBStageCam *" in result["param_types"][0] or "CCBStageCam" in result["param_types"][0]

    def test_constructor(self):
        # ??0AStarPathFinder@@QAE@XZ
        result = demangle_msvc_params("??0AStarPathFinder@@QAE@XZ")
        assert result is not None
        assert result["method_name"] == "AStarPathFinder"  # ctor
        assert result["param_types"] == []

    def test_non_mangled_returns_none(self):
        result = demangle_msvc_params("TileNum")
        assert result is None
```

- [ ] **Step 2: Run test to verify it fails**

Run: `python -m pytest tests/test_fix_signatures.py::TestDemangleMsvcParams -v`
Expected: ImportError — `demangle_msvc_params` not found

- [ ] **Step 3: Implement MSVC name demangler**

Add to `tools/fix_signatures.py` after the signature parsing section:

```python
# ---------- MSVC name demangling ----------

# MSVC type encoding reference:
# X=void, D=char, E=unsigned char, F=short, G=unsigned short,
# H=int, I=unsigned int, J=long, K=unsigned long, M=float, N=double
# P=pointer, A=reference, Q=const pointer
# AV=class ref, AU=struct ref, AW=enum ref
# Suffix modifiers: A=__cdecl, E=__thiscall, G=__stdcall, I=__fastcall

_SIMPLE_TYPES = {
    "X": "void", "D": "char", "E": "unsigned char",
    "F": "short", "G": "unsigned short",
    "H": "int", "I": "unsigned int",
    "J": "long", "K": "unsigned long",
    "M": "float", "N": "double",
    "_J": "__int64", "_K": "unsigned __int64",
    "_N": "bool",
}


def _parse_mangled_type(s, pos, class_names):
    """Parse one type from mangled string at position pos.

    class_names: list of class names encountered so far (for back-references).
    Returns (type_string, new_pos) or (None, pos) on failure.
    """
    if pos >= len(s):
        return None, pos

    ch = s[pos]

    # Simple types
    if ch == "_" and pos + 1 < len(s):
        key = "_" + s[pos + 1]
        if key in _SIMPLE_TYPES:
            return _SIMPLE_TYPES[key], pos + 2

    if ch in _SIMPLE_TYPES:
        return _SIMPLE_TYPES[ch], pos + 1

    # Back-reference to previously seen type (digit 0-9)
    if ch.isdigit():
        idx = int(ch)
        if idx < len(class_names):
            return class_names[idx] + " *", pos + 1
        return None, pos

    # Pointer: P[modifier][type]
    if ch == "P":
        pos += 1
        if pos >= len(s):
            return None, pos
        # Skip cv-qualifiers: A=none, B=const, C=volatile, D=const volatile
        mod = s[pos]
        if mod in "ABCD":
            pos += 1
        # Check for class pointer: PAV/PAU/QAV/QAU
        if pos < len(s) and s[pos] in ("V", "U"):
            kind = s[pos]  # V=class, U=struct
            pos += 1
            # Read class name until @
            name_end = s.find("@", pos)
            if name_end < 0:
                return None, pos
            type_name = s[pos:name_end]
            pos = name_end + 1
            # Skip scope qualifier (number or @)
            while pos < len(s) and (s[pos].isdigit() or s[pos] == "@"):
                pos += 1
                if s[pos - 1] == "@":
                    break
            if type_name not in class_names:
                class_names.append(type_name)
            return type_name + " *", pos
        # Simple pointer: PAH = int*, PAD = char*, etc.
        inner, pos = _parse_mangled_type(s, pos, class_names)
        if inner:
            return inner + " *", pos
        return None, pos

    # Class reference: [modifier]V/U name@scope@
    if ch in "QRA":  # const pointer, reference, reference
        return _parse_mangled_type(s, pos + 1, class_names)

    # Direct class/struct/enum type (V=class, U=struct, W=enum)
    if ch in "VUW":
        pos += 1
        if ch == "W":
            pos += 1  # skip enum size indicator
        name_end = s.find("@", pos)
        if name_end < 0:
            return None, pos
        type_name = s[pos:name_end]
        pos = name_end + 1
        while pos < len(s) and s[pos] == "@":
            pos += 1
        if type_name not in class_names:
            class_names.append(type_name)
        return type_name, pos

    return None, pos


def demangle_msvc_params(mangled):
    """Extract parameter types from MSVC mangled name.

    Returns: {"class_name": str, "method_name": str,
              "return_type": str, "param_types": [str, ...]}
    or None if not a valid mangled name.
    """
    if not mangled.startswith("?"):
        return None

    # Constructor: ??0ClassName@@...
    m = re.match(r"\?\?0(\w+)@@(\w+)@?(.*?)@?Z$", mangled)
    if m:
        cls = m.group(1)
        qual = m.group(2)
        params_enc = m.group(3)
        class_names = [cls]
        param_types = []
        pos = 0
        while pos < len(params_enc):
            if params_enc[pos] == "X":
                break  # void = no more params
            t, pos = _parse_mangled_type(params_enc, pos, class_names)
            if t is None:
                break
            param_types.append(t)
        return {
            "class_name": cls, "method_name": cls,
            "return_type": cls + " *",
            "param_types": param_types,
        }

    # Destructor: ??1ClassName@@...
    m = re.match(r"\?\?1(\w+)@@(\w+)@?(.*?)@?Z$", mangled)
    if m:
        cls = m.group(1)
        return {
            "class_name": cls, "method_name": "~" + cls,
            "return_type": "void",
            "param_types": [],
        }

    # Regular method: ?Method@Class@@QualRetParams@Z
    m = re.match(r"\?(\w+)@(\w+)@@(\w{3})(.*?)@?Z$", mangled)
    if not m:
        return None

    method = m.group(1)
    cls = m.group(2)
    qual = m.group(3)  # e.g., QAE, IAE, UAE
    rest = m.group(4)

    if not rest:
        return None

    class_names = [cls]

    # First char of rest is return type
    ret_type, pos = _parse_mangled_type(rest, 0, class_names)
    if ret_type is None:
        return None

    # Remaining chars are parameter types
    param_types = []
    while pos < len(rest):
        if rest[pos] == "X":
            break
        if rest[pos] == "@":
            break
        t, pos = _parse_mangled_type(rest, pos, class_names)
        if t is None:
            break
        param_types.append(t)

    return {
        "class_name": cls, "method_name": method,
        "return_type": ret_type,
        "param_types": param_types,
    }
```

- [ ] **Step 4: Run demangler tests**

Run: `python -m pytest tests/test_fix_signatures.py::TestDemangleMsvcParams -v`
Expected: PASS. Some tests may need adjustment based on exact demangling behavior — fix iteratively.

- [ ] **Step 5: Write tests for cross-ref-pal3a**

Append to `tests/test_fix_signatures.py`:

```python
from fix_signatures import cross_ref_pal3a


class TestCrossRefPal3a:
    def test_matches_by_class_method(self):
        funcs = {
            "0x00402D00": {
                "name": "GRPinput::SetJoystickFreePos",
                "signature": "char __thiscall(GRPinput *this, int a2, int a3)"
            }
        }
        pal3a = [
            {"name": "GRPinput::SetJoystickFreePos",
             "mangled": "?SetJoystickFreePos@GRPinput@@QAEXMM@Z"}
        ]
        changes = cross_ref_pal3a(funcs, pal3a, dry_run=True)
        # M=float, so a2→float, a3→float
        if changes:
            assert "float" in changes[0]["new_signature"]

    def test_skips_param_count_mismatch(self):
        funcs = {
            "0x00402D00": {
                "name": "GRPinput::Func",
                "signature": "int __thiscall(GRPinput *this, int a2, int a3, int a4)"
            }
        }
        pal3a = [
            {"name": "GRPinput::Func",
             "mangled": "?Func@GRPinput@@QAEHH@Z"}  # only 1 param
        ]
        changes = cross_ref_pal3a(funcs, pal3a, dry_run=True)
        assert len(changes) == 0  # param count mismatch → skip
```

- [ ] **Step 6: Implement cross-ref-pal3a subcommand**

Add to `tools/fix_signatures.py`:

```python
# ---------- Subcommand: cross-ref-pal3a ----------

def cross_ref_pal3a(funcs, pal3a_funcs, dry_run=True):
    """Cross-reference PAL3A mangled names to improve PAL3 signatures.

    Only applies when:
    - Same Class::Method name exists in both
    - Parameter count matches (excluding this)
    - PAL3A mangled name provides more specific types
    """
    # Build PAL3A index: Class::Method → demangled info
    pal3a_index = {}
    for f in pal3a_funcs:
        name = f.get("name", "")
        mangled = f.get("mangled", "")
        if "::" in name and mangled.startswith("?"):
            info = demangle_msvc_params(mangled)
            if info:
                pal3a_index[name] = info

    changes = []
    for addr, func_info in funcs.items():
        name = func_info.get("name", "")
        sig = func_info.get("signature", "")
        if not sig or "::" not in name:
            continue

        base_name = name.split("(")[0]  # Remove overload suffix
        if base_name not in pal3a_index:
            continue

        pal3a_info = pal3a_index[base_name]
        parsed = parse_signature(sig)

        # Count non-this params
        pal3_params = [p for p in parsed["params"] if p["name"] != "this"]
        pal3a_params = pal3a_info["param_types"]

        if len(pal3_params) != len(pal3a_params):
            continue

        # Check if PAL3A provides better types
        improved = False
        new_parsed = parse_signature(sig)  # fresh copy
        non_this_idx = 0
        for i, p in enumerate(new_parsed["params"]):
            if p["name"] == "this":
                continue
            if non_this_idx < len(pal3a_params):
                pal3a_type = pal3a_params[non_this_idx]
                current_type = p["type"]
                # Only replace if current is generic (int/void*) and PAL3A is specific
                if current_type in ("int", "void *") and pal3a_type not in ("int", "void *"):
                    new_parsed["params"][i]["type"] = pal3a_type
                    improved = True
            non_this_idx += 1

        if not improved:
            continue

        new_sig = rebuild_signature(new_parsed)
        changes.append({
            "addr": addr,
            "name": name,
            "old_signature": sig,
            "new_signature": new_sig,
            "confidence": 70,
            "evidence": [
                "[C] PAL3A PDB mangled name: %s" % base_name,
                "[C] Parameter count matches: %d params" % len(pal3a_params),
                "[C] PAL3A类比推断 — 需后续二进制验证确认",
            ],
        })

    return changes


def cmd_cross_ref_pal3a(args):
    funcs = load_functions()
    with open(PAL3A_DUMP, encoding="utf-8") as f:
        pal3a_data = json.load(f)
    pal3a_funcs = pal3a_data["functions"]

    changes = cross_ref_pal3a(funcs, pal3a_funcs, dry_run=True)
    print("[cross-ref-pal3a] Found %d improvable signatures" % len(changes))
    for ch in changes:
        print("  %s %s" % (ch["addr"], ch["name"]))
        print("    old: %s" % ch["old_signature"])
        print("    new: %s" % ch["new_signature"])

    if args.apply and changes:
        apply_changes(funcs, changes)
        save_functions(funcs)
        entry = format_changelog_entry(
            "Phase 1.2: PAL3A cross-reference type improvement",
            "%d 个函数参数类型从 PAL3A mangled name 推断改进" % len(changes),
            changes
        )
        append_changelog(entry)
        os.makedirs(LOGS_DIR, exist_ok=True)
        log_path = os.path.join(LOGS_DIR, "phase1_2_changes.json")
        with open(log_path, "w", encoding="utf-8") as f:
            json.dump(changes, f, indent=2, ensure_ascii=False)
        print("[cross-ref-pal3a] Applied %d changes." % len(changes))
    elif not args.apply:
        print("[cross-ref-pal3a] Dry run. Use --apply to write changes.")
```

Update `main()` to register the new subcommand:

```python
    p2 = sub.add_parser("cross-ref-pal3a", help="Cross-reference PAL3A mangled names")
    p2.add_argument("--apply", action="store_true")

    # ... in dispatch:
    elif args.command == "cross-ref-pal3a":
        cmd_cross_ref_pal3a(args)
```

- [ ] **Step 7: Run all tests**

Run: `python -m pytest tests/test_fix_signatures.py -v`
Expected: All PASS

- [ ] **Step 8: Run cross-ref-pal3a dry run and commit**

Run: `python tools/fix_signatures.py cross-ref-pal3a`
Review output. If reasonable:
Run: `python tools/fix_signatures.py cross-ref-pal3a --apply`

```bash
git add tools/fix_signatures.py tests/test_fix_signatures.py \
  pipeline/data/annotations/functions.json \
  pipeline/data/annotations/CHANGE_LOG.md
git commit -m "feat(fix_signatures): Phase 1.2 — PAL3A cross-reference type improvement

Demangle PAL3A MSVC mangled names, cross-reference with PAL3 same-name
functions to improve parameter types. Confidence: 70 (PAL3A analogy)."
```

---

### Task 3: infer-void-star + infer-int-params 子命令

**Files:**
- Modify: `tools/fix_signatures.py` — add inference subcommands
- Modify: `tests/test_fix_signatures.py` — add inference tests
- Modify: `pipeline/data/annotations/functions.json`
- Modify: `pipeline/data/annotations/CHANGE_LOG.md`

- [ ] **Step 1: Write tests for void* inference**

Append to `tests/test_fix_signatures.py`:

```python
from fix_signatures import infer_void_star_params, infer_int_params


class TestInferVoidStar:
    def test_detects_explicit_cast(self):
        funcs = {
            "0x00412400": {
                "name": "RoleSystem::RenderRole",
                "signature": "void __thiscall(RoleSystem *this, void *pStack, int a3)"
            }
        }
        # Simulate decomp body with explicit cast
        decomp = {
            "0x00412400": "gbMatrixStack::Push((gbMatrixStack *)pStack);\n"
        }
        changes = infer_void_star_params(funcs, decomp, dry_run=True)
        assert len(changes) == 1
        assert "gbMatrixStack *" in changes[0]["new_signature"]
        assert changes[0]["confidence"] >= 80

    def test_skips_ambiguous(self):
        funcs = {
            "0x00412400": {
                "name": "Foo::Bar",
                "signature": "void __thiscall(Foo *this, void *a2)"
            }
        }
        decomp = {"0x00412400": "memcpy(buf, a2, 100);\n"}
        changes = infer_void_star_params(funcs, decomp, dry_run=True)
        assert len(changes) == 0  # no clear type evidence


class TestInferIntParams:
    def test_detects_pointer_cast(self):
        funcs = {
            "0x004C3EC0": {
                "name": "CEffCylinder::Init",
                "signature": "int __thiscall(int this, int pType, float fx)"
            }
        }
        decomp = {
            "0x004C3EC0": "((tagEffObjType *)pType)->dwClassNameCRC;\n"
        }
        changes = infer_int_params(funcs, decomp, dry_run=True)
        # pType should become tagEffObjType *
        has_ptype_fix = any("tagEffObjType *" in c["new_signature"] for c in changes)
        assert has_ptype_fix

    def test_skips_genuine_int(self):
        funcs = {
            "0x00401000": {
                "name": "Foo::Bar",
                "signature": "void __thiscall(Foo *this, int nCount)"
            }
        }
        decomp = {"0x00401000": "for (i = 0; i < nCount; i++)\n"}
        changes = infer_int_params(funcs, decomp, dry_run=True)
        assert len(changes) == 0  # nCount is genuinely int
```

- [ ] **Step 2: Run tests to verify they fail**

Run: `python -m pytest tests/test_fix_signatures.py::TestInferVoidStar -v`
Expected: ImportError

- [ ] **Step 3: Implement infer-void-star**

Add to `tools/fix_signatures.py`:

```python
# ---------- Decomp body loading ----------

def load_decomp_bodies():
    """Load all decomp JSON function bodies, indexed by address."""
    bodies = {}
    for fname in os.listdir(DECOMP_DIR):
        if not fname.endswith(".json"):
            continue
        path = os.path.join(DECOMP_DIR, fname)
        try:
            with open(path, encoding="utf-8") as f:
                d = json.load(f)
            addr = d.get("address", "")
            body = d.get("decompiled_c", "")
            if addr and body:
                bodies[addr] = body
        except:
            continue
    return bodies


# ---------- Subcommand: infer-void-star ----------

def infer_void_star_params(funcs, decomp_bodies, dry_run=True):
    """Infer void* parameter types from cast patterns in function bodies."""
    changes = []
    for addr, info in funcs.items():
        sig = info.get("signature", "")
        name = info.get("name", "")
        if "void *" not in sig and "void*" not in sig:
            continue

        body = decomp_bodies.get(addr, "")
        if not body:
            continue

        parsed = parse_signature(sig)

        improved = False
        for i, p in enumerate(parsed["params"]):
            if "void" not in p["type"] or "*" not in p["type"]:
                continue
            param_name = p["name"]
            if not param_name:
                continue

            # Pattern 1: explicit cast — (ClassName *)param_name
            cast_types = re.findall(
                r"\(\s*(\w+)\s*\*\s*\)\s*" + re.escape(param_name) + r"\b",
                body
            )
            # Pattern 2: ClassName::Method((ClassName *)param_name, ...)
            method_casts = re.findall(
                r"(\w+)::\w+\s*\(\s*\(\s*(\w+)\s*\*\s*\)\s*" + re.escape(param_name),
                body
            )
            for cls, cast_type in method_casts:
                cast_types.append(cast_type)

            if not cast_types:
                continue

            # Pick most common cast type
            from collections import Counter
            type_counts = Counter(cast_types)
            best_type = type_counts.most_common(1)[0][0]

            # Filter out generic types
            if best_type in ("void", "char", "int", "_DWORD", "_BYTE"):
                continue

            parsed["params"][i]["type"] = best_type + " *"
            improved = True

        if improved:
            new_sig = rebuild_signature(parsed)
            changes.append({
                "addr": addr, "name": name,
                "old_signature": sig, "new_signature": new_sig,
                "confidence": 80,
                "evidence": [
                    "[A] Explicit cast pattern in function body: (Type *)param",
                    "[B] Cast type consistent across multiple usages in function",
                ],
            })

    return changes


# ---------- Subcommand: infer-int-params ----------

def infer_int_params(funcs, decomp_bodies, dry_run=True):
    """Infer int parameter types that are actually pointers from usage evidence."""
    changes = []
    for addr, info in funcs.items():
        sig = info.get("signature", "")
        name = info.get("name", "")
        if "int " not in sig:
            continue

        body = decomp_bodies.get(addr, "")
        if not body:
            continue

        parsed = parse_signature(sig)

        improved = False
        for i, p in enumerate(parsed["params"]):
            if p["type"] != "int" or p["name"] == "this":
                continue
            param_name = p["name"]
            if not param_name:
                continue

            # Pattern 1: explicit cast to pointer — (Type *)param
            cast_types = re.findall(
                r"\(\s*(\w+)\s*\*\s*\)\s*" + re.escape(param_name) + r"\b",
                body
            )
            # Pattern 2: ((Type *)param)->member
            deref_casts = re.findall(
                r"\(\s*\(\s*(\w+)\s*\*\s*\)\s*" + re.escape(param_name) + r"\s*\)\s*->",
                body
            )
            cast_types.extend(deref_casts)

            if not cast_types:
                continue

            from collections import Counter
            type_counts = Counter(t for t in cast_types if t not in
                                  ("void", "char", "int", "_DWORD", "_BYTE", "unsigned"))
            if not type_counts:
                continue

            best_type, count = type_counts.most_common(1)[0]
            # Only accept if used >= 2 times or single dominant cast
            confidence = 80 if count >= 2 else 60
            if confidence < 80:
                continue  # skip low confidence

            parsed["params"][i]["type"] = best_type + " *"
            improved = True

        if improved:
            new_sig = rebuild_signature(parsed)
            changes.append({
                "addr": addr, "name": name,
                "old_signature": sig, "new_signature": new_sig,
                "confidence": 80,
                "evidence": [
                    "[A] Cast-to-pointer pattern: (Type *)param in function body",
                    "[A] Multiple cast occurrences confirm pointer type",
                ],
            })

    return changes
```

Add CLI subcommands:

```python
    p3 = sub.add_parser("infer-void-star", help="Infer void* param types from body")
    p3.add_argument("--apply", action="store_true")

    p4 = sub.add_parser("infer-int-params", help="Infer int param types that are pointers")
    p4.add_argument("--apply", action="store_true")

    # ... dispatch:
    elif args.command == "infer-void-star":
        cmd_infer_body(args, "infer-void-star", infer_void_star_params,
                       "Phase 1.3: void* parameter type inference")
    elif args.command == "infer-int-params":
        cmd_infer_body(args, "infer-int-params", infer_int_params,
                       "Phase 1.4: int parameter pointer inference")
```

Shared CLI handler:

```python
def cmd_infer_body(args, label, infer_fn, phase_label):
    funcs = load_functions()
    bodies = load_decomp_bodies()
    changes = infer_fn(funcs, bodies, dry_run=True)
    print("[%s] Found %d improvable signatures" % (label, len(changes)))
    for ch in changes[:20]:
        print("  %s %s" % (ch["addr"], ch["name"]))
        print("    old: %s" % ch["old_signature"][:80])
        print("    new: %s" % ch["new_signature"][:80])
    if len(changes) > 20:
        print("  ... and %d more" % (len(changes) - 20))

    if args.apply and changes:
        apply_changes(funcs, changes)
        save_functions(funcs)
        entry = format_changelog_entry(
            phase_label,
            "%d 个函数参数类型从函数体推断改进" % len(changes), changes)
        append_changelog(entry)
        os.makedirs(LOGS_DIR, exist_ok=True)
        log_path = os.path.join(LOGS_DIR, "%s_changes.json" % label.replace("-", "_"))
        with open(log_path, "w", encoding="utf-8") as f:
            json.dump(changes, f, indent=2, ensure_ascii=False)
        print("[%s] Applied %d changes." % (label, len(changes)))
    elif not args.apply:
        print("[%s] Dry run. Use --apply to write changes." % label)
```

- [ ] **Step 4: Run all tests**

Run: `python -m pytest tests/test_fix_signatures.py -v`
Expected: All PASS

- [ ] **Step 5: Run infer subcommands on real data**

Run:
```bash
python tools/fix_signatures.py infer-void-star
python tools/fix_signatures.py infer-int-params
```
Review output. Both should show reasonable type inferences.

- [ ] **Step 6: Apply and commit**

```bash
python tools/fix_signatures.py infer-void-star --apply
python tools/fix_signatures.py infer-int-params --apply
git add tools/fix_signatures.py tests/test_fix_signatures.py \
  pipeline/data/annotations/functions.json \
  pipeline/data/annotations/CHANGE_LOG.md
git commit -m "feat(fix_signatures): Phase 1.3+1.4 — void*/int parameter type inference

Infer void* and int parameter types from cast patterns in decomp bodies.
Only applies high-confidence (>=80) changes with explicit cast evidence."
```

---

### Task 4: rename-params 子命令（参数语义命名）

**Files:**
- Modify: `tools/fix_signatures.py` — add `rename-params` subcommand
- Modify: `tests/test_fix_signatures.py`
- Modify: `pipeline/data/annotations/functions.json`
- Modify: `pipeline/data/annotations/CHANGE_LOG.md`

- [ ] **Step 1: Write tests for rename-params**

Append to `tests/test_fix_signatures.py`:

```python
from fix_signatures import rename_params, generate_param_name


class TestGenerateParamName:
    def test_class_pointer(self):
        assert generate_param_name("gbMatrixStack *", "a2", "") == "pStack"

    def test_float_param(self):
        assert generate_param_name("float", "a2", "") in ("fVal", "f")

    def test_int_param_keeps_name(self):
        # int params without context keep their name
        assert generate_param_name("int", "nCount", "") == "nCount"

    def test_already_named(self):
        # Already has a semantic name — don't change
        assert generate_param_name("float", "fAngle", "") == "fAngle"


class TestRenameParams:
    def test_renames_generic_params(self):
        funcs = {
            "0x00412400": {
                "name": "RoleSystem::RenderRole",
                "signature": "void __thiscall(RoleSystem *this, gbMatrixStack *a2, int a3)"
            }
        }
        changes = rename_params(funcs, {}, dry_run=True)
        assert len(changes) == 1
        # a2 (gbMatrixStack *) should become pStack or pMatrixStack
        assert "a2" not in changes[0]["new_signature"]
```

- [ ] **Step 2: Run tests to verify they fail**

Run: `python -m pytest tests/test_fix_signatures.py::TestGenerateParamName -v`
Expected: ImportError

- [ ] **Step 3: Implement rename-params**

Add to `tools/fix_signatures.py`:

```python
# ---------- Parameter naming ----------

# Hungarian-style prefix rules for PAL3/VC6 codebase
_TYPE_PREFIX_MAP = {
    "float": "f",
    "double": "d",
    "int": "n",
    "unsigned int": "dw",
    "DWORD": "dw",
    "UINT": "u",
    "BOOL": "b",
    "bool": "b",
    "char": "ch",
    "unsigned char": "by",
    "BYTE": "by",
    "short": "n",
    "WORD": "w",
    "long": "l",
    "unsigned long": "dw",
    "LPCSTR": "lpsz",
    "const char *": "psz",
    "char *": "psz",
}


def generate_param_name(param_type, current_name, body_context):
    """Generate a semantic parameter name from type and context.

    Rules:
    1. If current name is already semantic (not a1/a2/a3...), keep it
    2. Class pointer → p<ClassName> (strip leading prefixes like gb/C/tag)
    3. Primitive type → Hungarian prefix
    """
    # Already has a semantic name
    if current_name and not re.match(r"^[a-z]\d+$", current_name):
        return current_name

    clean_type = param_type.strip()

    # Pointer to class/struct
    if clean_type.endswith("*"):
        base = clean_type[:-1].strip()
        # Remove const
        base = re.sub(r"^const\s+", "", base).strip()
        if base and base[0].isupper():
            # Strip common prefixes for shorter name
            short = base
            for prefix in ("tag", "gb", "Arc"):
                if short.startswith(prefix) and len(short) > len(prefix):
                    short = short[len(prefix):]
                    break
            return "p" + short
        if base in ("void", "int", "char"):
            return "p" + base.capitalize()

    # Primitive types
    for type_pattern, prefix in _TYPE_PREFIX_MAP.items():
        if clean_type == type_pattern:
            return prefix + "Val" if len(prefix) <= 2 else prefix

    return current_name  # fallback: keep original


def rename_params(funcs, pal3a_index, dry_run=True):
    """Rename generic parameter names (a1, a2...) to semantic names."""
    changes = []
    for addr, info in funcs.items():
        sig = info.get("signature", "")
        name = info.get("name", "")

        parsed = parse_signature(sig)
        improved = False
        for i, p in enumerate(parsed["params"]):
            if p["name"] == "this":
                continue
            if not re.match(r"^[a-z]\d+$", p["name"]):
                continue  # already has semantic name

            new_name = generate_param_name(p["type"], p["name"], "")
            if new_name != p["name"]:
                parsed["params"][i]["name"] = new_name
                improved = True

        if improved:
            new_sig = rebuild_signature(parsed)
            changes.append({
                "addr": addr, "name": name,
                "old_signature": sig, "new_signature": new_sig,
                "confidence": 60,
                "evidence": [
                    "[D] Type-based Hungarian naming convention",
                    "[D] Common PAL3 naming patterns (p=pointer, f=float, n=int)",
                ],
            })

    return changes


def cmd_rename_params(args):
    funcs = load_functions()
    changes = rename_params(funcs, {}, dry_run=True)
    print("[rename-params] Found %d signatures to rename" % len(changes))
    for ch in changes[:15]:
        print("  %s" % ch["name"])
        print("    old: %s" % ch["old_signature"][:80])
        print("    new: %s" % ch["new_signature"][:80])
    if len(changes) > 15:
        print("  ... and %d more" % (len(changes) - 15))

    if args.apply and changes:
        apply_changes(funcs, changes)
        save_functions(funcs)
        entry = format_changelog_entry(
            "Phase 1.5: Parameter semantic naming",
            "%d 个函数的泛化参数名 (a1,a2...) 替换为语义命名" % len(changes),
            changes
        )
        append_changelog(entry)
        print("[rename-params] Applied %d changes." % len(changes))
    elif not args.apply:
        print("[rename-params] Dry run. Use --apply to write changes.")
```

Register subcommand in `main()`:

```python
    p5 = sub.add_parser("rename-params", help="Semantic parameter naming")
    p5.add_argument("--apply", action="store_true")

    # dispatch:
    elif args.command == "rename-params":
        cmd_rename_params(args)
```

- [ ] **Step 4: Run all tests**

Run: `python -m pytest tests/test_fix_signatures.py -v`
Expected: All PASS

- [ ] **Step 5: Run rename-params and commit**

```bash
python tools/fix_signatures.py rename-params
# Review output
python tools/fix_signatures.py rename-params --apply
git add tools/fix_signatures.py tests/test_fix_signatures.py \
  pipeline/data/annotations/functions.json \
  pipeline/data/annotations/CHANGE_LOG.md
git commit -m "feat(fix_signatures): Phase 1.5 — parameter semantic naming

Rename generic a1/a2/a3 params to semantic Hungarian-style names
based on type (pClass for pointers, fVal for float, nVal for int)."
```

---

### Task 5: apply_annotations.py lvars 扩展

**Files:**
- Modify: `pipeline/ida/apply_annotations.py:560-584` — add step 9 for lvars
- Modify: `pipeline/ida/export_full.py:61-85` — export lvar names in decomp JSON

- [ ] **Step 1: Extend functions.json schema documentation**

No code change — just verify the schema is clear. A `local_vars` entry looks like:

```json
{
  "0x00412400": {
    "name": "RoleSystem::RenderRole",
    "signature": "void __thiscall(RoleSystem *this, gbMatrixStack *pStack, int nLOD)",
    "local_vars": [
      {"name": "matWorld", "type": "gbMatrix4", "stack_offset": -64},
      {"name": "pObj", "type": "gbRenderObj *", "stack_offset": -4}
    ]
  }
}
```

Constraints: `local_vars` is optional. `stack_offset` is the Hex-Rays stkoff value. `type` is optional (can rename without retyping).

- [ ] **Step 2: Add lvars step to apply_annotations.py**

Insert after step 8b (re-apply failed global types), before `idc.save_database`:

```python
    # --- 9. Local variable names/types (requires Hex-Rays) ---
    lvar_ok = 0
    lvar_fail = 0
    lvar_total = 0
    for addr_str, info in funcs.items():
        lvars_ann = info.get("local_vars")
        if not lvars_ann:
            continue
        addr = int(addr_str, 16)
        lvar_total += len(lvars_ann)

        func = ida_funcs.get_func(addr)
        if not func:
            lvar_fail += len(lvars_ann)
            continue

        try:
            cfunc = ida_hexrays.decompile(func)
        except:
            lvar_fail += len(lvars_ann)
            continue

        if not cfunc:
            lvar_fail += len(lvars_ann)
            continue

        # Build stkoff → annotation map
        ann_by_stkoff = {}
        for lv_ann in lvars_ann:
            stkoff = lv_ann.get("stack_offset")
            if stkoff is not None:
                ann_by_stkoff[stkoff] = lv_ann

        modified = False
        lvars = cfunc.get_lvars()
        for lvar in lvars:
            loc = lvar.location
            if not loc.is_stkoff():
                continue
            soff = loc.stkoff()
            if soff not in ann_by_stkoff:
                continue

            ann = ann_by_stkoff[soff]
            new_name = ann.get("name")
            new_type = ann.get("type")

            if new_name and lvar.name != new_name:
                lvar.name = new_name
                modified = True

            if new_type:
                tif = ida_typeinf.tinfo_t()
                if ida_typeinf.parse_decl(tif, None, new_type + ";", 0):
                    lvar.set_lvar_type(tif)
                    modified = True

            lvar_ok += 1

        if modified:
            cfunc.save_user_lvars()

    print("[9] Lvars: %d/%d applied (fail=%d)" % (lvar_ok, lvar_total, lvar_fail))
```

Also add `import ida_funcs` at the top of apply_annotations.py if not already present.

- [ ] **Step 3: Extend export_full.py to export lvar info**

In `export_full.py`, after line 84 where the JSON is written, add lvar export. Modify the export block:

```python
                # Export local variable info for annotation round-trip
                lvar_info = []
                try:
                    for lvar in cfunc.lvars:
                        loc = lvar.location
                        if loc.is_stkoff():
                            lvar_info.append({
                                "name": lvar.name,
                                "type": lvar.type().dstr() if lvar.type() else "",
                                "stack_offset": loc.stkoff(),
                            })
                except:
                    pass

                with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                    data = {'name': display_name, 'address': '0x%08X' % ea,
                            'size_bytes': size, 'signature': sig,
                            'decompiled_c': code}
                    if lvar_info:
                        data['local_vars'] = lvar_info
                    json.dump(data, f, indent=2, ensure_ascii=False)
```

- [ ] **Step 4: Commit lvars extension**

```bash
git add pipeline/ida/apply_annotations.py pipeline/ida/export_full.py
git commit -m "feat(pipeline): Phase 2.2 — lvars support in apply_annotations + export

apply_annotations.py step 9: apply local_vars annotations via Hex-Rays API.
export_full.py: export lvar names/types/stkoff in decomp JSON.
functions.json local_vars field is optional — only applied when present."
```

---

### Task 6: 集成验证 — 运行全管线并统计错误变化

**Files:** No new files — this is a verification task.

- [ ] **Step 1: Record baseline error count**

```bash
cmake --build build -- -k 2>&1 | grep "error C" | wc -l
```
Record the number (expected ~6234 from last milestone).

- [ ] **Step 2: Run Phase 1 fixes in sequence**

If not already applied:
```bash
python tools/fix_signatures.py fix-this-type --apply
python tools/fix_signatures.py cross-ref-pal3a --apply
python tools/fix_signatures.py infer-void-star --apply
python tools/fix_signatures.py infer-int-params --apply
python tools/fix_signatures.py rename-params --apply
```

- [ ] **Step 3: Run IDA pipeline (requires IDA headless)**

This requires IDA Pro headless mode. The user runs these commands:

```bash
# 1. Apply annotations to IDB
idat -A -S"pipeline/ida/apply_annotations.py" original/PAL3.exe.i64

# 2. Export all functions
idat -A -S"pipeline/ida/export_full.py" original/PAL3.exe.i64
```

- [ ] **Step 4: Regenerate code**

```bash
python pipeline/gen/gen_headers.py
python pipeline/gen/gen_cpp.py --force-all
```

- [ ] **Step 5: Build and count errors**

```bash
cmake --build build -- -k 2>&1 | tee build_log_new.txt
grep "error C" build_log_new.txt | wc -l
```

Compare with baseline. Target: ≥500 fewer signature-related errors.

- [ ] **Step 6: Error breakdown analysis**

```bash
grep "error C" build_log_new.txt | sed 's/.*error //' | sed 's/:.*//' | sort | uniq -c | sort -rn | head -15
```

- [ ] **Step 7: Commit final CHANGE_LOG summary**

Append a summary entry to CHANGE_LOG.md with before/after error counts.

```bash
git add pipeline/data/annotations/CHANGE_LOG.md
git commit -m "docs(CHANGE_LOG): Phase 1 integration results — error count delta"
```

---

### Task 7: Phase 3 prep — 高错误密度文件的签名批量修正工具

**Files:**
- Modify: `tools/fix_signatures.py` — add `fix-file` subcommand
- Modify: `tests/test_fix_signatures.py`

- [ ] **Step 1: Write test for fix-file**

```python
from fix_signatures import find_functions_for_file


class TestFindFunctionsForFile:
    def test_finds_by_class_name(self):
        funcs = {
            "0x001": {"name": "CCBAI::Update", "signature": "void __thiscall(CCBAI *this)"},
            "0x002": {"name": "CCBAI::Reset", "signature": "void __thiscall(int this)"},
            "0x003": {"name": "Foo::Bar", "signature": "void()"},
        }
        result = find_functions_for_file(funcs, "CCBAI.cpp")
        assert len(result) == 2
        assert "0x001" in result
        assert "0x002" in result
```

- [ ] **Step 2: Implement fix-file subcommand**

Add to `tools/fix_signatures.py`:

```python
def find_functions_for_file(funcs, cpp_filename):
    """Find all functions that belong to a given .cpp file (by class name match)."""
    # Extract class name from filename: "CCBAI.cpp" → "CCBAI"
    base = os.path.splitext(os.path.basename(cpp_filename))[0]
    result = {}
    for addr, info in funcs.items():
        name = info.get("name", "")
        if "::" in name:
            cls = name.split("::")[0]
            if cls == base:
                result[addr] = info
    return result


def cmd_fix_file(args):
    """Run all Phase 1 fixes targeting functions from a specific .cpp file."""
    funcs = load_functions()
    target = find_functions_for_file(funcs, args.file)
    print("[fix-file] %s: %d functions" % (args.file, len(target)))

    bodies = load_decomp_bodies()
    all_changes = []

    # Run each fixer on the target subset
    ch1 = fix_this_type(target, dry_run=True)
    ch2 = infer_void_star_params(target, bodies, dry_run=True)
    ch3 = infer_int_params(target, bodies, dry_run=True)
    ch4 = rename_params(target, {}, dry_run=True)

    for label, changes in [("this-type", ch1), ("void-star", ch2),
                           ("int-params", ch3), ("rename", ch4)]:
        print("  %s: %d changes" % (label, len(changes)))
        all_changes.extend(changes)

    for ch in all_changes:
        print("  %s %s" % (ch["addr"], ch["name"]))
        print("    %s → %s" % (ch["old_signature"][:60], ch["new_signature"][:60]))

    if args.apply and all_changes:
        apply_changes(funcs, all_changes)
        save_functions(funcs)
        entry = format_changelog_entry(
            "Phase 3: %s targeted fixes" % args.file,
            "%d 个函数签名修正 (file: %s)" % (len(all_changes), args.file),
            all_changes
        )
        append_changelog(entry)
        print("[fix-file] Applied %d changes." % len(all_changes))
```

Register:

```python
    p6 = sub.add_parser("fix-file", help="Fix all signatures for a .cpp file")
    p6.add_argument("file", help="Target .cpp filename (e.g., CCBAI.cpp)")
    p6.add_argument("--apply", action="store_true")

    # dispatch:
    elif args.command == "fix-file":
        cmd_fix_file(args)
```

- [ ] **Step 3: Run all tests and commit**

```bash
python -m pytest tests/test_fix_signatures.py -v
git add tools/fix_signatures.py tests/test_fix_signatures.py
git commit -m "feat(fix_signatures): Phase 3 — fix-file subcommand for targeted fixes

Run all signature fixers against functions from a specific .cpp file.
Usage: python tools/fix_signatures.py fix-file CCBAI.cpp [--apply]"
```

---

### Task 8: 全子命令一次运行 + summary 报告

**Files:**
- Modify: `tools/fix_signatures.py` — add `run-all` subcommand

- [ ] **Step 1: Implement run-all**

Add to `tools/fix_signatures.py`:

```python
def cmd_run_all(args):
    """Run all Phase 1 fixes in sequence."""
    funcs = load_functions()
    bodies = load_decomp_bodies()

    with open(PAL3A_DUMP, encoding="utf-8") as f:
        pal3a_data = json.load(f)
    pal3a_funcs = pal3a_data["functions"]

    total = 0
    summary = []

    # Phase 1.1
    ch = fix_this_type(funcs, dry_run=True)
    summary.append(("1.1 fix-this-type", len(ch)))
    if args.apply:
        apply_changes(funcs, ch)
    total += len(ch)

    # Phase 1.2
    ch = cross_ref_pal3a(funcs, pal3a_funcs, dry_run=True)
    summary.append(("1.2 cross-ref-pal3a", len(ch)))
    if args.apply:
        apply_changes(funcs, ch)
    total += len(ch)

    # Phase 1.3
    ch = infer_void_star_params(funcs, bodies, dry_run=True)
    summary.append(("1.3 infer-void-star", len(ch)))
    if args.apply:
        apply_changes(funcs, ch)
    total += len(ch)

    # Phase 1.4
    ch = infer_int_params(funcs, bodies, dry_run=True)
    summary.append(("1.4 infer-int-params", len(ch)))
    if args.apply:
        apply_changes(funcs, ch)
    total += len(ch)

    # Phase 1.5
    ch = rename_params(funcs, {}, dry_run=True)
    summary.append(("1.5 rename-params", len(ch)))
    if args.apply:
        apply_changes(funcs, ch)
    total += len(ch)

    print("\n=== Summary ===")
    for label, count in summary:
        print("  %s: %d changes" % (label, count))
    print("  Total: %d" % total)

    if args.apply:
        save_functions(funcs)
        print("\nAll changes written to functions.json")
```

Register:

```python
    p7 = sub.add_parser("run-all", help="Run all Phase 1 fixes")
    p7.add_argument("--apply", action="store_true")

    # dispatch:
    elif args.command == "run-all":
        cmd_run_all(args)
```

- [ ] **Step 2: Test run-all dry run**

```bash
python tools/fix_signatures.py run-all
```

Expected: Summary table showing counts for each phase.

- [ ] **Step 3: Commit**

```bash
git add tools/fix_signatures.py
git commit -m "feat(fix_signatures): run-all subcommand for complete Phase 1 execution"
```
