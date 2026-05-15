# Pipeline Refactor Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 精简 gen_cpp 删除 workaround 规则，嵌入 Hex-Rays microcode optimizer 到 export_full.py，提升管线可维护性。

**Architecture:** 三阶段执行：(1) gen_cpp 删除 6 条 Category B workaround 规则，(2) export_full.py 嵌入 Phase 1 microcode optimizer（vtable init NOP），(3) 验证整体管线。microcode optimizer 使用 `optinsn_t.install()` 全局安装，在 export 循环前后 install/remove。

**Tech Stack:** Python, IDA Pro 9.1 ida_hexrays API (optinsn_t, minsn_t, mop_t), tree-sitter-cpp

---

### Task 1: gen_cpp 删除 Category B workaround 规则

**Files:**
- Modify: `pipeline/gen/gen_cpp.py`

- [ ] **Step 1: 删除 B1 — stdiobuf→UIWnd 替换 (L351-356)**

删除以下代码块：

```python
    # 6b. Fix IDA type misidentification: stdiobuf/ios_base -> UIWnd in game code
    code = code.replace('stdiobuf *', 'UIWnd *')
    code = code.replace('stdiobuf::', 'UIWnd::')
    code = code.replace('(stdiobuf *)', '(UIWnd *)')
    code = code.replace('std::ios_base *', 'UIWnd *')
    code = code.replace('(std::ios_base *)', '(UIWnd *)')
```

- [ ] **Step 2: 删除 B2 — *(this+N) cast (L367-369)**

删除以下代码块：

```python
    # 6. Fix *(this + N) -> *((_DWORD *)this + N) for pointer arithmetic on typed this
    code = re.sub(r'\*\(\s*this\s*\+\s*(\d+)\s*\)', r'*((_DWORD *)this + \1)', code)
    code = re.sub(r'\*\(\s*this\s*-\s*(\d+)\s*\)', r'*((_DWORD *)this - \1)', code)
```

- [ ] **Step 3: 删除 B3 — int this→int _this 重命名 (L371-377)**

删除以下代码块：

```python
    # 6c. If 'this' appears as a non-pointer parameter (e.g. "int this"), rename to _this
    # This handles cases where IDA named a parameter 'this' but it's not a real C++ this
    code = re.sub(r'\bint\s+this\b', 'int _this', code)
    code = re.sub(r'\bchar\s+this\b', 'char _this', code)
    code = re.sub(r'\b_DWORD\s+this\b', '_DWORD _this', code)
    # Also: &this[N] -> &((_DWORD *)this)[N]  and  this[N] -> ((_DWORD *)this)[N]
    # But be careful not to break this->member access
```

- [ ] **Step 4: 删除 B4 — void* cast 逻辑 (L379-420)**

删除从 `# 7. Fix void* implicit conversion` 到 `code = '\n'.join(new_lines)` 的完整块（约 42 行），包括 `fix_ptr_assign` 函数定义和 `ptr_vars` 追踪逻辑。

- [ ] **Step 5: 删除 B5 — double-deref (L441-443)**

删除以下代码块：

```python
    # Fix IDA double-deref: (*)*(expr) → *(expr) — only in assignment context
    # e.g. "* p = (*)*(_DWORD *)&this->member;" → "* p = *(_DWORD *)&this->member;"
    code = re.sub(r'= \(\*\)\*\(', '= *(', code)
```

- [ ] **Step 6: 删除 B6 — STL 调用注释 (L445-451)**

删除以下代码块：

```python
    # Comment out STL internal calls that VC6 can't compile
    # Pattern: ((std *)&expr)->string::Method(args);
    # Pattern: ((std *)expr)->codecvt_base::Method();
    def _comment_std(m):
        return m.group(1) + '// [IDA_STL] ' + m.group(2)
    code = re.sub(r'(\n[ \t]*)((?:\(\(std \*\)|result = \(\(std \*\)).*?;)', _comment_std, code)
    code = re.sub(r'(\n[ \t]*)(.*?codecvt_base::\w+\(\).*?;)', _comment_std, code)
```

- [ ] **Step 7: 验证 gen_cpp 仍能运行**

```bash
python pipeline/gen/gen_cpp.py --force-all 2>&1 | tail -3
```

Expected: 正常输出文件数量，无 Python 错误。

- [ ] **Step 8: 统计行数减少并 build**

```bash
wc -l pipeline/gen/gen_cpp.py
cmake --build build -- -k 2>&1 | grep -c "error C"
```

Expected: 行数减少 ≥60 行。错误数上升（预期，暴露了被掩盖的问题）。

- [ ] **Step 9: 提交**

```bash
git add pipeline/gen/gen_cpp.py
git commit -m "refactor(gen_cpp): remove 6 Category B workaround rules

Delete stdiobuf→UIWnd, *(this+N) cast, int this rename,
void* cast logic, double-deref, STL comment-out.
These should be fixed in IDA annotations, not codegen."
```

---

### Task 2: Microcode Optimizer Phase 1 — vtable init NOP

**Files:**
- Modify: `pipeline/ida/export_full.py`

- [ ] **Step 1: 在 export_full.py 顶部添加 microcode optimizer 类**

在 `TEXT_END` 常量之后，`log_lines` 之前，添加：

