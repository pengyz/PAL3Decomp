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
        """Class::Method(this, ...) -> this->Method(...)"""
        code = "int Foo::Bar() { Foo::DoSomething(this, 1, 2); return 0; }"
        result = transform_oop_calls(code, cls_name='Foo')
        self.assertIn('this->DoSomething(1, 2)', result)
        self.assertNotIn('Foo::DoSomething(this', result)

    def test_identifier_as_first_arg(self):
        """Class::Method(var, ...) -> ((Class *)var)->Method(...)"""
        code = "int test() { Foo::DoSomething(ptr, 1, 2); return 0; }"
        result = transform_oop_calls(code)
        self.assertIn('((Foo *)ptr)->DoSomething(1, 2)', result)

    def test_complex_expr_as_first_arg(self):
        """Class::Method(ptr->field, ...) -> ((Class *)ptr->field)->Method(...)"""
        code = "int test() { Foo::DoSomething(obj->field, 1); return 0; }"
        result = transform_oop_calls(code)
        self.assertIn('((Foo *)obj->field)->DoSomething(1)', result)

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
        """OtherClass::Method(this, ...) -> ((OtherClass *)this)->Method(...)"""
        code = "int Derived::Bar() { OtherClass::DoSomething(this, 1, 2); return 0; }"
        result = transform_oop_calls(code, cls_name='Derived')
        self.assertIn('((OtherClass *)this)->DoSomething(1, 2)', result)
        self.assertNotIn('OtherClass::DoSomething(this', result)


class TestStage3Cleanup(unittest.TestCase):
    """Test stage3_cleanup.py run()"""

    def test_vtbl_placeholder_commented(self):
        """_vtbl_placeholder member access should be commented out"""
        code = "this->_vtbl_placeholder = 0;"
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('// [VFTABLE]', result)
        self.assertIn('_vtbl_placeholder', result)  # still visible inside comment

    def test_vtbl_placeholder_multiline_function(self):
        """_vtbl_placeholder in a function body should be commented"""
        code = "void Test() { this->_vtbl_placeholder = 0; DoSomething(); }"
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('// [VFTABLE]', result)

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
        """__vftable = value should be commented out (compiler-managed)"""
        code = 'this->__vftable = &off_123456;'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('// [VFTABLE]', result)

    def test_normal_method_unchanged(self):
        """Regular virtual method calls should not be affected"""
        code = 'this->DoSomething(1, 2);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertEqual(result.strip(), code.strip())

    def test_vftable_direct_call_commented(self):
        """(*(void(**)(Type*))(obj->__vftable))(obj) -> commented (fallback)"""
        code = '(*(void (**)(SceneObj *))(this->m_pObj->__vftable))(this->m_pObj);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('// [VFTABLE]', result)

    def test_vftable_offset4_call_commented(self):
        """(*(void(**)(Type*))(obj->__vftable + 4))(obj) -> commented (fallback)"""
        code = '(*(void (**)(SceneObj *))(this->m_pObj->__vftable + 4))(this->m_pObj);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('// [VFTABLE]', result)

    def test_mixed_normal_and_vftable(self):
        """Normal code with vftable refs should comment only vftable lines"""
        code = '''void Test::Foo() {
    this->NormalCall(1);
    this->__vftable = 0;
    this->OtherCall(2);
}'''
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('this->NormalCall(1)', result)
        self.assertIn('// [VFTABLE]', result)
        self.assertIn('this->OtherCall(2)', result)

    def test_slot0_vftable_call_commented(self):
        """((Type*)&obj->__vftable)->Method(args) -> commented (IDA layer handles)"""
        code = '((UIWnd *)&this->m_wnd->__vftable)->Destroy(0);'
        result = stage3_run(code, _make_ctx(cls_name='Test'))
        self.assertIn('// [VFTABLE]', result)


if __name__ == '__main__':
    unittest.main(verbosity=2)
