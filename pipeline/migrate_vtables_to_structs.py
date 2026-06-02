#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
migrate_vtables_to_structs.py — 把独立的 vtables.json 迁移进 per-class struct 文件。

设计（最终形态）:
  - 每个 struct 文件新增 `vtables` 字段: 数组, 每项 {addr, base, slots[]}
      slots[] 是有序 list, 每项 {addr, from}:
        from = null    -> 本类实现的 slot
        from = "Base"  -> 继承自基类 Base 的 slot (不在本类 methods 新建条目)
  - method 是否虚函数由 `ordinal` 字段存在性判定:
      本类 slot 对应的 method 条目打上 ordinal (主表=第一张表 的 slot 下标)
  - 同一函数在多张表占多个 slot: slots 是有序 list, 天然支持重复地址
  - 名字一律按地址从 functions.json / 已有 methods 解析权威名 (Trust functions.json by address)
  - 缺失本类 method 条目则新建: 签名 functions.json 优先, 否则 vtables.json slot 签名,
    统一 source=vtable_migrated
  - stub (__purecall / nullsub / ??_G... / loc_) 与继承 slot 不新建 method

用法:
  python3 pipeline/migrate_vtables_to_structs.py            # dry-run, 只报告
  python3 pipeline/migrate_vtables_to_structs.py --apply    # 写入 struct 文件
