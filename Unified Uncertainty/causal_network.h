

#ifndef __CAUSAL_NETWORK_H__
#define __CAUSAL_NETWORK_H__

typedef unsigned short uint16;
typedef unsigned long uint32;

#include <cstdlib>
#include <string>

using namespace std;

#include "MDD.h"

class variable
{
	string the_name;
	uint16 domain_size;
	uint16 num_of_parents;
	variable* parent_array;

public:

};

#endif

