# glab 环境安装与认证配置指南

当检测到 glab 未安装或未认证时，按以下步骤完成环境配置。

---

## Part 1 — 安装 glab

检测当前操作系统，**自动选择对应包管理器执行安装**，无需询问用户：

**Windows — 优先 winget，备选 scoop：**

```powershell
winget install GLab.GLab
```

若 winget 不可用则尝试：

```powershell
scoop install glab
```

**macOS — Homebrew：**

```bash
brew install glab
```

**Linux — 按发行版优先级自动选择：**

```bash
# Debian / Ubuntu
curl -fsSL "https://gitlab.com/gitlab-org/cli/-/releases/permalink/latest/downloads/glab_amd64.deb" -o /tmp/glab.deb && sudo dpkg -i /tmp/glab.deb

# Fedora / RHEL / CentOS
sudo dnf install -y glab

# Arch Linux
sudo pacman -S --noconfirm glab

# Alpine
sudo apk add glab

# 通用备选：Go install
go install gitlab.com/gitlab-org/cli/cmd/glab@main
```

安装完成后运行 `glab --version` 确认，若仍失败则告知用户并停止。

---

## Part 2 — Token 认证配置

> **安全原则：绝不向用户索取 token 的值。** 只告知用户在哪里获取 token，并给出需要用户自己在 shell 中执行的认证命令，由用户自行填入。

### 第一步：准备 Personal Access Token

提示用户：**如果已有可用的 Personal Access Token，可直接跳到第二步使用。**

若需要新建，向用户说明以下步骤（仅引导，不索取 token 值）：

1. 登录 GitLab Web → 右上角头像 → **Preferences** → 左侧 **Access Tokens**
2. 点击 **Add new token**
3. 填写名称（如 `glab-cli`），勾选权限范围：
   - 必选：`api`、`read_user`
   - 推荐加选：`read_repository`、`write_repository`
4. 点击 **Create personal access token**，**立即复制**生成的 token（页面刷新后不可再查看）

### 第二步：给出认证命令，让用户自行在 shell 执行

向用户提供以下命令（**用户需自行替换 hostname 并填入 token**）：

```bash
glab auth login --hostname your.gitlab.com
```

执行后按提示操作：
- 选择认证方式：**Token**
- 粘贴 Personal Access Token

> 以上命令由用户自己在 shell 中执行，AI 不参与 token 的传递过程。

### 第三步：验证认证结果

用户执行完认证命令后，运行以下命令确认：

```bash
glab auth status
```

输出中出现已登录账户信息即表示认证成功，可继续执行用户的原始任务。

> **故障排查**：若命令返回 `401 Unauthorized`，说明 token 权限不足或已过期，重新执行 `glab auth login`。环境变量 `GITLAB_TOKEN`、`GITLAB_ACCESS_TOKEN`、`OAUTH_TOKEN` 会覆盖存储的凭据，可通过 `echo $GITLAB_TOKEN` 检查是否有冲突。
