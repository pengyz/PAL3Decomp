# 函数签名修正 + 语义化命名 + 变量类型改进

## 目标

批量修正 `functions.json` 中的函数签名（参数类型/参数名），补全 `globals.json` 中的全局变量类型/名称，扩展管线支持局部变量（lvars）标注。所有修改写入 CHANGE_LOG 置信度日志。

## 当前状态

| 指标 | 数值 |
|------|------|
| 总函数 | 3970 |
| 泛化参数名 (a1,a2...) | 1285 (32%) |
| int 代替指针 | 833 (21%) |
| void* 参数 | 121 (3%) |
| int this (应为类指针) | 54 (1.4%) |
| 全局变量 | 426 (全部已命名+有类型) |
| PAL3A 类级匹配 | 71 个共同类，169 个方法级匹配 |
| 编译错误 (全量) | ~6234，其中 C2228/C2227/C2664/C2440 约 3144 与签名相关 |

## 数据流

```
functions.json (signature 字段)
    → apply_annotations.py (IDA SetType)
        → IDA 内部类型系统
            → export_full.py (Hex-Rays 反编译)
                → decomp/*.json (decompiled_c)
                    → gen_cpp.py → src/pal3/**/*.cpp
```

修正 `functions.json` 的 signature 后，需要完整管线重跑才能看到效果。

## Phase 1：高置信度自动修正

### 1.1 int this → ClassName *this（54 个）

**策略**: 扫描 functions.json，对所有 `__thiscall` 函数中 `int this` 的签名，自动替换为 `ClassName *this`。

**置信度**: 95 — `__thiscall` 的第一个参数必然是类指针，这是编译器约定。

**实现**: 新建 `tools/fix_signatures.py`，子命令 `fix-this-type`。

### 1.2 PAL3A mangled name 类型提取（~169 个）

**策略**: PAL3A 的 MSVC mangled name 编码了参数类型。解码后提取参数类型列表，与 PAL3 同名函数的签名做比对。

**约束**: PAL3A 和 PAL3 可能不完全一致（确认过 RoleSystem 有 0x244 偏移差异），所以：
- 参数**类型**可以参考（同一方法大概率参数类型一致）
- 参数**名称**可以参考
- 参数**个数**必须匹配才采用
- 置信度标为 70（C 级：PAL3A 类比推断），需逐个验证

**实现**: `fix_signatures.py` 子命令 `cross-ref-pal3a`。需要 MSVC name demangler（纯 Python 实现或调用 `undname.exe`）。

### 1.3 void* 参数自动推断（~121 个）

**策略**: 在 decomp JSON 的函数体中搜索对 `void *` 参数的实际使用：
- `(ClassName *)param` cast → 参数类型应为 `ClassName *`
- `param->member` 访问 → 通过 member 推断类型
- `FuncTakingType(param)` 调用 → 从被调函数签名推断

**置信度**: 80（当有明确 cast 时），60（仅通过 member 推断时）

**实现**: `fix_signatures.py` 子命令 `infer-void-star`。

### 1.4 int 参数类型推断（~833 个）

**策略**: 在函数体中搜索 `int` 参数被当指针用的证据：
- `*(Type *)a2` → a2 是 `Type *`
- `a2->member` → a2 是指针（需推断哪个类）
- `(Type *)a2` 后调用方法 → a2 是 `Type *`

**约束**: 很多 `int` 参数确实就是 int（index, count, flags），只修正有明确指针使用证据的。

**置信度**: 80（有明确 cast + 使用），50（仅单次使用推断）→ 只提交 ≥80 的。

**实现**: `fix_signatures.py` 子命令 `infer-int-params`。

### 1.5 参数语义命名

**策略**: 
- PAL3A 同名函数的参数名作为首选（如果参数个数匹配）
- 常见模式自动命名：`ClassName *` → `p<Class>`，`float` → `f<Context>`
- 函数体中的使用语境推断：`a2` 被传入 `SetPosition(a2)` → `pPos`

**置信度**: 60（语义推断），70（PAL3A 参考）

**输出**: 仅更新 signature 中的参数名，不影响类型。

## Phase 2：管线扩展

### 2.1 functions.json 新增 local_vars 字段

**Schema 扩展**:
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

