---
name: git-rev-path-needs-posix-separators
description: Windows 下 `git show HEAD:<path>` 传 WindowsPath 反斜杠路径 rc=128 "exists on disk, but not in 'HEAD'"；rev:path 树内路径必须 .as_posix()，症状像"文件内容读不出"
type: gotcha
created: 2026-11-03
sources: [session-2026-11-03 编码修复]
---

Windows 下 `git show HEAD:<path>`（`<rev>:<path>` 语法）传反斜杠路径（`str(pathlib.Path)` 的 Windows 形态）⇒ rc=128 `fatal: path 'data\...' exists on disk, but not in 'HEAD'`；同路径正斜杠形 rc=0。`git ls-tree` 的 pathspec 参数容忍反斜杠 ⇒ 文件列表正常、逐文件读全灭。

**为什么：** git 树内路径分隔符恒为 `/`；`<rev>:<path>` 的 path 部分**不做**平台归一（而 pathspec 参数在 Windows 会归一），反斜杠在树内是合法文件名字节 ⇒ 查找必失配。`str(WindowsPath)` 恰产反斜杠 ⇒ Windows-only 静默失效；Linux 上 `str(Path)` 即正斜杠，故原开发机无症状。症状（"N 个文件内容读不出"）极易误判成 git 坏或编码问题——2026-11-03 实测先误判为解码病灶，二次病灶层检查才定位。

**何时使用：** 任何把路径喂给 `git show`/`git cat-file` 等 rev:path 形命令的代码 ⇒ 必须 `.as_posix()`；工作区读取 `PROJECT_ROOT / posix_rel` 不受影响（Windows 文件 API 接受正斜杠）。实测案例：`tools/annotation_diff.py`（942 文件读不出即此因）。
