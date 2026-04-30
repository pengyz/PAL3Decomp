#!/usr/bin/env python3
"""
Demangle DLL 导出的 MSVC C++ 名称，生成类/方法索引。

用法：
    python demangle_exports.py                # 处理所有目标 DLL
    python demangle_exports.py topo.dll       # 处理指定 DLL
    python demangle_exports.py --header       # 生成 C++ 头文件
"""

import argparse
import json
import sys
from collections import defaultdict
from pathlib import Path

try:
    import undname
except ImportError:
    print("[!] 需要 undname 包: pip install undname")
    sys.exit(1)

PROJECT_ROOT = Path(__file__).parent.parent
BUILD_DIR = PROJECT_ROOT / "build"
INCLUDE_DIR = PROJECT_ROOT / "include"

TARGET_DLLS = ['topo', 'gbengine']


def load_exports(dll_name):
    """加载之前生成的导出 JSON"""
    path = BUILD_DIR / "{}_exports.json".format(dll_name)
    if not path.exists():
        print("[!] 未找到 {} — 请先运行 analyze_dll_exports.py".format(path))
        return None
    with open(path) as f:
        return json.load(f)


def demangle_name(mangled):
    """Demangle 单个 MSVC C++ 名称"""
    try:
        return undname.undname(mangled)
    except Exception:
        return mangled


def parse_demangled(demangled):
    """从 demangled 字符串中提取结构化信息"""
    info = {
        'full': demangled,
        'class_name': '',
        'method_name': '',
        'return_type': '',
        'params': '',
        'calling_conv': '',
        'access': '',
        'is_static': False,
        'is_virtual': False,
        'is_const': False,
        'is_constructor': False,
        'is_destructor': False,
    }

    # 解析 access specifier
    for acc in ('public:', 'protected:', 'private:'):
        if demangled.startswith(acc):
            info['access'] = acc.rstrip(':')
            demangled = demangled[len(acc):].strip()
            break

    # static/virtual
    if demangled.startswith('static '):
        info['is_static'] = True
        demangled = demangled[7:]
    if demangled.startswith('virtual '):
        info['is_virtual'] = True
        demangled = demangled[8:]

    # 查找 class::method 模式
    # 格式通常是: return_type calling_conv class::method(params)
    # 或 constructor: class::class(params)
    paren_pos = demangled.find('(')
    if paren_pos > 0:
        before_paren = demangled[:paren_pos]
        after_paren = demangled[paren_pos:]

        # 提取参数
        info['params'] = after_paren

        # 找 :: 来分离类名和方法名
        # 从右往左找 :: （因为返回类型中也可能有 ::）
        dcolon_pos = before_paren.rfind('::')
        if dcolon_pos > 0:
            method_part = before_paren[dcolon_pos+2:]
            class_and_ret = before_paren[:dcolon_pos]

            info['method_name'] = method_part.strip()

            # class_and_ret 可能是 "return_type calling_conv class"
            # 或者对构造函数是 "calling_conv class"
            # 尝试提取类名（最后一个空格后的部分）
            parts = class_and_ret.rsplit(' ', 1)
            if len(parts) == 2:
                info['class_name'] = parts[1].strip()
                # 剩余部分可能包含返回类型和调用约定
                remainder = parts[0].strip()
                for conv in ('__cdecl', '__thiscall', '__stdcall', '__fastcall'):
                    if conv in remainder:
                        info['calling_conv'] = conv
                        remainder = remainder.replace(conv, '').strip()
                info['return_type'] = remainder
            else:
                info['class_name'] = parts[0].strip()

            # 检查构造/析构
            if info['method_name'] == info['class_name']:
                info['is_constructor'] = True
            elif info['method_name'] == '~' + info['class_name']:
                info['is_destructor'] = True

        # const 方法
        if after_paren.rstrip().endswith('const'):
            info['is_const'] = True

    return info


