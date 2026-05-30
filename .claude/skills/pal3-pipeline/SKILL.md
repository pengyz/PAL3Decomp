---
name: pal3-pipeline
description: "PAL3 标注迭代管线 — IDA 标注→导出→codegen→编译→对比的完整工作流"
tags: [reverse-engineering, pal3, annotations, pipeline]
when_to_use: "当用户需要执行 PAL3 反编译管线流程（标注、导出、codegen、编译、字节对比）时加载"
---

# PAL3 标注迭代管线

<CRITICAL-INSTRUCTION>
当前阶段：**IDA 标注阶段**。源码是生成物，不手动编辑。
唯一目标：提升 `data/annotations/` 数据质量。
所有结构体字段修改必须有 PAL3.exe 二进制直接证据。

**阶段分离**：标注阶段（当前）产出 annotations；codegen 阶段（未来）产出可编译源码。
编译错误是 codegen 适配度指标，不是标注正确性指标。
</CRITICAL-INSTRUCTION>

## 数据架构

```
data/annotations/
  ├── functions.json            — {addr: {name, signature}}
  ├── globals.json              — {addr: {name, type}}
  ├── skip_functions.json       — {addr: {name, reason}}
  ├── vtables.json              — {vtbl_name: {address, class, methods}}
  ├── structs/ClassName.json    — {name, binary_size, known_members: {offset: {name, type, source}}}
  ├── field_overrides.json      — TAUDT_FIXED 绕过 / 嵌入偏移文档（仅注释，不生成代码）
  └── CHANGE_LOG.md             — 变更审计记录
```

### field_overrides.json

IDA 无法通过 TAUDT_FIXED 创建巨型稀疏结构体时，用此文件提供偏移→名称映射。codegen Pattern C 读取后为 `(char*)this+N` 等表达式附加内联注释 `/* fieldName */`。

**约束**：
- 只产生注释，不生成代码访问——不改变 struct binary_size
- stub 类（4B）不能靠此添加成员——`memset(this, 0, sizeof(*this))` 会越界
- 伪语义命名（`m_field_104`）无效——不加比加好

## IDA 9.x API 差异

### 调用注意事项

- IDA 静默运行，stdout/stderr 不显示在终端。脚本内 `print()` 不可见。
- 脚本必须写文件到 `_logs/` 目录才能查看结果
- Python 脚本需要 `import idaapi; idaapi.auto_wait()` 在开头
- 退出用 `idc.qexit(0)`（正常）或 `idc.qexit(1)`（错误）
- 脚本路径有空格时需要在 `-S` 参数中额外加引号：`-S"\"path with spaces\script.py\""`
- `idc.get_type(va)` 可能返回 None（函数未设置签名）
- `idaapi.get_func(va)` 返回 None 时表示地址处没有函数

### API 变更（IDA 7.x → 9.x）

- `get_first_member(sid)` / `get_next_member(sid, m)` → **不存在**，改 `get_member_by_idx(sid, idx)` 遍历
- `get_member_name(m_handle)` → `get_member_name(sid, offset)`（两个参数）
- `get_member_offset(m_handle)` → `get_member_offset(sid, member_name)`
- `get_member_size(m_handle)` → `get_member_size(sid, offset)`
- `ida_struct` 模块不存在
- `idautils.Structs()` 不稳定 → 优先 `get_struc_id` + 已知 name

## 禁止行为

<HARD-REQUIREMENT>
1. 禁止从 Hex-Rays 反编译文本推断偏移——除非 IDB 已 apply_annotations 且结构体正确
2. 禁止批量修改未验证字段——每个偏移/类型变更必须逐一验证
3. 禁止仅凭 PDB 数据修改——PAL3A PDB 偏移可能与 PAL3 不同
4. 禁止提交无 A 级证据的偏移/类型修改
5. 禁止伪语义命名——`m_nState_4968` 没有语义价值，不如 `_todo_`
6. 禁止对 IDA 查询工具输出不加验证直接命名——工具提供候选，人工判断拍板
7. 禁止仅凭 signature this 类型修正函数归属——必须有 decomp member access evidence
8. 禁止用编译错误评判标注质量——codegen 适配问题，不是标注问题
</HARD-REQUIREMENT>

