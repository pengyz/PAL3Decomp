---
name: glab
description: |-
  通过 glab（GitLab 官方 CLI）在命令行管理 GitLab 全量资源：Merge Request、Issue、CI/CD Pipeline、仓库、Release、Label、Variable、Runner、Milestone、Token 等。
  触发条件（满足任一激活）：
  1. 用户提及 GitLab、MR、Merge Request、Pipeline、CI/CD、Issue（GitLab 语境）、glab；
  2. 要求创建/查看/合并/审批 MR，查看 Pipeline 状态，创建/管理 Issue，查看 Job 日志；
  3. 要求操作 GitLab 仓库相关资源：Release、Label、Variable、Runner、Schedule、Snippet、Milestone；
  4. 要求通过 glab api 直接调用 GitLab REST/GraphQL API；
  5. 用户主动要求"初始化 glab 环境"、"安装 glab"、"配置 glab 认证"、"设置 GitLab CLI"。
  强制规则：所有 GitLab 操作优先使用 glab CLI 完成，避免手动拼接 API 请求。执行任何 glab 命令前必须先完成【环境自检流程】，确认 glab 已安装且已认证。
---

# glab — GitLab CLI

所有操作格式：`glab <模块> <子命令> [参数] [--flags]`。常用入口：`glab mr list` 列出 MR、`glab ci status` 查看 Pipeline、`glab issue list` 列出 Issue。

模块总览：`mr` Merge Request · `issue` Issue · `ci` CI/CD Pipeline · `job` Job · `repo` 仓库/项目 · `release` 发版 · `label` 标签 · `variable` 变量 · `runner` Runner · `schedule` 定时调度 · `milestone` 里程碑 · `snippet` 代码片段 · `token` Token 管理 · `user` 用户 · `auth` 认证 · `config` 配置 · `api` 原始 API 调用

## 环境自检

执行任何 glab 命令前，快速完成以下两步检测：

**Step 1 — 检测安装：**

```bash
glab --version
```

- 输出版本号 → 已安装，继续 Step 2
- 命令未找到 → **读取 `reference/setup-guide.md` Part 1**，自动完成安装

**Step 2 — 检测认证：**

```bash
glab auth status
```

- 输出已登录账户信息 → 已认证，直接执行用户任务
- 输出 `No hosts configured` 或 `not logged in` → **读取 `reference/setup-guide.md` Part 2**，完成 Token 认证引导

---

## 全局约定

### 仓库上下文

glab 默认操作当前 Git 仓库对应的 GitLab 项目。如需操作其他仓库，使用 `-R` / `--repo` 参数：

```bash
glab mr list -R owner/repo
glab mr list -R group/namespace/repo
glab mr list -R https://gitlab.example.com/owner/repo
```

### 输出格式

多数命令支持 `-F json` 或 `--output json` 输出 JSON 格式，便于程序化处理：

```bash
glab mr list -F json
glab mr view 123 -F json
glab ci status -F json
glab issue list -O json
```

### 分页

列表类命令支持分页参数：

| 参数 | 说明 |
|------|------|
| `-p, --page` | 页码（默认 1） |
| `-P, --per-page` | 每页条数（默认 30） |

---

## Merge Request（mr）

### 创建 MR

```bash
glab mr create -t "标题" -d "描述" -b target-branch
glab mr create --fill --yes                    # 自动从 commit 填充标题和描述，跳过确认
glab mr create --fill --fill-commit-body --yes # 多个 commit 时用 commit body 填充描述
glab mr create --draft -t "WIP: 新功能"        # 创建 Draft MR
glab mr create -a username1,username2          # 指定负责人
glab mr create --reviewer user1,user2          # 指定审核人
glab mr create -l "bug,urgent"                 # 添加标签
glab mr create -s feature-branch -b main       # 指定源/目标分支
glab mr create --related-issue 42              # 关联 Issue
```

> `--fill` 会自动推送分支并使用 commit 信息填充 MR，适合快速创建。

### 列出 MR

