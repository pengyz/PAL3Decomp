---
name: gotcha-globals-cpp-nondeterministic-order
description: globals.cpp 的行序每次生成都不同（多重集完全相同），所以它的 md5 永远在变 ⇒ 不能把它当 A-B-A 字节锚点，也不能用 md5 判「这个文件是否被改动」
type: gotcha
created: 2026-09-18
updated: 2026-09-18
status: active
sources: [session-2026-09-18]
---

**现象**：做 A-B-A 落地校验，用 `md5sum` 逐文件比对"落地前"与"落地后"的 `pal3/src`，
202 个文件中 **201 个逐字节相同、只有 `globals.cpp` 不同**。第一反应是"改动泄漏到了 globals"
或"归档快照不完整"。

**实测判定**：`globals.cpp` 的差异**只是行序**：

```
pre lines 2703   post lines 2703
same as multiset: True      <-- 多重集完全相同
same as sequence: False     <-- 只有顺序不同
only-in-pre: 0   only-in-post: 0
```

**为什么**：`globals.cpp` 由 `emit_cpp.py` 依据 `asm/pal3/ida_structs.json` 的 `_globals` + PE 二进制 +
CRT init data 生成（文件头自述）。这条链路上有**无序容器**被直接迭代（`set`/未排序的 dict key），
于是同一个输入集合可以产出不同顺序。**同一输入、两次运行，输出行序不同**——不是增量/缓存问题，
也不是任何一次改动造成的。

**影响（三条，都是踩过的）**：

1. **`md5` 不能当"这个文件是否变化"的判据**：任何基于 md5 的变更集都会被 `globals.cpp` 污染，
   制造一个假阳性。要么把它排除，要么按**多重集**比较。
2. **A-B-A 的"落地前内容归档"不要用 md5 代替内容**：只存 md5 时，一旦需要复核"到底改了什么"，
   而工作树已被重新生成（`codegen.py` 的 `cmd_clean()` 会 `shutil.rmtree(pal3/src)`），
   内容就永久丢了。归档整棵树（202 个 .cpp 只有几 MB）才是可复核的。
3. **`git status` / `git diff` 对 `pal3/src` 完全无效**：`.gitignore:125` 忽略 `pal3/src/`，
   `git ls-files pal3/src | wc -l` = 0 ⇒ 判别改动只能靠内容/md5/文件清单，不能靠 git。

**规避**：把 `globals.cpp` 当作**已知的非确定性产物**——校验脚本里显式标注它并按多重集比对；
其余 201 个文件可以用 md5 当强锚点（本次就是这样拿到 201/202 的）。
真正的修法是让生成端排序（`sorted()`）输出；在修之前，别依赖它的字节稳定性。