/**
 * PAL3 Decompilation - Master Header
 *
 * Include this single file in all decompiled source files.
 * It pulls in all necessary type definitions, globals, and platform headers.
 */

#ifndef PAL3_H
#define PAL3_H

/* Build configuration (must be first) */
#include "pal3_config.h"

/* Windows and standard headers */
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Project headers */
#include "pal3_types.h"
#include "pal3_structs.h"
#include "pal3_globals.h"

#endif /* PAL3_H */
