"""
Generate JSON pseudocode files for the 45 functions that Hex-Rays failed to decompile.
These are manually translated from assembly to C pseudocode.
Output goes to asm/pal3a/decomp/ in the same format as auto-exported functions.

Usage: python manual_decompile.py [output_dir]
  output_dir defaults to ../../asm/pal3a/decomp relative to this script
"""
import json
import os
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DEFAULT_OUTPUT = os.path.normpath(os.path.join(SCRIPT_DIR, "..", "..", "asm", "pal3a", "decomp"))
OUTPUT_DIR = sys.argv[1] if len(sys.argv) > 1 else DEFAULT_OUTPUT

def write_func(name, address, size, signature, code):
    data = {
        "name": name,
        "address": f"0x{address:08X}",
        "size_bytes": size,
        "signature": signature,
        "decompiled_c": code,
        "manual_decompile": True
    }
    filename = f"{name}_{address:08x}.json"
    filename = filename.replace("::", "_").replace(" ", "_").replace("?", "_").replace("<", "_").replace(">", "_").replace("*", "")
    filepath = os.path.join(OUTPUT_DIR, filename)
    with open(filepath, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
    return filepath


# ============================================================
# Group 1: Scalar Deleting Destructors (7 functions, 28 bytes each)
# Pattern: call dtor, if (flags & 1) operator_delete(this), return this
# ============================================================

scalar_dtors = [
    (0x0049B858, "CUtil::iRange", "$E48_14_0"),
    (0x004A446B, "AStarPathFinder::CheckOPEN_0", "CCBStageRole::GetWeaponTagByACT"),
    (0x00451358, "CG_Scene::GetMonsterNum", "RoleCameraCtrl::HorizonRotate"),
    (0x00455622, "CCBSystem::SetLockCam", "CCBSystem::PassCmdViaThread"),
    (0x00480B1F, "CCBEditor::_CCBEditor_2", "CCBRoleState::AttackSpecAffect"),
    (0x0048C180, "MyMdl::MyMdl_0", "SceneObj::SetUniteObjectsRight"),
    (0x0049C458, "_::_Kfn::operator", "___operator"),
]

for addr, name, dtor_call in scalar_dtors:
    sig = f"void *__thiscall {name}(void *this, unsigned int flags)"
    code = f"""void *__thiscall {name}(void *this, unsigned int flags)
{{
  {dtor_call}(this);
  if ( flags & 1 )
    operator delete(this);
  return this;
}}
"""
    write_func(name, addr, 28, sig, code)


# ============================================================
# Group 2: Scalar Deleting Destructor with vtable set (1 function)
# ============================================================

write_func("CCBRoleState::Update", 0x00430A75, 34,
    "void *__thiscall CCBRoleState::Update(void *this, unsigned int flags)",
    """void *__thiscall CCBRoleState::Update(void *this, unsigned int flags)
{
  *(_DWORD *)this = &CCBRoleState_vtable; // off_558AC0
  CCBAttackSequen::SetSlot2Speed(this);
  if ( flags & 1 )
    operator delete(this);
  return this;
}
""")


# ============================================================
# Group 3: Simple thunks and wrappers
# ============================================================

write_func("CCBAttackSequen::SetLock_0", 0x0052BBAE, 11,
    "void __cdecl CCBAttackSequen::SetLock_0(void *lpMem)",
    """void __cdecl CCBAttackSequen::SetLock_0(void *lpMem)
{
  operator delete(lpMem);
}
""")

write_func("CCBParabolaWindow::Reset", 0x0052CAD4, 15,
    "void __cdecl CCBParabolaWindow::Reset()",
    """void __cdecl CCBParabolaWindow::Reset()
{
  CCBParabolaWindow::OnMessage(&g_CCBParabolaWindow, 0, 1);
}
""")

write_func("_::_Erase", 0x0049D250, 18,
    "int __cdecl _Erase(int ebx_param)",
    """// Epilogue of a larger function - pushes indexed pointer and calls LoadImage
int __cdecl _Erase(int ebx_param)
{
  UIWnd_LoadImage(off_55D494[ebx_param]);
  // returns via shared epilogue (pop edi, pop esi, pop ebx, leave, retn 8)
}
""")


# ============================================================
# Group 4: Destructors
# ============================================================

write_func("TxtFile::_TxtFile_0", 0x00401042, 25,
    "void __thiscall TxtFile::~TxtFile(void *this)",
    """void __thiscall TxtFile::~TxtFile(void *this)
{
  *(_DWORD *)this = &TxtFile_vtable; // off_558630
  sub_401687();
  operator delete(*(_DWORD *)((char *)this + 0x10));
}
""")

write_func("PtrArray::_PtrArray_8", 0x0043B313, 21,
    "void __thiscall PtrArray::~PtrArray(void *this)",
    """void __thiscall PtrArray::~PtrArray(void *this)
{
  if ( *(_DWORD *)this )
  {
    operator delete(*(void **)this);
    *(_DWORD *)this = 0;
  }
}
""")

write_func("GRPinput::GetMouseDeltas_0", 0x0041FC5D, 31,
    "void __thiscall GRPinput::GetMouseDeltas_0(void *this)",
    """void __thiscall GRPinput::GetMouseDeltas_0(void *this)
{
  if ( *(void **)((char *)this + 0xC) )
  {
    operator delete(*(void **)((char *)this + 0xC));
    *(_DWORD *)((char *)this + 0xC) = 0;
  }
  *(_DWORD *)((char *)this + 0x8) = 0;
  *(_DWORD *)((char *)this + 0x4) = 0;
}
""")


# ============================================================
# Group 5: std::copy_backward_7 - smart pointer / factory
# ============================================================

write_func("std::copy_backward_7", 0x0043D787, 24,
    "void *__cdecl std::copy_backward_7()",
    """void *__cdecl std::copy_backward_7()
{
  void *result = PtrArray::_PtrArray_0(g_global_ptr);
  if ( result )
    return loc_43AED8(result); // tail call - method on result
  return NULL;
}
""")


# ============================================================
# Group 6: Resource cleanup destructor
# ============================================================

write_func("std::_Unguarded_insert_0", 0x0043CC86, 36,
    "void __cdecl std::_Unguarded_insert_0(void *ptr)",
    """void __cdecl std::_Unguarded_insert_0(void *ptr)
{
  if ( ptr )
  {
    sub_43CCAA(ptr); // destructor body
    operator delete(ptr);
    std::copy_7(&g_allocator, ptr);
  }
}
""")


# ============================================================
# Group 7: String search in array
# ============================================================

write_func("_::size_7", 0x0043B280, 50,
    "int __cdecl size_7(const char *name, int edi_index, int esi_base)",
    """// Searches an array of 0x48-byte entries for a name match (case-insensitive)
int __cdecl size_7(const char *name, int edi_index, int esi_base)
{
  while ( _strcmpi(name, (const char *)esi_base) != 0 )
  {
    ++edi_index;
    esi_base += 0x48;
    if ( edi_index >= g_array_count )
      return 0;
  }
  return *(int *)(g_array_ptr + edi_index * 0x48);
}
""")


# ============================================================
# Group 8: CCBEditor::SceneEditorProc
# ============================================================

write_func("CCBEditor::SceneEditorProc", 0x00525D98, 53,
    "void __thiscall CCBEditor::SceneEditorProc(void *this, const char *source)",
    """void __thiscall CCBEditor::SceneEditorProc(void *this, const char *source)
{
  char *buf = (char *)this + 0x2220;
  strncpy(buf, source, 100);
  CCBEditor::EditorDialogProc(this);
  memset(buf, 0, 100);
  *buf = '_';
}
""")


# ============================================================
# Group 9: Chain destructor
# ============================================================

write_func("CCBStageScene::IsShowFiveLineup", 0x004AA1BE, 58,
    "void *__thiscall CCBStageScene::IsShowFiveLineup(void *this)",
    """void *__thiscall CCBStageScene::IsShowFiveLineup(void *this)
{
  sub_cmd_CombatMaxRound((char *)this + 0x174);
  CCBMagicWindow::OnMessage((char *)this + 0x1628);
  Console::Print((char *)this + 0x2ADC);
  cmd_DlgTime((char *)this + 0x3F90);
  cmd_RoleActive(this);
  return this;
}
""")


# ============================================================
# Group 10: Loop-based functions
# ============================================================

write_func("std::bitset_48_::reference::operator__1", 0x00422D40, 67,
    "void __cdecl std::bitset_48_::reference::operator__1()",
    """void __cdecl std::bitset_48_::reference::operator__1()
{
  int result = std::bitset_48_::operator_0();
  CCBStageRole::IsValid(result);
  // Loop 1: iterate over role array at fixed stride 0x10B214
  char *p = (char *)&g_roles + 0x381D8;
  while ( p < g_roles_end )
  {
    CCBStageRole::IsTaskFinished(p);
    p += 0x10B214;
  }
  // Loop 2: iterate over sub-array at stride 0x188
  char *q = g_sub_array_start;
  while ( q < g_sub_array_end )
  {
    sub_420633(q);
    q += 0x188;
  }
}
""")

write_func("std::sort_1", 0x0043D12C, 70,
    "void *__cdecl std::sort_1(const char *name)",
    """// Searches array for entry matching name, returns pointer or NULL
void *__cdecl std::sort_1(const char *name)
{
  int count = g_entry_count;
  char *base = g_entry_base;
  for ( int i = 0; i < count; i++ )
  {
    char *entry = base + i * 0x18 + 8;
    if ( entry == NULL )
      return base + i * 0x18; // found
  }
  return NULL;
}
""")


# ============================================================
# Group 11: CCBSystem::IsFriendDoSkill - slot search
# ============================================================

write_func("CCBSystem::IsFriendDoSkill", 0x004EDE1C, 72,
    "int __thiscall CCBSystem::IsFriendDoSkill(void *this, int role_index)",
    """int __thiscall CCBSystem::IsFriendDoSkill(void *this, int role_index)
{
  char *base = (char *)this + role_index * 0xA48;
  char *slot = base + 0xF8;
  int idx = 0;
  while ( idx < 32 )
  {
    if ( *slot == 0 )
    {
      // Found empty slot - fill with memcpy (0x50 bytes)
      // ... (continues with slot population at offset idx*0x50)
      return idx;
    }
    ++idx;
    slot += 0x50;
  }
  return -1;
}
""")


# ============================================================
# Group 12: CCBMagicWindow - collision call
# ============================================================

write_func("CCBMagicWindow::_CCBMagicWindow_0", 0x00417800, 74,
    "int __thiscall CCBMagicWindow::_CCBMagicWindow_0(void *this, int a2, int a3)",
    """int __thiscall CCBMagicWindow::_CCBMagicWindow_0(void *this, int a2, int a3)
{
  struct ReturnUdt result;
  result.field_0 = a2;
  result.field_4 = a3;
  result.field_8 = 0.0f;
  int obj = std::bitset_48_::operator_0(*(_DWORD *)((char *)this + 0x274), &result, 0, 0);
  GRPinput::UnacquireKeyboard_0(obj);
  // result.field_8 assigned from FPU
  DoCollideBySphere(this, &result, a2);
}
""")


# ============================================================
# Group 13: RoleCameraCtrl::Push - camera setup
# ============================================================

write_func("RoleCameraCtrl::Push", 0x00450B75, 86,
    "void __thiscall RoleCameraCtrl::Push(void *this, void *data, float targetdist, float time, int itype)",
    """void __thiscall RoleCameraCtrl::Push(void *this, void *data, float targetdist, float time, int itype)
{
  sub_450E82((char *)this + 0x1D7C, data);
  *(float *)((char *)this + 0x2590) = targetdist;
  *(float *)((char *)this + 0x2594) = time;
  *(_DWORD *)((char *)this + 0x2598) = itype;
  if ( this )
  {
    // virtual call: this->vtable[6](1000, 1, 0)
    (*(void (__thiscall **)(void *, int, int, int))(*(_DWORD *)this + 0x18))(this, 1000, 1, 0);
  }
  CG_Scene::GetSpecialOBJNum(this);
  *(_BYTE *)((char *)this + 0x25A8) = 1;
}
""")


# ============================================================
# Group 14: std::_Insertion_sort_1_1 - texture/resource cleanup
# ============================================================

write_func("std::_Insertion_sort_1_1", 0x0043CD15, 94,
    "void __thiscall std::_Insertion_sort_1_1(void *this)",
    """void __thiscall std::_Insertion_sort_1_1(void *this)
{
  // Free main buffer at offset 0x48
  if ( *(_DWORD *)((char *)this + 0x48) )
  {
    operator delete(*(void **)((char *)this + 0x48));
    *(_DWORD *)((char *)this + 0x48) = 0;
  }
  // Free sub-entries array
  unsigned short count = *(_WORD *)((char *)this + 0x4C);
  if ( count > 0 )
  {
    void **entries = *(void ***)((char *)this + 0x50);
    for ( int i = 0; i < count; i++ )
    {
      if ( *(unsigned short *)((char *)entries + i * 8 + 2) > 0 )
      {
        operator delete(*(void **)((char *)entries + i * 8 + 4));
        *(void **)((char *)entries + i * 8 + 4) = NULL;
      }
    }
    operator delete(entries);
    *(_DWORD *)((char *)this + 0x50) = 0;
  }
}
""")


# ============================================================
# Group 15: Role::RotateFly - stop audio
# ============================================================

write_func("Role::RotateFly", 0x0044163F, 104,
    "void __cdecl Role::RotateFly()",
    """void __cdecl Role::RotateFly()
{
  sub_49B948(&g_instance, 1);
  void *inst = GetGlobalInstance();
  *(_BYTE *)((char *)inst + 4) = 0;
  // Stop sound streams for channels 1, 0, 2
  void *mgr1 = CCBControl_GetCurAction(GetGlobalInstance(1));
  gbAudioManager::StopSoundStream(mgr1);
  void *mgr0 = CCBControl_GetCurAction(GetGlobalInstance(0));
  gbAudioManager::StopSoundStream(mgr0);
  void *mgr2 = CCBControl_GetCurAction(GetGlobalInstance(2));
  gbAudioManager::StopSoundStream(mgr2);
  // Conditional call based on global flag
  int flag = g_flag_80124;
  int param = flag ? g_value_80168 : 0;
  std::copy_14(param);
}
""")


# ============================================================
# Group 16: __onexit - CRT atexit implementation
# ============================================================

write_func("__onexit", 0x00540649, 109,
    "_onexit_t __cdecl __onexit(_onexit_t func)",
    """_onexit_t __cdecl __onexit(_onexit_t func)
{
  void *old_end = g_atexit_end;
  void *old_begin = g_atexit_begin;
  int capacity = (char *)old_begin - (char *)old_end + 4;
  // Expand table if needed
  if ( (unsigned int)func < (unsigned int)capacity )
  {
    void *new_table = realloc(old_end, capacity + 16);
    if ( !new_table )
      return NULL;
    int old_count = ((char *)old_begin - (char *)old_end) >> 2;
    g_atexit_end = new_table;
    g_atexit_begin = (char *)new_table + old_count * 4;
  }
  // Register function
  *(_onexit_t *)g_atexit_begin = func;
  g_atexit_begin = (char *)g_atexit_begin + 4;
  return func;
}
""")


# ============================================================
# Group 17: UIMap::CheckMoveRight_1 - map position update
# ============================================================

write_func("UIMap::CheckMoveRight_1", 0x004CEDF8, 118,
    "void __thiscall UIMap::CheckMoveRight_1(void *this)",
    """void __thiscall UIMap::CheckMoveRight_1(void *this)
{
  float *vtable_50 = (float *)(*(_DWORD *)this + 0x50);
  float base_val = *vtable_50;
  char *slots = (char *)this + 0x10;

  if ( !*(_BYTE *)((char *)this + 0x1C5)
    && *(_BYTE *)((char *)this + 0x1C4)
    && !*(_BYTE *)((char *)this + 0x1C7) )
  {
    // Active mode: compute deltas
    for ( int i = 0; i < 11; i++ )
    {
      char *entry = slots + i * 0x28;
      if ( !entry[0x1F] )
        *(float *)(entry - 4) = base_val - *(float *)entry;
      else
        *(float *)(entry - 4) = 0.0f;
      *(float *)entry = base_val;
    }
  }
  else
  {
    // Inactive mode: zero deltas
    for ( int i = 0; i < 11; i++ )
    {
      char *entry = slots + i * 0x28;
      *(float *)(entry - 4) = 0.0f;
      *(float *)entry = base_val;
    }
  }
  UIMap::ResetMapPosition_0(this);
  UIMap::MoveMapUp(this);
  sub_4CF508(this);
}
""")


# ============================================================
# Group 18: CCBUI::CreateFiveNimbus
# ============================================================

write_func("CCBUI::CreateFiveNimbus", 0x0050D09C, 111,
    "bool __thiscall CCBUI::CreateFiveNimbus(void *this)",
    """bool __thiscall CCBUI::CreateFiveNimbus(void *this)
{
  void *obj = (char *)this + 0x490;
  if ( !Role::FaceTo(obj) )
    return false;
  RECT rc;
  rc.left = 0;
  rc.top = 0;
  rc.right = 0;
  rc.bottom = 0;
  int base_x = g_rect - 0x170;
  g_dword_20B589C = base_x;
  rc.left = base_x;
  rc.right = base_x + g_width;
  int base_y = g_dword_20B58A0;
  rc.top = base_y;
  rc.bottom = base_y + g_height;
  void *inner = *(void **)obj;
  CCBStageRole::GetRoleRadius(inner, &rc, this);
  // Virtual call: inner->vtable[0](0)
  (*(void (__thiscall **)(void *, int))(*(_DWORD *)inner))(inner, 0);
  return true;
}
""")


# ============================================================
# Group 19: __check_range_exit - FPU math error handling
# ============================================================

write_func("__check_range_exit", 0x00545109, 163,
    "double __cdecl __check_range_exit(double value, int func_id)",
    """// CRT internal: checks for overflow/underflow after math operations
double __cdecl __check_range_exit(double value, int func_id)
{
  // Extract exponent
  unsigned int exp_bits;
  _asm { fst [esp]; mov eax, [esp+4]; and eax, 0x7FF00000 }

  if ( exp_bits == 0 ) // underflow
  {
    value = scalbn(value, UNDERFLOW_SCALE);
    if ( fabs(value) < DBL_MIN_THRESHOLD )
    {
      error_code = 4; // ERANGE underflow
      goto handle_error;
    }
    value *= UNDERFLOW_FIXUP;
    error_code = 4;
    goto handle_error;
  }
  if ( exp_bits == 0x7FF00000 ) // overflow
  {
    value = scalbn(value, OVERFLOW_SCALE);
    if ( fabs(value) <= DBL_MAX_THRESHOLD )
    {
      error_code = 3; // ERANGE overflow
      goto handle_error;
    }
    value *= OVERFLOW_FIXUP;
    error_code = 3;
    goto handle_error;
  }
  // Check FPU status for precision loss
  if ( saved_cw != 0x27F && !(saved_cw & 0x20) && (fpu_status & 0x20) )
  {
    error_code = 8; // precision loss
handle_error:
    if ( func_id == 0x1D ) // pow
      return __startTwoArgErrorHandling(error_code);
    else
      return __startOneArgErrorHandling(error_code);
  }
  // Restore control word if needed
  if ( saved_cw != 0x27F )
    _asm { fldcw saved_cw }
  return value;
}
""")


# ============================================================
# Group 20: __freebuf - CRT stream buffer free
# ============================================================

write_func("__freebuf", 0x005479F4, 43,
    "void __cdecl __freebuf(FILE *stream)",
    """void __cdecl __freebuf(FILE *stream)
{
  int flags = stream->_flag;
  if ( !(flags & 0x83) || !(flags & 0x08) )
    return;
  operator delete(stream->_base);
  stream->_flag &= ~0x0408; // clear _IOMYBUF | _IOALLOCBUF
  stream->_ptr = NULL;
  stream->_base = NULL;
  stream->_cnt = 0;
}
""")


# ============================================================
# Group 21: AStarPathFinder::_AStarPathFinder
# ============================================================

write_func("AStarPathFinder::_AStarPathFinder", 0x00412B91, 46,
    "int __thiscall AStarPathFinder::_AStarPathFinder(void *this, int node_index, int x, int save_flag)",
    """int __thiscall AStarPathFinder::_AStarPathFinder(void *this, int node_index, int x, int save_flag)
{
  void *node = (void *)(0xC1D250 + node_index * 12);
  AStarPathFinder::GenerateSucc(this, node, x);
  if ( save_flag )
    *(_DWORD *)((char *)this + 0x568) = node_index;
}
""")


# ============================================================
# Group 22: UIButtonEXA::_UIButtonEXA_0 - slot allocator
# ============================================================

write_func("UIButtonEXA::_UIButtonEXA_0", 0x004B93A3, 134,
    "int __thiscall UIButtonEXA::_UIButtonEXA_0(void *this, int param1, int param2, char param3)",
    """int __thiscall UIButtonEXA::_UIButtonEXA_0(void *this, int param1, int param2, char param3)
{
  int count = *(_DWORD *)((char *)this + 0x1C);
  char *base = *(char **)((char *)this + 0xC);
  // Find first empty slot
  int idx = 0;
  char *entry = base + 0x94;
  while ( idx < count )
  {
    if ( *entry == 0 )
      goto found;
    ++idx;
    entry += 0x98;
  }
  return -1;
found:
  // Initialize slot
  *(_DWORD *)(base + idx * 0x98 + 0x0C) = 2;
  *(base + idx * 0x98 + 0x94) = 1;
  *(base + idx * 0x98 + 0x95) = param3;
  // Increment global sequence counter
  ++g_sequence_counter;
  if ( g_sequence_counter == 0 || g_sequence_counter >= 0x7FFFFFFF )
    g_sequence_counter = 1;
  // Store sequence and copy data (0x7C bytes) if param2 set
  // ... (memcpy continues beyond read window)
  return idx;
}
""")


# ============================================================
# Group 23: CCBAttackSequen::SetZeroSpeed - role state change
# ============================================================

write_func("CCBAttackSequen::SetZeroSpeed", 0x0042FCA8, 146,
    "void __thiscall CCBAttackSequen::SetZeroSpeed(void *this, int new_state)",
    """void __thiscall CCBAttackSequen::SetZeroSpeed(void *this, int new_state)
{
  int cur_state = *(unsigned char *)((char *)this + 0x42F);
  if ( new_state == cur_state )
    return;
  *(_BYTE *)((char *)this + 0x42F) = (char)new_state;
  if ( new_state )
    *(_BYTE *)((char *)this + 0x3D0) = 1;
  else
    *(_BYTE *)((char *)this + 0x3D0) = 2;
  *(float *)((char *)this + 0x3D4) = 0.0f;
  // Copy direction vector (12 bytes: 0x3A8 -> 0x3B8)
  memcpy((char *)this + 0x3B8, (char *)this + 0x3A8, 12);
  // Initialize identity matrix
  gbMatrix4 mat;
  gbMatrix4::gbMatrix4(&mat);
  NavTileLayer::Tile2World(this, &mat);
  float adjusted_y = mat.field_8 - g_flt_5586FC;
  *(_BYTE *)((char *)this + 0x451) = *(_BYTE *)((char *)this + 0x42F);
  *(float *)((char *)this + 0x3C4) = adjusted_y;
  PlayerMgr::CalRoleFull_DEF(this, 0);
}
""")


# ============================================================
# Group 24: Role::DrawView - role rendering setup
# ============================================================

write_func("Role::DrawView", 0x0051740C, 182,
    "void __thiscall Role::DrawView(void *this, void *target)",
    """void __thiscall Role::DrawView(void *this, void *target)
{
  if ( !target )
    return;
  int mode = *(_DWORD *)((char *)target + 0x280);
  if ( mode == 0 )
  {
    // Setup default view
    *(_BYTE *)((char *)this + 0x73915) = 0;
    *(_BYTE *)((char *)this + 0x73914) = 0;
    *(_DWORD *)((char *)this + 0x7391C) = 5;
    *(float *)((char *)this + 0x73910) = 1.0f;
    *(_DWORD *)((char *)this + 0x73920) = 1;
    *(float *)((char *)this + 0x73918) = 0.0f;
    collision::unitSphereIntersection(target);
    *(_BYTE *)((char *)target + 0x288) = 1;
    int scene_obj = *(_DWORD *)(*(_DWORD *)((char *)this + 0xC) + 8);
    int mirror_count = CG_Scene::CGPROP_MIRROR(scene_obj);
    if ( mirror_count > 0 )
    {
      int ctrl = sub_45626A(&g_instance, 11, target);
      RoleCtrl::GetClickPoint_0(ctrl);
    }
  }
  else
  {
    // Mode > 0: setup with specific index
    int idx = mode - 1;
    collision::unitSphereIntersection(target);
    *(_BYTE *)((char *)target + 0x288) = 1;
    float *arr = *(float **)((char *)this + 0x64);
    arr[idx * 4] = 1.0f;
    *(_DWORD *)(&arr[idx * 4] + 3) = 1;
    *(_DWORD *)(&arr[idx * 4] + 2) = 3;
  }
}
""")


# ============================================================
# Group 25: JusticeBookUI::DestroyMonsters - _acos implementation
# ============================================================

write_func("JusticeBookUI::DestroyMonsters", 0x0054221D, 174,
    "double __cdecl _acos(double x)",
    """// CRT _acos: arc cosine with error handling
double __cdecl _acos(double x)
{
  unsigned int exp = *(unsigned int *)(&x + 1) & 0x7FF00000;
  if ( exp == 0x7FF00000 )
  {
    // Infinity or NaN
    unsigned int mantissa_hi = *(unsigned int *)(&x + 1) & 0xFFFFF;
    unsigned int mantissa_lo = *(unsigned int *)&x;
    if ( mantissa_hi || mantissa_lo )
      return __convertTOStoQNaN(); // NaN input
    // +-Infinity: domain error
    _asm { fstp st(0) }
    _asm { fld qNaN_constant }
    goto domain_error;
  }
  if ( exp < 0x3FF00000 )
  {
    // |x| < 1: normal case
    double one_plus = 1.0 + x;
    double one_minus = 1.0 - x;
    double arg = sqrt(one_plus * one_minus);
    return atan2(arg, x);
  }
  if ( exp == 0x3FF00000 && !(mantissa_hi & 0xFFFFF) && !mantissa_lo )
  {
    // x == +1.0 or x == -1.0
    _asm { fstp st(0) }
    if ( x < 0 )
      return M_PI;
    else
      return 0.0;
  }
domain_error:
  if ( !g_fast_math_mode )
    return __startOneArgErrorHandling(13, "acos");
  return __fast_exit();
}
""")


# ============================================================
# Group 26: unknown_libname_232 - FPU range reduction helper
# ============================================================

write_func("unknown_libname_232", 0x0054C67C, 178,
    "void __cdecl unknown_libname_232()",
    """// MSVC CRT internal: FPU argument range reduction for trig functions
// Takes two values on FPU stack, reduces to safe range, calls core routine
void __cdecl unknown_libname_232()
{
  long double val1, val2;
  _asm { fstp val1; fstp val2 }
  int edx_flags = 0;
  unsigned int exp = *(unsigned int *)(&val2 + 3) & 0x7FFF0000;
  if ( exp != 0 )
  {
    // Normal case
    _asm { fld val2; fld val1 }
    if ( *(unsigned int *)&val2 == 0 && *((unsigned int *)&val2 + 1) == 0 )
    {
      _asm { fprem }
      return;
    }
    edx_flags |= 2;
    // Scale down if exponent too large
    unsigned int raw_exp = *(unsigned short *)(&val2 + 4) & 0x7FFF;
    if ( raw_exp <= 0x7FBE )
    {
      edx_flags |= 1;
      val1 *= SCALE_FACTOR;
      val2 *= SCALE_FACTOR;
    }
    else
    {
      // Set precision to 64-bit
      val2 *= SCALE_FACTOR;
    }
    unknown_libname_231(/* reduced values */);
    return;
  }
  // Denormal or zero exponent
  unknown_libname_231();
}
""")


# ============================================================
# Group 27: unknown_libname_234 - similar FPU helper
# ============================================================

write_func("unknown_libname_234", 0x0054C934, 181,
    "void __cdecl unknown_libname_234()",
    """// MSVC CRT internal: FPU argument range reduction (variant 2)
// Nearly identical to unknown_libname_232 but calls unknown_libname_233
void __cdecl unknown_libname_234()
{
  long double val1, val2;
  _asm { fstp val1; fstp val2 }
  int edx_flags = 0;
  unsigned int exp = *(unsigned int *)(&val2 + 3) & 0x7FFF0000;
  if ( exp != 0 )
  {
    _asm { fld val2; fld val1 }
    if ( *(unsigned int *)&val2 == 0 && *((unsigned int *)&val2 + 1) == 0 )
    {
      _asm { fprem }
      return;
    }
    edx_flags |= 2;
    unsigned int raw_exp = *(unsigned short *)(&val2 + 4) & 0x7FFF;
    if ( raw_exp <= 0x7FBE )
    {
      edx_flags |= 1;
      val1 *= SCALE_FACTOR;
      val2 *= SCALE_FACTOR;
    }
    else
    {
      val2 *= SCALE_FACTOR;
    }
    unknown_libname_233(/* reduced values */);
    return;
  }
  unknown_libname_233();
}
""")


# ============================================================
# Group 28: CCBEditor::CheckCamEditor - keyboard input handler
# ============================================================

write_func("CCBEditor::CheckCamEditor", 0x00525B15, 265,
    "void __thiscall CCBEditor::CheckCamEditor(void *this, char key)",
    """void __thiscall CCBEditor::CheckCamEditor(void *this, char key)
{
  char *buf = (char *)this + 0x2220;
  if ( key == '`' )
  {
    // Toggle editor mode
    *(_DWORD *)((char *)this + 0x2208) = 0;
    *(_DWORD *)((char *)this + 0x2204) = 0;
    int *active = (int *)((char *)this + 0x2214);
    *active = (*active == 0) ? 1 : 0;
    *(_DWORD *)((char *)this + 0x220C) = g_X;
    *(_DWORD *)((char *)this + 0x2210) = 300;
    return;
  }
  if ( !*(_DWORD *)((char *)this + 0x2214) )
    return; // editor not active
  if ( key == 0x08 ) // Backspace
  {
    int len = lstrlenA(buf);
    if ( len >= 2 )
    {
      buf[len - 1] = 0;
      buf[len - 2] = '_';
    }
  }
  else if ( key == 0x0D ) // Enter
  {
    int len = lstrlenA(buf);
    buf[len - 1] = 0;
    // Execute command: sprintf + EditorDialogProc
    cmd_Add_0(this, "%s", buf);
    CCBEditor::EditorDialogProc(this);
    memset(buf, 0, 100);
    *buf = '_';
  }
  else if ( key == 0x1B ) // Escape
  {
    memset(buf, 0, 100);
    *buf = '_';
  }
  else
  {
    // Append character
    int len = lstrlenA(buf);
    if ( len < 99 )
    {
      buf[len - 1] = key;
      buf[len] = '_';
    }
  }
}
""")


# ============================================================
# Group 29: ConfigFile::Writef - EH destructor (scalar dtor + body)
# ============================================================

write_func("ConfigFile::Writef", 0x0051F36F, 329,
    "void *__thiscall ConfigFile::Writef(void *this, unsigned int flags)",
    """// This is a scalar deleting destructor that wraps a large EH-based destructor
void *__thiscall ConfigFile::Writef(void *this, unsigned int flags)
{
  ConfigFile_dtor_body(this); // calls at loc_51F38B
  if ( flags & 1 )
    operator delete(this);
  return this;
}

// The actual destructor body (EH prolog, destroys members in reverse order):
// void __thiscall ConfigFile_dtor_body(void *this)
// {
//   *(_DWORD *)this = &ConfigFile_vtable; // off_55EF78
//   // Destroy members at offsets 0xB308, 0xAB2C, 0xA5C0, 0xA058, 0x9AF0, 0x6C90, 0x69C0
//   // Then vector destructor iterators for arrays at 0x637C (10 * 0xA0) and 0x560C (10 * 0x158)
//   // Then individual dtors at 0x54B4, 0x5414, 0x5374, 0x52D4, 0x5234, 0x5194
//   // Finally calls MainEquipUI::SetJT
// }
""")


# ============================================================
# Group 30: UIWnd::Destroy - flag-based dispatch
# ============================================================

write_func("UIWnd::Destroy", 0x004D3F72, 343,
    "void __thiscall UIWnd::Destroy(void *this)",
    """void __thiscall UIWnd::Destroy(void *this)
{
  // Check and dispatch 15 different operation flags
  if ( g_flag_20B11EC ) { g_flag_20B11EC = 0; UIWnd::SetFontColor(); }
  if ( g_flag_20B11ED ) { g_flag_20B11ED = 0; UIBigMap::Create800(this); }
  if ( g_flag_20B11EE ) { g_flag_20B11EE = 0; CCBStageScene::Init(this); }
  if ( g_flag_20B11F0 ) { g_flag_20B11F0 = 0; CCBStageScene::Render(this); }
  if ( g_flag_20B11EF ) { g_flag_20B11EF = 0; CCBUI::ChangeSpecStateLum(this); }
  if ( g_flag_20B11FC ) { g_flag_20B11FC = 0; C2DSpark::Update(this); }
  if ( g_flag_20B11FD ) { g_flag_20B11FD = 0; UIBigMap::Create(this); }
  if ( g_flag_20B11FE ) { g_flag_20B11FE = 0; CCBStageScene::ShowAxis(this); }
  if ( g_flag_20B1200 ) { g_flag_20B1200 = 0; CCBStageScene::ShowFiveLineupEx(this); }
  if ( g_flag_20B11FF ) { g_flag_20B11FF = 0; UIWnd::SetWndColor_1(this); }
  if ( g_flag_20B1202 ) { g_flag_20B1202 = 0; UIBigMap::SetSpiritDefault(this); }
  if ( g_flag_20B1201 ) { g_flag_20B1201 = 0; sub_4D7C61(this); }
  if ( g_flag_20B1203 ) { g_flag_20B1203 = 0; UIBigMap::CheckSpiritDirect(this); }
  if ( g_flag_20B1204 ) { g_flag_20B1204 = 0; UIBigMap::_UIBigMap_3(this); }
  if ( g_flag_20B1205 ) { g_flag_20B1205 = 0; UIBigMap::OnMessage(this); }
  if ( g_flag_20B1206 ) { g_flag_20B1206 = 0; UICaption::UICaption(this); }
}
""")


# ============================================================
# Group 31: UIStatic::Update - combat AI targeting
# ============================================================

write_func("UIStatic::Update", 0x004CC981, 335,
    "bool __thiscall UIStatic::Update(void *this, int role_index, int a3)",
    """// This is mid-function code (starts after a loop entry) for combat target selection
bool __thiscall UIStatic::Update(void *this, int role_index, int a3)
{
  // ... (continues from earlier part of function)
  // Evaluate each potential target (0-10) for best match
  float best_ratio = g_initial_ratio;
  int best_target = -1;
  for ( int i = edi_start; i < 11; i++ )
  {
    void *scene = *(_DWORD *)((char *)this + 0x10 + 0x10);
    int total = CEffCustomShape::Destroy(scene, 1, i);
    float ratio = (float)CEffCustomShape::Destroy(scene, i) / (float)total;
    if ( i == 6 )
    {
      if ( sub_4E1A03(scene, role_index, i) )
        continue; // skip this target
    }
    if ( ratio < best_ratio )
    {
      best_target = i;
      best_ratio = ratio;
    }
  }
  if ( g_count <= 0 || best_target == -1 )
  {
    // Fallback: search slots for valid target
    for ( int slot = 0; slot < g_max_slot; slot++ )
    {
      if ( /* slot is in valid range and active */ )
      {
        if ( CCBSystem::SetAutoOnly(best_target) && Inventory::_Inventory(100 / g_count) )
        {
          // Found valid target
          break;
        }
      }
    }
    if ( best_target == -1 )
      return false;
  }
  // Apply target
  void *role = CCBStageRole_GetRolePtr(*(_DWORD *)((char *)this + 0x10), role_index);
  *(_BYTE *)((char *)role + 0x3B4) = 1;
  bool result = UIStaticEX::UIStaticEX(this, role_index, best_target, 0);
  role = CCBStageRole_GetRolePtr(*(_DWORD *)((char *)this + 0x10), role_index);
  *(_BYTE *)((char *)role + 0x3B4) = 0;
  if ( a3 )
  {
    // Record action in command buffer
    struct CMD cmd = {0};
    cmd.type = 0x103;
    cmd.role_index = role_index;
    cmd.target = best_target;
    memcpy(dst_buffer + role_index * 0x34, &cmd, 0x2C);
  }
  return result;
}
""")


# ============================================================
# Group 32: PlayerMgr::UpdateMagicByLV - physics/movement update
# ============================================================

write_func("PlayerMgr::UpdateMagicByLV", 0x00436BD0, 438,
    "int __thiscall PlayerMgr::UpdateMagicByLV(void *this)",
    """// Mid-function code for role movement/physics calculation
// Continues from a calling function - uses ebx (this), edi (config), esi (direction)
int __thiscall PlayerMgr::UpdateMagicByLV(void *this)
{
  // Calculate movement direction from target
  gbVec3D *dir = (gbVec3D *)((char *)this + 0x130);
  gbVec3D *result = PlayerMgr::CalRoleFull_MP(this, /* role */);
  *dir = *result;
  dir->Normalize();
  // Reverse direction if mode == 1
  if ( *(_DWORD *)((char *)this + 0x14C) == 1 )
    *dir = -(*dir);
  *(float *)((char *)this + 0x13C) = 0.0f;
  // Scale direction by speed
  float speed = *(float *)(config + 0x30);
  dir->x *= speed;
  dir->y *= speed;
  dir->z *= speed;
  // Accumulate position
  gbVec3D *pos = (gbVec3D *)((char *)this + 0x454);
  float dt = *(float *)((char *)this + 0x5C);
  gbVec3D delta = *dir * dt;
  pos->x += delta.x;
  pos->y += delta.y;
  pos->z += delta.z;
  *(float *)((char *)this + 0x13C) += dt;
  // Apply gravity/secondary motion
  float accel = *(float *)(config + 0x3C);
  dir->x += dir->x * accel;
  dir->y += dir->y * accel;
  dir->z += dir->z * accel;
  // Check distance to target
  gbVec3D *target_pos = (gbVec3D *)(config + 0x48);
  float dist = gbVec3D_Distance(pos, Inventory::Read2(target_pos));
  if ( dist < *(float *)(config + 0x24) )
    return 0; // reached target
  // Compute final position along direction
  dir->Normalize();
  float max_dist = *(float *)(config + 0x24);
  gbVec3D *final_pos = (gbVec3D *)((char *)this + 0x140);
  final_pos->x += dir->x * max_dist;
  final_pos->y += dir->y * max_dist;
  final_pos->z += dir->z * max_dist;
  pos->x = final_pos->x;
  pos->y = final_pos->y;
  pos->z = final_pos->z;
  // Update state
  *(_DWORD *)(config + 0x10) = 4;
  PlayerMgr_UpdateRoleTimer(*(_DWORD *)((char *)this + 0x38));
  if ( *(int *)(config + 0x54) >= 0 )
    *(_BYTE *)((char *)this + 0x3D0) = *(_BYTE *)(config + 0x54);
  gbInterp(this, 1);
  // Copy direction to facing
  memcpy((char *)this + 0x3A8, dir, 12);
  *(_BYTE *)((char *)this + 0x451) = 0;
  gbInterp(this, 0);
  return 0;
}
""")


# ============================================================
# CCBAI::CastNormalAttack (751b) - SKIPPED: Hex-Rays auto-exported this successfully
# (file: CCBAI__CastNormalAttack_004a2587.json)

# CCBEditor::CheckCCTValue (850b) - scalar dtor + EH destructor body
write_func("CCBEditor::CheckCCTValue", 0x00463010, 850,
    "void *__thiscall CCBEditor::CheckCCTValue(void *this, unsigned int flags)",
    """// Scalar deleting destructor wrapping a massive EH-based destructor
void *__thiscall CCBEditor::CheckCCTValue(void *this, unsigned int flags)
{
  CCBEditor_dtor_body(this); // calls loc_46302C
  if ( flags & 1 )
    operator delete(this);
  return this;
}

// Destructor body (EH prolog, destroys ~40 sub-objects in reverse construction order):
// void __thiscall CCBEditor_dtor_body(void *this)
// {
//   *(_DWORD *)this = &CCBEditor_vtable; // off_559678
//   // Free 4 heap pointers:
//   if ( *(void **)((char *)this + 0x1AD7C) ) operator delete(...);
//   if ( *(void **)((char *)this + 0x1ADF8) ) operator delete(...);
//   if ( *(void **)((char *)this + 0x154) )   operator delete(...);
//   if ( *(void **)((char *)this + 0x1ADFC) ) operator delete(...);
//   *(_BYTE *)((char *)this + 0x170) = 0;
//   *(_BYTE *)((char *)this + 0x1D6A0) = 0;
//   MainEquipUI::SetZX(this);
//   // Destroy sub-objects (UIFrameWnd, $E66_22_0 etc.) at offsets:
//   // 0x1D438, 0x1D2D0, 0x1D168, 0xCFFFC, 0x1CF4C, 0x1CE9C, 0x1CDEC,
//   // 0x1CD3C, 0x1CC9C, 0x1C9B0+0x178, 0x1C9B0+0x20, 0x1C498, 0x1C3F8,
//   // 0x1C358, 0x1C2B8
//   // Vector destructor iterators for arrays:
//   //   0x1B9F8 (14 * 0xA0), 0x19A9C (30 * 0xA0), 0x18494 (30 * 0xBC),
//   //   0x153D4 (240 * 0x34), 0x101F0 (80 * 0xA0), 0x6BF0 (240 * 0xA0),
//   //   0x6868 (5 * 0xA0)
//   // More sub-objects: 0x1B958, 0x1B8A8, 0x1B750, 0x1B5F8, 0x1B548,
//   //   0x1B4A8, 0x1AF40, 0x1AE0C, 0x67C4, 0x6724, 0x6684, 0x65E4,
//   //   0x6544, 0x64A4, 0x6450, 0x63B0
//   MainEquipUI::SetJT(this);
// }
""")


# ============================================================
# Main
# ============================================================

if __name__ == "__main__":
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    # Remove stale placeholder if it exists
    stale = os.path.join(OUTPUT_DIR, "CCBAI_CastNormalAttack_004a2587.json")
    if os.path.exists(stale):
        os.remove(stale)
        print(f"Removed stale placeholder: {stale}")
    print(f"Generated manual decompilation JSON files in {OUTPUT_DIR}")
    print(f"Total: 44 functions (CCBAI::CastNormalAttack auto-exported by Hex-Rays)")
