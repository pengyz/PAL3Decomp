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

## 修法（T20）——⚠️ 2026-10-13 T22/T23 限缩：「已通吃该族」**过度**
（T22 F3：dtor 路径 params[1+] 被裸丢 ⇒ 两活体 0x00411BD0/0x00541710 静默腐蚀）
1. **丢参时同步 AST 标识符逐个改名→`this`**（跳过成员/限定访问/声明位）
2. **stage3 补三形守卫**（dtor+delete+return）—— 防止改名暴露「显式 ctor/dtor 噪声」清理误吃真调用
3. **[T23-F1] dtor 路径 params[1+] 保留**（flags 形参是真栈实参，A 级
   `test BYTE PTR [esp+0x8],0x1`）—— 原「strip all params」裸丢即 F1 blocker

## 通用风险面（⚠️ 口径限定，T22 F2 教训）
**凡丢参不改名的 this 槽函数都可能静默绑错** —— T20 修法顺带清 2 行即证（同族）。

### 口径限定（T22 F2 更正）
- ✅ **可声称**：「9 个 this 槽函数体内 `Block` 引用 0」（scoped grep 逐字：对
  9 个单元各跑 `grep -n '\bBlock\b' <unit>.cpp`，各自 0 命中）
- ✅ **可声称**：「丢参名 × globals.h 同名裸引用 = 0」（精确 scoped 判据）
- ❌ **不可声称**：宽泛「全树 `\bBlock\b` 残留 0」——实测全树 191 处（均良性：
  形参/局部/成员名），**不可复现的口径=无效声称**
- **纪律**：零残留类声称必须附**可复现的精确命令**（含作用域）

### 清点（T23 ③：三形守卫的语义判定挂账）
- 语料中 stage3「显式 ctor/dtor 噪声」清理形命中集：**647 行**独立 ctor/dtor
  调用形（原始 decomp `~` 形 0 行——dtor 形经 T11 改写后才出现）。
- 三形守卫只护删除析构族；**非删除 dtor 的显式 `X::~X()` 调用仍可被清理形
  误吃**（T22 F3）⇒ 语义判定挂账，勿再扩三形清单式打补丁。

## T17 结论口径（T22 F4）
「误归属→vptr→全员漂移 **0 例**」≠「归属错 **0 例**」——漂移型 0 ✓ 但存在
真归属错 **2 例**（UIPostUpdate / SceneRenderWithRotation），已入挂账单
（ROI 4 位）。

## 检查方法
```bash
# 找同名全局（this 槽名与全局名重合）
grep -n "extern .* <Name>;" pal3/src/**/globals.h
# 对照 decomp JSON 里该函数的首参名
```

## 相关
- T20 修法：`pipeline/gen/stages/stage1_structural.py` + `stage3_cleanup.py` 三形守卫
- 「测试绿证据力为 0」：`gotcha_wiring_type_changes_test_green_is_zero_evidence.md`
