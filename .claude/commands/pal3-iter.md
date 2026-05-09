持续执行 PAL3.exe 反编译迭代，直到 frontier 耗尽或被中断。

## 核心机制

**BFS 展开模型**:
```
实现函数 → 生成 callee stub（注册 call_graph 节点） → CMake 链接 PAL3.exe → commit+push
→ 取下一个 stub 节点 → 实现它 → 生成新 stub → 链接 → commit+push → 循环
```

**数据结构**:
- 调用图: `asm/pal3/call_graph.json` — BFS 节点（实现+stub）
- 游标: `.claude/pal3_cursor.json` — 迭代进度
- 迭代日志: `.claude/pal3_iterations/NNNN.json`

## 构建门控

```bash
cmake --build build/pal3
```

**成功标准: 链接出 PAL3.exe。** 所有符号必须有定义（真实实现或 stub 体）。

首次需配置: `cmake -B build/pal3 -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake -DBUILD_TARGET=pal3`

## 主循环

```
while (frontier 非空):
    1. 读取/创建游标
    2. 执行完整迭代:
       a. 选择目标 (python tools/pal3_callgraph.py next)
       b. 反编译 (读取 decomp JSON → 重写为 C++，替换 stub)
       c. 生成 callee stub (为所有未解析依赖生成 stub + 注册 call_graph 节点)
       d. 字节对比 (python tools/pal3_compare.py --compile ...)
       e. 匹配度门控
       f. 质量门控
       g. 构建门控 (cmake --build → 链接 PAL3.exe)
       h. commit + push
    3. 写入迭代日志
    4. 更新游标 (iteration_count++, stats)
    5. 输出迭代摘要
    6. 继续下一个
```

## Stub 规则

**每加一个 stub，都必须在 call_graph 中注册为节点：**

```bash
python tools/pal3_callgraph.py add <addr> --name <name> --size <size> --status stub --source <file>
```

Stub 放在该函数最终会被实现的正确源文件中（按 PDB `suggested_source`）。

Stub 格式：
```cpp
// === STUB: 待实现 ===
void __cdecl PAL3::CreateGfxWindow(void) {}
```

全局变量/字符串常量放在 `src/pal3/globals.cpp`：
```cpp
extern "C" HWND hWnd = 0;
extern "C" const char aDatascriptComb[] = "data\\script\\combat";
```

## 门控规则

### 匹配度门控

| 结果 | 判定 | 后续动作 |
|------|------|----------|
| **exact** (100%) | PASS | 标记 matched |
| **equiv** (≥95%, 大小相同) | PASS | 标记 compiled |
| **≥90%, 大小相同** | 条件通过 | 标记 wip |
| **<90% 或 Size MISMATCH** | FAIL | 尝试修正(最多3轮)，仍失败标记 wip |
| **无 decomp** | SKIP | 保留 stub，标记 skipped |

### 质量门控（硬性要求，不通过不得提交）

1. **禁止 IDA 变量名** — v1/v2/v3... 必须替换为语义名称
2. **禁止无意义函数名** — 已实现函数禁止 `sub_XXXXXX`
3. **禁止裸偏移** → 结构体成员 `this->m_field`
4. **禁止魔数** → 命名常量/sizeof/enum
5. **gbengine 引用使用头文件** — 不允许 extern 前向声明 gbengine 导出
6. **源文件路径** — 必须按 PDB suggested_source 放置
7. 重新对比确认未破坏匹配

### 构建门控

```bash
cmake --build build/pal3
```

链接出 PAL3.exe，无 unresolved externals。失败时补充 stub 直到通过。

## 迭代记录

每次迭代完成后写入 `.claude/pal3_iterations/NNNN.json`：

```json
{
  "iteration": 1,
  "timestamp_start": "...",
  "timestamp_end": "...",
  "duration_minutes": 46,
  "function": {
    "name": "PAL3::InitGFX",
    "address": "0x00404FF0",
    "size": 786,
    "status": "wip|matched|compiled",
    "match_rate": 0.258,
    "compiled_size": 573
  },
  "exe_size": { "before": 16384, "after": 16896, "delta": 512 },
  "bfs_nodes": { "before": 56, "after": 60, "added": ["0x..."] },
  "frontier": { "before": 47, "after": 50 },
  "changes": [...]
}
```

更新 `.claude/pal3_cursor.json` 中的 iteration_count、exe_size、stats。

## 每次迭代完成后输出

