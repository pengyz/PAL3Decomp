# PAL3A IDA Manual Review Report
Generated: 2026-05-06

## Summary

- Remaining userpurge: 7
- Decompilation failures (sampled 500): 37
- Boundary overlaps: 1521

---

## 1. Remaining Userpurge Functions

These functions have non-standard calling conventions that prevent correct decompilation.
Action: Manually determine correct calling convention in IDA (Edit > Functions > Set type).

| Address | Name | Type |
|---------|------|------|
| `0x0043A801` | sub_43A801 | `void __userpurge(int@<eax>, #643 *@<ecx>, int@<edi>, void *@<esi>, int, int, voi` |
| `0x004BC4DC` | sub_4BC4DC | `void __userpurge(int this@<ecx>, int, const tagRECT *, #812 *, const char *, uns` |
| `0x004C9B18` | UIScrollBar::SetBKRect_0 | `void __usercall __noreturn(int@<ebp>, const void *@<esi>)` |
| `0x004D3221` | sub_4D3221 | `void __usercall(int@<eax>, #468 *@<ecx>, int@<ebp>, float *@<esi>, double@<st0>)` |
| `0x005054EA` | sub_5054EA | `void __usercall __noreturn(void *@<eax>, int@<ecx>, int@<ebp>, void *@<edi>, con` |
| `0x0054C67C` | unknown_libname_232 | `int __usercall __spoils<ecx,st0>@<eax>(double@<st1>, double@<st0>)` |
| `0x0054C934` | unknown_libname_234 | `int __usercall __spoils<ecx,st0>@<eax>(double@<st1>, double@<st0>)` |

## 2. Decompilation Failures (sample)

These functions cannot be decompiled by Hex-Rays.
Action: Check SP analysis (Edit > Functions > Change stack pointer), fix function boundaries.

| Address | Name | Error |
|---------|------|-------|
| `0x00401042` | TxtFile::_TxtFile_0 | returned None |
| `0x00408173` | Archive::_Archive | returned None |
| `0x0040FABC` | CCBRoleState::_CCBRoleState_2 | returned None |
| `0x00412B91` | AStarPathFinder::_AStarPathFin | returned None |
| `0x00414051` | AStarPathFinder::DeleteNode | returned None |
| `0x004147B0` | ?id@?$ctype@G@std@@$D | returned None |
| `0x00414EB0` | gbVfsearch | returned None |
| `0x00415021` | collision::isEmbedded | returned None |
| `0x00417800` | CCBMagicWindow::_CCBMagicWindo | returned None |
| `0x004185A0` | matrix_3_1_float_::operator__0 | returned None |
| `0x0041A6F0` | matrix_3_3_float_::matrix_3_3_ | returned None |
| `0x0041BB00` | primitive_3_float_::setWorldTe | returned None |
| `0x0041CC77` | OpenSceneFile::_OpenSceneFile | returned None |
| `0x0041CFC0` | PAL3::IfFlag | returned None |
| `0x0041D216` | GRPinput::GRPinput_0 | returned None |
| `0x0041D439` | GRPinput::RunJoystickControlPa | returned None |
| `0x0041D446` | ?ClearKeyBuffer@GRPinput@@QAEX | returned None |
| `0x0041D670` | GRPinput::GetMouseSensitivity | returned None |
| `0x0041D6FF` | GRPinput::GetMousePos | returned None |
| `0x0041D716` | GRPinput::GetMouseFreePos | returned None |
| `0x0041D73B` | GRPinput::GetShiftedKeyState | returned None |
| `0x0041D87C` | GRPinput::AcquireJoystick | returned None |
| `0x0041DB28` | GRPinput::InitShiftedKeys | returned None |
| `0x0041E4BF` | GRPinput::RunJoystickControlPa | returned None |
| `0x0041F9C0` | Float2PixelX | returned None |
| `0x0041FA21` | Float2PixelY | returned None |
| `0x0041FC1B` | GRPinput::GetMouseFreePos_0 | returned None |
| `0x0041FC5D` | GRPinput::GetMouseDeltas_0 | returned None |
| `0x00420973` | NameSys::_NameSys_1 | returned None |
| `0x00420A5B` | NameSys::ZeroRef | returned None |

## 3. Boundary Overlaps (by overlap size)