```python
# --- Microcode Optimizer ---
# Installed before decompilation to modify Hex-Rays output at the microcode level.
# Phase 1: NOP vtable pointer initialization (compiler-generated, not in source code)

RDATA_START = 0x0056A000
RDATA_END = 0x0057F178

class PAL3Optimizer(ida_hexrays.optinsn_t):
    def __init__(self):
        ida_hexrays.optinsn_t.__init__(self)
        self.vftable_nops = 0

    def func(self, blk, ins, optflags):
        n = 0
        n += self._nop_vftable_init(blk, ins)
        return n

    def _nop_vftable_init(self, blk, ins):
        """NOP vtable pointer writes: mov [obj+0], &vtable_in_rdata

        Compiler generates these in every ctor/dtor. They're not in the
        original source code — the compiler inserts them automatically.
        Removing them at microcode level means decompiled_c won't contain
        __vftable = &xxx assignments at all.
        """
        if ins.opcode != ida_hexrays.m_stx:
            return 0
        # Check: destination is a memory write (mop_d for stx is the address)
        # For vtable init, the value being stored (ins.l) is a constant address in .rdata
        src = ins.l  # source operand (what's being stored)
        if src.t != ida_hexrays.mop_n:
            return 0
        val = src.nnn.value if hasattr(src, 'nnn') and src.nnn else 0
        if not (RDATA_START <= val <= RDATA_END):
            return 0
        # This is a store of a .rdata address (likely vtable pointer) — NOP it
        if blk:
            blk.make_nop(ins)
        else:
            ins._make_nop()
        self.vftable_nops += 1
        return 1
```

- [ ] **Step 2: 在 main() 中安装和卸载 optimizer**

在 `targets.sort()` 之后、`exported = 0` 之前，添加 optimizer install：

```python
        # Install microcode optimizer before decompilation
        opt = PAL3Optimizer()
        opt.install()
        log("[*] Microcode optimizer installed")
```

在 export 循环结束后（`log("[*] Exported: ...")`行之前），添加 remove：

```python
        opt.remove()
        log("[*] Optimizer: %d vftable inits NOPed" % opt.vftable_nops)
```

- [ ] **Step 3: 提交**

```bash
git add pipeline/ida/export_full.py
git commit -m "feat(export_full): Phase 1 microcode optimizer — vtable init NOP

Install optinsn_t before decompilation to NOP vtable pointer
writes (m_stx of .rdata address). These are compiler-generated
and shouldn't appear in decompiled source code."
```

---

### Task 3: 验证 microcode optimizer + 完整管线

**Files:** 无新文件——验证任务。

- [ ] **Step 1: 运行完整管线**

```bash
# Apply annotations
/home/peng/ida-pro-9.1/idat -A -S"pipeline/ida/apply_annotations.py" original/PAL3.exe.i64

# Export with optimizer
/home/peng/ida-pro-9.1/idat -A -S"pipeline/ida/export_full.py" original/PAL3.exe.i64

# Check optimizer log
cat pipeline/ida/_logs/pal3_export_only_log.txt
```

Expected: 日志中出现 `Optimizer: N vftable inits NOPed`，N > 0。

- [ ] **Step 2: 验证 __vftable 减少**

```bash
# Count __vftable in decompiled code
grep -rh "__vftable" asm/pal3/decomp/*.json 2>/dev/null | wc -l
```

Expected: 数量显著减少（如果 optimizer 工作正确）。如果没有减少，说明 Phase 1 的 microcode 模式匹配不正确——需要调试 `m_stx` 的操作数结构。

- [ ] **Step 3: 如果 optimizer 不生效，添加调试日志**

如果 Step 2 中 __vftable 没有减少，在 `_nop_vftable_init` 开头添加临时调试：

```python
    def _nop_vftable_init(self, blk, ins):
        if ins.opcode == ida_hexrays.m_stx:
            # Debug: log all m_stx instructions to understand operand structure
            try:
                self._debug_count = getattr(self, '_debug_count', 0) + 1
                if self._debug_count <= 20:
                    print("[DBG] m_stx: l.t=%d r.t=%d d.t=%d" % (ins.l.t, ins.r.t, ins.d.t))
                    if ins.l.t == ida_hexrays.mop_n:
                        print("[DBG]   l.value=0x%X" % ins.l.nnn.value)
            except:
                pass
        # ... rest of function
```

重新运行 export，检查日志中 `[DBG]` 输出来理解 microcode 结构。根据实际结构调整匹配逻辑。

- [ ] **Step 4: 重新生成代码并 build**

```bash
python pipeline/gen/gen_headers.py 2>&1 | tail -2
python pipeline/gen/gen_cpp.py --force-all 2>&1 | tail -2
cmake --build build -- -k 2>&1 | grep -c "error C"
```

记录错误数。与 Task 1 的结果对比。

- [ ] **Step 5: 写 CHANGE_LOG 并提交**

```bash
cat >> pipeline/data/annotations/CHANGE_LOG.md << 'EOF'

### [2026-05-15] 管线重构：gen_cpp 精简 + Microcode Optimizer Phase 1

- **变更**:
  1. gen_cpp: 删除 6 条 Category B workaround 规则 (stdiobuf/*(this+N)/int this/void* cast/double-deref/STL comment)
  2. export_full.py: 嵌入 Phase 1 microcode optimizer (vtable init NOP via optinsn_t)
- **置信度**: 85
- **证据**:
  1. [A] Category B 规则是 IDA 标注不完整的 workaround，应在 annotations 层修正
  2. [A] optinsn_t.install() 在 decompile() 前全局安装，影响所有后续反编译
  3. [A] cmake --build -- -k 编译验证
- **预期**: 错误数上升（暴露被掩盖的标注问题），但管线更可维护
EOF

git add pipeline/data/annotations/CHANGE_LOG.md
git commit -m "chore(pipeline): CHANGE_LOG for pipeline refactor

Evidence: gen_cpp -60 lines, microcode optimizer Phase 1 installed
Confidence: 85"
```

- [ ] **Step 6: Push**

```bash
git push
```
