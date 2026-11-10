"""Collect and group functions from decomp JSON files.

Reads all decomp/*.json, parses MSVC mangled names, and groups functions
by class (for class .cpp files) or as free functions.
"""
import json
import re
from collections import defaultdict
from pathlib import Path

from data import store

# Classes to skip entirely (CRT, STL, gbengine wrappers, thunk trampolines)
SKIP_CLASSES = {
    'std', 'stdiobuf', 'exception', 'type_info', 'filebuf',
    'Iostream_init', 'Concurrency',
    'j_std', 'j_j_codecvt_base',
}

# Auto-detect classes defined in gbengine headers
import re as _re
_GBENGINE_DIR = Path(__file__).parent.parent.parent.parent / "include" / "gbengine"
if _GBENGINE_DIR.exists():
    for _hf in _GBENGINE_DIR.glob("*.h"):
        with open(_hf, 'r', encoding='utf-8', errors='replace') as _fh:
            for _line in _fh:
                _m = _re.match(r'^(?:class|struct)\s+(\w+)', _line)
                if _m:
                    SKIP_CLASSES.add(_m.group(1))

# Organize classes into subdirectories by category
CLASS_DIRS = {
    # Combat system
    'CCBSystem': 'Combat', 'CCBRoleState': 'Combat', 'CCBStage': 'Combat',
    'CCBStageCam': 'Combat', 'CCBStageRole': 'Combat', 'CCBStageScene': 'Combat',
    'CCBStageEffect': 'Combat', 'CCBStageShadow': 'Combat',
    'CCBControl': 'Combat', 'CCBAttackSequen': 'Combat',
    'CCBAI': 'Combat', 'CCBUI': 'Combat', 'CCCTData': 'Combat',
    'CCBAIWindow': 'Combat', 'CCBControlWindow': 'Combat',
    'CCBItemWindow': 'Combat', 'CCBLineupWindow': 'Combat',
    'CCBMagicWindow': 'Combat', 'CCBSkillWindow': 'Combat',
    'CCBParabolaWindow': 'Combat', 'CCBProtectWindow': 'Combat',
    'CCBResultWindow': 'Combat', 'CCBCamControl': 'Combat',
    'Combat': 'Combat', 'CUtil': 'Combat',
    # Effects
    'CEffect': 'Effect', 'CEffMgr': 'Effect', 'CEffectSystem': 'Effect',
    'CEffCylinder': 'Effect', 'CEffExplosive': 'Effect', 'CEffGrid': 'Effect',
    'CEffMeteor': 'Effect', 'CEffModel': 'Effect', 'CEffQuad': 'Effect',
    'CEffQuake': 'Effect', 'CEffShock': 'Effect', 'CEffSParticle': 'Effect',
    'CEffgbParticle': 'Effect', 'CMeteorChain': 'Effect',
    'C2DSpark': 'Effect', 'C3DSpark': 'Effect',
    'ScreenEffect': 'Effect', 'ScreenEffectMgr': 'Effect',
    # UI
    'UIWnd': 'UI', 'UIScene': 'UI', 'UIManager': 'UI', 'UISystem': 'UI',
    'UIDialog': 'UI', 'UIBigDialog': 'UI', 'UISelectDialog': 'UI',
    'UIItem': 'UI', 'UIBase': 'UI', 'UICamera': 'UI', 'UICursor': 'UI',
    'UIListBox': 'UI', 'UILBColumn': 'UI', 'UILBItem': 'UI',
    'UINote': 'UI', 'UIQuadManager': 'UI', 'UIRenderObj': 'UI',
    'EquipUI': 'UI', 'MagicUI': 'UI', 'PropUI': 'UI', 'StateUI': 'UI',
    # Render
    'RenderTarget': 'Render', 'RenderTarget2': 'Render',
    'RenderTarget3': 'Render', 'RenderTarget4': 'Render',
    'CRenderTarget': 'Render', 'CRenderTarget2': 'Render',
    'CScreenMode': 'Render', 'TextureLib': 'Render',
    # Game core
    'PAL3': 'GameBase', 'GRPinput': 'GameBase', 'Config': 'GameBase',
    'Logger': 'GameBase', 'InputSystem': 'GameBase',
    'SoundSystem': 'GameBase', 'SoundContext': 'GameBase',
    # Script
    'PalScript': 'Script', 'PalScriptMgr': 'Script',
    'ScriptObj': 'Script', 'ScriptSystem': 'Script',
    # Scene/Role
    'Role': 'Role', 'RoleSystem': 'Role', 'NPC': 'Role',
    'Actor': 'Role', 'Object3D': 'Role', 'ObjectCamera': 'Role',
    'Scene': 'Scene', 'SceneMgr': 'Scene', 'SceneObj': 'Scene',
    'Camera': 'Scene', 'CameraCtrl': 'Scene', 'CameraSystem': 'Scene',
    # Data
    'CGameData': 'Data', 'PAL_GDB': 'Data',
    # Misc
    'MiniGame1': 'MiniGame', 'MiniGame3': 'MiniGame',
    'ParabolaCalculator': 'Misc', 'PtrArray': 'Misc', 'Array': 'Misc',
    'OpenBaseFile': 'Misc', 'OpenNULLFile': 'Misc', 'OpenSceneFile': 'Misc',
    'MvcController': 'Misc', 'MvcViewport': 'Misc',
}


