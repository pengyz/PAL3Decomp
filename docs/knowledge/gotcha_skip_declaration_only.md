# gotcha: skip / declaration_only 字段契约（发射意图三值模型）

> 2026-11-21 系统审计固化（审计动因：functions.json declaration_only 22 条为死区、
> P-A1 机制锈死、词汇碰撞三层积）。**本文件 = 字段契约的单一真值源**。

## 发射意图三值模型

反编译管线对每个地址必须能表达：

| 意图 | 语义 | 典型成因 | 存储位置 |
|---|---|---|---|
| **full**（默认） | 声明+体都发射 | 正常函数 | —（无标记即 full） |
| **declaration_only** | 真函数，要声明，**体不可信不发射** | 体借用（Hex-Rays 非起点地址渲染借用体）/ ICF 折叠 / C8 伴生 dtor / 导入 DLL 桩 | structs methods 或 functions.json |
| **skip**（type='skip'） | **非游戏函数目标**，无声明无体，出语义域 | CRT 运行时 / 编译器杂项 / 幻影退赔 | skip_functions.json |

## 存储形态与消费矩阵（实测 2026-11-21）

| 存储 | 条数 | 生效消费 | 目录性/辅助消费 |
|---|---|---|---|
| skip_functions.json | 1932 | **type='skip' 仅 4 条**→emit_cpp 自由函数无体；**reason='thunk'+target_name 13 条**→data.py 别名改写；名形命中合成物→emit_headers 过滤 | 消双注豁免标记（declaration_only 24 条=门禁豁免，**非发射语义**）；负 claim 目录（冲突门执法 ~1890） |
| functions.json | 243 | declaration_only=22 →emit_cpp 自由函数无体（**20261121 补的通道，此前死区**） | — |
| structs methods | — | declaration_only（collect 名对齐+emit_cpp 无体+emit_headers 声明+C8 伴生门+证据豁免）；type='skip'（emit_headers 头抑制） | — |

## 已知病灶（收敛排队中）

1. skip_functions.json 一文件四角色（发射抑制/thunk 别名/豁免标记/负 claim 目录）
2. 词汇碰撞：skip 侧 declaration_only=**消双注豁免标记**（权威注册在 struct 侧），与发射意图同字段不同义
3. functions.json declaration_only 通道 20261121 前为死区；P-A1 注释与代码错位（注释称 functions.json，代码读 skip_functions.json）
4. reason 词汇漂移：'thunk'(带 target_name=别名改写生效) vs 'compiler_thunk'(纯目录)

## 使用规则（写入前必读）

1. **自由函数**的发射意图 → functions.json（declaration_only 字段）；**不要**再往 skip_functions.json 塞发射意图
2. **类方法**的发射意图 → structs/<Cls>.json methods（declaration_only 字段）
3. skip_functions.json 新增仅限两种：type='skip'（真非函数目标）+ reason='thunk'+target_name（别名）
4. C8 dtor 对：删除式（slot5）declaration_only；完全形=定义源（stage1 4d 剥隐式织入，20261121 试点）
5. 每条 declaration_only 必须带证据注记（体借用/伴生/导入的成因）——无证据的 declaration_only = 死区候选
6. **单一真值源（20261121 第一性修正）**：declaration_only 只写在权威注册
   （structs methods / functions.json），**不再要求 skip_functions 孪生**——
   export_full 自动派生 skip_addrs（含权威 declaration_only 派生段）。
   历史：曾要求人工孪生（双文件同步）→ 静默失效（RenderTargetNode 案）→
   批量补 100 条孪生 → 当日被第一性质询推翻，孪生协议退役。
   skip_functions 现存角色：legacy 条目（无害保留）/ thunk 别名 / 非函数目录