# codegen 的「产出集」必须记录实际写盘，不能从类名反推

**created**: 2026-10-20
**实证案**: `pipeline/gen/stages/emit_headers.py` 头文件清理判据两次修错，引发 S2 121→0

## 事故时间线

1. **原判据错**：`if should_skip_class(stem)` 只清「类被跳过」的文件，不清
   「已不在产出地址」的文件 ⇒ 旧版双址镜像的 `include/pal3/*.h`（795 个）
   在产出地址迁移到 `include/pal3/gen/` 后**永不清理** ⇒ 同一类三副本并存
   （`include/pal3/X.h` 旧·class / `include/pal3/gen/X.h` shim / `pal3/src/Misc/X.h` canonical）
   ⇒ 2026-10-20 三副本分叉实测引发 S2 121→0。
2. **修法又错**：改判据为「本次未产出的 .h 一律清掉」，产出集从
   `all_classes ∪ enum_names` 反推 ⇒ **漏了模板实例化桩**（tmpl 路径产出的
   `CTaskTpl_tagEffTaskParam__unsigned_long____thiscall_CEffgbParticle_____unsigned_long__.h`）
   ⇒ 被当 stale 删 ⇒ **C1083 ×214** 全线打不开头文件，S2 121→0 再现。
3. **处置**：判据回退保守形（`should_skip_class`），旧址孤儿改用**手动清理**
   （`include/pal3/*.h` 795→4，保留 `ida_defs.h`/`ida_types.h`/`pal3_constants.h`/`pal3_stl.h`）。

## 根因（通用规律）

codegen 的产出**路径不止一条**。本仓实测 5 条：

| 路径 | 产出者 | 易漏？ |
|---|---|---|
| 类头 | `generate_header` 主循环 | 否 |
| 枚举头 | enum 循环 | 否 |
| **模板实例化桩** | tmpl 循环（`tmpl_count`）| **是**（不在 `all_classes`）|
| `globals.h` | `generate_globals()` | 是 |
| `_ns_udts.h` | ns-decl 共享头写出 | 是 |

**从类名集合反推产出集必然漏**——只有**记录每次 `write_text`/`open(...,'w')` 的目标**
才是完整产出集。

## 防复发约定

1. **产出集 = 实际写盘集合**：每次写文件时把 `path` 加入 `_produced`，清理时只删
   不在 `_produced` 里的。禁止用「类名/枚举名集合」反推。
2. **清理前必须有安全阀**：产出集为空（异常路径）时**不得**执行删除
   （本次若无此阀会全删 `pal3/src`）。
3. **基础设施头白名单**：`ida_defs.h` / `ida_types.h` / `pal3_constants.h` /
   `pal3_stl.h` / `globals.h` / `_ns_udts.h` 是手写/特殊产出，永不删。
4. **产出地址迁移要清旧址**：改输出目录时必须显式清理旧地址
   （本次 795 个孤儿就是迁移遗留）。
5. **动手清理前先查引用面**：`grep -rho '#include "pal3/[^"]*\.h"'` 确认哪些被引用
   （本次实测 1204 处引用全是 4 个基础设施头 ⇒ 删除类头安全）。

## 核对命令

```bash
# 三址产出规模
python3 -c "
import os
for d in ('include/pal3','include/pal3/gen','pal3/src'):
    print(d, sum(len([f for f in fs if f.endswith('.h')]) for _,_,fs in os.walk(d)))"

# 引用面（删除前必查）
grep -rho '#include "pal3/[^"]*\.h"' pal3/src/ | grep -v 'pal3/gen/' | sort -u

# 缺失头检查
python3 -c "
import os,re,glob
refs=set()
for fp in glob.glob('pal3/src/**/*.cpp',recursive=True)+glob.glob('pal3/src/**/*.h',recursive=True):
    refs|=set(re.findall(r'#include\s+\"([^\"]+\.h)\"', open(fp,encoding='utf-8',errors='replace').read()))
have={f for d in ('pal3/src','include') for r,_,fs in os.walk(d) for f in fs if f.endswith('.h')}
print('引用但缺失:', sorted({r for r in refs if os.path.basename(r) not in have})[:10])"
```

