#!/usr/bin/env python3
"""vtable **声明校验（棘轮制）**—— codegen 时关卡：校验 C++ `virtual` 声明与二进制 vtable 一致。

本模块**不写真相源**（只读 `data/annotations/**` + 生成头 + Task 3 旁路），只产出判定与棘轮指标。
门禁是**棘轮**（health 只升不降），**不是硬门禁** —— v1/v2 两次死锁证明硬门禁此路不通。

## 校验三类项（按 view 对，MI 多表各自校验）

  1. **槽数数**：`声明数量 == vtables[].slots 数量`
  2. **槽序**：用 Task 1（`vtable_slot_order`）**正向规则**从声明生成预期槽序，逐槽对比
  3. **签名**：Task 3（`vtable_sig_infer`）`methods_pending` 候选 vs 声明（**等价类**维度）

## 棘轮制门禁（核心）

```
vtable_health[class] = 已验证槽数 / 总槽数
  health 下降 ⇒ 阻塞（回归检测）· 不变 ⇒ 放行 · 上升 ⇒ 放行 + 更新基线
```

本模块把"已验证"拆成**三个各自单调**的分量（单一标量会让棘轮留洞：例如"多声明一个
虚函数"不改槽序 ⇒ 单一 slot_health 察觉不到）：

| 分量 | 定义 | 防的倒退 |
|---|---|---|
| `slot_health` | 槽序命中（含别名槽）/ 总槽数 | 槽序错位、槽位无声明 |
| `count_health` | 命中声明数 / (声明数 + 无地址声明数 + 未覆盖槽数) | 多声明、少声明、`virtual ~C() {}` 这类不可定位声明 |
| `sig_health` | 签名无矛盾 / 有签名证据 | 声明与二进制序言/调用序列矛盾 |

外加**第 4 类：验证面规模**（`_SURFACE_METRICS` = `slots` = 该类的二进制槽数）。
**只比比值会奖励"缩小分母"**：删掉一个未声明槽 ⇒ `slot_health 0.5 → 1.0` ⇒ 旧实现判
`improved` 并回写基线；同时删声明与其槽（`slots_total 3 → 1`）⇒ 三个比值全 `same` ⇒ 放行。
基线一旦被写成 1.0，**把缺失证据补回来**（完备性修复）反而让 `slot_health` 下降 ⇒ BLOCKED
⇒ 门禁拦住**正确的修复**。⇒ 规模本身必须单调不降（`_SURFACE_METRICS`），与"整类消失 =
`missing` ⇒ 阻塞"同一语义：**验证面不得缩小**。

⚠️ **R=2 降级**：`count_denom`（声明数 = `声明数 + 无地址声明数 + 未覆盖槽数`）**不入**
`_SURFACE_METRICS` —— 它合法地随**声明清理**变化（删冗余/错误的 `virtual ~C() {}`
注入虚析构时，本工具自己判 `count_ok False→True`、`count_health 0.5→1.0`），把它当
验证面会**拦住正确的清理**（过严路径）。Q1 两洞由 `slots` **单分量**封死：删未声明槽
⇒ `slots 2 → 1 down`；删声明+槽 3→1 ⇒ `slots 3 → 1 down`。

`slot_health` 就是规格里的 `vtable_health`；任一分量**下降**即阻塞（`ratchet_decide`），
阻塞优先于 `improved`（被阻塞的运行不得同时报"改善"）。
**没有任何阈值参数**（v2 规格曾把不等号写反："未解析 < 阈值 ⇒ 阻塞"，导致 0 未解析反而阻塞 ✗）。

`None` 的处理是**方向性**的：基线未测 → 当前有值 = 新证据（`unmeasured`，不阻塞）；
基线**有值** → 当前 `None` = **证据源丢失**（`down`，阻塞；例如漏传 `--pending` 会让整个
签名维度悄悄消失）。

## 证据独立性（Ruling 5）

校验基准是**编译产物链**，不是同源自比：

  * 声明侧 = **codegen 生成头**（`virtual ...; // 0xADDR`），即编译器的输入
  * 基线侧 = `vtables[].slots`（IDB 从 `.rdata` 直接读出的二进制表）
  * 签名侧 = Task 3 的 `methods_pending`（只来自**原始指令字节**）

本模块**从不读 `methods` 表**（同源自比的入口）；有静态守卫测试钉死这一点。

## 控制器裁定（Ruling 1–5）的实现口径

| Ruling | 实现 |
|---|---|
| 1 | 棘轮接受 **B/C 带证据**：只要被判定的维度无矛盾即 `SIG_OK`；不要求 A 级 |
| 2 | `signature_verdict` 读 `features`：`sret_ambiguous`（判不出）豁免 return/arity/params；`hidden_param_suspicion`（隐藏参数嫌疑）只把 arity 放宽为下界 —— 两者 `waived` 不同 |
| 3 | 所有地址键经 `norm_addr_key()` 归一小写（真实注解 3398 个 methods 键里 32 个是小写） |
| 4 | kind 一律经 Task 2 `normalize_kind` / `slot_order_kind` 适配（Task 1 `'func'` vs Task 2 `'fn'`） |
| 5 | 基准独立于 methods 表（见上）；`struct_to_views` 只读 `vtables` |

## 两种顺序模型（默认 `flat`；实测数据决定）

| 模型 | 预期槽序来源 | 真实数据实测（78 类 / 841 槽） | 用途 |
|---|---|---|---|
| `flat`（默认） | `compute_slot_order([], 本类声明)` —— codegen 发射器把**整张表**（含继承槽）都写进本类头，故声明表即完整槽表 | `slot_health 0.589` · 全对类 45 · 全错类 10 | 逐槽校验主表（**当前唯一可用的口径**） |
| `chain` | `compute_class_views(hierarchy, cls)` —— 基链合成多视图（MI 多表各自校验） | `slot_health 0.306` · 全对类 18 | MI 逐视图校验（合成夹具已验证；真实数据受下述缺口限制） |

`chain` 在真实数据上偏低的**原因已定位**（属发现项，非本模块缺陷）：发射器给补位槽起的名字
按**本表**槽下标（`slot_N`），基类同名槽的 `slot_N` 与之不同 ⇒ Task 1 的 `match_key` 认不出
"同一槽的继承"，把继承段当新增段重复计数。⇒ 修好发射器补位命名（或按地址回填）后
`chain` 才应成为默认；**切换模型会让分量不可比**，故棘轮对模型切换显式返回
`comparison='model_changed'`（不假装放行、也不误报阻塞）。

## 用法

```sh
python3 tools/vtable_decl_check.py --decls pal3/src --structs data/annotations/structs \
    --pending /tmp/methods_pending.json --baseline data/status/vtable_decl_health.json
```

退出码：`0` 放行 · `1` 棘轮阻塞（health 下降 / 验证面缩小）· `2` 输入/写入错误与用法错误。

`--write-baseline` 是**显式**开关（规格语义"上升 ⇒ 更新基线"由 `ratchet_decide().updated`
提供）：本仓常有多个实现者并行，默认不落盘以免争用同一基线文件。
⚠️ `--write-baseline` **必须**与 `--baseline` 同时给出（否则基线永不落盘 ⇒ 无基线可比 ⇒
`decision is None` ⇒ 一切运行恒 exit 0 = 门禁永久静默关闭）；缺一则 **rc=2**。
⚠️ `--json` / `--baseline` 的**目标目录**不存在时报 **rc=2**，不得以 exit 1（= 棘轮阻塞的
同信号）退场。
"""
import argparse
import json
import re
import sys
from dataclasses import dataclass, field
from datetime import date
from pathlib import Path

_HERE = Path(__file__).resolve().parent
if str(_HERE) not in sys.path:
    sys.path.insert(0, str(_HERE))
_ROOT = _HERE.parent

# ---- Task 1：槽序正向规则（编译器实测规则的可执行形式） ----
from vtable_slot_order import (  # noqa: E402
    KIND_FUNC,
    VirtualDecl,
    compute_class_views,
    compute_slot_order,
    match_key,
)

# ---- Task 2：词表适配器（Ruling 4：'fn' ↔ 'func' 必须经适配器） ----
from vtable_slot_classifier import (  # noqa: E402
    KIND_ADJUSTOR_STATIC,
    KIND_ADJUSTOR_VBASE,
    KIND_COMPOSITE,
    KIND_DELETING_DTOR,
    KIND_FN,
    KIND_PURECALL,
    normalize_kind,
    slot_order_kind,
)

