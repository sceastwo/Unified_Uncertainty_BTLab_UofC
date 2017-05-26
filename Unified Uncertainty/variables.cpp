
#include "variables.h"

#define ARRAY_BLOCK_SIZE 50

uint16 variable_list::num_of_variables;
uint16 variable_list::array_length;
bool* variable_list::array_occupancy_flags;
uint16 variable_list::write_target_slot;
uint16 variable_list::read_target_slot;
string* variable_list::variable_names;
uint16* variable_list::domain_sizes;

void variable_list::initialize_list()
{
	num_of_variables = 0;
	array_length = ARRAY_BLOCK_SIZE;
	array_occupancy_flags = new bool[ARRAY_BLOCK_SIZE];
	for (uint16 i = 0; i < array_length; i++)
	{
		array_occupancy_flags[i] = false;
	}
	write_target_slot = 0;
	read_target_slot = 0;
	variable_names = new string[ARRAY_BLOCK_SIZE];
	domain_sizes = new uint16[ARRAY_BLOCK_SIZE];
}

void variable_list::reset_list()
{
	delete[] array_occupancy_flags;
	delete[] variable_names;
	delete[] domain_sizes;

	initialize_list();
}

bool variable_list::has_variable(string var)
{
	for (uint16 i = read_target_slot; i < read_target_slot+array_length; i++)
	{
		uint16 i2 = CYCLE(i,array_length);
		if (array_occupancy_flags[i2] && (variable_names[i2] == var))
		{
			read_target_slot = i2;
			return true;
		}
	}
	return false;
}

void variable_list::add_variable(string new_var, uint16 new_dom_size)
{
	// Utilize the write target slot.
	num_of_variables++;
	array_occupancy_flags[write_target_slot] = true;
	variable_names[write_target_slot] = new_var;
	domain_sizes[write_target_slot] = new_dom_size;
	// Search for a new empty slot.
	for (uint16 i = write_target_slot+1; i < array_length; i++)
	{
		if (!array_occupancy_flags[i])
		{
			write_target_slot = i;
			return;
		}
	}
	// Extend the array if needed.
	bool* new_array_occupancy_flags = new bool[array_length+ARRAY_BLOCK_SIZE];
	string* new_variable_names = new string[array_length+ARRAY_BLOCK_SIZE];
	uint16* new_domain_sizes = new uint16[array_length+ARRAY_BLOCK_SIZE];
	for (uint16 i = 0; i < array_length; i++)
	{
		new_array_occupancy_flags[i] = array_occupancy_flags[i];
		if (array_occupancy_flags[i])
		{
			new_variable_names[i] = variable_names[i];
			new_domain_sizes[i] = domain_sizes[i];
		}
	}
	for (uint16 i = array_length; i < array_length+ARRAY_BLOCK_SIZE; i++)
	{
		new_array_occupancy_flags[i] = false;
	}
	delete[] array_occupancy_flags;
	delete[] variable_names;
	delete[] domain_sizes;
	array_occupancy_flags = new_array_occupancy_flags;
	variable_names = new_variable_names;
	domain_sizes = new_domain_sizes;
	write_target_slot = array_length;
	array_length += ARRAY_BLOCK_SIZE;
}

void variable_list::read_variables(ifstream& in, uint16 num_of_new_vars)
{
	string new_var;
	uint16 new_dom_size;
	for (uint16 i = 0; i < num_of_new_vars; i++)
	{
		in >> new_var;
		if (in.fail())
		{
			throw "variable_list::read_variables: failed to read variable name";
		}
		in >> new_dom_size;
		if (in.fail())
		{
			throw "variable_list::read_variables: failed to read domain size";
		}
		add_variable(new_var, new_dom_size);
	}
}

void variable_list::remove_variable(string var)
{
	for (uint16 i = read_target_slot; i < read_target_slot+array_length; i++)
	{
		uint16 i2 = CYCLE(i,array_length);
		if (array_occupancy_flags[i2] && (variable_names[i2] == var))
		{
			num_of_variables--;
			array_occupancy_flags[i2] = false;
			if (write_target_slot > i2)
			{
				write_target_slot = i2;
			}
			read_target_slot = i2;
			return;
		}
	}
}

uint16 variable_list::get_domain_size(string var)
{
	for (uint16 i = read_target_slot; i < read_target_slot+array_length; i++)
	{
		uint16 i2 = CYCLE(i,array_length);
		if (array_occupancy_flags[i2] && (variable_names[i2] == var))
		{
			read_target_slot = i2;
			return domain_sizes[i2];
		}
	}
	return 0;
}