## 关联

- 同型风险：[gotcha_dual_copy_table_divergence.md](gotcha_dual_copy_table_divergence.md)
  （逻辑表双副本分叉）—— 本条是**文件副本**维度的同构问题。

## 【2026-10-20 查证更正】"隐性依赖"假说是**测量错误**，撤回

初判：删除 `include/pal3/*.h` 791 个副本后，`include/pal3/gen/` 的 shim 裸名 include
（`#include "tagEffTaskParam.h"`）会断链，说明那 791 个副本在"承担 include 解析兜底"。

**查证结果：假说不成立，撤回**：
1. 我的计数用了 `os.walk` **递归**，把 `include/pal3/gen/`（835 个）算进了
   `include/pal3/`（看起来 839）⇒ 误以为"删了又长回来"。精确顶层计数：
   `include/pal3/*.h` = **4**（仅 ida_defs/ida_types/pal3_constants/pal3_stl）⇒
   删除 791 个类头**正确且完整**。
2. shim 的裸名 include 实际解析到**同目录** `include/pal3/gen/<name>.h`（shim 侧同名件），
   不依赖 `include/pal3/` 顶层 ⇒ 无隐性依赖。
3. S2=121→0 的真因是**清理判据**删了 `pal3/src/Misc/` 的模板桩，与 `include/pal3/`
   删除无关（两件事被我混为一谈）。

**教训（计数口径）**：统计某目录的产出规模时，**必须区分顶层 vs 递归**；
`os.walk` 会把子目录（如 `gen/`）算进来，导致"删了又长回来"的假象。

残留的真实观察（非缺陷）：`include/pal3/gen/` shim 用**裸名 include**
（`#include "tagEffTaskParam.h"`）依赖同目录同名件 —— 目前可用，但若未来清理
`include/pal3/gen/` 会连锁断链。清理该地址时需一并检查。

---

## 【2026-10-20 追加】假型批量降级 typedef 路线**不可行**（两次尝试均净负，停用）

**尝试**：把 annotation `_verdicts` 判为"误挂"的空壳型批量降级为 `typedef int X;`
（`SaleUI_SortData`/`gbMeshData`/`collision`/`gbVolumeModifier` 等，期望消 C2440 36 条）。

**两次结果**：
| 轮 | 判据 | 结果 |
|---|---|---|
| 1 | 凡 `_verdicts` 含"误挂" | ❌ S2 121→0（C2371 ×368 + C2504 ×214）—— **误伤 `Parent_Data`/`Iostream_init`** |
| 2 | 只认定谳（排除"待终审"）| ❌ 净负（C2440 −2 但 S2 121→120、总错误 +5）|

**根因（为什么批量降级不可行）**：
1. **"误挂待终审"≠定谳** —— `Parent_Data` 带待审标记但**是真类型**（`Parent_Data *` 指针用）；
   任何按 verdict 批量处置都必须先区分「定谳」与「待审」。
2. **即使定谳也不保证可降级** —— 类型可能在某些用法上需要类语义
   （作基类/有成员访问/被 `->` 解引用），`typedef int` 会破坏那些用法。
3. **判定的语义是"名字来源可疑"，不是"可以用标量替代"** —— 两者是不同的命题。

**结论（决策）**：假型真型化**必须逐条做**（每条要二进制证据确认其真实角色），
**禁止批量降级**。这与 CLAUDE.md「禁止批量修改未验证字段」是同一条铁律的另一面。

**若仍要做**，前置检查清单（缺一不可）：
- [ ] 该名在全仓的**全部用法**已枚举（值成员/指针/基类/模板实参/强转）
- [ ] 每种用法在 `typedef int` 下都语义等价
- [ ] 无同名前向声明（`class X;`）
- [ ] 无 SDK 头（gbengine/）同名定义
- [ ] 跑全链（apply→export→codegen→probe）且 **S2 不降、总错误不增**