## 置信度规则

| 等级 | 类型 | 分值 | 示例 |
|------|------|------|------|
| A | 二进制指令 reg+disp32 | 85 | `mov byte [esi+0xD1], 1` 且 esi=this |
| A+ | apply 后 Hex-Rays 偏移 | 85 | 结构体正确时 `this+484` |
| B | 3+ 条 A 级交叉确认 | 80+ | 多函数同偏移同访问模式 |
| C | Hex-Rays 文本推断（未 apply） | 50 | 不可单独用于偏移修改 |
| D | 语义推断 | 30 | 从调用上下文猜测 |

**提交阈值**：偏移修改≥80，类型修改≥70，字段命名≥60，结构体 size≥85。

## 关键方法论

### 反编译器伪像识别

审计脚本报告的 `this+N` 超标函数中，约 25% 是反编译器伪像——IDA 生成虚假表达式但二进制实际无 `[esi+disp]` 访问。

**ESI 验证法**：扫描函数内所有 `[esi+disp]` 指令取最大 disp，与审计 max_off 对比：
- ESI max ≈ 审计 max_off → **真实字段访问**
- ESI max << 审计 max_off → **反编译器伪像**（来自指针强制转换）
- ESI max = 0 → **伪像**

处理审计条目时先过 ESI 筛子，伪像直接跳过。

### 嵌入模式 vs 归属错误

函数同时访问小偏移（≤原类 size）和大偏移（>原类 size）→ **嵌入模式**，不是归属错误。

| 模式 | 小偏移 | 大偏移 | this 来源 | 处理 |
|------|--------|--------|----------|------|
| 偏移 0 嵌入 | ✅ | ✅ | `mov esi, ecx` | 可重归属到包含结构体 |
| 非零偏移嵌入 | ✅ | ✅ | `lea esi, [ecx+X]` | 必须在包含结构体中定义嵌入成员 |
| 全局指针 | 可能有 | 可能有 | `mov ecx, offset g_X` | 不能重归属 |
| 反编译器伪像 | ❌ | 审计有但 ESI 无 | 任意 | 跳过 |

**验证偏移 0 嵌入**：查函数入口 `mov esi, ecx`（无 `lea esi, [ecx+offset]`）。如有 LEA 调整，这是非零偏移嵌入，不能简单重归属。

### `_misattrib_` 函数处理

确定归属错误但未找到正确类时，用 `_misattrib_ClassName::Method` 命名。

**修正流程**：
1. 运行 `_audit_attribution.py` 查 Candidates（size 匹配的 struct）
2. IDA 查 ESI 偏移范围，验证是否在候选 binary_size 内
3. 确认偏移 0 嵌入（`mov esi, ecx`）
4. 同类多函数交叉验证
5. 更新 functions.json：去掉 `_misattrib_`，改为 `CorrectClass::Method`
6. 管线：`apply → export → codegen → check_annotations`

### Codegen Pattern C

`stage4_substitution.py` 中 `_decompose_raw_pointer_arithmetic`：

1. Pattern C（常量偏移注释）→ 立即应用，优先于 stride 检查
2. C1: `(char*)this+N`, C2: `*((_DWORD*)this+N)`, C3: `*((_BYTE*)this+N)` → `/* fieldName */`
3. 偏移索引从 `field_overrides.json` + struct known_members 构建，缓存在函数对象上
4. 仅注释，不替换代码（编译安全）

Pattern A/B（数组步幅分解）→ `build_array_stride_index` 匹配 stride 后重写 `v[K]` → `this->array[var].field`。

## 管线操作

