#!/usr/bin/env python3
"""
Tests for PAL3 decomp codegen pipeline stages.
Run: python pipeline/gen/test_pipeline.py
"""
import sys
import os
import unittest

# Set up paths for pipeline imports
_gen_dir = os.path.dirname(os.path.abspath(__file__))
_project_dir = os.path.dirname(os.path.dirname(_gen_dir))
if _gen_dir not in sys.path:
    sys.path.insert(0, _gen_dir)
if _project_dir not in sys.path:
    sys.path.insert(0, _project_dir)

# Must set PROJECT_ROOT before importing pipeline modules
os.environ['PROJECT_ROOT'] = _project_dir

from ast_transform import transform_oop_calls
from stages.stage3_cleanup import run as stage3_run


def _make_ctx(cls_name=None, is_free_function=False):
    """Minimal context object for stage tests."""
    class Ctx:
        pass
    ctx = Ctx()
    ctx.cls_name = cls_name
    ctx.is_free_function = is_free_function
    return ctx


class TestOopTransform(unittest.TestCase):
    """Test ast_transform.transform_oop_calls"""

    def test_this_as_first_arg(self):
        """Class::Method(this, ...) -> this->Class::Method(...)
        Qualifier keeps the direct-call semantics for virtual methods."""
        code = "int Foo::Bar() { Foo::DoSomething(this, 1, 2); return 0; }"
        result = transform_oop_calls(code, cls_name='Foo')
        self.assertIn('this->Foo::DoSomething(1, 2)', result)
        self.assertNotIn('Foo::DoSomething(this', result)

    def test_identifier_as_first_arg(self):
        """Class::Method(var, ...) -> ((Class *)var)->Class::Method(...)
        Cast + qualifier both preserved: compiles for untyped locals and
        keeps the direct-call semantics Hex-Rays reported."""
        code = "int test() { Foo::DoSomething(ptr, 1, 2); return 0; }"
        result = transform_oop_calls(code)
        self.assertIn('((Foo *)ptr)->Foo::DoSomething(1, 2)', result)

    def test_complex_expr_as_first_arg(self):
        """Class::Method(ptr->field, ...) -> ((Class *)ptr->field)->Class::Method(...)"""
        code = "int test() { Foo::DoSomething(obj->field, 1); return 0; }"
        result = transform_oop_calls(code)
        self.assertIn('((Foo *)obj->field)->Foo::DoSomething(1)', result)

    def test_qualified_destructor(self):
        """Class::_Class(this) -> this->~Class()"""
        code = "int Foo::Cleanup() { Foo::_Foo(this); return 0; }"
        result = transform_oop_calls(code, cls_name='Foo')
        self.assertIn('this->~Foo()', result)

    def test_base_class_destructor(self):
        """Base::_Base(this) -> Base::_Base() preserved (no shadowing)"""
        code = "int Derived::Cleanup() { Base::_Base(this); return 0; }"
        result = transform_oop_calls(code, cls_name='Derived')
        # Base::_Base(this) → this->~Base()
        self.assertIn('this->~Base()', result)

    def test_static_method_not_transformed(self):
        """Static (__cdecl) methods should not be transformed"""
        code = "int test() { Foo::StaticMethod(ptr, 1, 2); return 0; }"
        result = transform_oop_calls(code, static_methods={'Foo::StaticMethod'})
        self.assertIn('Foo::StaticMethod(ptr, 1, 2)', result)
        self.assertNotIn('->StaticMethod', result)

    def test_private_call_not_transformed(self):
        """sub_* calls should remain unchanged"""
        code = "int Foo::Bar() { sub_4F3020(this, 3); return 0; }"
        result = transform_oop_calls(code, cls_name='Foo')
        self.assertIn('sub_4F3020(this, 3)', result)

    def test_direct_call_no_scope_unchanged(self):
        """Plain function() calls (no Class::) should remain unchanged"""
        code = "int Foo::Bar() { DoSomething(1, 2); return 0; }"
        result = transform_oop_calls(code, cls_name='Foo')
        self.assertIn('DoSomething(1, 2)', result)
        self.assertNotIn('this->', result)

    def test_inter_class_call_with_this(self):
        """OtherClass::Method(this, ...) in Derived::Bar = confirmed IDB
        attribution error: keep the static call form (C2352 at compile time)
        and mark it — never launder it into legal-looking syntax.

        t6 note: this scenario is the "no evidence" case on purpose. The
        Track-1 gate must NOT open here — `OtherClass` is not in the corpus,
        so neither the ret-N evidence nor the vtable-slot evidence exists and
        `_ret_param_slots` returns None. See TestTrack1EvidenceGate for the
        two positive controls."""
        code = "int Derived::Bar() { OtherClass::DoSomething(this, 1, 2); return 0; }"
        result = transform_oop_calls(code, cls_name='Derived')
        self.assertIn('/* [MISATTRIBUTED] OtherClass::DoSomething on Derived::this',
                      result)
        self.assertIn('OtherClass::DoSomething(this, 1, 2)', result)

    def test_inter_class_call_with_this_gate_blocked_by_arity(self):
        """t6: ret-N gate must stay CLOSED when the rendered arg count does
        not match the callee's real __thiscall stack-param count.

        `AStarPathFinder::GetHeuristicIdx` really takes 2 params (retn 8), so
        calling it with 3 arguments is inconsistent => the `(T*)this` reading
        is NOT self-consistent => keep the marker. This is the control that
        keeps the Track-1 gate to exactly 3 sites instead of 298."""
        code = ("int Foo::Bar() { "
                "AStarPathFinder::GetHeuristicIdx((AStarPathFinder *)this, 1, 2, 3); "
                "return 0; }")
        result = transform_oop_calls(code, cls_name='Foo')
        self.assertIn('/* [MISATTRIBUTED] AStarPathFinder on Foo::this',
                      result)
        self.assertIn('AStarPathFinder::GetHeuristicIdx((AStarPathFinder *)this, '
                      '1, 2, 3)', result)

    def test_rowtable_cast_this_form(self):
        """t6 (`:421` ROWTABLE emission): a family class called on our own
        `(T*)this` emits the faithful cast+qualified form plus the
        `/* [ROWTABLE] */` anchor. `SceneObj` is a real family member, so this
        also guards the `_rowtable_family()` contract (CG-023: the file must
        be readable — a missing list now raises instead of degrading)."""
        code = ("int Foo::Bar() { "
                "SceneObj::Update((SceneObj *)this, 7); return 0; }")
        result = transform_oop_calls(code, cls_name='Foo')
        self.assertIn('((SceneObj *)this))->SceneObj::Update(7)', result)
        self.assertIn('[ROWTABLE]', result)
        self.assertNotIn('[MISATTRIBUTED] SceneObj', result)

    def test_rowtable_not_applied_to_non_family(self):
        """t6 (`:421` counterpart): a class outside the family must NOT get
        the ROWTABLE form. `Actor` is not in the family list."""
        code = ("int Foo::Bar() { "
                "Actor::Update((Actor *)this, 7); return 0; }")
        result = transform_oop_calls(code, cls_name='Foo')
        self.assertNotIn('[ROWTABLE]', result)


