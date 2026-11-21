# plan · dtor 发射意图改造完备性方案（2026-11-21，T4 对抗复核后定稿）

> 依据：对抗复核结报（子agent 只读复核，120 次工具调用，HEAD=e656175bd）+
> methodology_dtor_governance_20261121.md + N20 门禁。**本文件=改造战役单一真值源。**

## 〇、模型定谳（勘误）

**??_G 载体 = MSVC 合成**（合成模型定谳，纠正 d17eda1df 提交语的"wrapper 体直出"表述）：

```
??_G 匹配 = virtual ~Cls() 头声明（flags 通道：methods.flags ∪ vtable slot.flags；
            header_facts.scalar_dtor_classes 仅影响 vptr 注入分支）
          + TU 内存在一个 dtor 定义（完全形 ~Cls() 定义；
            或删除式经 P-A5 改名 + N18 源级化成 ~Cls() 定义）
          → MSVC 自源合成 ??1 + ??_G → S4 字节匹配
```

铁证：RoleCameraCtrl ??_G@0x450AB0 match_L1 100.0%，而其 wrapper 单元从未发射
（collect 跳过）——定义来自完全形 0x450a25。12/12 相关性的真机制=压制→单元不生成
→类掉出 scalar_dtor_classes→virtual 声明消失→合成停止；恢复→单元回归→声明回归
+完全形定义→合成恢复。??_E（向量形）注册表 0 行=无需覆盖。

## 一、改造点完备清单（D1..D21）

【改】=方案覆盖；【察】=现存异常需知悉；【保】=确认合法保留。

| # | 位置 | 当前行为 | 改造后 | 依赖 |
|---|---|---|---|---|
| D1【改】 | collect.py:245-246 | `_scalar_dtor/_vector_dtor/_sdtor` 泛化 continue | 删除；backtick/`_scalar_dtor` 命名单元按名路由携 vintage 标签；决策移交意图函数；**无意图数据的删除式单元显式拒发+计数**（非无条件放行） | S2 |
| D2【改】 | collect.py:161-164 | 空单元/`sub_` 静默 continue | 保留跳过但计数可见 | 独立可先行 |
| D3【改】 | collect.py:227-232 + normalization.py:43-47 | backtick 改名+体重写 | 保留（机械层合法），归一化后名+原名 vintage 传下游 | D1 |
| D4【改】 | emit_cpp.py:904-922 | 三重 decl_only 消费（含 L911-922 直读注解） | 收编为单点 `intent.body_emit` 查询 | D10 |
| D5【改】 | emit_cpp.py:1125-1126 | 自由函数 make_context 不传 flags | 走意图函数 | D12 |
| D6【改】 | transform.py:37-48 | is_dtor 三门判定（名等值/返型启发式/flags） | 意图函数给出 name/n18_strip，make_context 只消费；**消 `[] is not None` 陷阱**（类通路 sig 启发式当前是死代码） | D10 |
| D7【改】 | stage1_structural.py:316-330,448-505 | `_is_del_dtor` 自判 | 消费 `intent.n18_strip`；4c 逻辑保留 | D6 |
| D8【改】 | emit_headers.py:3304-3311 | 槽循环 flags 判 dtor→virtual 声明 | 判据换 `intent.decl_virtual`；has_dtor_decl 所有权保留 | D10 |
| D9【改】 | emit_headers.py:3651-3662 | 方法循环发**非 virtual** dtor 声明（F5 31 类出处） | 意图函数决定 virtual；F5 根修仍需槽5证据注解 | D10 |
| D10【改】 | 新模块 pipeline/gen/dtor_intent.py | 无 | `resolve_dtor_intent` 单点（见三） | — |
| D11【改】 | emit_headers.py:4010-4011 G1b | decl_only 非 DLL 不发声明 | dtor 条目改走意图函数（尊重 has_dtor_decl 防双声明） | D8/D10 |
| D12【改】 | emit_cpp.py:1088-1123 | 自由函数发射器无 dtor 特判——**活体：free_functions.cpp:3686 `sdtor_15` 裸 wrapper 在发射** | functions.json 7 条 class-less `_sdtor_NN` 意图分类 | D10 |
| D13【察】 | emit_headers.py:202-217 + _decomp_derived_header_facts.json | **缓存陈旧 12 天（80 vs fresh 27 类）**，注入通路运行在过期事实上 | S1 前必须全量 export 刷缓存；长期收编进意图函数事实查询 | 先行 |
| D14【改】 | check_annotations.py:2093-2100 N20 | 只扫 methods 不扫 vtable slots；跨类注册不可见；ParticleEffect 0x4bc790 完全形误标 deleting（N20c 伪阳） | 扩槽扫描 + sig-vs-deleting 交叉核 | D10 |
| D15【察】 | export_full.py:418-453 | decl_only/type=skip 派生 skip_addrs（今日落地） | suppressed 定义须与意图函数同源（防双文件再漂移） | D10 |
| D16【察】 | export_full.py:518 | 预改名 mangle 缺 deleting= 透传 | 有 None 拒绝护栏兜住，意图化后统一 | 低优 |
| D17【察】 | skip_functions.json 遗留层 | **4 个 N20c 删除式单元被 legacy skip 键挡在 export 外**（UIWnd 0x445b20/CPK 0x53c2b0/CCBPanelSlot 0x4431b0/UIScene 0x43be10）→ N20c"未压制"与 export 层矛盾 | S3 前显式清算 4 条 | S3 前置 |
| D18【察】 | tables.py:60-63 `_SYNTH_PAT` | 匹配 `_scalar_dtor_`（带尾下划线）不匹配裸名 | 意图收编后降级为检测器 | D10 |
| D19【保】 | stage5/stage3/ast_transform/compare_pal3/vc6_mangler 的 dtor 名族处理 | 机械层合法 | normalize 副本（实测 4 份）逐步收编，非阻塞 | 后续 |
| D20【察】 | apply_annotations.py:3246-3259 | IDB 侧 dtor_Class 命名 | 与注解名槽律分属两层，暂不动 | — |
| D21【察】 | stage1_structural.py:448-505 4c | return this 剥离不认 `(Cls*)this;` cast 形（ScreenEffectMgr.cpp:682 活体残留） | 4c 表达式补一形态 | D7 |

