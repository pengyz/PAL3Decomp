# 同一逻辑表双副本并存会静默分叉（表修一漏一）

**type**: gotcha
**created**: 2026-10-16（reviewer 复核实证归档）
**实证案**: `_GB_REF_PARAM_FUNCS` / `_fix_ref_params` 在 `pipeline/gen/stages/stage3_cleanup.py:2222/2256` 与 `pipeline/gen/stages/stage5_fixup.py:564/664` **双副本并存**；2026-10-14「B 修补条」在 stage5 侧把 `GetAABBox` 裸键拆成限定键 `gbOBBox::GetAABBox`，**stage3 副本未同步** ⇒ 两表键级分叉至今（当场实测：stage3 键 30 / stage5 键 34 / 交集 29；仅 stage3 有 `GetAABBox`，仅 stage5 有 `GetBlend`/`SetBlend`/`RightMultiply`/`PointWorldToScr`/`gbOBBox::GetAABBox`，**分叉键合计 6**）。R15 测试 `pipeline/gen/test_ref_param_table_b.py` 只 `from stage5_fixup import _GB_REF_PARAM_FUNCS`——**单侧防护**，stage3 副本漂移零覆盖。

**为什么：** 逻辑表/映射在两个 stage 各存一份时，修表动作天然是「点状」的——修者看着眼前的副本改，另一份没有红线提醒、没有测试盯着，分叉后两侧渲染行为静默不一致（同一调用形在 stage3 路径和 stage5 路径得到不同改写），且**编译/字节指标都不会报警**（两份各自"自洽"）。本仓已有同型教训：codegen 注解直读多点散落（CLAUDE.md「单一读点」条款，现存 3 处直读未清），以及 test 影子副本突变杀 0 实证（`test_struct_value_cast_fix.py` 头注：「import 生产函数——影子副本教训：本地副本突变杀 0/5」）。修一漏一是**结构性**风险，不是粗心问题。

**何时使用：** ① 任何「同一张表/同一段改写逻辑出现在 ≥2 个模块」的场景（grep `= {` 同名常量、同名 `_fix_*` 函数）——要么收敛到单一读点/单一实现（export_full 头部 `[t4-DECLARED-EXCEPTION]` 的处置先例），要么建**双侧一致性测试**（断言两份键集相等）；② 修表/改映射类补丁落地前，必须 `grep -rn "<表名>" pipeline/` 找全副本并同改（R13 变体：补丁落地 grep 核实应含**副本数核对**）；③ R15 写测试时 import **生产函数**（禁影子副本），且若生产物有双副本，测试必须双侧各断言一份。

**诊断命令（复算本文数字）：**
```bash
python3 -c "
import re
def keys(f):
    b=re.search(r'_GB_REF_PARAM_FUNCS\s*=\s*\{(.*?)\n\}', open(f).read(), re.S).group(1)
    return set(re.findall(r\"'([\w:]+)'\s*:\s*\{\", b))
k3=keys('pipeline/gen/stages/stage3_cleanup.py'); k5=keys('pipeline/gen/stages/stage5_fixup.py')
print(len(k3), len(k5), len(k3&k5), sorted(k3-k5), sorted(k5-k3))"
```
