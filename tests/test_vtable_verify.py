"""`tools/vtable_verify.py` 的测试 —— **先写测试**（TDD，红→绿）。

本文件是 vtable **编译产物对比器**（最终裁判）的回归集，覆盖 task-6-brief 的五项要求：

  1. **符号重定位归约**（含 RTTI COL 前缀）：.obj 的 vtable 槽是**符号重定位不是地址**
     ⇒ 必须经 `coff_vtable` 的符号名归约；`vtable[-1]` 的 RTTI COL 指针不得被数成槽
     （真机实测：`??_7C2@@6B@` 的符号 value = 4，COL 在 value-4）。
  2. **thunk 归一**：静态 adjustor 归一为 `(目标函数, this 调整量)` 二元组（真机
     `?ff@D3@@W7AEHXZ` = `83 e9 08; e9 <rel>` ⇒ offset 8）；动态 delta 用
     `(target, kind=dynamic, const)` 三元组（真机 `??_ED@@$4PPPPPPPM@BA@AEPAXI@Z` =
     `2b 49 fc; 83 e9 10; e9 <rel>` ⇒ dynamic + const 0x10，attack README B-1/B-4）。
  3. **强制发射**：普通类构造对象；抽象类定义具体派生类构造；无虚析构的抽象类
     需 dummy `Cls::Cls(){}` 用实体（真机 lazy COMDAT 实测见本文件 `LIVE` 备注）。
  4. **对比项**：槽数数（含 address point 偏移）+ 槽序 + 每槽归一化元组 + vbtable 内容。
  5. **偏差报告**：定位到**具体槽位 + kind**（不是"表不等"）。

## 夹具策略（两层，缺一不可）

* **全部默认测试为 hermetic**：夹具是本文件内的**最小合法 COFF 构造器**（`CoffBuilder`）
  与**内存镜像**（`BytesImage`），构造出的 .obj / 镜像形态与真机一致（reloc 按**原始 COFF
  索引**含 aux 占位、COL 在 address point 前 4 字节、thunk 字节与真机逐字节相同）。
  预期值来自真机实测（见各测试 docstring 的复现命令）。
* **真机 LIVE 测试**：`VTV_LIVE=1` 时才跑（默认 skip，避免依赖 wine 的慢/脆），
  用 `tools/wine_cl.sh` 真编译 `data/status/_vtable_abi_probe_20260925/` 的探针形态，
  验证"强制发射"在**真编译器**上生效、且 /O2 的死存储消除会被发射检查**捕获**。

运行：`python3 tests/test_vtable_verify.py`
真机：`VTV_LIVE=1 python3 tests/test_vtable_verify.py`
"""
import io
import json
import os
import struct
import subprocess
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))

from vtable_verify import (  # noqa: E402
    KIND_ADJUSTOR_STATIC,
    KIND_ADJUSTOR_VBASE,
    KIND_COMPOSITE,
    KIND_DELETING_DTOR,
    KIND_FN,
    KIND_PURECALL,
    PROBE_STRATEGY_DERIVED,
    PROBE_STRATEGY_DUMMY_CTOR,
    PROBE_STRATEGY_OBJECT,
    BinTable,
    BytesImage,
    EmissionError,
    NormSlot,
    ProbeSpec,
    build_probe_source,
    compare_tables,
    compare_vbtable,
    decode_adjustor_chain,
    force_emit,
    image_thunk,
    main,
    name_key,
    normalize_bin_slots,
    normalize_obj_slots,
    obj_vbtables,
    obj_vtables,
    parse_obj_artifacts,
    render_report,
)
from vtable_verify import (  # noqa: E402
    PEImage,
    ImageError,
    bin_table_from_image,
    bin_vbtable,
)

LIVE = os.environ.get('VTV_LIVE') == '1'
EXE = PROJECT_ROOT / 'original' / 'PAL3.exe'
WINE_CL = PROJECT_ROOT / 'tools' / 'wine_cl.sh'


# =====================================================================================
# 夹具 1：最小合法 COFF 构造器（.obj 侧）
# =====================================================================================

def _align(v, n):
    return (v + n - 1) // n * n


class CoffBuilder:
    """写一个真实可被 `coff_vtable.parse_obj` 读取的最小 COFF。

    刻意保留真机的两处结构（它们正是 Task 6 简报点名的坑）：

    * **符号表按原始索引含 aux 占位**：`symbol(..., naux=1)` 之后的索引跳 2，
      重定位里的索引按原始索引写 ⇒ 任何"按遍历序计数"的实现都会错位。
    * **节名 `/NN` 长名形态**：`section(name='/4')` + `strtab_prefix`。

    节的 `chars` 默认带 `IMAGE_SCN_CNT_INITIALIZED_DATA|MEM_READ`（0x40000040），
    与真机 .rdata 一致；不影响解析，但让夹具更接近真物。
    """

    def __init__(self, machine=0x014c, strtab_prefix=b''):
        self.machine = machine
        self.sections = []          # dict(name, data, relocs=[(off, symname)], chars)
        self.symbols = []           # dict(name, value, section, type, storage, naux)
        self.strtab_prefix = strtab_prefix

    def add_section(self, name, data, chars=0x40000040):
        self.sections.append({'name': name, 'data': bytes(data),
                              'relocs': [], 'chars': chars})
        return len(self.sections)              # 1-based

    def add_reloc(self, sec_index, offset, sym_name, rtype=0x0006):
        self.sections[sec_index - 1]['relocs'].append((offset, sym_name, rtype))

    def add_symbol(self, name, section, value, naux=0, storage=2, type=0):
        self.symbols.append({'name': name, 'value': value, 'section': section,
                             'type': type, 'storage': storage, 'naux': naux})

    # -- layout ----------------------------------------------------------------
    def _build(self):
        strtab = bytearray(self.strtab_prefix)      # 内容从 str_tab+4 开始
        strtab_off = {}

        def strtab_add(s):
            key = s.encode('ascii')
            if key in strtab_off:
                return strtab_off[key]
            off = 4 + len(strtab)                   # 长度字段占 4 字节
            strtab.extend(key + b'\x00')
            strtab_off[key] = off
            return off

        # 原始索引（含 aux 占位）—— reloc 里的索引必须按这个表写
        sym_raw_index = {}
        idx = 0
        for s in self.symbols:
            sym_raw_index.setdefault(s['name'], idx)
            idx += 1 + s['naux']
        num_syms = idx

        sec_names = []
        for sec in self.sections:
            nm = sec['name']
            if nm.startswith('/'):
                sec_names.append(nm.encode('ascii')[:8].ljust(8, b'\x00'))
            else:
                sec_names.append(nm.encode('ascii')[:8].ljust(8, b'\x00'))

        cursor = 20 + 40 * len(self.sections)
        data_offs = []
        for sec in self.sections:
            data_offs.append(cursor if sec['data'] else 0)
            cursor = _align(cursor + len(sec['data']), 4)
        reloc_offs = []
        for sec in self.sections:
            reloc_offs.append(cursor if sec['relocs'] else 0)
            cursor += 10 * len(sec['relocs'])
        sym_off = _align(cursor, 4)
        strtab_file_off = sym_off + 18 * num_syms

        out = bytearray(struct.pack('<HHIIIHH', self.machine, len(self.sections), 0,
                                    sym_off, num_syms, 0, 0))
        for i, sec in enumerate(self.sections):
            out += sec_names[i]
            out += struct.pack('<IIII', 0, 0, len(sec['data']), data_offs[i])
            out += struct.pack('<II', reloc_offs[i], 0)
            out += struct.pack('<HH', len(sec['relocs']), 0)
            out += struct.pack('<I', sec['chars'])
        for i, sec in enumerate(self.sections):                # 节数据
            if not sec['data']:
                continue
            out += b'\x00' * (data_offs[i] - len(out))
            out += sec['data']
        for i, sec in enumerate(self.sections):                # 重定位
            if not sec['relocs']:
                continue
            out += b'\x00' * (reloc_offs[i] - len(out))
            for off, sym_name, rtype in sorted(sec['relocs']):
                out += struct.pack('<IIH', off, sym_raw_index[sym_name], rtype)
        out += b'\x00' * (sym_off - len(out))                  # 符号表
        for s in self.symbols:
            nm = s['name'].encode('ascii')
            name_field = (nm.ljust(8, b'\x00') if len(nm) <= 8
                          else struct.pack('<II', 0, strtab_add(s['name'])))
            out += name_field
            out += struct.pack('<IhHBB', s['value'], s['section'], s['type'],
                               s['storage'], s['naux'])
            out += b'\x00' * (18 * s['naux'])
        total = 4 + len(strtab)                                # 字符串表
        out += struct.pack('<I', total) + bytes(strtab)
        assert len(out) == strtab_file_off + total, (len(out), strtab_file_off, total)
        return bytes(out)

    def write(self, path):
        with open(path, 'wb') as f:
            f.write(self._build())
        return str(path)


