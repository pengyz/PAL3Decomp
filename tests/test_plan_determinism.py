"""B 转换链 Task 2：归并确定性 + targetKey 分立（task-2-brief Step 1，TDD 红→绿）。

真值锚（spec §3 docs/specs/2026-11-04-converter-proof-design.md:56-60）：
- 确定性病灶：gen_plan glob 未排序 ⇒ struct 处理/同址认领胜者随文件系统序漂移
  ⇒ 同输入两次 plan 跨机不同，「可重放」不成立（Review Focus #3）。
- targetKey 病灶：plan_to_changeset 旧键 `'name:'+addr` 比 Changeset.java:313-322
  的 targetKey 粗 ⇒ 同址函数改名被全局改名互吃（Review Focus #4）。
- 归并 tie-break（对齐 apply_annotations.py:1382-1385 语义、代码独立）：
  owner(==本 struct name) 优先 > adjudication=='confirmed' > sorted 类名序 > 首个。
- 地址归一（全局约束）：切片 a[2:] if a.startswith('0x')，**禁 lstrip('0x')**
  （字符集剥离会把 '0x0abc' 吃成 'abc'——前导零陷阱）。
- 控制器裁定（T2×T7 预飞）：test_same_addr 断言改**子集**——T7 将为带 'type' 的
  define_global 增发 set_global_type，恰等断言会在 T7 后破。
"""
import glob as globmod
import json
import os

from ghidra_track.import_annotation import build_import_plan, merge_method_claims
from ghidra_track.plan_to_changeset import norm_key_addr, plan_to_changesets

_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# brief 逐字 fixture 路径（锚到仓库根，禁依赖 cwd）
_ANN = os.path.join(_ROOT, 'ghidra_track', 'fixture', 'cases',
                    'case-01-struct-union-overload', 'annotations')


def test_plan_deterministic():
    a = build_import_plan(_ANN)
    b = build_import_plan(_ANN)
    # 正锚（防空过：两次空 plan 也相等）——fixture 装载面必须真的产出 op
    assert a and any(o['kind'] == 'set_name' for o in a), 'fixture plan 非空正锚'
    assert a == b, '同输入两次 plan 必须逐字节同（glob 序/归并序确定性）'
    # 键序级逐字节（== 不比 dict 键序；json.dumps 比插入序 ⇒ 真字节同）
    assert json.dumps(a, ensure_ascii=False) == json.dumps(b, ensure_ascii=False), \
        '序列化后逐字节同（含 dict 键序）'


def test_same_addr_fn_and_global_both_kept():
    plan = [{'kind': 'set_name', 'addr': '0x401000', 'name': 'Fn'},
            {'kind': 'define_global', 'addr': '0x401000', 'name': 'g_X'}]
    ops = [o for b in plan_to_changesets(plan) for o in b['ops']]
    kinds = {o['op'] for o in ops}
    # 控制器裁定：子集断言（两 op 都保留即可，不断言恰等——T7 可能增发 set_global_type）
    assert 'rename_function' in kinds and 'rename_global' in kinds, \
        'targetKey 分立：同址两 op 都保留（现互吃）'


def test_multiclaim_tiebreak():
    # owner 优先 > confirmed > sorted 类名序（对齐 apply_annotations.py:1382-1385）
    ann = {'A_cls.json': {'name': 'Z_cls', 'methods': {'0x401000': {'name': 'fromZ'}}},
           'B_cls.json': {'name': 'A_cls', 'methods': {'0x401000': {'name': 'fromA', 'owner': 'A_cls'}}}}
    merged = merge_method_claims(ann)   # build_import_plan 内归并段抽出的可测函数
    assert merged['0x401000']['name'] == 'fromA', 'owner 优先胜出'
    ann2 = {'A.json': {'name': 'Z_cls', 'methods': {'0x401000': {'name': 'z', 'adjudication': 'confirmed'}}},
            'B.json': {'name': 'A_cls', 'methods': {'0x401000': {'name': 'a'}}}}
    assert merge_method_claims(ann2)['0x401000']['name'] == 'z', 'confirmed 优先于类名序'


