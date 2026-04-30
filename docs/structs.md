# Known Data Structures

This file tracks all struct/class/typedef definitions discovered during decompilation.
Update this file whenever a new structure is confirmed through reverse engineering.

## Core Engine Types

```c
// Placeholder - to be filled as structures are discovered
// Example format:

// typedef struct {
//     float x, y, z;
// } Vec3;

// typedef struct {
//     float m[4][4];
// } Matrix4x4;
```

## Game Object Types

```c
// To be discovered during decompilation
```

## File Format Structures

```c
// CPK archive header (if custom format)
// SCE script bytecode structures
```

## DirectX Related

```c
// Wrappers around D3D structures (if any)
```

## Notes

- Struct member ordering matters for binary compatibility
- Pay attention to padding and alignment (#pragma pack)
- MSVC default packing is 8 bytes
- Verify each struct's size matches what Ghidra reports
