#!/usr/bin/env python3
"""
编译回归检测工具（**正式对账闸**）

**职责分工（2026-09-20 审计 P1-6）**：本仓有两个"编译回归门禁"——
* **本工具**：挂 `probe` 之后（`pipeline/cli.py:614`），基线 `data/status/baselines/latest.json`，
  做 `(code,msg)` 多重集比较、剔除 C1003 截断单元、识别 churn，支持 `--before/--after`、
  `--self-test`、`--save-baseline`。**这是"正式对账"入口**。
* `tools/compile_regression.py`：挂 `codegen all` 之后（`cli.py:455`），基线
  `data/status/compile_baseline.json`，只比 ok/fail，是"即时快照"闸；它读**缓存 census**，
  未跑 probe 时结果无意义。
两者**不是冗余**（触发时机与基线不同），但**命名未讲清**，清理时勿误删其一。

功能：
1. 存储和管理编译基线

功能：
1. 存储和管理编译基线
2. 对比当前构建输出与基线
3. 检测新失败、新错误、修复的文件
4. 生成回归报告

用法：
    python3 tools/regression_detector.py --save-baseline    # 保存当前为基线
    python3 tools/regression_detector.py --check            # 检查回归
    python3 tools/regression_detector.py --report           # 生成报告
"""

import argparse
import collections
import json
import os
import sys
from pathlib import Path
from datetime import datetime
from typing import Dict, List, Set, Tuple, Optional

PROJECT_ROOT = Path(__file__).parent.parent
STATUS_DIR = PROJECT_ROOT / "data" / "status"
BASELINES_DIR = STATUS_DIR / "baselines"
CENSUS_FILE = STATUS_DIR / "probe_census.json"
REPORT_DIR = PROJECT_ROOT / "pipeline" / "_logs" / "regression_detection"


class Baseline:
    """编译基线数据结构"""
    
    def __init__(self, name: str, timestamp: str, results: Dict):
        self.name = name
        self.timestamp = timestamp
        self.results = results  # {unit: {"status": "ok"/"fail", "errors": [...], "error_count": N}}
    
    def to_dict(self) -> Dict:
        return {
            "name": self.name,
            "timestamp": self.timestamp,
            "results": self.results
        }
    
    @classmethod
    def from_dict(cls, data: Dict) -> 'Baseline':
        return cls(
            name=data["name"],
            timestamp=data["timestamp"],
            results=data["results"]
        )