`local_vars` 字段可选。只在有确切类型/名称信息时填入。

### 2.2 apply_annotations.py 新增 lvars 支持

**IDA API**: `ida_hexrays.rename_lvar()` + `ida_hexrays.set_lvar_type()`

**实现**:
```python
# 在 apply_annotations.py 中新增 step 7
# --- 7. Local variable names/types ---
cfunc = ida_hexrays.decompile(func)
for lvar in cfunc.lvars:
    if lvar.location.stkoff() == target_stack_offset:
        lvar.name = new_name
        lvar.set_lvar_type(new_type_tinfo)
cfunc.save_user_lvars()
```

**约束**: 
- 只在函数成功反编译时才能应用
- stack_offset 是 Hex-Rays 内部的，可能随类型变化而变化
- 需要容错：如果 lvar 找不到就跳过

### 2.3 globals.json 类型补全

当前 426 个全局变量已全部命名且有类型。Phase 2 中主要是验证和修正现有类型的精度：
- `void *` 类型的 vtable 指针 → 改为具体的函数指针数组类型
- 数组长度确认（通过 binary stride 分析）

## Phase 3：IDA 辅助深度修正

### 3.1 高错误密度文件优先修正

按错误数排序的 Top 15 文件作为目标：

| 文件 | C2228 | C2664 | 总错误 |
|------|-------|-------|--------|
| CCBAI.cpp | ~96 | ~20 | ~120 |
| CameraCtrl.cpp | ~42 | ~15 | ~60 |
| CCCTData.cpp | ~41 | ~10 | ~55 |
| EquipUI.cpp | ~39 | ~12 | ~55 |
| Object3D.cpp | ~38 | ~8 | ~50 |

### 3.2 验证工具链

使用 raw IDB (`PAL3.exe.raw.i64`) + `_raw_query_flex.py` 快速验证偏移：
1. 将待验证的地址写入 `_logs/raw_query_input.json`
2. 用 `idat -A -S"_raw_query_flex.py" original/PAL3.exe.raw.i64` 执行
3. 从 `_logs/raw_query_output.json` 读取原始反编译结果
4. 对比原始偏移与标注后的类型是否一致

### 3.3 CHANGE_LOG 格式

每批修正都写入 `pipeline/data/annotations/CHANGE_LOG.md`：

```markdown
## [2026-05-XX] Phase 1.1: int this → ClassName *this (54 函数)

- **变更**: 54 个 __thiscall 函数的 this 参数从 int 修正为 ClassName *
- **置信度**: 95
- **证据**:
  1. [A] __thiscall 调用约定要求 ECX=this，参数类型必为类指针
  2. [B] 逐个验证: 函数名包含 ClassName:: 前缀，与 this 类型一致
- **影响**: 消除约 54 个 C2228/C2227 编译错误
- **函数列表**: [附在 _logs/phase1_1_changes.json]
```

## 工具清单

| 工具 | 用途 | 新建/修改 |
|------|------|----------|
| `tools/fix_signatures.py` | 签名修正主工具（多子命令） | 新建 |
| `pipeline/ida/apply_annotations.py` | 新增 lvars 支持 | 修改 |
| `pipeline/data/annotations/functions.json` | 签名更新 | 修改 |
| `pipeline/data/annotations/globals.json` | 类型补全 | 修改 |
| `pipeline/data/annotations/CHANGE_LOG.md` | 置信度日志 | 修改 |

## 验证流程

每个 Phase 完成后：
1. 运行 `tools/fix_signatures.py --dry-run` 查看变更预览
2. 确认后写入 functions.json + CHANGE_LOG
3. 在 IDA 中跑 `apply_annotations.py` → `export_full.py`
4. 跑 `gen_headers.py` + `gen_cpp.py --force-all`
5. `cmake --build build -- -k` 统计错误数变化
6. 对比前后错误数，确认无回归

## 成功标准

- Phase 1: 签名相关编译错误（C2228+C2227+C2664+C2440）减少 ≥500
- Phase 2: lvars 管线可用，至少 10 个函数完成局部变量标注
- Phase 3: Top 5 错误密度文件各减少 ≥50% 错误
- 所有修改有 CHANGE_LOG 置信度记录
