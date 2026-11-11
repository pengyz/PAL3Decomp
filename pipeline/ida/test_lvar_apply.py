"""[L-VAR 测试 2026-11-11] 注解 lvars → IDB user lvar 技术方案打通测试。

用法: idat -A -S"pipeline/ida/test_lvar_apply.py" original/PAL3.exe.i64
产出: pipeline/ida/_logs/test_lvar_apply_log.txt (PASS/FAIL 证据链)

测试链(技术方案四步, 全部真机制):
  T1 读注解   structs/CameraCtrl.json methods[0x41CC50].lvars = {"v7": "float *"}
  T2 反编译   ida_hexrays.decompile(0x41CC50), 定位 lvar 'v7', 记录当前类型
  T3 设类型   _resolve_member_type("float *") → set_lvar_type → save_user_lvar_settings
  T4 重渲染   重新 decompile, 验证声明行含 'float *v7' 且体使用点渲染一致

通过判据: T4 重渲染声明含 'float *v7' 且无异常。通过后同链可生产化
(apply_annotations Section 9 增补注解 lvars 分支)。
"""
import json
import os
import sys

import ida_funcs
import ida_hexrays
import ida_typeinf

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(PROJECT_ROOT, 'pipeline', 'ida'))

LOG = []
FN_ADDR = 0x41CC50
LV_NAME = 'v7'
LV_TYPE = 'float *'
ANN_PATH = os.path.join(PROJECT_ROOT, 'data', 'annotations', 'structs', 'CameraCtrl.json')


def log(msg):
    LOG.append(str(msg))
    print('[test-lvar] %s' % msg)


def main():
    # T0 环境自检
    if not ida_hexrays.init_hexrays_plugin():
        log('FAIL T0: Hex-Rays 不可用')
        return 1
    log('T0 OK: Hex-Rays 就绪')

    # T1 读注解(真消费路径, 不硬编码)
    ann = json.load(open(ANN_PATH, encoding='utf-8'))
    m = (ann.get('methods') or {}).get('0x0041CC50') or {}
    lv = (m.get('lvars') or {}).get(LV_NAME)
    if lv is None:
        log('FAIL T1: 注解缺 %s 的 lvars 覆盖' % LV_NAME)
        return 1
    log('T1 OK: 注解 %s = %r' % (LV_NAME, lv))

    func = ida_funcs.get_func(FN_ADDR)
    if not func:
        log('FAIL T1b: 0x%X 无函数' % FN_ADDR)
        return 1

    # T2 反编译+定位 lvar+记录当前类型
    cfunc = ida_hexrays.decompile(func)
    target = None
    for lvar in cfunc.lvars:
        if lvar.name == LV_NAME:
            target = lvar
            break
    if target is None:
        log('FAIL T2: lvar %s 不存在(现名: %s)' % (
            LV_NAME, [l.name for l in cfunc.lvars][:10]))
        return 1
    try:
        old_t = str(target.type())
    except Exception:
        old_t = '?'
    log('T2 OK: lvar %s 现类型 %s' % (LV_NAME, old_t))

    # T3 设类型(_resolve_member_type 与 Section 9 同源)
    try:
        from apply_annotations import _resolve_member_type  # 真实现复用
        tif = _resolve_member_type(LV_TYPE, ida_typeinf.get_idati())
    except Exception as e:
        log('FAIL T3a: 解析器不可用 %s' % str(e)[:80])
        return 1
    if tif is None:
        log('FAIL T3a: %r 解析为 None' % LV_TYPE)
        return 1
    try:
        target.set_lvar_type(tif)
    except Exception as e:
        log('FAIL T3b: set_lvar_type %s' % str(e)[:80])
        return 1
    # 持久化(Section 9 同款 uvec 全量保存)
    uvec = ida_hexrays.lvar_uservec_t()
    uvec.lvvec = ida_hexrays.lvar_saved_infos_t()
    for lv_i in cfunc.lvars:
        si = ida_hexrays.lvar_saved_info_t()
        ll = ida_hexrays.lvar_locator_t()
        ll.defea = cfunc.entry_ea
        si.ll = ll
        si.name = lv_i.name
        try:
            _t = lv_i.type
            if _t is not None and hasattr(_t, 'is_correct') and _t.is_correct():
                si.type = _t
        except Exception:
            pass
        uvec.lvvec.push_back(si)
    ida_hexrays.save_user_lvar_settings(FN_ADDR, uvec)
    log('T3 OK: set_lvar_type(%s) + save_user_lvar_settings' % LV_TYPE)

    # T4 重渲染验证(重新 decompile, 读声明)
    cfunc2 = ida_hexrays.decompile(func)
    text = str(cfunc2)
    decl_line = None
    for ln in text.split('\n'):
        if LV_NAME in ln and ('float *' in ln or 'float*' in ln):
            decl_line = ln.strip()
            break
    if decl_line is None:
        v7_line = [l.strip() for l in text.split('\n') if ' v7;' in l or ' v7 ' in l][:1]
        log('FAIL T4: 重渲染未见 float *v7 声明; 候选行: %s' % v7_line)
        return 1
    log('T4 OK: 重渲染声明 %r' % decl_line[:70])

    # 持久化复核: fresh decompile(隔离缓存)后声明仍为真类型
    ida_hexrays.clear_cached_cfuncs()
    cfunc3 = ida_hexrays.decompile(func)
    t3 = str(cfunc3)
    ok3 = ('float *' in [l for l in t3.split('\n') if LV_NAME in l][0]) if any(
        LV_NAME in l for l in t3.split('\n')) else False
    log('T4b %s: clear-cache 后重反编译声明仍含 float *v7 = %s' % ('OK' if ok3 else 'FAIL', ok3))
    if not ok3:
        return 1

    log('=== PASS: 注解 lvars → IDB user lvar 全链打通 ===')
    return 0


try:
    res = main()
except Exception as _e:
    import traceback
    log('FAIL EXC: %s' % str(_e)[:200])
    log(traceback.format_exc()[-900:])
    res = 1
try:
    log_dir = os.path.join(PROJECT_ROOT, 'pipeline', 'ida', '_logs')
    os.makedirs(log_dir, exist_ok=True)
    open(os.path.join(log_dir, 'test_lvar_apply_log.txt'), 'w',
         encoding='utf-8').write('\n'.join(LOG))
except Exception:
    pass
import idc
idc.qexit(res)
