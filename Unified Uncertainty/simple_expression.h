

#ifndef __SIMPLE_EXPRESSION_H__
#define __SIMPLE_EXPRESSION_H__

typedef unsigned short uint16;
typedef unsigned long uint32;

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "variables.h"
#include "set.h"

enum expression_type {ET_NULL, ET_FULL, ET_VAL, ET_OR, ET_AND};

class simple_expression
{
	friend void testing();
	friend class or_expression;
	friend class and_expression;
protected:
	uint16 num_of_vars;
	string* var_names;
	uint16 num_of_dummy_vars;
	uint16* dummy_var_indices;
	expression_type the_expression_type;

public:
	simple_expression();
	simple_expression(uint16 new_num_of_vars, uint16 new_num_of_dummy_vars, expression_type new_expression_type);
	simple_expression(uint16 new_num_of_vars, string* new_var_names, 
					  uint16 new_num_of_dummy_vars, uint16* new_dummy_var_indices,
					  expression_type new_expression_type); // A deep copy is used.
	simple_expression(simple_expression& existing_expression); // A deep copy is used.
	virtual simple_expression& operator=(simple_expression& existing_expression); // A deep copy is used.
	virtual simple_expression* copy(); // A deep copy is used.
	~simple_expression();

	static simple_expression* read_expression(ifstream& f_in);
};

class null_expression : public simple_expression
{
public:
	null_expression();
	null_expression(uint16 new_num_of_vars, string* new_var_names, 
					uint16 new_num_of_dummy_vars, uint16* new_dummy_var_indices); 
	null_expression(null_expression& existing_expression); 
	virtual null_expression& operator=(null_expression& existing_expression); 
	virtual null_expression* copy();
	~null_expression();
};

class full_expression : public simple_expression
{
public:
	full_expression(uint16 new_num_of_vars, string* new_var_names, 
					uint16 new_num_of_dummy_vars, uint16* new_dummy_var_indices); 
	full_expression(full_expression& existing_expression); 
	virtual full_expression& operator=(full_expression& existing_expression); 
	virtual full_expression* copy();
	~full_expression();
};

class value_expression : public simple_expression
{
	uint16 the_val;

public:
	value_expression(string new_var_name, uint16 new_val); // For non-dummy variables.
	value_expression(uint16 new_dummy_var_index, uint16 new_val); // For dummy variables.
	value_expression(value_expression& existing_expression);
	virtual value_expression& operator=(value_expression& existing_expression);
	virtual value_expression* copy();
	~value_expression();
};

class or_expression : public simple_expression
{
	uint16 num_of_parts;
	simple_expression** alternatives_list;

public:
	or_expression(uint16 new_num_of_parts, simple_expression** new_alternatives_list); // A deep copy is used.
	or_expression(or_expression& existing_expression); // A deep copy is used.
	virtual or_expression& operator=(or_expression& existing_expression); // A deep copy is used.
	virtual or_expression* copy(); // A deep copy is used.
	~or_expression();
};

class and_expression : public simple_expression
{
	uint16 num_of_parts;
	simple_expression** components_list;

public:
	and_expression(uint16 new_num_of_parts, simple_expression** new_components_list); // A deep copy is used.
	and_expression(and_expression& existing_expression); // A deep copy is used.
	virtual and_expression& operator=(and_expression& existing_expression); // A deep copy is used.
	virtual and_expression* copy(); // A deep copy is used.
	~and_expression();
};

string read_token(istream& input);


#endif

