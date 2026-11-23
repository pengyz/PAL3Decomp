# PAL3 反编译项目

**目标**：从 PAL3.exe（MSVC 6.0 SP0）重建字节一致的 C++ 源码（L1 字节匹配为验收硬线）。

## 管线（唯一真相链）

```
data/annotations/（标注=唯一真相源）
  → pipeline apply   （注入 IDB：命名+类型+结构）
  → export           （Hex-Rays 语料 asm/pal3/decomp/）
  → codegen          （生成 pal3/src/ 生成树，含 include/pal3/gen/ 头镜像）
  → probe            （MSVC6 编译普查，S2 读数）
  → match            （编译产物 vs 原 exe 字节对拍，L1 棘轮）
```

日常入口：`python3 pipeline/cli.py loop`（五阶段全链）；门禁：`python3 pipeline/check_annotations.py`。

## 当前读数（2026-11-23）

- S2 编译单元 160/233 ok（fail 73）· L1 字节匹配 181 · check 13 警告（起点 210）

## 模块导览

| 目录 | 用途 | 版控 |
|---|---|---|
| `pipeline/` | 管线代码（check/apply/export/codegen/probe/match + 门禁） | tracked |
| `data/annotations/` | **标注真值层**（structs/functions/globals/skip + schema/allowlist 族） | tracked |
| `data/status/` | 运行状态对账层（棘轮基线+裁决台账+pending 队列） | tracked(latest) |
| `asm/` | IDB 工作区+Hex-Rays 语料（管线工作数据） | gitignored |
| `pal3/` | 生成树 src/（codegen 覆盖，gitignored）+ CMake | src gitignored |
| `include/` | pal3/gen 头镜像（生成）+ gbengine 头 | 混合 |
| `modules/` | PAL3 姊妹 DLL 模块（topo/gbengine 手动维护源码+def） | tracked |
| `lib/` `cmake/` | 构建辅助（ijl15 链接件 / 工具链配置） | tracked |
| `original/` | 原始游戏输入（PAL3.exe 等，只读） | 部分跟踪 |
| `thirdparty/` | 外部子模块（ghidra-mcp/ghidra-reconstruct/pal3-redivivus B面研究线/PAL3patch 参考） | submodule |
| `tools/` | 工具箱（审计/取证/构建辅助脚本 + MSVC6/Ghidra 工具链） | 脚本 tracked |
| `experiments/` | 实验线（ghidra_track 双轨验证——VERIFICATION-ONLY） | tracked |
| `tests/` `docs/` | 测试与知识库 | tracked |
| `build/` | CMake 产物 | gitignored |

## 纪律（2026-11-23 目录治理后）

- **平行手写层已全部退役**（phase2 overlay / manual / src_fake / src_error / stubs）——修复只走 annotation 层，禁直改 pal3/src（codegen 覆盖）
- **KEYCASE 门**：在用 JSON 十六进制字面量一律小写规范形（check 强制）
- **status 生命周期**：活基线/台账入白名单跟踪；运行输出→`pipeline/_logs/`；一次性调查→`data/status/archive/`
- `*.obj` 与编译实验残物不入库（.gitignore 在册）
