执行 PAL3.exe 反编译工作流的**一次**完整迭代（含强检查），完成后停止。

**前置参考**: 反编译时必须先阅读 `/pal3-patterns` 了解常见 IDA 输出模式的正确还原方式。

## 单次迭代流程

### Step 1: 选择目标

```bash
python tools/pal3_callgraph.py next
```

解析 JSON 输出获取: address, name, size, decomp_file, has_decomp

如果 frontier 为空，输出 "Frontier exhausted" 并停止。

### Step 2: 反编译

- 如果 `has_decomp=false`: 标记 skipped，展开 callees，跳到 Step 6
- 读取 `decomp_file` 中的 decompiled_c
- 重写为可编译 C++ 代码:
  - 确定目标源文件（按类名分组，如 PAL3::Create → PAL3_Create.cpp）
  - 添加必要的 extern 声明、#include
  - 保持与 IDA 反编译相同的控制流结构
  - 匹配变量类型和声明顺序
- 如果是新文件，在 `src/pal3/` 创建

### Step 3: 字节对比

```bash
python tools/pal3_compare.py --compile src/pal3/<file>.cpp --func <name> --addr <addr> --size <size> --json-output
```

解析 JSON 判定: exact / equiv / mismatch / size_mismatch

### Step 4: 匹配度门控

| 结果 | 判定 | 后续动作 |
|------|------|----------|
| exact (100%) | PASS | 标记 matched，继续 |
| equiv (≥95%, 大小相同) | PASS | 标记 compiled，继续 |
| ≥90%, 大小相同 | 条件PASS | 标记 wip，继续 |
| <90% 或 size_mismatch | FAIL | 迭代修正直到通过 |

修正策略:
- size_mismatch → 检查控制流结构、循环形式、变量声明
- <90% → 检查类型宽度、cast、调用约定

最多尝试 3 轮修正。如果仍不通过，标记 wip 并继续（不阻塞）。

### Step 5: 质量门控（匹配通过后）

**硬性要求 — 不通过不得提交：**

1. **禁止 IDA 变量名** — `v1`, `v2`, `v3`, `v4`, `v5`... `v99` 等必须全部替换为有语义的名称。
   - 根据用途推断：循环变量→`i/j/k`，指针→`pXxx`，返回值→`result`，临时中间值→描述其含义
   - 改名不影响字节匹配（同类型同作用域内）
   - 例外：只有当变量确实无法推断语义时，可以用 `tmp` 或 `unused`

2. **禁止裸偏移** — `*(DWORD*)(this + 0x1C)` 必须改为 `this->m_pStage` 形式
   - 在类声明中定义正确偏移的成员变量

3. **禁止魔数** — `0x162D8` 应为 `sizeof(CCBSystem)` 或命名常量

4. **gbengine 引用使用头文件** — PAL3 调用 gbengine.dll 的函数/类时：
   - 使用 `#include` 引用 `include/gbengine/` 下的头文件
   - 不允许在 .cpp 中用 `extern "C"` 前向声明 gbengine 的导出函数
   - 如果头文件不存在，先创建对应头文件再 include

5. **源文件路径正确** — 必须使用 `suggested_source`（来自 PAL3A PDB）指定的路径
   - 同一个类的多个方法放在同一个 .cpp 文件中

6. 重新对比确认未破坏匹配（如果破坏则回退质量修改）

### Step 6: 强检查

**CHECK 1: 全量编译**

```bash
python tools/pal3_compare.py --compile-all
```

必须所有文件编译通过。如果失败，修正编译错误直到通过。

**CHECK 2: BFS 节点更新**

```bash
python tools/pal3_callgraph.py update <addr> --status <status> --match-rate <rate> --source <path>
python tools/pal3_callgraph.py expand <addr>
python tools/pal3_callgraph.py validate
```

**CHECK 3: 提交推送**

```bash
git add src/pal3/<files> include/<files> asm/pal3/call_graph.json
git commit -m "feat(pal3): decompile <FuncName> (0x<ADDR>) — <judgment>"
git push origin master
```

### Step 7: 输出摘要

```
═══ PAL3 Iteration Complete ═══
函数: <Name> (0x<ADDR>, <SIZE> bytes)
匹配: <judgment> (<rate>%)
构建: PASS
推送: origin/master <hash>
Frontier: <before> → <after> (+<new> callees)
═══════════════════════════════
```

## 注意事项

- 每个函数必须独立编译（每个 .cpp 文件包含自己的 extern 声明）
- 新创建的源文件名格式: `<ClassName>_<Method>.cpp` 或 `<module>.cpp`
- 优先保持 IDA 控制流结构不变，只修改类型和变量名
- 编译器: VC6 SP0 (/O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MD /Gd)
- 对于 WinMain.cpp 中的函数使用 VC7.1 编译（已在注释中标明）