def test_owner_beats_sorted_class_order():
    # brief 两测未隔离 owner 层（fromA 恰也赢类名序）——此测钉 owner 单层判别力：
    # 无 owner 时 'A_cls'<'Z_cls' 应胜；owner 挂在类名序**劣**位（Z_cls）必须翻盘
    ann = {'A.json': {'name': 'A_cls', 'methods': {'0x401000': {'name': 'a'}}},
           'Z.json': {'name': 'Z_cls', 'methods': {'0x401000': {'name': 'z', 'owner': 'Z_cls'}}}}
    assert merge_method_claims(ann)['0x401000']['name'] == 'z', 'owner 压过 sorted 类名序'


def test_merge_order_independent():
    # 纯函数确定性：ann 插入序反转 ⇒ 胜者不变（按文件名排序遍历，非依赖调用方序）
    ann = {'b.json': {'name': 'S', 'methods': {'0x401000': {'name': 'fromB'}}},
           'a.json': {'name': 'S', 'methods': {'0x401000': {'name': 'fromA'}}}}
    rev = dict(reversed(list(ann.items())))
    assert merge_method_claims(ann) == merge_method_claims(rev), \
        'merge_method_claims 必须与输入插入序无关（确定性纯函数）'
    # 全平（同类名/无 owner/无 confirmed）胜者=按文件名序首个
    assert merge_method_claims(ann)['0x401000']['name'] == 'fromA'


def test_ann_dir_glob_order_independent(tmp_path, monkeypatch):
    # 同名双 struct（'Dup'）：structs[n]=last-wins ⇒ 无 sorted(glob) 时 define_struct
    # 胜者随文件系统序翻转（size 4↔8）。sorted(glob) 后逆序 glob 仍逐字节同。
    s = tmp_path / 'structs'
    s.mkdir()
    (s / 'a_dup.json').write_text(json.dumps(
        {'name': 'Dup', 'size': 4, 'known_members': {'0': {'name': 'm_a', 'type': 'int'}},
         'methods': {'0x401000': {'name': 'fromA'}}}))
    (s / 'b_dup.json').write_text(json.dumps(
        {'name': 'Dup', 'size': 8, 'known_members': {'0': {'name': 'm_b', 'type': 'int'}},
         'methods': {'0x401008': {'name': 'fromB'}}}))
    p1 = build_import_plan(str(tmp_path))
    assert p1 and any(o['kind'] == 'define_struct' for o in p1), '正锚：define_struct 必须产出'
    real_glob = globmod.glob
    monkeypatch.setattr(globmod, 'glob',
                        lambda pat, *a, **k: list(reversed(real_glob(pat, *a, **k))))
    p2 = build_import_plan(str(tmp_path))
    assert p1 == p2, 'sorted(glob)：文件系统序不得进入 plan（逆 glob 序仍逐字节同）'


def test_norm_key_addr_slice_not_lstrip():
    # 全局约束：地址归一切片 [2:]；lstrip('0x') 把 '0x0abc' 剥成 'abc'（前导零陷阱）
    assert norm_key_addr('0x0abc') == '0abc', "禁 lstrip('0x')：'0x0abc' 不得变 'abc'"
    assert norm_key_addr('0x401000') == '401000'
    assert norm_key_addr('401000') == '401000'  # 无前缀原样
    # 行为钉：同址异写（'0x401000' vs '401000'）归一后同 key ⇒ 去重保后
    plan = [{'kind': 'set_name', 'addr': '0x401000', 'name': 'A'},
            {'kind': 'set_name', 'addr': '401000', 'name': 'B'}]
    renames = [o for b in plan_to_changesets(plan) for o in b['ops']
               if o['op'] == 'rename_function']
    assert len(renames) == 1 and renames[0]['name'] == 'B', '前缀异写同址必须归一去重'
