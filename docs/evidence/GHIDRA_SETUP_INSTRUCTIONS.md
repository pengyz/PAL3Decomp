# Ghidra Setup Instructions for PAL3.exe Analysis

## Environment Status

### Prerequisites Completed
- ✅ Java JDK 17.0.8 installed at `C:\Java\jdk-17.0.8+7`
- ✅ Ghidra 11.2.1 installed at `D:\workspace\project-x\tools\ghidra`
- ✅ PAL3.exe available at `D:\workspace\project-x\original\PAL3.exe` (unpacked, 2.17 MB)
- ✅ Project directories created:
  - `D:\workspace\project-x\asm/pal3/` - Ghidra project directory
  - `D:\workspace\project-x/docs/pal3/` - Documentation directory

### Environment Variables to Set (Windows)
If running Ghidra GUI, set these first:
```cmd
setx JAVA_HOME "C:\Java\jdk-17.0.8+7"
setx PATH "%JAVA_HOME%\bin;%PATH%"
```
Or for the current session only:
```cmd
set JAVA_HOME=C:\Java\jdk-17.0.8+7
set PATH=%JAVA_HOME%\bin;%PATH%
```

## Manual Steps for Ghidra Project Setup

### Step 1: Start Ghidra GUI
```cmd
cd D:\workspace\project-x\tools\ghidra
ghidraRun.bat
```

Wait for the Ghidra window to appear (first launch may take 30-60 seconds).

### Step 2: Create New Project
1. Click **File** → **New Project**
2. Select **"Non-Shared Project"**
3. Set options:
   - **Project Directory**: `D:\workspace\project-x\asm\pal3`
   - **Project Name**: `PAL3`
4. Click **"Finish"**

Expected result: Ghidra project window opens with empty file list

### Step 3: Import PAL3.exe
1. Click **File** → **Import File**
2. Navigate to `D:\workspace\project-x\original\PAL3.exe`
3. Select it and click **"Open"** (or **"Next"** if prompted)
4. In the import options dialog:
   - **Format**: Should auto-detect as "Portable Executable (PE)"
   - **Language**: Should auto-select "x86:LE:32:default"
   - Click **"OK"** to proceed
5. In the options dialog (if shown), use default settings
6. Click **"OK"** to import

Expected result: PAL3.exe appears in the project file list

### Step 4: Open CodeBrowser and Analyze
1. Double-click **PAL3.exe** in the project to open CodeBrowser
2. When the **Analyze** dialog appears:
   - Select **"Analyze"** to start automatic analysis
   - A detailed analysis options dialog should appear

3. **Important Analysis Options to Enable** (check if not already checked):
   - ✅ **RTTI Analyzer** - Recognizes C++ virtual tables and class hierarchies
   - ✅ **Decompiler Parameter ID** - Identifies function parameters
   - ✅ **Function Start Search** - Finds additional function entry points
   - ✅ **Windows x86 PE Exception Handling** - Parses exception handling tables
   - ✅ **Windows x86 Thread Environment Block (TEB) Analyzer** - Windows-specific structures
   - ✅ **Call-Fixup Installer** - Fixes import calls
   - ✅ **Stack** - Analyzes stack frames
   - ✅ **Reference** - Analyzes cross-references
   - ⚠️ **PDB** - If you have PDB symbols, enable this (not needed for unpacked PAL3.exe)
   - ⚠️ **Scalar Operand References** - Optional, can slow analysis
   - ⚠️ **Function ID** - Optional, identifies library functions

4. Click **"Analyze"** to begin (this will take 10-30 minutes depending on your CPU)

### Step 5: Monitor Analysis Progress
- Look at the **Analysis Queue** window (Window → Analysis Queue if not visible)
- Watch for status messages showing which analyzer is running
- Status bar at bottom shows overall progress
- Analysis complete when queue shows "All tasks complete" or status says "Analysis complete"

**Expected metrics when analysis completes:**
- Function count: 3000-5000
- Data blocks: 1000+
- Strings: 2000+

### Step 6: Verify Analysis Results
1. Open **Functions window**: Window → Functions (Ctrl+F9)
2. Check function count in status bar
3. Test search: try searching for "WinMain" or common functions
4. Browse a few functions to verify decompilation looks reasonable

### Step 7: Save the Project
1. File → Save Project (Ctrl+S)
2. Project saved successfully when status bar updates
3. Verify files exist:
   - `D:\workspace\project-x\asm\pal3\PAL3.gpr` - Project file
   - `D:\workspace\project-x\asm\pal3\PAL3.rep\` - Repository directory (contains analysis)

## Automated Export (After Manual Analysis)

Once analysis is complete, run this to export function data:

```bash
cd D:\workspace\project-x
python tools/ghidra_export.py D:\workspace\project-x\asm\pal3 pal3.exe all
```

This will:
- Export all 3000+ functions
- Create JSON files in `asm/pal3/`
- Generate statistics summary

## Troubleshooting

### Java Not Found
If Ghidra shows "Java runtime not found":
```cmd
setx JAVA_HOME "C:\Java\jdk-17.0.8+7"
```
Then restart Ghidra.

### Ghidra Won't Start
1. Check Java version: `java -version` should show "openjdk version 17.0.8"
2. Try deleting Ghidra settings: `%APPDATA%\Ghidra\`
3. Check Event log in Windows for errors

### Import Fails
- Make sure PAL3.exe path is correct
- Ensure PAL3.exe is actually unpacked (not StarForce protected)
- Try re-extracting from backup if file seems corrupted

### Analysis Takes Too Long
- This is normal - Ghidra analyzes 2MB binary with 3000+ functions
- CPU usage should be high during analysis
- Consider running overnight if your machine is slow

### Analysis Produces Too Few Functions (<2000)
- Likely sign that analysis didn't complete properly
- Try running analysis again from menu: Analysis → Auto Analyze

## Expected Deliverables After This Task

1. **Ghidra Project**:
   - `asm/pal3/PAL3.gpr` - Project file
   - `asm/pal3/PAL3.rep/` - Repository with analysis data
   
2. **Analysis Log**:
   - `docs/pal3/ghidra_analysis_log.txt` - Function statistics

3. **Exported Functions** (optional, after analysis):
   - `asm/pal3/*.json` - Function definitions in JSON format

## Next Steps (Task 2)

After completing this analysis:
1. Export function data using Python script
2. Create function priority list
3. Begin matching decompilation of individual functions

See `docs/decompilation_workflow.md` for full workflow details.
