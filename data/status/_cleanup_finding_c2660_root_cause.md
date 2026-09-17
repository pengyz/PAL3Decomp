# C2660 系统性根因**完整定位** + 归一化尝试的结果（含回退）

> 用户要求：扫出影响面、统一归一化到一点、完成方案后做独立复核。

## 1. 影响面（扫完）

```
C2660（`'X' : function does not take N parameters`，**全部是「过多」参数**）
  632 条 / **101 个文件**（= 71% 的失败文件）
  N 分布: 0:93 · 1:183 · 2:193 · 3:114 · 4:20 · 5:12 · 6:7 · 7:1 · 9:10 · 10:1
```

## 2. 根因：**唯一一点** —— `ast_transform.py:587-693` 的"归属门禁"分支

```python
if first_arg.type == 'cast_expression':
    if inner == 'this':
        if class_name == cls_name or <是基类>:        # 同类/基类 ⇒ 变换
        else:
            if class_name in _rowtable_family():      # gbUI 族 ⇒ 变换
            else:                                     # ← **C2660 全部出自这里**
                _t1_retn = (_ret_param_slots(...) == len(arg_nodes)-1)   # 渲染实参数==栈参数数
                _t1_vt   = _occupies_vtable_slot(...)                    # 占 vtable 槽
                if _t1_retn and _t1_vt and not ctor/dtor:  变换
                else:  只加 `[MISATTRIBUTED]` 注释、**保持静态调用形式** ⇒ 不编译（C2352/C2660）
```

**⇒ 不是"codegen bug"，而是【刻意设计】的诚实门禁**：
它认为 `X::M((X*)this)` 出现在**别的类**里 ⇒ **IDB 归属不可能对** ⇒
**拒绝"洗白成合法语法"**，故意留成编译错误作为"去修 IDB 归属"的信号（注释明写此意）。

## 3. ✅ A 级证据：对象**确实**是调用者的 this

```
CCBAttackSequen.cpp:172  CCBSystem::CalcSpeed((CCBSystem *)this, v2, 0);
0x004DB640 (CalcSpeed) 反汇编:
  4db644: mov 0x8(%ecx),%ecx      ← 读 %ecx = this（确为 __thiscall）
  4db653: ret $0x8               ← 被调者清 8 字节 = **2 个栈参数**（与声明一致）
调用点 4db667-4db672:
  4db667: mov %ecx,%esi          ← 调用者的 this
  4db669: push $0x0 / 4db66e: push %edi
  4db672: call 0x4db640          ← %ecx 此刻 = %esi = **调用者 CCBAttackSequen 的 this**
⇒ **对象就是调用者的 this**（不是 CCBSystem 实例）
⇒ `CCBSystem::CalcSpeed` 的归属**不可信**；门禁的"怀疑"是**对的**
```

**⇒ 632 条 C2660 的本质 = 632 处"疑似归属错误"的显式标记。**

## 4.  归一化尝试（已实施、测量、**回退**）

**改法**：当 `_t1_retn` 成立时，用**调用者自己的类**生成合法且忠实的调用：
```python
new_text = '((%s *)this)->%s::%s(%s)' % (cls_name, cls_name, method_name, rest_str)
# CCBSystem::CalcSpeed((CCBSystem*)this, v2, 0) → ((CCBAttackSequen*)this)->CCBAttackSequen::CalcSpeed(v2, 0)
```

**实测（完整管线）**：
| 指标 | 改前 | 改后 |
|---|---|---|
| census `ok` | 56/202 | **56/202（无改善）** |
| **C2660** | 632 | **417（−215）** |
| **C2039** | 1075 | **1469（+394）** |
| `matched` | 170 | 170 |
| **`L1`** | **16** | **16（无回退）** |

**⇒ 结论：这是「错误换错误」**——把 `C2352/C2660` 换成了
`C2039 'CalcSpeed' : is not a member of 'CCBAttackSequen'`（实测确认），**`ok` 无改善**，
且**引入了未取证的断言**（"对象是调用者类型"）。

**⇒ 按纪律回退**（`ok` 无改善 + 新增错误类）。补丁保全：
`data/status/_cleanup_patch_oop_normalize_attempt.py`（可原样复用）。

## 5. ⇒ 最终判定：**C2660 不是 codegen 能修的**

```
要让它合法，必须让 `CCBAttackSequen::CalcSpeed` **存在**
  ⇒ 那是 **annotation 工作**（把 `CalcSpeed` 归给 `CCBAttackSequen`）
  ⇒ 且需 **A 级证据**（我目前只有"对象是调用者 this"这一条间接证据，
     尚无"该函数读写的成员属于 CCBAttackSequen"的直接证据：
     CCBSystem+0x8=m_pControl、CCBAttackSequen+0x8=m_pRole，需看 `0x8(%ecx)` 传给谁后被如何使用）
```

**⇒ 与 F2/归属 是同一个瓶颈**（本会话第 4 次撞上）：**归属注解不完整**。

## 6. 顺带发现（供复核）

| # | 发现 | 状态 |
|---|---|---|
| 1 | **2 个既有 unittest 失败**（`test_identifier_as_first_arg` / `test_complex_expr_as_first_arg`）——产物多一层括号 `(((Foo *)ptr))` vs 期望 `((Foo *)ptr)` | **先前就存在**，与本次无关 |
| 2 | `pal3_vtbl_unk_0` 的**签名损坏**：`cannot convert parameter 1 from 'void *' to 'unsigned long'` | **未查明**；927 个 stub 可能普遍如此 |
| 3 | `transform_oop_calls` 的首参分支共 **4 条出路**（同类/基类、rowtable 族、Track-1 例外、MISATTRIBUTED），**其中只有 MISATTRIBUTED 那条产出不合法代码** | 已定位 |
