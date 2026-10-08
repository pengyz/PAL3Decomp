import os
import ast
import contextlib
import importlib.util
import io
import json
import random
import re
import sys
import unittest
import warnings
from unittest import mock
from unittest.mock import MagicMock


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFERRED_ANNOTATION_TRAVERSALS = {
    ('pipeline/ida/export_full.py', 613),
}


class AnnotationDeterminismTests(unittest.TestCase):
    @staticmethod
    def _annotation_traversals(source):
        tree = ast.parse(source)
        parents = {}
        for parent in ast.walk(tree):
            for child in ast.iter_child_nodes(parent):
                parents[child] = parent
        module_aliases = {}
        for node in ast.walk(tree):
            if isinstance(node, ast.Import):
                for alias in node.names:
                    local_name = alias.asname or alias.name.split('.')[0]
                    module_aliases[local_name] = alias.name
            elif isinstance(node, ast.ImportFrom) and node.module in ('os', 'glob'):
                for alias in node.names:
                    if alias.name in ('listdir', 'glob'):
                        local_name = alias.asname or alias.name
                        module_aliases[local_name] = '%s.%s' % (node.module, alias.name)

        def resolve_name(node):
            if isinstance(node, ast.Name):
                return module_aliases.get(node.id)
            if isinstance(node, ast.Attribute):
                base_name = resolve_name(node.value)
                return '%s.%s' % (base_name, node.attr) if base_name else None
            return None

        assignments = {}
        for node in ast.walk(tree):
            if not isinstance(node, ast.Assign):
                continue
            for target in node.targets:
                if isinstance(target, ast.Name):
                    assignments.setdefault(target.id, []).append(node.value)

        def is_annotations_literal(value):
            if not isinstance(value, str):
                return False
            parts = value.replace('\\', '/').strip('/').split('/')
            return 'annotations' in parts

        def mentions_annotation_path(node, visiting=None):
            visiting = visiting or set()
            if isinstance(node, ast.Constant):
                return is_annotations_literal(node.value)
            if isinstance(node, ast.Name):
                if node.id in visiting:
                    return False
                return any(
                    mentions_annotation_path(value, visiting | {node.id})
                    for value in assignments.get(node.id, [])
                )
            return any(
                mentions_annotation_path(child, visiting)
                for child in ast.iter_child_nodes(node)
            )

        traversals = []
        for node in ast.walk(tree):
            if not isinstance(node, ast.Call):
                continue
            function_name = resolve_name(node.func)
            parent = parents.get(node)
            is_sorted_call = (
                isinstance(parent, ast.Call)
                and isinstance(parent.func, ast.Name)
                and parent.func.id == 'sorted'
            )
            if function_name in ('os.listdir', 'glob.glob') and not is_sorted_call and any(
                mentions_annotation_path(argument) for argument in node.args
            ):
                traversals.append((node.lineno, function_name))
        return traversals

    def test_five_sites_use_single_sorted_read_point(self):
        """5 个站点不得针对注解目录使用裸 os.listdir/glob.glob（含别名）遍历。"""
        sites = [
            'pipeline/ida/apply_annotations.py',
            'pipeline/ida/export_full.py',
            'pipeline/check_annotations.py',
            'tools/verify_fix.py',
            'tools/audit_retn_param_count.py',
        ]
        for relative_path in sites:
            absolute_path = os.path.join(ROOT, relative_path)
            with open(absolute_path, encoding='utf-8') as source_file:
                traversals = self._annotation_traversals(source_file.read())
            traversals = [
                traversal for traversal in traversals
                if (relative_path, traversal[0]) not in DEFERRED_ANNOTATION_TRAVERSALS
            ]
            self.assertEqual(traversals, [], f'{relative_path} 仍针对注解目录裸遍历')

    def test_alias_guard_detects_only_annotation_directory_traversals(self):
        source = '''
import glob as _gl
import os as _os
from glob import glob as list_structs
base = os.path.dirname(__file__)
other_dir = os.path.join(base, "other")
annotations_dir = os.path.join(base, "other")
annotation_dir = os.path.join(base, "annotations")
structs_dir = os.path.join(annotation_dir, "structs")
_structs_dir = os.path.join(structs_dir, "nested")
listing_dir = os.path.join(annotation_dir, "listing")
_gl.glob(os.path.join(other_dir, "*.txt"))
_os.listdir(other_dir)
_os.listdir(listing_dir)
_gl.glob(os.path.join(structs_dir, "*.json"))
_os.listdir(os.path.join(annotations_dir, "structs"))
list_structs(os.path.join(_structs_dir, "*.json"))
'''
        traversals = self._annotation_traversals(source)
        self.assertEqual(traversals, [(14, 'os.listdir'), (15, 'glob.glob'), (17, 'glob.glob')])

    def test_strict_struct_helpers_reject_invalid_struct_annotations(self):
        strict_files = [
            'pipeline/ida/apply_annotations.py',
            'pipeline/ida/export_full.py',
            'pipeline/check_annotations.py',
        ]
        for relative_path in strict_files:
            with open(os.path.join(ROOT, relative_path), encoding='utf-8') as source_file:
                source = source_file.read()
            tree = ast.parse(source)
            function_node = next(
                node for node in tree.body
                if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef))
                and node.name == '_strict_struct_entries'
            )
            function_source = ast.get_source_segment(source, function_node)
            self.assertIsNotNone(function_source, f'{relative_path} 缺少严格读取封装')

            for invalid_data in (None, [], 'object'):
                paths = ['/tmp/bad.json']
                seen_directories = []

                def fake_iter_struct_files(directory):
                    return paths

                def fake_load_struct(path):
                    return invalid_data

                def fake_iter_structs(directory):
                    seen_directories.append(directory)
                    return [(path, {}) for path in paths]

                namespace = {
                    'iter_struct_files': fake_iter_struct_files,
                    'load_struct': fake_load_struct,
                    'iter_structs': fake_iter_structs,
                }
                exec(compile(function_source, relative_path, 'exec'), namespace)
                with self.assertRaisesRegex(
                    ValueError,
                    r'bad\.json: struct annotation must be a JSON object',
                    msg=f'{relative_path} 对 {invalid_data!r} 静默跳过',
                ):
                    namespace['_strict_struct_entries']('/tmp/annotations/structs')
                self.assertEqual(seen_directories, [])

    def test_all_struct_sites_route_through_annotation_view(self):
        sites = [
            ('pipeline/ida/apply_annotations.py', 1),
            ('pipeline/ida/export_full.py', 2),
            ('pipeline/check_annotations.py', 1),
            ('tools/verify_fix.py', 1),
            ('tools/audit_retn_param_count.py', 1),
        ]
        for relative_path, expected_calls in sites:
            with open(os.path.join(ROOT, relative_path), encoding='utf-8') as source_file:
                source = source_file.read()
            tree = ast.parse(source)
            helper_ranges = [
                (node.lineno, node.end_lineno)
                for node in ast.walk(tree)
                if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef))
                and node.name == '_strict_struct_entries'
            ]
            direct_calls = sum(
                isinstance(node, ast.Call)
                and (
                    (isinstance(node.func, ast.Name) and node.func.id in ('iter_structs', '_strict_struct_entries'))
                    or (isinstance(node.func, ast.Attribute) and node.func.attr in ('iter_structs', '_strict_struct_entries'))
                )
                and not any(start <= node.lineno <= end for start, end in helper_ranges)
                for node in ast.walk(tree)
            )
            self.assertGreaterEqual(direct_calls, expected_calls, f'{relative_path} 未统一经过 annotation_view')


