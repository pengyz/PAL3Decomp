"""任务 3：enum IAT 槽数函数类型注入链（`SetAxisAngle` / `SetOpenMode`）。

机理（data/status/_attr_cards_20261009/N3_N4_finding.md + 任务 4 报告 §1 实证）：
Hex-Rays 在「被调函数 IAT 槽的形参类型 = enum」时自动补 cast（`(EEffect)1` 实证——
即使 `EF_Simple=1` 有名有姓，Hex-Rays 仍打印 `(EEffect)1` 而非常量名 ⇒ 只有 **enum 类型名**
参与生成码，成员名无关）。当前缺口：IAT 槽形参退化成 int ⇒ 不补 cast ⇒ `SetAxisAngle(2, …)`
裸整型 ⇒ C2664。

本测试锁三件事（全部对 `apply_annotations.py` 内**真实存在**的函数/数据结构断言，
不引用计划里已裁决作废的 `resolve_iat_sig` 占位符）：
  1. `test_enum_param_written_to_iat`      —— `_GB_IMPORT_SIGS`（真实数据结构）必须给
     `CPK::SetOpenMode` 写入 `enum ECPKMode` 形参（简报步骤 1 的意图，0x53c38f push 0x1）。
  2. `test_iat_sig_contains_enum_param`    —— mangled `W4gbAxis` 必须被解出 enum 形参
     （A 级证据：修饰名直接编码形参类型）。
  3. `test_existing_enum_short_circuit_does_not_drop_declared_params`
     —— `apply_annotations.py:2186` 3b 步对已存在 enum 的整体短路，不得让 `enums.json`
     里已声明的值静默丢失（每个已声明 (name,value) 都要有显式处置）。

两条绿路：
  python -m pytest --assert=plain tests/ida/test_gbimport_enum_sig.py -v
  python3 tests/ida/test_gbimport_enum_sig.py
"""
import importlib.util
import os
import re
import sys
import unittest.mock

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MODULE_PATH = os.path.join(ROOT, 'pipeline', 'ida', 'apply_annotations.py')
IDA_MODULES = (
    'ida_auto', 'ida_bytes', 'ida_funcs', 'ida_hexrays', 'ida_name',
    'ida_typeinf', 'idautils', 'idc',
)


def _load_apply_annotations():
    """stub 掉 IDA 模块后加载真实的 `apply_annotations`（同 tests/test_owner_field.py 手法）。"""
    saved_modules = {name: sys.modules.get(name) for name in IDA_MODULES}
    for name in IDA_MODULES:
        sys.modules[name] = unittest.mock.MagicMock()
    try:
        spec = importlib.util.spec_from_file_location(
            'test_apply_annotations_gbimport', MODULE_PATH)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        return module
    finally:
        for name, previous in saved_modules.items():
            if previous is None:
                sys.modules.pop(name, None)
            else:
                sys.modules[name] = previous


def test_enum_param_written_to_iat():
    """简报步骤 1：0x53c38f push 0x1 / call → CPK::SetOpenMode(ECPKMode)。

    `?SetOpenMode@CPK@@QAEXW4ECPKMode@@@Z`（data/gbengine_registry.jsonl:1044，A 级）
    的形参 1 必须以 **enum 形参**写进 IAT 槽数函数类型（`_GB_IMPORT_SIGS` 真实数据结构）。
    """
    m = _load_apply_annotations()
    sig = m._GB_IMPORT_SIGS['?SetOpenMode@CPK@@QAEXW4ECPKMode@@@Z']
    assert 'ECPKMode' in sig
    assert re.search(r'\benum\s+ECPKMode\b', sig), sig
    # mangled 解出的形参类型必须同为 enum 形参（与 decl 一致，位置 1）
    assert m._mangled_param_types('?SetOpenMode@CPK@@QAEXW4ECPKMode@@@Z') == ['enum ECPKMode']


def test_iat_sig_contains_enum_param():
    """mangled `W4gbAxis` 必须被解出 enum 形参（A 级：修饰名直接编码形参类型）。

    取证链（任务 4 §5）：
      `?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@M@Z`   ⇒ 形参 1 = enum gbAxis，形参 2 = float
      `?SetAxisAngle@gbMatrix4@@QAEXPAUgbVec3D@@M@Z` ⇒ 形参 1 = struct gbVec3D *
    """
    m = _load_apply_annotations()
    assert m._mangled_param_types('?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@M@Z') == [
        'enum gbAxis', 'float']
    assert m._mangled_param_types('?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@MM@Z') == [
        'enum gbAxis', 'float', 'float']
    assert m._mangled_param_types('?SetAxisAngle@gbMatrix4@@QAEXPAUgbVec3D@@M@Z') == [
        'struct gbVec3D *', 'float']
    assert m._mangled_param_types('?SetOpenMode@CPK@@QAEXW4ECPKMode@@@Z') == [
        'enum ECPKMode']
    # 无 enum 的普通成员不受影响（回归护栏）
    assert m._mangled_param_types('?Read@gbVFileSystem@@QAEXPAXIPAVgbVFile@@@Z') == [
        'void *', 'unsigned int', 'class gbVFile *']