```bash
glab mr list                                   # 当前项目所有 open MR
glab mr list --assignee=@me                    # 分配给自己的
glab mr list --reviewer=@me                    # 需要自己 review 的
glab mr list --merged                          # 已合并的
glab mr list --closed                          # 已关闭的
glab mr list --draft                           # Draft 状态的
glab mr list --label "bug"                     # 按标签筛选
glab mr list --source-branch feature           # 按源分支筛选
glab mr list --target-branch main              # 按目标分支筛选
glab mr list --search "关键词"                 # 按标题/描述搜索
glab mr list --author username                 # 按作者筛选
glab mr list --created-after "2025-01-01"      # 按创建时间筛选
glab mr list -F json                           # JSON 格式输出
```

### 查看 MR

```bash
glab mr view 123                               # 查看 MR 详情
glab mr view 123 --comments                    # 包含评论
glab mr view 123 --comments --resolved         # 仅已解决的讨论
glab mr view 123 --comments --unresolved       # 仅未解决的讨论
glab mr view 123 -F json                       # JSON 格式
glab mr view 123 --web                         # 在浏览器中打开
```

### 审查 & 合并

```bash
glab mr diff 123                               # 查看 MR 代码变更
glab mr diff 123 --raw                         # 原始 diff 格式（可管道处理）
glab mr approve 123                            # 审批通过
glab mr approve                                # 审批当前分支的 MR
glab mr revoke 123                             # 撤销审批
glab mr merge 123                              # 合并
glab mr merge 123 --squash                     # Squash 合并
glab mr merge 123 --rebase                     # Rebase 合并
glab mr merge 123 -d                           # 合并后删除源分支
glab mr merge 123 -m "合并说明"                # 自定义合并 commit message
glab mr rebase 123                             # Rebase 源分支
```

### 评论 & 讨论

```bash
glab mr note 123 -m "LGTM!"                   # 添加评论
glab mr note -m "请修改"                       # 评论当前分支的 MR
glab mr note list 123                          # 列出讨论
glab mr note resolve <discussion-id> 123       # 解决讨论
glab mr note reopen <discussion-id> 123        # 重新打开讨论
```

### 更新 & 管理

```bash
glab mr update 123 -t "新标题"                 # 修改标题
glab mr update 123 -d "新描述"                 # 修改描述
glab mr update 123 --ready                     # 标记为 Ready
glab mr update 123 --draft                     # 标记为 Draft
glab mr update 123 -a user1,user2              # 修改负责人
glab mr update 123 --reviewer user1            # 修改审核人
glab mr update 123 -l "feature,v2"             # 添加标签
glab mr update 123 -u "old-label"              # 移除标签
glab mr update 123 --target-branch develop     # 修改目标分支
glab mr checkout 123                           # 检出 MR 分支到本地
glab mr close 123                              # 关闭 MR
glab mr reopen 123                             # 重新打开 MR
glab mr delete 123                             # 删除 MR
glab mr subscribe 123                          # 订阅 MR 通知
glab mr todo 123                               # 添加到待办事项
```

### 查看审批人

```bash
glab mr approvers 123                          # 列出合格的审批人
```

---

## Issue

### 创建 Issue

```bash
glab issue create -t "Bug: 登录失败" -d "详细描述"
glab issue create -t "标题" -l "bug,P1" -a username
glab issue create -t "标题" -m "Sprint 1"      # 关联里程碑
glab issue create -t "标题" --due-date "2025-06-30"
glab issue create -t "标题" --linked-mr 123    # 关联 MR
glab issue create -t "标题" --confidential     # 保密 Issue
glab issue create --web                        # 在浏览器中创建
```

### 列出 Issue

```bash
glab issue list                                # 当前项目所有 open Issue
glab issue list --all                          # 包含关闭的
glab issue list --closed                       # 仅关闭的
glab issue list --assignee=@me                 # 分配给自己的
glab issue list --label "bug"                  # 按标签筛选
glab issue list --milestone "v1.0"             # 按里程碑筛选
glab issue list --search "关键词"              # 搜索
glab issue list --author username              # 按作者
glab issue list -O json                        # JSON 格式输出
```

