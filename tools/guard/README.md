# tools/guard — 管线并发守卫

只读、零依赖（只用 Python 标准库）。**不写 `data/`，不改 `pipeline/cli.py`，不改 `tools/r7_check/`。**

解决的问题：本仓多条卡可以同时动 annotation 与生成树，若在别人跑
`apply / export / codegen / probe / loop / census_struct_holes.py` 的中途去跑
`match` 或 `census`，读到的数字会被污染（obj 被重写、生成树短时缺文件、
语料/基线被另一条管线刷新），但**数字本身看起来完全正常**。

守卫的作用是在出数前后给一次明确判定：干净（0）/ 有并发（2）/ 守卫自己坏了（1）。

## 什么时候必须跑

| 时机 | 命令 |
|------|------|
| 跑 `pipeline/cli.py match` **前** | `python3 tools/guard/preflight.py` |
| 跑 `tools/census_struct_holes.py` **前** | `python3 tools/guard/preflight.py` |
| 拿到读数、准备写进报告/基线**前** | `python3 tools/guard/reading_guard.py --reading match --value "L1 196"`（或 `--reading census --value "hole_bytes 213151"`） |
| 落位提交（`git commit`）前 | `python3 tools/guard/preflight.py` |

两个脚本都可直接当命令用，也可 `python3 -m tools.guard.preflight`。

## 返回码契约

| rc | 含义 | 该怎么做 |
|----|------|----------|
| 0 | 干净：没有并发管线进程 | 可以出数、可以写基线 |
| 2 | 检测到并发占用 | **不得**把本次读数当基线，不得据此归因；等占用退出后重跑 |
| 1 | 守卫自身错误（读不到 /proc、解析异常等） | 读数同样不可信；先修工具或换机器 |

`reading_guard.py` 用同一套 rc，并额外打印 `baseline_allowed=true/false`。

## 输出长什么样

```
$ python3 tools/guard/preflight.py
[guard] DETECTED 并发占用 2 个（扫描 285 个进程）— 读数不可比（并发窗口），拒绝作为基线
[guard]   pid=445903 start=2026-11-28 01:21:54 matched=codegen cmd=timeout 1200 python3 pipeline/cli.py codegen all --skip-probe
[guard]   pid=448109 start=2026-11-28 01:24:21 matched=loop cmd=/usr/bin/python3 /tmp/demo/pipeline/cli.py loop
$ echo $?
2
```

```
$ python3 tools/guard/reading_guard.py --reading match --value "L1 196"
[guard] reading=match value="L1 196" verdict=not-comparable
[guard] reason=并发窗口（2 个占用进程）
[guard]   pid=445903 start=2026-11-28 01:21:54 matched=codegen cmd=...
[guard] baseline_allowed=false —— 不要写基线 / 不要据此归因，等并发退出后重跑
```

干净时：

```
[guard] OK 干净（扫描 285 个进程）— 未检测到并发管线，可以出数
```

## 检测规则（可核对，不看进程名猜）

命中任一条即算占用：

- `pipeline/cli.py` 且子命令 ∈ `apply | export | codegen | probe | loop`；
  兼容 `timeout 1200 python3 pipeline/cli.py ...` 这种前缀（看命令行 token，不看 `ps` 的列位置）。
- 任意路径下文件名是 `census_struct_holes.py` 的进程。

不算占用：`cli.py status`、`cli.py check`、`cli.py match`（默认）、编辑器、grep 等。
需要把**另一条 `match`** 也算占用时加 `--include-match`。

自身与自己的祖先进程永远排除（守卫在一条管线里被调用时不会把自己判成并发）。

## 与 `pipeline/cli.py status` 的分工

| 工具 | 回答的问题 |
|------|-----------|
| `pipeline/cli.py status` | 仓库**常量**状态：阶段顺序、三份基线对照、哪些门禁是已知恒红（TOLERATED） |
| `tools/guard/preflight.py` | 此刻**有没有别人在动管线**（实时进程占用） |

两者不替代：status 不知道谁在跑 codegen，guard 不知道 S2/L1 基线该是多少。

## 已知覆盖边界

守卫只能看见「进程」。它看不见：

- 别人把 `/tmp/pal3_probe` 清空后**已经退出**（没有进程可查，读数却已经坏了）；
- `git checkout` / 手工脚本 / 编辑器直接改 `data/annotations/`；
- 同一进程内部的竞态（比如 `loop` 自己的 apply 与 export）。

因此守卫的 rc=0 只表示「此刻没有并发管线进程」，不等于「当前读数一定干净」；
落位提交前仍应配合 `git status` 与生成树完整性检查（cpp/header 数量是否在正常量级）。

## 测试

```
python3 -m unittest tools.guard.test_guard -v   # 22 个用例，零依赖，不依赖真实并发
```