# ---- Task 3：候选签名词表（分级 / 特征 / 等价类 / 返回宽度） ----
from vtable_sig_infer import (  # noqa: E402
    CC_CDECL,
    CC_FASTCALL,
    CC_STDCALL,
    CC_THISCALL,
    CC_UNKNOWN,
    CLASS_BOOL,
    CLASS_F32,
    CLASS_F64,
    CLASS_I16,
    CLASS_I32,
    CLASS_I64,
    CLASS_I8,
    CLASS_PTR,
    CLASS_STRUCT,
    FEATURE_CC_FROM_MANGLING,
    FEATURE_HIDDEN_PARAM_SUSPICION,
    FEATURE_SRET,
    FEATURE_SRET_AMBIGUOUS,
    FEATURE_THIS_ON_STACK,
    GRADE_A,
    GRADE_B,
    GRADE_C,
    RET_BOOL,
    RET_F32,
    RET_F64,
    RET_I16,
    RET_I32,
    RET_I64,
    RET_I8,
    RET_SRET,
    RET_UNKNOWN,
    RET_VOID,
    param_class_equiv,
)

__all__ = [
    # 词面 / 判定常量
    'KIND_FN',
    'ORDER_OK', 'ORDER_ALIAS', 'ORDER_MISMATCH', 'ORDER_UNDECLARED', 'ORDER_VIEW_UNMATCHED',
    'SIG_OK', 'SIG_SYNTHETIC_OK', 'SIG_CONTRADICTION', 'SIG_UNCHECKED', 'SIG_WEAK',
    'MODEL_FLAT', 'MODEL_CHAIN',
    'RATCHET_PASS', 'RATCHET_IMPROVED', 'RATCHET_BLOCKED',
    'METRIC_SLOT', 'METRIC_COUNT', 'METRIC_SIG', 'METRIC_SLOTS', 'METRIC_COUNT_DENOM',
    # 数据
    'DeclSpec', 'ClassDecls', 'BinaryView', 'SlotResult', 'ViewCheck', 'ClassHealth',
    'CheckResult', 'SigVerdict', 'RatchetComponent', 'RatchetDecision',
    # 解析 / 装载
    'parse_decl_text', 'parse_header_decls', 'load_decl_dir', 'struct_to_views',
    'load_structs_dir', 'load_pending', 'norm_addr_key', 'build_hierarchy',
    # 判定
    'decl_arity', 'cpp_type_param_class', 'cpp_return_kind', 'signature_verdict',
    'to_virtual_decls', 'decl_slot_order_kind', 'check_class', 'check_all',
    'build_baseline', 'ratchet_decide', 'render_report', 'report_to_dict',
    'main',
]

# ---------------- 常量 ----------------

MODEL_FLAT = 'flat'      # 声明表即完整槽表（codegen 发射器口径）；只校验主表
MODEL_CHAIN = 'chain'    # 按基链合成多视图（MI 多表各自校验）

ORDER_OK = 'ok'                          # 该槽与预期声明同位同址
ORDER_ALIAS = 'alias'                    # 同址重复槽（二进制同一函数占多槽）⇒ 算已验证
ORDER_MISMATCH = 'mismatch'              # 该地址被声明了，但不在这个位置（顺序错）
ORDER_UNDECLARED = 'undeclared'          # 该地址没有任何声明
ORDER_VIEW_UNMATCHED = 'view_unmatched'  # 该二进制表没匹配上预期视图（未验证）

SIG_OK = 'ok'
SIG_SYNTHETIC_OK = 'synthetic_ok'        # 合成槽（析构/纯虚/调节器）：无签名推断，槽型即证据
SIG_CONTRADICTION = 'contradiction'
SIG_UNCHECKED = 'unchecked'              # 无候选证据（不计入 sig_health 分母）
SIG_WEAK = 'weak'                        # 有候选但什么都没判定（不计入分母）

RATCHET_PASS = 'pass'
RATCHET_IMPROVED = 'improved'
RATCHET_BLOCKED = 'blocked'

METRIC_SLOT = 'slot_health'
METRIC_COUNT = 'count_health'
METRIC_SIG = 'sig_health'
_METRICS = (METRIC_SLOT, METRIC_COUNT, METRIC_SIG)
#: 第 4 类单调分量 = **验证面**（证据规模），见 `ratchet_decide` 的 Q1/Q7 说明。
#: ⚠️ R=2（降级）：只留 `slots`。`count_denom`（声明数）**不是**验证面 —— 它合法地随
#: **声明清理**变化（删掉冗余/错误的 `virtual ~C() {}` 注入虚析构时，工具自己判
#: `count_ok False→True`、`count_health 0.5→1.0`，却会被 `count_denom 8→7 down` 判 blocked
#: ⇒ 拦住正确清理）。`slots` 单分量已足够封死 Q1 两洞（删未声明槽 / 删声明+槽 3→1）。
METRIC_SLOTS = 'slots'
METRIC_COUNT_DENOM = 'count_denom'
_SURFACE_METRICS = (METRIC_SLOTS,)
_RATCHET_METRICS = _METRICS + _SURFACE_METRICS
_EPS = 1e-9

#: 声明级"合成槽"种类（Task 1 单槽组语义）。注意 `purecall` **不在**此列：
#: 纯虚函数在**声明级**是普通虚函数（参与同名分组），只是槽内容指向 CRT purecall stub。
_SYNTHETIC_DECL_KINDS = frozenset({
    KIND_DELETING_DTOR, KIND_ADJUSTOR_STATIC, KIND_ADJUSTOR_VBASE, KIND_COMPOSITE,
})

_ANNOTATIONS_DIR = (_ROOT / 'data' / 'annotations').resolve()


# ---------------- 数据模型 ----------------

@dataclass(frozen=True)
class DeclSpec:
    """一条 `virtual` 声明（生成头口径）。`kind` 用 **Task 2 词面**（`'fn'`/`'deleting_dtor'`…）。"""
    name: str
    params: str = ''                       # 规范参数表：'(int,char*)'（已剥参数名）
    cv: str = ''                           # 'const' / ''
    ret: str = ''                          # C++ 返回类型文本（析构为空）
    kind: str = KIND_FN
    addr: int = None                       # 槽地址；None = 声明无地址注释（位置不可判）
    variadic: bool = False
    pure: bool = False
    inline: bool = False
    line: int = 0

    @property
    def params_norm(self):
        if not self.params:
            return '()'
        return self.params if self.params.startswith('(') else '(%s)' % self.params

    @property
    def sig(self):
        """声明级签名 = 参数表 + 方法 cv（Task 1 `VirtualDecl.sig` 口径）。"""
        return self.params_norm + ((' ' + self.cv) if self.cv else '')


@dataclass(frozen=True)
class ClassDecls:
    """一个类从生成头解析出的声明集合。"""
    cls: str
    bases: tuple = ()
    decls: tuple = ()


@dataclass(frozen=True)
class BinaryView:
    """二进制侧一个 vtable（view）：表地址 + 视图标签（`base` 字段）+ 槽地址序列。"""
    addr: int = None
    base: str = None
    slot_addrs: tuple = ()


@dataclass(frozen=True)
class SigVerdict:
    """签名单槽判定。"""
    status: str
    detail: str = ''
    grade: str = ''
    features: tuple = ()
    notes: tuple = ()
    waived: tuple = ()                     # 被 features 豁免的维度（Ruling 2 的可检查形式）


@dataclass(frozen=True)
class SlotResult:
    """一个二进制槽的判定。"""
    index: int
    addr: int
    order: str
    decl_index: int = None
    decl_name: str = ''
    signature: str = SIG_UNCHECKED
    sig_detail: str = ''
    grade: str = ''
    features: tuple = ()
    notes: tuple = ()
    waived: tuple = ()

    @property
    def verified(self):
        return self.order in (ORDER_OK, ORDER_ALIAS)


@dataclass(frozen=True)
class ViewCheck:
    """一个（二进制表 ↔ 预期视图）对的判定。"""
    cls: str
    label: str = None
    view_addr: int = None
    match_reason: str = ''
    n_slots: int = 0
    n_decl_addr: int = 0
    n_decl_addrless: int = 0
    count_ok: bool = False
    order_model: str = MODEL_FLAT
    slots: tuple = ()
    notes: tuple = ()


@dataclass(frozen=True)
class ClassHealth:
    """一个类的棘轮分量（三个分量各自单调）。"""
    cls: str
    slot_health: float = 0.0
    count_health: float = 0.0
    sig_health: float = None
    n_slots: int = 0
    n_order_ok: int = 0
    n_decl_addr: int = 0
    n_decl_addrless: int = 0
    n_matched_decls: int = 0
    n_count_denom: int = 0
    sig_checked: int = 0
    sig_ok: int = 0
    sig_contradictions: int = 0
    count_ok: bool = False
    n_views: int = 0
    n_views_unmatched: int = 0
    findings: tuple = ()


@dataclass(frozen=True)
class CheckResult:
    classes: dict = field(default_factory=dict)     # cls → ClassHealth
    views: dict = field(default_factory=dict)       # cls → tuple[ViewCheck]
    findings: tuple = ()
    stats: dict = field(default_factory=dict)


@dataclass(frozen=True)
class RatchetComponent:
    klass: str
    metric: str
    base: float = None
    current: float = None
    status: str = 'same'          # 'up' | 'same' | 'down' | 'new' | 'missing' | 'unmeasured'


