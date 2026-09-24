# vtable 映射与验证架构设计（v3 修订版）

日期：2026-09-25
状态：待复核
修订依据：4 路对抗性复核（33 个真机实测反例）+ 用户确认的技术路线转向

## 0. v2 → v3 变更摘要

v2 被 4 路对抗性复核发现 **11 个致命伤**（33 个真机实测反例）。v3 根本性转向：

| v2 缺陷 | v3 修正 |
|---|---|
| 全自动反推签名（欠定问题） | **候选生成 + IDA 定性**（人工确认后才写真相源） |
| L1 作为 vtable 数据最终裁判（结构性失明） | **双裁判制**：L1=函数层裁判，.rdata 对比=vtable 数据裁判 |
| 槽序反推声明序（派生类必错） | **正向迭代**：声明→编译→对比→IDA 归因→修正 |
| 签名等价类（BOOL 物化证伪） | **编译产物实测签名**（.obj 序言/调用序列逐字节对比） |
| mangling 识别合成槽（域迁移错误） | **二进制可观测形态**（序言/地址特征/RTTI 类名锚点） |
| 同源自比（血缘未断） | **证据只来自原始指令字节**（禁止 decomp JSON 输入） |
| 硬门禁（两次死锁） | **棘轮制**（health 只升不降） |
| PMF 断言自永真 + 硬编码 4 | **按实际继承形状生成**，常量来自 IDA 证据 |
| offsetof 虚基成员 C2057 停摆 | **虚基成员跳过 offsetof**（编译期不可用） |
| 门禁不等号反向（spec bug） | **已修正** |
| gbengine 换信仰源 | **PAL3.exe 本体对表**（.h 与 dll 都是参考，真值是 PAL3.exe） |

## 1. 技术路线

### 1.1 核心哲学

```
工具生成候选 → IDA 二进制证据定性 → 人工确认 → 写入真相源
```

**工具只产出候选，不写真相源**。IDA 二进制证据是唯一定性裁判。这与项目既有方法论一致（vtable 存储反查 > 调用约定 > 槽位函数群 > 邻居推断）。

### 1.2 为什么放弃全自动反推

| 问题 | 实测证据 |
|---|---|
| 槽序→声明序是欠定问题 | adv2/adv4：同一槽序可由多种声明序产出；A-1：某些槽序不存在任何声明序能产出 |
| 签名在二进制中不可观测 | vtable 只记地址不记签名；同宽签名（int/指针）字节层不可区分 |
| 自动推断有系统性偏差 | C-1~C-6：未用参数/this 入栈/fastcall/BOOL 物化均导致 arity 错误 |

**正向迭代替代反向推导**：声明→编译→对比是确定性的（编译器保证），比反向推导可靠得多。

### 1.3 双裁判制

| 裁判 | 对比对象 | 覆盖 |
|---|---|---|
| **L1**（函数层） | `.text` 函数体字节 | 签名错误导致函数体字节不同（能捕获大部分签名错误） |
| **.rdata 对比**（vtable 数据层） | vtable 槽序/RTTI/vbtable 数据字节 | vtable 结构错误（槽序/槽数/kind） |

两个裁判独立，不混用。L1 是函数层裁判（它测的没错），vtable 数据是另一个维度。

## 2. 数据模型

### 2.1 vtable 槽位模型（二进制可观测）

```json
vtables: [{
  "addr": "0x0056F824",
  "subobject_offset": 0,
  "declaring_class": "CEffectSystem",
  "address_point": 0,
  "rtti_col": true,
  "slots": [
    {"addr": "0x004C5D50", "kind": "fn", "from": null},
    {"addr": "0x0044A7D0", "kind": "deleting_dtor", "from": null},
    {"addr": "0x0051A390", "kind": "adjustor_static", "delta": 8, "target": "0x0051A2E0", "from": "CCBUI"},
    {"addr": "0x0043DDF0", "kind": "purecall", "from": "UIWnd"}
  ]
}]
```

