#pragma once
// Auto-generated: ScriptSystem

class ScriptSystem {
public:
    static void Render(void *a1); // 0x0040C630
    static int Cleanup(); // 0x0040C790
    static char Render2(); // 0x0040C7D0
    static int Destroy(); // 0x0040C960
    static int Execute(int a1, char a2); // 0x0040E5F0
    static int RunScript(int a1, int a2, int a3); // 0x004100A0
    static int RunWithDelay(float delay, int a2, int a3); // 0x004101F0
    static int RunEvent(int eventId, int a2, int a3); // 0x00410470
    static int UpdateTimers(float dt); // 0x00411F60
    static int UpdateObjects(float dt); // 0x004194C0
    static void Init(); // 0x0041EFA0
};