Sorted by overlap size (smallest first = easiest to verify).
Action: In IDA, check if the split point is a real function boundary.
If yes: Edit > Functions > set_func_end, then create new function.
If no: PDB address mismatch, skip.

### Small overlaps (1-4 bytes) - likely alignment/off-by-one

| Parent Addr | Parent Name | Split Addr | PDB Name | Overlap |
|-------------|-------------|------------|----------|---------|
| `0x00413EE3` | AStarPathFinder::CanGoTil | `0x00413F0E` | AStarPathFinder::ReturnBe | 1 |
| `0x004140C7` | AStarPathFinder::Propagat | `0x004142A8` | AStarPathFinder::Push | 1 |
| `0x004144C6` | CCBAI::CastAttackItem | `0x00414770` | destructor' | 1 |
| `0x00414E26` | sub_414E26 | `0x00414E70` | gbGeomQuad::gbGeomQuad | 1 |
| `0x00414F94` | collision::traceCollision | `0x00414F99` | collision::unitSphereInte | 1 |
| `0x00415021` | collision::isEmbedded | `0x00415105` | collision::calcColliders | 1 |
| `0x00416637` | collision::collideAndSlid | `0x00416AA1` | frand | 1 |
| `0x0041892E` | sub_41892E | `0x00418960` | matrix<3,1,float>::operat | 1 |
| `0x00418A70` | matrix_3_1_float_::length | `0x00418AB0` | matrix<3,1,float>::setLen | 1 |
| `0x00418EFF` | sub_418EFF | `0x00418F00` | primitive<3,float>::opera | 1 |
| `0x00418F88` | sub_418F88 | `0x00419070` | primitive<3,float>::calcP | 1 |
| `0x00419185` | sub_419185 | `0x004191E0` | primitive<3,float>::insid | 1 |
| `0x0041A40E` | sub_41A40E | `0x0041A410` | >::insert | 1 |
| `0x0041A468` | sub_41A468 | `0x0041A470` | >::erase | 1 |
| `0x0041BB00` | primitive_3_float_::setWo | `0x0041BE00` | matrix<2,1,float>::x | 1 |
| `0x0041C952` | sub_41C952 | `0x0041CA6A` | FileSysDestory | 1 |
| `0x0041CDA6` | sub_41CDA6 | `0x0041CDAE` | OpenNULLFile::~OpenNULLFi | 1 |
| `0x0041D571` | sub_41D571 | `0x0041D57A` | GRPinput::SetJoystickPos | 1 |
| `0x0041D670` | GRPinput::GetMouseSensiti | `0x0041D681` | GRPinput::GetShiftedKeySt | 1 |
| `0x0041D77F` | GRPinput::GetJoystickFree | `0x0041D7A2` | GRPinput::GetJoystickDelt | 1 |
| `0x0041DD37` | sub_41DD37 | `0x0041DD39` | GRPinput::InitDIKToKEY | 1 |
| `0x0041E1FC` | sub_41E1FC | `0x0041E304` | GRPinput::GetKey | 1 |
| `0x0041E3B4` | GRPinput::GetCharKey | `0x0041E3E1` | GRPinput::DecideKeyStatus | 1 |
| `0x0041F826` | GRPinput::SetMouseSensiti | `0x0041F840` | destructor' | 1 |
| `0x0041F94E` | sub_41F94E | `0x0041F950` | RoleCtrl::GetRole | 1 |
| `0x0041FAAE` | sub_41FAAE | `0x0041FAB0` | >::c_str | 1 |
| `0x0041FCFB` | GRPinput::GetJoystickFree | `0x0041FD10` | std::char_traits<char>::a | 1 |
| `0x0041FF40` | _::_Copy | `0x004200D0` | std::allocator<char>::all | 1 |
| `0x0042024B` | sub_42024B | `0x00420353` | NameSys::~NameSys | 1 |
| `0x00422279` | std::bitset_48_::count_0 | `0x004222D1` | NameSys::Read | 1 |
| `0x004236AF` | std::logic_error::_Dorais | `0x004236C0` | destructor' | 1 |
| `0x00423860` | std::out_of_range::out_of | `0x00423890` | > | 1 |
| `0x00423E69` | std::bitset_10_::_Trim_0 | `0x00423E82` | NavFaceLayer::RayCol | 1 |
| `0x00423FD2` | NavFaceLayer::MapPoint2Su | `0x00424033` | NavigationInfo::Navigatio | 1 |
| `0x004255CD` | LayerNode::_LayerNode | `0x00425690` | LayerNode::RayCol | 1 |
| `0x0042916E` | PAL3::Destroy | `0x00429416` | WriteReg | 1 |
| `0x0042A9FA` | PAL3::StartWolf | `0x0042AB24` | PAL3::StartHideFight | 1 |
| `0x0042AC95` | LayerNode::Build | `0x0042AFD0` | PAL3::StartCombat | 1 |
| `0x0042B097` | PAL3::IfHideFightSucceed | `0x0042B17C` | PAL3::OnSwitchState | 1 |
| `0x0042CDE9` | PathObj::MapPoint2PathDis | `0x0042CE60` | >::_Pdif | 1 |
| ... | (694 more) | | | |

