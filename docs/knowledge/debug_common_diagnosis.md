# 常见问题诊断方法

**created**: 2026-10-22（知识库重构·补 debug）

## 诊断原则（CLAUDE.md 病灶层检查）

**动前必答三问**：
1. **病灶在哪一层？**（annotation / apply / export / codegen / stage1-5）
2. **消费者实际读的是哪个文件/哪份声明？**（#include 链 / /I 顺序）
3. **报错还缺什么信息？**（如 `does not take N parameters` 只给个数不给类型）

**配套**：定位完成后把**实测数字**写进被改代码旁的注释。

## 诊断流程图

```
问题现象
  ↓
┌─ S2 编译错误？ ──→ 用 error_classifier.py 分类
│                     ├─ annotation_fix (33.6%) → 修注解
│                     ├─ codegen_fix (22.6%) → 修 codegen
│                     ├─ hexrays_limit (42.5%) → 不修（已知限制）
│                     └─ manual_idb (1.4%) → 记待办
│
├─ L1 字节不匹配？ ──→ 用 match 三限定核查
│                      ├─ 截断（编译多出的尾部）
│                      ├─ 长度相等（截断后）
│                      └─ 重定位 4 字节 don't-care
│
├─ 布局偏移错？ ──→ 用 audit_type_layout.py（编译器裁判）
│                   ├─ 用 objdump 访问形交叉验证
│                   └─ 注意：audit 假阳性（wrapper 上下文差异）
│
├─ 类型/签名错？ ──→ 用 member_usage_scan.py（全用法形）
│                     ├─ 混合用法 ⇒ 冻结（禁猜测）
│                     └─ 三判据①须值证（位型立即数）
│
└─ 管线慢？ ──→ 用 check_incremental.py（hash+timestamp）
                └─ 管线脚本变 ⇒ 强制全跑
```

## 常见诊断命令

### 1. S2 编译错误分类

```bash
python pipeline/cli.py probe s2
python tools/error_classifier.py --summary
```

**输出**：根因分布（annotation_fix / codegen_fix / hexrays_limit / manual_idb）

### 2. L1 字节比对

```bash
python pipeline/cli.py match
```

**三限定**（`[metric]` 行当场读）：
- **截断**：编译产物先截到原函数长度再比
- **长度相等**：截断后两侧长度必须相等
- **重定位 4 字节 don't-care**：重定位覆盖的字节即使不同也计 match

### 3. 布局审计（编译器裁判）

```bash
python tools/audit_type_layout.py --only <Cls>
```

**判据**：`char c[offsetof(Cls, m) == 0x<注解偏移> ? 1 : -1]`
不匹配 ⇒ C2118 ⇒ 冲突

⚠️ **注意假阳性**：audit wrapper 上下文可能与真实 TU 不同源（R63 实证）

### 4. 成员全用法形扫描（P0-6）

```bash
python3 tools/member_usage_scan.py --cls <Cls> --offset 0xNN --json
```

**7 种用法形**：arith / cmp / assign / addr / float / bitop / indirect
**判据**：混合用法 ⇒ 冻结（禁猜测）

### 5. 增量检查

```bash
python3 tools/check_incremental.py
```

**7 项输入**：annotations · ida_structs · decomp · pal3_src · pipeline_gen · pipeline_ida · tools
**规则**：管线脚本变 ⇒ 强制全跑

## 常见根因（历史教训）

| 症状 | 根因 | 实证 |
|---|---|---|
| S2 突降 | 批量改型破坏用法 | R51 +617 |
| L1 不升 | 字节匹配三限定外的真实差 | 度量盲区 |
| 布局偏移差 4 | vptr 占位 + gap 重复 | P0-1 |
| sizeof ≠ IDA | MSVC 对齐 padding | P0-1 |
| 测试假失败 | worktree editable install 污染 | R70 |
| commit 丢失 | pre-commit hook 静默阻塞 | R48-R70 |

## 诊断工具清单

| 工具 | 用途 | 耗时 |
|---|---|---|
| `check_annotations` | 注解一致性 | 秒级 |
| `error_classifier` | 错误分类 | 秒级 |
| `audit_type_layout` | 布局审计（编译器裁判）| 分钟级 |
| `member_usage_scan` | 成员全用法形 | 秒级 |
| `check_incremental` | 增量检查 | 秒级 |
| `check_dual_claims` | 两说并存检测 | 秒级 |
| `check_annotation_preflight` | 前置全检 8 项 | 0.108s |

## 关联

- **病灶层检查**（CLAUDE.md R16）
- **两层定位**：[debug_two_layer_localization.md](debug_two_layer_localization.md)
- **管线架构**：[arch_pipeline_overview.md](arch_pipeline_overview.md)
