---
name: binary-alignment-iteration
description: 二进制对齐迭代 - 对 gbengine.dll 已实现函数逐批进行字节对比，修正不匹配，编译验证，发现并实现缺失函数。每次调用执行一个完整迭代。
---

# 二进制对齐迭代 (Binary Alignment Iteration)

## 目标

对 gbengine.dll 的已实现函数进行字节级匹配验证，逐步修正直到所有函数达到"等价匹配"。

## 核心原则

1. **不信任已有结果** — 每次都重新跑字节对比
2. **等价匹配即可** — 寄存器分配差异可接受，逻辑必须一致
3. **编译驱动** — 修正过程中自然发现缺失函数，实现之
4. **批量+验证** — 每修正一批（~10个）就编译验证

## 单次迭代流程

```
1. 选择一个源文件 (按优先级: 小文件优先, 匹配率低优先)
2. 运行字节对比: python tools/gbengine_compare.py --compile src/gbengine/XXX.cpp --all
3. 对每个不匹配函数:
   a. 读取 IDA 反编译 (asm/gbengine_ida/)
   b. 对比当前实现与 IDA 输出
   c. 判断差异类型:
      - 逻辑错误 → 修正实现
      - 缺失调用 (调用了我们没实现的函数) → 实现缺失函数
      - 寄存器分配差异 → 标记为"等价匹配"
      - Size MISMATCH → 必须修正 (逻辑结构不同)
   d. 修正代码
4. 每修正 ~10 个函数, 编译验证:
   cd /home/peng/workspace/PAL3Decomp/build && make -j$(nproc)
5. 修复编译错误 (如有)
6. 重新对比验证修正后的匹配率
7. 更新 registry 记录匹配状态
```

## 匹配状态分类

在 registry 中通过 note 字段记录:

| 状态 | 含义 | 判定标准 |
|------|------|----------|
| `match:exact` | 字节完全匹配 | 100% match |
| `match:equiv` | 等价匹配 | Size OK, 仅寄存器分配/指令顺序差异, 逻辑等价 |
| `match:partial` | 部分匹配 | 有实质性差异但不影响正确性 |
| `match:wrong` | 需要修正 | 逻辑错误或缺失调用 |

## 判断"等价匹配"的标准

以下差异可接受为等价:
- 寄存器选择不同 (如 eax vs ecx)
- push/mov 顺序不同但效果相同
- lea vs add 等等价指令替换
- 局部变量在栈上的偏移不同

以下差异必须修正:
- Size MISMATCH (函数体大小不同)
- 调用了不同的函数
- 控制流结构不同 (if/else 逻辑不同)
- 常量值不同
- 缺少对其他函数的调用

## 工具命令

```bash
# 对比单个文件所有函数
python tools/gbengine_compare.py --compile src/gbengine/XXX.cpp --all

# 对比特定函数 (详细)
python tools/gbengine_compare.py --compile src/gbengine/XXX.cpp --func "FunctionName" -v

# 编译验证
cd /home/peng/workspace/PAL3Decomp/build && make -j$(nproc)

# 读取 IDA 反编译
cat asm/gbengine_ida/FUNCNAME_addr.json | python3 -c "import sys,json; d=json.load(sys.stdin); print(d['decompiled_c'])"

# 更新 registry 匹配状态
python tools/registry.py mark 0xADDR done --note="match:exact"
python tools/registry.py mark 0xADDR done --note="match:equiv"
```

## 选择文件的优先级

1. 函数少 (快速完成)
2. 当前匹配率低 (改进空间大)
3. 有已知的 IDA 反编译参考
4. 被其他文件依赖 (修正后可能暴露更多缺失)

## 迭代结束条件

一次迭代在以下条件满足时结束:
- 至少处理了一个完整源文件
- 所有修改后编译通过
- 新发现的缺失函数已实现或记录

## 输出格式

每次迭代结束时报告:
```
文件: XXX.cpp
总函数: N
修正前: X/N 匹配 (Y%)
修正后: X'/N 匹配 (Y'%)
新实现: [列出新实现的函数]
等价标记: [列出标记为 equiv 的函数]
仍需修正: [列出仍不匹配的函数]
编译状态: PASS/FAIL
```
