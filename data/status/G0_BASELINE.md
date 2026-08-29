# G0 基线（2026-08-29，HEAD 2ee9bd2dd + 多继承修复后的全量重跑）

三层信号首次同时可测。测量工具与产物：

| 层 | 工具 | 产物 |
|----|------|------|
| S1 头独立编译 | `pipeline/probe_compile.py`（/TP /c /W3, wine MSVC6, obj 假 OK 防护） | probe_census.json `s1` |
| S2 文件独立编译 | 同上 + own/imported 归因 | probe_census.json `s2` |
| S4 函数字节匹配 | `pipeline/compare_pal3.py`（COFF 提取 + vc6_mangler 匹配 + 原地址比对，reloc 不计） | s4_baseline.json, pal3_registry.jsonl |

## 数字

- **S1 = 308/746**。438 个失败的根因高度集中：头文件引用 `UINT`(740)/`BYTE`(602)/`_BYTE`(410) 等类型但独立编译时无定义——单一 codegen 前导 typedef 缺口，修复后 S1 预期接近满值。
- **S2 = 41/205**（与 codegen 内置 full-build 快照 41/206 独立吻合，交叉验证通过）。own-fail 163、imported-only 1（globals.cpp）。多继承 C2208 级联已消失（错误码 top8 无 C2208），剩余为 C2440(908)/C2664(617)/C2039(304)/C2065(287) 等类型保真问题，且错误都指向 cpp 自身——归因从"全项目级联"塌缩为"单文件自身"。
- **S4 = 0 L1 / 19 partial，覆盖 19/153 符号（41 个 pass 文件全部跑完）**。partial 匹配率 6-12%（Phase-1 未调优代码的诚实起点）。匹配率受限于 vc6_mangler 覆盖面：构造/析构 `?0/?1` 特殊名、静态成员 `__stdcall`（真实符号 'S'，mangler 表为 'G'）暂不产出——`__thiscall` 实例方法已验证逐字符正确。S4 真实分母待 mangler 扩展后上修。

## 与历史对照

full-build 口径：0/206（6-27 快照）→ **41/206**；历史峰值 48/185（5 月底）。字节匹配此前从未有过分层测量，本日为 S4 首版基线。

## 复跑方式

```bash
python3 pipeline/cli.py apply && python3 pipeline/cli.py export && python3 pipeline/cli.py codegen all
python3 pipeline/probe_compile.py        # S1+S2
python3 pipeline/compare_pal3.py         # S4（依赖 probe_census.json 的 s2 通过名单）
```
