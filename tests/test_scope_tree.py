"""Tests for scope_tree module."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "pipeline" / "gen" / "stages"))

from scope_tree import ScopeTree, is_ida_artifact, parent_key, should_skip_root


def test_is_ida_artifact():
    assert is_ida_artifact("")
    assert is_ida_artifact("_")
    assert is_ida_artifact("gbColorQuad::$GUID")
    assert is_ida_artifact("?mangled_name")
    assert is_ida_artifact("tpl<A>")
    assert not is_ida_artifact("AStarPathFinder")
    assert not is_ida_artifact("SceneMgr")


def test_parent_key():
    assert parent_key("AStarPathFinder") is None
    assert parent_key("AStarPathFinder::NODE") == "AStarPathFinder"
    assert parent_key("A::B::C") == "A::B"
    assert parent_key("std::string") == "std"


def test_should_skip_root():
    skip_classes = {"std", "string", "HWND__"}
    skip_prefixes = ("D3D", "gb", "IUnknown")
    assert should_skip_root("std", skip_classes, skip_prefixes)
    assert should_skip_root("HWND__", skip_classes, skip_prefixes)
    assert should_skip_root("D3DVIEWPORT9", skip_classes, skip_prefixes)
    assert should_skip_root("gbCamera", skip_classes, skip_prefixes)
    assert not should_skip_root("AStarPathFinder", skip_classes, skip_prefixes)
    assert not should_skip_root("SceneMgr", skip_classes, skip_prefixes)


def test_build_basic():
    ida_data = {
        "AStarPathFinder": {"size": 24, "data_members": []},
        "AStarPathFinder::NODE": {"size": 64, "data_members": []},
        "AStarPathFinder::STACK": {"size": 4, "data_members": []},
    }
    tree = ScopeTree()
    tree.build(ida_data, set(), ())
    assert len(tree.roots) == 1
    assert tree.roots[0].full_name == "AStarPathFinder"
    assert len(tree.roots[0].children) == 2
    child_names = {c.full_name for c in tree.roots[0].children}
    assert "AStarPathFinder::NODE" in child_names
    assert "AStarPathFinder::STACK" in child_names


def test_build_deep_nesting():
    ida_data = {
        "Alpha": {"size": 10, "data_members": []},
        "Alpha::Beta": {"size": 10, "data_members": []},
        "Alpha::Beta::Gamma": {"size": 10, "data_members": []},
    }
    tree = ScopeTree()
    tree.build(ida_data, set(), ())
    assert len(tree.roots) == 1
    assert tree.roots[0].full_name == "Alpha"
    assert len(tree.roots[0].children) == 1
    assert tree.roots[0].children[0].full_name == "Alpha::Beta"
    assert len(tree.roots[0].children[0].children) == 1
    assert tree.roots[0].children[0].children[0].full_name == "Alpha::Beta::Gamma"


def test_prune_skipped_root():
    ida_data = {
        "std": {"size": 1, "data_members": []},
        "std::string": {"size": 20, "data_members": []},
        "AStarPathFinder": {"size": 24, "data_members": []},
    }
    tree = ScopeTree()
    tree.build(ida_data, {"std"}, ())
    assert len(tree.roots) == 1
    assert tree.roots[0].full_name == "AStarPathFinder"
    assert tree.find("std").is_skipped
    assert tree.find("std::string").is_skipped


def test_multiple_valid_roots():
    ida_data = {"ClassA": {"size": 4, "data_members": []}, "ClassB": {"size": 4, "data_members": []}}
    tree = ScopeTree()
    tree.build(ida_data, set(), ())
    assert len(tree.roots) == 2


def test_find():
    ida_data = {"Xenon": {"size": 4, "data_members": []}, "Xenon::Yttrium": {"size": 4, "data_members": []}}
    tree = ScopeTree()
    tree.build(ida_data, set(), ())
    assert tree.find("Xenon") is not None
    assert tree.find("Xenon::Yttrium") is not None
    assert tree.find("Zenith") is None


def test_parent_of():
    ida_data = {"Parent": {"size": 4, "data_members": []}, "Parent::Child": {"size": 4, "data_members": []}}
    tree = ScopeTree()
    tree.build(ida_data, set(), ())
    parent = tree.parent_of("Parent::Child")
    assert parent is not None
    assert parent.full_name == "Parent"
    assert tree.parent_of("Parent") is None


def test_build_from_real_data():
    """Smoke test: load actual ida_structs.json and build tree."""
    import json

    path = Path(__file__).resolve().parent.parent / "asm" / "pal3" / "ida_structs.json"
    if not path.exists():
        return
    data = json.load(open(path, encoding="utf-8"))
    tree = ScopeTree()
    tree.build(data, {"std", "string", "HWND__"}, ("D3D", "gb", "IUnknown"))
    assert len(tree.roots) > 0
    for root in tree.roots:
        assert "::" not in root.full_name