@dataclass(frozen=True)
class RatchetDecision:
    passed: bool
    improved: bool
    blocked: bool
    components: tuple = ()
    updated: dict = None
    notes: tuple = ()
    baseline_present: bool = True
    comparison: str = 'ok'        # 'ok' | 'model_changed'（模型切换 ⇒ 不可比，不做对比）

    @property
    def state(self):
        if self.blocked:
            return RATCHET_BLOCKED
        return RATCHET_IMPROVED if self.improved else RATCHET_PASS


# ---------------- 地址键归一（Ruling 3） ----------------

def norm_addr_key(addr):
    """地址键归一到 `'0x%08x'`（**小写**）。

    Ruling 3：Task 3 的 `methods_pending` 用 `'0x%08X'` 大写，而真实注解 `methods` 键里
    3398 个中有 32 个是**小写**（如 `SaleUI.json` 的 `0x0045ae60`）⇒ 消费侧必须归一，
    否则 0.94% 的键对不上。
    """
    if isinstance(addr, bool):
        raise TypeError('地址键不接受 bool')
    if isinstance(addr, int):
        return '0x%08x' % addr
    s = str(addr).strip()
    try:
        if s.lower().endswith('h'):
            return '0x%08x' % int(s[:-1], 16)
        return '0x%08x' % int(s, 16)
    except (TypeError, ValueError):
        return s.lower()


def _addr_int(addr):
    """任意地址表示 → int（不可解析 ⇒ None）。"""
    if addr is None:
        return None
    if isinstance(addr, bool):
        return None
    if isinstance(addr, int):
        return addr
    s = str(addr).strip()
    try:
        if s.lower().endswith('h'):
            return int(s[:-1], 16)
        return int(s, 16)
    except (TypeError, ValueError):
        return None


# ---------------- 生成头解析 ----------------

_CLASS_RE = re.compile(r'^\s*class\s+([A-Za-z_]\w*)\s*(?::\s*([^{;]*?))?\s*\{', re.M)
_BASE_RE = re.compile(r'(?:virtual\s+)?(?:public|private|protected)\s+([\w:]+)')
#: `virtual [ret] name(params) [const] [= 0]` + `{...}`（内联体，同行）或 `;` + 可选 `// 0xADDR`
_DECL_RE = re.compile(
    r'^\s*virtual\s+'
    r'(?:(?P<ret>[A-Za-z_][\w:<>,\*&\s]*?)\s+)?'
    r'(?P<name>~?[A-Za-z_]\w*)\s*'
    r'\((?P<params>[^;]*?)\)\s*'
    r'(?P<cv>const)?\s*'
    r'(?P<pure>=\s*0)?\s*'
    r'(?:\{[^\n]*\}|;)'
    r'\s*(?://\s*(?P<addr>0[xX][0-9A-Fa-f]+))?'
)

#: 类型关键字（剥参数名时不得被当成参数名剥掉）
_TYPE_WORDS = frozenset("""
void char short int long float double signed unsigned bool
const volatile struct enum class union
byte word dword qword uint uchar ushort ulong
__int8 __int16 __int32 __int64 __int128
""".split())

#: 已知**指针型** typedef（按值写但语义是指针）
_PTR_TYPEDEFS = frozenset("""
HWND HDC HGDIOBJ HBITMAP HPEN HBRUSH HFONT HICON HCURSOR HMENU HMODULE HINSTANCE HANDLE
LPSTR LPCSTR LPWSTR LPCWSTR LPVOID LPRECT LPARAM WPARAM HKEY HFILE va_list FILE
""".split())

_PARAM_TYPE_TABLE = {
    'void': 'void',
    'char': CLASS_I8, 'byte': CLASS_I8, '_byte': CLASS_I8, 'uint8': CLASS_I8,
    'int8': CLASS_I8, '__int8': CLASS_I8,
    'short': CLASS_I16, 'word': CLASS_I16, 'uint16': CLASS_I16, 'int16': CLASS_I16,
    '__int16': CLASS_I16, 'wchar_t': CLASS_I16,
    'int': CLASS_I32, 'long': CLASS_I32, 'dword': CLASS_I32, 'uint': CLASS_I32,
    'uint32': CLASS_I32, 'int32': CLASS_I32, '__int32': CLASS_I32, 'enum': CLASS_I32,
    '__int64': CLASS_I64, 'int64': CLASS_I64, 'uint64': CLASS_I64,
    'float': CLASS_F32, 'f32': CLASS_F32,
    'double': CLASS_F64, 'f64': CLASS_F64, 'long double': CLASS_F64,
    'bool': CLASS_BOOL,
}


def _split_top(text):
    """按顶层逗号切分（括号/尖括号内不切）。"""
    out, depth, cur = [], 0, []
    for ch in text:
        if ch in '([<':
            depth += 1
        elif ch in ')]>':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(''.join(cur)); cur = []
        else:
            cur.append(ch)
    out.append(''.join(cur))
    return [p for p in (p.strip() for p in out) if p != '']


def _strip_param_names(params):
    """剥掉参数名（只剥一个尾部标识符，且不得是类型关键字）。

    生成头里参数名来自 IDA（`int nVal` / `PalScript *fTime`）。覆写声明与基类声明的参数名
    经常不同 ⇒ 若保留，Task 1 的 `match_key` 认不出覆写（当成新增槽 ⇒ 槽序假失败）。
    """
    if not params.strip():
        return ''
    out = []
    for p in _split_top(params):
        p = ' '.join(p.split())
        if p == '...':
            out.append(p)
            continue
        m = re.match(r'^(.*?[\s\*&])([A-Za-z_]\w*)$', p)
        if m:
            head, tail = m.group(1).strip(), m.group(2)
            if tail not in _TYPE_WORDS and head:
                p = head
        out.append(p)
    return ','.join(out)


def _canon_params_text(params):
    """参数表 → 规范文本 `'(a,b)'`（剥参数名 + 压空白 + `char *`→`char*`）。"""
    inner = _strip_param_names(params)
    if not inner:
        return '()'
    parts = []
    for p in _split_top(inner):
        p = re.sub(r'\s+([*&])', r'\1', p)
        parts.append(p)
    return '(' + ','.join(parts) + ')'


def _class_bodies(text):
    """扫描 `class X ... { ... };` → 产出 (类名, 基类元组, 体文本, 体起始行号)。

    用花括号配对（不是找第一个 `};`）—— 内联虚析构 `virtual ~C() {}` 会引入额外花括号。
    """
    for m in _CLASS_RE.finditer(text):
        cls = m.group(1)
        bases = tuple(_BASE_RE.findall(m.group(2) or ''))
        open_idx = m.end() - 1                      # 指向 '{'
        depth = 0
        i = open_idx
        while i < len(text):
            ch = text[i]
            if ch == '{':
                depth += 1
            elif ch == '}':
                depth -= 1
                if depth == 0:
                    break
            i += 1
        if i >= len(text):
            continue
        body = text[open_idx + 1:i]
        line0 = text.count('\n', 0, open_idx) + 1
        yield cls, bases, body, line0


def parse_decl_text(text):
    """生成头文本 → `{类名: ClassDecls}`（同名类保留**声明最多**的一份，确定性）。"""
    out = {}
    for cls, bases, body, line0 in _class_bodies(text):
        decls = []
        for k, line in enumerate(body.splitlines(), 1):
            m = _DECL_RE.match(line)
            if not m:
                continue
            name = m.group('name')
            params_raw = m.group('params') or ''
            pure = bool(m.group('pure'))
            addr = _addr_int(m.group('addr'))
            params = _canon_params_text(params_raw)
            variadic = '...' in _split_top(params[1:-1]) if params != '()' else False
            kind = (KIND_DELETING_DTOR if name.startswith('~')
                    else (KIND_PURECALL if pure else KIND_FN))
            decls.append(DeclSpec(
                name=name, params=params, cv=(m.group('cv') or ''), ret=(m.group('ret') or '').strip(),
                kind=kind, addr=addr, variadic=variadic, pure=pure,
                inline=('{' in line.rsplit(')', 1)[-1]) if ')' in line else False,
                line=line0 + k,
            ))
        if not decls:
            continue
        prev = out.get(cls)
        if prev is None or len(decls) > len(prev.decls):
            out[cls] = ClassDecls(cls=cls, bases=bases, decls=tuple(decls))
    return {k: out[k] for k in sorted(out)}


#: 别名（历史/外部调用口径）
parse_header_decls = parse_decl_text


def load_decl_dir(path):
    """目录下所有 `**/*.h` 的声明（生成头目录）。确定性：路径排序 + 同名取声明最多者。"""
    path = Path(path)
    if not path.is_dir():
        raise FileNotFoundError('声明目录不存在：%s' % path)
    merged = {}
    for p in sorted(path.rglob('*.h')):
        try:
            text = p.read_text(encoding='utf-8', errors='replace')
        except OSError:
            continue
        for cls, cd in parse_decl_text(text).items():
            prev = merged.get(cls)
            if prev is None or len(cd.decls) > len(prev.decls):
                merged[cls] = cd
    return {k: merged[k] for k in sorted(merged)}


