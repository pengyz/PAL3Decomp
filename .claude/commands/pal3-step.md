执行 PAL3.exe 反编译工作流的**一次**完整迭代（含强检查），完成后停止。

**前置参考**: 反编译时必须先阅读 `/pal3-patterns` 了解常见 IDA 输出模式的正确还原方式。

## 核心机制

**BFS 展开模型**: 实现一个函数 → 为其 callee 生成 stub → stub 注册为 call_graph 节点 → CMake 链接通过 → 下一轮取一个 stub 节点实现 → 继续展开。

**构建门控**: `cmake --build build/pal3` 必须链接出 PAL3.exe。所有符号必须有定义（真实实现或 stub 体）。

**Stub 规则**:
- Stub 放在该函数最终会被实现的正确源文件中（按 `suggested_source`）
- 每个 stub 必须在 `call_graph.json` 中注册为 `pending` 节点
- Stub 函数体为空实现（返回 0/NULL/void），仅满足链接

## 单次迭代流程

### Step 1: 选择目标

```bash
python tools/pal3_callgraph.py next
```

解析 JSON 输出获取: address, name, size, decomp_file, has_decomp, suggested_source

如果 frontier 为空，输出 "Frontier exhausted" 并停止。

### Step 2: 反编译

- 如果 `has_decomp=false`: 保留为 stub，标记 skipped，跳到 Step 5
- 读取 `decomp_file` 中的 decompiled_c
- 重写为可编译 C++ 代码:
  - 目标源文件由 `suggested_source` 决定（如 `gamebase/PAL3.cpp`）
  - 保持与 IDA 反编译相同的控制流结构
  - 匹配变量类型和声明顺序
- 如果是新文件:
  1. 在 `src/pal3/` 创建
  2. 将文件路径加入根 `CMakeLists.txt` 的 `PAL3_SOURCES`
- 将该函数的 stub（如果之前存在）替换为真实实现

### Step 3: 生成 Callee Stub

实现函数后，分析其所有外部依赖（extern 声明的函数和全局变量）。
对于每个未解析的符号：

1. **确定归属文件** — 通过 PDB `suggested_source` 或按类名推断
2. **生成 stub 定义** — 放入对应源文件
   - 函数 stub: 空函数体，返回类型匹配的零值
   - 全局变量 stub: 定义为对应类型的零初始化变量
   - 字符串常量: 定义为实际字符串值（从 IDA 获取）
3. **注册到 call_graph** — 每个 stub 函数调用:
   ```bash
   python tools/pal3_callgraph.py add <addr> --name <name> --size <size> --status stub --source <file>
   ```
   stub 节点自动成为 frontier 候选

如果目标文件不存在，创建并加入 CMakeLists.txt。

### Step 4: 字节对比

```bash
python tools/pal3_compare.py --compile src/pal3/<file>.cpp --func <name> --addr <addr> --size <size> --json-output
```

解析 JSON 判定: exact / equiv / mismatch / size_mismatch

### Step 5: 匹配度门控

| 结果 | 判定 | 后续动作 |
|------|------|----------|
| exact (100%) | PASS | 标记 matched |
| equiv (≥95%, 大小相同) | PASS | 标记 compiled |
| ≥90%, 大小相同 | 条件PASS | 标记 wip |
| <90% 或 size_mismatch | FAIL | 迭代修正直到通过 |
| 无 decomp / skipped | SKIP | 保留 stub |

修正策略:
- size_mismatch → 检查控制流结构、循环形式、变量声明
- <90% → 检查类型宽度、cast、调用约定

最多尝试 3 轮修正。如果仍不通过，标记 wip 并继续（不阻塞）。

### Step 6: 质量门控（匹配通过后）

**硬性要求 — 不通过不得提交：**

1. **禁止 IDA 变量名** — `v1`, `v2`... `v99` 必须全部替换为语义名称
   - 改名不影响字节匹配（同类型同作用域内）

2. **禁止无意义函数名** — 已实现函数禁止使用 `sub_XXXXXX`
   - extern 声明的未实现 stub 可暂时保留 `sub_XXXXXX`
   - 命名依据：函数行为、PDB 名称

3. **禁止裸偏移** — `*(DWORD*)(this + 0x1C)` → `this->m_pStage`

4. **禁止魔数** — `0x162D8` → `sizeof(CCBSystem)` 或命名常量

5. **gbengine 引用使用头文件** — 不允许 extern 前向声明 gbengine 导出

6. **源文件路径正确** — 必须按 `suggested_source` 放置

7. 重新对比确认未破坏匹配（如果破坏则回退质量修改）

### Step 7: 构建门控（CMake 链接）

```bash
cmake --build build/pal3
```

**成功标准: 链接出 PAL3.exe，无未解析符号。**

如果链接失败（unresolved externals）:
- 分析缺失符号
- 为每个缺失符号生成 stub（放入正确文件 + 注册 call_graph 节点）
- 重新链接直到通过

新增 .cpp 文件时必须同步更新根 `CMakeLists.txt` 的 `PAL3_SOURCES`。

### Step 8: 提交推送

```bash
python tools/pal3_callgraph.py validate
git add src/pal3/ CMakeLists.txt asm/pal3/call_graph.json
git commit -m "feat(pal3): decompile <FuncName> (0x<ADDR>) — <judgment>"
git push origin master
```

### Step 9: 输出摘要

```
═══ PAL3 Iteration Complete ═══
函数: <Name> (0x<ADDR>, <SIZE> bytes)
匹配: <judgment> (<rate>%)
构建: PASS (PAL3.exe linked)
推送: origin/master <hash>
Frontier: <before> → <after> (+<new> stubs)
═══════════════════════════════
```

## Stub 文件组织

Stub 放在最终实现该函数的源文件中：
- `src/pal3/gamebase/PAL3.cpp` — PAL3:: 系列方法的 stub
- `src/pal3/Combat/CBSystem.cpp` — CCBSystem 系列的 stub
- `src/pal3/globals.cpp` — 全局变量、字符串常量的定义

Stub 格式示例：
```cpp
// === STUB: 待实现 ===
void __cdecl PAL3::CreateGfxWindow(void) {}
void __cdecl PAL3::CheckSystemRequire(HINSTANCE hInst) {}
int __cdecl sub_53DF70(void) { return 0; }
```

全局变量/字符串常量示例：
```cpp
// === 全局变量定义 ===
extern "C" HWND hWnd = 0;
extern "C" int xRight = 0;
extern "C" const char aDatascriptComb[] = "data\\script\\combat";
```

## 注意事项

- **每个 stub 必须注册 call_graph 节点** — 这是 BFS 展开的核心
- CMakeLists.txt 中的源文件列表是根 CMakeLists.txt（不是 src/pal3/CMakeLists.txt）
- 编译器: VC6 SP0, 构建命令: `cmake --build build/pal3`
- 首次构建需要: `cmake -B build/pal3 -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake -DBUILD_TARGET=pal3`
- 对于 WinMain.cpp 中的函数：VC7.1 编译，字节对比仅作参考
- `pal3_compare.py` 仅用于单函数字节对比验证，不作为构建门控
