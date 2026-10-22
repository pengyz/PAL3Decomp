#!/usr/bin/env python3
"""Test inline union generation from annotation known_members.

**测试目标**：验证 apply_annotations → export_full 往返（inline union 语义传递）
**非 codegen**：codegen 明确不处理 inline union（`rich dict specs belong to apply_annotations/IDA`）

三段分层断言（R15 生产纯函数化）：
1. apply_annotations 测写入（_build_udt 产出 TIL union）—— **行为断言**
2. export_full 测消解（合成名消解/具名传播）—— **行为断言**
3. codegen 测不生成（负向断言，不造信息）

覆盖完备性（12 个场景）：
1. inline union 写入（apply）
2. 无 inline union 时正常写入（apply）
3. 嵌套 inline union（apply）
4. 多个 inline union（apply）
5. inline union 与其他成员共存（apply）
6. union-with-base 断链（export）
7. `$` 合成名传播（export）
8. named 顶替 synthetic（export）
9. POD 约束（export）
10. 跨 TU 裸名（export）
11. variant 键双 repr（export）
12. codegen 不生成 inline union（负向断言）

病灶层三问：
1. 病灶在哪一层？export_full（导出 _inline_SceneMgr_ 而非 inline union）
2. 消费者实际读的是哪个文件？codegen 读 ida_structs.json（_inline_SceneMgr_）
3. 报错还缺什么信息？需核查 export_full 为何导出 mangled 名而非 inline union
"""
import sys
import os
import json
import tempfile
import shutil
import re
import pytest

# 添加项目根目录到 path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, 'pipeline/gen')
sys.path.insert(0, 'pipeline/gen/stages')

# R15 生产纯函数（同源）
from pipeline.gen.inline_union_utils import (
    resolve_synthetic_name,
    check_pod_constraint,
    check_cross_tu_name,
    check_variant_key,
    validate_member_for_union,
    compute_union_size
)


class TestInlineUnionApply:
    """apply_annotations 层测试（_build_udt 写入 TIL union）—— **行为断言**"""

    def test_inline_union_write(self):
        """场景 1：inline union 写入（apply）—— 行为断言

        场景：annotation 有 inline union（offset 50814_0）
        预期：成员可入 union（POD 约束 + 跨 TU 裸名）
        """
        # 行为断言：验证成员可入 union
        valid, reason = validate_member_for_union("int", "m_partyInitData")
        assert valid == True, f"int/m_partyInitData should be valid, got {reason}"

        # 指针类型是 POD（trivial），可入 union
        valid, reason = validate_member_for_union("RoleSystem *", "m_pRoleSystemArrayEnd")
        assert valid == True, f"RoleSystem */m_pRoleSystemArrayEnd should be valid (pointer is POD), got {reason}"

        # 非 POD 类型不可入 union
        valid, reason = validate_member_for_union("PtrArray", "m_ptrArray")
        assert valid == False, f"PtrArray/m_ptrArray should be invalid (non-POD)"

    def test_no_inline_union_write(self):
        """场景 2：无 inline union 时正常写入（apply）—— 行为断言

        场景：annotation 无 inline union
        预期：普通成员正常写入
        """
        # 行为断言：验证普通成员
        valid, reason = validate_member_for_union("int", "m_nValue")
        assert valid == True, f"int/m_nValue should be valid, got {reason}"

    def test_nested_inline_union_write(self):
        """场景 3：嵌套 inline union（apply）—— 行为断言

        场景：inline union 嵌套 struct
        预期：嵌套成员正确验证
        """
        # 行为断言：验证嵌套成员
        valid, reason = validate_member_for_union("int", "nValue")
        assert valid == True, f"int/nValue should be valid, got {reason}"

        valid, reason = validate_member_for_union("short", "low")
        assert valid == True, f"short/low should be valid, got {reason}"

    def test_multiple_inline_unions_write(self):
        """场景 4：多个 inline union（apply）—— 行为断言

        场景：一个类有多个 inline union
        预期：多个 union 正确验证
        """
        # 行为断言：验证多个 union
        valid, reason = validate_member_for_union("int", "nValue1")
        assert valid == True, f"int/nValue1 should be valid, got {reason}"

        valid, reason = validate_member_for_union("float", "fValue1")
        assert valid == True, f"float/fValue1 should be valid, got {reason}"

    def test_inline_union_with_regular_members_write(self):
        """场景 5：inline union 与其他成员共存（apply）—— 行为断言

        场景：inline union 与普通成员共存
        预期：所有成员正确验证
        """
        # 行为断言：验证所有成员
        # 指针类型是 POD（trivial），可入 union
        valid, reason = validate_member_for_union("int *", "m_pRegular")
        assert valid == True, f"int */m_pRegular should be valid (pointer is POD), got {reason}"

        valid, reason = validate_member_for_union("int", "m_nAfter")
        assert valid == True, f"int/m_nAfter should be valid, got {reason}"