def process_dll(dll_name):
    """处理单个 DLL 的所有导出"""
    data = load_exports(dll_name)
    if data is None:
        return None

    results = {
        'dll_name': data['dll_name'],
        'num_exports': data['num_exports'],
        'classes': defaultdict(lambda: {
            'methods': [],
            'constructors': 0,
            'destructors': 0,
            'static_methods': 0,
            'virtual_methods': 0,
        }),
        'global_functions': [],
    }

    all_exports = []

    # 处理类中的方法
    for class_name, class_data in data['classes'].items():
        for method in class_data['methods']:
            mangled = method['mangled']
            demangled = demangle_name(mangled)
            parsed = parse_demangled(demangled)

            entry = {
                'mangled': mangled,
                'demangled': demangled,
                'rva': method['rva'],
                'ordinal': method['ordinal'],
                'parsed': parsed,
            }
            all_exports.append(entry)

            # 归类
            cname = parsed['class_name'] or '(global)'
            cls = results['classes'][cname]
            cls['methods'].append(entry)
            if parsed['is_constructor']:
                cls['constructors'] += 1
            if parsed['is_destructor']:
                cls['destructors'] += 1
            if parsed['is_static']:
                cls['static_methods'] += 1
            if parsed['is_virtual']:
                cls['virtual_methods'] += 1

    # 处理 plain exports
    for exp in data.get('plain_exports', []):
        demangled = demangle_name(exp['name'])
        entry = {
            'mangled': exp['name'],
            'demangled': demangled,
            'rva': exp['rva'],
            'ordinal': exp['ordinal'],
        }
        all_exports.append(entry)
        results['global_functions'].append(entry)

    results['all_exports'] = all_exports
    return results


def print_class_summary(results, dll_name):
    """打印类摘要"""
    print()
    print("{} 类结构摘要".format(dll_name))
    print("=" * 70)
    print()
    print("{:<25s} {:>5s} {:>5s} {:>5s} {:>5s} {:>7s}".format(
        "Class", "Total", "Ctor", "Dtor", "Stat", "Virtual"))
    print("-" * 70)

    sorted_classes = sorted(
        results['classes'].items(),
        key=lambda x: -len(x[1]['methods']))

    for cname, cdata in sorted_classes:
        if cname == '(global)':
            continue
        print("{:<25s} {:>5d} {:>5d} {:>5d} {:>5d} {:>7d}".format(
            cname[:25],
            len(cdata['methods']),
            cdata['constructors'],
            cdata['destructors'],
            cdata['static_methods'],
            cdata['virtual_methods']))

    # 全局函数
    globals_class = results['classes'].get('(global)', {'methods': []})
    if globals_class['methods']:
        print()
        print("全局/命名空间函数: {} 个".format(len(globals_class['methods'])))


def print_class_detail(results, class_name):
    """打印某个类的详细方法列表"""
    cdata = results['classes'].get(class_name)
    if cdata is None:
        print("[!] 类 '{}' 不存在".format(class_name))
        return

    print()
    print("class {} {{".format(class_name))

    # 按类别分组
    ctors = []
    dtors = []
    methods = []

    for m in cdata['methods']:
        p = m['parsed']
        if p['is_constructor']:
            ctors.append(m)
        elif p['is_destructor']:
            dtors.append(m)
        else:
            methods.append(m)

    if ctors:
        print("  // Constructors")
        for m in ctors:
            print("  {};".format(m['demangled']))
    if dtors:
        print("  // Destructor")
        for m in dtors:
            print("  {};".format(m['demangled']))
    if methods:
        print("  // Methods")
        for m in sorted(methods, key=lambda x: x['parsed']['method_name']):
            print("  {};  // RVA=0x{:X}".format(
                m['demangled'], m['rva']))

    print("};")


