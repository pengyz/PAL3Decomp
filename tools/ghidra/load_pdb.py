# Ghidra preScript: Load PDB file for PAL3A
# @category PAL3A

import os
from ghidra.app.util.bin.format.pdb2 import PdbUniversalAnalyzer
from ghidra.app.plugin.core.analysis import AutoAnalysisManager

args = getScriptArgs()
if args:
    pdb_path = args[0]
else:
    pdb_path = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
        getSourceFile().getAbsolutePath()))), "original", "PAL3A.pdb")

from java.io import File
pdb_file = File(pdb_path)

if not pdb_file.exists():
    printerr("PDB file not found: " + pdb_path)
else:
    println("Loading PDB: " + pdb_path)
    from ghidra.app.util.pdb.pdbapplicator import PdbApplicatorControl
    from ghidra.app.util.bin.format.pdb2 import PdbParser
    # Use the PDB Universal analyzer approach
    from ghidra.program.model.listing import Program
    from ghidra.app.util.importer import MessageLog

    # Set PDB file path in program options so analyzer picks it up
    opts = currentProgram.getOptions(Program.PROGRAM_INFO)
    opts.setString("Executable Location", pdb_file.getParent())

    # Also set in analysis options
    analysis_opts = currentProgram.getOptions("Analyzers")
    analysis_opts.setBoolean("PDB Universal", True)

    println("PDB path configured for analysis: " + pdb_path)