**kind 识别特征（二进制可观测，非 mangling）**：

| kind | 二进制识别特征 | 声明映射 |
|---|---|---|
| `fn` | 普通函数序言 | 1 声明 ↔ 1 槽 |
| `deleting_dtor` | 与 `??_G` 共享地址（IDA 可见）+ 签名 `void*(unsigned)` | `virtual ~Cls()` ↔ 1 槽 |
| `adjustor_static` | `add/sub imm; jmp` 序言（仅限 ecx 操作数） | 1 声明 ↔ N 槽 |
| `adjustor_vbase` | `sub -N(%ecx),%ecx; jmp` 或 vbtable 间接调整 | 1 声明 ↔ N 槽 |
| `purecall` | 指向 CRT stub 地址（链接后 `__purecall`） | `virtual ... = 0` ↔ 1 槽 |
| `composite` | 多种特征同时命中 | 需 IDA 人工定性 |

**关键实测修正**（v2 错误）：
- **不用 mangling 识别**——真实二进制 531 条名字仅 4 条 mangled
- **复合槽存在**（adv7）：`deleting_dtor × vbase_adjustor` 复合，单值 kind 不够
- **"1 声明 ↔ N 槽"的 N = 可达子对象视图数**，需 IDA 类图确认

### 2.2 槽序验证规则（非生成规则）

```
正向规则（声明 → 槽序）：
  1. 继承槽原位保留（覆写原位替换）
  2. 本地新增段尾插
  3. 本地新增段内：同名组内逆序
  4. 合成槽（deleting_dtor/adjustor）落声明位，不参与同名分组

反向验证（槽序 vs 声明产出）：
  用正向规则从声明生成预期槽序
  与二进制槽序逐槽对比
  偏差 ⇒ IDA 归因（声明错 / 槽序模型错 / 合成槽分类错）
```

**v2 错误修正**：~~"按名分组→首现位置→组内反转"~~ ✗ → 派生类必错（A-1/A-2 实测）。v3 不反推声明序，只正向验证。

### 2.3 单一真相源归属表

| 类别 | 真相源 | 写入点 | 校验器 | 裁决顺序 |
|---|---|---|---|---|
| gbengine 类型 | `include/gbengine/*.h` | `_import_gbengine_headers()` | .rdata 对比 | **PAL3.exe 本体** > .h > dll |
| PAL3 类型 | `data/annotations/structs/*.json` | apply_annotations | 声明校验（棘轮） | annotation > IDB struct |
| 函数签名 | **原始指令字节**（disasm） | 人工确认后写入 | 编译产物实测对比 | **原始字节** > decomp > PDB（仅参考） |
| methods 表 | `data/annotations/structs/*.json` methods | **唯一写点：人工确认** | 棘轮制 | IDA 定性 > 推断候选 |

**v2 错误修正**：methods 表 4 个物理形态中，**struct JSON methods = 唯一推断写点**；ida_structs.json = 只读导出缓存；IDB = apply 单向落地。

## 3. 工作流（候选 + 定性）

```
┌─ 工具层（候选生成）─────────────────────────────────┐
│  coff_vtable.py     → 候选槽序（.obj vtable 读取）    │
│  vtable_compare.py  → 候选差异（二进制 vs 编译产物）  │
│  provenance.py      → 候选签名（寄存器来源追踪）       │
│  槽序分析脚本       → 候选声明序（继承树+规则）        │
│  合成槽分类器       → 候选 kind（序言形态+地址特征）   │
└──────────────────────┬───────────────────────────────┘
                       ↓ 候选
┌─ IDA 定性层（裁判）─────────────────────────────────┐
│  IDA 二进制证据：vtable 地址、槽位内容、函数边界       │
│  人工确认：签名、合成槽分类、声明序                     │
│  交叉验证：候选 vs 二进制逐字节                       │
└──────────────────────┬───────────────────────────────┘
                       ↓ 确认的声明
┌─ 迭代闭环 ──────────────────────────────────────────┐
│  声明 → MSVC6 编译 → .obj vtable → .rdata 对比       │
│  + L1 函数体对比                                     │
│  偏差 ⇒ IDA 定性归因（annotation / 推断器 / 发射器）  │
│  修正 ⇒ 再编译 ⇒ 再对比                              │
└──────────────────────────────────────────────────────┘
```