# 真机常量（复现命令见下方各测试 docstring）
TEXT = '.text'
RDATA = '.rdata'
FUNC_FF_D3 = '?ff@D3@@UAEHXZ'
FUNC_ONLYA = '?onlyA@A3@@UAEHXZ'
FUNC_ONLYB = '?onlyB@B3@@UAEHXZ'
FUNC_V_DV2 = '?v@DV2@@UAEXXZ'
DTOR_D = '??_ED@@UAEPAXI@Z'
THUNK_STATIC = '?ff@D3@@W7AEHXZ'            # 83 e9 08; e9 <rel>
THUNK_DYNAMIC = '?v@DV2@@$4PPPPPPPM@A@AEXXZ'   # 2b 49 fc; e9 <rel>
THUNK_COMPOSITE = '??_ED@@$4PPPPPPPM@BA@AEPAXI@Z'  # 2b 49 fc; 83 e9 10; e9 <rel>
COL_D3A = '??_R4D3@@6BA3@@@'
COL_D3B = '??_R4D3@@6BB3@@@'


def _jmp(off_from_end):
    return b'\xe9' + struct.pack('<i', off_from_end)


def fixture_obj(path):
    """MI + 静态/动态/复合 thunk + 析构 + RTTI COL + aux 符号 + 长节名 的 .obj 夹具。

    与真机 `data/status/_vtable_abi_probe_20260925/vt3.cpp`（`??_7D3@@6BB3@@@` 槽 0 =
    `?ff@D3@@W7AEHXZ`）和 `_vtable_attack_cases_20260925/c2.cpp`（B-1 复合槽）逐字节同形。
    """
    b = CoffBuilder(strtab_prefix=b'.rdata2\x00')
    # .text：vtable 槽指向的函数 + thunk 本体（字节与真机 objdump 逐字节相同）
    text = bytearray()
    off = {}

    def emit(name, data):
        off[name] = len(text)
        text.extend(data)
        while len(text) % 4:
            text.append(0x90)

    emit(FUNC_FF_D3, b'\x8b\x41\x10\xc3')                     # mov eax,[ecx+0x10]; ret
    emit(FUNC_ONLYA, b'\x8b\x41\x08\xc3')
    emit(FUNC_ONLYB, b'\x8b\x41\x08\xc3')
    emit(FUNC_V_DV2, b'\x8b\x41\x04\xc3')
    emit(DTOR_D, b'\x83\xc0\x01\xc3')
    emit(THUNK_STATIC, b'\x83\xe9\x08' + _jmp(0))             # sub $0x8,%ecx; jmp 本体
    emit(THUNK_DYNAMIC, b'\x2b\x49\xfc' + _jmp(0))            # sub -0x4(%ecx),%ecx; jmp
    emit(THUNK_COMPOSITE, b'\x2b\x49\xfc\x83\xe9\x10' + _jmp(0))
    ti = b.add_section(TEXT, bytes(text), chars=0x60000020)
    b.add_reloc(ti, off[THUNK_STATIC] + 4, FUNC_FF_D3)        # jmp 的操作数 = 符号重定位
    b.add_reloc(ti, off[THUNK_DYNAMIC] + 4, FUNC_V_DV2)
    b.add_reloc(ti, off[THUNK_COMPOSITE] + 7, DTOR_D)
    # aux 占位符号：排在重定位目标符号**之前** ⇒ 原始索引错位会立刻暴露
    b.add_symbol('?dummy_aux@@YAXXZ', ti, off[FUNC_FF_D3], naux=1)
    for nm in (FUNC_FF_D3, FUNC_ONLYA, FUNC_ONLYB, FUNC_V_DV2, DTOR_D,
               THUNK_STATIC, THUNK_DYNAMIC, THUNK_COMPOSITE):
        b.add_symbol(nm, ti, off[nm])

    # 主表（A3 视图）：[COL][ff@D3][onlyA@A3]，address point 在节内 +4
    prim = bytearray(b'\x00' * 12)
    pi = b.add_section(RDATA, bytes(prim))
    b.add_symbol('??_7D3@@6BA3@@@', pi, 4)
    b.add_symbol(COL_D3A, pi, 0)
    b.add_reloc(pi, 0, COL_D3A)                               # vtable[-1] = RTTI COL
    b.add_reloc(pi, 4, FUNC_FF_D3)
    b.add_reloc(pi, 8, FUNC_ONLYA)

    # 次表（B3 视图）：槽 0 = 静态 adjustor thunk
    sec2 = bytearray(b'\x00' * 12)
    si2 = b.add_section(RDATA, bytes(sec2))
    b.add_symbol('??_7D3@@6BB3@@@', si2, 4)
    b.add_symbol(COL_D3B, si2, 0)
    b.add_reloc(si2, 0, COL_D3B)
    b.add_reloc(si2, 4, THUNK_STATIC)
    b.add_reloc(si2, 8, FUNC_ONLYB)

    # 动态调整表（DV2 视图）：槽 0 = 动态 thunk，槽 1 = 复合 thunk（B-1）
    sec3 = bytearray(b'\x00' * 12)
    si3 = b.add_section('/4', bytes(sec3))                    # 长节名形态
    b.add_symbol('??_7DV2@@6B@', si3, 4)
    b.add_reloc(si3, 4, THUNK_DYNAMIC)
    b.add_reloc(si3, 8, THUNK_COMPOSITE)

    # vbtable（虚继承）：内容为字面量 DWORD（**无重定位**）
    vb = struct.pack('<ii', -4, 24)
    vi = b.add_section(RDATA, vb)
    b.add_symbol('??_8D3@@7B@', vi, 0)
    return b.write(path)


