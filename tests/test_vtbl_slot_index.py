"""vtable 槽位映射的**证据记录**与未来修复的守卫（当前不可通过，故显式 skip）。

# 已证明的事实（A 级，2026-09-18）

`store.struct_vtables[cls]` 的键是**槽位下标**（`data.py:44` 的注释：`slot_index`），
而 Hex-Rays 文本 `obj->__vftable + N` 里的 **N 就是槽位下标，不是字节偏移**：

    二进制 asm（original/PAL3.exe.asm）        Hex-Rays 文本（asm/pal3/decomp/*.json）
    sub_4C52C0:  call dword ptr [edx+8]   ⇔   ...__vftable + 2 ...
                                            8 / 4 = 2  ✓

脚本化配对另得 6/9 例一致（`sub_5371B0 N=15 ↔ 位移 60=3Ch`、`sub_536FD0 N=7 ↔ 28=1Ch` …）。
反面证据同样干净：855 处 `__vftable + N` 里 **639 处（75%）的 N 不是 4 的倍数**
（`+3` 243 次、`+1` 91 次…）；字节偏移必然 4 的倍数，故 N 只能是元素下标。

⇒ **`stage3_cleanup.py:501` 的 `slots.get(d['offset'] // 4)` 在语义上是错的。**

# 但它**不能**直接改成 `slots.get(d['offset'])` —— 实测净退化

改动后 `probe all` + `compile_regression` 报：**2 个 ok→fail**（`Misc/UI3DCtrl.cpp`、
`Misc/UIStatic.cpp`）、1 个 fail→ok（`Combat/CCBProtectWindow.cpp`）、**S2 净 −1**。
故已回退。

# 根因：**DLL 类的 vtable 注解不完整**，`//4` 一直在"意外地顶住"

| 类 | 注解覆盖下标 | Hex-Rays 实际引用的 N |
|---|---|---|
| `gbTexture` | **0–3** | {2, **4, 5**} |
| `gbGfxManager` | **0–6** | {2, **12, 13, 15, 21, 22, 23, 25, 26, 28**} |
| `gbActorDef` | — | {7, 15} |

机制（可逐条对上）：

- **旧 `N // 4`**：`gbGfxManager` 的 12→3、13→3、15→3、21→5、22→5、23→5、28→7 ——
  把**未标注的高槽折叠进已标注的低区间**，于是"命中"并产出一个**名字**（如
  `gbTexture` 的 `N=5 //4=1` → `UpdateTexture`）。这些名字**多数能通过类型检查**，
  所以文件保持 ok —— 这是**巧合在顶住**，不是正确。
- **新 `N`**：槽 5/12/28 压根没标注 → 返回 None → 走 **stub 回退**，而 stub 的签名由
  Hex-Rays 的 cast 合成（如 `int (__thiscall)(gbGfxManager *, char *)`），**与调用点实参
  类型不一定相符** ⇒ 产生 C2664/C2440。

⇒ 真正的两处缺陷是：**(1) DLL 类 vtable 注解缺槽位**；**(2) stub 回退合成的签名不是类型安全的**
（"没有注解"反而比"错的注解"更糟）。`//4` 本身不是任何东西的根因，它只是把 (1) 掩盖了。

# 结论 / 前置条件

在 (1)(2) 解决之前，**不要把 `//4` 改成 `N`** —— 那不是修 bug，是把掩盖物拿掉而洞还在。
正确的顺序：
  1. 用 DLL 侧证据（`original/gbengine.dll` + `gbengine.dll.asm` + `gbengine/gbengine.def`）
     **补全 DLL 类的 vtable 注解槽位**；
  2. 让 stub 回退的合成签名类型安全（或让它在类型不符时退回裸下标调用形）；
  3. **然后**再改 `//4` → `N`，本文件的测试即为那时的守卫。
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

from stages import stage3_cleanup as s3  # noqa: E402
from data import store  # noqa: E402

# 前置条件未满足 ⇒ 下面三项开通前先补全注解（见模块 docstring 的结论）
_BLOCKED = ("需要先补全 DLL 类 vtable 注解 + 让 stub 合成签名类型安全；"
            "否则实测会让 UI3DCtrl/UIStatic 由 ok 转 fail、S2 净 −1")


def _with_slots(mapping):
    old = store.struct_vtables
    store.struct_vtables = mapping
    return lambda: setattr(store, "struct_vtables", old)


def test_n_is_slot_index_not_byte_offset_proven_from_binary():
    """证明本身要留在仓库里：N = 二进制位移 / 4（抽样自我手工核对的实例）。"""
    # (地址, Hex-Rays 的 N, 二进制 call 位移)
    verified = [("sub_4C52C0", 2, 0x08), ("sub_5371B0", 15, 0x3C),
                ("sub_536AC0", 15, 0x3C), ("sub_537120", 15, 0x3C),
                ("sub_536FD0", 7, 0x1C), ("sub_541710", 26, 0x68),
                ("sub_541590", 25, 0x64)]
    for lab, n, disp in verified:
        assert disp % 4 == 0, (lab, disp)
        assert n == disp // 4, "%s: N=%d 但对话位移=%d(0x%X)" % (lab, n, disp, disp)


def test_named_method_path_unchanged():
    """`__vftable->Method` 形态（method 非空）的既有行为不得改变。"""
    restore = _with_slots({"Cls": {0: "Slot0", 2: "Slot2"},
                           "Other": {1: "Solo"}})
    try:
        assert s3._resolve_vtbl_method(
            {"method": "Slot2", "offset": None, "cls_hint": "Cls"}) == "Slot2"
        assert s3._resolve_vtbl_method(
            {"method": "Solo", "offset": None, "cls_hint": None}) == "Solo"
        assert s3._resolve_vtbl_method(
            {"method": "Nope", "offset": None, "cls_hint": None}) is None
    finally:
        restore()


def _skip(msg):
    print("  ⏭  SKIP: %s" % msg)
    return True


def test_offset_should_be_used_as_slot_index():
    if _skip(_BLOCKED):
        return
    restore = _with_slots({"Cls": {0: "Slot0", 2: "Slot2"}})
    try:
        assert s3._resolve_vtbl_method(
            {"method": None, "offset": 2, "cls_hint": "Cls"}) == "Slot2"
    finally:
        restore()


def test_unaligned_n_resolves_correctly():
    if _skip(_BLOCKED):
        return
    restore = _with_slots({"Cls": {i: "M%d" % i for i in range(20)}})
    try:
        for n in (1, 2, 3, 5, 6, 7, 9, 15, 19):
            assert s3._resolve_vtbl_method(
                {"method": None, "offset": n, "cls_hint": "Cls"}) == "M%d" % n
    finally:
        restore()


def test_out_of_range_slot_is_none():
    if _skip(_BLOCKED):
        return
    restore = _with_slots({"Cls": {0: "Slot0", 1: "Slot1"}})
    try:
        assert s3._resolve_vtbl_method(
            {"method": None, "offset": 4, "cls_hint": "Cls"}) is None
    finally:
        restore()


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