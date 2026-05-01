# Ghidra Export Tools

This directory contains Ghidra scripts for exporting PAL3.exe function data to JSON format for decompilation.

## Files

- **export_functions.py** - Ghidra Python script to export all functions to JSON
- **run_headless_export.bat** - Windows batch script to run the export in headless mode

## Prerequisites

1. **Ghidra Installation**: Ghidra 11.2+ installed at `D:\workspace\project-x\tools\ghidra\`
2. **Java Runtime**: Java 17+ installed at `C:\Java\jdk-17.0.8+7\`
3. **Ghidra Project**: PAL3.exe imported and analyzed in Ghidra project at `asm\pal3\PAL3.rep`

## Usage

### Method 1: Headless Export (Recommended)

Run the batch script to export all functions without opening the Ghidra GUI:

```batch
tools\ghidra\run_headless_export.bat
```

This will:
1. Validate the environment (Java, Ghidra, project)
2. Run Ghidra headless analysis with the export script
3. Export all functions to `asm\pal3\functions\*.json`
4. Create a summary index at `asm\pal3\pal3_functions.json`

### Method 2: GUI Export

If you need to run the export from within Ghidra:

1. Open Ghidra GUI
2. Open the PAL3 project
3. Open PAL3.exe in the CodeBrowser
4. Run the script:
   - Window → Script Manager
   - Find "export_functions.py" under PAL3.Export category
   - Click "Run Script"

## Output Format

### Individual Function Files

Each function is exported to: `asm/pal3/functions/FunctionName_ADDRESS.json`

Example: `WinMain_00401000.json`

```json
{
  "address": "0x00401000",
  "size_bytes": 1234,
  "calling_convention": "__cdecl",
  "signature": "int __cdecl WinMain(HINSTANCE hInstance, ...)",
  "callees": [
    {"address": "0x00401100", "name": "InitGame"}
  ],
  "global_refs": [
    {"address": "0x00500000", "type": null, "name": "g_hInstance"}
  ],
  "has_custom_name": true,
  "decompiled_c": "...",
  "is_thunk": false,
  "name": "WinMain",
  "assembly": "...",
  "callers": []
}
```

### Summary Index File

The summary is exported to: `asm/pal3/pal3_functions.json`

```json
{
  "program": "PAL3.exe",
  "image_base": "0x00400000",
  "total_functions": 5000,
  "exported_count": 5000,
  "external_count": 200,
  "functions": [
    {
      "address": "0x00401000",
      "name": "WinMain",
      "size_bytes": 1234,
      "signature": "int __cdecl WinMain(...)",
      "calling_convention": "__cdecl",
      "has_custom_name": true,
      "is_thunk": false,
      "callees_count": 10,
      "callers_count": 0,
      "global_refs_count": 5
    }
  ]
}
```

## JSON Schema

The exported JSON follows the same format used for gbengine.dll and topo.dll exports:

| Field | Type | Description |
|-------|------|-------------|
| address | string | Function entry point (e.g., "0x00401000") |
| size_bytes | number | Function size in bytes |
| calling_convention | string | Calling convention (__cdecl, __thiscall, etc.) |
| signature | string | Full function signature from Ghidra |
| callees | array | Functions called by this function |
| callers | array | Functions that call this function |
| global_refs | array | Global data references |
| has_custom_name | boolean | True if not a default "FUN_" name |
| decompiled_c | string/null | Ghidra-decompiled C code |
| is_thunk | boolean | True if this is a thunk function |
| name | string | Function name |
| assembly | string | Disassembled x86 code |

## Troubleshooting

### Error: "Ghidra project not found"

The Ghidra project hasn't been created yet. Complete **Task 1: Ghidra 项目设置和初步分析** first:

1. Open Ghidra GUI
2. Create new project: `PAL3` at `asm\pal3\`
3. Import `original\PAL3.exe`
4. Run auto-analysis
5. Save the project

### Error: "Java not found"

Install Java 17+ or update the `JAVA_HOME` path in `run_headless_export.bat`:

```batch
set JAVA_HOME=C:\Path\To\Your\Java
```

### Error: "Failed to decompile function"

Some functions may fail to decompile due to:
- Complex control flow
- Data embedded in code
- Anti-disassembly techniques

These functions will have `decompiled_c: null` in the JSON and can be manually decompiled later.

### Warning: "Large output"

PAL3.exe contains thousands of functions. The export may generate:
- 5,000+ JSON files (50-100 MB total)
- Export time: 10-30 minutes depending on CPU

This is expected and normal.

## Next Steps

After exporting functions:

1. Review `asm/pal3/pal3_functions.json` for overview
2. Proceed to **Task 3: 函数分类和优先级排序**
3. Use the JSON data for automated decompilation
4. Track progress in `build/progress.json`

## References

- Ghidra API Documentation: https://ghidra.re/ghidra_docs/api/
- Ghidra Scripting Guide: https://ghidra.re/ghidra_docs/GhidraClass/Intermediate/Scripting.html
- PAL3 Decompilation Workflow: `docs/decompilation_workflow.md`
