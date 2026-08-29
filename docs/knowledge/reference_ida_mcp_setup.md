---
name: ida-mcp-setup
description: mrexodia/ida-pro-mcp 装在独立 venv（~/.local/ida-mcp-venv，Python 3.11），headless idalib 模式常驻 127.0.0.1:13337，可交互查询二进制替代临时写 IDA 脚本
type: reference
created: 2026-08-29
sources: [session-2026-08-29]
---

安装位置：`~/.local/ida-mcp-venv`（独立 venv，因为 ida-pro-mcp 要求 Python >=3.11，系统 python 是 3.10）。启动命令：

```bash
source ~/.local/ida-mcp-venv/bin/activate
export IDADIR=/home/peng/ida-pro-9.1
nohup python -m ida_pro_mcp.idalib_supervisor --host 127.0.0.1 --port 13337 --unsafe > /tmp/ida_mcp_supervisor.log 2>&1 &
```

打开工作 IDB（服务重启后需要重新 open）：`idb_open` 工具传 `input_path` 指向 `original/PAL3.exe.i64`，返回的 `session_id` 后续所有工具调用都要带 `database` 参数。项目级 `.mcp.json` 已注册 server 名 `idapro`（避免和未来装的 IDA GUI 插件冲突）。

**DSH 原生接入（2026-08-29）**：`~/.dsh/profiles/web/cordis.patch.yml` 已 insert `@deepseek-ai/dsh-mcp-client` 实例（id `mcp-idapro`，transport `streamable-http`，url `http://127.0.0.1:13337/mcp`，`toolCallTimeoutMs: 120000`，`failOnStartupError: false`）。DSH 会话重启后工具以 `mcp__idapro__*` 命名原生可用，无需 curl。已用 headless profile + `--patch /tmp/idapro_patch.yml` 单发验证过端到端连通。注意 worker 默认 idle TTL 600s，闲置后第一次调用会报 `Worker ... not reachable`，重新 `idb_open` 即恢复；需要常驻时 `idb_open` 传大 `idle_ttl_sec`。

用途边界：这是辅助查询通道（反编译/xref/交叉引用等只读探索），不是标注提交的权威来源，annotation 数据流和证据分级规则不变。