def get_class_dir(cls_name):
    """Get subdirectory for a class."""
    return CLASS_DIRS.get(cls_name, 'Misc')


def _get_skip_classes():
    """Build the full skip set including thunk classes from annotations."""
    skip = set(SKIP_CLASSES)

    # Add thunk class names from skip_functions.json
    # 2026-09-20 审计 P1-5（第二批）：直读收敛到单一读点 annotation_view。
    # 逻辑逐字等价：原先读 store.annotations_dir/"skip_functions.json" 并遍历其 values()。
    try:
        import annotation_view as _av
    except ImportError:
        from pipeline.gen import annotation_view as _av
    skip_data = _av.skip_functions(store=store)
    if skip_data:
        for info in skip_data.values():
            if info.get('reason') == 'thunk':
                name = info.get('name', '')
                # Only skip the entire class if the thunk is a class-level
                # wrapper (j_ClassName). Method-level thunks (ClassName::method)
                # should not suppress the whole class -- they're individual stubs.
                if '::' not in name and name.startswith('j_'):
                    skip.add(name[2:])
    return skip


def _annotation_class_map():
    """[5a7a3b86 残渣清理] 此函数已无调用点（N1 路由已撤）——保留空壳仅为外部引用兼容。"""
    return {}


_ANN_CLS_MAP = None


_ANN_CLS_MAP = None


