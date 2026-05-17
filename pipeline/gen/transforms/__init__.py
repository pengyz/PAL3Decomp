"""Transform registry with auto-discovery.

Each transform is a plain function decorated with @register(order=N).
Transforms are auto-imported from all non-underscore .py files in this directory.
"""
import importlib
import os
import pkgutil

_registry = []  # [(order, func)]


def register(order=500):
    """Register a code transform function.

    Args:
        order: Execution priority (lower = earlier). Ranges:
            0-99: IDA cleanup (remove invalid code)
            100-199: Type fixes (COERCE_FLOAT, int types, suffixes)
            200-299: OOP transforms (ast_transform, ref params)
            300-399: Name resolution (thunks, literals, globals, struct members)
            400-499: VC6 compatibility (calling conventions, casts)
    """
    def decorator(func):
        _registry.append((order, func))
        return func
    return decorator


def get_pipeline():
    """Return all registered transforms sorted by order."""
    return [func for _, func in sorted(_registry, key=lambda x: x[0])]


# Auto-import all transform modules in this package
_pkg_dir = os.path.dirname(os.path.abspath(__file__))
for _, _name, _ in pkgutil.iter_modules([_pkg_dir]):
    if not _name.startswith('_'):
        importlib.import_module('.' + _name, __package__)
