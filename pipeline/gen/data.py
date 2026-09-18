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
        self.project_root = cfg.annotations_dir.parent.parent
        self.header_dir = cfg.output_headers
        self.output_dir = cfg.output_src
        self.pipeline_root = self.project_root / "pipeline"

        # Data tables (populated by load())
        self.literals = {}          # "flt_XXX" -> "1.0f", "aXxx" -> '"string"'
        self.thunks = {}            # "sub_XXX" -> "TargetFunc"
        self.globals_map = {}       # "dword_XXX" -> "g_SceneMgr"
        self.global_types = {}      # "dword_XXX" -> "int[4]"
        self.struct_instances = []  # [(base, end, name, type)]
        self.struct_members = {}    # type -> {offset: (name, member_type)}
        self.struct_bases = {}      # type -> {base_name: offset}（限定形 __vftable 的偏移解析用）
        self.struct_base_names = {} # type -> [直接基类名, 按声明顺序]
        self.game_classes = set()   # class names with .h files
        self.thunk_classes = set()  # j_ClassName thunk type names
        self.static_methods = set() # "ClassName::Method" for __cdecl methods
        self.method_sigs = {}       # "ClassName::Method" -> decomp signature (ret-type lookup)
        self.declared_globals = set()  # already in globals.h
        self.free_func_sigs = {}    # "FuncName" -> "ret FuncName(params)" declaration
        self.exe_data = b''         # raw exe for .rdata string lookup
        self.skip_classes = set()   # classes to not generate
        self.global_addrs = {}      # name -> base_address (from ida_structs.json _globals)
        self.scalar_dtor_classes = set()  # classes that had _scalar_dtor filtered
        self.struct_vtables = {}    # "ClassName" -> {slot_index: method_name} (from annotations)
        self.skip_globals = {}      # {name: addr} — annotation-skipped globals
        self.skip_funcs = set()     # function names from skip_functions.json (non-thunk)
        self.annotated_globals = {} # "dword_ADDR" -> (name, type) from globals.json

    def load(self):
        """Load all resources from disk. Call once at startup."""
        if self.loaded:
            return
        self._load_game_classes()
        self._load_globals_h()
        self._load_exported_data()
        self._load_vtable_data()
        self._load_struct_bases()
        self._load_annotated_globals()
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
        globals_h = self.project_root / "pal3" / "src" / "globals.h"
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
        # Separate skip entries from real globals
        _skip_names = set()
        for _addr_s, _ginfo in list(_globals.items()):
            if _ginfo.get('type') == 'skip':
                _skip_names.add(_ginfo.get('name', ''))
                _skip_addr = int(_addr_s, 16) if isinstance(_addr_s, str) else _addr_s
                self.skip_globals[_ginfo.get('name', '')] = _skip_addr
        ida_prefixes = ('dword', 'byte', 'word', 'stru', 'off', 'unk', 'flt')
        for addr_str, ginfo in _globals.items():
            gname = ginfo.get('name', '')
            gtype = ginfo.get('type', '')
            if gname and gtype:
                self.global_types[gname] = gtype
            if gname in _skip_names:
                continue
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
                variants = sinfo.get('_variants', {})
                self.struct_members[sname] = {}
                for dm in dms:
                    mname = dm['name']
                    mtype = dm.get('type', 'int')
                    off = dm['offset']
                    # Restore annotation-preserved array type (IDA truncates arrays to span)
                    var_info = variants.get(str(off)) or variants.get(str(int(off)))
                    if var_info:
                        vt = var_info.get('type', '')
                        if isinstance(vt, str) and vt.endswith(']') and '[' in vt:
                            mtype = vt
                    self.struct_members[sname][off] = (mname, mtype)

        # 3. Struct instances from _globals + struct sizes
        _struct_sizes = {
            sname: sinfo.get('size', 0)
            for sname, sinfo in ida_structs.items()
            if not sname.startswith('_') and sinfo.get('size', 0)
        }
        self.struct_sizes = dict(_struct_sizes)  # for _resolve_offset array resolution
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

        # 3b. Skip function names from export metadata
        self.skip_funcs = set(ida_structs.get('_skip_function_names', {}).get('_names', []))

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
                        if _mname:
                            if '::' in _mname:
                                _method = _mname.split('::')[-1]
                            else:
                                _method = _mname  # short name, use directly
                            if _method not in _slot_map.values():
                                _slot_map[_i] = _method
            if _slot_map:
                self.struct_vtables[_name] = _slot_map

        # 5a. Load globals.json annotations for extern generation

    def _load_struct_bases(self):
        """type -> {base_name: offset}，供 `_fold_vftable_mask` 解析**限定形**
        `this->A::B::__vftable` 的总偏移（限定形原先被整块跳过 —— 见该函数 docstring 的
        "qualified base accesses `X->Base::__vftable` — base offset unknown"）。

        offset 来源，**优先显式、绝不猜**：
          1. 注解 `bases` 里的显式 `offset`（每个写入的类都在 `bases_source` 里附 A 级依据）；
          2. 若无 `bases`：**只给"首个基类"填 0** —— 这是 MS C++ ABI 的事实
             （主基类子对象必在偏移 0），不是猜测；**其余基类不写入**，
             于是 `_fold_vftable_mask` 对它们保持"原样跳过"的旧行为。
        """
        _dir = self.annotations_dir / "structs"
        if not _dir.exists():
            return
        for _f in sorted(_dir.glob("*.json")):
            try:
                _ann = json.load(open(_f, encoding='utf-8'))
            except Exception:
                continue
            _name = _ann.get('name') or _f.stem
            _bases = _ann.get('bases')
            m = {}
            if isinstance(_bases, list) and _bases and isinstance(_bases[0], dict):
                for _b in _bases:
                    if 'name' in _b and 'offset' in _b:
                        m[_b['name']] = _b['offset']
            else:
                _bc = _ann.get('base_class')
                _names = _bc if isinstance(_bc, list) else ([_bc] if _bc else [])
                if _names:
                    m[_names[0]] = 0        # ABI: 主基类子对象在偏移 0
            if m:
                self.struct_bases[_name] = m
            # 直接基类名单（含无 offset 的）—— 供"某名字到底是不是基类"的判定，
            # 该判定**不需要偏移**，故名单本身即可用。
            _bc2 = _ann.get('base_class')
            _n2 = _bc2 if isinstance(_bc2, list) else ([_bc2] if _bc2 else [])
            if _n2:
                self.struct_base_names[_name] = [x for x in _n2 if x]

    def _load_annotated_globals(self):
        """Load globals.json for extern generation of non-IDA globals."""
        _ann_path = self.project_root / "data" / "annotations" / "globals.json"
        if not _ann_path.exists():
            return
        try:
            _data = json.load(open(_ann_path, encoding='utf-8'))
        except:
            return
        ida_prefixes = ('dword_', 'byte_', 'word_', 'stru_', 'off_', 'unk_', 'flt_')
        for _addr_s, _info in _data.items():
            if _info.get('type') == 'skip':
                continue
            _name = _info.get('name', '')
            _type = _info.get('type', '')
            if not _name or not _type:
                continue
            try:
                _addr = int(_addr_s, 16) if isinstance(_addr_s, str) else int(_addr_s, 0)
            except ValueError:
                continue
            _addr_hex = '%X' % _addr
            # Add all possible raw names for extern generation and name resolution
            for _pfx in ('dword', 'byte', 'word', 'flt', 'off', 'stru', 'unk'):
                _raw = '%s_%s' % (_pfx, _addr_hex)
                self.annotated_globals[_raw] = (_name, _type)
                self.globals_map[_raw] = _name

        # 5b. Free function sigs + static methods + scalar_dtor detection from decomp JSONs
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
                # Normalize IDA __hidden this marker (apply_annotations writes
                # method types as `Cls *__hidden this`; consume as `Cls *this`)
                _sig = _re2.sub(r'\b__hidden\s+', '', _sig)
                # Normalize Hex-Rays struct-return sret param (not a real param);
                # the sret spelling means by-value return, so drop one '*' from ret
                if '__return_ptr' in _sig:
                    _sig = _re2.sub(r'\s*,?\s*[A-Za-z_][\w:]*(?:\s*\*+)?\s*__return_ptr\s+\w+\s*,?', ' ', _sig)
                    _sig = _re2.sub(r'\(\s*,', '(', _sig)
                    _sig = _re2.sub(r',\s*\)', ')', _sig)
                    _p0 = _sig.find('(')
                    if _p0 > 0:
                        _j = _sig[:_p0].rstrip().rfind('*')
                        if _j != -1:
                            _sig = _sig[:_j] + _sig[_j+1:]
                if not _name or not _sig:
                    continue
                if '::' in _name:
                    # Class method: keep signature for return-type lookups.
                    # decomp `name` carries a param list ("Cls::M(int)") — index
                    # by the bare "Cls::M"; first overload wins (best-effort).
                    # FIX(2026-09-18)：`_name` 是 decomp 的**带参数表**名字
                    # （"Cls::M(int)"），而所有消费方都用**裸名**比：
                    #   ast_transform:529 / :702   ('%s::%s' % (class_name, method_name))
                    #   stage4_substitution:721   ('%s::%s' % (cls, meth))
                    # ⇒ 只要名字带参数表，`in static_methods` 就**恒为假**，
                    # "__cdecl 静态成员的第一个实参是数据、不是 this" 这条守卫从未生效。
                    # 实测 104 条里 96 条带参数表。上行 method_sigs 已 split，这里漏了。
                    # 归一化为裸名（与 method_sigs / 消费方同形）。
                    self.method_sigs.setdefault(_name.split('(')[0], _sig)
                    # detect __cdecl for static_methods
                    if '__cdecl' in _sig and '__thiscall' not in _sig:
                        self.static_methods.add(_name.split('(')[0])
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

        # Supplement: functions.json annotations for free functions missing from decomp
        # (e.g. 1-byte empty functions like NullCallback that Hex-Rays cannot decompile)
        _ann_func_path = self.project_root / "data" / "annotations" / "functions.json"
        if _ann_func_path.exists():
            try:
                _ann_funcs = json.load(open(_ann_func_path, encoding='utf-8'))
            except:
                _ann_funcs = {}
            for _addr_s, _info in _ann_funcs.items():
                if not isinstance(_info, dict):
                    continue
                _name = _info.get('name', '')
                _sig = _info.get('signature', '')
                if not _name or not _sig:
                    continue
                if '::' in _name:
                    continue  # class method, not a free function
                if _name in self.free_func_sigs:
                    continue  # already have it from decomp
                # Same filters as above
                if _name.startswith('_') or _name.startswith('$') or _name.startswith('?'):
                    continue
                # NOTE: do NOT filter unknown_libname/nullsub here — annotation
                # entries are manually curated and may reference such functions
                # (e.g. atexit cleanup handlers).
                if not re.match(r'^[A-Za-z_]\w*$', _name):
                    continue
                # Parse signature — two formats:
                #   decomp: "ret __cc(params)"
                #   functions.json: "ret __cc FuncName(params)"
                _sig_n = re.sub(r'\b__hidden\s+', '', _sig)
                if '__cdecl' in _sig_n or '__stdcall' in _sig_n:
                    m = re.match(r'^(.+?)\s*(__cdecl|__stdcall)\s*(?:\w+\s*)?\((.*)\)$', _sig_n)
                    if m:
                        ret = m.group(1).strip()
                        ret = re.sub(r'\bvirtual\s+', '', ret)
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

    def try_read_rdata_dword(self, va):
        """Read a dword value from .rdata section by virtual address."""
        import struct
        off = va - 0x400000
        if off < 0 or off + 4 > len(self.exe_data):
            return None
        if 0x16A000 <= (va - 0x400000) < 0x16A000 + 0x16000:
            return struct.unpack_from('<I', self.exe_data, off)[0]
        return None


# Module-level singleton
store = DataStore()
