"""vtable-as-data v2（R94c·2026-10-25·用户已批准）。

前提（十进制数学+探针双证）：CEffect 注解坐标是【含 vptr 的绝对偏移】，
as_data=true 使编译器不再插 vptr，坐标自洽。
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / "pipeline" / "gen"))
sys.path.insert(0, str(REPO / "pipeline" / "gen" / "stages"))

import emit_headers as EH


def test_get_vtable_addr_skips_as_data(monkeypatch):
    monkeypatch.setattr(EH, "_vtable_as_data", lambda cls: True)
    assert EH._get_vtable_addr("VDataTestClass") is None


def test_get_vtable_addr_normal_table_kept(monkeypatch):
    monkeypatch.setattr(EH, "_ida_structs_cache", {
        "VNormalClass": {"vtables": [{"addr": "0x00ABCE00"}], "methods": {}}})
    assert EH._get_vtable_addr("VNormalClass") == "0x00ABCE00"


def test_class_vtable_slots_skips_as_data(monkeypatch):
    monkeypatch.setattr(EH, "_vtable_as_data", lambda cls: True)
    monkeypatch.setattr(EH, "_ida_structs_cache", {
        "VDataTestClass2": {
            "vtables": [{"addr": "0x00ABCD10"}],
            "methods": {}}})
    assert EH.class_vtable_slots("VDataTestClass2") == []


def test_class_vtable_slots_normal_kept(monkeypatch):
    monkeypatch.setattr(EH, "_ida_structs_cache", {
        "VNormalClass2": {
            "vtables": [{"addr": "0x00ABCE10",
                         "slots": [{"addr": "0x004C5DB0"}]}],
            "methods": {"0x004C5DB0": {"name": "Activate"}}}})
    assert EH.class_vtable_slots("VNormalClass2") == ["Activate"]
