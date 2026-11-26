#!/usr/bin/env python3
"""R4 拆类回归（#19）：ScreenEffectMgr / ScreenEffectRingNode / ScreenEffect / PAL3VisNode 级联。

判据全部来自 `docs/specs/2026-11-26-r4-fill-change-plan.md`（#16）与
`docs/specs/2026-11-26-pal3visnode-size-evidence.md`（#15）的实测证据，
本测试只锁定注解结构，不跑管线。

运行：python3 -m pytest tests/test_r4_screeneffect_split.py -q
"""
import json
import os

REPO = os.environ.get("PAL3_REPO") or os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
STRUCTS = os.path.join(REPO, "data", "annotations", "structs")


def _load(cls):
    with open(os.path.join(STRUCTS, cls + ".json"), encoding="utf-8") as f:
        return json.load(f)


def test_pal3visnode_size_and_state_member():
    d = _load("PAL3VisNode")
    assert d["binary_size"] == 92, "PAL3VisNode 真实尺寸 92（ctor 在 +0x58 写 4B，派生首员在 0x5C）"
    # base_size 语义 = 直接基类 gbVisNode 的 binary_size，保持 88
    assert int(d.get("base_size", 0)) == 88, "base_size 是直接基类 gbVisNode 的尺寸，不得跟着 binary_size 改"
    m = d["known_members"]["0x58"]
    assert m["name"] == "m_nState" and m["type"] == "int"


def test_derived_base_size_cascade():
    for cls, size in (("CEffGroupNode", 116), ("UI3DModelNode", 248), ("ScreenEffectNode", 220)):
        d = _load(cls)
        assert int(d["base_size"]) == 92, f"{cls} 的 base_size 必须跟随 PAL3VisNode 的 92"
        assert d["binary_size"] == size, f"{cls} 的 sizeof 不因级联改变"


def test_screeneffectmgr_is_singleton_only():
    d = _load("ScreenEffectMgr")
    assert d["binary_size"] == 152, "A 侧是 152B 静态单例（16 员闭合到 0x98）"
    offs = sorted(int(k, 0) for k in d["known_members"])
    assert offs == [0x0, 0x4, 0x20, 0x38, 0x50, 0x68, 0x6C, 0x70, 0x74, 0x78, 0x7C,
                    0x80, 0x84, 0x88, 0x8C, 0x94], "A 的 16 员，0x90 留洞"
    assert [v["addr"] for v in d["vtables"]] == ["0x0056f508"]
    assert len(d["vtables"][0]["slots"]) == 1
    assert not hasattr(d, "bases") or not d.get("bases"), "A 无基类"


def test_ring_node_owns_b_side():
    d = _load("ScreenEffectRingNode")
    assert d["binary_size"] == 363968
    assert d["base_size"] == 92
    assert d["bases"] == [{"name": "PAL3VisNode", "offset": 0}]
    assert [v["addr"] for v in d["vtables"]] == ["0x0056f580"]
    assert len(d["vtables"][0]["slots"]) == 15
    for off, name in (("0x5c", "m_fAnimAccum"), ("0x60", "m_hResLarge"),
                      ("0x64", "m_hResSmall"), ("0xa4", "m_nGeometryReady"),
                      ("0xb0", "m_ringQuadsLarge"), ("0x248", "m_ringQuadsSmall"),
                      ("0x3e0", "m_singleQuad"), ("0x454", "m_particleEffect")):
        assert d["known_members"][off]["name"] == name, off
    # 洞三段不得用 m_unk_ 占位（命名铁律）
    for k in d["known_members"]:
        assert not d["known_members"][k]["name"].startswith("m_unk_"), k


def test_screeneffect_keeps_own_ctor():
    d = _load("ScreenEffect")
    assert d["binary_size"] == 24
    assert "0x004bdf10" in d["methods"], "ScreenEffect 真正的 ctor 0x4BDF10（写 vptr 0x56F4F0）"
    assert d["methods"]["0x004bdf10"]["name"] == "ScreenEffect"
    assert "ctor" in d["methods"]["0x004bdf10"].get("flags", [])
    assert "0x004bdfb0" not in d["methods"], "0x4BDFB0 属 ScreenEffectMgr"
    assert "0x004be060" not in d["methods"], "0x4BE060 属 ScreenEffectMgr"
    assert [v["addr"] for v in d["vtables"]] == ["0x0056f4f0"]


def test_cross_owner_entries_removed():
    rt = _load("RenderTarget")
    assert "0x004bdf10" not in rt["methods"], "RenderTarget 旧条目必须删，否则 owner 门丢弃新归属"
    urd = _load("UIRoleDialog")
    assert "0x004bef50" not in urd["methods"], "UIRoleDialog 旧条目必须删"


def test_atexit_thunk_renamed():
    with open(os.path.join(REPO, "data", "annotations", "functions.json"), encoding="utf-8") as f:
        funcs = json.load(f)
    assert funcs["0x004be5d0"]["name"] == "DestroyScreenEffectSingleton"


if __name__ == "__main__":
    for name, fn in sorted(globals().items()):
        if name.startswith("test_") and callable(fn):
            fn()
            print("ok", name)