def test_existing_enum_short_circuit_does_not_drop_declared_params():
    """:2186 3b 步对已存在 enum 的整体短路，不得让 enums.json 已声明的值静默丢失。

    实测形态（任务 4 §1）：IDB TIL 里 `gbAxis` 已有成员 GB_AXIS_X/Y/Z=0/1/2
    （来自 include/gbengine/gbengine_types.h 的 parse_decls），而 enums.json 声明
    GB_AXIS_0/1/2=0/1/2。旧代码 `if idc.get_enum(ename) != -1: continue` 会把这三个
    **已声明值**整体丢弃且不留痕。新语义：逐项处置（add/keep/alias/conflict），
    每个已声明 (name,value) 都必须出现在处置表里。
    """
    m = _load_apply_annotations()
    # 场景 1：同名同值（ECPKMode 形态）—— 处置必须是 keep，不得再丢
    plan = m._enum_merge_plan(
        {'CPKM_Null': 0, 'CPKM_Normal': 1},
        {'CPKM_Null': '0', 'CPKM_Normal': '1', 'CPKM_End': '4'})
    assert plan == [('keep', 'CPKM_Null', 0), ('keep', 'CPKM_Normal', 1),
                    ('add', 'CPKM_End', 4)]
    # 场景 2：值被别的名字占用（gbAxis 形态）—— 显式 alias 处置，不静默
    plan = m._enum_merge_plan(
        {'GB_AXIS_X': 0, 'GB_AXIS_Y': 1, 'GB_AXIS_Z': 2},
        {'GB_AXIS_0': '0', 'GB_AXIS_1': '1', 'GB_AXIS_2': '2'})
    assert [(a, n) for a, n, _v in plan] == [
        ('alias', 'GB_AXIS_0'), ('alias', 'GB_AXIS_1'), ('alias', 'GB_AXIS_2')]
    assert [v for _a, _n, v in plan] == [0, 1, 2]
    # 场景 3：同名不同值 —— 显式 conflict，不覆盖既有信息
    plan = m._enum_merge_plan({'E': 7}, {'E': '9'})
    assert plan == [('conflict', 'E', 9)]
    # 不变量：处置表恰好覆盖全部已声明项（= 没有任何声明被静默丢弃）
    declared = {'A': '1', 'B': '2', 'C': '3'}
    plan = m._enum_merge_plan({'B': 2}, declared)
    assert sorted((n, v) for _a, n, v in plan) == sorted(
        (n, int(v)) for n, v in declared.items())
    # 执行层：add 项逐个落 add_member，其余不写（幂等、不覆盖）
    written = []
    added, notes = m._enum_merge_apply(plan, lambda n, v: written.append((n, v)) or True)
    assert written == [('A', 1), ('C', 3)]
    assert added == 2 and len(notes) == 1


def test_iat_enum_upgrade_flag_and_no_int_downgrade():
    """:1585 early-return 前的 enum/int 错配判定 + 禁破坏性 workaround。

    `_fix_gbengine_import_slots` 的通用路径此前「参数个数够 + 约定对 + 非指针占位
    就 early return」⇒ 不会把 int 升级成 enum。新判定：mangled 是 enum 而槽里是
    整型占位 ⇒ 必须改写。反向护栏：白名单里凡是 mangled 带 W4 的形参，decl 里
    不得写成 int（禁止丢类型信息的破坏性 workaround）。
    """
    m = _load_apply_annotations()
    assert m._enum_upgrade_needed(['int', 'float'], ['enum gbAxis', 'float']) is True
    assert m._enum_upgrade_needed(['_DWORD', 'float'], ['enum gbAxis', 'float']) is True
    assert m._enum_upgrade_needed(['enum gbAxis', 'float'],
                                  ['enum gbAxis', 'float']) is False
    assert m._enum_upgrade_needed(['int', 'float'], ['int', 'float']) is False
    # 长度不一致（对齐失败）不得误判
    assert m._enum_upgrade_needed(['int'], ['enum gbAxis', 'float']) is False
    # 未解析出名字的 enum（反引用）不得盲注入
    assert m._enum_upgrade_needed(['int', 'float'], ['enum ?', 'float']) is False

    for mangled, decl in m._GB_IMPORT_SIGS.items():
        params = m._mangled_param_types(mangled)
        if not params:
            continue
        inner = decl.rstrip(';')[decl.index('(') + 1:decl.rindex(')')]
        decl_params = m._split_param_list(inner)   # 顶层逗号切分（不切函数指针内层）
        # decl 第 1 个形参是 this，其后与 mangled 形参一一对应
        assert len(decl_params) == len(params) + 1, (mangled, decl)
        for mp, dp in zip(params, decl_params[1:]):
            if re.match(r'^enum [A-Za-z_]\w*$', mp):
                # 禁破坏性 workaround：enum 形参不得退化成 int
                assert re.search(r'\b%s\b' % re.escape(mp), dp), (mangled, decl)
                assert dp != 'int', (mangled, decl)


if __name__ == '__main__':
    os.chdir(ROOT)   # 独立 runner 可从任意 cwd 启动
    tests = [test_enum_param_written_to_iat,
             test_iat_sig_contains_enum_param,
             test_existing_enum_short_circuit_does_not_drop_declared_params,
             test_iat_enum_upgrade_flag_and_no_int_downgrade]
    failed = 0
    for t in tests:
        try:
            t()
            print('PASS %s' % t.__name__)
        except AssertionError as e:
            failed += 1
            print('FAIL %s: %s' % (t.__name__, e))
        except Exception as e:
            failed += 1
            print('ERROR %s: %r' % (t.__name__, e))
    print('%d/%d passed' % (len(tests) - failed, len(tests)))
    raise SystemExit(1 if failed else 0)
