#!/usr/bin/env python3
"""
Annotation Regression Tests (Simple Version)

验证已知的annotation修复不会回退。

用法：
    python3 tests/annotations/test_regression_simple.py
"""

import json
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent.parent
ANNOTATIONS_DIR = PROJECT_ROOT / "data" / "annotations" / "structs"


def load_struct(name: str) -> dict:
    """加载结构体annotation"""
    filepath = ANNOTATIONS_DIR / f"{name}.json"
    if not filepath.exists():
        return None
    with open(filepath, 'r', encoding='utf-8') as f:
        return json.load(f)


def test_pointer_fixes():
    """测试指针类型修复"""
    print("🔍 Testing pointer fixes...")
    
    tests = [
        # (struct_name, offset, expected_type, description)
        ("CameraCtrl", "572", "float", "CameraCtrl 0x23C should be float"),
        ("PAL3", "2188", "gbTexture *", "PAL3 0x88C should be gbTexture*"),
        ("PAL3", "3272", "gbTexture *", "PAL3 0xCC8 should be gbTexture*"),
        ("PAL3", "3988", "gbTexture *", "PAL3 0xF94 should be gbTexture*"),
        ("CCBCamControl", "236", "gbVolModNode", "CCBCamControl 0xEC should be gbVolModNode"),
    ]
    
    passed = 0
    failed = 0
    skipped = 0
    
    for struct_name, offset, expected_type, description in tests:
        data = load_struct(struct_name)
        if data is None:
            print(f"  ⏭️  {struct_name}: struct not found")
            skipped += 1
            continue
        
        members = data.get("known_members", {})
        if offset not in members:
            print(f"  ⏭️  {struct_name}[{offset}]: offset not found")
            skipped += 1
            continue
        
        actual_type = members[offset].get("type", "")
        # Normalize types for comparison (handle spaces in pointer types)
        actual_normalized = actual_type.replace(" ", "")
        expected_normalized = expected_type.replace(" ", "")
        
        if actual_normalized == expected_normalized:
            print(f"  ✅ {struct_name}[{offset}]: {actual_type} (correct)")
            passed += 1
        else:
            print(f"  ❌ {struct_name}[{offset}]: {actual_type} (expected {expected_type})")
            failed += 1
    
    return passed, failed, skipped


def test_thiscall_fixes():
    """测试__thiscall调用约定修复"""
    print("\n🔍 Testing __thiscall fixes...")
    
    tests = [
        # (struct_name, min_thiscall_methods, description)
        ("C3DSpark", 1, "C3DSpark should have __thiscall methods"),
        ("CCBAIWindow", 1, "CCBAIWindow should have __thiscall methods"),
        ("CUtil", 1, "CUtil should have __thiscall methods"),
    ]
    
    passed = 0
    failed = 0
    skipped = 0
    
    for struct_name, min_count, description in tests:
        data = load_struct(struct_name)
        if data is None:
            print(f"  ⏭️  {struct_name}: struct not found")
            skipped += 1
            continue
        
        methods = data.get("methods", {})
        thiscall_count = sum(1 for m in methods.values() 
                           if "__thiscall" in m.get("signature", ""))
        
        if thiscall_count >= min_count:
            print(f"  ✅ {struct_name}: {thiscall_count} __thiscall methods (>= {min_count})")
            passed += 1
        else:
            print(f"  ❌ {struct_name}: {thiscall_count} __thiscall methods (< {min_count})")
            failed += 1
    
    return passed, failed, skipped


def test_semantic_naming():
    """测试语义命名修复"""
    print("\n🔍 Testing semantic naming...")
    
    tests = [
        # (struct_name, offset, expected_name, description)
        ("EquipUI", "644", "m_nCurRoleIdx", "EquipUI 0x284 should be m_nCurRoleIdx"),
        ("EquipUI", "636", "m_nCurSlot", "EquipUI 0x27C should be m_nCurSlot"),
        ("EquipUI", "656", "m_pMsgWnd", "EquipUI 0x290 should be m_pMsgWnd"),
        ("CCBCamControl", "9620", "m_nCurCamIdx", "CCBCamControl 0x2594 should be m_nCurCamIdx"),
        ("CCBStageRole", "436", "m_nProperAction", "CCBStageRole 0x1B4 should be m_nProperAction"),
        ("CCBStageRole", "496", "m_nCurState", "CCBStageRole 0x1F0 should be m_nCurState"),
    ]
    
    passed = 0
    failed = 0
    skipped = 0
    
    for struct_name, offset, expected_name, description in tests:
        data = load_struct(struct_name)
        if data is None:
            print(f"  ⏭️  {struct_name}: struct not found")
            skipped += 1
            continue
        
        members = data.get("known_members", {})
        if offset not in members:
            print(f"  ⏭️  {struct_name}[{offset}]: offset not found")
            skipped += 1
            continue
        
        actual_name = members[offset].get("name", "")
        if actual_name == expected_name:
            print(f"  ✅ {struct_name}[{offset}]: {actual_name} (correct)")
            passed += 1
        else:
            print(f"  ❌ {struct_name}[{offset}]: {actual_name} (expected {expected_name})")
            failed += 1
    
    return passed, failed, skipped