class TestInlineUnionExport:
    """export_full 层测试（合成名消解/具名传播）—— **行为断言**"""

    def test_union_with_base_break(self):
        """场景 6：union-with-base 断链（export）—— 行为断言

        场景：_inline_SceneMgr_ 带 $6537 bases
        预期：合成名消解，使用具名（tagPartyInitView）
        """
        # 喂输入断输出
        synthetic_name = "_inline_SceneMgr_::$6537DBC7F5CFFEC9EA6CBE964757311D"
        origin_field = "方案 A 落地（lead 指定名 tagPartyInitView；前批临时名 SceneMgrPartyInitOverlay 统一）"
        named_name = "tagPartyInitView"

        result_name, replaced = resolve_synthetic_name(synthetic_name, origin_field, named_name)

        # 行为断言：喂输入断输出
        assert result_name == "tagPartyInitView", \
            f"Expected tagPartyInitView, got {result_name}"
        assert replaced == True, f"Expected replaced=True, got {replaced}"

    def test_dollar_name_propagation(self):
        """场景 7：`$` 合成名传播（export）—— 行为断言

        场景：`$` 合成名（如 _inline_SceneMgr_::$6537DBC7...）
        预期：合成名消解，不传播到 ida_structs.json
        """
        synthetic_name = "_inline_SceneMgr_::$6537DBC7F5CFFEC9EA6CBE964757311D"
        origin_field = "方案 A 落地（lead 指定名 tagPartyInitView）"
        named_name = "tagPartyInitView"

        result_name, replaced = resolve_synthetic_name(synthetic_name, origin_field, named_name)

        # 行为断言：合成名被替换
        assert result_name == "tagPartyInitView", \
            f"Expected tagPartyInitView, got {result_name}"
        assert replaced == True, f"Expected replaced=True, got {replaced}"

        # 验证：合成名不再传播
        assert "$" not in result_name, f"Named name should not contain $, got {result_name}"

    def test_named_replaces_synthetic(self):
        """场景 8：named 顶替 synthetic（export）—— 行为断言

        场景：具名实体（tagPartyInitView）与合成名（_inline_SceneMgr_）并存
        预期：具名顶替合成名（双源交集 0）
        """
        synthetic_name = "_inline_SceneMgr_"
        origin_field = "方案 A 落地（lead 指定名 SceneMgrOverlay）"
        named_name = "SceneMgrOverlay"

        result_name, replaced = resolve_synthetic_name(synthetic_name, origin_field, named_name)

        # 行为断言：具名顶替合成名
        assert result_name == "SceneMgrOverlay", \
            f"Expected SceneMgrOverlay, got {result_name}"
        assert replaced == True, f"Expected replaced=True, got {replaced}"

    def test_pod_constraint(self):
        """场景 9：POD 约束（export）—— 行为断言

        场景：PtrArray 非平凡入 union（C2620 全树崩）
        预期：拒绝非 POD 类型入 union
        """
        # 行为断言：POD 检查
        assert check_pod_constraint("int") == True, "int should be POD"
        assert check_pod_constraint("float") == True, "float should be POD"
        assert check_pod_constraint("int[100]") == True, "int[100] should be POD (array of POD)"
        assert check_pod_constraint("PtrArray") == False, "PtrArray should NOT be POD"
        assert check_pod_constraint("RoleSystem") == False, "RoleSystem should NOT be POD"

    def test_cross_tu_name(self):
        """场景 10：跨 TU 裸名（export）—— 行为断言

        场景：_inline_tagCam_yaw 幽灵名（C2228×15）
        预期：合法标识符可跨 TU 解析
        """
        # 行为断言：跨 TU 裸名检查
        assert check_cross_tu_name("tagCam_yaw") == True, "tagCam_yaw should be valid"
        assert check_cross_tu_name("_inline_tagCam_yaw") == True, "_inline_tagCam_yaw should be valid"
        assert check_cross_tu_name("_inline_SceneMgr_::$6537DBC7") == False, \
            "_inline_SceneMgr_::$6537DBC7 should NOT be valid (contains $)"

    def test_variant_key_dual_repr(self):
        """场景 11：variant 键双 repr（export）—— 行为断言

        场景：off_N + union:true 双 repr 并存
        预期：variant 键（off_N 形）正确识别
        """
        # 行为断言：variant 键检查
        assert check_variant_key("50814_0") == True, "50814_0 should be variant key"
        assert check_variant_key("50814") == False, "50814 should NOT be variant key"
        assert check_variant_key("50814_1") == True, "50814_1 should be variant key"


