# S2 只编译不链接——LNK 族错误是全盲区

**type**: gotcha
**created**: 2026-10-16（reviewer 复核实证归档）
**实证案**: 验证阶梯 S1/S2（`pipeline/cli.py probe`）只做 **`/c` 单元编译**；「整程序能否链接」在 `pipeline/link_probe.py` 之前是**整体未知**。该探针（verification ladder step 3）把 S2 绿单元全量编 .obj 后交给 MSVC6 LINK.EXE 分类落点：**LNK2005（重复符号=跨 TU ODR 违规）· LNK2001/LNK2019（未解析外部=CRT 边界/extern 不符/缺定义）· LNK1104 等（环境）**，输出 `data/status/link_census.json`，把链接问题变成**单调收敛的计量**（unresolved/duplicate 计数）。

**为什么：** MSVC `/c` 编译的每个 TU 是封闭的——符号重复定义、extern 声明与定义不符、缺全局定义，这些在编译期**一概不触发**，只在链接期爆 LNK 族。因此「S2 绿单元数上升 / 总错误下降」**不能**外推为「更接近可运行程序」；同理 L1（字节匹配）也覆盖不了链接层（字节级对的函数照样可能符号解析不一致）。把编译成功当作整体成功是度量越界——S2 度量的是 TU 级语法/类型收敛，链接是另一层判据。

**何时使用：** ① 汇报/评估「S2 或总错误改善」时，若要宣称「程序更接近可运行」，必须补 link_probe 计量（`python3 pipeline/link_probe.py [--limit N]`，当场读 `link_census.json` 的 unresolved/duplicate 计数趋势）；② 出现 LNK2005 优先查跨 TU 重复定义（同名全局双定义/inline 滥用），LNK2001/2019 查 CRT 边界与 extern 不符（本仓「CRT 边界」核心困难第 1 条）；③ 别把 `compile_regression`/`regression_detector`（编译层闸）误当链接层证据——两者都只看编译结果。