## 4. 组件设计

### 4.1 组件 0：gbengine til→struct 同步

**职责**：消除 gbengine 三模型（.h / til / IDB struct）断裂。

**方案**：`parse_decls` 后调用 `ida_typeinf.tinfo_t.set_named_type()` 强制同步到 IDB struct。

**验证基准**：**PAL3.exe 本体**（不是 gbengine.dll——dll 是另一个二进制）。用 PAL3.exe 中 gbengine 类的使用模式（ctor vptr 存储、成员偏移访问）验证 .h 的 sizeof/virtual 序。

**v2 错误修正**：~~用 gbengine.dll 验证~~ ✗ → dll 版本/开关可能与 PAL3.exe 不同，真值是 PAL3.exe。

### 4.2 组件 1：签名候选生成（`vtable_sig_infer`）

**职责**：从原始指令字节生成候选签名，**不直接写 methods**。

**证据源（只允许原始指令字节）**：

```
第 1 步：合成槽分类（二进制可观测形态）
  - 与 ??_G 共享地址 + void*(unsigned) 签名 ⇒ deleting_dtor
  - add/sub imm; jmp 序言（仅 ecx）⇒ adjustor_static
  - sub -N(%ecx),%ecx; jmp 或 vbtable 间接 ⇒ adjustor_vbase
  - 指向 CRT stub ⇒ purecall
  - 多特征命中 ⇒ composite，交 IDA 人工定性

第 2 步：调用约定（callee 侧证据）
  - ecx 存 this（provenance 追踪）⇒ __thiscall
  - callee 裸 C3 + 调用点 add esp,N ⇒ __cdecl
  - 首参在 edx + callee 裸 ret ⇒ __fastcall
  - 变参（...）⇒ __cdecl（mangle UAA...ZZ）
  - ret N 在 epilogue，N = 4×DWORD 栈槽数（double/结构占 2 槽）

第 3 步：参数个数（callee 侧读取集为下界）
  - prologue 后 [esp+4..] 读取集合 = 参数下界（非精确计数）
  - 未用参数不可见 ⇒ 标记"可能有隐藏参数"
  - sret 隐藏首参：返回结构体 >8 字节 ⇒ 首参为 sret 指针
  - 调用点 push 计数为旁证（注意 double 双槽/float 位型/push 交错/尾调用 jmp）

第 4 步：输出候选（不写真相源）
  - A 级候选：调用约定+参数个数+返回宽度全部确定
  - B 级候选：缺返回宽度或有隐藏参数嫌疑
  - C 级候选：参数个数不确定
  - 全部写入 methods_pending 旁路字段，等 IDA 定性
```

**v2 错误修正**：
- ~~"prologue 后读取集 = 精确参数个数"~~ ✗ → 是**下界**（未用参数不可见）
- ~~"push imm32 ⇒ int"~~ ✗ → float 常量以 push imm32 传位型
- ~~"取交集"~~ ✗ → ICF 折叠使一地址多签名，按调用点分账
- ~~"int/DWORD/BOOL/enum/指针等价"~~ ✗ → BOOL 有物化转换（test/setne/push vs push，+5B），**BOOL/char/short 单独成类**
- ~~"audit_retn_param_count.py 既有口径"~~ ✗ → 该工具跳过 cdecl/fastcall，不能直接照抄

### 4.3 组件 2：虚调用转换（候选 + 确认）

**职责**：生成候选虚调用转换，人工确认后应用。