def collect_functions(decomp_dir=None):
    """Collect all functions from decomp, grouped by class and free functions.

    Args:
        decomp_dir: Path to decomp JSON directory. Defaults to store.decomp_dir.

    Returns:
        (by_class, free_funcs) where:
            by_class: dict mapping class name -> list of method dicts
            free_funcs: list of free function dicts
    """
    if decomp_dir is None:
        decomp_dir = store.decomp_dir
    decomp_dir = Path(decomp_dir)

    skip_classes = _get_skip_classes()
    by_class = defaultdict(list)
    free_funcs = []

    for f in sorted(decomp_dir.glob("*.json")):
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                d = json.load(fh)
        except Exception as _e:
            # 5a7a3b86 硬债①：解析失败**显式报错**（8 个零填充坏文件曾被裸 except 静默吞
            # ⇒ 7 函数体丢失+UIQuadManager TU 蒸发——R12 中断残留的静默面）
            print("  [collect-ERR] %s: %s" % (f.name, _e))
            continue

        name = d.get('name', '')
        code = d.get('decompiled_c', '')
        addr = d.get('address', '')
        sig = d.get('signature', '')

        if not code or not name:
            continue
        if name.startswith('sub_'):
            continue


        # Demangle MSVC names: ?Method@Class@@... -> Class::Method
        cls = None
        method = None
        if name.startswith('?'):
            inner = name[1:]
            if inner.startswith('?0') or inner.startswith('?1'):
                code_ch = inner[1]
                rest = inner[2:]
                at_pos = rest.find('@')
                if at_pos > 0:
                    cls = rest[:at_pos]
                    method = cls if code_ch == '0' else '~' + cls
            else:
                at_pos = inner.find('@')
                if at_pos > 0:
                    method = inner[:at_pos]
                    rest = inner[at_pos + 1:]
                    at_pos2 = rest.find('@')
                    if at_pos2 > 0:
                        cls = rest[:at_pos2]
            if cls and ('$' in cls or '<' in cls or not (cls[0].isalpha() or cls[0] == '_')):
                cls = None
        elif '::' in name:
            # [F-CG#2 2026-10-15] 先剥参数表再 rsplit：decomp name 的**参数表内可含 `::`**
            # （嵌套型 `AStarPathFinder::NODE *`）⇒ 原 `name.rsplit('::', 1)` 切进参数表
            # ⇒ cls='AStarPathFinder::Release(AStarPathFinder' · method='NODE *)' ⇒
            # stage1 name 归一拼回双参表（C2091 族）+ emit_cpp safe_name 不含 `(`/`)`
            # ⇒ 文件名带 `(`。实测影响面=decomp 全库 4 条（911 条扫描：PushOpen/TryExpand/
            # UpdateNeighbors/Release = 49 错同根因），无外溢。
            base = name.split('(')[0]              # AStarPathFinder::Release
            parts = base.rsplit('::', 1)
            cls = parts[0]
            method = parts[1] if len(parts) > 1 else None
        # N1 注记（回退教训 2026-09-29）：曾加"渲染首行/注解映射回退路由成员"——
        # 30 函数改类后裸调用失 free_func_sigs 声明 ⇒ C2065 洪泛（S2 100→91）。
        # **分类保持 name 形原判**；N1 的正确闭合在调用形转写层（挂账）。

        # [__ovl_ 剥离退役 2026-11-04] 原「collect 无条件 strip_ovl + 正文重写」
        # （2026-09-14 959ef254b 起存在）已退役：戳归一已下沉 annotation 层
        # （2026-11-04 全量剥除 17 处，撞名如实显形——用户裁定「让隐性撞名变真撞名」）。
        # 对抗复核定谳（out/_adversarial_review_verdict.md #1）：定义名剥落的真路径是
        # 此处（stage1 从正文签名行重建定义），emit_cpp 正则只是调用形残余清理；
        # 无条件剥（定义侧）+ 撞则不剥（声明侧）判据不对称 = C2084 隐性撞名制造点。
        # 此后 annotation 名即最终名：再有戳名原样透传（可见、不静默合并）。

        # 【2026-09-15 修】规范化 Hex-Rays 的**反引号特名**：
        #   `` `scalar deleting destructor' `` → `_scalar_dtor`
        #   `` `vector deleting destructor' `` → `_vector_dtor`
        #
        # 为什么必须做：`collect.py:196` 的跳过判据只认 `_scalar_dtor` / `_sdtor`，
        # 而 `:171-173` 从 name（`UIStatic::`scalar deleting destructor'(uint)`）提取出的
        # method 是**反引号原名** ⇒ 判据**不匹配** ⇒ 该函数**未被跳过**、带着反引号名进入 codegen
        # ⇒ 其函数头含反引号/非法字符被剥离 ⇒ 产物只剩 `return (int)this;` + `}`
        # ⇒ **C2143 语法崩、文件必然编译失败**（实测 `UIStatic.cpp` 6 错）。
        #
        # 与既有 `__ovl_` 处理同模式：**改名后必须同步重写正文**，
        # 因为 stage1 会从正文自己的签名行重建定义。
        #
        # ⚠️ 注解侧本就把该地址记为 `_scalar_dtor`（`source: vtable_migrated`）
        # ⇒ 两处命名本就不一致，此处是**归一化**，不是新造信息。
        if method:
            from pipeline.gen.normalization import normalize_dtor_name as _ndn
            _norm = _ndn(method)  # 单点律收编
            if _norm and _norm != method:
                code = re.sub(r'\b%s\b' % re.escape(method), _norm, code)
                method = _norm

        if cls and method:
            if cls in skip_classes:
                continue

            # Skip compiler-generated _scalar_dtor functions.
            # These are vtable wrappers around virtual destructors; the compiler
            # generates them automatically from 'virtual ~ClassName()' declarations.
            # 【2026-09-15】`_vector_dtor` 同属编译器生成物，一并跳过
            # （其名字由上面的规范化产生，见 `` `vector deleting destructor' `` → `_vector_dtor`）。
            # [债 2026-11-10] scalar_dtor_classes 是 DEAD 集(零读者——真实现=
            # emit_headers 的 header_facts 缓存)。continue 行为保留(跳过发射)。
            if '_scalar_dtor' in method or '_vector_dtor' in method or method.startswith('_sdtor'):
                continue

            # Strip _misattrib_ prefix: put function back under the original class
            # with a comment marking it as misattributed (attribution unconfirmed)
            if cls.startswith('_misattrib_'):
                original_cls = cls
                cls = cls[len('_misattrib_'):]
                code = '// [MISATTRIB] attribution unconfirmed\n' + code
                # Also strip _misattrib_ references in function body
                code = code.replace('_misattrib_' + cls + '::', cls + '::')
                code = code.replace('misattrib_' + cls + '::', cls + '::')

            # [死守卫删除 2026-11-01] 对抗审核 F2：L211 已无条件剥，此守卫是死代码
            # 原逻辑：Strip __ovl_XXXX suffix to match header declaration (emit_headers.py does the same)

            # P-A5 (2026-11-09): structs annotation methods[addr].name 覆盖 decomp 名。
            # IDA 错名实证: UIListBox 0x43DE90(jmp 0x43dea0=AddColumn 的 5 字节 thunk)
            # 被命名为 Destroy,与真体 0x43E520(vtable 槽)同名 → C2084。
            try:
                try:
                    import annotation_view as _av_p5
                except ImportError:
                    from pipeline.gen import annotation_view as _av_p5
                _sp5 = _av_p5.struct_by_class(cls, store=store)
                _anm5 = (_sp5.get('methods', {}) or {}).get(addr) if _sp5 else None
                if _anm5 is None and _sp5:
                    _au = (str(addr).upper().replace('0X', '0x'))
                    _methods5 = _sp5.get('methods', {}) or {}
                    for _k5, _v5 in _methods5.items():
                        if str(_k5).upper() == _au:
                            _anm5 = _v5
                            break
                _an5 = _anm5.get('name') if isinstance(_anm5, dict) else None
                if _an5 and _an5 != method and 'thunk' in str(_anm5.get('name_source', '')) + str(_anm5.get('name_note', '')):
                    # 体文本定义行同步改名(stage1 重建按 ctx.method 搜定义行——
                    # 不同步则搜不到 → 保留旧名 → C2084 复活)
                    code = code.replace('%s::%s(' % (cls, method), '%s::%s(' % (cls, _an5), 1)
                    code = code.replace('%s::%~%s(' % (cls, method), '%s::%~%s(' % (cls, _an5), 1)
                    method = _an5
            except Exception:
                pass
            by_class[cls].append({
                'name': '%s::%s' % (cls, method),
                'method': method,
                'code': code,
                'addr': addr,
                'sig': sig,
                '_source_file': str(f),
            })
        else:
            # [R91 2026-10-24·重归属战役 1b] 地址已归属且过门（reattrib.decide_routing）
            # ⇒ 路由进类发射（体变 Cls::Method，stage1 重建签名剥 this 形参——复核已验链路）。
            # 按地址不按名：`_` 前缀漂移族（_todo_* vs todo_*，复核 B 实证 20 条）地址可靠。
            _routed = getattr(store, 'routed_free', None) or {}
            _r = None
            try:
                _r = _routed.get(int(str(addr), 16)) if addr else None
            except ValueError:
                _r = None
            if _r:
                _rc, _rm = _r
                by_class[_rc].append({
                    'name': '%s::%s' % (_rc, _rm),
                    'method': _rm,
                    'code': code,
                    'addr': addr,
                    'sig': sig,
                    '_source_file': str(f),
                })
            else:
                free_funcs.append({
                    'name': name,
                    'code': code,
                    'addr': addr,
                    'sig': sig,
                })

    return by_class, free_funcs


