#pragma once
// Auto-generated: __old_sbh_region_struct

#include "__old_region_map_t.h"

class __old_sbh_page_struct;

class __old_sbh_region_struct {
public:
    __old_sbh_region_struct * p_next_region; // +0x0
    __old_sbh_region_struct * p_prev_region; // +0x4
    __old_region_map_t * p_starting_region_map; // +0x8
    __old_region_map_t * p_first_uncommitted; // +0xC
    __old_sbh_page_struct * p_pages_begin; // +0x10
    __old_sbh_page_struct * p_pages_end; // +0x14
    __old_region_map_t region_map[1025]; // +0x18
    // total size: 0x2020 (8224)

};
