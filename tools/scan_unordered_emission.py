"""S-1b：set/dict 无序迭代进入文本产出路径的静态扫描（第一版 report-only）。

背景（2026-10-09 对抗复核）：
  `_forced_global_entries()` 遍历 set 产 extra，导致 globals.cpp 尾块行序逐进程漂移。
  同款模式可能存在于其他生成路径。本扫描器**宁可漏报，不用不存在的函数充数**。

判据（可操作）：
  for 循环的可迭代对象是 set / frozenset / dict.keys() / dict.values()，
  且该 for 未被 sorted(...) 包裹  => 列为候选。

⚠️ 第一版 **report-only**（不 assert 空）—— AST 浅层扫描必然误报：
   set 迭代用于仅做 membership/filter 时语法上与「迭代后拼进输出」无法仅靠语法区分。
   人工复核后把「确认有害」的位点列为待修，「无害」的列入白名单；误报率稳定后再考虑转硬门禁。
"""
import ast
import pathlib

REPO = pathlib.Path(__file__).resolve().parents[1]

CANDIDATES = (
    ('pipeline/gen/stages/emit_headers.py', 'emit_headers'),
    ('pipeline/gen/stages/emit_cpp.py', 'emit_cpp'),
    ('pipeline/gen/stages/stage2_semantic.py', 'stage2_semantic'),
    ('pipeline/gen/stages/stage3_cleanup.py', 'stage3_cleanup'),
    ('pipeline/gen/stages/stage4_substitution.py', 'stage4_substitution'),
    ('pipeline/gen/stages/stage5_fixup.py', 'stage5_fixup'),
    ('pipeline/gen/collect.py', 'collect'),
    ('pipeline/gen/data.py', 'data'),
)


def _is_unordered_iterable(node):
    """可迭代对象是 set / frozenset / dict.keys() / dict.values()？"""
    if isinstance(node, (ast.Set, ast.SetComp)):
        return True
    if isinstance(node, ast.Call):
        f = node.func
        if isinstance(f, ast.Name) and f.id in ('set', 'frozenset'):
            return True
        if isinstance(f, ast.Attribute) and f.attr in ('keys', 'values', 'items'):
            return True
    # 名字绑定到 set() 调用的变量：浅层识别（漏报可接受）
    if isinstance(node, ast.Name):
        return None        # 未知，交人工
    return False


def _wrapped_in_sorted(for_node):
    """该 for 的 iter 是否是 sorted(...) 的结果？"""
    it = for_node.iter
    return (isinstance(it, ast.Call) and isinstance(it.func, ast.Name)
            and it.func.id == 'sorted')


def scan_unordered_emission(root: pathlib.Path):
    """返回候选清单：['<path>:<lineno>  for <target> in ...']"""
    out = []
    for rel, _tag in CANDIDATES:
        p = root / rel
        if not p.exists():
            continue
        try:
            tree = ast.parse(p.read_text(encoding='utf-8'))
        except SyntaxError as e:
            out.append('%s: <parse error %s>' % (p, e))
            continue
        for node in ast.walk(tree):
            if not isinstance(node, ast.For):
                continue
            if _wrapped_in_sorted(node):
                continue
            verdict = _is_unordered_iterable(node.iter)
            if verdict is True:
                out.append('%s:%d  for %s in <%s>'
                           % (p, node.lineno, ast.unparse(node.target),
                              ast.unparse(node.iter)[:60]))
            elif verdict is None:
                out.append('%s:%d  [UNKNOWN-ITER] for %s in %s'
                           % (p, node.lineno, ast.unparse(node.target),
                              ast.unparse(node.iter)[:60]))
    return out


def main():
    v = scan_unordered_emission(REPO)
    report = REPO / 'data' / 'status' / '_s1b_unordered_emission.md'
    lines = [
        '# S-1b 无序迭代候选清单（report-only，非门禁）',
        '',
        '生成时间：%s' % __import__('datetime').datetime.now().isoformat(timespec='seconds'),
        '判据：for 的可迭代对象是 set/frozenset/dict.keys()/dict.values() 且未被 sorted() 包裹。',
        '⚠️ AST 浅层扫描必然误报（membership/filter 用途语法上无法区分）⇒ 人工复核后才可定性。',
        '',
        '## 候选（%d 条）' % len(v),
        '',
    ]
    lines += ['- `%s`' % s for s in v] if v else ['(clean)']
    report.write_text('\n'.join(lines) + '\n', encoding='utf-8')
    print('候选 %d 条 -> %s' % (len(v), report))
    for s in v[:40]:
        print('  ', s)
    return v


if __name__ == '__main__':
    main()