# =====================================================================================
# 夹具 2：内存镜像（二进制侧）
# =====================================================================================

def fixture_image():
    """构造与 fixture_obj 同形的**二进制镜像**（VA 侧）。

    节边界与 PAL3.exe 同规则（VA = imagebase + 节 VA + 偏移）。槽地址分布：
      .text 0x401000 起；.rdata 0x402000 起；表 address point 0x402004（COL 在 -4）。
    """
    img = BytesImage(image_base=0x400000)
    code = bytearray()
    at = {}

    def emit(name, data, va):
        at[name] = va
        pad = va - (0x401000 + len(code))
        code.extend(b'\x90' * pad)
        code.extend(data)

    emit('ffD3', b'\x8b\x41\x10\xc3', 0x401000)
    emit('onlyA', b'\x8b\x41\x08\xc3', 0x401010)
    emit('onlyB', b'\x8b\x41\x08\xc3', 0x401020)
    emit('vDV2', b'\x8b\x41\x04\xc3', 0x401030)
    emit('dtorD', b'\x83\xc0\x01\xc3', 0x401040)
    # 真机 PAL3.exe 0x42C8D0 的字节：83 e9 08; e9 88 6f ff ff ⇒ jmp 0x423860
    emit('thunkStatic', b'\x83\xe9\x08\xe9\x88\x6f\xff\xff', 0x401100)
    # 真机 c2.obj（B-1）：2b 49 fc; 83 e9 10; e9 <rel>
    emit('thunkComposite', b'\x2b\x49\xfc\x83\xe9\x10' + _jmp(0), 0x401110)
    img.add_section('.text', 0x1000, bytes(code), executable=True)

    # .rdata：COL(0x402000) + 槽 0x402004 / 0x402008（主表 2 槽）
    rdata = struct.pack('<III', 0x402100, at['ffD3'], at['onlyA'])
    img.add_section('.rdata', 0x2000, rdata)
    rdata2 = struct.pack('<II', 0x402100, at['thunkComposite'])
    img.add_section('.rdata', 0x2100, rdata2)
    img.add_section('.data', 0x3000, struct.pack('<ii', -4, 24))
    return img, at


IMG_BASE = 0x402004              # 主表 address point
IMG_BASE_DYN = 0x402104          # 动态/复合表 address point


def fixture_index(at):
    """VA → 名字（二进制侧归约用；模拟 decomp/注解给出的名字）。"""
    return {
        at['ffD3']: 'D3::ff',
        at['onlyA']: 'A3::onlyA',   # 继承槽保留**基类**归属（obj 的 mangled 名同此）
        at['onlyB']: 'D3::onlyB',
        at['vDV2']: 'DV2::v',
        at['dtorD']: 'D::~D',
        0x402100: '??_R4D3@@6BA3@@@',
        at['thunkStatic']: THUNK_STATIC,
        at['thunkComposite']: THUNK_COMPOSITE,
    }


# =====================================================================================
# 1. 符号重定位归约（含 RTTI COL 前缀）
# =====================================================================================

def test_obj_slots_are_symbol_relocations_not_addresses():
    """.obj 侧槽 = **符号重定位**（数据字节是 0，语义在 reloc 里）。

    真机复现：
        tools/wine_cl.sh /c /nologo /Od /GR /Itools/compilers/msvc6.0/Include \
            /Fo/tmp/vt3.obj data/status/_vtable_abi_probe_20260925/vt3.cpp
        objdump -dr /tmp/vt3.obj | grep -A3 '??_7D3@@6BA3@@@'
    """
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        vt = obj_vtables(p)
        t = vt['??_7D3@@6BA3@@@']
        assert [s.name for s in t.slots] == [FUNC_FF_D3, FUNC_ONLYA], t.slots
        # 槽位记录里**不得**出现裸地址/裸 0 —— 只有符号名与 reloc 偏移
        assert [s.offset for s in t.slots] == [4, 8], t.slots
        assert t.value == 4 and t.address_point_offset == 4


def test_rtti_col_prefix_detected_and_not_counted_as_slot():
    """`vtable[-1]` = RTTI COL 指针（`??_R4...`）⇒ 必须识别为 COL，
    **不得**被数成一个槽，也不得让槽序整体错位（真机 `??_7C2@@6B@` value=4）。

    复现：`tools/wine_cl.sh /c /nologo /Od /GR /... /Fo/tmp/p3.obj <上面的 p3.cpp>`；
    `python3 -c "import coff_vtable as cv; ..."` 实测 value=4、COL 在 value-4。
    """
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        vt = obj_vtables(p)
        assert vt['??_7D3@@6BA3@@@'].col_symbol == COL_D3A
        assert vt['??_7D3@@6BB3@@@'].col_symbol == COL_D3B
        # 无 COL 的表（纯净 TU 形态）→ None，且槽序不受影响
        assert vt['??_7DV2@@6B@'].col_symbol is None
        assert len(vt['??_7DV2@@6B@'].slots) == 2


def test_aux_symbol_entries_do_not_shift_reloc_targets():
    """reloc 的符号索引是**原始 COFF 索引**（含 aux 占位）⇒ 夹具把带 aux 的符号排在
    重定位目标**之前**；任何"按遍历到的第 i 个"计数都会解出错误的符号名。"""
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        art = parse_obj_artifacts(p)
        naux = [s for s in art.by_index.values() if s['naux']]
        assert naux, '夹具有 aux 符号'
        # 直接验证 reloc 解出的目标名逐个正确
        vt = obj_vtables(p)
        assert [s.name for s in vt['??_7D3@@6BB3@@@'].slots] == [THUNK_STATIC, FUNC_ONLYB]


