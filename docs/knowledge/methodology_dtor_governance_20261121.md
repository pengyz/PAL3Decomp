# methodology · dtor 治理方法论（2026-11-21 L1恢复战役提炼）

> 血统：C8 伴生批（batch6/7/8）→ L1 106→96 真衰退归因 → 12 ??_G 恢复（106→113）
> → 全量载体审计（tools/audit_dtor_carriers_20261121.py）。单一真值源=本文。

## 一、问题定性（此处的问题是什么）

**C8 批次把"删除式 dtor = 编译器包装 → 压制不发射"当作普适模型统一落地，
但压制动作同时切断了 ??_G 的符号供给链——头声明（virtual 标记）由删除式条目供给。**

病灶链（12/12 实证）：
```
C8批次: 删除式条目 declaration_only / type=skip
  → 清仓归档 wrapper 单元
  → 头声明缺失/失去 virtual（emit_headers 从被压制条目不再产出 virtual ~Cls()）
  → MSVC 不合成 ??_G（合成前提=virtual 头声明 + 类内存在 dtor 定义）
  → 注册符号 ??_GCls 无 OBJ 符号 → S4 匹配丢失
  → 12 个 100.0% 字节完美的 ??_G 匹配蒸发（L1 −12）
```

理论 vs 证据：C8 的"删除式=编译器包装，无源体"是**理论**；03:17 基线这些
??_G 全部 100.0% 字节匹配是**证据**。理论服从证据（vtable-writer-evidence-law 同款）。

## 二、dtor 符号供给链（现行正确模型）

```
                    ┌─ 头声明 virtual ~Cls()  ← 删除式条目(槽5证据)供给 ←── 被压制即断链
源码唯一析构 ~Cls(){...}（=完全形定义发射）
                    └─ MSVC 自源编译出 ??1(体) + ??_G(合成wrapper)
                                         ↑
二进制: ??1=完全形真身   ??_G=删除式真身（reloc 归一后与合成 wrapper 字节一致）
```

三条硬律：
1. **载体律**：每个注册表 dtor 符号必须有编译载体。??_G 载体 = virtual 头声明 +
   类内至少一个 dtor 定义。wrapper 体本身从不发射（collect 把 backtick
   `` `scalar deleting destructor' `` 归一成 `_scalar_dtor` 后泛化跳过）——**它不是载体**。
2. **唯一源律**：每类恰好一个 `~Cls()` 定义发射（完全形承担；类只有删除式时由
   删除式经 N18 源级化承担——该通路当前被 collect 泛化跳过阻塞，见四）。
3. **压制分级律**：对删除式条目，`declaration_only`（头声明仍产出）与
   `type='skip'`（头抑制）符号学后果完全不同——后者=??_G 死刑。压制前必查本类符号态。

## 三、ABI 真值律（MoveWindow 案固化）

IDB 名内嵌 mangle（如 `QAEHPAX@Z`）可与机器码矛盾——**RET 弹栈字节=显式栈参真相**。
0x445f20：体 `mov edi,ecx`+`retn`（弹栈0）+调用站 `lea ecx,[esi+74h]` 无 push
= thiscall 0 参；注册 `params=[void*]`=hexrays this 分裂病。名 mangle 非真值。

## 四、全量扫描结论（129 类 213 条目 55 符号）

| 桶 | 数量 | 处置 |
|---|---|---|
| 健康 L1（曾L1现L1） | 17 | 保持 |
| 新 L1（完全形发射红利） | 2 | ??1CCBResultWindow / ??1UILoadingFrm |
| **F1 曾L1现丢** | **2** | **??_GUIProgressBar、??_GParticleEffect（待修，见五）** |
| 从未 L1 | 34 | 逐例定谳战役挂账 |
| F2 双形全压制 | 11 类 | 符号双丢态；多数从未 L1，逐例定谳 |
| F3 删除式唯一形态被压制 | 8 类 | 无任何 dtor 载体；同上 |
| F4 双形同发 | 7 类 | **实测安全**（泛化跳过使 wrapper 体从不发射，C2084=0） |
| F5 头声明无 virtual | 31 类 | ??_G 不合成的前提态；仅影响注册表含 ??_G 的类 |

## 五、残余修复清单（scoped 战役，勿重蹈覆辙）

1. **UIProgressBar**：唯一 dtor 形态 0x439110 的 backtick 单元被 collect 泛化跳过
   → 全 TU 无 dtor 定义 → 合成无从发生。
   **修法（已试已回退）**：collect 豁免直接落产生了 N18 未接管的 raw wrapper 直通
   （`~CameraCtrl(int)` 非法形 + 头解析级联崩，S2 −10）。
   **正道**：collect 豁免必须与 N18 源级化联动落地（collect→emit_cpp→stage1 全链
   单测先行：backtick 单元→豁免→N18 剥 flags/删尾/return→合法 `~Cls()` 定义），
   或数据层给 0x439110 显式定义源标记。
2. **ParticleEffect**：头声明 `~ParticleEffect()` 非 virtual（vtables 注解空、槽证据缺失）
   → ??_G 不合成。修法=slot5 归属探针（ctor 写表）落 vtables 注解，virtual 恢复。
3. **F2/F3 的 19 类**：逐例"注册符号×载体"定谳后修（多数无 L1 损失，属符号机会恢复）。
4. **collect 豁免+N18 联动战役**：单测先行（backtick 单元端到端 8 例）。

## 六、教训（流程律）

- **管线改动必须 scoped 验证后再全量**：collect 豁免一次性放开 → S2 134→124。
  回退恢复绿，再设计联动通路。
- **衰退定性看符号不看文件**：文件级 L1 对账会漏"同文件 ±1 对冲"
  （CCBResultWindow ??_G 丢+??1 得=净0，文件级隐形，符号级显形）。
- **S4 全量行对比法**：diff detail 只含 partial 行，集合差是伪影；
  直接跑 compare_pal3 拿全量 rows 对拍（备份/恢复舞步保护棘轮对）。
