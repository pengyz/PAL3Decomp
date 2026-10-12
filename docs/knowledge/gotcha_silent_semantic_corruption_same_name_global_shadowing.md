# gotcha · 同名全局遮蔽 = 静默语义腐蚀（字节级不可见）

**type**: gotcha
**created**: 2026-10-13（T20 发现，T21 扩批）
**confidence**: high（Block 案实证 + 同族顺带 2 行验证）

## 一句话
**丢 this 参数时若不改名体内引用，引用会落到同名全局 ⇒ 语义腐蚀**（`delete`/`return` 到全局而非对象）—— **编译通过、错误数不变、字节匹配可能虚高，但行为错了**。

## Block 案实证（T20）
```
stage1_structural.py:210-231 的 this-param 剥离段
  —— 只删首参、不改名体内引用
  ⇒ 引用落到同名全局（globals.h:334 extern void * Block; // 0x00D8E470）
  = 语义腐蚀（delete Block / return Block 到全局！）
```
**A 级证据**：register 16 = ECX 槽 ⇒ `__thiscall` this。

## 🔥 为什么这是最危险形态
| 形态 | 可见性 |
|---|---|
| 编译失败 | ✅ 可见（错误数涨）|
| 布局错 | ✅ 可见（audit 报冲突）|
| **语义腐蚀** | ❌ **字节级不可见** —— 编译通过、错误数不变、L1 可能虚高 |

**⇒ 这是「测试绿证据力为 0」的最极端形态**：
- 若不修，字节匹配可能在**错误的语义**上通过
- 或 Phase 2 手工 fix 时才暴露（成本更高）

## 修法（T20，已通吃该族）
1. **丢参时同步 AST 标识符逐个改名→`this`**（跳过成员/限定访问/声明位）
2. **stage3 补三形守卫**（dtor+delete+return）—— 防止改名暴露「显式 ctor/dtor 噪声」清理误吃真调用

## 通用风险面
**凡丢参不改名的 this 槽函数都可能静默绑错** —— T20 修法顺带清 2 行即证（同族）。

## 检查方法
```bash
# 找同名全局（this 槽名与全局名重合）
grep -n "extern .* <Name>;" pal3/src/**/globals.h
# 对照 decomp JSON 里该函数的首参名
```

## 相关
- T20 修法：`pipeline/gen/stages/stage1_structural.py` + `stage3_cleanup.py` 三形守卫
- 「测试绿证据力为 0」：`gotcha_wiring_type_changes_test_green_is_zero_evidence.md`