## 二、顺序方案（修订：S0 → (S1 ∥ S2) → S3）

- **S0（新前置，不做则 S3 验证不可解释）**：
  ① 跨类 dtor 名判据修复——CameraCtrl 注解名 `~GameObject`（继承槽）≠ TU 类名，
  transform.py:39 名字等值先短路→flags 不被咨询→is_dtor=False→N18 死；
  **CameraCtrl.cpp:151 的 `~GameObject(int)` 非法形现仍在树上**（非实验残留）；
  ② legacy skip_functions 对 4 个 N20c 单元的 shadow 压制清算（D17）；
  ③ header_facts 全量 export 刷新（D13，80↔27 差 65 类）。
- **S1（emit_headers 四点接线 D8/D9/D11/D13→意图函数）与 S2（注解数据批）互不依赖，可并行**。
  原 S1"decl_only 契约修复"表述作废——decl_only 不切断 virtual（flags 通道独立）；
  F5 31 类缺的是槽证据注解，非本点可解。
- **S2 真前置，范围=H-set 11 类**（"另一条 dtor 定义将发射 + 本删除式未压制 + decomp 在场"）：
  CCBResultWindow/CCBUIPanel/JusticeBookUI/Role/RoleCameraCtrl/TaskBookUI/UILoadingFrm/
  UIRoleDialog/UISceneMap/UITitle/ParticleEffect（末者 0x4bc790 误标 deleting）。
  意图=wrapper 形 decl_only（依赖 S1 后声明/virtual 照发）+源形 full。
  **S3 先于 S2 = 10 个刚恢复的 L1 ??_G 再丢 + ParticleEffect C2084（上次实验 −10 实证）**。
- **S3 collect 去过滤（D1）**：36 N20c 逐类实证路径——~15 backtick 类注解名/flags 齐
  →P-A5+N18→合法定义（UIProgressBar 残丢就此闭合）；~17 已在发射无变化；
  4 shadow-blocked 待 D17；CameraCtrl 待 S0①；unannotated backtick 单元（与注解覆盖差集）
  →显式拒发+计数。**逐类白名单放量（CODEGEN_CLASS）后全量**。

## 三、公共函数（D10）

新模块 `pipeline/gen/dtor_intent.py`。纯函数核（零文件直读），事实经 annotation_view
（struct_by_class 单一读点）+ ida_structs flags 通道 + header_facts 注入为普通 dict。
数据查询与决策逻辑严格分层。

```python
@dataclass(frozen=True)
class DtorIntent:
    role: str              # 'complete_def'|'deleting_source'|'declaration_only'|'suppressed'|'orphan_free'
    body_emit: bool
    decl_emit: bool
    decl_virtual: bool
    decl_inline: bool      # 注入形 virtual ~Cls() {} vs 槽循环 ; 形
    name: str              # 规范 '~Cls'（跨类 ~GameObject 在此规范化/拒收）
    definition_owner: str  # 唯一源律仲裁（拥有 TU 定义的条目地址）
    n18_strip: bool
    reason: str            # 可审计判定理由

def resolve_dtor_intent(*, cls, entry_addr, entry, siblings, unit_present,
                        unit_vintage, flags_channel, header_facts_scalar,
                        s4_symbols=None) -> DtorIntent: ...
```

