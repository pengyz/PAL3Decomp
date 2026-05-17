"""Global data store for codegen pipeline.

Loaded once at startup, accessed by transforms via `from .data import store`.
"""
import json
import os
import re
import struct as _struct
from pathlib import Path


class DataStore:
    """All annotation + binary resources needed by codegen transforms."""

    def __init__(self):
        self.loaded = False
        # Paths
        self.pipeline_root = Path(__file__).parent.parent
        self.project_root = self.pipeline_root.parent
        self.annotations_dir = self.pipeline_root / "data" / "annotations"
        self.decomp_dir = self.project_root / "asm" / "pal3" / "decomp"
        self.header_dir = self.project_root / "include" / "pal3" / "gen"
        self.output_dir = self.project_root / "src" / "pal3"

        # Data tables (populated by load())
        self.literals = {}          # "flt_XXX" -> "1.0f", "aXxx" -> '"string"'
        self.thunks = {}            # "sub_XXX" -> "TargetFunc"
        self.globals_map = {}       # "dword_XXX" -> "g_SceneMgr"
        self.global_types = {}      # "dword_XXX" -> "int[4]"
        self.struct_instances = []  # [(base, end, name, type)]
        self.struct_members = {}    # type -> {offset: (name, member_type)}
        self.game_classes = set()   # class names with .h files
        self.thunk_classes = set()  # j_ClassName thunk type names
        self.static_methods = set() # "ClassName::Method" for __cdecl methods
        self.declared_globals = set()  # already in globals.h
        self.exe_data = b''         # raw exe for .rdata string lookup
        self.skip_classes = set()   # classes to not generate

    def load(self):
        """Load all resources from disk. Call once at startup."""
        if self.loaded:
            return
        self._load_game_classes()
        self._load_globals_h()
        self._load_annotations()
        self._load_binary()
        self.loaded = True

    def _load_game_classes(self):
        for h in self.header_dir.glob("*.h"):
            self.game_classes.add(h.stem)

    def _load_globals_h(self):
        globals_h = self.project_root / "include" / "pal3" / "globals.h"
        if globals_h.exists():
            for line in open(globals_h, encoding='utf-8', errors='replace'):
                m = re.search(r'extern\s+\S.*?\b(\w+)\s*(?:\[|;)', line)
                if m:
                    self.declared_globals.add(m.group(1))

    def _load_annotations(self):
        # functions.json → static methods + thunks
        funcs_path = self.annotations_dir / "functions.json"
        if funcs_path.exists():
            funcs = json.load(open(funcs_path, encoding='utf-8'))
            for addr, info in funcs.items():
                name = info.get('name', '')
                sig = info.get('signature', '')
                if '::' in name and '__cdecl' in sig:
                    self.static_methods.add(name)

        # skip_functions.json → thunks
        skip_path = self.annotations_dir / "skip_functions.json"
        if skip_path.exists():
            skip = json.load(open(skip_path, encoding='utf-8'))
            for addr, info in skip.items():
                if info.get('reason') == 'thunk' and info.get('target_name'):
                    target = info['target_name']
                    self.thunks["sub_%s" % addr[2:].lstrip('0').lower()] = target
                    self.thunks[info['name']] = target
                    self.thunks[info['name'].replace('~', '_')] = target.replace('~', '_')
                    # Collect thunk class names for type cast replacement
                    n = info.get('name', '')
                    if '::' in n:
                        self.thunk_classes.add(n.split('::')[0])
            self.thunk_classes.add('j_std')
            self.thunk_classes.add('j_j_codecvt_base')

        # globals.json → global types + name map
        globals_path = self.annotations_dir / "globals.json"
        if globals_path.exists():
            gdata = json.load(open(globals_path, encoding='utf-8'))
            ida_prefixes = ('dword', 'byte', 'word', 'stru', 'off', 'unk', 'flt')
            for addr_str, ginfo in gdata.items():
                gname = ginfo.get('name', '')
                gtype = ginfo.get('type', '')
                if gname and gtype:
                    self.global_types[gname] = gtype
                if not gname or any(gname.startswith(p + '_') for p in ida_prefixes):
                    continue
                addr_int = int(addr_str, 16)
                addr_hex = '%X' % addr_int
                for pfx in ida_prefixes:
                    self.globals_map['%s_%s' % (pfx, addr_hex)] = gname

        # structs → struct instances + members for member resolution
        structs_dir = self.annotations_dir / "structs"
        if structs_dir.exists():
            struct_sizes = {}
            for sf in structs_dir.glob("*.json"):
                sd = json.load(open(sf, encoding='utf-8'))
                sname = sf.stem
                bs = sd.get('binary_size')
                if bs:
                    struct_sizes[sname] = bs
                members = sd.get('known_members', {})
                self.struct_members[sname] = {
                    int(k): (v['name'], v.get('type', ''))
                    for k, v in members.items()
                }

            # Build instance ranges from globals
            if globals_path.exists():
                for addr_str, ginfo in gdata.items():
                    gtype = ginfo.get('type', '')
                    gname = ginfo.get('name', '')
                    if gtype in struct_sizes and gname:
                        base = int(addr_str, 16)
                        self.struct_instances.append(
                            (base, base + struct_sizes[gtype], gname, gtype))
                self.struct_instances.sort()

    def _load_binary(self):
        exe_path = self.project_root / "original" / "PAL3.exe"
        if not exe_path.exists():
            return
        self.exe_data = open(exe_path, 'rb').read()

        # .rdata float literals
        rdata_start = 0x56A000
        rdata_end = 0x571000
        for off in range(rdata_start - 0x400000, rdata_end - 0x400000, 4):
            va = off + 0x400000
            val = _struct.unpack_from('<f', self.exe_data, off)[0]
            if abs(val) < 1e10 and (abs(val) > 1e-10 or val == 0.0):
                key = 'flt_%X' % va
                if val == int(val) and abs(val) < 1000000:
                    self.literals[key] = '%d.0f' % int(val)
                else:
                    self.literals[key] = '%.7gf' % val

        # IDA aXxx string names
        astring_path = self.pipeline_root / "ida" / "_logs" / "ida_astring_names.json"
        if astring_path.exists():
            astrings = json.load(open(astring_path, encoding='utf-8'))
            for aname, ainfo in astrings.items():
                aval = ainfo.get('value', '')
                if aval:
                    escaped = aval.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n').replace('\t', '\\t')
                    self.literals[aname] = '"%s"' % escaped

    def try_read_rdata_string(self, va):
        """Try to read a null-terminated string at a .rdata virtual address."""
        off = va - 0x400000
        if off < 0 or off >= len(self.exe_data):
            return None
        end = self.exe_data.find(b'\x00', off)
        if end <= off or end - off > 260:
            return None
        raw = self.exe_data[off:end]
        if len(raw) < 1:
            return None
        try:
            s = raw.decode('gbk')
        except (UnicodeDecodeError, ValueError):
            return None
        if not all(c == '\t' or c == '\n' or ('\x20' <= c) for c in s):
            return None
        return s


# Module-level singleton
store = DataStore()
