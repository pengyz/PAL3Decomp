# Ghidra script: Set PDB path and trigger PDB analysis
# @category PAL3A

from java.io import File
from ghidra.app.util.bin.format.pdb2 import PdbUniversalAnalyzer

args = getScriptArgs()
if args:
    pdb_path = args[0]
else:
    pdb_path = "D:\\workspace\\project-x\\original\\PAL3A.pdb"

pdb_file = File(pdb_path)
if not pdb_file.exists():
    printerr("PDB not found: " + pdb_path)
    raise Exception("PDB not found: " + pdb_path)

println("Setting PDB file: " + pdb_path)

# Set PDB file path option so PDB Universal analyzer can find it
PdbUniversalAnalyzer.setPdbFileOption(currentProgram, pdb_file)

println("PDB file option set. PDB Universal analyzer will apply it during analysis.")
