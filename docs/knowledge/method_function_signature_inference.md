# 函数签名推断方法论：从汇编推断参数个数/类型/名字

**created**: 2026-10-21（用户三轮指正定谳）
**适用**：PAL3 反编译的 annotation 签名补全 / 校正 / 验证

---

## 一、为什么不能信 IDA 的签名（循环论证）

**IDA 的函数签名是我们注入的**：
```
apply_annotations.py:11-12
  1. functions — set_name + SetType (幂等)
  2. globals   — set_name + SetType (幂等)
```
⇒ IDA 修饰名 / `stack_frame` 参数名型 / 反编译 **全是读回我们自己的数据** ❌

**实证**：
- `strings PAL3.exe | grep VisUpdate@SceneVisNode` = **0 命中**（二进制无此名）
- `?VisUpdate@SceneVisNode@@QAEXXZ` 的 `XXZ=void()` 是**我们写进去的**
- `stack_frame` 报 `nVal:int` —— `nVal` 在 `functions.json` 里（我们标的）

**⇒ 用 IDA 验证我们的签名 = 循环论证**。

---

## 二、证据分级（哪些是二进制事实）

### ✅ A 级（非循环 · 指令/数据字节）

| 证据 | 来源 | 能推什么 |
|---|---|---|
| **`ret N`** | 函数尾指令 | **参数个数**（`__thiscall`/`__stdcall` callee-cleans：N/4 = 栈参数个数）|
| **调用点 `push` 序列** | 调用者指令 | 参数个数（交叉验证）|
| **`fld`/`fstp qword`/`mov` opcode 形** | 指令 | **参数类型**（浮点/整型/指针）|
| **访问形** `0xNN(%reg)` | 指令 | 成员偏移 · 数组步进 |
| **值位型常量** `movl $0x41200000` | 指令 | 类型（=10.0f 位型 ⇒ float）|
| **vtable 槽位**（.rdata） | 数据 | 虚函数归属 |
| **IDA 函数边界** | 自动分析 | 函数范围（可信）|
| **IDA xref** | 自动分析 | 调用关系（可信）|

### ❌ B 级（循环 · 我们写入的投影）

| 证据 | 为什么不可信 |
|---|---|
| IDA 修饰名 `?F@C@@QAE...` | `apply_annotations set_name` 写的 |
| IDA `stack_frame` 参数名/型 | `apply_annotations SetType` 写的 |
| IDA/decomp 反编译 | 基于我们写的类型 |
| `placeholder_retN.json` 的 `nparams` | 实测有误（0x54211A 读 retn=2 但真实 0）|
| decomp JSON 签名 | Hex-Rays 基于我们写的类型 |

---

## 三、工作流（三步）

### Step 1 · IDA 给边界 + xref（可信）

```python
idb_open(input_path='.../PAL3.exe.i64', idle_ttl_sec=3600)  # ← 3600 防闲置失效
xrefs_to(database=SID, addrs='0xADDR')       # 调用点（可信）
disasm(database=SID, addr='0xADDR')          # 函数边界 + 指令
```

### Step 2 · 汇编推断签名（A 级）

**① 参数个数** ← `ret N`：
```
retn       = 0 参（__thiscall 只有 this）
retn 4     = 1 参
retn 8     = 2 参
retn 0Ch   = 3 参
```
⚠️ 交叉验证：**调用点 `push` 计数**（排除序言 `push ebx/esi/edi` 保存寄存器）

**② 参数类型** ← opcode 形：

| 形 | 推断 |
|---|---|
| `fld [esp+N]` / `fstp qword` 后 `mov edi,[+4]; mov ebx,[+0]` | **double**（8 字节分解）|
| `fstps 0xNN(%reg)` / `flds` | **float**（4 字节）|
| `mov [esp+N], eax`（整数）| **int**（4 字节）|
| `mov [esp+N], ecx`（地址）| **指针** |
| `lea ecx, [esi+0Ch]; push ecx` | **结构体指针**（取址传参）|
| `push offset aBbb` | **const char***（字面量）|

**③ this 确认** ← `mov esi, ecx` / `mov eax, ecx`（ecx=this ⇒ `__thiscall`）

**④ 参数名** ← 用法语义（**B 级**）：
- 浮点参数被 `fld`/`fstp` ⇒ 名含 `f`/`F`（如 `fVal`）
- 索引参数用于数组下标 ⇒ 名含 `nIdx`/`i`
- 路径/字符串 ⇒ `psz`/`lpsz`

### Step 3 · 名字（五面语义 · B 级）

① 调用者 ② 被调用者 ③ 成员访问 ④ 类归属 ⑤ 交互模式（字面量）
- **conf<60 ⇒ 冻结 `_todo_`**，禁伪语义命名（`m_nState_4968` 同 `_todo_`）