**三形态识别（stage3 解码分支内）**：
1. inline 形态：`(*(fn)(vptr+OFFSET))(obj, args)` ⇒ `obj->Method(args)`
2. 局部 vftable 变量：`v5 = *(void**)obj; (*(fn)(v5+OFFSET))(obj, args)` ⇒ `obj->Method(args)`
3. 裸 vptr 读：`*(void**)(obj)`（已转换，保留）

**失败输出契约**：保留既有 stub 语义 + 记账到 `data/status/vtable_transform_failures.md`。

**禁止**：`obj->Base::Method()` 限定调用形态（抑制虚派发 ⇒ 字节必不匹配）。

**名称解析链**：vtable 地址 → IDB vtbl data_members → methods[addr].name。**不用 mangling**。

**v2 错误修正**：
- ~~`MethodName = vtables[cls].slots[i].name`~~ ✗ → 841 槽 0 个有 name
- ~~"独立正则工具"~~ ✗ → R11 实测：_tail_000 需按类重建
- ~~"~32 处虚调用"~~ ✗ → 实测 `_tail_000+N))(` 形态现存 0 处

### 4.4 组件 3：布局断言生成器（默认启用）

**职责**：生成 `_layout_asserts.h`，编译期校验数据布局。

**生命周期**：默认开启，`--no-layout-assert` 关闭，全反编译期持续。

**断言常量来源**：IDA 二进制证据（reg+disp32 绝对地址）。**v2 错误修正**：~~"A 级证据"~~ ✗ → A 级是证据形态等级不是独立性等级，常量必须来自**独立于 annotation 的 IDA 直接读取**。

**继承形状断言（按实际形状生成）**：
```
PMF 大小规则（MSVC6 SP0 实测，无虚基=4/8，有虚基=12）：
  有虚基 ⇒ 12
  否则基类数 > 1 ⇒ 8
  否则 ⇒ 4
```

**v2 错误修正**：
- ~~`sizeof(void (Cls::*)()) == 4` 硬编码~~ ✗ → 10 个双基类必假失败
- ~~"多态性断言"~~ ✗ → PMF 大小是继承形状，不是多态性
- ~~"虚继承 12"~~ ✗ → 实测 MI+虚继承=12，多虚基=12（非 16）
- ~~offsetof 虚基成员~~ ✗ → **C2057 编译期不可用**，跳过

### 4.5 组件 4：声明校验（棘轮制）

**职责**：校验 virtual 声明与二进制 vtable 一致（棘轮制，非硬门禁）。

**校验项**：
1. 槽数数对比（按 view 对，MI 多表各自校验）
2. 槽序对比（用 §2.2 正向规则从声明生成预期槽序）
3. 签名对比（编译产物实测 vs 二进制序言/调用序列）

**棘轮制门禁**：
```
vtable_health[class] = 已验证槽数 / 总槽数
门禁规则：health 只能升，不能降
  - health 下降 ⇒ 阻塞（回归检测）
  - health 不变 ⇒ 放行
  - health 上升 ⇒ 放行 + 更新基线
```

**v2 错误修正**：
- ~~硬门禁（codegen exit 1）~~ ✗ → 两次死锁（v1/v2）证明此路不通
- ~~"未解析槽位 < 阈值 ⇒ 阻塞"~~ ✗ → 不等号反向（spec bug），0 未解析反而阻塞
- ~~同源自比~~ ✗ → 校验基准是**编译产物**（独立于 methods 表）

### 4.6 组件 5：编译产物对比（vtable 数据最终裁判）

**职责**：读编译产物 .obj 的 vtable，与二进制 vtable 逐槽对比。

**对比项**：
- 槽数数（含 RTTI COL 前缀的 address point 偏移）
- 槽序（符号名→VA 归约序列）
- 每个槽的归一化二元组（目标函数, this 调整量）——动态 delta 的 thunk 用 (target, kind=dynamic, const) 三元组
- vbtable 内容（虚继承类）

**强制发射**：
- 普通类：探针 TU 构造对象
- 抽象类：定义具体派生类构造（借派生 ctor 先写基类 vptr 引发基类表发射）
- 无虚析构的抽象类：需 dummy `Cls::Cls(){}` 用实体（实测 adv5 证明构造对象不可行）