# ---------------- 二进制表装载（只读 `vtables`） ----------------

def struct_to_views(struct):
    """struct JSON → `[BinaryView...]`。**只读 `vtables`**（Ruling 5：不碰 methods 表）。"""
    views = []
    if not isinstance(struct, dict):
        return views
    for vt in (struct.get('vtables') or []):
        if not isinstance(vt, dict):
            continue
        addrs = []
        for s in (vt.get('slots') or []):
            a = _addr_int(s.get('addr') if isinstance(s, dict) else s)
            if a is not None:
                addrs.append(a)
        views.append(BinaryView(addr=_addr_int(vt.get('addr')),
                                base=(vt.get('base') or None),
                                slot_addrs=tuple(addrs)))
    return views


def load_structs_dir(path):
    """注解 struct 目录 → `{类名: [BinaryView...]}`（只保留有槽的表）。"""
    path = Path(path)
    if not path.is_dir():
        raise FileNotFoundError('注解目录不存在：%s' % path)
    out = {}
    for p in sorted(path.glob('*.json')):
        try:
            data = json.loads(p.read_text(encoding='utf-8'))
        except (OSError, ValueError):
            continue
        if not isinstance(data, dict):
            continue
        cls = data.get('name') or p.stem
        views = struct_to_views(data)
        if sum(len(v.slot_addrs) for v in views) <= 0:
            continue
        out[cls] = views
    return out


def load_pending(src):
    """Task 3 `methods_pending` 旁路 → `{归一地址键: record}`；键一律归一（Ruling 3）。"""
    data = src
    if isinstance(src, (str, Path)):
        data = json.loads(Path(src).read_text(encoding='utf-8'))
    if not isinstance(data, dict):
        return {}
    pending = data.get('methods_pending')
    if not isinstance(pending, dict):
        pending = data
    out = {}
    for k, v in pending.items():
        if not isinstance(v, dict):
            continue
        out[norm_addr_key(k)] = v
    return out


# ---------------- 词面适配（Ruling 4） ----------------

def decl_slot_order_kind(kind):
    """声明级 kind → **Task 1** 词面。**必须**经 Task 2 适配器（Ruling 4）。

    `'fn'` → `'func'`（同名分组参与）；`purecall` 在声明级也是普通虚函数（见
    `_SYNTHETIC_DECL_KINDS` 注释）；`deleting_dtor`/`adjustor*`/`composite` ⇒ 合成单槽组。
    """
    k = normalize_kind(kind)                     # 未知名面直接 ValueError（不静默）
    if k in _SYNTHETIC_DECL_KINDS:
        return slot_order_kind(k)
    return KIND_FUNC


def _to_virtual_decl(d, owner):
    return VirtualDecl(name=d.name, sig=d.sig, kind=decl_slot_order_kind(d.kind), owner=owner)


def to_virtual_decls(cd):
    """`ClassDecls` → Task 1 `VirtualDecl` 列表（经 Ruling 4 适配器）。"""
    return [_to_virtual_decl(d, cd.cls) for d in cd.decls]


def build_hierarchy(decls_by_cls):
    """`{类名: ClassDecls}` → Task 1 `compute_class_views` 的 hierarchy 结构。"""
    return {cls: {'bases': list(cd.bases),
                  'decls': to_virtual_decls(cd)}
            for cls, cd in decls_by_cls.items()}


# ---------------- 签名等价类（声明侧类型 → Task 3 词面） ----------------

def cpp_type_param_class(text):
    """C++ 参数类型文本 → Task 3 参数**等价类**（未知 ⇒ None，绝不当等价）。

    等价类口径与 Task 3 一致：`bool` 与 `i32` **不等价**（调用点 `setcc` 物化 +5B），
    `char`/`short` 单独成类；`int`/指针 字节等价（同族）。
    """
    if text is None:
        return None
    t = ' '.join(str(text).split())
    if not t:
        return None
    if t == 'BOOL':                      # Windows BOOL = int（不是 C++ bool）
        return CLASS_I32
    if t in _PTR_TYPEDEFS:
        return CLASS_PTR
    if '*' in t or '&' in t:
        return CLASS_PTR
    t = re.sub(r'^(?:(?:const|volatile)\s+)+', '', t)
    t = re.sub(r'^(?:(?:struct|enum|class|union)\s+)', '', t)
    if t == 'BOOL':
        return CLASS_I32
    low = t.lower()
    if low in _PARAM_TYPE_TABLE:
        return _PARAM_TYPE_TABLE[low]
    low2 = low.replace('unsigned ', '').replace('signed ', '').strip()
    if low2 in _PARAM_TYPE_TABLE:
        return _PARAM_TYPE_TABLE[low2]
    if ' ' in low or '::' in low:
        return CLASS_STRUCT
    if re.match(r'^[A-Za-z_]\w*$', t) and not t.isupper():
        return CLASS_STRUCT                # 按值类/结构体
    if re.match(r'^[A-Za-z_]\w*$', t):
        return None                        # 未知全大写名（可能是宏）⇒ 不断言
    return None


def cpp_return_kind(text):
    """C++ 返回类型文本 → Task 3 返回宽度词面；**不可判 ⇒ None**（绝不猜）。"""
    if text is None:
        return None
    t = ' '.join(str(text).split())
    if not t:
        return None
    if t == 'void':
        return RET_VOID
    if t == 'BOOL':
        return RET_I32
    if t in _PTR_TYPEDEFS or '*' in t or '&' in t:
        return RET_I32                     # 4 字节寄存器返回（Task 3 词面不区分 int/指针）
    t = re.sub(r'^(?:(?:const|volatile)\s+)+', '', t)
    t = re.sub(r'^(?:(?:struct|enum|class|union)\s+)', '', t)
    low = t.lower()
    if low in _PARAM_TYPE_TABLE:
        k = _PARAM_TYPE_TABLE[low]
        return {CLASS_I8: RET_I8, CLASS_I16: RET_I16, CLASS_I32: RET_I32,
                CLASS_I64: RET_I64, CLASS_F32: RET_F32, CLASS_F64: RET_F64,
                CLASS_BOOL: RET_BOOL, 'void': RET_VOID}.get(k)
    low2 = low.replace('unsigned ', '').replace('signed ', '').strip()
    if low2 != low and low2 in _PARAM_TYPE_TABLE:
        return cpp_return_kind(low2)
    return None                            # 结构体按值返回：宽度不可判 ⇒ 不作判据


def decl_arity(decl):
    """声明参数个数（排除 `this` 与 `...`；与 Task 3 的 `arity` 同口径）。"""
    p = decl.params_norm
    if p == '()':
        return 0
    inner = p[1:-1]
    return len([x for x in _split_top(inner) if x and x != '...'])


def _decl_param_classes(decl):
    p = decl.params_norm
    if p == '()':
        return []
    return [cpp_type_param_class(x) for x in _split_top(p[1:-1]) if x != '...']


# ---------------- 签名判定（§3；Ruling 1/2 的实现） ----------------

def _feats(cand):
    return {str(f) for f in (cand.get('features') or ())}


def _waived_for(feats):
    """features → 被豁免的维度（Ruling 2：sret_ambiguous 与 hidden_param_suspicion 语义不同）。

    * `sret_ambiguous` = **判不出**（返回可能是 >8B 结构 ⇒ 首参 sret ⇒ 整体可能错位一位）⇒
      豁免 return/arity/params 三个维度（不能拿"错位"当矛盾）
    * `sret` = **已判定**是 >8B 结构返回 ⇒ 只豁免 arity/params（隐藏 sret 指针是否计入），
      **return 维度仍然校验**（声明 void 与 sret 是实打实的矛盾）
    * `hidden_param_suspicion` = **有隐藏参数嫌疑** ⇒ 只把 arity 放宽为下界
    """
    waived = set()
    if FEATURE_SRET_AMBIGUOUS in feats:
        waived |= {'return', 'arity', 'params'}
    elif FEATURE_SRET in feats:
        waived |= {'arity', 'params'}
    if FEATURE_HIDDEN_PARAM_SUSPICION in feats:
        waived.add('arity')
    return waived


