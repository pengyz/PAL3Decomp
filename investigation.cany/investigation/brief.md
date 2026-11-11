# Brief

**Question:** 按 PAL3Decomp 自有管线推进 PAL3.exe 反编译：修复上一批标注引起的 131/215 回归（33 个单元引用未声明的 dir_0），使 S2 编译单元数恢复并尽量提升。

**Purpose:** 继续项目已运行数月的反向工程管线（annotation → IDA apply → Hex-Rays export → codegen → 编译普查），本轮聚焦回归定位与修复。

**Targets:**
- /home/peng/workspace/PAL3Decomp
- original/PAL3.exe
- data/annotations/globals.json

**Constraints:**
- 不新建 app/，在工作区原地修改
- 不改 Craft Anything 自身记录
- 标注修改必须有二进制证据（A 级）
- 验证前必须跑 apply→export→codegen→probe 全链

**Done when:** S2 从 131/215 恢复到 140+，dir_0 未声明错误清零，改动提交并记录指标。
