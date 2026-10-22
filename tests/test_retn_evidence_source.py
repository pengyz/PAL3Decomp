"""指令级 retn 证据源的回归测试。

背景（2026-09-18 定谳）：`ast_transform` 原先只用**裸字节扫描**找函数尾 `retn`
（在原始字节里搜 `0xC2`/`0xC3`），会把**指令操作数里的**同值字节当成函数尾。
实测对 3395 个注解方法：3178 个能在 `original/PAL3.exe.asm` 里做指令级取值，
其中与裸扫描**分歧 367 个（11.6%）**，幅度极大
（`Actor::LoadActorModel` 指令级=4 而裸扫描=420 ⇒ 105 个假 slots）。

修法：以 asm 指令级为主源，裸扫描仅作回退，并上报来源分布。

本测试**不编码 annotation 状态**：它断言的是"缓存里的值必须等于对不可变
`PAL3.exe.asm` 做独立指令级读取的结果"这一**不变量**，以及几个属于二进制事实
（retn 立即数）的取值。
"""
import pytest
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "tools", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

import ast_transform as at  # noqa: E402

ASM = PROJECT_ROOT / "original" / "PAL3.exe.asm"


def _annotated_methods():
    """(cls, method, va) 列表 —— 与 _load_ret_slots 的输入集合同源。"""
    import glob, json, os
    out = []
    for f in sorted(glob.glob(str(PROJECT_ROOT / "data/annotations/structs/*.json"))):
        d = json.load(open(f, encoding="utf-8"))
        cls = d.get("name") or os.path.basename(f)[:-5]
        for a, m in (d.get("methods") or {}).items():
            try:
                out.append((cls, str(m.get("name", "")), int(a, 16)))
            except ValueError:
                continue
    return out


def test_evidence_is_asm_dominant_and_reported():
    """主源必须是指令级 asm；裸扫描只能是被计数的回退。"""
    # 触发加载
    at._ret_param_slots("AStarPathFinder", "IsInBounds")
    stats = at._ASM_SRC_STATS
    assert stats["asm"] > 2500, stats
    assert stats["byte"] < 600, stats          # 回退面必须小
    assert stats["asm"] + stats["byte"] + stats["none"] > 3000, stats


@pytest.mark.slow(reason="asm 读取 — 集成测试非 UT")
def test_cached_values_agree_with_independent_asm_read():
    """不变量：缓存值 == **另一套独立实现**（tools/sig_evidence.rets_of_asm）
    对同一份 asm 做指令级读取的结果/4。暴露两套读取实现的分歧。"""
    import sig_evidence as se
    at._ret_param_slots("AStarPathFinder", "IsInBounds")
    cache = at._RET_SLOTS_CACHE
    checked = mism = 0
    # 镜像 loader 语义：同名方法可能标注在多个地址上，loader 只用**第一个**
    # 出现的地址（`if (cls, mn) in _RET_SLOTS_CACHE: continue`），故这里也要去重，
    # 否则会拿另一个地址的真值去比、产生假分歧（实测 CCBRoleState::CheckMP
    # 同时标注在 0x004DF3D0 与 0x004EE910）。
    first = {}
    for c, m, va in _annotated_methods():
        first.setdefault((c, m), va)
    cand = [(c, m, va) for (c, m), va in first.items() if (c, m) in cache]
    step = max(1, len(cand) // 150)          # 抽样：避免逐条重开 18MB 文件
    for cls, meth, va in cand[::step]:
        rets, err = se.rets_of_asm(va)
        if err or not rets or len(set(rets)) != 1:
            continue
        checked += 1
        want = rets[0] // 4 if rets[0] % 4 == 0 else None
        if cache[(cls, meth)] != want:
            mism += 1
    assert checked >= 80, checked
    assert mism == 0, "两套指令级实现分歧 %d / %d" % (mism, checked)


def test_byte_scan_error_cases_are_now_instruction_accurate():
    """曾经被裸扫描读错的实例，现在必须是指令级真值（二进制事实，非注解状态）。"""
    for cls, meth, want in (
        ("Actor", "LoadActorModel", 1),   # 裸扫描曾给 105
        ("Actor", "SetVisible", 3),       # 裸扫描曾给 0
        ("Actor", "InsertAction", 2),     # 裸扫描曾给 0
        ("AStarPathFinder", "GetHeuristicIdx", 2),
    ):
        got = at._ret_param_slots(cls, meth)
        assert got == want, (cls, meth, got, want)


def test_h_suffix_is_parsed_as_hex_not_decimal():
    """retn 的多位立即数必须按十六进制读（`20h`=32 ⇒ 8 slots，不是 5）。"""
    at._ret_param_slots("AStarPathFinder", "IsInBounds")
    assert at._parse_retn("retn 20h") == 32
    assert at._parse_retn("retn 10h") == 16
    assert at._parse_retn("retn 0Ch") == 12
    assert at._parse_retn("retn 8") == 8
    assert at._parse_retn("retn") == 0
    assert at._parse_retn("mov eax, 1") is None
    assert at._parse_retn("retn 0x20") is None   # 非 asm 清单写法


def test_asm_source_declines_when_rets_disagree():
    """多个不一致的 retn ⇒ 无证据（保守），不得随便取一个。"""
    # AStarPathFinder::IsInBounds 真值唯一（retn 8）
    assert at._ret_param_slots("AStarPathFinder", "IsInBounds") == 2
    # 未注解/不存在的方法必须给 None 而不是 0
    assert at._ret_param_slots("NoSuchClass", "NoSuchMethod") is None


if __name__ == "__main__":
    tests = [v for k, v in sorted(globals().items()) if k.startswith("test_")]
    failed = 0
    for t in tests:
        try:
            t()
            print("  ✅ %s" % t.__name__)
        except AssertionError as e:
            print("  ❌ %s: %s" % (t.__name__, e))
            failed += 1
        except Exception as e:
            print("  ⚠️  %s: %s" % (t.__name__, e))
            failed += 1
    print("\nResults: %d passed, %d failed" % (len(tests) - failed, failed))
    sys.exit(1 if failed else 0)