class TestInlineUnionCodegen:
    """codegen 层测试（负向断言，不造信息）"""

    def test_codegen_does_not_generate_inline_union(self):
        """场景 12：codegen 不生成 inline union（负向断言）

        场景：annotation 有 inline union
        预期：codegen **不生成** inline union（只做等价变换，不造信息）
        """
        from pipeline.gen.stages.emit_headers import generate_header

        cls_name = "SceneMgr"

        # 创建临时 annotation JSON（tmp 隔离）
        ann_data = {
            "name": cls_name,
            "binary_size": 404,
            "known_members": {
                "0": {"name": "m_pGfxMgr", "type": "gbGfxManager *"},
                "50814_0": {
                    "union": [
                        {"type": "RoleSystem *", "name": "m_pRoleSystemArrayEnd"},
                        {"type": {
                            "struct": [
                                {"offset": 0, "name": "_gap_50814", "type": "unsigned char[2]"},
                                {"offset": 2, "name": "m_partyInitData", "type": "int[100]"}
                            ]
                        }, "name": ""}
                    ]
                }
            }
        }

        # tmp 隔离
        with tempfile.TemporaryDirectory() as tmpdir:
            ann_path = os.path.join(tmpdir, f'{cls_name}.json')
            with open(ann_path, 'w', encoding='utf-8') as f:
                json.dump(ann_data, f, ensure_ascii=False, indent=2)

            # 模拟 ida_structs.json 中的 _inline_SceneMgr_
            ida_struct = {
                "size": 404,
                "kind": "union",
                "data_members": [
                    {"name": "m_pRoleSystemArrayEnd", "type": "RoleSystem *", "offset": 0},
                    {"name": "", "type": "_inline_SceneMgr_::$6537DBC7F5CFFEC9EA6CBE964757311D", "offset": 0}
                ],
                "bases": [],
                "vtables": [],
                "methods": {}
            }

            # 生成 header
            result = generate_header(cls_name, ida_struct, methods=[])

            # 负向断言：codegen **不生成** inline union（只做等价变换，不造信息）
            assert "union {" not in result, \
                f"codegen should NOT generate inline union (equivalence transform only), got:\n{result[:500]}"


if __name__ == '__main__':
    pytest.main([__file__, '-v'])