class TestTrack1EvidenceGate(unittest.TestCase):
    """t6 Track 1: the `(ret-N) AND (callee occupies a vtable slot)` gate.

    The gate is deliberately narrow. These tests pin BOTH halves of the
    conjunction and the ctor/dtor exclusion, because either half alone is
    inadmissible (measured: ret-N alone rewrites 298 sites / 189 files on the
    corpus; the vtable fact alone opens 3)."""

    def test_both_halves_needed(self):
        """Same callee, same rendered shape: MISATTRIBUTED unless BOTH facts
        hold. `AStarPathFinder::GetHeuristicIdx` is the real 0x4014F0 stub —
        it occupies vtable slot 2 of 0x56A600 and its tail is `retn 8`."""
        # (a) vtable fact true, arity WRONG -> marker stays
        bad = ("int Foo::Bar() { "
               "AStarPathFinder::GetHeuristicIdx((AStarPathFinder *)this, 1, 2, 3); "
               "return 0; }")
        r = transform_oop_calls(bad, cls_name='Foo')
        self.assertIn('[MISATTRIBUTED]', r)
        # (b) both facts true -> clean cast+qualified form, marker gone
        good = ("int Foo::Bar() { "
                "AStarPathFinder::GetHeuristicIdx((AStarPathFinder *)this, 1, 2); "
                "return 0; }")
        r = transform_oop_calls(good, cls_name='Foo')
        self.assertNotIn('[MISATTRIBUTED]', r)
        self.assertIn('(((AStarPathFinder *)this))->AStarPathFinder::GetHeuristicIdx(1, 2)',
                      r)

    def test_three_track1_sites(self):
        """The three CCBAI sites must all open the gate, and only those: the
        callee is a vtable-slot holder, the arity is consistent, and the
        qualifier is preserved (t11 checks `Cls::` is kept)."""
        code = ("int Foo::Bar() { "
                "if ( AStarPathFinder::GetHeuristicIdx((AStarPathFinder *)this, nRoleIndex, "
                "(int)&this->m_nHandleEnemyWell) ) { return 1; } "
                "return 0; }")
        result = transform_oop_calls(code, cls_name='Foo')
        self.assertNotIn('[MISATTRIBUTED]', result)
        self.assertIn('AStarPathFinder::GetHeuristicIdx(nRoleIndex, '
                      '(int)&this->m_nHandleEnemyWell)', result)
        # qualifier preserved: the qualified form is what keeps the direct-call
        # (non-dispatch) semantics for this virtual method
        self.assertIn('->AStarPathFinder::GetHeuristicIdx(', result)

    def test_ctor_dtor_excluded(self):
        """The gate must explicitly exclude ctor/dtor: a ctor/dtor can never
        be "the unrelated class's vtable slot on our own this" case. Force the
        two arity/vtable facts true via the evidence caches and assert the
        marker still stands for a dtor."""
        import ast_transform as _at
        saved_ret = _at._RET_SLOTS_CACHE
        saved_va = _at._VA_BY_METHOD
        saved_vt = _at._VTABLE_EVIDENCE
        try:
            _at._RET_SLOTS_CACHE = {('FakeCls', '~FakeCls'): 1}
            _at._VA_BY_METHOD = {('FakeCls', '~FakeCls'): 0xDEADBEEF}
            _at._VTABLE_EVIDENCE = (frozenset({0xDEADBEEF}),
                                    frozenset({('FakeCls', '~FakeCls')}))
            code = ("int Foo::Bar() { "
                    "FakeCls::_FakeCls((FakeCls *)this, 1); return 0; }")
            result = transform_oop_calls(code, cls_name='Foo')
            self.assertIn('[MISATTRIBUTED]', result)
        finally:
            _at._RET_SLOTS_CACHE = saved_ret
            _at._VA_BY_METHOD = saved_va
            _at._VTABLE_EVIDENCE = saved_vt

    def test_rowtable_family_is_required(self):
        """CG-023: a missing family list must raise, never fall back to an
        empty set (the empty set silently reclassifies every ROWTABLE site as
        MISATTRIBUTED — measured 586 sites / 326 files)."""
        import ast_transform as _at
        import builtins
        saved = _at._ROWTABLE_CACHE
        saved_open = builtins.open
        try:
            _at._ROWTABLE_CACHE = None
            def _boom(*a, **kw):
                raise FileNotFoundError('simulated missing family list')
            builtins.open = _boom
            with self.assertRaises(RuntimeError):
                _at._rowtable_family()
        finally:
            builtins.open = saved_open
            _at._ROWTABLE_CACHE = saved

    def test_vtable_evidence_is_required(self):
        """Same contract for the IDB export: a missing export must raise
        rather than silently degrading the gate to 'never opens'."""
        import ast_transform as _at
        import builtins
        saved_va = _at._VA_BY_METHOD
        saved_vt = _at._VTABLE_EVIDENCE
        saved_open = builtins.open
        try:
            _at._VA_BY_METHOD = None
            _at._VTABLE_EVIDENCE = None
            def _boom(*a, **kw):
                raise FileNotFoundError('simulated missing export')
            builtins.open = _boom
            with self.assertRaises(RuntimeError):
                _at._load_va_by_method()
        finally:
            builtins.open = saved_open
            _at._VA_BY_METHOD = saved_va
            _at._VTABLE_EVIDENCE = saved_vt

    def test_ret_slots_missing_exe_warns_on_stderr(self):
        """t6 §4: the typed `except` sites that stay permissive must be
        VISIBLE. With `original/PAL3.exe` absent, `_load_ret_slots` used to
        return silently; it must now say so on stderr."""
        import ast_transform as _at
        import builtins
        import io
        import contextlib
        saved_open = builtins.open
        saved_cache = _at._RET_SLOTS_CACHE
        saved_isfile = _at.os.path.isfile
        buf = io.StringIO()
        try:
            _at._RET_SLOTS_CACHE = {}
            _at.os.path.isfile = (
                lambda p: False if str(p).endswith('PAL3.exe') else saved_isfile(p))
            with contextlib.redirect_stderr(buf):
                _at._load_ret_slots()
            self.assertIn('[WARN]', buf.getvalue())
        finally:
            _at.os.path.isfile = saved_isfile
            builtins.open = saved_open
            _at._RET_SLOTS_CACHE = saved_cache


