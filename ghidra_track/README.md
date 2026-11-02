# ghidra_track — 双轨验证轨（VERIFICATION-ONLY）

spec: docs/specs/2026-11-02-ghidra-dual-track-spec.md

结构：
  config/project.json    ghidra-reconstruct PAL3 配置（modules/typeOwnership）
  import_annotation.py   注解 JSON → Ghidra 转换层（本仓新核心件，TDD）
  tests/                 用例（mangled 真值锚）
  out/                   生成的丑 C（.gitignore）
  ghidra_proj/           派生 Ghidra 库（.gitignore，可弃件）

第三方（git submodule）：
  thirdparty/ghidra-reconstruct   生成器（quick 预设=可编译铁律档）
  thirdparty/ghidra-mcp           Ghidra 桥（local-worker stdio 模式）

铁律：VERIFICATION-ONLY · 不准确=不判定 · 零字节轨变更 · 失败即弃条件门
