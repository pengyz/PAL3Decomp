# Phase-2 queue: sret (struct-return) functions — RESOLVED 2026-08-31

The entire queue was caused by ONE apply-layer tokenization bug: in the [6]
signature path, `RET *__thiscall` tokenized as the single unknown token
`*__thiscall`, which was dropped as a "function-name token" — silently
stripping the return type's '*' and the calling convention. parse_decl then
parsed e.g. `UIFrameWnd _sdtor(...)` as a by-value struct return (ctor form),
and Hex-Rays invented `__return_ptr retstr` for all of them.

Fix: normalize `*` → `* ` before tokenizing (apply_annotations.py).
Post-fix export: 0 `retstr` references corpus-wide; all 86 functions render
with their true signatures. No manual body translation was ever needed.
Original queue preserved below for the record.

# Phase-2 queue: sret (struct-return) functions needing manual by-value translation

Hex-Rays renders these as `RET *Cls::Method(RET *__return_ptr retstr, Cls *this, ...)`;
