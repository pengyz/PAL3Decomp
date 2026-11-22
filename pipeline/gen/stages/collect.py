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
# [SKIP_CLASSES 常量+gbengine 头自动侦测 退役 20261122] 类级域排除迁移至
# data/annotations/domain_exclude.json(数据层单一真值源, 带 provenance/定谳状态)。
# 退役根因: ①常量=代码内遗留数据(层错位) ②头文件存在性推导域归属被 CPK 案证伪
# (头在 include/gbengine/ 但实现全在 PAL3 .text——头共享实现本地, 自动侦测过判
#  ⇒CPK 全类方法从未发射)。注解优先(structs 注册类不可入排除表)为本表不变式。

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
    """Build the full skip set from the data layer (collect 只管收集, 域裁决全在数据层).

    [第一性复裁 2026-11-22 用户质询] 本函数只机械读 domain_exclude.json——
    原此处的「注解 methods ⇒ discard 排除」覆盖规则(CPK 案 20261122 加)是
    管线层决策=层错位, 已撤。域归属冲突的正解在数据层改裁决条目, 不在管线
    加启发式。structs 注解与域排除正交: CRT/工具链类可以有注解 methods
    (供参考/匹配), 不改变域归属。
    """
    skip = set()
    _dex_p = (Path(__file__).parent.parent.parent.parent
              / 'data' / 'annotations' / 'domain_exclude.json')
    if _dex_p.exists():
        try:
            _dex = json.loads(_dex_p.read_text(encoding='utf-8'))
            skip.update((_dex.get('classes') or {}).keys())
        except Exception as _e:
            print('  [collect-DOMAIN-ERR] domain_exclude.json 读取失败: %s' % str(_e)[:60])

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
    # [D2 计数可见 20261121] 静默丢弃改显式计数(5a7a3b86 静默吞教训同族)
    _census = {'empty': 0, 'sub_': 0, 'dtor_reject_no_identity': 0,
               'dtor_emit': 0, 'dtor_reject_intent': 0}

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
            _census['empty'] += 1
            continue
        if name.startswith('sub_'):
            _census['sub_'] += 1
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
            elif inner.startswith('?_G'):
                # [??_G 路由 20261121] scalar deleting dtor 的 MSVC mangle 形——
                # 原走通用 @-切分误路由为自由函数('?_GCls' 非法标识符垃圾发射)。
                # 路由进类 dtor 家族, 归一形与 backtick 单元同路径;
                # 发射决策在 D10 意图路由点统一仲裁(下文 dtor 形路由)。
                _c = inner[3:].split('@')[0]
                if _c:
                    cls = _c
                    method = '_scalar_dtor'
                    code = re.sub(r'\?\?_G%s@@[^\n(]*' % re.escape(_c),
                                  '%s::_scalar_dtor' % _c, code, count=1)
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
                # [字面替换修复 20261121] 原 \b...\b 对反引号引导名永不命中
                #   (` 为非词字符, '::`' 处无词边界)——重写从未发生; 旧无恙因单元
                #   总被泛化跳过, S3 撕除跳过后暴露(UIProgressBar 无签名行案)。
                #   字面替换: dtor 名唯一性足够, 无需词边界。
                code = code.replace(method, _norm)
                method = _norm

        if cls and method:
            if cls in skip_classes:
                continue

            # [D1 dtor 形路由 20261121] backtick 归一形/??_G 路由形/_sdtor_NN——
            # 旧「编译器包装泛化跳过」理论过滤已退役(层错位, 用户第一性质询裁定;
            # 12/12 字节证据证伪), 发射决策移交 dtor_intent 单点(见下)。
            # [判据扩面 20261122] 条件从"名形"改"注解身份"——UIWnd 0x445B20 案:
            #   decomp 名 `_UIWnd_0`(??_G/ICF 归一形)不被名形条件命中, P-A5 按注解
            #   名翻成 ~UIWnd 走通用路径发射 ⇒ 与完全形双定义(C2084 ×12, 11-21 晚波
            #   欠债——shadow 移除后全量回归门 13h 未跑, 本 loop 首拦)。判据公共函数
            #   should_route_dtor: 名形兼容 + 注解 flags dtor / ~名 身份路径。
            try:
                try:
                    import annotation_view as _av_di
                except ImportError:
                    from pipeline.gen import annotation_view as _av_di
                _sp = _av_di.struct_by_class(cls, store=store) if cls else None
                _mdi = (_sp.get('methods', {}) or {}) if _sp else {}
                _e = _mdi.get(addr)
                if _e is None:
                    _au = str(addr).upper().replace('0X', '0x')
                    for _k, _v in _mdi.items():
                        if str(_k).upper() == _au:
                            _e = _v
                            break
            except Exception as _e_di:
                # 决策器故障 = fail-loud(静默回退=旧理论过滤复辟)
                print("  [collect-D1-ERR] %s %s: %s" % (cls, addr, _e_di))
                continue
            from pipeline.gen.dtor_intent import should_route_dtor as _srd
            if _srd(method, _e):
                # [D1 泛化跳过退役→意图路由 20261121] "编译器包装无源体"理论过滤
                # 层错位退役(用户第一性质询裁定; 12/12 字节证据证伪该理论)。
                # 发射决策移交 dtor_intent 单点:
                #   有注解身份 → intent.body_emit 仲裁(唯一源律/decl_only/suppressed)
                #   无注解身份 → 显式拒发+计数(无身份=无可发射, 非理论过滤)
                # 命中本分支的单元: backtick 归一形 / ??_G mangle 路由形 / _sdtor_NN
                #   / 注解 dtor 身份(名形外归一形 _UIWnd_0 等)。
                try:
                    if _e is not None:
                        from pipeline.gen.dtor_intent import resolve_dtor_intent as _rdi
                        _sib = [{'addr': _ka, 'entry': _kv,
                                 'unit_present': True}
                                for _ka, _kv in _mdi.items()
                                if _ka != addr and
                                ('dtor' in (_kv.get('flags') or []) or
                                 str(_kv.get('name') or '').startswith('~'))]
                        _it = _rdi(cls=cls, entry_addr=addr, entry=_e,
                                   siblings=_sib, unit_present=True,
                                   unit_vintage='named', flags_channel=None,
                                   header_facts_scalar=False, s4_symbols=None)
                        if _it.body_emit:
                            _census['dtor_emit'] += 1
                            # 发射: 名规范化交 P-A5(注解名=唯一真值), N18 源级化
                            # 由 emit_cpp ctx.flags 通道驱动(不在此重写签名)
                        else:
                            _census['dtor_reject_intent'] += 1
                            continue   # 拒发: 体不发射(声明由头路径供给)
                    else:
                        _census['dtor_reject_no_identity'] += 1
                        continue   # 拒发: 无注解身份(D12 自由 dtor 分类排队)
                except Exception as _e_di:
                    # 决策器故障 = fail-loud(静默回退=旧理论过滤复辟)
                    print("  [collect-D1-ERR] %s %s: %s" % (cls, addr, _e_di))
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

            _decl_only5 = False
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
                # [正名对齐 2026-11-15] 注解名存在即覆盖(注解=唯一真值, G1b根因:
                # 旧条件仅thunk类条目吃注解名 → 正名条目的cpp定义名残留decomp旧名 → 头体漂移C2039/C2673)
                # ⚠️ 安全权衡记录: 注解名错时由此前"编译失败暴露"变为"静默传播"——
                #    对冲 = check_annotations 名漂移检查(W2 warn 可见) + 正名条目均有 evidence 记录
                # [declaration_only 尊重 2026-11-15] 注解声明收编条目(体借用/ICF折叠垃圾):
                # Hex-Rays 对非起点地址渲染出借用体(实证: 0x4C2640系4文件 len=1236 全同,
                # 而二进制 4 址体互异) ⇒ cpp 不发射定义体, 头声明由 emit 常规产出
                _decl_only5 = isinstance(_anm5, dict) and _anm5.get('declaration_only')
                if _an5 and _an5 != method:
                    # 体文本定义行同步改名(stage1 重建按 ctx.method 搜定义行——
                    # 不同步则搜不到 → 保留旧名 → C2084 复活)
                    code = code.replace('%s::%s(' % (cls, method), '%s::%s(' % (cls, _an5), 1)
                    # [dtor行replace修复 2026-11-18] 原文'%s::%~%s('把%~当格式符
                    #   →ValueError→except吞→method覆盖从未执行(P-A5全死, HideAll_1
                    #   等全部注解正名失效C2039/C2673族根因)。%%转义+正则防注入:
                    code = code.replace('%s::%%~%s(' % (cls, method), '%s::%%~%s(' % (cls, _an5), 1)
                    method = _an5
            except Exception:
                pass
            by_class[cls].append({
                'name': '%s::%s' % (cls, method),
                'method': method,
                'code': '' if _decl_only5 else code,
                'addr': addr,
                'sig': sig,
                '_declaration_only': bool(_decl_only5),
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

    if any(_census.values()):
        print('  [collect-census] 空/无名=%d sub_=%d | dtor形: 发射=%d 拒发(意图)=%d '
              '拒发(无身份)=%d' % (
                  _census['empty'], _census['sub_'], _census['dtor_emit'],
                  _census['dtor_reject_intent'], _census['dtor_reject_no_identity']))
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