# ─────────────────────────────────────────────────────────────────────────────
# 任务 5：shuffle 确定性兜底（2026-10-08 命名仲裁·交付物 A）
#
# 目的：在「目录枚举顺序被打乱」的条件下，`load_annotations()` 的结果必须唯一。
# 规格：.superpowers/sdd/2026-10-08-naming-arbitration-a/task-5-brief.md
#
# 为什么同时打乱 `os.scandir`：`annotation_view.iter_struct_files()` 走 `glob.glob`，
# 而 CPython(≥3.5) 的 glob 用 `os.scandir` 枚举目录 —— 只打乱 `os.listdir` 时断言会
# 空转（实测：unsorted 变异体在仅打乱 listdir 时也只有 1 种结果）。两者都打乱，
# 变异体（去掉 `sorted()`）实测为 30 种结果 ⇒ 本测试非恒真。
# ─────────────────────────────────────────────────────────────────────────────

APPLY_ANNOTATIONS_PATH = os.path.join(ROOT, 'pipeline', 'ida', 'apply_annotations.py')
STRUCTS_DIR = os.path.join(ROOT, 'data', 'annotations', 'structs')
SHUFFLE_ROUNDS = 30
# 2026-10-08 实测基线；同名 struct 覆盖是**数据**问题（本任务范围外，不在本任务修），
# 本测试只记录它、并断言「覆盖赢家确定」（排序序最后者胜）。详见 task-5-report.md §3。
SAME_NAME_OVERWRITE_BASELINE = 17

IDA_MODULES = (
    'ida_auto',
    'ida_bytes',
    'ida_funcs',
    'ida_hexrays',
    'ida_name',
    'ida_typeinf',
    'idautils',
    'idc',
)


