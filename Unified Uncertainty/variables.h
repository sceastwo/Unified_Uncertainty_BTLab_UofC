

#ifndef __VARIABLES_H__
#define __VARIABLES_H__

typedef unsigned short uint16;
typedef unsigned long uint32;

#define CYCLE(a,b) (a < b) ? a : a-b;

#include <string>
#include <fstream>

using namespace std;

class variable_list
{
private:
	static uint16 num_of_variables;
	static uint16 array_length;
	static bool* array_occupancy_flags;
	static uint16 write_target_slot; // The array slot to which the next variable will be written. Must always reference an empty slot.
	static uint16 read_target_slot; // The array slot that was read most recently. May not reference a full slot if a variable is deleted.
	static string* variable_names;
	static uint16* domain_sizes; // The domain of each variable is 0, 1, ..., domain_sizes[i]-1
public:
	static void initialize_list(); // Should be called at the start of "main".
	static void reset_list();
	static bool has_variable(string var);
	static void add_variable(string new_var, uint16 new_domain_size); 
	static void read_variables(ifstream& in, uint16 num_of_new_vars); 
	static void remove_variable(string var);
	static uint16 get_domain_size(string var);

};










#endif