class RegressionDetector:
    """编译回归检测器"""
    
    def __init__(self):
        self.baselines_dir = BASELINES_DIR
        self.baselines_dir.mkdir(parents=True, exist_ok=True)
        self.report_dir = REPORT_DIR
        self.report_dir.mkdir(parents=True, exist_ok=True)
    
    def load_census(self, path=None) -> Dict:
        """加载编译结果（默认当前 probe_census.json，可传归档的 census 路径）。"""
        target = Path(path) if path else CENSUS_FILE
        if not target.exists():
            raise FileNotFoundError(f"Census file not found: {target}")

        with open(target, 'r', encoding='utf-8') as f:
            data = json.load(f)

        return data
    
    def extract_results(self, census: Dict) -> Dict:
        """从census提取结果摘要"""
        results = {}
        
        for result in census.get("s2", {}).get("results", []):
            unit = result["unit"]
            status = result["status"]
            errors = result.get("errors", [])
            
            results[unit] = {
                "status": status,
                "error_count": len(errors),
                "errors": [
                    {
                        "code": e["code"],
                        "msg": e["msg"],
                        "line": e.get("line", 0)
                    }
                    for e in errors
                ]
            }
        
        return results
    
    def save_baseline(self, name: str = None) -> str:
        """保存当前编译结果为基线"""
        if name is None:
            name = datetime.now().strftime("%Y%m%d_%H%M%S")
        
        census = self.load_census()
        results = self.extract_results(census)
        
        baseline = Baseline(
            name=name,
            timestamp=datetime.now().isoformat(),
            results=results
        )
        
        # 保存基线文件
        baseline_file = self.baselines_dir / f"{name}.json"
        with open(baseline_file, 'w', encoding='utf-8') as f:
            json.dump(baseline.to_dict(), f, indent=2, ensure_ascii=False)
        
        # latest.json 一律写成**普通文件**（不是符号链接）。
        #
        # 历史缺陷（2026-09-15 清理工作 t5 第 1 项，发行阻断）：
        # 这里原来无条件 symlink_to，只在 OSError 时才回退到 copyfile。
        # 在 Linux 上 symlink_to **总是成功**，于是 index 变成 mode 120000，
        # 而 `latest.json` 的 blob 内容会是"路径串"——本仓历史上更糟：
        # 某次提交把 462044 字节的完整 JSON 当成了链接目标，
        # 于是 `git -c core.symlinks=true clone` 直接 exit 128（文件名过长），
        # 克隆后该路径甚至不存在。
        #
        # 现在改为：**始终写普通文件**，语义与 --check 的消费方式一致
        # （消费方只按路径读 JSON，不解析链接）。
        import shutil as _shutil
        latest_link = self.baselines_dir / "latest.json"
        if latest_link.is_symlink() or latest_link.exists():
            latest_link.unlink()
        _shutil.copyfile(str(baseline_file), str(latest_link))
        # 断言落地形态正确（防复发）：必须是普通文件，且可被 json.load
        import os as _os
        if _os.path.islink(str(latest_link)):
            raise RuntimeError(
                "latest.json was written as a symlink; it must be a regular file "
                "(see t5 symlink blocker). Path=%s" % latest_link)
        with open(str(latest_link), 'r', encoding='utf-8') as _vf:
            json.load(_vf)
        
        print(f"✅ 基线已保存: {baseline_file}")
        print(f"   总文件数: {len(results)}")
        print(f"   成功: {sum(1 for r in results.values() if r['status'] == 'ok')}")
        print(f"   失败: {sum(1 for r in results.values() if r['status'] == 'fail')}")
        
        return str(baseline_file)
    
    def load_baseline(self, name: str = None) -> Baseline:
        """加载基线"""
        if name is None:
            name = "latest"
        
        baseline_file = self.baselines_dir / f"{name}.json"
        if not baseline_file.exists():
            raise FileNotFoundError(f"Baseline not found: {baseline_file}")
        
        with open(baseline_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
        
        return Baseline.from_dict(data)
    
    def compare_with_baseline(self, baseline_name: str = None) -> Dict:
        """对比当前结果与基线"""
        baseline = self.load_baseline(baseline_name)
        current_census = self.load_census()
        current_results = self.extract_results(current_census)
        return self._compare(baseline.results, baseline.name,
                             baseline.timestamp, current_results)

    def compare_censuses(self, before_path: str, after_path: str = None) -> Dict:
        """直接对比两份 probe_census.json（A-B-A 落地校验的正路）。

        比 `--check` 更可靠：不经过 data/status/baselines/ 那套与
        compile_baseline 格式冲突的存储（该目录的 latest.json 由 probe/compile
        以另一套 schema 写入），而是拿"落地前归档的 census"直接对"当前 census"。
        """
        before_census = self.load_census(before_path)
        after_census = self.load_census(after_path or CENSUS_FILE)
        return self._compare(
            self.extract_results(before_census),
            os.path.basename(before_path),
            before_census.get("generated_at", "unknown"),
            self.extract_results(after_census),
            current_timestamp=after_census.get("generated_at"))

    @staticmethod
    def _truncated(unit_result: Dict) -> bool:
        """该单元的错误列表是否被编译器上限截断（C1003: error count exceeds 100）。

        被截断时这份列表**不是完整错误集**，任何"逐错误码净增减"都只是
        报告窗口的位移，不可当收益或回归。实测本仓库 15 个文件恰好 102 条
        且都带 C1003。
        """
        return any(e.get("code") == "C1003" for e in unit_result.get("errors", []))

    def _compare(self, baseline_results: Dict, baseline_name: str,
                 baseline_timestamp: str, current_results: Dict,
                 current_timestamp: str = None) -> Dict:
        # 检测变化
        #
        # R2 (2026-09-18)：旧实现用**下标切片**判断"新错误"——
        #     "new_errors": current["errors"][baseline_count:]
        # 即假定当前错误列表的前 baseline_count 条就是"旧错误"，其余为"新错误"。
        # 只要发生
        #     (a) 错误顺序变化，或
        #     (b) 修掉一条旧错误的同时引入一条新错误（总数不变，甚至总数下降），
        # 这个判据就完全看不见。实证：F1a/F1b/F3 落地后 `GameBase/PAL3.cpp` 的
        # C2660 从 31 涨到 36，但该文件**总错误数下降**（其它码修掉更多）
        # ⇒ 旧实现对此报 0 条新错误，正是本轮靠手工逐码对账才发现。
        #
        # 现在按 (code, msg) 的**多重集**比较，并且**忽略 line**：行号在 codegen
        # 变更后会整体漂移，按行号比会产生大批幻影增删。实测 3499 条 msg 中
        # 0 条含文件名或行号，故 (code, msg) 是稳定的错误身份。
        #
        # 另外补上**跨文件抵消**：同一个 (code,msg) 在 A 文件消失、在 B 文件出现，
        # 是"搬家"而非"修好+引入"——逐文件仍如实报告，但不计入回归/修复总数。
        new_failures = []        # 之前成功，现在失败
        new_errors = []          # 仍失败，但多出了**新的** (code,msg)
        fixed_files = []         # 之前失败，现在成功
        fixed_errors = []        # 仍失败，但**消失**了 (code,msg)
        unchanged_failures = []  # 持续失败
        error_count_changes = [] # 错误数量变化（保留旧字段，向后兼容）
        moved_errors = []        # 跨文件搬家的错误
        churn_errors = []        # 同码增删并存 = 报错文本/站点变化（非新错误种类）
        truncated_units = []     # C1003 截断：错误集不完整，逐码增减不可测

        def _multiset(errors):
            return collections.Counter((e["code"], e["msg"]) for e in errors)

        def _pick(errors, keys):
            """按 keys 里的 (code,msg) 从 errors 里取出带行号的可读条目。"""
            out = []
            for e in errors:
                if (e["code"], e["msg"]) in keys:
                    out.append({"code": e["code"], "msg": e["msg"],
                                "line": e.get("line", 0)})
            return out

        all_units = set(list(current_results.keys()) + list(baseline_results.keys()))

        # 第一遍：逐文件多重集差  gone = 基线有现值无, added = 现值有基线无
        per_unit = {}
        for unit in all_units:
            current = current_results.get(unit)
            baseline_unit = baseline_results.get(unit)
            if current is None or baseline_unit is None:
                continue
            before = _multiset(baseline_unit["errors"])
            after = _multiset(current["errors"])
            per_unit[unit] = (before - after, after - before)

        # 第二遍：全局层面找可抵消的 key（跨文件搬家）
        glob_gone, glob_added = collections.Counter(), collections.Counter()
        for gone, added in per_unit.values():
            glob_gone.update(gone)
            glob_added.update(added)
        cancellable = set(glob_gone) & set(glob_added)

        # 第三遍：分类
        for unit in all_units:
            current = current_results.get(unit)
            baseline_unit = baseline_results.get(unit)
            if current is None or baseline_unit is None:
                continue

            if baseline_unit["status"] == "ok" and current["status"] == "fail":
                new_failures.append({"unit": unit, "errors": current["errors"]})
                continue
            if baseline_unit["status"] == "fail" and current["status"] == "ok":
                fixed_files.append(unit)
                continue
            if current["status"] == "ok":
                continue

            unchanged_failures.append(unit)
            gone, added = per_unit[unit]

            # 把"搬家"的 key 摘出去，避免把搬家算成引入
            real_added = collections.Counter(
                {k: v for k, v in added.items() if k not in cancellable})
            real_gone = collections.Counter(
                {k: v for k, v in gone.items() if k not in cancellable})

            # 逐 (unit, code) 归因：同一错误码在**同一文件**里既消失又出现，
            # 说明这不是"新的错误种类"，而是同一个站点换了报错文本——
            # 最典型的形态是 msg 里嵌了实参类型，例如 F1b 恢复 `&` 之后
            #   "cannot convert parameter 1 from type 'struct gbMatrix4'"
            #   → "... from type 'struct gbMatrix4 *'"
            # 只有"出现数抵不掉消失数"的那部分才算真新增。
            gone_by_code = collections.Counter(k[0] for k in real_gone.elements())
            added_by_code = collections.Counter(k[0] for k in real_added.elements())
            genuine = {c: n - gone_by_code.get(c, 0)
                       for c, n in added_by_code.items()}
            genuine = {c: n for c, n in genuine.items() if n > 0}
            churn = {c: min(n, gone_by_code.get(c, 0))
                     for c, n in added_by_code.items()}
            churn = {c: n for c, n in churn.items() if n > 0}

            if genuine:
                new_errors.append({
                    "unit": unit,
                    "baseline_count": baseline_unit["error_count"],
                    "current_count": current["error_count"],
                    "genuine_count": sum(genuine.values()),
                    "by_code": genuine,
                    "new_errors": _pick(
                        current["errors"],
                        {k for k in real_added if k[0] in genuine}),
                })
            if churn:
                churn_errors.append({
                    "unit": unit,
                    "by_code": churn,
                    "examples": _pick(
                        current["errors"],
                        {k for k in real_added if k[0] in churn}),
                })
            if real_gone:
                fixed_errors.append({
                    "unit": unit,
                    "baseline_count": baseline_unit["error_count"],
                    "current_count": current["error_count"],
                    "fixed_errors": _pick(baseline_unit["errors"], set(real_gone)),
                })
            if baseline_unit["error_count"] != current["error_count"]:
                error_count_changes.append({
                    "unit": unit,
                    "baseline_count": baseline_unit["error_count"],
                    "current_count": current["error_count"],
                })
            if gone & added:
                moved_errors.append({
                    "unit": unit,
                    "keys": sorted("%s | %s" % k for k in (gone & added)),
                })

        # 逐错误码的净增减（会**明确标出增加**——这是旧实现完全看不到的一层）
        #
        # 注意：被 C1003 截断的单元必须排除。它们的错误列表是"前 ~100 条 + C1003"，
        # 修掉靠前的错误会让靠后的错误**从窗口外移入**，看起来像新增；反之亦然。
        # 实测 CCBStage.cpp 的 C2440 5->7 就是这种位移（L3536/L3540 的源码
        # 前后逐字未变），所以它是窗口/错误恢复位移，不是引入的缺陷。
        code_delta = collections.Counter()
        for unit in all_units:
            b = baseline_results.get(unit)
            c = current_results.get(unit)
            if b is None or c is None:
                continue
            if self._truncated(b) or self._truncated(c):
                truncated_units.append({
                    "unit": unit,
                    "baseline_count": len(b.get("errors", [])),
                    "current_count": len(c.get("errors", [])),
                    "reason": "C1003 截断：错误集不完整，逐码增减不可测",
                })
                continue
            code_delta.update(collections.Counter(
                e["code"] for e in c["errors"]))
            code_delta.subtract(collections.Counter(
                e["code"] for e in b["errors"]))
        # 被截断单元里的新/消失错误同样不可测，一并从归因里剔除
        trunc_names = {t["unit"] for t in truncated_units}
        new_errors = [e for e in new_errors if e["unit"] not in trunc_names]
        fixed_errors = [e for e in fixed_errors if e["unit"] not in trunc_names]
        churn_errors = [e for e in churn_errors if e["unit"] not in trunc_names]
        code_delta = {k: v for k, v in code_delta.items() if v != 0}
        increased_codes = sorted(k for k, v in code_delta.items() if v > 0)

        return {
            "baseline": baseline_name,
            "baseline_timestamp": baseline_timestamp,
            "current_timestamp": current_timestamp or datetime.now().isoformat(),
            "summary": {
                "total_files": len(all_units),
                "new_failures": len(new_failures),
                "new_errors": len(new_errors),
                "fixed_files": len(fixed_files),
                "fixed_errors": len(fixed_errors),
                "unchanged_failures": len(unchanged_failures),
                "moved_errors": len(moved_errors),
                "churn_errors": len(churn_errors),
                "increased_codes": increased_codes,
                "truncated_units": len(truncated_units),
            },
            "new_failures": new_failures,
            "new_errors": new_errors,
            "fixed_files": fixed_files,
            "fixed_errors": fixed_errors,
            "unchanged_failures": unchanged_failures,
            "error_count_changes": error_count_changes,
            "moved_errors": moved_errors,
            "churn_errors": churn_errors,
            "truncated_units": truncated_units,
            "code_delta": dict(sorted(code_delta.items(),
                                      key=lambda kv: kv[1])),
        }
    
    def generate_report(self, comparison: Dict, output_format: str = "text") -> str:
        """生成回归报告"""
        if output_format == "json":
            return self._generate_json_report(comparison)
        else:
            return self._generate_text_report(comparison)
    
    def _generate_text_report(self, comparison: Dict) -> str:
        """生成文本报告"""
        lines = []
        lines.append("=" * 80)
        lines.append("编译回归检测报告")
        lines.append("=" * 80)
        lines.append(f"基线: {comparison['baseline']}")
        lines.append(f"基线时间: {comparison['baseline_timestamp']}")
        lines.append(f"检测时间: {comparison['current_timestamp']}")
        lines.append("")
        
        summary = comparison["summary"]
        lines.append("📊 摘要:")
        lines.append(f"  总文件数: {summary['total_files']}")
        lines.append(f"  新失败: {summary['new_failures']}")
        lines.append(f"  新错误(真新增 (code,msg)): {summary['new_errors']}")
        lines.append(f"  已修复: {summary['fixed_files']}")
        lines.append(f"  错误收敛(消失 (code,msg)): {summary.get('fixed_errors', 0)}")
        lines.append(f"  持续失败: {summary['unchanged_failures']}")
        if summary.get("truncated_units"):
            lines.append(f"  ⚠️ C1003 截断单元(逐码增减不可测): "
                         f"{summary['truncated_units']}")
        if summary.get("moved_errors"):
            lines.append(f"  跨文件搬家: {summary['moved_errors']}")
        lines.append("")

        # 逐错误码净增减 —— 旧实现只看"文件总错误数是否上涨"，
        # 因而完全看不到「总数下降但某个码上涨」这种形态。
        code_delta = comparison.get("code_delta") or {}
        if code_delta:
            lines.append("🔢 逐错误码净增减 (正=增加，负=减少):")
            lines.append("-" * 40)
            for code, delta in sorted(code_delta.items(),
                                      key=lambda kv: -abs(kv[1]))[:15]:
                flag = "  ⚠️ 增加" if delta > 0 else ""
                lines.append(f"  {code:<8} {delta:+d}{flag}")
            inc = summary.get("increased_codes") or []
            if inc:
                lines.append(f"  ⚠️ 注意: 以下错误码**净增** {', '.join(inc)}"
                             f" —— 即使总错误数在下降也要逐条归因")
            lines.append("")
        
        # 新失败
        if comparison["new_failures"]:
            lines.append("❌ 新失败 (之前成功，现在失败):")
            lines.append("-" * 40)
            for failure in comparison["new_failures"]:
                lines.append(f"  {failure['unit']}")
                for error in failure["errors"][:3]:  # 只显示前3个错误
                    lines.append(f"    L{error['line']}: {error['code']} - {error['msg'][:60]}")
                if len(failure["errors"]) > 3:
                    lines.append(f"    ... 还有 {len(failure['errors']) - 3} 个错误")
            lines.append("")
        
        # 新错误
        if comparison["new_errors"]:
            lines.append("⚠️  真新增错误 (同码出现数抵不掉消失数):")
            lines.append("-" * 40)
            for error_info in comparison["new_errors"]:
                lines.append(f"  {error_info['unit']}")
                lines.append(f"    错误数: {error_info['baseline_count']} -> "
                             f"{error_info['current_count']}  真新增 "
                             f"{error_info.get('genuine_count', '?')} "
                             f"{error_info.get('by_code', {})}")
                for error in error_info["new_errors"][:5]:
                    lines.append(f"    新增 L{error['line']}: {error['code']} - "
                                 f"{error['msg'][:70]}")
            lines.append("")

        # 报错文本/站点变化（同码增删并存）
        if comparison.get("churn_errors"):
            lines.append("🔁 报错文本/站点变化 (同码增删并存 —— 不是新的错误种类，"
                         "常见于 msg 里嵌了实参类型):")
            lines.append("-" * 40)
            for info in comparison["churn_errors"]:
                lines.append(f"  {info['unit']}: {info['by_code']}")
            lines.append("")

        # 错误收敛（仍失败，但消失了一批错误）
        if comparison.get("fixed_errors"):
            lines.append("🔧 错误收敛 (仍失败，但部分错误消失):")
            lines.append("-" * 40)
            for info in comparison["fixed_errors"][:15]:
                lines.append(f"  {info['unit']}: {info['baseline_count']} -> "
                             f"{info['current_count']}  (消失 {len(info['fixed_errors'])})")
            lines.append("")

        # 跨文件搬家
        if comparison.get("moved_errors"):
            lines.append("🔀 跨文件搬家 (同一 (code,msg) 在别处消失/出现，非引入):")
            lines.append("-" * 40)
            for info in comparison["moved_errors"][:10]:
                lines.append(f"  {info['unit']}")
                for k in info["keys"][:3]:
                    lines.append(f"    {k[:90]}")
            lines.append("")
        
        # 已修复
        if comparison["fixed_files"]:
            lines.append("✅ 已修复 (之前失败，现在成功):")
            lines.append("-" * 40)
            for unit in comparison["fixed_files"]:
                lines.append(f"  {unit}")
            lines.append("")
        
        # 错误数量变化
        if comparison["error_count_changes"]:
            lines.append("📈 错误数量变化:")
            lines.append("-" * 40)
            for change in comparison["error_count_changes"]:
                direction = "↓" if change["current_count"] < change["baseline_count"] else "→"
                lines.append(f"  {change['unit']}: {change['baseline_count']} {direction} {change['current_count']}")
            lines.append("")
        
        # 判断是否有回归。判据比旧实现严：
        #   ① 有文件 ok->fail，或
        #   ② 有**真新增**错误（同码增删抵消后仍多出来的），或
        #   ③ 任一错误码**净增**（文件总错误数下降也挡不住这一条）
        has_regression = (summary["new_failures"] > 0
                          or summary["new_errors"] > 0
                          or bool(summary.get("increased_codes")))
        if has_regression:
            lines.append("🚨 需要归因：存在新失败 / 真新增错误 / 净增错误码 "
                         "—— 请逐条说明来源。")
        else:
            lines.append("✅ 未检测到回归。")
        
        return "\n".join(lines)
    
    def _generate_json_report(self, comparison: Dict) -> str:
        """生成JSON报告"""
        return json.dumps(comparison, indent=2, ensure_ascii=False)
    
    def save_report(self, comparison: Dict, format: str = "text") -> str:
        """保存报告到文件"""
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        
        if format == "json":
            report_file = self.report_dir / f"regression_{timestamp}.json"
            content = self._generate_json_report(comparison)
        else:
            report_file = self.report_dir / f"regression_{timestamp}.txt"
            content = self._generate_text_report(comparison)
        
        with open(report_file, 'w', encoding='utf-8') as f:
            f.write(content)
        
        return str(report_file)


def _self_test() -> int:
    """自检：只依赖合成 census，不依赖仓库状态（见 CLAUDE.md 的用例纪律）。

    覆盖三个曾让结论说假话的形态：
      ① 同一文件"总数不变但错误种类换了"（旧实现的下标切片看不见）
      ② 同码增删并存 = 报错文本变化，不得算作新错误种类
      ③ C1003 截断单元必须从逐码统计里剔除
    """
    def unit(name, status, errs):
        return {"unit": name, "status": status,
                "errors": [{"file": name, "line": l, "code": c, "msg": m}
                           for (l, c, m) in errs]}

    det = RegressionDetector.__new__(RegressionDetector)  # 不触碰文件系统
    before = {
        "a.cpp": {"status": "fail", "error_count": 2,
                  "errors": [{"code": "C2100", "msg": "illegal indirection", "line": 10},
                             {"code": "C2660", "msg": "'F' : does not take 3", "line": 20}]},
        # 总数不变，但 C2100 -> C2664：旧实现报 0 条新错误
        "b.cpp": {"status": "fail", "error_count": 1,
                  "errors": [{"code": "C2100", "msg": "x", "line": 5}]},
        # 同码增删并存（msg 里嵌了类型）
        "c.cpp": {"status": "fail", "error_count": 1,
                  "errors": [{"code": "C2665", "msg": "from 'struct T'", "line": 7}]},
        # C1003 截断
        "d.cpp": {"status": "fail", "error_count": 2,
                  "errors": [{"code": "C1003", "msg": "error count exceeds 100", "line": 0},
                             {"code": "C2440", "msg": "z", "line": 9}]},
    }
    after = {
        "a.cpp": {"status": "ok", "error_count": 0, "errors": []},
        "b.cpp": {"status": "fail", "error_count": 1,
                  "errors": [{"code": "C2664", "msg": "y", "line": 5}]},
        "c.cpp": {"status": "fail", "error_count": 1,
                  "errors": [{"code": "C2665", "msg": "from 'struct T *'", "line": 7}]},
        "d.cpp": {"status": "fail", "error_count": 3,
                  "errors": [{"code": "C1003", "msg": "error count exceeds 100", "line": 0},
                             {"code": "C2440", "msg": "z", "line": 9},
                             {"code": "C2440", "msg": "w", "line": 11}]},
    }
    r = det._compare(before, "synthetic", "t0", after)
    fails = []
    def chk(cond, msg):
        if not cond:
            fails.append(msg)

    chk(r["summary"]["fixed_files"] == 1, "a.cpp 应记为已修复")
    chk(any(e["unit"] == "b.cpp" and e["by_code"] == {"C2664": 1}
            for e in r["new_errors"]),
        "② b.cpp 的同码换种必须报成真新增（旧实现漏报）")
    chk(not any(e["unit"] == "c.cpp" for e in r["new_errors"]),
        "③ c.cpp 只是报错文本变化，不得算真新增")
    chk(any(e["unit"] == "c.cpp" for e in r["churn_errors"]),
        "③ c.cpp 应出现在 churn 里")
    chk(not any(e["unit"] == "d.cpp" for e in r["new_errors"]),
        "④ d.cpp 被 C1003 截断，不得算真新增")
    chk(r["summary"]["truncated_units"] == 1, "④ 应识别出 1 个截断单元")
    chk("C2440" not in r["code_delta"], "④ 截断单元的逐码增减必须剔除")
    chk(r["code_delta"].get("C2100") == -2, "a/b 的 C2100 净减应为 -2")

    for f in fails:
        print("  ❌ %s" % f)
    print("自检: %s (%d 项)" % ("全部通过" if not fails else "失败", 7))
    return 1 if fails else 0


def main():
    parser = argparse.ArgumentParser(description="编译回归检测工具")
    parser.add_argument("--save-baseline", action="store_true", help="保存当前结果为基线")
    parser.add_argument("--baseline-name", help="基线名称")
    parser.add_argument("--check", action="store_true", help="检查回归")
    parser.add_argument("--report", action="store_true", help="生成报告")
    parser.add_argument("--before", help="落地前归档的 probe_census.json（A-B-A 用）")
    parser.add_argument("--after", help="落地后的 probe_census.json（默认 data/status/probe_census.json）")
    parser.add_argument("--format", choices=["text", "json"], default="text", help="报告格式")
    parser.add_argument("--output", help="输出文件路径")
    parser.add_argument("--self-test", action="store_true", help="跑内置自检（不依赖仓库状态）")

    args = parser.parse_args()

    if args.self_test:
        return _self_test()
    
    detector = RegressionDetector()
    
    try:
        if args.save_baseline:
            detector.save_baseline(args.baseline_name)
            return 0
        
        if args.before:
            comparison = detector.compare_censuses(args.before, args.after)
            report = detector.generate_report(comparison, args.format)
            if args.output:
                with open(args.output, 'w', encoding='utf-8') as f:
                    f.write(report)
                print(f"✅ 报告已保存: {args.output}")
            else:
                print(report)
            # 任一错误码**净增**即需归因，而不只是"文件总错误数上涨"
            has_regression = (comparison["summary"]["new_failures"] > 0
                              or comparison["summary"]["new_errors"] > 0
                              or bool(comparison["summary"].get("increased_codes")))
            return 1 if has_regression else 0

        if args.check or args.report:
            comparison = detector.compare_with_baseline(args.baseline_name)
            
            if args.output:
                report_file = detector.save_report(comparison, args.format)
                print(f"✅ 报告已保存: {report_file}")
            else:
                report = detector.generate_report(comparison, args.format)
                print(report)
            
            # 返回码：有回归返回1，无回归返回0
            has_regression = comparison["summary"]["new_failures"] > 0 or comparison["summary"]["new_errors"] > 0
            return 1 if has_regression else 0
        
        # 默认：显示帮助
        parser.print_help()
        return 0
        
    except Exception as e:
        print(f"❌ 错误: {e}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
