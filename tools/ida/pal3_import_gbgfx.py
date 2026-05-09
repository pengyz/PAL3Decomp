"""
IDAPython: 导入 gbGfxManager 完整结构体 + 子结构体

从 PDB 获取 gbGfxManager(1520B), gbMatrixStack, gbEffectMgr 等定义，
导入 IDA 使 Hex-Rays 显示成员名而非裸偏移。

用法:
  idat.exe -A -S"pal3_import_gbgfx.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
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
LOG_FILE = os.path.join(LOG_DIR, "pal3_import_gbgfx_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


STRUCT_DECLS = [
    # Forward declarations
    "struct gbVertPoolMgr;",
    "struct gbEffectMgr;",
    "struct gbResManager;",
    "struct gbPrintFontMgr;",
    "struct gbMatrixStack;",
    "struct gbSceneGraph;",
    "struct gbLight;",

    # gbGfxDriverInfo (size ~0xB8)
    """struct gbGfxDriverInfo {
        char _data[184];
    };""",

    # gbMatrix4 (4x4 float = 64 bytes)
    """struct gbMatrix4 {
        float m[4][4];
    };""",

    # gbColorFlt (4 floats = 16 bytes)
    """struct gbColorFlt {
        float r;
        float g;
        float b;
        float a;
    };""",

    # gbViewPort (6 ints = 24 bytes)
    """struct gbViewPort {
        int x;
        int y;
        int width;
        int height;
        float minZ;
        float maxZ;
    };""",

    # gbClearParam (size 20 bytes)
    """struct gbClearParam {
        int flags;
        int color;
        float z;
        int stencil;
        int mask;
    };""",

    # gbGfxStatistic (size 0x30 = 48)
    """struct gbGfxStatistic {
        char _data[48];
    };""",

    # gbLight (size approx 0x44 = 68 per light)
    """struct gbLight {
        char _data[68];
    };""",

    # gbGfxManager (size=1520, from PDB)
    """struct gbGfxManager {
        void *vtable;
        int _pad04;
        unsigned int hGfxWnd;
        gbGfxDriverInfo DrvInfo;
        gbVertPoolMgr *pVertPoolMgr;
        gbEffectMgr *pEffectMgr;
        gbResManager *pTexResMgr;
        gbPrintFontMgr *pFontMgr;
        gbMatrixStack *pMatrixStack[4];
        gbMatrix4 ViewMatrix;
        gbMatrix4 InvViewMatrix;
        gbMatrix4 WorldMatrix;
        int CurZBias;
        int bWireMode;
        gbColorFlt AmbientLight;
        float fSelfIllum;
        gbSceneGraph *pSceneGraph;
        gbViewPort Viewport;
        gbClearParam ClearParam;
        double LastTime;
        double CurTime;
        unsigned int LastTick;
        unsigned int CurTick;
        gbGfxStatistic Stat;
        gbLight AllLight[8];
        int LightEnable[8];
    };""",
]


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe gbGfxManager 结构体导入")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        til = ida_typeinf.get_idati()

        # Import structs
        ok = 0
        for decl in STRUCT_DECLS:
            decl = decl.strip()
            tinfo = ida_typeinf.tinfo_t()
            result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
            if result is not None:
                # Extract name
                import re
                m = re.search(r'struct\s+(\w+)', decl)
                if m:
                    name = m.group(1)
                    tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                    ok += 1
                    log("  [+] %s" % name)
            else:
                log("  [-] FAILED: %s" % decl[:60])

        log("[*] 结构体导入: %d / %d" % (ok, len(STRUCT_DECLS)))

        # Apply g_pGfxManager type
        g_addr = 0x00BFDA60
        idc.SetType(g_addr, "gbGfxManager *")
        log("[*] g_pGfxManager 类型已设置")

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
            name = ida_name.get_name(ea) or ""
            if not name or name.startswith("nullsub_") or name.startswith("j_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, name, func.size()))

        targets.sort()
        named = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] 目标: %d (命名: %d)" % (len(targets), named))

        exported = 0
        errors = 0
        t0 = time.time()

        for i, (ea, name, size) in enumerate(targets):
            if (i + 1) % 1000 == 0:
                elapsed = time.time() - t0
                log("  [%d/%d] (%.0f f/s)" % (i+1, len(targets), (i+1)/elapsed))
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    continue
                code = str(cfunc)
                sig = cfunc.type.dstr()
                demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else name
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
        log("[*] 导出: %d (%.1fs)" % (exported, elapsed))
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
