#!/usr/bin/env python3
"""
Annotation Diff Visualization Tool

对比annotation文件的不同版本，显示有意义的变更。

功能：
1. 对比当前annotation文件与git HEAD版本
2. 解析diff，提取有意义的变更：
   - 新增/删除的成员
   - 类型变更
   - 偏移变更
   - 名称变更
3. 输出可视化报告

用法：
    python3 tools/annotation_diff.py                    # 对比当前vs HEAD
    python3 tools/annotation_diff.py --commit abc123    # 对比当前vs指定commit
    python3 tools/annotation_diff.py --format html      # 输出HTML报告
    python3 tools/annotation_diff.py --output report.txt # 保存到文件
"""

import argparse
import json
import os
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Set, Tuple, Optional, Any
from dataclasses import dataclass
from enum import Enum
from collections import Counter

PROJECT_ROOT = Path(__file__).parent.parent
ANNOTATIONS_DIR = PROJECT_ROOT / "data" / "annotations" / "structs"
REPORT_DIR = PROJECT_ROOT / "pipeline" / "_logs" / "annotation_diffs"


class ChangeType(Enum):
    """变更类型"""
    MEMBER_ADDED = "member_added"
    MEMBER_REMOVED = "member_removed"
    TYPE_CHANGED = "type_changed"
    OFFSET_CHANGED = "offset_changed"
    NAME_CHANGED = "name_changed"
    SOURCE_CHANGED = "source_changed"
    BINARY_SIZE_CHANGED = "binary_size_changed"
    STRUCT_ADDED = "struct_added"
    STRUCT_REMOVED = "struct_removed"


@dataclass
class MemberChange:
    """成员变更"""
    offset: str
    change_type: ChangeType
    old_value: Optional[str] = None
    new_value: Optional[str] = None
    field: str = ""  # name, type, source, etc.


@dataclass
class StructDiff:
    """结构体diff"""
    struct_name: str
    changes: List[MemberChange]
    old_data: Optional[Dict] = None
    new_data: Optional[Dict] = None


