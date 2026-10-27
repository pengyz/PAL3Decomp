# PAL3.exe FDS 迁移工作表（逐函数 + 对拍）

## 工作流

```
1. 选函数（按层优先）
2. 从 codegen 迁移（pal3/src/...）
3. 编译验证（bash manual/pal3/build.sh）
4. L1 对拍（python3 tools/pal3_callgraph_comprehensive.py check）
5. 确认语义一致（>=95%）+ 字节一致（100%）
6. 标记完成
```

## 优先级

**N=0（WinProc）> N=1（33 个）> N=2（427 个）**

## 工作表

### N=0（1 个）

| # | 地址 | 符号 | 状态 | 语义 | 字节 | codegen 参考 |
|---|---|---|---|---|---|---|
| 1 | 0x00541900 | WinMain | pending | - | None | pal3/src/... |

### N=1（33 个）

| # | 地址 | 符号 | 状态 | 语义 | 字节 | codegen 参考 |
|---|---|---|---|---|---|---|
| 1 | 0x541d75 | func_0x541d75 | mock | - | None | pal3/src/... |
| 2 | 0x555290 | func_0x555290 | mock | - | None | pal3/src/... |
| 3 | 0x541d10 | func_0x541d10 | mock | - | None | pal3/src/... |
| 4 | 0x554670 | func_0x554670 | mock | - | None | pal3/src/... |
| 5 | 0x546f41 | func_0x546f41 | mock | - | None | pal3/src/... |
| 6 | 0x553082 | func_0x553082 | mock | - | None | pal3/src/... |
| 7 | 0x5382d0 | func_0x5382d0 | mock | - | None | pal3/src/... |
| 8 | 0x542059 | func_0x542059 | mock | - | None | pal3/src/... |
| 9 | 0x541860 | func_0x541860 | mock | - | None | pal3/src/... |
| 10 | 0x55353b | func_0x55353b | mock | - | None | pal3/src/... |
| ... | ... | ... | ... | ... | ... | ... |

### N=2（427 个）

| # | 地址 | 符号 | 状态 | 语义 | 字节 | codegen 参考 |
|---|---|---|---|---|---|---|
| 1 | 0x4038f0 | func_0x4038f0 | mock | - | None | pal3/src/... |
| 2 | 0x401810 | func_0x401810 | mock | - | None | pal3/src/... |
| 3 | 0x404300 | func_0x404300 | mock | - | None | pal3/src/... |
| 4 | 0x404310 | func_0x404310 | mock | - | None | pal3/src/... |
| 5 | 0x5536a9 | func_0x5536a9 | mock | - | None | pal3/src/... |
| 6 | 0x403b80 | func_0x403b80 | mock | - | None | pal3/src/... |
| 7 | 0x404380 | func_0x404380 | mock | - | None | pal3/src/... |
| 8 | 0x404060 | func_0x404060 | mock | - | None | pal3/src/... |
| 9 | 0x553549 | func_0x553549 | mock | - | None | pal3/src/... |
| 10 | 0x4042d0 | func_0x4042d0 | mock | - | None | pal3/src/... |
| ... | ... | ... | ... | ... | ... | ... |

## 进度追踪

| 层 | 总数 | 已迁移 | 语义一致 | 字节一致 |
|---|---|---|---|---|
| N=0 | 1 | 0 | 0 | 0 |
| N=1 | 33 | 0 | 0 | 0 |
| N=2 | 427 | 0 | 0 | 0 |

## 工具

- **编译**：`bash manual/pal3/build.sh`
- **L1 对拍**：`python3 tools/pal3_callgraph_comprehensive.py check`
- **codegen 参考**：`pal3/src/**/*.cpp`
