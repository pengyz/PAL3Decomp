# L1 三口径定义 + 复算命令 + COMDAT 膨胀限定

**type**: reference
**created**: 2026-10-15
**来源**: T80 首次定义（captain.jsonl t80 段末"度量口径：行 150 / 唯一 124 / 去删除析构 106"）· T81 续用 · reviewer 2026-10-15 复核闭环

## 三口径定义

| 口径 | 定义 | 计算 | 用途 |
|---|---|---|---|
| **行数** | `match_L1` 行计数 | `len(L)` | 历史延续（**受 COMDAT 膨胀影响**）|
| **唯一** | 按 `va` 去重 | `len(set(r['va'] for r in L))` | **主判据**（前提：同 va 同函数，2026-10-15 实测 0 冲突成立）|
| **去删除析构** | 唯一里去 `deleting destructor` 名的 | `sum('deleting destructor' not in n for n in u.values())` | 反映**非编译器生成形态**的 L1 |

## 复算命令（3 秒，当场核）

```bash
python3 -c "
import json, collections as C
d=json.load(open('data/status/s4_baseline.json'))
L=[r for r in d['rows'] if r['status']=='match_L1']
c=C.Counter(r['va'] for r in L)
u={r['va']:r['name'] for r in L}
game=sum('deleting destructor' not in n for n in u.values())
print(f'L1 行数: {len(L)}')
print(f'L1 唯一(va 去重): {len(c)}')
print(f'去删除析构: {game}')
"
```

## COMDAT 膨胀限定（⚠️ 必读）

**「行数」被 COMDAT 折叠删除析构人工膨胀**：
- 实测（2026-10-15）：184 − 155 = **29 条多余行**，**100% 是 COMDAT 折叠删除析构**
  - `UIWnd::scalar deleting destructor` @0x44E5C0 × **25 行/25 文件**
  - `UIButton` @0x43F950 × 5
  - `UISceneMap` @0x450070 × 2
  - 同 va 同名 **0 冲突** ✓

**⇒ 单引「行数」会高估游戏进度** —— **三元组成套引用**（`行/唯一/去删除析构`）是正确做法。

## ⚠️ 措辞纪律（reviewer 2026-10-15 修正）

**禁用「游戏函数 L1」措辞**（T66-F1 同族措辞漂移）：
- 被剔的 18 个 `scalar deleting destructor` **恰是游戏类的**（UIWnd/UIButton/UISceneMap…）
- 剔除的是**编译器生成函数形态**，**不是「非游戏代码」**
- **正确措辞**：「**去删除析构**」或「非编译器生成形态」

**历史措辞漂移**（已修正）：
- T80 原名「去删除析构」→ 漂移为「游戏（反映游戏函数 L1）」→ **本档回归「去删除析构」**

## 引用纪律

- 引用三口径**必须成套**（`行/唯一/去删除析构`），禁止单引「行数」
- 引用时**必须附复算命令**（上文）
- 出处：**T80**（首次定义），**非 T82**（T82 是 L2 593 consecutive ROI 量化，与三口径无关）