class TestStage3Cleanup(unittest.TestCase):
    """Test stage3_cleanup.py run()"""

    def test_vfptr_assignment_passthrough(self):
        """vfptr assignments pass through stage3 unchanged
        (_vtbl_placeholder was renamed to vfptr in 8a2bba3e9; the old
        comment-out behavior no longer applies to this member name)"""
        code = "this->vfptr = 0;"
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('vfptr = 0', result)

    def test_vfptr_assignment_multiline_function(self):
        """vfptr assignment inside a function body is not touched"""
        code = "void Test() { this->vfptr = 0; DoSomething(); }"
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('vfptr = 0', result)
        self.assertIn('DoSomething();', result)

    def test_normal_code_unchanged(self):
        """Non-vtbl code should not be affected"""
        code = "this->DoSomething(1, 2);"
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertEqual(result.strip(), code.strip())

    def test_vftable_commented(self):
        """__vftable references should still be commented (existing behavior)"""
        code = "this->__vftable = &vtable;"
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('// [VFTABLE]', result)

    def test_thiscall_removed(self):
        """__thiscall should be stripped from function body"""
        code = "void Foo::Bar() { __thiscall Func(); }"
        result = stage3_run(code, _make_ctx(cls_name='Foo'))
        self.assertNotIn('__thiscall', result)

    def test_this_declaration_removed(self):
        """'ClassName *this;' declaration should be removed in class methods"""
        code = "void Foo::Bar()\n{\nFoo *this;\nint x;\n}"
        result = stage3_run(code, _make_ctx(cls_name='Foo'))
        self.assertNotIn('*this', result)

    def test_coerce_float_replaced(self):
        """COERCE_FLOAT(0x3F800000) should be replaced with 1.0f"""
        code = "float x = COERCE_FLOAT(0x3F800000);"
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertNotIn('COERCE_FLOAT', result)
        self.assertIn('1.0f', result)

    def test_coerce_float_small_int(self):
        """COERCE_FLOAT(0) should be replaced with 0.0f"""
        code = "float x = COERCE_FLOAT(0);"
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertNotIn('COERCE_FLOAT', result)
        self.assertIn('0.0f', result)

    def test_gap_zero(self):
        """obj.0 should be stripped from member access"""
        code = "x = arr[i].0;"
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertNotIn('.0', result)