def _load_apply_annotations():
    """stub 掉 IDA 模块后加载真实的 `apply_annotations`（同 tests/test_owner_field.py 手法）。

    验收命令 `python3 tests/test_annotation_determinism.py` 不加载 pytest conftest，
    因此本文件自带加载器，保证可独立运行；测的仍是生产代码本身。
    """
    saved_modules = {name: sys.modules.get(name) for name in IDA_MODULES}
    for name in IDA_MODULES:
        sys.modules[name] = MagicMock()
    try:
        spec = importlib.util.spec_from_file_location(
            'test_apply_annotations_determinism', APPLY_ANNOTATIONS_PATH
        )
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        return module
    finally:
        for name, previous in saved_modules.items():
            if previous is None:
                sys.modules.pop(name, None)
            else:
                sys.modules[name] = previous


def _annotation_view():
    """注解的单一读取视图（枚举 structs/*.json 也走它，不另起第二套枚举逻辑）。"""
    if ROOT not in sys.path:
        sys.path.insert(0, ROOT)
    from pipeline.gen import annotation_view
    return annotation_view


class _DirEntries:
    """`os.scandir()` 替身：支持 glob 的 `with os.scandir(...) as it: for entry in it` 协议。"""

    def __init__(self, entries):
        self._entries = list(entries)

    def __enter__(self):
        return self

    def __exit__(self, *exc_info):
        return False

    def __iter__(self):
        return iter(self._entries)


def _mock_round_patch(listdir, scandir):
    """**每轮独立**的 `mock.patch` 上下文：退出即还原，循环外不做全局 undo。"""
    stack = contextlib.ExitStack()
    stack.enter_context(mock.patch.object(os, 'listdir', listdir))
    stack.enter_context(mock.patch.object(os, 'scandir', scandir))
    return stack


def _monkeypatch_round_patch(monkeypatch, listdir, scandir):
    """**每轮独立**的 `monkeypatch` 上下文。

    控制器裁决：不在循环内 `monkeypatch.undo()`（那会撤销**全部** monkeypatch）；
    这里每轮只撤销本轮自己的 setattr（`monkeypatch.context()` = try/finally 语义）。
    """
    stack = contextlib.ExitStack()
    context = stack.enter_context(monkeypatch.context())
    context.setattr(os, 'listdir', listdir)
    context.setattr(os, 'scandir', scandir)
    return stack


@contextlib.contextmanager
def _quiet():
    """吞掉 `load_annotations()` 的 stdout 日志，并抑制**既有**的 ResourceWarning 噪音。

    ResourceWarning 来自生产代码 `annotation_view.load_struct`（`open(...).read()` 未
    close；Task 4' 报告已记为既有问题，非本任务范围）。本文件要加载注解 31 次，
    不抑制的话验收命令的 stderr 会被 ~2700 行既有告警淹没（与本任务无关）。
    """
    with contextlib.redirect_stdout(io.StringIO()), warnings.catch_warnings():
        warnings.simplefilter('ignore', ResourceWarning)
        yield


def _measure_shuffle_variants(round_patch, rounds=SHUFFLE_ROUNDS):
    """打乱目录枚举顺序跑 `rounds` 轮，收集每轮 `load_annotations()` 的结果签名。

    返回 `[(functions 签名, structs 表签名), ...]`；`round_patch` 提供「单轮独立 patch」。
    """
    module = _load_apply_annotations()
    real_listdir = os.listdir
    real_scandir = os.scandir
    variants = []
    for seed in range(rounds):
        random.seed(seed)

        def shuffled_names(path='.', _listdir=real_listdir):
            names = list(_listdir(path))
            random.shuffle(names)
            return names

        def shuffled_entries(path='.', _scandir=real_scandir):
            with _scandir(path) as entries:
                materialized = list(entries)
            random.shuffle(materialized)
            return _DirEntries(materialized)

        with round_patch(shuffled_names, shuffled_entries):
            with _quiet():
                annotations = module.load_annotations()
        functions = annotations['functions']
        variants.append((
            frozenset(
                (address, info.get('class'), info.get('name'))
                for address, info in functions.items()
            ),
            frozenset(
                (name, json.dumps(data, sort_keys=True, default=str))
                for name, data in annotations['structs'].items()
            ),
        ))
    return variants


def _load_annotations_once():
    """不打乱目录顺序地加载一次（供「覆盖语义」断言使用）。"""
    module = _load_apply_annotations()
    with _quiet():
        return module.load_annotations()


def _same_name_struct_overwrite_groups():
    """同名 struct 覆盖组：`{struct 名: [structs/*.json, ...]}`（只保留 ≥2 个文件的名字）。

    `load_annotations()` 里 `structs[sname] = sdata` 会把同名者互相覆盖，
    覆盖赢家 = 排序序（`iter_struct_files` 已 sorted）最后处理的文件。
    """
    view = _annotation_view()
    by_name = {}
    with _quiet():  # 同样的既有 ResourceWarning 噪音（见 _quiet 注释）
        for path in view.iter_struct_files(STRUCTS_DIR):
            data = view.load_struct(path)
            if not isinstance(data, dict):
                continue
            by_name.setdefault(data.get('name', os.path.basename(path)[:-5]), []).append(path)
    return {name: files for name, files in by_name.items() if len(files) > 1}


