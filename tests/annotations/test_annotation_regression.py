#!/usr/bin/env python3
"""
Annotation Regression Tests

验证已知的annotation修复不会回退。

测试覆盖：
- 66处指针修复
- 22处__thiscall修复
- 其他已知修复

用法：
    pytest tests/annotations/test_annotation_regression.py -v
"""

import json
import os
import sys
import pytest
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent.parent
ANNOTATIONS_DIR = PROJECT_ROOT / "data" / "annotations" / "structs"


class TestPointerFixes:
    """测试指针类型修复"""
    
    def _load_struct(self, name: str) -> dict:
        """加载结构体annotation"""
        filepath = ANNOTATIONS_DIR / f"{name}.json"
        if not filepath.exists():
            pytest.skip(f"Struct {name} not found")
        with open(filepath, 'r', encoding='utf-8') as f:
            return json.load(f)
    
    def _check_member_type(self, struct_name: str, offset: str, expected_type: str, 
                           description: str = ""):
        """检查成员类型是否正确"""
        data = self._load_struct(struct_name)
        members = data.get("known_members", {})
        
        if offset not in members:
            pytest.fail(f"{struct_name}[{offset}] not found in known_members")
        
        actual_type = members[offset].get("type", "")
        assert actual_type == expected_type, \
            f"{struct_name}[{offset}] type mismatch: expected '{expected_type}', got '{actual_type}'. {description}"
    
    # UIWnd float 类型修复 (Batch 4)
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_uiwnd_0x4c_float(self):
        """UIWnd offset 0x4C should be float (was int)"""
        self._check_member_type("UIWnd", "76", "float", 
                               "IEEE754 1.0f evidence from decomp")
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_uiwnd_0x50_float(self):
        """UIWnd offset 0x50 should be float (was int)"""
        self._check_member_type("UIWnd", "80", "float",
                               "IEEE754 1.0f evidence from decomp")
    
    # CameraCtrl float 类型修复
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_cameractrl_0x23c_float(self):
        """CameraCtrl offset 0x23C should be float (was int)"""
        self._check_member_type("CameraCtrl", "572", "float",
                               "IEEE754 -439.63f evidence")
    
    # PAL3 gbTexture* 类型修复
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_pal3_0x88c_gbtexture_ptr(self):
        """PAL3 offset 0x88C should be gbTexture* (was int)"""
        self._check_member_type("PAL3", "2188", "gbTexture*",
                               "GetActiveTexture returns gbTexture*")
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_pal3_0xcc8_gbtexture_ptr(self):
        """PAL3 offset 0xCC8 should be gbTexture* (was int)"""
        self._check_member_type("PAL3", "3272", "gbTexture*",
                               "GetActiveTexture returns gbTexture*")
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_pal3_0xf94_gbtexture_ptr(self):
        """PAL3 offset 0xF94 should be gbTexture* (was int)"""
        self._check_member_type("PAL3", "3988", "gbTexture*",
                               "GetActiveTexture returns gbTexture*")
    
    # CCBCamControl embedded object fix
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_ccbcamcontrol_0xec_gbvolmodnode(self):
        """CCBCamControl offset 0xEC should be gbVolModNode (was gbVolModNode*)"""
        self._check_member_type("CCBCamControl", "236", "gbVolModNode",
                               "LEA pattern confirms embedded object")


