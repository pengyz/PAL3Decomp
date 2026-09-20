"""
IDAPython (IDA 9.x): 基于类聚集性匹配未命名函数

策略:
1. 对每个类，找到 IDA 中已命名成员函数的地址范围
2. 在该地址范围附近的未命名函数，很可能也属于同一类
3. 结合 PDB 中该类的函数数量和大小信息做匹配
4. 利用链接器特性: 同一 .obj 文件的函数地址连续

关键洞察: MSVC 链接器保持同一编译单元(.obj)内函数的相对顺序。
如果 ClassA 的函数在源文件中依次为 F1,F2,...,Fn，
在二进制中它们也是连续的（可能有其他 obj 的函数穿插，但同 obj 内保序）。

用法:
  idat.exe -A -S"D:\workspace\project-x\tools\ida_class_cluster_match.py" "D:\workspace\project-x\original\PAL3A.exe.i64"
"""

import json
import os
import traceback
from collections import defaultdict

import ida_auto
import ida_funcs
import ida_name
import idautils
import idc


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

PDB_EXPORT = r"D:\workspace\project-x\asm\pal3a\pdb_export.json"
LOG_FILE = r"D:\workspace\project-x\tools\fulldump\ida_class_cluster_log.txt"
RESULT_FILE = r"D:\workspace\project-x\tools\fulldump\ida_class_cluster_result.json"