```bash
# 日常迭代（标注更新后）：apply → export → codegen
"D:\Program Files\IDA Professional 9.2\idat.exe" -A -S"pipeline/ida/apply_annotations.py" original\PAL3.exe.i64
"D:\Program Files\IDA Professional 9.2\idat.exe" -A -S"pipeline/ida/export_full.py" original\PAL3.exe.i64
python pipeline/gen/codegen.py all

# 注意：IDA 调用不输出到 stdout，运行时间 30s-5min
# -S 参数写法：-S"绝对或相对路径" IDB路径
# 如果 IDA 静默退出 code!=0，检查脚本是否有 Python import 错误
```

## IDA 查询工具

所有脚本在 `pipeline/ida/` 下，在 IDA 中运行：

```bash
idat.exe -A -S"pipeline/ida/query_todo_fields.py" original\PAL3.exe.i64
idat.exe -A -S"pipeline/ida/query_class_full.py Camera,PalScript" original\PAL3.exe.i64
```

**关键**：IDA 脚本的 `print()` 输出不显示在终端，需要写入文件。所有查询工具输出到 `pipeline/ida/_logs/*.json`。

| 脚本 | 用途 | 输出 |
|------|------|------|
| `query_todo_fields.py` | 全局 _todo_ 字段扫描 | `_logs/todo_field_context.json` |
| `query_highref_fields.py` | 补充高引用字段上下文（需先跑 todo） | `_logs/highref_field_context.json` |
| `query_class_full.py Name` | 指定类全部方法的字段上下文 | `_logs/class_full_context.json` |
| `query_method.py` | 指定函数的内存访问 | `_logs/method_accesses.json`（需改脚本内地址表） |
| `find_strides.py` | 分析嵌入子对象 stride | `_logs/stride_analysis.json` |

**IDA 脚本自定义查询**：写一个 `.py` 文件，用 `idc.get_func(va)`、`idc.generate_disasm_line(ea, 0)`、`idc.get_type(va)` 等 API。输出写入 `_logs/` 目录文件后用 `Get-Content -Path "绝对路径"` 读取。

## 非 IDA 工具

| 脚本 | 用途 |
|------|------|
| `pipeline/check_annotations.py` | 校验合法性（0 errors 门槛） |
| `pipeline/verify_offset.py` | 验证全局实例字段偏移 |
| `pipeline/_audit_attribution.py` | 审计函数归属：`this+N` > binary_size 检测 |
| `pipeline/decomp_quality.py` | 四维指标：type/field/global/attribution |

## 类型判定（二进制指令级）

| 证据 | 结论 |
|------|------|
| `fld`/`fadd`/`fst`/`fcomp` | **float** |
| `fild`/`fistp` | int↔float 转换 |
| `movzx byte`/`mov byte` | **unsigned char** |
| `lea reg,[reg+off]; push reg; call Func(char*)` | **char[] 缓冲区** |
| `lea reg,[reg+off]; mov ecx,reg; call ctor` | **嵌入子对象** |

**关键教训**：`mov eax,[esi+off]; test eax,eax` 对 4 字节**无法区分** int 和 float。只有 FPU 指令能确定性证明 float。

## 嵌入子对象发现

构造函数中 `lea ecx,[esi+offset]; call CtorFunc` 模式：
- 连续 LEA 的 stride = 子对象大小
- 调用目标 = 子对象类的构造函数
- stride > binary_size 时：每个 slot 含子对象 + 额外数据

**二进制 LEA 是嵌入偏移的最终权威**——apply 后的 Hex-Rays 也可能因结构体布局错误给出偏移偏差（CScreenMode 案例：系统性偏移 -8）。如果 decomp 偏移与二进制 LEA 矛盾→以二进制为准。

## 退出条件

- 对齐违规 = 0
- `_todo_` + `_field_` 数趋于稳定
- 重建一致性 ≥95%
- sub_ 数趋于稳定

切换到：编译修复 → 字节匹配阶段。
