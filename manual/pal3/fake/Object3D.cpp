// Object3D.cpp - fake empty implementation
// TODO: gradually enable

void Object3D::SetTransform(gbMatrix4 *pMatrix) {}
PalScriptMgr::BuildCmdTransform(pMatrix) { return 0; }
gbMatrix4::LoadIdentity() { return 0; }
gbMatrix4::SetAxisAngle(GB_AXIS_Z, this->m_roty) { return 0; }
gbMatrix4::RightMultiply(&v3) { return 0; }