def test_embedded_objects():
    """测试内嵌对象发现"""
    print("\n🔍 Testing embedded objects...")
    
    tests = [
        # (struct_name, offset, expected_type, description)
        ("EquipUI", "4988", "UIFrameWnd", "EquipUI 0x137C should be UIFrameWnd"),
        ("CCBCamControl", "236", "gbVolModNode", "CCBCamControl 0xEC should be gbVolModNode"),
    ]
    
    passed = 0
    failed = 0
    skipped = 0
    
    for struct_name, offset, expected_type, description in tests:
        data = load_struct(struct_name)
        if data is None:
            print(f"  ⏭️  {struct_name}: struct not found")
            skipped += 1
            continue
        
        members = data.get("known_members", {})
        if offset not in members:
            print(f"  ⏭️  {struct_name}[{offset}]: offset not found")
            skipped += 1
            continue
        
        actual_type = members[offset].get("type", "")
        if actual_type == expected_type:
            print(f"  ✅ {struct_name}[{offset}]: {actual_type} (correct)")
            passed += 1
        else:
            print(f"  ❌ {struct_name}[{offset}]: {actual_type} (expected {expected_type})")
            failed += 1
    
    return passed, failed, skipped


def test_annotation_consistency():
    """测试annotation一致性"""
    print("\n🔍 Testing annotation consistency...")
    
    passed = 0
    failed = 0
    skipped = 0
    
    # Check binary_size is positive
    print("  Checking binary_size values...")
    for struct_file in ANNOTATIONS_DIR.glob("*.json"):
        try:
            with open(struct_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
        except (json.JSONDecodeError, OSError):
            continue
        
        struct_name = data.get("name", struct_file.stem)
        binary_size = data.get("binary_size")
        
        if binary_size is not None and binary_size <= 0:
            print(f"    ❌ {struct_name}: non-positive binary_size: {binary_size}")
            failed += 1
        else:
            passed += 1
    
    # Check member offsets are non-negative
    print("  Checking member offsets...")
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
                if offset_int < 0:
                    print(f"    ❌ {struct_name}[{offset}]: negative offset")
                    failed += 1
                else:
                    passed += 1
            except ValueError:
                # Non-numeric offset (e.g., for union members)
                passed += 1
    
    return passed, failed, skipped


def main():
    print("=" * 80)
    print("Annotation Regression Tests")
    print("=" * 80)
    print()
    
    total_passed = 0
    total_failed = 0
    total_skipped = 0
    
    # Run all tests
    p, f, s = test_pointer_fixes()
    total_passed += p
    total_failed += f
    total_skipped += s
    
    p, f, s = test_thiscall_fixes()
    total_passed += p
    total_failed += f
    total_skipped += s
    
    p, f, s = test_semantic_naming()
    total_passed += p
    total_failed += f
    total_skipped += s
    
    p, f, s = test_embedded_objects()
    total_passed += p
    total_failed += f
    total_skipped += s
    
    p, f, s = test_annotation_consistency()
    total_passed += p
    total_failed += f
    total_skipped += s
    
    # Summary
    print("\n" + "=" * 80)
    print("📊 Summary:")
    print(f"  ✅ Passed: {total_passed}")
    print(f"  ❌ Failed: {total_failed}")
    print(f"  ⏭️  Skipped: {total_skipped}")
    print()
    
    if total_failed > 0:
        print("❌ Some tests failed!")
        return 1
    else:
        print("✅ All tests passed!")
        return 0


if __name__ == "__main__":
    sys.exit(main())
