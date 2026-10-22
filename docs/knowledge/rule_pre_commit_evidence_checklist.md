# 落盘前证据充分性 Checklist（2026-10-21 ROI 诊断立）

## 起因：6 轮回滚实证（R51-R56 净改善 ≈ 0）

| 轮 | 落盘 | 被证伪 | 原因 |
|---|---|---|---|
| R51 | 59 弱型改型 | **全部** | +617 错误（P0-6 单点证据不足）|
| R53 | 数组 50/100 元素 | 撤回 | idiv 除数误读 |
| R54 | 值位面标 | 撤回 | 差 16B 非同存储 |
| R55 | 2 条改型 | 回退 | MIXED/ASSIGN 非 FLOAT |
| R56 | 撤位面标 | 不彻底 | 新旧说并存 9 处 |

**模式**：`分析 → 落盘 → 被证伪 → 回滚` = 「事后 reviewer」而非「事前 gate」

## Checklist（落盘前必答 5 问）

### ① 证据等级（A 级 = 指令字节？）
- ✅ A 级：`ret N` · 调用点 `push` · `fld/fstp/mov` opcode · 访问形 · 值位型常量 · vtable 槽 · IDA 函数边界/xref
- ❌ B 级（循环）：IDA 修饰名 · IDA `stack_frame` 参数名/型 · IDA/decomp 反编译
- **A 级不足 ⇒ 标 `evidence_level: B` 落盘，不伪标 A**

### ② 单点还是全用法形？（P0-6）
- ✅ 全用法形扫描（`tools/member_usage_scan.py`）：算术/比较/赋值/取址/浮点/位运算/间接
- ❌ 单点 opcode（R51 +617 回归源）
- **用法混合 ⇒ 冻结**（可能 union/位面复用）

### ③ 过滤规则可复现吗？
- ✅ 另一个 agent 能跑出同样数（明确定义：分子/分母/过滤器/范围）
- ❌ 判定和 ≠ 规则数（R56 verifier 抓到 404 = 4 类异质判定和）
- **规则未钉定义 ⇒ 不算「可复现」**

### ④ 有无同名/同偏移混淆？（张冠李戴）
- ✅ 逐类独立核（PalScript vs UIItem/UIScene 同名不同类）
- ✅ lea 形寄存器语义核（edi/esi 是否 this）
- ✅ offset 十进制/十六进制换算核
- ❌ 凭名称/偏移相似就合并

### ⑤ 有无账面不同步？
- ✅ 注解 + `data/status/pending/` **双改**
- ✅ 撤标须**删旧说**非追加（R56 抓到 9 处残文本）
- ❌ 只改一处

## 配套纪律

### 小批量落盘（≤5 条/批）
- 59 条一把梭（R51）→ +617 全回滚
- **每批 ≤5 条 + 逐条消融验证**（S2/总错误当场读）

### 判定和 ≠ 规则数（分离产出）
- **判定和**：人工逐条判定的累加（如 404）—— 须留痕逐条
- **规则数**：统一过滤器跑出来的数（如 C=405）—— 须可复现
- 两者**不得混用**

### 证据充分性 gate（前置）
```
落盘前：checklist 5 问
   ↓ 全答 ✓
消融验证（apply→export→codegen→probe）
   ↓ 指标合格
提交 push
   ↓
事后 reviewer（二次把关）
```

**不是取消 reviewer，是把检查前置到落盘前**。

## 关联

- **P0-6 改型纪律**：[method_function_signature_inference.md](method_function_signature_inference.md) §7
- **证据分级**：[rule_evidence_tiering_no_unobtainable_gate.md](rule_evidence_tiering_no_unobtainable_gate.md)
- **证据循环性**：同上（IDA 签名=循环论证）
- **衰退纪律**（CLAUDE.md）：先分析定位不立即回退
