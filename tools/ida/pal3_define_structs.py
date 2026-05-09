"""
IDAPython: 定义 PAL3.exe 关键结构体

从反编译分析和 PDB 交叉验证得到的结构体定义。
应用到 IDB 后重新导出可获得更好的 Hex-Rays 输出。

用法:
  idat.exe -A -S"pal3_define_structs.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_name
import ida_typeinf
import ida_hexrays
import ida_funcs
import idautils
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
LOG_FILE = os.path.join(LOG_DIR, "pal3_define_structs_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


# ========================================================================
# 结构体定义 (从反编译分析得到)
# ========================================================================

STRUCT_DEFS = [
    # DisplayConfig: dword_A3A7D8 的类型
    # +0x00: vtable/flags
    # +0x04: width setting
    # +0x08: height setting
    # +0x0C: D3D display mode pointer (deref to get actual width/height)
    """
    struct DisplayConfig {
        int m_nFlags;
        int m_nSettingWidth;
        int m_nSettingHeight;
        void *m_pDisplayMode;
    };
    """,

    # AudioContext: AudioUpdate/StopAll/FadeOut 的 this 类型
    # 从 AudioUpdate 反编译得到:
    # +0x00: 前 4 dwords 基础字段
    # +0x0C: char* (sound name)
    # +0x10: int (flag)
    # +0x18: gbAudioManager* (audio mgr ptr)
    # +0x20: string offset 1
    """
    struct AudioContext {
        int m_nType;
        int m_nState;
        int m_nVolume;
        char *m_pSoundName;
        int m_bPlaying;
        int m_nReserved;
        void *m_pAudioMgr;
        int m_nFadeTarget;
        char m_szPrefix[32];
    };
    """,
]

# 全局变量类型标注
GLOBAL_TYPES = [
    (0x00A3A7D8, "DisplayConfig", "g_DisplayConfig"),
]

# 函数签名修正
FUNC_SIGNATURES = [
    # sub_53C710: int DisplayConfig::GetWidth()
    (0x0053C710, "int __thiscall sub_53C710(DisplayConfig *this)", "DisplayConfig_GetWidth"),
    # sub_53C720: int DisplayConfig::GetHeight()
    (0x0053C720, "int __thiscall sub_53C720(DisplayConfig *this)", "DisplayConfig_GetHeight"),
    # sub_53C6F0: void CScreenMode::SetViewport(int x, int y)
    (0x0053C6F0, "int __thiscall sub_53C6F0(void *this, int a2, int a3)", "CScreenMode_SetViewport"),
]


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 结构体定义 + 类型标注")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        til = ida_typeinf.get_idati()

        # Phase 1: 定义结构体
        log("\n[Phase 1] 定义结构体")
        structs_ok = 0
        for decl in STRUCT_DEFS:
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
                    structs_ok += 1
                    log("  [+] %s" % name)
            else:
                log("  [-] FAILED: %s" % decl[:50])

        log("[*] 结构体定义: %d" % structs_ok)

        # Phase 2: 全局变量类型标注
        log("\n[Phase 2] 全局变量类型")
        for addr, type_name, var_name in GLOBAL_TYPES:
            # Name
            cur = ida_name.get_name(addr) or ""
            if cur.startswith("dword_") or cur.startswith("unk_") or not cur:
                ida_name.set_name(addr, var_name, ida_name.SN_NOWARN | ida_name.SN_FORCE)
                log("  [+] 0x%08X: %s -> %s" % (addr, cur, var_name))
            # Type
            decl = "%s %s;" % (type_name, var_name)
            idc.SetType(addr, decl)

        # Phase 3: 函数签名
        log("\n[Phase 3] 函数签名")
        sigs_ok = 0
        for addr, sig, new_name in FUNC_SIGNATURES:
            # Rename
            cur = ida_name.get_name(addr) or ""
            if cur.startswith("sub_"):
                ida_name.set_name(addr, new_name, ida_name.SN_NOWARN | ida_name.SN_FORCE)
            # Apply signature
            if idc.SetType(addr, sig):
                sigs_ok += 1
                log("  [+] 0x%08X: %s" % (addr, new_name))
            else:
                log("  [-] 0x%08X: sig failed" % addr)

        log("[*] 签名应用: %d" % sigs_ok)

        # Save
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB 已保存")

        # Phase 4: 重新导出
        log("\n[Phase 4] 重新导出")
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        import glob as gl
        for f in gl.glob(os.path.join(OUTPUT_DIR, "*.json")):
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
                log("  [%d/%d] exported=%d (%.0f f/s)" % (i+1, len(targets), exported, (i+1)/elapsed))
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
        log("[*] 导出: %d 成功, %d 错误 (%.1fs)" % (exported, errors, elapsed))
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
