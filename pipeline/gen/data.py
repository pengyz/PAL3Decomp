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
        # Paths from config
        try:
            from pipeline.config import cfg
            self.annotations_dir = cfg.annotations_dir
            self.decomp_dir = cfg.decomp_dir
            self.header_dir = cfg.output_headers
            self.output_dir = cfg.output_src
            self.project_root = cfg.annotations_dir.parent.parent
            self.pipeline_root = self.project_root / "pipeline"
        except (ImportError, SystemExit):
            # Fallback for standalone usage
            self.pipeline_root = Path(__file__).parent.parent
            self.project_root = self.pipeline_root.parent
            self.annotations_dir = self.project_root / "data" / "annotations"
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
        self.free_func_sigs = {}    # "FuncName" -> "ret FuncName(params)" declaration
        self.exe_data = b''         # raw exe for .rdata string lookup
        self.skip_classes = set()   # classes to not generate
        self.functions_ann = {}     # "0x00XXXXXX" -> {name, signature} from annotations

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
        # Also include gbengine classes for ctor/dtor detection
        gb_dir = self.project_root / "include" / "gbengine"
        if gb_dir.exists():
            for h in gb_dir.glob("*.h"):
                self.game_classes.add(h.stem)
        # Add struct names from annotations (covers engine types like gbVec3D)
        structs_dir = self.project_root / "data" / "annotations" / "structs"
        if structs_dir.exists():
            for f in structs_dir.glob("*.json"):
                self.game_classes.add(f.stem)
        # Common engine structs not in annotation files
        self.game_classes.update([
            'gbVec3D', 'gbVec2D', 'gbVec4D', 'gbMatrix4', 'gbColorQuad',
            'gbResManager', 'gbLight', 'gbMaterial', 'gbViewPort',
            'gbQuaternion', 'gbPlane', 'gbBoundingBox', 'gbRay',
            'string', 'basic_string',
        ])

    def _load_globals_h(self):
        globals_h = self.project_root / "include" / "pal3" / "globals.h"
        if globals_h.exists():
            for line in open(globals_h, encoding='utf-8', errors='replace'):
                m = re.search(r'extern\s+\S.*?\b(\w+)\s*(?:\[|;)', line)
                if m:
                    self.declared_globals.add(m.group(1))

    def _load_annotations(self):
        # functions.json → static methods + thunks + full annotation lookup
        funcs_path = self.annotations_dir / "functions.json"
        if funcs_path.exists():
            funcs = json.load(open(funcs_path, encoding='utf-8'))
            self.functions_ann = funcs
            for addr, info in funcs.items():
                name = info.get('name', '')
                sig = info.get('signature', '')
                if '::' in name and '__cdecl' in sig:
                    self.static_methods.add(name)

        # Hardcoded gbengine static methods (not in PAL3.exe functions.json)
        # These are methods that IDA decompiles as static calls but headers declare as members
        self.static_methods.update([
        ])

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
                if gtype == 'skip':
                    continue  # known-unnameable: don't substitute in codegen
                if gname and gtype:
                    self.global_types[gname] = gtype
                if not gname or any(gname.startswith(p + '_') for p in ida_prefixes):
                    continue
                addr_int = int(addr_str, 16)
                addr_hex = '%X' % addr_int
                for pfx in ida_prefixes:
                    self.globals_map['%s_%s' % (pfx, addr_hex)] = gname
                # Map decompiler-generated name to annotation name
                decomp_name = ginfo.get('decomp_name', '')
                if decomp_name:
                    self.globals_map[decomp_name] = gname

        # functions.json → free function signatures for forward declarations
        funcs_path = self.annotations_dir / "functions.json"
        if funcs_path.exists():
            import re as _re
            fdata = json.load(open(funcs_path, encoding='utf-8'))
            for addr_s, finfo in fdata.items():
                fname = finfo.get('name', '')
                fsig = finfo.get('signature', '')
                if '::' in fname or not fname or not fsig:
                    continue
                if '__thiscall' in fsig:
                    # __thiscall without class (no ::) → emit as cdecl with explicit this
                    if fname.startswith('_') or fname.startswith('$') or fname.startswith('?'):
                        continue
                    if 'unknown_libname' in fname or 'nullsub' in fname:
                        continue
                    if not _re.match(r'^[A-Za-z_]\w*$', fname):
                        continue
                    m = _re.match(r'^(.+?)\s*__thiscall\s*\((.*)\)$', fsig)
                    if m:
                        ret = m.group(1).strip()
                        params = m.group(2).strip()
                        if not params:
                            params = 'void'
                        # Replace 'this' keyword in params with '_this'
                        params = _re.sub(r'\bthis\b', '_this', params)
                        self.free_func_sigs[fname] = '%s %s(%s)' % (ret, fname, params)
                    continue
                if '__cdecl' not in fsig and '__stdcall' not in fsig:
                    continue
                if fname.startswith('_') or fname.startswith('$') or fname.startswith('?'):
                    continue
                if 'unknown_libname' in fname or 'nullsub' in fname:
                    continue
                # Skip names that conflict with ida_defs.h macros
                _IDA_MACROS = {'Func', 'JUMPOUT', 'NAN', 'LOBYTE', 'HIBYTE',
                               'LOWORD', 'HIWORD', 'LODWORD', 'HIDWORD'}
                if fname in _IDA_MACROS:
                    continue
                m = _re.match(r'^(.+?)\s*(__cdecl|__stdcall)\s*\((.*)\)$', fsig)
                if not m:
                    continue
                ret = m.group(1).strip()
                callconv = m.group(2)
                params = m.group(3).strip()
                if not params:
                    params = 'void'
                if callconv == '__cdecl':
                    self.free_func_sigs[fname] = '%s %s(%s)' % (ret, fname, params)
                else:
                    self.free_func_sigs[fname] = '%s %s %s(%s)' % (ret, callconv, fname, params)

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
                import re as _re
                for addr_str, ginfo in gdata.items():
                    gtype = ginfo.get('type', '')
                    gname = ginfo.get('name', '')
                    if not gname or ginfo.get('type') == 'skip':
                        continue
                    if gtype in struct_sizes:
                        base = int(addr_str, 16)
                        self.struct_instances.append(
                            (base, base + struct_sizes[gtype], gname, gtype))
                    else:
                        # Handle array types: TypeName[N]
                        arr_m = _re.match(r'^(\w+)\[(\d+)\]$', gtype)
                        if arr_m:
                            elem_type = arr_m.group(1)
                            count = int(arr_m.group(2))
                            elem_size = struct_sizes.get(elem_type, 0)
                            if elem_size and elem_type in self.struct_members:
                                base = int(addr_str, 16)
                                # Register each array element as a separate instance
                                for idx in range(count):
                                    elem_base = base + idx * elem_size
                                    elem_name = '%s[%d]' % (gname, idx)
                                    self.struct_instances.append(
                                        (elem_base, elem_base + elem_size, elem_name, elem_type))
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
