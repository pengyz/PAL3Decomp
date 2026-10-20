"""注解的**单一读取视图**（2026-09-20 审计 P1-5，第一批）。

# 为什么需要它

CLAUDE.md 的红线是「**codegen 不读 annotation**：codegen 只读 export 产物」，
但实测该红线在 pipeline 里已被**违反 5 文件 19+ 处**（审计报告 §2/§3）：
`emit_headers.py`（sdk_types / known_methods / template_bases / base_class / globals …）、
`ast_transform.py`、`data.py`、`collect.py`、`stage4_substitution.py`。
其中 `data.py` 自称"The ONLY place codegen reads from annotations"**已不成立**。

**本模块不改变"读不读"这个既成事实**，只做一件事：把散落的直读**收敛到一个读点**，
使"改一处字段名/路径就要动 N 处"变成"只动这里"。

# 设计原则（避免语义漂移）

* **逐处迁移、逐处验证**：每迁一处都要保证 `codegen all` 的产物**字节相同**
  （`diff -r` 验），不符即回退该处。
* 各调用点历史上对**缺字段/坏 JSON 的容错语义不同**（有的 `.get(x, {})`、有的
  `if x in entry`、有的静默 `continue`），所以本模块提供**细粒度**原语，
  由调用方保留自己的容错；**不做"统一容错"这种会改行为的合并**。
* 本模块**只做读取**，不缓存跨 run 的可变状态（除进程内惰性缓存）。
"""
import json
import os

_STRUCTS_CACHE = None
_MEMBER_NAMES_CACHE = None


def structs_dir(store=None):
    """注解 structs 目录。优先用 `store.annotations_dir`（唯一获准读注解的模块）。"""
    if store is not None and getattr(store, 'annotations_dir', None):
        return os.path.join(str(store.annotations_dir), 'structs')
    return os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
        os.path.abspath(__file__)))), 'data', 'annotations', 'structs')


def iter_struct_files(directory):
    """按文件名排序遍历 structs/*.json（排序与历史实现一致，避免产物顺序漂移）。"""
    try:
        return sorted(__import__('glob').glob(os.path.join(directory, '*.json')))
    except Exception:
        return []


SKIPPED_ANNOTATIONS = []


def load_struct(path):
    """读一个 struct JSON；坏文件返回 None（调用方可自行决定是否 continue）。

    [坏 JSON 盲区治理 2026-10-16] 坏文件**记账 + 响亮告警**（SKIPPED_ANNOTATIONS）
    ——原静默跳过是盲区（并发写半成品/控制字符会被下游静默吞掉；实测
    TaskMgr_SceneObjParam_SceneObj.json 竞态半写：check_annotations 能抓到、
    codegen 侧 iter_structs 无声跳过 ✗）。不改跳过语义（不破 codegen），但
    记账面可查（fail-visible）——`SKIPPED_ANNOTATIONS` 非空即下游应处置。
    """
    try:
        return json.loads(open(path, encoding='utf-8').read())
    except Exception as e:
        SKIPPED_ANNOTATIONS.append((path, str(e)[:120]))
        import sys
        print('[annotation_view] WARN: 坏 JSON 被跳过（记账 fail-visible）: %s -> %s'
              % (os.path.basename(path), str(e)[:80]), file=sys.stderr)
        return None


def iter_structs(directory, store=None):
    """(path, dict) 生成器，跳过坏文件 —— 与原各处的"静默 continue"语义一致。"""
    for p in iter_struct_files(directory if directory else structs_dir(store)):
        d = load_struct(p)
        if isinstance(d, dict):
            yield p, d


def member_names(directory=None, store=None):
    """所有 struct 的 `known_members[*].name` 去重集合（进程内缓存）。

    与 `stage4_substitution._load_member_names()` 的**原逻辑逐字等价**：
    只看 `known_members` 的值里 `isinstance(dict) and m.get('name')`。
    """
    global _MEMBER_NAMES_CACHE
    if _MEMBER_NAMES_CACHE is None:
        names = set()
        for _p, d in iter_structs(directory, store):
            for m in (d.get('known_members') or {}).values():
                if isinstance(m, dict) and m.get('name'):
                    names.add(m['name'])
        _MEMBER_NAMES_CACHE = names
    return _MEMBER_NAMES_CACHE



def annotation_json_path(name, store=None):
    """`data/annotations/<name>` 的路径（顶层注解 JSON，如 sdk_types/globals/functions）。

    提供给调用方"**自己做 exists 与读取**"的场合 —— 有些调用点对异常的捕获是**精确**
    的（例如只捕 `OSError/JSONDecodeError/TypeError`），用 `load_annotation_json`
    （宽捕获 + 返回 None）会**改变语义**；这类调用点应改用本函数取路径，保留原读取与容错。
    """
    return os.path.join(os.path.dirname(structs_dir(store)), name)


