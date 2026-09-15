#!/usr/bin/env python3
"""
编译回归检测工具

自动检测codegen变更引入的新编译失败或退化。

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
    
    def load_census(self) -> Dict:
        """加载当前编译结果"""
        if not CENSUS_FILE.exists():
            raise FileNotFoundError(f"Census file not found: {CENSUS_FILE}")
        
        with open(CENSUS_FILE, 'r', encoding='utf-8') as f:
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
        
        baseline_results = baseline.results
        
        # 检测变化
        new_failures = []      # 之前成功，现在失败
        new_errors = []        # 之前失败但错误更少，现在错误更多
        fixed_files = []       # 之前失败，现在成功
        unchanged_failures = [] # 持续失败
        error_count_changes = [] # 错误数量变化
        
        all_units = set(list(current_results.keys()) + list(baseline_results.keys()))
        
        for unit in all_units:
            current = current_results.get(unit)
            baseline_unit = baseline_results.get(unit)
            
            if current is None or baseline_unit is None:
                continue
            
            # 新失败
            if baseline_unit["status"] == "ok" and current["status"] == "fail":
                new_failures.append({
                    "unit": unit,
                    "errors": current["errors"]
                })
            
            # 修复的文件
            elif baseline_unit["status"] == "fail" and current["status"] == "ok":
                fixed_files.append(unit)
            
            # 持续失败
            elif baseline_unit["status"] == "fail" and current["status"] == "fail":
                unchanged_failures.append(unit)
                
                # 检查错误数量变化
                baseline_count = baseline_unit["error_count"]
                current_count = current["error_count"]
                
                if current_count > baseline_count:
                    new_errors.append({
                        "unit": unit,
                        "baseline_count": baseline_count,
                        "current_count": current_count,
                        "new_errors": current["errors"][baseline_count:]
                    })
                elif current_count != baseline_count:
                    error_count_changes.append({
                        "unit": unit,
                        "baseline_count": baseline_count,
                        "current_count": current_count
                    })
        
        return {
            "baseline": baseline.name,
            "baseline_timestamp": baseline.timestamp,
            "current_timestamp": datetime.now().isoformat(),
            "summary": {
                "total_files": len(all_units),
                "new_failures": len(new_failures),
                "new_errors": len(new_errors),
                "fixed_files": len(fixed_files),
                "unchanged_failures": len(unchanged_failures)
            },
            "new_failures": new_failures,
            "new_errors": new_errors,
            "fixed_files": fixed_files,
            "unchanged_failures": unchanged_failures,
            "error_count_changes": error_count_changes
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
        lines.append(f"  新错误: {summary['new_errors']}")
        lines.append(f"  已修复: {summary['fixed_files']}")
        lines.append(f"  持续失败: {summary['unchanged_failures']}")
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
            lines.append("⚠️  新错误 (错误数量增加):")
            lines.append("-" * 40)
            for error_info in comparison["new_errors"]:
                lines.append(f"  {error_info['unit']}")
                lines.append(f"    基线错误数: {error_info['baseline_count']}")
                lines.append(f"    当前错误数: {error_info['current_count']}")
                for error in error_info["new_errors"][:2]:
                    lines.append(f"    新增: {error['code']} - {error['msg'][:60]}")
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
        
        # 判断是否有回归
        has_regression = summary["new_failures"] > 0 or summary["new_errors"] > 0
        if has_regression:
            lines.append("🚨 检测到回归！请检查上述新失败和新错误。")
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


def main():
    parser = argparse.ArgumentParser(description="编译回归检测工具")
    parser.add_argument("--save-baseline", action="store_true", help="保存当前结果为基线")
    parser.add_argument("--baseline-name", help="基线名称")
    parser.add_argument("--check", action="store_true", help="检查回归")
    parser.add_argument("--report", action="store_true", help="生成报告")
    parser.add_argument("--format", choices=["text", "json"], default="text", help="报告格式")
    parser.add_argument("--output", help="输出文件路径")
    
    args = parser.parse_args()
    
    detector = RegressionDetector()
    
    try:
        if args.save_baseline:
            detector.save_baseline(args.baseline_name)
            return 0
        
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
