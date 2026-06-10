"""Scope tree: map type names to output-file relationships.

Builds a tree from ida_structs.json keys where :: delimits hierarchy:
  AStarPathFinder (root, standalone .h)
  ├── NODE (child, inline in parent)
  └── STACK (child, inline in parent)

Used by emit_headers.py to decide which types get standalone headers
vs inline emission.
"""

from dataclasses import dataclass, field
from typing import Optional


@dataclass
class ScopeNode:
    full_name: str  # "AStarPathFinder::NODE"
    short_name: str  # "NODE"
    children: list["ScopeNode"] = field(default_factory=list)
    data: dict = field(default_factory=dict)  # ida_structs.json entry
    is_skipped: bool = False
    is_root: bool = False


def is_ida_artifact(name: str) -> bool:
    """True for IDA internal/pseudo types that should never be exported."""
    if not name or len(name) <= 1:
        return True
    if "$" in name or "?" in name or "<" in name:
        return True
    return False


def parent_key(name: str) -> Optional[str]:
    """Return parent's full name, or None if name is a root.

    'AStarPathFinder::NODE' -> 'AStarPathFinder'
    'A::B::C' -> 'A::B'
    'A' -> None
    """
    if "::" not in name:
        return None
    return name.rsplit("::", 1)[0]


def should_skip_root(name: str, skip_classes: set, skip_prefixes: tuple) -> bool:
    """Root-level skip rules (system/external types)."""
    if name in skip_classes:
        return True
    if name.startswith(skip_prefixes):
        return True
    return False


class ScopeTree:
    """Tree of all exported types, organized by :: nesting depth."""

    def __init__(self):
        self._nodes: dict[str, ScopeNode] = {}
        self.roots: list[ScopeNode] = []  # non-skipped roots ready for generation

    def build(self, ida_structs: dict, skip_classes: set, skip_prefixes: tuple,
              ida_enums: dict = None):
        """Build tree from ida_structs.json data."""
        self._nodes = {}
        if ida_enums is None:
            ida_enums = {}

        # 1. Filter + create nodes from structs
        for key, data in ida_structs.items():
            if key.startswith("_"):
                continue  # _globals, _enums
            if is_ida_artifact(key):
                continue
            if data.get("size", 0) <= 0 or data.get("size") == 0xFFFFFFFFFFFFFFFF:
                continue
            short = key.split("::")[-1] if "::" in key else key
            if not short or not (short[0].isalpha() or short[0] == "_"):
                continue
            node = ScopeNode(
                full_name=key,
                short_name=short,
                data=data,
                is_root=("::" not in key),
            )
            self._nodes[key] = node

        # 2. Link children (process shallowest first to guarantee parent exists)
        for key in sorted(self._nodes, key=lambda k: k.count("::")):
            node = self._nodes[key]
            pkey = parent_key(key)
            if pkey and pkey in self._nodes:
                self._nodes[pkey].children.append(node)

        # 3. Mark skipped roots
        for node in self._nodes.values():
            if node.is_root:
                node.is_skipped = should_skip_root(
                    node.full_name, skip_classes, skip_prefixes
                )

        # 4. Prune skipped subtrees
        for node in self._nodes.values():
            if node.is_skipped:
                self._prune(node)

        # 5. Add enum entries (from _enums) that have :: in name (nested enums)
        for key, edata in ida_enums.items():
            if '::' not in key:
                continue
            if key in self._nodes:
                continue
            short = key.split("::")[-1]
            if not short or not (short[0].isalpha() or short[0] == "_"):
                continue
            node = ScopeNode(
                full_name=key,
                short_name=short,
                data=edata,
                is_root=False,
            )
            self._nodes[key] = node
            pkey = parent_key(key)
            if pkey and pkey in self._nodes:
                self._nodes[pkey].children.append(node)

        # 6. Collect valid roots
        self.roots = [n for n in self._nodes.values() if n.is_root and not n.is_skipped]

    @staticmethod
    def _prune(node: ScopeNode):
        """Recursively mark all descendants skipped."""
        for child in node.children:
            child.is_skipped = True
            ScopeTree._prune(child)

    def find(self, full_name: str) -> Optional[ScopeNode]:
        """Look up a node by fully qualified name."""
        return self._nodes.get(full_name)

    def parent_of(self, full_name: str) -> Optional[ScopeNode]:
        """Return the parent node of a nested type, or None."""
        pkey = parent_key(full_name)
        return self._nodes.get(pkey) if pkey else None
