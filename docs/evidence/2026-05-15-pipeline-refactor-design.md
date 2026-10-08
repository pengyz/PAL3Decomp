# 管线重构：gen_cpp 精简 + Microcode Optimizer

## 目标

1. 删除 gen_cpp 中的 workaround 规则，暴露 IDA 标注问题的真实错误
2. 在 export_full.py 中嵌入 Hex-Rays microcode optimizer，从反编译器层面修正输出
3. 提升管线可维护性——regex 后处理只保留 Hex-Rays 固有输出的等价变换

## 当前状态

- gen_cpp.py: 911 行, 22 个 transform blocks, 59 个 regex/replace 调用
- ast_transform.py: 128 行, 1 个 AST 函数 (OOP 转换)
- export_full.py: ~130 行, 纯导出无优化
- 编译错误: 5263

## 第一部分：gen_cpp 精简

### 删除的规则 (Category B: workaround)

| ID | 规则 | 行号 | 删除理由 |
|----|------|------|---------|
| B1 | `stdiobuf→UIWnd` 替换 | L352-356 | annotations 修正函数签名 |
| B2 | `*(this+N)→*((_DWORD*)this+N)` | L368-369 | 结构体布局标注不完整 |
| B3 | `int this→int _this` 重命名 | L373-375 | 函数签名错误 |
| B4 | void* cast 逻辑 | L379-420 | 局部变量类型错误（整个 fix_ptr_assign + ptr_vars tracking） |
| B5 | `(*)*( → *(` double-deref | L441-443 | 局部变量类型错误 |
| B6 | STL 调用注释 `((std *)...)` | L445-451 | IDA this 类型推断错误 |

### 保留的规则 (Category A: Hex-Rays 固有输出)

| ID | 规则 | 实现 | 理由 |
|----|------|------|------|
| A1 | OOP 转换 `Class::Method(obj)→obj->Method()` | tree-sitter AST | Hex-Rays 不输出 OOP 调用 |
| A2 | 删除 `__thiscall/__cdecl` | 文本替换 | VC6 函数定义不支持 |
| A3 | 删除 `ClassName *this` 参数 | regex | C++ 方法不需要 |
| A4 | ctor/dtor 返回类型/return | regex | C++ 不允许 |
| A5 | `LL→i64` | regex | GCC→VC6 后缀 |
| A6 | `(*)var→(*var)` | regex | Hex-Rays 输出 bug |
| A7 | `_ThrowInfo→_s__ThrowInfo` | 文本替换 | IDA 类型名差异 |
| A8 | `vtbl_XXXXX→void` | regex | IDA 内部类型 |
| A9 | backtick 编译器调用删除 | 行过滤 | 编译器生成代码 |
| A10 | `__vftable=` 赋值删除 | 行过滤 | 编译器生成代码 |
| A11 | `return &this->__vftable→return this` | regex | Hex-Rays ctor 模式 |
| A12 | `((operator *)0xNN)->new()→operator new(0xNN)` | regex | Hex-Rays new 模式 |
| A13 | `(int)Class::Method` MFP cast | regex+地址提取 | Hex-Rays MFP 模式 |
| A14 | `LODWORD(x) = &symbol` cast | regex | Hex-Rays 宏展开 |
| A15 | 前导下划线类名修正 | 文本替换 | Hex-Rays 输出 bug |
| A16 | thunk/literal/global 名称替换 | 映射表 | 纯名称等价变换 |
| A17 | ctor/dtor 调用删除 | _replace_ida_internals | 编译器生成的 ctor/dtor |

### 预期影响

删除 B1-B6 后错误数会上升（暴露了被 workaround 掩盖的 IDA 标注问题），但代码更真实，后续 annotation 修正的效果更直接。

## 第二部分：Microcode Optimizer

### 架构

嵌入 `export_full.py`。在反编译循环开始前 `install()`，结束后 `remove()`。

```python
# export_full.py 修改
class PAL3Optimizer(ida_hexrays.optinsn_t):
    def __init__(self):
        super().__init__()
        self.changes = 0
    
    def func(self, blk, ins, optflags):
        n = 0
        n += self._fix_vftable_init(blk, ins)
        n += self._fix_ctor_pattern(blk, ins)
        n += self._fix_vcall_pattern(blk, ins)
        self.changes += n
        return n

opt = PAL3Optimizer()
opt.install()
# ... decompile all functions ...
opt.remove()
log("[*] Optimizer: %d changes" % opt.changes)
```

### Phase 1: __vftable 赋值消除

**microcode 模式：** `m_stx` 写入 vtable 指针地址到对象首 DWORD

```python
def _fix_vftable_init(self, blk, ins):
    # Match: stx [obj+0], &vtable_address
    if ins.opcode == m_stx:
        if ins.d.t == mop_a and ins.d.a.off == 0:
            # Check if RHS is a constant address in .rdata vtable range
            if ins.l.t == mop_n and 0x56A000 <= ins.l.nnn.value <= 0x57F000:
                ins.opcode = m_nop  # or make_nop
                return 1
    return 0
```

**验证：** 消除 gen_cpp 中 `_replace_ida_internals` 的 `__vftable = ` 行过滤。如果 microcode 成功 NOP 了 vtable init，decompiled_c 中就不会出现 `__vftable =` 语句。

### Phase 2: 构造函数还原

**microcode 模式：** `m_call operator_new(size)` → 结果存入 `reg` → `m_call ctor(reg, args)`

```python
def _fix_ctor_pattern(self, blk, ins):
    # This is complex: need to match a sequence within the same block
    # 1. Find m_call to operator_new
    # 2. Track where result goes (register/stack)  
    # 3. Find subsequent m_call where first arg == that result
    # 4. Check if called function name matches a known class name (ctor)
    # Implementation deferred to Phase 2
    return 0
```

**注意：** 这需要遍历 basic block 内的指令序列，不是单条指令匹配。可能需要 `optblock_t`（block 级别优化器）而非 `optinsn_t`（指令级别）。

### Phase 3: 虚调用简化

**microcode 模式：** `m_ldx vtable_ptr` → `m_ldx func_ptr_from_vtable` → `m_icall`

这是最复杂的模式。可能需要 IDA 已经标注了 vtable 结构体才能识别。

### 分阶段实施

| Phase | 内容 | 复杂度 | 替代的 gen_cpp 规则 |
|-------|------|--------|-------------------|
| 1 | vtable init NOP | 低 | A10 (`__vftable=` 删除) |
| 2 | ctor 还原 | 高 | A17 (ctor/dtor 调用删除) + C2273 |
| 3 | vcall 简化 | 高 | C2039 __vftable 访问 |

## 第三部分：管线执行顺序

不变：

```
IDB → master_pipeline → import_gbengine → apply_annotations → export_full [+optimizer] → gen_headers → gen_cpp → build
```

export_full.py 的内部流程变为：

```
install optimizer → mark_cfunc_dirty(all) → decompile+export → remove optimizer → export structs
```

## 验证标准

1. gen_cpp 删除 B1-B6 后无功能回归（错误数上升是预期的）
2. Phase 1 microcode optimizer 成功消除 `__vftable =` 语句（验证一个函数即可）
3. gen_cpp 行数减少 ≥60 行（B4 void* cast 逻辑是最大块，约 40 行）
4. 整体管线可一键执行，无中间手动步骤
