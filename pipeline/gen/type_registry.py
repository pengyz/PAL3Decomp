"""TypeRegistry —— 类型单一真值注册表 [P3a 2026-11-24·用户批准端到端重设计]。

设计公理 (docs/template_enum_redesign_plan_20261124.md §0):
  真相唯一: 每个类型名恰好一个权威声明通道, 注解层显式登记, 管线其余层只消费。
  注解层=唯一真相: 枚举值/形式(平铺|嵌套)/别名全读注解 json; IDB 只为 hexrays;
  IDB 与注解分歧 = 对账留痕而非静默取边。
  输出集先知: 产物文件集合在写第一个文件前由 registry 推导 → include 解析
  纯内存(TYPE_HEADER_MAP), 清理=manifest 差集, 无运行间顺序依赖。

四个消费面:
  面1 头生成: standalone enum 头(平铺)/类内嵌套 enum(嵌套)/别名
  面2 对账:   registry vs IDB _enums 分歧清单(只报不改真相)
  面3 include 接线: TYPE_HEADER_MAP 纯内存(枚举恒 include——VC6 无 enum fwd)
  面4 清理:   本次产物全集之差 = 删除清单(manifest)

条目形: {name(注解键原样), values{member:int}, form: flat|nested, owner_cls,
         source: annotation|gbengine, header_path}
"""

import json
import os
import re

_CLASS_DECL_RE = re.compile(r'^(?:class|struct|enum)\s+(\w+)')
_EXPORT_MACROS = ('GBAPI', 'DLLAPI', 'DLLEXPORT', 'DECLSPEC', 'EXPORT', 'API')


def _decl_name(line):
    """`line` 声明的类型名; 容忍 __declspec 与导出宏前缀。"""
    s = re.sub(r'__declspec\s*\([^)]*\)\s*', '', line)
    for mac in _EXPORT_MACROS:
        s = re.sub(r'^(class|struct|enum)\s+%s\s+' % mac, r'\1 ', s)
    m = _CLASS_DECL_RE.match(s)
    return m.group(1) if m else None


def _enum_decl_name(line):
    m = re.match(r'enum(?:\s+class)?\s+(\w+)', line)
    return m.group(1) if m else None


def _parse_int(v):
    """注解值解析(保号): '0x10'/'-1'/'2'/int 全收; 失败原样返回(对账面显形)。"""
    if isinstance(v, int):
        return v
    try:
        return int(str(v), 0)
    except Exception:
        return v


