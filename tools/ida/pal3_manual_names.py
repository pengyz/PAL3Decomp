"""
IDAPython: 批量应用人工分析得到的函数名

来源: BFS 反编译上下文分析 + PDB 交叉验证

用法:
  idat.exe -A -S"pal3_manual_names.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_hexrays
import ida_name
import idautils
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_names_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

# === 人工分析结果 ===
# Format: (address, name, evidence)
MANUAL_NAMES = [
    # From PAL3::Update context analysis
    (0x005415F0, "UIQuadManager_GetInstance", "singleton pattern: check flag, init, atexit, return global"),
    (0x0053D150, "CScreenMode_GetSomething", "singleton pattern similar to GetInstance"),
    (0x004022C0, "GRPinput_GetKeyState2", "return *(this + a2 + 104) — key state array access"),
    (0x004C0200, "CRenderTarget2_Update", "near CRenderTarget2 cluster, __thiscall with float dt"),
    (0x0053D1A0, "CScreenMode_SetResolution", "sets width/height via sub_432770"),

    # From PAL3::Render context
    (0x004BE460, "RenderPost", "already named in callgraph"),
    (0x004BE590, "RenderPrepare", "already named in callgraph"),

    # From GetInstance pattern analysis (deep_analysis round 1)
    (0x0041B6A0, "GetGfxManager_1", "returns g_pGfxManager"),
    (0x00421830, "GetGfxManager_2", "returns g_pGfxManager"),
    (0x00421870, "GetGfxManager_3", "returns g_pGfxManager"),
    (0x00429CA0, "GetActorMgr", "returns g_pActorMgr"),
    (0x0042C6E0, "GetGfxManager_4", "returns g_pGfxManager"),
    (0x004352D0, "GetCamera_1", "returns g_pCamera"),
    (0x00435320, "GetCamera_2", "returns g_pCamera"),
    (0x00435350, "GetCamera_3", "returns g_pCamera"),
    (0x00435380, "GetCamera_4", "returns g_pCamera"),
    (0x004353A0, "GetCamera_5", "returns g_pCamera"),

    # From cluster analysis: CCBRoleState/CCBSystem related
    (0x0040CCF0, "CCBStageRole_GetAlive", "called by CCBRoleState methods, __thiscall"),
    (0x0040CF60, "CCBStageRole_PassCmd", "called by CCBSystem::PassCmdToThread"),
    (0x0040D010, "CCBStageRole_CheckValid", "called by CCBRoleState::CheckRoleValid"),
    (0x0040DCF0, "CCBStageRole_GetByIndex", "indexed access pattern"),
    (0x0040DD30, "CCBStageRole_Find", "lookup pattern"),
    (0x0040DD80, "CCBStageRole_Reset", "called in init context"),
    (0x0040CC90, "CCBStageRole_Init", "takes &dword as init param"),

    # PAL3::Update remaining unknowns
    (0x00421C40, "UINotifyUpdate", "in UI area, called from main loop"),
    (0x004226F0, "UISceneUpdate", "in UI area near EffectUpdate"),
    (0x0044F610, "CGameData_Load", "near CGameData, large function 604B"),
]

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 批量命名 (人工分析)")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        renamed = 0
        skipped = 0
        failed = 0

        for addr, name, evidence in MANUAL_NAMES:
            if addr < TEXT_START or addr >= TEXT_END:
                skipped += 1
                continue

            cur = ida_name.get_name(addr) or ""
            if cur and not cur.startswith("sub_"):
                skipped += 1
                continue

            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                renamed += 1
                log("  [+] 0x%08X: %s -> %s (%s)" % (addr, cur, name, evidence[:50]))
            else:
                failed += 1
                log("  [-] 0x%08X: FAILED -> %s" % (addr, name))

        log("")
        log("[*] 结果: 命名=%d, 跳过=%d, 失败=%d" % (renamed, skipped, failed))

        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB 已保存")

        # Re-export
        log("[*] 重新导出...")
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        import glob
        for f in glob.glob(os.path.join(OUTPUT_DIR, "*.json")):
            if not os.path.basename(f).startswith('_'):
                os.remove(f)

        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            nm = ida_name.get_name(ea) or ""
            if not nm or nm.startswith("nullsub_") or nm.startswith("j_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, nm, func.size()))

        targets.sort()
        named_total = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] 目标: %d (命名: %d)" % (len(targets), named_total))

        exported = 0
        errors = 0
        t0 = time.time()

        for i, (ea, nm, size) in enumerate(targets):
            if (i + 1) % 1000 == 0:
                elapsed = time.time() - t0
                log("  [%d/%d] exported=%d (%.0f f/s)" % (
                    i+1, len(targets), exported, (i+1)/elapsed))
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    continue
                code = str(cfunc)
                sig = cfunc.type.dstr()
                demangled = idc.demangle_name(nm, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else nm

                safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe = safe.replace('*', '_').replace(' ', '_').replace('?', '_')
                safe = safe.replace('@', '_').replace('$', '_').replace(',', '_')
                safe = safe.replace('(', '').replace(')', '').replace('/', '_')
                safe = safe.replace('"', '').replace("'", '').replace('\\', '_')
                while '__' in safe:
                    safe = safe.replace('__', '_')
                safe = safe.strip('_')
                if len(safe) > 100:
                    safe = safe[:100]
                filename = '%s_%08x.json' % (safe, ea)

                result = {
                    'name': display_name,
                    'address': '0x%08X' % ea,
                    'size_bytes': size,
                    'signature': sig,
                    'decompiled_c': code,
                }
                with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                    json.dump(result, f, indent=2, ensure_ascii=False)
                exported += 1
            except Exception:
                errors += 1

        elapsed = time.time() - t0
        log("[*] 导出: %d 成功, %d 错误 (%.1fs)" % (exported, errors, elapsed))

        summary = {
            'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
            'manual_renamed': renamed,
            'named_functions': named_total,
            'exported': exported,
        }
        with open(os.path.join(OUTPUT_DIR, "_export_summary.json"), 'w', encoding='utf-8') as f:
            json.dump(summary, f, indent=2)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 完成!")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