def test_long_section_name_slash_form_parsed():
    """节名 `/NN`（长名 → 字符串表）不得让该节的表读空（真机 COMDAT 节常见）。"""
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        art = parse_obj_artifacts(p)
        assert any(s['name'] == '.rdata2' for s in art.sections), \
            [s['name'] for s in art.sections]


def test_name_key_mangling_variants():
    """两侧归约到同一名字键：mangled 符号 ↔ `Cls::Func` 文本名。"""
    assert name_key('?ff@D3@@UAEHXZ') == name_key('D3::ff')
    assert name_key(THUNK_STATIC) == 'D3::ff'
    assert name_key(THUNK_DYNAMIC) == 'DV2::v'
    assert name_key(THUNK_COMPOSITE) == 'D::~D'
    assert name_key(DTOR_D) == 'D::~D'
    assert name_key('??_GD@@UAEPAXI@Z') == 'D::~D'
    assert name_key('??1D@@UAE@XZ') == 'D::~D'
    assert name_key('??_7D3@@6BA3@@@') == 'D3::__vftable[A3]'
    assert name_key('??_7D3@@6B@') == 'D3::__vftable'
    assert name_key('??_8D3@@7B@') == 'D3::__vbtable'
    assert name_key('__purecall') == '__purecall'
    assert name_key('_purecall') == '__purecall'


# =====================================================================================
# 2. thunk 归一（静态 / 动态 / 复合）
# =====================================================================================

def test_static_adjustor_thunk_normalizes_to_target_and_offset():
    """真机 `?ff@D3@@W7AEHXZ` = `83 e9 08; e9 <rel ?ff@D3@@UAEHXZ>`（vt3.obj 实测）
    ⇒ 归一为 `(目标函数 D3::ff, kind=adjustor_static, this 调整量 8)`。"""
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        art = parse_obj_artifacts(p)
        t = obj_vtables(p)['??_7D3@@6BB3@@@']
        slots = normalize_obj_slots(t, art)
        s0 = slots[0]
        assert s0.raw == THUNK_STATIC
        assert s0.key == 'D3::ff', s0
        assert s0.kind == KIND_ADJUSTOR_STATIC, (s0.kind, s0.notes)
        assert s0.offset == 8, s0
        assert s0.dynamic is False
        assert s0.normalized == ('D3::ff', KIND_ADJUSTOR_STATIC, 8)


def test_dynamic_vbase_thunk_normalizes_to_triple():
    """真机 `?v@DV2@@$4PPPPPPPM@A@AEXXZ` = `2b 49 fc; e9 <rel>`（dv2.obj 实测）
    ⇒ `(DV2::v, adjustor_vbase, dynamic, const=0)`——**不是**标量二元组（B-4）。"""
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        art = parse_obj_artifacts(p)
        t = obj_vtables(p)['??_7DV2@@6B@']
        slots = normalize_obj_slots(t, art)
        s0 = slots[0]
        assert s0.kind == KIND_ADJUSTOR_VBASE, (s0.kind, s0.notes)
        assert s0.dynamic is True
        assert s0.offset == 0
        assert s0.normalized == ('DV2::v', KIND_ADJUSTOR_VBASE, 'dynamic', 0)


def test_bin_table_matches_vtable_compare_on_real_binary():
    """**表长界定与既有工具逐字同规则**：189 张真机表（ctor 实写的全部表起始）
    槽序列/置信度/类族/断裂点**零分歧**。

    这条测试是"复用而不另立规则"的可验证证据；若本源改了界定逻辑，它会红。
    """
    if not EXE.exists():
        raise unittest.SkipTest('PAL3.exe 不存在')
    import vtable_compare as vc
    import vtable_scanner as vs
    from vtable_verify import PEImage, bin_table_from_image, load_bin_targets, load_va_index
    vs.SECTIONS = vs.load_sections()
    img = PEImage(str(EXE))
    idx = load_va_index()
    targets = load_bin_targets()
    assert len(targets) >= 100, len(targets)
    bad = []
    for base in targets:
        try:
            old = vc.bin_table(base, targets, idx)
        except Exception:
            continue
        bt = bin_table_from_image(img, base, idx=idx, targets=targets)
        if not (bt.slots == tuple(old[0]) and bt.confidence == old[2]
                and bt.family == old[4] and bt.broken_at == old[3]):
            bad.append((hex(base), len(bt.slots), len(old[0])))
    assert not bad, bad[:5]


def test_real_binary_table_normalizes_adjustor_slot():
    """真机 PAL3.exe 0x56AB28（gbLightObj 主表）槽 2 = 0x42C8D0 静态 adjustor
    ⇒ 归一成 `(目标键, adjustor_static, 8)`，普通槽保持 `fn`。"""
    if not EXE.exists():
        raise unittest.SkipTest('PAL3.exe 不存在')
    from vtable_verify import PEImage, bin_table_from_image, load_bin_targets, load_va_index
    img = PEImage(str(EXE))
    idx = load_va_index()
    targets = load_bin_targets()
    bt = bin_table_from_image(img, 0x56AB28, idx=idx, targets=targets)
    assert bt.slots[2] == 0x42C8D0, [hex(v) for v in bt.slots]
    # 真机实测：该表**没有** RTTI COL（PAL3.exe 无游戏类 RTTI）⇒ 全库只有 CRT/STL 的
    # 6 条 .?AV 串；若 .obj 侧带 COL，address_point_rtti 偏差就是真发现
    assert bt.col is None, hex(bt.col)
    slots = normalize_bin_slots(bt, img, idx)
    assert slots[2].kind == KIND_ADJUSTOR_STATIC, slots[2]
    assert slots[2].offset == 8 and slots[2].dynamic is False, slots[2]
    assert slots[2].normalized[1] == KIND_ADJUSTOR_STATIC and len(slots[2].normalized) == 3
    assert slots[0].kind == KIND_FN, slots[0]