**v2 错误修正**：
- ~~"可选兜底"~~ ✗ → vtable 数据的最终裁判，必须存在
- ~~"探针 TU 构造对象"~~ ✗ → 抽象类不可构造（adv5 实测 0 个 vtable 符号）
- ~~"读 .obj 的 .rdata 对比函数地址"~~ ✗ → .obj 槽是符号重定位非地址

## 5. 数据流

```
PAL3.exe 原始指令字节（disasm）
  ↓ provenance.py（寄存器来源追踪）
候选签名（methods_pending 旁路）
  ↓ IDA 定性（人工确认）
methods 表（真相源，唯一写点）
  ↓ 发射器（正向生成）
C++ 头文件（virtual 声明 + _layout_asserts.h）
  ↓ MSVC6 编译（布局断言自动校验）
编译产物 .obj（强制发射探针 TU）
  ↓ coff_vtable.py + vtable_compare.py
.rdata 对比（vtable 数据最终裁判）
  ↓ L1 对比（函数层裁判）
一致 ✓ / 偏差 ⇒ IDA 归因 ⇒ 修正
```

**关键**：证据链**无反馈环**——methods 表只从原始指令字节写入，不从 decomp JSON 写入。

## 6. 测试策略

| 测试 | 方法 | 覆盖 |
|---|---|---|
| 签名候选正确性 | held-out 集（IDA 人工确认条目）测 A 级准确率 | 调用约定/参数/返回 |
| 虚调用转换正确性 | 编译后 L1 字节比对 | 转换后代码等价性 |
| 布局断言正确性 | 编译 `_layout_asserts.h` | 偏移/大小/继承形状 |
| 声明校验 | codegen 生成 + 黄金 fixture | 槽数/槽序/签名 |
| **负向/变异测试** | 故意改槽序/槽数/签名，断言校验必须报警 | 门禁判别力 |
| **继承族夹具** | MI thunk / 虚析构 / 纯虚 / 跨类共享各 ≥1 例 | 合成槽覆盖 |
| **确定性测试** | 连续两次 codegen 产物 diff 为空 | 可重跑 |
| **编译器规则金样本** | `_vtable_abi_probe/` + `_vtable_advprobe/` + `_vtable_attack_cases/` | ABI 前提 |
| **.rdata 对比** | 编译产物 vs 二进制逐槽 | vtable 数据 |
| **L1 对比** | 函数体逐字节 | 签名正确性 |
| COMDAT 折叠用例 | 相同 COMDAT 折叠时符号归约验证 | 组件 5 |

## 7. 最终裁判声明

| 裁判 | 覆盖 | 不覆盖 |
|---|---|---|
| **L1 字节比对** | 函数体字节（签名错误导致函数体差异） | .rdata vtable 数据 |
| **.rdata 对比** | vtable 槽序/槽数/kind/RTTI/vbtable | 函数体字节 |
| **两者合取** | 字节完全匹配 | — |

**vtable 数据的最终裁判是 .rdata 对比**（组件 5），不是 L1。L1 是函数层裁判。

## 8. 约束

1. **vptr 由编译器生成**——annotation 不声明 `__vftable`/`vfptr`/`vtable` 成员
2. **`vtables[]` 数组是唯一声明点**——有 = 多态，无 = 非多态（需完备性验证防漏写）
3. **每个 vtable slot 必须有对应 virtual 声明**——数量+顺序+签名严格对应（含合成槽映射）
4. **虚调用始终用直接方法调用**——做不到的记账+证据，不降级（失败输出契约：保留 stub 语义）
5. **布局断言默认开启**——参数关闭，全反编译期持续生效
6. **工具生成候选，IDA 定性**——工具不直接写真相源
7. **证据只来自原始指令字节**——禁止 decomp JSON 作为签名证据输入
8. **棘轮制门禁**——health 只升不降，不设硬门禁