def generate_header(results, dll_name):
    """生成 C++ 头文件"""
    lines = []
    lines.append("#pragma once")
    lines.append("/**")
    lines.append(" * Auto-generated from {}.dll export table".format(dll_name))
    lines.append(" * {} exported functions".format(results['num_exports']))
    lines.append(" *")
    lines.append(" * NOTE: This is a reference file showing the DLL's API surface.")
    lines.append(" * Parameter names are inferred and may not match original source.")
    lines.append(" */")
    lines.append("")
    lines.append("#ifndef {}_API_H".format(dll_name.upper()))
    lines.append("#define {}_API_H".format(dll_name.upper()))
    lines.append("")
    lines.append('#include "pal3_types.h"')
    lines.append("")

    sorted_classes = sorted(
        results['classes'].items(),
        key=lambda x: -len(x[1]['methods']))

    for cname, cdata in sorted_classes:
        if cname == '(global)' or not cname:
            continue

        lines.append("// {} methods".format(len(cdata['methods'])))
        lines.append("class {} {{".format(cname))
        lines.append("public:")

        for m in sorted(cdata['methods'], key=lambda x: (
                not x['parsed']['is_constructor'],
                not x['parsed']['is_destructor'],
                x['parsed']['method_name'])):
            # 简化 demangled 名称为声明形式
            decl = m['demangled']
            # 去掉 access specifier
            for prefix in ('public: ', 'protected: ', 'private: '):
                if decl.startswith(prefix):
                    decl = decl[len(prefix):]

            lines.append("    {};  // 0x{:X}".format(decl.rstrip(), m['rva']))

        lines.append("};")
        lines.append("")

    lines.append("#endif // {}_API_H".format(dll_name.upper()))
    return '\n'.join(lines)


def save_results(results, dll_name):
    """保存 demangle 结果"""
    # 保存完整 JSON
    output = {
        'dll_name': results['dll_name'],
        'num_exports': results['num_exports'],
        'classes': {},
        'global_functions': results['global_functions'],
    }

    for cname, cdata in results['classes'].items():
        output['classes'][cname] = {
            'method_count': len(cdata['methods']),
            'constructors': cdata['constructors'],
            'destructors': cdata['destructors'],
            'static_methods': cdata['static_methods'],
            'virtual_methods': cdata['virtual_methods'],
            'methods': [{
                'mangled': m['mangled'],
                'demangled': m['demangled'],
                'rva': m['rva'],
                'ordinal': m['ordinal'],
            } for m in cdata['methods']],
        }

    output_path = BUILD_DIR / "{}_demangled.json".format(dll_name)
    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(output, f, indent=2, ensure_ascii=False)
    print("完整结果已保存: {}".format(output_path))
    return output_path


def main():
    parser = argparse.ArgumentParser(
        description="Demangle DLL 导出的 MSVC C++ 名称")
    parser.add_argument('dll_name', nargs='?',
                        help='DLL 名称（不含 .dll 后缀），默认处理所有')
    parser.add_argument('--header', action='store_true',
                        help='生成 C++ 头文件')
    parser.add_argument('--class', dest='show_class',
                        help='显示指定类的详细方法列表')
    parser.add_argument('--list-classes', action='store_true',
                        help='仅列出类名')
    args = parser.parse_args()

    if args.dll_name:
        targets = [args.dll_name.replace('.dll', '')]
    else:
        targets = TARGET_DLLS

    BUILD_DIR.mkdir(parents=True, exist_ok=True)

    for dll_name in targets:
        results = process_dll(dll_name)
        if results is None:
            continue

        if args.list_classes:
            for cname in sorted(results['classes'].keys()):
                if cname and cname != '(global)':
                    print(cname)
            continue

        if args.show_class:
            print_class_detail(results, args.show_class)
            continue

        print_class_summary(results, dll_name)
        save_results(results, dll_name)

        if args.header:
            header_content = generate_header(results, dll_name)
            header_path = INCLUDE_DIR / "{}_api.h".format(dll_name)
            with open(header_path, 'w') as f:
                f.write(header_content)
            print("头文件已生成: {}".format(header_path))

        print()


if __name__ == '__main__':
    main()