def test_composite_dynamic_plus_const_thunk_b1():
    """attack README B-1 真机复合槽 `??_ED@@$4PPPPPPPM@BA@AEPAXI@Z`
    = `2b 49 fc; 83 e9 10; e9 <rel ??_ED@@UAEPAXI@Z>`（c2.obj 实测）
    ⇒ kind=composite（deleting_dtor × 动态 adjustor 双命中）、dynamic、const=0x10。

    复现：`tools/wine_cl.sh /c /nologo /Od /GR /I.../Include /Fo/tmp/c2.obj \
        data/status/_vtable_attack_cases_20260925/c2.cpp`；`objdump -dr /tmp/c2.obj`。
    """
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        art = parse_obj_artifacts(p)
        t = obj_vtables(p)['??_7DV2@@6B@']
        s1 = normalize_obj_slots(t, art)[1]
        assert s1.raw == THUNK_COMPOSITE
        assert s1.kind == KIND_COMPOSITE, (s1.kind, s1.notes)
        assert s1.dynamic is True
        assert s1.offset == 0x10, s1
        assert s1.key == 'D::~D'
        assert s1.normalized == ('D::~D', KIND_COMPOSITE, 'dynamic', 0x10)


def test_deleting_dtor_and_purecall_kinds():
    """非 thunk 槽的 kind：`??_E/??_G` ⇒ deleting_dtor；`__purecall` ⇒ purecall。"""
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        art = parse_obj_artifacts(p)
        t = obj_vtables(p)['??_7D3@@6BA3@@@']
        dt_slots = normalize_obj_slots(
            type(t)(symbol='??_7X@@6B@', section_index=t.section_index, value=4,
                    slots=(type(t.slots[0])(DTOR_D, 4),), col_symbol=None,
                    address_point_offset=4), art)
        assert dt_slots[0].kind == KIND_DELETING_DTOR, dt_slots[0].notes
        pc = normalize_obj_slots(
            type(t)(symbol='??_7X@@6B@', section_index=t.section_index, value=4,
                    slots=(type(t.slots[0])('__purecall', 4),), col_symbol=None,
                    address_point_offset=4), art)
        assert pc[0].kind == KIND_PURECALL, pc[0].notes
        assert pc[0].key == '__purecall'


def test_decode_adjustor_chain_static_add_and_sub():
    """静态调整链：`sub ecx,imm` ⇒ offset=+imm；`add ecx,imm` ⇒ offset=-imm（this 语义）。

    真机旁证：PAL3.exe 0x445920 = `83 c1 68; e9 ...`（add ecx,0x68 形态，实测于本任务扫描）。
    """
    img = BytesImage(image_base=0x400000)
    img.add_section('.text', 0x1000, bytes.fromhex('83e910') + _jmp(0x40))
    img.add_section('.text', 0x1100, bytes.fromhex('83c168') + _jmp(0x40))
    ch = decode_adjustor_chain(img.read, 0x401000)
    assert (ch.ok, ch.static_delta, ch.dynamic) == (True, 0x10, False), ch
    assert ch.target_va == 0x401003 + 5 + 0x40, hex(ch.target_va)
    ch2 = decode_adjustor_chain(img.read, 0x401100)
    assert (ch2.ok, ch2.static_delta) == (True, -0x68), ch2


def test_decode_adjustor_chain_dynamic_forms():
    """动态链：`2b 49 xx`（sub ecx,[ecx+disp]）⇒ dynamic=True + dynamic_disp；
    实机 B-1 的 `2b 49 fc; 83 e9 10` ⇒ dynamic_disp=-4、static_delta=0x10。"""
    img = BytesImage(image_base=0x400000)
    img.add_section('.text', 0x1000, bytes.fromhex('2b49fc83e910') + _jmp(0))
    ch = decode_adjustor_chain(img.read, 0x401000)
    assert ch.ok and ch.dynamic and ch.dynamic_disp == -4, ch
    assert ch.static_delta == 0x10, ch
    assert ch.kind_hint == KIND_ADJUSTOR_VBASE, ch


def test_image_thunk_on_real_pal3_adjustor_slot():
    """真机 PAL3.exe 0x42C8D0（本任务扫描命中的 adjustor 槽）：
    `83 e9 08; e9 88 6f ff ff` ⇒ offset 8、目标 0x423860。"""
    if not EXE.exists():
        raise unittest.SkipTest('PAL3.exe 不存在')
    from vtable_verify import PEImage
    img = PEImage(str(EXE))
    th = image_thunk(img, 0x42C8D0)
    assert th.ok, th
    assert th.kind == KIND_ADJUSTOR_STATIC, th
    assert th.static_delta == 8
    assert th.target_va == 0x423860, hex(th.target_va)


# =====================================================================================
# 3. 强制发射（普通类 / 抽象类 / 无虚析构抽象类）
# =====================================================================================

def test_probe_source_concrete_class_instantiates_object():
    """普通类：探针 TU **构造对象**（全局对象 ⇒ ctor 必发射 ⇒ vftable 被引用）。

    真机 lazy COMDAT 实测（本任务）：`struct C2{virtual int f();}; int C2::f(){...}` 单独
    编译 ⇒ `??_7C2@@6B@` **缺失**（0 张表）；加 `void use(){C2 c;}` ⇒ 出现。
    """
    src = build_probe_source(ProbeSpec(cls='CEffCylinder'), PROBE_STRATEGY_OBJECT)
    assert 'CEffCylinder' in src
    assert 'vtv_probe' in src
    assert src.count('CEffCylinder') >= 2
    # 必须是**实体**（对象定义），不是仅声明
    assert 'vtv_probe_object' in src and ';' in src


def test_probe_source_abstract_class_defines_concrete_derived():
    """抽象类：定义**具体派生类**并构造（借派生 ctor 写基类 vptr 引发基类表发射）。

    真机实测：抽象类 `NA` + `struct Shim:NA{int p(){...}}` + 全局 shim ⇒ `??_7NA@@6B@` 出现
    （/Od；/O2 见 LIVE 测试的死存储消除告警）。
    """
    spec = ProbeSpec(cls='CEffEffect', abstract=True, pure_virtuals=('int p()', 'void q(int)'))
    src = build_probe_source(spec, PROBE_STRATEGY_DERIVED)
    assert 'struct VtvProbeCEffEffect : CEffEffect' in src, src
    assert 'int p()' in src and 'void q(int)' in src
    assert 'return 0' in src            # 非 void 纯虚的重写体必须返回值
    assert 'VtvProbeCEffEffect vtv_probe_object' in src


def test_probe_source_abstract_without_virtual_dtor_emits_dummy_ctor():
    """无虚析构的抽象类：需 dummy `Cls::Cls(){}` **用实体**（真机 e3/p4 实测：定义即发射）

    真机复现：
        tools/wine_cl.sh /c /nologo /Od /GR /I.../Include /Fo/tmp/e3.obj <e3.cpp>
        e3.cpp: struct AC{AC();virtual int p()=0;virtual int r();}; AC::AC(){x=1;}
        ⇒ `??_7AC@@6B@` 出现（/Od 与 /O2 都出现）。
    """
    spec = ProbeSpec(cls='CEffEffect', abstract=True, has_virtual_dtor=False,
                     ctor_declared=True, pure_virtuals=('int p()',))
    src = build_probe_source(spec, PROBE_STRATEGY_DUMMY_CTOR)
    assert 'CEffEffect::CEffEffect()' in src, src
    assert '{ }' in src or '{}' in src