Total 1-4 byte overlaps: 734

### Medium overlaps (5-64 bytes)

| Parent Addr | Parent Name | Split Addr | PDB Name | Overlap |
|-------------|-------------|------------|----------|---------|
| `0x00414933` | sub_414933 | `0x00414960` | $E48 | 5 |
| `0x00418710` | matrix_3_1_float_::operat | `0x00418790` | matrix<3,1,float>::operat | 5 |
| `0x0041A21C` | sub_41A21C | `0x0041A220` | primitive<3,float>::verti | 5 |
| `0x0041B2CE` | sub_41B2CE | `0x0041B2F0` | >::_Ufill | 5 |
| `0x0041C59D` | sub_41C59D | `0x0041C5C0` | vert<float>::operator= | 5 |
| `0x0041DAF1` | sub_41DAF1 | `0x0041DB23` | GRPinput::CheckKeyEvents | 5 |
| `0x0041F883` | sub_41F883 | `0x0041F930` | ClientWidth | 5 |
| `0x004233C0` | std::bitset_10_::test | `0x00423420` | std::bitset<10>::_Tidy | 5 |
| `0x0042CBCB` | NavTileLayer::Tile2World | `0x0042CC20` | Role::SetScale | 5 |
| `0x004346EA` | sub_4346EA | `0x00434706` | PlayerMgr::AddFavor | 5 |
| `0x0043B569` | std::fill_8 | `0x0043B5C0` | >::insert | 5 |
| `0x0043D7D0` | std::copy_backward_8 | `0x0043D7E4` | MakeFightInfo | 5 |
| `0x0043ED6D` | sub_43ED6D | `0x0043EDA8` | Role::GotoAction | 5 |
| `0x00444169` | sub_444169 | `0x004441DD` | Role::UpdateTalk | 5 |
| `0x004463CF` | Role::UpdateMove | `0x004464FC` | Role::Check | 5 |
| `0x00448626` | Role::AMove | `0x004486AB` | Role::DrawView | 5 |
| `0x00450FF2` | sub_450FF2 | `0x00450FF3` | RoleCameraCtrl::Push | 5 |
| `0x004578EB` | RoleShadow::DisableFrameS | `0x00457948` | RoleShadow::DisableFrameS | 5 |
| `0x00458905` | RoleTaskPool::GetTaskPic | `0x00458921` | RoleTaskPool::GetTaskPic | 5 |
| `0x0045941D` | RoleTaskLine::RoleTaskLin | `0x00459460` | RoleTaskLine::RoleTaskLin | 5 |
| `0x0045A50A` | sub_45A50A | `0x0045A530` | std::copy_backward | 5 |
| `0x0045A5C0` | std::_Destroy_4 | `0x0045A5D0` | std::_Allocate | 5 |
| `0x0045BBDB` | CTrail::Create | `0x0045BC41` | Scene::LoadGeom | 5 |
| `0x0045FAC1` | sub_45FAC1 | `0x0045FAD5` | Scene::CanGoTile | 5 |
| `0x0046667B` | SceneMgr::LoadSpecialVari | `0x00466702` | SceneMgr::GetMap | 5 |
| `0x0047BBDB` | SceneObj::HasInverseState | `0x0047BC18` | SceneObj::HasInverseState | 5 |
| `0x0047DAF0` | SceneObj::Door_Switch | `0x0047DBDC` | SceneObj::SetFloorCanGo | 5 |
| `0x00486870` | long_100 | `0x004868B0` | long | 5 |
| `0x00491E9E` | SceneObj::SetFloorCanGo | `0x00492055` | SceneObj::Proc_MoveToAndF | 5 |
| `0x004937E4` | SceneObj::Proc_ObjectMove | `0x0049384B` | SceneObj::Proc_RoleToPosi | 5 |
| ... | (376 more) | | | |