class TypeRegistry(object):
    def __init__(self):
        # name -> entry {values, form, owner_cls, source, header_path}
        self.enums = {}
        # 别名表(type_aliases.json, 显式别名唯一通道)
        self.aliases = {}
        # gbengine 域: 类/枚举名 -> include 相对路径('gbengine/X.h')
        self.gbengine_types = {}
        # [external 域 2026-11-24·用户批准② 对抗复核v2] 平台/工具链提供型:
        #   name -> {'provided_by', 'kind': typedef|class|macro|enum}
        #   语义="该名已由某外部头提供"(fwd 抑制/include 提供方头), 与
        #   system_names 的"排除"语义轴不同。
        self.external = {}
        # IDB _enums 有而 registry 无(渲染期硬报警 adjudication-required)
        self.adjudication_required = set()
        # 大小写 FS 碰撞(UIEMOTE/UIEmote 族)——注册表构建期一次裁决的输入
        self.case_collisions = {}
        # 顶层类根(头产物名) -> 相对 OUTPUT_DIR 头路径('Misc/X.h')
        self.class_headers = {}

    # ---------- 构建 ----------
    @classmethod
    def build(cls, project_root, ida_enums=None, class_roots=None):
        """project_root: Path/str; ida_enums: ida_structs.json '_enums' dict(可空);
        class_roots: 顶层类名集合(emit 侧 scope_tree.roots, 可空)。"""
        reg = cls()
        root = str(project_root)
        ann_dir = os.path.join(root, 'data', 'annotations')

        # 1. 注解枚举 = 唯一真相(键名原样)
        try:
            with open(os.path.join(ann_dir, 'enums.json'), encoding='utf-8') as f:
                raw = json.load(f)
        except Exception:
            raw = {}
        for name, einfo in raw.items():
            # 元数据键(_doc 等)=非 dict 值; 游戏枚举名可合法以下划线起首
            # (_BGM/_BIGMAP_ELEMENT/_FLIP 实证)——键名原样律, 不按首字符猜。
            if not isinstance(einfo, dict):
                continue
            values = {m: _parse_int(v)
                      for m, v in (einfo.get('values') or {}).items()}
            form = 'nested' if '::' in name else 'flat'
            owner = name.rsplit('::', 1)[0] if form == 'nested' else None
            short = name.rsplit('::', 1)[-1]
            reg.enums[name] = {
                'name': name, 'values': values, 'form': form,
                'owner_cls': owner, 'short_name': short,
                'source': 'annotation', 'header_path': None,
            }
        # 嵌套枚举的值表可同时随类标注(structs/<Cls>.json nested_types)——
        # 键形同源(enums.json 嵌套键), 结构 json 只是消费视图, 不另立真相。

        # 2. 别名表(显式别名唯一通道; 枚举名禁入由 N16 门强制)
        try:
            with open(os.path.join(ann_dir, 'type_aliases.json'), encoding='utf-8') as f:
                reg.aliases = {k: v for k, v in
                               (json.load(f).get('aliases') or {}).items()
                               if not k.startswith('_')}
        except Exception:
            reg.aliases = {}

        # 3. gbengine 域(外部项目头, 只扫描不生成)
        gb_dir = os.path.join(root, 'include', 'gbengine')
        if os.path.isdir(gb_dir):
            for fn in sorted(os.listdir(gb_dir)):
                if not fn.endswith('.h'):
                    continue
                rel = 'gbengine/%s' % fn
                try:
                    with open(os.path.join(gb_dir, fn), encoding='utf-8',
                              errors='replace') as f:
                        for line in f:
                            n = _decl_name(line)
                            if not n:
                                continue
                            prev = reg.gbengine_types.get(n)
                            is_def = ('{' in line or ':' in line)
                            if prev is None or is_def:
                                reg.gbengine_types[n] = rel
                except Exception:
                    pass

        # 3.4 [类属枚举数据家 2026-11-24·用户裁定] 嵌套(类属)枚举唯一数据家 =
        #   类 json nested_types(kind=enum, 定义跟着类走, 生成的 h 与类一体,
        #   不单独发头)。enums.json 只承载全局平铺枚举(通用枚举)。
        #   gbengine 属主类 → header_path 指外部头(不产 pal3 侧头)。
        try:
            import glob as _g2
            for _sp in sorted(_g2.glob(os.path.join(ann_dir, 'structs', '*.json'))):
                try:
                    with open(_sp, encoding='utf-8') as f:
                        _sd = json.load(f)
                except Exception:
                    continue
                _owner = _sd.get('name') or os.path.basename(_sp)[:-5]
                for _short, _nt in (_sd.get('nested_types') or {}).items():
                    if not isinstance(_nt, dict) or _nt.get('kind') != 'enum':
                        continue
                    _vals = {m: _parse_int(v)
                             for m, v in (_nt.get('values') or {}).items()}
                    if not _vals:
                        continue
                    _full = '%s::%s' % (_owner, _short)
                    # 类 json = 类属枚举权威家: 覆盖同键(enums.json 残留/迁移期双源)
                    reg.enums[_full] = {
                        'name': _full, 'values': _vals, 'form': 'nested',
                        'owner_cls': _owner, 'short_name': _short,
                        'source': 'annotation-struct', 'header_path': None,
                    }
        except Exception:
            pass

        # 3.5 [external 域 2026-11-24·用户批准②] 平台提供型两个数据源:
        #   a) sdk_types.json 带 provided_by 的条目(对抗复核v2 迁册, 99 条)
        #   b) prelude(include/pal3/ida_types.h)typedef 行扫描(gbengine 同款
        #      自动建档——uchar/unchar/uint/_BYTE/_WORD/_DWORD/_QWORD 手工词表
        #      与别名表脱节教训: class uchar; C2371×8 实证)
        try:
            with open(os.path.join(ann_dir, 'sdk_types.json'), encoding='utf-8') as f:
                _sdk = json.load(f)
            for e in _sdk:
                if (isinstance(e, dict) and e.get('provided_by')
                        and isinstance(e.get('name'), str)):
                    reg.external[e['name']] = {
                        'provided_by': e['provided_by'],
                        'kind': e.get('kind') or 'typedef',
                    }
        except Exception:
            pass
        prelude = os.path.join(root, 'include', 'pal3', 'ida_types.h')
        if os.path.exists(prelude):
            _td_re = re.compile(r'^typedef\s+(?:unsigned\s+|signed\s+)?\w[\w\s]*?\**\s+(\w+)\s*;')
            with open(prelude, encoding='utf-8', errors='replace') as f:
                for line in f:
                    m = _td_re.match(line.strip())
                    if m:
                        reg.external.setdefault(m.group(1), {
                            'provided_by': 'pal3/ida_types.h', 'kind': 'typedef'})

        # 4. 头路径推导(TYPE_HEADER_MAP 面)
        #    平铺枚举 -> get_class_dir(name)/name.h; 嵌套枚举 -> 容器类头;
        #    类根 -> 同平铺式。lazy import 防环(emit_headers import 本模块)。
        from pipeline.gen.stages.collect import get_class_dir
        for name, e in reg.enums.items():
            if e['form'] == 'flat':
                e['header_path'] = '%s/%s.h' % (get_class_dir(name), name)
            else:
                # [类属枚举] gbengine 属主类 → 外部头(无 pal3 侧头); 其余随类头
                if e['owner_cls'] in reg.gbengine_types:
                    e['header_path'] = reg.gbengine_types[e['owner_cls']]
                else:
                    e['header_path'] = '%s/%s.h' % (get_class_dir(e['owner_cls']),
                                                    e['owner_cls'])
        for cls in (class_roots or ()):
            reg.class_headers[cls] = '%s/%s.h' % (get_class_dir(cls), cls)

        # 5. IDB 对账(面2, 只报不改): IDB _enums 中 registry 解析不了的名
        #    (= 注解无且非 gbengine) → adjudication_required, 渲染期硬报警。
        if ida_enums:
            known = set(reg.enums.keys())
            known |= {e['short_name'] for e in reg.enums.values()}
            known |= set(reg.gbengine_types.keys())
            for idb_name in ida_enums:
                if idb_name.startswith('_'):
                    continue
                short = idb_name.rsplit('::', 1)[-1]
                if idb_name not in known and short not in known:
                    reg.adjudication_required.add(idb_name)

        # 6. 大小写 FS 碰撞(R-7): 全发射名 casefold 分组, 同盘名一次呈报
        all_names = [e['name'] if e['form'] == 'flat' else e['short_name']
                     for e in reg.enums.values()]
        all_names += list((class_roots or ()))
        groups = {}
        for n in all_names:
            groups.setdefault(n.lower(), set()).add(n)
        for low, names in groups.items():
            if len(names) > 1:
                reg.case_collisions[low] = sorted(names)
        return reg

    # ---------- 查询 ----------
    def enum_entry(self, type_name):
        """按类型名查枚举条目: 全名(平铺/嵌套)或嵌套短名。"""
        e = self.enums.get(type_name)
        if e:
            return e
        if '::' in type_name:
            short = type_name.rsplit('::', 1)[-1]
            return self.enums.get(short) or self.by_short(short)
        return self.by_short(type_name)

    def by_short(self, short):
        for e in self.enums.values():
            if e['short_name'] == short:
                return e
        return None

    def is_enum(self, type_name):
        return self.enum_entry(type_name) is not None

    def is_gbengine(self, type_name):
        return type_name in self.gbengine_types

    def is_alias(self, type_name):
        return type_name in self.aliases

    def is_external(self, type_name):
        """平台/工具链提供型(external 域)。"""
        return type_name in self.external

    def external_kind(self, type_name):
        e = self.external.get(type_name)
        return e['kind'] if e else None

    def resolve(self, type_name):
        """[五域单点解析 2026-11-24·对抗复核v2] 类型名 → 声明通道。
        返回 (domain, info): domain ∈ enum|alias|gbengine|external|class|None。
        所有 include/fwd/参数候选统一过此单点——解析失败=裁决队列(fail-loud),
        禁止静默 class 前置(静默降级公理)。"""
        if self.is_enum(type_name):
            return ('enum', self.enum_entry(type_name))
        if type_name in self.aliases:
            return ('alias', self.aliases[type_name])
        if type_name in self.gbengine_types:
            return ('gbengine', {'header': self.gbengine_types[type_name]})
        if type_name in self.external:
            return ('external', self.external[type_name])
        if type_name in self.class_headers:
            return ('class', {'header': self.class_headers[type_name]})
        return (None, None)

    def header_for(self, type_name):
        """TYPE_HEADER_MAP(面3): 类型名 → '#include' 相对路径(pal3/src 基准)。
        枚举恒 include(VC6 无 enum fwd); gbengine → 'gbengine/X.h';
        生成类 → 'Misc/X.h' 式; 嵌套枚举 → 容器头;
        external 且 provided_by 非系统头 → 提供方头(<d3dx9.h> 形)。
        prelude 契约头(windows.h/stdio.h/pal3/ida_types.h/scalar_typedefs.h)
        已被每个生成头引用 → 返回 None(调用方抑制 include/fwd)。未知返回 None。"""
        e = self.enum_entry(type_name)
        if e:
            return e['header_path']
        if type_name in self.gbengine_types:
            return self.gbengine_types[type_name]
        if type_name in self.class_headers:
            return self.class_headers[type_name]
        ext = self.external.get(type_name)
        if ext:
            pb = ext.get('provided_by') or ''
            if pb in ('windows.h', 'stdio.h', 'pal3/ida_types.h', 'scalar_typedefs.h',
                      'pal3/globals.h'):
                return None   # prelude 契约: 恒可见, 抑制
            return '<%s>' % pb   # 系统头: 条件 include 形
        return None

    def flat_enum_names(self):
        return {n for n, e in self.enums.items() if e['form'] == 'flat'}
