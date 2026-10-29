"""合成物不发射（spec #5：T6 adjustthunk 反模式清理）。

判据（dtor 报告 A-E 字节形 + 名形）：*_adjthunk（sub this+forward）· _scalar_dtor_* ·
~X_addr 后缀 · compiler_init_* ⇒ 编译器再生件禁手写（源写 ~X()+delete 即再生）。
运行: python3 tests/test_synthesized_no_emit.py
"""
import glob
import json
import re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
PAT = re.compile(r'(_adjthunk\b|_scalar_dtor_|^~\w+_[0-9a-fA-F]{4,}$|^compiler_init_)')


def test_classifier():
    try:
        from pipeline.gen.tables import is_synthesized_member as f
    except ImportError:
        from tables import is_synthesized_member as f
    assert f('Object_adjthunk_1be20') is True
    assert f('_scalar_dtor_BE80') is True
    assert f('~UIWnd_ef50') is True
    assert f('Destroy__ovl_03') is False          # 对抗样本：真虚方法禁滤
    assert f('RandLerpF') is False


def test_no_adjthunk_annotation_entries():
    """合成物注册=declaration_only（vtable 槽符号提供者保留，体意图剥离——
    T4 矫正：删注册致 78 槽失名，钩子 vtable 闸实证）。"""
    bad = []
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        for k, v in (d.get('methods') or {}).items():
            if '_adjthunk' in (k + (v.get('name') or '')) and not v.get('declaration_only'):
                bad.append((f, k))
    assert not bad, bad                          # 合成物注册须标 declaration_only


def test_no_adjthunk_definitions_generated():
    hits = [f for f in glob.glob(str(ROOT / 'pal3/src/**/*.cpp'), recursive=True)
            if re.search(r'^\s*\w[\w:~ ]*_adjthunk\s*\(', open(f).read(), re.M)]
    assert not hits, hits                        # 生成源零手写定义体


# ---- T4 批1（修法 D·地址级闸）复核 46cdde8a 实施清单 ----
REG16 = ('0x0047E570', '0x004C27C0', '0x004D5860', '0x004C1550', '0x004C1560',
         '0x004C88B0', '0x004C9530', '0x004CB340', '0x004CD9F0', '0x004D5850',
         '0x004506C0', '0x00451800', '0x00451C70', '0x0047DD70', '0x0044BE40',
         '0x0041BE20')
BODY_PAT = re.compile(r'^\s*[\w:~* ]*\b(sub_[0-9a-fA-F]{6,}|_todo_[0-9a-fA-F]+|_sdtor_\w+|_scalar_dtor_\w+|[\w]+_adjthunk\w*)\s*\([^;]*\)\s*(const\s*)?\{', re.M)


def test_synth_addr_registry():
    """16 地址入 skip_functions(compiler_regenerated)——地址级合成物闸。"""
    SK2 = json.load(open(ROOT / 'data/annotations/skip_functions.json'))
    for a in REG16:
        e = SK2.get(a)
        assert e and e.get('skip_reason') == 'compiler_regenerated', (a, e)


def test_no_synth_call_sites():
    """批1 承诺面：复核 46cdde8a 波及面 6 站点所在文件零 _scalar_dtor_/_sdtor_ 调用。
    全局零=批2 棘轮（PAL_GDB/GRPinput/Scene/CScreenMode 等存量 2026-10-29 记账）。"""
    pat = re.compile(r'(->|\.|::)\s*(_scalar_dtor_|_sdtor_)\w*\s*\(')
    promised = ('UITitle_YXXX.cpp', 'RenderTarget2.cpp', 'CEffSParticle.cpp', 'UIScene.cpp', 'PalScript.cpp')
    hits = [f for f in glob.glob(str(ROOT / 'pal3/src/**/*.cpp'), recursive=True)
            if pat.search(open(f).read()) and f.split('/')[-1] in promised]
    assert not hits, hits


def test_no_synth_definitions_generated():
    """批1 承诺面：REG16 合成物零定义体。全局零=批2 棘轮（32 文件手写删析构存量）。"""
    pat = re.compile(r'(_scalar_dtor_DD70|_scalar_dtor_adjthunk|Object_adjthunk_1be|sub_47E570)\s*\(')
    hits = [f for f in glob.glob(str(ROOT / 'pal3/src/**/*.cpp'), recursive=True)
            if pat.search(open(f).read())]
    assert not hits, [h.split('/')[-1] for h in hits][:5]