TEXT_START = 0x00401000
TEXT_END = 0x00558000


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb = json.load(f)

        # ====== 构建 PDB 类索引 ======
        # 按源文件+类分组 PDB 函数
        pdb_by_src_class = defaultdict(list)  # (src, class) -> [func]
        pdb_name_set = set()
        for func in pdb['functions']:
            name = func.get('name', '')
            src = func.get('source_file', '')
            cls = func.get('class', '')
            size = func.get('size', 0)
            if not name or not cls or not src:
                continue
            if name.startswith('$') or '[thunk]' in name:
                continue
            pdb_by_src_class[(src, cls)].append({
                'name': name, 'size': size
            })
            pdb_name_set.add(name)

        # 每组按 PDB 地址排序（保持源文件内的顺序）
        for key in pdb_by_src_class:
            addr_key = lambda func: pdb['functions'][next(
                i for i, f in enumerate(pdb['functions']) if f.get('name') == func['name']
            )].get('address', '0')
            # Already sorted by pdb address in file order

        log(f"[*] PDB 源文件+类 组合: {len(pdb_by_src_class)}")

        # ====== 获取 IDA 函数列表 ======
        ida_all = []
        for ea in idautils.Functions():
            func = ida_funcs.get_func(ea)
            if not func:
                continue
            if ea < TEXT_START or ea >= TEXT_END:
                continue
            name = ida_name.get_name(ea) or ""
            ida_all.append({
                'addr': ea,
                'size': func.size(),
                'name': name,
                'is_named': bool(name) and not name.startswith("sub_"),
            })
        ida_all.sort(key=lambda x: x['addr'])

        ida_named_count = sum(1 for f in ida_all if f['is_named'])
        log(f"[*] IDA .text 函数: {len(ida_all)} (已命名: {ida_named_count})")

        # ====== 策略: 类地址聚集匹配 ======
        log("[*] 分析类的地址聚集...")

        # 对每个类，找到在 IDA 中的地址范围
        class_addresses = defaultdict(list)  # class -> [ida_addr]
        for f in ida_all:
            if f['is_named'] and '::' in f['name']:
                cls = f['name'].split('::')[0]
                class_addresses[cls].append(f['addr'])

        # 对每个类，找"簇"(连续的地址区域)
        class_clusters = {}  # class -> [(start_idx, end_idx)] in ida_all
        ida_addr_to_idx = {f['addr']: i for i, f in enumerate(ida_all)}

        for cls, addrs in class_addresses.items():
            if len(addrs) < 3:
                continue
            addrs.sort()

            # 找连续的簇（相邻命名函数之间间隔不超过20个函数）
            clusters = []
            cluster_start = ida_addr_to_idx[addrs[0]]
            prev_idx = cluster_start

            for addr in addrs[1:]:
                idx = ida_addr_to_idx[addr]
                if idx - prev_idx > 30:
                    # 新簇开始
                    clusters.append((cluster_start, prev_idx))
                    cluster_start = idx
                prev_idx = idx
            clusters.append((cluster_start, prev_idx))

            class_clusters[cls] = clusters

        log(f"  有地址簇的类: {len(class_clusters)}")

        # ====== 在簇内匹配未命名函数 ======
        log("[*] 在类簇内匹配未命名函数...")

        applied = 0
        skipped = 0

        for cls, clusters in class_clusters.items():
            # 获取此类在 PDB 中未匹配的函数
            unmatched_pdb = []
            for (src, pcls), funcs in pdb_by_src_class.items():
                if pcls == cls:
                    for pf in funcs:
                        if pf['name'] not in {f['name'] for f in ida_all if f['is_named']}:
                            unmatched_pdb.append(pf)

            if not unmatched_pdb:
                continue

            # 按大小排序 PDB 未匹配函数（用于大小匹配）
            pdb_by_size = defaultdict(list)
            for pf in unmatched_pdb:
                if pf['size'] > 0:
                    pdb_by_size[pf['size']].append(pf['name'])

            # 遍历每个簇内的未命名函数
            for start_idx, end_idx in clusters:
                # 扩展簇的搜索范围（前后各几个函数）
                search_start = max(0, start_idx - 3)
                search_end = min(len(ida_all), end_idx + 4)

                for i in range(search_start, search_end):
                    f = ida_all[i]
                    if f['is_named']:
                        continue

                    # 尝试按大小匹配
                    ida_size = f['size']
                    if ida_size < 10:
                        continue

                    # 精确大小匹配
                    candidates = pdb_by_size.get(ida_size, [])
                    if len(candidates) == 1:
                        target_name = candidates[0]
                        success = ida_name.set_name(
                            f['addr'], target_name,
                            ida_name.SN_NOWARN | ida_name.SN_FORCE)
                        if success:
                            applied += 1
                            f['is_named'] = True
                            f['name'] = target_name
                            pdb_by_size[ida_size].remove(target_name)
                        continue

                    # 近似大小匹配（±10%）
                    for tolerance in (0.05, 0.10):
                        low = int(ida_size * (1 - tolerance))
                        high = int(ida_size * (1 + tolerance))
                        near_candidates = []
                        for size in range(low, high + 1):
                            near_candidates.extend(pdb_by_size.get(size, []))

                        if len(near_candidates) == 1:
                            target_name = near_candidates[0]
                            target_size = next(
                                pf['size'] for pf in unmatched_pdb if pf['name'] == target_name)
                            success = ida_name.set_name(
                                f['addr'], target_name,
                                ida_name.SN_NOWARN | ida_name.SN_FORCE)
                            if success:
                                applied += 1
                                f['is_named'] = True
                                f['name'] = target_name
                                if target_name in pdb_by_size.get(target_size, []):
                                    pdb_by_size[target_size].remove(target_name)
                            break

        log(f"  类簇内匹配: {applied}")

        # ====== 策略 2: 更激进的序列匹配 ======
        # 对于已有多个锚点的类，尝试在锚点之间做 1:1 匹配
        log("\n[*] 锚点间强制序列匹配...")

        forced = 0
        for cls, clusters in class_clusters.items():
            unmatched_pdb = []
            for (src, pcls), funcs in pdb_by_src_class.items():
                if pcls == cls:
                    for pf in funcs:
                        if pf['name'] not in {f['name'] for f in ida_all if f['is_named']}:
                            unmatched_pdb.append(pf)

            if not unmatched_pdb:
                continue

            for start_idx, end_idx in clusters:
                # 收集簇内的已命名和未命名函数
                named_in_cluster = []
                unnamed_in_cluster = []

                for i in range(start_idx, end_idx + 1):
                    f = ida_all[i]
                    if f['is_named'] and '::' in f['name']:
                        if f['name'].split('::')[0] == cls:
                            named_in_cluster.append((i, f))
                    elif not f['is_named']:
                        unnamed_in_cluster.append((i, f))

                if len(named_in_cluster) < 2 or not unnamed_in_cluster:
                    continue

                # 尝试用 PDB 序列填充空隙
                # 建立已命名函数在 PDB 中的位置
                pdb_all_class = []
                for (src, pcls), funcs in pdb_by_src_class.items():
                    if pcls == cls:
                        pdb_all_class.extend(funcs)

                # 建立 PDB name -> index
                pdb_name_to_idx = {pf['name']: i for i, pf in enumerate(pdb_all_class)}

                # 对每对相邻已命名函数，看中间有多少未命名函数
                for j in range(len(named_in_cluster) - 1):
                    ida_idx1, f1 = named_in_cluster[j]
                    ida_idx2, f2 = named_in_cluster[j + 1]

                    pdb_idx1 = pdb_name_to_idx.get(f1['name'])
                    pdb_idx2 = pdb_name_to_idx.get(f2['name'])

                    if pdb_idx1 is None or pdb_idx2 is None:
                        continue
                    if pdb_idx2 <= pdb_idx1:
                        continue

                    # PDB 中两个锚点之间的函数
                    pdb_between = pdb_all_class[pdb_idx1 + 1:pdb_idx2]
                    pdb_between = [pf for pf in pdb_between
                                   if pf['name'] not in {f['name'] for f in ida_all if f['is_named']}]

                    # IDA 中两个锚点之间的未命名函数
                    ida_between = [(i, f) for i, f in unnamed_in_cluster
                                   if ida_idx1 < i < ida_idx2]

                    # 如果数量完全匹配 -> 1:1 对应
                    if len(pdb_between) == len(ida_between) and len(pdb_between) > 0:
                        for k, (idx, f) in enumerate(ida_between):
                            target_name = pdb_between[k]['name']
                            success = ida_name.set_name(
                                f['addr'], target_name,
                                ida_name.SN_NOWARN | ida_name.SN_FORCE)
                            if success:
                                forced += 1
                                f['is_named'] = True
                                f['name'] = target_name

                    # 如果 PDB 少 1 个（可能 IDA 多拆了一个函数），也尝试
                    elif len(pdb_between) == len(ida_between) - 1 and len(pdb_between) > 0:
                        # 按大小找最不匹配的 IDA 函数跳过
                        pass  # 复杂情况暂不处理

        log(f"  强制序列匹配: {forced}")

        # ====== 最终统计 ======
        total_named = sum(1 for f in ida_all if f['is_named'] or
                          (ida_name.get_name(f['addr']) or "").startswith("sub_") is False)
        real_named = sum(1 for ea in idautils.Functions()
                         if TEXT_START <= ea < TEXT_END
                         and not (ida_name.get_name(ea) or "").startswith("sub_")
                         and ida_name.get_name(ea))

        log(f"\n{'='*50}")
        log(f"[*] 最终结果:")
        log(f"  类簇内匹配: {applied}")
        log(f"  强制序列匹配: {forced}")
        log(f"  总新增: {applied + forced}")
        log(f"  当前 .text 已命名: {real_named}")
        log(f"{'='*50}")

        result = {
            'cluster_applied': applied,
            'forced_sequence': forced,
            'total_new': applied + forced,
            'final_named': real_named,
        }

        os.makedirs(os.path.dirname(RESULT_FILE), exist_ok=True)
        with open(RESULT_FILE, 'w', encoding='utf-8') as f:
            json.dump(result, f, indent=2)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))

    try:
        idc.qexit(0)
    except:
        pass


main()
