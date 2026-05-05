void PAL3A_RegisterScriptSubsystem(void);
int PAL3A_ScriptBootstrap(void);

int PAL3A_Bootstrap(void)
{
    PAL3A_RegisterScriptSubsystem();
    return PAL3A_ScriptBootstrap();
}