消费方：collect L245（D1）、emit_cpp L904-922（D4）/L1125（D12）、transform L37-48（D6）、
stage1 L316-330（D7）、emit_headers L3304/L3651/L4010/L3181（D8/D9/D11）、
export_full L418-453（D15）、check_annotations N20（D14）。
has_dtor_decl 所有权机制保留（头内生产者不相交，与跨 TU 意图正交）。

迁移：①模块+表驱动单测先行（红）→②emit_headers 接线（绿）→③H-set 注解批→
④collect 去过滤（白名单放量）→⑤normalize 副本归一（非阻塞）。

## 四、TDD 测试矩阵（T1..T14）

| # | 名称 | 断言要点 | 覆盖 |
|---|---|---|---|
| T1 | test_intent_vintage_matrix | 同一删除式单元×5 命名 vintage×有无注解 → role/name 唯一正确；无注解 backtick→拒发+reason | D1/D3/D10 |
| T2 | test_dual_form_single_owner | Role 3 兄弟+CCBResultWindow 对 → 恰 1 条 body_emit；VA 级仲裁同 N20 | D10/D14 |
| T3 | test_no_complete_form_abi | CEffObj：decl_emit+virtual=True，body_emit=False | D8/D11 |
| T4 | test_decl_only_dll_import | 非 dtor 借用体维持；dtor 走意图 | D11 |
| T5 | test_suppressed_pipeline_consistency | type=skip ≡ export 派生 ≡ N20 分类三方一致 | D14/D15 |
| T6 | test_cross_class_slot_registration | RTN slot 0x4bd850 归属；N20 扩槽 | D14 |
| T7 | test_icf_folded_slots | UIListBox 5 dtor 条目恰 1 声明；`_scalar_dtor_DCF0` 形名识别 | D8/D18 |
| T8 | test_collect_counts_visible | 去过滤后跳过/拒发/直通计数输出 | D2/D3 |
| T9 | test_n18_gate_pure | flags deleting+~Cls→strip；~GameObject 跨类拒收；`[]` 陷阱消除 | D6/D7 |
| T10 | test_e2e_uiprogressbar | 单类 codegen：.cpp 合法 `~UIProgressBar()`（无参/无 return this/无条件 delete）+.h virtual 声明 | 全链 |
| T11 | test_e2e_role_single_def | .cpp 恰 1 条 `~Role()`；兄弟零发射 | H-set |
| T12 | test_free_dtor_not_leaked | free_functions.cpp 不再含裸 wrapper（当前红：sdtor_15@L3686 活体） | D12 |
| T13 | test_vector_dtor_absence_pin | corpus 0 vector 单元；构造用例拒发 | D1/D19 |
| T14 | test_n20_gate_extended | slot-only dtor + sig-vs-deleting 交叉（0x4bc790 应报数据疑点） | D14 |

前置债：`test_hang3_nails::test_rename_fingerprint` 既有红（AStarPathFinder 指纹，
与本案无关）S3 前归因，避免记账到改造头上。

## 五、风险与 scoped 验证/回滚

| 改造点 | 爆炸半径 | scoped 验证 | 回滚 |
|---|---|---|---|
| S2 数据批 | 落地时零发射变化 | s4_baseline 行对比+N20a 静默 | 注解单 commit revert |
| S1 接线 | 全库头再生；C2535 前科(L3177) | 先刷 header_facts→CODEGEN_CLASS=UIProgressBar+PROBE_ONLY+MATCH_SCOPED 三档→全量 probe s2 | pipeline 单 commit |
| S3 去过滤 | 全库 .cpp 再生（上次 −10） | 36 类逐类白名单放量+拒发计数核对→全量 | collect 单点 revert+环境变量逃生门 |
| D13 刷缓存 | 头决策集抖动 | export 全量+diff 缓存文件逐类核对 | 重跑 export |

通用舞步不跳：probe s2 门+snapshot+compile_regression+门链（cli.py:549-623）。

## 六、对抗复核纠正清单（自我纠错留档）

1. "wrapper 体=??_G 载体"模型错——合成模型定谳（S4 铁证：RoleCameraCtrl wrapper 未发射仍 100%）
2. S1 前置地位错——decl_only 不切断 virtual（flags 独立通道）
3. CameraCtrl 失败根因不全——真门=跨类注解名 ~GameObject 名字等值短路，非法形现在树上
4. flags `[] is not None` 陷阱遗漏（类通路 sig 启发式=死代码）
5. legacy skip_functions shadow 压制 4 条遗漏（N20c 与 export 层矛盾）
6. header_facts 缓存陈旧 12 天遗漏
7. N20c WARN 文案失真（36 类中仅 ~15 真被跳过阻塞）
8. ParticleEffect 0x4bc790 完全形误标 deleting（N20c 伪阳+H-set 隐患）
9. 自由 dtor 泄漏（sdtor_15）未列入
10. normalization.py 头注自身漂移（data.py 副本已删仍被指认）
