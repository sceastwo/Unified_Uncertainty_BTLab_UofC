
#include "simple_expression.h"

simple_expression::simple_expression()
{
	num_of_vars = 0;
	var_names = new string[0];
	num_of_dummy_vars = 0;
	dummy_var_indices = new uint16[0];
	the_expression_type = ET_NULL;
}

simple_expression::simple_expression(uint16 new_num_of_vars, uint16 new_num_of_dummy_vars, expression_type new_expression_type)
{
	num_of_vars = new_num_of_vars;
	var_names = new string[num_of_vars];
	for (uint16 i = 0; i < num_of_vars; i++)
	{
		var_names[i] = "";
	}
	num_of_dummy_vars = new_num_of_dummy_vars;
	dummy_var_indices = new uint16[num_of_dummy_vars];
	for (uint16 i = 0; i < num_of_dummy_vars; i++)
	{
		dummy_var_indices[i] = 0;
	}
	the_expression_type = new_expression_type;
}

simple_expression::simple_expression(uint16 new_num_of_vars, string* new_var_names, 
									 uint16 new_num_of_dummy_vars, uint16* new_dummy_var_indices,
									 expression_type new_expression_type)
{
	num_of_vars = new_num_of_vars;
	var_names = new string[num_of_vars];
	for (uint16 i = 0; i < num_of_vars; i++)
	{
		var_names[i] = new_var_names[i];
	}
	num_of_dummy_vars = new_num_of_dummy_vars;
	dummy_var_indices = new uint16[num_of_dummy_vars];
	for (uint16 i = 0; i < num_of_dummy_vars; i++)
	{
		dummy_var_indices[i] = new_dummy_var_indices[i];
	}
	the_expression_type = new_expression_type;
}

simple_expression::simple_expression(simple_expression& existing_expression)
{
	num_of_vars = existing_expression.num_of_vars;
	var_names = new string[num_of_vars];
	for (uint16 i = 0; i < num_of_vars; i++)
	{
		var_names[i] = existing_expression.var_names[i];
	}
	num_of_dummy_vars = existing_expression.num_of_dummy_vars;
	dummy_var_indices = new uint16[num_of_dummy_vars];
	for (uint16 i = 0; i < num_of_dummy_vars; i++)
	{
		dummy_var_indices[i] = existing_expression.dummy_var_indices[i];
	}
	the_expression_type = existing_expression.the_expression_type;
}

simple_expression& simple_expression::operator=(simple_expression& existing_expression)
{
	delete[] var_names;
	delete[] dummy_var_indices;
	num_of_vars = existing_expression.num_of_vars;
	var_names = new string[num_of_vars];
	for (uint16 i = 0; i < num_of_vars; i++)
	{
		var_names[i] = existing_expression.var_names[i];
	}
	num_of_dummy_vars = existing_expression.num_of_dummy_vars;
	dummy_var_indices = new uint16[num_of_dummy_vars];
	for (uint16 i = 0; i < num_of_dummy_vars; i++)
	{
		dummy_var_indices[i] = existing_expression.dummy_var_indices[i];
	}
	the_expression_type = existing_expression.the_expression_type;
	return *this;
}

simple_expression* simple_expression::copy()
{
	return new simple_expression(*this);
}

simple_expression::~simple_expression()
{
	delete[] var_names;
	delete[] dummy_var_indices;
}


null_expression::null_expression() : simple_expression()
{
	the_expression_type = ET_NULL;
}

null_expression::null_expression(uint16 new_num_of_vars, string* new_var_names, 
								 uint16 new_num_of_dummy_vars, uint16* new_dummy_var_indices) : 
simple_expression(new_num_of_vars, new_var_names, 
				  new_num_of_dummy_vars, new_dummy_var_indices, ET_NULL)
{
}

null_expression::null_expression(null_expression& existing_expression) : simple_expression(existing_expression) 
{
}

null_expression& null_expression::operator=(null_expression& existing_expression)
{
	simple_expression::operator=(existing_expression);
	return *this;
}
	
null_expression* null_expression::copy()
{
	return new null_expression(*this);
}

null_expression::~null_expression()
{
}


full_expression::full_expression(uint16 new_num_of_vars, string* new_var_names, 
								 uint16 new_num_of_dummy_vars, uint16* new_dummy_var_indices) : 
simple_expression(new_num_of_vars, new_var_names, 
				  new_num_of_dummy_vars, new_dummy_var_indices, ET_FULL)
{
}

full_expression::full_expression(full_expression& existing_expression) : simple_expression(existing_expression) 
{
}

full_expression& full_expression::operator=(full_expression& existing_expression)
{
	simple_expression::operator=(existing_expression);
	return *this;
}
	
full_expression* full_expression::copy()
{
	return new full_expression(*this);
}