def _candidate_detail(decl, cand):
    """一个候选 vs 声明 → `(矛盾detail|None, 判定维度数, waived, notes)`。"""
    feats = _feats(cand)
    waived = _waived_for(feats)
    notes = tuple(sorted(f for f in (FEATURE_SRET_AMBIGUOUS, FEATURE_HIDDEN_PARAM_SUSPICION,
                                     FEATURE_SRET, FEATURE_THIS_ON_STACK,
                                     FEATURE_CC_FROM_MANGLING) if f in feats))
    determined = 0

    # 1) 调用约定（只认 A 级、非 provisional、非 this_on_stack 的硬矛盾）
    conv = cand.get('convention') or CC_UNKNOWN
    if (conv not in (CC_UNKNOWN, CC_THISCALL) and cand.get('grade') == GRADE_A
            and not cand.get('cc_provisional') and FEATURE_THIS_ON_STACK not in feats
            and not decl.variadic and not cand.get('variadic')
            and conv in (CC_CDECL, CC_STDCALL, CC_FASTCALL)):
        return 'convention_mismatch', 0, waived, notes

    # 2) 变参
    if bool(cand.get('variadic')) != bool(decl.variadic):
        return 'variadic_mismatch', 0, waived, notes
    if cand.get('variadic'):
        determined += 1

    # 3) 参数个数（arity 是 callee 侧证据；下界/隐藏参数只放宽下界）
    d_arity = decl_arity(decl)
    arity = cand.get('arity')
    if arity is not None:
        determined += 1
        if 'arity' in waived and (FEATURE_SRET_AMBIGUOUS in feats or FEATURE_SRET in feats):
            if abs(d_arity - arity) > 1:
                return 'arity_mismatch', determined, waived, notes
        elif cand.get('arity_is_lower_bound') or FEATURE_HIDDEN_PARAM_SUSPICION in feats:
            if d_arity < arity:
                return 'arity_below_lower_bound', determined, waived, notes
        elif d_arity != arity:
            return 'arity_mismatch', determined, waived, notes

    # 4) 返回宽度（sret_ambiguous 豁免；已判定的 sret 不豁免 —— 见 `_waived_for`）
    rk = cand.get('return_kind') or RET_UNKNOWN
    if rk == RET_UNKNOWN or 'return' in waived:
        pass
    else:
        drk = cpp_return_kind(decl.ret)
        if drk is None:
            pass                            # 按值结构体返回：宽度不可判 ⇒ 不作判据
        elif drk != rk:
            return 'return_mismatch', determined, waived, notes
        else:
            determined += 1

    # 5) 参数等价类
    if 'params' not in waived:
        got = _decl_param_classes(decl)
        for i, p in enumerate(cand.get('params') or ()):
            if i >= len(got):
                break
            classes = {str(c) for c in ((p or {}).get('class_candidates') or ())}
            if not classes:
                continue
            if got[i] is None:
                continue
            determined += 1
            if got[i] in classes or any(param_class_equiv(got[i], c) for c in classes):
                continue
            return 'param_class_mismatch', determined, waived, notes

    return None, determined, waived, notes


_GRADE_RANK = {GRADE_A: 0, GRADE_B: 1, GRADE_C: 2}


def signature_verdict(decl, cands, record=None):
    """§3 签名单槽判定（**等价类维度**）。

    * 无候选 + 合成槽（或 Task 3 显式 `skipped`）⇒ `SIG_SYNTHETIC_OK`（槽型声明即证据）
    * 无候选 + 普通声明 ⇒ `SIG_UNCHECKED`（不计入 `sig_health` 分母）
    * 候选中**任一**无矛盾 ⇒ `SIG_OK`（**Ruling 1**：B/C 带证据同样放行）；什么都没判定 ⇒ `SIG_WEAK`
    * 全部有矛盾 ⇒ `SIG_CONTRADICTION`（取证据等级最高的候选作 detail）

    `SIG_WEAK` 与 `SIG_UNCHECKED` 都**不**进 `sig_health` 分母（新证据出现不得倒打一耙 ⇒
    棘轮单调），只有 `SIG_CONTRADICTION` 会把分量拉下来。
    """
    record = record if isinstance(record, dict) else {}
    cands = list(cands or ())
    if record.get('skipped'):
        return SigVerdict(status=SIG_SYNTHETIC_OK, detail='synthetic',
                          notes=('task3_skipped_synthetic_slot',))
    if not cands:
        if decl.kind in _SYNTHETIC_DECL_KINDS:
            return SigVerdict(status=SIG_SYNTHETIC_OK, detail='synthetic',
                              notes=('declaration_kind_synthetic',))
        return SigVerdict(status=SIG_UNCHECKED, detail='unchecked')

    # best = (detail, cand, determined, waived, notes, rank)；rank 越小 = 证据越强
    best = None
    for c in cands:
        detail, determined, waived, notes = _candidate_detail(decl, c)
        if detail is None and determined:
            return SigVerdict(status=SIG_OK, detail='ok', grade=c.get('grade') or '',
                              features=tuple(sorted(_feats(c))), notes=notes,
                              waived=tuple(sorted(waived)))
        rank = _GRADE_RANK.get(c.get('grade') or GRADE_C, 3)
        if detail is None:
            detail, rank = 'nothing_determined', 99 + rank    # 弱候选排在所有矛盾之后
        if best is None or rank < best[5]:
            best = (detail, c, determined, waived, notes, rank)

    status = SIG_WEAK if best[0] == 'nothing_determined' else SIG_CONTRADICTION
    return SigVerdict(status=status, detail=best[0], grade=best[1].get('grade') or '',
                      features=tuple(sorted(_feats(best[1]))), notes=best[4],
                      waived=tuple(sorted(best[3])))


# ---------------- 预期视图与视图配对 ----------------

@dataclass(frozen=True)
class _ExpectedView:
    label: str
    slots: tuple = ()


def _expected_views(cls, cd, hierarchy, model):
    """声明的**预期视图**（Task 1 正向规则）→ `([_ExpectedView...], notes)`。

    * `MODEL_FLAT`：声明表即完整槽表（codegen 发射器口径）⇒ 单视图
    * `MODEL_CHAIN`：按基链合成多视图（MI 多表各自校验）；基链不可解析时**回落 flat** 并留痕
    """
    if model == MODEL_CHAIN:
        if hierarchy is None:
            hierarchy = {cls: {'bases': list(cd.bases), 'decls': to_virtual_decls(cd)}}
        try:
            views = compute_class_views(hierarchy, cls)
            return ([_ExpectedView(label=lbl, slots=tuple(slots)) for lbl, slots in views],
                    ('order_model=chain',))
        except (KeyError, ValueError, NotImplementedError) as e:
            return ([_ExpectedView(label=cls, slots=tuple(compute_slot_order([], to_virtual_decls(cd))))],
                    ('order_model=flat', 'chain_fallback:%s' % type(e).__name__))
    return ([_ExpectedView(label=cls, slots=tuple(compute_slot_order([], to_virtual_decls(cd))))],
            ('order_model=flat',))


def _addr_index(cd, decls_by_cls):
    """`(类, match_key) → (槽地址, DeclSpec)`（把预期视图里的声明解析回地址与原声明）。

    按 `(声明类, match_key)` 建索引而不是按对象身份：`compute_class_views` 里**继承槽**仍是
    基类声明（owner=基类），而**覆写槽**是本类声明（owner=本类）⇒ 两者地址不同且都必须正确定位。
    """
    idx = {}
    for cls, c in (decls_by_cls or {cd.cls: cd}).items():
        for d in c.decls:
            vd = _to_virtual_decl(d, cls)
            idx[(cls, match_key(vd))] = (d.addr, d)
    return idx


def _match_views(expected, binary_views):
    """预期视图 ↔ 二进制表配对：标签 → 槽数唯一 → 序号；剩余记 `view_unmatched`。"""
    pairs = []
    used = set()
    matched_bin = set()

    for bi, bv in enumerate(binary_views):
        if not bv.base:
            continue
        for i, ev in enumerate(expected):
            if i in used or ev.label != bv.base:
                continue
            used.add(i); matched_bin.add(bi)
            pairs.append((bi, bv, ev, 'label'))
            break

    for bi, bv in enumerate(binary_views):
        if bi in matched_bin:
            continue
        cands = [i for i, ev in enumerate(expected)
                 if i not in used and len(ev.slots) == len(bv.slot_addrs)]
        if len(cands) == 1:
            used.add(cands[0]); matched_bin.add(bi)
            pairs.append((bi, bv, expected[cands[0]], 'count'))

    rest_exp = [i for i in range(len(expected)) if i not in used]
    rest_bin = [bi for bi in range(len(binary_views)) if bi not in matched_bin]
    for bi, i in zip(rest_bin, rest_exp):
        used.add(i); matched_bin.add(bi)
        pairs.append((bi, binary_views[bi], expected[i], 'index'))
    for bi in rest_bin[len(rest_exp):]:
        pairs.append((bi, binary_views[bi], None, 'view_unmatched'))

    pairs.sort(key=lambda p: p[0])
    return pairs


# ---------------- 单类校验 ----------------

