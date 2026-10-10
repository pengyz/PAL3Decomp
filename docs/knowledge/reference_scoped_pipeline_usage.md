# reference · 射程管线（scoped pipeline）用法与已验证能力

**type**: reference
**created**: 2026-10-10
**confidence**: high（端到端实测，非估算）

## 一句话
把「验证一个函数的字节一致性」从 ~6 分钟（全量管线）降到 **~30 秒**，通过只反编译/生成/编译/比对目标。

## 已验证能力（端到端实测，2026-10-10）

| 能力 | 命令 | 实测 | 状态 |
|---|---|---|---|
| **生成确定性** | （S-1，无开关）| 3 个 `PYTHONHASHSEED` 输出逐字节同 | ✅ |
| **头事实缓存化** | `data/status/_decomp_derived_header_facts.json` | 739 头 A/B **0 差异** | ✅ |
| **export 射程** | `EXPORT_FUNC=0x429ee0 EXPORT_OUTDIR=/tmp/x python pipeline/cli.py export` | **16.5s** vs 148.5s = **9×**（1 函数）| ✅ |
| **codegen 射程** | `CODEGEN_CLASS=Object3D python pipeline/gen/codegen.py all --skip-probe` | **28.3s** vs 2m30s = **5.3×**（cpp 210→2，头 739 全量）| ✅ |
| probe/match 射程 | `PROBE_ONLY=… MATCH_SCOPED=…` | ❌ **6 次尝试未通** | ⛔ |

## 用法

### export 射程（只反编译目标函数）
```bash
# 按地址（写独立目录，主 asm/pal3/decomp/ 零污染）
EXPORT_FUNC=0x429ee0 EXPORT_OUTDIR=/tmp/scoped python pipeline/cli.py export

# 按类（该类全部方法）
EXPORT_CLASS=Object3D EXPORT_OUTDIR=/tmp/scoped python pipeline/cli.py export
```
**⚠️ `EXPORT_OUTDIR` 必填** —— 缺失会报错（射程必须写独立目录，否则静默覆盖主产物）。

### codegen 射程（只生成目标 TU 的 .cpp，头全量）
```bash
CODEGEN_CLASS=Object3D python pipeline/gen/codegen.py all --skip-probe
# 产物：cpp 210 -> 2，头 739 全量（依赖闭包天然满足）
```

### 头事实缓存（射程 export 不污染头决策）
```bash
python pipeline/cli.py export    # 全量 export 末尾自动写缓存
# 缓存：data/status/_decomp_derived_header_facts.json
#   scalar_dtor_classes(60) / underscore_aliases(2) / forced_global_names(12855) / vptr_inject_classes(60)
```
**缓存缺失时报错退出，不静默回退到目录扫描**（回退会让射程 export 污染头决策）。

## 加速比的真实曲线（不是「9×」通用数字）

| 射程规模 | export 耗时 | 加速比 |
|---|---|---|
| 1 函数 | 16.2s | 9.2× |
| 25 函数（Object3D 类）| 16.9s | 8.8× |
| 233 函数（PalScript 类）| 19.8s | 7.5× |

**⇒ idat 启动固定 ~16s，边际 ~0.015s/函数。规模越大加速比越快逼近 1×。**
「9×」只适用**单函数/极小类**级别射程。

## 已知边界
- **probe/match 射程未通**（6 次尝试）—— 见 `gotcha_wiring_type_changes_test_green_is_zero_evidence.md`
- 射程 `match` 的输出隔离已设计（`s4_scoped_<target>.json`，禁覆 `s4_baseline.json`）但未端到端验
- `collect.py` 里的旧 `resolve_targets`/`scoped_decomp_dir` 已废弃（用 `scoped_targets.py`）

## 相关
- 计划：`docs/superpowers/plans/2026-10-09-scoped-pipeline-impl.md`
- 设计：`docs/superpowers/plans/2026-10-09-scoped-pipeline.md`
- 6 次失败教训：`docs/knowledge/gotcha_wiring_type_changes_test_green_is_zero_evidence.md`
