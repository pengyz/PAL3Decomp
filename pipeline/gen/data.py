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
        # Paths from pipeline config (must be configured)
        from pipeline.config import cfg
        self.annotations_dir = cfg.annotations_dir
        self.decomp_dir = cfg.decomp_dir
        self.header_dir = cfg.output_headers
        self.output_dir = cfg.output_src
        self.project_root = cfg.annotations_dir.parent.parent
        self.pipeline_root = self.project_root / "pipeline"

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
        self.global_addrs = {}      # name -> base_address (from ida_structs.json _globals)
        self.scalar_dtor_classes = set()  # classes that had _scalar_dtor filtered
        self.struct_vtables = {}    # "ClassName" -> {slot_index: method_name} (from annotations)

    def load(self):
        """Load all resources from disk. Call once at startup."""
        if self.loaded:
            return
        self._load_game_classes()
        self._load_globals_h()
        self._load_exported_data()
        self._load_vtable_data()
        self._load_binary()
        self.loaded = True

    def _load_game_classes(self):
        for h in self.header_dir.glob("*.h"):
            self.game_classes.add(h.stem)
        gb_dir = self.project_root / "include" / "gbengine"
        if gb_dir.exists():
            for h in gb_dir.glob("*.h"):
                self.game_classes.add(h.stem)
        # Add struct names from ida_structs.json keys (already exported)
        ida_structs_path = self.project_root / "asm" / "pal3" / "ida_structs.json"
        if ida_structs_path.exists():
            try:
                _ida_data = json.load(open(ida_structs_path, encoding='utf-8'))
                for _k in _ida_data:
                    if not _k.startswith('_'):
                        self.game_classes.add(_k)
            except:
                pass
        self.game_classes.update([
            'gbVec3D', 'gbVec2D', 'gbVec4D', 'gbMatrix4', 'gbColorQuad',
            'gbResManager', 'gbLight', 'gbMaterial', 'gbViewPort',
            'gbQuaternion', 'gbPlane', 'gbBoundingBox', 'gbRay',
            'string', 'basic_string',
        ])

    def _load_globals_h(self):
        globals_h = self.project_root / "include" / "pal3" / "gen" / "globals.h"
        if globals_h.exists():
            for line in open(globals_h, encoding='utf-8', errors='replace'):
                m = re.search(r'extern\s+\S.*?\b(\w+)\s*(?:\[|;)', line)
                if m:
                    self.declared_globals.add(m.group(1))

    def _load_exported_data(self):
        """Load all data from exported JSONs (NOT from annotations).

        Sources:
          - asm/pal3/ida_structs.json: struct defs, globals, methods
          - asm/pal3/decomp/*.json: function signatures for free funcs, static methods
        """
        ida_structs_path = self.project_root / "asm" / "pal3" / "ida_structs.json"
        ida_structs = {}
        if ida_structs_path.exists():
            try:
                ida_structs = json.load(open(ida_structs_path, encoding='utf-8'))
            except:
                pass

        # 1. Globals: name mapping + type info from ida_structs._globals
        _globals = ida_structs.get('_globals', {})
        ida_prefixes = ('dword', 'byte', 'word', 'stru', 'off', 'unk', 'flt')
        for addr_str, ginfo in _globals.items():
            gname = ginfo.get('name', '')
            gtype = ginfo.get('type', '')
            if gname and gtype:
                self.global_types[gname] = gtype
            # Build name->address lookup for identifier resolution in stage4
            if gname:
                addr_int = int(addr_str, 16) if isinstance(addr_str, str) else addr_str
                self.global_addrs[gname] = addr_int
            if gname and not any(gname.startswith(p + '_') for p in ida_prefixes):
                addr_int = int(addr_str, 16) if isinstance(addr_str, str) else addr_str
                addr_hex = '%X' % addr_int
                for pfx in ida_prefixes:
                    self.globals_map['%s_%s' % (pfx, addr_hex)] = gname

        # 2. Struct members from ida_structs data_members
        for sname, sinfo in ida_structs.items():
            if sname.startswith('_'):
                continue
            dms = sinfo.get('data_members', [])
            if dms:
                self.struct_members[sname] = {
                    dm['offset']: (dm['name'], dm.get('type', 'int'))
                    for dm in dms
                }

        # 3. Struct instances from _globals + struct sizes
        _struct_sizes = {
            sname: sinfo.get('size', 0)
            for sname, sinfo in ida_structs.items()
            if not sname.startswith('_') and sinfo.get('size', 0)
        }
        import re as _re
        for addr_str, ginfo in _globals.items():
            gtype = ginfo.get('type', '')
            gname = ginfo.get('name', '')
            if not gname or not gtype:
                continue
            if gtype in _struct_sizes:
                base = int(addr_str, 16) if isinstance(addr_str, str) else addr_str
                self.struct_instances.append(
                    (base, base + _struct_sizes[gtype], gname, gtype))
            else:
                arr_m = _re.match(r'^(\w+)\[(\d+)\]$', gtype)
                if arr_m:
                    elem_type = arr_m.group(1)
                    count = int(arr_m.group(2))
                    elem_size = _struct_sizes.get(elem_type, 0)
                    if elem_size and elem_type in self.struct_members:
                        base = int(addr_str, 16) if isinstance(addr_str, str) else addr_str
                        for idx in range(count):
                            elem_base = base + idx * elem_size
                            elem_name = '%s[%d]' % (gname, idx)
                            self.struct_instances.append(
                                (elem_base, elem_base + elem_size, elem_name, elem_type))
        self.struct_instances.sort()

        # 4. Thunks from skip_functions.json (manually curated thunk replacements)
        _skip_path = self.project_root / "data" / "annotations" / "skip_functions.json"
        if _skip_path.exists():
            try:
                _skip_data = json.load(open(_skip_path, encoding='utf-8'))
                for _addr_s, _tinfo in _skip_data.items():
                    if _tinfo.get('reason') != 'thunk':
                        continue
                    _tname = _tinfo.get('name', '')
                    _ttarget = _tinfo.get('target_name', '')
                    if not _tname or not _ttarget:
                        continue
                    self.thunks[_tname] = _ttarget
                    self.thunks[_tname.replace('~', '_')] = _ttarget.replace('~', '_')
                    if '::' in _tname:
                        _short = _tname.split('::')[1]
                        if _short not in ('Destroy', 'Create', 'Update', 'Render', 'Init',
                                          'Reset', 'Load', 'Save', 'Release', 'Free', 'Show',
                                          'Hide', 'Set', 'Get', 'Add', 'Remove', 'Clear',
                                          'Move', 'Copy', 'Find', 'Close', 'Open',
                                          'IsValid', 'IsReady', 'Process', 'Handle',
                                          'CCBAI', 'MoveWindow'):
                            if _short not in self.thunks:
                                self.thunks[_short] = _ttarget
                            _short_dtor = _short.replace('~', '_')
                            if _short_dtor not in self.thunks:
                                self.thunks[_short_dtor] = _ttarget.replace('~', '_')
                        self.thunk_classes.add(_tname.split('::')[0] if '::' in _tname else '')
            except:
                pass
        self.thunk_classes.add('j_std')
        self.thunk_classes.add('j_j_codecvt_base')

    def _load_vtable_data(self):
        """Load vtable slot→method mapping from struct annotations.

        This is the ONLY place codegen reads from annotations (architectural exception).
        Vtable slot resolution requires method names that only exist in annotations.
        """
        _structs_dir = self.annotations_dir / "structs"
        if not _structs_dir.exists():
            return
        for _f in sorted(_structs_dir.glob("*.json")):
            try:
                _ann = json.load(open(_f, encoding='utf-8'))
            except:
                continue
            _name = _ann.get('name', '')
            _vtables = _ann.get('vtables', [])
            _methods = _ann.get('methods', {})
            if not _vtables or not _methods:
                continue
            _slot_map = {}
            for _vt in _vtables:
                for _i, _slot in enumerate(_vt.get('slots', [])):
                    _addr = _slot.get('addr', '')
                    if _addr in _methods:
                        _mname = _methods[_addr].get('name', '')
                        if _mname and '::' in _mname:
                            _method = _mname.split('::')[-1]
                            if _method not in _slot_map.values():
                                _slot_map[_i] = _method
            if _slot_map:
                self.struct_vtables[_name] = _slot_map

        # 5. Free function sigs + static methods + scalar_dtor detection from decomp JSONs
        _decomp_dir = self.project_root / "asm" / "pal3" / "decomp"
        if _decomp_dir.exists():
            # Pre-scan for _scalar_dtor classes (needed before header generation)
            for _df in sorted(_decomp_dir.glob("*.json")):
                try:
                    _dd = json.load(open(_df, encoding='utf-8'))
                except:
                    continue
                _name = _dd.get('name', '')
                if '::' in _name:
                    _cls = _name.split('::')[0]
                    _method = _name.split('::', 1)[1].split('(')[0]
                    if '_scalar_dtor' in _method or _method == '_sdtor':
                        self.scalar_dtor_classes.add(_cls)
            import re as _re2
            _IDA_MACROS = {'Func', 'JUMPOUT', 'NAN', 'LOBYTE', 'HIBYTE',
                           'LOWORD', 'HIWORD', 'LODWORD', 'HIDWORD'}
            for _df in sorted(_decomp_dir.glob("*.json")):
                try:
                    _dd = json.load(open(_df, encoding='utf-8'))
                except:
                    continue
                _name = _dd.get('name', '')
                _sig = _dd.get('signature', '')
                if not _name or not _sig:
                    continue
                if '::' in _name:
                    # Class method: detect __cdecl for static_methods
                    if '__cdecl' in _sig and '__thiscall' not in _sig:
                        self.static_methods.add(_name)
                else:
                    # Free function: build forward declaration
                    if _name.startswith('_') or _name.startswith('$') or _name.startswith('?'):
                        continue
                    if 'unknown_libname' in _name or 'nullsub' in _name:
                        continue
                    if not _re2.match(r'^[A-Za-z_]\w*$', _name):
                        continue
                    if _name in _IDA_MACROS:
                        continue
                    # Parse signature: "ret __cc(params)"
                    # Strip 'virtual' from free function signatures (Hex-Rays adds it
                    # for vtable-related thunks, but free functions cannot be virtual).
                    if '__thiscall' in _sig:
                        m = _re2.match(r'^(.+?)\s*__thiscall\s*\((.*)\)$', _sig)
                        if m:
                            ret = m.group(1).strip()
                            ret = _re2.sub(r'\bvirtual\s+', '', ret)
                            params = m.group(2).strip()
                            if not params: params = 'void'
                            params = _re2.sub(r'\bthis\b', '_this', params)
                            self.free_func_sigs[_name] = '%s %s(%s)' % (ret, _name, params)
                    elif '__cdecl' in _sig or '__stdcall' in _sig:
                        m = _re2.match(r'^(.+?)\s*(__cdecl|__stdcall)\s*\((.*)\)$', _sig)
                        if m:
                            ret = m.group(1).strip()
                            ret = _re2.sub(r'\bvirtual\s+', '', ret)
                            cc = m.group(2)
                            params = m.group(3).strip()
                            if not params: params = 'void'
                            if cc == '__cdecl':
                                self.free_func_sigs[_name] = '%s %s(%s)' % (ret, _name, params)
                            else:
                                self.free_func_sigs[_name] = '%s %s %s(%s)' % (ret, cc, _name, params)

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