def check_class(cls, cd, binary_views, pending=None, hierarchy=None, model=MODEL_FLAT,
                decls_by_cls=None):
    """一个类的全部 view 校验 → `(list[ViewCheck], ClassHealth)`。"""
    pending = pending or {}
    expected, model_notes = _expected_views(cls, cd, hierarchy, model)
    idx = _addr_index(cd, decls_by_cls)
    pairs = _match_views(expected, binary_views)

    view_checks = []
    findings = []
    all_decl_addrs = []
    n_addrless = 0
    covered_slot_addrs = set()

    for _bi, bv, ev, reason in pairs:
        seq = []           # [(DeclSpec, addr)]
        addrless = 0
        if ev is not None:
            for entry in ev.slots:
                d = entry.decl
                a, spec = idx.get((d.owner, match_key(d)), (None, None))
                if a is None:
                    addrless += 1
                else:
                    seq.append((spec, a))
        binaddrs = list(bv.slot_addrs)
        slot_results = []
        declared = {}
        declared_pos = {}
        for k, (d, a) in enumerate(seq):
            declared.setdefault(a, d)
            declared_pos.setdefault(a, k)
        k = 0                 # 在预期序列 seq 中的位置（别名槽**不**推进）
        seen = set()
        for i, sa in enumerate(binaddrs):
            notes = ()
            decl = None
            di = None
            if ev is None:
                # 该二进制表没有匹配到预期视图 ⇒ 全部槽未验证（不是"少声明"，是"没视图"）
                slot_results.append(SlotResult(
                    index=i, addr=sa, order=ORDER_VIEW_UNMATCHED,
                    signature=SIG_UNCHECKED, sig_detail='view_unmatched',
                    notes=('该二进制表未匹配到预期视图（%s 模型下不校验）' % model,),
                ))
                seen.add(sa)
                continue
            if k < len(seq) and seq[k][1] == sa:
                order = ORDER_OK
                decl, di = seq[k][0], k
                k += 1
            elif sa in seen and sa in declared:
                order = ORDER_ALIAS
                decl = declared[sa]
                di = declared_pos.get(sa)
                notes = ('别名槽：二进制表在同一函数上占多槽，声明按唯一地址去重 ⇒ 该槽由同一声明覆盖',)
            elif sa in declared:
                # 位置对齐（不是贪心查找）：该地址声明了，但不在这个位置 ⇒ 顺序错位
                order = ORDER_MISMATCH
                decl = declared[sa]
                di = declared_pos.get(sa)
                if k < len(seq):
                    notes = ('顺序错位：预期位置 %d 是 0x%08X，二进制此处是 0x%08X'
                             % (k, seq[k][1], sa),)
                else:
                    notes = ('顺序错位：声明序列已用尽，二进制此处仍有已声明地址 0x%08X' % sa,)
                k += 1
            else:
                order = ORDER_UNDECLARED
                notes = ('该槽地址没有任何 virtual 声明覆盖（发射器不会为它生成声明 ⇒ 编译器槽位数不足）',)
            seen.add(sa)

            sig = SigVerdict(status=SIG_UNCHECKED, detail='unchecked')
            if order in (ORDER_OK, ORDER_ALIAS) and decl is not None:
                rec = pending.get(norm_addr_key(sa)) or {}
                sig = signature_verdict(decl, rec.get('candidates') or (), record=rec)
            elif order in (ORDER_MISMATCH, ORDER_UNDECLARED):
                sig = SigVerdict(status=SIG_UNCHECKED, detail='order_not_ok')

            slot_results.append(SlotResult(
                index=i, addr=sa, order=order, decl_index=di,
                decl_name=(decl.name if decl is not None else ''),
                signature=sig.status, sig_detail=sig.detail, grade=sig.grade,
                features=sig.features, notes=tuple(notes) + tuple(sig.notes), waived=sig.waived,
            ))

        n_slots = len(binaddrs)
        n_decl_addr = len(seq)
        count_ok = (n_decl_addr + addrless == n_slots) and ev is not None
        vnotes = list(model_notes)
        if ev is None:
            count_ok = False
            vnotes.append('view_unmatched：该二进制表没有匹配到预期视图（%s 模型下未验证）'
                          '⇒ 如需逐表校验请用 --model chain' % model)
        view_checks.append(ViewCheck(
            cls=cls, label=(ev.label if ev is not None else None), view_addr=bv.addr,
            match_reason=reason, n_slots=n_slots, n_decl_addr=n_decl_addr,
            n_decl_addrless=addrless, count_ok=count_ok, order_model=model,
            slots=tuple(slot_results), notes=tuple(vnotes),
        ))

        all_decl_addrs.extend(a for _d2, a in seq)
        n_addrless += addrless
        covered_slot_addrs |= set(binaddrs)

    # ---- 汇总 ----
    n_slots = sum(v.n_slots for v in view_checks)
    n_order_ok = sum(1 for v in view_checks for s in v.slots if s.verified)
    n_decl_addr = len(all_decl_addrs)
    n_matched = len([a for a in set(all_decl_addrs) if a in covered_slot_addrs])
    uncovered = len([a for a in covered_slot_addrs if a not in set(all_decl_addrs)])
    denom = n_decl_addr + n_addrless + uncovered
    count_health = (n_matched / denom) if denom else 1.0
    slot_health = (n_order_ok / n_slots) if n_slots else 0.0
    sig_checked = sum(1 for v in view_checks for s in v.slots
                      if s.signature in (SIG_OK, SIG_SYNTHETIC_OK, SIG_CONTRADICTION))
    sig_ok = sum(1 for v in view_checks for s in v.slots
                 if s.signature in (SIG_OK, SIG_SYNTHETIC_OK))
    sig_health = (sig_ok / sig_checked) if sig_checked else None
    n_view_unmatched = sum(1 for v in view_checks if v.label is None)
    count_ok = bool(view_checks) and all(v.count_ok for v in view_checks)

    # ---- 发现项 ----
    for v in view_checks:
        if not v.count_ok:
            findings.append('%s[view %s] 槽数：声明 %d（+%d 无地址）≠ 槽 %d'
                            % (cls, v.label or '-', v.n_decl_addr, v.n_decl_addrless, v.n_slots))
        if v.n_decl_addrless:
            findings.append('%s[view %s] %d 条 virtual 声明无地址注释（内联定义/注入虚析构）'
                            '⇒ 位置不可判，不计入逐槽序对比'
                            % (cls, v.label or '-', v.n_decl_addrless))
        for s in v.slots:
            if s.order == ORDER_MISMATCH:
                findings.append('%s[view %s] 槽序：槽%d @0x%08X 位置错（声明里有、位置不对）'
                                % (cls, v.label or '-', s.index, s.addr))
            elif s.order == ORDER_UNDECLARED:
                findings.append('%s[view %s] 槽序：槽%d @0x%08X 无声明'
                                % (cls, v.label or '-', s.index, s.addr))
            elif s.order == ORDER_VIEW_UNMATCHED:
                findings.append('%s[view %s] view_unmatched：该表未验证' % (cls, '-'))
                break
            if s.signature == SIG_CONTRADICTION:
                findings.append('%s[view %s] 签名：槽%d @0x%08X %s（grade %s%s）'
                                % (cls, v.label or '-', s.index, s.addr, s.sig_detail, s.grade or '?',
                                   ('；豁免 ' + ','.join(s.waived)) if s.waived else ''))

    health = ClassHealth(
        cls=cls, slot_health=slot_health, count_health=count_health, sig_health=sig_health,
        n_slots=n_slots, n_order_ok=n_order_ok, n_decl_addr=n_decl_addr,
        n_decl_addrless=n_addrless, n_matched_decls=n_matched, n_count_denom=denom,
        sig_checked=sig_checked, sig_ok=sig_ok,
        sig_contradictions=sum(1 for v in view_checks for s in v.slots
                               if s.signature == SIG_CONTRADICTION),
        count_ok=count_ok, n_views=len(view_checks), n_views_unmatched=n_view_unmatched,
        findings=tuple(findings),
    )
    return view_checks, health


def check_all(decls, structs, pending=None, model=MODEL_FLAT, hierarchy=None, decls_by_cls=None):
    """全类校验。类集合 = **二进制表有槽的类**（棘轮要保护的对象）。"""
    pending = pending or {}
    decls_by_cls = decls_by_cls if decls_by_cls is not None else decls
    if model == MODEL_CHAIN and hierarchy is None:
        hierarchy = build_hierarchy(decls)
    classes, views, findings = {}, {}, []
    for cls in sorted(structs):
        cd = decls.get(cls) or ClassDecls(cls=cls, bases=(), decls=())
        vcs, health = check_class(cls, cd, structs[cls], pending=pending,
                                 hierarchy=hierarchy, model=model, decls_by_cls=decls_by_cls)
        classes[cls] = health
        views[cls] = tuple(vcs)
        findings.extend(health.findings)

    slots_total = sum(h.n_slots for h in classes.values())
    order_ok = sum(h.n_order_ok for h in classes.values())
    matched = sum(h.n_matched_decls for h in classes.values())
    denom = sum(h.n_count_denom for h in classes.values())
    sig_checked = sum(h.sig_checked for h in classes.values())
    sig_ok = sum(h.sig_ok for h in classes.values())
    stats = {
        'classes': len(classes),
        'views': sum(h.n_views for h in classes.values()),
        'views_unmatched': sum(h.n_views_unmatched for h in classes.values()),
        'slots_total': slots_total,
        'order_ok': order_ok,
        'slot_health': (order_ok / slots_total) if slots_total else 0.0,
        'count_health': (matched / denom) if denom else 1.0,
        'sig_health': (sig_ok / sig_checked) if sig_checked else None,
        'sig_checked': sig_checked,
        'sig_ok': sig_ok,
        'sig_contradictions': sum(h.sig_contradictions for h in classes.values()),
        'count_ok_classes': sum(1 for h in classes.values() if h.count_ok),
        'classes_full': sum(1 for h in classes.values() if h.slot_health >= 1.0),
        'classes_zero': sum(1 for h in classes.values() if h.slot_health <= 0.0),
        'decl_addrless': sum(h.n_decl_addrless for h in classes.values()),
        'model': model,
    }
    return CheckResult(classes=classes, views=views, findings=tuple(findings), stats=stats)