### 查看 & 管理 Issue

```bash
glab issue view 42                             # 查看详情
glab issue view 42 --comments                  # 含评论
glab issue view 42 -F json                     # JSON 格式
glab issue view 42 --web                       # 在浏览器中打开
glab issue note 42 -m "已修复，请验证"         # 添加评论
glab issue update 42 -t "新标题"               # 修改标题
glab issue update 42 -l "wontfix"              # 添加标签
glab issue close 42                            # 关闭
glab issue reopen 42                           # 重新打开
glab issue delete 42                           # 删除
```

### Issue 看板

```bash
glab issue board view                          # 查看项目 Issue 看板
glab issue board create --name "Sprint Board"  # 创建看板
```

---

## CI/CD Pipeline（ci）

### 查看状态

```bash
glab ci status                                 # 当前分支 Pipeline 状态
glab ci status --branch main                   # 指定分支
glab ci status --live                          # 实时刷新直到 Pipeline 结束
glab ci status --compact                       # 紧凑视图
glab ci status -F json                         # JSON 格式
```

### 运行 Pipeline

```bash
glab ci run                                    # 在当前分支运行 Pipeline
glab ci run -b main                            # 指定分支
glab ci run --variables "KEY1:value1"          # 传入变量
glab ci run --variables-env "K1:V1,K2:V2"     # 多个环境变量
glab ci run --variables-file "KEY:filepath"    # 文件变量
glab ci run -f variables.json                  # 从 JSON 文件加载变量
glab ci run --mr                               # 运行 MR Pipeline
glab ci run --web                              # 在浏览器中打开
```

### 查看 Job 日志

```bash
glab ci trace                                  # 交互式选择 Job 查看日志
glab ci trace 224356863                        # 按 Job ID
glab ci trace lint                             # 按 Job 名称
glab ci trace lint -b main                     # 指定分支
```

### Pipeline 管理

```bash
glab ci list                                   # 列出 Pipeline
glab ci get                                    # 获取当前 Pipeline 的 JSON 详情
glab ci cancel                                 # 取消运行中的 Pipeline
glab ci delete 12345                           # 删除 Pipeline
glab ci retry 67890                            # 重试 Job
glab ci trigger 67890                          # 触发手动 Job
glab ci view                                   # 交互式查看/运行/追踪
glab ci lint                                   # 校验 .gitlab-ci.yml 语法
glab ci artifact main build                    # 下载 artifact
```

---

## 仓库/项目（repo）

```bash
glab repo view                                 # 查看当前仓库信息
glab repo view owner/repo                      # 查看指定仓库
glab repo list                                 # 列出仓库
glab repo search --search "keyword"            # 搜索仓库
glab repo clone owner/repo                     # 克隆仓库
glab repo clone -g my-group                    # 克隆整个组的仓库
glab repo create my-project                    # 创建新仓库
glab repo fork owner/repo                      # Fork 仓库
glab repo archive download                     # 下载仓库归档
glab repo contributors                         # 查看贡献者
glab repo members list                         # 列出项目成员
```

---

## Release

```bash
glab release list                              # 列出 Release
glab release view v1.0.0                       # 查看 Release 详情
glab release create v1.0.0                     # 创建 Release
glab release create v1.0.0 ./bin/*             # 创建并上传文件
glab release upload v1.0.0 ./dist/*            # 上传文件到已有 Release
glab release download v1.0.0                   # 下载 Release 文件
glab release delete v1.0.0                     # 删除 Release
```

---

## Label

```bash
glab label list                                # 列出标签
glab label create --name "bug" --color "#FF0000" --description "Bug 报告"
glab label edit --name "bug" --new-name "defect"
glab label delete --name "bug"
```

---

## Variable