```
═══ PAL3 Iteration #N (Xm Ys) ═══
函数: <Name> (0x<ADDR>, <SIZE> bytes)
匹配: <judgment> (<rate>%)
构建: PASS — PAL3.exe <SIZE> bytes (+<DELTA>)
推送: origin/master <hash>
BFS: <total_before> → <total_after> 节点 (+<new_count> new)
Frontier: <before> → <after>
═══════════════════════════════
```

## 跳过策略

以下情况保留 stub 并继续（不阻塞 BFS）:
- `has_decomp=false` — 无反编译数据
- 函数 size ≤ 5 bytes — 太小，可能是 thunk/jump
- 3轮修正仍 <90% 且 size_mismatch — 结构性问题，待后续处理

## Workaround 记录

如果在迭代中发现严重问题但暂时用 workaround 绕过（如：gbengine 函数不在 .lib 中需要本地 stub、结构体偏移不确定用 `_pad` 占位、调用约定与 IDA 标注不一致等），**必须**记录到 `.claude/pal3_workarounds.md`：

```markdown
## [地址] 函数名 — 问题描述
- **问题**: gbEffectMgr::NewRenderEffect 不在 gbengine.lib 导出表中
- **Workaround**: 在 GfxHelper.cpp 中提供空 stub 实现
- **影响**: 运行时该函数返回 NULL，不会创建渲染效果
- **正确修复**: 确认该函数是否通过 IAT 导入或 vtable 间接调用，生成正确的 .lib
- **迭代**: #15
```

每次 `/pal3-verify` 时会检查此文件并尝试修复已记录的 workaround。

## CMakeLists.txt 维护

根 `CMakeLists.txt` 中 `PAL3_SOURCES` 列表必须包含所有源文件：
```cmake
set(PAL3_SOURCES
    src/pal3/WinMain.cpp
    src/pal3/gamebase/PAL3.cpp
    src/pal3/Combat/CBSystem.cpp
    src/pal3/globals.cpp          # 全局变量+字符串常量
    # ... 随 BFS 展开添加新文件
)
```

新增文件时同步更新此列表。

## 全局变量交叉引用 (xref)

在实现函数时遇到全局变量，用 xref 命令管理：

```bash
# 查询变量（按名称/地址/类型模糊搜索）
python tools/pal3_callgraph.py xref g_pGfxManager
python tools/pal3_callgraph.py xref 0x00BFDA60
python tools/pal3_callgraph.py xref gbGfxManager

# 列出所有已注册全局变量
python tools/pal3_callgraph.py xref --list

# 注册新全局变量
python tools/pal3_callgraph.py xref --add 0x00BFDA6C --name g_nGameState --type int --ida-name dword_BFDA6C

# 重命名
python tools/pal3_callgraph.py xref --rename 0x00BFDA6C --name g_nGameState

# 修改类型
python tools/pal3_callgraph.py xref --retype 0x00BFDA6C --type "enum GameState"

# 添加引用关系
python tools/pal3_callgraph.py xref --add-ref 0x00BFDA6C --ref-func 0x004055D0
```

每次实现新函数时，识别到的全局变量都应注册/更新 xref。

## PAL3A PDB 类型参考

`asm/pal3a/pdb_export.json` 含 1057 个类的完整成员定义，可用于命名参考：

```python
import json
d = json.load(open('asm/pal3a/pdb_export.json'))
for c in d['classes']:
    if c['name'] == 'TargetClass':
        for m in c['data_members']:
            print(f"+0x{m['offset']:04X} {m['type']} {m['name']}")
```

**PAL3A ≠ PAL3**: 偏移量可能不同！必须从 PAL3.exe 二进制验证。
- 成员**名称和类型** → 可直接用于命名
- **偏移量** → 以 PAL3.exe 反汇编中的 `[ecx+XX]` 为准
- 两者冲突时以二进制为准

## 注意事项

- **每个 stub 必须注册 call_graph 节点** — 这是 BFS 展开的核心路径
- **每个全局变量引用必须注册 xref** — 这是类型推断的数据基础
- **类成员偏移以 PAL3.exe 二进制为准** — PDB 仅供命名参考
- 不要中断，持续运行直到 frontier 耗尽
- 每次迭代必须完成强检查（链接+call_graph更新+commit+push）
- 迭代日志和游标不提交到 git
- `pal3_compare.py` 仅用于单函数字节对比，不作为构建门控