# ---------------- 棘轮 ----------------

def _r6(x):
    return None if x is None else round(float(x), 6)


def build_baseline(result, generated_at=None):
    """`CheckResult` → 基线 dict（可比、可 roundtrip JSON、确定性）。"""
    return {
        'version': 1,
        'generated_at': generated_at,
        'overall': {k: (_r6(v) if isinstance(v, float) else v) for k, v in result.stats.items()},
        'classes': {
            cls: {
                'slot_health': _r6(h.slot_health),
                'count_health': _r6(h.count_health),
                'sig_health': _r6(h.sig_health),
                'slots': h.n_slots,
                'order_ok': h.n_order_ok,
                'decl_addr': h.n_decl_addr,
                'decl_addrless': h.n_decl_addrless,
                'matched_decls': h.n_matched_decls,
                'count_denom': h.n_count_denom,
                'sig_checked': h.sig_checked,
                'sig_ok': h.sig_ok,
                'count_ok': h.count_ok,
                'views': h.n_views,
                'views_unmatched': h.n_views_unmatched,
            } for cls, h in sorted(result.classes.items())
        },
    }


def ratchet_decide(baseline, current):
    """棘轮判定：**四类分量（4 个可比值）任一不得下降**（无阈值、无硬门禁）。

    分量 = 三个 health（`_METRICS`）+ 一个**验证面规模**（`_SURFACE_METRICS`：

    * `slots` = 该类的二进制槽数（注解 `vtables[].slots` 的证据规模）

    **为什么必须有第 4 类**（R=1 修复的语义洞）：只比**比值**时，缩小分母会被奖励 ——
    删掉一个**未声明**槽 ⇒ `slot_health 0.5 → 1.0` ⇒ 判 `improved` 并回写基线；同时
    删声明与其槽（`slots_total 3 → 1`）⇒ 三个比值**全 same** ⇒ 放行。基线一旦被写成 1.0，
    把缺失证据**补回来**（完备性修复）反而让 `slot_health` 下降 ⇒ BLOCKED ⇒ 门禁拦住**正确
    的修复**（与 CLAUDE.md 的"假失败"同型）。⇒ 规模本身必须单调不降 —— 与"整类消失 =
    `missing` ⇒ 阻塞"是同一语义：**验证面不得缩小**。

    ⚠️ **R=2 降级（去 `count_denom`）**：R=1 曾把 `count_denom`（`声明数 + 无地址声明数 +
    未覆盖槽数`）也当验证面 ⇒ **过严**：它把"删任何声明"一律判 `down`，包括**正确清理
    冗余/错误声明**。实测反例：删 `CGameData.h` 中重复表达的注入虚析构
    `virtual ~CGameData() {}`（无地址、槽表里没有它）⇒ 本工具自己判 `count_ok False→True`、
    `count_health 0.875 → 1.0`（改善）、`slot_health`/`slots` 不变，却被
    `count_denom 8 → 7 down` 判 `blocked`/`updated=None`；R=1 之前的实现对该改动是
    `pass` 并回写基线 ⇒ **新增过严路径**。理由：`count_denom`（声明数）合法地随声明清理
    变化，真正的验证面是注解 vtables 槽数（`slots`）；而 `slots` 单分量**已能**捕获 Q1
    两洞（删未声明槽 ⇒ `slots 2 → 1 down`；删声明+槽 3→1 ⇒ `slots 3 → 1 down`）。
    `count_denom` 仍在报告/baseline JSON 里（可观测），只是**不参与棘轮判定**。

    * 任一分量下降 ⇒ `down` ⇒ 阻塞
    * 基线里有、当前没有的类 ⇒ `missing` ⇒ 阻塞（整类的验证面消失同样是倒退）
    * 当前新增的类 ⇒ `new` ⇒ 不算倒退（算改善）
    * `None` 的处理**方向性**（R=1 修复 Q3）：
      - 基线 `None` → 当前有值 ⇒ `unmeasured` ⇒ **不**阻塞（新证据出现不得倒打一耙）
      - 基线**有值** → 当前 `None` ⇒ `down` ⇒ **阻塞**（证据源丢失是倒退：例如漏传
        `--pending` ⇒ 整个签名维度的验证悄悄消失）

    ⚠️ 有意的验证面缩小（删掉确认是错的**槽**）会与本棘轮冲突：语义上"缩小验证面"必须
    显式重建基线（`--baseline` 指向新路径、或先移除旧基线文件）——这是棘轮制的固有代价，
    不是 bug（无阈值、无硬门禁的代价是不接受静默缩水）。
    **但删除冗余/错误声明不再属于此类**（R=2）：声明数不参与判定，只留 `slots`；
    删声明本身不阻塞，只有"删到槽也少"才阻塞。
    """
    base_classes = (baseline or {}).get('classes') or {}
    cur_classes = (current or {}).get('classes') or {}
    comps, notes = [], []
    improved = blocked = False
    base_model = ((baseline or {}).get('overall') or {}).get('model')
    cur_model = ((current or {}).get('overall') or {}).get('model')
    if base_model is not None and cur_model is not None and base_model != cur_model:
        # 模型切换（flat ↔ chain）会让全部分量不可比 ⇒ 不做对比，也不据此阻塞；
        # 必须显式重建基线（--write-baseline）。
        return RatchetDecision(
            passed=True, improved=False, blocked=False, components=(),
            updated=current, baseline_present=bool(baseline), comparison='model_changed',
            notes=('模型不一致（基线 %s ≠ 当前 %s）⇒ 本次不做棘轮对比；'
                   '如为有意切换，请用 --write-baseline 重建基线' % (base_model, cur_model),))
    for cls in sorted(set(base_classes) | set(cur_classes)):
        if cls not in cur_classes:
            comps.append(RatchetComponent(klass=cls, metric='*', status='missing'))
            notes.append('%s: 当前结果里消失了（整类验证面丢失）' % cls)
            blocked = True
            continue
        if cls not in base_classes:
            comps.append(RatchetComponent(klass=cls, metric='*', status='new'))
            improved = True
            continue
        b, c = base_classes[cls], cur_classes[cls]
        for metric in _RATCHET_METRICS:
            bv, cv = b.get(metric), c.get(metric)
            if bv is None and cv is None:
                continue
            if cv is None:
                # 基线**有值**而当前测不出 ⇒ 证据源丢失（如漏传 --pending）⇒ 倒退，必须阻塞。
                comps.append(RatchetComponent(klass=cls, metric=metric, base=bv, current=None,
                                              status='down'))
                notes.append('%s.%s 证据源丢失：%s → 无证据（基线有值而当前测不出 ⇒ 视为倒退，'
                             '不是 unmeasured）' % (cls, metric, bv))
                blocked = True
                continue
            if bv is None:
                # 基线未测而当前有值 ⇒ 新证据出现不得倒打一耙 ⇒ 不阻塞。
                comps.append(RatchetComponent(klass=cls, metric=metric, base=None, current=cv,
                                              status='unmeasured'))
                notes.append('%s.%s: 基线未测（None → %s）⇒ 不阻塞' % (cls, metric, cv))
                continue
            if cv > bv + _EPS:
                status = 'up'
                improved = True
            elif cv < bv - _EPS:
                status = 'down'
                blocked = True
                if metric in _SURFACE_METRICS:
                    notes.append('%s.%s 验证面缩小：%s → %s（证据规模只允许持平或上升；'
                                 '如需有意缩小请显式重建基线）' % (cls, metric, bv, cv))
                else:
                    notes.append('%s.%s 下降：%.6f → %.6f（允许的只有持平或上升）'
                                 % (cls, metric, bv, cv))
            else:
                status = 'same'
            comps.append(RatchetComponent(klass=cls, metric=metric, base=bv, current=cv,
                                          status=status))
    # 阻塞优先级最高：被阻塞的运行**不得**同时报 `improved`（否则"删一个槽换更高比值"
    # 这种缩水会被 `improved=True` 读成"被奖励"，虽然 `updated` 已经因阻塞而不写）。
    # 想知道"哪些分量上升"请看 `components` 里 status=='up' 的条目。
    improved = improved and not blocked
    updated = current if improved else None
    return RatchetDecision(passed=not blocked, improved=improved, blocked=blocked,
                           components=tuple(comps), updated=updated, notes=tuple(notes),
                           baseline_present=bool(baseline))