class AnnotationDiffer:
    """Annotation差异分析器"""
    
    def __init__(self):
        self.report_dir = REPORT_DIR
        self.report_dir.mkdir(parents=True, exist_ok=True)
    
    def get_git_file_content(self, filepath: str, commit: str = "HEAD") -> Optional[str]:
        """获取git中指定commit的文件内容"""
        try:
            result = subprocess.run(
                ["git", "show", f"{commit}:{filepath}"],
                capture_output=True,
                text=True,
                cwd=PROJECT_ROOT
            )
            if result.returncode == 0:
                return result.stdout
            return None
        except Exception:
            return None
    
    def get_current_file_content(self, filepath: str) -> Optional[str]:
        """获取当前文件内容"""
        full_path = PROJECT_ROOT / filepath
        if full_path.exists():
            return full_path.read_text(encoding='utf-8')
        return None
    
    def load_struct_json(self, content: str) -> Optional[Dict]:
        """加载结构体JSON"""
        try:
            return json.loads(content)
        except json.JSONDecodeError:
            return None
    
    def compare_members(self, old_members: Dict, new_members: Dict) -> List[MemberChange]:
        """比较成员变更"""
        changes = []
        
        all_offsets = set(list(old_members.keys()) + list(new_members.keys()))
        
        for offset in sorted(all_offsets, key=lambda x: int(x) if x.isdigit() else 0):
            old_member = old_members.get(offset)
            new_member = new_members.get(offset)
            
            # 新增成员
            if old_member is None and new_member is not None:
                changes.append(MemberChange(
                    offset=offset,
                    change_type=ChangeType.MEMBER_ADDED,
                    new_value=json.dumps(new_member, ensure_ascii=False),
                    field="member"
                ))
            
            # 删除成员
            elif old_member is not None and new_member is None:
                changes.append(MemberChange(
                    offset=offset,
                    change_type=ChangeType.MEMBER_REMOVED,
                    old_value=json.dumps(old_member, ensure_ascii=False),
                    field="member"
                ))
            
            # 成员变更
            elif old_member is not None and new_member is not None:
                # 检查类型变更
                old_type = old_member.get("type", "")
                new_type = new_member.get("type", "")
                if old_type != new_type:
                    changes.append(MemberChange(
                        offset=offset,
                        change_type=ChangeType.TYPE_CHANGED,
                        old_value=old_type,
                        new_value=new_type,
                        field="type"
                    ))
                
                # 检查名称变更
                old_name = old_member.get("name", "")
                new_name = new_member.get("name", "")
                if old_name != new_name:
                    changes.append(MemberChange(
                        offset=offset,
                        change_type=ChangeType.NAME_CHANGED,
                        old_value=old_name,
                        new_value=new_name,
                        field="name"
                    ))
                
                # 检查source变更
                old_source = old_member.get("source", "")
                new_source = new_member.get("source", "")
                if old_source != new_source:
                    changes.append(MemberChange(
                        offset=offset,
                        change_type=ChangeType.SOURCE_CHANGED,
                        old_value=old_source,
                        new_value=new_source,
                        field="source"
                    ))
        
        return changes
    
    def compare_struct(self, old_data: Dict, new_data: Dict) -> StructDiff:
        """比较整个结构体"""
        struct_name = new_data.get("name", old_data.get("name", "unknown"))
        changes = []
        
        # 检查binary_size变更
        old_size = old_data.get("binary_size")
        new_size = new_data.get("binary_size")
        if old_size != new_size:
            changes.append(MemberChange(
                offset="",
                change_type=ChangeType.BINARY_SIZE_CHANGED,
                old_value=str(old_size),
                new_value=str(new_size),
                field="binary_size"
            ))
        
        # 比较成员
        old_members = old_data.get("known_members", {})
        new_members = new_data.get("known_members", {})
        member_changes = self.compare_members(old_members, new_members)
        changes.extend(member_changes)
        
        return StructDiff(
            struct_name=struct_name,
            changes=changes,
            old_data=old_data,
            new_data=new_data
        )
    
    def analyze_directory(self, commit: str = "HEAD") -> List[StructDiff]:
        """分析整个annotation目录"""
        diffs = []
        
        # 获取当前所有struct文件
        current_files = set()
        if ANNOTATIONS_DIR.exists():
            for f in ANNOTATIONS_DIR.glob("*.json"):
                current_files.add(f.name)
        
        # 获取git中的struct文件
        git_files = set()
        try:
            result = subprocess.run(
                ["git", "ls-tree", "-r", "--name-only", commit, str(ANNOTATIONS_DIR.relative_to(PROJECT_ROOT))],
                capture_output=True,
                text=True,
                cwd=PROJECT_ROOT
            )
            if result.returncode == 0:
                for line in result.stdout.strip().split('\n'):
                    if line.endswith('.json'):
                        git_files.add(Path(line).name)
        except Exception:
            pass
        
        all_files = current_files | git_files
        
        for filename in sorted(all_files):
            filepath = str(ANNOTATIONS_DIR.relative_to(PROJECT_ROOT) / filename)
            
            current_content = self.get_current_file_content(filepath)
            git_content = self.get_git_file_content(filepath, commit)
            
            # 新增文件
            if current_content and not git_content:
                current_data = self.load_struct_json(current_content)
                if current_data:
                    diffs.append(StructDiff(
                        struct_name=filename.replace('.json', ''),
                        changes=[MemberChange(
                            offset="",
                            change_type=ChangeType.STRUCT_ADDED,
                            new_value=f"New struct with {len(current_data.get('known_members', {}))} members"
                        )],
                        new_data=current_data
                    ))
            
            # 删除文件
            elif not current_content and git_content:
                git_data = self.load_struct_json(git_content)
                if git_data:
                    diffs.append(StructDiff(
                        struct_name=filename.replace('.json', ''),
                        changes=[MemberChange(
                            offset="",
                            change_type=ChangeType.STRUCT_REMOVED,
                            old_value=f"Removed struct with {len(git_data.get('known_members', {}))} members"
                        )],
                        old_data=git_data
                    ))
            
            # 文件存在但内容可能变更
            elif current_content and git_content:
                current_data = self.load_struct_json(current_content)
                git_data = self.load_struct_json(git_content)
                
                if current_data and git_data:
                    diff = self.compare_struct(git_data, current_data)
                    if diff.changes:
                        diffs.append(diff)
        
        return diffs
    
    def generate_text_report(self, diffs: List[StructDiff]) -> str:
        """生成文本报告"""
        lines = []
        lines.append("=" * 80)
        lines.append("Annotation Diff Report")
        lines.append("=" * 80)
        lines.append(f"分析时间: {__import__('datetime').datetime.now().isoformat()}")
        lines.append(f"变更结构体数量: {len(diffs)}")
        lines.append("")
        
        if not diffs:
            lines.append("✅ 未检测到annotation变更。")
            return "\n".join(lines)
        
        # 统计变更类型
        change_counts = {}
        for diff in diffs:
            for change in diff.changes:
                change_counts[change.change_type] = change_counts.get(change.change_type, 0) + 1
        
        lines.append("📊 变更统计:")
        for change_type, count in sorted(change_counts.items(), key=lambda x: x[1], reverse=True):
            lines.append(f"  {change_type.value}: {count}")
        lines.append("")
        
        # 详细变更
        lines.append("📋 详细变更:")
        lines.append("-" * 80)
        
        for diff in diffs:
            lines.append(f"\n🔧 {diff.struct_name}")
            
            for change in diff.changes:
                if change.change_type == ChangeType.STRUCT_ADDED:
                    lines.append(f"  + {change.new_value}")
                elif change.change_type == ChangeType.STRUCT_REMOVED:
                    lines.append(f"  - {change.old_value}")
                elif change.change_type == ChangeType.BINARY_SIZE_CHANGED:
                    lines.append(f"  binary_size: {change.old_value} → {change.new_value}")
                elif change.change_type == ChangeType.MEMBER_ADDED:
                    lines.append(f"  + [{change.offset}] {change.new_value}")
                elif change.change_type == ChangeType.MEMBER_REMOVED:
                    lines.append(f"  - [{change.offset}] {change.old_value}")
                elif change.change_type == ChangeType.TYPE_CHANGED:
                    lines.append(f"  [{change.offset}] type: {change.old_value} → {change.new_value}")
                elif change.change_type == ChangeType.NAME_CHANGED:
                    lines.append(f"  [{change.offset}] name: {change.old_value} → {change.new_value}")
                elif change.change_type == ChangeType.SOURCE_CHANGED:
                    lines.append(f"  [{change.offset}] source: {change.old_value} → {change.new_value}")
        
        return "\n".join(lines)
    
    def generate_json_report(self, diffs: List[StructDiff]) -> str:
        """生成JSON报告"""
        report = {
            "timestamp": __import__('datetime').datetime.now().isoformat(),
            "total_structs_changed": len(diffs),
            "changes": []
        }
        
        for diff in diffs:
            struct_report = {
                "struct_name": diff.struct_name,
                "changes": []
            }
            
            for change in diff.changes:
                struct_report["changes"].append({
                    "type": change.change_type.value,
                    "offset": change.offset,
                    "field": change.field,
                    "old_value": change.old_value,
                    "new_value": change.new_value
                })
            
            report["changes"].append(struct_report)
        
        return json.dumps(report, indent=2, ensure_ascii=False)
    
    def generate_html_report(self, diffs: List[StructDiff]) -> str:
        """生成HTML报告"""
        html = []
        html.append("""<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Annotation Diff Report</title>
    <style>
        body { font-family: monospace; margin: 20px; background: #1e1e1e; color: #d4d4d4; }
        .header { background: #2d2d2d; padding: 15px; border-radius: 5px; margin-bottom: 20px; }
        .summary { background: #252526; padding: 10px; margin-bottom: 20px; border-left: 3px solid #569cd6; }
        .struct { background: #2d2d2d; padding: 10px; margin-bottom: 10px; border-radius: 3px; }
        .struct-name { color: #4ec9b0; font-weight: bold; font-size: 1.1em; }
        .change { margin: 5px 0; padding: 5px; }
        .added { color: #6a9955; }
        .removed { color: #f44747; }
        .changed { color: #dcdcaa; }
        .offset { color: #569cd6; }
        .type { color: #4ec9b0; }
        .value { color: #ce9178; }
    </style>
</head>
<body>
    <div class="header">
        <h1>Annotation Diff Report</h1>
        <p>Generated: """ + __import__('datetime').datetime.now().isoformat() + """</p>
        <p>Structs changed: """ + str(len(diffs)) + """</p>
    </div>
""")
        
        if not diffs:
            html.append('<div class="summary">✅ No annotation changes detected.</div>')
        else:
            html.append('<div class="summary">📊 Changes found in ' + str(len(diffs)) + ' structs</div>')
            
            for diff in diffs:
                html.append(f'<div class="struct">')
                html.append(f'<div class="struct-name">🔧 {diff.struct_name}</div>')
                
                for change in diff.changes:
                    if change.change_type == ChangeType.STRUCT_ADDED:
                        html.append(f'<div class="change added">+ {change.new_value}</div>')
                    elif change.change_type == ChangeType.STRUCT_REMOVED:
                        html.append(f'<div class="change removed">- {change.old_value}</div>')
                    elif change.change_type == ChangeType.BINARY_SIZE_CHANGED:
                        html.append(f'<div class="changed">binary_size: {change.old_value} → {change.new_value}</div>')
                    elif change.change_type == ChangeType.MEMBER_ADDED:
                        html.append(f'<div class="change added">+ [<span class="offset">{change.offset}</span>] {change.new_value}</div>')
                    elif change.change_type == ChangeType.MEMBER_REMOVED:
                        html.append(f'<div class="change removed">- [<span class="offset">{change.offset}</span>] {change.old_value}</div>')
                    elif change.change_type == ChangeType.TYPE_CHANGED:
                        html.append(f'<div class="change">[<span class="offset">{change.offset}</span>] type: <span class="removed">{change.old_value}</span> → <span class="added">{change.new_value}</span></div>')
                    elif change.change_type == ChangeType.NAME_CHANGED:
                        html.append(f'<div class="change">[<span class="offset">{change.offset}</span>] name: <span class="removed">{change.old_value}</span> → <span class="added">{change.new_value}</span></div>')
                    elif change.change_type == ChangeType.SOURCE_CHANGED:
                        html.append(f'<div class="change">[<span class="offset">{change.offset}</span>] source: <span class="removed">{change.old_value}</span> → <span class="added">{change.new_value}</span></div>')
                
                html.append('</div>')
        
        html.append("""
</body>
</html>
""")
        return "\n".join(html)
    
    def save_report(self, diffs: List[StructDiff], format: str = "text") -> str:
        """保存报告到文件"""
        timestamp = __import__('datetime').datetime.now().strftime("%Y%m%d_%H%M%S")
        
        if format == "json":
            report_file = self.report_dir / f"annotation_diff_{timestamp}.json"
            content = self.generate_json_report(diffs)
        elif format == "html":
            report_file = self.report_dir / f"annotation_diff_{timestamp}.html"
            content = self.generate_html_report(diffs)
        else:
            report_file = self.report_dir / f"annotation_diff_{timestamp}.txt"
            content = self.generate_text_report(diffs)
        
        with open(report_file, 'w', encoding='utf-8') as f:
            f.write(content)
        
        return str(report_file)


def main():
    parser = argparse.ArgumentParser(description="Annotation Diff Visualization Tool")
    parser.add_argument("--commit", default="HEAD", help="Git commit to compare against")
    parser.add_argument("--format", choices=["text", "json", "html"], default="text", help="Output format")
    parser.add_argument("--output", help="Output file path")
    parser.add_argument("--quiet", action="store_true", help="Suppress terminal output")
    
    args = parser.parse_args()
    
    differ = AnnotationDiffer()
    
    try:
        # 分析差异
        diffs = differ.analyze_directory(args.commit)
        
        # 生成报告
        if args.output:
            report_file = differ.save_report(diffs, args.format)
            if not args.quiet:
                print(f"✅ 报告已保存: {report_file}")
        else:
            if args.format == "json":
                report = differ.generate_json_report(diffs)
            elif args.format == "html":
                report = differ.generate_html_report(diffs)
            else:
                report = differ.generate_text_report(diffs)
            
            if not args.quiet:
                print(report)
        
        # 返回码：有变更返回0，无变更返回0
        return 0
        
    except Exception as e:
        print(f"❌ 错误: {e}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
