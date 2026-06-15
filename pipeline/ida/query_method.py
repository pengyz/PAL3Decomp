"""Query raw IDB for all memory accesses with displacement in a specific function.
Run on raw IDB: idat -A -S"pipeline/ida/_query_method.py" original/PAL3.exe.raw.i64
"""
import idaapi
import idautils
import idc
import json
import os

idaapi.auto_wait()

# Functions to analyze
FUNCTIONS = [
    ("CCBProtectWindow::_scalar_dtor", 0x00516120),
    ("CCBProtectWindow::CCBProtectWindow", 0x0051D6E0),
    ("CCBProtectWindow::~CCBProtectWindow", 0x0051D6F0),
    ("CCBProtectWindow::Reset", 0x0051D700),
    ("CCBProtectWindow::Destroy", 0x0051DD80),
    ("CCBProtectWindow::OnCommand", 0x0051F0A0),
    ("CCBProtectWindow::ShowAndNotify", 0x00518E30),
    ("CCBProtectWindow::ValidateSlot", 0x00449BE0),
    ("CCBProtectWindow::OnMessage", 0x0051F1B0),
    ("CCBProtectWindow::_sdtor_19", 0x00516100),
    ("CCBProtectWindow::ShowWindow", 0x00445E70),
    ("CCBProtectWindow::Render", 0x0043DDF0),
    ("CCBProtectWindow::Destroy", 0x005164D0),
    ("CCBProtectWindow::Create", 0x00445B90),
    ("CCBProtectWindow::ForwardOnMessage", 0x0043D7A0),
    ("ScreenEffectMgr::UpdateFrontEffect", 0x004BE4A0),
    ("ScreenEffectMgr::GetInstance", 0x004BE590),
    ("ScreenEffectMgr::ProcessEffect", 0x004BE1A0),
    ("ScreenEffectMgr::ClearAllEffects", 0x004BE080),
    ("ScreenEffectMgr::GetFadeFlags", 0x004BE810),
    ("ScreenEffectMgr::RenderFadeOut", 0x004BE920),
    ("ScreenEffectMgr::RenderFadeIn", 0x004BEAB0),
    ("ScreenEffectMgr::ScreenEffectMgr", 0x004BEE60),
    ("ScreenEffectMgr::LoadResources", 0x004BEFB0),
    ("ScreenEffectMgr::IsScriptDelNeeded", 0x004BDF60),
    ("ScreenEffectMgr::StartFade", 0x004BDF70),
    ("ScreenEffectMgr::IsFadeWhiteHolding", 0x004BE5E0),
    ("ScreenEffectMgr::DrainQueue", 0x004BE5F0),
    ("ScreenEffectMgr::AllocEffectBlock", 0x004BE6B0),
    ("ScreenEffectMgr::ToggleFade", 0x004BE9C0),
    ("ScreenEffectMgr::StartFadeIn", 0x004BE9E0),
    ("ScreenEffectMgr::RenderFadeWhiteOut", 0x004BEC00),
    ("ScreenEffectMgr::RenderFadeWhiteIn", 0x004BED50),
    ("ScreenEffectMgr::UpdateAnimation", 0x004BF4F0),
    ("ScreenEffectMgr::GetPageIndex", 0x004BF680),
    ("ScreenEffectMgr::SetFadeParams", 0x004BF6C0),
    ("ScreenEffectMgr::ResetFadeState", 0x004BF760),
    ("ScreenEffectMgr::ProcessInstance", 0x0052F310),
    ("ScreenEffectMgr::IsFadeActive", 0x0052F330),
    ("ScreenEffectMgr::CleanupTextures", 0x004BF170),
    ("ScreenEffectMgr::sub_0054210E", 0x0054210E),
    ("ScreenEffectMgr::sub_005420DE", 0x005420DE),
    ("ScreenEffectMgr::sub_005420D8", 0x005420D8),
    ("ScreenEffectMgr::Render", 0x004BF260),
    ("ScreenEffectMgr::Destroy", 0x004BF1D0),
    ("ScreenEffectMgr::Create", 0x004BF1C0),
    ("MainPropUI::~MainPropUI", 0x004909F0),
    ("MainPropUI::SetPage", 0x0048C4A0),
    ("MainPropUI::ShowPage", 0x00491B40),
    ("MainPropUI::ShowSubPanels", 0x00492BB0),
]

results = {}

for func_name, func_va in FUNCTIONS:
    func = idaapi.get_func(func_va)
    if not func:
        results[func_name] = {"error": f"no function at {hex(func_va)}"}
        continue

    accesses = []
    ea = func.start_ea
    while ea < func.end_ea:
        insn = idaapi.insn_t()
        length = idaapi.decode_insn(insn, ea)
        if length <= 0:
            ea += 1
            continue

        for op_idx in range(6):
            op = insn.ops[op_idx]
            if op.type == 0:
                break
            if op.type in (idaapi.o_displ, idaapi.o_phrase):
                disp = op.addr if hasattr(op, 'addr') else 0
                if disp > 0 and disp < 0x10000:
                    reg_names = {0:'eax',1:'ecx',2:'edx',3:'ebx',4:'esp',5:'ebp',6:'esi',7:'edi'}
                    base_reg = reg_names.get(op.reg, f'r{op.reg}')
                    mnem = idc.print_insn_mnem(ea)
                    disasm = idc.generate_disasm_line(ea, 0)
                    dtype_sizes = {0:1, 1:2, 2:4, 3:8, 4:10, 5:16}
                    width = dtype_sizes.get(op.dtype, 4)
                    accesses.append({
                        "va": f"0x{ea:08X}",
                        "disp": f"0x{disp:X}",
                        "base_reg": base_reg,
                        "mnem": mnem,
                        "width": width,
                        "disasm": disasm,
                        "op_idx": op_idx,
                    })
        ea += length

    results[func_name] = accesses

out_path = os.path.join(os.path.dirname(__file__), "_logs", "method_accesses.json")
os.makedirs(os.path.dirname(out_path), exist_ok=True)
with open(out_path, "w", encoding="utf-8") as f:
    json.dump(results, f, indent=2, ensure_ascii=False)

print(f"Saved to {out_path}")
for name, data in results.items():
    if isinstance(data, list):
        print(f"  {name}: {len(data)} accesses")
    else:
        print(f"  {name}: {data}")

idc.qexit(0)
