# class/struct 键不一致只产 warning（非 error）—— 勘误

**created**: 2026-10-22（对抗复核 7bce40c6 证伪 lead 归因）

## 勘误背景

lead commit `694203cea` 声称「class/struct 键不一致（C4099/**C2653**）」+「C2653/C4099 消除」
⇒ **C2653 半句证伪**（对抗复核实测）。

## 实测证据

**同 TU 重建 pre-fix 头**（43 条 `struct X;` + `Combat/CCBStage.h`）：
```
C4099 = 50（warning，class/struct 键不一致）
C2653 = 0
error = 0
obj 正常产出
```

⇒ **class/struct 键不一致只产 warning，零 error**

## C2653 真因（58 条全仓归因）

| 族 | 数 | 真因 |
|---|---|---|
| C2039 级联 | 23 | 成员不存在 |
| C2227 系 | 17 | `->` 左侧非类/结构 |
| **C2440 转型级联** | **9** | **float→指针转型失败**（Hex-Rays 垃圾 float 局部量）|
| C2027 不完整型 | 4 | 缺 include/前向声明 |
| 其余 | 5 | — |

**0 条与 class/struct 键有关**

## 正确结论

| 项 | 正确 |
|---|---|
| C4099 | class/struct 键不一致（warning）✅ |
| C2653 | **与 class/struct 无关** ❌ |
| 方案 B（emit_cpp.py:848）| 只清 warning（50→5），**0 error 收益** |

## 残留（方案 B 不完整）

5 条**反向 C4099**：gbengine 真 struct 型（gbVec3D/gbColorQuad/gbTextureArray/gbVFile/gbGfxManager）被 emit 成 `class`

## 并案必修：emit 双写点漏洞

`free_functions.h` 双写点：
- **预生成**（`emit_cpp.py:779-796`）：**零前向声明** ⇒ 单独 include **102 error** 至 C1003 截断
- **全量**（`825-855`）：正常

⇒ **任何 `filter_classes` 跑即留编译破坏态**（全量写在 `if free_funcs and not filter_classes` 内）

**结构修②必须做**（合并双写点为单一 `_emit_free_functions_header()`）

## 教训

1. **commit message 不得写未证的因果**（「C2653」半句误导）
2. **class/struct 键不一致 ≠ error**（只 warning）
3. **C2653 真因须逐条归因**（58 条分 5 族，0 条与 class/struct 相关）
4. **双写点是真实漏洞**（live 抓获 102 error）

## 关联

- **gotcha_dual_copy_table_divergence.md**（同型双副本分叉）
- **对抗复核**：`data/status/pending/review_class_struct.md`
