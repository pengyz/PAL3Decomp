"""
IDAPython: PAL3A 一键反编译质量优化 Master Pipeline

按顺序执行所有改进脚本:
  Phase 1: 导入 PDB 结构体定义 (416 classes)
  Phase 2: 补充缺失类型 (UIWnd, NPCInfo, SaveTask, PtrArray)
  Phase 3: 修补 UI 类基类 (_gap_0 -> UIWnd)
  Phase 4: 批量重命名高频 sub_ 函数 (15个, 影响8000+调用点)
  Phase 5: 重新导出全部反编译结果

用法:
  idat.exe -A -S"ida_master_pipeline.py [options]" PAL3A.exe.i64

选项:
  --skip-import    跳过 Phase 1 (已导入过)
  --skip-export    跳过 Phase 5 (只优化不导出)
  --phase=N        只执行 Phase N
"""

import sys
import os
import time
import importlib.util
import builtins

builtins._IDA_PIPELINE_RUNNING = True

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

SKIP_IMPORT = '--skip-import' in sys.argv
SKIP_EXPORT = '--skip-export' in sys.argv
PHASE_ONLY = None
for arg in sys.argv:
    if arg.startswith('--phase='):
        PHASE_ONLY = int(arg.split('=')[1])


def run_phase(phase_num, description, script_name):
    if PHASE_ONLY is not None and PHASE_ONLY != phase_num:
        print(f"  [SKIP] Phase {phase_num}: {description}")
        return True

    print()
    print("=" * 60)
    print(f"  Phase {phase_num}: {description}")
    print("=" * 60)

    script_path = os.path.join(SCRIPT_DIR, script_name)
    if not os.path.exists(script_path):
        print(f"  [!] 脚本不存在: {script_path}")
        return False

    t0 = time.time()
    spec = importlib.util.spec_from_file_location(
        script_name.replace('.py', ''), script_path)
    module = importlib.util.module_from_spec(spec)
    try:
        spec.loader.exec_module(module)
        if hasattr(module, 'main'):
            module.main()
    except Exception as e:
        print(f"  [!] 执行出错: {e}")
        import traceback
        traceback.print_exc()
        return False

    elapsed = time.time() - t0
    print(f"  [OK] Phase {phase_num} 完成 ({elapsed:.1f}s)")
    return True


def main():
    print()
    print("=" * 60)
    print("  PAL3A IDA Decompilation Quality Pipeline")
    print("=" * 60)
    print()
    print(f"  脚本目录: {SCRIPT_DIR}")
    if SKIP_IMPORT:
        print(f"  --skip-import")
    if SKIP_EXPORT:
        print(f"  --skip-export")
    if PHASE_ONLY:
        print(f"  --phase={PHASE_ONLY}")
    print()

    t_start = time.time()
    results = []

    if not SKIP_IMPORT:
        ok = run_phase(1, "导入 PDB 结构体定义 (416 classes)", "ida_import_all.py")
        results.append(("Phase 1: PDB 结构体导入", ok))
    else:
        results.append(("Phase 1: PDB 结构体导入", "SKIP"))

    ok = run_phase(2, "定义缺失基类/嵌套类型", "ida_define_base_types.py")
    results.append(("Phase 2: 缺失类型定义", ok))

    ok = run_phase(3, "修补 UI 类基类字段", "ida_patch_base_classes.py")
    results.append(("Phase 3: UI 基类修补", ok))

    ok = run_phase(4, "重命名高频未命名函数", "ida_rename_top_subs.py")
    results.append(("Phase 4: sub_ 重命名", ok))

    if not SKIP_EXPORT:
        ok = run_phase(5, "重新导出反编译结果", "ida_reexport_all.py")
        results.append(("Phase 5: 反编译导出", ok))
    else:
        results.append(("Phase 5: 反编译导出", "SKIP"))

    elapsed_total = time.time() - t_start
    print()
    print("=" * 60)
    print("  结果汇总")
    print("=" * 60)
    for name, status in results:
        if status == "SKIP":
            print(f"  [ ] {name} (跳过)")
        elif status:
            print(f"  [+] {name}")
        else:
            print(f"  [!] {name} (失败)")
    print(f"\n  总耗时: {elapsed_total:.1f}s")

    try:
        import idc
        print("\n[*] 保存 IDA 数据库...")
        idc.save_database(idc.get_idb_path(), 0)
        print("[+] 已保存")
    except:
        pass


if __name__ == '__main__':
    main()
