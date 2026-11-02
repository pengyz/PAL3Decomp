# E2E 用例规则（双轨对拍集成测试）

> 2026-11-02 立项 · 分支 feature/ghidra-dual-track · 配套 spec: 2026-11-02-ghidra-dual-track-spec.md
> 目的：**已知真值的独立集成测试**——注解→双轨→编译全链的合理性验证；与 PAL3 数据零耦合。

## 1. 用例结构（一案一目录，全自包含）

```
ghidra_track/fixture/cases/<case-id>/
  src/            已知源（C++，编译出 fixture 可执行体）
  annotations/    已知真值注解（**正式 annotation schema 子集**，禁私有格式）
    structs/*.json  functions.json  globals.json
  expected/
    layout.json     布局真值（sizeof/offsetof——机测产物，禁手算）
    compile.json    编译面期望（允许错误桶白名单，见 §3）
    render.json     渲染判据（语义钉，见 §2 D3）
  case.json       元数据：层级/覆盖特性/判定口径/双轨开关
  report.json     运行产物（每次 run 覆写）
```

case.json 形：
```json
{"id": "case-01-struct-union-overload", "tier": "L1",
 "features": ["inheritance", "vtable", "inline-union", "overload", "globals", "zero-arg", "tail-pad-reuse"],
 "dual_track": true, "judge": ["D1", "D2", "D3", "D4"]}
```

## 2. 判定维度（四钉，全过=case PASS）

| 钉 | 判据 | 失败归因桶 |
|---|---|---|
| **D1 布局钉** | ①layout.json=机测 offsetof/sizeof ②注解 size=layout ③**Ghidra 库内 sizeof 对账=0 mismatch** | converter（转换层）|
| **D2 编译钉** | 丑C 全编译：**错误必须 ⊆ compile.json 允许桶**（变换 pass 域白名单）；白名单外零容 | transform（变换）|
| **D3 渲染钉** | render.json 逐条语义断言（正则/AST 面）：`this->member` 出现、重载分离、union 视图、虚调用形、零参 XZ 名、mangled 直通 | transform / converter |
| **D4 对拍钉** | 双轨同注解：C₁（IDA 轨）与 C₂（Ghidra 轨）各自编译错误集差分——差异必分类归因（约束/伪影/管线）| tracks-diff |

## 3. 错误桶白名单（D2 的防混淆核心）

编译错误先分桶，白名单外=红：
- `noise-missing-src`：缺源噪声——**全量出码后应为零**；非零=出码遗漏（管线缺陷）
- `ghidra-ism`：`undefined*`/`code`/`LAB_/FUN_/DAT_` 类——变换 quick 预设域（白名单候选，计数随变换接入应单调降）
- `transform-broken`：ctor 直调/`code*` 解引用/模板残——变换应消，逐个转白名单需附理由
- `annotation-signal`：`X 无成员 m_y`/类型转非法/布局越界——**真信号桶（禁入白名单）**=差分对象

## 4. 分层（复杂度爬升=管线压力爬升）

| 层 | 特性面 | 代表 |
|---|---|---|
| L0 冒烟 | 打印/全局/普通函数 | hello-world |
| **L1 结构** | 继承+vtable+内嵌 struct+inline union+重载+全局+零参+尾填充复用 | **case-01** ✅ 已立 |
| L2 边界 | 函数指针/静态成员/虚继承/位域/枚举/模板实例 | 待立 |
| L3 对抗 | 优化码（-O2）内联/尾合并/switch 表 | 待立 |

## 5. 运行规则

1. 一键：`ghidra_track/fixture/run_e2e.sh <case-id>`（=编译 fixture→layout 机测→plan→apply→出码→D1-D4 判）
2. 每案 `report.json` 落四钉结果+错误桶分账；**全绿判据=四钉全过**
3. 每加一层特性=新 case 目录（禁在旧 case 里改期望迁就实现——**期望即真值**）
4. 双轨开关：`dual_track:true` 案必须 IDA 轨同注解复跑（对拍前提交=禁单轨绿即过）

## 6. 复用与对拍约束

- **注解 schema=正式子集**：case 注解可被正式 apply_annotations/转换层直读（禁 fixture 专用字段）
- IDA 轨复用：同一份 annotations/ 灌 IDB（对拍前提）；轨差异只准来自渲染器
- 独立性：case 禁读 PAL3 任何数据；fixture 可执行体由 case src 自编译
