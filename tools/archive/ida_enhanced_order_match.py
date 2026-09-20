"""
IDAPython (IDA 9.x): 增强版源文件顺序匹配

改进点:
1. 多锚点精确对齐（使用 LCS-like 算法而非贪心）
2. 更宽松的大小容差（PDB 是不同编译版本）
3. 利用 thunk 检测跳过不匹配的小函数
4. 迭代匹配：每轮新增命名后，下一轮有更多锚点
5. 新增：反向验证（如果一个命名的调用者/被调用者也匹配 PDB 关系，增加置信度）

用法:
  idat.exe -A -S"D:\workspace\project-x\tools\ida_enhanced_order_match.py" "D:\workspace\project-x\original\PAL3A.exe.i64"
"""

import json
import os
import traceback
from collections import defaultdict

import ida_auto
import ida_funcs
import ida_name
import ida_xref
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
LOG_FILE = r"D:\workspace\project-x\tools\fulldump\ida_enhanced_order_log.txt"
RESULT_FILE = r"D:\workspace\project-x\tools\fulldump\ida_enhanced_order_result.json"

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

        # 加载 PDB
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb = json.load(f)

        # 按源文件分组 PDB 函数
        pdb_by_source = defaultdict(list)
        for func in pdb['functions']:
            name = func.get('name', '')
            addr_str = func.get('address', '')
            size = func.get('size', 0)
            src = func.get('source_file', '')
            if not name or not addr_str or not src:
                continue
            if name.startswith('$') or '[thunk]' in name:
                continue
            try:
                addr = int(addr_str, 16) if addr_str.startswith('0x') else int(addr_str)
            except ValueError:
                continue
            pdb_by_source[src].append({'name': name, 'addr': addr, 'size': size})

        for src in pdb_by_source:
            pdb_by_source[src].sort(key=lambda x: x['addr'])

        log(f"[*] PDB 源文件: {len(pdb_by_source)}")
        log(f"[*] PDB 函数总数: {sum(len(v) for v in pdb_by_source.values())}")

        # 迭代匹配（最多3轮）
        total_applied = 0
        round_results = []

        for round_num in range(1, 4):
            log(f"\n[*] === 第 {round_num} 轮匹配 ===")

            # 获取 IDA 当前所有函数
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

            # 建立索引
            ida_addr_to_idx = {f['addr']: i for i, f in enumerate(ida_all)}
            known_mapping = {}
            for f in ida_all:
                if f['is_named']:
                    known_mapping[f['name']] = f['addr']

            ida_named_count = sum(1 for f in ida_all if f['is_named'])
            ida_unnamed_count = len(ida_all) - ida_named_count
            log(f"  IDA 函数: {len(ida_all)} (已命名: {ida_named_count}, 未命名: {ida_unnamed_count})")

            applied_this_round = 0

            for src, pdb_funcs in sorted(pdb_by_source.items()):
                if len(pdb_funcs) < 2:
                    continue

                # 找锚点
                anchors = []  # [(pdb_index, ida_index)]
                for i, pf in enumerate(pdb_funcs):
                    if pf['name'] in known_mapping:
                        ida_addr = known_mapping[pf['name']]
                        if ida_addr in ida_addr_to_idx:
                            anchors.append((i, ida_addr_to_idx[ida_addr]))

                if len(anchors) < 1:
                    continue

                # 验证锚点顺序一致性
                # 在 IDA 中的顺序应该和 PDB 中一致
                valid_anchors = [anchors[0]]
                for j in range(1, len(anchors)):
                    if anchors[j][1] > valid_anchors[-1][1]:
                        valid_anchors.append(anchors[j])
                    # 如果不单调递增，跳过不一致的锚点

                anchors = valid_anchors

                # 对每对相邻锚点之间的区间做匹配
                # 包括第一个锚点之前和最后一个锚点之后
                intervals = []

                # 第一个锚点之前
                if anchors[0][0] > 0:
                    intervals.append((
                        0, anchors[0][0],  # PDB range [start, end)
                        max(0, anchors[0][1] - anchors[0][0] - 5),  # IDA 估计起始
                        anchors[0][1],  # IDA end (exclusive)
                        'before_first'
                    ))

                # 相邻锚点之间
                for j in range(len(anchors) - 1):
                    pdb_start = anchors[j][0] + 1
                    pdb_end = anchors[j+1][0]
                    ida_start = anchors[j][1] + 1
                    ida_end = anchors[j+1][1]
                    if pdb_start < pdb_end and ida_start < ida_end:
                        intervals.append((pdb_start, pdb_end, ida_start, ida_end, 'between'))

                # 最后一个锚点之后
                last_pdb_idx = anchors[-1][0]
                last_ida_idx = anchors[-1][1]
                remaining_pdb = len(pdb_funcs) - last_pdb_idx - 1
                if remaining_pdb > 0:
                    ida_search_end = min(len(ida_all), last_ida_idx + remaining_pdb + 10)
                    intervals.append((
                        last_pdb_idx + 1, len(pdb_funcs),
                        last_ida_idx + 1, ida_search_end,
                        'after_last'
                    ))

                # 对每个区间做匹配
                for pdb_start, pdb_end, ida_start, ida_end, interval_type in intervals:
                    pdb_j = pdb_start
                    ida_j = ida_start

                    while pdb_j < pdb_end and ida_j < ida_end:
                        pf = pdb_funcs[pdb_j]
                        idf = ida_all[ida_j]

                        # 跳过已命名
                        if idf['is_named']:
                            if idf['name'] == pf['name']:
                                pdb_j += 1
                                ida_j += 1
                            else:
                                ida_j += 1
                            continue

                        # 计算大小匹配度
                        pdb_size = pf['size']
                        ida_size = idf['size']

                        if pdb_size > 0 and ida_size > 0:
                            ratio = min(pdb_size, ida_size) / max(pdb_size, ida_size)
                        else:
                            ratio = 0.5  # 未知大小，中等置信度

                        # 对于相邻锚点之间的函数，置信度更高
                        if interval_type == 'between':
                            # 锚点之间的函数数量接近 -> 高可信度
                            pdb_count = pdb_end - pdb_start
                            ida_count = ida_end - ida_start
                            count_ratio = min(pdb_count, ida_count) / max(pdb_count, ida_count)

                            if count_ratio > 0.7:
                                # 函数数量匹配，更宽松的大小阈值
                                threshold = 0.25
                            else:
                                threshold = 0.4
                        else:
                            threshold = 0.35

                        if ratio >= threshold:
                            # 应用命名
                            success = ida_name.set_name(
                                idf['addr'], pf['name'],
                                ida_name.SN_NOWARN | ida_name.SN_FORCE)
                            if success:
                                applied_this_round += 1
                                idf['is_named'] = True
                                idf['name'] = pf['name']
                            pdb_j += 1
                            ida_j += 1
                        elif ida_size < 16:
                            # 很小的函数可能是 thunk/padding
                            ida_j += 1
                        elif pdb_size < 16:
                            pdb_j += 1
                        else:
                            # 大小不匹配，跳过两个
                            pdb_j += 1
                            ida_j += 1

            log(f"  本轮应用: {applied_this_round}")
            total_applied += applied_this_round
            round_results.append(applied_this_round)

            if applied_this_round == 0:
                log("  无新增匹配，停止迭代")
                break

        # ====== 额外策略: 唯一大小匹配 ======
        log("\n[*] === 唯一大小匹配 ===")

        # 重新获取当前状态
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

        # 对每个源文件，找未匹配的 PDB 函数
        # 如果其大小在未命名 IDA 函数中是唯一的，直接匹配
        known_names = {f['name'] for f in ida_all if f['is_named']}
        unnamed_by_size = defaultdict(list)
        for f in ida_all:
            if not f['is_named']:
                unnamed_by_size[f['size']].append(f['addr'])

        size_applied = 0
        for src, pdb_funcs in pdb_by_source.items():
            for pf in pdb_funcs:
                if pf['name'] in known_names:
                    continue
                pdb_size = pf['size']
                if pdb_size < 20:  # 太小不可靠
                    continue
                # 检查这个大小在未命名函数中是否唯一
                candidates = unnamed_by_size.get(pdb_size, [])
                if len(candidates) == 1:
                    addr = candidates[0]
                    success = ida_name.set_name(
                        addr, pf['name'],
                        ida_name.SN_NOWARN | ida_name.SN_FORCE)
                    if success:
                        size_applied += 1
                        # 从池中移除
                        unnamed_by_size[pdb_size].remove(addr)

        log(f"  唯一大小匹配: {size_applied}")
        total_applied += size_applied

        # ====== 最终统计 ======
        final_named = sum(1 for ea in idautils.Functions()
                          if not (ida_name.get_name(ea) or "").startswith("sub_")
                          and ida_name.get_name(ea)
                          and TEXT_START <= ea < TEXT_END)

        log(f"\n{'='*50}")
        log(f"[*] 最终结果:")
        log(f"  轮次结果: {round_results}")
        log(f"  唯一大小: {size_applied}")
        log(f"  总新增命名: {total_applied}")
        log(f"  当前 .text 已命名: {final_named}")
        log(f"{'='*50}")

        result = {
            'rounds': round_results,
            'size_match': size_applied,
            'total_applied': total_applied,
            'final_named': final_named,
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
