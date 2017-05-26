
#include "set.h"


bool is_member(string query, uint16 set_size, string* set)
{
	for (uint16 i = 0; i < set_size; i++)
	{
		if (query == set[i])
		{
			return true;
		}
	}
	return false;
}

bool is_member(uint16 query, uint16 set_size, uint16* set)
{
	for (uint16 i = 0; i < set_size; i++)
	{
		if (query == set[i])
		{
			return true;
		}
	}
	return false;
}


bool verify(uint16 set_size, string* set)
{
	for (uint16 i = 1; i < set_size; i++)
	{
		if (is_member(set[i], i, set))
		{
			return false;
		}
	}
	return true;
}

bool verify(uint16 set_size, uint16* set)
{
	for (uint16 i = 1; i < set_size; i++)
	{
		if (is_member(set[i], i, set))
		{
			return false;
		}
	}
	return true;
}


void set_union(uint16 num_of_sets, uint16* set_sizes, string** sets, uint16& set_size_union, string*& set_union)
{
	uint16 max_total_size = 0;
	for (uint16 i = 0; i < num_of_sets; i++)
	{
		max_total_size += set_sizes[i];
	}
	string* temp_set_union = new string[max_total_size];
	set_size_union = 0;
	for (uint16 i = 0; i < num_of_sets; i++) // Loop through each set.
	{
		for (uint16 j = 0; j < set_sizes[i]; j++) // Loop throgh the contents of each set.
		{
			if (!is_member(sets[i][j], set_size_union, temp_set_union))
			{
				temp_set_union[set_size_union] = sets[i][j];
				set_size_union++;
			}
		}
	}
	set_union = new string[set_size_union];
	for (uint16 i = 0; i < set_size_union; i++)
	{
		set_union[i] = temp_set_union[i];
	}
	delete[] temp_set_union;
}

void set_union(uint16 num_of_sets, uint16* set_sizes, uint16** sets, uint16& set_size_union, uint16*& set_union)
{
	uint16 max_total_size = 0;
	for (uint16 i = 0; i < num_of_sets; i++)
	{
		max_total_size += set_sizes[i];
	}
	uint16* temp_set_union = new uint16[max_total_size];
	set_size_union = 0;
	for (uint16 i = 0; i < num_of_sets; i++) // Loop through each set.
	{
		for (uint16 j = 0; j < set_sizes[i]; j++) // Loop throgh the contents of each set.
		{
			if (!is_member(sets[i][j], set_size_union, temp_set_union))
			{
				temp_set_union[set_size_union] = sets[i][j];
				set_size_union++;
			}
		}
	}
	set_union = new uint16[set_size_union];
	for (uint16 i = 0; i < set_size_union; i++)
	{
		set_union[i] = temp_set_union[i];
	}
	delete[] temp_set_union;
}


void set_intersection(uint16 num_of_sets, uint16* set_sizes, string** sets, uint16& set_size_intersection, string*& set_intersection)
{
	uint16 smallest_set = 0;
	for (uint16 i = 1; i < num_of_sets; i++)
	{
		if (set_sizes[i] < set_sizes[smallest_set])
		{
			smallest_set = i;
		}
	}
	string* temp_set_intersection = new string[set_sizes[smallest_set]];
	set_size_intersection = 0;
	for (uint16 i = 0; i < set_sizes[smallest_set]; i++)
	{
		bool included_flag = true;
		for (uint16 j = 0; j < num_of_sets; j++)
		{
			if ((j != smallest_set) && (!is_member(sets[smallest_set][i],set_sizes[j],sets[j])))
			{
				included_flag = false;
			}
		}
		if (included_flag)
		{
			temp_set_intersection[set_size_intersection] = sets[smallest_set][i];
			set_size_intersection++;
		}
	}
	set_intersection = new string[set_size_intersection];
	for (uint16 i = 0; i < set_size_intersection; i++)
	{
		set_intersection[i] = temp_set_intersection[i];
	}
	delete[] temp_set_intersection;
}

void set_intersection(uint16 num_of_sets, uint16* set_sizes, uint16** sets, uint16& set_size_intersection, uint16*& set_intersection)
{
	uint16 smallest_set = 0;
	for (uint16 i = 1; i < num_of_sets; i++)
	{
		if (set_sizes[i] < set_sizes[smallest_set])
		{
			smallest_set = i;
		}
	}
	uint16* temp_set_intersection = new uint16[set_sizes[smallest_set]];
	set_size_intersection = 0;
	for (uint16 i = 0; i < set_sizes[smallest_set]; i++)
	{
		bool included_flag = true;
		for (uint16 j = 0; j < num_of_sets; j++)
		{
			if ((j != smallest_set) && (!is_member(sets[smallest_set][i],set_sizes[j],sets[j])))
			{
				included_flag = false;
			}
		}
		if (included_flag)
		{
			temp_set_intersection[set_size_intersection] = sets[smallest_set][i];
			set_size_intersection++;
		}
	}
	set_intersection = new uint16[set_size_intersection];
	for (uint16 i = 0; i < set_size_intersection; i++)
	{
		set_intersection[i] = temp_set_intersection[i];
	}
	delete[] temp_set_intersection;
}

