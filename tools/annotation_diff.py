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

失败形态（重要）：
本工具**必须**能区分「注解无变更」与「读不到 git」。旧实现在 git 不可用
（无仓库 / 坏 commit / git 不在 PATH）时 `git show` 与 `git ls-tree` 全部失败，
于是每个结构体都被当成「新增文件」：实测把 898 个结构体全报为新增，**仍以 0 退出**，
与「无变更」不可区分。现在：
    * git/commit 不可读 -> 报错并退出 3（verdict: git_unavailable）
    * git 可读          -> 退出 0（verdict: clean / changed），报告写明 git 可读证据

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


class GitUnavailableError(Exception):
    """git (or the requested commit) cannot be read -> the diff is meaningless."""


def summarize_value(v, limit: int = 200) -> str:
    """把任意 JSON 值压成一行摘要，供报告使用。"""
    try:
        s = json.dumps(v, ensure_ascii=False, sort_keys=True)
    except (TypeError, ValueError):
        s = repr(v)
    return s if len(s) <= limit else s[:limit] + "..."


class ChangeType(Enum):
    """变更类型"""
    MEMBER_ADDED = "member_added"
    MEMBER_REMOVED = "member_removed"
    TYPE_CHANGED = "type_changed"
    OFFSET_CHANGED = "offset_changed"
    NAME_CHANGED = "name_changed"
    SOURCE_CHANGED = "source_changed"
    BINARY_SIZE_CHANGED = "binary_size_changed"
    FIELD_ADDED = "field_added"
    FIELD_REMOVED = "field_removed"
    FIELD_CHANGED = "field_changed"
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
        self.git_sha = None            # resolved commit sha (proves git was readable)
        self.commit_arg = None         # commit argument as given on the CLI
        self.git_files_count = 0       # struct files found in git at that commit
        self.current_files_count = 0   # struct files in the working tree
        self.git_read_errors = []      # files listed by git but not readable

    def check_git_available(self, commit: str = "HEAD") -> str:
        """Resolve <commit> to a sha or fail loudly.

        A diff tool that cannot read git has NO information; it must not
        degrade into "everything is new".
        """
        try:
            result = subprocess.run(
                ["git", "rev-parse", "--verify", "--quiet", "%s^{commit}" % commit],
                capture_output=True, text=True, cwd=PROJECT_ROOT)
        except FileNotFoundError as e:
            raise GitUnavailableError(
                "git is not runnable: %s\n"
                "  This tool diffs the working tree against a git commit; without git it\n"
                "  cannot distinguish 'no annotation changes' from 'cannot read git'." % e)
        except Exception as e:
            raise GitUnavailableError("git invocation failed: %s" % e)
        if result.returncode != 0:
            raise GitUnavailableError(
                "cannot resolve commit %r (git rev-parse exit %d)\n"
                "  cwd: %s\n"
                "  stderr: %s\n"
                "  If this is a clean checkout without git metadata, run the diff from a\n"
                "  git working copy -- 'no changes' cannot be claimed without git."
                % (commit, result.returncode, PROJECT_ROOT, result.stderr.strip()))
        sha = result.stdout.strip()
        if not sha:
            raise GitUnavailableError("git rev-parse returned an empty sha for %r" % commit)
        return sha

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
    
    # 已被 compare_struct 专门处理的顶层字段；其余字段一律走 compare_other_fields
    DETAILED_FIELDS = ("name", "known_members", "binary_size")

    def compare_other_fields(self, old_data: Dict, new_data: Dict) -> List[MemberChange]:
        """比较 `known_members` / `binary_size` 之外的**全部**顶层字段。

        这个洞曾经真实存在：`compare_struct` 只看 binary_size + known_members，
        于是 **`methods`（函数归属）变更完全不可见** —— 而归属迁移是本项目的主要
        改动类型。实例：把 `UIWnd::GetWidth/GetHeight/GetPosition` 迁到
        `UIProgressBar` 后，本工具仍报「变更结构体数量: 0 / verdict: clean」，
        而 `git status` 明确显示两个文件已修改（见
        data/status/_cleanup_landing_uiwnd_3methods.md §5）。

        修法不是逐个补字段（那样下一个新字段还会被静默忽略），而是**白名单之外
        全部比较**；dict 字段再按键细化，报告里能看出是哪个 VA / 哪个基类变了。
        """
        changes: List[MemberChange] = []
        for key in sorted(set(old_data) | set(new_data)):
            if key in self.DETAILED_FIELDS:
                continue
            ov, nv = old_data.get(key), new_data.get(key)
            if ov == nv:
                continue
            if isinstance(ov, dict) or isinstance(nv, dict):
                od = ov if isinstance(ov, dict) else {}
                nd = nv if isinstance(nv, dict) else {}
                for k in sorted(set(od) | set(nd), key=str):
                    a, b = od.get(k), nd.get(k)
                    if a == b:
                        continue
                    if a is None:
                        ct = ChangeType.FIELD_ADDED
                    elif b is None:
                        ct = ChangeType.FIELD_REMOVED
                    else:
                        ct = ChangeType.FIELD_CHANGED
                    changes.append(MemberChange(
                        offset=str(k), change_type=ct,
                        old_value=None if a is None else summarize_value(a),
                        new_value=None if b is None else summarize_value(b),
                        field=key))
            else:
                changes.append(MemberChange(
                    offset="",
                    change_type=ChangeType.FIELD_REMOVED if nv is None
                    else (ChangeType.FIELD_ADDED if ov is None else ChangeType.FIELD_CHANGED),
                    old_value=None if ov is None else summarize_value(ov),
                    new_value=None if nv is None else summarize_value(nv),
                    field=key))
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

        # 其余顶层字段（methods / base_class / base_size / vtables / ...）
        changes.extend(self.compare_other_fields(old_data, new_data))
        
        return StructDiff(
            struct_name=struct_name,
            changes=changes,
            old_data=old_data,
            new_data=new_data
        )
    
    def analyze_directory(self, commit: str = "HEAD") -> List[StructDiff]:
        """分析整个annotation目录

        Raises GitUnavailableError when git / the commit / the tree listing
        cannot be read. Never classifies "git unreadable" as "file added".
        """
        diffs = []

        # Fail fast: without a resolvable commit this analysis has no meaning.
        self.commit_arg = commit
        self.git_sha = self.check_git_available(commit)

        # 获取当前所有struct文件
        current_files = set()
        if ANNOTATIONS_DIR.exists():
            for f in ANNOTATIONS_DIR.glob("*.json"):
                current_files.add(f.name)
        self.current_files_count = len(current_files)

        # 获取git中的struct文件
        git_files = set()
        result = subprocess.run(
            ["git", "ls-tree", "-r", "--name-only", commit,
             str(ANNOTATIONS_DIR.relative_to(PROJECT_ROOT))],
            capture_output=True, text=True, cwd=PROJECT_ROOT)
        if result.returncode != 0:
            raise GitUnavailableError(
                "git ls-tree failed for %r (exit %d)\n  stderr: %s\n"
                "  The tracked struct list cannot be read, so every struct would look new."
                % (commit, result.returncode, result.stderr.strip()))
        for line in result.stdout.strip().split('\n'):
            if line.endswith('.json'):
                git_files.add(Path(line).name)
        self.git_files_count = len(git_files)

        all_files = current_files | git_files

        for filename in sorted(all_files):
            filepath = str(ANNOTATIONS_DIR.relative_to(PROJECT_ROOT) / filename)

            current_content = self.get_current_file_content(filepath)
            git_content = self.get_git_file_content(filepath, commit)
            tracked = filename in git_files

            if tracked and git_content is None:
                # git listed the file but its content could not be read: this is
                # a git read failure, NOT a new file. Never silently reclassify.
                self.git_read_errors.append(filename)
                continue

            # 新增文件（git 确认该文件不在这个 commit 里）
            if current_content and not tracked:
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
            elif not current_content and tracked:
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

        if self.git_read_errors:
            raise GitUnavailableError(
                "%d file(s) are tracked at %s but their content could not be read "
                "(first: %s)\n  Refusing to report them as 'added': the diff would be wrong."
                % (len(self.git_read_errors), commit, self.git_read_errors[0]))

        return diffs
    
    def generate_text_report(self, diffs: List[StructDiff]) -> str:
        """生成文本报告"""
        lines = []
        lines.append("=" * 80)
        lines.append("Annotation Diff Report")
        lines.append("=" * 80)
        lines.append(f"分析时间: {__import__('datetime').datetime.now().isoformat()}")
        lines.append(f"git: {self.commit_arg} -> {self.git_sha} (可读)")
        lines.append(f"struct 文件: 工作区 {self.current_files_count} / git {self.git_files_count}")
        lines.append(f"变更结构体数量: {len(diffs)}")
        lines.append(f"verdict: {'changed' if diffs else 'clean'}")
        lines.append("")
        
        if not diffs:
            lines.append(
                "✅ 未检测到annotation变更（git 可读: %s；%d 个 struct 文件与 %s 一致）。"
                % (self.git_sha, self.current_files_count, self.commit_arg))
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
                elif change.change_type == ChangeType.FIELD_ADDED:
                    lines.append(f"  + {change.field}[{change.offset}] {change.new_value}")
                elif change.change_type == ChangeType.FIELD_REMOVED:
                    lines.append(f"  - {change.field}[{change.offset}] {change.old_value}")
                elif change.change_type == ChangeType.FIELD_CHANGED:
                    lines.append(f"  {change.field}[{change.offset}]: "
                                 f"{change.old_value} → {change.new_value}")
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
            "verdict": "changed" if diffs else "clean",
            "git_readable": True,
            "git_commit": self.commit_arg,
            "git_sha": self.git_sha,
            "current_struct_files": self.current_files_count,
            "git_struct_files": self.git_files_count,
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
        <p>git: """ + str(self.commit_arg) + """ -&gt; """ + str(self.git_sha) + """ (readable); struct files: working tree """ + str(self.current_files_count) + """ / git """ + str(self.git_files_count) + """</p>
        <p>Structs changed: """ + str(len(diffs)) + """</p>
    </div>
""")
        
        if not diffs:
            html.append('<div class="summary">✅ No annotation changes detected (git readable: '
                        + str(self.git_sha) + ').</div>')
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
        
        # 返回码：git 可读且有/无变更均返回 0（verdict 在报告里）
        return 0

    except GitUnavailableError as e:
        # Cannot read git -> the diff is meaningless. Exit 3 (distinct from the
        # generic 2) so a caller can never mistake this for "no changes".
        print("❌ GIT 不可读 —— 无法判断注解是否有变更（不是「无变更」）:", file=sys.stderr)
        print(str(e), file=sys.stderr)
        return 3

    except Exception as e:
        print(f"❌ 错误: {e}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