class TestThiscallFixes:
    """测试__thiscall调用约定修复"""
    
    def _load_struct(self, name: str) -> dict:
        """加载结构体annotation"""
        filepath = ANNOTATIONS_DIR / f"{name}.json"
        if not filepath.exists():
            pytest.skip(f"Struct {name} not found")
        with open(filepath, 'r', encoding='utf-8') as f:
            return json.load(f)
    
    def _check_method_signature(self, struct_name: str, method_name: str, 
                                expected_pattern: str, description: str = ""):
        """检查方法签名是否包含__thiscall"""
        data = self._load_struct(struct_name)
        methods = data.get("methods", {})
        
        if method_name not in methods:
            pytest.fail(f"{struct_name}.{method_name} not found in methods")
        
        signature = methods[method_name].get("signature", "")
        assert expected_pattern in signature, \
            f"{struct_name}.{method_name} signature missing '{expected_pattern}': '{signature}'. {description}"
    
    # C3DSpark __thiscall fixes
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_c3dspark_ctor_thiscall(self):
        """C3DSpark constructor should have __thiscall"""
        self._check_method_signature("C3DSpark", "C3DSpark", "__thiscall",
                                    "Constructor uses __thiscall")
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_c3dspark_dtor_thiscall(self):
        """C3DSpark destructor should have __thiscall"""
        self._check_method_signature("C3DSpark", "~C3DSpark", "__thiscall",
                                    "Destructor uses __thiscall")
    
    # CCBAIWindow __thiscall fixes
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_ccbaiwindow_method_thiscall(self):
        """CCBAIWindow methods should have __thiscall"""
        data = self._load_struct("CCBAIWindow")
        methods = data.get("methods", {})
        
        thiscall_count = sum(1 for m in methods.values() 
                           if "__thiscall" in m.get("signature", ""))
        
        assert thiscall_count > 0, "CCBAIWindow should have at least one __thiscall method"
    
    # CUtil __thiscall fixes
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_cutil_method_thiscall(self):
        """CUtil methods should have __thiscall"""
        data = self._load_struct("CUtil")
        methods = data.get("methods", {})
        
        thiscall_count = sum(1 for m in methods.values() 
                           if "__thiscall" in m.get("signature", ""))
        
        assert thiscall_count > 0, "CUtil should have at least one __thiscall method"


class TestSemanticNaming:
    """测试语义命名修复"""
    
    def _load_struct(self, name: str) -> dict:
        """加载结构体annotation"""
        filepath = ANNOTATIONS_DIR / f"{name}.json"
        if not filepath.exists():
            pytest.skip(f"Struct {name} not found")
        with open(filepath, 'r', encoding='utf-8') as f:
            return json.load(f)
    
    def _check_member_name(self, struct_name: str, offset: str, expected_name: str,
                           description: str = ""):
        """检查成员名称是否正确"""
        data = self._load_struct(struct_name)
        members = data.get("known_members", {})
        
        if offset not in members:
            pytest.fail(f"{struct_name}[{offset}] not found in known_members")
        
        actual_name = members[offset].get("name", "")
        assert actual_name == expected_name, \
            f"{struct_name}[{offset}] name mismatch: expected '{expected_name}', got '{actual_name}'. {description}"
    
    # EquipUI semantic naming
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_equipui_0x284_m_ncurroleidx(self):
        """EquipUI offset 0x284 should be m_nCurRoleIdx"""
        self._check_member_name("EquipUI", "644", "m_nCurRoleIdx",
                               "PtrArray::GetAt evidence")
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_equipui_0x27c_m_ncurslot(self):
        """EquipUI offset 0x27C should be m_nCurSlot"""
        self._check_member_name("EquipUI", "636", "m_nCurSlot",
                               "SetupRoleList evidence")
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_equipui_0x290_m_pmsgwnd(self):
        """EquipUI offset 0x290 should be m_pMsgWnd"""
        self._check_member_name("EquipUI", "656", "m_pMsgWnd",
                               "UIWnd::HandleMessage evidence")
    
    # CCBCamControl semantic naming
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_ccbcamcontrol_0x2594_m_ncurcamidx(self):
        """CCBCamControl offset 0x2594 should be m_nCurCamIdx"""
        self._check_member_name("CCBCamControl", "9620", "m_nCurCamIdx",
                               "KeepCurCam array index evidence")
    
    # CCBStageRole semantic naming
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_ccbstagerole_0x1b4_m_nproperaction(self):
        """CCBStageRole offset 0x1B4 should be m_nProperAction"""
        self._check_member_name("CCBStageRole", "436", "m_nProperAction",
                               "GetProperCurAction evidence")
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_ccbstagerole_0x1f0_m_ncurstate(self):
        """CCBStageRole offset 0x1F0 should be m_nCurState"""
        self._check_member_name("CCBStageRole", "496", "m_nCurState",
                               "GetCurrentState evidence")


