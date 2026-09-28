# 类型源分裂——同名双猜型器造 redefinition 族

事实：同一名字的声明若由**两个独立启发式**产出，会造出整族 redefinition 错误：
本仓 globals.h 侧 `_prefix_type`（byte_→'unsigned char'）与 TU 就地 extern 的自带
前缀链（byte_→'char'）不一致 ⇒ C2371 `different basic types`；另一侧把 windows.h
typedef（LPCSTR）当未知类名发 `class LPCSTR;` 前向声明 ⇒ C2040 `overloaded function
type differs in levels of indirection`。修复后净消 ≈34 错（C2040×25+C2371×4+C2440×4）。

**为什么：** 声明一致性要求**同一解析函数**；类型拼写还有"typedef vs class"语义陷阱
（全大写名是 typedef 惯例，不能 class 前向声明）。数字型名（`_DWORD[1]` 数组型 type）
在发射路径上还须拆 `[N]` 后缀到名字后（`_DWORD x[1];`——非 POD 路径曾漏拆 ⇒ C2143）。
空串 name/键形差异（见另两则 gotcha）是同族病：**消费侧规范化必须跨层同公式**。

**何时使用：** 新增任何"按名字/前缀猜类型"的代码前——先查既有权威源
（globals.json 注解型 → ida_structs 导出型 → 前缀启发**仅作最后回退**）并复用同一
解析函数；验证法：同名声明在 globals.h 与 TU 侧拼写逐字一致（相容重复声明无错）。
诊断入口：C2040/C2371/C2511 族聚类出现时，先找双猜型器而非逐条改类型。
