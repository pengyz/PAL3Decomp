# Gotcha: 全局命名冲突 → dir_0 C2065 级联（2026-11-11 investigation.cany 结案迁移）

## 病灶
0x583A9C（串池首串 "fivemagic"）标注名 `dir` 与 0x58B44C（"role"）的 IDB 名 `dir` **撞名**：
IDA 实落 `dir_0`，globals.h 发 `dir` ⇒ 33 个单元报 C2065 'dir_0'（级联 C2109/C2102），
S2 131/215 回归。

## 修复
改为唯一名 `aFivemagic` 后全链验证：S2 141/215、总错 800、dir_0 C2065 归零。

## 律
- 全局命名必须全局唯一——标注名与 IDB 自动名（IDA 撞名加 `_0` 后缀的消歧形）之间的
  错位是 C2065 的隐蔽源；撞名查证用「标注名 vs IDB 实落名」双账对比。
- 串池条目命名走 `a<Literal>` 惯例（IDA 字符串数组惯例），不用语义词。

证据原档：investigation.cany/investigation/{brief,findings,handoff}.md（2026-11-23 清理退役，
evidence 哈希链见 craft-anything 会话存档 ~/.config/）。