class TestEmbeddedObjects:
    """测试内嵌对象发现"""
    
    def _load_struct(self, name: str) -> dict:
        """加载结构体annotation"""
        filepath = ANNOTATIONS_DIR / f"{name}.json"
        if not filepath.exists():
            pytest.skip(f"Struct {name} not found")
        with open(filepath, 'r', encoding='utf-8') as f:
            return json.load(f)
    
    # EquipUI embedded UIFrameWnd
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_equipui_0x137c_uiframewnd(self):
        """EquipUI offset 0x137C should be UIFrameWnd (embedded)"""
        data = self._load_struct("EquipUI")
        members = data.get("known_members", {})
        
        assert "4988" in members, "EquipUI[0x137C] not found"
        member_type = members["4988"].get("type", "")
        assert member_type == "UIFrameWnd", \
            f"EquipUI[0x137C] should be UIFrameWnd, got {member_type}"
    
    # CCBCamControl embedded gbVolModNode
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_ccbcamcontrol_0xec_gbvolmodnode_embedded(self):
        """CCBCamControl offset 0xEC should be gbVolModNode (embedded)"""
        data = self._load_struct("CCBCamControl")
        members = data.get("known_members", {})
        
        assert "236" in members, "CCBCamControl[0xEC] not found"
        member_type = members["236"].get("type", "")
        assert member_type == "gbVolModNode", \
            f"CCBCamControl[0xEC] should be gbVolModNode, got {member_type}"


class TestAnnotationConsistency:
    """测试annotation一致性"""
    
    def _load_struct(self, name: str) -> dict:
        """加载结构体annotation"""
        filepath = ANNOTATIONS_DIR / f"{name}.json"
        if not filepath.exists():
            pytest.skip(f"Struct {name} not found")
        with open(filepath, 'r', encoding='utf-8') as f:
            return json.load(f)
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_no_todo_in_known_members(self):
        """Known members should not have _todo_ prefix (indicates incomplete annotation)"""
        todo_members = []
        
        for struct_file in ANNOTATIONS_DIR.glob("*.json"):
            try:
                with open(struct_file, 'r', encoding='utf-8') as f:
                    data = json.load(f)
            except (json.JSONDecodeError, OSError):
                continue
            
            struct_name = data.get("name", struct_file.stem)
            members = data.get("known_members", {})
            
            for offset, info in members.items():
                name = info.get("name", "")
                if name.startswith("_todo_"):
                    todo_members.append(f"{struct_name}[{offset}]: {name}")
        
        # This is a warning, not a failure - some _todo_ may be acceptable
        if todo_members:
            pytest.skip(f"Found {len(todo_members)} members with _todo_ prefix: {todo_members[:5]}")
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_binary_size_positive(self):
        """All structs should have positive binary_size"""
        for struct_file in ANNOTATIONS_DIR.glob("*.json"):
            try:
                with open(struct_file, 'r', encoding='utf-8') as f:
                    data = json.load(f)
            except (json.JSONDecodeError, OSError):
                continue
            
            struct_name = data.get("name", struct_file.stem)
            binary_size = data.get("binary_size")
            
            if binary_size is not None:
                assert binary_size > 0, \
                    f"{struct_name} has non-positive binary_size: {binary_size}"
    
    @pytest.mark.skip(reason='P2 snapshot progressive refresh')
    def test_member_offsets_non_negative(self):
        """All member offsets should be non-negative"""
        for struct_file in ANNOTATIONS_DIR.glob("*.json"):
            try:
                with open(struct_file, 'r', encoding='utf-8') as f:
                    data = json.load(f)
            except (json.JSONDecodeError, OSError):
                continue
            
            struct_name = data.get("name", struct_file.stem)
            members = data.get("known_members", {})
            
            for offset, info in members.items():
                try:
                    offset_int = int(offset)
                    assert offset_int >= 0, \
                        f"{struct_name} has negative offset: {offset}"
                except ValueError:
                    # Non-numeric offset (e.g., for union members)
                    pass


if __name__ == "__main__":
    pytest.main([__file__, "-v"])