"""
import json
import os
import sys
import re

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")
STRUCTS_DIR = os.path.join(ANNOTATIONS_DIR, "structs")
VTABLES_PATH = os.path.join(ANNOTATIONS_DIR, "vtables.json")
FUNCTIONS_PATH = os.path.join(ANNOTATIONS_DIR, "functions.json")

STUB_PREFIXES = ("__purecall", "nullsub", "loc_", "sub_")
MANGLED_PREFIX = "??"


def is_stub_name(name):
    """slot 是否是不该当作命名 method 的 stub / IDA 占位名。"""
    if not name:
        return True
    if name.startswith(MANGLED_PREFIX):
        return True
    if name.startswith("__purecall") or name.startswith("nullsub") or name.startswith("loc_"):
        return True
    return False


def short_name(full):
    """从 'Class::Method' 取 'Method'; 无 '::' 原样返回。"""
    if "::" in full:
        return full.split("::")[-1]
    return full


def slot_owning_class(slot_name, owning_class):
    """
    判定 slot 函数实现归属哪个类。
    返回 None 表示属于 owning_class (本类), 否则返回基类名。
    """
    if "::" in slot_name:
        cls = slot_name.split("::")[0]
        if cls != owning_class:
            return cls
    return None


def load_struct(struct_cache, cls):
    if cls in struct_cache:
        return struct_cache[cls]
    p = os.path.join(STRUCTS_DIR, "%s.json" % cls)
    if os.path.exists(p):
        d = json.load(open(p, encoding="utf-8"))
    else:
        d = None
    struct_cache[cls] = d
    return d


def main():
    apply = "--apply" in sys.argv

    vtables = json.load(open(VTABLES_PATH, encoding="utf-8"))
    functions = json.load(open(FUNCTIONS_PATH, encoding="utf-8"))

    struct_cache = {}            # cls -> struct dict (or None)
    dirty = set()                # cls names that got modified

    # 统计
    stats = {
        "vtable_entries": 0,
        "total_slots": 0,
        "classes_touched": set(),
        "skipped_no_classfile": set(),
        "method_existing_ordinal": 0,
        "method_created": 0,
        "inherited_slots": 0,
        "stub_slots": 0,
    }

    # 待重分配清单: vtables.json 把多个类的表误聚合到一个 class 标签下,
    # 只迁移"本类主表", 额外表识别真正 owner 后输出, 不搬脏数据。
    reassign_report = []  # (orig_class, vtable_addr, slot_count, own_score, guessed_owner)

    def own_score(cls, sms):
        """表内 slot 名属于 cls 的数量 —— 用于判定本类主表。"""
        return sum(1 for m in sms if m.get("name", "").startswith(cls + "::"))

    def guess_owner(sms):
        """按 slot 名多数决猜真正 owner 类。"""
        votes = {}
        for m in sms:
            nm = m.get("name", "")
            if "::" in nm:
                c = nm.split("::")[0]
                votes[c] = votes.get(c, 0) + 1
        return max(votes, key=votes.get) if votes else None

    # 按 owning class 聚合 vtable 条目 (一个类可能有多张表)
    class_vtables = {}  # cls -> list of (addr, methods_list)
    for sym, v in vtables.items():
        cls = v.get("class", "")
        stats["vtable_entries"] += 1
        if not cls:
            continue
        class_vtables.setdefault(cls, []).append((v.get("address", ""), v.get("methods", [])))

    for cls, vt_list in class_vtables.items():
        sd = load_struct(struct_cache, cls)
        if sd is None:
            stats["skipped_no_classfile"].add(cls)
            continue

        methods = sd.setdefault("methods", {})
        out_vtables = []

        # 主表判定: 本类 slot 占比最高的表。其余表 = 误标的子类/无关表,
        # 不迁移, 只记入待重分配清单。
        if len(vt_list) > 1:
            scored = sorted(
                vt_list,
                key=lambda t: own_score(cls, t[1]),
                reverse=True,
            )
            main_table = scored[0]
            for vt_addr, slot_methods in scored[1:]:
                reassign_report.append((
                    cls, vt_addr, len(slot_methods),
                    own_score(cls, slot_methods), guess_owner(slot_methods),
                ))
            migrate_list = [main_table]
        else:
            migrate_list = vt_list

        # 主表写入 vtables[], slots 顺序即 ordinal。
        for vt_idx, (vt_addr, slot_methods) in enumerate(migrate_list):
            slots_out = []
            # 推断该表对应的基类: 看表内继承 slot 的来源类 (多数一致)
            base_guess = None
            base_votes = {}

            for ordinal, m in enumerate(slot_methods):
                stats["total_slots"] += 1
                addr = m.get("address", "")
                slot_name = m.get("name", "")

                # 权威名: 按地址查 functions.json -> 已有 methods -> vtables.json slot 名
                auth_name = None
                if addr in functions:
                    auth_name = functions[addr].get("name", "")
                elif addr in methods:
                    auth_name = methods[addr].get("name", "")
                if not auth_name:
                    auth_name = slot_name

                owner = slot_owning_class(auth_name if "::" in auth_name else slot_name, cls)

                slot_entry = {"addr": addr, "from": owner}
                slots_out.append(slot_entry)

                if owner is not None:
                    base_votes[owner] = base_votes.get(owner, 0) + 1

                if is_stub_name(short_name(auth_name)) and addr not in methods and addr not in functions:
                    stats["stub_slots"] += 1
                    continue

                if owner is not None:
                    # 继承自基类: 不在本类新建 method, slots 已标记 from
                    stats["inherited_slots"] += 1
                    continue

                # 本类 slot: 确保 methods 有条目并打 ordinal (仅主表 vt_idx==0)。
                # ordinal 取该地址在表内"首次出现"的 slot 下标 —— 同址多 slot 时
                # 不覆盖。完整布局以 vtables[].slots 为权威, ordinal 仅作虚函数标志。
                if addr in methods:
                    if vt_idx == 0 and "ordinal" not in methods[addr]:
                        methods[addr]["ordinal"] = ordinal
                    stats["method_existing_ordinal"] += 1
                else:
                    # 新建 method: 签名 functions.json 优先, 否则 vtables.json slot
                    sig = ""
                    nm = short_name(auth_name)
                    if addr in functions:
                        sig = functions[addr].get("signature", "")
                        nm = short_name(functions[addr].get("name", "")) or nm
                    if not sig:
                        sig = m.get("signature", "")
                    new_entry = {
                        "name": nm,
                        "signature": sig,
                        "source": "vtable_migrated",
                    }
                    if vt_idx == 0:
                        new_entry["ordinal"] = ordinal
                    methods[addr] = new_entry
                    stats["method_created"] += 1

            if base_votes:
                base_guess = max(base_votes, key=base_votes.get)
            out_vtables.append({"addr": vt_addr, "base": base_guess, "slots": slots_out})

        # 非主表的本类 slot 也需要 ordinal? -> 多表场景下 ordinal 仅主表语义,
        # 完整布局以 vtables[].slots 为权威。method.ordinal 只是主表快捷标志。
        sd["vtables"] = out_vtables
        stats["classes_touched"].add(cls)
        dirty.add(cls)

    # ---- 报告 ----
    print("=== vtables.json -> per-class 迁移报告 (%s) ===" % ("APPLY" if apply else "DRY-RUN"))
    print("vtable 条目总数:        %d" % stats["vtable_entries"])
    print("slot 总数:              %d" % stats["total_slots"])
    print("涉及类数:               %d" % len(stats["classes_touched"]))
    print("已有method打ordinal:    %d" % stats["method_existing_ordinal"])
    print("新建method条目:         %d" % stats["method_created"])
    print("继承slot(存slots不建):  %d" % stats["inherited_slots"])
    print("stub slot(存slots不建): %d" % stats["stub_slots"])
    print("跳过(无struct文件):     %d %s" % (
        len(stats["skipped_no_classfile"]), sorted(stats["skipped_no_classfile"])))

    if reassign_report:
        print("\n=== 待重分配额外表 (误标, 未迁移) %d 张 ===" % len(reassign_report))
        print("%-18s %-14s %-8s %-10s %s" % (
            "orig_class", "vtable_addr", "slots", "own_score", "guessed_owner"))
        for oc, va, n, sc, go in sorted(reassign_report):
            print("%-18s %-14s %-8d %-10d %s" % (oc, va, n, sc, go))
        # 写一份机读清单供后续 IDA 侧重标注使用
        rp = os.path.join(ANNOTATIONS_DIR, "vtable_reassign_todo.json")
        if apply:
            with open(rp, "w", encoding="utf-8") as f:
                json.dump([
                    {"orig_class": oc, "vtable_addr": va, "slot_count": n,
                     "own_score": sc, "guessed_owner": go}
                    for oc, va, n, sc, go in sorted(reassign_report)
                ], f, ensure_ascii=False, indent=2)
            print("\n待重分配清单已写入 data/annotations/vtable_reassign_todo.json")

    if apply:
        for cls in sorted(dirty):
            sd = struct_cache[cls]
            p = os.path.join(STRUCTS_DIR, "%s.json" % cls)
            with open(p, "w", encoding="utf-8") as f:
                json.dump(sd, f, ensure_ascii=False, indent=2)
        print("\n已写入 %d 个 struct 文件。" % len(dirty))
        print("下一步: 删除 vtables.json, 改消费方, 跑 check_annotations。")
    else:
        print("\n(dry-run, 未写入。加 --apply 执行。)")


if __name__ == "__main__":
    main()
