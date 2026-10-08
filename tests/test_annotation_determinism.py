import os
import re
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


class AnnotationDeterminismTests(unittest.TestCase):
    def test_five_sites_use_single_sorted_read_point(self):
        """5 个站点不得针对注解目录使用裸 os.listdir/glob.glob 遍历。"""
        sites = [
            'pipeline/ida/apply_annotations.py',
            'pipeline/ida/export_full.py',
            'pipeline/check_annotations.py',
            'tools/verify_fix.py',
            'tools/audit_retn_param_count.py',
        ]
        bad_call = re.compile(r'(?<!sorted\()\b(?:os\.listdir|glob\.glob)\s*\(')
        annotation_dir_line = re.compile(r'\bannotations?\b|\bstructs?_dir\b', re.IGNORECASE)

        for relative_path in sites:
            absolute_path = os.path.join(ROOT, relative_path)
            with open(absolute_path, encoding='utf-8') as source_file:
                for line_number, line in enumerate(source_file, 1):
                    self.assertFalse(
                        bad_call.search(line) and annotation_dir_line.search(line),
                        f'{relative_path}:{line_number} 仍针对注解目录裸遍历: {line.strip()}',
                    )


if __name__ == '__main__':
    unittest.main()