_ANNOTATION_JSON_CACHE = {}


def load_annotation_json(name, store=None):
    """读 `data/annotations/<name>`（如 `skip_functions.json` / `functions.json` /
    `globals.json`）。坏文件返回 None —— 与历史各处的容错一致。

    这是"**顶层注解 JSON**"的单一读点（structs/*.json 走 `iter_structs`）。
    """
    if name not in _ANNOTATION_JSON_CACHE:
        base = structs_dir(store)
        path = os.path.join(os.path.dirname(base), name)
        try:
            _ANNOTATION_JSON_CACHE[name] = json.loads(open(path, encoding='utf-8').read())
        except Exception as e:
            # [坏 JSON 盲区治理 2026-10-16] 同 load_struct：记账 + 响亮告警
            SKIPPED_ANNOTATIONS.append((path, str(e)[:120]))
            import sys
            print('[annotation_view] WARN: 坏 JSON 被跳过（记账 fail-visible）: %s -> %s'
                  % (name, str(e)[:80]), file=sys.stderr)
            _ANNOTATION_JSON_CACHE[name] = None
    return _ANNOTATION_JSON_CACHE[name]


def skip_functions(store=None):
    """`skip_functions.json` 的内容（dict）；不可读返回 `{}`（与调用方原语义一致）。"""
    d = load_annotation_json('skip_functions.json', store=store)
    return d if isinstance(d, dict) else {}



def struct_path(cls_name, store=None):
    """`structs/<cls_name>.json` 的路径。"""
    return os.path.join(structs_dir(store), '%s.json' % cls_name)


def struct_by_class(cls_name, store=None):
    """按类名读一个 struct JSON。

    **语义**：与各处原写法 `if path.exists(): json.loads(path.read_text(encoding='utf-8'))`
    一致 —— 内部完成 `exists` 守卫（**缺失返回 None**），**不捕获异常**（损坏时抛出，
    由调用方自己的 `try` 决定是否容错）。故调用方应保留原有的 `try`/`if` 结构。
    """
    path = struct_path(cls_name, store=store)
    if not os.path.exists(path):
        return None
    return json.loads(open(path, encoding='utf-8').read())


_TEMPLATE_BASES_CACHE = None


def template_bases():
    """`data/annotations/template_bases.json`（进程内缓存）。

    **语义与三处原读取一致：不捕获异常** —— 文件缺失或损坏时**同样抛出**
    （原代码是 `if exists: with open: json.load`，没有 try 包裹）。
    这也意味着调用方仍需自行决定是否容错（本模块不替它们做决定）。
    注意：与原代码一致，这里**不指定 encoding**（保持逐字行为）。
    """
    global _TEMPLATE_BASES_CACHE
    if _TEMPLATE_BASES_CACHE is None:
        path = os.path.join(os.path.dirname(structs_dir()), 'template_bases.json')
        with open(path) as _f:
            _TEMPLATE_BASES_CACHE = json.load(_f)
    return _TEMPLATE_BASES_CACHE


def template_bases_path():
    """`template_bases.json` 的路径（供调用方先做 exists 判断，保持原有守卫语义）。"""
    return os.path.join(os.path.dirname(structs_dir()), 'template_bases.json')


def reset_caches():
    """测试用：清空进程内缓存。"""
    global _STRUCTS_CACHE, _MEMBER_NAMES_CACHE
    _STRUCTS_CACHE = None
    _MEMBER_NAMES_CACHE = None
    _ANNOTATION_JSON_CACHE.clear()
    global _TEMPLATE_BASES_CACHE
    _TEMPLATE_BASES_CACHE = None


def base_names(info):
    """基类名列表 —— **唯一真相源读点**（读 `bases`，不读已废弃的 `base_class`）。

    [真相源迁移 2026-10-20] `base_class`（早期单继承·纯名字）与 `bases`
    （后期 MI 专项·{name,offset}）两字段**名字信息完全冗余**（15/15 重叠一致），
    `bases` 是超集（含 MI 偏移）⇒ 统一到 `bases`，`base_class` 已删除。

    消费方一律经本函数取基类名，禁止直读字段（防双副本分叉复发）。
    """
    if not isinstance(info, dict):
        return []
    bs = info.get('bases')
    out = []
    if isinstance(bs, list):
        for x in bs:
            if isinstance(x, dict):
                n = x.get('name')
                if n:
                    out.append(str(n))
            elif x:
                out.append(str(x))
    return out

def base_entries(info):
    """基类（含 MI 偏移）—— 需要偏移的场景用这个。"""
    if not isinstance(info, dict):
        return []
    bs = info.get('bases')
    return [x for x in bs if isinstance(x, dict) and x.get('name')] if isinstance(bs, list) else []
