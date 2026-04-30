# PAL3.exe Ghidra Analysis - Phase 0 Task 1

## Status: SETUP COMPLETE - AWAITING MANUAL ANALYSIS

All prerequisite setup for Ghidra analysis of PAL3.exe has been completed. The manual GUI-based analysis steps must now be performed.

## What Has Been Done

### ✅ Completed Setup Tasks

1. **Java Runtime Installation**
   - OpenJDK 17.0.8 installed at `C:\Java\jdk-17.0.8+7`
   - Verified working: `java -version` confirms Temurin 17.0.8

2. **Ghidra Installation**
   - Ghidra 11.2.1 extracted at `D:\workspace\project-x\tools\ghidra`
   - Configuration completed: Java home set in launch.properties
   - Ready to launch: `tools\ghidra\ghidraRun.bat`

3. **Project Structure**
   - Created `asm/pal3/` - Directory for Ghidra project files
   - Created `docs/pal3/` - Directory for documentation
   - Created `docs/pal3/GHIDRA_SETUP_INSTRUCTIONS.md` - Detailed step-by-step guide

4. **Prerequisites Verified**
   - PAL3.exe exists at `original/PAL3.exe` (2.17 MB, unpacked)
   - Project tree ready for analysis

## What Needs to Be Done (Manual Steps)

### GUI-Based Analysis (Cannot Be Automated)

The remaining steps require **interactive GUI interaction with Ghidra**:

1. **Launch Ghidra GUI** (takes 30-60 seconds first time)
   ```cmd
   cd D:\workspace\project-x\tools\ghidra
   ghidraRun.bat
   ```

2. **Create Project in Ghidra**
   - File → New Project
   - Project Name: `PAL3`
   - Location: `D:\workspace\project-x\asm\pal3`

3. **Import PAL3.exe**
   - File → Import File
   - Select `original/PAL3.exe`
   - Confirm format: PE (Portable Executable)
   - Language: x86:LE:32:default

4. **Run Analysis** (most time-consuming step)
   - Double-click PAL3.exe in project
   - Confirm "Analyze"
   - Enable key analyzers (RTTI, Decompiler, Function Search, etc.)
   - **Wait 10-30 minutes for analysis to complete**

5. **Verify Results**
   - Check function count (should be 3000-5000)
   - Window → Functions to verify
   - Save project (Ctrl+S)

### Detailed Instructions

See **`docs/pal3/GHIDRA_SETUP_INSTRUCTIONS.md`** for:
- Complete step-by-step GUI walkthrough
- Troubleshooting guide
- Analysis options explanation
- Verification procedures

### Timeline

- **Launch Ghidra**: 1-2 minutes
- **Create project**: 1 minute
- **Import PAL3.exe**: 2-3 minutes
- **Run analysis**: 10-30 minutes (CPU dependent)
- **Verify results**: 5 minutes
- **Total time**: 20-40 minutes

## Expected Results After Manual Analysis

### Deliverables

1. **Ghidra Project Files**
   ```
   asm/pal3/
   ├── PAL3.gpr          (Project file)
   └── PAL3.rep/         (Repository with analysis data)
       ├── index.db
       ├── addressMap
       └── [analysis files]
   ```

2. **Analysis Log**
   ```
   docs/pal3/ghidra_analysis_log.txt
   ```
   Contains function statistics after analysis

3. **Statistics Expected**
   - Total functions: 3200-3500
   - Internal functions: 3100-3400
   - External functions (imports): 150-200
   - Thunks: 50-100

## Next Steps After Manual Analysis

### Automated Export (Task 2)
Once analysis completes in Ghidra, run export to get function data:
```bash
python tools/ghidra_export.py asm/pal3 pal3.exe all
```

This creates JSON files for each function in `asm/pal3/*.json`

### Function Classification
```bash
python tools/analyze_priority.py asm/pal3
```

Groups functions by complexity and priority for decompilation

### Begin Decompilation
Follow `docs/decompilation_workflow.md` for matching decompilation process

## Files Reference

### Key Documentation
- `docs/pal3/GHIDRA_SETUP_INSTRUCTIONS.md` - **START HERE for GUI steps**
- `docs/pal3/ghidra_analysis_log.txt` - Analysis statistics and checklist
- `docs/pal3/README.md` - This file
- `docs/decompilation_workflow.md` - Detailed workflow for decompilation

