#include "particle.h"

direction_emitter_graph::direction_emitter_graph()
{
    /* stub */
}

elelife_emitter_graph::elelife_emitter_graph()
{
    /* stub */
}

elerandvec_emitter_graph::elerandvec_emitter_graph()
{
    /* stub */
}

emissionrate_emitter_graph::emissionrate_emitter_graph()
{
    /* stub */
}

void graph::cal_realval(D3DXVECTOR3 * ori, D3DXVECTOR3 * real)
{
    /* stub */
}

void graph::save_graphto_file(gbVFile * fp)
{
    /* stub */
}

void graph::get_graphfrom_file(gbVFile * fp)
{
    /* stub */
}

rgbcolor_particle_graph::rgbcolor_particle_graph()
{
    /* stub */
}

rotation_particle_graph::rotation_particle_graph()
{
    /* stub */
}

rotmulti_emitter_graph::rotmulti_emitter_graph()
{
    /* stub */
}

void sg_customshape::set_transform(D3DXMATRIX * _tmat)
{
    /* stub */
}

void sg_customshape::load_fromIniFile(char * _filename)
{
    /* stub */
}

void sg_customshape::init_customshape()
{
    /* stub */
}

sg_customshape::~sg_customshape()
{
    /* stub */
}

int sg_customshape::load_fromBinFile(char * _filename)
{
    /* stub */
    return 0;
}

sg_customshape::sg_customshape()
{
    /* stub */
}

void sg_customshape::get_vec(float _f, int _frame, D3DXVECTOR3 * _resvec)
{
    /* stub */
}

void sg_customshape::get_vec(D3DXVECTOR3 * _resvec)
{
    /* stub */
}

void sg_emission_control::get_currotation(int index)
{
    /* stub */
}

void sg_emission_control::save_emicontrolto_file(gbVFile * fp)
{
    /* stub */
}

void sg_emission_control::get_currgbcolor(int index)
{
    /* stub */
}

void sg_emission_control::update_particle(int index)
{
    /* stub */
}

void sg_emission_control::get_emitter_data()
{
    /* stub */
}

void sg_emission_control::emitter_cyclestart()
{
    /* stub */
}

void sg_emission_control::get_resistance(int index)
{
    /* stub */
}

void sg_emission_control::init_particle_pos(int index, D3DXVECTOR3 * _offset)
{
    /* stub */
}

void sg_emission_control::get_tvalofparticle(int index)
{
    /* stub */
}

sg_emission_control::sg_emission_control()
{
    /* stub */
}

void sg_emission_control::reset_econtrol()
{
    /* stub */
}

void sg_emission_control::get_curvertexalpha(int index)
{
    /* stub */
}

void sg_emission_control::update_frame(float elapse_time, D3DXVECTOR3 * _offset)
{
    /* stub */
}

void sg_emission_control::get_initparticle_velocity(int index)
{
    /* stub */
}

void sg_emission_control::emitter_cycleend()
{
    /* stub */
}

void sg_emission_control::get_emicontrolfrom_file(gbVFile * fp)
{
    /* stub */
}

void sg_emission_control::init_emicontrol(sg_particle * par, sg_emitter * emi)
{
    /* stub */
}

void sg_emission_control::replace_particle(int num, D3DXVECTOR3 * _offset)
{
    /* stub */
}

void sg_emission_control::init_particle(int index, D3DXVECTOR3 * _offset)
{
    /* stub */
}

void sg_emission_control::get_cursize(int index)
{
    /* stub */
}

int sg_emission_control::get_particlenum()
{
    /* stub */
    return 0;
}

void sg_emission_control::get_looptex(int index)
{
    /* stub */
}

void sg_emitter::get_emitterfrom_file(gbVFile * fp)
{
    /* stub */
}

void sg_emitter::restore_multiSize()
{
    /* stub */
}

int sg_emitter::set_csf_name(char * _name)
{
    /* stub */
    return 0;
}

void sg_emitter::init_emitter()
{
    /* stub */
}

void sg_emitter::multi(float _num)
{
    /* stub */
}

void sg_emitter::save_emitterto_file(gbVFile * fp)
{
    /* stub */
}

sg_emitter::sg_emitter()
{
    /* stub */
}

void sg_emitter::reset_orginalSize()
{
    /* stub */
}

void sg_particle::init_particle()
{
    /* stub */
}

void sg_particle::save_particleto_file(gbVFile * fp)
{
    /* stub */
}

sg_particle::sg_particle()
{
    /* stub */
}

void sg_particle::get_particlefrom_file(gbVFile * fp)
{
    /* stub */
}

void sg_particle::multi(float _num)
{
    /* stub */
}

sg_particle_scene::sg_particle_scene()
{
    /* stub */
}

bool sg_particle_scene::load_scenefrom_file(char * filename)
{
    /* stub */
    return FALSE;
}

void sg_particle_scene::multisize(float _msize)
{
    /* stub */
}

void sg_particle_scene::reinit_scene()
{
    /* stub */
}

void sg_particle_scene::save_sceneto_file(char * filename)
{
    /* stub */
}

size_particle_graph::size_particle_graph()
{
    /* stub */
}

sizemulti_emitter_graph::sizemulti_emitter_graph()
{
    /* stub */
}

vertexalpha_particle_graph::vertexalpha_particle_graph()
{
    /* stub */
}

void delzero(char * str)
{
    /* stub */
}

int getrand_fromfloat(float rate)
{
    /* stub */
    return 0;
}

float getrand_fromfloatscope(float min, float max)
{
    /* stub */
    return 0.0f;
}

int getrand_yesorno()
{
    /* stub */
    return 0;
}

