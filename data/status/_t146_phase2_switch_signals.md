# T146 · Phase 2 切换信号评估表（2026-10-15，数字全部当场实测）

## 切换信号定义（任务给定：满足其二即切换；估 S2 ≈ 155+ 后）

| # | 信号 | 现状（当场实测） | 判定 | 预计何时满足 |
|---|---|---|---|---|
| 1 | **前沿 ≤5 错单元清零** + 连续 2 轮新绿 <1 | 失败单元 74 个中 **1..5 错的 25 个**（1 错×1 · 2 错×8 · 3 错×12 · 4 错×3 · 5 错×1）；未清零 | ❌ 未满足 | 按 T143-T145 节奏（每轮净清 2-3 个前端单元）≈ **8-12 轮**后清零；再加 2 轮观察 ⇒ 约 **10-14 轮** |
| 2 | **连续 3 次 loop L1 增长 <3** | 近 3 轮 L1 增量 **+11（T143 批1）→ +10（T144 批2）→ +7（T145 批3）**（任务背景值，与 s4_baseline 棘轮一致），全部 ≥3 | ❌ 未满足 | 增量递减趋势（11→10→7）⇒ 预计 **3-5 轮**后连续 <3；但 partial 快赢/布局修（Role/RoleStatePanel 家族）可能续命 ⇒ 保守 **5-8 轮** |
| 3 | **剩余错误以 hexrays_limit/manual_idb 为主** | `error_classifier --summary`（当场跑）：**annotation_fix 36 文件 48.6%** · codegen_fix 10 · **hexrays_limit 21（28.4%）** · manual_idb 0 · unknown 7 ⇒ 注解+codegen 型仍 **62.1%**（任务口径"45% 仍注解型"实测 **48.6%**，略高） | ❌ 未满足 | annotation_fix 需从 36 降到 ≲15 才翻主次 ⇒ 与 S2 前沿推进同速，估 **S2 ≈ 155+ 时**（与任务估计一致） |

## 三信号当前状态汇总

```
信号1 前沿清零        [██░░░░░░░░] 25/74 单元在 ≤5 错前沿（未清零）
信号2 L1 增速衰减     [██████░░░░] +11→+10→+7（递减中，未连续 <3）
信号3 错误构成换主次   [███░░░░░░░] 注解+codegen 62.1% vs hexrays+manual 28.4%
⇒ 切换条件：0/3 满足（需任意 2 条）—— 继续 Phase 1
```

## 结论

**暂不切换**。三条信号均未满足（0/3）。最快的信号 2 预计 3-8 轮内触发；
信号 3 与 S2 ≈ 155 的估计一致（当前 135，按每轮 +1~+3 需 7-20 轮）。
建议：Phase 1 继续主攻「annotation_fix 36 文件」（48.6% 最大桶）+
partial 近池可注解单点修族（返回型/参数个数形、显式 this 形、成员偏移形）。

## 数据来源（可复跑）

```bash
python pipeline/cli.py status                                    # S2/错误/截断单元
python tools/error_classifier.py --summary                       # 错误构成
python3 -c "import json,collections as C;c=json.load(open('data/status/probe_census.json'));\
f=[r for r in c['s2']['results'] if r['status']!='ok'];\
print(sorted(C.Counter(len(r.get('errors') or []) for r in f).items()))"   # 前沿分布
```