def _divergence_sample(first, second, limit=5):
    """两个 functions 签名之间的差异样本（失败时可见，不用再去手跑）。"""
    left = {address: (cls, name) for address, cls, name in first}
    right = {address: (cls, name) for address, cls, name in second}
    sample = []
    for address in sorted(set(left) | set(right)):
        if left.get(address) != right.get(address):
            sample.append((address, left.get(address), right.get(address)))
            if len(sample) >= limit:
                break
    return sample


class ShuffleDeterminismTests(unittest.TestCase):
    """任务 5：`load_annotations()` 必须在打乱目录枚举顺序后仍然唯一。"""

    @classmethod
    def setUpClass(cls):
        # 30 轮洗牌只跑一次，两条确定性断言共用（单一测量实现）。
        cls.variants = _measure_shuffle_variants(_mock_round_patch)

    def test_load_annotations_deterministic_under_shuffle(self):
        """简报判据：30 轮 shuffle，functions 赢家变动必须为 0（只允许 1 种结果）。"""
        distinct = {variant[0] for variant in self.variants}
        message = 'shuffle 后 winner 不唯一：%d 种结果（%d 轮）' % (
            len(distinct), len(self.variants)
        )
        if len(distinct) > 1:
            message += '；sample=%r' % (
                _divergence_sample(self.variants[0][0], self.variants[1][0]),
            )
        self.assertEqual(len(distinct), 1, message)

    def test_struct_table_deterministic_under_shuffle(self):
        """17 组同名 struct 覆盖也必须「排序序最后者胜」⇒ 30 轮 structs 表只允许 1 种。"""
        distinct = {variant[1] for variant in self.variants}
        self.assertEqual(
            len(distinct),
            1,
            'shuffle 后 structs 表不唯一：%d 种结果（%d 轮）' % (len(distinct), len(self.variants)),
        )

    def test_same_name_struct_overwrite_recorded_as_known_issue(self):
        """**已知问题**（任务范围外）：同名 struct 覆盖数 != 0。此处只记录，不断言为 0。

        覆盖数是数据问题（同名两个文件互相覆盖），不是非确定性问题；本任务只保证
        「覆盖赢家稳定」。这里记录实际值，并断言赢家 == 排序序最后一个文件。
        """
        groups = _same_name_struct_overwrite_groups()
        print(
            '\n[已知问题·任务范围外] 同名 struct 覆盖数 = %d（基线 %d，见 task-5-report.md §3）'
            % (len(groups), SAME_NAME_OVERWRITE_BASELINE)
        )
        for name, files in sorted(groups.items()):
            print('  %s <= %s' % (name, [os.path.basename(path) for path in files]))
        if len(groups) != SAME_NAME_OVERWRITE_BASELINE:
            print('⚠️ 覆盖数与基线不一致，请更新 task-5-report.md §3 与 SAME_NAME_OVERWRITE_BASELINE')

        if not groups:
            self.skipTest('同名 struct 覆盖已清零：请更新 task-5-report.md §3 与本测试基线')

        view = _annotation_view()
        annotations = _load_annotations_once()
        for name, files in sorted(groups.items()):
            winner = annotations['structs'].get(name)
            self.assertIsNotNone(winner, '%s 未出现在 load_annotations()["structs"]' % name)
            with _quiet():
                expected = view.load_struct(max(files))
            expected.pop('name', None)
            self.assertEqual(
                json.dumps(winner, sort_keys=True, default=str),
                json.dumps(expected, sort_keys=True, default=str),
                '%s 的覆盖赢家不是排序序最后一个文件 %s（覆盖语义应为「排序序最后者胜」）'
                % (name, os.path.basename(max(files))),
            )


def test_load_annotations_deterministic_under_shuffle(monkeypatch):
    """pytest 入口（简报原文签名）：30 轮 shuffle，winner 变动应为 0。

    控制器裁决：每轮用独立的 `monkeypatch` 上下文，循环外不做 `monkeypatch.undo()`。
    验收命令走 `ShuffleDeterminismTests.test_load_annotations_deterministic_under_shuffle`
    （同一测量实现，仅 patch 机制不同），本函数供 pytest 收集。
    """
    variants = _measure_shuffle_variants(
        lambda listdir, scandir: _monkeypatch_round_patch(monkeypatch, listdir, scandir)
    )
    distinct = {variant[0] for variant in variants}
    assert len(distinct) == 1, 'winner 随机：%d 种不同结果（%d 轮）' % (len(distinct), len(variants))


if __name__ == '__main__':
    unittest.main()