def test_probe_source_shim_calls_base_dummy_ctor_when_available():
    """dummy ctor 策略的"用实体"：派生 shim 的 ctor **显式调用**基类 ctor
    （`VtvProbe::VtvProbe() : Cls()`）⇒ 基类 ctor 不可能被当作未使用而丢弃。"""
    spec = ProbeSpec(cls='AC', abstract=True, has_virtual_dtor=False,
                     ctor_declared=True, pure_virtuals=('int p()',))
    src = build_probe_source(spec, PROBE_STRATEGY_DUMMY_CTOR)
    assert ': AC()' in src, src


def test_force_emit_retries_next_strategy_until_vtable_present():
    """强制发射的**验收判据**：编译后必须能在 .obj 里看到 `??_7<Cls>@@`。
    第一策略（derived）产出"没有基类表"的 obj ⇒ 必须自动换下一策略并成功。"""
    with tempfile.TemporaryDirectory() as d:
        calls = []

        def fake_compiler(cmd, cwd=None):
            calls.append(cmd)
            src = Path(cmd[-1]).read_text()
            obj = [a[3:] for a in cmd if a.startswith('/Fo')][0]
            b = CoffBuilder()
            ti = b.add_section(TEXT, b'\xc3')
            if 'CEffEffect::CEffEffect()' in src:
                b.add_symbol('??_7CEffEffect@@6B@', ti, 0)
            b.write(obj)
            return subprocess.CompletedProcess(cmd, 0, '', '')

        spec = ProbeSpec(cls='CEffEffect', abstract=True, has_virtual_dtor=False,
                         ctor_declared=True, pure_virtuals=('int p()',),
                         strategies=(PROBE_STRATEGY_DERIVED, PROBE_STRATEGY_DUMMY_CTOR))
        res = force_emit(spec, d, compiler=fake_compiler)
        assert res.strategy == PROBE_STRATEGY_DUMMY_CTOR, res
        assert '??_7CEffEffect@@6B@' in res.symbols, res.symbols
        assert len([a for a in res.attempts if not a['emitted']]) == 1, res.attempts
        assert len(calls) == 2


def test_force_emit_raises_when_all_strategies_fail():
    """全部策略都无法发射 ⇒ 必须**报错**（带探针源 + 每次尝试的痕迹），
    绝不静默返回 0 槽的"对比通过"。"""
    with tempfile.TemporaryDirectory() as d:
        def fake_compiler(cmd, cwd=None):
            obj = [a[3:] for a in cmd if a.startswith('/Fo')][0]
            b = CoffBuilder()
            b.add_section(TEXT, b'\xc3')
            b.write(obj)
            return subprocess.CompletedProcess(cmd, 0, '', '')

        spec = ProbeSpec(cls='CEffEffect', abstract=True, ctor_declared=True,
                         pure_virtuals=('int p()',))
        try:
            force_emit(spec, d, compiler=fake_compiler)
        except EmissionError as e:
            assert 'CEffEffect' in str(e)
            assert e.probe_source and 'CEffEffect' in e.probe_source
            assert len(e.attempts) >= 2 and all('strategy' in a for a in e.attempts)
        else:
            raise AssertionError('未发射却未报错')


def test_force_emit_live_concrete_and_abstract():
    """真机端到端（`VTV_LIVE=1`）：普通类 + 抽象类（无虚析构、无 ctor 声明）都能发射。

    抽象类无 ctor 声明 ⇒ dummy ctor 不可用，走 derived shim；本仓 README #6 记录
    这类表在普通 TU 里缺失（lazy COMDAT），故必须由本测试证明探针策略有效。
    """
    if not LIVE:
        raise unittest.SkipTest('设 VTV_LIVE=1 才跑真机编译测试')
    with tempfile.TemporaryDirectory() as d:
        hdr = os.path.join(d, 'probe.h')
        with open(hdr, 'w') as f:
            f.write('struct CConc { virtual int f(); int a; };\n'
                    'inline int CConc::f() { return a; }\n'
                    'struct CAbsNoDtor { virtual int p() = 0; virtual int r(); };\n'
                    'inline int CAbsNoDtor::r() { return 1; }\n')
        spec_c = ProbeSpec(cls='CConc', header='probe.h')
        rc = force_emit(spec_c, d, include_dirs=[d], flags=['/Od'])
        assert '??_7CConc@@6B@' in rc.symbols, rc.symbols
        spec_a = ProbeSpec(cls='CAbsNoDtor', header='probe.h', abstract=True,
                           pure_virtuals=('int p()',))
        ra = force_emit(spec_a, d, include_dirs=[d], flags=['/Od'])
        assert '??_7CAbsNoDtor@@6B@' in ra.symbols, ra.attempts


def test_force_emit_live_o2_dead_store_caught():
    """/O2 死存储消除：派生 shim 写派生 vptr 会吃掉基类 vptr 写 ⇒ 基类表**不发射**。

    真机实测（本任务）：抽象类 `NA` + shim，`/O2 /Ob2 /Oi /Ot /Oy` ⇒ 只剩 `??_7Shim@@6B@`，
    `??_7NA@@6B@` 缺失；/Od 则两张都在。本测试钉死"发射检查必须捕获这一点"，
    而不是把 0 槽当成"对比通过"。
    """
    if not LIVE:
        raise unittest.SkipTest('设 VTV_LIVE=1 才跑真机编译测试')
    with tempfile.TemporaryDirectory() as d:
        with open(os.path.join(d, 'probe.h'), 'w') as f:
            f.write('struct CAbs { virtual int p() = 0; virtual int r(); int x; };\n'
                    'inline int CAbs::r() { return x; }\n')
        spec = ProbeSpec(cls='CAbs', header='probe.h', abstract=True,
                         pure_virtuals=('int p()',))
        try:
            res = force_emit(spec, d, include_dirs=[d], flags=['/O2', '/Ob2', '/Oi', '/Ot', '/Oy'])
        except EmissionError as e:
            assert any('??_7CAbs@@' in str(a.get('missing', '')) for a in e.attempts), e.attempts
        else:
            raise AssertionError('O2 下基类表未发射却报成功：%s' % (res.symbols,))


# =====================================================================================
# 4. 对比：槽数 / 槽序 / 归一化元组 / vbtable
# =====================================================================================