# ---------------- 报告 / CLI ----------------

def report_to_dict(result, decision=None):
    """报告 JSON（CLI `--json` 与报告消费）。"""
    out = {
        'overall': result.stats,
        'classes': {cls: {
            'slot_health': _r6(h.slot_health), 'count_health': _r6(h.count_health),
            'sig_health': _r6(h.sig_health), 'slots': h.n_slots, 'order_ok': h.n_order_ok,
            'decl_addr': h.n_decl_addr, 'decl_addrless': h.n_decl_addrless,
            'matched_decls': h.n_matched_decls, 'sig_checked': h.sig_checked,
            'sig_ok': h.sig_ok, 'sig_contradictions': h.sig_contradictions,
            'count_ok': h.count_ok, 'views': h.n_views,
            'views_unmatched': h.n_views_unmatched,
        } for cls, h in sorted(result.classes.items())},
        'findings': list(result.findings),
    }
    if decision is not None:
        out['ratchet'] = {
            'state': decision.state,
            'passed': decision.passed,
            'improved': decision.improved,
            'blocked': decision.blocked,
            'baseline_present': decision.baseline_present,
            'comparison': decision.comparison,
            'notes': list(decision.notes),
            'down': [{'class': c.klass, 'metric': c.metric, 'base': c.base,
                      'current': c.current} for c in decision.components if c.status == 'down'],
            'missing': [c.klass for c in decision.components if c.status == 'missing'],
        }
    return out


def render_report(result, decision=None, max_classes=40, max_findings=200):
    """人读报告（含三类校验项与棘轮三态）。"""
    s = result.stats
    L = []
    L.append('== vtable 声明校验（棘轮制） ==')
    L.append('模型 %s · 类 %d · view %d（未匹配 %d）· 槽 %d'
             % (s.get('model'), s.get('classes', 0), s.get('views', 0),
                s.get('views_unmatched', 0), s.get('slots_total', 0)))
    L.append('【槽数】count_ok 类 %d/%d · count_health %.6f'
             % (s.get('count_ok_classes', 0), s.get('classes', 0), s.get('count_health', 0.0)))
    L.append('【槽序】已验证槽 %d/%d · slot_health %.6f · 全对类 %d · 全错类 %d'
             % (s.get('order_ok', 0), s.get('slots_total', 0), s.get('slot_health', 0.0),
                s.get('classes_full', 0), s.get('classes_zero', 0)))
    sh = s.get('sig_health')
    L.append('【签名】有证据槽 %d · 无矛盾 %d · 矛盾 %d · sig_health %s'
             % (s.get('sig_checked', 0), s.get('sig_ok', 0), s.get('sig_contradictions', 0),
                ('%.6f' % sh) if sh is not None else 'N/A（无签名证据）'))
    L.append('无地址声明 %d 条（位置不可判，只计入槽数项）' % s.get('decl_addrless', 0))
    L.append('')
    L.append('-- 逐类 health（slot_health / count_health / sig_health）--')
    rows = sorted(result.classes.values(), key=lambda h: (h.slot_health, h.cls))
    for h in rows[:max_classes]:
        L.append('  %-28s %6.3f  %6.3f  %s   (槽 %d/%d, 声明 %d%s)'
                 % (h.cls, h.slot_health, h.count_health,
                    ('%6.3f' % h.sig_health) if h.sig_health is not None else '   N/A',
                    h.n_order_ok, h.n_slots, h.n_decl_addr,
                    ('+%d 无地址' % h.n_decl_addrless) if h.n_decl_addrless else ''))
    if len(rows) > max_classes:
        L.append('  ... 其余 %d 类见 --json' % (len(rows) - max_classes))
    if decision is not None:
        L.append('')
        L.append('-- 棘轮 --')
        L.append('  状态 %s（passed=%s improved=%s blocked=%s）'
                 % (decision.state, decision.passed, decision.improved, decision.blocked))
        for n in decision.notes[:max_findings]:
            L.append('  ✗ %s' % n)
    if result.findings:
        L.append('')
        L.append('-- 发现项（前 %d/%d）--' % (min(max_findings, len(result.findings)),
                                             len(result.findings)))
        for f in result.findings[:max_findings]:
            L.append('  · %s' % f)
    return '\n'.join(L) + '\n'


def _under_annotations(path):
    try:
        p = Path(path).resolve()
    except OSError:
        return False
    return p == _ANNOTATIONS_DIR or _ANNOTATIONS_DIR in p.parents


def main(argv=None):
    ap = argparse.ArgumentParser(description='vtable 声明校验（棘轮制）')
    ap.add_argument('--decls', required=True, help='codegen 生成头目录（**/*.h）')
    ap.add_argument('--structs', required=True, help='注解 struct 目录（只读 vtables）')
    ap.add_argument('--pending', default=None, help='Task 3 methods_pending JSON（旁路）')
    ap.add_argument('--model', choices=(MODEL_FLAT, MODEL_CHAIN), default=MODEL_FLAT)
    ap.add_argument('--baseline', default=None, help='棘轮基线 JSON（存在即对比）')
    ap.add_argument('--write-baseline', action='store_true',
                    help='放行时写回基线（上升/持平）。默认不写：并行环境下避免争用同一文件'
                         '；**必须**与 --baseline 同时给出')
    ap.add_argument('--json', dest='json_out', default=None, help='报告 JSON 输出路径')
    ap.add_argument('--quiet', '-q', action='store_true')
    args = ap.parse_args(argv)

    if args.write_baseline and not args.baseline:
        # Q2（静默关闸）：旧实现下 `--write-baseline` 无 `--baseline` ⇒ exit 0、不落盘、
        # 无告警；而无基线 ⇒ decision is None ⇒ **一切运行恒 exit 0**（门禁永久静默关闭）。
        print('ERROR: --write-baseline 必须与 --baseline 同时给出'
              '（否则基线永不落盘 ⇒ 无基线可比 ⇒ 棘轮静默关闭、一切运行恒放行）',
              file=sys.stderr)
        return 2

    for p in (args.decls, args.structs):
        if not Path(p).is_dir():
            print('ERROR: 目录不存在：%s' % p, file=sys.stderr)
            return 2
    for p in (args.baseline, args.json_out):
        if p and _under_annotations(p):
            print('ERROR: 拒绝写入注解目录（%s）—— 本工具只读 data/annotations/**' % p,
                  file=sys.stderr)
            return 2

    try:
        decls = load_decl_dir(args.decls)
        structs = load_structs_dir(args.structs)
        pending = load_pending(args.pending) if args.pending else {}
    except (OSError, ValueError) as e:
        print('ERROR: 输入读取失败：%s' % e, file=sys.stderr)
        return 2

    result = check_all(decls, structs, pending=pending, model=args.model)

    decision = None
    baseline = None
    if args.baseline and Path(args.baseline).exists():
        try:
            baseline = json.loads(Path(args.baseline).read_text(encoding='utf-8'))
        except (OSError, ValueError) as e:
            print('ERROR: 基线读取失败：%s' % e, file=sys.stderr)
            return 2
        decision = ratchet_decide(baseline, build_baseline(result))

    if not args.quiet:
        sys.stdout.write(render_report(result, decision))

    if args.json_out:
        # Q5：目标目录不存在必须归 rc=2（输入/写入错误），不得抛未捕获 FileNotFoundError
        # 并以 exit 1 退场 —— 那与"棘轮阻塞（rc=1）"**同信号**（假红/假阻塞）。
        try:
            Path(args.json_out).write_text(
                json.dumps(report_to_dict(result, decision), ensure_ascii=False, indent=2,
                           sort_keys=True),
                encoding='utf-8')
        except OSError as e:
            print('ERROR: 报告写入失败（%s）：%s' % (args.json_out, e), file=sys.stderr)
            return 2

    if args.write_baseline and args.baseline:
        if decision is None or decision.passed:
            payload = build_baseline(result, generated_at=date.today().isoformat())
            try:
                Path(args.baseline).write_text(
                    json.dumps(payload, ensure_ascii=False, indent=2, sort_keys=True),
                    encoding='utf-8')
            except OSError as e:
                print('ERROR: 基线写入失败（%s）：%s' % (args.baseline, e), file=sys.stderr)
                return 2
            if not args.quiet:
                print('[棘轮] 已写基线 %s' % args.baseline)
        elif not args.quiet:
            print('[棘轮] 阻塞，基线未更新')

    if decision is not None and decision.blocked:
        if not args.quiet:
            print('[棘轮] BLOCKED：health 下降 ⇒ 回归检测')
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())