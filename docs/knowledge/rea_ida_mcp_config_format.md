# REA_IDA_MCP_CONFIG 配置格式定谳

**created**: 2026-10-21（4 轮排查定谳）

## 正确格式（envelope 形）

```json
{
  "mcpServers": {
    "ida-pro-mcp": {
      "type": "http",
      "url": "http://127.0.0.1:13337/mcp"
    }
  }
}
```

**⚠️ envelope 键必须是 `ida-pro-mcp`**（不是 `idapro`）—— rea schema 硬编码
（`rea-agents/dist/ida/IdaConfiguration.js:44`）：
```js
const envelope = z.object({ mcpServers: z.object({ "ida-pro-mcp": z.unknown() }) })
```

也支持**直接形**（无 envelope）：`{"url": "http://127.0.0.1:13337/mcp"}` 或
`{"command": "...", "args": [...]}`（stdio 形）。

## schema 约束

- `type`: 可选，"http" 或 "stdio"
- `url`: 须本地（localhost/127.0.0.1/[::1]）+ 无 URL 凭据
- `headers`: 可选 record
- `mode`: "attached" | "headless"，默认 attached
- `timeoutMs`: 默认 300000
- `.strict()` — **不许额外键**

## 4 轮排查的坑

1. **DSH 从 zsh 启动** ⇒ `.bashrc`/`.profile`（bash）配置无效，须 `.zshrc`/`.zprofile`
2. **`.bashrc` 非交互 return 守卫**（L11/17）⇒ export 须放文件**开头**
3. **envelope 键名** `idapro` ✗ → `ida-pro-mcp` ✓
4. **rea 进程缓存启动时 parse 态** ⇒ 改配置须重启 DSH

## 验证方法

```bash
cd ~/.npm/_npx/<rea>/node_modules/rea-agents
node --input-type=module -e "
import { readIdaConfiguration } from './dist/ida/IdaConfiguration.js';
console.log(JSON.stringify(readIdaConfiguration('/path/to/config.json')))"
# 期望 {"ok":true,"value":{...}}
```

## 副产品

`mcp__idapro__*` 工具**未注册**（DSH 只暴露 resources 不暴露 tools）—— 路径 B（rea IDA provider）绕过它。
