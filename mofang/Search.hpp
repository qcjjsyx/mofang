#ifndef SEARCH
#define SEARCH
#include "CubeState.hpp"
#define MAX_STEP 25

typedef struct {
	int co;
	int eo;
	int middle_edge_combination;
}phase1_t;//һ�׶�

typedef struct {
	int cornor;
	int edge1;
	int edge2;
}phase2_t;//���׶�



struct moves_t {
	int steps[16];
	int vaildLength;
	moves_t(int size) {
		for (int i = 0; i < 16; i++) {
			steps[i] = 0;
		}
		vaildLength = size;

	}
};


struct search_info_t
{
	cube_t initstate;
	int  face, total_depth, current_depth;
	moves_t* steps;
	int co_index;
	int eo_index;
	int me_combine_index;
	int ud_edges_perm_index;
	int middle_edges_perm_index;
	int cornors_perm_index;
};


enum phase_type {
	eo_index = 0,
	co_index,
	me_combine_index,
	ud_edges_perm_index,
	middle_edges_perm_index,
	cornors_perm_index
};


#endif