full_expression::~full_expression()
{
}


value_expression::value_expression(string new_var_name, uint16 new_val) : simple_expression(1, 0, ET_VAL) 
{
	var_names[0] = new_var_name;
	the_val = new_val;
}

value_expression::value_expression(uint16 new_dummy_var_index, uint16 new_val) : simple_expression(0, 1, ET_VAL)
{
	dummy_var_indices[0] = new_dummy_var_index;
	the_val = new_val;
}

value_expression::value_expression(value_expression& existing_expression) : simple_expression(existing_expression)
{
	the_val = existing_expression.the_val;
}

value_expression& value_expression::operator=(value_expression& existing_expression)
{
	simple_expression::operator=(existing_expression);
	the_val = existing_expression.the_val;
	return *this;
}

value_expression* value_expression::copy()
{
	return new value_expression(*this);
}

value_expression::~value_expression()
{
}


or_expression::or_expression(uint16 new_num_of_parts, simple_expression** new_alternatives_list) : 
simple_expression(new_alternatives_list[0]->num_of_vars, new_alternatives_list[0]->var_names,
new_alternatives_list[0]->num_of_dummy_vars, new_alternatives_list[0]->dummy_var_indices, ET_OR)
{
	num_of_parts = new_num_of_parts;
	alternatives_list = new simple_expression*[num_of_parts];
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		alternatives_list[i] = new_alternatives_list[i]->copy();
	}
}

or_expression::or_expression(or_expression& existing_expression) : simple_expression(existing_expression) 
{
	num_of_parts = existing_expression.num_of_parts;
	alternatives_list = new simple_expression*[num_of_parts];
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		alternatives_list[i] = existing_expression.alternatives_list[i]->copy();
	}
}

or_expression& or_expression::operator=(or_expression& existing_expression)
{
	simple_expression::operator=(existing_expression);
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		delete alternatives_list[i];
	}
	delete[] alternatives_list; 
	num_of_parts = existing_expression.num_of_parts;
	alternatives_list = new simple_expression*[num_of_parts];
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		alternatives_list[i] = existing_expression.alternatives_list[i]->copy();
	}
	return *this;
}

or_expression* or_expression::copy()
{
	return new or_expression(*this);
}

or_expression::~or_expression()
{
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		delete alternatives_list[i];
	}
	delete[] alternatives_list;
}


and_expression::and_expression(uint16 new_num_of_parts, simple_expression** new_components_list) : simple_expression()
{
	num_of_parts = new_num_of_parts;
	components_list = new simple_expression*[num_of_parts];
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		components_list[i] = new_components_list[i]->copy();
	}
	uint16* component_num_of_vars = new uint16[num_of_parts];
	string** component_variable_lists = new string*[num_of_parts];
	uint16* component_num_of_dummy_vars = new uint16[num_of_parts];
	uint16** component_dummy_variable_lists = new uint16*[num_of_parts];
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		component_num_of_vars[i] = components_list[i]->num_of_vars;
		component_variable_lists[i] = components_list[i]->var_names;
		component_num_of_dummy_vars[i] = components_list[i]->num_of_dummy_vars;
		component_dummy_variable_lists[i] = components_list[i]->dummy_var_indices;
	}
	set_union(num_of_parts, component_num_of_vars, component_variable_lists, num_of_vars, var_names);
	set_union(num_of_parts, component_num_of_dummy_vars, component_dummy_variable_lists, num_of_dummy_vars, dummy_var_indices);

	the_expression_type = ET_AND;

	delete[] component_num_of_vars;
	delete[] component_variable_lists;
	delete[] component_num_of_dummy_vars;
	delete[] component_dummy_variable_lists;
}

and_expression::and_expression(and_expression& existing_expression) : simple_expression(existing_expression)
{
	num_of_parts = existing_expression.num_of_parts;
	components_list = new simple_expression*[num_of_parts];
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		components_list[i] = existing_expression.components_list[i]->copy();
	}
}

and_expression& and_expression::operator=(and_expression& existing_expression)
{
	simple_expression::operator=(existing_expression);
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		delete components_list[i];
	}
	delete components_list;
	num_of_parts = existing_expression.num_of_parts;
	components_list = new simple_expression*[num_of_parts];
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		components_list[i] = existing_expression.components_list[i]->copy();
	}
	return *this;
}

and_expression* and_expression::copy()
{
	return new and_expression(*this);
}

and_expression::~and_expression()
{
	for (uint16 i = 0; i < num_of_parts; i++)
	{
		delete components_list[i];
	}
	delete components_list;
}


simple_expression* simple_expression::read_expression(ifstream& f_in)
{
	char char_buffer;
	f_in >> char_buffer;
}


string read_token(istream& input)
{

}