class TestVftableFallback(unittest.TestCase):
    """Test vftable cleanup fallback (IDA handles conversion; codegen just comments)"""

    def test_vftable_assign_commented(self):
        """genuine vptr store (address of a vftable symbol) stays commented"""
        code = 'this->__vftable = &off_123456;'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('// [VFTABLE]', result)

    def test_vftable_assign_backtick_symbol_commented(self):
        """`&Cls::`vftable'` is the compiler-managed vptr store -> comment path

        (the line is then removed by `_remove_backtick_calls`, so assert on the
        comment pass itself rather than on the final text)
        """
        import stages.stage3_cleanup as _s3
        code = "void Test::Foo() {\n    this->__vftable = &Foo::`vftable';\n}"
        commented = _s3._comment_vptr_stores(code)
        self.assertIn('// [VFTABLE] this->__vftable', commented)
        self.assertEqual(_s3._vptr_store_kind("    this->__vftable = &Foo::`vftable';"),
                         'store')

    def test_normal_method_unchanged(self):
        """Regular virtual method calls should not be affected"""
        code = 'this->DoSomething(1, 2);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertEqual(result.strip(), code.strip())

    def test_vftable_direct_call_stubbed(self):
        """(*(void(**)(Type*))(obj->__vftable))(obj) -> signature-accurate stub
        (structure preserved; old behavior commented out the whole statement)"""
        code = '(*(void (**)(SceneObj *))(this->m_pObj->__vftable))(this->m_pObj);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('pal3_vtbl_unk_0(this->m_pObj)', result)
        self.assertIn('[VFTABLE-STUB]', result)
        self.assertNotIn('// [VFTABLE]', result)

    def test_vftable_offset4_call_stubbed(self):
        """(*(void(**)(Type*))(obj->__vftable + 4))(obj) -> stub, not deletion"""
        code = '(*(void (**)(SceneObj *))(this->m_pObj->__vftable + 4))(this->m_pObj);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('pal3_vtbl_unk_0(this->m_pObj)', result)
        self.assertIn('[VFTABLE-STUB]', result)
        # signature from the decompiler cast is preserved
        self.assertIn('static void pal3_vtbl_unk_0(SceneObj *);', result)

    def test_mixed_normal_and_vftable(self):
        """Only genuine vptr stores are commented; data stores are restored.

        t7: `this->__vftable = 0;` is a real offset-0 store that appears in the
        tree as a data write (see SceneObj/UISceneFrm contexts in
        data/status/_cleanup_fix_vftable_comment.md), so it must survive as an
        offset-0 access instead of being dropped.
        """
        code = '''void Test::Foo() {
    this->NormalCall(1);
    this->__vftable = 0;
    this->OtherCall(2);
}'''
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('this->NormalCall(1)', result)
        self.assertIn('this->OtherCall(2)', result)
        self.assertNotIn('[VFTABLE]', result)
        self.assertIn('(*(void **)(this)) = (void *)(0);', result)

    def test_slot0_vftable_call_folded(self):
        """((Type*)&obj->__vftable)->Method(args) -> offset-0 address, compilable"""
        code = '((UIWnd *)&this->m_wnd->__vftable)->Destroy(0);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertNotIn('[VFTABLE]', result)
        self.assertIn('((UIWnd *)((void **)(this->m_wnd)))->Destroy(0);', result)

    def test_vftable_value_read_folded(self):
        """X->__vftable read -> (*(void **)(X)); &X->__vftable -> ((void **)(X))"""
        code = 'vftable = (int ( **)(gbGfxManager *, CHAR *))gfxMgr->__vftable;'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('(*(void **)(gfxMgr))', result)

    def test_vftable_address_keeps_pointer_type(self):
        """&X->__vftable keeps the `void **` type so pointer arithmetic holds"""
        code = 'v20 = *(int *)((char *)&g_RoleSlotBuf.__vftable + k);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('((void **)&(g_RoleSlotBuf))', result)

    def test_qualified_vftable_left_alone(self):
        """A base-subobject offset is not recoverable -> never folded

        SceneObj has GlowObj at +8, so folding `this->GlowObj::__vftable` to
        offset 0 would write the wrong address.
        """
        code = 'this->GlowObj::__vftable = 0;'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('this->GlowObj::__vftable = 0;', result)
        self.assertNotIn('(*(void **)(this)) = ', result)

    def test_vftable_chained_access_left_alone(self):
        """X->__vftable->M cannot be folded (void * cannot be dereferenced)"""
        code = 'v = gfxMgr->__vftable->GetSomething(1);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('gfxMgr->__vftable->GetSomething(1)', result)

    def test_auto_commented_assignment_value_restored(self):
        """t7: an assignment whose ctor-call value is consumed must survive

        Real site: pal3/src/Combat/CCBStage.cpp:868
        (`Color = v22.gbColorQuad(..)->Color;`).  The game-class branch of
        `_get_ctor_call_info` needs `store.game_classes`, which the unit-test
        harness never loads, so it is stubbed here.
        """
        from data import store
        store.game_classes.add('gbColorQuad')
        self.addCleanup(store.game_classes.discard, 'gbColorQuad')
        code = 'Color = v22.gbColorQuad(1, 2)->Color;'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertNotIn('[AUTO-COMMENTED]', result)
        self.assertIn('Color = ((gbColorQuad *)&v22)->Color;', result)

    def test_auto_commented_arrow_assignment_value_restored(self):
        """obj->Cls(args) folds to ((Cls *)obj)

        Real site: pal3/src/Role/ObjectCamera.cpp:90 (`v4 = v3->gbCamera(..)`),
        whose `v4` is later stored into `this->m_pCamera`.
        """
        from data import store
        store.game_classes.add('gbCamera')
        self.addCleanup(store.game_classes.discard, 'gbCamera')
        code = 'v4 = v3->gbCamera(position);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertNotIn('[AUTO-COMMENTED]', result)
        self.assertIn('v4 = ((gbCamera *)v3);', result)

    def test_auto_commented_dtor_assignment_value_restored(self):
        """`x->~Cls(a)` (destructor-pattern branch) folds to the object pointer

        Real site: pal3/src/Misc/UIStatic.cpp:262
        """
        code = 'this->m_textx = gfxMgr->~gbGfxManager(lpString);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertNotIn('[AUTO-COMMENTED]', result)
        self.assertIn('this->m_textx = ((gbGfxManager *)gfxMgr);', result)

    def test_auto_commented_standalone_call_still_commented(self):
        """A standalone (value-less) ctor-call statement keeps the old behaviour

        Real site: pal3/src/Misc/UIStatic.cpp:199 etc.
        """
        from data import store
        store.game_classes.add('OpenNULLFile')
        self.addCleanup(store.game_classes.discard, 'OpenNULLFile')
        code = '(OpenNULLFile *)&v13->OpenNULLFile();'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('[AUTO-COMMENTED]', result)

    def test_ida_misid_table_removed(self):
        """t7: the hard-coded IDA-misidentification pattern table is gone"""
        code = ('ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;\n'
                'std::_Xlen();\n'
                'Concurrency::IThreadProxy *Proxy;\n')
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertNotIn('[IDA_MISID]', result)
        self.assertIn('ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;', result)
        self.assertIn('std::_Xlen();', result)
        self.assertIn('Concurrency::IThreadProxy *Proxy;', result)

    def test_ida_vftable_dead_branch_removed(self):
        """the unreachable `insert` / `comment_vft` actions no longer exist"""
        import stages.stage3_cleanup as _s3
        src = open(_s3.__file__, encoding='utf-8').read()
        executable = '\n'.join(l for l in src.split('\n')
                               if not l.lstrip().startswith('#'))
        self.assertNotIn("action == 'comment_vft'", executable)
        self.assertNotIn("action == 'insert'", executable)


if __name__ == '__main__':
    unittest.main(verbosity=2)


if __name__ == '__main__':
    unittest.main(verbosity=2)