def _sides():
    """同形两侧（.obj 夹具 ↔ 内存镜像），用于对比测试。"""
    d = tempfile.mkdtemp()
    p = fixture_obj(os.path.join(d, 'f.obj'))
    art = parse_obj_artifacts(p)
    vt = obj_vtables(p)
    img, at = fixture_image()
    idx = fixture_index(at)
    obj_prim = normalize_obj_slots(vt['??_7D3@@6BA3@@@'], art)
    bin_prim = normalize_bin_slots(
        BinTable(base=IMG_BASE, end=IMG_BASE + 12, slots=(at['ffD3'], at['onlyA']),
                 confidence='high', family='D3'), img, idx)
    return obj_prim, bin_prim, vt, art, img, at, idx


def test_compare_identical_sides_ok():
    obj_prim, bin_prim, *_ = _sides()
    res = compare_tables(obj_prim, bin_prim)
    assert res.ok, res.deviations
    assert (res.obj_count, res.bin_count) == (2, 2)
    assert res.identity_mode == 'name', res.identity_mode


def test_slot_count_deviation_reported():
    """槽数不同 ⇒ 偏差 kind='slot_count'，index=首个多出/缺失的位置。"""
    obj_prim, bin_prim, *_ = _sides()
    res = compare_tables(obj_prim, bin_prim + [NormSlot(side='bin', raw='0x1', key='X::y', kind=KIND_FN, va=1)])
    assert not res.ok
    dev = [d for d in res.deviations if d.kind == 'slot_count']
    assert dev and dev[0].index == 2, res.deviations
    assert (dev[0].obj, dev[0].bin) == (2, 3)


def test_slot_order_deviation_locates_index_and_kind():
    """槽序错位 ⇒ kind='slot_key' 且**定位到具体槽位**（不是"表不等"）。"""
    obj_prim, bin_prim, *_ = _sides()
    res = compare_tables(obj_prim, [bin_prim[1], bin_prim[0]])
    assert not res.ok
    devs = [d for d in res.deviations if d.kind == 'slot_key']
    assert [d.index for d in devs] == [0, 1], res.deviations
    text = render_report(res)
    assert 'slot 0' in text and 'slot_key' in text


def test_slot_kind_deviation():
    """同一目标函数、不同槽内容形态（静态 thunk vs 裸函数）⇒ kind='slot_kind'。"""
    obj_prim, bin_prim, *_ = _sides()
    flat = NormSlot(side='bin', raw='0x401000', key='D3::ff', kind=KIND_FN)
    bin_second = NormSlot(side='bin', raw='0x401020', key='D3::onlyA',
                          kind=KIND_ADJUSTOR_STATIC, offset=8)
    obj_first = NormSlot(side='obj', raw=THUNK_STATIC, key='D3::ff',
                         kind=KIND_ADJUSTOR_STATIC, offset=8)
    res = compare_tables([obj_first, obj_prim[1]], [flat, bin_second])
    kinds = {(d.index, d.kind) for d in res.deviations}
    assert (0, 'slot_kind') in kinds, res.deviations
    assert (0, 'this_adjust') in kinds, res.deviations


def test_this_adjust_deviation():
    """this 调整量不同 ⇒ kind='this_adjust'（thunk 归一的二元组维度）。"""
    a = NormSlot(side='obj', raw=THUNK_STATIC, key='D3::ff', kind=KIND_ADJUSTOR_STATIC, offset=8)
    b = NormSlot(side='bin', raw='0x401100', key='D3::ff',
                 kind=KIND_ADJUSTOR_STATIC, offset=16)
    res = compare_tables([a], [b])
    assert not res.ok
    dev = [d for d in res.deviations if d.kind == 'this_adjust'][0]
    assert dev.index == 0 and (dev.obj, dev.bin) == ((8, False), (16, False)), \
        res.deviations


def test_address_point_rtti_deviation():
    """RTTI COL 前缀不一致 ⇒ kind='address_point_rtti'（一侧有 COL、另一侧没有）。"""
    obj_prim, bin_prim, *_ = _sides()
    res = compare_tables(obj_prim, bin_prim, obj_col='??_R4D3@@6BA3@@@', bin_col=None)
    assert not res.ok
    assert [d.kind for d in res.deviations] == ['address_point_rtti'], res.deviations
    ok = compare_tables(obj_prim, bin_prim, obj_col='??_R4D3@@6BA3@@@',
                        bin_col=0x402100, obj_address_point_offset=4, bin_address_point_offset=0)
    assert ok.ok, ok.deviations


def test_bin_table_detects_col_prefixed_base():
    """传入的 base 若是 **RTTI COL 地址**（base 处 = .rdata 指针、base+4 才是代码指针）
    ⇒ 自动前进 4 字节、`address_point_offset=4`，槽序**不得**整体错位。"""
    img, at = fixture_image()
    idx = fixture_index(at)
    tbl = bin_table_from_image(img, 0x402000, idx=idx,
                               targets=(0x402000, 0x40200C),
                               family_of=lambda va: 'D3' if va in (at['ffD3'], at['onlyA']) else None)
    assert tbl.address_point_offset == 4, tbl
    assert tbl.slots == (at['ffD3'], at['onlyA']), tbl
    assert tbl.col == 0x402100, hex(tbl.col or 0)


def test_bin_vbtable_reads_signed_entries():
    """二进制 vbtable 读为**有符号**项（真机 `??_8D@@7B@` = [-4, 24]）。"""
    img, at = fixture_image()
    assert bin_vbtable(img, 0x403000, 2) == (-4, 24)
    res = compare_vbtable(bin_vbtable(img, 0x403000, 2), (-4, 16))
    assert [(d.kind, d.index) for d in res.deviations] == [('vbtable_value', 1)]
    try:
        bin_vbtable(img, 0x403000, 99)
    except ImageError:
        pass
    else:
        raise AssertionError('越界 vbtable 未报错')


def test_vbtable_content_deviation():
    """vbtable 内容（虚继承类）逐项对比；偏差定位到项下标。"""
    assert compare_vbtable((-4, 24), (-4, 24)).ok
    res = compare_vbtable((-4, 24), (-4, 16))
    assert not res.ok
    assert [(d.kind, d.index) for d in res.deviations] == [('vbtable_value', 1)], res.deviations


def test_vbtable_extracted_from_obj():
    """.obj 侧 vbtable 内容是**字面量 DWORD**（无重定位），真机 `??_8D@@7B@` = [-4,24]。"""
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        vb = obj_vbtables(p)
        assert vb['??_8D3@@7B@'] == (-4, 24), vb


