

#ifndef __MDD_H__
#define __MDD_H__

typedef unsigned short uint16;
typedef unsigned long uint32;

#include <cstdlib>
#include "uncertainty_models.h"

class MDD_node
{
	uint16 var_index;
	uint16 var_domain_size;
	bool *child_terminal_flags;
	union node_child {MDD_node* internal_node; uncertainty_model* terminal_node;} *child_nodes;
};

class MDD
{
	uint16 num_of_vars;
	uint16* var_domain_sizes;
	uint16 num_of_terminal_models;
	uncertainty_model* terminal_models;
public:

};


#endif