# ---------------------------------------------------------------------------
# S1：export 射程过滤（2026-10-09）
# ---------------------------------------------------------------------------
# 病灶层三问：
#   ①层：export 的函数遍历（纯过滤，不改语义）
#   ②消费者读哪份声明：codegen.py 读 asm/pal3/decomp/*.json
#   ③报错还缺什么：无（地址/类名是显式输入）
#
# 设计要点（对抗复核裁决，不得偏离）：
#   0. 射程 export 必须写独立目录 —— collect_methods() :829-835 从主 decomp
#      收集类的全部方法签名以生成完整头，污染则头残缺
#   1. apply 保持全量（IDB 是共享状态）
#   2. 非函数产物（ida_structs.json、_globals）保持全量
#   3. 只射程「函数反编译」这一步（148.5s 的大头）


def resolve_targets(addrs=None, class_name=None):
    """解析射程目标地址集合。

    addrs:      显式地址集合（int 或 hex str）
    class_name: 按 data/annotations/structs/<Cls>.json 的 methods 归属过滤
    二者都 None  => 返回 None（全量，向后兼容）
    二者都给     => 取交集（收窄，非并集）
    """
    import json as _json
    from pathlib import Path as _P
    if addrs is None and class_name is None:
        return None
    out = None
    if addrs is not None:
        out = {int(a, 16) if isinstance(a, str) else int(a) for a in addrs}
    if class_name is not None:
        ann = _P(__file__).resolve().parents[3] / 'data' / 'annotations' / 'structs' / ('%s.json' % class_name)
        if not ann.exists():
            raise ValueError('未找到类注解：%s' % ann)
        d = _json.loads(ann.read_text(encoding='utf-8'))
        cls_addrs = {int(k, 16) for k in (d.get('methods') or {})}
        out = cls_addrs if out is None else (out & cls_addrs)
    return out


def scoped_decomp_dir(outdir):
    """射程 export 的输出目录 —— 必须与主 asm/pal3/decomp/ 隔离。

    理由：collect_methods() 从主 decomp 收集类的全部方法签名以生成完整头；
    若射程 export 覆盖主目录，头会残缺（只剩目标那 1 个方法签名）。
    """
    from pathlib import Path as _P
    return _P(outdir) / 'decomp'