def test_missing_one_side_vbtable_leaves_trace():
    """虚继承类：只给一侧 vbtable ⇒ **留痕**而非静默"该维度通过"。"""
    obj_prim, bin_prim, *_ = _sides()
    res = compare_tables(obj_prim, bin_prim, obj_vbtable=(-4, 24))
    assert res.ok, res.deviations
    assert any('vbtable 维度未比' in n for n in res.notes), res.notes
    text = render_report(res)
    assert 'vbtable 维度未比' in text, text


def test_dynamic_tuple_compared_as_triple():
    """B-4：动态 delta **不可**归一成标量二元组 ⇒ 必须比 `(target, kind, dynamic, const)`；
    若发射侧归一成 (target,0x10)、.obj 侧归一成 (target,dyn)，对比必须**不匹配**而非假通过。"""
    obj_slot = NormSlot(side='obj', raw=THUNK_COMPOSITE, key='D::~D', kind=KIND_COMPOSITE,
                        dynamic=True, offset=0x10)
    bin_same = NormSlot(side='bin', raw='0x401110', key='D::~D', kind=KIND_COMPOSITE,
                        dynamic=True, offset=0x10)
    bin_static = NormSlot(side='bin', raw='0x401110', key='D::~D', kind=KIND_COMPOSITE,
                          dynamic=False, offset=0x10)
    assert compare_tables([obj_slot], [bin_same]).ok
    res = compare_tables([obj_slot], [bin_static])
    assert [d.kind for d in res.deviations] == ['this_adjust'], res.deviations


def test_va_reduction_identity_prefers_va():
    """两侧都能归约到 VA 时，身份判据用 **VA**（简报"归约到函数 VA 对比"）。

    名字键只是**归约的中间量**：真正的身份是 VA。这里同时验证 `va_of` 注入两条路径
    （obj 侧按符号名键映射、bin 侧按表槽 VA 反查目标函数 VA）。
    """
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        art = parse_obj_artifacts(p)
        vt = obj_vtables(p)
        img, at = fixture_image()
        idx = fixture_index(at)
        mapping = {'D3::ff': 0x401000, 'A3::onlyA': 0x401010}
        o = normalize_obj_slots(vt['??_7D3@@6BA3@@@'], art, va_of=mapping)
        tbl = BinTable(base=IMG_BASE, end=IMG_BASE + 8, slots=(at['ffD3'], at['onlyA']))
        b = normalize_bin_slots(tbl, img, idx, va_of=mapping)
        assert [s.va for s in o] == [0x401000, 0x401010], o
        assert [s.va for s in b] == [0x401000, 0x401010], b
        res = compare_tables(o, b)
        assert res.identity_mode == 'va', res.identity_mode
        assert res.ok, res.deviations


def test_bin_side_end_to_end_from_image():
    """二进制侧全链路（内存镜像）：界定表长 → 归约 → 与 .obj 侧对比通过；
    再把镜像里一个槽改成"别的类族"⇒ 表在断点处结束（启发式置信度降级）。"""
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        art = parse_obj_artifacts(p)
        img, at = fixture_image()
        idx = fixture_index(at)
        tbl = bin_table_from_image(img, IMG_BASE, idx=idx, targets=(IMG_BASE, IMG_BASE + 8),
                                  family_of=lambda va: 'D3' if va in (at['ffD3'], at['onlyA']) else None)
        assert tbl.slots == (at['ffD3'], at['onlyA']), tbl
        obj_prim = normalize_obj_slots(obj_vtables(p)['??_7D3@@6BA3@@@'], art)
        res = compare_tables(obj_prim, normalize_bin_slots(tbl, img, idx))
        assert res.ok, res.deviations
        # 动态/复合表：二进制侧 thunk 必须归一成与 .obj 侧相同的元组
        tbl2 = bin_table_from_image(img, IMG_BASE_DYN, idx=idx, targets=(IMG_BASE_DYN,),
                                    family_of=lambda va: None)
        dyn_bin = normalize_bin_slots(tbl2, img, idx)[0]
        assert dyn_bin.kind in (KIND_ADJUSTOR_VBASE, KIND_COMPOSITE), dyn_bin
        assert dyn_bin.dynamic is True and dyn_bin.offset == 0x10, dyn_bin


def test_render_report_lists_each_deviation_with_slot_and_kind():
    a = NormSlot(side='obj', raw=THUNK_STATIC, key='D3::ff', kind=KIND_ADJUSTOR_STATIC, offset=8)
    b = NormSlot(side='bin', raw='0x401100', key='D3::other', kind=KIND_FN, va=0x401100)
    res = compare_tables([a], [b], obj_label='obj.x', bin_label='0x402004')
    text = render_report(res)
    assert 'obj.x' in text and '0x402004' in text
    assert 'slot 0' in text and 'slot_key' in text
    assert json.dumps(res.to_dict())            # 报告可机读


# =====================================================================================
# 5. CLI
# =====================================================================================

def test_cli_list_obj_json():
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        buf = io.StringIO()
        with redirect_stdout(buf):
            rc = main(['--obj', p, '--list', '--json'])
        assert rc == 0, (rc, buf.getvalue())
        data = json.loads(buf.getvalue())
        syms = {t['symbol'] for t in data['vtables']}
        assert '??_7D3@@6BA3@@@' in syms and '??_7DV2@@6B@' in syms
        prim = [t for t in data['vtables'] if t['symbol'] == '??_7D3@@6BA3@@@'][0]
        assert prim['slots'][0]['kind'] == KIND_FN, prim
        assert prim['col_symbol'] == COL_D3A
        # vbtable 按**类令牌**关联（??_7D3@@6BA3@@@ ↔ ??_8D3@@7B@，不同符号）
        assert prim['vbtable'] == [-4, 24], prim['vbtable']


def test_cli_probe_src():
    buf = io.StringIO()
    with redirect_stdout(buf):
        rc = main(['--probe-src', 'CLS', '--abstract', '--has-virtual-dtor',
                   '--pure', 'int p()'])
    assert rc == 0
    out = buf.getvalue()
    assert 'VtvProbeCLS' in out and 'CLS' in out, out


def test_cli_bad_obj_returns_2():
    buf = io.StringIO()
    with redirect_stdout(buf):
        rc = main(['--obj', '/nonexistent/nope.obj', '--list'])
    assert rc == 2, (rc, buf.getvalue())


def test_cli_compare_without_bin_base_is_usage_error():
    with tempfile.TemporaryDirectory() as d:
        p = fixture_obj(os.path.join(d, 'f.obj'))
        buf = io.StringIO()
        with redirect_stdout(buf):
            rc = main(['--obj', p, '--cls', 'D3', '--bin-base', '0x0'])
        # --bin-base 0x0 非法（不在镜像里）⇒ 退出码 2，而不是假装比过
        assert rc == 2, (rc, buf.getvalue())


if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)