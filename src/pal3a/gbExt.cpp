#include "gbExt.h"
#include <stdio.h>

static FILE *g_logfile = NULL;

void _InitLogFile()
{
    if (g_logfile)
        return;
    g_logfile = fopen("PAL3A.log", "w");
}

void _WriteLogString(char *s)
{
    if (!g_logfile)
        return;
    fprintf(g_logfile, "%s\n", s);
    fflush(g_logfile);
}