Total 5-64 byte overlaps: 406

### Large overlaps (65+ bytes) - likely PDB version mismatch

| Parent Addr | Parent Name | Split Addr | PDB Name | Overlap |
|-------------|-------------|------------|----------|---------|
| `0x00423D39` | std::locale::_locale | `0x00423D40` | $E48 | 65 |
| `0x0042C9D0` | destructor__18 | `0x0042CA10` | destructor' | 65 |
| `0x004C34E0` | destructor__28 | `0x004C3520` | destructor' | 65 |
| `0x004D8D1E` | UICoverFrm::Create | `0x004D9420` | _MapElement::_MapElement | 65 |
| `0x00418BA0` | matrix_3_1_float_::normal | `0x00418BD0` | matrix<3,1,float>::abs | 66 |
| `0x00423DB0` | NavTileLayer::CanGoTile | `0x00423DB5` | $E73 | 66 |
| `0x004519F7` | RoleCamera::Ctrl_IsRevers | `0x00451A02` | RoleCamera::SetDist | 66 |
| `0x004C2744` | sub_4C2744 | `0x004C275F` | UIListBox::SetItemHeight | 66 |
| `0x0049A0B6` | CUtil::Rand_0 | `0x0049A0C0` | SceneObj::SetMainGroupObj | 67 |
| `0x0053DBC8` | CCBRoleState::IsRoleItem_ | `0x0053DCA8` | Object3D::GetScreenDegree | 67 |
| `0x0054B3C0` | ___dtold | `0x0054B433` | LineupUI::CreateStpCtl | 67 |
| `0x00418418` | sub_418418 | `0x00418420` | Collide_Ray<3,float>::vec | 68 |
| `0x004BAB74` | sub_4BAB74 | `0x004BABB0` | $E48 | 69 |
| `0x00540649` | __onexit | `0x00540670` | ChoseCompose::IsWaiting | 70 |
| `0x00423425` | sub_423425 | `0x00423480` | std::bitset<10>::referenc | 71 |
| `0x0053480D` | SaleUI::AddNum | `0x00534D1E` | SaleUI::ResetSuface | 71 |
| `0x0054078B` | ?_UnwindNestedFrames@@YGX | `0x00540793` | $E72 | 71 |
| `0x004B2B62` | scAsmDecoder::GetGlobalUs | `0x004B2B70` | scVarStack::Pop | 72 |
| `0x0049B786` | ORect::AddPoint | `0x0049B807` | ORect::AddPoint | 73 |
| `0x005406F7` | _sprintf | `0x00540700` | $E48 | 73 |
| `0x004F6F99` | Actor::Destroy | `0x004F6FD0` | UITitle_JDHY::UpdateNoteC | 74 |
| `0x004EAB9F` | UIRoleDialog::Render | `0x004EABD7` | UIRoleDialog::Destroy | 76 |
| `0x00547947` | __isctype | `0x00547970` | JusticeBookUI::PageUP | 76 |
| `0x0041BFA2` | sub_41BFA2 | `0x0041BFB0` | primitive<3,float>::userF | 79 |
| `0x004A9971` | cmd_CameraFree | `0x004A99A8` | cmd_Sub | 79 |
| `0x004B7DFF` | UIButton::_UIButton_0 | `0x004B7E1B` | UIButton::Update | 79 |
| `0x00418387` | sub_418387 | `0x00418390` | Collide_Ray<3,float>::end | 80 |
| `0x00426A7D` | sub_426A7D | `0x00426A90` | gbVfopen | 80 |
| `0x0044DF07` | sub_44DF07 | `0x0044DF10` | PalScriptWaitObj::ScriptU | 80 |
| `0x0044E769` | Scene::GetObjByID | `0x0044E780` | UIGameFrm::GetRoleDlg | 80 |
| ... | (351 more) | | | |

Total 65+ byte overlaps: 381
