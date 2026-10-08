import os
import ast
import re
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


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

        def mentions_annotation_path(node):
            if isinstance(node, ast.Name):
                text = node.id
            elif isinstance(node, ast.Constant) and isinstance(node.value, str):
                text = node.value
            else:
                return any(mentions_annotation_path(child) for child in ast.iter_child_nodes(node))
            return text.lower() in ('ann_dir', 'annotations_dir') or bool(
                re.search(r'annotations?\b|structs?_dir\b', text, re.IGNORECASE)
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
            self.assertEqual(traversals, [], f'{relative_path} 仍针对注解目录裸遍历')

    def test_alias_guard_detects_only_annotation_directory_traversals(self):
        source = '''
import glob as _gl
import os as _os
from glob import glob as list_structs
_gl.glob(os.path.join(other_dir, "*.txt"))
_os.listdir(other_dir)
_gl.glob(os.path.join(structs_dir, "*.json"))
_os.listdir(os.path.join(annotations_dir, "structs"))
list_structs(os.path.join(_structs_dir, "*.json"))
'''
        traversals = self._annotation_traversals(source)
        self.assertEqual(traversals, [(7, 'glob.glob'), (8, 'os.listdir'), (9, 'glob.glob')])

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
                tree = ast.parse(source_file.read())
            direct_calls = sum(
                isinstance(node, ast.Call)
                and ((isinstance(node.func, ast.Name) and node.func.id in ('iter_structs', '_strict_struct_entries'))
                     or (isinstance(node.func, ast.Attribute) and node.func.attr in ('iter_structs', '_strict_struct_entries')))
                for node in ast.walk(tree)
            )
            self.assertGreaterEqual(direct_calls, expected_calls, f'{relative_path} 未统一经过 annotation_view')


if __name__ == '__main__':
    unittest.main()
