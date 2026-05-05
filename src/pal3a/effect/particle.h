#ifndef PAL3A_PARTICLE_H
#define PAL3A_PARTICLE_H

#include "pal3a_types.h"

class direction_emitter_graph {
public:
    char _data[5300];

    direction_emitter_graph();
};

class elelife_emitter_graph {
public:
    char _data[5300];

    elelife_emitter_graph();
};

class elerandvec_emitter_graph {
public:
    char _data[5300];

    elerandvec_emitter_graph();
};

class emissionrate_emitter_graph {
public:
    char _data[5300];

    emissionrate_emitter_graph();
};

class graph {
public:
    char _data[5300];

    void cal_realval(D3DXVECTOR3 * ori, D3DXVECTOR3 * real);
    void save_graphto_file(gbVFile * fp);
    void get_graphfrom_file(gbVFile * fp);
};

class rgbcolor_particle_graph {
public:
    char _data[5300];

    rgbcolor_particle_graph();
};

class rotation_particle_graph {
public:
    char _data[5300];

    rotation_particle_graph();
};

class rotmulti_emitter_graph {
public:
    char _data[5300];

    rotmulti_emitter_graph();
};

class sg_customshape {
public:
    char _data[76];

    void set_transform(D3DXMATRIX * _tmat);
    void load_fromIniFile(char * _filename);
    void init_customshape();
    ~sg_customshape();
    int load_fromBinFile(char * _filename);
    sg_customshape();
    void get_vec(float _f, int _frame, D3DXVECTOR3 * _resvec);
    void get_vec(D3DXVECTOR3 * _resvec);
};

class sg_emission_control {
public:
    char _data[36952];

    void get_currotation(int index);
    void save_emicontrolto_file(gbVFile * fp);
    void get_currgbcolor(int index);
    void update_particle(int index);
    void get_emitter_data();
    void emitter_cyclestart();
    void get_resistance(int index);
    void init_particle_pos(int index, D3DXVECTOR3 * _offset);
    void get_tvalofparticle(int index);
    sg_emission_control();
    void reset_econtrol();
    void get_curvertexalpha(int index);
    void update_frame(float elapse_time, D3DXVECTOR3 * _offset);
    void get_initparticle_velocity(int index);
    void emitter_cycleend();
    void get_emicontrolfrom_file(gbVFile * fp);
    void init_emicontrol(sg_particle * par, sg_emitter * emi);
    void replace_particle(int num, D3DXVECTOR3 * _offset);
    void init_particle(int index, D3DXVECTOR3 * _offset);
    void get_cursize(int index);
    int get_particlenum();
    void get_looptex(int index);
};

class sg_emitter {
public:
    char _data[32088];

    void get_emitterfrom_file(gbVFile * fp);
    void restore_multiSize();
    int set_csf_name(char * _name);
    void init_emitter();
    void multi(float _num);
    void save_emitterto_file(gbVFile * fp);
    sg_emitter();
    void reset_orginalSize();
};

class sg_particle {
public:
    char _data[21572];

    void init_particle();
    void save_particleto_file(gbVFile * fp);
    sg_particle();
    void get_particlefrom_file(gbVFile * fp);
    void multi(float _num);
};

class sg_particle_scene {
public:
    char _data[362832];

    sg_particle_scene();
    bool load_scenefrom_file(char * filename);
    void multisize(float _msize);
    void reinit_scene();
    void save_sceneto_file(char * filename);
};

class size_particle_graph {
public:
    char _data[5300];

    size_particle_graph();
};

class sizemulti_emitter_graph {
public:
    char _data[5300];

    sizemulti_emitter_graph();
};

class vertexalpha_particle_graph {
public:
    char _data[5300];

    vertexalpha_particle_graph();
};

void delzero(char * str);
int getrand_fromfloat(float rate);
float getrand_fromfloatscope(float min, float max);
int getrand_yesorno();

#endif // PAL3A_PARTICLE_H