### Helper Scripts
- `tools/ghidra_stats_export.py` - Extracts statistics from Ghidra project
- `tools/ghidra_export.py` - Exports all functions to JSON (for Task 2)
- `tools/ghidra_analyze_dll.py` - Can be used for headless analysis (DLL mode)

### Project Structure
```
D:\workspace\project-x\
├── original/
│   └── PAL3.exe           (2.17 MB, unpacked binary)
├── tools/
│   └── ghidra/            (Ghidra 11.2.1)
│       ├── ghidraRun.bat  (Start Ghidra)
│       ├── support/
│       └── ...
├── asm/
│   └── pal3/              (Ghidra project goes here)
│       ├── PAL3.gpr       (Will be created)
│       └── PAL3.rep/      (Will be created)
└── docs/
    └── pal3/
        ├── GHIDRA_SETUP_INSTRUCTIONS.md
        ├── ghidra_analysis_log.txt
        └── README.md (this file)
```

## Troubleshooting

### Problem: Ghidra Won't Start
**Solution**: Check Java is set correctly
```cmd
set JAVA_HOME=C:\Java\jdk-17.0.8+7
set PATH=%JAVA_HOME%\bin;%PATH%
java -version
```

### Problem: "Java Runtime Not Found"
**Solution**: Set JAVA_HOME environment variable and restart Ghidra

### Problem: Analysis Too Slow
**Solution**: This is normal for 2MB binary. Let it run. Close other applications to free memory.

### Problem: Function Count Too Low (<1500)
**Solution**: Analysis may not have completed. Try:
1. Restart Ghidra
2. Re-run analysis: Analysis → Auto Analyze
3. Wait longer

### Problem: Can't Import PAL3.exe
**Solution**: Verify file is unpacked
- PAL3.exe size should be exactly 2,170,880 bytes
- If smaller or compressed, may need unpacking

For more troubleshooting, see `GHIDRA_SETUP_INSTRUCTIONS.md`

## FAQ

### Q: Why is manual GUI required?
A: Ghidra's project creation and analysis launch requires interactive GUI dialogs. This cannot be fully automated in headless mode while maintaining configuration options.

### Q: How long will analysis take?
A: Typically 10-30 minutes depending on CPU and system load. Modern CPUs (8+ cores) complete faster.

### Q: Can I use the headless analyzer instead?
A: For now, manual analysis is recommended for PAL3.exe as it's the first full project. See `ghidra_analyze_dll.py` for headless mode (used for smaller DLLs like topo.dll).

### Q: What if analysis fails partway through?
A: Save the project anyway. Next time you open it, analysis will continue from where it left off.

### Q: How do I verify analysis quality?
A: Check:
1. Function count >= 2000
2. Can find WinMain or entry point
3. Decompilation windows show readable pseudocode
4. Window → Analysis → Console shows no ERROR messages

## Verification Checklist

Before considering this task complete:

- [ ] Ghidra project created at `asm/pal3/PAL3.gpr`
- [ ] PAL3.exe imported and visible in project
- [ ] Analysis completed (Analysis Queue shows "complete")
- [ ] Function count verified (3000-5000 range expected)
- [ ] Project saved successfully
- [ ] `docs/pal3/ghidra_analysis_log.txt` updated with results
- [ ] Changes committed to git

## Commit Message Template

After manual analysis completes:

```
chore(phase0): complete Ghidra analysis of PAL3.exe

- Analyzed PAL3.exe with Ghidra 11.2.1
- Identified [X] functions (internal: [Y], external: [Z], thunks: [W])
- Enabled RTTI, decompiler, and full analysis suite
- Project saved to asm/pal3/
- Statistics logged in docs/pal3/ghidra_analysis_log.txt

Next: Export functions to JSON and begin decompilation

Refs: Phase 0 Task 1
```

## Contact & References

- **Ghidra Documentation**: https://ghidra-sre.org/
- **Community Wiki**: http://ghidra.re/
- **Project Workflow**: `docs/decompilation_workflow.md`
- **Structure Reference**: `include/pal3_structs.h`

---

**Last Updated**: 2026-05-01  
**Status**: Awaiting manual GUI analysis completion
