"""
Reset structs whose PDB offsets don't match PAL3 binary.

These structs were imported from PAL3A PDB but their member offsets
are WRONG for PAL3 (different base class sizes between versions).

Replace with correctly-sized placeholders until individual binary analysis.
"""
import ida_auto, ida_typeinf, idc

ida_auto.auto_wait()

# (name, estimated_pal3_size) - sizes from binary max offset or operator new
# For large classes where we can't verify size, use a safe estimate
RESET = [
    # CEffect family: PDB base=+0x30, PAL3 base=+0x04 (shift = -0x2C)
    ("CEffMeteor", 512),
    ("CEffCylinder", 512),
    ("CEffExplosive", 1280),
    ("CEffGrid", 512),
    ("CEffQuad", 512),
    ("CEffShock", 512),
    ("CEffModel", 256),
    ("CEffSParticle", 128),
    ("CEffgbParticle", 80),

    # UI family: PDB base=+0x44/+0x48, PAL3 much smaller base
    ("UIStatic", 248),       # from operator new
    ("UIFrameWnd", 152),     # from operator new
    ("UIListBox", 1208),     # from operator new
    ("UIDialog", 128),
    ("CCBControlWindow", 84),# from operator new
    ("CCBItemWindow", 108),
    ("CCBMagicWindow", 180),
    ("CCBAIWindow", 256),
    ("CCBProtectWindow", 128),
    ("CCBParabolaWindow", 128),
    ("CCBSkillWindow", 128),
    ("CCBResultWindow", 256),

    # Scene/Script
    ("SceneObj", 256),
    ("CCBStageScene", 1024),
    ("CCBStageCam", 2048),

    # Large game classes
    ("MagicUI", 4096),
    ("StateUI", 4096),
    ("EquipUI", 4096),
    ("CEffMgr", 2304),

    # Misc
    ("PalScript", 64),
    ("ParabolaCalculator", 512),
    ("_Texture_Info", 1088),
    ("CCCTData", 4096),
    ("PAL_GDB", 8192),
    ("CCBStageScene", 1024),
]

reset_count = 0
for name, size in RESET:
    decl = "struct %s { char _data[%d]; };" % (name, size)
    nerr = idc.parse_decls(decl, idc.PT_TYP)
    if nerr == 0:
        reset_count += 1
    else:
        print("[!] %s: parse error %d" % (name, nerr))

print("[+] Reset %d structs to sized placeholders" % reset_count)
print("[*] These need individual binary analysis for proper member layout")

idc.qexit(0)