---

## 四、实证案例：`SetParam` (0x536160)

### 汇编证据（A 级）
```asm
536160: sub esp, 44h          ← 局部 0x44（无 push ebp prologue）
536164: mov esi, ecx          ← this=ECX ✓ __thiscall
...
5361ed: retn 8                ← **2 栈参** ✓

调用点（IDA xref 给的 0x535561，在 MiniGame3Update 内）：
535543: fld [esp+18h+fVal]    ← **装 double**（指令字节）
535547: mov ecx, [esi+8]
53554a: fstp qword ptr [esp+18h+nVal]   ← **存 qword**（8 字节）
53554e: mov edi, [esp+18h+nVal+4]       ← 高 dword
535552: mov ebx, [esp+18h+nVal]         ← 低 dword
53555d: mov ecx, [esi]                  ← this
53555f: push edi                        ← arg2
535560: push ebx                        ← arg1
535561: call SetParam                   ← 2 push ✓ 与 retn 8 一致
```

### 结论
- **参数个数**：2 ✓（`retn 8` + 调用点 2 push 双证）
- **参数类型**：**`double`**（`fld`/`fstp qword` 分解成 edi+ebx）—— **非注解的 `int nVal, int nVal2`**
- **签名**：`? SetParam(Actor *this, double fVal)` 或按用法定

### 注解错在哪
`int __thiscall(Actor *this, int nVal, int nVal2)` —— **把 double 拆成两个 int** ✗
（可能因 Hex-Rays 看到两个 dword 传递就标成两个 int）

---

## 五、禁令

1. **禁用 IDA 修饰名/stack_frame/反编译做"验证"**（循环）
2. **禁凭 `placeholder_retN.json` 的 nparams**（实测有误）
3. **禁批量推断**（每条独立取证，同批相似 ≠ 第 N 条成立）
4. **禁伪语义命名**（conf<60 ⇒ `_todo_`）
5. **禁仅凭 signature-this 判归属**（须成员访问 + 调用点核对）

---

## 六、核对出口

签名落盘记录须含：
```json
{
  "signature": "double __thiscall(Actor *this, double fVal)",
  "source_note": "[A 级汇编 2026-XX-XX] retn 8（2 栈参）+ 调用点 0x535561 push edi/push ebx（2 push）"
                + " + fld/fstp qword（double 型）· this=ECX（mov esi,ecx）"
                + " · IDA xref 1 调用点在 MiniGame3Update(0x5353a0)"
                + " · ⚠️ 原注解 int nVal,int nVal2 错（double 被拆成两 int）",
  "evidence_level": "A（指令字节）",
  "circular_check": "未用 IDA 修饰名/stack_frame/反编译 ✓",
  "confidence": 85
}
```

---

## 关联

- **证据循环性**：[rule_evidence_tiering_no_unobtainable_gate.md](rule_evidence_tiering_no_unobtainable_gate.md)
- **衰退纪律**（CLAUDE.md）：先分析定位，不立即回退
- **五面语义**（CLAUDE.md）：命名证据面
- **IDL MCP 运维**：`idb_open(idle_ttl_sec=3600)` 防闲置失效；JSON-RPC 可调 69 工具

---

## 七、改型纪律（2026-10-21 R51 教训）

**改成员类型前，必须查该成员的全部用法形**（不只一个 opcode）。

### 反例（R51 实证：+617 错误）

59 条弱型改型（`int`→`struct` 31 条 · `float`→`struct` 16 条）致 S2 117→111 · 总错误 1268→1885。

**根因**：opcode 证据只查一种用法形（`lea`+`call <ctor>` = 子对象），
未查其他用法（算术/比较/赋值）——改 `int`→`struct` 破坏了整数运算。

### 正解：全用法形扫描

```bash
# 对成员 offset NNN，扫类方法内所有访问形
objdump -d --start-address=<fn> --stop-address=<fn+size> PAL3.exe | \
  grep "0xNNN(%esi)"
# 分类：算术（add/sub/imul）· 比较（cmp/test）· 赋值（mov reg,addr / mov addr,reg）
#       取址（lea）· 传参（push）· 浮点（fld/fstp）· 位运算（and/or/xor）
```

**只有「用法单一」的成员才可安全改型**（如仅浮点访问 ⇒ float）。
**用法混合**（既有算术又有取址）⇒ 冻结（禁猜测）。

### 判据

| 用法形组合 | 可改型？ |
|---|---|
| 仅浮点（fld/fstp/fadd/fmul）| ✅ float/double |
| 仅取址传参（lea + push）| ✅ 结构体指针 |
| 仅整数算术（add/sub/imul/cmp）| ✅ int |
| **混合**（算术 + 取址）| ❌ **冻结**（可能 union/位面复用）|
| **零特征** | ❌ 冻结 |
