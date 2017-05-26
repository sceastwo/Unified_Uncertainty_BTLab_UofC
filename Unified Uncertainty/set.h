

#ifndef __SET_H__
#define __SET_H__

typedef unsigned short uint16;
typedef unsigned long uint32;

#define MAX(a,b) (a >= b) ? a : b
#define MIN(a,b) (a <= b) ? a : b

#include <cstdlib>
#include <string>
using namespace std;

bool is_member(string query, uint16 set_size, string* set);
bool is_member(uint16 query, uint16 set_size, uint16* set);

bool verify(uint16 set_size, string* set); // Verify that there are no duplicate elements.
bool verify(uint16 set_size, uint16* set);

void set_union(uint16 num_of_sets, uint16* set_sizes, string** sets, uint16& set_size_union, string*& set_union);
void set_union(uint16 num_of_sets, uint16* set_sizes, uint16** sets, uint16& set_size_union, uint16*& set_union);

void set_intersection(uint16 num_of_sets, uint16* set_sizes, string** sets, uint16& set_size_intersection, string*& set_intersection);
void set_intersection(uint16 num_of_sets, uint16* set_sizes, uint16** sets, uint16& set_size_intersection, uint16*& set_intersection);



#endif

