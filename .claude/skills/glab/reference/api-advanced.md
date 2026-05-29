# glab api 高级用法

当 glab 内置命令无法覆盖需求时，`glab api` 可直接调用 GitLab REST API v4 和 GraphQL API。

---

## REST API

### 基本语法

```bash
glab api <endpoint> [--flags]
```

默认行为：无参数时使用 `GET`，有参数时使用 `POST`。通过 `-X` / `--method` 覆盖。

### 占位符

在 endpoint 中使用占位符，glab 会自动替换为当前仓库信息：

| 占位符 | 说明 |
|--------|------|
| `:id` | 项目 ID |
| `:fullpath` | 项目全路径（URL 编码） |
| `:branch` | 当前分支名 |
| `:repo` | 仓库名 |
| `:namespace` | 命名空间 |
| `:group` | 组名 |
| `:user` / `:username` | 当前用户名 |

### 传参方式

```bash
# -f / --raw-field：字符串参数
glab api projects/:id/issues -f title="Bug Report" -f description="Details"

# -F / --field：自动类型推断（true/false/null/数字 → 对应 JSON 类型）
glab api projects/:id/issues -F title="Bug" -F weight=5 -F confidential=true

# --input：从文件读取请求体
glab api projects/:id/issues --input body.json

# --form：multipart 上传文件
glab api projects/:id/wikis/attachments --form "file=@image.png"
```

### 分页

```bash
glab api projects/:id/members --paginate                # 自动遍历所有分页
glab api projects/:id/members --paginate --output ndjson # 逐行输出（节省内存）
```

### 输出格式

| 选项 | 说明 |
|------|------|
| `--output json` | 格式化 JSON（默认） |
| `--output ndjson` | 每行一个 JSON 对象，适合大数据集和 jq 处理 |
| `-i` / `--include` | 输出中包含 HTTP 响应头 |
| `--silent` | 不打印响应体 |

### 指定实例

```bash
glab api --hostname gitlab.example.com projects/1/issues
```

### 常用 REST 端点示例

```bash
# 项目
glab api projects/:fullpath
glab api projects/:id/members --paginate
glab api projects/:id/languages

# MR
glab api projects/:id/merge_requests?state=opened
glab api projects/:id/merge_requests/123/changes
glab api projects/:id/merge_requests/123/pipelines

# Issue
glab api projects/:id/issues?labels=bug
glab api projects/:id/issues/42/notes

# Pipeline / Job
glab api projects/:id/pipelines
glab api projects/:id/jobs/67890/trace

# 用户
glab api users?username=john

# 组
glab api groups/:group/projects --paginate

# 搜索
glab api projects/:id/search?scope=blobs -f search="TODO"
```

---

## GraphQL API

```bash
glab api graphql -f query="<GraphQL 查询>"
```

### 示例

```bash
# 当前用户
glab api graphql -f query="query { currentUser { username name email } }"

# 项目信息
glab api graphql -f query='
query {
  project(fullPath: "group/repo") {
    name
    forksCount
    statistics { wikiSize }
    issuesEnabled
    boards { nodes { id name } }
  }
}'

# 带变量
glab api graphql -f query='
query($path: ID!) {
  project(fullPath: $path) { name description }
}' -f path="group/repo"
```

### GraphQL 分页

查询必须接受 `$endCursor: String` 变量，并返回 `pageInfo { hasNextPage, endCursor }`：

```bash
glab api graphql --paginate -f query='
query($endCursor: String) {
  project(fullPath: "group/repo") {
    issues(first: 50, after: $endCursor) {
      edges { node { title state } }
      pageInfo { endCursor hasNextPage }
    }
  }
}'
```

---

## 与 jq 配合使用

```bash
# 获取所有 open MR 的标题
glab api projects/:id/merge_requests?state=opened --paginate --output ndjson | jq -r '.title'

# 统计每个用户的 MR 数量
glab api projects/:id/merge_requests?state=all --paginate --output ndjson | jq -r '.author.username' | sort | uniq -c | sort -rn

# 获取最近失败的 Pipeline
glab api projects/:id/pipelines?status=failed -F per_page=5 | jq '.[].web_url'
```

---

## 注意事项

- `--form` 不能与 `--field`、`--raw-field`、`--input` 同时使用
- MR Pipeline 类型的 `ci run` 不支持 `--variables` 系列参数
- `--paginate` 在 GraphQL 模式下要求查询包含 `$endCursor` 变量和 `pageInfo` 字段
- 项目路径中的 `/` 需要 URL 编码为 `%2F`（使用 `:fullpath` 占位符可自动处理）
