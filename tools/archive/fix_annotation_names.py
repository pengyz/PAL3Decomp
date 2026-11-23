"""Fix annotation names based on decomp JSON evidence.

Usage: python tools/fix_annotation_names.py
"""
import json, os, glob


# ---- 2026-09-20 审计 P2-4：无参数解析工具的统一护栏 ----------------------------
# 本工具**会写盘**且**没有任何 argparse/sys.argv 处理** ⇒ 传任何 `-` 开头的参数
# （最典型的是 `--help`）此前会被当作普通输入，**执行全流程并覆盖产物**。
# 本次审计期间已因此发生 **2 起事故**（`sig_evidence.py` 删掉 6020 行、
# `misattribution_ledger.py` 把 197 cluster 改写成 3）。
# 统一护栏：见到任何以 `-` 开头的参数即打印用法并**退出，不执行任何工作**。
import sys as _sys_guard
if any(_a.startswith('-') for _a in _sys_guard.argv[1:]):
    print('[%s] 本工具不接受命令行开关；收到 %r ⇒ 不执行任何操作。'
          % (__file__.rsplit('/', 1)[-1], _sys_guard.argv[1:]))
    print('用法: python3 %s    # 无参数，直接运行' % __file__)
    _sys_guard.exit(0)
# ---------------------------------------------------------------------------

def load_json(path):
    for enc in ['utf-8', 'gbk', 'latin-1']:
        try:
            with open(path, encoding=enc) as f:
                return json.load(f)
        except (UnicodeDecodeError, json.JSONDecodeError):
            continue
    return None

def save_json(path, data):
    with open(path, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
        f.write('\n')

ann_dir = 'data/annotations/structs'

# Map of address -> correct name (verified from decomp JSON)
fixes = {
    '0x0043DDF0': 'CCBControlWindow::Render',
    '0x0043DE40': 'CCBRoleState::Destroy',
    '0x00524970': 'CCBRoleState::Render',
    '0x0051C9B0': 'CCBFiveNimbusWindow::OnMessage',
}

fixed_count = 0
for ann_file in sorted(os.listdir(ann_dir)):
    if not ann_file.endswith('.json'):
        continue
    path = f'{ann_dir}/{ann_file}'
    ann = load_json(path)
    if not ann or 'methods' not in ann:
        continue
    changed = False
    for addr, correct_name in fixes.items():
        if addr in ann['methods']:
            old_name = ann['methods'][addr]['name']
            if old_name != correct_name:
                print(f'{ann_file}: {addr} "{old_name}" -> "{correct_name}"')
                ann['methods'][addr]['name'] = correct_name
                changed = True
                fixed_count += 1
    if changed:
        save_json(path, ann)

print(f'\nFixed {fixed_count} entries across {len(fixes)} addresses')
