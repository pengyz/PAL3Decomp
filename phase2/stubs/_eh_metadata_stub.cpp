// phase2/stubs/_eh_metadata_stub.cpp - EH metadata supply ((d) manual synthesis)
// codegen+stub overlay design: link closure only.
//
// CAUSE: codegen replicates the _CxxThrowException(p, &_TI1_AV_Exception__)
// call shape from the original throw sites, but the compiler-emitted EH
// metadata COMDATs of the original `throw Exception(...)` statements do not
// come along => every TU referencing _TI1_AV_Exception__ is unresolved.
// The original binary got them emitted by the compiler in the throw TUs.
//
// Supply here as zeroed data: fine for link closure; runtime throw behavior
// is NOT represented (loud-fail decision is M5 per design section 7).
#include "pal3/ida_defs.h"

_s__ThrowInfo _TI1_AV_Exception__ = {0, 0, 0, 0};