```bash
glab variable list                             # 列出项目变量
glab variable get MY_KEY                       # 获取变量值
glab variable set MY_KEY "my_value"            # 设置变量
glab variable set MY_KEY "secret" --masked     # 设置遮蔽变量
glab variable update MY_KEY "new_value"        # 更新变量
glab variable delete MY_KEY                    # 删除变量
glab variable export                           # 导出所有变量
```

---

## Runner

```bash
glab runner list                               # 列出 Runner
glab runner jobs 12345                         # 查看 Runner 处理的 Job
glab runner assign 12345                       # 分配 Runner 到项目
glab runner unassign 12345                     # 取消分配
glab runner update 12345 --description "desc"  # 更新 Runner 信息
glab runner delete 12345                       # 删除 Runner
```

---

## Schedule（定时调度）

```bash
glab schedule list                             # 列出定时调度
glab schedule create --description "Nightly" --ref main --cron "0 2 * * *"
glab schedule run 123                          # 手动触发定时调度
glab schedule update 123 --cron "0 3 * * *"   # 更新调度
glab schedule delete 123                       # 删除调度
```

---

## Milestone（里程碑）

```bash
glab milestone list                            # 列出里程碑
glab milestone get --milestone-id 1            # 查看里程碑详情
glab milestone create --title "v2.0" --description "..." --due-date "2025-12-31"
glab milestone edit --milestone-id 1 --title "v2.0.1"
glab milestone delete --milestone-id 1         # 删除里程碑
```

---

## Snippet（代码片段）

```bash
glab snippet create -t "My Snippet" main.go   # 从文件创建
glab snippet create -t "My Snippet" -f main.go # 从 stdin 读取
```

---

## Token 管理

```bash
glab token list                                # 列出 Token
glab token create "deploy-token" --scopes api,read_registry --expires-at "2026-01-01"
glab token revoke "deploy-token"               # 撤销 Token
glab token rotate "deploy-token"               # 轮换 Token
```

---

## 原始 API 调用（api）

当 glab 内置命令无法满足需求时，可直接调用 GitLab REST 或 GraphQL API。

```bash
glab api projects/:fullpath/releases                           # GET 请求
glab api projects/:id/members --paginate                       # 分页获取
glab api -X POST projects/:id/issues -f title="新 Issue"       # POST 请求
glab api graphql -f query="query { currentUser { username } }" # GraphQL 查询
```

占位符自动替换：`:id` 项目 ID · `:fullpath` 项目全路径 · `:branch` 当前分支 · `:repo` 仓库名 · `:namespace` 命名空间 · `:group` 组名 · `:user` / `:username` 用户名

> 完整 API 用法和高级技巧：见 `reference/api-advanced.md`

---

## 配置管理（config）

```bash
glab config get host                           # 查看当前 GitLab 实例
glab config set host gitlab.example.com        # 设置 GitLab 实例
glab config set editor vim                     # 设置编辑器
glab config set browser firefox                # 设置浏览器
glab config set check_update false             # 关闭自动更新检查
glab config edit                               # 编辑配置文件
```

配置文件路径：`~/.config/glab-cli/config.yml`

---

## 实用技巧

### 跨项目操作

所有命令都支持 `-R` 指定其他仓库，无需切换目录：

```bash
glab mr list -R group/project
glab issue list -R group/project
glab ci status -R group/project
```

### Pipeline 故障排查流程

1. `glab ci status` 查看 Pipeline 整体状态
2. `glab ci status --live` 实时监控
3. `glab ci trace <job-name>` 追踪失败 Job 的日志
4. `glab ci retry <job-id>` 重试失败的 Job
5. `glab ci lint` 校验 `.gitlab-ci.yml` 配置

### MR 完整工作流

1. `glab mr create --fill --draft` 从 commit 创建 Draft MR
2. `glab mr update <id> --reviewer user1,user2` 指定审核人
3. `glab mr update <id> --ready` 标记为 Ready
4. `glab mr approve <id>` 审批通过
5. `glab mr merge <id> --squash -d` Squash 合并并删除源分支
